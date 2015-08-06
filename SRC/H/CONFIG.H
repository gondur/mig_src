//------------------------------------------------------------------------------
//Filename       config.h
//System         
//Author         Paul.   
//Date           Mon 26 Apr 1999
//Description    
//------------------------------------------------------------------------------
#ifndef	CONFIG_Included
#define	CONFIG_Included

#define	DEFAULT_CONFIG 0

struct SModeFlags
{
	enum {Max_Modes=32};
	UWord widths[Max_Modes];
	ULong freeTextureRam[Max_Modes];
	SModeFlags() {for (int i=Max_Modes-1;i>=0;i--) widths[i]=0;}
};

struct SDriverSettings
{
	UByte	filtering;
	bool	transparency;
	bool	pal8;
};

struct SModeEnum
{
	enum {Max_Modes=32};
	int	num_modes;
	int widths[Max_Modes];
};

struct SDrivers
{
	enum			{Max_Drivers=2};
	int				num_drivers;
	bool			fFirstHardIsPrimary;
	SModeFlags		soft_modes;
	GUID			hard_guids[Max_Drivers];
	SModeFlags		hard_modes[Max_Drivers];
	SDriverSettings	hard_settings[Max_Drivers];
	SDrivers()		{num_drivers=0;fFirstHardIsPrimary=false;}
};

#endif
