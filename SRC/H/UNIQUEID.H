//;;------------------------------------------------------------------------------
//;;Filename       uniqueid.g
//;;System         
//;;Author         Jim Taylor
//;;Date           Mon 27 Nov 1995
//;;Description    Unique ID equates. 
//;;				Basic bands input and specific item UIDs output
//;;------------------------------------------------------------------------------
//;;This bit is manually editable:
#ifndef	UNIQUEID_Included
#define	UNIQUEID_Included
#define	DEFAULT_UNIQUEID 0

#ifndef	UNIQUEIDBAND_Included
#define	UNIQUEIDBAND_Included
enum	UniqueIDBand
//DeadCode MS 14Oct98 	{
//DeadCode MS 14Oct98 		PilotedAcBAND			=	0x0000,
//DeadCode MS 14Oct98 		WayPointBAND			=	0x0100,						//MS 06Dec96
//DeadCode MS 14Oct98 		RedGroundMobileBAND		=	0x0400,		WayPointBANDEND			=	RedGroundMobileBAND,//MS 06Dec96
//DeadCode MS 14Oct98 		BlueGroundMobileBAND	=	0x0600,						//MS 06Dec96
//DeadCode MS 14Oct98 		MissileBAND				=	0x0800,						//MS 06Dec96
//DeadCode MS 14Oct98 		RedAcBAND				=	0x0C00,
//DeadCode MS 14Oct98 		BlueAcBAND				=	0x0E00,
//DeadCode MS 14Oct98 		RedCivilianBAND			=	0x1000,		BlueAcBANDEND=RedCivilianBAND,//NOTHING BELOW THIS HAS A PLACENAME!!!
//DeadCode MS 14Oct98 		BlueCivilianBAND		=	0x1200,
//DeadCode MS 14Oct98 		GreenCivilianBAND		=	0x1400,
//DeadCode MS 14Oct98 		RedVetoedBAND			=	0x1800,	
//DeadCode MS 14Oct98 		BlueVetoedBAND			=	0x1C00,
//DeadCode MS 14Oct98 		LandscapeBAND			=	0x1E00,
//DeadCode MS 14Oct98 		RedMilitaryBAND			=	0x2000,
//DeadCode MS 14Oct98 		BlueMilitaryBAND		=	0x2200,
//DeadCode MS 14Oct98 		RedAirfieldBAND			=	0x2400,
//DeadCode MS 14Oct98 		BlueAirfieldBAND		=	0x2600,
//DeadCode MS 14Oct98 		RedPortBAND				=	0x2800,
//DeadCode MS 14Oct98 		BLuePortBAND			=	0x2A00,
//DeadCode MS 14Oct98 		RedCCCBAND				=	0x2C00,
//DeadCode MS 14Oct98 		BlueCCCBAND				=	0x2E00,
//DeadCode MS 14Oct98 		RedGICBAND				=	0x3000,
//DeadCode MS 14Oct98 		BlueGICBAND				=	0x3300,						//MS 11Dec96
//DeadCode MS 14Oct98 		RedAAASiteBAND			=	0x3600,						//MS 11Dec96
//DeadCode MS 14Oct98 		BlueAAASiteBAND			=	0x3900,
//DeadCode MS 14Oct98 		RedSAMBAND				=	0x3C00,
//DeadCode MS 14Oct98 		BlueSAMBAND				=	0x3E00,

//TempCode MS 14Oct98 	{															//MS 14Oct98
//TempCode MS 14Oct98 		PilotedAcBAND			=	0x0000,
//TempCode MS 14Oct98 		WayPointBAND			=	0x0100,						
//TempCode MS 14Oct98 		MissileBAND				=	0x0800,					
//TempCode MS 14Oct98 		LandscapeBAND			=	0x1E00,
//TempCode MS 14Oct98 		RedRailBand				=	0x1F00
//TempCode MS 14Oct98 		RedRoadBAND				=	0x1F40
//TempCode MS 14Oct98 		RedAcBAND				=	0x1F80
//TempCode MS 14Oct98 		BlueAcBAND				=	0x2000
//TempCode MS 14Oct98 		AmberAirfieldBAND		=	0x2080
//TempCode MS 14Oct98 		RedStaticAcBAND			=	0x2280,
//TempCode MS 14Oct98 		BlueStaticACBAND		=	0x22A0,
//TempCode MS 14Oct98 		RedFakeAcBAND			=	0x22C0,
//TempCode MS 14Oct98 		RedAAAHiddenBAND		=	0x22E0,
//TempCode MS 14Oct98   		AmberCivilianBand		=	0x2360,
//TempCode MS 14Oct98 		AmberSupplyBAND			=	0x2460,
//TempCode MS 14Oct98 		RedRepairBAND			=	0x2660,
//TempCode MS 14Oct98 		AmberBridgeBAND			=	0x2760,
//TempCode MS 14Oct98 		AmberMYardBAND			=	0x27E0,
//TempCode MS 14Oct98 		RedTrainBAND			=	0x2800,
//TempCode MS 14Oct98 		RedTruckBAND			=	0x2880,
//TempCode MS 14Oct98 		RedTruckParkBAND		=	0x2900,
//TempCode MS 14Oct98 		RedCombatVehicleBAND	=	0x2980,
//TempCode MS 14Oct98 		BlueCombatVehicleBAND	=	0x29C0,
//TempCode MS 14Oct98 		RedArmourBAND			=	0X2A00,
//TempCode MS 14Oct98 		BlueArmourBAND			=	0x2A40,
//TempCode MS 14Oct98 		RedArtilleryBAND		=	0x2A80,
//TempCode MS 14Oct98 		BlueArtilleryBAND		=	0x2B00,
//TempCode MS 14Oct98 		RedTroopBAND			=	0x2B80,
//TempCode MS 14Oct98 		BlueTroopBAND			=	0x2C80,
//TempCode MS 14Oct98 		RedHQBAND				=	0x2D80,
//TempCode MS 14Oct98 		BlueHQBAND				=	0x2DA0,
//TempCode MS 14Oct98 		RedBoatBAND				=	0x2DC0,
//TempCode MS 14Oct98 		BlueBoatBAND			=	0x2DE0,
//TempCode MS 14Oct98 		GreenBoatBAND			=	0x2E00,
//TempCode MS 14Oct98 		EventBand				=	0x2E20,
//TempCode MS 14Oct98 		GreenVetoedBAND			=	0x2F20,	
//TempCode MS 14Oct98 		GreenMobileBAND			
//TempCode MS 14Oct98 	  	GreenMiscBand
												
	{						 									//MS 14Oct98
		PilotedAcBAND			=	0x0000,	
		WayPointBAND			=	0x0100,			
		MissileBAND				=	0x0400,		WayPointBANDEND = MissileBAND,
		LandscapeBAND			=	0x0600,
		RedRailBand				=	0x0800,
		RedRoadBAND				=	0x0C00,
		RedAcBAND				=	0x0E00,
		BlueAcBAND				=	0x1000,
		AmberAirfieldBAND		=	0x1200,		BlueAcBANDEND= AmberAirfieldBAND,		
		RedFakeAcBAND			=	0x1400,		AmberAirfieldBANDEND=RedFakeAcBAND,
		RedAAASiteBAND			=	0x1500,			
		BlueAAASiteBAND			=	0x1700,
		RedAAALargeBAND			=	0x1900,
  		AmberCivilianBAND		=	0x1A00,	//needs to be bigger
		AmberSupplyBAND			=	0x2500, 
		RedRepairBAND			=	0x2650,
		AmberBridgeBAND			=	0x2700,
		AmberMYardBAND			=	0x2800,
		AmberBattleNodeBAND		=	0x2880,
		RedTrainBAND			=	0x2B00,		AmberBattleNodeBANDEND=RedTrainBAND,
		RedTruckBAND			=	0x2C00,
		RedTruckParkBAND		=	0x2E00,
		RedTroopBAND			=	0x2F00,
		BlueTroopBAND			=	0x2F20,
		RedArmourBAND			=	0x2F40,
		BlueArmourBAND			=	0x2F60,
		RedArtilleryBAND		=	0x2F80,
		BlueArtilleryBAND		=	0x2FB0,
		RedCombatVehicleBAND 	=	0x2FD0,
		BlueCombatVehicleBAND	=	0x3000,
		EventBAND				=	0x3380,
		GreenVetoedBAND			=	0x3400,
		GreenMobileBAND			=	0x3480,
	  	GreenMiscBAND			=	0x3500,
		RedHQBAND				=	0x3580,
		BlueHQBAND				=	0x3600,
		RedBoatBAND				=	0x3680,
		BlueBoatBAND			=	0x3700,
		GreenBoatBAND			=	0x3780,
		RedStaticAcBAND			=	0x3800,
		BlueStaticACBAND		=	0x3840,

		RunwaySBAND				=	0x3880,
		RunwayEBAND				=	0x38C0,


		AfHangerBAND			=	0x3900,		RunwayEBANDEND=AfHangerBAND, //DAW 16/04/99
		AfRevetmentBAND			=	0x3940,
		AfSupplyBAND			=	0x3980,
		AfRunwayBAND			=	0x3B80,
		AfNoScoreBAND			=	0x3C80,		AfRunwayBANDEND=AfNoScoreBAND,


		NextBAND				=	0x3D00,
		LastBAND				=	0x3f00,
//THESE ARE OLD BANDS I AM KEEPING FOR THE MOMENT SO SYSTEM WILL COMPILE
		RedMilitaryBAND			=	0x3F01,						//MS 30Apr99
		BlueMilitaryBAND		=	0x3F02,						//MS 30Apr99
		RedAirfieldBAND			=	0x3FAE,						//MS 30Apr99
		BlueAirfieldBAND		=	0x3FAF,						//MS 30Apr99
		RedPortBAND				=	0x3FB0,
		BLuePortBAND			=	0x3FB8,
		RedCCCBAND				=	0x3FC0,
		BlueCCCBAND				=	0x3FC8,
		RedGICBAND				=	0x3FD0,
		BlueGICBAND				=	0x3FD8,
		RedSAMBAND				=	0x3FF0,						
		BlueSAMBAND				=	0x3FF8,
//END OF TEMP BANDS
		IllegalBAND				=	0x3fff,
	};
#endif
//;;This bit is auto-generated:	
//This bit is auto-generated:	NOT ANY MORE!!!

enum	UniqueID
	{
		#include	"uidvals.g"
		UID_Null				=	0x000,
		UID_NULL				=	0x000,
		PilotedSepID			=	0x000,
		IllegalSepID			=	0x3fff,
		AbsolutingSepID			=	0xffff
	};
//;;------------------------------------------------------------------------------
//inline UniqueIDBand	operator+(UniqueID u) {return (UniqueIDBand) u;}
//inline UniqueID	operator+(UniqueIDBand u) {return (UniqueID) u;}
//------------------------------------------------------------------------------


#endif
