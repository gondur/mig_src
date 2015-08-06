//------------------------------------------------------------------------------
//Filename       shpweap.h
//System         
//Author         Robert Slater
//Date           Wed 16 Apr 1997
//Description    Data relating weapon launcher shapes to aircraft shapes
//
//
//				Weight 	is in 0.01 kg
//				Drag	is in Newtons
//
//		Tip-Tanks are 100lb each
//		
//------------------------------------------------------------------------------
#ifndef	SHPWEAP_Included
#define	SHPWEAP_Included

#define	DEFAULT_SHPWEAP 0

#define MaxWeapTypes	8

typedef struct	weaplist
{
	LnchrType	lnchr;
	UWord		StationShape[2];			// Left & Right		//RJS 17May99
	SLong		Weight;											//RJS 24Apr98
	SLong		Drag;											//RJS 24Apr98
}
WeapListType, *WeapListTypeP;

typedef struct	shptoweaptype
{
	ShapeNum		LchShape;
	WeapListType	LchList[MaxWeapTypes];	
}
ShpToWeapType, *ShpToWeapTypeP;

//DeadCode RJS 13May98 typedef struct	shptoweight
//DeadCode RJS 13May98 {
//DeadCode RJS 13May98 	LnchrType	lnchr;
//DeadCode RJS 13May98 	SLong		unitweight;										//RJS 24Apr98
//DeadCode RJS 13May98 	SLong		drag;											//RJS 24Apr98
//DeadCode RJS 13May98 }
//DeadCode RJS 13May98 ShpToWeight, *ShpToWeightP;

static ShpToWeapType	ShpToWeap[] =
{
	{F86,
	{{LT_FUEL, 	{{F86FU},{F86FU}},		4535970,	1250	},//1685	},//RJS 21May99
	 {LT_ROCKET,{{F86RTL},{F86RTR}},	6350000,	63		},		//RJS 13May98
	{LT_NAPALM,{{F86BMB},{F86BMB}},		45359230,	600		},//1375	},		//RJS 13May98
	{LT_BOMB,	{{F86BMB},{F86BMB}},	22680000,	425		},//45359230,	1375	},		//RJS 13May98
	 {LT_BULLET,{{0},{0}},	13500,		0		},				//RJS 17May99
	 {LT_CONTACT,{{0},{0}},	0,		0	}}},					//RJS 17May99

	{F84,
	{{LT_FUEL, 	{{F84FUL},{F84FUR}},	4535970,	1250	},//1685	},//RJS 21May99
	 {LT_ROCKET4,{{F80RT},{F80RT}},		6350000,	63		},	//MS 03Dec98
	 {LT_ROCKET6,{{F84RT},{F84RT}},		6350000,	63		},	//MS 03Dec98
	{LT_NAPALM,{{F84NAP},{F84NAP}},		45359230,	600		},//1375	},	//RJS 02Dec98
	{LT_BOMB,	{{F84BMB},{F84BMB}},	22680000,	425		},//45359230,	1375	},		//RJS 13May98
	 {LT_BULLET,{{0},{0}},	13500,		0		},				//RJS 17May99
	 {LT_BOMB1000,{{F84B10},{F84B10}},	45359230,	600		},//1375	},	//MS 09Nov98
	 {LT_CONTACT,{{0},{0}},	0,		0	}}},					//RJS 17May99

	{F80,
	{{LT_FUEL, 	{{F80FUL},{F80FUR}},	4535970,	1250	},//1685	},//RJS 21May99
	{LT_ROCKET4,{{F80RT},{F80RT}},		6350000,	63		},		//RJS 13May98
	{LT_NAPALM,{{F80NAP},{F80NAP}},		45359230,	600		},//1375	},	//RJS 02Dec98
	{LT_BOMB500,	{{F80BMB},{F80BMB}},22680000,	425		},//45359230,	1375	},//MS 11Nov98
	 {LT_BOMB1000,{{F80B10},{F80B10}},	45359230,	600		},//1375	},	//MS 09Nov98
	 {LT_BULLET,{{0},{0}},	13500,		0		},				//RJS 17May99
	 {LT_CONTACT,{{0},{0}},	0,		0	}}},					//RJS 17May99

	{F51,
	{{LT_FUEL, 	{{F51FU},{F51FU}},		4535970,	1250	},//1685	},//RJS 21May99
	 {LT_ROCKET,{{F51RTL},{F51RTR}},	6350000,	63		},		//RJS 13May98
	{LT_NAPALM,{{F51NAP},{F51NAP}},		45359230,	600		},//	1375	},	//RJS 02Dec98
	{LT_BOMB,	{{F51BMB},{F51BMB}},	22680000,	425		},//45359230,	1375	},		//RJS 13May98
	 {LT_BULLET,{{0},{0}},	13500,		0		},				//RJS 17May99
	 {LT_BOMB1000,{{F51B10},{F51B10}},	45359230,	600		},//1375	},	//MS 09Nov98
	 {LT_CONTACT,{{0},{0}},	0,		0	}}},					//RJS 17May99


#define MIGWEAP													\
	{{LT_FUEL, 	{{M15FU},{M15FU}},		4535970,	1685	},	 \
	 {LT_CANNON2,{{DUMMY1},{DUMMY1}},	0,	0		},			  \
	 {LT_NAPALM,{{F86BMB},{F86BMB}},	45359230,	1375	},	   \
	 {LT_BOMB,	{{F86BMB},{F86BMB}},	45359230,	1375	},		\
	 {LT_CANNON,{{DUMMY1},{DUMMY1}},	0,		0	},				 \
	 {LT_BULLET,{{0},{0}},	13500,		0		},		  \
	 {LT_CONTACT,{{0},{0}},	0,		0	}}				   

	{MIG15,MIGWEAP},
	{CMIG15,MIGWEAP},
	{M15SHD,MIGWEAP},
	{SUPMIG,MIGWEAP},

	{(ShapeNum)0,
	{{LT_FUEL, 	{{F86FU},{F86FU}},0,0},							//RJS 24Apr98
	 {LT_ROCKET,{{F86RTL},{F86RTR}},0,0},						//RJS 24Apr98
	 {LT_NAPALM,{{F86BMB},{F86BMB}},0,0},						//RJS 24Apr98
	 {LT_BOMB,	{{F86BMB},{F86BMB}},0,0},						//RJS 24Apr98
	 {LT_BULLET,{{0},{0}},0,0},									//RJS 17May99
	 {LT_CONTACT,{{0},{0}},0,	0}}},							//RJS 17May99

};

//This should now get filled in by Init Launcher routine using above values
//DeadCode RJS 13May98 static	ShpToWeight	WeapWeights[] =
//DeadCode RJS 13May98 {
//DeadCode RJS 13May98 	{LT_BOMB,0,0},												//RJS 24Apr98
//DeadCode RJS 13May98 	{LT_FUEL,0,0},												//RJS 24Apr98
//DeadCode RJS 13May98 	{LT_ROCKET,0,0},											//RJS 24Apr98
//DeadCode RJS 13May98 	{LT_NAPALM,0,0},											//RJS 24Apr98
//DeadCode RJS 13May98 	{LT_CONTACT,0,0}											//RJS 24Apr98
//DeadCode RJS 13May98 };

#endif
