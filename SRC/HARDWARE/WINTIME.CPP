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

//DeadCode RDH 27Oct96 
//DeadCode RDH 27Oct96 THIS IS IDENTICAL TO DOSTINE AND A MAINTAINANCE NIGHTMARE!
//DeadCode RDH 27Oct96 
//DeadCode RDH 27Oct96 //------------------------------------------------------------------------------
//DeadCode RDH 27Oct96 //Filename       WinTime.cpp
//DeadCode RDH 27Oct96 //System         
//DeadCode RDH 27Oct96 //Author         Andrew McRae
//DeadCode RDH 27Oct96 //Date           Mon 1 Jul 1996
//DeadCode RDH 27Oct96 //Description    
//DeadCode RDH 27Oct96 //------------------------------------------------------------------------------
//DeadCode RDH 27Oct96 
//DeadCode RDH 27Oct96 #include	<stdio.h>
//DeadCode RDH 27Oct96 #include	<stdlib.h>
//DeadCode RDH 27Oct96 
//DeadCode RDH 27Oct96 #include	"DOSDefs.h"
//DeadCode RDH 27Oct96 #include	"time.h"
//DeadCode RDH 27Oct96 #include	"display.h"											//ARM 17Sep96
//DeadCode RDH 27Oct96 
//DeadCode RDH 27Oct96 volatile UWord	TimerCode::TestLoopTime()
//DeadCode RDH 27Oct96 {
//DeadCode RDH 27Oct96 	ULong	current_tus,
//DeadCode RDH 27Oct96 			time_diff;
//DeadCode RDH 27Oct96 
//DeadCode RDH 27Oct96 	current_tus = tus;
//DeadCode RDH 27Oct96 			
//DeadCode RDH 27Oct96 //DeadCode JIM 03Jun96 			if(current_tus<last_tus)
//DeadCode RDH 27Oct96 //DeadCode JIM 03Jun96 			{
//DeadCode RDH 27Oct96 //DeadCode JIM 03Jun96 				//handle wrapping of loop time
//DeadCode RDH 27Oct96 //DeadCode JIM 03Jun96 
//DeadCode RDH 27Oct96 //DeadCode JIM 03Jun96 				time_diff = current_tus - last_tus + 0x0FFFFFFFF;
//DeadCode RDH 27Oct96 //DeadCode JIM 03Jun96 			}
//DeadCode RDH 27Oct96 //DeadCode JIM 03Jun96 			else
//DeadCode RDH 27Oct96 
//DeadCode RDH 27Oct96 	time_diff = current_tus - last_tus;
//DeadCode RDH 27Oct96 	time_diff = (time_diff * 100)/FREQ;
//DeadCode RDH 27Oct96 	return(time_diff);
//DeadCode RDH 27Oct96 
//DeadCode RDH 27Oct96 }
//DeadCode RDH 27Oct96 
//DeadCode RDH 27Oct96 Bool	TimerCode::TestMsgTime()
//DeadCode RDH 27Oct96 {
//DeadCode RDH 27Oct96 	int	currframetime=TestLoopTime();
//DeadCode RDH 27Oct96 	if (currframetime<nextmsgframetime)
//DeadCode RDH 27Oct96 		return(FALSE);
//DeadCode RDH 27Oct96 	elser
//DeadCode RDH 27Oct96 	{
//DeadCode RDH 27Oct96 		nextmsgframetime+=4;
//DeadCode RDH 27Oct96 		return(TRUE);
//DeadCode RDH 27Oct96 	}
//DeadCode RDH 27Oct96 
//DeadCode RDH 27Oct96 }
//DeadCode RDH 27Oct96 
//DeadCode RDH 27Oct96 		
//DeadCode RDH 27Oct96 Bool	TimerCode::GetLoopTime()
//DeadCode RDH 27Oct96 {
//DeadCode RDH 27Oct96 
//DeadCode RDH 27Oct96 	ULong	current_tus,
//DeadCode RDH 27Oct96 			time_diff,
//DeadCode RDH 27Oct96 			time_shift;
//DeadCode RDH 27Oct96 
//DeadCode RDH 27Oct96 	framenum++;
//DeadCode RDH 27Oct96 
//DeadCode RDH 27Oct96 	current_tus = tus;
//DeadCode RDH 27Oct96 			
//DeadCode RDH 27Oct96 //DeadCode JIM 03Jun96 			if(current_tus<last_tus)
//DeadCode RDH 27Oct96 //DeadCode JIM 03Jun96 			{
//DeadCode RDH 27Oct96 //DeadCode JIM 03Jun96 				//handle wrapping of loop time
//DeadCode RDH 27Oct96 //DeadCode JIM 03Jun96 
//DeadCode RDH 27Oct96 //DeadCode JIM 03Jun96 				time_diff = current_tus - last_tus + 0x0FFFFFFFF;
//DeadCode RDH 27Oct96 //DeadCode JIM 03Jun96 			}
//DeadCode RDH 27Oct96 //DeadCode JIM 03Jun96 			else
//DeadCode RDH 27Oct96 
//DeadCode RDH 27Oct96 	time_diff = current_tus - last_tus;
//DeadCode RDH 27Oct96 
//DeadCode RDH 27Oct96 
//DeadCode RDH 27Oct96 	//time_diff value depends on TIMER_FREQ and so
//DeadCode RDH 27Oct96 	//may not be in centiseconds
//DeadCode RDH 27Oct96 	//scale the value so that our frame time is
//DeadCode RDH 27Oct96 	//really in centiseconds
//DeadCode RDH 27Oct96 	//these two lines are equivalent to "*100, /FREQ", but the error
//DeadCode RDH 27Oct96 	//is estimatable
//DeadCode RDH 27Oct96 	time_shift = (100*65536)/FREQ;
//DeadCode RDH 27Oct96 	time_diff = (time_diff * time_shift)>>16;
//DeadCode RDH 27Oct96 
//DeadCode RDH 27Oct96 	if (accel)
//DeadCode RDH 27Oct96 	{
//DeadCode RDH 27Oct96 		if (accelaccum>=frametime)		//returned TRUE last frame...
//DeadCode RDH 27Oct96 		{
//DeadCode RDH 27Oct96 			nextmsgframetime=0;									//ARM 17Sep96
//DeadCode RDH 27Oct96 			realframetime=0;
//DeadCode RDH 27Oct96 			last_tus = last_tus+(time_diff<<16)/time_shift;
//DeadCode RDH 27Oct96 			accelaccum-=time_diff*accelrate;
//DeadCode RDH 27Oct96 		}
//DeadCode RDH 27Oct96 
//DeadCode RDH 27Oct96 		frametime=FRAMEMAX;
//DeadCode RDH 27Oct96 		accelaccum+=frametime;
//DeadCode RDH 27Oct96 		nextmsgframetime=-1;
//DeadCode RDH 27Oct96 
//DeadCode RDH 27Oct96 		if (time_diff>200)	//2 seconds max delay between frames
//DeadCode RDH 27Oct96 		{
//DeadCode RDH 27Oct96 			realframetime=time_diff;
//DeadCode RDH 27Oct96 			time_diff=200;
//DeadCode RDH 27Oct96 			accelaccum=0;
//DeadCode RDH 27Oct96 			return(FALSE);
//DeadCode RDH 27Oct96 		}
//DeadCode RDH 27Oct96 		else
//DeadCode RDH 27Oct96 		if (accelaccum>0)
//DeadCode RDH 27Oct96 		{
//DeadCode RDH 27Oct96 			realframetime=time_diff;
//DeadCode RDH 27Oct96 			return(FALSE);
//DeadCode RDH 27Oct96 		}
//DeadCode RDH 27Oct96 //DeadCode JIM 18Jun96 				realframetime=0;
//DeadCode RDH 27Oct96 		return(TRUE);
//DeadCode RDH 27Oct96 	}
//DeadCode RDH 27Oct96 	else
//DeadCode RDH 27Oct96 	if (paused)
//DeadCode RDH 27Oct96 	{
//DeadCode RDH 27Oct96 		frametime=0;
//DeadCode RDH 27Oct96 		realframetime=(UWord) time_diff;
//DeadCode RDH 27Oct96 		last_tus = last_tus+(time_diff<<16)/time_shift;	//PD 26Jun96
//DeadCode RDH 27Oct96 	}
//DeadCode RDH 27Oct96 	else
//DeadCode RDH 27Oct96 	{
//DeadCode RDH 27Oct96 		last_tus = last_tus+(time_diff<<16)/time_shift;
//DeadCode RDH 27Oct96 		realframetime=(UWord) time_diff;
//DeadCode RDH 27Oct96 		if (realframetime<FRAMEMIN)
//DeadCode RDH 27Oct96 		{	//we could change this to a test for VBL so there is no minimum frametime
//DeadCode RDH 27Oct96 			//in fact, this should never happen as there is a delay loop in screenswap
//DeadCode RDH 27Oct96 			//this is why screenswap is before getframetime!
//DeadCode RDH 27Oct96 //TempCode JIM 17Jun96 					while	 (realframetime+TestLoopTime()<FRAMEMIN)	/*wait*/;
//DeadCode RDH 27Oct96 //DeadCode JIM 18Jun96 					time_diff = current_tus - last_tus;
//DeadCode RDH 27Oct96 //DeadCode JIM 18Jun96 					//time_diff value depends on TIMER_FREQ and so
//DeadCode RDH 27Oct96 //DeadCode JIM 18Jun96 					//may not be in centiseconds
//DeadCode RDH 27Oct96 //DeadCode JIM 18Jun96 					//scale the value so that our frame time is
//DeadCode RDH 27Oct96 //DeadCode JIM 18Jun96 					//really in centiseconds
//DeadCode RDH 27Oct96 //DeadCode JIM 18Jun96 
//DeadCode RDH 27Oct96 //DeadCode JIM 18Jun96 					time_shift = (100*65536)/FREQ;
//DeadCode RDH 27Oct96 //DeadCode JIM 18Jun96 					time_diff = (time_diff * time_shift)>>16;
//DeadCode RDH 27Oct96 //DeadCode JIM 18Jun96 					//these two lines are equivalent to "*100, /FREQ", but the error
//DeadCode RDH 27Oct96 //DeadCode JIM 18Jun96 					//is estimatable
//DeadCode RDH 27Oct96 //DeadCode JIM 18Jun96 					realframetime+=(UWord) time_diff;
//DeadCode RDH 27Oct96 //DeadCode JIM 18Jun96 					last_tus = last_tus+(time_diff<<16)/time_shift;
//DeadCode RDH 27Oct96 //DeadCode JIM 18Jun96 			    	//the old code waited here
//DeadCode RDH 27Oct96 //DeadCode JIM 18Jun96 					frametime=realframetime;
//DeadCode RDH 27Oct96 
//DeadCode RDH 27Oct96 		}
//DeadCode RDH 27Oct96 
//DeadCode RDH 27Oct96 		if (realframetime>FRAMESILLY)
//DeadCode RDH 27Oct96 		{
//DeadCode RDH 27Oct96 			//new wrinkle.. if the time is silly don't put max in
//DeadCode RDH 27Oct96 			//as this will cause a big display stepping
//DeadCode RDH 27Oct96 			last_tus=tus;
//DeadCode RDH 27Oct96 			frametime=FRAMENORM;
//DeadCode RDH 27Oct96 			nextmsgframetime=0;									//ARM 17Sep96
//DeadCode RDH 27Oct96 		}
//DeadCode RDH 27Oct96 		else
//DeadCode RDH 27Oct96 		if (realframetime>FRAMEMAX)
//DeadCode RDH 27Oct96 		{
//DeadCode RDH 27Oct96 			//the old code played with the current_csecs
//DeadCode RDH 27Oct96 			//so that any residues were forgotten
//DeadCode RDH 27Oct96 			last_tus=tus;
//DeadCode RDH 27Oct96 			frametime=FRAMEMAX;
//DeadCode RDH 27Oct96 		}
//DeadCode RDH 27Oct96 		else
//DeadCode RDH 27Oct96 		{
//DeadCode RDH 27Oct96 			frametime=realframetime;
//DeadCode RDH 27Oct96 		}
//DeadCode RDH 27Oct96 		if (nextmsgframetime>0)
//DeadCode RDH 27Oct96 			nextmsgframetime-=frametime;
//DeadCode RDH 27Oct96 	}
//DeadCode RDH 27Oct96 
//DeadCode RDH 27Oct96 	return(AccelSkip());
//DeadCode RDH 27Oct96 };
//DeadCode RDH 27Oct96 
//DeadCode RDH 27Oct96 
//DeadCode RDH 27Oct96 void	TimerCode::PauseToggle()
//DeadCode RDH 27Oct96 {
//DeadCode RDH 27Oct96 	paused = (paused)?FALSE:TRUE;
//DeadCode RDH 27Oct96 	accel=FALSE;
//DeadCode RDH 27Oct96 	accelaccum=0;
//DeadCode RDH 27Oct96 }
//DeadCode RDH 27Oct96 void	TimerCode::PauseToggle(Bool s)
//DeadCode RDH 27Oct96 {
//DeadCode RDH 27Oct96 	paused = s;
//DeadCode RDH 27Oct96 
//DeadCode RDH 27Oct96 	accel=FALSE;
//DeadCode RDH 27Oct96 	accelaccum=0;
//DeadCode RDH 27Oct96 }
//DeadCode RDH 27Oct96 
//DeadCode RDH 27Oct96 
//DeadCode RDH 27Oct96 void	TimerCode::AccelToggle()
//DeadCode RDH 27Oct96 {
//DeadCode RDH 27Oct96 		accel=accel?FALSE:TRUE;
//DeadCode RDH 27Oct96 	accelaccum=0;
//DeadCode RDH 27Oct96 }
//DeadCode RDH 27Oct96 
//DeadCode RDH 27Oct96 void	TimerCode::AccelToggle(Bool s)
//DeadCode RDH 27Oct96 {
//DeadCode RDH 27Oct96 	paused = FALSE;
//DeadCode RDH 27Oct96 		accel=s;
//DeadCode RDH 27Oct96 	accelaccum=0;
//DeadCode RDH 27Oct96 }
//DeadCode RDH 27Oct96 
//DeadCode RDH 27Oct96 
//DeadCode RDH 27Oct96 Bool	TimerCode::AccelSkip()
//DeadCode RDH 27Oct96 {	//returns true if accel should SKIP drawing.
//DeadCode RDH 27Oct96 	ULong	current_tus,
//DeadCode RDH 27Oct96 			time_diff,
//DeadCode RDH 27Oct96 			time_shift;
//DeadCode RDH 27Oct96 
//DeadCode RDH 27Oct96 	current_tus = tus;
//DeadCode RDH 27Oct96 	time_diff = current_tus - last_tus;
//DeadCode RDH 27Oct96 	time_shift = (100*65536)/FREQ;
//DeadCode RDH 27Oct96 	time_diff = (time_diff * time_shift)>>16;
//DeadCode RDH 27Oct96 			
//DeadCode RDH 27Oct96 	return((accelaccum<time_diff)?TRUE:FALSE);
//DeadCode RDH 27Oct96 }
//DeadCode RDH 27Oct96 
