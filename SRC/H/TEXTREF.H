////TEMPCODE JIM 25/03/99 //------------------------------------------------------------------------------
////TEMPCODE JIM 25/03/99 //Filename       textref.h
////TEMPCODE JIM 25/03/99 //System         
////TEMPCODE JIM 25/03/99 //Author         Jim Taylor
////TEMPCODE JIM 25/03/99 //Date           Mon 6 Nov 1995
////TEMPCODE JIM 25/03/99 //Description    
////TEMPCODE JIM 25/03/99 //------------------------------------------------------------------------------
////TEMPCODE JIM 25/03/99 #ifndef	TEXTREF_Included
////TEMPCODE JIM 25/03/99 #define	TEXTREF_Included
////TEMPCODE JIM 25/03/99 
////TEMPCODE JIM 25/03/99 #define	DEFAULT_TEXTREF 0
////TEMPCODE JIM 25/03/99 
////TEMPCODE JIM 25/03/99 #include	"TEXT.H"
////TEMPCODE JIM 25/03/99 #include	"enumbits.m"
////TEMPCODE JIM 25/03/99 //#include	"Screenxy.h"
////TEMPCODE JIM 25/03/99 #include	"UniqueID.h"
////TEMPCODE JIM 25/03/99 
////TEMPCODE JIM 25/03/99 class	Window;
////TEMPCODE JIM 25/03/99 
////TEMPCODE JIM 25/03/99 
////TEMPCODE JIM 25/03/99 #ifndef	TEXTREFL_Included
////TEMPCODE JIM 25/03/99 typedef	struct	TextBlock 		*TextBlockPtr;
////TEMPCODE JIM 25/03/99 struct	TextSnipBlock;
////TEMPCODE JIM 25/03/99 struct	TextListBlock;
////TEMPCODE JIM 25/03/99 struct	TextIndirectBlock;
////TEMPCODE JIM 25/03/99 struct  TextSeqBlock;
////TEMPCODE JIM 25/03/99 struct	TextBlock_constants;
////TEMPCODE JIM 25/03/99 struct	GetRetVal;
////TEMPCODE JIM 25/03/99 struct	TextBlock_addresses;
////TEMPCODE JIM 25/03/99 struct	TextBlock_offsets;
////TEMPCODE JIM 25/03/99 enum	CharOutputLayout	{OFORM_NORM,OFORM_MIN,OFORM_LZ,OFORM_TH,OFORM_SIGN,OFORM_ALIGN=255};
////TEMPCODE JIM 25/03/99 
////TEMPCODE JIM 25/03/99 #endif
////TEMPCODE JIM 25/03/99 
////TEMPCODE JIM 25/03/99 enum	PrintFlags
////TEMPCODE JIM 25/03/99 		{	PF_BorderSizeMask=0x000f,
////TEMPCODE JIM 25/03/99 				PF_NoBorder=0x0000,PF_SmallBorder=0x0004,
////TEMPCODE JIM 25/03/99 				PF_MediumBorder=0x0008,PF_LargeBorder=0x000C,
////TEMPCODE JIM 25/03/99 			PF_HAlignMask=0x0030,
////TEMPCODE JIM 25/03/99 				PF_HAlignLeft=0x0000,PF_HAlignCenter=0x0010,
////TEMPCODE JIM 25/03/99 				PF_HAlignRight=0x0020,PF_HAlignJust=0x0030,
////TEMPCODE JIM 25/03/99 			PF_VAlignMask=0x0040,
////TEMPCODE JIM 25/03/99 				PF_VAlignPara=0,PF_VAlignCenter=0x0040,
////TEMPCODE JIM 25/03/99 			PF_VLeadMask=0x0700,
////TEMPCODE JIM 25/03/99 				PF_NoVLead=0,PF_SmallVLead=0x0200,PF_MedVLead=0x0400,
////TEMPCODE JIM 25/03/99 				PF_BigVLead=0x0600,PF_NegVLead=0x0700,
////TEMPCODE JIM 25/03/99 			PF_HLeadMask=0x3800,
////TEMPCODE JIM 25/03/99 				PF_NoHLead=0,PF_SmallHLead=0x0800,PF_MedHLead=0x1000,
////TEMPCODE JIM 25/03/99 				PF_BigHLead=0x1800,PF_NegHLead=0x3800,
////TEMPCODE JIM 25/03/99 			PF_SpaceLeadMask=0xC000,
////TEMPCODE JIM 25/03/99 				PF_SingleSpaces=0,PF_DoubleSpaces=0x4000,
////TEMPCODE JIM 25/03/99 				PF_HalfSpaces=0x8000,PF_ZeroSpaces=0xC000,
////TEMPCODE JIM 25/03/99 			PF_IgnoreBSlash=0x0800,
////TEMPCODE JIM 25/03/99 			PF_Spares=0x0080,PF_AllMask=0xffff
////TEMPCODE JIM 25/03/99 		};
////TEMPCODE JIM 25/03/99 
////TEMPCODE JIM 25/03/99 BITABLE(PrintFlags);
////TEMPCODE JIM 25/03/99 ADDORABLE(PrintFlags);
////TEMPCODE JIM 25/03/99 NOTABLE(PrintFlags,PF_AllMask);
////TEMPCODE JIM 25/03/99 
////TEMPCODE JIM 25/03/99 
////TEMPCODE JIM 25/03/99 #ifndef	FILEMAN_Included
////TEMPCODE JIM 25/03/99 class	fileblock;
////TEMPCODE JIM 25/03/99 typedef	fileblock *fileblockptr;
////TEMPCODE JIM 25/03/99 #endif
////TEMPCODE JIM 25/03/99 
////TEMPCODE JIM 25/03/99 //------------------------------------------------------------------------------
////TEMPCODE JIM 25/03/99 //Author		Jim Taylor
////TEMPCODE JIM 25/03/99 //Date			Mon 6 Nov 1995
////TEMPCODE JIM 25/03/99 //Modified	
////TEMPCODE JIM 25/03/99 //
////TEMPCODE JIM 25/03/99 //Description	Name overloading trickery. 
////TEMPCODE JIM 25/03/99 //				The basic text manipulation if we have already loaded the block
////TEMPCODE JIM 25/03/99 //------------------------------------------------------------------------------
////TEMPCODE JIM 25/03/99 class	TextC
////TEMPCODE JIM 25/03/99 {	//defines string based printing stuff - as opposed to enum based stuff
////TEMPCODE JIM 25/03/99 protected:
////TEMPCODE JIM 25/03/99 	int			CalcLineSplits(Window* w,char*	text,int boxwidth,int SpaceSize,int hlead,char escchar);
////TEMPCODE JIM 25/03/99 ///	ScreenXY	PrintLines(Window* w,int lines,ScreenXY xy,ScreenWH wh,PrintFlags pf,int linesep,int spcwidth,int hleading,char escchar);
////TEMPCODE JIM 25/03/99 	struct	LineSplitsEntry		
////TEMPCODE JIM 25/03/99 	{	//filled in by CalcLineSplits. Read by PrintLines
////TEMPCODE JIM 25/03/99 		UWord	LineWidthPixels;
////TEMPCODE JIM 25/03/99 		UWord	LineWidthChars;
////TEMPCODE JIM 25/03/99 		SWord	NumWords;
////TEMPCODE JIM 25/03/99 		char*	TextStarts;
////TEMPCODE JIM 25/03/99 	}	linesplits[50];
////TEMPCODE JIM 25/03/99 };
////TEMPCODE JIM 25/03/99 
////TEMPCODE JIM 25/03/99 class	TextB:private	TextC
////TEMPCODE JIM 25/03/99 {	//defines 'dirty' conversion stuff between enums and to text
////TEMPCODE JIM 25/03/99 protected:
////TEMPCODE JIM 25/03/99 	TextB();		//Only constructable as a base class 'cos constructor protected
////TEMPCODE JIM 25/03/99 	~TextB();		//Only constructable as a base class 'cos constructor protected
////TEMPCODE JIM 25/03/99 
////TEMPCODE JIM 25/03/99 	void			LoadTextBlocks();
////TEMPCODE JIM 25/03/99 //	ScreenXY		Print(Window* w,ScreenXY xy,ScreenWH wh,PrintFlags pf,char*	text);
////TEMPCODE JIM 25/03/99 	char*			TextDeref(TextBlockPtr,TextRef);
////TEMPCODE JIM 25/03/99 	char*			TextDeref(TextRef);
////TEMPCODE JIM 25/03/99 	void			TextBuildAlloc(ULong size,TextBuild& newtextref,char* &newtextptr);
////TEMPCODE JIM 25/03/99 	void			TextBuildFree(TextBuild);
////TEMPCODE JIM 25/03/99 	TextBlockPtr	loadtextblock(TextRef	textsnip);
////TEMPCODE JIM 25/03/99 	TextSnipBlock*	loadsnipblock(TextRef	textsnip,int expectedargcount);
////TEMPCODE JIM 25/03/99 //	void			LoadTextBlocks();
////TEMPCODE JIM 25/03/99 
////TEMPCODE JIM 25/03/99 	TextBuild	Conv(TextSnipBlock*,TextSnip0);
////TEMPCODE JIM 25/03/99 	TextBuild	Conv(TextSnipBlock*,TextSnip1,TextBuild);
////TEMPCODE JIM 25/03/99 	TextBuild	Conv(TextSnipBlock*,TextSnip2,TextBuild,TextBuild);
////TEMPCODE JIM 25/03/99 	TextBuild	Conv(TextSnipBlock*,TextSnip3,TextBuild,TextBuild,TextBuild);
////TEMPCODE JIM 25/03/99 	TextBuild	Conv(TextSnipBlock*,TextSnip4,TextBuild,TextBuild,TextBuild,TextBuild);
////TEMPCODE JIM 25/03/99 	TextBuild	Conv(TextSnipBlock*,TextRef,int NumParams,TextBuild Params[]);
////TEMPCODE JIM 25/03/99 
////TEMPCODE JIM 25/03/99 	TextSnip0	ConvTextList(TextListBlock*,TextList,ULong	index);
////TEMPCODE JIM 25/03/99 		
////TEMPCODE JIM 25/03/99 	TextBuild	Conv(TextPerm);
////TEMPCODE JIM 25/03/99 	TextBuild	Conv(TextListBlock* tb,UniqueID);
////TEMPCODE JIM 25/03/99 	TextBuild	DummyUID(UniqueID);
////TEMPCODE JIM 25/03/99 
////TEMPCODE JIM 25/03/99 	int 			gettextparams(char*);
////TEMPCODE JIM 25/03/99 	char			gettexttype(TextBlockPtr);
////TEMPCODE JIM 25/03/99 
////TEMPCODE JIM 25/03/99 	TextBlockPtr		loadedblocks[256];
////TEMPCODE JIM 25/03/99 	TextBlockPtr		currtextblock;	
////TEMPCODE JIM 25/03/99 	TextIndirectBlock	*currtextbuild;
////TEMPCODE JIM 25/03/99 	fileblockptr		loadedblock;
////TEMPCODE JIM 25/03/99 	TextRef				permbase;
////TEMPCODE JIM 25/03/99 
////TEMPCODE JIM 25/03/99 };	
////TEMPCODE JIM 25/03/99 
////TEMPCODE JIM 25/03/99 class	Text:private	TextB
////TEMPCODE JIM 25/03/99 {		//clean public interface... ahhhh!!!
////TEMPCODE JIM 25/03/99 public:
////TEMPCODE JIM 25/03/99 //written these
////TEMPCODE JIM 25/03/99 	Text();
////TEMPCODE JIM 25/03/99 	TextBuild	Conv(TextSnip0);
////TEMPCODE JIM 25/03/99 	TextBuild	Conv(TextSnip1,TextBuild);
////TEMPCODE JIM 25/03/99 	TextBuild	Conv(TextSnip2,TextBuild,TextBuild);
////TEMPCODE JIM 25/03/99 	TextBuild	Conv(TextSnip3,TextBuild,TextBuild,TextBuild);
////TEMPCODE JIM 25/03/99 	TextBuild	Conv(TextSnip4,TextBuild,TextBuild,TextBuild,TextBuild);
////TEMPCODE JIM 25/03/99 	TextBuild	Conv(TextSnip5,TextBuild,TextBuild,TextBuild,TextBuild,TextBuild);
////TEMPCODE JIM 25/03/99 	TextBuild	Conv(TextSnip6,TextBuild,TextBuild,TextBuild,TextBuild,TextBuild,
////TEMPCODE JIM 25/03/99 								TextBuild);
////TEMPCODE JIM 25/03/99 	TextBuild	Conv(TextSnip7,TextBuild,TextBuild,TextBuild,TextBuild,TextBuild,
////TEMPCODE JIM 25/03/99 								TextBuild,TextBuild);
////TEMPCODE JIM 25/03/99 	TextBuild	Conv(TextSnip8,TextBuild,TextBuild,TextBuild,TextBuild,TextBuild,
////TEMPCODE JIM 25/03/99 								TextBuild,TextBuild,TextBuild);
////TEMPCODE JIM 25/03/99 	TextBuild	Conv(TextSnip9,TextBuild,TextBuild,TextBuild,TextBuild,TextBuild,
////TEMPCODE JIM 25/03/99 								TextBuild,TextBuild,TextBuild,TextBuild);
////TEMPCODE JIM 25/03/99 	TextBuild	Conv(TextSnip10,TextBuild,TextBuild,TextBuild,TextBuild,TextBuild,
////TEMPCODE JIM 25/03/99 								TextBuild,TextBuild,TextBuild,TextBuild,TextBuild);
////TEMPCODE JIM 25/03/99 	TextBuild	Conv(TextSnip11,TextBuild,TextBuild,TextBuild,TextBuild,TextBuild,
////TEMPCODE JIM 25/03/99 								TextBuild,TextBuild,TextBuild,TextBuild,TextBuild,
////TEMPCODE JIM 25/03/99 								TextBuild);
////TEMPCODE JIM 25/03/99 	TextBuild	Conv(TextSnip12,TextBuild,TextBuild,TextBuild,TextBuild,TextBuild,
////TEMPCODE JIM 25/03/99 								TextBuild,TextBuild,TextBuild,TextBuild,TextBuild,
////TEMPCODE JIM 25/03/99 								TextBuild,TextBuild);
////TEMPCODE JIM 25/03/99 	TextBuild	Conv(TextSnip13,TextBuild,TextBuild,TextBuild,TextBuild,TextBuild,
////TEMPCODE JIM 25/03/99 								TextBuild,TextBuild,TextBuild,TextBuild,TextBuild,
////TEMPCODE JIM 25/03/99 								TextBuild,TextBuild,TextBuild);
////TEMPCODE JIM 25/03/99 	TextBuild	Conv(TextSnip14,TextBuild,TextBuild,TextBuild,TextBuild,TextBuild,
////TEMPCODE JIM 25/03/99 								TextBuild,TextBuild,TextBuild,TextBuild,TextBuild,
////TEMPCODE JIM 25/03/99 								TextBuild,TextBuild,TextBuild,TextBuild);
////TEMPCODE JIM 25/03/99 	TextBuild	Conv(TextSnip15,TextBuild,TextBuild,TextBuild,TextBuild,TextBuild,
////TEMPCODE JIM 25/03/99 								TextBuild,TextBuild,TextBuild,TextBuild,TextBuild,
////TEMPCODE JIM 25/03/99 								TextBuild,TextBuild,TextBuild,TextBuild,TextBuild);
////TEMPCODE JIM 25/03/99 	TextBuild	Conv(TextSnip16,TextBuild,TextBuild,TextBuild,TextBuild,TextBuild,
////TEMPCODE JIM 25/03/99 								TextBuild,TextBuild,TextBuild,TextBuild,TextBuild,
////TEMPCODE JIM 25/03/99 								TextBuild,TextBuild,TextBuild,TextBuild,TextBuild,
////TEMPCODE JIM 25/03/99 								TextBuild);
////TEMPCODE JIM 25/03/99 	TextBuild	Conv(TextSnip17,TextBuild,TextBuild,TextBuild,TextBuild,TextBuild,
////TEMPCODE JIM 25/03/99 								TextBuild,TextBuild,TextBuild,TextBuild,TextBuild,
////TEMPCODE JIM 25/03/99 								TextBuild,TextBuild,TextBuild,TextBuild,TextBuild,
////TEMPCODE JIM 25/03/99 								TextBuild,TextBuild);
////TEMPCODE JIM 25/03/99 	TextBuild	Conv(TextSnip18,TextBuild,TextBuild,TextBuild,TextBuild,TextBuild,
////TEMPCODE JIM 25/03/99 								TextBuild,TextBuild,TextBuild,TextBuild,TextBuild,
////TEMPCODE JIM 25/03/99 								TextBuild,TextBuild,TextBuild,TextBuild,TextBuild,
////TEMPCODE JIM 25/03/99 								TextBuild,TextBuild,TextBuild);
////TEMPCODE JIM 25/03/99 	TextBuild	Conv(TextSnip19,TextBuild,TextBuild,TextBuild,TextBuild,TextBuild,
////TEMPCODE JIM 25/03/99 								TextBuild,TextBuild,TextBuild,TextBuild,TextBuild,
////TEMPCODE JIM 25/03/99 								TextBuild,TextBuild,TextBuild,TextBuild,TextBuild,
////TEMPCODE JIM 25/03/99 								TextBuild,TextBuild,TextBuild,TextBuild);
////TEMPCODE JIM 25/03/99 	
////TEMPCODE JIM 25/03/99 	TextBuild	Conv(TextRef,int	index);
////TEMPCODE JIM 25/03/99 	TextBuild	Conv(TextList,int	index);
////TEMPCODE JIM 25/03/99 	TextSnip0	ConvSnip0(TextList,int	index);
////TEMPCODE JIM 25/03/99 		
////TEMPCODE JIM 25/03/99 	TextBuild	Conv(UniqueID);
////TEMPCODE JIM 25/03/99 	TextSnip0	ConvSnip0(UniqueID);
////TEMPCODE JIM 25/03/99 	TextBuild	Conv(TextBuild);
////TEMPCODE JIM 25/03/99 	TextBuild	Conv(TextPerm);
////TEMPCODE JIM 25/03/99  	TextBuild	Convert(TextRef);
////TEMPCODE JIM 25/03/99  	TextBuild	Conv(TextConst);
////TEMPCODE JIM 25/03/99  	TextBuild	Conv(TextAddr);
////TEMPCODE JIM 25/03/99   	TextBuild	Conv(TextSeq);
////TEMPCODE JIM 25/03/99 	TextBuild	Conv_List(TextRef* &);
////TEMPCODE JIM 25/03/99 
////TEMPCODE JIM 25/03/99  	GetRetVal getval(TextRef* &);
////TEMPCODE JIM 25/03/99  	GetRetVal getoneval(TextRef);
////TEMPCODE JIM 25/03/99  	GetRetVal getval(GetRetVal&, TextRef);
////TEMPCODE JIM 25/03/99  	
////TEMPCODE JIM 25/03/99  	GetRetVal getval(TextBlock_constants);
////TEMPCODE JIM 25/03/99  	GetRetVal getval(TextBlock_addresses);
////TEMPCODE JIM 25/03/99  	GetRetVal getval(GetRetVal&, TextBlock_offsets);
////TEMPCODE JIM 25/03/99  	GetRetVal getval(TextAddr, TextOffset);
////TEMPCODE JIM 25/03/99 	
////TEMPCODE JIM 25/03/99 	TextBuild Conv(GetRetVal);
////TEMPCODE JIM 25/03/99  	TextBlockPtr loadintblock(TextRef );
////TEMPCODE JIM 25/03/99  	TextBlock_constants	  TextconstDeref(TextBlockPtr, TextRef);
////TEMPCODE JIM 25/03/99  	TextBlock_addresses	  TextaddrDeref(TextBlockPtr, TextRef);
////TEMPCODE JIM 25/03/99  	TextBlock_offsets	  TextoffDeref(TextBlockPtr, TextRef);
////TEMPCODE JIM 25/03/99  	int	  	  TextSeqDeref(TextBlockPtr, TextRef);
////TEMPCODE JIM 25/03/99 
////TEMPCODE JIM 25/03/99 
////TEMPCODE JIM 25/03/99 	TextBuild	Conv(char*);
////TEMPCODE JIM 25/03/99 	TextBuild	Conv(SLong value,int chars=1,CharOutputLayout=OFORM_NORM);
////TEMPCODE JIM 25/03/99 
////TEMPCODE JIM 25/03/99 	TextBuild	Conv(TextRef ...);	//not written yet... quite trivial though
////TEMPCODE JIM 25/03/99 	TextBuild	ConvBrief(TextRef* &);		//main brief engine
////TEMPCODE JIM 25/03/99 
////TEMPCODE JIM 25/03/99 private:	//compile-time error-trapping - never written
////TEMPCODE JIM 25/03/99 	TextBuild	Conv(SLong,TextBuild);
////TEMPCODE JIM 25/03/99 	TextBuild	Conv(SLong,TextBuild,TextBuild);
////TEMPCODE JIM 25/03/99 	TextBuild	Conv(SLong,TextBuild,TextBuild,TextBuild);
////TEMPCODE JIM 25/03/99 	TextBuild	Conv(SLong,TextRef);
////TEMPCODE JIM 25/03/99 	TextBuild	Conv(TextList ...);
////TEMPCODE JIM 25/03/99 	TextBuild	Conv(TextRef);
////TEMPCODE JIM 25/03/99 
////TEMPCODE JIM 25/03/99 	TextBuild	convlist(TextRef* &);
////TEMPCODE JIM 25/03/99 
////TEMPCODE JIM 25/03/99 
////TEMPCODE JIM 25/03/99 public:
////TEMPCODE JIM 25/03/99 
////TEMPCODE JIM 25/03/99 #ifndef	WINSTALL
////TEMPCODE JIM 25/03/99 //Written these
////TEMPCODE JIM 25/03/99 //ScreenXY	Print(Window* w,ScreenXY xy,ScreenWH wh,PrintFlags pf,TextBuild	textref);
////TEMPCODE JIM 25/03/99 //ScreenXY	Print(Window* w,ScreenXY xy,ScreenWH wh,PrintFlags pf,TextRef		textref);
////TEMPCODE JIM 25/03/99 //ScreenXY	Print(Window* w,ScreenXY xy,ScreenWH wh,PrintFlags pf,TextPerm	textref);
////TEMPCODE JIM 25/03/99 //ScreenXY	Print(Window* w,ScreenXY xy,ScreenWH wh,PrintFlags pf,TextSnip0	textref);
////TEMPCODE JIM 25/03/99 
////TEMPCODE JIM 25/03/99 //ScreenXY	Print(Window* w,ScreenXY xy,ScreenWH wh,TextBuild	textref,PrintFlags pf)
////TEMPCODE JIM 25/03/99 //			{return(Print(w,xy,wh,pf,textref));}	
////TEMPCODE JIM 25/03/99 //ScreenXY	Print(Window* w,ScreenXY xy,ScreenWH wh,TextRef	textref,PrintFlags pf)
////TEMPCODE JIM 25/03/99 //			{return(Print(w,xy,wh,pf,textref));}	
////TEMPCODE JIM 25/03/99 //ScreenXY	Print(Window* w,ScreenXY xy,ScreenWH wh,TextPerm	textref,PrintFlags pf)
////TEMPCODE JIM 25/03/99 //			{return(Print(w,xy,wh,pf,textref));}	
////TEMPCODE JIM 25/03/99 //ScreenXY	Print(Window* w,ScreenXY xy,ScreenWH wh,TextSnip0	textref,PrintFlags pf)
////TEMPCODE JIM 25/03/99 //			{return(Print(w,xy,wh,pf,textref));}
////TEMPCODE JIM 25/03/99 
////TEMPCODE JIM 25/03/99 void		FreePermPage(TextPage&);
////TEMPCODE JIM 25/03/99 TextPerm	Perm(TextBuild,TextPage&);
////TEMPCODE JIM 25/03/99 void		Perm(TextPerm);
////TEMPCODE JIM 25/03/99 #endif
////TEMPCODE JIM 25/03/99 
////TEMPCODE JIM 25/03/99 	Bool	Text::Stringify(char *dest,TextBuild src);			//DAW 13Feb97
////TEMPCODE JIM 25/03/99 
////TEMPCODE JIM 25/03/99 };
////TEMPCODE JIM 25/03/99 
////TEMPCODE JIM 25/03/99 
////TEMPCODE JIM 25/03/99 extern	Text	_Text;
////TEMPCODE JIM 25/03/99 
////TEMPCODE JIM 25/03/99 
////TEMPCODE JIM 25/03/99 #endif
////TEMPCODE JIM 25/03/99 