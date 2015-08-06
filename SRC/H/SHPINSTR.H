//------------------------------------------------------------------------------
//Filename       shpinstr.h
//System         
//Author         Robert Slater
//Date           Mon 1 Dec 1997
//Description    
//				Shape instruction definitions and equates.
//				Should only really be included by '3dcom.cpp'....
//
//------------------------------------------------------------------------------
#ifndef	SHPINSTR_Included
#define	SHPINSTR_Included

#define	DEFAULT_SHPINSTR 0

enum	GrpTokenFlags											//RJS 12Feb99
{
	GRP_NORMAL = 0,
	GRP_INVIS,
	GRP_TKN_INVIS_DEP,
	GRP_TKN_VIS,
	GRP_TKN_VIS_DEP
};

enum	SmkDeath
{
	DEADSMK_DEFAULT = 0,
	DEADSMK_SMOKECLOUD
};

enum	AtMax
{
	MAX_STAY = 0,
	MAX_RESET_ZERO,
	MAX_RESET_ONE,
	MAX_DECREMENT,
	MAX_FADEOUT,
	MAX_ALIGN = 255
};

enum	ClockType
{
	PER_FRAME = 0,
	PER_SEC10,
	PER_SEC100,
	PER_ALIGN = 255
};

enum	EffectType
{
 	FX_SFX = 0,
	FX_VISUAL,
	FX_INCREMENT,
	FX_EJECT,
	FX_RADIO,
	FX_ALIGN = 255
};

enum	SwitchConditions										//RJS 13Mar98
{																//RJS 13Mar98
	GREATER_THAN = 0,											//RJS 13Mar98
	LESS_THAN													//RJS 13Mar98
};																//RJS 13Mar98

enum	SufaceTextureType										//RJS 24May99
{																//RJS 24May99
	STEXT_NOSHADE = 0,											//RJS 24May99
	STEXT_DULL,													//RJS 24May99
	STEXT_SHINY,												//RJS 24May99
	STEXT_REFLECTIVE											//RJS 24May99
};

enum	MipMapTextureType										//RJS 24May99
{																//RJS 24May99
	MIP_OFF = 0,												//RJS 24May99
	MIP_ON = 1													//RJS 24May99
};																//RJS 24May99

enum	TrailStat
{
	TRAIL_OFF = 0,
	TRAIL_NORMAL,
	TRAIL_GROUND,
	TRAIL_STATIC												//MS 30Nov98
};

enum	SmkTrailTypes
{
	SMK_IMAPD = 0,
	SMK_SCATTER = 1,
	SMK_STREAM = 2,
	SMK_CLUSTER = 3,
	SMK_HEAVY_STREAM = 4,
	SMK_LINES = 5,
	SMK_FISHPOO = 6,
	SMK_TRANSIENTS,												//RJS 09Sep98
	SMK_TRACER													//RJS 10Nov98
};

enum	LightTimerTypes
{
	LGT_USER = 1,
	LGT_PERIODIC = 2,
	LGT_ONLY_DARK = 4
};

enum	WarpAxis
{
	AXIS_X = 0,
	AXIS_Y,
	AXIS_Z
};

enum	DeltaMask
{
	DMASK_NULL = 0,
	DMASK_Z,
	DMASK_Y,
	DMASK_Y_Z,
	DMASK_X,
	DMASK_X_Z,
	DMASK_X_Y,
	DMASK_X_Y_Z
};

enum	DamFX
{
	DAMFX_SPARKS = 0,
	DAMFX_SMOKE,
	DAMFX_JUNK
};

enum	ForceFlags
{
	FORCE_SET = 0,
	FORCE_LEVEL1 = 0,
	FORCE_LEVEL2 = 1,
	FORCE_LEVEL3 = 2,
	FORCE_LEVEL4 = 3
};

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//						   SHAPE INSTRUCTION EQUATES
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴

enum	SHPINST	{dopointno	=	1,
				 dopolygonno,
				 dosetlcno,
				 dosetcolourno,
				 dolineno,
				 doretno,
				 doifcrossno,
				 dogosubno,
				 doifeqno,
				 doifneno,
				 donopno,
				 dogroupno,
				 dogotono,
				 doendno,
				 dowindowdialno,								//RJS 06Apr98
				 doattitudeno,									//RJS 01Apr98
				 dodotno,
				 doscalesizeno,									//RJS 03Mar98
				 dogunsightno,									//RJS 04Mar98
				 dowheelsprayno,								//RJS 16Mar98
				 doifbrightno,									//RJS 20Mar98
				 doquikpolyno,
				 dofadeenvelopeno,								//RJS 27Mar98
				 dowhiteoutno,									//RJS 31Mar98
				 donpointsno,
				 don4cmpntsno,
				 do4cmpntno,
				 dondupvecno,									//RJS 29May98
				 dondeltapointsno,								//RJS 02Jun98
				 dodrawsunno,									//RJS 22Jun98
				 dosetcolour256no,
				 doswitchno,
				 dosetcolourallno,
				 dopoint2xno,
				 do4cmpt2xno,
				 doifcaseno,
				 donincpntsno,
				 dotransparentonno,
				 dotransparentoffno,
				 dosphereno,
				 dosmokedonno,
				 dosmokedoffno,
				 donormalno,
				 dosmoothpolyno,
				 dovectorno,
				 dotransformlightno,
				 dolshadeonno,								//RJS 30Apr98
				 dorelpolyno,
				 donspheresno,									//RJS 13Jul98
				 donspheresimapdno,								//RJS 13Jul98
				 doweaponoffno,									//RJS 13Jul98
				 dodrawreflectpolyno,							//RJS 26Aug98
				 doresetanimno,									//RJS 13Nov98
				 dospinno,										//RJS 19Nov98
				 dosetcolourhno,
				 doquiksmoothpolyno,
				 doreposno,
				 dodepthcolourno,
				 dodepthpolyno,
				 doimagemapno,
				 docreateipolyno,
				 docreateivertno,
				 dodrawipolyno,
				 docopyivertno,
				 dosmthrelpolyno,
				 doquikrelpolyno,
				 donsubsno,
				 dobitsofffxno,									//RJS 15Jan99
				 doondamagedno,									//RJS 18Jan99
				 dosetmipmapno,									//RJS 24May99
				 donvecno,
				 donextvecno,
				 donpoint2xno,
				 dummyentry,			
				 docallshapeno,
				 dosmokepntno,
				 dobitsoffno,
				 doplumepntno,
				 doisphereno,
				 docreaterpolyno,
				 dodrawipolysno,
				 domappolyno,
				 dosetmapmapno,
				 do3dbreakno,
				 docylinderno,
				 dontpointsno,
				 dosetmapoffno,
				 dosetmappingplanerno,
				 dosetmappingtanno,
				 dosmktrailno,
				 dooffsetpntno,
				 doicylinderno,
				 dodrawbetweenno,								
				 docreatebumppolyno,							
				 docopybvertno,									
				 dodrawbpolyno,									
				 dodrawrpolyno,									
				 dodrawopolyno,									
				 dorealisphereno,									
				 dolauncherno,									
				 dodialno,										
				 docompassno,									
				 doiswitchno,									
				 doinclnno,										
				 doanimationno,									
				 docollisionno,									
				 doeffectno,									
				 dodamageno,									
				 dodrawstationno,								
				 docaserangeno,									
				 doifpilotedno,									
				 donivertsno,									
				 dotrifanno,									
				 dotrizagno,									
				 dotrifanflatno,								
				 dotrizagflatno,								
				 dostretchpointno,								
				 dostretchmapno,								
				 doflipvectorno,								
				 doflipnvecno,									
				 domorphpointno,
				 domorphnpointsno,
				 douserealtimeno,
				 dotimerphaseno,
				 dobloblineno,
				 dowheeldamageno,
				 dolightno,
				 lightdatano,
				 dolighttimerno,
				 dodigitdialno,
				 donianimvertsno,									
				 dosetluminosityno,									
			 	 dobitsoffcockno,
			 	 domorphsphereno,
			 	 domorphcylinderimapdno,						//RJS 19Nov98
			 	 doheathazeno,
			 	 doifhard3dno,
			 	 domorphnsphrsno,										//RJS 04Feb98
			  	 domorphnsphrsimapdno,									//RJS 04Feb98
				 dosetglassrangeno
			};


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
typedef struct	_coords
{
	SWord	xcoord, ycoord, zcoord;
}
COORDS,
*COORDS_PTR;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
typedef struct _dopoint
{
	UWord	vertex;
	SWord	xcoord, ycoord, zcoord;
}
DOPOINT,
*DOPOINT_PTR;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
typedef struct _dopolygon
{
	UByte	edges;
}
DOPOLYGON,
*DOPOLYGON_PTR;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
typedef	struct _dosetlc
{
	UWord	colour;
}
DOSETLC,
*DOSETLC_PTR;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
typedef struct _dosetcolour
{
	SWord	flagname;											
	SWord	imageno;											
}
DOSETCOLOUR,
*DOSETCOLOUR_PTR;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
typedef struct _doline
{
	UWord	start_vertex,
			end_vertex;
}
DOLINE,
*DOLINE_PTR;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
typedef struct _doifcross
{
	UWord	vertex1,
			vertex2,
			vertex3;
	SWord	offset;
}
DOIFCROSS,
*DOIFCROSS_PTR;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
typedef struct _doifeq
{
	UWord	vertex1,
			vertex2,
			vertex3;
}
DOIFEQ,
*DOIFEQ_PTR;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
typedef struct _doifne
{
	UWord	vertex1,
			vertex2,
			vertex3;
}
DOIFNE,
*DOIFNE_PTR;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RJS 06Apr98 typedef struct _doifflag
//DeadCode RJS 06Apr98 {
//DeadCode RJS 06Apr98 	SWord	param1,
//DeadCode RJS 06Apr98 			param2;
//DeadCode RJS 06Apr98 }
//DeadCode RJS 06Apr98 DOIFFLAG,
//DeadCode RJS 06Apr98 DOIFFLAG_PTR;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
typedef struct _doattitude										//RJS 01Apr98
{																//RJS 01Apr98
	UByte	radius;												//RJS 01Apr98
	SWord	xpos, ypos, zpos;									//RJS 01Apr98
	SWord	imagemap;											//RJS 01Apr98
	UWord	animoffset;											//RJS 01Apr98
	SWord	minx, miny;											//RJS 01Apr98
	SWord	width, height;										//RJS 01Apr98
}																//RJS 01Apr98
DOATTITUDE,														//RJS 01Apr98
*DOATTITUDE_PTR;												//RJS 01Apr98

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
typedef	struct _dodot
{
	UByte	vertex;
	SWord	colour;
	SWord	imagemap;
	UByte	ix,iy;
}
DODOT,
*DODOT_PTR;

//DeadCode RJS 03Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RJS 03Mar98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RJS 03Mar98 typedef struct _dosmall
//DeadCode RJS 03Mar98 {
//DeadCode RJS 03Mar98 	UWord	vertex;
//DeadCode RJS 03Mar98 	SWord	xcoord, ycoord, zcoord;
//DeadCode RJS 03Mar98 }
//DeadCode RJS 03Mar98 DOSMALL,
//DeadCode RJS 03Mar98 *DOSMALL_PTR;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RJS 04Mar98 typedef struct _dotcolour
//DeadCode RJS 04Mar98 {
//DeadCode RJS 04Mar98 	UWord	colour;
//DeadCode RJS 04Mar98 }
//DeadCode RJS 04Mar98 DOTCOLOUR,
//DeadCode RJS 04Mar98 *DOTCOLOUR_PTR;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
typedef struct _dovdot
{
	SWord	xcoord, ycoord, zcoord;
}
DOVDOT,
*DOVDOT_PTR;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
typedef struct _dovdot4
{
	SWord	xcoord, ycoord, zcoord;
}
DOVDOT4,
*DOVDOT4_PTR;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
typedef struct _doquikpoly
{
	UByte	edges;
	UWord*	vertices;
}
DOQUIKPOLY,
*DOQUIKPOLY_PTR;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
typedef struct _donpoints
{
	UByte	vertex_count;										//RJS 03Jun98
	UWord	start_vertex;										//RJS 03Jun98
}
DONPOINTS,
*DONPOINTS_PTR;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
typedef struct _don4cmpnts
{
	UWord	start_vertex,
			vertex_count;
}
DON4CMPNTS,
*DON4CMPNTS_PTR;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
typedef struct _do4cmpnt
{
	UWord	vertex;
	SWord	xcoord, ycoord, zcoord;
}
DO4CMPNT,
*DO4CMPNT_PTR;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
typedef struct _dosetanim
{
	SWord	param1,param2,param3;
}
DOSETANIM,
*DOSETANIM_PTR;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
typedef struct _dosetcolour256
{
	UWord	basecolour;
	UByte	spread;
	UByte	imap;
}
DOSETCOLOUR256,
*DOSETCOLOUR256_PTR;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
typedef struct _doswitch							
{												
	UByte	animscale;											//RJS 13Mar98
	UWord	animoff;											//RJS 13Mar98
	SWord	value;												//RJS 13Mar98
	SByte	bitoffset;											//RJS 27May98
	UByte	nobits;												//RJS 27May98
	UByte	condition;											//RJS 13Mar98
	UByte	dummyret;											//RJS 13Mar98
}																//RJS 13Mar98
DOSWITCH,											
*DOSWITCH_PTR;									

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
typedef struct _dosetcolourall
{
	UByte	colour256;
	UByte	colour16;
	UByte	spread;
	UByte	shade256;
}
DOSETCOLOURALL,
*DOSETCOLOURALL_PTR;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
typedef struct _dopoint2x
{
	UWord	start_vertex;
	SWord	next_vertex_offset;
	SWord	xcoord, ycoord, zcoord;
}
DOPOINT2X,
*DOPOINT2X_PTR;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
typedef struct _do4cmpt2x
{
	UWord	start_vertex;
	SWord	next_vertex_offset;
	SWord	xcoord, ycoord, zcoord;
}
DO4CMPT2X,
*DO4CMPT2X_PTR;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
typedef struct _doifcase
{
	UByte	shiftup;											//RJS 14May98
	UWord	flag;
	UByte	count:7,											//RJS 14May98
			bidirectional:1;									//RJS 14May98
	UByte	factor;												
}
DOIFCASE,
*DOIFCASE_PTR;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
typedef struct _donincpnts
{
	UWord	start_vertex;
	UWord	count;
	UWord	flag;
}
DONINCPNTS,
*DONINCPNTS_PTR;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
typedef struct _doinit
{
	SWord	xcoord, ycoord, zcoord;
}
DOINIT,
*DOINIT_PTR;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
typedef struct _doinc
{
	SWord	delta_x, delta_y, delta_z;
}
DOINC,
*DOINC_PTR;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
typedef	struct _dosphere
{
	UByte	colour;
	UByte	animflag;
	UByte	animscale;
	UWord	vertex:11,
			transp:4,
			smooth:1;
	UWord	radius;
	UWord	halowidth:12,
			lumtype:4;
	UByte	animflag2;
}
DOSPHERE,
*DOSPHERE_PTR;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
typedef struct _donormal
{
	UWord	vertex;
	SWord	intensity;
}
DONORMAL,
*DONORMAL_PTR;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
typedef struct _dosmoothpoly
{
	UByte	edges;
	UWord*	vertices;
}
DOSMOOTHPOLY,
*DOSMOOTHPOLY_PTR;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
typedef struct _dovector
{
	SByte	an;
	UWord	vertex:15,
			ambientfiddle:1;
	SByte	bn,
			cn;
}
DOVECTOR,
*DOVECTOR_PTR;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
typedef struct _dorelpoly
{
	UByte	edges;
	UWord	start_vertex;
}
DORELPOLY,
*DORELPOLY_PTR;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
typedef struct _dospin											//RJS 19Nov98
{																//RJS 19Nov98
	UByte	pad;												//RJS 19Nov98
	UByte	animoff;											//RJS 19Nov98
	UByte	speedoff;											//RJS 19Nov98
	UWord	minspeed;											//RJS 19Nov98
	UWord	maxspeed;											//RJS 19Nov98
}																//RJS 19Nov98
DOSPIN,															//RJS 19Nov98
*DOSPIN_PTR;													//RJS 19Nov98

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
typedef struct _dosetcolourh
{
	UWord	colour;
}
DOSETCOLOURH,
*DOSETCOLOURH_PTR;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
typedef struct _doquiksmoothpoly
{
	UByte	edges;
	UWord*	vertices;
}
DOQUIKSMOOTHPOLY,
*DOQUIKSMOOTHPOLY_PTR;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
typedef struct _docreateipoly
{
	SWord	image_no;
}
DOCREATEIPOLY,
*DOCREATEIPOLY_PTR;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
typedef struct _docreateivert
{
	SWord	xcoord,
			ycoord,
			zcoord;
	UWord	image_x,
			image_y;
}
DOCREATEIVERT,
*DOCREATEIVERT_PTR;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
typedef struct _docopyivert
{
	UByte	vertex;
	UWord	image_x,
			image_y;
}
DOCOPYIVERT,
*DOCOPYIVERT_PTR;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
typedef struct _dosmthrelpoly
{
	UByte	edges;
	UWord	start_vertex;
	SByte*	offsets;
}
DOSMTHRELPOLY,
*DOSMTHRELPOLY_PTR;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
typedef struct _doquikrelpoly
{
	UByte	edges;
	UWord	start_vertex;
	SByte*	offsets;
}
DOQUIKRELPOLY,
*DOQUIKRELPOLY_PTR;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
typedef struct _donsubs
{
	UWord	count;
}
DONSUBS,
*DONSUBS_PTR;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
typedef struct _dobitsofffx										//RJS 15Jan99
{																//RJS 15Jan99
	UByte	fxtype;												//RJS 15Jan99
	UWord	animoff;											//RJS 15Jan99
	UWord	threshold;											//RJS 15Jan99
	SWord	xpos;												//RJS 15Jan99
	SWord	ypos;												//RJS 15Jan99
	SWord	zpos;												//RJS 15Jan99
}																//RJS 15Jan99
DOBITSOFFFX,													//RJS 15Jan99
*DOBITSOFFFX_PTR;												//RJS 15Jan99

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
typedef struct _doondamaged
{
	UByte	topthresh;
	UWord	animoff;
	SWord	thresh;
	UByte	pad;
	UByte	dummyret;
}
DOONDAMAGED,
*DOONDAMAGED_PTR;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
typedef struct _dosetmipmap										//RJS 24May99
{																//RJS 24May99
	UByte	textureflag;										//RJS 24May99
}																//RJS 24May99
DOSETMIPMAP,													//RJS 24May99
*DOSETMIPMAP_PTR;												//RJS 24May99

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
typedef struct _donvec
{
	UWord	vertex;
	UWord	count;
}
DONVEC,
*DONVEC_PTR;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
typedef struct _nextvec
{
	SByte	an,bn,cn;
}
NEXTVEC,
*NEXTVEC_PTR;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
typedef struct _donpoint2x
{
	UWord	start_vertex;
	UWord	count;
}
DONPOINT2X,
*DONPOINT2X_PTR;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
typedef struct _docallshape
{
	UWord	vertex;												
	UWord	shape;												
	UWord	hdg, pitch, roll;									
}
DOCALLSHAPE,
*DOCALLSHAPE_PTR;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
typedef struct _dosmokepnt
{
	UByte	flagoffset;											
	UByte	countoffset;										
	SWord	xcoord,												
			ycoord,												
			zcoord;												
	UWord	LifeTime;											
}
DOSMOKEPNT,
*DOSMOKEPNT_PTR;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
typedef struct _doisphere
{
	UByte	flagoffset;											
	UWord	vertex:15,									//RJS 20Feb98
			quadsphere:1;								//RJS 20Feb98
	SWord 	radius;												
	SWord	image;												
	SWord	minx;												
	SWord	miny;												
	SWord	width;										//RJS 11Feb98
 	SWord	height;										//RJS 11Feb98
	SWord	image2;										//RJS 11Feb98		
	UWord	framelimit:8,								//RJS 11Feb98
			animscale:8;								//RJS 11Feb98
	UWord	depthoffset;								//RJS 05May98
	UByte	angleoff;											//RJS 19Nov98
	UByte	fadeoff;											//RJS 27Nov98
}
DOISPHERE,													//RJS 10Feb98
*DOISPHERE_PTR;

//DeadCode RJS 16Dec97 typedef struct _doosphere										
//DeadCode RJS 16Dec97 {																
//DeadCode RJS 16Dec97 	UByte	flagoffset;											
//DeadCode RJS 16Dec97 	UWord	vertex;												
//DeadCode RJS 16Dec97 	SLong 	radius;												
//DeadCode RJS 16Dec97 	SWord	image;												
//DeadCode RJS 16Dec97 	SWord	minx;												
//DeadCode RJS 16Dec97 	SWord	miny;												
//DeadCode RJS 16Dec97 	SWord	maxx;												
//DeadCode RJS 16Dec97  	SWord	maxy;												
//DeadCode RJS 16Dec97 	SWord	width;												
//DeadCode RJS 16Dec97  	SWord	height;												
//DeadCode RJS 16Dec97 	UByte	factor;												
//DeadCode RJS 16Dec97 }																
//DeadCode RJS 16Dec97 DOOSPHERE,														
//DeadCode RJS 16Dec97 *DOOSPHERE_PTR;

typedef struct _dorealisphere
{
	UByte	flagoffset;
	SWord	animfactor;	
	SWord	image;												
	UWord	radius;
	UWord	minix;
	UWord	miniy;
	UWord	maxix;
	UWord	maxiy;
	UByte	vertex;
	UByte	morphanim;											//RJS 23Jan98
	UWord	growtime;											//RJS 23Jan98
	UWord	radius2;											//RJS 23Jan98
}																
DOREALISPHERE,														
*DOREALISPHERE_PTR;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
typedef struct _docreaterpoly
{
 	UByte	animscale;											//RJS 13Aug98
	UWord	animoff;											//RJS 13Aug98					
	SWord	imagemap;											//RJS 13Aug98
}
DOCREATERPOLY,
*DOCREATERPOLY_PTR;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
typedef struct _docylinder
{
	UByte	point0,
			point1;
	UWord	radius;
}
DOCYLINDER,
*DOCYLINDER_PTR;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
typedef struct _dontpoints
{
	UByte	count;												//RJS 23Jun98
	UWord	start_vertex:14,									//RJS 06Oct98
			notrpm:1,											//RJS 06Oct98
			isWord:1;											//RJS 06Oct98
	UWord	flag;												//RJS 23Jun98
	SWord	base_x,
			base_y,
			base_z;

	UByte	hpr_data;											
	UByte	fixedrpm;											
}
DONTPOINTS,
*DONTPOINTS_PTR;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
typedef struct _nextt
{
	SWord	xcoord,
			ycoord,
			zcoord,
			Txcoord,
			Tycoord,
			Tzcoord;
}
NEXTT,
*NEXTT_PTR;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
typedef struct _nnext
{
	SWord	xcoord,
			ycoord,
			zcoord;
}
NNEXT,
*NNEXT_PTR;

typedef struct _nnext2x
{
	SWord	vertex;

	SWord	xcoord,
			ycoord,
			zcoord;
}
NNEXT2X,
*NNEXT2X_PTR;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
typedef struct _dooffsetpnt
{
	UWord	vertex1;
	SWord	init_x,
			init_y,
			init_z;
	UByte	dummy;
	UWord	vertex2;
	SWord	xcoord,
			ycoord,
			zcoord;
}
DOOFFSETPNT,
*DOOFFSETPNT_PTR;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
typedef struct _doicylinder
{
	UByte	flagoffset;											
	UByte	point0,
			point1;
	UWord	radius;
	SWord	image;												
	UWord	min_ix,
			min_iy,
			max_ix,
			max_iy;
	UWord	width, height;										
	UByte	factor;
	UByte	framelimit;											//RJS 19Nov98
	SWord	image2;												//RJS 19Nov98
	UWord	fadeoff;											//RJS 27Nov98
}
DOICYLINDER,
*DOICYLINDER_PTR;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
typedef struct _dosetglassrange
{
	UByte	base,
			spread;
}
DOSETGLASSRANGE,
*DOSETGLASSRANGE_PTR;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
typedef struct _doreturn
{
}
DORET,
*DORET_PTR;

typedef struct	_dogosub
{
	SWord	offset;
}
DOGOSUB,
*DOGOSUB_PTR;

typedef struct	_dogoto
{
	SWord	offset;
}
DOGOTO,
*DOGOTO_PTR;

typedef struct _drawbetween										
{																
	UWord	offset;												
	SLong	mindist,maxdist;									
}																
DRAWBETWEEN,													
*DRAWBETWEEN_PTR;												

typedef	struct	_dogroup
{
	UByte	element_number;										
	UWord	shapenum;
	SLong	xoffset;											
	SWord	yoffset;											
	SLong	zoffset;											
	SWord	angle;												
	UWord	tokendepanim:13,
			tokenflag:3;
	SByte	element_prev;								
	SByte	element_next;
	SByte	element_parent;
	SLong	range_min;
	SLong	range_max;
}
DOGROUP,
*DOGROUP_PTR;

typedef	struct	_donop
{
}
DONOP,
*DONOP_PTR;

typedef	struct	_doend
{
}
DOEND,
*DOEND_PTR;

typedef	struct	_doradar
{
}
DORADAR,
*DORADAR_PTR;

typedef	struct	_donoradar
{
}
DONORADAR,
*DONORADAR_PTR;

typedef	struct	_dondeltapoints									//RJS 02Jun98
{
	UByte	count;
	UWord	vertex:13,
			mask:3;
	UWord	scale;												//RJS 24May99
	SWord	offset;												//RJS 24May99
}
DONDELTAPOINTS,
*DONDELTAPOINTS_PTR;											//RJS 02Jun98

typedef	struct	_dotextureoff
{
}
DOTEXTUREOFF,
*DOTEXTUREOFF_PTR;

typedef	struct	_dotransparentoff
{
}
DOTRANSPARENTOFF,
*DOTRANSPARENTOFF_PTR;

typedef	struct	_dotransparenton
{
	UByte	depth;
}
DOTRANSPARENTON,
*DOTRANSPARENTON_PTR;

typedef	struct	_dosmokedon
{
}
DOSMOKEDON,
*DOSMOKEDON_PTR;

typedef	struct	_dosmokedoff
{
}
DOSMOKEDOFF,
*DOSMOKEDOFF_PTR;

typedef	struct	_dotransformlight
{
}
DOTRANSFORMLIGHT,
*DOTRANSFORMLIGHT_PTR;

//DeadCode RJS 30Apr98 typedef	struct	_doicon
//DeadCode RJS 30Apr98 {
//DeadCode RJS 30Apr98 }
//DeadCode RJS 30Apr98 DOICON,
//DeadCode RJS 30Apr98 *DOICON_PTR;

typedef	struct	_dodrawipoly
{
	UByte	nopoints;											
}
DODRAWIPOLY,
*DODRAWIPOLY_PTR;

typedef	struct	_dodrawopoly									
{																
}																
DODRAWOPOLY,													
*DODRAWOPOLY_PTR;												

typedef	struct	_dodrawrpoly									
{
	SWord	flag;
	UByte	nopoints;											
}
DODRAWRPOLY,
*DODRAWRPOLY_PTR;

typedef	struct	_dodrawipolys
{
}
DODRAWIPOLYS,
*DODRAWIPOLYS_PTR;

typedef	struct	_doplumepnt
{
	SWord	imagemap;
	UByte	width,height;
	UByte	rangefar:1,
			sphereframe:3,										
			justspheres:1;
}
DOPLUMEPNT,
*DOPLUMEPNT_PTR;

typedef	struct	_dosetmappingplaner
{
}
DOSETMAPPINGPLANER,
*DOSETMAPPINGPLANER_PTR;

typedef	struct	_dosetmappingtan
{
}
DOSETMAPPINGTAN,
*DOSETMAPPINGTAN_PTR;

typedef struct _docreatebumppoly								//PD 15Jan96
{
	SWord	bump_no,
			image_no;
}
DOCREATEBUMPPOLY,
*DOCREATEBUMPPOLY_PTR;

typedef struct _docopybvert										//PD 15Jan96
{
	UWord	vertex;
	SWord	image_x,image_y;
}
DOCOPYBVERT,
*DOCOPYBVERT_PTR;

typedef struct _dodrawbpoly										//PD 15Jan96
{
}
DODRAWBPOLY,
*DODRAWBPOLY_PTR;

typedef struct _dodrawcloud										//PD 22Jan96
{
	SWord	bump_no,
			image_no;
}
DODRAWCLOUD,
*DODRAWCLOUD_PTR;

typedef	struct
{
	SWord			launchtime,
					stores;
	void*			WeapPtr;
	void*			DetectRtn;
}
LnchrInst,*LnchrInstP;

typedef	struct
{
	UWord		shape;
	LnchrInst	launcher;
}
Shp2Lnchr, *Shp2LnchrP;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴

typedef	struct
{
	UByte	lnchrtype;											//RJS 28Jan98
	SWord	posx,posy,posz;										//RJS 28Jan98
	SByte	trailtype;											//RJS 28Jan98
	UByte	damthresh;											//RJS 02Apr98
	UWord	damageflag;											//RJS 31Mar98
	UWord	TransLauncher;										//RJS 02Apr98
}
DOLAUNCHER,
*DOLAUNCHER_PTR;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴

typedef	struct
{
	UByte	radius;												//RJS 29Jan98
	UWord	animflag;											//RJS 29Jan98
	SWord	xpos, ypos, zpos;									//RJS 29Jan98
	SWord	startangle,											//RJS 29Jan98
			endangle;
	UWord	radius2:10,
			flagsize:6;
	SLong	arc:31,												//RJS 11Feb98
			fatneedle:1;										//RJS 11Feb98
	SWord	scale;
}
DODIAL,
*DODIAL_PTR;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴

typedef	struct
{
	SWord	vertex1,vertex2;
	SWord	vertex3,vertex4;
	SWord	imageno;
	SWord	width,height;
}
DOCOMPASS,
*DOCOMPASS_PTR;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴

typedef	struct
{
	SWord	imageno;
	SWord	posx,
			posy;
	SWord	onimage,
			offimage;
}
DOISWITCH,
*DOISWITCH_PTR;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴

typedef	struct
{
	UByte	radius;												//RJS 12Feb98
	UWord	animoffset;											//RJS 12Feb98
	SWord	xpos, ypos, zpos;									//RJS 12Feb98
	SWord	imagamap;
	UByte	minx,miny;
	UByte	maxx,maxy;
}
DOINCLN,
*DOINCLN_PTR;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴

typedef	struct	_dosmktrail										
{																
	UByte	ShadeVariation;
	SWord	Imagemap;											
	UByte	Width,Height;										
	SLong	FadeDist;											
	SWord	Colour;												
	UByte	TrailType:5,
			MaxTransparency:3;
	UByte	Density;
	SWord	MinIx,MinIy;
	SWord	Imagemap2;											
	UByte	framelimit;
	UByte	width2,height2;
	UByte	noframes;											//RJS 24Nov98
	UWord	frametime;											//RJS 24Nov98
	UByte	minix2,miniy2;										//RJS 25Nov98
}																
DOSMKTRAIL,														
*DOSMKTRAIL_PTR;												

typedef struct _dobitsoff
{
	UByte	shitpad;
	UWord	animoff;			
	SWord	dam1offset,		
			dam2offset,
			deadoffset;											//RJS 31Mar98
	UByte	dummyret;		
}
DOBITSOFF,
*DOBITSOFF_PTR;

typedef struct _dobitsoffcock
{
	UByte	bitflag;			
	UWord	animflag;			
	UWord	offset;
}
DOBITSOFFCOCK,
*DOBITSOFFCOCK_PTR;

typedef struct _doanimation
{
	UByte		maxframes;
	UWord		flagoffset;
	UByte		toggleoffset;
	UByte		timeroffset;
	UByte		loopoffset;
	UByte		maxaction:3,									
				increment:2,									
				activatenow:3;									
	UWord		damageoffset:15,
				damagetoggle:1;
	UByte		fadeoffset;
	UByte		maxfadeframes;
	UByte		fadedepth;
}
DOANIMATION,
*DOANIMATION_PTR;

typedef struct _docollision
{
	UByte		shitpad;
	UWord		flagoffset;
	SWord		xoff, yoff, zoff;
	UWord		sx, sy, sz;
	UWord		radius;
	UWord		succeed;
	UWord		fail;
}
DOCOLLISION,
*DOCOLLISION_PTR;

typedef struct _doeffect
{
	UByte		levelactive;
	UWord		flagoffset:13,
				damagetype:3;
	UWord		type:3,
				stationno:4,
				damindexold:3,
				damindexnew:3;
	UWord		enumvalue;
	UWord		randomdelta;
}
DOEFFECT,
*DOEFFECT_PTR;

typedef struct _dodamage
{
	UByte		increment;
	UWord		flagoffset;
	UByte		isfatal:1,										
				isejected:1,									
				stationno:4,
				setinvisible:1;									//RJS 22Nov98
	UByte		veloffset;
	ULong		vulnerability;									//RJS 29Jun98
}
DODAMAGE,
*DODAMAGE_PTR;

typedef struct _dodrawstation
{
	UByte		stationno;
}
DODRAWSTATION,
*DODRAWSTATION_PTR;

typedef struct _docaserange
{
	UByte	flag;
	UByte	nofields:7,											
			useword:1;											
	UByte	factor;												
	SWord	failjump;											
}
DOCASERANGE,
*DOCASERANGE_PTR;

typedef struct _doifpiloted
{
	UWord	offset;
}
DOIFPILOTED,
*DOIFPILOTED_PTR;

typedef struct _doniverts
{
	UByte	vertex;
	UByte	count;
}
DONIVERTS,
*DONIVERTS_PTR;

typedef struct nextmap
{
	UWord	ix;
	UWord	iy;
}
NEXTMAP,
*NEXTMAP_PTR;

typedef struct _dotrifan
{
	UByte	rootpnt;
	SWord	material;
	UByte	edges;
}
DOTRIFAN,
*DOTRIFAN_PTR;

typedef struct _dotrizag
{
	SWord	material;
 	UByte	direction:1,
			edges:7;
}
DOTRIZAG,
*DOTRIZAG_PTR;

typedef struct _dotrifanflat
{
	UByte	rootpnt;
	SWord	material;
	UByte	xprodp1;
	UByte	xprodp2;
	UByte	xprodp3;
	UByte	edges;
}
DOTRIFANFLAT,
*DOTRIFANFLAT_PTR;

typedef struct _dotrizagflat
{
	SWord	material;
	UByte	xprodp1;
	UByte	xprodp2;
	UByte	xprodp3;
 	UByte	direction:1,
			edges:7;
}
DOTRIZAGFLAT,
*DOTRIZAGFLAT_PTR;

typedef struct _dostretchpoint
{
	UByte	killflag;
	UByte	minpoint,
			maxpoint,
			outpoint;
}
DOSTRETCHPOINT,
*DOSTRETCHPOINT_PTR;

typedef struct _dostretchmap
{
	UByte	killflag;
	UByte	minpoint,
			maxpoint,
			outpoint;
}
DOSTRETCHMAP,
*DOSTRETCHMAP_PTR;

typedef struct _doflipvector									
{																
	SWord	vertex;												
}																
DOFLIPVECTOR,													
*DOFLIPVECTOR_PTR;												

typedef struct _doflipnvec										
{																
	SWord	vertex;												
	SWord	nopoints;											
}																
DOFLIPNVEC,														
*DOFLIPNVEC_PTR;

typedef struct _domorphpoint									//RJS 04Dec97
{																
	UByte	framecntoffset;
	UWord	vertex:15,
			haswind:1;
	SWord	xcoord, ycoord, zcoord;
	SWord	mxcoord, mycoord, mzcoord;
	UWord	growtime;
}																
DOMORPHPOINT,														
*DOMORPHPOINT_PTR;												//RJS 04Dec97

typedef struct _domorphnnext							
{
	SWord	mxcoord, mycoord, mzcoord;
	SWord	xcoord, ycoord, zcoord;
}																
MORPHNNEXT,														
*MORPHNNEXT_PTR;

typedef struct _domorphnpoints							
{
	UByte	framecntoffset;
	UWord	startvertex:15,
			haswind:1;
	UWord	growtime;
	UByte	nopoints;
}																
DOMORPHNPOINTS,														
*DOMORPHNPOINTS_PTR;

typedef struct _douserealtime							
{
	UByte	birthtimeoffset;
}																
DOUSEREALTIME,														
*DOUSEREALTIME_PTR;

typedef struct _dotimerphase
{
	UByte	birthtimeoffset;
	UByte	deltatimeoffset;
	UByte	nophases;
}																
DOTIMERPHASE,														
*DOTIMERPHASE_PTR;

typedef struct _tphasestep
{
	UWord	timedelta;
	UWord	objjump;
}																
TPHASESTEP,	
*TPHASESTEP_PTR;

typedef struct _doblobline
{
	UWord	start_vertex,
			end_vertex;
	UWord	maxradius;
}
DOBLOBLINE,
*DOBLOBLINE_PTR;

typedef struct _dowheeldamage
{
	UByte	threshold;
	UWord	suspoffset;
	UWord	underoffset;
	UWord	damageoffset;
	UWord	subdamageoffset;
	UByte	animmax;
}
DOWHEELDAMAGE,
*DOWHEELDAMAGE_PTR;

typedef struct _dolight
{
	UByte	animoff;
	UWord	lightoffset:6,
			radius:9,
			isword:1;
	UWord	timeoff;
	UWord	timeup;
	UWord	timeon;
	UWord	imagemap;
	UByte	minx;
	UByte	miny;
	UWord	width;
	UWord	height;
}
DOLIGHT,
*DOLIGHT_PTR;

typedef struct _lightdata
{
	SWord	xpos, ypos, zpos;
	SWord	spotxpos, spotypos, spotzpos;
	UByte	colouron;
	UByte	colouroff;
}
LIGHTDATA,
*LIGHTDATA_PTR;

typedef struct _dolighttimer
{
	UByte	animoff;
	UWord	duration;
	UByte	timertype;
	UByte	isword;
}
DOLIGHTTIMER,
*DOLIGHTTIMER_PTR;

typedef struct _dodigitdial
{
	UByte	nodigits;
	UWord	animoff;
	SWord	imagemap;
	UByte	width, height;
	SWord	vertex0,vertex1;
	SWord	vertex2,vertex3;
}
DODIGITDIAL,
*DODIGITDIAL_PTR;

typedef struct _donianimverts
{
	UByte	vertex;										
	UByte	count;										
	UWord	animoff:9,											//RJS 13Aug98
			noxframes:6,										//RJS 13Aug98
			isthresh:1;											//RJS 13Aug98
	UByte	factor;												//RJS 13Aug98
	UByte	framewx, framewy;									//RJS 13Aug98
	UByte	mapscale;											//RJS 13Aug98
}
DONIANIMVERTS,
*DONIANIMVERTS_PTR;

typedef struct _dosetluminosity
{
	UByte	animoff;
	UByte	brightness;
	UByte	animscale;
}
DOSETLUMINOSITY,
*DOSETLUMINOSITY_PTR;

typedef	struct _domorphsphere
{
	UByte	colour;
	UByte	animflag;
	UByte	animscale;
	UWord	vertex:11,
			transp:4,
			smooth:1;
	UWord	radius;
	UWord	halowidth:12,
			lumtype:4;
	UByte	MrphAnim;											
	UWord	MrphGrowtime;										
	UWord	MrphRadius:12,
			MrphTransp:4;										
	UWord	MrphColour:12,
			MrphLumtype:4;
}
DOMORPHSPHERE,
*DOMORPHSPHERE_PTR;

typedef	struct _domorphcylinderimapd
{
	UByte	animflag;
	UByte	animscale;
	UByte	lumtype:4,
			MrphLumtype:4;
	UWord	radius;
	UByte	transp:4,
			smooth:1;
	UByte	MrphAnim;											
	UWord	MrphGrowtime;										
	UWord	MrphRadius:12,
			MrphTransp:4;
	UByte	vertex1;
	UByte	vertex2;
	SWord	imap1;
	SWord	imap2;
	UByte	framelimit;
	UByte	fadeoff;											//RJS 27Nov98
	SWord	min_ix,min_iy;
	SWord	width,height;
}
DOMORPHCYLINDERIMAPD,
*DOMORPHCYLINDERIMAPD_PTR;

typedef struct _doheathaze
{
	UByte	colour;
	UByte	animflag;
	UByte	animscale;
	SWord	image;												//RJS 22Jun98
	UByte	minx,miny;											//RJS 22Jun98
	UByte	width,height;										//RJS 22Jun98
	UWord	vertex;
	UWord	radius;
}
DOHEATHAZE,
*DOHEATHAZE_PTR;

typedef struct _doifhard3d
{
	UWord	offset;
}
DOIFHARD3D,
*DOIFHARD3D_PTR;

typedef	struct _domorphnsphrs
{
	UByte	colour;
	UByte	animflag;
	UByte	animscale;
	UWord	vertex:11,
			transp:4,
			smooth:1;
	UByte	lumtype:4,
			MrphTransp:4;										
	UByte	MrphAnim;											
	UWord	MrphGrowtime;										
	UWord	MrphColour:12,
			MrphLumtype:4;
	UWord	count;
}
DOMORPHNSPHRS,
*DOMORPHNSPHRS_PTR;

typedef	struct _domorphnsphrsimapd
{
	UByte	animflag;
	UByte	animscale;
	UByte	count;
	UWord	vertex:10,											//RJS 26Nov98
			transp:4,											//RJS 26Nov98
			smooth:1,											//RJS 26Nov98
			pivoted:1;											//RJS 26Nov98
	UByte	lumtype:4,
			MrphTransp:4;										
	UByte	MrphAnim;											
	UWord	MrphGrowtime;										
	UWord	SwitchImagemap;
	UWord	imagemap;
	UByte	MrphLumtype:4,
			framelimit:4;
	UByte	minix, miniy;
	UByte	ix, iy;
	UByte	spinoff;											//RJS 19Nov98
	UByte	fadeoff;											//RJS 27Nov98
}
DOMORPHNSPHRSIMAPD,
*DOMORPHNSPHRSIMAPD_PTR;

typedef struct _morphsphnext
{
	UWord	radius;
	UWord	MrphRadius;
}
MORPHSPHNEXT,
*MORPHSPHNEXT_PTR;

typedef struct _doscalesize
{
	UByte	animoffsrc;
	UByte	animoffdest;
	UWord	animscale;
}
DOSCALESIZE,
*DOSCALESIZE_PTR;

typedef struct _dogunsight
{
	UByte	nopoints;
	SWord	imap;												//RJS 24Mar99
	SWord	posx;
	SWord	posy;
	SWord	posz;
}
DOGUNSIGHT,
*DOGUNSIGHT_PTR;

typedef struct _dowheelspray
{
	SWord	xcoord, ycoord, zcoord;
	UWord	animflag;											//RJS 28May98
}
DOWHEELSPRAY,
*DOWHEELSPRAY_PTR;

typedef struct _doifbright										//RJS 20Mar98
{
	UByte	nopoints;
	SWord	threshold;
	UWord	offset;
}
DOIFBRIGHT,
*DOIFBRIGHT_PTR;												//RJS 20Mar98

typedef struct _dofadeenvelope									//RJS 30Mar98
{
	UByte	birthtimeoffset;
	UByte	animfadeoffset;
	UWord	attacktime;
	UWord	decaytime;
	UWord	sustaintime;
	UWord	releasetime;
	UByte	attackval;
	UByte	decayval;
	UByte	sustainval;
	UByte	releaseval;
}
DOFADEENVELOPE,
*DOFADEENVELOPE_PTR;

typedef struct _dowhiteout										//RJS 31Mar98
{
	UByte	pad;
	SLong	fadedist;
}
DOWHITEOUT,
*DOWHITEOUT_PTR;												//RJS 31Mar98

typedef struct _dowindowdial									//RJS 06Apr98
{
	UByte	shiftx:4,
			shifty:4;
	UWord	animoffset:12,										//RJS 03Nov98
			nobytes:3,											//RJS 03Nov98
			issigned:1;											//RJS 03Nov98
	UWord	imagemap;											//RJS 03Nov98
	SWord	minx, miny;
	SWord	width;
	SWord	height;
	SWord	winwidth;											//RJS 26May98
	SWord	winheight;											//RJS 26May98
}
DOWINDOWDIAL,
*DOWINDOWDIAL_PTR;												//RJS 06Apr98

typedef struct _dolshadeon
{
	UByte	surfacetype;
}
DOLSHADEON,
*DOLSHADEON_PTR;

typedef struct _dondupvec
{
	UByte	vertex;
	UByte	count:7,
			ambientfiddle:1;
	SByte	an,
			bn,
			cn;
}
DONDUPVEC,
*DONDUPVEC_PTR;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
typedef struct _ndnext3
{
	SByte	delta[3];
}
NDNEXT3,
*NDNEXT3_PTR;

typedef struct _ndnext2
{
	SByte	delta[2];
}
NDNEXT2,
*NDNEXT2_PTR;

typedef struct _ndnext1
{
	SByte	delta;
}
NDNEXT1,
*NDNEXT1_PTR;

typedef struct _dodrawsun										//RJS 22Jun98
{
	UByte	animoffset;
	SWord	image;
	UWord	radius;
	UWord	animscale;
	UByte	minx;
	UByte	miny;
	UByte	width;
	UByte	height;
	UByte	hazeanim;
	UByte	hazescale;
	SWord	hazeimage;
	UByte	hazeminx;
	UByte	hazeminy;
	UByte	hazewidth;
	UByte	hazeheight;
}
DODRAWSUN,
*DODRAWSUN_PTR;													//RJS 22Jun98

typedef	struct _donspheres										//RJS 13Jul98
{
	UByte	colour;
	UByte	animflag;
	UByte	animscale;
	UWord	vertex:11,
			transp:4,
			smooth:1;
	UWord	count:12,
			lumtype:4;
}
DONSPHERES,
*DONSPHERES_PTR;												//RJS 13Jul98

typedef	struct _donspheresimapd
{
	UByte	animflag;
	UByte	animscale;
	UByte	count;
	UWord	vertex:11,
			transp:4,
			smooth:1;
	UByte	lumtype;
	UWord	imagemap:11,
			framelimit:5;
	UByte	minix, miniy;
	UByte	ix, iy;
}
DONSPHERESIMAPD,
*DONSPHERESIMAPD_PTR;

typedef struct _spherenext
{
	UWord	radius;
}
SPHERENEXT,
*SPHERENEXT_PTR;

typedef	struct _doweaponoff										//RJS 13Jul98
{
	UByte	pad;
	UByte	launchertype;
	UByte	storesoffset;
	UByte	launchoffset;
	UByte	dummyret;		
}
DOWEAPONOFF,
*DOWEAPONOFF_PTR;												//RJS 13Jul98

typedef	struct	_dodrawreflectpoly
{
	UByte	nopoints;											
}
DODRAWREFLECTPOLY,
*DODRAWREFLECTPOLY_PTR;

typedef	struct	_doresetanim									//RJS 13Nov98
{
	UByte	animofftimer;											
	UByte	animoffframe;
	UByte	resetval;
}
DORESETANIM,
*DORESETANIM_PTR;												//RJS 13Nov98


#endif
