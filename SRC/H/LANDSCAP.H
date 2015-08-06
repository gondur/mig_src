//------------------------------------------------------------------------------
//Filename       landscap.h
//System
//Author         Paul.
//Date           Mon 6 Nov 1995
//Description
//------------------------------------------------------------------------------
#ifndef	LANDSCAP_Included
#define	LANDSCAP_Included
		#include "enumbits.m"									//PD 04Dec95
		#include "myvector.h"										//PD 06Sep96
		#include "mystack.h"										//PD 18Oct96
#include	"Palette.h"											//ARM 05Aug96
#include	"ImageMap.h"										//ARM 05Aug96
#include	"display.h"											//ARM 05Aug96
#define	MAX_RECORD_COUNT	256
#define	DEFAULT_LANDSCAP 0

const	int	CloudsAt5000ft	= 0x028B0A;							//PD 11Oct96
const	int CloudsAt10000ft	= 2*CloudsAt5000ft;					//PD 11Oct96
const	int	CloudsAt15000ft	= 3*CloudsAt5000ft;					//PD 11Oct96

enum	CloudAlt {CH_5Kft=0,CH_10Kft,CH_15Kft};

//new bits-n-pieces for time of day/bad weather effects

struct SLayerRGB
{
	UWord r,g,b;

	UByte red() {return UByte(r>>8);}
	UByte green() {return UByte(g>>8);}
	UByte blue() {return UByte(b>>8);}
};

struct SLandLight
{
	COORDS3D pos;
	SLayerRGB color;
	SLong	range;
	SWord	timer;
};

struct SLightingRGB
{
  	SLayerRGB	horizonBase;		/* horizon fade colour 		*/
	SLayerRGB	horizonMid;			/* colour @ the top of the
									   lower horizon strip 		*/
	SLayerRGB	horizonUnderClouds;	/* colour underneath the
									   cloud layer				*/
	SLayerRGB	horizonAtClouds;	/* colour @ the cloud layer */
	SLayerRGB	horizonAboveClouds;	/* colour above the clouds	*/
	SLayerRGB	horizonTop;			/* colour @ highest point of
									   the horizon				*/
	SLayerRGB	landAmbientCol;		/* Ambient lighting value
									   for the landscape polys	*/
	SLayerRGB	shadedAmbientCol;	/* Ambient lighting value
									   for light shaded shapes	*/
	SLayerRGB	staticAmbientCol;	/* Ambient lighting value
									   for non-light shaded
									   shapes					*/
	SLayerRGB	cockpitAmbientCol;	/* Ambient light for internal 
										cockpit view */
	SLayerRGB	effectsAmbientCol;	/* Ambient light for explosions */
};

//------------------------------------------------------------------------------
//Author		Paul.   
//Date			Mon 6 Nov 1995
//Modified	
//
//Description	
//
//Inputs		
//------------------------------------------------------------------------------
class CDataBlock;
//DEAD class Heap<landvertex>;
class ViewPoint;
struct PointDef;
struct DataRecord;
struct AltPointsHdr;
struct Rect;

struct CHorizData;
struct CPointList;

//DEAD typedef	class Heap<landvertex>	LVHeap,*LVHeapP;

class LandScape
{
	enum MigLandConsts{

#ifndef	__BCPLUSPLUS__
		//General constants...
		_wholeAreaSizeMAX=33,
		_wholeAreaSizeMIN=17,
		_mediumAreaSize=6,	//5,	//2,	//8,
		_centralAreaSize=5,	//3,	//1,	//3,
		_blockWidth=131072,
		_halfBlockWidth=_blockWidth>>1,
		_halfAreaSizeMAX=_wholeAreaSizeMAX>>1,
		_halfAreaSizeMIN=_wholeAreaSizeMIN>>1,
		_sortMinMAX=_halfAreaSizeMAX-_centralAreaSize,
		_sortMinMIN=_halfAreaSizeMIN-_centralAreaSize,
		_sortMaxMAX=_halfAreaSizeMAX+_centralAreaSize,
		_sortMaxMIN=_halfAreaSizeMIN+_centralAreaSize,
		_medMinMAX=_halfAreaSizeMAX-_mediumAreaSize,
		_medMinMIN=_halfAreaSizeMIN-_mediumAreaSize,
		_medMaxMAX=_halfAreaSizeMAX+_mediumAreaSize,
		_medMaxMIN=_halfAreaSizeMIN+_mediumAreaSize,
		_maxalt=257000,

		//grid cone constants
		_cornerLengthMAX=_wholeAreaSizeMAX+1,
		_cornerLengthMIN=_wholeAreaSizeMIN+1,
		_cornerBufferSizeMAX=_cornerLengthMAX*_cornerLengthMAX,
		_cornerBufferSizeMIN=_cornerLengthMIN*_cornerLengthMIN,

		//Route types...
		_coast=128,
		_wood=129,
		_lake=130,
		_river=131,
		_track=157,
		_rail=158,
		_road=159,

		//Route detail constants...
		_routeMPolySize=3*_blockWidth,
		_routePolySize=(_centralAreaSize)*_blockWidth,
		_routeLineSize=(_halfAreaSizeMAX-1)*_blockWidth,
		_doNowt=0,
		_doLine=1,
		_doPoly=2,
		_doMPoly=3,

		//Ground detail constants...
		_groundHighSize=_centralAreaSize*_blockWidth,
		_groundMedSize=_mediumAreaSize*_blockWidth,
		_groundLowSizeMAX=_halfAreaSizeMAX*_blockWidth,
		_groundLowSizeMIN=_halfAreaSizeMIN*_blockWidth,
		_doLowGround=255,
		_doMedGround=1,
		_doHighGround=0,
		_landscapeTextures=6,
		_landTextureWH=256,
		_snowLine=50000,
		_mistBase=0,
		_mistTop=25000,
		_numBands=7,	//number of vertical segments in
						//the hemisphere
		_numSegs=32		//number of horizontal segments
						//in the hemisphere
						//NOTE: ((_numBands+1)*_numSegs)+1 
						//		must be less than or equal 
						//		to 257
#endif
	};

public:
	enum{_MaxLights=32};

	SLandLight lightList[_MaxLights];

	UWord lightsActive;
	UWord lightMe;
#ifndef	__BCPLUSPLUS__
	struct SLightTable
	{
		UWord numLights;
		UByte lightIndices[_MaxLights];
	}
	lightTable[_wholeAreaSizeMAX];
#endif
public:
	SLong GroundHuggingAltitude(MobileItem*);
	void AddLight(SLandLight*);
	inline void ResetLights();
	void ProcessLights(SLong,SLong);

	void RefreshLandscape();
	SLightingRGB	currentLighting;
	SLong groundFogBegin,groundFogEnd,skyFogBegin,skyFogEnd;
private:
	SLightingRGB	*pDawn, *pDay, *pDusk, *pNite, *pBadW, *pMapL;

	SLong treeHeight;

	struct RouteData;

	RouteData* pRouteData;

	UByte* gridCorners;

	UByte* gridCone;
	UByte* lightCone;
	UByte* routeDetail;
	UByte* groundDetail;
	UByte* landRnd;						//for noise generation
	UByte* softGrid;					//for s/w version item tracking

//DeadCode PD 16Feb99 public:
	UByte* pLastGrid;
	HTEXT* pHTextureGrid;
	SLong lastPx,lastPz;
//DeadCode PD 16Feb99 private:

	SLong View_Ground_Height;

	SLong land_min_detail;

	//dome horizon variables

	CHorizData* pointList;
	CPointList* polyList;

	bool meshCreated;	//is it done yet?

	Colour topColor;	//color for top of horizon dome
	Colour midColor;	//color for top of horizon texture strip
	Colour botColor;	//color for horizon fade

	//RGB values for 'topColor'

	UByte topR;
	UByte topG;
	UByte topB;

	//RGB values for 'midColor'

	UByte midR;
	UByte midG;
	UByte midB;

//DeadCode PD 16Feb99 	SLong lastPx,lastPz;

	//number of hemisphere segments to wrap the texture over

	int imageVTile;

	FileNum theHorizonStrip;

	DataRecord*	pDataBlocks;

	COORDS3D* tileCoords;

	SLong	max_body_z;

	SLong	gnd_band_start,gnd_band_end,shape_band_start;
	SLong	sky_band_start,sky_band_end;
	SLong	viewer_x,viewer_y,viewer_z,viewer_dy,cviewer_dy;

	FPMATRIX_PTR fpviewer_matrix;

	//Poly sorting variables
	LandObj3DPtr list_index,start_index,list_header,list_end;
	DoPointStruc* highco;
	ANGLES	viewer_hdg;
	UWord	list_size;
	ANGLES	viewconeangle;
	SWord	minscale;

	FileNum	FilSkyStrip;									//RJS 24Jun98

	public:

	void ResetItemLog();
	bool LogItem(ULong vx,ULong vz,COORDS3D& pos);

	ViewPoint*	View_Point;
	Window 	*currscreen;

	SLong	cloud_base;
	COORDS3D	cloudset;									//RJS 01Apr98
	SLong	fade_band_start,fade_band_end,fade_band_mid;
	SLong	Cloud_Layer_Height;
	SLong	view_range;
	SLong	gvisrange,cvisrange;
	SLong	blackingout,redingout,whitingout;

	Bool	texturedclouds,incloudlayer,bDoingHardware3D,bAnyLandDrawn;

	bool	mistenabled;

	animptr	CloudAnimP;											//RJS 21Apr99

	LandScape::LandScape();
	LandScape::~LandScape();

	Bool SetLighting(SLong);									//RJS 15Jun99

	void Init();
	void Exit();

	void SetLVector(COORDS3D&);
	void SetupGroundData(MovingItem*,Bool inclouds=FALSE);
	void SetFogMode(SLong,SLong);
	void DistantClouds();								//PD 05Dec96
	void CloudLayer(ViewPoint*);									//PD 05Dec96
	void IncDetailLevel();								//PD 12Sep96
	void DecDetailLevel();								//PD 12Sep96
	SLong SetViewDetail();								//RJS 25Jun98
	void RenderLandscape(Window *,ViewPoint* VP,
						FPMATRIX_PTR,
						ULong&, ULong&, ULong&,
						ANGLES);						//PD 07Jan97
	SLong GetGroundLevel(ItemBasePtr ,UByte* pAreaType=NULL,bool fReallyGetData=false);
	SLong GetGroundLevel(COORDS3D& ,UByte* pAreaType=NULL,bool fReallyGetData=false);
	SLong GetCloudLevel(COORDS3D& );						//PD 22Oct96
	void  TidyUp();										//PD 13Mar96
	void  RenderLandPoly(LandObj3DPtr );					//PD 13Mar96
	void  RenderSpecialLandPoly(LandObj3DPtr );					//PD 13Mar96
	void  RenderSkyPoly(LandObj3DPtr );					//PD 13Mar96
	SLong GetFadeStart();									//PD 10May96
	SLong GetFadeEnd();									//PD 10May96
	SLong CloudAlt()	{return (cloud_base);}
	void  CalcVisibleRanges(SLong,SLong);					//PD 14Nov96
	void  ScaleInsideHorizon(COORDS3D&);
	void	SetSkyMap(FileNum);							//RJS 24Jun98

	protected:
	void 	WireFrame(DoPointStruc& ,DoPointStruc& ,DoPointStruc& );
	Bool	SelectTexture(Colour, Colour, Colour, Colour);
	void	MakeTextureInfo(Colour&,ImageMapNumber&,UWord&,UWord&,UWord&,UWord&);
	void	MakeTextureInfoPtr(Colour&, UByte *&);
	void	MakeMaskPtr(UWord, UByte *&);
	bool	GeneratePointData(void );
	void	RenderPolyList(void );

	//Revamped cone check routines here

	Bool	GroundTileCone(SLong,SLong,SLong,SLong);		//PD 29Jan97
//DEAD	Bool	InCone(landvertex&,landvertex&,landvertex&,landvertex&);//PD 29Jan97
//DEAD	Bool	TriCone(landvertex&,landvertex&,landvertex&);//PD 29Jan97
//DEAD	UWord	TwoTriCone(landvertex&,landvertex&,landvertex&,landvertex&);//PD 29Jan97
	Bool	SkyTileCone(SLong,SLong,SLong,SLong);			//PD 29Jan97

	private:
	void InterpSLightRGB(SLayerRGB&,SLayerRGB&,SLayerRGB&,ULong);
	int  VHighDetailTile(ULong,UByte*&,ULong&,COORDS3D&);
	int  HighDetailTile(UByte*&,ULong&,COORDS3D&);
	int  UnclippedTile(UByte*&,ULong&,COORDS3D&);
	int	 ClippedTile(UByte*&,ULong&,COORDS3D&,Rect&);
	int  MedDetailTile(UByte*&,ULong&,COORDS3D&);
	int  LowDetailTile(UByte*&,ULong&,COORDS3D&);

	void  HighDetailRoute(UByte*&,ULong&,int,COORDS3D&);
	void  MedDetailRoute(UByte*&,ULong&,int,COORDS3D&);
	void  LowDetailRoute(UByte*&,ULong&,int,COORDS3D&);

	void  GenerateRoutePoly(COORDS3D&,int,UByte*,RouteData*);
	void  GenerateEdgePoly(COORDS3D&,int,UByte*,RouteData*);

	Bool  BadVision();								//PD 24Jun96
	SWord IntensFromRange(SLong);						//PD 12Jan96
	void  GenerateGroundPoints(	SLong,SLong,		//PD 22May96
								SLong&, SLong&, SLong&, SLong&);//PD 22May96
	void  DomeHorizon(FileNum);							//RJS 24Jun98
	void  StripHorizon();
	void InfiniteStrip();
	void GStrip(DoPointStruc**,UByte,UByte,UByte,UByte,UByte,UByte);
//DEAD	Bool  CheckRange(LandObj3DPtr );					//PD 13Mar96

	void  GridCone(const SLong,const SLong);
	bool  FillDataGrid(SLong,SLong);
	bool  LVisCheck(SLong x,SLong z);

	void ScrollGrid(SLong,SLong,UByte*);
	void ScrollGridDis(SLong,SLong,HTEXT*,Dropped*);
	void ManageHighLandTextures(SLong,SLong);

	inline SLong perm(SLong x) {return landRnd[x&0xFF];}
	inline UByte index2d(SLong x,SLong y) {return (UByte)perm(x+perm(y));}
	inline UByte index3d(SLong x,SLong y,SLong z) {return (UByte)perm(x+perm(y+perm(z)));}

	void		DoRain(ViewPoint*,SLong);				//RJS 25Jun98

	ImageMapDesc* CreateImageMap(UWord);
	void DestroyImageMap(ImageMapDesc*);
	void RenderTile2ImageMap(ImageMapDesc*,UByte*&,ULong&);
	void RenderTri(UByte,ImageMapDesc*,PointDef&,PointDef&,PointDef&,ImageMapDesc*);
	void ScanLine(UByte*,SLong,SLong,UByte*,SLong);
	bool FanClipTest(UByte*);
	void SetMist(DoPointStruc&);
	void DisplayBoxes();
	void PrintDebugs();

	inline UByte SetClipFlags(const SLong,const SLong,const Rect&);
	inline UByte ClipToTop(DoPointStruc*,DoPointStruc*,DoPointStruc*,Rect&);
	inline UByte ClipToBottom(DoPointStruc*,DoPointStruc*,DoPointStruc*,Rect&);
	inline UByte ClipToLeft(DoPointStruc*,DoPointStruc*,DoPointStruc*,Rect&);
	inline UByte ClipToRight(DoPointStruc*,DoPointStruc*,DoPointStruc*,Rect&);
	void TriClipper(SLong&,DoPointStruc**,UByte*,DoPointStruc*&,Rect&);
	void DoCloudLayer();
	void RenderTrees(UByte*,COORDS3D&);
	void RenderWaves(UByte*,COORDS3D&);
	void StandardTileRender(SLong ,SLong );
	void HighDetailTileRender(SLong ,SLong );
	void HiRezTile(UByte*&,ULong&,COORDS3D&,const HTEXT&);
	void AutoScaleFrameRate();
	void GetMinMaxAlt(AirStrucPtr,SLong&,SLong&);
	void AddTile(ULong,ULong,DoPointStruc*,ULong,UByte*&,const HTEXT&);
	void SoftTile(UByte*&,ULong&,COORDS3D&,const HTEXT&);
	void AddTileSub(ULong ,ULong ,DoPointStruc*,ULong,UByte*&,const HTEXT&);

	struct LPolyDef
	{
		enum {Max_Points=5};
		SWord	count;
		DoPointStruc *point[Max_Points];
	};

	struct LPolyList
	{
		enum {Max_Polys=48};
		SWord		count;
		LPolyDef	poly[Max_Polys];
	};

	class CVertexAllocator
	{
	protected:
		UWord count;
		UWord limit;
		DoPointStruc* pdp;
	public:
		CVertexAllocator() {count=0;pdp=NULL;}
		CVertexAllocator(UWord sz,DoPointStruc* ptr)
		{
			count=0;
			limit=sz;
			pdp=ptr;
		}
		DoPointStruc *alloc()
		{
			if (count<limit)
			{
				DoPointStruc *retval=pdp+count;
				count++;
				return retval;
			}
			return NULL;
		}
	};

	inline bool SubdivisionNeeded(const LPolyDef&,bool&);
	void Split(LPolyDef&,LPolyDef&,bool,CVertexAllocator&);
	void PerspectivePoly(SWord,DoPointStruc*,const HTEXT&);
};

extern class LandScape Land_Scape;

#endif

