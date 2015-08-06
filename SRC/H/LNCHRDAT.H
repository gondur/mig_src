//------------------------------------------------------------------------------
//Filename       lnchrdat.h
//System         
//Author         Paul.   
//Date           Mon 1 Apr 1996
//Description    
//------------------------------------------------------------------------------
#ifndef	LNCHRDAT_Included
#define	LNCHRDAT_Included

#define	DEFAULT_LNCHRDAT 0

struct	LaunchInfo
{
	LnchrType	lnchrtype;										//RJS 12May97
	UWord		muzlvel;
	UByte		firingdelay;									//RJS 23Jul98
	UByte		burstcount;										//RDH 31Jul98
	ShapeNum	theShape;										//RJS 27Jul98
};

static LaunchInfo	launcherdata[] =							//RJS 27May99
{																//RJS 27May99
	{LT_BULLET,9143,5,24,BULLET},								//RJS 27May99
	{LT_CANNON,6900,10,5,DUMMY1},								//RJS 27May99	//CSB 04/06/99	
	{LT_CANNON2,6900,15,6,DUMMY1},								//RJS 27May99
	{LT_ROCKET4,0,50,0,ROCKET},									//RJS 27May99
	{LT_ROCKET6,0,50,0,ROCKET},									//RJS 27May99
	{LT_ROCKET8,0,50,0,ROCKET},									//RJS 27May99
	{LT_BOMB,0,50,0,BOMB},										//RJS 27May99
	{LT_BOMB500,0,50,0,BMB500},									//RJS 27May99
	{LT_BOMB1000,0,50,0,BMB100},								//RJS 27May99
	{LT_NAPALM,0,50,0,DUMY10},									//RJS 27May99
	{LT_BOMBB29,0,150,0,BOMB29},								//RJS 17Jun99
	{LT_BMB1B29,0,150,0,BMB129},								//RJS 17Jun99
	{LT_CONTACT,0,0,0}											//RJS 27May99
};																//RJS 27May99

#endif
