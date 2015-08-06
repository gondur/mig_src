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
//Filename       lbmfile.cpp
//System         
//Author         Paul.   
//Date           Tue 16 Jan 1996
//Description    lbm file writer code
//------------------------------------------------------------------------------

		#include	<stdlib.h>
		#include	<stdio.h>
//		#include	"wrapper.h"
		#include	"polygon.h"
		#include	"myerror.h"		
	
//TempCode PD 17Jan96 class	lbmwrite
//TempCode PD 17Jan96 {
//TempCode PD 17Jan96 	enum	MaskSet	{ mskNone = 0,mskHasMask,mskHasTransparentColour,mskLasso};
//TempCode PD 17Jan96 
//TempCode PD 17Jan96 	enum	CompSet	{ cmpNone = 0,cmpByteRun1};
//TempCode PD 17Jan96 
//TempCode PD 17Jan96 	typedef	UByte	Masking;
//TempCode PD 17Jan96 
//TempCode PD 17Jan96 	typedef	UByte	Compression;
//TempCode PD 17Jan96 
//TempCode PD 17Jan96 	typedef struct	image8
//TempCode PD 17Jan96 	{
//TempCode PD 17Jan96 		SWord	Width,Height;
//TempCode PD 17Jan96 		SLong	imagesize;
//TempCode PD 17Jan96 		UByte	bitmap;
//TempCode PD 17Jan96 	}
//TempCode PD 17Jan96 	Image8,*Image8P;
//TempCode PD 17Jan96 
//TempCode PD 17Jan96 	typedef	struct	bitmapheader
//TempCode PD 17Jan96 	{
//TempCode PD 17Jan96 		UWord	w,h;
//TempCode PD 17Jan96 		SWord	x,y;
//TempCode PD 17Jan96 		UByte	nPlanes;
//TempCode PD 17Jan96 		Masking	masking;
//TempCode PD 17Jan96 		Compression compression;
//TempCode PD 17Jan96 		UByte	pad1;
//TempCode PD 17Jan96 		UWord	transparentColour;
//TempCode PD 17Jan96 		UByte	xAspect,yAspect;
//TempCode PD 17Jan96 		SWord	pageWidth,pageHeight;
//TempCode PD 17Jan96 	}
//TempCode PD 17Jan96 	BitMapHeader,*BitMapHeaderP;
//TempCode PD 17Jan96 
//TempCode PD 17Jan96 	BitMapHeaderP	bmhd;
//TempCode PD 17Jan96 
//TempCode PD 17Jan96 	Bool	writepacked;
//TempCode PD 17Jan96 
//TempCode PD 17Jan96 	public:
//TempCode PD 17Jan96 		CON		lbmwrite()
//TempCode PD 17Jan96 		{
//TempCode PD 17Jan96 			bmhd = new BitMapHeader;
//TempCode PD 17Jan96 			writepacked=TRUE;
//TempCode PD 17Jan96 		};
//TempCode PD 17Jan96 
//TempCode PD 17Jan96 		CON		lbmwrite(Bool packflag)
//TempCode PD 17Jan96 		{
//TempCode PD 17Jan96 			bmhd = new BitMapHeader;
//TempCode PD 17Jan96 			writepacked=packflag;
//TempCode PD 17Jan96 		};
//TempCode PD 17Jan96 
//TempCode PD 17Jan96 		DES		~lbmwrite()
//TempCode PD 17Jan96 		{
//TempCode PD 17Jan96 			delete [] bmhd;
//TempCode PD 17Jan96 		};
//TempCode PD 17Jan96 
//TempCode PD 17Jan96 		void	WritePBM(UByteP pbmfilename,Image8P lbmimage,UByteP colourmap);
//TempCode PD 17Jan96 
//TempCode PD 17Jan96 	private:
//TempCode PD 17Jan96 
//TempCode PD 17Jan96 		void	PutHead(FILE *fp,SLong size);
//TempCode PD 17Jan96 
//TempCode PD 17Jan96 		void	Put16Bit(FILE *fp,SWord value);
//TempCode PD 17Jan96 
//TempCode PD 17Jan96 		void	Put32Bit(FILE *fp,SLong value);
//TempCode PD 17Jan96 
//TempCode PD 17Jan96 		void	PutID(FILE *fp,UByteP data);
//TempCode PD 17Jan96 
//TempCode PD 17Jan96 		void	PutBody(FILE *fp,UByteP data,SLong size);
//TempCode PD 17Jan96 
//TempCode PD 17Jan96 		void	PutCmap(FILE *fp,UByteP  data);
//TempCode PD 17Jan96 
//TempCode PD 17Jan96 		SLong	PackBody(Image8P lbmimage,UByteP op);
//TempCode PD 17Jan96 
//TempCode PD 17Jan96 		SLong	PackLine(UByteP ip,UByteP op, SLong limit);
//TempCode PD 17Jan96 
//TempCode PD 17Jan96 	protected:
//TempCode PD 17Jan96 
//TempCode PD 17Jan96 };

//DeadCode JIM 16Jul96 static	UByte	LBMHeader[]=
//DeadCode JIM 16Jul96 {
//DeadCode JIM 16Jul96 	0x046, 0x04f, 0x052, 0x04d, 0x000, 0x004, 0x0b3, 0x030,  0x050, 0x042, 0x04d, 0x020, 0x042, 0x04d, 0x048, 0x044,
//DeadCode JIM 16Jul96 	0x000, 0x000, 0x000, 0x014, 0x002, 0x080, 0x001, 0x0e0,  0x000, 0x000, 0x000, 0x000, 0x008, 0x000, 0x000, 0x000,
//DeadCode JIM 16Jul96 	0x000, 0x0ff, 0x001, 0x001, 0x002, 0x080, 0x001, 0x0e0,  0x043, 0x04d, 0x041, 0x050, 0x000, 0x000, 0x003, 0x000,
//DeadCode JIM 16Jul96 	0x000, 0x000, 0x000, 0x097, 0x0f3, 0x0ff, 0x0bf, 0x093,  0x03b, 0x000, 0x09f, 0x043, 0x0d3, 0x000, 0x000, 0x0a3,
//DeadCode JIM 16Jul96 	0x0a3, 0x0a3, 0x087, 0x057, 0x02f, 0x0cb, 0x0cb, 0x0cb,  0x07b, 0x07b, 0x07b, 0x04f, 0x0b7, 0x04b, 0x077, 0x0df,
//DeadCode JIM 16Jul96 	0x073, 0x027, 0x07f, 0x09f, 0x0ff, 0x06f, 0x06f, 0x053,  0x053, 0x053, 0x0ff, 0x0d7, 0x067, 0x0ff, 0x0ff, 0x0ff,
//DeadCode JIM 16Jul96 	0x00f, 0x000, 0x000, 0x02f, 0x000, 0x000, 0x053, 0x000,  0x000, 0x073, 0x000, 0x000, 0x097, 0x000, 0x000, 0x0b7,
//DeadCode JIM 16Jul96 	0x000, 0x000, 0x0db, 0x000, 0x000, 0x0ff, 0x000, 0x000,  0x0f3, 0x01b, 0x01b, 0x0e3, 0x037, 0x037, 0x0d7, 0x04f,
//DeadCode JIM 16Jul96 	0x04f, 0x0cb, 0x063, 0x063, 0x0bf, 0x077, 0x077, 0x0b3,  0x083, 0x083, 0x0a7, 0x08f, 0x08f, 0x09b, 0x09b, 0x09b,
//DeadCode JIM 16Jul96 	0x000, 0x000, 0x000, 0x011, 0x011, 0x011, 0x022, 0x022,  0x022, 0x033, 0x033, 0x033, 0x044, 0x044, 0x044, 0x055,
//DeadCode JIM 16Jul96 	0x055, 0x055, 0x066, 0x066, 0x066, 0x077, 0x077, 0x077,  0x088, 0x088, 0x088, 0x099, 0x099, 0x099, 0x0aa, 0x0aa,
//DeadCode JIM 16Jul96 	0x0aa, 0x0bb, 0x0bb, 0x0bb, 0x0cc, 0x0cc, 0x0cc, 0x0dd,  0x0dd, 0x0dd, 0x0ee, 0x0ee, 0x0ee, 0x0ff, 0x0ff, 0x0ff,
//DeadCode JIM 16Jul96 	0x0f9, 0x0f9, 0x0f9, 0x0f3, 0x0f3, 0x0f3, 0x0ec, 0x0ec,  0x0ec, 0x0e6, 0x0e6, 0x0e6, 0x0e0, 0x0e0, 0x0e0, 0x0da,
//DeadCode JIM 16Jul96 	0x0da, 0x0da, 0x0d3, 0x0d3, 0x0d3, 0x0cd, 0x0cd, 0x0cd,  0x0c7, 0x0c7, 0x0c7, 0x0c1, 0x0c1, 0x0c1, 0x0ba, 0x0ba,
//DeadCode JIM 16Jul96 	0x0ba, 0x0b4, 0x0b4, 0x0b4, 0x0ae, 0x0ae, 0x0ae, 0x0a8,  0x0a8, 0x0a8, 0x0a1, 0x0a1, 0x0a1, 0x09b, 0x09b, 0x09b,
//DeadCode JIM 16Jul96 	0x00f, 0x023, 0x027, 0x01f, 0x02f, 0x02b, 0x027, 0x037,  0x02f, 0x033, 0x047, 0x037, 0x043, 0x057, 0x03b, 0x04f,
//DeadCode JIM 16Jul96 	0x067, 0x043, 0x057, 0x06f, 0x047, 0x05f, 0x077, 0x04b,  0x067, 0x07c, 0x055, 0x06e, 0x080, 0x05f, 0x076, 0x085,
//DeadCode JIM 16Jul96 	0x069, 0x07d, 0x089, 0x073, 0x085, 0x08e, 0x07d, 0x08c,  0x092, 0x087, 0x094, 0x097, 0x091, 0x09b, 0x09b, 0x09b,
//DeadCode JIM 16Jul96 	0x057, 0x05b, 0x047, 0x05b, 0x063, 0x04b, 0x063, 0x06b,  0x04f, 0x06b, 0x073, 0x053, 0x06f, 0x077, 0x05b, 0x077,
//DeadCode JIM 16Jul96 	0x07f, 0x05f, 0x07f, 0x087, 0x063, 0x083, 0x08f, 0x067,  0x08b, 0x097, 0x06b, 0x08d, 0x098, 0x072, 0x090, 0x098,
//DeadCode JIM 16Jul96 	0x079, 0x092, 0x099, 0x080, 0x094, 0x099, 0x086, 0x096,  0x09a, 0x08d, 0x099, 0x09a, 0x094, 0x09b, 0x09b, 0x09b,
//DeadCode JIM 16Jul96 	0x08f, 0x073, 0x04b, 0x093, 0x07b, 0x04f, 0x09b, 0x07f,  0x04f, 0x0ab, 0x08b, 0x053, 0x0b3, 0x093, 0x057, 0x0bf,
//DeadCode JIM 16Jul96 	0x09f, 0x05b, 0x0cf, 0x0ab, 0x05f, 0x0d3, 0x0b3, 0x063,  0x0e3, 0x0bf, 0x067, 0x0d9, 0x0ba, 0x06e, 0x0ce, 0x0b5,
//DeadCode JIM 16Jul96 	0x076, 0x0c4, 0x0b0, 0x07d, 0x0ba, 0x0aa, 0x085, 0x0b0,  0x0a5, 0x08c, 0x0a5, 0x0a0, 0x094, 0x09b, 0x09b, 0x09b,
//DeadCode JIM 16Jul96 	0x03f, 0x04b, 0x03f, 0x043, 0x04f, 0x043, 0x047, 0x053,  0x047, 0x047, 0x05b, 0x047, 0x04b, 0x05b, 0x04b, 0x04f,
//DeadCode JIM 16Jul96 	0x063, 0x04f, 0x04f, 0x067, 0x04f, 0x053, 0x06b, 0x053,  0x05f, 0x073, 0x05f, 0x068, 0x079, 0x068, 0x070, 0x07e,
//DeadCode JIM 16Jul96 	0x070, 0x079, 0x084, 0x079, 0x081, 0x08a, 0x081, 0x08a,  0x090, 0x08a, 0x092, 0x095, 0x092, 0x09b, 0x09b, 0x09b,
//DeadCode JIM 16Jul96 	0x033, 0x043, 0x057, 0x03b, 0x04b, 0x05f, 0x043, 0x053,  0x067, 0x04b, 0x05b, 0x06f, 0x053, 0x063, 0x077, 0x05b,
//DeadCode JIM 16Jul96 	0x06b, 0x07f, 0x063, 0x073, 0x087, 0x06b, 0x077, 0x08b,  0x077, 0x087, 0x09b, 0x07c, 0x08a, 0x09b, 0x081, 0x08d,
//DeadCode JIM 16Jul96 	0x09b, 0x086, 0x090, 0x09b, 0x08c, 0x092, 0x09b, 0x091,  0x095, 0x09b, 0x096, 0x098, 0x09b, 0x09b, 0x09b, 0x09b,
//DeadCode JIM 16Jul96 	0x0cb, 0x0b3, 0x08b, 0x0cf, 0x0b7, 0x08f, 0x0d7, 0x0bf,  0x093, 0x0df, 0x0c3, 0x097, 0x0e7, 0x0cb, 0x09f, 0x0ef,
//DeadCode JIM 16Jul96 	0x0d3, 0x0a3, 0x0f7, 0x0d7, 0x0a7, 0x0ff, 0x0df, 0x0af,  0x0f7, 0x0db, 0x0b3, 0x0ea, 0x0d2, 0x0b0, 0x0dd, 0x0c9,
//DeadCode JIM 16Jul96 	0x0ac, 0x0d0, 0x0c0, 0x0a9, 0x0c2, 0x0b6, 0x0a5, 0x0b5,  0x0ad, 0x0a2, 0x0a8, 0x0a4, 0x09e, 0x09b, 0x09b, 0x09b,
//DeadCode JIM 16Jul96 	0x07b, 0x063, 0x043, 0x082, 0x069, 0x048, 0x08a, 0x070,  0x04e, 0x091, 0x076, 0x053, 0x098, 0x07d, 0x059, 0x09f,
//DeadCode JIM 16Jul96 	0x083, 0x05e, 0x0a7, 0x08a, 0x064, 0x0ae, 0x090, 0x069,  0x0b2, 0x09a, 0x07b, 0x0af, 0x09a, 0x080, 0x0ab, 0x09a,
//DeadCode JIM 16Jul96 	0x084, 0x0a8, 0x09a, 0x089, 0x0a5, 0x09b, 0x08d, 0x0a2,  0x09b, 0x092, 0x09e, 0x09b, 0x096, 0x09b, 0x09b, 0x09b,
//DeadCode JIM 16Jul96 	0x043, 0x02f, 0x03f, 0x04b, 0x033, 0x047, 0x057, 0x037,  0x053, 0x05f, 0x03b, 0x05f, 0x06b, 0x03b, 0x06b, 0x073,
//DeadCode JIM 16Jul96 	0x03f, 0x073, 0x07b, 0x043, 0x07f, 0x07f, 0x04b, 0x083,  0x07f, 0x053, 0x083, 0x083, 0x05d, 0x086, 0x087, 0x068,
//DeadCode JIM 16Jul96 	0x08a, 0x08b, 0x072, 0x08d, 0x08f, 0x07c, 0x091, 0x093,  0x086, 0x094, 0x097, 0x091, 0x098, 0x09b, 0x09b, 0x09b,
//DeadCode JIM 16Jul96 	0x02d, 0x025, 0x01a, 0x038, 0x02e, 0x020, 0x043, 0x036,  0x026, 0x04e, 0x03f, 0x02c, 0x058, 0x048, 0x032, 0x063,
//DeadCode JIM 16Jul96 	0x051, 0x038, 0x06e, 0x059, 0x03e, 0x079, 0x062, 0x044,  0x082, 0x072, 0x05a, 0x086, 0x078, 0x063, 0x089, 0x07e,
//DeadCode JIM 16Jul96 	0x06d, 0x08d, 0x084, 0x076, 0x090, 0x089, 0x07f, 0x094,  0x08f, 0x088, 0x097, 0x095, 0x092, 0x09b, 0x09b, 0x09b,
//DeadCode JIM 16Jul96 	0x0f9, 0x0f9, 0x0f9, 0x0f2, 0x0f5, 0x0f8, 0x0eb, 0x0f0,  0x0f7, 0x0e5, 0x0ec, 0x0f6, 0x0de, 0x0e8, 0x0f6, 0x0d7,
//DeadCode JIM 16Jul96 	0x0e4, 0x0f5, 0x0d0, 0x0df, 0x0f4, 0x0c9, 0x0db, 0x0f3,  0x0c3, 0x0d7, 0x0f2, 0x0bc, 0x0d3, 0x0f1, 0x0b5, 0x0ce,
//DeadCode JIM 16Jul96 	0x0f0, 0x0ae, 0x0ca, 0x0ef, 0x0a7, 0x0c6, 0x0ef, 0x0a1,  0x0c2, 0x0ee, 0x09a, 0x0bd, 0x0ed, 0x093, 0x0b9, 0x0ec,
//DeadCode JIM 16Jul96 	0x041, 0x02b, 0x018, 0x04b, 0x031, 0x01b, 0x055, 0x038,  0x01f, 0x05f, 0x03e, 0x022, 0x069, 0x044, 0x025, 0x073,
//DeadCode JIM 16Jul96 	0x04a, 0x028, 0x07d, 0x051, 0x02c, 0x087, 0x057, 0x02f,  0x08a, 0x060, 0x03d, 0x08c, 0x068, 0x04a, 0x08f, 0x071,
//DeadCode JIM 16Jul96 	0x058, 0x091, 0x079, 0x065, 0x094, 0x082, 0x073, 0x096,  0x08a, 0x080, 0x099, 0x093, 0x08e, 0x09b, 0x09b, 0x09b,
//DeadCode JIM 16Jul96 	0x000, 0x000, 0x000, 0x03f, 0x000, 0x000, 0x07f, 0x000,  0x000, 0x0bf, 0x000, 0x000, 0x0d3, 0x01f, 0x000, 0x0e7,
//DeadCode JIM 16Jul96 	0x043, 0x000, 0x0ff, 0x073, 0x000, 0x0ff, 0x0a3, 0x023,  0x0ff, 0x0c7, 0x047, 0x0ff, 0x0e7, 0x06b, 0x0ff, 0x0fb,
//DeadCode JIM 16Jul96 	0x08f, 0x0ff, 0x0fb, 0x0c3, 0x0ff, 0x0ff, 0x0ff, 0x000,  0x000, 0x0ff, 0x0ff, 0x000, 0x0ff, 0x0ff, 0x0ff, 0x0ff,
//DeadCode JIM 16Jul96 	0x042, 0x04f, 0x044, 0x059, 0x000, 0x004, 0x0b0, 0x000  
//DeadCode JIM 16Jul96 };
//DeadCode JIM 16Jul96 
//DeadCode JIM 16Jul96 char shotname[]="shot00.lbm";
//DeadCode JIM 16Jul96 
//DeadCode JIM 16Jul96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JIM 16Jul96 //Procedure		ScreenShot
//DeadCode JIM 16Jul96 //Author		Paul.   
//DeadCode JIM 16Jul96 //Date			Wed 17 Jan 1996
//DeadCode JIM 16Jul96 //
//DeadCode JIM 16Jul96 //Description	
//DeadCode JIM 16Jul96 //
//DeadCode JIM 16Jul96 //Inputs		
//DeadCode JIM 16Jul96 //
//DeadCode JIM 16Jul96 //Returns	
//DeadCode JIM 16Jul96 //
//DeadCode JIM 16Jul96 //------------------------------------------------------------------------------
//DeadCode JIM 16Jul96 void polygon::ScreenShot(Window* screen)
//DeadCode JIM 16Jul96 {
//DeadCode JIM 16Jul96  	FILE	*op;
//DeadCode JIM 16Jul96 
//DeadCode JIM 16Jul96 	LogicalPtr screen_mem = screen->logicalscreenptr;
//DeadCode JIM 16Jul96 
//DeadCode JIM 16Jul96 	int	i;
//DeadCode JIM 16Jul96 
//DeadCode JIM 16Jul96 	char	c;
//DeadCode JIM 16Jul96 
//DeadCode JIM 16Jul96 	op = fopen(shotname,"wb");
//DeadCode JIM 16Jul96 
//DeadCode JIM 16Jul96 	c = (char )(shotname[5]+1);
//DeadCode JIM 16Jul96 
//DeadCode JIM 16Jul96 	if(c>'9')	c='A';
//DeadCode JIM 16Jul96 
//DeadCode JIM 16Jul96 	if(c>'Z')	c='0';
//DeadCode JIM 16Jul96 
//DeadCode JIM 16Jul96 	shotname[5]=c;
//DeadCode JIM 16Jul96 
//DeadCode JIM 16Jul96 	for(i=0;i<sizeof(LBMHeader);i++)
//DeadCode JIM 16Jul96 	{
//DeadCode JIM 16Jul96 		c = (char )LBMHeader[i];
//DeadCode JIM 16Jul96 		putc(c,op);
//DeadCode JIM 16Jul96 	}
//DeadCode JIM 16Jul96 
//DeadCode JIM 16Jul96 	for(i=640*480;i--;)
//DeadCode JIM 16Jul96 	{
//DeadCode JIM 16Jul96 		c = (char )*screen_mem;
//DeadCode JIM 16Jul96 		putc(c,op);
//DeadCode JIM 16Jul96 		screen_mem++;
//DeadCode JIM 16Jul96 	}
//DeadCode JIM 16Jul96 
//DeadCode JIM 16Jul96 	fclose(op);
//DeadCode JIM 16Jul96 }

//TempCode PD 17Jan96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//TempCode PD 17Jan96 //Procedure		WritePBM
//TempCode PD 17Jan96 //Author		Paul.   
//TempCode PD 17Jan96 //Date			Tue 16 Jan 1996
//TempCode PD 17Jan96 //
//TempCode PD 17Jan96 //Description	
//TempCode PD 17Jan96 //
//TempCode PD 17Jan96 //Inputs		
//TempCode PD 17Jan96 //
//TempCode PD 17Jan96 //Returns	
//TempCode PD 17Jan96 //
//TempCode PD 17Jan96 //------------------------------------------------------------------------------
//TempCode PD 17Jan96 void lbmwrite::WritePBM(UByteP pbmfilename,Image8P lbmimage,UByteP colourmap)
//TempCode PD 17Jan96 {
//TempCode PD 17Jan96 	FILE	*fp;
//TempCode PD 17Jan96 	UByteP	op;
//TempCode PD 17Jan96 
//TempCode PD 17Jan96 	SLong	filesize;
//TempCode PD 17Jan96 
//TempCode PD 17Jan96 	if((fp=fopen((char *)pbmfilename,"wb"))==NULL)
//TempCode PD 17Jan96 		_Error.EmitSysErr(__FILE__":Unable to open o/p file (%s)",pbmfilename);
//TempCode PD 17Jan96 
//TempCode PD 17Jan96 	bmhd->w =
//TempCode PD 17Jan96 		bmhd->pageWidth = lbmimage->Width;
//TempCode PD 17Jan96 
//TempCode PD 17Jan96 	bmhd->h =
//TempCode PD 17Jan96 		bmhd->pageHeight = lbmimage->Height;
//TempCode PD 17Jan96 
//TempCode PD 17Jan96 	bmhd->compression = (Compression )cmpNone;
//TempCode PD 17Jan96 
//TempCode PD 17Jan96 	if(writepacked)
//TempCode PD 17Jan96 	{
//TempCode PD 17Jan96 		bmhd->compression = (Compression )cmpByteRun1;
//TempCode PD 17Jan96 
//TempCode PD 17Jan96 		op = (UByteP )malloc(sizeof(UByte)*lbmimage->imagesize*2);
//TempCode PD 17Jan96 
//TempCode PD 17Jan96 		if(op==NULL)
//TempCode PD 17Jan96 			_Error.EmitSysErr(__FILE__":mem alloc failed in pbmwrite");
//TempCode PD 17Jan96 
//TempCode PD 17Jan96 		filesize = PackBody(lbmimage,op);
//TempCode PD 17Jan96 		PutHead(fp,filesize);
//TempCode PD 17Jan96 		PutCmap(fp,colourmap);
//TempCode PD 17Jan96 		PutBody(fp,op,filesize);
//TempCode PD 17Jan96 		free(op);
//TempCode PD 17Jan96 
//TempCode PD 17Jan96 	}
//TempCode PD 17Jan96 	fclose(fp);
//TempCode PD 17Jan96 }
//TempCode PD 17Jan96 
//TempCode PD 17Jan96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//TempCode PD 17Jan96 //Procedure		PutHead
//TempCode PD 17Jan96 //Author		Paul.   
//TempCode PD 17Jan96 //Date			Tue 16 Jan 1996
//TempCode PD 17Jan96 //
//TempCode PD 17Jan96 //Description	
//TempCode PD 17Jan96 //
//TempCode PD 17Jan96 //Inputs		
//TempCode PD 17Jan96 //
//TempCode PD 17Jan96 //Returns	
//TempCode PD 17Jan96 //
//TempCode PD 17Jan96 //------------------------------------------------------------------------------
//TempCode PD 17Jan96 void lbmwrite::PutHead(FILE *fp, SLong size)
//TempCode PD 17Jan96 {
//TempCode PD 17Jan96 	size+=0x0330;
//TempCode PD 17Jan96 
//TempCode PD 17Jan96 	PutID(fp,"FORM");
//TempCode PD 17Jan96 	Put32Bit(fp,size);
//TempCode PD 17Jan96 	PutID(fp,"PBM ");
//TempCode PD 17Jan96 
//TempCode PD 17Jan96 	PutID(fp,"BMHD");
//TempCode PD 17Jan96 	Put32Bit(fp,20);
//TempCode PD 17Jan96 
//TempCode PD 17Jan96 	Put16Bit(fp,bmhd->w);
//TempCode PD 17Jan96 	Put16Bit(fp,bmhd->h);
//TempCode PD 17Jan96 	Put16Bit(fp,bmhd->x);
//TempCode PD 17Jan96 	Put16Bit(fp,bmhd->y);
//TempCode PD 17Jan96 	putc(bmhd->nPlanes,fp);
//TempCode PD 17Jan96 	putc(bmhd->masking,fp);
//TempCode PD 17Jan96 	putc(bmhd->compression,fp);
//TempCode PD 17Jan96 	putc(bmhd->pad1,fp);
//TempCode PD 17Jan96 	Put16Bit(fp,bmhd->transparentColour);
//TempCode PD 17Jan96 	putc(bmhd->xAspect,fp);
//TempCode PD 17Jan96 	putc(bmhd->yAspect,fp);
//TempCode PD 17Jan96 	Put16Bit(fp,bmhd->pageWidth);
//TempCode PD 17Jan96 	Put16Bit(fp,bmhd->pageHeight);
//TempCode PD 17Jan96 }
//TempCode PD 17Jan96 
//TempCode PD 17Jan96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//TempCode PD 17Jan96 //Procedure		Put16Bit
//TempCode PD 17Jan96 //Author		Paul.   
//TempCode PD 17Jan96 //Date			Tue 16 Jan 1996
//TempCode PD 17Jan96 //
//TempCode PD 17Jan96 //Description	
//TempCode PD 17Jan96 //
//TempCode PD 17Jan96 //Inputs		
//TempCode PD 17Jan96 //
//TempCode PD 17Jan96 //Returns	
//TempCode PD 17Jan96 //
//TempCode PD 17Jan96 //------------------------------------------------------------------------------
//TempCode PD 17Jan96 void lbmwrite::Put16Bit(FILE *fp,SWord value)
//TempCode PD 17Jan96 {
//TempCode PD 17Jan96  	UByte	c;
//TempCode PD 17Jan96 
//TempCode PD 17Jan96 	c = (UByte )(0x000FF & (value>>8));
//TempCode PD 17Jan96 	putc(c,fp);
//TempCode PD 17Jan96 	c = (UByte )(0x000FF & value);
//TempCode PD 17Jan96 	putc(c,fp);
//TempCode PD 17Jan96 }
//TempCode PD 17Jan96 
//TempCode PD 17Jan96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//TempCode PD 17Jan96 //Procedure		Put32Bit
//TempCode PD 17Jan96 //Author		Paul.   
//TempCode PD 17Jan96 //Date			Tue 16 Jan 1996
//TempCode PD 17Jan96 //
//TempCode PD 17Jan96 //Description	
//TempCode PD 17Jan96 //
//TempCode PD 17Jan96 //Inputs		
//TempCode PD 17Jan96 //
//TempCode PD 17Jan96 //Returns	
//TempCode PD 17Jan96 //
//TempCode PD 17Jan96 //------------------------------------------------------------------------------
//TempCode PD 17Jan96 void lbmwrite::Put32Bit(FILE *fp,SLong value)
//TempCode PD 17Jan96 {
//TempCode PD 17Jan96 	UByte	c;
//TempCode PD 17Jan96 
//TempCode PD 17Jan96 	c = (UByte )(0x000FF & (value>>24));
//TempCode PD 17Jan96 	putc(c,fp);
//TempCode PD 17Jan96 	c = (UByte )(0x000FF & (value>>16));
//TempCode PD 17Jan96 	putc(c,fp);
//TempCode PD 17Jan96 	c = (UByte )(0x000FF & (value>>8));
//TempCode PD 17Jan96 	putc(c,fp);
//TempCode PD 17Jan96 	c = (UByte )(0x000FF & value);
//TempCode PD 17Jan96 	putc(c,fp);
//TempCode PD 17Jan96 }
//TempCode PD 17Jan96 
//TempCode PD 17Jan96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//TempCode PD 17Jan96 //Procedure		PutID
//TempCode PD 17Jan96 //Author		Paul.   
//TempCode PD 17Jan96 //Date			Tue 16 Jan 1996
//TempCode PD 17Jan96 //
//TempCode PD 17Jan96 //Description	
//TempCode PD 17Jan96 //
//TempCode PD 17Jan96 //Inputs		
//TempCode PD 17Jan96 //
//TempCode PD 17Jan96 //Returns	
//TempCode PD 17Jan96 //
//TempCode PD 17Jan96 //------------------------------------------------------------------------------
//TempCode PD 17Jan96 void lbmwrite::PutID(FILE *fp,UByteP data)
//TempCode PD 17Jan96 {
//TempCode PD 17Jan96 	putc(*data,fp);data++;
//TempCode PD 17Jan96 	putc(*data,fp);data++;
//TempCode PD 17Jan96 	putc(*data,fp);data++;
//TempCode PD 17Jan96 	putc(*data,fp);
//TempCode PD 17Jan96 }
//TempCode PD 17Jan96 
//TempCode PD 17Jan96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//TempCode PD 17Jan96 //Procedure		PutBody
//TempCode PD 17Jan96 //Author		Paul.   
//TempCode PD 17Jan96 //Date			Tue 16 Jan 1996
//TempCode PD 17Jan96 //
//TempCode PD 17Jan96 //Description	
//TempCode PD 17Jan96 //
//TempCode PD 17Jan96 //Inputs		
//TempCode PD 17Jan96 //
//TempCode PD 17Jan96 //Returns	
//TempCode PD 17Jan96 //
//TempCode PD 17Jan96 //------------------------------------------------------------------------------
//TempCode PD 17Jan96 void lbmwrite::PutBody(FILE *fp,UByteP data,SLong size)
//TempCode PD 17Jan96 {
//TempCode PD 17Jan96 	int	j;
//TempCode PD 17Jan96 
//TempCode PD 17Jan96  	PutID(fp,"BODY");
//TempCode PD 17Jan96 	Put32Bit(fp,size);
//TempCode PD 17Jan96 
//TempCode PD 17Jan96 	for(j=size;j--;putc(*data++,fp));
//TempCode PD 17Jan96 }
//TempCode PD 17Jan96 
//TempCode PD 17Jan96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//TempCode PD 17Jan96 //Procedure		PutCmap
//TempCode PD 17Jan96 //Author		Paul.   
//TempCode PD 17Jan96 //Date			Tue 16 Jan 1996
//TempCode PD 17Jan96 //
//TempCode PD 17Jan96 //Description	
//TempCode PD 17Jan96 //
//TempCode PD 17Jan96 //Inputs		
//TempCode PD 17Jan96 //
//TempCode PD 17Jan96 //Returns	
//TempCode PD 17Jan96 //
//TempCode PD 17Jan96 //------------------------------------------------------------------------------
//TempCode PD 17Jan96 void lbmwrite::PutCmap(FILE *fp,UByteP  data)
//TempCode PD 17Jan96 {
//TempCode PD 17Jan96 	SLong	j;
//TempCode PD 17Jan96 
//TempCode PD 17Jan96 	PutID(fp,"CMAP");
//TempCode PD 17Jan96 	Put32Bit(fp,768);
//TempCode PD 17Jan96 	for(j=3*256;j--;putc(*data++,fp));
//TempCode PD 17Jan96 }
//TempCode PD 17Jan96 
//TempCode PD 17Jan96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//TempCode PD 17Jan96 //Procedure		PackBody
//TempCode PD 17Jan96 //Author		Paul.   
//TempCode PD 17Jan96 //Date			Tue 16 Jan 1996
//TempCode PD 17Jan96 //
//TempCode PD 17Jan96 //Description	
//TempCode PD 17Jan96 //
//TempCode PD 17Jan96 //Inputs		
//TempCode PD 17Jan96 //
//TempCode PD 17Jan96 //Returns	
//TempCode PD 17Jan96 //
//TempCode PD 17Jan96 //------------------------------------------------------------------------------
//TempCode PD 17Jan96 SLong lbmwrite::PackBody(Image8P lbmimage,UByteP op)
//TempCode PD 17Jan96 {
//TempCode PD 17Jan96 	SLong filelen = 0;
//TempCode PD 17Jan96 
//TempCode PD 17Jan96 	UByteP ip = &(lbmimage->bitmap);
//TempCode PD 17Jan96 
//TempCode PD 17Jan96 	SLong	i,j;
//TempCode PD 17Jan96 
//TempCode PD 17Jan96 	for(i=lbmimage->Height;i--;)
//TempCode PD 17Jan96 	{
//TempCode PD 17Jan96 		j = PackLine(ip,op,lbmimage->Width);
//TempCode PD 17Jan96 
//TempCode PD 17Jan96 		filelen += j;
//TempCode PD 17Jan96 
//TempCode PD 17Jan96 		ip += lbmimage->Width;
//TempCode PD 17Jan96 
//TempCode PD 17Jan96 		op += j;
//TempCode PD 17Jan96 	}
//TempCode PD 17Jan96 	if(filelen & 0x0001)
//TempCode PD 17Jan96 	{
//TempCode PD 17Jan96 		*op++ = 0x080;
//TempCode PD 17Jan96 		filelen++;
//TempCode PD 17Jan96 	}
//TempCode PD 17Jan96 	return(filelen);
//TempCode PD 17Jan96 }
//TempCode PD 17Jan96 
//TempCode PD 17Jan96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//TempCode PD 17Jan96 //Procedure		PackLine
//TempCode PD 17Jan96 //Author		Paul.   
//TempCode PD 17Jan96 //Date			Tue 16 Jan 1996
//TempCode PD 17Jan96 //
//TempCode PD 17Jan96 //Description	
//TempCode PD 17Jan96 //
//TempCode PD 17Jan96 //Inputs		
//TempCode PD 17Jan96 //
//TempCode PD 17Jan96 //Returns	
//TempCode PD 17Jan96 //
//TempCode PD 17Jan96 //------------------------------------------------------------------------------
//TempCode PD 17Jan96 SLong lbmwrite::PackLine(UByteP ip,UByteP op, SLong limit)
//TempCode PD 17Jan96 {
//TempCode PD 17Jan96 	UByte	j;
//TempCode PD 17Jan96 	Bool	flag;
//TempCode PD 17Jan96 	SLong	y = 0;
//TempCode PD 17Jan96 	SLong	i,z;
//TempCode PD 17Jan96 	SLong	filelen=0;
//TempCode PD 17Jan96 
//TempCode PD 17Jan96 	while (y<limit){
//TempCode PD 17Jan96 		if	(ip[y] == ip[y+1]){		/* packable */
//TempCode PD 17Jan96 			z=y;
//TempCode PD 17Jan96 			j=ip[y];
//TempCode PD 17Jan96 			while ((ip[z]==j) && (z<limit) && (z-y<128)){
//TempCode PD 17Jan96 					z += 1;
//TempCode PD 17Jan96 			}
//TempCode PD 17Jan96 			*op++ = (UByte )(256 - ((z-y)-1));		/* write count */
//TempCode PD 17Jan96 			*op++ = j;
//TempCode PD 17Jan96 			filelen += 2;
//TempCode PD 17Jan96 			y = z;
//TempCode PD 17Jan96 		}
//TempCode PD 17Jan96 		else{							/* not packable */
//TempCode PD 17Jan96 			flag = TRUE;
//TempCode PD 17Jan96 			for (z = y; (flag); z += 1) {
//TempCode PD 17Jan96 				if (z>=limit)
//TempCode PD 17Jan96 					flag = FALSE;
//TempCode PD 17Jan96 				if (z-y>=127)
//TempCode PD 17Jan96 					flag = FALSE;
//TempCode PD 17Jan96 				if ((ip[z]==ip[z+1])&&(ip[z]==ip[z+2]))
//TempCode PD 17Jan96 					flag = FALSE;
//TempCode PD 17Jan96 			}
//TempCode PD 17Jan96 			z = (z-y)-2;
//TempCode PD 17Jan96 			*op++ = (UByte )z;					/* write(OFILE,i); */
//TempCode PD 17Jan96 			for (i=0; i <= z; i++)
//TempCode PD 17Jan96 				*op++ = ip[y++];
//TempCode PD 17Jan96 			filelen += z+2;
//TempCode PD 17Jan96 		}
//TempCode PD 17Jan96 	}
//TempCode PD 17Jan96 	return(filelen);
//TempCode PD 17Jan96 }
