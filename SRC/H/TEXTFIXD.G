MINMAX	(TextList,		TextList0MIN,TextList19MAX);		//Lists to choose from	- text equates go in here!
enum	TextRef		
		{	TextRef_MIN=0,TextRef_MAX=65535,
			TextRef_LastLoadable=TextSeqMAX,	//This is highest legal number from UI
		};	
MINMAX	(TextBuild,		0xC000,0xC0ff);		//Temporary workspace management

MINMAX	(TextPerm,		0xC100,0xC6ff);		//Permanentised workspace - per nested sheet
MINMAX	(TextPerm0,		0xC100,0xC1ff);		
MINMAX	(TextPerm1,		0xC200,0xC2ff);
MINMAX	(TextPerm2,		0xC300,0xC3ff);
MINMAX	(TextPerm3,		0xC400,0xC4ff);
MINMAX	(TextPerm4,		0xC500,0xC5ff);
MINMAX	(TextPerm5,		0xC600,0xC6ff);

const	int	TextIntMIN	=	0xD000;

//DeadCode MGA 05Feb96 MINMAX	(TextVarTxt,	0xfa00,0xfaff);		//Direct value references
//DeadCode MGA 05Feb96 MINMAX	(TextVarInt,	0xfb00,0xfbff);
//DeadCode MGA 05Feb96 MINMAX	(TextVarUID,	0xfc00,0xfcff);
//DeadCode MGA 05Feb96 
//DeadCode MGA 05Feb96 MINMAX	(TextRefRef,	0xfd00,0xffff);		//Multi-indirect references
//DeadCode MGA 05Feb96 MINMAX	(TextRefTxt,	0xfd00,0xfdff);		//Multi-indirect references
//DeadCode MGA 05Feb96 MINMAX	(TextRefInt,	0xfe00,0xfeff);
//DeadCode MGA 05Feb96 MINMAX	(TextRefUID,	0xff00,0xffff);

inline	TextRef		operator+(TextSnip0 t)	{return (TextRef) t;}
inline	TextRef		operator+(TextSnip1 t)	{return (TextRef) t;}
inline	TextRef		operator+(TextSnip2 t)	{return (TextRef) t;}
inline	TextRef		operator+(TextSnip3 t)	{return (TextRef) t;}
inline	TextRef		operator+(TextSnip4 t)	{return (TextRef) t;}
inline	TextRef		operator+(TextSnip5 t)	{return (TextRef) t;}
inline	TextRef		operator+(TextSnip6 t)	{return (TextRef) t;}
inline	TextRef		operator+(TextSnip7 t)	{return (TextRef) t;}
inline	TextRef		operator+(TextSnip8 t)	{return (TextRef) t;}
inline	TextRef		operator+(TextSnip9 t)	{return (TextRef) t;}
inline	TextRef		operator+(TextSnip10 t)	{return (TextRef) t;}
inline	TextRef		operator+(TextSnip11 t)	{return (TextRef) t;}
inline	TextRef		operator+(TextSnip12 t)	{return (TextRef) t;}
inline	TextRef		operator+(TextSnip13 t)	{return (TextRef) t;}
inline	TextRef		operator+(TextSnip14 t)	{return (TextRef) t;}
inline	TextRef		operator+(TextSnip15 t)	{return (TextRef) t;}
inline	TextRef		operator+(TextList t)	{return (TextRef) t;}
inline	TextList	operator+(TextList2 t)	{return (TextList) t;}	//To get to TextRef needs +(+TextListN)
inline	TextList	operator+(TextList3 t)	{return (TextList) t;}
inline	TextList	operator+(TextList4 t)	{return (TextList) t;}
inline	TextList	operator+(TextList5 t)	{return (TextList) t;}
inline	TextList	operator+(TextList6 t)	{return (TextList) t;}
inline	TextList	operator+(TextList7 t)	{return (TextList) t;}
inline	TextList	operator+(TextList8 t)	{return (TextList) t;}
inline	TextList	operator+(TextList9 t)	{return (TextList) t;}
inline	TextList	operator+(TextList10 t)	{return (TextList) t;}
inline	TextList	operator+(TextList11 t)	{return (TextList) t;}
inline	TextList	operator+(TextList12 t)	{return (TextList) t;}
inline	TextList	operator+(TextList13 t)	{return (TextList) t;}
inline	TextList	operator+(TextList14 t)	{return (TextList) t;}
inline	TextList	operator+(TextList15 t)	{return (TextList) t;}
inline	TextList	operator+(TextList16 t)	{return (TextList) t;}
inline	TextList	operator+(TextList17 t)	{return (TextList) t;}
inline	TextList	operator+(TextList18 t)	{return (TextList) t;}
inline	TextList	operator+(TextList19 t)	{return (TextList) t;}
inline	TextRef		operator+(TextBuild t)	{return (TextRef) t;}
inline	TextRef		operator+(TextPerm t)	{return (TextRef) t;}
inline	TextRef		operator+(TextPerm1 t)	{return (TextRef) t;}
inline	TextRef		operator+(TextPerm2 t)	{return (TextRef) t;}
inline	TextRef		operator+(TextPerm3 t)	{return (TextRef) t;}
inline	TextRef		operator+(TextPerm4 t)	{return (TextRef) t;}
inline	TextRef		operator+(TextPerm5 t)	{return (TextRef) t;}
//DeadCode MGA 05Feb96 inline	TextRef		operator+(TextVarTxt t)	{return (TextRef) t;}
//DeadCode MGA 05Feb96 inline	TextRef		operator+(TextVarInt t)	{return (TextRef) t;}
//DeadCode MGA 05Feb96 inline	TextRef		operator+(TextVarUID t)	{return (TextRef) t;}
//DeadCode MGA 05Feb96 inline	TextRef		operator+(TextRefTxt t)	{return (TextRef) t;}
//DeadCode MGA 05Feb96 inline	TextRef		operator+(TextRefInt t)	{return (TextRef) t;}
//DeadCode MGA 05Feb96 inline	TextRef		operator+(TextRefUID t)	{return (TextRef) t;}
inline	TextRef		operator+(TextConst t)	{return (TextRef) t;}
inline	TextRef		operator+(TextAddr t)	{return (TextRef) t;}
inline	TextRef		operator+(TextOffset t)	{return (TextRef) t;}
inline	TextRef		operator+(TextSeq t)	{return	(TextRef) t;}	
