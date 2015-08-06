//------------------------------------------------------------------------------
//Filename       modinst.h
//System         
//Author         Andrew McRae
//Date           Wed 27 Aug 1997
//Description    
//------------------------------------------------------------------------------
#ifndef	MODINST_Included
#define	MODINST_Included

#define	DEFAULT_MODINST 0

//typedef class Model *PMODEL;
#include "modvec.h"

enum	AnimSteps
{
	ARC_IMMEDIATE = 1,
	ARC_1SEC = 100,
	ARC_30SEC = 3000,
	ARC_240SEC = 24000
};

enum	SrcBaseType
{
	SBASE_DEFAULT = 0,
	SBASE_AC,
	SBASE_ANIM
};

#define	RUNNING_VOLTS  28
#define	MaxDialSrc 		8
#define	MaxAutoDial		32

struct	DialSpec
{
	int	DestValOffset;
	int	SrcValOffset;
	int	SrcValStructIndex;

	FP	ValScale;

	FP	minval;
	FP	maxval;

	int		minIntval;
	int		maxIntval;
	int		Intvalscale;

	UWord	shiftsrc:6,
			shiftdest:6,
			useint:1;

	UWord	torestval;
	SrcBaseType	btype;

	void	SetDialValue(ItemPtr,UByteP,UByteP*);
};

struct	TimedDialSpec											//RJS 29Jun98
{
	SWord	theTimer;
	SLong	SrcVal;
	SLong	OldGap;
	SLong	OldVal;

	int		destOffset;

	int		timeUp;
	int		timeDown;

//DeadCode RJS 30Jun98 	Bool	signedSrc;
	Bool	signedDest;

	UByte	nobitsDest;

	void	SetTimedAnim(void*	adptr);
};


typedef class _instruments
{

public:

	// Instruments
	FP ActualSpeed;			// miles per hour
	FP TrueAirSpeed;		// knotts
	FP IndicatedAirSpeed; 	// knotts
	FP MachNo;				// no units
	ULong Altitude;			// feet
//	ULong RateOfClimb;		// feet per minute
	SLong RateOfClimb;		// feet per minute
	FP BankAngle;		// degrees
	FP PitchAngle;		// degrees
	FP HdgAngle;		// degrees
	FP LastHdgAngle;
	FP NormalAcc;			// gravities
	FP Rpm1;				// rpm
	FP Rpm2;				// rpm
	FP Slip;				// slip								//RJS 06Apr98
//	SWord Turn;				// turn								//RJS 21Apr98
	FP	turn;				//turn in rads/cs
	FP pitchrate;			//in rads/cs
	FP Turn;				// turn								//RJS 21Apr98
	FP Turn2;				// turn								//RJS 21Apr98
	FP	time;				//time in csecs	debug only
	// Fiddled instruments....

	FP		TempFreeAir;										//RJS 03Apr98
	SLong	TempExhaust;							//RJS 11Feb98
	SLong	Charge;										//RJS 11Feb98
	SLong	GyroCompass;										//RJS 11Feb98
	SLong	HorizStab;										//RJS 11Feb98
	SLong	HydraulicPress;							//RJS 11Feb98
	SLong	CabPress;							//RJS 11Feb98
	SLong	FuelPress;							//RJS 11Feb98
	SLong	FuelContentInt;										//RJS 03Apr98
	SLong	FuelContentTot;										//RJS 14Apr99
	SLong	OxygenPress;										//RJS 01May98
	SWord	ManifoldPressure;							//RJS 02Nov98
	SWord	SuctionGuage;										//RJS 16Feb99
	SWord	CarburettorAirTemp;									//RJS 16Feb99
	SWord	CoolantTemp;										//RJS 16Feb99
	SWord	Power;												//RJS 31Mar99
	SWord	ExhaustTemp;				//RJS 01Apr99
	SWord	Voltage;											//RJS 14Apr99


	UWord	TimerCharge;								//RJS 11Feb98
	UWord	TimerGyro;									//RJS 11Feb98
	UWord	TimerHorizStab;									//RJS 11Feb98
	UWord	TimerExhaust;									//RJS 11Feb98
	UWord	TimerCabPress;									//RJS 11Feb98
	UWord	TimerHydraulicPress;									//RJS 11Feb98
	UWord	TimerFuelPress;									//RJS 11Feb98
	UWord	TimerOxygenPress;									//RJS 01May98
	UWord	TimerManifoldPress;									//RJS 01May98

	UByteP	DialSrcList[MaxDialSrc];							//RJS 16Feb98
	UWord	DialSrcCnt;											//RJS 16Feb98

	DialSpec	DialList[MaxAutoDial];							//RJS 29Jun98
	UWord		DialCnt;

	TimedDialSpec	TimedDialList[MaxAutoDial];					//RJS 29Jun98
	UWord			TimedDialCnt;

	void SetInstruments (AirStrucPtr const ControlledAC,PMODEL);

	SLong	SetTimedAnim (SLong&,UWord&,SLong,UWord,UWord);		//RJS 23Jun98
	SLong	EngineDamage(UByteP, int);							//RJS 16Feb98
	void	SetCockpitAnims(ItemPtr,UByteP);					//RJS 20Jul98
	void	UpdateCockpitTimers(SLong);							//RJS 16Feb98
	void	NewDialValue(void*,UByteP,void*,UByteP,int,int,int,UByte,UByte,UWord	restrot = 0);
	void	AddAutoDial(void*,UByteP,void*,SWordP,int,int,int scaler = 0);//RJS 24Apr98
	void	AddAutoDial(void*,SWordP,void*,SWordP,int,int,int scaler = 0);//RJS 24Apr98
	void	AddAutoDial(void*,UByteP,void*,ULongP,int,int,int scaler = 0);//RJS 24Apr98
	void	AddAutoDial(void*,SWordP,void*,ULongP,int,int,int scaler = 0);//RJS 24Apr98

	void	NewDialValue(void*,UByteP,void*,UByteP,FP,FP,FP,UByte,UWord	restrot = 0);
	void	AddAutoDial(void*,UByteP,void*,FP*,FP,FP,FP scaler = 0);//RJS 24Apr98
	void	AddAutoDial(void*,SWordP,void*,FP*,FP,FP,FP scaler = 0);//RJS 24Apr98

	void	AddAutoDial(void*,UByteP,void*,SLongP,int,int,int scaler = 0);//RJS 24Apr98
	void	AddAutoDial(void*,SWordP,void*,SLongP,int,int,int scaler = 0);//RJS 24Apr98

	void	AddTimedDial(void*,UByteP,int,int,Bool signedSrc=FALSE);//RJS 29Jun98
	void	AddTimedDial(void*,SByteP,int,int,Bool signedSrc=FALSE);//RJS 29Jun98
	void	AddTimedDial(void*,UWordP,int,int,Bool signedSrc=FALSE);//RJS 29Jun98
	void	AddTimedDial(void*,SWordP,int,int,Bool signedSrc=FALSE);//RJS 29Jun98
	void	AddTimedDial(void*,ULongP,int,int,Bool signedSrc=FALSE);//RJS 29Jun98
	void	AddTimedDial(void*,SLongP,int,int,Bool signedSrc=FALSE);//RJS 29Jun98

	void	NewTimedDial(int,int,int,Bool,Bool,UByte);			//RJS 29Jun98
					   
	void Null ()		
 	{
 		ActualSpeed = 0.0;
 		TrueAirSpeed = 0;
 		IndicatedAirSpeed = 0;
 		MachNo = 0;
 		Altitude = 0;
 		RateOfClimb = 0;
 		BankAngle = 0;
 		PitchAngle = 0;
 		HdgAngle = 0;
		LastHdgAngle = 0;
 		NormalAcc = 0;
 		Rpm1 = 0;
 		Rpm2 = 0;
		Turn = 0;			//rdh
		turn = 0;
		Turn2 = 0;			//rdh
		time = 0;
 		TempFreeAir = 0;	
 		TempExhaust = 0;
 		Charge = 0;
 		GyroCompass = 0;
 		HorizStab = 0;
 		HydraulicPress = 0;
 		CabPress = 0;
 		FuelPress = 0;
		FuelContentInt = 0;										//RJS 16Feb99								
		FuelContentTot = 0;										//RJS 16Feb99
//DeadCode CSB 14/04/99			FuelContentExt = 0;										//RJS 16Feb99
		OxygenPress = 0;										//RJS 16Feb99
		ManifoldPressure = 0;									//RJS 16Feb99
		SuctionGuage = 0;										//RJS 16Feb99
		CarburettorAirTemp = 0;									//RJS 16Feb99
		CoolantTemp = 0;										//RJS 16Feb99
 
 		TimerCharge = 0;
 		TimerGyro = 0;
 		TimerHorizStab = 0;
 		TimerExhaust = 0;
 		TimerCabPress = 0;
 		TimerHydraulicPress = 0;
 		TimerFuelPress = 0;
		TimerOxygenPress = 0;									//RJS 16Feb99
		TimerManifoldPress = 0;

		DialSrcCnt = 0;
		DialCnt = 0;

		TimedDialCnt = 0;
 	}	

}
INSTRUMENTS,
*PINSTRUMENTS;

#endif

