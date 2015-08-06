//------------------------------------------------------------------------------
//Filename       textrefl.h
//System         
//Author         Martin Alderton
//Date           Mon 29 Jan 1996
//Description    
//------------------------------------------------------------------------------
#ifndef	TEXTREFL_Included
#define	TEXTREFL_Included

#define	DEFAULT_TEXTREFL 0

#include	"TEXT.H"
#include	"enumbits.m"
//#include	"Screenxy.h"

enum	TextType		{	TEXTTYPE_Empty=		0x00,
							TEXTTYPE_Snip0=		0x01,
							TEXTTYPE_Snipn=		0x02,
							TEXTTYPE_List=		0x03,
							TEXTTYPE_Build=		0x04,
							TEXTTYPE_Seq=		0x05,
							TEXTTYPE_Const=		0x08,
							TEXTTYPE_Addr=		0x09,
							TEXTTYPE_Offset=		0x0a,
//DeadCode MGA 17Jan96 							TEXTTYPE_VarText=	0x08,
//DeadCode MGA 17Jan96 							TEXTTYPE_VarInt=	0x09,
//DeadCode MGA 17Jan96 							TEXTTYPE_VarUID=	0x0a,
//DeadCode MGA 17Jan96 							TEXTTYPE_RefText=	0x0c,
//DeadCode MGA 17Jan96 							TEXTTYPE_RefInt=	0x0d,
//DeadCode MGA 17Jan96 							TEXTTYPE_RefUID=	0x0e
						};
//;;------------------------------------------------------------------------------
//;;Author		Jim Taylor
//;;Date			Mon 6 Nov 1995
//;;Description	Common class for text reference blocks 
//;;			
//;;------------------------------------------------------------------------------
typedef	struct	TextBlock
{
public:
//	TextType	type;
//	ULong		lastelement;
//	ULong		parameters;
	UByte		type;
	UByte		parameters;
	UByte		lastelement;
} 		*TextBlockPtr;

struct	TextSnipBlock:public	TextBlock
{
	UWord	textstarters[257];
	char	textdatas[1];	//legal in c++? Defined by volume of text
	static	TextSnipBlock*	make(string start,string end,int params);
};

struct	TextListBlock:public	TextBlock
{
	UWord	listentries;
//	TextRef	lists[1];			//Defined by lastelement*listentries
	UWord	lists[1];			//Defined by lastelement*listentries
	static	TextListBlock*	make(TextRef init[],int initsize,int params);
};

struct TextSeqBlock:public	TextBlock
{
	UWord 	seqentries;
	UWord   index[257];
//	TextRef seqs[1];
	UWord	seqs[1];
	static	TextSeqBlock*	make(TextRef init[],UWord index[],int seqindex,int r);

};

struct	TextIndirectBlock:public	TextBlock
{	//Used for Build and Perm
	char*	textstarters[256];
	TextIndirectBlock();
};


enum	BitInputMaskIllegals	{ILL_VALID=0,ILL_INDAFTER,ILL_INDB4,ILL_TEXTREF,ILL_OFFSET,ILL_UNIQUEID,ILL_ALIGN=255};
struct	BitInputForm
{
UByte	shift,
		mask;
};

enum	CharOutputLayout	{OFORM_NORM,OFORM_MIN,OFORM_LZ,OFORM_TH,OFORM_SIGN,OFORM_ALIGN=255};
//DeadCode MGA 29Jan96 enum	CharOutputLayout;

struct	CharOutputForm
{
UByte				chars;
CharOutputLayout	layout;
};

struct	TextBlock_constants
{
SLong			value;
BitInputForm	input;
CharOutputForm	output;
};

struct	TextConstBlock:	public TextBlock
{
char dummybyte;
TextBlock_constants	entry[1];
};

struct	TextBlock_addresses
{
void*		value;
BitInputForm	input;
CharOutputForm	output;
};

struct	TextAddrBlock: public TextBlock
{
char dummybyte;
TextBlock_addresses	entry[1];
};

//TempCode JIM 23Jan96 //Use this to get classes known to the textblock system
//TempCode MGA 29Jan96   class	TextBlockKnown
//TempCode MGA 29Jan96   {
//TempCode MGA 29Jan96   	dummy(){};
//TempCode MGA 29Jan96   };


#define	OFFSETCAST(struct,field)	((ULong)&(((struct*) 2)->field)-2)

struct	TextBlock_offsets
{
ULong	value;
BitInputForm	input;
CharOutputForm	output;
};

struct	TextOffsetBlock:public TextBlock
{
char dummybyte;
TextBlock_offsets	entry[1];
};


struct GetRetVal
{
  	ULong			value;
	BitInputMaskIllegals
					furtherindirection;
  	CharOutputForm	outputform;
};


//DeadCode JIM 23Jan96 struct	MemRefForm
//DeadCode JIM 23Jan96 {		//Identifies a memory location
//DeadCode JIM 23Jan96 ULong	*baseptr;
//DeadCode JIM 23Jan96 TextRef	offsetvar;
//DeadCode JIM 23Jan96 UWord	offsetmul;
//DeadCode JIM 23Jan96 UWord	offsetadd;
//DeadCode JIM 23Jan96 };
//DeadCode JIM 23Jan96 
//DeadCode JIM 23Jan96 struct	TextVarBlock:public	TextBlock
//DeadCode JIM 23Jan96 {	//Used for textref and UID
//DeadCode JIM 23Jan96 	MemRefForm	memrefs[256];
//DeadCode JIM 23Jan96 };
//DeadCode JIM 23Jan96 
//DeadCode JIM 23Jan96 struct	TextVarIntBlock:public	TextVarBlock
//DeadCode JIM 23Jan96 {
//DeadCode JIM 23Jan96 	NumberForm	numforms[256];
//DeadCode JIM 23Jan96 };
//DeadCode JIM 23Jan96 
//DeadCode JIM 23Jan96 struct	TextVarRefBlock:public	TextVarBlock
//DeadCode JIM 23Jan96 {
//DeadCode JIM 23Jan96   	TextRefRef	indir[256];
//DeadCode JIM 23Jan96 };

#endif
