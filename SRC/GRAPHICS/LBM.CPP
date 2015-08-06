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
//Filename       lbm.cpp
//System         new eng
//Author         Dave Whiteside
//Date           Thu 11 Jan 1996
//Description    lbm unpacking with transparancy stuff
//------------------------------------------------------------------------------
#include	"dosdefs.h"
#include	<string.h>
#include	<stdlib.h>
#include	<stdio.h>
#include	"fonts.h"
#define		F_GRAFIX											//JIM 01Aug96
#include	"display.h"
//DeadCode JIM 02Jul96 #include	<assert.h>
#include	<fstream.h>
#include	"fileman.h"
#include	"lbm.h"
#include	"mouse.h"
//DeadCode JIM 08Apr97 #include	<stdio.h>

UWord	screenshotnum=0;
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ScreenShot
//Author		Dave Whiteside
//Date			Mon 19 Feb 1996
//
//Description	Take a ScreenShot and write the results to a file
//
//Inputs		WindowPtr
//
//Returns		
//
//------------------------------------------------------------------------------
void Graphic::ScreenShot()
{
	LBM		screenShot;
	ULong	packedlength;

	screenShot.MakeHead(PhysicalWidth,PhysicalHeight);
	screenShot.MakePall((char *)Palette);
	packedlength = screenShot.MakeBody(logicalscreenptr,BytesPerScanLine);
	screenShot.Save(screenshotnum++,packedlength);
	if (screenshotnum>99)
		screenshotnum=0;
}

LBM::LBM()
{
//	body		= new char[DEFAULT_LBM*DEFAULT_LBM];
	body		= new UByte[DEFAULT_LBM*DEFAULT_LBM];
	hdr			= new LBMHeader;
	pal			= new char[3*256];
	hdr->width	= DEFAULT_LBM;
	hdr->height	= DEFAULT_LBM;

}


LBM::~LBM()
{
	delete	hdr;
	delete	body;
	delete	pal;
}


void LBM::MakeHead(short w, short h)
{
	delete		hdr;

	hdr			= new LBMHeader;
	hdr->width	= w;
	hdr->height	= h;
	hdr->x		= 0;
	hdr->y		= 0;
	hdr->nPlanes= 8;
	hdr->masking= 0;
//Old_Code DAW 22Feb96 	hdr->compression=cmpNone;
	hdr->compression=cmpByteRun1;
	hdr->pad1	= 0;
	hdr->transparentColour= 0xff;
	hdr->xAspect= 1;
	hdr->yAspect= 1;
	hdr->pageWidth= w;
	hdr->pageHeight= h;

}

ULong LBM::MakeBody(LogicalPtr logicalscreenptr,int	BytesPerScanLine)
{
	delete		body;
	ULong		filelen,m,packedlength,x,k;
	UByte		c;
	//char*		p,q;

	body= new UByte[hdr->width*hdr->height*2];		//*2 cause it may be massive
//	body= new char[hdr->width*hdr->height*2];		//*2 cause it may be massive
//	q= 	*body;
	packedlength=0;
	m=0;
	for (int y=0;y<hdr->height;y++)
	{
		x=0;
		while (x<hdr->width)
		{
			if (x<hdr->width && (logicalscreenptr[x] == logicalscreenptr[x+1]))
			{											//packable
				k=0;
				c=logicalscreenptr[x+k];
				while ((logicalscreenptr[x+k]==c) && k<127 && ((x+k)<hdr->width))
					k++;
				body[packedlength++]=257-k;
				body[packedlength++]=c;
				x+=k;
			}
			else
			{											//not packable
				k=1;
				c=logicalscreenptr[x];
				while ((x+k < hdr->width-2 && (logicalscreenptr[x+k]!=c || logicalscreenptr[x+k+1]!=c)) && (k<127 && ((x+k)<hdr->width)))
					c=logicalscreenptr[x+k++];
				body[packedlength++]=k-1;
				for (int i=0;i<k;i++)
					body[packedlength++]=logicalscreenptr[(x++)];
				}
		}
		logicalscreenptr+=BytesPerScanLine;
	}
	return(packedlength);
}

void LBM::MakePall(char* newpal)
{
	delete	pal;
	pal = new char[3*256];
	for (int i=0;i<768;i++)
		pal[i]=newpal[i];										//JIM 16Jul96
}

void Put68KLong(FILE *fp,int size)
{
	fputc(size>>24,fp);
	fputc(size>>16,fp);
	fputc(size>>8,fp);
	fputc(size,fp);
}

void Put68KWord(FILE *fp,UWord size)
{
	fputc(size>>8,fp);
	fputc(size,fp);
}

void	LBM::Save(UWord ScreenShot,ULong packedlength)
{
	FileNum	fil;
	FILE	*fp;
	div_t	val;
	char	*p;
	char	c;

	string nom=FILEMAN.namenumberedfile(FIL_STILLS_START);
	val = div(ScreenShot,10);
	p= 	strrchr(nom,'0');
	*p	=(val.rem)+'0';
	p--;
	*p	=(val.quot)+'0';
	p= 	strrchr(nom,'.');										//DAW 03Jun97
	p++;
	*p ='L';
	p++;
	*p='B';
	p++;
	*p='M';

	fp=fopen(nom,"wb");
	if (fp)
	{
		fprintf(fp,"FORM");
		Put68KLong(fp,48+3*256+packedlength);

		fprintf(fp,"PBM BMHD");
		Put68KLong(fp,20);
		Put68KWord(fp,hdr->width);
		Put68KWord(fp,hdr->height);
		Put68KWord(fp,hdr->x);
		Put68KWord(fp,hdr->y);
		fputc(hdr->nPlanes,fp);
		fputc(hdr->masking,fp);
		fputc(hdr->compression,fp);
		fputc(hdr->pad1,fp);
		Put68KWord(fp,hdr->transparentColour);
		putc(hdr->xAspect,fp);
		putc(hdr->yAspect,fp);
		Put68KWord(fp,hdr->pageWidth);
		Put68KWord(fp,hdr->pageHeight);

		fprintf(fp,"CMAP");
		Put68KLong(fp,3*256);
		fwrite(pal,3,256,fp);

		fprintf(fp,"BODY");
		Put68KLong(fp,packedlength);
		fwrite(body,1,packedlength,fp);
//Old_Code DAW 22Feb96 		Put68KLong(fp,hdr->width*hdr->height);
//Old_Code DAW 22Feb96 		fwrite(body,1,hdr->width*hdr->height,fp);

		fclose(fp);

	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FillExpandBuff
//Author		Jim Taylor
//Date			Tue 8 Apr 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
UByte	Graphic::ExpandBuff[256][8];
SLong	Graphic::fontcolour=-2;

void	Graphic::FillExpandBuff()
{
	for (int x=0;x<256;x++)
		for (int y=0;y<8;y++)
			ExpandBuff[x][y]=x;
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	Graphic::UnpackRow
//------------------------------------------------------------------------------
//Author		Paul.   
//Date			Fri 7 Jul 1995
//Modified		DAW 11Jan96
//
//Description	Unpack a row of artwork
//
//Inputs		Source data
//				Length of line in data
//				start	x
//				start	y
//				physical min x
//				physical max x
//
//Returns		Data ptr moved
//
//Externals
//------------------------------------------------------------------------------
UByte *Graphic::UnpackRow(UByte *c, SLong width, SLong x, SLong y, SLong minx, SLong maxx)
//------------------------------------------------------------------------------
{
//DEADCODE JIM 29/03/99 	if (BytesPerPixel>=2)
//DEADCODE JIM 29/03/99 		if (BytesPerPixel<3)
//DEADCODE JIM 29/03/99 			return (Unpack2Row(c,width,x<<1,y,minx<<1,maxx<<1));
//DEADCODE JIM 29/03/99 		elseif (BytesPerPixel>3)
//DEADCODE JIM 29/03/99 			return (Unpack4Row(c,width,x<<2,y,minx<<2,maxx<<2));
//DEADCODE JIM 29/03/99 		else
//DEADCODE JIM 29/03/99 			return (Unpack3Row(c,width,x<<2,y,minx<<2,maxx<<2));

	#define	TRANSFERVALUESIZE	UByte
	#define	LOADVALUE(x)	TRANSFERVALUE=x
	#define	COPYVALUE(t,s)	*t++=s

	#include	"lbmcpp.h"

//DEADCODE JIM 29/03/99 //------------------------------------------------------------------------------
//DEADCODE JIM 29/03/99 UByte *Graphic::Unpack2Row(UByte *c, SLong width, SLong x, SLong y, SLong minx, SLong maxx)
//DEADCODE JIM 29/03/99 //------------------------------------------------------------------------------
//DEADCODE JIM 29/03/99 {
//DEADCODE JIM 29/03/99 	x>>=1;
//DEADCODE JIM 29/03/99 	minx>>=1;
//DEADCODE JIM 29/03/99 	maxx>>=1;
//DEADCODE JIM 29/03/99 	#define	TRANSFERVALUESIZE	UWord
//DEADCODE JIM 29/03/99 	#define LOADVALUE(x)	TRANSFERVALUE=*(TRANSFERVALUESIZE*)(ExpandBuff[x])
//DEADCODE JIM 29/03/99 	#define COPYVALUE(x,y)	*((TRANSFERVALUESIZE*&)x)++=*(TRANSFERVALUESIZE*)(ExpandBuff[y])
//DEADCODE JIM 29/03/99 	#include	"lbmcpp.h"
//DEADCODE JIM 29/03/99 //------------------------------------------------------------------------------
//DEADCODE JIM 29/03/99 UByte *Graphic::Unpack3Row(UByte *c, SLong width, SLong x, SLong y, SLong minx, SLong maxx)
//DEADCODE JIM 29/03/99 //------------------------------------------------------------------------------
//DEADCODE JIM 29/03/99 {
//DEADCODE JIM 29/03/99 	#define	TRANSFERVALUESIZE	ULong
//DEADCODE JIM 29/03/99 	#define LOADVALUE(x)	TRANSFERVALUE=*(TRANSFERVALUESIZE*)(ExpandBuff[x])
//DEADCODE JIM 29/03/99 	#define SAVEVALUE(x)	*((UWord*&)x)++=TRANSFERVALUE;		\
//DEADCODE JIM 29/03/99 							*((UByte*&)x)++=TRANSFERVALUE>>16
//DEADCODE JIM 29/03/99 	#define COPYVALUE(x,y)	LOADVALUE(y);SAVEVALUE(x)
//DEADCODE JIM 29/03/99 	#define DELTAVALUE(x,d) (int&)x += d+d+d;
//DEADCODE JIM 29/03/99 
//DEADCODE JIM 29/03/99 	#include	"lbmcpp.h"
//DEADCODE JIM 29/03/99 //------------------------------------------------------------------------------
//DEADCODE JIM 29/03/99 UByte *Graphic::Unpack4Row(UByte *c, SLong width, SLong x, SLong y, SLong minx, SLong maxx)
//DEADCODE JIM 29/03/99 //------------------------------------------------------------------------------
//DEADCODE JIM 29/03/99 {
//DEADCODE JIM 29/03/99 	x>>=2;
//DEADCODE JIM 29/03/99 	minx>>=2;
//DEADCODE JIM 29/03/99 	maxx>>=2;
//DEADCODE JIM 29/03/99 	#define	TRANSFERVALUESIZE	ULong
//DEADCODE JIM 29/03/99 	#define LOADVALUE(x)	TRANSFERVALUE=*(TRANSFERVALUESIZE*)(ExpandBuff[x])
//DEADCODE JIM 29/03/99 	#define COPYVALUE(x,y)	*((TRANSFERVALUESIZE*&)x)++=*(TRANSFERVALUESIZE*)(ExpandBuff[y])
//DEADCODE JIM 29/03/99 	#include	"lbmcpp.h"
//DEADCODE JIM 29/03/99 
//DEADCODE JIM 29/03/99 //------------------------------------------------------------------------------
//DEADCODE JIM 29/03/99 UByte *Graphic::Unpack8Row(UByte *c, SLong width, SLong x, SLong y, SLong minx, SLong maxx)
//DEADCODE JIM 29/03/99 //------------------------------------------------------------------------------
//DEADCODE JIM 29/03/99 {
//DEADCODE JIM 29/03/99 	x>>=3;
//DEADCODE JIM 29/03/99 	minx>>=3;
//DEADCODE JIM 29/03/99 	maxx>>=3;
//DEADCODE JIM 29/03/99 	#define	TRANSFERVALUESIZE	Float
//DEADCODE JIM 29/03/99 	#define LOADVALUE(x)	TRANSFERVALUE=*(TRANSFERVALUESIZE*)(ExpandBuff[x])
//DEADCODE JIM 29/03/99 	#define COPYVALUE(x,y)	*((TRANSFERVALUESIZE*&)x)++=*(TRANSFERVALUESIZE*)(ExpandBuff[y])
//DEADCODE JIM 29/03/99 	#include	"lbmcpp.h"
//DEADCODE JIM 29/03/99 
//DEADCODE JIM 29/03/99 //------------------------------------------------------------------------------
//DEADCODE JIM 29/03/99 UByte *Graphic::UnpackShadeRow(UByte *c, SLong width, SLong x, SLong y, SLong minx, SLong maxx)
//DEADCODE JIM 29/03/99 //------------------------------------------------------------------------------
//DEADCODE JIM 29/03/99 {
//DEADCODE JIM 29/03/99 	if (BytesPerPixel>=2)
//DEADCODE JIM 29/03/99 		if (BytesPerPixel<3)
//DEADCODE JIM 29/03/99 			return (Unpack2Row(c,width,x<<1,y,minx<<1,maxx<<1));
//DEADCODE JIM 29/03/99 		elseif (BytesPerPixel>3)
//DEADCODE JIM 29/03/99 			return (Unpack4Row(c,width,x<<2,y,minx<<2,maxx<<2));
//DEADCODE JIM 29/03/99 		else
//DEADCODE JIM 29/03/99 			return (Unpack3Row(c,width,x<<2,y,minx<<2,maxx<<2));
//DEADCODE JIM 29/03/99 
//DEADCODE JIM 29/03/99 	#define	TRANSFERVALUESIZE	UByte
//DEADCODE JIM 29/03/99 	#define LOADVALUE(x)	TRANSFERVALUE=x+colour
//DEADCODE JIM 29/03/99 	#define COPYVALUE(x,y)	*x++=y+colour
//DEADCODE JIM 29/03/99 	#include	"lbmcpp.h"
//DEADCODE JIM 29/03/99 
//DEADCODE JIM 29/03/99 //------------------------------------------------------------------------------
//DEADCODE JIM 29/03/99 UByte *Graphic::UnpackSmoothRow(UByte *c, SLong width, SLong x, SLong y, SLong minx, SLong maxx)
//DEADCODE JIM 29/03/99 //------------------------------------------------------------------------------
//DEADCODE JIM 29/03/99 {
//DEADCODE JIM 29/03/99 	#define	TRANSFERVALUESIZE	UByte
//DEADCODE JIM 29/03/99 	#define LOADVALUE(x)	TRANSFERVALUE=shadetable[x]
//DEADCODE JIM 29/03/99 	#define COPYVALUE(x,y)	*x++=shadetable[y]
//DEADCODE JIM 29/03/99 	#include	"lbmcpp.h"
//DEADCODE JIM 29/03/99 
//DEADCODE JIM 29/03/99 
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	Graphic::SkipRow
//------------------------------------------------------------------------------
//Author		Paul.   
//Date			Fri 7 Jul 1995
//Modified		DAW 19Jan96
//
//Description	cleaned and made slightly more cunning
//
//Inputs		data area
//				length of line
//
//Returns		new position in the data area
//
//Externals		Nufin
//------------------------------------------------------------------------------
UByte *Graphic::SkipRow(UByte *c, SWord length) 
//------------------------------------------------------------------------------
{
	while(length>0)
	{
	SLong	Count;
	char	b=*c;

		if(b<0x080)						//Copy
		{
			Count = 1+(SByte)b;
			c+=Count+1;
		}
		else
		{
			if(b>0x080)					//Run
			{
				Count = 1-(SByte)b;
				c+=2;
			}
			else							//transparent
			{
				c++;
				Count = 1 + (UByte)*c++;
			}
		}
		length -= Count;
	}
	return(c);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	Graphic::SearchIFFHunk
//------------------------------------------------------------------------------
//Author		Paul.   
//Date			Fri 7 Jul 1995
//Modified		DAW 22Jan96 - made it more safe and it now looks at the header
//				for each chunk for a faster safer search
//
//Description	Search a buffer for a 4 character string
//				LBM's always have a header that looks like:-
//				FORMxxxx
//				PBM 
//				BMHDxxxx
//				[CMAPxxxx|BODYxxxx]
//				where xxxx is a 68k style long word denoting length of this block
//
//Inputs		ptr to search string
//				ptr to buffer - LBM style in mem [ has blocks
//									FORM, BMHD, CMAP, BODY]
//
//Returns		position of correct data or 0 if failed
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
UByte *Graphic::SearchIFFHunk(UByte *search,UByte *ptr)			//MGA 21Feb96
{
	ULong	maxlen;
	UByte*	tmp=0;

	if (((ULong*)ptr)[0]==((ULong*)"FORM")[0])					//MGA 21Feb96
	{																//Good
		maxlen=(ptr[4]<<24)+(ptr[5]<<16)+(ptr[6]<<8)+ptr[7];
		ptr+=12;
		tmp=ptr+maxlen;

		while (		(((ULong*)ptr)[0]!=((ULong*)"BODY")[0])		//MGA 21Feb96
				&&	(((ULong*)ptr)[0]!=((ULong*)search)[0])		//MGA 21Feb96
			)
			ptr+=(ptr[4]<<24)+(ptr[5]<<16)+(ptr[6]<<8)+ptr[7]+8;
	}
	if (((ULong*)ptr)[0]==((ULong*)search)[0])					//MGA 21Feb96
		return(ptr+8);
	else
		return(0);												//MGA 21Feb96
}																//jim actually.

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SearchIFFHunks
//Author		Paul.   
//Date			Tue 27 Oct 1998
//------------------------------------------------------------------------------
SLong Graphic::SearchIFFHunks(SLong count,IFFHunkSearch* pSearch,UByte* ptr)
{

	SLong found=0;

	if (((ULong*)ptr)[0]==((ULong*)"FORM")[0])
	{
		ptr+=12;

		while (found!=count)
		{
			for (SLong i=0;i<count;i++)
				if (pSearch[i].hunkPtr==NULL &&
					pSearch[i].searchVal==*(ULong*)ptr)
				{
					pSearch[i].hunkPtr=ptr+8;
					found++;
					break;
				}

			if (*(ULong*)ptr==*(ULong*)"BODY") break;

			ptr+=(ptr[4]<<24)+(ptr[5]<<16)+(ptr[6]<<8)+ptr[7]+8;
		}
	}

	return found;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Graphic::Readword
//------------------------------------------------------------------------------
//Author		Paul.   
//Date			Fri 7 Jul 1995
//Modified		DAW 22Jan96
//
//Description	Read a word in 68k format, from the buffer and store it in the
//				variable and return the new position of the buffer
//
//Inputs		buffer and variable
//
//Returns		buffer and variable
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
UByte *Graphic::ReadWord(UByte *c, SWord &number)
{
	number=(c[0]<<8)+c[1];
	c+=2;
	return(c);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Graphic::ReadLong
//------------------------------------------------------------------------------
//Author		Paul.   
//Date			Fri 7 Jul 1995
//Modified		DAW 22Jan96
//
//Description	Read a Long in 68k format
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
UByte *Graphic::ReadLong(UByte *c, SLong &number)
{
	number=(c[0]<<24)+(c[1]<<16)+(c[2]<<8)+c[3];
	c+=4;
	return(c);
}
//DEADCODE JIM 29/03/99 
//DEADCODE JIM 29/03/99 
//DEADCODE JIM 29/03/99 
//DEADCODE JIM 29/03/99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE JIM 29/03/99 //Procedure		PalFontTables
//DEADCODE JIM 29/03/99 //Author		Jim Taylor
//DEADCODE JIM 29/03/99 //Date			Thu 22 May 1997
//DEADCODE JIM 29/03/99 //
//DEADCODE JIM 29/03/99 //Description	
//DEADCODE JIM 29/03/99 //
//DEADCODE JIM 29/03/99 //Inputs		
//DEADCODE JIM 29/03/99 //
//DEADCODE JIM 29/03/99 //Returns	
//DEADCODE JIM 29/03/99 //
//DEADCODE JIM 29/03/99 //------------------------------------------------------------------------------
//DEADCODE JIM 29/03/99 void Graphic::PalFontTables()
//DEADCODE JIM 29/03/99 {
//DEADCODE JIM 29/03/99 	if (BytesPerPixel>1 && fontcolour!=-1)
//DEADCODE JIM 29/03/99 	{
//DEADCODE JIM 29/03/99 		fontcolour=-1;
//DEADCODE JIM 29/03/99 		UByte* p=(UByte*)Palette;
//DEADCODE JIM 29/03/99 
//DEADCODE JIM 29/03/99 		if (BytesPerPixel==2)
//DEADCODE JIM 29/03/99 			for (int i=0;i<256;i++)
//DEADCODE JIM 29/03/99 			{
//DEADCODE JIM 29/03/99 //Old_Code PD 23May97 				UWord tc=(*p++>>3);
//DEADCODE JIM 29/03/99 //Old_Code PD 23May97 				tc+=(*p++>>2)<<5;
//DEADCODE JIM 29/03/99 //Old_Code PD 23May97 				tc+=(*p++>>3)<<11;
//DEADCODE JIM 29/03/99 
//DEADCODE JIM 29/03/99 				UWord
//DEADCODE JIM 29/03/99 				tc= (*p++>>(8-RedBits))		<< RedShift;
//DEADCODE JIM 29/03/99 				tc+=(*p++>>(8-GreenBits))	<< GreenShift;
//DEADCODE JIM 29/03/99 				tc+=(*p++>>(8-BlueBits))	<< BlueShift;
//DEADCODE JIM 29/03/99 
//DEADCODE JIM 29/03/99 //Old_Code RDH 16Oct97 				UWord tc=(*p++>>3)<<11;
//DEADCODE JIM 29/03/99 //Old_Code RDH 16Oct97 				tc+=(*p++>>2)<<5;
//DEADCODE JIM 29/03/99 //Old_Code RDH 16Oct97 				tc+=(*p++>>3);
//DEADCODE JIM 29/03/99 				(UWord&)ExpandBuff[i][0]=tc;
//DEADCODE JIM 29/03/99 			}
//DEADCODE JIM 29/03/99 		else
//DEADCODE JIM 29/03/99 			for (int i=0;i<256;i++)
//DEADCODE JIM 29/03/99 			{
//DEADCODE JIM 29/03/99 				UWord tc=*(ULong*)p & 0x00ffffff;
//DEADCODE JIM 29/03/99 				p+=3;
//DEADCODE JIM 29/03/99 				(ULong&)ExpandBuff[i][0]=tc;
//DEADCODE JIM 29/03/99 			}
//DEADCODE JIM 29/03/99 	}
//DEADCODE JIM 29/03/99 }
//DEADCODE JIM 29/03/99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE JIM 29/03/99 //Procedure		SetFontTables
//DEADCODE JIM 29/03/99 //Author		Jim Taylor
//DEADCODE JIM 29/03/99 //Date			Thu 22 May 1997
//DEADCODE JIM 29/03/99 //
//DEADCODE JIM 29/03/99 //Description	
//DEADCODE JIM 29/03/99 //
//DEADCODE JIM 29/03/99 //Inputs		
//DEADCODE JIM 29/03/99 //
//DEADCODE JIM 29/03/99 //Returns	
//DEADCODE JIM 29/03/99 //
//DEADCODE JIM 29/03/99 //------------------------------------------------------------------------------
//DEADCODE JIM 29/03/99 void Graphic::SetFontTables()
//DEADCODE JIM 29/03/99 {
//DEADCODE JIM 29/03/99 	if (BytesPerPixel>1 && fontcolour!=colour)
//DEADCODE JIM 29/03/99 	{
//DEADCODE JIM 29/03/99 		fontcolour=colour;
//DEADCODE JIM 29/03/99 		if (BytesPerPixel==2)
//DEADCODE JIM 29/03/99 		{
//DEADCODE JIM 29/03/99 			int db=colour*3;
//DEADCODE JIM 29/03/99 			int	dr=((((UByte*)Palette)[db++]) >> (7-RedBits))  <<  (RedShift);
//DEADCODE JIM 29/03/99 			int dg=((((UByte*)Palette)[db++]) >> (7-GreenBits))  <<  (GreenShift);
//DEADCODE JIM 29/03/99 				db=((((UByte*)Palette)[db++]) >> (7-BlueBits))  <<  (BlueShift); //256<<4=4096
//DEADCODE JIM 29/03/99 			int mb=(255>>(8-BlueBits))<<(BlueShift+8),
//DEADCODE JIM 29/03/99 				mg=(255>>(8-GreenBits))<<(GreenShift+8),
//DEADCODE JIM 29/03/99 				mr=(255>>(8-RedBits))<<(RedShift+8);
//DEADCODE JIM 29/03/99 
//DEADCODE JIM 29/03/99 			int	r=0,g=0,b=0;
//DEADCODE JIM 29/03/99 			for (int i=0;i<128;i++)
//DEADCODE JIM 29/03/99 			{
//DEADCODE JIM 29/03/99 				int c=((r&mr)+(b&mb)+(g&mg))>>8;
//DEADCODE JIM 29/03/99 				(UWord&)ExpandBuff[i][0]=c;//((r>>8)<<11)+((g>>8)<<5)+(b>>8);
//DEADCODE JIM 29/03/99 				r+=dr;
//DEADCODE JIM 29/03/99 				g+=dg;
//DEADCODE JIM 29/03/99 				b+=db;
//DEADCODE JIM 29/03/99 			}
//DEADCODE JIM 29/03/99 			(UWord&)ExpandBuff[0][0]=(UWord&)ExpandBuff[127][0];
//DEADCODE JIM 29/03/99 			dr-=mr+1;
//DEADCODE JIM 29/03/99 			dg-=mg+1;
//DEADCODE JIM 29/03/99 			db-=mb+1;
//DEADCODE JIM 29/03/99 			r=mr;
//DEADCODE JIM 29/03/99 			g=mg;
//DEADCODE JIM 29/03/99 			b=mb;
//DEADCODE JIM 29/03/99 			for (i=255;i>=128;i--)
//DEADCODE JIM 29/03/99 			{
//DEADCODE JIM 29/03/99 				int c=((r&mr)+(b&mb)+(g&mg))>>8;
//DEADCODE JIM 29/03/99 				(UWord&)ExpandBuff[i][0]=c;//((r>>8)<<11)+((g>>8)<<5)+(b>>8);
//DEADCODE JIM 29/03/99 				r+=dr;
//DEADCODE JIM 29/03/99 				g+=dg;
//DEADCODE JIM 29/03/99 				b+=db;
//DEADCODE JIM 29/03/99 			}
//DEADCODE JIM 29/03/99 		}
//DEADCODE JIM 29/03/99 		else
//DEADCODE JIM 29/03/99 		{
//DEADCODE JIM 29/03/99 			int dr=colour*3;
//DEADCODE JIM 29/03/99 			int db=((UByte*)Palette)[dr++]<<1; //256<<4=4096
//DEADCODE JIM 29/03/99 			int dg=((UByte*)Palette)[dr++]<<1;
//DEADCODE JIM 29/03/99 				dr=((UByte*)Palette)[dr++]<<1;
//DEADCODE JIM 29/03/99 			int	r=0,g=0,b=0;
//DEADCODE JIM 29/03/99 			for (int i=0;i<128;i++)
//DEADCODE JIM 29/03/99 			{
//DEADCODE JIM 29/03/99 				ExpandBuff[i][0]=b>>8;
//DEADCODE JIM 29/03/99 				ExpandBuff[i][1]=g>>8;
//DEADCODE JIM 29/03/99 				ExpandBuff[i][2]=r>>8;
//DEADCODE JIM 29/03/99 				ExpandBuff[i][3]=0;
//DEADCODE JIM 29/03/99 				r+=dr;
//DEADCODE JIM 29/03/99 				g+=dg;
//DEADCODE JIM 29/03/99 				b+=db;
//DEADCODE JIM 29/03/99 			}
//DEADCODE JIM 29/03/99 			(UWord&)ExpandBuff[0][0]=(UWord&)ExpandBuff[127][0];
//DEADCODE JIM 29/03/99 			dr-=511;
//DEADCODE JIM 29/03/99 			dg-=511;
//DEADCODE JIM 29/03/99 			db-=511;
//DEADCODE JIM 29/03/99 			r=65535;
//DEADCODE JIM 29/03/99 			g=65535;
//DEADCODE JIM 29/03/99 			b=65535;
//DEADCODE JIM 29/03/99 			for (i=255;i>=128;i--)
//DEADCODE JIM 29/03/99 			{
//DEADCODE JIM 29/03/99 				ExpandBuff[i][0]=b>>8;
//DEADCODE JIM 29/03/99 				ExpandBuff[i][1]=g>>8;
//DEADCODE JIM 29/03/99 				ExpandBuff[i][2]=r>>8;
//DEADCODE JIM 29/03/99 				ExpandBuff[i][3]=0;
//DEADCODE JIM 29/03/99 				r+=dr;
//DEADCODE JIM 29/03/99 				g+=dg;
//DEADCODE JIM 29/03/99 				b+=db;
//DEADCODE JIM 29/03/99 			}
//DEADCODE JIM 29/03/99 		//else
//DEADCODE JIM 29/03/99 
//DEADCODE JIM 29/03/99 
//DEADCODE JIM 29/03/99 		}
//DEADCODE JIM 29/03/99 	}
//DEADCODE JIM 29/03/99 }
//DEADCODE JIM 29/03/99 
//DEADCODE JIM 29/03/99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE JIM 29/03/99 //Procedure	Graphic::ShowPic
//DEADCODE JIM 29/03/99 //------------------------------------------------------------------------------
//DEADCODE JIM 29/03/99 //Author		Paul.   
//DEADCODE JIM 29/03/99 //Date			Thu 6 Jul 1995
//DEADCODE JIM 29/03/99 //Modified		DAW 22Jan96
//DEADCODE JIM 29/03/99 //
//DEADCODE JIM 29/03/99 //Description	Made it more cunning by use of a new SearchIFFHunk routine
//DEADCODE JIM 29/03/99 //
//DEADCODE JIM 29/03/99 //Inputs		mem pointer to lbm image
//DEADCODE JIM 29/03/99 //
//DEADCODE JIM 29/03/99 //Returns	
//DEADCODE JIM 29/03/99 //
//DEADCODE JIM 29/03/99 //Externals
//DEADCODE JIM 29/03/99 //------------------------------------------------------------------------------
//DEADCODE JIM 29/03/99 //------------------------------------------------------------------------------
//DEADCODE JIM 29/03/99 void Graphic::ShowPic(UByte *buffer)
//DEADCODE JIM 29/03/99 {
//DEADCODE JIM 29/03/99 	UByte* start=buffer;
//DEADCODE JIM 29/03/99 	UByte	*tmp;
//DEADCODE JIM 29/03/99 	SWord	picwidth,picheight,picy,picx,x,y;
//DEADCODE JIM 29/03/99 
//DEADCODE JIM 29/03/99 
//DEADCODE JIM 29/03/99 	tmp = SearchIFFHunk((UByte *)"BMHD",buffer);		//Process PBM header
//DEADCODE JIM 29/03/99 	if (tmp)
//DEADCODE JIM 29/03/99 	{
//DEADCODE JIM 29/03/99 		tmp = ReadWord(tmp,picwidth);
//DEADCODE JIM 29/03/99 		tmp = ReadWord(tmp,picheight);
//DEADCODE JIM 29/03/99 		tmp = ReadWord(tmp,picx);
//DEADCODE JIM 29/03/99 		tmp = ReadWord(tmp,picy);
//DEADCODE JIM 29/03/99 	}
//DEADCODE JIM 29/03/99 		x = picx;				//Only display the part of the image contained within
//DEADCODE JIM 29/03/99 		y = picy;				//the window defined by the screen structure
//DEADCODE JIM 29/03/99 		picheight+=y;
//DEADCODE JIM 29/03/99 
//DEADCODE JIM 29/03/99 
//DEADCODE JIM 29/03/99 	if (PhysicalMinY<master->ifflinenum)
//DEADCODE JIM 29/03/99 	{
//DEADCODE JIM 29/03/99 
//DEADCODE JIM 29/03/99 	tmp = SearchIFFHunk((UByte *)"CMAP",buffer);		//Process CMAP hunk - palette
//DEADCODE JIM 29/03/99 	if (tmp)
//DEADCODE JIM 29/03/99 		RegisterPalette(tmp,0x300);		//Signal to update palette on next screen swap
//DEADCODE JIM 29/03/99 
//DEADCODE JIM 29/03/99 	tmp = SearchIFFHunk((UByte *)"BODY",buffer);		//Process BODY hunk
//DEADCODE JIM 29/03/99 	}
//DEADCODE JIM 29/03/99 	else
//DEADCODE JIM 29/03/99 	{
//DEADCODE JIM 29/03/99 		tmp = start+master->iffoffset;
//DEADCODE JIM 29/03/99 		y = master->ifflinenum;
//DEADCODE JIM 29/03/99 	}
//DEADCODE JIM 29/03/99 	PalFontTables();											//PD 23May97
//DEADCODE JIM 29/03/99 
//DEADCODE JIM 29/03/99 	if (PhysicalMinY>picheight)	return;
//DEADCODE JIM 29/03/99 	if (PhysicalMinX>picwidth)	return;
//DEADCODE JIM 29/03/99 	if (PhysicalMaxY<picy)		return;
//DEADCODE JIM 29/03/99 	if (PhysicalMaxX<picx)		return;
//DEADCODE JIM 29/03/99 
//DEADCODE JIM 29/03/99 	if (tmp)
//DEADCODE JIM 29/03/99 	{
//DEADCODE JIM 29/03/99 		while(picheight>y && PhysicalMinY>y)
//DEADCODE JIM 29/03/99 		{
//DEADCODE JIM 29/03/99 			tmp = SkipRow(tmp,picwidth);
//DEADCODE JIM 29/03/99 			y++;
//DEADCODE JIM 29/03/99 		}
//DEADCODE JIM 29/03/99 
//DEADCODE JIM 29/03/99 		if (PhysicalMinY>0 && PhysicalMinY<master->ifflinenum)
//DEADCODE JIM 29/03/99 		{
//DEADCODE JIM 29/03/99 			master->ifflinenum=PhysicalMinY;
//DEADCODE JIM 29/03/99 			master->iffoffset=tmp-start;
//DEADCODE JIM 29/03/99 		}
//DEADCODE JIM 29/03/99 
//DEADCODE JIM 29/03/99 		int maxy=picheight;
//DEADCODE JIM 29/03/99 		if (PhysicalMinY+PhysicalHeight<maxy)
//DEADCODE JIM 29/03/99 			maxy=PhysicalMinY+PhysicalHeight;
//DEADCODE JIM 29/03/99 		const	int	LINESPERMOUSE	=	50;
//DEADCODE JIM 29/03/99 		int	yblock=((maxy-y)%LINESPERMOUSE)+y;
//DEADCODE JIM 29/03/99 		while(yblock>y)
//DEADCODE JIM 29/03/99 			tmp = UnpackRow(tmp,picwidth,x,y++,PhysicalMinX,PhysicalMinX+PhysicalWidth-1);
//DEADCODE JIM 29/03/99 		while (maxy>yblock)
//DEADCODE JIM 29/03/99 		{
//DEADCODE JIM 29/03/99 //			_Mouse.Move();
//DEADCODE JIM 29/03/99 			yblock+=LINESPERMOUSE;
//DEADCODE JIM 29/03/99 			while(yblock>y)
//DEADCODE JIM 29/03/99 				tmp = UnpackRow(tmp,picwidth,x,y++,PhysicalMinX,PhysicalMinX+PhysicalWidth-1);
//DEADCODE JIM 29/03/99 		}
//DEADCODE JIM 29/03/99 	}
//DEADCODE JIM 29/03/99 }
//DEADCODE JIM 29/03/99 
//DEADCODE JIM 29/03/99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE JIM 29/03/99 //Procedure	Graphic::ShowPic
//DEADCODE JIM 29/03/99 //------------------------------------------------------------------------------
//DEADCODE JIM 29/03/99 //Author		Paul.   
//DEADCODE JIM 29/03/99 //Date			Thu 6 Jul 1995
//DEADCODE JIM 29/03/99 //Modified		DAW 22Jan96
//DEADCODE JIM 29/03/99 //
//DEADCODE JIM 29/03/99 //Description	Made it more cunning by use of a new SearchIFFHunk routine
//DEADCODE JIM 29/03/99 //
//DEADCODE JIM 29/03/99 //Inputs		mem pointer to lbm image
//DEADCODE JIM 29/03/99 //
//DEADCODE JIM 29/03/99 //Returns	
//DEADCODE JIM 29/03/99 //
//DEADCODE JIM 29/03/99 //Externals
//DEADCODE JIM 29/03/99 //------------------------------------------------------------------------------
//DEADCODE JIM 29/03/99 //------------------------------------------------------------------------------
//DEADCODE JIM 29/03/99 void Graphic::ShowPicScaled(UByte *buffer,const int scale)
//DEADCODE JIM 29/03/99 {
//DEADCODE JIM 29/03/99 	UByte* start=buffer;
//DEADCODE JIM 29/03/99 	UByte	*tmp;
//DEADCODE JIM 29/03/99 	SWord	picwidth,picheight,picy,picx,x,y;
//DEADCODE JIM 29/03/99 
//DEADCODE JIM 29/03/99 
//DEADCODE JIM 29/03/99 	tmp = SearchIFFHunk((UByte *)"BMHD",buffer);		//Process PBM header
//DEADCODE JIM 29/03/99 	if (tmp)
//DEADCODE JIM 29/03/99 	{
//DEADCODE JIM 29/03/99 		tmp = ReadWord(tmp,picwidth);
//DEADCODE JIM 29/03/99 		tmp = ReadWord(tmp,picheight);
//DEADCODE JIM 29/03/99 		tmp = ReadWord(tmp,picx);
//DEADCODE JIM 29/03/99 		tmp = ReadWord(tmp,picy);
//DEADCODE JIM 29/03/99 	}
//DEADCODE JIM 29/03/99 		x = picx;				//Only display the part of the image contained within
//DEADCODE JIM 29/03/99 		y = picy;				//the window defined by the screen structure
//DEADCODE JIM 29/03/99 		picheight+=y;
//DEADCODE JIM 29/03/99 
//DEADCODE JIM 29/03/99 	int PMY = (PhysicalMinY+scale-1) /scale;
//DEADCODE JIM 29/03/99 
//DEADCODE JIM 29/03/99 
//DEADCODE JIM 29/03/99 	if (PMY<master->ifflinenum)
//DEADCODE JIM 29/03/99 	{
//DEADCODE JIM 29/03/99 
//DEADCODE JIM 29/03/99 		tmp = SearchIFFHunk((UByte *)"CMAP",buffer);		//Process CMAP hunk - palette
//DEADCODE JIM 29/03/99 		if (tmp)
//DEADCODE JIM 29/03/99 			RegisterPalette(tmp,0x300);		//Signal to update palette on next screen swap
//DEADCODE JIM 29/03/99 		tmp = SearchIFFHunk((UByte *)"BODY",buffer);		//Process BODY hunk
//DEADCODE JIM 29/03/99 	}
//DEADCODE JIM 29/03/99 	else
//DEADCODE JIM 29/03/99 	{
//DEADCODE JIM 29/03/99 		tmp = start+master->iffoffset;
//DEADCODE JIM 29/03/99 		y = master->ifflinenum;
//DEADCODE JIM 29/03/99 	}
//DEADCODE JIM 29/03/99 	PalFontTables();											//PD 23May97
//DEADCODE JIM 29/03/99 
//DEADCODE JIM 29/03/99 	y*=scale;
//DEADCODE JIM 29/03/99 	if (PhysicalMinY>=picheight*scale)	return;
//DEADCODE JIM 29/03/99 	if (PhysicalMinX>picwidth*scale)	return;
//DEADCODE JIM 29/03/99 	if (PhysicalMaxY<y)					return;
//DEADCODE JIM 29/03/99 	if (PhysicalMaxX<picx*scale)		return;
//DEADCODE JIM 29/03/99 
//DEADCODE JIM 29/03/99 
//DEADCODE JIM 29/03/99 	if (tmp)
//DEADCODE JIM 29/03/99 	{
//DEADCODE JIM 29/03/99 		int maxy=picheight*scale;
//DEADCODE JIM 29/03/99 		while(maxy>y && PhysicalMinY>y)
//DEADCODE JIM 29/03/99 		{
//DEADCODE JIM 29/03/99 			tmp = SkipRow(tmp,picwidth);
//DEADCODE JIM 29/03/99 			y+=scale;
//DEADCODE JIM 29/03/99 		}
//DEADCODE JIM 29/03/99 
//DEADCODE JIM 29/03/99 		if (PMY>0 && PMY<master->ifflinenum)
//DEADCODE JIM 29/03/99 		{
//DEADCODE JIM 29/03/99 			master->ifflinenum=PMY;
//DEADCODE JIM 29/03/99 			master->iffoffset=tmp-start;
//DEADCODE JIM 29/03/99 		}
//DEADCODE JIM 29/03/99 
//DEADCODE JIM 29/03/99 		if (PhysicalMaxY<maxy)
//DEADCODE JIM 29/03/99 			maxy=PhysicalMinY+PhysicalHeight;
//DEADCODE JIM 29/03/99 		maxy-=scale-1;
//DEADCODE JIM 29/03/99 		const	int	LINESPERMOUSE	=	50;
//DEADCODE JIM 29/03/99 		int	yblock=((maxy-y)%LINESPERMOUSE)+y;
//DEADCODE JIM 29/03/99 
//DEADCODE JIM 29/03/99 		if (scale==2)
//DEADCODE JIM 29/03/99 		{
//DEADCODE JIM 29/03/99 			while(yblock>y)
//DEADCODE JIM 29/03/99 			{
//DEADCODE JIM 29/03/99 				Unpack2Row(tmp,picwidth,x,y++,PhysicalMinX,PhysicalMinX+PhysicalWidth-1);
//DEADCODE JIM 29/03/99 				tmp = Unpack2Row(tmp,picwidth,x,y++,PhysicalMinX,PhysicalMinX+PhysicalWidth-1);
//DEADCODE JIM 29/03/99 			}
//DEADCODE JIM 29/03/99 			while (maxy>yblock)
//DEADCODE JIM 29/03/99 			{
//DEADCODE JIM 29/03/99 //				_Mouse.Move();
//DEADCODE JIM 29/03/99 				yblock+=LINESPERMOUSE;
//DEADCODE JIM 29/03/99 				while(yblock>y)
//DEADCODE JIM 29/03/99 				{
//DEADCODE JIM 29/03/99 					Unpack2Row(tmp,picwidth,x,y++,PhysicalMinX,PhysicalMinX+PhysicalWidth-1);
//DEADCODE JIM 29/03/99 					tmp = Unpack2Row(tmp,picwidth,x,y++,PhysicalMinX,PhysicalMinX+PhysicalWidth-1);
//DEADCODE JIM 29/03/99 				}
//DEADCODE JIM 29/03/99 			}
//DEADCODE JIM 29/03/99 		}
//DEADCODE JIM 29/03/99 		elseif (scale==4)
//DEADCODE JIM 29/03/99 		{
//DEADCODE JIM 29/03/99 			while(yblock>y)
//DEADCODE JIM 29/03/99 			{
//DEADCODE JIM 29/03/99 				Unpack4Row(tmp,picwidth,x,y++,PhysicalMinX,PhysicalMinX+PhysicalWidth-1);
//DEADCODE JIM 29/03/99 				Unpack4Row(tmp,picwidth,x,y++,PhysicalMinX,PhysicalMinX+PhysicalWidth-1);
//DEADCODE JIM 29/03/99 				Unpack4Row(tmp,picwidth,x,y++,PhysicalMinX,PhysicalMinX+PhysicalWidth-1);
//DEADCODE JIM 29/03/99 				tmp = Unpack4Row(tmp,picwidth,x,y++,PhysicalMinX,PhysicalMinX+PhysicalWidth-1);
//DEADCODE JIM 29/03/99 			}
//DEADCODE JIM 29/03/99 			while (maxy>yblock)
//DEADCODE JIM 29/03/99 			{
//DEADCODE JIM 29/03/99 //				_Mouse.Move();
//DEADCODE JIM 29/03/99 				yblock+=LINESPERMOUSE;
//DEADCODE JIM 29/03/99 				while(yblock>y)
//DEADCODE JIM 29/03/99 				{
//DEADCODE JIM 29/03/99 					Unpack4Row(tmp,picwidth,x,y++,PhysicalMinX,PhysicalMinX+PhysicalWidth-1);
//DEADCODE JIM 29/03/99 					Unpack4Row(tmp,picwidth,x,y++,PhysicalMinX,PhysicalMinX+PhysicalWidth-1);
//DEADCODE JIM 29/03/99 					Unpack4Row(tmp,picwidth,x,y++,PhysicalMinX,PhysicalMinX+PhysicalWidth-1);
//DEADCODE JIM 29/03/99 					tmp = Unpack4Row(tmp,picwidth,x,y++,PhysicalMinX,PhysicalMinX+PhysicalWidth-1);
//DEADCODE JIM 29/03/99 				}
//DEADCODE JIM 29/03/99 			}
//DEADCODE JIM 29/03/99 		}
//DEADCODE JIM 29/03/99 		elseif (scale==8)
//DEADCODE JIM 29/03/99 		{
//DEADCODE JIM 29/03/99 			while(yblock>y)
//DEADCODE JIM 29/03/99 			{
//DEADCODE JIM 29/03/99 				Unpack8Row(tmp,picwidth,x,y++,PhysicalMinX,PhysicalMinX+PhysicalWidth-1);
//DEADCODE JIM 29/03/99 				Unpack8Row(tmp,picwidth,x,y++,PhysicalMinX,PhysicalMinX+PhysicalWidth-1);
//DEADCODE JIM 29/03/99 				Unpack8Row(tmp,picwidth,x,y++,PhysicalMinX,PhysicalMinX+PhysicalWidth-1);
//DEADCODE JIM 29/03/99 				Unpack8Row(tmp,picwidth,x,y++,PhysicalMinX,PhysicalMinX+PhysicalWidth-1);
//DEADCODE JIM 29/03/99 				Unpack8Row(tmp,picwidth,x,y++,PhysicalMinX,PhysicalMinX+PhysicalWidth-1);
//DEADCODE JIM 29/03/99 				Unpack8Row(tmp,picwidth,x,y++,PhysicalMinX,PhysicalMinX+PhysicalWidth-1);
//DEADCODE JIM 29/03/99 				Unpack8Row(tmp,picwidth,x,y++,PhysicalMinX,PhysicalMinX+PhysicalWidth-1);
//DEADCODE JIM 29/03/99 				tmp = Unpack8Row(tmp,picwidth,x,y++,PhysicalMinX,PhysicalMinX+PhysicalWidth-1);
//DEADCODE JIM 29/03/99 			}
//DEADCODE JIM 29/03/99 			while (maxy>yblock)
//DEADCODE JIM 29/03/99 			{
//DEADCODE JIM 29/03/99 //				_Mouse.Move();
//DEADCODE JIM 29/03/99 				yblock+=LINESPERMOUSE;
//DEADCODE JIM 29/03/99 				while(yblock>y)
//DEADCODE JIM 29/03/99 				{
//DEADCODE JIM 29/03/99 					Unpack8Row(tmp,picwidth,x,y++,PhysicalMinX,PhysicalMinX+PhysicalWidth-1);
//DEADCODE JIM 29/03/99 					Unpack8Row(tmp,picwidth,x,y++,PhysicalMinX,PhysicalMinX+PhysicalWidth-1);
//DEADCODE JIM 29/03/99 					Unpack8Row(tmp,picwidth,x,y++,PhysicalMinX,PhysicalMinX+PhysicalWidth-1);
//DEADCODE JIM 29/03/99 					Unpack8Row(tmp,picwidth,x,y++,PhysicalMinX,PhysicalMinX+PhysicalWidth-1);
//DEADCODE JIM 29/03/99 					Unpack8Row(tmp,picwidth,x,y++,PhysicalMinX,PhysicalMinX+PhysicalWidth-1);
//DEADCODE JIM 29/03/99 					Unpack8Row(tmp,picwidth,x,y++,PhysicalMinX,PhysicalMinX+PhysicalWidth-1);
//DEADCODE JIM 29/03/99 					Unpack8Row(tmp,picwidth,x,y++,PhysicalMinX,PhysicalMinX+PhysicalWidth-1);
//DEADCODE JIM 29/03/99 					tmp = Unpack8Row(tmp,picwidth,x,y++,PhysicalMinX,PhysicalMinX+PhysicalWidth-1);
//DEADCODE JIM 29/03/99 				}
//DEADCODE JIM 29/03/99 			}
//DEADCODE JIM 29/03/99 		}
//DEADCODE JIM 29/03/99 		else
//DEADCODE JIM 29/03/99 		_Error.EmitSysErr("Scaling factor bad: %i",scale);
//DEADCODE JIM 29/03/99 	}
//DEADCODE JIM 29/03/99 }
//DEADCODE JIM 29/03/99 
//DEADCODE JIM 29/03/99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE JIM 29/03/99 //Procedure	GrafPrim.PrintColour
//DEADCODE JIM 29/03/99 //------------------------------------------------------------------------------
//DEADCODE JIM 29/03/99 //Author		Paul.   
//DEADCODE JIM 29/03/99 //Date		Tue 8 Aug 1995
//DEADCODE JIM 29/03/99 //Modified	
//DEADCODE JIM 29/03/99 //
//DEADCODE JIM 29/03/99 //Description	
//DEADCODE JIM 29/03/99 //
//DEADCODE JIM 29/03/99 //Inputs	
//DEADCODE JIM 29/03/99 //
//DEADCODE JIM 29/03/99 //Returns	
//DEADCODE JIM 29/03/99 //
//DEADCODE JIM 29/03/99 //Externals
//DEADCODE JIM 29/03/99 //------------------------------------------------------------------------------
//DEADCODE JIM 29/03/99 //------------------------------------------------------------------------------
//DEADCODE JIM 29/03/99 short Graphic::PrintColour(CharTableEntryPtr cte)
//DEADCODE JIM 29/03/99 {
//DEADCODE JIM 29/03/99 	PalFontTables();
//DEADCODE JIM 29/03/99 	SWord	sx,sy;		//Character start x and y coordinates
//DEADCODE JIM 29/03/99 	SWord	width,height;	//Width and height of the packed data
//DEADCODE JIM 29/03/99 	UByte	*src;
//DEADCODE JIM 29/03/99 
//DEADCODE JIM 29/03/99 	sx = CharX;
//DEADCODE JIM 29/03/99 	sy = CharY + cte->YShift;
//DEADCODE JIM 29/03/99 
//DEADCODE JIM 29/03/99 	width = cte->Width;
//DEADCODE JIM 29/03/99 	height = cte->Height+sy;
//DEADCODE JIM 29/03/99 
//DEADCODE JIM 29/03/99 	src = (UByte *) cte->pixeldata;								//DAW 29Nov95
//DEADCODE JIM 29/03/99 	if (height>(PhysicalMaxY))
//DEADCODE JIM 29/03/99 	{
//DEADCODE JIM 29/03/99 		while(sy<PhysicalMinY)
//DEADCODE JIM 29/03/99 		{
//DEADCODE JIM 29/03/99 			src = Graphic::SkipRow(src,width);
//DEADCODE JIM 29/03/99 			sy++;
//DEADCODE JIM 29/03/99 		}
//DEADCODE JIM 29/03/99 		while(sy<=(PhysicalMaxY))
//DEADCODE JIM 29/03/99 			src = Graphic::UnpackRow(src,width,sx,sy++,PhysicalMinX,PhysicalMinX+PhysicalWidth-1);
//DEADCODE JIM 29/03/99 	}
//DEADCODE JIM 29/03/99 	else
//DEADCODE JIM 29/03/99 	{
//DEADCODE JIM 29/03/99 		while(sy<PhysicalMinY)
//DEADCODE JIM 29/03/99 		{
//DEADCODE JIM 29/03/99 			src = Graphic::SkipRow(src,width);
//DEADCODE JIM 29/03/99 			sy++;
//DEADCODE JIM 29/03/99 		}
//DEADCODE JIM 29/03/99 		while(sy<height)
//DEADCODE JIM 29/03/99 			src = Graphic::UnpackRow(src,width,sx,sy++,PhysicalMinX,PhysicalMinX+PhysicalWidth-1);
//DEADCODE JIM 29/03/99 	}
//DEADCODE JIM 29/03/99 	return(0);
//DEADCODE JIM 29/03/99 }
//DEADCODE JIM 29/03/99 
//DEADCODE JIM 29/03/99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE JIM 29/03/99 //Procedure	GrafPrim.PrintShade
//DEADCODE JIM 29/03/99 //------------------------------------------------------------------------------
//DEADCODE JIM 29/03/99 //Author		Paul.   
//DEADCODE JIM 29/03/99 //Date		Tue 8 Aug 1995
//DEADCODE JIM 29/03/99 //Modified	
//DEADCODE JIM 29/03/99 //
//DEADCODE JIM 29/03/99 //Description	
//DEADCODE JIM 29/03/99 //
//DEADCODE JIM 29/03/99 //Inputs	
//DEADCODE JIM 29/03/99 //
//DEADCODE JIM 29/03/99 //Returns	
//DEADCODE JIM 29/03/99 //
//DEADCODE JIM 29/03/99 //Externals
//DEADCODE JIM 29/03/99 //------------------------------------------------------------------------------
//DEADCODE JIM 29/03/99 //------------------------------------------------------------------------------
//DEADCODE JIM 29/03/99 short Graphic::PrintShade(CharTableEntryPtr cte)
//DEADCODE JIM 29/03/99 {
//DEADCODE JIM 29/03/99 	SetFontTables();
//DEADCODE JIM 29/03/99 	SWord	sx,sy;					//Character start x and y coordinates
//DEADCODE JIM 29/03/99 	SWord	width,height;			//Width and height of the packed data
//DEADCODE JIM 29/03/99 	UByte	*src;
//DEADCODE JIM 29/03/99 
//DEADCODE JIM 29/03/99 	sx = CharX;
//DEADCODE JIM 29/03/99 	sy = CharY + cte->YShift;
//DEADCODE JIM 29/03/99 
//DEADCODE JIM 29/03/99 	width = cte->Width;
//DEADCODE JIM 29/03/99 	height = cte->Height+sy;
//DEADCODE JIM 29/03/99 
//DEADCODE JIM 29/03/99 	src = (UByte *) cte->pixeldata;								//DAW 29Nov95
//DEADCODE JIM 29/03/99 	if (height>(PhysicalMaxY))									//RDH 06Nov96
//DEADCODE JIM 29/03/99 	{
//DEADCODE JIM 29/03/99 		while(sy<PhysicalMinY)
//DEADCODE JIM 29/03/99 		{
//DEADCODE JIM 29/03/99 			src = Graphic::SkipRow(src,width);
//DEADCODE JIM 29/03/99 			sy++;
//DEADCODE JIM 29/03/99 		}
//DEADCODE JIM 29/03/99 		while(sy<=(PhysicalMaxY))								//RDH 06Nov96
//DEADCODE JIM 29/03/99 			src = Graphic::UnpackShadeRow(src,width,sx,sy++,PhysicalMinX,PhysicalMinX+PhysicalWidth-1);
//DEADCODE JIM 29/03/99 	}
//DEADCODE JIM 29/03/99 	else
//DEADCODE JIM 29/03/99 	{
//DEADCODE JIM 29/03/99 		while(sy<PhysicalMinY)
//DEADCODE JIM 29/03/99 		{
//DEADCODE JIM 29/03/99 			src = Graphic::SkipRow(src,width);
//DEADCODE JIM 29/03/99 			sy++;
//DEADCODE JIM 29/03/99 		}
//DEADCODE JIM 29/03/99 		while(sy<height)
//DEADCODE JIM 29/03/99 			src = Graphic::UnpackShadeRow(src,width,sx,sy++,PhysicalMinX,PhysicalMinX+PhysicalWidth-1);
//DEADCODE JIM 29/03/99 	}
//DEADCODE JIM 29/03/99 	return(0);
//DEADCODE JIM 29/03/99 }
//DEADCODE JIM 29/03/99 
//DEADCODE JIM 29/03/99 
//DEADCODE JIM 29/03/99 
//DEADCODE JIM 29/03/99 
