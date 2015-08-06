//DeadCode JIM 12Dec95 //------------------------------------------------------------------------------
//DeadCode JIM 12Dec95 //Filename       hardprim.h
//DeadCode JIM 12Dec95 //System         
//DeadCode JIM 12Dec95 //Author         Paul.   
//DeadCode JIM 12Dec95 //Date           Mon 3 Jul 1995
//DeadCode JIM 12Dec95 //Description    
//DeadCode JIM 12Dec95 //------------------------------------------------------------------------------
//DeadCode JIM 12Dec95 #ifndef	hardprim_Included
//DeadCode JIM 12Dec95 #define	hardprim_Included
//DeadCode JIM 12Dec95 #include	"screen.h"
//DeadCode JIM 12Dec95 #define	REALMODE_STACK_SIZE	(5*1024)
//DeadCode JIM 12Dec95 
//DeadCode JIM 12Dec95 struct	DPMIMem
//DeadCode JIM 12Dec95 {
//DeadCode JIM 12Dec95 ULong	size;			//Input to GetDPMImem is size already filled in bytes
//DeadCode JIM 12Dec95 UWord	desc;			//This returns desc as a segment descriptor
//DeadCode JIM 12Dec95 UWord	seg,off;		//Seg is enough to find the data in both modes, 
//DeadCode JIM 12Dec95 void*	flat;			//but an offset may be desirable sometimes
//DeadCode JIM 12Dec95 };						//So, off is also an input, and flat will be set up.
//DeadCode JIM 12Dec95 
//DeadCode JIM 12Dec95 
//DeadCode JIM 12Dec95 class	HardPrim												//PD 29Nov95
//DeadCode JIM 12Dec95 {
//DeadCode JIM 12Dec95 	unsigned char *real_mode_stack;
//DeadCode JIM 12Dec95 	short	stkhndl;
//DeadCode JIM 12Dec95 
//DeadCode JIM 12Dec95 	public:
//DeadCode JIM 12Dec95 		void 	ClearScreen(ScreenRecord *,short);
//DeadCode JIM 12Dec95 		short	SetGraphicsMode(ScreenRecord *,MODE );
//DeadCode JIM 12Dec95 		void	ScreenSwap(ScreenRecord *, short);
//DeadCode JIM 12Dec95 		short	PlotPixel(ScreenRecord *, short, short, short);
//DeadCode JIM 12Dec95 		void	SetTextMode(void );
//DeadCode JIM 12Dec95 		Bool	GetDOSRAM(DPMIMem&,ULong size=0,ULong off=-1);
//DeadCode JIM 12Dec95 		void	FreeDOSRAM(DPMIMem&);
//DeadCode JIM 12Dec95 
//DeadCode JIM 12Dec95 	private:
//DeadCode JIM 12Dec95 		short	SetMode320x200(ScreenRecord *);
//DeadCode JIM 12Dec95 		short	SetMode320x200Debug(ScreenRecord *);			//DAW 30Nov95
//DeadCode JIM 12Dec95 		short	SetMode640x480(ScreenRecord *);
//DeadCode JIM 12Dec95 
//DeadCode JIM 12Dec95 		short	GetDOSRAM(long& ,short);
//DeadCode JIM 12Dec95 		void	FreeDOSRAM(short );
//DeadCode JIM 12Dec95 
//DeadCode JIM 12Dec95 
//DeadCode JIM 12Dec95 	protected:
//DeadCode JIM 12Dec95 
//DeadCode JIM 12Dec95 };
//DeadCode JIM 12Dec95 
//DeadCode JIM 12Dec95 //DeadCode DAW 28Nov95 extern	HardPrim	_HardPrim;
//DeadCode JIM 12Dec95 
//DeadCode JIM 12Dec95 typedef	struct	VESAModeFormat
//DeadCode JIM 12Dec95 {
//DeadCode JIM 12Dec95  	UWord		ModeAttrib;
//DeadCode JIM 12Dec95 	UByte		WinAAttrib;
//DeadCode JIM 12Dec95 	UByte		WinBAttrib;
//DeadCode JIM 12Dec95 	UWord		WinGranularity;
//DeadCode JIM 12Dec95 	UWord		WinSize;			//in K
//DeadCode JIM 12Dec95 	UWord		WinAStartSeg;
//DeadCode JIM 12Dec95 	UWord		WinBStartSeg;
//DeadCode JIM 12Dec95 	ULong		WinPos;
//DeadCode JIM 12Dec95 	UWord		BytesPerScanline;
//DeadCode JIM 12Dec95 	UWord		Width;
//DeadCode JIM 12Dec95 	UWord		Height;
//DeadCode JIM 12Dec95 	UByte		CharWidth;
//DeadCode JIM 12Dec95 	UByte		CharHeight;
//DeadCode JIM 12Dec95 	UByte		NoOfPlanes;
//DeadCode JIM 12Dec95 	UByte		BitsPerPixel;
//DeadCode JIM 12Dec95 	UByte		NoOfBanks;
//DeadCode JIM 12Dec95 	UByte		MemModel;
//DeadCode JIM 12Dec95 	UByte		BankSize;		//in K
//DeadCode JIM 12Dec95 }
//DeadCode JIM 12Dec95 VESAMODEFMT, *VESAMODEFMTPTR;
//DeadCode JIM 12Dec95 
//DeadCode JIM 12Dec95 	extern	class HardPrim	Hard_Prim;							//PD 29Nov95
//DeadCode JIM 12Dec95 
//DeadCode JIM 12Dec95 #endif
#include	"display.h"
