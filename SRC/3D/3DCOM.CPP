/*
	 MiG Alley
	 Copyright (C) 1998, 1999, 2000, 2001 Empire Interactive (Europe) Ltd,
	 677 High Road, North Finchley, London N12 0DA

	 Please see the document licence.doc for the full licence agreement

2. LICENCE
 2.1 	
 	Subject to the provisions of this Agreement we now grant to you the 
 	following rights in respect of the Source Code:
  2.1.1 
  	the non-exclusive right to Exploit  the Source Code and Executable 
  	Code on any medium; and 
  2.1.2 
  	the non-exclusive right to create and distribute Derivative Works.
 2.2 	
 	Subject to the provisions of this Agreement we now grant you the
	following rights in respect of the Object Code:
  2.2.1 
	the non-exclusive right to Exploit the Object Code on the same
	terms and conditions set out in clause 3, provided that any
	distribution is done so on the terms of this Agreement and is
	accompanied by the Source Code and Executable Code (as
	applicable).

3. GENERAL OBLIGATIONS
 3.1 
 	In consideration of the licence granted in clause 2.1 you now agree:
  3.1.1 
	that when you distribute the Source Code or Executable Code or
	any Derivative Works to Recipients you will also include the
	terms of this Agreement;
  3.1.2 
	that when you make the Source Code, Executable Code or any
	Derivative Works ("Materials") available to download, you will
	ensure that Recipients must accept the terms of this Agreement
	before being allowed to download such Materials;
  3.1.3 
	that by Exploiting the Source Code or Executable Code you may
	not impose any further restrictions on a Recipient's subsequent
	Exploitation of the Source Code or Executable Code other than
	those contained in the terms and conditions of this Agreement;
  3.1.4 
	not (and not to allow any third party) to profit or make any
	charge for the Source Code, or Executable Code, any
	Exploitation of the Source Code or Executable Code, or for any
	Derivative Works;
  3.1.5 
	not to place any restrictions on the operability of the Source 
	Code;
  3.1.6 
	to attach prominent notices to any Derivative Works stating
	that you have changed the Source Code or Executable Code and to
	include the details anddate of such change; and
  3.1.7 
  	not to Exploit the Source Code or Executable Code otherwise than
	as expressly permitted by  this Agreement.

questions about this file may be asked at http://www.simhq.com/
*/

//------------------------------------------------------------------------------
//Filename       3dcom.cpp
//System     
//Author         Paul.   
//Date           Wed 16 Aug 1995
//Description    
//------------------------------------------------------------------------------

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//				           INCLUDE FILES
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//We want them now
//#define	   _NOSMOKETRAILS_
//#define	MEMTRACE

	#include	"DOSDefs.h"
	//#include	"MAClib.h"f
#define F_GRAFIX												//DAW 05Aug96
//DeadCode RJS 17Oct96 #define F_SOUNDS
#define F_BATTLE
	#include	"Files.g"
	#include 	"myerror.h"
	#include	"FileMan.h"
	#include 	"Palette.h"
	#include	"Fonts.h"
	#include	"myAngles.h"
	#include	"Worldinc.h"
	#include	"AnimData.h"									//RJS 10Feb97

	#include	"3DDefs.h"
 	#include	"World.h"
//	#include	"3DInstr.h"
	#include	"shapes.h"										//RJS 02Dec97
	#include	"3DCom.h"
#define MATRIX_CODE_REQ
	#include	"Matrix.h"
	#include	"polygon.h"										//RJS 02Dec97
	#include	"3dcode.h"
	#include	"shpbld.h"										//PD 22Jan96
	#include	"landscap.h"									//MGA 09May96
//DeadCode DAW 23Feb98 	#include	"Wrapper.h"										//PD 26Oct95

	#include	"Mytime.h"										//PD 15Mar96

	#include	"keytest.h"										//PD 01Apr96

	#include	"flymodel.h"									//PD 16Apr96
	#include	"Transite.h"									//PD 24Apr96
	#include	"mymath.h"										//RJS 25Jul96
	#include	"savegame.h"									//RJS 12Aug96
	#include	"missman2.h"										//RDH 24Oct96
	#include	"viewsel.h"										//RJS 30Aug96
	#include	"LnchrDat.h"									//RJS 09Sep96
	#include	"speed.h"										//RJS 01Oct96
	#include	"miles.h"										//RJS 17Oct96
	#include	"BoxCol.h"										//RJS 24Feb97
	#include	"shpweap.h"										//RJS 16Apr97
	#include	"deathnum.g"									//RJS 23May97
	#include "monotxt.h"
	#include "stdio.h"											//ARM 09Jun97

	#include	"shpinstr.h"									//RJS 03Jul98
	#include	"modinst.h"										//RJS 03Jul98
	#include	"weappak.h"										//RJS 03Jul98
	#include	"model.h"										//RJS 03Jul98
	#include	"smktrl.g"										//RJS 03Jul98
#include	"winmove.h"
#include	"persons2.h"
#include	"string.h"
#include	"replay.h"
	#include	"shapenam.h"

static	int	shitey = 0;

static	void*	shititem;

#ifdef	__WATCOMC__
	extern	"C" SLong ASM_GetFadeColour(SLong, SLong );			//PD 10May96
#else
#ifdef	__MSVC__
//-----------------------------------------------------------------------------
// Procedure    ASM_GetFadeColour
// Author       Paul
// Date         05/11/97
//
// Description  
//
// Inputs       
//
// Returns      
//
//-----------------------------------------------------------------------------
extern	"C" void XASM_GetFadeColour(void);
#pragma warning (disable:4035)
inline	SLong ASM_GetFadeColour(SLong a, SLong b)
{
	_asm {
		mov		eax,a
		mov		edx,b
		call	XASM_GetFadeColour
	}
}
#pragma warning (default:4035)
#endif
#endif
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//				      EXTERNAL REFERENCES
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴

//	extern	KeyMapping	*Debug3dMapTable;						//PD 01Apr96
//
//	extern class matrix _matrix;
//	extern class Error _Error;		//For 'EmitSysErr'

	extern SWord winmode_w;					//RJS 04Nov98

	class shape	SHAPE;

//DeadCode RJS 01Dec97 	shape::InterpProc*	shape::InterpTable[dosetglassrangeno+1];
	shape::InterpProc*	*shape::InterpTable;
	UByteP				shape::animflags;
	SLong				shape::fade_start,
						shape::fade_end,
						shape::object_dist;

//DeadCode PD 10Jan97 	MATRIX_PTR 			shape::object_matrix;
	FPMATRIX_PTR 		shape::fpobject_matrix;
	Obj3DPtr	  		shape::object_obj3d;
	FPMATRIX_PTR 		shape::fprealobject_matrix;				//RJS 15Jan99

	Window*				shape::current_screen;
	Colour				shape::colour;
	ColourRange			shape::range;
	ImageMapNumber		shape::image;

	SWord 				shape::shapescale,
						shape::AnimWeaponPack;					//RJS 11May98

	shape::GlobalAnimTime	shape::globalanimtime;
	TrailRecord		shape::traillist[REAL_MAX_VAPOURS];				//RJS 21Jan99
	DoPointStruc		*shape::newco;							//RJS 02Dec97
	DoPointStruc		shape::shpco[MAX_DOPOINTS];				//RJS 02Dec97
	 UByte		shape::lastdamage[8];					//RJS 23Feb99
	 UByte		shape::laststationdamage[8];					//RJS 06Apr98
	 UByteP		shape::lastdamptr;						//RJS 21Feb97
	 UWord		shape::HitThisOffset;					//RJS 24Nov98
	 Bool			shape::CommsDamage;						//RJS 15May97
	 Bool			shape::CollisionOn;						//RJS 21Feb97

	 DoPointStruc		shape::CylPnt1;						//RJS 14May97
	 DoPointStruc		shape::CylPnt2;						//RJS 14May97
	 Bool				shape::VapourCyl;					//RJS 15May97

	 UByte	shape::VapourAnim;							//RJS 20May97
	 Bool		shape::IsSubShape;							//RJS 03Jun97
	LightVec	shape::TransLightVector;					//PD 13Nov97
	LightVec	shape::TransViewVector;
	LightVec	shape::ViewLightVector;					//PD 13Nov97
	FPMATRIX	shape::light_matrix;						//PD 13Nov97
	Bool		shape::ClearMorph;								//RJS 12Mar98
			static	SWord	vsin_ang;							//RJS 17Mar98
	SWord		shape::v_sin_ang;
	SWord		shape::v_cos_ang;

	UByte	shape::RandTable[256];						//RJS 17Nov97
	ViewPoint*	shape::View_Point;					//JIM

	SByte	shape::VapDeadList[REAL_MAX_VAPOURS];				//RJS 21Jan99
	int		shape::VapDeadCnt;									//RJS 09Apr98
	UWord 	shape::andedFlags;
	UWord 	shape::oredFlags;
	SWord 	shape::polyVertCount;
	DoPointStruc* shape::polyVertIndex[64];
	bool	shape::specularEnabled;
	bool	shape::doingHW3D;
	AirStrucPtr	shape::globinitairitem;							//RJS 13May98
	SWord	shape::oldAlphaSwitch;								//RJS 04Jun98
	Bool	shape::DamageNow;									//RJS 07Jul98
	SLong	shape::CollisionCnt;								//RJS 07Jul98
	Bool	shape::FixUpCollision;								//RJS 07Jul98
	SphTreeTypeP	shape::SphereTree;							//RJS 09Jul98
	SphTreeTypeP	shape::SphereTreeTable;						//RJS 09Jul98
	UByte	shape::SphereList[256];								//RJS 09Jul98
	SLong	shape::GlobSphereCnt;								//RJS 09Jul98
	Bool	shape::DrawnClouds;									//RJS 16Jul98
	ItemPtr	shape::damage_ItemPtr;	//RJS 25Aug98
	animptr	shape::damage_AnimPtr;								//RJS 21Apr99
	SLong	shape::damage_Scale;	//RJS 25Aug98
   ShapeNum shape::damage_Shape;	//RJS 16Sep98
    SLong	shape::damage_GrpElmt;	//RJS 16Sep98
	animptr	shape::damage_GrpAnimPrev;							//RJS 21Apr99
	animptr	shape::damage_GrpAnimNext;							//RJS 21Apr99
	UByteP	shape::damage_GrpPrev;
	UByteP	shape::damage_GrpNext;
	UByteP	shape::damage_Sdptr;
	SWord shape::dotNLineFadeValue;
	ItemPtr	shape::pTrailItm;						//RJS 02Sep98
	Float	shape::DistScale;
	UByte	shape::staticRed;									//PD 20Jan99
	UByte	shape::staticGreen;									//PD 20Jan99
	UByte	shape::staticBlue;									//PD 20Jan99
	UByte	shape::shadedRed;									//PD 20Jan99
	UByte	shape::shadedGreen;									//PD 20Jan99
	UByte	shape::shadedBlue;									//PD 20Jan99
	bool	shape::fSpecialShade;
	bool	shape::fPolyPitShade;
	animptr	shape::damage_GrpTokenDep;							//RJS 21Apr99
	animptr	shape::GlobalAdptr;									//RJS 21Apr99
	UByte	shape::damage_ItemState;							//RJS 26Apr99
	UByte	shape::current_level;
	UByte	shape::IsAircraft;

	bool	shape::oldMipMapState;								//RJS 24May99

	FPMATRIX		shape::subMatrix;							//DAW 07May99
	FPMATRIX_PTR	shape::subMatrixP;							//DAW 07May99

	SLong	shape::gunsightX;									//AMM 25Jun99
	SLong	shape::gunsightY;									//AMM 25Jun99
	SLong	shape::gunsightZ;									//AMM 25Jun99
	UWord	shape::gunsightmvel;								//AMM 25Jun99

	SLong	shape::animlag;										//RJS 30Jun99

#ifndef	NDEBUG
#ifdef	COLTRACE

#define AFX_CDECL __cdecl
typedef char CHAR;
#define CONST               const
typedef CONST CHAR *LPCSTR, *PCSTR;
typedef LPCSTR LPCTSTR;
void AFX_CDECL AfxTrace(LPCTSTR lpszFormat, ...);

#endif
#endif


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	shape::shape
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
shape::shape()
{
	InterpTable = new InterpProc*[dosetglassrangeno+1];			//RJS 01Dec97

	if (InterpTable)
	{
		InterpTable[dopointno] 				= &dopoint;
		InterpTable[dopolygonno] 			= &dopolygon;
		InterpTable[dosetlcno] 				= &dosetlc;
		InterpTable[dosetcolourno] 			= &dosetcolour;
		
		InterpTable[dolineno] 				= &doline;
		InterpTable[doretno] 				= &doret;
		InterpTable[doifcrossno] 			= &doifcross;
		InterpTable[dogosubno] 				= &dogosub;

		InterpTable[doifeqno] 				= &doifeq;
		InterpTable[doifneno] 				= &doifne;		
		InterpTable[donopno] 				= &donop;
		InterpTable[dogroupno] 				= &dogroup;

		InterpTable[dogotono] 				= &dogoto;
		InterpTable[doendno] 				= &doend;
		InterpTable[dowindowdialno] 		= &dowindowdial;	//RJS 06Apr98
		InterpTable[doattitudeno] 			= &doattitude;		//RJS 01Apr98

		InterpTable[dodotno] 				= &dodot;
		InterpTable[doscalesizeno] 			= &doscalesize;		//RJS 03Mar98
		InterpTable[dogunsightno] 			= &dogunsight;		//RJS 04Mar98
		InterpTable[dowheelsprayno] 		= &dowheelspray;

		InterpTable[doifbrightno] 			= &doifbright;		//RJS 20Mar98
		InterpTable[doquikpolyno] 			= &doquikpoly;
		InterpTable[dofadeenvelopeno] 		= &dofadeenvelope;	//RJS 27Mar98
		InterpTable[dowhiteoutno] 			= &dowhiteout;		//RJS 31Mar98

		InterpTable[donpointsno] 			= &donpoints;
		InterpTable[don4cmpntsno] 			= &don4cmpnts;
		InterpTable[do4cmpntno] 			= &do4cmpnt;
		InterpTable[dondupvecno] 			= &dondupvec;

		InterpTable[dondeltapointsno]		= &dondeltapoints;	//RJS 02Jun98
		InterpTable[dodrawsunno] 			= &dodrawsun;		//RJS 22Jun98
		InterpTable[dosetcolour256no] 		= &dosetcolour256;
		InterpTable[doswitchno] 			= &doswitch;

		InterpTable[dosetcolourallno] 		= &dosetcolourall;
		InterpTable[dopoint2xno] 			= &dopoint2x;
		InterpTable[do4cmpt2xno] 			= &do4cmpt2x;
		InterpTable[doifcaseno] 			= &doifcase;

		InterpTable[donincpntsno] 			= &donincpnts;
		InterpTable[dotransparentonno] 		= &dotransparenton;
		InterpTable[dotransparentoffno] 	= &dotransparentoff;
		InterpTable[dosphereno] 			= &dosphere;

		InterpTable[dosmokedonno] 			= &dosmokedon;
		InterpTable[dosmokedoffno] 			= &dosmokedoff;
		InterpTable[donormalno] 			= &donormal;
		InterpTable[dosmoothpolyno] 		= &dosmoothpoly;

		InterpTable[dovectorno] 			= &dovector;
		InterpTable[dotransformlightno] 	= &dotransformlight;
		InterpTable[dolshadeonno] 			= &dolshadeon;			//RJS 30Apr98
		InterpTable[dorelpolyno] 			= &dorelpoly;

		InterpTable[donspheresno]	 		= &donspheres;			//RJS 13Jul98
		InterpTable[donspheresimapdno]	 	= &donspheresimapd;		//RJS 13Jul98
		InterpTable[doweaponoffno] 			= &doweaponoff;			//RJS 13Jul98
		InterpTable[dodrawreflectpolyno] 	= &dodrawreflectpoly;	//RJS 26Aug98

		InterpTable[doresetanimno] 			= &doresetanim;		//RJS 13Nov98
		InterpTable[dospinno] 				= &dospin;				//RJS 19Nov98
		InterpTable[dosetcolourhno] 		= &dosetcolourh;
		InterpTable[doquiksmoothpolyno]		= &doquiksmoothpoly;

		InterpTable[doreposno] 				= &dorepos;
		InterpTable[dodepthcolourno] 		= &dodepthcolour;
		InterpTable[dodepthpolyno] 			= &dodepthpoly;
		InterpTable[doimagemapno] 			= &doimagemap;

		InterpTable[docreateipolyno] 		= &docreateipoly;
		InterpTable[docreateivertno] 		= &docreateivert;
		InterpTable[dodrawipolyno] 			= &dodrawipoly;
		InterpTable[docopyivertno] 			= &docopyivert;

		InterpTable[dosmthrelpolyno] 		= &dosmthrelpoly;
		InterpTable[doquikrelpolyno] 		= &doquikrelpoly;
		InterpTable[donsubsno] 				= &donsubs;
		InterpTable[dobitsofffxno] 			= &dobitsofffx;		//RJS 15Jan99

		InterpTable[doondamagedno] 			= &doondamaged;		//RJS 18Jan99
		InterpTable[dosetmipmapno] 			= &dosetmipmap;		//RJS 24May99
		InterpTable[donvecno] 				= &donvec;
		InterpTable[donextvecno] 			= &donextvec;

		InterpTable[donpoint2xno] 			= &donpoint2x;
		InterpTable[docallshapeno] 			= &docallshape;
		InterpTable[dosmokepntno] 			= &dosmokepnt;
		InterpTable[dobitsoffno] 			= &dobitsoff;

		InterpTable[doplumepntno] 			= &doplumepnt;
		InterpTable[doisphereno] 			= &doisphere;
		InterpTable[docreaterpolyno] 		= &docreaterpoly;
		InterpTable[dodrawipolysno] 		= &dodrawipolys;

		InterpTable[domappolyno] 			= &domappoly;
		InterpTable[dosetmapmapno] 			= &dosetmapmap;
		InterpTable[do3dbreakno] 			= &do3dbreak;
		InterpTable[docylinderno] 			= &docylinder;

		InterpTable[dontpointsno] 			= &dontpoints;
		InterpTable[dosetmapoffno] 			= &dosetmapoff;
		InterpTable[dosetmappingplanerno]	= &dosetmappingplaner;
		InterpTable[dosetmappingtanno] 		= &dosetmappingtan;

		InterpTable[dosmktrailno] 			= &dosmktrail;
		InterpTable[dooffsetpntno] 			= &dooffsetpnt;
		InterpTable[doicylinderno] 			= &doicylinder;
		InterpTable[dodrawbetweenno] 		= &drawbetween;

		InterpTable[docreatebumppolyno] 	= &docreatebpoly;
		InterpTable[docopybvertno] 			= &docopybvert;
		InterpTable[dodrawbpolyno] 			= &dodrawbpoly;
		InterpTable[dodrawrpolyno] 			= &dodrawrpoly;

		InterpTable[dodrawopolyno] 			= &dodrawopoly;
		InterpTable[dorealisphereno] 		= &dorealisphere;	//RJS 16Dec97
		InterpTable[dolauncherno] 			= &dolauncher;
		InterpTable[dodialno] 				= &dodial;

		InterpTable[docompassno] 			= &docompass;
		InterpTable[doiswitchno] 			= &doiswitch;
		InterpTable[doinclnno] 				= &doincln;
		InterpTable[doanimationno] 			= &doanimation;			//RJS 18Feb97

		InterpTable[docollisionno] 			= &docollision;			//RJS 18Feb97
		InterpTable[dodamageno] 			= &dodamage;			//RJS 18Feb97
		InterpTable[doeffectno] 			= &doeffect;			//RJS 18Feb97
		InterpTable[dodrawstationno]		= &dodrawstation;		//RJS 28Feb97
		InterpTable[docaserangeno]			= &docaserange;			//RJS 03Mar97
		InterpTable[doifpilotedno]			= &doifpiloted;			//RJS 07Mar97
		InterpTable[donivertsno]			= &doniverts;			//RJS 20Mar97

		InterpTable[dotrifanno]				= &dotrifan;			//RJS 27Mar97
		InterpTable[dotrizagno]				= &dotrizag;			//RJS 27Mar97
		InterpTable[dotrifanflatno]			= &dotrifanflat;		//RJS 16Apr97
		InterpTable[dotrizagflatno]			= &dotrizagflat;		//RJS 16Apr97

		InterpTable[dostretchpointno]		= &dostretchpoint;		//RJS 11Jun97
		InterpTable[dostretchmapno]			= &dostretchmap;		//RJS 11Jun97

		InterpTable[doflipvectorno]			= &doflipvector;		//RJS 30Jul97
		InterpTable[doflipnvecno]			= &doflipnvec;			//RJS 30Jul97

		InterpTable[domorphpointno]			= &domorphpoint;	//RJS 10Dec97
		InterpTable[domorphnpointsno]		= &domorphnpoints;	//RJS 10Dec97
		InterpTable[douserealtimeno]		= &douserealtime;	//RJS 10Dec97
		InterpTable[dotimerphaseno]			= &dotimerphase;	//RJS 10Dec97
		InterpTable[dobloblineno]			= &doblobline;		//RJS 15Dec97
		InterpTable[dowheeldamageno]		= &dowheeldamage;
		InterpTable[dolightno]				= &dolight;
		InterpTable[dolighttimerno]			= &dolighttimer;	//RJS 06Jan98
		InterpTable[dodigitdialno]			= &dodigitdial;		//RJS 08Jan98
		InterpTable[donianimvertsno]		= &donianimverts;	//RJS 13Jan98
		InterpTable[dosetluminosityno]		= &dosetluminosity;	//RJS 20Jan98
		InterpTable[dobitsoffcockno]		= &dobitsoffcock;	//RJS 23Jan98
		InterpTable[domorphsphereno]		= &domorphsphere;	//RJS 27Jan98
		InterpTable[domorphcylinderimapdno]	= &domorphsphereimapd;//RJS 19Nov98
		InterpTable[doheathazeno]			= &doheathaze;	//RJS 30Jan98

		InterpTable[doifhard3dno]			= &doifhard3d;			//RJS 04Feb98
		InterpTable[domorphnsphrsno]		= &domorphnsphrs;		//RJS 04Feb98
		InterpTable[domorphnsphrsimapdno]	= &domorphnsphrsimapd;	//RJS 04Feb98

		InterpTable[dosetglassrangeno] 		= &dosetglassrange;
		InterpTable[0] 						= &donop;				//RJS 11Feb98
	}
	else
		_Error.EmitSysErr(__FILE__":Could not create interptable!");

	int		i;

	shape_ptr = NULL;
	draw_data = NULL;

	globalanimtime.centisec =
		globalanimtime.tnthssec =
		globalanimtime.secs = 0;								//PD 08Mar96

	animflags = new UByte [MAXANIMFLAG];

	for (i=0; i < REAL_MAX_VAPOURS; i++)						//RJS 21Jan99
	{
		traillist[i].thelist = NULL;							//RJS 20Sep96
		traillist[i].lifetime = 0;								//RJS 29May97
		traillist[i].nopoints = 0;								//RJS 29May97
		traillist[i].bitshift = 0;								//RJS 29May97
		traillist[i].nextlist = 0;								//RJS 29May97
		traillist[i].beendrawn = 0;								//RJS 29May97
		traillist[i].LaunchCountdown = -1;						//RJS 25Nov97
		traillist[i].SampleTime = 0;							//RJS 08Jan98
		traillist[i].FakePointPtr = NULL;						//RJS 25Feb98
//DeadCode RJS 06May99 		traillist[i].InitVelH = 0;								//RJS 09Apr98
//DeadCode RJS 06May99 		traillist[i].InitVelY = 0;								//RJS 09Apr98
//DeadCode RJS 06May99 		traillist[i].Acceleration = 0;							//RJS 09Apr98
		traillist[i].SmkDescPtr = NULL;							//RJS 09Apr98
		traillist[i].cloudlaunched = FALSE;						//RJS 03Jul98
		traillist[i].transient = 0;								//RJS 22Jan99
		traillist[i].currTime = 0;								//RJS 16Jun99
	}

	for (i=0; i < 8; i++)
	{
		lastdamage[i] = 0;										//RJS 23Feb98
		laststationdamage[i] = 0;								//RJS 06Apr98
	}

	lastdamptr = 0;											//RJS 18Feb97
	HitThisOffset = 0;											//RJS 21Feb97
	CommsDamage = FALSE;										//RJS 21Feb97
	CollisionOn = FALSE;										//RJS 21Feb97

	VapourAnim = 0;												//RJS 20May97

	for (i = 0; i < 256; i++)									//RJS 17Nov97
		RandTable[i] = (Math_Lib.rnd() >> 8);					//RJS 17Nov97

	newco = shpco;												//RJS 02Dec97
	object_obj3d = NULL;										//RJS 18Mar98
	DoWhiteFade = 0;											//RJS 31Mar98
	VapDeadCnt = 0;

	ClosestGap = 1000000;
//	RequiredRange = 50000;										//MS 30Nov98
	RequiredRange = 40000;										//MS 30Nov98
	WingSpan = 35 * 16 * 2;
	ValidGunSight = FALSE;
	globinitairitem = NULL;
	FixUpCollision = FALSE;
	CollisionCnt = 0;

	AnimDeltaList = new ReplayAnimOffsets[sizeof(PolyPitAnimData)];
	SphereTree= NULL;											//RJS 09Jul98
	SphereTreeTable = new SphTreeType[256];						//RJS 09Jul98
	GlobSphereCnt = 0;											//RJS 09Jul98
	OldWhiteFade = 0;											//RJS 15Jul98
	DrawnClouds = FALSE;											//RJS 15Jul98
	MaxMuzzles = 0;
	damage_ItemPtr = NULL;
	damage_AnimPtr = NULL;
	damage_Scale = 0;
	pTrailItm = NULL;											//RJS 02Sep98
	damage_Shape = (ShapeNum) 0;
	damage_Sdptr = NULL;

	animptr	poo;												//RJS 21Apr99
	SetGroupDamage(-1,NULL,NULL,poo,poo,poo);					//RJS 21Apr99

	ClosestGap2 = 1000000;										//RJS 09Nov98

	shititem = NULL;

	damage_GrpTokenDep = NULL;									//RJS 12Feb99
	newprobecnt = 0;											//AMM 26Mar99

//DeadCode AMM 14Apr99 	safeTrail = FALSE;
	radarTimer = -1;											//RJS 07Apr99
	fSpecialShade=false;
	fPolyPitShade=false;
	globinititem = NULL;

	damage_ItemState = 0;										//AMM 26Apr99

	subMatrixP = &subMatrix;
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		shape
//Author		Paul.   
//Date			Mon 15 Jan 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
shape::~shape()
{
	delete InterpTable;											//RJS 01Dec97
	delete []AnimDeltaList;											  //JIM 02/05/99
	delete animflags;											//PD 27Mar96
	delete []SphereTreeTable;									//RJS 09Jul98
	pTrailItm = NULL;											//RJS 02Sep98
}

inline double ARCCOS(double x,double pi)
{
	double temp=(1.-x*x)/(x*x);
	bool xneg=x<0?true:false;
	_asm{
		fld temp;
		fsqrt;
		fld1;
		fpatan;
		fstp temp;
	}
	if (xneg) temp=pi-temp;
	return temp;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		calcSpecular
//Author		Paul.   
//Date			Tue 25 Aug 1998
//
//Description	generates a value to be used for specular lighting
//				based on the dot product of the light and view vectors
//				with the vertex normal.
//
//Inputs		result of the two dot products
//
//Returns	
//
//------------------------------------------------------------------------------
void calcSpecular(Float& specDot,Float& lightDot,SLong& specular,SLong& specFlip)
{
	double pi;
	_asm
	{
		fldpi;
		fstp pi;
	}

	double spa=ARCCOS(specDot,pi);
	double lia=ARCCOS(lightDot,pi);

	if (spa<pi/2. && lia<pi/2.)
	{
		double delta=spa-lia; delta=delta<0?-delta:delta;

		if (delta<pi/4.)
		{
			delta=double(specMax)*(1.-delta/(pi/4.));
			specFlip=SLong(delta);
			if (specFlip<0)	specFlip=0;
			else if (specFlip>specMax) specFlip=specMax;
		}
		else specFlip=0;
	}
	else specFlip=0;

	spa+=pi; if (spa>pi) spa=2*pi-spa;
	lia+=pi; if (lia>pi) lia=2*pi-lia;

	if (spa<pi/2. && lia<pi/2.)
	{
		double delta=spa-lia; delta=delta<0?-delta:delta;

		if (delta<pi/4.)
		{
			delta=double(specMax)*(1.-delta/(pi/4.));
			specular=SLong(delta);
			if (specular<0)	specular=0;
			else if (specular>specMax) specular=specMax;
		}
		else specular=0;
	}
	else specular=0;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UpdateGlobalFlags
//Author		Paul.   
//Date			Fri 8 Mar 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::UpdateGlobalFlags(int ft)
{
	SLong	temp;

	temp = globalanimtime.centisec + ft;//Timer_Code.frametime;		//PD 15Mar96

	if(temp<globalanimtime.centisec)	//Wrapped arround
	{
		temp = globalanimtime.centisec - 0x07FFFFFFF;
		temp = temp + current_screen->FrameTime();//Timer_Code.frametime;						//PD 15Mar96
	}

	globalanimtime.centisec = temp;
	globalanimtime.tnthssec = temp/10;
	globalanimtime.secs = temp/100;

	//PD 16Apr96 - test code

//	PolyPitAnimData* adptr = (PolyPitAnimData* )Manual_Pilot.ControlledAC2->Anim;
}

//DeadCode PD 10Jun97 Bool	bZBufferLock;
Bool	bOldZState;

Bool	bPlayerTextures;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetLineAndDotShade
//Author		Paul.   
//Date			Mon 2 Nov 1998
//------------------------------------------------------------------------------
void shape::SetLineAndDotShade(itemptr ip,ViewPoint* vp)
{
	const SLong FADE_DIST=FT_50;
	const SLong HALF_FADE_DIST=FADE_DIST>>1;
	if (ip && vp && ((ip->shape==DSPARK) || (ip->shape==BULLET) || (IsAircraft && current_level>=2)))
	{
		Float fintensity=-TransLightVector.nj.f*TransViewVector.nj.f;
		fintensity*=Float(32385);
		SLong top_intens=fintensity;
		top_intens+=32385;
		top_intens/=232;
		top_intens=280-top_intens;
		if (top_intens>256)	top_intens=256;
		else if (top_intens<0) top_intens=0;
		dotNLineFadeValue=top_intens;
	}
	else dotNLineFadeValue=-1;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	shape::process_shape
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void shape::process_shape(	Window 	*screen,ViewPoint* vp,					//JIM 12Dec95
							Obj3DPtr 		this_obj3d,			//PD 13Mar96
							FPMATRIX_PTR 	this_matrix,
							Bool			subshape,			//RJS 15Jan99
							FPMATRIX_PTR 	this_objmatrix)		//RJS 15Jan99
{
	if (fPolyPitShade)
	{
		staticRed=Land_Scape.currentLighting.cockpitAmbientCol.red();
		staticGreen=Land_Scape.currentLighting.cockpitAmbientCol.green();
		staticBlue=Land_Scape.currentLighting.cockpitAmbientCol.blue();
		shadedRed=Land_Scape.currentLighting.cockpitAmbientCol.red();
		shadedGreen=Land_Scape.currentLighting.cockpitAmbientCol.green();
		shadedBlue=Land_Scape.currentLighting.cockpitAmbientCol.blue();
	}
	else if (fSpecialShade)
	{
		staticRed=Land_Scape.currentLighting.landAmbientCol.red();
		staticGreen=Land_Scape.currentLighting.landAmbientCol.green();
		staticBlue=Land_Scape.currentLighting.landAmbientCol.blue();
		shadedRed=Land_Scape.currentLighting.landAmbientCol.red();
		shadedGreen=Land_Scape.currentLighting.landAmbientCol.green();
		shadedBlue=Land_Scape.currentLighting.landAmbientCol.blue();
	}
	else
	{
		staticRed=Land_Scape.currentLighting.staticAmbientCol.red();
		staticGreen=Land_Scape.currentLighting.staticAmbientCol.green();
		staticBlue=Land_Scape.currentLighting.staticAmbientCol.blue();
		shadedRed=Land_Scape.currentLighting.shadedAmbientCol.red();
		shadedGreen=Land_Scape.currentLighting.shadedAmbientCol.green();
		shadedBlue=Land_Scape.currentLighting.shadedAmbientCol.blue();
	}

	screen->DoSetShadeVals(staticRed,staticGreen,staticBlue,
							Land_Scape.currentLighting.effectsAmbientCol.red(),
							Land_Scape.currentLighting.effectsAmbientCol.green(),
							Land_Scape.currentLighting.effectsAmbientCol.blue());

	specularEnabled=false;
	if (!subshape) current_level=0;
	IsAircraft=(this_obj3d->ItemPtr && this_obj3d->ItemPtr->Status.size==AirStrucSize)?1:0;
	fpobject_matrix = this_matrix;
	fprealobject_matrix = this_objmatrix;						//RJS 15Jan99
	object_obj3d  = this_obj3d;
	current_screen = screen;
	doingHW3D=(current_screen->DoingHardware3D())?true:false;	//PD 19Jun98
	current_screen->DoCalcItemFog(	true,
									this_obj3d->Body.X.f,
									this_obj3d->Body.Y.f,
									this_obj3d->Body.Z.f);		//PD 09Sep98

	//pre-calculate pseudo lighshading values for dots and lines
 	SetLineAndDotShade(object_obj3d->ItemPtr,vp);

	bPlayerTextures=FALSE;										//PD 20Jun97
	if (object_obj3d->ItemPtr==Manual_Pilot.ControlledAC2)
	{
		bPlayerTextures=TRUE;									//PD 20Jun97
		current_screen->DoSetPlayerTextures(TRUE);
	}
	VapourCyl = FALSE;											//RJS 14May97
	IsSubShape = subshape;										//RJS 03Jun97

	if (Save_Data.detail_3d[DETAIL3D_ITEMSHADING])				//PD 10Dec98
			View_Point->isLightShaded = TRUE;					//PD 10Dec98
	else														//PD 10Dec98
			View_Point->isLightShaded = FALSE;					//PD 10Dec98
	current_screen->DoSetLShade(false);							//RJS 30Apr98
	oldAlphaSwitch = -1;										//RJS 04Jun98
																//RJS 30Apr98
	GlobalAdptr = this_obj3d->AnimPtr;							//RJS 21Apr99

	oldMipMapState = true;										//RJS 24May99

	draw_shape(this_obj3d);										//RJS 30Apr98
																//RJS 30Apr98
	View_Point->isLightShaded = TRUE;							//RJS 30Apr98
	current_screen->DoSetLShade(false);							//RJS 30Apr98
//DEAD	POLYGON.SetCrossProduct(TRUE);								//PD 11Dec96
	if (doingHW3D)												//PD 19Jun98
	{
		current_screen->DoSetPlayerTextures(FALSE);
		current_screen->DoCalcItemFog(	false,
										this_obj3d->Body.X.f,
										this_obj3d->Body.Y.f,
										this_obj3d->Body.Z.f);	//PD 09Sep98
	}															//PD 06Jun97
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	shape::animate_shape
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void shape::animate_shape(Obj3DPtr thisobj3d)
{
	if (!Three_Dee.shapecheat && thisobj3d->ItemPtr!=Persons2::PlayerGhostAC)									//RJS 09Dec97
	{
		ShapeDescPtr	sdptr;

		animptr	adptr;											//RJS 21Apr99

 		object_obj3d  = thisobj3d;									//RJS 19Jun97

		adptr = thisobj3d->AnimPtr;								//RJS 21Apr99

		sdptr = SHAPESTUFF.GetShapePtr((ShapeNum)thisobj3d->Shape);

		// We need this for smoke launchers......				//MS 30Nov98
//DEADCODE DAW 23/04/99  		switch (SHAPESTUFF.GetShapeScale(sdptr))				//MS 30Nov98
//DEADCODE DAW 23/04/99  		{														//MS 30Nov98
//DEADCODE DAW 23/04/99  			case SHP_GRP:										//MS 30Nov98
//DEADCODE DAW 23/04/99  				_Error.EmitSysErr(__FILE__":Bad shape type field (SHAPE NUMBER %d)",thisobj3d->Shape);//MS 30Nov98
//DEADCODE DAW 23/04/99  				break;											//MS 30Nov98
//DEADCODE DAW 23/04/99  			case SHP_1CM:										//MS 30Nov98
//DEADCODE DAW 23/04/99  				shapescale = 0;									//MS 30Nov98
//DEADCODE DAW 23/04/99  				break;											//MS 30Nov98
//DEADCODE DAW 23/04/99  			case SHP_4CM:										//MS 30Nov98
//DEADCODE DAW 23/04/99  				shapescale = 2;									//MS 30Nov98
//DEADCODE DAW 23/04/99  				break;											//MS 30Nov98
//DEADCODE DAW 23/04/99  			case SHP_16CM:										//MS 30Nov98
//DEADCODE DAW 23/04/99  				shapescale = 4;									//MS 30Nov98
//DEADCODE DAW 23/04/99  				break;											//MS 30Nov98
//DEADCODE DAW 23/04/99  		}														//MS 30Nov98
		// ....We need this for smoke launchers					//MS 30Nov98

		UByte	vaptype = sdptr->Type.VapourType;				//RJS 21Jan99

		//Call the correct anim routine in this case statement

		if (sdptr->AnimDataSize > -1)
		{
			switch (sdptr->AnimDataSize)
			{
				case POLYPITANIM:										//PD 15Apr96
					PolyPitItemAnim((PolyPitAnimData *)adptr);
					break;

				case BLOKESANIM:								//RJS 01Jun99
					BlokesItemAnim((BlokesAnimData* )adptr);	//RJS 01Jun99
					break;										//RJS 01Jun99

				case WEAPANIM:											//PD 01Apr96
					WeapItemAnim((WeapAnimData* )adptr);
					break;

				case AIRCRAFTANIM:
					AircraftAnim((AircraftAnimData* )adptr);			//RJS 09Jan97
					break;

				case SUNANIM:											//PD 24Jun96
					SunItemAnim((SunAnimData* )adptr);					//PD 24Jun96
					break;												//PD 24Jun96

//DeadCode RJS 21Jan99 				case FLAMEANIM:
//DeadCode RJS 21Jan99 					FlameItemAnim((FireAnimData *)adptr);
//DeadCode RJS 21Jan99 					break;

//DeadCode RJS 21Jan99 				case BALLOONANIM:										//RJS 05Aug96
//DeadCode RJS 21Jan99 					BalloonItemAnim((BalloonAnimData *)adptr,thisobj3d);
//DeadCode RJS 21Jan99 					break;
				case WINDSOCANIM:									//RJS 05Jun97
					WindsockItemAnim((WindsocAnimData*) adptr);		//RJS 05Jun97
					break;

				case BARAGEANIM:										//RJS 24Sep96
					BarageItemAnim((BarageAnimData*) adptr);
					break;

//DeadCode RJS 21Apr99 				case FIREBALLANIM:										//RJS 07Oct96
//DeadCode RJS 21Apr99 					FireballItemAnim((ExplodeAnimData*) adptr);		//RJS 09Jan97
//DeadCode RJS 21Apr99 					break;
				case MOVEGUNANIM:
					if (!sdptr->Type.VapourType)						//RJS 10Mar98
						MoveGunItemAnim((MoveGunAnimData*) adptr);	//RJS 04Jun97
					break;
				case TANKANIM:
					TankItemAnim((MoveGunAnimData*) adptr);				//RJS 17Oct96
					break;
				case TRUCKANIM:
					TruckItemAnim((MoveGunAnimData*) adptr,(UByteP)sdptr);	//RJS 18May99
					break;
 				case TRAINANIM:
 					TrainItemAnim((TrainAnimData*) adptr);				//RJS 07Feb97
 					break;
				case TROOPANIM:
					TroopItemAnim((TroopAnimData*) adptr,(TroopAnimData*)thisobj3d->ItemPtr->Anim);//RJS 06Dec96
					break;
//DeadCode RJS 21Apr99 				case BRIDGEANIM:
//DeadCode RJS 21Apr99 					BridgeItemAnim((ExplodeAnimData*) adptr);			//RJS 20Nov96
//DeadCode RJS 21Apr99 					break;
				case SMOKETRAILANIM:
					vaptype = TRAIL_OFF;
					ProbeStaticTrail((UByteP)sdptr,thisobj3d->ItemPtr,adptr);
					break;
				case PARACHUTEANIM:
				{
					if (thisobj3d->ItemPtr->Status.size == TRANSIENTSIZE)
					{
						TransientItem*	targ = (TransientItem*) thisobj3d->ItemPtr;
						if (targ->isOwned && targ->Target)
						{
							Coords3D	oldcoords;
							TransientItem*	theChute = (TransientItem*)targ->Target; 
							oldcoords = theChute->World;
							theChute->World = thisobj3d->ItemPtr->World;
//DeadCode RJS 27Apr99							theChute->uniqueID.changed = TRUE;

							Three_Dee.StuffInBinaryTree(theChute);//DAW 23Apr99
							theChute->World = oldcoords;
						}
					}
				}	 
				break;
			}
		}

#ifndef	_NOSMOKETRAILS_														//RJS 08Apr99
		switch (vaptype)							//RJS 10Mar98
		{
			case TRAIL_NORMAL:
			case TRAIL_STATIC:
				UpdateVapourCoords(thisobj3d->ItemPtr,adptr);	//DAW 23Apr99
				break;
			case TRAIL_GROUND:
				UpdateSmokeDriftCoords(thisobj3d->ItemPtr,adptr);//DAW 23Apr99
				break;
		}
#else
		#pragma message (__HERE__ "Smoke-trails disabled!")
#endif
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		sfx_shape
//Author		Robert Slater
//Date			Mon 20 Apr 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::sfx_shape(ItemPtr	itm, IFShare	bx, IFShare	by, IFShare	bz)
{
	if (itm->Status.size == FORMATIONSIZE)						//RJS 17May99
	{															//RJS 17May99
		if (	(((FormationItemPtr)itm)->leader != NULL)		//RJS 17May99
			&&	(((FormationItemPtr)itm)->follower != NULL)	)	//RJS 17May99
			return;												//RJS 17May99
	}															//RJS 17May99

	ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(itm->shape);	//RJS 17May99
	switch (sdptr->AnimDataSize)								//RJS 17May99
	{															//RJS 17May99
		case TANKANIM:											//RJS 17May99
		case TRUCKANIM:											//RJS 17May99
		case TRAINANIM:											//RJS 17May99
			break;												//RJS 17May99
		default:												//RJS 17May99
			return;												//RJS 17May99
	}															//RJS 17May99
																//RJS 17May99
	SLong	disx = SLong(bx.f);									//RJS 17May99
	SLong	disy = SLong(by.f);									//RJS 17May99
	SLong	disz = SLong(bz.f);									//RJS 17May99
																//RJS 17May99
	disx = (disx<0)?-disx:disx;									//RJS 17May99
	disy = (disy<0)?-disy:disy;									//RJS 17May99
	disz = (disz<0)?-disz:disz;									//RJS 17May99
																//RJS 17May99
	if (	(disx < 150000)										//RJS 17May99
		&&	(disy < 150000)										//RJS 17May99
		&&	(disz < 150000)	)									//RJS 17May99
	{															//RJS 17May99
		MinAnimData		*mad = (MinAnimData*) itm->Anim;		//RJS 17May99
		if (mad->itemstate == ALIVE)							//RJS 17May99
		{
			switch (sdptr->AnimDataSize)
			{
				case TANKANIM:
					_Miles.PlayDelayed(FIL_SFX_TANK_LOOP1,itm,128,TRUE);//PD 13Aug99
					break;
				case TRUCKANIM:
					_Miles.PlayDelayed(FIL_SFX_TRUCK_NORM_LOOP,itm,128,TRUE);//PD 13Aug99
					break;
				case TRAINANIM:
					_Miles.PlayDelayed(FIL_SFX_TRAIN_LOOP, itm,128,TRUE);//PD 13Aug99
					break;
			}
		}
		else
		{
			if (sdptr->AnimDataSize == TRAINANIM)
				_Miles.PlayDelayed(FIL_SFX_SMALL_FIRE_LOOP,itm,128,TRUE);//PD 13Aug99
		}
	}
}

static	UByteP	shphedr;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	shape::draw_shape
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void shape::draw_shape(Obj3DPtr this_obj3d)						//PD 13Mar96
{
	UWord 	instruction;
	int		cnt;
	MinAnimData*	mad = (MinAnimData*) GlobalAdptr;				//RJS 22Apr99

	ShapeDescPtr	header_ptr;

	UByte 	*instr_ptr;

	object_dist=(SLong)this_obj3d->realbz.f;
	fade_start	=200000;	//Land_Scape.GetFadeStart();		//PD 19Dec96
	fade_end  	=400000;	//Land_Scape.GetFadeEnd();			//PD 19Dec96

	SHAPESTUFF.shape_image_mem = 0;
	SHAPESTUFF.shape_alpha_mem = 0;
	
	animlag = 0;													//RJS 30Jun99
	header_ptr = SHAPESTUFF.GetShapePtr((ShapeNum)this_obj3d->Shape);
	if (header_ptr->AnimDataSize == AIRCRAFTANIM)					//RJS 30Jun99
	{
		AircraftAnimData*	adptr = (AircraftAnimData*)GlobalAdptr;
		animlag = adptr->timenotvis;
	}

	shphedr = (UByteP)header_ptr;
//DeadCode PD 05Oct98 	switch(SHAPESTUFF.GetShapeScale(header_ptr))				//PD 23Apr96
//DeadCode PD 05Oct98 	{
//DeadCode PD 05Oct98 		case SHP_1CM:
//DeadCode PD 05Oct98 			shapescale = 0;										//PD 10Apr96
//DeadCode PD 05Oct98 			break;												//PD 10Apr96
//DeadCode PD 05Oct98 
//DeadCode PD 05Oct98 		case SHP_4CM:
//DeadCode PD 05Oct98 			shapescale = 2;										//PD 10Apr96
//DeadCode PD 05Oct98 			break;												//PD 10Apr96
//DeadCode PD 05Oct98 
//DeadCode PD 05Oct98 		case SHP_16CM:
//DeadCode PD 05Oct98 			shapescale = 4;										//PD 10Apr96
//DeadCode PD 05Oct98 			break;												//PD 10Apr96
//DeadCode PD 05Oct98 
//DeadCode PD 05Oct98 		case SHP_GRP:
//DeadCode PD 05Oct98 			_Error.EmitSysErr(__FILE__"Bad shape type field (SHAPE NUMBER %d)",this_obj3d->Shape);
//DeadCode PD 05Oct98 			break;
//DeadCode PD 05Oct98 	}

 	DrawHitBox(current_screen,object_obj3d,NULL);
	instr_ptr =(UByte *)header_ptr;							//RJS 16Nov98
	switch (mad->itemstate)									//RJS 16Nov98
	{														//RJS 16Nov98
	case ALIVE:												//RJS 16Nov98
		instr_ptr += header_ptr->liveshpref;				//RJS 16Nov98
		break;												//RJS 16Nov98
	case DAMMAGED:											//RJS 16Nov98
		instr_ptr += header_ptr->damagedshpref;				//RJS 16Nov98
		break;												//RJS 16Nov98
	case DYING:												//RJS 16Nov98
		instr_ptr += header_ptr->dyingshpref;				//RJS 16Nov98
		break;												//RJS 16Nov98
	case DEAD:												//RJS 16Nov98
		instr_ptr += header_ptr->deadshpref;				//RJS 16Nov98
		break;												//RJS 16Nov98
	}														//RJS 16Nov98

	if (header_ptr->AnimDataSize == AIRCRAFTANIM)			//RJS 30Jun99
	{
		AircraftAnimData*	adptr = (AircraftAnimData*)GlobalAdptr;
		adptr->timenotvis = 0;
	}

//TempCode RJS 16Nov98 	if (header_ptr->AnimDataSize == AIRCRAFTANIM)
//TempCode RJS 16Nov98 		Image_Map.DoingAC = TRUE;
//TempCode RJS 16Nov98 
//TempCode RJS 16Nov98 	if (header_ptr->AnimDataSize == POLYPITANIM)
//TempCode RJS 16Nov98 		Image_Map.DoingCock = TRUE;

	InterpLoop(instr_ptr);									//RJS 16Nov98

//TempCode RJS 16Nov98 	Image_Map.DoingAC = FALSE;
//TempCode RJS 16Nov98 	Image_Map.DoingCock = FALSE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//					    SHAPE INSTRUCTIONS
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dopoint
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void shape::dopoint(UByte *& instr_ptr)
{
	DOPOINT_PTR ptr = (DOPOINT_PTR )instr_ptr;
	DoPointStruc* dp=newco+UWord(ptr->vertex);
	dp->bodyx.i = ptr->xcoord;
	dp->bodyy.i = ptr->ycoord;
	dp->bodyz.i = ptr->zcoord;
	_matrix.transformNC(fpobject_matrix,dp);
	dp->bodyx.f +=object_obj3d->Body.X.f;
	dp->bodyy.f +=object_obj3d->Body.Y.f;
	dp->bodyz.f +=object_obj3d->Body.Z.f;
	_matrix.SetClipFlags(*dp);
//	if (!doingHW3D) _matrix.body2screen(*dp);					//PD 19Jun98
	dp->intensity=
	dp->specFlip=
	dp->specular=-1;												//PD 24Aug98
	instr_ptr+=sizeof(DOPOINT);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dopolygon
//LastModified:	PD 24Apr98
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void shape::dopolygon(UByte *& instr_ptr)
{
	DOPOLYGON_PTR poly_data=(DOPOLYGON_PTR)instr_ptr;
	int j=poly_data->edges;
	oredFlags=CF3D_NULL;
	andedFlags=CF3D_ALL;
	UWord* vertices=(UWord*)(instr_ptr+sizeof(DOPOLYGON));
	DoPointStruc** pDp=polyVertIndex;
	for (int i=0;i<j;i++){
		DoPointStruc& dp=newco[*vertices++];
		oredFlags|=dp.clipFlags;
		andedFlags&=dp.clipFlags;
		*pDp++=&dp;
	}
	//test clip flags before drawing the polygon...
	bool clipping=(oredFlags!=CF3D_NULL)?true:false;
	bool visible=(andedFlags==CF3D_NULL)?true:false;
	if (visible){
		//if 'clipping' is false then this poly will not need any clipping
		clipping=current_screen->DoSetClipState(clipping);
		POLYGON.createpoly(shape::colour);
		pDp=polyVertIndex;
		for (i=0;i<j;i++){
			DoPointStruc& dp=**pDp++;
			SWord iVal=dp.intensity;
			if (iVal < 0) POLYGON.createvert(dp);//RJS 13Jul98
			else{
//				iVal+=255;
				POLYGON.createvert(dp,iVal);	//RJS 13Jul98
			}
		}
		POLYGON.drawpoly();
		current_screen->DoSetClipState(clipping);
	}
   	instr_ptr+=sizeof(DOPOLYGON)+(UWord)poly_data->edges * sizeof(UWord);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dosetlc
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
 void shape::dosetlc(UByte *& instr_ptr)
{
	instr_ptr += sizeof(DOSETLC);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dosetcolour
//LastModified:	PD 10Jul96
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
 void shape::dosetcolour(UByte *& instr_ptr)
{
	ImageMapNumber	imapno;
	SLong	flag;												//RJS 12Feb97
//DeadCode RJS 21Apr99 	UByteP	adptr = (UByteP) object_obj3d->AnimPtr;				//RJS 18Feb97

	DOSETCOLOUR_PTR	dscptr = (DOSETCOLOUR_PTR )instr_ptr;

	imapno = (ImageMapNumber )(dscptr->imageno);

//DeadCode RJS 01Apr98 	imapno = (ImageMapNumber )((imapno<0)?-imapno:imapno);

	ImageMapDescPtr imptr = Image_Map.GetImageMapPtr(imapno);

	flag = GlobalAdptr[dscptr->flagname];						//RJS 16Apr99
//DeadCode RJS 12Feb97 	flag = *(animflags+flag);

	flag <<= 6;		// * 64

	flag *= imptr->w;											//RJS 06Feb98

	Colour base_colour = (Colour )(*(imptr->body)+flag);

/*	SWord intense = Three_Dee.IntensFromRange(object_dist,fade_start,fade_end);

 	intense = intense>>4;

	if (intense)												//RJS 27Jun97
	{
		SLong	temp1,temp2;

		temp1 = (SLong )base_colour;
		temp1 &= 0x0FF;

		temp2 = intense;
		temp1 = ASM_GetFadeColour(temp1,temp2);

		base_colour = (Colour )temp1;
	}
*/
	shape::colour = base_colour;

	current_screen->SetColour(base_colour);

	instr_ptr += sizeof(DOSETCOLOUR);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	doline
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
 void shape::doline(UByte *& instr_ptr)
{
	LINETYPE	ltLine;
	struct		vertex	startVertex,endVertex;

 	SWord start_vertex,end_vertex;								//PD 08Jan96
	Float	z0,z1;

	SetLineAndDotShade(object_obj3d->ItemPtr,View_Point);
	
 	DOLINE_PTR ptr = (DOLINE_PTR )instr_ptr;
 
 	start_vertex = (SWord )ptr->start_vertex;					//RJS 10Mar97
 	end_vertex	 = (SWord )ptr->end_vertex;					//RJS 10Mar97
 
	ltLine.ltType 			= LineType::LT_PlainColour;

	ltLine.lpStartVertex 	= &startVertex;
	startVertex.bx			= newco[start_vertex].bodyx;
	startVertex.by			= newco[start_vertex].bodyy;
	startVertex.bz			= newco[start_vertex].bodyz;
	startVertex.clipFlags	= newco[start_vertex].clipFlags;
	startVertex.intensity	= dotNLineFadeValue;

	ltLine.lpEndVertex 		= &endVertex;
	endVertex.bx			= newco[end_vertex].bodyx;
	endVertex.by			= newco[end_vertex].bodyy;
	endVertex.bz			= newco[end_vertex].bodyz;
	endVertex.clipFlags	= newco[end_vertex].clipFlags;
	endVertex.intensity	= dotNLineFadeValue;

	ltLine.colour			= shape::colour;

	if (current_screen->DoHardLine(&ltLine)==FALSE)
	{
//DEAD		z0 = newco[start_vertex].bodyz.f;
//DEAD 		z1 = newco[end_vertex].bodyz.f;

//DEAD 		current_screen->zclipline(newco[start_vertex],newco[end_vertex]);
 	
//DEAD 		if ((z0>0)&&(z1>0))
//DEAD 		{
//DEAD			_matrix.body2screen(newco[start_vertex]);
//DEAD 			_matrix.body2screen(newco[end_vertex]);
  	
//DEAD 			current_screen->ClipLine3D(	newco[start_vertex].screenx.f,//JIM 12Dec95
//DEAD 								   		newco[start_vertex].screeny.f,
//DEAD 								   		newco[end_vertex].screenx.f,
//DEAD 								   		newco[end_vertex].screeny.f);
//DEAD  		}
		POLYGON.DoLine3D(shape::colour,newco[start_vertex],newco[end_vertex]);
	}
	else
	{
		POINTTYPE	ptPointType;
		ptPointType.lpVertex= &startVertex;

		Float maxDotZ=200000;
		if (startVertex.bz.f>maxDotZ)
		{
		 	Float xyDiv=maxDotZ/startVertex.bz.f;
			startVertex.bz.f=maxDotZ;
			startVertex.bx.f*=xyDiv;
			startVertex.by.f*=xyDiv;
		}
		startVertex.clipFlags&~CF3D_PASTFARZ;
		ptPointType.ptType	= PointType::PT_PlainColour;
		ptPointType.colour	= shape::colour;
		current_screen->DoHardPoint(&ptPointType);
	}
	instr_ptr += sizeof(DOLINE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	doret
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
 void shape::doret(UByte *& )									//PD 04Jan96
{
	//Empty
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	doifcross
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
 void shape::doifcross(UByte *& instr_ptr)
{
	SWord	v1, v2, v3;											//PD 04Jan96

	DOIFCROSS_PTR ptr = (DOIFCROSS_PTR)instr_ptr;

	v1 = (SWord )ptr->vertex1;									//RJS 10Mar97
	v2 = (SWord )ptr->vertex2;									//RJS 10Mar97
	v3 = (SWord )ptr->vertex3;									//RJS 10Mar97

	if(!_matrix.crossproduct(newco[v1],newco[v2],newco[v3]))
//Old_Code PD 06Dec96 	if(!_matrix.accuratecrossproduct(newco[v1],newco[v2],newco[v3]))
	{
		instr_ptr += ptr->offset;
	}
	else
	{
		instr_ptr += sizeof(DOIFCROSS);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dogosub
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
 void shape::dogosub(UByte *& instr_ptr)
{
	UByte 	*old_ptr;

	old_ptr = instr_ptr;

	instr_ptr += *(SWord *)instr_ptr;	//Signed word offset from the
										//current position.

	InterpLoop(instr_ptr);

	instr_ptr = old_ptr + sizeof(SWord);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	doifeq
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
 void shape::doifeq(UByte *& instr_ptr)
{
	instr_ptr += sizeof(DOIFEQ);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	doifne
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
 void shape::doifne(UByte *& instr_ptr)
{
	instr_ptr += sizeof(DOIFNE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	donop
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
 void shape::donop(UByte *& )									//PD 29Nov95
{
	_Error.EmitSysErr(__FILE__":Not a real instruction (DONOP)\n");
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dogroup
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
 void shape::dogroup(UByte *& )									//PD 29Nov95
{
	_Error.EmitSysErr(__FILE__":Not a real instruction (DOGROUP)\n");
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dogoto
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
 void shape::dogoto(UByte *& instr_ptr)
{
	instr_ptr += *(SWord *)instr_ptr;//RJS 17Jun98
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	doend
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
 void shape::doend(UByte *& )
{
	_Error.EmitSysErr(__FILE__":Not a real instruction (DOEND), shape %d\n",object_obj3d->Shape);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		dowindowdial
//Author		Robert Slater
//Date			Tue 6 Apr 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void shape::dowindowdial(UByte *& instr_ptr)
{
	DOWINDOWDIAL_PTR ptr = (DOWINDOWDIAL_PTR )instr_ptr;
	SWord			minx, miny, maxx, maxy;
//DeadCode RJS 21Apr99 	UByteP			adptr = (UByteP) object_obj3d->AnimPtr;
	SLong			val;
	SWord			rwidth, rheight;
	SLong			maxshift;

	switch (ptr->nobytes)
	{
	case 1:
		val = GlobalAdptr[ptr->animoffset];						//RJS 16Apr99
		maxshift = 8;
		break;
	case 2:
		val = *((UWordP)&GlobalAdptr[ptr->animoffset]);			//RJS 16Apr99
		maxshift = 16;
		break;
	case 4:
		val = *((ULongP)&GlobalAdptr[ptr->animoffset]);			//RJS 16Apr99
		maxshift = 32;
		break;
	}
	oredFlags=CF3D_NULL;
	andedFlags=CF3D_ALL;

	oredFlags|=newco[0].clipFlags;
	oredFlags|=newco[1].clipFlags;
	oredFlags|=newco[2].clipFlags;
	oredFlags|=newco[3].clipFlags;

	andedFlags&=newco[0].clipFlags;
	andedFlags&=newco[1].clipFlags;
	andedFlags&=newco[2].clipFlags;
	andedFlags&=newco[3].clipFlags;
	if (andedFlags==0)
	{
		rwidth = ptr->winwidth;
		rheight = ptr->winheight;

		minx = ptr->minx;
		miny = ptr->miny;

		if (ptr->issigned)
		{
			if (ptr->shiftx)
				minx += (val * ptr->width)/510;

			if (ptr->shifty)
				miny += (val * ptr->height)/510;
		}
		else
		{
			if (ptr->shiftx)
			{
				minx += (val * ptr->width)>>maxshift;
				minx-=(rwidth/2);
			}

			if (ptr->shifty)
			{
				miny += (val * ptr->height)>>maxshift;
				miny-=(rheight/2);
			}
		}

		maxx = minx + rwidth;
		maxy = miny + rheight;

		POLYGON.createpoly((ImageMapNumber) ptr->imagemap);
 		POLYGON.createvert(newco[0],minx,miny);
 		POLYGON.createvert(newco[1],maxx,miny);
 		POLYGON.createvert(newco[2],maxx,maxy);
 		POLYGON.createvert(newco[3],minx,maxy);
		POLYGON.drawpoly();
	}

	instr_ptr += sizeof(DOWINDOWDIAL);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		doattitude
//Author		Robert Slater
//Date			Wed 1 Apr 1998
//
//Description	Imagemapped cockpit attitude dial thing
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void shape::doattitude(UByte *& instr_ptr)
{
	DOATTITUDE_PTR	ptr = (DOATTITUDE_PTR) instr_ptr;
	ImageMapDescPtr imptr;
	SLong			cx,cy,cz;
	SWord			ystep;
	SWord			pitch = object_obj3d->AngC;
	SWord			windy, windy2;
	SWord			minx,miny, maxx,maxy;
	SWord			sin_ang, cos_ang;
	FPMATRIX		tmat;
	FPMATRIX_PTR	tmatp = &tmat;
	IFShare			wx,wy,wz;
	SWord			radius = ptr->radius;
	DoPointStruc	dp0, dp1, dp2, dp3;

	ANGLES			extraRoll;

	if (Manual_Pilot.ControlledAC2->classtype->visible==MIG15 || 
		Manual_Pilot.ControlledAC2->classtype->visible==CMIG15)
		extraRoll=ANGLES_0Deg;
	else
	{
		extraRoll=ANGLES_180Deg;
		pitch=-pitch;
	}

	imptr = Image_Map.GetImageMapPtr((ImageMapNumber )ptr->imagemap);

 	windy = ptr->height / 4;
 	windy2 = ptr->height>>1;

	ystep = (-pitch * windy) / ANGLES_20Deg;								//RJS 21Apr98
	ystep += windy;

	if (ystep < 0)
		ystep = 0;

	if (ystep > windy2)
		ystep = windy2;

	miny = ptr->miny + ystep;
	minx = ptr->minx;
	maxx = minx + ptr->width;
	maxy = miny + windy2;

	cx = ptr->xpos;
	cy = -ptr->ypos;
	cz = ptr->zpos;
//DeadCode PD 05Oct98 	cx = ptr->xpos << shapescale;
//DeadCode PD 05Oct98 	cy = -ptr->ypos << shapescale;
//DeadCode PD 05Oct98 	cz = ptr->zpos << shapescale;

	//radius <<= shapescale;
//DeadCode PD 05Oct98 	radius <<= shapescale;
//Old_Code PD 12Oct98 	_matrix.generate2(ANGLES_0Deg,ANGLES_0Deg,(ANGLES)-object_obj3d->AngR,tmatp);//RJS 19Jun98
	_matrix.Generate2(ANGLES_0Deg,ANGLES_0Deg,(ANGLES)extraRoll-object_obj3d->AngR,1,tmatp);//RJS 19Jun98

	wx.i = -radius;
	wy.i = radius;
	wz.i = 0;
	_matrix.transformNC(tmatp,wx,wy,wz);

	dp0.bodyx.i = cx + wx.f;
	dp0.bodyy.i = cy + wy.f;
	dp0.bodyz.i = cz;
	_matrix.transformNC(fpobject_matrix,&dp0);
	dp0.bodyx.f += object_obj3d->Body.X.f;
	dp0.bodyy.f += object_obj3d->Body.Y.f;
	dp0.bodyz.f += object_obj3d->Body.Z.f;
	_matrix.SetClipFlags(dp0);

	wx.i = radius;
	wy.i = radius;
	wz.i = 0;
	_matrix.transformNC(tmatp,wx,wy,wz);

	dp1.bodyx.i = cx + wx.f;
	dp1.bodyy.i = cy + wy.f;
	dp1.bodyz.i = cz;
	_matrix.transformNC(fpobject_matrix,&dp1);
	dp1.bodyx.f += object_obj3d->Body.X.f;
	dp1.bodyy.f += object_obj3d->Body.Y.f;
	dp1.bodyz.f += object_obj3d->Body.Z.f;
	_matrix.SetClipFlags(dp1);

	wx.i = radius;
	wy.i = -radius;
	wz.i = 0;
	_matrix.transformNC(tmatp,wx,wy,wz);

	dp2.bodyx.i = cx + wx.f;
	dp2.bodyy.i = cy + wy.f;
	dp2.bodyz.i = cz;
	_matrix.transformNC(fpobject_matrix,&dp2);
	dp2.bodyx.f += object_obj3d->Body.X.f;
	dp2.bodyy.f += object_obj3d->Body.Y.f;
	dp2.bodyz.f += object_obj3d->Body.Z.f;
	_matrix.SetClipFlags(dp2);

	wx.i = -radius;
	wy.i = -radius;
	wz.i = 0;
	_matrix.transformNC(tmatp,wx,wy,wz);

	dp3.bodyx.i = cx + wx.f;
	dp3.bodyy.i = cy + wy.f;
	dp3.bodyz.i = cz;
	_matrix.transformNC(fpobject_matrix,&dp3);
	dp3.bodyx.f += object_obj3d->Body.X.f;
	dp3.bodyy.f += object_obj3d->Body.Y.f;
	dp3.bodyz.f += object_obj3d->Body.Z.f;
	_matrix.SetClipFlags(dp3);									//RJS 19Jun98

	oredFlags=CF3D_NULL;
	andedFlags=CF3D_ALL;

	oredFlags|=dp0.clipFlags;
	oredFlags|=dp1.clipFlags;
	oredFlags|=dp2.clipFlags;
	oredFlags|=dp3.clipFlags;

	andedFlags&=dp0.clipFlags;
	andedFlags&=dp1.clipFlags;
	andedFlags&=dp2.clipFlags;
	andedFlags&=dp3.clipFlags;
	if (andedFlags == 0)
	{
		dp0.intensity=dp0.specFlip=dp0.specular=-1;
		dp1.intensity=dp1.specFlip=dp1.specular=-1;
		dp2.intensity=dp2.specFlip=dp2.specular=-1;
		dp3.intensity=dp3.specFlip=dp3.specular=-1;
//		if (!doingHW3D)												//PD 19Jun98
//		{															//PD 19Jun98
//			_matrix.body2screen(dp0);			
//			_matrix.body2screen(dp1);			
//			_matrix.body2screen(dp2);			
//			_matrix.body2screen(dp3);
//		}

		POLYGON.createpoly((ImageMapNumber )ptr->imagemap);
		POLYGON.createvert(dp0,minx,miny);										//RJS 21Apr98
		POLYGON.createvert(dp1,maxx,miny);										//RJS 21Apr98
		POLYGON.createvert(dp2,maxx,maxy);										//RJS 21Apr98
		POLYGON.createvert(dp3,minx,maxy);										//RJS 21Apr98
		POLYGON.drawpoly();
	}

	instr_ptr += sizeof(DOATTITUDE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dodot
//LastModified:	PD 07May96
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
 void shape::dodot(UByte *& instr_ptr)
{
	DODOT_PTR	ddptr = (DODOT_PTR )instr_ptr;
	SLong	glintrange = (SLong)object_obj3d->Body.Z.f;			//DAW 01Sep98
	SetLineAndDotShade(object_obj3d->ItemPtr,View_Point);
//	if (glintrange < RANGE_AIRCRAFT)							//DAW 01Sep98
	{
 		UWord	vertex;
 
 		vertex = (UWord )ddptr->vertex;								//RJS 10Mar97
 
 		Colour	clr = (Colour )(ddptr->colour);
 
 		if (object_obj3d->Shape==BULLET)							//PD 26Jul96
 			clr = YELLOW;											//PD 26Jul96
 
		if (doingHW3D)
		{
			POINTTYPE	ptPointType;
			struct		vertex	pVertex;
			ptPointType.lpVertex= &pVertex;

			Float maxDotZ=200000;	//Float(Land_Scape.view_range)*.5;
			pVertex.bx.f		= newco[vertex].bodyx.f;
			pVertex.by.f		= newco[vertex].bodyy.f;
			pVertex.bz.f		= newco[vertex].bodyz.f;
			pVertex.intensity	= dotNLineFadeValue;
			if (pVertex.bz.f>maxDotZ)
			{
			 	Float xyDiv=maxDotZ/pVertex.bz.f;
				pVertex.bz.f=maxDotZ;
				pVertex.bx.f*=xyDiv;
				pVertex.by.f*=xyDiv;
			}
			pVertex.clipFlags	= newco[vertex].clipFlags&~CF3D_PASTFARZ;
			ptPointType.ptType	= PointType::PT_PlainColour;
			ptPointType.colour	= clr;
			current_screen->DoHardPoint(&ptPointType);
		}
//		else
//		{
//	 		SWord 	intense;
 //
 //			SLong	dist = object_dist;									//PD 19Dec96
 //		
 //			intense = Three_Dee.IntensFromRange(dist,fade_start,fade_end);//PD 24Jul96
 //
//	 		intense = intense>>4;
 //			
//			if (intense)												//RJS 27Jun97
//			{
//	 			SLong	temp1,temp2;
 //
 //				temp1 = (SLong )clr;
//		 		temp1 &= 0x0FF;
 //
//	 			temp2 = intense;
 //
//	 			temp1 = ASM_GetFadeColour(temp1,temp2);
 //			
//		 		clr = (Colour )temp1;
//			}

//	 		Float	temp;												//RJS 26Feb97
 
 //			SLong	abstemp;
 //
//			temp = newco[vertex].screenx.f;								//RJS 22Aug97
 //
 //			abstemp = (temp<0)?-temp:temp;

 //			if (abstemp<=0x07FFF)
//	 		{
 //				SWord	xcoord = (SWord )temp;
 //
//				temp = newco[vertex].screeny.f;
 //
 //				abstemp = (temp<0)?-temp:temp;
 //
//	 			if (abstemp<=0x07FFF)
 //				{
 //					SWord ycoord = (SWord )temp;
 //
//					current_screen->PlotLogicalPixel(xcoord,ycoord,clr);
//	 			}
 //			}
//		}
	}

//DeadCode DAW 01Sep98 	else
//DeadCode DAW 01Sep98 	{
	// Do glint....
	if (	(Three_Dee.lightson == FALSE)						//RJS 10May99
		&& 	ddptr->imagemap										//RJS 10May99
		&&	!Land_Scape.blackingout						)		//RJS 10May99
	{
		MinAnimData*	mad = (MinAnimData*) GlobalAdptr;
		if (mad->itemstate != DEAD)							//RJS 10May99
		{
//			SLong		roll = object_obj3d->AngR;
			SLong		randno = 0;										//RJS 16Jun99
			SLong		specular;

			if (View_Point->isLightShaded)								//RJS 06May98
			{
				SLong	specflip;

				// Vector pointing up
				Float fintensity=TransLightVector.nj.f;

				double fspecular=TransViewVector.nj.f;
				calcSpecular(fspecular,fintensity,specular,specflip);

				specular *= 4;			// 3 frames						//RJS 16Jun99
				specular /= specMax;									//RJS 16Jun99
																		//RJS 16Jun99
				specflip *= 4;			// 3 frames						//RJS 16Jun99
				specflip /= specMax;									//RJS 16Jun99
																		//RJS 16Jun99
				if (specular > specflip)								//RJS 16Jun99
					randno = specular;									//RJS 16Jun99
				else													//RJS 16Jun99
					randno = specflip;									//RJS 16Jun99
			}

			if (randno)				//RJS 22Mar99
			{
				randno--;

				DoPointStruc	dp1,dp2,dp3,dp4;
				SWord			width = ddptr->ix;
				SWord			height = ddptr->iy;
				SWord			nofx,stepx,stepy,minx,miny,maxx,maxy;
				ImageMapDescPtr	imptr = Image_Map.GetImageMapPtr((ImageMapNumber )ddptr->imagemap);
				Float			gscale;
				COORDS3D	*wptr = &object_obj3d->ItemPtr->World;
				SLong			fno = SHAPE.Noise(wptr->X,wptr->Y,wptr->Z)/128;

//				randno = (randno * 3)/16384;
//				fno /= 120;
//
				randno -= fno;
//				if (randno > 3)	randno = 2;						//DAW 01Sep98
//
				if (randno > -1)
				{
					SLong	range = RANGE_AIRCRAFT_FLASH - 100000;
					gscale = 100000 / object_obj3d->Body.Z.f;
//					gscale = 5000.0 / object_obj3d->Body.Z.f;

					dp1.bodyx.f = object_obj3d->Body.X.f * gscale;
					dp1.bodyy.f = object_obj3d->Body.Y.f * gscale;
					dp1.bodyz.f = 100000.0;		//5000.0;

					dp4 = dp3 = dp2 = dp1;

//					if (SHAPE.ClipSphere(dp1,dp2,dp3,dp4,120)==FALSE)//DAW 01Sep98
					if (SHAPE.ClipSphere(dp1,dp2,dp3,dp4,750)==FALSE)//rjs 16Jun99
					{
						minx = miny = 0;
						nofx = imptr->w / width;						
						if (nofx)
						{
	 						stepy = randno / nofx;			
							stepx = randno - (stepy*nofx);	
												
							minx += stepx * width;	
							miny += stepy * height;	
							if (miny >= imptr->h)
								minx = miny = 0;
						}

						maxx = minx + width;
						maxy = miny + height;

						POLYGON.createpoly((ImageMapNumber )ddptr->imagemap);				
						POLYGON.createvert(dp1,minx,miny);
						POLYGON.createvert(dp2,maxx,miny);
						POLYGON.createvert(dp3,maxx,maxy);
						POLYGON.createvert(dp4,minx,maxy);
						POLYGON.drawpoly();
					}
				}
			}
		}
	}
	instr_ptr += sizeof(DODOT);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		doscalesize
//Author		Robert Slater
//Date			Tue 3 Mar 1998
//
//Description	Scales the shape size by the anim counter
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::doscalesize(UByte *& instr_ptr)
{
	DOSCALESIZE_PTR	ptr = (DOSCALESIZE_PTR) instr_ptr;
//DeadCode RJS 21Apr99 	UByteP	adptr = (UByteP) object_obj3d->AnimPtr;
	SLong	frameno = GlobalAdptr[ptr->animoffsrc];				//RJS 16Apr99
	UByte	animscale = ptr->animscale;

	frameno *= 255;
	if (animscale)
		frameno /= animscale;

	GlobalAdptr[ptr->animoffdest] = frameno;

	instr_ptr += sizeof(DOSCALESIZE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		dogunsight
//Author		Robert Slater
//Date			Wed 4 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::dogunsight(UByte *& instr_ptr)
{
	DOGUNSIGHT_PTR	ptr = (DOGUNSIGHT_PTR) instr_ptr;
//DeadCode RJS 21Apr99 	UByteP	adptr = (UByteP) object_obj3d->AnimPtr;
	int		count;
	int		vertno;
	int		count2;
	DoPointStruc	dp1,dp2,dp3,dp4,dpc;
	int		angstep = 65536 / 6;
	int		radius = 20;
	int		radius2 = 30;
	int		radius3 = 25;
	UWord	theangle = angstep;
	SWord	sin_ang, cos_ang;
	SLong	px, py, pz;
	DoPointStruc *dpptr;
	DoPointStruc *dpptr2;
	Float	minx, maxx;
	Float	miny, maxy;
	Float	gapx, gapy;
	int		left, right, up, down;
	UByteP	plist_ptr;
	SWord	angle1, angle2;
	SWord	adj, opp;
	Bool	doclip;
	UByteP	psave_ptr;
	UWord	realhdg, realpitch;
	SLong	px2,py2,pz2,pzclip;
	FPMATRIX	omat,vomat;
	FPMATRIX_PTR	viewptr = Three_Dee.fpviewer_matrix;
	FPMATRIX_PTR	matptr = &omat;
	FPMATRIX_PTR	vmatptr = &vomat;
	Float			zscale, testPointX,testPointY;
	Float			ddx, ddy, ddxscaled, ddfrac;
	Float			TopX,TopY,BotX,BotY;
	Float			CentreX,CentreY;
	SLong			bpx,bpy;
	SLong			gs_x,gs_y,gs_z;
	SWord			minix,miniy,maxix,maxiy;

	minix = miniy = 1;
	maxix = maxiy = 2;
	
//DeadCode RDH 29Nov98 	gs_x = SHAPE.GunSightPos.X;
//DeadCode RDH 29Nov98 	gs_y = SHAPE.GunSightPos.Y;
//DeadCode RDH 29Nov98 	gs_z = SHAPE.GunSightPos.Z;
//DeadCode RDH 29Nov98 
//DeadCode RDH 29Nov98 	if (	(SHAPE.ClosestGap != 1000000)
//DeadCode RDH 29Nov98 		&&	(SHAPE.ClosestGap2 != 1000000)	)
//DeadCode RDH 29Nov98 	{
//DeadCode RDH 29Nov98 		SLong	dx = SHAPE.GunSightPos2.X - SHAPE.GunSightPos.X;
//DeadCode RDH 29Nov98 		SLong	dy = SHAPE.GunSightPos2.Y - SHAPE.GunSightPos.Y;
//DeadCode RDH 29Nov98 		SLong	dz = SHAPE.GunSightPos2.Z - SHAPE.GunSightPos.Z;
//DeadCode RDH 29Nov98 		SLong	totgap = SHAPE.ClosestGap + SHAPE.ClosestGap2;
//DeadCode RDH 29Nov98 		SLong	frac_x,frac_y,frac_z;
//DeadCode RDH 29Nov98 
//DeadCode RDH 29Nov98 		if (totgap)
//DeadCode RDH 29Nov98 		{
//DeadCode RDH 29Nov98 			frac_x = (dx << 8)/totgap;
//DeadCode RDH 29Nov98 			frac_y = (dy << 8)/totgap;
//DeadCode RDH 29Nov98 			frac_z = (dz << 8)/totgap;
//DeadCode RDH 29Nov98 
//DeadCode RDH 29Nov98 			gs_x += (frac_x * SHAPE.ClosestGap)>>8;
//DeadCode RDH 29Nov98 			gs_y += (frac_y * SHAPE.ClosestGap)>>8;
//DeadCode RDH 29Nov98 			gs_z += (frac_z * SHAPE.ClosestGap)>>8;
//DeadCode RDH 29Nov98 		}
//DeadCode RDH 29Nov98 	}

//Calc gunsight pos.....
// default range = 500m

	SLong	time;		//time in csecs
	SWord	vx,vy,vz,vhori;
	SLong	sx,sy,sz;
	SLong	usexpos, useypos, usezpos;
	SLong	xpos, ypos, zpos;
	SLong	index, wpcnt;
//DeadCode DAW 25Jun99 	WeapAnimData*	weapon;
//DeadCode DAW 25Jun99 	UWord	mvel,mdelay,mburst;						//RDH 31Jul98
//DeadCode DAW 25Jun99 	rotitem	*tmpplane = new rotitem;
//DeadCode DAW 25Jun99 
//DeadCode DAW 25Jun99 	if (tmpplane)
//DeadCode DAW 25Jun99 	{
//DeadCode DAW 25Jun99 		usexpos = 0;
//DeadCode DAW 25Jun99 		useypos = 0;
//DeadCode DAW 25Jun99 		usezpos = 0;
//DeadCode DAW 25Jun99 		wpcnt = 0;
//DeadCode DAW 25Jun99 
//DeadCode DAW 25Jun99 		tmpplane->shape = Manual_Pilot.ControlledAC2->shape;
//DeadCode DAW 25Jun99 		tmpplane->Anim =  Manual_Pilot.ControlledAC2->Anim;
//DeadCode DAW 25Jun99 		tmpplane->World = SHAPE.GunSightPos;
//DeadCode DAW 25Jun99 
//DeadCode DAW 25Jun99 		index = 0;
//DeadCode DAW 25Jun99 		while (index < 3)
//DeadCode DAW 25Jun99 		{
//DeadCode DAW 25Jun99 			weapon = SHAPE.GetWeaponLauncher(tmpplane,index,xpos,ypos,zpos,mvel,mdelay,mburst,LT_BULLET);//RDH 31Jul98
//DeadCode DAW 25Jun99 			if (weapon)
//DeadCode DAW 25Jun99 			{
//DeadCode DAW 25Jun99 				usexpos += xpos;
//DeadCode DAW 25Jun99 				useypos += ypos;
//DeadCode DAW 25Jun99 				usezpos += zpos;
//DeadCode DAW 25Jun99 
//DeadCode DAW 25Jun99 				wpcnt++;
//DeadCode DAW 25Jun99  			}
//DeadCode DAW 25Jun99 			index++;
//DeadCode DAW 25Jun99  		}
//DeadCode DAW 25Jun99 
//DeadCode DAW 25Jun99 		if (wpcnt)
//DeadCode DAW 25Jun99 		{
//DeadCode DAW 25Jun99 			time = (SHAPE.RequiredRange*100) / mvel;
//DeadCode DAW 28Jun99 			time = (SHAPE.RequiredRange*100) / gunsightmvel;	//AMM 25Jun99

//DeadCode DAW 25Jun99 			gs_x = usexpos/wpcnt;
//DeadCode DAW 25Jun99 			gs_y = useypos/wpcnt;
//DeadCode DAW 25Jun99 			gs_z = usezpos/wpcnt;
			gs_x = gunsightX;									//AMM 25Jun99
			gs_y = gunsightY;									//AMM 25Jun99
			gs_z = gunsightZ;									//AMM 25Jun99

//DeadCode CSB 03/06/99				Manual_Pilot.ControlledAC2->fly.pModel->CalcLauncherVel(mvel,vx,vy,vz);//RJS 27Nov98
//DeadCode CSB 03/06/99	
//DeadCode CSB 03/06/99				sx = (vx * time)/100;
//DeadCode CSB 03/06/99				sz = (vz * time)/100;
//DeadCode CSB 03/06/99				sy = (vy * time)/100;
//DeadCode CSB 03/06/99				sy -= (time*time*5)/10000;
//DeadCode DAW 25Jun99 			Manual_Pilot.ControlledAC2->fly.pModel->CalcGunsightPos(SHAPE.RequiredRange, mvel, sx, sy, sz);
			Manual_Pilot.ControlledAC2->fly.pModel->CalcGunsightPos(SHAPE.RequiredRange, gunsightmvel, sx, sy, sz);


			gs_x += sx;
			gs_y += sy;
			gs_z += sz;

	//....Calced gunsight pos

//DeadCode RDH 29Nov98 
//DeadCode RDH 29Nov98 			realpitch = View_Point->pitch;
//DeadCode RDH 29Nov98 			realhdg = View_Point->hdg;
//DeadCode RDH 29Nov98 
//DeadCode RDH 29Nov98 			SHAPE.ClosestGap = 1000000;
//DeadCode RDH 29Nov98 			SHAPE.ClosestGap2 = 1000000;

			instr_ptr += sizeof(DOGUNSIGHT);

//DeadCode RDH 29Nov98 	if (	((realpitch > ANGLES_315Deg) || (realpitch < ANGLES_45Deg))
//DeadCode RDH 29Nov98 		&&	((realhdg > ANGLES_315Deg) || (realhdg < ANGLES_45Deg))		)
//DeadCode RDH 29Nov98 	{
			_matrix.inverseMobileMatrix((Angles)SHAPE.GunSightHdg,
										(Angles)SHAPE.GunSightPitch,
										(Angles)SHAPE.GunSightRoll,
										omat	);

			px = gs_x - SHAPE.GunSightPos.X;							//RDH 29Nov98
			py = gs_y - SHAPE.GunSightPos.Y;							//RDH 29Nov98
			pz = gs_z - SHAPE.GunSightPos.Z;							//RDH 29Nov98

			px2 = ptr->posx;
			py2 = ptr->posy;
			pz2 = ptr->posz;									//RJS 08May98
			pzclip = (ptr->posz-60);								//RJS 08May98

 			dp1.bodyx.i = px;
			dp1.bodyy.i = py;
			dp1.bodyz.i = pz;

			_matrix.transformNC(matptr,&dp1);

			px = (SLong) dp1.bodyx.f;
			py = (SLong) dp1.bodyy.f;
			pz = (SLong) dp1.bodyz.f;

			px = (px*pz2)/pz;
			py = (py*pz2)/pz;
			pz = pz2;

			radius = (SHAPE.WingSpan*pz2*256)/SHAPE.RequiredRange;		//RJS 10May99
			radius >>= 1;

			//Scale to f86 distance from eye to get small diamonds...
			radius2 = radius + ((2560*ptr->posz)/930);		//10 * 256
			radius3 = ((1280*ptr->posz)/930);					//5 * 256

			dpc.bodyx.i = px2;
			dpc.bodyy.i = py2;
			dpc.bodyz.i = pz2;
			_matrix.transformNC(fpobject_matrix,&dpc);
			_matrix.body2screen(dpc);

			plist_ptr = psave_ptr = instr_ptr;
			instr_ptr+= ptr->nopoints*sizeof(UByte);

			if (pz > pzclip)
			{
				SLong	xoff, yoff;

//DeadCode RJS 11Jun99 				xoff = (256*ptr->posz)/930;
//DeadCode RJS 11Jun99 
//DeadCode RJS 11Jun99 				dp1.bodyx.i = (px<<8)-xoff;
//DeadCode RJS 11Jun99 				dp1.bodyy.i = (py<<8);
//DeadCode RJS 11Jun99 				dp1.bodyz.i = (pz<<8);
//DeadCode RJS 11Jun99 				_matrix.transformNC(fpobject_matrix,&dp1);
//DeadCode RJS 11Jun99 				dp1.bodyx.f *=0.00390625;
//DeadCode RJS 11Jun99 				dp1.bodyy.f *=0.00390625;
//DeadCode RJS 11Jun99 				dp1.bodyz.f *=0.00390625;
//DeadCode RJS 11Jun99 				dp1.bodyx.f +=object_obj3d->Body.X.f;
//DeadCode RJS 11Jun99 				dp1.bodyy.f +=object_obj3d->Body.Y.f;
//DeadCode RJS 11Jun99 				dp1.bodyz.f +=object_obj3d->Body.Z.f;
//DeadCode RJS 11Jun99 
//DeadCode RJS 11Jun99 				dp2.bodyx.i = (px<<8);
//DeadCode RJS 11Jun99 				dp2.bodyy.i = (py<<8)-xoff;
//DeadCode RJS 11Jun99 				dp2.bodyz.i = (pz<<8);
//DeadCode RJS 11Jun99 				_matrix.transformNC(fpobject_matrix,&dp2);
//DeadCode RJS 11Jun99 				dp2.bodyx.f *=0.00390625;
//DeadCode RJS 11Jun99 				dp2.bodyy.f *=0.00390625;
//DeadCode RJS 11Jun99 				dp2.bodyz.f *=0.00390625;
//DeadCode RJS 11Jun99 				dp2.bodyx.f +=object_obj3d->Body.X.f;
//DeadCode RJS 11Jun99 				dp2.bodyy.f +=object_obj3d->Body.Y.f;
//DeadCode RJS 11Jun99 				dp2.bodyz.f +=object_obj3d->Body.Z.f;
//DeadCode RJS 11Jun99 
//DeadCode RJS 11Jun99 				dp3.bodyx.i = (px<<8)+xoff;
//DeadCode RJS 11Jun99 				dp3.bodyy.i = (py<<8);
//DeadCode RJS 11Jun99 				dp3.bodyz.i = (pz<<8);
//DeadCode RJS 11Jun99 				_matrix.transformNC(fpobject_matrix,&dp3);
//DeadCode RJS 11Jun99 				dp3.bodyx.f *=0.00390625;
//DeadCode RJS 11Jun99 				dp3.bodyy.f *=0.00390625;
//DeadCode RJS 11Jun99 				dp3.bodyz.f *=0.00390625;
//DeadCode RJS 11Jun99 				dp3.bodyx.f +=object_obj3d->Body.X.f;
//DeadCode RJS 11Jun99 				dp3.bodyy.f +=object_obj3d->Body.Y.f;
//DeadCode RJS 11Jun99 				dp3.bodyz.f +=object_obj3d->Body.Z.f;
//DeadCode RJS 11Jun99 
//DeadCode RJS 11Jun99 				dp4.bodyx.i = (px<<8);
//DeadCode RJS 11Jun99 				dp4.bodyy.i = (py<<8)+xoff;
//DeadCode RJS 11Jun99 				dp4.bodyz.i = (pz<<8);
//DeadCode RJS 11Jun99 				_matrix.transformNC(fpobject_matrix,&dp4);
//DeadCode RJS 11Jun99 				dp4.bodyx.f *=0.00390625;
//DeadCode RJS 11Jun99 				dp4.bodyy.f *=0.00390625;
//DeadCode RJS 11Jun99 				dp4.bodyz.f *=0.00390625;
//DeadCode RJS 11Jun99 				dp4.bodyx.f +=object_obj3d->Body.X.f;
//DeadCode RJS 11Jun99 				dp4.bodyy.f +=object_obj3d->Body.Y.f;
//DeadCode RJS 11Jun99 				dp4.bodyz.f +=object_obj3d->Body.Z.f;
//DeadCode RJS 11Jun99 
//DeadCode RJS 11Jun99 				andedFlags=CF3D_ALL;
//DeadCode RJS 11Jun99 
//DeadCode RJS 11Jun99 				// Clip and draw central dot....
//DeadCode RJS 11Jun99 				_matrix.SetClipFlags(dp1);
//DeadCode RJS 11Jun99 				_matrix.SetClipFlags(dp2);
//DeadCode RJS 11Jun99 				_matrix.SetClipFlags(dp3);
//DeadCode RJS 11Jun99 				_matrix.SetClipFlags(dp4);
//DeadCode RJS 11Jun99 
//DeadCode RJS 11Jun99 				andedFlags&=dp1.clipFlags;
//DeadCode RJS 11Jun99 				andedFlags&=dp2.clipFlags;
//DeadCode RJS 11Jun99 				andedFlags&=dp3.clipFlags;
//DeadCode RJS 11Jun99 				andedFlags&=dp4.clipFlags;
//DeadCode RJS 11Jun99 
//DeadCode RJS 11Jun99 				if (andedFlags == 0)
//DeadCode RJS 11Jun99 				{
//DeadCode RJS 11Jun99 					_matrix.body2screen(dp1);
//DeadCode RJS 11Jun99 					_matrix.body2screen(dp2);
//DeadCode RJS 11Jun99 					_matrix.body2screen(dp3);
//DeadCode RJS 11Jun99 					_matrix.body2screen(dp4);
//DeadCode RJS 11Jun99 
//DeadCode RJS 11Jun99 					if (!ptr->imap)								//RJS 24Mar99
//DeadCode RJS 11Jun99 					{
//DeadCode RJS 11Jun99  						POLYGON.createpoly(shape::colour);				
//DeadCode RJS 11Jun99  						POLYGON.createvert(dp4);
//DeadCode RJS 11Jun99  						POLYGON.createvert(dp3);
//DeadCode RJS 11Jun99  						POLYGON.createvert(dp2);
//DeadCode RJS 11Jun99 	 					POLYGON.createvert(dp1);
//DeadCode RJS 11Jun99 					}
//DeadCode RJS 11Jun99 					else
//DeadCode RJS 11Jun99 					{
//DeadCode RJS 11Jun99 						POLYGON.createpoly((ImageMapNumber)ptr->imap);//RJS 24Mar99
//DeadCode RJS 11Jun99 						POLYGON.createvert(dp4,minix,miniy);				//RJS 24Mar99
//DeadCode RJS 11Jun99 						POLYGON.createvert(dp3,minix,maxiy);				//RJS 24Mar99
//DeadCode RJS 11Jun99 						POLYGON.createvert(dp2,maxix,maxiy);				//RJS 24Mar99
//DeadCode RJS 11Jun99 						POLYGON.createvert(dp1,maxix,miniy);				//RJS 24Mar99
//DeadCode RJS 11Jun99 					}
//DeadCode RJS 11Jun99 
//DeadCode RJS 11Jun99 					POLYGON.drawpoly();
//DeadCode RJS 11Jun99 				}

				SLong	donecnt = 0;							//RJS 11Jun99

				CentreX = (Float)dpc.screenx.f;
				CentreY = (Float)-dpc.screeny.f;

				// Clip and draw diamonds...
				for (count2 = 0; count2 < 6; count2++)
				{
					Math_Lib.high_sin_cos((Angles) theangle,sin_ang,cos_ang);
					xoff = (radius * sin_ang) >> 15;
					yoff = (radius * cos_ang) >> 15;

					bpx = (px<<8) + xoff;
					bpy = (py<<8) + yoff;

					dp1.bodyx.i = bpx;
					dp1.bodyy.i = bpy;
					dp1.bodyz.i = (pz<<8);
					_matrix.transformNC(fpobject_matrix,&dp1);
					dp1.bodyx.f *=0.00390625;
					dp1.bodyy.f *=0.00390625;
					dp1.bodyz.f *=0.00390625;
					dp1.bodyx.f +=object_obj3d->Body.X.f;
					dp1.bodyy.f +=object_obj3d->Body.Y.f;
					dp1.bodyz.f +=object_obj3d->Body.Z.f;
					_matrix.SetClipFlags(dp1);
					_matrix.body2screen(dp1);

					xoff = (radius2 * sin_ang) >> 15;
					yoff = (radius2 * cos_ang) >> 15;

					dp3.bodyx.i = (px<<8) + xoff;
					dp3.bodyy.i = (py<<8) + yoff;
					dp3.bodyz.i = (pz<<8);
					_matrix.transformNC(fpobject_matrix,&dp3);
					dp3.bodyx.f *=0.00390625;
					dp3.bodyy.f *=0.00390625;
					dp3.bodyz.f *=0.00390625;
					dp3.bodyx.f +=object_obj3d->Body.X.f;
					dp3.bodyy.f +=object_obj3d->Body.Y.f;
					dp3.bodyz.f +=object_obj3d->Body.Z.f;
					_matrix.SetClipFlags(dp3);
					_matrix.body2screen(dp3);

					testPointX = (Float)dp3.screenx.f;
					testPointY = (Float)-dp3.screeny.f;

					// is it within box.....

					doclip = TRUE;
 					if (testPointX > CentreX)
	 				{
	 					// Test for right hand side clip...
	 					plist_ptr = psave_ptr;
						_matrix.body2screen(newco[*plist_ptr]);
	 					for (count=0; count < (ptr->nopoints-1); count++)
	 					{
	 						dpptr = &newco[*plist_ptr];
							plist_ptr++;
 							dpptr2 = &newco[*plist_ptr];
							_matrix.body2screen(*dpptr2);

							TopX = (Float)dpptr->screenx.f;
							BotX = (Float)dpptr2->screenx.f;
							TopY = (Float)-dpptr->screeny.f;
							BotY = (Float)-dpptr2->screeny.f;

							if (	(TopX > CentreX)
								||	(BotX > CentreX)	)
							{
								if (	(testPointY < TopY)
									&&	(testPointY > BotY)	)
								{
									ddy = TopY - BotY;
									ddxscaled = BotX;
									if (ddy != 0)
									{
										ddx = TopX - BotX;

										ddxscaled = (testPointY - BotY)*ddx;
										ddxscaled /= ddy;
										ddxscaled += BotX;
									}

									if (testPointX < ddxscaled)
										doclip = FALSE;
								}
							}
	 					}
	 				}
	 				else
	 				{
	 					// Test for left hand clip...
	 					plist_ptr = psave_ptr;
						_matrix.body2screen(newco[*plist_ptr]);
	 					for (count=0; count < (ptr->nopoints-1); count++)
	 					{
							dpptr = &newco[*plist_ptr];
							plist_ptr++;
							dpptr2 = &newco[*plist_ptr];
							_matrix.body2screen(*dpptr2);

							TopX = (Float)dpptr->screenx.f;
							BotX = (Float)dpptr2->screenx.f;
							TopY = (Float)-dpptr->screeny.f;
							BotY = (Float)-dpptr2->screeny.f;

							if (	(TopX < CentreX)
								||	(BotX < CentreX)	)
							{
								if (	(testPointY < BotY)
									&&	(testPointY > TopY)	)
								{
									ddy = BotY - TopY;
									ddxscaled = TopX;
									if (ddy != 0)
									{
										ddx = BotX - TopX;

										ddxscaled = (testPointY - TopY)*ddx;
										ddxscaled /= ddy;
										ddxscaled = TopX - ddxscaled;
									}

									if (testPointX > ddxscaled)
										doclip = FALSE;
								}
							}
	 					}
	 				}

					if (!doclip)
					{
						Math_Lib.high_sin_cos((Angles) (theangle-ANGLES_45Deg),sin_ang,cos_ang);
						xoff = (radius3 * sin_ang) >> 15;
						yoff = (radius3 * cos_ang) >> 15;

						dp2.bodyx.i = bpx + xoff;
						dp2.bodyy.i = bpy + yoff;
						dp2.bodyz.i = (pz<<8);
						_matrix.transformNC(fpobject_matrix,&dp2);
						dp2.bodyx.f *=0.00390625;
						dp2.bodyy.f *=0.00390625;
						dp2.bodyz.f *=0.00390625;
						dp2.bodyx.f +=object_obj3d->Body.X.f;
						dp2.bodyy.f +=object_obj3d->Body.Y.f;
						dp2.bodyz.f +=object_obj3d->Body.Z.f;
						_matrix.SetClipFlags(dp2);
						_matrix.body2screen(dp2);

						Math_Lib.high_sin_cos((Angles) (theangle+ANGLES_45Deg),sin_ang,cos_ang);
						xoff = (radius3 * sin_ang) >> 15;
						yoff = (radius3 * cos_ang) >> 15;

						dp4.bodyx.i = bpx + xoff;
						dp4.bodyy.i = bpy + yoff;
						dp4.bodyz.i = (pz<<8);
						_matrix.transformNC(fpobject_matrix,&dp4);
						dp4.bodyx.f *=0.00390625;
						dp4.bodyy.f *=0.00390625;
						dp4.bodyz.f *=0.00390625;
						dp4.bodyx.f +=object_obj3d->Body.X.f;
						dp4.bodyy.f +=object_obj3d->Body.Y.f;
						dp4.bodyz.f +=object_obj3d->Body.Z.f;
						_matrix.SetClipFlags(dp4);
						_matrix.body2screen(dp4);

						if (!ptr->imap)
						{
 							POLYGON.createpoly(shape::colour);				
 							POLYGON.createvert(dp1);
 							POLYGON.createvert(dp2);
 							POLYGON.createvert(dp3);
	 						POLYGON.createvert(dp4);
						}
						else
						{
							POLYGON.createpoly((ImageMapNumber)ptr->imap);				
							POLYGON.createvert(dp1,minix,miniy);
							POLYGON.createvert(dp2,minix,maxiy);
							POLYGON.createvert(dp3,maxix,maxiy);
							POLYGON.createvert(dp4,maxix,miniy);
						}
						POLYGON.drawpoly();

						donecnt++;
					}

					theangle += angstep;
				}

				//Centre dot...
				if (donecnt)
				{
					if (donecnt > 4)	//most likely we'll not need to clip!
					{
						xoff = (ptr->posz<<8)/930;

						dp1.bodyx.i = (px<<8)-xoff;
						dp1.bodyy.i = (py<<8);
						dp1.bodyz.i = (pz<<8);
						_matrix.transformNC(fpobject_matrix,&dp1);
						dp1.bodyx.f *=0.00390625;
						dp1.bodyy.f *=0.00390625;
						dp1.bodyz.f *=0.00390625;
						dp1.bodyx.f +=object_obj3d->Body.X.f;
						dp1.bodyy.f +=object_obj3d->Body.Y.f;
						dp1.bodyz.f +=object_obj3d->Body.Z.f;

						dp2.bodyx.i = (px<<8);
						dp2.bodyy.i = (py<<8)-xoff;
						dp2.bodyz.i = (pz<<8);
						_matrix.transformNC(fpobject_matrix,&dp2);
						dp2.bodyx.f *=0.00390625;
						dp2.bodyy.f *=0.00390625;
						dp2.bodyz.f *=0.00390625;
						dp2.bodyx.f +=object_obj3d->Body.X.f;
						dp2.bodyy.f +=object_obj3d->Body.Y.f;
						dp2.bodyz.f +=object_obj3d->Body.Z.f;

						dp3.bodyx.i = (px<<8)+xoff;
						dp3.bodyy.i = (py<<8);
						dp3.bodyz.i = (pz<<8);
						_matrix.transformNC(fpobject_matrix,&dp3);
						dp3.bodyx.f *=0.00390625;
						dp3.bodyy.f *=0.00390625;
						dp3.bodyz.f *=0.00390625;
						dp3.bodyx.f +=object_obj3d->Body.X.f;
						dp3.bodyy.f +=object_obj3d->Body.Y.f;
						dp3.bodyz.f +=object_obj3d->Body.Z.f;

						dp4.bodyx.i = (px<<8);
						dp4.bodyy.i = (py<<8)+xoff;
						dp4.bodyz.i = (pz<<8);
						_matrix.transformNC(fpobject_matrix,&dp4);
						dp4.bodyx.f *=0.00390625;
						dp4.bodyy.f *=0.00390625;
						dp4.bodyz.f *=0.00390625;
						dp4.bodyx.f +=object_obj3d->Body.X.f;
						dp4.bodyy.f +=object_obj3d->Body.Y.f;
						dp4.bodyz.f +=object_obj3d->Body.Z.f;

						andedFlags=CF3D_ALL;

						// Clip and draw central dot....
						_matrix.SetClipFlags(dp1);
						_matrix.SetClipFlags(dp2);
						_matrix.SetClipFlags(dp3);
						_matrix.SetClipFlags(dp4);

						andedFlags&=dp1.clipFlags;
						andedFlags&=dp2.clipFlags;
						andedFlags&=dp3.clipFlags;
						andedFlags&=dp4.clipFlags;

						if (andedFlags == 0)
						{
							_matrix.body2screen(dp1);
							_matrix.body2screen(dp2);
							_matrix.body2screen(dp3);
							_matrix.body2screen(dp4);

							if (!ptr->imap)								//RJS 24Mar99
							{
 								POLYGON.createpoly(shape::colour);				
 								POLYGON.createvert(dp4);
 								POLYGON.createvert(dp3);
 								POLYGON.createvert(dp2);
	 							POLYGON.createvert(dp1);
							}
							else
							{
								POLYGON.createpoly((ImageMapNumber)ptr->imap);//RJS 24Mar99
								POLYGON.createvert(dp4,minix,miniy);				//RJS 24Mar99
								POLYGON.createvert(dp3,minix,maxiy);				//RJS 24Mar99
								POLYGON.createvert(dp2,maxix,maxiy);				//RJS 24Mar99
								POLYGON.createvert(dp1,maxix,miniy);				//RJS 24Mar99
							}

							POLYGON.drawpoly();
						}
					}
				}
			}
//DeadCode DAW 25Jun99 		}
//DeadCode DAW 25Jun99 		else
//DeadCode DAW 25Jun99 		{
//DeadCode DAW 25Jun99 			instr_ptr += sizeof(DOGUNSIGHT);					//RDH 29Nov98
//DeadCode DAW 25Jun99 			instr_ptr += ptr->nopoints * sizeof(UByte);			//RDH 29Nov98
//DeadCode DAW 25Jun99 		}														//RDH 29Nov98
																//RDH 29Nov98
//DeadCode DAW 25Jun99 		tmpplane->Anim = NULL;									//RJS 29Mov98
//DeadCode DAW 25Jun99 		delete tmpplane;										//RDH 29Nov98
//DeadCode DAW 25Jun99 	}
//DeadCode DAW 25Jun99 	else														//RDH 29Nov98
//DeadCode DAW 25Jun99 	{															//RDH 29Nov98
//DeadCode DAW 25Jun99 		instr_ptr += sizeof(DOGUNSIGHT);						//RDH 29Nov98
//DeadCode DAW 25Jun99 		instr_ptr += ptr->nopoints * sizeof(UByte);				//RDH 29Nov98
//DeadCode DAW 25Jun99 	}															//RDH 29Nov98
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		dowheelspray
//Author		Robert Slater
//Date			Mon 16 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void shape::dowheelspray(UByte *& instr_ptr)
{
	DOWHEELSPRAY_PTR ptr = (DOWHEELSPRAY_PTR) instr_ptr;
//DeadCode RJS 21Apr99 	UByteP		adptr = (UByteP) object_obj3d->AnimPtr;
	UByte		suspension = GlobalAdptr[ptr->animflag];

	if (suspension)
	{
		mobileitem*	mobptr = (mobileitem*)object_obj3d->ItemPtr;
		SLong		vel = mobptr->velhori;
		SLong		totdist;
		SLong		diststep ;
		SLong		angfrac;
		SLong		thedist = 0;
		SLong		index;
		SWord		theangle;
		SWord		sin_ang, cos_ang;
		SLong		ystep;
		IFShare		wx,wy,wz;
		SLong		wxx,wyy,wzz, wystep;
		DODOT		dotinst;
		UByteP		dinstptr;
		SLong		outback;
		DoPointStruc	dp1,dp2,dp3,dp4;
		totdist = vel >> 3;
//DeadCode DAW 25Jan99 
//DeadCode DAW 25Jan99 		char	shite[32];
//DeadCode DAW 25Jan99 		sprintf(shite,"Dist: %d  ",totdist);
//DeadCode DAW 25Jan99 		Mono_Text.PrintAt(50,10,(UByteP)shite);

		wxx = ptr->xcoord;
		wyy = ptr->ycoord;
		wzz = ptr->zcoord;
//DeadCode PD 05Oct98 		wxx = ptr->xcoord << shapescale;
//DeadCode PD 05Oct98 		wyy = ptr->ycoord << shapescale;
//DeadCode PD 05Oct98 		wzz = ptr->zcoord << shapescale;

		dotinst.vertex = 0;
		dotinst.colour = 31;
		dotinst.imagemap = 0;									//RJS 04Jun98

		outback = wzz<<12;

		if (totdist)
		{
			diststep = totdist<<7;		// <<12 / 32
			angfrac = ANGLES_180Deg >> 5;
			theangle = 0;

			for (index = 0; index < 32; index++)
			{
				Math_Lib.high_sin_cos((Angles) theangle,sin_ang,cos_ang);

				wystep = (totdist * sin_ang)>>16;

				wzz = outback>>12;

				for (ystep = 0; ystep < wystep; ystep++)
				{
					wy.i = wyy + ystep;
					wz.i = wzz;
					wx.i = wxx;

					if (SHAPE.Noise(wx.i,wy.i,wz.i) > 180)
					{
						dinstptr = (UByteP) &dotinst;

						andedFlags=CF3D_ALL;
						_matrix.transformNC(fpobject_matrix,wx,wy,wz);
						newco[0].bodyx.f = wx.f + object_obj3d->Body.X.f;
						newco[0].bodyx.f = wy.f + object_obj3d->Body.Y.f;
						newco[0].bodyx.f = wz.f + object_obj3d->Body.Z.f;
						_matrix.SetClipFlags(newco[0]);
						andedFlags&=newco[0].clipFlags;
						if (andedFlags == 0)
						{
							_matrix.body2screen(newco[0]);
							dodot(dinstptr);
						}
					}
				}

				outback -= diststep;
				theangle += angfrac;
			}
		}
	}

	instr_ptr += sizeof(DOWHEELSPRAY);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		doifbright
//Author		Robert Slater
//Date			Mon 23 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void shape::doifbright(UByte *& instr_ptr)
{
	DOIFBRIGHT_PTR	ptr = (DOIFBRIGHT_PTR) instr_ptr;
	int		count = ptr->nopoints;
	int		i;
	UByte	vert;
	UByteP	tmp_instr_ptr;
	SLong	totintensity = 0;

	instr_ptr += sizeof(DOIFBRIGHT);
	tmp_instr_ptr = instr_ptr;

	for (i=0; i < count; i++)
	{
		vert = *tmp_instr_ptr;

		totintensity += (256 - newco[vert].intensity);//RJS 17Feb99
		newco[vert].intensity = -1;//0;//-1;
		newco[vert].specular = -1;

		tmp_instr_ptr++;
	}

	SHAPE.oldAlphaSwitch = -1;
	totintensity = totintensity / count;
	if (totintensity > ptr->threshold)
	{
		SWord	depth = ((totintensity-ptr->threshold)*255)/(256-ptr->threshold);

		SHAPE.oldAlphaSwitch = current_screen->DoSetGlobalAlpha(depth);
		instr_ptr = tmp_instr_ptr;
	}
	else
		instr_ptr += ptr->offset;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	doquikpoly
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void shape::doquikpoly(UByte *& instr_ptr)
{
	DOQUIKPOLY_PTR poly_data=(DOQUIKPOLY_PTR)instr_ptr;
	int j=poly_data->edges;
	oredFlags=CF3D_NULL;
	andedFlags=CF3D_ALL;
	UWord* vertices=(UWord*)(instr_ptr+sizeof(DOQUIKPOLY));
	DoPointStruc** pDp=polyVertIndex;
	for (int i=0;i<j;i++){
		DoPointStruc& dp=newco[*vertices++];
		oredFlags|=dp.clipFlags;
		andedFlags&=dp.clipFlags;
		*pDp++=&dp;
	}
	//test clip flags before drawing the polygon...
	bool clipping=(oredFlags!=CF3D_NULL)?true:false;
	bool visible=(andedFlags==CF3D_NULL)?true:false;
	if (visible){
		clipping=current_screen->DoSetClipState(clipping);
		POLYGON.createpoly(shape::colour);
		pDp=polyVertIndex;
		for (i=0;i<j;i++){
			DoPointStruc& dp=**pDp++;
			POLYGON.createvert(dp);
		}
		POLYGON.drawpoly();
		current_screen->DoSetClipState(clipping);
	}
	instr_ptr+=sizeof(DOQUIKPOLY)+(UWord)poly_data->edges*sizeof(UWord);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		dofadeenvelope
//Author		Robert Slater
//Date			Fri 27 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void shape::dofadeenvelope(UByte *& instr_ptr)
{
	DOFADEENVELOPE_PTR	ptr = (DOFADEENVELOPE_PTR) instr_ptr;
//DeadCode RJS 21Apr99 	UByteP	adptr = (UByteP) object_obj3d->AnimPtr;
	SLong	btime = *((SLongP)&GlobalAdptr[ptr->birthtimeoffset]);
	SLong	lastval, thisval;
	SLong	totval = ptr->attackval;
	SLong	tottime;

	lastval = ptr->attackval;
	thisval = ptr->decayval;

	btime = View_Point->TimeOfDay() - btime;
	tottime = 0;
	if (btime > ptr->attacktime)
	{
		tottime += ptr->attacktime;
		if (btime > (tottime + ptr->decaytime))
		{
			tottime += ptr->decaytime;
			if (btime > (tottime + ptr->sustaintime))
			{
				tottime += ptr->sustaintime;
				if (btime > (tottime + ptr->releasetime))
					totval = ptr->releaseval;
				else
				{
					btime -= tottime;
					lastval = ptr->sustainval;
					thisval = ptr->releaseval;

					if (ptr->releasetime)
					{
						totval = ((thisval - lastval) * btime) / ptr->releasetime;
						totval += lastval;
					}
					else
						totval = ptr->sustainval;
				}
			}
			else
				totval = ptr->sustainval;
		}
		else
		{
			btime -= tottime;
			lastval = ptr->decayval;
			thisval = ptr->sustainval;

			if (ptr->decaytime)
			{
				totval = ((thisval - lastval) * btime) / ptr->decaytime;
				totval += lastval;
			}
			else
				totval = ptr->decayval;
		}		
	}
	else
	{
		if (ptr->attacktime)
		{
			totval = ((thisval - lastval) * btime) / ptr->attacktime;
			totval += lastval;
		}
	}

	GlobalAdptr[ptr->animfadeoffset] = totval;

	instr_ptr += sizeof(DOFADEENVELOPE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		dowhiteout
//Author		Robert Slater
//Date			Tue 31 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void shape::dowhiteout(UByte *& instr_ptr)						//RJS 31Mar98
{
	DOWHITEOUT_PTR	ptr = (DOWHITEOUT_PTR) instr_ptr;
	SLong	dist;
	SLong	x,y,z,maxdist;

	maxdist = ptr->fadedist + 1;
	x = (SLong)object_obj3d->Body.X.f;
	y = (SLong)object_obj3d->Body.Y.f;
	z = (SLong)object_obj3d->Body.Z.f;

	z = (z<0)?-z:z;
	x = (x<0)?-x:x;
	y = (y<0)?-y:y;
	
	// Must be in the fade box...
	if ((x < maxdist) && (y < maxdist) && (z < maxdist))
	{
		if(x<y)	{dist=y;y=x;x=dist;}
		if(x<z) {dist=z;z=x;x=dist;}
		if(y<z) {dist=y;y=z;z=dist;}

		//Sorted so that absdx > absdy > absdz
		//Try +/- 8% option
		dist = x;
		y >>= 2;
		dist += y;
		y >>= 2;
		dist += y;
		y >>= 1;
		dist += y;
		z >>= 2;
		dist += z;

		if (dist < ptr->fadedist)
		{
			SLong	fadeval = 32 - ((dist << 5)/ptr->fadedist);
			if (fadeval > SHAPE.DoWhiteFade)
				SHAPE.DoWhiteFade = fadeval;

			DrawnClouds = TRUE;
		}
	}

	instr_ptr += sizeof(DOWHITEOUT);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	donpoints
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
 void shape::donpoints(UByte *& instr_ptr)
{
	DONPOINTS_PTR npnt_ptr=(DONPOINTS_PTR )instr_ptr;
	COORDS_PTR ptr=(COORDS_PTR)(instr_ptr+sizeof(DONPOINTS));
	UWord vertex_count=npnt_ptr->vertex_count;
	instr_ptr+=vertex_count*sizeof(NNEXT)+sizeof(DONPOINTS);

	DoPointStruc* pdp=newco+npnt_ptr->start_vertex;

	const Float obx=object_obj3d->Body.X.f;
	const Float oby=object_obj3d->Body.Y.f;
	const Float obz=object_obj3d->Body.Z.f;

	ULong far_z_high,far_z_low;

	far_z_high=*((ULong*)&_matrix.fpMaximumZ+1);
	far_z_low=*(ULong*)&_matrix.fpMaximumZ;

//	if (doingHW3D)
//	{
		while (vertex_count--)
		{
			Float f[3];
			Float* m=(Float*)fpobject_matrix;
			f[0]=Float(ptr->xcoord);
			f[1]=Float(ptr->ycoord);
			f[2]=Float(ptr->zcoord);
			ptr++;

			pdp->intensity=pdp->specFlip=pdp->specular=-1;

			pdp->bodyz.f=f[0]*m[6]+f[1]*m[7]+f[2]*m[8]+obz;

			UWord clipFlag=CF3D_NULL;
			ULong abs_z_high=*((ULong*)&pdp->bodyz.f+1);
			ULong abs_z_low=*((ULong*)&pdp->bodyz.f);
			ULong sign_z_high=abs_z_high&CF3D_SIGNBITMASK;
			abs_z_high-=sign_z_high;

			if (sign_z_high!=0 || abs_z_high<CF3D_ONE_HIGH)
					clipFlag=CF3D_BEHINDNEARZ;
			else if (abs_z_high>far_z_high ||
					(abs_z_high==far_z_high && abs_z_low>far_z_low))
					clipFlag=CF3D_PASTFARZ;

			pdp->bodyx.f=f[0]*m[0]+f[1]*m[1]+f[2]*m[2]+obx;

			ULong abs_high=*((ULong*)&pdp->bodyx.f+1);
			ULong sign_high=abs_high&CF3D_SIGNBITMASK;
			abs_high-=sign_high;
			if (abs_high>abs_z_high ||
				(abs_high==abs_z_high && *(ULong*)&pdp->bodyx.f>abs_z_low))
					clipFlag|=(sign_high!=0)?CF3D_OFFLEFT:CF3D_OFFRIGHT;

			pdp->bodyy.f=f[0]*m[3]+f[1]*m[4]+f[2]*m[5]+oby;

			abs_high=*((ULong*)&pdp->bodyy.f+1);
			sign_high=abs_high&CF3D_SIGNBITMASK;
			abs_high-=sign_high;
			if (abs_high>abs_z_high ||
				(abs_high==abs_z_high && *(ULong*)&pdp->bodyy.f>abs_z_low))
					clipFlag|=(sign_high!=0)?CF3D_OFFBOTTOM:CF3D_OFFTOP;

			pdp->clipFlags=clipFlag;
			pdp++;
		}
//	}
//	else
//	{
//		while (vertex_count--)
//		{
//			pdp->bodyx.i=ptr->xcoord;
//			pdp->bodyy.i=ptr->ycoord;
//			pdp->bodyz.i=ptr->zcoord;
//			ptr++;
//			_matrix.transformNC(fpobject_matrix,pdp);
//			pdp->bodyx.f+=obx;
//			pdp->bodyy.f+=oby;
//			pdp->bodyz.f+=obz;
//			_matrix.SetClipFlags(*pdp);
//			if (!doingHW3D) _matrix.body2screen(*pdp);
//			pdp->intensity=-1;
//			pdp->specFlip=
//			pdp->specular=-1;
//			pdp++;
//		}
//	}

//Old_Code PD 07Oct98 	UWord	vertex,
//Old_Code PD 07Oct98 			counter;
//Old_Code PD 07Oct98 
//Old_Code PD 07Oct98 	DONPOINTS_PTR npnt_ptr = (DONPOINTS_PTR )instr_ptr;
//Old_Code PD 07Oct98 
//Old_Code PD 07Oct98 	COORDS_PTR	ptr = (COORDS_PTR)(instr_ptr+sizeof(DONPOINTS));
//Old_Code PD 07Oct98 
//Old_Code PD 07Oct98 	vertex = (UWord )npnt_ptr->start_vertex;					//RJS 10Mar97
//Old_Code PD 07Oct98 
//Old_Code PD 07Oct98 	for(counter=0;counter<npnt_ptr->vertex_count;counter++)
//Old_Code PD 07Oct98 	{
//Old_Code PD 07Oct98 		DoPointStruc& dp=newco[vertex];
//Old_Code PD 07Oct98 		dp.bodyx.i = ptr->xcoord;
//Old_Code PD 07Oct98 		dp.bodyy.i = ptr->ycoord;
//Old_Code PD 07Oct98 		dp.bodyz.i = ptr->zcoord;
//Old_Code PD 07Oct98 		_matrix.transformNC(fpobject_matrix,dp);
//Old_Code PD 07Oct98 		dp.bodyx.f += object_obj3d->Body.X.f;
//Old_Code PD 07Oct98 		dp.bodyy.f += object_obj3d->Body.Y.f;
//Old_Code PD 07Oct98 		dp.bodyz.f += object_obj3d->Body.Z.f;
//Old_Code PD 07Oct98 		_matrix.SetClipFlags(dp);
//Old_Code PD 07Oct98 		if (!doingHW3D) _matrix.body2screen(dp);				//PD 19Jun98
//Old_Code PD 07Oct98 		dp.intensity = -1;//0;//-1;										//RJS 20Mar98
//Old_Code PD 07Oct98 		dp.specFlip=
//Old_Code PD 07Oct98 		dp.specular=-1;											//PD 24Aug98
//Old_Code PD 07Oct98 		ptr++;
//Old_Code PD 07Oct98 		vertex++;
//Old_Code PD 07Oct98 	}
//Old_Code PD 07Oct98 
//Old_Code PD 07Oct98 	instr_ptr += npnt_ptr->vertex_count * sizeof(NNEXT) + sizeof(DONPOINTS);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	don4cmpnts
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
 void shape::don4cmpnts(UByte *& instr_ptr)
{
	DON4CMPNTS_PTR npnt_ptr;

	npnt_ptr = (DON4CMPNTS_PTR )instr_ptr;

	instr_ptr += npnt_ptr->vertex_count * sizeof(COORDS) + sizeof(DON4CMPNTS);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	do4cmpnt
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
 void shape::do4cmpnt(UByte *& instr_ptr)
{
	instr_ptr+=sizeof(DO4CMPNT);
}

//inline double ARCCOS(double x,double pi)
//{
//	double temp=(1.-x*x)/(x*x);
//	bool xneg=x<0?true:false;
//	_asm{
//		fld temp;
//		fsqrt;
//		fld1;
//		fpatan;
//		fstp temp;
//	}
//	if (xneg) temp=pi-temp;
//	return temp;
//}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		calcSpecular
//Author		Paul.   
//Date			Tue 25 Aug 1998
//
//Description	generates a value to be used for specular lighting
//				based on the dot product of the light and view vectors
//				with the vertex normal.
//
//Inputs		result of the two dot products
//
//Returns	
//
//------------------------------------------------------------------------------
//void calcSpecular(Float& specDot,Float& lightDot,SLong& specular,SLong& specFlip)
//{
	//const SLong specMax=95;	//127;
	//double pi;
//
//	_asm
//	{
//		fldpi;
//		fstp pi;
//	}
//
//	double spa=ARCCOS(specDot,pi);
//	double lia=ARCCOS(lightDot,pi);
//
//	if (spa<pi/2. && lia<pi/2.)
//	{
//		double delta=spa-lia; delta=delta<0?-delta:delta;
//
//		if (delta<pi/4.)
//		{
/*			delta=(pi/2.)+2.*delta;
			_asm{
				fld delta;
				fcos;
//				fmul st(0),st;
//				fmul st(0),st;
				fstp delta;
			}
			delta=double(specMax)*(delta+1.);
*/
//			delta=double(specMax)*(1.-delta/(pi/4.));
//			specFlip=SLong(delta);
//			if (specFlip<0)	specFlip=0;
//			else if (specFlip>specMax) specFlip=specMax;
//		}
//		else specFlip=0;
//	}
//	else specFlip=0;
//
//	spa+=pi; if (spa>pi) spa=2*pi-spa;
//	lia+=pi; if (lia>pi) lia=2*pi-lia;
//
//	if (spa<pi/2. && lia<pi/2.)
//	{
//		double delta=spa-lia; delta=delta<0?-delta:delta;
//
//		if (delta<pi/4.)
//		{
/*
			delta=(pi/2.)+2.*delta;
			_asm{
				fld delta;
				fcos;
//				fmul st(0),st;
//				fmul st(0),st;
				fstp delta;
			}
			delta=double(specMax)*(delta+1.);
*/
//			delta=double(specMax)*(1.-delta/(pi/4.));
//			specular=SLong(delta);
//			if (specular<0)	specular=0;
//			else if (specular>specMax) specular=specMax;
//		}
//		else specular=0;
//	}
//	else specular=0;
//}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dondupvec
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
 void shape::dondupvec(UByte *& instr_ptr)
{
	DONDUPVEC_PTR	ptr = (DONDUPVEC_PTR) instr_ptr;
	int				vertex = ptr->vertex;
	int				count;
	SLong			intensity;
	SLong			specular;
	SLong			specflip;

	if (View_Point->isLightShaded)								
	{
		IFShare& li=TransLightVector.ni;
		IFShare& lj=TransLightVector.nj;
		IFShare& lk=TransLightVector.nk;
		Float an=ptr->an;
		Float bn=ptr->bn;
		Float cn=ptr->cn;
		double mag=an*an+bn*bn+cn*cn;
		_asm {	fld mag;
				fsqrt;
				fstp mag;
		}
		an/=mag; bn/=mag; cn/=mag;
		Float fintensity=li.f*an+lj.f*bn+lk.f*cn;
		if (specularEnabled)
		{
		 	IFShare& vi=TransViewVector.ni;
		 	IFShare& vj=TransViewVector.nj;
		 	IFShare& vk=TransViewVector.nk;
			double fspecular=vi.f*an+vj.f*bn+vk.f*cn;
			calcSpecular(fspecular,fintensity,specular,specflip);
		}
		else specular=specflip=-1;

		fintensity*=Float(32385);

		intensity = fintensity;
		intensity+=32385;	//range is (-127 * 255) to (127 * 255) (ie. -32385 to 32385)
		if (ptr->ambientfiddle)
		{
			intensity /= 232;					
			intensity = 280 - intensity;		
			if (intensity > 256)				
				intensity = 256;				
		}
		else
		{
			intensity >>= 8;
			intensity = 256 - intensity;
		}

		if (intensity<0) intensity=0;

		for (count=0; count < ptr->count; count++ )
		{
			newco[vertex].intensity = intensity;
			newco[vertex].specular = specular;
			newco[vertex].specFlip = specflip;
			vertex++;
		}
	}

	instr_ptr+=sizeof(DONDUPVEC);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		dondeltapoints
//Author		Robert Slater
//Date			Tue 2 Jun 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void shape::dondeltapoints(UByte *&instr_ptr )
{
	DONDELTAPOINTS_PTR	ptr = (DONDELTAPOINTS_PTR) instr_ptr;
	NNEXT_PTR			npoint;
	int					count;
	DoPointStruc		*dpPtr = &newco[ptr->vertex];
	int					vno = ptr->count;
	UWord				mask = ptr->mask;
	UWord				nobitsset = ((mask&4)>>2)+((mask&2)>>1)+(mask&1);
	UWord				nextstep = nobitsset*sizeof(NDNEXT1);
	SLong				scaleup = ptr->scale;				

	npoint = (NNEXT_PTR) (instr_ptr + ptr->offset);
	for (count = 0; count < vno; count++)
	{
		dpPtr->bodyx.i = npoint->xcoord;
		dpPtr->bodyy.i = npoint->ycoord;
		dpPtr->bodyz.i = npoint->zcoord;
//DeadCode PD 05Oct98 		dpPtr->bodyx.i = npoint->xcoord << shapescale;
//DeadCode PD 05Oct98 		dpPtr->bodyy.i = npoint->ycoord << shapescale;
//DeadCode PD 05Oct98 		dpPtr->bodyz.i = npoint->zcoord << shapescale;
		npoint++;
		dpPtr++;
	}

	instr_ptr += sizeof(DONDELTAPOINTS);

	dpPtr = &newco[ptr->vertex];
	switch (mask)
	{
		case DMASK_X:
		{
			NDNEXT1_PTR	npointdelta = (NDNEXT1_PTR) instr_ptr;
			for (count=0; count < vno; count++)
			{
				dpPtr->bodyx.i += (npointdelta->delta*scaleup)>>8;//RJS 24May99
//DeadCode PD 05Oct98 				dpPtr->bodyx.i += (npointdelta->delta << shapescale);
				npointdelta++;
				dpPtr++;
			}
			break;
		}
		case DMASK_Y:
		{
			NDNEXT1_PTR	npointdelta = (NDNEXT1_PTR) instr_ptr;
			for (count=0; count < vno; count++)
			{
				dpPtr->bodyy.i -= (npointdelta->delta*scaleup)>>8;
//DeadCode PD 05Oct98 				dpPtr->bodyy.i -= (npointdelta->delta << shapescale);
				npointdelta++;
				dpPtr++;
			}
			break;
		}
		case DMASK_Z:
		{
			NDNEXT1_PTR	npointdelta = (NDNEXT1_PTR) instr_ptr;
			for (count=0; count < vno; count++)
			{
				dpPtr->bodyz.i += (npointdelta->delta*scaleup)>>8;
//DeadCode PD 05Oct98 				dpPtr->bodyz.i += (npointdelta->delta << shapescale);
				npointdelta++;
				dpPtr++;
			}
			break;
		}
		case DMASK_X_Y:
		{
			NDNEXT2_PTR	npointdelta = (NDNEXT2_PTR) instr_ptr;
			for (count=0; count < vno; count++)
			{
				dpPtr->bodyx.i += (npointdelta->delta[0]*scaleup)>>8;
				dpPtr->bodyy.i -= (npointdelta->delta[1]*scaleup)>>8;
//DeadCode PD 05Oct98 				dpPtr->bodyx.i += (npointdelta->delta[0] << shapescale);
//DeadCode PD 05Oct98 				dpPtr->bodyy.i -= (npointdelta->delta[1] << shapescale);
				npointdelta++;
				dpPtr++;
			}
			break;
		}
		case DMASK_X_Z:
		{
			NDNEXT2_PTR	npointdelta = (NDNEXT2_PTR) instr_ptr;
			for (count=0; count < vno; count++)
			{
				dpPtr->bodyx.i += (npointdelta->delta[0]*scaleup)>>8;
				dpPtr->bodyz.i += (npointdelta->delta[1]*scaleup)>>8;
//DeadCode PD 05Oct98 				dpPtr->bodyx.i += (npointdelta->delta[0] << shapescale);
//DeadCode PD 05Oct98 				dpPtr->bodyz.i += (npointdelta->delta[1] << shapescale);
				npointdelta++;
				dpPtr++;
			}
			break;
		}
		case DMASK_Y_Z:
		{
			NDNEXT2_PTR	npointdelta = (NDNEXT2_PTR) instr_ptr;
			for (count=0; count < vno; count++)
			{
				dpPtr->bodyy.i -= (npointdelta->delta[0]*scaleup)>>8;
				dpPtr->bodyz.i += (npointdelta->delta[1]*scaleup)>>8;
//DeadCode PD 05Oct98 				dpPtr->bodyy.i -= (npointdelta->delta[0] << shapescale);
//DeadCode PD 05Oct98 				dpPtr->bodyz.i += (npointdelta->delta[1] << shapescale);
				npointdelta++;
				dpPtr++;
			}
			break;
		}
		case DMASK_X_Y_Z:
		{
			NDNEXT3_PTR	npointdelta = (NDNEXT3_PTR) instr_ptr;
			for (count=0; count < vno; count++)
			{
				dpPtr->bodyx.i += (npointdelta->delta[0]*scaleup)>>8;
				dpPtr->bodyy.i -= (npointdelta->delta[1]*scaleup)>>8;
				dpPtr->bodyz.i += (npointdelta->delta[2]*scaleup)>>8;
//DeadCode PD 05Oct98 				dpPtr->bodyx.i += (npointdelta->delta[0] << shapescale);
//DeadCode PD 05Oct98 				dpPtr->bodyy.i -= (npointdelta->delta[1] << shapescale);
//DeadCode PD 05Oct98 				dpPtr->bodyz.i += (npointdelta->delta[2] << shapescale);
				npointdelta++;
				dpPtr++;
			}
			break;
		}
	}

	dpPtr = &newco[ptr->vertex];
	for (count =0; count < vno; count++)
	{
		DoPointStruc &dp = *dpPtr;
		_matrix.transformNC(fpobject_matrix,&dp);
		dp.bodyx.f += object_obj3d->Body.X.f;
		dp.bodyy.f += object_obj3d->Body.Y.f;
		dp.bodyz.f += object_obj3d->Body.Z.f;
		_matrix.SetClipFlags(dp);
		_matrix.body2screen(dp);
		dp.intensity = -1;
		dp.specFlip=
		dp.specular=-1;
		dpPtr++;
	}

	instr_ptr += (ptr->count * nextstep);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dodrawsun
//------------------------------------------------------------------------------
//Author		RJS.   
//Date		Wed 22 Jun 1998
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
 void shape::dodrawsun(UByte *&instr_ptr)		
{
	DODRAWSUN_PTR	ptr = (DODRAWSUN_PTR) instr_ptr;
//DeadCode RJS 21Apr99  	UByteP			adptr = (UByteP) object_obj3d->AnimPtr; 			
	SWord			minx, maxx;
	SWord			miny, maxy;
	SWord			width, height;
	SWord			oldGlobalAlpha = -1;
	SWord			depth;
	SWord			radius = ptr->radius;
	SWord			radadd;
	DOHEATHAZE		hhaze;
	UByteP			hhazeptr = (UByteP) &hhaze;
	
	minx = ptr->minx;							
	miny = ptr->miny;						 	
	width = ptr->width;							
	height = ptr->height;						

	if (SHAPE.AnimMap(GlobalAdptr,ptr->image,ptr->animoffset,ptr->animscale,minx,miny,width,height))
	{
		depth = GlobalAdptr[ptr->animoffset];
		if (depth != SMOKED_SOLID)
		{
			current_screen->SetTransparency(depth);
			oldGlobalAlpha = current_screen->DoSetGlobalAlpha(depth);
		}

		//Make sun grow....
		radadd = ((255 - depth) * 4000)>>8;
		radius += radadd;
	}

	maxx = minx + width - 1;							
	maxy = miny + height;								

	SHAPE.imapsphere(0,radius,(ImageMapNumber)ptr->image,minx,miny,maxx,maxy);

	if (oldGlobalAlpha != -1)
	{
		current_screen->DoSetGlobalAlpha(oldGlobalAlpha);
		current_screen->SetTransparency(SMOKED_OFF);
	}

	if (ptr->hazeimage)
	{
		newco[0].bodyz.f -= 10;
		hhaze.colour = 0;
		hhaze.animflag = ptr->hazeanim;
		hhaze.animscale = 1;
		hhaze.image = ptr->hazeimage;
		hhaze.minx = ptr->hazeminx;
		hhaze.miny = ptr->hazeminy;
		hhaze.width = ptr->hazewidth;
		hhaze.height = ptr->hazeheight;
		hhaze.vertex = 0;
		hhaze.radius = (radius*5)>>2;

		doheathaze(hhazeptr);
	}

	instr_ptr += sizeof(DODRAWSUN);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dosetcolour256
//LastModified:	PD 07Jun96
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	
//
//Description	This should be the only colour setting command in the 
//				shape instruction set
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
 void shape::dosetcolour256(UByte *& instr_ptr)
{
	Colour			base_colour;								//JIM 12Dec95

	DOSETCOLOUR256_PTR	temp = (DOSETCOLOUR256_PTR)instr_ptr;

//	SWord intense = Three_Dee.IntensFromRange(object_dist,fade_start,fade_end);//MGA 09May96
	//returns 0-256 so scale to 0-16.							//MGA 09May96

// 	intense = intense>>4;										//PD 10May96

	base_colour = (Colour) ((temp->basecolour)>>1);

//	if (intense)												//RJS 27Jun97
//	{															//RJS 27Jun97
//		SLong	temp1,temp2;									//RJS 27Jun97
//		temp1 = (SLong )base_colour;							//RJS 27Jun97
//		temp1 &= 0x0FF;											//RJS 27Jun97

//		temp2 = intense;										//RJS 27Jun97
//		temp1 = ASM_GetFadeColour(temp1,temp2);					//RJS 27Jun97
//		base_colour = (Colour )temp1;							//RJS 27Jun97
//	}

	shape::range = temp->spread;								//PD 25Jan96

	shape::colour = base_colour;								//PD 25Jan96

	shape::image = (ImageMapNumber) temp->imap;					//RJS 18Feb97

	if(((shape::image & 0x7FFF) != 0x0FF)&&(object_dist<fade_start))//RJS 05Nov98
		current_screen->SetColour(shape::image);				//PD 25Jan96

	if(shape::range == -1)
		current_screen->SetColour(base_colour);
	else
		current_screen->SetColour(base_colour,shape::range);	//PD 25Jan96

	instr_ptr += sizeof(DOSETCOLOUR256);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	doswitch
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
 void shape::doswitch(UByte *& instr_ptr)
{
	DOSWITCH_PTR	ptr = (DOSWITCH_PTR) instr_ptr;				//RJS 13Mar98
//DeadCode RJS 21Apr99 	UByteP			adptr = (UByteP) object_obj3d->AnimPtr;		//RJS 13Mar98
	ULong			flag = GlobalAdptr[ptr->animoff];					//RJS 13Mar98
																//RJS 13Mar98

	instr_ptr += sizeof(DOSWITCH);								//RJS 27May98
																//RJS 27May98
	if (ptr->nobits)											//RJS 27May98
	{															//RJS 27May98
		flag >>= ptr->bitoffset;
		flag &= 1;
																//RJS 27May98
		if (flag != ptr->value)									//RJS 15Jun98
			instr_ptr--;										//RJS 27May98
	}															//RJS 27May98
	else
	{
		flag /= ptr->animscale;										//RJS 13Mar98
																	//RJS 13Mar98
		switch (ptr->condition)										//RJS 13Mar98
		{															//RJS 13Mar98
			case GREATER_THAN:										//RJS 13Mar98
				if (flag <= ptr->value)								//RJS 13Mar98
					instr_ptr--;									//RJS 13Mar98
				break;												//RJS 13Mar98
			case LESS_THAN:											//RJS 13Mar98
				if (flag >= ptr->value)								//RJS 13Mar98
					instr_ptr--;									//RJS 13Mar98
				break;
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dosetcolourall
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
 void shape::dosetcolourall(UByte *& instr_ptr)
{
	_Error.EmitSysErr(__FILE__":ILLEGAL instruction - dosetcolourall");
	instr_ptr += sizeof(DOSETCOLOURALL);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dopoint2x
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void shape::dopoint2x(UByte *& instr_ptr)
{
	UWord	vertex1,
			vertex2;

	DOPOINT2X_PTR dp2x_ptr = (DOPOINT2X_PTR)instr_ptr;

	vertex1 = dp2x_ptr->start_vertex;
	vertex2 = (UWord )(vertex1 + dp2x_ptr->next_vertex_offset);	//PD 15Jan96
	{
		DoPointStruc& dp=newco[vertex1];
		dp.bodyx.i = dp2x_ptr->xcoord;
		dp.bodyy.i = dp2x_ptr->ycoord;
		dp.bodyz.i = dp2x_ptr->zcoord;
//DeadCode PD 05Oct98 		dp.bodyx.i = dp2x_ptr->xcoord<<shapescale;
//DeadCode PD 05Oct98 		dp.bodyy.i = dp2x_ptr->ycoord<<shapescale;
//DeadCode PD 05Oct98 		dp.bodyz.i = dp2x_ptr->zcoord<<shapescale;
		_matrix.transformNC(fpobject_matrix,&dp);
		dp.bodyx.f += object_obj3d->Body.X.f;
		dp.bodyy.f += object_obj3d->Body.Y.f;
		dp.bodyz.f += object_obj3d->Body.Z.f;
		_matrix.SetClipFlags(dp);
//		if (!doingHW3D) _matrix.body2screen(dp);				//PD 19Jun98
		dp.intensity = -1;//0;//-1;									//RJS 20Mar98
		dp.specFlip=
		dp.specular=-1;
	}
	{
		DoPointStruc& dp=newco[vertex2];
		dp.bodyx.i = 0-dp2x_ptr->xcoord;
		dp.bodyy.i = dp2x_ptr->ycoord;
		dp.bodyz.i = dp2x_ptr->zcoord;
//DeadCode PD 05Oct98 		dp.bodyx.i = 0-dp2x_ptr->xcoord<<shapescale;
//DeadCode PD 05Oct98 		dp.bodyy.i = dp2x_ptr->ycoord<<shapescale;
//DeadCode PD 05Oct98 		dp.bodyz.i = dp2x_ptr->zcoord<<shapescale;
		_matrix.transformNC(fpobject_matrix,&dp);
		dp.bodyx.f += object_obj3d->Body.X.f;
		dp.bodyy.f += object_obj3d->Body.Y.f;
		dp.bodyz.f += object_obj3d->Body.Z.f;
		_matrix.SetClipFlags(dp);
//		if (!doingHW3D) _matrix.body2screen(dp);				//PD 19Jun98
		dp.intensity = -1;//0;//-1;									//RJS 20Mar98
		dp.specFlip=
		dp.specular=-1;											//PD 24Aug98
	}
	instr_ptr += sizeof(DOPOINT2X);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	do4cmpt2x
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
 void shape::do4cmpt2x(UByte *& instr_ptr)
{
	instr_ptr += sizeof(DO4CMPT2X);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	doifcase
//LastModified:	PD 15Apr96
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
 void shape::doifcase(UByte *& instr_ptr)
{
	DOIFCASE_PTR dic_ptr = (DOIFCASE_PTR )instr_ptr;			//RJS 04Nov98
//DeadCode RJS 21Apr99 	UByteP	adptr = (UByteP) object_obj3d->AnimPtr;				//RJS 18Feb97
	SLong	offset;												//RJS 15May98
	UWord	realcnt = dic_ptr->count - 1;						//RJS 04Nov98
																//RJS 15May98
	if (dic_ptr->bidirectional)									//RJS 15May98
	{															//RJS 15May98
		offset = *((SByteP)&GlobalAdptr[dic_ptr->flag]);				//RJS 15May98
		offset /= dic_ptr->factor;								//RJS 15May98
		if (offset)												//RJS 15May98
			offset += dic_ptr->shiftup;							//RJS 15May98
	}															//RJS 15May98
	else														//RJS 15May98
		offset = GlobalAdptr[dic_ptr->flag] / dic_ptr->factor;		//RJS 15May98
																//RJS 15May98
	if (offset > realcnt)										//RJS 04Nov98
		offset = realcnt;										//RJS 04Nov98
																//RJS 15May98
	instr_ptr += sizeof(DOIFCASE) + (offset * sizeof(UWord));	//RJS 15May98

	instr_ptr += *(UWord *)instr_ptr;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	donincpnts
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
 void shape::donincpnts(UByte *& instr_ptr)
{
	DONINCPNTS_PTR nip_ptr;

	nip_ptr = (DONINCPNTS_PTR )instr_ptr;

	instr_ptr += nip_ptr->count * (sizeof(DOINIT) + sizeof(DOINC)) + 
					sizeof(DONINCPNTS);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dotransparenton
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
 void shape::dotransparenton(UByte *&instr_ptr)			//RJS 18Jun97
{
	DOTRANSPARENTON_PTR	ptr = (DOTRANSPARENTON_PTR) instr_ptr;

 	current_screen->SetTransparency(ptr->depth);				//RJS 18Jun97
 	POLYGON.SetOpacityON();										//RJS 14May97

	instr_ptr += sizeof(DOTRANSPARENTON);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dotransparentoff
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
 void shape::dotransparentoff(UByte *& )							//PD 29Nov95
{
	current_screen->SetLuminosity(0);							//RJS 19Jan98
	current_screen->SetTransparency(SMOKED_OFF);				//RJS 18Jun97

	if (SHAPE.oldAlphaSwitch != -1)
	{
		current_screen->DoSetGlobalAlpha(SHAPE.oldAlphaSwitch);
		SHAPE.oldAlphaSwitch = -1;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dosphere
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	Martin 16 Apr 1996
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void shape::dosphere(UByte *& instr_ptr)
{
	DOSPHERE_PTR sphere_ptr;

	sphere_ptr = (DOSPHERE_PTR )instr_ptr;

	SHAPE.drawsphere(	sphere_ptr->vertex,
						sphere_ptr->radius,
						sphere_ptr->colour,
						sphere_ptr->animflag,
						sphere_ptr->animscale,
						sphere_ptr->transp,
						(Bool)sphere_ptr->smooth,
						sphere_ptr->halowidth,
						sphere_ptr->lumtype,
						sphere_ptr->animflag2);					//RJS 21Jan98

	instr_ptr += sizeof(DOSPHERE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		domorphsphere
//Author		Robert Slater
//Date			Tue 27 Jan 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::domorphsphere(UByte *& instr_ptr)
{
	DOMORPHSPHERE_PTR sphere_ptr = (DOMORPHSPHERE_PTR )instr_ptr;
	SLong		 radius;
//DeadCode RJS 21Apr99 	UByteP		adptr = (UByteP) object_obj3d->AnimPtr;
	UWord		timeframe;
	SLong		timefrac;
	int			lumtype;
	int			transp;
	int			growth = sphere_ptr->MrphGrowtime;
	int			delta;
	UByte		animflag;
	UByte		colour = sphere_ptr->colour;
	int			randcol;

	radius = sphere_ptr->radius;
	lumtype = sphere_ptr->lumtype;
	transp = sphere_ptr->transp;

	timeframe = *((UWordP)&GlobalAdptr[sphere_ptr->MrphAnim]);
	timefrac = (timeframe << 15)/growth;

	delta = (timefrac*(sphere_ptr->MrphRadius - radius))>>15;
	radius += delta;

	delta = (timefrac*(sphere_ptr->MrphLumtype - lumtype))>>15;
	lumtype += delta;

	delta = (timefrac*(sphere_ptr->MrphTransp - transp))>>15;
	transp += delta;

	delta = (timefrac*(sphere_ptr->MrphColour - colour))>>15;
	colour += delta;

	if (sphere_ptr->animflag && sphere_ptr->animscale)
	{
		animflag = GlobalAdptr[sphere_ptr->animflag];
		randcol = SHAPE.Noise(	object_obj3d->ItemPtr->World.X + animflag,
								object_obj3d->ItemPtr->World.Y + animflag,
								object_obj3d->ItemPtr->World.Z + animflag	);

		animflag++;

		randcol *= -sphere_ptr->animscale;
		randcol >>= 8;

		colour += randcol;
		GlobalAdptr[sphere_ptr->animflag] = animflag;
	}

//DeadCode RJS 03Feb98 	SHAPE.drawsphere(	sphere_ptr->vertex,
//DeadCode RJS 03Feb98 						radius,
//DeadCode RJS 03Feb98 						sphere_ptr->colour,
//DeadCode RJS 03Feb98 						sphere_ptr->animflag,
//DeadCode RJS 03Feb98 						sphere_ptr->animscale,
//DeadCode RJS 03Feb98 						transp,
//DeadCode RJS 03Feb98 						(Bool)sphere_ptr->smooth,
//DeadCode RJS 03Feb98 						sphere_ptr->halowidth,
//DeadCode RJS 03Feb98 						lumtype,
//DeadCode RJS 03Feb98 						0			);

	SHAPE.drawsphere(	sphere_ptr->vertex,
						radius,
						colour,
						0,
						1,
						transp,
						(Bool)sphere_ptr->smooth,
						sphere_ptr->halowidth,
						lumtype,
						0			);

	instr_ptr += sizeof(DOMORPHSPHERE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		domorphsphereimapd
//Author		Robert Slater
//Date			Tue 27 Jan 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::domorphsphereimapd(UByte *& instr_ptr)
{
	DOMORPHCYLINDERIMAPD_PTR ptr = (DOMORPHCYLINDERIMAPD_PTR )instr_ptr;
	SWord		 radius;
//DeadCode RJS 21Apr99 	UByteP		adptr = (UByteP) object_obj3d->AnimPtr;
	UWord		timeframe;
	int			lumtype;
	int			transp;
	int			growth = ptr->MrphGrowtime;
	int			delta;
	UWord		frameno = 0;
	ImageMapNumber	imap;
	SWord		oldalpha = -1;									//RJS 27Nov98
	UByte		fadedepth = GlobalAdptr[ptr->fadeoff];				//RJS 27Nov98

	if (ptr->fadeoff && (fadedepth < 255))						//RJS 27Nov98
		oldalpha = current_screen->DoSetGlobalAlpha(fadedepth);	//RJS 27Nov98

	radius = ptr->radius;
	lumtype = ptr->lumtype;
	transp = ptr->transp;

	timeframe = *((UWordP)&GlobalAdptr[ptr->MrphAnim]);

	delta = (timeframe*(ptr->MrphRadius - radius))/growth;
	radius += delta;

	delta = (timeframe*(ptr->MrphLumtype - lumtype))/growth;
	lumtype += delta;

	if (!lumtype)
	{
		delta = (timeframe*(ptr->MrphTransp - transp))/growth;
		transp += delta;
	}

	if (ptr->animflag)
	{
		frameno = GlobalAdptr[ptr->animflag] / ptr->animscale;
		if (ptr->imap2 && (frameno >= ptr->framelimit))
		{
			frameno -= ptr->framelimit;
			imap = (ImageMapNumber) ptr->imap2;
		}
		else
			imap = (ImageMapNumber) ptr->imap1;
	}
	else
		imap = (ImageMapNumber) ptr->imap1;

	SHAPE.imapcylinder(	ptr->vertex1,
						ptr->vertex2,
						radius,
						imap,
					   	ptr->min_ix,ptr->min_iy,
					  	ptr->width,ptr->height,
						frameno,
						0);   // trans depth...					//RJS 20Nov98

	if (oldalpha > -1)											//RJS 27Nov98
		current_screen->DoSetGlobalAlpha(oldalpha);				//RJS 27Nov98

	instr_ptr += sizeof(DOMORPHCYLINDERIMAPD);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dosmokedon
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
 void shape::dosmokedon(UByte *& )								//PD 29Nov95
{
//TempCode DAW 19Dec96 	current_screen->SetTransparency(0x0FFFF);					//PD 02Apr96
	current_screen->SetTransparency(0x00000);					//DAW 19Dec96
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dosmokedoff
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
 void shape::dosmokedoff(UByte *& )								//PD 29Nov95
{
	current_screen->SetTransparency(0x00000);					//PD 02Apr96
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	donormal
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
 void shape::donormal(UByte *& instr_ptr)
{
	instr_ptr += sizeof(DONORMAL);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dosmoothpoly
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
 void shape::dosmoothpoly(UByte *& instr_ptr)
{
  	DOSMOOTHPOLY_PTR	poly_data;
 	
 	poly_data = (DOSMOOTHPOLY_PTR )instr_ptr;
 
//DeadCode RJS 23Mar98  	SWord intensity = 0;//temp code
//DeadCode RJS 23Mar98 	int i;
//DeadCode RJS 23Mar98  	UByte j;
//DeadCode RJS 23Mar98  	UWord vertex;
//DeadCode RJS 23Mar98  
//DeadCode RJS 23Mar98  	POLYGON.createpoly(shape::colour,shape::range);				//PD 25Jan96
//DeadCode RJS 23Mar98  	j= poly_data->edges;
//DeadCode RJS 23Mar98  
//DeadCode RJS 23Mar98  
//DeadCode RJS 23Mar98  	for (i=0;i<j;i++)
//DeadCode RJS 23Mar98  	{
//DeadCode RJS 23Mar98   		vertex = poly_data->vertices[i];
//DeadCode RJS 23Mar98  		vertex = (UWord )vertex;								//RJS 10Mar97
//DeadCode RJS 23Mar98  		POLYGON.createvert(newco[vertex],intensity);
//DeadCode RJS 23Mar98  		if (i==1)
//DeadCode RJS 23Mar98 		intensity =255;
//DeadCode RJS 23Mar98  	}
//DeadCode RJS 23Mar98 	POLYGON.drawpoly();
 	instr_ptr +=  sizeof(DOSMOOTHPOLY) + poly_data->edges*sizeof(UWord);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dovector
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void shape::dovector(UByte *& instr_ptr)
{
	DOVECTOR_PTR	ptr = (DOVECTOR_PTR) instr_ptr;
	int				vertex;
	SLong			intensity;									//RJS 20Mar98
	SLong			specular;
	SLong			specflip;

	if (View_Point->isLightShaded)								//RJS 06May98
	{
		IFShare& li=TransLightVector.ni;
		IFShare& lj=TransLightVector.nj;
		IFShare& lk=TransLightVector.nk;
		Float an=ptr->an;
		Float bn=ptr->bn;
		Float cn=ptr->cn;
		double mag=an*an+bn*bn+cn*cn;
		_asm {	fld mag;
				fsqrt;
				fstp mag;
		}
		an/=mag; bn/=mag; cn/=mag;
		Float fintensity=li.f*an+lj.f*bn+lk.f*cn;
		if (specularEnabled)
		{
		 	IFShare& vi=TransViewVector.ni;
		 	IFShare& vj=TransViewVector.nj;
		 	IFShare& vk=TransViewVector.nk;
			double fspecular=vi.f*an+vj.f*bn+vk.f*cn;
			calcSpecular(fspecular,fintensity,specular,specflip);
		}
		else specular=specflip=-1;

		fintensity*=Float(32385);

		intensity = fintensity;
		intensity+=32385;	//range is (-127 * 255) to (127 * 255) (ie. -32385 to 32385)
		if (ptr->ambientfiddle)
		{
			intensity /= 232;											//RJS 23Apr98
			intensity = 280 - intensity;								//RJS 20Mar98
			if (intensity > 256)										//RJS 20Mar98
				intensity = 256;										//RJS 20Mar98
		}
		else
		{
			intensity >>= 8;
			intensity = 256 - intensity;
		}

		vertex = ptr->vertex;
		if (intensity<0) intensity=0;

		newco[vertex].intensity = intensity;						//RJS 20Mar98
		newco[vertex].specular = specular;						//PD 24Aug98
		newco[vertex].specFlip = specflip;						//PD 24Aug98
	}

	instr_ptr += sizeof(DOVECTOR);
}

void shape::makeViewLightVec()
{
/*DEAD	COORDS3D &viewPos=View_Point->World;
	//COORDS3D &itemPos=object_obj3d->ItemPtr->World;
	LightVec &sunPos=Three_Dee.SunLightVector;
	IFShare &li=ViewLightVector.ni,&lj=ViewLightVector.nj,&lk=ViewLightVector.nk;
	li.i=sunPos.ni.i-viewPos.X;
	lj.i=sunPos.nj.i-viewPos.Y;
	lk.i=sunPos.nk.i-viewPos.Z;
	_matrix.transform(Three_Dee.fpviewer_matrix,li,lj,lk);
	li.f-=object_obj3d->Body.X.f;
	lj.f-=object_obj3d->Body.Y.f;
	lk.f-=object_obj3d->Body.Z.f;
	double mag=li.f*li.f+lj.f*lj.f+lk.f*lk.f;
	_asm 
	{
	fld mag;
	fsqrt;
	fstp mag;
	}
	li.f/=mag; lj.f/=mag; lk.f/=mag;
	IsAircraft|=0x02;
DEAD*/
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dotransformlight
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void shape::dotransformlight(UByte *& )
{
	if (!IsSubShape)
	{
		if (!Save_Data.fSoftware && object_obj3d->ItemPtr->Status.size==AirStrucSize) specularEnabled=true;

		current_screen->DoSetShadeVals(shadedRed,shadedGreen,shadedBlue,
										Land_Scape.currentLighting.effectsAmbientCol.red(),
										Land_Scape.currentLighting.effectsAmbientCol.green(),
										Land_Scape.currentLighting.effectsAmbientCol.blue());
		COORDS3D itemPos;

		if (!Three_Dee.GetPosRec(object_obj3d->ItemPtr,itemPos))
			itemPos=object_obj3d->ItemPtr->World;

		LightVec& sunPos=Three_Dee.SunLightVector;

		IFShare& li=TransLightVector.ni;
		IFShare& lj=TransLightVector.nj;
		IFShare& lk=TransLightVector.nk;
			
		li.i=sunPos.ni.i;	//-itemPos.X;
		lj.i=sunPos.nj.i;	//-itemPos.Y;
		lk.i=sunPos.nk.i;	//-itemPos.Z;

		_matrix.inverseMobileMatrix(object_obj3d->AngH,object_obj3d->AngC,
									object_obj3d->AngR,light_matrix);

		_matrix.transform(&light_matrix,li,lj,lk);

		//and normalise...

		double mag=li.f*li.f+lj.f*lj.f+lk.f*lk.f;

		_asm {	fld mag;
				fsqrt;
				fstp mag;
		}
		li.f/=mag; lj.f/=mag; lk.f/=mag;

//dead		if (specularEnabled)
		{
			IFShare& vi=TransViewVector.ni;
			IFShare& vj=TransViewVector.nj;
			IFShare& vk=TransViewVector.nk;

			COORDS3D& viewPos=View_Point->World;

			vi.i=(viewPos.X-itemPos.X)&0xFFFFFF80;
  			vj.i=(viewPos.Y-itemPos.Y)&0xFFFFFF80;
			vk.i=(viewPos.Z-itemPos.Z)&0xFFFFFF80;

			_matrix.transform(&light_matrix,vi,vj,vk);

			mag=vi.f*vi.f+vj.f*vj.f+vk.f*vk.f;

			_asm {	fld mag;
					fsqrt;
					fstp mag;
			}

			vi.f/=mag; vj.f/=mag; vk.f/=mag;
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		doswitchlightson
//Author		Robert Slater
//Date			Thu 30 Apr 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void shape::dolshadeon(UByte *& instr_ptr)
{
	DOLSHADEON_PTR	ptr = (DOLSHADEON_PTR) instr_ptr;

	if (Save_Data.detail_3d[DETAIL3D_ITEMSHADING] && doingHW3D)													//RJS 13jul98
	{
		View_Point->isLightShaded = TRUE;							//RJS 06May98
		//specularEnabled=true;
		current_screen->DoSetLShade(true);
	}
	else
	{
		//specularEnabled=false;
		View_Point->isLightShaded = FALSE;							//RJS 06May98
	}

	instr_ptr += sizeof(DOLSHADEON);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dorelpoly
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void shape::dorelpoly(UByte *& instr_ptr)
{
	DORELPOLY_PTR drp_ptr=(DORELPOLY_PTR)instr_ptr;
	int j=drp_ptr->edges;
	SByte* pOffset=(SByte*)instr_ptr+sizeof(DORELPOLY);
	UWord vertex=UWord(drp_ptr->start_vertex);
	DoPointStruc** pDp=polyVertIndex;
	oredFlags=CF3D_NULL;
	andedFlags=CF3D_ALL;
	for (int i=0;i<j;i++){
		DoPointStruc& dp=newco[vertex];
		oredFlags|=dp.clipFlags;
		andedFlags&=dp.clipFlags;
		*pDp++=&dp;
		vertex=UWord(vertex+*pOffset++);
	}
	//test clip flags before drawing the polygon...
	bool clipping=(oredFlags!=CF3D_NULL)?true:false;
	bool visible=(andedFlags==CF3D_NULL)?true:false;
	if (visible){
		//if 'clipping' is false then this poly will not need any clipping

		POLYGON.createpoly(shape::colour);
		pDp=polyVertIndex;
		for (i=0;i<j;i++){
			DoPointStruc& dp=**pDp++;
			SWord iVal=dp.intensity;
			if (iVal>=0) POLYGON.createvert(dp,iVal);//RJS 13Jul98
			else{
//				iVal+=255;
				POLYGON.createvert(dp);				//RJS 13Jul98
			}
		}
		POLYGON.drawpoly();
	}
	instr_ptr+=sizeof(DORELPOLY)+(j-1)*sizeof(SByte);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		donspheres
//Author		Robert Slater
//Date			Mon 13 Jul 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::donspheres(UByte *& instr_ptr)						//RJS 13Jul98
{
	DONSPHERES_PTR	ptr = (DONSPHERES_PTR) instr_ptr;
	int	count;



	instr_ptr += sizeof(DONSPHERES);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		donspheresimapd
//Author		Robert Slater
//Date			Mon 13 Jul 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::donspheresimapd(UByte *& instr_ptr)				//RJS 13Jul98
{
	DONSPHERESIMAPD_PTR	ptr = (DONSPHERESIMAPD_PTR) instr_ptr;
	int	count;



	instr_ptr += sizeof(DONSPHERESIMAPD);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		doweaponoff
//Author		Robert Slater
//Date			Tue 14 Jul 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::doweaponoff(UByte *& instr_ptr)								//RJS 13Jul98
{
	DOWEAPONOFF_PTR ptr = (DOWEAPONOFF_PTR) instr_ptr;
//DeadCode RJS 21Apr99 	UByteP			adptr = (UByteP)object_obj3d->AnimPtr;

	instr_ptr += sizeof(DOWEAPONOFF);
	if (GlobalAdptr[ptr->launchoffset] == ptr->launchertype)
	{
		SWord	stores = *((SWordP)&GlobalAdptr[ptr->storesoffset]);
		if (stores == 0)
			instr_ptr--;
	}
	else
		instr_ptr--;													//RJS 02Jun99
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dodrawreflectpoly
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
 void shape::dodrawreflectpoly(UByte *& instr_ptr )				
{
	int j=((DODRAWREFLECTPOLY_PTR)instr_ptr)->nopoints;
	instr_ptr+=sizeof(DODRAWREFLECTPOLY);
	oredFlags=CF3D_NULL;
	andedFlags=CF3D_ALL;
	DoPointStruc** pDp=polyVertIndex;
	for (int i=0;i<j;i++){
		DoPointStruc& dp=newco[*instr_ptr++];
		oredFlags|=dp.clipFlags;
		andedFlags&=dp.clipFlags;
		*pDp++=&dp;
	}
	//test clip flags before drawing the polygon...
	bool clipping=(oredFlags!=CF3D_NULL)?true:false;
	bool visible=(andedFlags==CF3D_NULL)?true:false;
	if (!Save_Data.fSoftware && Save_Data.cockpit3Ddetail[COCK3D_SKYIMAGES] && visible){

		current_screen->DoSetTranspFade(true);

		//if 'clipping' is false then this poly will not need any clipping
		pDp=polyVertIndex;
		for (i=0;i<j;i++){
			DoPointStruc& dp=**pDp++;
			SWord iVal=dp.intensity;

			if (iVal < 0)										//RJS 13Jul98
				POLYGON.createvert(dp,dp.ix,dp.iy);				//RJS 13Jul98
			else												//RJS 13Jul98
				POLYGON.createvert(dp,dp.ix,dp.iy,iVal);		//RJS 13Jul98
		}
		POLYGON.drawpoly();

		current_screen->DoSetTranspFade(false);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		doresetanim
//Author		Robert Slater
//Date			Fri 13 Nov 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void shape::doresetanim(UByte *& instr_ptr)			
{
	DORESETANIM_PTR	ptr = (DORESETANIM_PTR) instr_ptr;
//DeadCode RJS 21Apr99 	UByteP			adptr = (UByteP) object_obj3d->AnimPtr;
	UWord			controlframe = *((UWordP)&GlobalAdptr[ptr->animofftimer]);

	if (controlframe == 0)
		GlobalAdptr[ptr->animoffframe] = ptr->resetval;

	instr_ptr += sizeof(DORESETANIM);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	docapture
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
 void shape::dospin(UByte *& instr_ptr)
{
	DOSPIN_PTR	ptr = (DOSPIN_PTR) instr_ptr;
//DeadCode RJS 21Apr99 	UByteP		adptr = (UByteP) object_obj3d->AnimPtr;
	UWordP		anglep = (UWordP)&GlobalAdptr[ptr->animoff];
	UWord		currentangle = *anglep;
	UWord		spinspeed = *((UWordP)&GlobalAdptr[ptr->speedoff]);

	if (spinspeed)
	{
		currentangle += ((spinspeed * current_screen->FrameTime())/100);
		*anglep = currentangle;
	}
	else
	{
		UWord	diff = ptr->maxspeed - ptr->minspeed;
		if (diff)												//MS 10Dec98
		{
			spinspeed = ptr->minspeed + Math_Lib.rnd(diff);
			*((UWordP)&GlobalAdptr[ptr->speedoff]) = spinspeed;
		}
		else
			*anglep = ptr->minspeed;			// crap fix to fix rotate...//MS 10Dec98
	}

	instr_ptr += sizeof(DOSPIN);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dosetcolourh
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
 void shape::dosetcolourh(UByte *& instr_ptr)
{
	_Error.EmitSysErr(__FILE__":ILLEGAL instruction - dosetcolourh");
	instr_ptr += sizeof(DOSETCOLOURH);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	doquiksmoothpoly
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
 void shape::doquiksmoothpoly(UByte *& instr_ptr)
{
//DeadCode RJS 23Mar98 	DOQUIKSMOOTHPOLY_PTR poly_data;
//DeadCode RJS 23Mar98 
//DeadCode RJS 23Mar98 	poly_data = (DOQUIKSMOOTHPOLY_PTR )instr_ptr;
//DeadCode RJS 23Mar98 
//DeadCode RJS 23Mar98 	
//DeadCode RJS 23Mar98 	SWord intensity = 0;//temp code
//DeadCode RJS 23Mar98 	int i,j;
//DeadCode RJS 23Mar98 	UWord vertex;
//DeadCode RJS 23Mar98 
//DeadCode RJS 23Mar98 	POLYGON.createpoly(shape::colour,shape::range);				//PD 25Jan96
//DeadCode RJS 23Mar98 	j= poly_data->edges;
//DeadCode RJS 23Mar98 
//DeadCode RJS 23Mar98 
//DeadCode RJS 23Mar98 	for (i=0;i<j;i++)
//DeadCode RJS 23Mar98 	{
//DeadCode RJS 23Mar98 		vertex = (UWord )poly_data->vertices[i];				//RJS 10Mar97
//DeadCode RJS 23Mar98 		POLYGON.createvert(newco[vertex],intensity);
//DeadCode RJS 23Mar98 		if (i==1)
//DeadCode RJS 23Mar98 		intensity =255;
//DeadCode RJS 23Mar98 	}
//DeadCode RJS 23Mar98 	POLYGON.drawpoly();
//DeadCode RJS 23Mar98 
//DeadCode RJS 23Mar98 	instr_ptr += sizeof(DOQUIKSMOOTHPOLY) + j*sizeof(UWord);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dorepos
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
 void shape::dorepos(UByte *& )									//PD 29Nov95
{
	_Error.EmitSysErr(__FILE__":Not a real instruction (DOREPOS)\n");
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dodepthcolour
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
 void shape::dodepthcolour(UByte *& )							//PD 29Nov95
{
	_Error.EmitSysErr(__FILE__":Not a real instruction (DODEPTHCOLOUR)\n");
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dodepthpoly
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
 void shape::dodepthpoly(UByte *& )								//PD 29Nov95
{
	_Error.EmitSysErr(__FILE__":Not a real instruction (DODEPTHPOLY)\n");
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	doimagemap
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
 void shape::doimagemap(UByte *& )								//PD 29Nov95
{
	//Empty
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	docreateipoly
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void shape::docreateipoly(UByte *& instr_ptr)
{
	DOCREATEIPOLY_PTR ptr = (DOCREATEIPOLY_PTR)instr_ptr;
	ImageMapNumber	imapno;
	imapno = (ImageMapNumber )ptr->image_no;
	if (IsAircraft && (current_level>=2))
	{
		//once only per shape, generate light shade info
		//if (!(IsAircraft&0x02))	makeViewLightVec();
		//select colour from the image;
		ImageMapDescPtr imap=Image_Map.GetImageMapPtr(imapno);
		shape::colour=Colour(*imap->body);
		current_screen->SetColour(shape::colour);
		POLYGON.createpoly(shape::colour);
	}
	else POLYGON.createpoly(imapno);
	instr_ptr += sizeof(DOCREATEIPOLY);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	docreateivert
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
 void shape::docreateivert(UByte *& instr_ptr)
{
	instr_ptr += sizeof(DOCREATEIVERT);
}

SWord shape::plainPolyLight(DoPointStruc** pDp)
{
	//generate 2 vectors
	Float a[3],b[3],n[3];
	a[0]=pDp[1]->bodyx.f-pDp[0]->bodyx.f;
	a[1]=pDp[1]->bodyy.f-pDp[0]->bodyy.f;
	a[2]=pDp[1]->bodyz.f-pDp[0]->bodyz.f;
	b[0]=pDp[1]->bodyx.f-pDp[2]->bodyx.f;
	b[1]=pDp[1]->bodyy.f-pDp[2]->bodyy.f;
	b[2]=pDp[1]->bodyz.f-pDp[2]->bodyz.f;
	//use cross product to generate normal
	n[0]=a[1]*b[2]-a[2]*b[1];
	n[1]=a[2]*b[0]-a[0]*b[2];
	n[2]=a[0]*b[1]-a[1]*b[0];
	//normalise vector
	double mag=n[0]*n[0]+n[1]*n[1]+n[2]*n[2];
	_asm 
	{
	fld mag;
	fsqrt
	fstp mag
	}
	n[0]/=-mag; n[1]/=-mag; n[2]/=-mag;
	//dot product normal with light vector
	mag=Float(32385)*(n[0]*ViewLightVector.ni.f+
		n[1]*ViewLightVector.nj.f+
		n[2]*ViewLightVector.nk.f);
	SLong intensity=SLong(mag)+32385;
	intensity/=232;
	intensity=280-intensity;
	if (intensity>256)		intensity=256;
	else if (intensity<0)	intensity=0;
	return SWord(intensity);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dodrawipoly
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void shape::dodrawipoly(UByte *& instr_ptr)				//RJS 19Mar97
{
	int j=((DODRAWIPOLY_PTR)instr_ptr)->nopoints;
	instr_ptr+=sizeof(DODRAWIPOLY);
	oredFlags=CF3D_NULL;
	andedFlags=CF3D_ALL;
	DoPointStruc** pDp=polyVertIndex;
	for (int i=0;i<j;i++){
		DoPointStruc& dp=newco[*instr_ptr++];
		oredFlags|=dp.clipFlags;
		andedFlags&=dp.clipFlags;
		*pDp++=&dp;
	}
	//test clip flags before drawing the polygon...
	bool clipping=(oredFlags!=CF3D_NULL)?true:false;
	bool visible=(andedFlags==CF3D_NULL)?true:false;
	if (visible)
	{
		if (IsAircraft && (current_level>=2))
		{
			pDp=polyVertIndex;
			//create normal from first 3 vertices & do dot product 
			//with viewlightvector to get shade
			SetLineAndDotShade(object_obj3d->ItemPtr,View_Point);
			SWord iVal=dotNLineFadeValue;	//plainPolyLight(pDp);
			for (i=0;i<j;i++){
				DoPointStruc& dp=**pDp++;
				if (dotNLineFadeValue<0)	iVal=0xFF;
				else						iVal=dotNLineFadeValue;
				POLYGON.createvert(dp,iVal);
			}
		}
		else
		{
			//if 'clipping' is false then this poly will not need any clipping
			pDp=polyVertIndex;
			for (i=0;i<j;i++){
				DoPointStruc& dp=**pDp++;
				SWord iVal=dp.intensity;
				if (iVal < 0)	POLYGON.createvert(dp,dp.ix,dp.iy);
				else			POLYGON.createvert(dp,dp.ix,dp.iy,iVal);
			}
		}
		POLYGON.drawpoly();
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		dodrawopoly
//Author		Paul.   
//Date			Tue 16 Apr 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void shape::dodrawopoly(UByte *& )
{
//TempCode DAW 19Dec96 	current_screen->SetTransparency(0x0FFFF);
//TempCode DAW 19Dec96 	POLYGON.SetOpacityON();
	current_screen->SetTransparency(SMOKED_ON);					//RJS 27Mar98
	POLYGON.drawpoly();
	current_screen->SetTransparency(SMOKED_OFF);				//RJS 27Mar98
}
			 
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dodrawrpoly
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
 void shape::dodrawrpoly(UByte *& instr_ptr)								//PD 29Nov95
{
	DODRAWRPOLY_PTR	ptr = (DODRAWRPOLY_PTR )instr_ptr;
//DeadCode RJS 21Apr99 	UByteP	adptr = (UByteP) object_obj3d->AnimPtr;				//RJS 18Feb97
	SLong	flag;												//RJS 12Feb97
	int		novertices;									
	int		i;											
	UByte	vertex;	

	flag = GlobalAdptr[ptr->flag];									//RJS 18Feb97
	novertices = ptr->nopoints;									
	instr_ptr += sizeof(DODRAWRPOLY);

	for (i=0; i < novertices; i++)								
	{															
		vertex = *((UByteP) instr_ptr);
		SWord iVal=newco[vertex].intensity;
		if (iVal < 0) POLYGON.createvert(newco[vertex],newco[vertex].ix,newco[vertex].iy);//RJS 13Jul98
		else{
//			iVal+=255;
			POLYGON.createvert(newco[vertex],newco[vertex].ix,newco[vertex].iy,iVal);//RJS 13Jul98
		}
		instr_ptr += sizeof(UByte);
	}

	POLYGON.ShiftIY(flag*64);
	POLYGON.drawpoly();
}
			 
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	docopyivert
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
 void shape::docopyivert(UByte *& instr_ptr)
{
	UWord	vertex;
	SWord	ix,
			iy;

	DOCOPYIVERT_PTR ptr = (DOCOPYIVERT_PTR)instr_ptr;

	vertex = ptr->vertex;
	ix = ptr->image_x;
	iy = ptr->image_y;

//DeadCode RJS 28Feb97  	if (	((ULong) newco[vertex].bodyx.f == -1.0)
//DeadCode RJS 28Feb97  		&&	((ULong) newco[vertex].bodyy.f == -1.0)
//DeadCode RJS 28Feb97  		&&	((ULong) newco[vertex].bodyz.f == -1.0)
//DeadCode RJS 28Feb97  		&&	((ULong) newco[vertex].screenx.f == -1.0)
//DeadCode RJS 28Feb97  		&&	((ULong) newco[vertex].screeny.f ==-1.0)	)
//DeadCode RJS 28Feb97  	{
//DeadCode RJS 28Feb97  		_Error.EmitSysErr(__FILE__":Bollocks do_point %d, shape %d\n",vertex,object_obj3d->Shape);
//DeadCode RJS 28Feb97  	}
		
	newco[vertex].ix = ix;
	newco[vertex].iy = iy;

//DeadCode RJS 19Mar97 	POLYGON.createvert(newco[vertex],ix,iy);

	instr_ptr += sizeof(DOCOPYIVERT);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dosmthrelpoly
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
 void shape::dosmthrelpoly(UByte *& instr_ptr)
{
//DeadCode RJS 23Mar98 	DOSMTHRELPOLY_PTR drp_ptr;
//DeadCode RJS 23Mar98 
//DeadCode RJS 23Mar98 	UWord	counter;
//DeadCode RJS 23Mar98 
//DeadCode RJS 23Mar98 	drp_ptr = (DOSMTHRELPOLY_PTR )instr_ptr;
//DeadCode RJS 23Mar98 
//DeadCode RJS 23Mar98 	counter = (UWord )(((UWord )drp_ptr->edges)-1);				//PD 15Jan96
//DeadCode RJS 23Mar98 
//DeadCode RJS 23Mar98 	SWord intensity = 3;//temp code
//DeadCode RJS 23Mar98 	int i;
//DeadCode RJS 23Mar98 	UWord vertex,old_vertex,new_vertex;
//DeadCode RJS 23Mar98 	SByte offset;
//DeadCode RJS 23Mar98 
//DeadCode RJS 23Mar98 	POLYGON.createpoly(shape::colour,shape::range);				//PD 25Jan96
//DeadCode RJS 23Mar98 	
//DeadCode RJS 23Mar98 	vertex = (UWord )drp_ptr->start_vertex;						//RJS 10Mar97
//DeadCode RJS 23Mar98 	POLYGON.createvert(newco[vertex]);
//DeadCode RJS 23Mar98 	old_vertex=drp_ptr->start_vertex;
//DeadCode RJS 23Mar98 	
//DeadCode RJS 23Mar98 	for (i=0;i<counter;i++)
//DeadCode RJS 23Mar98 	{
//DeadCode RJS 23Mar98 		offset=*(instr_ptr +(sizeof(DOSMTHRELPOLY))+(i*sizeof(SByte)));
//DeadCode RJS 23Mar98 		new_vertex = (UWord )(old_vertex + offset);				//PD 15Jan96
//DeadCode RJS 23Mar98 		vertex = (UWord )new_vertex;							//RJS 10Mar97
//DeadCode RJS 23Mar98 		POLYGON.createvert(newco[vertex],intensity);
//DeadCode RJS 23Mar98 		old_vertex=new_vertex;
//DeadCode RJS 23Mar98 		if (i==1)
//DeadCode RJS 23Mar98 			intensity =255;
//DeadCode RJS 23Mar98 
//DeadCode RJS 23Mar98 	}
//DeadCode RJS 23Mar98 	POLYGON.drawpoly();
//DeadCode RJS 23Mar98 
//DeadCode RJS 23Mar98 	instr_ptr += sizeof(DOSMTHRELPOLY) + counter * sizeof(SByte);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	doquikrelpoly
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
 void shape::doquikrelpoly(UByte *& instr_ptr)
{
	DOQUIKRELPOLY_PTR drp_ptr;

	UWord	counter;

	drp_ptr = (DOQUIKRELPOLY_PTR )instr_ptr;

	counter = (UWord )(((UWord )drp_ptr->edges)-1);				//PD 15Jan96

	int i;
	UWord vertex,old_vertex,new_vertex;
	SByte offset;

	POLYGON.createpoly(shape::colour);							//PD 25Jan96
	
	vertex = (UWord )drp_ptr->start_vertex;						//RJS 10Mar97
	POLYGON.createvert(newco[vertex]);
	old_vertex=drp_ptr->start_vertex;
	
	for (i=0;i<counter;i++)
	{
		offset=*(instr_ptr +(sizeof(DOQUIKRELPOLY))+(i*sizeof(SByte)));
		new_vertex = (UWord )(old_vertex + offset);				//PD 15Jan96
		vertex = (UWord )new_vertex;							//RJS 10Mar97
		POLYGON.createvert(newco[vertex]);
		old_vertex=new_vertex;

	}
	POLYGON.drawpoly();

	instr_ptr += sizeof(DOQUIKRELPOLY) + counter * sizeof(SByte);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	donsubs
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
 void shape::donsubs(UByte *& instr_ptr)
{
	DONSUBS_PTR dns_ptr;
	UWord	i;
	UByteP	old_ptr;											//RJS 19Mar97

	dns_ptr = (DONSUBS_PTR )instr_ptr;

//	instr_ptr += sizeof(UWord);
	instr_ptr += sizeof(DONSUBS);

	for(i=0;i<dns_ptr->count;i++)								//RJS 19Mar97
	{
		old_ptr = instr_ptr;
		instr_ptr += *(UWord *)instr_ptr;	//Unsigned offset from current pos//RJS 19Mar97
		InterpLoop(instr_ptr);
		instr_ptr = old_ptr + sizeof(SWord);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		dobitsofffx
//Author		Robert Slater
//Date			Fri 15 Jan 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void shape::dobitsofffx(UByte *& instr_ptr)
{
	DOBITSOFFFX_PTR	ptr = (DOBITSOFFFX_PTR)  instr_ptr;
//DeadCode RJS 21Apr99 	UByteP			adptr = (UByteP) object_obj3d->AnimPtr;
	UByte			damval = GlobalAdptr[ptr->animoff];

	if (damval > ptr->threshold)
	{
		if (fprealobject_matrix)
		{
			UWord	threshscale = 255 - ptr->threshold;
			if (threshscale)
			{
				UWord	randno = Math_Lib.rnd() * (damval - ptr->threshold);
				randno /= threshscale;

				if (randno > 32767)
				{
					DoPointStruc dp;
					dp.bodyx.i = ptr->xpos;
					dp.bodyy.i = ptr->ypos;
					dp.bodyz.i = ptr->zpos;
					_matrix.transformNC(fprealobject_matrix,&dp);
					dp.bodyx.f += object_obj3d->ItemPtr->World.X;
					dp.bodyy.f += object_obj3d->ItemPtr->World.Y;
					dp.bodyz.f += object_obj3d->ItemPtr->World.Z;

					WorldStuff*	worldptr = mobileitem::currworld;
					Coords3D	launchcoords;

					launchcoords.X = SLong(dp.bodyx.f);
					launchcoords.Y = SLong(dp.bodyy.f);
					launchcoords.Z = SLong(dp.bodyz.f);

					switch (ptr->fxtype)
					{
						case DAMFX_SPARKS:
							Trans_Obj.LaunchJunk((mobileitem*)object_obj3d->ItemPtr,SPARK,launchcoords,*worldptr);
							break;
						case DAMFX_SMOKE:
							Trans_Obj.LaunchJunk((mobileitem*)object_obj3d->ItemPtr,SPARK,launchcoords,*worldptr);
							break;
						case DAMFX_JUNK:
							Trans_Obj.LaunchJunk((mobileitem*)object_obj3d->ItemPtr,SPARK,launchcoords,*worldptr);
							break;
					}
				}
			}
		}
	}

	instr_ptr += sizeof(DOBITSOFFFX);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		doondamaged
//Author		Robert Slater
//Date			Mon 18 Jan 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void shape::doondamaged(UByte *& instr_ptr)
{
	DOONDAMAGED_PTR	ptr = (DOONDAMAGED_PTR) instr_ptr;
//DeadCode RJS 21Apr99 	UByteP			adptr = (UByteP) object_obj3d->AnimPtr;
	SLong			damval = GlobalAdptr[ptr->animoff];			//RJS 28Apr99
	SLong			topthresh;									//RJS 28Apr99

	instr_ptr += sizeof(DOONDAMAGED);

	if (ptr->topthresh == 0)
		topthresh = 256;
	else
		topthresh = SLong(ptr->topthresh);

	if ((damval < ptr->thresh) || (damval >= topthresh))
		instr_ptr--;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		dosetmipmap
//Author		Robert Slater
//Date			Mon 24 May 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void shape::dosetmipmap(UByte *& instr_ptr)
{
	DOSETMIPMAP_PTR	ptr = (DOSETMIPMAP_PTR) instr_ptr;

	if (ptr->textureflag)
		oldMipMapState = current_screen->DoSetMipMap(oldMipMapState);
	else
		oldMipMapState = current_screen->DoSetMipMap(false);

	instr_ptr += sizeof(DOSETMIPMAP);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	donvec
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void shape::donvec(UByte *& instr_ptr)
{
	DONVEC_PTR dnv_ptr = (DONVEC_PTR )instr_ptr;
	int			j;
	int			vertex;
	int			nopoints;
	NEXTVEC_PTR	vecpoo;
	SLong		intensity;
	SLong		specular;
	SLong		specflip;

	vertex = dnv_ptr->vertex;
	nopoints = dnv_ptr->count;

	instr_ptr += sizeof(DONVEC);

	if (View_Point->isLightShaded)								//RJS 06May98
	{
		IFShare& li=TransLightVector.ni;
		IFShare& lj=TransLightVector.nj;
		IFShare& lk=TransLightVector.nk;

		for (j = 0; j < nopoints; j++)
		{
			vecpoo = (NEXTVEC_PTR) instr_ptr;

			Float an=vecpoo->an;
			Float bn=vecpoo->bn;
			Float cn=vecpoo->cn;

			double mag=an*an+bn*bn+cn*cn;

			_asm {	fld mag;
					fsqrt;
					fstp mag;
			}

			an/=mag; bn/=mag; cn/=mag;

			Float fintensity=li.f*an+lj.f*bn+lk.f*cn;

			if (specularEnabled)
			{
			 	IFShare& vi=TransViewVector.ni;
		 		IFShare& vj=TransViewVector.nj;
			 	IFShare& vk=TransViewVector.nk;
				double fspecular=vi.f*an+vj.f*bn+vk.f*cn;
				calcSpecular(fspecular,fintensity,specular,specflip);
			}
			else specular=specflip=-1;

			fintensity*=Float(32385);

			intensity = fintensity;
			intensity+=32385;	//range is (-127 * 255) to (127 * 255) (ie. -32385 to 32385)
			intensity /= 232;											//RJS 23Apr98
			intensity = 280 - intensity;								//RJS 20Mar98
			if (intensity > 256)										//RJS 20Mar98
				intensity = 256;										//RJS 20Mar98

			if (intensity<0) intensity=0;
		
			newco[vertex].intensity = intensity;					//RJS 20Mar98
			newco[vertex].specular = specular;					//PD 24Aug98
			newco[vertex].specFlip = specflip;					//PD 24Aug98
			vertex++;

			instr_ptr += sizeof(NEXTVEC);
		}
	}
	else
		instr_ptr += (sizeof(NEXTVEC)*nopoints);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	donextvec
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
 void shape::donextvec(UByte *& )								//PD 29Nov95
{
	_Error.EmitSysErr(__FILE__":Not a real instruction (DONEXTVEC)\n");
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	donpoint2x
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void shape::donpoint2x(UByte *& instr_ptr)
{
	UWord	vertex1,
			vertex2;

	UWord	counter;

	DONPOINT2X_PTR npnt_ptr = (DONPOINT2X_PTR )instr_ptr;

	NNEXT2X_PTR ptr = (NNEXT2X_PTR)(instr_ptr+sizeof(DONPOINT2X));

	vertex1 = (UWord )npnt_ptr->start_vertex;					//RJS 10Mar97

	for(counter=0;counter<npnt_ptr->count;counter++)
	{
		vertex2 = (UWord )(vertex1 + ptr->vertex);				//RJS 10Mar97
		{
			DoPointStruc& dp=newco[vertex1];
			dp.bodyx.i = ptr->xcoord;
			dp.bodyy.i = ptr->ycoord;
			dp.bodyz.i = ptr->zcoord;
//DeadCode PD 05Oct98 			dp.bodyx.i = ptr->xcoord<<shapescale;
//DeadCode PD 05Oct98 			dp.bodyy.i = ptr->ycoord<<shapescale;
//DeadCode PD 05Oct98 			dp.bodyz.i = ptr->zcoord<<shapescale;
			_matrix.transformNC(fpobject_matrix,&dp);
			dp.bodyx.f += object_obj3d->Body.X.f;
			dp.bodyy.f += object_obj3d->Body.Y.f;
			dp.bodyz.f += object_obj3d->Body.Z.f;
			_matrix.SetClipFlags(dp);
//			if (!doingHW3D) _matrix.body2screen(dp);			//PD 19Jun98
			dp.intensity = -1;//0;//-1;									//RJS 20Mar98
			dp.specFlip=
			dp.specular=-1;										//PD 24Aug98
		}
		{
			DoPointStruc& dp=newco[vertex2];
			dp.bodyx.i = 0-ptr->xcoord;
			dp.bodyy.i = ptr->ycoord;
			dp.bodyz.i = ptr->zcoord;
//DeadCode PD 05Oct98 			dp.bodyx.i = 0-ptr->xcoord<<shapescale;
//DeadCode PD 05Oct98 			dp.bodyy.i = ptr->ycoord<<shapescale;
//DeadCode PD 05Oct98 			dp.bodyz.i = ptr->zcoord<<shapescale;
			_matrix.transformNC(fpobject_matrix,&dp);
			dp.bodyx.f += object_obj3d->Body.X.f;
			dp.bodyy.f += object_obj3d->Body.Y.f;
			dp.bodyz.f += object_obj3d->Body.Z.f;
			_matrix.SetClipFlags(dp);
//			if (!doingHW3D) _matrix.body2screen(dp);			//PD 19Jun98
			dp.intensity = -1;//0;//-1;									//RJS 20Mar98
			dp.specFlip=
			dp.specular=-1;
		}
		vertex1++;
		ptr++;
	}

	instr_ptr += npnt_ptr->count * sizeof(NNEXT2X) + sizeof(DONPOINT2X);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		docallshape
//Author		Robert Slater
//Date			Thu 27 Feb 1997
//
//Description	Backs up current important shape information,
//				and processes sub shape as a new shape.
//				Restores old shape information.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void shape::docallshape(UByte *& instr_ptr)
{
	DOCALLSHAPE_PTR	ptr = (DOCALLSHAPE_PTR) instr_ptr;
	UByteP			instr_bak = instr_ptr;

	DrawSubShape(instr_ptr);

	instr_ptr = instr_bak;
	instr_ptr += sizeof(DOCALLSHAPE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dosmokepnt
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
 void shape::dosmokepnt(UByte *& instr_ptr)
{
//DeadCode RJS 17Sep97 	DOSMOKEPNT_PTR	ptr = (DOSMOKEPNT_PTR) instr_ptr;
//DeadCode RJS 17Sep97 	UByteP			adptr = (UByteP) object_obj3d->AnimPtr;		//RJS 22May97
//DeadCode RJS 17Sep97 	SWord		*countptr = (SWord*) &adptr[ptr->countoffset];	//RJS 05Jun97
//DeadCode RJS 17Sep97 	SWord		Stores = *countptr;								//RJS 05Jun97
//DeadCode RJS 17Sep97 
//DeadCode RJS 17Sep97 	if (	adptr
//DeadCode RJS 17Sep97 		&&	adptr[ptr->flagoffset]
//DeadCode RJS 17Sep97 		&&	!Timer_Code.paused
//DeadCode RJS 17Sep97 		&&	Stores
//DeadCode RJS 17Sep97 		&&	!IsSubShape)										//RJS 03Jun97
//DeadCode RJS 17Sep97 	{
//DeadCode RJS 17Sep97 		int			index = adptr[ptr->flagoffset];				//RJS 22May97
//DeadCode RJS 17Sep97 		SLong		wx, wy, wz;									//RJS 21May97
//DeadCode RJS 17Sep97 		MATRIX  	omat;										//RJS 21May97
//DeadCode RJS 17Sep97 		MATRIX_PTR	obj_matrix = &omat;							//RJS 21May97
//DeadCode RJS 17Sep97 		UWord		scaleback;									//RJS 21May97
//DeadCode RJS 17Sep97 		TrailRecord*	trailptr = &traillist[index];			//RJS 21May97
//DeadCode RJS 17Sep97 		int			lifetime;
//DeadCode RJS 17Sep97 
//DeadCode RJS 17Sep97 		trailptr->addtime = ptr->LifeTime;
//DeadCode RJS 17Sep97 
//DeadCode RJS 17Sep97 		// -1 is infinite....
//DeadCode RJS 17Sep97 		if (Stores != -1)
//DeadCode RJS 17Sep97 		{
//DeadCode RJS 17Sep97 			Stores-=16;											//RJS 04Jun97
//DeadCode RJS 17Sep97 		
//DeadCode RJS 17Sep97 			if (Stores < 0)
//DeadCode RJS 17Sep97 				Stores = 0;
//DeadCode RJS 17Sep97 
//DeadCode RJS 17Sep97 			*countptr = Stores;
//DeadCode RJS 17Sep97 		}
//DeadCode RJS 17Sep97 
//DeadCode RJS 17Sep97 		if (Stores)
//DeadCode RJS 17Sep97 		{
//DeadCode RJS 17Sep97 			lifetime = ptr->LifeTime;
//DeadCode RJS 17Sep97 
//DeadCode RJS 17Sep97 			if (trailptr->lifetime && (lifetime > 500))
//DeadCode RJS 17Sep97 				lifetime = trailptr->lifetime;
//DeadCode RJS 17Sep97 
//DeadCode RJS 17Sep97  			if (trailptr->nextlist)
//DeadCode RJS 17Sep97  			{
//DeadCode RJS 17Sep97  				Coords3DListPtr	nextptr = traillist[trailptr->nextlist].thelist;
//DeadCode RJS 17Sep97  				if (nextptr)
//DeadCode RJS 17Sep97  				{
//DeadCode RJS 17Sep97  					wx = nextptr->trailpoint.gx;
//DeadCode RJS 17Sep97  					wy = nextptr->trailpoint.gy;
//DeadCode RJS 17Sep97  					wz = nextptr->trailpoint.gz;
//DeadCode RJS 17Sep97  
//DeadCode RJS 17Sep97  					SHAPE.AddNewVapourPoint(trailptr,wx,wy,wz,lifetime);
//DeadCode RJS 17Sep97  					lifetime = trailptr->lifetime;
//DeadCode RJS 17Sep97  				}
//DeadCode RJS 17Sep97  
//DeadCode RJS 17Sep97  				trailptr->nextlist = 0;
//DeadCode RJS 17Sep97  			}
//DeadCode RJS 17Sep97 
//DeadCode RJS 17Sep97 			// Every frame....
//DeadCode RJS 17Sep97 
//DeadCode RJS 17Sep97 			wx = ptr->xcoord << shapescale;
//DeadCode RJS 17Sep97 			wy = ptr->ycoord << shapescale;
//DeadCode RJS 17Sep97 			wz = ptr->zcoord << shapescale;
//DeadCode RJS 17Sep97 
//DeadCode RJS 17Sep97 			_matrix.generate2(	object_obj3d->AngH,
//DeadCode RJS 17Sep97 								object_obj3d->AngC,
//DeadCode RJS 17Sep97 								object_obj3d->AngR,
//DeadCode RJS 17Sep97 								obj_matrix);
//DeadCode RJS 17Sep97 
//DeadCode RJS 17Sep97 			scaleback = _matrix.transform(obj_matrix,wx,wy,wz);
//DeadCode RJS 17Sep97  			wx >>= (16-scaleback);
//DeadCode RJS 17Sep97  			wy >>= (16-scaleback);
//DeadCode RJS 17Sep97  			wz >>= (16-scaleback);
//DeadCode RJS 17Sep97 
//DeadCode RJS 17Sep97 			wx += trailptr->lastwx;
//DeadCode RJS 17Sep97 			wy += trailptr->lastwy;
//DeadCode RJS 17Sep97 			wz += trailptr->lastwz;
//DeadCode RJS 17Sep97 
//DeadCode RJS 17Sep97 			// Reset after approx 128 points.
//DeadCode RJS 17Sep97 			if (trailptr->bitshift == 8)
//DeadCode RJS 17Sep97 			{
//DeadCode RJS 17Sep97 				trailptr->bitshift = 0;
//DeadCode RJS 17Sep97 				trailptr->lifetime = 0;
//DeadCode RJS 17Sep97 				trailptr->addtime = 0;
//DeadCode RJS 17Sep97 				trailptr->nopoints = 0;
//DeadCode RJS 17Sep97 
//DeadCode RJS 17Sep97 				adptr[ptr->flagoffset] = -index;
//DeadCode RJS 17Sep97 				SHAPE.AddNewVapourPoint(trailptr,wx,wy,wz,ptr->LifeTime);
//DeadCode RJS 17Sep97 				SHAPE.DetatchVapourStream(index,LIFETIME_VAPOUR);
//DeadCode RJS 17Sep97 			}
//DeadCode RJS 17Sep97 			else
//DeadCode RJS 17Sep97 				SHAPE.AddNewVapourPoint(trailptr,wx,wy,wz,lifetime);//RJS 29May97
//DeadCode RJS 17Sep97 		}
//DeadCode RJS 17Sep97 		else
//DeadCode RJS 17Sep97 		{
//DeadCode RJS 17Sep97 			adptr[ptr->flagoffset] = 0;
//DeadCode RJS 17Sep97 			SHAPE.DetatchVapourStream(index,LIFETIME_VAPOUR);
//DeadCode RJS 17Sep97 		}
//DeadCode RJS 17Sep97 	}

	instr_ptr += sizeof(DOSMOKEPNT);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dobitsoff
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified		Feb 1997
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
 void shape::dobitsoff(UByte *& instr_ptr)
{
	DOBITSOFF_PTR	dbo_ptr = (DOBITSOFF_PTR )instr_ptr;
//DeadCode RJS 21Apr99 	UByteP	adptr = (UByteP) object_obj3d->AnimPtr;				//RJS 18Feb97
	UByte	damageflag = GlobalAdptr[dbo_ptr->animoff];					//RJS 18Feb97
	SWord	deadoff = dbo_ptr->deadoffset;//RJS 29AUG98

//DeadCode RJS 13Feb97 	UWordP	dammageflags = (UWordP )(animflags+ACBITSFLAGS);
//DeadCode RJS 13Feb97 
//DeadCode RJS 13Feb97 	UWord	localdamflag = *dammageflags;
//DeadCode RJS 13Feb97 
//DeadCode RJS 13Feb97 	localdamflag >>= dbo_ptr->flag;
//DeadCode RJS 13Feb97 
//DeadCode RJS 13Feb97 	localdamflag &= BS_DEAD;

	instr_ptr += sizeof(DOBITSOFF);

	if (damageflag >= BS_DAMLV1)
	{
		if (damageflag < BS_DAMLV2)
			instr_ptr += dbo_ptr->dam1offset;
		else
		{
			if (damageflag < BS_DEAD)
				instr_ptr += dbo_ptr->dam2offset;
			else
			{
				if (object_obj3d->IsTransient && (deadoff==0))
					deadoff = -1;

				instr_ptr += deadoff;
									//After adding the instruction
									//size at the end of this routine
									//the instruction pointer is left
									//looking at a RETURN instruction.
			}
		}
	}
}

static	ULong	biggestcyl = 0;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	doplumepnt
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	
//
//Description	Draws a section of a smoke/vapour/fire trail...
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
 void shape::doplumepnt(UByte *& instr_ptr)						//PD 13Nov97
{
//	ULongP		lo3dptr = (ULongP) &object_obj3d->AngH;			//RJS 17Sep97
//	Obj3DPtr	lastobj3d = (Obj3DPtr) (*lo3dptr);				//RJS 17Sep97
//	VapAnimDatPtr	vapptr = (VapAnimDatPtr) &object_obj3d->AngR;//RJS 18Sep97
//																//RJS 17Sep97
//	if (lastobj3d && vapptr->radius && !Three_Dee.shapecheat)	//RJS 27Mar98
//	{
//		DOPLUMEPNT_PTR	ptr = (DOPLUMEPNT_PTR) instr_ptr;
//		Coords3DListPtr	adptr = (Coords3DListPtr) object_obj3d->AnimPtr;
//		Coords3DListPtr	lastadptr = (Coords3DListPtr) lastobj3d->AnimPtr;
//		VapAnimDatPtr	oldvapptr = (VapAnimDatPtr) &lastobj3d->AngR;//RJS 18Sep97
//		SByte	fadetype = vapptr->depth;		
//		UWord	frameno = vapptr->frameno;
//		UWord	radius = vapptr->radius<<2;
//		UWord	oldrad = oldvapptr->radius<<2;
//		SLong	minx, miny;
//		SLong	realdist;
//		SLong	rangefix = 32768;
//		Bool	drawsphere;
 //		Bool	justsphere= FALSE;								//RJS 04Mar98
//		UByteP	tmpinstptr;
////		UWord	savebornat = adptr->birthdelta;
//	//	ULong	frameoff = ((ULong)&adptr->birthdelta) - ((ULong)adptr);
	//	SWord	xoff0;
	//	SWord	yoff0;
	//	SWord	xoff1 = adptr->xdelta;
	//	SWord	yoff1 = adptr->ydelta;
//
//		if (oldvapptr->radius)
//		{
//			xoff0 = lastadptr->xdelta;
//			yoff0 = lastadptr->ydelta;
//		}
//		else
//		{
//			oldrad = radius;
//
//			xoff0 = (adptr->xdelta * oldrad)/radius;
//			yoff0 = (adptr->ydelta * oldrad)/radius;
//		}
//
//		newco[0].bodyx.f = lastobj3d->Body.X.f;
//		newco[0].bodyy.f = lastobj3d->Body.Y.f;
//		newco[0].bodyz.f = lastobj3d->Body.Z.f;
//
//		newco[1].bodyx.f = object_obj3d->Body.X.f;
//		newco[1].bodyy.f = object_obj3d->Body.Y.f;
//		newco[1].bodyz.f = object_obj3d->Body.Z.f;
//
//		adptr->birthdelta = frameno;
//
//		realdist = (newco[0].bodyz.f + newco[1].bodyz.f)/2;	//RJS 17Sep97
//		if (ptr->rangefar)
//			rangefix = 218918;
//
//		minx = 0;
//		miny = 0;
//
//		if (realdist < rangefix)
//		{
//			drawsphere = FALSE;
//			fadetype = (fadetype * 255)/7;						//RJS 27Mar98
//			current_screen->SetTransparency(fadetype);			//RJS 27Mar98
//
//			if (ptr->sphereframe && realdist < 70000)
//			{
//				drawsphere = TRUE;
//				if (ptr->justspheres && !justsphere)
//					drawsphere = FALSE;
//				else
//				{
//					if (!fadetype)
//						justsphere = FALSE;
//				}
//			}
//
 //			if (!justsphere || !drawsphere)						//RJS 17Nov97
 //			{													//RJS 17Nov97
  //				SHAPE.imaptrailcyl(	0,							//RJS 17Nov97
  	//								1,							//RJS 17Nov97
  	//								(ImageMapNumber )ptr->imagemap,//RJS 17Nov97
  	 //	 							minx,miny,					//RJS 17Nov97
  	//								ptr->width,ptr->height,		//RJS 17Nov97
  	//								ptr->width,ptr->height,		//RJS 17Nov97
  	//								1,frameoff,					//RJS 17Nov97
  	//								xoff0, yoff0,				//RJS 17Nov97
  	//								xoff1, yoff1);				//RJS 17Nov97
 	//		}													//RJS 17Nov97
 //
//DeadCode RJS 06Feb98  			if (drawsphere)
//DeadCode RJS 06Feb98  			{
//DeadCode RJS 06Feb98  				SWord	mapstart = ptr->height*ptr->sphereframe;
//DeadCode RJS 06Feb98  				SWord	mapend = mapstart+ptr->height;
//DeadCode RJS 06Feb98  
//DeadCode RJS 06Feb98  				SHAPE.imapsphere(1,
//DeadCode RJS 06Feb98  							 	radius,
//DeadCode RJS 06Feb98  							 	(ImageMapNumber )ptr->imagemap,
//DeadCode RJS 06Feb98  							 	minx,mapstart,
//DeadCode RJS 06Feb98  							 	ptr->width,ptr->height,
//DeadCode RJS 06Feb98  							 	0);							//RJS 05Feb98
//DeadCode RJS 06Feb98  			}

// 			dotransparentoff(tmpinstptr);
//			current_screen->SetTransparency(SMOKED_OFF);		//RJS 25Nov97
//		}
//		else
//		{
//			DOLINE	tmpinst2;
//
//			tmpinst2.start_vertex = 0;
//			tmpinst2.end_vertex = 1;
//
//			tmpinstptr = (UByteP) &tmpinst2;
//			doline(tmpinstptr);
//		}
//
//		adptr->birthdelta = savebornat;
//	}
//
	instr_ptr += sizeof(DOPLUMEPNT);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	doisphere
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	Martin 16 Apr 1996	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
 void shape::doisphere(UByte *& instr_ptr)
{
	DOISPHERE_PTR 	isphere_ptr = (DOISPHERE_PTR )instr_ptr;			//RJS 05Feb98
//DeadCode RJS 21Apr99 	UByteP			adptr = (UByteP) object_obj3d->AnimPtr; 			//RJS 05Feb98
	UWord			frameno = 0;										//RJS 05Feb98
	SWord			stepx,stepy;
	SWord			nofx;
	SWord			minx, maxx;
	SWord			miny, maxy;
	SWord			width, height;
	SWord			imap = isphere_ptr->image;
	SWord			imap2 = isphere_ptr->image2;
	ImageMapDescPtr imptr;
	SWord			oldGlobalAlpha = -1;
	UWord			angle;
	ImageMapNumber	realmap = (ImageMapNumber) imap;
	UByte			fadedepth = GlobalAdptr[isphere_ptr->fadeoff];	//RJS 27Nov98

	if (isphere_ptr->fadeoff && (fadedepth < 255))				//RJS 27Nov98
		oldGlobalAlpha = current_screen->DoSetGlobalAlpha(fadedepth);//RJS 27Nov98

	minx = isphere_ptr->minx;							//RJS 05Feb98
	miny = isphere_ptr->miny;						 	//RJS 05Feb98
	width = isphere_ptr->width;							//RJS 05Feb98
	height = isphere_ptr->height;						//RJS 05Feb98

	if (isphere_ptr->flagoffset)
	{
		frameno = GlobalAdptr[isphere_ptr->flagoffset] / isphere_ptr->animscale;
		if (imap2 && (frameno >= isphere_ptr->framelimit))
		{
			frameno -= isphere_ptr->framelimit;
			realmap = (ImageMapNumber) imap2;
			minx = miny = 0;
		}

		imptr = Image_Map.GetImageMapPtr(realmap);
		nofx = imptr->w / width;						//RJS 05Feb98
														//RJS 05Feb98
		if (nofx)
		{
	 		stepy = frameno / nofx;							//RJS 05Feb98
			stepx = frameno - (stepy*nofx);					//RJS 05Feb98
														//RJS 05Feb98
			minx += stepx * width;							//RJS 05Feb98
			miny += stepy * height;							//RJS 05Feb98
			if (miny >= imptr->h)
				minx = miny = 0;
		}

		if (isphere_ptr->depthoffset && GlobalAdptr[isphere_ptr->depthoffset])
		{
			SLong	depth = GlobalAdptr[isphere_ptr->depthoffset];

			if (isphere_ptr->quadsphere)
			{
				if (oldGlobalAlpha != -1)
					current_screen->DoSetGlobalAlpha(oldGlobalAlpha);

	 			oldGlobalAlpha = current_screen->DoSetGlobalAlpha(depth);
			}

			current_screen->SetTransparency(SMOKED_SOLID - depth);

			depth = 255 - ((depth*255)/LUM_MAX);
			current_screen->SetLuminosity((SMOKED_SOLID - depth*255) >> 5);
		}
	}

	maxx = minx + width - 1;							//RJS 17Feb98
	maxy = miny + height;								//RJS 05Feb98

	if (!isphere_ptr->quadsphere)
	{
		if (isphere_ptr->angleoff)
		{
			angle = *((UWordP)&GlobalAdptr[isphere_ptr->angleoff]);
			SHAPE.imapspherespin(isphere_ptr->vertex,isphere_ptr->radius,realmap,
				minx,miny,maxx,maxy,angle);			//RJS 18Nov98
		}
		else
		{
			SHAPE.imapsphere(isphere_ptr->vertex,isphere_ptr->radius,realmap,
				minx,miny,maxx,maxy	);			//RJS 05Feb98
		}
	}
	else
	{
		SHAPE.imapsphereQuad(isphere_ptr->vertex,isphere_ptr->radius,realmap,
							minx,miny,maxx,maxy	);
	}

	if (oldGlobalAlpha != -1)
		current_screen->DoSetGlobalAlpha(oldGlobalAlpha);

	instr_ptr += sizeof(DOISPHERE);						//RJS 05Feb98
}

//DeadCode RJS 16Dec97 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RJS 16Dec97 //Procedure	dorealisphere
//DeadCode RJS 16Dec97 //------------------------------------------------------------------------------
//DeadCode RJS 16Dec97 //Author		Paul.   
//DeadCode RJS 16Dec97 //Date		Wed 16 Aug 1995
//DeadCode RJS 16Dec97 //Modified	Martin 16 Apr 1996	
//DeadCode RJS 16Dec97 //
//DeadCode RJS 16Dec97 //Description	
//DeadCode RJS 16Dec97 //
//DeadCode RJS 16Dec97 //Inputs	
//DeadCode RJS 16Dec97 //
//DeadCode RJS 16Dec97 //Returns	
//DeadCode RJS 16Dec97 //
//DeadCode RJS 16Dec97 //Externals
//DeadCode RJS 16Dec97 //------------------------------------------------------------------------------
//DeadCode RJS 16Dec97 //------------------------------------------------------------------------------
//DeadCode RJS 16Dec97  void shape::doosphere(UByte *& instr_ptr)
//DeadCode RJS 16Dec97 {
//DeadCode RJS 16Dec97 	DOOSPHERE_PTR osphere_ptr;
//DeadCode RJS 16Dec97 
//DeadCode RJS 16Dec97 	osphere_ptr = (DOOSPHERE_PTR )instr_ptr;
//DeadCode RJS 16Dec97 
//DeadCode RJS 16Dec97 	GREY3DTYPE	gtdt = (GREY3DTYPE )0;							//PD 21Jun96
//DeadCode RJS 16Dec97 
//DeadCode RJS 16Dec97 	SHAPE.omapsphere(osphere_ptr->vertex,osphere_ptr->radius,(ImageMapNumber )osphere_ptr->image,//PD 17Oct96
//DeadCode RJS 16Dec97 					osphere_ptr->minx,osphere_ptr->miny,osphere_ptr->maxx,osphere_ptr->maxy,osphere_ptr->width,osphere_ptr->height,
//DeadCode RJS 16Dec97 					osphere_ptr->factor,
//DeadCode RJS 16Dec97 					osphere_ptr->flagoffset);					//RJS 19Feb97
//DeadCode RJS 16Dec97 	
//DeadCode RJS 16Dec97 	instr_ptr += sizeof(DOOSPHERE);
//DeadCode RJS 16Dec97 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		dorealisphere
//Author		Robert Slater
//Date			Tue 16 Dec 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::dorealisphere(UByteP	&instr_ptr)
{
	DOREALISPHERE_PTR	ptr = (DOREALISPHERE_PTR) instr_ptr;	//RJS 14Jan98

	SHAPE.RealImapSphere(	ptr->vertex,
							ptr->radius,
							ptr->image,
							ptr->minix,
							ptr->miniy,
							ptr->maxix,
							ptr->maxiy,
							ptr->flagoffset,
							ptr->animfactor	);

	instr_ptr += sizeof(DOREALISPHERE);
}

//------------------------------------------------------------------------------
//Procedure	docreaterpoly
//------------------------------------------------------------------------------
//Author		Martin.   
//Date			Mon 19 Feb 1996
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
 void shape::docreaterpoly(UByte *& instr_ptr)
{
	DOCREATERPOLY_PTR	ptr = (DOCREATERPOLY_PTR)instr_ptr;				//RJS 13Aug98
	SWord				relimage = ptr->imagemap;						//RJS 13Aug98
	SWord				offset = GlobalAdptr[ptr->animoff];
	SWord				scaleoffset = offset / ptr->animscale;

	relimage += scaleoffset;											//RJS 13Aug98

	if (IsAircraft && (current_level>=2))
	{
		ImageMapDescPtr imap=Image_Map.GetImageMapPtr((ImageMapNumber)relimage);
		ULong			ydelta = offset - (scaleoffset * ptr->animscale);
		UByteP			body = imap->body;
		
		if (ydelta)
		{
			ydelta *= (imap->h / ptr->animscale);
			body += (imap->w * ydelta);
		}

		shape::colour=Colour(*body);
		current_screen->SetColour(shape::colour);
		POLYGON.createpoly(shape::colour);
	}
	else 
		POLYGON.createpoly((ImageMapNumber) relimage);						//RJS 13Aug98

	instr_ptr += sizeof(DOCREATERPOLY);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dodrawipolys
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
 void shape::dodrawipolys(UByte *& )								//PD 29Nov95
{
//	POLYGON.SetSubDivide(TRUE);									//PD 13Feb96
	POLYGON.drawpoly();											//PD 13Feb96
//	POLYGON.SetSubDivide(FALSE);								//PD 13Feb96
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	domappoly
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
 void shape::domappoly(UByte *& )								//PD 29Nov95
{
	_Error.EmitSysErr(__FILE__":Not a real instruction (DOMAPPOLY)\n");
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dosetmapmap
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
 void shape::dosetmapmap(UByte *& )								//PD 29Nov95
{
	_Error.EmitSysErr(__FILE__":Not a real instruction (DOMAPPOLY)\n");
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	do3dbreak
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
 void shape::do3dbreak(UByte *& )								//PD 29Nov95
{
	_Error.EmitSysErr(__FILE__":Not a real instruction (DOMAPPOLY)\n");
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	docylinder
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
 void shape::docylinder(UByte *& instr_ptr)
{
	DOCYLINDER_PTR	ptr = (DOCYLINDER_PTR )instr_ptr;

	SHAPE.plaincylinder(ptr->point0,ptr->point1,ptr->radius);

	instr_ptr += sizeof(DOCYLINDER);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dontpoints
//LastModified:	PD 25Jul96
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	Martin 8Nov1995	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
 void shape::dontpoints(UByte *& instr_ptr)
{
	DONTPOINTS_PTR ntp_ptr;
	
	ntp_ptr = (DONTPOINTS_PTR )instr_ptr;

	NEXTT_PTR next_ptr;

	next_ptr = (NEXTT_PTR )(instr_ptr + sizeof(DONTPOINTS));

	//Generate a temporary transformation matrix to rotate the prop( or whatever else it is)

	FPMATRIX		tmat;

	FPMATRIX_PTR	tmatp = &tmat;

	UWord			rpm;										//RJS 02Sep97

	ANGLES	h,p,r;

	h =	p = r = ANGLES_0Deg;									//RJS 03Sep97

	SLong	roll_angle;											//PD 08Mar96

	// RPM value is a 16-bit ROWAN angle
	if (ntp_ptr->flag)											//RJS 02Sep97
	{															//RJS 02Sep97
//Dead		animptr adptr = GlobalAdptr;							//RJS 22Apr99	
		if (ntp_ptr->isWord)									//RJS 06Oct98
		{
			UWordP	adptr2 = (UWordP) &GlobalAdptr[ntp_ptr->flag];	//RJS 22Apr99
			rpm = *adptr2;											//RJS 03Sep97
		}
		else
			rpm = GlobalAdptr[ntp_ptr->flag] * 257;//To ROWAN...		//RJS 06Oct98
	}															//RJS 02Sep97
	else														//RJS 02Sep97
		rpm = ntp_ptr->fixedrpm;								//RJS 03Sep97

//DeadCode DAW 13Nov97 	r = (Angles)roll_angle;									//PD 08Mar96
	if (rpm)
	{
//DeadCode RJS 03Sep97 		roll_angle = (ANGLES_359Deg * rpm)/60;						//PD 08Mar96
//DeadCode RJS 03Sep97 		roll_angle *= globalanimtime.centisec;						//PD 02Apr96
//DeadCode RJS 03Sep97 		roll_angle /= -10;											//PD 02Apr96

		if (!ntp_ptr->notrpm)									//RJS 03Sep97
		{														//RJS 03Sep97
			roll_angle = (ANGLES_359Deg * rpm)/120;				//RJS 16Feb99
			roll_angle *= globalanimtime.centisec;				//RJS 03Sep97
 			roll_angle /= 1000;									//RJS 03Sep97slowitdown
		}														//RJS 03Sep97
		else													//RJS 03Sep97
			roll_angle = rpm;									//RJS 03Sep97

		switch (ntp_ptr->hpr_data)									//RJS 03Sep97
		{															//RJS 03Sep97
			case 1:													//RJS 03Sep97
				h = (Angles )roll_angle;							//PD 13Nov97
				break;												//RJS 03Sep97
			case 2:													//RJS 03Sep97
				p = (Angles )roll_angle;							//PD 13Nov97
				break;												//RJS 03Sep97
			case 4:													//RJS 03Sep97
				r = (Angles )roll_angle;							//PD 13Nov97
				break;												//RJS 03Sep97
		}															//RJS 03Sep97
	}

	_matrix.generate2(h,p,r,tmatp);								//PD 25Jul96

	SWord	vertex = ntp_ptr->start_vertex;						//RJS 10Mar97

	SLong	basex,basey,basez;		//origin to rotate around

	basex = ntp_ptr->base_x;						//PD 08Mar96
	basey = ntp_ptr->base_y;						//PD 08Mar96
	basez = ntp_ptr->base_z;						//PD 08Mar96
//DeadCode PD 05Oct98 	basex = ntp_ptr->base_x<<shapescale;						//PD 08Mar96
//DeadCode PD 05Oct98 	basey = ntp_ptr->base_y<<shapescale;						//PD 08Mar96
//DeadCode PD 05Oct98 	basez = ntp_ptr->base_z<<shapescale;						//PD 08Mar96

	int	j = (int )ntp_ptr->count;

	while(j--)
	{
		IFShare	wx,wy,wz;

		wx.i = (next_ptr->xcoord)-basex;
		wy.i = (next_ptr->ycoord)-basey;
		wz.i = (next_ptr->zcoord)-basez;
//DeadCode PD 05Oct98 		wx.i = (next_ptr->xcoord<<shapescale)-basex;
//DeadCode PD 05Oct98 		wy.i = (next_ptr->ycoord<<shapescale)-basey;
//DeadCode PD 05Oct98 		wz.i = (next_ptr->zcoord<<shapescale)-basez;
		
		//Transform the point around the selected origin

		_matrix.transform(tmatp,wx,wy,wz);

		//Scale back to cm units and add the base coordinates back on//PD 08Mar96

		wx.i = (SLong)wx.f;
		wy.i = (SLong)wy.f;
		wz.i = (SLong)wz.f;

		wx.i += basex; wy.i += basey; wz.i += basez;

		_matrix.transformNC(fpobject_matrix,wx,wy,wz);

		newco[vertex].bodyx.f = wx.f + object_obj3d->Body.X.f;
		newco[vertex].bodyy.f = wy.f + object_obj3d->Body.Y.f;
		newco[vertex].bodyz.f = wz.f + object_obj3d->Body.Z.f;
		_matrix.SetClipFlags(newco[vertex]);
//		if (!doingHW3D) _matrix.body2screen(newco[vertex]);		//RJS 27Aug98
		newco[vertex].intensity = -1;//0;//-1;							//RJS 20Mar98
		newco[vertex].specFlip=
		newco[vertex++].specular=-1;							//RJS 27Aug98

		next_ptr++;
	}

	instr_ptr += ntp_ptr->count * sizeof(NEXTT) + sizeof(DONTPOINTS);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dosetmapoff
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
 void shape::dosetmapoff(UByte *& )								//PD 29Nov95
{
	//Empty
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dosetmappingplaner
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
 void shape::dosetmappingplaner(UByte *& )						//PD 29Nov95
{
	//Empty
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dosetmappingtan
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
 void shape::dosetmappingtan(UByte *& )							//PD 29Nov95
{
	//Empty
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dosmktrail
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	
//
//Description			Draws an image-mapped trail of cylinders from a list
//				of points.  The trail is transparent if you are looking upwards
//			 	towards the sky, or if you are above the clouds....
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
 void shape::dosmktrail(UByte *& instr_ptr)						//RJS 20Sep96
{
	ULongP			lo3dptr = (ULongP) &object_obj3d->AngH;
	Obj3DPtr		lastobj3d = (Obj3DPtr) (*lo3dptr);
	VapAnimDatPtr	vapptr = (VapAnimDatPtr) &object_obj3d->AngR;
											
	if (lastobj3d && vapptr->drawit && !Three_Dee.shapecheat)	//RJS 15Apr98
	{
		if (	(object_obj3d->objtype == SMOKE_OBJECT)			//DAW 18Aug99
			&&	(lastobj3d->objtype == SMOKE_OBJECT)	)		//DAW 18Aug99
		{
			DOSMKTRAIL_PTR	ptr = (DOSMKTRAIL_PTR) instr_ptr;
			Coords3DList*	adptr = (Coords3DList*) object_obj3d->AnimPtr;
			Coords3DList*	lastadptr = (Coords3DList*) lastobj3d->AnimPtr;
			VapAnimDatPtr	oldvapptr = (VapAnimDatPtr) &lastobj3d->AngR;
 			SWord	fadetype = vapptr->depth;
			UWord	radius = adptr->radius;							//RJS 15Apr98
			UWord	oldrad = lastadptr->radius;						//RJS 15Apr98
			SLong	realdist;
			UByteP	tmpinstptr;
			SWord	xoff0;
			SWord	yoff0;
			SWord	xoff1 = adptr->xdelta;
			SWord	yoff1 = adptr->ydelta;
			MyGroundVectorPtr	WCylStartP = NULL;					
			MyGroundVectorPtr	WCylEndP = NULL;					
			ULong	avdist, avrad;
			SLong	pixpercyl;
			SLong	dx, dy, dz;
			SWord	MaxRadius, Degrade;
 			SWord	ThisDepth = (ptr->MaxTransparency * 255)>>2;	//RJS 27Mar98
			UWord	FrameNo;
			SWord	minx, miny;
			SWord	MaxDepth = 64;
			ImageMapNumber	theImap;
			ImageMapNumber	theImap2;
			SWord	minx2,miny2,maxx2,maxy2;
			SWord	realfade = fadetype;
			SLong	fadetime = adptr->LifeTime - adptr->FadeTime;
			SLong	lifegone = adptr->LifeTime - adptr->lifeleft;
			SWord	oldGlobalAlpha = -1;
			UWord	noframes = ptr->noframes - 1;
			Bool	nocyl = FALSE;

	//DeadCode DAW 21Jun99 #ifndef NDEBUG
	//DeadCode DAW 21Jun99 		if (!radius || !fadetime)
	//DeadCode DAW 21Jun99 			INT3;
	//DeadCode DAW 21Jun99 #endif
			if (radius && fadetime>0)									//RJS 09Jul99
			{
				if (lifegone > adptr->FadeTime)
				{
					lifegone -= adptr->FadeTime;
					if (lifegone<0) lifegone=0;
					realfade = (lifegone * fadetype)/fadetime;
					realfade = fadetype - realfade;
					if (realfade < 0)
						realfade = 0;

					if (realfade > 255)
						realfade = 255;

					oldGlobalAlpha = current_screen->DoSetGlobalAlpha(realfade);
					ThisDepth = realfade;

					FrameNo = noframes*lifegone;
					FrameNo /= fadetime;
				}
				else
				{
					if (lifegone < 0)							//DAW 27Sep99
						lifegone=0;								//DAW 27Sep99

					ThisDepth = fadetype;								//MS 10Dec98
					oldGlobalAlpha = current_screen->DoSetGlobalAlpha(ThisDepth);//RJS 10Dec98
					if (ptr->frametime)
					{
						UWord	framepoo = lifegone / ptr->frametime;
						ULong	frametot = framepoo * ptr->frametime;

						FrameNo = ((lifegone - frametot)*noframes)/ptr->frametime;
					}
					else
						FrameNo = 0;
				}

				Float	fxoff,fyoff;									//RJS 03Dec98
																		//RJS 03Dec98
				if (oldvapptr->drawit)									//RJS 15Apr98
				{
					xoff0 = lastadptr->xdelta;
					yoff0 = lastadptr->ydelta;
				}
				else
				{
					MaxDepth = 96;
					xoff0 = (xoff1 * oldrad)/radius;					//RJS 03Dec98
					yoff0 = (yoff1 * oldrad)/radius;					//RJS 03Dec98
				}

				fxoff = xoff1;											//RJS 03Dec98
				fxoff *= SHAPE.SphereXScale;							//RJS 03Dec98
																		//RJS 03Dec98
				fyoff = yoff1;											//RJS 03Dec98
				fyoff *= SHAPE.SphereYScale;							//RJS 03Dec98
																		//RJS 03Dec98
				xoff1 = SWord(fxoff);									//RJS 03Dec98
				yoff1 = SWord(fyoff);									//RJS 03Dec98

				fxoff = xoff0;											//RJS 03Dec98
				fxoff *= SHAPE.SphereXScale;							//RJS 03Dec98
																		//RJS 03Dec98
				fyoff = yoff0;											//RJS 03Dec98
				fyoff *= SHAPE.SphereYScale;							//RJS 03Dec98
																		//RJS 03Dec98
				xoff0 = SWord(fxoff);									//RJS 03Dec98
				yoff0 = SWord(fyoff);									//RJS 03Dec98

				if (	((xoff1 < 0) && (xoff0 > 0))
					||	((xoff1 > 0) && (xoff0 < 0))	)
					xoff0 = -xoff0;

				if (	((yoff1 < 0) && (yoff0 > 0))
					||	((yoff1 > 0) && (yoff0 < 0))	)
					yoff0 = -yoff0;

				WCylStartP = &lastadptr->trailpoint;					
				WCylEndP = &adptr->trailpoint;							

				newco[0].bodyx.f = lastobj3d->Body.X.f;
				newco[0].bodyy.f = lastobj3d->Body.Y.f;
				newco[0].bodyz.f = lastobj3d->Body.Z.f;

				newco[1].bodyx.f = object_obj3d->Body.X.f;
				newco[1].bodyy.f = object_obj3d->Body.Y.f;
				newco[1].bodyz.f = object_obj3d->Body.Z.f;

				// if it is clipped... distance is different
				SLong	rz0 = newco[0].bodyz.f;							//RJS 06Dec98
				SLong	rz1 = newco[1].bodyz.f;							//RJS 06Dec98
																		//RJS 06Dec98
				if (rz0 < 1)											//RJS 06Dec98
					rz0 = 1;											//RJS 06Dec98
																		//RJS 06Dec98
				if (rz1 < 1)											//RJS 06Dec98
					rz1 = 1;											//RJS 06Dec98
																		//RJS 06Dec98
				realdist = (rz0 + rz1)>>1;								//RJS 06Dec98

				if (realdist < ptr->FadeDist)
				{
					DoPointStruc	dpoint0,dpoint1;
					SLong			opp , adj;
					SLong			prad0,prad1;

					dpoint0 = newco[0];
					dpoint1 = newco[1];

					minx = 0;
					miny = 0;

					_matrix.body2screen(newco[0]);
					_matrix.body2screen(newco[1]);

					opp = (newco[1].screeny.f - newco[0].screeny.f)/current_screen->virtualYscale;
					adj = (newco[1].screenx.f - newco[0].screenx.f)/current_screen->virtualXscale;

					dpoint0.bodyx.f += oldrad;
					dpoint1.bodyx.f += radius;

					_matrix.body2screen(dpoint0);
					_matrix.body2screen(dpoint1);

					prad1 = (dpoint1.screenx.f - newco[1].screenx.f)/current_screen->virtualXscale;
					prad0 = (dpoint0.screenx.f - newco[0].screenx.f)/current_screen->virtualXscale;

					avrad = (prad1+prad0)>>1;
					if (!avrad)
						avrad = 1;

					opp = (opp<0)?-opp:opp;
					adj = (adj<0)?-adj:adj;

					avdist = (3*(opp+adj))>>2;
					if (!avdist)
						avdist = 1;

		//DeadCode RJS 24Nov98 			fadetype = SMOKED_SOLID - fadetype;
		//DeadCode RJS 24Nov98 			ThisDepth -= fadetype;
		//DeadCode RJS 24Nov98 			if (ThisDepth < SMOKED_LIGHT)
		//DeadCode RJS 24Nov98 			{
		//DeadCode RJS 24Nov98 				Degrade = ((SMOKED_LIGHT - ThisDepth) / 63)+1;	//RJS 27Mar98
		//DeadCode RJS 24Nov98 				ThisDepth = SMOKED_LIGHT;
		//DeadCode RJS 24Nov98 				avdist /= Degrade;
		//DeadCode RJS 24Nov98 			}

					theImap = (ImageMapNumber) ptr->Imagemap;
					theImap2 = (ImageMapNumber) ptr->Imagemap2;
					if (theImap)							//RJS 29Jun99
					{
						ImageMapDescPtr imptr;
						SLong			nofx;
						SLong			stepy, stepx;

						if (theImap2)
						{
							imptr = Image_Map.GetImageMapPtr(theImap2);

							nofx = imptr->w / ptr->width2;
							stepy = FrameNo / nofx;
							stepx = FrameNo - (stepy*nofx);

							minx2 = ptr->minix2;
							miny2 = ptr->miniy2;

							minx2 += stepx*ptr->width2;
							miny2 += stepy*ptr->height2;

							maxx2 = minx2 + ptr->width2;
							maxy2 = miny2 + ptr->height2;
						}

						if (ptr->framelimit && (FrameNo >= ptr->framelimit))
						{
							SWord	framefrac = FrameNo / ptr->framelimit;
							SWord	framestep = framefrac * ptr->framelimit;

							FrameNo -= framestep;

							minx = 0;
							miny = 0;

							theImap = (ImageMapNumber) (ptr->Imagemap + framefrac);
						}
						else
						{
							minx = ptr->MinIx;
							miny = ptr->MinIy;
						}

						imptr = Image_Map.GetImageMapPtr(theImap);

						nofx = imptr->w / ptr->Width;
						stepy = FrameNo / nofx;
						stepx = FrameNo - (stepy*nofx);

						minx += stepx*ptr->Width;
						miny += stepy*ptr->Height;
					}

					switch (ptr->TrailType)
					{
						case SMK_SCATTER:
						{
							MaxRadius = (7*oldrad)>>3;

							pixpercyl = (avdist * avrad)>>5;
							pixpercyl += 8;

 							if (pixpercyl > MaxDepth)								//RJS 31Mar98
 								pixpercyl = MaxDepth;								//RJS 31Mar98

							pixpercyl = (pixpercyl * ThisDepth)/100;
							pixpercyl = (pixpercyl*ptr->Density)>>7;

		//DeadCode RJS 29Jun99 					if (doingHW3D)								//PD 19Jun98
	 							SHAPE.ParticleCylinderImapd(0,1,
 															xoff0,yoff0,
 															xoff1,yoff1,
 															pixpercyl,MaxRadius,
 															WCylStartP, WCylEndP,
 															ptr->Imagemap,
															minx,miny,
 															ptr->Width, ptr->Height,
		 													ThisDepth);
		//DeadCode DAW 30Jun99 					else
		//DeadCode DAW 30Jun99 						SHAPE.ParticleCylinderPlain(0,1,
		//DeadCode DAW 30Jun99  													xoff0,yoff0,
		//DeadCode DAW 30Jun99  													xoff1,yoff1,
		//DeadCode DAW 30Jun99  													pixpercyl,MaxRadius,
		//DeadCode DAW 30Jun99  													WCylStartP, WCylEndP,
		//DeadCode DAW 30Jun99 													ptr->Colour,
		//DeadCode DAW 30Jun99 		 											ThisDepth);
						}
						break;
						case SMK_STREAM:
						{
		//DeadCode MS 10Dec98 					SLong	realdist2 = ptr->FadeDist - realdist;
		//DeadCode MS 10Dec98 					pixpercyl = (avdist<<2)/avrad;
		//DeadCode MS 10Dec98 					pixpercyl = 4 + ((realdist2*pixpercyl)/ptr->FadeDist);
		//DeadCode MS 10Dec98 
		//DeadCode MS 10Dec98 					if (pixpercyl > 48)
		//DeadCode MS 10Dec98 						pixpercyl = 48;
		//DeadCode MS 10Dec98 
		//DeadCode MS 10Dec98 					pixpercyl = (pixpercyl*ptr->Density)>>7;

							SLong	realdist2 = (realdist << 7) / 7500;	//MS 10Dec98
							if (realdist2 <= 0)
								realdist2 = 128;

							if (realdist2 > 65535)
								realdist2 = 65535;
		//DeadCode RJS 29Jun99 #pragma message (__HERE__ "ROB - Unitialised Variable pixpercyl - still there...")
		//DeadCode RJS 29Jun99 //					if (doingHW3D)								//PD 19Jun98
								SHAPE.ParticleStreamImapd(	0,1,
															xoff0,yoff0,
															xoff1,yoff1,
															UWord(realdist2),	//RJS 10Dec98
															oldrad,
															radius,
															WCylStartP, WCylEndP,
															ptr->Imagemap,
															minx,miny,
															ptr->Width, ptr->Height,
															ThisDepth);
		//DeadCode DAW 30Jun99 //					else
		//DeadCode DAW 30Jun99 //						SHAPE.ParticleStreamPlain(	0,1,
		//DeadCode DAW 30Jun99 //													xoff0,yoff0,
		//DeadCode DAW 30Jun99 //													xoff1,yoff1,
		//DeadCode DAW 30Jun99 //													pixpercyl,
		//DeadCode DAW 30Jun99 //													oldrad,
		//DeadCode DAW 30Jun99 //													radius,
		//DeadCode DAW 30Jun99 //													WCylStartP, WCylEndP,
		//DeadCode DAW 30Jun99 //													ptr->Colour,
		//DeadCode DAW 30Jun99 //													ThisDepth);
						}
						break;
						case SMK_CLUSTER:
						{
							SHAPE.FixedPolyOnFloor(adptr,
										   		lastadptr,
										   		xoff0,yoff0,
										   		xoff1,yoff1,
										   		theImap,
										   		minx,miny,
										   		ptr->Width,miny+ptr->Height);
						}
						break;
						case SMK_HEAVY_STREAM:
						{
							if (realdist < 3000)
							{
								MaxRadius = (7*oldrad)>>3;

								pixpercyl = ThisDepth * ptr->Density;

		//DeadCode RJS 29Jun99 						if (doingHW3D)								//PD 19Jun98
	 								SHAPE.ParticleCylinderImapd(0,1,
 																xoff0,yoff0,
 																xoff1,yoff1,
 																pixpercyl,MaxRadius,
 																WCylStartP, WCylEndP,
 																theImap2,
																minx2,miny2,
 																maxx2 - minx2,maxy2-miny2,
		 														ThisDepth);
		//DeadCode DAW 30Jun99 						else
		//DeadCode DAW 30Jun99 							SHAPE.ParticleCylinderPlain(0,1,
		//DeadCode DAW 30Jun99  														xoff0,yoff0,
		//DeadCode DAW 30Jun99  														xoff1,yoff1,
		//DeadCode DAW 30Jun99  														pixpercyl,MaxRadius,
		//DeadCode DAW 30Jun99  														WCylStartP, WCylEndP,
		//DeadCode DAW 30Jun99 														ptr->Colour,
		//DeadCode DAW 30Jun99 		 												ThisDepth);
							}
							else
							{
		//						if (theImap2)								//RJS 21Jan99
		//							imapsphere(0,radius,theImap2,minix2,miniy2,maxix2,maxiy2);

								SHAPE.imaptrailcylWrapped(	0,						
  															1,				
  															theImap,
															radius,
  															theImap2,
  	 	 													miny,miny+ptr->Height,			
		  													xoff0, yoff0,	
  															xoff1, yoff1,
															minx2,miny2,
															maxx2,maxy2,
															nocyl);
							}
						}
						break;
						case SMK_LINES:
						{
							pixpercyl = (32 * ptr->Density)>>7;

							SHAPE.LineStream(	0,1,
												xoff0,yoff0,
												xoff1,yoff1,
												pixpercyl,
												oldrad,
												radius,
												WCylStartP, WCylEndP,
												ptr->Colour,
												ThisDepth);
						}
						break;
						case SMK_FISHPOO:
						{
							SHAPE.imaptrailcylWrapped(	0,						
  														1,				
  														theImap,
														radius,
  														theImap2,
  	 	 												miny,miny+ptr->Height,			
		  												xoff0, yoff0,	
  														xoff1, yoff1,
														minx2,miny2,
														maxx2,maxy2,
														nocyl);

						}
						break;
						case SMK_TRACER:
						break;
					}
				}
				else
				{
					if (ptr->Colour)									//MS 10Dec98
					{
						DOLINE	tmpinst2;									//RJS 24Nov97
						DOSETCOLOUR256	tmpinst3;							//RJS 24Nov97
																			//RJS 24Nov97
						tmpinst3.basecolour = ptr->Colour<<1;				//RJS 24Nov97
						tmpinst3.spread = 0;								//RJS 24Nov97
						tmpinst3.imap = 0xFF;
																			//RJS 24Nov97
						tmpinstptr = (UByteP) &tmpinst3;					//RJS 24Nov97
						dosetcolour256(tmpinstptr);							//RJS 24Nov97
																			//RJS 24Nov97
						tmpinst2.start_vertex = 0;							//RJS 24Nov97
						tmpinst2.end_vertex = 1;							//RJS 24Nov97
																			//RJS 24Nov97
						tmpinstptr = (UByteP) &tmpinst2;					//RJS 24Nov97

 						_matrix.SetClipFlags(newco[0]);						//RJS 27Nov98
 						_matrix.SetClipFlags(newco[1]);						//RJS 27Nov98
																		//MS 10Dec98
						doline(tmpinstptr);								//MS 10Dec98
					}													//MS 10Dec98
				}														//RJS 24Nov97

				if (oldGlobalAlpha != -1)
					current_screen->DoSetGlobalAlpha(oldGlobalAlpha);
			}
		}
	}

	instr_ptr += sizeof(DOSMKTRAIL);
}

// SUN MOVED HERE BECAUSE bOldZState used.
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SunItemAnim
//Author		Paul.   
//Date			Mon 24 Jun 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::SunItemAnim(SunAnimData* adptr)
{
	if (!Three_Dee.lightson)									//RJS 03Jun99
	{
		Float	sunXpos,											//PD 24Jun96
				sunYpos;											//PD 24Jun96
		Float	abssunXpos,											//PD 24Jun96
				abssunYpos;

		bool fHardware=current_screen->DoingHardware3D()?true:false;

		adptr->wasdrawn=TRUE;

		//Now, use object_obj3d to fill in the suns screen x and y
		//coordinates used to detect white outs

		if (object_obj3d->Body.Z.f > 1.0)
		{
 			//Use body2screen to generate the correct screen 
 			//coordinates
 
 			DoPointStruc	dps,dps2;
			Float			disx, disy;
 
 			dps.bodyx.f=object_obj3d->Body.X.f;						//RJS 26Feb97
 			dps.bodyy.f=object_obj3d->Body.Y.f;						//RJS 26Feb97
 			dps.bodyz.f=object_obj3d->Body.Z.f;						//RJS 26Feb97
 
			if (fHardware)
			{
				DoPointStruc tdps=dps;
				current_screen->DoBody2Screen(tdps);				//PD 27Nov98
				current_screen->DoSetSunPos(tdps);					//PD 27Nov98
			}

 			_matrix.body2screen(dps);								//PD 27Nov98
 
			sunXpos = dps.screenx.f;
			sunYpos = dps.screeny.f;

 			abssunXpos = sunXpos<0?-sunXpos:sunXpos;
 			abssunYpos = sunYpos<0?-sunYpos:sunYpos;

			disx = (abssunXpos*10)/current_screen->VirtualWidth;
			disy = (abssunYpos*10)/current_screen->VirtualHeight;

			if (	(disx > 5.0) || (disy > 5.0)
				|| ((disx < 0.1) && (disy < 0.1))	)	
				return;

			if (View_Point && !View_Point->PolyPitEnabled())
			{
	//DeadCode PD 12Feb99 			Bool oldState=current_screen->DoSetZUpdate(FALSE);	//PD 25Nov98

				int	i;
				Float	dx, dy, dz;
				Float	dx2, dy2, dz2;
				Float	bdz;
	//			int		fade = (disx + disy)/2;
				int		fade = disx + disy;

				bdz = 100;

				dx = object_obj3d->Body.X.f / 10000;
				dy = object_obj3d->Body.Y.f / 10000;
				dz = (object_obj3d->Body.Z.f-bdz) / 10000;

				dps.bodyx.f = -dx;
				dps.bodyy.f = -dy;
				dps.bodyz.f = bdz - dz;

				dx *= .5;//2.0;
				dy *= .5;//2.0;
				dz *= .5;//2.0;

				dx2 = dx * 0.1;// 10.0;
				dy2 = dy * 0.1;// 10.0;
				dz2 = dz * 0.1;/// 10.0;

	//			if (fade > LUM_MAX)
	//				fade = LUM_MAX;

				if (fHardware)										//PD 25Nov98
				{
					fade *= 255;
					fade /= 10;
					fade = 255 - fade;
					for (i=0; i < 10; i++)
					{
						switch (i)
						{
						case 0:
							//White...
							Three_Dee.AddLensObject(&dps,LNHALS,0,fade);
							dps.bodyx.f += dx2;	
							dps.bodyy.f += dy2;
							dps.bodyz.f += dz2;
							break;
						case 1:
							//Blue-indigo....
							Three_Dee.AddLensObject(&dps,LNHALB,0,fade);
							dps.bodyx.f += dx2;	
							dps.bodyy.f += dy2;
							dps.bodyz.f += dz2;
							break;
						case 2:
							//Red....
							Three_Dee.AddLensObject(&dps,DUMMY5,0,fade);
							dps.bodyx.f += dx2;	
							dps.bodyy.f += dy2;
							dps.bodyz.f += dz2;
							break;
						case 3:
							//Blue....
							Three_Dee.AddLensObject(&dps,LNSOLS,0,fade);
							dps.bodyx.f += dx;	
							dps.bodyy.f += dy;
							dps.bodyz.f += dz;
							break;
						case 4:
							//White...
							Three_Dee.AddLensObject(&dps,DUMMY4,0,fade);
							dps.bodyx.f += (dx/2.0);	
							dps.bodyy.f += (dy/2.0);
							dps.bodyz.f += (dz/2.0);
							break;
						case 5:
							//Red.....
							Three_Dee.AddLensObject(&dps,LNSOLS,0,fade);
							dps.bodyx.f += (dx/2.0);	
							dps.bodyy.f += (dy/2.0);
							dps.bodyz.f += (dz/2.0);
							break;
						case 6:
							//Orange-yellow
							Three_Dee.AddLensObject(&dps,DUMMY5,0,fade);
							dps.bodyx.f += dx*2;	
							dps.bodyy.f += dy*2;
							dps.bodyz.f += dz*2;
							break;
						case 7:
							//Blue...
							Three_Dee.AddLensObject(&dps,DUMMY5,0,fade);
							dps.bodyx.f += dx*2;	
							dps.bodyy.f += dy*2;
							dps.bodyz.f += dz*2;
							break;
						case 8:
							//More red...
							Three_Dee.AddLensObject(&dps,DUMMY5,0,fade);
							dps.bodyx.f += dx*2;	
							dps.bodyy.f += dy*2;
							dps.bodyz.f += dz*2;
							break;
						}
					}
				}
				else
				{
					if (fade > LUM_MAX)
						fade = LUM_MAX;

					fade /= 2;
					for (i=0; i < 10; i++)
					{
						switch (i)
						{
						case 0:
							Three_Dee.AddLensObject(&dps,LNHALS,15,fade);
							dps.bodyx.f += dx2;	
							dps.bodyy.f += dy2;
							dps.bodyz.f += dz2;
							break;
						case 1:
							Three_Dee.AddLensObject(&dps,LNHALB,13,fade);
							dps.bodyx.f += dx2;	
							dps.bodyy.f += dy2;
							dps.bodyz.f += dz2;
							break;
						case 2:
							Three_Dee.AddLensObject(&dps,DUMMY5,4,fade);
							dps.bodyx.f += dx2;	
							dps.bodyy.f += dy2;
							dps.bodyz.f += dz2;
							break;
						case 3:
							Three_Dee.AddLensObject(&dps,LNSOLS,13,fade);
							dps.bodyx.f += dx;	
							dps.bodyy.f += dy;
							dps.bodyz.f += dz;
							break;
						case 4:
							Three_Dee.AddLensObject(&dps,DUMMY4,15,fade);
							dps.bodyx.f += (dx/2.0);	
							dps.bodyy.f += (dy/2.0);
							dps.bodyz.f += (dz/2.0);
							break;
						case 5:
							Three_Dee.AddLensObject(&dps,LNSOLS,4,fade);
							dps.bodyx.f += (dx/2.0);	
							dps.bodyy.f += (dy/2.0);
							dps.bodyz.f += (dz/2.0);
							break;
						case 6:
							Three_Dee.AddLensObject(&dps,DUMMY5,8,fade);
							dps.bodyx.f += dx*2;	
							dps.bodyy.f += dy*2;
							dps.bodyz.f += dz*2;
							break;
						case 7:
							Three_Dee.AddLensObject(&dps,DUMMY5,13,fade);
							dps.bodyx.f += dx*2;	
							dps.bodyy.f += dy*2;
							dps.bodyz.f += dz*2;
							break;
						case 8:
							Three_Dee.AddLensObject(&dps,DUMMY5,3,fade);
							dps.bodyx.f += dx*2;	
							dps.bodyy.f += dy*2;
							dps.bodyz.f += dz*2;
							break;
						}
					}
				}
	//DeadCode PD 12Feb99 			current_screen->DoSetZUpdate(oldState);				//PD 25Nov98
			}

 			//Generate the dimensions of a box of screen area
 			//and test to see if the sun lies inside it.
 
 			const Float VIRTUALBOXSIZE = PIXEL640 * 64;				//PD 04Dec96
 
 			if (abssunXpos<=VIRTUALBOXSIZE && abssunYpos<=VIRTUALBOXSIZE)
 			{
 				SunInVision = TRUE;
 			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dooffsetpnt
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
 void shape::dooffsetpnt(UByte *& instr_ptr)
{
	instr_ptr += sizeof(DOOFFSETPNT);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	doicylinder
//------------------------------------------------------------------------------
//Author		Paul.
//Date		Wed 16 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
 void shape::doicylinder(UByte *& instr_ptr)
{
	DOICYLINDER_PTR ptr= (DOICYLINDER_PTR )instr_ptr;
//DeadCode RJS 21Apr99 	UByteP	adptr = (UByteP) object_obj3d->AnimPtr;
	UWord	frameno = 0;
	ImageMapNumber	imap;
	UByte			fadedepth = GlobalAdptr[ptr->fadeoff];		//RJS 16Apr99
	SWord			oldGlobalAlpha = -1;						//RJS 27Nov98

	if (ptr->fadeoff && (fadedepth < 255))						//RJS 27Nov98
		oldGlobalAlpha = current_screen->DoSetGlobalAlpha(fadedepth);//RJS 27Nov98

	if (ptr->flagoffset)
	{
		frameno = GlobalAdptr[ptr->flagoffset] / ptr->factor;
		if (ptr->image2 && (frameno >= ptr->framelimit))
		{
			frameno -= ptr->framelimit;
			imap = (ImageMapNumber) ptr->image2;
		}
		else
			imap = (ImageMapNumber) ptr->image;
	}
	else
		imap = (ImageMapNumber) ptr->image;

	SHAPE.imapcylinder(	ptr->point0,
						ptr->point1,
						ptr->radius,
						imap,
					   	ptr->min_ix,ptr->min_iy,
					  	ptr->width,ptr->height,
						frameno,
						0	);   // trans depth					//RJS 20Nov98

	if (oldGlobalAlpha > -1)									//RJS 27Nov98
		current_screen->DoSetGlobalAlpha(oldGlobalAlpha);		//RJS 27Nov98

	instr_ptr += sizeof(DOICYLINDER);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		drawbetween
//LastModified:	PD 07May96
//Author		Martin Alderton
//Date			Tue 28 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void shape::drawbetween(UByte *& instr_ptr)
{
	DRAWBETWEEN_PTR ptr;

	ptr = (DRAWBETWEEN_PTR) instr_ptr;

	SLong dist;													//PD 07May96

 	dist = (SLong)object_obj3d->Body.Z.f;

//DeadCode CSB 21/01/99	#ifndef NDEBUG													//RJS 02Nov98
//DeadCode CSB 21/01/99		if (object_obj3d->ItemPtr == Manual_Pilot.ControlledAC2)
//DeadCode CSB 21/01/99		{
//DeadCode CSB 21/01/99			char	shite[32];
//DeadCode CSB 21/01/99			sprintf(shite,"Dist : %d  ",dist);
//DeadCode CSB 21/01/99			Mono_Text.PrintAt(55,6,(UByteP)shite);
//DeadCode CSB 21/01/99		}
//DeadCode CSB 21/01/99	#endif

//	dist *= DistScale;
//	dist >>= 8;

	dist=SLong(Float(dist)*DistScale);

	if ((dist >= ptr->mindist)&& (dist < ptr->maxdist))
	{
//		if (!IsSubShape) current_level++;
		instr_ptr += (UWord )ptr->offset;						//RJS 19Mar97
	}
	else
	{
		if (!IsSubShape) current_level++;
		instr_ptr += sizeof(DRAWBETWEEN);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		dolauncher
//Author		Paul.   
//Date			Wed 10 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void shape::dolauncher(UByte *& instr_ptr)
{
	instr_ptr += sizeof(DOLAUNCHER);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		dodial
//Author		Robert Slater
//Date			Thu 12 Sep 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void shape::dodial(UByte *& instr_ptr)
{
//DeadCode RJS 29Jan98 	IFShare	xpos,ypos,zpos;
//DeadCode RJS 29Jan98 	SLong	radius;						
//DeadCode RJS 29Jan98 	IFShare	xpos2,ypos2,zpos2;
//DeadCode RJS 29Jan98 	SLong	xpos3,ypos3,zpos3;
//DeadCode RJS 29Jan98 	SWord	sin_ang,cos_ang,radius2;
//DeadCode RJS 29Jan98 	SWord	totalangle;
//DeadCode RJS 29Jan98 	SWord	valuestep;
//DeadCode RJS 29Jan98 	UWord	vertex;
//DeadCode RJS 29Jan98 	UWord	object_scale,point_scale,scalefactor;
//DeadCode RJS 29Jan98 	SWord	angval;
//DeadCode RJS 29Jan98 	SWord	pulledval;											//RJS 04Oct96
//DeadCode RJS 29Jan98 	SWord	viewangle;											//RJS 20Nov96
//DeadCode RJS 29Jan98 	PolyPitAnimData* adptr = (PolyPitAnimData*) object_obj3d->AnimPtr;
//DeadCode RJS 29Jan98 
//DeadCode RJS 29Jan98 	DODIAL_PTR ptr = (DODIAL_PTR )instr_ptr;
//DeadCode RJS 29Jan98 
//DeadCode RJS 29Jan98 	viewangle = View_Point.hdg;									//RJS 10Dec96
//DeadCode RJS 29Jan98 	viewangle += (SWord)Manual_Pilot.ControlledAC2->hdg;				//RJS 10Dec96
//DeadCode RJS 29Jan98 	if (	(viewangle > (SWord) ANGLES_280Deg)					//RJS 20Nov96
//DeadCode RJS 29Jan98 		&&	(viewangle < (SWord) ANGLES_80Deg))					//RJS 20Nov96
//DeadCode RJS 29Jan98 	{
//DeadCode RJS 29Jan98 		xpos.i = ptr->posx<<shapescale;
//DeadCode RJS 29Jan98 		ypos.i =  0 - ptr->posy<<shapescale;
//DeadCode RJS 29Jan98 		zpos.i = ptr->posz<<shapescale;
//DeadCode RJS 29Jan98 
//DeadCode RJS 29Jan98 		radius = ptr->radius;
//DeadCode RJS 29Jan98 		radius2 = ptr->radius2;
//DeadCode RJS 29Jan98 
//DeadCode RJS 29Jan98 		switch (ptr->dtype)
//DeadCode RJS 29Jan98 		{
//DeadCode RJS 29Jan98 			case DT_RPM:
//DeadCode RJS 29Jan98 				pulledval = adptr->rpmdial;							//RJS 04Oct96
//DeadCode RJS 29Jan98 				angval = pulledval * ptr->anglestep;				//RJS 04Oct96
//DeadCode RJS 29Jan98 				break;
//DeadCode RJS 29Jan98 			case DT_ALT:
//DeadCode RJS 29Jan98 				pulledval = (object_obj3d->ItemPtr->World.Y * 10) / 305;//RJS 04Oct96
//DeadCode RJS 29Jan98 				angval = (pulledval * ptr->anglestep) / 100;			//RJS 04Oct96
//DeadCode RJS 29Jan98 				break;
//DeadCode RJS 29Jan98 			case DT_MPH:
//DeadCode RJS 29Jan98 				pulledval = (adptr->veldial * 100) / 447;			//RJS 04Oct96
//DeadCode RJS 29Jan98 				angval = pulledval * ptr->anglestep;				//RJS 04Oct96
//DeadCode RJS 29Jan98 				break;
//DeadCode RJS 29Jan98 			case DT_FUEL:
//DeadCode RJS 29Jan98 				pulledval = adptr->fuel;							//RJS 04Oct96
//DeadCode RJS 29Jan98 				angval = pulledval * ptr->anglestep;				//RJS 04Oct96
//DeadCode RJS 29Jan98 				break;
//DeadCode RJS 29Jan98 		}
//DeadCode RJS 29Jan98 
//DeadCode RJS 29Jan98 		if (pulledval > ptr->maxvalue)
//DeadCode RJS 29Jan98 			angval = ptr->maxvalue * ptr->anglestep;
//DeadCode RJS 29Jan98 
//DeadCode RJS 29Jan98 		totalangle = (SWord)ptr->startangle + angval - (SWord)ANGLES_180Deg;
//DeadCode RJS 29Jan98 
//DeadCode RJS 29Jan98 		Math_Lib.high_sin_cos((Angles) totalangle,sin_ang,cos_ang);
//DeadCode RJS 29Jan98 		xpos2.i = (sin_ang * radius) / ANGLES_FRACT;
//DeadCode RJS 29Jan98 		ypos2.i = (cos_ang * radius) / ANGLES_FRACT;
//DeadCode RJS 29Jan98 
//DeadCode RJS 29Jan98 		xpos2.i = xpos.i - xpos2.i;
//DeadCode RJS 29Jan98 		ypos2.i = ypos.i - ypos2.i;
//DeadCode RJS 29Jan98 		zpos2.i = zpos.i;
//DeadCode RJS 29Jan98 
//DeadCode RJS 29Jan98 		if (radius != radius2)
//DeadCode RJS 29Jan98 		{
//DeadCode RJS 29Jan98 			radius += radius2;
//DeadCode RJS 29Jan98 
//DeadCode RJS 29Jan98   			xpos3 = xpos.i;
//DeadCode RJS 29Jan98   			ypos3 = ypos.i;
//DeadCode RJS 29Jan98   			zpos3 = zpos.i;
//DeadCode RJS 29Jan98  
//DeadCode RJS 29Jan98  			xpos.i = (sin_ang * radius) / ANGLES_FRACT;
//DeadCode RJS 29Jan98  			ypos.i = (cos_ang * radius) / ANGLES_FRACT;
//DeadCode RJS 29Jan98  
//DeadCode RJS 29Jan98  			xpos.i = xpos3- xpos.i;
//DeadCode RJS 29Jan98  			ypos.i = ypos3- ypos.i;
//DeadCode RJS 29Jan98 		}
//DeadCode RJS 29Jan98 
//DeadCode RJS 29Jan98 		_matrix.transform(fpobject_matrix,xpos,ypos,zpos);
//DeadCode RJS 29Jan98 
//DeadCode RJS 29Jan98 		newco[0].bodyx.f = xpos.f + object_obj3d->Body.X.f;
//DeadCode RJS 29Jan98 		newco[0].bodyy.f = ypos.f + object_obj3d->Body.Y.f;
//DeadCode RJS 29Jan98 		newco[0].bodyz.f = zpos.f + object_obj3d->Body.Z.f;
//DeadCode RJS 29Jan98 
//DeadCode RJS 29Jan98 		_matrix.transform(fpobject_matrix,xpos2,ypos2,zpos2);
//DeadCode RJS 29Jan98 
//DeadCode RJS 29Jan98 		newco[1].bodyx.f = xpos2.f + object_obj3d->Body.X.f;
//DeadCode RJS 29Jan98 		newco[1].bodyy.f = ypos2.f + object_obj3d->Body.Y.f;
//DeadCode RJS 29Jan98 		newco[1].bodyz.f = zpos2.f + object_obj3d->Body.Z.f;
//DeadCode RJS 29Jan98 
//DeadCode RJS 29Jan98 		_matrix.body2screen(newco[0]);				
//DeadCode RJS 29Jan98 		_matrix.body2screen(newco[1]);
//DeadCode RJS 29Jan98 
//DeadCode RJS 29Jan98 		SLong	z0,z1;												//PD 20Nov96
//DeadCode RJS 29Jan98 
//DeadCode RJS 29Jan98 		z0 = (SLong)newco[0].bodyz.f;									//PD 20Nov96
//DeadCode RJS 29Jan98 		z1 = (SLong)newco[1].bodyz.f;									//PD 20Nov96
//DeadCode RJS 29Jan98 
//DeadCode RJS 29Jan98 		if (z0>0&&z1>0)												//PD 20Nov96
//DeadCode RJS 29Jan98 		{
//DeadCode RJS 29Jan98  			current_screen->ClipLine3D(	newco[0].screenx.f,		//RJS 26Feb97
//DeadCode RJS 29Jan98 	 								   	newco[0].screeny.f,		//RJS 26Feb97
//DeadCode RJS 29Jan98  									   	newco[1].screenx.f,		//RJS 26Feb97
//DeadCode RJS 29Jan98  									   	newco[1].screeny.f);	//RJS 26Feb97
//DeadCode RJS 29Jan98 		}
//DeadCode RJS 29Jan98 	}
//DeadCode RJS 29Jan98 

	DODIAL_PTR	ptr = (DODIAL_PTR )instr_ptr;
	IFShare		cx,cy,cz;
	SLong		radius;						
	IFShare		tipx,tipy,tipz;
	SWord		ex,ey;
	IFShare		xpos2,ypos2,zpos2;
	IFShare		xpos3,ypos3,zpos3;
	SWord		sin_ang,cos_ang,radius2;
//DeadCode RJS 21Apr99 	UByteP		adptr = (UByteP) object_obj3d->AnimPtr;
	SLong		flag;
	SLong		arc;
	SWord		totalangle = ptr->startangle;
	UWord		flagsize = ptr->flagsize;					//RJS 10Feb98

	switch (flagsize)										//RJS 10Feb98
	{
		case 8:
			flag = GlobalAdptr[ptr->animflag];
			break;
		case 16:
			flag = *((SWordP)&GlobalAdptr[ptr->animflag]);
			flagsize--;										//RJS 10Feb98
			break;
		case 32:
			flag = *((SLongP)&GlobalAdptr[ptr->animflag]);
			flagsize--;										//RJS 10Feb98
			break;
	}

	arc = (flag*ptr->arc)>>flagsize;						//RJS 10Feb98

	radius = ptr->radius;
	radius2 = ptr->radius2;
	ex = 0;
	ey = 0;

	totalangle += arc;

	Math_Lib.high_sin_cos((Angles) totalangle,sin_ang,cos_ang);
	tipx.i = (sin_ang * radius) / ANGLES_FRACT;
	tipy.i = (cos_ang * radius) / ANGLES_FRACT;

	cx.i = ptr->xpos;
	cy.i = -ptr->ypos;
	cz.i = ptr->zpos;
//DeadCode PD 05Oct98 	cx.i = ptr->xpos << shapescale;
//DeadCode PD 05Oct98 	cy.i = -ptr->ypos << shapescale;
//DeadCode PD 05Oct98 	cz.i = ptr->zpos << shapescale;
//DeadCode DAW 03Feb98 ==========

	tipx.i += cx.i;
	tipy.i += cy.i;
	tipz.i = cz.i;

	if (radius2)
	{
		ex = (sin_ang * radius2) / ANGLES_FRACT;
		ey = (cos_ang * radius2) / ANGLES_FRACT;
	}

	if (ptr->fatneedle)
	{
		totalangle -= ANGLES_5Deg;
		Math_Lib.high_sin_cos((Angles) totalangle,sin_ang,cos_ang);

		radius *= 3;
		radius >>= 2;

		xpos2.i = (sin_ang * radius) / ANGLES_FRACT;
		ypos2.i = (cos_ang * radius) / ANGLES_FRACT;

		totalangle += ANGLES_10Deg;
		Math_Lib.high_sin_cos((Angles) totalangle,sin_ang,cos_ang);

		xpos3.i = (sin_ang * radius) / ANGLES_FRACT;
		ypos3.i = (cos_ang * radius) / ANGLES_FRACT;

		xpos2.i += cx.i;
		ypos2.i += cy.i;
		zpos2.i = cz.i;

		xpos3.i += cx.i;
		ypos3.i += cy.i;
		zpos3.i = cz.i;
	}

	cx.i += ex;
	cy.i += ey;

	_matrix.transformNC(fpobject_matrix,cx,cy,cz);

	newco[0].bodyx.f = cx.f + object_obj3d->Body.X.f;
	newco[0].bodyy.f = cy.f + object_obj3d->Body.Y.f;
	newco[0].bodyz.f = cz.f + object_obj3d->Body.Z.f;

	_matrix.transformNC(fpobject_matrix,tipx,tipy,tipz);

	newco[1].bodyx.f = tipx.f + object_obj3d->Body.X.f;
	newco[1].bodyy.f = tipy.f + object_obj3d->Body.Y.f;
	newco[1].bodyz.f = tipz.f + object_obj3d->Body.Z.f;

	oredFlags=CF3D_NULL;
	andedFlags=CF3D_ALL;

	_matrix.SetClipFlags(newco[0]);
	_matrix.SetClipFlags(newco[1]);
	oredFlags|=newco[0].clipFlags;
	oredFlags|=newco[1].clipFlags;
	andedFlags&=newco[0].clipFlags;
	andedFlags&=newco[1].clipFlags;
	if (andedFlags == 0)
	{
//		if (!doingHW3D) 
//		{
//			_matrix.body2screen(newco[0]);				
//			_matrix.body2screen(newco[1]);
//		}
		if (ptr->fatneedle)
		{
			_matrix.transformNC(fpobject_matrix,xpos2,ypos2,zpos2);

			newco[2].bodyx.f = xpos2.f + object_obj3d->Body.X.f;
			newco[2].bodyy.f = ypos2.f + object_obj3d->Body.Y.f;
			newco[2].bodyz.f = zpos2.f + object_obj3d->Body.Z.f;

			_matrix.transformNC(fpobject_matrix,xpos3,ypos3,zpos3);

			newco[3].bodyx.f = xpos3.f + object_obj3d->Body.X.f;
			newco[3].bodyy.f = ypos3.f + object_obj3d->Body.Y.f;
			newco[3].bodyz.f = zpos3.f + object_obj3d->Body.Z.f;

			_matrix.SetClipFlags(newco[2]);
			_matrix.SetClipFlags(newco[3]);

			oredFlags|=newco[2].clipFlags;
			oredFlags|=newco[3].clipFlags;
			andedFlags&=newco[2].clipFlags;
			andedFlags&=newco[3].clipFlags;
			if (andedFlags == 0)
			{
//				if (!doingHW3D)
//				{
//					_matrix.body2screen(newco[2]);				
//					_matrix.body2screen(newco[3]);
//				}

				POLYGON.createpoly(shape::colour);				
				POLYGON.createvert(newco[0]);
				POLYGON.createvert(newco[2]);
				POLYGON.createvert(newco[1]);
				POLYGON.createvert(newco[3]);
				POLYGON.drawpoly();
			}
		}
		else
		{
			DOLINE	doinst;
			UByteP	pinst = (UByteP) &doinst;

			doinst.start_vertex = 0;
			doinst.end_vertex = 1;

			doline(pinst);
		}
	}

	instr_ptr += sizeof(DODIAL);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		docompass
//Author		Paul.   
//Date			Wed 10 Jul 1996
//
//Description	Updated for fancy modern cockpit stuff.....
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::docompass(UByte *& instr_ptr)
{
	
	instr_ptr += sizeof(DOCOMPASS);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		doiswitch
//Author		Paul.   
//Date			Wed 10 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void shape::doiswitch(UByte *& instr_ptr)
{
	instr_ptr += sizeof(DOISWITCH);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		doincln
//Author		Robert Slater
//Date			Tue 17 Sep 1996
//
//Description	Updated for fancy modern cockpit stuff.....
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void shape::doincln(UByte *& instr_ptr)
{
	DOINCLN_PTR	ptr = (DOINCLN_PTR )instr_ptr;
	IFShare		cx,cy,cz;
	SLong		radius,radius2;						
	IFShare		tipx,tipy,tipz;
	IFShare		tipx2,tipy2,tipz2;
	IFShare		tipx3,tipy3,tipz3;
	IFShare		tipx4,tipy4,tipz4;
	SLong		ex,ey,ez;
	SWord		sin_ang,cos_ang;
	DOLINE		doinst;
	UByteP		pinst = (UByteP) &doinst;
	SWord		pitch = object_obj3d->AngC;
	SWord		l1;

	radius = (-pitch * ptr->radius) / ANGLES_20Deg;
	if (radius > ptr->radius)
		radius = ptr->radius;
	else
	{
		if (radius < -ptr->radius)
			radius = -ptr->radius;
	}

	radius2 = ((radius<0)?-radius:radius);

	cx.i = ptr->xpos;
	cy.i = -ptr->ypos;
	cz.i = ptr->zpos;
//DeadCode PD 05Oct98 	cx.i = ptr->xpos << shapescale;
//DeadCode PD 05Oct98 	cy.i = -ptr->ypos << shapescale;
//DeadCode PD 05Oct98 	cz.i = ptr->zpos << shapescale;

	Math_Lib.high_sin_cos(object_obj3d->AngR,sin_ang,cos_ang);
	l1 = (ptr->radius * POLYGON.Cos_ArcSin((radius2<<8)/ptr->radius)) >> 15;

	ex = (cos_ang * l1) / ANGLES_FRACT;
	ey = (sin_ang * l1) / ANGLES_FRACT;

	sin_ang = -sin_ang;

	cx.i += ((sin_ang * radius) / ANGLES_FRACT);
	cy.i += ((cos_ang * radius) / ANGLES_FRACT);

	tipx.i = cx.i - ex;
	tipy.i = cy.i - ey;
	tipz.i = cz.i;

	tipx2.i = cx.i + ex;
	tipy2.i = cy.i + ey;
	tipz2.i = cz.i;

	tipx3.i = (tipx2.i<<15)-(sin_ang*3);
	tipy3.i = (tipy2.i<<15)-(cos_ang*3);
	tipz3.i = (tipz2.i<<15);

	tipx4.i = (tipx.i<<15)-(sin_ang*3);
	tipy4.i = (tipy.i<<15)-(cos_ang*3);
	tipz4.i = (tipz.i<<15);

	_matrix.transformNC(fpobject_matrix,tipx,tipy,tipz);
	_matrix.transformNC(fpobject_matrix,tipx2,tipy2,tipz2);
	_matrix.transformNC(fpobject_matrix,tipx3,tipy3,tipz3);
	_matrix.transformNC(fpobject_matrix,tipx4,tipy4,tipz4);

	newco[0].bodyx.f = tipx.f + object_obj3d->Body.X.f;
	newco[0].bodyy.f = tipy.f + object_obj3d->Body.Y.f;
	newco[0].bodyz.f = tipz.f + object_obj3d->Body.Z.f;

	newco[1].bodyx.f = tipx2.f + object_obj3d->Body.X.f;
	newco[1].bodyy.f = tipy2.f + object_obj3d->Body.Y.f;
	newco[1].bodyz.f = tipz2.f + object_obj3d->Body.Z.f;

	newco[2].bodyx.f = (tipx3.f*0.00003052) + object_obj3d->Body.X.f;
	newco[2].bodyy.f = (tipy3.f*0.00003052) + object_obj3d->Body.Y.f;
	newco[2].bodyz.f = (tipz3.f*0.00003052) + object_obj3d->Body.Z.f;

	newco[3].bodyx.f = (tipx4.f*0.00003052) + object_obj3d->Body.X.f;
	newco[3].bodyy.f = (tipy4.f*0.00003052) + object_obj3d->Body.Y.f;
	newco[3].bodyz.f = (tipz4.f*0.00003052) + object_obj3d->Body.Z.f;

	andedFlags=CF3D_ALL;

	_matrix.SetClipFlags(newco[0]);
	_matrix.SetClipFlags(newco[1]);
	_matrix.SetClipFlags(newco[2]);
	_matrix.SetClipFlags(newco[3]);
	andedFlags&=newco[0].clipFlags;
	andedFlags&=newco[1].clipFlags;
	andedFlags&=newco[2].clipFlags;
	andedFlags&=newco[3].clipFlags;
	if (andedFlags == 0)
	{
//		if (!doingHW3D) 
//		{
//			_matrix.body2screen(newco[0]);				
//			_matrix.body2screen(newco[1]);
//			_matrix.body2screen(newco[2]);
//			_matrix.body2screen(newco[3]);
//		}

		SWord	minx,miny,maxx,maxy;

		minx = ptr->minx;
		miny = ptr->miny;
		maxx = ptr->maxx;
		maxy = ptr->maxy;

		POLYGON.createpoly((ImageMapNumber) ptr->imagamap);				
		POLYGON.createvert(newco[0],minx,miny);
		POLYGON.createvert(newco[1],maxx,miny);
		POLYGON.createvert(newco[2],maxx,maxy);
		POLYGON.createvert(newco[3],minx,maxy);
		POLYGON.drawpoly();
	}

//	_matrix.body2screen(newco[0]);				
//	_matrix.body2screen(newco[1]);				


//	doinst.start_vertex = 0;
//	doinst.end_vertex = 1;
//
//	doline(pinst);

	






	tipx.i = (ptr->xpos) - ptr->radius;
	tipy.i = (-ptr->ypos);
	tipz.i = (ptr->zpos);
//DeadCode PD 05Oct98 	tipx.i = (ptr->xpos << shapescale) - ptr->radius;
//DeadCode PD 05Oct98 	tipy.i = (-ptr->ypos << shapescale);
//DeadCode PD 05Oct98 	tipz.i = (ptr->zpos << shapescale);

	tipx2.i = tipx.i + (ptr->radius<<1);
	tipy2.i = tipy.i;
	tipz2.i = tipz.i;

	_matrix.transformNC(fpobject_matrix,tipx,tipy,tipz);
	_matrix.transformNC(fpobject_matrix,tipx2,tipy2,tipz2);

	newco[0].bodyx.f = tipx.f + object_obj3d->Body.X.f;
	newco[0].bodyy.f = tipy.f + object_obj3d->Body.Y.f;
	newco[0].bodyz.f = tipz.f + object_obj3d->Body.Z.f;

	newco[1].bodyx.f = tipx2.f + object_obj3d->Body.X.f;
	newco[1].bodyy.f = tipy2.f + object_obj3d->Body.Y.f;
	newco[1].bodyz.f = tipz2.f + object_obj3d->Body.Z.f;

	_matrix.SetClipFlags(newco[0]);
	_matrix.SetClipFlags(newco[1]);
	_matrix.body2screen(newco[0]);				
	_matrix.body2screen(newco[1]);				

	doinst.start_vertex = 0;
	doinst.end_vertex = 1;

	pinst = (UByteP) &doinst;
	doline(pinst);

	instr_ptr += sizeof(DOINCLN);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dosetglassrange
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
 void shape::dosetglassrange(UByte *& instr_ptr)
{
	DOSETGLASSRANGE_PTR ptr;

	ptr = (DOSETGLASSRANGE_PTR) instr_ptr;
	
	UByte MAPPING_BASE;
	UByte MAPPING_RANGE;

	MAPPING_BASE = ptr->base;
	MAPPING_RANGE = ptr->spread;

//PD 29Nov95 - THIS SHOULD BE IN WRAPPER!

	instr_ptr += sizeof(DOSETGLASSRANGE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		docreatebpoly
//Author		Paul.   
//Date			Mon 15 Jan 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void shape::docreatebpoly(UByte *& instr_ptr)
{
	instr_ptr += sizeof(DOCREATEBUMPPOLY);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		docopybvert
//Author		Paul.   
//Date			Mon 15 Jan 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void shape::docopybvert(UByte *& instr_ptr)
{
	instr_ptr += sizeof(DOCOPYBVERT);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		dodrawbpoly
//Author		Paul.   
//Date			Mon 15 Jan 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void shape::dodrawbpoly(UByte *&)
{
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		doanimation
//Author		Robert Slater
//Date			Tue 18 Feb 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void shape::doanimation(UByte *&instr_ptr)
{
	DOANIMATION_PTR	ptr = (DOANIMATION_PTR) instr_ptr;
//DeadCode RJS 21Apr99 	UByteP			adptr = (UByteP) object_obj3d->AnimPtr;			
	SByte			toggleflag;
	UByte			loopflag = GlobalAdptr[ptr->loopoffset];
	SLong			framecounter;
	SLong			cntinc, speedinc;
	MinAnimData*	mad = (MinAnimData*) GlobalAdptr;
	Bool			doit = FALSE;
	Bool			cheattrigger = FALSE;
	AtMax			MaxAction = (AtMax) ptr->maxaction;			//RJS 27Oct97
	ClockType		ClockInc = (ClockType) ptr->increment;		//RJS 27Oct97
	UByte			ThisState = mad->itemstate;					//RJS 27Oct97
	UByte			Condition = ptr->activatenow;				//RJS 27Oct97
	SLong			themax = ptr->maxframes;
	int				animtimer = ptr->flagoffset;

	if (ptr->damagetoggle)
	{
		ThisState = GlobalAdptr[ptr->damageoffset];
		ThisState /= 96;
	}

	if (	(ThisState == Condition)							//RJS 27Oct97
		||	(ThisState & Condition)	)							//RJS 27Oct97
		doit = TRUE;											//RJS 27Oct97
											
	if (ptr->toggleoffset)										//RJS 07Apr97
	{
		toggleflag = GlobalAdptr[ptr->toggleoffset];
		if (toggleflag)
			cheattrigger = doit = TRUE;
		else
			toggleflag = 1;
	}
	else
		toggleflag = 1;

	if (ptr->fadeoffset && GlobalAdptr[ptr->fadedepth])
	{
		animtimer = ptr->fadeoffset;
		themax = ptr->maxfadeframes;
	}

	framecounter = GlobalAdptr[animtimer];							//RJS 05May98
 	if (!doit && framecounter)									//RJS 15Oct97
 		cheattrigger = doit = TRUE;

	if (doit)
	{
		cntinc = current_screen->FrameTime();					//RJS 30Jun99
		if (cntinc)												//RJS 30Jun99
		{
			switch (ClockInc)										//RJS 27Oct97
			{
				case PER_FRAME:
					cntinc = 1;
					break;
				case PER_SEC10:
					cntinc += animlag;							//RJS 30Jun99
					cntinc /= 10;
					break;
				case PER_SEC100:
					cntinc += animlag;							//RJS 30Jun99
					break;
			}
		}

		if (ptr->timeroffset)
			cntinc = GlobalAdptr[ptr->timeroffset];

		cntinc *= toggleflag;									//RJS 05Jun97
		framecounter += cntinc;									//RJS 15Oct97

		if (ptr->toggleoffset)									//RJS 30Jun97
			GlobalAdptr[ptr->toggleoffset] = toggleflag;				//RJS 30Jun97

		if (toggleflag > 0)
		{
			if (framecounter > themax)							//RJS 05May98
			{
				switch (MaxAction)								//RJS 27Oct97
				{
					case MAX_STAY:
						framecounter = themax;
						break;
					case MAX_RESET_ZERO:
						if (cheattrigger)
							framecounter = cntinc;
						else
							framecounter = 0;
						break;
					case MAX_RESET_ONE:
						framecounter = cntinc;
						break;
					case MAX_DECREMENT:
						framecounter = themax - cntinc;
						GlobalAdptr[ptr->toggleoffset] = -GlobalAdptr[ptr->toggleoffset];
						break;
					case MAX_FADEOUT:
						framecounter = themax;
						if (!GlobalAdptr[ptr->fadedepth])
							GlobalAdptr[ptr->fadedepth] = 1;
						break;
				}
			}
		}
		else
		{
			if (framecounter < 0)
			{
				switch (MaxAction)								//RJS 27Oct97
				{
					case MAX_STAY:
						framecounter = 0;
						break;
					case MAX_RESET_ZERO:
						framecounter = themax;
						break;
					case MAX_RESET_ONE:
						framecounter = themax + cntinc;
						break;
					case MAX_DECREMENT:
						framecounter = 0;
						if (ptr->loopoffset)
						{
							if (GlobalAdptr[ptr->loopoffset])
							{
								GlobalAdptr[ptr->loopoffset]--;
								framecounter = cntinc;
								GlobalAdptr[ptr->toggleoffset] = -GlobalAdptr[ptr->toggleoffset];
							}
						}
						break;
				}
			}
		}

		GlobalAdptr[animtimer] = framecounter;
		if (animtimer == ptr->fadeoffset)
		{
			GlobalAdptr[ptr->fadedepth] = (framecounter * 254)/themax;
			GlobalAdptr[ptr->fadedepth]++;
		}
	}
	else
	{
		//Protect against going over max frames...
		if (MaxAction == MAX_STAY)								//RJS 31May99
		{
			if (toggleflag > 0)
			{
				if (framecounter > themax)
					GlobalAdptr[animtimer] = themax;
			}
			else
			{
				if (framecounter < 0)
					GlobalAdptr[animtimer] = 0;
			}
		}


	}

	instr_ptr += sizeof(DOANIMATION);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		dodamage
//Author		Robert Slater
//Date			Tue 18 Feb 1997
//
//Description	Increments damage flags,
//				or damage bits....
//
//			Could be a problem for transient items....
//
//		For group element damage..
//
//				Col_AnimPrevPtr--->Col_AnimPtr--->Col_AnimNextPtr
//					Col_NextDep------>THIS<-------Col_PrevDep
//
//					If dependencies < 0,   then just disable the dependent item,
//											else inflict damage.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void shape::dodamage(UByte *&instr_ptr)
{
	if (CollisionOn)		
	{
		DODAMAGE_PTR	ptr = (DODAMAGE_PTR) instr_ptr;
//DeadCode RJS 21Apr99 		UByteP			adptr = damage_AnimPtr;			//RJS 25Aug98
		UWord			damageflag;									//RJS 27Feb98
//DeadCode RJS 21Apr99 		UWord			velrand = adptr[ptr->veloffset];
		ItemPtr			itemhit = damage_ItemPtr;//RJS 25Aug98
		ULong			thisdead = BS_DEAD;
		WeapAnimData*	weapon = NULL;								//RJS 23May97
		MinAnimData*	mad = (MinAnimData*) damage_AnimPtr;				//RJS 27Feb98
		UWord	randno = Math_Lib.rnd();					//RJS 30Jun98
//DeadCode RJS 12Feb99 		SLong	realHitStrength = BoxCol::HitterStrength * (BoxCol::HitterDamageType + 1);//RJS 08Jan99
		SLong	realHitStrength = BoxCol::HitterStrength;		//RJS 12Feb99

		if (!HitThisOffset)
		{
			if (ptr->stationno)
			{
//DeadCode RJS 21Apr99 				weapon = (WeapAnimData*)(adptr + (sizeof(WeapAnimData)*(ptr->stationno-1)) + sizeof(MinAnimData));
				MoveGunAnimData* adptr = (MoveGunAnimData*)damage_AnimPtr;
				weapon = (WeapAnimData*) &adptr->weaponlaunchers[ptr->stationno-1];
				laststationdamage[0] = weapon->SubDamage;		//RJS 25Nov98
				if (weapon->SubDamage < 31)
				{
					ULong	destruction = damage_AnimPtr[ptr->flagoffset];
					if (destruction == BS_DEAD)
						weapon->SubDamage = 31;
					else
					{
						ULong	dmain,drand;
						ULong	damage;

						dmain = (destruction * 7)>>3;
						drand = (destruction - dmain)<<1;

						damage = dmain + ((randno * drand)>>16);

						if (damage > 255)
							damage = 255;

						damage *= 31;
						damage /= 255;

						laststationdamage[0] = weapon->SubDamage;					//RJS 06Apr98

						weapon->SubDamage = damage;
					}
				}

				instr_ptr += sizeof(DODAMAGE);
				return;
			}

			lastdamptr = &damage_AnimPtr[ptr->flagoffset];				//RJS 27Feb98
			if (ptr->flagoffset)								//RJS 27Feb98
			{
				ULong		vulnerability = ptr->vulnerability;	//RJS 30Jun98
				ULong		realinc = ptr->increment;

				damageflag = damage_AnimPtr[ptr->flagoffset];			//RJS 27Feb98
																//RJS 27Feb98
				lastdamage[0] = damageflag;						//RJS 27Feb98

				vulnerability >>= (BoxCol::HitterDamageType<<3);//RJS 30Jun98
				vulnerability &= 0xFF;							//RJS 30Jun98
				if (vulnerability)
				{
//DeadCode RJS 12Feb99 					realinc = vulnerability * realHitStrength;	//RJS 06Dec98
//DeadCode RJS 12Feb99 					damageflag += realinc;							//RJS 22Jan98
					if (BoxCol::HitterStrength)
					{
						ULong	nohitstokill = vulnerability / BoxCol::HitterStrength;
						if (nohitstokill)
						{
							realinc = (thisdead*BoxCol::HitterStrength)/vulnerability;
							damageflag += realinc;							//RJS 22Jan98
						}
						else
							damageflag = thisdead;
					}
					else
						damageflag = thisdead;
				}
			}
			else
			{
				ULong		vulnerability = ptr->vulnerability;
				ULong		destruction, hitstrength;

   				thisdead = 3;
				vulnerability >>= (BoxCol::HitterDamageType*8);	//RJS 30Jun98
				vulnerability &= 0xFF;							//RJS 30Jun98

				lastdamage[0] = mad->itemstate;					//RJS 27Feb98
				damageflag = mad->itemstate;					//RJS 27Feb98

				if (vulnerability)	//damage points needed to kill...
				{
					ULong	nohitstokill;
					//Make harder to kill if protected...
					if (damage_GrpTokenDep != NULL)
						vulnerability += vulnerability*(thisdead-((MinAnimData*)damage_GrpTokenDep)->itemstate);
					if (BoxCol::HitterStrength)						  //JIM 22/02/99
						nohitstokill = vulnerability / BoxCol::HitterStrength;
					else											  //JIM 22/02/99
						nohitstokill=1;								  //JIM 22/02/99
					if (nohitstokill)
					{
						// Calc what it takes to move up a notch...
						destruction = ((thisdead<<16)*BoxCol::HitterStrength)/vulnerability;
						if (randno < destruction)
						{
							SLong	notchsize = (destruction<<1)/65535;
							if (notchsize < 3)
								notchsize = 2;			//1 notch
							else
							{
								if (notchsize > 5)
									notchsize = 6;		//3 notches
								else
									notchsize = 4;	//shit fiddle, cos we can't add 1.5 units of damage...2 notches
							}

							damageflag+=(notchsize>>1);
						}
					}
					else
						damageflag = thisdead;

//DeadCode RJS 08Feb99 					vulnerability++;	//up to 256
//DeadCode RJS 08Feb99 					hitstrength = realHitStrength + 1;//up to 32
//DeadCode RJS 08Feb99 
//DeadCode RJS 08Feb99 					//random hit strength increment, of maximum 30% power (out of hitterstrength),
//DeadCode RJS 08Feb99 					//so something of 70% hit strength could do total damage with one hit
//DeadCode RJS 08Feb99 					randno = (randno * 3 * hitstrength)/7;
//DeadCode RJS 08Feb99 					hitstrength += (randno>>16);
//DeadCode RJS 08Feb99 
//DeadCode RJS 08Feb99 					destruction = thisdead * vulnerability * hitstrength;//RJS 17Nov98
//DeadCode RJS 08Feb99 					destruction >>= 13;							//RJS 17Nov98
//DeadCode RJS 08Feb99 
//DeadCode RJS 08Feb99 					damageflag += destruction;
				}
			}
		}
		else
		{
			if (ptr->stationno)
			{
				MoveGunAnimData* adptr = (MoveGunAnimData*)damage_AnimPtr;
				weapon = (WeapAnimData*)&adptr->weaponlaunchers[ptr->stationno-1];
				laststationdamage[0] = weapon->SubDamage;		//RJS 25Nov98
				if (weapon->SubDamage < 31)
				{
					ULong	damage = (damage_AnimPtr[ptr->flagoffset] * 31)/255;//RJS 25Nov98
																//RJS 25Nov98
					weapon->SubDamage = damage;					//RJS 25Nov98
				}

				instr_ptr += sizeof(DODAMAGE);
				return;
			}
			else
			{
				lastdamptr = &damage_AnimPtr[ptr->flagoffset];				//RJS 27Feb98
				if (ptr->flagoffset)								//RJS 27Feb98
//DEADCODE DAW 26/04/99 					damageflag = damage_AnimPtr[ptr->flagoffset];//RJS 21Apr99
					damageflag = damage_ItemState;					//RJS 26Apr99
				else
				{
   					thisdead = 3;
					damageflag = mad->itemstate;					//RJS 27Feb98
				}
			}
		}

		if (damageflag > thisdead)
			damageflag = thisdead;

		if (lastdamage[0] != damageflag)
		{
			Bool	isplane = FALSE;

			if (itemhit->Status.size == AirStrucSize)
			{
				isplane = TRUE;						//RJS 08Jun99
				if (BoxCol::Col_Shooter)
				{
					if (!AirStrucPtr(itemhit)->lasthitter.count && BoxCol::Col_Shooter->Status.size==AIRSTRUCSIZE) //RJS 08Jun99
					{
						if (AirStrucPtr(itemhit)->ai.eventlog!=AirStrucPtr(BoxCol::Col_Shooter)->ai.eventlog)
						{
							if (AirStrucPtr(itemhit)->IsUsingPilotedAcLog()) 
								Persons2::UpdateLog	(AirStrucPtr(BoxCol::Col_Shooter),-1,EventLog::DAMAGED);
							else
								if (AirStrucPtr(BoxCol::Col_Shooter)->IsUsingPilotedAcLog())
									Persons2::UpdateLog	(AirStrucPtr(itemhit),+1,EventLog::DAMAGED);
								else
								{
									Persons2::UpdateLog	(AirStrucPtr(itemhit),0,EventLog::ATTACKEDBYOTHERS);
									Persons2::UpdateLog	(AirStrucPtr(BoxCol::Col_Shooter),0,EventLog::ATTACKEDBYOTHERS);
								}
						}
					}

					if (itemhit->uniqueID.count != BoxCol::Col_Shooter->uniqueID.count)			//RJS 08Jun99
						((AirStrucPtr)itemhit)->lasthitter.count = BoxCol::Col_Shooter->uniqueID.count;

// cant do this in record/playback because in playback there is no shooter
// and so ac wont get shoved in same way as in record, resulting in complete
// breakdown of playback and me getting very annoyed 			//AMM 08Jul99
					
//DeadCode AMM 08Jul99 					if (!_Replay.Playback || (itemhit != Persons2::PlayerSeenAC))		//RJS 29Jun99
					if (!_Replay.Playback && !_Replay.Record)	//AMM 08Jul99
					{									
						if (BoxCol::ShoveX || BoxCol::ShoveY || BoxCol::ShoveZ)
						{
							AirStrucPtr	ac = (AirStrucPtr) itemhit;

							//+- 0.001						
							ac->fly.pModel->RotVel.x += (Float(BoxCol::ShoveX) * 0.000078125);
							ac->fly.pModel->RotVel.y += (Float(BoxCol::ShoveY) * 0.000078125);
							ac->fly.pModel->RotVel.z += (Float(BoxCol::ShoveZ) * 0.000078125);
						}
					}
				}
			}

			if (damageflag == thisdead)
			{
				ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(damage_Shape);//RJS 16Sep98

				if ((BoxCol::Col_Shooter == Manual_Pilot.ControlledAC2) && !isplane)	//RJS 18Jun99
					View_Point->PossDirectorAction(BoxCol::colpos_hitgrp);//RJS 24May99

				if (damage_GrpElmt > -1)//RJS 16Sep98
				{
					ShapeDescPtr	supersdptr = (ShapeDescPtr) damage_Sdptr;
					SLong			timedead, supertimedead;
					SLong			ndam,odam;
					GrpMinAnimData		*madder;
					DOGROUP_PTR		gptr;
					SLong			Col_NextDep = 0;
					SLong			Col_PrevDep = 0;
					Coords3D		pPos,nPos;
					GrpMinAnimData*	gmad = (GrpMinAnimData*) mad;
					UWord			panimoff,nanimoff;


					if (ptr->setinvisible)						//RJS 22Nov98
						gmad->IsInvisible = 1;					//RJS 22Nov98

					panimoff = nanimoff = 0;					//RJS 27Apr99

					if (damage_GrpPrev)
					{
						gptr = (DOGROUP_PTR) damage_GrpPrev;
						Col_NextDep = gptr->element_next;
						madder = (GrpMinAnimData*) damage_GrpAnimPrev;//RJS 17Nov98
						if ((madder->itemstate == DEAD) || (madder->IsBullied==1))//RJS 17Nov98
						{
							Col_NextDep = 0;
//Dead							panimoff = 0;
						}
						else
						{
							if (Col_NextDep)
							{
								pPos.X = gptr->xoffset + itemhit->World.X;
								pPos.Y = gptr->yoffset + itemhit->World.Y;
								pPos.Z = gptr->zoffset + itemhit->World.Z;
								madder->IsBullied = 1;
								panimoff = damage_GrpAnimPrev - itemhit->Anim;
							}
						}
					}

					if (damage_GrpNext)
					{
						gptr = (DOGROUP_PTR) damage_GrpNext;
						Col_PrevDep = gptr->element_prev;
						madder = (GrpMinAnimData*) damage_GrpAnimNext;//RJS 17Nov98
						if ((madder->itemstate == DEAD) || (madder->IsBullied==1))//RJS 17Nov98
						{
							Col_PrevDep = 0;
//Dead							nanimoff = 0;
						}
						else
						{
							if (Col_PrevDep)
							{
								nPos.X = gptr->xoffset + itemhit->World.X;
								nPos.Y = gptr->yoffset + itemhit->World.Y;
								nPos.Z = gptr->zoffset + itemhit->World.Z;
								madder->IsBullied = 1;
								nanimoff = damage_GrpAnimNext - itemhit->Anim;
							}
						}
					}

					if (Col_PrevDep || Col_NextDep)
					{
						Trans_Obj.LaunchGroupThug(	itemhit,
													FIST,
													damage_GrpElmt-1,
													Col_NextDep,
													Col_PrevDep,
													pPos,
													nPos,
													panimoff,
													nanimoff,
													BoxCol::Col_Shooter);//RJS 05Jul99
					}

					if (	!itemhit->Status.deaded				//AMM 10Jun98
						&&	SHAPE.GetGroupDeathToll(itemhit) )
					{
						itemhit->Status.deaded = TRUE;			//AMM 10Jun98
						if (BoxCol::Col_Shooter)				//RJS 09Jun99
						{
							if (_DPlay.Implemented)						
							{											
								if (_DPlay.GameType>TEAMPLAY)
									_DPlay.NewScoreClaim(BoxCol::Col_Shooter,itemhit->uniqueID.count);
							}
							else
							{
								if (BoxCol::Col_Shooter->Status.size == AIRSTRUCSIZE)
									itemhit->ScoreSimpleItemKilled(true,(AirStrucPtr)BoxCol::Col_Shooter);
							}
						}
					}

					timedead = sdptr->DeadTime + itemhit->Status.deadtime;
					supertimedead = supersdptr->DeadTime;

					if (supertimedead < timedead)
						itemhit->Status.deadtime = supertimedead;
					else
						itemhit->Status.deadtime = timedead;

					itemhit->Status.deadscale = supersdptr->DeadScale;
				}
				else											//RJS 27Feb98
				{
					if (ptr->setinvisible)						//RJS 22Nov98
						mad->IsInvisible = 1;					//RJS 22Nov98

					if (	(itemhit != Manual_Pilot.ControlledAC2)	//RJS 06Mar97
						&&	isplane)								//RJS 06Mar97
						mad->itemstate = DAMMAGED;					//RJS 06Mar97

					if (itemhit->Status.deadtime == FALSE)			//RJS 06May99
					{
						if (ptr->isfatal || (itemhit != Manual_Pilot.ControlledAC2))//RJS 06May99
						{
							itemhit->Status.deadtime = sdptr->DeadTime;
							itemhit->Status.deadscale = sdptr->DeadScale;
	 						itemhit->Status.deaded = TRUE;		//RJS 27Feb98
							if (itemhit == Persons2::PlayerSeenAC)//RJS 09Jul99
							{
								Persons2::PlayerGhostAC->Status.deadtime = sdptr->DeadTime;
								Persons2::PlayerGhostAC->Status.deadscale = sdptr->DeadScale;
								Persons2::PlayerGhostAC->Status.deaded = TRUE;
							}

	// if we are in coop game score needs to be set when claim packets arrive

							if (_DPlay.Implemented && _DPlay.GameType<COMMSQUICKMISSION && isplane)	//RJS 09Jun99
							{
								_DPlay.SetScore((AirStrucPtr)itemhit,BoxCol::Col_Shooter);//JIM 11Mar99
							}

							if (itemhit->Status.size == FORMATIONSIZE)
							{
//DEADCODE JIM 09/09/99 								if (((FormationItem*)itemhit)->movecode != AUTO_NOPPILOT)//RJS 01Jul99
									((FormationItem*)itemhit)->BreakForm();
							}
							else
							{
								if (isplane)
								{
	// Screws up other aircraft death movecodes....
									if  (Manual_Pilot.ControlledAC2 == itemhit)
										_Miles.SequenceAudible(FIL_MUSIC_SPIRALLING);	  //RDH 01/03/99
									Manual_Pilot.DeathSequenceOverride(itemhit,AUTO_DEATHSEQUENCE);
									((AirStrucPtr)itemhit)->BreakForm();
									mad->itemstate = DAMMAGED;					//RJS 08Jan99
								}
							}

							if (!_DPlay.Implemented)
							{
	// claims in comms dealt with when claim packets arrive
								itemhit->ScoreSimpleItemKilled(true,(AirStrucPtr)BoxCol::Col_Shooter);//JIM 11Mar99
	//							itemhit->ScoreSimpleItemKilled(true,(AirStrucPtr)BoxCol::Col_Hitter);
							}
							else
							{
								if (_DPlay.GameType>TEAMPLAY)
								{
	// coop games only
	//DeadCode AMM 08Apr99 								if (hitterscorer)
	//DeadCode AMM 08Apr99 									_DPlay.NewScoreClaim(hitterscorer,(UniqueID)uniqueid);
									if (BoxCol::Col_Shooter)		//AMM 08Apr99
										_DPlay.NewScoreClaim(BoxCol::Col_Shooter,itemhit->uniqueID.count);//AMM 08Apr99


								}
							}
						}
					}
				}

				if (ptr->isejected)
				{
					WorldStuff*	worldptr = mobileitem::currworld;

					BoxCol::AddEffect(FX_VISUAL,BS_DEAD,ANIM_SMALLFLASH,0,NULL,damage_GrpElmt,damage_Shape);//RJS 05May99

					Trans_Obj.LaunchBitsOffPart(itemhit,
												&damage_AnimPtr[ptr->flagoffset],//RJS 21Apr99
												*worldptr,
												lastdamage[0],
												lastdamptr,
												BoxCol::HitterStrength);
				}
			}
		}														//RJS 27Feb98
																//RJS 27Feb98
		if (ptr->flagoffset)									//RJS 27Feb98
			damage_AnimPtr[ptr->flagoffset] = damageflag;		//RJS 21Apr99
		else													//RJS 27Feb98
			mad->itemstate = damageflag;						//RJS 27Feb98
	}															//RJS 27Feb98

	instr_ptr += sizeof(DODAMAGE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		doeffect
//Author		Robert Slater
//Date			Tue 18 Feb 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void shape::doeffect(UByte *&instr_ptr)
{
	if (CollisionOn)					
	{
		DOEFFECT_PTR	ptr = (DOEFFECT_PTR) instr_ptr;
//DeadCode RJS 21Apr99 		UByteP			adptr = damage_AnimPtr;			//RJS 25Aug98
		UWord			damageflag;
		ULong			knockval;
		UWord			randomval;
		Bool			doit = FALSE;
		EffectType		thetype = (EffectType) ptr->type;				//RJS 23May97
		WeapAnimData	*weapon = NULL;								//RJS 23May97
		UWord			EffectVal = ptr->enumvalue;						//RJS 23May97
		SWord			damtype = ptr->damagetype - 1;
		MinAnimData		*mad = (MinAnimData*) damage_AnimPtr;	//RJS 21Apr99
		UByte			maxscale = 255;
		UByte			lastdamval = lastdamage[ptr->damindexold];

		if ((damtype == -1) || (damtype == BoxCol::HitterDamageType))
		{
			UByte	levelactive = ptr->levelactive;
			if (ptr->flagoffset == 0)
			{
				damageflag = mad->itemstate;
				maxscale = 3;
			}
			else
			{
				if (ptr->stationno)
				{
					MoveGunAnimData*	adptr = (MoveGunAnimData*)damage_AnimPtr;
					// Always assume the weapon array is first in the animation data....
					weapon = (WeapAnimData*)&adptr->weaponlaunchers[ptr->stationno-1];;

					if (	(weapon->LauncherType == LT_INTFUEL)
						||	(weapon->LauncherType == LT_FUEL)
						||	(weapon->LauncherType == LT_VAPOUR)	)
						EffectVal = ANIM_FUELDAMAGE;
					else
						EffectVal = ANIM_WEAPONDAMAGE;

					lastdamval = laststationdamage[ptr->damindexold];
					damageflag = weapon->SubDamage;
					maxscale = 31;
				}
				else
					damageflag = damage_AnimPtr[ptr->flagoffset];//RJS 21Apr99
			}

			if (ptr->levelactive)
			{
				UByte	levellimit = BS_DAMLV1;

				levelactive = (maxscale * levelactive)/255;
				if (thetype < FX_ALIGN)
				{
					if (	(damageflag >= levelactive)
						&&	(lastdamval < levelactive) )				//RJS 06Apr98
						doit = TRUE;
				}
				else
				{
					switch (ptr->levelactive)
					{
						case BS_DAMLV1:
							levellimit = BS_DAMLV2;
							break;
						case BS_DAMLV2:
						case BS_DEAD:
							levellimit = BS_DEAD;
							break;
					}

					levellimit = (maxscale*levellimit)/255;

					if (	(damageflag >= levelactive)
						&&	(damageflag < levellimit)	)
					{
						doit = TRUE;
						if (	(EffectVal == ANIM_FUELDAMAGE)
							&&	(ptr->levelactive == BS_DEAD)	)
							thetype = FX_EJECT;
					}
				}
			}
			else
			{
				//We can pretty much guarantee that the only effects 
				//  to come in here are bullet hits
				if (HitThisOffset == FALSE)								//RJS 15Sep98
				{
					if (damage_GrpElmt > -1)
					{
						GrpMinAnimData*	gmad = (GrpMinAnimData*) mad;
						if (!gmad->IsBullied)
							doit = TRUE;
					}
					else
						doit = TRUE;										//RJS 15Sep98
				}
			}
		
			if (doit)
			{
				switch (thetype)
				{
//DeadCode RJS 04Feb99 					case FX_SFX_ALL:									//RJS 15Sep98
					case FX_SFX:										//RJS 15Sep98
						BoxCol::AddEffect(thetype,ptr->levelactive,ptr->enumvalue,ptr->randomdelta,NULL,damage_GrpElmt,damage_Shape);
						break;

					case FX_RADIO:
					{
						// Only trigger if another ac has inflicted this damage...
//DeadCode RDH 18May99 						TransientItemPtr transhitter = (TransientItemPtr) BoxCol::Col_Hitter;
//DeadCode RDH 18May99 						if (	transhitter
//DeadCode RDH 18May99 							&& (transhitter->Status.size == TRANSIENTSIZE)
//DeadCode RDH 18May99 							&& (transhitter->Launcher->Status.size >= AIRSTRUCSIZE)	)
//DeadCode RDH 18May99 						{
//DeadCode RDH 18May99 							BoxCol::AddEffect(thetype,ptr->levelactive,EffectVal,ptr->randomdelta,(UByteP)weapon,damage_GrpElmt,damage_Shape);
//DeadCode RDH 18May99 						}
						if ((BoxCol::Col_Shooter)&&
							BoxCol::Col_Shooter->Status.size >= AIRSTRUCSIZE)		//RDH 18May99
							BoxCol::AddEffect(thetype,ptr->levelactive,EffectVal,ptr->randomdelta,(UByteP)weapon,damage_GrpElmt,damage_Shape);//RDH 18May99
					}
					break;
					case FX_VISUAL:										//RJS 15Sep98
						BoxCol::AddEffect(thetype,ptr->levelactive,EffectVal,ptr->randomdelta,(UByteP)weapon,damage_GrpElmt,damage_Shape);
						break;
					case FX_EJECT:
					{
//DeadCode RJS 23Mar99 						if (BoxCol::Col_ExplodeIt == FALSE)		//RJS 30Mar98
						{
							WorldStuff*	worldptr = mobileitem::currworld;
							UByte		lastdam = damage_AnimPtr[ptr->enumvalue];//RJS 21Apr99
							UByteP		lastptr = &damage_AnimPtr[ptr->enumvalue];//RJS 21Apr99

							if (lastdam != BS_DEAD)
							{
								BoxCol::AddEffect(FX_VISUAL,ptr->levelactive,ANIM_SMALLFLASH,ptr->randomdelta,(UByteP)weapon,damage_GrpElmt,damage_Shape);//RJS 05May99
//DeadCode RJS 23Mar99 								adptr[ptr->enumvalue] = BS_DEAD;

								Trans_Obj.LaunchBitsOffPart(damage_ItemPtr,
															lastptr,
															*worldptr,
															lastdam,
															lastptr,
															ptr->randomdelta);

								damage_AnimPtr[ptr->enumvalue] = BS_DEAD;//RJS 21Apr99
							}
						}
					}
					break;
					case FX_INCREMENT:
						UWord	maxhit = ((damageflag - lastdamage[0]) * ptr->randomdelta)/100;
						if (maxhit)
						{
							UWord	chance = maxhit>>3;
							SLong	hitrand = Math_Lib.rnd(chance);

							knockval = damage_AnimPtr[ptr->enumvalue] + maxhit - (maxhit>>4) + hitrand;//RJS 21Apr99
							if (knockval > BS_DEAD)
								knockval = BS_DEAD;

							lastdamage[ptr->damindexnew] = damage_AnimPtr[ptr->enumvalue];//RJS 21Apr99

							damage_AnimPtr[ptr->enumvalue] = knockval;//RJS 21Apr99
						}
						break;
				}
			}
		}
	}

	instr_ptr += sizeof(DOEFFECT);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		docollision
//Author		Robert Slater
//Date			Tue 18 Feb 1997
//
//Description	
//				Macca stuff...
//			
//				send flag:
//							0 ... don't send
//							1 ... transient hit
//							2 ... non-transient hit
//							3 ... forced hit
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void shape::docollision(UByte *&instr_ptr)
{
	if (FixUpCollision)
	{
		CollisionCnt++;
		instr_ptr += sizeof(DOCOLLISION);
	}
	else
	{
		DOCOLLISION_PTR	ptr = (DOCOLLISION_PTR) instr_ptr;
//DeadCode RJS 21Apr99 		UByteP			adptr = damage_AnimPtr;						//RJS 25Aug98
		UByte			flag = damage_AnimPtr[ptr->flagoffset];
		Bool			hitit = FALSE;

		if (HitThisOffset)
		{
			if (ptr->flagoffset == HitThisOffset)
			{
				DOLAUNCHER	thislaunch;
				Coords3D	*cptr = &BoxCol::colpos_impact;

				CollisionOn = TRUE;
				DamageNow = TRUE;
			
				thislaunch.posx = ptr->xoff;
				thislaunch.posy = ptr->yoff;
				thislaunch.posz = ptr->zoff;

				SHAPE.LauncherToWorld(damage_ItemPtr,(UByteP)&thislaunch,damage_Scale,cptr->X,cptr->Y,cptr->Z,NULL);//RJS 25Aug98

				instr_ptr += sizeof(DOCOLLISION);

				if ((_DPlay.Implemented || _Replay.Record) 
					&& damage_ItemPtr==Persons2::PlayerSeenAC)//RJS 09Sep98
				{
					// Log a successful collision...
//						DamageNow = TRUE;
//DeadCode AMM 12Jul99 					CollisionOn = FALSE;
					_Replay.FakeCollisionOn=true;				//AMM 12Jul99

					SHAPE.LogCollision(	damage_ItemPtr,
										BoxCol::Col_Shooter,		  //JIM 11/03/99
										damage_Shape,			//AMM 26Nov98
										instr_ptr,
										damage_GrpElmt,					//RJS 16Sep98
										(damage_ItemState * FORCE_LEVEL4)/BS_DEAD,
										FORCE_SET,
										3);						//AMM 08Jan99
				}
			}
			else
				instr_ptr += sizeof(DOCOLLISION);
		}
		else
		{
			if (ptr->radius > 0)									//RJS 04Mar97
			{
 				if (ptr->flagoffset == 0)
 					flag = BS_ALIVE;
 
 				if (flag != BS_DEAD)	
 				{
 					// Detailed Collision test here....
					if (BoxCol::Col_ExplodeIt)						//RJS 30Mar98
						hitit = TRUE;								//RJS 30Mar98
					else
	 					hitit = BoxCol::TestCol2(ptr->xoff,			//RJS 20Apr98
												 ptr->yoff,			//RJS 20Apr98
												 ptr->zoff,			//RJS 20Apr98
												 ptr->sx,			//RJS 20Apr98
												 ptr->sy,			//RJS 20Apr98
												 ptr->sz,			//RJS 20Apr98
												 ptr->succeed);		//RJS 20Apr98
 				}

  				CollisionOn = hitit;								//RJS 22Jun98
			}
			else
				CollisionOn = hitit = BoxCol::DetailedTest();//New hit-box test//RJS 01Dec98

			if (hitit)
			{
				if (ptr->succeed)
					instr_ptr += ptr->succeed;
				else
				{
					SLong	send;								//AMM 08Jan99

					DamageNow = TRUE;
					instr_ptr += sizeof(DOCOLLISION);
					if (_DPlay.PossTransmitColl(damage_ItemPtr,BoxCol::Col_Hitter,send))//AMM 08Jan99
					{
						// Log a successful collision...
//						DamageNow = TRUE;
//DeadCode AMM 12Jul99 						CollisionOn = FALSE;
						_Replay.FakeCollisionOn=true;			//AMM 12Jul99

						// send calc moved to posstransmitcoll...//AMM 08Jan99

//DeadCode AMM 13Apr99 						if (send == 1)							//AMM 08Jan99
						if (send==-1)							//AMM 13Apr99
						{
// we are going to do this collision so kill the transient that caused it on all machines

//DeadCode AMM 13Apr99 							_DPlay.SendKillTransientsMessage(((TransientItemPtr)(BoxCol::Col_Hitter))->uniqueID.count);
							_DPlay.SendKillTransientsMessage();
						}

						SHAPE.LogCollision(	damage_ItemPtr,
											BoxCol::Col_Shooter,		  //JIM 11/03/99
											damage_Shape,		//AMM 26Nov98
											instr_ptr,
											damage_GrpElmt,					//RJS 16Sep98
											BoxCol::HitterDamageType,
											BoxCol::HitterStrength,
 											send);//AMM 31Aug98
					}
				}
			}
			else
				instr_ptr += ptr->fail;
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		dodrawstation
//Author		Robert Slater
//Date			Fri 28 Feb 1997
//
//Description	Duplicates weapon anim information for this station,
//				then draws the station....
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void shape::dodrawstation(UByte *&instr_ptr)
{
	DODRAWSTATION_PTR	ptr = (DODRAWSTATION_PTR) instr_ptr;
	AircraftAnimData*	adptr = (AircraftAnimData*) GlobalAdptr;
	WeapAnimData		weap = adptr->weaponlaunchers[ptr->stationno];

	if (weap.stationshape)										//RJS 24May99
	{															//RJS 24May99
		DOCALLSHAPE			subptr;								//RJS 24May99
		LauncherAnimData	newadptr;							//RJS 24May99
		MinAnimData*		mad;								//RJS 24May99
		animptr				oldadptr;							//RJS 24May99

		subptr.vertex = 0;
		subptr.shape = (ShapeNum) weap.stationshape;
		subptr.hdg = ANGLES_0Deg;
		subptr.pitch = ANGLES_0Deg;
		subptr.roll = ANGLES_0Deg;

		mad = (MinAnimData*) &newadptr;
		*mad = *((MinAnimData*) GlobalAdptr);
		mad->itemstate = ALIVE;		//otherwise rockets ignite!		//RJS 10May99

		newadptr.ammoleft = weap.LoadedStores;

		oldadptr = GlobalAdptr;
		GlobalAdptr = (UByteP)mad;
		GlobalAdptr = sizeof(LauncherAnimData)+ (1<<MINANIM)+ (1<<LAUNCHERANIM);

		DrawSubShape((UByteP)&subptr);							//RJS 01Dec97

		GlobalAdptr = oldadptr;
	}

	instr_ptr += sizeof(DODRAWSTATION);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		docaserange
//Author		Robert Slater
//Date			Mon 3 Mar 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void shape::docaserange(UByte *& instr_ptr)
{
	DOCASERANGE_PTR ptr = (DOCASERANGE_PTR )instr_ptr;
//DeadCode RJS 21Apr99 	UByteP			adptr = (UByteP) object_obj3d->AnimPtr;	
	SWord			flag;										//RJS 04Sep97
	SWord			thisjump;									//RJS 03Sep97
	UByteP			offset;
	int				i;											//RJS 03Sep97
	SWord			range;										//RJS 03Sep97
	SWord			possiblejump;								//RJS 03Sep97
	
	if (!ptr->useword)
		flag = GlobalAdptr[ptr->flag] / ptr->factor;			//RJS 21Apr99
	else
		flag = *((SWordP) &GlobalAdptr[ptr->flag]);				//RJS 21Apr99

	offset = instr_ptr + sizeof(DOCASERANGE);

	possiblejump = ptr->failjump;

	for (i=0; i < ptr->nofields; i++)
	{
		range = *(SWordP)offset;
		offset += sizeof(SWord);

		thisjump = *(SWordP)offset;
		offset += sizeof(SWord);

		if (flag >= range)
			possiblejump = thisjump;
		else
			break;
	}

//DeadCode RJS 03Sep97 	if (flag < ptr->range)
//DeadCode RJS 03Sep97 		offset += (ptr->nofields-1) * sizeof(UWord);
//DeadCode RJS 03Sep97 
//DeadCode RJS 03Sep97 	instr_ptr += *(UWord *)offset;

	instr_ptr += possiblejump;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		doifpiloted
//Author		Robert Slater
//Date			Fri 7 Mar 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void shape::doifpiloted(UByte *& instr_ptr)
{
	DOIFPILOTED_PTR ptr = (DOIFPILOTED_PTR )instr_ptr;
	
	if (BoxCol::Col_Shooter == Manual_Pilot.ControlledAC2)		//JIM 11Mar99
		instr_ptr += sizeof(DOIFPILOTED);
	else
		instr_ptr += ptr->offset;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		doniverts
//Author		Robert Slater
//Date			Thu 20 Mar 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void shape::doniverts(UByte *& instr_ptr)
{
	DONIVERTS_PTR ptr = (DONIVERTS_PTR )instr_ptr;
	NEXTMAP_PTR	  mapit;
	int		counter;
	int		vertex;
	int		i;


	counter = ptr->count;
	vertex = ptr->vertex;

	instr_ptr += sizeof(DONIVERTS);

	for (i=0; i < counter; i++)
	{
		mapit = (NEXTMAP_PTR) instr_ptr;

		newco[vertex].ix = mapit->ix;
		newco[vertex].iy = mapit->iy;

		vertex++;
		instr_ptr += sizeof(NEXTMAP);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		dotrifan
//Author		Robert Slater
//Date			Thu 27 Mar 1997
//
//Description	Crappy test for a fan of triangles......
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void shape::dotrifan(UByte *& instr_ptr)
{
	DOTRIFAN_PTR ptr = (DOTRIFAN_PTR )instr_ptr;
	int		counter;
	UByte	vertex;
	int		rootvert;
	int		tricnt;


	instr_ptr += sizeof(DOTRIFAN);

	rootvert = ptr->rootpnt;
	counter = ptr->edges;
	tricnt = 0;

	if (ptr->material)
	{
		DOCREATEIPOLY	tmpinst;
		UByteP			tmpptr;

		tmpinst.image_no = ptr->material;
		tmpptr = (UByteP) &tmpinst;
		docreateipoly(tmpptr);

		while (counter)
		{
			if (!tricnt)
			{
				tricnt++;
				POLYGON.createvert(newco[rootvert],newco[rootvert].ix,newco[rootvert].iy);
			}
			else
			{
				vertex = *((UByteP) instr_ptr);

				POLYGON.createvert(newco[vertex],newco[vertex].ix,newco[vertex].iy);
				counter--;

				if (tricnt < 2)
				{
					instr_ptr += sizeof(UByte);
					tricnt++;
				}
				else
				{
					tricnt = 0;
					POLYGON.drawpoly();

					if (counter)
					{
						counter++;
						tmpptr = (UByteP) &tmpinst;
						docreateipoly(tmpptr);
					}
				}
			}
		}
	}
	else
	{
		POLYGON.createpoly(shape::colour);

		while (counter)
		{
			if (!tricnt)
			{
				POLYGON.createvert(newco[rootvert]);
				tricnt++;
			}
			else
			{
				vertex = *((UByteP) instr_ptr);

				POLYGON.createvert(newco[vertex]);
				counter--;

				if (tricnt < 2)
				{
					tricnt++;
					instr_ptr += sizeof(UByte);
				}
				else
				{
					tricnt = 0;
					POLYGON.drawpoly();

					if (counter)
					{
						counter++;
						POLYGON.createpoly(shape::colour);
					}
				}
			}
		}
	}

	instr_ptr += sizeof(UByte);

//DeadCode RJS 23Apr97	_Error.EmitSysErr(__FILE__":Not a real instruction yet.....(DOTRIFAN)\n");
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		dotrizag
//Author		Robert Slater
//Date			Thu 27 Mar 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void shape::dotrizag(UByte *& instr_ptr)
{
	DOTRIZAG_PTR ptr = (DOTRIZAG_PTR )instr_ptr;
	int		tricnt;
	UByte	vertex[3];
	int		counter;
	Bool	clockwise = (Bool) ptr->direction;
	int		p1, p2, p3;

	counter = ptr->edges;
	tricnt = 0;

	instr_ptr += sizeof(DOTRIZAG);

	if (ptr->material)
	{
		DOCREATEIPOLY	tmpinst;
		UByteP			tmpptr;

		tmpinst.image_no = ptr->material;
		tmpptr = (UByteP) &tmpinst;
		docreateipoly(tmpptr);

		while (counter)
		{
			vertex[tricnt] = *((UByteP) instr_ptr);

			counter--;

			if (tricnt < 2)
			{
				tricnt++;
				instr_ptr += sizeof(UByte);
			}
			else
			{
				tricnt = 0;

				if (clockwise)
				{
					p1 = 0;
					p2 = 2;
					p3 = 1;
					clockwise = FALSE;
				}
				else
				{
					p1 = 0;
					p2 = 1;
					p3 = 2;
					clockwise = TRUE;
				}

				POLYGON.createvert(newco[vertex[p1]],newco[vertex[p1]].ix,newco[vertex[p1]].iy);
				POLYGON.createvert(newco[vertex[p2]],newco[vertex[p2]].ix,newco[vertex[p2]].iy);
				POLYGON.createvert(newco[vertex[p3]],newco[vertex[p3]].ix,newco[vertex[p3]].iy);
				POLYGON.drawpoly();

				if (counter)
				{
					instr_ptr -= sizeof(UByte);
					counter+=2;

					tmpptr = (UByteP) &tmpinst;
					docreateipoly(tmpptr);
				}
			}
		}
	}
	else
	{
		POLYGON.createpoly(shape::colour);

		while (counter)
		{
			vertex[tricnt] = *((UByteP) instr_ptr);
			counter--;

			if (tricnt < 2)
			{
				tricnt++;
				instr_ptr += sizeof(UByte);
			}
			else
			{
				tricnt = 0;

				if (clockwise)
				{
					p1 = 0;
					p2 = 2;
					p3 = 1;
					clockwise = FALSE;
				}
				else
				{
					p1 = 0;
					p2 = 1;
					p3 = 2;
					clockwise = TRUE;
				}

				POLYGON.createvert(newco[vertex[p1]]);
				POLYGON.createvert(newco[vertex[p2]]);
				POLYGON.createvert(newco[vertex[p3]]);
				POLYGON.drawpoly();

				if (counter)
				{
					instr_ptr -= sizeof(UByte);
					counter+=2;
					POLYGON.createpoly(shape::colour);
				}
			}
		}
	}

	instr_ptr += sizeof(UByte);

//DeadCode RJS 23Apr97 	_Error.EmitSysErr(__FILE__":Not a real instruction yet.....(DOTRIZAG)\n");
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		dotrifanflat
//Author		Robert Slater
//Date			Wed 16 Apr 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void shape::dotrifanflat(UByte *& instr_ptr)
{
	DOTRIFANFLAT_PTR ptr = (DOTRIFANFLAT_PTR )instr_ptr;
	int		counter;
	UByte	vertex;
	int		rootvert;
	int		tricnt;


	instr_ptr += sizeof(DOTRIFANFLAT);

	rootvert = ptr->rootpnt;
	counter = ptr->edges;
	tricnt = 0;

	if (ptr->material)
	{
		DOCREATEIPOLY	tmpinst;
		UByteP			tmpptr;

		tmpinst.image_no = ptr->material;
		tmpptr = (UByteP) &tmpinst;
		docreateipoly(tmpptr);

		while (counter)
		{
			if (!tricnt)
			{
				tricnt++;
				POLYGON.createvert(newco[rootvert],newco[rootvert].ix,newco[rootvert].iy);
			}
			else
			{
				vertex = *((UByteP) instr_ptr);

				POLYGON.createvert(newco[vertex],newco[vertex].ix,newco[vertex].iy);
				counter--;

				if (tricnt < 2)
				{
					tricnt++;
					instr_ptr += sizeof(UByte);
				}
				else
				{
					tricnt = 0;
					POLYGON.drawpoly();

					if (counter)
					{
						counter++;
						tmpptr = (UByteP) &tmpinst;
						docreateipoly(tmpptr);
					}
				}
			}
		}
	}
	else
	{
		POLYGON.createpoly(shape::colour);

		while (counter)
		{
			if (!tricnt)
			{
				tricnt++;
				POLYGON.createvert(newco[rootvert]);
			}
			else
			{
				vertex = *((UByteP) instr_ptr);

				POLYGON.createvert(newco[vertex]);
				counter--;

				if (tricnt < 2)
				{
					tricnt++;
					instr_ptr += sizeof(UByte);
				}
				else
				{
					tricnt = 0;
					POLYGON.drawpoly();

					if (counter)
					{
						counter++;
						POLYGON.createpoly(shape::colour);
					}
				}
			}
		}
	}

	instr_ptr += sizeof(UByte);

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		dotrizagflat
//Author		Robert Slater
//Date			Thu 27 Mar 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void shape::dotrizagflat(UByte *& instr_ptr)
{
	DOTRIZAGFLAT_PTR ptr = (DOTRIZAGFLAT_PTR )instr_ptr;
 	int		tricnt;
	UByte	vertex[3];
	int		counter;
	Bool	clockwise = (Bool) ptr->direction;
	int		p1,p2,p3;

	counter = ptr->edges;
	tricnt = 0;

	instr_ptr += sizeof(DOTRIZAGFLAT);


	if (ptr->material)
	{
		DOCREATEIPOLY	tmpinst;
		UByteP			tmpptr;

		tmpinst.image_no = ptr->material;
		tmpptr = (UByteP) &tmpinst;
		docreateipoly(tmpptr);

		while (counter)
		{
			vertex[tricnt] = *((UByteP) instr_ptr);

			counter--;

			if (tricnt < 2)
			{
				tricnt++;
				instr_ptr += sizeof(UByte);
			}
			else
			{
				tricnt = 0;

				if (clockwise)
				{
					p1 = 0;
					p2 = 2;
					p3 = 1;
					clockwise = FALSE;
				}
				else
				{
					p1 = 0;
					p2 = 1;
					p3 = 2;
					clockwise = TRUE;
				}

				POLYGON.createvert(newco[vertex[p1]],newco[vertex[p1]].ix,newco[vertex[p1]].iy);
				POLYGON.createvert(newco[vertex[p2]],newco[vertex[p2]].ix,newco[vertex[p2]].iy);
				POLYGON.createvert(newco[vertex[p3]],newco[vertex[p3]].ix,newco[vertex[p3]].iy);
				POLYGON.drawpoly();

				if (counter)
				{
					instr_ptr -= sizeof(UByte);
					counter+=2;

					tmpptr = (UByteP) &tmpinst;
					docreateipoly(tmpptr);
				}
			}
		}
	}
	else
	{
		POLYGON.createpoly(shape::colour);

		while (counter)
		{
			vertex[tricnt] = *((UByteP) instr_ptr);
			counter--;

			if (tricnt < 2)
			{
				tricnt++;
				instr_ptr += sizeof(UByte);
			}
			else
			{
				tricnt = 0;

				if (clockwise)
				{
					p1 = 0;
					p2 = 2;
					p3 = 1;
					clockwise = FALSE;
				}
				else
				{
					p1 = 0;
					p2 = 1;
					p3 = 2;
					clockwise = TRUE;
				}

				POLYGON.createvert(newco[vertex[p1]]);
				POLYGON.createvert(newco[vertex[p2]]);
				POLYGON.createvert(newco[vertex[p3]]);
				POLYGON.drawpoly();

				if (counter)
				{
					instr_ptr -= sizeof(UByte);
					counter+=2;
					POLYGON.createpoly(shape::colour);
				}
			}
		}
	}

	instr_ptr += sizeof(UByte);

//DeadCode RJS 23Apr97 	_Error.EmitSysErr(__FILE__":Not a real instruction yet.....(DOTRIZAGFLAT)\n");
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		dostretchpoint
//Author		Robert Slater
//Date			Mon 9 Jun 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void shape::dostretchpoint(UByte *& instr_ptr)
{
	DOSTRETCHPOINT_PTR  ptr = (DOSTRETCHPOINT_PTR )instr_ptr;
//DeadCode RJS 21Apr99 	UByteP				adptr = (UByteP) object_obj3d->AnimPtr;
	int					nokills = GlobalAdptr[ptr->killflag];
	Float				xdiff, ydiff, zdiff;
	int					killfrac,killdiff;

	newco[ptr->outpoint] = newco[ptr->minpoint];

	if (nokills)
	{
		xdiff = newco[ptr->maxpoint].bodyx.f - newco[ptr->minpoint].bodyx.f;
		ydiff = newco[ptr->maxpoint].bodyy.f - newco[ptr->minpoint].bodyy.f;
		zdiff = newco[ptr->maxpoint].bodyz.f - newco[ptr->minpoint].bodyz.f;

		xdiff /= 16.0;
		ydiff /= 16.0;
		zdiff /= 16.0;

		killfrac = nokills / 16;
		killdiff = nokills - (killfrac * 16);

		ydiff *= (killfrac+1);
		xdiff *= (killdiff+1);
		zdiff *= (killdiff+1);

		newco[ptr->outpoint].bodyx.f += xdiff;
		newco[ptr->outpoint].bodyy.f += ydiff;
		newco[ptr->outpoint].bodyz.f += zdiff;

		_matrix.SetClipFlags(newco[ptr->outpoint]);

		_matrix.body2screen(newco[ptr->outpoint]);
	}

	instr_ptr += sizeof(DOSTRETCHPOINT);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		dostretchmap
//Author		Robert Slater
//Date			Mon 9 Jun 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void shape::dostretchmap(UByte *& instr_ptr)
{
	DOSTRETCHMAP_PTR ptr = (DOSTRETCHMAP_PTR )instr_ptr;
//DeadCode RJS 21Apr99 	UByteP			 adptr = (UByteP) object_obj3d->AnimPtr;
	int				 nokills = GlobalAdptr[ptr->killflag];
	Float			 xdiff, ydiff, zdiff;
	int				 killfrac,killdiff;

	newco[ptr->outpoint] = newco[ptr->minpoint];

	if (nokills)
	{
		xdiff = newco[ptr->maxpoint].ix - newco[ptr->minpoint].ix;
		ydiff = newco[ptr->maxpoint].iy - newco[ptr->minpoint].iy;

		xdiff /= 16.0;
		ydiff /= 16.0;

		killfrac = nokills / 16;
		killdiff = nokills - (killfrac * 16);

		ydiff *= (killfrac+1);
		xdiff *= (killdiff+1);
	   //	zdiff *= (killdiff+1);	   //NOT INITIALISED!!!

		newco[ptr->outpoint].ix += xdiff;
		newco[ptr->outpoint].iy += ydiff;
	}



	instr_ptr += sizeof(DOSTRETCHMAP);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		doflipvector
//Author		Robert Slater
//Date			Wed 30 Jul 1997
//
//Description	Negates known vector intensity for two-sided flat polys
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::doflipvector(UByte *& instr_ptr)		//PD 13Nov97
{
	DOFLIPVECTOR_PTR ptr=(DOFLIPVECTOR_PTR )instr_ptr;
	DoPointStruc& dp=newco[ptr->vertex];
	dp.intensity=256-dp.intensity;//RJS 13Jul98
//DeadCode PD 25Aug98 	dp.specular=256-dp.specular;
	if (dp.intensity<0) dp.intensity=0;

	SLong temp=dp.specular;
	dp.specular=dp.specFlip;
	dp.specFlip=temp;

	instr_ptr+=sizeof(DOFLIPVECTOR);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		doflipnvec
//Author		Robert Slater
//Date			Wed 30 Jul 1997
//
//Description	Negates known vector intensities for two-sided flat polys
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::doflipnvec(UByte *& instr_ptr)			//PD 13Nov97
{
	DOFLIPNVEC_PTR ptr=(DOFLIPNVEC_PTR )instr_ptr;
	DoPointStruc* pDp=newco+ptr->vertex;
	int nopoints=ptr->nopoints;
	for (int count=0; count < nopoints; count++){
		DoPointStruc& dp=*pDp++;
		dp.intensity=256-dp.intensity;//RJS 13Jul98
		if (dp.intensity<0) dp.intensity=0;

//DeadCode PD 25Aug98 		dp.specular=256-dp.specular;

		SLong temp=dp.specular;
		dp.specular=dp.specFlip;
		dp.specFlip=temp;

	}
	instr_ptr+=sizeof(DOFLIPNVEC);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		domorphpoint
//Author		Robert Slater
//Date			Thu 4 Dec 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void shape::domorphpoint(UByte *& instr_ptr)
{
	DOMORPHPOINT_PTR  ptr = (DOMORPHPOINT_PTR )instr_ptr;
//DeadCode RJS 21Apr99 	UByteP				adptr = (UByteP) object_obj3d->AnimPtr;
	DOPOINT			ptr2;
	UByteP			instptr2 = (UByteP) &ptr2;
	SLong			TotDist;
	SWord			sin_ang,cos_ang;
	SLong			xdelta, ydelta, zdelta;
	UByteP			timedeltap = &GlobalAdptr[ptr->framecntoffset];//RJS 21Apr99
	UWord			timedelta = *((UWordP)timedeltap);

	xdelta = (timedelta*(ptr->mxcoord - ptr->xcoord))/ptr->growtime;
	ydelta = (timedelta*(ptr->mycoord - ptr->ycoord))/ptr->growtime;
	zdelta = (timedelta*(ptr->mzcoord - ptr->zcoord))/ptr->growtime;

	ptr2.vertex = ptr->vertex;
	ptr2.xcoord = ptr->xcoord + xdelta;
	ptr2.ycoord = ptr->ycoord + ydelta;
	ptr2.zcoord = ptr->zcoord + zdelta;

	if (ptr->haswind)
	{
		//rdh need to change to MiG Alley wind
//		TotDist = (Timer_Code.FRAMETIME * MMC.wind.speed)/10;
//		Math_Lib.high_sin_cos((ANGLES )MMC.wind.direction,sin_ang,cos_ang);
//		xdelta = (TotDist*sin_ang)>>15;
//		zdelta = (TotDist*cos_ang)>>15;
//
//		ptr2.xcoord += xdelta;
//		ptr2.zcoord += zdelta;
	}

	dopoint(instptr2);

	instr_ptr += sizeof(DOMORPHPOINT);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		domorphnpoints
//Author		Robert Slater
//Date			Mon 8 Dec 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::domorphnpoints(UByte *& instr_ptr)
{
	DOMORPHNPOINTS_PTR  ptr = (DOMORPHNPOINTS_PTR )instr_ptr;
	MORPHNNEXT_PTR		ptr2;
//DeadCode RJS 21Apr99 	UByteP				adptr = (UByteP) object_obj3d->AnimPtr;
	DOPOINT			ptr3;
	UByteP			instptr2 = (UByteP) &ptr3;
	SLong			TotDist;
	SWord			sin_ang,cos_ang;
	SLong			xdelta, ydelta, zdelta;
	SLong			wxdelta, wydelta, wzdelta;
	UByteP			timedeltap = &GlobalAdptr[ptr->framecntoffset];//RJS 21Apr99
	UWord			timedelta = *((UWordP)timedeltap);
	ULong			count;
	UWord			vertex = ptr->startvertex;
	SLong			timefrac = (timedelta<<13)/ptr->growtime;

//	if (ptr->haswind)
//	{
//		//rdh need to change to MiG Alley wind
//		MMC.wind.speed = 100;
//		TotDist = (Timer_Code.FRAMETIME * MMC.wind.speed)/10;
//		Math_Lib.high_sin_cos((ANGLES )MMC.wind.direction,sin_ang,cos_ang);
//		wxdelta = (TotDist*sin_ang)>>15;
//		wzdelta = (TotDist*cos_ang)>>15;
//	}
//	else
	{
		wxdelta = 0;
		wydelta = 0;
		wzdelta = 0;
	}

	instr_ptr += sizeof(DOMORPHNPOINTS);

	for (count=0; count < ptr->nopoints; count++)
	{
		ptr2 = (MORPHNNEXT_PTR) instr_ptr;

		xdelta = (timefrac*(ptr2->mxcoord - ptr2->xcoord))>>13;
		ydelta = (timefrac*(ptr2->mycoord - ptr2->ycoord))>>13;
		zdelta = (timefrac*(ptr2->mzcoord - ptr2->zcoord))>>13;

		ptr3.vertex = vertex;
		ptr3.xcoord = ptr2->xcoord + xdelta;
		ptr3.ycoord = ptr2->ycoord + ydelta;
		ptr3.zcoord = ptr2->zcoord + zdelta;

		if (ptr3.ycoord)
		{
			ptr3.xcoord += wxdelta;
			ptr3.ycoord += wydelta;
			ptr3.zcoord += wzdelta;
		}

		instptr2 = (UByteP) &ptr3;
		dopoint(instptr2);

		instr_ptr += sizeof(MORPHNNEXT);
		vertex++;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		douserealtime
//Author		Robert Slater
//Date			Wed 10 Dec 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::douserealtime(UByte *& instr_ptr)
{
	DOUSEREALTIME_PTR  ptr = (DOUSEREALTIME_PTR )instr_ptr;
//DeadCode RJS 21Apr99 	UByteP				adptr = (UByteP) object_obj3d->AnimPtr;
	ULongP			btimep = (ULongP) &GlobalAdptr[ptr->birthtimeoffset];//RJS 21Apr99
	ULong			btime = *btimep;

	if (btime == 0)												//RJS 16Nov98
		*btimep = View_Point->TimeOfDay();						//RJS 16Nov98

	instr_ptr += sizeof(DOUSEREALTIME);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		dotimerphase
//Author		Robert Slater
//Date			Wed 10 Dec 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::dotimerphase(UByte *& instr_ptr)
{
	DOTIMERPHASE_PTR  ptr = (DOTIMERPHASE_PTR )instr_ptr;
//DeadCode RJS 21Apr99 	UByteP				adptr = (UByteP) object_obj3d->AnimPtr;
	ULongP			btimep = (ULongP) &GlobalAdptr[ptr->birthtimeoffset];//RJS 21Apr99
	UWordP			dtimep = (UWordP) &GlobalAdptr[ptr->deltatimeoffset];//RJS 21Apr99
	ULong			btime = *btimep;
	UWord			dtime = *dtimep;
	UWord			nophases = ptr->nophases;
	UWord			count;
	ULong			phasetdelta;
	UWord			lowtime = 0;
	ULong			tdelta;
	TPHASESTEP_PTR	ptr2;
	UByteP			instr_ptr2 = instr_ptr;

	tdelta = View_Point->TimeOfDay() - btime;

	instr_ptr2 += sizeof(DOTIMERPHASE);
	ptr2 = (TPHASESTEP_PTR) instr_ptr2;
	instr_ptr2 += (nophases * sizeof(TPHASESTEP));

	for (count=0; count < nophases; count++)
	{
		phasetdelta = ptr2->timedelta;
		if (phasetdelta == 65535)
			tdelta = 65534;

		if (	(tdelta >= lowtime)
			&&	(tdelta < phasetdelta)	)
		{
			*dtimep = (UWord)(tdelta - lowtime);
			instr_ptr += ptr2->objjump;
			instr_ptr2 = instr_ptr;
			break;
		}

		lowtime = phasetdelta;
		ptr2++;
	}

	instr_ptr = instr_ptr2;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		dowheeldamage
//Author		Robert Slater
//Date			Thu 18 Dec 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::dowheeldamage(UByte *& instr_ptr)
{
	DOWHEELDAMAGE_PTR  ptr = (DOWHEELDAMAGE_PTR )instr_ptr;
//DeadCode RJS 21Apr99 	UByteP				adptr = (UByteP) object_obj3d->AnimPtr;
	UByteP				oldinstr_ptr = instr_ptr;
	MinAnimData*		mad = (MinAnimData*) GlobalAdptr;

	if (mad->itemstate != DEAD)
	{
		if (GlobalAdptr[ptr->suspoffset])
		{
			if (GlobalAdptr[ptr->underoffset])
			{
				ULong	damage = (GlobalAdptr[ptr->suspoffset] * ((GlobalAdptr[ptr->underoffset]<<8)/ptr->animmax))>>8;
				if (damage > BS_DEAD)
					damage = BS_DEAD;

				SHAPE.ForceDamage(	object_obj3d->ItemPtr,
									object_obj3d->ItemPtr,
									&GlobalAdptr[ptr->damageoffset],//RJS 21Apr99
									(BitStates) damage	);

/*				if (damage >= ptr->threshold)
				{
					if (ptr->subdamageoffset)
					{
						damage -= ptr->threshold;
						damage += GlobalAdptr[ptr->subdamageoffset];
						if (damage > BS_DEAD)
							damage = BS_DEAD;


						SHAPE.ForceDamage(	object_obj3d->ItemPtr,
											&GlobalAdptr[ptr->subdamageoffset],
											(BitStates) damage	);
					}
				}*/
			}
		}

		instr_ptr = oldinstr_ptr;
	}
	instr_ptr += sizeof(DOWHEELDAMAGE);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		doblobline
//Author		Robert Slater
//Date			Thu 11 Dec 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::doblobline(UByte *& instr_ptr)
{
	LINETYPE	ltLine;
	struct		vertex	startVertex,endVertex;

 	SWord start_vertex,end_vertex;								//PD 08Jan96
	Float	z0,z1;
 	
 	DOBLOBLINE_PTR ptr = (DOBLOBLINE_PTR )instr_ptr;
 
 	start_vertex = (SWord )ptr->start_vertex;					//RJS 10Mar97
 	end_vertex	 = (SWord )ptr->end_vertex;					//RJS 10Mar97
 
	ltLine.ltType 			= LineType::LT_PlainColour;

	ltLine.lpStartVertex 	= &startVertex;
	startVertex.bx			= newco[start_vertex].bodyx;
	startVertex.by			= newco[start_vertex].bodyy;
	startVertex.bz			= newco[start_vertex].bodyz;
	startVertex.clipFlags	= newco[start_vertex].clipFlags;	//PD 25Nov98
	//startVertex.scalefactor	= newco[start_vertex].scalefactor;

	ltLine.lpEndVertex 		= &endVertex;
	endVertex.bx			= newco[end_vertex].bodyx;
	endVertex.by			= newco[end_vertex].bodyy;
	endVertex.bz			= newco[end_vertex].bodyz;
	endVertex.clipFlags		= newco[end_vertex].clipFlags;		//PD 25Nov98
	//endVertex.scalefactor	= newco[end_vertex].scalefactor;

	ltLine.colour			= shape::colour;

	if (current_screen->DoHardLine(&ltLine)==FALSE)
	{
		z0 = newco[start_vertex].bodyz.f;
 		z1 = newco[end_vertex].bodyz.f;
 	
 		current_screen->zclipline(newco[start_vertex],newco[end_vertex]);
 	
 		if ((z0>0)&&(z1>0))
 		{
 			_matrix.body2screen(newco[start_vertex]);					//PD 25Jul96
 			_matrix.body2screen(newco[end_vertex]);						//PD 25Jul96

  			SHAPE.PlainBlobLine(start_vertex,end_vertex,ptr->maxradius);
  		}
	}
	instr_ptr += sizeof(DOBLOBLINE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		dolight
//Author		Robert Slater
//Date			Thu 18 Dec 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::dolight(UByte *& instr_ptr)
{
	DOLIGHT_PTR	ptr = (DOLIGHT_PTR) instr_ptr;
//DeadCode RJS 21Apr99 	UByteP		adptr = (UByteP) object_obj3d->AnimPtr;
	UWord		frametime;
	LIGHTDATA_PTR	ldataptr = (LIGHTDATA_PTR) SHAPE.GetLightDataPtr((ShapeNum)object_obj3d->Shape,ptr->lightoffset);

	if (ldataptr)
	{
//DeadCode RJS 15Feb99 		DOPOINT dopointno;
//DeadCode RJS 15Feb99 		UByteP	instr_ptr2 = (UByteP) &dopointno;
//DeadCode RJS 15Feb99 		Colour	colon = (Colour) ldataptr->colouron;
//DeadCode RJS 15Feb99 		Colour	coloff = (Colour) ldataptr->colouroff;
//DeadCode RJS 15Feb99 		DOSETCOLOUR256	tmpinst3;								//RJS 06Jan98
//DeadCode RJS 15Feb99 		UByteP			tmpinstptr;
//DeadCode RJS 15Feb99 		Bool			issmooth = FALSE;
//DeadCode RJS 15Feb99 		UWord			radius = ptr->radius;
//DeadCode RJS 15Feb99 
//DeadCode RJS 15Feb99 		tmpinst3.spread = 0;									//RJS 06Jan98
//DeadCode RJS 15Feb99 		tmpinst3.imap = 0xFF;									//RJS 06Jan98
//DeadCode RJS 15Feb99 		tmpinst3.basecolour = coloff<<1;						//RJS 06Jan98
//DeadCode RJS 15Feb99 
//DeadCode RJS 15Feb99 		if (ptr->animoff)
//DeadCode RJS 15Feb99 		{
//DeadCode RJS 15Feb99 			if (ptr->isword)
//DeadCode RJS 15Feb99 				frametime = *((UWordP)&adptr[ptr->animoff]);
//DeadCode RJS 15Feb99 			else
//DeadCode RJS 15Feb99 				frametime = adptr[ptr->animoff];
//DeadCode RJS 15Feb99 
//DeadCode RJS 15Feb99 			if (frametime >= ptr->timeoff)
//DeadCode RJS 15Feb99 			{
//DeadCode RJS 15Feb99 				if (frametime < ptr->timeup)
//DeadCode RJS 15Feb99 					tmpinst3.basecolour = coloff<<1;			//RJS 06Jan98
//DeadCode RJS 15Feb99 				else
//DeadCode RJS 15Feb99 				{
//DeadCode RJS 15Feb99 					if (frametime < ptr->timeon)
//DeadCode RJS 15Feb99 					{
//DeadCode RJS 15Feb99 						tmpinst3.basecolour = colon<<1;			//RJS 06Jan98
//DeadCode RJS 15Feb99 						radius += 6;
//DeadCode RJS 15Feb99 						issmooth = TRUE;
//DeadCode RJS 15Feb99 					}
//DeadCode RJS 15Feb99 				}
//DeadCode RJS 15Feb99 			}
//DeadCode RJS 15Feb99 		}
//DeadCode RJS 15Feb99 
//DeadCode RJS 15Feb99 		tmpinstptr = (UByteP) &tmpinst3;						//RJS 06Jan98
//DeadCode RJS 15Feb99 		dosetcolour256(tmpinstptr);								//RJS 06Jan98
//DeadCode RJS 15Feb99 
//DeadCode RJS 15Feb99 		if (ptr->radius)
//DeadCode RJS 15Feb99 		{
//DeadCode RJS 15Feb99 			dopointno.xcoord = ldataptr->xpos;
//DeadCode RJS 15Feb99 			dopointno.ycoord = ldataptr->ypos;
//DeadCode RJS 15Feb99 			dopointno.zcoord = ldataptr->zpos;
//DeadCode RJS 15Feb99 			dopointno.vertex = 0;
//DeadCode RJS 15Feb99 
//DeadCode RJS 15Feb99 			dopoint(instr_ptr2);
//DeadCode RJS 15Feb99 
//DeadCode RJS 15Feb99 			SHAPE.drawsphere(	0,
//DeadCode RJS 15Feb99 	 							radius,
//DeadCode RJS 15Feb99  								shape::colour,
//DeadCode RJS 15Feb99  								0,
//DeadCode RJS 15Feb99  								1,
//DeadCode RJS 15Feb99  								4,
//DeadCode RJS 15Feb99  								issmooth,
//DeadCode RJS 15Feb99 								0,
//DeadCode RJS 15Feb99 								LUM_MAX,
//DeadCode RJS 15Feb99 								0);								//RJS 21Jan98
//DeadCode RJS 15Feb99 		}
		DOPOINT dopointno;
		UByteP	instr_ptr2 = (UByteP) &dopointno;
		SWord	minx,miny,maxx,maxy;
		UWord	radius = ptr->radius;

		minx = ptr->minx;
		miny = ptr->miny;
		maxx = ptr->minx + ptr->width;
		maxy = ptr->miny + ptr->height;

		if (ptr->animoff)
		{
			if (ptr->isword)
				frametime = *((UWordP)&GlobalAdptr[ptr->animoff]);
			else
				frametime = GlobalAdptr[ptr->animoff];

			if (frametime >= ptr->timeoff)
			{
				if (frametime < ptr->timeup)
				{
					//Fade...

//hmmm...					oldGlobalAlpha = current_screen->DoSetGlobalAlpha();
				}
				else
				{
					if (frametime < ptr->timeon)
					{
						//On...
						ImageMapDescPtr imptr;
						SLong			nofx;
						SLong			stepy, stepx;

						imptr = Image_Map.GetImageMapPtr((ImageMapNumber)ptr->imagemap);
						
						nofx = imptr->w / ptr->width;

						stepy = 1 / nofx;
						stepx = 1 - (stepy*nofx);

						minx += stepx*ptr->width;
						miny += stepy*ptr->height;

						maxx = minx + ptr->width;
						maxy = miny + ptr->height;

						radius += 3;
					}
				}
			}
		}

		if (ptr->radius)
		{
			dopointno.vertex = 0;
			dopointno.xcoord = ldataptr->xpos;
			dopointno.ycoord = ldataptr->ypos;
			dopointno.zcoord = ldataptr->zpos;

			dopoint(instr_ptr2);

			SHAPE.imapsphere(0,radius,(ImageMapNumber)ptr->imagemap,minx,miny,maxx,maxy);
		}
	}

	instr_ptr += sizeof(DOLIGHT);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		dolighttimer
//Author		Robert Slater
//Date			Tue 6 Jan 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::dolighttimer(UByte *& instr_ptr)
{
	DOLIGHTTIMER_PTR	ptr = (DOLIGHTTIMER_PTR) instr_ptr;
//DeadCode RJS 21Apr99 	UByteP				adptr = (UByteP) object_obj3d->AnimPtr;
	UWordP				wordptr = (UWordP)&GlobalAdptr[ptr->animoff];
	UWord				frametime;
	LightTimerTypes		timertype = (LightTimerTypes)ptr->timertype;
	Bool				islit = TRUE;

	if (	(timertype&LGT_ONLY_DARK)
		&&	!Three_Dee.lightson			)
	{
		frametime = 0;
	}
	else
	{
		if (ptr->isword)
			frametime = *wordptr;
		else
			frametime = GlobalAdptr[ptr->animoff];				//RJS 21Apr99

		//frametime of 0 means switched off...					//DAW 17Feb99
		if (frametime && (timertype&LGT_PERIODIC))				//DAW 17Feb99
		{
			frametime += View_Point->FrameTime();
			if (frametime > ptr->duration)
				frametime = Timer_Code.FRAMETIME;				//DAW 17Feb99
		}
	}

	if (ptr->isword)
		*wordptr = frametime;
	else
		GlobalAdptr[ptr->animoff] = frametime;					//RJS 21Apr99

	instr_ptr += sizeof(DOLIGHTTIMER);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		dodigitdial
//Author		Robert Slater
//Date			Thu 8 Jan 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::dodigitdial(UByte *& instr_ptr)
{
	DODIGITDIAL_PTR	ptr = (DODIGITDIAL_PTR) instr_ptr;
//DeadCode RJS 21Apr99 	UByteP				adptr = (UByteP) object_obj3d->AnimPtr;
	UWordP				wordptr = (UWordP)&GlobalAdptr[ptr->animoff];
	Float				dx, dy, dz;
	Float				dx2, dy2, dz2;
	DoPointStruc		dopoint0, dopoint1, dopoint2, dopoint3;
	int					i;
	int					nodigits = ptr->nodigits;
	ImageMapNumber		imapno;
	SWord				minx,miny,maxx,maxy;
	UWord				theno = *wordptr;
	UByteP				digits;
	UWord				thenoleft;
	int					dcnt = 0;
	Float				digdiv = 1.0 / Float(nodigits);

	digits = new UByte[nodigits];
	dcnt = nodigits-1;

	while (dcnt > -1)
	{
		thenoleft = theno;
		theno /= 10;

		thenoleft -= (theno*10);

		digits[dcnt--] = thenoleft;
	}

	imapno = (ImageMapNumber) ptr->imagemap;
	ImageMapDescPtr imptr = Image_Map.GetImageMapPtr(imapno);
	SLong	noxframes = imptr->w / ptr->width;
	SLong	stepy,stepx;

	dx = newco[ptr->vertex1].bodyx.f - newco[ptr->vertex0].bodyx.f;
	dy = newco[ptr->vertex1].bodyy.f - newco[ptr->vertex0].bodyy.f;
	dz = newco[ptr->vertex1].bodyz.f - newco[ptr->vertex0].bodyz.f;

	dx2 = newco[ptr->vertex2].bodyx.f - newco[ptr->vertex3].bodyx.f;
	dy2 = newco[ptr->vertex2].bodyy.f - newco[ptr->vertex3].bodyy.f;
	dz2 = newco[ptr->vertex2].bodyz.f - newco[ptr->vertex3].bodyz.f;

	dx *= digdiv;
	dy *= digdiv;
	dz *= digdiv;

	dx2 *= digdiv;
	dy2 *= digdiv;
	dz2 *= digdiv;

	dopoint1 = newco[ptr->vertex0];
	dopoint2 = newco[ptr->vertex3];

	maxx = ptr->width;
	minx = 0;

	for (i=0; i < nodigits; i++)
	{
		stepy = digits[i]/noxframes;
		stepx = digits[i] - (stepy*noxframes);

		miny = 32 + (stepy * ptr->height);		//shit cheat!
		minx = stepx * ptr->width;
		maxx = minx + ptr->width;
		maxy = miny + ptr->height;

		dopoint0 = dopoint1;
		dopoint1.bodyx.f += dx;
		dopoint1.bodyy.f += dy;
		dopoint1.bodyz.f += dz;

		dopoint3 = dopoint2;
		dopoint2.bodyx.f += dx2;
		dopoint2.bodyy.f += dy2;
		dopoint2.bodyz.f += dz2;

		_matrix.SetClipFlags(dopoint0);
		_matrix.SetClipFlags(dopoint1);
		_matrix.SetClipFlags(dopoint2);
		_matrix.SetClipFlags(dopoint3);

 		_matrix.body2screen(dopoint0);
 		_matrix.body2screen(dopoint1);
 		_matrix.body2screen(dopoint2);
 		_matrix.body2screen(dopoint3);

		// draw it.....

		POLYGON.createpoly(imapno);								
 																
  		POLYGON.createvert(dopoint3,minx,miny);					
		POLYGON.createvert(dopoint2,maxx,miny);					
		POLYGON.createvert(dopoint1,maxx,maxy);					
  		POLYGON.createvert(dopoint0,minx,maxy);					

		POLYGON.drawpoly();
	}

	delete digits;

	instr_ptr += sizeof(DODIGITDIAL);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		donianimverts
//Author		Robert Slater
//Date			Tue 13 Jan 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::donianimverts(UByte *& instr_ptr)
{
	DONIANIMVERTS_PTR	ptr = (DONIANIMVERTS_PTR) instr_ptr;
//DeadCode RJS 21Apr99 	UByteP				adptr = (UByteP) object_obj3d->AnimPtr;
	NEXTMAP_PTR			mapit;
	int					counter;
	int					vertex;
	int					i;
	UByte				frameno = GlobalAdptr[ptr->animoff];
	int					minx, miny;
	int					nofx;
	int					stepx,stepy;
	int					animscale = ptr->factor;

	if (ptr->isthresh)
	{
		if (frameno > animscale)
			frameno = 1;
		else
			frameno = 0;
	}
	else
	{
		frameno /= animscale;
		if (ptr->mapscale)
		{
			UByte	totframes = frameno;

			frameno /= ptr->mapscale;
			frameno = totframes - (frameno * ptr->mapscale);
		}
	}

	nofx = ptr->noxframes;

	stepy = frameno/nofx;
	stepx = frameno - (stepy*nofx);

	miny = stepy * ptr->framewy;
	minx = stepx * ptr->framewx;

	instr_ptr += sizeof(DONIANIMVERTS);

	counter = ptr->count;
	vertex = ptr->vertex;

	for (i=0; i < counter; i++)
	{
		mapit = (NEXTMAP_PTR) instr_ptr;

		newco[vertex].ix = minx + mapit->ix;
		newco[vertex].iy = miny + mapit->iy;

		vertex++;
		instr_ptr += sizeof(NEXTMAP);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		dosetluminosity
//Author		Robert Slater
//Date			Tue 20 Jan 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::dosetluminosity(UByte *& instr_ptr)
{
	DOSETLUMINOSITY_PTR	ptr = (DOSETLUMINOSITY_PTR) instr_ptr;
//DeadCode RJS 21Apr99 	UByteP				adptr = (UByteP) object_obj3d->AnimPtr;
	UByte				depth;

	if (ptr->animoff)
		depth = GlobalAdptr[ptr->animoff] / ptr->animscale;
	else
		depth = ptr->brightness;

	if (depth > LUM_MAX)
		depth == LUM_MAX;

	current_screen->SetLuminosity(depth);

	instr_ptr += sizeof(DOSETLUMINOSITY);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		dobitsoffcock
//Author		Robert Slater
//Date			Fri 23 Jan 1998
//
//Description	Check for cockpit detail....
//				If detail bit flag is set, then it means we want to skip
//				the draw.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::dobitsoffcock(UByte *& instr_ptr)
{
	DOBITSOFFCOCK_PTR	ptr = (DOBITSOFFCOCK_PTR )instr_ptr;
//DeadCode RJS 21Apr99 	UByteP	adptr = (UByteP) object_obj3d->AnimPtr;
	ULong	flag = *((ULongP)&GlobalAdptr[ptr->animflag]);

	flag >>= ptr->bitflag;
	flag &= 1;

	if (!flag)
		instr_ptr += ptr->offset;
	else
		instr_ptr += sizeof(DOBITSOFFCOCK);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		doheathaze
//Author		Robert Slater
//Date			Fri 30 Jan 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::doheathaze(UByte *& instr_ptr)
{
	DOHEATHAZE_PTR	ptr = (DOHEATHAZE_PTR) instr_ptr;
	SWord			colour;
	SWord			radius = ptr->radius;

	if (!current_screen->DoingHardware3D())
	{
		colour = Math_Lib.rnd();
		SHAPE.DrawHeatHaze(ptr->vertex,radius,colour);
	}
	else
	{
//DeadCode RJS 21Apr99 		UByteP			adptr = (UByteP) object_obj3d->AnimPtr;
		SWord			minx, maxx;
		SWord			miny, maxy;
		SWord			width, height;
	
		radius /= 2;

		minx = ptr->minx;							
		miny = ptr->miny;						 	
		width = ptr->width;							
		height = ptr->height;						

		SHAPE.AnimMap(GlobalAdptr,ptr->image,ptr->animflag,ptr->animscale,minx,miny,width,height);

		maxx = minx + width - 1;							
		maxy = miny + height;	

		SHAPE.imapsphere(ptr->vertex,radius,(ImageMapNumber)ptr->image,minx,miny,maxx,maxy);
	}

	instr_ptr += sizeof(DOHEATHAZE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		doifhard3d
//Author		Robert Slater
//Date			Wed 4 Feb 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::doifhard3d(UByte *& instr_ptr)
{
	DOIFHARD3D_PTR	ptr = (DOIFHARD3D_PTR) instr_ptr;

//	if (doingHW3D)												//PD 19Jun98
		instr_ptr += ptr->offset;
//	else
//		instr_ptr += sizeof(DOIFHARD3D);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		domorphnsphrs
//Author		Robert Slater
//Date			Tue 24 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::domorphnsphrs(UByte *& instr_ptr)
{
	DOMORPHNSPHRS_PTR ptr = (DOMORPHNSPHRS_PTR )instr_ptr;
	SLong		 radius;
//DeadCode RJS 21Apr99 	UByteP		adptr = (UByteP) object_obj3d->AnimPtr;
	UWord		timeframe;
	SLong		timefrac;
	int			lumtype;
	int			transp;
	int			growth = ptr->MrphGrowtime;
	int			delta;
	UByte		animflag;
	UByte		colour = ptr->colour;
	int			randcol;
	int			count = ptr->count;
	int			i = 0;
	MORPHSPHNEXT_PTR	ptr2;
	int			animscale = ptr->animscale;
	int			vertex = ptr->vertex;

	instr_ptr += sizeof(DOMORPHNSPHRS);

	lumtype = ptr->lumtype;
	transp = ptr->transp;

	timeframe = *((UWordP)&GlobalAdptr[ptr->MrphAnim]);
	timefrac = (timeframe << 15)/growth;

	delta = (timefrac*(ptr->MrphLumtype - lumtype))>>15;
	lumtype += delta;

	delta = (timefrac*(ptr->MrphTransp - transp))>>15;
	transp += delta;

	delta = (timefrac*(ptr->MrphColour - colour))>>15;
	colour += delta;

	while (i < count)
	{
		ptr2 = (MORPHSPHNEXT_PTR) instr_ptr;

		radius = ptr2->radius;

		delta = (timefrac*(ptr2->MrphRadius - radius))>>15;
		radius += delta;

		if (ptr->animflag && animscale)
		{
			animflag = GlobalAdptr[ptr->animflag];
			randcol = SHAPE.Noise(	object_obj3d->ItemPtr->World.X + animflag,
									object_obj3d->ItemPtr->World.Y + animflag,
									object_obj3d->ItemPtr->World.Z + animflag	);

			animflag++;

			randcol *= -animscale;
			randcol >>= 8;

			colour += randcol;
			GlobalAdptr[ptr->animflag] = animflag;
		}

		SHAPE.drawsphere(	vertex++,
							radius,
							colour,
							0,
							1,
							transp,
							(Bool)ptr->smooth,
							0,
							lumtype,
							0			);

		i++;
		instr_ptr += sizeof(MORPHSPHNEXT);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		domorphnsphrsimapd
//Author		Robert Slater
//Date			Thu 5 Feb 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::domorphnsphrsimapd(UByte *& instr_ptr)
{
	DOMORPHNSPHRSIMAPD_PTR ptr = (DOMORPHNSPHRSIMAPD_PTR )instr_ptr;
	SLong		 radius;
//DeadCode RJS 21Apr99 	UByteP		adptr = (UByteP) object_obj3d->AnimPtr;
	UWord		timeframe;
	SLong		timefrac;
	int			lumtype;
	int			transp;
	int			growth = ptr->MrphGrowtime;
	int			delta;
	UWord		imap;											//RJS 19Nov98
	int			randcol;
	MORPHSPHNEXT_PTR	ptr2;
	int			vertex = ptr->vertex;
	int			i = 0;
	int			count = ptr->count;
	UByte		width, height;
	UWord		frameno = 0;
	UWord		minix, miniy;
	UWord		maxix, maxiy;
	SWord		stepx,stepy;
	SWord		nofx;
	ImageMapDescPtr imptr;										//RJS 19Nov98
	UWord		jmpsize = sizeof(MORPHSPHNEXT);
	UByteP		pnt_base;
	UWord		angle;
	bool		pivoted = ptr->pivoted;							//RJS 26Nov98
	SWord		oldalpha = -1;
	UByte		fadedepth = GlobalAdptr[ptr->fadeoff];

	if (ptr->fadeoff && (fadedepth < 255))						//RJS 27Nov98
		oldalpha = current_screen->DoSetGlobalAlpha(fadedepth);	//RJS 27Nov98

	instr_ptr += sizeof(DOMORPHNSPHRSIMAPD);

	minix = ptr->minix;
	miniy = ptr->miniy;

	width = ptr->ix;
	height = ptr->iy;

	lumtype = ptr->lumtype;
	transp = ptr->transp;

	timeframe = *((UWordP)&GlobalAdptr[ptr->MrphAnim]);
	timefrac = (timeframe << 15)/growth;

	delta = (timefrac*(ptr->MrphLumtype - lumtype))>>15;
	lumtype += delta;

	delta = (timefrac*(ptr->MrphTransp - transp))>>15;
	transp += delta;

	if (ptr->animflag)
	{
		frameno = GlobalAdptr[ptr->animflag] / ptr->animscale;
		if (ptr->SwitchImagemap && (frameno >= ptr->framelimit))
		{
			frameno -= ptr->framelimit;
			imap = ptr->SwitchImagemap;
		}
		else
			imap = ptr->imagemap;

		imptr = Image_Map.GetImageMapPtr((ImageMapNumber )imap);

		nofx = imptr->w / width;				
														
		stepy = frameno / nofx;							
		stepx = frameno - (stepy*nofx);					
														
		minix += stepx * width;							
		miniy += stepy * height;
	}
	else
		imap = ptr->imagemap;

	maxix = minix + width;								
	maxiy = miniy + height;								

	if (count > 1)													//RJS 10Jul98
	{
		for (i = 0; i < count; i++)
		{
			SHAPE.AddToTree(vertex);
			vertex++;
		}
	}

	i = 0;
	vertex = ptr->vertex;

	SLong	newcnt = SHAPE.EmptyTree();										//RJS 09Jul98
	if (newcnt)
	{
		pnt_base = instr_ptr - (vertex * jmpsize);
		if (ptr->spinoff)
		{
			angle = *((UWordP)&GlobalAdptr[ptr->spinoff]);
			while (i < newcnt)
			{
				ptr2 = (MORPHSPHNEXT_PTR) (pnt_base + (SphereList[i]*jmpsize));
				
				radius = ptr2->radius;

				delta = (timefrac*(ptr2->MrphRadius - radius))>>15;
				radius += delta;

				SHAPE.imapspherespin(	SphereList[i],
										radius,
										(ImageMapNumber )imap,
										minix,
										miniy,
										maxix,
										maxiy,
										angle	);
				i++;
			}
		}
		else
		{
			while (i < newcnt)
			{
				ptr2 = (MORPHSPHNEXT_PTR) (pnt_base + (SphereList[i]*jmpsize));
				
				radius = ptr2->radius;

				delta = (timefrac*(ptr2->MrphRadius - radius))>>15;
				radius += delta;

				SHAPE.imapsphere(	SphereList[i],
									radius,
									(ImageMapNumber )imap,
									minix,
									miniy,
									maxix,
									maxiy,
									pivoted	);
				i++;
			}
		}
		instr_ptr += (count * jmpsize);
	}
	else
	{
		if (ptr->spinoff)
		{
			angle = *((UWordP)&GlobalAdptr[ptr->spinoff]);
			while (i < count)
	 		{
	 			ptr2 = (MORPHSPHNEXT_PTR) instr_ptr;
 
	 			radius = ptr2->radius;
 
 				delta = (timefrac*(ptr2->MrphRadius - radius))>>15;
 				radius += delta;
 
				SHAPE.imapspherespin(	vertex++,
										radius,
										(ImageMapNumber )imap,
										minix,
										miniy,
										maxix,
										maxiy,
										angle	);

				instr_ptr += sizeof(MORPHSPHNEXT);
 				i++;
 			}
		}
		else
		{
			while (i < count)
	 		{
	 			ptr2 = (MORPHSPHNEXT_PTR) instr_ptr;
 
	 			radius = ptr2->radius;
 
 				delta = (timefrac*(ptr2->MrphRadius - radius))>>15;
 				radius += delta;
 
				SHAPE.imapsphere(	vertex++,
									radius,
									(ImageMapNumber )imap,
									minix,
									miniy,
									maxix,
									maxiy,
									pivoted );

				instr_ptr += sizeof(MORPHSPHNEXT);
 				i++;
 			}
		}
	}																	//RJS 09Jul98

	if (oldalpha > -1)											//RJS 27Nov98
		current_screen->DoSetGlobalAlpha(oldalpha);				//RJS 27Nov98
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//				      GENERAL SUPPORT ROUTINES
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DrawSubShape
//Author		Robert Slater
//Date			Mon 3 Mar 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void	shape::DrawSubShape(UByteP	thisptr)					//RJS 01Dec97
{
	DOCALLSHAPE_PTR	ptr = (DOCALLSHAPE_PTR) thisptr;			//RJS 01Dec97
	DoPointStruc	*const	subco=new DoPointStruc[64];//RJS 02Dec97
	Obj3D			backobj3d;
	int				index;
//DeadCode DAW 07May99 	Bool			oldsubstat = IsSubShape;
	DoPointStruc	*oldco;
	FPMATRIX bupMatrix=light_matrix;			//PD 8May98
	Bool			oldsubstate = IsSubShape;

	if (subco)
	{
		backobj3d = *object_obj3d;

		object_obj3d->Shape = ptr->shape;//rjs 28aug98
		object_obj3d->IsTransient = 0;//rjs 28aug98
		object_obj3d->Body.X.f = newco[ptr->vertex].bodyx.f;
		object_obj3d->Body.Y.f = newco[ptr->vertex].bodyy.f;
		object_obj3d->Body.Z.f = newco[ptr->vertex].bodyz.f;
		object_obj3d->AngH = (Angles)ptr->hdg;
		object_obj3d->AngC = (Angles)ptr->pitch;
		object_obj3d->AngR = (Angles)ptr->roll;

		oldco = newco;												//RJS 02Dec97
		newco = subco;

		FPMATRIX_PTR	matrixbak = fpobject_matrix;
		fpobject_matrix = subMatrixP;

		IsSubShape = TRUE;
		SHAPE.draw_shape(object_obj3d);
		IsSubShape = oldsubstate;

		fpobject_matrix = matrixbak;

		newco = oldco;

		*object_obj3d = backobj3d;

//DeadCode DAW 07May99 		IsSubShape = oldsubstat;
 
		delete subco;												//RJS 02Dec97
	}
	light_matrix=bupMatrix;						//PD 8May98
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InterpLoop
//Author		Robert Slater
//Date			Wed 19 Mar 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void	shape::InterpLoop(UByteP	instr_ptr)
{
	UWord	instruction;
//	ULong	instcnt = 0;
//	struct	fart
//	{
//		SHPINST	instno;
//		UByteP	address;
//		UWord	offset;
//	};
//	fart	DInst[512];

	for(;;)
	{
		instruction = (UWord )*instr_ptr;
		instr_ptr ++;

//		DInst[instcnt].instno = (SHPINST)instruction;	//RJS 16Jun98
//		DInst[instcnt].offset = instr_ptr - shphedr;	//RJS 16Jun98
//		DInst[instcnt++].address = instr_ptr;
//		DInst[instcnt].instno = (SHPINST)0;

		if (instruction > dosetglassrangeno)
			_Error.EmitSysErr(__FILE__":Bollocks instruction!!");

		if(instruction==doretno) break;

		(*InterpTable[instruction]) (instr_ptr);

//		if (IsAircraft && current_level>=2)
//			IsAircraft|=4;

	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TestHitBoxes
//Author		Robert Slater
//Date			Mon 24 Feb 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	shape::TestHitBoxes(ItemPtr	itm, ShapeNum theShape,animptr& AnimPtr, UByteP	rsdptr)//RJS 21Apr99
{
	UByteP			instr_ptr;									//RJS 17Sep98
	Bool			go = TRUE;									//RJS 17Sep98
	UWord			instruction;								//RJS 17Sep98
	ShapeDescPtr	sdptr = (ShapeDescPtr) rsdptr;				//RJS 17Sep98
																//RJS 17Sep98
	damage_ItemPtr = itm;										//RJS 17Sep98
	damage_AnimPtr = AnimPtr;									//RJS 17Sep98
	damage_Shape = theShape;									//RJS 16Nov98
	damage_Sdptr = (UByteP) SHAPESTUFF.GetShapePtr(itm->shape);	//RJS 16Nov98
																//RJS 17Sep98
	CollisionOn = FALSE;										//RJS 17Sep98
	HitThisOffset = 0;											//RJS 17Sep98
	DamageNow = FALSE;											//RJS 17Sep98
	CollisionCnt = 0;											//RJS 17Sep98
	_Replay.FakeCollisionOn=false;								//AMM 12Jul99
																//RJS 17Sep98
	instr_ptr = (UByteP )sdptr + sdptr->CollisionOffset;		//RJS 17Sep98
																//RJS 17Sep98
	while (go)		  											//RJS 17Sep98
	{															//RJS 17Sep98
		instruction = (UWord) *instr_ptr;						//RJS 17Sep98
																//RJS 17Sep98
		instr_ptr ++;											//RJS 17Sep98
																//RJS 17Sep98
		if (instruction > dosetglassrangeno)					//RJS 17Sep98
			_Error.EmitSysErr(__FILE__":Bad instruction in collision (%d)",instruction);//RJS 17Sep98
																//RJS 17Sep98
		if (	((instruction == doretno) && CollisionOn)		//RJS 17Sep98
			||	(instruction==doendno))							//RJS 17Sep98
			break;												//RJS 17Sep98
																//RJS 17Sep98
		if (_Replay.FakeCollisionOn)							//AMM 12Jul99
			CollisionOn=FALSE;									//AMM 12Jul99

		(*InterpTable[instruction]) (instr_ptr);				//RJS 17Sep98

		if (_Replay.FakeCollisionOn)							//AMM 12Jul99
			CollisionOn=TRUE;									//AMM 12Jul99
	}															//RJS 17Sep98
																//RJS 17Sep98
	_Replay.FakeCollisionOn=false;								//AMM 12Jul99
	CollisionOn = DamageNow;									//RJS 17Sep98
																//RJS 17Sep98
	return(CollisionOn);										//RJS 17Sep98
}





	
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ForceDamage
//Author		Robert Slater
//Date			Fri 21 Feb 1997
//
//Description	Forces a new damage state on a specified damage byte.
//				This in-turn pretends there has been a hit-box collision,
//				and executes the relevant special effects....
//
//Inputs		Item
//				Address of damage byte to hit
//				Its new state
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::ForceDamage(	ItemPtr		itm,
							ItemPtr		theShooter,			//JIM 11Mar99
  							UByteP	 	damageptr,		
 							BitStates 	whatstate,
							UByte		HitterStrength,
							Bool		commsdamage)
{
	if (*damageptr != whatstate)								//RJS 27Aug98
	{
		animptr			adptr;									//RJS 21Apr99
		UWord			offset;
		ShapeDescPtr	sdptr;
		UByteP			instr_ptr;
		Bool			go;
		UWord			instruction;
		Bool			oldcolflag;
		ULong			oldoffset;
		SLong			oldcollogcnt = ColLogCnt;				//DAW 07Apr99

		BoxCol::ResetCollisionStuff();

		BoxCol::Col_Shooter = theShooter;						//JIM 11Mar99

		oldcolflag = CollisionOn;
		oldoffset = HitThisOffset;

		adptr = itm->Anim;										//RJS 21Apr99
//DeadCode AMM 26Apr99 		animptr		damageanim = adptr;
//DeadCode AMM 26Apr99 		damageanim = damageptr;
//DeadCode AMM 26Apr99 		offset = damageanim - adptr;
		offset = adptr.Offset(damageptr);						//AMM 26Apr99
		sdptr = SHAPESTUFF.GetShapePtr(itm->shape);

		if ((sdptr->CollisionOffset != 0) && (offset != 0))
		{
			damage_ItemPtr = itm;								//RJS 17Sep98
			damage_AnimPtr = adptr;								//RJS 17Sep98
			damage_Shape = itm->shape;							//RJS 17Sep98
			damage_GrpElmt = -1;								//RJS 17Sep98
			damage_Sdptr = (UByteP) sdptr;						//RJS 17Sep98

			go = TRUE;
			HitThisOffset = offset;

			lastdamage[0] = *damageptr;
			lastdamptr = damageptr;

//DeadCode AMM 26Apr99 			*damageptr = whatstate;
			damage_ItemState = whatstate;						//AMM 26Apr99
			CommsDamage = commsdamage;
			CollisionOn = FALSE;

			BoxCol::HitterStrength = HitterStrength;

			switch (SHAPESTUFF.GetShapeScale(sdptr))				//RJS 30Mar98
			{
				case SHP_GRP:
					_Error.EmitSysErr(__FILE__":Bad shape type field (SHAPE NUMBER %d)",itm->shape);
					break;
				case SHP_1CM:
					damage_Scale = 0;										
					break;												
				case SHP_4CM:
					damage_Scale = 2;										
					break;												
				case SHP_16CM:
					damage_Scale = 4;										
					break;
			}

			instr_ptr = (UByteP )sdptr + sdptr->CollisionOffset;

			_Replay.FakeCollisionOn=false;						//AMM 12Jul99
			while (go)
			{
				instruction = (UWord) *instr_ptr;

				instr_ptr ++;
				if (instruction > dosetglassrangeno)				//RJS 11Feb98
					_Error.EmitSysErr(__FILE__":Bad instruction in collision (%d)",instruction);//RJS 11Feb98

				if (	((instruction == doretno) && CollisionOn)
					||	(instruction==doendno))
					break;

				if (_Replay.FakeCollisionOn)					//AMM 12Jul99
					CollisionOn=FALSE;							//AMM 12Jul99

				(*InterpTable[instruction]) (instr_ptr);

				if (_Replay.FakeCollisionOn)					//AMM 12Jul99
					CollisionOn=TRUE;							//AMM 12Jul99
			}

			_Replay.FakeCollisionOn=false;						//AMM 12Jul99
			if (!oldcollogcnt)									//DAW 07Apr99
			{													//DAW 07Apr99
				FixUpColLog();									//DAW 07Apr99
				BoxCol::ProcessEffectQueue(itm);				//DAW 07Apr99
			}													//DAW 07Apr99
		}

		HitThisOffset = oldoffset;
		CommsDamage = FALSE;
		CollisionOn = oldcolflag;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetGroupDeps
//Author		Robert Slater
//Date			Mon 30 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::GetGroupDeps(UByteP	inst_ptr,SLong	&nextdep, SLong &prevdep)
{
	SWord inst = *inst_ptr;

	if (inst != dogroupno)
	{
		nextdep = 0;
		prevdep = 0;
	}
	else
	{
		inst_ptr++;

		DOGROUP_PTR	temp = (DOGROUP_PTR) inst_ptr;
	
		prevdep = temp->element_prev;
		nextdep = temp->element_next;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetGroupElement
//Author		Paul.   
//Date			Fri 8 Mar 1996
//
//Description	
//
//Inputs		
//
//Returns	   	 0 fail,
//				 1 - 255 success, 
//
//------------------------------------------------------------------------------
SLong shape::GetGroupElement(UByte *&instr_ptr,
							ShapeNum& shape,
							SLong& x, SLong& y, SLong& z,
							SLong range,
							UByteP	*PrevIptr,
							SWordP	heading,
							UByteP	*NextIptr	)
{
	SWord	inst;
	SLong	priority;											//RJS 14Nov96

	inst = (SWord )*instr_ptr;
	instr_ptr ++;

	if(inst!=dogroupno)
		return(0);

	DOGROUP_PTR temp = (DOGROUP_PTR)instr_ptr;

	shape = (ShapeNum )temp->shapenum;

	x = temp->xoffset;
	y = temp->yoffset;
	z = temp->zoffset;
	priority = temp->element_number;							//RJS 27Feb98
	if (PrevIptr)
		*PrevIptr = (UByteP)temp;
	if (heading)
		*heading = temp->angle;

	temp++;

	instr_ptr = (UByte *)temp;
	if (NextIptr)												//RJS 30Jun99
	{
		if (*instr_ptr == dogroupno)
			*NextIptr = (instr_ptr + 1);
		else
			*NextIptr = NULL;
	}

	return(priority);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetLiveElement
//Author		Jim Taylor
//Date			Wed 16 Oct 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
int shape::GetLiveElementPos(int num, ItemPtr itm, SLong& x, SLong& y, SLong& z)
{
	ShapeDescPtr sdptr,newshpp;
	SLong	ret_val;
	SByte	priority;											//RJS 22Nov96
	int		actualeltnum=0;
	sdptr = SHAPESTUFF.GetShapePtr(itm->shape);
	ShapeNum	newshp;
	if (SHAPESTUFF.GetShapeScale(sdptr)==SHP_GRP)				//JIM 06Sep96
	{
//DeadCode RJS 21Apr99 		UByteP	animdataptr = (UByteP )itm->Anim;
		MinAnimData*	aptr = (MinAnimData*) itm->Anim;			  //MS 06/05/99
		UByteP	li,instr_ptr = (UByteP )sdptr + sdptr->liveshpref;
		while ((priority = GetGroupElement(instr_ptr,newshp,x,y,z))!=0 )//RJS 22Nov96
		{
			actualeltnum++;
			if ((aptr->itemstate!=DEAD) && priority < 0)		//RJS 22Nov96
			{
				if (num==0)	return(actualeltnum);
				num--;
			}
			aptr=(MinAnimData*)((int)aptr+GetElementAnimOffset(newshp));//RJS 20Nov97
		}
		x=y=z=0;
		return(0);
	}
	else
	{
		x=y=z=0;
		if (itm->Status.size==FORMATIONSIZE)
		{
			if (itm->Status.deadtime)
				num++;
			FormationItemPtr i2=*itm;

			{
				FormationItemPtr i3=i2;
//Old_Code PD 09Dec96 				while (i3 && !i3->uniqueID.deaded && num--)
//Old_Code PD 09Dec96 				{
//Old_Code PD 09Dec96 					i2=i3;
//Old_Code PD 09Dec96 					i3=i3->follower;
//Old_Code PD 09Dec96 				}

				while (i3)
				{
					if (!i3->Status.deadtime)
					{
						num--;
					}
					if (num<=0)	break;
					i2=i3;
					i3=i3->follower;
				}

				if (i3)
					i2=i3;
			}

			if (i2)
			{
				x=itm->World.X-i2->World.X;
				y=itm->World.Y-i2->World.Y;
				z=itm->World.Z-i2->World.Z;
				return(1);
			}
			else
				return(0);
		}
		if (itm->Status.deadtime)
			return(0);
		else
			return(1);
	}
}

void	TraceChain(int yoff);
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetAnimData
//Author		Paul.   
//Date			Tue 26 Mar 1996
//
//Description	Uses functional GetAnimDataSize to get size, now
//
//Inputs		The item to initialise,
//				The weapon pack to be used (if there is one)...
//
//Returns	
//
//------------------------------------------------------------------------------
SLong shape::SetAnimData(itemptr itm,SWord pack)
{
	AnimWeaponPack = pack;
	SLong	animdatasize;
	SLong	animflagsize;

	animdatasize = GetAnimDataSize(itm->shape);

	if (itm->Anim != NULL)										//RJS 21Apr99
		itm->Anim.Delete();										//RJS 21Apr99
	UByteP	p;
#ifdef DEBUG_NEW_MODE
	#undef	new
	itm->Anim = p = new (__HERE__,itm->shape) UByte[animdatasize];//DAW 25Feb00
	#define	new DEBUG_NEW
#else
	itm->Anim = p = new UByte[animdatasize];
#endif
	
	for (int i=0;i<animdatasize;i++)							//JIM 06Sep96
		p[i]=0;													//JIM 06Sep96

	animflagsize = animdatasize;
#ifndef	NDEBUG
	SetAnimDataFlags(itm->shape,itm->Anim,animflagsize);		//RJS 21Apr99
#endif
	
	InitAnimData(itm);

	return(animdatasize);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetNumberOfLaunchers
//Author		Robert Slater
//Date			Wed 21 Aug 1996
//
//Description	Calculates number of launchers in a shape
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
UByte shape::GetNumberOfLaunchers(ShapeNum shpno)
{
	ShapeDescPtr	sdptr;
//DeadCode AMM 30Jul99 	UByteP			launcher_ptr = NULL;
	UByte 			*instr_ptr;
	UWord		 	instruction, last_inst;
//DeadCode AMM 30Jul99 	Bool			go=TRUE;
	UByte			nolaunchers;
	DOLAUNCHER_PTR	lptr;

	nolaunchers = 0;

	sdptr = SHAPESTUFF.GetShapePtr(shpno);

//DeadCode AMM 30Jul99 	launcher_ptr = (UByteP )sdptr + sdptr->LauncherDataSize;

	if (sdptr->LauncherDataSize)
	{
		Bool			go=TRUE;								//AMM 30Jul99
		UByteP			launcher_ptr;							//AMM 30Jul99

		launcher_ptr = (UByteP )sdptr + sdptr->LauncherDataSize;//AMM 30Jul99

		instr_ptr = launcher_ptr;

		while (go)
		{
			instruction = (UWord )*instr_ptr;

			instr_ptr ++;
//DeadCode RJS 19Dec97 			instruction>>=1;

			if(instruction>dosetglassrangeno || instruction==0)
				_Error.EmitSysErr(__FILE__":Bad instruction in launcher size (%d)",instruction);

			if(instruction==doretno || instruction==doendno)
				go=FALSE;
			else
			{
				switch (instruction)
				{
					case dolauncherno:
						{
							lptr = (DOLAUNCHER_PTR) instr_ptr;	//RJS 09Apr98
							instr_ptr += sizeof(DOLAUNCHER);

							if (lptr->lnchrtype < LT_CONTACT)	//RJS 09Apr98
								nolaunchers++;					//RJS 09Apr98
						}
					break;
					default:
						_Error.EmitSysErr(__FILE__":Bad launcher instruction (%d)",instruction);
				}
			}

			last_inst = instruction;
		}
	}

	return(nolaunchers);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetAnimDataSizeAndCheck
//Author		Robert Slater
//Date			Fri 30 Oct 1998
//
//Description	Should never be a group......
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SLong shape::GetAnimDataSizeAndCheck(ShapeNum shpno, AnimSizes  theanim, Bool &isTrue)
{
	ShapeDescPtr	sdptr = (ShapeDescPtr) SHAPESTUFF.GetShapePtr(shpno);
	SLong			ret_val;
	SWord			animdatasize = sdptr->AnimDataSize;

	isTrue = FALSE;

	if (animdatasize > -1)									
	{
		if (animdatasize == theanim)
			isTrue = TRUE;

		switch (animdatasize)				
		{											
			case MINANIM:			RETURN(sizeof(MinAnimData));
//DeadCode RJS 21Apr99 			case EXPLODEANIM:		RETURN(sizeof(ExplodeAnimData));
			case POLYPITANIM:		RETURN(sizeof(PolyPitAnimData));
			case BLOKESANIM: 		RETURN(sizeof(BlokesAnimData));
			case WEAPANIM:			RETURN(sizeof(WeapAnimData));
			case AIRCRAFTANIM:		RETURN(sizeof(AircraftAnimData));
			case SUNANIM:			RETURN(sizeof(SunAnimData ));
//DeadCode RJS 21Apr99 			case FLAMEANIM:			RETURN(sizeof(FireAnimData ));
//DeadCode RJS 21Apr99 			case BALLOONANIM:		RETURN(sizeof(BalloonAnimData ));
			case WINDSOCANIM:		RETURN(sizeof(WindsocAnimData ));
			case BARAGEANIM:		RETURN(sizeof(BarageAnimData ));
			case MOVEGUNANIM:		RETURN(sizeof(MoveGunAnimData ));
//DeadCode RJS 21Apr99 			case FIREBALLANIM:		RETURN(sizeof(ExplodeAnimData ));
			case TANKANIM:			RETURN(sizeof(TwoGunAnimData ));
			case TRUCKANIM:			RETURN(sizeof(MoveGunAnimData ));
			case TRAINANIM:			RETURN(sizeof(TrainAnimData ));
			case TROOPANIM:			RETURN(sizeof(TroopAnimData ));
			case BRIDGEANIM:		RETURN(sizeof(MinAnimData ));//RJS 18Apr99
			case CLONEANIM:			RETURN(sizeof(CloneAnimData ));
			case FLAREANIM:			RETURN(sizeof(FlareAnimData ));
			case THUGANIM:			RETURN(sizeof(ThugAnimData ));
			case MISSILEANIM:		RETURN(sizeof(MissileAnimData ));
			case DEBRISANIM:		RETURN(sizeof(DebrisAnimData ));//RJS 20Jan99
			case SMOKETRAILANIM:	RETURN(sizeof(SmokeTrailAnimData ));//RJS 21Jan99
			case PARACHUTEANIM:		RETURN(sizeof(ParachuteAnimData ));//RJS 25Mar99
			case LAUNCHERANIM:		RETURN(sizeof(LauncherAnimData ));//RJS 16Apr99
			default:	//unique number below 4					
				RETURN(3);										
		}
	}
	else
		return(-animdatasize);	
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetAnimDataSize
//Author		Paul.				//JIM 06Sep96
//Date			Tue 26 Mar 1996
//
//Description	Modified so that correct value for groups is also returned//JIM 06Sep96
//				Also fills launcher count for group, but doesn't allocate any memory!//JIM 06Sep96
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SLong shape::GetAnimDataSize(ShapeNum shpno)
{
	ShapeDescPtr sdptr,newshpp;
	SLong	ret_val;
	SWord	animdatasize;										//RJS 30Jun97

	sdptr = SHAPESTUFF.GetShapePtr(shpno);
	ShapeNum	newshp;

	if (SHAPESTUFF.GetShapeScale(sdptr)==SHP_GRP)				//JIM 06Sep96
		if (sdptr->AnimDataSize>1)								//JIM 06Sep96
			RETURN(sdptr->AnimDataSize);						//JIM 06Sep96
		else													//JIM 06Sep96
		{														//JIM 06Sep96
			ULong	elementcnt = 0;
			ULong	haslaunchers=0;
			SLong	tmp,										//JIM 06Sep96
					animdatasize = 0;
			UByteP	li,instr_ptr = (UByteP )sdptr + sdptr->liveshpref;
			while (GetGroupElement(instr_ptr,newshp,tmp,tmp,tmp))
			{
				newshpp=SHAPESTUFF.GetShapePtr(newshp);
				animdatasize += GetElementAnimOffset(newshp);	//RJS 20Nov97
				haslaunchers|=(ULong) newshpp->LauncherDataSize;
				li=instr_ptr;
				elementcnt++;
			}
			if (!elementcnt)									//DAW 23Apr99
				animdatasize = sizeof(MinAnimData) + 1;			//DAW 23Apr99

			sdptr->AnimDataSize=animdatasize;
			if (haslaunchers)
				sdptr->LauncherDataSize=li-(UByteP)sdptr;
		 	return(animdatasize);
		}
	else
	{
		animdatasize = sdptr->AnimDataSize;						//RJS 30Jun97
		if (animdatasize > -1)									//RJS 30Jun97
		{
			switch (animdatasize)								//RJS 30Jun97
			{														//JIM 06Sep96
				case MINANIM:			RETURN(sizeof(MinAnimData));//JIM 06Sep96
//DeadCode RJS 21Apr99 				case EXPLODEANIM:		RETURN(sizeof(ExplodeAnimData));
				case POLYPITANIM:		RETURN(sizeof(PolyPitAnimData));
				case BLOKESANIM: 		RETURN(sizeof(BlokesAnimData));
				case WEAPANIM:			RETURN(sizeof(WeapAnimData));
				case AIRCRAFTANIM:		RETURN(sizeof(AircraftAnimData));
				case SUNANIM:			RETURN(sizeof(SunAnimData ));						//PD 24Jun96
//DeadCode RJS 21Apr99 				case FLAMEANIM:			RETURN(sizeof(FireAnimData ));
//DeadCode RJS 21Apr99 				case BALLOONANIM:		RETURN(sizeof(BalloonAnimData ));
				case WINDSOCANIM:		RETURN(sizeof(WindsocAnimData ));//RJS 05Jun97
				case BARAGEANIM:		RETURN(sizeof(BarageAnimData ));
				case MOVEGUNANIM:		RETURN(sizeof(MoveGunAnimData ));
//DeadCode RJS 21Apr99 				case FIREBALLANIM:		RETURN(sizeof(ExplodeAnimData ));//RJS 07Feb97
				case TANKANIM:			RETURN(sizeof(TwoGunAnimData ));//RJS 17Oct96
				case TRUCKANIM:			RETURN(sizeof(MoveGunAnimData ));//JIM 14Dec96
				case TRAINANIM:			RETURN(sizeof(TrainAnimData ));//RJS 03Mar98
				case TROOPANIM:			RETURN(sizeof(TroopAnimData ));//RJS 07Nov96
				case BRIDGEANIM:		RETURN(sizeof(MinAnimData ));//RJS 18Apr99
				case CLONEANIM:			RETURN(sizeof(CloneAnimData ));//RJS 21Jan98
				case FLAREANIM:			RETURN(sizeof(FlareAnimData ));//RJS 21Jan98
				case THUGANIM:			RETURN(sizeof(ThugAnimData ));//RJS 03Mar98
				case MISSILEANIM:		RETURN(sizeof(MissileAnimData ));//RJS 03Mar98
				case DEBRISANIM:		RETURN(sizeof(DebrisAnimData ));//RJS 20Jan99
				case SMOKETRAILANIM:	RETURN(sizeof(SmokeTrailAnimData ));//RJS 21Jan99
				case PARACHUTEANIM:		RETURN(sizeof(ParachuteAnimData ));//RJS 25Mar99
				case LAUNCHERANIM:		RETURN(sizeof(LauncherAnimData ));//RJS 16Apr99
				default:	//unique number below 4					//JIM 06Sep96
					RETURN(3);										//JIM 06Sep96
			}
		}
		else
			return(-animdatasize);								//RJS 30Jun97
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetElementYDelta
//Author		Robert Slater
//Date			Thu 20 Nov 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SByte	shape::GetElementYDelta(ShapeNum	shpno, animptr	&adptr, Coords3D&	pos, SLong centreY)
{
	SByte			delta = 0;										//RJS 09Jun99
	Bool			isTrue;
	MinAnimData*	mad = (MinAnimData*) adptr;

	adptr += GetAnimDataSizeAndCheck(shpno,BRIDGEANIM,isTrue);
	if (centreY)
	{	
		if (isTrue)
		{
			if (mad->itemstate == DEAD)								//RJS 09Jun99
			{
	//DeadCode RJS 21Apr99 			delta = *((SByteP)adptr);
				delta = (SByte) adptr[0];
				if (delta == -128)
				{
					SLong	ey = _Collide.AccurateGroundAltitude(pos);//RJS 28Apr99
					if (ey)											//RJS 28Apr99
					{												//RJS 28Apr99
						ey -= pos.Y;								//RJS 28Apr99

						ey >>= 4;

						if (ey < -127)
							ey = -127;
						else
						{
							if (ey > 127)
								ey = 127;
						}

						delta = SByte(ey);
						adptr[0] = (UByte)delta;						//RJS 21Apr99
					}
					else
					{
						//We don't have real altitude!!
						delta = 0;									//RJS 28Apr99
					}
				}
			}
		}
		else
		{
			// Init Group Y Delta here....							//DAW 01Dec98
			delta = (SByte) adptr[0];								//RJS 21Apr99
			if (delta == -128)										//DAW 01Dec98
			{														//DAW 01Dec98
				SLong	ey = _Collide.AccurateGroundAltitude(pos);	//RJS 28Apr99
				if (ey)
				{
					ey -= pos.Y;									//RJS 28Apr99
																	//DAW 01Dec98
					ey >>= 4;											//DAW 01Dec98
																		//DAW 01Dec98
					if (ey < -127)										//DAW 01Dec98
						ey = -127;										//DAW 01Dec98
					else												//DAW 01Dec98
					{													//DAW 01Dec98
						if (ey > 127)									//DAW 01Dec98
							ey = 127;									//DAW 01Dec98
					}													//DAW 01Dec98
																		//DAW 01Dec98
					delta = SByte(ey);									//DAW 01Dec98
					adptr[0] = (UByte)delta;							//RJS 21Apr99
				}
				else
				{
					//We don't have real altitude!!
					delta = 0;										//RJS 28Apr99
				}
			}														//DAW 01Dec98
		}
	}

	adptr += 1;													//RJS 21Apr99

	return(delta);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitAnimData
//Author		Paul.   
//Date			Tue 26 Mar 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::InitAnimData(itemptr itm)
{
	DefaultAnimData(itm,itm->Anim);								//RJS 21Apr99

//DeadCode RJS 06Jul98 	ShapeDescPtr	sdptr;
//DeadCode RJS 06Jul98 	UByteP			instr_ptr;
//DeadCode RJS 06Jul98 	Bool			haslaunchers = FALSE;
//DeadCode RJS 06Jul98 
//DeadCode RJS 06Jul98 	sdptr = SHAPESTUFF.GetShapePtr(itm->shape);
//DeadCode RJS 06Jul98 
//DeadCode RJS 06Jul98 	UByteP	animdataptr = (UByteP )itm->Anim;
//DeadCode RJS 06Jul98 
//DeadCode RJS 06Jul98 	globinitairitem = NULL;
//DeadCode RJS 06Jul98 
//DeadCode RJS 06Jul98 	switch (SHAPESTUFF.GetShapeScale(sdptr))					//PD 23Apr96
//DeadCode RJS 06Jul98 	{
//DeadCode RJS 06Jul98 		case SHP_GRP:
//DeadCode RJS 06Jul98 
//DeadCode RJS 06Jul98 			SLong	tmp;
//DeadCode RJS 06Jul98 			ShapeNum	newshp;
//DeadCode RJS 06Jul98 
//DeadCode RJS 06Jul98 			instr_ptr = (UByteP )sdptr + sdptr->liveshpref;
//DeadCode RJS 06Jul98 
//DeadCode RJS 06Jul98 			while (GetGroupElement(instr_ptr,newshp,tmp,tmp,tmp))
//DeadCode RJS 06Jul98 			{
//DeadCode RJS 06Jul98 				if (GetNumberOfLaunchers(newshp) > 0)
//DeadCode RJS 06Jul98 					haslaunchers = TRUE;
//DeadCode RJS 06Jul98 
//DeadCode RJS 06Jul98 				InitItemAnim(animdataptr,newshp);
//DeadCode RJS 06Jul98 				*animdataptr++ = 0x80;							//RJS 20Nov97
//DeadCode RJS 06Jul98 			}
//DeadCode RJS 06Jul98 
//DeadCode RJS 06Jul98 			if (haslaunchers)
//DeadCode RJS 06Jul98 				sdptr->Type.haslaunchers = TRUE;
//DeadCode RJS 06Jul98 			else
//DeadCode RJS 06Jul98 				sdptr->Type.haslaunchers = FALSE;
//DeadCode RJS 06Jul98 
//DeadCode RJS 06Jul98 			break;
//DeadCode RJS 06Jul98 
//DeadCode RJS 06Jul98 		case SHP_1CM:
//DeadCode RJS 06Jul98 		case SHP_4CM:
//DeadCode RJS 06Jul98 		case SHP_16CM:
//DeadCode RJS 06Jul98 			if (itm->Status.size == AirStrucSize)					//RJS 13May98
//DeadCode RJS 06Jul98 			{
//DeadCode RJS 06Jul98 				AirStrucPtr	asptr = (AirStrucPtr) itm;
//DeadCode RJS 06Jul98 				asptr->weap.left.mass = 0;
//DeadCode RJS 06Jul98 				asptr->weap.left.drag = 0;
//DeadCode RJS 06Jul98 				asptr->weap.left.int_fuel = 0;
//DeadCode RJS 06Jul98 				asptr->weap.left.int_fuel_leakage = 0;
//DeadCode RJS 06Jul98 				asptr->weap.left.ext_fuel = 0;
//DeadCode RJS 06Jul98 				asptr->weap.left.ext_fuel_leakage = 0;
//DeadCode RJS 06Jul98 
//DeadCode RJS 06Jul98 				asptr->weap.centre.mass = 0;
//DeadCode RJS 06Jul98 				asptr->weap.centre.drag = 0;
//DeadCode RJS 06Jul98 				asptr->weap.centre.int_fuel = 0;
//DeadCode RJS 06Jul98 				asptr->weap.centre.int_fuel_leakage = 0;
//DeadCode RJS 06Jul98 				asptr->weap.centre.ext_fuel = 0;
//DeadCode RJS 06Jul98 				asptr->weap.centre.ext_fuel_leakage = 0;
//DeadCode RJS 06Jul98 
//DeadCode RJS 06Jul98 				asptr->weap.right.mass = 0;
//DeadCode RJS 06Jul98 				asptr->weap.right.drag = 0;
//DeadCode RJS 06Jul98 				asptr->weap.right.int_fuel = 0;
//DeadCode RJS 06Jul98 				asptr->weap.right.int_fuel_leakage = 0;
//DeadCode RJS 06Jul98 				asptr->weap.right.ext_fuel = 0;
//DeadCode RJS 06Jul98 				asptr->weap.right.ext_fuel_leakage = 0;
//DeadCode RJS 06Jul98 
//DeadCode RJS 06Jul98 				asptr->weap.UseIntFuel = TRUE;		//Default fuel switch	RJS 23Jun98
//DeadCode RJS 06Jul98 				asptr->weap.FuelDumped = TRUE;		//Default fuel dump		RJS 23Jun98
//DeadCode RJS 06Jul98 
//DeadCode RJS 06Jul98 				globinitairitem = asptr;
//DeadCode RJS 06Jul98 			}
//DeadCode RJS 06Jul98 			InitItemAnim(animdataptr,itm->shape);					//RJS 13May98
//DeadCode RJS 06Jul98 			break;
//DeadCode RJS 06Jul98 	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitItemAnim
//Author		Paul.   
//Date			Wed 27 Mar 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SWord shape::InitItemAnim(animptr& adptr,ShapeNum shpno)			//RDH 23Sep96
{
	ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(shpno);		//RJS 30Jun97
	SWord			storesweight = 0;							//RJS 30Jun97
	SWord			animdatasize = sdptr->AnimDataSize;			//RJS 30Jun97
 	MinAnimData*	mad = (MinAnimData*) adptr;					//RJS 22Oct97
 
  	mad->IsInvisible = 0;										//RJS 17Nov98

	if (animdatasize > -1)										//RJS 30Jun97
	{
		switch (animdatasize)									//RJS 30Jun97
		{
			default:
			case MINANIM:										//RJS 11Nov97
				adptr += sizeof(MinAnimData);					//RJS 11Nov97
			break;											//RJS 11Nov97
			case WINDSOCANIM:										//RJS 05Jun97
				adptr += sizeof(WindsocAnimData);					//RJS 05Jun97
				break;
			case DEBRISANIM:									//RJS 20Jan99
				adptr += sizeof(DebrisAnimData);				//RJS 20Jan99
				break;											//RJS 20Jan99

			case TRAINANIM:											//RJS 09Dec96
			{
				TrainAnimData* aptr;								//RJS 09Jan97
				aptr = (TrainAnimData* )adptr;						//RJS 09Jan97
				InitLauncherAnim(adptr,shpno);						//RJS 04Jun99
			}														//RJS 09Dec96
				adptr += sizeof(TrainAnimData);						//RJS 07Feb97
				break;												//RJS 09Dec96
//DeadCode RJS 21Apr99  			case BRIDGEANIM:										//RJS 20Nov96
//DeadCode RJS 21Apr99 			case EXPLODEANIM:										//PD 15Apr96
//DeadCode RJS 21Apr99 				{
//DeadCode RJS 21Apr99 				ExplodeAnimData* aptr;
//DeadCode RJS 21Apr99 				aptr = (ExplodeAnimData* )adptr;
//DeadCode RJS 21Apr99 				aptr->frameno=0;
//DeadCode RJS 21Apr99 				}
//DeadCode RJS 21Apr99 				adptr += sizeof(ExplodeAnimData);
//DeadCode RJS 21Apr99 				break;
			case TRUCKANIM:											//DAW 14Dec96
			case TANKANIM:
			{
				MoveGunAnimData*	mptr=(MoveGunAnimData*) adptr;	  	
//Dead				mptr->nolaunchers = 0;								//RJS 23Aug96
				InitLauncherAnim(adptr,shpno);
				if (mptr->nolaunchers >2)
					_Error.EmitSysErr("Shape %x Num launchers %i !=1",shpno,mptr->nolaunchers);

				adptr+=sizeof(MoveGunAnimData);
		 		break;
			}
			case MOVEGUNANIM:
			{
				MoveGunAnimData*	mptr=(MoveGunAnimData*) adptr;	  	
				mptr->nolaunchers = 0;								//RJS 23Aug96
				InitLauncherAnim(adptr,shpno);
				if (mptr->nolaunchers >1) ///!=1)
					_Error.EmitSysErr("Agh %i",shpno);

				adptr+=sizeof(MoveGunAnimData);
		 		break;
			}
			case POLYPITANIM:										//PD 15Apr96
				{
				PolyPitAnimData* aptr;
				aptr = (PolyPitAnimData* )adptr;
				aptr->detailmask = 0;										//RJS 26Jan98

				aptr->detailmask |= (1 << COCK3D_DIALSROW1ON);				//RJS 26Jan98
				aptr->detailmask |= (1 << COCK3D_DIALSROW2ON);				//RJS 26Jan98
				aptr->detailmask |= (1 << COCK3D_DIALSROW3ON);				//RJS 26Jan98
				aptr->detailmask |= (1 << COCK3D_DIALSROW4ON);				//RJS 26Jan98
				aptr->detailmask |= (1 << COCK3D_PANELIMAPDSPLIT);				//RJS 26Jan98
				aptr->detailmask |= (1 << COCK3D_PANELGLASSFRONT);			//RJS 25Mar98

//				aptr->compasscount = 0;								//RJS 24Sep96
	//DeadCode JIM 06Sep96 			aptr->itemstate=ALIVE;
				}
				adptr += sizeof(PolyPitAnimData);
				break;

			case AIRCRAFTANIM:
				{
				AircraftAnimData* aptr;
				aptr = (AircraftAnimData* )adptr;
				aptr->nolaunchers = 0;								//RJS 23Aug96
				storesweight = InitLauncherAnim(adptr,shpno,AnimWeaponPack);//RJS 11May98

				if (globinititem->Status.size != AIRSTRUCSIZE)			//RJS 21Apr99
				{
					//Put gear down...
					aptr->acleglowerl = 0;
					aptr->acleglowerf = 0;
					aptr->acleglowerr = 0;
				}

				adptr += sizeof(AircraftAnimData);					//RJS 11May98

				}
				break;

			case SUNANIM:											//PD 24Jun96
				{													//PD 24Jun96
				SunAnimData *aptr;									//PD 24Jun96
				aptr = (SunAnimData* )adptr;						//PD 24Jun96
				aptr->wasdrawn=FALSE;								//PD 24Jun96
				}													//PD 24Jun96

				adptr += sizeof(SunAnimData);						//PD 24Jun96
				break;												//PD 24Jun96

//DeadCode RJS 21Apr99 			case FLAMEANIM:											//RJS 10Jul96
//DeadCode RJS 21Apr99 			{
//DeadCode RJS 21Apr99 				FireAnimData* aptr;
//DeadCode RJS 21Apr99 				aptr = (FireAnimData* )adptr;
//DeadCode RJS 21Apr99 
//DeadCode RJS 21Apr99 				if (shpno == TroopLauncherShape)					//RJS 10Dec96
//DeadCode RJS 21Apr99 					aptr->frameno=0;								//RJS 10Dec96
//DeadCode RJS 21Apr99 				else												//RJS 10Dec96
//DeadCode RJS 21Apr99 				{													//RJS 10Dec96
//DeadCode RJS 21Apr99 					if (Math_Lib.rnd() > 60000)							//RJS 06Dec96
//DeadCode RJS 21Apr99 						aptr->frameno=0;								//RJS 05Dec96
//DeadCode RJS 21Apr99 					else												//RJS 05Dec96
//DeadCode RJS 21Apr99 						aptr->frameno=1;								//RJS 05Dec96
//DeadCode RJS 21Apr99 				}
//DeadCode RJS 21Apr99 			}
//DeadCode RJS 21Apr99 			adptr += sizeof(FireAnimData);
//DeadCode RJS 21Apr99 			break;
//DeadCode RJS 21Apr99 
//DeadCode RJS 21Apr99 			case BALLOONANIM:										//RJS 05Aug96
//DeadCode RJS 21Apr99 				{
//DeadCode RJS 21Apr99 				BalloonAnimData* aptr;
//DeadCode RJS 21Apr99 				aptr = (BalloonAnimData* )adptr;
//DeadCode RJS 21Apr99 				aptr->manjumped=FALSE;
//DeadCode RJS 21Apr99 				aptr->groundheight=0;
//DeadCode RJS 21Apr99 				aptr->countdown=10;
//DeadCode RJS 21Apr99 				aptr->frameno = 0;
//DeadCode RJS 21Apr99 
//DeadCode RJS 21Apr99 				}
//DeadCode RJS 21Apr99 				adptr += sizeof(BalloonAnimData);
//DeadCode RJS 21Apr99 				break;

	//DeadCode RJS 20Nov96 		case WINDSOCKANIM:										//RJS 12Aug96
	//DeadCode RJS 20Nov96 			{
	//DeadCode RJS 20Nov96 			WindsockAnimData* aptr;
	//DeadCode RJS 20Nov96 			aptr = (WindsockAnimData* )adptr;
	//DeadCode RJS 20Nov96 			aptr->frameno=0;
	//DeadCode RJS 20Nov96 			}
	//DeadCode RJS 20Nov96 			adptr += sizeof(WindsockAnimData);
	//DeadCode RJS 20Nov96 			break;

			case BARAGEANIM:										//RJS 24Sep96
				{
				BarageAnimData* aptr;
				aptr = (BarageAnimData* )adptr;
				aptr->countdown=0;
				}

				adptr += sizeof(BarageAnimData);
				break;

//DeadCode RJS 21Apr99 			case FIREBALLANIM:										//RJS 07Oct96
//DeadCode RJS 21Apr99 				{
//DeadCode RJS 21Apr99 				ExplodeAnimData* aptr;								//RJS 09Jan97
//DeadCode RJS 21Apr99 				aptr = (ExplodeAnimData* )adptr;					//RJS 09Jan97
//DeadCode RJS 21Apr99 				aptr->frameno=0;
//DeadCode RJS 21Apr99 				}
//DeadCode RJS 21Apr99 				adptr += sizeof(ExplodeAnimData);					//RJS 09Jan97
//DeadCode RJS 21Apr99 				break;
			case TROOPANIM:											//RJS 07Nov96
				{
				TroopAnimData* aptr;								
				aptr = (TroopAnimData* )adptr;
				}

				adptr += sizeof(TroopAnimData);					
				break;

			case CLONEANIM:										//RJS 21Jan98
				adptr += sizeof(CloneAnimData);					//RJS 21Jan98
				break;
			case FLAREANIM:										//RJS 21Jan98
				adptr += sizeof(FlareAnimData);					//RJS 21Jan98
				break;											//RJS 21Jan98
			case THUGANIM:										//RJS 03Mar98
				adptr += sizeof(ThugAnimData);					//RJS 03Mar98
				break;											//RJS 03Mar98
			case MISSILEANIM:									//RJS 03Mar98
			{
				MissileAnimData*	aptr = (MissileAnimData*) adptr;

				aptr->hitstrength = 0;
				aptr->novirtualguns = 0;
				aptr->lastmissile = 0;

				adptr += sizeof(MissileAnimData);				//RJS 03Mar98
				break;
			}
			case SMOKETRAILANIM:
			{
				MoveGunAnimData*	mptr=(MoveGunAnimData*) adptr;	  	
				mptr->nolaunchers = 0;
				InitLauncherAnim(adptr,shpno);
				if (mptr->nolaunchers >1) ///!=1)
					_Error.EmitSysErr("Agh %i",shpno);

				adptr+=sizeof(SmokeTrailAnimData);
		 		break;
			}
			case PARACHUTEANIM:									//RJS 25Mar99
				adptr += sizeof(ParachuteAnimData);				//RJS 25Mar99
				break;											//RJS 25Mar99
		}

		if (globinitairitem)
		{
			InitUndercarriageAnim(globinitairitem);				//RJS 28May98
//			Trans_Obj.WeaponSearch(globinitairitem);			//RJS 09Sep98
		}
	}
	else
	{
		animdatasize = -animdatasize;							//RJS 27Apr98

		adptr += animdatasize;
	}

	return (storesweight);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FindWeapRecord
//Author		Robert Slater
//Date			Thu 17 Apr 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void*	shape::FindWeapRecord(ShapeNum	shpno,SLong	&index)
{
	ShpToWeapTypeP	wprec = NULL;
	SLong			i = 0;
	
	index = 0;
	while (ShpToWeap[i].LchShape)
	{
		if (ShpToWeap[i].LchShape == shpno)
		{
			wprec = &ShpToWeap[i];
			index = i;
			break;
		}

		i++;
	}

	return ((void*)wprec);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddWeapToAnim
//Author		Robert Slater
//Date			Thu 17 Apr 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void  shape::AddWeapToAnim(	void*				WeapPtr,
	  						MoveGunAnimData* 	adptr,
	  						LnchrType			lchtype,
							int					stores,
	  						int					&index,
							int					&addweight,
							int					&adddrag)
{
	int 			i,j,k;
	Bool			foundweap = FALSE;							//RJS 27Aug98
	ShpToWeapTypeP	WeapRec = (ShpToWeapTypeP) WeapPtr;			//RJS 27Aug98
																//RJS 27Aug98
	if (WeapRec)												//RJS 27Aug98
	{
		//Could be a weapon...
		i=0;

		while ((i < MaxWeapTypes) && (WeapRec->LchList[i].lnchr != LT_CONTACT))
		{
			if (WeapRec->LchList[i].lnchr == lchtype)
			{
				foundweap = TRUE;
				break;
			}
			else
				i++;
		}
	}																		//RJS 25Aug98

	//Return weight and drag for this station...
	addweight = 0;															//RJS 25Aug98
	adddrag = 0;
//DeadCode RJS 18Jan99 	if (lchtype == LT_FUEL)
//DeadCode RJS 18Jan99 		stores = 32767;

	UWord	muzandweapIndex;									//RJS 27May99
	if (foundweap)
	{
//DeadCode RJS 27May99 		UWord	muzandweapIndex;										//RJS 25Aug98

		addweight = WeapRec->LchList[i].Weight;
		adddrag = WeapRec->LchList[i].Drag;
		if (lchtype == LT_FUEL)									//RJS 18Jan99
		{														//RJS 18Jan99
			// 500 kilos max...									//RJS 18Jan99
			stores *= 32767;									//RJS 18Jan99
			stores /= 50000000;									//RJS 18Jan99
		}														//RJS 18Jan99

		// 8bits weapindex ... 8bits muzzleindex;
		muzandweapIndex = (i << 8);
		muzandweapIndex = muzandweapIndex | GetMuzzleIndex(lchtype);

		for (k=0; k < 2; k++)  						// Keep symmetrical
		{
			adptr->weaponlaunchers[index+k].LauncherType = lchtype;
			adptr->weaponlaunchers[index+k].stationshape = (UWord) WeapRec->LchList[i].StationShape[k];
			adptr->weaponlaunchers[index+k].target = UID_Null;
			adptr->weaponlaunchers[index+k].LaunchTime = muzandweapIndex;//RDH 03Aug98
  			adptr->weaponlaunchers[index+k].Stores = stores;		//RJS 11May98
			adptr->weaponlaunchers[index+k].SubDamage = 0;
			adptr->weaponlaunchers[index+k].hdg = 0;	//RJS 12Jan98
			adptr->weaponlaunchers[index+k].pitch = 0;	//RJS 12Jan98
			adptr->weaponlaunchers[index+k].LoadedStores = stores;	//RJS 11May98
		}

		index += 2;
	}
	else
	{
		if (lchtype == LT_FUEL)									//RJS 18Jan99
			stores = 32767;										//RJS 18Jan99

		SLong	masked = lchtype & LT_MASK;
		if ((masked == LT_SMKTRAILS) || (masked == LT_MOVEGUN))//RJS 22Oct98
		{
			// Must be an effect launcher, like LT_CONTRAIL, or LT_VAPOUR...
			adptr->weaponlaunchers[index].LauncherType = lchtype;
			adptr->weaponlaunchers[index].stationshape = 0;
			adptr->weaponlaunchers[index].target = UID_Null;
			adptr->weaponlaunchers[index].LaunchTime = 0;
  			adptr->weaponlaunchers[index].Stores = 534;
			adptr->weaponlaunchers[index].SubDamage = 0;
			adptr->weaponlaunchers[index].hdg = 0;
			adptr->weaponlaunchers[index].pitch = 0;
			adptr->weaponlaunchers[index].LoadedStores = 534;
			index += 1;
		}
		else
		{
			//Must be a dummy station; keep symmetrical
			for (k=0; k < 2; k++)  					
			{
				adptr->weaponlaunchers[index+k].LauncherType = lchtype;
				adptr->weaponlaunchers[index+k].stationshape = 0;
				adptr->weaponlaunchers[index+k].target = UID_Null;
				adptr->weaponlaunchers[index+k].LaunchTime = GetMuzzleIndex(lchtype);//RJS 27May99
  				adptr->weaponlaunchers[index+k].Stores = stores;					//RJS 23Apr99
				adptr->weaponlaunchers[index+k].SubDamage = 0;
				adptr->weaponlaunchers[index+k].hdg = 0;
				adptr->weaponlaunchers[index+k].pitch = 0;
				adptr->weaponlaunchers[index+k].LoadedStores = stores;				//RJS 23Apr99
			}

			index += 2;
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetWeaponPack
//Author		Robert Slater
//Date			Wed 8 Apr 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
UByteP	shape::GetWeaponPack(ShapeNum	shape, int packno)
{
	UByteP	retval = NULL;
	int		i;

	i = 0;
	if ((packno >= 0) && (packno < MaxPackNo))
	{
		while (ShpToWeapPak[i].shape)
		{
			if (ShpToWeapPak[i].shape == shape)
			{
				retval = (UByteP) ShpToWeapPak[i].weappack[packno].stationlaunchers;
				break;
			}

			i++;
		}

		// Default to F86 launchers.....
//		if (!retval)
//	 		retval = (UByteP) ShpToWeapPak[0].weappack[packno].stationlaunchers;
	}

	return(retval);
}

void	shape::AddFuelLauncher(UByteP instr_ptr, int launcher, int index)
{
	if (globinitairitem && (launcher==LT_INTFUEL))
	{
		DOLAUNCHER_PTR	lptr = (DOLAUNCHER_PTR) instr_ptr;
		SLong			dx = lptr->posx;
		weap_info		*WIPtrL;
		weap_info		*WIPtrR;
		weap_info		*WIPtrC;

		WIPtrL = &globinitairitem->weap.left;
		WIPtrR = &globinitairitem->weap.right;
		WIPtrC = &globinitairitem->weap.centre;

		if ((dx < -40) || (dx > 40))
		{
			if (dx < 0)
				WIPtrL->int_launcher = index;
			else
				WIPtrR->int_launcher = index;
		}
		else
			WIPtrC->int_launcher = index;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddMassAndDrag
//Author		Robert Slater
//Date			Wed 13 May 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::AddMassAndDrag(UByteP	instr_ptr, int	launcher, int count, int mass, int drag, SLong wpIndex, SWord launcherindex)
{
	if (globinitairitem)
	{
		DOLAUNCHER_PTR lptr = (DOLAUNCHER_PTR) instr_ptr;
		SLong			dx = lptr->posx;
		weap_info		*WIPtrL;
		weap_info		*WIPtrR;
		weap_info		*WIPtrC;
		SLong			totmass,totdrag;

		globinitairitem->weap.shpweapindex = (UWord) wpIndex;

		WIPtrL = &globinitairitem->weap.left;
		WIPtrR = &globinitairitem->weap.right;
		WIPtrC = &globinitairitem->weap.centre;

		if ((dx < -40) || (dx > 40))
		{
			weap_info		*WIPtr;								//RJS 21May99
			if (dx < 0)											//RJS 21May99
				WIPtr = WIPtrL;									//RJS 21May99
			else												//RJS 21May99
				WIPtr = WIPtrR;									//RJS 21May99

			if (launcher == LT_FUEL)
			{
				WIPtr->ext_fuel = count;						//RJS 21May99
//DeadCode RJS 21May99 				WIPtrR->ext_fuel = count;
				globinitairitem->weap.UseIntFuel = FALSE;		//RJS 25Jan99
				globinitairitem->weap.FuelDumped = FALSE;		//RJS 25Jan99
				globinitairitem->weap.StoresDumped = FALSE;		//RDH 04/03/99
				totmass = mass;									//RJS 25Jan99
				totdrag = drag;									//RJS 25Jan99

				WIPtr->ext_launcher = launcherindex;			//RJS 21May99
//DeadCode RJS 21May99 				if (dx < 0)
//DeadCode RJS 21May99 				{
//DeadCode RJS 21May99 					WIPtrL->ext_launcher = launcherindex;
//DeadCode RJS 21May99 					WIPtrR->ext_launcher = launcherindex+1;
//DeadCode RJS 21May99 				}
//DeadCode RJS 21May99 				else
//DeadCode RJS 21May99 				{
//DeadCode RJS 21May99 					WIPtrR->ext_launcher = launcherindex;
//DeadCode RJS 21May99 					WIPtrL->ext_launcher = launcherindex+1;
//DeadCode RJS 21May99 				}
			}
			else
			{													//RJS 25Jan99
				totmass = mass * count;							//RJS 25Jan99
				totdrag = drag * count;							//RJS 25Jan99
																//RJS 25Jan99
				WIPtr->reloadmass += totmass;					//RJS 21May99
 				WIPtr->reloaddrag += totdrag;					//RJS 21May99
//DeadCode RJS 21May99 																//RJS 25Jan99
//DeadCode RJS 21May99 				WIPtrR->reloadmass += totmass;					//RJS 25Jan99
//DeadCode RJS 21May99 				WIPtrR->reloaddrag += totdrag;					//RJS 25Jan99
			}													//RJS 25Jan99

			WIPtr->mass += totmass;								//RJS 21May99
			WIPtr->drag += totdrag;								//RJS 21May99

//DeadCode RJS 21May99 			WIPtrR->mass += totmass;							//RJS 25Jan99
//DeadCode RJS 21May99 			WIPtrR->drag += totdrag;							//RJS 25Jan99
		}
		else
		{
			if (launcher == LT_FUEL)
			{
				WIPtrC->ext_fuel = count;
				globinitairitem->weap.UseIntFuel = FALSE;		//RJS 25Jan99
				globinitairitem->weap.FuelDumped = FALSE;		//RJS 25Jan99
																//RJS 25Jan99
				totmass = mass;									//RJS 25Jan99
				totdrag = drag;									//RJS 25Jan99

				WIPtrC->ext_launcher = launcherindex;
			}
			else
			{
				totmass = mass * count;							//RJS 25Jan99
				totdrag = drag * count;							//RJS 25Jan99
																//RJS 25Jan99
				WIPtrC->reloadmass += totmass;					//RJS 25Jan99
				WIPtrC->reloaddrag += totdrag;					//RJS 25Jan99
			}

			WIPtrC->mass += totmass;
			WIPtrC->drag += totdrag;
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitLauncherAnim
//Author		Robert Slater
//Date			Wed 21 Aug 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SWord shape::InitLauncherAnim(animptr& adptr,ShapeNum shpno,int  packno)
{
	ShapeDescPtr	sdptr;
	UByte 			*instr_ptr;
	LnchrType		lchtype,addExtStore;						//RJS 13May98
	UWord		 	instruction, last_inst;
	Bool			go=TRUE;
	int				count=0;
	int				count2 = 0;
	SWord			storesweight = 0;
	void*			weaprec;
	LchrInfoP		lchlist;									//RJS 11May98
	int				fiddlecnt = 0;								//RJS 12May97
	int				addWeight, addDrag, addExtCount;			//RJS 13May98
	SLong			masked;
	SLong			wpIndex;
	Bool			setMassDrag = FALSE;						//RJS 13May99


//THIS NOBBLE FORCES A SPECIFIC WEAP PACK FOR ALL AIRCRAFT
//	packno = 1;													//RJS 02Dec98

	lchlist = (LchrInfoP) GetWeaponPack(shpno,packno);			//RJS 11May98
	sdptr = SHAPESTUFF.GetShapePtr(shpno);						//RJS 11May98
	weaprec = FindWeapRecord(shpno,wpIndex);					//RDH 03Aug98

	if (sdptr->LauncherDataSize)
	{
		MoveGunAnimData* aptr = (MoveGunAnimData*) adptr;
 
		instr_ptr = (UByteP )sdptr + sdptr->LauncherDataSize;

		while (go)
		{
			instruction = (UWord )*instr_ptr;

			instr_ptr ++;
//DeadCode RJS 19Dec97 			instruction>>=1;

			if(instruction>dosetglassrangeno || instruction==0)
				_Error.EmitSysErr(__FILE__":Bad instruction in launcher shape (%d)",instruction);

			if(instruction==doretno || instruction==doendno)
				go=FALSE;
			else
			{
				switch (instruction)
				{
					case dolauncherno:
					{
						DOLAUNCHER_PTR aptrsrc;
						aptrsrc = (DOLAUNCHER_PTR) instr_ptr;

						lchtype = (LnchrType) aptrsrc->lnchrtype;//RJS 17Apr97
						if (count < 12)							//RJS 12Jun97
						{
							if (lchtype < LT_CONTACT)
							{
								if (count == count2)				//RJS 17Apr97
								{
									setMassDrag = FALSE;
									masked = lchtype & LT_MASK;
									switch (masked)
									{
									case LT_SMKTRAILS:
									{
										AddWeapToAnim(	weaprec,
														aptr,
														lchtype,
														0,
														count2,
														addWeight,
														addDrag	);

										AddFuelLauncher(instr_ptr,lchtype,count);
									}
									break;
									case LT_WEAPON:
									{
										if (lchlist)			//RJS 17May99
										{
											addExtStore = lchlist[fiddlecnt].lnchrtype;
											addExtCount = lchlist[fiddlecnt++].ammocount;
											AddWeapToAnim(	weaprec,
															aptr,
															addExtStore,
															addExtCount,
															count2,
															addWeight,
															addDrag);		 //RJS 12May98		

											setMassDrag = TRUE;
											AddMassAndDrag(instr_ptr,addExtStore,addExtCount,addWeight,addDrag,wpIndex,count);//RJS 25Mar99
										}
									}
									break;
									case LT_MOVEGUN:
									{
										AddWeapToAnim(	weaprec,
														aptr,
														lchtype,
														534,			//default stores
														count2,
														addWeight,
														addDrag	);
									}
									break;
									}
								}
								else
								{
									//Needs to be twinned...
									if (setMassDrag)
										AddMassAndDrag(instr_ptr,addExtStore,addExtCount,addWeight,addDrag,wpIndex,count);//RJS 13May99
								}
							}
							else
								count2++;

							count++;
						}
						else
						{
							if (	(lchtype < LT_CONTACT)		//RJS 27May97
								||	(lchtype > CT_DUMMY)	)	//RJS 27May97
								_Error.EmitSysErr(__FILE__":Weapon launcher index out of range; shape %d",shpno);
						}

						instr_ptr += sizeof(DOLAUNCHER);
					}
					break;
					default:
						_Error.EmitSysErr(__FILE__":Bad launcher instruction (%d)",instruction);
				}
			}

			last_inst = instruction;
		}

		aptr->nolaunchers = GetNumberOfLaunchers(shpno);
	}

	return (storesweight);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetLightData
//Author		Robert Slater
//Date			Thu 18 Dec 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
UByteP	shape::GetLightDataPtr(ShapeNum	shpno, int	index)
{
	ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(shpno);
	ULong			lsize = (index * (sizeof(LIGHTDATA) + 1)) + sdptr->LightDataOffset;//RJS 19Dec97
	UByteP			retval = NULL;

	if (sdptr->LightDataOffset)
		retval = (UByteP) ((ULong)sdptr + lsize + 1);			//RJS 19Dec97

	return(retval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetLauncherPos
//Author		Robert Slater
//Date			Fri 23 Aug 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
UByteP shape::GetLauncherPos(ShapeNum	shpno, UByte	offset)
{
	ShapeDescPtr	sdptr;
	UByte 			*instr_ptr;
	UWord		 	instruction, last_inst;
	Bool			go=TRUE;
	DOLAUNCHER_PTR	launchfound = NULL;
	UByte			instsize = sizeof(DOLAUNCHER) + 1;

	sdptr = SHAPESTUFF.GetShapePtr(shpno);

	if (SHAPESTUFF.GetShapeScale(sdptr) != SHP_GRP)				//JIM 29Sep96
	{															//JIM 29Sep96
		if (sdptr->LauncherDataSize)
		{
			instr_ptr = (UByteP )sdptr + sdptr->LauncherDataSize + (instsize * offset);

			instruction = (UWord) *instr_ptr;
			instr_ptr++;

//DeadCode RJS 19Dec97 			instruction >>= 1;

			if (instruction == dolauncherno)
				return(instr_ptr);
			else
			{
				if (	(instruction == doretno)
					 || (instruction == doendno)	)
					return(NULL);
				else
					_Error.EmitSysErr(__FILE__":Bad launcher instruction (%d)",instruction);
			}

//DeadCode RJS 21May97 			while (go)
//DeadCode RJS 21May97 			{
//DeadCode RJS 21May97 				instruction = (UWord )*instr_ptr;
//DeadCode RJS 21May97 
//DeadCode RJS 21May97 				instr_ptr ++;
//DeadCode RJS 21May97 				instruction>>=1;
//DeadCode RJS 21May97 
//DeadCode RJS 21May97 				if(instruction>dosetglassrangeno || instruction==0)
//DeadCode RJS 21May97 					_Error.EmitSysErr(__FILE__":Bad instruction in launcher GetLauncherPos (%d)",instruction);
//DeadCode RJS 21May97 
//DeadCode RJS 21May97 				if(instruction==doretno || instruction==doendno)//JIM 29Sep96
//DeadCode RJS 21May97 					go=FALSE;
//DeadCode RJS 21May97 				else
//DeadCode RJS 21May97 				{
//DeadCode RJS 21May97 					switch (instruction)
//DeadCode RJS 21May97 					{
//DeadCode RJS 21May97 						case dolauncherno:
//DeadCode RJS 21May97 							{
//DeadCode RJS 21May97 								if (offset > 0)
//DeadCode RJS 21May97 									offset--;
//DeadCode RJS 21May97 								else
//DeadCode RJS 21May97 								{
//DeadCode RJS 21May97 									RETURN(instr_ptr);			//JIM 29Sep96
//DeadCode RJS 21May97 								}
//DeadCode RJS 21May97 
//DeadCode RJS 21May97 								instr_ptr += sizeof(DOLAUNCHER);
//DeadCode RJS 21May97 							}
//DeadCode RJS 21May97 						break;
//DeadCode RJS 21May97 						default:
//DeadCode RJS 21May97 							_Error.EmitSysErr(__FILE__":Bad launcher instruction (%d)",instruction);
//DeadCode RJS 21May97 					}
//DeadCode RJS 21May97 				}
//DeadCode RJS 21May97 
//DeadCode RJS 21May97 			}
		}
	}
	else														//JIM 29Sep96
	{
		if (sdptr->AnimDataSize==0)
			SHAPE.GetAnimDataSize(shpno);	
 		if (sdptr->LauncherDataSize)
		{
			UByteP	instr_ptr = (UByteP )sdptr + sdptr->liveshpref;
			Coords3D	g;
			ShapeNum	newshp;
			while	(GetGroupElement(instr_ptr,newshp,g.X,g.Y,g.Z))
			{
				sdptr = SHAPESTUFF.GetShapePtr(newshp);
				if (sdptr->LauncherDataSize)
				{
					if (offset--==0)
						RETURN((UByteP)sdptr + sdptr->LauncherDataSize +1);
				}
			}
		}
	}

	return((UByteP) launchfound);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetContactPoint
//Author		Paul.   
//Date			Wed 11 Sep 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::GetContactPoint(	itemptr itm,LnchrType ct,
	  							COORDS3D&	position,
	  							COORDS3D&	offset,
								COORDS3D&	dummyoffset)
{
	DOLAUNCHER_PTR	thislaunch = NULL;
	DOLAUNCHER_PTR	dummylaunch = NULL;
	ClassPtr		clstyp;
	ShapeDescPtr	sdptr;
	ShapeNum		shpno;
	Bool			polypit = FALSE;
	UByte count 	= 0;
	SByte target 	= (SByte )ct;
	UByte			thisscale = 0;
	MyGroundVectorPtr		goffset = NULL;								//RJS 21Nov96
	SLong			xpos, ypos, zpos;							//RJS 12Aug97
	Bool			inCock = FALSE;

//DeadCode RJS 21Apr99  	if ((itm == Manual_Pilot.ControlledAC2) && View_Point)
//DeadCode RJS 21Apr99  	{
//DeadCode RJS 21Apr99  		if (View_Point)
//DeadCode RJS 21Apr99 		{
//DeadCode RJS 21Apr99 			if (View_Point->PolyPitEnabled())
//DeadCode RJS 21Apr99  			{
//DeadCode RJS 21Apr99 	 			clstyp = Manual_Pilot.ControlledAC2->classtype;
//DeadCode RJS 21Apr99  				if (View_Point->viewnum.viewmode == VM_Inside)
//DeadCode RJS 21Apr99  					shpno = clstyp->cockpit1;
//DeadCode RJS 21Apr99  				else
//DeadCode RJS 21Apr99  					shpno = clstyp->cockpit2;
//DeadCode RJS 21Apr99 
//DeadCode RJS 21Apr99 				inCock = TRUE;
//DeadCode RJS 21Apr99 			}
//DeadCode RJS 21Apr99 			else
//DeadCode RJS 21Apr99 			{
//DeadCode RJS 21Apr99 				if (View_Point->viewnum.viewmode == VM_InsideCheat)
//DeadCode RJS 21Apr99 				{
//DeadCode RJS 21Apr99 					clstyp = Manual_Pilot.ControlledAC2->classtype;
//DeadCode RJS 21Apr99 					shpno = clstyp->cockpit1;
//DeadCode RJS 21Apr99 					inCock = TRUE;
//DeadCode RJS 21Apr99 				}
//DeadCode RJS 21Apr99 				else
//DeadCode RJS 21Apr99 					shpno = itm->shape;
//DeadCode RJS 21Apr99 			}
//DeadCode RJS 21Apr99  		}
//DeadCode RJS 21Apr99  		else
//DeadCode RJS 21Apr99  			shpno = itm->shape;
//DeadCode RJS 21Apr99  	}
//DeadCode RJS 21Apr99  	else
	shpno = itm->shape;											//RJS 21Apr99

 	sdptr = SHAPESTUFF.GetShapePtr(shpno);
 
 	switch (SHAPESTUFF.GetShapeScale(sdptr))
 	{
 		case SHP_1CM:
 			thisscale = 0;
 			break;
 
 		case SHP_4CM:
 			thisscale = 2;
 			break;
 
 		case SHP_16CM:
 			thisscale = 4;
 			break;
 	}

	offset.X = 0;
	offset.Y = 0;
	offset.Z = 0;

	do
	{
		thislaunch = (DOLAUNCHER_PTR) GetLauncherPos(shpno,count++);

		if (thislaunch)
		{
//DeadCode RJS 17Mar97 			if (thislaunch->lnchrtype==LT_CONTACT)
//DeadCode RJS 17Mar97 			{
//DeadCode RJS 17Mar97 				target--;
//DeadCode RJS 17Mar97 				if (target<0)
//DeadCode RJS 17Mar97 					break;
//DeadCode RJS 17Mar97 			}

			if (thislaunch->lnchrtype == ct)
			{
 				xpos = thislaunch->posx << thisscale;			//RJS 10Feb99
 				ypos = thislaunch->posy << thisscale;			//RJS 10Feb99
 				zpos = thislaunch->posz << thisscale;			//RJS 10Feb99
//DeadCode RJS 10Feb99 				xpos = thislaunch->posx;						//RJS 27Aug97
//DeadCode RJS 10Feb99 				ypos = thislaunch->posy;						//RJS 27Aug97
//DeadCode RJS 10Feb99 				zpos = thislaunch->posz;						//RJS 27Aug97


				// Set dummy suspension pushed-in default to fully suspended...
				offset.X = dummyoffset.X = xpos;				//RJS 12Aug97
				offset.Y = dummyoffset.Y = ypos;				//RJS 12Aug97
				offset.Z = dummyoffset.Z = zpos;				//RJS 12Aug97

				dummylaunch = (DOLAUNCHER_PTR) GetLauncherPos(shpno,count);//RJS 13Jun97
				if (dummylaunch)
				{
					if (dummylaunch->lnchrtype == CT_DUMMY)
					{
 						dummyoffset.X = dummylaunch->posx << thisscale;//RJS 10Feb99
 						dummyoffset.Y = dummylaunch->posy << thisscale;//RJS 10Feb99
 						dummyoffset.Z = dummylaunch->posz << thisscale;//RJS 10Feb99
//DeadCode RJS 10Feb99 						dummyoffset.X = dummylaunch->posx;		//RJS 27Aug97
//DeadCode RJS 10Feb99 						dummyoffset.Y = dummylaunch->posy;		//RJS 27Aug97
//DeadCode RJS 10Feb99 						dummyoffset.Z = dummylaunch->posz;		//RJS 27Aug97
					}
				}
				break;
			}
		}
	}
	while (thislaunch);

//Dead	LauncherToWorld(itm,(UByteP )thislaunch,thisscale,position.X,position.Y,position.Z,goffset,NULL,inCock);
	LauncherToWorld(itm,(UByteP )thislaunch,thisscale,position.X,position.Y,position.Z,goffset);

	if (goffset)	delete (goffset);

//DeadCode RJS 12Aug97 	return((UByteP) dummylaunch);								//RJS 13Jun97
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetVapourPoint
//Author		Robert Slater
//Date			Fri 20 Sep 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SLong shape::GetVapourPoint(itemptr itm,int index,int ltype,SLong &xpos,SLong &ypos,SLong &zpos)
{
	DOLAUNCHER_PTR	thislaunch = NULL;
	ShapeDescPtr	sdptr;
	ShapeNum		shpno;
	int				count 	= 0;
	SByte			thisscale = 0;
	MinAnimData		*mad = (MinAnimData*) itm->Anim;
	int				vapindex = 0;

//	if (index < mad->nolaunchers)
//	{
		count = index;

		shpno = itm->shape;
		sdptr = SHAPESTUFF.GetShapePtr(shpno);

		switch (SHAPESTUFF.GetShapeScale(sdptr))
		{
			case SHP_GRP:
				thisscale = -1;
				break;
			case SHP_1CM:
				thisscale = 0;
				break;

			case SHP_4CM:
				thisscale = 2;
				break;

			case SHP_16CM:
				thisscale = 4;
				break;
		}

		if (thisscale > -1)
		{
			do
			{
				thislaunch = (DOLAUNCHER_PTR) GetLauncherPos(shpno,count++);
				if (thislaunch && (thislaunch->lnchrtype==ltype))
				{
					LauncherToWorld(itm,(UByteP) thislaunch,thisscale,xpos,ypos,zpos,NULL);

					vapindex = count;
					break;
				}
			}
			while (thislaunch);
		}
//	}

	return (vapindex);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetWeaponLauncher
//Author		Robert Slater
//Date			Thu 22 Aug 1996
//
//Description	Gets a pointer to indexed weapon launcher
//
//Inputs		The item, index, x,y,z dummies, and launcher type
//
//Returns		Pointer to weapon launcher data
//
//------------------------------------------------------------------------------
WeapAnimData* shape::GetWeaponLauncher(itemptr	itm, UByte	index,
									   SLong&	xpos, SLong&	ypos,
									   SLong&	zpos,
									   UWord&	MuzzleVel,
									   UWord&	MuzzleDelay,
									   UWord&	MuzzleBurst,
									   SByte 	ltype,
									   UWord	*bulletShape
									   )
{
	ShapeDescPtr		sdptr;
	DOLAUNCHER_PTR		thislaunch = NULL;
	animptr				animdataptr;
	UByteP				instr_ptr;
	ShapeNum			shape;
	ShapeDescPtr		tmpsdptr;
	WeapAnimData*		weapon=NULL;
	MoveGunAnimData*	aptr;
	UByte				thisscale = 0;
	SLong				gx, gy, gz;
	MyGroundVectorPtr			goffset = NULL;
	int					cnt;
	Coords3D			eyeDelta;
	UWord				muzindex = 0;
	UWord				noLaunchers = 0;						//RJS 09Dec98
	Bool				incock = FALSE;							//RDH 08Dec98
	ShapeNum			scaleshape;								//RJS 19Jan99
	Bool				nofix = FALSE;							//RJS 25Jan99

 	MuzzleVel = 9000;
	MuzzleDelay = 15;
	MuzzleBurst = 8;											//RDH 31Jul98
	shape= scaleshape = itm->shape;								//RJS 19Jan99

	// All a right load of shite...
 	if (View_Point && itm == Manual_Pilot.ControlledAC2)						//RJS 07Oct96
 	{
 		ClassPtr			clstyp = Manual_Pilot.ControlledAC2->classtype;
 
//DEADCODE DAW 12/04/99  		if (View_Point->PolyPitEnabled())
//DEADCODE DAW 12/04/99  		{
//DEADCODE DAW 12/04/99  			if (View_Point->viewnum.viewmode == VM_Inside)
//DEADCODE DAW 12/04/99 			{
//DEADCODE DAW 12/04/99 				shape = clstyp->cockpit1;//RJS 19Jan99
//DEADCODE DAW 12/04/99 				scaleshape = shape;								//RJS 15Mar99
//DEADCODE DAW 12/04/99 // 				tmpsdptr = SHAPESTUFF.GetShapePtr(clstyp->cockpit1);
//DEADCODE DAW 12/04/99 			}
//DEADCODE DAW 12/04/99  			else
//DEADCODE DAW 12/04/99 			{
//DEADCODE DAW 12/04/99 				shape = clstyp->cockpit2;//RJS 19Jan99
//DEADCODE DAW 12/04/99  //				tmpsdptr = SHAPESTUFF.GetShapePtr(clstyp->cockpit2);
//DEADCODE DAW 12/04/99 			}
//DEADCODE DAW 12/04/99 			incock = TRUE;
//DEADCODE DAW 12/04/99  		}
//DEADCODE DAW 12/04/99  		else
//DEADCODE DAW 12/04/99  		{
//DEADCODE DAW 12/04/99  			if (View_Point->viewnum.viewmode == VM_InsideCheat)
//DEADCODE DAW 12/04/99 			{
//DEADCODE DAW 12/04/99 				shape = clstyp->cockpit1;//RJS 19Jan99
//DEADCODE DAW 12/04/99 				scaleshape = shape;								//RJS 15Mar99
//DEADCODE DAW 12/04/99 // 				tmpsdptr = SHAPESTUFF.GetShapePtr(clstyp->cockpit1);
//DEADCODE DAW 12/04/99 				incock = TRUE;
//DEADCODE DAW 12/04/99 			}
//DEADCODE DAW 12/04/99  			else
//DEADCODE DAW 12/04/99  				tmpsdptr = SHAPESTUFF.GetShapePtr(shape);
//DEADCODE DAW 12/04/99  		}

//DeadCode RDH 08Dec98  		eyeDelta.X = tmpsdptr->EyeDeltaX;
//DeadCode RDH 08Dec98  		eyeDelta.Y = tmpsdptr->EyeDeltaY;
//DeadCode RDH 08Dec98  		eyeDelta.Z = tmpsdptr->EyeDeltaZ;
//DeadCode RDH 08Dec98  	}
//DeadCode RDH 08Dec98  	else
//DeadCode RDH 08Dec98  	{
		eyeDelta.X = 0;
		eyeDelta.Y = 0;
		eyeDelta.Z = 0;
 	}

	animdataptr = itm->Anim;

	aptr = (MoveGunAnimData*) animdataptr;
	sdptr = SHAPESTUFF.GetShapePtr(scaleshape);

	if (SHAPESTUFF.GetShapeScale(sdptr) == SHP_GRP)
	{
		SLong	tmp;

		if (sdptr->Type.haslaunchers)
		{
			instr_ptr = (UByteP )sdptr + sdptr->liveshpref;
			while	(GetGroupElement(instr_ptr,shape,gx,gy,gz))
			{
				sdptr = SHAPESTUFF.GetShapePtr(shape);
				if (sdptr->LauncherDataSize && aptr->itemstate==ALIVE)//RJS 22Nov96
				{
					thislaunch = (DOLAUNCHER_PTR) GetLauncherPos(shape,0);
					if ((thislaunch->lnchrtype & LT_MASK)!= LT_CONTACT)
						if (ltype==-1||(thislaunch->lnchrtype & LT_MASK)==ltype)
							if (index--==0)
							{	//found my launcher
								GrpMinAnimData*	gmad;				//RJS 09Dec98
								gmad = (GrpMinAnimData*) aptr;		//RJS 09Dec98
								noLaunchers = gmad->nolaunchers;	//RJS 09Dec98

								goffset=new MyGroundVector;			//RJS 21Nov96
								goffset->gx=gx;
								goffset->gy=gy;
								goffset->gz=gz;
								break;
							}
				}
				aptr=(MoveGunAnimData*)((int)aptr+GetElementAnimOffset(shape));//RJS 20Nov97
//pooDec98				GrpMinAnimData*	gmad = (GrpMinAnimData*) aptr;
//pooDec98				noLaunchers = gmad->nolaunchers;				//RJS 17Nov98
			}
			if (index!=0xff)
				return(NULL);
			index=0;
		}
		else return(NULL);
	}
	else
		noLaunchers = aptr->nolaunchers;						//RJS 17Nov98

	// now shape and sdptr points to correct element & so does aptr
	//
	//

	if ( (index >= 0) && (index < noLaunchers) && aptr->itemstate==ALIVE)//RJS 17Nov98
	{
		DOLAUNCHER	fiddledlauncher;

		switch(SHAPESTUFF.GetShapeScale(sdptr))
		{
			case SHP_1CM:
				thisscale = 0;
				break;												
			case SHP_4CM:
				thisscale = 2;										
				break;												
			case SHP_16CM:
				thisscale = 4;										
				break;
		}

		// Handle sub-shape launchers.....
		if (index < 14)
		{
			weapon = &aptr->weaponlaunchers[index];
			if (weapon)
			{
				if (weapon->stationshape)
				{
					// Get base x,y,z...
					thislaunch = (DOLAUNCHER_PTR) GetLauncherPos(shape,index);
					if (thislaunch)
					{
						// Real index and shape...
						if (weapon->LoadedStores)
						{
							DOLAUNCHER_PTR	thislaunch2;

							index = weapon->Stores - weapon->LoadedStores;
							thislaunch2 = (DOLAUNCHER_PTR) GetLauncherPos((ShapeNum)weapon->stationshape,index);
							if (thislaunch2)
							{
								// Sub launcher is relative to main launcher...
								fiddledlauncher = *thislaunch;
								fiddledlauncher.posx += thislaunch2->posx;
								fiddledlauncher.posy += thislaunch2->posy;
								fiddledlauncher.posz += thislaunch2->posz;
								thislaunch = &fiddledlauncher;
								nofix = TRUE;
							}
						}
					}
				}
				else
					thislaunch = (DOLAUNCHER_PTR) GetLauncherPos(shape,index);
			}
			else
				thislaunch = NULL;
		}
		else
		{
			thislaunch = NULL;
			weapon = NULL;										//RJS 25Jan99
		}

		if (thislaunch)
		{
			if (	(thislaunch->lnchrtype < LT_CONTACT)		//RJS 27May97
				||	(thislaunch->lnchrtype > CT_DUMMY)	)		//RJS 27May97
			{
				if (weapon == NULL)
					_Error.EmitSysErr(__FILE__":Weapon launcher index out of range!");
			}

			if (ltype > -1)
			{
				if (weapon)												//RJS 14Aug98
				{
					if ((weapon->LauncherType & LT_MASK) != ltype)		//RJS 14Aug98
					{
						thislaunch = NULL;
						weapon = NULL;
					}
					else
					{
						

						//DAVE----- KEEP THIS CODE IN!!!!!!!!!						//RJS 10Sep98
						muzindex = weapon->LaunchTime & 0x00FF;						//RJS 10Sep98
						if (muzindex > MaxMuzzles)									//RJS 10Sep98
							muzindex = 0;											//RJS 10Sep98
																					//RJS 10Sep98
						MuzzleVel = launcherdata[muzindex].muzlvel;					//RJS 10Sep98
						MuzzleDelay = launcherdata[muzindex].firingdelay;			//RJS 10Sep98
						MuzzleBurst = launcherdata[muzindex].burstcount;			//RJS 10Sep98
																					//RJS 10Sep98
						if (bulletShape)											//RJS 10Sep98
							*bulletShape = (UWord) launcherdata[muzindex].theShape;	//RJS 10Sep98

						if ((shape == F86) && (nofix == FALSE))						//RJS 25Jan99 //JIM 29/03/99
						{
							//Work out which of the 3 guns it is...
							SWord	stores = ((weapon->LoadedStores & 3)<<1)/3;	//vals 0-2

							fiddledlauncher = *thislaunch;
							thislaunch = &fiddledlauncher;

							// gap between guns is 16cm
							thislaunch->posy -= ((10 * stores) >> thisscale);
						}
					}

				}
			}
		}

		LauncherToWorld(itm,(UByteP) thislaunch,thisscale,xpos,ypos,zpos,goffset,&eyeDelta,incock);
	}

	if (goffset)
		delete goffset;

	return(weapon);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetNearestTrench
//Author		Robert Slater
//Date			Thu 7 Nov 1996
//
//Description	Finds nearest trench to a given troop launcher
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool shape::GetNearestTrench(	itemptr	itm,
						     	SLong&	xpos, SLong&	ypos,
							 	SLong&	zpos, SWord&	hdg)
{
	ShapeDescPtr		sdptr;
	UByteP				animdataptr;
	UByteP				instr_ptr;
	ShapeNum			shape;
	SLong				gx, gy, gz;
	SLong				dx, dy, dz;
	SLong				tx, ty, tz;
	SLong				dist;
	SWord				thehdg,thepitch;
	Bool				foundone;
	SLong				nearest;

	sdptr = SHAPESTUFF.GetShapePtr(itm->shape);
	foundone = FALSE;

	if (SHAPESTUFF.GetShapeScale(sdptr) == SHP_GRP)
	{
		tx = xpos;
		ty = ypos;
		tz = zpos;

		nearest = 0x7fffffff;

		instr_ptr = (UByteP )sdptr + sdptr->liveshpref;
		while	(GetGroupElement(instr_ptr,shape,gx,gy,gz))
		{
			if (	(shape == TrenchShapeBrit)
				||	(shape == TrenchShapeGerm)	)				//RJS 15Dec96
			{
//DeadCode JIM 18Dec96 			if (shape == TrenchShape)
//DeadCode JIM 18Dec96 			{
				foundone = TRUE;

				gx += itm->World.X;
				gy += itm->World.Y;
				gz += itm->World.Z;

				dx = gx - tx;
				dy = gy - ty;
				dz = gz - tz;

				Math_Lib.Intercept(dx,dy,dz,dist,thehdg,thepitch);

				if (dist < nearest)
				{
					nearest = dist;
					xpos = gx;
					ypos = gy;
					zpos = gz;

					hdg = thehdg;
				}
			}
		}
	}
	
	return(foundone);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RechargeWeapons
//Author		Robert Slater
//Date			Tue 19 Nov 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::RechargeWeapons(itemptr	itm)
{
	ShapeDescPtr		sdptr;
	AircraftAnimData*	adptr;
	WeapAnimData*		weapon=NULL;
	int					count,index;
	UByte				lchtype;

	adptr = (AircraftAnimData*) itm->Anim;

	if (itm->Status.size == AirStrucSize)
	{
		Trans_Obj.ReloadWeapons((AirStrucPtr)itm);				//RJS 11May98
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		WeapUnitWeight
//Author		Robert Slater
//Date			Thu 2 Oct 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SLong	shape::WeapUnitWeight(LnchrType	lnchr)
{
//	int	index;
//	int	retval = 0;
//
//	index = 0;
//
//	while (WeapWeights[index].lnchr != LT_CONTACT)
//	{
//		if (WeapWeights[index].lnchr == lnchr)
//		{
//			retval = WeapWeights[index].unitweight;
//			break;
//		}
//		else
//			index++;
//	}
//
	return(0);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ReduceLauncherLoad
//Author		Robert Slater
//Date			Wed 13 May 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SLong	shape::ReduceLauncherLoad(	AirStrucPtr	itm,
									SWord		index,
									SWord		count)
{
	DOLAUNCHER_PTR		lptr;
	WeapAnimData*		weapon;
	AircraftAnimData*	adptr = (AircraftAnimData*) itm->Anim;
	ShapeDescPtr		sdptr = SHAPESTUFF.GetShapePtr(itm->shape);
	UByte				instsize = sizeof(DOLAUNCHER) + 1;
	UByteP				instr_ptr;
	UByteP				base_ptr;
	UWord				instruction;
	SLong				stores;
	weap_info			*weapptr;
	Bool				isFuel=TRUE;
	SLong				xdelta, mass, drag;

	base_ptr = (UByteP )sdptr + sdptr->LauncherDataSize;

	instr_ptr = base_ptr + (instsize * index);
	instr_ptr++;

	lptr = (DOLAUNCHER_PTR) instr_ptr;

	xdelta = lptr->posx;
	mass = 0;//RJS 16Sep98
	if (count)													//RJS 18Jun99
	{
		weapon = (WeapAnimData*) &adptr->weaponlaunchers[index];
		if ((weapon->LauncherType == LT_FUEL) || (!Save_Data.gamedifficulty[GD_UNLIMITEDARM]))//RJS 06May99
		{
//DeadCode RJS 18Jun99 			stores = weapon->LoadedStores;
//DeadCode RJS 18Jun99 			if (stores)
 			{
				UWord	index_shpweap = itm->weap.shpweapindex;						//RDH 03Aug98
				UWord	index_weap;
				ShpToWeapType	sweap = ShpToWeap[index_shpweap];

				index_weap = (weapon->LaunchTime & 0xFF00)>>8;

				mass = sweap.LchList[index_weap].Weight;
				if (mass)
				{
					LnchrType	lchtype = (LnchrType) weapon->LauncherType;

					drag = sweap.LchList[index_weap].Drag;

					mass *= count;
					drag *= count;

					if ((xdelta < -40) || (xdelta > 40))
					{
						if (xdelta < 0)
							weapptr = &itm->weap.left;
						else
							weapptr = &itm->weap.right;
					}
					else
					{
						xdelta = 0;
						weapptr = &itm->weap.centre;
					}

					if (lchtype != LT_FUEL)
						isFuel = FALSE;

					weapptr->mass -= mass;						//RJS 18Jun99
					weapptr->drag -= drag;						//RJS 18Jun99

					itm->fly.pModel->RemoveStore(weapptr,xdelta,mass,drag,isFuel);
				}																	//RDH 03Aug98
			}
		}
	}

	return(mass);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LauncherToWorld
//Author		Robert Slater
//Date			Wed 28 Aug 1996
//
//Description	Transforms and scales an item's launcher coordinates relative
//				to the item
//
//Inputs		The item, position, scale, x,y,z return values
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::LauncherToWorld(	itemptr	itm,
								UByteP position,
								UByte	thisscale,
								SLong& xpos, SLong& ypos, SLong& zpos,
								MyGroundVectorPtr	goffset,
								Coords3D			*eyePtr,
								Bool				incock	)
{
//	MATRIX   			omat;						
//	MATRIX_PTR			obj_matrix = &omat;
	SLong				tmpx, tmpy, tmpz;
	DOLAUNCHER_PTR		thislaunch;
	mobileitem*			tmpitm = (mobileitem*) itm;
 	UWord				scaleback;
	SWord				eyefixX, eyefixY, eyefixZ;

	if (eyePtr)
	{
		eyefixX = eyePtr->X;
		eyefixY = eyePtr->Y;
		eyefixZ = eyePtr->Z;
	}
	else
	{
		eyefixX = 0;
		eyefixY = 0;
		eyefixZ = 0;
	}

	thislaunch = (DOLAUNCHER_PTR) position;
	if (thislaunch)
	{
		tmpx = thislaunch->posx << thisscale;			
		tmpy = thislaunch->posy << thisscale;		
		tmpz = thislaunch->posz << thisscale;	

		if (incock)			//RJS 08Dec98
		{
			ClassPtr	clstyp = ((AirStrucPtr)itm)->classtype;		//RJS 19Jan99

			tmpx=SLong(Float(tmpx)*clstyp->cockscale);		//RJS 19Jan99
			tmpy=SLong(Float(tmpy)*clstyp->cockscale); 		//RJS 19Jan99
			tmpz=SLong(Float(tmpz)*clstyp->cockscale);		//RJS 19Jan99
		}
//		tmpx += eyefixX;
//		tmpy += eyefixY;
//		tmpz += eyefixZ;

		if ((tmpitm == Manual_Pilot.ControlledAC2) && !_Replay.Playback)//RJS 21Jun99
			((AirStrucPtr)tmpitm)->fly.pModel->CalcLauncherPos(tmpx,tmpy,tmpz);
		else
		{
			MATRIX   			omat;						
			MATRIX_PTR			obj_matrix = &omat;

			_matrix.generate2(tmpitm->hdg, tmpitm->pitch, tmpitm->roll, obj_matrix);
			
			scaleback = _matrix.transform(obj_matrix,tmpx,tmpy,tmpz);

 			tmpx >>= (16-scaleback);
 			tmpy >>= (16-scaleback);
 			tmpz >>= (16-scaleback);
		}
	}
	else
	{
		tmpx = eyefixX;			//RJS 09Jul98
		tmpy = eyefixY;			//RJS 09Jul98
		tmpz = eyefixZ;			//RJS 09Jul98
	}

	xpos = tmpx + itm->World.X;
	ypos = tmpy + itm->World.Y;
	zpos = tmpz + itm->World.Z;

	if (goffset)
	{
		xpos += goffset->gx;
		ypos += goffset->gy;
		zpos += goffset->gz;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoTrailPoint
//Author		Robert Slater
//Date			Mon 23 Sep 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Float	shape::DoTrailPoint(UWord	vertex, SLong wx, SLong wy, SLong wz)
{
	IFShare	ifwx,ifwy,ifwz;

	ifwx.i=wx; ifwy.i=wy; ifwz.i=wz;

	FPMATRIX_PTR	fpobj_matrix = Three_Dee.fpviewer_matrix;

	_matrix.transformNC(fpobj_matrix,ifwx,ifwy,ifwz);

 	newco[vertex].bodyx.f = ifwx.f;								//RJS 02Jun97
 	newco[vertex].bodyy.f = ifwy.f;								//RJS 02Jun97
 	newco[vertex].bodyz.f = ifwz.f;								//RJS 02Jun97

	_matrix.SetClipFlags(newco[vertex]);
	_matrix.body2screen(newco[vertex]);							//PD 25Jul96

	return (newco[vertex].bodyz.f);								//RJS 02Jun97
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetGroupItemAnim
//Author		Robert Slater
//Date			Wed 2 Oct 1996
//
//Description	Finds position in group anim data, with regard to group index
//
//Inputs		Group item, index
//
//Returns		animation data pointer
//
//------------------------------------------------------------------------------
UByteP	shape::GetGroupItemAnim(itemptr	itm, ShapeNum& shape, SByte	index, MyGroundVectorPtr P)
{
	ShapeDescPtr		sdptr;
	ShapeNum			newshp;
	animptr				animdataptr;
	UByteP				indexedptr;
	UByteP				instr_ptr;
	int					totalsize;
	int					thisindex;
	animptr				dummyadptr;

	animdataptr = itm->Anim;
	indexedptr = &animdataptr[0];
	dummyadptr = animdataptr;

	shape = itm->shape;
	sdptr = SHAPESTUFF.GetShapePtr(shape);						//RJS 14Oct96

	if (SHAPESTUFF.GetShapeScale(sdptr) == SHP_GRP)
	{
		SLong	tmpx,tmpy,tmpz,yDelta;							//RJS 03Dec98
		
		instr_ptr = (UByteP )sdptr + sdptr->liveshpref;
		thisindex = 0;
		totalsize = 0;

		while	(GetGroupElement(instr_ptr,newshp,tmpx,tmpy,tmpz))//RJS 21Nov96
		{
			if (thisindex == index)
			{
				Coords3D	tmpworld;
				indexedptr = (UByteP) &animdataptr[totalsize];
				shape = newshp;
				tmpworld = itm->World;
				tmpworld.X += tmpx;
				tmpworld.Y += tmpy;
				tmpworld.Z += tmpz;

				dummyadptr = indexedptr;

				yDelta = GetElementYDelta(shape,dummyadptr,tmpworld,itm->World.Y);	//RJS 09Jun99
				yDelta <<= 4;

				P->gx = tmpworld.X;
				P->gy = tmpworld.Y + yDelta;
				P->gz = tmpworld.Z;
				break;
			}
			else
			{
				thisindex++;
				totalsize += GetElementAnimOffset(newshp);		//RJS 20Nov97
			}
		}
	}
	else
	{
		P->gx = itm->World.X;
		P->gy = itm->World.Y;
		P->gz = itm->World.Z;
	}

	return(indexedptr);
}

UByteP	shape::GetGroupItemAnimHdg(itemptr	itm, ShapeNum& shape, SByte	index, MyGroundVector* P, UWord& ghdg)
{
	ShapeDescPtr		sdptr;
	ShapeNum			newshp;
	animptr				animdataptr;
	UByteP				indexedptr = NULL;
	UByteP				instr_ptr;
	int					totalsize;
	int					thisindex;
	SWord				thehdg;
	animptr				dummyadptr;

	animdataptr = itm->Anim;
	dummyadptr = animdataptr;
	indexedptr = &animdataptr[0];

	shape = itm->shape;
	sdptr = SHAPESTUFF.GetShapePtr(shape);						//RJS 14Oct96
	ghdg = 0;

	if (SHAPESTUFF.GetShapeScale(sdptr) == SHP_GRP)
	{
		SLong	tmpx,tmpy,tmpz,yDelta;							//RJS 03Dec98
		
		instr_ptr = (UByteP )sdptr + sdptr->liveshpref;
		thisindex = 0;
		totalsize = 0;

		while	(GetGroupElement(instr_ptr,newshp,tmpx,tmpy,tmpz,0,NULL,&thehdg))//RJS 18Nov98
		{
			if (thisindex == index)
			{
				Coords3D	tmpworld;
				indexedptr = (UByteP) &animdataptr[totalsize];
				shape = newshp;
				ghdg = UWord(thehdg);

				tmpworld = itm->World;
				tmpworld.X += tmpx;
				tmpworld.Y += tmpy;
				tmpworld.Z += tmpz;

				dummyadptr = indexedptr;

				yDelta = GetElementYDelta(shape,dummyadptr,tmpworld,itm->World.Y);	//RJS 09Jun99
				yDelta <<= 4;

				P->gx = tmpworld.X;
				P->gy = tmpworld.Y + yDelta;
				P->gz = tmpworld.Z;
				break;
			}
			else
			{
				thisindex++;
				totalsize += GetElementAnimOffset(newshp);		//RJS 20Nov97
			}
		}
	}
	else
	{
		P->gx = itm->World.X;
		P->gy = itm->World.Y;
		P->gz = itm->World.Z;
		if (itm->Status.size >= HDGSIZE)						//RJS 02Dec98
			ghdg = ((rotitem*)itm)->hdg;						//RJS 02Dec98
	}

	return(indexedptr);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetGroupDeathToll
//Author		Robert Slater
//Date			Wed 16 Oct 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
UByte	shape::GetGroupDeathToll(itemptr	itm)
{
	ShapeDescPtr		sdptr;
	ShapeNum			newshp;
	animptr				animdataptr;
	MinAnimData*		adptr = NULL;
	UByteP				instr_ptr;
	SLong				deathtoll;
	SLong				priority ;
	UByte				noimportant;

	animdataptr = itm->Anim;
	adptr = (MinAnimData*) animdataptr;

	sdptr = SHAPESTUFF.GetShapePtr(itm->shape);						//RJS 14Oct96
	deathtoll = 0;
	noimportant = 0;

	if (SHAPESTUFF.GetShapeScale(sdptr) == SHP_GRP)
	{
		SLong	tmp;
		
		instr_ptr = (UByteP )sdptr + sdptr->liveshpref;

		priority = GetGroupElement(instr_ptr,newshp,tmp,tmp,tmp);//RJS 14Nov96

		while(priority)											//RJS 27Feb98
		{														//RJS 27Feb98
			adptr = (MinAnimData*) animdataptr;
			if (adptr->itemstate == DEAD)						//RJS 27Feb98
				deathtoll += priority;							//RJS 27Feb98

			animdataptr += (int)GetElementAnimOffset(newshp);
			priority = GetGroupElement(instr_ptr,newshp,tmp,tmp,tmp);//RJS 14Nov96
		}

		if (deathtoll < 250)									//RJS 27Feb98
			deathtoll = 0;										//RJS 27Feb98
	}

	return(deathtoll);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CopyAnimData
//Author		Paul.   
//Date			Wed 27 Mar 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
UByteP shape::CopyAnimData(animptr& adptr,ShapeNum shpno)
{
	int	j;

	SLong	adsize;

	UByteP	dstptr,retval;

	adsize = GetAnimDataSize(shpno);

	dstptr =
		retval = new UByte [adsize];

	for (j=0; j < adsize; j++)
		dstptr[j] = adptr[j];

//DeadCode RJS 21Apr99 	for (j=adsize;j--;)
//DeadCode RJS 21Apr99 		*dstptr++ = *adptr++;

	return(retval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ResetAnimFlags
//Author		Paul.   
//Date			Wed 27 Mar 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::ResetAnimFlags()
{
	UByteP	tmp = animflags;

	int	j;

//DeadCode RJS 26Nov96 	for (j=MAXANIMFLAG;j--;)
//DeadCode RJS 26Nov96 		*tmp++=0;

	for (j=MAXANIMFLAG-2;j--;)									//RJS 26Nov96
		*tmp++=0;
}

//DeadCode RJS 05Jun97 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RJS 05Jun97 //Procedure		SimpleItemAnim
//DeadCode RJS 05Jun97 //Author		Paul.   
//DeadCode RJS 05Jun97 //Date			Wed 27 Mar 1996
//DeadCode RJS 05Jun97 //
//DeadCode RJS 05Jun97 //Description	
//DeadCode RJS 05Jun97 //
//DeadCode RJS 05Jun97 //Inputs		
//DeadCode RJS 05Jun97 //
//DeadCode RJS 05Jun97 //Returns	
//DeadCode RJS 05Jun97 //
//DeadCode RJS 05Jun97 //------------------------------------------------------------------------------
//DeadCode RJS 05Jun97 void shape::SimpleItemAnim(MinAnimData* adptr)
//DeadCode RJS 05Jun97 {
//DeadCode RJS 05Jun97 	if (adptr)													//PD 02Apr96
//DeadCode RJS 05Jun97 		*(animflags+ITEMSTATE) = (UByte )(adptr->itemstate);	//PD 02Apr96
//DeadCode RJS 05Jun97 }

//DeadCode RJS 05Jun97 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RJS 05Jun97 //Procedure		ExplodeItemAnim
//DeadCode RJS 05Jun97 //Author		Paul.   
//DeadCode RJS 05Jun97 //Date			Mon 15 Apr 1996
//DeadCode RJS 05Jun97 //
//DeadCode RJS 05Jun97 //Description	
//DeadCode RJS 05Jun97 //
//DeadCode RJS 05Jun97 //Inputs		
//DeadCode RJS 05Jun97 //
//DeadCode RJS 05Jun97 //Returns	
//DeadCode RJS 05Jun97 //
//DeadCode RJS 05Jun97 //------------------------------------------------------------------------------
//DeadCode RJS 05Jun97 void shape::ExplodeItemAnim(ExplodeAnimData* adptr)
//DeadCode RJS 05Jun97 {
//DeadCode RJS 05Jun97 //DeadCode RJS 05Jun97 	SimpleItemAnim((MinAnimData* )adptr);
//DeadCode RJS 05Jun97 
//DeadCode RJS 05Jun97 	*(animflags+EXPLODEFRAME) = adptr->frameno;
//DeadCode RJS 05Jun97 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FlameItemAnim
//Author		Robert Slater
//Date			Wed 10 Jul 1996
//
//Description	Launch point for birds or troops...
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::FlameItemAnim(FireAnimData* adptr)

{
//DeadCode RJS 05Jun97 	SimpleItemAnim((MinAnimData* )adptr);
//DeadCode RJS 16Nov98 
//DeadCode RJS 16Nov98 	if (!Three_Dee.IsPaused())									//RJS 27Feb98
//DeadCode RJS 16Nov98 	{
//DeadCode RJS 16Nov98 		WorldStuff*	worldptr = mobileitem::currworld;				//RJS 08Nov96
//DeadCode RJS 16Nov98 
//DeadCode RJS 16Nov98 	//DeadCode RJS 18Oct96 	*(animflags+EXPLODEFRAME) = adptr->frameno;
//DeadCode RJS 16Nov98 		if (object_obj3d->Shape == TroopLauncherShape)
//DeadCode RJS 16Nov98 		{
//DeadCode RJS 16Nov98 			if (adptr->frameno == 0)								
//DeadCode RJS 16Nov98 				Trans_Obj.LaunchTroops((mobileitem*) object_obj3d->ItemPtr,0,0,0,*worldptr);				//RJS 08Nov96
//DeadCode RJS 16Nov98 		}
//DeadCode RJS 16Nov98 		else
//DeadCode RJS 16Nov98 		{
//DeadCode RJS 16Nov98 			if (	(Math_Lib.rnd() > 65000)					//RJS 10Dec96
//DeadCode RJS 16Nov98 				&&  (adptr->frameno == 0)
//DeadCode RJS 16Nov98 				&&	(object_obj3d->realbz.f < (Float)30000))
//DeadCode RJS 16Nov98 				Trans_Obj.LaunchBirds((mobileitem*) object_obj3d->ItemPtr,BirdShape,*worldptr);
//DeadCode RJS 16Nov98 		}
//DeadCode RJS 16Nov98 	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BalloonItemAnim
//Author		Robert Slater
//Date			Mon 5 Aug 1996
//
//Description	Launch a parachute from balloon if close enough and not already
//				done so...
//				Then lower the balloon
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::BalloonItemAnim(BalloonAnimData* adptr, Obj3DPtr thisobj3d)
{
	SLong	yshift;

//DeadCode RJS 05Jun97 	SimpleItemAnim((MinAnimData* )adptr);

	if (!Three_Dee.IsPaused())									//RJS 27Feb98
	{
		if ( (adptr->itemstate == DEAD) && (adptr->countdown > -300) )
		{
			adptr->frameno++;
			if (adptr->frameno > 7)
				adptr->frameno = 0;

			*(animflags+EXPLODEFRAME) = adptr->frameno;
			adptr->countdown--;
			adptr->manjumped = TRUE;							//RJS 26Nov96
		}

		if (adptr->manjumped == FALSE)
		{
			if (	(thisobj3d->realbz.f < (Float)30000)
				)
			{
				WorldStuff*	worldptr = mobileitem::currworld;
				Trans_Obj.LaunchParachute((mobileitem*) thisobj3d->ItemPtr,*worldptr);
			}
		}
		else
		{
			if (adptr->countdown > 0)
				adptr->countdown--;
			else
			{
				if (thisobj3d->ItemPtr->World.Y > (adptr->groundheight + 500))
				{
					if (adptr->itemstate == DEAD)
					{
						yshift = (15000 * Timer_Code.FRAMETIME) / 100;
						thisobj3d->ItemPtr->World.Y -= yshift;
						Trans_Obj.AddWindDrift(thisobj3d->ItemPtr);//RJS 07Jan97
					}
					else
					{
						yshift = (5000 * Timer_Code.FRAMETIME) / 100;
						thisobj3d->ItemPtr->World.Y -= yshift;
					}
				}
				else
				{
					if (adptr->itemstate == DEAD)
					{
						WorldStuff*	worldptr = mobileitem::currworld;
						Trans_Obj.LaunchBigExplosion((mobileitem*) thisobj3d->ItemPtr,*worldptr);
//DeadCode RDH 17Dec96 						worldptr->RemoveFromWorld(thisobj3d->ItemPtr);
						thisobj3d->ItemPtr->shape = EMPTY;		//RDH 17Dec96
					}
				}
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		WindsockItemAnim
//Author		Robert Slater
//Date			Mon 12 Aug 1996
//
//Description	Points a windsoc animation item in the right direction.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::WindsockItemAnim(WindsocAnimData* adptr)			//RJS 05Jun97
{
	SWord	windscale = 0;
	SLong	vx,vy,vz,vel;
	SLong	MaxWindVel = 255;//dont know yet...

	if (MMC.Sky.GetWind(object_obj3d->ItemPtr->World.Y,vx,vy,vz))
	{
		vel = Math_Lib.distance3d(vx,vy,vz) / 10;				//RJS 30Apr99

		object_obj3d->AngH = Angles(SLong(MMC.Sky.dir0) * 10430);

		windscale = (255*vel)/MaxWindVel;
	}

	adptr->frameno = windscale;									//RJS 05Jun97
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MoveGunItemAnim
//Author		Robert Slater
//Date			Tue 15 Oct 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::MoveGunItemAnim(MoveGunAnimData* adptr)
{
//DeadCode RJS 19Jun97  	FPMATRIX		smat;									 	//RJS 14May97
//DeadCode RJS 19Jun97  	FPMATRIX_PTR	stan_matrix = &smat;					 	//RJS 14May97
 	SWord		pitchscale;
 	UWord		framestep = ANGLES_90Deg / 6;			 
 	ANGLES		thehdg, thepitch;
 
 	if (	(object_obj3d->Shape != TrenchShapeBrit)						
 		&&	(object_obj3d->Shape != TrenchShapeGerm)	)
 	{
		WeapAnimData*	weapon = (WeapAnimData*) &adptr->weaponlaunchers[0];//RJS 05Jun97
 		thehdg = (Angles)weapon->hdg;							//RJS 12Jan98
 		thepitch = (Angles)weapon->pitch;						//RJS 12Jan98
 
//DeadCode RJS 19Jun97 		*stan_matrix=*Three_Dee.fpviewer_matrix;				//RJS 14May97
//DeadCode RJS 19Jun97 
//DeadCode RJS 19Jun97  		_matrix.generate2(thehdg,ANGLES_0Deg,ANGLES_0Deg,fpobject_matrix);//RJS 14May97
//DeadCode RJS 19Jun97  		_matrix.multiply(fpobject_matrix,stan_matrix);			//RJS 14May97
 
		object_obj3d->AngH = thehdg;							//RJS 19Jun97
		object_obj3d->AngC = ANGLES_0Deg;						//RJS 19Jun97
		object_obj3d->AngR = ANGLES_0Deg;						//RJS 19Jun97

//DeadCode RJS 05Jun97  		SimpleItemAnim((MinAnimData* )adptr);
 
  		pitchscale = ((SWord)thepitch / framestep);
 
 		if (pitchscale < 0)
 			pitchscale = 0;
 
 		if (pitchscale > 5)
 			pitchscale = 5;
 
 		weapon->stationshape = pitchscale;						//RJS 05Jun97
 	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TankItemAnim
//Author		Robert Slater
//Date			Thu 17 Oct 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::TankItemAnim(MoveGunAnimData* adptr)
{
	SWord		pitchscale;
	UWord		framestep = ANGLES_90Deg / 6;			 
	ANGLES		thepitch;

//DeadCode RJS 05Jun97 	SimpleItemAnim((MinAnimData* )adptr);						//RJS 14Nov96

	if ((adptr->itemstate == ALIVE)	&& !Three_Dee.IsPaused())	//RJS 27Feb98
	{
		ShapeDescPtr	sdptr;									//RJS 13Nov96

		sdptr = SHAPESTUFF.GetShapePtr(object_obj3d->ItemPtr->shape);//RJS 13Nov96
		if (SHAPESTUFF.GetShapeScale(sdptr) != SHP_GRP)			//RJS 13Nov96
		{
			SByte		distance;								//RJS 13Nov96
			WorldStuff*	worldptr = mobileitem::currworld;			//RJS 13Nov96
			WeapAnimData*	weapon = (WeapAnimData*) &adptr->weaponlaunchers[0];//RJS 05Jun97

//DeadCode RJS 05Jun97 			SimpleItemAnim((MinAnimData* )adptr);

 			pitchscale = ((SWord)weapon->pitch / framestep);			//RJS 05Jun97

			if (pitchscale < 0)
				pitchscale = 0;

			if (pitchscale > 5)
				pitchscale = 5;

			weapon->stationshape = pitchscale;					//RJS 05Jun97

			if (object_obj3d->realbz.f > (Float)30000)					//RJS 13Nov96
				distance = 1;
			else
				distance = 0;

			if (object_obj3d->ItemPtr->Status.size == FORMATIONSIZE)//RJS 15Dec96
			{
//DeadCode RJS 20Apr98 				_Miles.PlayLooped(FIL_SFX_TANK_LOOP1, (ItemBasePtr) object_obj3d->ItemPtr,128,8);//RJS 22Nov96
//DeadCode RJS 27Aug98 				Trans_Obj.LaunchDustTrail((mobileitem*) object_obj3d->ItemPtr,*worldptr,distance);//RJS 13Nov96
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TruckItemAnim
//Author		Robert Slater
//Date			Thu 17 Oct 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::TruckItemAnim(MinAnimData* adptr, UByteP	descptr)
{
//TempCode RJS 18May99 	if (adptr->itemstate == ALIVE)
//TempCode RJS 18May99 	{
//TempCode RJS 18May99 		if (object_obj3d->ItemPtr->Status.size >= MovingSize)
//TempCode RJS 18May99 		{
//TempCode RJS 18May99 			mobileitem*	itm = (mobileitem*)object_obj3d->ItemPtr;
//TempCode RJS 18May99 			FakeDustTrail(itm,vel,SWord(itm->hdg),descptr);
//TempCode RJS 18May99 		}
//TempCode RJS 18May99 	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TrainItemAnim
//Author		Robert Slater
//Date			Thu 17 Oct 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::TrainItemAnim(TrainAnimData* adptr)
{
	WeapAnimData*	weapon = (WeapAnimData*) &adptr->weaponlaunchers[0];
	if (weapon)
	{
		SLong	index = weapon->hdg;

		if (adptr->itemstate != DEAD)
		{
			if (Math_Lib.rnd() > 65000)
				_Miles.PlayDelayed(FIL_SFX_TRAIN_WHISTLE,object_obj3d->ItemPtr);//PD 13Aug99

			if (!index)
			{
				Trans_Obj.LaunchVapourStream((UByteP)weapon,(ShapeNum)object_obj3d->Shape);
				weapon->pitch = -1;
			}
		}
		else
		{
			if (index > 0)
			{
				pTrailItm = object_obj3d->ItemPtr;				//RJS 07Jul99
				SHAPE.DetatchVapourStream(index,LIFETIME_VAPOUR);
			 	weapon->hdg = 0;
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TroopItemAnim
//Author		Robert Slater
//Date			Fri 18 Oct 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::TroopItemAnim(TroopAnimData* adptr,TroopAnimData* adptr2)
{
//DeadCode RJS 05Jun97 	SimpleItemAnim((MinAnimData* )adptr);
//DeadCode RJS 26Nov98 	UByte	frameno;											//RJS 26Nov96
//DeadCode RJS 26Nov98 
//DeadCode RJS 26Nov98 	frameno = *(animflags+TROOPFRAME);							//RJS 26Nov96
//DeadCode RJS 26Nov98 
//DeadCode RJS 26Nov98 	if (!Three_Dee.IsPaused())									//RJS 27Feb98
//DeadCode RJS 26Nov98 	{
//DeadCode RJS 26Nov98 		if (object_obj3d->ItemPtr->shape == TinyFireShape)		//RJS 06Dec96
//DeadCode RJS 26Nov98 		{
//DeadCode RJS 26Nov98 			if (adptr2->frameno < 3)								//RJS 06Dec96
//DeadCode RJS 26Nov98 				adptr2->frameno++;								//RJS 06Dec96
//DeadCode RJS 26Nov98 			else												//RJS 06Dec96
//DeadCode RJS 26Nov98 				adptr2->frameno = 0;								//RJS 06Dec96
//DeadCode RJS 26Nov98 
//DeadCode RJS 26Nov98 			*(animflags+EXPLODEFRAME) = adptr2->frameno;		//RJS 06Dec96
//DeadCode RJS 26Nov98 		}
//DeadCode RJS 26Nov98 		else
//DeadCode RJS 26Nov98 		{
//DeadCode RJS 26Nov98 			if (adptr->itemstate != DEAD)							//RJS 05Dec96
//DeadCode RJS 26Nov98 			{
//DeadCode RJS 26Nov98 				if (frameno < 2)									//RJS 26Nov96
//DeadCode RJS 26Nov98 					frameno++;										//RJS 26Nov96
//DeadCode RJS 26Nov98 				else
//DeadCode RJS 26Nov98 					frameno = 0;									//RJS 26Nov96
//DeadCode RJS 26Nov98 			}
//DeadCode RJS 26Nov98 			else
//DeadCode RJS 26Nov98 				frameno = 3;										//RJS 26Nov96
//DeadCode RJS 26Nov98 
//DeadCode RJS 26Nov98 			*(animflags+TROOPFRAME) = frameno;					//RJS 06Dec96
//DeadCode RJS 26Nov98 			*(animflags+EXPLODEFRAME) = frameno;				//RJS 06Dec96
//DeadCode RJS 26Nov98 		}
//DeadCode RJS 26Nov98 	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BarageItemAnim
//Author		Robert Slater
//Date			Tue 24 Sep 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::BarageItemAnim(BarageAnimData* adptr)
{
	SLong	xpos, ypos, zpos;
	SWord	doit;

	if (!Three_Dee.IsPaused())									//RJS 27Feb98
	{
		if (adptr->countdown <= 0)
		{
			ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(object_obj3d->Shape);

			doit = Math_Lib.rnd();
			if (doit > 16384)									//RJS 07Dec98
			{
				WorldStuff*	worldptr = mobileitem::currworld;
				Coords3D	oldcoords = object_obj3d->ItemPtr->World;
				Coords3D	newcoords = oldcoords;
				SLong		sizex = sdptr->sx << 6;
				SLong		sizez = sdptr->sz << 6;

				if (doit < 32767)
				{
					newcoords.X += Math_Lib.rnd(sizex) - (sizex >> 1);
					newcoords.Z += Math_Lib.rnd(sizez) - (sizez >> 1);

					object_obj3d->ItemPtr->World = newcoords;

					Trans_Obj.LaunchDirtSmall((mobileitem*)object_obj3d->ItemPtr,*worldptr,false);//PD 13Aug99

					object_obj3d->ItemPtr->World = oldcoords;
				}
				else
				{
					newcoords.X += Math_Lib.rnd(sizex>>1) - (sizex >> 2);
					newcoords.Z += Math_Lib.rnd(sizez>>1) - (sizez >> 2);
					newcoords.Y += Math_Lib.rnd(200);

					object_obj3d->ItemPtr->World = newcoords;

					Trans_Obj.LaunchGunDot((mobileitem*)object_obj3d->ItemPtr,*worldptr);

					object_obj3d->ItemPtr->World = oldcoords;
				}
			}

			adptr->countdown = 20 + Math_Lib.rnd(50);
		}
		else
			adptr->countdown -= Timer_Code.FRAMETIME;

		if (Math_Lib.rnd() > 63000)												//RJS 24Jun99
			_Miles.PlayDelayed(FIL_SFX_MACHINE_GUN_LOOP1,object_obj3d->ItemPtr);//PD 13Aug99
//DeadCode DAW 25Jun99 		_Miles.PlayLooped(FIL_SFX_BATTLEFIELD_LOOP, (ItemBasePtr) object_obj3d->ItemPtr,128,8);//RJS 22Nov96
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FireballItemAnim
//Author		Robert Slater
//Date			Mon 7 Oct 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::FireballItemAnim(ExplodeAnimData* adptr)
{
//DeadCode RJS 05Jun97 	SimpleItemAnim((MinAnimData* )adptr);

//DeadCode RJS 26Nov98 	if (!Three_Dee.IsPaused())									//RJS 27Feb98
//DeadCode RJS 26Nov98 	{
//DeadCode RJS 26Nov98 		adptr->frameno++;
//DeadCode RJS 26Nov98 
//DeadCode RJS 26Nov98 		if (adptr->frameno > 3)
//DeadCode RJS 26Nov98 			adptr->frameno = 0;
//DeadCode RJS 26Nov98 
//DeadCode RJS 26Nov98 		_Miles.PlayLooped(FIL_SFX_SMALL_FIRE_LOOP, (ItemBasePtr) object_obj3d->ItemPtr);//RJS 09Jan97
//DeadCode RJS 26Nov98 
//DeadCode RJS 26Nov98 		*(animflags+EXPLODEFRAME) = adptr->frameno;
//DeadCode RJS 26Nov98 	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BridgeItemAnim
//Author		Robert Slater
//Date			Wed 20 Nov 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::BridgeItemAnim(ExplodeAnimData* adptr)
{
//DeadCode RJS 05Jun97  	SimpleItemAnim((MinAnimData* )adptr);
//DeadCode RJS 19Jun97  
//DeadCode RJS 19Jun97  	FPMATRIX		smat;									 	//RJS 14May97
//DeadCode RJS 19Jun97  	FPMATRIX_PTR	stan_matrix = &smat;					 	//RJS 14May97
//DeadCode RJS 26Nov98  	ANGLES		thehdg;
//DeadCode RJS 26Nov98  
//DeadCode RJS 26Nov98  	thehdg = (Angles) adptr->frameno;
//DeadCode RJS 26Nov98  
//DeadCode RJS 19Jun97 	*stan_matrix=*Three_Dee.fpviewer_matrix;					//RJS 14May97
//DeadCode RJS 19Jun97  
//DeadCode RJS 19Jun97  	_matrix.generate2(thehdg,ANGLES_0Deg,ANGLES_0Deg,fpobject_matrix);//RJS 14May97
//DeadCode RJS 19Jun97  	_matrix.multiply(fpobject_matrix,stan_matrix);				//RJS 14May97
//DeadCode RJS 26Nov98  
//DeadCode RJS 26Nov98 	object_obj3d->AngH = thehdg;								//RJS 19Jun97
//DeadCode RJS 26Nov98 	object_obj3d->AngC = ANGLES_0Deg;							//RJS 19Jun97
//DeadCode RJS 26Nov98 	object_obj3d->AngR = ANGLES_0Deg;							//RJS 19Jun97

//DeadCode RJS 05Jun97  	SimpleItemAnim((MinAnimData* )adptr);
}	

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PolyPitItemAnim
//Author		Paul.   
//Date			Mon 15 Apr 1996
//
//Description	
//
//Inputs		
//
//Returns									 
//
//------------------------------------------------------------------------------
void shape::PolyPitItemAnim(PolyPitAnimData* adptr)
{
 	AircraftAnim((AircraftAnimData *)adptr,TRUE);				//RJS 12Feb98
	ULong		timesec = View_Point->TimeOfDay() / 100;

	Manual_Pilot.ControlledAC2->fly.pInst->SetCockpitAnims(Manual_Pilot.ControlledAC2,(UByteP)adptr);
	Manual_Pilot.ControlledAC2->fly.pInst->UpdateCockpitTimers(current_screen->FrameTime());

//	adptr->detailmask = 0;										//RJS 26Jan98
  //
//	adptr->detailmask |= (1 << COCK3D_DIALSROW1ON);				//RJS 26Jan98
//	adptr->detailmask |= (1 << COCK3D_DIALSROW2ON);				//RJS 26Jan98
//	adptr->detailmask |= (1 << COCK3D_DIALSROW3ON);				//RJS 26Jan98
//	adptr->detailmask |= (1 << COCK3D_DIALSROW4ON);				//RJS 26Jan98
//	adptr->detailmask |= (1 << COCK3D_PANELIMAPDSPLIT);				//RJS 26Jan98
//	adptr->detailmask |= (1 << COCK3D_PANELGLASSFRONT);			//RJS 25Mar98

//DEAD	if (View_Point->PolyPitEnabled())							//PD 11Dec96
//DEAD		POLYGON.SetCrossProduct(FALSE);							//PD 11Dec96

	adptr->acclocksec = (timesec<<8)/60;
	timesec /= 60;
	adptr->acclockmin = (timesec<<8)/60;
	timesec /= 60;
	adptr->acclockhour = (timesec<<8)/12;	//60;
	//so each hour is worth 21.3 units on the clock (out of 256)
	//hour units = acclockhour + (21.3 * acclockmin)/256
	adptr->acclockhour += ((adptr->acclockmin * 213)/2560);

	adptr->acwingspam = 255- ((WingSpan * 255)/5791);	// 0 feet to 190 feet
//	adptr->acwingspam = 255- ((WingSpan * 255)/5486);	// 0 feet to 180 feet

	Float	ydsrange = RequiredRange;
	ydsrange *= 0.0984;

	adptr->acgunrange = (SLong(ydsrange) * 255)/5000;		// 0 to 5000 yds

	UByte	gunswitch = 0;
	UByte	rocketswitch = 0;
	SLong	launcher = Manual_Pilot.ControlledAC2->weap.weapontype & LT_MASK;

	if (launcher != LT_BULLET)
	{
		gunswitch = 1;
		if (launcher != LT_ROCKET)
			rocketswitch = 1;
	}

	adptr->gunotherswitch = gunswitch;
	adptr->bombrocketswitch = rocketswitch;

	if (Manual_Pilot.ControlledAC2->weap.UseIntFuel)
		adptr->fuelswitch = 1;
	else
		adptr->fuelswitch = 0;

	if (_Replay.Record)
		adptr->lightguncamera = 1;
	else
		adptr->lightguncamera = 0;

	adptr->acgyrocompassflip = -adptr->acgyrocompass;

	if (radarTimer > -1)										//RJS 07Apr99
	{
		radarTimer -= View_Point->FrameTime();
		if (radarTimer < 0)
		{
			radarTimer = 0;
			adptr->lightgunsight = 1;
		}
	}
	else
		adptr->lightgunsight = 0;

	if (adptr->ENGINELEFTIN >= BS_DAMLV2)
		adptr->lightfire = 1;
	else
		adptr->lightfire = 0;

	//stall light (high revs thing from Craig...)

	//gear ... don't need
//	if (adptr->acleglowerl == 0)
//		adptr->lightlanding = 1;
//	else
//		adptr->lightlanding = 0;

	if (Manual_Pilot.ControlledAC2->weap.UseIntFuel)			//RJS 14Apr99
		adptr->acfuelext = 0;									//RJS 14Apr99
	else														//RJS 14Apr99
		adptr->acfuelext = 1;									//RJS 14Apr99
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AircraftAnim
//Author		Paul.   
//Date			Wed 27 Mar 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::AircraftAnim(AircraftAnimData* adptr,Bool pitset)
{
//DeadCode MS 30Nov98 	if (!Three_Dee.IsPaused() && !pitset && (object_obj3d->ItemPtr->Status.size == AirStrucSize))
//DeadCode MS 30Nov98 	{
//DeadCode MS 30Nov98 		AirStrucPtr	acptr = (AirStrucPtr) object_obj3d->ItemPtr;
//DeadCode MS 30Nov98 		if (acptr->fly.pModel)
//DeadCode MS 30Nov98 		{
//DeadCode MS 30Nov98 			WorldStuff*	worldptr = mobileitem::currworld;				//RJS 12Jan98
//DeadCode MS 30Nov98 
//DeadCode RJS 27Aug98 			if (	adptr->aclegsuspl
//DeadCode RJS 27Aug98 				|| 	adptr->aclegsuspr
//DeadCode RJS 27Aug98 				||	adptr->aclegsuspf
//DeadCode RJS 27Aug98 				||	adptr->aclegsuspb	)
//DeadCode RJS 27Aug98 			{
//DeadCode RJS 27Aug98 				if (	adptr->LEFTWHEEL
//DeadCode RJS 27Aug98 					||	adptr->RIGHTWHEEL
//DeadCode RJS 27Aug98 					||	adptr->FRONTWHEEL
//DeadCode RJS 27Aug98 					||	adptr->BACKWHEEL	)
//DeadCode RJS 27Aug98 				{
//DeadCode RJS 27Aug98 					// Throw off sparks if on runway...
//DeadCode RJS 27Aug98 
//DeadCode RJS 27Aug98 					if (!adptr->hasdust)
//DeadCode RJS 27Aug98 					{
//DeadCode RJS 27Aug98 						adptr->hasdust = TRUE;
//DeadCode RJS 27Aug98 						Trans_Obj.LaunchDustTrail2((mobileitem*)object_obj3d->ItemPtr,*worldptr);
//DeadCode RJS 27Aug98 						Manual_Pilot.DeathSequenceOverride(object_obj3d->ItemPtr,AUTO_CRASHSKID);
//DeadCode RJS 27Aug98 					}
//DeadCode RJS 27Aug98 				}
//DeadCode RJS 27Aug98 				else
//DeadCode RJS 27Aug98 				{
//DeadCode RJS 27Aug98 					adptr->hasdust = FALSE;
//DeadCode RJS 27Aug98 					if (!adptr->justlanded)
//DeadCode RJS 27Aug98 					{
//DeadCode RJS 27Aug98 						adptr->justlanded = TRUE;
//DeadCode RJS 27Aug98 						_Miles.PlayOnce(FIL_SFX_TYRE_SCREECH1,object_obj3d->ItemPtr);		//RJS 23Feb98
//DeadCode RJS 27Aug98 					}
//DeadCode RJS 27Aug98 				}
//DeadCode RJS 27Aug98 			}
//DeadCode RJS 27Aug98 			else
//DeadCode RJS 27Aug98 			{
//DeadCode RJS 27Aug98 				adptr->hasdust = FALSE;
//DeadCode RJS 27Aug98 				adptr->justlanded = FALSE;
//DeadCode RJS 27Aug98 			}
//DeadCode MS 30Nov98 
//DeadCode MS 30Nov98 			if (View_Point)
//DeadCode MS 30Nov98 			{
//DeadCode MS 30Nov98 				SLong	rpm = acptr->fly.pModel->Inst.Rpm1;
//DeadCode MS 30Nov98 				SLong	mph = acptr->fly.pModel->Inst.ActualSpeed;
//DeadCode MS 30Nov98 
//DeadCode MS 30Nov98 				if ((mph < 50) && (rpm > 0))
//DeadCode MS 30Nov98 				{
//DeadCode MS 30Nov98 					adptr->exhaustframe = 0;
//DeadCode MS 30Nov98 
//DeadCode MS 30Nov98 					SLong	atimer = adptr->animtimer - View_Point->FrameTime();
//DeadCode MS 30Nov98 					if (atimer <= 0)
//DeadCode MS 30Nov98 					{
//DeadCode MS 30Nov98 						int			maxframe = 32;
//DeadCode MS 30Nov98 						int			count = 0;
//DeadCode MS 30Nov98 						SLong		xpos,ypos,zpos;
//DeadCode MS 30Nov98 						ShapeNum	theShape;
//DeadCode MS 30Nov98 
//DeadCode MS 30Nov98 						atimer = maxframe - ((maxframe * mph)/50);
//DeadCode MS 30Nov98 						if ((rpm > 7000) && (object_obj3d->Shape == F86))
//DeadCode MS 30Nov98 							theShape = SOOT2;
//DeadCode MS 30Nov98 						else
//DeadCode MS 30Nov98 							theShape = SOOT;
//DeadCode MS 30Nov98 
//DeadCode MS 30Nov98 						count = GetVapourPoint(acptr,count,LT_CONTRAIL,xpos,ypos,zpos);
//DeadCode MS 30Nov98 						while (count)
//DeadCode MS 30Nov98 						{
//DeadCode MS 30Nov98 							Trans_Obj.LaunchSmokePuff((mobileitem*)object_obj3d->ItemPtr,theShape,xpos,ypos,zpos,*worldptr);
//DeadCode MS 30Nov98 							count = GetVapourPoint(acptr,count,LT_CONTRAIL,xpos,ypos,zpos);
//DeadCode MS 30Nov98 						}
//DeadCode MS 30Nov98 					}
//DeadCode MS 30Nov98 
//DeadCode MS 30Nov98 					adptr->animtimer = atimer;
//DeadCode MS 30Nov98 				}
//DeadCode MS 30Nov98 			}
//DeadCode MS 30Nov98 		}
//DeadCode MS 30Nov98 	}
	if (adptr->shooting)
		adptr->muzzleflash = !adptr->muzzleflash;
	else
		adptr->muzzleflash = 0;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CalcTrailDeltas
//Author		Robert Slater
//Date			Thu 18 Sep 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
UWord	shape::CalcTrailDeltas(	UByteP	thisdrawnobj,
								UByteP	lastdrawnobj,
								UWord	radius,
								SWord	&xoff, SWord &yoff)
{
	DoPointStruc dopoint0,dopoint2;
	Obj3DPtr	 objold = (Obj3DPtr) lastdrawnobj;
	Obj3DPtr	 objnew = (Obj3DPtr) thisdrawnobj;
	SLong		valid = 0;
	SWord		angleofcyl = 0;
	SWord		sin_ang, cos_ang;

	xoff = 0;
	yoff = 0;

	if (objold && objnew)
	{
		Float	opposite, adjacent;								//RJS 03Dec98
		SWord	angleofcyl;

		dopoint0.bodyx.f = objold->Body.X.f;
		dopoint0.bodyy.f = objold->Body.Y.f;
		dopoint0.bodyz.f = objold->Body.Z.f;

		dopoint2.bodyx.f = objnew->Body.X.f;
		dopoint2.bodyy.f = objnew->Body.Y.f;
		dopoint2.bodyz.f = objnew->Body.Z.f;

		if (	(dopoint0.bodyz.f > 0)								
 			||	(dopoint2.bodyz.f > 0)	)							
 		{
			if (	(dopoint0.bodyz.f < 1)							
				||	(dopoint2.bodyz.f < 1)	)
			{
		 		current_screen->zclipline(dopoint0,dopoint2);
	 	
				objold->Body.X.f = dopoint0.bodyx.f;
				objold->Body.Y.f = dopoint0.bodyy.f;
				objold->Body.Z.f = dopoint0.bodyz.f;

			}
				
			objnew->Body.X.f = dopoint2.bodyx.f;
			objnew->Body.Y.f = dopoint2.bodyy.f;
			objnew->Body.Z.f = dopoint2.bodyz.f;

			_matrix.body2screen(dopoint0);						
	 		_matrix.body2screen(dopoint2);						

			opposite = dopoint0.screeny.f - dopoint2.screeny.f;		//RJS 03Dec98
 			adjacent = dopoint2.screenx.f - dopoint0.screenx.f;	//RJS 03Dec98

//DeadCode DAW 07Apr99 			valid = 1;

			if (opposite || adjacent)							//RJS 03Dec98
			{
				Float	res = 10430.37835047*FPATan(adjacent,opposite);

//DeadCode RJS 03Dec98 				angleofcyl = Math_Lib.HighArcTan(adjacent,opposite);
 				angleofcyl = SWord(res);
 				angleofcyl -= ANGLES_90Deg;

				Math_Lib.high_sin_cos((Angles) angleofcyl,sin_ang,cos_ang);		//PD 13Nov97
				xoff = (sin_ang * radius) / ANGLES_FRACT;				
  				yoff = (cos_ang * radius) / ANGLES_FRACT;

				valid = 1;										//DAW 07Apr99
			}
//DeadCode RJS 03Dec98 			else
//DeadCode RJS 03Dec98 			{
//DeadCode RJS 03Dec98 				xoff = radius;
//DeadCode RJS 03Dec98 				yoff = 0;
//DeadCode RJS 03Dec98 
//DeadCode RJS 03Dec98 				if (adjacent)
//DeadCode RJS 03Dec98 				{
//DeadCode RJS 03Dec98 					xoff = 0;
//DeadCode RJS 03Dec98 					yoff = radius;
//DeadCode RJS 03Dec98 				}
//DeadCode RJS 03Dec98 			}
		}
	}

	return(valid);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SampleSmokePnt
//Author		Robert Slater
//Date			Tue 16 Sep 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	shape::SampleSmokePnt(	UByteP		smkinfo,
								SWord		&listindex,
								UByteP		instr_ptr,
								SWord		&Stores,
								UWord		LifeTime	)
{
	Bool	validpoint = TRUE;

	if (SamplePntTime)
	{
		DOLAUNCHER_PTR	ptr = (DOLAUNCHER_PTR) instr_ptr;
		TrailRecord*	trailptr = &traillist[listindex];
		SmokeTypeP		smkptr = (SmokeTypeP) smkinfo;
		SLong			xcoord = ptr->posx;
		SLong			ycoord = ptr->posy;
		SLong			zcoord = ptr->posz;
		SLong			lifetime;
		SLong			wx, wy, wz;
		SWord			index = listindex;
		MATRIX  		omat;										
		MATRIX_PTR		obj_matrix = &omat;							
		UWord			scaleback;

		if (!LifeTime)											//RJS 09Apr98
			LifeTime = smkptr->LifeTime;						//RJS 09Apr98

//		if (Three_Dee.IsPaused())								//RJS 27Feb98
//			SamplePntTime = FALSE;

		trailptr->SampleTime -= View_Point->FrameTime();			//RJS 08Jan98
		if (trailptr->SampleTime < 0)							//RJS 08Jan98
			trailptr->SampleTime = smkptr->SampleTime;			//RJS 02Feb98
		else													//RJS 02Feb98
			validpoint = FALSE;									//RJS 02Feb98

		// -1 is infinite....
		if (Stores != -1)
		{
			Stores-=Timer_Code.FRAMETIME;						//RJS 25Mar99

			if (Stores < 0)
				Stores = 0;
		}

		if (Stores)
		{
			lifetime = LifeTime;								//RJS 08Dec97

//			if (trailptr->lifetime && (lifetime > 500))
//				lifetime = trailptr->lifetime;

 			if (trailptr->nextlist)
 			{
 				Coords3DList*	nextptr = traillist[trailptr->nextlist].thelist;
 				if (nextptr)
 				{
 					wx = nextptr->trailpoint.gx;
 					wy = nextptr->trailpoint.gy;
 					wz = nextptr->trailpoint.gz;

 					SHAPE.AddNewVapourPoint(trailptr,wx,wy,wz,lifetime,smkptr->FadeTime);
 					lifetime = trailptr->lifetime;
 				}

 				trailptr->nextlist = 0;
 			}

			// Every frame....

 			wx = xcoord << shapescale;
 			wy = ycoord << shapescale;
 			wz = zcoord << shapescale;

			_matrix.generate2(	object_obj3d->AngH,
								object_obj3d->AngC,
								object_obj3d->AngR,
								obj_matrix);

			scaleback = _matrix.transform(obj_matrix,wx,wy,wz);
			wx >>= (16-scaleback);
			wy >>= (16-scaleback);
			wz >>= (16-scaleback);

			wx += trailptr->lastwx;
			wy += trailptr->lastwy;
			wz += trailptr->lastwz;

			AddNewVapourPoint(trailptr,wx,wy,wz,lifetime,smkptr->FadeTime);

			if (trailptr->nopoints > smkptr->MaxPoints)
			{
				switch (smkptr->DeadAction)
				{
				case DEADSMK_DEFAULT:
	 				trailptr->bitshift = 0;
//DEADCODE DAW 23/04/99 				listindex = 0;				//RJS 12Apr99
//DEADCODE DAW 12/04/99 					listindex = -index;
					DetatchVapourStream(index,LIFETIME_VAPOUR);
					listindex = NextFreeVapour(0,0,0,smkinfo);										//RJS 23Apr99
					if (listindex)																	//RJS 23Apr99
						AddNewVapourPoint(&traillist[listindex],wx,wy,wz,lifetime,smkptr->FadeTime);//RJS 23Apr99
					break;
				case DEADSMK_SMOKECLOUD:
					AddSmokeCloud(trailptr,smkptr->CloudShape,index);
					break;
				}
			}
		}
		else
		{
			listindex = 0;
			DetatchVapourStream(index,LIFETIME_VAPOUR);	//RJS 09Apr98
		}
	}

	return(validpoint);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DrawSmokeTrail
//Author		Robert Slater
//Date			Tue 16 Sep 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SLong	shape::DrawSmokeTrail(	SWord		index,
								UByteP		smkinfo,
								ULong		LifeTime,
								SWord		xdrift,
								SWord		ydrift,
								SWord		zdrift,
								Bool		valid	)
{
	SLong	totpoints = 0;
	if (index)
	{
		if (index < 0)											
			index = -index;

		if (index > MAX_VAPOURS)								//RJS 21Jan99
			_Error.EmitSysErr(__FILE__":(DOSMKTRAIL)    Shouldn't be this : %d\n",index);

		TrailRecordPtr	TrailPtr = &traillist[index];			//RJS 09Apr98
																//RJS 09Apr98
		if (smkinfo)											//RJS 09Apr98
			TrailPtr->SmkDescPtr = smkinfo;						//RJS 09Apr98
		else													//RJS 09Apr98
		{
			smkinfo = TrailPtr->SmkDescPtr;						//RJS 09Apr98
			LifeTime = TrailPtr->lifetime;						//RJS 13Apr98
		}

		if (!smkinfo)
			return 0;

		SmokeTypeP		ptr = (SmokeTypeP) smkinfo;
		Coords3DList*	apoint;
		Coords3DList*	*lastpointptr;						
		Coords3DList*	nextpoint;							
		Coords3DList*	lastpoint;							
		SLong			nocyls = 0;
		SLong			lifegone, lifeleft;						//RJS 24Nov98
		SLong			distz,lastdistz;
		SWord			grow2time = ptr->Growth;
		UWord			startradius = ptr->Radius;
		SWord			radius;
		SWord			radiusinc;
 		SByte			frameno;
		SLong			degrade;
		ShapeNum		trailshape = (ShapeNum) ptr->Shape;
		SLong			degcnt;
		UByteP			lastdrawnobj = NULL;
		UByteP			thisdrawnobj = NULL;
		UWord			failedcnt = 0;
		VapAnimDat		AnimDat;
		VapAnimDatPtr	AnimDataPtr;
		SLong			timesincebirth;
		SLong			totcount = 0;
		SWord			uy,vy;
		SWord			hdist;
		SLong			dragy;
		SWord			Acceleration;
		SLong			reallife;
		SLong			frametime;
		SLong			currtime = View_Point->TimeOfDay();		//RJS 16Jun99

		//If it's a static transient, we want real time...
//		if (TrailPtr->transient)								//RJS 16Jun99
			frametime = currtime - TrailPtr->currTime;			//RJS 16Jun99
//		else													//RJS 16Jun99
//			frametime = Timer_Code.FRAMETIME;					//RJS 16Jun99

 		lastpointptr = &TrailPtr->thelist;
		if (TrailPtr->nopoints > 4)								//RJS 20Jan99
			degrade = ptr->DegradeDist << 4;					//RJS 20Jan99
		else													//RJS 20Jan99
			degrade = 100000000;								//RJS 20Jan99

		distz = 0;
		degcnt = 0;

		apoint = lastpoint = TrailPtr->thelist;			
 		while (apoint)
 		{
 			nextpoint = apoint->next;
			lifeleft = reallife = apoint->lifeleft;				//RJS 14Apr98
 			if (!Three_Dee.IsPaused())							//RJS 27Feb98
 			{
				if (apoint->KillMe)								//RJS 17Feb99
 				{
					// Add to dead list...
					apoint->next = TrailPtr->FakePointPtr;
					TrailPtr->FakePointPtr = apoint;
 
 					TrailPtr->nopoints--;
 					*lastpointptr = nextpoint;

					lifeleft = 0;
 				}
				else
				{
					reallife -= frametime;						//RJS 16Jun99
					if (reallife <= 0)							//RJS 14Jun99
						reallife = 0;							//RJS 14Jun99
																//RJS 14Jun99
					apoint->lifeleft = reallife;				//RJS 14Jun99
				}
			}

 			if (!apoint->KillMe)	//(lifeleft)		//RJS 20Apr99
 			{
				if (!apoint->lifeleft)	apoint->KillMe = 1;		//RJS 14Jun99
				if (apoint->LifeTime)							//RJS 16Jun99
				{
					lifegone = apoint->LifeTime - lifeleft;
//DeadCode DAW 27Sep99 					if (lifegone > 0)							//RJS 27Sep99
//DeadCode DAW 27Sep99 					{
//DeadCode DAW 27Sep99 						radius = startradius + ((startradius*lifegone)/grow2time);
//DeadCode DAW 27Sep99 						apoint->radius = radius;
//DeadCode DAW 27Sep99 					}
//DeadCode DAW 27Sep99 					else
//DeadCode DAW 27Sep99 						apoint->radius = startradius;
					if (lifegone >= 0)							//RJS 27Sep99
						radius = startradius + ((startradius*lifegone)/grow2time);
					else
					{
						// For some reason lifeleft > total LifeTime,
						// so set lifeleft to LifeTime...
						apoint->lifeleft = apoint->LifeTime;	//RJS 27Sep99
						lifegone = 0;							//RJS 27Sep99
						radius = startradius;					//RJS 27Sep99
					}											//RJS 27Sep99

 					apoint->radius = radius;
 					if (!degcnt || !nextpoint)
 					{
						if (lifegone > ptr->FadeTime)
						{
							if (ptr->FadeShape)
								trailshape = ptr->FadeShape;
						}

						distz = Three_Dee.AddVapourObject(	trailshape,
															(UByteP)apoint,
															lastdrawnobj,
															thisdrawnobj,
															failedcnt);

						if (thisdrawnobj)
						{
							AnimDat.depth = ptr->Depth;;		//initial fade depth...
							AnimDat.drawit = CalcTrailDeltas(thisdrawnobj,
													 		lastdrawnobj,
													 		radius,
 													 		apoint->xdelta,apoint->ydelta);//RJS 15Apr98

							AnimDataPtr = (VapAnimDatPtr) &((Obj3DPtr)thisdrawnobj)->AngR;
							*AnimDataPtr = AnimDat;

							lastdrawnobj = thisdrawnobj;
							nocyls++;
						}
						else
							failedcnt++;

//DeadCode DAW 21Jun99 #ifndef NDEBUG
//DeadCode DAW 21Jun99 						if ((apoint->radius == 0) || ((apoint->LifeTime-apoint->FadeTime)==0))
//DeadCode DAW 21Jun99 								INT3;
//DeadCode DAW 21Jun99 #endif

						degcnt = distz / degrade;
					}												
					else											
						degcnt--;
				}

 				lastpointptr = &apoint->next;

				totcount++;
 			}
 
 			lastpoint = apoint;									//AMM 26Mar99
 			apoint = nextpoint;
 		}

		apoint = TrailPtr->thelist;
		if (apoint && !valid && !TrailPtr->transient)
			apoint->KillMe = 1;							//RJS 17Feb99

		totpoints = TrailPtr->nopoints;				//RJS 12Mar99

 		if (View_Point->FrameTime())							//RJS 16Jun99
			TrailPtr->currTime = currtime;						//RJS 16Jun99
	}

	return (totpoints);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UpdateVapourCoords
//Author		Robert Slater
//Date			Thu 29 May 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::UpdateVapourCoords(itemptr	itm,animptr&	aptr)
{
	ShapeDescPtr		sdptr = SHAPESTUFF.GetShapePtr(itm->shape);//RJS 23Apr99
	int					wpnum, index, oldindex;
	WeapAnimData*		weapon;
	MoveGunAnimData*	adptr = (MoveGunAnimData*) aptr;
	SLong				wx = itm->World.X;
	SLong				wy = itm->World.Y;
	SLong				wz = itm->World.Z;
	int					weapcnt = 1;
	SWord				animsize = sdptr->AnimDataSize;
	UByte				instsize = sizeof(DOLAUNCHER) + 1;
	DOLAUNCHER_PTR		lptr;
	UByteP				instr_ptr;
	UByteP				base_ptr;
	UWord				instruction;
	SmokeTypeP			smkptr = NULL;
	UWord				lifetime;
	ULong				reallifetime;
	SByte				TType;
	Bool				validpoint = TRUE;						//RJS 30Nov98
	SLong				driftx,drifty,driftz;					//RJS 10Mar98
	Bool				justlanded=FALSE;								//RJS 11Mar98
	UByte				weaplaunchertype;
	SLong				nopoints;
	//Remove all trails at altitude, because we have no wind.
	Bool				toohigh;
								
	if (itm->World.Y >= FT_34000)								//RJS 27Jun99	//CSB 01/07/99	
		toohigh = TRUE;
	else
		toohigh = FALSE;

	switch (SHAPESTUFF.GetShapeScale(sdptr))				
 	{														
 		case SHP_1CM:										
 			shapescale = 0;									
 			break;											
 		case SHP_4CM:										
 			shapescale = 2;									
 			break;											
 		case SHP_16CM:										
 			shapescale = 4;									
 			break;											
 	}			

	pTrailItm = itm;//RJS 02Sep98
	weapcnt = adptr->nolaunchers;								//RJS 09Apr98

	Math_Lib.high_sin_cos((ANGLES )((mobileitem*)itm)->hdg,v_sin_ang,v_cos_ang);

	base_ptr = (UByteP )sdptr + sdptr->LauncherDataSize;

	for (wpnum = 0; wpnum < weapcnt; wpnum++)
	{
		oldindex = 0;
		weapon = (WeapAnimData*) &adptr->weaponlaunchers[wpnum];
		if (weapon)
		{
			instr_ptr = base_ptr + (instsize * wpnum);
			instr_ptr++;

			lptr = (DOLAUNCHER_PTR) instr_ptr;
			if (	!lptr->damageflag
				|| (aptr[lptr->damageflag] < lptr->damthresh)	)
			{
				TType = lptr->trailtype;
				if (TType < 0)
				{
					if (TType == -1)
					{
						if (toohigh)							//DAW 28Jun99
						{
							index = weapon->hdg;
							if (index > 0)
							{
								SHAPE.DetatchVapourStream(index,LIFETIME_VAPOUR);
								weapon->hdg = 0;
							}
						}
						else
						{
							if (	(weapon->LauncherType == LT_FUEL)
								||	(weapon->LauncherType == LT_INTFUEL)	)	//RJS 10May99
							{
								TType = TRAIL_VAPOUR;
								smkptr = (SmokeTypeP) &SmokeTrlList[TRAIL_VAPOUR];
								lifetime = smkptr->LifeTime;

								weaplaunchertype = weapon->LauncherType;//MS 30Nov98
							}
						}
					}
					else
					{
						// Generic one for engines...
						if (lptr->lnchrtype == LT_ENGINE)		//MS 30Nov98
						{
							UByte	dolaunch = LT_ENGINE;

							if (itm->Status.size == AirStrucSize)				//RJS 20Jan99
							{
								AirStrucPtr	acptr = (AirStrucPtr) itm;
								if (!toohigh)
								{
									SLong	rpm = acptr->fly.pModel->Inst.Rpm1;
									SLong	mph = acptr->fly.pModel->Inst.ActualSpeed;

									if (aptr[lptr->damageflag] < BS_DAMLV2)
									{
										dolaunch = LT_CONTRAIL;
										TType = TRAIL_CONTRAIL;
										smkptr = (SmokeTypeP) &SmokeTrlList[TType];
										lifetime = smkptr->LifeTime;

										if (weapon->LauncherType != LT_CONTRAIL)
										{
											if (	(object_obj3d->Shape == F86)
												&&	(acptr->fly.thrustpercent > 33))
											{
												if (!MMC.Sky.Contrails((AirStrucPtr)itm, reallifetime))
												{
								 					dolaunch = LT_FUEL;
													if (rpm > 7000)
													{
														TType = TRAIL_EXHAUSTDIRTY;
														smkptr = (SmokeTypeP) &SmokeTrlList[TType];
														lifetime = smkptr->LifeTime;
													}
													else
													{
														TType = TRAIL_EXHAUST;
														smkptr = (SmokeTypeP) &SmokeTrlList[TType];
														lifetime = smkptr->LifeTime;
													}
												}
											}
										}
									}
									else
									{
										dolaunch = LT_FUEL;
										TType = TRAIL_ENGINEPLUME;
										smkptr = (SmokeTypeP) &SmokeTrlList[TType];
										lifetime = smkptr->LifeTime;
									}
							
									index = weapon->hdg;
									if (index > 0)
									{
										if (traillist[index].SmkDescPtr != (UByteP)smkptr)
										{
											SHAPE.DetatchVapourStream(index,LIFETIME_VAPOUR);
											weapon->hdg = 0;
										}
										weapon->LauncherType = LT_ENGINE;
									}
									else
										weapon->LauncherType = LT_ENGINE;

									if (weapon->LauncherType != dolaunch)
									{
										if (dolaunch != LT_CONTRAIL)
										{
											weapon->LauncherType = dolaunch;
											oldindex = Trans_Obj.LaunchVapourStream((UByteP)weapon,(ShapeNum)object_obj3d->Shape);//RJS 09Apr98
										}
										weapon->pitch = -1;
									}
								}
								else
								{
									index = weapon->hdg;
									if (index > 0)
									{
										SHAPE.DetatchVapourStream(index,LIFETIME_VAPOUR);
										weapon->hdg = 0;
									}
									weapon->LauncherType = LT_ENGINE;
								}
							}

							weaplaunchertype = dolaunch;
						}
						else
						{
							// This is a generic, inherited trail...
							// ... make sure we sample no extra points!

							smkptr = NULL;
							weaplaunchertype = LT_CONTACT;
						}
					}											//MS 30Nov98
				}
				else
				{
					if (toohigh)
					{
						index = weapon->hdg;
						if (index > 0)
						{
							SHAPE.DetatchVapourStream(index,LIFETIME_VAPOUR);
							weapon->hdg = 0;
						}
						TType = -1;
					}
					else
					{
						smkptr = (SmokeTypeP) &SmokeTrlList[TType];	//RJS 09Apr98
						lifetime = smkptr->LifeTime;

						weaplaunchertype = weapon->LauncherType;	//MS 30Nov98
					}
				}

				if (TType != -1)
				{
					// min sample distance is 1024 cm per frame, which is 256m/s
					SLong	mindist = (51200 * Timer_Code.FRAMETIME)/100;
					SLong	distscale;

					validpoint = TRUE;
					driftx = 0;										//RJS 10Mar98
					drifty = 0;										//RJS 10Mar98
					driftz = 0;										//RJS 10Mar98

					index = weapon->hdg;	//RJS 23Apr99

					switch (weaplaunchertype)					//RJS 29Nov98
					{
						case LT_CONTRAIL:
						{
							if (MMC.Sky.Contrails((AirStrucPtr) itm, reallifetime))
							{
								//Cannot implement different lifetime until we extend
								//smoke trail coordinate type to include this master lifetime
								lifetime = reallifetime;

								oldindex = Trans_Obj.LaunchVapourStream((UByteP)weapon,(ShapeNum)object_obj3d->Shape);//RJS 09Apr98
								index = weapon->hdg;					//RJS 12Jan98
								if (index > 0)
								{
									traillist[index].lastwx = wx;
									traillist[index].lastwy = wy;
									traillist[index].lastwz = wz;
									traillist[index].nextlist = oldindex;

									validpoint = SampleSmokePnt((UByteP)smkptr,(SWord&)weapon->hdg,instr_ptr,weapon->pitch,lifetime);	//RJS 02Feb98
								}
							}
							else
							{
								index = weapon->hdg;				//RJS 12Jan98
								if (index > 0)
								{
									SHAPE.DetatchVapourStream(index,LIFETIME_VAPOUR);//RJS 09Apr98
									weapon->hdg = 0;				//RJS 12Jan98
								}
							}
							break;
						}
						case LT_FUNNEL:							//RJS 06Jun99
						{
							index = weapon->hdg;
							if (index > 0)
							{
								//Not really a trail, but samples points...
								//...and draws them seperately.

								traillist[index].lastwx = wx;
								traillist[index].lastwy = wy;
								traillist[index].lastwz = wz;

								validpoint = SampleSmokePnt((UByteP)smkptr,(SWord&)weapon->hdg,instr_ptr,weapon->pitch,lifetime);
								DrawTempBlobTrail(index,(UByteP)smkptr,lifetime,validpoint);

								index = 0;
							}
							break;
						}
						case LT_INTFUEL:
						case LT_FUEL:
						{
							index = weapon->hdg;					//RJS 12Jan98
							if (index > 0)
							{
								if (traillist[index].thelist)
								{
									SLong	dist;
									SLong	dx,dy,dz;

									dx = wx - traillist[index].lastwx;
									dy = wy - traillist[index].lastwy;
									dz = wz - traillist[index].lastwz;

									dist = Math_Lib.distance3d(dx,dy,dz);
									if (dist >= mindist)
									{
										distscale = dist / mindist;

										traillist[index].lastwx = wx;
										traillist[index].lastwy = wy;
										traillist[index].lastwz = wz;
										traillist[index].nextlist = oldindex;

										validpoint = SampleSmokePnt((UByteP)smkptr,(SWord&)weapon->hdg,instr_ptr,weapon->pitch,lifetime);	//RJS 02Feb98
									}
									else
									{
										if (SamplePntTime)
										{
											SLong	oldx, oldy, oldz;

											oldx = traillist[index].lastwx;
											oldy = traillist[index].lastwy;
											oldz = traillist[index].lastwz;

											traillist[index].lastwx = wx;
											traillist[index].lastwy = wy;
											traillist[index].lastwz = wz;

											SampleSmokePnt((UByteP)smkptr,(SWord&)weapon->hdg,instr_ptr,weapon->pitch,lifetime);
											validpoint = FALSE;

											traillist[index].lastwx = oldx;
											traillist[index].lastwy = oldy;
											traillist[index].lastwz = oldz;
										}
									}
								}
								else
								{
									traillist[index].lastwx = wx;
									traillist[index].lastwy = wy;
									traillist[index].lastwz = wz;
									traillist[index].nextlist = oldindex;

									validpoint = SampleSmokePnt((UByteP)smkptr,(SWord&)weapon->hdg,instr_ptr,weapon->pitch,lifetime);	//RJS 02Feb98
								}
							}
							break;
						}
						case LT_DUST:
						{
							index = weapon->hdg;					//RJS 12Jan98
							if (index > 0)
							{
								traillist[index].lastwx = wx;
								traillist[index].lastwy = Land_Scape.GetGroundLevel(itm);
								traillist[index].lastwz = wz;
								traillist[index].nextlist = oldindex;

								validpoint = SampleSmokePnt((UByteP)smkptr,(SWord&)weapon->hdg,instr_ptr,weapon->pitch,lifetime);	//RJS 2Feb98
							}
							break;
						}
						case LT_MUDDY:
						{
//DeadCode RJS 25Nov98 							if (justlanded)	  //NOT INITIALISED!!
//DeadCode RJS 25Nov98 								oldindex = Trans_Obj.LaunchVapourStream((UByteP)weapon,(ShapeNum)object_obj3d->Shape);//RJS 09Apr98
//DeadCode RJS 25Nov98 							else
//DeadCode RJS 25Nov98 							{
//DeadCode RJS 25Nov98 								if (weapon->hdg > 0)
//DeadCode RJS 25Nov98 								{
//DeadCode RJS 25Nov98 									SHAPE.DetatchVapourStream(weapon->hdg,LIFETIME_VAPOUR);//RJS 09Apr98
//DeadCode RJS 25Nov98 									weapon->hdg = 0;			
//DeadCode RJS 25Nov98 								}
//DeadCode RJS 25Nov98 							}
//DeadCode RJS 25Nov98 
//DeadCode RJS 25Nov98 							index = weapon->hdg;
//DeadCode RJS 25Nov98 							if (index > 0)
//DeadCode RJS 25Nov98 							{
//DeadCode RJS 25Nov98 								traillist[index].lastwx = wx;
//DeadCode RJS 25Nov98 								traillist[index].lastwy = wy;
//DeadCode RJS 25Nov98 								traillist[index].lastwz = wz;
//DeadCode RJS 25Nov98 								traillist[index].nextlist = 0;
//DeadCode RJS 25Nov98 
//DeadCode RJS 25Nov98 								validpoint = SampleSmokePnt((UByteP)smkptr,(SWord&)weapon->hdg,instr_ptr,weapon->pitch,lifetime);
//DeadCode RJS 25Nov98 								drifty = (((mobileitem*)itm)->velhori << 7)>>10;
//DeadCode RJS 25Nov98 							}
//DeadCode RJS 25Nov98 							break;
							index = weapon->hdg;					//RJS 12Jan98
							if (index > 0)
							{
								if (traillist[index].thelist)
								{
									SLong	dist;
									SLong	dx,dy,dz;
									SLong	ox,oy,oz;

									ox = traillist[index].lastwx;
									oy = traillist[index].lastwy;
									oz = traillist[index].lastwz;

									dx = wx - ox;
									dy = wy - oy;
									dz = wz - oz;

									traillist[index].lastwx = wx;
									traillist[index].lastwy = wy;
									traillist[index].lastwz = wz;
									traillist[index].nextlist = oldindex;

									validpoint = SampleSmokePnt((UByteP)smkptr,(SWord&)weapon->hdg,instr_ptr,weapon->pitch,lifetime);

									dist = Math_Lib.distance3d(dx,dy,dz);
									if (dist < 100)
									{
										if (SamplePntTime)
										{
											validpoint = FALSE;
											if (dist == 0)
												drifty = -View_Point->FrameTime();
										}

										traillist[index].lastwx = ox;
										traillist[index].lastwy = oy;
										traillist[index].lastwz = oz;
									}
								}
								else
								{
									traillist[index].lastwx = wx;
									traillist[index].lastwy = wy;
									traillist[index].lastwz = wz;
									traillist[index].nextlist = oldindex;

									validpoint = SampleSmokePnt((UByteP)smkptr,(SWord&)weapon->hdg,instr_ptr,weapon->pitch,lifetime);//RJS 25Nov98
								}
							}
							break;
						}
						case LT_JETDUST:
						{
							if (itm->Status.size == AirStrucSize)
							{
								AirStrucPtr	acptr = (AirStrucPtr) itm;
								SLong		gheight = acptr->fly.pModel->GroundHeight;
								SLong		height = wy - gheight;
								SWord		realpitch = acptr->pitch;

								if ((height < 4000) && (realpitch > ANGLES_0Deg))
								{
									oldindex = Trans_Obj.LaunchVapourStream((UByteP)weapon,(ShapeNum)object_obj3d->Shape);
									index = weapon->hdg;
									if (index > 0)
									{
										weapon->pitch = -1;

										traillist[index].lastwx = wx;
										traillist[index].lastwy = wy;
										traillist[index].lastwz = wz;
										traillist[index].nextlist = 0;

										if (traillist[index].LaunchCountdown < 0)
										{
											SLong	veltime = 300 - acptr->velhori;
											veltime /= 10;
											traillist[index].LaunchCountdown = veltime;

											validpoint = SampleDustPnt((UByteP)smkptr,(SWord&)weapon->hdg,instr_ptr,lifetime,height,realpitch);
										}
										else
											traillist[index].LaunchCountdown -= View_Point->FrameTime();
									}
								}
								else
								{
									if (weapon->hdg > 0)
									{
										SHAPE.DetatchVapourStream(weapon->hdg,LIFETIME_VAPOUR);//RJS 09Apr98
										weapon->hdg = 0;			
									}	
								}
							}
							break;
						}
					}

//Test					if (weaplaunchertype != LT_DUST)
//Dead					nopoints = DrawSmokeTrail((SWord)weapon->hdg,(UByteP)smkptr,lifetime,0,drifty,0,validpoint);//RJS 10Mar98
					nopoints = DrawSmokeTrail(index,(UByteP)smkptr,lifetime,0,drifty,0,validpoint);	//RJS 23Apr99
					if (nopoints && (weapcnt > 4))
					{
						AircraftAnimData*	adptr = (AircraftAnimData*) aptr;
						// Set hassmoked flag...
						adptr->hassmoked = 1;
					}
//Test					else
//Test						DrawDirtTrail((SWord)weapon->hdg,(UByteP)smkptr,lifetime,validpoint);//RJS 10Dec98
				}
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UpdateSmokeDriftCoords
//Author		Robert Slater
//Date			Mon 24 Nov 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::UpdateSmokeDriftCoords(itemptr	itm,animptr&	aptr)
{
	ShapeDescPtr		sdptr = SHAPESTUFF.GetShapePtr(itm->shape);//RJS 23Apr99
	int					index;
	WeapAnimData*		weapon;
	MoveGunAnimData*	adptr = (MoveGunAnimData*) aptr;
	SLong				wx = itm->World.X;
	SLong				wy = itm->World.Y;
	SLong				wz = itm->World.Z;
	SWord				animsize = sdptr->AnimDataSize;
	UByte				instsize = sizeof(DOLAUNCHER) + 1;
	DOLAUNCHER_PTR		lptr;
	UByteP				instr_ptr;
	UByteP				base_ptr;
	UWord				instruction;
	SWord				xdrift,ydrift,zdrift;
	SWord				sin_ang,cos_ang;
	SLong				distpframe;
	SmokeTypeP			smkptr;
	UWord				lifetime;
	Bool				validpoint;

	switch (SHAPESTUFF.GetShapeScale(sdptr))				
 	{														
 		case SHP_1CM:										
 			shapescale = 0;									
 			break;											
 		case SHP_4CM:										
 			shapescale = 2;									
 			break;											
 		case SHP_16CM:										
 			shapescale = 4;									
 			break;											
 	}

	v_sin_ang = 0;
	v_cos_ang = 0;

//	if (!Three_Dee.IsPaused())										//RJS 27Feb98
//		SamplePntTime = TRUE;									

	base_ptr = (UByteP )sdptr + sdptr->LauncherDataSize;

	weapon = (WeapAnimData*) &adptr->weaponlaunchers[0];
	if (weapon)
	{
		instr_ptr = base_ptr;
		instr_ptr++;

		lptr = (DOLAUNCHER_PTR) instr_ptr;
		if (	!lptr->damageflag
			|| (aptr[lptr->damageflag] < lptr->damthresh)	)
		{
			if (lptr->trailtype > -1)
			{
				smkptr = (SmokeTypeP) &SmokeTrlList[lptr->trailtype];//RJS 08Dec97
				lifetime = smkptr->LifeTime;					//RJS 08Dec97

				index = weapon->hdg;								//RJS 12Jan98
				if (index > 0)									//RJS 13Apr99
				{
					traillist[index].lastwx = wx;
					traillist[index].lastwy = wy;
					traillist[index].lastwz = wz;
					traillist[index].nextlist = 0;
					validpoint = TRUE;

//					if (SamplePntTime)
//					{
//						if (traillist[index].LaunchCountdown < 0)
//						{
//							traillist[index].LaunchCountdown = 4;
//							validpoint = SampleSmokePnt((UByteP)smkptr,(SWord&)weapon->hdg,instr_ptr,weapon->pitch,lifetime);	//RJS 02Feb98
//						}
//						else
//							traillist[index].LaunchCountdown -= View_Point->FrameTime();
//
//						distpframe = (Timer_Code.FRAMETIME * MMC.wind.speed)/10;
//						Math_Lib.high_sin_cos((ANGLES )MMC.wind.direction,sin_ang,cos_ang);
//
//						xdrift = (distpframe*sin_ang)>>15;
//						zdrift = (distpframe*cos_ang)>>15;
//						ydrift = 200;
//					}
//					else
//					{
//						xdrift = 0;
//						ydrift = 0;
//						zdrift = 0;
//					}
//
//					DrawSmokeTrail((SWord)weapon->hdg,(UByteP)smkptr,lifetime,xdrift,ydrift,zdrift,validpoint);	//RJS 02Feb98

					SLong	dist = object_obj3d->Body.Z.f;
//DeadCode RJS 22Apr99 					Bool	dotrail;
//DeadCode RJS 22Apr99 
//DeadCode RJS 22Apr99 					if (dist > 120000)
//DeadCode RJS 22Apr99 						dotrail = FALSE;
//DeadCode RJS 22Apr99 					else
//DeadCode RJS 22Apr99 					{
//DeadCode RJS 22Apr99 						dotrail = TRUE;
//DeadCode RJS 22Apr99 						if (dist >= 100000)
//DeadCode RJS 22Apr99 						{
//DeadCode RJS 22Apr99 							UWord	oldshape = object_obj3d->Shape;
//DeadCode RJS 22Apr99 
//DeadCode RJS 22Apr99 							itm->shape = PLUME1;
//DeadCode RJS 22Apr99 							Three_Dee.do_object_dummy(itm);
//DeadCode RJS 22Apr99 							itm->shape = (ShapeNum)oldshape;
//DeadCode RJS 22Apr99 						}
//DeadCode RJS 22Apr99 					}
//DeadCode RJS 22Apr99 
//DeadCode RJS 22Apr99 					if (dotrail)
//DeadCode RJS 22Apr99 					{
						if (SamplePntTime)
						{
							if (traillist[index].SampleTime < 1)
							{
								SWord	stores = weapon->pitch;
								SLong	degradetime = 10;						//RJS 07Jun99
//DeadCode RJS 13May99 								SLong	nojobbies = 1;

								if (dist < 40000)
								{
									if (dist < 20000)
									{
//DeadCode RJS 13May99 										nojobbies = 3;
										lifetime = (dist * lifetime)/20000;
									}
//DeadCode RJS 13May99 									else
//DeadCode RJS 13May99 										nojobbies += (2*(40000 - dist))/20000;
								}
								else
								{
									dist -= 40000;
									degradetime = 10 + ((100 * dist)/80000);//1 sec sampling is slowest...
								}
								
								traillist[index].SampleTime = degradetime;

								stores -= 1;
								if (stores < 0)
								{
									SHAPE.DetatchVapourStream((SWord)weapon->hdg,0);
									weapon->hdg = 0;
									weapon->pitch = 0;
								}
								else
								{
									Coords3D	pos;
									SLong		xcoord = lptr->posx << shapescale;
									SLong		ycoord = lptr->posy << shapescale;
									SLong		zcoord = lptr->posz << shapescale;

									xcoord += wx;
									ycoord += wy;
									zcoord += wz;

									pos.X = xcoord;
									pos.Y = ycoord;
									pos.Z = zcoord;

									weapon->pitch = (Angles) stores;

									// Should only get here if launcher is in visible anyway...
									WorldStuff	*world = mobileitem::currworld;
									SWord		vhori;

									if (degradetime)
									{
										vhori = Math_Lib.rnd(smkptr->VelHori/2);
										Trans_Obj.LaunchSmokePuff2((mobileitem*)itm,&pos,SMKDRK,SMKMED,vhori,smkptr->VelY,Math_Lib.rnd(),lifetime,lifetime,*world);
									}
									else
									{
										SLong		sno;
										UWord		randval;
										SWord		poovel = smkptr->VelY>>1;
										SWord		poovelh = smkptr->VelHori>>1;
										UWord		reallife;

//DeadCode RJS 13May99 										for (sno=0; sno < nojobbies; sno++)
//DeadCode RJS 13May99 										{
											randval = Math_Lib.rnd();
											vhori = Math_Lib.rnd(smkptr->VelHori);
											reallife = (lifetime * (smkptr->VelHori - vhori))/smkptr->VelHori;
											if (vhori > poovelh)
												Trans_Obj.LaunchSmokePuff2((mobileitem*)itm,&pos,BSMKE,0,vhori,poovel+Math_Lib.rnd(poovel),Math_Lib.rnd(),reallife,65535,*world);
											else
											{
												if (randval > 45000)
													Trans_Obj.LaunchSmokePuff2((mobileitem*)itm,&pos,SMKDRK,SMKMED,vhori,smkptr->VelY,Math_Lib.rnd(),reallife,lifetime,*world);
												else
													Trans_Obj.LaunchSmokePuff2((mobileitem*)itm,&pos,SMKDRK,0,vhori,poovel+Math_Lib.rnd(poovel),Math_Lib.rnd(),(reallife*randval)/45000,65536,*world);
											}
//DeadCode RJS 13May99 
//DeadCode RJS 13May99 										}
									}
								}
							}
							else
								traillist[index].SampleTime -= View_Point->FrameTime();
						}
//DeadCode RJS 22Apr99 					}
//DeadCode RJS 22Apr99 					else
//DeadCode RJS 22Apr99 					{
//DeadCode RJS 22Apr99 						// Put temporary shape into the binary tree...
//DeadCode RJS 22Apr99 						UWord	oldshape = object_obj3d->Shape;
//DeadCode RJS 22Apr99 
//DeadCode RJS 22Apr99 						itm->shape = PLUME1;
//DeadCode RJS 22Apr99 						Three_Dee.do_object_dummy(itm);
//DeadCode RJS 22Apr99 						itm->shape = (ShapeNum)oldshape;
//DeadCode RJS 22Apr99 
//DeadCode RJS 22Apr99 						traillist[index].SampleTime = 0;
//DeadCode RJS 22Apr99 					}
				}
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddNewVapourPoint
//Author		Robert Slater
//Date			Fri 20 Sep 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::AddNewVapourPoint(TrailRecord* trailptr,SLong	wx, SLong wy, SLong wz, ULong	lifetime, ULong fadetime)
{
	Coords3DList*	anewpoint;									//RJS 02Jun97

	anewpoint = new Coords3DList;
	if (anewpoint)												//RJS 02Jun97
	{
		anewpoint->next = trailptr->thelist;					//RJS 18Sep97
		anewpoint->trailpoint.gx = wx;							//RJS 18Sep97
		anewpoint->trailpoint.gy = wy;							//RJS 18Sep97
		anewpoint->trailpoint.gz = wz;							//RJS 18Sep97
		anewpoint->lifeleft = lifetime;							//RJS 14Apr98
		anewpoint->radius = 1;									//RJS 21Jun99
		anewpoint->LifeTime = lifetime;							//RJS 15Apr98
		anewpoint->FadeTime = fadetime;							//RJS 24Nov98
		anewpoint->KillMe = 0;					//RJS 17Feb99

		trailptr->thelist = anewpoint;							//RJS 18Sep97
		trailptr->lifetime = lifetime;							//RJS 13Apr98
		trailptr->nopoints++;										//RJS 29May97
#ifndef	NDEBUG
	//Get ROB very quickly!
	if (!anewpoint->LifeTime)									//RJS 21Jun99
		INT3;
#endif
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		KillVapourStream
//Author		Robert Slater
//Date			Mon 23 Sep 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::KillVapourStream(int	index)
{
 	Coords3DList*		apoint, nextpoint;
	if (index < 0)											
		index = -index;

	if (index >= MAX_VAPOURS)					
		_Error.EmitSysErr(__FILE__":(KILL_VAPOUR)    Shouldn't be this : %d\n",index);

 	traillist[index].thelist->Wipe();
//DeadCode RJS 21Apr99  	apoint = traillist[index].thelist;
//DeadCode RJS 21Apr99  	while (apoint)												//RJS 02Jun97
//DeadCode RJS 21Apr99  	{															//RJS 02Jun97
//DeadCode RJS 21Apr99  		nextpoint = (Coords3DListPtr) apoint->next;				//RJS 02Jun97
//DeadCode RJS 21Apr99 																//RJS 02Jun97
//DeadCode RJS 21Apr99  		delete apoint;											//RJS 02Jun97
//DeadCode RJS 21Apr99  		apoint = nextpoint;										//RJS 02Jun97
//DeadCode RJS 21Apr99  	}															//RJS 02Jun97
																//RJS 02Jun97
 	traillist[index].thelist = NULL;							//RJS 02Jun97
 	traillist[index].lifetime = 0;								//RJS 02Jun97
 	traillist[index].nopoints = 0;								//RJS 02Jun97
 	traillist[index].bitshift = 0;								//RJS 02Jun97
	traillist[index].nextlist = 0;								//RJS 03Jun97
	traillist[index].beendrawn = 0;								//RJS 03Jun97
//DeadCode RJS 14Apr98 	traillist[index].birthtime = 0;								//RJS 18Sep97
	traillist[index].SampleTime = 0;							//RJS 08Jan98
//DeadCode RJS 17Feb99 	traillist[index].FakePointPtr = NULL;						//RJS 17Mar98
//DeadCode RJS 06May99 	traillist[index].InitVelH = 0;								//RJS 09Apr98
//DeadCode RJS 06May99 	traillist[index].InitVelY = 0;								//RJS 17Mar98
//DeadCode RJS 06May99 	traillist[index].Acceleration = 0;							//RJS 17Mar98
	traillist[index].SmkDescPtr = NULL;							//RJS 09Apr98
	traillist[index].cloudlaunched = FALSE;						//RJS 03Jul98
	traillist[index].transient = 0;
	traillist[index].currTime = 0;								//RJS 16Jun99
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DetatchVapourStream
//Author		Robert Slater
//Date			Tue 27 May 1997
//
//Description	Hands over the mantle to a transient item.....
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SLong	shape::DetatchVapourStream(int	index,int	LifeTime, bool novapour)
{
	SLong	newlife = 0;
	ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(pTrailItm->shape);//DAW 19May99
	if (sdptr->Type.VapourType != TRAIL_OFF)
	{
		if (index > 0)
		{
//DeadCode DAW 19May99 			if (traillist[index].thelist && LifeTime && (traillist[index].nopoints > 1))//RJS 13Apr99
			if (	traillist[index].thelist
				&&	LifeTime
				&& (traillist[index].nopoints > 1)
				&&	!novapour						)
			{
				ShapeNum	detachshape = (ShapeNum) 0;
				SmokeTypeP	smkdptr = (SmokeTypeP) traillist[index].SmkDescPtr;//RJS 09Apr98
				if (smkdptr)
					detachshape = smkdptr->DetachShape;

				if (detachshape > 0)									//RJS 10Mar98
				{
					WorldStuff*	worldptr = mobileitem::currworld;
					TrailRecordPtr	TrailPtr = &traillist[index];
					Coords3DList*	apoint = TrailPtr->thelist;
					Coords3DList*	fpoint = apoint;
					SLong	lastx,lasty,lastz;

					// Calculate mid point of trail...
 					while (apoint)
 					{
						if (apoint->next == NULL)
						{
							lastx = apoint->trailpoint.gx;
							lasty = apoint->trailpoint.gy;
							lastz = apoint->trailpoint.gz;
						}
						apoint = apoint->next;
 					}

					lastx += fpoint->trailpoint.gx;
					lasty += fpoint->trailpoint.gy;
					lastz += fpoint->trailpoint.gz;

					lastx >>= 1;
					lasty >>= 1;
					lastz >>= 1;

					TrailPtr->transient = 1;

  					if (!Trans_Obj.LaunchVapourTransient((mobileitem*) pTrailItm,		//RJS 12Apr99
	  													lastx,							//RJS 22Jan99
  														lasty,							//RJS 22Jan99
  														lastz,							//RJS 22Jan99
  														index,
  														500,			//give it 5 secs before degrade
  														*worldptr,
  														SMKSHP))	//always this shape	//RJS 07Jul99
						AddVapourStreamToDeadList(index,pTrailItm);			//DAW 06Apr99
				}
				else
					AddVapourStreamToDeadList(index,pTrailItm);					//RJS 09Apr98
			}
			else
				AddVapourStreamToDeadList(index,pTrailItm);						//RJS 09Apr98
		}
		else
		{
			//Must be a static trail....
			if (index)
			{
				SmokeTrailAnimData*	adptr = (SmokeTrailAnimData*) pTrailItm->Anim;

				if (adptr->nopoints || novapour)					//RJS 19May99
				{
					if (adptr->nopoints)
					{
						MakeProbes[newprobecnt].action = PROBER_KILL;
						MakeProbes[newprobecnt++].itm = (TransientItem*) pTrailItm;
					}
					else
						AddVapourStreamToDeadList(-index,pTrailItm);					//RJS 12Apr99
				}
				else
				{
					// Prepare the trail for abandonment...
					if (adptr->thelist == 0)
					{
						index = -index;

						Coords3DList*	apoint = traillist[index].thelist;
						while (apoint)
						{
							if (apoint->lifeleft > newlife)
								newlife = apoint->lifeleft;
					
							apoint = apoint->next;
						}
						if (newlife)								//AMM 26Mar99
						{
							if (!adptr->isDegraded)					//RJS 06May99
							{
								adptr->isDegraded = TRUE;				//RJS 06May99

								MakeProbes[newprobecnt].action = PROBER_DEGRADE;
								MakeProbes[newprobecnt].index = index;
								MakeProbes[newprobecnt++].itm = (TransientItem*)pTrailItm;
							}
						}
						else
							AddVapourStreamToDeadList(index,pTrailItm);					//RJS 12Apr99
					}
					else
					{
						// shouldn't get here...
						Trans_Obj.RemoveTransientItemFromTrailList((TransientItemPtr)pTrailItm);//RJS 18Feb99
					}
				}
			}
		}
	}

	return(newlife);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddVapourStreamToDeadList
//Author		Robert Slater
//Date			Thu 9 Apr 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::AddVapourStreamToDeadList(int	index, ItemPtr	itm)
{
	if (index > 0)
	{
		int	i;
		for (i=0; i < VapDeadCnt; i++)
		{
			if (VapDeadList[i] == index)
				break;
		}

		if (i==VapDeadCnt)
		{
			if (VapDeadCnt == REAL_MAX_VAPOURS)
				_Error.EmitSysErr(__FILE__":Vapour Dead List is full");
			else
			{
				SLong	absindex = index;
				if (absindex < 0)
					absindex = -absindex;

				if (absindex > MAX_VAPOURS)
					INT3;

				VapDeadList[VapDeadCnt++] = index;
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		KillVapourStreamDeadList
//Author		Robert Slater
//Date			Thu 9 Apr 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::KillVapourStreamDeadList()
{
	int	i;

//Deaded by RJS 17Feb99...
//dead	for (i=0; i < VapDeadCnt; i++)
//dead		KillVapourStream(VapDeadList[i]);
//dead
//dead	VapDeadCnt = 0;

//DeadCode RJS 17Feb99 	if (SamplePntTime)
//	{
		// and kill unwanted trail points...
		for (i=0; i < REAL_MAX_VAPOURS; i++)
		{
//			Coords3DList* apoint = traillist[i].FakePointPtr;
//			Coords3DList* dpoint;
//  
//			while (apoint)
//			{						
//				dpoint = apoint;
//				apoint = apoint->next;
//
//				delete dpoint;
//			}

			traillist[i].FakePointPtr->Wipe();
			traillist[i].FakePointPtr = NULL;
		}

		for (i=0; i < VapDeadCnt; i++)					//RJS 17Feb99
			KillVapourStream(VapDeadList[i]);			//RJS 17Feb99

		VapDeadCnt = 0;									//RJS 17Feb99
//	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DetatchAllVapourStreams
//Author		Robert Slater
//Date			Tue 27 May 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SLong	shape::DetatchAllVapourStreams(itemptr	itm,int	LifeTime, bool novapour)
{
	MinAnimData*		aptr = (MinAnimData*) itm->Anim;
	UWord				noLaunchers;
	ShapeDescPtr		sdptr = SHAPESTUFF.GetShapePtr(itm->shape);//RJS 17Nov98
	SLong				newlife = 0;

	if (	(SHAPESTUFF.GetShapeScale(sdptr) != SHP_GRP)		//RJS 19May99
		&&	(sdptr->Type.VapourType != TRAIL_OFF)		)		//RJS 19May99
	{
		noLaunchers = aptr->nolaunchers;							//RJS 17Nov98
		if (noLaunchers)											//RJS 17Nov98
		{
			int					index;
			WeapAnimData*		weapon;
			MoveGunAnimData*	adptr = (MoveGunAnimData*) itm->Anim;

			pTrailItm = itm;//RJS 02Sep98

			for (index=0; index < noLaunchers; index++)			//RJS 17Nov98
			{
				weapon = &adptr->weaponlaunchers[index];
				if (weapon && weapon->hdg)									//RJS 08Apr99
				{
					if ((weapon->LauncherType & LT_MASK) == LT_SMKTRAILS)	//RJS 13Apr99
					{
						newlife = DetatchVapourStream(weapon->hdg,LifeTime,novapour);//RJS 19May99
						if (newlife==0)						//RJS 21Jan99
						{
							//if transient death, alert transite...
							if (weapon->hdg < 0)			//RJS 06Apr99
								newlife = -1;				//RJS 06Apr99

							weapon->hdg = 0;				//DAW 06Apr99
						}
					}
				}
			}
		}
	}

	return(newlife);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NextFreeVapour
//Author		Robert Slater
//Date			Tue 27 May 1997
//
//Description	
//				acceleration is -g (scaled up) * resistance percentage
//												   (100% is no drag)
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
UByte	shape::NextFreeVapour(SWord	velh,SWord vely, SWord	resistance,UByteP smkptr)
{
	int		index;			
	UByte	retval = 0;

	if (View_Point)
	{
		for (index=1; index < MAX_VAPOURS; index++)
		{
			if (!traillist[index].thelist && !traillist[index].beendrawn)
			{
				if (smkptr)
				{
					SmokeTypeP	smkdptr = (SmokeTypeP) smkptr;

					velh = smkdptr->VelHori;
					vely = smkdptr->VelY;
					resistance = smkdptr->Resistance;
				}

				resistance = (resistance << 7) / 100;
				resistance = 128 - resistance;

				traillist[index].beendrawn = 1;						//RJS 17Sep97
//DeadCode RJS 06May99 				traillist[index].InitVelY = vely;
//DeadCode RJS 06May99 				traillist[index].InitVelH = velh;
//DeadCode RJS 06May99 				traillist[index].Acceleration = -100 * resistance;
				traillist[index].SmkDescPtr = smkptr;
				traillist[index].cloudlaunched = FALSE;
//Dead...				traillist[index].FakePointPtr = NULL;	//always maintain the deadlist...
				traillist[index].transient = 0;
				traillist[index].currTime = View_Point->TimeOfDay();//RJS 16Jun99
				retval = index;
				break;
			}
		}
	}

	return(retval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BlokesItemAnim
//Author		Robert Slater
//Date			Tue 1 Jun 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::BlokesItemAnim(BlokesAnimData* adptr)
{
	if (SLong(object_obj3d->Body.Z.f) < 80000)				//RJS 10Jun99
	{
		bool	ejectblokes = false;

		ItemPtr		itm = NULL;
		SLong		placecnt = 0;
		Coords3D	*placelist = NULL;

		if (adptr->nearestuid)
		{
			itm = (ItemPtr)Persons2::ConvertPtrUID((UniqueID)adptr->nearestuid);
			if (itm && !itm->Status.deadtime)
			{
				if (!adptr->timer)
				{
					placelist = new Coords3D[48];
					if (placelist)
						placelist[0] = itm->World;

					ejectblokes = true;
				}
				else
				{
					SLong	realtime = adptr->timer;
					realtime -= View_Point->FrameTime();
					if (realtime < 0)
						realtime = 0;

					adptr->timer = UWord(realtime);
				}
			}
		}
		else
		{
			if (adptr->itemstate == ALIVE)
			{
				ejectblokes = true;

				adptr->itemstate = DEAD;
				adptr->timer = 12000;		//give them 2 mins to come back

				itm = Three_Dee.NearestAliveThing(object_obj3d->ItemPtr);
				if (itm)
				{
					adptr->nearestuid = itm->uniqueID.count;
					
					placelist = new Coords3D[48];
					if (placelist)
						placelist[0] = itm->World;
				}
			}
		}

		if (ejectblokes)
		{
			if (itm && placelist)
			{
				ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(itm->shape);
				animptr			adptrtmp = itm->Anim;
				ShapeNum		newshp;
				SLong			xpos,ypos,zpos;
				MinAnimData*	mad;

				if (SHAPESTUFF.GetShapeScale(sdptr) == SHP_GRP)
				{
					UByteP		instr_ptr = (UByteP )sdptr + sdptr->liveshpref;

					// Search for nearest strongest....

					while (GetGroupElement(instr_ptr,newshp,xpos,ypos,zpos))
					{
						mad = (MinAnimData*) adptrtmp;
						if (mad->itemstate == ALIVE)
						{
							placelist[placecnt].X = xpos + itm->World.X;
							placelist[placecnt].Y = ypos + itm->World.Y;
							placelist[placecnt++].Z = zpos + itm->World.Z;
						}

						adptrtmp += SHAPE.GetElementAnimOffset(newshp);
					}
				}
				else
					placecnt = 1;
			}

			Trans_Obj.PointBlokes(object_obj3d->ItemPtr,BLOKRN,object_obj3d->ItemPtr->World,12,placelist,placecnt);//RJS 11Jun99
		}

		if (placelist)
			delete []placelist;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		WeapItemAnim
//Author		Paul.   
//Date			Mon 1 Apr 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::WeapItemAnim(WeapAnimData* adptr)
{
//DeadCode RJS 01Jun99 	DirectItemAnim((DirectAnimData* )adptr);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetLauncherData
//Author		Paul.   
//Date			Mon 1 Apr 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::SetLauncherData(WeapAnimData* adptr, ShapeNum shpno)
{
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		drawsphere
//Author		Robert Slater
//Date			Tue 16 Dec 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::drawsphere(	int	vertex,
							int	radius,
							int	colour,
							int	animflag,
							int	animscale,
							int	transdepth,
							Bool	smoothed,
							int	halowidth,
							int	lumdepth,
							int	animflag2	)
{
//DeadCode RJS 21Apr99 	UByteP	adptr = (UByteP) object_obj3d->AnimPtr; 			
	DoPointStruc	dopointr, dopoint0;
	SWord			RealRadius,BandWidth;
	Colour			thecol = (Colour) colour;

	transdepth *= 25;

	dopointr = dopoint0 = newco[vertex];
	dopointr.bodyx.f += radius;
	_matrix.body2screen(dopointr);

	RealRadius = dopointr.screenx.f - dopoint0.screenx.f;

	if (animflag)
		thecol = (Colour) (colour + (GlobalAdptr[animflag]/animscale));

//DEAD	POLYGON.SetPixelWidth(1);

	if (!halowidth)
	{
		if (smoothed)
		{
			if (lumdepth)
			{
				if (animflag2)
					lumdepth -= (GlobalAdptr[animflag2]/animscale);

				if (lumdepth > 0)
				{
					POLYGON.createsphere(thecol,(LUMINOSITYTYPE)lumdepth);
					POLYGON.createsphvert(dopoint0,RealRadius);
					POLYGON.drawsphere();
				}
			}
			else
			{
				if (animflag2)
					transdepth -= ((GlobalAdptr[animflag2]*25)/animscale);

				POLYGON.createsphere(thecol,transdepth);
				POLYGON.createsphvert(dopoint0,RealRadius);
				POLYGON.drawsphere();
			}
		}
		else
		{
			POLYGON.createsphere(thecol);
			POLYGON.createsphvert(dopoint0,RealRadius);
			POLYGON.drawsphere();
		}
	}
	else
	{
		BandWidth = (RealRadius * halowidth) >> 7;
		if (BandWidth)
		{
			if (animflag2)
				lumdepth -= (GlobalAdptr[animflag2]/animscale);

			if (lumdepth > 0)
			{
				POLYGON.createhalo(thecol,lumdepth);
				POLYGON.createsphvert(dopoint0,RealRadius,BandWidth);
				POLYGON.drawsphere();
			}
		}
	}

	current_screen->SetLuminosity(LUM_OFF);
	current_screen->SetTransparency(SMOKED_OFF);
}

void	shape::DrawHeatHaze(int	vertex,
							int	radius,
							int	colour	)
{
	DoPointStruc	dopointr, dopoint0;
	SWord			RealRadius;
	Colour			thecol = (Colour) colour;

	dopointr = dopoint0 = newco[vertex];
	dopointr.bodyx.f += radius;
	_matrix.body2screen(dopointr);

	RealRadius = dopointr.screenx.f - dopoint0.screenx.f;

	POLYGON.createhaze(thecol);
	POLYGON.createsphvert(dopoint0,RealRadius);
	POLYGON.drawsphere();
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RealImapSphere
//Author		Robert Slater
//Date			Tue 16 Dec 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::RealImapSphere(	int	vertex,
								int	radius,
								int	imageno,
								int	minx,
								int	miny,
								int	maxx,
								int	maxy,
								int	animflag,
								int	animscale	)
{
//DeadCode RJS 21Apr99 	UByteP	adptr = (UByteP) object_obj3d->AnimPtr; 			
	DoPointStruc	dopointr, dopoint0;
	SWord			RealRadius;
	ImageMapNumber	imapno = (ImageMapNumber)imageno;

	dopointr = dopoint0 = newco[vertex];
	dopointr.bodyx.f += radius;
	_matrix.body2screen(dopointr);

	RealRadius = dopointr.screenx.f - dopoint0.screenx.f;

	if (animflag)
	{
		UWord	frameno = GlobalAdptr[animflag] / animscale;
		SWord	sizey = maxy - miny;

		miny += (frameno * sizey);
		maxy = miny + sizey;
	}

//DEAD	POLYGON.SetPixelWidth(1);
	
 	POLYGON.createsphere(imapno);
	POLYGON.createsphvert(dopoint0,RealRadius,minx,miny,maxx,maxy);
	POLYGON.drawsphere();

//DEAD	POLYGON.SetPixelWidth(1);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		imapsphere
//Author		Martin Alderton
//Date			Tue 16 Apr 1996
//
//Description		
//				
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::imapsphere(	UWord vertex,
						UWord 	radius,	
						ImageMapNumber imapno,
						SWord	minx, SWord	miny,
						SWord	maxx, SWord	maxy,
						bool	ispivoted	)
{
 	DoPointStruc dopoint0,dopoint1,dopoint2,dopoint3;
	Float	scaleradius = radius;

	dopoint0 = dopoint1 = dopoint2 = dopoint3 = newco[vertex];

	if (dopoint0.bodyz.f > 100.0)								//RJS 26Nov98
	{															//RJS 24Jun97
		SWord	width,height;

		width = maxx - minx;
		height = maxy - miny;

		if (ClipSphereRatio(dopoint0,dopoint1,dopoint2,dopoint3,scaleradius,width,height,ispivoted)==FALSE)//RJS 26Nov98
		{
			_matrix.body2screen(dopoint0);							//RJS 26Jun97
			_matrix.body2screen(dopoint1);							//RJS 26Jun97
//			if ((dopoint1.screenx.f - dopoint0.screenx.f) > 2.0)
			{
//DEAD				if (object_obj3d->Shape!=SUN)
//DEAD					POLYGON.SetPixelWidth(1<<Save_Data.pixelsize);

				POLYGON.createpoly(imapno);

				POLYGON.createvert(dopoint0,minx,miny);
				POLYGON.createvert(dopoint1,maxx,miny);
				POLYGON.createvert(dopoint2,maxx,maxy);
				POLYGON.createvert(dopoint3,minx,maxy);

				POLYGON.drawpoly();

//DEAD				POLYGON.SetPixelWidth(1);
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		imapsphereQuad
//Author		Robert Slater
//Date			Fri 20 Feb 1998
//
//Description	Quad sphere to make things BIGGER
//
// 	dopoints:	2----3----2
//				|	 |	  |
//				|	 |	  |
//				1----0----1
//				|	 |	  |
//				|	 |	  |
//				2----3----2
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::imapsphereQuad(	UWord vertex,
							UWord 	radius,	
							ImageMapNumber imapno,
							SWord	minx, SWord	miny,
							SWord	maxx, SWord	maxy	)
{
 	DoPointStruc dopoint0,dopoint1,dopoint2,dopoint3,dopoint4;
	Float	scaleradius = radius;
	Float	scaleradius2 = (radius<<1);

	dopoint0 = dopoint1 = dopoint2 = dopoint3 = dopoint4 = newco[vertex];

	if (dopoint0.bodyz.f > 1)								
	{															
		if (dopoint0.bodyz.f < 1172)							
			current_screen->SetTransparency(SMOKED_OFF);		

		//Crappy line fix...
//		minx++;
//		miny++;
		maxy-=2;
	  	maxx--;

		dopoint1.bodyx.f -= scaleradius;						
																
		dopoint2.bodyx.f -= scaleradius;						
		dopoint2.bodyy.f += scaleradius;						
																
		dopoint3.bodyy.f += scaleradius;

		_matrix.SetClipFlags(dopoint1);
		_matrix.SetClipFlags(dopoint2);
		_matrix.SetClipFlags(dopoint3);
																
//		_matrix.body2screen(dopoint1);							
//		_matrix.body2screen(dopoint2);							
//		_matrix.body2screen(dopoint3);							

		dopoint4 = dopoint1;

//DEAD		if (object_obj3d->Shape!=SUN)
//DEAD			POLYGON.SetPixelWidth(1<<Save_Data.pixelsize);

		POLYGON.createpoly(imapno);
		POLYGON.createvert(dopoint0,maxx,maxy);
		POLYGON.createvert(dopoint1,minx,maxy);
		POLYGON.createvert(dopoint2,minx,miny);
		POLYGON.createvert(dopoint3,maxx,miny);
		POLYGON.drawpoly();

		dopoint2.bodyx.f += scaleradius2;						
		dopoint1.bodyx.f += scaleradius2;

		_matrix.SetClipFlags(dopoint1);
		_matrix.SetClipFlags(dopoint2);

//		_matrix.body2screen(dopoint1);							
//		_matrix.body2screen(dopoint2);							

		POLYGON.createpoly(imapno);
		POLYGON.createvert(dopoint0,maxx,maxy);
		POLYGON.createvert(dopoint3,maxx,miny);
		POLYGON.createvert(dopoint2,minx,miny);
		POLYGON.createvert(dopoint1,minx,maxy);
		POLYGON.drawpoly();

		dopoint2.bodyy.f -= scaleradius2;						
		dopoint3.bodyy.f -= scaleradius2;						

		_matrix.SetClipFlags(dopoint3);
		_matrix.SetClipFlags(dopoint2);

//		_matrix.body2screen(dopoint2);							
//		_matrix.body2screen(dopoint3);

		POLYGON.createpoly(imapno);
		POLYGON.createvert(dopoint0,maxx,maxy);
		POLYGON.createvert(dopoint1,minx,maxy);
		POLYGON.createvert(dopoint2,minx,miny);
		POLYGON.createvert(dopoint3,maxx,miny);
		POLYGON.drawpoly();

		dopoint2.bodyx.f -= scaleradius2;						

		dopoint1 = dopoint4;

		_matrix.SetClipFlags(dopoint1);
//		_matrix.body2screen(dopoint2);							

		POLYGON.createpoly(imapno);
		POLYGON.createvert(dopoint0,maxx,maxy);
		POLYGON.createvert(dopoint3,maxx,miny);
		POLYGON.createvert(dopoint2,minx,miny);
		POLYGON.createvert(dopoint1,minx,maxy);
		POLYGON.drawpoly();

//DEAD		POLYGON.SetPixelWidth(1);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		imaptrailcyl
//Author		Robert Slater
//Date			Wed 17 Sep 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::imaptrailcyl(UWord   vertex1, UWord vertex2,
						ImageMapNumber imapno,
						SWord	minix, SWord	miniy,
						SWord	maxix, SWord	maxiy,
						UWord	width, UWord	height,
						UByte	divfactor,
						UByte	flagoffset,
						SWord	xoff0, SWord yoff0,
						SWord	xoff1, SWord yoff1)
{
//DeadCode RJS 21Apr99 	UByteP	adptr = (UByteP) object_obj3d->AnimPtr; 			
//	UByte	frameno = adptr[flagoffset] / divfactor;
//	SWord	minx, miny, maxx, maxy;								
	ULong	thewidth, theheight;
	DoPointStruc dopoint0,dopoint1,dopoint2,dopoint3;
 	Float	xdelt1 = (Float) xoff0;
 	Float	ydelt1 = (Float) yoff0;
 	Float	xdelt2 = (Float) xoff1;
 	Float	ydelt2 = (Float) yoff1;
 	Bool	oldcross;

// 	minx = minix;		
// 	miny = miniy;		
// 	maxx = maxix - 1;	
// 	maxy = maxiy;
 
// 	theheight = maxiy - miniy;
// 
// 	miny += height * frameno;							
// 	maxy = miny + theheight - 1;
  
//DEAD  	oldcross = POLYGON.SetCrossProduct(FALSE);
  
//  	ImageMapNumber	absimapno = (ImageMapNumber )((imapno<0)?-imapno:imapno);
  	ImageMapDescPtr imptr = Image_Map.GetImageMapPtr(imapno);
 
   	dopoint0 = dopoint1 = newco[vertex1];				
   	dopoint2 = dopoint3 = newco[vertex2];

 	dopoint0.bodyx.f += xdelt1;								
  	dopoint0.bodyy.f += ydelt1;
	_matrix.SetClipFlags(dopoint0);
 
  	dopoint1.bodyx.f += -xdelt1;								
 	dopoint1.bodyy.f += -ydelt1;								
	_matrix.SetClipFlags(dopoint1);
 
   	dopoint2.bodyx.f += -xdelt2;								
   	dopoint2.bodyy.f += -ydelt2;								
	_matrix.SetClipFlags(dopoint2);
 
   	dopoint3.bodyx.f += xdelt2;								
   	dopoint3.bodyy.f += ydelt2;								
	_matrix.SetClipFlags(dopoint3);

	andedFlags=CF3D_ALL;
	andedFlags&=dopoint0.clipFlags;
	andedFlags&=dopoint1.clipFlags;
	andedFlags&=dopoint2.clipFlags;
	andedFlags&=dopoint3.clipFlags;
	if (andedFlags==0)
	{
//		if (!doingHW3D)
//		{
//			_matrix.body2screen(dopoint0);
//			_matrix.body2screen(dopoint1);
//			_matrix.body2screen(dopoint2);
//			_matrix.body2screen(dopoint3);
//		}
 
//DEAD   		POLYGON.SetPixelWidth(1<<Save_Data.pixelsize);			
   		POLYGON.createpoly(imapno);								
   																
 		POLYGON.createvert(dopoint3,minix,miniy);					
   		POLYGON.createvert(dopoint2,maxix,miniy);					
   		POLYGON.createvert(dopoint1,maxix,maxiy);					
  		POLYGON.createvert(dopoint0,minix,maxiy);					
   																
   		POLYGON.drawpoly();									
  
//DEAD   		POLYGON.SetPixelWidth(1);
	}
   
//DEAD   	POLYGON.SetCrossProduct(oldcross);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		plaintrailcyl
//Author		Robert Slater
//Date			Mon 12 Jan 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::plaintrailcyl(	UWord   vertex1,
							UWord	vertex2,
							SWord	col,
							SWord	xoff0, SWord yoff0,
							SWord	xoff1, SWord yoff1,
							SWord	fadedepth			)
{
	DoPointStruc dopoint0,dopoint1,dopoint2,dopoint3;

	xoff0 = (xoff0 * 90)>>7;
	xoff1 = (xoff1 * 90)>>7;

	yoff0 = (yoff0 * 90)>>7;
	yoff1 = (yoff1 * 90)>>7;

 	Float	xdelt1 = (Float) xoff0;
 	Float	ydelt1 = (Float) yoff0;
 	Float	xdelt2 = (Float) xoff1;
 	Float	ydelt2 = (Float) yoff1;
 	Bool	oldcross;

	if (fadedepth < SMOKED_LIGHT)
		return;

//DEAD  	oldcross = POLYGON.SetCrossProduct(FALSE);
  
   	dopoint0 = dopoint1 = newco[vertex1];				
   	dopoint2 = dopoint3 = newco[vertex2];

  	dopoint0.bodyx.f += xdelt1;								
  	dopoint0.bodyy.f += ydelt1;								
	_matrix.SetClipFlags(dopoint0);
 
  	dopoint1.bodyx.f += -xdelt1;								
 	dopoint1.bodyy.f += -ydelt1;								
	_matrix.SetClipFlags(dopoint1);
 
   	dopoint2.bodyx.f += -xdelt2;								
   	dopoint2.bodyy.f += -ydelt2;								
	_matrix.SetClipFlags(dopoint2);
 
   	dopoint3.bodyx.f += xdelt2;								
   	dopoint3.bodyy.f += ydelt2;								
	_matrix.SetClipFlags(dopoint3);

	andedFlags=CF3D_ALL;
	andedFlags&=dopoint0.clipFlags;
	andedFlags&=dopoint1.clipFlags;
	andedFlags&=dopoint2.clipFlags;
	andedFlags&=dopoint3.clipFlags;
	if (andedFlags==0)
	{
//		if (!doingHW3D)
//		{
//			_matrix.body2screen(dopoint0);
//			_matrix.body2screen(dopoint1);
//			_matrix.body2screen(dopoint2);
//			_matrix.body2screen(dopoint3);
//		}
 
		current_screen->SetTransparency(fadedepth);

//DEAD   		POLYGON.SetPixelWidth(1);			
   		POLYGON.createpoly((Colour)col);								
   																
 		POLYGON.createvert(dopoint0);					
   		POLYGON.createvert(dopoint1);					
   		POLYGON.createvert(dopoint2);					
  		POLYGON.createvert(dopoint3);					
   																
   		POLYGON.drawpoly();									

		current_screen->SetTransparency(SMOKED_OFF);
	}

//DEAD   	POLYGON.SetCrossProduct(oldcross);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LineStream
//Author		Robert Slater
//Date			Mon 5 Jan 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::LineStream(	UWord	vertex0,
						 	UWord	vertex1,
						 	SWord	xoff0, SWord yoff0,
							SWord	xoff1, SWord yoff1,
							UWord	depth,
							SWord	StartRadius,
							SWord	EndRadius,
							MyGroundVectorPtr	WCylStartP,
							MyGroundVectorPtr	WCylEndP,
							SWord	col,
							SWord	transdepth	)
{
	DoPointStruc dopoint0,dopoint1,dopoint2,dopoint3,dopointRoot,dptmp1,dptmp2;
 	Bool	oldcross;
	Float	RelX, RelY, RelZ;
	Float	RelXStep,RelYStep, RelZStep;
	UWord	counter;
	SLong	xDelta,yDelta;
	SLong	RandxDelta,RandyDelta;
	SLong	xDeltCap,yDeltCap;
	UWord	RSeed;
	SLong	XoffGap;
	SLong	YoffGap;
	SLong	Radius;
	SWord	MaxRadius;
	SWord	RadStep;
	SLong	wXStep, wYStep, wZStep;								
	SLong	wXStart, wYStart, wZStart;							
	Colour	thecol = (Colour) col;
	SLong	MaxDist, Dist;
	DOSETCOLOUR256	tmpinst3;									//RJS 08Jan98
	UByteP	tmpinstptr;
	DOLINE	lineinst;
	DoPointStruc	*dp0ptr,*dp1ptr;

	dp0ptr = &newco[2];
	dp1ptr = &newco[3];

	lineinst.start_vertex = 2;
	lineinst.end_vertex = 3;

	tmpinst3.basecolour = thecol<<1;							//RJS 08Jan98
	tmpinst3.spread = 0;										//RJS 08Jan98
	tmpinst3.imap = 0xFF;										//RJS 08Jan98

	tmpinstptr = (UByteP) &tmpinst3;							//RJS 08Jan98
	dosetcolour256(tmpinstptr);									//RJS 08Jan98

//DeadCode RJS 30Mar98 	if (transdepth == SMOKED_SOLID)
//DeadCode RJS 30Mar98 		transdepth = SMOKED_OFF;

	wXStart = WCylStartP->gx;									
	wYStart = WCylStartP->gy;									
	wZStart = WCylStartP->gz;									

//DEAD 	oldcross = POLYGON.SetCrossProduct(FALSE);

	dopointRoot = newco[vertex0];								
   	dopoint2 = newco[vertex1];

	RelX = dopoint2.bodyx.f - dopointRoot.bodyx.f;
	RelY = dopoint2.bodyy.f - dopointRoot.bodyy.f;
	RelZ = dopoint2.bodyz.f - dopointRoot.bodyz.f;

	wXStep = (WCylEndP->gx - wXStart) / depth;					
	wYStep = (WCylEndP->gy - wYStart) / depth;					
	wZStep = (WCylEndP->gz - wZStart) / depth;					

	XoffGap = (xoff1 - xoff0)/depth;
	YoffGap = (yoff1 - yoff0)/depth;

	RelXStep = RelX / depth;
	RelYStep = RelY / depth;
	RelZStep = RelZ / depth;

	RadStep = (EndRadius - StartRadius)/depth;
	MaxRadius = StartRadius;

	xDelta = xoff0;
	yDelta = yoff0;

//DEAD 	POLYGON.SetPixelWidth(1);

	SLong	xloff, yloff, zloff;
	current_screen->SetTransparency(transdepth);				//RJS 18Jun97

	for (counter = 0; counter < depth; counter++)
	{
		tmpinstptr = (UByteP)&lineinst;
		RSeed = Noise(wXStart,wYStart,wZStart);					//RJS 11Mar98
																//RJS 11Mar98
		RandxDelta = ((RSeed*xDelta)>>7) - xDelta;				//RJS 11Mar98
		RandyDelta = ((RSeed*yDelta)>>7) - yDelta;				//RJS 11Mar98

		*dp0ptr = dopointRoot;									//RJS 11Mar98
		dp0ptr->bodyx.f += RandxDelta;							//RJS 11Mar98
		dp0ptr->bodyy.f += RandyDelta;							//RJS 11Mar98

		if (dp0ptr->bodyz.f > 100)								
		{
			*dp1ptr = *dp0ptr;									//RJS 11Mar98

			RSeed = 256 - RSeed;

			xloff = RSeed * RelXStep;
			yloff = RSeed * RelYStep;
			zloff = RSeed * RelZStep;

			xloff >>= 9;
			yloff >>= 9;
			zloff >>= 9;

			dp0ptr->bodyx.f += xloff;							//RJS 11Mar98
			dp0ptr->bodyy.f += yloff;							//RJS 11Mar98
			dp0ptr->bodyz.f += zloff;							//RJS 11Mar98

			dp1ptr->bodyx.f -= xloff;							//RJS 11Mar98
			dp1ptr->bodyy.f -= yloff;							//RJS 11Mar98
			dp1ptr->bodyz.f -= zloff;							//RJS 11Mar98

			doline(tmpinstptr);									//RJS 11Mar98
		}

		dopointRoot.bodyx.f += RelXStep;
		dopointRoot.bodyy.f += RelYStep;
  		dopointRoot.bodyz.f += RelZStep;

		xDelta += XoffGap;
		yDelta += YoffGap;

		wXStart += wXStep;										//RJS 12Nov97
		wYStart += wYStep;										//RJS 12Nov97
		wZStart += wZStep;										//RJS 12Nov97

		MaxRadius += RadStep;
	}

	current_screen->SetTransparency(SMOKED_OFF);				//RJS 18Jun97

//DEAD 	POLYGON.SetCrossProduct(oldcross);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PlainBlobLine
//Author		Robert Slater
//Date			Thu 11 Dec 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::PlainBlobLine(	UWord	vertex0,
							 	UWord	vertex1,
								UWord	MaxRadius)
{
	DoPointStruc dopoint0,dopoint1,dopoint2,dopoint3,dopointRoot;
 	Bool	oldcross;
	SLong	RelX, RelY, RelZ;
	SLong	RelXStep, RelYStep, RelZStep;
	UWord	counter;
	UWord	RSeed;
	SLong	Radius,RealRadius;

//DEAD 	oldcross = POLYGON.SetCrossProduct(FALSE);

	dopointRoot = newco[vertex0];

	RelX = newco[vertex1].bodyx.f - newco[vertex0].bodyx.f;
	RelY = newco[vertex1].bodyy.f - newco[vertex0].bodyy.f;
	RelZ = newco[vertex1].bodyz.f - newco[vertex0].bodyz.f;

	RelXStep = RelX / 2;
	RelYStep = RelY / 2;
	RelZStep = RelZ / 2;

	Radius = MaxRadius;

	dopoint0 = dopointRoot;
	dopoint0.bodyx.f += RelXStep;
	dopoint0.bodyy.f += RelXStep;
	dopoint0.bodyz.f += RelXStep;

	dopoint2 = dopoint0;
	dopoint2.bodyx.f += Radius;

	_matrix.SetClipFlags(dopoint0);
	_matrix.SetClipFlags(dopoint2);

	_matrix.body2screen(dopoint0);
	_matrix.body2screen(dopoint2);

	RealRadius = dopoint2.screenx.f - dopoint0.screenx.f;
	if (RealRadius)
	{
		POLYGON.createsphere(shape::colour,SMOKED_SOLID);			
		POLYGON.createsphvert(dopoint0,RealRadius);				
		POLYGON.drawsphere();
	}

	POLYGON.SetOpacityON();
//DEAD 	POLYGON.SetPixelWidth(1);

	dopoint1 = dopoint0;

	while (Radius > 2)
	{
		RelXStep /= 2;
		RelYStep /= 2;
		RelZStep /= 2;

		Radius /= 2;

		dopoint0.bodyx.f -= RelXStep;
		dopoint0.bodyy.f -= RelXStep;
		dopoint0.bodyz.f -= RelXStep;

		dopoint2 = dopoint0;
		dopoint2.bodyx.f += Radius;

		dopoint1.bodyx.f += RelXStep;
		dopoint1.bodyy.f += RelXStep;
		dopoint1.bodyz.f += RelXStep;

		dopoint3 = dopoint1;
		dopoint3.bodyx.f += Radius;

		_matrix.SetClipFlags(dopoint0);
		_matrix.SetClipFlags(dopoint1);
		_matrix.SetClipFlags(dopoint2);
		_matrix.SetClipFlags(dopoint3);
		_matrix.body2screen(dopoint0);
		_matrix.body2screen(dopoint1);
		_matrix.body2screen(dopoint2);
		_matrix.body2screen(dopoint3);

		RealRadius = dopoint2.screenx.f - dopoint0.screenx.f;
		if (RealRadius)
		{
			POLYGON.createsphere(shape::colour,SMOKED_SOLID);			
			POLYGON.createsphvert(dopoint0,RealRadius);				
			POLYGON.drawsphere();
		}

		RealRadius = dopoint3.screenx.f - dopoint1.screenx.f;
		if (RealRadius)
		{
			POLYGON.createsphere(shape::colour,SMOKED_SOLID);			
			POLYGON.createsphvert(dopoint1,RealRadius);				
			POLYGON.drawsphere();							
		}
	}

	current_screen->SetTransparency(SMOKED_OFF);				//RJS 18Jun97

//DEAD 	POLYGON.SetCrossProduct(oldcross);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ParticleBoxPlain
//Author		Robert Slater
//Date			Thu 4 Dec 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::ParticleBoxPlain(	UWord	vertex0,
							 		UWord	vertex1,
									UWord	width,
									UWord	height,
									UWord	length,
							 		MyGroundVectorPtr	WCylStartP,
							 		SWord	col,
									SWord	cvar,
									SWord	fadedepth,
									Bool	fuzzy)
{
	DoPointStruc dopoint0,dopoint1,dopointRoot;
 	Bool	oldcross;
	SLong	RelX, RelY, RelZ;
	SLong	RelX2, RelY2, RelZ2;
	SLong	RelX3, RelY3, RelZ3;
	UWord	counter;
	UWord	RSeed;
	SLong	Radius;
	SLong	wXStep, wYStep, wZStep;								
	SLong	wXStart, wYStart, wZStart;							
	Colour	thecol = (Colour) col;
	SLong	MaxDist, Dist;
	SLong	MaxRadius;

	wXStart = WCylStartP->gx;									
	wYStart = WCylStartP->gy;									
	wZStart = WCylStartP->gz;									

//DEAD 	oldcross = POLYGON.SetCrossProduct(FALSE);

	dopointRoot = newco[vertex0];								

	RelX = width;
	RelY = height;
	RelZ = length;

	SLong depth = 1 + ((RelX * RelY * RelZ)/230000);

	MaxRadius = ((RelX/2) + (RelY/2) + (RelZ/2))/3;

	RelX2 = RelX;
	RelY2 = RelY;
	RelZ2 = RelZ;

	RelX /= 2;
	RelY /= 2;
	RelZ /= 2;

	RelX3 = (RelX<0)?-RelX:RelX;
	RelY3 = (RelY<0)?-RelY:RelY;
	RelZ3 = (RelZ<0)?-RelZ:RelZ;

	POLYGON.SetOpacityON();
//DEAD 	POLYGON.SetPixelWidth(1);

	SLong	randx,Spazx,Spazx2,Distx;
	SLong	randy,Spazy,Spazy2,Disty;
	SLong	randz,Spazz,Spazz2,Distz;

	Spazx2 = dopointRoot.bodyx.f + RelX;
	Spazy2 = dopointRoot.bodyy.f + RelY;
	Spazz2 = dopointRoot.bodyz.f + RelZ;

	if (fuzzy)
	{
		for (counter = 0; counter < depth; counter++)
		{
			randx = (Math_Lib.rnd()*RelX2)>>16;
			randy = (Math_Lib.rnd()*RelY2)>>16;
			randz = (Math_Lib.rnd()*RelZ2)>>16;

			Spazx = randx + dopointRoot.bodyx.f;
			Spazy = randy + dopointRoot.bodyy.f;
			Spazz = randz + dopointRoot.bodyz.f;

			Distx = Spazx - Spazx2;
			Disty = Spazy - Spazy2;
			Distz = Spazz - Spazz2;

			Distx = (Distx<0)?-Distx:Distx;
			Disty = (Disty<0)?-Disty:Disty;
			Distz = (Distz<0)?-Distz:Distz;

			Radius = (	((MaxRadius*(RelX3 - Distx))/RelX3)
				  	+ ((MaxRadius*(RelY3 - Disty))/RelY3)
				  	+ ((MaxRadius*(RelZ3 - Distz))/RelZ3)	)/3;

			thecol = (Colour) (col - (((MaxRadius - Radius)*cvar)/MaxRadius));

			dopoint0.bodyx.f = Spazx;
			dopoint0.bodyy.f = Spazy;
			dopoint0.bodyz.f = Spazz;

			dopoint1 = dopoint0;

			_matrix.SetClipFlags(dopoint0);
			_matrix.body2screen(dopoint0);
			dopoint1.bodyx.f += Radius;
			_matrix.SetClipFlags(dopoint1);
			_matrix.body2screen(dopoint1);

			Radius = dopoint1.screenx.f - dopoint0.screenx.f;

			if (Radius)
			{
				POLYGON.createsphere(thecol,fadedepth);			//RJS 04Dec97
				POLYGON.createsphvert(dopoint0,Radius);				//RJS 04Dec97
				POLYGON.drawsphere();								//RJS 04Dec97
			}
		}
	}
	else
	{
		for (counter = 0; counter < depth; counter++)
		{
			RSeed = Noise(wXStart,wYStart,wZStart);
			wXStart += 16;
			wYStart += 16;
			wZStart += 16;

			randx = (RSeed*RelX2)>>8;

			RSeed = Noise(wXStart,wYStart,wZStart);
			wXStart += 16;
			wYStart += 16;
			wZStart += 16;

			randy = (RSeed*RelY2)>>8;

			RSeed = Noise(wXStart,wYStart,wZStart);
			wXStart += 16;
			wYStart += 16;
			wZStart += 16;

			randz = (RSeed*RelZ2)>>8;

			Spazx = randx + dopointRoot.bodyx.f;
			Spazy = randy + dopointRoot.bodyy.f;
			Spazz = randz + dopointRoot.bodyz.f;

			Distx = Spazx - Spazx2;
			Disty = Spazy - Spazy2;
			Distz = Spazz - Spazz2;

			Distx = (Distx<0)?-Distx:Distx;
			Disty = (Disty<0)?-Disty:Disty;
			Distz = (Distz<0)?-Distz:Distz;

			Radius = (	((MaxRadius*(RelX3 - Distx))/RelX3)
				  	+ ((MaxRadius*(RelY3 - Disty))/RelY3)
				  	+ ((MaxRadius*(RelZ3 - Distz))/RelZ3)	)/3;

			thecol = (Colour) (col - (((MaxRadius - Radius)*cvar)/MaxRadius));

			dopoint0.bodyx.f = Spazx;
			dopoint0.bodyy.f = Spazy;
			dopoint0.bodyz.f = Spazz;

			dopoint1 = dopoint0;

			_matrix.SetClipFlags(dopoint0);
			_matrix.body2screen(dopoint0);
			dopoint1.bodyx.f += Radius;
			_matrix.SetClipFlags(dopoint1);
			_matrix.body2screen(dopoint1);

			Radius = dopoint1.screenx.f - dopoint0.screenx.f;

			if (Radius)
			{
				POLYGON.createsphere(thecol,fadedepth);			//RJS 04Dec97
				POLYGON.createsphvert(dopoint0,Radius);				//RJS 04Dec97
				POLYGON.drawsphere();								//RJS 04Dec97
			}
		}
	}

	current_screen->SetTransparency(SMOKED_OFF);				//RJS 18Jun97

//DEAD 	POLYGON.SetCrossProduct(oldcross);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ParticleStream
//Author		Robert Slater
//Date			Tue 4 Nov 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::ParticleStreamPlain(	UWord	vertex0,
							 		UWord	vertex1,
							 		SWord	xoff0, SWord yoff0,
							 		SWord	xoff1, SWord yoff1,
							 		UWord	depth,
							 		SWord	StartRadius,
									SWord	EndRadius,
							 		MyGroundVectorPtr	WCylStartP,
							 		MyGroundVectorPtr	WCylEndP,
							 		SWord	col,
							 		SWord	transdepth)
{
	DoPointStruc dopoint0,dopoint1,dopoint2,dopoint3,dopointRoot,dptmp1,dptmp2;
 	Bool	oldcross;
	Float	RelX, RelY, RelZ;
	Float	RelXStep,RelYStep, RelZStep;
	UWord	counter;
	SLong	xDelta,yDelta;
	SLong	RandxDelta,RandyDelta;
	SLong	xDeltCap,yDeltCap;
	UWord	RSeed;
	SLong	XoffGap;
	SLong	YoffGap;
	SLong	Radius;
	SWord	MaxRadius;
	SWord	RadStep;
	SLong	wXStep, wYStep, wZStep;								
	SLong	wXStart, wYStart, wZStart;							
	Colour	thecol = (Colour) col;
	SLong	MaxDist, Dist;

	depth = 1 + (depth >> 1);

	wXStart = WCylStartP->gx;									
	wYStart = WCylStartP->gy;									
	wZStart = WCylStartP->gz;									

//DEAD 	oldcross = POLYGON.SetCrossProduct(FALSE);

	if (newco[vertex1].bodyz.f > newco[vertex0].bodyz.f)		//RJS 09Jul98
	{															//RJS 09Jul98
		SLong	vswap = vertex0;								//RJS 09Jul98
		vertex0 = vertex1;										//RJS 09Jul98
		vertex1 = vswap;										//RJS 09Jul98
	}															//RJS 09Jul98

	dopointRoot = newco[vertex0];								
   	dopoint2 = newco[vertex1];

	RelX = dopoint2.bodyx.f - dopointRoot.bodyx.f;
	RelY = dopoint2.bodyy.f - dopointRoot.bodyy.f;
	RelZ = dopoint2.bodyz.f - dopointRoot.bodyz.f;

	wXStep = (WCylEndP->gx - wXStart) / depth;					
	wYStep = (WCylEndP->gy - wYStart) / depth;					
	wZStep = (WCylEndP->gz - wZStart) / depth;					

	XoffGap = (xoff1 - xoff0)/depth;
	YoffGap = (yoff1 - yoff0)/depth;

	RelXStep = RelX / depth;
	RelYStep = RelY / depth;
	RelZStep = RelZ / depth;

	RadStep = (EndRadius - StartRadius)/depth;
	MaxRadius = StartRadius;

	xDelta = xoff0;
	yDelta = yoff0;

	POLYGON.SetOpacityON();
//DEAD 	POLYGON.SetPixelWidth(1);

	for (counter = 0; counter < depth; counter++)
	{
		xDeltCap = xDelta << 1;
		yDeltCap = yDelta << 1;

		RSeed = Noise(wXStart,wYStart,wZStart);

		RandxDelta = (((RSeed*xDeltCap)>>8) - xDelta)>>3;			
		RandyDelta = (((RSeed*yDeltCap)>>8) - yDelta)>>3;			

		dopoint0 = dopointRoot;
		dopoint0.bodyx.f += RandxDelta;
		dopoint0.bodyy.f += RandyDelta;

		if (dopoint0.bodyz.f > 100)								
		{
			dopoint1 = dopoint2 = dopoint3 = dopoint0;

			_matrix.SetClipFlags(dopoint0);
			_matrix.body2screen(dopoint0);
			dopoint1.bodyx.f += MaxRadius;
			_matrix.SetClipFlags(dopoint1);
			_matrix.body2screen(dopoint1);

			Radius = dopoint1.screenx.f - dopoint0.screenx.f;

			POLYGON.createsphere(thecol,transdepth);			//RJS 04Dec97
			POLYGON.createsphvert(dopoint0,Radius);				//RJS 04Dec97
			POLYGON.drawsphere();								//RJS 04Dec97
		}

		dopointRoot.bodyx.f += RelXStep;
		dopointRoot.bodyy.f += RelYStep;
  		dopointRoot.bodyz.f += RelZStep;

		xDelta += XoffGap;
		yDelta += YoffGap;

		wXStart += wXStep;										//RJS 12Nov97
		wYStart += wYStep;										//RJS 12Nov97
		wZStart += wZStep;										//RJS 12Nov97

		MaxRadius += RadStep;
	}

	current_screen->SetTransparency(SMOKED_OFF);				//RJS 18Jun97

//DEAD 	POLYGON.SetCrossProduct(oldcross);
}
//PARTICLE.CPP
//PARTICLE.CPP//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//PARTICLE.CPP//Procedure		ParticleStreamEdgedPlain
//PARTICLE.CPP//Author		Robert Slater
//PARTICLE.CPP//Date			Tue 16 Dec 1997
//PARTICLE.CPP//
//PARTICLE.CPP//Description	
//PARTICLE.CPP//
//PARTICLE.CPP//Inputs		
//PARTICLE.CPP//
//PARTICLE.CPP//Returns	
//PARTICLE.CPP//
//PARTICLE.CPP//------------------------------------------------------------------------------
//PARTICLE.CPPvoid	shape::ParticleStreamEdgedPlain(UWord	vertex0,
//PARTICLE.CPP							 			UWord	vertex1,
//PARTICLE.CPP							 			SWord	xoff0, SWord yoff0,
//PARTICLE.CPP							 			SWord	xoff1, SWord yoff1,
//PARTICLE.CPP							 			UWord	depth,
//PARTICLE.CPP							 			SWord	StartRadius,
//PARTICLE.CPP										SWord	EndRadius,
//PARTICLE.CPP							 			MyGroundVectorPtr	WCylStartP,
//PARTICLE.CPP							 			MyGroundVectorPtr	WCylEndP,
//PARTICLE.CPP							 			SWord	col,
//PARTICLE.CPP							 			SWord	transdepth)
//PARTICLE.CPP{
//PARTICLE.CPP	DoPointStruc dopoint0,dopoint1,dopoint2,dopoint3,dopointRoot,dptmp1,dptmp2;
//PARTICLE.CPP 	Bool	oldcross;
//PARTICLE.CPP	Float	RelX, RelY, RelZ;
//PARTICLE.CPP	Float	RelXStep,RelYStep, RelZStep;
//PARTICLE.CPP	UWord	counter;
//PARTICLE.CPP	SLong	xDelta,yDelta;
//PARTICLE.CPP	SLong	RandxDelta,RandyDelta;
//PARTICLE.CPP	SLong	xDeltCap,yDeltCap;
//PARTICLE.CPP	UWord	RSeed;
//PARTICLE.CPP	SLong	XoffGap;
//PARTICLE.CPP	SLong	YoffGap;
//PARTICLE.CPP	SLong	Radius;
//PARTICLE.CPP	SWord	MaxRadius;
//PARTICLE.CPP	SWord	RadStep;
//PARTICLE.CPP	SLong	wXStep, wYStep, wZStep;								
//PARTICLE.CPP	SLong	wXStart, wYStart, wZStart;							
//PARTICLE.CPP	Colour	thecol = (Colour) col;
//PARTICLE.CPP	SLong	MaxDist, Dist;
//PARTICLE.CPP	SWord	realmaxrad = EndRadius;
//PARTICLE.CPP
//PARTICLE.CPP	depth = 1 + (depth >> 1);
//PARTICLE.CPP
//PARTICLE.CPP	wXStart = WCylStartP->gx;									
//PARTICLE.CPP	wYStart = WCylStartP->gy;									
//PARTICLE.CPP	wZStart = WCylStartP->gz;									
//PARTICLE.CPP
//PARTICLE.CPP 	oldcross = POLYGON.SetCrossProduct(FALSE);
//PARTICLE.CPP
//PARTICLE.CPP	if (newco[vertex1].bodyz.f > newco[vertex0].bodyz.f)		//RJS 09Jul98
//PARTICLE.CPP	{															//RJS 09Jul98
//PARTICLE.CPP		SLong	vswap = vertex0;								//RJS 09Jul98
//PARTICLE.CPP		vertex0 = vertex1;										//RJS 09Jul98
//PARTICLE.CPP		vertex1 = vswap;										//RJS 09Jul98
//PARTICLE.CPP	}															//RJS 09Jul98
//PARTICLE.CPP
//PARTICLE.CPP	dopoint1 = dopoint0 = newco[vertex0];								
//PARTICLE.CPP   	dopoint3 = dopoint2 = newco[vertex1];
//PARTICLE.CPP
//PARTICLE.CPP	wXStep = (WCylEndP->gx - wXStart) / depth;					
//PARTICLE.CPP	wYStep = (WCylEndP->gy - wYStart) / depth;					
//PARTICLE.CPP	wZStep = (WCylEndP->gz - wZStart) / depth;					
//PARTICLE.CPP
//PARTICLE.CPP	XoffGap = (xoff1 - xoff0)/depth;
//PARTICLE.CPP	YoffGap = (yoff1 - yoff0)/depth;
//PARTICLE.CPP
//PARTICLE.CPP	EndRadius = (5*EndRadius)>>3;
//PARTICLE.CPP	StartRadius = (5*StartRadius)>>3;
//PARTICLE.CPP
//PARTICLE.CPP	RadStep = (EndRadius - StartRadius)/depth;
//PARTICLE.CPP	MaxRadius = StartRadius;
//PARTICLE.CPP
//PARTICLE.CPP	xDelta = xoff0;
//PARTICLE.CPP	yDelta = yoff0;
//PARTICLE.CPP
//PARTICLE.CPP	POLYGON.SetOpacityON();
//PARTICLE.CPP 	POLYGON.SetPixelWidth(1);
//PARTICLE.CPP
//PARTICLE.CPP	dopoint0.bodyx.f += xoff0;								
//PARTICLE.CPP  	dopoint0.bodyy.f += yoff0;								
//PARTICLE.CPP	_matrix.SetClipFlags(dopoint0);
//PARTICLE.CPP  	_matrix.body2screen(dopoint0);
//PARTICLE.CPP 
//PARTICLE.CPP  	dopoint1.bodyx.f += -xoff0;								
//PARTICLE.CPP 	dopoint1.bodyy.f += -yoff0;								
//PARTICLE.CPP	_matrix.SetClipFlags(dopoint1);
//PARTICLE.CPP 	_matrix.body2screen(dopoint1);
//PARTICLE.CPP 
//PARTICLE.CPP   	dopoint2.bodyx.f += -xoff1;								
//PARTICLE.CPP   	dopoint2.bodyy.f += -yoff1;								
//PARTICLE.CPP	_matrix.SetClipFlags(dopoint2);
//PARTICLE.CPP  	_matrix.body2screen(dopoint2);
//PARTICLE.CPP 
//PARTICLE.CPP   	dopoint3.bodyx.f += xoff1;								
//PARTICLE.CPP   	dopoint3.bodyy.f += yoff1;								
//PARTICLE.CPP	_matrix.SetClipFlags(dopoint3);
//PARTICLE.CPP  	_matrix.body2screen(dopoint3);
//PARTICLE.CPP
//PARTICLE.CPP 	POLYGON.SetPixelWidth(1<<Save_Data.pixelsize);			
//PARTICLE.CPP 	POLYGON.createpoly(thecol);						
//PARTICLE.CPP	POLYGON.createvert(dopoint0);					
//PARTICLE.CPP  	POLYGON.createvert(dopoint1);					
//PARTICLE.CPP  	POLYGON.createvert(dopoint2);					
//PARTICLE.CPP	POLYGON.createvert(dopoint3);					
//PARTICLE.CPP 	POLYGON.drawpoly();			
//PARTICLE.CPP
//PARTICLE.CPP	SLong	XStep0, YStep0, ZStep0;
//PARTICLE.CPP	SLong	XStep1, YStep1, ZStep1;
//PARTICLE.CPP
//PARTICLE.CPP	XStep0 = (dopoint3.bodyx.f - dopoint0.bodyx.f)/depth;
//PARTICLE.CPP	YStep0 = (dopoint3.bodyy.f - dopoint0.bodyy.f)/depth;
//PARTICLE.CPP	ZStep0 = (dopoint3.bodyz.f - dopoint0.bodyz.f)/depth;
//PARTICLE.CPP
//PARTICLE.CPP	XStep1 = (dopoint2.bodyx.f - dopoint1.bodyx.f)/depth;
//PARTICLE.CPP	YStep1 = (dopoint2.bodyy.f - dopoint1.bodyy.f)/depth;
//PARTICLE.CPP	ZStep1 = (dopoint2.bodyz.f - dopoint1.bodyz.f)/depth;
//PARTICLE.CPP
//PARTICLE.CPP	for (counter = 0; counter < depth; counter++)
//PARTICLE.CPP	{
//PARTICLE.CPP		xDeltCap = xDelta << 1;
//PARTICLE.CPP		yDeltCap = yDelta << 1;
//PARTICLE.CPP
//PARTICLE.CPP		RSeed = Noise(wXStart,wYStart,wZStart);
//PARTICLE.CPP
//PARTICLE.CPP		RandxDelta = (((RSeed*xDeltCap)>>8) - xDelta)>>3;			
//PARTICLE.CPP		RandyDelta = (((RSeed*yDeltCap)>>8) - yDelta)>>3;			
//PARTICLE.CPP
//PARTICLE.CPP		dptmp1 = dopoint0;
//PARTICLE.CPP		dptmp1.bodyx.f += RandxDelta;
//PARTICLE.CPP		dptmp1.bodyy.f += RandyDelta;
//PARTICLE.CPP
//PARTICLE.CPP		dptmp2 = dptmp1;
//PARTICLE.CPP
//PARTICLE.CPP		_matrix.SetClipFlags(dptmp1);
//PARTICLE.CPP		_matrix.body2screen(dptmp1);
//PARTICLE.CPP		dptmp2.bodyx.f += MaxRadius;
//PARTICLE.CPP		_matrix.SetClipFlags(dptmp2);
//PARTICLE.CPP		_matrix.body2screen(dptmp2);
//PARTICLE.CPP
//PARTICLE.CPP		Radius = dptmp2.screenx.f - dptmp1.screenx.f;
//PARTICLE.CPP		if (Radius)
//PARTICLE.CPP		{
//PARTICLE.CPP			POLYGON.createsphere(thecol,transdepth);			//RJS 04Dec97
//PARTICLE.CPP			POLYGON.createsphvert(dptmp1,Radius);				//RJS 04Dec97
//PARTICLE.CPP			POLYGON.drawsphere();								//RJS 04Dec97
//PARTICLE.CPP		}
//PARTICLE.CPP
//PARTICLE.CPP		dptmp1 = dopoint1;
//PARTICLE.CPP		dptmp1.bodyx.f -= RandxDelta;
//PARTICLE.CPP		dptmp1.bodyy.f -= RandyDelta;
//PARTICLE.CPP
//PARTICLE.CPP		dptmp2 = dptmp1;
//PARTICLE.CPP
//PARTICLE.CPP		_matrix.SetClipFlags(dptmp1);
//PARTICLE.CPP		_matrix.body2screen(dptmp1);
//PARTICLE.CPP		dptmp2.bodyx.f += MaxRadius;
//PARTICLE.CPP		_matrix.SetClipFlags(dptmp2);
//PARTICLE.CPP		_matrix.body2screen(dptmp2);
//PARTICLE.CPP
//PARTICLE.CPP		Radius = dptmp2.screenx.f - dptmp1.screenx.f;
//PARTICLE.CPP		if (Radius)
//PARTICLE.CPP		{
//PARTICLE.CPP			POLYGON.createsphere(thecol,transdepth);			//RJS 04Dec97
//PARTICLE.CPP			POLYGON.createsphvert(dptmp1,Radius);				//RJS 04Dec97
//PARTICLE.CPP			POLYGON.drawsphere();								//RJS 04Dec97
//PARTICLE.CPP		}
//PARTICLE.CPP
//PARTICLE.CPP		dopoint0.bodyx.f += XStep0;
//PARTICLE.CPP		dopoint0.bodyy.f += YStep0;
//PARTICLE.CPP		dopoint0.bodyz.f += ZStep0;
//PARTICLE.CPP
//PARTICLE.CPP		dopoint1.bodyx.f += XStep1;
//PARTICLE.CPP		dopoint1.bodyy.f += YStep1;
//PARTICLE.CPP		dopoint1.bodyz.f += ZStep1;
//PARTICLE.CPP
//PARTICLE.CPP		xDelta += XoffGap;
//PARTICLE.CPP		yDelta += YoffGap;
//PARTICLE.CPP
//PARTICLE.CPP		wXStart += wXStep;										//RJS 12Nov97
//PARTICLE.CPP		wYStart += wYStep;										//RJS 12Nov97
//PARTICLE.CPP		wZStart += wZStep;										//RJS 12Nov97
//PARTICLE.CPP
//PARTICLE.CPP		MaxRadius += RadStep;
//PARTICLE.CPP	}
//PARTICLE.CPP
//PARTICLE.CPP	dptmp2 = newco[1];
//PARTICLE.CPP	dptmp2.bodyx.f += realmaxrad;
//PARTICLE.CPP	_matrix.SetClipFlags(dptmp2);
//PARTICLE.CPP	_matrix.body2screen(dptmp2);
//PARTICLE.CPP
//PARTICLE.CPP	Radius = dptmp2.screenx.f - newco[1].screenx.f;
//PARTICLE.CPP	POLYGON.createsphere(thecol,transdepth);			//RJS 04Dec97
//PARTICLE.CPP	POLYGON.createsphvert(newco[1],Radius);				//RJS 04Dec97
//PARTICLE.CPP	POLYGON.drawsphere();
//PARTICLE.CPP
//PARTICLE.CPP	current_screen->SetTransparency(SMOKED_OFF);				//RJS 18Jun97
//PARTICLE.CPP
//PARTICLE.CPP 	POLYGON.SetCrossProduct(oldcross);
//PARTICLE.CPP}
//PARTICLE.CPP
//PARTICLE.CPP//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//PARTICLE.CPP//Procedure		ParticleStreamImapd
//PARTICLE.CPP//Author		Robert Slater
//PARTICLE.CPP//Date			Thu 4 Dec 1997
//PARTICLE.CPP//
//PARTICLE.CPP//Description	
//PARTICLE.CPP//
//PARTICLE.CPP//Inputs		
//PARTICLE.CPP//
//PARTICLE.CPP//Returns	
//PARTICLE.CPP//
//PARTICLE.CPP//------------------------------------------------------------------------------
//PARTICLE.CPPvoid	shape::ParticleStreamImapd(	UWord	vertex0,
//PARTICLE.CPP							 		UWord	vertex1,
//PARTICLE.CPP							 		SWord	xoff0, SWord yoff0,
//PARTICLE.CPP							 		SWord	xoff1, SWord yoff1,
//PARTICLE.CPP							 		UWord	depth,
//PARTICLE.CPP									SWord	StartRadius,
//PARTICLE.CPP									SWord	EndRadius,
//PARTICLE.CPP							 		MyGroundVectorPtr	WCylStartP,
//PARTICLE.CPP							 		MyGroundVectorPtr	WCylEndP,
//PARTICLE.CPP							 		SWord	Imap,
//PARTICLE.CPP									SWord	minx, SWord  miny,
//PARTICLE.CPP							 		SWord	iW, SWord	iH,
//PARTICLE.CPP							 		SWord	transdepth)
//PARTICLE.CPP{
//PARTICLE.CPP	DoPointStruc dopoint0,dopoint1,dopoint2,dopoint3,dopointRoot,dptmp1,dptmp2;
//PARTICLE.CPP 	Bool	oldcross;
//PARTICLE.CPP	Float	RelX, RelY, RelZ;
//PARTICLE.CPP	UWord	counter;
//PARTICLE.CPP	SLong	xDelta,yDelta;
//PARTICLE.CPP	SLong	RandxDelta,RandyDelta;
//PARTICLE.CPP	SLong	xDeltCap,yDeltCap;
//PARTICLE.CPP	SWord	RSeed;
//PARTICLE.CPP	SLong	XoffGap;
//PARTICLE.CPP	SLong	YoffGap;
//PARTICLE.CPP	SLong	Radius;
//PARTICLE.CPP	ImageMapNumber imapno = (ImageMapNumber) Imap;				
//PARTICLE.CPP	SWord	maxx, maxy;
//PARTICLE.CPP	SLong	MaxRadius = StartRadius<<16;						//RJS 15Apr98
//PARTICLE.CPP	SLong	wXStep, wYStep, wZStep;								
//PARTICLE.CPP	SLong	wXStart, wYStart, wZStart;							
//PARTICLE.CPP	SLong	MaxDist, Dist;
//PARTICLE.CPP	SLong	RadStep;
//PARTICLE.CPP	ULong	thetime = 0;
//PARTICLE.CPP
//PARTICLE.CPP//DeadCode RJS 30Mar98 	depth = 1 + (depth >> 1);
//PARTICLE.CPP
//PARTICLE.CPP	RadStep = ((EndRadius - StartRadius)<<16)/depth;				//RJS 04Feb98
//PARTICLE.CPP
//PARTICLE.CPP	wXStart = WCylStartP->gx;									
//PARTICLE.CPP	wYStart = WCylStartP->gy;									
//PARTICLE.CPP	wZStart = WCylStartP->gz;									
//PARTICLE.CPP
//PARTICLE.CPP	maxx = minx + iW;													
//PARTICLE.CPP	maxy = miny + iH;													
//PARTICLE.CPP
//PARTICLE.CPP 	oldcross = POLYGON.SetCrossProduct(FALSE);
//PARTICLE.CPP
//PARTICLE.CPP	if (newco[vertex1].bodyz.f > newco[vertex0].bodyz.f)		//RJS 09Jul98
//PARTICLE.CPP	{															//RJS 09Jul98
//PARTICLE.CPP		SLong	vswap = vertex0;								//RJS 09Jul98
//PARTICLE.CPP		vertex0 = vertex1;										//RJS 09Jul98
//PARTICLE.CPP		vertex1 = vswap;										//RJS 09Jul98
//PARTICLE.CPP	}															//RJS 09Jul98
//PARTICLE.CPP
//PARTICLE.CPP	dopointRoot = newco[vertex0];								
//PARTICLE.CPP   	dopoint2 = newco[vertex1];
//PARTICLE.CPP
//PARTICLE.CPP	RelX = dopoint2.bodyx.f - dopointRoot.bodyx.f;
//PARTICLE.CPP	RelY = dopoint2.bodyy.f - dopointRoot.bodyy.f;
//PARTICLE.CPP	RelZ = dopoint2.bodyz.f - dopointRoot.bodyz.f;
//PARTICLE.CPP
//PARTICLE.CPP	wXStep = (WCylEndP->gx - wXStart) / depth;					
//PARTICLE.CPP	wYStep = (WCylEndP->gy - wYStart) / depth;					
//PARTICLE.CPP	wZStep = (WCylEndP->gz - wZStart) / depth;					
//PARTICLE.CPP
//PARTICLE.CPP	if (View_Point)
//PARTICLE.CPP		thetime = View_Point->TimeOfDay();
//PARTICLE.CPP
//PARTICLE.CPP	wXStart += thetime;									
//PARTICLE.CPP	wYStart += thetime;									
//PARTICLE.CPP	wZStart += thetime;
//PARTICLE.CPP
//PARTICLE.CPP	XoffGap = (xoff1 - xoff0)/depth;
//PARTICLE.CPP	YoffGap = (yoff1 - yoff0)/depth;
//PARTICLE.CPP
//PARTICLE.CPP	RelX /= depth;
//PARTICLE.CPP	RelY /= depth;
//PARTICLE.CPP	RelZ /= depth;
//PARTICLE.CPP
//PARTICLE.CPP	xDelta = xoff0;
//PARTICLE.CPP	yDelta = yoff0;
//PARTICLE.CPP
//PARTICLE.CPP	POLYGON.SetOpacityON();
//PARTICLE.CPP 	POLYGON.SetPixelWidth(1);
//PARTICLE.CPP
//PARTICLE.CPP	for (counter = 0; counter < depth; counter++)
//PARTICLE.CPP	{
//PARTICLE.CPP		RSeed = Noise(wXStart,wYStart,wZStart);
//PARTICLE.CPP
//PARTICLE.CPP		RandxDelta = (((RSeed*xDelta)>>7) - xDelta)>>2;			//RJS 27Feb98
//PARTICLE.CPP		RandyDelta = (((RSeed*yDelta)>>7) - yDelta)>>2;			//RJS 27Feb98
//PARTICLE.CPP
//PARTICLE.CPP		dopoint0 = dopointRoot;
//PARTICLE.CPP		dopoint0.bodyx.f += RandxDelta;
//PARTICLE.CPP		dopoint0.bodyy.f += RandyDelta;
//PARTICLE.CPP
//PARTICLE.CPP		if (dopoint0.bodyz.f > 100)								
//PARTICLE.CPP		{
//PARTICLE.CPP			dopoint1 = dopoint2 = dopoint3 = dopoint0;
//PARTICLE.CPP			RSeed -= 128;
//PARTICLE.CPP			RSeed = (RSeed<0)?-RSeed:RSeed;
//PARTICLE.CPP
//PARTICLE.CPP			Radius = ((MaxRadius>>1) + ((MaxRadius * (128-RSeed))>>8))>>16;
//PARTICLE.CPP			dopoint0.bodyx.f -= Radius;						
//PARTICLE.CPP			dopoint0.bodyy.f += Radius;						
//PARTICLE.CPP																
//PARTICLE.CPP			dopoint1.bodyx.f += Radius;						
//PARTICLE.CPP			dopoint1.bodyy.f += Radius;						
//PARTICLE.CPP																
//PARTICLE.CPP			dopoint2.bodyx.f += Radius;						
//PARTICLE.CPP			dopoint2.bodyy.f -= Radius;						
//PARTICLE.CPP																
//PARTICLE.CPP			dopoint3.bodyx.f -= Radius;						
//PARTICLE.CPP			dopoint3.bodyy.f -= Radius;
//PARTICLE.CPP			
//PARTICLE.CPP			_matrix.SetClipFlags(dopoint0);
//PARTICLE.CPP			_matrix.SetClipFlags(dopoint1);
//PARTICLE.CPP			_matrix.SetClipFlags(dopoint2);
//PARTICLE.CPP			_matrix.SetClipFlags(dopoint3);
//PARTICLE.CPP												
//PARTICLE.CPP			_matrix.body2screen(dopoint0);						
//PARTICLE.CPP			_matrix.body2screen(dopoint1);						
//PARTICLE.CPP			_matrix.body2screen(dopoint2);						
//PARTICLE.CPP			_matrix.body2screen(dopoint3);
//PARTICLE.CPP
//PARTICLE.CPP			POLYGON.createpoly(imapno);
//PARTICLE.CPP			POLYGON.createvert(dopoint0,minx,miny);
//PARTICLE.CPP			POLYGON.createvert(dopoint1,maxx,miny);
//PARTICLE.CPP			POLYGON.createvert(dopoint2,maxx,maxy);
//PARTICLE.CPP			POLYGON.createvert(dopoint3,minx,maxy);
//PARTICLE.CPP			POLYGON.drawpoly();
//PARTICLE.CPP		}
//PARTICLE.CPP
//PARTICLE.CPP		dopointRoot.bodyx.f += RelX;
//PARTICLE.CPP		dopointRoot.bodyy.f += RelY;
//PARTICLE.CPP  		dopointRoot.bodyz.f += RelZ;
//PARTICLE.CPP
//PARTICLE.CPP		xDelta += XoffGap;
//PARTICLE.CPP		yDelta += YoffGap;
//PARTICLE.CPP
//PARTICLE.CPP		wXStart += wXStep;										//RJS 12Nov97
//PARTICLE.CPP		wYStart += wYStep;										//RJS 12Nov97
//PARTICLE.CPP		wZStart += wZStep;										//RJS 12Nov97
//PARTICLE.CPP
//PARTICLE.CPP		MaxRadius += RadStep;
//PARTICLE.CPP	}
//PARTICLE.CPP
//PARTICLE.CPP	current_screen->SetTransparency(SMOKED_OFF);				//RJS 18Jun97
//PARTICLE.CPP                                                                                                              
//PARTICLE.CPP 	POLYGON.SetCrossProduct(oldcross);
//PARTICLE.CPP}
//PARTICLE.CPP
//PARTICLE.CPP//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//PARTICLE.CPP//Procedure		ParticleStreamStaggeredImapd
//PARTICLE.CPP//Author		Robert Slater
//PARTICLE.CPP//Date			Fri 27 Feb 1998
//PARTICLE.CPP//
//PARTICLE.CPP//Description	
//PARTICLE.CPP//
//PARTICLE.CPP//Inputs		
//PARTICLE.CPP//
//PARTICLE.CPP//Returns	
//PARTICLE.CPP//
//PARTICLE.CPP//------------------------------------------------------------------------------
//PARTICLE.CPPvoid	shape::ParticleStreamStaggeredImapd(UWord	vertex0,
//PARTICLE.CPP							 				UWord	vertex1,
//PARTICLE.CPP							 				SWord	xoff0, SWord yoff0,
//PARTICLE.CPP							 				SWord	xoff1, SWord yoff1,
//PARTICLE.CPP							 				SLong	distance3d,
//PARTICLE.CPP											SLong	fadedist,
//PARTICLE.CPP											SWord	StartRadius,
//PARTICLE.CPP											SWord	EndRadius,
//PARTICLE.CPP							 				MyGroundVectorPtr	WCylStartP,
//PARTICLE.CPP							 				MyGroundVectorPtr	WCylEndP,
//PARTICLE.CPP							 				SWord	Imap,
//PARTICLE.CPP											SWord	minx, SWord  miny,
//PARTICLE.CPP							 				SWord	iW, SWord	iH,
//PARTICLE.CPP							 				SWord	transdepth,
//PARTICLE.CPP											SWord	MaxDepth)
//PARTICLE.CPP{
//PARTICLE.CPP	DoPointStruc dopoint0,dopoint1,dopoint2,dopoint3,dopointRoot,dptmp1,dptmp2;
//PARTICLE.CPP 	Bool	oldcross;
//PARTICLE.CPP	Float	RelX, RelY, RelZ;
//PARTICLE.CPP	UWord	counter;
//PARTICLE.CPP	SLong	xDelta,yDelta,zDelta;
//PARTICLE.CPP	SLong	RandxDelta,RandyDelta,RandzDelta;
//PARTICLE.CPP	SWord	RSeed;
//PARTICLE.CPP	SLong	XoffGap;
//PARTICLE.CPP	SLong	YoffGap;
//PARTICLE.CPP	SLong	Radius;
//PARTICLE.CPP	ImageMapNumber imapno = (ImageMapNumber) Imap;				
//PARTICLE.CPP	SWord	maxx, maxy;
//PARTICLE.CPP	SWord	MaxRadius = StartRadius;						//RJS 04Feb98
//PARTICLE.CPP	SLong	wXStep, wYStep, wZStep;								
//PARTICLE.CPP	SLong	wXStart, wYStart, wZStart;							
//PARTICLE.CPP	SLong	MaxDist, Dist;
//PARTICLE.CPP	SWord	RadStep;
//PARTICLE.CPP	SWord	avrad = (StartRadius + EndRadius)>>1;
//PARTICLE.CPP	SLong	depth;
//PARTICLE.CPP
//PARTICLE.CPP	if (newco[vertex1].bodyz.f > newco[vertex0].bodyz.f)		//RJS 09Jul98
//PARTICLE.CPP	{															//RJS 09Jul98
//PARTICLE.CPP		SLong	vswap = vertex0;								//RJS 09Jul98
//PARTICLE.CPP		vertex0 = vertex1;										//RJS 09Jul98
//PARTICLE.CPP		vertex1 = vswap;										//RJS 09Jul98
//PARTICLE.CPP	}															//RJS 09Jul98
//PARTICLE.CPP
//PARTICLE.CPP	dopointRoot = newco[vertex0];								
//PARTICLE.CPP   	dopoint2 = newco[vertex1];
//PARTICLE.CPP
//PARTICLE.CPP	RelX = dopoint2.bodyx.f - dopointRoot.bodyx.f;
//PARTICLE.CPP	RelY = dopoint2.bodyy.f - dopointRoot.bodyy.f;
//PARTICLE.CPP	RelZ = dopoint2.bodyz.f - dopointRoot.bodyz.f;
//PARTICLE.CPP
//PARTICLE.CPP	depth = (Math_Lib.distance3d(RelX,RelY,RelZ) / avrad) * distance3d;
//PARTICLE.CPP	depth /= fadedist;
//PARTICLE.CPP	depth = (depth*3)>>2;
//PARTICLE.CPP	depth += 1;
//PARTICLE.CPP	if (depth > MaxDepth)
//PARTICLE.CPP		depth = MaxDepth;
//PARTICLE.CPP
//PARTICLE.CPP	RadStep = (EndRadius - StartRadius)/depth;
//PARTICLE.CPP
//PARTICLE.CPP	wXStart = WCylStartP->gx;									
//PARTICLE.CPP	wYStart = WCylStartP->gy;									
//PARTICLE.CPP	wZStart = WCylStartP->gz;									
//PARTICLE.CPP
//PARTICLE.CPP	maxx = minx + iW;													
//PARTICLE.CPP	maxy = miny + iH;													
//PARTICLE.CPP
//PARTICLE.CPP 	oldcross = POLYGON.SetCrossProduct(FALSE);
//PARTICLE.CPP
//PARTICLE.CPP	wXStep = (WCylEndP->gx - wXStart) / depth;					
//PARTICLE.CPP	wYStep = (WCylEndP->gy - wYStart) / depth;					
//PARTICLE.CPP	wZStep = (WCylEndP->gz - wZStart) / depth;					
//PARTICLE.CPP
//PARTICLE.CPP	XoffGap = (xoff1 - xoff0)/depth;
//PARTICLE.CPP	YoffGap = (yoff1 - yoff0)/depth;
//PARTICLE.CPP
//PARTICLE.CPP	RelX /= depth;
//PARTICLE.CPP	RelY /= depth;
//PARTICLE.CPP	RelZ /= depth;
//PARTICLE.CPP
//PARTICLE.CPP	xDelta = xoff0;
//PARTICLE.CPP	yDelta = yoff0;
//PARTICLE.CPP	zDelta = RelZ;
//PARTICLE.CPP	zDelta >>= 1;
//PARTICLE.CPP
//PARTICLE.CPP	POLYGON.SetOpacityON();
//PARTICLE.CPP 	POLYGON.SetPixelWidth(1);
//PARTICLE.CPP
//PARTICLE.CPP	for (counter = 0; counter < depth; counter++)
//PARTICLE.CPP	{
//PARTICLE.CPP		RSeed = Noise(wXStart,wYStart,wZStart);
//PARTICLE.CPP
//PARTICLE.CPP		RandxDelta = (((RSeed*xDelta)>>7) - xDelta)>>2;			
//PARTICLE.CPP		RandyDelta = (((RSeed*yDelta)>>7) - yDelta)>>2;			
//PARTICLE.CPP		RandzDelta = (((RSeed*zDelta)>>7) - zDelta)>>2;			
//PARTICLE.CPP
//PARTICLE.CPP		dopoint0 = dopointRoot;
//PARTICLE.CPP		dopoint0.bodyx.f += RandxDelta;
//PARTICLE.CPP		dopoint0.bodyy.f += RandyDelta;
//PARTICLE.CPP		dopoint0.bodyz.f += RandzDelta;
//PARTICLE.CPP
//PARTICLE.CPP		if (dopoint0.bodyz.f > 100)								
//PARTICLE.CPP		{
//PARTICLE.CPP			dopoint1 = dopoint2 = dopoint3 = dopoint0;
//PARTICLE.CPP			RSeed -= 128;
//PARTICLE.CPP			RSeed = (RSeed<0)?-RSeed:RSeed;
//PARTICLE.CPP
//PARTICLE.CPP			Radius = (MaxRadius>>1) + ((MaxRadius * (128-RSeed))>>8);
//PARTICLE.CPP
//PARTICLE.CPP			dopoint0.bodyx.f -= Radius;						
//PARTICLE.CPP			dopoint0.bodyy.f += Radius;						
//PARTICLE.CPP																
//PARTICLE.CPP			dopoint1.bodyx.f += Radius;						
//PARTICLE.CPP			dopoint1.bodyy.f += Radius;						
//PARTICLE.CPP																
//PARTICLE.CPP			dopoint2.bodyx.f += Radius;						
//PARTICLE.CPP			dopoint2.bodyy.f -= Radius;						
//PARTICLE.CPP																
//PARTICLE.CPP			dopoint3.bodyx.f -= Radius;						
//PARTICLE.CPP			dopoint3.bodyy.f -= Radius;						
//PARTICLE.CPP																
//PARTICLE.CPP			_matrix.SetClipFlags(dopoint0);
//PARTICLE.CPP			_matrix.SetClipFlags(dopoint1);
//PARTICLE.CPP			_matrix.SetClipFlags(dopoint2);
//PARTICLE.CPP			_matrix.SetClipFlags(dopoint3);
//PARTICLE.CPP
//PARTICLE.CPP			_matrix.body2screen(dopoint0);						
//PARTICLE.CPP			_matrix.body2screen(dopoint1);						
//PARTICLE.CPP			_matrix.body2screen(dopoint2);						
//PARTICLE.CPP			_matrix.body2screen(dopoint3);
//PARTICLE.CPP
//PARTICLE.CPP			POLYGON.createpoly(imapno);
//PARTICLE.CPP			POLYGON.createvert(dopoint0,minx,miny);
//PARTICLE.CPP			POLYGON.createvert(dopoint1,maxx,miny);
//PARTICLE.CPP			POLYGON.createvert(dopoint2,maxx,maxy);
//PARTICLE.CPP			POLYGON.createvert(dopoint3,minx,maxy);
//PARTICLE.CPP			POLYGON.drawpoly();
//PARTICLE.CPP		}
//PARTICLE.CPP
//PARTICLE.CPP		dopointRoot.bodyx.f += RelX;
//PARTICLE.CPP		dopointRoot.bodyy.f += RelY;
//PARTICLE.CPP  		dopointRoot.bodyz.f += RelZ;
//PARTICLE.CPP
//PARTICLE.CPP		xDelta += XoffGap;
//PARTICLE.CPP		yDelta += YoffGap;
//PARTICLE.CPP
//PARTICLE.CPP		wXStart += wXStep;										//RJS 12Nov97
//PARTICLE.CPP		wYStart += wYStep;										//RJS 12Nov97
//PARTICLE.CPP		wZStart += wZStep;										//RJS 12Nov97
//PARTICLE.CPP
//PARTICLE.CPP		MaxRadius += RadStep;
//PARTICLE.CPP	}
//PARTICLE.CPP
//PARTICLE.CPP	current_screen->SetTransparency(SMOKED_OFF);				//RJS 18Jun97
//PARTICLE.CPP
//PARTICLE.CPP 	POLYGON.SetCrossProduct(oldcross);
//PARTICLE.CPP}
//PARTICLE.CPP
//PARTICLE.CPP//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//PARTICLE.CPP//Procedure		ParticleCylinder
//PARTICLE.CPP//Author		Robert Slater
//PARTICLE.CPP//Date			Tue 4 Nov 1997
//PARTICLE.CPP//
//PARTICLE.CPP//Description	
//PARTICLE.CPP//
//PARTICLE.CPP//Inputs		
//PARTICLE.CPP//
//PARTICLE.CPP//Returns	
//PARTICLE.CPP//
//PARTICLE.CPP//------------------------------------------------------------------------------
//PARTICLE.CPPvoid	shape::ParticleCylinderPlain(UWord	vertex0,
//PARTICLE.CPP									UWord	vertex1,
//PARTICLE.CPP									SWord	xoff0, SWord yoff0,
//PARTICLE.CPP									SWord	xoff1, SWord yoff1,
//PARTICLE.CPP									UWord	depth,
//PARTICLE.CPP									SWord	MaxRadius,
//PARTICLE.CPP									MyGroundVectorPtr	WCylStartP,
//PARTICLE.CPP									MyGroundVectorPtr	WCylEndP,
//PARTICLE.CPP									SWord	col,
//PARTICLE.CPP									SWord	transdepth)
//PARTICLE.CPP{
//PARTICLE.CPP	DoPointStruc dopoint0,dopoint1,dopoint2,dopoint3,dopointRoot,dptmp1,dptmp2;
//PARTICLE.CPP 	Bool	oldcross;
//PARTICLE.CPP	Float	RelX, RelY, RelZ;
//PARTICLE.CPP	UWord	counter;
//PARTICLE.CPP	SLong	xDelta,yDelta;
//PARTICLE.CPP	SLong	RandxDelta,RandyDelta;
//PARTICLE.CPP	SLong	xDeltCap,yDeltCap;
//PARTICLE.CPP	UWord	RSeed;
//PARTICLE.CPP	SLong	XoffGap;
//PARTICLE.CPP	SLong	YoffGap;
//PARTICLE.CPP	SLong	Radius, Radius3d;
//PARTICLE.CPP	SWord	HalfRadius = MaxRadius>>1;							//RJS 04Dec97
//PARTICLE.CPP	SLong	wXStep, wYStep, wZStep;								//RJS 04Dec97
//PARTICLE.CPP	SLong	wXStart, wYStart, wZStart;							//RJS 12Nov97
//PARTICLE.CPP	Colour	thecol = (Colour) col;
//PARTICLE.CPP	SLong	MaxDist, Dist;										//RJS 02Dec97
//PARTICLE.CPP
//PARTICLE.CPP	wXStart = WCylStartP->gx;									//RJS 12Nov97
//PARTICLE.CPP	wYStart = WCylStartP->gy;									//RJS 12Nov97
//PARTICLE.CPP	wZStart = WCylStartP->gz;									//RJS 12Nov97
//PARTICLE.CPP
//PARTICLE.CPP 	oldcross = POLYGON.SetCrossProduct(FALSE);
//PARTICLE.CPP
//PARTICLE.CPP	if (newco[vertex1].bodyz.f > newco[vertex0].bodyz.f)		//RJS 09Jul98
//PARTICLE.CPP	{															//RJS 09Jul98
//PARTICLE.CPP		SLong	vswap = vertex0;								//RJS 09Jul98
//PARTICLE.CPP		vertex0 = vertex1;										//RJS 09Jul98
//PARTICLE.CPP		vertex1 = vswap;										//RJS 09Jul98
//PARTICLE.CPP	}															//RJS 09Jul98
//PARTICLE.CPP
//PARTICLE.CPP	dopointRoot = newco[vertex0];										
//PARTICLE.CPP   	dopoint2 = newco[vertex1];
//PARTICLE.CPP
//PARTICLE.CPP	RelX = dopoint2.bodyx.f - dopointRoot.bodyx.f;
//PARTICLE.CPP	RelY = dopoint2.bodyy.f - dopointRoot.bodyy.f;
//PARTICLE.CPP	RelZ = dopoint2.bodyz.f - dopointRoot.bodyz.f;
//PARTICLE.CPP
//PARTICLE.CPP	wXStep = (WCylEndP->gx - wXStart) / depth;					//RJS 12Nov97
//PARTICLE.CPP	wYStep = (WCylEndP->gy - wYStart) / depth;					//RJS 12Nov97
//PARTICLE.CPP	wZStep = (WCylEndP->gz - wZStart) / depth;					//RJS 12Nov97
//PARTICLE.CPP
//PARTICLE.CPP	XoffGap = (xoff1 - xoff0)/depth;
//PARTICLE.CPP	YoffGap = (yoff1 - yoff0)/depth;
//PARTICLE.CPP
//PARTICLE.CPP	RelX /= depth;
//PARTICLE.CPP	RelY /= depth;
//PARTICLE.CPP	RelZ /= depth;
//PARTICLE.CPP
//PARTICLE.CPP	xDelta = xoff0;
//PARTICLE.CPP	yDelta = yoff0;
//PARTICLE.CPP
//PARTICLE.CPP	POLYGON.SetOpacityON();
//PARTICLE.CPP 	POLYGON.SetPixelWidth(1);
//PARTICLE.CPP
//PARTICLE.CPP	for (counter = 0; counter < depth; counter++)
//PARTICLE.CPP	{
//PARTICLE.CPP		xDeltCap = xDelta << 1;
//PARTICLE.CPP		yDeltCap = yDelta << 1;
//PARTICLE.CPP
//PARTICLE.CPP		RSeed = Noise(wXStart,wYStart,wZStart);
//PARTICLE.CPP
//PARTICLE.CPP		RandxDelta = ((RSeed*xDeltCap)>>8) - xDelta;			//RJS 12Nov97
//PARTICLE.CPP		RandyDelta = ((RSeed*yDeltCap)>>8) - yDelta;			//RJS 12Nov97
//PARTICLE.CPP
//PARTICLE.CPP		dopoint0 = dopointRoot;
//PARTICLE.CPP		dopoint0.bodyx.f += RandxDelta;
//PARTICLE.CPP		dopoint0.bodyy.f += RandyDelta;
//PARTICLE.CPP
//PARTICLE.CPP		if (dopoint0.bodyz.f > 100)								//RJS 13Nov97
//PARTICLE.CPP		{
//PARTICLE.CPP			dopoint1 = dopoint2 = dopoint3 = dopoint0;
//PARTICLE.CPP
//PARTICLE.CPP			xDeltCap >>= 1;
//PARTICLE.CPP			yDeltCap >>= 1;
//PARTICLE.CPP			xDeltCap = (xDeltCap<0)?-xDeltCap:xDeltCap;
//PARTICLE.CPP			yDeltCap = (yDeltCap<0)?-yDeltCap:yDeltCap;
//PARTICLE.CPP
//PARTICLE.CPP			if (xDeltCap || yDeltCap)
//PARTICLE.CPP			{
//PARTICLE.CPP				if (xDeltCap > yDeltCap)
//PARTICLE.CPP				{
//PARTICLE.CPP					MaxDist = xDeltCap;
//PARTICLE.CPP					Dist = (RandxDelta<0)?-RandxDelta:RandxDelta;
//PARTICLE.CPP				}
//PARTICLE.CPP				else
//PARTICLE.CPP				{
//PARTICLE.CPP					MaxDist = yDeltCap;
//PARTICLE.CPP					Dist = (RandyDelta<0)?-RandyDelta:RandyDelta;
//PARTICLE.CPP				}
//PARTICLE.CPP
//PARTICLE.CPP				Dist = MaxDist - Dist;
//PARTICLE.CPP
//PARTICLE.CPP				Radius = 2 + ((Dist*MaxRadius)/MaxDist);
//PARTICLE.CPP
//PARTICLE.CPP				_matrix.SetClipFlags(dopoint0);
//PARTICLE.CPP				_matrix.body2screen(dopoint0);
//PARTICLE.CPP
//PARTICLE.CPP				dopoint1.bodyx.f += Radius;
//PARTICLE.CPP
//PARTICLE.CPP				_matrix.SetClipFlags(dopoint1);
//PARTICLE.CPP				_matrix.body2screen(dopoint1);
//PARTICLE.CPP
//PARTICLE.CPP				Radius3d = dopoint1.screenx.f - dopoint0.screenx.f;
//PARTICLE.CPP				if ((Radius < HalfRadius) && (Radius3d == 0))	//RJS 04Dec97
//PARTICLE.CPP					Radius3d = -1;
//PARTICLE.CPP
//PARTICLE.CPP				POLYGON.createsphere(thecol,transdepth);		//RJS 04Dec97
//PARTICLE.CPP				POLYGON.createsphvert(dopoint0,Radius3d);		//RJS 04Dec97
//PARTICLE.CPP				POLYGON.drawsphere();							//RJS 04Dec97
//PARTICLE.CPP			}
//PARTICLE.CPP		}
//PARTICLE.CPP
//PARTICLE.CPP		dopointRoot.bodyx.f += RelX;
//PARTICLE.CPP		dopointRoot.bodyy.f += RelY;
//PARTICLE.CPP  		dopointRoot.bodyz.f += RelZ;
//PARTICLE.CPP
//PARTICLE.CPP		xDelta += XoffGap;
//PARTICLE.CPP		yDelta += YoffGap;
//PARTICLE.CPP
//PARTICLE.CPP		wXStart += wXStep;										//RJS 12Nov97
//PARTICLE.CPP		wYStart += wYStep;										//RJS 12Nov97
//PARTICLE.CPP		wZStart += wZStep;										//RJS 12Nov97
//PARTICLE.CPP	}
//PARTICLE.CPP
//PARTICLE.CPP	current_screen->SetTransparency(SMOKED_OFF);				//RJS 18Jun97
//PARTICLE.CPP
//PARTICLE.CPP	POLYGON.SetPixelWidth(1);
//PARTICLE.CPP 	POLYGON.SetCrossProduct(oldcross);
//PARTICLE.CPP}
//PARTICLE.CPP
//PARTICLE.CPP//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//PARTICLE.CPP//Procedure		ParticleCylinderImapd
//PARTICLE.CPP//Author		Robert Slater
//PARTICLE.CPP//Date			Thu 4 Dec 1997
//PARTICLE.CPP//
//PARTICLE.CPP//Description	
//PARTICLE.CPP//
//PARTICLE.CPP//Inputs		
//PARTICLE.CPP//
//PARTICLE.CPP//Returns	
//PARTICLE.CPP//
//PARTICLE.CPP//------------------------------------------------------------------------------
//PARTICLE.CPPvoid	shape::ParticleCylinderImapd(UWord	vertex0,
//PARTICLE.CPP									UWord	vertex1,
//PARTICLE.CPP									SWord	xoff0, SWord yoff0,
//PARTICLE.CPP									SWord	xoff1, SWord yoff1,
//PARTICLE.CPP									UWord	depth,
//PARTICLE.CPP									SWord	MaxRadius,
//PARTICLE.CPP									MyGroundVectorPtr	WCylStartP,
//PARTICLE.CPP									MyGroundVectorPtr	WCylEndP,
//PARTICLE.CPP									SWord	Imap,
//PARTICLE.CPP									SWord	minx, SWord  miny,
//PARTICLE.CPP									SWord	iW, SWord iH,
//PARTICLE.CPP									SWord	transdepth)
//PARTICLE.CPP{
//PARTICLE.CPP	DoPointStruc dopoint0,dopoint1,dopoint2,dopoint3,dopointRoot,dptmp1,dptmp2;
//PARTICLE.CPP 	Bool	oldcross;
//PARTICLE.CPP	Float	RelX, RelY, RelZ;
//PARTICLE.CPP	UWord	counter;
//PARTICLE.CPP	SLong	xDelta,yDelta;
//PARTICLE.CPP	SLong	RandxDelta,RandyDelta;
//PARTICLE.CPP	SLong	xDeltCap,yDeltCap;
//PARTICLE.CPP	UWord	RSeed;
//PARTICLE.CPP	SLong	XoffGap;
//PARTICLE.CPP	SLong	YoffGap;
//PARTICLE.CPP	SLong	Radius, Radius3d;
//PARTICLE.CPP	ImageMapNumber imapno = (ImageMapNumber) Imap;				//RJS 12Nov97
//PARTICLE.CPP	SWord	maxx, maxy;
//PARTICLE.CPP	SWord	HalfRadius = MaxRadius>>1;							//RJS 04Dec97
//PARTICLE.CPP	SLong	wXStep, wYStep, wZStep;								//RJS 04Dec97
//PARTICLE.CPP	SLong	wXStart, wYStart, wZStart;							//RJS 12Nov97
//PARTICLE.CPP	SLong	MaxDist, Dist;										//RJS 02Dec97
//PARTICLE.CPP
//PARTICLE.CPP	wXStart = WCylStartP->gx;									//RJS 12Nov97
//PARTICLE.CPP	wYStart = WCylStartP->gy;									//RJS 12Nov97
//PARTICLE.CPP	wZStart = WCylStartP->gz;									//RJS 12Nov97
//PARTICLE.CPP
//PARTICLE.CPP	maxx = minx + iW;													//RJS 12Nov97
//PARTICLE.CPP	maxy = miny + iH;													//RJS 12Nov97
//PARTICLE.CPP
//PARTICLE.CPP 	oldcross = POLYGON.SetCrossProduct(FALSE);
//PARTICLE.CPP
//PARTICLE.CPP	if (newco[vertex1].bodyz.f > newco[vertex0].bodyz.f)		//RJS 09Jul98
//PARTICLE.CPP	{															//RJS 09Jul98
//PARTICLE.CPP		SLong	vswap = vertex0;								//RJS 09Jul98
//PARTICLE.CPP		vertex0 = vertex1;										//RJS 09Jul98
//PARTICLE.CPP		vertex1 = vswap;										//RJS 09Jul98
//PARTICLE.CPP	}															//RJS 09Jul98
//PARTICLE.CPP
//PARTICLE.CPP	dopointRoot = newco[vertex0];										
//PARTICLE.CPP   	dopoint2 = newco[vertex1];
//PARTICLE.CPP
//PARTICLE.CPP	RelX = dopoint2.bodyx.f - dopointRoot.bodyx.f;
//PARTICLE.CPP	RelY = dopoint2.bodyy.f - dopointRoot.bodyy.f;
//PARTICLE.CPP	RelZ = dopoint2.bodyz.f - dopointRoot.bodyz.f;
//PARTICLE.CPP
//PARTICLE.CPP	wXStep = (WCylEndP->gx - wXStart) / depth;					//RJS 12Nov97
//PARTICLE.CPP	wYStep = (WCylEndP->gy - wYStart) / depth;					//RJS 12Nov97
//PARTICLE.CPP	wZStep = (WCylEndP->gz - wZStart) / depth;					//RJS 12Nov97
//PARTICLE.CPP
//PARTICLE.CPP	XoffGap = (xoff1 - xoff0)/depth;
//PARTICLE.CPP	YoffGap = (yoff1 - yoff0)/depth;
//PARTICLE.CPP
//PARTICLE.CPP	RelX /= depth;
//PARTICLE.CPP	RelY /= depth;
//PARTICLE.CPP	RelZ /= depth;
//PARTICLE.CPP
//PARTICLE.CPP	xDelta = xoff0;
//PARTICLE.CPP	yDelta = yoff0;
//PARTICLE.CPP
//PARTICLE.CPP	POLYGON.SetOpacityON();
//PARTICLE.CPP 	POLYGON.SetPixelWidth(1);
//PARTICLE.CPP
//PARTICLE.CPP	for (counter = 0; counter < depth; counter++)
//PARTICLE.CPP	{
//PARTICLE.CPP		xDeltCap = xDelta << 1;
//PARTICLE.CPP		yDeltCap = yDelta << 1;
//PARTICLE.CPP
//PARTICLE.CPP		RSeed = Noise(wXStart,wYStart,wZStart);
//PARTICLE.CPP
//PARTICLE.CPP		RandxDelta = ((RSeed*xDeltCap)>>8) - xDelta;			//RJS 12Nov97
//PARTICLE.CPP		RandyDelta = ((RSeed*yDeltCap)>>8) - yDelta;			//RJS 12Nov97
//PARTICLE.CPP
//PARTICLE.CPP		dopoint0 = dopointRoot;
//PARTICLE.CPP		dopoint0.bodyx.f += RandxDelta;
//PARTICLE.CPP		dopoint0.bodyy.f += RandyDelta;
//PARTICLE.CPP
//PARTICLE.CPP		if (dopoint0.bodyz.f > 100)								//RJS 13Nov97
//PARTICLE.CPP		{
//PARTICLE.CPP			dopoint1 = dopoint2 = dopoint3 = dopoint0;
//PARTICLE.CPP
//PARTICLE.CPP			xDeltCap >>= 1;
//PARTICLE.CPP			yDeltCap >>= 1;
//PARTICLE.CPP			xDeltCap = (xDeltCap<0)?-xDeltCap:xDeltCap;
//PARTICLE.CPP			yDeltCap = (yDeltCap<0)?-yDeltCap:yDeltCap;
//PARTICLE.CPP
//PARTICLE.CPP			if (xDeltCap || yDeltCap)
//PARTICLE.CPP			{
//PARTICLE.CPP				if (xDeltCap > yDeltCap)
//PARTICLE.CPP				{
//PARTICLE.CPP					MaxDist = xDeltCap;
//PARTICLE.CPP					Dist = (RandxDelta<0)?-RandxDelta:RandxDelta;
//PARTICLE.CPP				}
//PARTICLE.CPP				else
//PARTICLE.CPP				{
//PARTICLE.CPP					MaxDist = yDeltCap;
//PARTICLE.CPP					Dist = (RandyDelta<0)?-RandyDelta:RandyDelta;
//PARTICLE.CPP				}
//PARTICLE.CPP
//PARTICLE.CPP				Dist = MaxDist - Dist;
//PARTICLE.CPP
//PARTICLE.CPP				Radius = 2 + ((Dist*MaxRadius)/MaxDist);
//PARTICLE.CPP
//PARTICLE.CPP				dopoint0.bodyx.f -= Radius;						//RJS 26Jun97
//PARTICLE.CPP				dopoint0.bodyy.f += Radius;						//RJS 26Jun97
//PARTICLE.CPP																		//RJS 26Jun97
//PARTICLE.CPP				dopoint1.bodyx.f += Radius;						//RJS 26Jun97
//PARTICLE.CPP				dopoint1.bodyy.f += Radius;						//RJS 26Jun97
//PARTICLE.CPP																		//RJS 26Jun97
//PARTICLE.CPP				dopoint2.bodyx.f += Radius;						//RJS 26Jun97
//PARTICLE.CPP				dopoint2.bodyy.f -= Radius;						//RJS 26Jun97
//PARTICLE.CPP																		//RJS 26Jun97
//PARTICLE.CPP				dopoint3.bodyx.f -= Radius;						//RJS 26Jun97
//PARTICLE.CPP				dopoint3.bodyy.f -= Radius;						//RJS 26Jun97
//PARTICLE.CPP																		//RJS 26Jun97
//PARTICLE.CPP				_matrix.SetClipFlags(dopoint0);
//PARTICLE.CPP				_matrix.SetClipFlags(dopoint1);
//PARTICLE.CPP				_matrix.SetClipFlags(dopoint2);
//PARTICLE.CPP				_matrix.SetClipFlags(dopoint3);
//PARTICLE.CPP
//PARTICLE.CPP				_matrix.body2screen(dopoint0);							//RJS 26Jun97
//PARTICLE.CPP				_matrix.body2screen(dopoint1);							//RJS 26Jun97
//PARTICLE.CPP				_matrix.body2screen(dopoint2);							//RJS 26Jun97
//PARTICLE.CPP				_matrix.body2screen(dopoint3);	
//PARTICLE.CPP
//PARTICLE.CPP				POLYGON.createpoly(imapno);
//PARTICLE.CPP				POLYGON.createvert(dopoint0,minx,miny);
//PARTICLE.CPP				POLYGON.createvert(dopoint1,maxx,miny);
//PARTICLE.CPP				POLYGON.createvert(dopoint2,maxx,maxy);
//PARTICLE.CPP				POLYGON.createvert(dopoint3,minx,maxy);
//PARTICLE.CPP				POLYGON.drawpoly();
//PARTICLE.CPP			}
//PARTICLE.CPP		}
//PARTICLE.CPP
//PARTICLE.CPP		dopointRoot.bodyx.f += RelX;
//PARTICLE.CPP		dopointRoot.bodyy.f += RelY;
//PARTICLE.CPP  		dopointRoot.bodyz.f += RelZ;
//PARTICLE.CPP
//PARTICLE.CPP		xDelta += XoffGap;
//PARTICLE.CPP		yDelta += YoffGap;
//PARTICLE.CPP
//PARTICLE.CPP		wXStart += wXStep;										//RJS 12Nov97
//PARTICLE.CPP		wYStart += wYStep;										//RJS 12Nov97
//PARTICLE.CPP		wZStart += wZStep;										//RJS 12Nov97
//PARTICLE.CPP	}
//PARTICLE.CPP
//PARTICLE.CPP	current_screen->SetTransparency(SMOKED_OFF);				//RJS 18Jun97
//PARTICLE.CPP
//PARTICLE.CPP	POLYGON.SetPixelWidth(1);
//PARTICLE.CPP 	POLYGON.SetCrossProduct(oldcross);
//PARTICLE.CPP}
//PARTICLE.CPP

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		plaincylinder
//Author		Robert Slater
//Date			Tue 4 Nov 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::plaincylinder(UWord	vertex0,UWord	vertex1, UWord	radius)
{
	DoPointStruc dopoint0,dopoint1,dopoint2,dopoint3;
	SLong		xDelta, yDelta;
	Float		xoff, yoff;											
  	SWord		angleofcylinder;									
 	SWord		sin_ang,cos_ang;
 	Bool		oldcross;
 	Float		opposite, adjacent;

//DEAD 	oldcross = POLYGON.SetCrossProduct(FALSE);

	dopoint0 = dopoint1 = newco[vertex0];										
   	dopoint2 = dopoint3 = newco[vertex1];										
 
 	// Clip Z...
 
 	if (	(dopoint0.bodyz.f > 1.0)								//RJS 27Aug98
 		||	(dopoint2.bodyz.f > 1.0)	)							//RJS 27Aug98
 	{
//		if (doingHW3D)												//RJS 21Aug98
//		{															//RJS 21Aug98
//			_matrix.body2screen(dopoint0);							//RJS 21Aug98
 //			_matrix.body2screen(dopoint2);							//RJS 21Aug98
//		}															//RJS 21Aug98

		opposite = dopoint0.screeny.f - dopoint2.screeny.f;		
 		adjacent = dopoint2.screenx.f - dopoint0.screenx.f;		

		if (opposite && adjacent)
		{
 			angleofcylinder = Math_Lib.HighArcTan(adjacent,opposite);
 			angleofcylinder -= ANGLES_90Deg;
 
 			Math_Lib.high_sin_cos((Angles) angleofcylinder,sin_ang,cos_ang);	//PD 13Nov97
 
  			xDelta = (sin_ang * radius) >> ANGLES_SHIFT;				
  			yDelta = (cos_ang * radius) >> ANGLES_SHIFT;

			if (ClipCylinder(dopoint0,dopoint1,dopoint2,dopoint3,xDelta,yDelta)==FALSE)//RJS 21Aug98
			{
//DEAD 		 		POLYGON.SetPixelWidth(1<<Save_Data.pixelsize);			
 				POLYGON.createpoly(shape::colour);						
																	
	  			POLYGON.createvert(dopoint0);					
  				POLYGON.createvert(dopoint1);					
  				POLYGON.createvert(dopoint2);					
	  			POLYGON.createvert(dopoint3);					
 																
 				POLYGON.drawpoly();							
 
//DEAD 				POLYGON.SetPixelWidth(1);
			}
		}
 	}
 
//DEAD 	POLYGON.SetCrossProduct(oldcross);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		imapcylinder
//Author		Robert Slater
//Date			Fri 16 Aug 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::imapcylinder(	UWord   vertex1,
							UWord 	vertex2,
							SLong 	radius,
							ImageMapNumber imapno,
							UWord	minix, UWord	miniy,
							UWord	width, UWord	height,
							UWord	frameno,
							UWord	depth	)					//RJS 20Nov98
{
//DeadCode RJS 21Apr99 	UByteP	adptr = (UByteP) object_obj3d->AnimPtr; 			
	SWord	minx, miny, maxx, maxy;								
	ULong	thewidth, theheight;
	DoPointStruc dopoint0,dopoint1,dopoint2,dopoint3;
 	Float	xoff, yoff;											//RJS 20Feb97
  	SWord	angleofcylinder;									
 	SWord	sin_ang,cos_ang;
 	Bool	oldcross;
 	Float	opposite, adjacent;									//RJS 20Feb97
	Bool	wantwind = FALSE;									//RJS 18Mar97
 	ImageMapDescPtr imptr = Image_Map.GetImageMapPtr(imapno);	//RJS 05Feb98
	SWord	stepx,stepy;
	SWord	nofx;


	minx = minix;		
	miny = miniy;

	if (frameno)										//RJS 05Feb98
	{													//RJS 05Feb98
		nofx = imptr->w / width;				//RJS 05Feb98
														//RJS 05Feb98
		stepy = frameno / nofx;							//RJS 05Feb98
		stepx = frameno - (stepy*nofx);					//RJS 05Feb98
														//RJS 05Feb98
		minx += stepx * width;							//RJS 05Feb98
		miny += stepy * height;							//RJS 05Feb98

		if (miny >= imptr->h)
			minx = miny = 0;
	}													//RJS 05Feb98
														//RJS 05Feb98
	maxx = minx + width-1;								//RJS 05Feb98
	maxy = miny + height;								//RJS 05Feb98
 
//DEAD 	oldcross = POLYGON.SetCrossProduct(FALSE);
 
   	dopoint0 = newco[vertex1];									//RJS 20Nov98
   	dopoint2 = newco[vertex2];									//RJS 20Nov98
 
 	// Clip Z...
 
 	if (	(dopoint0.bodyz.f > 0.0)							//RJS 27Aug98
 		||	(dopoint2.bodyz.f > 0.0)	)						//RJS 27Aug98
 	{
		if (	(dopoint0.bodyz.f < 1.0)						//RJS 27Aug98
			||	(dopoint2.bodyz.f < 1.0)	)					//RJS 27Aug98
		{														//RJS 23Jun97
		 	current_screen->zclipline(dopoint0,dopoint2);		//RJS 23Jun97
	 		_matrix.body2screen(dopoint0);						//RJS 23Jun97
 			_matrix.body2screen(dopoint2);						//RJS 23Jun97
		}														//RJS 23Jun97
		else
		{
//			if (doingHW3D)
//			{
				_matrix.body2screen(dopoint0);					//RJS 21Aug98
				_matrix.body2screen(dopoint2);					//RJS 21Aug98
//			}
		}

		dopoint1 = dopoint0;									//RJS 25Jun97
		dopoint3 = dopoint2;									//RJS 25Jun97

//		if (dopoint2.bodyz.f < 1172)							//RJS 24Jun97
//			depth = 0;											//RJS 24Jun97

		opposite = dopoint0.screeny.f - dopoint2.screeny.f;		//RJS 19May97
 		adjacent = dopoint2.screenx.f - dopoint0.screenx.f;		//RJS 19May97

		if (opposite || adjacent)								//MS 30Nov98
		{
			Float res=10430.37835047*FPATan(adjacent,opposite);

			angleofcylinder = res;   //Math_Lib.HighArcTan(adjacent,opposite);	//RJS 23Sep96
 			angleofcylinder -= ANGLES_90Deg;
 
 			Math_Lib.high_sin_cos((Angles) angleofcylinder,sin_ang,cos_ang);
 
  			xoff = (sin_ang * radius) / ANGLES_FRACT;				//RJS 13Jun97
  			yoff = (cos_ang * radius) / ANGLES_FRACT;				//RJS 13Jun97

			if (ClipCylinder(dopoint0,dopoint1,dopoint2,dopoint3,xoff,yoff)==FALSE)//RJS 21Aug98
			{														//RJS 21Aug98
//DEAD 		 		POLYGON.SetPixelWidth(1<<Save_Data.pixelsize);			//RJS 25Jun97
 				POLYGON.createpoly(imapno);								//RJS 25Jun97
	  			POLYGON.createvert(dopoint3,minx,maxy);					//RJS 13Jun97
  				POLYGON.createvert(dopoint2,maxx,maxy);					//RJS 13Jun97
  				POLYGON.createvert(dopoint1,maxx,miny);					//RJS 13Jun97
	  			POLYGON.createvert(dopoint0,minx,miny);					//RJS 13Jun97
									//RJS 13Jun97
				if (depth)												//RJS 20Jun97
				{														//RJS 20Jun97
					current_screen->SetTransparency(depth);				//RJS 20Jun97
					POLYGON.SetOpacityON();								//RJS 20Jun97
 					POLYGON.drawpoly();									//RJS 20Jun97
	  				current_screen->SetTransparency(SMOKED_OFF);		//RJS 20Jun97
				}														//RJS 20Jun97
				else													//RJS 20Jun97
	 				POLYGON.drawpoly();									//RJS 20Jun97
 
//DEAD 				POLYGON.SetPixelWidth(1);
			}
		}
 	}
 
//DEAD 	POLYGON.SetCrossProduct(oldcross);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		omapcylinder
//Author		Robert Slater
//Date			Mon 23 Sep 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::omapcylinder(	UWord vertex,
							UWord depth,						//RJS 20Jun97
							SLong radius,
							ImageMapNumber imapno,
							UWord	minix, UWord miniy,
							UWord	maxix, UWord maxiy,
							UWord	width, UWord height,
							UByte	divfactor,
							UByte	flagoffset)
{
//DeadCode RJS 27Aug98 	UByteP	adptr = (UByteP) object_obj3d->AnimPtr; 			
//DeadCode RJS 27Aug98 	UByte	frameno = adptr[flagoffset] / divfactor;
//DeadCode RJS 27Aug98 	SWord	minx, miny, maxx, maxy;								
//DeadCode RJS 27Aug98 	ULong	thewidth, theheight;
//DeadCode RJS 27Aug98 	DoPointStruc dopoint0,dopoint1,dopoint2,dopoint3;
//DeadCode RJS 27Aug98  	Float	xoff, yoff;											//RJS 20Feb97
//DeadCode RJS 27Aug98   	SWord	angleofcylinder;									
//DeadCode RJS 27Aug98  	SWord	sin_ang,cos_ang;
//DeadCode RJS 27Aug98  	Bool	oldcross;
//DeadCode RJS 27Aug98  	Float	opposite, adjacent;									//RJS 20Feb97
//DeadCode RJS 27Aug98 
//DeadCode RJS 27Aug98 	minx = minix;		
//DeadCode RJS 27Aug98 	miny = miniy;		
//DeadCode RJS 27Aug98 	maxx = maxix - 1;	
//DeadCode RJS 27Aug98 	maxy = maxiy;
//DeadCode RJS 27Aug98 
//DeadCode RJS 27Aug98 	theheight = maxiy - miniy;
//DeadCode RJS 27Aug98 
//DeadCode RJS 27Aug98 	//Cycle through the animation frames				
//DeadCode RJS 27Aug98 
//DeadCode RJS 27Aug98 	miny += height * frameno;							
//DeadCode RJS 27Aug98 	maxy = miny + theheight - 1;
//DeadCode RJS 27Aug98 
//DeadCode RJS 27Aug98 
//DeadCode RJS 27Aug98 	oldcross = POLYGON.SetCrossProduct(FALSE);
//DeadCode RJS 27Aug98  
//DeadCode RJS 27Aug98  	ImageMapNumber	absimapno = (ImageMapNumber )((imapno<0)?-imapno:imapno);
//DeadCode RJS 27Aug98  	ImageMapDescPtr imptr = Image_Map.GetImageMapPtr(absimapno);
//DeadCode RJS 27Aug98  
//DeadCode RJS 27Aug98  	// Clip Z...
//DeadCode RJS 27Aug98 
//DeadCode RJS 27Aug98  	if (	(newco[vertex].bodyz.f > 0)							//RJS 13Jun97
//DeadCode RJS 27Aug98  		||	(newco[1].bodyz.f > 0)	)							//RJS 20Jun97
//DeadCode RJS 27Aug98 	{															//RJS 13Jun97
//DeadCode RJS 27Aug98 	  	dopoint0 = dopoint1 = newco[vertex];					//RJS 13Jun97
//DeadCode RJS 27Aug98   		dopoint2 = dopoint3 = newco[1];							//RJS 20Jun97
//DeadCode RJS 27Aug98 
//DeadCode RJS 27Aug98 	 	opposite = dopoint0.screeny.f - dopoint2.screeny.f;		//RJS 19May97
//DeadCode RJS 27Aug98 	 	adjacent = dopoint2.screenx.f - dopoint0.screenx.f;		//RJS 19May97
//DeadCode RJS 27Aug98 
//DeadCode RJS 27Aug98  		angleofcylinder = Math_Lib.HighArcTan(adjacent,opposite);	//RJS 23Sep96
//DeadCode RJS 27Aug98  		angleofcylinder -= ANGLES_90Deg;
//DeadCode RJS 27Aug98  
//DeadCode RJS 27Aug98  		Math_Lib.high_sin_cos((Angles) angleofcylinder,sin_ang,cos_ang);
//DeadCode RJS 27Aug98  
//DeadCode RJS 27Aug98 		xoff = (sin_ang * radius) / ANGLES_FRACT;				//RJS 20Jun97
//DeadCode RJS 27Aug98   		yoff = (cos_ang * radius) / ANGLES_FRACT;				//RJS 20Jun97
//DeadCode RJS 27Aug98 
//DeadCode RJS 27Aug98 		if (VapourCyl)											//RJS 14May97
//DeadCode RJS 27Aug98 		{
//DeadCode RJS 27Aug98 			dopoint0 = CylPnt1;
//DeadCode RJS 27Aug98 			dopoint1 = CylPnt2;
//DeadCode RJS 27Aug98 		}
//DeadCode RJS 27Aug98 		else
//DeadCode RJS 27Aug98 		{
//DeadCode RJS 27Aug98   			dopoint0.bodyx.f += xoff;								//RJS 20Feb97
//DeadCode RJS 27Aug98   			dopoint0.bodyy.f += yoff;								//RJS 20Feb97
//DeadCode RJS 27Aug98   
//DeadCode RJS 27Aug98   			dopoint1.bodyx.f += -xoff;								//RJS 20Feb97
//DeadCode RJS 27Aug98   			dopoint1.bodyy.f += -yoff;								//RJS 20Feb97
//DeadCode RJS 27Aug98 		}
//DeadCode RJS 27Aug98   
//DeadCode RJS 27Aug98   		dopoint2.bodyx.f += -xoff;								//RJS 20Feb97
//DeadCode RJS 27Aug98   		dopoint2.bodyy.f += -yoff;								//RJS 20Feb97
//DeadCode RJS 27Aug98   
//DeadCode RJS 27Aug98   		dopoint3.bodyx.f += xoff;								//RJS 20Feb97
//DeadCode RJS 27Aug98   		dopoint3.bodyy.f += yoff;								//RJS 20Feb97
//DeadCode RJS 27Aug98 
//DeadCode RJS 27Aug98 		current_screen->zclipline(dopoint1,dopoint2);			//RJS 13Jun97
//DeadCode RJS 27Aug98 		current_screen->zclipline(dopoint0,dopoint3);			//RJS 13Jun97
//DeadCode RJS 27Aug98 
//DeadCode RJS 27Aug98 		_matrix.SetClipFlags(dopoint0);
//DeadCode RJS 27Aug98 		_matrix.SetClipFlags(dopoint1);
//DeadCode RJS 27Aug98 		_matrix.SetClipFlags(dopoint2);
//DeadCode RJS 27Aug98 		_matrix.SetClipFlags(dopoint3);
//DeadCode RJS 27Aug98 
//DeadCode RJS 27Aug98  		_matrix.body2screen(dopoint0);							//RJS 13Jun97
//DeadCode RJS 27Aug98  		_matrix.body2screen(dopoint1);							//RJS 13Jun97
//DeadCode RJS 27Aug98  		_matrix.body2screen(dopoint2);							//RJS 13Jun97
//DeadCode RJS 27Aug98  		_matrix.body2screen(dopoint3);							//RJS 13Jun97
//DeadCode RJS 27Aug98 
//DeadCode RJS 27Aug98  		CylPnt1 = dopoint3;										//RJS 14May97
//DeadCode RJS 27Aug98 		CylPnt2 = dopoint2;										//RJS 14May97
//DeadCode RJS 27Aug98 
//DeadCode RJS 27Aug98  		if (object_obj3d->Shape!=SUN)
//DeadCode RJS 27Aug98  			POLYGON.SetPixelWidth(1<<Save_Data.pixelsize);
//DeadCode RJS 27Aug98  
//DeadCode RJS 27Aug98  		POLYGON.createpoly(imapno);								//RJS 20Jun97
//DeadCode RJS 27Aug98  		POLYGON.createvert(dopoint0,minx,miny);					//RJS 20Jun97
//DeadCode RJS 27Aug98 		POLYGON.createvert(dopoint1,maxx,miny);					//RJS 20Jun97
//DeadCode RJS 27Aug98 		POLYGON.createvert(dopoint2,maxx,maxy);					//RJS 20Jun97
//DeadCode RJS 27Aug98   		POLYGON.createvert(dopoint3,minx,maxy);					//RJS 20Jun97
//DeadCode RJS 27Aug98 
//DeadCode RJS 27Aug98 		current_screen->SetTransparency(depth);
//DeadCode RJS 27Aug98 		POLYGON.SetOpacityON();
//DeadCode RJS 27Aug98  		POLYGON.drawpoly();
//DeadCode RJS 27Aug98   		current_screen->SetTransparency(SMOKED_OFF);
//DeadCode RJS 27Aug98 
//DeadCode RJS 27Aug98  		POLYGON.SetPixelWidth(1);
//DeadCode RJS 27Aug98   	}
//DeadCode RJS 27Aug98  
//DeadCode RJS 27Aug98  	POLYGON.SetCrossProduct(oldcross);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetPilotedAcAnim
//Author		Paul.   
//Date			Tue 16 Apr 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::SetPilotedAcAnim(AirStrucPtr pilotedac)
{
	int		count;												//RJS 23Aug96

	PolyPitAnimData		*newanim = new PolyPitAnimData;
	AircraftAnimData	*oldanim = (AircraftAnimData* )pilotedac->Anim,
						*naa=newanim;

	animptr		thenewanim;

	*naa=*oldanim;

	thenewanim = pilotedac->Anim;
	thenewanim = (UByteP)newanim;

	//Bollocks for the detail.....
	newanim->detailmask = 0;										//RJS 26Jan98
	newanim->detailmask |= (1 << COCK3D_DIALSROW1ON);				//RJS 26Jan98
	newanim->detailmask |= (1 << COCK3D_DIALSROW2ON);				//RJS 26Jan98
	newanim->detailmask |= (1 << COCK3D_DIALSROW3ON);				//RJS 26Jan98
	newanim->detailmask |= (1 << COCK3D_DIALSROW4ON);				//RJS 26Jan98
	newanim->detailmask |= (1 << COCK3D_PANELIMAPDSPLIT);			//RJS 26Jan98
	newanim->detailmask |= (1 << COCK3D_PANELGLASSFRONT);			//RJS 25Mar98

//	newanim->compasscount = 0;									//RJS 05Jun97
//	newanim->muzzlego = FALSE;									//RJS 05Jun97

	delete (oldanim);

	pilotedac->Anim = thenewanim;
	pilotedac->Anim = sizeof(PolyPitAnimData)
						+ (1<<MINANIM)
						+ (1<<MOVEGUNANIM)
						+ (1<<AIRCRAFTANIM)
						+ (1<<POLYPITANIM);

	Trans_Obj.WeaponSearch(pilotedac);								//RJS 02Nov98
};


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DrawHitBox
//Author		Paul.   
//Date			Wed 23 Oct 1996
//
//Description	Draws a Magenta box around a shapes hit area
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::DrawHitBox(Window* screen,Obj3DPtr obj3dptr,MATRIX_PTR matp)
{
 	if (!Three_Dee.shapecheat || Save_Data.fSoftware)
		return;

	SWord	dx,dy,dz;

	ShapeDescPtr	sdp;

	DOSETCOLOUR256	idosetcolour256;
	DOPOINT			idopoint;
	DOLINE			idoline;

	UByte*			instp;

	SLong		tmpscale;

	sdp = SHAPESTUFF.GetShapePtr((ShapeNum)obj3dptr->Shape);
 	switch(SHAPESTUFF.GetShapeScale(sdp))				//PD 23Apr96
 	{
 		case SHP_1CM:
 			tmpscale = 0;										//PD 10Apr96
 			break;												//PD 10Apr96
 
 		case SHP_4CM:
 			tmpscale = 2;										//PD 10Apr96
 			break;												//PD 10Apr96
 
 		case SHP_16CM:
 			tmpscale = 4;										//PD 10Apr96
 			break;												//PD 10Apr96
 	}


//	dx = sdp->sx << 4;											//RJS 20Apr98
//	dy = sdp->sy << 4;											//RJS 20Apr98
//	dz = sdp->sz << 4;											//RJS 20Apr98

 	dx = sdp->sx<<(4-tmpscale);
 	dy = sdp->sy<<(4-tmpscale);
 	dz = sdp->sz<<(4-tmpscale);

	switch (Save_Data.targetsize)
	{
		case TS_LARGE:
			dx<<=1;
			dy<<=1;
			dz<<=1;
			break;
		case TS_MEDIUM:
			dx=(dx<<1)-(dx>>1);
			dy=(dy<<1)-(dy>>1);
			dz=(dz<<1)-(dz>>1);
			break;
		case TS_SMALL:
			break;
	}

	idosetcolour256.basecolour = RED;
	idosetcolour256.spread = 1;
	idosetcolour256.imap = 0xFF;
	instp = (UByte*)&idosetcolour256;
	SHAPE.dosetcolour256(instp);

	idopoint.vertex = 0;
	idopoint.xcoord = -dx;
	idopoint.ycoord = -dy;
	idopoint.zcoord = -dz;
	instp = (UByte*)&idopoint;
	SHAPE.dopoint(instp);

	idopoint.vertex = 1;
	idopoint.xcoord = -dx;
	idopoint.ycoord = -dy;
	idopoint.zcoord = dz;
	instp = (UByte*)&idopoint;
	SHAPE.dopoint(instp);

 	idopoint.vertex = 2;
	idopoint.xcoord = dx;
	idopoint.ycoord = -dy;
	idopoint.zcoord = dz;
	instp = (UByte*)&idopoint;
	SHAPE.dopoint(instp);

	idopoint.vertex = 3;
	idopoint.xcoord = dx;
	idopoint.ycoord = -dy;
	idopoint.zcoord = -dz;
	instp = (UByte*)&idopoint;
	SHAPE.dopoint(instp);

	idopoint.vertex = 4;
	idopoint.xcoord = -dx;
	idopoint.ycoord = dy;
	idopoint.zcoord = -dz;
	instp = (UByte*)&idopoint;
	SHAPE.dopoint(instp);

	idopoint.vertex = 5;
	idopoint.xcoord = -dx;
	idopoint.ycoord = dy;
	idopoint.zcoord = dz;
	instp = (UByte*)&idopoint;
	SHAPE.dopoint(instp);

	idopoint.vertex = 6;
	idopoint.xcoord = dx;
	idopoint.ycoord = dy;
	idopoint.zcoord = dz;
	instp = (UByte*)&idopoint;
	SHAPE.dopoint(instp);

	idopoint.vertex = 7;
	idopoint.xcoord = dx;
	idopoint.ycoord = dy;
	idopoint.zcoord = -dz;
	instp = (UByte*)&idopoint;
	SHAPE.dopoint(instp);

	idoline.start_vertex = 0;
	idoline.end_vertex = 1;
	instp = (UByte*)&idoline;
	SHAPE.doline(instp);

	idoline.start_vertex = 1;
	idoline.end_vertex = 2;
	instp = (UByte*)&idoline;
	SHAPE.doline(instp);

	idoline.start_vertex = 2;
	idoline.end_vertex = 3;
	instp = (UByte*)&idoline;
	SHAPE.doline(instp);

	idoline.start_vertex = 3;
	idoline.end_vertex = 0;
	instp = (UByte*)&idoline;
	SHAPE.doline(instp);

	idoline.start_vertex = 4;
	idoline.end_vertex = 5;
	instp = (UByte*)&idoline;
	SHAPE.doline(instp);

	idoline.start_vertex = 5;
	idoline.end_vertex = 6;
	instp = (UByte*)&idoline;
	SHAPE.doline(instp);

	idoline.start_vertex = 6;
	idoline.end_vertex = 7;
	instp = (UByte*)&idoline;
	SHAPE.doline(instp);

	idoline.start_vertex = 7;
	idoline.end_vertex = 4;
	instp = (UByte*)&idoline;
	SHAPE.doline(instp);

	idoline.start_vertex = 0;
	idoline.end_vertex = 4;
	instp = (UByte*)&idoline;
	SHAPE.doline(instp);

	idoline.start_vertex = 1;
	idoline.end_vertex = 5;
	instp = (UByte*)&idoline;
	SHAPE.doline(instp);

	idoline.start_vertex = 2;
	idoline.end_vertex = 6;
	instp = (UByte*)&idoline;
	SHAPE.doline(instp);

	idoline.start_vertex = 3;
	idoline.end_vertex = 7;
	instp = (UByte*)&idoline;
	SHAPE.doline(instp);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Noise
//Author		Robert Slater
//Date			Wed 12 Nov 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SLong shape::Noise(SLong	wx, SLong	wy, SLong	wz)
{
	wx &= 0xFF;
	wy &= 0xFF;
	wz &= 0xFF;

	return(RandTable[(RandTable[wx]+RandTable[wy]+RandTable[wz])&0xFF]);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitTrailFields
//Author		Robert Slater
//Date			Mon 12 Jan 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::InitTrailFields(	UByteP		wptr,
								int			index,
								int			capacity,
								LnchrType	ltype		)
{
	if (wptr)			
	{
		WeapAnimData  *weapon = (WeapAnimData*) wptr;

		if (weapon->hdg==0)						//RJS 21Jan99
		{
			weapon->LauncherType = ltype;
			weapon->LaunchTime = 0;
			weapon->hdg = index;
			weapon->pitch = capacity;
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		WingSpanUp
//Author		Robert Slater
//Date			Mon 20 Apr 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::WingSpanUp()
{
	WingSpan += 15;					// 0.5 feet
	if (WingSpan > 4876)
		WingSpan = 4876;			// 160 feet
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		WingSpanDown
//Author		Robert Slater
//Date			Mon 20 Apr 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::WingSpanDown()
{
	WingSpan -= 15;					// .5 feet
	if (WingSpan < 609)		
		WingSpan = 609;				//20 feet
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GunRangeUp
//Author		Robert Slater
//Date			Mon 20 Apr 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::GunRangeUp()
{
	// Max is 5000 yds...
	RequiredRange += 100;
	if (RequiredRange > 50813)									//RJS 11Dec98
		RequiredRange = 50813;									//RJS 11Dec98
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GunRangeDown
//Author		Robert Slater
//Date			Mon 20 Apr 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::GunRangeDown()
{
	RequiredRange -= 100;
	if (RequiredRange < 10000)									//RJS 11Dec98
		RequiredRange = 10000;									//RJS 11Dec98
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SampleDustPnt
//Author		Robert Slater
//Date			Thu 7 May 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	shape::SampleDustPnt(	UByteP		smkinfo,
								SWord		&listindex,
								UByteP		instr_ptr,
								UWord		LifeTime,
								SLong		gheight,
								SWord		realpitch	)
{
	Bool	validpoint = TRUE;

	if (SamplePntTime)
	{
		DOLAUNCHER_PTR	ptr = (DOLAUNCHER_PTR) instr_ptr;
		TrailRecord*	trailptr = &traillist[listindex];
		SmokeTypeP		smkptr = (SmokeTypeP) smkinfo;
		SLong			xcoord = ptr->posx;
		SLong			ycoord = ptr->posy;
		SLong			zcoord = ptr->posz;
		SLong			lifetime;
		SLong			wx, wy, wz;
		SWord			index = listindex;
		MATRIX  		omat;										
		MATRIX_PTR		obj_matrix = &omat;							
		UWord			scaleback;
		SWord			sin_ang, cos_ang;
		SLong			hyp = 0;
		SLong			wwz;
		SLong			tailbit = zcoord << shapescale;
		SLong			tailfrac;
		ItemPtr			tmpitem;

		Math_Lib.high_sin_cos((Angles) realpitch,sin_ang,cos_ang);

		if (sin_ang)
			hyp = (gheight<<15) / sin_ang;

		tmpitem = new item;

		hyp -= tailbit;

		if (!LifeTime)											
			LifeTime = smkptr->LifeTime;						

		LifeTime = (LifeTime * -tailbit)/hyp;
		if (!LifeTime)
		{
			LifeTime = 10;
			hyp = -tailbit;
		}

		trailptr->SampleTime -= View_Point->FrameTime();		
		if (trailptr->SampleTime < 0)							
			trailptr->SampleTime = smkptr->SampleTime;			
		else													
			validpoint = FALSE;									

		lifetime = LifeTime;							

 		if (trailptr->nextlist)
 		{
 			Coords3DList*	nextptr = traillist[trailptr->nextlist].thelist;
 			if (nextptr)
 			{
 				wx = nextptr->trailpoint.gx;
 				wy = nextptr->trailpoint.gy;
 				wz = nextptr->trailpoint.gz;

 				SHAPE.AddNewVapourPoint(trailptr,wx,wy,wz,lifetime,smkptr->FadeTime);
 				lifetime = trailptr->lifetime;
 			}

 			trailptr->nextlist = 0;
 		}

		// Every frame....

 		wx = xcoord << shapescale;
 		wy = ycoord << shapescale;
 		wz = -hyp;

		_matrix.generate2(	object_obj3d->AngH,
							object_obj3d->AngC,
							object_obj3d->AngR,
							obj_matrix);

		scaleback = _matrix.transform(obj_matrix,wx,wy,wz);
		wx >>= (16-scaleback);
		wy >>= (16-scaleback);
		wz >>= (16-scaleback);

		wx += trailptr->lastwx;
		wy += trailptr->lastwy;
		wz += trailptr->lastwz;

		tmpitem->World.X = wx;
		tmpitem->World.Y = wy;
		tmpitem->World.Z = wz;

		wy = Land_Scape.GetGroundLevel(tmpitem);
		if (wy <= trailptr->lastwy)
		{
			SHAPE.AddNewVapourPoint(trailptr,wx,wy,wz,lifetime,smkptr->FadeTime);
			if (trailptr->nopoints > 127)
			{
 				trailptr->bitshift = 0;
				listindex = 0;			//RJS 12/4/99
//DEADCODE DAW 12/04/99 				listindex = -index;
				SHAPE.DetatchVapourStream(index,lifetime);
			}
		}

		delete tmpitem;
	}

	return(validpoint);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitUndercarriageAnim
//Author		Robert Slater
//Date			Thu 28 May 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::InitUndercarriageAnim(AirStrucPtr	itm)
{
	if (itm->vel)
		itm->fly.pModel->SetGearAnimPos(itm, ANIM_GEAR_UP);
	else
		itm->fly.pModel->SetGearAnimPos(itm, ANIM_GEAR_DOWN);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RipStores					   MODIFIED
//Author		Robert Slater				   CRAIG BEESTON
//Date			Wed 3 Jun 1998				   Tue 27 Apr 1999
//
//Description	Removes fuel stores after (5 g's for 13 secs - to - 8g's for 1 frame)
//
//				Should set up a flag in airstruc to say they've been removed,
//				so we don't come into this routine again.....
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::RipStores(AirStrucPtr	ac)
{
	if(!Save_Data.flightdifficulty [FD_EXCESSIVEACCELDAMAGE])
		return;
	
	const FP MinGs = 5.0;
	const FP MaxGs = 8.0;

	if (ac->weap.FuelDumped == FALSE)
		if(ac->fly.pModel->Inst.NormalAcc > MinGs)
		{
			bool dodump = false;
			if(ac->fly.pModel->Inst.NormalAcc < MaxGs)
			{
				SLong gs = ((MaxGs - ac->fly.pModel->Inst.NormalAcc) * 65535.0) / (MaxGs - MinGs) + 1.0;
				gs = (100 * 65535) / gs;
				UWord chance = Math_Lib.rnd();
				if (chance < gs)
					dodump = true;
			}
			else
				dodump = true;

			if (dodump)
			{
				WorldStuff*	world = mobileitem::currworld;
				Trans_Obj.DumpFuel(ac,*world,TRUE);				//RJS 04Feb99
			}
		}
//DeadCode CSB 27/04/99		if (ac->weap.FuelDumped == FALSE)
//DeadCode CSB 27/04/99		{
//DeadCode CSB 27/04/99			SLong	gs = ((ac->fly.pModel->Inst.NormalAcc - 3.0) * 65535.0);
//DeadCode CSB 27/04/99			if (gs > 0)
//DeadCode CSB 27/04/99			{
//DeadCode CSB 27/04/99				bool dodump = false;
//DeadCode CSB 27/04/99				gs /= 3;
//DeadCode CSB 27/04/99				if (gs < 65535)
//DeadCode CSB 27/04/99				{
//DeadCode CSB 27/04/99					ULong	chance = Math_Lib.rnd();
//DeadCode CSB 27/04/99					chance = (chance*gs)>>16;
//DeadCode CSB 27/04/99					if (chance > 64000)
//DeadCode CSB 27/04/99						dodump = true;
//DeadCode CSB 27/04/99				}
//DeadCode CSB 27/04/99				else
//DeadCode CSB 27/04/99					dodump = true;
//DeadCode CSB 27/04/99	
//DeadCode CSB 27/04/99				if (dodump)
//DeadCode CSB 27/04/99				{
//DeadCode CSB 27/04/99					WorldStuff*	world = mobileitem::currworld;
//DeadCode CSB 27/04/99					Trans_Obj.DumpFuel(ac,*world,TRUE);				//RJS 04Feb99
//DeadCode CSB 27/04/99				}
//DeadCode CSB 27/04/99			}
//DeadCode CSB 27/04/99		}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AnimMap
//Author		Robert Slater
//Date			Mon 22 Jun 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	shape::AnimMap(	animptr&	adptr,
						SWord	imap,
						SWord	animflag,
						SWord	animscale,
						SWord	&minx,
						SWord	&miny,
						SWord	width,
						SWord	height)
{
	Bool	retval = FALSE;
	if (animflag)
	{
		SWord			frameno;
		SWord			nofx,stepy,stepx;
		ImageMapDescPtr imptr = Image_Map.GetImageMapPtr((ImageMapNumber )imap);

		frameno = adptr[animflag]/animscale;

		nofx = imptr->w / width;						
		if (nofx)
		{
	 		stepy = frameno / nofx;					
			stepx = frameno - (stepy*nofx);		
												
			minx += stepx * width;					
			miny += stepy * height;
			if (miny >= imptr->h)
				minx = miny = 0;
		}
	}

	return(retval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetRadarItem
//Author		Robert Slater
//Date			Thu 25 Jun 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::GetRadarItem(ItemPtr	itm, SLong	range)
{
	if ((range > 100) && (range < radarRange))		// must be at least a metre away
	{
		FPMATRIX_PTR	matp = &radarMatrix;
		IFShare			wx, wy, wz;
		SLong			wxx,wyy,wzz;
		SLong			viewz;
		SLong			temp;

		wx.i = itm->World.X - viewer_x;
		wy.i = itm->World.Y - viewer_y;
		wz.i = itm->World.Z - viewer_z;

		_matrix.transform(matp,wx,wy,wz);

		// Cleaned up by Rob.
		wzz = SLong(wz.f);
		if (wzz > 0)
		{
			wxx = SLong(wx.f);
			wyy = SLong(wy.f);

			viewz = wzz;
			temp = (wxx<0?-wxx:wxx);
			if (temp<=viewz)
			{
				temp = (wyy<0?-wyy:wyy);
				if (temp <= viewz)
				{
					// New lock....
					radarTmpItm = itm;
					radarRange = range;
				}
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CalcRadarRange
//Author		Robert Slater
//Date			Thu 25 Jun 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::CalcRadarRange(AirStrucPtr	me)
{
//DeadCode RDH 13Apr99 	if (RadarItemPtr)
//DeadCode RDH 13Apr99 	{
//DeadCode RDH 29Nov98 		SWord	dummy1, dummy2;
//DeadCode RDH 29Nov98 		Math_Lib.Intercept(	RadarItemPtr->World.X - me->World.X,
//DeadCode RDH 29Nov98 							RadarItemPtr->World.Y - me->World.Y,
//DeadCode RDH 29Nov98 							RadarItemPtr->World.Z - me->World.Z,
//DeadCode RDH 29Nov98 							RequiredRange,dummy1,dummy2);
//DeadCode RDH 13Apr99 
//DeadCode RDH 13Apr99 		RequiredRange = Math_Lib.distance3d(RadarItemPtr->World.X - me->World.X,
//DeadCode RDH 13Apr99 											RadarItemPtr->World.Y - me->World.Y,
//DeadCode RDH 13Apr99 											RadarItemPtr->World.Z - me->World.Z	);
//DeadCode RDH 13Apr99 
//DeadCode RDH 13Apr99 		if (RequiredRange > 100000)								//RJS 11Dec98
//DeadCode RDH 13Apr99 			RequiredRange = 100000;								//RJS 11Dec98
//DeadCode RDH 13Apr99 																//RJS 11Dec98
//DeadCode RDH 13Apr99 		if (RequiredRange < 20000)								//RJS 11Dec98
//DeadCode RDH 13Apr99 			RequiredRange = 20000;								//RJS 11Dec98
//DeadCode RDH 13Apr99 	}
	bool fixsight;												//CSB 09Jun99
	if ((me->weap.weapontype & LT_MASK) == LT_BULLET)			//CSB 09Jun99
		fixsight = false;										//CSB 09Jun99
	else														//CSB 09Jun99
		fixsight = true;										//CSB 09Jun99
																//CSB 09Jun99
	me->fly.pModel->RememberForGunSight(fixsight);				//CSB 09Jun99

	GunSightPos.X = me->World.X;
	GunSightPos.Y = me->World.Y;
	GunSightPos.Z = me->World.Z;

	GunSightHdg = me->hdg;
	GunSightPitch = me->pitch;
	GunSightRoll = me->roll;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClearRadar
//Author		Robert Slater
//Date			Thu 25 Jun 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::ClearRadar()
{
	RadarItemPtr = NULL;
	ResetRadar(NULL,0,0,0);
	radarTimer = -1;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddSmokeCloud
//Author		Robert Slater
//Date			Fri 3 Jul 1998
//
//Description	Kill the oldest smoke point,
//				Then launch transient smoke cloud...
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::AddSmokeCloud(TrailRecord* trailptr, ShapeNum	cloudshape, int index)
{
	Coords3DList*	apoint = trailptr->thelist;
	Coords3DList*	npoint;
	Coords3DList*	*lpointptr = &trailptr->thelist;
	COORDS3D		World;

	while (apoint)
	{
		npoint = apoint->next;
		if (npoint == NULL)
		{
			World.X = apoint->trailpoint.gx;
			World.Y = apoint->trailpoint.gy;
			World.Z = apoint->trailpoint.gz;

			delete apoint;
			trailptr->nopoints--;

			apoint = NULL;
			*lpointptr = NULL;
		}
		else
		{
			lpointptr = &apoint->next;
			apoint = npoint;
		}
	}

	if (cloudshape && (trailptr->cloudlaunched==FALSE))
	{
		WorldStuff*	worldptr = mobileitem::currworld;

		trailptr->cloudlaunched = TRUE;
		Trans_Obj.LaunchSmokeCloud((mobileitem*) object_obj3d->ItemPtr,
									cloudshape,
 									World,
									*worldptr	);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DefaultAnimData
//Author		Robert Slater
//Date			Mon 6 Jul 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::DefaultAnimData(itemptr itm, animptr&	adptr, Bool isReplay)
{
	ShapeDescPtr	sdptr;
	UByteP			instr_ptr;
	Bool			haslaunchers = FALSE;

	sdptr = SHAPESTUFF.GetShapePtr(itm->shape);

	animptr	animdataptr = adptr;

	globinitairitem = NULL;
	globinititem = itm;											//RJS 21Apr99

	switch (SHAPESTUFF.GetShapeScale(sdptr))					//PD 23Apr96
	{
		case SHP_GRP:

			SLong	tmp;
			ShapeNum	newshp;

			instr_ptr = (UByteP )sdptr + sdptr->liveshpref;

			while (GetGroupElement(instr_ptr,newshp,tmp,tmp,tmp))
			{
				if (GetNumberOfLaunchers(newshp) > 0)
					haslaunchers = TRUE;

				InitItemAnim(animdataptr,newshp);
				animdataptr[0] = 0x80;							//RJS 21Apr99
				animdataptr += 1;								//RJS 21Apr99
			}

			if (haslaunchers)
				sdptr->Type.haslaunchers = TRUE;
			else
				sdptr->Type.haslaunchers = FALSE;

			break;

		case SHP_1CM:
		case SHP_4CM:
		case SHP_16CM:
			if ((itm->Status.size == AirStrucSize) && (isReplay == FALSE))//RJS 06Jul98
			{
				AirStrucPtr	asptr = (AirStrucPtr) itm;

				asptr->fly.inRadarSight = FALSE;				//RJS 13May99

				asptr->weap.shpweapindex = 0;					//RDH 03Aug98

				asptr->weap.left.reloadmass = 0;				//RJS 25Jan99
				asptr->weap.left.reloaddrag = 0;				//RJS 25Jan99
				asptr->weap.left.mass = 0;
				asptr->weap.left.drag = 0;
				asptr->weap.left.int_fuel = 0;
				asptr->weap.left.int_fuel_leakage = 0;
				asptr->weap.left.int_launcher = -1;				//RJS 25Mar99
				asptr->weap.left.ext_fuel = 0;					//RJS 25Mar99
				asptr->weap.left.ext_fuel_leakage = 0;			//RJS 25Mar99
				asptr->weap.left.ext_launcher = -1;				//RJS 25Mar99

				asptr->weap.centre.reloadmass = 0;				//RJS 25Jan99
				asptr->weap.centre.reloaddrag = 0;				//RJS 25Jan99
				asptr->weap.centre.mass = 0;
				asptr->weap.centre.drag = 0;
				asptr->weap.centre.int_fuel = 0;
				asptr->weap.centre.int_fuel_leakage = 0;
				asptr->weap.centre.int_launcher = -1;			//RJS 25Mar99
				asptr->weap.centre.ext_fuel = 0;				//RJS 25Mar99
				asptr->weap.centre.ext_fuel_leakage = 0;		//RJS 25Mar99
				asptr->weap.centre.ext_launcher = -1;			//RJS 25Mar99

				asptr->weap.right.reloadmass = 0;				//RJS 25Jan99
				asptr->weap.right.reloaddrag = 0;				//RJS 25Jan99
				asptr->weap.right.mass = 0;
				asptr->weap.right.drag = 0;
				asptr->weap.right.int_fuel = 0;
				asptr->weap.right.int_fuel_leakage = 0;
				asptr->weap.right.int_launcher = -1;			//RJS 25Mar99
				asptr->weap.right.ext_fuel = 0;					//RJS 25Mar99
				asptr->weap.right.ext_fuel_leakage = 0;			//RJS 25Mar99
				asptr->weap.right.ext_launcher = -1;			//RJS 25Mar99

				asptr->weap.UseIntFuel = TRUE;		//Default fuel switch	RJS 23Jun98
				asptr->weap.FuelDumped = TRUE;		//Default fuel dump		RJS 23Jun98
				asptr->weap.weapforce = 0;			//Weapon force
				asptr->weap.Ejected = FALSE;
				asptr->weap.StoresDumped = TRUE;	//Default dumped//RJS 18Jun99

				asptr->lasthitter.count = (UniqueID)0;								//RJS 23May99

				globinitairitem = asptr;
			}

			InitItemAnim(animdataptr,itm->shape);					//RJS 13May98
			break;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ScanAnimData
//Author		Robert Slater
//Date			Mon 6 Jul 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
int	shape::ScanAnimData(itemptr	itm)
{
	int	ChangeCnt = 0;

	SLong	animdatasize = GetAnimDataSize(itm->shape);
	if (itm->Anim != NULL)
	{
		UByteP	adptr2 = new UByte[animdatasize];
		if (adptr2)
		{
			UByteP	adptr = &itm->Anim[0];						//RJS 26May99
			UByte	oldval, newval;
			UWord	newoffset = 0;
			UWord	oldoffset = 0;
			UByteP	temp;
			animptr newanimdata = itm->Anim;					//RJS 26May99
			int		animcnt;									//RJS 26May99

			temp=adptr2;
			newanimdata = adptr2;

			memset(adptr2,0,animdatasize);	//Banana
			if (itm->Status.size == AIRSTRUCSIZE)						//RJS 27May99
				AnimWeaponPack = ((AirStrucPtr)itm)->weap.Weapons;		//RJS 27May99
			else														//RJS 27May99
				AnimWeaponPack = 0;										//RJS 27May99

			DefaultAnimData(itm,newanimdata,TRUE);

//Dead			AircraftAnimData*	acanimnow = (AircraftAnimData*) adptr;
//Dead			AircraftAnimData*	acanimdefault = (AircraftAnimData*) adptr2;

			for (animcnt = 0; animcnt < animdatasize; animcnt++)//DAW 26May99
			{
				oldval = *adptr2;
				newval = *adptr;								//DAW 26May99

				if (newval != oldval)
				{
					AnimDeltaList[ChangeCnt].deltaoffset = newoffset - oldoffset;
					AnimDeltaList[ChangeCnt++].newbyte = newval;

					oldoffset = newoffset;
				}

				newoffset++;

				adptr2++;
				adptr++;										//DAW 26May99

//DeadCode DAW 26May99 				animdatasize--;
			}

			adptr2=temp;
			delete[]adptr2;
		}
	}

	return(ChangeCnt);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PatchAnimData
//Author		Robert Slater
//Date			Mon 6 Jul 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::PatchAnimData(itemptr	itm, int count)
{
	int	ChangeCnt = 0;

	SLong	animdatasize = GetAnimDataSize(itm->shape);
	if (itm->Anim != NULL)
	{
		animptr	adptr = itm->Anim;
		UByte	newval;
		UWord	newoffset = 0;

		ChangeCnt = 0;
		newoffset = 0;

		do
		{
			newoffset += AnimDeltaList[ChangeCnt].deltaoffset;
			newval = AnimDeltaList[ChangeCnt++].newbyte;// = newval;

			if (newoffset < animdatasize)
				adptr[newoffset] = newval;
			else
				_Error.EmitSysErr(__FILE__": Playback anim data wrong size!");

		}while (ChangeCnt < count);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LogCollision
//Author		Robert Slater
//Date			Tue 7 Jul 1998
//
//Description	
//
//Inputs		grpel    -1  not group    ----> log is 0
//						  0  element 1	  ----> log is 1
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::LogCollision(ItemPtr	itm, ItemPtr killer, ShapeNum shapehit, UByteP	instr_ptr, SLong grpel, int coltype, int colstrength, UByte send)//DAW 18Sep98
{
	if (ColLogCnt < MaxColLogs)
	{
		ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(shapehit);//A REAL CHANGE!! 02Dec98
		UByteP			inst_base = (UByteP )sdptr + sdptr->CollisionOffset;

		ColLog[ColLogCnt].theShooter = killer;		//RJS 11Mar99
		ColLog[ColLogCnt].item = itm;
		ColLog[ColLogCnt].shapehit = shapehit;
		ColLog[ColLogCnt].coloffset = instr_ptr - inst_base;
		ColLog[ColLogCnt].grpel = grpel + 1;// //RJS 16Sep98
		ColLog[ColLogCnt].coltype = coltype;
		ColLog[ColLogCnt].send=send;							//AMM 31Aug98
		ColLog[ColLogCnt++].colstrength = colstrength;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FixupColLog
//Author		Robert Slater
//Date			Tue 7 Jul 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::FixUpColLog()
{
	ShapeDescPtr	sdptr;
	UByteP			inst_col;
	int				index = 0;
	Bool			go=TRUE;
	UByteP			instr_ptr;
	Bool			oldcolon = CollisionOn;
	UWord			instruction;
	UByte			Hit_Byte;

	while (index < ColLogCnt)
	{
		sdptr = SHAPESTUFF.GetShapePtr((ShapeNum)ColLog[index].shapehit);//AMM 26Nov98
 
		instr_ptr = (UByteP )sdptr + sdptr->CollisionOffset;
		inst_col = instr_ptr + ColLog[index].coloffset;
		CollisionOn = FALSE;
		FixUpCollision = TRUE;
		CollisionCnt = 0;
		Hit_Byte = 0;

		while (go)
		{
			instruction = (UWord) *instr_ptr;
			instr_ptr ++;

			if ((instr_ptr == inst_col) || (instr_ptr > inst_col))
				break;

			(*InterpTable[instruction]) (instr_ptr);
		}

		//   |--- Hit_Byte ----|
		//    0000         0000
//DeadCode DAW 25Jun99 		// if ((Hit_Byte & 1) == 1)   then cast Hit Byte to 00 00000 0    (Hit Element) (Grp Element) (HitBit)
//DeadCode DAW 25Jun99 		//                            else case Hit Byte to 0000000  0	  (Hit Element) (Grp Element) (HitBit)
		// if ((Hit_Byte & 1) == 1)   then cast Hit Byte to 00 000000    (Hit Element) (Grp Element) (HitBit)
		//                            else case Hit Byte to 00000000	  (Hit Element) (Grp Element) (HitBit)
//DeadCode DAW 25Jun99 		if (ColLog[index].grpel == 0)
//DeadCode DAW 25Jun99 			Hit_Byte = (CollisionCnt << 1);
//DeadCode DAW 25Jun99 		else
//DeadCode DAW 25Jun99 		{
//DeadCode DAW 25Jun99 			// Can only have 4 hit boxes per group element
//DeadCode DAW 25Jun99 			Hit_Byte = CollisionCnt << 6;
//DeadCode DAW 25Jun99 			Hit_Byte |= (ColLog[index].grpel << 1);
//DeadCode DAW 25Jun99 			Hit_Byte += 1;		// Set hit bit for groups
//DeadCode DAW 25Jun99 		}
		if (ColLog[index].grpel == 0)							//AMM 24Jun99
			Hit_Byte = CollisionCnt;							//AMM 24Jun99
		else													//AMM 24Jun99
		{														//AMM 24Jun99
			// Can only have 4 hit boxes per group element		//AMM 24Jun99
 			Hit_Byte = CollisionCnt << 6;						//AMM 24Jun99
 			Hit_Byte |= ColLog[index].grpel;					//AMM 24Jun99
		}														//AMM 24Jun99

		ItemPtr	hitterscorer=Persons2::PlayerSeenAC;

		if (ColLog[index].send)									//AMM 31Aug98
		{

// pass in the hitter here as well.....RJS 11Mar99

			_DPlay.NewCollision2(ColLog[index].item->uniqueID.count,		//14BITS
								Hit_Byte,						//AMM 26Nov98
								ColLog[index].coltype,					//2 BITS
								ColLog[index].colstrength,		//6 bits
								ColLog[index].theShooter->uniqueID.count);		//RJS 11Mar99
//								hitterscorer->uniqueID.count);

			if (ColLog[index].send==2)
			{
// collision with another AC, send a kill launcher if its a comms AC

				if (ColLog[index].theShooter)
				{
					if (ColLog[index].theShooter->uniqueID.commsmove)
					{
// dont want to have a killer for these packets

						UByte temp=_DPlay.CommsKiller;
						_DPlay.CommsKiller=255;
						_DPlay.NewKillLauncher(ColLog[index].theShooter->uniqueID.count);
						_DPlay.CommsKiller=temp;
					}
				}
			}

//DeadCode AMM 18Mar99 			if (!_DPlay.Implemented)
//DeadCode AMM 18Mar99 			{
// if in replay can score now - no, wait till collision is processed!
//DeadCode AMM 18Mar99 			}
		}

		index++;
	}

	FixUpCollision = FALSE;
	CollisionOn = oldcolon;
	ColLogCnt = 0;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddToCollisionList
//Author		Robert Slater
//Date			Thu 17 Sep 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::AddToCollisionList(	SLong	uniqueid,
									SLong	element,
									SLong	hittype,
									SLong	hitstrength,
									UByte	pnum,
									bool	myscorer)
{
	ItemPtr	itm = (ItemPtr)Persons2::ConvertPtrUID((UniqueID)uniqueid);

	if (ColLogCnt < MaxColLogs)
	{
		SLong	grpel, hitel;
		ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(itm->shape);//AMM 24Jun99
		if (SHAPESTUFF.GetShapeScale(sdptr)==SHP_GRP)			//AMM 24Jun99
		{														//AMM 24Jun99
			grpel = element & 63;								//AMM 24Jun99
			hitel = (element >> 6) & 3;							//AMM 24Jun99
		}														//AMM 24Jun99
		else													//AMM 24Jun99
		{														//AMM 24Jun99
			grpel = 0;											//AMM 24Jun99
			hitel = element;									//AMM 24Jun99
		}														//AMM 24Jun99

//DeadCode DAW 25Jun99 		if ((element & 1)==1)  // Test hit bit
//DeadCode DAW 25Jun99 		{
//DeadCode DAW 25Jun99 			// 00 00000 0	(Hit element) (Grp element)
//DeadCode DAW 25Jun99 			grpel = (element >> 1) & 31;	
//DeadCode DAW 25Jun99 			hitel = (element >> 6) & 3;
//DeadCode DAW 25Jun99 		}
//DeadCode DAW 25Jun99 		else
//DeadCode DAW 25Jun99 		{
//DeadCode DAW 25Jun99 			// 0000000 0	(Hit element) (Grp element)
//DeadCode DAW 25Jun99 			grpel = 0;
//DeadCode DAW 25Jun99 			hitel = (element >> 1) & 127;
//DeadCode DAW 25Jun99 		}

//DeadCode AMM 08Apr99 		// hitter fudge!!
//DeadCode AMM 30Mar99 #pragma warnmsg("Macca!... Fix this comms hitter fudge!")		
//DeadCode AMM 08Apr99 
//DeadCode AMM 08Apr99 // filled in below if info is available
//DeadCode AMM 08Apr99 
//DeadCode AMM 08Apr99 		if (!_DPlay.Implemented || (_DPlay.Implemented && _DPlay.GameType>TEAMPLAY))
//DeadCode AMM 08Apr99 		{
//DeadCode AMM 08Apr99  			ColLog[ColLogCnt].theShooter = itm;		// needs real hitter.......
//DeadCode AMM 08Apr99 		}

		ColLog[ColLogCnt].send=0; //AMM27Nov98
		ColLog[ColLogCnt].item = itm;
		ColLog[ColLogCnt].coloffset = hitel;
		ColLog[ColLogCnt].grpel = grpel - 1;
		ColLog[ColLogCnt].coltype = hittype;
		ColLog[ColLogCnt].colstrength = hitstrength;			//AMM 08Apr99
		ColLog[ColLogCnt].theShooter=NULL; // gets filled in below if we know it//AMM 03Jun99
		ColLog[ColLogCnt].shapehit=0;//AMM 03Jun99
//DeadCode AMM 08Apr99 		ColLog[ColLogCnt++].colstrength = hitstrength;

		if (myscorer)
		{
//DeadCode AMM 08Apr99 			if (!_Replay.Playback)
			{
				ItemPtr hitterscorer;

				hitterscorer=_DPlay.GetHitterScorer(uniqueid,element,hittype,hitstrength,pnum);
				ColLog[ColLogCnt].theShooter=hitterscorer;	//AMM 08Apr99

//DeadCode AMM 08Apr99 				if (_Replay.Record)
//DeadCode AMM 08Apr99 				{
//DeadCode AMM 08Apr99 					itm=(ItemPtr)Persons2::ConvertPtrUID((UniqueID)uniqueid);
//DeadCode AMM 08Apr99 					ColLog[ColLogCnt].theShooter = itm;
//					itm->ScoreSimpleItemKilled(true,(AirStrucPtr)hitterscorer);
//DeadCode AMM 08Apr99 				}
//DeadCode AMM 08Apr99 				else
//DeadCode AMM 08Apr99 				{
//DeadCode AMM 08Apr99 					if (_DPlay.GameType>TEAMPLAY)
//DeadCode AMM 08Apr99 					{
//DeadCode AMM 08Apr99 	// comms...
//DeadCode AMM 08Apr99 // coop games only
//DeadCode AMM 08Apr99 						if (hitterscorer)
//DeadCode AMM 08Apr99 							_DPlay.NewScoreClaim(hitterscorer,(UniqueID)uniqueid);
//DeadCode AMM 08Apr99 					}
//DeadCode AMM 08Apr99 				}
			}
		}
// in playback we will never know who shooter was but score is not maintained
// in record all packets will have a hitterscorer so shooter will be set up OK
// in comms deathmatch or teamplay shooter is sender of packet
// in comms quickmissions or campaign if I am sender then hitterscorer will be 
// set up and packet sent, otherwise shooter is null and must wait for packet
// for score to be set

// done above
//DeadCode AMM 03Jun99 		if (_Replay.Playback)
//DeadCode AMM 03Jun99 			 ColLog[ColLogCnt].theShooter = NULL;	//ColLog[ColLogCnt].item;//DAW 01Jun99

//DeadCode AMM 29Apr99 		else
//DeadCode AMM 29Apr99 		{
//DeadCode AMM 29Apr99 // dont know who shooter is yet!
//DeadCode AMM 29Apr99 // in playback will never know
//DeadCode AMM 29Apr99 
//DeadCode AMM 29Apr99 			ColLog[ColLogCnt].theShooter=NULL;
//DeadCode AMM 29Apr99 		}

		ColLogCnt++;											//AMM 08Apr99

		CollisionPlayback();
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CollisionPlayback
//Author		Robert Slater
//Date			Tue 7 Jul 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::CollisionPlayback()
{
	if (ColLogCnt)
	{
		UByteP			instr_ptr;
		UWord			instruction;
		Obj3D			tmpobj3d;
		ShapeDescPtr	sdptr;
		int				index = 0;
		Bool			go=TRUE;
		Bool			oldcolon = CollisionOn;
		ItemPtr			itm;
		Bool			isDifferent;
		SWord			new_damage_GrpElmt;
		UWord			new_damage_Shape;
		Coords3D		colpos_impact;
		Coords3D		colpos_hititem;
		Coords3D		colpos_hitgrp;
		SLong			last_vdeltax, last_vdeltay, last_vdeltaz;//RJS 20May99
		SLong			vdeltax, vdeltay, vdeltaz;				//RJS 20May99
		SWord			sin_ang, cos_ang;						//RJS 20May99
		ANGLES			theHdg, thePitch;						//RJS 20May99
		SLong			theDist;
		SLong			dy,dh,dx,dz;							//RJS 20May99

		last_vdeltax = 0;
		last_vdeltay = 0;
		last_vdeltaz = 0;

		HitThisOffset = 0;
		DamageNow = TRUE;										
		CollisionCnt = 0;

		damage_Scale = 2;										

		while (index < ColLogCnt)
		{															//AMM 26Nov98
			itm = ColLog[index].item;								//AMM 26Nov98
																	//AMM 26Nov98
			new_damage_Shape = itm->shape;							//AMM 26Nov98
			new_damage_GrpElmt = ColLog[index].grpel;				//AMM 26Nov98
																	//AMM 26Nov98
 			sdptr = SHAPESTUFF.GetShapePtr(new_damage_Shape);		//AMM 26Nov98
																	//AMM 26Nov98
			damage_Sdptr = (UByteP) sdptr;							//AMM 26Nov98
			damage_AnimPtr = itm->Anim;							//DAW 23Apr99

			BoxCol::Col_Shooter = ColLog[index].theShooter;			//RJS 11Mar99

			colpos_hitgrp = itm->World;
			colpos_hititem = itm->World;
			colpos_impact = itm->World;

			if (new_damage_GrpElmt != -1)
			{
				UByteP	instr_ptr2 = (UByteP) damage_Sdptr + sdptr->liveshpref;
				UByte	groupel = -1;
				UByteP	Col_GroupPrev = NULL;
				UByteP	Col_GroupNext = NULL;
				animptr	Col_AnimPrevPtr;						//DAW 23Apr99
				animptr	Col_AnimNextPtr = damage_AnimPtr;		//DAW 23Apr99
				animptr	Col_TokenDepAnim;						//DAW 23Apr99
				SLong	tmpx,tmpy,tmpz;

				forever
				{
					instruction = *instr_ptr2;

					instr_ptr2++;

					if (instruction == dogroupno)
					{
						DOGROUP_PTR	gptr = (DOGROUP_PTR) instr_ptr2;
						
						new_damage_Shape = gptr->shapenum;
						tmpx = gptr->xoffset;
						tmpy = gptr->yoffset;
						tmpz = gptr->zoffset;
						
						groupel++;

						instr_ptr2 += sizeof(DOGROUP);	

						damage_AnimPtr = Col_AnimNextPtr;

						if (groupel == new_damage_GrpElmt)
						{
							sdptr = SHAPESTUFF.GetShapePtr(new_damage_Shape);

							Col_AnimNextPtr += GetElementAnimOffset((ShapeNum)new_damage_Shape);

//DeadCode RJS 30 Jun99							instruction = *((UByteP)instr_ptr2+1);
							instruction = *((UByteP)instr_ptr2);			//RJS 30Jun99
							if (instruction == dogroupno)
								Col_GroupNext = (UByteP)instr_ptr2+1;
							else
								Col_GroupNext = NULL;

							colpos_hitgrp.X = colpos_hititem.X + tmpx;
							colpos_hitgrp.Y = colpos_hititem.Y + tmpy;
							colpos_hitgrp.Z = colpos_hititem.Z + tmpz;

							colpos_impact = colpos_hitgrp;

							SetGroupDamage(new_damage_GrpElmt,Col_GroupPrev,Col_GroupNext,Col_AnimPrevPtr,Col_AnimNextPtr,Col_TokenDepAnim);//DAW 07Apr99
							break;
						}
						else
						{
							Col_GroupPrev = instr_ptr2;

							Col_AnimPrevPtr = Col_AnimNextPtr;
							Col_AnimNextPtr += GetElementAnimOffset((ShapeNum)new_damage_Shape);
						}
					}
					else
						break;
				}
			}

 			instr_ptr = (UByteP )sdptr + sdptr->CollisionOffset;

			CollisionOn = FALSE;
			CollisionCnt = 0;
			FixUpCollision = TRUE;
			isDifferent = FALSE;

			damage_ItemPtr = itm;				//RJS 26Aug98
			damage_GrpElmt = new_damage_GrpElmt;				//RJS 27Apr99
			damage_Shape = (ShapeNum)new_damage_Shape;					//RJS 27Apr99

			while (go)
			{
				instruction = (UWord) *instr_ptr;
				instr_ptr ++;

				if (CollisionCnt == ColLog[index].coloffset)
				{
					FixUpCollision = FALSE;
					CollisionCnt = -1;
					CollisionOn = TRUE;

					if (ColLog[index].colstrength == FORCE_SET)
					{
						damage_ItemState = (ColLog[index].coltype*BS_DEAD)/FORCE_LEVEL4;
						BoxCol::HitterStrength = 31;
						BoxCol::HitterDamageType = DMT_SHOCKWAVE;
						HitThisOffset = 1;
					}
					else
					{
						HitThisOffset = 0;
						BoxCol::HitterStrength = ColLog[index].colstrength;
						BoxCol::HitterDamageType = ColLog[index].coltype;
					}

					vdeltax = colpos_impact.X - View_Point->World.X;
					vdeltay = colpos_impact.Y - View_Point->World.Y;
					vdeltaz = colpos_impact.Z - View_Point->World.Z;

					if (	(vdeltax != last_vdeltax)
						||	(vdeltay != last_vdeltay)
						||	(vdeltaz != last_vdeltaz)	)
					{
						Math_Lib.Intercept(vdeltax,vdeltay,vdeltaz,theDist,theHdg,thePitch);
						theDist = (sdptr->Size << 4) + 50;

						Math_Lib.high_sin_cos(thePitch,sin_ang,cos_ang);

						dy = (sin_ang * theDist)/ANGLES_FRACT;
						dh = (cos_ang * theDist)/ANGLES_FRACT;

						Math_Lib.high_sin_cos(theHdg,sin_ang,cos_ang);

						dx = (sin_ang * dh)/ANGLES_FRACT;
						dz = (cos_ang * dh)/ANGLES_FRACT;
					}

					last_vdeltax = vdeltax;						//RJS 20May99
					last_vdeltay = vdeltay;						//RJS 20May99
					last_vdeltaz = vdeltaz;						//RJS 20May99

					BoxCol::colpos_impact.X = colpos_impact.X - dx;	//RJS 20May99
					BoxCol::colpos_impact.Y = colpos_impact.Y - dy;	//RJS 20May99
					BoxCol::colpos_impact.Z = colpos_impact.Z - dz;	//RJS 20May99

					BoxCol::colpos_hititem = colpos_hititem;				//RJS 20Apr99
					BoxCol::colpos_hitgrp = colpos_hitgrp;				//RJS 20Apr99
				}

				if (	((instruction == doretno) && CollisionOn)
					||	(instruction==doendno))
					break;

				(*InterpTable[instruction]) (instr_ptr);
			}

			index++;

			BoxCol::ProcessEffectQueue(itm);			//RJS 15Jan99
		}

		ColLogCnt = 0;
		CollisionOn = oldcolon;
//DeadCode AMM 03Jun99 		ColLogCnt = 0;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddToTree
//Author		Robert Slater
//Date			Wed 8 Jul 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::AddToTree(int	vertex)
{
	SphTreeTypeP	NewTree = &SphereTreeTable[vertex];
	SphTreeTypeP 	TreeRoot = SphereTree;
	Float			bodyz = newco[vertex].bodyz.f;

	NewTree->vertex = vertex;
	NewTree->left = NULL;
	NewTree->right = NULL;

	if (SphereTree == NULL)
		SphereTree = NewTree;
	else
	{
		while (TreeRoot)
		{
			if (bodyz <= newco[TreeRoot->vertex].bodyz.f)
			{
				if (TreeRoot->left == NULL)
				{
					TreeRoot->left = NewTree;
					break;
				}

				TreeRoot = TreeRoot->left;
			}
			else
			{
				if (TreeRoot->right == NULL)
				{
					TreeRoot->right = NewTree;
					break;
				}

				TreeRoot = TreeRoot->right;
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RecurseTree
//Author		Robert Slater
//Date			Thu 9 Jul 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::RecurseTree(SphTreeTypeP 	TreeRoot)
{
	while (TreeRoot)
	{
		RecurseTree(TreeRoot->right);

		SphereList[GlobSphereCnt++] = TreeRoot->vertex;

		TreeRoot = TreeRoot->left;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		EmptyTree
//Author		Robert Slater
//Date			Thu 9 Jul 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SLong	shape::EmptyTree()
{
	GlobSphereCnt = 0;
	RecurseTree(SphereTree);

	SphereTree = NULL;

	return(GlobSphereCnt);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetCloudFade
//Author		Robert Slater
//Date			Thu 16 Jul 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::SetCloudFade()
{
	if (OldWhiteFade != DoWhiteFade)
	{
		GREY3DTYPE	softfade;

		if (DrawnClouds)
		{
			if (doingHW3D)					
				current_screen->DoSetFade((Colour)26,DoWhiteFade,TDE_UNIFORM);
			else
			{
				softfade = (GREY3DTYPE) (DoWhiteFade>>2);

//DEAD				POLYGON.SetFadeData(_WHITEOUT);
//DEAD				POLYGON.SetFaded3DType(softfade);
			}
		}
		else
		{
			DoWhiteFade = 0;
			if (doingHW3D)							
				current_screen->DoSetFade((Colour)26,0,TDE_UNIFORM);
			else
			{
				softfade = (GREY3DTYPE) 0;

//DEAD				POLYGON.SetFadeData(_WHITEOUT);
//DEAD				POLYGON.SetFaded3DType(softfade);
			}
		}

		OldWhiteFade = DoWhiteFade;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitCloudFade
//Author		Robert Slater
//Date			Thu 16 Jul 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::InitCloudFade()
{
	DrawnClouds = FALSE;
	DoWhiteFade = 0;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetMuzzleInfo
//Author		Robert Slater
//Date			Thu 23 Jul 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
UWord	shape::GetMuzzleIndex(LnchrType	launcher)
{
	UWord	cnt = 0;
	UWord	retval = 0;

	while (launcherdata[cnt].lnchrtype != LT_CONTACT)		//RJS 25Jan99
	{
		if (launcherdata[cnt].lnchrtype == launcher)
		{
			retval = cnt;
			if (retval > MaxMuzzles)
				MaxMuzzles = retval;

			break;
		}

		cnt++;
	}

	return(retval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DirectWeaponLauncher
//Author		Dave Whiteside
//Date			Wed 29 Jul 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
WeapAnimData* shape::DirectWeaponLauncher(	itemptr	itm,
											UByte	index,
											UWord&	theShape,
											SLong&	xpos,
											SLong&	ypos,
											SLong&	zpos,
											UWord&	MuzzleVel,
											UWord&	MuzzleDelay,
											UByte&  ltype	)
{
	ShapeDescPtr		sdptr;
	DOLAUNCHER_PTR		thislaunch = NULL;
	animptr				animdataptr;
	UByteP				instr_ptr;
	ShapeNum			shape;
	WeapAnimData*		weapon=NULL;
	MoveGunAnimData*	aptr;
	UByte				thisscale = 0;
	SLong				gx, gy, gz;
	MyGroundVectorPtr	goffset = NULL;
	SLong				muzindex;								//DAW 29Jul98

	shape= itm->shape;

	animdataptr = itm->Anim;

	ltype = LT_BULLET;	//Default
	theShape = (UWord) BULLET;					//RJS 01Jul99

	aptr = (MoveGunAnimData*) animdataptr;
	sdptr = SHAPESTUFF.GetShapePtr(shape);

//	if (SHAPESTUFF.GetShapeScale(sdptr) == SHP_GRP)
//	{
//		SLong	tmp;
//
//		if (sdptr->Type.haslaunchers)
//		{
//			instr_ptr = (UByteP )sdptr + sdptr->liveshpref;
//			while	(GetGroupElement(instr_ptr,shape,gx,gy,gz))
//			{
//				sdptr = SHAPESTUFF.GetShapePtr(shape);
//				if (sdptr->LauncherDataSize && aptr->itemstate==ALIVE)//RJS 22Nov96
//				{
//					thislaunch = (DOLAUNCHER_PTR) GetLauncherPos(shape,0);
//					if ((thislaunch->lnchrtype & LT_MASK)!= LT_CONTACT)
//						if (ltype==-1||(thislaunch->lnchrtype & LT_MASK)==ltype)
//							if (index--==0)
//							{	//found my launcher
//								goffset=new MyGroundVector;			//RJS 21Nov96
//								goffset->gx=gx;
//								goffset->gy=gy;
//								goffset->gz=gz;
//								break;
//							}
//				}
//				aptr=(MoveGunAnimData*)((int)aptr+GetElementAnimOffset(shape));//RJS 20Nov97
//			}
//			if (index!=0xff)
//				return(NULL);
//			index=0;
//		}
//		else return(NULL);
//	}
	// now shape and sdptr points to correct element & so does aptr
	//
	//

	if ((index >= 0) && (index < aptr->nolaunchers))
	{
		switch(SHAPESTUFF.GetShapeScale(sdptr))
		{
			case SHP_1CM:
				thisscale = 0;
				break;												
			case SHP_4CM:
				thisscale = 2;										
				break;												
			case SHP_16CM:
				thisscale = 4;										
				break;
		}
		thislaunch = (DOLAUNCHER_PTR) GetLauncherPos(shape,index);

		if (thislaunch)
		{
			if (	(thislaunch->lnchrtype < LT_CONTACT)
				||	(thislaunch->lnchrtype > CT_DUMMY)	)
			{
 				if (index < 10)						
				{
					weapon = &aptr->weaponlaunchers[index];
					if (weapon)
					{
						ltype = weapon->LauncherType;

						muzindex = weapon->LaunchTime & 0x00FF;	//RDH 03Aug98
						if (muzindex > MaxMuzzles)						//RDH 03Aug98
							muzindex = 0;								//RDH 03Aug98
		
						MuzzleVel = launcherdata[muzindex].muzlvel;//DAW 29Jul98
						MuzzleDelay = launcherdata[muzindex].firingdelay;//DAW 29Jul98
						theShape = (UWord) launcherdata[muzindex].theShape;//RJS 01Jul99
					}
				}
				else
					_Error.EmitSysErr(__FILE__":Weapon launcher index out of range!");
			}
		}
	}

	LauncherToWorld(itm,(UByteP) thislaunch,thisscale,xpos,ypos,zpos,goffset);

	// Extract from Rob's new weapon array stuff...
//DeadCode DAW 29Jul98 	MuzzleVel = 9000;		//Shit fix
//DeadCode DAW 29Jul98 	MuzzleDelay = 5;		//Shit fix
//DEADCODE DAW 01/07/99 	theShape = (UWord) BULLET;		//shit fix

	if (goffset)
		delete goffset;

	return(weapon);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ResetAnimData_NewShape
//Author		Robert Slater
//Date			Fri 4 Sep 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	shape::ResetAnimData_NewShape(ItemPtr	itm,ShapeNum	newshape,UByte  weappack,bool sendPacket)
{
	ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(itm->shape);
	Bool	valid = FALSE;
	SLong	animdatasize;
	
	sdptr = SHAPESTUFF.GetShapePtr(newshape);

	if (itm!=Persons2::PlayerSeenAC)
		sendPacket=0;

	// Only do if anim datas for old shape and replacement shape are the same...
	SLong olddatasize = GetAnimDataSize(itm->shape);
	animdatasize = GetAnimDataSize(newshape);
	if (olddatasize == animdatasize)
	{
		if (sendPacket && (_Replay.Record || _DPlay.Implemented))	//RJS 21Apr99
		{
			//Send a packet instead...
			_DPlay.NewShapePacket(itm->uniqueID.count,newshape);
		}
		else if (sendPacket && _Replay.Playback)
		{
// playback wait for packet
		}
		else
		{
			animdatasize = GetAnimDataSize(newshape);
			UByteP		adptr = (UByteP) &itm->Anim[0];

			memset(adptr,0,animdatasize);

			itm->shape = newshape;

			AnimWeaponPack = weappack;								//AMM 08Apr99

			DefaultAnimData(itm,itm->Anim,TRUE);
		}

		valid = TRUE;
	}

	return(valid);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		KillGear
//Author		Robert Slater
//Date			Mon 7 Sep 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::KillGear(ItemPtr	itm)
{
	if (itm->Status.size == AIRSTRUCSIZE)
	{
		AirStrucPtr	ac = (AirStrucPtr) itm;
		ac->fly.pModel->SetGearAnimPos(ac,ANIM_GEAR_AUTO,TRUE);	//Drop gear regardless
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetGroupDamage
//Author		Robert Slater
//Date			Thu 17 Sep 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::SetGroupDamage(	SLong	element,
								UByteP	gp,
								UByteP	gn,
								animptr	&gpa,
								animptr	&gna,
								animptr &tkndp	)
{
	damage_GrpElmt = element;					
	damage_GrpAnimPrev = gpa;					
	damage_GrpAnimNext = gna;
//DeadCode DAW 30Jun99 	if (gpa != NULL)
		damage_GrpPrev = gp;
//DeadCode DAW 30Jun99 	else
//DeadCode DAW 30Jun99 		damage_GrpPrev = NULL;

//DeadCode DAW 30Jun99 	if (gna != NULL)
		damage_GrpNext = gn;
//DeadCode DAW 30Jun99 	else
//DeadCode DAW 30Jun99 		damage_GrpNext = NULL;

	damage_GrpTokenDep = tkndp;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FixUpGroupCol
//Author		Robert Slater
//Date			Thu 17 Sep 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::FixUpGroupCol()
{
//DeadCode DAW 30Jun99 	ShapeDescPtr	sdptr = (ShapeDescPtr) damage_Sdptr;
//DeadCode DAW 30Jun99 	UByteP			iptr = (UByteP) sdptr->liveshpref; 
//DeadCode DAW 30Jun99 	int				groupindex = 0;
//DeadCode DAW 30Jun99 	MinAnimData*	mad = (MinAnimData*) damage_AnimPtr;
//DeadCode DAW 30Jun99 	UByteP			PrevIptr;
//DeadCode DAW 30Jun99 	ShapeNum		newshape;
//DeadCode DAW 30Jun99 	SLong			ex,ey,ez;
//DeadCode DAW 30Jun99 	UByteP			Col_GroupPrev = NULL;
//DeadCode DAW 30Jun99 	UByteP			Col_GroupNext = NULL;
//DeadCode DAW 30Jun99 	animptr			Col_AnimPrevPtr;
//DeadCode DAW 30Jun99 	animptr			Col_AnimNextPtr = damage_AnimPtr;
//DeadCode DAW 30Jun99 	animptr			Col_TokenDepAnim;
//DeadCode DAW 30Jun99 
//DeadCode DAW 30Jun99 	while(GetGroupElement(iptr,newshape,ex,ey,ez,0,&PrevIptr))
//DeadCode DAW 30Jun99 	{
//DeadCode DAW 30Jun99 		Col_GroupNext = iptr + 1;
//DeadCode DAW 30Jun99 
//DeadCode DAW 30Jun99 		damage_AnimPtr = Col_AnimNextPtr;
//DeadCode DAW 30Jun99 		damage_Shape = newshape;													//RJS 16Nov98
//DeadCode DAW 30Jun99 
//DeadCode DAW 30Jun99 		Col_AnimNextPtr += GetElementAnimOffset(newshape);
//DeadCode DAW 30Jun99 		Col_AnimPrevPtr = Col_AnimNextPtr;						
//DeadCode DAW 30Jun99 		Col_GroupPrev = PrevIptr;
//DeadCode DAW 30Jun99 	
//DeadCode DAW 30Jun99 		if (groupindex != damage_GrpElmt)
//DeadCode DAW 30Jun99 			groupindex++;								
//DeadCode DAW 30Jun99 		else
//DeadCode DAW 30Jun99 			break;
//DeadCode DAW 30Jun99 	}
//DeadCode DAW 30Jun99 
//DeadCode DAW 30Jun99 	SetGroupDamage(damage_GrpElmt,Col_GroupPrev,Col_GroupNext,Col_AnimPrevPtr,Col_AnimNextPtr,Col_TokenDepAnim);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetDistScale
//Author		Robert Slater
//Date			Fri 6 Nov 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::SetDistScale()
{
	DistScale = _matrix.FoV * (Float(640)/Float(winmode_w));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ResetRader
//Author		Robert Slater
//Date			Fri 6 Nov 1998
//
//Description	Clear radar flags and generate view matrix view ac...
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::ResetRadar(AirStrucPtr	eye, SLong vx, SLong vy, SLong vz)
{
	FPMATRIX_PTR	matp = &radarMatrix;

	if (eye)
		_matrix.GenerateRadar(eye->hdg,eye->pitch,eye->roll,matp);

	viewer_x = vx;
	viewer_y = vy;
	viewer_z = vz;
	
	radarRange = RANGE_RADAR;
 	radarTmpItm = NULL;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetRadar
//Author		Robert Slater
//Date			Fri 6 Nov 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::SetRadar()
{
	if (Manual_Pilot.ControlledAC2)
	{
		//Do we have a new lock?
		if (RadarItemPtr != radarTmpItm)							//RJS 07Apr99
			radarTimer = 0;	//pause for 1 sec...				//RJS 07Apr99
	//		radarTimer = 100;	//pause for 1 sec...				//RJS 07Apr99

		RadarItemPtr = radarTmpItm;
		if (radarTmpItm)
		{
			if (radarTmpItm->Status.size == AIRSTRUCSIZE)
				((AirStrucPtr)radarTmpItm)->fly.inRadarSight = TRUE;//RJS 13May99

 			RequiredRange = radarRange;
			if (RequiredRange > 100000)								//RDH 13Apr99
				RequiredRange = 100000;								//RDH 13Apr99
																	//RDH 13Apr99
			if (RequiredRange < 20000)								//RDH 13Apr99
				RequiredRange = 20000;								//RDH 13Apr99
		}
		else
		{
			//if realistic radar, we can lock onto the ground...
			if (Three_Dee.groundlockOn)								//RJS 04Jun99
			{
				UWord thePitch = Manual_Pilot.ControlledAC2->pitch;
				if ((thePitch > ANGLES_240Deg) && (thePitch < ANGLES_300Deg))
				{
					//Ground lock!
					SLong	radarRange = Manual_Pilot.ControlledAC2->fly.pModel->GroundHeight;
					SLong	disang = thePitch - ANGLES_270Deg;
					ULong	disfiddle = (radarRange * 77)>>9;

					disang = (disang<0)?-disang:disang;

					disfiddle *= disang;
					disfiddle /= ANGLES_30Deg;

					radarRange += disfiddle;
				}

				RequiredRange = radarRange;							
				if (RequiredRange > 100000)							
					RequiredRange = 100000;							
																	
				if (RequiredRange < 20000)							
					RequiredRange = 20000;							
			}

			radarTimer = -1;										//RJS 07Apr99
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SampleTrailList
//Author		Robert Slater
//Date			Mon 23 Nov 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	shape::SampleTrailList()
{
	SLong			index;
	ReplaySmkStruc	replaysmk;
	SLong			smkindex;

	ULong reallist=0;

	if (MAX_VAPOURS>32)
		_Error.SayAndQuit("MAX_VAPOURS>32");

	for (index=1; index < MAX_VAPOURS; index++)
	{
		if (traillist[index].thelist || traillist[index].beendrawn)
		{
			reallist|=1<<index;
		}
	}

	if (!_Replay.StoreSmkIndexData(reallist))
		return FALSE;

	for (index=1; index < MAX_VAPOURS; index++)
	{
		if (traillist[index].thelist || traillist[index].beendrawn)
		{
			if (traillist[index].SmkDescPtr)
			{
				smkindex = ((UByteP)(traillist[index].SmkDescPtr) - (UByteP)&SmokeTrlList[0]);
				smkindex /= sizeof(SmokeType);
			}
			else
				smkindex = -1;

			replaysmk.lifetime = traillist[index].lifetime;
			replaysmk.lastwx = traillist[index].lastwx;
			replaysmk.lastwy = traillist[index].lastwy;
			replaysmk.lastwz = traillist[index].lastwz;
			replaysmk.nextlist= traillist[index].nextlist;
			replaysmk.beendrawn= traillist[index].beendrawn;
			replaysmk.cloudlaunched= traillist[index].cloudlaunched;
			replaysmk.LaunchCountdown= traillist[index].LaunchCountdown;
			replaysmk.SampleTime= traillist[index].SampleTime;
			replaysmk.smkindex = smkindex;
			replaysmk.nopoints = traillist[index].nopoints;	//RJS 17Feb99
			replaysmk.transient = traillist[index].transient;	//RJS 18Feb99
			replaysmk.currTime = traillist[index].currTime;	//RJS 16Jun99
							  	
			if (!_Replay.StoreSmkData(&replaysmk,(UByteP)traillist[index].thelist))//RJS 17Feb99
				return FALSE;

		}
	}

	//Now sample static trails...
	//Header...
	UByte	smltrailtot = Trans_Obj.StaticTrailCnt;
	if (!_Replay.ReplayWrite(&smltrailtot,sizeof(smltrailtot)))	//RJS 18Feb99
		return FALSE;

	//Data...
	ReplaySmlSmkStruc	replaysmlsmk;
	SmokeTrailAnimData*	adptr;
	for (index = 0; index < MaxTrails; index++)						//RJS 08Apr99
	{
		if (Trans_Obj.StaticTrailList[index].item)				//RJS 13May99
		{
			adptr = (SmokeTrailAnimData*) Trans_Obj.StaticTrailList[index].item->Anim;//RJS 13May99

			if (Trans_Obj.StaticTrailList[index].item->Launcher)//RJS 13May99
			{
				replaysmlsmk.uniqueid = Trans_Obj.StaticTrailList[index].item->Launcher->uniqueID.count;//RJS 13May99

#ifndef NDEBUG
				if (!(Persons2::ConvertPtrUID((UniqueID)(replaysmlsmk.uniqueid))))
					INT3;
#endif
			}
			else
			{
				//The trail's launcher was also a transient,
				//so set up uniqueid to be YOU, to keep things clean...
				replaysmlsmk.uniqueid = Persons2::PlayerSeenAC->uniqueID.count;		//RJS 21Apr99
			}

			replaysmlsmk.lifetime = adptr->lifetime;
			replaysmlsmk.nopoints = adptr->nopoints;
			replaysmlsmk.smkindex = adptr->SmkDescIndex;
			replaysmlsmk.currTime = adptr->currTime;				//RJS 16Jun99

			if (!_Replay.StoreSmlSmkData(&replaysmlsmk,(UByteP)adptr->thelist))
				return FALSE;
		}
	}

	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetSmokeTrailList
//Author		Robert Slater
//Date			Mon 23 Nov 1998
//
//Description	
//
//Inputs		dummy flag
//				... if dummy is true, we want to skip through all the data,
//					but do nothing with it.
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	shape::GetSmokeTrailList(Bool dummy)
{
	ULong bigindex;
	ReplaySmkStruc	replaysmk;
	SLong index;
	UByteP	listptr;											//RJS 18Feb99

	if (!_Replay.LoadSmkIndexData(bigindex))
		return FALSE;

	for (index=1; index < MAX_VAPOURS; index++)
	{
		if (bigindex&(1<<index))								//RJS 17Feb99
		{
// load smoke list
			listptr = NULL;										//RJS 18Feb99
			if (!_Replay.LoadSmkData(&replaysmk,dummy,listptr))//RJS 18Feb99
				return FALSE;

			if (!dummy)
			{
				SLong	smkindex = replaysmk.smkindex;

				traillist[index].lifetime =	replaysmk.lifetime;
				traillist[index].lastwx	= replaysmk.lastwx;
				traillist[index].lastwy	= replaysmk.lastwy;
				traillist[index].lastwz	= replaysmk.lastwz;
				traillist[index].nextlist = replaysmk.nextlist;
				traillist[index].beendrawn = replaysmk.beendrawn;
				traillist[index].cloudlaunched = (Bool)replaysmk.cloudlaunched;
				traillist[index].LaunchCountdown = replaysmk.LaunchCountdown;
				traillist[index].SampleTime	= replaysmk.SampleTime;
				if (smkindex > -1)
					traillist[index].SmkDescPtr = (UByteP)&SmokeTrlList[smkindex];
				else
					traillist[index].SmkDescPtr = NULL;

				traillist[index].thelist = (Coords3DList*)listptr;
				traillist[index].nopoints = replaysmk.nopoints;
				traillist[index].nextlist = 0;
				traillist[index].transient = replaysmk.transient;
				traillist[index].currTime = replaysmk.currTime;			//RJS 16Jun99
			}
		}
		else
		{
			if (!dummy)
			{
// null smoke list

			}
		}
	}

	UByte	smltrailtot;
//DeadCode AMM 20Apr99 	if (!_Replay.ReplayRead(&smltrailtot,sizeof(smltrailtot)))
	if (!_Replay.SmokeRead(&smltrailtot,sizeof(smltrailtot)))
		return FALSE;

	ReplaySmlSmkStruc	replaysmlsmk;
	Coords3D	centrepos;
	for (index = 0; index < smltrailtot; index++)
	{
		listptr = NULL;								
		if (_Replay.LoadSmlSmkData(&replaysmlsmk,dummy,listptr,centrepos))
		{
			if (!dummy)
				Trans_Obj.LaunchReplayTrail(centrepos,(UByteP)&replaysmlsmk,listptr);
		}
		else
			return FALSE;
	}

	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DeleteAllSmokeTrails
//Author		Andy McMaster
//Date			Wed 4 Nov 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::DeleteAllSmokeTrails()
{
	SLong	i;

	//Just in case...											//DAW 21Jun99
	GenerateProbeTrails();										//DAW 21Jun99

	// First kill orphaned trail points...
	for (i=0; i < REAL_MAX_VAPOURS; i++)
	{
//		Coords3DList* apoint = traillist[i].FakePointPtr;
//		Coords3DList* dpoint;
// 
//		while (apoint)
//		{						
//			dpoint = apoint;
//			apoint = apoint->next;
//
//			delete dpoint;
//		}

		traillist[i].FakePointPtr->Wipe();
		traillist[i].FakePointPtr = NULL;
	}

	VapDeadCnt = 0;
	for (i=0; i < MAX_VAPOURS; i++)
		KillVapourStream(i);

	newprobecnt = 0;			//RJS 26Mar99
	Trans_Obj.CleanUpTrailList();									//RJS 18Feb99
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		imapspherespin
//Author		Robert Slater
//Date			Mon 23 Nov 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::imapspherespin(	UWord vertex,
							UWord 	radius,	
							ImageMapNumber imapno,
							SWord	minx, SWord	miny,
							SWord	maxx, SWord	maxy,
							SWord	angle	)
{
 	DoPointStruc dopoint0,dopoint1,dopoint2,dopoint3;
	Float	scaleradius = radius;

	dopoint0 = dopoint1 = dopoint2 = dopoint3 = newco[vertex];

	if (dopoint0.bodyz.f > 10.0)			
	{												
		if (ClipSphereSpin(dopoint0,dopoint1,dopoint2,dopoint3,scaleradius,angle)==FALSE)
		{
			_matrix.body2screen(dopoint0);						  
			_matrix.body2screen(dopoint1);						  
//			if ((dopoint1.screenx.f - dopoint0.screenx.f) > 2.0)
			{
//DEAD				if (object_obj3d->Shape!=SUN)
//DEAD					POLYGON.SetPixelWidth(1<<Save_Data.pixelsize);

				POLYGON.createpoly(imapno);

				POLYGON.createvert(dopoint0,minx,miny);
				POLYGON.createvert(dopoint1,maxx,miny);
				POLYGON.createvert(dopoint2,maxx,maxy);
				POLYGON.createvert(dopoint3,minx,maxy);

				POLYGON.drawpoly();

//DEAD				POLYGON.SetPixelWidth(1);
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DrawDirtTrail
//Author		Mark Shaw
//Date			Thu 10 Dec 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::DrawDirtTrail(	SWord		index,
								UByteP		smkinfo,
								ULong		LifeTime,
								Bool		valid	)
{
	if (index)
	{
		if (index < 0)											
			index = -index;

		if (index > MAX_VAPOURS)			
			_Error.EmitSysErr(__FILE__":(DOSMKTRAIL)    Shouldn't be this : %d\n",index);

		TrailRecordPtr	TrailPtr = &traillist[index];			
																
		if (smkinfo)											
			TrailPtr->SmkDescPtr = smkinfo;						
		else													
		{
			smkinfo = TrailPtr->SmkDescPtr;						
			LifeTime = TrailPtr->lifetime;						
		}

		SmokeTypeP		ptr = (SmokeTypeP) smkinfo;
		Coords3DList*	apoint;
		Coords3DList*	*lastpointptr;						
		Coords3DList*	nextpoint;							
		Coords3DList*	lastpoint;							
		SLong			nocyls = 0;
		SLong			lifegone, lifeleft;				
		SLong			distz,lastdistz;
		SWord			grow2time = ptr->Growth;
		UWord			startradius = ptr->Radius;
		SWord			radius;
		SWord			radiusinc;
 		SByte			frameno;
		SLong			degrade;
		ShapeNum		trailshape = (ShapeNum) ptr->Shape;
		SLong			degcnt;
		UByteP			lastdrawnobj = NULL;
		UByteP			thisdrawnobj = NULL;
		UWord			failedcnt = 0;
		VapAnimDat		AnimDat;
		VapAnimDatPtr	AnimDataPtr;
		SLong			timesincebirth;
		SLong			totcount = 0;
		SWord			hdist;
		SLong			reallife;

 		lastpointptr = &TrailPtr->thelist;
		degrade = ptr->DegradeDist << 4;
		distz = 0;
		degcnt = 0;

		apoint = lastpoint = TrailPtr->thelist;			
 		while (apoint)
 		{
 			nextpoint = apoint->next;
			lifeleft = reallife = apoint->lifeleft;				
 			if (!Three_Dee.IsPaused())							
 			{
				if (lifeleft == 0)
 				{
					// Add to dead list...
					apoint->next = TrailPtr->FakePointPtr;
					TrailPtr->FakePointPtr = apoint;
 
 					TrailPtr->nopoints--;
 					*lastpointptr = nextpoint;
 				}
				else
				{
					reallife -= Timer_Code.FRAMETIME;
					if (reallife < 0)
						reallife = 0;

					apoint->lifeleft = reallife;				//RJS 14Apr98
				}
			}

 			if (lifeleft)
 			{
				lifegone = apoint->LifeTime - lifeleft;
				radius = startradius + ((startradius*lifegone)/grow2time);

				apoint->radius = radius;
 				if (!degcnt || !nextpoint)
 				{
					if (lifegone > ptr->FadeTime)
					{
						if (ptr->FadeShape)
							trailshape = ptr->FadeShape;
					}

					distz = Three_Dee.AddVapourObject(	trailshape,
														(UByteP)apoint,
														lastdrawnobj,
														thisdrawnobj,
														failedcnt);

					if (thisdrawnobj)
					{
						AnimDat.depth = ptr->Depth;		//initial fade depth...
						AnimDat.drawit = CalcDirtDeltas( apoint,
														 lastpoint,
														 radius,
 														 apoint->xdelta,apoint->ydelta);//RJS 15Apr98

						AnimDataPtr = (VapAnimDatPtr) &((Obj3DPtr)thisdrawnobj)->AngR;
						*AnimDataPtr = AnimDat;

						lastdrawnobj = thisdrawnobj;
						nocyls++;
					}
					else
						failedcnt++;

					degcnt = distz / degrade;
				}												
				else											
					degcnt--;									

 				lastpointptr = &apoint->next;
 				lastpoint = apoint;

				totcount++;
 			}
 
 			apoint = nextpoint;
 		}

		apoint = TrailPtr->thelist;
		if (apoint && !valid)
		{
			TrailPtr->thelist = apoint->next;

			apoint->next = TrailPtr->FakePointPtr;
			TrailPtr->FakePointPtr = apoint;					

			TrailPtr->nopoints--;
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CalcDirtDeltas
//Author		Mark Shaw
//Date			Thu 10 Dec 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
UWord	shape::CalcDirtDeltas(	Coords3DList*	apoint,
								Coords3DList*	lastpoint,
								UWord	radius,
								SWord	&xoff, SWord &yoff)
{
	DoPointStruc dopoint0,dopoint2;
	SLong		valid = 0;
	SWord		angleofcyl = 0;
	SWord		sin_ang, cos_ang;
	SLong		adjacent,opposite;

	xoff = 0;
	yoff = 0;

	adjacent = apoint->trailpoint.gx - lastpoint->trailpoint.gx;
	opposite = apoint->trailpoint.gz - lastpoint->trailpoint.gz;

	if (opposite || adjacent)
	{
		Float	res = 10430.37835047*FPATan(adjacent,opposite);
		angleofcyl = SWord(res);
 		angleofcyl -= ANGLES_90Deg;

		Math_Lib.high_sin_cos((Angles) angleofcyl,sin_ang,cos_ang);		//PD 13Nov97
		xoff = (sin_ang * radius) / ANGLES_FRACT;				
		yoff = (cos_ang * radius) / ANGLES_FRACT;

		valid = 1;
	}

	return(valid);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LogFuelDamage
//Author		Robert Slater
//Date			Mon 18 Jan 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::LogFuelDamage(	ItemPtr		itm,
								UByteP		weapon,
								ItemPtr		hitter	)
{
	WeapAnimData*	weapptr = (WeapAnimData*) weapon;
	if (	(weapptr->LauncherType == LT_FUEL)
		||	(weapptr->LauncherType == LT_INTFUEL)	)
	{
		if (itm->Status.size == AIRSTRUCSIZE)
		{
			AirStrucPtr			ac = (AirStrucPtr) itm;
			AircraftAnimData*	adptr = (AircraftAnimData*) ac->Anim;
			SLong				weapelement = weapon - (UByteP)&adptr->weaponlaunchers[0];
			ShapeDescPtr		sdptr = SHAPESTUFF.GetShapePtr(itm->shape);
			UByteP				instr_ptr;
			UWord				instruction;
			SLong				instsize = sizeof(DOLAUNCHER) + 1;

			weapelement /= sizeof(WeapAnimData);

			// Find relative launcher offset in shape...
			// Calc whether internal, external fuel hit,
			// Damage level and which wing....

			if (sdptr->LauncherDataSize)
			{
				instr_ptr = (UByteP )sdptr + sdptr->LauncherDataSize + (instsize * weapelement);

				instruction = (UWord) *instr_ptr;
				instr_ptr++;

				if (instruction == dolauncherno)
				{
					DOLAUNCHER_PTR	ptr = (DOLAUNCHER_PTR) instr_ptr;
					weap_info		*WIPtr;
					SLong			dx = ptr->posx;
					SLong			leakval = (weapptr->SubDamage * 500000)/31;

					if (dx > 40)
						WIPtr = &ac->weap.right;
					else
					{
						if (dx < -40)
							WIPtr = &ac->weap.left;
						else
							WIPtr = &ac->weap.centre;
					}

					if (ac->weap.FuelDumped || ac->weap.UseIntFuel)
					{
						// Can't be external leak...
						if (!weapptr->stationshape)
							WIPtr->int_fuel_leakage = leakval;
					}
					else
					{
						if (!weapptr->stationshape)
							WIPtr->int_fuel_leakage = leakval;
						else
							WIPtr->ext_fuel_leakage = leakval;
					}
				}
			}
		}

		// Record radio message...


	}
	else
	{
		// smoke trail...


	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProbeStaticTrail
//Author		Robert Slater
//Date			Thu 21 Jan 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::ProbeStaticTrail(UByteP	rsdptr, itemptr	itm,animptr&	aptr)
{
	ShapeDescPtr		sdptr = (ShapeDescPtr) rsdptr;
	int					wpnum, index, oldindex;
	WeapAnimData*		weapon;
	SmokeTrailAnimData*	adptr = (SmokeTrailAnimData*) aptr;
	SmokeTypeP			smkptr = NULL;
	UWord				lifetime=0;
	SByte				TType;
	Bool				validpoint = TRUE;
	UByte				istransient = 0;

	pTrailItm = itm;
//DeadCode RJS 17Feb99 	if (pTrailItm->Status.size == TRANSIENTSIZE)			//RJS 15Feb99
//DeadCode RJS 17Feb99 		istransient = 1;									//RJS 15Feb99

	weapon = (WeapAnimData*) &adptr->weaponlaunchers[0];
	if (adptr->nopoints == 0)
	{
		smkptr = NULL;

		DrawSmokeTrail((SWord)weapon->hdg,(UByteP)smkptr,lifetime,0,0,0,TRUE);
	}
	else
	{
		TrailRecordPtr	TrailPtr = &traillist[MAX_VAPOURS];
		SWord			index;

		// if the list is empty, draw nothing...
		if (adptr->thelist)
		{
			TrailPtr->thelist = (Coords3DList*) adptr->thelist;
			TrailPtr->nopoints = adptr->nopoints;
			TrailPtr->lifetime = adptr->lifetime;
			TrailPtr->SmkDescPtr = (UByteP) &SmokeTrlList[adptr->SmkDescIndex];
 			TrailPtr->transient = 1;							//RJS 17Feb99
			TrailPtr->beendrawn = 1;			//RJS 15Feb99
			TrailPtr->currTime = adptr->currTime;				//RJS 16Jun99

			index = MAX_VAPOURS;

			DrawSmokeTrail(index,NULL,TrailPtr->lifetime,0,0,0,TRUE);

			adptr->thelist = (ULong)TrailPtr->thelist;
			adptr->currTime = TrailPtr->currTime;				//RJS 17Jun99
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ReloadMassAndDrag
//Author		Robert Slater
//Date			Mon 25 Jan 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::ReloadMassAndDrag(AirStrucPtr	ac)
{
	if (ac->Status.size == AirStrucSize)
	{
		weap_info		*WIPtrL = &ac->weap.left;
		weap_info		*WIPtrR = &ac->weap.right;
		weap_info		*WIPtrC = &ac->weap.centre;

		WIPtrL->mass = WIPtrL->reloadmass;						//RJS 18Jun99
		WIPtrL->drag = WIPtrL->reloaddrag;						//RJS 18Jun99

		WIPtrR->mass = WIPtrR->reloadmass;						//RJS 18Jun99
		WIPtrR->drag = WIPtrR->reloaddrag;						//RJS 18Jun99

		WIPtrC->mass = WIPtrC->reloadmass;						//RJS 18Jun99
		WIPtrC->drag = WIPtrC->reloaddrag;						//RJS 18Jun99

		//At the mo', tip tanks are special cases...
		if (!ac->weap.FuelDumped)								//RJS 18Jun99
		{
			WIPtrL->mass += 4535970;	//100lbs				//RJS 18Jun99
			WIPtrL->drag += 1250;								//RJS 18Jun99

			WIPtrR->mass += 4535970;	//100lbs				//RJS 18Jun99
			WIPtrR->drag += 1250;								//RJS 18Jun99
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetGrpTokenVisibility
//Author		Robert Slater
//Date			Fri 12 Feb 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::SetGrpTokenVisibility(UByteP	instr_ptr, animptr& astart, animptr& adptr)
{
	MinAnimData*	mad = (MinAnimData*) adptr;
	DOGROUP_PTR		ptr = (DOGROUP_PTR) instr_ptr;

	if (ptr->tokenflag)
	{
		if (ptr->tokenflag < GRP_TKN_VIS)
			mad->IsInvisible = 1;
		else
		{
			if ((ptr->tokenflag == GRP_TKN_VIS_DEP) && ptr->tokendepanim)
			{
				MinAnimData*	mad2 = (MinAnimData*) &astart[ptr->tokendepanim-1];
				if (mad->itemstate > BS_DAMLV2)
					mad2->IsInvisible = 0;
				else
					mad2->IsInvisible = 1;
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetGroupElementToken
//Author		Robert Slater
//Date			Fri 12 Feb 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SLong shape::GetGroupElementToken(	UByte *&instr_ptr,
									ShapeNum& shape,
									SLong& x, SLong& y, SLong& z,
									SLong range,
									UByteP	*PrevIptr,
									SWordP	heading,
									ULong&	animdepoff,
									UByteP&	nextgrpptr
									)
{
	SWord	inst;
	SLong	priority;											//RJS 14Nov96

	inst = (SWord )*instr_ptr;
	instr_ptr ++;

	nextgrpptr = NULL;
	if(inst!=dogroupno)
		return(0);

	DOGROUP_PTR temp = (DOGROUP_PTR)instr_ptr;

	shape = (ShapeNum )temp->shapenum;

	x = temp->xoffset;
	y = temp->yoffset;
	z = temp->zoffset;
	priority = temp->element_number;							//RJS 27Feb98
	if (PrevIptr)
		*PrevIptr = (UByteP)temp;
	if (heading)
		*heading = temp->angle;

	animdepoff = temp->tokendepanim;

	temp++;

	instr_ptr = (UByte *)temp;
	if (*instr_ptr == dogroupno)								//RJS 30Jun99
		nextgrpptr = instr_ptr+1;								//RJS 30Jun99

	return(priority);
}

void	shape::InitGlobalItem()
{
	globinitairitem = NULL;
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NavigationLightsActive
//Author		Dave Whiteside
//Date			Wed 17 Feb 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::NavigationLightsActive(ItemPtr itm,Bool haveon)
{
	if (itm->Status.size == AIRSTRUCSIZE)
	{
		if (itm==Persons2::PlayerGhostAC)
			itm=Persons2::PlayerSeenAC;

		AircraftAnimData*	adptr = (AircraftAnimData*) itm->Anim;
		if (adptr->lighttoggle)
		{
			//Switch off...
			if (!haveon)
			{
				adptr->lighttoggle = 0;
				adptr->aclightclock1 = 0;
				adptr->aclightclock2 = 0;
			}
		}
		else
		{
			//Switch on...
			if (haveon)
			{
				adptr->lighttoggle = 1;
				adptr->aclightclock1 = Timer_Code.FRAMETIME;
				adptr->aclightclock2 = Timer_Code.FRAMETIME;
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BombBaysActive
//Author		Dave Whiteside
//Date			Wed 17 Feb 1999
//
//Description	Works on similar principle as undercarriage anim.
//
//				... this means it hogs 'animtoggle',
//				which means an ac with bombbays cannot have an
//				undercarriage lowering/raising anim!
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::ActivateBombBays(ItemPtr itm)
{
	if (itm->Status.size == AIRSTRUCSIZE)
	{
		AircraftAnimData*	adptr = (AircraftAnimData*) itm->Anim;
		if (adptr->animtoggle)									
			adptr->animtoggle = -adptr->animtoggle;				
		else													
			adptr->animtoggle = 1;	
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AmISmoking
//Author		Robert Slater
//Date			Thu 18 Feb 1999
//
//Description	Checks to see if ac has contrail...
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	AirStruc::AmISmoking()
{
	AircraftAnimData*	adptr = (AircraftAnimData*) Anim;
	SLong				weapcnt = adptr->nolaunchers;
	SLong				index;
	WeapAnimData*		weapon;
	Bool				retval = FALSE;

	for (index=0; index < weapcnt; index++)
	{
		weapon = (WeapAnimData*) &adptr->weaponlaunchers[index];
		if (weapon)
		{
			if (weapon->LauncherType == LT_ENGINE)	//nowt wrong, exit
				break;
			else
			{
				if (weapon->LauncherType==LT_CONTRAIL)
				{
					retval = TRUE;
					break;
				}
			}
		}
	}

	return (retval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UpdateReplayVapourCoords
//Author		Robert Slater
//Date			Wed 21 Apr 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::UpdateReplayVapourCoords(UByteP	rsdptr, itemptr	itm,animptr&	aptr)
{
	ShapeDescPtr		sdptr = (ShapeDescPtr) rsdptr;			//RJS 02Dec97
	int					wpnum, index, oldindex;
	WeapAnimData*		weapon;
	MoveGunAnimData*	adptr = (MoveGunAnimData*) aptr;		//RJS 21Apr99
	SLong				wx = itm->World.X;
	SLong				wy = itm->World.Y;
	SLong				wz = itm->World.Z;
	int					weapcnt = 1;
	SWord				animsize = sdptr->AnimDataSize;
	UByte				instsize = sizeof(DOLAUNCHER) + 1;
	DOLAUNCHER_PTR		lptr;
	UByteP				instr_ptr;
	UByteP				base_ptr;
	UWord				instruction;
	SmokeTypeP			smkptr = NULL;
	UWord				lifetime;
	ULong				reallifetime;
	SByte				TType;
	Bool				validpoint = TRUE;						//RJS 30Nov98
	SLong				driftx,drifty,driftz;					//RJS 10Mar98
	Bool				justlanded=FALSE;								//RJS 11Mar98
	UByte				weaplaunchertype;
	SWord				theHdg,thePitch,theRoll;

	switch (SHAPESTUFF.GetShapeScale(sdptr))				
 	{														
 		case SHP_1CM:										
 			shapescale = 0;									
 			break;											
 		case SHP_4CM:										
 			shapescale = 2;									
 			break;											
 		case SHP_16CM:										
 			shapescale = 4;									
 			break;											
 	}

	if (itm->Status.size >= ROTATEDSIZE)
	{
		theHdg = ((RotItemPtr)itm)->hdg;
		thePitch = ((RotItemPtr)itm)->pitch;
		theRoll = ((RotItemPtr)itm)->roll;
	}
	else
	{
		theHdg = thePitch = theRoll = 0;
	}

	pTrailItm = itm;//RJS 02Sep98
	weapcnt = adptr->nolaunchers;								//RJS 09Apr98

//DeadCode RJS 18Feb99 	if (itm == shititem)
//DeadCode RJS 18Feb99 	{
//DeadCode RJS 18Feb99 		int	fuck;
//DeadCode RJS 18Feb99 		fuck = 1;
//DeadCode RJS 18Feb99 	}

	Math_Lib.high_sin_cos((ANGLES )((mobileitem*)itm)->hdg,v_sin_ang,v_cos_ang);

	base_ptr = (UByteP )sdptr + sdptr->LauncherDataSize;

	for (wpnum = 0; wpnum < weapcnt; wpnum++)
	{
		oldindex = 0;
		weapon = (WeapAnimData*) &adptr->weaponlaunchers[wpnum];
		if (weapon)
		{
			instr_ptr = base_ptr + (instsize * wpnum);
			instr_ptr++;

			lptr = (DOLAUNCHER_PTR) instr_ptr;
			if (	!lptr->damageflag
				|| (aptr[lptr->damageflag] < lptr->damthresh)	)
			{
				TType = lptr->trailtype;
				if (TType < 0)
				{
					if (TType == -1)
					{
						if (weapon->LauncherType == LT_FUEL)
						{
							TType = TRAIL_VAPOUR;
							smkptr = (SmokeTypeP) &SmokeTrlList[TRAIL_VAPOUR];
							lifetime = smkptr->LifeTime;

							weaplaunchertype = weapon->LauncherType;//MS 30Nov98
						}
					}
					else
					{
						// Generic one for engines...
						if (lptr->lnchrtype == LT_ENGINE)		//MS 30Nov98
						{
							UByte	dolaunch = LT_ENGINE;

							if (itm->Status.size == AirStrucSize)				//RJS 20Jan99
							{
								AirStrucPtr	acptr = (AirStrucPtr) itm;
								SLong	rpm = acptr->fly.pModel->Inst.Rpm1;
								SLong	mph = acptr->fly.pModel->Inst.ActualSpeed;

								if (aptr[lptr->damageflag] < BS_DAMLV2)
								{
									dolaunch = LT_CONTRAIL;
									TType = TRAIL_CONTRAIL;
									smkptr = (SmokeTypeP) &SmokeTrlList[TType];
									lifetime = smkptr->LifeTime;

									if (weapon->LauncherType != LT_CONTRAIL)
									{
										if (	(object_obj3d->Shape == F86)
											&&	(acptr->fly.thrustpercent > 33))
										{
											if (!MMC.Sky.Contrails((AirStrucPtr)itm, reallifetime))
											{
								 				dolaunch = LT_FUEL;
												if (rpm > 7000)
												{
													TType = TRAIL_EXHAUSTDIRTY;
													smkptr = (SmokeTypeP) &SmokeTrlList[TType];
													lifetime = smkptr->LifeTime;
												}
												else
												{
													TType = TRAIL_EXHAUST;
													smkptr = (SmokeTypeP) &SmokeTrlList[TType];
													lifetime = smkptr->LifeTime;
												}
											}
										}
									}
								}
								else
								{
									dolaunch = LT_FUEL;
									TType = TRAIL_ENGINEPLUME;
									smkptr = (SmokeTypeP) &SmokeTrlList[TType];
									lifetime = smkptr->LifeTime;
								}
							
								index = weapon->hdg;
								if (index > 0)
								{
									if (traillist[index].SmkDescPtr != (UByteP)smkptr)
									{
										SHAPE.DetatchVapourStream(index,LIFETIME_VAPOUR);
										weapon->hdg = 0;
									}
									weapon->LauncherType = LT_ENGINE;
								}
								else
									weapon->LauncherType = LT_ENGINE;

								if (weapon->LauncherType != dolaunch)
								{
//DeadCode AMM 30Mar99 									weapon->LauncherType = dolaunch;
									if (dolaunch != LT_CONTRAIL)
									{
										weapon->LauncherType = dolaunch;//AMM 30Mar99
										oldindex = Trans_Obj.LaunchVapourStream((UByteP)weapon,itm->shape);//RJS 09Apr98
//DeadCode AMM 30Mar99 										weapon->pitch = -1;
									}
									weapon->pitch = -1;			//AMM 30Mar99
								}
							}

							weaplaunchertype = dolaunch;
						}
						else
						{
							// This is a generic, inherited trail...
							// ... make sure we sample no extra points!

							smkptr = NULL;
							weaplaunchertype = LT_CONTACT;
						}
					}											//MS 30Nov98
				}
				else
				{
					smkptr = (SmokeTypeP) &SmokeTrlList[TType];	//RJS 09Apr98
					lifetime = smkptr->LifeTime;

					weaplaunchertype = weapon->LauncherType;	//MS 30Nov98
				}

				if (TType != -1)
				{
					// min sample distance is 1024 cm per frame, which is 256m/s
					SLong	mindist = (51200 * Timer_Code.FRAMETIME)/100;
					SLong	distscale;

					validpoint = TRUE;
					driftx = 0;										//RJS 10Mar98
					drifty = 0;										//RJS 10Mar98
					driftz = 0;										//RJS 10Mar98

					switch (weaplaunchertype)					//RJS 29Nov98
					{
						case LT_CONTRAIL:
						{
							if (MMC.Sky.Contrails((AirStrucPtr) itm, reallifetime))
							{
								//Cannot implement different lifetime until we extend
								//smoke trail coordinate type to include this master lifetime
								lifetime = reallifetime;

								oldindex = Trans_Obj.LaunchVapourStream((UByteP)weapon,itm->shape);//RJS 09Apr98
								index = weapon->hdg;					//RJS 12Jan98
								if (index > 0)
								{
									traillist[index].lastwx = wx;
									traillist[index].lastwy = wy;
									traillist[index].lastwz = wz;
									traillist[index].nextlist = oldindex;

									validpoint = ReplaySampleSmokePnt((UByteP)smkptr,(SWord&)weapon->hdg,instr_ptr,weapon->pitch,lifetime,theHdg,thePitch,theRoll);	//RJS 02Feb98
								}
							}
							else
							{
								index = weapon->hdg;				//RJS 12Jan98
								if (index > 0)
								{
									SHAPE.DetatchVapourStream(index,LIFETIME_VAPOUR);//RJS 09Apr98
									weapon->hdg = 0;				//RJS 12Jan98
								}
							}
							break;
						}
						case LT_FUNNEL:							//RJS 06Jun99
						{
//In real draw, this also removes the point straight away,
//so this bit doesn't actually do anything...
//							index = weapon->hdg;
//							if (index > 0)
//							{
//								traillist[index].lastwx = wx;
//								traillist[index].lastwy = wy;
//								traillist[index].lastwz = wz;
//
//								validpoint = ReplaySampleSmokePnt((UByteP)smkptr,(SWord&)weapon->hdg,instr_ptr,weapon->pitch,lifetime,theHdg,thePitch,theRoll);
//							}
							break;
						}
						case LT_INTFUEL:
						case LT_FUEL:
						{
							index = weapon->hdg;					//RJS 12Jan98
							if (index > 0)
							{
								if (traillist[index].thelist)
								{
									SLong	dist;
									SLong	dx,dy,dz;

									dx = wx - traillist[index].lastwx;
									dy = wy - traillist[index].lastwy;
									dz = wz - traillist[index].lastwz;

									dist = Math_Lib.distance3d(dx,dy,dz);
									if (dist >= mindist)
									{
										distscale = dist / mindist;

										traillist[index].lastwx = wx;
										traillist[index].lastwy = wy;
										traillist[index].lastwz = wz;
										traillist[index].nextlist = oldindex;

										validpoint = ReplaySampleSmokePnt((UByteP)smkptr,(SWord&)weapon->hdg,instr_ptr,weapon->pitch,lifetime,theHdg,thePitch,theRoll);	//RJS 02Feb98
									}
									else
									{
										if (SamplePntTime)
										{
											SLong	oldx, oldy, oldz;

											oldx = traillist[index].lastwx;
											oldy = traillist[index].lastwy;
											oldz = traillist[index].lastwz;

											traillist[index].lastwx = wx;
											traillist[index].lastwy = wy;
											traillist[index].lastwz = wz;

											ReplaySampleSmokePnt((UByteP)smkptr,(SWord&)weapon->hdg,instr_ptr,weapon->pitch,lifetime,theHdg,thePitch,theRoll);
											validpoint = FALSE;

											traillist[index].lastwx = oldx;
											traillist[index].lastwy = oldy;
											traillist[index].lastwz = oldz;
										}
									}
								}
								else
								{
									traillist[index].lastwx = wx;
									traillist[index].lastwy = wy;
									traillist[index].lastwz = wz;
									traillist[index].nextlist = oldindex;

									validpoint = ReplaySampleSmokePnt((UByteP)smkptr,(SWord&)weapon->hdg,instr_ptr,weapon->pitch,lifetime,theHdg,thePitch,theRoll);
								}
							}
							break;
						}
						case LT_DUST:
						{
							index = weapon->hdg;					//RJS 12Jan98
							if (index > 0)
							{
								traillist[index].lastwx = wx;
								traillist[index].lastwy = Land_Scape.GetGroundLevel(itm);
								traillist[index].lastwz = wz;
								traillist[index].nextlist = oldindex;

								validpoint = ReplaySampleSmokePnt((UByteP)smkptr,(SWord&)weapon->hdg,instr_ptr,weapon->pitch,lifetime,theHdg,thePitch,theRoll);
							}
							break;
						}
						case LT_MUDDY:
						{
//DeadCode RJS 25Nov98 							if (justlanded)	  //NOT INITIALISED!!
//DeadCode RJS 25Nov98 								oldindex = Trans_Obj.LaunchVapourStream((UByteP)weapon,(ShapeNum)object_obj3d->Shape);//RJS 09Apr98
//DeadCode RJS 25Nov98 							else
//DeadCode RJS 25Nov98 							{
//DeadCode RJS 25Nov98 								if (weapon->hdg > 0)
//DeadCode RJS 25Nov98 								{
//DeadCode RJS 25Nov98 									SHAPE.DetatchVapourStream(weapon->hdg,LIFETIME_VAPOUR);//RJS 09Apr98
//DeadCode RJS 25Nov98 									weapon->hdg = 0;			
//DeadCode RJS 25Nov98 								}
//DeadCode RJS 25Nov98 							}
//DeadCode RJS 25Nov98 
//DeadCode RJS 25Nov98 							index = weapon->hdg;
//DeadCode RJS 25Nov98 							if (index > 0)
//DeadCode RJS 25Nov98 							{
//DeadCode RJS 25Nov98 								traillist[index].lastwx = wx;
//DeadCode RJS 25Nov98 								traillist[index].lastwy = wy;
//DeadCode RJS 25Nov98 								traillist[index].lastwz = wz;
//DeadCode RJS 25Nov98 								traillist[index].nextlist = 0;
//DeadCode RJS 25Nov98 
//DeadCode RJS 25Nov98 								validpoint = SampleSmokePnt((UByteP)smkptr,(SWord&)weapon->hdg,instr_ptr,weapon->pitch,lifetime);
//DeadCode RJS 25Nov98 								drifty = (((mobileitem*)itm)->velhori << 7)>>10;
//DeadCode RJS 25Nov98 							}
//DeadCode RJS 25Nov98 							break;
							index = weapon->hdg;					//RJS 12Jan98
							if (index > 0)
							{
								if (traillist[index].thelist)
								{
									SLong	dist;
									SLong	dx,dy,dz;
									SLong	ox,oy,oz;

									ox = traillist[index].lastwx;
									oy = traillist[index].lastwy;
									oz = traillist[index].lastwz;

									dx = wx - ox;
									dy = wy - oy;
									dz = wz - oz;

									traillist[index].lastwx = wx;
									traillist[index].lastwy = wy;
									traillist[index].lastwz = wz;
									traillist[index].nextlist = oldindex;

									validpoint = ReplaySampleSmokePnt((UByteP)smkptr,(SWord&)weapon->hdg,instr_ptr,weapon->pitch,lifetime,theHdg,thePitch,theRoll);

									dist = Math_Lib.distance3d(dx,dy,dz);
									if (dist < 100)
									{
										if (SamplePntTime)
										{
											validpoint = FALSE;
											if (dist == 0)
												drifty = -View_Point->FrameTime();
										}

										traillist[index].lastwx = ox;
										traillist[index].lastwy = oy;
										traillist[index].lastwz = oz;
									}
								}
								else
								{
									traillist[index].lastwx = wx;
									traillist[index].lastwy = wy;
									traillist[index].lastwz = wz;
									traillist[index].nextlist = oldindex;

									validpoint = ReplaySampleSmokePnt((UByteP)smkptr,(SWord&)weapon->hdg,instr_ptr,weapon->pitch,lifetime,theHdg,thePitch,theRoll);//RJS 25Nov98
								}
							}
							break;
						}
						case LT_JETDUST:
						{
							if (itm->Status.size == AirStrucSize)
							{
								AirStrucPtr	acptr = (AirStrucPtr) itm;
								SLong		gheight = acptr->fly.pModel->GroundHeight;
								SLong		height = wy - gheight;
								SWord		realpitch = acptr->pitch;

								if ((height < 4000) && (realpitch > ANGLES_0Deg))
								{
									oldindex = Trans_Obj.LaunchVapourStream((UByteP)weapon,itm->shape);
									index = weapon->hdg;
									if (index > 0)
									{
										weapon->pitch = -1;

										traillist[index].lastwx = wx;
										traillist[index].lastwy = wy;
										traillist[index].lastwz = wz;
										traillist[index].nextlist = 0;

										if (traillist[index].LaunchCountdown < 0)
										{
											SLong	veltime = 300 - acptr->velhori;
											veltime /= 10;
											traillist[index].LaunchCountdown = veltime;

											validpoint = SampleDustPnt((UByteP)smkptr,(SWord&)weapon->hdg,instr_ptr,lifetime,height,realpitch);
										}
										else
											traillist[index].LaunchCountdown -= View_Point->FrameTime();
									}
								}
								else
								{
									if (weapon->hdg > 0)
									{
										SHAPE.DetatchVapourStream(weapon->hdg,LIFETIME_VAPOUR);//RJS 09Apr98
										weapon->hdg = 0;			
									}	
								}
							}
							break;
						}
					}
				}
			}
		}
	}
}

void shape::replay_animate_shape(ItemPtr	itm)
{
	if (itm !=Persons2::PlayerGhostAC)						
	{
		ShapeDescPtr	sdptr;

		animptr	adptr;

		// could fuck if something is being drawn...
//DeadCode JIM 26Mar99  		object_obj3d  = NULL;									//RJS 19Jun97

		adptr = itm->Anim;

		sdptr = SHAPESTUFF.GetShapePtr((ShapeNum)itm->shape);

		// We need this for smoke launchers......				//MS 30Nov98
 		switch (SHAPESTUFF.GetShapeScale(sdptr))				//MS 30Nov98
 		{														//MS 30Nov98
 			case SHP_GRP:										//MS 30Nov98
				return;
 				break;											//MS 30Nov98
 			case SHP_1CM:										//MS 30Nov98
 				shapescale = 0;									//MS 30Nov98
 				break;											//MS 30Nov98
 			case SHP_4CM:										//MS 30Nov98
 				shapescale = 2;									//MS 30Nov98
 				break;											//MS 30Nov98
 			case SHP_16CM:										//MS 30Nov98
 				shapescale = 4;									//MS 30Nov98
 				break;											//MS 30Nov98
 		}														//MS 30Nov98
		// ....We need this for smoke launchers					//MS 30Nov98

		UByte	vaptype = sdptr->Type.VapourType;				//RJS 21Jan99

		//Call the correct anim routine in this case statement
		if (sdptr->AnimDataSize > -1)
		{
			switch (sdptr->AnimDataSize)
			{
				case SMOKETRAILANIM:
					vaptype = TRAIL_OFF;
//					ProbeReplayStaticTrail((UByteP)sdptr,itm,adptr);
					break;
			}
		}

		switch (vaptype)							//RJS 10Mar98
		{
			case TRAIL_NORMAL:
			case TRAIL_STATIC:
				UpdateReplayVapourCoords((UByteP)sdptr,itm,adptr);
				break;
			case TRAIL_GROUND:
//				UpdateReplaySmokeDriftCoords((UByteP)sdptr,itm,adptr);
				break;
		}
	}
}

Bool	shape::ReplaySampleSmokePnt(	UByteP		smkinfo,
										SWord		&listindex,
										UByteP		instr_ptr,
										SWord		&Stores,
										UWord		LifeTime,
										SWord		&hdg,
										SWord		&pitch,
										SWord		&roll
										)
{
	Bool	validpoint = TRUE;

	if (SamplePntTime)
	{
		DOLAUNCHER_PTR	ptr = (DOLAUNCHER_PTR) instr_ptr;
		TrailRecord*	trailptr = &traillist[listindex];
		SmokeTypeP		smkptr = (SmokeTypeP) smkinfo;
		SLong			xcoord = ptr->posx;
		SLong			ycoord = ptr->posy;
		SLong			zcoord = ptr->posz;
		SLong			lifetime;
		SLong			wx, wy, wz;
		SWord			index = listindex;
		MATRIX  		omat;										
		MATRIX_PTR		obj_matrix = &omat;							
		UWord			scaleback;

		if (!LifeTime)											//RJS 09Apr98
			LifeTime = smkptr->LifeTime;						//RJS 09Apr98

//		if (Three_Dee.IsPaused())								//RJS 27Feb98
//			SamplePntTime = FALSE;

		trailptr->SampleTime -= View_Point->FrameTime();			//RJS 08Jan98
		if (trailptr->SampleTime < 0)							//RJS 08Jan98
			trailptr->SampleTime = smkptr->SampleTime;			//RJS 02Feb98
		else													//RJS 02Feb98
			validpoint = FALSE;									//RJS 02Feb98

		// -1 is infinite....
		if (Stores != -1)
		{
			Stores-=1;											

			if (Stores < 0)
				Stores = 0;
		}

		if (Stores)
		{
			lifetime = LifeTime;								//RJS 08Dec97

//			if (trailptr->lifetime && (lifetime > 500))
//				lifetime = trailptr->lifetime;

 			if (trailptr->nextlist)
 			{
 				Coords3DList*	nextptr = traillist[trailptr->nextlist].thelist;
 				if (nextptr)
 				{
 					wx = nextptr->trailpoint.gx;
 					wy = nextptr->trailpoint.gy;
 					wz = nextptr->trailpoint.gz;

 					SHAPE.AddNewVapourPoint(trailptr,wx,wy,wz,lifetime,smkptr->FadeTime);
 					lifetime = trailptr->lifetime;
 				}

 				trailptr->nextlist = 0;
 			}

			// Every frame....

 			wx = xcoord << shapescale;
 			wy = ycoord << shapescale;
 			wz = zcoord << shapescale;

			_matrix.generate2(	(Angles)hdg,
								(Angles)pitch,
								(Angles)roll,
								obj_matrix);

			scaleback = _matrix.transform(obj_matrix,wx,wy,wz);
			wx >>= (16-scaleback);
			wy >>= (16-scaleback);
			wz >>= (16-scaleback);

			wx += trailptr->lastwx;
			wy += trailptr->lastwy;
			wz += trailptr->lastwz;

			SHAPE.AddNewVapourPoint(trailptr,wx,wy,wz,lifetime,smkptr->FadeTime);

			if (trailptr->nopoints > smkptr->MaxPoints)
			{
				switch (smkptr->DeadAction)
				{
				case DEADSMK_DEFAULT:
	 				trailptr->bitshift = 0;
//DEADCODE DAW 23/04/99 					listindex = 0;					//RJS 12Apr99
//DEADCODE DAW 12/04/99 					listindex = -index;
					SHAPE.DetatchVapourStream(index,LIFETIME_VAPOUR);
					listindex = NextFreeVapour(0,0,0,smkinfo);										//RJS 23Apr99
					if (listindex)																	//RJS 23Apr99
						AddNewVapourPoint(&traillist[listindex],wx,wy,wz,lifetime,smkptr->FadeTime);//RJS 23Apr99
					break;
				case DEADSMK_SMOKECLOUD:
					SHAPE.AddSmokeCloud(trailptr,smkptr->CloudShape,index);
					break;
				}
			}
		}
		else
		{
			listindex = 0;
			SHAPE.DetatchVapourStream(index,LIFETIME_VAPOUR);	//RJS 09Apr98
		}
	}

	return(validpoint);
}

Bool	AirStruc::HasSmoked()
{
	Bool	retval = FALSE;
	if (this)
	{
		ShapeDescPtr		sdptr = SHAPESTUFF.GetShapePtr(shape);

		if (sdptr->AnimDataSize == AIRCRAFTANIM)
		{
			AircraftAnimData*	adptr = (AircraftAnimData*) Anim;
			if (adptr->hassmoked)
				retval = TRUE;
		}
	}

	return(retval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GenerateProbeTrails
//Author		Andy McMaster
//Date			Fri 26 Mar 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::GenerateProbeTrails()
{
	if (newprobecnt)
	{
		TrailRecordPtr		TrailPtr;
	 	SmokeTrailAnimData*	adptr;
		Coords3DList*		apoint;
		Coords3DList*		dpoint;
		Coords3DList*		npoint;
		Coords3DList*		*lpointptr;
		SLong				counter;
		SLong				howmany;
		SLong				divvy;
		SLong				staticlifeleft;
		SLong				realnopoints;

		int	index;
		for (index=0; index < newprobecnt; index++)
		{
			adptr = (SmokeTrailAnimData*) MakeProbes[index].itm->Anim;

			switch (MakeProbes[index].action)
			{
			case PROBER_KILL:
			{
				TrailPtr = &traillist[MAX_VAPOURS];
				apoint = (Coords3DList*) adptr->thelist;
				while (apoint)
				{
					dpoint = apoint;
					apoint = apoint->next;

					dpoint->next = TrailPtr->FakePointPtr;
					TrailPtr->FakePointPtr = dpoint;
				}

				adptr->thelist = NULL;

				Trans_Obj.RemoveTransientItemFromTrailList(MakeProbes[index].itm);//AMM 26Mar99
			}
			break;
			case PROBER_DEGRADE:
			{
				TrailPtr = &traillist[MakeProbes[index].index];
				apoint = TrailPtr->thelist;
				counter = 0;
				howmany = TrailPtr->nopoints;
				divvy = howmany / 6;
				staticlifeleft = 0;
				realnopoints = 0;

				// Down-grade first to max 6 points...
				if (divvy)
				{
					realnopoints++;

					howmany /= divvy;

					lpointptr = &apoint->next;
					apoint = apoint->next;
					while (apoint)
					{
						npoint = apoint;
						apoint = apoint->next;

						if (apoint && (counter != howmany))
						{
							//After draw, so any KillMe points are new and have not
							//already been added to fakepoint list...
//Dead							if (!npoint->KillMe)
//Dead							{
								npoint->next = TrailPtr->FakePointPtr;
								TrailPtr->FakePointPtr = npoint;
								TrailPtr->nopoints--;
//Dead							}
							counter++;
						}
					  	else
					  	{
					  		*lpointptr = npoint;

					  		lpointptr = &npoint->next;
					  		counter = 0;
					  		realnopoints++;
					  	}
					}
				}
				else
					realnopoints = howmany;

				adptr->nopoints = realnopoints;
				adptr->thelist = (ULong) TrailPtr->thelist;
				adptr->lifetime = TrailPtr->lifetime;
				adptr->SmkDescIndex = ((UByteP)TrailPtr->SmkDescPtr - (UByteP) &SmokeTrlList[0])/sizeof(SmokeType);
				adptr->currTime = TrailPtr->currTime;						//RJS 16Jun99

	
				TrailPtr->thelist = NULL;							
				TrailPtr->lifetime = 0;
				TrailPtr->nopoints = 0;								
				TrailPtr->bitshift = 0;								
				TrailPtr->nextlist = 0;								
				TrailPtr->beendrawn = 0;								
				TrailPtr->SampleTime = 0;							
//DeadCode RJS 06May99 				TrailPtr->InitVelH = 0;								
//DeadCode RJS 06May99 				TrailPtr->InitVelY = 0;								
//DeadCode RJS 06May99 				TrailPtr->Acceleration = 0;						
				TrailPtr->SmkDescPtr = NULL;						
				TrailPtr->cloudlaunched = FALSE;
				TrailPtr->transient = 0;
				TrailPtr->currTime = 0;							//RJS 16Jun99

				//Log this item as transient fiddle...
				Trans_Obj.AddTransientItemToTrailList(MakeProbes[index].itm);//AMM 26Mar99
			}
			break;
			}
		}

		newprobecnt = 0;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		dummy_animate_shape
//Author		Robert Slater
//Date			Tue 6 Apr 1999
//
//Description	Routine to handle vapour trails that are off screen.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::dummy_animate_shape(ItemPtr	itm, UByteP	sptr)
{
	if (itm->Status.size == AIRSTRUCSIZE)
	{
		ShapeDescPtr	sdptr = (ShapeDescPtr) sptr;
		switch (sdptr->Type.VapourType)
		{
			case TRAIL_NORMAL:
			case TRAIL_STATIC:
				HandleVapourCoords(sptr,itm);
				break;
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		HandleVapourCoords
//Author		Robert Slater
//Date			Tue 6 Apr 1999
//
//Description	Kills vapour streams that aren't important...
//				... such as the F86 exhaust
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::HandleVapourCoords(UByteP	rsdptr, itemptr	itm)
{
	AircraftAnimData*	adptr = (AircraftAnimData*) itm->Anim;	//RJS 07Apr99
	if (adptr->hassmoked)										//RJS 07Apr99
	{
		ShapeDescPtr		sdptr = (ShapeDescPtr) rsdptr;
		int					wpnum;
		WeapAnimData*		weapon;
		UByte				instsize = sizeof(DOLAUNCHER) + 1;
		DOLAUNCHER_PTR		lptr;
		UByteP				instr_ptr;
		UByteP				base_ptr;
		UWord				instruction;
		UByteP				aptr = (UByteP)adptr;

		base_ptr = (UByteP )sdptr + sdptr->LauncherDataSize;

		for (wpnum = 0; wpnum < adptr->nolaunchers; wpnum++)
		{
			weapon = (WeapAnimData*) &adptr->weaponlaunchers[wpnum];
			if (weapon && (weapon->hdg > 0))
			{
				instr_ptr = base_ptr + (instsize * wpnum);
				instr_ptr++;

				lptr = (DOLAUNCHER_PTR) instr_ptr;
				switch (lptr->lnchrtype)
				{
				case LT_FUNNEL:
				case LT_ENGINE:
				{
					if (weapon->LauncherType != LT_CONTRAIL)
					{
						pTrailItm = itm;
						SHAPE.DetatchVapourStream(weapon->hdg,200);
						weapon->hdg = 0;
						weapon->LauncherType = lptr->lnchrtype;
					}
				}
				break;
				}
			}
		}
	}
	adptr->timenotvis += View_Point->FrameTime();			//RJS 30Jun99
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ReplayAnimData_NewShape
//Author		Robert Slater
//Date			Wed 21 Apr 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::ReplayAnimData_NewShape(UWord	uniqueid, UWord	theShape)
{
	ItemPtr		itm = (ItemPtr)Persons2::ConvertPtrUID((UniqueID)uniqueid);
	SLong		animdatasize = GetAnimDataSize((ShapeNum)theShape);

	memset(&itm->Anim[0],0,animdatasize);

	itm->shape = (ShapeNum)theShape;

	AnimWeaponPack = 0;

	DefaultAnimData(itm,itm->Anim,TRUE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FakeDustTrail
//Author		Robert Slater
//Date			Tue 18 May 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::FakeDustTrail(Coords3D& pos, SLong	vel, SWord	hdg, UByteP	descptr)
{
	if (vel > MPHHALF)
	{
		ShapeDescPtr	sdptr = (ShapeDescPtr)descptr;
		if (sdptr->LauncherDataSize && Trans_Obj.WithinVisibleRange(pos,50000))
		{
			SWord			direction = hdg + ANGLES_180Deg;
			UByteP			instr_ptr = (UByteP )sdptr + sdptr->LauncherDataSize;
			DOLAUNCHER_PTR	lptr;
			SLong			deltax, deltaz;
			SWord			sin_ang, cos_ang;
			SLong			distance = (vel * 800)/MPH30;

			if (distance > 800)	distance = 800;

			instr_ptr++;

			lptr = (DOLAUNCHER_PTR)instr_ptr;

			Math_Lib.high_sin_cos((Angles)direction,sin_ang,cos_ang);
			deltax = (cos_ang * distance) / ANGLES_FRACT;
			deltaz = (sin_ang * distance) / ANGLES_FRACT;

			//Put dust trail object in the binary tree...


		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ResetACGears
//Author		Robert Slater
//Date			Tue 1 Jun 1999
//
//Description
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	mobileitem::ResetACGears()
{
	AircraftAnimData*	adptr;
	MobileItemPtr		entry = ACList;
	AirStrucPtr			ac;

	while (entry)
	{
		if (	(entry->Status.size == AIRSTRUCSIZE)
			&&	(entry->vel >= MPH100)							//RJS 10Jun99
			&&	(entry->movecode != AUTO_TAKEOFF)				//RJS 10Jun99
			&&	(entry->movecode != AUTO_LANDING)	)			//RJS 10Jun99
		{
			ac = (AirStrucPtr) entry;
			if (ac != Persons2::PlayerSeenAC)					//RJS 30Jun99
			{
				SHAPE.NavigationLightsActive(entry,FALSE);

				adptr = (AircraftAnimData*) entry->Anim;
				adptr->acleglowerl = 255;
				adptr->acleglowerr = 255;
				adptr->acleglowerf = 255;
				adptr->acleglowerb = 255;
				adptr->animtoggle = 1;

				ac->fly.pModel->ResetGearPos(false);			//RJS 30Jun99
			}
			else
				ac->fly.pModel->ResetGearPos(true);				//RJS 30Jun99
		}

		entry = entry->nextmobile;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DrawTempBlobTrail
//Author		Robert Slater
//Date			Mon 7 Jun 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::DrawTempBlobTrail(SLong	index, UByteP smkinfo,SLong lifetime,Bool validpoint)
{
	if (index)
	{
		if (index < 0)											
			index = -index;

		if (index > MAX_VAPOURS)						
			_Error.EmitSysErr(__FILE__":(DOSMKTRAIL)    Shouldn't be this : %d\n",index);

		TrailRecordPtr	TrailPtr = &traillist[index];
													 
		if (smkinfo)								 
			TrailPtr->SmkDescPtr = smkinfo;			 
		else										 
		{
			smkinfo = TrailPtr->SmkDescPtr;			 
			lifetime = TrailPtr->lifetime;			 
		}

		if (smkinfo)
		{
			SmokeTypeP		ptr = (SmokeTypeP) smkinfo;
			Coords3DList*	apoint;

			apoint = TrailPtr->thelist;
			if (apoint)
			{
				Coords3D	pos;
				
				pos.X = apoint->trailpoint.gx;
				pos.Y = apoint->trailpoint.gy;
				pos.Z = apoint->trailpoint.gz;

				apoint->KillMe = 1;

				apoint->next = TrailPtr->FakePointPtr;
				TrailPtr->FakePointPtr = apoint;
				TrailPtr->nopoints--;

				if (validpoint)
				{
					SLong	velhori = ptr->VelHori;
					SLong	vely = ptr->VelY;
					SWord	hdg;

					if (pTrailItm->Status.size >= MOBILESIZE)
					{	
						vely += ((mobileitem*)pTrailItm)->vely;
						hdg = ((mobileitem*)pTrailItm)->hdg;
					}
					else
						hdg = Math_Lib.rnd();

					Trans_Obj.LaunchSmokePuff2((mobileitem*)pTrailItm,&pos,WRECKP,NULL,velhori,vely,hdg,lifetime,lifetime,*mobileitem::currworld);
				}

				TrailPtr->thelist = NULL;
			}
		}
	}
}

void	Coords3DList::Wipe()
{
	Coords3DList*	apoint = this;
	Coords3DList*	tmpptr;
	while (apoint)
	{
		tmpptr = apoint->next;
		delete apoint;
		apoint = tmpptr;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BombBayDoors
//Author		Robert Slater
//Date			Mon 28 Jun 1999
//
//Description	Shares the anim toggle with the gear...
//				...bombers have fake gear anyway, so this doesn't matter
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::BombBayDoors(AirStrucPtr	ac, SLong animval)
{
	//We don't want to accidently lower the gear.
	if ((ac->shape == B29) || (ac->shape == B26))
	{
		AircraftAnimData*	adptr = (AircraftAnimData*) ac->Anim;

		if (animval == ANIM_GEAR_DOWN)
			adptr->animtoggle = 1;
		else
			adptr->animtoggle = -1;
	}
}








//Special anim data stuff......

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetAnimDataSizeFlags
//Author		Robert Slater
//Date			Fri 16 Apr 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::SetAnimDataFlags(ShapeNum shpno,animptr& adptr, SLong &animflags)
{
	ShapeDescPtr sdptr,newshpp;
	SLong	ret_val;
	SWord	animdatasize;
	SLong	flagstuff = 0;

	sdptr = SHAPESTUFF.GetShapePtr(shpno);
	ShapeNum	newshp;

	if (SHAPESTUFF.GetShapeScale(sdptr)!=SHP_GRP)				
	{
		animdatasize = sdptr->AnimDataSize;
		if (animdatasize > -1)
		{
			//special cases...
			switch (animdatasize)
			{
				case MINANIM:
					flagstuff += 1<<MINANIM;
					break;
				case POLYPITANIM:
					flagstuff += 1<<MINANIM;
					flagstuff += 1<<MOVEGUNANIM;
					flagstuff += 1<<AIRCRAFTANIM;
					flagstuff += 1<<POLYPITANIM;
					break;
				case WEAPANIM:
					flagstuff += 1<<MINANIM;
//DeadCode RJS 01Jun99 					flagstuff += 1<<DIRECTANIM;
					flagstuff += 1<<WEAPANIM;
					break;
				case AIRCRAFTANIM:
					flagstuff += 1<<MINANIM;
					flagstuff += 1<<MOVEGUNANIM;
					flagstuff += 1<<AIRCRAFTANIM;
					break;
				case SMOKETRAILANIM:
					flagstuff += 1<<MINANIM;
					flagstuff += 1<<MOVEGUNANIM;
					flagstuff += 1<<SMOKETRAILANIM;
					break;
				case TRUCKANIM:
					flagstuff += 1<<MINANIM;
					flagstuff += 1<<MOVEGUNANIM;
					flagstuff += 1<<TRUCKANIM;
					break;
				case TRAINANIM:
					flagstuff += 1<<MINANIM;
					flagstuff += 1<<MOVEGUNANIM;
					flagstuff += 1<<TRAINANIM;
					break;
				default:
					flagstuff += 1<<MINANIM;
					flagstuff += 1<<animdatasize;
					break;
			}
		}
		else
			flagstuff = 1<<MINANIM;

		animflags |= flagstuff;
	}
	else
	{
		ShapeNum	newshp;
		SLong		tmp;
		UByteP		instr_ptr = (UByteP )sdptr + sdptr->liveshpref;
		SLong		count = 0;

		while (GetGroupElement(instr_ptr,newshp,tmp,tmp,tmp))
		{
			SetAnimDataFlags(newshp,adptr,animflags);
			count++;
		}

		if (!count)												//DAW 23Apr99
			animflags |= 1<<MINANIM;							//DAW 23Apr99
	}

	adptr = animflags;
}

//DeadCode DAW 30Jul99 UByte&	animptr::operator[] (int a)
//DeadCode DAW 30Jul99 {
//DeadCode DAW 30Jul99 #ifndef	NDEBUG
//DeadCode DAW 30Jul99 	assert((size&~(1<<MINANIM))>a);
//DeadCode DAW 30Jul99 #endif
//DeadCode DAW 30Jul99 	return UByteP(ptr)[a];
//DeadCode DAW 30Jul99 }
//DeadCode DAW 30Jul99 
//DeadCode DAW 30Jul99 UByte&	animptr::operator[] (SWord a)
//DeadCode DAW 30Jul99 {
//DeadCode DAW 30Jul99 #ifndef	NDEBUG
//DeadCode DAW 30Jul99 	assert((size&~(1<<MINANIM))>a);
//DeadCode DAW 30Jul99 #endif
//DeadCode DAW 30Jul99 	return UByteP(ptr)[a];
//DeadCode DAW 30Jul99 }
//DeadCode DAW 30Jul99 
//DeadCode DAW 30Jul99 UByte&	animptr::operator[] (UWord a)
//DeadCode DAW 30Jul99 {
//DeadCode DAW 30Jul99 #ifndef	NDEBUG
//DeadCode DAW 30Jul99 	assert((size&~(1<<MINANIM))>a);
//DeadCode DAW 30Jul99 #endif
//DeadCode DAW 30Jul99 	return UByteP(ptr)[a];
//DeadCode DAW 30Jul99 }
//DeadCode DAW 30Jul99 
//DeadCode DAW 30Jul99 UByte&	animptr::operator[] (UByte a)
//DeadCode DAW 30Jul99 {
//DeadCode DAW 30Jul99 #ifndef	NDEBUG
//DeadCode DAW 30Jul99 	assert((size&~(1<<MINANIM))>a);
//DeadCode DAW 30Jul99 #endif
//DeadCode DAW 30Jul99 	return UByteP(ptr)[a];
//DeadCode DAW 30Jul99 }
//DeadCode DAW 30Jul99 
//DeadCode DAW 30Jul99 void	animptr::operator += (int a)
//DeadCode DAW 30Jul99 {
//DeadCode DAW 30Jul99 	ptr = (void*)((UByteP)ptr + a);
//DeadCode DAW 30Jul99 #ifndef	NDEBUG
//DeadCode DAW 30Jul99 	assert((size&0x3ff) >= a);
//DeadCode DAW 30Jul99 	size -= ULong(a);
//DeadCode DAW 30Jul99 	if ((size & 0x3ff)==0)	ptr = 0;							//RJS 26May99
//DeadCode DAW 30Jul99 #endif
//DeadCode DAW 30Jul99 }
//DeadCode DAW 30Jul99 
//DeadCode DAW 30Jul99 void	animptr::operator ++ ()
//DeadCode DAW 30Jul99 {
//DeadCode DAW 30Jul99 	ptr = (void*)((UByteP)ptr + 1);
//DeadCode DAW 30Jul99 #ifndef	NDEBUG
//DeadCode DAW 30Jul99 	assert((size&0x3ff) >= 1);
//DeadCode DAW 30Jul99 	size -= 1;
//DeadCode DAW 30Jul99 	if ((size & 0x3ff)==0)	ptr = 0;							//RJS 26May99
//DeadCode DAW 30Jul99 #endif
//DeadCode DAW 30Jul99 }
//DeadCode DAW 30Jul99 
//DeadCode DAW 30Jul99 #ifndef	NDEBUG
//DeadCode DAW 30Jul99 
//DeadCode DAW 30Jul99 animptr::operator MinAnimData*(){assert(size & (1<<MINANIM)); return (MinAnimData*)ptr;};
//DeadCode DAW 30Jul99 animptr::operator GrpMinAnimData*(){assert(size & (1<<MINANIM)); return (GrpMinAnimData*)ptr;};
//DeadCode DAW 30Jul99 animptr::operator SunAnimData*(){assert(size & (1<<SUNANIM)); return (SunAnimData*)ptr;};
//DeadCode DAW 30Jul99 animptr::operator ExplodeAnimData*(){INT3; return (ExplodeAnimData*)ptr;};
//DeadCode DAW 30Jul99 animptr::operator FireAnimData*(){INT3; return (FireAnimData*)ptr;};
//DeadCode DAW 30Jul99 animptr::operator BalloonAnimData*(){INT3; return (BalloonAnimData*)ptr;};
//DeadCode DAW 30Jul99 animptr::operator BarageAnimData*(){assert(size & (1<<BARAGEANIM)); return (BarageAnimData*)ptr;};
//DeadCode DAW 30Jul99 animptr::operator TroopAnimData*(){assert(size & (1<<TROOPANIM)); return (TroopAnimData*)ptr;};
//DeadCode DAW 30Jul99 animptr::operator TrainAnimData*(){assert(size & (1<<TRAINANIM)); return (TrainAnimData*)ptr;};
//DeadCode DAW 30Jul99 animptr::operator BlokesAnimData*(){assert(size & (1<<BLOKESANIM)); return (BlokesAnimData*)ptr;};		
//DeadCode DAW 30Jul99 animptr::operator WeapAnimData*(){assert(size & (1<<WEAPANIM)); return (WeapAnimData*)ptr;};
//DeadCode DAW 30Jul99 animptr::operator MoveGunAnimData*(){assert(size & (1<<MOVEGUNANIM)); return (MoveGunAnimData*)ptr;};
//DeadCode DAW 30Jul99 animptr::operator TwoGunAnimData*(){assert(size & (1<<MOVEGUNANIM)); return (TwoGunAnimData*)ptr;};
//DeadCode DAW 30Jul99 animptr::operator AircraftAnimData*(){assert(size & (1<<AIRCRAFTANIM)); return (AircraftAnimData*)ptr;};
//DeadCode DAW 30Jul99 animptr::operator PolyPitAnimData*(){assert(size & (1<<POLYPITANIM)); return (PolyPitAnimData*)ptr;};
//DeadCode DAW 30Jul99 animptr::operator LauncherAnimData*(){assert(size & (1<<LAUNCHERANIM)); return (LauncherAnimData*)ptr;};
//DeadCode DAW 30Jul99 animptr::operator WindsocAnimData*(){assert(size & (1<<WINDSOCANIM)); return (WindsocAnimData*)ptr;};
//DeadCode DAW 30Jul99 animptr::operator CloneAnimData*(){assert(size & (1<<CLONEANIM)); return (CloneAnimData*)ptr;};
//DeadCode DAW 30Jul99 animptr::operator FlareAnimData*(){assert(size & (1<<FLAREANIM)); return (FlareAnimData*)ptr;};
//DeadCode DAW 30Jul99 animptr::operator ParachuteAnimData*(){assert(size & (1<<PARACHUTEANIM)); return (ParachuteAnimData*)ptr;};
//DeadCode DAW 30Jul99 animptr::operator ThugAnimData*(){assert(size & (1<<THUGANIM)); return (ThugAnimData*)ptr;};
//DeadCode DAW 30Jul99 animptr::operator MissileAnimData*(){assert(size & (1<<MISSILEANIM)); return (MissileAnimData*)ptr;};
//DeadCode DAW 30Jul99 animptr::operator DebrisAnimData*(){assert(size & (1<<DEBRISANIM)); return (DebrisAnimData*)ptr;};
//DeadCode DAW 30Jul99 animptr::operator SmokeTrailAnimData*(){assert(size & (1<<SMOKETRAILANIM)); return (SmokeTrailAnimData*)ptr;};
//DeadCode DAW 30Jul99 animptr::operator Coords3DList*(){return (Coords3DList*)ptr;};
//DeadCode DAW 30Jul99 
//DeadCode DAW 30Jul99 #endif
//DeadCode DAW 30Jul99 
//DeadCode DAW 30Jul99 UByteP	animptr::operator & ()
//DeadCode DAW 30Jul99 {
//DeadCode DAW 30Jul99 #ifndef	NDEBUG
//DeadCode DAW 30Jul99 	if (size & 0x3ff)
//DeadCode DAW 30Jul99 		return (UByteP)ptr;
//DeadCode DAW 30Jul99 	
//DeadCode DAW 30Jul99 	return NULL;
//DeadCode DAW 30Jul99 #else
//DeadCode DAW 30Jul99 	return (UByteP)ptr;
//DeadCode DAW 30Jul99 #endif	
//DeadCode DAW 30Jul99 };
//DeadCode DAW 30Jul99 
//DeadCode DAW 30Jul99 int		animptr::operator - (animptr& a)
//DeadCode DAW 30Jul99 {
//DeadCode DAW 30Jul99 #ifndef	NDEBUG
//DeadCode DAW 30Jul99 	int	retval = (int)ptr - (int)a.ptr;
//DeadCode DAW 30Jul99 
//DeadCode DAW 30Jul99 	assert((retval>=0)&&(retval<(size&0x3ff)));
//DeadCode DAW 30Jul99 
//DeadCode DAW 30Jul99 	return (retval);
//DeadCode DAW 30Jul99 #else
//DeadCode DAW 30Jul99 	return (int)ptr - (int)a.ptr;
//DeadCode DAW 30Jul99 #endif
//DeadCode DAW 30Jul99 }
//DeadCode DAW 30Jul99 
//DeadCode DAW 30Jul99 ULong	animptr::Offset(void*	a)
//DeadCode DAW 30Jul99 {
//DeadCode DAW 30Jul99 #ifndef	NDEBUG
//DeadCode DAW 30Jul99 	SLong	offset = (UByteP)a - (UByteP)ptr;
//DeadCode DAW 30Jul99 
//DeadCode DAW 30Jul99 	assert ((offset>=0)&&(offset<(size&0x3ff)));
//DeadCode DAW 30Jul99 
//DeadCode DAW 30Jul99 	return ULong(offset);
//DeadCode DAW 30Jul99 #else
//DeadCode DAW 30Jul99 	return ULong((UByteP)a - (UByteP)ptr);
//DeadCode DAW 30Jul99 #endif
//DeadCode DAW 30Jul99 }




#ifndef	NANIMDEBUG

typedef struct _MemBlockStruc
{
        _MemBlockStruc*	pBlockHeaderNext;
		_MemBlockStruc*	pBlockHeaderPrev;
		char*			filename;
		ULong			nLine;
		ULong			nDataSize;
		ULong			nBlockUse;
		ULong			lrequest;
		UByte			gap[4];
		UByte			userdata[8];
} _MemBlockStruc;

void	DbgMemTest2(void*	ptr)
{
	if (ptr)
	{
		_MemBlockStruc*	memblock = (_MemBlockStruc*) (int(ptr)-32);
		if (	(memblock->gap[0]!=0xFD)
			||	(memblock->gap[1]!=0xFD)
			||	(memblock->gap[2]!=0xFD)
			||	(memblock->gap[3]!=0xFD)	)
		{
			INT3;
		}

		if (	(memblock->gap[4+memblock->nDataSize]!=0xFD)
			||	(memblock->gap[5+memblock->nDataSize]!=0xFD)
			||	(memblock->gap[6+memblock->nDataSize]!=0xFD)
			||	(memblock->gap[7+memblock->nDataSize]!=0xFD)	)
		{
			INT3;
		}
	}
}

void	animptr::MemTest()
{
	DbgMemTest2(ptr);
}


#endif
