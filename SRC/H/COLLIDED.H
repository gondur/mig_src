//------------------------------------------------------------------------------
//Filename       collided.h
//System         
//Author         Paul.   
//Date           Thu 21 Mar 1996
//Description    
//------------------------------------------------------------------------------
#ifndef	COLLIDED_Included
#define	COLLIDED_Included

#define	DEFAULT_COLLIDED 0

#include	"DosDefs.h"
#include	"WorldInc.h"
#include	"MyVector.h"   //PLEASE DONT LOSE THIS ERROR AGAIN!!!!!!!
#include	"World.h"
#include	"ViewSel.h"
#include	"myError.h"
#include	"MyTime.h"


class	Collide
{
	typedef	Bool (Collide::*CollRtnPtr) (	MovingItemPtr,
											itemptr,
											vector&
											);
	typedef	Bool (Collide::CollRtn)  	(	MovingItemPtr,
											itemptr,
											vector&
											);
	WorldStuff*	worldptr;

	CollRtnPtr	collrtnptr;

	SLong		srcrange;

	vector		sDIR,sPOS;

	vector		VT;

	ULong		currgrp;

	public:

		enum	Pos{NOTTOUCHED=0,
					LANDED_OK,
					LEFT_WING_TOUCH,
					RIGHT_WING_TOUCH,
					NOSE_TOUCH,
					PROP_TOUCH,									//RJS 27Aug98
					LANDED_BELLY,								//RJS 27Aug98
					TAIL_TOUCH									//RJS 13Jan99
					};
				

		void	SetWorld	(WorldStuff* );

		SLong	GroundAltitude(COORDS3D&,UByte* pAreaType=NULL,bool fReallyGetData=false);
		SLong	RoughGroundAltitude(SLong,SLong,SLong);
		SLong	AccurateGroundAltitude(COORDS3D&);				//PD 08Oct96

		Collide::Pos	HaveWeLanded(AirStruc* ,ANGLES& pitch, ANGLES& roll,Bool isCrashed=FALSE);//RJS 02Jul98
		void			StillLanded(AirStruc* ,ANGLES& pitch, ANGLES& roll);//RJS 02Jul98

		UByte	GroupsHit	(MovingItemPtr,
							 itemptr,
							 vector&
							 );									//RJS 02Oct96
		
		Bool	CollisionTest  (MovingItemPtr,
								itemptr&,
								vector&,
								SByte&
								);								//RJS 02Oct96

		Bool	TransCollTest  (MovingItemPtr,
								itemptr&,
								vector&,
								SByte&
								);								//RJS 02Oct96

		Bool	MobileHitItem  (MovingItemPtr,
								itemptr,
								vector&
								);

		Bool	QuikMobileHitItem  (MovingItemPtr,
									itemptr,
									vector&
									);

		Bool	RayHitTriangle (	const vector&,				//PD 29Jul96
									const vector&,
									const vector&,
									const vector&,
									const vector&,
									vector&
								);

		Bool	RayHitParallelogram	(	const vector&,			//PD 29Jul96
										const vector&,
										const vector&,
										const vector&,
										const vector&,
										vector&
									);

		Bool	RayHitSphere(	const vector&,					//PD 29Jul96
								const vector&,
								const vector&,
								SLong
							);

		SLong 	LowestSafeAlt(	AirStrucPtr,ANGLES,ANGLES);		//RDH 21Oct96
		void	FindShadAngles(AirStrucPtr,ANGLES&,ANGLES&,ANGLES&);//RJS 06May97

		Bool	tdalt;											//PD 30Sep96

	private:

		SLong	CalcRange(MovingItemPtr ,SWord);

		Bool	InRange(const vector&, const vector&, SLong );	//PD 29Jul96

//		Bool 	AcNearToGround(	AirStrucPtr,const vector&,const vector&,const vector&,const vector&);
		Bool 	TouchedGround(	AirStrucPtr,ANGLES,ANGLES,Collide::Pos&,SLong,Bool isCrashed=FALSE);//RJS 15Apr98
//Old_Code RDH 21Oct96 		SLong 	LowestSafeAlt(	AirStrucPtr,ANGLES,ANGLES);
		void 	FindRelPitchAndRoll(AirStrucPtr ac,ANGLES&,ANGLES&,ANGLES&);



};

extern	Collide	_Collide;

#endif
