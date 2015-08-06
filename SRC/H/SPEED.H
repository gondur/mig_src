//------------------------------------------------------------------------------
//Filename       speed.h
//System         
//Author         R. Hyde 
//Date           Wed 19 Jun 1996
//Description    
//------------------------------------------------------------------------------
#ifndef	SPEED_Included
#define	SPEED_Included

#define	DEFAULT_SPEED 0



//speeds in 10cm/s units
enum	speeds	{												//JIM 18Dec96
				MPH00	=	0,
				MPHHALF=	3,									//RJS 15Dec96
				MPH02  =	9,
				MPH05  =	22,
				MPH10  =	45,
				MPH15  =	67,
				MPH30  =	134,	 
				MPH40  =	179,	 
				MPH45  =	201,	 
				MPH50  =	224,	 
				MPH55  =	246,
				MPH70	=	308,
				MPH80	=	357,
				MPH100 =	447,
				MPH140 = 	626,
				MPH200 = 	894,
				MPH250 = 	1118,
				MPH400 =	1788,
				MPH450 =	2011,

				WINDSTEPSIZE = MPH05,
				MAXWINDSPEED = MPH15,
				BESTCLIMBSPEED = 246,
				TAKEOFFSPEED = MPH140,
				SPEEDOFBULLET = 9140, 

				CORNERSPEED = MPH250,
				SUSTAINEDTURNSPEED = MPH400,
				MINIMUMCOMBATSPEED = MPH200
				};			


#endif
