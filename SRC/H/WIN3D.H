//------------------------------------------------------------------------------
//Filename       win3d.h
//System         
//Author         Dave Whiteside
//Date           Thu 30 Jan 1997
//Description    
//------------------------------------------------------------------------------
#ifndef	WIN3D_Included
#define	WIN3D_Included

#define	DEFAULT_WIN3D 0

#include "DosDefs.H"
#include <assert.h>
#include <windows.h>
#include <ddraw.h>
#include <d3d.h>
#pragma pack(1)														  //JIM 30/07/99
#include "mystack.h"
#include "areaType.h"

#include "d3dmacs.h"

enum {_landscapeTextures=7,_landTextureWH=256};

const SWord MAX_MAP_RECORDS=128;
const SWord MAX_RECORD_RECORDS=32;

enum MapUseFlags {MUF_NULL=0,MUF_NOMIP,MUF_REFRESH};

struct MapUse
{
	ImageMapDescPtr pmap;
	SWord textureQuality;
	SWord count;
	UWord flags;
	UWord offset[MAX_MAP_RECORDS];
};

struct BufferUse
{
	SWord count;
	MapUse mapUse[MAX_RECORD_RECORDS];
};

typedef struct R3DCOLOR
{
	UByte	b,g,r,a;

	inline bool operator==(const R3DCOLOR& cmp) const
	{
		return (*(ULong*)this==*(ULong*)&cmp);
	}
}
*LPR3DCOLOR;

enum INTERPFLAGS3D {IF3D_NULL		= 0x0000,
					IF3D_COLOR		= 0x0040,
					IF3D_SPECULAR	= 0x0080,
					IF3D_TEXTURE	= 0x0100,
					IF3D_ALL=IF3D_COLOR+IF3D_SPECULAR+IF3D_TEXTURE};

typedef struct R3DTLVERTEX
{
	union
	{
		D3DVALUE	sx;
		D3DVALUE	dvSX;
	};
	union
	{
		D3DVALUE	sy;
		D3DVALUE	dvSY;
	};
	union
	{
		D3DVALUE	sz;
		D3DVALUE	dvSZ;
	};
	union
	{
		D3DVALUE	rhw;
		D3DVALUE	dvRHW;
		UWord		clipFlags;	//new bit!
	};
	union
	{
		D3DCOLOR	color;
		D3DCOLOR	dcColor;
		R3DCOLOR	col;
	};
	union
	{
		D3DCOLOR	specular;
		D3DCOLOR	dcSpecular;
		R3DCOLOR	spec;
	};
	union
	{
		D3DVALUE	tu;
		D3DVALUE	dvTU;
		SWord		ix;
	};
	union
	{
		D3DVALUE	tv;
		D3DVALUE	dvTV;
		SWord		iy;
	};
}
*LPR3DTLVERTEX;

struct 
LandTexture
{
	COORDS3D				World;
 	DDSURFACEDESC			ddsdSurfaceDesc;
	LPDIRECTDRAWSURFACE 	lpDD1TSurf;
	LPDIRECTDRAWSURFACE2 	lpDD2TSurf;
	LPDIRECT3DTEXTURE   	lpD3DText;
	D3DTEXTUREHANDLE		hTexture;
	BOOL					bPageLocked;
	BOOL					bUpdatePending;						//PD 03Jun97
};

typedef struct LandVert
{
	IFShare	wx,wz;
	IFShare	bodyx,
			bodyy,
			bodyz;
	SWord	intensity;
}
LANDVERTEX,*LPLANDVERTEX;	

typedef struct	fvertex
{

	IFShare	bx,by,bz;
	IFShare	sx,sy;
	IFShare	ix,iy;
	IFShare	intensity;
	UByte	r,g,b,a;
	UByte	mist;
	UByte	snow;
}
FVERTEX,*LPFVERTEX;

typedef	struct	ClipVertex
{
	LANDVERTEX	lvt;
	UWord		flags;
}
ClipVertex,*ClipVertexP;

typedef struct	PClipVertex
{
	FVERTEX	lvt;
	UWord	flags;
}
PClipVertex,*PClipVertexP;

typedef	class Heap<ClipVertex> CVHeap,*CVHeapP;

typedef	class Heap<PClipVertex> PCVHeap,*PCVHeapP;

class	item;

const ULong	ltSystem 	=  0x0001;
const ULong ltNormal	=  0x0002;
const ULong	ltSystemDPF =  0x0004;
const ULong ltNormalDPF =  0x0008;

const ULong NormalLevels = 8;
const ULong LandTextureWH = 256;
const ULong UpdateTextureWH = 64;

const int D3DAPP_MAXDDDRIVERS = MAXCMODES;
const int D3DAPP_MAXD3DMODES = MAXCMODES;

const int D3DAPP_MAXD3DDRIVERS = 5;
const int D3DAPP_MAXTEXTUREFORMATS = 50;
const int D3DAPP_MAXTEXTURES = 15;

const int D3DAPP_EXECUTEBUFFERSIZE = 65536;
const int D3DAPP_EXECUTEBUFFERSAFETY = 16384;

const int D3DAPP_MAXSCENETRIANGLECOUNT =
			D3DAPP_EXECUTEBUFFERSIZE/
			(sizeof(D3DTRIANGLE)+3*sizeof(D3DTLVERTEX));		//PD 01Apr97

const int D3DAPP_MAXSCENEVERTEXCOUNT = 3*D3DAPP_MAXSCENETRIANGLECOUNT;

const int D3DAPP_VERTEXSAFETY = 32;
const int D3DAPP_TRIANGLESAFETY = 4;

const int D3DAPP_MAXVIDTEXTURES = 1024;

const int D3DAPP_MAXLINESCOUNT =
			D3DAPP_EXECUTEBUFFERSIZE/
			(sizeof(D3DLINE)+2*sizeof(D3DTLVERTEX));

const int D3DAPP_MAXPOINTSCOUNT =
			D3DAPP_EXECUTEBUFFERSIZE/
			(sizeof(D3DPOINT)+sizeof(D3DTLVERTEX));

typedef	struct	ViewData
{
	Float	originx,originy;
	Float	scalex,scaley;
	Float	D,F,h;
	Float	hoD,R;
	Float	FoR;												//PD 13Jun97
	Float	sD;													//PD 13Jun97
	Float	FogStart,
			FogEnd;
	Float	sqFogStart,
			sqFogEnd;
	Float	rangeFogConst;
	Float	clipTop,
			clipBot,
			clipLft,
			clipRgt;
	ANGLES	viewang;
}
ViewData;

class direct_draw;
class direct_3d;

typedef class direct_draw DirectDD,*DirectDDP;
typedef class direct_3d Direct3D,*Direct3DP;

typedef int	HTEXTURE;	//Rowan texture handle

const HTEXTURE R3DERR_CREATETEXTURE_FAILED 	= -1;
const HTEXTURE R3DERR_OUTOFTEXTURES 		= -2;

class direct_draw
{
	protected:

//------------------------------------------------------------------------------
//	STRUCTURE/CLASS DEFINITIONS
//------------------------------------------------------------------------------
//
// D3DAppD3DDriver structure
// Describes a D3D driver
//
	typedef
	struct D3DAppDDDriver
	{
    	char Name[30];      	/* short name of the driver */
	    char About[50];     /* short string about the driver */
	    GUID Guid;          /* it's GUID */
		ULong vidMem;		/* Total RAM available on the card */
	    BOOL bHardware3D;   /* does it have 3d hardware assist */
		BOOL bCanBltSysMem;	/* can this device support blitting to/from system memory */
		BOOL bDoesAsyncBlt; /* can it do asynchronous blit operations? */
	}
	DDAppD3DDriver;

//
// D3DAppD3DModes structure
// Describes graphics modes
// supported by a D3D driver
//
	typedef
	struct D3DAppD3DModes
	{
		int		Driver;		// -1 == Primary directdraw driver
		int		Width,		// width
				Height,		// height
				Bpp;		// colour depth

		DWORD	dwRedBits,	dwRedShift;
		DWORD	dwGreenBits,dwGreenShift;
		DWORD	dwBlueBits,	dwBlueShift;
	}
	D3DAppD3DModes;

//------------------------------------------------------------------------------
//	MEMBER VARIABLE DEFINITIONS
//------------------------------------------------------------------------------

	protected:

	LPDIRECTDRAW		lpDD;

	D3DAppDDDriver		Drivers[D3DAPP_MAXDDDRIVERS];
	D3DAppDDDriver		ThisDriver;
	D3DAppD3DModes		Modes[D3DAPP_MAXD3DMODES];
	D3DAppD3DModes		ThisMode;

	int	NumDrivers;
	int CurrDriver;
	int	NumModes;
	int CurrMode;
	int	CanDoHardware3D;

	ULong primaryDisplayDriverMem;
	BOOL bPrimaryDisplayDriverDoesHw3D;
	BOOL bButNotVeryWell;
	BOOL bFogVertexMode;
	BOOL bFogTableMode;

	BOOL primaryDoesAsyncBlt;
	BOOL primaryCanBltSysMem;

	public:

	UByte* softpallookup;

	LPDIRECTDRAW2	lpDD2;

//DEADCODE	int	EightBitOnly;

	bool fullScreenRequired;

//------------------------------------------------------------------------------
//	MEMBER FUNCTION DEFINITIONS
//------------------------------------------------------------------------------

	SWord				lockLevel;
	bool				gotShifts;
	ROWANSURFACEDESC	rsdGlobal;
	UWord				swRedMask,swGreenMask,swBlueMask;
	SWord				swRedSh1, swGreenSh1, swBlueSh1;
	SWord				swRedSh2, swGreenSh2, swBlueSh2;


	public:
  	
	CON	direct_draw();
	DES ~direct_draw();

	void MakePaletteFadeTable(struct _DirectDraw*,UByte*,UWord*,UByte,UByte,UByte);
	void MakeColourRangeFadeTable(struct _DirectDraw*,UWord*,UByte,UByte,UByte,UByte,UByte,UByte);
	void LockScr(struct _DirectDraw*,ROWANSURFACEDESC*);
	void UnlockScr(struct _DirectDraw*,ROWANSURFACEDESC*);
	void GetColourInfo(struct _DirectDraw*,
						UWord&,SWord&,SWord&,
						UWord&,SWord&,SWord&,
						UWord&,SWord&,SWord&);
	void GetSurfaceDimensions(struct _DirectDraw*,SLong&,SLong&);
	void SetSmackerMode(bool flag,HWND wnd);

	void GetModes(_DirectDraw&);

	BOOL SetMode(int mode);

	BOOL DriverDoesHardware3D();

	Bool ModeSupported(ScreenRez*);

	Bool DriverIsCapable(SWord);

	bool isFullScreen() {return fullScreenRequired;}

	void GetBltCaps(bool&,bool&);

	UByte* NameNumberedDriver(SWord);

	SWord CountDrivers();										//PD 27May97

	protected:

	static BOOL FAR PASCAL enumDDDrivers(	GUID FAR*,	LPSTR,
											LPSTR, 		LPVOID);
	static HRESULT WINAPI enumDisplayModes(	LPDDSURFACEDESC,	
											LPVOID);
	static HRESULT WINAPI enum3DDevices(	LPGUID,			LPSTR,
											LPSTR,			LPD3DDEVICEDESC,
											LPD3DDEVICEDESC,LPVOID);
};

class CPolyTree;

class direct_3d
{
	friend class CPolyTree;

	public:

	LPDIRECTDRAW2 pdd2Debug;

	protected:

	bool refreshTexture;

	CPolyTree* pPolyTree;

//------------------------------------------------------------------------------
//	MACRO DEFINITIONS
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	STRUCTURE/CLASS DEFINITIONS
//------------------------------------------------------------------------------

	struct SPeripheralPoly
	{
	 	R3DTLVERTEX v[4];
	};

	struct SPeripheralData
	{
		enum {MAX_PERIPHERAL_POLYS=32};

		SLong count;
		SPeripheralPoly polys[MAX_PERIPHERAL_POLYS];
	};

	SPeripheralData periphData;

//
// D3DAppD3DDriver structure
// Describes a D3D driver
//

	typedef
	struct D3DAppD3DDriver
	{
    	char Name[30];      /* short name of the driver */
	    char About[50];     /* short string about the driver */
    	D3DDEVICEDESC Desc; /* D3DDEVICEDESC for complete information */
	    GUID Guid;          /* it's GUID */
    	BOOL bIsHardware;   /* does this driver represent a hardware device? */
	    BOOL bDoesTextures; /* does this driver do texture mapping? */
    	BOOL bDoesZBuffer;  /* can this driver use a z-buffer? */
	    BOOL bCanDoWindow;  /* can it render to Window's display depth? */
		BOOL bDoesFogTable; /* supports FogTableMode */
		BOOL bDoesFogVertex;/* supports fog vertex mode */
		BOOL bDoesSrcOne;										//PD 06Oct97
		BOOL bDoesSrcSrcAlpha;									//PD 06Oct97
		BOOL bDoesDestInvSrcAlpha;								//PD 06Oct97
		BOOL bDoesDestZero;										//PD 06Oct97

		BOOL bDoesAllowZDisable;								//PD 13Oct97

		D3DTEXTUREFILTER	tfFilterMIN;						//PD 03Nov98
		D3DTEXTUREFILTER	tfFilterMAG;						//PD 03Nov98
		D3DTEXTUREFILTER	tfFilterMSK;						//PD 23Nov98
		D3DTEXTUREBLEND		tbBlendMode;						//PD 09Sep98
	}
	D3DAppD3DDriver;

//
// D3DAppTextureFormat stucture
// Describes a texture format
//
	typedef
	struct D3DAppTextureFormat
	{
    	DDSURFACEDESC ddsd; /* DDSURFACEDESC for complete information */
    	bool bPalettized;   /* is this format palettized */
    	int RedBPP;         /* number of red, */
    	int BlueBPP;        /*           blue, */
    	int GreenBPP;       /*           green, */
		int AlphaBPP;		/*			 alpha bits per pixel */
    	int IndexBPP;       /* number of bits in palette index */

		int	RedShift;
		int	BlueShift;
		int GreenShift;
		int	AlphaShift;
	}
	D3DAppTextureFormat;

	typedef
	struct D3DTexture
	{
		D3DTEXTUREHANDLE	thandle;
		LPDIRECTDRAWSURFACE	lpTSurface;
		LPDIRECT3DTEXTURE	lpTexture;
	}
	D3DTexture;

	typedef UWord	RGB16,*LPRGB16;

	typedef
	struct D3DBackgroundMaterial
	{
		D3DMATERIALHANDLE	hMaterial;
		LPDIRECT3DMATERIAL	lpMaterial;
		D3DMATERIAL			MaterialDesc;
	}
	D3DBackgroundMaterial;

	typedef
	struct D3DMaterial
	{
		D3DTEXTUREHANDLE	hTexture;
		D3DCOLOR			dcColorVal;
		RGB16				dcColorVal16;
	}
	D3DMaterial;

	public:
	typedef
	struct R3DPal
	{
		UByte r,g,b;
	}
	R3DPal,*R3DPalP;

	protected:
	struct VidRamTexture;

	typedef	struct VidRamTexture VIDRAMTEXTURE, *LPVIDRAMTEXTURE;

	struct VidRamTexture
	{
		LPVIDRAMTEXTURE	lpOlderTexture;
		LPVIDRAMTEXTURE lpNewerTexture;
		ImageMapDescPtr lpImageMap;
		UWord			bInUse;
		UWord			bPlayerTexture;
		UWord			dwHeight;
		UWord			dwWidth;
		bool			bHasAlpha;
		bool			bIsMasked;
		bool			pixelFormat;
		Float			fWidth;
		Float			fHeight;
		UWord			mipMapLevels;

		//	Direct 3D bits

		LPDIRECTDRAWSURFACE	lpdds1TSurf;
		LPDIRECTDRAWSURFACE2 lpdds2TSurf;
		LPDIRECT3DTEXTURE	lpd3dTexture;
		D3DTEXTUREHANDLE	d3dhTexture;
		void*				pSurface;

		VidRamTexture() {lpOlderTexture=lpNewerTexture=NULL;bInUse=0;mipMapLevels=0;}
		inline VidRamTexture(ImageMapDescPtr p);
	};

	struct EDVidTex
	{
		LPDIRECTDRAWSURFACE pdds;
		LPDIRECTDRAWSURFACE2 pdds2;
		LPDIRECT3DTEXTURE pd3dt;
		D3DTEXTUREHANDLE d3dht;
		EDVidTex() {pdds=NULL;pdds2=NULL;pd3dt=NULL;d3dht=NULL;}
	};

	struct SExtraDetail
	{
		enum {MAX_IMAGES=8,MAX_AREAS=16};

		//animation control variables

		SLong timerReset;
		SLong timerCur;

		//texture info

		SLong numTextures;
		SLong curTexture;

		ImageMapDesc* 	images[MAX_IMAGES];
		EDVidTex 		vidTex[MAX_IMAGES];

		//land area type info

		SLong numAreas;

		AreaType areaTypes[MAX_AREAS];

		SExtraDetail() {}
		SExtraDetail(	SLong numT,ImageMapNumber* pNums,
						SLong numA,AreaType* pAreas,
						SLong tReset=0);
	};

	SLong numExtraDetails;
	SExtraDetail* extraDetails[32];

	#define	USED_BYCLIPPED		0x00000001
	#define	USED_BYUNCLIPPED	0x00000002

	struct TriangleDesc;

	typedef struct TriangleDesc TRIANGLEDESC, *LPTRIANGLEDESC;

	struct TriangleDesc
	{
		PolyType::PolyTypes	ptType;

		union
		{
			Colour				colour;
			ImageMapNumber		nID;
			D3DTEXTUREHANDLE 	hTexture;
		};

		ImageMapDescPtr		lpImageMap;

		LPVIDRAMTEXTURE		lpVidramtexture;

		int			nVertexIndex[3];

		int			wFlags;
	};

	struct LineDesc;

	typedef struct LineDesc LINEDESC, *LPLINEDESC;

	struct LineDesc
	{
		LineType::LineTypes	ltType;
		Colour				colour;
		int					nVertexIndex[2];
	};

	struct PointDesc;

	typedef struct PointDesc POINTDESC, *LPPOINTDESC;

	struct PointDesc
	{
		PointType::PointTypes	ptType;
		Colour					colour;
		int						nVertexIndex[1];
	};

//------------------------------------------------------------------------------
//	MEMBER VARIABLE DEFINITIONS
//------------------------------------------------------------------------------

	protected:

	Float	aspectRatio;
	Float	recipAspectRatio;
	Float	FoV;
	Float	rFoV;

	Float	fMaxVisRange;
	Float	fZBufScaleSwitchRange;
	Float	frMaxVisRange;
	Float	fConeGradient;

	ULong	TextureRAMFree;

	ULong	fontColour;

	ULong	maxVertexCount;

	PALETTEENTRY	peSrcPalette[256];
	LPPALETTEENTRY	lppeSrcPalPtr;

	int	NumVidTextures;

	VIDRAMTEXTURE 	vidramtextures[D3DAPP_MAXVIDTEXTURES];
	LPVIDRAMTEXTURE	lpOldestTexture,
					lpNewestTexture;

	VIDRAMTEXTURE* vidramlandptr[_landscapeTextures];
	VIDRAMTEXTURE* sysramlandptr[_landscapeTextures];

	VIDRAMTEXTURE vidramlandmaps[_landscapeTextures];
	VIDRAMTEXTURE sysramlandmaps[_landscapeTextures];

	//new landscape stuff

	enum {NUM_SCALES=6};

	SLong	NUM_256_TEXTURES,	NUM_128_TEXTURES,
			NUM_64_TEXTURES,	NUM_32_TEXTURES,
			NUM_16_TEXTURES,	NUM_8_TEXTURES;

	VIDRAMTEXTURE* vidram256maps;
	VIDRAMTEXTURE* vidram128maps;
	VIDRAMTEXTURE* vidram64maps;
	VIDRAMTEXTURE* vidram32maps;
	VIDRAMTEXTURE* vidram16maps;
	VIDRAMTEXTURE* vidram8maps;
	VIDRAMTEXTURE sysramALLmaps[NUM_SCALES];
	VIDRAMTEXTURE vidramdithermap;

	D3DTEXTUREHANDLE ditherHandles[32];

	UByte* landTextureUsage;

	VIDRAMTEXTURE* pFanTexture;
	ImageMapDescPtr pFanMapDesc;

    int     NumDrivers;    // number of D3D drivers avail.
    int		CurrDriver;    // number of curr. D3D driver

	int		D3DAppExecuteBufferSize;

    D3DAppD3DDriver         Driver[D3DAPP_MAXD3DDRIVERS]; // avail. drivers

    D3DAppD3DDriver         ThisDriver;    // description of this driver,
                                      	   // identical to Driver[CurrDriver]

    int	NumTextureFormats; // num texture formats avail

	// description of all avail. formats

    D3DAppTextureFormat     TextureFormat[D3DAPP_MAXTEXTUREFORMATS];

	D3DAppTextureFormat		opaqueTexture,
							transpTexture,
							maskedTexture;

    int	NumTextures;    // number of textures in D3DApp's
                        // texture list

	D3DTexture	Textures[D3DAPP_MAXTEXTURES];

    int                     NumUsableTextures; 					/* the number of
																	currently usable
                                              						textures (e.g. for a hardware
                                               						device there may not be enough
                                               						video memory*/

	D3DMaterial		palette[256];		//Standard 256 colour palette as D3D materials

	D3DBackgroundMaterial	backgroundMaterial;

	SLong	CurrMaxVisRange;
	ANGLES	CurrViewAng;

	SLong	CurrFogStart;
	SLong	CurrFogEnd;
	D3DCOLOR	CurrFogColour;

	bool fMipMap,fBilinear;

	Bool	bPlayerTextures;
	BOOL	bGlobalFogFlag;										//PD 09Oct97
	BOOL	globalSpecular;
	BOOL	globalLighting;
	Bool	bCantLockZBuffer;									//DAW 21Oct97
	bool	bItemFoggingActive;
	UByte	itemFogVal;
	Bool	currZWriteState;

	enum	TextureQuality {TQ_Low=0,TQ_High=4};

	SWord	textureQuality;

	public:

    LPDIRECT3D              lpD3D;         // D3D object
    LPDIRECT3DDEVICE        lpD3DDevice;   // D3D device
    LPDIRECT3DVIEWPORT      lpD3DViewport; // D3D viewport, created by
	                                       // application

	enum {MAX_PALS=8};											//RJS 19Mar98

	UByte lastPals[256*3];

	UByte specRed,specGreen,specBlue;

	LPDIRECTDRAWPALETTE		lpDDPalette[MAX_PALS];				//PD 06Mar98
	UByteP					lpDDPalLookup[MAX_PALS];			//PD 06Mar98
	UByteP					lpDMPalLookup[MAX_PALS];			//PD 06Mar98
    LPDIRECT3DLIGHT			lpD3DLight;
	LPDIRECTDRAWSURFACE		lpZBuffer;							//PD 21Feb97

	LPDIRECTDRAWPALETTE	lpDDLandPal;
	UByteP				lpDDLandPalLookup;
	UByteP				lpDDTLandPalLookup;

	D3DEXECUTEBUFFERDESC	GlobalExecuteBufferDesc;			//PD 20Mar97

	SLong	CurrentFadeStep;									//PD 05Jun97
	Colour	TargetFadeColour;									//PD 05Jun97

	UByte	fadeRed,fadeGreen,fadeBlue;

	SWord	nWhichLandPalette;

	D3DCOLOR	dcGlobalFogColour;
	Float		fogRedVal,fogGreenVal,fogBlueVal;

	UWord		fakeRHWControl;

	Bool		bFirstTime;							//PD 17Apr97
	Bool		bBackClipEnabled;					//PD 05Jun97
	bool		fMipMapEnabled;

	UByte		AmbientALPHA;						//PD 24Jun97
	UByte		globalAlphaValue;

	SLong		vShadeRed;
	SLong		vShadeGreen;
	SLong		vShadeBlue;

	SLong		vEffectsRed;
	SLong		vEffectsGreen;
	SLong		vEffectsBlue;

	SLong		vNormalRed;
	SLong		vNormalGreen;
	SLong		vNormalBlue;

	bool		isLightShaded;
	bool		isTranspFade;
	bool		rangeFogEnabled;
	SLong		textureUploads;
	bool		clipTestEnabled;
	bool		lightingEffectsEnabled;
	ULong		winWidth,winHeight;

	bool driverDoesAsyncBlt;
	bool driverDoesSysMemBlt;
	bool fullScreen;											//PD 21Aug98
	bool fEdgeTestActive;

	enum PTYPE {T_NONE=0,T_PLAIN,T_TEXT,T_MASKED,T_TRANSP};

	PTYPE lastPolyType;

//------------------------------------------------------------------------------
//	MEMBER FUNCTION DEFINITIONS
//------------------------------------------------------------------------------

	public:

	void RegisterPalette(struct _DirectDraw*,UByte*,ULong);

	void SetAspectRatio(Float ar,Float fov)
	{
		aspectRatio=ar;
		recipAspectRatio=1./ar;
		FoV=fov;
		rFoV=1./FoV;
	}

	bool SetEdgeTest(bool);

	//-------------------------------
	// Initialisation/Close down code
	//-------------------------------

	CON	direct_3d(struct _DirectDraw* lpdirectd=NULL);

	DES ~direct_3d();

	BOOL SelectDriver(struct _DirectDraw*);

	void CloseDown();

	//-------------------------------
	// Scene managemant methods
	//-------------------------------

	inline bool SetLShade(bool newval)
	{
	 	bool oldval=isLightShaded;
		isLightShaded=(newval&&globalLighting)?true:false;
		return oldval;
	}

	void CalcItemFog(bool,Float&,Float&,Float&);

	bool SetTranspFade(bool);

	inline bool SetRangeFog(bool newval) {bool oldval=rangeFogEnabled;rangeFogEnabled=newval; return oldval;}

	void SetShadeVals(SLong,SLong,SLong,SLong,SLong,SLong);

	void BeginScene(struct _DirectDraw*);

	void EndScene(struct _DirectDraw*);
	void End3DScene(struct _DirectDraw*);

	void ClearViewport(struct _DirectDraw*,Bool);				//PD 10Jun97

	void SetTextureQuality(struct _DirectDraw*,bool);

	void SetFadeValue(UByte);									//PD 07Jun97

	void TestHW3D(struct _DirectDraw*,Window*);					//PD 23Sep97

	UByte CALC_RANGE_FOG(Float,Float,Float);

	void SetFogState(Bool );									//PD 09Oct97

	//-------------------------------
	// Texture manipulation methods
	//-------------------------------

	void MakePALLookup(D3DAppTextureFormat&,UByte*&,R3DPalP); 	//PD 23Feb98

	void SetPalette(struct _DirectDraw*,UByte*);

	void SetFade(Colour,SLong,TwoDeeEffect);									//PD 05Jun97

	Bool EnableBackClip(Bool);									//PD 05Jun97

	void GammaCorrectRGB(R3DPalP,Float);

	void CreateLandscapePalette(struct _DirectDraw*);

	void SetColorKey(DWORD,LPVIDRAMTEXTURE lpVRT=NULL);

	void MakePaletteMods(R3DPalP);

	UWord TranslateColour16(Colour);

	LPVIDRAMTEXTURE TextureLoaded(VIDRAMTEXTURE&);
	void PrepTexture(LPDIRECTDRAWSURFACE2,DDSURFACEDESC&,VIDRAMTEXTURE&,int);
	void PrepMipMap(LPDIRECTDRAWSURFACE2,DDSURFACEDESC,VIDRAMTEXTURE&);
	int SetTextureScale(VIDRAMTEXTURE&);

	LPVIDRAMTEXTURE	CreateTexture(	ImageMapDescPtr,
									struct _DirectDraw*,
									bool fRefresh=false);

	void RemakeTexture(struct _DirectDraw*,ImageMapDescPtr,LPVIDRAMTEXTURE,int);

	void ReleaseTextures();

	DWORD GetAvailableTextureRAM(LPDIRECTDRAW2);


	//-------------------------------
	// Primitive rendering code 
	//-------------------------------

	inline Float MAKE_SZ(Float);
	inline Float MAKE_RHW(Float);

	void SetViewParams(ANGLES,Window*,struct _DirectDraw*);
	
	BOOL InitView(struct _DirectDraw*);

	void SetFog(UByte,UByte,UByte,SLong,SLong);
	void SetFog(UByte,UByte,UByte);
	void GetFog(UByte&,UByte&,UByte&,SLong&,SLong&);

	BOOL SetMatrices(struct _DirectDraw*,SLong,ANGLES); //View range/angle

	Bool SetZUpdate(struct _DirectDraw*,Bool);

	Bool SetPlayerTextures(struct _DirectDraw*,Bool);

	void ForceRender(struct _DirectDraw*);
	UByte SetGlobalAlpha(UByte);
	bool SetClipState(bool);

	void SmokedGlassBox(struct _DirectDraw*,SWord,SWord,SWord,SWord,ULong);

	void FlushLandscapeBuffers(struct _DirectDraw*);

	void Body2Screen(DoPointStruc&);

	void AddPlainLine(		struct _DirectDraw*,
							LPLINETYPE);

	void AddPlainPoint(		struct _DirectDraw*,
							LPPOINTTYPE);

	void AddTexturedPoly(	struct _DirectDraw*,
							LPPOLYTYPE);

	void AddPlainPoly(		struct _DirectDraw*,
							LPPOLYTYPE);

	void AddDebugPoly(	struct _DirectDraw*,
							LPPOLYTYPE);

	SWord ForceTQ(SWord);

	void BeginFan(ULong);
	void BeginFan(struct _DirectDraw*,ImageMapDesc*);
	void AddFanPoint(struct _DirectDraw*,DoPointStruc*,SLong,UByte*&);

	void AddGouraudPoly(struct _DirectDraw*,LPPOLYTYPE);

	void FlushAll(struct _DirectDraw*,Bool);					//PD 28Oct98

	void UploadLandTexture(struct _DirectDraw*,ULong,ImageMapDesc*);
	//------------------------
	// Specail effects
	//------------------------

	void Add2DEffect(struct _DirectDraw* lpDirectD,TWODEFFECT tdeEffect);//PD 02Jun97
	void FadeIn2Out(SLong);
	void FadeOut2In(SLong);
	void FadeUniform(SLong);

	protected:

	BOOL EnumDevices();

	static HRESULT WINAPI enumDeviceFunc(	LPGUID,			LPSTR,
											LPSTR,			LPD3DDEVICEDESC,
											LPD3DDEVICEDESC,LPVOID);

	BOOL VerifyDriver(int);

	BOOL CreateDevice(int,struct _DirectDraw*);

	BOOL EnumTextureFormats();

	static HRESULT CALLBACK enumTextureFormat(LPDDSURFACEDESC, LPVOID);

	void InitPaletteData();

	void MakeNewest(LPVIDRAMTEXTURE lpVRT)
	{
		//Remove this texture from the current 
		//list if it is already in

		//if (lpVRT==lpNewestTexture) return;

		if (lpVRT->lpNewerTexture!=NULL)
			lpVRT->lpNewerTexture->lpOlderTexture=lpVRT->lpOlderTexture;

		if (lpVRT->lpOlderTexture!=NULL)
			lpVRT->lpOlderTexture->lpNewerTexture=lpVRT->lpNewerTexture;

		if (lpOldestTexture==lpVRT)
			lpOldestTexture=lpVRT->lpNewerTexture;

		//Add this texture to the head of the list

		lpVRT->lpNewerTexture=NULL;

		if (lpNewestTexture!=NULL)
		{
			lpNewestTexture->lpNewerTexture=lpVRT;
			lpVRT->lpOlderTexture=lpNewestTexture;
			lpNewestTexture=lpVRT;
		}
		else
			lpNewestTexture=lpVRT;

		if (lpOldestTexture==NULL)
			lpOldestTexture=lpVRT;
	};

	void UnlinkTexture(LPVIDRAMTEXTURE lpVRT)
	{
		//Remove this texture from the current 
		//list if it is already in

		if (lpVRT->lpNewerTexture!=NULL)
			lpVRT->lpNewerTexture->lpOlderTexture=lpVRT->lpOlderTexture;

		if (lpVRT->lpOlderTexture!=NULL)
			lpVRT->lpOlderTexture->lpNewerTexture=lpVRT->lpNewerTexture;

		if (lpNewestTexture==lpVRT)
			lpNewestTexture=lpVRT->lpOlderTexture;

		if (lpOldestTexture==lpVRT)
			lpOldestTexture=lpVRT->lpNewerTexture;

		lpVRT->lpNewerTexture = NULL;
		lpVRT->lpOlderTexture = NULL;
	}

	void CreateExecuteBuffer();

	void ReleaseExecuteBuffer();

	void CreateLandTextureBuffers(struct _DirectDraw*);
	void ReleaseLandTextureBuffers();
	void PrepLandMap(VIDRAMTEXTURE&,ImageMapDesc*);
	struct XBuf
	{
		//no longer global constants!
		ULong _xbuffer_size;
		ULong _max_verts;
		ULong _inst_start;
		ULong _inst_len;

		D3DEXECUTEBUFFERDESC xbDesc;
		LPDIRECT3DEXECUTEBUFFER pxBuf;
		ULong vertCount;
		ULong instOffset;
		bool	bLocked;
	};

	struct XXBuf:public XBuf
	{
		BufferUse bufUse;
	};

	struct LXBuf:public XBuf
	{
		LPD3DPROCESSVERTICES pPV;
	};

	inline void	RClipToFront(R3DTLVERTEX*,R3DTLVERTEX*,R3DTLVERTEX*);
	inline void RClipToBack(R3DTLVERTEX*,R3DTLVERTEX*,R3DTLVERTEX*);
	inline void RClipToEast(R3DTLVERTEX*,R3DTLVERTEX*,R3DTLVERTEX*);
	inline void RClipToWest(R3DTLVERTEX*,R3DTLVERTEX*,R3DTLVERTEX*);
	inline void RClipToTop(R3DTLVERTEX*,R3DTLVERTEX*,R3DTLVERTEX*);
	inline void	RClipToBottom(R3DTLVERTEX*,R3DTLVERTEX*,R3DTLVERTEX*);
	void GenericPolyClip(ULong&,R3DTLVERTEX**,R3DTLVERTEX*&,R3DTLVERTEX*);
	SWord GenericLineClip(R3DTLVERTEX&,R3DTLVERTEX&);
	void FlushPTDraw(struct _DirectDraw*,struct XXBuf&);
	void FlushPCDraw(struct _DirectDraw*,struct XBuf&);

	void FlushPLDraw(struct _DirectDraw*,struct LXBuf&);
	void FlushPPDraw(struct _DirectDraw*,struct LXBuf&);

	void FreeExecuteBuffers();

	XXBuf landXB;		//normal unclipped land tiles
	XBuf plainXB;		//plain color land tiles
	XBuf nearlndXB;		//near land execute buffer

	XXBuf clandXB;		//clipped version of landXB
	XBuf cnearlndXB;	//clipped version of nearlndXB

	XBuf ditherlndXB;		//near dither land execute buffer
	XBuf cditherlndXB;		//clipped version of ditherlndXB

	XBuf plaincXB;		//for plain color polygons

	XXBuf transpXXB;	//for transparent polygons
	XXBuf maskedXXB;	//for masked polygons
	XXBuf normalXXB;	//for normal texture mapped polygons

	XXBuf nzbufXXB;		//for non z-buffered polys
	XXBuf fontXXB;		//font execute buffer

	LXBuf lineXB;		//for lines
	LXBuf pointXB;		//for points

	public:

	void CreateLandExecuteBuffer();

	void FlushLandDraw(struct _DirectDraw*,struct XBuf&);

	void AddTileVertices(	struct _DirectDraw*,
							ULong,
							ULong,
							DoPointStruc*,
							ULong,
							UByte*&);

	void CAddTileVertices(	struct _DirectDraw*,
							ULong,
							ULong,
							DoPointStruc*,
							ULong,
							UByte*&);

	void NearAddTileVertices(	struct _DirectDraw*,
								ULong,
								ULong,
								DoPointStruc*,
								ULong,
								UByte*&,
								ULong);

	void CNearAddTileVertices(	struct _DirectDraw*,
								ULong,
								ULong,
								DoPointStruc*,
								ULong,
								UByte*&,
								ULong);

	void NearAddTileVerticesX(	struct _DirectDraw*,
								ULong,
								ULong,
								DoPointStruc*,
								ULong,
								UByte*&,
								const HTEXT&,
								UWord);

	void CNearAddTileVerticesX(	struct _DirectDraw*,
								ULong,
								ULong,
								DoPointStruc*,
								ULong,
								UByte*&,
								const HTEXT&,
								UWord);

	void NearAddTileVerticesX2(	struct _DirectDraw*,
								ULong,
								ULong,
								DoPointStruc*,
								ULong,
								UByte*&,
								const HTEXT&,
								UWord);

	void CNearAddTileVerticesX2(	struct _DirectDraw*,
								ULong,
								ULong,
								DoPointStruc*,
								ULong,
								UByte*&,
								const HTEXT&,
								UWord);

	void NearAddTileDitherX(	struct _DirectDraw*,
								ULong,
								ULong,
								DoPointStruc*,
								ULong,
								UByte*&);

	void CNearAddTileDitherX(	struct _DirectDraw*,
								ULong,
								ULong,
								DoPointStruc*,
								ULong,
								UByte*&,SLong);

	void SingleClipResult(	DoPointStruc*,DoPointStruc*,
							DoPointStruc*);

	inline void InsFan(ULong,UByte*,ULong,UByte*,void*&);
	inline void InsStrip(ULong,UByte*,ULong,UByte*,bool,void*&);

	void DumpXBuffer(XBuf& xb);
	inline void SetVertexColor(R3DTLVERTEX*,DoPointStruc*);

	inline void ResetBufferUse(BufferUse&);
	bool RecordTextureUse(ImageMapDescPtr,UWord*&,BufferUse&);
	void WipeLastTexture(ImageMapDescPtr,BufferUse&);
	void RegisterTextureUse(struct _DirectDraw*,BufferUse&,void*);
	inline void SetupExecuteBuffer(LPDIRECT3DDEVICE,ULong size,XBuf* pxb);
	void SetInitialRenderStatesPlain(XBuf* pxb);
	void SetInitialRenderStatesTextured(XBuf* pbx);
	void SetInitialRenderStatesLand(XBuf* pbx);
	void SetInitialRenderStatesFont(XBuf* pbx);
	void SetInitialRenderStatesTransp(XBuf* pxb);
	void SetInitialRenderStatesMasked(XBuf* pxb);

	void SetInitialRenderStatesLines(LXBuf* pxb);
	void SetInitialRenderStatesPoints(LXBuf* pxb);

	void CreateLandTBuffers(struct _DirectDraw*);
	void CreateLandTBuffers2(struct _DirectDraw*);
	void* GetLandBufferPtr(struct _DirectDraw*,SWord);
	void* GetLandPalLookup(struct _DirectDraw*);
	void SetLandPalLookup(struct _DirectDraw*,UByte*);
	SWord GetLandBpp(struct _DirectDraw*);
	void BeginTextureScroll(struct _DirectDraw*,const SWord,void*,void*);
	void WaitTextureScrollComplete(struct _DirectDraw*,const SWord);
	void PartialTextureUpload(struct _DirectDraw*,const SWord,void*,void*);
	bool TestAsyncBlt() {return driverDoesAsyncBlt;}

	void NewTile(struct _DirectDraw*,SLong,DoPointStruc*,SLong,UByte*,SLong);
	void CNewTile(struct _DirectDraw*,SLong,DoPointStruc*,SLong,UByte*,SLong);

	//new landscape bits

	void RenderTileToDDSurface(struct _DirectDraw*,UByte*,const HTEXT&);
	void FreeTexture(const HTEXT&);
	void FreeTextures();
	HTEXT AllocateTexture(UByte);
	void GetTextureScales(SLong&,SLong&,SLong&,SLong&,SLong&,SLong&);
//DeadCode PD 20Apr99 	void GetSurfaceDimensions(struct _DirectDraw*,SLong&,SLong&);
	void PutC(struct _DirectDraw*,ImageMapDesc*,DoPointStruc*,bool fRefresh=false);
	void PutA(struct _DirectDraw*,ImageMapDesc*,DoPointStruc*);
	void PutLine(struct _DirectDraw*,SWord,SWord,SWord,SWord,Colour);
	void SetFontColour(ULong a) {fontColour=a;}
	void UpdateFromPrefs();
	void PeripheralBlob(Float*,Float*,Float*,UByte,SLong);
	void RenderPeripheralBlobs(struct _DirectDraw*,struct XXBuf&);
	void AddPoly(struct _DirectDraw*,LPPOLYTYPE);
	void AddPoly2(struct _DirectDraw*,LPPOLYTYPE);
	inline bool PolyCross(LPPOLYTYPE);
	inline bool PolySplit(LPPOLYTYPE);

	inline void SaveClipFlags(LPPOLYTYPE);
	inline void RestoreClipFlags(LPPOLYTYPE);
	inline void UpdateClipFlagsFrontChanged(LPPOLYTYPE);
	inline void UpdateClipFlagsBackChanged(LPPOLYTYPE);

	inline bool TileSplit(ULong,DoPointStruc *);
	inline void SaveClipFlags(ULong,DoPointStruc *);
	inline void RestoreClipFlags(ULong,DoPointStruc *);
	inline void UpdateClipFlagsFrontChanged(ULong,DoPointStruc *);
	inline void UpdateClipFlagsBackChanged(ULong,DoPointStruc *);

	void AddPlainPolyNZ(LPPOLYTYPE,XXBuf&);
	void WriteStateChanged(struct _DirectDraw*,XXBuf&,PTYPE,PTYPE);
	void FlushNZDraw(struct _DirectDraw*,struct XXBuf&);
	void AddTexturedPolyNZ(LPPOLYTYPE,XXBuf&,UWord*,bool);
	void RestoreZWriteState(XBuf*);
	bool SetMipMap(bool );
	void SetSunPos(DoPointStruc& );
	void CreateDitherMap(struct _DirectDraw*);
	void FlushDitherDraw(struct _DirectDraw*,struct XBuf&);
	void SetupExtraLandDetail(struct _DirectDraw*);
	void FreeExtraLandDetail();
	void UpdateLandDetailAnimFrames(SLong);
	bool EdgeOnTest(LPPOLYTYPE,bool&);
	void AddLineInstead(struct _DirectDraw*,LPPOLYTYPE,bool);
	void RenderPolyCallback(struct _DirectDraw*,LPPOLYTYPE);
	void RenderPolyCallback2(struct _DirectDraw*,LPPOLYTYPE);
	void GammaCorr(UByte& r,UByte& g,UByte& b);
	ULong AvailableTextureRAM(struct _DirectDraw*);
	void InitialiseVideoBuffer(struct _DirectDraw*);
	void ReleaseVideoBuffer();
	void CaptureScreen(struct _DirectDraw*);
	void SaveVideoBuffer(struct _DirectDraw*);
	void D2DLine(struct _DirectDraw*,UWord,UWord,UWord,UWord);
	void ShowLoaderArt(struct _DirectDraw*,void*);
	void PushPull(UByte);
	void EatTextureRAM(struct _DirectDraw* pdirectd,ULong ramSize);
	bool decreaseTextureQuality;
	bool ScanForBottomPixelsOfText(struct _DirectDraw*,SWord,SWord,SWord);
	void PushViewData(struct _DirectDraw *);
	void PopViewData(struct _DirectDraw *);
	void Set3DWin(struct _DirectDraw *,SLong,SLong,SLong,SLong);
};

// Macro that should dump an objects current reference count
// to the debugger log window

#define DEBUGREFCOUNT(lpInterface)

#undef	RELEASE

#define	RELEASE(lpInterface,hrError)					\
		if ((lpInterface)!=NULL){						\
			DEBUGREFCOUNT((lpInterface));				\
			(hrError) =									\
			(lpInterface)->Release();					\
			(lpInterface)=NULL;							\
		}												\

#ifndef	NDEBUG

#define	DEBUGTEXT(p1)			\
		OutputDebugString(p1);

#else

#define	DEBUGTEXT(p1)

#endif

#ifndef		NDEBUG

#ifndef INWIN3D
extern	void DDErrorCodes(char*,int,HRESULT);
extern	void D3DErrorCodes(char*,int,HRESULT);
#endif

#define		DIRECTDRAWERROR(p1)						\
			if ((SLong)DD_OK>(SLong)(p1))			\
				DDErrorCodes(__FILE__,__LINE__,(p1));	

#define		DIRECT3DERROR(p1)						\
			if ((SLong)D3D_OK>(SLong)(p1))			\
				D3DErrorCodes(__FILE__,__LINE__,(p1));

#else

#define		DIRECTDRAWERROR(p1)

#define		DIRECT3DERROR(p1)

#endif

#endif
