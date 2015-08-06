//------------------------------------------------------------------------------
//Filename       palette.h
//System         
//Author         Paul.   
//Date           Tue 4 Jul 1995
//Description    
//------------------------------------------------------------------------------
#ifndef	palette_Included
#define	palette_Included

typedef	char PAL[256*3*8];										//RJS 19Mar98

typedef	SWord	ColourRange;

//
//Basic pallette:
//A)	16*	 1 indipendent colours
//B)	1*	16 entry red/hilight range
//C)	1*	32 entry grey range
//D-N)	11*	16 entry shading range
//O)	1*	16 entry range which has various 'specials'
//
//	We expect time of day to effect B-N consistantly,
//  but A and O entries may be specials -eg bright at night!
//
enum	Colour
		{
		//First 32 first - actually 16

		BLACK = 0,												//RJS 15Jun98
		SKYBLUE,
		MUSTARD,
		GRNDGREEN,
		RED = 120,												//RJS 12Jun98
		MGREY,
		BROWN,
		LGREY,
		DGREY,
		GREEN,
		BGREEN,
		SEABLUE,
		PINK,
		VDGREY,
		YELLOW,
		WHITE = 252,											//RJS 12Jun98

		//Rest of palette

		//Red range (16)

		RED00,RED01,RED02,RED03,
		RED04,RED05,RED06,RED07,
		RED08,RED09,RED10,RED11,
		RED12,RED13,RED14,RED15,

		//Grey range

		GREY00,GREY01,GREY02,GREY03,
		GREY04,GREY05,GREY06,GREY07,
		GREY08,GREY09,GREY10,GREY11,
		GREY12,GREY13,GREY14,GREY15,

		GREY16,GREY17,GREY18,GREY19,
		GREY20,GREY21,GREY22,GREY23,
		GREY24,GREY25,GREY26,GREY27,
		GREY28,GREY29,GREY30,GREY31,

		//Light brown range

		LBROWN00,LBROWN01,LBROWN02,LBROWN03,
		LBROWN04,LBROWN05,LBROWN06,LBROWN07,
		LBROWN08,LBROWN09,LBROWN10,LBROWN11,
		LBROWN12,LBROWN13,LBROWN14,LBROWN15,

		//Sea blue range

		SEABLUE00,SEABLUE01,SEABLUE02,SEABLUE03,
		SEABLUE04,SEABLUE05,SEABLUE06,SEABLUE07,
		SEABLUE08,SEABLUE09,SEABLUE10,SEABLUE11,
		SEABLUE12,SEABLUE13,SEABLUE14,SEABLUE15,

		//Brown range

		BROWN00,BROWN01,BROWN02,BROWN03,
		BROWN04,BROWN05,BROWN06,BROWN07,
		BROWN08,BROWN09,BROWN10,BROWN11,
		BROWN12,BROWN13,BROWN14,BROWN15,

		//Ground green range

		GNDGREEN00,GNDGREEN01,GNDGREEN02,GNDGREEN03,
		GNDGREEN04,GNDGREEN05,GNDGREEN06,GNDGREEN07,
		GNDGREEN08,GNDGREEN09,GNDGREEN10,GNDGREEN11,
		GNDGREEN12,GNDGREEN13,GNDGREEN14,GNDGREEN15,

		//Green range

		GREEN00,GREEN01,GREEN02,GREEN03,
		GREEN04,GREEN05,GREEN06,GREEN07,
		GREEN08,GREEN09,GREEN10,GREEN11,
		GREEN12,GREEN13,GREEN14,GREEN15,

		//Purple range

		PURPLE00,PURPLE01,PURPLE02,PURPLE03,
		PURPLE04,PURPLE05,PURPLE06,PURPLE07,
		PURPLE08,PURPLE09,PURPLE10,PURPLE11,
		PURPLE12,PURPLE13,PURPLE14,PURPLE15,

		//Grey 2 range

		GREY200,GREY201,GREY202,GREY203,
		GREY204,GREY205,GREY206,GREY207,
		GREY208,GREY209,GREY210,GREY211,
		GREY212,GREY213,GREY214,GREY215,

		//Green 2 range

		GREEN200,GREEN201,GREEN202,GREEN203,
		GREEN204,GREEN205,GREEN206,GREEN207,
		GREEN208,GREEN209,GREEN210,GREEN211,
		GREEN212,GREEN213,GREEN214,GREEN215,

		//Yellow range

		YELLOW00,YELLOW01,YELLOW02,YELLOW03,
		YELLOW04,YELLOW05,YELLOW06,YELLOW07,
		YELLOW08,YELLOW09,YELLOW10,YELLOW11,
		YELLOW12,YELLOW13,YELLOW14,YELLOW15,

		//Sky blue range										//PD 12Jan96
																//PD 12Jan96
		SKYBLUE00,SKYBLUE01,SKYBLUE02,SKYBLUE03,				//PD 12Jan96
		SKYBLUE04,SKYBLUE05,SKYBLUE06,SKYBLUE07,				//PD 12Jan96
		SKYBLUE08,SKYBLUE09,SKYBLUE10,SKYBLUE11,				//PD 12Jan96
		SKYBLUE12,SKYBLUE13,SKYBLUE14,SKYBLUE15,				//PD 12Jan96

		//Blue range

		BLUE00,BLUE01,BLUE02,BLUE03,
		BLUE04,BLUE05,BLUE06,BLUE07,
		BLUE08,BLUE09,BLUE10,BLUE11,
		BLUE12,BLUE13,BLUE14,BLUE15,

		//Explosion range

		EXPLO00,EXPLO01,EXPLO02,EXPLO03,
		EXPLO04,EXPLO05,EXPLO06,EXPLO07,
		EXPLO08,EXPLO09,EXPLO10,EXPLO11,
		EXPLO12,

		//Font mask colour - not of interest in game

		FONTMASK = 253,											//RJS 15Jun98

		//Artwork mask colour

		ARTWORKMASK = 254,										//RJS 15Jun98

		//Off white

		OFFWHITE = 255,											//RJS 15Jun98

		//Colour range equates

		RANGE00 = RED00,
		RANGE01 = GREY00,
		RANGE02 = LBROWN00,
		RANGE03 = SEABLUE00,
		RANGE04 = BROWN00,
		RANGE05 = GNDGREEN00,
		RANGE06 = GREEN00,
		RANGE07 = PURPLE00,
		RANGE08 = GREY200,
		RANGE09 = SKYBLUE00,
		RANGE10 = GREEN200,
		RANGE11 = YELLOW00,
		RANGE12 = BLUE00,

		SPREAD00 = 16,
		SPREAD01 = 32,
		SPREAD02 = 16,
		SPREAD03 = 16,
		SPREAD04 = 16,
		SPREAD05 = 16,
		SPREAD06 = 16,
		SPREAD07 = 16,
		SPREAD08 = 16,
		SPREAD09 = 16,
		SPREAD10 = 16,
		SPREAD11 = 16,
		SPREAD12 = 16,

		HORIZON = 208											//RJS 17Jun97
		};

//Icon hilight/dehilight/disable colour defs - all values are the same except for
//screens using the 3D palette where the icon draw colour range is different

const	Colour		PAL_ICNDRW_COLOUR = (Colour )224;
const	ColourRange	PAL_ICNDRW_RANGE  = (ColourRange )16;

const	Colour		D3D_ICNDRW_COLOUR = (Colour )32;		//Use these two for screens using the//PD 09Apr96
const	ColourRange	D3D_ICNDRW_RANGE  = (ColourRange )16;	//3D palette

const	Colour		PAL_ICNHI_COLOUR  = (Colour )16;		//Icon hilight base colour
const	Colour		D3D_ICNHI_COLOUR  = (Colour )240;		//Icon 3dhilight base colour
const	Colour		PAL_ICNGRY_COLOUR = (Colour )32;		//Icon greyed out base colour//RDH 27Nov96
const	Colour		PAL_ICNACT_COLOUR = (Colour )48;		//Icon greyed out base colour//RDH 27Nov96

//text ranges
const	Colour		TEXT_MIDGRY_COLOUR = (Colour )40;
const	Colour		TEXT_TYPEWRITERRED = (Colour )16;

#endif
