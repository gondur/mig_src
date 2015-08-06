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
//Filename       hardgap.cpp
//System         
//Author         Jim Taylor
//Date           Mon 19 Feb 1996
//Description    
//------------------------------------------------------------------------------
#include	"Wrapper.h"

void	Display::XX_ResetGraphicsMode()
{
 	Display::XX_ResetGraphicsMode();
}

void	Display::XX_SetGraphicsMode()
{
 	Display::XX_SetGraphicsMode();
}
void	Display::XX_PalChange()
{
	Display::XX_PalChange();
}
Bool	Display::XX_CopyP2L(LogicalPtr	a,int b,int c)
{
	return (Display::XX_CopyP2L(a,b,c));
}

ULong	Display::XX_PlotPixelNoClip(UWord	x, UWord	y, ULong	thecol)
{
	return(XX_PlotPixelNoClip(x,y,thecol));
}

void	Display::XX_ScreenFlip()
{
 	Display::XX_ScreenFlip();

	STUB256();		//size of lib patch.
	STUB256();		//size of lib patch.
	STUB256();		//size of lib patch.
	STUB256();		//size of lib patch.

	STUB256();		//size of lib patch.
	STUB256();		//size of lib patch.
	STUB256();		//size of lib patch.
	STUB256();		//size of lib patch.

	STUB256();		//size of lib patch.
	STUB256();		//size of lib patch.
	STUB256();		//size of lib patch.
	STUB256();		//size of lib patch.

	STUB256();		//size of lib patch.
	STUB256();		//size of lib patch.
	STUB256();		//size of lib patch.
	STUB256();		//size of lib patch.

}

//DeadCode RJS 14Mar96 void	Display::XX_PhysMouseMove(MouseSave* oldpos,void* MouseShape,MouseSave* newpos)
//DeadCode RJS 14Mar96 {
//DeadCode RJS 14Mar96 	Display::XX_PhysMouseMove(oldpos,MouseShape,newpos);
//DeadCode RJS 14Mar96 	STUB256();		//size of lib patch.
//DeadCode RJS 14Mar96 	STUB256();		//size of lib patch.
//DeadCode RJS 14Mar96 	STUB256();		//size of lib patch.
//DeadCode RJS 14Mar96 	STUB256();		//size of lib patch.
//DeadCode RJS 14Mar96 	STUB256();		//size of lib patch.
//DeadCode RJS 14Mar96 }
	STUBENDSPACE(Display);

// DOS version stubs

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LockBackScreen
//Author		Andrew McRae
//Date			Tue 25 Jun 1996
//
//Description	Locks Direct Draw Back Surface & gets ptr to it
//
//Inputs		none
//
//Returns		none
//
//------------------------------------------------------------------------------
void	Display::LockBackScreen (Bool winmov)
{

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UnLockBackScreen
//Author		Andrew McRae
//Date			Tue 25 Jun 1996
//
//Description	Unlocks Direct Draw BAck Surface
//
//Inputs		None
//
//Returns		None
//
//------------------------------------------------------------------------------
void	Display::UnLockBackScreen ()
{
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LockBackScreen
//Author		Andy McMaster
//Date			Tue 6 May 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Display::LockBackScreen(Bool winmov,UByte low, UByte high)//AMM 06May97
{
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UnLockBackScreen
//Author		Andy McMaster
//Date			Tue 6 May 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Display::UnLockBackScreen(UByte low, UByte high)		//AMM 06May97
{
}

Bool	Display::HardPoly(LPPOLYTYPE){return (FALSE);}
UByte	Display::SetGlobalAlpha(UByte a){return a;}
void 	Display::ForceRender() {}
void	Display::FakeLand() {};									//PD 30Jul97
void	Display::XHair(Float ,Float ,Colour ) {};				//PD 20Jun97
void	Display::D3DLandPalette(SWord){};						//PD 09Jun97
void	Display::SetFadeValue(UByte){};							//PD 07Jun97
Bool	Display::EnableBackClip(Bool bFlag){return (bFlag);}	//PD 05Jun97

void	Display::SetFade(Colour,SLong) {};						//PD 05Jun97
void	Display::CheckForUpdate(SLong&,SLong&){}				//PD 03Jun97
UByte*	Display::NameNumberedDriver(SWord){return (NULL);}
SWord	Display::CountDrivers(){return (0);}					//PD 27May97
Bool	Display::HardLine(LPLINETYPE){return (FALSE);}
Bool	Display::HardPoint(LPPOINTTYPE){return (FALSE);}
Bool	Display::HardPlainRectFill(Window*,SWord,SWord,SWord,SWord){return (FALSE);}
//Old_Code PD 22May97 Bool	Display::HardPlainRectFill(SWord,SWord,SWord,SWord){return (FALSE);}
Bool	Display::SetZUpdate(Bool flag){return (flag);}
Bool	Display::SetPlayerTextures(Bool flag){return (flag);}
Bool	Display::Hardware3D(){return (FALSE);}
Bool	Display::SetMatrices(SLong,ANGLES){return (FALSE);}

Bool	Display::ModeSupported(ScreenRez*) {return (TRUE);}		//PD 29May97
Bool	Display::DriverIsCapable(SWord) {return (FALSE);}		//PD 29May97

void	Display::InitLand(){}
//Old_Code PD 22May97 void	Display::InitLand(class item*){}
void	Display::UpdateLand(class item*){}
//Old_Code PD 22May97 void	Display::UpdateLand(class item*){}
void 	Display::LandPoly(ULong ,ULong ,ULong ,landvertexptr){}
void 	Display::SetImageMapTablePtr(SLong*){}
void 	Display::SetFog(Colour,SLong,SLong){}
void 	Display::SetLightVector(Float,Float,Float){}
void	Display::BeginScene(){}
void	Display::EndScene(){}
void 	Display::HCls(Bool ){}									//PD 10Jun97
void 	Display::SetViewParams(Window*){}
void	Display::SetMapShifts(UByte,UByte,UByte,UByte,UByte,UByte){}
