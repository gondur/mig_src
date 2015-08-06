//------------------------------------------------------------------------------
//Filename       h2h.h
//System         
//Author         R. Hyde 
//Date           Thu 5 Sep 1996
//Description    
//------------------------------------------------------------------------------
#ifndef	H2H_Included
#define	H2H_Included

#define	DEFAULT_H2H 0

enum	{BF_H2HRandom = 0, BF_H2Himplode, BF_H2Hexplode,BF_H2Hmax = 3};
//50 chars max fit on screen!!
enum	{MAXNUMOFPLAYERS = 8, MAXNUMOFDIALOGUECHARS = 100, MAXNUMOFGAMENAMECHAR = 12};

enum	{
		NAMEX = PIXEL640 * 10,
		NAMEY = PIXEL640 * 274,
		NAMEW = PIXEL640 * 130,
		NAMEH = PIXEL640 * 18,

		STATUSX = NAMEX + NAMEW,
		STATUSY = NAMEY,
		STATUSW = PIXEL640 * 40,
		STATUSH = NAMEH,

		DIALOGUEX = STATUSX + STATUSW,
		DIALOGUEY = NAMEY,
		DIALOGUEW = PIXEL640 * 360,
		DIALOGUEH = NAMEH,

		KILLSX = DIALOGUEX + DIALOGUEW,
		KILLSY = NAMEY,
		KILLSW = PIXEL640 * 50,
		KILLSH = NAMEH,

		DEATHSX = KILLSX + KILLSW,
		DEATHSY = NAMEY,
		DEATHSW = PIXEL640 * 40,
		DEATHSH = NAMEH


		};


#endif
