//------------------------------------------------------------------------------
//Filename       contlist.h
//System         
//Author         Jim 
//Date           Sun 27 Oct 1996
//Description    Contour list cache.
//				 This tells a truck how to move along
//------------------------------------------------------------------------------
#ifndef	CONTLIST_Included
#define	CONTLIST_Included

#define	DEFAULT_CONTLIST 0

//
// The basis of this list is to give a vertical shift to the truck every
// 40M or less as it passes over contour points in the tile.
// Each shift is either to the next horizontal or vertical separation.
// The separations are every 4096cm	(40m)
// The table is refilled each time a new tile edge is crossed
// The tile edjes are every 129072cm (1.3km)
//

struct	ContourList
{
	ContourList()	{allocatednext=allocatedlist;allocatedlist=this;}
static
	void	FreeList();
	SWord	velx,velz;			//25.6m/s is only 50mph! Good enough for pitch though
	SLong	tilex,tilez;		
	int		currind;		
	SByte	vely[64];		//worst case: just off 45 deg needs 60 readings I think
							
	SWord	GetVVel(FormationItemPtr	it);
	void	MakeNewTable(FormationItemPtr	it);
static	
	ContourList*	allocatedlist;
	ContourList*	allocatednext;

};





#endif
