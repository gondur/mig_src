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

//DEADCODE DAW 28/03/99 //------------------------------------------------------------------------------
//DEADCODE DAW 28/03/99 //Filename       mouse.cpp
//DEADCODE DAW 28/03/99 //System         
//DEADCODE DAW 28/03/99 //Author         Jim Taylor
//DEADCODE DAW 28/03/99 //Date           Tue 30 Jan 1996
//DEADCODE DAW 28/03/99 //Description    Code to read hardware mouse.. well.. keyboard at present
//DEADCODE DAW 28/03/99 //------------------------------------------------------------------------------
//DEADCODE DAW 28/03/99 #define	SPECIAL_KEYMAPS	0
//DEADCODE DAW 28/03/99 #include	"keytest.h"
//DEADCODE DAW 28/03/99 #include	"MOUSE.H"
//DEADCODE DAW 28/03/99 #include	"Analogue.h"
//DEADCODE DAW 28/03/99 #include	"myangles.h"
//DEADCODE DAW 28/03/99 #include	"Mytime.h"
//DEADCODE DAW 28/03/99 	Mouse	_Mouse;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE DAW 28/03/99 //Procedure		MoveMouse
//DEADCODE DAW 28/03/99 //Author		Jim Taylor
//DEADCODE DAW 28/03/99 //Date			Tue 30 Jan 1996
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Description	Allow a mouse move to be processed
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Inputs		
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Returns	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //------------------------------------------------------------------------------
//DEADCODE DAW 28/03/99 void	Mouse::Move(int mouseshape)
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 UIKeyNoMouse keyfake={0,KEYSH_norm,KEYHIT};
//DEADCODE DAW 28/03/99 static UWord	x=0,y=0,lastmouse=-2;
//DEADCODE DAW 28/03/99 ScreenXY&
//DEADCODE DAW 28/03/99 		mousepos=Key_Tests.mousepos();
//DEADCODE DAW 28/03/99 //DeadCode DAW 02Apr96 	if (movekeycheat)
//DEADCODE DAW 28/03/99 //DeadCode DAW 02Apr96 	{
//DEADCODE DAW 28/03/99 //DeadCode DAW 02Apr96 UIKeyEvent
//DEADCODE DAW 28/03/99 //DeadCode DAW 02Apr96 		latestcookedkey=*movekeycheat;
//DEADCODE DAW 28/03/99 //DeadCode DAW 02Apr96 		if (latestcookedkey==COOKEDKEY_LEFT)
//DEADCODE DAW 28/03/99 //DeadCode DAW 02Apr96 			mousepos.x-=50;
//DEADCODE DAW 28/03/99 //DeadCode DAW 02Apr96 		if (latestcookedkey==COOKEDKEY_RIGHT)
//DEADCODE DAW 28/03/99 //DeadCode DAW 02Apr96 			mousepos.x+=50;
//DEADCODE DAW 28/03/99 //DeadCode DAW 02Apr96 		if (latestcookedkey==COOKEDKEY_UP)
//DEADCODE DAW 28/03/99 //DeadCode DAW 02Apr96 			mousepos.y-=50;
//DEADCODE DAW 28/03/99 //DeadCode DAW 02Apr96 		if (latestcookedkey==COOKEDKEY_DOWN)
//DEADCODE DAW 28/03/99 //DeadCode DAW 02Apr96 			mousepos.y+=50;
//DEADCODE DAW 28/03/99 //DeadCode DAW 02Apr96 
//DEADCODE DAW 28/03/99 //DeadCode DAW 02Apr96 		if (latestcookedkey==COOKEDKEY_RLEFT)
//DEADCODE DAW 28/03/99 //DeadCode DAW 02Apr96 			mousepos.x-=500;
//DEADCODE DAW 28/03/99 //DeadCode DAW 02Apr96 		if (latestcookedkey==COOKEDKEY_RRIGHT)
//DEADCODE DAW 28/03/99 //DeadCode DAW 02Apr96 			mousepos.x+=500;
//DEADCODE DAW 28/03/99 //DeadCode DAW 02Apr96 		if (latestcookedkey==COOKEDKEY_RUP)
//DEADCODE DAW 28/03/99 //DeadCode DAW 02Apr96 			mousepos.y-=200;
//DEADCODE DAW 28/03/99 //DeadCode DAW 02Apr96 		if (latestcookedkey==COOKEDKEY_RDOWN)
//DEADCODE DAW 28/03/99 //DeadCode DAW 02Apr96 			mousepos.y+=200;
//DEADCODE DAW 28/03/99 //DeadCode DAW 02Apr96 
//DEADCODE DAW 28/03/99 //DeadCode DAW 02Apr96 		if (latestcookedkey==COOKEDKEY_LB)
//DEADCODE DAW 28/03/99 //DeadCode DAW 02Apr96 			keyfake.keycode=Raw_Extra0ML;
//DEADCODE DAW 28/03/99 //DeadCode DAW 02Apr96 		if (latestcookedkey==COOKEDKEY_MB)
//DEADCODE DAW 28/03/99 //DeadCode DAW 02Apr96 			keyfake.keycode=Raw_Extra1MM;
//DEADCODE DAW 28/03/99 //DeadCode DAW 02Apr96 		if (latestcookedkey==COOKEDKEY_RB)
//DEADCODE DAW 28/03/99 //DeadCode DAW 02Apr96 			keyfake.keycode=Raw_Extra2MR;
//DEADCODE DAW 28/03/99 //DeadCode DAW 02Apr96 
//DEADCODE DAW 28/03/99 //DeadCode DAW 02Apr96 	}
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 //some code for reading real mouse
//DEADCODE DAW 28/03/99 //...
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 	RealTime=Timer_Code.TestLoopTime();
//DEADCODE DAW 28/03/99 	if (RealTime==0)
//DEADCODE DAW 28/03/99 		lasttime=0;
//DEADCODE DAW 28/03/99 	else
//DEADCODE DAW 28/03/99 	if ((UWord) RealTime != (UWord) lasttime )
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 //The following line forces continuous mouse redraw
//DEADCODE DAW 28/03/99 //DeadCode RDH 21Oct96 		;;;														//JIM 20Oct96
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 	{
//DEADCODE DAW 28/03/99 //DeadCode RDH 21Oct96 	(*(char*)0xB0000)++;
//DEADCODE DAW 28/03/99 		lasttime=(UWord) RealTime;
//DEADCODE DAW 28/03/99 		SWord	xy[2];
//DEADCODE DAW 28/03/99 		AxisUsesField	auf;
//DEADCODE DAW 28/03/99 						auf|=AU_UI_X;
//DEADCODE DAW 28/03/99 						auf|=AU_UI_Y;
//DEADCODE DAW 28/03/99 	 	_Analogue.ReadPosition(auf,xy);
//DEADCODE DAW 28/03/99 		int	mousex=mousepos.x;
//DEADCODE DAW 28/03/99 		int	mousey=mousepos.y;
//DEADCODE DAW 28/03/99 		if (xy[0]!=-0x8000)
//DEADCODE DAW 28/03/99 		{
//DEADCODE DAW 28/03/99 			mousex+=xy[0];
//DEADCODE DAW 28/03/99 			mousey+=xy[1];
//DEADCODE DAW 28/03/99 		}
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 // Clip the mouse so it doesn't wrap
//DEADCODE DAW 28/03/99 		//modified so that UI can control mouse draw region
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 		if (mousex < Whole_Screen->VirtualMinX)
//DEADCODE DAW 28/03/99 			mousex = Whole_Screen->VirtualMinX;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 		if (mousex > Whole_Screen->VirtualMinX+Whole_Screen->VirtualWidth-1)
//DEADCODE DAW 28/03/99 			mousex = Whole_Screen->VirtualMinX+Whole_Screen->VirtualWidth-1;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 		if (mousey < Whole_Screen->VirtualMinY)
//DEADCODE DAW 28/03/99 			mousey = Whole_Screen->VirtualMinY;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 		if (mousey > Whole_Screen->VirtualMinY+Whole_Screen->VirtualHeight-1)
//DEADCODE DAW 28/03/99 			mousey = Whole_Screen->VirtualMinY+Whole_Screen->VirtualHeight-1;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 		mousepos.x=mousex;
//DEADCODE DAW 28/03/99 		mousepos.y=mousey;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 		if (x != mousepos.x ||	y != mousepos.y || lastmouse!=mouseshape)
//DEADCODE DAW 28/03/99 		{
//DEADCODE DAW 28/03/99 			x = mousepos.x;
//DEADCODE DAW 28/03/99 			y = mousepos.y;
//DEADCODE DAW 28/03/99 			lastmouse=mouseshape;
//DEADCODE DAW 28/03/99 			Whole_Screen->PhysMouseMove(x,y,lastmouse);
//DEADCODE DAW 28/03/99 		}
//DEADCODE DAW 28/03/99 }	}
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 
