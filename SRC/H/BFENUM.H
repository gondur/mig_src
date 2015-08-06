//------------------------------------------------------------------------------
//Filename       bfenum.h
//System         
//Author         R. Hyde 
//Date           Thu 31 Jul 1997
//Description    
//------------------------------------------------------------------------------
#ifndef	BFENUM_Included
#define	BFENUM_Included

#define	DEFAULT_BFENUM 0

enum	EnumListNames		//this enum indexes the list maintained by PERSONS6!
	{
		ENUM_RealInt=-1,	//extra
		//used in makebf
		ENUM_Angle=0,ENUM_UIDBand,ENUM_Shape,ENUM_Action,ENUM_Side,
		ENUM_Type,ENUM_Duty,ENUM_MoveCode,ENUM_Skill,ENUM_Morale,
		ENUM_Character,ENUM_Int,ENUM_PaintScheme,ENUM_Squadron,ENUM_Formation,
		//usually made by makebf
		ENUM_UniqueID,ENUM_Files,
                //Extra texts indexed with UniqueID
                ENUM_UIDtitle,ENUM_UIDdesc,ENUM_ShapeTitle,
	};


enum	EnableComplexVal		//different names for the same thing...
	{	ENABLE_COMPLEX_VAL=(SLong)0x80000000,
		GOT_COMPLEX_VAL=(SLong)0x80000000,
		GOT_UNDEFINED_VAL=(SLong)0x80000000,
	};


#endif
