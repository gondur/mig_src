//------------------------------------------------------------------------------
//Filename       areatype.h
//System         
//Author         Paul
//Date           Thu 13 Aug 1998
//Description    
//------------------------------------------------------------------------------
#ifndef	AREATYPE_Included
#define	AREATYPE_Included

#define	DEFAULT_AREATYPE 0

//Landscape area type enums

enum AreaType
{
	AT_woods=0,		AT_softRock,	AT_vSoftRock,	AT_hardRock,
	AT_sandyRock,	AT_sand,		AT_smallHill,
	AT_denseBush,	AT_sandII,		AT_roughSoil,	AT_village,
	AT_paddyFields,	AT_softEarth,	AT_washShore,
	AT_sea,			AT_forestHill,	AT_roughEarth,	AT_river,
	AT_highRock,	AT_lowRock,		AT_snowyRock,
	AT_mossyRock,	AT_snow,		AT_rockySnow,	AT_soil,
	AT_city,		AT_spare1,		AT_spare2,
	AT_spare3,		AT_spare4,		AT_spare5,		AT_spare6,
	AT_MASK=0x1F,

	RT_river=131,
	RT_bigStream=133,
	RT_smallStream=134,
	RT_track=157,
	RT_rail=158,
	RT_road=159,
	RT_magic=1,

	TREE_HEIGHT=1500
};

inline bool IsWater(UByte at) {at&=AT_MASK; if (at==AT_washShore||at==AT_sea||at==AT_river) return true; return false;}
inline bool IsForest(UByte at) {at&=AT_MASK; if (at==AT_woods||at==AT_forestHill) return true; return false;}
inline bool IsWooded(UByte at) {at&=AT_MASK; if (at==AT_smallHill||at==AT_denseBush) return true; return false;}
inline bool IsValidRoute(UByte at) {if (at==RT_river||at==RT_track||at==RT_rail||at==RT_road) return true; return false;}

#endif
