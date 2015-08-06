#pragma crap
//DeadCode JIM 12Dec95 //------------------------------------------------------------------------------
//DeadCode JIM 12Dec95 //Filename       wrapper.h
//DeadCode JIM 12Dec95 //System         
//DeadCode JIM 12Dec95 //Author         Paul.   
//DeadCode JIM 12Dec95 //Date           Tue 4 Jul 1995
//DeadCode JIM 12Dec95 //Description    
//DeadCode JIM 12Dec95 //------------------------------------------------------------------------------
//DeadCode JIM 12Dec95 #ifndef	wrapper_Included
//DeadCode JIM 12Dec95 #define	wrapper_Included
//DeadCode JIM 12Dec95 
//DeadCode JIM 12Dec95 #include	"files.g"
//DeadCode JIM 12Dec95 #include	"3DDefs.h"
//DeadCode JIM 12Dec95 #include	"Palette.h"
//DeadCode JIM 12Dec95 #include	"Worldinc.h"
//DeadCode JIM 12Dec95 
//DeadCode JIM 12Dec95 //DeadCode DAW 28Nov95 extern
//DeadCode JIM 12Dec95 class	Wrapper 												//PD 29Nov95
//DeadCode JIM 12Dec95 {
//DeadCode JIM 12Dec95 
//DeadCode JIM 12Dec95 	public:
//DeadCode JIM 12Dec95 
//DeadCode JIM 12Dec95 		SCANLINETYPE		horiline;
//DeadCode JIM 12Dec95 
//DeadCode JIM 12Dec95 		short	Init(ScreenRecord *,MODE );
//DeadCode JIM 12Dec95 
//DeadCode JIM 12Dec95 		void	ClearScreen(ScreenRecord *,COLOUR );
//DeadCode JIM 12Dec95 
//DeadCode JIM 12Dec95 		void 	GetFontInfo(ScreenRecord *, short&, short& ,short&);
//DeadCode JIM 12Dec95 
//DeadCode JIM 12Dec95 		short	GetCharacterWidth(ScreenRecord *, short);
//DeadCode JIM 12Dec95 
//DeadCode JIM 12Dec95 		short	RegisterFontActive(ScreenRecord *, FileNum, short&, short&, short&);
//DeadCode JIM 12Dec95 
//DeadCode JIM 12Dec95 		void 	GetPixelInfo(void );
//DeadCode JIM 12Dec95 
//DeadCode JIM 12Dec95 		void 	SetColour(COLOUR );
//DeadCode JIM 12Dec95 		void 	SetColour(COLOUR ,COLOUR_RANGE);
//DeadCode JIM 12Dec95 		void 	SetColour(ImageMapNumber);
//DeadCode JIM 12Dec95 
//DeadCode JIM 12Dec95 		void 	ClipPolygon(void );
//DeadCode JIM 12Dec95 
//DeadCode JIM 12Dec95 		ScreenRecord *CloneWindow(ScreenRecord *);
//DeadCode JIM 12Dec95 
//DeadCode JIM 12Dec95 		void 	DestroyWindow(ScreenRecord *);
//DeadCode JIM 12Dec95 
//DeadCode JIM 12Dec95 		void 	MouseRedraw(void );
//DeadCode JIM 12Dec95 
//DeadCode JIM 12Dec95 		void 	GetCharPos(ScreenRecord *, short&, short&);
//DeadCode JIM 12Dec95 		short 	GetCharPos(ScreenRecord *);	//returns X					//JIM 15Nov95
//DeadCode JIM 12Dec95 
//DeadCode JIM 12Dec95 		void 	SetCharPos(ScreenRecord *, short, short);
//DeadCode JIM 12Dec95 
//DeadCode JIM 12Dec95 		void 	ScreenSwap(ScreenRecord *);
//DeadCode JIM 12Dec95 
//DeadCode JIM 12Dec95 		void 	SetTextMode(void );
//DeadCode JIM 12Dec95 
//DeadCode JIM 12Dec95 		void	ShowPic(ScreenRecord *, FileNum );
//DeadCode JIM 12Dec95 
//DeadCode JIM 12Dec95 		short	CharacterPrint(ScreenRecord *, short);
//DeadCode JIM 12Dec95 
//DeadCode JIM 12Dec95 		void	PlainLine(ScreenRecord *,SLong X1,SLong Y1,SLong X2,SLong Y2);
//DeadCode JIM 12Dec95 
//DeadCode JIM 12Dec95 		void	ClipLine(ScreenRecord *,SLong X1,SLong Y1,SLong X2,SLong Y2);
//DeadCode JIM 12Dec95 
//DeadCode JIM 12Dec95 		void	PlainCircle(ScreenRecord *,SLong R,SLong X,SLong Y);
//DeadCode JIM 12Dec95 
//DeadCode JIM 12Dec95 		COLOUR	PlotLogicalPixel(ScreenRecord *,SWord, SWord);
//DeadCode JIM 12Dec95 
//DeadCode JIM 12Dec95 		void	GetRealSxy(SLong &, SLong &);
//DeadCode JIM 12Dec95 
//DeadCode JIM 12Dec95 		//Horizontal scan line routines for polygon drawing go here//PD 30Oct95
//DeadCode JIM 12Dec95 
//DeadCode JIM 12Dec95  		void	setscanline(SCANLINETYPE );						//PD 03Nov95
//DeadCode JIM 12Dec95 		void	HoriLine(UByte *, VERTEX &, VERTEX &);			//PD 03Nov95
//DeadCode JIM 12Dec95 
//DeadCode JIM 12Dec95 		void	MakeIntensityData(void );
//DeadCode JIM 12Dec95 
//DeadCode JIM 12Dec95 //DeadCode PD 03Nov95 		void	cpolyhoriline(UByte *, VERTEX &, VERTEX &);		//PD 30Oct95
//DeadCode JIM 12Dec95 //DeadCode PD 03Nov95 		void	gpolyhoriline(UByte *, VERTEX &, VERTEX &);		//PD 30Oct95
//DeadCode JIM 12Dec95 //DeadCode PD 03Nov95 		void	ipolyhoriline(UByte *, VERTEX &, VERTEX &);		//PD 30Oct95
//DeadCode JIM 12Dec95 //DeadCode PD 03Nov95 		void	ipolyhorilinem(UByte *, VERTEX &, VERTEX &);	//PD 30Oct95
//DeadCode JIM 12Dec95 
//DeadCode JIM 12Dec95 	private:
//DeadCode JIM 12Dec95 
//DeadCode JIM 12Dec95 		short	PlotPhysicalPixel(ScreenRecord *,short, short, short);
//DeadCode JIM 12Dec95 
//DeadCode JIM 12Dec95 	protected:	
//DeadCode JIM 12Dec95 
//DeadCode JIM 12Dec95 };
//DeadCode JIM 12Dec95 
//DeadCode JIM 12Dec95 	extern	class	Wrapper	Wrapper_;							//PD 29Nov95
//DeadCode JIM 12Dec95 
//DeadCode JIM 12Dec95 #endif
#include	"display.h"
