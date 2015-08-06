//------------------------------------------------------------------------------
//Filename       buffer.h
//System         
//Author         Andy McMaster
//Date           Tue 28 Apr 1998
//Description    Circular buffer used for comms
//------------------------------------------------------------------------------
#ifndef	BUFFER_Included
#define	BUFFER_Included

#define	DEFAULT_BUFFER 0

#include	"dosdefs.h"

template<class T,SWord size>
class CBuffer
{
private:
	T*	start;	// entry 0
	T*	curr;	// current entry
	T*	next;	// next entry
	T*	temp;	// temp

	SLong	entries;	//curr number of entries
	SLong	currpos;
	SLong	nextpos;
	SLong	temppos;
	SLong	maxentries;


public: 

	CBuffer()
	{
		start=curr=next=new T[maxentries=size];
		entries=nextpos=currpos=temppos=0;
	}

	~CBuffer()
	{
		delete [] start;
	}

	T*	GetCurr()
	{
		return curr;
	}

	void	UpdateCurr()
	{
		entries--;
		currpos++;

		if (currpos==maxentries) //size)
		{
			curr=start;
			currpos=0;
		}
		else
			curr++;
	}

	T*	GetNext()
	{
		return next;
	}

	void	InitNext()
	{
		next=curr;
		nextpos=currpos;
	}

	void	UpdateNext()
	{
		nextpos++;

		if (nextpos==maxentries) //size)
		{
			next=start;
			nextpos=0;
		}
		else
			next++;
	}

	void InitBuffer()
	{
		entries=0;
		next=curr;
		nextpos=currpos;
	}

	SLong	NumEntries()
	{
		return entries;
	}

//	void	SetTemp()
	void	SetTempCurr() // be more specific as to what temp is being set to
	{
		temp=curr;
		temppos=currpos;
	}

	void	SetTempNext()
	{
		temp=next;
		temppos=nextpos;
	}

	T* 	GetTemp()
	{
		return temp;
	}

	void	UpdateTemp()
	{
		temppos++;

		if (temppos==maxentries) //size)
		{
			temp=start;
			temppos=0;
		}
		else
			temp++;
	}

	void	AddEntry()
	{
		entries++;
	}

	void	AddEntryAndUpdateNext()
	{
		AddEntry();
		UpdateNext();
	}

	void	TempPrev()
	{
		temppos--;

		if (temppos<0)
		{
			temppos=maxentries-1;
			temp=start;
			temp+=(maxentries-1);
		}
		else
		{
			temp--;
		}
	}
};


#endif
