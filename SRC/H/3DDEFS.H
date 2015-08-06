//------------------------------------------------------------------------------
//Filename       3ddefs.h
//System         
//Author         Paul.   
//Date           Mon 16 Oct 1995
//Description    
//------------------------------------------------------------------------------
#ifndef	D3DDEFS_Included
#define	D3DDEFS_Included

		#include	"Palette.h"

#define	DEFAULT_D3DDEFS 0

#define	ZPlane	0x00010000
#define	ZMask	0xFFFF0000

enum	TRANSPARENCYTYPE										//RJS 17Jun97
{																//RJS 17Jun97
	SMOKED_INVISIBLE = 0x00,									//RJS 27Mar98
	SMOKED_LIGHT = 63,											//RJS 27Mar98
	SMOKED_ON = 127,											//RJS 27Mar98
	SMOKED_DARK = 191,											//RJS 27Mar98
	SMOKED_SOLID = 255,											//RJS 27Mar98
	SMOKED_OFF = 255											//RJS 27Mar98
};

enum	LUMINOSITYTYPE											//RJS 19Jan98
{																//RJS 19Jan98
	LUM_OFF = 0x00,												//RJS 19Jan98
	LUM_ONE,													//RJS 19Jan98
	LUM_TWO,													//RJS 19Jan98
	LUM_THREE,													//RJS 19Jan98
	LUM_FOUR,													//RJS 19Jan98
	LUM_FIVE,													//RJS 19Jan98
	LUM_SIX,													//RJS 19Jan98
	LUM_SEVEN,													//RJS 19Jan98
	LUM_MAX														//RJS 19Jan98
};																//RJS 19Jan98

enum	ObjectType	{GROUND_TILE_OBJECT=0,
//DEAD					NRGRND_TILE_OBJECT,							//PD 18Mar96
//DEAD					SKY_TILE_OBJECT,
//DEAD					HORIZON_TILE_OBJECT,
					STATIC_OBJECT,
					MOBILE_OBJECT,
					POSSMOVE_OBJECT,							//PD 15Oct96
					SHADOW_OBJECT,								//RJS 07May97
					SMOKE_OBJECT,								//RJS 08Sep97
					COCKPIT_OBJECT,
					MAP_OBJECT,									//RJS 08Sep98
					SHADEOVERRIDE_OBJECT,
					SPECIAL_TILE_OBJECT,
					XXX_DUMMYTYPE = 0x07FFF						//PD 23Aug96
					};

enum	TDFadeType	{_BLACKOUT = 0,_REDOUT,_WHITEOUT,_NOWTOUT};	//PD 27Nov96

class	fileblock;								//RJS 06Feb98

struct	ImageMap_Desc											//PD 05Dec95
{																//PD 05Dec95
//DeadCode RJS 06Feb98 	UByte	height:4,											//PD 12Jan96
//DeadCode RJS 06Feb98 			width:4;											//PD 12Jan96
//DeadCode RJS 06Feb98 	UByte	data;												//PD 05Dec95

	UWord	w, h;												//RJS 06Feb98
	UByteP	body;												//RJS 06Feb98
	UByteP	alpha;												//RJS 24Feb98
	UByteP	palette;											//RJS 24Feb98
	UByte	paletteindex:7,										//RJS 26Mar98
			isMasked:1;											//RJS 26Mar98

	void	FixLbmImageMap(fileblock* fblockptr);
	void	InitFont(int, int, int);									//RJS 4Dec00
	void	MakeChar(int, int, int);					//RJS 4Dec00

	CON	ImageMap_Desc()
	{
	  	w=h=0;
		body = palette = alpha = NULL;
		paletteindex = 0;										//RJS 24Feb98
		isMasked = 0;											//RJS 26Mar98
	};

	DES	~ImageMap_Desc()
	{

		delete []body;
		delete []palette;
		delete []alpha;

		body = palette = alpha = NULL;
		paletteindex = 0;										//RJS 24Feb98
		isMasked = 0;											//RJS 26Mar98
	};

	static ImageMap_Desc* initsafe( const int& width, const int& height ,bool hasAlpha=false)
	{ 
		ImageMap_Desc* toCreate;
		if ( !hasAlpha )
		{
		    toCreate = new ImageMap_Desc;
			toCreate->body = new UByte [ width*height ];
			toCreate->_initsafe( width, height );

		} else
		{
			toCreate = new ImageMap_Desc;
			toCreate->_initsafe( width, height );
			toCreate->body = new UByte[ width*height ];
			toCreate->alpha = new UByte[ width*height ];
		}
		return toCreate;
	}

private:
	
	void _initsafe( const int& width, const int& height )
	{ 
		w = width;
		h = height;
		palette = alpha = NULL;
		paletteindex = 0;										//RJS 24Feb98
		isMasked = 0;											//RJS 26Mar98
	}

};																//PD 05Dec95

typedef struct 	ImageMap_Desc									//PD 01Aug96
				ImageMapDesc,									//PD 01Aug96
				*ImageMapDescPtr;								//PD 01Aug96

enum	TileSeg
		{
			TS_Whole=0,
			TS_TopLeft,
			TS_TopRight,
			TS_BottomLeft,
			TS_BottomRight,
			TS_NotATileMap,
			TileSeg_Align=255};//PD 27Aug96

struct	LandMapDesc												//PD 27Aug96
{
	TileSeg			tileseg;
//	SLong			tileinvidram;								//PD 10Mar97
	ImageMapDesc	tilemap;
};

typedef	struct LandMapDesc *LandMapDescPtr;						//PD 27Aug96

struct	Base_Obj3D;
struct	Land_Obj;
struct	Vert_Ex;
struct	Obj_3D;

typedef	struct 	Base_Obj3D 	BaseObj3D,	*BaseObj3DPtr;
typedef	struct	Land_Obj 	LandObj3D,	*LandObj3DPtr;
typedef struct	Obj_3D		Obj3D,		*Obj3DPtr;
//DEAD typedef struct	Vert_Ex	 	landvertex,	*landvertexptr;

typedef float R3DVALUE;

struct	Base_Obj3D
{
	BaseObj3DPtr	lptr,
					rptr;
	ObjectType		objtype;
	IFShare			realbz;
};

//OLD struct	Land_Obj : public Base_Obj3D
//OLD {
//OLD 	IFShare			bodyz;
//OLD 	landvertexptr	vt0,
//OLD 					vt1,
//OLD 					vt2,
//OLD 					vt3;
//OLD 	LandMapDescPtr	imagep;
//OLD 	UByte			tileseg;
//OLD 	UByte			pad[19];
//OLD };


struct HTEXT
{
	UWord textureHandle;
	UWord operator() () {return textureHandle;}
	UWord operator() () const {return textureHandle;}
	HTEXT() : textureHandle(0xFFFF) {}
	explicit HTEXT(UWord i) {textureHandle=i;}
};

#define HTEXTNULL HTEXT(0xFFFF)

struct Dropped
{
	SWord num;
	HTEXT hText[17*17];
	Dropped() : num(0) {}
};

inline bool operator==(const HTEXT& a,const HTEXT& b)
{ return (a.textureHandle==b.textureHandle); }

inline bool operator!=(const HTEXT& a,const HTEXT& b)
{ return (!(a==b)); }

inline bool operator<(const HTEXT& a,const HTEXT& b)
{ return (a.textureHandle<b.textureHandle); }

inline HTEXT operator-(const HTEXT& a,const HTEXT& b)
{ return HTEXT(a.textureHandle-b.textureHandle); }

struct Land_Obj : public Base_Obj3D
{
	IFShare bodyz;
	Float bx[3],by[3],bz[3];
	SWord u[3],v[3];
	UWord clipFlags[3];
	HTEXT hMaterial;
};

enum CLIPFLAGS3D {	CF3D_NULL		=0x0000,
					CF3D_BEHINDNEARZ=0x0001,
					CF3D_PASTFARZ	=0x0002,
					CF3D_OFFLEFT	=0x0004,
					CF3D_OFFRIGHT	=0x0008,
					CF3D_OFFTOP		=0x0010,
					CF3D_OFFBOTTOM	=0x0020,
					CF3D_ALL		=(int)CF3D_BEHINDNEARZ+(int)CF3D_PASTFARZ+(int)CF3D_OFFLEFT+
									 (int)CF3D_OFFRIGHT+(int)CF3D_OFFTOP+(int)CF3D_OFFBOTTOM,
					};

const ULong CF3D_SIGNBITMASK=0x80000000;
const ULong CF3D_ONE_HIGH=0x3FF00000;
const ULong CF3D_ONE_LOW=0x00000000;

/*UWord void _clipAll(ULong abs_farz_high,ULong abs_farz_lo,
					Float* x,Float* y,Float* z)
{
	ULong abs_z_high=*((ULong*)z+1);
	ULong abs_z_low=*(ULong*)z;

	UWord clipVal;

	if (abs_z_high&CF3D_SIGNBITMASK)
	{
		abs_z_high&=~CF3D_SIGNBITMASK;
		clipVal=CF3D_BEHINDNEARZ;
	}
	else if (abs_z_high<CF3D_ABS_1_HIGH ||
			(abs_z_high==CF3D_ABS_1_HIGH && abs_z_low<CF3D_ABS_1_LOW))
	{
		clipVal=CF3D_BEHINDNEARZ;
	}
	else if (abs_z_high>abs_farz_high ||
			(abs_z_high==abs_farz_high && abs_z_low>abs_farz_low))
	{
		clipVal=CF3D_PASTFARZ;
	}
	else clipVal=CF3D_NULL;


}*/


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	_clipFB
//------------------------------------------------------------------------------
//Author	Paul.   
//Date		Wed 1 Jul 1998
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
inline void _clipFB(UWord& cf,Float z,Float nearz,Float farz)
{
	if (z<nearz)
 		cf=CF3D_BEHINDNEARZ;
	else if (z>farz)
		cf=CF3D_PASTFARZ;
	else
		cf=CF3D_NULL;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	_clipLR
//------------------------------------------------------------------------------
//Author	Paul.   
//Date		Wed 1 Jul 1998
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
#ifndef __BCPLUSPLUS__
inline void _clipLR(UWord& cf,Float x,Float z)
{
	Float abs_z;
	abs_z=z<0?-z:z;
	if (x<0)
	{
		if (-x>z) cf|=CF3D_OFFLEFT;
	}
	else if (x>z) cf|=CF3D_OFFRIGHT;
}

//Old_Code PD 26Feb99 inline void _clipLR(UWord& cf,Float x,Float z)
//Old_Code PD 26Feb99 {
//Old_Code PD 26Feb99  	ULong abs_z_high=*((ULong*)&z+1)&~CF3D_SIGNBITMASK;
//Old_Code PD 26Feb99 	ULong abs_x_high=*((ULong*)&x+1);
//Old_Code PD 26Feb99 	if (abs_x_high&CF3D_SIGNBITMASK)
//Old_Code PD 26Feb99 	{
//Old_Code PD 26Feb99 		abs_x_high&=~CF3D_SIGNBITMASK;
//Old_Code PD 26Feb99 		if (abs_x_high>abs_z_high || 
//Old_Code PD 26Feb99 			(abs_x_high==abs_z_high && *(ULong*)&x>*(ULong*)&z))
//Old_Code PD 26Feb99 			cf|=CF3D_OFFLEFT;
//Old_Code PD 26Feb99 	}
//Old_Code PD 26Feb99 	else if (abs_x_high>abs_z_high || 
//Old_Code PD 26Feb99 			(abs_x_high==abs_z_high && *(ULong*)&x>*(ULong*)&z))
//Old_Code PD 26Feb99 			cf|=CF3D_OFFRIGHT;
//Old_Code PD 26Feb99 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	_clipTB
//------------------------------------------------------------------------------
//Author	Paul.   
//Date		Wed 1 Jul 1998
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
inline void _clipTB(UWord& cf,Float y,Float z)
{
	Float abs_z;
	abs_z=z<0?-z:z;
	if (y<0)
	{
		if (-y>z) cf|=CF3D_OFFBOTTOM;
	}
	else if (y>z) cf|=CF3D_OFFTOP;
}
//Old_Code PD 26Feb99 inline void _clipTB(UWord& cf,Float y,Float z)
//Old_Code PD 26Feb99 {
//Old_Code PD 26Feb99  	ULong abs_z_high=*((ULong*)&z+1)&~CF3D_SIGNBITMASK;
//Old_Code PD 26Feb99 	ULong abs_y_high=*((ULong*)&y+1);
//Old_Code PD 26Feb99 	if (abs_y_high&CF3D_SIGNBITMASK)
//Old_Code PD 26Feb99 	{
//Old_Code PD 26Feb99 		abs_y_high&=~CF3D_SIGNBITMASK;
//Old_Code PD 26Feb99 		if (abs_y_high>abs_z_high || 
//Old_Code PD 26Feb99 			(abs_y_high==abs_z_high && *(ULong*)&y>*(ULong*)&z))
//Old_Code PD 26Feb99 			cf|=CF3D_OFFBOTTOM;
//Old_Code PD 26Feb99 	}
//Old_Code PD 26Feb99 	else if (abs_y_high>abs_z_high || 
//Old_Code PD 26Feb99 			(abs_y_high==abs_z_high && *(ULong*)&y>*(ULong*)&z))
//Old_Code PD 26Feb99 			cf|=CF3D_OFFTOP;
//Old_Code PD 26Feb99 }
#endif

struct	DoPointStruc
		{
		IFShare	bodyx,
				bodyy,
				bodyz;
		IFShare	screenx,
				screeny;
		Colour	colour;
		Colour	padbyte;
		SWord	ix, iy;											//RJS 19Mar97
		SWord	intensity;										//RJS 20Mar98
		SWord	specular;
		SWord	specFlip;
		UWord	clipFlags;
		UByte	mist;
		UByte	snow;
		SByte	ni,nj,nk;	//Normal info (DEBUG!)
		};

typedef	DoPointStruc	*dopointptr;

typedef	struct	vertex	VERTEX, *VERTEX_PTR;					//PD 30Oct95

enum	OBJ3DTYPE		{STATIC = 0, MOBILE};					//PD 31Oct95
enum	SCANLINETYPE	{PLAIN=0,
						GOURAUD,
						NDGOURAUD,		//no dither				//PD 10Oct96
						IMAPPED,
						IMAPPED_M,
						IMAPPED_S,
						IMAPPED_SH,								//PD 18Jan96
						NDIMAPPED_SH,	//no dither				//PD 10Oct96
						OMAPPED,								//PD 18Jan96
						OMAPPED_M,
						IMAPPED_TF,
						IMAPPED_ALPHA,
						IMAPPED_C};

typedef void *HoriLineRtnPtr;									//PD 03Jan96

MINMAX		(ImageMapNumber,0,1023);							//PD 25Aug96

typedef SLong OpacityMapNumber;									//PD 18Jan96

struct	matrix_												//PD 23Nov95
		{
			SWord	L11,L12,L13,								//PD 27Feb96
					L21,L22,L23,								//PD 27Feb96
					L31,L32,L33;								//PD 27Feb96
		};


typedef struct matrix_ MATRIX, *MATRIX_PTR;					//PD 23Nov95

struct	fpmatrix_												//PD 06Jan97
		{
			Float	L11,L12,L13,
					L21,L22,L23,
					L31,L32,L33;
		};

typedef struct fpmatrix_ FPMATRIX, *FPMATRIX_PTR;				//PD 06Jan97

#define	THREE_DEE_WINDOW_X		32								//PD 03Nov95
#define	THREE_DEE_WINDOW_Y		20								//PD 03Nov95
#define	THREE_DEE_WINDOW_WIDTH	256								//PD 03Nov95
#define	THREE_DEE_WINDOW_HEIGHT	160								//PD 03Nov95

struct	Land_Obj;
struct	Vert_Ex;

struct	Vert_Ex
{
	SLong	wx,wz;
	IFShare	bodyx,
			bodyy,
			bodyz;
	IFShare	sx,
			sy;
	SWord	intensity;											//PD 27Nov96
	UByte	b2sflag;											//PD 02Oct96
};	

//TempCode PD 07Jan97 typedef	struct	worldvert
//TempCode PD 07Jan97 {
//TempCode PD 07Jan97 	SLong	bodyx,
//TempCode PD 07Jan97 			bodyy,
//TempCode PD 07Jan97 			bodyz;
//TempCode PD 07Jan97 	UWord	scale;
//TempCode PD 07Jan97 }
//TempCode PD 07Jan97 wvert, *wvertptr;

enum	GREY3DTYPE	{NOGREY3D=0x00,								//PD 07Jan96
					CLOUD01,CLOUD02,CLOUD03,CLOUD04,
					CLOUD05,CLOUD06,CLOUD07,CLOUD08,
					CLOUD09,CLOUD0A,CLOUD0B,CLOUD0C,
					CLOUD0D,CLOUD0E,CLOUD0F,CLOUD10,
					CLOUD11,CLOUD12,CLOUD13,CLOUD14,
					CLOUD15,CLOUD16,CLOUD17,CLOUD18,
					CLOUD19,CLOUD1A,CLOUD1B,CLOUD1C,
					CLOUD1D,CLOUD1E,CLOUD1F,CLOUD20,
					};

const	SLong	LandTreeSize	 = 3*6*1024;							//PD 20Jun96
const	SLong	ObjectTreeSize	 = 1024;						//PD 13Mar96
const	SLong	AircraftTreeSize	= 64;						//PD 28Oct98

//typedef
//DeadCode PD 03Mar98 enum PInOut{pio_NULL 	= 0x0000,
//DeadCode PD 03Mar98 	 		pio_Top		= 0x0020,
//DeadCode PD 03Mar98 	 		pio_Bottom	= 0x0010,
//DeadCode PD 03Mar98 	 		pio_North	= 0x0008,
//DeadCode PD 03Mar98 	 		pio_South	= 0x0004,
//DeadCode PD 03Mar98 	 		pio_East	= 0x0002,
//DeadCode PD 03Mar98 	 		pio_West	= 0x0001,
//DeadCode PD 03Mar98 			pio_ALL		= 0x003F} PInOut;

typedef
class PointType
{
	public:

	enum	PointTypes
	{
		PT_PlainColour=0,
		PT_ShadeColour=1,
		PT_MAX=0xFFFF
	};

	PointTypes	ptType;

	struct	vertex*	lpVertex;

	Colour	colour;

	CON	PointType(PointTypes ptype=PT_PlainColour)
	{
		ptType=ptype;
	}
	DES	~PointType() {};
}
POINTTYPE,
*LPPOINTTYPE;

typedef
class	LineType
{
	public:

	enum	LineTypes
	{
		LT_PlainColour=0,
		LT_ShadeColour=1,
		LT_MAX=0xFFFF
	};

	LineTypes	ltType;

	struct	vertex*	lpStartVertex;

	struct	vertex*	lpEndVertex;

	Colour	colour;

	CON	LineType(LineTypes ltype=LT_PlainColour)
	{
		ltType=ltype;
	}
	DES	~LineType() {};
}
LINETYPE,
*LPLINETYPE;

typedef
class PolyType
{
	public:
	
	enum	PolyTypes
	{
		PT_PlainColour=0,
		PT_ShadeColour=1,
		PT_PlainImagem=2,
		PT_ShadeImagem=3,
		PT_LandPoly=4,
		PT_MaskedImagem=5,
		PT_GColour=6,
		PT_HighLand=7,
		PT_FakeFog=8,
		PT_Max=0xFFFF
	};

	PolyTypes		ptType;			//Type of polygon

	UWord			points;			//No of vertices in the polygon

	struct vertex**	lplpVertices;	//List of vertices in the polygon

	union
	{
		Colour			colour;		//Colour for plain polygons
		ImageMapNumber	imapno;		//Image map ID number
		ULong			hTexture;	//Landscape texture map handle
	};

	ImageMapDescPtr	lpImageMap;	//Texture map for textured polygons

	CON	PolyType(PolyTypes ptype=PT_PlainColour)
	{
		ptType = ptype;
	}
	DES	~PolyType() {};
}
POLYTYPE,
*LPPOLYTYPE;

typedef															//PD 02Jun97
enum	TwoDeeEffect
{
	TDE_NULL=0,
	TDE_INSIDE2OUT,	//Fade starts from the centre of the screen and works outwards
	TDE_OUTSIDE2IN,	//Fade starts from the edge of the screen and works inwards
	TDE_UNIFORM		//Fade is uniform over the whole screen
}
TWODEFFECT,*LPTWODEFFECT;

typedef struct lightvec											//RJS 16Jul97
{																//RJS 16Jul97
	IFShare	ni, nj, nk;											//RJS 16Jul97
}LightVec, *LightVecP;											//RJS 16Jul97

struct CockpitBuf
{
	UWord hdg,pitch,roll;
	COORDS3D delta;
};
#endif

