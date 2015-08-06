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
//Filename       collided.cpp
//System         
//Author         Paul.   
//Date           Thu 21 Mar 1996
//Description    
//------------------------------------------------------------------------------

#define F_GRAFIX												//DAW 05Aug96
#define F_SOUNDS
#define F_BATTLE
#include	"Collided.h"
#include	"shapes.h"											//RJS 02Dec97
// #include	"JimLong.h"											//PD 06Sep96
#include	"3dcom.h"
#include	"landscap.h"
#include	"savegame.h"										//PD 30Aug96
#include	"flymodel.h"										//PD 30Aug96
#include	"matrix.h"											//PD 06Sep96
#include	"ranges.h"											//RDH 12Sep96
#include	"lstream.h"											//PD 29Sep96
#include	"migLand.h"
#include	"3dcode.h"
const	ANGLES ACROLLANGLE = ANGLES_10Deg;						//RJS 02JUN99
const	ANGLES ACPITCHANGLE= ANGLES_15Deg;						//PD 11Sep96
const	UWord ACUPSIDEDOWNMIN= UWord(ANGLES_180Deg) - UWord(ANGLES_15Deg);	//RJS 14Apr99
const	UWord ACUPSIDEDOWNMAX= UWord(ANGLES_180Deg) + UWord(ANGLES_15Deg);	//RJS 14Apr99


#include	"winmove.h"											//ARM 08Nov96
#include	"modinst.h"
#include	"model.h"

Collide	_Collide;

typedef	struct
{
	double	a,b,c,d;
}
Coeffs,*CoeffsP;

extern	SLong	GroundHeight(SLong& x, SLong& z, Coeffs& coeff);
#ifdef __WATCOMC__
#pragma	aux		GroundHeight =			\
"		fld		qword ptr ds:[ebx]		"\
"		fild	dword ptr ds:[eax]		"\
"		fmulp	st(1),st				"\
"		fld		qword ptr ds:[ebx+16]	"\
"		fild	dword ptr ds:[edx]		"\
"		fmulp	st(1),st				"\
"		faddp	st(1),st				"\
"		fld		qword ptr ds:[ebx+8]	"\
"		fdivp	st(1),st				"\
"		sub		esp,4					"\
"		fchs							"\
"		fistp	dword ptr ss:[esp]		"\
"		pop		eax						"\
parm	[eax] [edx] [ebx]				\
value	[eax]
#endif
#ifdef __MSVC__
SLong GroundHeight(SLong& x, SLong& z, Coeffs& coeff)
{
	SLong	retval;
	_asm 
	{
		push	eax
		push	ebx
		push	edx

		mov		eax,x
		mov		edx,z
		mov		ebx,coeff
		fld		qword ptr ds:[ebx]		
		fild	dword ptr ds:[eax]		
		fmulp	st(1),st				
		fld		qword ptr ds:[ebx+16]	
		fild	dword ptr ds:[edx]		
		fmulp	st(1),st				
		faddp	st(1),st				
		fld		qword ptr ds:[ebx+8]	
		fdivp	st(1),st				
		sub		esp,4					
		fchs							
		fistp	dword ptr ss:[esp]		
		pop		eax
		mov		retval,eax

		pop		edx
		pop		ebx
		pop		eax
	}
	return retval;
}

#endif

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetWorld
//Author		Paul.   
//Date			Thu 21 Mar 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Collide::SetWorld(WorldStuff *wptr)
{
 	worldptr = wptr;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RayHitTriangle
//LastModified:	PD 29Jul96
//Author		Paul.   
//Date			Tue 19 Mar 1996
//
//Description	Checks to see if the ray defined by S + alpha.D hits the
//				triangle defined by position vectors TO, TA, TB and
//				return the impact position vector P or FALSE if the
//				ray fails to hit the triangle.
//
//Inputs		S+D 		position and direction vectors for the ray
//				PO,PA,PB	position vectors for the vertices of the
//							triangle
//
//Returns		TRUE & impact position vector P if the ray hits the
//						triangle
//				or
//				FALSE if there is no intersection
//
//------------------------------------------------------------------------------
Bool Collide::RayHitTriangle(	const vector& S,				//PD 29Jul96
								const vector& D,
								const vector& TO,
								const vector& TA,
								const vector& TB,
								vector& P)
{
	SLong	alpha;

	SDLong	AdotA, BdotB, AdotB,
			QdotA, QdotB;

	SDLong	u, v;

	vector	A, B, C, N, SminusC, Q;

	A = TA - TO;

	B = TB - TO;

	C = TO;

	N = A % B;

	N.normalise();

	SminusC = S-C;

	alpha = -(SminusC*N / (D*N));

	Q = SminusC + (D * alpha);

	AdotA = (A * A)>>12;

	BdotB = (B * B)>>12;

	AdotB = (A * B)>>12;

	QdotB = (Q * B)>>12;

	QdotA = (Q * A)>>12;

	u =	BdotB * QdotA;
		
	u -= AdotB * QdotB;
 
	u *= (SLong )0x0100;
	
 	u /= (AdotA*BdotB - AdotB*AdotB);

	if (u<0 || u>0x0100)
		return FALSE;

	v = QdotB * (SLong )0x0100;
	
	v -= u * AdotB;
	
	v /= BdotB;

	if (v<0 || v>0x0100)
		return FALSE;

	if (u+v > 0x0100)
		return FALSE;

	//position vector for ground intersection point
	//is given by P = C + Q

	P = C + Q;

	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RayHitParallelogram
//LastModified:	PD 29Jul96
//Author		Paul.   
//Date			Tue 19 Mar 1996
//
//Description	Checks to see if the ray defined by S + alpha.D hits the
//				parallelogram defined by position vectors TO, TA, TB and
//				return the impact position vector P or FALSE if the
//				ray fails to hit the parallelogram.
//
//Inputs		S+D 		position and direction vectors for the ray
//				C,A,B		position vectors for 3 of the vertices of the
//							parallelogram
//
//Returns		TRUE & impact position vector P if the ray hits the
//						parallelogram
//				or
//				FALSE if there is no intersection
//
//------------------------------------------------------------------------------
Bool Collide::RayHitParallelogram(	const vector& S,			//PD 29Jul96
									const vector& D,
									const vector& C,
									const vector& A,
									const vector& B,
									vector& P)
{
	SLong	alpha;

	SDLong	AdotA, BdotB, AdotB,
			QdotA, QdotB;

	SDLong	u, v;

	vector	N, SminusC, Q;

	N = A % B;

	N.normalise();

	SminusC = S-C;

	SLong	DdotN = D*N;

	if (!DdotN)
		return	FALSE;

	alpha = -(SminusC*N / DdotN);

	Q = SminusC + (D * alpha);

	AdotA = (A * A);

	BdotB = (B * B);

	AdotB = (A * B);

	QdotB = (Q * B);

	QdotA = (Q * A);

	u =	BdotB * QdotA;
		
	u -= AdotB * QdotB;
 
	u *= (SLong )0x0100;
		
 	u /= (AdotA*BdotB - AdotB*AdotB);

	if (u<0 || u>0x0100)
	{
//TempCode RJS 24Nov96 		FILE*	fp;
//TempCode RJS 24Nov96 		fp = fopen("bumbug.txt","at");
//TempCode RJS 24Nov96 		fprintf(fp,"\n MISS 2\n");
//TempCode RJS 24Nov96 		fprintf(fp,"	u = %d ... %d\n",u.hi,u.lo);
//TempCode RJS 24Nov96 		fclose(fp);
		return FALSE;
	}

	v = QdotB * (SLong )0x0100;
	
	v -= u * AdotB;
	
	v /= BdotB;

	if (v<0 || v>0x0100)
	{
//TempCode RJS 24Nov96 		FILE*	fp;
//TempCode RJS 24Nov96 		fp = fopen("bumbug.txt","at");
//TempCode RJS 24Nov96 		fprintf(fp,"\n MISS 3\n");
//TempCode RJS 24Nov96 		fprintf(fp,"	v = %d ... %d\n",v.hi,v.lo);
//TempCode RJS 24Nov96 		fclose(fp);
		return FALSE;
	}

	//position vector for intersection point
	//is given by P = C + Q

	P = C + Q;

//TempCode RJS 24Nov96 	FILE*	fp;
//TempCode RJS 24Nov96 	fp = fopen("bumbug.txt","at");
//TempCode RJS 24Nov96 	fprintf(fp,"\n	    --- HIT PARALLELOGRAM!! --- \n\n");
//TempCode RJS 24Nov96 	fclose(fp);

	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AcNearToGround
//Author		Paul.   
//Date			Wed 11 Sep 1996
//
//Description	Changed to allow for fact that world.Y is centre of aircraft
//				not bottom of wheels
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//Bool Collide::AcNearToGround(	AirStrucPtr ac,
//								const vector& ip1,
//								const vector& ip2,
//								const vector& ip3,
//								const vector& ip4)
//{ 
//	if ((ac->World.Y- METRES04)>=ip1.b &&						//RDH 22Oct96
//		(ac->World.Y- METRES04)>=ip2.b &&						//RDH 22Oct96
//		(ac->World.Y- METRES04)>=ip3.b &&						//RDH 22Oct96
//		(ac->World.Y- METRES04)>=ip4.b)							//RDH 22Oct96
//			return (FALSE);
// 
//	return (TRUE);
//}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TouchedGround
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
Bool Collide::TouchedGround(	AirStrucPtr ac,
								ANGLES newpitch,ANGLES newroll,
								Collide::Pos& pos,
								SLong	groundlevel,
								Bool	isCrashed	)
{
	Bool		retval = FALSE;
	SWord 		pitchdelta,
				rolldelta;
	COORDS3D	coords;
	COORDS3D	offset;
	COORDS3D	PushedOffset;									//RJS 12Aug97
	UWord		absroll = ac->roll;								//RJS 14Apr99
	AircraftAnimData*	adptr = (AircraftAnimData*) ac->Anim;	//RJS 15Apr99

	pitchdelta = newpitch - ac->pitch;
	rolldelta = newroll - ac->roll;

	ac->fly.pModel->GroundHeight = groundlevel;			//RJS 15Apr99
	//First, are we upside down???
	if ((absroll > ACUPSIDEDOWNMIN) && (absroll < ACUPSIDEDOWNMAX))//RJS 14Apr99
	{
		pos = Collide::NOSE_TOUCH;
		retval = TRUE;
	}
	else
	{
		if ( (pitchdelta<0?-pitchdelta:pitchdelta) < (rolldelta<0?-rolldelta:rolldelta) )
		{
			//Dpitch gt Droll

			if ((ANGLES)(Angles)rolldelta>ACROLLANGLE)
			{
				SHAPE.GetContactPoint((itemptr )ac,CT_LEFT,coords,offset,PushedOffset);//RJS 12Aug97
	 			pos = Collide::LEFT_WING_TOUCH;
			}
			else
			{
				if ((ANGLES)(Angles)rolldelta<-ACROLLANGLE)
				{
					SHAPE.GetContactPoint((itemptr )ac,CT_RIGHT,coords,offset,PushedOffset);//RJS 12Aug97
		 			pos = Collide::RIGHT_WING_TOUCH;
				}
				else
				{
					if (	(!adptr->acleglowerl && !adptr->LEFTWHEEL)				//RJS 19May99
						&&	(!adptr->acleglowerr && !adptr->RIGHTWHEEL)	)			//RJS 19MaY99
					{
						pos = Collide::LANDED_OK;
						return FALSE;
					}	
					else
					{
						SHAPE.GetContactPoint((itemptr )ac,CT_BELLY,coords,offset,PushedOffset);//RJS 12Aug97
						pos = Collide::LANDED_BELLY;
					}
				}
			}
		}
		else
		{
			//Droll gt DPitch

			if ((ANGLES)(Angles)pitchdelta>ACPITCHANGLE)
			{
				SHAPE.GetContactPoint((itemptr )ac,CT_FRONT,coords,offset,PushedOffset);//RJS 12Aug97
		 		pos = Collide::NOSE_TOUCH;
			}
			else
			{
				if ((ANGLES)(Angles)pitchdelta<-ACPITCHANGLE)
				{
					SHAPE.GetContactPoint((itemptr )ac,CT_BACK,coords,offset,PushedOffset);//RJS 12Aug97
					pos = Collide::TAIL_TOUCH;						//RJS 13Jan99
				}
				else
				{
					if (	(!adptr->acleglowerl && !adptr->LEFTWHEEL)				//RJS 19May99
						&&	(!adptr->acleglowerr && !adptr->RIGHTWHEEL)	)			//RJS 19MaY99
					{
						pos = Collide::LANDED_OK;
						return FALSE;
					}	
					else
					{
						SHAPE.GetContactPoint((itemptr )ac,CT_BELLY,coords,offset,PushedOffset);//RJS 12Aug97
						pos = Collide::LANDED_BELLY;
					}
				}
			}
		}

		SLong	glevel;
//Dead		SLong	groundlevel;
	
		if (isCrashed)												//RJS 02Jul98
		{
//Dead			ac->fly.pModel->GroundHeight = Land_Scape.GetGroundLevel(ac);//RJS 13Jan99
			if (ac->World.Y <= ac->fly.pModel->GroundHeight)				//RJS 24Aug98
				retval = TRUE;
		}
		else
		{
			glevel = Land_Scape.GetGroundLevel(coords);				//RJS 13Jan99
	//DeadCode RJS 13Jan99 		groundlevel = glevel + ac->World.Y - coords.Y;				//RJS 02Jul98
	//DeadCode RJS 13Jan99 
	//DeadCode RJS 13Jan99 		if (ac->World.Y <= groundlevel)								//PD 15Nov96
	//DeadCode RJS 13Jan99 		{
	//DeadCode RJS 13Jan99 			ac->World.Y = groundlevel;								//PD 08Oct96
	//DeadCode RJS 13Jan99 			retval = TRUE;
	//DeadCode RJS 13Jan99 		}
			if (coords.Y <= glevel)									//RJS 13Jan99
				retval = TRUE;										//RJS 13Jan99
		}
	}

	if (!retval)
		pos = Collide::NOTTOUCHED;
//DeadCode RJS 20Apr99 	else														//RJS 14Apr99
//DeadCode RJS 20Apr99 	{															//RJS 14Apr99
//DeadCode RJS 20Apr99 		ac->pitch = newpitch;									//RJS 14Apr99
//DeadCode RJS 20Apr99 		ac->roll = newroll;										//RJS 14Apr99
//DeadCode RJS 20Apr99 	}															//RJS 14Apr99

	return(retval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LowestSafeAlt
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
SLong Collide::LowestSafeAlt(	AirStrucPtr ac,
								ANGLES newpitch,ANGLES newroll)
{
	SWord 		pitchdelta,
				rolldelta;
	COORDS3D	coords;
	COORDS3D	offset;
	COORDS3D	PushedOffset;									//RJS 12Aug97

	if (ac->World.Y>HIGHESTGROUND) return 0;

	coords=ac->World;

	SLong groundlevel = Land_Scape.GetGroundLevel(coords);				//PD 24Oct96

	if (ac->World.Y>groundlevel+FT_500) return groundlevel;

	pitchdelta = newpitch - ac->pitch;
	rolldelta = newroll - ac->roll;
	if ( (pitchdelta<0?-pitchdelta:pitchdelta) < (rolldelta<0?-rolldelta:rolldelta) )//RDH 12Sep96
	{
		//Dpitch gt Droll

		if ((Angles)rolldelta<-ACROLLANGLE)
		{
			SHAPE.GetContactPoint((itemptr )ac,CT_LEFT,coords,offset,PushedOffset);//RJS 12Aug97
		}
		else
		{
			if ((ANGLES)(Angles)rolldelta>ACROLLANGLE)
			{
				SHAPE.GetContactPoint((itemptr )ac,CT_RIGHT,coords,offset,PushedOffset);//RJS 12Aug97
			}
			else
			{
				SHAPE.GetContactPoint((itemptr )ac,LT_CONTACT,coords,offset,PushedOffset);//RJS 12Aug97
			}
		}
	}
	else
	{
		//Droll gt DPitch

		if ((Angles)pitchdelta<-ACPITCHANGLE)
		{
			SHAPE.GetContactPoint((itemptr )ac,CT_FRONT,coords,offset,PushedOffset);//RJS 12Aug97
		}
		else
		{
			if ((ANGLES)(Angles)pitchdelta>ACPITCHANGLE)
			{
				SHAPE.GetContactPoint((itemptr )ac,CT_BACK,coords,offset,PushedOffset);//RJS 12Aug97
			}
			else
			{
				SHAPE.GetContactPoint((itemptr )ac,LT_CONTACT,coords,offset,PushedOffset);//RJS 12Aug97
			}
		}
	}

	groundlevel += (ac->World.Y - coords.Y);				//PD 24Oct96

	return (groundlevel);		//RDH 21Oct96
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FindRelPitchAndRoll
//Author		Paul.   
//Date			Fri 6 Sep 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Collide::FindRelPitchAndRoll(	AirStrucPtr ac,
									ANGLES& heading,
									ANGLES& pitch,
									ANGLES& roll
									)
{
	ANGLES newhdg,newpitch,newroll;
	Coords3D	thecoord = ac->World;						//RJS 20Apr99

 	Three_Dee.pMigLand->GetShadowAngles(thecoord,ac->hdg,newpitch,newroll);//RJS 20Apr99	//CSB 01Jul99
//DeadCode DAW 01Jul99 	Three_Dee.pMigLand->GetShadowAngles(thecoord,ac->hdg,newpitch,newroll);//RJS 01Jul99
	heading=ac->hdg;
	pitch=(ANGLES)newpitch;
	roll=(ANGLES)newroll;
}

//------------------------------------------------------------------------------
//Procedure		HaveWeLanded
//Author		R. Hyde 
//Date			Thu 12 Sep 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Collide::Pos Collide::HaveWeLanded(AirStruc* ac,ANGLES& pitch,ANGLES& roll,Bool isCrashed)
{
	Collide::Pos retval=NOTTOUCHED;

	if ( (ac->World.Y <HIGHESTGROUND)
		)
	{
		//Quick throw out on tile corner altitude
	
		SLong glevel=Land_Scape.GetGroundLevel(ac);
		ac->fly.pModel->GroundHeight = glevel;								//RJS 20May99
		if (ac->World.Y<=glevel+METRES10)						//RJS 20Apr99
		{
			ANGLES	newhdg,newpitch,newroll;
	
			FindRelPitchAndRoll(ac,newhdg,newpitch,newroll);
	
			if (TouchedGround(ac,newpitch,newroll,retval,glevel,isCrashed))	//RJS 15Apr99
			{
				if (retval != Collide::LANDED_OK)
				{
					ac->pitch = newpitch;
					ac->roll = newroll;
					ac->fly.pModel->ResetAngles(ac,-ac->hdg,newpitch,newroll);	//RJS 15Apr99
					ac->fly.pModel->Vel.y = 0;
				}
			}
		}
	}
	return (retval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GroundAltitude
//Author		Paul.   
//Date			Fri 27 Sep 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SLong Collide::GroundAltitude(COORDS3D& coords,UByte* pAreaType,bool fReallyGetData)
{
	SLong newalt=Three_Dee.pMigLand->GetAltitude(coords,pAreaType,fReallyGetData);
	return newalt;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RoughGroundAltitude
//Author		Paul.   
//Date			Wed 3 Mar 1999
//------------------------------------------------------------------------------
SLong Collide::RoughGroundAltitude(SLong x,SLong y,SLong z)
{
	SLong newalt=Three_Dee.pMigLand->GetRoughAltitude(x,y,z);
	if (newalt==0) return HIGHESTGROUND;
	return newalt;
}	

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AccurateGroundAltitude
//Author		Paul.   
//Date			Tue 8 Oct 1996
//
//Description	Special case accurate ground altitude used for altering
//				the altitude of Items in the 3D. No quick throw outs are
//				included because the item is defintely supposed to be
//				on the ground, we just want to know where.
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SLong Collide::AccurateGroundAltitude(COORDS3D& coords)
{
	return Three_Dee.pMigLand->GetAltitude(coords);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StillLanded
//Author		R. Hyde 
//Date			Thu 12 Sep 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Collide::StillLanded(AirStruc* ac,ANGLES& pitch,ANGLES& roll)
{
	ANGLES newhdg,newpitch,newroll;

	FindRelPitchAndRoll(ac,newhdg,newpitch,newroll);
	SLong miny=LowestSafeAlt(ac,newpitch,newroll);
	ac->World.Y=miny;
	ac->fly.pModel->Pos.y=miny;
#pragma warnmsg("OK: check for updating deltas when StillLanded gets called")

	if (ac==Persons2::PlayerSeenAC)								//AMM 30Mar99
		Persons2::PlayerGhostAC->World.Y=miny;					//AMM 30Mar99

	pitch=newpitch;
	roll=newroll;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FindShadAngles
//Author		Robert Slater
//Date			Tue 6 May 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Collide::FindShadAngles(AirStrucPtr,ANGLES&, ANGLES&,ANGLES&)
{
	assert(false&&"No longer used!");
}

