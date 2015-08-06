//------------------------------------------------------------------------------
//Filename       shapes.h
//System         
//Author         Paul.   
//Date           Mon 18 Sep 1995
//Description    
//------------------------------------------------------------------------------
#ifndef	SHAPES_Included
#define	SHAPES_Included

//DeadCode RJS 01Dec97 #include	"AnimData.h"										//RJS 10Feb97
//DeadCode RJS 01Dec97 #include	"3dInstr.H"
#include	"shapenum.g"										//PD 27Aug96

#include	"bitfield.h"										//PD 27Aug96

 MAKEFIELD	(ShapeNum,ShapeNumMIN,ShapeNumMAX);					//PD 27Aug96

#define	DEFAULT_SHAPES 0

#define	SIMPLE	0
#define	COMPLX	1

//DeadCode RJS 06Mar98 #define MaxNumberOfShapes	512

typedef UWord	ShapeNumber;

typedef ShapeNumber *ShapeListPtr;

typedef struct	Shape_Type										//RJS 02Dec97
{
	UWord		shapenumber:12,		//For debug purposes...		//RJS 10Mar98
				VapourType:4;									//RJS 10Mar98
	UByte		haslaunchers: 1,	//obvious
				DrawPriority: 1,	//For some transients...	//RJS 27Aug97
				StopDead	: 1,	//if you hit something bigenough//RJS 01Aug9
				KillInvTrans: 1,	//if this transient goes out of view, remove
				SubShapeOnly: 1,								//RJS 10Mar98
/*ScaleType*/	scaletype 	: 2;	//Size or Group flag
}
ShapeType,*ShapeTypeP;											//RJS 02Dec97

typedef	struct	Shape_Desc										//RJS 02Dec97
{
	ShapeType	Type;         //scaling,shape ID,has launchers,grp//PD 07Mar96
	UWord		Size;         //in bigger 1M units
	UWord		LauncherDataSize;								//PD 09Jul96
	UWord		CollisionOffset;								//RJS 18Feb97
	UWord		LightDataOffset;								//RJS 17Dec97
	SWord		AnimDataSize;									//RJS 11Nov97
	UWord		sx,
				sy,
				sz;

	UWord		liveshpref,	 //need Fast routine to generate dopoint 0 on body0
				deadshpref;	//need interpretted case on range
	UWord		damagedshpref,	 //need Fast routine to generate dopoint 0 on body0
				dyingshpref;

	UWord		Vulnerability	:6,	//number of hits needed
				VulnSpare		:2,								//RJS 09Sep96
	  			DeadTime		:5,								//RJS 06Sep96
				DeadScale		:2,								//RJS 06Sep96
				Spare			:1;								//RJS 09Sep96
 	UWord		DamageOffset;									//RJS 28Apr99
	UWord		RealVulnerability;								//RJS 22Jan98
	SWord		EyeDeltaX;										//RJS 09Jul98
	SLong		MaxDrawRange;									//RJS 22Jan99
	UWord		RealDamageType:8,								//RJS 28Apr99
				RealDamageStrength:8;							//RJS 28Apr99
}
ShapeDesc,
*ShapeDescPtr;													//RJS 02Dec97

//DeadCode RDH 28Nov95 class	fileblock;
//DeadCode RDH 28Nov95 typedef	fileblock	*fileblockptr;								//JIM 31Oct95
//DeadCode PD 15Mar96 #ifndef	FILEMAN_Included
//DeadCode PD 15Mar96 typedef class	fileblock *fileblockptr;
//DeadCode PD 15Mar96 #endif
//------------------------------------------------------------------------------
//	ShapeStuff class definition
//------------------------------------------------------------------------------
//DeadCode JIM 17Jan96 typedef	struct	ShapeNumField*	ShapeNumFieldPtr;

class	shapestuff
		{
			
		friend	class	fileman;
		friend	class	fileblock;
		friend 	class	shape;

		//----------------------------------------
		// Typedef for pointer to member function
		//----------------------------------------

		typedef	void	(shapestuff::*sfmfp) (UByte *&,ULong &);

		//------------------------------
		// Typedef for fix-up table data
		//------------------------------

		typedef	struct	shp_inst_fix
		{
			sfmfp	fixrtn;
			UWord	skipsize;
		}
		shpinstfix,
		*shpinstfixptr;
		
		fileblock*		*shapetable;							//PD 15Mar96

		ShapeNum		ShapeFixing;							//RJS 23Apr97

//DeadCode RJS 01Dec97 		shpinstfix		fixuptable[dosetglassrangeno+1];		//PD 13Mar96
		shpinstfixptr		fixuptable;							//RJS 01Dec97

		UWord			//Fixup table size						//PD 13Mar96
						list_size,
						list_index;

//Old_Code PD 27Aug96 		ULong	glob_list[(MaxNumberOfShapes/32)];

		ShapeNumField	gsnf;									//PD 27Aug96

		ShapeNumField*	glob_list;								//PD 27Aug96

		UByte	*shp_base_ptr;

		Bool	forwardref;										//RJS 19Mar97

	public:
		SLong				shape_image_mem;					//RJS 26Mar98
		SLong				shape_alpha_mem;					//RJS 26Mar98

		shapestuff(void );

		shapestuff(UWord );

		~shapestuff(void );

//Old_Code PD 27Aug96 		UWord 	LoadShapes(ShapeListPtr );

		ShapeDescPtr
				GetShapePtr(ShapeNumber );

		void	AddShapesToGlobList(ShapeNumField* reqdshps);
//Old_Code PD 27Aug96 		void	AddShapesToGlobList(UWord *,UWord&);

		void	LoadRequiredShapes(void );

		void	UnLoadRequiredShapes(void );

		ScaleType GetShapeScale(ShapeDescPtr );					//PD 23Apr96
		ULong	GetShapeStrength(ShapeNumber );					//RJS 22Jan98
		ULong	GetShapeDamageStrength(ShapeNumber );			//RJS 22Jan98
		ULong	GetShapeDamageType(ShapeNumber );				//RJS 22Jan98

	private:

		Bool	LoadShape(ShapeNumber );

		void	UnLoadShape(ShapeNumber );

		static	void	FixupShapeFile(void*	&dataarea,ULong&	datalengthin);
		void	FixupShape(UByte *);

		void	FixHeaderData(ShapeDescPtr );

		void	FixInstrData(UByte *&, ULong& );

	protected:

		void	settable(void );

		void	FixupStubb(UByte *&,ULong &);
		void	FixupPolygon(UByte *&,ULong &);
		void	FixupSmoothPoly(UByte *&,ULong &);
		void	FixupCreateIPoly(UByte *&,ULong &);
		void	FixupDoGroup(UByte *&,ULong &);
		void	FixupDoNPoints(UByte *&,ULong &);
		void	FixupDoNTPoints(UByte *&,ULong &);
		void	FixupGoto(UByte *&,ULong &);
		void	FixupDrawBetween(UByte *&,ULong &);				//MGA 28Nov95
		void	FixupIfCross(UByte *&,ULong &);
		void	FixupDoNSubs(UByte *&,ULong &);
		void	FixupNPoint2X(UByte *&,ULong &);
		void	FixupNVec(UByte *&,ULong &);
		void	FixupDoRelpoly(UByte *&,ULong &);
		void	FixupIfCase(UByte *&,ULong &);
		void	FixupCreateBPoly(UByte *&,ULong &);				//PD 15Jan96
		void	FixupDrawCloud(UByte *&,ULong &);				//PD 22Jan96
		void	FixupBitsOff(UByte *&,ULong &);					//PD 17Apr96
		void	FixupBitsOffCock(UByte *&,ULong &);				//RJS 23Jan98
		void	FixupDoCollision(UByte *&,ULong &);				//RJS 18Feb97
		void	FixupDoCaseRange(UByte *&,ULong &);				//RJS 03Mar97
		void	FixupDoIfPiloted(UByte *&,ULong &);				//RJS 07Mar97
		void	FixupDoDrawIPoly(UByte *&,ULong &);				//RJS 19Mar97
		void	FixupDoNIVerts(UByte *&,ULong &);				//RJS 20Mar97
		void	FixupDoTriFan(UByte *&,ULong &);				//RJS 27Mar97
		void	FixupDoTriZag(UByte *&,ULong &);				//RJS 27Mar97
		void	FixupDoTriFanFlat(UByte *&,ULong &);			//RJS 16Apr97
		void	FixupDoTriZagFlat(UByte *&,ULong &);			//RJS 16Apr97
		void	FixupDoMorphNPoints(UByte *&,ULong &);			//RJS 08Dec97
		void	FixupDoTimerPhase(UByte *&,ULong &);			//RJS 10Dec97
		void	FixupDoNiAnimVerts(UByte *&,ULong &);			//RJS 13Jan98
		void	FixupDoIfHard3d(UByte *&,ULong &);				//RJS 04Feb98
		void	FixupDoMorphNSphrs(UByte *&,ULong &);				//RJS 05Feb98
		void	FixupDoMorphNSphrsImapd(UByte *&,ULong &);				//RJS 05Feb98
		void	FixupDoGunSight(UByte *&,ULong &);				//RJS 04Mar98
		void	FixupDoIfBright(UByte *&,ULong &);				//RJS 20Mar98
		void	FixupDoNDeltaPoints(UByte *&,ULong &);			//RJS 02Jun98
		void	FixupDoNSpheres(UByte *&,ULong &);				//RJS 13Jul98
		void	FixupDoNSpheresImapd(UByte *&,ULong &);			//RJS 13Jul98
		void	FixupDoDrawReflectPoly(UByte *&,ULong &);		//RJS 26Aug98
		void	FixupDoISphere(UByte *&,ULong &);				//RJS 03Nov98
		void	FixupDoICylinder(UByte *&,ULong &);				//RJS 03Nov98
		void	FixupDoIncln(UByte *&,ULong &);					//RJS 06Apr99


		};

		extern class shapestuff SHAPESTUFF;

#endif
