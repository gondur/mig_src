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
//Filename       analogue.cpp
//System         
//Author         Jim Taylor
//Date           Thu 14 Mar 1996
//Description    Top level analogue control code.
//				Actually, now this drives all analogue code
//				as using DirectInput...
//
#include	"dinput.h"		//CHECK THE DATES!!!!

#include	"sw_force.h"	//STILL USING SAME PROTOTYPES BUT LOCAL ROUTINES

////////////////////////////

Analogue	_Analogue;		//My class

 

Bool	Analogue::Initialise(int HWNDw,int HINSTANCEi)	//Doncha just hate handles?
{
	{for (int i=0;i<MAXFORCEAXES;i++)	   ForceAxes[i]=NULL;}

	HWND w=(HWND)HWNDw;
	HINSTANCE i=(HINSTANCE)HINSTANCEi;
	DIdev=Master_3d.g_lpDI;
	if (runtimedevices[0].devid.Data1==0)
	{	//if never manually configured set up default manual config (true=enable FF)
		//normal manual config has ff disabled.
		SController::BuildEnumerationTables();
		SController::GetAxisConfig(true);
		SController::SetAxisConfig();
	}
	FFdevice=NULL;
	DIPROPDWORD	buffprop={{sizeof(DIPROPDWORD),sizeof(DIPROPHEADER),0,DIPH_DEVICE},150};
	DIPROPDWORD	centreprop={{sizeof(DIPROPDWORD),sizeof(DIPROPHEADER),0,DIPH_DEVICE},};
	for (int devnum=0;runtimedevices[devnum].devid.Data1;devnum++)
	{	//Dirty... GUID.Data1==0=end of list. 1=defalut stick.
		GUID	devid=runtimedevices[devnum].devid;
		if (devid.Data1==1)
			GetFirstJoystick(devid);
		else
		if (devid.Data1==2)
			GetFirstMouse(devid);

		if (devid.Data1>2)
		{
			DIdev->CreateDevice(devid,&runtimedevices[devnum].dev,NULL);
			int hres = runtimedevices[devnum].dev->QueryInterface(IID_IDirectInputDevice2,(LPVOID *)&runtimedevices[devnum].dev2); 
			axiscount=0;hatcount=0;
			buttoncount=0;buttonbase=250+50*devnum;
			objectcount=0;
			if (!SUCCEEDED(hres))
			{
				runtimedevices[devnum].dev->EnumObjects(DIEnumDeviceObjectsProc,runtimedevices+devnum,DIDFT_BUTTON+DIDFT_AXIS+DIDFT_POV);
				runtimedevices[devnum].dev->SetProperty(DIPROP_BUFFERSIZE,&buffprop.diph);

				// DI_PROPNOEFFECT(0001) DIERR_INVALIDPARAM (57) 
				// DIERR_NOTINITIALIZED DIERR_OBJECTNOTFOUND(0002) DIERR_UNSUPPORTED(40001)
				
				DIDATAFORMAT dataform={sizeof(DIDATAFORMAT),sizeof(DIOBJECTDATAFORMAT),DIDF_ABSAXIS ,0x500,objectcount,dataobjects};
				runtimedevices[devnum].dev->SetDataFormat(&dataform);
	//			int hres = runtimedevices[devnum].dev->QueryInterface(IID_IDirectInputDevice2,(LPVOID *)&runtimedevices[devnum].dev2); 
				runtimedevices[devnum].dev2=NULL;
				runtimedevices[devnum].dev->SetCooperativeLevel(w,DISCL_BACKGROUND+DISCL_NONEXCLUSIVE);
				runtimedevices[devnum].dev->Acquire();
			}
			else
			{
				runtimedevices[devnum].dev->Release();
				runtimedevices[devnum].dev=NULL;
				runtimedevices[devnum].dev2->EnumObjects(DIEnumDeviceObjectsProc,runtimedevices+devnum,DIDFT_BUTTON+DIDFT_AXIS+DIDFT_POV);
				runtimedevices[devnum].dev2->SetProperty(DIPROP_BUFFERSIZE,&buffprop.diph);

				// DI_PROPNOEFFECT(0001) DIERR_INVALIDPARAM (57) 
				// DIERR_NOTINITIALIZED DIERR_OBJECTNOTFOUND(0002) DIERR_UNSUPPORTED(40001)
				
				DIDATAFORMAT dataform={sizeof(DIDATAFORMAT),sizeof(DIOBJECTDATAFORMAT),DIDF_ABSAXIS ,0x500,objectcount,dataobjects};
				runtimedevices[devnum].dev2->SetDataFormat(&dataform);
	//			int hres = runtimedevices[devnum].dev->QueryInterface(IID_IDirectInputDevice2,(LPVOID *)&runtimedevices[devnum].dev2); 
				if (runtimedevices[devnum].useff)
				{
 
//					runtimedevices[devnum].dev->SetProperty(DIPROP_AUTOCENTER,&centreprop.diph);
					FFdevice=runtimedevices[devnum].dev2;
					FFdevice->EnumEffects( DIEnumEffectsProc,NULL,DIEFT_ALL);  
					runtimedevices[devnum].dev2->SetCooperativeLevel(w,DISCL_BACKGROUND+DISCL_EXCLUSIVE);
				}
				else
					runtimedevices[devnum].dev2->SetCooperativeLevel(w,DISCL_BACKGROUND+DISCL_NONEXCLUSIVE);
				runtimedevices[devnum].dev2->Acquire();
				int i=4;
			}
		}
	}
	for (int a=0;a<AU_MAX;a++)
		axisvalues[a]=0x8000;
	if (FFdevice)
	{			 //DIGFFS_ACTUATORSOFF
		DWORD result;
		FFdevice-> GetForceFeedbackState(&result);
		SWFF_DestroyAllEffects(FFdevice);
		FFshake.Init(FFdevice);
		FFstiff.Init(FFdevice);
		FFpush.Init(FFdevice);
	}

	return TRUE;
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CloseDown
//Author		Jim Taylor
//Date			Thu 14 Mar 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	Analogue::CloseDown()
{
	for (int devnum=0;runtimedevices[devnum].devid.Data1;devnum++)
	{
		if (runtimedevices[devnum].dev2)
		{
			runtimedevices[devnum].dev2->Unacquire();
			runtimedevices[devnum].dev2->Release();
//			runtimedevices[devnum].dev->Release();
			runtimedevices[devnum].dev2=NULL;
			runtimedevices[devnum].dev=NULL;
		}
		else
		if (runtimedevices[devnum].dev)
		{
			runtimedevices[devnum].dev->Unacquire();
			runtimedevices[devnum].dev->Release();
			runtimedevices[devnum].dev=NULL;
		}
	}
	FFdevice=NULL;
//	if (DIdev)
//		DIdev->Release();
//	DIdev=NULL;
	return TRUE;
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ReadPosition
//Author		Jim Taylor
//Date			Thu 14 Mar 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//enum	{AX_FLAG_HATASBUTTON=0x200,AX_FLAG_HATASAXIS=0x400,AX_FLAG_AXIS=0x480,AX_FLAG_AXIS_IGNORE=0x4ff};

void	Analogue::PollForces()	//called @ 50Hz. Only allow 1 effect instruction at a time
{
	if (!FFdevice)
		return;
	FFpush.Tick();
	FFstiff.Tick();
	FFshake.Tick();
	switch	(lastFFeffect)
	{	//intensional fall through
	case 0:		if (FFpush.Poll())	{	lastFFeffect=1;	return;		}
	case 1:		if (FFstiff.Poll())	{	lastFFeffect=2;	return;		}
	case 2:		if (FFshake.Poll())	{	lastFFeffect=0;	return;		}
	case 3:	//really 0 again
				if (FFpush.Poll())	{	lastFFeffect=1;	return;		}
	case 4:	//really 1 again
				if (FFstiff.Poll())	{	lastFFeffect=2;	return;		}
	}
	
}

void	Analogue::PollPosition()
{
	DIDEVICEOBJECTDATA	readings[30];
	for (int devnum=0;runtimedevices[devnum].devid.Data1;devnum++)
	if (runtimedevices[devnum].dev || runtimedevices[devnum].dev2)
	{	// DI_BUFFEROVERFLOW
		//DIERR_INPUTLOST (1E) DIERR_INVALIDPARAM (57 ) DIERR_NOTACQUIRED (0c)
		//DIERR_NOTBUFFERED (07) DIERR_NOTINITIALIZED (15)
		ULong numelts=30;
		if (runtimedevices[devnum].dev2)
		{
			runtimedevices[devnum].dev2->Poll();
			runtimedevices[devnum].dev2->GetDeviceData(sizeof(DIDEVICEOBJECTDATA),readings,&numelts,0);
		}
		else
		{
			runtimedevices[devnum].dev->GetDeviceData(sizeof(DIDEVICEOBJECTDATA),readings,&numelts,0);
		}
		for (DIDEVICEOBJECTDATA* datum=readings;numelts--;datum++)
		{
			if (datum->dwOfs>=AX_FLAG_AXIS)
			{
				int theaxis=(datum->dwOfs-AX_FLAG_AXIS)>>2;
				if (theaxis<32)
					if (axisscales[theaxis])
					{
						if (axisbases[theaxis]==0x8000)
							axisbases[theaxis]=datum->dwData;
						int newval=(int(UWord(datum->dwData))-int(UWord(axisbases[theaxis])))/axisscales[theaxis];
						if (newval<-0x7fff)
							newval=0-0x7fff;
						if (newval>0x7fff)
							newval=0X7FFF;
						axisvalues[theaxis]=newval;
					}
					else
					{
						if (datum->dwData==0)
							axisvalues[theaxis]=-0x7fff;
						else
							axisvalues[theaxis]=datum->dwData-0x8000;
					}
//temp				Mono_Text.PrintHexAt(20,(datum->dwOfs-AX_FLAG_AXIS)>>2,datum->dwData,4);
			}
			else
			if (datum->dwOfs>=AX_FLAG_HATASAXIS)
			{
				int dx=0,dy=0;
				if ((datum->dwData&0xffff)!=0xffff)
				switch(datum->dwData/22500)
				{		//this code is not so good if we get proper analogue hats in the short term
				case 0:	case 15:
				case 16: case 17:   dx=0;dy=1;				break;
				case 1: case 2:		dx=1;dy=1;				break;
				case 3: case 4:		dx=1;dy=0;				break;
				case 5: case 6:		dx=1,dy=-1;				break;
				case 7: case 8:		dx=0;dy=-1;				break;
				case 9: case 10:	dx=-1;dy=-1;			break;
				case 11: case 12:	dx=-1;dy=0;				break;
				case 13: case 14:	dx=-1;dy=1;				break;
				}
				int axis=datum->dwOfs-AX_FLAG_HATASAXIS;
				int scale=_Analogue.axisscales[axis];
				if (datum->dwOfs-AX_FLAG_HATASAXIS==AU_UI_X)
				{

					if (axisvalues[axis]>scale-32767 && axisvalues[axis]<32767-scale)
						axisvalues[axis]+=dx*scale;
					if (axisvalues[axis+1]>scale-32767 && axisvalues[axis+1]<32767-scale)
						axisvalues[axis+1]+=dy*scale;
				}
				else
					if (dx==0 && dy==0)
					{
					   axisvalues[axis]=0;
					   axisvalues[axis+1]=0;
					}
					else
						if (	axisvalues[axis]*dy==axisvalues[axis+1]*dx
							&&	axisvalues[axis]*dx+axisvalues[axis+1]*dy>0
							)
						{
							if (axisvalues[axis]>scale-32767 && axisvalues[axis]<32767-scale)
								axisvalues[axis]+=dx*scale;
							if (axisvalues[axis+1]>scale-32767 && axisvalues[axis+1]<32767-scale)
								axisvalues[axis+1]+=dy*scale;
						}
						else
						{
							axisvalues[axis]=dx*scale;
							axisvalues[axis+1]=dy*scale;
						}
			}
			else
			if (datum->dwOfs>=AX_FLAG_HATASBUTTON)
			{
				int pressing;
				int base=datum->dwOfs-AX_FLAG_HATASBUTTON;
				if ((datum->dwData&0xffff)==0xffff)
					pressing=8;
				else
					pressing=(((datum->dwData/2250)+1)&14)>>1;

				for (int i=0;i<8;i++)
					if (i!=pressing)
						Inst3d::OnKeyUp(base+i);
					else
						Inst3d::OnKeyDown(base+i);
					
			}
			else
			{
				if (datum->dwData&0x80)
					Inst3d::OnKeyDown(datum->dwOfs);
				else
					Inst3d::OnKeyUp(datum->dwOfs);

			}
		}
	}
	PollForces();
}
SWord	Analogue::ReadPosition(AxisUses a)
{
  return axisvalues[a];
}

struct	Inf	{_GUID* g;int buts,hats,axes;bool foundone;};
static BOOL CALLBACK DIEnumDevicesProc(const DIDEVICEINSTANCE *ddi,LPVOID pvRef)
{
	Inf* inf=(Inf*) pvRef;
	inf->g[0]=ddi->guidInstance;
	inf->foundone=true;
	return	DIENUM_STOP;
}
bool	Analogue::GetFirstMouse(struct _GUID &uid,int *numbuts,int *numhats)
{
	Inf inf={&uid};
	DIdev->EnumDevices(DIDEVTYPE_MOUSE,DIEnumDevicesProc,&inf,DIEDFL_ATTACHEDONLY);
	return	inf.foundone;
}
bool	Analogue::GetFirstJoystick(struct _GUID &uid,int * axes,int *numbuts,int *numhats)
{
	Inf inf={&uid};
	DIdev->EnumDevices(DIDEVTYPE_JOYSTICK,DIEnumDevicesProc,&inf,DIEDFL_ATTACHEDONLY);
	return	inf.foundone;
}

//
// Push forces descriptions
//
//
void	FF_Push::Init(IDirectInputDevice2A* d)	
{
	triggerX=triggerZ=false;MX=MZ=0x8000;durationX=durationZ=0;
	dev=d;
	if (pForceX)  pForceX->Release();	pForceX=NULL;
	if (pForceY)  pForceY->Release();	pForceY=NULL;
//	Set(30000,30000,10);
//	Poll();
//	Poll();
//	Set(-30000,-30000,10);
//	Poll();
//	Poll();

}

bool	FF_Push::Set(SWord x,SWord z,int dur)
{
	if (x==MX && z==MZ && (ULong)(durationX-dur-5)<10 && (ULong)(durationZ-dur-5)<10)
		return false;
	MX=x;MZ=z;
	durationX=durationZ=dur;
	triggerX=triggerZ=true;
	return true;
}

bool	FF_Push::SetX(SWord x,int dur)
{
	if (x==MX && (ULong)(durationX-dur-5)<10)
		return false;
	MX=x;
	durationX=dur;
	triggerX=true;
	return true;
}

bool	FF_Push::SetZ(SWord z,int dur)
{
	if (z==MZ && (ULong)(durationZ-dur-5)<10)
		return false;
	MZ=z;
	durationZ=dur;
	triggerZ=true;
	return true;
}


bool	FF_Push::Poll()
{
	if (!(triggerX||triggerZ))	return false;
	if (durationX<0)
		MX=0;
	if (durationZ<0)
		MZ=0;
	if (triggerX)
	{
		if (pForceX)	pForceX->Release();
		SWFF_CreateRawAxisForceEffect(dev,&pForceX,MX/4,X_AXIS);
		triggerX=false;
		return true;
	}
//	if (triggerZ)	//must be!
//	{
		if (pForceY)	pForceY->Release();
		SWFF_CreateRawAxisForceEffect(dev,&pForceY,MZ/4,Y_AXIS);
		triggerZ=false;
		return true;
//	}
//	return false;	//not poss
}
bool	FF_Push::Tick()
{
	if (durationX==0)
		triggerX=true;
	if (durationZ==0)
		triggerZ=true;
	durationX--;
	durationZ--;
	return false;
}
//
// Stiffness and centrepoint descriptions
//
//
//
bool	FF_Stiff::Set(SWord cx,SWord cz,SWord sx,SWord sz)
{
	if (cx==CX && cz==CZ && sx==SX && sz==SZ)
		return false;
	CX=cx;CZ=cz;
	SX=sx;SZ=sz;
	trigger=true;
	return true;
}

bool	FF_Stiff::SetX(SWord cx,SWord sx)
{
	if (cx==CX && sx==SX)
		return false;
	CX=cx;
	SX=sx;
	trigger=true;
	return true;
}

bool	FF_Stiff::SetZ(SWord cz,SWord sz)
{
	if (cz==CZ && sz==SZ)
		return false;
	CZ=cz;
	SZ=sz;
	trigger=true;
	return true;
}

void	FF_Stiff::Init(IDirectInputDevice2A* d)	
{
	trigger=false;
	CX=CZ=SX=SZ=0x8000;
	dev=d;
	if (pStiffX)	pStiffX->Release();
	if (pStiffY)	pStiffY->Release();
	pStiffX=pStiffY=NULL;
	if (dev)
	{
		SWFF_CreateAxisCenter(dev,&pStiffX,0,0,X_AXIS);
		SWFF_CreateAxisCenter(dev,&pStiffY,0,0,Y_AXIS);
		SetX(25000,30000);
		Poll();
		SetZ(25000,30000);
		Poll();
	}
}
bool	FF_Stiff::Poll()
{
	if (!trigger)	return false;
	SWFF_ChangeAxisCenter(pStiffX,(SX)/3,CX/3);
	SWFF_ChangeAxisCenter(pStiffY,(SZ)/3,CZ/3);
	trigger=false;
	return true;
}
//
// Shakes descriptions
//
//
//
//
//

bool	FF_Shake::Set(SWord mx,SWord mz,SWord fx,SWord fz,bool rnd)
{
	if (MX==mx && MZ==mz && FX==fx && FZ==fz && randomX==rnd && randomZ==rnd)
		return false;
	MX=mx;MZ=mz;
	FX=fx;FZ=fz;
	randomX=randomZ=rnd;
	triggerX=triggerZ=true;
	return true;
}

bool	FF_Shake::SetX(SWord mx,SWord fx,bool rnd)
{
	if (MX==mx && FX==fx && randomX==rnd)
		return false;
	MX=mx;
	FX=fx;
	randomX==rnd;
	triggerX=true;
	return true;
}

bool	FF_Shake::SetZ(SWord mz,SWord fz,bool rnd)
{
	if (MZ==mz && FZ==fz && randomZ==rnd)
		return false;
	MZ=mz;
	FZ=fz;
	randomZ==rnd;
	triggerZ=true;
	return true;
}

void	FF_Shake::Init(IDirectInputDevice2A* d)	
{
	triggerX=triggerZ=randomX=randomZ=false;MX=MZ=FX=FZ=0x8000;dev=d;
	if (pShakeX)	pShakeX->Release();	pShakeX=NULL;
	if (pShakeY)	pShakeY->Release();	pShakeY=NULL;				  //JIM 03/03/99
	if (pRandX)		pRandX->Release();	pRandX=NULL;
	if (pRandY)		pRandY->Release();	pRandY=NULL;				  //JIM 03/03/99
	if (dev)
	{
		SWFF_CreateROMEffect(dev,&pRandX,GUID_RandomNoise,INFINITE,0,0,-1);
		SWFF_CreateROMEffect(dev,&pRandY,GUID_RandomNoise,INFINITE,0,9000,-1);
		SWFF_CreatePeriodicEffect(dev,&pShakeX,SQUARE_HIGH,INFINITE,0,0,0,0,0,0,0,0,-1);
		SWFF_CreatePeriodicEffect(dev,&pShakeY,SQUARE_HIGH,INFINITE,0,0,0,0,0,0,0,0,-1);
	}
	Set(30000,30000,20,20,false);
	Poll();
	Poll();
	Set(30000,30000,20,20,true);
	Poll();
	Poll();

}
bool	FF_Shake::Poll()
{
	if (!(triggerX || triggerZ))
		return false;
	if (triggerX)
	{
		if (randomX!=lastrandomX)
			if (lastrandomX)
				SWFF_SetGain(pRandX,0);
			else
				SWFF_SetPeriodic(pShakeX,0,0,0,0);
		if (randomX)
			SWFF_SetGain(pRandX,MX/3);
		else
			SWFF_SetPeriodic(pShakeX,MX/4,0,0,HZ_TO_uS(FX)); 
		triggerX=false;
		lastrandomX=randomX;
		return true;
	}
	//if (triggerZ)
	{
		if (randomZ!=lastrandomZ)
			if (lastrandomZ)
				SWFF_SetGain(pRandY,0);
			else
				SWFF_SetPeriodic(pShakeY,0,0,0,0);
		if (randomZ)
			SWFF_SetGain(pRandY,MZ/3);
		else
			SWFF_SetPeriodic(pShakeY,MZ/4,0,0,HZ_TO_uS(FZ)); 
		triggerZ=false;
		lastrandomZ=randomZ;
		return true;
	}
}

// Set Spring Constants function by DBM most of it stolen from CreateCondition
HRESULT SWFF_SetSpringConstants(
	IN LPDIRECTINPUTEFFECT pDIEffect,
	IN DWORD lXCoefficient,
	IN DWORD lXOffset,
	IN DWORD lYCoefficient,
	IN DWORD lYOffset)
{
//	if(pDIEffect == NULL)
//		return SFERR_INVALID_PARAM;

	DIEFFECT thisEffect = { sizeof(DIEFFECT) };
	DICONDITION DIConditionStruct[2];
	DIConditionStruct[0].lOffset				= lXOffset;
	DIConditionStruct[0].lPositiveCoefficient	= lXCoefficient;
	DIConditionStruct[0].lNegativeCoefficient	= lXCoefficient;
	DIConditionStruct[0].dwPositiveSaturation	= 10000;
	DIConditionStruct[0].dwNegativeSaturation	= 10000;
	DIConditionStruct[0].lDeadBand				= 0;
	DIConditionStruct[1].lOffset				= lYOffset;
	DIConditionStruct[1].lPositiveCoefficient	= lYCoefficient;
	DIConditionStruct[1].lNegativeCoefficient	= lYCoefficient;
	DIConditionStruct[1].dwPositiveSaturation	= 10000;
	DIConditionStruct[1].dwNegativeSaturation	= 10000;
	DIConditionStruct[1].lDeadBand				= 0;

//	DWORD rgdwAxes[2];
//	int nAxisCount = 0;
//	if(lXCoefficient != 0)
//	{
//		rgdwAxes[nAxisCount] = _Analogue.ForceAxes[0];
//		nAxisCount++;
//	}
//	if(lYCoefficient != 0)
//	{
//		rgdwAxes[nAxisCount] = _Analogue.ForceAxes[1];
//		nAxisCount++;
//	}
//	if(lXCoefficient == 0 && lYCoefficient == 0)
//	{
//		nAxisCount = 2;
//		rgdwAxes[0] = _Analogue.ForceAxes[0];
//		rgdwAxes[1] = _Analogue.ForceAxes[1];
//	}

	DWORD cbTypeSpecificParams;
	PVOID pvTypeSpecificParams;
//	if(nAxisCount == 1)
//	{
//		cbTypeSpecificParams = sizeof(DICONDITION[1]);
//		if(lXCoefficient != 0)
//			pvTypeSpecificParams = &DIConditionStruct[0];
//		else
//			pvTypeSpecificParams = &DIConditionStruct[1];
//	}
//	else
//	{
		cbTypeSpecificParams = sizeof(DICONDITION[2]);
		pvTypeSpecificParams = &DIConditionStruct[0];
//	}
	thisEffect.cbTypeSpecificParams		= cbTypeSpecificParams;
	thisEffect.lpvTypeSpecificParams	= pvTypeSpecificParams;

	return pDIEffect->SetParameters(&thisEffect, DIEP_TYPESPECIFICPARAMS);
}
	
// ----------------------------------------------------------------------------
// Function: 	SWFF_SetGain
// Purpose:		Sets Gain for the Effect
// Parameters:	LPDIRECTINPUTEFFECT	pDIEffect	- Pointer to effect to set the gain for
//				DWORD dwGain					- Gain in 1 to 10000
// Returns:
// Algorithm:	
// Comments:
// 
// ----------------------------------------------------------------------------
HRESULT SWFF_SetGain(
	IN LPDIRECTINPUTEFFECT pDIEffect,
	IN DWORD dwGain)
{
	if(pDIEffect == NULL)
		return SFERR_INVALID_PARAM;

	DIEFFECT thisEffect = { sizeof(DIEFFECT) };
	thisEffect.dwGain = dwGain;
	return pDIEffect->SetParameters(&thisEffect, DIEP_GAIN);
}
// ----------------------------------------------------------------------------
// Function: 	SWFF_CreateRawAxisForceEffect
// Parameters:	LPDIRECTINPUTDEVICE2 pDIDevice		- IDIRECTINPUTDEVICE2 interface
//				LPDIRECTINPUTEFFECT* ppDIEffect		- Receives pointer to created effect
//				LONG lMagnitude						- -10000 to 10000
//				DWORD dwAxis						- Either X_AXIS or Y_AXIS
//
//				
// Returns:		
// Algorithm:
// Comments:	Create this Effect once, then use SetParameter(...) to play the
//				force value
//
// ----------------------------------------------------------------------------
HRESULT SWFF_CreateAxisCenter(
	IN LPDIRECTINPUTDEVICE2 pDIDevice, 
	IN OUT LPDIRECTINPUTEFFECT * ppDIEffect,
	IN LONG lMagnitude,
	IN LONG lCentre,
	IN DWORD dwAxis)
{
	if(pDIDevice == NULL || ppDIEffect == NULL)
		return SFERR_INVALID_PARAM;

	if(!(dwAxis == X_AXIS || dwAxis == Y_AXIS))
		return SFERR_INVALID_PARAM;

	// Always clear return IPtr
	*ppDIEffect = NULL;

	GUID guid=GUID_Spring;

	LPDIRECTINPUTEFFECT  pRawForce;

	DICONSTANTFORCE DIConstantForceStruct;
	DIConstantForceStruct.lMagnitude = lMagnitude;

	DICONDITION DIConditionStruct;
	DIConditionStruct.lOffset				= lCentre;
	DIConditionStruct.lPositiveCoefficient	= lMagnitude;
	DIConditionStruct.lNegativeCoefficient	= lMagnitude;
	DIConditionStruct.dwPositiveSaturation	= 10000;
	DIConditionStruct.dwNegativeSaturation	= 10000;
	DIConditionStruct.lDeadBand				= 0;

	DWORD rgdwAxes[1];
	if(dwAxis == X_AXIS)
		rgdwAxes[0] = _Analogue.ForceAxes[0];
	else
		rgdwAxes[0] = _Analogue.ForceAxes[1];

	LONG rglDirection[1];
	rglDirection[0] = 0;

	DIEFFECT DIEffect;
	DIEffect.dwSize					= sizeof(DIEFFECT);
	DIEffect.dwFlags				= DIEFF_OBJECTIDS | DIEFF_CARTESIAN;
	DIEffect.dwDuration				= INFINITE;
	DIEffect.dwSamplePeriod			= HZ_TO_uS(100);
	DIEffect.dwGain					= 10000;
	DIEffect.dwTriggerButton		= DIEB_NOTRIGGER;
	DIEffect.dwTriggerRepeatInterval= 0;
	DIEffect.cAxes					= 1;
	DIEffect.rgdwAxes				= rgdwAxes;
	DIEffect.rglDirection			= rglDirection;
	DIEffect.lpEnvelope				= NULL;
	DIEffect.cbTypeSpecificParams	= sizeof(DICONDITION);
	DIEffect.lpvTypeSpecificParams	= &DIConditionStruct;

	HRESULT hRet;
	hRet = pDIDevice->CreateEffect(GUID_Spring, &DIEffect, &pRawForce, NULL);
	if(FAILED(hRet)) return hRet;

	*ppDIEffect = pRawForce;
	return SUCCESS;
}
HRESULT SWFF_ChangeAxisCenter(
	IN LPDIRECTINPUTEFFECT pDIEffect,
	IN LONG lMagnitude,
	IN LONG lCentre)
{
	if(pDIEffect == NULL)
		return SFERR_INVALID_PARAM;


	GUID guid=GUID_Spring;

	DICONSTANTFORCE DIConstantForceStruct;
	DIConstantForceStruct.lMagnitude = lMagnitude;

	DICONDITION DIConditionStruct;
	DIConditionStruct.lOffset				= lCentre;
	DIConditionStruct.lPositiveCoefficient	= lMagnitude;
	DIConditionStruct.lNegativeCoefficient	= lMagnitude;
	DIConditionStruct.dwPositiveSaturation	= 10000;
	DIConditionStruct.dwNegativeSaturation	= 10000;
	DIConditionStruct.lDeadBand				= 0;

	DIEFFECT DIEffect;
	DIEffect.dwSize					= sizeof(DIEFFECT);
	DIEffect.dwFlags				= DIEFF_OBJECTIDS | DIEFF_CARTESIAN;
	DIEffect.dwDuration				= INFINITE;
	DIEffect.dwSamplePeriod			= HZ_TO_uS(100);
	DIEffect.dwGain					= 10000;
	DIEffect.dwTriggerButton		= DIEB_NOTRIGGER;
	DIEffect.dwTriggerRepeatInterval= 0;
	DIEffect.cAxes					= 1;
	DIEffect.rgdwAxes				= NULL;
	DIEffect.rglDirection			= NULL;
	DIEffect.lpEnvelope				= NULL;
	DIEffect.cbTypeSpecificParams	= sizeof(DICONDITION);
	DIEffect.lpvTypeSpecificParams	= &DIConditionStruct;

	return pDIEffect->SetParameters(&DIEffect, DIEP_TYPESPECIFICPARAMS);
}

HRESULT SWFF_CreateRawAxisForceEffect(
	IN LPDIRECTINPUTDEVICE2 pDIDevice, 
	IN OUT LPDIRECTINPUTEFFECT * ppDIEffect,
	IN LONG lMagnitude,
	IN DWORD dwAxis)
{
	if(pDIDevice == NULL || ppDIEffect == NULL)
		return SFERR_INVALID_PARAM;

	if(!(dwAxis == X_AXIS || dwAxis == Y_AXIS))
		return SFERR_INVALID_PARAM;

	// Always clear return IPtr
	*ppDIEffect = NULL;

	LPDIRECTINPUTEFFECT  pRawForce;

	DICONSTANTFORCE DIConstantForceStruct;
	DIConstantForceStruct.lMagnitude = lMagnitude;

	DWORD rgdwAxes[1];
	if(dwAxis == X_AXIS)
		rgdwAxes[0] = _Analogue.ForceAxes[0];
	else
		rgdwAxes[0] = _Analogue.ForceAxes[1];

	LONG rglDirection[1];
	rglDirection[0] = 0;

	DIEFFECT DIEffect;
	DIEffect.dwSize					= sizeof(DIEFFECT);
	DIEffect.dwFlags				= DIEFF_OBJECTIDS | DIEFF_CARTESIAN;
	DIEffect.dwDuration				= INFINITE;
	DIEffect.dwSamplePeriod			= HZ_TO_uS(100);
	DIEffect.dwGain					= 10000;
	DIEffect.dwTriggerButton		= DIEB_NOTRIGGER;
	DIEffect.dwTriggerRepeatInterval= 0;
	DIEffect.cAxes					= 1;
	DIEffect.rgdwAxes				= rgdwAxes;
	DIEffect.rglDirection			= rglDirection;
	DIEffect.lpEnvelope				= NULL;
	DIEffect.cbTypeSpecificParams	= sizeof(DICONSTANTFORCE);
	DIEffect.lpvTypeSpecificParams	= &DIConstantForceStruct;

	HRESULT hRet;
	hRet = pDIDevice->CreateEffect(GUID_RawForce, &DIEffect, &pRawForce, NULL);
	if(FAILED(hRet)) return hRet;

	*ppDIEffect = pRawForce;
	return SUCCESS;
}

// ----------------------------------------------------------------------------
// Function: 	SWFF_CreateROMEffect
// Parameters:	LPDIRECTINPUTDEVICE2 pDIDevice	- IDIRECTINPUTDEVICE2 interface
//				LPDIRECTINPUTEFFECT* ppDIEffect	- Receives pointer to created effect
//				REFGUID refGUID					- GUID for ROM Effect
//				DWORD dwDuration				- uS
//				DWORD dwGain					- 1 to 10000
//				DWORD dwDirection				- 0 to 35999
//				LONG lButton					- Index of playback button, -1 for none
//
// Returns:		
// Algorithm:
// Comments:	Assumes valid GUID for the ROM Effect
// Note:		If unmodified ROM Effect, user has to pass
//				   DEFAULT_ROM_EFFECT_DURATION,  DEFAULT_ROM_EFFECT_GAIN
// ----------------------------------------------------------------------------
HRESULT SWFF_CreateROMEffect(
	IN LPDIRECTINPUTDEVICE2 pDIDevice, 
	IN OUT LPDIRECTINPUTEFFECT * ppDIEffect,
	IN REFGUID refGUID,
	IN DWORD dwDuration,		
	IN DWORD dwGain,
	IN DWORD dwDirection,		
	IN LONG lButton)			
{
	if(pDIDevice == NULL || ppDIEffect == NULL)
		return SFERR_INVALID_PARAM;
	// Always clear return IPtr
	*ppDIEffect = NULL;

	LPDIRECTINPUTEFFECT  pROMEffect = NULL;

	// Default NO Envelope
	DIENVELOPE DIEnvelopeStruct;				
	DIEnvelopeStruct.dwSize = sizeof(DIENVELOPE);
	DIEnvelopeStruct.dwAttackTime = 0;
	DIEnvelopeStruct.dwAttackLevel = 10000;
	DIEnvelopeStruct.dwFadeTime = 0;
	DIEnvelopeStruct.dwFadeLevel = 10000;

	// 2DOF
	DWORD rgdwAxes[2];
	rgdwAxes[0] = _Analogue.ForceAxes[0];
	rgdwAxes[1] = _Analogue.ForceAxes[1];

	LONG rglDirection[2];
	rglDirection[0] = dwDirection;
	rglDirection[1] = 0;

	DIEFFECT DIEffect;
	DIEffect.dwSize					= sizeof(DIEFFECT);
	DIEffect.dwFlags				= DIEFF_OBJECTIDS | DIEFF_POLAR;
	// Set Duration and Gain to use Default ROM Effect params unless overridden
	DIEffect.dwDuration				= dwDuration;	// can be DEFAULT_ROM_EFFECT_DURATION
	DIEffect.dwSamplePeriod			= DEFAULT_ROM_EFFECT_OUTPUTRATE;
	DIEffect.dwGain					= dwGain;		// can be DEFAULT_ROM_EFFECT_GAIN;	
	//
	DIEffect.dwTriggerButton		= lButton == -1 ? DIEB_NOTRIGGER : FIELD_OFFSET(DIJOYSTATE, rgbButtons) + lButton;
	DIEffect.dwTriggerRepeatInterval= 0;
	DIEffect.cAxes					= 2;
	DIEffect.rgdwAxes				= rgdwAxes;
	DIEffect.rglDirection			= rglDirection;
	DIEffect.lpEnvelope				= &DIEnvelopeStruct;
	DIEffect.cbTypeSpecificParams	= 0;
	DIEffect.lpvTypeSpecificParams	= NULL;

	HRESULT hRet = pDIDevice->CreateEffect(refGUID, &DIEffect, &pROMEffect, NULL);
	if(FAILED(hRet)) return hRet;

	*ppDIEffect = pROMEffect;
	return SUCCESS;
}

// ----------------------------------------------------------------------------
// Function: 	SWFF_CreatePeriodicEffect
// Purpose:		Creates a Periodic type Effect with specified params
// Parameters:  LPDIRECTINPUTDEVICE2 pDIDevice	- IDIRECTINPUTDEVICE2 interface
//				LPDIRECTINPUTEFFECT* ppDIEffect	- Receives pointer to created effect
//				DWORD dwType			- Type of PERIODIC Effect (SINE | COSINE | ...)
//				DWORD dwDuration		- uS
//				DWORD dwPeriod			- uS
//				DWORD dwDirection		- 0 to 35999
//				DWORD dwMagnitude		- 0 to 10000
//				LONG lOffset			- Offset in -10000 to 10000
//				DWORD dwAttackTime		- Envelope Attack Time in uS
//				DWORD dwAttackLevel		- Envelope Attack Level in 0 to 10000
//				DWORD dwFadeTime		- Envelope Fade time in uS
//				DWORD dwFadeLevel		- Envelope Fade Level
//				LONG lButton			- Index of playback button, -1 for none
//
// Returns:
// Algorithm:	
// Comments:
// 
// ----------------------------------------------------------------------------
HRESULT SWFF_CreatePeriodicEffect(	IN LPDIRECTINPUTDEVICE2 pDIDevice,
								IN OUT LPDIRECTINPUTEFFECT* ppDIEffect,
								IN DWORD dwType,
								IN DWORD dwDuration,		
								IN DWORD dwPeriod,			
								IN DWORD dwDirection,		
								IN DWORD dwMagnitude,		
								IN LONG lOffset,			
								IN DWORD dwAttackTime,		
								IN DWORD dwAttackLevel,		
								IN DWORD dwFadeTime,		
								IN DWORD dwFadeLevel,		
								IN LONG lButton)			
{
	if(pDIDevice == NULL || ppDIEffect == NULL)
		return SFERR_INVALID_PARAM;
	// Always clear return IPtr
	*ppDIEffect = NULL;

	// type-specific stuff
	DWORD dwPhase = 0;
	GUID guid;
	switch(dwType)
	{
		case SINE:
			guid = GUID_Sine;
			break;
		case COSINE:
			guid = GUID_Sine;
			dwPhase = 9000;
			break;
		case SQUARE_HIGH:
			guid = GUID_Square;
			break;
		case SQUARE_LOW:
			guid = GUID_Square;
			dwPhase = 18000;
			break;
		case TRIANGLE_UP:
			guid = GUID_Triangle;
			break;
		case TRIANGLE_DOWN:
			guid = GUID_Triangle;
			dwPhase = 18000;
			break;
		case SAWTOOTH_UP:
			guid = GUID_SawtoothUp;
			break;
		case SAWTOOTH_DOWN:
			guid = GUID_SawtoothDown;
			break;
		default:
			// illegal
			break;
	}

	DIPERIODIC DIPeriodicStruct;
	DIPeriodicStruct.dwMagnitude = dwMagnitude;
	DIPeriodicStruct.lOffset = lOffset;
	DIPeriodicStruct.dwPhase = dwPhase;
	DIPeriodicStruct.dwPeriod = dwPeriod;

	DIENVELOPE DIEnvelopeStruct;
	DIEnvelopeStruct.dwSize = sizeof(DIENVELOPE);
	DIEnvelopeStruct.dwAttackTime = dwAttackTime;
	DIEnvelopeStruct.dwAttackLevel = dwAttackLevel;
	DIEnvelopeStruct.dwFadeTime = dwFadeTime;
	DIEnvelopeStruct.dwFadeLevel = dwFadeLevel;

	DWORD rgdwAxes[2];
	rgdwAxes[0] = _Analogue.ForceAxes[0];
	rgdwAxes[1] = _Analogue.ForceAxes[1];

	LONG rglDirection[2];
	rglDirection[0] = dwDirection;
	rglDirection[1] = 0;

	DIEFFECT DIEffectStruct;
	DIEffectStruct.dwSize					= sizeof(DIEFFECT);
	DIEffectStruct.dwFlags					= DIEFF_OBJECTIDS | DIEFF_POLAR;
	DIEffectStruct.dwDuration				= dwDuration;
	DIEffectStruct.dwSamplePeriod			= HZ_TO_uS(100);
	DIEffectStruct.dwGain					= 10000;
	DIEffectStruct.dwTriggerButton			= lButton == -1 ? DIEB_NOTRIGGER : FIELD_OFFSET(DIJOYSTATE, rgbButtons) + lButton;
	DIEffectStruct.dwTriggerRepeatInterval	= 0;
	DIEffectStruct.cAxes					= 2;
	DIEffectStruct.rgdwAxes					= rgdwAxes;
	DIEffectStruct.rglDirection				= rglDirection;
	DIEffectStruct.lpEnvelope				= &DIEnvelopeStruct;
	DIEffectStruct.cbTypeSpecificParams		= sizeof(DIPeriodicStruct);
	DIEffectStruct.lpvTypeSpecificParams	= &DIPeriodicStruct;

	HRESULT hResult;
	hResult = pDIDevice->CreateEffect(guid, &DIEffectStruct, ppDIEffect, NULL);

	return hResult;
}

// ----------------------------------------------------------------------------
// Function: 	SWFF_CreateSpringEffect
// Purpose:		Creates a Spring type Effect with specified params
// Parameters:	LPDIRECTINPUTDEVICE2 pDIDevice	- IDIRECTINPUTDEVICE2 interface
//				LPDIRECTINPUTEFFECT* ppDIEffect	- Receives pointer to created effect
//				DWORD dwDuration				- Duration in uS
//				LONG lKx						- X-Axis K Coefficient in -10000 to 10000
//				LONG lCenterx					- X-Axis Center in -10000 to 10000
//				LONG lKy						- Y-Axis K Coefficient in -10000 to 10000
//				LONG lCentery					- Y-Axis Center in -10000 to 10000
//				LONG lButton					- Index of playback button, -1 for none
//
// Returns:
// Algorithm:	
// Comments:
//			To create a 1D spring, set the lKx or lKy parameter to 0
//			To create a 2D spring, set both lKx and lKy parameter to non-zero
//				or set both lFx and lFy to zero
//  
// ----------------------------------------------------------------------------
HRESULT SWFF_CreateSpringEffect(	IN LPDIRECTINPUTDEVICE2 pDIDevice,
							IN OUT LPDIRECTINPUTEFFECT* ppDIEffect,
							IN DWORD dwDuration,
							IN LONG lKx,
							IN LONG lCenterx,
							IN LONG lKy,
							IN LONG lCentery,
							IN LONG lButton)
{
	if(pDIDevice == NULL || ppDIEffect == NULL)
		return SFERR_INVALID_PARAM;
	
	// Always clear return IPtr
	*ppDIEffect = NULL;

	HRESULT hResult = SWFF_CreateConditionEffect(pDIDevice,
											ppDIEffect,
											SPRING,
											dwDuration,
											lKx, lCenterx,
											lKy, lCentery,
											lButton);

	return hResult;
}

// Set Periodic function by DBM
HRESULT SWFF_SetPeriodic(
	IN LPDIRECTINPUTEFFECT pDIEffect,
	IN DWORD dwMagnitude,
	IN DWORD lOffset,
	IN DWORD dwPhase,
	IN DWORD dwPeriod)
{
	if(pDIEffect == NULL)
		return SFERR_INVALID_PARAM;

	DIEFFECT thisEffect = { sizeof(DIEFFECT) };
	DIPERIODIC DIPeriodicStruct;
	DIPeriodicStruct.dwMagnitude=dwMagnitude;
	DIPeriodicStruct.lOffset=lOffset;
	DIPeriodicStruct.dwPhase=dwPhase;
	DIPeriodicStruct.dwPeriod=dwPeriod;

	thisEffect.cbTypeSpecificParams		= sizeof(DIPeriodicStruct);
	thisEffect.lpvTypeSpecificParams	= &DIPeriodicStruct;

	return pDIEffect->SetParameters(&thisEffect, DIEP_TYPESPECIFICPARAMS);
}

// ----------------------------------------------------------------------------
// Function: 	SWFF_CreateConditionEffect
// Purpose:		Creates a Condition type Effect with specified params
// Parameters:	LPDIRECTINPUTDEVICE2 pDIDevice	- IDIRECTINPUTDEVICE2 interface
//				LPDIRECTINPUTEFFECT* ppDIEffect	- Receives pointer to created effect
//				DWORD dwType					- SPRING | INERTIA | DAMPER | FRICTION
//				DWORD dwDuration				- Duration in uS
//				LONG lXCoefficient				- Coefficient in -10000 to 10000
//				LONG lXOffset					- Offset in -10000 to 10000
//				LONG lYCoefficient				- Coefficient in -10000 to 10000
//				LONG lYOffset					- Offset in -10000 to 10000
//				LONG lButton					- Index of playback button, -1 for none
// Returns:
// Algorithm:	
// Comments:
//			To create a 1D Friction, set the lFx or lFy parameter to 0
//			To create a 2D Friction, set both lFx and lFy parameter to non-zero
//				or set both lFx and lFy to zero
// 
// ----------------------------------------------------------------------------
HRESULT SWFF_CreateConditionEffect(	
	IN LPDIRECTINPUTDEVICE2 pDIDevice,
	IN OUT LPDIRECTINPUTEFFECT* ppDIEffect,
	IN DWORD dwType,
	IN DWORD dwDuration,
	IN LONG lXCoefficient,
	IN LONG lXOffset,
	IN LONG lYCoefficient,
	IN LONG lYOffset,
	IN LONG lButton)
{
	if(pDIDevice == NULL || ppDIEffect == NULL)
		return SFERR_INVALID_PARAM;

	// Always clear return IPtr
	*ppDIEffect = NULL;

	GUID guid;
	switch(dwType)
	{
		case SPRING:		  //this one for us!
			guid = GUID_Spring;
			break;
		case INERTIA:
			guid = GUID_Inertia;
			break;
		case DAMPER:
			guid = GUID_Damper;
			break;
		case FRICTION:
			guid = GUID_Friction;
			break;
		default:
			break;
	}

	DICONDITION DIConditionStruct[2];
	DIConditionStruct[0].lOffset				= lXOffset;
	DIConditionStruct[0].lPositiveCoefficient	= lXCoefficient;
	DIConditionStruct[0].lNegativeCoefficient	= lXCoefficient;
	DIConditionStruct[0].dwPositiveSaturation	= 10000;
	DIConditionStruct[0].dwNegativeSaturation	= 10000;
	DIConditionStruct[0].lDeadBand				= 0;
	DIConditionStruct[1].lOffset				= lYOffset;
	DIConditionStruct[1].lPositiveCoefficient	= lYCoefficient;
	DIConditionStruct[1].lNegativeCoefficient	= lYCoefficient;
	DIConditionStruct[1].dwPositiveSaturation	= 10000;
	DIConditionStruct[1].dwNegativeSaturation	= 10000;
	DIConditionStruct[1].lDeadBand				= 0;

	DWORD rgdwAxes[2];
	int nAxisCount = 0;
	if(lXCoefficient != 0 && lYCoefficient==0)
	{
		rgdwAxes[nAxisCount] = _Analogue.ForceAxes[0];
		nAxisCount++;
	}
	else
	if(lYCoefficient != 0 && lXCoefficient == 0)
	{
		rgdwAxes[nAxisCount] = _Analogue.ForceAxes[1];
		nAxisCount++;
	}
	else
	{
		nAxisCount = 2;
		rgdwAxes[0] = _Analogue.ForceAxes[0];
		rgdwAxes[1] = _Analogue.ForceAxes[1];
	}
	DWORD cbTypeSpecificParams;
	PVOID pvTypeSpecificParams;
	if(nAxisCount == 1)
	{
		cbTypeSpecificParams = sizeof(DICONDITION[1]);
		if(lXCoefficient != 0)
			pvTypeSpecificParams = &DIConditionStruct[0];
		else
			pvTypeSpecificParams = &DIConditionStruct[1];
	}
	else
	{
		cbTypeSpecificParams = sizeof(DICONDITION[2]);
		pvTypeSpecificParams = &DIConditionStruct[0];
	}

	LONG rglDirection[2];
	rglDirection[0] = 1;//was 0
	rglDirection[1] = 0;

	DIEFFECT DIEffectStruct;
	DIEffectStruct.dwSize					= sizeof(DIEFFECT);
	DIEffectStruct.dwFlags					= DIEFF_OBJECTIDS | DIEFF_CARTESIAN;
	DIEffectStruct.dwDuration				= dwDuration;
	DIEffectStruct.dwSamplePeriod			= HZ_TO_uS(100);
	DIEffectStruct.dwGain					= 10000;
	DIEffectStruct.dwTriggerButton			= lButton == -1 ? DIEB_NOTRIGGER : FIELD_OFFSET(DIJOYSTATE, rgbButtons) + lButton;
	DIEffectStruct.dwTriggerRepeatInterval	= 0;
	DIEffectStruct.cAxes					= nAxisCount;
	DIEffectStruct.rgdwAxes					= rgdwAxes;
	DIEffectStruct.rglDirection				= rglDirection;
	DIEffectStruct.lpEnvelope				= NULL;
	DIEffectStruct.cbTypeSpecificParams		= cbTypeSpecificParams;
	DIEffectStruct.lpvTypeSpecificParams	= pvTypeSpecificParams;

	HRESULT hResult;
	hResult = pDIDevice->CreateEffect(guid, &DIEffectStruct, ppDIEffect, NULL);

	return hResult;
}

// ----------------------------------------------------------------------------
// Function: 	SWFF_DestroyAllEffects
// Purpose:		Destroys all created effects
// Parameters:	LPDIRECTINPUTDEVICE2 pDIDevice	- IDIRECTINPUTDEVICE2 interface
// Returns:
// Algorithm:	
// Comments:
// 
// ----------------------------------------------------------------------------
BOOL CALLBACK DIEnumAndDestroyCreatedEffectsProc(LPDIRECTINPUTEFFECT pDIEffect, LPVOID lpvRef)
{
	pDIEffect->Release();

	return DIENUM_CONTINUE;
}
HRESULT SWFF_DestroyAllEffects(
	IN LPDIRECTINPUTDEVICE2 pDIDevice)
{
	HRESULT hResult;

	if(pDIDevice == NULL)
		return SFERR_INVALID_PARAM;

	hResult = pDIDevice->EnumCreatedEffectObjects(DIEnumAndDestroyCreatedEffectsProc, NULL, 0);

	return hResult;
}


