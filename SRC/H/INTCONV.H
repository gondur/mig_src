//------------------------------------------------------------------------------
//Filename       intconv.h
//System         
//Author         Martin Alderton
//Date           Wed 24 Jan 1996
//Description    
//------------------------------------------------------------------------------
#ifndef	INTCONV_Included
#define	INTCONV_Included

#define	DEFAULT_INTCONV 0

//TempCode MGA 26Jan96 #include "textref.h"

struct GetRetVal
{
  	ULong			value;
  	Bool			furtherindirection;
  	CharOutputForm	outputform;
};

	GetRetVal getoneval(TextRef* &);
	GetRetVal getval(TextRef);
	GetRetVal getval(GetRetVal&, TextRef);
	
	GetRetVal getval(TextConst);
	GetRetVal getval(TextAddr);
	GetRetVal getval(GetRetVal&, TextOffset);
	GetRetVal getval(TextAddr, TextOffset);
	TextBuild Conv(GetRetVal);
	TextBlockPtr loadintblock(TextRef );
	char *	  TextintDeref(TextBlockPtr, TextRef);

#endif
