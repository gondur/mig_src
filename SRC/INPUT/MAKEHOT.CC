//------------------------------------------------------------------------------
//Filename       makehot.cc
//System         
//Author         Robert Slater
//Date           Thu 21 Mar 1996
//Description    Makes binary files of the raw keyboard code map to a known
//				 hot key enum
//------------------------------------------------------------------------------

#include 	"dosdefs.h"
#include 	<stdio.h>
#include 	<stdarg.h>
#include 	<stdlib.h>
#include 	<dos.h>
#include 	<string.h>
#include 	<conio.h>
#define		SPECIAL_KEYMAPS	FALSE
#include	"keytest.h"

const		NO_ASCII_TABLES = 8;
const		NO_ASCII_KEYS = 54;


struct	RawToHotMapTable
{
	RawToHotMapRecord	rawtohotmapelements[50];
};


RawToHotMapRecord	newmap[50];

RawToHotMapTable
	defaultmap =
	{{	{	{Raw_enter, KEYSH_normext, KEYHIT},		HOTKEY_ENTER},
		{	{Raw_f1, KEYSH_norm, KEYHIT},			HOTKEY_HELP},
		{	{Raw_esc, KEYSH_norm, KEYHIT},			HOTKEY_CANCEL},
		{	{Raw_movehome, KEYSH_normext, KEYHIT},	HOTKEY_CANCEL},
		{	{Raw_f4, KEYSH_Alt, KEYHIT},			HOTKEY_CANCEL},
		{	{Raw_x, KEYSH_Alt, KEYHIT},				HOTKEY_CANCEL},
		{	{Raw_tab, KEYSH_norm, KEYHIT},			HOTKEY_NEXTCOMP},
		{	{Raw_movedown, KEYSH_normext, KEYHIT},	HOTKEY_NEXTCOMP},
		{	{Raw_tab, KEYSH_Shift, KEYHIT},			HOTKEY_PREVCOMP},
		{	{Raw_moveup, KEYSH_normext, KEYHIT},	HOTKEY_PREVCOMP},
		{	{Raw_pageup, KEYSH_normext, KEYHIT},	HOTKEY_NEXTGROUP},
		{	{Raw_tab, KEYSH_Alt, KEYHIT},			HOTKEY_NEXTGROUP},
		{	{Raw_numplus, KEYSH_extsh, KEYHIT},		HOTKEY_NEXTGROUP},
		{	{Raw_pagedown, KEYSH_normext, KEYHIT},	HOTKEY_PREVGROUP},
		{	{Raw_numminus, KEYSH_extsh, KEYHIT},	HOTKEY_PREVGROUP},
		{	{Raw_f10, KEYSH_norm, KEYHIT},			HOTKEY_ACCEPT},
		{	{Raw_moveend, KEYSH_norm, KEYHIT},		HOTKEY_ACCEPT},
		{	{Raw_Extra0ML,KEYSH_normext, KEYHIT},		HOTKEY_LEFTMOUSE},
		{	{Raw_Extra1MM,KEYSH_normext, KEYHIT},		HOTKEY_CENTREMOUSE},
		{	{Raw_Extra2MR,KEYSH_normext, KEYHIT},		HOTKEY_RIGHTMOUSE},
		{	{Raw_space, KEYSH_norm, KEYHIT},		HOTKEY_SPACEBAR},
		{	{Raw_moveleft, KEYSH_normext, KEYHIT},	HOTKEY_LEFTONEDIT},
		{	{Raw_moverigh, KEYSH_normext, KEYHIT},	HOTKEY_RIGHTONEDIT},
		{	{Raw_backspc,KEYSH_norm, KEYHIT},		HOTKEY_BACKSPACEONEDIT},
		{	{Raw_delete,KEYSH_normext, KEYHIT},		HOTKEY_DELETEONEDIT},
		{	{Raw_print,KEYSH_normext, KEYHIT},		HOTKEY_CENTREMOUSE},
		{	{Raw_Extra0ML,KEYSH_normext, KEYHELD},		HOTKEY_LEFTMOUSEHELD},
		{	{Raw_Extra0ML,KEYSH_normext, KEYREL},		HOTKEY_LEFTMOUSERLS},
		{	{Raw_DISABLED, KEYSH_norm, KEYENDOFLIST},	HOTKEY_UNRECOGNISED}
	}};

RawToHotMapTable
	pntshpmap =
	{{	{	{Raw_enter, KEYSH_normext, KEYREL},		HOTKEY_LEFTMOUSERLS},//JIM 15Aug96
//DeadCode JIM 15Aug96 		{	{Raw_Extra0ML,KEYSH_normext, KEYREL},		HOTKEY_U1},//JIM 15Aug96
		{	{Raw_space, KEYSH_norm, KEYREL},		HOTKEY_LEFTMOUSERLS},//JIM 15Aug96
		{	{Raw_moveleft, KEYSH_normext, KEYHIT},	HOTKEY_U2},
		{	{Raw_moverigh, KEYSH_normext, KEYHIT},	HOTKEY_U3},
		{	{Raw_numplus, KEYSH_normext, KEYHIT},		HOTKEY_U4},
		{	{Raw_numminus, KEYSH_normext, KEYHIT},	HOTKEY_U5},
		{	{Raw_moveleft, KEYSH_normext, KEYREL},	HOTKEY_U6},
		{	{Raw_moverigh, KEYSH_normext, KEYREL},	HOTKEY_U7},
		{	{Raw_numplus, KEYSH_normext, KEYREL},		HOTKEY_U8},
		{	{Raw_numminus, KEYSH_normext, KEYREL},	HOTKEY_U9},
		{	{Raw_DISABLED, KEYSH_norm, KEYENDOFLIST},	HOTKEY_UNRECOGNISED}
	}};

RawToHotMapTable
	nostopmap =
	{{	{	{Raw_stop, KEYSH_normext, KEYHIT},		HOTKEY_U8},
		{	{Raw_DISABLED, KEYSH_norm, KEYENDOFLIST},	HOTKEY_UNRECOGNISED}
	}};

UWord	asciitable[NO_ASCII_TABLES][NO_ASCII_KEYS] =
	{	{	0, 0,
			'1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', 0,
			0, 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', 0,
			0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', 39, 96,
			0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', 44, '.', '/'
		},
		{0},
		{	0, 0,
			'!', 64, 35, '$', '%', '^', '&', '*', '(', ')', '_', '+', 0,
			0, 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', 0,
			0, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', 34, 126,
			0, '|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?'
		},
		{	0, 0,	 
			'!', 64, 35, '$', '%', '^', '&', '*', '(', ')', '_', '+',0,
			0, 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', 0,
			0, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', 34, 126,
			0, '|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?'
		},
		{0},{0},{0},{0}
	};

UWord	ASCIItable[NO_ASCII_TABLES][NO_ASCII_KEYS] =
	{	{	0, 0,
			'1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', 0,
			0, 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '[', ']', 0,
			0, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ';', 39, 96,
			0, '\\', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', 44, '.', '/'
		},
		{0},
		{	0, 0,
			'!', 64, 35, '$', '%', '^', '&', '*', '(', ')', '_', '+', 0,
			0, 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', 0,
			0, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', 34, 126,
			0, '|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?'
		},
		{	0, 0,	 
			'!', 64, 35, '$', '%', '^', '&', '*', '(', ')', '_', '+',0,
			0, 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', 0,
			0, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', 34, 126,
			0, '|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?'
		},
		{0},{0},{0},{0}
	};

UWord	hextable[NO_ASCII_TABLES][NO_ASCII_KEYS] =
	{	{	0, 0,
			'1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 000, 000, 0,
			0, 000, 000, 'E', 000, 000, 000, 000, 000, 000, 000, 000, 000, 0,
			0, 'A', 000, 'D', 'F', 000, 000, 000, 000, 000, 000, 39, 96,
			0, 0000, 000, 000, 'C', 000, 'B', 000, 000, 00, 000, 000
		},
		{0},
		{	0, 0,
			'1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 000, 000, 0,
			0, 000, 000, 'E', 000, 000, 000, 000, 000, 000, 000, 000, 000, 0,
			0, 'A', 000, 'D', 'F', 000, 000, 000, 000, 000, 000, 39, 96,
			0, 0000, 000, 000, 'C', 000, 'B', 000, 000, 00, 000, 000
		},
		{	0, 0,	 
			'1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 000, 000, 0,
			0, 000, 000, 'E', 000, 000, 000, 000, 000, 000, 000, 000, 000, 0,
			0, 'A', 000, 'D', 'F', 000, 000, 000, 000, 000, 000, 39, 96,
			0, 0000, 000, 000, 'C', 000, 'B', 000, 000, 00, 000, 000
		},
		{0},{0},{0},{0}
	};

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FindMapSize
//Author		Robert Slater
//Date			Thu 21 Mar 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
ULong	FindMapSize(RawToHotMapRecord	*element)
{
	int			count = 0;
	UByte		*endaddress;
	UByte		*startaddress;
	ULong		size;
	KeyBounce	thebounce;

	startaddress = (UByte*) element;

	do
	{
		thebounce = element[count].keyinfo.keyhit;

		count++;
	}
	while (thebounce != KEYENDOFLIST);


	endaddress = (UByte*) &element[count-1].thishotkey;

	size = (ULong) (endaddress - startaddress);
		
	size += sizeof(element[count-1].thishotkey);

	return(size);


}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SaveMap
//Author		Robert Slater
//Date			Thu 21 Mar 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	SaveMap(char	*directory, char	*thefile, RawToHotMapRecord	*elements)
{
	char	safetext[80];
	char	filename[80];
	FILE	*fptr;
	ULong	size;
	void	*start;
	char	*ptr;
	char	last;


	strcpy(safetext,thefile);

	if (directory)
		strcpy(filename,directory);
	else
		filename[0] = NULL;

	ptr = filename;

	while (*ptr)
		ptr++;

	if (ptr != filename)
	{
		ptr--;

		last = *ptr;

		if (last != '\\')
		{
			// Add a '\\'

			ptr++;

			*ptr++ = '\\';
			*ptr = NULL;
		}
	}

	strcat(filename,safetext);

	start = (void*)	elements;

	size = FindMapSize(elements);

 	if (strlen(filename) <= 1)
 		return;
 
 	if ((fptr = fopen(filename,"wb")) == NULL)
 	{
 		printf("Cannot open file!\n");
 		return;
 	}
 
 	fwrite(start,1,size,fptr);
 
 	fclose(fptr);

	printf("Successfully written file '%s' to hard disk.\n",filename);

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SaveAscii
//Author		Robert Slater
//Date			Thu 21 Mar 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	SaveAscii(char	*directory, char	*thefile, UWord	*elements)
{
	char	filename[80];
	char	safetext[80];
	FILE	*fptr;
	ULong	size;
	void	*start;
	char	*ptr;
	char	last;


	strcpy(safetext,thefile);

	if (directory)
		strcpy(filename,directory);
	else
		filename[0] = NULL;

	ptr = filename;

	while (*ptr)
		ptr++;

	if (ptr != filename)
	{
		ptr--;

		last = *ptr;

		if (last != '\\')
		{
			// Add a '\\'

			ptr++;

			*ptr++ = '\\';
			*ptr = NULL;
		}
	}

	strcat(filename,safetext);


	start = (void*)	elements;

	size = NO_ASCII_TABLES * NO_ASCII_KEYS * 2;

 	if (strlen(filename) <= 1)
 		return;
 
 	if ((fptr = fopen(filename,"wb")) == NULL)
 	{
 		printf("Cannot open file!\n");
 		return;
 	}
 
 	fwrite(start,1,size,fptr);
 
 	fclose(fptr);

	printf("Successfully written file '%s' to hard disk.\n",filename);

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		main
//Author		Robert Slater
//Date			Thu 21 Mar 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
int		main(int	argc, char **argv)
{
	char	*directory;


	if (argc < 2)
	{
		printf("Will use current directory\n");

		directory = NULL;
	}
	else
		directory = argv[1];

	SaveMap(directory,"rthmap1.bin",defaultmap.rawtohotmapelements);
	SaveMap(directory,"rthmap2.bin",pntshpmap.rawtohotmapelements);
	SaveMap(directory,"rthmap3.bin",nostopmap.rawtohotmapelements);
	
	SaveAscii(directory,"asckeyb.bin",&asciitable[0][0]);
	SaveAscii(directory,"capkeyb.bin",&ASCIItable[0][0]);
	SaveAscii(directory,"hexkeyb.bin",&hextable[0][0]);

	return(0);
}

