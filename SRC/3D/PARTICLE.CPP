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
//Filename       particle.cpp
//System     
//Author         Paul.   
//Date           Wed 16 Aug 1995
//Description    Particle stuff from 3dcom.cpp. This won't compile with optimisations!
//------------------------------------------------------------------------------

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//				           INCLUDE FILES
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴


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
//	#include	"LnchrDat.h"	//launcherdata									//RJS 09Sep96
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

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ParticleStreamEdgedPlain
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
void	shape::ParticleStreamEdgedPlain(UWord	vertex0,
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
/*	DoPointStruc dopoint0,dopoint1,dopoint2,dopoint3,dopointRoot,dptmp1,dptmp2;
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
	SWord	realmaxrad = EndRadius;

	depth = 1 + (depth >> 1);

	wXStart = WCylStartP->gx;									
	wYStart = WCylStartP->gy;									
	wZStart = WCylStartP->gz;									

 	oldcross = POLYGON.SetCrossProduct(FALSE);

	dopoint1 = dopoint0 = newco[vertex0];								
   	dopoint3 = dopoint2 = newco[vertex1];

	wXStep = (WCylEndP->gx - wXStart) / depth;					
	wYStep = (WCylEndP->gy - wYStart) / depth;					
	wZStep = (WCylEndP->gz - wZStart) / depth;					

	XoffGap = (xoff1 - xoff0)/depth;
	YoffGap = (yoff1 - yoff0)/depth;

	EndRadius = (5*EndRadius)>>3;
	StartRadius = (5*StartRadius)>>3;

	RadStep = (EndRadius - StartRadius)/depth;
	MaxRadius = StartRadius;

	xDelta = xoff0;
	yDelta = yoff0;

	POLYGON.SetOpacityON();
 	POLYGON.SetPixelWidth(1);

	dopoint0.bodyx.f += xoff0;								
  	dopoint0.bodyy.f += yoff0;								
	_matrix.SetClipFlags(dopoint0);
  	_matrix.body2screen(dopoint0);
 
  	dopoint1.bodyx.f += -xoff0;								
 	dopoint1.bodyy.f += -yoff0;								
	_matrix.SetClipFlags(dopoint1);
 	_matrix.body2screen(dopoint1);
 
   	dopoint2.bodyx.f += -xoff1;								
   	dopoint2.bodyy.f += -yoff1;								
	_matrix.SetClipFlags(dopoint2);
  	_matrix.body2screen(dopoint2);
 
   	dopoint3.bodyx.f += xoff1;								
   	dopoint3.bodyy.f += yoff1;								
	_matrix.SetClipFlags(dopoint3);
  	_matrix.body2screen(dopoint3);

 	POLYGON.SetPixelWidth(1<<Save_Data.pixelsize);			
 	POLYGON.createpoly(thecol);						
	POLYGON.createvert(dopoint0);					
  	POLYGON.createvert(dopoint1);					
  	POLYGON.createvert(dopoint2);					
	POLYGON.createvert(dopoint3);					
 	POLYGON.drawpoly();			

	SLong	XStep0, YStep0, ZStep0;
	SLong	XStep1, YStep1, ZStep1;

	XStep0 = (dopoint3.bodyx.f - dopoint0.bodyx.f)/depth;
	YStep0 = (dopoint3.bodyy.f - dopoint0.bodyy.f)/depth;
	ZStep0 = (dopoint3.bodyz.f - dopoint0.bodyz.f)/depth;

	XStep1 = (dopoint2.bodyx.f - dopoint1.bodyx.f)/depth;
	YStep1 = (dopoint2.bodyy.f - dopoint1.bodyy.f)/depth;
	ZStep1 = (dopoint2.bodyz.f - dopoint1.bodyz.f)/depth;

	for (counter = 0; counter < depth; counter++)
	{
		xDeltCap = xDelta << 1;
		yDeltCap = yDelta << 1;

		RSeed = Noise(wXStart,wYStart,wZStart);

		RandxDelta = (((RSeed*xDeltCap)>>8) - xDelta)>>3;			
		RandyDelta = (((RSeed*yDeltCap)>>8) - yDelta)>>3;			

		dptmp1 = dopoint0;
		dptmp1.bodyx.f += RandxDelta;
		dptmp1.bodyy.f += RandyDelta;

		dptmp2 = dptmp1;

		_matrix.SetClipFlags(dptmp1);
		_matrix.body2screen(dptmp1);
		dptmp2.bodyx.f += MaxRadius;
		_matrix.SetClipFlags(dptmp2);
		_matrix.body2screen(dptmp2);

		Radius = dptmp2.screenx.f - dptmp1.screenx.f;
		if (Radius)
		{
			POLYGON.createsphere(thecol,transdepth);			//RJS 04Dec97
			POLYGON.createsphvert(dptmp1,Radius);				//RJS 04Dec97
			POLYGON.drawsphere();								//RJS 04Dec97
		}

		dptmp1 = dopoint1;
		dptmp1.bodyx.f -= RandxDelta;
		dptmp1.bodyy.f -= RandyDelta;

		dptmp2 = dptmp1;

		_matrix.SetClipFlags(dptmp1);
		_matrix.body2screen(dptmp1);
		dptmp2.bodyx.f += MaxRadius;
		_matrix.SetClipFlags(dptmp2);
		_matrix.body2screen(dptmp2);

		Radius = dptmp2.screenx.f - dptmp1.screenx.f;
		if (Radius)
		{
			POLYGON.createsphere(thecol,transdepth);			//RJS 04Dec97
			POLYGON.createsphvert(dptmp1,Radius);				//RJS 04Dec97
			POLYGON.drawsphere();								//RJS 04Dec97
		}

		dopoint0.bodyx.f += XStep0;
		dopoint0.bodyy.f += YStep0;
		dopoint0.bodyz.f += ZStep0;

		dopoint1.bodyx.f += XStep1;
		dopoint1.bodyy.f += YStep1;
		dopoint1.bodyz.f += ZStep1;

		xDelta += XoffGap;
		yDelta += YoffGap;

		wXStart += wXStep;										//RJS 12Nov97
		wYStart += wYStep;										//RJS 12Nov97
		wZStart += wZStep;										//RJS 12Nov97

		MaxRadius += RadStep;
	}

	dptmp2 = newco[1];
	dptmp2.bodyx.f += realmaxrad;
	_matrix.SetClipFlags(dptmp2);
	_matrix.body2screen(dptmp2);

	Radius = dptmp2.screenx.f - newco[1].screenx.f;
	POLYGON.createsphere(thecol,transdepth);			//RJS 04Dec97
	POLYGON.createsphvert(newco[1],Radius);				//RJS 04Dec97
	POLYGON.drawsphere();

	current_screen->SetTransparency(SMOKED_OFF);				//RJS 18Jun97

 	POLYGON.SetCrossProduct(oldcross);*/
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ParticleStreamImapd
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
void	shape::ParticleStreamImapd(	UWord	vertex0,
							 		UWord	vertex1,
							 		SWord	xoff0, SWord yoff0,
							 		SWord	xoff1, SWord yoff1,
							 		UWord	depthscale,
									SWord	StartRadius,
									SWord	EndRadius,
							 		MyGroundVectorPtr	WCylStartP,
							 		MyGroundVectorPtr	WCylEndP,
							 		SWord	Imap,
									SWord	minx, SWord  miny,
							 		SWord	iW, SWord	iH,
							 		SWord	transdepth)
{
	DoPointStruc dopoint0,dopoint1,dopoint2,dopoint3,dopointRoot,dptmp1,dptmp2;
 	Bool	oldcross;
	Float	RelX, RelY, RelZ;
	UWord	counter;
	SLong	xDelta,yDelta;
	SLong	RandxDelta,RandyDelta;
	SLong	xDeltCap,yDeltCap;
	SWord	RSeed;
	SLong	XoffGap;
	SLong	YoffGap;
	SLong	Radius;
	ImageMapNumber imapno = (ImageMapNumber) Imap;				
	SWord	maxx, maxy;
	SLong	MaxRadius = StartRadius<<16;						//RJS 15Apr98
	SLong	wXStep, wYStep, wZStep;								
	SLong	wXStart, wYStart, wZStart;							
	SLong	MaxDist, Dist;
	SLong	RadStep;
	ULong	thetime = 0;
	ULong	depth;												//RJS 10Dec98

//DeadCode RJS 30Mar98 	depth = 1 + (depth >> 1);
//DeadCode MS 10Dec98 
//DeadCode MS 10Dec98 	RadStep = ((EndRadius - StartRadius)<<16)/depth;				//RJS 04Feb98

	wXStart = WCylStartP->gx;									
	wYStart = WCylStartP->gy;									
	wZStart = WCylStartP->gz;									

	maxx = minx + iW;													
	maxy = miny + iH;													

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

	if (RelX || RelY || RelZ)									//MS 10Dec98
	{
		SLong	traillength = Math_Lib.distance3d(SLong(RelX),SLong(RelY),SLong(RelZ));
		SLong	avradius = (StartRadius + EndRadius)>>1;

		avradius++;												//RJS 10Dec98

		// max depth...
		depth = traillength / avradius;					//RJS 10Dec98
		depth <<= 7;											//RJS 10Dec98
		depth /= depthscale;									//RJS 10Dec98
		if (depth <= 0)	depth = 1;								//RJS 25Jun99
//DeadCode DAW 25Jun99 		depth ++;												//RJS 10Dec98

		RadStep = ((EndRadius - StartRadius)<<16)/depth;				//RJS 04Feb98

		wXStep = (WCylEndP->gx - wXStart) / depth;					
		wYStep = (WCylEndP->gy - wYStart) / depth;					
		wZStep = (WCylEndP->gz - wZStart) / depth;					

		if (View_Point)
			thetime = View_Point->TimeOfDay();

		wXStart += thetime;									
		wYStart += thetime;									
		wZStart += thetime;

		XoffGap = (xoff1 - xoff0)/depth;
		YoffGap = (yoff1 - yoff0)/depth;

		RelX /= depth;
		RelY /= depth;
		RelZ /= depth;

		xDelta = xoff0;
		yDelta = yoff0;

	//	POLYGON.SetOpacityON();
//DEAD 		POLYGON.SetPixelWidth(1);

		for (counter = 0; counter < depth; counter++)
		{
			RSeed = Noise(wXStart,wYStart,wZStart);

			RandxDelta = RSeed*xDelta;
			RandxDelta >>= 7;
			RandxDelta -= xDelta;
			RandxDelta >>= 2;

			RandyDelta = RSeed*yDelta;
			RandyDelta >>= 7;
			RandyDelta -= yDelta;
			RandyDelta >>= 2;

	//		RandxDelta = (((RSeed*xDelta)>>7) - xDelta)>>2;			//RJS 27Feb98
	//		RandyDelta = (((RSeed*yDelta)>>7) - yDelta)>>2;			//RJS 27Feb98

			dopoint0 = dopointRoot;
			dopoint0.bodyx.f += RandxDelta;
			dopoint0.bodyy.f += RandyDelta;

			if (dopoint0.bodyz.f > 10.0)								
			{
				dopoint1 = dopoint2 = dopoint3 = dopoint0;
				RSeed -= 128;
				RSeed = (RSeed<0)?-RSeed:RSeed;
				RSeed = 128 - RSeed;

				Radius = MaxRadius * RSeed;
				Radius >>= 8;
				Radius += (MaxRadius >> 1);
				Radius >>= 16;

	//			Radius = ((MaxRadius>>1) + ((MaxRadius * (128-RSeed))>>8))>>16;

				if (ClipSphere(dopoint0,dopoint1,dopoint2,dopoint3,Radius)==FALSE)
				{
					POLYGON.createpoly(imapno);
					POLYGON.createvert(dopoint0,minx,miny);
					POLYGON.createvert(dopoint1,maxx,miny);
					POLYGON.createvert(dopoint2,maxx,maxy);
					POLYGON.createvert(dopoint3,minx,maxy);
					POLYGON.drawpoly();
				}
			}

			dopointRoot.bodyx.f += RelX;
			dopointRoot.bodyy.f += RelY;
  			dopointRoot.bodyz.f += RelZ;

			xDelta += XoffGap;
			yDelta += YoffGap;

			wXStart += wXStep;										//RJS 12Nov97
			wYStart += wYStep;										//RJS 12Nov97
			wZStart += wZStep;										//RJS 12Nov97

			MaxRadius += RadStep;
		}

		current_screen->SetTransparency(SMOKED_OFF);				//RJS 18Jun97
                                                                                                              
//DEAD 		POLYGON.SetCrossProduct(oldcross);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ParticleStreamStaggeredImapd
//Author		Robert Slater
//Date			Fri 27 Feb 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::ParticleStreamStaggeredImapd(UWord	vertex0,
							 				UWord	vertex1,
							 				SWord	xoff0, SWord yoff0,
							 				SWord	xoff1, SWord yoff1,
							 				SLong	distance3d,
											SLong	fadedist,
											SWord	StartRadius,
											SWord	EndRadius,
							 				MyGroundVectorPtr	WCylStartP,
							 				MyGroundVectorPtr	WCylEndP,
							 				SWord	Imap,
											SWord	minx, SWord  miny,
							 				SWord	iW, SWord	iH,
							 				SWord	transdepth,
											SWord	MaxDepth)
{
	DoPointStruc dopoint0,dopoint1,dopoint2,dopoint3,dopointRoot,dptmp1,dptmp2;
 	Bool	oldcross;
	Float	RelX, RelY, RelZ;
	UWord	counter;
	SLong	xDelta,yDelta,zDelta;
	SLong	RandxDelta,RandyDelta,RandzDelta;
	SWord	RSeed;
	SLong	XoffGap;
	SLong	YoffGap;
	SLong	Radius;
	ImageMapNumber imapno = (ImageMapNumber) Imap;				
	SWord	maxx, maxy;
	SWord	MaxRadius = StartRadius;						//RJS 04Feb98
	SLong	wXStep, wYStep, wZStep;								
	SLong	wXStart, wYStart, wZStart;							
	SLong	MaxDist, Dist;
	SWord	RadStep;
	SWord	avrad = (StartRadius + EndRadius)>>1;
	SLong	depth;

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

//	depth = (Math_Lib.distance3d(RelX,RelY,RelZ) / avrad) * distance3d;
	avrad *= fadedist;
	depth = Math_Lib.distance3d(RelX,RelY,RelZ) * distance3d;
	depth /= avrad;
//	depth /= fadedist;
	depth = (depth*3)>>2;
	if (depth <= 0)	depth = 1;								//RJS 25Jun99
//DeadCode DAW 25Jun99 	depth += 1;

	if (depth > MaxDepth)
		depth = MaxDepth;

	RadStep = (EndRadius - StartRadius)/depth;

	wXStart = WCylStartP->gx;									
	wYStart = WCylStartP->gy;									
	wZStart = WCylStartP->gz;									

	maxx = minx + iW;													
	maxy = miny + iH;													

//DEAD 	oldcross = POLYGON.SetCrossProduct(FALSE);

	wXStep = (WCylEndP->gx - wXStart) / depth;					
	wYStep = (WCylEndP->gy - wYStart) / depth;					
	wZStep = (WCylEndP->gz - wZStart) / depth;					

	XoffGap = (xoff1 - xoff0)/depth;
	YoffGap = (yoff1 - yoff0)/depth;

	RelX /= depth;
	RelY /= depth;
	RelZ /= depth;

	xDelta = xoff0;
	yDelta = yoff0;
	zDelta = RelZ;
	zDelta >>= 1;

	POLYGON.SetOpacityON();
//DEAD 	POLYGON.SetPixelWidth(1);

	for (counter = 0; counter < depth; counter++)
	{
		RSeed = Noise(wXStart,wYStart,wZStart);

		RandxDelta = RSeed*xDelta;
		RandxDelta >>= 7;
		RandxDelta -= xDelta;
		RandxDelta >>= 2;

		RandyDelta = RSeed*yDelta;
		RandyDelta >>= 7;
		RandyDelta -= yDelta;
		RandyDelta >>= 2;

		RandzDelta = RSeed*zDelta;
		RandzDelta >>= 7;
		RandzDelta -= zDelta;
		RandzDelta >>= 2;

//		RandxDelta = (((RSeed*xDelta)>>7) - xDelta)>>2;			
//		RandyDelta = (((RSeed*yDelta)>>7) - yDelta)>>2;			
//		RandzDelta = (((RSeed*zDelta)>>7) - zDelta)>>2;			

		dopoint0 = dopointRoot;
		dopoint0.bodyx.f += RandxDelta;
		dopoint0.bodyy.f += RandyDelta;
		dopoint0.bodyz.f += RandzDelta;

		if (dopoint0.bodyz.f > 10.0)								
		{
			dopoint1 = dopoint2 = dopoint3 = dopoint0;
			RSeed -= 128;
			RSeed = (RSeed<0)?-RSeed:RSeed;
			RSeed = 128 - RSeed;

//			Radius = (MaxRadius>>1) + ((MaxRadius * (128-RSeed))>>8);
			Radius = (MaxRadius * RSeed)>>8;
			Radius += (MaxRadius>>1);

			if (ClipSphere(dopoint0,dopoint1,dopoint2,dopoint3,Radius)==FALSE)
			{
				POLYGON.createpoly(imapno);
				POLYGON.createvert(dopoint0,minx,miny);
				POLYGON.createvert(dopoint1,maxx,miny);
				POLYGON.createvert(dopoint2,maxx,maxy);
				POLYGON.createvert(dopoint3,minx,maxy);
				POLYGON.drawpoly();
			}
		}

		dopointRoot.bodyx.f += RelX;
		dopointRoot.bodyy.f += RelY;
  		dopointRoot.bodyz.f += RelZ;

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
//Procedure		ParticleCylinder
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
void	shape::ParticleCylinderPlain(UWord	vertex0,
									UWord	vertex1,
									SWord	xoff0, SWord yoff0,
									SWord	xoff1, SWord yoff1,
									UWord	depth,
									SWord	MaxRadius,
									MyGroundVectorPtr	WCylStartP,
									MyGroundVectorPtr	WCylEndP,
									SWord	col,
									SWord	transdepth)
{
	DoPointStruc dopoint0,dopoint1,dopoint2,dopoint3,dopointRoot,dptmp1,dptmp2;
 	Bool	oldcross;
	Float	RelX, RelY, RelZ;
	UWord	counter;
	SLong	xDelta,yDelta;
	SLong	RandxDelta,RandyDelta;
	SLong	xDeltCap,yDeltCap;
	UWord	RSeed;
	SLong	XoffGap;
	SLong	YoffGap;
	SLong	Radius, Radius3d;
	SWord	HalfRadius = MaxRadius>>1;							//RJS 04Dec97
	SLong	wXStep, wYStep, wZStep;								//RJS 04Dec97
	SLong	wXStart, wYStart, wZStart;							//RJS 12Nov97
	Colour	thecol = (Colour) col;
	SLong	MaxDist, Dist;										//RJS 02Dec97

	if (depth <= 0)	depth = 1;								//RJS 25Jun99

	wXStart = WCylStartP->gx;									//RJS 12Nov97
	wYStart = WCylStartP->gy;									//RJS 12Nov97
	wZStart = WCylStartP->gz;									//RJS 12Nov97

//DEAD 	oldcross = POLYGON.SetCrossProduct(FALSE);

	dopointRoot = newco[vertex0];										
   	dopoint2 = newco[vertex1];

	RelX = dopoint2.bodyx.f - dopointRoot.bodyx.f;
	RelY = dopoint2.bodyy.f - dopointRoot.bodyy.f;
	RelZ = dopoint2.bodyz.f - dopointRoot.bodyz.f;

	wXStep = (WCylEndP->gx - wXStart) / depth;					//RJS 12Nov97
	wYStep = (WCylEndP->gy - wYStart) / depth;					//RJS 12Nov97
	wZStep = (WCylEndP->gz - wZStart) / depth;					//RJS 12Nov97

	XoffGap = (xoff1 - xoff0)/depth;
	YoffGap = (yoff1 - yoff0)/depth;

	RelX /= depth;
	RelY /= depth;
	RelZ /= depth;

	xDelta = xoff0;
	yDelta = yoff0;

	POLYGON.SetOpacityON();
//DEAD 	POLYGON.SetPixelWidth(1);

	for (counter = 0; counter < depth; counter++)
	{
		xDeltCap = xDelta << 1;
		yDeltCap = yDelta << 1;

		RSeed = Noise(wXStart,wYStart,wZStart);

		RandxDelta = ((RSeed*xDeltCap)>>8) - xDelta;			//RJS 12Nov97
		RandyDelta = ((RSeed*yDeltCap)>>8) - yDelta;			//RJS 12Nov97

		dopoint0 = dopointRoot;
		dopoint0.bodyx.f += RandxDelta;
		dopoint0.bodyy.f += RandyDelta;

		if (dopoint0.bodyz.f > 100)								//RJS 13Nov97
		{
			dopoint1 = dopoint2 = dopoint3 = dopoint0;

			xDeltCap >>= 1;
			yDeltCap >>= 1;
			xDeltCap = (xDeltCap<0)?-xDeltCap:xDeltCap;
			yDeltCap = (yDeltCap<0)?-yDeltCap:yDeltCap;

			if (xDeltCap || yDeltCap)
			{
				if (xDeltCap > yDeltCap)
				{
					MaxDist = xDeltCap;
					Dist = (RandxDelta<0)?-RandxDelta:RandxDelta;
				}
				else
				{
					MaxDist = yDeltCap;
					Dist = (RandyDelta<0)?-RandyDelta:RandyDelta;
				}

				Dist = MaxDist - Dist;

				Radius = 2 + ((Dist*MaxRadius)/MaxDist);

				_matrix.SetClipFlags(dopoint0);
				_matrix.body2screen(dopoint0);

				dopoint1.bodyx.f += Radius;

				_matrix.SetClipFlags(dopoint1);
				_matrix.body2screen(dopoint1);

				Radius3d = dopoint1.screenx.f - dopoint0.screenx.f;
				if ((Radius < HalfRadius) && (Radius3d == 0))	//RJS 04Dec97
					Radius3d = -1;

				POLYGON.createsphere(thecol,transdepth);		//RJS 04Dec97
				POLYGON.createsphvert(dopoint0,Radius3d);		//RJS 04Dec97
				POLYGON.drawsphere();							//RJS 04Dec97
			}
		}

		dopointRoot.bodyx.f += RelX;
		dopointRoot.bodyy.f += RelY;
  		dopointRoot.bodyz.f += RelZ;

		xDelta += XoffGap;
		yDelta += YoffGap;

		wXStart += wXStep;										//RJS 12Nov97
		wYStart += wYStep;										//RJS 12Nov97
		wZStart += wZStep;										//RJS 12Nov97
	}

	current_screen->SetTransparency(SMOKED_OFF);				//RJS 18Jun97

//DEAD	POLYGON.SetPixelWidth(1);
//DEAD 	POLYGON.SetCrossProduct(oldcross);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ParticleCylinderImapd
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
void	shape::ParticleCylinderImapd(UWord	vertex0,
									UWord	vertex1,
									SWord	xoff0, SWord yoff0,
									SWord	xoff1, SWord yoff1,
									UWord	density,			//RJS 10Dec98
									SWord	MaxRadius,
									MyGroundVectorPtr	WCylStartP,
									MyGroundVectorPtr	WCylEndP,
									SWord	Imap,
									SWord	minx, SWord  miny,
									SWord	iW, SWord iH,
									SWord	transdepth)
{
	DoPointStruc dopoint0,dopoint1,dopoint2,dopoint3,dopointRoot,dptmp1,dptmp2;
 	Bool	oldcross;
	Float	RelX, RelY, RelZ;
	UWord	counter;
	SLong	xDelta,yDelta;
	SLong	RandxDelta,RandyDelta;
	SLong	xDeltCap,yDeltCap;
	UWord	RSeed;
	SLong	XoffGap;
	SLong	YoffGap;
	SLong	Radius, Radius3d;
	ImageMapNumber imapno = (ImageMapNumber) Imap;				//RJS 12Nov97
	SWord	maxx, maxy;
	SWord	HalfRadius = MaxRadius>>1;							//RJS 04Dec97
	SLong	wXStep, wYStep, wZStep;								//RJS 04Dec97
	SLong	wXStart, wYStart, wZStart;							//RJS 12Nov97
	SLong	MaxDist, Dist;										//RJS 02Dec97
	SLong	depth;												//RJS 10Dec98

	wXStart = WCylStartP->gx;									//RJS 12Nov97
	wYStart = WCylStartP->gy;									//RJS 12Nov97
	wZStart = WCylStartP->gz;									//RJS 12Nov97

	maxx = minx + iW;													//RJS 12Nov97
	maxy = miny + iH;													//RJS 12Nov97

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

		if (RelX || RelY || RelZ)
	{
		SLong	traillength = Math_Lib.distance3d(SLong(RelX),SLong(RelY),SLong(RelZ));

		depth = (traillength*density) / HalfRadius;					//RJS 10Dec98
		depth >>= 15;												//RJS 10Dec98
		if (depth <= 0)	depth = 1;								//RJS 25Jun99
//DeadCode DAW 25Jun99 		depth ++;

		wXStep = (WCylEndP->gx - wXStart) / depth;					//RJS 12Nov97
		wYStep = (WCylEndP->gy - wYStart) / depth;					//RJS 12Nov97
		wZStep = (WCylEndP->gz - wZStart) / depth;					//RJS 12Nov97

		XoffGap = (xoff1 - xoff0)/depth;
		YoffGap = (yoff1 - yoff0)/depth;

		RelX /= depth;
		RelY /= depth;
		RelZ /= depth;

		xDelta = xoff0;
		yDelta = yoff0;

		POLYGON.SetOpacityON();
//DEAD 		POLYGON.SetPixelWidth(1);

		for (counter = 0; counter < depth; counter++)
		{
			xDeltCap = xDelta << 1;
			yDeltCap = yDelta << 1;

			RSeed = Noise(wXStart,wYStart,wZStart);

			RandxDelta = RSeed * xDeltCap;
			RandxDelta >>= 8;
			RandxDelta -= xDelta;

			RandyDelta = RSeed * yDeltCap;
			RandyDelta >>= 8;
			RandyDelta -= yDelta;

	//		RandxDelta = ((RSeed*xDeltCap)>>8) - xDelta;			//RJS 12Nov97
	//		RandyDelta = ((RSeed*yDeltCap)>>8) - yDelta;			//RJS 12Nov97

			dopoint0 = dopointRoot;
			dopoint0.bodyx.f += RandxDelta;
			dopoint0.bodyy.f += RandyDelta;

			if (dopoint0.bodyz.f > 100)								//RJS 13Nov97
			{
				dopoint1 = dopoint2 = dopoint3 = dopoint0;

				xDeltCap >>= 1;
				yDeltCap >>= 1;
				xDeltCap = (xDeltCap<0)?-xDeltCap:xDeltCap;
				yDeltCap = (yDeltCap<0)?-yDeltCap:yDeltCap;

				if (xDeltCap || yDeltCap)
				{
					if (xDeltCap > yDeltCap)
					{
						MaxDist = xDeltCap;
						Dist = (RandxDelta<0)?-RandxDelta:RandxDelta;
					}
					else
					{
						MaxDist = yDeltCap;
						Dist = (RandyDelta<0)?-RandyDelta:RandyDelta;
					}

					Dist = MaxDist - Dist;

					Radius = 2 + ((Dist*MaxRadius)/MaxDist);
		
					if (ClipSphere(dopoint0,dopoint1,dopoint2,dopoint3,Radius)==FALSE)
					{
						current_screen->DoSetGlobalAlpha((Radius*255)/MaxRadius);
						POLYGON.createpoly(imapno);
						POLYGON.createvert(dopoint0,minx,miny);
						POLYGON.createvert(dopoint1,maxx,miny);
						POLYGON.createvert(dopoint2,maxx,maxy);
						POLYGON.createvert(dopoint3,minx,maxy);
						POLYGON.drawpoly();
					}
				}
			}

			dopointRoot.bodyx.f += RelX;
			dopointRoot.bodyy.f += RelY;
  			dopointRoot.bodyz.f += RelZ;

			xDelta += XoffGap;
			yDelta += YoffGap;

			wXStart += wXStep;										//RJS 12Nov97
			wYStart += wYStep;										//RJS 12Nov97
			wZStart += wZStep;										//RJS 12Nov97
		}

		current_screen->SetTransparency(SMOKED_OFF);				//RJS 18Jun97

//DEAD		POLYGON.SetPixelWidth(1);
//DEAD 		POLYGON.SetCrossProduct(oldcross);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClipSphere
//Author		Robert Slater
//Date			Fri 21 Aug 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	shape::ClipSphere(DoPointStruc	&dp0,
						  DoPointStruc	&dp1,
						  DoPointStruc	&dp2,
						  DoPointStruc	&dp3,
						  SLong			Radius)
{
	Bool	Clipped = TRUE;
	Float	Radx = Float(Radius);
	Float	Rady;

	Rady = Radx;				//RJS 10Dec98
	Radx *= SphereXScale;
	Rady *= SphereYScale;

	dp0.bodyx.f -= Radx;						
	dp0.bodyy.f += Rady;						
																
	dp1.bodyx.f += Radx;						
	dp1.bodyy.f += Rady;						
																
	dp2.bodyx.f += Radx;						
	dp2.bodyy.f -= Rady;						
																
	dp3.bodyx.f -= Radx;						
	dp3.bodyy.f -= Rady;						
																
	_matrix.SetClipFlags(dp0);
	_matrix.SetClipFlags(dp1);
	_matrix.SetClipFlags(dp2);
	_matrix.SetClipFlags(dp3);

	andedFlags=CF3D_ALL;
	andedFlags&=dp0.clipFlags;
	andedFlags&=dp1.clipFlags;
	andedFlags&=dp2.clipFlags;
	andedFlags&=dp3.clipFlags;
	if (andedFlags==0)
	{
		Clipped = FALSE;
		if (!doingHW3D)
		{
			_matrix.body2screen(dp0);
			_matrix.body2screen(dp1);
			_matrix.body2screen(dp2);
			_matrix.body2screen(dp3);
		}
	}

	return(Clipped);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClipCylinder
//Author		Robert Slater
//Date			Fri 21 Aug 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	shape::ClipCylinder(DoPointStruc	&dp0,
							DoPointStruc	&dp1,
							DoPointStruc	&dp2,
							DoPointStruc	&dp3,
							SLong			xRadius,
							SLong			yRadius	)
{
	Bool	Clipped = TRUE;
	Float	xRad = Float(xRadius);
	Float	yRad = Float(yRadius);

	xRad *= SphereXScale;
	yRad *= SphereYScale;

	dp0.bodyx.f += xRad;						
	dp0.bodyy.f += yRad;						
																
	dp1.bodyx.f -= xRad;						
	dp1.bodyy.f -= yRad;						
																
	dp2.bodyx.f -= xRad;						
	dp2.bodyy.f -= yRad;						
																
	dp3.bodyx.f += xRad;						
	dp3.bodyy.f += yRad;						
																
	_matrix.SetClipFlags(dp0);
	_matrix.SetClipFlags(dp1);
	_matrix.SetClipFlags(dp2);
	_matrix.SetClipFlags(dp3);

	andedFlags=CF3D_ALL;
	andedFlags&=dp0.clipFlags;
	andedFlags&=dp1.clipFlags;
	andedFlags&=dp2.clipFlags;
	andedFlags&=dp3.clipFlags;
	if (andedFlags==0)
	{
		Clipped = FALSE;
		if (!doingHW3D)
		{
			_matrix.body2screen(dp0);
			_matrix.body2screen(dp1);
			_matrix.body2screen(dp2);
			_matrix.body2screen(dp3);
		}
	}

	return(Clipped);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		imaptrailcylWrapped
//Author		Robert Slater
//Date			Tue 17 Nov 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::imaptrailcylWrapped(UWord   vertex1, UWord vertex2,
								ImageMapNumber imapno,
								SWord	radius,
								ImageMapNumber imapno2,
								SWord	miniy, SWord maxiy,
								SWord	xoff0, SWord yoff0,
								SWord	xoff1, SWord yoff1,
								SWord	minix2,SWord miniy2,
								SWord	maxix2,SWord maxiy2,
								Bool	nocylinder	)
{
//DeadCode RJS 21Apr99 	UByteP	adptr = (UByteP) object_obj3d->AnimPtr; 			
	ULong	thewidth, theheight;
	DoPointStruc dopoint0,dopoint1,dopoint2,dopoint3,oldpoint;
 	Float	xdelt1 = (Float) xoff0;
 	Float	ydelt1 = (Float) yoff0;
 	Float	xdelt2 = (Float) xoff1;
 	Float	ydelt2 = (Float) yoff1;
 	Bool	oldcross;
	SLong	traillength,nopixels;
	SLong	dx,dy,dz;
	SWord	maxix,minix;
	Bool	dosphere = FALSE;
	Bool	nocyl = FALSE;

//DEAD  	oldcross = POLYGON.SetCrossProduct(FALSE);
  
  	ImageMapDescPtr imptr = Image_Map.GetImageMapPtr(imapno);
	maxix = imptr->w;
	minix = 0;
 
   	dopoint0 = dopoint1 = newco[vertex1];				
   	oldpoint = dopoint2 = dopoint3 = newco[vertex2];

	if (xoff0 || xoff1 || yoff0 || yoff1)
	{
		dx = dopoint0.bodyx.f - dopoint2.bodyx.f;
		dy = dopoint0.bodyy.f - dopoint2.bodyy.f;
		dz = dopoint0.bodyz.f - dopoint2.bodyz.f;

		traillength = Math_Lib.distance3d(dx,dy,dz);

		// Assume 1 pixel is 8 cm...

		nopixels = traillength >> 3;
		nopixels = nopixels / maxix;
		if (nopixels)
			maxix = maxix * nopixels;

		SLong	vislength = Math_Lib.distance3d(dx,dy,0);
		if (vislength)
		{
			vislength = traillength / vislength;
			if (vislength > 3)
			{
				dosphere = TRUE;
				if (vislength > 7)
					nocyl = TRUE;
			}
		}
		else
		{
			nocyl = TRUE;
			dosphere = TRUE;
		}

		if (!nocyl || !nocylinder)
		{
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
				if (!doingHW3D)
				{
					_matrix.body2screen(dopoint0);
					_matrix.body2screen(dopoint1);
					_matrix.body2screen(dopoint2);
					_matrix.body2screen(dopoint3);
				}

//DEAD   				POLYGON.SetPixelWidth(1<<Save_Data.pixelsize);			
   				POLYGON.createpoly(imapno);								
   								
				maxiy--;
				miniy++;
				POLYGON.createvert(dopoint3,maxix,miniy);					
   				POLYGON.createvert(dopoint2,maxix,maxiy);					
   				POLYGON.createvert(dopoint1,minix,maxiy);					
  				POLYGON.createvert(dopoint0,minix,miniy);
   																
   				POLYGON.drawpoly();									
//DEAD   				POLYGON.SetPixelWidth(1);
			}
		}

		if (dosphere && imapno2)			//RJS 21JAN99
		{
			SLong	pooradius = (3*radius)>>2;
			if (pooradius)
			{
				int	nospheres = 1 + (vislength / pooradius);
				int	i;
				Float	dxpoo,dypoo,dzpoo;

				dxpoo = Float(dx);
				dypoo = Float(dy);
				dzpoo = Float(dz);

				if (nospheres > 8)
					nospheres = 8;
				
				dxpoo /= nospheres;
				dypoo /= nospheres;
				dzpoo /= nospheres;

				newco[3] = oldpoint;

				for (i=0; i < nospheres; i++)
				{
					imapsphere(3,radius,imapno2,minix2,miniy2,maxix2,maxiy2);
					newco[3].bodyx.f += dxpoo;
					newco[3].bodyy.f += dypoo;
					newco[3].bodyz.f += dzpoo;
				}
			}
		}
	}
	else
	{
		if (imapno2)								//RJS 21Jan99
		{
			newco[3] = oldpoint;
			newco[3].bodyx.f = (dopoint0.bodyx.f + dopoint2.bodyx.f)/2;
			newco[3].bodyy.f = (dopoint0.bodyy.f + dopoint2.bodyy.f)/2;
			newco[3].bodyz.f = (dopoint0.bodyz.f + dopoint2.bodyz.f)/2;

			imapsphere(3,radius,imapno2,minix2,miniy2,maxix2,maxiy2);
		}
	}

//DEAD   	POLYGON.SetCrossProduct(oldcross);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClipSphereSpin
//Author		Robert Slater
//Date			Thu 19 Nov 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	shape::ClipSphereSpin(	DoPointStruc	&dp0,
						  		DoPointStruc	&dp1,
						  		DoPointStruc	&dp2,
						  		DoPointStruc	&dp3,
						  		SLong			Radius,
								SWord			angle	)
{
	Bool	Clipped = TRUE;
//DeadCode RJS 26May99 	Float	RadX = Float(Radius);
//DeadCode RJS 26May99 	Float	RadY;
 	SWord 	sinAng,cosAng;
	SLong	x0,x1,x2,x3;
	SLong	y0,y1,y2,y3;
	SLong 	m[4];
	SLong	nx,ny;

//DeadCode RJS 26May99 	RadY = RadX;
//DeadCode RJS 26May99 	RadX *= SphereXScale;
//DeadCode RJS 26May99 	RadY *= SphereYScale;
//DeadCode RJS 26May99 
//DeadCode RJS 26May99 	x0 = -RadX;
//DeadCode RJS 26May99 	y0 = RadY;
//DeadCode RJS 26May99 
//DeadCode RJS 26May99 	x1 = RadX;
//DeadCode RJS 26May99 	y1 = RadY;
//DeadCode RJS 26May99 
//DeadCode RJS 26May99 	x2 = RadX;
//DeadCode RJS 26May99 	y2 = -RadY;
//DeadCode RJS 26May99 
//DeadCode RJS 26May99 	x3 = -RadX;
//DeadCode RJS 26May99 	y3 = -RadY;

	x0 = -Radius;
	y0 = Radius;

	x1 = Radius;
	y1 = Radius;

	x2 = Radius;
	y2 = -Radius;

	x3 = -Radius;
	y3 = -Radius;

	Math_Lib.high_sin_cos((Angles)angle,sinAng,cosAng);

	m[0]=m[3]=SLong(cosAng);
	m[1]=SLong(sinAng);
	m[2]=-SLong(sinAng);

	nx=(m[0]*x0)/ANGLES_FRACT+(m[1]*y0)/ANGLES_FRACT;
	ny=(m[2]*x0)/ANGLES_FRACT+(m[3]*y0)/ANGLES_FRACT;

	x0 = nx;
	y0 = ny;

	nx=(m[0]*x1)/ANGLES_FRACT+(m[1]*y1)/ANGLES_FRACT;
	ny=(m[2]*x1)/ANGLES_FRACT+(m[3]*y1)/ANGLES_FRACT;

	x1 = nx;
	y1 = ny;

	nx=(m[0]*x2)/ANGLES_FRACT+(m[1]*y2)/ANGLES_FRACT;
	ny=(m[2]*x2)/ANGLES_FRACT+(m[3]*y2)/ANGLES_FRACT;

	x2 = nx;
	y2 = ny;

	nx=(m[0]*x3)/ANGLES_FRACT+(m[1]*y3)/ANGLES_FRACT;
	ny=(m[2]*x3)/ANGLES_FRACT+(m[3]*y3)/ANGLES_FRACT;

	x3 = nx;
	y3 = ny;

	dp0.bodyx.f += Float(x0) * SphereXScale;	
	dp0.bodyy.f += Float(y0) * SphereYScale;
						
	dp1.bodyx.f += Float(x1) * SphereXScale;	
	dp1.bodyy.f += Float(y1) * SphereYScale;
						
	dp2.bodyx.f += Float(x2) * SphereXScale;
	dp2.bodyy.f += Float(y2) * SphereYScale;
						
	dp3.bodyx.f += Float(x3) * SphereXScale;
	dp3.bodyy.f += Float(y3) * SphereXScale;
	
	_matrix.SetClipFlags(dp0);
	_matrix.SetClipFlags(dp1);
	_matrix.SetClipFlags(dp2);
	_matrix.SetClipFlags(dp3);

	andedFlags=CF3D_ALL;
	andedFlags&=dp0.clipFlags;
	andedFlags&=dp1.clipFlags;
	andedFlags&=dp2.clipFlags;
	andedFlags&=dp3.clipFlags;
	if (andedFlags==0)
	{
		Clipped = FALSE;
		if (!doingHW3D)
		{
			_matrix.body2screen(dp0);
			_matrix.body2screen(dp1);
			_matrix.body2screen(dp2);
			_matrix.body2screen(dp3);
		}
	}

	return(Clipped);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClipSphereRatio
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
Bool	shape::ClipSphereRatio(	DoPointStruc	&dp0,
								DoPointStruc	&dp1,
								DoPointStruc	&dp2,
								DoPointStruc	&dp3,
								SLong			Radius,
								SWord			wx,
								SWord			wy,
								bool			ispivoted	)
{
	Bool	Clipped = TRUE;
	Float	Radx = Float(Radius);
	Float	Rady;
	SLong	ratio = (wy << 16)/wx;
	SLong	rady;


	rady = (Radius * ratio);

	Radx *= SphereXScale;
	if (ispivoted)
	{
		rady >>= 15;
		Rady = Float(rady);
		Rady *= SphereYScale;

//DeadCode RJS 26May99 		if (View_Point->PolyPitEnabled() || (View_Point->viewnum.viewmode == VM_InsideCheat))
		if (View_Point->roll)									//RJS 26May99
		{
			SWord 	sinAng,cosAng;
			SLong	x0,x1,x2,x3;
			SLong	y0,y1,y2,y3;
			SLong 	m[4];
			SLong	nx,ny;
			SWord	angle = View_Point->roll;


			x0 = -Radx;
			y0 = Rady;

			x1 = Radx;
			y1 = Rady;

			x2 = Radx;
			y2 = 0;

			x3 = -Radx;
			y3 = 0;

			Math_Lib.high_sin_cos((Angles)angle,sinAng,cosAng);

			m[0]=m[3]=SLong(cosAng);
			m[1]=SLong(sinAng);
			m[2]=-SLong(sinAng);

			nx=(m[0]*x0)/ANGLES_FRACT+(m[1]*y0)/ANGLES_FRACT;
			ny=(m[2]*x0)/ANGLES_FRACT+(m[3]*y0)/ANGLES_FRACT;

			x0 = nx;
			y0 = ny;

			nx=(m[0]*x1)/ANGLES_FRACT+(m[1]*y1)/ANGLES_FRACT;
			ny=(m[2]*x1)/ANGLES_FRACT+(m[3]*y1)/ANGLES_FRACT;

			x1 = nx;
			y1 = ny;

			nx=(m[0]*x2)/ANGLES_FRACT+(m[1]*y2)/ANGLES_FRACT;
			ny=(m[2]*x2)/ANGLES_FRACT+(m[3]*y2)/ANGLES_FRACT;

			x2 = nx;
			y2 = ny;

			nx=(m[0]*x3)/ANGLES_FRACT+(m[1]*y3)/ANGLES_FRACT;
			ny=(m[2]*x3)/ANGLES_FRACT+(m[3]*y3)/ANGLES_FRACT;

			x3 = nx;
			y3 = ny;

			dp0.bodyx.f += Float(x0);	
			dp0.bodyy.f += Float(y0);	
								
			dp1.bodyx.f += Float(x1);	
			dp1.bodyy.f += Float(y1);	
								
			dp2.bodyx.f += Float(x2);	
			dp2.bodyy.f += Float(y2);	
								
			dp3.bodyx.f += Float(x3);	
			dp3.bodyy.f += Float(y3);
		}
		else
		{
			dp0.bodyx.f -= Radx;						
			dp0.bodyy.f += Rady;						
																
			dp1.bodyx.f += Radx;						
			dp1.bodyy.f += Rady;						
																
			dp2.bodyx.f += Radx;						

			dp3.bodyx.f -= Radx;	
		}
	}
	else
	{
		rady >>= 16;
		Rady = Float(rady);
		Rady *= SphereYScale;

		dp0.bodyx.f -= Radx;						
		dp0.bodyy.f += Rady;						
																
		dp1.bodyx.f += Radx;						
		dp1.bodyy.f += Rady;						
																
		dp2.bodyx.f += Radx;						
		dp2.bodyy.f -= Rady;						

		dp3.bodyx.f -= Radx;						
		dp3.bodyy.f -= Rady;						
	}
																
	_matrix.SetClipFlags(dp0);
	_matrix.SetClipFlags(dp1);
	_matrix.SetClipFlags(dp2);
	_matrix.SetClipFlags(dp3);

	andedFlags=CF3D_ALL;
	andedFlags&=dp0.clipFlags;
	andedFlags&=dp1.clipFlags;
	andedFlags&=dp2.clipFlags;
	andedFlags&=dp3.clipFlags;
	if (andedFlags==0)
	{
		Clipped = FALSE;
		if (!doingHW3D)
		{
			_matrix.body2screen(dp0);
			_matrix.body2screen(dp1);
			_matrix.body2screen(dp2);
			_matrix.body2screen(dp3);
		}
	}

	return(Clipped);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FixedPolyOnFloor
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
void shape::FixedPolyOnFloor(Coords3DList*	adptr,
							 Coords3DList*	lastadptr,
							 SWord			    xoff0,
							 SWord				yoff0,
							 SWord			    xoff1,
							 SWord				yoff1,
							 ImageMapNumber	    imapno, 
							 SWord				minx,
							 SWord				miny,
							 SWord				maxx,
							 SWord				maxy	)

{
	if (xoff0 || xoff1 || yoff0 || yoff1)
	{
		DoPointStruc dp0,dp1,dp2,dp3;

		dp0.bodyx.i = -xoff0;
		dp0.bodyy.i = 0;
		dp0.bodyz.i = -yoff0;

		_matrix.transformNC(fpobject_matrix,&dp0);

		dp0.bodyx.f += newco[1].bodyx.f;
		dp0.bodyy.f += newco[1].bodyy.f;
		dp0.bodyz.f += newco[1].bodyz.f;

		_matrix.SetClipFlags(dp0);
		if (!doingHW3D) _matrix.body2screen(dp0);
		dp0.intensity=
		dp0.specFlip=
		dp0.specular=-1;
	
		dp1.bodyx.i = xoff0;
		dp1.bodyy.i = 0;
		dp1.bodyz.i = yoff0;

		_matrix.transformNC(fpobject_matrix,&dp1);

		dp1.bodyx.f += newco[1].bodyx.f;
		dp1.bodyy.f += newco[1].bodyy.f;
		dp1.bodyz.f += newco[1].bodyz.f;

		_matrix.SetClipFlags(dp1);
		if (!doingHW3D) _matrix.body2screen(dp1);
		dp1.intensity=
		dp1.specFlip=
		dp1.specular=-1;		

		dp2.bodyx.i = -xoff1;
		dp2.bodyy.i = 0;
		dp2.bodyz.i = -yoff1;

		_matrix.transformNC(fpobject_matrix,&dp2);

		dp2.bodyx.f += newco[0].bodyx.f;
		dp2.bodyy.f += newco[0].bodyy.f;
		dp2.bodyz.f += newco[0].bodyz.f;

		_matrix.SetClipFlags(dp2);
		if (!doingHW3D) _matrix.body2screen(dp2);
		dp2.intensity=
		dp2.specFlip=
		dp2.specular=-1;

		dp3.bodyx.i = xoff1;
		dp3.bodyy.i = 0;
		dp3.bodyz.i = yoff1;

		_matrix.transformNC(fpobject_matrix,&dp3);

		dp3.bodyx.f += newco[0].bodyx.f;
		dp3.bodyy.f += newco[0].bodyy.f;
		dp3.bodyz.f += newco[0].bodyz.f;

		_matrix.SetClipFlags(dp3);
		if (!doingHW3D) _matrix.body2screen(dp3);
		dp3.intensity=
		dp3.specFlip=
		dp3.specular=-1;

		SLong	dx = SLong(newco[0].bodyx.f - newco[1].bodyx.f);
		SLong	dy = SLong(newco[0].bodyy.f - newco[1].bodyy.f);
		SLong	dz = SLong(newco[0].bodyz.f - newco[1].bodyz.f);
		SLong	traillength = Math_Lib.distance3d(dx,dy,dz);
		SLong	nopixels;

		// Assume 1 pixel is 8 cm...

		nopixels = traillength >> 3;
		nopixels = nopixels / maxx;
		if (nopixels)
			maxx = maxx * nopixels;

		POLYGON.createpoly(imapno);
		POLYGON.createvert(dp0,minx,miny);
		POLYGON.createvert(dp1,maxx,miny);
		POLYGON.createvert(dp2,maxx,maxy);
		POLYGON.createvert(dp3,minx,maxy);
		POLYGON.drawpoly();
	}
}
