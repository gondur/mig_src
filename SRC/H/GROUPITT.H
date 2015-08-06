//------------------------------------------------------------------------------
//Filename       groupitt.h
//System         
//Author         Robert Slater
//Date           Mon 15 Feb 1999
//Description    
//------------------------------------------------------------------------------
#ifndef	GROUPITT_Included
#define	GROUPITT_Included

#define	DEFAULT_GROUPITT 0

//
// Itterator object for stepping through groups.
// It will be set up with:
//	ShapeNum-			Always-		Shapenumber for group
//	animdataptr-		Optional-	pointer to runtime animdata
//	deadBlockItterator*	Optional-	pointer to savegame info
//
//	This should set itself up with info for the first element
//	immediately available.
//
//	
//
//



class	DeadStream;
class	DeadStream::DeadBlockItterator;
struct ITEM_STATUS;
struct GroupItterator
{
	CON	GroupItterator(ShapeNum	s)								//RJS 21Apr99
	{	group=shape=s;deadstream=NULL;
		//need to fill in data for first element!

		deadittpostlauncherdata = NULL;							//RJS 16Feb00
		deadittfirstbyteptr = NULL;								//RJS 16Feb00

		InitGroupFields();
	}
	CON	GroupItterator(ShapeNum	s,animptr& anim)
	{	group=shape=s;animdata=anim;deadstream=NULL;
		//need to fill in data for first element!

		deadittpostlauncherdata = NULL;							//RJS 16Feb00
		deadittfirstbyteptr = NULL;								//RJS 16Feb00

		InitGroupFields();
	}
	CON	GroupItterator(ShapeNum	s,DeadStream::DeadBlockItterator* d)
	{	
		deadittpostlauncherdata = NULL;							//RJS 16Feb00
		deadittfirstbyteptr = NULL;								//RJS 16Feb00

		group=shape=s;											//RJS 21Apr99
		if (d)
		{
			deadstream=DeadIttCopy(d);
			deadittfirstbyteptr=&deadittfirstbyte;
			NextDeadIttElt(deadstream,deadittfirstbyte,deadittpostlaunchercount,deadittpostlauncherdata);
		}
		else
			deadstream=d;
		int deadstreamblocksize=-1;
		//need to fill in data for first element!

		InitGroupFields();
	}

	DES ~GroupItterator()
	{	DeadIttDelete(deadstream);}

//THE FOLLOWING VARIABLES CAN BE ITERROGATED DIRECTLY
	ShapeNum	group,			//go back to group for some fn calls...
				shape;			//fill in so can be confirmed quickly
	int			status;			//2 bit status field
	int			percentdamage;	//current element points
	Coords3D	delta;			//fill in from group delta x,y,z in CM
	bool		hitlimit;										//RJS 15Feb99

//THE FOLLOWING FUNCTIONS ALLOW THE ITTERATOR TO ITTERATE
//DeadCode RJS 15Feb99 	bool	operator++(int);//		{status++;return (status<10);}				
	bool	operator++(int)
	{
		bool rv;
		if (noelements<=1)
		{
			rv=false;
			hitlimit=true;
		}
		else
		{
			rv=NextElement();
			if (rv && deadstream)
				NextDeadIttElt(deadstream,deadittfirstbyte,deadittpostlaunchercount,deadittpostlauncherdata);
		}
		return(rv);	// no wrap.
	}				
	//move on to next element? 
	//if not NULL Push animdata,grpindexer, and deadstream forward
	operator bool()	{return (!hitlimit);}	//reached end of group?

//THE FOLLOWING FUNCTIONS GET MORE INFORMATION ABOUT THE GROUP
	int			NumElts();					//how many elements in the group
	int			MaxDamagePoints();
	void		MaxKillTime(ITEM_STATUS&);	//highest value for howlongdead.
//THE FOLLOWING FUNCTIONS GET MORE INFORMATION ABOUT THE CURRENT ELEMENT
	int			EltAnimDataSize();			//mem needed for current shape
	int			EltLauncherDataSize(animptr&);	//skip this much to get past launchers (always 1 or more)
	int			PostLauncherDataSize();		//remaining animdata
	UByte&		AnimDataByte();				//that first byte
	MinAnimData&	AnimDataMAD();
	char*		PostLauncherDataLoc();		//the bit after the launchers
	void		ResetLaunchers();			//clean up any counters?
	int			DamageWeight();
	bool		IsStoresToken();
private:					
	//call these routines to move and read deaditterator
static 	DeadStream::DeadBlockItterator*	DeadIttCopy(DeadStream::DeadBlockItterator*);
static 	void	DeadIttDelete(DeadStream::DeadBlockItterator*);
static 	void	NextDeadIttElt(DeadStream::DeadBlockItterator*,UByte&di1b,int&diplc,char*&dipld);

	UByte		deadittfirstbyte;
	UByte*		deadittfirstbyteptr;

	int			deadittpostlaunchercount;
	char*		deadittpostlauncherdata;

	void		InitGroupFields();								//RJS 15Feb99
	bool		NextElement();									//RJS 15Feb99

	ULong		totalpoints;									//RJS 15Feb99
	int			noelements;										//RJS 15Feb99
	animptr		baseanimdata;									//RJS 21Apr99
	animptr		animdata;										//RJS 21Apr99
	char*		grpindexer;
	char*		basegrpindexer;
	DeadStream::DeadBlockItterator* deadstream;
};


struct DamageDef
{
	UniqueID	memberid;
	UniqueID	loadedid;
	ITEM_STATUS	status;
	ITEM_STATUS	worstdamage;
	ShapeNum	shape;
	MinAnimData	firstanimbyte;
	int			animbytesskip,animbyteslen;
	char*		remaininganimbytes;
};

#endif

