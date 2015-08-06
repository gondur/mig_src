//------------------------------------------------------------------------------
//Filename       libdefs.h
//System         
//Author         Paul.   
//Date           Thu 26 Oct 1995
//Description    
//------------------------------------------------------------------------------
#ifndef	LIBDEFS_Included
#define	LIBDEFS_Included

#define	DEFAULT_LIBDEFS 0

//Change this #define to change the library resolution used

#define	LIB_320_240_256	1

#define	LIB_VERSION	LIB_320_240_256

#if	LIB_VERSION == LIB_320_240_256

	#define	XRESFACTOR	80
	#define	YRESFACTOR	80

#endif

#if LIB_VERSION == LIB_640_480_256

	#define	XRESFACTOR	40
	#define	YRESFACTOR	40

#endif


#endif
