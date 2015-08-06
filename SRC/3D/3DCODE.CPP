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
//Filename       3dcode.cpp
//System         
//Author         Paul.   
//Date           Tue 22 Aug 1995
//Description    
//------------------------------------------------------------------------------
	#include	"DOSDefs.h"	
#define F_GRAFIX												
#define F_BATTLE
	#include 	"myerror.h"
	#include	"World.h"
	#include 	"aaa.h"
	#include	"AnimData.h"									

	#include	"3DCom.h"
	#include	"Matrix.H"

	#include	"btree.h"
	#include	"tilemake.h"
	#include	"migLand.h"										
	#include	"3DCode.h"

	#include	"transite.h"										
	#include	"savegame.h"									
	#include	"winmove.h"										
	#include	"shpinstr.h"									

	#include	"FileMan.h"
	#include	"mymath.h"
	#include	"Polygon.h"
	#include	"LandScap.h"									//PD 06Nov95
	#include	"ViewSel.h"										//PD 20Feb96
	#include	"Shapes.H"										//PD 08Mar96
	#include	"flymodel.h"									//PD 12Apr96
	#include	"Mytime.h"										//JIM 03Jun96
	#include	"ai.h"											//JIM 03Jun96
	#include	"mouse.h"
	#include	"collided.h"									//PD 08Oct96
	#include	"missman2.h"									//RJS 23Oct96
	#include	"Persons2.h"									//PD 10Dec96

	#include	"lghtshad.h"									//RJS 02Sep97
	#include	"miles.h"										//RJS 26Feb98

	#include "worldinc.h" // To check some #defines
	#include "modvec.h" // To check some #defines
	#include "Model.h" // To check some #defines
	#include	<stdio.h>
	#include	"monotxt.h"

	#include "overlay.h"
	#include "prof.h"


	class	ThreeDee	Three_Dee;
	
	extern	class	matrix 	_matrix;
	extern 	class	Wrapper _Wrapper;
	extern  Replay _Replay;

#include "replay.h"

	#if	DEBUGGING												//PD 23Jan96
	SLong	polygon_count;										//PD 23Jan96
	#endif														//PD 23Jan96

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ThreeDee
//Author		Robert Slater
//Date			Tue 24 Feb 1998
//
//Description	Constructor
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
CON	ThreeDee::ThreeDee()
{
	b3DRunning=FALSE;
	MasterPalettePtr = NULL;
	NewPalettePtr = new RGBINFO[256*8];

	sunanimptr = new UByte[sizeof(SunAnimData)];
	sunanimptr = sizeof(SunAnimData) + (1<<MINANIM) + (1<<SUNANIM);//RJS 21Apr99
	pMigLand=NULL;
	pTMake=NULL;

	normalDataPtr=NULL;
	pNormalLookup=NULL;

	View_Point=NULL;
	nomorereallygetdata=false;
	bt=NULL;

// We need animdata for the lens-flare, which doesn't get deleted, or created on the fly.
	int animdatasize= sizeof(FlareAnimData);
	UByteP	p = new UByte[animdatasize+16];	//make it bigger, just to be safe
	p[0]=0;									//clear itemstate
	lensflareanim = p;											//RJS 25Feb00
	lensflareanim = animdatasize + (1<<MINANIM) + (1<<FLAREANIM);//RJS 25Feb00
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ThreeDee
//Author		Robert Slater
//Date			Tue 24 Feb 1998
//
//Description	Destructor...
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
DES	ThreeDee::~ThreeDee()
{
	delete []NewPalettePtr;
//DeadCode RJS 21Apr99 	delete []sunanimptr;
	if (normalDataPtr!=NULL) delete[]normalDataPtr,normalDataPtr=NULL;
	if (pNormalLookup!=NULL) delete[]pNormalLookup,pNormalLookup=NULL;

	sunanimptr.Delete();										//RJS 21Apr99
	lensflareanim.Delete();										//RJS 25Feb00
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Init3D
//Author		Paul.   
//Date			Tue 17 Oct 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ThreeDee::Init3D(Window* win,ViewPoint*	vp)				
{
//DeadCode JIM 26Mar99 	Trans_Obj.CleanUpTrailList();								//RJS 18Feb99
	Save_Data.fieldOfView=ANGLES_45Deg;

	buffetData.hdg=
		buffetData.pitch=
		buffetData.roll=ANGLES_0Deg;

	buffetData.delta.X=
		buffetData.delta.Y=
		buffetData.delta.Z=0;

	View_Point=vp;
	
	current_screen=win;
	current_display=win->Master();
	_matrix.SetWin(win);
	b3DRunning=TRUE;
//DEAD	POLYGON.ClearAliasFlag();									//RJS 29Oct96
	if (!bt)
	{
		if (Save_Data.fSoftware)
			bt = new btree(LandTreeSize,ObjectTreeSize);
		else
			bt = new btree(32,ObjectTreeSize);
	}
//TempCode PD 04Feb99 	aircraft_tree= new btree(1,AircraftTreeSize);

	current_screen->MakeIntensityData();
	shapecheat = FALSE;											//RJS 18Sep96
	oldtime = -1;												//RJS 24Oct96
	time_minutes = -1;											//RJS 23Apr98
	whereinpal = -1;												//RJS 22Oct96
	whichpal = PAL_DAY;											//RJS 02Sep97
	newpalettes = NULL;											//RJS 22Oct96
	SHAPE.SunInVision = FALSE;									//RJS 26Nov96
	if (Manual_Pilot.ControlledAC2)
		((AirStrucPtr)Manual_Pilot.ControlledAC2)->fly.gforce = 0;	//RJS 12May97
//	current_screen->DoInitLand();

	Trans_Obj.CloudTotal = 0;									//RJS 09Jul97
	Trans_Obj.CloudTimer = 0;									//RJS 09Jul97

	Trans_Obj.GScatterTimer = 0;								//RJS 21Oct97
	Trans_Obj.GScatterCnt = 0;									//RJS 21Oct97
	if (vp)
	{
		View_Point->isMagic = FALSE;									//RJS 12Aug97
		View_Point->MagicCode = 0;									//RJS 12Aug97
	}

	if (pMigLand==NULL)	
	{
		pMigLand=new CMigLand;
		pTMake=new TMake;
	}
	PaletteBlender(View_Point->TimeOfDay());
	pMigLand->BigInit(View_Point);
	pTMake->Init(vp->World.X,vp->World.Z,win);
	OverLay.LoaderScreen((2<<8)+128+96);
	MaxShapeCount = FILEMAN.filesindir(DIR_SHAPES) - 1;
	MaxShape2Count = 255 + FILEMAN.filesindir(DIR_MOBSHPS);
	MaxGroupCount = 511 + FILEMAN.filesindir(DIR_GROUPS);

	CheatStart[0] = 1;
	CheatStart[1] = 257;
	CheatStart[2] = 513;

	CheatEnd[0] = MaxShapeCount;
	CheatEnd[1] = MaxShape2Count;
	CheatEnd[2] = MaxGroupCount;

	if ((CheatEnd[0] - CheatStart[0]) < 0)
	{
		CheatStart[0] = 0;
		CheatEnd[0] = 0;
	}

	if ((CheatEnd[1] - CheatStart[1]) < 0)
	{
		CheatStart[1] = 0;
		CheatEnd[1] = 0;
	}

	if ((CheatEnd[2] - CheatStart[2]) < 0)
	{
		CheatStart[2] = 0;
		CheatEnd[2] = 0;
	}

 	SHAPE.ClearRadar();											//RJS 25Jun98

	SunAnimData*	adptr = (SunAnimData*) sunanimptr;		//RJS 02Jul98
	adptr->frameno = 0;										//RJS 02Jul98
	adptr->nolaunchers = 0;									//RJS 02Jul98


	if (normalDataPtr==NULL)
		normalDataPtr=new NormalData[256];
	if (pNormalLookup==NULL)
		pNormalLookup=new UByte[256];
	lastSunPos.X=lastSunPos.Y=lastSunPos.Z=0;

	ConstructNormalData();

	ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(MAPZ);

	mapdistz = sdptr->sx << 6; // cos map is 4cm
	mapoffx = mapoffy = 0;

	SHAPE.SetDistScale();//RJS 02Nov98

	OverLay.LoaderScreen((2<<8)+128+96+16);

	radarOn = FALSE;											//RJS 06Nov98
	groundlockOn = FALSE;										//RJS 04Jun99

	supercheatitem = NULL;

	SHAPE.SphereXScale = 1;										//RJS 02Dec98
	SHAPE.SphereYScale = 1;										//RJS 02Dec98

	if (Save_Data.gamedifficulty[GD_PERFECTRADARASSISTEDGUNSIGHT])	//RJS 09Dec98
		radarOn = TRUE;												//RJS 09Dec98

	if (Save_Data.gamedifficulty[GD_REALISTICRADARASSISTEDGUNSIGHT])//RJS 04Jun99
	{
		radarOn = TRUE;
		groundlockOn = TRUE;									//RJS 04Jun99
	}

	havematrix = false;				//RJS 10Dec98

	OverLay.InitInfoTexts();

	OverLay.LoaderScreen((2<<8)+255);

	if (Manual_Pilot.ControlledAC2)
	{
		PolyPitAnimData* adptr = (PolyPitAnimData*)	Manual_Pilot.ControlledAC2->Anim;

		adptr->lastweapindex = 0xFF;
		adptr->acprevammoleft = 0xFFFF;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Done3D
//Author		Paul.   
//Date			Tue 17 Oct 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ThreeDee::Done3D()
{
//TempCode PD 23Nov98 	Save_Data.gameSettings=gameSettings;
	b3DRunning=FALSE;											//PD 10Jun97
	GREY3DTYPE	gtdt = NOGREY3D;								//PD 29Sep96
//DEAD	POLYGON.SetGrey3DType(gtdt);								//PD 29Sep96
	if (pMigLand!=NULL)	delete pMigLand,pMigLand=NULL;		//PD 18Jan98
	if (pTMake!=NULL){
		pTMake->Exit();
		delete pTMake;
		pTMake=NULL;
	}
	delete(bt);
//TempCode PD 04Feb99 	delete aircraft_tree;										//PD 28Oct98
	aircraft_tree=NULL;											//PD 28Oct98
	bt=NULL;													//JIM 06Oct96
	Land_Scape.Exit();											//PD 18Oct96

	if (normalDataPtr!=NULL) delete[]normalDataPtr,normalDataPtr=NULL;
	if (pNormalLookup!=NULL) delete[]pNormalLookup,pNormalLookup=NULL;

	OverLay.ReleaseInfoTexts();

	SHAPE.DeleteAllSmokeTrails();								//RJS 18Feb99
}

static char	fnum=0;
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		render
//------------------------------------------------------------------------------
//Author		Paul.   
//Date			Tue 22 Aug 1995
//Modified	
//
//Description	renders a 3D scene in a viewport from a given viewpoint
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

ShapeNum operator++ (ShapeNum& s,int) {return (ShapeNum)((*(UWord*)&s)++);}
ShapeNum operator-- (ShapeNum& s,int) {return (ShapeNum)((*(UWord*)&s)--);}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		render3d
//Author		Robert Slater
//Date			Tue 8 Sep 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ThreeDee::render3d(Window *screen, ViewPoint* vp,WorldStuff *world)//PD 22Apr96
{
	current_screen=screen;

	ROWANSURFACEDESC rsd;
	if (Save_Data.fSoftware)	current_screen->DoLockScr(&rsd);

	View_Point=vp;
	bt->SetupBTree(screen,vp);
	nomorereallygetdata=true;
//TempCode PD 04Feb99 	aircraft_tree->SetupBTree(screen,vp);						//PD 28Oct98
	SHAPE.SetView(vp,screen);

	Bool	bDoingHW3D;

	if (!shapecheat)
	{
		if (Key_Tests.KeyHeld3d(NEXTSHAPEDN))
			Save_Data.fieldOfView+=ANGLES_2Deg;
		else if (Key_Tests.KeyHeld3d(NEXTSHAPEUP))
			Save_Data.fieldOfView-=ANGLES_2Deg;

		if (Save_Data.fieldOfView<ANGLES_45Deg)
			Save_Data.fieldOfView=ANGLES_45Deg;
		else if (Save_Data.fieldOfView>ANGLES_60Deg)
			Save_Data.fieldOfView=ANGLES_60Deg;
	}

	bDoingHW3D = current_screen->DoingHardware3D();				//PD 19Nov97
	current_screen->DoSetViewParams(Save_Data.fieldOfView,screen,vp);//PD 01Oct98
	_matrix.SetViewParams(current_screen,Save_Data.fieldOfView,0x7FFFFFFF);

	SHAPE.SetDistScale();
//DEAD	current_screen->BeginScene();									//PD 17Feb97

	fnum++;

	View_Point->BlockTick(BOOL_Align); //DAW 10/02/00
//DeadCode DAW 10Sep99 	long	ft=View_Point->FrameTime();
//DeadCode DAW 10Sep99 	static int col=0;
//DeadCode DAW 10Sep99 	col=(col+2)%512;
//DeadCode DAW 10Sep99 	UByteP(0xB0000)[20*160+col]=ft+'0';
	View_Point->SelectView();									//PD 19Feb96
	current_screen->BeginScene();									//PD 17Feb97
	Bool	drawpolypit;
#ifndef NDEBUG													//DAW 20Dec96
	SLong			index;
	if (shapecheat)
	{
		MinAnimData*	adptr;
		SLong			ThisShape = Manual_Pilot.ControlledAC2->shape;//RJS 20May98

		if (Key_Tests.KeyPress3d(NEXTSHAPEUP))
		{
			adptr = (MinAnimData*) Manual_Pilot.ControlledAC2->Anim;
			if (View_Point->deathview == TRUE)
				adptr->itemstate = DEAD;
			else
				adptr->itemstate = ALIVE;

			ThisShape++;
			if (ThisShape > CheatEnd[CheatPos])
			{
				CheatPos++;
				if (CheatPos > 2)
					CheatPos = 0;

				if (CheatStart[CheatPos] == 0)
				{
					CheatPos++;
					if (CheatPos > 2)
						CheatPos = 0;
					else
					{
						if (CheatStart[CheatPos] == 0)
						{
							CheatPos++;
							if (CheatPos > 2)
								CheatPos = 0;
						}
					}
				}

				ThisShape = CheatStart[CheatPos];
			}

			char	shite[32];
			sprintf(shite,"Shape : %d  ",ThisShape);
			Mono_Text.PrintAt(55,5,(UByteP)shite);
								
			Manual_Pilot.ControlledAC2->shape = (ShapeNum) ThisShape;//RJS 20May98
		}

		if (Key_Tests.KeyPress3d(NEXTSHAPEDN))
		{
			adptr = (MinAnimData*) Manual_Pilot.ControlledAC2->Anim;
			if (View_Point->deathview == TRUE)
				adptr->itemstate = DEAD;
			else
				adptr->itemstate = ALIVE;

			ThisShape--;
			if (ThisShape < CheatStart[CheatPos])
			{
				CheatPos--;
				if (CheatPos < 0)
					CheatPos = 2;

				if (CheatStart[CheatPos] == 0)
				{
					CheatPos--;
					if (CheatPos < 0)
						CheatPos = 2;
					else
					{
						if (CheatStart[CheatPos] == 0)
						{
							CheatPos--;
							if (CheatPos < 0)
								CheatPos = 2;
						}
					}
				}

				ThisShape = CheatEnd[CheatPos];
			}

			char	shite[32];
			sprintf(shite,"Shape : %d  ",ThisShape);
			Mono_Text.PrintAt(55,5,(UByteP)shite);
								
			Manual_Pilot.ControlledAC2->shape = (ShapeNum) ThisShape;//RJS 20May98
		}

		if (Key_Tests.KeyPress3d(DROPBOMB))
		{
			adptr = (MinAnimData*) Manual_Pilot.ControlledAC2->Anim;
			adptr->itemstate++;
		}
	}

	SuperShapeCheat();

	if (Key_Tests.KeyPress3d(SHAPECHEATTOG))
	{
		if (shapecheat)
		{
			Manual_Pilot.ControlledAC2->shape = CheatSave;
			shapecheat = FALSE;
		}
		else
		{
			CheatSave = Manual_Pilot.ControlledAC2->shape;
			for (index = 0; index < 3; index++)
			{
				if (	(CheatSave >= CheatStart[index])
					&&	(CheatSave <= CheatEnd[index])	)
				{
					CheatPos = index;
					break;
				}
			}

			shapecheat = TRUE;
		}
	}
#endif

	drawpolypit = View_Point->PolyPitEnabled();					
	_matrix.SetZScale(current_screen);							
	OverLay.SetViewpoint(View_Point);
	OverLay.SetScreen(current_screen);

	init_scene(world, vp);
	ANGLES h,p,r;												
	if(drawpolypit)												
	{															
		//Get gunsight stuff here, during blocktick!
		if (Manual_Pilot.ControlledAC2)					//RJS 25Jun99
		{
			WeapAnimData*	weapon;
			SLong			index = 0;
			SLong	xpos, ypos, zpos;
			SLong	wpcnt = 0;
			UWord	mvel,mdelay,mburst;

			SHAPE.gunsightX = 0;
			SHAPE.gunsightY = 0;
			SHAPE.gunsightZ = 0;
			SHAPE.gunsightmvel = 9000;
			while (index < 3)
			{
				weapon = SHAPE.GetWeaponLauncher(Manual_Pilot.ControlledAC2,index,xpos,ypos,zpos,mvel,mdelay,mburst,LT_BULLET);
				if (weapon)
				{
					SHAPE.gunsightX += xpos;
					SHAPE.gunsightY += ypos;
					SHAPE.gunsightZ += zpos;

					SHAPE.gunsightmvel = mvel;

					wpcnt++;
 				}
				index++;
 			}

			if (wpcnt)
			{
				SHAPE.gunsightX /= wpcnt;
				SHAPE.gunsightY /= wpcnt;
				SHAPE.gunsightZ /= wpcnt;
			}

			Manual_Pilot.ControlledAC2->fly.pModel->BackupForGunsight();//RJS 25Jun99
		}

		View_Point->GetPolyPitAngles(h,p,r);
		_Miles.SetCockpit(TRUE);
	}
	else
	{
		if (View_Point->viewnum.viewmode == VM_InsideCheat)			//RJS 16Jun99
			_Miles.SetCockpit(TRUE);
		else
			_Miles.SetCockpit(FALSE);
	}

	SHAPE.ResetRadar(Manual_Pilot.ControlledAC2,viewer_x,viewer_y,viewer_z);//RJS 09Nov98
	PaletteBlender(View_Point->TimeOfDay());						//RJS 10Mar98
	pTMake->BuildShadowList(world,vp);							//PD 22Oct98
	if (Manual_Pilot.ControlledAC2)
	{
		//if player is MiG15 then change shape to complex MiG
		ShapeNum manualPilotShape=Manual_Pilot.ControlledAC2->shape;
		if (manualPilotShape==CMIG15) Manual_Pilot.ControlledAC2->shape=MIG15;
		do_objects();		
		Manual_Pilot.ControlledAC2->shape=manualPilotShape;
	}
	else do_ui_objects();

	SHAPE.SetRadar();											//RJS 06Nov98

	Land_Scape.RenderLandscape(	screen,View_Point,							
								fpviewer_matrix,					
								viewer_x,viewer_y,viewer_z,		
								vp->hdg);
	View_Point->BlockTick(FALSE);

//DeadCode DAW 22Jun99 	View_Point->BlockTick(FALSE);

	current_screen->DoFlushLandDraw();
	// Do not call possmove cycle before do_objects();			//ARM 26Jul96
	Add_Sun(*vp,world);											//RJS 23Mar98
	Land_Scape.CloudLayer(View_Point);							//RJS 30Mar98
	SHAPE.InitCloudFade();									//RJS 15Jul98
	render_scene();												//PD 20Dec95
	SHAPE.SetCloudFade();										//RJS 15Jul98

	Land_Scape.TidyUp();

	if(drawpolypit)												//PD 20Feb96
	{															//PD 20Feb96
		current_screen->DoForceRender();
		add_cockpit(*vp,UNMASKED,h,p,r);					//JIM 10Aug96
	}															//PD 20Feb96

	current_screen->End3DScene();

	OverLay.RenderInfoPanel();

	Add_PeripheralVision();

	View_Point->BlockTick(TRUE);
	if (Manual_Pilot.ControlledAC2 &&
		!Manual_Pilot.ControlledAC2->Status.deadtime)
	{
		if (Key_Tests.KeyPress3d(INFOPANEL))			OverLay.StepInfoBarUp();
		if (Key_Tests.KeyPress3d(TOGGLEMESSAGES))
		{
			if (Save_Data.gamedifficulty[GD_DISPLAYMESSAGES])
				Save_Data.gamedifficulty%=GD_DISPLAYMESSAGES;
			else
				Save_Data.gamedifficulty|=GD_DISPLAYMESSAGES;
		}
		if (Key_Tests.KeyPress3d(RADIOCOMMS))			OverLay.SetToRadioScreen();
		else if (Key_Tests.KeyPress3d(GROUPINFOMSG))	OverLay.HotKeyTriggerMenu(SEL_1);
		else if (Key_Tests.KeyPress3d(PRECOMBATMSG))	OverLay.HotKeyTriggerMenu(SEL_2);
		else if (Key_Tests.KeyPress3d(COMBATMSG))		OverLay.HotKeyTriggerMenu(SEL_3);
		else if (Key_Tests.KeyPress3d(POSTCOMBATMSG))	OverLay.HotKeyTriggerMenu(SEL_4);
		else if (Key_Tests.KeyPress3d(TOWERMSG))		OverLay.HotKeyTriggerMenu(SEL_5);
		else if (Key_Tests.KeyPress3d(FACMSG))			OverLay.HotKeyTriggerMenu(SEL_6);
		if (Key_Tests.KeyPress3d(ANYBANDITS))			OverLay.HotKeyTriggerMessage(SEL_3,SEL_3);
		if (Key_Tests.KeyPress3d(BREAK))				OverLay.HotKeyTriggerMessage(SEL_3,SEL_4);
		if (Key_Tests.KeyPress3d(CLEAR))				
		{
			if (Manual_Pilot.ControlledAC2->Leader()!=NULL)
			{
				OverLay.HotKeyTriggerMessage(SEL_3,SEL_6);
			}
			else
			{
				OverLay.HotKeyTriggerMessage(SEL_3,SEL_5);
			}
		}
	}
	OverLay.ProcessUIScreen();
	View_Point->BlockTick(FALSE);

	current_screen->EndScene();									//PD 11Jun97

	if (Save_Data.fSoftware) POLYGON.DoSoftwareFades();

	if (Land_Scape.incloudlayer)
	{
		Land_Scape.SetupGroundData(*View_Point,TRUE);
	}
	if (Save_Data.fSoftware)	current_screen->DoUnlockScr(&rsd);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	init_scene
//LastModified:	PD 20Dec95
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Tue 22 Aug 1995
//Modified	
//
//Description	Sets up variables/data required to render the world from a 
//			selected viewpoint.
//
//Inputs		viewpoint containing coordinate and angular info. required
//			to generate the view.	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void ThreeDee::init_scene(WorldStuff *worldptr, ViewPoint* viewpoint)//PD 22Apr96
{
//DEAD 	POLYGON.MakeAliasTable();									//PD 25Mar96
//DEAD 	POLYGON.MakeLumTable();										//RJS 19Jan98

	current_world = worldptr;

	viewer_x = viewpoint->World.X;
	viewer_y = viewpoint->World.Y;
	viewer_z = viewpoint->World.Z;

	generate_matrix(*viewpoint);									//PD 20Dec95

	bt->Clear3DArea();
//TempCode PD 04Feb99 	aircraft_tree->Clear3DArea();								//PD 28Oct98

	SHAPE.UpdateGlobalFlags(viewpoint->FrameTime());									//PD 08Mar96

	COORDS3D posn;
	GetSunPos(posn);
	Land_Scape.SetLVector(posn);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		add_cockpit
//LastModified:	PD 20Jun96
//Author		Paul.   
//Date			Fri 26 Jan 1996
//
//Description	Inserts polygon cockpit at current viewer position
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ThreeDee::add_cockpit(rotitem& viewpoint,PitTypes pittype,ANGLES h,ANGLES p,ANGLES r)	//PD 20Jun96
{
	Bool	bDoingHardware3D;

	bDoingHardware3D = current_screen->DoingHardware3D();

//DEAD	current_screen->LockBackScreen(TRUE,MIDLOCK);							//AMM 30Apr97

	rotitem	tempitem,
			*tempitemptr;

	ShapeNum shape;

	SLong	zoffset,yoffset;

	ClassPtr	clstyp;

	clstyp = Manual_Pilot.ControlledAC2->classtype;

	if (View_Point->viewnum.viewmode!=VM_InPadlock)
	{
		//Inside normal views

		zoffset =
			yoffset = 0;

		if (pittype==UNMASKED)
			shape = clstyp->cockpit1;
		else
			shape = clstyp->maskpit1;
	}
	else
	{
		//Inside looking forwards view

		zoffset = 0;
		yoffset = 0;

		if (pittype==UNMASKED)
			shape = clstyp->cockpit2;
		else
			shape = clstyp->maskpit2;
	}
	
	tempitemptr = &tempitem;

	bt->Clear3DArea();
//TempCode PD 04Feb99 	aircraft_tree->Clear3DArea();

	if (bDoingHardware3D)
		current_screen->DoSetPlayerTextures(TRUE);

	Obj3DPtr	obj3dptr;

	IFShare		wx,wy,wz;

	tempitem.shape = shape;

	tempitem.World.X = viewpoint.World.X;
	tempitem.World.Y = viewpoint.World.Y;
	tempitem.World.Z = viewpoint.World.Z;

	bt->SetHPRBuffet((Angles)buffetData.hdg,(Angles)buffetData.pitch,(Angles)buffetData.roll);

	tempitem.hdg=h;												//JIM 10Aug96
	tempitem.pitch=p;											//JIM 10Aug96
	tempitem.roll=r;												//JIM 10Aug96

	ANGLES	deltahdg,deltapitch,deltaroll;

	deltahdg = viewpoint.hdg + tempitem.hdg;
	deltapitch = viewpoint.pitch + tempitem.pitch;
	deltaroll = viewpoint.roll + tempitem.roll;

//DEAD 	if(POLYGON.UpdateYList(deltahdg,deltapitch,deltaroll) || pittype!=MASKED)
 	if(pittype!=MASKED)
	{
		animptr	adptr = Manual_Pilot.ControlledAC2->Anim;		//RJS 21Apr99
		PolyPitAnimData*	ppitanim = (PolyPitAnimData*) adptr;
		ULong	detailshift = ppitanim->detailmask;

//Removed music testing keypresses...										//RJS 15Apr99
/*		if (Key_Tests.KeyPress3d(DETAILDIALS))
		{
//			SHAPE.ForceDamage(Manual_Pilot.ControlledAC2,&((AircraftAnimData*)adptr)->RIGHTWINGIN,BS_DEAD);
//			SHAPE.ForceDamage(Manual_Pilot.ControlledAC2,&((AircraftAnimData*)adptr)->LEFTWINGIN,BS_DEAD);

			_Miles.SequenceAudible(MOOD_NEUTRAL);
		}

		if (Key_Tests.KeyPress3d(DETAILCANOPY))
		{
			detailshift >>= COCK3D_PANELGLASSFRONT;
			detailshift &= 1;

			if (!detailshift)
				ppitanim->detailmask |= (1 << COCK3D_PANELGLASSFRONT);//RJS 25Mar98
			else
				ppitanim->detailmask &= (0xFFFFFFFF - (1 << COCK3D_PANELGLASSFRONT));


//			_Miles.SequenceAudible(MOOD_HERO);


		}

		if (Key_Tests.KeyPress3d(DETAILPANEL))
		{

			_Miles.SequenceAudible(MOOD_TENSE);


		}

		if (Key_Tests.KeyPress3d(DETAILSIDES))
		{

			_Miles.SequenceAudible(MOOD_DESPERATE);


		}

		if (Key_Tests.KeyPress3d(DETAILSIGHT))
		{
			_Miles.SequenceAudible(FIL_MUSIC_SAD);


		}*/

		if (buffetData.delta.X==0 && 
			buffetData.delta.Y==0 &&
			buffetData.delta.Z==0)
		{
			wx.f=wy.f=wz.f=0.;
		}
		else
		{
			FPMATRIX bufMat;

//DEAD			wx.i = SLong(Float(buffetData.delta.X)*clstyp->cockscale);
//DEAD			wy.i = SLong(Float(buffetData.delta.Y)*clstyp->cockscale);
//DEAD			wz.i = SLong(Float(buffetData.delta.Z)*clstyp->cockscale);
			wx.i = buffetData.delta.X;
			wy.i = buffetData.delta.Y;
			wz.i = buffetData.delta.Z;

//Dead			_matrix.Generate2(tempitemptr->hdg,tempitemptr->pitch,tempitemptr->roll,1,&bufMat);
			_matrix.Generate2(tempitemptr->hdg,tempitemptr->pitch,tempitemptr->roll,clstyp->cockscale,&bufMat);
			_matrix.multiply(&bufMat,fpviewer_matrix);
			_matrix.transform(&bufMat,wx,wy,wz);
		}

//		UByteP	adptr = (UByteP )Manual_Pilot.ControlledAC2->Anim;//RJS 21Feb97

		if (resetpit)
		{
			resetpit = FALSE;
		}

		IFShare	bzoffset;
		bzoffset.f=0;

  		obj3dptr=(Obj3DPtr )bt->Get3DArea(STATIC_OBJECT);
  		SetObj3D(obj3dptr,tempitemptr,wx,wy,wz,bzoffset);
		obj3dptr->objtype=COCKPIT_OBJECT;

		obj3dptr->ItemPtr= Manual_Pilot.ControlledAC2;			//DAW 23Apr99
		obj3dptr->AnimPtr= adptr;								//RJS 21Feb97

		View_Point->BlockTick(TRUE);
		//Crap contrail fix put back!! //RJS 02Jul99
		Coords3D	horridhack = Manual_Pilot.ControlledAC2->World;//DAW 23Apr99
		Manual_Pilot.ControlledAC2->World = tempitemptr->World;	//DAW 23Apr99
		
		SHAPE.animate_shape(obj3dptr);							//RJS 26Jan98

		Manual_Pilot.ControlledAC2->World =	horridhack;			//DAW 23Apr99

		bt->insert_object2(obj3dptr);
		View_Point->BlockTick(FALSE);

		Bool oldState=current_screen->DoSetZUpdate(FALSE);
		bool oldState2=current_screen->DoSetMipMap(false);
		render_scene();
		current_screen->DoSetZUpdate(oldState);
		current_screen->DoSetMipMap(oldState2);

//DEAD  		if(pittype==MASKED)											//PD 20Jun96
//DEAD  			POLYGON.FillYList();
	}
	bt->Clear3DArea();
//TempCode PD 04Feb99 	aircraft_tree->Clear3DArea();								//PD 28Oct98

	tempitem.Anim=NULL;	//This stops the item delete code from freeing animation//PD 16Apr96
						//data that doesn't really belong to this item//PD 16Apr96

//DEAD 	current_screen->UnLockBackScreen(MIDLOCK);							//AMM 30Apr97
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Add_PeripheralVision
//Author		Paul.   
//Date			Tue 22 Jul 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ThreeDee::Add_PeripheralVision()
{
	#define	__MAX_VISIBLE_AC__	32
	SLong howMany=
	View_Point->BuildPeripheralVisionList(	current_screen,
											NULL,
											__MAX_VISIBLE_AC__);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Add_Sun
//Author		Paul.   
//Date			Mon 22 Apr 1996
//
//Description	Places sun based on delta in x,y given by earth's rotation.
//				Doesn't take into account axial tilt and sun goes overhead.
//				Are these the same problem? Modify dZ by season/latitude to fix? 
//				We only need to update the sun position about every 20 secs
//				as this gives 2000 updates /12 hours
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ThreeDee::Add_Sun(rotitem& viewpoint,WorldStuff *worldptr)
{
 	Coords3D	sunpos=viewpoint.World;
 	SLong		xdist, ydist, zdist;						//RJS 16Jul97
 	vector		SunPos;										//RJS 16Jul97
	SunAnimData*	adptr = (SunAnimData*) sunanimptr;		//RJS 02Jul98
 
 	sunpos.X += worldptr->sunpos.X;								//RJS 23Mar98
 	sunpos.Y += worldptr->sunpos.Y;								//RJS 23Mar98
 	sunpos.Z += worldptr->sunpos.Z;								//RJS 23Mar98
	//scale sun distance so that it is always drawn infront of
	//the horizon polygons...
	//Land_Scape.ScaleInsideHorizon(sunpos);
 
 	SunLightVector.ni.i = worldptr->sunpos.X;	//sunpos.X;
 	SunLightVector.nj.i = worldptr->sunpos.Y;	//sunpos.Y;
 	SunLightVector.nk.i = worldptr->sunpos.Z;	//sunpos.Z;
 
 	//This assumes the sun goes directly overhead
 
 	SHAPE.SunInVision = FALSE;								//PD 27Nov96
 
 	itemptr	sunitemp = new item;
  	sunitemp->shape=SUN;							//RJS 29Sep97
 	sunitemp->World = sunpos;						//RJS 29Sep97

 	//PD 27Nov96 - fix to stop sun not being drawn 'cos
 	//it's too far away
 	SLong	oldfaderange=Land_Scape.fade_band_end;		//PD 27Nov96
 	Land_Scape.fade_band_end=0x7FFFFFFF;				//PD 27Nov96

	// Sun starts to fade below 30degrees.
	SLong	horizfade = worldptr->sunrot;
	if (horizfade < 0)
		horizfade = -horizfade;

	if (horizfade < ANGLES_30Deg)
		horizfade = (255 * horizfade)/ANGLES_30Deg;
	else
		horizfade = 255;


	if (whichpal != PAL_NIGHT)
		adptr->itemstate = ALIVE;
	else
		adptr->itemstate = DEAD;

	adptr->fader = horizfade;

	sunitemp->Anim = sunanimptr;								//RJS 21Apr99

 	do_object_dummy(sunitemp,true);									//RJS 11Nov98
//DeadCode PD 28Apr99  	do_object_dummy(sunitemp);									//RJS 11Nov98

 	Land_Scape.fade_band_end=oldfaderange;				//PD 27Nov96

	sunitemp->Anim = NULL;

 	delete (sunitemp);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Add_Shadow
//Author		Robert Slater
//Date			Thu 24 Apr 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ThreeDee::Add_Shadow(AirStrucPtr	ac, Bool dopiloted)
{
	if (!Save_Data.detail_3d[DETAIL3D_AIRCRAFTSHADOWS])
		return;

	if (dopiloted || (ac != Manual_Pilot.ControlledAC2))		//RJS 13Jul98
	{
		//Fix for supermigs & pdeaths...
		if (ac->classtype->visible == ac->shape)				//RJS 24Jun99
		{
			MinAnimData*	mad = (MinAnimData*) ac->Anim;
			if (	(mad->itemstate != DEAD)					//RJS 01Sep99
				&&	!mad->IsInvisible			)				//RJS 01Sep99
			{
				rotitem*		shaditem;
				ANGLES			newhdg,newpitch,newroll;

				shaditem = new rotitem;
				if (shaditem)
				{
//DeadCode DAW 30Jun99  					shaditem->shape = ac->classtype->shadowshpno;
//DeadCode DAW 30Jun99 					shaditem->World = ac->World;
//DeadCode DAW 30Jun99 //#pragma warnmsg("Paul: timerFudgeFactor is garbage!")
//DeadCode DAW 30Jun99 ////TEMPCODE JIM 08/04/99 				shaditem->World.X += (View_Point->timerFudgeFactor * ac->velx)/100;//PD 19Sep97
//DeadCode DAW 30Jun99 ////TEMPCODE JIM 08/04/99 				shaditem->World.Z += (View_Point->timerFudgeFactor * ac->velz)/100;//PD 19Sep97
//DeadCode DAW 30Jun99 ////TEMPCODE JIM 08/04/99 
//DeadCode DAW 30Jun99 					newhdg = ac->hdg;
//DeadCode DAW 30Jun99 
//DeadCode DAW 30Jun99 					pMigLand->GetShadowAngles(shaditem->World,newhdg,newpitch,newroll);
//DeadCode DAW 30Jun99 
//DeadCode DAW 30Jun99 					shaditem->hdg = newhdg;
//DeadCode DAW 30Jun99 					shaditem->pitch = newpitch;
//DeadCode DAW 30Jun99 					shaditem->roll = newroll;
//DeadCode DAW 30Jun99 					shaditem->Anim = ac->Anim;
//DeadCode DAW 30Jun99 
//DeadCode DAW 30Jun99 					do_object_shad(shaditem,ac);
//DeadCode DAW 30Jun99 
//DeadCode DAW 30Jun99 					shaditem->Anim = NULL;
//DeadCode DAW 30Jun99 					delete (shaditem);
					Coords3D	shadpos=View_Point->World;
 
					shadpos.X += mobileitem::currworld->sunpos.X;								
 					shadpos.Y += mobileitem::currworld->sunpos.Y;
 					shadpos.Z += mobileitem::currworld->sunpos.Z;

 					shaditem->shape = ac->classtype->shadowshpno;

					SLong	glevel;
					if (ac->fly.pModel->GroundHeight)	//crap fix
						glevel = ac->fly.pModel->GroundHeight;
					else
						glevel = ac->World.Y - 200;		//crap fix

					SLong	heightsun = shadpos.Y - glevel;
					if (heightsun > 0)
					{
						SLong	heightac = ac->World.Y - glevel;
						SLong	ixpos,izpos;
						Float	xpos, zpos;
						Float	heightscale = Float(heightac);

						heightscale *= 0.2;
						heightscale /= Float(heightsun);

						ixpos = ac->World.X - shadpos.X;
						izpos = ac->World.Z - shadpos.Z;

						xpos = Float(ixpos);
						zpos = Float(izpos);

						xpos *= heightscale;
						zpos *= heightscale;

						ixpos = SLong(xpos);			
						izpos = SLong(zpos);			

						if (	((ixpos < 100000) && (ixpos > -100000))
							&&	((izpos < 100000) && (izpos > -100000))	)
						{
							shaditem->World.X = ac->World.X + ixpos;
							shaditem->World.Z = ac->World.Z + izpos;

							newhdg = ac->hdg;

							pMigLand->GetShadowAngles(shaditem->World,newhdg,newpitch,newroll);

							shaditem->World.Y += 10;
							shaditem->hdg = newhdg;
							shaditem->pitch = newpitch;
							shaditem->roll = newroll;
							shaditem->Anim = ac->Anim;

							do_object_shad(shaditem,ac);
						}
					}

					shaditem->Anim = NULL;
					delete (shaditem);
				}
			}
		}
	}															//RJS 13Jul98
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddLensObject
//Author		Robert Slater
//Date			Thu 15 Jan 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ThreeDee::AddLensObject(DoPointStruc	*dopointP, ShapeNum	shpno, int	frameno,int fader)
{
	if (!Save_Data.fSoftware)
	{
		Obj3DPtr	obj3dptr;										
		IFShare		wx,wy,wz;
		IFShare			bzoffset;
		ShapeDescPtr	sdptr;
		itemptr			tempitemptr = new item;
		int				thisscale = 4;
		FlareAnimData	*adptr;

		wx.f = dopointP->bodyx.f;
		wy.f = dopointP->bodyy.f;
		wz.f = dopointP->bodyz.f;

		tempitemptr->shape = shpno;
		tempitemptr->World = View_Point->World;
		tempitemptr->Anim = lensflareanim;				//RJS 25Feb00

//DeadCode DAW 25Feb00 		SHAPE.SetAnimData(tempitemptr,0);						

		sdptr = SHAPESTUFF.GetShapePtr(shpno);		
		switch(SHAPESTUFF.GetShapeScale(sdptr))					
		{														
			case SHP_1CM:										
				thisscale += 0;									
				break;											
																
			case SHP_4CM:										
				thisscale += 2;									
				break;											
																
			case SHP_16CM:										
				thisscale += 4;									
				break;											
		}														

		bzoffset.f = 5000;									

		obj3dptr = (Obj3DPtr )bt->Get3DArea(STATIC_OBJECT);
		SetObj3D(obj3dptr,tempitemptr,wx,wy,wz,bzoffset);

		obj3dptr->ItemPtr = NULL;										//RJS 11Nov98
		obj3dptr->AnimPtr = tempitemptr->Anim;								 //RJS 4/16/99//RJS 21Apr99
		adptr = (FlareAnimData*) obj3dptr->AnimPtr;
		adptr->colstep = frameno;
		adptr->depth = fader;

		bt->insert_object(obj3dptr);							

		tempitemptr->Anim = NULL;
		delete (tempitemptr);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddVapourObject
//Author		Robert Slater
//Date			Mon 8 Sep 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SLong ThreeDee::AddVapourObject(ShapeNum	shape,
								UByteP		apoint1,
								UByteP		prevobj3d,
								UByteP		&thisobj3d,
								UWord		failedcnt)
{
	SLong		distz;
	rotitem*	VapItemP = new rotitem;
	if (VapItemP)
	{
		SLong		wx, wy, wz;
		Coords3DList*	currpoint = (Coords3DList*) apoint1;	//RJS 21Apr99
		ULongP		lastobjptr = (ULongP) &VapItemP->hdg;			//RJS 17Sep97

		wx = currpoint->trailpoint.gx;								//RJS 17Sep97
		wy = currpoint->trailpoint.gy;								//RJS 17Sep97
		wz = currpoint->trailpoint.gz;								//RJS 17Sep97

		VapItemP->shape = shape;
 		VapItemP->World.X = wx;
 		VapItemP->World.Y = wy;
 		VapItemP->World.Z = wz;
		*lastobjptr = (ULong) prevobj3d;							//RJS 17Sep97
 		VapItemP->roll = ANGLES_0Deg;								//RJS 17Sep97
		VapItemP->Anim = apoint1;									//RJS 17Sep97
		VapItemP->Anim = (1<<MINANIM);				//RJS 21Apr99

		distz = do_object_vapour(VapItemP,thisobj3d,failedcnt);		//RJS 17Sep97

 		VapItemP->Anim = NULL;

		delete (VapItemP);
	}
	else
	{
		distz = 0;
		thisobj3d = NULL;
	}

	return(distz);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	render_scene
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Tue 22 Aug 1995
//Modified	
//
//Description	Draws objects in the order contained in the binary tree.
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void ThreeDee::render_scene()
{
//DEAD	current_screen->LockBackScreen(TRUE,MIDLOCK);							//AMM 30Apr97

//DEAD	POLYGON.SetPixelWidth(1);									//PD 20Feb96
	bt->draw_object(current_screen,View_Point);							//PD 20Dec95

	//temp waiting for a proper fix!
//TempCode PD 05Feb99 	bool fOldVal=current_screen->DoSetEdgeTest(true);

//TempCode PD 04Feb99 	aircraft_tree->nz_draw_object(current_screen,View_Point);		//PD 28Oct98

	//temp waiting for a proper fix!
//TempCode PD 05Feb99 	current_screen->DoSetEdgeTest(fOldVal);

//DEAD 	current_screen->UnLockBackScreen(MIDLOCK);							//AMM 30Apr97
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	exit_3D
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Tue 22 Aug 1995
//Modified	
//
//Description	Deallocate buffers and tidy up
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void ThreeDee::exit_3D()
{
	havematrix = false;				//RJS 10Dec98
	delete fpviewer_matrix;
	delete fpinverse_matrix;

	SLong	rfps = View_Point->RealFrameTime();			//RJS 28May99
	if (rfps)											//RJS 28May99
		Trans_Obj.realFrameTime = 100 / rfps;			//RJS 28May99
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	generate_matrix
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Tue 22 Aug 1995
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
void ThreeDee::generate_matrix(rotitem& viewpoint)
{

	fpviewer_matrix = new FPMATRIX;
	fpinverse_matrix = new FPMATRIX;

	viewer_hdg=viewpoint.hdg;
	viewer_pitch=viewpoint.pitch;
	viewer_roll=viewpoint.roll;

	_matrix.Generate(viewer_hdg,viewer_pitch,viewer_roll,fpviewer_matrix);
	_matrix.inverse(viewer_hdg,viewer_pitch,viewer_roll,fpinverse_matrix);

	_matrix.GenerateXY(SHAPE.SphereXScale,SHAPE.SphereYScale);	//RJS 02Dec98

	havematrix = true;			//RJS 10Dec98
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetDistance
//Author		Martin Alderton
//Date			Tue 14 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
ULong ThreeDee::GetDistance(Obj3DPtr thisobj3d)					//PD 13Mar96
{
	ULong dist;
	SLong dx,dy,dz;

	dx= viewer_x - thisobj3d->ItemPtr->World.X;
	dy= viewer_y - thisobj3d->ItemPtr->World.Y;
	dz= viewer_z - thisobj3d->ItemPtr->World.Z;

 	dist = Math_Lib.distance3d(dx,dy,dz);						//PD 29Nov95

	return(dist);

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		zClipLine
//Author		Martin Alderton
//Date			Mon 20 Nov 1995
//
//Description	takes in two dopointstrucs works out where (if anywhere) they
//				cross the zclipping planes and adjusts the bodyx and bodyy
//				coordinates of each point as required. Hey Presto a line
//				clipped in the z plane ready to go to ClipLine function
//
//Inputs		2* dopointstruc
//
//Returns		2 * adjusted DoPointStruc	
//
//------------------------------------------------------------------------------
Bool ThreeDee::zclipline(Bool draw,DoPointStruc /*start_vertex*/,DoPointStruc /*end_vertex*/)//PD 15Jan96
{
	return(draw);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		IntensFromRange
//Author		Paul.   
//Date			Tue 9 Jan 1996
//
//Description	Returns an intensity value in the range 0..255 based
//				on position within start and end ranges
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SWord ThreeDee::IntensFromRange(SLong& range,
								SLong& fade_band_start,
								SLong& fade_band_end)
{
	if (range<=fade_band_start)	return (0);

	if (range>=fade_band_end)	return (255);

	SLong	rangedelta,fadedelta;

	SWord	retval;

	fadedelta = range - fade_band_start;

	rangedelta = fade_band_end - fade_band_start;				//PD 18Dec96

	if (fadedelta<0x7FFFFF)
		retval = (fadedelta<<8)/rangedelta;
	else
		retval = (fadedelta/(rangedelta>>8));

	//Clip to max and min.

	if (retval<0)		retval=0x00;
	if (retval>0xFF)	retval=0xFF;

	return(retval);
}

inline SLong D3Distance(SLong a,SLong b,SLong c)
{
	SLong	max,med,min,temp;

	max = a<0?-a:a; med = b<0?-b:b; min = c<0?-c:c;

	if (max < med )
	{
		temp = max; max = med; med = temp;
	}

	if (max < min)
	{
		temp = max; max = min; min = max;
	}

	if (med < min)
	{
		temp = med; med = min; min = temp;
	}

	// Now max > med > min

	temp = med >> 2;	//	1/4 med

	med = temp;

	temp >>= 2;			//	1/16 med

	med += temp;

	temp >>= 1;			//	1/32 med

	med += temp;

	min	>>= 2;			//	1/4 min

	return max + med + min;
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	do_objects
//LastModified:	PD 14Jun96
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Tue 22 Aug 1995
//Modified	Simplified nesting...	//JIM 12Aug96
//
//Description	Scans the world area around the viewpoint and sorts objects
//			into a binary tree (same as old engine).
//			Ignores items in different world wrap				//JIM 12Aug96
//			Ignores piloted A/C if inside view					//JIM 12Aug96
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void ThreeDee::do_objects()
{
	Land_Scape.ResetItemLog(); /* for software landscape sorting */

	ShapeDescPtr	sdp;

	int		i,j;

	item 	tempitem,
			*tempitemptr,
			*previtmptr;

	UWord	sector_x,
			sector_y,
			current_sector_x,
			current_sector_y,
			this_sector;

	Bool	dopilotedshad = FALSE;
	Bool	isPiloted = FALSE;

	if (!View_Point->PolyPitEnabled() && (View_Point->viewnum.viewmode!=VM_InsideCheat && View_Point->viewnum.viewmode!=VM_Inside))
		dopilotedshad = TRUE;

	tempitem.World.X = viewer_x;
	tempitem.World.Y = viewer_y;
	tempitem.World.Z = viewer_z;

	tempitemptr = &tempitem;

	current_world->getsectornos(tempitemptr,sector_x,sector_y);
	ResetPosRec();

	//Draw a 3x3 grid of sectors around the viewer

	int	sectorcount = 12;

	// Ensure smoke trail points are all sampled once if paused....
	if (!IsPaused())														//RJS 16Apr98
		SHAPE.SamplePntTime = TRUE;											//RJS 16Apr98

	previtmptr=NULL;
	for(current_sector_x = sector_x-1;sectorcount;current_sector_x++)
	{
		//sc test&dec occurs 4 times per yloop of 3 times

		for(current_sector_y = sector_y-1;--sectorcount&3;current_sector_y++)
		{
			bool itemLogged=false;	/* for software landscape sort */

			this_sector =
				current_world->makeindex(current_sector_x,current_sector_y);

			tempitemptr =
				current_world->getfirstitem(this_sector);

			while (tempitemptr)
			{
				Bool  itemdisabled=FALSE;
		
				if (current_world->SameSector(tempitemptr,*View_Point) &&
					!itemdisabled)
				{
					sdp = SHAPESTUFF.GetShapePtr(tempitemptr->shape);

					SLong rangemax = sdp->MaxDrawRange;		//RJS 22Jan99
					SLong rng=D3Distance(	tempitemptr->World.X-View_Point->World.X,
											tempitemptr->World.Y-View_Point->World.Y,
											tempitemptr->World.Z-View_Point->World.Z);

					if (tempitemptr->Status.size==AirStrucSize)	//RJS 04Jun98
					{
						StoreAcPos(tempitemptr);
						rangemax = RANGE_AIRCRAFT_FLASH;		//RJS 04Jun98
						isPiloted = TRUE;									//RJS 08Sep98
						if (rng < RANGE_SHADOW)					//RJS 13Jul98
							Add_Shadow((AirStrucPtr)tempitemptr,dopilotedshad);//RJS 13Jul98

						if (	(tempitemptr != Persons2::PlayerGhostAC)	//RJS 07Sep98
							&&	(tempitemptr != Persons2::PlayerSeenAC)	)	//RJS 07Sep98
						{									
							isPiloted = FALSE;								//RJS 08Sep98
							if (rng < RANGE_FLYBYFAST)		
								DoFlyBySound((AirStrucPtr)tempitemptr,rng);

							if (radarOn && View_Point->PolyPitEnabled())//RJS 09Nov98
								SHAPE.GetRadarItem(tempitemptr,rng);//RJS 09Nov98
						}										//RJS 07Sep98
//						else
//						{
//							//If in flyby view...
//							//DoFlyBySound((AirStrucPtr)tempitemptr,rng);
//						}
					}
					else										//RJS 04Jun98
					{
						if (	groundlockOn									//RJS 10Jun99
							&&	(tempitemptr->Status.size != TRANSIENTSIZE)		//RJS 10Jun99
							&&	View_Point->PolyPitEnabled()	)				//RJS 10Jun99
							SHAPE.GetRadarItem(tempitemptr,rng);//RJS 04Jun99

						isPiloted = FALSE;
					}
																//RJS 04Jun98
					if (rng<=rangemax)							//RJS 04Jun98
					{
						SLong	oldfaderange=Land_Scape.fade_band_end;//PD 19Dec96

						if (rangemax==RANGE_AIRCRAFT_FLASH)		//RJS 04Jun98
							Land_Scape.fade_band_end=0x7FFFFFFF;//RJS 04Jun98

						/* for software landscape sorting */
						if (!itemLogged) 
							itemLogged=Land_Scape.LogItem(viewer_x,viewer_z,tempitemptr->World);

						switch(SHAPESTUFF.GetShapeScale(sdp))
						{
							case SHP_GRP:
 								do_object_grp(tempitemptr);
								break;

							case SHP_1CM:
							case SHP_4CM:
							case SHP_16CM:
								if (dopilotedshad)//RJS 02Sep98
								{
// dont delete these lines!!!! I use them often for testing
//									if (tempitemptr==Persons2::PlayerSeenAC)
//									{
//										do_object(Persons2::PlayerGhostAC);
//									}

									//if (!isPiloted)
										do_object(tempitemptr);
									/*else
									{
										ANGLES oldHdg,oldPitch,oldRoll;
										COORDS3D oldWorld;
										FPMATRIX tmat;
										IFShare tx,ty,tz;
										oldHdg=RotItemPtr(tempitemptr)->hdg;
										oldPitch=RotItemPtr(tempitemptr)->pitch;
										oldRoll=RotItemPtr(tempitemptr)->roll;
										RotItemPtr(tempitemptr)->hdg+=buffetData.hdg;
										RotItemPtr(tempitemptr)->pitch+=buffetData.pitch;
										RotItemPtr(tempitemptr)->roll+=buffetData.roll;
										_matrix.Generate2(	RotItemPtr(tempitemptr)->hdg,
															RotItemPtr(tempitemptr)->pitch,
															RotItemPtr(tempitemptr)->roll,
															1,&tmat);
										oldWorld=tempitemptr->World;
										tx.i=0;//buffetData.delta.X;
										ty.i=0;//buffetData.delta.Y;
										tz.i=0;//buffetData.delta.Z;
										_matrix.transform(&tmat,tx,ty,tz);
										tx.i=SLong(tx.f);
										ty.i=SLong(ty.f);
										tz.i=SLong(tz.f);
										tempitemptr->World.X+=tx.i;
										tempitemptr->World.Y+=ty.i;
										tempitemptr->World.Z+=tz.i;
										do_object(tempitemptr);
										tempitemptr->World=oldWorld;
										RotItemPtr(tempitemptr)->hdg=oldHdg;
										RotItemPtr(tempitemptr)->pitch=oldPitch;
										RotItemPtr(tempitemptr)->roll=oldRoll;
									} */
								}
								else if (isPiloted == FALSE)
									do_object(tempitemptr);
								break;
						}
						Land_Scape.fade_band_end=oldfaderange;	//PD 19Dec96

					}
				}
				previtmptr = tempitemptr;		//RJS 27Apr99
			 	tempitemptr = tempitemptr->Next;
			}
		}
	}

	// Lock smoke trail point sampling....
	if (IsPaused())															//RJS 16Apr98
		SHAPE.SamplePntTime = FALSE;										//RJS 16Apr98
	else
		SHAPE.SamplePntTime = TRUE;								//RJS 23Nov98
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		do_ui_objects
//Author		Paul.   
//Date			Fri 12 Mar 1999
//------------------------------------------------------------------------------
void ThreeDee::do_ui_objects()
{
	ShapeDescPtr	sdp;

	int		i,j;

	itemptr tempitemptr=(itemptr)current_world->pMapItemHead;

	while (tempitemptr)
	{
		SLong oldfaderange=Land_Scape.fade_band_end;

		sdp=SHAPESTUFF.GetShapePtr(tempitemptr->shape);

		switch(SHAPESTUFF.GetShapeScale(sdp))
		{
		case SHP_GRP:
			do_object_grp(tempitemptr);
			break;
		case SHP_1CM:
		case SHP_4CM:
		case SHP_16CM:
			do_object(tempitemptr);
			break;
		}
		Land_Scape.fade_band_end=oldfaderange;
	 	tempitemptr = tempitemptr->Next;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		do_object
//Author		Paul.   
//Date			Fri 8 Mar 1996
//
//Description	Transform and insert a simple shape
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ThreeDee::do_object(itemptr tempitemptr)
{
	if (tempitemptr->Anim==NULL)								//RJS 21Apr99
		SHAPE.SetAnimData(tempitemptr,0);						//RDH 23Sep96

	//New test to see if we want to draw or not...
	MinAnimData*	mad = (MinAnimData*)tempitemptr->Anim;
	if (!mad->IsInvisible)										//RJS 17Nov98
	{
		Obj3DPtr	obj3dptr;										//PD 13Mar96
		IFShare		wx,wy,wz;
		btree*		which_tree;
		bool		beenfixed = false;

//TempCode PD 04Feb99 		if (tempitemptr->Status.size==AirStrucSize)
//TempCode PD 04Feb99 			which_tree=aircraft_tree;
//TempCode PD 04Feb99 		else
			which_tree=bt;

//DeadCode DAW 23Apr99 		if (tempitemptr->Anim==NULL)							//RJS 21Apr99
//DeadCode DAW 23Apr99 			SHAPE.SetAnimData(tempitemptr,0);						//RDH 23Sep96
//DeadCode DAW 23Apr99 
//DeadCode DAW 23Apr99 		animptr	adptr=tempitemptr->Anim;			 //RJS 4/16/99

		IFShare			bzoffset;

		ShapeDescPtr	sdptr;

		if(tempitemptr->World.Y==0)
		{
			tempitemptr->World.Y = _Collide.AccurateGroundAltitude(tempitemptr->World);//PD 08Oct96
			beenfixed = true;
		}

		wx.i = tempitemptr->World.X - viewer_x;
		wy.i = tempitemptr->World.Y - viewer_y;
		wz.i = tempitemptr->World.Z - viewer_z;

		_matrix.transform(fpviewer_matrix,wx,wy,wz);
		if (tempitemptr->Status.size == TRANSIENTSIZE)			//RJS 27Nov98
		{
			UWord	offset = ((TransientItem*)tempitemptr)->DrawOffset;
			if (offset)
			{
				// scale the 3d coords so the object is drawn closer...
				Float	newz = wz.f - Float(offset);
				Float	dscale = newz / wz.f;

				wx.f *= dscale;
				wy.f *= dscale;
				wz.f = newz;
			}
		}

		sdptr = SHAPESTUFF.GetShapePtr(tempitemptr->shape);		//RJS 29May97
		int	shpsize = sdptr->Size<<4;								//RJS 20Aug98

		if(RoughCone(wx,wy,wz,shpsize) || (tempitemptr->shape == ROCKET))//RJS 09Jul98
		{															//RJS 09Jul98
 			if (!sdptr->Type.DrawPriority)							//RJS 09Jul98
				bzoffset.f = (Float)shpsize;						//RJS 09Jul98
 			else													//RJS 09Jul98
 				bzoffset.f = 12325.0;								//RJS 09Jul98

			obj3dptr = (Obj3DPtr )which_tree->Get3DArea(STATIC_OBJECT);
			SetObj3D(obj3dptr,tempitemptr,wx,wy,wz,bzoffset);

			obj3dptr->AnimPtr = tempitemptr->Anim;				//DAW 23Apr99

			which_tree->insert_object(obj3dptr);							//RJS 17Sep97

			SHAPE.animate_shape(obj3dptr);							//RJS 17Sep97

			tempitemptr->Status.Drawn = TRUE;//RJS 05Oct98

	#ifndef NDEBUG					
			if (supercheatitem && (beenfixed==true))			
				tempitemptr->World.Y = 0;
	#endif
		}															//RJS 10Nov98
		else
			SHAPE.dummy_animate_shape(tempitemptr,(UByteP)sdptr);//RJS 06Apr99

		SHAPE.sfx_shape(tempitemptr,wx,wy,wz);						//RJS 20Apr98
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		do_object_shad
//Author		Robert Slater
//Date			Thu 19 Jun 1997
//
//Description	Places a shadow in the binary tree.
//				This is essentially a simpler version of above,
//				and ensures that it is drawn first... (ie. bzoffset = 0)
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ThreeDee::do_object_shad(itemptr tempitemptr, itemptr	owner)
{
	Obj3DPtr	obj3dptr;										
	IFShare		wx,wy,wz;
	IFShare		bzoffset;

	bzoffset.f = 96;				// Only use small amount

//DeadCode RJS 21Apr99 	animptr	adptr=tempitemptr->Anim;							//RJS 21Apr99

	wx.i = tempitemptr->World.X - viewer_x;
	wy.i = tempitemptr->World.Y - viewer_y;
	wz.i = tempitemptr->World.Z - viewer_z;

	_matrix.transform(fpviewer_matrix,wx,wy,wz);

	if(RoughCone(wx,wy,wz,960))									//RJS 20Aug98
	{
		obj3dptr = (Obj3DPtr )bt->Get3DArea(STATIC_OBJECT);
		SetObj3D(obj3dptr,tempitemptr,wx,wy,wz,bzoffset);

		obj3dptr->ItemPtr = owner;								//RJS 11Nov98
		obj3dptr->objtype = SHADOW_OBJECT;
		obj3dptr->AnimPtr = tempitemptr->Anim;								//RJS 21Apr99

		bt->insert_object(obj3dptr);

		tempitemptr->Status.Drawn = TRUE;//RJS 05Oct98
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		do_object_vapour
//Author		Robert Slater
//Date			Mon 8 Sep 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SLong ThreeDee::do_object_vapour(rotitem* tempitemptr, UByteP&	thisobj, UWord failedyet)
{
	Obj3DPtr	obj3dptr;										
	IFShare		wx,wy,wz;
	IFShare		bzoffset;

	bzoffset.f = 96*4;											//RJS 17Sep97

//DeadCode RJS 21Apr99 	UByteP	adptr=(UByteP )tempitemptr->Anim;

	wx.i = tempitemptr->World.X - viewer_x;
	wy.i = tempitemptr->World.Y - viewer_y;
	wz.i = tempitemptr->World.Z - viewer_z;

	_matrix.transform(fpviewer_matrix,wx,wy,wz);

	if(RoughCone(wx,wy,wz,0) || !failedyet)					//RJS 20Aug98
	{
		obj3dptr = (Obj3DPtr )bt->Get3DArea(SMOKE_OBJECT);		//DAW 18Aug99
		if (obj3dptr)
		{
			SetObj3D(obj3dptr,tempitemptr,wx,wy,wz,bzoffset);

			obj3dptr->ItemPtr = NULL;								//RJS 11Nov98
			obj3dptr->objtype = SMOKE_OBJECT;
			obj3dptr->AnimPtr = tempitemptr->Anim;								//RJS 21Apr99

			bt->insert_object(obj3dptr);

			tempitemptr->Status.Drawn = TRUE;//RJS 05Oct98
		}

		thisobj = (UByteP) obj3dptr;
	}
	else
		thisobj = NULL;

	return(wz.f);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		do_object_grp
//LastModified:	PD 25Jul96
//Author		Paul.   
//Date			Fri 8 Mar 1996
//
//Description	Transform and insert a group of shapes
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ThreeDee::do_object_grp(itemptr tempitemptr)
{
	Obj3DPtr	obj3dptr;										//PD 13Mar96
	IFShare		wx,wy,wz;
	SLong		ex,ey,ez;
//DeadCode RJS 21Apr99   	UByteP		adptroff;										//RJS 11Oct96
	static		item	localitem;								//PD 25Jul96
	IFShare		bzoffset;
	UByte*		groupjump;										//RJS 18Oct96
	SWord		instruction;									//RJS 18Oct96
	DOGROUP_PTR 	tempgrp;									//RJS 18Oct96
	DRAWBETWEEN_PTR	dobetptr;									//RJS 18Oct96
	SWord		heading;										//RJS 14Aug97
	SByte		ydelta;											//RJS 20Nov97
	UByteP		adptrold;
	COORDS3D	tmpworld;
	SLong		heightfix;
	MinAnimData*	mad;										//RJS 16Nov98

	ShapeDescPtr	sdptr;
	
	ShapeNum	newshape,oldshape;

	if (tempitemptr->Anim==NULL)								//RJS 21Apr99
		SHAPE.SetAnimData(tempitemptr,0);						//RDH 23Sep96

	animptr	adptr=tempitemptr->Anim;							//RJS 21Apr99

//DeadCode RJS 21Apr99 	adptroff = adptr;											//RJS 11Oct96

	ShapeDescPtr	header_ptr =
		SHAPESTUFF.GetShapePtr(oldshape = tempitemptr->shape);

	UByte *instr_ptr = (UByte *)header_ptr + header_ptr->liveshpref;

	if(tempitemptr->World.Y == 0)
		tempitemptr->World.Y =	_Collide.AccurateGroundAltitude(tempitemptr->World);//PD 08Oct96

	wx.i = tempitemptr->World.X - viewer_x;						//PD 10Oct96
	wy.i = tempitemptr->World.Y - viewer_y;						//PD 10Oct96
	wz.i = tempitemptr->World.Z - viewer_z;						//PD 10Oct96

	_matrix.transform(fpviewer_matrix,wx,wy,wz);

	SLong	grouprange = (SLong)wz.f;
	Bool	notinrange;											//RJS 04Dec96
	SLong	shpsize;											//RJS 09Jul98
	Bool	isFiddled;

	groupjump = NULL;											//RJS 05Dec96

	forever	//while(TRUE)
	{
		instruction = *instr_ptr;
		instr_ptr++;

		if (instruction!=dogroupno)
			break;

		tempgrp = (DOGROUP_PTR)instr_ptr;

		newshape = (ShapeNum )tempgrp->shapenum;

		heading = tempgrp->angle;								//RJS 14Aug97

		tempitemptr->shape = newshape;

		tmpworld.X = tempitemptr->World.X + tempgrp->xoffset;
		tmpworld.Y = tempitemptr->World.Y + tempgrp->yoffset;
		tmpworld.Z = tempitemptr->World.Z + tempgrp->zoffset;

		SHAPE.SetGrpTokenVisibility((UByteP)tempgrp,tempitemptr->Anim,adptr);//RJS 21Apr99
		mad = (MinAnimData*) adptr;//rjs fucked

		//Eliminate cocked-up deltas
		ydelta = SHAPE.GetElementYDelta(newshape,adptr,tmpworld,tempitemptr->World.Y);//RJS 09Jun99

#ifndef NDEBUG					
		if (supercheatitem)			
			ydelta = -128;
#endif

		if (	(grouprange >= tempgrp->range_min)				//MS 27May98
			&&	(grouprange < tempgrp->range_max)	)			//MS 27May98
		{
			// Delta calc moved to 3dcom.cpp					//DAW 01Dec98
			heightfix = ydelta<<4;								//DAW 01Dec98

			if (!mad->IsInvisible)								//RJS 21Apr99
			{
				tmpworld.Y += heightfix;							//RJS 30Oct98

				localitem.World.X = wx.i = tmpworld.X;				//RJS 30Oct98
				localitem.World.Y = wy.i = tmpworld.Y;				//RJS 30Oct98
				localitem.World.Z = wz.i = tmpworld.Z;				//RJS 30Oct98

				wx.i -= viewer_x;
				wy.i -= viewer_y;											//PD 30Sep96
				wz.i -= viewer_z;

				_matrix.transform(fpviewer_matrix,wx,wy,wz);

				sdptr = SHAPESTUFF.GetShapePtr(newshape);			//RJS 17Nov98
				shpsize = sdptr->Size << 4;							//RJS 17Nov98
				if(RoughCone(wx,wy,wz,shpsize))						//RJS 09Jul98
				{
//DeadCode RJS 12Feb99 					bzoffset.f = tempgrp->bzoffset << 4;//Shit fix, this isn't entirely accurate...

					obj3dptr = (Obj3DPtr )bt->Get3DArea(STATIC_OBJECT);	//PD 13Mar96
					SetObj3D(obj3dptr,tempitemptr,wx,wy,wz,bzoffset);//PD 15Mar96

#ifndef NDEBUG													//RJS 13Aug97
					if (shapecheat)									//RJS 13Aug97
					{												//RJS 13Aug97
						obj3dptr->AngH = ANGLES_0Deg;				//RJS 13Aug97
						obj3dptr->AngC = ANGLES_0Deg;				//RJS 13Aug97
						obj3dptr->AngR = ANGLES_0Deg;				//RJS 13Aug97
					}												//RJS 13Aug97
#endif															//RJS 13Aug97

					if (heading)									//RJS 14Aug97
					{												//RJS 20Nov97
						obj3dptr->AngH = (Angles) heading;			//RJS 20Nov97
						obj3dptr->AngC = ANGLES_0Deg;				//RJS 13Aug97
						obj3dptr->AngR = ANGLES_0Deg;				//RJS 13Aug97
						obj3dptr->objtype = MOBILE_OBJECT;			//RJS 14Aug97
					}												//RJS 14Aug97

					//Make sure animdata inherits sizefield too	//RJS 21Apr99
					obj3dptr->AnimPtr = tempitemptr->Anim;		//RJS 21Apr99
					obj3dptr->AnimPtr = (UByteP)mad;				//RJS 20Nov97
					SHAPE.animate_shape(obj3dptr);					//RJS 25Jun97

					bt->insert_object(obj3dptr);					//RJS 29May97

					tempitemptr->Status.Drawn = TRUE;//RJS 05Oct98
				}
			}
		}

		instr_ptr += sizeof(DOGROUP);							//RJS 22Aug97
	}
	tempitemptr->shape = oldshape;

#ifndef NDEBUG					
		if (supercheatitem)			
			tempitemptr->World.Y = 0;
#endif
}




//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PaletteBlender
//Author		Robert Slater
//Date			Tue 22 Oct 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ThreeDee::PaletteBlender(SLong time)
{
//DeadCode RJS 15Jun99 	ImageMapNumber	imapno;
//DeadCode RJS 15Jun99 	ULong			red,green,blue;
//DeadCode RJS 15Jun99 	ULong			red2,green2,blue2;
//DeadCode RJS 15Jun99 	ULong			rtot,gtot,btot;
//DeadCode RJS 15Jun99 	RGBINFO_PTR		src,dest,paloffset;
//DeadCode RJS 15Jun99 	UByte			nextpal,bias1,bias2;
//DeadCode RJS 15Jun99 	SWord			count;
//DeadCode RJS 15Jun99 	SLong			timedif,palpos;
//DeadCode RJS 15Jun99 	SWord			bigcount;
//DeadCode RJS 15Jun99 	SLong			newtime_minutes;
//DeadCode RJS 15Jun99 
//DeadCode RJS 15Jun99 	paloffset = NewPalettePtr;									//RJS 24Feb98
//DeadCode RJS 15Jun99 
//DeadCode RJS 15Jun99 	time /= 100;							// To seconds
//DeadCode RJS 15Jun99 	newtime_minutes = time/60;									//RJS 23Apr98
//DeadCode RJS 15Jun99 	if (newtime_minutes != time_minutes)						//RJS 23Apr98
//DeadCode RJS 15Jun99 	{
//DeadCode RJS 15Jun99 		time_minutes = newtime_minutes;							//RJS 23Apr98
//DeadCode RJS 15Jun99 
//DeadCode RJS 15Jun99 		Land_Scape.SetLighting(time);
//DeadCode RJS 15Jun99 
//DeadCode RJS 15Jun99 		Bool	lightson = FALSE;
//DeadCode RJS 15Jun99 		Bool	timetochange = FALSE;							//RJS 30Oct96
//DeadCode RJS 15Jun99 		WorldStuff*	worldptr = mobileitem::currworld;			//RJS 23Mar98
//DeadCode RJS 15Jun99 
//DeadCode RJS 15Jun99 		if (oldtime > -2)
//DeadCode RJS 15Jun99 		{
//DeadCode RJS 15Jun99 			lightson = TRUE;									//RJS 23Mar98
//DeadCode RJS 15Jun99 
//DeadCode RJS 15Jun99 			timedif = time - Miss_Man.camp.dawntime;		
//DeadCode RJS 15Jun99 			if ((timedif >= -1800) && (timedif <= 1800))
//DeadCode RJS 15Jun99 			{
//DeadCode RJS 15Jun99 				palpos = 0;
//DeadCode RJS 15Jun99 
//DeadCode RJS 15Jun99 				if (timedif < 0)
//DeadCode RJS 15Jun99 				{
//DeadCode RJS 15Jun99 					whichpal = PAL_NIGHT;						//RJS 02Sep97
//DeadCode RJS 15Jun99 					palpos = 16;
//DeadCode RJS 15Jun99 				}
//DeadCode RJS 15Jun99 				else
//DeadCode RJS 15Jun99 					whichpal = PAL_DAWN;						//RJS 02Sep97
//DeadCode RJS 15Jun99 
//DeadCode RJS 15Jun99 				palpos += ((timedif<<4) / 1800);
//DeadCode RJS 15Jun99 
//DeadCode RJS 15Jun99 				if (palpos != whereinpal)
//DeadCode RJS 15Jun99 				{
//DeadCode RJS 15Jun99 					whereinpal = palpos;
//DeadCode RJS 15Jun99 					timetochange = TRUE;
//DeadCode RJS 15Jun99 					if ((whereinpal > 8) && (whichpal == PAL_DAWN))//RJS 01Sep97
//DeadCode RJS 15Jun99 					{
//DeadCode RJS 15Jun99 						lightson = FALSE;
//DeadCode RJS 15Jun99 					}
//DeadCode RJS 15Jun99 				}
//DeadCode RJS 15Jun99 			}
//DeadCode RJS 15Jun99 			else
//DeadCode RJS 15Jun99 			{
//DeadCode RJS 15Jun99 				lightson = FALSE;
//DeadCode RJS 15Jun99 
//DeadCode RJS 15Jun99 				timedif = time - Miss_Man.camp.dusktime;
//DeadCode RJS 15Jun99 				if ((timedif >= -1800) && (timedif <= 1800))
//DeadCode RJS 15Jun99 				{
//DeadCode RJS 15Jun99 					palpos = 0;
//DeadCode RJS 15Jun99 
//DeadCode RJS 15Jun99 					if (timedif < 0)
//DeadCode RJS 15Jun99 					{
//DeadCode RJS 15Jun99 						whichpal = PAL_DAY;						//RJS 02Sep97
//DeadCode RJS 15Jun99 						palpos = 16;
//DeadCode RJS 15Jun99 					}
//DeadCode RJS 15Jun99 					else
//DeadCode RJS 15Jun99 					{
//DeadCode RJS 15Jun99 						whichpal = PAL_DUSK;					//RJS 01Sep97
//DeadCode RJS 15Jun99 					}
//DeadCode RJS 15Jun99 
//DeadCode RJS 15Jun99 					palpos += ((timedif<<4) / 1800);
//DeadCode RJS 15Jun99 
//DeadCode RJS 15Jun99 					if (palpos != whereinpal)
//DeadCode RJS 15Jun99 					{
//DeadCode RJS 15Jun99 						whereinpal = palpos;
//DeadCode RJS 15Jun99 						if ((whereinpal > 7) && (whichpal == PAL_DUSK))//RJS 01Sep97
//DeadCode RJS 15Jun99 						{
//DeadCode RJS 15Jun99 							lightson = TRUE;
//DeadCode RJS 15Jun99 						}
//DeadCode RJS 15Jun99 
//DeadCode RJS 15Jun99 						timetochange = TRUE;
//DeadCode RJS 15Jun99 					}
//DeadCode RJS 15Jun99 				}
//DeadCode RJS 15Jun99 			}
//DeadCode RJS 15Jun99 
//DeadCode RJS 15Jun99 			if ((timetochange == FALSE) && (oldtime == -1))
//DeadCode RJS 15Jun99 			{
//DeadCode RJS 15Jun99 				SLong	daytimelow,daytimehigh;
//DeadCode RJS 15Jun99 
//DeadCode RJS 15Jun99 				daytimelow = Miss_Man.camp.dawntime + 1800;
//DeadCode RJS 15Jun99 				daytimehigh = Miss_Man.camp.dusktime - 1800;
//DeadCode RJS 15Jun99 				whereinpal = 0;
//DeadCode RJS 15Jun99 				timetochange = TRUE;
//DeadCode RJS 15Jun99 
//DeadCode RJS 15Jun99 				if ((time > daytimelow) && (time < daytimehigh))
//DeadCode RJS 15Jun99 				{
//DeadCode RJS 15Jun99 					whichpal = PAL_DAY;							//RJS 02Sep97
//DeadCode RJS 15Jun99 					lightson = FALSE;
//DeadCode RJS 15Jun99 				}
//DeadCode RJS 15Jun99 				else
//DeadCode RJS 15Jun99 				{
//DeadCode RJS 15Jun99 					whichpal = PAL_NIGHT;						//RJS 02Sep97
//DeadCode RJS 15Jun99 					lightson = TRUE;
//DeadCode RJS 15Jun99 				}
//DeadCode RJS 15Jun99 			}
//DeadCode RJS 15Jun99 
//DeadCode RJS 15Jun99 			oldtime = time_minutes;
//DeadCode RJS 15Jun99 		}
//DeadCode RJS 15Jun99 		else
//DeadCode RJS 15Jun99 		{
//DeadCode RJS 15Jun99 			timetochange = TRUE;
//DeadCode RJS 15Jun99 			whereinpal = 0;
//DeadCode RJS 15Jun99 			whichpal = PAL_DAY;									//RJS 02Sep97
//DeadCode RJS 15Jun99 			lightson = FALSE;
//DeadCode RJS 15Jun99 		}
//DeadCode RJS 15Jun99 
//DeadCode RJS 15Jun99 		if ((timetochange) && (oldtime != -3))					//RJS 13Nov96
//DeadCode RJS 15Jun99 		{
//DeadCode RJS 15Jun99 			Bool	boffweather = FALSE;
//DeadCode RJS 15Jun99 			ULong	redl,greenl,bluel;
//DeadCode RJS 15Jun99 
//DeadCode RJS 15Jun99 			if (newpalettes == NULL)							//RJS 24Feb98
//DeadCode RJS 15Jun99 			{													//RJS 24Feb98
//DeadCode RJS 15Jun99 				LandMapNum lmn=LandMapNum(FIL_PALCLUSTMAP_NUM);	//RJS 24Feb98
//DeadCode RJS 15Jun99 												  					//RJS 24Feb98
//DeadCode RJS 15Jun99 				newpalettes = lmn.GetLandMapPtr();				//RJS 24Feb98
//DeadCode RJS 15Jun99 				MasterPalettePtr = newpalettes->palette;		//RJS 24Feb98
//DeadCode RJS 15Jun99 			}													//RJS 24Feb98
//DeadCode RJS 15Jun99 
//DeadCode RJS 15Jun99 			if (whereinpal == 16)								//RJS 24Feb98
//DeadCode RJS 15Jun99 			{
//DeadCode RJS 15Jun99 				whereinpal = 0;
//DeadCode RJS 15Jun99 				whichpal++;
//DeadCode RJS 15Jun99 
//DeadCode RJS 15Jun99 				if (whichpal > PAL_DAWN)						//RJS 02Sep97
//DeadCode RJS 15Jun99 					whichpal = PAL_DAY;							//RJS 02Sep97
//DeadCode RJS 15Jun99 			}
//DeadCode RJS 15Jun99 
//DeadCode RJS 15Jun99 			nextpal = whichpal + 1;
//DeadCode RJS 15Jun99 			if (nextpal > PAL_DAWN)								//RJS 02Sep97
//DeadCode RJS 15Jun99 				nextpal = PAL_DAY;								//RJS 02Sep97
//DeadCode RJS 15Jun99 
//DeadCode RJS 15Jun99 			src = (RGBINFO_PTR) (MasterPalettePtr + (whichpal*768));//RJS 24Feb98
//DeadCode RJS 15Jun99 			dest = (RGBINFO_PTR) (MasterPalettePtr + (nextpal*768));//RJS 24Feb98
//DeadCode RJS 15Jun99 																	//RJS 24Feb98
//DeadCode RJS 15Jun99 			for (bigcount = 0; bigcount < 8; bigcount++)		//RJS 12Mar98
//DeadCode RJS 15Jun99 			{
//DeadCode RJS 15Jun99 				count = 0;											//RJS 24Feb98
//DeadCode RJS 15Jun99 				bias1 = 16 - whereinpal;
//DeadCode RJS 15Jun99 				bias2 = whereinpal;
//DeadCode RJS 15Jun99 
//DeadCode RJS 15Jun99 				redl = src[250].rval << 16;
//DeadCode RJS 15Jun99 				greenl = src[250].gval << 16;
//DeadCode RJS 15Jun99 				bluel = src[250].bval << 16;
//DeadCode RJS 15Jun99 
//DeadCode RJS 15Jun99 				while (count < 256)
//DeadCode RJS 15Jun99 				{
//DeadCode RJS 15Jun99 					red = src->rval << 16;
//DeadCode RJS 15Jun99 					green = src->gval << 16;
//DeadCode RJS 15Jun99 					blue = src->bval << 16;
//DeadCode RJS 15Jun99 
//DeadCode RJS 15Jun99 					red2 = dest->rval << 16;
//DeadCode RJS 15Jun99 					green2 = dest->gval << 16;
//DeadCode RJS 15Jun99 					blue2 = dest->bval << 16;
//DeadCode RJS 15Jun99 					if (count == 255)
//DeadCode RJS 15Jun99 					{
//DeadCode RJS 15Jun99 			 			if (lightson)
//DeadCode RJS 15Jun99 						{
//DeadCode RJS 15Jun99 							rtot = redl << 4;
//DeadCode RJS 15Jun99 							gtot = greenl << 4;
//DeadCode RJS 15Jun99 							btot = bluel << 4;
//DeadCode RJS 15Jun99 						}
//DeadCode RJS 15Jun99 						else
//DeadCode RJS 15Jun99 						{
//DeadCode RJS 15Jun99 							rtot = 0;
//DeadCode RJS 15Jun99 							gtot = 0;
//DeadCode RJS 15Jun99 							btot = 0;
//DeadCode RJS 15Jun99 						}
//DeadCode RJS 15Jun99 					}
//DeadCode RJS 15Jun99 					else
//DeadCode RJS 15Jun99 					{
//DeadCode RJS 15Jun99 						rtot = (red * bias1) + (red2 * bias2);
//DeadCode RJS 15Jun99 						gtot = (green * bias1) + (green2 * bias2);
//DeadCode RJS 15Jun99 						btot = (blue * bias1) + (blue2 * bias2);
//DeadCode RJS 15Jun99 					}
//DeadCode RJS 15Jun99 
//DeadCode RJS 15Jun99 					rtot >>= 20;
//DeadCode RJS 15Jun99 					gtot >>= 20;
//DeadCode RJS 15Jun99 					btot >>= 20;
//DeadCode RJS 15Jun99 
//DeadCode RJS 15Jun99 					paloffset->rval = gtot;									//RJS 25Feb98
//DeadCode RJS 15Jun99 					paloffset->gval = btot;
//DeadCode RJS 15Jun99 					paloffset->bval = rtot;
//DeadCode RJS 15Jun99 
//DeadCode RJS 15Jun99 					src++;
//DeadCode RJS 15Jun99 					dest++;
//DeadCode RJS 15Jun99 					paloffset++;
//DeadCode RJS 15Jun99 					count++;
//DeadCode RJS 15Jun99 				}
//DeadCode RJS 15Jun99 
//DeadCode RJS 15Jun99 				// Next palette...
//DeadCode RJS 15Jun99 				src += 768;
//DeadCode RJS 15Jun99 				dest += 768;
//DeadCode RJS 15Jun99 			}
//DeadCode RJS 15Jun99 
//DeadCode RJS 15Jun99 			current_screen->RegisterPalette((UByteP)NewPalettePtr,(256*3*8)+1);
//DeadCode RJS 15Jun99 			current_screen->UseNewPal=TRUE;
//DeadCode RJS 15Jun99 
//DeadCode RJS 15Jun99 			if (oldtime == -2)
//DeadCode RJS 15Jun99 				oldtime = -3;									//RJS 13Nov96
//DeadCode RJS 15Jun99 		}
//DeadCode RJS 15Jun99 	}

	SLong			newtime_minutes;

	time /= 100;						
	newtime_minutes = time/60;			
	if (newtime_minutes != time_minutes)
	{
		time_minutes = newtime_minutes;	

		lightson = Land_Scape.SetLighting(time);

		if (newpalettes == NULL)							
		{													
			LandMapNum lmn=LandMapNum(FIL_PALCLUSTMAP_NUM);	
											  				
			newpalettes = lmn.GetLandMapPtr();
			if (newpalettes)
			{
				ImageMapNumber	imapno;
				RGBINFO_PTR		src,paloffset;
				SWord			count;

				MasterPalettePtr = newpalettes->palette;

				//Use daytime palette!
				src = (RGBINFO_PTR) MasterPalettePtr;
				paloffset = NewPalettePtr;			

				int	bigcount;														
				for (bigcount = 0; bigcount < 8; bigcount++)
				{
					count = 0;											
					while (count < 256)
					{
						paloffset->rval = src->gval;							
						paloffset->gval = src->bval;
						paloffset->bval = src->rval;

						src++;
						paloffset++;
						count++;
					}

					// Next palette...
					src += 768;
				}

				current_screen->RegisterPalette((UByteP)NewPalettePtr,(256*3*8)+1);
 				current_screen->UseNewPal=TRUE;
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ResetPalette
//Author		Robert Slater
//Date			Thu 24 Oct 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ThreeDee::ResetPalette(Bool	forceday)
{
	if (forceday)
		oldtime = -2;
	else
		oldtime = -1;

	whereinpal = -1;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ResetCompass
//Author		Robert Slater
//Date			Thu 21 Nov 1996
//
//Description	Sets the old compass heading to the new one instantaneously
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ThreeDee::ResetCompass()
{
	resetpit = TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CalcLightsOn
//Author		Robert Slater
//Date			Mon 16 Dec 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ThreeDee::CalcLightsOn(SLong	time)
{
	SLong			timedif,palpos;
	Bool			timetochange;

	time /= 100;							// To seconds
	lightson = TRUE;

	timedif = time - Miss_Man.camp.dawntime;		
	if ((timedif >= -1800) && (timedif <= 1800))
	{
		palpos = 0;

		if (timedif < 0)
		{
			whichpal = PAL_NIGHT;								//RJS 02Sep97
			palpos = 16;
		}
		else
			whichpal = PAL_DAWN;								//RJS 02Sep97

		palpos += ((timedif<<4) / 1800);

		if (palpos != whereinpal)
		{
			whereinpal = palpos;
			timetochange = TRUE;
			if ((whereinpal > 8) && (whichpal == PAL_DAWN))		//RJS 02Sep97
				lightson = FALSE;
		}
	}
	else
	{
		lightson = FALSE;

		timedif = time - Miss_Man.camp.dusktime;
		if ((timedif >= -1800) && (timedif <= 1800))
		{
			palpos = 0;

			if (timedif < 0)
			{
				whichpal = PAL_DAY;								//RJS 02Sep97
				palpos = 16;
			}
			else
				whichpal = PAL_DUSK;							//RJS 02Sep97

			palpos += ((timedif<<4) / 1800);

			if (palpos != whereinpal)
			{
				whereinpal = palpos;
				if ((whereinpal > 7) && (whichpal == PAL_DUSK))	//RJS 02Sep97
					lightson = TRUE;

				timetochange = TRUE;
			}
		}
	}

	if (!timetochange)
	{
		SLong	daytimelow,daytimehigh;

		daytimelow = Miss_Man.camp.dawntime + 1800;
		daytimehigh = Miss_Man.camp.dusktime - 1800;
		whereinpal = 0;
		timetochange = TRUE;

		if ((time > daytimelow) && (time < daytimehigh))
		{
			whichpal = PAL_DAY;									//RJS 02Sep97
			lightson = FALSE;
		}
		else
		{
			whichpal = PAL_NIGHT;								//RJS 02Sep97
			lightson = TRUE;
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitialiseCache
//Author		Paul.   
//Date			Mon 19 Jan 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ThreeDee::InitialiseCache()
{
//	PaletteBlender(0);
	if (pMigLand==NULL) pMigLand=new CMigLand(/*NULL*/);
	if (pTMake==NULL) pTMake=new TMake;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DeleteCache
//Author		Paul.   
//Date			Mon 19 Jan 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ThreeDee::DeleteCache()
{
	if (pMigLand!=NULL)	delete pMigLand,pMigLand=NULL;
	if (pTMake)
	{
		pTMake->Exit();
		delete pTMake;
		pTMake=NULL;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RezChanged
//Author		Paul.   
//Date			Mon 19 Jan 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ThreeDee::RezChanged(ScreenRez&)
{
	assert(false&&" threedee::rezchanged");
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		IsPaused
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
Bool	ThreeDee::IsPaused()
{
 	if (current_display)
		if (current_display->FrameTime())
			return(FALSE);
		else
			return(TRUE);
	else
			return(TRUE);	//This is really an error!!!
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ConstructNormalData
//Author		Paul.   
//Date			Tue 18 Aug 1998
//Description	Generates a table of normals used to build a lookup table
//				to light shade the landscape
//------------------------------------------------------------------------------
void ThreeDee::ConstructNormalData()
{
	NormalData* pNormal=normalDataPtr;
	double PI;

	_asm
	{
	fldpi;
	fstp PI; 
	}

	int x,y;

	double TOP=(3.5/360)*2*PI;
	const double STEP=(6.2/360)*2*PI;
	const int headingbands[15]={1,7,13,19,25,30,35,40,44,20,12,10,10,10,10};
	int pitchindex=0;
	double pitch,heading,nextheading,nextpitch,headingstep;
	int currentpoint=1; // 0 is reserved for the horizontal plane
	
	// first fill the flat area...

	pNormal->i=pNormal->k=0;
	pNormal->j=1;
	pNormal++;

	for (pitch=TOP,nextpitch=TOP;pitch<PI/2;pitch=nextpitch)
	{
		nextpitch+=STEP;
		pitchindex++;
		headingstep=(2*PI)/headingbands[pitchindex];
		if (pitchindex>10) nextpitch+=STEP;
		if (pitchindex>11) nextpitch+=STEP;
		for (heading=0,nextheading=0;heading<(2*PI)-0.01;heading=nextheading)
		{
			NormalData norm;
			nextheading+=headingstep;

			double 	ave_heading,ave_pitch;
			double 	sin_pitch,cos_pitch,
					sin_heading,cos_heading;

			ave_pitch=(pitch+nextpitch)/2;
			ave_heading=(heading+nextheading)/2;

			_asm
			{
			fld ave_pitch;
			fsincos;
			fstp cos_pitch;
			fstp sin_pitch;
			fld ave_heading;
			fsincos;
			fstp cos_heading;
			fstp sin_heading;
			}

			norm.j=cos_pitch;
			norm.i=-sin_pitch*cos_heading;
			norm.k=-sin_pitch*sin_heading;

			if (currentpoint<256)
			{
				currentpoint++;

				double mag=norm.i*norm.i+norm.j*norm.j+norm.k*norm.k;
				_asm
				{
				fld mag;
				fsqrt;
				fstp mag;
				}
				norm.i/=mag;
				norm.j/=mag;
				norm.k/=mag;
				*pNormal++=norm;
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetSunPos
//Author		Paul.   
//Date			Tue 21 Jul 1998
//------------------------------------------------------------------------------
inline void ThreeDee::GetSunPos(COORDS3D& pos)
{
	current_world->MakeSunPos(View_Point);
	pos=current_world->sunpos;

	//re-make the landscape normal lookup table if the sun position
	//has changed
	if (lastSunPos.X!=pos.X||lastSunPos.Y!=pos.Y||lastSunPos.Z!=pos.Z)
	{
		lastSunPos.X=pos.X;
		lastSunPos.Y=pos.Y;
		lastSunPos.Z=pos.Z;

		double 	li=double(pos.X),
				lj=double(pos.Y>>1),
				lk=double(pos.Z),
				mag=li*li+lj*lj+lk*lk;

		_asm {	fld mag; 
				fsqrt; 
				fstp mag; 
			}

		li/=mag;
		lj/=mag;
		lk/=mag;

		NormalData* pNormal=normalDataPtr;
		UByte*		pnlu=pNormalLookup;

		//add scaling so that level ground always gets
		//full intensity regardless of the sun position

		const double darkest_value=.3;	//min=0, max=1
		const double level_i=pNormal->i*li+pNormal->j*lj+pNormal->k*lk;
		const double min_i=0.;
		const double add_factor=255*darkest_value;
		const double mul_factor=255-add_factor;
		const SLong low_clip=SLong(add_factor);

		for (SLong i=0;i<256;i++)
		{
			//take dot product of sun light vector and landscape vector

			NormalData& n=*pNormal;

			double dot=li*n.i+lj*n.j+lk*n.k;

			if (dot<min_i)			dot=min_i;
			else if (dot>level_i)	dot=level_i;

			//dot is in the range min_i<=dot<=level_i
			//convert to the range add_factor<=dot<=255

			dot-=min_i;
			dot/=(level_i-min_i);
			dot=add_factor+mul_factor*dot;

			SLong dotVal=SLong(dot);

			if (dotVal>255)				dotVal=255;
			else if (dotVal<low_clip)	dotVal=low_clip;

			*pnlu++=UByte(dotVal);

			pNormal++;
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetLandType
//Author		Robert Slater
//Date			Mon 24 Aug 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SLong	ThreeDee::GetLandType()
{
	return(pMigLand->GetAreaType());
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoFlyBySound
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
void	ThreeDee::DoFlyBySound(AirStrucPtr	ac,SLong	distance)
{
	if (!IsPaused())
	{
//DeadCode RJS 10May99 		SLong	ann,bnn,cnn;
//DeadCode RJS 10May99 		SLong	dvx,dvy,dvz;
//DeadCode RJS 10May99 		SLong	magVelAC;//RJS 06Oct98
//DeadCode RJS 10May99 
//DeadCode RJS 10May99 		ann = ac->velx;
//DeadCode RJS 10May99 		bnn = ac->vely;
//DeadCode RJS 10May99 		cnn = ac->velz;
//DeadCode RJS 10May99 		magVelAC = (ann*ann) + (bnn*bnn) + (cnn*cnn);
		if (ac->vel && !ac->Status.deadtime)		//Other AC must not be at standstill
		{
			SLong	dvx,dvy,dvz;
			SLong	eyevx, eyevy, eyevz, eyevel;
			bool	isyou = false;		//are we in flyby view?

			if (isyou)
			{
				eyevx = 0;
				eyevy = 0;
				eyevz = 0;
				eyevel = 0;
			}
			else
			{
				eyevx = Manual_Pilot.ControlledAC2->velx;
				eyevy = Manual_Pilot.ControlledAC2->vely;
				eyevz = Manual_Pilot.ControlledAC2->velz;
				eyevel = Manual_Pilot.ControlledAC2->vel;
			}


			dvx = eyevx - ac->velx;
			dvy = eyevy - ac->vely;
			dvz = eyevz - ac->velz;

			ULong magVelTot = Math_Lib.distance3d(dvx,dvy,dvz);
			if (magVelTot > 1500)
			{
				ULong	timetoreach = distance / magVelTot;
				if (timetoreach < 65)				//6.5 secs
				{
					ULong	maxVel = eyevel + ac->vel;
					magVelTot = (magVelTot << 16)/maxVel;
					if (eyevel)
					{
						SLong	vxa,vya,vza;
						SLong	vxb,vyb,vzb;
						SLong	intensity;

						vxa = (eyevx << 8)/eyevel;
						vya = (eyevy << 8)/eyevel;
						vza = (eyevz << 8)/eyevel;

						vxb = (ac->velx << 8)/ac->vel;
						vyb = (ac->vely << 8)/ac->vel;
						vzb = (ac->velz << 8)/ac->vel;
						
						intensity = -((vxa*vxb)+(vya*vyb)+(vza*vzb));

						magVelTot *= intensity;
						magVelTot >>= 16;

						if ((intensity > 60000) && (distance < 2000))			//RJS 24May99
						{
							if (ac->nationality != Manual_Pilot.ControlledAC2->nationality)
							{
								AirStrucPtr	buddy = Manual_Pilot.ControlledAC2->FindBuddy();

								_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_HEADON,MSG_BOGEYCALL,buddy,ac,Manual_Pilot.ControlledAC2));
							}
						}
					}

					if (magVelTot > 24000)
					{
						if (ac->fly.pModel->EngineList->Type == ET_PISTON)
						{
							if (timetoreach < 20)
								_Miles.PlayDelayed(FIL_SFX_P51_FLYBY_FAST,ac,128,FALSE,FIL_SFX_JET_FLYBY_FAST,FIL_SFX_P51_FLYAWAY);//PD 13Aug99
							else
								_Miles.PlayDelayed(FIL_SFX_P51_FLYBY_SLOW,ac,128,FALSE,FIL_SFX_JET_FLYBY_FAST,FIL_SFX_P51_FLYAWAY);//PD 13Aug99
						}
						else
						{
							if (timetoreach < 20)
								_Miles.PlayDelayed(FIL_SFX_JET_FLYBY_FAST,ac,128,FALSE,FIL_SFX_JET_FLYBY_FAST,FIL_SFX_P51_FLYAWAY);//PD 13Aug99
							else
								_Miles.PlayDelayed(FIL_SFX_JET_FLYBY_SLOW,ac,128,FALSE,FIL_SFX_JET_FLYBY_FAST,FIL_SFX_P51_FLYAWAY);//PD 13Aug99
						}
					}
				}
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		add_map
//Author		Robert Slater
//Date			Tue 8 Sep 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ThreeDee::add_map(rotitem& viewpoint,Bool	isZoomed)
{
	Bool	bDoingHardware3D = current_screen->DoingHardware3D();

//	current_screen->LockBackScreen(TRUE,MIDLOCK);					

	item	tempitem,
			*tempitemptr;

	ShapeNum shape;

	SLong	zoffset,yoffset;

	zoffset = yoffset = 0;

	tempitemptr = &tempitem;

	if (bDoingHardware3D)
		current_screen->DoSetPlayerTextures(TRUE);				

	Obj3DPtr	obj3dptr;										
	IFShare		wx,wy,wz;
	IFShare		bzoffset;

	ShapeDescPtr	sdptr;
	
	tempitem.World.X = viewpoint.World.X;
	tempitem.World.Y = viewpoint.World.Y;
	tempitem.World.Z = viewpoint.World.Z;
	tempitemptr->Anim = Manual_Pilot.ControlledAC2->Anim;

//TempCode PD 07Apr99  	if (isZoomed == FALSE)
//TempCode PD 07Apr99   	{
//TempCode PD 07Apr99  		sdptr = SHAPESTUFF.GetShapePtr(MAPZ);
//TempCode PD 07Apr99  		SLong	properdistz = (sdptr->sx << 4)*4;
//TempCode PD 07Apr99  		SLong	minzoom = properdistz >> 2;
//TempCode PD 07Apr99  
//TempCode PD 07Apr99  		tempitem.shape = MAP;
//TempCode PD 07Apr99  
//TempCode PD 07Apr99  		if (Key_Tests.KeyPress3d(ZOOMIN) || Key_Tests.KeyHeld3d(ZOOMIN))
//TempCode PD 07Apr99  		{
//TempCode PD 07Apr99  			if (mapdistz < properdistz)
//TempCode PD 07Apr99  			{
//TempCode PD 07Apr99  				mapdistz = properdistz;
//TempCode PD 07Apr99  				mapoffx = mapoffy = 0;
//TempCode PD 07Apr99  			}
//TempCode PD 07Apr99  		}
//TempCode PD 07Apr99  
//TempCode PD 07Apr99  		if (Key_Tests.KeyPress3d(ZOOMOUT) || Key_Tests.KeyHeld3d(ZOOMOUT))
//TempCode PD 07Apr99  		{
//TempCode PD 07Apr99  			if (mapdistz > (minzoom+16))
//TempCode PD 07Apr99  				mapdistz -= 16;
//TempCode PD 07Apr99  		}
//TempCode PD 07Apr99  
//TempCode PD 07Apr99  		SLong	zoomoffset = (properdistz - mapdistz)>>1;
//TempCode PD 07Apr99  		SLong	yoffset;
//TempCode PD 07Apr99  		SLong	distgap = properdistz - minzoom;
//TempCode PD 07Apr99  
//TempCode PD 07Apr99  		wx.f = mapoffx + zoomoffset;								
//TempCode PD 07Apr99  		wy.f = mapoffy;													
//TempCode PD 07Apr99  		wz.f = mapdistz;										
//TempCode PD 07Apr99  
//TempCode PD 07Apr99  		obj3dptr = (Obj3DPtr )bt->Get3DArea(STATIC_OBJECT);
//TempCode PD 07Apr99  
//TempCode PD 07Apr99  		bzoffset.f=0;
//TempCode PD 07Apr99  		tempitemptr->Anim = Manual_Pilot.ControlledAC2->Anim;
//TempCode PD 07Apr99  
//TempCode PD 07Apr99  		SetObj3D(obj3dptr,tempitemptr,wx,wy,wz,bzoffset);
//TempCode PD 07Apr99  
//TempCode PD 07Apr99  		obj3dptr->objtype = STATIC_OBJECT;
//TempCode PD 07Apr99  		obj3dptr->AnimPtr= (UByteP) Manual_Pilot.ControlledAC2->Anim;								
//TempCode PD 07Apr99  
//TempCode PD 07Apr99  		bt->insert_object2(obj3dptr);
//TempCode PD 07Apr99  	}

	sdptr = SHAPESTUFF.GetShapePtr(MAPZ);

	tempitem.shape = MAPZ;

	wx.f = 0;											
	wy.f = 0;														
	wz.f = 20<<4;	//(sdptr->sx << 4);											

	obj3dptr = (Obj3DPtr )bt->Get3DArea(STATIC_OBJECT);

	bzoffset.f=0;

	SetObj3D(obj3dptr,tempitemptr,wx,wy,wz,bzoffset);

	obj3dptr->objtype = STATIC_OBJECT;
	obj3dptr->AnimPtr= Manual_Pilot.ControlledAC2->Anim;								//RJS 21Apr99

	bt->insert_object2(obj3dptr);

	tempitem.Anim=NULL;	
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		render
//Author		Robert Slater
//Date			Tue 8 Sep 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ThreeDee::render(Window *screen, ViewPoint* vp,WorldStuff *world)//PD 22Apr96
{
//DeadCode AMM 14Apr99 	SHAPE.safeTrail = FALSE;
	if (vp->drawSpecialFlags)
	{
		if (vp->drawSpecialFlags & VIEW_SPECIAL_REPLAY)
			renderreplay(screen,vp,world);
		else
		{
			if (OverLay.fZoomedMap)		renderzoomedmap(screen,vp,world);
			else						rendermap(screen,vp,world);
		}
	}
	else
		render3d(screen,vp,world);

	exit_3D();

static SWord curTime=0;
	curTime-=(SWord)View_Point->FrameTime();
	if (curTime<0)
	{
		curTime=8;
		screen->DoCaptureScreen();
	}

//Dead	SHAPE.GenerateProbeTrails();								//AMM 26Mar99
//Dead	SHAPE.KillVapourStreamDeadList();							//RJS 11Nov98
//DeadCode AMM 14Apr99 	SHAPE.safeTrail = TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		rendermap
//Author		Robert Slater
//Date			Tue 8 Sep 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ThreeDee::rendermap(Window *screen, ViewPoint* vp,WorldStuff *world)//PD 22Apr96
{
	ANGLES	oldfov = Save_Data.fieldOfView;
	Save_Data.fieldOfView = ANGLES_90Deg;

	// Similar to add cockpit... just render 1 shape in the world
	// Blobs represent shapes (ac and target?)
	// A shape without 3d transforms .. a MAP_OBJECT

	current_screen=screen;
	View_Point=vp;
	SHAPE.SetView(vp,screen);
	current_screen->DoSetFade(RED,0,TDE_INSIDE2OUT);

	current_screen->DoSetViewParams(Save_Data.fieldOfView,screen,vp);//DAW 23Oct98
	_matrix.SetViewParams(current_screen,Save_Data.fieldOfView,0x7FFFFFFF);
	current_screen->BeginScene();									//PD 17Feb97

	fnum++;

	View_Point->BlockTick(TRUE);
	View_Point->SelectView();									//PD 19Feb96

	_matrix.SetZScale(current_screen);							
//DEAD	POLYGON.setpolyscrn(screen,,Save_Data.fieldOfView);

//DEAD	POLYGON.SetCrossProduct(TRUE);

	OverLay.SetViewpoint(View_Point);
	OverLay.SetScreen(current_screen);

	init_scene(world, vp);

	PaletteBlender((Miss_Man.camp.dawntime + 2000)*100);						//daytime?

	View_Point->BlockTick(FALSE);
//DEAD	current_screen->LockBackScreen(TRUE,MIDLOCK);							//AMM 30Apr97

	Land_Scape.RenderLandscape(	screen,View_Point,							
								fpviewer_matrix,					
								viewer_x,viewer_y,viewer_z,		
								vp->hdg);

	current_screen->DoFlushLandDraw();
//DEAD 	current_screen->UnLockBackScreen(MIDLOCK);							//AMM 30Apr97

	// Shove everything into binary tree and render...
//DEAD	current_screen->LockBackScreen(TRUE,MIDLOCK);					
	Bool oldState=current_screen->DoSetZUpdate(FALSE);
	bool oldState2=current_screen->DoSetMipMap(false);
	SWord oldTQ=screen->DoForceTQ(4);
	add_map(*vp);
//DeadCode PD 02Mar99 	do_objects_map(FALSE);
	render_scene();
	screen->DoForceTQ(oldTQ);
	current_screen->DoSetZUpdate(oldState);
	current_screen->DoSetMipMap(oldState2);
	bt->Clear3DArea();
//DEAD 	current_screen->UnLockBackScreen(MIDLOCK);
	// ...shoved everything into binary tree and rendered

	current_screen->End3DScene();

	View_Point->BlockTick(TRUE);
	OverLay.ProcessUIScreen();
	View_Point->BlockTick(FALSE);

	current_screen->EndScene();	
	Save_Data.fieldOfView = oldfov;//RJS 09Nov98
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		renderzoomedmap
//Author		Robert Slater
//Date			Tue 8 Sep 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ThreeDee::renderzoomedmap(Window *screen, ViewPoint* vp,WorldStuff *world)//PD 22Apr96
{
	// Satellite view of landscape, with blobs instead of shapes (acs & target)
	ANGLES	oldfov = Save_Data.fieldOfView;
	Save_Data.fieldOfView = ANGLES_90Deg;
	current_screen=screen;
	current_screen->DoSetFade(RED,0,TDE_INSIDE2OUT);
	View_Point=vp;
	SHAPE.SetView(vp,screen);
	current_screen->DoSetViewParams(Save_Data.fieldOfView,screen,vp);						//PD 03Feb98
	_matrix.SetViewParams(current_screen,Save_Data.fieldOfView,0x7FFFFFFF);
	current_screen->BeginScene();									//PD 17Feb97
	View_Point->BlockTick(TRUE);
	View_Point->SelectView();									//PD 19Feb96
	_matrix.SetZScale(current_screen);							
	OverLay.SetViewpoint(View_Point);
	OverLay.SetScreen(current_screen);
	init_scene(world, vp);
	PaletteBlender((Miss_Man.camp.dawntime + 2000)*100);						//daytime?
	View_Point->BlockTick(FALSE);
	current_screen->DoEnableBackClip(FALSE);


	{
	SWord qx,qy,qw,qh;
	qx=SWord(float(6)*float(OverLay.physicalWidth)/640.);
	qw=SWord(float(316)*float(OverLay.physicalWidth)/640.);
	qy=SWord(float(1)*float(OverLay.physicalHeight)/480.);
	qh=SWord(float(438)*float(OverLay.physicalHeight)/480.);
//	if (Save_Data.fSoftware)
//	{
//		POLYGON.PushViewData();
//		POLYGON.Set3DWin(qx,qy,qw,qh);
//	}
	if (!Save_Data.fSoftware)
	{
		screen->DoPushViewData();
		screen->DoSet3DWin(qx,qy,qw,qh);
		Float qd=0;
		current_screen->DoCalcItemFog(true,qd,qd,qd);
	}
	}

	Land_Scape.RenderLandscape(	screen,View_Point,							
								fpviewer_matrix,					
								viewer_x,viewer_y,viewer_z,		
								vp->hdg);
	current_screen->DoFlushLandDraw();
//	if (Save_Data.fSoftware)
//		POLYGON.PopViewData();
	if (!Save_Data.fSoftware)
		screen->DoPopViewData();
 	do_objects_map(TRUE);
	add_map(*vp,TRUE);
	render_scene();								
	bt->Clear3DArea();
	current_screen->DoEnableBackClip(TRUE);
	current_screen->End3DScene();
	View_Point->BlockTick(TRUE);
	OverLay.ProcessUIScreen();
	View_Point->BlockTick(FALSE);
	current_screen->EndScene();	
	Save_Data.fieldOfView = oldfov;//RJS 09Nov98
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		do_objects_map
//Author		Robert Slater
//Date			Tue 20 Oct 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ThreeDee::do_objects_map(Bool	zoomed)
{
	ShapeDescPtr	sdptr;
	int		i,j;
	item 	tempitem,
			*tempitemptr;
	UWord	sector_x,
			sector_y,
			current_sector_x,
			current_sector_y,
			min_sector_x,
			max_sector_x,
			min_sector_y,
			max_sector_y,
			this_sector;

	sdptr = SHAPESTUFF.GetShapePtr(MAPZ);
	SLong	properdistz = (sdptr->sx << 4)*4;
	SLong	zoomoffset = (properdistz - mapdistz)>>1;

	if (zoomed==TRUE)
	{
		tempitemptr = &tempitem;

		tempitemptr->World.X = Manual_Pilot.ControlledAC2->World.X;
		tempitemptr->World.Y = Manual_Pilot.ControlledAC2->World.Y;
		tempitemptr->World.Z = Manual_Pilot.ControlledAC2->World.Z;

		current_world->getsectornos(tempitemptr,sector_x,sector_y);

		max_sector_x = sector_x + 1;
		max_sector_y = sector_y + 1;

		min_sector_x = sector_x - 1;
		min_sector_y = sector_y - 1;

		if (min_sector_x > 32)		// cos unsigned arithmetic (-1 = 65536)
			min_sector_x = 0;

		if (min_sector_y > 32)		// cos unsigned arithmetic (-1 = 65536)
			min_sector_y = 0;

		if (max_sector_x > 32)
			max_sector_x = 32;

		if (max_sector_y > 32)
			max_sector_y = 32;

		zoomoffset = 0;//(FT_25000 - FT_20000)>>1;
		mapoffx = mapoffy = 0;
		mapdistz = 0;//FT_20000;		// This is how high we want the items on the Landscape map
	}
	else
	{
		min_sector_x = min_sector_y = 0;
		max_sector_x = max_sector_y = 32;
	}

	for(current_sector_x = min_sector_x;current_sector_x < max_sector_x; current_sector_x++)
	{
		for(current_sector_y = min_sector_y; current_sector_y < max_sector_y;current_sector_y++)
		{
			this_sector = current_world->makeindex(current_sector_x,current_sector_y);
			tempitemptr = current_world->getfirstitem(this_sector);

			while (tempitemptr)
			{
				if (	(tempitemptr->Status.size==AirStrucSize)
					/*&&	(tempitemptr != Persons2::PlayerGhostAC)*/	)
				{
					switch(SHAPESTUFF.GetShapeScale(sdptr))
					{
						case SHP_1CM:
						case SHP_4CM:
						case SHP_16CM:

							do_map_object(tempitemptr,zoomoffset);

							break;
					}
				}
			 	tempitemptr = tempitemptr->Next;
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		do_map_object
//Author		Robert Slater
//Date			Tue 20 Oct 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ThreeDee::do_map_object(ItemPtr	tempitemptr,SLong	zoomoffset)
{
	Obj3DPtr		obj3dptr;										
	IFShare			wx,wy,wz;
	animptr			adptr=tempitemptr->Anim;	 //RJS 4/16/99	//RJS 21Apr99
	IFShare			bzoffset;
	ShapeDescPtr	sdptr;
	MinAnimData*	mad = (MinAnimData*)adptr;
	SLong			xmax,ymax;
	SLong			xmap,ymap;
	SLong			ix,iy;
	SLong			gridsize = 1 << 21;

	// Total world is 1 - 8 by 1 - 8
	// World covered is 2 - 6 by 2 - 8

	// Each block is 1 << 21 cm square

	xmap = tempitemptr->World.X - (gridsize*11);// cos real map doesn't start til after 11 blocks (8 + 3)
	ymap = tempitemptr->World.Z;

	xmax = gridsize * 37;      // Five big blocks of 8 little blocks
	ymax = gridsize * 64;

	if ((xmap < xmax) && (ymap < ymax))
	{
		xmax /= 312;
		ymax /= 624;

		ix = (xmap << 2)/xmax;			//Width of map object is 312 cm x 4cm scale
		iy = (ymap << 2)/ymax;			//Height of map object is double the width

		ix += mapoffx;
		iy += mapoffy;

		ix += zoomoffset;

		wx.f = (-312 * 4) + ix;				//cos map is 4cm scale							
		wy.f = (-290 * 4) + iy;													
		wz.f = mapdistz - 4;	
		
		bzoffset.f = 1.0;	

		obj3dptr = (Obj3DPtr )bt->Get3DArea(STATIC_OBJECT);
		SetObj3D(obj3dptr,tempitemptr,wx,wy,wz,bzoffset);

		obj3dptr->Shape = MAPRED;
		obj3dptr->AnimPtr = adptr;	

		bt->insert_object(obj3dptr);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		do_smoke_object
//Author		Robert Slater
//Date			Wed 16 Sep 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//void	ThreeDee::do_smoke_object(	ItemPtr		theLauncher,
//									Coords3D	*posP,
//									ShapeNum	theShape	)
//{
//	IFShare			wx,wy,wz;
//	ShapeDescPtr	sdptr;
//	SLong			shpsize;
//
//	wx.i = posP->X - viewer_x;
//	wy.i = posP->Y - viewer_y;
//	wz.i = posP->Z - viewer_z;
//
//	_matrix.transform(fpviewer_matrix,wx,wy,wz);
//
//	sdptr = SHAPESTUFF.GetShapePtr(theShape);
//	shpsize = sdptr->Size<<4;
//
//	if(RoughCone(wx,wy,wz,shpsize))
//	{										
//		WorldStuff	*world = mobileitem::currworld;
//	}
//}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		renderreplay
//Author		Robert Slater
//Date			Tue 20 Oct 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ThreeDee::renderreplay(Window *screen, ViewPoint* vp,WorldStuff *world)//PD 22Apr96
{
	current_screen=screen;
	View_Point=vp;
	bt->SetupBTree(screen,vp);									//AMM 10Feb99
	SHAPE.SetView(vp,screen);

	current_screen->DoSetViewParams(Save_Data.fieldOfView,screen,vp);
	_matrix.SetViewParams(current_screen,Save_Data.fieldOfView,0x7FFFFFFF);
	SHAPE.SetDistScale();										//AMM 10Feb99
	current_screen->BeginScene();

	fnum++;

	View_Point->BlockTick(TRUE);
	View_Point->SelectView();									

	_matrix.SetZScale(current_screen);							
//DEAD	POLYGON.setpolyscrn(screen,,Save_Data.fieldOfView);

//DEAD	POLYGON.SetCrossProduct(TRUE);

	OverLay.SetViewpoint(View_Point);
	OverLay.SetScreen(current_screen);

	init_scene(world, vp);

	PaletteBlender(View_Point->TimeOfDay()); 
	pTMake->BuildShadowList(world,vp);							//RJS 17Feb99
	ShapeNum manualPilotShape=Manual_Pilot.ControlledAC2->shape;
	if (manualPilotShape==CMIG15) Manual_Pilot.ControlledAC2->shape=MIG15;
	do_objects();		
	Manual_Pilot.ControlledAC2->shape=manualPilotShape;

	View_Point->BlockTick(FALSE);
//DEAD	current_screen->LockBackScreen(TRUE,MIDLOCK);	  

//DeadCode PD 24Nov98 	current_screen->DoSetZUpdate(FALSE);
	current_screen->DoEnableBackClip(FALSE);

	if (_Replay.UpdateLandscape)
	{
		_Replay.UpdateLandscape=false;
		Land_Scape.RefreshLandscape();
	}

	Land_Scape.RenderLandscape(	screen,View_Point,							
								fpviewer_matrix,					
								viewer_x,viewer_y,viewer_z,		
								vp->hdg);

	current_screen->DoFlushLandDraw();
//DEAD 	current_screen->UnLockBackScreen(MIDLOCK);		


	// Shove everything into binary tree and render...
//dEAD,cos gonna use interface stuff instead...	add_replay(*vp);
	Add_Sun(*vp,world);										
	Land_Scape.CloudLayer(View_Point);						
	SHAPE.InitCloudFade();									
	render_scene();											
	SHAPE.SetCloudFade();
	bt->Clear3DArea();
	// ...shoved everything into binary tree and rendered

//DeadCode PD 24Nov98 	current_screen->DoSetZUpdate(TRUE);
	current_screen->DoEnableBackClip(TRUE);
	current_screen->End3DScene();
	View_Point->BlockTick(TRUE);
	OverLay.ProcessUIScreen();
	View_Point->BlockTick(FALSE);

	current_screen->EndScene();	
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		add_replay
//Author		Robert Slater
//Date			Tue 20 Oct 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ThreeDee::add_replay(rotitem& viewpoint)
{
	ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(RPLAY);
	if (sdptr)
	{
		Obj3DPtr	obj3dptr;										
		IFShare		wx,wy,wz;
		IFShare		bzoffset;
		Bool		bDoingHardware3D = current_screen->DoingHardware3D();
		item		tempitem,
					*tempitemptr;

		tempitemptr = &tempitem;

		if (bDoingHardware3D)
		{
			current_screen->DoSetPlayerTextures(TRUE);				
//DeadCode PD 24Nov98 			current_screen->DoSetZUpdate(FALSE);		
		}										

		tempitem.World.X = viewpoint.World.X;
		tempitem.World.Y = viewpoint.World.Y;
		tempitem.World.Z = viewpoint.World.Z;
		tempitemptr->Anim = Manual_Pilot.ControlledAC2->Anim;
		tempitem.shape = RPLAY;

		wx.f = 0;								
		wy.f = 0;													
		wz.f = (sdptr->sx << 4);

		obj3dptr = (Obj3DPtr )bt->Get3DArea(STATIC_OBJECT);

		bzoffset.f=0;

		SetObj3D(obj3dptr,tempitemptr,wx,wy,wz,bzoffset);

		obj3dptr->objtype = MAP_OBJECT;
		obj3dptr->AnimPtr= Manual_Pilot.ControlledAC2->Anim;								//RJS 21Apr99

		bt->insert_object2(obj3dptr);

		tempitem.Anim=NULL;	
						
//DeadCode PD 24Nov98 		if (bDoingHardware3D)
//DeadCode PD 24Nov98 			current_screen->DoSetZUpdate(TRUE);
	}
}

void SetBuffetData(CockpitBuf* newBuffetData)
{
	Three_Dee.SetCockpitBuffet(newBuffetData);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetCockpitBuffet
//Author		Paul.   
//Date			Thu 29 Oct 1998
//------------------------------------------------------------------------------
void ThreeDee::SetCockpitBuffet(CockpitBuf* newBuffetData)
{
 	buffetData=*newBuffetData;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SuperShapeCheat
//Author		Robert Slater
//Date			Mon 9 Nov 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ThreeDee::SuperShapeCheat()
{
#if !defined(NDEBUG)
	if (shapecheat)
	{
		if (Key_Tests.KeyPress3d(GROUPINFOMSG))
		{
 			WorldStuff	*worldptr = mobileitem::currworld;
 			ItemPtr		firstitem,nextitem;
 			UWord		nextsector, i, totcount;
 
 			if (supercheatitem)
 			{
				nextitem = supercheatitem->Next;
				while (nextitem)
				{
					if (nextitem->Status.size == TRANSIENTSIZE)
						nextitem = nextitem->Next;
					else
						break;
				}

 				if (nextitem == NULL)
 				{
 					nextsector = worldptr->GetSector(supercheatitem);
 		
 					i = nextsector;
 					totcount = 0;

 					firstitem = worldptr->getfirstitem(nextsector);
					while (firstitem)
					{
						if (firstitem->Status.size == TRANSIENTSIZE)
							firstitem = firstitem->Next;
						else
							break;
					}

 					while (firstitem == NULL)
 					{
 						i++;

 						totcount++;

 						if (i == 32*32)
 							i = 0;

 						firstitem = worldptr->getfirstitem(i);

 						if (totcount == 32*32-1)
 							firstitem = Manual_Pilot.ControlledAC2;

						while (firstitem)
						{
							if (firstitem->Status.size == TRANSIENTSIZE)
								firstitem = firstitem->Next;
							else
								break;
						}
 					}

 					nextitem = firstitem;
 				}

 				supercheatitem = nextitem;

				// Set tracked item to supercheatitem...

				View_Point->SetCheatItem(supercheatitem);

				char	shite[32];
				sprintf(shite,"Shape : %d  ",supercheatitem->shape);
				Mono_Text.PrintAt(55,5,(UByteP)shite);
 			}
 			else
 				supercheatitem = Manual_Pilot.ControlledAC2;
		}
	}

	if (supercheatitem)
	{
		if (Key_Tests.KeyPress3d(POSTCOMBATMSG))
			KillTheFucker(LT_BULLET);

		if (Key_Tests.KeyPress3d(PRECOMBATMSG))
			KillTheFucker(LT_BOMB);

		if (Key_Tests.KeyPress3d(COMBATMSG))
			KillTheFucker(LT_NAPALM);
//			KillTheFucker(LT_ROCKET);

		if (Key_Tests.KeyPress3d(TOWERMSG))
			KillTheFucker(LT_NAPALM);

		char	shite[64];
		sprintf(shite,"%d   %d   %d   ",supercheatitem->World.X,supercheatitem->World.Y,supercheatitem->World.Z);
		Mono_Text.PrintAt(50,7,(UByteP)shite);
	}
#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		KillTheFucker
//Author		Robert Slater
//Date			Wed 11 Nov 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ThreeDee::KillTheFucker(UByte	lnchrtype)
{
	if (supercheatitem)
	{
 		WorldStuff	*worldptr = mobileitem::currworld;

		switch (lnchrtype)
		{
		case LT_BULLET:
			Trans_Obj.TwatWithWeapon(supercheatitem,BULLET,-1,*worldptr);
			break;
		case LT_ROCKET:
			Trans_Obj.TwatWithWeapon(supercheatitem,ROCKET,-1,*worldptr);
			break;
		case LT_BOMB:
			Trans_Obj.TwatWithWeapon(supercheatitem,BMB100,-1,*worldptr);
			break;
		case LT_NAPALM:
			Trans_Obj.TwatWithWeapon(supercheatitem,DUMY10,-1,*worldptr);
			break;
		case LT_CONTACT:
			Trans_Obj.TwatWithWeapon(supercheatitem,Manual_Pilot.ControlledAC2->shape,-1,*worldptr);
			break;
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		do_object_dummy
//Author		Robert Slater
//Date			Wed 11 Nov 1998
//
//Description	Same as do_object, but sets the object's itemptr to NULL,
//				cos it is not real......
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ThreeDee::do_object_dummy(itemptr tempitemptr,bool fSpecial)
//DeadCode PD 28Apr99 void ThreeDee::do_object_dummy(itemptr tempitemptr)
{
	Obj3DPtr	obj3dptr;										//PD 13Mar96
	IFShare		wx,wy,wz;
	btree*		which_tree;

	which_tree=bt;

	if (tempitemptr->Anim==NULL)								//RJS 21Apr99
		SHAPE.SetAnimData(tempitemptr,0);						//RDH 23Sep96

//DeadCode RJS 21Apr99 	UByteP	adptr=(UByteP )tempitemptr->Anim;					//PD 27Mar96

	IFShare			bzoffset;

	ShapeDescPtr	sdptr;
//DeadCode RJS 21Apr99 	MinAnimData*	mad = (MinAnimData*)adptr;

	if(tempitemptr->World.Y==0)
		tempitemptr->World.Y = _Collide.AccurateGroundAltitude(tempitemptr->World);//PD 08Oct96

	wx.i = tempitemptr->World.X - viewer_x;
	wy.i = tempitemptr->World.Y - viewer_y;
	wz.i = tempitemptr->World.Z - viewer_z;

	_matrix.transform(fpviewer_matrix,wx,wy,wz);

	sdptr = SHAPESTUFF.GetShapePtr(tempitemptr->shape);
	int	shpsize = sdptr->Size<<4;	

	if(RoughCone(wx,wy,wz,shpsize))
	{									
		if (!sdptr->Type.DrawPriority)	
			bzoffset.f = (Float)shpsize;
		else							
			bzoffset.f = 1000.0;		

		obj3dptr = (Obj3DPtr )which_tree->Get3DArea(STATIC_OBJECT);
		SetObj3D(obj3dptr,tempitemptr,wx,wy,wz,bzoffset);
		if (fSpecial) obj3dptr->objtype=SHADEOVERRIDE_OBJECT;

		obj3dptr->ItemPtr = NULL;
		obj3dptr->AnimPtr = tempitemptr->Anim;					//RJS 21Apr99

		which_tree->insert_object(obj3dptr);			
																
		SHAPE.animate_shape(obj3dptr);							
	}															
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NearestAliveThing
//Author		Robert Slater
//Date			Mon 16 Nov 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
ItemPtr	ThreeDee::NearestAliveThing(ItemPtr	itm)
{
	WorldStuff	*worldptr = mobileitem::currworld;
 	ItemPtr		firstitem,founditem;
	SLong		x,y,z,dx,dy,dz,dist,mindist;
	MinAnimData*	mad;

	x = itm->World.X;
	y = itm->World.Y;
	z = itm->World.Z;

	founditem = NULL;
	mindist = 100000000;

	firstitem = worldptr->getfirstitem(worldptr->GetSector(itm));
 	while (firstitem)
 	{
		if (	(firstitem != itm)								//RJS 11Jun99
			&&	(firstitem->Status.size < MOVINGSIZE)	)		//RJS 11Jun99
		{
			mad = (MinAnimData*) firstitem->Anim;
			if (mad && (mad->itemstate == ALIVE))
			{
				dx = firstitem->World.X - x;
				dy = firstitem->World.X - y;
				dz = firstitem->World.Z - z;

				dist = Math_Lib.distance3d(dx,dy,dz);
				if (dist < mindist)
				{
					founditem = firstitem;

					mindist = dist;
				}
			}
		}
	
		firstitem = firstitem->Next;
	}

	return (founditem);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetVP
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
void	ThreeDee::SetVP(ViewPoint*	vp)
{
	View_Point=vp;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		IsItVisible
//Author		Rob.   
//Date			Wed 9 Dec 1998
//
//Description	For effects like barrages....
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool	ThreeDee::IsItVisible(Coords3D&	worldpos)				//RJS 18May99
{
	bool	retval = false;
	if (havematrix)
	{
		IFShare	wx,wy,wz;

		wx.i = worldpos.X - viewer_x;
		wy.i = worldpos.Y - viewer_y;
		wz.i = worldpos.Z - viewer_z;

		_matrix.transform(fpviewer_matrix,wx,wy,wz);
		if (RoughCone(wx,wy,wz,2000))							//give it about 20m radius
			retval = true;
	}

	return(retval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StuffInBinaryTree
//Author		Robert Slater
//Date			Fri 23 Apr 1999
//
//Description	Same as do_object,
//				but doesn't perform animdata or invisible check....
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ThreeDee::StuffInBinaryTree(ItemPtr	tempitemptr)
{
	Obj3DPtr	obj3dptr;					
	IFShare		wx,wy,wz;
	btree*		which_tree = bt;
	bool		beenfixed = false;
	IFShare		bzoffset;
	ShapeDescPtr	sdptr;

	if(tempitemptr->World.Y==0)
	{
		tempitemptr->World.Y = _Collide.AccurateGroundAltitude(tempitemptr->World);//PD 08Oct96
		beenfixed = true;
	}

	wx.i = tempitemptr->World.X - viewer_x;
	wy.i = tempitemptr->World.Y - viewer_y;
	wz.i = tempitemptr->World.Z - viewer_z;

	_matrix.transform(fpviewer_matrix,wx,wy,wz);
	if (tempitemptr->Status.size == TRANSIENTSIZE)
	{
		UWord	offset = ((TransientItem*)tempitemptr)->DrawOffset;
		if (offset)
		{
			// scale the 3d coords so the object is drawn closer...
			Float	newz = wz.f - Float(offset);
			Float	dscale = newz / wz.f;

			wx.f *= dscale;
			wy.f *= dscale;
			wz.f = newz;
		}
	}

	sdptr = SHAPESTUFF.GetShapePtr(tempitemptr->shape);
	int	shpsize = sdptr->Size<<4;					   

	if(RoughCone(wx,wy,wz,shpsize) || (tempitemptr->shape == ROCKET))
	{									
 		if (!sdptr->Type.DrawPriority)	
			bzoffset.f = (Float)shpsize;
 		else							
 			bzoffset.f = 12325.0;		

		obj3dptr = (Obj3DPtr )which_tree->Get3DArea(STATIC_OBJECT);
		SetObj3D(obj3dptr,tempitemptr,wx,wy,wz,bzoffset);

		obj3dptr->AnimPtr = tempitemptr->Anim;

		which_tree->insert_object(obj3dptr);

		SHAPE.animate_shape(obj3dptr);

		tempitemptr->Status.Drawn = TRUE;

#ifndef NDEBUG					
		if (supercheatitem && (beenfixed==true))			
			tempitemptr->World.Y = 0;
#endif
	} 
	else
		SHAPE.dummy_animate_shape(tempitemptr,(UByteP)sdptr);

	SHAPE.sfx_shape(tempitemptr,wx,wy,wz);
}
