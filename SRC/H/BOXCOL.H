//------------------------------------------------------------------------------
//Filename       boxcol.h
//System         
//Author         R. Hyde 
//Date           Tue 26 Nov 1996
//Description    
//------------------------------------------------------------------------------
#ifndef	BOXCOL_Included
#define	BOXCOL_Included

#define	DEFAULT_BOXCOL 0

#define	MaxEffects	32											//RJS 06Jun99
typedef	struct	EFFECTLINETYPE									//RJS 26Feb97
{															
	UByte		level;										
	UByte		type;										
	UWord		effectno;									
	UWord		randval;									
	UByteP		weapptr;									
	SByte		pointindex;										//RJS 29Jun99
	SByte		grpindex;
	UWord		hitshape;										//RJS 16Nov98
}EffectLine;

struct	HitEffectRecord											//RJS 18Jan99
{
	Coords3D	hitCoords;
	SLong		val;
	SLong		randval;
	UByteP		weapptr;
	Coords3D	hitterCoords;
	Coords3D	grpCoords;
	SLong		damagestrength;
	SByte		groupindex;
	UWord		animdamageoffset;								//RJS 10Feb99
	ItemPtr		theShooter;										//JIM 11Mar99
};

#ifndef	NDEBUG

#define AFX_CDECL __cdecl
typedef char CHAR;
#define CONST               const
typedef CONST CHAR *LPCSTR, *PCSTR;
typedef LPCSTR LPCTSTR;
void AFX_CDECL AfxTrace(LPCTSTR lpszFormat, ...);

#endif


class BoxCol
{
public:
	static  Coords3D	colpos_hitgrp;							//RJS 27Feb97
	static	Coords3D	colpos_hititem;							//RJS 27Feb97
	static	Coords3D	colpos_impact;							//RJS 27Feb97
	Coords3D	hitter_start, hitter_end;						//RJS 26Feb97
	static	Coords3D*	TPos1;									//RJS 26Feb97
	static	Coords3D*	TPos2;									//RJS 26Feb97
	static	Coords3D*	LastTSize;								//RJS 01Dec98
	static	int			TTrgSize;								//RJS 26Feb97
	static	int			TSizeMul;								//RJS 26Feb97
	static	int			HitterStrength;							//RJS 06Mar97
	static	UByte		HitterDamageType;						//RJS 22Jan98

	static  EffectLine	EffectQueue[MaxEffects];				//RJS 26Feb97
	static  int			EffectCnt;								//RJS 26Feb97

	static	ItemPtr		Col_Shooter;							//JIM 11Mar99
	static	ItemPtr		Col_Hitter;								//RJS 07Mar97
	static	int			Col_GroupElement;						//RJS 27Feb98
	static	UByteP		Col_GroupSdptr;							//RJS 27Feb98
	static	animptr		Col_AnimPtr;							//RJS 27Feb98
	static	animptr		Col_AnimNextPtr;						//RJS 02Mar98
	static	animptr		Col_AnimPrevPtr;						//RJS 02Mar98
	static	SLong		Col_PrevDep;							//RJS 02Mar98
	static	SLong		Col_NextDep;							//RJS 02Mar98
	static  UByteP		Col_GroupPrev;
	static  UByteP		Col_GroupNext;
	static	SLong		StaticHitterSize;						//RJS 03Mar98
	static	ShapeDescPtr	StaticTrgSdptr;						//RJS 03Mar98
	static  Bool		Col_ExplodeIt;							//RJS 30Mar98
	static	animptr		Col_TokenDepAnim;						//RJS 12Feb99
	static	SLong		noGuns;									//RJS 29Mar99
	static	UWord		Col_HitShape;							//RJS 20May99
	static	MATRIX		frame1inverse_matrix;					//RJS 15Jun99
	static	Bool		matrixset;								//RJS 15Jun99
	static	SLong		StaticHitterSizeSingle;					//RJS 15Jun99
	static	SLong		pointindex;								//RJS 29Jun99
	static	Coords3D	colpos_list[MaxEffects];				//RJS 29Jun99
	static	SLong		ShoveX;									//RJS 29Jun99
	static	SLong		ShoveY;									//RJS 29Jun99
	static	SLong		ShoveZ;									//RJS 29Jun99

	int			hitter_size;

	static	ItemPtr NineSectorCol(MobileItemPtr hitter,Coords3D& hitpos,int& eltnum);
	static	ItemPtr SectorCol(MobileItemPtr hitter,ItemPtr trg,Coords3D& hitpos,int& eltnum,Bool,TransientItem*,Bool);//RJS 27May99
	static	Bool GroupCol(MobileItemPtr hitter,ItemPtr trg,Coords3D& hitpos,int& eltnum,TransientItem*,Bool);//RJS 27May99
	static	Bool TestCol(MobileItemPtr hitter,ItemPtr,ItemPtr,Coords3D& hitpos,TransientItem*,Bool);//RJS 27May99
//DeadCode RJS 01Dec97 	static	Bool TestCol2(DOCOLLISION_PTR ptr);					//RJS 26Feb97
	static	Bool TestCol2(SWord,SWord,SWord,UWord,UWord,UWord,UWord);//RJS 01Dec97
	static  void AddEffect(UByte, UByte, UWord, UWord,UByteP,SByte,UWord);//RJS 16Nov98
	static  void ProcessEffectQueue(ItemPtr);					//RJS 27Feb97
	static  void ResetCollisionStuff();							//RJS 10Mar98
	static	void BashHitter(MobileItemPtr,ItemPtr,Coords3D&,int,Coords3D&,UWord);//RJS 20May99
	static	ItemPtr SpecificCollision(MobileItemPtr,ItemPtr);	//RJS 18Nov98
	static  Bool DetailedTest();								//RJS 01Dec98
	static	ItemPtr NineSectorColPiloted(MobileItemPtr);		//RJS 17May99
	static	ItemPtr NineSectorColThisPiloted(MobileItemPtr);	//RJS 20May99
	static	void	BounceOrExplode(MobileItemPtr,ItemPtr,int,Coords3D&,UByteP);//RJS 20May99


private:
	static	Bool TestCol(Coords3D* hitter1,Coords3D* hitter2,Coords3D* TargSize);
	static	Bool TestCube(Coords3D* hitter1,Coords3D* hitter2,SLong side1);
	static	Bool TestFace(Coords3D* hitter1,Coords3D* hitter2,
							SLong hit1axis,SLong hit2axis,SLong sizeaxis);
	static	Bool TestFace2(Coords3D* hitter1,Coords3D* hitter2,	
							SLong hit1axis,SLong hit2axis,
							SLong	offset, SLong sizeaxis);	//RJS 26Feb97

	static	Bool SmallSideTest(SLong,SLong,SLong);				//RJS 26Feb97
	static	Bool GroupColSpecific(MobileItemPtr hitter,ItemPtr trg,Coords3D& hitpos,int& eltnum);//RJS 03Dec98
	static	Bool DoCollision(Coords3D&,Coords3D&,Coords3D&,ItemPtr,ItemPtr,MobileItem*,SLong);//RJS 18May99

	static	ItemPtr SectorColPiloted(MobileItemPtr,ItemPtr,Bool);//RJS 17May99

};



#endif
