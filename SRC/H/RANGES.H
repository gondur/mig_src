//------------------------------------------------------------------------------
//Filename       ranges.h
//System         
//Author         R. Hyde 
//Date           Wed 17 Jan 1996
//Description    
//------------------------------------------------------------------------------
#ifndef	RANGES_Included
#define	RANGES_Included

#define	DEFAULT_RANGES 0







enum	rel_altitude {LOWER = 0, SAME_ALT,HIGHER};


//changed to cm from mm									//RDH 27Feb96
enum 	ranges		{
	METRES00 = 0,
	METRES01 = 100,
	METRES02 = 200,												//JIM 09Apr96
	METRES03 = 300,
	METRES04 = 400,												//MS 10Apr96
	METRES05 = 500,
	METRES06 = 600,												//MS 11Apr96
	METRES07 = 700,												//MS 10Apr96
	METRES08 = 800,												//MS 11Apr96
	METRES09 = 900,												//MS 11Apr96
	METRES10 = 1000,
	METRES14 = 1400,
	METRES15 = 1500,
	METRES20 = 2000,
	METRES22_3 = 2230,
	METRES25 = 2500,
	METRES26 = 2600,
	METRES28 = 2800,
	METRES30 = 3000,
	METRES31_3 = 3130,
	METRES32 = 3200,
	METRES35 = 3500,
	METRES40 = 4000,
	METRES42 = 4200,
	METRES44_6 = 4460,
	METRES45 = 4500,
	METRES50 = 5000,
	METRES55 = 5500,
	METRES56 = 5600,
	METRES60 = 6000,
	METRES62_6 = 6260,
	METRES65 = 6500,
	METRES66_9 = 6690,
	METRES70 = 7000,
	METRES75 = 7500,
	METRES78 = 7800,
	METRES80 = 8000,
	METRES84 = 8400,
	METRES85 = 8500,
	METRES89_2 = 8920,
	METRES90 = 9000,
	METRES95 = 9500,
	METRES100 = 10000,
	METRES105 = 10500,
	METRES110 = 11000,											//MS 07May96
	METRES120 = 12000,											//MS 07May96
	METRES130 = 13000,											//MS 07May96
	METRES133_8 = 13380,											//MS 07May96
	METRES135 = 13500,											//MS 29Nov96
	METRES140 = 14000,											//MS 11Apr96
	METRES150 = 15000,											//MS 11Apr96
	METRES160 = 16000,											//MS 11Apr96
	METRES165 = 16500,											//MS 29Nov96
	METRES180 = 18000,											//MS 29Nov96
	METRES190 = 19000,											//MS 11Apr96
	METRES200 = 20000,
	METRES210 = 21000,
	METRES220 = 22000,
	METRES230 = 23000,
	METRES240 = 24000,											//MS 08Apr96
	METRES250 = 25000,											//MS 08Apr96
	METRES260 = 26000,											//MS 08Apr96
	METRES280 = 28000,											//MS 08Apr96
	METRES300 = 30000,
	METRES310 = 31000,
	METRES313 = 31300,
	METRES350 = 35000,											//MS 11Apr96
	METRES400 = 40000,
	METRES450 = 45000,											//MS 11Apr96
	METRES500 = 50000,
	METRES550 = 55000,											//MS 06May96
	METRES600 = 60000,
	METRES650 = 65000,
	METRES700 = 70000,
	METRES750 = 75000,
	METRES800 = 80000,
	METRES850 = 85000,
	METRES900 = 90000,
	METRES950 = 95000,
	METRES1000 = 100000,
	METRES1100 = 120000,										//MS 06May96
	METRES1200 = 120000,
	METRES1250 = 125000,
	METRES1300 = 130000,
	METRES1400 = 140000,
	METRES1500 = 150000,
	METRES1600 = 160000,										//MS 06May96
	METRES1700 = 170000,
	METRES1800 = 180000,
	METRES1900 = 190000,
	METRES2000 = 200000,
	METRES2500 = 250000,										//MS 06Jun96
	METRES3000 = 300000,
	METRES4000 = 400000,
	METRES4500 = 450000,										//MS 07Oct96
	METRES5000 = 500000,
	METRES5500 = 550000,										//MS 15Aug96
	METRES6000 = 600000,										//MS 06Jun96
	METRES7000 = 700000,										//MS 14Aug96
	METRES8000 = 800000,
	KM1 =		 100000,			
	KM10 =		1000000,			
	METRES10KM =1000000,
	METRES15KM =1500000,
	METRES20KM =2000000,
	METRES30KM =3000000,
	METRES40KM =4000000,
	METRES50KM =5000000,
	METRES60KM =6000000,
	METRES70KM =7000000,
	METRES80KM =8000000,
	METRES90KM =9000000,
	METRES100KM=10000000,
	METRES150KM=15000000,
	METRES200KM=20000000,
	METRES250KM=25000000,
	METRES500KM=50000000,
	MILES01	=  185196,
	MILES02	=  370392,
	MILES03	=  555588,
	MILES04	=  740784,
	MILES05	=  925980,
	MILES10	= 1850000,
	MILES15	= 2775000,
	MILES20	= 3700000,
	MILES25	= 4625000,
	MILES30	= 5550000,
	MILES35	= 6475000,
	MILES40	= 7400000,
	MILES45	= 8325000,
	MILES50	= 9250000,
	MILES100=18500000,
	MILES150=27750000,
	MILES200  = 37039200,
	MILES2000 = 370392000,											  //RDH 08/03/99
//DeadCode DAW 02Apr96 	NEGFT_100 = 0,
//DeadCode DAW 02Apr96 	NEGFT_500 = 0,
//DeadCode DAW 02Apr96 	NEGFT_1000 = 0,
//DeadCode DAW 02Apr96 	NEGFT_2000 = 0,	

	FT_0	= 0,												//DAW 02Apr96
	FT_1	= 30,												//DAW 02Apr96
	FT_2	= 60,												//DAW 02Apr96
	FT_3	= 92,												//MS 08May96
	FT_5	= 150,
	FT_6	= 183,												//ARM 16Jun97
	FT_10	= 305,
	FT_20	= 609,												//MS 07Apr96
	FT_25	= 750,												//DAW 02Apr96
	FT_30	= 900,												//DAW 02Apr96
	FT_40	= 1219,												//MS 08Apr96
	FT_50	= 1500,												//DAW 02Apr96
	FT_60	= 1829,												//DAW 02Apr96
	FT_75	= 2286,												//MS 11Apr96
	FT_80	= 2438,												//MS 07May96
	FT_94	= 2865,												//MS 07May96
	FT_95	= 2895,												//MS 07May96
	FT_96	= 2926,												//MS 07May96
	FT_100	= 3048,
	FT_105	= 3200,												//MS 11Apr96
	FT_120	= 3658,												//MS 18Sep96
	FT_150	= 4572,												//MS 07May96
	FT_200	= 6096,
	FT_250	= 7620,												//MS 08Apr96
	FT_300	= 9144,												//MS 08Apr96
	FT_400	= 12192,											//MS 08Apr96
	FT_500	= 15240,											//MS 08Apr96
	FT_550 	= 16764,											//MS 05May96
	FT_600	= 18288,											//MS 10Apr96
	FT_700  = 21336,											//MS 05May96
	FT_750	= 22860,											//MS 08Apr96
	FT_770	= 23469,											//MS 03May96
	FT_800	= 24384,											//MS 05May96
	FT_820	= 24993,											//MS 06May96
	FT_830	= 25298,											//MS 06May96
	FT_850	= 25908,											//MS 05May96
	FT_900	= 27432,											//MS 05May96

	FT_1000	= 30480,
	FT_1100 = 33528,											//MS 14Apr99
	FT_1200	= 36576,
	FT_1250 = 38100,
	FT_1300 = 39624,											//MS 14Apr99
	FT_1400 = 42672,											//MS 14Apr99
	FT_1500	= 45720,
	FT_1600 = 48768,											//MS 14Apr99
	FT_1700 = 51816,											//MS 14Apr99

	FT_1800	= 54864,

	FT_2000	= 60960,
	FT_2200	= 67056,											//MS 08Apr96
	FT_2500	= 76200,											//MS 03Jul96
	FT_2800	= 85344,											//MS 07Apr96
	FT_2900	= 88392,											//MS 07Apr96
	FT_2950	= 89916,											//MS 07Apr96

	FT_3000	= 91440,
	FT_3015	= 91897,											//MS 10Apr96
	FT_3025	= 92202,											//MS 10Apr96
	FT_3050	= 92964,											//MS 07Apr96
	FT_3100	= 94488,											//JIM 05Apr96
	FT_3200	= 97536,											//MS 05Apr96
	FT_3400	= 103632,											//MS 05Apr96
	FT_3500	= 106680,											//MS 05Apr96
	FT_3750	= 114300,
	FT_3600	= 109728,											//MS 07Apr96
	FT_3900	= 118872,											//MS 07Apr96
	FT_3950	= 120396,											//MS 07Apr96

	FT_4000	= 121920,
	FT_4050	= 123444,											//JIM 04Dec96
	FT_4300	= 129000,
	FT_4950	= 150876,											//MS 25Apr96

	FT_5000 = 152400,
	FT_5950 = 181356,											//MS 25Apr96

	FT_6000 = 182880,
	FT_6450 = 196596,											//MS 25Apr96
	FT_6500 = 198120,											//MS 25Apr96

	FT_7000 = 200000,

	FT_8000 = 243840,

	FT_8500 = 259080,

	FT_9000 = 274320,

	FT_10000 = 304800,

	FT_12000 = 365760,											//RDH 07Nov96

	FT_14000 = 426720,											//MS 18Apr96

	FT_15000 = 457200,

	FT_16000 = 487680,											//MS 18Apr96

	FT_17000 = 500000,
	FT_18000 = 548640,
	FT_20000 = 609600,

	FT_25000 = 762000,											//ARM 28Aug97
	FT_30000 = 914400,	
	FT_35000 = 1066800,											//ARM 20Aug97
	FT_34000 = 1036333,										//CSB 01/07/99	
	FT_40000 = 1219200,												  //RDH 30/06/99
	FT_45000 = 1371600,

	FT_60000 = 1828800,											//ARM 15May97
	
	HIGHESTGROUND=256000,										//PD 19Mar99

//	LOWESTSAFEALT=HIGHESTGROUND+FT_2000,						//PD 19Mar99

//DeadCode PD 19Mar99 	HIGHESTGROUND = 304800,										//RDH 27Mar98

//DeadCode DAW 02Apr96 	IDENTRANGE		= 300000,
//DeadCode RDH 27Mar98 	BREAKOFFRANGE	= 250000,									//RDH 19Aug96
//DeadCode RDH 27Mar98 	COMBATRANGE 	= 25000,
//DeadCode RDH 27Mar98 	SHOOTINGRANGE   = 15000,									//RDH 02Oct96
	BALLOON_ALT		=	60960,
	SUNELEVDIST	=	0x048000,

	WIND_DIRECTION_CHANGE = 1066800,		//35000ft
	IDEALCOMBATRANGE = 30000,
	OUTERCOMBATRANGE = 150000,
//Following ranges define the maximum at which the condition holds
	CONTRAILRANGE = 3200000,			//if < then contrails can be seen
	VISIBLERANGE = 1280000,			//if < then bogey can be seen
	RECOGNISERANGE  = 480000,		//if < then can distinguish between bandit and friendly
	BREAKOFFRANGE =  480000,		//far enough away to safely break off
	REDUCEDVISIBILITY = 640000,		//used in Seen()
	COMBATRANGE = 320000,			//pre combat: can decide to engage or not
	ENGAGERANGE= 150000,		//combat manoeuvres: must attack or defend
	DANGERRANGE  = 75000,		//must defend self
	WEAPONSRANGE = 50000,		//inside range of guns
	INSIDEWEAPONSRANGE = 40000,		//well inside weaponrange
	COLLISIONRANGE = 30000,		//inside this range must avoid collision
	THRUST_0_RANGE = 21000,							//point when thrust goes to 0 to avoid collision
	BREAKTURNRADIUS = 60000

	};





#endif
