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
//Filename       imagemap.cpp
//System         
//Author         Martin Alderton
//Date           Mon 9 Oct 1995
//Description    
//------------------------------------------------------------------------------

#include "DosDefs.h"
#define F_GRAFIX 
#define F_SOUNDS 
#define F_BATTLE
#include "Files.g"
#include "myerror.h"
#include "fileman.h"
#include "myAngles.h"
#include "worldinc.h"
#include	"AnimData.h"									//RJS 10Feb97

#include "3DInstr.h"
#include "shapes.h"
#include "imagemap.h"
#include "3dcode.h"												//RJS 19Nov96
//#include "winmove.h"											//RJS 15Dec96

#include	<stdio.h>
#include	"monotxt.h"

extern Error _Error;
extern SWord winmode_bpp;

ImageMap Image_Map;											//DAW 27Oct98

// For Texture RAM usage debug...
static char*	ImapNames[374]=
{
	{"......."},
	{"F51FIN"},
	{"F51FINB"},
	{"F51FUSEL"},
	{"F51INT"},
	{"F51NOSE"}, 
	{"F51PIT"},  
	{"F51TAIL"}, 
	{"F51WBL"},  
	{"F51WBR"},  
	{"F51WTL"},  
	{"F51WTR"},  
	{"SURFACE1"},
	{"SURFACE2"},
	{"SURFACE3"},
	{"SURFACE5"},
	{"SURFACE6"},
	{"SURFACE8"},
	{"SURFACE9"},
	{"SURFAC10"},
	{"SURFAC11"},
	{"SURFAC12"},
	{"SURFAC14"},
	{"SURFAC15"},
	{"SURFAC16"},
	{"SURFAC18"},
	{"SURFAC20"},
	{"SURFAC21"},
	{"SURFAC22"},
	{"SURFAC23"},
	{"SURFAC24"},
	{"SURFAC25"},
	{"F86BWL"},  
	{"F86BWR"},  
	{"F86CPIT"}, 
	{"F86EXHST"},
	{"F86FUSEL"},
	{"F86IN"},	 
	{"F86LFINB"},
	{"F86LFINT"},
	{"F86NOSE"}, 
	{"F86RFINB"},
	{"F86RFINT"},
	{"F86TAIL"}, 
	{"F86TWL"},  
	{"F86TWR"},  
	{"F84BTL"},  
	{"F84BTR"},  
	{"F84BWL"},  
	{"F84BWR"},  
	{"F84CPIT"}, 
	{"F84EXHST"},
	{"F84FUSEL"},
	{"F84NOSE"}, 
	{"F84TAIL"},
	{"F84TTL"},  
	{"F84TTR"},  
	{"F84TWL"},  
	{"F84TWR"},  
	{"F80BTL"},  
	{"F80BTR"},  
	{"F80BWL"},  
	{"F80BWR"},  
	{"F80CPIT"}, 
	{"F80EXHST"},
	{"F80FUSEL"},
	{"F80INT"},  
	{"F80TAIL"}, 
	{"F80TTL"},  
	{"F80TTR"},  
	{"F80TWL"},  
	{"F80TWR"},  
	{"M15BTL"},  
	{"M15BTR"},  
	{"M15BWL"},  
	{"M15BWR"},  
	{"M15EXHST"},
	{"M15FUSEL"},
	{"M15NOSE"}, 
	{"M15TAIL"}, 
	{"M15TTL"},  
	{"M15TTR"},  
	{"M15TWL"},  
	{"M15TWR"},  
	{"M15CPIT"}, 
	{"M15FUEL"}, 
	{"F86FUEL"}, 
	{"F80FUEL"}, 
	{"ROCKET"},  
	{"F84FUEL"}, 
	{"YAKBLWNG"},
	{"YAKBRWNG"},
	{"YAKBTAIL"},
	{"YAKFUSEL"},
	{"YAKTAIL"}, 
	{"YAKTLWNG"},
	{"YAKTRWNG"},
	{"YAKCPIT"}, 
	{"YAKFIN"},  
	{"B29FRENG"},
	{"B29VTAIL"},
	{"B26BLTL"}, 
	{"B26BLWI"}, 
	{"B26BRTL"}, 
	{"B26BRWI"}, 
	{"B26ENG"},  
	{"B26FREN"}, 
	{"B26FUSE"}, 
	{"B26LTL"},  
	{"B26LWIN"}, 
	{"B26RTL"},  
	{"B26RWIN"}, 
	{"B26SNSE"}, 
	{"B26VTAL"}, 
	{"F51FUEL"}, 
	{"F82FUSEL"},
	{"F82TLWNG"},
	{"F82TRWNG"},
	{"F82BLWNG"},
	{"F82BRWNG"},
	{"F82TOPC"}, 
	{"F82BOTC"}, 
	{"F82TAILT"},
	{"F82TAILB"},
	{"F82NOSE"}, 
	{"F82CPIT"}, 
	{"C54FUSEL"},
	{"C54LWIN"}, 
	{"C54RWIN"}, 
	{"C54NOSE"}, 
	{"C54TAILS"},
	{"C54VBITS"},
	{"CMIGFUSE"},
	{"CMIGTWL"}, 
	{"CMIGBWL"}, 
	{"CMIGTAIL"},
	{"CMIGNOSE"},
	{"CMIGFIN"}, 
	{"CMIGTWR"}, 
	{"CMIGBWR"}, 
	{"HUTTOP"},  
	{"B29TAILS"},
	{"B29PARTS"},
	{"B29NSES"}, 
	{"B29RWING"},
	{"B29LWING"},
	{"B26LWING"},
	{"B26RWING"},
	{"TBITS"},	 
	{"CORSBITS"},
	{"GL_MET"},  
	{"GL_MET1"}, 
	{"CIVIBITS"},
	{"T6TAIL"},  
	{"C47FUSEL"},
	{"C47TAILS"},
	{"HALFTRK"}, 
	{"FOODS"},	 
	{"NUMS"},	 
	{"TENGINE"}, 
	{"ERTRUCK"}, 
	{"CPTF86D1"},
	{"CPTF86D2"},
	{"CPTF86D3"},
	{"CPTF86D4"},
	{"CPTF86D5"},
	{"CPTF86D6"},
	{"CPTF86D7"},
	{"CPTF86D8"},
	{"CPTF86D9"},
	{"CPTF8610"},
	{"CPTF8611"},
	{"CPTF8612"},
	{"CPTF8613"},
	{"CPTF8615"},
	{"CPTF8616"},
	{"CPTF8617"},
	{"CPTF8618"},
	{"CPTF8619"},
	{"CPTF8620"},
	{"CPTF8621"},
	{"CPTF86AM"},
	{"CPTF86EW"},
	{"HQ"},	 
	{"CONAIR"},  
	{"MUSHYPEA"},
	{"NUMD"},	 
	{"SPLASH"},  
	{"TROOPS"},  
	{"CPTM15D1"},
	{"CPTM15D2"},
	{"CPTM15D3"},
	{"CPTM15D4"},
	{"CPTM15D7"},
	{"CPTM15D8"},
	{"CPTM15D9"},
	{"CPTM1510"},
	{"CPTM1511"},
	{"CPTM1512"},
	{"CPTM1513"},
	{"CPTM1514"},
	{"CPTM1515"},
	{"CPTM1516"},
	{"CPTM1517"},
	{"CPTM15WW"},
	{"CPTM15EW"},
	{"CPTF86FR"},
	{"CPTF86WF"},
	{"CPTF86WB"},
	{"CPTF86WD"},
	{"CPITF861"},
	{"CPITF862"},
	{"CPITF863"},
	{"CPITF864"},
	{"CPTM15TW"},
	{"CPTM15TE"},
	{"CPTM15BW"},
	{"CPTM15BE"},
	{"CPTM15DT"},
	{"CPITF511"},
	{"CPITF512"},
	{"CPITF513"},
	{"CPITF514"},
	{"CPTF51D1"},
	{"CPTF51D2"},
	{"CPTF51D3"},
	{"CPTF51D4"},
	{"CPTF51D5"},
	{"CPTF51D8"},
	{"CPTF51D9"},
	{"CPTF5111"},
	{"CPTF5113"},
	{"CPTF5114"},
	{"CPTF5115"},
	{"CPTF5116"},
	{"CPTF51LH"},
	{"CPTF51BT"},
	{"CPTF51W"}, 
	{"CITY1"},	 
	{"RPLYICNS"},
	{"CPTF86BK"},
	{"BRIBASE"}, 
	{"RANGE"},	 
	{"243"},
	{"244"},
	{"245"},
	{"246"},
	{"247"},
	{"248"},
	{"249"},
	{"250"},
	{"251"},
	{"252"},
	{"253"},
	{"254"},
	{"255"},
	{"256"},
	{"F51BLANK"},
	{"F51DECAL"},
	{"F51WHEEL"},
	{"BALFIRE"}, 
	{"BHOLE"},	 
	{"BIGEX"},	 
	{"CRATER"},  
	{"EXPLOMAP"},
	{"FBALL"},	 
	{"FIRE"},	 
	{"GFIRE2"},  
	{"HOLE"},	 
	{"PFIRE"},	 
	{"PILOT1"},  
	{"PILOT2"},  
	{"SMKMAP"},  
	{"SMKMAP2"}, 
	{"SMKMAP3"}, 
	{"SUNMAP"},  
	{"SURFACE4"},
	{"SURFACE7"},
	{"SURFAC13"},
	{"SURFAC17"},
	{"SURFAC19"},
	{"VAPOUR"},  
	{"WRECK"},	 
	{"BLANK"},	 
	{"F86WHEEL"},
	{"F86DECAL"},
	{"F84BRAKE"},
	{"F84STRUT"},
	{"F84WHEEL"},
	{"F80WHEEL"},
	{"M15GLASS"},
	{"M15WHEEL"},
	{"BOMB"},	 
	{"CLOUDX"},  
	{"CLOUDY"},  
	{"CLOUDZ"},  
	{"NK"},	 
	{"YAKWHEEL"},
	{"DUSTMAP"}, 
	{"SMKTRAIL"},
	{"FIRTRAIL"},
	{"MUSHYPEE"},
	{"PIT01"},	 
	{"F86CAN"},  
	{"PFAST"},	 
	{"F51CAN"},  
	{"F80CAN"},  
	{"F84CAN"},  
	{"M15CAN"},  
	{"YAKCAN"},  
	{"B26GEND"}, 
	{"B26GENP"}, 
	{"B26GLNP"}, 
	{"B26GLNS"}, 
	{"B26TURI"}, 
	{"PRFAST"},  
	{"F82CAN"},  
	{"USA"},	 
	{"F82INSIG"},
	{"B29NUM"},  
	{"B29WIN"},  
	{"B26NUM"},  
	{"B26NAM"},  
	{"B26USA"},  
	{"C54NUM"},  
	{"CHINA"},	 
	{"CMIGCAN"}, 
	{"GROUNDD"}, 
	{"GROUNDD2"},
	{"CORSFUSE"},
	{"CORSNAM"}, 
	{"VAPBLOB"}, 
	{"HO3S"},	 
	{"BMONKS"},  
	{"LENSFX"},  
	{"FLMEOUT1"},
	{"FAKE"},	 
	{"CPTF8614"},
	{"CPTF86HD"},
	{"CPTF86WL"},
	{"WHITEX"},  
	{"CPTF86M8"},
	{"LENSFX2"}, 
	{"DROPS"},	 
	{"EXPOL1"},  
	{"EXPOL2"},  
	{"NEXPLO"},  
	{"DIRT"},	 
	{"DIRTY"},	 
	{"FIRE2"},	 
	{"CPTM15D5"},
	{"CPTM15D6"},
	{"CPTM15HD"},
	{"CPTM15WL"},
	{"CPTM15AM"},
	{"DIRT2"},	 
	{"DIRT3"},	 
	{"MM15D11"}, 
	{"M15ART"},  
	{"CPTF86BT"},
	{"SLIP"},	 
	{"FLAT"},	 
	{"CPTF51HD"},
	{"CPTF5112"},
	{"REAR"},	 
	{"DIRT4"},	 
	{"CPTF51D7"},
	{"FLASHER"}, 
	{"SQUEAK"},  
	{"FONT"},	 
	{"EXHAUST"}, 
	{"BRIDGE"},  
	{"EXHAUST2"},
	{"HHAZE"}
};

// Dave .. changes man...
//
// This module has been cleaned up and re-written by Rob .... 27 Oct 1998


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitImageMaps
//Author		Robert Slater
//Date			Tue 20 Oct 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ImageMap::InitImageMaps()
{
	fileblock	*theblock = new fileblock (FIL_IMAP_DIRTABLE);
	if (theblock)
	{
		UWordP		dptr = (UWordP) getdata(theblock);
		SWord		nodirs = (*dptr++) + 1;//last dir inclusive
		SWord		i,noimaps;
		SLong		count;

		supercnt = nodirs;
		for (i = 0; i < nodirs; i++)
		{
			superimagemaptable[i].offset_8bit = *dptr++;
			superimagemaptable[i].offset_16bit = *dptr++;
			superimagemaptable[i].nomaps = *dptr++;

			noimaps = superimagemaptable[i].nomaps;
			if (noimaps)
			{
				superimagemaptable[i].imagemaptable = new ImageMapDescPtr[noimaps];
				for (list_index = 0; list_index < noimaps; list_index++)
					superimagemaptable[i].imagemaptable[list_index] = NULL;
			}
			else
				superimagemaptable[i].imagemaptable = NULL;
		}

// cludge for fake FONT directory...
		supercnt=5;
		superimagemaptable[4].offset_8bit = 0;
		superimagemaptable[4].offset_16bit = 0;
		superimagemaptable[4].nomaps = 255;

		noimaps = superimagemaptable[4].nomaps;
		
		superimagemaptable[4].imagemaptable = new ImageMapDescPtr[noimaps];
		for (list_index = 0; list_index < noimaps; list_index++)
			superimagemaptable[4].imagemaptable[list_index] = NULL;

		delete theblock;
	}
}

static FILE*	dfp;
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		imagemap
//Author		Martin Alderton
//Date			Wed 11 Oct 1995
//
//Description class constructor.	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		imagemap
//LastModified:	PD 25Aug96
//Author		Martin Alderton
//Date			Tue 10 Oct 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//-------------------------------------------------------------------------------
ImageMap::ImageMap()
{
	total_image_mem = 0;										//PD 06Jun96
	total_ac_mem = 0;											//RJS 24Jun98
	total_cockpit_mem = 0;										//RJS 24Jun98
	DoingAC = FALSE;
	DoingCock = FALSE;
	dfp = NULL;
//	dfp = fopen("imdeb.txt","wt");

	SLong	i,count;
	ImageMapBitField*	imagemapfield;

	supercnt = 0;
	for (i=0; i<16; i++)
	{
		superimagemaptable[i].offset_8bit = 0;
		superimagemaptable[i].offset_16bit = 0;
		superimagemaptable[i].nomaps = 0;
		superimagemaptable[i].imagemaptable = NULL;

		imagemapfield = &superimagemaptable[i].imbf;
		for (count=ImageMapBitMIN;count<ImageMapBitMAX;count++)
			*imagemapfield%=(ImageMapBit)count;
	}

	list_index = 0;

	total_image_mem = 0;								
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		~imagemap
//Author		Martin Alderton
//Date			Tue 10 Oct 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//---------------------------------------------------------------------------
ImageMap::~ImageMap()
{
	if (dfp)
	{
		fprintf(dfp,"\n\nTotal Imagemap mem used: %d\n",total_image_mem);
		fprintf(dfp,"Total AC mem used: %d\n",total_ac_mem);
		fprintf(dfp,"Total Cockpit mem used: %d\n",total_cockpit_mem);
		fclose(dfp);
	}

  	UWord			index,j,max;							
	ImageMapDescPtr imgp;						

	for (j=0; j < supercnt; j++)
	{
		max = superimagemaptable[j].nomaps;
		for(index=0;index<max;index++)
		{
			imgp = superimagemaptable[j].imagemaptable[index];		//RJS 19Oct98
  			if (imgp)												//RJS 19Oct98
   			{														//RJS 19Oct98
 				SWord imgwidth,imgheight;							//RJS 19Oct98
 																	//RJS 19Oct98
 				imgwidth = imgp->w;									//RJS 19Oct98
 				imgheight = imgp->h;								//RJS 19Oct98
																	//RJS 19Oct98
				total_image_mem -= imgwidth * imgheight;			//RJS 19Oct98

    			delete imgp;

				superimagemaptable[j].imagemaptable[index]=NULL;
   			}
		}

	   	delete [] superimagemaptable[j].imagemaptable;				//RJS 19Oct98
	}

	supercnt = 0;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetImageMapPtr
//Author		Martin Alderton
//Date Tue 10 Oct 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
ImageMapDescPtr ImageMap::GetImageMapPtr(ImageMapNumber imagemap_number,Bool	skipmap)
{
	UWord	real_imagemap_number = imagemap_number & 0x7FFF;
	UWord	file_no = real_imagemap_number & 0xFF;
	UWord	dir_no = real_imagemap_number >> 8;

	if(superimagemaptable[dir_no].imagemaptable[file_no]==NULL)	//CSB 10/11/98	FAILS HERE !!!!
	{
		Bool				is16 = FALSE;			
		ImageMapBitField*	imagemapfield = &superimagemaptable[dir_no].imbf;//RJS 19Oct98
		UWord				mapoff = superimagemaptable[dir_no].nomaps;

		if ((real_imagemap_number != imagemap_number) && (winmode_bpp > 8))
		{
			is16 = TRUE;
			*imagemapfield|=(ImageMapBit) (file_no + mapoff);				//RJS 19Oct98
		}
		else
			*imagemapfield|=(ImageMapBit)file_no;								//RJS 19Oct98

		if ((real_imagemap_number & 0xFF00) != (FONTBASENO & 0xFF00))		//RJS 4Dec00
			LoadImageMap(&superimagemaptable[dir_no],file_no,is16,skipmap);		//RJS 19Oct98
		else
			LoadFontMap(&superimagemaptable[dir_no],file_no);			//RJS 4Dec00
	}
	
	return(superimagemaptable[dir_no].imagemaptable[file_no]);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddImageMapsToGlobList
//Author		Paul.   
//Date			Sun 25 Aug 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ImageMap::AddImageMapToGlbList(UWord imageno)
{
	UWord	realmapno = imageno & 0x7FFF;
	UWord	dir_no = realmapno >> 8;
	UWord	file_no = realmapno & 0xFF;
	UWord	mapoff = superimagemaptable[dir_no].nomaps;

	ImageMapBitField* imagemapfield = &superimagemaptable[dir_no].imbf;

	if ((realmapno != imageno) && (winmode_bpp > 8))
		*imagemapfield|=(ImageMapBit) (file_no + mapoff);//16bit file
	else
		*imagemapfield|=(ImageMapBit) file_no;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LoadImageMapPtrs
//Author		Paul.   
//Date			Sun 25 Aug 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ImageMap::LoadImageMapPtrs()
{
	int		index_list;
	int		i;
	ImageMapBitField* imagemapfield;
	UWord	maxmaps,mapoff;

	for (i=0; i < supercnt; i++)
	{
		imagemapfield = &superimagemaptable[i].imbf;
		mapoff = superimagemaptable[i].nomaps;
		maxmaps = mapoff << 1;

		for(index_list=ImageMapBitMIN;index_list<maxmaps;index_list++)
		{
			if ((*imagemapfield)[(ImageMapBit)index_list])
			{
				if (index_list < mapoff)
					LoadImageMap(&superimagemaptable[i],index_list,FALSE);
				else
					LoadImageMap(&superimagemaptable[i],(index_list - mapoff),TRUE);
			}
		}
	}
	File_Man.DiscardDirList(DIR_IMAGEMAP);	//no point me cacheing the image maps, is there?
	File_Man.DiscardDirList(DIR_MASKMAP);
	File_Man.DiscardDirList(DIR_IMGMAP16);
	File_Man.DiscardDirList(DIR_MSKMAP16);
	File_Man.DiscardDirList(DIR_COCKPITS);
	File_Man.DiscardDirList(DIR_COCKPT16);
	File_Man.DiscardDirList(DIR_COCKPM16);
	File_Man.DiscardDirList(DIR_COCKMASK);
}
 
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LoadImageMap
//Author		Dave Whiteside
//Date			Tue 27 Oct 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool ImageMap::LoadImageMap(SuperMap*	supermap, UWord file_no,Bool is16bit, Bool	skipmap)
{
	Bool 	ret_val = FALSE;

	if(supermap->imagemaptable[file_no]==NULL)
	{
		ImageMapDescPtr imgp = new ImageMapDesc;				//RJS 19Oct98
		if (imgp)
		{
			FileNum		imagemapfile;							//RJS 19Oct98
//DeadCode RJS 27Oct98 			UWord		fnum = DIR_IMAGEMAP + file_no;			//RJS 19Oct98

			supermap->imagemaptable[file_no] = imgp;				//RJS 19Oct98

			//if (file_no==13) _asm {int 3}

			if (is16bit)
				imagemapfile = (FileNum) (file_no + supermap->offset_16bit);//RJS 27Oct98
			else
				imagemapfile = (FileNum) (file_no + supermap->offset_8bit);//RJS 27Oct98

			fileblock	fblock = imagemapfile;

			imgp->FixLbmImageMap(&fblock);

			//Texture RAM usage summary....
			total_image_mem += imgp->w * imgp->h;				//RJS 19Oct98
//TempCode DAW 27Oct98 			if (DoingAC)
//TempCode DAW 27Oct98 			{
//TempCode DAW 27Oct98 				total_ac_mem += imgwidth*imgheight;
//TempCode DAW 27Oct98 				fprintf(dfp,"AC:   %s ..... %d\n",ImapNames[imagemap_number],imgwidth*imgheight);
//TempCode DAW 27Oct98 			}
//TempCode DAW 27Oct98 			else
//TempCode DAW 27Oct98 			{
//TempCode DAW 27Oct98 				if (DoingCock)
//TempCode DAW 27Oct98 				{
//TempCode DAW 27Oct98 					total_cockpit_mem += imgwidth*imgheight;
//TempCode DAW 27Oct98 					fprintf(dfp,"Cock: %s ..... %d\n",ImapNames[imagemap_number],imgwidth*imgheight);
//TempCode DAW 27Oct98 				}
//TempCode DAW 27Oct98 				else
//TempCode DAW 27Oct98 					fprintf(dfp,"Gen:  %s ..... %d\n",ImapNames[imagemap_number],imgwidth*imgheight);
//TempCode DAW 27Oct98 			}

			if (imgp->w == 0)
				INT3;

			ret_val = TRUE;
		}
		else
			_Error.EmitSysErr("COULD NOT ALLOCATE IMAGEMAP %d",file_no);
	}
	return(ret_val);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FixLbmImageMap
//Author		Robert Slater
//Date			Fri 6 Feb 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ImageMap_Desc::FixLbmImageMap(fileblock* fblockptr)
{
	struct LbmSearch
	{
		IFFHunkSearch bmhd, cmap, alfa, body;
	}
	lbmSearch;

	const SLong searchCount=sizeof(LbmSearch)/sizeof(IFFHunkSearch);

	lbmSearch.bmhd.searchVal=*(ULong*)"BMHD";
	lbmSearch.cmap.searchVal=*(ULong*)"CMAP";
	lbmSearch.alfa.searchVal=*(ULong*)"ALFA";
	lbmSearch.body.searchVal=*(ULong*)"BODY";
	lbmSearch.bmhd.hunkPtr=
		lbmSearch.cmap.hunkPtr=
		lbmSearch.alfa.hunkPtr=
		lbmSearch.body.hunkPtr=NULL;

	UByte* buffer = (UByteP) fblockptr->getdata();
	UByte* start=buffer;
	UByte	*tmp;
	SWord	picwidth,picheight,picy,picx,x,y;
	SLong	blocksize;
	int		colline;

	Graphic::SearchIFFHunks(searchCount,(IFFHunkSearch*)&lbmSearch,buffer);

	w=0;
	h=0;
	isMasked = 0;												//RJS 26Mar98

	tmp = lbmSearch.bmhd.hunkPtr;
	if (tmp)
	{
		tmp = Graphic::ReadWord(tmp,picwidth);
		tmp = Graphic::ReadWord(tmp,picheight);
		tmp += 5;												//RJS 26Mar98
		if (*tmp)												//RJS 26Mar98
			isMasked = 1;										//RJS 26Mar98
	}

	tmp = lbmSearch.cmap.hunkPtr;
	if (tmp)
	{
		UByteP	palptr;

		tmp = Graphic::ReadLong((UByteP)(tmp-4),blocksize);

		if (blocksize < 256)									//RJS 24Feb98
		{
			// A palette index number, not palette.....

			paletteindex = blocksize;
			tmp += blocksize;									// Keep things safe with dummy data
		}
		else
		{
			palette = new UByte[blocksize];
			if (palette)
			{
				palptr = palette;

				for (colline = 0; colline < blocksize; colline++)
				{
					*palptr = *tmp;
					palptr++;
					tmp++;
				}
			}
		}														//RJS 24Feb98
	}

	tmp = lbmSearch.alfa.hunkPtr;
	if (tmp)
	{
		alpha = new UByte[picwidth*picheight];
		if (alpha)
		{
			ULong	BytesPerScanLine = picwidth;
			UByteP	logicalscreenptr = alpha;

			int	y, x;
			for (y=0; y < picheight; y ++)
			{
				UByteP	c = tmp;
				SLong	width = picwidth;
				SLong	x = 0;
				SLong	minx = 0;
				SLong	maxx = picwidth - 1;

//		tmp = Graphic::UnpackRow(tmp,picwidth,x,y++,PhysicalMinX,PhysicalMinX+PhysicalWidth-1);
//
//		UnpackRow(UByte *c, SLong width, SLong x, SLong y, SLong minx, SLong maxx)

				#define	TRANSFERVALUESIZE	UByte
				#define	LOADVALUE(x)	TRANSFERVALUE=x
				#define	COPYVALUE(t,s)	*t++=s
				#define	return(s)

				{
				#include "lbmcpp.h"

				tmp = c;
				#undef	return
			}
		}
	}

	tmp = lbmSearch.body.hunkPtr;
	if (tmp)
	{
		// blah... alocate buffer body (width * height)
		body = new UByte[picwidth*picheight];
		if (body)
		{
			ULong	BytesPerScanLine = picwidth;
			UByteP	logicalscreenptr = body;

			w=picwidth;
			h=picheight;

			int	y, x;
			for (y=0; y < picheight; y ++)
			{
				UByteP	c = tmp;
				SLong	width = picwidth;
				SLong	x = 0;
				SLong	minx = 0;
				SLong	maxx = picwidth - 1;

//		tmp = Graphic::UnpackRow(tmp,picwidth,x,y++,PhysicalMinX,PhysicalMinX+PhysicalWidth-1);
//
//		UnpackRow(UByte *c, SLong width, SLong x, SLong y, SLong minx, SLong maxx)

				#define	TRANSFERVALUESIZE	UByte
				#define	LOADVALUE(x)	TRANSFERVALUE=x
				#define	COPYVALUE(t,s)	*t++=s
				#define	return(s)

				{
				#include "lbmcpp.h"

				tmp = c;
				#undef	return
			}
		}
	}


	}


//Old_Code PD 27Oct98 void	ImageMap_Desc::FixLbmImageMap(fileblock* fblockptr)
//Old_Code PD 27Oct98 {
//Old_Code PD 27Oct98 	UByte* buffer = (UByteP) fblockptr->getdata();
//Old_Code PD 27Oct98 	UByte* start=buffer;
//Old_Code PD 27Oct98 	UByte	*tmp;
//Old_Code PD 27Oct98 	SWord	picwidth,picheight,picy,picx,x,y;
//Old_Code PD 27Oct98 	SLong	blocksize;
//Old_Code PD 27Oct98 	int		colline;
//Old_Code PD 27Oct98 
//Old_Code PD 27Oct98 	w=0;
//Old_Code PD 27Oct98 	h=0;
//Old_Code PD 27Oct98 	isMasked = 0;												//RJS 26Mar98
//Old_Code PD 27Oct98 
//Old_Code PD 27Oct98 	tmp = Graphic::SearchIFFHunk((UByte *)"BMHD",buffer);		//Process PBM header
//Old_Code PD 27Oct98 	if (tmp)
//Old_Code PD 27Oct98 	{
//Old_Code PD 27Oct98 		tmp = Graphic::ReadWord(tmp,picwidth);
//Old_Code PD 27Oct98 		tmp = Graphic::ReadWord(tmp,picheight);
//Old_Code PD 27Oct98 		tmp += 5;												//RJS 26Mar98
//Old_Code PD 27Oct98 		if (*tmp)												//RJS 26Mar98
//Old_Code PD 27Oct98 			isMasked = 1;										//RJS 26Mar98
//Old_Code PD 27Oct98 	}
//Old_Code PD 27Oct98 
//Old_Code PD 27Oct98 	tmp = Graphic::SearchIFFHunk((UByte *)"CMAP",buffer);		//Process CMAP hunk - palette
//Old_Code PD 27Oct98 	if (tmp)
//Old_Code PD 27Oct98 	{
//Old_Code PD 27Oct98 		UByteP	palptr;
//Old_Code PD 27Oct98 
//Old_Code PD 27Oct98 		tmp = Graphic::ReadLong((UByteP)(tmp-4),blocksize);
//Old_Code PD 27Oct98 
//Old_Code PD 27Oct98 		if (blocksize < 256)									//RJS 24Feb98
//Old_Code PD 27Oct98 		{
//Old_Code PD 27Oct98 			// A palette index number, not palette.....
//Old_Code PD 27Oct98 
//Old_Code PD 27Oct98 			paletteindex = blocksize;
//Old_Code PD 27Oct98 			tmp += blocksize;									// Keep things safe with dummy data
//Old_Code PD 27Oct98 		}
//Old_Code PD 27Oct98 		else
//Old_Code PD 27Oct98 		{
//Old_Code PD 27Oct98 			palette = new UByte[blocksize];
//Old_Code PD 27Oct98 			if (palette)
//Old_Code PD 27Oct98 			{
//Old_Code PD 27Oct98 				palptr = palette;
//Old_Code PD 27Oct98 
//Old_Code PD 27Oct98 				for (colline = 0; colline < blocksize; colline++)
//Old_Code PD 27Oct98 				{
//Old_Code PD 27Oct98 					*palptr = *tmp;
//Old_Code PD 27Oct98 					palptr++;
//Old_Code PD 27Oct98 					tmp++;
//Old_Code PD 27Oct98 				}
//Old_Code PD 27Oct98 			}
//Old_Code PD 27Oct98 		}														//RJS 24Feb98
//Old_Code PD 27Oct98 	}
//Old_Code PD 27Oct98 
//Old_Code PD 27Oct98 	tmp = Graphic::SearchIFFHunk((UByte *)"ALFA",buffer);		//Process PBM header
//Old_Code PD 27Oct98 	if (tmp)
//Old_Code PD 27Oct98 	{
//Old_Code PD 27Oct98 		alpha = new UByte[picwidth*picheight];
//Old_Code PD 27Oct98 		if (alpha)
//Old_Code PD 27Oct98 		{
//Old_Code PD 27Oct98 			ULong	BytesPerScanLine = picwidth;
//Old_Code PD 27Oct98 			UByteP	logicalscreenptr = alpha;
//Old_Code PD 27Oct98 
//Old_Code PD 27Oct98 			int	y, x;
//Old_Code PD 27Oct98 			for (y=0; y < picheight; y ++)
//Old_Code PD 27Oct98 			{
//Old_Code PD 27Oct98 				UByteP	c = tmp;
//Old_Code PD 27Oct98 				SLong	width = picwidth;
//Old_Code PD 27Oct98 				SLong	x = 0;
//Old_Code PD 27Oct98 				SLong	minx = 0;
//Old_Code PD 27Oct98 				SLong	maxx = picwidth - 1;
//Old_Code PD 27Oct98 
//Old_Code PD 27Oct98 //		tmp = Graphic::UnpackRow(tmp,picwidth,x,y++,PhysicalMinX,PhysicalMinX+PhysicalWidth-1);
//Old_Code PD 27Oct98 //
//Old_Code PD 27Oct98 //		UnpackRow(UByte *c, SLong width, SLong x, SLong y, SLong minx, SLong maxx)
//Old_Code PD 27Oct98 
//Old_Code PD 27Oct98 				#define	TRANSFERVALUESIZE	UByte
//Old_Code PD 27Oct98 				#define	LOADVALUE(x)	TRANSFERVALUE=x
//Old_Code PD 27Oct98 				#define	COPYVALUE(t,s)	*t++=s
//Old_Code PD 27Oct98 				#define	return(s)
//Old_Code PD 27Oct98 
//Old_Code PD 27Oct98 				{
//Old_Code PD 27Oct98 				#include "lbmcpp.h"
//Old_Code PD 27Oct98 
//Old_Code PD 27Oct98 				tmp = c;
//Old_Code PD 27Oct98 				#undef	return
//Old_Code PD 27Oct98 			}
//Old_Code PD 27Oct98 		}
//Old_Code PD 27Oct98 	}
//Old_Code PD 27Oct98 
//Old_Code PD 27Oct98 	tmp = Graphic::SearchIFFHunk((UByte *)"BODY",buffer);		//Process PBM header
//Old_Code PD 27Oct98 	if (tmp)
//Old_Code PD 27Oct98 	{
//Old_Code PD 27Oct98 		// blah... alocate buffer body (width * height)
//Old_Code PD 27Oct98 		body = new UByte[picwidth*picheight];
//Old_Code PD 27Oct98 		if (body)
//Old_Code PD 27Oct98 		{
//Old_Code PD 27Oct98 			ULong	BytesPerScanLine = picwidth;
//Old_Code PD 27Oct98 			UByteP	logicalscreenptr = body;
//Old_Code PD 27Oct98 
//Old_Code PD 27Oct98 			w=picwidth;
//Old_Code PD 27Oct98 			h=picheight;
//Old_Code PD 27Oct98 
//Old_Code PD 27Oct98 			int	y, x;
//Old_Code PD 27Oct98 			for (y=0; y < picheight; y ++)
//Old_Code PD 27Oct98 			{
//Old_Code PD 27Oct98 				UByteP	c = tmp;
//Old_Code PD 27Oct98 				SLong	width = picwidth;
//Old_Code PD 27Oct98 				SLong	x = 0;
//Old_Code PD 27Oct98 				SLong	minx = 0;
//Old_Code PD 27Oct98 				SLong	maxx = picwidth - 1;
//Old_Code PD 27Oct98 
//Old_Code PD 27Oct98 //		tmp = Graphic::UnpackRow(tmp,picwidth,x,y++,PhysicalMinX,PhysicalMinX+PhysicalWidth-1);
//Old_Code PD 27Oct98 //
//Old_Code PD 27Oct98 //		UnpackRow(UByte *c, SLong width, SLong x, SLong y, SLong minx, SLong maxx)
//Old_Code PD 27Oct98 
//Old_Code PD 27Oct98 				#define	TRANSFERVALUESIZE	UByte
//Old_Code PD 27Oct98 				#define	LOADVALUE(x)	TRANSFERVALUE=x
//Old_Code PD 27Oct98 				#define	COPYVALUE(t,s)	*t++=s
//Old_Code PD 27Oct98 				#define	return(s)
//Old_Code PD 27Oct98 
//Old_Code PD 27Oct98 				{
//Old_Code PD 27Oct98 				#include "lbmcpp.h"
//Old_Code PD 27Oct98 
//Old_Code PD 27Oct98 				tmp = c;
//Old_Code PD 27Oct98 				#undef	return
//Old_Code PD 27Oct98 			}
//Old_Code PD 27Oct98 		}
//Old_Code PD 27Oct98 	}
//Old_Code PD 27Oct98 
//Old_Code PD 27Oct98 
//Old_Code PD 27Oct98 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FixupImageMap
//Author		Robert Slater
//Date			Sun 15 Dec 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void  ImageMap::FixupImageMap(void*	&dataarea,ULong&	datalengthin)
{
//DeadCode DAW 27Oct98 	UByteP	imagestart = (UByteP) dataarea;
//DeadCode DAW 27Oct98 	ULong	dlength = datalengthin;
//DeadCode DAW 27Oct98 	ULong	count = 0;
//DeadCode DAW 27Oct98 	UByte	thiscol;
//DeadCode DAW 27Oct98 	UByte	newcol;												//RDH 16Dec96
//DeadCode DAW 27Oct98 
//DeadCode DAW 27Oct98 //	if (_DPlay.SelectedService)	//test for in windows...								//RJS 15Dec96
//DeadCode DAW 27Oct98 //	{
//DeadCode DAW 27Oct98 //DeadCode RDH 20Dec96 		if (Three_Dee.lightson)
//DeadCode DAW 27Oct98 			newcol = 251;										//RDH 20Dec96
//DeadCode DAW 27Oct98 //DeadCode RDH 20Dec96 		else
//DeadCode DAW 27Oct98 //DeadCode RDH 20Dec96 			newcol = 0;
//DeadCode DAW 27Oct98 
//DeadCode DAW 27Oct98 		while (count < dlength)
//DeadCode DAW 27Oct98 		{
//DeadCode DAW 27Oct98 			thiscol = *imagestart;
//DeadCode DAW 27Oct98 
//DeadCode DAW 27Oct98 			if (thiscol == 255)
//DeadCode DAW 27Oct98 				*imagestart = newcol;
//DeadCode DAW 27Oct98 
//DeadCode DAW 27Oct98 			imagestart++;
//DeadCode DAW 27Oct98 			count++;
//DeadCode DAW 27Oct98 		}
//DeadCode DAW 27Oct98 //	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UnLoadImageMap
//Author		Martin   
//Date			Tue 10 Oct 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ImageMap::UnLoadImageMap(ImageMapNumber imagemap_number)
{
 	UWord	file_no = imagemap_number & 0xFF;
	UWord	dir_no = imagemap_number >> 8;

	if(superimagemaptable[dir_no].imagemaptable[file_no]!=NULL)
	{
		ImageMapDescPtr imgp = superimagemaptable[dir_no].imagemaptable[file_no];				
		
		SWord imgwidth,imgheight;								

		imgwidth = imgp->w;										
		imgheight = imgp->h;									

		total_image_mem -= imgwidth*imgheight;					

		delete imgp;

		superimagemaptable[dir_no].imagemaptable[file_no] = NULL;		
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UnLoadImageMapPtrs
//Author		Martin Alderton
//Date			Mon 9 Oct 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ImageMap::UnLoadImageMapPtrs()
{
	UWord	index_list;
	int		i;
	UWord	file_no;
	ImageMapBitField* imagemapfield;
	UWord	maxmap, mapoff;

	for (i=0; i < supercnt; i++)
	{
		imagemapfield = &superimagemaptable[i].imbf;
		mapoff = superimagemaptable[i].nomaps;
		maxmap = mapoff << 1;

		for(index_list=ImageMapBitMIN;index_list<maxmap;index_list++)
		{
			if ((*imagemapfield)[(ImageMapBit)index_list])
			{
				*imagemapfield%=(ImageMapBit)index_list;

				file_no = index_list;
				if (index_list > mapoff)
					file_no -= mapoff;

				UnLoadImageMapPtr(&superimagemaptable[i],file_no);
			}
		}
	}

	Three_Dee.newpalettes = NULL;					
//DeadCode RJS 14Jun99 
//DeadCode RJS 14Jun99 	failedcnt = 0;
//DeadCode RJS 14Jun99 #ifndef	NDEBUG
//DeadCode RJS 14Jun99 	for (i=0; i < supercnt; i++)
//DeadCode RJS 14Jun99 	{
//DeadCode RJS 14Jun99 		mapoff = superimagemaptable[i].nomaps;
//DeadCode RJS 14Jun99 		for (file_no = 0; file_no < mapoff; file_no++)
//DeadCode RJS 14Jun99 		{
//DeadCode RJS 14Jun99 			if (superimagemaptable[i].imagemaptable[file_no])
//DeadCode RJS 14Jun99 				 failedcnt++;
//DeadCode RJS 14Jun99 		}
//DeadCode RJS 14Jun99 	}
//DeadCode RJS 14Jun99 #endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UnLoadImageMapPtr
//Author		Dave Whiteside
//Date			Tue 27 Oct 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ImageMap::UnLoadImageMapPtr(SuperMap*	supermap, UWord	file_no)
{
	ImageMapDescPtr imgp = supermap->imagemaptable[file_no];
 	if (imgp)													
	{
		SWord imgwidth,imgheight;								

		imgwidth = imgp->w;										
		imgheight = imgp->h;									

		total_image_mem -= imgwidth*imgheight;					

		delete imgp;											
		supermap->imagemaptable[file_no] = NULL;//RJS 19Oct98
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UnLoadImageMaps
//Author		Robert Slater
//Date			Mon 14 Jun 1999
//
//Description	Wipes entire imagemap table and resets bit fields
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ImageMap::UnLoadImageMaps()
{
	UWord	index_list;
	int		i;
	UWord	file_no;
	ImageMapBitField* imagemapfield;
	UWord	maxmap;

	for (i=0; i < supercnt; i++)
	{
		maxmap = superimagemaptable[i].nomaps;
		for(file_no=0;file_no<maxmap;file_no++)
			UnLoadImageMapPtr(&superimagemaptable[i],file_no);

		imagemapfield = &superimagemaptable[i].imbf;
		for (index_list=ImageMapBitMIN;index_list<ImageMapBitMAX;index_list++)
			*imagemapfield%=(ImageMapBit)index_list;
	}

	Three_Dee.newpalettes = NULL;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LoadFontMap
//Author		Robert Slater
//Date			Tue 5 Dec 2000
//
//Description	For auto-generated fonts
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ImageMap::LoadFontMap(SuperMap*	supermap, UWord file_no)
{
	if(supermap->imagemaptable[file_no]==NULL)
	{
		ImageMapDescPtr imgp = ImageMap_Desc::initsafe(128,128,true);
		if (imgp)
		{
			FileNum		imagemapfile;

			supermap->imagemaptable[file_no] = imgp;

// Generate table (with alpha)...
			imgp->InitFont(file_no-1,128,128);

			total_image_mem += imgp->w * imgp->h;
		}
		else
			_Error.EmitSysErr("COULD NOT ALLOCATE IMAGEMAP %d",file_no);
	}
}

