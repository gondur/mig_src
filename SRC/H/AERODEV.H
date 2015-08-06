//------------------------------------------------------------------------------
//Filename       aerodev.h
//System         
//Author         Andrew McRae
//Date           Tue 12 Aug 1997
//Description    
//------------------------------------------------------------------------------
#ifndef	AERODEV_Included
#define	AERODEV_Included

#define	DEFAULT_AERODEV 0


class AeroDevice
{

public:

	enum DT_TYPE
	{
		DT_VOID,
		DT_GEAR,
		DT_FLAPS,
		DT_SLATS,
		DT_SPEEDBRAKES,
		DT_TANKS
	};

	enum CONTROL_TYPE
	{
		CT_KEYS,
		CT_AUTO
	};

	PMODEL pModel;

	DT_TYPE Type;

	SWord Val;
	SWord Attractor;
// Taken from aerodev.cpp.....
	SWord OldAttractor;									//RJS 29Apr98

	FP dCl, dCd, dCm, dAlpha;

	FP scale;

	SWord Rate;
	KeyVal3D Key;

	// For comms and replay....
	UByte	DeviceID;									//RJS 18Sep98
	
//	enum MOVEMENT { STATIONARY=0, MOVEIN=1, MOVEOUT=2, OVERFLOW=3 };

//	MOVEMENT Dir;

	AeroDevice (
				AirStrucPtr const ControlledAC,
				PMODEL pmodel,		// parent flight model class
				DT_TYPE type,		// DT_xxxxx
				FP dcl,	  			// delta CL
				FP dcd,				// delta CD
				FP dcm,				// delta CM
				FP dalpha,			// delta Alpha
				SWord rate,			// movement rate
				KeyVal3D key,		// control key (0 if none)
				UByte* pAnimByte,	// anim byte address
				SLong	minval=0,
				SLong	maxval=16384,
				SLong	Scale=0);		// anim scale

	~AeroDevice ();

	LINKEDLIST<AeroDevice> List;
	void Process ();
	void GearUp ();
	void GearDown ();

	void Action (AirStrucPtr const ControlledAC, CONTROL_TYPE,Bool sendpacket = TRUE);//RJS 21Sep98

} ;

typedef AeroDevice AERODEVICE, *PAERODEVICE;


#endif
