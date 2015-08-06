//------------------------------------------------------------------------------
//Filename       weappak.h
//System         
//Author         Robert Slater
//Date           Wed 8 Apr 1998
//Description    
//
//	F86:
//			300 rounds per gun, 3 guns on each side of nose
//------------------------------------------------------------------------------
#ifndef	WEAPPAK_Included
#define	WEAPPAK_Included

#define	DEFAULT_WEAPPAK 0

#define	MaxPackNo	10


typedef struct	lchinfo
{
	LnchrType	lnchrtype;
	SLong		ammocount;
}
LchrInfo, *LchrInfoP;

struct	lchpak;
typedef struct	lchpak
{
	LchrInfo	stationlaunchers[4];
	int			WeapSetName;
	int			StringResources[4][2];
	int			TotalDrag;
}
LchrPak, *LchrPakP;

typedef struct	weappak
{
	ShapeNum	shape;
	LchrPak		weappack[MaxPackNo];
}
WeapPakType, *WeapPakTypeP;

	
#ifndef	MAKE_WEAPPACKS	
extern	WeapPakType	ShpToWeapPak[];
#else
WeapPakType	ShpToWeapPak[] =
{	 //ordered by flyinit.h PlaneTypeSelect	ignoring F86 variants
	{F86,	
		{
			{
				{	{LT_BULLET,	900},	{LT_CONTACT,	0},	{LT_FUEL,	35850000},	{LT_CONTACT,	0}	},
				IDS_WEAP_FUEL,
				{	{IDS_FUEL,250},{IDS_NONE},{IDS_NONE},{IDS_UNITSG}	},
				2500	
			},
			{	
				{	{LT_BULLET,	900},	{LT_ROCKET4,	4},	{LT_FUEL,	35850000},	{LT_CONTACT,	0}	},
				IDS_WEAP_ROCKFUEL,
				{	{IDS_ROCKETS,8},{IDS_FUEL,250},{IDS_NONE},{IDS_UNITSG}	},
				3004
			},
			{	
				{	{LT_BULLET,	900},	{LT_CONTACT,	0},	{LT_CONTACT,	0},		{LT_CONTACT,	0}	},
				IDS_WEAP_BASIC,
				{{IDS_NONE},{IDS_NONE},{IDS_NONE}	},
				0
			},
			{	{	{LT_CONTACT,	0},	{LT_CONTACT,	0},	{LT_CONTACT,	0},		{LT_CONTACT,	0}	}	},
			{	{	{LT_CONTACT,	0},	{LT_CONTACT,	0},	{LT_CONTACT,	0},		{LT_CONTACT,	0}	}	},
			{	{	{LT_CONTACT,	0},	{LT_CONTACT,	0},	{LT_CONTACT,	0},		{LT_CONTACT,	0}	}	}
		}
	}, 
	{F84,
		{
			{
				{	{LT_BULLET,	900},	{LT_CONTACT,	0},	{LT_CONTACT,	0},		{LT_FUEL,	68700000}	},
				IDS_WEAP_FUEL,
				{	{IDS_FUEL,450},{IDS_NONE},{IDS_NONE},{IDS_UNITSG}	},
				2500
			},
			{	
				{	{LT_BULLET,	900},	{LT_ROCKET4,	4},	{LT_ROCKET6,	6},		{LT_ROCKET6,	6}	},
				IDS_WEAP_ROCKETS,
				{	{IDS_ROCKETS,32},{IDS_NONE},{IDS_NONE},{IDS_UNITSG}	},
				2016
			},
			{	
				{	{LT_BULLET,	900},	{LT_CONTACT,	0},	{LT_ROCKET6,	6},		{LT_FUEL,	68700000}	},
				IDS_WEAP_ROCKFUEL,
				{	{IDS_ROCKETS,12},{IDS_FUEL,450},{IDS_NONE},{IDS_UNITSG}	},	
				3256
			},
			{	
				{	{LT_BULLET,	900},	{LT_BOMB500,	1},	{LT_CONTACT,	0},		{LT_FUEL,	68700000}	},
				IDS_WEAP_BOMBFUEL,
				{	{IDS_BOMB500,2},{IDS_FUEL,450},{IDS_NONE},{IDS_UNITSG}	},
				3350
			},
			{	
				{	{LT_BULLET,	900},	{LT_NAPALM,		1},	{LT_CONTACT,	0},		{LT_FUEL,	68700000}	},
				IDS_WEAP_NAPMFUEL,
				{	{IDS_NAPALM,2},{IDS_FUEL,450},{IDS_NONE},{IDS_UNITSG}	},
				3700
			},
			{	
				{	{LT_BULLET,	900},	{LT_BOMB500,	1},	{LT_ROCKET6,	6},		{LT_CONTACT,	0}	},
				IDS_WEAP_BOMBROCK,
				{	{IDS_BOMB500,2},{IDS_ROCKETS,12},{IDS_NONE},{IDS_UNITSG}	},
				1606
			},
			{	
				{	{LT_BULLET,	900},	{LT_NAPALM,		1},	{LT_ROCKET6,	6},		{LT_CONTACT,	0}	},
				IDS_WEAP_NAPMROCK,
				{	{IDS_NAPALM,2},{IDS_ROCKETS,12},{IDS_NONE},{IDS_UNITSG}	},
				1956
			},
			{	
				{	{LT_BULLET,	900},	{LT_BOMB1000,	1},	{LT_CONTACT,	0},		{LT_FUEL,	68700000}	},
				IDS_WEAP_BOMBFUEL2,
				{	{IDS_BOMB1000,2},{IDS_FUEL,450},{IDS_NONE},{IDS_UNITSG}	},
				3700
			},
			{	
				{	{LT_BULLET,	900},	{LT_BOMB500,	1},	{LT_ROCKET4,	4},		{LT_FUEL,	68700000}	},
				IDS_WEAP_BOMBROCKFUEL,
				{	{IDS_BOMB500,2},{IDS_ROCKETS,8},{IDS_FUEL,450},{IDS_UNITSG}	},
				3854
			}
//DeadCode MS 06May99 		},
//DeadCode MS 06May99 		{{{LT_BULLET,	900},	{LT_NAPALM,		1},	{LT_ROCKET4,	4},		{LT_FUEL,	68700000}},
//DeadCode MS 06May99 		IDS_WEAP_NAPMROCKFUEL,	{{IDS_NAPALM,2},{IDS_ROCKETS,8},{IDS_FUEL,450},{IDS_UNITSG}}
		}
	},
	{F80,
		{	
			{	
				{	{LT_BULLET,	900},	{LT_CONTACT,	0},	{LT_FUEL,	49350000},	{LT_CONTACT,	0}	},
				IDS_WEAP_FUEL,
				{	{IDS_FUEL,330},{IDS_NONE},{IDS_NONE},{IDS_UNITSG}	},
				2500
			},
			{	
				{	{LT_BULLET,	900},	{LT_ROCKET4,	4},	{LT_ROCKET4,	4},		{LT_CONTACT,	0}	},
				IDS_WEAP_ROCKETS,
				{	{IDS_ROCKETS,16},{IDS_NONE},{IDS_NONE},{IDS_UNITSG}	},	
				1008
			},
			{	
				{	{LT_BULLET,	900},	{LT_ROCKET4,	4},	{LT_FUEL,	49350000},	{LT_CONTACT,	0}	},
				IDS_WEAP_ROCKFUEL,
				{	{IDS_ROCKETS,8},{IDS_FUEL,330},{IDS_NONE},{IDS_UNITSG}	},	
				3004
			},
			{	
				{	{LT_BULLET,	900},	{LT_BOMB500,	1},	{LT_FUEL,	49350000},	{LT_CONTACT,	0}	},
				IDS_WEAP_BOMBFUEL,
				{	{IDS_BOMB500,2},{IDS_FUEL,330},{IDS_NONE},{IDS_UNITSG}	},	
				3350
			},
			{	
				{	{LT_BULLET,	900},	{LT_NAPALM,		1},	{LT_FUEL,	49350000},	{LT_CONTACT,	0}	},
				IDS_WEAP_NAPMFUEL,
				{	{IDS_NAPALM,2},{IDS_FUEL,330},{IDS_NONE},{IDS_UNITSG}	},
				3700
			},
			{	
				{	{LT_BULLET,	900},	{LT_BOMB500,	1},	{LT_CONTACT,	0},		{LT_CONTACT,	0}	},
				IDS_WEAP_BOMB,
				{	{IDS_BOMB500,2},{IDS_NONE},{IDS_NONE},{IDS_UNITSG}	},	
				850
			},
			{	
				{	{LT_BULLET,	900},	{LT_NAPALM,		1},	{LT_CONTACT,	0},		{LT_CONTACT,	0}	},
				IDS_WEAP_NAPM,
				{	{IDS_NAPALM,2},{IDS_NONE},{IDS_NONE},{IDS_UNITSG}	},	
				1200
			},
			{	
				{	{LT_BULLET,	900},	{LT_BOMB1000,	1},	{LT_FUEL,	49350000},	{LT_CONTACT,	0}	},
				IDS_WEAP_BOMBFUEL2,
				{	{IDS_BOMB1000,2},{IDS_FUEL,330},{IDS_NONE},{IDS_UNITSG}	},
				3700
			},
			{	
				{	{LT_BULLET,	900},	{LT_BOMB1000,	1},	{LT_CONTACT,	0},		{LT_CONTACT,	0}	},
				IDS_WEAP_BOMB2,
				{	{IDS_BOMB1000,2},{IDS_NONE},{IDS_NONE},{IDS_UNITSG}	},	
				1200
			}
		}
	},

	{F51,
		{
			{
				{	{LT_BULLET,	940},	{LT_FUEL,	32300000},	{LT_CONTACT,0},		{LT_CONTACT,	0}	},
				IDS_WEAP_FUEL,
				{	{IDS_FUEL,220},{IDS_NONE},{IDS_NONE},{IDS_UNITSG}	},	
				2500
			},
			{
				{	{LT_BULLET,	940},	{LT_CONTACT,	0},		{LT_ROCKET,	3}, {LT_CONTACT, 0}	},
				IDS_WEAP_ROCKETS,
				{	{IDS_ROCKETS,6},{IDS_NONE},{IDS_NONE},{IDS_UNITSG}	},	
				378
			},
			{	
				{	{LT_BULLET,	940},	{LT_FUEL,	32300000},		{LT_ROCKET,	3}, {LT_CONTACT, 0}	},
				IDS_WEAP_ROCKFUEL,
				{	{IDS_ROCKETS,6},{IDS_FUEL,220},{IDS_NONE},{IDS_UNITSG}	},	
				2878
			},
			{	
				{	{LT_BULLET,	940},	{LT_BOMB500,	1},	{LT_CONTACT,	0},		{LT_CONTACT,	0}	},
				IDS_WEAP_BOMB,
				{{IDS_BOMB500,2},{IDS_FUEL,220},{IDS_NONE},{IDS_UNITSG}	},	
				850
			},
			{	
				{	{LT_BULLET,	940},	{LT_NAPALM,	1},	{LT_CONTACT,	0},		{LT_CONTACT,	0}	},
				IDS_WEAP_NAPM,
				{	{IDS_NAPALM,2},{IDS_NONE},{IDS_NONE},{IDS_UNITSG}	},	
				1200
			},
			{	
				{	{LT_BULLET,	940},	{LT_BOMB500,	1},	{LT_ROCKET,	3},		{LT_CONTACT,	0}	},
				IDS_WEAP_BOMBROCK,
				{{IDS_BOMB500,2},{IDS_ROCKETS,6},{IDS_NONE},{IDS_UNITSG}	},	
				1228
			},
			{	
				{	{LT_BULLET,	940},	{LT_NAPALM,	1},	{LT_ROCKET,		3},		{LT_CONTACT,	0}	},
				IDS_WEAP_NAPMROCK,
				{{IDS_NAPALM,2},{IDS_ROCKETS,6},{IDS_NONE},{IDS_UNITSG}	},	
				1578
			},
			{	
				{	{LT_BULLET,	940},	{LT_BOMB1000,	1},	{LT_CONTACT,	0},		{LT_CONTACT,	0}	},
				IDS_WEAP_BOMB2,
				{{IDS_BOMB1000,2},{IDS_NONE},{IDS_NONE},{IDS_UNITSG}	},	
				1200
			}
		}
	},
	{F82
	},
	{B26,	//2 centre stores....
		{
			{
				{	{LT_BOMB500,	4},	{LT_CONTACT,		7},	{LT_CONTACT, 0},	{LT_CONTACT,	0}	},
				IDS_WEAP_BOMB,
				{	{IDS_BOMB500,8},{IDS_NONE},{IDS_NONE},{IDS_UNITSG}	},	
				0
			},
			{	
				{	{LT_BOMB1000,	2},	{LT_CONTACT,	0},	{LT_CONTACT, 0},	{LT_CONTACT,	0}	},
				IDS_WEAP_BOMB2,
				{	{IDS_BOMB1000,4},{IDS_NONE},{IDS_NONE},{IDS_UNITSG}	},	
				0
			}
		}	
	},
	{B29,
		{	
			{	
				{	{LT_BOMBB29,	2},	{LT_CONTACT,		8},	{LT_CONTACT, 0},	{LT_CONTACT,	0}},
				IDS_WEAP_BOMB,
				{	{IDS_BOMB500,40},{IDS_NONE},{IDS_NONE},{IDS_UNITSG}	},	
				0
			},
			{	
				{	{LT_BOMBB29,	1},	{LT_CONTACT,	0},	{LT_CONTACT, 0},	{LT_CONTACT,	0}},
				IDS_WEAP_BOMB2,
				{	{IDS_BOMB1000,20},{IDS_NONE},{IDS_NONE},{IDS_UNITSG}	},	
				0
			}
		}
	},
	{YAK9,														//MS 17May99
		{
			{
				{	{LT_BULLET,	900},	{LT_CONTACT,	0},	{LT_CONTACT,	0},	{LT_CONTACT,	0}	},
				IDS_WEAP_BASIC,
				{	{IDS_NONE},{IDS_NONE},{IDS_NONE},{IDS_UNITSG}	},	
				0
			}
		}
	},

		//JIM 28/04/99
#define	MIGPACK	\
	{	{{	{LT_CANNON,	160},	{LT_CANNON2,	40},{LT_CONTACT,	0},		{LT_CONTACT,	0}},\
		IDS_WEAP_ROCKFUEL,	{{IDS_ROCKETS,8},{IDS_FUEL,350},{IDS_NONE},{IDS_UNITSG}},	0			 \
		},																						  \
		{{	{LT_CANNON,	160},	{LT_CANNON2,	40},{LT_FUEL,	35400000},	{LT_CONTACT,	0}},   \
		IDS_WEAP_ROCKFUEL,	{{IDS_ROCKETS,8},{IDS_FUEL,350},{IDS_NONE},{IDS_UNITSG}},	2500				\
	}}

	{MIG15,	MIGPACK},
	{M15SHD,MIGPACK},
	{CMIG15,MIGPACK},
	{SUPMIG,MIGPACK},

	{(ShapeNum)0}
};
#endif


#endif
