//------------------------------------------------------------------------------
//Filename       mastfile.h
//System         
//Author         Paul.   
//Date           Mon 7 Aug 1995
//Description    
//------------------------------------------------------------------------------
#ifndef	mastfile_Included
#define	mastfile_Included

#ifdef	InDiskIO

	//-------------
	//General files
	//-------------

	"ShpBin\\Shapes.com",
	"Bfields\\testbf.com",

	//--------------------
	//Low resolution files
	//--------------------

	// Artwork

	"Scrn320.200\\rowan.lbm",

	"Scrn320.200\\empire.lbm",

	"Scrn320.200\\title.lbm",

	// Fonts

	"Fonts320.200\\mono.fnt",

	"Fonts320.200\\grey.fnt",

	"Fonts320.200\\colour.fnt",

	//---------------------
	//High resolution files
	//---------------------

	// Artwork

	"Scrn640.480\\rowan.lbm",

	"Scrn640.480\\empire.lbm",

	"Scrn640.480\\title.lbm",

	// Fonts

	"Fonts640.480\\mono.fnt",

	"Fonts640.480\\grey.fnt",

	"Fonts640.480\\colour.fnt"

#else

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

	#define	GENERAL					0

	//-------------
	//General files
	//-------------

	#define	FILShapesNUM			GENERAL + 0	
	#define	FILTestBFNUM			GENERAL + 1

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

	#define	LO_REZ					(FILTestBFNUM + 1)

	//--------------------
	//Low resolution files
	//--------------------

	#define	ARTRowan320x200NUM		LO_REZ + 0
	#define	ARTEmpire320x200NUM		LO_REZ + 1
	#define	ARTTitle320x200NUM		LO_REZ + 2

	#define	FNTMono320x200NUM		LO_REZ + 3
	#define	FNTGrey320x200NUM		LO_REZ + 4
	#define	FNTColour320x200NUM		LO_REZ + 5

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

	#define	HI_REZ					(FNTColour320x200NUM + 1)

	//---------------------
	//High resolution files
	//---------------------

	#define	ARTRowan640x480NUM		HI_REZ + 0
	#define	ARTEmpire640x480NUM		HI_REZ + 1
	#define	ARTTitle640x480NUM		HI_REZ + 2

	#define	FNTMono640x480NUM		HI_REZ + 3
	#define	FNTGrey640x480NUM		HI_REZ + 4
	#define	FNTColour640x480NUM		HI_REZ + 5

#endif

#endif
