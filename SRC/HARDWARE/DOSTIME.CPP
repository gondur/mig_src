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

//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 //------------------------------------------------------------------------------
//DEADCODE DAW 28/03/99 //Filename       DosTime.cpp
//DEADCODE DAW 28/03/99 //System         
//DEADCODE DAW 28/03/99 //Author         Andrew McRae
//DEADCODE DAW 28/03/99 //Date           Mon 1 Jul 1996
//DEADCODE DAW 28/03/99 //Description    
//DEADCODE DAW 28/03/99 //------------------------------------------------------------------------------
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 #include	<stdio.h>
//DEADCODE DAW 28/03/99 #include	<stdlib.h>
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 #include	"DOSDefs.h"
//DEADCODE DAW 28/03/99 #include	"myangles.h"
//DEADCODE DAW 28/03/99 #include	"Mytime.h"
//DEADCODE DAW 28/03/99 #include	"display.h"											//ARM 17Sep96
//DEADCODE DAW 28/03/99 #include	"missman2.h"											//ARM 17Sep96
//DEADCODE DAW 28/03/99 #include	"mymath.h"											//ARM 17Sep96
//DEADCODE DAW 28/03/99 #include	"ranges.h"											//ARM 17Sep96
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 volatile UWord	TimerCode::TestLoopTime()
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 	ULong	current_tus,
//DEADCODE DAW 28/03/99 			time_diff;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 	current_tus = tus;
//DEADCODE DAW 28/03/99 			
//DEADCODE DAW 28/03/99 //DeadCode JIM 03Jun96 			if(current_tus<last_tus)
//DEADCODE DAW 28/03/99 //DeadCode JIM 03Jun96 			{
//DEADCODE DAW 28/03/99 //DeadCode JIM 03Jun96 				//handle wrapping of loop time
//DEADCODE DAW 28/03/99 //DeadCode JIM 03Jun96 
//DEADCODE DAW 28/03/99 //DeadCode JIM 03Jun96 				time_diff = current_tus - last_tus + 0x0FFFFFFFF;
//DEADCODE DAW 28/03/99 //DeadCode JIM 03Jun96 			}
//DEADCODE DAW 28/03/99 //DeadCode JIM 03Jun96 			else
//DEADCODE DAW 28/03/99 	time_diff = current_tus - last_tus;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 	#ifdef	PROFILE_ON
//DEADCODE DAW 28/03/99 		time_diff = time_diff / (((FREQ/100)<<8)>>8);
//DEADCODE DAW 28/03/99 	#else
//DEADCODE DAW 28/03/99 		time_diff = time_diff * ((100/FREQ)<<8)>>8;
//DEADCODE DAW 28/03/99 	#endif
//DEADCODE DAW 28/03/99 	return(time_diff);
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 Bool	TimerCode::TestMsgTime()
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 	int	currframetime=TestLoopTime();
//DEADCODE DAW 28/03/99 	if (currframetime<nextmsgframetime)
//DEADCODE DAW 28/03/99 		return(FALSE);
//DEADCODE DAW 28/03/99 	elser
//DEADCODE DAW 28/03/99 	{
//DEADCODE DAW 28/03/99 		nextmsgframetime+=Timer_Code.FIXEDFRAMETIME; // was just 4
//DEADCODE DAW 28/03/99 		msgcounttime+=Timer_Code.FIXEDFRAMETIME;
//DEADCODE DAW 28/03/99 //TempCode PD 12Nov96 		if (currframetime>=nextmsgframetime)
//DEADCODE DAW 28/03/99 //TempCode PD 12Nov96 			INT3();
//DEADCODE DAW 28/03/99 //TempCode DAW 16Oct96 			*(char*)0xb0000+=1;
//DEADCODE DAW 28/03/99 		return(TRUE);
//DEADCODE DAW 28/03/99 	}
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 		
//DEADCODE DAW 28/03/99 Bool	TimerCode::GetLoopTime()
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 	ULong	current_tus,
//DEADCODE DAW 28/03/99 			time_diff,
//DEADCODE DAW 28/03/99 			time_shift;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 	framenum++;
//DEADCODE DAW 28/03/99 //used for debugging: framecount print out
//DEADCODE DAW 28/03/99 //TempCode RDH 14Nov96 	Quit3DTimer='0'+(Timer_Code.framenum & 7);
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 	current_tus = tus;
//DEADCODE DAW 28/03/99 			
//DEADCODE DAW 28/03/99 //DeadCode JIM 03Jun96 			if(current_tus<last_tus)
//DEADCODE DAW 28/03/99 //DeadCode JIM 03Jun96 			{
//DEADCODE DAW 28/03/99 //DeadCode JIM 03Jun96 				//handle wrapping of loop time
//DEADCODE DAW 28/03/99 //DeadCode JIM 03Jun96 
//DEADCODE DAW 28/03/99 //DeadCode JIM 03Jun96 				time_diff = current_tus - last_tus + 0x0FFFFFFFF;
//DEADCODE DAW 28/03/99 //DeadCode JIM 03Jun96 			}
//DEADCODE DAW 28/03/99 //DeadCode JIM 03Jun96 			else
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 	time_diff = current_tus - last_tus;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 	//time_diff value depends on TIMER_FREQ and so
//DEADCODE DAW 28/03/99 	//may not be in centiseconds
//DEADCODE DAW 28/03/99 	//scale the value so that our frame time is
//DEADCODE DAW 28/03/99 	//really in centiseconds
//DEADCODE DAW 28/03/99 	//these two lines are equivalent to "*100, /FREQ", but the error
//DEADCODE DAW 28/03/99 	//is estimatable
//DEADCODE DAW 28/03/99 	time_shift = (100*65536)/FREQ;
//DEADCODE DAW 28/03/99 	time_diff = (time_diff * time_shift)>>16;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 	if (accel)
//DEADCODE DAW 28/03/99 	{
//DEADCODE DAW 28/03/99 		static here;
//DEADCODE DAW 28/03/99 //DeadCode DAW 06Nov96 		char*s=(char*)0xB0000;
//DEADCODE DAW 28/03/99 //DeadCode DAW 06Nov96 		int	d2=-accelaccum;
//DEADCODE DAW 28/03/99 //DeadCode DAW 06Nov96 		char d;
//DEADCODE DAW 28/03/99 //DeadCode DAW 06Nov96 		d=d2%10;
//DEADCODE DAW 28/03/99 //DeadCode DAW 06Nov96 		s[10]=d+'0';
//DEADCODE DAW 28/03/99 //DeadCode DAW 06Nov96 		d2/=10;
//DEADCODE DAW 28/03/99 //DeadCode DAW 06Nov96 		d=d2%10;
//DEADCODE DAW 28/03/99 //DeadCode DAW 06Nov96 		s[8]=d+'0';
//DEADCODE DAW 28/03/99 //DeadCode DAW 06Nov96 		d2/=10;
//DEADCODE DAW 28/03/99 //DeadCode DAW 06Nov96 		d=d2%10;
//DEADCODE DAW 28/03/99 //DeadCode DAW 06Nov96 		s[6]=d+'0';
//DEADCODE DAW 28/03/99 //DeadCode DAW 06Nov96 		d2/=10;
//DEADCODE DAW 28/03/99 //DeadCode DAW 06Nov96 		d=d2%10;
//DEADCODE DAW 28/03/99 //DeadCode DAW 06Nov96 		s[4]=d+'0';
//DEADCODE DAW 28/03/99 //DeadCode DAW 06Nov96 		d2/=10;
//DEADCODE DAW 28/03/99 //DeadCode DAW 06Nov96 		d=d2%10;
//DEADCODE DAW 28/03/99 //DeadCode DAW 06Nov96 		s[2]=d+'0';
//DEADCODE DAW 28/03/99 //DeadCode DAW 06Nov96 		d2/=10;
//DEADCODE DAW 28/03/99 //DeadCode DAW 06Nov96 		d=d2%10;
//DEADCODE DAW 28/03/99 //DeadCode DAW 06Nov96 		s[0]=d+'0';
//DEADCODE DAW 28/03/99 //DeadCode DAW 06Nov96 		d2=time_diff*accelrate;
//DEADCODE DAW 28/03/99 //DeadCode DAW 06Nov96 		s+=160;
//DEADCODE DAW 28/03/99 //DeadCode DAW 06Nov96 		d=d2%10;
//DEADCODE DAW 28/03/99 //DeadCode DAW 06Nov96 		s[10]=d+'0';
//DEADCODE DAW 28/03/99 //DeadCode DAW 06Nov96 		d2/=10;
//DEADCODE DAW 28/03/99 //DeadCode DAW 06Nov96 		d=d2%10;
//DEADCODE DAW 28/03/99 //DeadCode DAW 06Nov96 		s[8]=d+'0';
//DEADCODE DAW 28/03/99 //DeadCode DAW 06Nov96 		d2/=10;
//DEADCODE DAW 28/03/99 //DeadCode DAW 06Nov96 		d=d2%10;
//DEADCODE DAW 28/03/99 //DeadCode DAW 06Nov96 		s[6]=d+'0';
//DEADCODE DAW 28/03/99 //DeadCode DAW 06Nov96 		d2/=10;
//DEADCODE DAW 28/03/99 //DeadCode DAW 06Nov96 		d=d2%10;
//DEADCODE DAW 28/03/99 //DeadCode DAW 06Nov96 		s[4]=d+'0';
//DEADCODE DAW 28/03/99 //DeadCode DAW 06Nov96 		d2/=10;
//DEADCODE DAW 28/03/99 //DeadCode DAW 06Nov96 		d=d2%10;
//DEADCODE DAW 28/03/99 //DeadCode DAW 06Nov96 		s[2]=d+'0';
//DEADCODE DAW 28/03/99 //DeadCode DAW 06Nov96 		d2/=10;
//DEADCODE DAW 28/03/99 //DeadCode DAW 06Nov96 		d=d2%10;
//DEADCODE DAW 28/03/99 //DeadCode DAW 06Nov96 		s[0]=d+'0';
//DEADCODE DAW 28/03/99 //DeadCode DAW 06Nov96 		s[here]++;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 		frametime=FIXEDFRAMETIME;
//DEADCODE DAW 28/03/99 		realtime+=frametime;									//JIM 02Sep96
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 		if (accelaccum>=0)		//returned TRUE last frame...
//DEADCODE DAW 28/03/99 		{
//DEADCODE DAW 28/03/99 			here=160;
//DEADCODE DAW 28/03/99 			realframetime=0;
//DEADCODE DAW 28/03/99 			last_tus = last_tus+(time_diff<<16)/time_shift;
//DEADCODE DAW 28/03/99 			accelaccum-=time_diff*accelrate;
//DEADCODE DAW 28/03/99 		}
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 		here++;
//DEADCODE DAW 28/03/99 		here++;
//DEADCODE DAW 28/03/99 		accelaccum+=frametime;
//DEADCODE DAW 28/03/99 		nextmsgframetime=-1;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 		if (time_diff>100)	//2 seconds max delay between frames
//DEADCODE DAW 28/03/99 		{
//DEADCODE DAW 28/03/99 			realframetime=time_diff;
//DEADCODE DAW 28/03/99 			time_diff=0;
//DEADCODE DAW 28/03/99 			last_tus=current_tus;
//DEADCODE DAW 28/03/99 			accelaccum=0;
//DEADCODE DAW 28/03/99 			return(FALSE);
//DEADCODE DAW 28/03/99 		}
//DEADCODE DAW 28/03/99 		else
//DEADCODE DAW 28/03/99 		if (accelaccum>=0)										//RDH 14Oct96
//DEADCODE DAW 28/03/99 		{
//DEADCODE DAW 28/03/99 			realframetime=time_diff;
//DEADCODE DAW 28/03/99 			return(FALSE);
//DEADCODE DAW 28/03/99 		}
//DEADCODE DAW 28/03/99 //DeadCode JIM 18Jun96 				realframetime=0;
//DEADCODE DAW 28/03/99 		return(TRUE);
//DEADCODE DAW 28/03/99 	}
//DEADCODE DAW 28/03/99 	else
//DEADCODE DAW 28/03/99 	if (paused)
//DEADCODE DAW 28/03/99 	{
//DEADCODE DAW 28/03/99 		frametime=0;
//DEADCODE DAW 28/03/99 		realframetime=(UWord) time_diff;
//DEADCODE DAW 28/03/99 		last_tus = last_tus+(time_diff<<16)/time_shift;	//PD 26Jun96
//DEADCODE DAW 28/03/99 			return(FALSE);
//DEADCODE DAW 28/03/99 	}
//DEADCODE DAW 28/03/99 	else
//DEADCODE DAW 28/03/99 	{
//DEADCODE DAW 28/03/99 		last_tus = last_tus+(time_diff<<16)/time_shift;
//DEADCODE DAW 28/03/99 		realframetime=(UWord) time_diff;
//DEADCODE DAW 28/03/99 		if (realframetime<FRAMEMIN)
//DEADCODE DAW 28/03/99 		{	//we could change this to a test for VBL so there is no minimum frametime
//DEADCODE DAW 28/03/99 			//in fact, this should never happen as there is a delay loop in screenswap
//DEADCODE DAW 28/03/99 			//this is why screenswap is before getframetime!
//DEADCODE DAW 28/03/99 //TempCode JIM 17Jun96 					while	 (realframetime+TestLoopTime()<FRAMEMIN)	/*wait*/;
//DEADCODE DAW 28/03/99 //DeadCode JIM 18Jun96 					time_diff = current_tus - last_tus;
//DEADCODE DAW 28/03/99 //DeadCode JIM 18Jun96 					//time_diff value depends on TIMER_FREQ and so
//DEADCODE DAW 28/03/99 //DeadCode JIM 18Jun96 					//may not be in centiseconds
//DEADCODE DAW 28/03/99 //DeadCode JIM 18Jun96 					//scale the value so that our frame time is
//DEADCODE DAW 28/03/99 //DeadCode JIM 18Jun96 					//really in centiseconds
//DEADCODE DAW 28/03/99 //DeadCode JIM 18Jun96 
//DEADCODE DAW 28/03/99 //DeadCode JIM 18Jun96 					time_shift = (100*65536)/FREQ;
//DEADCODE DAW 28/03/99 //DeadCode JIM 18Jun96 					time_diff = (time_diff * time_shift)>>16;
//DEADCODE DAW 28/03/99 //DeadCode JIM 18Jun96 					//these two lines are equivalent to "*100, /FREQ", but the error
//DEADCODE DAW 28/03/99 //DeadCode JIM 18Jun96 					//is estimatable
//DEADCODE DAW 28/03/99 //DeadCode JIM 18Jun96 					realframetime+=(UWord) time_diff;
//DEADCODE DAW 28/03/99 //DeadCode JIM 18Jun96 					last_tus = last_tus+(time_diff<<16)/time_shift;
//DEADCODE DAW 28/03/99 //DeadCode JIM 18Jun96 			    	//the old code waited here
//DEADCODE DAW 28/03/99 //DeadCode JIM 18Jun96 					frametime=realframetime;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 		}
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 		if (realframetime>FRAMESILLY)
//DEADCODE DAW 28/03/99 		{
//DEADCODE DAW 28/03/99 			//new wrinkle.. if the time is silly don't put max in
//DEADCODE DAW 28/03/99 			//as this will cause a big display stepping
//DEADCODE DAW 28/03/99 			last_tus=tus;
//DEADCODE DAW 28/03/99 			frametime=FRAMENORM;
//DEADCODE DAW 28/03/99 			nextmsgframetime=0;
//DEADCODE DAW 28/03/99 		}
//DEADCODE DAW 28/03/99 		else
//DEADCODE DAW 28/03/99 		if (realframetime>FRAMEMAX)
//DEADCODE DAW 28/03/99 		{
//DEADCODE DAW 28/03/99 			//the old code played with the current_csecs
//DEADCODE DAW 28/03/99 			//so that any residues were forgotten
//DEADCODE DAW 28/03/99 			last_tus=tus;
//DEADCODE DAW 28/03/99 			frametime=FRAMEMAX;
//DEADCODE DAW 28/03/99 			nextmsgframetime=0;
//DEADCODE DAW 28/03/99 		}
//DEADCODE DAW 28/03/99 		else
//DEADCODE DAW 28/03/99 		{
//DEADCODE DAW 28/03/99 			frametime=realframetime;
//DEADCODE DAW 28/03/99 		}
//DEADCODE DAW 28/03/99 		if (nextmsgframetime>0)
//DEADCODE DAW 28/03/99 			nextmsgframetime-=frametime;
//DEADCODE DAW 28/03/99 		realtime+=frametime;										//JIM 14Aug96
//DEADCODE DAW 28/03/99 		return(FALSE);
//DEADCODE DAW 28/03/99 	}
//DEADCODE DAW 28/03/99 };
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 void	TimerCode::PauseToggle()
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 	paused = (paused)?FALSE:TRUE;
//DEADCODE DAW 28/03/99 	accel=FALSE;
//DEADCODE DAW 28/03/99 	accelaccum=0;
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 void	TimerCode::PauseToggle(Bool s)
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 	paused = s;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 	accel=FALSE;
//DEADCODE DAW 28/03/99 	accelaccum=0;
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 void	TimerCode::AccelToggle()
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 		accel=accel?FALSE:TRUE;
//DEADCODE DAW 28/03/99 	accelaccum=0;
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 void	TimerCode::AccelToggle(Bool s)
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 	paused = FALSE;
//DEADCODE DAW 28/03/99 		accel=s;
//DEADCODE DAW 28/03/99 	accelaccum=0;
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 Bool	TimerCode::AccelSkip()
//DEADCODE DAW 28/03/99 {	//returns true if accel should SKIP drawing.
//DEADCODE DAW 28/03/99 	ULong	current_tus,
//DEADCODE DAW 28/03/99 			time_diff,
//DEADCODE DAW 28/03/99 			time_shift;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 	current_tus = tus;
//DEADCODE DAW 28/03/99 	time_diff = current_tus - last_tus;
//DEADCODE DAW 28/03/99 	time_shift = (100*65536)/FREQ;
//DEADCODE DAW 28/03/99 	time_diff = (time_diff * time_shift)>>16;
//DEADCODE DAW 28/03/99 			
//DEADCODE DAW 28/03/99 	return((accelaccum<time_diff)?TRUE:FALSE);
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE DAW 28/03/99 //Procedure		MakeSunPos
//DEADCODE DAW 28/03/99 //Author		Jim Taylor
//DEADCODE DAW 28/03/99 //Date			Wed 6 Nov 1996
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Description	Fills in all sun fields from current time
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Inputs		
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //Returns	
//DEADCODE DAW 28/03/99 //
//DEADCODE DAW 28/03/99 //------------------------------------------------------------------------------
//DEADCODE DAW 28/03/99 //DeadCode RJS 23Mar98 void	TimerCode::MakeSunPos()
//DEADCODE DAW 28/03/99 //DeadCode RJS 23Mar98 {
//DEADCODE DAW 28/03/99 //DeadCode RJS 23Mar98 	int	currtime=realtime/100;
//DEADCODE DAW 28/03/99 //DeadCode RJS 23Mar98 	SWord	sinang,cosang;
//DEADCODE DAW 28/03/99 //DeadCode RJS 23Mar98 	ANGLES sunang=(Angles)(((currtime-MMC.dawntime)<<15)/(MMC.dusktime-MMC.dawntime));
//DEADCODE DAW 28/03/99 //DeadCode RJS 23Mar98 
//DEADCODE DAW 28/03/99 //DeadCode RJS 23Mar98 	// Shit fix....												//RJS 14Jan98
//DEADCODE DAW 28/03/99 //DeadCode RJS 23Mar98 	sunang = ANGLES_60Deg;										//RJS 14Jan98
//DEADCODE DAW 28/03/99 //DeadCode RJS 23Mar98 
//DEADCODE DAW 28/03/99 //DeadCode RJS 23Mar98 	sunrot=sunang;
//DEADCODE DAW 28/03/99 //DeadCode RJS 23Mar98 	Math_Lib.high_sin_cos(sunang,sinang,cosang);
//DEADCODE DAW 28/03/99 //DeadCode RJS 23Mar98 	sunpos.Y=MULSHSIN(sinang,SUNELEVDIST,ANGLES_SHIFT);
//DEADCODE DAW 28/03/99 //DeadCode RJS 23Mar98 	sunpos.X=MULSHSIN(cosang,SUNELEVDIST,ANGLES_SHIFT);
//DEADCODE DAW 28/03/99 //DeadCode RJS 23Mar98 	sunpos.Z=-MMC.sunsouth;
//DEADCODE DAW 28/03/99 //DeadCode RJS 23Mar98 	SLong	range;
//DEADCODE DAW 28/03/99 //DeadCode RJS 23Mar98 	Math_Lib.Intercept(sunpos.X,sunpos.Y,sunpos.Z,range,sunhdg,sunpitch);
//DEADCODE DAW 28/03/99 //DeadCode RJS 23Mar98 }
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE DAW 28/03/99 //Procedure		TimeSinceLastMove
//DEADCODE DAW 28/03/99 //Author		Paul.   
//DEADCODE DAW 28/03/99 //Date			Tue 17 Nov 1998
//DEADCODE DAW 28/03/99 //------------------------------------------------------------------------------
//DEADCODE DAW 28/03/99 int	TimerCode::TimeSinceLastMove()
//DEADCODE DAW 28/03/99 {
//DEADCODE DAW 28/03/99 	if (paused)	return (0);
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 	ULong	last_time,
//DEADCODE DAW 28/03/99 			this_time,
//DEADCODE DAW 28/03/99 			time_diff;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 	this_time = TestLoopTime();
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 	last_time = ((nextmsgframetime-FIXEDFRAMETIME)*FREQ)/100;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 	time_diff = this_time - last_time;
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 	return (int)time_diff;
//DEADCODE DAW 28/03/99 }
//DEADCODE DAW 28/03/99 
//DEADCODE DAW 28/03/99 
