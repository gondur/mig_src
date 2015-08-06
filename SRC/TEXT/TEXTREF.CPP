/*
	 MiG Alley
	 Copyright (C) 1998, 1999, 2000, 2001 Empire Interactive (Europe) Ltd,
	 677 High Road, North Finchley, London N12 0DA

	 Please see the document licence.doc for the full licence agreement

2. LICENCE
 2.1 	
 	Subject to the provisions of this Agreement we now grant to you the 
 	following rights in respect of the Source Code:
  2.1.1 
  	the non-exclusive right to Exploit  the Source Code and Executable 
  	Code on any medium; and 
  2.1.2 
  	the non-exclusive right to create and distribute Derivative Works.
 2.2 	
 	Subject to the provisions of this Agreement we now grant you the
	following rights in respect of the Object Code:
  2.2.1 
	the non-exclusive right to Exploit the Object Code on the same
	terms and conditions set out in clause 3, provided that any
	distribution is done so on the terms of this Agreement and is
	accompanied by the Source Code and Executable Code (as
	applicable).

3. GENERAL OBLIGATIONS
 3.1 
 	In consideration of the licence granted in clause 2.1 you now agree:
  3.1.1 
	that when you distribute the Source Code or Executable Code or
	any Derivative Works to Recipients you will also include the
	terms of this Agreement;
  3.1.2 
	that when you make the Source Code, Executable Code or any
	Derivative Works ("Materials") available to download, you will
	ensure that Recipients must accept the terms of this Agreement
	before being allowed to download such Materials;
  3.1.3 
	that by Exploiting the Source Code or Executable Code you may
	not impose any further restrictions on a Recipient's subsequent
	Exploitation of the Source Code or Executable Code other than
	those contained in the terms and conditions of this Agreement;
  3.1.4 
	not (and not to allow any third party) to profit or make any
	charge for the Source Code, or Executable Code, any
	Exploitation of the Source Code or Executable Code, or for any
	Derivative Works;
  3.1.5 
	not to place any restrictions on the operability of the Source 
	Code;
  3.1.6 
	to attach prominent notices to any Derivative Works stating
	that you have changed the Source Code or Executable Code and to
	include the details anddate of such change; and
  3.1.7 
  	not to Exploit the Source Code or Executable Code otherwise than
	as expressly permitted by  this Agreement.

questions about this file may be asked at http://www.simhq.com/
*/

//------------------------------------------------------------------------------
//Filename       textref.cpp
//System         
//Author         Jim Taylor
//Date           Mon 6 Nov 1995
//Description    management for textrefs - implementation!
//------------------------------------------------------------------------------

#include	<string.h>
#include	<stdio.h>
#include	"dosdefs.h"
#define		F_BATTLE											//JIM 01Aug96
#include	"fileman.h"
#include	"textrefl.h"
#include	"textref.h"
#include	"myerror.h"
//#include	"wrapper.h"
#include	"display.h"
#include	"savegame.h"
#include	<stdio.h>


static	TextIndirectBlock	Temp_Blocks[6];
	TextIndirectBlock::TextIndirectBlock()
{
int	i;
	for	(i=255;i--;)	textstarters[i]=NULL;
	type=TEXTTYPE_Build;
	parameters=0;
	lastelement=255;
}

//
// This stuff is all to do with managing texts until we can do it properly
// A very little is permanent, but most is garbage.
//
//
//


Text	_Text;


////////////////////////////////////////////////////////////////////////////////////////////////////
	TextB::TextB()	{loadedblock=NULL;}
	TextB::~TextB()	{delete loadedblock;loadedblock=NULL;};


	Text::Text():
		TextB()
{	//Cheaty fixup for run-time mem ref blocks
int	i;
	for (i=6;i--;)
		loadedblocks[(TextBuildMIN>>8)+i]=&(Temp_Blocks[i]);
	currtextbuild=&(Temp_Blocks[0]);
	permbase=(TextRef)TextPermMIN;
	loadedblocks[permbase>>8]->lastelement=50;

	LoadTextBlocks();
};



//
// That stuff all needs rewriting when the data files exist
//
//
//
//

///////////////////////////////////////////////////////////////////////

TextBlockPtr	TextB::loadtextblock(TextRef	textsnip)
{	//attempts to load in  block if not already fixed up
TextBlockPtr
	retval=loadedblocks[textsnip>>8];
	if (retval==0)
	{
	 	//load it in... if one loaded already then check if same, otherwise delete
		if ((TextRef)textsnip>TextRef_LastLoadable)
			_Error.EmitSysErr("Requested dynamic text block number too high!");
		if (loadedblock)
			delete	loadedblock;
		loadedblock=new fileblock ((FileNum) (FIL_TEXTBLOCKSTART+1+(textsnip>>8)));//DAW 10Jan96
		retval=(TextBlockPtr) getdata(loadedblock);
		//Note: not actually added to table 'cos not permanent
	}
	return(retval);
}

///////////////////////////////////////////////////////////////////////
char*		TextB::TextDeref(TextBlockPtr	tmptextblock,TextRef textref)
{
 	if (tmptextblock->type==TEXTTYPE_Snip0)
	{
TextSnipBlock
		*tmpsnip=(TextSnipBlock*) tmptextblock;
		assert( ((textref&0xff)<=tmptextblock->lastelement)&&
				("Low level index wrong!"));
		return (& (tmpsnip->textdatas[tmpsnip->textstarters[textref&0xff]]));
	}
	else
 	if (tmptextblock->type==TEXTTYPE_Snipn)
	{
TextSnipBlock
		*tmpsnip=(TextSnipBlock*) tmptextblock;
		assert( ((textref&0xff)<=tmptextblock->lastelement)&&
				("Low level index wrong!"));
		return (& (tmpsnip->textdatas[tmpsnip->textstarters[textref&0xff]]));
	}
	else
	if (tmptextblock->type==TEXTTYPE_Build)
	{
		assert( (((TextIndirectBlock*) tmptextblock)->textstarters[textref&0xff])
				&&("Low level index wrong!"));
		return (((TextIndirectBlock*) tmptextblock)->textstarters[textref&0xff]);
	}
	//else
		_Error.EmitSysErr("Low level error: Only basic types derefable here! (%04X)",textref);
		return(NULL);
}

char*		TextB::TextDeref(TextRef textref)
{	//This only works with loaded blocks - thats why it's a secret!
TextBlockPtr	tmptextblock=loadedblocks[textref>>8];
	assert((tmptextblock)&&("Only loaded text blocks work at this level"));
	assert((tmptextblock->lastelement>=(textref&0xff))&&("Low level fail: text num too high!"));
 	return(TextDeref(tmptextblock,textref));
}


void	TextB::TextBuildAlloc(ULong size,TextBuild& newtextref,string& newtextptr)
{
int	i=0;
	while(currtextbuild->textstarters[i]) i++;
	assert((i<50)&&("Over 50 temporary strings... can handle 250 but want limmit."));
	currtextbuild->textstarters[i]=
		newtextptr=
			new char [size];
	newtextref=(TextBuild) (TextBuildMIN+i);
}

void	TextB::TextBuildFree(TextBuild textref)	//only if it is a textbuild
{
	if ((textref&0xFF00)==TextBuildMIN)
	{
	delete	[]	currtextbuild->textstarters[textref&0x00ff];
	currtextbuild->textstarters[textref&0x00ff]=NULL;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	int	strlen(char* src)
{
int	len=0;
	while (*src)	{src++;len++;}
	return(len);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
////
////	TEXT CONVERSION ROUTINES - Return a new string allocted in TextBuild:
////
////		Snip0-Snip15: simple parameter replacement
////
////		TextB::Conv 0-3 	are hand written-optimised
////		TextB::Conv	4-15 	translate their parameter list to an array
////
////
////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	TextBuild	TextB::Conv(TextSnipBlock	*currtextblock,TextSnip0 textsnip)
{
//first, check it really is legal snip0
int	textsnipi=textsnip&0x00ff;
	if (textsnipi>currtextblock->lastelement)
		_Error.EmitSysErr("Text number too high in page: %04X (max %d)",
						textsnip,(textsnipi>currtextblock->lastelement));
string
	src=&(currtextblock->textdatas[currtextblock->textstarters[textsnipi]]),
	trg;
int	len=strlen(src)+1;
TextBuild
	tb;
	TextBuildAlloc(len,tb,trg);
	while (len--)	*trg++=*src++;
	return(tb);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	TextBuild	TextB::Conv(TextSnipBlock	*currtextblock,TextSnip1 textsnip,TextBuild tr1)
{
//first, check it really is legal snip0
int	textsnipi=textsnip&0x00ff;
	if (textsnipi>currtextblock->lastelement)
		_Error.EmitSysErr("Text number too high in page: %04X (max %d)",
						textsnip,(textsnipi>currtextblock->lastelement));
string
	src=&(currtextblock->textdatas[currtextblock->textstarters[textsnipi]]),
	srcr1=TextDeref((TextRef)tr1),
	trg;

int	len=strlen(src)+1-2+strlen(srcr1);		//+1='\0' -2='%1'

TextBuild
	tb;
	TextBuildAlloc(len,tb,trg);
	while (((UWord*) src)[0]!=((UWord*)("%1"))[0])
		*(trg++)=*(src++);
	while (*srcr1)
		*(trg++)=*(srcr1++);
	src+=2;
	while (*src)
		*(trg++)=*(src++);
	*(trg)=0;
	TextBuildFree(tr1);
	return(tb);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	TextBuild	TextB::Conv(TextSnipBlock	*currtextblock,TextSnip2 textsnip,TextBuild tr1,TextBuild tr2)
{
//first, check it really is legal snip0
int	textsnipi=textsnip&0x00ff;
	if (textsnipi>currtextblock->lastelement)
		_Error.EmitSysErr("Text number too high in page: %04X (max %d)",
						textsnip,(textsnipi>currtextblock->lastelement));
string
	src=&(currtextblock->textdatas[currtextblock->textstarters[textsnipi]]),
	srcr1=TextDeref((TextRef)tr1),
	srcr2=TextDeref((TextRef)tr2),
	trg;

int	len=strlen(src)+1-4+strlen(srcr1)+strlen(srcr2);		//+1='\0' -4='%1%2'

TextBuild
	tb;
	TextBuildAlloc(len,tb,trg);
	while ((*src!='%')&&(*src))
		*(trg++)=*(src++);
	while(*src)
	{
		if	(src[1]=='1')
			{
			while (*srcr1)
				*(trg++)=*(srcr1++);
			src+=2;
			}
		else
		if	(src[1]=='2')
			{
			while (*srcr2)
				*(trg++)=*(srcr2++);
			src+=2;
			}
		else
			*(trg++)=*(src++);
		while ((*src!='%')&&(*src))
			*(trg++)=*(src++);
	}
	*(trg)=0;
	TextBuildFree(tr1);
	TextBuildFree(tr2);
	return(tb);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	TextBuild	TextB::Conv(TextSnipBlock	*currtextblock,TextSnip3 textsnip,TextBuild tr1,TextBuild tr2,TextBuild tr3)
{
//first, check it really is legal snip0
int	textsnipi=textsnip&0x00ff;
	if (textsnipi>currtextblock->lastelement)
		_Error.EmitSysErr("Text number too high in page: %04X (max %d)",
						textsnip,(textsnipi>currtextblock->lastelement));
string
	src=&(currtextblock->textdatas[currtextblock->textstarters[textsnipi]]),
	srcr1=TextDeref((TextRef)tr1),
	srcr2=TextDeref((TextRef)tr2),
	srcr3=TextDeref((TextRef)tr3),
	trg;

int	len=strlen(src)+1+strlen(srcr1)+strlen(srcr2)+strlen(srcr3)-6;

TextBuild
	tb;
	TextBuildAlloc(len,tb,trg);
	while ((*src!='%')&&(*src))
		*(trg++)=*(src++);
	while(*src)
	{
		if	(src[1]=='1')
			{
			while (*srcr1)
				*(trg++)=*(srcr1++);
			src+=2;
			}
		else
		if	(src[1]=='2')
			{
			while (*srcr2)
				*(trg++)=*(srcr2++);
			src+=2;
			}
		else
		if	(src[1]=='3')
			{
			while (*srcr3)
				*(trg++)=*(srcr3++);
			src+=2;
			}
		else
			*(trg++)=*(src++);
		while ((*src!='%')&&(*src))
			*(trg++)=*(src++);
	}
	*(trg)=0;
	TextBuildFree(tr1);
	TextBuildFree(tr2);
	TextBuildFree(tr3);
	return(tb);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	TextBuild	TextB::Conv(TextSnipBlock* currtextblock,TextRef textsnip,int numparams,TextBuild params[])
{
//first, check it really is legal snip0
int	textsnipi=textsnip&0x00ff;
	if (textsnipi>currtextblock->lastelement)
		_Error.EmitSysErr("Text number too high in page: %04X (max %d)",
						textsnip,(textsnipi>currtextblock->lastelement));

string
	src=&(currtextblock->textdatas[currtextblock->textstarters[textsnipi]]),
	insert,
	trg;
int	len=strlen(src)+1-numparams*2;					//Work out used length
int	i;
	for(i=numparams;i--;)
		len=len+strlen(TextDeref((TextRef)params[i]));		//Work out total length

TextBuild
	tb;
	TextBuildAlloc(len,tb,trg);
	while ((*src!='%')&&(*src))
		*(trg++)=*(src++);
	while(*src)
	{
		i=src[1]-'1';
		if ((i==-1) && (numparams>9))
		{
			i=10+src[2]-'0';
			if (i<=numparams)
			{
				insert=TextDeref((TextRef)params[i]);
				while (*insert)
					*(trg++)=*(insert++);
				TextBuildFree(params[i]);
				params[i]=(TextBuild)	-1;
				src+=3;
			}
		}
		else
		if ((i>=0) && (i<numparams))
		{
			insert=TextDeref((TextRef)params[i]);
			while (*insert)
				*(trg++)=*(insert++);
			TextBuildFree(params[i]);
			params[i]=(TextBuild)	-1;
			src+=2;
		}
		else
			*(trg++)=*(src++);

		while ((*src!='%')&&(*src))
			*(trg++)=*(src++);
	}
	*(trg)=0;
	return(tb);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
TextBuild	Text::Conv(TextSnip0 textsnip)
{
TextSnipBlock*	currblock=(TextSnipBlock*)	loadtextblock((TextRef)textsnip);
	if (currblock==0)
		_Error.EmitSysErr("Text block not loaded! (%04X)",textsnip);
	if (currblock->type!=TEXTTYPE_Snip0)
		_Error.EmitSysErr("Text block not snip 0! (%04X)",textsnip);
	if (currblock->parameters!=0)
		_Error.EmitSysErr("Text block not zero parameters in snip0! (%04X)",textsnip);
	return(TextB::Conv(currblock,textsnip));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
TextSnipBlock*	TextB::loadsnipblock(TextRef	textsnip,int	expectedparams)
{
TextSnipBlock*	currblock=(TextSnipBlock*) loadtextblock(textsnip);
	if (currblock==0)
		_Error.EmitSysErr("Text block not loaded! (%04X)",textsnip);
	if (currblock->type!=TEXTTYPE_Snipn)
		_Error.EmitSysErr("Text block not SnipN! (%04X)",textsnip);
	if (currblock->parameters!=expectedparams)
		_Error.EmitSysErr("Text block not %d parameters in SnipN! (%04X)",expectedparams,textsnip);
	return(currblock);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
TextBuild	Text::Conv(TextSnip1 textsnip,TextBuild p1)
{
TextSnipBlock*	currblock=loadsnipblock((TextRef)textsnip,1);
	return(TextB::Conv(currblock,textsnip,p1));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
TextBuild	Text::Conv(TextSnip2 textsnip,TextBuild p1,TextBuild p2)
{
TextSnipBlock*	currblock=loadsnipblock((TextRef)textsnip,2);
	return(TextB::Conv(currblock,textsnip,p1,p2));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
TextBuild	Text::Conv(TextSnip3 textsnip,TextBuild p1,TextBuild p2,TextBuild p3)
{
TextSnipBlock*	currblock=loadsnipblock((TextRef)textsnip,3);
	return(TextB::Conv(currblock,textsnip,p1,p2,p3));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
TextBuild	Text::Conv(TextSnip4 textsnip,TextBuild p1,TextBuild p2,TextBuild p3,TextBuild p4)
{
TextSnipBlock*	currblock=loadsnipblock((TextRef)textsnip,4);
TextBuild	tmp[]={p1,p2,p3,p4};
	return(TextB::Conv(currblock,(TextRef)textsnip,4,tmp));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
TextBuild	Text::Conv(TextSnip5 textsnip,TextBuild p1,TextBuild p2,TextBuild p3,TextBuild p4,TextBuild p5)
{
TextSnipBlock*	currblock=loadsnipblock((TextRef)textsnip,5);
TextBuild	tmp[]={p1,p2,p3,p4,p5};
	return(TextB::Conv(currblock,(TextRef)textsnip,5,tmp));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
TextBuild	Text::Conv(TextSnip6 textsnip,	TextBuild p1,TextBuild p2,TextBuild p3,TextBuild p4,TextBuild p5,
											TextBuild p6
					)
{
TextSnipBlock*	currblock=loadsnipblock((TextRef)textsnip,6);
TextBuild	tmp[]={p1,p2,p3,p4,p5,p6};
	return(TextB::Conv(currblock,(TextRef)textsnip,6,tmp));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
TextBuild	Text::Conv(TextSnip7 textsnip,	TextBuild p1,TextBuild p2,TextBuild p3,TextBuild p4,TextBuild p5,
											TextBuild p6,TextBuild p7
					)
{
TextSnipBlock*	currblock=loadsnipblock((TextRef)textsnip,7);
TextBuild	tmp[]={p1,p2,p3,p4,p5,p6,p7};
	return(TextB::Conv(currblock,(TextRef)textsnip,7,tmp));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
TextBuild	Text::Conv(TextSnip8 textsnip,	TextBuild p1,TextBuild p2,TextBuild p3,TextBuild p4,TextBuild p5,
											TextBuild p6,TextBuild p7,TextBuild p8
					)
{
TextSnipBlock*	currblock=loadsnipblock((TextRef)textsnip,8);
TextBuild	tmp[]={p1,p2,p3,p4,p5,p6,p7,p8};
	return(TextB::Conv(currblock,(TextRef)textsnip,8,tmp));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
TextBuild	Text::Conv(TextSnip9 textsnip,	TextBuild p1,TextBuild p2,TextBuild p3,TextBuild p4,TextBuild p5,
											TextBuild p6,TextBuild p7,TextBuild p8,TextBuild p9
					)
{
TextSnipBlock*	currblock=loadsnipblock((TextRef)textsnip,9);
TextBuild	tmp[]={p1,p2,p3,p4,p5,p6,p7,p8,p9};
	return(TextB::Conv(currblock,(TextRef)textsnip,9,tmp));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
TextBuild	Text::Conv(TextSnip10 textsnip,	TextBuild p1,TextBuild p2,TextBuild p3,TextBuild p4,TextBuild p5,
											TextBuild p6,TextBuild p7,TextBuild p8,TextBuild p9,TextBuild p10
					)
{
TextSnipBlock*	currblock=loadsnipblock((TextRef)textsnip,10);
TextBuild	tmp[]={p1,p2,p3,p4,p5,p6,p7,p8,p9,p10};
	return(TextB::Conv(currblock,(TextRef)textsnip,10,tmp));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
TextBuild	Text::Conv(TextSnip11 textsnip,	TextBuild p1,TextBuild p2,TextBuild p3,TextBuild p4,TextBuild p5,
											TextBuild p6,TextBuild p7,TextBuild p8,TextBuild p9,TextBuild p10,
											TextBuild p11
					)
{
TextSnipBlock*	currblock=loadsnipblock((TextRef)textsnip,11);
TextBuild	tmp[]={p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11};
	return(TextB::Conv(currblock,(TextRef)textsnip,11,tmp));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
TextBuild	Text::Conv(TextSnip12 textsnip,	TextBuild p1,TextBuild p2,TextBuild p3,TextBuild p4,TextBuild p5,
											TextBuild p6,TextBuild p7,TextBuild p8,TextBuild p9,TextBuild p10,
											TextBuild p11,TextBuild p12
					)
{
TextSnipBlock*	currblock=loadsnipblock((TextRef)textsnip,12);
TextBuild	tmp[]={p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12};
	return(TextB::Conv(currblock,(TextRef)textsnip,12,tmp));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
TextBuild	Text::Conv(TextSnip13 textsnip,	TextBuild p1,TextBuild p2,TextBuild p3,TextBuild p4,TextBuild p5,
											TextBuild p6,TextBuild p7,TextBuild p8,TextBuild p9,TextBuild p10,
											TextBuild p11,TextBuild p12,TextBuild p13
					)
{
TextSnipBlock*	currblock=loadsnipblock((TextRef)textsnip,13);
TextBuild	tmp[]={p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13};
	return(TextB::Conv(currblock,(TextRef)textsnip,13,tmp));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
TextBuild	Text::Conv(TextSnip14 textsnip,	TextBuild p1,TextBuild p2,TextBuild p3,TextBuild p4,TextBuild p5,
											TextBuild p6,TextBuild p7,TextBuild p8,TextBuild p9,TextBuild p10,
											TextBuild p11,TextBuild p12,TextBuild p13,TextBuild p14
					)
{
TextSnipBlock*	currblock=loadsnipblock((TextRef)textsnip,14);
TextBuild	tmp[]={p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14};
	return(TextB::Conv(currblock,(TextRef)textsnip,14,tmp));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
TextBuild	Text::Conv(TextSnip15 textsnip,	TextBuild p1,TextBuild p2,TextBuild p3,TextBuild p4,TextBuild p5,
											TextBuild p6,TextBuild p7,TextBuild p8,TextBuild p9,TextBuild p10,
											TextBuild p11,TextBuild p12,TextBuild p13,TextBuild p14,TextBuild p15
					)
{
TextSnipBlock*	currblock=loadsnipblock((TextRef)textsnip,15);
TextBuild	tmp[]={p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15};
	return(TextB::Conv(currblock,(TextRef)textsnip,15,tmp));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
////
////	TEXT CONVERSION ROUTINES - Return a new string allocted in TextBuild:
////
////		List2-List15 lists of varying lengths to choose from by an index integer
////
////		Input should be TextList, but may be TextRef
////		
////		A bad TextList input is not as noisy
////
////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
TextSnip0	TextB::ConvTextList(TextListBlock*	currblock,TextList texttable,ULong	index)
{
	if (currblock->listentries<=index)
		_Error.EmitSysErr("Text list (%04X) is fixed size (%d) indexed by value too high (%d)!",
								texttable,currblock->listentries,index);
	if (currblock->lastelement<(texttable&0x00ff))
		_Error.EmitSysErr("Text list TextRef (%04X) too high for block (Index is ok though!)",texttable);
TextRef
	reqtextref=(TextRef)currblock->lists[(currblock->listentries*(texttable&0x00ff))+index];
	return (TextSnip0)(reqtextref);
}

/////////////////////////////////////////////////////////////////////////////////////
TextBuild	Text::Conv(TextRef texttable,int	index)
{
TextListBlock*	currblock=(TextListBlock*)	loadtextblock(texttable);
	if (currblock==0)
		_Error.EmitSysErr("Text block not loaded! (%04X)",texttable);
	if (currblock->type!=TEXTTYPE_List)
		_Error.EmitSysErr("Text variable (%04X) not resolved to list type - using an integer parameter (%d) is wrong!",
								texttable,index);
	return(Conv(ConvTextList(currblock,(TextList) texttable,index)));
}
/////////////////////////////////////////////////////////////////////////////////////
TextBuild	Text::Conv(TextList texttable,int	index)
{
TextListBlock*	currblock=(TextListBlock*)	loadtextblock((TextRef)texttable);
	if (currblock==0)
		_Error.EmitSysErr("Text block not loaded! (%04X)",texttable);
	if (currblock->type!=TEXTTYPE_List)
		_Error.EmitSysErr("TextList type Text variable (%04X)"
							"not indexing TextList!",texttable);
	return(Conv(ConvTextList(currblock,(TextList) texttable,index)));
}
/////////////////////////////////////////////////////////////////////////////////////
TextSnip0	Text::ConvSnip0(TextList texttable,int	index)
{
TextListBlock*	currblock=(TextListBlock*)	loadtextblock((TextRef)texttable);
	if (currblock==0)
		_Error.EmitSysErr("Text block not loaded! (%04X)",texttable);
	if (currblock->type!=TEXTTYPE_List)
		_Error.EmitSysErr("TextList type Text variable (%04X)"
							"not indexing TextList!",texttable);
	return(ConvTextList(currblock,(TextList) texttable,index));
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
////
////	TEXT CONVERSION ROUTINES - Return a new string allocted in TextBuild:
////
////		Input is a number to be formatted as specified
////		NOTE: Any screwed up replacement stuff ends up here!!
////
////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Conv
//Author		Jim Taylor
//Date			Mon 10 Jun 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
TextBuild	TextB::Conv(TextListBlock* tb,UniqueID uid)
{
	int	g=uid;
	int	h=g/256;
	g=g%256;

TextRef
	reqtextref=(TextRef)tb->lists[h];
	if (reqtextref==0xffff)
		return((TextBuild)reqtextref);
	h=g/16;
	g=g%16;
	reqtextref=(TextRef)tb->lists[(tb->listentries*(reqtextref&0x00ff))+h];
	if (reqtextref==0xffff)
		return((TextBuild)reqtextref);
	h=g;
	reqtextref=(TextRef)tb->lists[(tb->listentries*(reqtextref&0x00ff))+h];
	return((TextBuild)reqtextref);
}

TextBuild	TextB::DummyUID(UniqueID uid)
{
	TextBuild	tb;
	char*	trg;
	TextBuildAlloc(10,tb,trg);	//alloc 1 extra
	*(ULong*) trg=*(ULong*)"(UID";
	sprintf(trg+4,"%04x",uid);
	*(UWord*) (trg+8)=')';
	return(tb);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Conv
//Author		Jim Taylor
//Date			Mon 10 Jun 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
TextSnip0	Text::ConvSnip0(UniqueID uid)
{
//TextListBlock*	currblock=(TextListBlock*)	loadtextblock((TextRef)TEXTUID_namespage);
//	if (currblock==0)
//		_Error.EmitSysErr("UID Text block not loaded!");
//	if (currblock->type!=TEXTTYPE_List)
//		_Error.EmitSysErr("UID Text block not resolved to list type!");
//TextRef
//	reqtextref=(TextRef)TextB::Conv(currblock,uid);
//	if (reqtextref==0xffff)
		return(TEXT_NULL);
//	else
//		return((TextSnip0) reqtextref);
}

TextBuild	Text::Conv(UniqueID uid)
{
	TextSnip0 retstr=ConvSnip0(uid);
	if (retstr!=TEXT_NULL)
	 	return(Conv(retstr));
	else
		return(DummyUID(uid));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Conv
//Author		Jim Taylor
//Date			Tue 14 Nov 1995
//Modified		Wed 24 Jan 1996 by Martin
//
//Modification	Modified to only expect one type of layout (OFORM)
//
//Description	Convert integer to text...
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
TextBuild	Text::Conv(SLong	value2,int	places,CharOutputLayout output)
{
	//1) find out how many places the number takes up
	//4) allocate space
	//7) convert number
   
	char signchar;
	char leadchar;

	
	if (output==OFORM_LZ)
		 leadchar='0';
	else
		 leadchar=' ';
	
int
	dividefactor,
	divideplaces;												//RDH 06Feb96
ULong	value=value2;

	if (output==OFORM_SIGN)										//JIM 08Feb96
		if (output==OFORM_SIGN && value2<0)						//JIM 08Feb96
		{														//JIM 08Feb96
			value=-value2;										//JIM 08Feb96
			signchar='-';										//JIM 08Feb96
		}														//JIM 08Feb96
	else														//JIM 08Feb96
		signchar='+';											//JIM 08Feb96

	if (value==0)
	{
		dividefactor=0;
		divideplaces=0;												//RDH 06Feb96
	}
	if (value>=1000000000)										//JIM 24Jan96
	{															//JIM 24Jan96
		dividefactor=1000000000;								//JIM 24Jan96
		divideplaces=10;										//JIM 24Jan96
	}															//JIM 24Jan96
	else
	{
		dividefactor=1;
		divideplaces=1;												//RDH 06Feb96
int		df2=10;													//JIM 24Jan96
		while	(df2<=value)									//JIM 24Jan96
		{														//JIM 24Jan96
			dividefactor=df2;									//JIM 24Jan96
			df2=dividefactor*10;								//JIM 24Jan96
			divideplaces++;										//JIM 24Jan96
		}														//JIM 24Jan96
	}
	places-=divideplaces;
	if (places<0)	places=0;
string
	trg;
TextBuild
	tb;
	
	if (output==OFORM_SIGN)
	{
		TextBuildAlloc(places+divideplaces+2,tb,trg);	//alloc 1 extra
		*(trg++)=signchar;
	}
	else
		if (output==OFORM_TH)										//JIM 10Oct96
			TextBuildAlloc(places+divideplaces+3,tb,trg);	//alloc 1 extra
		else
			TextBuildAlloc(places+divideplaces+1,tb,trg);			

	while (places--)									//leading spaces
		*(trg++)=leadchar;								//or zeros

	if (divideplaces)
	{
		while (dividefactor>1)								//actual calc.
		{
			*(trg++)=(char) ('0'+(value/dividefactor));				//start with top digit
			value%=dividefactor;							//rather than last
			dividefactor=dividefactor/10;					//too high initially
		}
		*(trg++)=(char) ('0'+value);				//start with top digit//RDH 06Feb96
	}
		if (output==OFORM_TH)
		{
			if (Save_Data.rangediv!=10000)						//DAW 10Dec96
			{
				if ((*(trg-2)=='1')||(*(trg-1)>'3')||*(trg-1)<'1')
				{
					*(trg++)='t';
					*(trg++)='h';
				}
				else
				if (*(trg-1)>'2')
				{
					*(trg++)='r';
					*(trg++)='d';
				}
				else
				if (*(trg-1)=='2')
				{
					*(trg++)='n';
					*(trg++)='d';
				}
				else
				{
					*(trg++)='s';
					*(trg++)='t';
				}
			}
			else												//DAW 06Dec96
			{
				*(trg++)='.';									//DAW 06Dec96
			}
		}

	*trg=0;	
	return(tb);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Conv
//Author		Jim Taylor
//Date			Tue 14 Nov 1995
//
//Description	Convert integer to text...
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
////
////	TEXT CONVERSION ROUTINES - Return a new string allocted in TextBuild:
////
////		Input is a char* c style string - say a filename
////		NOTE: 	THIS ROUTINE IS NOT FOR GENERAL USE. 
////				DO NOT REMOVE THE INT3() OFF THE TOP.
////
////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
TextBuild	Text::Conv(string	src)
{
string
	trg;
int	len=strlen(src)+1;
TextBuild
	tb;
	TextBuildAlloc(len,tb,trg);
	while (len--)	*trg++=*src++;
	return(tb);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
////
////	TEXT PRINT ROUTINES - Output a constructed string to the display:
////
////	Inputs:	screenXY= top left of box, or 'base point' of no screenWH specified
////			screenWH= width and height
////			flags:	alignment control
////
////	Outputs:final cursor position. If y is -ve then text was clipped to height of box
////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CalcLineSplits
//Author		Jim Taylor
//Date			Wed 8 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
int	TextC::CalcLineSplits(	Window* w,char*	text,
							int boxwidth,int SpaceSize,int /*HLeadSize*/,
								char	escchar)
{
int	linenum=0;
int	currx=0;
int	lastx=0;
int	lastxplusspc=0;
char*	lastword=0;
int	words=0;
int	lastwords=0;
int	chars=0;
int	lastchars=0;
char	ch;
	linesplits[linenum].TextStarts=text;
	for (;;)
	{
		ch=*text;
		if (escchar&&ch==escchar)
		{
		 	ch=*++text;
			switch (ch)
			{
			case 's':
			case ' ':	ch='\1';	break;
			case 't':	ch='\t';	break;
			case 'n':	ch='\n';	break;
			}
		}
		while (ch>' ')
		{
			currx+=w->GetCharacterWidth(ch);//PD 29Nov95
			chars++;
			ch=*++text;
			if (escchar&&ch==escchar)
			{
		 		ch=*++text;
				switch (ch)
				{
				case 's':
				case ' ':	ch='\1';	break;
				case 't':	ch='\t';	break;
				case 'n':	ch='\n';	break;
				}
			}
		}
		//we know we are on a word end... the question is, does the word fit?
		//if not put a split in.
		if (currx>boxwidth)
		{
			linesplits[linenum].LineWidthPixels=(UWord)lastx;
			linesplits[linenum].LineWidthChars=(UWord)lastchars;
			linesplits[linenum].NumWords=(SWord)lastwords;
			if (lastwords==0)
			{
				text[20]=0;
				_Error.EmitSysErr("Can't fit this word in box: %s",
									linesplits[linenum].TextStarts);
			}
			currx-=lastxplusspc;
			words-=lastwords;
			chars-=lastchars;
			linenum++;
			linesplits[linenum].TextStarts=lastword;
		}

		words++;
		chars++;
		text++;

		if (ch!='\1')
		{
			lastword=text;
			lastchars=chars;
			lastx=currx;
			lastwords=words;
		}


		switch (ch)
		{
		case	' ':
			lastxplusspc=lastx+SpaceSize;
		case	'\1':
			currx+=SpaceSize;
		break;
		case	'\t':
			currx-=currx%TAB;	//tabs are relative to box! - this line finds previous tab
			currx+=TAB;
			lastxplusspc=currx;
			if (currx>boxwidth)
			{
				text[10]=0;
				_Error.EmitSysErr("Can't fit TAB in box: end of: (%s)",
										linesplits[linenum].TextStarts);
			}
		break;
		case	'\n':
			linesplits[linenum].LineWidthPixels=(UWord)currx;
			linesplits[linenum].LineWidthChars=(UWord)chars;
			linesplits[linenum].NumWords=(SWord)-words;		//stop justification!
			linenum++;
			linesplits[linenum].TextStarts=text;
			chars=words=lastwords=lastx=currx=lastchars=lastxplusspc=0;
		break;
		case	'\0':		//end of text -double break!
			linesplits[linenum].LineWidthPixels=(UWord)currx;
			linesplits[linenum].LineWidthChars=(UWord)chars;
			linesplits[linenum].NumWords=(SWord)words;	//Note: Justification allowed!!!
			return(linenum+1);
		}
	}
}

//FIX10-2//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//FIX10-2//Procedure		PrintLines
//FIX10-2//Author		Jim Taylor
//FIX10-2//Date			Mon 13 Nov 1995
//FIX10-2//
//FIX10-2//Description	
//FIX10-2//
//FIX10-2//Inputs		
//FIX10-2//
//FIX10-2//Returns	
//FIX10-2//
//FIX10-2//------------------------------------------------------------------------------
//FIX10-2ScreenXY	TextC::PrintLines(	Window* w,
//FIX10-2								int	lines,						//how many lines
//FIX10-2								ScreenXY	xy,ScreenWH	wh,		//box sizes
//FIX10-2								PrintFlags	pf,					//format flags
//FIX10-2								int linesep,  					//font size mods
//FIX10-2								int spcwidth,
//FIX10-2								int hleading,
//FIX10-2								char	escchar)
//FIX10-2{
//FIX10-2//should be a call to getpixelinfo here....
//FIX10-2ScreenWH	pwm(w->GetPixelInfo());
//FIX10-2int pwmod=pwm.w,
//FIX10-2	phmod=pwm.h,
//FIX10-2	linenum=0,
//FIX10-2	leftxcoord,
//FIX10-2	currxcoord,
//FIX10-2	currycoord=xy.y,
//FIX10-2	usespcwidth=spcwidth,
//FIX10-2	modspcwidth=0,
//FIX10-2	ofspcwidth=pwmod,
//FIX10-2	usehleading=hleading;			//for alternate justification using leading
//FIX10-2	switch (pf&PF_HAlignMask)
//FIX10-2	{
//FIX10-2	case	PF_HAlignCenter:
//FIX10-2		leftxcoord=xy.x+wh.w/2;
//FIX10-2	break;
//FIX10-2	case	PF_HAlignRight:
//FIX10-2		leftxcoord=xy.x+wh.w;
//FIX10-2	break;
//FIX10-2	case	PF_HAlignLeft:
//FIX10-2	case	PF_HAlignJust:
//FIX10-2		leftxcoord=xy.x;
//FIX10-2	}
//FIX10-2
//FIX10-2	for(linenum=0;linenum!=lines;linenum++)
//FIX10-2	{
//FIX10-2		//get starting pos for line and justified spacing
//FIX10-2		switch (pf&PF_HAlignMask)
//FIX10-2		{
//FIX10-2		case	PF_HAlignCenter:
//FIX10-2			currxcoord=leftxcoord-linesplits[linenum].LineWidthPixels/2;
//FIX10-2		break;
//FIX10-2		case	PF_HAlignRight:
//FIX10-2			currxcoord=leftxcoord-linesplits[linenum].LineWidthPixels;
//FIX10-2			break;
//FIX10-2		case	PF_HAlignJust:
//FIX10-2			if(linesplits[linenum].NumWords>0)
//FIX10-2			{
//FIX10-2				if (linesplits[linenum].NumWords<2)
//FIX10-2				{}
//FIX10-2				else
//FIX10-2					usespcwidth=
//FIX10-2							(wh.w-linesplits[linenum].LineWidthPixels)
//FIX10-2									/*------------------------*/
//FIX10-2								/ (linesplits[linenum].NumWords-1);
//FIX10-2				if (usespcwidth>4*spcwidth)
//FIX10-2
//FIX10-2				modspcwidth=usespcwidth%pwmod;
//FIX10-2				usespcwidth=spcwidth+usespcwidth-modspcwidth;
//FIX10-2			}
//FIX10-2			else
//FIX10-2			{
//FIX10-2				usespcwidth=spcwidth;
//FIX10-2				modspcwidth=0;
//FIX10-2			}
//FIX10-2		case	PF_HAlignLeft:
//FIX10-2			currxcoord=leftxcoord;
//FIX10-2		}
//FIX10-2		//start to print out. Ignore leading for now!
//FIX10-2string	text=linesplits[linenum].TextStarts;
//FIX10-2int		wordcount=linesplits[linenum].NumWords;
//FIX10-2		if (wordcount<0)
//FIX10-2			wordcount=-wordcount;
//FIX10-2		w->SetCharPos((SWord) currxcoord,(SWord) currycoord);//PD 29Nov95
//FIX10-2		while(wordcount--)
//FIX10-2		{
//FIX10-2			char	ch=*text;
//FIX10-2			if (escchar&&ch==escchar)
//FIX10-2			{
//FIX10-2		 		ch=*++text;
//FIX10-2				switch (ch)
//FIX10-2				{
//FIX10-2				case ' ':	ch=' ';		break;	//ignoring hard space for now!
//FIX10-2				case 't':	ch='\t';	break;
//FIX10-2				case 'n':	ch='\n';	break;
//FIX10-2				}
//FIX10-2			}
//FIX10-2			while (ch>' ')
//FIX10-2			{
//FIX10-2				w->CharacterPrint(ch);		//PD 29Nov95
//FIX10-2				ch=*++text;
//FIX10-2				if (escchar&&ch==escchar)
//FIX10-2				{
//FIX10-2		 			ch=*++text;
//FIX10-2					switch (ch)
//FIX10-2					{
//FIX10-2					case ' ':	ch=' ';		break;	//ignoring hard space for now!
//FIX10-2					case 't':	ch='\t';	break;
//FIX10-2					case 'n':	ch='\n';	break;
//FIX10-2					}
//FIX10-2				}
//FIX10-2			}
//FIX10-2			text++;
//FIX10-2			switch (ch)
//FIX10-2			{
//FIX10-2			case	' ':
//FIX10-2				currxcoord=w->GetCharPos();			//PD 29Nov95
//FIX10-2				if ((ofspcwidth-=modspcwidth)<=0)
//FIX10-2				{
//FIX10-2					currxcoord+=pwmod;
//FIX10-2					ofspcwidth+=pwmod;
//FIX10-2				}
//FIX10-2				currxcoord+=usespcwidth;
//FIX10-2				w->SetCharPos((SWord) currxcoord,(SWord) currycoord);//PD 29Nov95
//FIX10-2			break;
//FIX10-2			case	'\t':
//FIX10-2				currxcoord=w->GetCharPos();			//PD 29Nov95
//FIX10-2				currxcoord-=(currxcoord-leftxcoord)%(TAB);	//tabs are relative to box!
//FIX10-2				currxcoord+=TAB;
//FIX10-2				w->SetCharPos((SWord) currxcoord,(SWord) currycoord);//PD 29Nov95
//FIX10-2			break;
//FIX10-2			case	'\n':;		//Should be end of line - wordcount=0
//FIX10-2			}
//FIX10-2		}		
//FIX10-2		xy.x=(SWord)	currxcoord;
//FIX10-2		xy.y=(SWord)	currycoord;
//FIX10-2		currycoord=currycoord+linesep;
//FIX10-2	}
//FIX10-2	return(xy);
//FIX10-2}
//FIX10-2
//FIX10-2//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//FIX10-2//Procedure		Print
//FIX10-2//Author		Jim Taylor
//FIX10-2//Date			Wed 8 Nov 1995
//FIX10-2//
//FIX10-2//Description	This is the print routine that does all the organising... 
//FIX10-2//				this is where they all come to!
//FIX10-2//
//FIX10-2//Inputs		Box definition
//FIX10-2//				Format flags
//FIX10-2//				text string
//FIX10-2//
//FIX10-2//Returns		final cursor position - to help with concatination
//FIX10-2//				if Y value is negative then text didn't fit in box and stopped.
//FIX10-2//------------------------------------------------------------------------------
//FIX10-2ScreenXY	TextB::Print(Window* w,ScreenXY xy,ScreenWH wh,PrintFlags pf,char*	text)
//FIX10-2{
//FIX10-2SWord	spcwidth,ascend,linesep;
//FIX10-2w->GetFontInfo( spcwidth, ascend ,linesep);		//PD 29Nov95
//FIX10-2//should be a call to getpixelinfo here....
//FIX10-2int	pwmod=16;
//FIX10-2int	phmod=16;
//FIX10-2	switch (pf&PF_VLeadMask)
//FIX10-2	{
//FIX10-2	case	PF_SmallVLead:	linesep+=(80&-phmod);		break;
//FIX10-2	case	PF_MedVLead:	linesep+=(160&-phmod);	break;
//FIX10-2	case	PF_BigVLead:	linesep+=(320&-phmod);	break;
//FIX10-2	case	PF_NegVLead:	linesep-=(160&-phmod);	break;
//FIX10-2	case	PF_NoVLead:;
//FIX10-2	}
//FIX10-2
//FIX10-2	switch (pf&PF_SpaceLeadMask)
//FIX10-2	{
//FIX10-2	case	PF_DoubleSpaces:	spcwidth*=2;			break;
//FIX10-2	case	PF_HalfSpaces:		spcwidth=(SWord) (spcwidth/2);	break;
//FIX10-2	case	PF_ZeroSpaces:		spcwidth=0;				break;
//FIX10-2	case	PF_SingleSpaces:;
//FIX10-2	}
//FIX10-2
//FIX10-2char	escchar=(pf&PF_IgnoreBSlash)?0:'\\';
//FIX10-2int	hleading=0;
//FIX10-2	switch (pf&PF_HLeadMask)
//FIX10-2	{
//FIX10-2	case	PF_SmallHLead:		hleading=(8%pwmod);		break;
//FIX10-2	case	PF_MedHLead:		hleading=(16%pwmod);	break;
//FIX10-2	case	PF_BigHLead:		hleading=(32%pwmod);	break;
//FIX10-2	case	PF_NegHLead:		hleading=-(16%pwmod);	break;
//FIX10-2	case	PF_NoHLead:;
//FIX10-2	}
//FIX10-2
//FIX10-2int	i=(pf&PF_BorderSizeMask)*32;	//15-->512=1/50th of screen= 6 low res pixels off border
//FIX10-2	xy.x+=i;	
//FIX10-2	if ((wh.w-=(2*i))<0) wh.w=0;	
//FIX10-2	xy.y+=i;
//FIX10-2	if ((wh.h-=(2*i))<0) wh.h=0;
//FIX10-2	if (pf&PF_VAlignCenter)
//FIX10-2	{	//single line
//FIX10-2		if ((pf&PF_HAlignMask==PF_HAlignJust)&&(wh.w==0))
//FIX10-2			_Error.EmitSysErr("Can't justify text if width is zero! (%s)",text);
//FIX10-2		if (wh.w)
//FIX10-2			if (CalcLineSplits(w,text,wh.w,spcwidth,hleading,escchar)!=1)
//FIX10-2#ifndef NDEBUG
//FIX10-2				_Error.EmitSysErr("Text doesn't fit width (%d): %s",wh.w,text)
//FIX10-2#endif
//FIX10-2					;
//FIX10-2			else;
//FIX10-2		else
//FIX10-2			if (CalcLineSplits(w,text,FULLW,spcwidth,hleading,escchar)!=1)
//FIX10-2				_Error.EmitSysErr("Text doesn't fit width of screen! (%s)",text);
//FIX10-2		//calc vertical centering - don't care about height - never fails
//FIX10-2		if (wh.h)
//FIX10-2			xy.y=(SWord) (xy.y+(wh.h+ascend)/2);
//FIX10-2		return(PrintLines(w,1,xy,wh,pf,linesep,spcwidth,hleading,escchar));
//FIX10-2	}
//FIX10-2	elser	//paragraph
//FIX10-2	if ((wh.w==0) || (wh.h==0))
//FIX10-2		_Error.EmitSysErr("Paragraph aligned text requires a proper box! (%s)",text);
//FIX10-2	elser
//FIX10-2	{
//FIX10-2int		numlines=CalcLineSplits(w,text,wh.w,spcwidth,hleading,escchar);
//FIX10-2		xy.y=(SWord) (xy.y+ascend);
//FIX10-2int		printablelines=wh.h/linesep;
//FIX10-2		if (printablelines<numlines)
//FIX10-2		{
//FIX10-2			assert(printablelines&&"Can't fit 1 line of text in height.");
//FIX10-2			xy=PrintLines(w,printablelines,xy,wh,pf,linesep,spcwidth,hleading,escchar);
//FIX10-2			xy.x=(SWord)0x8000;
//FIX10-2			return(xy);
//FIX10-2		}
//FIX10-2		elser
//FIX10-2			return(PrintLines(w,numlines,xy,wh,pf,linesep,spcwidth,hleading,escchar));
//FIX10-2	}
//FIX10-2}
//FIX10-2
//FIX10-2/////////////////////////////////////////////////////////////////////////////////////
//FIX10-2ScreenXY	Text::Print(Window* w,ScreenXY xy,ScreenWH wh,PrintFlags pf,TextPerm	textref)
//FIX10-2{
//FIX10-2string	tmp=TextDeref((TextRef)textref);
//FIX10-2		if (tmp==NULL)
//FIX10-2			_Error.EmitSysErr("Built text 'not at home'! (%04X)",textref);
//FIX10-2		xy=TextB::Print(w,xy,wh,pf,tmp);
//FIX10-2		TextBuildFree((TextBuild) textref);
//FIX10-2		return(xy);
//FIX10-2};
//FIX10-2/////////////////////////////////////////////////////////////////////////////////////
//FIX10-2ScreenXY	Text::Print(Window* w,ScreenXY xy,ScreenWH wh,PrintFlags pf,TextBuild	textref)
//FIX10-2{
//FIX10-2	return(Print(w,xy,wh,pf,(TextPerm) textref));
//FIX10-2};
//FIX10-2/////////////////////////////////////////////////////////////////////////////////////
//FIX10-2ScreenXY	Text::Print(Window* w,ScreenXY xy,ScreenWH wh,PrintFlags pf,TextSnip0	textref)
//FIX10-2{
//FIX10-2TextBlockPtr
//FIX10-2	currblock=(loadtextblock((TextRef)textref));
//FIX10-2	if	(currblock->type==TEXTTYPE_Snip0)
//FIX10-2	{
//FIX10-2string
//FIX10-2		tmp=TextDeref(currblock,(TextRef)textref);
//FIX10-2		xy=TextB::Print(w,xy,wh,pf,tmp);
//FIX10-2		TextBuildFree((TextBuild) textref);
//FIX10-2		return(xy);
//FIX10-2	}
//FIX10-2else
//FIX10-2	_Error.EmitSysErr("Input to print was not actually Snip0! (%04X)",textref);
//FIX10-2	return(xy);
//FIX10-2};
//FIX10-2
//FIX10-2///////////////////////////////////////////////////////////////////////////////
//FIX10-2ScreenXY	Text::Print(Window* w,ScreenXY xy,ScreenWH wh,PrintFlags pf,TextRef	textref)
//FIX10-2{
//FIX10-2
//FIX10-2	int poo2=textref;
//FIX10-2TextBlockPtr
//FIX10-2	currblock=(loadtextblock(textref));
//FIX10-2
//FIX10-2	int	poo = currblock->type;
//FIX10-2
//FIX10-2	if	(currblock->type==TEXTTYPE_Snip0)
//FIX10-2	{	
//FIX10-2string
//FIX10-2		tmp=TextDeref(currblock,textref);
//FIX10-2		xy=TextB::Print(w,xy,wh,pf,tmp);
//FIX10-2		TextBuildFree((TextBuild) textref);
//FIX10-2		return(xy);
//FIX10-2	}	
//FIX10-2	//else
//FIX10-2	if	(currblock->type==TEXTTYPE_Build)
//FIX10-2		return(Print(w,xy,wh,pf,(TextPerm) textref));
//FIX10-2	//else
//FIX10-2		_Error.EmitSysErr("TextRef var input to print (%04X) was not simple type!",textref);
//FIX10-2	  	return(xy);
//FIX10-2};
//FIX10-2
////////////////////////////////////////////////////////////////////////
//
//	Permanentizing built strings.
//
//	The value returned from Conv is deleted as soon as you use it as an input
//  Permanent strings hang arround until you exit the sheet
//
//  IncPermWin/DecPermWin manage the sheet entry exit
//	Perm() makes a string permanent or frees a permanent string
//	
//
////////////////////////////////////////////////////////////////////////

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DecPermWin
//Author		Jim Taylor
//Date			Tue 14 Nov 1995
//
//Description	close pervious layer of permanent strings
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Text::FreePermPage(TextPage& t)
{
	if (t)
	{	//we have allocated some temp text.. so free that page
TextIndirectBlock*	clearpage=(TextIndirectBlock*) loadedblocks[t>>8];
		t=(TextPage)0;
		clearpage->lastelement=255;
		int i;
		for (i=256;i--;)
		{
			delete [] clearpage->textstarters[i];
			clearpage->textstarters[i]=NULL;
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Perm
//LastModified:	JIM 29Sep96
//Author		Jim Taylor
//Date			Tue 14 Nov 1995
//
//Description	Make a built string permanent and delete the built original
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
TextPerm	Text::Perm(TextBuild textbuild,TextPage& t)
{
	if (t==0)
	{	//no page allocated yet... find one.
		t=TextPageMIN;
		while (t<TextPageMAX && loadedblocks[t>>8]->lastelement!=255)
				t=(TextPage)(t+0x100);
		if (t>TextPageMAX)
			_Error.EmitSysErr("Run out of permanent text pages... aggghhh!!!");
		loadedblocks[t>>8]->lastelement=50;
	}
string
	trg,
	src=TextDeref((TextRef)textbuild);
int	len=strlen(src)+1;
TextIndirectBlock*
	permpage=(TextIndirectBlock*) loadedblocks[t>>8];
	if (	(permpage==NULL)
		||	(permpage->type!=TEXTTYPE_Build)
		)
		_Error.EmitSysErr("Trying to free a perm text which"
						"isn't on a permanent page! (%04X)",t);	//JIM 29Sep96
int	i=0;
	while (permpage->textstarters[i])	i++;
	assert((i<=permpage->lastelement)&&("Over 50 permanent strings on 1 page unexpected. Can increase to 250."));
	permpage->textstarters[i]=
		trg=new char [len];
	while (len--)	*(trg++)=*(src++);
	TextBuildFree(textbuild);
	return (TextPerm) (t+i);									//DAW 17Oct96
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Perm
//Author		Jim Taylor
//Date			Tue 14 Nov 1995
//
//Description	Request early deletion of a permanent text
//
//Inputs		textperm equate to free
//
//Returns		none
//
//------------------------------------------------------------------------------
void	Text::Perm(TextPerm textperm)
{
TextIndirectBlock*
	permpage=(TextIndirectBlock*) loadedblocks[textperm>>8];

	if (	(permpage==NULL)
		||	(permpage==currtextbuild)
		||	(permpage->type!=TEXTTYPE_Build)
		)
		_Error.EmitSysErr("Trying to free a perm text which"
						"isn't on a permanent page! (%04X)",textperm);
	if (permpage->textstarters[textperm&0x00ff]==NULL)
		_Error.EmitSysErr("Trying to free a perm text which"
						"is already free! (%04X)",textperm);
	delete [] permpage->textstarters[textperm&0x00ff];
	permpage->textstarters[textperm&0x00ff]=NULL;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//
//	Brief text decomposition engine
//	Takes in a stream of TextRef values and converts them into a string
//
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//Recursive process
//1) eat first textref
//2) if string param required
//3) then:	for number of parameters required
//4)			recursive call to build table of temp strings from stream
//5)		Conv() to new temp string
//6) else:	for number of params required
//7)			call IntBrief() from stream
//8)		Conv() to new temp string
//9) return new temp string


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		loadtextblock
//Author		Martin Alderton
//Date			Fri 26 Jan 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
TextBlockPtr	Text::loadintblock(TextRef	textbit)
{	
TextBlockPtr
	retval=loadedblocks[textbit>>8];
	if (retval==0)
	{
	   _Error.EmitSysErr("TextRef not loaded !");
	}
	return(retval);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TextDeref
//Author		Martin Alderton
//Date			Fri 26 Jan 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
TextBlock_constants	Text::TextconstDeref(TextBlockPtr	tmptextblock,TextRef textref)
{
 	if (tmptextblock->type!=TEXTTYPE_Const)
		_Error.EmitSysErr("Const equate didn't lead to const textblock");
	//else
	{
TextConstBlock
		*tmpsnip=(TextConstBlock*) tmptextblock;
		assert( ((textref&0xff)<=tmptextblock->lastelement)&&
				("Low level index wrong!"));
		return ((tmpsnip->entry[textref&0xff]));
	}
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TextDeref
//Author		Martin Alderton
//Date			Fri 26 Jan 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
TextBlock_addresses	Text::TextaddrDeref(TextBlockPtr	tmptextblock,TextRef textref)
{
 	if (tmptextblock->type!=TEXTTYPE_Addr)
		_Error.EmitSysErr("Address equate didn't lead to address textblock");
	elser
	{
TextAddrBlock
		*tmpsnip=(TextAddrBlock*) tmptextblock;
		assert( ((textref&0xff)<=tmptextblock->lastelement)&&
				("Low level index wrong!"));
		return ((tmpsnip->entry[textref&0xff]));
	}
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TextDeref
//Author		Martin Alderton
//Date			Fri 26 Jan 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
TextBlock_offsets	Text::TextoffDeref(TextBlockPtr	tmptextblock,TextRef textref)
{
 	if (tmptextblock->type!=TEXTTYPE_Offset)
		_Error.EmitSysErr("Offset equate didn't lead to offset textblock");
	elser
	{
TextOffsetBlock
		*tmpsnip=(TextOffsetBlock*) tmptextblock;
		assert( ((textref&0xff)<=tmptextblock->lastelement)&&
				("Low level index wrong!"));
		return ((tmpsnip->entry[textref&0xff]));

	}
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TextDeref
//Author		Martin Alderton
//Date			Fri 26 Jan 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 int	Text::TextSeqDeref(TextBlockPtr	tmptextblock,TextRef textref)
 {
  	if (tmptextblock->type!=TEXTTYPE_Seq)
		_Error.EmitSysErr("Sequence equate didn't lead to sequence textblock");
 	elser
 	{
 TextSeqBlock
 		*tmpsnip=(TextSeqBlock*) tmptextblock;
 		assert( ((textref&0xff)<=tmptextblock->lastelement)&&
 				("Low level index wrong!"));
			//cludge 'cos entry 0 is really entry 1				//JIM 13May96
		if (textref&0xff)										//JIM 13May96
	 		return ((tmpsnip->index[(textref&0xff)-1]));		//JIM 13May96
		elser													//JIM 13May96
			return(0);											//JIM 13May96
 	}
 }
 

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetVal
//Author		Martin Alderton
//Date			Thu 25 Jan 1996
//
//Description	first stopping off point for getval routines.
//			
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
GetRetVal Text::getval(TextRef* &textreflist)
{
 	GetRetVal retval;
	TextBlockPtr temptextblock;


	if ((*textreflist<TextConstMIN)&&(*textreflist>TextOffsetMAX))
		_Error.EmitSysErr("TextRef unrecognised by GetVal command");

	else if ((*textreflist>=TextConstMIN)&&(*textreflist<=TextConstMAX))
	{
		TextBlock_constants text;
		temptextblock= loadintblock((TextRef) *textreflist);
		text= TextconstDeref(temptextblock,(TextRef) *textreflist);
		retval=getval(text);
		textreflist++;
	}
	else if ((*textreflist>=TextAddrMIN)&&(*textreflist<=TextAddrMAX))
	{
		TextBlock_addresses text;
		temptextblock= loadintblock((TextRef) *textreflist);
		text= TextaddrDeref(temptextblock,(TextRef) *textreflist);
		retval=getval(text);
		textreflist++;

		while (retval.furtherindirection==ILL_OFFSET)
		{
			TextBlock_offsets text;
			temptextblock= loadintblock((TextRef) *textreflist);
			text= TextoffDeref(temptextblock,(TextRef) *textreflist);
			retval=getval((GetRetVal&)retval, text);
			textreflist++;
		}

	}
	else
		_Error.EmitSysErr("Trying to directly call an offset value");
	
	


	return(retval);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetVal
//Author		Martin Alderton
//Date			Wed 24 Jan 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
GetRetVal Text::getval(TextBlock_constants textconst)
{
	
	GetRetVal retval;


 	if (textconst.input.shift+textconst.input.mask>31)
 		_Error.EmitSysErr("Illegal values for this constant");
 	else
 	{
	 	retval.value=((ULong)textconst.value);
		retval.furtherindirection=ILL_VALID;
 		retval.outputform.chars=textconst.output.chars;
 		retval.outputform.layout=textconst.output.layout;
 	}
	return(retval);

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetVal
//Author		Martin Alderton
//Date			Wed 24 Jan 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
GetRetVal Text::getval(TextBlock_addresses textaddr)
{
	GetRetVal retval;

	if (textaddr.input.shift+textaddr.input.mask<=31)
	{
		retval.value=*(ULong*)textaddr.value;
		retval.value=retval.value>>textaddr.input.shift;
		int	masker=2<<textaddr.input.mask;
		masker-=1;
		retval.value&=masker;
		retval.furtherindirection=ILL_VALID;
 		retval.outputform.chars=textaddr.output.chars;
 		retval.outputform.layout=textaddr.output.layout;
		return(retval);

 	}
 	else if (textaddr.input.shift!=31)
 		_Error.EmitSysErr("TextAddr shift value not 31 for specialcases!");
 
 	else
 	{
 	 	if ((textaddr.input.mask==ILL_TEXTREF)||(textaddr.input.mask==ILL_UNIQUEID))
 		{
			retval.value=*(ULong*)textaddr.value;
  			retval.furtherindirection=(BitInputMaskIllegals)textaddr.input.mask;
 		}
 		else
 		{
 			if ((textaddr.input.mask==ILL_INDAFTER)||(textaddr.input.mask==ILL_OFFSET))
 			{
 	 			retval.value=(ULong)textaddr.value;
 			}
 			else if (textaddr.input.mask==ILL_INDB4)
 			{
				retval.value=*(ULong*)textaddr.value;

 			}
 
 			else
 			{
 			 	_Error.EmitSysErr("Illegal combination of shift + mask in GetVal");
 			}
 			retval.furtherindirection=ILL_OFFSET;
 			retval.outputform.chars=textaddr.output.chars;
 			retval.outputform.layout=textaddr.output.layout;
 		}
 	}

 	return(retval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetVal
//Author		Martin Alderton
//Date			Wed 24 Jan 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
GetRetVal Text::getval(GetRetVal& base,TextBlock_offsets offset)
{

	if (base.furtherindirection!=ILL_OFFSET)
		_Error.EmitSysErr("Not an Offset ! in Get Val. By the way, what's Val done wrong anyway ?");

	base.furtherindirection=ILL_VALID;

 	if (offset.input.mask==ILL_INDAFTER)
 		base.furtherindirection=ILL_OFFSET;
	
	int temp;
	temp = base.value+offset.value;

	if (offset.input.shift+offset.input.mask<=31)
	{
 		base.value=*(ULong*)temp;
		base.value=base.value>>offset.input.shift;
		int	masker=2<<offset.input.mask;
		masker-=1;
		base.value&=masker;
		base.furtherindirection=ILL_VALID;
		return(base);

 	}
 	else if (offset.input.shift!=31)
 		_Error.EmitSysErr("Offset shift value not 31 for specialcases!");
	
 	else
 	{
 	 	if ((offset.input.mask==ILL_TEXTREF)||(offset.input.mask==ILL_UNIQUEID))
 		{
 		base.value=*(UWord*)temp;
  		base.furtherindirection=(BitInputMaskIllegals)offset.input.mask;
 		}
 		else
 		{
 			if ((offset.input.mask==ILL_INDAFTER)||(offset.input.mask==ILL_OFFSET))
 			{
 	 			base.value=temp;
 			}
 			else if (offset.input.mask==ILL_INDB4)
 			{
 				base.value=*(ULong*)temp;
 			}
 
 			else
 			{
 			 	_Error.EmitSysErr("Illegal combination of shift + mask in GetVal");
 			}
 			base.furtherindirection=ILL_OFFSET;
 		}
 	}
		
	return(base);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetVal
//Author		Martin Alderton
//Date			Wed 24 Jan 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
GetRetVal Text::getval(TextAddr address,TextOffset offset)
{
 	GetRetVal retval;
	TextBlockPtr temptextblock;

	TextBlock_addresses addr;
	temptextblock= loadintblock((TextRef) address);
	addr= TextaddrDeref(temptextblock,(TextRef) address);

	retval=getval(addr);

	if (retval.furtherindirection!=ILL_OFFSET)
		_Error.EmitSysErr("Expecting further indirection in GetVal");

	else
	{
		TextBlock_offsets text;
		temptextblock= loadintblock((TextRef) offset);
		text= TextoffDeref(temptextblock,(TextRef) offset);
		
		retval=getval(retval,text);

	}

	return(retval);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetVal
//Author		Martin Alderton
//Date			Wed 24 Jan 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 GetRetVal Text::getoneval(TextRef textref)
 {
 	GetRetVal retval;
	TextBlockPtr temptextblock;

 
 	if ((textref<TextConstMIN)&&(textref>TextOffsetMAX))
 		_Error.EmitSysErr("TextRef unrecognised by GetVal command");
 
 	else if ((textref>=TextConstMIN)&&(textref<=TextConstMAX))
	{
		TextBlock_constants text;
		temptextblock= loadintblock(textref);
		text= TextconstDeref(temptextblock,textref);
 		retval=getval(text);
 	}

 	else if ((textref>=TextAddrMIN)&&(textref<=TextAddrMAX))
 	{	
		TextBlock_addresses text;
		temptextblock= loadintblock(textref);
		text= TextaddrDeref(temptextblock,textref);
		retval=getval(text);


	}
 	else
 		_Error.EmitSysErr("Trying to directly call an offset value");
 
 	return(retval);
 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetVal
//Author		Martin Alderton
//Date			Wed 24 Jan 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
GetRetVal Text::getval(GetRetVal& base, TextRef offset)
{
	GetRetVal retval;
	TextBlockPtr temptextblock;

	if ((offset<TextOffsetMIN)&&(offset>TextOffsetMAX))
		_Error.EmitSysErr("TextRef not recognised as an offset by GetVal command");
	else
	{
		TextBlock_offsets text;
		temptextblock= loadintblock((TextRef) offset);
		text= TextoffDeref(temptextblock,(TextRef) offset);
		retval=getval(base, text);
	}

	return(retval);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Conv
//Author		Martin Alderton
//Date			Wed 24 Jan 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
TextBuild Text::Convert(TextRef textref)
{

	if ((textref<TextConstMIN)&&(textref>TextOffsetMAX))
		_Error.EmitSysErr("TextRef unrecognised by GetVal command");

	else if ((textref>=TextConstMIN)&&(textref<=TextConstMAX))
		return(Conv((TextConst) textref));
	
	else if ((textref>=TextAddrMIN)&&(textref<=TextAddrMAX))
		return(Conv((TextAddr) textref));

	else
		_Error.EmitSysErr("Attempting to convert an Offset into a text string !");

	return(Conv(textref&0xff));
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Conv
//Author		Martin Alderton
//Date			Thu 25 Jan 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
TextBuild Text::Conv(TextConst textconst)
{
	GetRetVal retval;
	TextBlockPtr temptextblock;

	TextBlock_constants text;
	temptextblock= loadintblock((TextRef) textconst);
	text= TextconstDeref(temptextblock,(TextRef) textconst);

	retval=getval(text);


	return(Conv((SLong)retval.value,retval.outputform.chars,(CharOutputLayout)retval.outputform.layout)); 

}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Conv
//Author		Martin Alderton
//Date			Thu 25 Jan 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
TextBuild Text::Conv(TextAddr textaddr)
{
 	GetRetVal retval;
	TextBlockPtr temptextblock;

	TextBlock_addresses text;
	temptextblock= loadintblock((TextRef)textaddr);
	text= TextaddrDeref(temptextblock,(TextRef)textaddr);
	retval=getval(text);
 
	if (retval.furtherindirection)
		_Error.EmitSysErr("This Can't be happening to me ! You're trying to convert an incomplete GetRetVal!, Doh!");
	
 
 	return(Conv((SLong)retval.value,retval.outputform.chars,(CharOutputLayout)retval.outputform.layout)); 


}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Conv
//Author		Martin Alderton
//Date			Thu 25 Jan 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
TextBuild Text::Conv(GetRetVal retval)
{
	if (retval.furtherindirection)
		if (retval.furtherindirection==ILL_OFFSET)
			_Error.EmitSysErr("This Can't be happening to me ! You're trying to convert an incomplete GetRetVal!, Doh!");
		elseif (retval.furtherindirection==ILL_TEXTREF)
			;//return(Conv((TextRef) retval.value));
		elseif (retval.furtherindirection==ILL_UNIQUEID)
			return(Conv((UniqueID) retval.value));				//JIM 10Jun96
	elser
		return (Conv((SLong)retval.value,retval.outputform.chars,(CharOutputLayout)retval.outputform.layout)); 

}

/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
//																			   //
//																			   //
//			Convert routines for Seq types									   //
//																			   //
//																			   //
//																			   //
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Conv
//Author		Martin Alderton
//Date			Tue 30 Jan 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
TextBuild Text::Conv(TextSeq sequence)
{
	TextBlockPtr temptextblock;
	TextRef	*seqsrc,*seqtrg,*seqind;
	TextBuild blob;
	
	int temp;
	temptextblock= loadtextblock((TextRef) sequence);
  	if (temptextblock->type==TEXTTYPE_Snip0)					//RDH 02Jul96
		return(TextB::Conv((TextSnipBlock*)temptextblock,(TextSnip0) sequence));//RDH 02Jul96

	temp= TextSeqDeref(temptextblock,(TextRef) sequence);


	seqsrc=(TextRef*)&((TextSeqBlock*)temptextblock)->seqs[temp];
	seqind=seqsrc;
	temp=1;

	while (*seqind++!=(UWord)-1)
			temp++;
	seqtrg= new TextRef[temp];

	seqind= seqtrg;
	while (*seqsrc!=(UWord)-1)
		*seqind++=*seqsrc++;

	*seqind=*seqsrc;

	seqind= seqtrg;

	blob = Conv_List(seqtrg);
	delete[]seqind;

	return(blob);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Conv_List
//Author		Martin Alderton
//Date			Tue 30 Jan 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
TextBuild Text::Conv_List(TextRef* &reflist)
{

	TextBuild retval;

		retval = convlist(reflist);

	if (*reflist!=(UWord)-1)
	{
		_Error.EmitSysErr("No -1 terminator on Sequence list!");
	}

	//remeber to test for -1 as terminating conditon satisfied .

	return(retval);

}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		gettextparams
//Author		Martin Alderton
//Date			Thu 1 Feb 1996
//
//Description	never used.	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
int TextB::gettextparams(char* text)
{
 	int count=0;
	return(count);
}


			 
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		gettexttype
//Author		Martin Alderton
//Date			Thu 1 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
char TextB::gettexttype(TextBlockPtr ref)
{
char type;

if (ref->type==TEXTTYPE_Snip0)
	type='A';

else if (ref->type==TEXTTYPE_Snipn)
	type='B';

else if (ref->type==TEXTTYPE_List)
	type='C';

else if (ref->type==TEXTTYPE_Addr)
	type='D';

else if (ref->type==TEXTTYPE_Const)
	type='E';

else if (ref->type==TEXTTYPE_Offset)
	type='F';

else
	_Error.EmitSysErr("Type not recognised");


return (type);


}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		convlist
//Author		Martin Alderton
//Date			Tue 30 Jan 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
TextBuild Text::convlist(TextRef* &reflist)
{

	TextBlockPtr temptextblock;
	temptextblock= loadtextblock((TextRef) *reflist);
	char text;
	text=gettexttype(temptextblock);

	switch (text)
	{
		case 'A':
		{
			return(Conv((TextSnip0)*reflist++));
		}
		case 'B':
		{
			int num;
			num=temptextblock->parameters;
			switch (num)
			{
				case 0:
					return (Conv((TextSnip0)*reflist++));
				case 1:
				{
					TextSnip1 base=((TextSnip1)*reflist++);
					TextBuild p1=convlist(reflist);
					return(Conv(base,p1));
				}
				case 2:
				{
					TextSnip2 base=((TextSnip2)*reflist++);
					TextBuild p1=convlist(reflist);
					TextBuild p2=convlist(reflist);
					return(Conv(base,p1,p2));
				}
				case 3:
				{
					TextSnip3 base=((TextSnip3)*reflist++);
					TextBuild p1=convlist(reflist);
					TextBuild p2=convlist(reflist);
					TextBuild p3=convlist(reflist);
					return(Conv(base,p1,p2,p3));
				}
				case 4:
				{
					TextSnip4 base=((TextSnip4)*reflist++);
					TextBuild p1=convlist(reflist);
					TextBuild p2=convlist(reflist);
					TextBuild p3=convlist(reflist);
					TextBuild p4=convlist(reflist);
					return(Conv(base,p1,p2,p3,p4));
				}
				case 5:
				{
					TextSnip5 base=((TextSnip5)*reflist++);
					TextBuild p1=convlist(reflist);
					TextBuild p2=convlist(reflist);
					TextBuild p3=convlist(reflist);
					TextBuild p4=convlist(reflist);
					TextBuild p5=convlist(reflist);
					return(Conv(base,p1,p2,p3,p4,p5));
				}
				case 6:
				{
					TextSnip6 base=((TextSnip6)*reflist++);
					TextBuild p1=convlist(reflist);
					TextBuild p2=convlist(reflist);
					TextBuild p3=convlist(reflist);
					TextBuild p4=convlist(reflist);
					TextBuild p5=convlist(reflist);
					TextBuild p6=convlist(reflist);
					return(Conv(base,p1,p2,p3,p4,p5,p6));
				}
				case 7:
				{
					TextSnip7 base=((TextSnip7)*reflist++);
					TextBuild p1=convlist(reflist);
					TextBuild p2=convlist(reflist);
					TextBuild p3=convlist(reflist);
					TextBuild p4=convlist(reflist);
					TextBuild p5=convlist(reflist);
					TextBuild p6=convlist(reflist);
					TextBuild p7=convlist(reflist);
					return(Conv(base,p1,p2,p3,p4,p5,p6,p7));
				}
				case 8:
				{
					TextSnip8 base=((TextSnip8)*reflist++);
					TextBuild p1=convlist(reflist);
					TextBuild p2=convlist(reflist);
					TextBuild p3=convlist(reflist);
					TextBuild p4=convlist(reflist);
					TextBuild p5=convlist(reflist);
					TextBuild p6=convlist(reflist);
					TextBuild p7=convlist(reflist);
					TextBuild p8=convlist(reflist);
					return(Conv(base,p1,p2,p3,p4,p5,p6,p7,p8));
				}
				case 9:
				{
					TextSnip9 base=((TextSnip9)*reflist++);
					TextBuild p1=convlist(reflist);
					TextBuild p2=convlist(reflist);
					TextBuild p3=convlist(reflist);
					TextBuild p4=convlist(reflist);
					TextBuild p5=convlist(reflist);
					TextBuild p6=convlist(reflist);
					TextBuild p7=convlist(reflist);
					TextBuild p8=convlist(reflist);
					TextBuild p9=convlist(reflist);
					return(Conv(base,p1,p2,p3,p4,p5,p6,p7,p8,p9));
				}
				case 10:
				{
					TextSnip10 base=((TextSnip10)*reflist++);
					TextBuild p1=convlist(reflist);
					TextBuild p2=convlist(reflist);
					TextBuild p3=convlist(reflist);
					TextBuild p4=convlist(reflist);
					TextBuild p5=convlist(reflist);
					TextBuild p6=convlist(reflist);
					TextBuild p7=convlist(reflist);
					TextBuild p8=convlist(reflist);
					TextBuild p9=convlist(reflist);
					TextBuild p10=convlist(reflist);
					return(Conv(base,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10));
				}
				case 11:
				{
					TextSnip11 base=((TextSnip11)*reflist++);
					TextBuild p1=convlist(reflist);
					TextBuild p2=convlist(reflist);
					TextBuild p3=convlist(reflist);
					TextBuild p4=convlist(reflist);
					TextBuild p5=convlist(reflist);
					TextBuild p6=convlist(reflist);
					TextBuild p7=convlist(reflist);
					TextBuild p8=convlist(reflist);
					TextBuild p9=convlist(reflist);
					TextBuild p10=convlist(reflist);
					TextBuild p11=convlist(reflist);
					return(Conv(base,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11));
				}
				case 12:
				{
					TextSnip12 base=((TextSnip12)*reflist++);
					TextBuild p1=convlist(reflist);
					TextBuild p2=convlist(reflist);
					TextBuild p3=convlist(reflist);
					TextBuild p4=convlist(reflist);
					TextBuild p5=convlist(reflist);
					TextBuild p6=convlist(reflist);
					TextBuild p7=convlist(reflist);
					TextBuild p8=convlist(reflist);
					TextBuild p9=convlist(reflist);
					TextBuild p10=convlist(reflist);
					TextBuild p11=convlist(reflist);
					TextBuild p12=convlist(reflist);
					return(Conv(base,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12));
				}
				case 13:
				{
					TextSnip13 base=((TextSnip13)*reflist++);
					TextBuild p1=convlist(reflist);
					TextBuild p2=convlist(reflist);
					TextBuild p3=convlist(reflist);
					TextBuild p4=convlist(reflist);
					TextBuild p5=convlist(reflist);
					TextBuild p6=convlist(reflist);
					TextBuild p7=convlist(reflist);
					TextBuild p8=convlist(reflist);
					TextBuild p9=convlist(reflist);
					TextBuild p10=convlist(reflist);
					TextBuild p11=convlist(reflist);
					TextBuild p12=convlist(reflist);
					TextBuild p13=convlist(reflist);
					return(Conv(base,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13));
				}
				case 14:
				{
					TextSnip14 base=((TextSnip14)*reflist++);
					TextBuild p1=convlist(reflist);
					TextBuild p2=convlist(reflist);
					TextBuild p3=convlist(reflist);
					TextBuild p4=convlist(reflist);
					TextBuild p5=convlist(reflist);
					TextBuild p6=convlist(reflist);
					TextBuild p7=convlist(reflist);
					TextBuild p8=convlist(reflist);
					TextBuild p9=convlist(reflist);
					TextBuild p10=convlist(reflist);
					TextBuild p11=convlist(reflist);
					TextBuild p12=convlist(reflist);
					TextBuild p13=convlist(reflist);
					TextBuild p14=convlist(reflist);
					return(Conv(base,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14));
				}
				case 15:
				{
					TextSnip15 base=((TextSnip15)*reflist++);
					TextBuild p1=convlist(reflist);
					TextBuild p2=convlist(reflist);
					TextBuild p3=convlist(reflist);
					TextBuild p4=convlist(reflist);
					TextBuild p5=convlist(reflist);
					TextBuild p6=convlist(reflist);
					TextBuild p7=convlist(reflist);
					TextBuild p8=convlist(reflist);
					TextBuild p9=convlist(reflist);
					TextBuild p10=convlist(reflist);
					TextBuild p11=convlist(reflist);
					TextBuild p12=convlist(reflist);
					TextBuild p13=convlist(reflist);
					TextBuild p14=convlist(reflist);
					TextBuild p15=convlist(reflist);
					return(Conv(base,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15));
				}
			}
		}
		case 'C':
		{
		 	TextList	tmplist=(TextList)*reflist++;
			GetRetVal	tmpval=getval(reflist);
			return(Conv(tmpval));								//JIM 11Jun96
		}
		case 'E':
		case 'D':
		{
			GetRetVal	tmpval=getval(reflist);
		

			return(Conv(tmpval));								//JIM 11Jun96
		}
		default:
		case 'F':
			_Error.EmitSysErr("You have done a very,very bad thing to convlist!");
	}
	return((TextBuild)0);
}
/////////////////////////////////////////////////////////////////////////////////
//
// DEBUG STUFF
//
///////////////////////////////////////////////////////////////////////////////

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TextTest
//Author		Jim Taylor
//Date			Tue 14 Nov 1995
//
//Description	Test the text routines
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TextTest()
{	//dry-run testbed for fonts and strings
short	a;	
//DeadCode JIM 19Jan98 	Whole_Screen->RegisterFontActive(FIL_MAINTEXTFONT, a,a,a);	//PD 29Nov95
//DeadCode JIM 19Jan98 
//DeadCode JIM 19Jan98 	Whole_Screen->LoadMouseImage(FIL_MOUSE_IMAGE);

}




//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Stringify
//Author		Dave Whiteside
//Date			Thu 13 Feb 1997
//
//Description	make a string from an equate
//
//Inputs		address to put string, text enum
//
//Returns		address filled [no error checking is length is too small]
//
//------------------------------------------------------------------------------
Bool	Text::Stringify(char *dest,TextBuild src)
{
	char	*poo;
	poo=TextDeref((TextRef)src);
	strcpy(dest,poo);
	return(TRUE);
}


