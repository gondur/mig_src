//
//MODULE:	stub3d.cpp
//
//TASK:		manages the 3d thread
//
//ROUTINES:	presently about 5 routines:
//
//	MakeInteractive(WinMode,Coords)
//	WinMode(WinMode,Coords)
//	MakeResize(WinMode,Coords)
//	ToggleInteractive(bool)
//	TogglePaused(bool)
//	ToggleAccel(bool)
//	DeleteWorld()
//	
//	WinMode:	
//		FullScreen/Windowed/DualScreen 
//							0x0000,0x1000,0x2000
//		Accelerated			0x000=no,0x100=yes,
//							0x10n=specific card									
//							0x1m0=specific mode

#ifndef	STUB3d_defined
inline	int	LockExchange(int* loc,int newval=0)
{
	int rv;
    #ifndef    __BCPLUSPLUS__
	_asm	{	mov		eax,newval
				mov		ebx,loc
				xchg	ds:[ebx],eax
				mov		rv,eax
			}
    #else
    rv=0; 
    #endif
	return	rv;
}
#define STUB3d_defined

class	WorldStuff;
class	WorldRef
{
	WorldStuff* w;
public:
	WorldStuff*  operator=(WorldStuff* W)	{return w=W;}
	operator	WorldStuff&	()				{return *w;}	
	WorldStuff*	operator	&	()			{return w;}
	operator	WorldStuff*	()				{return w;}
};

struct	WinMode
{
	enum	Mode	{
		NONE=-1,
		FULL=0x0000,WIN=0x1000,DUAL=0x2000,
		SOFT=0x000,HARD=0x100,
		H_PRIM=0x101,H_SEC=0x102,H_TIRT=0x103,
		H_8P=0x110,H_8F=0x120,
		H_12_16=0x140,H_15_16=0x150,H_16=0x160,
		H_24=0x180,
		H_24_32=0x1C0,H_30_32=0x1D0,H_32=0x1E0
	};
	enum	Mask	{DISP=0xf000,HW=0x0f00,SLOT=0x01f0,DEPTH=0x010f};
};
inline WinMode::Mode operator | (WinMode::Mode a,WinMode::Mode b)
{return WinMode::Mode(int(a)|int(b));}
inline WinMode::Mode operator + (WinMode::Mode a,WinMode::Mode b)
{return a|b;}
inline WinMode::Mode operator & (WinMode::Mode a,WinMode::Mask b)
{return WinMode::Mode(int(a)&int(b));}
inline WinMode::Mode operator & (WinMode::Mask a,WinMode::Mode b)
{return WinMode::Mode(int(a)&int(b));}
class	View3d;
struct	KeyMap3d;
class	CEvent;
class	Display;
#ifdef UNICODE
#define IID_IDirectInputDevice IID_IDirectInputDeviceW
#define IDirectInputDevice IDirectInputDeviceW
#define IDirectInputDeviceVtbl IDirectInputDeviceWVtbl
#else
#define IID_IDirectInputDevice IID_IDirectInputDeviceA
#define IDirectInputDevice IDirectInputDeviceA
#define IDirectInputDeviceVtbl IDirectInputDeviceAVtbl
#endif
typedef struct IDirectInput *LPDIRECTINPUT;
typedef struct IDirectInputDevice *LPDIRECTINPUTDEVICE;
struct	LiveList;

class	Inst3d;

#ifdef NDEBUG
   #define	NDEBUGSTACKS
#endif
	
struct	LogStack
{
	enum	FrameType	{CHECKALL,MESSAGELOOP,THREEDEE,INTERRUPT,MOVECODE,MAX_STACKS};
	int	stacks[10][2];
	FrameType	dontcheck;

	//Log the address of a stack. The address of the parameters defines the stack address
	void	Log(FrameType frametype,int knownsize=0)
	#ifdef	NDEBUGSTACKS
	{}
	#else
	{
		stacks[frametype][0]=(int)&frametype;
		stacks[frametype][1]=knownsize;
	}
	#endif

	//Forget the address of a stack. Lets check it is still valid, though!
	void	UnLog(FrameType frametype)
	#ifdef	NDEBUGSTACKS
	{}
	#else
	{
		if (stacks[frametype][0])
			Check(frametype);
		stacks[frametype][0]=0;
		stacks[frametype][1]=0;
	}
	#endif

	//Disable checking for specific stack
	void	DontCheck(FrameType dc=CHECKALL)
	#ifdef	NDEBUGSTACKS
	{}
	#else
	{
		dontcheck=dc;
	}
	#endif

	//Check if current stack is as expected
	//If higher address then obviously bad. 
	//If the stacks size is known then that can be checked.
	//If not then just check for overlapping stack.
	void	Check(FrameType frametype)
	#ifdef	NDEBUGSTACKS
	{}
	#else
	{
		if (dontcheck==frametype)
			return;
		int	addr=(int)&frametype;
		if (addr>=stacks[frametype][0])
			INT3
		else
			if (stacks[frametype][1])
				if (addr<stacks[frametype][0]-stacks[frametype][1])
					INT3
				else
					;
			else
				for (int i=0;i<MAX_STACKS;i++)
					if (addr<stacks[i][0] && stacks[frametype][0]>stacks[i][0])
						INT3
	}
	#endif
};
extern	LogStack	Log_Stack;

class	Mast3d
#ifdef	DECLARE_HANDLE

{
#ifndef	_WINDEF_
#define	HINSTANCE	HWND
#endif

#ifdef	__AFXMT_H__

static void CALLBACK StaticTimeProc(UINT uID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2 ); 

void TimeProc(UINT uID, UINT uMsg, DWORD dw1, DWORD dw2 ); 
#endif
	friend	class	fileman;
	friend	class	CMIGApp;
	friend	class	View3d;
	friend	class	Inst3d;
	friend	class	DPlay;

	enum	{EVENT_KEYS=0,EVENT_MOUSE,EVENT_AGGREGATOR,NUM_EVENTS=3};
	HANDLE				htable[NUM_EVENTS];
	HINSTANCE			hinst;
	int				uTimerID;
	int				wTimerRes;
	int				ticknum;
//DEADCODE DAW 10/02/00 	int				loopticks;
public:
	HWND				winst;
	LPDIRECTINPUT		g_lpDI; 
	LPDIRECTINPUTDEVICE	g_lpDIDevice;
	Inst3d*	currinst;
	Mast3d();
	void	Init(HINSTANCE			hinst,HWND				hwind);
	~Mast3d();
	void	MainInit(void);
	void	QuitGame(void );
	void	Stop();
	void	SmallWin();
	void	BigWin();
	
}
#endif
;
extern	Mast3d	Master_3d;
class	CWinThread;


class	Inst3d
{	//master control for ongoing 3d world instances
	friend	class	CMIGApp;
	friend	class	View3d;
	friend	class	Mast3d;
	friend	class	Replay;
	friend	class	Persons2;
	friend	class	Persons3;
	friend	class	DPlay;

	enum {
		MAX_ACCEL_FRAME=100,
#ifndef	NDEBUG
		MAX_NORMAL_FRAME=7
#else
		MAX_NORMAL_FRAME=25
#endif
	};
	CWinThread*	movethread;
	static unsigned int moveloop(void*);
	int	accelframes;
	bool		accel,paused,interactive;
	View3d*		viewedwin;
	Inst3d*		nextinst;
	volatile bool	insidetimer;
//	static char		lastkeys[256];
	static	KeyMap3d*	commonkeymaps;
	WorldRef	world;
	LiveList*	livelist;
//DEADCODE DAW 17/02/00 	int		blocktick,blockticks;
	void	Inst3d::BlockTick(Bool setit);
	bool	mapview;
	int		timeofday;
	volatile int	framecount;

public:
#ifdef DECLARE_HANDLE
	HANDLE			semaphore;
	HANDLE			mutex;
#endif

	Inst3d();
	Inst3d(bool);
	~Inst3d();
	View3d* Interactive(View3d* newwin);
	bool Paused(bool newmode);
	bool Accel(bool newmode);
	View3d* Drawing(View3d* newwin);	
	View3d* Interactive();
	bool Paused();					
	bool Accel();					
	View3d* Drawing();
	static	bool	InThe3D();//	{return !currinst->Paused();}
	static	void	ReleaseDirectX();
	static	void	RestoreDirectX();

void	DoMoveCycle();
//DeadCode AMM 12May99 void	MoveCycle(int timeofday,WorldStuff* worldref);
void	MoveCycle(WorldStuff* worldref);						//AMM 11May99

//DeadCode AMM 06Oct98 void	SkipCycles(ULong num);									//AMM 16Sep98


	static void	OnKeyDown(int key);
	static void	OnKeyUp(int key);
private:
	static void OnKeyInput();
};
class	RDialog;
class	ViewPoint;
#ifdef __AFXWIN_H__
class	View3d
{
	friend	class	CMIGApp;
	friend	class	Inst3d;
	friend	class	Mast3d;

	typedef	WinMode::Mode	WinMode;
 	ViewPoint*	View_Point;
	HWND		window;
	CWnd*	mfcwin;
	CRect		coords;
	WinMode		mode;
	Inst3d*		inst;
	View3d*		nextview;
	CEvent*		E;
	KeyMap3d*	keymap;
	Display*	Whole_Screen;
	enum	DrawState {D_NO=0,D_YES,D_SWITCH,D_CLOSE}
			drawing;
	static UINT AFX_CDECL drawloop(LPVOID);
	void	SetEndDraw(DrawState d);
	int		doneframe,frametime,lastframetime,timeSinceLastMove;
	int		realframetime,lastrealframetime;
	int		waitforframecount;
	void	DoneFrame();
	void	CloseWindow(const ULong id=IDOK);
public:
	void	BlockTick(Bool setit);
	int	PeekFrameTime();
	int	LastFrameTime();
	int	RealFrameTime()	{return lastrealframetime;}
	int TimeSinceLastMove();
	int TimeOfDay()		{return inst->timeofday;}
	void SetTimeOfDay(int time) {inst->timeofday=time;}			//AMM 12May99
	int	MakeInteractive	(WinMode	v=WinMode::FULL,const CRect& pos=*(CRect*)NULL,bool flag=false,bool flag2=false);
	int	MakePassive		(WinMode	v=WinMode::FULL,const CRect& pos=*(CRect*)NULL,bool flag=false,bool flag2=false);
	int	MakeResize		(WinMode	v=WinMode::FULL,const CRect& pos=*(CRect*)NULL);
	bool Interactive(bool newmode)	
	{	return (this==inst->Interactive(
						newmode	?this
								:(inst->viewedwin==this)	
									?NULL
									:inst->viewedwin));
	}
	bool Paused(bool newmode)		{return inst->Paused(newmode);}
	bool Accel(bool newmode)		{return inst->Accel(newmode);}
	bool Drawing(bool newmode);	
	bool Interactive()				{return (this==inst->Interactive());}
	bool Paused()					{return inst->Paused();}     
	bool Accel()					{return inst->Accel();}      
	bool Drawing()					{return drawing==D_YES;}


	int	WaitEndDraw(DrawState d,int timeoutmilisec=INFINITE);

	bool InThe3D()	{return Drawing();}

//DeadCode AMM 06Oct98 	void	SkipCycles(ULong num);								//AMM 16Sep98

	View3d(Inst3d* i,HWND,CWnd*); 	
	~View3d();
};
#endif




#endif
