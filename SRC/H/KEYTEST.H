//------------------------------------------------------------------------------
//Filename       keytest.h
//System         
//Author         Jim Taylor
//Date           Mon 23 Oct 1995
//Description    Keyboard test ISR data structures.
//
//In UI schema the keyboard feeds a queue of raw key and shift values.
//	Also recorded is wether it was a key press, hold, or release,
//  and the mouse position at that moment.
//	This queue is translated in the queue reading loop using a table into
//	recognised codes. 
//	The translation is done at this stage so the user can type ahead and
//	we can apply different schemas on different sheets.
//  The interrupt queue management code should be modified so that it refuses
//  additional 'held' events when there are only enough spaces to release all
//  the pressed keys. At present release events will be lost if the queue is 
//  full of held events. DOS doesn't handle release events at all.
//
//In 3d schema the keyboard sets bits in a bitfield.
//	This allows key hold durations to be measured, and multiple simultanious
//	keys to be easily provided.
//	There is a private array of 1 bit per scancode and a translation table
//	to a second bit table. This table indicates wether that scancode is
//	currently pressed or released.
//	All the interesting key combinations will be assigned entries in this 
//  second table, and a translation will be logged.
//	Each key has 2 consecutive bits (could change to 2 arrays of 1 bit)
//	The first bit shows if the key combination is currently pressed or released
//	The second bit indicates wether the UI has 'eaten' the keypress yet.
//  This provides a 'one-shot' test, or a 'held' test, as required for each
//  combination.
//------------------------------------------------------------------------------
#ifndef	KEYTEST_Included
#define	KEYTEST_Included
#include	"dosdefs.h"
//#include "display.h"

#include	"files.g"

#define	DEFAULT_KEYTEST 0

const	MAXqueuesize=32;	//Pointer to end of queue
const	TOTALKEYBITFLAGS=400;

enum	KeyBounce	{KEYHIT,KEYDBLHIT,KEYHELD,KEYREL,KEYHOT,KEYENDOFLIST};

//Keyshifts: 8 in total. 
//Lowest numbered has priority. 
//No bit set is equivalent to bit zero set = normal
//bit 0: normal
//bit 1: extra shift (grey keys)
//bit 2: AltGr
//bit 3: Alt
//bit 4: RHS Ctrl
//bit 5: LHS Ctrl
//bit 6: RHS Shift
//bit 7: LHS Shift		//LHS shift			//RHS shift			//Both shifts
//
enum	KeyShifts	{	KEYSH_none=0,		KEYSH_norm=1,		KEYSH_extsh=2, KEYSH_normext = 3,
						KEYSH_AltL=4,		KEYSH_AltGR=8,		KEYSH_Alt=12,
						KEYSH_CtrlL=16,		KEYSH_CtrlR=32,		KEYSH_Ctrl=48,
						KEYSH_ShiftL=64,	KEYSH_ShiftR=128,	KEYSH_Shift=192
					};

enum	KeyShift_BN	{	KEYSH_BN_norm=0,
						KEYSH_BN_extsh=1,
						KEYSH_BN_AltL=2,		KEYSH_BN_AltGR=3,
						KEYSH_BN_CtrlL=4,		KEYSH_BN_CtrlR=5,
						KEYSH_BN_ShiftL=6,		KEYSH_BN_ShiftR=7
					};

struct	UIKeyNoMouse		//This is used by joystick key emulators and similar
{							//to generate key presses in ECX probably.
UByte		keycode,		//Scancode. Top bits available for mouse events
			keyshifts;		//Shiftcode. normal + 6 shift keys + 'grey'
//KeyBounce	keyhit;			//hit or released key - releases ignored currently
UByte		keyhit;			//hit or released key - releases ignored currently
};

struct	UIKeyEvent:UIKeyNoMouse
							//Raw key definition. The mouse stuff allows
{							//mouse events to come here too.
//ScreenXY	mousecoords;	//Allows event to be linked with position/movement
};

struct	RawToHotMapRecord
{
	UIKeyNoMouse	keyinfo;
//	HotKey			thishotkey;
	UByte			thishotkey;
};

//inline	Bool	operator==(const	UIKeyEvent&	evt,const	UIKeyNoMouse&	comp)
//{
// 	return(Bool)(	(evt.keycode==comp.keycode)
//			  	&&	(evt.keyhit==comp.keyhit)
//				&&	(	((evt.keyshifts==0) && (comp.keyshifts&(int)KEYSH_norm))
//					||	(evt.keyshifts&comp.keyshifts)
//					)
//				);
//}

struct	CommonKeyMap
{
UByte		active;		//Are we in UI mode? Bool really
UByte		currshifts;	//Shift bit pattern
UByte		keyholds[16];		//256 bits - only need 128 bits realy
};

struct	UIKeyQueue:CommonKeyMap
{
UWord		addref,		//Pointer to add point in queue
			takeref,  	//Pointer to take point in queue
			queuesize;	//Pointer to end of queue
//ScreenXY	currmouse;	//Filled by mouse interrupt
UIKeyEvent	keyqueue[MAXqueuesize];		//This queue holds raw keys
};


struct	KeyMap3d:CommonKeyMap
{
	enum	{MAXKEYS=512};
UWord	mappings[MAXKEYS][8];
UByte	bitflags[(TOTALKEYBITFLAGS+7)/4];
};

enum	KeyValUI	{KeyValUI_MAX=32767};
enum	KeyVal3D	{keyVal3D_MAX=TOTALKEYBITFLAGS};
enum	FileNum;

struct	KeyMapping
{
	UWord	scancode:10,
			shiftstate:6;
	UWord	bitflag;
};
//------------------------------------------------------------------------------
//Author		Jim Taylor
//Date			Mon 23 Oct 1995
//Modified	
//
//Description	Keyboard test class. 
//				Mainly management of interrupts and DOS memory blocks
//------------------------------------------------------------------------------
class	keytests;
class	keytests
{	//most of the resources for the keyboard are declared
	//in main memory. This class contains pointers to those resources

UWord	orig_pm_sel;
ULong	orig_pm_off;
UWord	orig_rm_seg;
UWord	orig_rm_off;
void	ClearKeyTables();
public:
	struct	DPMIMem	{void* flat;};
DPMIMem	reftable3d,hitqueueui,isr_code,isr_data;				//ARM 25Jun96
Bool	ModeIs3D;
UWord		lastkeyasciicode;
//ScreenXY	lastkeymousexy;
	keytests();
	~keytests();
Bool	GetUIKey(UIKeyEvent&);	//fill in caller supplied record
void	RegUIConv(FileNum);
void	UnRegUIConv();
void	Reg3dConv(FileNum);
void	Reg3dConv(KeyMapping*,int);
bool	KeyHeld3d(KeyVal3D);
bool	KeyPress3d(KeyVal3D);
void	KeyFake3d(KeyVal3D,Bool held,Bool hit);
//ScreenXY&	mousepos();
void	InsertUIKey(UIKeyNoMouse& keyfake);
void	(keytests::*InsertUIKeyThru) (UIKeyNoMouse& keyfake);
void	(keytests::*KeyFake3dThru) (KeyVal3D,Bool held,Bool hit);

};

extern	keytests	Key_Tests;
///////////////////////////////////////////////////////////////////
#ifdef __WATCOMC__
extern	"C" void	__far	keytests__dosISRend();
extern	"C" void	__far	keytests__dosISRcode();
extern	"C" void	__far	keytests__dosISRstart();
#else
#ifdef __MSVC__
extern	"C" void	keytests__dosISRend();
extern	"C" void	keytests__dosISRcode();
extern	"C" void	keytests__dosISRstart();
#endif
#endif
extern	"C" void	keytests__dexISRtables();
extern	"C" void	keytests__dexISRstart();
extern	"C" void	keytests__dexISRcode();
extern	"C" void	keytests__dexISRend();

#endif
#include	"keymaps.h"
