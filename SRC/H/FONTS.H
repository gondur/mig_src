//------------------------------------------------------------------------------
//Filename       fonts.h
//System         
//Author         Paul.   
//Date           Tue 8 Aug 1995
//Description    Font data structures
//------------------------------------------------------------------------------
#ifndef	fonts_Included
#define	fonts_Included

//------------------------------------------------------------------------------
//Font types
//------------------------------------------------------------------------------

enum	FONTTYPES	{FNT_MONOBMP = 0, FNT_MONORUN, FNT_SHADE, FNT_COLOUR, FNT_COLOUR_NOPACK};

//------------------------------------------------------------------------------
//Font data structure defs. Currently 8 bytes for a CharTableEntry.
//
//The current encoding assumes 128*128 in the definition of YShift and NextXShift.
//To encode characters up to 256*256:
//		Make YShift be 
//			always negative - complicating the encoding of underscore,
//			offset from height - max descender is usually less than max body,
//			or unsigned based from descenter value for space - largest in font.
//		Make NextXShift a delta from Width
//To encode characters up to 65535x65535: costs 16 bytes per entry
//		Height, Width = 2 words
//		YShift = signed word 
//		NextXShift signed byte delta from width
//		PreXShift - new = signed byte delta - allowing better auto kerning
//		Kern table -new = long pointer to table
//		pixeldata		= long pointer
//
//	Actally, to do kerning 'on the cheep' you need to generate 12 pieces of info
//  for every character. You need start and stop info for typical scanlines 
//	at top, midtop, middle, midbottom, bottom, and descender.
//	These values are maximised with their neighboring values, and the characters 
//  are placed far enough apart so that the stop of one character doesn't touch
//  the start of the next for each region.
//  this allows j to be placed under a but not under g, and a to be placed under f,
//	but not l, and vice versa.
//
//------------------------------------------------------------------------------

struct	CharSizeEntry
{	//easily calculated size info
	signed	char	YShift;		//No. of lines from start position to start
								//unpacking this character. (normally -ve.)
	signed	char	NextXShift;	//Number of pixels to move accross by before
								//starting the next character.
	unsigned char	Height;	//No. of scan lines in this character
	unsigned char	Width;	//No. of pixels in each scan line.
};

struct	CharTableEntry:public	CharSizeEntry
{	//pointer to pixel data not available in public structure
	void*			pixeldata;
};
typedef	CharTableEntry	*CharTableEntryPtr;

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
struct	FontStructInfo
{
	char		name[4];	//4 bytes
	int			n5:8;		// 1 byte
	FONTTYPES	type:8;		//1 byte
	int			maxchar:16;	//2 bytes
};


typedef	struct	Font:public	FontStructInfo
{
	CharTableEntry	charentries[255];
}

*FontPtr;

#endif
