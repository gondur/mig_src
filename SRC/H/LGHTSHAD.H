//------------------------------------------------------------------------------
//Filename       lghtshad.h
//System         
//Author         Robert Slater
//Date           Fri 29 Aug 1997
//Description    Minimum shade values for varying palettes (light-shading only)
//
//------------------------------------------------------------------------------
#ifndef	LGHTSHAD_Included
#define	LGHTSHAD_Included

#define	DEFAULT_LGHTSHAD 0

// Day-time palette fade minimum values...
const UByte	SHADE_DAY_RED = (UByte) 48;							
const UByte	SHADE_DAY_GREEN = (UByte) 48;						
const UByte	SHADE_DAY_BLUE = (UByte) 48;						

// Fog-time palette fade minimum values...
const UByte	SHADE_FOG_RED = (UByte) 96;							
const UByte	SHADE_FOG_GREEN = (UByte) 96;						
const UByte	SHADE_FOG_BLUE = (UByte) 96;						

// Dusk-time palette fade minimum values...
const UByte	SHADE_DUSK_RED = (UByte) 65;						
const UByte	SHADE_DUSK_GREEN = (UByte) 57;						
const UByte	SHADE_DUSK_BLUE = (UByte) 30;

// Dawn-time palette fade minimum values...
const UByte	SHADE_NIGHT_RED = (UByte) 96;						
const UByte	SHADE_NIGHT_GREEN = (UByte) 96;						
const UByte	SHADE_NIGHT_BLUE = (UByte) 110;

// Palette equates for time of day....
const UByte	PAL_DAY = (UByte) 0;
const UByte	PAL_DUSK = (UByte) 1;
const UByte	PAL_NIGHT = (UByte) 2;
const UByte	PAL_DAWN = (UByte) 3;

#endif
