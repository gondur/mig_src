//DeadCode JIM 12Dec95 //------------------------------------------------------------------------------
//DeadCode JIM 12Dec95 //Filename       screen.h
//DeadCode JIM 12Dec95 //System         
//DeadCode JIM 12Dec95 //Author         Paul.   
//DeadCode JIM 12Dec95 //Date           Mon 3 Jul 1995
//DeadCode JIM 12Dec95 //Description    
//DeadCode JIM 12Dec95 //------------------------------------------------------------------------------
//DeadCode JIM 12Dec95 #ifndef	screen_Included
//DeadCode JIM 12Dec95 #define	screen_Included
//DeadCode JIM 12Dec95 
//DeadCode JIM 12Dec95 #define	V_MINX	0
//DeadCode JIM 12Dec95 #define V_MAXX	25600
//DeadCode JIM 12Dec95 #define V_MINY	0
//DeadCode JIM 12Dec95 #define V_MAXY	19200
//DeadCode JIM 12Dec95 
//DeadCode JIM 12Dec95 enum	MODE	{MODE_TEXT = 0, MODE_320x200Debug, MODE_320x200, MODE_640x480};
//DeadCode JIM 12Dec95 typedef	struct	Font	*FontPtr;
//DeadCode JIM 12Dec95 	
//DeadCode JIM 12Dec95 struct	ScreenRecord
//DeadCode JIM 12Dec95 {
//DeadCode JIM 12Dec95 	short	NumberOfScreens;
//DeadCode JIM 12Dec95 	short	ScreenNumOnLogical;
//DeadCode JIM 12Dec95 	void	*LogicalScreenPtr;	//this may become a FAR!!!
//DeadCode JIM 12Dec95 	short	PhysicalMinX;
//DeadCode JIM 12Dec95 	short	PhysicalWidth;		//Width of screen in pixels
//DeadCode JIM 12Dec95 	short	PhysicalMinY;
//DeadCode JIM 12Dec95 	short	PhysicalHeight;		//Height of screen in pixels
//DeadCode JIM 12Dec95 	short	BytesPerPixel;
//DeadCode JIM 12Dec95 	short	BytesPerScanLine;
//DeadCode JIM 12Dec95 	long	VirtualMinX;		//these should never be>word
//DeadCode JIM 12Dec95 	long	VirtualWidth;		//note that these virtual mins and sizes
//DeadCode JIM 12Dec95 	long	VirtualMinY;		//must be proportional to 
//DeadCode JIM 12Dec95 	long	VirtualHeight;		//physical mins and sizes so that the
//DeadCode JIM 12Dec95 	short	virtualXscale;		//origin LogicalScreenPtr is in the same place
//DeadCode JIM 12Dec95 	short	virtualYscale;		//Then, scaling only needs /virtual?scale.
//DeadCode JIM 12Dec95 	void	*Palette;			//Let's attempt to spell this correctly
//DeadCode JIM 12Dec95 								//in the new engine!
//DeadCode JIM 12Dec95 	void	*HardPage;			//Hardware page management
//DeadCode JIM 12Dec95 	void	*MouseSave;
//DeadCode JIM 12Dec95 	MODE	PrevMode;			//This should really be the hardware video mode detected
//DeadCode JIM 12Dec95 	MODE	CurrMode;
//DeadCode JIM 12Dec95 	void	*CharColourTable;	//This should be palette or fade map?
//DeadCode JIM 12Dec95 	short	CharX;				
//DeadCode JIM 12Dec95 	short	CharY;
//DeadCode JIM 12Dec95 	FontPtr	fontptr;
//DeadCode JIM 12Dec95 };
//DeadCode JIM 12Dec95 
//DeadCode JIM 12Dec95 
//DeadCode JIM 12Dec95 #endif
//DeadCode JIM 12Dec95 
//DeadCode DAW 15Apr96 #include	"display.h"

ERROR
