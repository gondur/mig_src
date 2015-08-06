//------------------------------------------------------------------------------
//Filename       bitftmp.h
//System         
//Author         Jim Taylor
//Date           Thu 18 Jan 1996
//Description    Bit field class using templates
//------------------------------------------------------------------------------
#ifndef	BITFTMP_Included
#define	BITFTMP_Included
	#include	<assert.h>
	#include	"hardpasm.h"
#define	DEFAULT_BITFTMP 0

class	BitFieldErrors2
{
protected:
void	errorcheck(int val,int min,int max)
	{assert ((val<=max && val>=min) && ("Bit field index out of range"));}
};

/////////////////////////////
template	<class counttype,int minval,int maxval>
//
// This was...
//  #define MakeBitField(BitField,counttype,minval,maxval)
//
// Usage was...
//	MakeBitField(newstructname,oldenumname,rangemin,rangemax)
//
// Usage is now...
//  typedef BitField<oldenumname,rangemin,rangemax>	newstructname;
//
/////////////////////////////
class	BitField:protected BitFieldErrors2
{

public:													
enum	fieldsize	{	MAX=maxval,MIN=minval,			
						RANGE=(maxval-minval)+1,		
						BYTES=(maxval-minval+8)/8		
					};									
private:												
char	dataspace[BYTES];
public:						
CON	BitField()
	{
		int i;					
		for (i=BYTES;i--;)		
			dataspace[i]=0;		
	}

BitField&	operator	|=(counttype	s)
{									
	errorcheck(s,MIN,MAX);			
	BITSET(dataspace,s-MIN);		
	return(*this);					
}
/*squillions more functions...*/
};
#endif
