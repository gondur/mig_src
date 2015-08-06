//------------------------------------------------------------------------------
//Filename       3dcode.h
//System         
//Author         Paul.   
//Date           Wed 23 Aug 1995
//Description    
//------------------------------------------------------------------------------
#ifndef	Dcode_Included
#define	Dcode_Included

	#include	"myANGLES.H"
	#include	"ENUMBITS.M"
	#include	"landscap.h"									//PD 01Oct96

struct NormalData
{
	Float i,j,k;
};

 struct	Obj_3D : public Base_Obj3D	//moved from 3ddefs to cut dependency on worldinc//JIM 14May96
 {
 	itemptr		ItemPtr;
 	animptr		AnimPtr;
 	fpCOORDS3D	Body;
 	UWord		Shape:15,										//RJS 28Aug98
				IsTransient:1;									//RJS 28Aug98
 	ANGLES		AngH,
 				AngC,
 				AngR;
 };

enum	DrawRanges												//RJS 04Jun98
{																//RJS 04Jun98
	RANGE_DEFAULT = 800000,										//RJS 04Jun98
	RANGE_AIRCRAFT = 1600000,									//RJS 04Jun98
	RANGE_AIRCRAFT_FLASH = 1920000,								//RJS 25Jun98
	RANGE_RADAR = 1280000,										//RJS 25Jun98
	RANGE_SHADOW = 160000,										//RJS 08Sep98
	RANGE_FLYBYFAST = 95000,									//RJS 04Sep98
	RANGE_FLYBYSLOW = 217800,									//RJS 04Sep98
	RANGE_CONTRAIL = 4200000									//RJS 22Jan99
};																//RJS 04Jun98

enum	PitTypes {UNMASKED=0,MASKED};						//PD 20Jun96
struct	LiveList;												//JIM 22Sep96
class CMigLand;											//PD 18Jan98
class TMake;


class	ThreeDee
{
	typedef struct	RGBValues
	{
		UByte	rval,gval,bval;
	}RGBINFO, *RGBINFO_PTR;

	Window		*current_screen;								//PD 20Dec95
	Display		*current_display;
	ViewPoint*	View_Point;
	class	btree	*aircraft_tree;

	CockpitBuf	buffetData;										//PD 29Oct98

	ULong	viewer_x,
			viewer_y,
			viewer_z;

	ANGLES	viewer_hdg,
			viewer_pitch,
			viewer_roll;


	COORDS3D	lastSunPos;

	struct SPosRec
	{
		enum {Max_Recs=32};
		itemptr ip;
		COORDS3D pos;
	}
	posRecTable[SPosRec::Max_Recs];
	SLong cur_rec;
	void ResetPosRec() {cur_rec=0;}
	void StoreAcPos(itemptr ip)
	{	
		if (cur_rec<SPosRec::Max_Recs)
		{
			posRecTable[cur_rec].ip=ip;
			posRecTable[cur_rec].pos=ip->World;
			cur_rec++;
		}
	}

	ANGLES	staticH,staticP,staticR;							//PD 05Sep97

	ImageMapDescPtr landdata[4];								//PD 06Nov95
	SLong			whereinpal;									//RJS 22Oct96
	SLong			whichpal;									//RJS 22Oct96
	SLong			oldtime;									//RJS 24Oct96
	Bool			aboveclouds;								//RJS 30Oct96
	Bool			resetpit;								//RJS 30Oct96

	SLong  imagemaps[6];										//MGA 21Feb96
	SLong	time_minutes;										//RJS 23Apr98

	int	MaxShapeCount;											//RJS 20May98
	int	MaxShape2Count;											//RJS 20May98
	int MaxGroupCount;											//RJS 20May98
																//RJS 20May98
	SLong	CheatStart[3];										//RJS 20May98
	SLong	CheatEnd[3];										//RJS 20May98
	SLong	CheatPos;											//RJS 20May98
	ShapeNum	CheatSave;										//RJS 20May98

	animptr		sunanimptr;										//RJS 02Jul98
	SLong		mapdistz;										//RJS 10Sep98
	SLong		mapoffx;
	SLong		mapoffy;

	ItemPtr		supercheatitem;									//RJS 09Nov98
	SByte		supergroupindex;								//RJS 09Nov98

	animptr		lensflareanim;									//RJS 25Feb00

	public:
		void	ClearCurrentScreen()	{current_screen=NULL;}
		void	ClearCurrentDisplay()	{current_display=NULL;}
		class	btree	*bt;
		bool nomorereallygetdata;
		NormalData* normalDataPtr;
		UByte*		pNormalLookup;
		Bool		b3DRunning;									//PD 10Jun97
		Bool		shapecheat;									//RJS 24Jul96
		Bool		lightson;									//RJS 04Nov96
		CMigLand*	pMigLand;									//PD 18Jan98
		TMake*		pTMake;										//PD 20Jul98
		ImageMapDescPtr	newpalettes;							//RJS 19Nov96
		LightVec	SunLightVector;								//RJS 16Jul97
		RGBINFO_PTR	NewPalettePtr;								//RJS 24Feb98
		UByteP		MasterPalettePtr;							//RJS 24Feb98
		Bool		radarOn;									//RJS 06Nov98
		bool		havematrix;									//RJS 10Dec98
		Bool		groundlockOn;								//RJS 04Jun99

		WorldStuff	*current_world;								//PD 24Apr96
		LiveList	*livelist;
		CON	ThreeDee();											//RJS 24Feb98
		DES	~ThreeDee();										//RJS 24Feb98

		FPMATRIX_PTR fpviewer_matrix,
					 fpviewee_matrix,
					 fpinverse_matrix;
		
		inline void GetSunPos(COORDS3D&);

		bool GetPosRec(itemptr ip,COORDS3D& pos)
		{
        	int	i;	//the standard says... you can't access for statement locals outside 
			for (i=cur_rec-1;i>=0 && posRecTable[i].ip!=ip;i--) {}
			if (i==-1) return false;
			pos=posRecTable[i].pos;
			return true;
		}
  		void render(Window *,ViewPoint* vp,WorldStuff *);			//PD 22Apr96
		void Init3D(Window* win,ViewPoint*);					//RJS 19Nov98
		void Done3D(void );
		ULong GetDistance(Obj3DPtr );							//PD 13Mar96
		Bool zclipline(Bool,DoPointStruc,DoPointStruc);
		void	SetVP(ViewPoint*);								//RJS 19Nov98

		void InitialiseCache();									//PD 05Aug98
		void DeleteCache();										//PD 19Jan98
		void RezChanged(ScreenRez&);							//PD 19Jan98

		void SetCockpitBuffet(CockpitBuf*);
		void	KillTheFucker(UByte);							//RJS 09Nov98


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetObj3D
//Author		Paul.   
//Date			Tue 7 Jan 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
		void SetObj3D(	Obj3DPtr 	obj3dptr,
						itemptr 	itmptr,
						IFShare		bx,
						IFShare		by,
						IFShare		bz,
						IFShare		bzoffset)
		{
			bzoffset.f=0;		//causes more trouble than it's worth//PD 07Dec98
			obj3dptr->IsTransient = 0;							//RJS 28Aug98
			switch(itmptr->Status.size)
			{
				default:
				case ItemSize:
					obj3dptr->objtype = STATIC_OBJECT;
					break;

				case TransientSize:
					obj3dptr->IsTransient = 1;					//RJS 28Aug98
				case RotatedSize:
				case MovingSize:
				case MobileSize:
				case FormationSize:
				case ShipSize:
				case AirStrucSize:
					obj3dptr->AngR = ((rotitem *)itmptr)->roll;

				case HPSize:
					obj3dptr->AngC = ((hpitem *)itmptr)->pitch;

				case HdgSize:
					obj3dptr->AngH = ((hdgitem *)itmptr)->hdg;
					obj3dptr->objtype = MOBILE_OBJECT;//PD 12Mar96
					break;
			}
			//Fix to stop most of the transparency sort problems...
//TempCode RJS 19Jan99 			if (bzoffset.f!=0.)
//TempCode RJS 19Jan99 			{
//TempCode RJS 19Jan99 				Float newz=bz.f-bzoffset.f;
//TempCode RJS 19Jan99 				Float scale_z=newz/bz.f;
//TempCode RJS 19Jan99 				obj3dptr->Body.X.f 	= bx.f*scale_z;
//TempCode RJS 19Jan99 				obj3dptr->Body.Y.f 	= by.f*scale_z;
//TempCode RJS 19Jan99 				obj3dptr->Body.Z.f 	=
//TempCode RJS 19Jan99 				obj3dptr->realbz.f 	= newz;
//TempCode RJS 19Jan99 			}
//TempCode RJS 19Jan99 			else
//TempCode RJS 19Jan99 			{
				obj3dptr->Body.X.f 	= bx.f;
				obj3dptr->Body.Y.f 	= by.f;
				obj3dptr->Body.Z.f 	=
				obj3dptr->realbz.f 	= bz.f;
//TempCode RJS 19Jan99 			}
			obj3dptr->Shape 	= itmptr->shape;
			obj3dptr->ItemPtr 	= itmptr;
		};

		SWord IntensFromRange(SLong& rng, SLong& start, SLong& end);//PD 09Jan96
//DeadCode AMM 16Apr99 		static void PossMoveCycle();
		void ResetPalette(Bool	forceday=FALSE);				//RJS 24Oct96
		void ResetCompass();									//RJS 21Nov96
		void do_object(itemptr);								//RJS 19Jun97
		void do_object_shad(itemptr,itemptr);					//RJS 20Apr99
		void CalcLightsOn(SLong );								//RJS 16Dec96
		SLong AddVapourObject(ShapeNum,UByteP,UByteP,UByteP&,UWord);//RJS 17Sep97
		void AddLensObject(DoPointStruc*,ShapeNum,int,int);		//RJS 21Jan98
		Bool	IsPaused();										//RJS 27Feb98
		SLong GetLandType();									//RJS 24Aug98
		void	DoFlyBySound(AirStrucPtr,SLong);				//RJS 04Sep98
//deadrjs11nov98		void	do_smoke_object(ItemPtr,Coords3D*,ShapeNum,SLong,SLong,SWord,SLong);//RJS 15Sep98
		void	do_object_dummy(itemptr,bool fSpecial=false);						//RJS 11Nov98
		ItemPtr	NearestAliveThing(ItemPtr);						//RJS 16Nov98
		bool	IsItVisible(Coords3D&);							//RJS 18May99
		void	StuffInBinaryTree(ItemPtr);						//DAW 23Apr99


	private:
		void Add_Sun(rotitem&,WorldStuff* );					//RJS 23Mar98
		void LoadLandData(void );					//PD 06Nov95
		void init_scene(WorldStuff *, ViewPoint*);				//PD 22Apr96
		void do_landscape	();									//PD 20Dec95
		void do_objects(void);
		void do_ui_objects(void);								//PD 12Mar99
		void render_scene	();									//PD 20Dec95
		void exit_3D(void);

		void generate_matrix(rotitem&);							//PD 22Apr96
		void add_cockpit(rotitem&,PitTypes,ANGLES,ANGLES,ANGLES);//JIM 10Aug96
		void Add_PeripheralVision();							//PD 22Jul97

//TempCode PD 05Dec96 		void do_object(itemptr );								//PD 08Mar96
		void do_object_grp(itemptr );							//PD 08Mar96
		void PaletteBlender(SLong );							//RJS 22Oct96
		void Add_Shadow(AirStrucPtr,Bool);						//RJS 13Jul98
		SLong do_object_vapour(rotitem*,UByteP&,UWord);			//RJS 16Apr98
		void add_map(rotitem&,Bool isZoomed=FALSE);				//RJS 08Sep98
  		void render3d(Window *,ViewPoint* vp,WorldStuff *);		//RJS 08Sep98
  		void rendermap(Window *,ViewPoint* vp,WorldStuff *);	//RJS 08Sep98
  		void renderzoomedmap(Window *,ViewPoint* vp,WorldStuff *);//RJS 08Sep98
		void do_objects_map(Bool);								//RJS 15Sep98
		void do_map_object(ItemPtr,SLong);						//RJS 14Sep98
  		void renderreplay(Window *,ViewPoint* vp,WorldStuff *);	//AMM 20Oct98
		void add_replay(rotitem& viewpoint);					//AMM 20Oct98
		void SuperShapeCheat();									//RJS 09Nov98

	protected:

		Bool RoughCone(IFShare bx, IFShare by, IFShare bz, SLong shpsize)//RJS 20Aug98
		{
			Float	temp = (Float)1.0;

			bz.f += (Float)shpsize;								//RJS 20Aug98
			if (bz.f<temp) return (FALSE);	//Z-Clipped			//RJS 20Aug98

			temp = (bx.f<0?-bx.f:bx.f)-shpsize;					//RJS 08Jul98
			if (temp < 0)										//RJS 08Jul98
				temp = 0;										//RJS 08Jul98

			if (temp>bz.f)	return (FALSE);

			temp = (by.f<0?-by.f:by.f)-shpsize;					//RJS 08Jul98
			if (temp < 0)										//RJS 08Jul98
				temp = 0;										//RJS 08Jul98

			if (temp>bz.f)	return (FALSE);

			return (TRUE);
		};
		void ConstructNormalData();
};

	extern	class	ThreeDee	Three_Dee;

#endif
