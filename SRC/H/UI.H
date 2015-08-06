//------------------------------------------------------------------------------
//Filename       ui.h
//System         
//Author         Dave Whiteside
//Date           Wed 13 Sep 1995
//Description    
//------------------------------------------------------------------------------

// Base class for components
//
// This defines the basic structure of the component class
// In particular, link-listing and draw/action routine pointers are defined
// Basic size fields are also defined, 
// although they will occasionally not be needed.
// 
// The sub-classes provide support for local data.
//
// The sub-classes must provide the function SetCode. This sets a 
// specific function to a specific draw/action pointer.
//
// The sub-classes may provide the function writeback in their constructor.
// This function copies the local data back to the global data.
// It may be useful in the future to allow the writeback proc to be set 
// externally. For now, though...
//
//

#ifndef	UI_Included
#define	UI_Included


#define	DEFAULT_UI 0
#define	DEFAULT_COMPONENTW	TAB
#define	DEFAULT_COMPONENTH	VTAB

//TempCode RDH 07Dec95 #include	<iostream.h>
#include	"missman2.h"
#include	"screenxy.h"
#include	"palette.h"
#include	"display.h"
#include	"myerror.h"
//DeadCode JIM 14May96 #include	"worldinc.h"
//DeadCode JIM 14May96 #include	"fileman.h"

// Win95 Control flags for Win95ManageSheets
//DeadCode PD 05Aug96 enum	W95Cont	{WIN95CON_INIT=2,WIN95CON_GO=4,WIN95CON_EXIT=0};//JIM 16Jul96

enum	UIComponentFlags
{
	UIComponentFlagsMAX=65535
};
	#ifdef ENUMBITS_Included
BITABLE(UIComponentFlags);
ADDORABLE(UIComponentFlags);
	#endif
//Old_Code DAW 23Oct95 class	UICFlags
//Old_Code DAW 23Oct95 {
//Old_Code DAW 23Oct95 	protected:
//Old_Code DAW 23Oct95 	private:
//Old_Code DAW 23Oct95 	public:
//Old_Code DAW 23Oct95 				UICFlags::UICFlags();
//Old_Code DAW 23Oct95 				UICFlags::~UICFlags();
//Old_Code DAW 23Oct95 		UICFlags& operator|=(const UIComponentFlags& a);
//Old_Code DAW 23Oct95 		UICFlags& operator|(const UIComponentFlags& a);
//Old_Code DAW 23Oct95 };
//Old_Code DAW 23Oct95 

class	Install;
class	UIListDescComp;
class	ListEltComp;
class	UIComponent;
typedef	class	SheetBase	*SheetBasePtr;
typedef	class	UISheet 	*UISheetPtr;
typedef	class	UIComponent	*UIComponentPtr;
typedef	UISheetPtr	(*SheetMake) ();
struct	UIKeyEvent;
//DeadCode JIM 12Dec95 struct	ScreenRecord;
//------------------------------------------------------------------------------
enum	ProcReference	{PR_MIN=0,PR_MAX=0xffffffff};
typedef	Bool	(SheetBase::*InterSheetProc)	(UISheet* caller);	//inter sheet comms
#define	SHEETONLYPROC(name)	void	name()
typedef	int	(*SheetProc) (SheetBase*,UIComponent&);
//DeadCode JIM 30May96 typedef	void	(SheetBase::*NoDataProc) (class	NoDataComp&);
//DeadCode JIM 30May96 typedef	void	(SheetBase::*IntProc) (class	IntComp&);
//DeadCode JIM 30May96 typedef	void	(SheetBase::*IntRefProc) (class	IntRefComp&);
typedef	void	(SheetBase::*IntWBProc) (class	IntWBComp&);
typedef	void	(SheetBase::*IntRefWBProc) (class	IntRefWBComp&);
//DeadCode JIM 30May96 typedef	void	(SheetBase::*TextProc) (class	TextComp&);
typedef	void	(SheetBase::*TextWBProc) (class	TextWBComp&);
//DeadCode JIM 30May96 typedef	void	(SheetBase::*TextIntProc) (class	TextIntComp&);
//DeadCode JIM 30May96 typedef	void	(SheetBase::*TextIntRefProc) (class	TextIntRefComp&);
typedef	void	(SheetBase::*TextIntWBProc) (class	TextIntWBComp&);
typedef	void	(SheetBase::*TextIntRefWBProc) (class	TextIntRefWBComp&);
typedef	void	(SheetBase::*StringWBProc) (class	StringWBComp&);
typedef	UISheet*  (*BaseSheetDefType)	();
//------------------------------------------------------------------------------
class	SheetBase 
{
	public:
		//constructor
		SheetBase() {};
		//simplest default sheetproc - does nothing!
		static	int	EmptyDefault(SheetBase*,UIComponent&);
		static	int	PossHelp(SheetBase*,UIComponent&);


//Static control variables for UISheet
		enum	{MAX_CHILD_COUNT=32};
	static 	UISheetPtr	basesheet,			//this is the backmost sheet
						activesheet,		//this is the foregroundmost sheet
						newchildreq[MAX_CHILD_COUNT],   		//outstanding request to insert child
						newchildparent[MAX_CHILD_COUNT],		//parent of new child
						killsheetreq[MAX_CHILD_COUNT];		//sheet wants to die!
	static int			newchildcount,killsheetcount;


	static	Bool	KeyboardLastKey;
//DeadCode JIM 12Apr96 	static	FileNum			LastPic;
//DeadCode JIM 12Apr96 	static	UByte			TimeOut;
	static	BaseSheetDefType
							basesheetconstructor;
	static	enum			UILoopStage
			{	UI_IN_LIMBO,
				FALLBACK_DELETE,
				FALLBACK_BASESHEET,
				FALLBACK_NEWCHILD,
				MAINUI_DRAW,
				MAINUI_ANIM,
				MAINUI_KEYIN,
				MAINUI_SCREENSWAP
			}				UIloopstage;

//Default writeback routines. A bit of a pain
static	void	IntDefaultWBProc		(SheetBase*,IntWBComp& UIC);				
static	void	IntRefDefaultWBProc		(SheetBase*,IntRefWBComp& UIC);			
static	void	TextDefaultWBProc		(SheetBase*,TextWBComp& UIC);				
static	void	TextIntDefaultWBProc	(SheetBase*,TextIntWBComp& UIC);		
static	void	TextIntRefDefaultWBProc	(SheetBase*,TextIntRefWBComp& UIC);	
static	void	StringWBRemoveCursor	(SheetBase*,StringWBComp& UIC);
//DeadCode JIM 30May96 static	void	CallUICProc(ProcReference PR,UIComponent& UIC);
//DeadCode JIM 30May96 static	void	SetUICProc(ProcReference& PR,SheetProc& sp);

};
//------------------------------------------------------------------------------
//Author		Dave Whiteside
//Date			Wed 13 Sep 1995
//Modified	
//
//Description	This the the control structure for a Sheet. All sheets must have
//				one of these.
//
//
//Inputs		
//------------------------------------------------------------------------------
class	UISheet :public SheetBase
{
	friend	class	SheetBase;
	friend	class	UIListDescComp;
	friend	class	ManualPorts;
	friend	class	TnkMapSheet;
	friend	class	UITriSheet;

public:
	enum	UICompListType	{DRAW=1,TEST=2,ANIM=4,NODRAW=8,CURRENT=16,EVERYFRAME=32,UICompListType__ALL=63};

enum	RedrawFlags	{	REDRAW_NOTHING,					//does nothing!
						REDRAW_COMP=1,REDRAW_DRAW,REDRAW_HILIGHT,	//single component gets redrawn
						REDRAW_SHEET,					//this sheet gets redrawn and any children
						REDRAW_ALLCOMPS,
						REDRAW_SIBLINGS,				//this sheet and all siblings redrawn
						REDRAW_PARENT,					//parent sheet, this, and all siblings redrawn
						REDRAW_FROMTOP,					//everything is redrawn!
						REDRAW_DISABLE,					//stop sheet from drawing
						REDRAW_DISABLE_PARENT,			//stop sheet from drawing
						REDRAW_DISABLE_TOP,				//stop sheet from drawing
						};
protected:
//--------------------------------
//these are variables you will be directly useing from within specific sheets:

	InterSheetProc			  	//informs that another has closed
				siblingclosed,	//If you in turn close then return TRUE
				childclosed,	//otherwise return FALSE.
				parentclosed,
				anyclosed,
				movedto,movedfrom;

	UIComponentPtr	drawlist,		//Draw list
					testlist,		//Test list
					animlist,		//Active animation list - linked by Test ptr

					nodrawlist,		//Non-drawn components - linked by draw ptr
					current;

	struct	HotKeyHandlerRecord
	{
		UIComponentPtr	compptr;
		SheetProc		sheetprocptr;
	};

	struct	HandlerTable
	{
		HotKeyHandlerRecord	hotkeyhandlers[34];
	};

	static	HandlerTable	defaulthotkeyhandlertable;

	HandlerTable	*userhotkeytableptr;

	// A default and user-defined scancode-to-hotkey map file...

	static	fileblock	*defaultrawtohotmapfile;

	static	fileblock	*asciitablefile;

	fileblock	*newrawtohotmapfile;


	Window*		window;

	FileNum		backdropart;
	ScreenXY	basexy;
	ScreenWH	basewh;

	// Flag for Win95ManageSheets								//ARM 19Jun96
//DeadCode JIM 16Jul96 	static Bool	boolWin95Control;									//ARM 19Jun96

	UIComponent*	draggedcomponent;
	TextPage	permtextpage;
#define	PermText(T)		_Text.Perm(T,permtextpage)	
//--------------------------------
//These are some of the routines you will be using from within specific sheets
	UISheet();
	UISheet(ScreenXY X,ScreenWH W);
	virtual	~UISheet();
	void	RecursiveClosed(UISheetPtr x);

	void	SetScreenXY(SWord x, SWord y)		{	basexy.x=x;basexy.y=y;	}
	void	SetScreenWH(SWord w, SWord h)		{	basewh.w=w;basewh.h=h;	}

	UIComponentPtr	Add(UICompListType,UIComponentPtr); //merged with FullComponentFlags

//Old_Code DAW 15Sep95 		UIComponent*	writeback();
//Old_Code DAW 15Sep95 		compbaseproc	select,hilight,draw,drawhilight,move,rclickcode;

//routines to service requests from components to die:
Bool	WriteBack();
Bool	PopThisSheet(BaseSheetDefType);		//base sheets must launch new base sheet


//routines to service requests from components to change display
public:
void	SetRedraw(RedrawFlags,UIComponentPtr=NULL);
enum	SheetFlags
		{
			SHEETFLAGS_CLEAR=0,

			SHEETFLAGS_DISABLEWHENPARENT=1,
			SHEETFLAGS_DISABLEWHENSIBLING=2,
			SHEETFLAGS_ENCLOSE_CHILDREN=4,
			SHEETFLAGS_3SIZES=8,
			SHEETFLAGS_DETECTALLSCREEN=16,

			SHEETFLAGS_MAX=8192,
			SHEETFLAGS_ALIGN=65535
		}
		sheetflags:13;
protected:
UWord	RedrawCount	:3;						//0=no redraw //1-3=outstanding redraws //4=every frame
enum	{REDRAWCOUNT_SPECIAL=7};


void	ChangeCurrentTo(UIComponentPtr);

//routines to service requests from components to create new sheets:
UISheetPtr	SiblingSheet(UISheetPtr);			//creates a sibling sheet - BOTH will have focus
UISheetPtr	ChildSheet(UISheetPtr);				//creates a child sheet - this takes focus - error if child already exists!
UISheetPtr	NextChildSheet(UISheetPtr);			//creates a younger sibling to the youngest child
UISheetPtr	GrandChildSheet(UISheetPtr);		//creates a child to the youngest child


//--------------------------------
//These routines are used only from within forms to manage sheets
private:
	void	AddTEST(UIComponentPtr);		//specific list addition
	void	AddDRAW(UIComponentPtr);
	void	AddANIM(UIComponentPtr);
	void	AddNODRAW(UIComponentPtr);
	void	AddCURRENT(UIComponentPtr);
	void	DrawEverySheetNest();
	void	PartDrawEverySheetNest();
	void	DrawAllSheet();
	void	PartDrawAllSheet();
	void	drawcomponent(UIComponentPtr Draw);
	Bool	intree(UISheetPtr	find,UISheetPtr	base=basesheet);

	UISheetPtr	child,						//links between sheets
				sibling,
				parent;

	int	DebugParentage;

protected:
	SheetBase*	WhatChild()	{return child;}			
	SheetBase*	WhatSibling()	{return sibling;}			
	SheetBase*	WhatParent()	{return parent;}			

//--------------------------------
//static control pointers and access routines
private:
//these are used within forms
static	void	LodgeNewSheet(UISheetPtr olds, UISheetPtr news,Window *screen);
static	void	DrawEverySheet();
static	void	RedrawAsNeeded();
static	void	HandleInput();
static	void	SheetFallBack(Window	*screen);
static	Bool	testforedit(UIKeyEvent&	latestcookedkey);
static	Bool	testforhot(UIKeyEvent&	latestcookedkey);
static	void	SetMousePos(UIComponentPtr current);

static	void	ReorganiseTriSheets();
static	UISheetPtr FindTriSheet(UISheet* tritop);
static	int	MeasureTriDepth(UISheet* tritop);
static	int		AfterTheEvent(UISheet* p,int ypos,int xpos=0);
enum	Direction {SC_OPEN=2,SC_MID=1,SC_CLOSED=0,SC_STEP=2,SC_MIDBIAS=5};
static	void	scoringchildren(UISheet* p,Direction direction,UISheet*& bestsheet);
static	void	scoringchildren(UISheet* p,int& level,Direction direction,int& bestlevel,UISheet*& bestsheet);


//DeadCode RJS 20Mar96 static	Bool	processmousepress(UIKeyEvent& latestrawkey);
void	processmousemovement();
static Bool	findundermouse(const ScreenXY& mousepos,UISheetPtr& newsheet,UIComponentPtr& newcomp);
Bool	recurseundermouse(const ScreenXY& mousepos,UISheetPtr& newsheet,UIComponentPtr& newcomp);
void	PrepareToDraw(Window *screen);

UByte	HotKeyMatch(void	*tableptr, UIKeyEvent&	latestrawkey, UWord	&hotcode);		//RJS 29Mar96
UByte	ProcessHotKey(UIKeyEvent&	latestrawkey, UWord	&hotcode);
UWord	ProcessAsciiKey(UIKeyEvent&	latestrawkey);

// Prototypes for the 10 main hotkeys...

void	ProcessEnterKey(UIComponentPtr UIC);
void	ProcessHelpKey(UIComponentPtr UIC);
void	ProcessCancelKey(UIComponentPtr UIC);
void	ProcessNextCompKey(UIComponentPtr UIC);
void	ProcessPrevCompKey(UIComponentPtr UIC);
void	ProcessNextGroupKey(UIComponentPtr UIC);
void	ProcessPrevGroupKey(UIComponentPtr UIC);
void	ProcessAcceptKey(UIComponentPtr UIC);
void	ProcessLeftMouseButton(UIComponentPtr UIC);
void	ProcessRightMouseButton(UIComponentPtr UIC);
void	ProcessCentreMouseButton(UIComponentPtr UIC);
void	ProcessScreenShot(UIComponentPtr UIC);

static	void	XX_ProcessEnterKey			(SheetBase*,UIComponentPtr UIC);
static	void	XX_ProcessHelpKey			(SheetBase*,UIComponentPtr UIC);
static	void	XX_ProcessCancelKey			(SheetBase*,UIComponentPtr UIC);
static	void	XX_ProcessNextCompKey		(SheetBase*,UIComponentPtr UIC);
static	void	XX_ProcessPrevCompKey		(SheetBase*,UIComponentPtr UIC);
static	void	XX_ProcessNextGroupKey		(SheetBase*,UIComponentPtr UIC);
static	void	XX_ProcessPrevGroupKey		(SheetBase*,UIComponentPtr UIC);
static	void	XX_ProcessAcceptKey			(SheetBase*,UIComponentPtr UIC);
static	void	XX_ProcessLeftMouseButton	(SheetBase*,UIComponentPtr UIC);
static	void	XX_ProcessLMBHeld			(UISheet*,UIComponentPtr UIC);
static	void	XX_ProcessLMBRls			(UISheet*,UIComponentPtr UIC);
static	void	XX_ProcessRightMouseButton	(SheetBase*,UIComponentPtr UIC);
static	void	XX_ProcessCentreMouseButton	(SheetBase*,UIComponentPtr UIC);
static	void	XX_ProcessScreenShot		(SheetBase*,UIComponentPtr UIC);

// Prototypes for the string and string hotkey input...
Bool	InsertIntoString(StringWBComp&	UIC, char	asciicode);
void	RemoveFromString(StringWBComp&	UIC);
static	void	StringLeftCursor(UISheet*,StringWBComp&	UIC);
static	void	StringRightCursor(UISheet*,StringWBComp&	UIC);
static	void	StringBackspace(UISheet*,StringWBComp&	UIC);
static	void	StringDelete(UISheet*,StringWBComp&	UIC);
static	void	StringSpacebar(UISheet*,StringWBComp&	UIC);
static	void	StringProcessAscii(UISheet*,StringWBComp&	UIC);
static	void	StringCancel(UISheet*,StringWBComp&	UIC);

public:
//this is the public access to forms
static	void	ManageSheets(Window		*screen);
static	Bool	Win95ManageSheets(Window	*screen);	//ARM 19Jun96
Bool	PopThisSheet(RedrawFlags flags=REDRAW_PARENT);				 		//nested sub-sheets can give up//RDH 06Feb96


static	proc	DefaultReqDraw(SheetBase*,UIComponent&);
static	proc	DefaultReqDrawHi(SheetBase*,UIComponent&);

void	NewHotKey(UByte	hotkey, SheetProc	procaddr, UIComponentPtr UIC);
void	HotKeyTable(FileNum	mapfilename=FIL_NULL);

void	StringEditDisable(StringWBComp	*UIC);
void	StringEditEnable(StringWBComp	*UIC);

//some standard default sheetprocs. I still don't know how well this will work at this level!

//DeadCode JIM 16Apr96 		void	Border(IComponent& a,Colour C);
//DeadCode JIM 16Apr96 		UWord	SmackNoPal(Smack *smk);							//DAW 09Feb96
//DeadCode JIM 16Apr96 		UWord	SmackFull(Smack *smk);							//DAW 09Feb96
//DeadCode JIM 16Apr96 		Smack*	OpenSmack(FileNum filenumber);					//DAW 09Feb96

//END:: standard default sheetprocs. I still don't know how well this will work at this level!
#include	"sheetlst.h"

};

class	UITriSheet:public UISheet
{
	friend class UISheet;
protected:
	UIComponentPtr	subdrawlist,		//Draw list
					subtestlist,		//Test list
					subcurr;
	int	miny,maxy;
	int direction;
	SheetProc	secselectrtn;
	UITriSheet(int min_y,int max_y,SheetProc DrawRtn)
#ifdef	BRIEFING_Included
		{ConTriSheet(min_y,max_y,DRAWERW,DrawRtn);}
	UITriSheet(int min_y,int max_y,int width=DRAWERW,SheetProc DrawRtn=NULL)
#else
		{ConTriSheet(min_y,max_y,PIXEL640*150,DrawRtn);}
	UITriSheet(int min_y,int max_y,int width=PIXEL640 * 184,SheetProc DrawRtn=NULL)
#endif
		{ConTriSheet(min_y,max_y,width,DrawRtn);}


	~UITriSheet();

void	TriMaxMode();
void	TriMinMode();

private:
void	ConTriSheet(int min_y,int max_y,int width,SheetProc DrawRtn);
static	int TriReOpen(SheetBase*,UIComponent&);

};

//------------------------------------------------------------------------------

	#ifdef ENUMBITS_Included
	BITABLE(UISheet::UICompListType);
	ADDORABLE(UISheet::UICompListType);
	BITABLE(UISheet::RedrawFlags);
	ADDORABLE(UISheet::RedrawFlags);
	#endif

//------------------------------------------------------------------------------
//Author		Dave Whiteside
//Date			Fri 15 Sep 1995
//Modified	
//
//Description	
//
//Inputs		
//------------------------------------------------------------------------------
class	UIComponent
{

public:

//Old_Code DAW 18Oct95 		UIComponent*	Prev;
//Old_Code DAW 18Oct95 		UIComponent*	Next;
	UIComponentPtr	nextdraw,		//Draw list link
					nexttest;		//Test list link
	ScreenXY	xy;				//component coverage box
	ScreenWH	wh;
enum	FullComponentFlags		
	{	//incoorporates UICompListType //some flags are secret!
		CLEARFLAGS=0,
		//currently 64 is spare
//DeadCode JIM 12Apr96 		WHSET=128,			   	//currently unused tests
//DeadCode JIM 12Apr96 		XYSET=256,

		WBACTIVE=64,			//important. Identifies wether component is derived from UIWBComp

		FCF_UNSIGNED=65535
	}	Flags		:7;
UWord	RedrawCount	:3;						//0=no redraw //1-3=outstanding redraws //4=every frame
//TempCode JIM 22Apr97 UWord	IsHilight	:1;
UWord	tabpast		:1;

enum	WinShiftDef	xalign:2,
					yalign:2;
UWord	ReturnCodes	:1;

	TextSnip0		helptext;

	SheetProc		
					DrawRtn,		//Code to be done when drawing
					DrawHiRtn,		//Code to be done when drawing as current hilight

					SelectRtn,		//Code to be done as soon as Selected
					Select2Rtn,		//Code to be done as soon as Selected by rh mouse
					HilightRtn,		//Code to be done as soon as hilighted
					DeHilightRtn;	//Code to be done as soon as dehilighted

	UIComponentPtr	HelpText(TextSnip0);	
	UIComponentPtr	DrawCode(SheetProc);	
	UIComponentPtr	DrawHiCode(SheetProc);	
	UIComponentPtr	SelectCode(SheetProc);	
	UIComponentPtr	Select2Code(SheetProc);	
	UIComponentPtr	HilightCode(SheetProc);	
	UIComponentPtr	DeHilightCode(SheetProc);	
	UIComponentPtr	MousePos(WinShiftDef x,WinShiftDef y)
		{xalign=x;yalign=y;return this;}


protected:							//These should be protected! 
	UIComponent();		//It stops raw components being created
	UIComponent(SWord X,SWord Y,SWord W,SWord H);

	TextBuild	MakeText(TextRef,int)
		{return ((TextBuild) 0);}	//for now...

public:
//DeadCode JIM 12Apr96 	~UIComponent();

//DeadCode JIM 11Mar97 	void	SetScreenXY(SWord x, SWord y)		{	xy.Set(x,y);	}
//DeadCode JIM 11Mar97 	void	SetScreenWH(SWord w, SWord h)		{	wh.Set(w,h);	}

//DeadCode JIM 15Nov95 	UIComponent*	GetDraw();
//DeadCode JIM 15Nov95 	void			SetDraw(UIComponent* x);
//TempCode JIM 21Nov95 	void			SetFlags(UIComponentFlags a);
//TempCode JIM 21Nov95 	UWord			TestFlag(UIComponentFlags a);

};

//shell inherit
#define	SHELLHERIT(outputtype,fnname,paramtype,parent)			\
	outputtype	fnname(paramtype	X)		   					\
		{return (outputtype)	parent::fnname(X);}

#define	SHELLHERITL(outputtype,fnname,paramlist,parent,paramlist2)			\
	outputtype	fnname paramlist		   					\
		{return (outputtype)	parent::fnname paramlist2;}

////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
//
//  Basic component types for no value, 
//	and various forms of integer value.
//
//
//
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------------
//Author		Dave Whiteside
//Date			Wed 13 Sep 1995
//Modified	
//
//Description	A component with nothing in it.
//
//Inputs		
//------------------------------------------------------------------------------
class	NoDataComp	:public UIComponent
{
public:
				NoDataComp(SWord X,SWord Y,SWord W,SWord H):
					UIComponent(X,Y,W,H)	{};
				NoDataComp():
					UIComponent()	{};

	
 	SHELLHERITL(NoDataComp*,MousePos,(WinShiftDef x,WinShiftDef y),
							UIComponent,(x,y));
	SHELLHERIT(NoDataComp*,DrawCode,SheetProc,UIComponent);
	SHELLHERIT(NoDataComp*,SelectCode,SheetProc,UIComponent);
	SHELLHERIT(NoDataComp*,Select2Code,SheetProc,UIComponent);
	SHELLHERIT(NoDataComp*,DrawHiCode,SheetProc,UIComponent);
	NoDataComp*	SetBack(NoDataComp*		&X)	{X=this;		return(this);}
	NoDataComp*	SetBack(UIComponentPtr	&X)	{X=this;		return(this);}
	//////////	DataVal()		/// not got one!

};

//------------------------------------------------------------------------------
//Author		Dave Whiteside
//Date			Wed 13 Sep 1995
//Modified	
//
//Description	A component with nothing in it.
//
//Inputs		
//------------------------------------------------------------------------------
class	WriteBackComp	:public NoDataComp
{
public:
	SheetProc	wbcode;

				WriteBackComp(SWord X,SWord Y,SWord W,SWord H):
					NoDataComp(X,Y,W,H)
					{Flags=WBACTIVE;}

};


//------------------------------------------------------------------------------
//Author		Dave Whiteside
//Date			Wed 13 Sep 1995
//Modified	
//
//Description	A component with an integer in it.
//				The value cannot be changed.
//
//Inputs		
//------------------------------------------------------------------------------
class	IntComp	:public UIComponent
{
public:
	int		value;
				IntComp(SWord X,SWord Y,SWord W,SWord H):
					UIComponent(X,Y,W,H)	{};
 	SHELLHERITL(IntComp*,MousePos,(WinShiftDef x,WinShiftDef y),
							UIComponent,(x,y));
	SHELLHERIT(IntComp*,DrawCode,SheetProc,UIComponent);
	SHELLHERIT(IntComp*,SelectCode,SheetProc,UIComponent);
	SHELLHERIT(IntComp*,Select2Code,SheetProc,UIComponent);
	SHELLHERIT(IntComp*,DrawHiCode,SheetProc,UIComponent);
	IntComp*	SetBack(IntComp*		&X)	{X=this;		return(this);}
	IntComp*	SetBack(UIComponentPtr	&X)	{X=this;		return(this);}
	IntComp*	DataVal(int i)
					{value=i;									return(this);}
protected:

};

//------------------------------------------------------------------------------
//Author		Dave Whiteside
//Date			Wed 13 Sep 1995
//Modified	
//
//Description	A component with an integer reference in it.
//				The value should not be changed.
//				If the value is changed then the referenced value changes 
//				immediately
//
//Inputs		
//------------------------------------------------------------------------------
class	IntRefComp	:public UIComponent
{
public:
	SLong		*value;
				IntRefComp(SWord X,SWord Y,SWord W,SWord H):
					UIComponent(X,Y,W,H)	{};
 	SHELLHERITL(IntRefComp*,MousePos,(WinShiftDef x,WinShiftDef y),
							UIComponent,(x,y));
	SHELLHERIT(IntRefComp*,DrawCode,SheetProc,UIComponent);
	SHELLHERIT(IntRefComp*,SelectCode,SheetProc,UIComponent);
	SHELLHERIT(IntRefComp*,Select2Code,SheetProc,UIComponent);
	SHELLHERIT(IntRefComp*,DrawHiCode,SheetProc,UIComponent);
	IntRefComp*	SetBack(IntRefComp*		&X)	{X=this;		return(this);}
	IntRefComp*	SetBack(UIComponentPtr	&X)	{X=this;		return(this);}
	IntRefComp*	DataVal(SLong	&i)
					{value=&i;									return(this);}
protected:

};
	
//------------------------------------------------------------------------------
//Author		Dave Whiteside
//Date			Wed 13 Sep 1995
//Modified	
//
//Description	A component with an integer reference in it.
//				If the value is changed then it will be written back 
//				by a call to the procedure registered to WriteCode.
//				The default writeback simply copies the value.
//				
//Inputs		
//------------------------------------------------------------------------------
class	IntWBComp	:public WriteBackComp
{
public:
	SLong		*wbref,value;
				IntWBComp(SWord X,SWord Y,SWord W,SWord H):
					WriteBackComp(X,Y,W,H)
					{wbref=NULL;value=0;wbcode=(SheetProc) SheetBase::IntDefaultWBProc;}
 	SHELLHERITL(IntWBComp*,MousePos,(WinShiftDef x,WinShiftDef y),
							UIComponent,(x,y));
	SHELLHERIT(IntWBComp*,DrawCode,SheetProc,UIComponent);
	SHELLHERIT(IntWBComp*,SelectCode,SheetProc,UIComponent);
	SHELLHERIT(IntWBComp*,Select2Code,SheetProc,UIComponent);
	SHELLHERIT(IntWBComp*,DrawHiCode,SheetProc,UIComponent);
	IntWBComp*	SetBack(IntWBComp*		&X)	{X=this;		return(this);}
	IntWBComp*	SetBack(UIComponentPtr	&X)	{X=this;		return(this);}
	IntWBComp*	WriteCode(SheetProc d)
					{wbcode=d;									return(this);}
	IntWBComp*	DataVal(SLong	&i)
					{value=i,wbref=&i;							return(this);}
protected:

};

//------------------------------------------------------------------------------
//Author		Robert Slater
//Date			Wed 27 Mar 1996
//Modified	
//
//Description	A component with a string reference in it.
//				If the string is changed then it will be written back 
//				by a call to the procedure registered to WriteCode.
//				The default writeback simply copies the value.
//				
//Inputs		
//------------------------------------------------------------------------------
class	StringWBComp	:public WriteBackComp
{
public:
	char*		value;
	int			maxlen,currlen,currpos;
	CON		StringWBComp(SWord X,SWord Y,SWord W,SWord H):
	   			WriteBackComp(X,Y,W,H)
	   			{value=NULL;currpos = -1;wbcode=(SheetProc) SheetBase::StringWBRemoveCursor;}
 	SHELLHERITL(StringWBComp*,MousePos,(WinShiftDef x,WinShiftDef y),
							UIComponent,(x,y));
	SHELLHERIT(StringWBComp*,DrawCode,SheetProc,UIComponent);
	SHELLHERIT(StringWBComp*,SelectCode,SheetProc,UIComponent);
	SHELLHERIT(StringWBComp*,Select2Code,SheetProc,UIComponent);
	SHELLHERIT(StringWBComp*,DrawHiCode,SheetProc,UIComponent);

	StringWBComp*	SetBack(StringWBComp*		&X)	{X=this;		return(this);}
	StringWBComp*	SetBack(UIComponentPtr	&X)	{X=this;		return(this);}
	StringWBComp*	WriteCode(SheetProc d)
					{wbcode=d;									return(this);}
	StringWBComp*	DataVal(char* loc,SLong	len)
					{value=loc,maxlen=len;						return(this);}
protected:

};

//------------------------------------------------------------------------------
//Author		Dave Whiteside
//Date			Wed 13 Sep 1995
//Modified	
//
//Description	A component with an integer reference in it.
//				A local copy of the value is kept in an external location!!!
//				Both locations are specified in DataVal
//				If the value is changed then it will be written back
//				by a call to the procedure registered to WriteCode.
//				The default writeback simply copies the value.
//
//Inputs		
//------------------------------------------------------------------------------
class	IntRefWBComp	:public WriteBackComp
{
public:
	SLong		*wbref,&value;
				IntRefWBComp(SWord X,SWord Y,SWord W,SWord H,SLong& vloc):
					WriteBackComp(X,Y,W,H),
					value(vloc)
					{wbref=NULL;wbcode=(SheetProc) SheetBase::IntRefDefaultWBProc;}
 	SHELLHERITL(IntRefWBComp*,MousePos,(WinShiftDef x,WinShiftDef y),
							UIComponent,(x,y));
	SHELLHERIT(IntRefWBComp*,DrawCode,SheetProc,UIComponent);
	SHELLHERIT(IntRefWBComp*,SelectCode,SheetProc,UIComponent);
	SHELLHERIT(IntRefWBComp*,Select2Code,SheetProc,UIComponent);
	SHELLHERIT(IntRefWBComp*,DrawHiCode,SheetProc,UIComponent);
	IntRefWBComp*	SetBack(IntRefWBComp*		&X)	{X=this;		return(this);}
	IntRefWBComp*	SetBack(UIComponentPtr		&X)	{X=this;		return(this);}
	IntRefWBComp*	WriteCode(SheetProc d)
					{wbcode=d;								return(this);}
	IntRefWBComp*	DataVal(SLong	&g)
					{wbref=&g;value=g;				return(this);}
protected:

};

////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
//
//  Simple text-only component types: 
//	write-back and read-only variants
//
//
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
//Author		Dave Whiteside
//Date			Wed 13 Sep 1995
//Modified	
//
//Description	A component with text in it. 
//				The text value is copied to local, where it should not be changed
//
//Inputs		
//------------------------------------------------------------------------------
class	TextComp	:public NoDataComp
{
public:
	TextRef	text;
				TextComp(SWord X,SWord Y,SWord W,SWord H):
					NoDataComp(X,Y,W,H)	{};
 	SHELLHERITL(TextComp*,MousePos,(WinShiftDef x,WinShiftDef y),
							UIComponent,(x,y));
	SHELLHERIT(TextComp*,DrawCode,SheetProc,UIComponent);
	SHELLHERIT(TextComp*,SelectCode,SheetProc,UIComponent);
	SHELLHERIT(TextComp*,Select2Code,SheetProc,UIComponent);
	SHELLHERIT(TextComp*,DrawHiCode,SheetProc,UIComponent);
	TextComp*	SetBack(TextComp*		&X)	{X=this;		return(this);}
	TextComp*	SetBack(UIComponentPtr	&X)	{X=this;		return(this);}
	TextComp*	DataVal(TextRef t)
					{text=t;									return(this);}
//TempCode JIM 16Nov95 	TextBuild			MakeText()
//TempCode JIM 16Nov95 					{return(UIComponent::MakeText(text,value));}				
protected:

};

//------------------------------------------------------------------------------
//Author		Dave Whiteside
//Date			Wed 13 Sep 1995
//Modified	
//
//Description	A component with text in it.
//				If the local value is cahnged it will be written back on exit
//
//Inputs		
//------------------------------------------------------------------------------
class	TextWBComp	:public WriteBackComp
{
public:
	TextRef	*WBtext,text;
				TextWBComp(SWord X,SWord Y,SWord W,SWord H):
					WriteBackComp(X,Y,W,H)
					{WBtext=NULL;wbcode=(SheetProc) SheetBase::TextDefaultWBProc;}

 	SHELLHERITL(TextWBComp*,MousePos,(WinShiftDef x,WinShiftDef y),
							UIComponent,(x,y));
	SHELLHERIT(TextWBComp*,DrawCode,SheetProc,UIComponent);
	SHELLHERIT(TextWBComp*,SelectCode,SheetProc,UIComponent);
	SHELLHERIT(TextWBComp*,Select2Code,SheetProc,UIComponent);
	SHELLHERIT(TextWBComp*,DrawHiCode,SheetProc,UIComponent);
	TextWBComp*	SetBack(TextWBComp*		&X)	{X=this;		return(this);}
	TextWBComp*	SetBack(UIComponentPtr	&X)	{X=this;		return(this);}

	TextWBComp*	WriteCode(SheetProc d)
					{wbcode=d;									return(this);}
	TextWBComp*	DataVal(TextRef &t)
					{WBtext=&t;text=t;							return(this);}
//TempCode JIM 16Nov95 	TextBuild			MakeText()
//TempCode JIM 16Nov95 					{return(UIComponent::MakeText(text,value));}				
protected:

};

////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
//
//  More complex text modified components.
//	These components contain non-editable text and an integer
//	the integer may, or may not be writable
//
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
//Author		Dave Whiteside
//Date			Wed 13 Sep 1995
//Modified	
//
//Description	A component with an integer in it.
//				The value cannot be changed.
//
//Inputs		
//------------------------------------------------------------------------------
class	TextIntComp	:public IntComp
{
public:
	TextRef	textref;
				TextIntComp(SWord X,SWord Y,SWord W,SWord H):
					IntComp(X,Y,W,H)	{};
 	SHELLHERITL(TextIntComp*,MousePos,(WinShiftDef x,WinShiftDef y),
							UIComponent,(x,y));
	SHELLHERIT(TextIntComp*,DrawCode,SheetProc,UIComponent);
	SHELLHERIT(TextIntComp*,SelectCode,SheetProc,UIComponent);
	SHELLHERIT(TextIntComp*,Select2Code,SheetProc,UIComponent);
	SHELLHERIT(TextIntComp*,DrawHiCode,SheetProc,UIComponent);
	TextIntComp*	SetBack(TextIntComp*		&X)	{X=this;		return(this);}
	TextIntComp*	SetBack(UIComponentPtr		&X)	{X=this;		return(this);}
	TextIntComp*	DataVal(TextRef t,int i)
					{textref=t;IntComp::DataVal(i);				return(this);}
	TextBuild			MakeText()
					{return(UIComponent::MakeText(textref,value));}				
protected:

};

//------------------------------------------------------------------------------
//Author		Dave Whiteside
//Date			Wed 13 Sep 1995
//Modified	
//
//Description	A component with an integer reference in it.
//				The value should not be changed.
//				If the value is changed then the referenced value changes 
//				immediately
//
//Inputs		
//------------------------------------------------------------------------------
class	TextIntRefComp	:public IntRefComp
{
public:
	TextRef	textref;
				TextIntRefComp(SWord X,SWord Y,SWord W,SWord H):
					IntRefComp(X,Y,W,H)	{};
 	SHELLHERITL(TextIntRefComp*,MousePos,(WinShiftDef x,WinShiftDef y),
							UIComponent,(x,y));
	SHELLHERIT(TextIntRefComp*,DrawCode,SheetProc,UIComponent);
	SHELLHERIT(TextIntRefComp*,SelectCode,SheetProc,UIComponent);
	SHELLHERIT(TextIntRefComp*,Select2Code,SheetProc,UIComponent);
	SHELLHERIT(TextIntRefComp*,DrawHiCode,SheetProc,UIComponent);
	TextIntRefComp*	SetBack(TextIntRefComp*		&X)	{X=this;		return(this);}
	TextIntRefComp*	SetBack(UIComponentPtr		&X)	{X=this;		return(this);}
	TextIntRefComp*	DataVal(TextRef t,SLong	&i)
					{textref=t;IntRefComp::DataVal(i);			return(this);}
	TextBuild			MakeText()
					{return(UIComponent::MakeText(textref,*value));}				
protected:

};
	
//------------------------------------------------------------------------------
//Author		Dave Whiteside
//Date			Wed 13 Sep 1995
//Modified	
//
//Description	A component with an integer reference in it.
//				If the value is changed then it will be written back 
//				by a call to the procedure registered to WriteCode.
//				The default writeback simply copies the value.
//				
//Inputs		
//------------------------------------------------------------------------------
class	TextIntWBComp	:public IntWBComp
{
public:
	TextRef	textref;
				TextIntWBComp(SWord X,SWord Y,SWord W,SWord H):
					IntWBComp(X,Y,W,H)	{};
 	SHELLHERITL(TextIntWBComp*,MousePos,(WinShiftDef x,WinShiftDef y),
							UIComponent,(x,y));
	SHELLHERIT(TextIntWBComp*,DrawCode,SheetProc,UIComponent);
	SHELLHERIT(TextIntWBComp*,SelectCode,SheetProc,UIComponent);
	SHELLHERIT(TextIntWBComp*,Select2Code,SheetProc,UIComponent);
	SHELLHERIT(TextIntWBComp*,DrawHiCode,SheetProc,UIComponent);
	TextIntWBComp*	SetBack(TextIntWBComp*		&X)	{X=this;		return(this);}
	TextIntWBComp*	SetBack(UIComponentPtr		&X)	{X=this;		return(this);}
	TextIntWBComp*	DataVal(TextRef t,SLong	&i)
					{textref=t;IntWBComp::DataVal(i);			return(this);}
	TextBuild			MakeText()
					{return(UIComponent::MakeText(textref,value));}				
protected:

};

//------------------------------------------------------------------------------
//Author		Dave Whiteside
//Date			Wed 13 Sep 1995
//Modified	
//
//Description	A component with an integer reference in it.
//				A local copy of the value is kept in an external location!!!
//				Both locations are specified in DataVal
//				If the value is changed then it will be written back
//				by a call to the procedure registered to WriteCode.
//				The default writeback simply copies the value.
//
//Inputs		
//------------------------------------------------------------------------------
class	TextIntRefWBComp	:public IntRefWBComp
{
public:
	TextRef	textref;
				TextIntRefWBComp(SWord X,SWord Y,SWord W,SWord H,SLong &vloc):
					IntRefWBComp(X,Y,W,H,vloc){};
 	SHELLHERITL(TextIntRefWBComp*,MousePos,(WinShiftDef x,WinShiftDef y),
							UIComponent,(x,y));
	SHELLHERIT(TextIntRefWBComp*,DrawCode,SheetProc,UIComponent);
	SHELLHERIT(TextIntRefWBComp*,SelectCode,SheetProc,UIComponent);
	SHELLHERIT(TextIntRefWBComp*,Select2Code,SheetProc,UIComponent);
	SHELLHERIT(TextIntRefWBComp*,DrawHiCode,SheetProc,UIComponent);
	TextIntRefWBComp*	SetBack(TextIntRefWBComp*	&X)	{X=this;	return(this);}
	TextIntRefWBComp*	SetBack(UIComponentPtr		&X)	{X=this;	return(this);}
	TextIntRefWBComp*	DataVal(TextRef t,SLong	&glob)
					{textref=t;IntRefWBComp::DataVal(glob);		return(this);}
	TextBuild			MakeText()
					{return(UIComponent::MakeText(textref,value));}				
protected:

};

//------------------------------------------------------------------------------
//Author		//JIM 16Apr96
//Date			Wed 27 Mar 1996
//Modified	
//
//Description	This component is in a list.
//				It has an index field to the list 
//				and a VOID pointer to the list itself, if required
//				
//				
//Inputs		
//------------------------------------------------------------------------------
class	ListEltComp	:public NoDataComp
{
	friend	class	UIListDescComp;
public:
	enum	SCROLLENTRIES	{SCR_lineup,SCR_pageup,SCR_pickup,SCR_pagedn,SCR_linedn,
			SCROLLBARBOXSIZE=PIXEL640*14};
	int				value;
	void*		listdata;
	UIListDescComp*	listctrl;
	CON		ListEltComp(SWord X,SWord Y,SWord W,SWord H):
	   			NoDataComp(X,Y,W,H)
	   			{value=0;listdata=NULL;}
	CON		ListEltComp():
	   			NoDataComp()
	   			{value=0;listdata=NULL;}

 	SHELLHERITL(ListEltComp*,MousePos,(WinShiftDef x,WinShiftDef y),
							UIComponent,(x,y));
	SHELLHERIT(ListEltComp*,DrawCode,SheetProc,UIComponent);
	SHELLHERIT(ListEltComp*,SelectCode,SheetProc,UIComponent);
	SHELLHERIT(ListEltComp*,Select2Code,SheetProc,UIComponent);
	SHELLHERIT(ListEltComp*,DrawHiCode,SheetProc,UIComponent);
	SHELLHERIT(ListEltComp*,HilightCode,SheetProc,UIComponent);
	SHELLHERIT(ListEltComp*,DeHilightCode,SheetProc,UIComponent);

	ListEltComp*	SetBack(ListEltComp* &X)	{X=this;		return(this);}
	ListEltComp*	SetBack(UIComponentPtr &X)	{X=this;			return(this);}
	ListEltComp*	DataVal(int Value,void* Listdata,UIListDescComp* Listctrl)
				{value=Value;listdata=Listdata;listctrl=Listctrl;	return(this);}
protected:

};


//------------------------------------------------------------------------------
class	UIListDescComp:public ListEltComp
{
	friend	class	ListEltComp;
public:
//the following fields should be filled by the caller
	ScreenWH	nextcomppos;	//nextcomp can equal 0,height

	int			//total len is specified in value field of ListComp
				winlen,			//default is 10
				topnum,			//default to zero
				currnum;		//this is the returned value - default zero

	//the following fields are filled automatically
	ListEltComp		**refreshcomps,
					**scrollbarcomps;
///////////////////

	~UIListDescComp()		//this destructor is a problem....
	{delete [] refreshcomps;delete [] scrollbarcomps;}
	UIListDescComp():
		ListEltComp(),
		nextcomppos(0,0)
	{refreshcomps=scrollbarcomps=NULL;listctrl=this;}
	void Coords(int x,int y,int w,int h)
		{xy.x=x;xy.y=y;wh.w=w;wh.h=h;}
 	SHELLHERITL(UIListDescComp*,MousePos,(WinShiftDef x,WinShiftDef y),
							UIComponent,(x,y));
	SHELLHERIT(UIListDescComp*,DrawCode,SheetProc,UIComponent);
	SHELLHERIT(UIListDescComp*,SelectCode,SheetProc,UIComponent);
	SHELLHERIT(UIListDescComp*,Select2Code,SheetProc,UIComponent);
	SHELLHERIT(UIListDescComp*,DrawHiCode,SheetProc,UIComponent);
	SHELLHERIT(UIListDescComp*,HilightCode,SheetProc,UIComponent);
	SHELLHERIT(UIListDescComp*,DeHilightCode,SheetProc,UIComponent);

	UIListDescComp*	DeltaXY(int w,int h)	{nextcomppos.w=w;nextcomppos.h=h;return(this);}

	UIListDescComp*	SetBack(UIListDescComp*		&X)	{X=this;		return(this);}
	UIListDescComp*	SetBack(UIComponentPtr	&X)	{X=this;		return(this);}
	UIListDescComp*	DataVal(UISheet* This,int listlen,void* ListData,int winlen=10,int topnum=0,int currnum=0);


};



inline	void	SheetBase::IntDefaultWBProc		(SheetBase *,IntWBComp& UIC)			{UIC.wbref[0]=UIC.value;}
inline	void	SheetBase::IntRefDefaultWBProc		(SheetBase *,IntRefWBComp& UIC)		{UIC.wbref[0]=UIC.value;}
inline	void	SheetBase::TextDefaultWBProc		(SheetBase *,TextWBComp& UIC)			{UIC.WBtext[0]=UIC.text;}
inline	void	SheetBase::TextIntDefaultWBProc	(SheetBase *,TextIntWBComp& UIC)		{UIC.wbref[0]=UIC.value;}
inline	void	SheetBase::TextIntRefDefaultWBProc	(SheetBase *,TextIntRefWBComp& UIC)	{UIC.wbref[0]=UIC.value;}

//DeadCode RDH 18Jan96 const 	SWord													//RDH 07Dec95
//DeadCode RDH 18Jan96 		PIXEL640 	=	40;										//RDH 07Dec95



#endif

