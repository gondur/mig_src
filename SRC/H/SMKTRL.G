//------------------------------------------------------------------------------
//Filename       smktrl.g
//System
//Author         Shape-Make Utility (Bionic Version)
//Date           Tue 16 Sep 1997
//Description
//------------------------------------------------------------------------------
#ifndef	SMKTRL_Included
#define	SMKTRL_Included

#define	DEFAULT_SMKTRL 0

typedef struct	smktrltype
{
	ShapeNum	Shape;
	ULong		LifeTime;
	UWord		DegradeDist;
	SWord		Growth;
	UByte		Radius;
	ShapeNum	DetachShape;
	SWord		SampleTime;
	SWord		VelHori;
	SWord		VelY;
	UByte		Resistance;
	UByte		Depth;
	UByte		MaxPoints;
	SmkDeath	DeadAction;
	ShapeNum	CloudShape;
	ShapeNum	FadeShape;
	ULong		FadeTime;
}
SmokeType, *SmokeTypeP;

enum SmokeTrailDefs
{
	TRAIL_CONTRAIL = 0,
	TRAIL_ROCKET = 1,
	TRAIL_VAPOUR = 2,
	TRAIL_ESMOKE = 3,
	TRAIL_FSMOKE = 4,
	TRAIL_DUSTY = 5,
	TRAIL_FINGERSMK = 6,
	TRAIL_DUDCONTRAIL = 7,
	TRAIL_SCONTRAIL1 = 8,
	TRAIL_SCONTRAIL2 = 9,
	TRAIL_MUDSPLASH = 10,
	TRAIL_WINGVAP = 11,
	TRAIL_TRAINSMOKE = 12,
	TRAIL_BIGFIRE = 13,
	TRAIL_JETDUST = 14,
	TRAIL_WATERY = 15,
	TRAIL_WRECK = 16,
	TRAIL_FINGERDUST = 17,
	TRAIL_ENGINEPLUME = 18,
	TRAIL_EXHAUST = 19,
	TRAIL_EXHAUSTDIRTY = 20,
	TRAIL_NAPALM = 21
};

static SmokeType	SmokeTrlList[] =
{
	{VSCON,6000,1875,500,60,SMKSHP,0,0,0,100,255,64,DEADSMK_DEFAULT,(ShapeNum)0,(ShapeNum)0,0},
	{VSROCK,100,1875,20,16,SMKSHP,0,0,0,100,191,64,DEADSMK_DEFAULT,(ShapeNum)0,(ShapeNum)0,0},
	{VSVAP,80,1875,1000,8,SMKSHP,0,0,0,100,128,64,DEADSMK_DEFAULT,(ShapeNum)0,(ShapeNum)0,0},
	{VSFSMK,400,1250,40,80,SMKSHP,0,0,1000,64,255,24,DEADSMK_SMOKECLOUD,(ShapeNum)0,(ShapeNum)0,0},
	{VSBSMK,80,1875,5,24,SMKSHP,0,0,0,100,255,64,DEADSMK_DEFAULT,(ShapeNum)0,(ShapeNum)0,0},
	{VSDUST,80,937,30,200,SMKSHP,0,0,0,100,255,64,DEADSMK_DEFAULT,(ShapeNum)0,(ShapeNum)0,0},
	{VSFSMK,200,1250,80,80,(ShapeNum)0,0,0,0,100,191,64,DEADSMK_DEFAULT,(ShapeNum)0,(ShapeNum)0,0},
	{VSCON,6000,1875,500,24,(ShapeNum)0,0,0,0,100,255,64,DEADSMK_DEFAULT,(ShapeNum)0,(ShapeNum)0,0},
	{VSCON,6000,1875,500,24,SMKSHP,0,0,0,100,255,64,DEADSMK_DEFAULT,(ShapeNum)0,(ShapeNum)0,0},
	{VSSCON,6000,1875,500,144,SMKSHP,0,0,0,100,255,64,DEADSMK_DEFAULT,(ShapeNum)0,(ShapeNum)0,0},
	{VSMUD,200,1875,1,100,(ShapeNum)0,0,0,0,100,255,64,DEADSMK_DEFAULT,(ShapeNum)0,(ShapeNum)0,0},
	{VSWVAP,5,1875,1000,4,(ShapeNum)0,0,0,0,100,63,64,DEADSMK_DEFAULT,(ShapeNum)0,(ShapeNum)0,0},
	{VSCON,600,1250,40,80,(ShapeNum)0,50,0,50,100,255,64,DEADSMK_DEFAULT,(ShapeNum)0,(ShapeNum)0,0},
	{VSFSMK,800,1250,40,200,SMKSHP,50,50,100,64,255,64,DEADSMK_DEFAULT,(ShapeNum)0,(ShapeNum)0,0},
	{VSDUST,400,937,10,200,SMKSHP,20,0,0,100,255,64,DEADSMK_DEFAULT,(ShapeNum)0,(ShapeNum)0,0},
	{VSWATR,80,937,30,200,SMKSHP,0,0,0,100,191,64,DEADSMK_DEFAULT,(ShapeNum)0,(ShapeNum)0,0},
	{VSBSMK,40,625,5,100,SMKSHP,0,0,0,100,255,64,DEADSMK_DEFAULT,(ShapeNum)0,(ShapeNum)0,0},
	{VSDUST,250,1250,5,60,(ShapeNum)0,0,0,0,100,255,64,DEADSMK_DEFAULT,(ShapeNum)0,(ShapeNum)0,200},
	{VSTRAC,300,3125,10,60,SMKSHP,0,0,0,100,255,64,DEADSMK_DEFAULT,(ShapeNum)0,(ShapeNum)0,125},
	{VSEHST,200,3125,10,60,SMKSHP,0,0,0,100,24,64,DEADSMK_DEFAULT,(ShapeNum)0,(ShapeNum)0,0},
	{VSEHST,200,3125,10,60,SMKSHP,0,0,0,100,32,64,DEADSMK_DEFAULT,(ShapeNum)0,(ShapeNum)0,0},
	{VSGSMK,100,3125,40,30,(ShapeNum)0,0,0,0,100,255,64,DEADSMK_DEFAULT,(ShapeNum)0,(ShapeNum)0,0}
};

#endif

