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
//Filename       main.cpp
//System         
//Author         Paul.   
//Date           Tue 4 Jul 1995
//Description    
//------------------------------------------------------------------------------

#define		F_GRAFIX
#include	"DOSDefs.H"
#include	"Files.G"
#include	"FileMan.h"
#include	"getset.h"
#include	"Main.H"
#include	"UI.h"
#include	<stdio.h>
#include	<stdlib.h>
#include	<systime.h>
#include	"mymath.h"
#include	"Analogue.h"

#include	"miles.h"
//DeadCode ARM 02Aug96 #include	<stdio.h>
//DeadCode ARM 02Aug96 #include	<stdlib.h>
#include	<Signal.h>										//PD 06Nov95
//DeadCode JIM 30Nov95 MATHABLE(ANGLES);

//DeadCode JIM 22Nov95 extern	KeyMapping	*Debug3dMapTable;							//JIM 03Nov95

//DeadCode JIM 22Nov95 #include	"forms.h"											//DAW 20Oct95
//DeadCode JIM 22Nov95 #include	"flymodel.h"									//PD 01Nov95

////////////////////////////////////////////////////////////////////////////////
//
//
////////////////////////////////////////////////////////////////////////////////

//DeadCode JIM 22Nov95 extern	Three_Dee	_Three_Dee;
void	TextTest();

//DeadCode JIM 09Nov95 extern	Wrapper	_Wrapper;
//DeadCode JIM 15Nov95 extern	UIControl*	MakeFirstSelectSheet(ScreenXY XY,ScreenWH WH);
//DeadCode JIM 15Nov95 UIControl*	MainControl;							//DAW 05Oct95 temp
//Old_Code DAW 25Oct95 extern  ImageMap ImageMap;

#include	"worldinc.h"										//ARM 12Aug96
#include	"uniqueID.h"										//ARM 12Aug96

#include "winmove.h"											//RDH 25Nov96

Main	_Main;
DPlay	_DPlay;													//ARM 12Aug96

Display		*Whole_Screen=NULL;
//DeadCode JIM 12Dec95 ScreenRecord	*screen;

//DeadCode JIM 22Nov95 void	MoveViewPoint(void );
//DeadCode JIM 22Nov95 
//DeadCode JIM 22Nov95 SLong	ViewX = 0x0104fb5<<6;
//DeadCode JIM 22Nov95 SLong	ViewZ = 0x017ad31<<6;
//DeadCode JIM 22Nov95 SLong	ViewY = 2200;
//DeadCode JIM 22Nov95 ANGLES	ViewHDG = ANGLES_0Deg;
SLong	ViewX = 0x0104fb5<<6;
SLong	ViewZ = 0x017ad31<<6;
//SLong	ViewY = 220000;											//RDH 14Nov95
SLong	ViewY = 2200;											//RDH 14Nov95
ANGLES	ViewHDG = ANGLES_0Deg;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	main
//------------------------------------------------------------------------------
//Author	Paul.   
//Date		Wed 5 Jul 1995
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
extern	void	TextTest();										//DAW 16Nov95
void	main(int	argc,char	*argv[])
{

	_amblksiz=0x60000;	//multiples of 350K

	int	t=time(NULL);
	t=t+t>>16;
	t=t+t>>8;
	t&=0xff;
	while (t--)	Math_Lib.rnd();



	signal(SIGBREAK,SIG_IGN);									//JIM 15Dec95
	_Main.ReadArgs(argc,argv);

	_Main.MainInit();
	TextTest();
	_Analogue.Test();
	delete new char [0x900000];	//9MB memory required at this point.

	while (UISheet::Win95ManageSheets(Whole_Screen)) {}	//JIM 22Nov95 This is the main loop

	//General deallocation & stuff

	_Main.QuitGame();

	//Display copyright message

	_Main.RowanMessage();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	Main::MainInit
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 5 Jul 1995
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
void Main::MainInit(void)
{
//TempCode ARM 27Jun96 	fileman::quitonfailalloc=FALSE;							//MS 11Apr96

	if((Whole_Screen = new Display) == NULL)
		_Error.EmitSysErr(__FILE__":Failed to create screen record\n");

	if(InitFileSystem(*this)==FALSE)
		_Error.EmitSysErr(__FILE__":Failed to init file system\n");

	if(Whole_Screen->Init(*this) == FALSE)	
		_Error.EmitSysErr(__FILE__":Failed to initialise screen record\n");


	ScreenRez	modelist[20];
	Whole_Screen->ListVesaModes(modelist);

 	_Miles.Init();												//DAW 03Apr96
}


//DeadCode JIM 22Nov95 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JIM 22Nov95 //Procedure		DoScreen
//DeadCode JIM 22Nov95 //Author		Dave Whiteside
//DeadCode JIM 22Nov95 //Date			Fri 20 Oct 1995
//DeadCode JIM 22Nov95 //
//DeadCode JIM 22Nov95 //Description	
//DeadCode JIM 22Nov95 //
//DeadCode JIM 22Nov95 //Inputs		
//DeadCode JIM 22Nov95 //
//DeadCode JIM 22Nov95 //Returns	
//DeadCode JIM 22Nov95 //
//DeadCode JIM 22Nov95 //------------------------------------------------------------------------------
//DeadCode JIM 22Nov95 void Main::DoScreen(ScreenRecord *screen)
//DeadCode JIM 22Nov95 {
//DeadCode JIM 22Nov95 
//DeadCode JIM 22Nov95 //DeadCode JIM 15Nov95 	Forms		MainForm;
//DeadCode JIM 22Nov95 
//DeadCode JIM 22Nov95 	//ControlUISound();
//DeadCode JIM 22Nov95 		UISheet::ManageSheets(screen);
//DeadCode JIM 22Nov95 //DeadCode JIM 21Nov95 		UISheet::DrawSheet(screen);											//DAW 11Oct95
//DeadCode JIM 22Nov95 //DeadCode JIM 22Nov95 	  	_Wrapper.ScreenSwap(screen);
//DeadCode JIM 22Nov95 //DeadCode JIM 21Nov95 		UISheet::HandleInput();
//DeadCode JIM 22Nov95 
//DeadCode JIM 22Nov95 }

//DeadCode JIM 22Nov95 THIS HAS ALL MOVED TO UI\STATE3D.CC
//DeadCode JIM 22Nov95 
//DeadCode JIM 22Nov95 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JIM 22Nov95 //Procedure		Do3DScreen
//DeadCode JIM 22Nov95 //Author		Paul.   
//DeadCode JIM 22Nov95 //Date			Tue 10 Oct 1995
//DeadCode JIM 22Nov95 //
//DeadCode JIM 22Nov95 //Description	
//DeadCode JIM 22Nov95 //
//DeadCode JIM 22Nov95 //Inputs		
//DeadCode JIM 22Nov95 //
//DeadCode JIM 22Nov95 //Returns	
//DeadCode JIM 22Nov95 //
//DeadCode JIM 22Nov95 //------------------------------------------------------------------------------
//DeadCode JIM 22Nov95 void Main::Do3DScreen(ScreenRecord *screen,WorldStuff *worldptr)
//DeadCode JIM 22Nov95 {
//DeadCode JIM 22Nov95 	//Load in the shape files requested by the battle field file loads
//DeadCode JIM 22Nov95 
//DeadCode JIM 22Nov95 	SHAPESTUFF.LoadRequiredShapes();
//DeadCode JIM 22Nov95 
//DeadCode JIM 22Nov95 	//Load in the image maps requested by the shape loads
//DeadCode JIM 22Nov95 
//DeadCode JIM 22Nov95   	Image_Map.LoadImageMapPtrs();
//DeadCode JIM 22Nov95 
//DeadCode JIM 22Nov95 	//Call the 3D loop repeatedly until finished
//DeadCode JIM 22Nov95 
//DeadCode JIM 22Nov95 	Key_Tests.Reg3dConv(Debug3dMapTable,1000);
//DeadCode JIM 22Nov95 
//DeadCode JIM 22Nov95 	_Three_Dee.Init3D();
//DeadCode JIM 22Nov95 
//DeadCode JIM 22Nov95 	while(_Main.Loop3D(screen,worldptr)!=FALSE)
//DeadCode JIM 22Nov95 	{
//DeadCode JIM 22Nov95 		Manual_Pilot.MainManualPilot();							//PD 01Nov95
//DeadCode JIM 22Nov95 
//DeadCode JIM 22Nov95 		_Wrapper.ScreenSwap(screen);
//DeadCode JIM 22Nov95 
//DeadCode JIM 22Nov95 		//Clear the screen ready for the next frame
//DeadCode JIM 22Nov95 
//DeadCode JIM 22Nov95 		_Wrapper.ClearScreen(screen,0);
//DeadCode JIM 22Nov95 
//DeadCode JIM 22Nov95 UIKeyEvent	mykeyevent,prevkeyevent;
//DeadCode JIM 22Nov95 UByte	*screen=(UByte*) 0xB0000L;
//DeadCode JIM 22Nov95 	breakif(Key_Tests.KeyPress3d((KeyVal3D) EXITKEY));
//DeadCode JIM 22Nov95 //DeadCode JIM 03Nov95 	if (Key_Tests.GetUIKey(mykeyevent)==TRUE)
//DeadCode JIM 22Nov95 //DeadCode JIM 03Nov95 		if (	(mykeyevent.keyhit==KEYHIT)
//DeadCode JIM 22Nov95 //DeadCode JIM 03Nov95 			&&	(mykeyevent.keycode==0x1c)
//DeadCode JIM 22Nov95 //DeadCode JIM 03Nov95 			)
//DeadCode JIM 22Nov95 //DeadCode JIM 03Nov95 			break;
//DeadCode JIM 22Nov95 	};
//DeadCode JIM 22Nov95 
//DeadCode JIM 22Nov95 	//Dispose of the shape files loaded
//DeadCode JIM 22Nov95 
//DeadCode JIM 22Nov95 	SHAPESTUFF.UnLoadRequiredShapes();
//DeadCode JIM 22Nov95 
//DeadCode JIM 22Nov95 	_Three_Dee.Done3D();
//DeadCode JIM 22Nov95 
//DeadCode JIM 22Nov95 	//Dispose of the image map files loaded
//DeadCode JIM 22Nov95 
//DeadCode JIM 22Nov95  	Image_Map.UnLoadImageMapPtrs();
//DeadCode JIM 22Nov95 }
//DeadCode JIM 22Nov95 
//DeadCode JIM 22Nov95 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JIM 22Nov95 //Procedure	Loop3D
//DeadCode JIM 22Nov95 //------------------------------------------------------------------------------
//DeadCode JIM 22Nov95 //Author		Paul.   
//DeadCode JIM 22Nov95 //Date		Wed 23 Aug 1995
//DeadCode JIM 22Nov95 //Modified	
//DeadCode JIM 22Nov95 //
//DeadCode JIM 22Nov95 //Description	
//DeadCode JIM 22Nov95 //
//DeadCode JIM 22Nov95 //Inputs	
//DeadCode JIM 22Nov95 //
//DeadCode JIM 22Nov95 //Returns	
//DeadCode JIM 22Nov95 //
//DeadCode JIM 22Nov95 //Externals
//DeadCode JIM 22Nov95 //------------------------------------------------------------------------------
//DeadCode JIM 22Nov95 //------------------------------------------------------------------------------
//DeadCode JIM 22Nov95 UWord Main::Loop3D(ScreenRecord *screen,WorldStuff *worldptr)
//DeadCode JIM 22Nov95 {
//DeadCode JIM 22Nov95 	rotitem *my_viewpoint = new rotitem;
//DeadCode JIM 22Nov95 
//DeadCode JIM 22Nov95 	my_viewpoint->World.X = ViewX;
//DeadCode JIM 22Nov95 	my_viewpoint->World.Y = ViewY;
//DeadCode JIM 22Nov95 	my_viewpoint->World.Z = ViewZ;
//DeadCode JIM 22Nov95 	MoveViewPoint();
//DeadCode JIM 22Nov95 
//DeadCode JIM 22Nov95 	my_viewpoint->hdg = ViewHDG;
//DeadCode JIM 22Nov95 	my_viewpoint->pitch = ANGLES_10Deg;
//DeadCode JIM 22Nov95 	my_viewpoint->roll = ANGLES_0Deg;
//DeadCode JIM 22Nov95 
//DeadCode JIM 22Nov95 	_Three_Dee.render(screen,worldptr,*my_viewpoint);
//DeadCode JIM 22Nov95 
//DeadCode JIM 22Nov95 	delete my_viewpoint;
//DeadCode JIM 22Nov95 
//DeadCode JIM 22Nov95 	return(TRUE);
//DeadCode JIM 22Nov95 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	Main::QuitGame
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 5 Jul 1995
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
void Main::QuitGame()
{
	Display* ws=Whole_Screen;
	if (ws)
	{
		FILEMAN.CDCloseDown();									//PD 29Oct96
		Whole_Screen=NULL;										//PD 06Nov96

		ws->SetTextMode();
		delete	ws;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	Main::EmitSysErr
//------------------------------------------------------------------------------
//Author	Paul.   
//Date		Tue 4 Jul 1995
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
//DeadCode PD 13Oct95 /*void Main::EmitSysErr(char *fmt, ...)
//DeadCode PD 13Oct95 {
//DeadCode PD 13Oct95 	va_list	marker;
//DeadCode PD 13Oct95 
//DeadCode PD 13Oct95 	va_start(marker, fmt);
//DeadCode PD 13Oct95 
//DeadCode PD 13Oct95 	Main::QuitGame();
//DeadCode PD 13Oct95 
//DeadCode PD 13Oct95 	fprintf(stdout, "ERROR ");
//DeadCode PD 13Oct95 	vfprintf(stdout, fmt, marker);
//DeadCode PD 13Oct95 	fprintf(stdout, "\n");
//DeadCode PD 13Oct95 
//DeadCode PD 13Oct95 	exit(0);
//DeadCode PD 13Oct95 } */

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	RowanMessage
//------------------------------------------------------------------------------
//Author	Paul.   
//Date		Wed 5 Jul 1995
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
void Main::RowanMessage()
{
	fprintf(stdout, "(c) 1997 Rowan Software Ltd. Compiled "__DATE__" "__TIME__"\n");
}


//DeadCode JIM 22Nov95 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JIM 22Nov95 //Procedure		MoveViewPoint
//DeadCode JIM 22Nov95 //Author		Paul.   
//DeadCode JIM 22Nov95 //Date			Tue 17 Oct 1995
//DeadCode JIM 22Nov95 //
//DeadCode JIM 22Nov95 //Description	DEBUG ONLY!!
//DeadCode JIM 22Nov95 //
//DeadCode JIM 22Nov95 //Inputs		
//DeadCode JIM 22Nov95 //
//DeadCode JIM 22Nov95 //Returns	
//DeadCode JIM 22Nov95 //
//DeadCode JIM 22Nov95 //------------------------------------------------------------------------------
//DeadCode JIM 22Nov95 	#include	<conio.h>
//DeadCode JIM 22Nov95 	#include	<dos.h>
//DeadCode JIM 22Nov95 //------------------------------------------------------------------------------
//DeadCode JIM 22Nov95 void MoveViewPoint()
//DeadCode JIM 22Nov95 {
//DeadCode JIM 22Nov95 		if(Key_Tests.KeyHeld3d((KeyVal3D) BACKKEY))		ViewX -= 10;
//DeadCode JIM 22Nov95 		if(Key_Tests.KeyHeld3d((KeyVal3D) FWDKEY))		ViewX += 10;
//DeadCode JIM 22Nov95 		if(Key_Tests.KeyHeld3d((KeyVal3D) LEFTKEY))		ViewZ -= 10;
//DeadCode JIM 22Nov95 		if(Key_Tests.KeyHeld3d((KeyVal3D) RIGHTKEY))	ViewZ += 10;
//DeadCode JIM 22Nov95 		if(Key_Tests.KeyHeld3d((KeyVal3D) UPKEY))		ViewHDG -=ANGLES_2Deg;
//DeadCode JIM 22Nov95 		if(Key_Tests.KeyHeld3d((KeyVal3D) DOWNKEY))		ViewHDG +=ANGLES_2Deg;
//DeadCode JIM 22Nov95 }
//Old_Code DAW 06Nov95 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Old_Code DAW 06Nov95 //Procedure		MoveViewPoint
//Old_Code DAW 06Nov95 //Author		Paul.   
//Old_Code DAW 06Nov95 //Date			Tue 17 Oct 1995
//Old_Code DAW 06Nov95 //
//Old_Code DAW 06Nov95 //Description	DEBUG ONLY!!
//Old_Code DAW 06Nov95 //
//Old_Code DAW 06Nov95 //Inputs		
//Old_Code DAW 06Nov95 //
//Old_Code DAW 06Nov95 //Returns	
//Old_Code DAW 06Nov95 //
//Old_Code DAW 06Nov95 //------------------------------------------------------------------------------
//Old_Code DAW 06Nov95 	#include	<conio.h>
//Old_Code DAW 06Nov95 	#include	<dos.h>
//Old_Code DAW 06Nov95 //------------------------------------------------------------------------------
//Old_Code DAW 06Nov95 void MoveViewPoint()
//Old_Code DAW 06Nov95 {
//Old_Code DAW 06Nov95 	char	c;
//Old_Code DAW 06Nov95 
//Old_Code DAW 06Nov95 	if(kbhit())
//Old_Code DAW 06Nov95 	{
//Old_Code DAW 06Nov95 		c=getch()&0x00FF;
//Old_Code DAW 06Nov95 		switch(c)
//Old_Code DAW 06Nov95 		{
//Old_Code DAW 06Nov95 			case ',':
//Old_Code DAW 06Nov95 				ViewX -= 10;
//Old_Code DAW 06Nov95 				break;
//Old_Code DAW 06Nov95 
//Old_Code DAW 06Nov95 			case '.':
//Old_Code DAW 06Nov95 				ViewX += 10;
//Old_Code DAW 06Nov95 				break;
//Old_Code DAW 06Nov95 
//Old_Code DAW 06Nov95 			case 'p':
//Old_Code DAW 06Nov95 				ViewZ += 10;
//Old_Code DAW 06Nov95 				break;
//Old_Code DAW 06Nov95 
//Old_Code DAW 06Nov95 			case 'l':
//Old_Code DAW 06Nov95 				ViewZ -= 10;
//Old_Code DAW 06Nov95 				break;
//Old_Code DAW 06Nov95 
//Old_Code DAW 06Nov95 			case '<':
//Old_Code DAW 06Nov95 //				ViewHDG -= ANGLES_2Deg;
//Old_Code DAW 06Nov95 				break;
//Old_Code DAW 06Nov95 
//Old_Code DAW 06Nov95 			case '>':
//Old_Code DAW 06Nov95 //				ViewHDG += ANGLES_2Deg;
//Old_Code DAW 06Nov95 				break;
//Old_Code DAW 06Nov95 
//Old_Code DAW 06Nov95 			case 'c':
//Old_Code DAW 06Nov95 				ViewX =0x0104fb5<<6;
//Old_Code DAW 06Nov95 				ViewZ =0x017ad31<<6;
//Old_Code DAW 06Nov95 				ViewHDG=ANGLES_0Deg;
//Old_Code DAW 06Nov95 				break;
//Old_Code DAW 06Nov95 
//Old_Code DAW 06Nov95 		}
//Old_Code DAW 06Nov95 	}
//Old_Code DAW 06Nov95 }


	Analogue::Test()
{
 	devices[1].devfile=FILLIB_ANALOGUE_MOUSE;
 	devices[1].activeaxes|=AU_UI_X;
 	devices[1].activeaxes|=AU_UI_Y;
	devices[0].devfile=FILLIB_ANALOGUE_JOYSTICK;
//DeadCode JIM 25Apr96 	(devices[0].activeaxes|=AU_AILERON)|=AU_ELEVATOR;
//DeadCode RDH 19Apr96 	((devices[0].activeaxes|=AU_AILERON)|=AU_ELEVATOR)|=AU_THROTTLE;
 	Initialise();
}

