//------------------------------------------------------------------------------
//Filename       mouse.h
//System         
//Author         Jim Taylor
//Date           Tue 30 Jan 1996
//Description    class to drive mouse updates
//------------------------------------------------------------------------------
#ifndef	MOUSE_Included
#define	MOUSE_Included

#define	DEFAULT_MOUSE 0

extern	class	Mouse
{
	UWord	RealTime;
	UByte	RTC;
	UWord	lasttime;
public:
	void 	Move(int mouseshape=0);

}	_Mouse;


#endif
