//------------------------------------------------------------------------------
//Filename       display.h
//System         
//Author         Jim Taylor
//Date           Tue 12 Dec 1995
//Description    Hierachy of 3 physical realities:
//					Graphic:	Low level graphics interface
//					Window:		Public high level graphics interface
//					Display:	Low level physical interface
//
//
//------------------------------------------------------------------------------
#ifndef	DISPLAY_Included
#define	DISPLAY_Included

#define	DEFAULT_DISPLAY 0
 
#define MAXCMODES 60											//ARM 26Nov96
//------------------------------------------------------------------------------
class	Window;
//------------------------------------------------------------------------------

#include	"dosdefs.h"
#include	"files.g"
struct Vertex;
#include	"3ddefs.h"
#include	"palette.h"

#include	"myangles.h"

struct	CharSizeEntry;
struct	CharTableEntry;
typedef	CharTableEntry	*CharTableEntryPtr;
struct	FontStructInfo;
typedef	struct	Font *FontPtr;;
class ViewPoint;

struct	SmackTag;
typedef	SmackTag Smack;													//ARM 02Aug96

#define	NORMAL_RHW		0
#define	FORCE_FAR_RHW	1
#define FORCE_NEAR_RHW	2

struct SDrvrModes
{
	int driverNo;
	int displayWidth;
	int displayHeight;
	int displayBPP;
};

struct ROWANSURFACEDESC
{
	void	*lpSurface;
	ULong	dwWidth,
			dwHeight,
			lPitch,
			dwRGBBitCount;
};

struct	ImageMap_Desc;											//PD 05Dec95
typedef	UWord	IntensityIndex[16][32];							//PD 08Nov95
typedef	UByte*	LogicalPtr;
typedef	ULong*	LogicalLPtr;

typedef struct ScreenRez										//PD 04Feb97
{
	SWord	width;
	SWord	colourdepth;
	SWord	driver;												//PD 22May97
}
ScreenRez;

struct IFFHunkSearch
{
	ULong searchVal;
	UByte* hunkPtr;
};

//------------------------------------------------------------------------------
struct OutCode 
{
	unsigned all;
	unsigned left:4;
	unsigned right:4;
	unsigned bottom:4;
	unsigned top:4;
};

typedef OutCode outcode;

struct ZOutCode
{
	unsigned all;
	unsigned behind:4;
};

//------------------------------------------------------------------------------
//
// All output to the logical screen
//
//
//------------------------------------------------------------------------------
struct	ImageMap_Desc;						//RJS 06Feb98
class	Graphic;
class	Display;
class	Graphic
{
private:
	static Bool	locked;												//AMM 01May97
	static UByte	locklevel;											//AMM 01May97

	enum	ScreenPages	{SCREEN_PHYSICAL=-1,SCREEN_SPARE=+1,SCREEN_LOGICAL=0};
	//-------------------------------------------------------
	//3 mouse areas are required in 3 screen system.
	//2 areas (X,Y) are needed to swap the existing mouse position
	//an 3rd area is needed to hold the spare screen mouse position
	//If w/h = 0 then no data to restore
	//
	//
//FIX10-2	struct	MouseSave	//specifies data to restore
//FIX10-2	{
//FIX10-2		MouseSave*	Info;
//FIX10-2		ScreenXY	XY;
//FIX10-2		ScreenWH	WH;
//FIX10-2		UWord		datasize;	//fixed by source pointer image type
//FIX10-2		char		smallarea[2];
//FIX10-2		char*		dataptr;
//FIX10-2		MouseSave()	{Info=this;datasize=0;dataptr=0;WH.w=0;WH.h=0;}
//FIX10-2	};			 d

	friend	struct	ImageMap_Desc;					//RJS 06Feb98
	friend	class	Display;
	friend	class	Window;
	friend	class	ScreenResSheet;
protected:
	enum	{SHADECOLOURMAX=32,RANGE_SHIFT_FACTOR=3,RANGE_MASK=0x001F};

	LogicalPtr
			logicalscreenptr;	//this may become a FAR!!!
	Graphic	*master,
			*windowlink;
	Display*	Master()	{return	(Display*) master;}			//JIM 19Jan98
	short	BytesPerPixel;

	//Screen RGB format info for non-8bpp modes					//RDH 16Oct97

	short	RedBits,RedShift;									//RDH 16Oct97
	short	GreenBits,GreenShift;								//RDH 16Oct97
	short	BlueBits,BlueShift;									//RDH 16Oct97

	short	BytesPerScanLine;
	short	PhysicalMinX;
	short	PhysicalWidth;		//Width of screen in pixels
	short	PhysicalMaxX;		//Width of screen in pixels
	short	PhysicalMinY;
	short	PhysicalHeight;		//Width of screen in pixels
	short	PhysicalMaxY;		//Height of screen in pixels
	Smack* 	currsmk;
	static UByte	Graphic::ExpandBuff[256][8];
	static SLong	fontcolour;

	Colour			colour;
	ColourRange		range;
	Colour			glasscolour;								//PD 02Apr96
	FontPtr&	fontptr;			//Current font description
	FontPtr&	mousefontptr;			//Current font description
	short	CharX,CharY;

	//The following are references to the Display instance
	UByte *		imageptr;										//DAW 18Dec95
	Colour			*shadetable;	//[SHADECOLOURMAX];

	IntensityIndex&	intensityindex;
public:
	Bool&			UseNewPal;
	void*	&Palette;			//Let's attempt to spell this correctly
protected:
	SLong	image_x_mask,									//PD 05Dec95
			image_y_mask,									//PD 05Dec95
			image_y_shift;									//PD 05Dec95

//-------------------------------------------------------
protected:
	CON		Graphic(Bool& unp,IntensityIndex*	ii,void*& pal,FontPtr& fp,FontPtr& mp);

//-------------------------------------------------------
protected:
	void	SetPixelWidth(SWord& );								//PD 03Jan96
	void*	GetPaletteTable();
	void	SelectPalette(SWord);
	UWord	GetPaletteEntry(UWord);
	void	SetPaletteEntry(UWord,UWord);
	void*	GetLandFadeTable();
	void*	GetSkyFadeTable();
	void*	GetHorizonFadeTable();
	void	SetTransparency(SWord );							//PD 02Apr96
	void	SetLuminosity(SWord );								//RJS 19Jan98
	void	SetHeatHaze(SWord );								//RJS 30Jan98
	HoriLineRtnPtr	GetScanLineAddr(SCANLINETYPE );				//PD 03Jan96
	void	SetFadeData(SLong );								//PD 24Jun96
	void	SetGrey3DType(GREY3DTYPE&);							//PD 07Jan96
	void	SetFaded3DType(GREY3DTYPE&);						//PD 21Jun96
	void    SetColour(Colour);
	void	SetColour(ROWANSURFACEDESC*);
	void    SetColour(Colour,ColourRange);
	void	SetGlassRange(Colour);								//PD 02Apr96
	ULong	TranslateColour(Colour);

	void    ClearScreen		();
	void	CirclePoints	(short,short,short);
	void    PlainCircle		(short,short,short);

	void	TransparentBlob (SWord,SWord,SWord,SWord,SWord);	//RJS 05Nov97
	void 	FuzzyLine		(SWord,SWord,SWord,SWord,SWord,SWord);//RJS 05Nov97
	void 	FuzzyLine2		(SWord,SWord,SWord,SWord,SWord,SWord);//RJS 06Nov97
	void    PlainLineTransparent(SWord,SWord,SWord,SWord,SWord);//RJS 13Jan98
	void    PlainLine		(short,short,short,short);
	void    PlainLine16		(short,short,short,short);			//PD 28May97
	void	ClipLine		(SWord,SWord,SWord,SWord);
	void	ClipLine3D		(SLong,SLong,SLong,SLong,SWord,SWord);
	void	ClipLine3D		(Float,Float,Float,Float,SWord,SWord);//RJS 25Feb97
	void    RegisterPalette	( UByte *, SLong);
	void	ReinitDisplay();									//PD 03Jul97
	void    PlainCircleFill	();
	UWord	PlainRectangleFill(SWord,SWord,SWord,SWord);
	UWord	GlassRectangleFill(SWord,SWord,SWord,SWord);		//PD 02Apr96
	UWord	AilRectangleFill(SWord,SWord,SWord,SWord);			//PD 21Jun96
	void    PlainPolygonFill();
	Colour	PlotPixel(SWord, SWord, Colour colour);
	void    PlotPixelNoClip(short, short, short colour);
	Colour	PlotPixel(SWord, SWord);
	void    PlotPixelNoClip(short, short);
	void    ShowPic(UByte *);
	void	ShowPicScaled(UByte *buffer,const int scale);
	UWord	DoSmack(Smack* smk, UWord yoff);
	UWord	SmackLoad(Smack* smk);
	void    RegisterPaletteSmk(Smack* smk);
	Bool	CopyP2L(SWord x,SWord Y,SWord W,SWord H);

	short   PrintMonoBMP	(CharTableEntryPtr);
	short   PrintMonoRUN	(CharTableEntryPtr);
	short   PrintShade		(CharTableEntryPtr);
	short   PrintColour		(CharTableEntryPtr);
	outcode	CompOutCode		(short,short);
	outcode	Comp3DOutCode	(SLong,SLong);
	short   PlaneHoriLine	(short, short, short);

	//Horizontal scan line routines for polygon drawing go here//PD 30Oct95

	void	MakeIntensityData();						//PD 08Nov95
	void 	FillIntensityTable(UByte,UByte );
	void	zclipline(DoPointStruc&,DoPointStruc&);				//RJS 23Jun97

	void	FillPalFxTable(void );								//PD 05Jan96
protected:

	void	Graphic::FillExpandBuff();
	void	PlotAndSaveMouseScanline(SWord	x, SWord	y, SWord	w, UByte	*&oldpos, UByte	*&newpos);
	void	PlotMouseScanline(SWord	x, SWord	y, SWord	w, UByte	*&pos);

private:
	void	PalFontTables();
	void	SetFontTables();
	UByte	*UnpackRow		(UByte *,SLong width, SLong x, SLong y, SLong minx, SLong maxx);
	UByte	*Unpack2Row		(UByte *,SLong width, SLong x, SLong y, SLong minx, SLong maxx);
	UByte	*Unpack3Row		(UByte *,SLong width, SLong x, SLong y, SLong minx, SLong maxx);
	UByte	*Unpack4Row		(UByte *,SLong width, SLong x, SLong y, SLong minx, SLong maxx);
	UByte	*Unpack8Row		(UByte *,SLong width, SLong x, SLong y, SLong minx, SLong maxx);
	UByte	*UnpackShadeRow	(UByte *,SLong width, SLong x, SLong y, SLong minx, SLong maxx);
	UByte	*UnpackSmoothRow	(UByte *,SLong width, SLong x, SLong y, SLong minx, SLong maxx);

	Colour 	MapColourToBase	(UByte,UByte,UByte,Colour );
	ZOutCode CompZOutCode	(SLong,SLong);

	inline	UByte	*makemapindex(SLong ix, SLong iy)
					{return(imageptr + ((ix&image_x_mask)>>16) + ((iy&image_y_mask)>>image_y_shift));};//PD 19Dec95

	inline	UByte	makecolindex(SLong intensity)
					{return	(UByte)(  ( intensity >> (16+(int)RANGE_SHIFT_FACTOR) )  &  (int)RANGE_MASK  );};

	void	PrintIcon(int x,int y,int iconnum,CharTableEntryPtr cptr);

//-------------------------------------------------------
//These functions are not libraried
//
public:
	int		iffartnum;
private:
	int		ifflinenum;
	int		iffoffset;
	void	ScreenShot();
	void	ScreenShot16();
static	UByte	*SearchIFFHunk	(UByte *,UByte *);
static	UByte	*ReadWord		(UByte *, SWord &);
static	UByte	*ReadLong		(UByte *, SLong &);
static	UByte	*SkipRow		(UByte *, SWord);
static	SLong	SearchIFFHunks	(SLong,IFFHunkSearch*,UByte*);
protected:
	void    SetColour(ImageMap_Desc*);
};
//-------------------------------------------------------
//
//
//
//
//-------------------------------------------------------
struct	InitDisplayDef		//used to change mode
{
	SLong	width;			//This is what the customer sets
	SLong	height;			//we do the rest
	SWord	colourdepth;	
	SWord	driver;												//PD 22May97
};

struct	InitWindowDef		//used to make a window
{
	SLong	VirtualMinX;		//these should never be>word
	SLong	VirtualWidth;		//note that these virtual mins and sizes
	SLong	VirtualMinY;		//must be proportional to 
	SLong	VirtualHeight;		//physical mins and sizes so zero is in same place
	CON	InitWindowDef(SLong X,SLong Y,SLong W,SLong H)
	{
		VirtualMinX=X;
		VirtualMinY=Y;
		VirtualWidth=W;
		VirtualHeight=H;
	};
};
enum	WinShiftDef	{WINSH_SAME,WINSH_MIN,WINSH_MID,WINSH_MAX,WINSH_ALIGN=65535};
//-------------------------------------------------------
//
// Translation between colour space and virtual resolution
//
//
//-------------------------------------------------------

class	Window:public	Graphic
{
	friend	class	shape;
	friend	class	polygon;
	friend	class	matrix;
	friend	class	Land_Stream;
	friend  class	ThreeDee;
public:
	Bool	DoSetPlayerTextures(Bool B);
 	Bool	DoSetZUpdate(Bool B);
	Bool	DoHardLine(LPLINETYPE L);
	Bool	DoingHardware3D();
	Bool	DoHardPoint(LPPOINTTYPE L);
	Bool	DoEnableBackClip(Bool);
	void	DoSetFade(Colour trgCol,SLong step,TwoDeeEffect tdfx);
	void	HCls(Bool);
	void	DoSetFadeValue(UByte);
	void	DoSetFogState(Bool);
	Bool	DoSetMatrices(SLong,ANGLES);
	void	DoSetFog(UByte,UByte,UByte,SLong,SLong);
	void	DoSetFog(UByte,UByte,UByte);
	void	DoGetFog(UByte&,UByte&,UByte&,SLong&,SLong&);
	void	DoSetViewParams(ANGLES,Window*,ViewPoint*);
	void	DoBeginScene();
	void	BeginScene();
	void LockBackScreen(Bool winmov,UByte low, UByte high);
//DEAD 	void UnLockBackScreen(UByte low, UByte high);
	void	EndScene();
	void	End3DScene();
	Bool	DoHardPoly(LPPOLYTYPE);
	void	DoPushViewData();
	void	DoPopViewData();
	void	DoSet3DWin(SLong x,SLong y,SLong w,SLong h);
	bool	DoScanForBottomPixelsOfText(SWord,SWord,SWord);
	void	DoPushPull(UByte);
	void	DoMakePaletteFadeTable(UByte*,UWord*,UByte,UByte,UByte);
	void	DoMakeColourRangeFadeTable(UWord*,UByte,UByte,UByte,UByte,UByte,UByte);
	void	DoGetColourInfo(UWord&,SWord&,SWord&,UWord&,SWord&,SWord&,UWord&,SWord&,SWord&);
	void	DoLockScr(ROWANSURFACEDESC*);
	void	DoUnlockScr(ROWANSURFACEDESC*);
	void	DoPutLine(SWord,SWord,SWord,SWord,Colour);
	void	DoScreenSwap();
	void	DoShowLoaderArt(void*);
	void	DoCaptureScreen();
	void	DoSaveVideoBuffer();
	void	DoGammaCorr(UByte& r,UByte& g,UByte& b);
	bool	DoSetEdgeTest(bool);
	void	DoSetSunPos(DoPointStruc&);
	void	DoBody2Screen(DoPointStruc&);
	bool	DoSetMipMap(bool);
	void	DoPeripheralBlob(Float*,Float*,Float*,UByte,SLong);
	void	DoSetFontColour(ULong );
	void	DoGetSurfaceDimensions(SLong&,SLong&);
	void	DoPutC(ImageMapDesc*,DoPointStruc*,bool fRefresh=false);
	void	DoPutA(ImageMapDesc*,DoPointStruc*);
	void	Do2DLine(UWord,UWord,UWord,UWord);
	void	DoRenderTileToDDSurface(UByte*,const HTEXT&);
	void	DoGetTextureScales(SLong&,SLong&,SLong&,SLong&,SLong&,SLong&);
	void	DoFreeTexture(const HTEXT&);
	void	DoFreeTextures();
	HTEXT	DoAllocateTexture(UByte);
	SWord	DoForceTQ(SWord);
	void	DoFlushAll(Bool);
	void	DoHWRegisterPal(UByte* src,ULong length);
	void	DoCalcItemFog(bool,Float&,Float&,Float&);
	bool  DoSetTranspFade(bool);
	void	DoNewTile(SLong,DoPointStruc*,SLong,UByte*,SLong);
	void	DoCNewTile(SLong,DoPointStruc*,SLong,UByte*,SLong);
	bool	DoTestAsyncBlt();
	void	DoBeginTextureScroll(const SWord,void*,void*);
	void	DoWaitTextureScrollComplete(const SWord);
	void	DoPartialTextureUpload(const SWord,void*,void*);
	void	DoCreateLandTBuffers();
	void*	DoGetLandBufferPtr(SWord);
	void*	DoGetLandPalLookup();
	void	DoSetLandPalLookup(UByte*);
	SWord	DoGetLandBpp();
	void	DoSetAspectRatio(Float ,Float);
	void	DoFlushLandDraw();
	void	DoCLEB();
	void	DoAddTile(ULong,ULong,DoPointStruc*,ULong,UByte*&);
	void	DoCAddTile(ULong,ULong,DoPointStruc*,ULong,UByte*&);
	void	DoCNearAddTile(ULong,ULong,DoPointStruc*,ULong,UByte*&,ULong);
	void	DoNearAddTile(ULong,ULong,DoPointStruc*,ULong,UByte*&,ULong);

	void	DoCNearAddTileX(ULong,ULong,DoPointStruc*,ULong,UByte*&,const HTEXT&,UWord);
	void	DoNearAddTileX(ULong,ULong,DoPointStruc*,ULong,UByte*&,const HTEXT&,UWord);

	void	DoNearAddDitherX(ULong,ULong,DoPointStruc*,ULong,UByte*&);

	void	DoSmokedGlassBox(SWord,SWord,SWord,SWord,ULong);
	void	DoBeginFan(ULong);
	void	DoBeginFan(ImageMapDesc*);
	void	DoAddFanPoint(DoPointStruc*,SLong,UByte*&);
	void	DoUploadLandTexture(ULong,ImageMapDesc*);
	bool	DoSetClipState(bool);
	void	DoReleaseTextures();
	void	DoSetTextureQuality(bool);
	bool	DoSetRangeFog(bool);
	void	DoGetHorizonColour(UByte&,UByte&,UByte&);			//PD 18Jan99
	void	DoSetHorizonColour(UByte,UByte,UByte);				//PD 18Jan99
	void	DoSetShadeVals(SLong,SLong,SLong,SLong,SLong,SLong);
	bool	DoSetLShade(bool);
	void	DoDomeHorizon(void*,void*);							//PD 26Nov97
	void	DoForceRender();
	UByte	DoSetGlobalAlpha(UByte);

	int	FrameTime();

	enum	{V_MINX=0,V_MAXX=25600,V_MINY=0,V_MAXY=19200,REALMODE_STACK_SIZE=(5*1024)};
	short	NumberOfScreens;
	SLong	VirtualMinX;		//these should never be>word
	SLong	VirtualWidth;		//note that these virtual mins and sizes
	SLong	VirtualMinY;		//must be proportional to 
	SLong	VirtualHeight;		//physical mins and sizes so that the
	short	virtualXscale;		//origin LogicalScreenPtr is in the same place
	short	virtualYscale;		//Then, scaling only needs /virtual?scale.

//-------------------------------------------------------
public:		//window on a physical screen
	CON		Window(const Window&,const int x,const int y,SWord scale=1);
	CON		Window(const Window&,const InitWindowDef&,SWord scale=1,Bool nofitfatal=FALSE);
	CON		Window(const Window&,WinShiftDef X=WINSH_SAME,WinShiftDef Y=WINSH_SAME,SWord scale=1);
	CON		Window(const Window&,ImageMap_Desc&);				//PD 28Jun96
	DES		~Window();

	CON		Window(Bool& unp,IntensityIndex*	ii,void*& pal,FontPtr& fp,FontPtr& mp);
//-------------------------------------------------------
public:
	void	ClearScreen(Colour);

	void 	GetFontInfo(short&, short& ,short&);
	short	GetCharacterWidth (short);

	void	GetRGB(SWord index,UByte& red,UByte& green,UByte& blue)
	{
		index = SWord(index*3);
		UByte* pp=(UByte*)Palette;
		pp += index;
		red = *pp++;
		green = *pp++;
		blue = *pp;
	};

	void	SetPixelWidth(SWord &);								//PD 03Jan96
	void*	GetPaletteTable();
	void	SelectPalette(SWord);
	UWord	GetPaletteEntry(UWord);
	void	SetPaletteEntry(UWord,UWord);
	void*	GetLandFadeTable();
	void*	GetSkyFadeTable();
	void*	GetHorizonFadeTable();
	void	SetTransparency(SWord );							//PD 02Apr96
	void	SetLuminosity(SWord );								//RJS 19Jan98
	void	SetHeatHaze(SWord );								//RJS 30Jan98
	void 	SetColour(Colour);
	void	SetColour(ROWANSURFACEDESC*);
	void 	SetColour(Colour,ColourRange);
	void 	SetColour(ImageMapNumber);
	void 	SetColour(ImageMap_Desc*);							//PD 03May96
	void	SetGlassRange(Colour);								//PD 02Apr96

	void 	ClipPolygon();

	void 	GetCharPos(short&, short&);
	short 	GetCharPos();	//returns X					//JIM 15Nov95

	void 	SetCharPos(short, short);

	void	ShowPic(FileNum );
	void	ShowPicScaled(FileNum,const int scale);
	UWord	ShowSmackSmall(Smack *);									//DAW 05Feb96
	UWord	ShowSmack(Smack *);
	Smack*	OpenSmack(FileNum);
	void	KillSmack(Smack *);										//DAW 01Feb96
	void	ScreenShot();										//DAW 19Feb96
	void	ScreenShot16();										//DAW 19Feb96

	short	CharacterPrint	(short);

	void	PlainLine		(SLong X1,SLong Y1,SLong X2,SLong Y2);

	void	ClipLine		(SLong X1,SLong Y1,SLong X2,SLong Y2);

	void	ClipLine3D		(SLong X1,SLong Y1,SLong X2,SLong Y2);
	void	ClipLine3D		(Float x1,Float y1,Float x2,Float y2);//RJS 25Feb97

	void	PlainCircle		(SLong R,SLong X,SLong Y);

	void	TransparentBlob	(SWord, SWord, SLong, SLong, SLong);//PD 28Jul97

	void	RegisterPalette(UByte*,SLong);
	void	ReinitDisplay();									//PD 03Jul97

	Colour	PlotLogicalPixel(SWord, SWord);
	Colour	PlotLogicalPixel(SWord, SWord,Colour);
	Bool	CopyP2L(SWord x,SWord Y,SWord W,SWord H);

	void	GetTrunkSxy(SLong &, SLong &);

	//Horizontal scan line routines for polygon drawing go here//PD 30Oct95

	HoriLineRtnPtr	GetScanLineAddr(SCANLINETYPE );				//PD 03Jan96

	void	MakeIntensityData();
	void	RectangleFill(SLong x,SLong y,ULong w,ULong h);		//PD 22Jul97
	void	GlassRectFill(ULong x,ULong y,ULong w,ULong h);		//PD 02Apr96
	void	AilRectFill(ULong x,ULong y,ULong w,ULong h);		//PD 21Jun96
	void	zclipline(DoPointStruc&,DoPointStruc&);				//RJS 23Jun97

	void	SetMouseImage(UWord chrnum);
	void	PrintIcon(int x,int y,int iconnum);

	void	ListVesaModes(ScreenRez* modelist);


private:

	short	PlotPhysicalPixel(short, short, short);
};
//-------------------------------------------------------
struct	DPMIMem
{
ULong	size;			//Input to GetDPMImem is size already filled in bytes
UWord	desc;			//This returns desc as a segment descriptor
UWord	seg,off;		//Seg is enough to find the data in both modes, 
void*	flat;			//but an offset may be desirable sometimes
};						//So, off is also an input, and flat will be set up.
//-------------------------------------------------------
//
// Physical screen manipulation
//
//
//-------------------------------------------------------
struct	PhysVesa
{
 	UWord	BytesPerPixel;
 	UWord	BitsPerPixel;
 	UWord	BytesPerScanLine;
	UWord	ScanLines;
	UWord	Screens;
	UWord	ScreenNum;
	UWord	PageNum;
	UWord	PageShift;
	UWord	pagetop;
	UWord	pageoff;
	ULong	PageSize;
	ULong	readaddr;
	ULong	writeaddr;
	ULong	readwin;
	ULong	writewin;
	ULong	videomem;	//available
	UWord	mode;
};

struct	FlatVesa
{
	UWord	mode;
	ULong	screen;
	ULong	scrsize;
	ULong	extrarama;
	ULong	extrarams;
	UWord	ScreenNum;
	UWord	lineshift;
	UWord	colshift;
	ULong	fliproutine;
	UWord	flipseg;
};
//-------------------------------------------------------


// Structure for Direct Draw Parameters							//ARM 25Jun96
//JIM 12/1/98
#ifdef	DECLARE_HANDLE
#undef	DECLARE_HANDLE
#endif
#ifdef STRICT
typedef void *HANDLE;
#define DECLARE_HANDLE(name) struct name##__; typedef struct name##__ *name
#else
typedef void *HANDLE;
#define DECLARE_HANDLE(name) typedef HANDLE name
#endif
typedef HANDLE *PHANDLE;

DECLARE_HANDLE            (HWND);
																//ARM 25Jun96
struct _DDSURFACEDESC;											//ARM 25Jun96
typedef struct IDirectDraw			*LPDIRECTDRAW;				//ARM 25Jun96
typedef struct IDirectDraw2			*LPDIRECTDRAW2;				//ARM 25Nov96
typedef struct IDirectDrawSurface   *LPDIRECTDRAWSURFACE;		//ARM 25Jun96
typedef struct IDirectDrawPalette   *LPDIRECTDRAWPALETTE;		//ARM 25Jun96
typedef struct IDirectDrawClipper   *LPDIRECTDRAWCLIPPER;		//ARM 25Jun96
																//ARM 25Jun96
typedef struct _DDSURFACEDESC       *LPDDSURFACEDESC;			//ARM 25Jun96
typedef struct IDirect3D			*LPDIRECT3D;				//PD 03Feb97

//struct	_DDCAPS;
//typedef	_DDCAPS	DDCAPS;
//typedef DDCAPS * LPDDCAPS;								//ARM 25Jun96

//struct DDCAPS;
//typedef struct DDCAPS *LPDDCAPS;

// This Structure is equivalent to tagPALETTEENTRY				//ARM 25Jun96
// defined in nt\wingdi.h										//ARM 25Jun96
// Cannot include windows header files							//ARM 25Jun96
																//ARM 25Jun96
typedef struct tagMYPALETTEENTRY {								//ARM 25Jun96
    UByte        peRed;											//ARM 25Jun96
    UByte        peGreen;										//ARM 25Jun96
    UByte        peBlue;										//ARM 25Jun96
    UByte        peFlags;										//ARM 25Jun96
} MYPALETTEENTRY, *MYPPALETTEENTRY, *MYLPPALETTEENTRY;			//ARM 25Jun96

class direct_3d;												//PD 31Jan97
typedef class direct_3d Direct3D,*Direct3DP;					//PD 31Jan97
class direct_draw;
typedef class direct_draw DirectDD,*DirectDDP;

#if !defined(DIRECTDRAW_VERSION) 
#define LPDDCAPS void*
#endif
																//ARM 25Jun96
struct _DirectDraw {												//ARM 25Jun96
																//ARM 25Jun96
	HWND	hWnd;		//handle to the window containing the
						//windowed version of the 3D
	HWND	hWndApp;	//handle to the main application window
																//ARM 25Jun96
	LPDIRECTDRAW2		lpDD2;									//ARM 25Nov96
	LPDIRECT3D			lpD3D;									//PD 03Feb97
	LPDIRECTDRAWSURFACE lpDDSPrimary; 							//ARM 25Jun96
	LPDIRECTDRAWSURFACE lpDDSBack;    							//ARM 25Jun96
	LPDIRECTDRAWSURFACE lpDDSBack2;    							//ARM 25Jun96
	LPDIRECTDRAWPALETTE	lpDDPal;	  							//ARM 25Jun96

	LPDDCAPS		lpDDDriverCaps;								//ARM 25Jul96
	LPDDCAPS		lpDDHelCaps;								//ARM 25Jul96
	
	LPDDSURFACEDESC   lpddsd;									//ARM 25Jun96
																//ARM 25Jun96
	MYLPPALETTEENTRY	PaletteBuffer;							//ARM 25Jun96
																//ARM 25Jun96
	UByteP pScreenB;											//ARM 22Jul96

	LPDIRECTDRAWSURFACE Screens[4];								//ARM 24Jul96
	UWord	DDOnScreen;			   								//ARM 24Jul96
	UWord	DDSpareScreen;										//ARM 24Jul96
	UWord	DDLogicalScreen;									//ARM 24Jul96

	UWord DDCurrMode;											//ARM 26Nov96
	UWord cModes;												//ARM 26Nov96
	InitDisplayDef DDModes [MAXCMODES];							//ARM 25Nov96

	static DirectDDP	lpDirectDD;										//PD 03Feb97
	Direct3DP	lpDirect3D;										//PD 03Feb97
	SLong		*lpImageMapTable2;								//PD 10Mar97

	Bool	ModeX;												//ARM 29Nov96

	Bool	DebugMode;											//ARM 19Dec96
	UByte	hcRed,hcGreen,hcBlue;

};																//ARM 25Jun96

class	View3d;

class	Display:public	Window
{

	friend class UISheet;										//AMM 29Apr97
	friend class ThreeDee;										//AMM 30Apr97
	friend class btree;											//AMM 30Apr97
	friend class Graphic;										//AMM 01May97
	friend class polygon;										//AMM 01May97

public:
	View3d*	view3dwin;
	int	FrameTime();
	enum	SVGALibModeFix		//use this to indirect through for now!
				{	SVGA_winc,	//direct
					SVGA_winf,	//pseudoscreen
					SVGA_VESAc,	//copy to physical
					SVGA_VESAf,	//hardware swapping
					SVGA_VESAd,	//debug direct to display
					SVGA_CUSTOM_1c,
					SVGA_CUSTOM_1d,
					SVGA_CUSTOM_2,
					SVGA_CUSTOM_3
				}
			svgalibmodefix;

	int		mouseimagenumber;
	short	ScreenNumOnLogical;
	unsigned char *real_mode_stack;
	FontPtr	mousefontptr;
	UWord	prevmodeAX,prevmodeBX;			//This should really be the hardware video mode detected

	//The following 4 fields are referenced from Graphic
	//They are kind of static, but not quite!
	Bool	UseNewPal;
	void*	Palette;			//Let's attempt to spell this correctly
	Colour	shadetable[SHADECOLOURMAX];
	FontPtr	fontptr;			//Current font description
	IntensityIndex
			intensityindex;

	union	{	PhysVesa	VESA;	//add other support records 'here'
				FlatVesa	VFLAT;
				_DirectDraw	DD;	// The DirectDraw Params	//ARM 25Jun96
			};

//-------------------------------------------------------
	CON	Display(View3d* view);
	DES	~Display();
//-------------------------------------------------------
//actual low level routines that need to be libraried:
//
//
	void	PlotMouseScanline(SWord	x, SWord	y, SWord	w, UByte	*&pos);
	void	PlotAndSaveMouseScanline(SWord	x, SWord	y, SWord	w, UByte	*&oldpos, UByte	*&newpos);

	void	SetGraphicsMode();

 	Colour	PlotPixel(SWord, SWord, Colour);
	ULong	PlotPixelNoClip(UWord, UWord, ULong);
	Bool	CopyP2L(LogicalPtr	T,int W,int H);

	void	PhysMouseMove(SWord	newx, SWord	newy, short	imagenum=-1);
	UByte*	MousePixelData(short	imagenum);

//DEAD 	void LockBackScreen(Bool winmov,UByte low, UByte high);			//AMM 01May97
//DEAD 	void UnLockBackScreen(UByte low, UByte high);						//AMM 01May97


//DEAD 	void	LockBackScreen (Bool);								//ARM 21Jun96
//DEAD 	void	UnLockBackScreen ();								//ARM 21Jun96
	void	TestHW3D(Window*);									//PD 23Sep97
	Bool	HardPoly(LPPOLYTYPE);								//PD 12Feb97
	void	PushViewData();
	void	PopViewData();
	void	Set3DWin(SLong x,SLong y,SLong w,SLong h);
	bool	ScanForBottomPixelsOfText(SWord,SWord,SWord);
	void	PushPull(UByte);
	void	MakePaletteFadeTable(UByte*,UWord*,UByte,UByte,UByte);
	void	MakeColourRangeFadeTable(UWord*,UByte,UByte,UByte,UByte,UByte,UByte);
	void	GetColourInfo(UWord&,SWord&,SWord&,UWord&,SWord&,SWord&,UWord&,SWord&,SWord&);
	void	LockScr(ROWANSURFACEDESC*);
	void	UnlockScr(ROWANSURFACEDESC*);
	void	PutLine(SWord,SWord,SWord,SWord,Colour);
	void	ShowLoaderArt(void*);
	void	CaptureScreen();
	void	SaveVideoBuffer();
	void	GammaCorr(UByte& r,UByte& g,UByte& b);
	bool	SetEdgeTest(bool);
	void	SetSunPos(DoPointStruc&);
	bool	SetMipMap(bool);
	void	PeripheralBlob(Float*,Float*,Float*,UByte,SLong);
	void	SetFontColour(ULong );
	void	GetSurfaceDimensions(SLong&,SLong&);
	void	PutC(ImageMapDesc*,DoPointStruc*,bool fRefresh=false);
	void	PutA(ImageMapDesc*,DoPointStruc*);
	void	D2DLine(UWord,UWord,UWord,UWord);
	void	RenderTileToDDSurface(UByte*,const HTEXT&);
	void	GetTextureScales(SLong&,SLong&,SLong&,SLong&,SLong&,SLong&);
	void	FreeTexture(const HTEXT&);
	void	FreeTextures();
	HTEXT	AllocateTexture(UByte);
	SWord	ForceTQ(SWord);
	void	FlushAll(Bool);
	void	HWRegisterPal(UByte*,ULong);
	void	CalcItemFog(bool,Float&,Float&,Float&);
	bool  SetTranspFade(bool);
	void	NewTile(SLong,DoPointStruc*,SLong,UByte*,SLong);
	void	CNewTile(SLong,DoPointStruc*,SLong,UByte*,SLong);
	bool	TestAsyncBlt();
	void	BeginTextureScroll(const SWord,void*,void*);
	void	WaitTextureScrollComplete(const SWord);
	void	PartialTextureUpload(const SWord,void*,void*);
	void	CreateLandTBuffers();
	void*	GetLandPalLookup();
	void	SetLandPalLookup(UByte*);
	SWord	GetLandBpp();
	void*	GetLandBufferPtr(SWord);
	void	SetAspectRatio(Float ,Float);
	void	FlushLandDraw();
	void	CLEB();
	void	AddTile(ULong,ULong,DoPointStruc*,ULong,UByte*&);
	void	CAddTile(ULong,ULong,DoPointStruc*,ULong,UByte*&);
	void	CNearAddTile(ULong,ULong,DoPointStruc*,ULong,UByte*&,ULong);

	void	CNearAddTileX(ULong,ULong,DoPointStruc*,ULong,UByte*&,const HTEXT&,UWord);
	void	NearAddTileX(ULong,ULong,DoPointStruc*,ULong,UByte*&,const HTEXT&,UWord);

	void	NearAddDitherX(ULong,ULong,DoPointStruc*,ULong,UByte*&);

	void	NearAddTile(ULong,ULong,DoPointStruc*,ULong,UByte*&,ULong);
	void	SmokedGlassBox(SWord,SWord,SWord,SWord,ULong);
	void	BeginFan(ULong);
	void	BeginFan(ImageMapDesc*);
	void	AddFanPoint(DoPointStruc*,SLong,UByte*&);
	void	UploadLandTexture(ULong,ImageMapDesc*);
	bool	SetClipState(bool);
	void	ReleaseTextures();
	void	SetTextureQuality(bool);
	bool	SetRangeFog(bool);
	void	GetHorizonColour(UByte&,UByte&,UByte&);				//PD 18Jan99
	void	SetHorizonColour(UByte,UByte,UByte);				//PD 18Jan99
	void	SetShadeVals(SLong,SLong,SLong,SLong,SLong,SLong);
	bool	SetLShade(bool);
	void	ForceRender();
	UByte	SetGlobalAlpha(UByte);
	void	DomeHorizon(void*,void*);							//PD 26Nov97
	void	BackupLogicalPtr();									//PD 21Oct97
	void	ResetLogicalPtr();									//PD 21Oct97
	void	SetFogState(Bool);									//PD 09Oct97
	void	Body2Screen(DoPointStruc&);
	void	SetFadeValue(UByte);								//PD 07Jun97
	Bool	EnableBackClip(Bool);								//PD 05Jun97
	void	SetFade(Colour trgCol,SLong step,TwoDeeEffect tdfx);					//PD 05Jun97
	Bool	ModeSupported(ScreenRez*);							//PD 29May97
	Bool	DriverIsCapable(SWord );							//PD 29May97
	UByte*	NameNumberedDriver(SWord);							//PD 23May97
	SWord	CountDrivers();										//PD 27May97
	Bool	HardLine(LPLINETYPE);								//PD 28Apr97
	Bool	HardPoint(LPPOINTTYPE);								//PD 28Apr97
	void	SetViewParams(ANGLES,Window*,ViewPoint*);								//PD 18Apr97
	Bool	HardPlainRectFill(Window*,SWord,SWord,SWord,SWord);	//PD 22May97
	Bool	SetZUpdate(Bool);									//PD 07Apr97
	Bool	SetPlayerTextures(Bool);							//PD 08May97
	Bool	Hardware3D();										//PD 25Feb97
	void	SetFog(UByte,UByte,UByte,SLong,SLong);							//PD 24Feb97
	void	SetFog(UByte,UByte,UByte);
	void	GetFog(UByte&,UByte&,UByte&,SLong&,SLong&);
	Bool	SetMatrices(SLong,ANGLES);							//PD 06Mar97
	void	BeginScene();										//PD 17Feb97
	void	EndScene();											//PD 17Feb97
	void	End3DScene();											//PD 17Feb97
	void	HCls(Bool);											//PD 10Jun97
	void	EnableGUI (Bool Ctrl);								//ARM 30Sep96
	Bool	InitDirectDraw ();									//ARM 25Nov96
	Bool	ExitDirectDraw ();									//ARM 25Nov96
	Bool	EnumModes ();										//ARM 25Nov96
private:
	void	ScreenFlip();	//short UseNewPal=FALSE);
	void	PalChange();	//short UseNewPal=FALSE);
	void	SetMouseSaveInfo(short	savenum, short	imagenum, SWord	newx, SWord	newy);
	void	ResetGraphicsMode();

	void	XX_SetGraphicsMode();
	void	XX_ResetGraphicsMode();
	void	XX_ScreenFlip();	//short UseNewPal=FALSE);
	void	XX_PalChange();	//short UseNewPal=FALSE);
	Bool	XX_CopyP2L(LogicalPtr	T,int W,int H);
	ULong	XX_PlotPixelNoClip(UWord, UWord, ULong);
	ULong 	SetDirectDrawMode (InitDisplayDef&);				//ARM 26Nov96
	Bool	KillSurfaces ();									//ARM 26Nov96
	void	ChangeBytesPerScanLine ();							//ARM 26Nov96


//-------------------------------------------------------
//higher level routines that don't need libraries:
//
public:
	void 	ClearScreen(short Colour);
	void	SetTextMode();
	Bool	GetDOSRAM(DPMIMem&,ULong size=0,UWord off=-1);
	void	FreeDOSRAM(DPMIMem&);
	void	MemScreen(ScreenPages);
	void	DirectDraw_MemScreen (ScreenPages);						//ARM 23Jul96
	void 	MouseRedraw();
	void	ScreenSwap();	//short UseNewPal=FALSE);
	void	LoadMouseImage(FileNum filenumber);
	void	SetMouseImage(UWord chrnum)	{mouseimagenumber=chrnum;}
	void	ListVesaModes(ScreenRez* modelist);
	void	DoTestHW3D(Window*);								//PD 23Sep97
	Bool	DoHardPoly(LPPOLYTYPE);								//PD 12Feb97
	void	DoPushViewData();
	void	DoPopViewData();
	void	DoSet3DWin(SLong x,SLong y,SLong w,SLong h);
	bool	DoScanForBottomPixelsOfText(SWord,SWord,SWord);
	void	DoPushPull(UByte);
	void	DoMakeColourRangeFadeTable(UWord*,UByte,UByte,UByte,UByte,UByte,UByte);
	void	DoMakePaletteFadeTable(UByte*,UWord*,UByte,UByte,UByte);
	void	DoGetColourInfo(UWord&,SWord&,SWord&,UWord&,SWord&,SWord&,UWord&,SWord&,SWord&);
	void	DoLockScr(ROWANSURFACEDESC*);
	void	DoUnlockScr(ROWANSURFACEDESC*);
	void	DoPutLine(SWord,SWord,SWord,SWord,Colour);
	void	DoScreenSwap();
	void	DoShowLoaderArt(void*);
	void	DoCaptureScreen();
	void	DoSaveVideoBuffer();
	void	DoGammaCorr(UByte& r,UByte& g,UByte& b);
	bool	DoSetEdgeTest(bool);
	void	DoSetSunPos(DoPointStruc&);
	bool	DoSetMipMap(bool);
	void	DoPeripheralBlob(Float*,Float*,Float*,UByte,SLong);
	void	DoSetFontColour(ULong );
	void	DoGetSurfaceDimensions(SLong&,SLong&);
	void	DoPutC(ImageMapDesc*,DoPointStruc*,bool fRefresh=false);
	void	DoPutA(ImageMapDesc*,DoPointStruc*);
	void	Do2DLine(UWord,UWord,UWord,UWord);
	void	DoRenderTileToDDSurface(UByte*,const HTEXT&);
	void	DoGetTextureScales(SLong&,SLong&,SLong&,SLong&,SLong&,SLong&);
	void	DoFreeTexture(const HTEXT&);
	void	DoFreeTextures();
	HTEXT	DoAllocateTexture(UByte);
	SWord	DoForceTQ(SWord);
	void	DoFlushAll(Bool);
	void	DoCalcItemFog(bool,Float&,Float&,Float&);
	bool  DoSetTranspFade(bool);
	void	DoNewTile(SLong,DoPointStruc*,SLong,UByte*,SLong);
	void	DoCNewTile(SLong,DoPointStruc*,SLong,UByte*,SLong);
	bool	DoTestAsyncBlt();
	void	DoWaitTextureScrollComplete(const SWord);
	void	DoPartialTextureUpload(const SWord,void*,void*);
	void	DoBeginTextureScroll(const SWord,void*,void*);
	void	DoCreateLandTBuffers();
	void*	DoGetLandPalLookup();
	void	DoSetLandPalLookup(UByte*);
	SWord	DoGetLandBpp();
	void*	DoGetLandBufferPtr(SWord);
	void	DoSetAspectRatio(Float ,Float);
	void	DoFlushLandDraw();
	void	DoCLEB();
	void	DoAddTile(ULong,ULong,DoPointStruc*,ULong,UByte*&);
	void	DoCAddTile(ULong,ULong,DoPointStruc*,ULong,UByte*&);
	void	DoCNearAddTile(ULong,ULong,DoPointStruc*,ULong,UByte*&,ULong);

	void	DoCNearAddTileX(ULong,ULong,DoPointStruc*,ULong,UByte*&,const HTEXT&,UWord);
	void	DoNearAddTileX(ULong,ULong,DoPointStruc*,ULong,UByte*&,const HTEXT&,UWord);

	void	DoNearAddDitherX(ULong,ULong,DoPointStruc*,ULong,UByte*&);

	void	DoNearAddTile(ULong,ULong,DoPointStruc*,ULong,UByte*&,ULong);
	void	DoSmokedGlassBox(SWord,SWord,SWord,SWord,ULong);
	void	DoBeginFan(ULong);
	void	DoBeginFan(ImageMapDesc*);
	void	DoAddFanPoint(DoPointStruc*,SLong,UByte*&);
	void	DoUploadLandTexture(ULong,ImageMapDesc*);
	bool	DoSetClipState(bool);
	void	DoReleaseTextures();
	void	DoSetTextureQuality(bool);
	bool	DoSetRangeFog(bool);
	void	DoGetHorizonColour(UByte&,UByte&,UByte&);			//PD 18Jan99
	void	DoSetHorizonColour(UByte,UByte,UByte);				//PD 18Jan99
	void	DoSetShadeVals(SLong,SLong,SLong,SLong,SLong,SLong);
	bool	DoSetLShade(bool);
	UByte	DoSetGlobalAlpha(UByte);
	void	DoForceRender();
	void	DoDomeHorizon(void*,void*);							//PD 26Nov97
	void	DoBackupLogicalPtr();								//PD 21Oct97
	void	DoResetLogicalPtr();								//PD 21Oct97
	void	DoSetFogState(Bool);								//PD 09Oct97
	void	DoBody2Screen(DoPointStruc&);
	void	DoSetFadeValue(UByte);								//PD 07Jun97
	Bool	DoEnableBackClip(Bool);								//PD 05Jun97
	void	DoSetFade(Colour trgCol,SLong step,TwoDeeEffect tdfx);				//PD 05Jun97
	Bool	XModeSupported(ScreenRez*);							//PD 29May97
	Bool	XDriverIsCapable(SWord );							//PD 29May97
	UByte*	DoNameNumberedDriver(SWord);						//PD 23May97
	SWord	DoCountDrivers();									//PD 27May97
	Bool	DoHardLine(LPLINETYPE);								//PD 28Apr97
	Bool	DoHardPoint(LPPOINTTYPE);							//PD 28Apr97
	void	DoSetViewParams(ANGLES,Window*,ViewPoint*);							//PD 18Apr97
	Bool	DoHardPlainRectFill(Window*,SWord,SWord,SWord,SWord);//PD 22May97
	Bool	DoSetZUpdate(Bool);									//PD 07Apr97
	Bool	DoSetPlayerTextures(Bool);							//PD 08May97
	Bool	DoingHardware3D();									//PD 25Feb97
	Bool	DoSetMatrices(SLong,ANGLES);						//PD 06Mar97
	void	DoSetFog(UByte,UByte,UByte,SLong,SLong);						//PD 24Feb97
	void	DoSetFog(UByte,UByte,UByte);
	void	DoGetFog(UByte&,UByte&,UByte&,SLong&,SLong&);
	void	DoBeginScene();										//PD 17Feb97
	void	DoEndScene();										//PD 17Feb97
	void	DoEnd3DScene();										//PD 17Feb97
	void	HClearScreen();										//PD 10Feb97

private:

	short	GetDOSRAM(long& ,short);
	void	FreeDOSRAM(short );

	void	WindowMoved(LogicalPtr	oldplace,LogicalPtr newplace);//JIM 25Jan96
//Res specific routines that CHOOSE which res library to load!

Bool	FindModeWin(InitDisplayDef&);
FileNum	SelectLibWin();
Bool	FindModeVESA(InitDisplayDef&);
FileNum	SelectLibVESA();
Bool	FindModeDirty(InitDisplayDef&);
FileNum	SelectLibDirty();
void	LoadGraphicsLib(FileNum);


//-------------------------------------------------------
//These routines are not 'libraried'
//
//
public:
#ifdef	STUB3d_defined
	short	Init(WinMode::Mode v,int L,int T,int R,int B);
#endif
	void	Exit();
	void	ChangeRes(ScreenRez& srez);							//PD 04Feb97
private:
	void	SelectAndLoadLib(InitDisplayDef&);
};
inline	void	Window::SetMouseImage(UWord chrnum)
	{((Display*)master)->SetMouseImage(chrnum);}

//------------------------------------------------------------------------------
//This layer should not be here. The callers should know the master window.
//When I understand how windows are being used I'll redo this bit.
inline	Bool	Window::DoSetPlayerTextures(Bool B)
	{return	Master()->DoSetPlayerTextures(B);}
inline 	Bool	Window::DoSetZUpdate(Bool B)
	{return Master()->DoSetZUpdate(B);}
inline	Bool	Window::DoHardLine(LPLINETYPE L)
	{return	Master()->DoHardLine(L);}
inline	Bool	Window::DoingHardware3D()
	{return	Master()->DoingHardware3D();}
inline	Bool	Window::DoHardPoint(LPPOINTTYPE L)
	{return	Master()->DoHardPoint(L);}
inline	Bool	Window::DoEnableBackClip(Bool b)
{return	Master()->DoEnableBackClip(b);}
inline	void	Window::DoSetFade(Colour trgCol,SLong step,TwoDeeEffect tdfx)
{Master()->DoSetFade(trgCol,step,tdfx);}
inline	void	Window::HCls(Bool b)
{Master()->HCls(b);}
inline	void	Window::DoSetFadeValue(UByte U)
{Master()->DoSetFadeValue(U);}
inline	void	Window::DoSetFogState(Bool b)
{Master()->DoSetFogState(b);}
inline	Bool	Window::DoSetMatrices(SLong a,ANGLES b)
{return	Master()->DoSetMatrices(a,b);}
inline	void	Window::DoSetFog(UByte rr,UByte gg,UByte bb,SLong b,SLong c)
{Master()->DoSetFog(rr,gg,bb,b,c);}

inline void	Window::DoSetFog(UByte r,UByte g,UByte b)
{Master()->DoSetFog(r,g,b);}

inline void	Window::DoGetFog(UByte& r,UByte& g,UByte& b,SLong& s,SLong& e)
{Master()->DoGetFog(r,g,b,s,e);}

inline	void	Window::DoSetViewParams(ANGLES a,Window* w,ViewPoint* v)
{Master()->DoSetViewParams(a,w,v);}
inline	void	Window::DoBeginScene()
{Master()->DoBeginScene();}
inline	void	Window::BeginScene()
{Master()->BeginScene();}

//DEAD inline	void Window::LockBackScreen(Bool winmov,UByte low, UByte high)
//DEAD {Master()->LockBackScreen(winmov,low, high);}
//DEAD inline	void Window::UnLockBackScreen(UByte low, UByte high)
//DEAD {Master()->UnLockBackScreen(low,high);}
inline	void	Window::EndScene()
{Master()->EndScene();}
inline	void	Window::End3DScene()
{Master()->End3DScene();}
inline	Bool	Window::DoHardPoly(LPPOLYTYPE L)
{return Master()->DoHardPoly(L);}
inline	void	Window::DoPushViewData()
{Master()->DoPushViewData();}
inline 	void	Window::DoPopViewData()
{Master()->DoPopViewData();}
inline void	Window::DoSet3DWin(SLong x,SLong y,SLong w,SLong h)
{Master()->DoSet3DWin(x,y,w,h);}
inline bool	Window::DoScanForBottomPixelsOfText(SWord a,SWord b,SWord c)
{ 	return Master()->DoScanForBottomPixelsOfText(a,b,c);}
inline	void	Window::DoPushPull(UByte a)
{Master()->DoPushPull(a);}

inline 	void	Window::DoMakePaletteFadeTable(UByte* a,UWord* b,UByte c,UByte d,UByte e)
{
	Master()->DoMakePaletteFadeTable(a,b,c,d,e);
}
inline void Window::DoMakeColourRangeFadeTable(UWord* a,UByte b,UByte c,UByte d,UByte e,UByte f,UByte g)
{
	Master()->DoMakeColourRangeFadeTable(a,b,c,d,e,f,g);
}
inline	void	Window::DoGetColourInfo(UWord& a,SWord& b,SWord& c,UWord& d,SWord& e,SWord& f,UWord& g,SWord& h,SWord& i)
{Master()->DoGetColourInfo(a,b,c,d,e,f,g,h,i);}

inline void Window::DoLockScr(ROWANSURFACEDESC* a)
{Master()->DoLockScr(a);}

inline void Window::DoUnlockScr(ROWANSURFACEDESC* a)
{Master()->DoUnlockScr(a);}

inline void	Window::DoPutLine(SWord a,SWord b,SWord c,SWord d,Colour e)
{Master()->DoPutLine(a,b,c,d,e);}

inline void Window::DoScreenSwap()
{Master()->DoScreenSwap();}
inline void Window::DoShowLoaderArt(void* pArt)
{Master()->DoShowLoaderArt(pArt);}
inline	void	Window::DoCaptureScreen()
{Master()->DoCaptureScreen();}
inline 	void	Window::DoSaveVideoBuffer()
{Master()->DoSaveVideoBuffer();}
inline 	void	Window::DoSetFontColour(ULong a)
{Master()->DoSetFontColour(a);}

inline void Window::DoGammaCorr(UByte& r,UByte& g,UByte& b)
{Master()->DoGammaCorr(r,g,b);}

inline bool	Window::DoSetEdgeTest(bool a)
{return Master()->DoSetEdgeTest(a);}

inline void Window::DoSetSunPos(DoPointStruc& a)
{Master()->DoSetSunPos(a);}

inline void	Window::DoBody2Screen(DoPointStruc& a)
{Master()->DoBody2Screen(a);}

inline bool Window::DoSetMipMap(bool a)
{return Master()->DoSetMipMap(a);}

inline void	Window::DoPeripheralBlob(Float* a,Float* b,Float* c,UByte d,SLong e)
{Master()->DoPeripheralBlob(a,b,c,d,e);}

inline void	Window::DoGetSurfaceDimensions(SLong& a,SLong& b)
{Master()->DoGetSurfaceDimensions(a,b);}

inline void	Window::DoPutC(ImageMapDesc* a,DoPointStruc* b,bool fRefresh)
{Master()->DoPutC(a,b,fRefresh);}

inline void	Window::DoPutA(ImageMapDesc* a,DoPointStruc* b)
{Master()->DoPutA(a,b);}

inline 	void	Window::Do2DLine(UWord a,UWord b,UWord c,UWord d)
{Master()->Do2DLine(a,b,c,d);}

inline	void	Window::DoRenderTileToDDSurface(UByte* a,const HTEXT& b)
{Master()->DoRenderTileToDDSurface(a,b);}

inline void	Window::DoGetTextureScales(SLong& a,SLong& b,SLong& c,SLong& d,SLong& e,SLong& f)
{Master()->DoGetTextureScales(a,b,c,d,e,f);}

inline void Window::DoFreeTexture(const HTEXT& a)
{Master()->DoFreeTexture(a);}

inline void Window::DoFreeTextures()
{Master()->DoFreeTextures();}

inline HTEXT Window::DoAllocateTexture(UByte a)
{return Master()->DoAllocateTexture(a);}

inline SWord	Window::DoForceTQ(SWord a)
{return Master()->DoForceTQ(a);}

inline void Window::DoFlushAll(Bool f)
{Master()->DoFlushAll(f);}

inline void		Window::DoCalcItemFog(bool a,Float& b,Float& c,Float& d)
{Master()->DoCalcItemFog(a,b,c,d);}

inline bool Window::DoSetTranspFade(bool a)
{
	return Master()->DoSetTranspFade(a);
}

inline void Window::DoNewTile(SLong z,DoPointStruc* a,SLong b,UByte* c,SLong d)
{
	Master()->DoNewTile(z,a,b,c,d);
}
inline void Window::DoCNewTile(SLong z,DoPointStruc* a,SLong b,UByte* c,SLong d)
{
	Master()->DoCNewTile(z,a,b,c,d);
}

inline	bool	Window::DoTestAsyncBlt()
{return Master()->DoTestAsyncBlt();}

inline void	Window::DoPartialTextureUpload(const SWord a,void* b,void* c)
{
 	Master()->DoPartialTextureUpload(a,b,c);
}

inline void	Window::DoBeginTextureScroll(const SWord a,void* b,void* c)
{
	Master()->DoBeginTextureScroll(a,b,c);
}

inline 	void	Window::DoWaitTextureScrollComplete(const SWord a)
{
	Master()->DoWaitTextureScrollComplete(a);
}
inline void		Window::DoCreateLandTBuffers()
{Master()->DoCreateLandTBuffers();}

inline	void*	Window::DoGetLandPalLookup()
{return Master()->DoGetLandPalLookup();}

inline	void	Window::DoSetLandPalLookup(UByte* a)
{Master()->DoSetLandPalLookup(a);}

inline SWord	Window::DoGetLandBpp()
{return Master()->DoGetLandBpp();}

inline void*	Window::DoGetLandBufferPtr(SWord a)
{return Master()->DoGetLandBufferPtr(a);}

inline 	void	Window::DoSetAspectRatio(Float ar,Float fov)
{Master()->DoSetAspectRatio(ar,fov);}

inline void	Window::DoFlushLandDraw()
{Master()->DoFlushLandDraw();}

inline void Window::DoCLEB() {Master()->DoCLEB();}
inline void	Window::DoAddTile(ULong a,ULong aa,DoPointStruc* b,ULong c,UByte*& d)
{Master()->DoAddTile(a,aa,b,c,d);}

inline void	Window::DoCAddTile(ULong a,ULong aa,DoPointStruc* b,ULong c,UByte*& d)
{Master()->DoCAddTile(a,aa,b,c,d);}

inline void	Window::DoCNearAddTile(ULong a,ULong aa,DoPointStruc* b,ULong c,UByte*& d,ULong e)
{Master()->DoCNearAddTile(a,aa,b,c,d,e);}

inline void	Window::DoNearAddTile(ULong a,ULong aa,DoPointStruc* b,ULong c,UByte*& d,ULong e)
{Master()->DoNearAddTile(a,aa,b,c,d,e);}

inline	void	Window::DoCNearAddTileX(ULong a,ULong b,DoPointStruc* c,ULong d,UByte*& e,const HTEXT& f,UWord flag)
{Master()->DoCNearAddTileX(a,b,c,d,e,f,flag);}

inline	void	Window::DoNearAddTileX(ULong a,ULong b,DoPointStruc* c,ULong d,UByte*& e,const HTEXT& f,UWord flag)
{Master()->DoNearAddTileX(a,b,c,d,e,f,flag);}

inline	void	Window::DoNearAddDitherX(ULong a,ULong b,DoPointStruc* c,ULong d,UByte*& e)
{Master()->DoNearAddDitherX(a,b,c,d,e);}

inline void Window::DoSmokedGlassBox(SWord a,SWord b,SWord c,SWord d,ULong e)
{Master()->DoSmokedGlassBox(a,b,c,d,e);}

inline void	Window::DoBeginFan(ULong hTexture)
{Master()->DoBeginFan(hTexture);}
inline void	Window::DoBeginFan(ImageMapDesc* pImage)
{Master()->DoBeginFan(pImage);}
inline void	Window::DoAddFanPoint(DoPointStruc* pdp,SLong vCnt,UByte*& pData)
{Master()->DoAddFanPoint(pdp,vCnt,pData);}

inline	void	Window::DoUploadLandTexture(ULong hTexture,ImageMapDesc* lpImage)
{Master()->DoUploadLandTexture(hTexture,lpImage);}
inline bool Window::DoSetClipState(bool newState)
{return Master()->DoSetClipState(newState);}
inline	void	Window::DoReleaseTextures()
{Master()->DoReleaseTextures();}
inline 	void	Window::DoSetTextureQuality(bool b)
{Master()->DoSetTextureQuality(b);}
inline bool 	Window::DoSetRangeFog(bool b)
{return Master()->DoSetRangeFog(b);}
inline void Window::DoGetHorizonColour(UByte& a,UByte& b,UByte& c)//PD 18Jan99
{Master()->DoGetHorizonColour(a,b,c);}							//PD 18Jan99
inline void Window::DoSetHorizonColour(UByte a,UByte b,UByte c)	//PD 18Jan99
{Master()->DoSetHorizonColour(a,b,c);}							//PD 18Jan99
inline void Window::DoSetShadeVals(SLong nr,SLong ng,SLong nb,SLong er,SLong eg,SLong eb)
{Master()->DoSetShadeVals(nr,ng,nb,er,eg,eb);}
inline bool Window::DoSetLShade(bool b)
{return Master()->DoSetLShade(b);}
inline UByte Window::DoSetGlobalAlpha(UByte a)
{return Master()->DoSetGlobalAlpha(a);}
inline void	Window::DoForceRender()
{Master()->DoForceRender();}
inline	int		Window::FrameTime()
{return Master()->FrameTime();}
inline void	Window::DoDomeHorizon(void* a,void* b)							//PD 26Nov97
{Master()->DoDomeHorizon(a,b);}

//------------------------------------------------------------------------------
#endif

