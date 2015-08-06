//------------------------------------------------------------------------------
//Filename       tga.h
//System         
//Author         Paul.   
//Date           Mon 21 Apr 1997
//Description    
//------------------------------------------------------------------------------
#ifndef	TGA_Included
#define	TGA_Included

#define	DEFAULT_TGA 0

#define	RLCOPY 1
#define	RLRUN  0

typedef struct TGAHeader
{
	UByte	JD00;
	UByte	JD01;
	UByte	Compression;
	UByte	JD03;

	UByte	JD04;
	UByte	JD05;
	UByte	JD06;
	UByte	JD07;

	UByte	JD08;
	UByte	JD09;
	UByte	JD10;
	UByte	JD11;

	UWord	w,h;						/* width and height */
	UByte	nPlanes;					/* No of bit planes */
	UByte	flags;
}
TGAHeader,*TGAHeaderP;

class	TGA
{
	public:

		int	redMask,greenMask,blueMask;							//PD 24Oct97
		int redScale,greenScale,blueScale;						//PD 24Oct97
		int redBits,greenBits,blueBits;							//DAW 24Oct97

		TGA::TGA();

		TGA::~TGA();

		TGA::TGA(Window *screen);

		char*	GetBody(UWord		PhysicalWidth,
						UWord		PhysicalHeight,
						LogicalPtr 	logicalscreenptr);

		void	MakeHead(UWord		PhysicalWidth,
						 UWord		PhysicalHeight);

		ULong	MakeBody(ROWANSURFACEDESC*);	//LogicalPtr logicalscreenptr,
//						 int 		bpsl);

		void	MakePall(UByte*);

		void	Save(UWord,ULong);

	private:

		TGAHeader *hdrPtr;

		UWord	*bodyPtr;

		void	PutTGAWord(FILE*,UWord);

		void	PutTGAHeader(FILE*,TGAHeaderP);

		void	PutTGABody(FILE*,UWord*,ULong);
};



#endif
