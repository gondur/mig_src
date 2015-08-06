//------------------------------------------------------------------------------
//Filename       ctimeout.h
//System         
//Author         Andy McMaster
//Date           Fri 27 Nov 1998
//Description    Timeout stuff for comms, whenever need to do a timeout
//				 create a new timeout object! That way dont get silly 
//				 overwrites, hopefully!! 
//------------------------------------------------------------------------------
#ifndef	CTIMEOUT_Included
#define	CTIMEOUT_Included

#define	DEFAULT_CTIMEOUT 0

#include	"dosdefs.h"

class CommsTimeout
{
private:
	ULong	start;
	ULong 	end;

public:

	CommsTimeout(ULong now, ULong len)
	{
		Init(now,len);
//		start=now;
//		end=now+len;
	}

	~CommsTimeout()
	{
	}

	void	Init(ULong now, ULong len)
	{
		start=now;
		end=now+len;
	}

	bool	TimedOut(ULong now)
	{
		if (now>end)
			return true;

		return false;
	}
};

#endif
