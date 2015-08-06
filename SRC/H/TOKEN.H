//------------------------------------------------------------------------------
//Filename       token.h
//System         
//Author         Robert Slater
//Date           Mon 1 Apr 1996
//Description    Header file for the token dictionary class
//------------------------------------------------------------------------------
#ifndef	TOKEN_Included
#define	TOKEN_Included

#define	DEFAULT_TOKEN 0


#include	"bfcommon.h"



enum	MaxFile
{
	MaxFileCount 	=	32,
	MaxTotFileCount =	250,
	MaxFileBits		=	5
};

struct	TokenInit
{
	char*		tokentext;
	UsageType	usage:4;						//max 16
	TokenCode	tokencode:8;					//max 256
	Defined		defined:2;
	UWord		srcfname:MaxFileBits;			//max 16 files
};

typedef struct	DataInst	*DataRef;

struct	TokenName:public	TokenInit
{
	UWord		srcfline;					//max 64K lines per file
	DataRef		instance;

	string	TokenText();

	TokenName()
	{
		tokencode=T_unknown;
		instance=NULL;
	}

	void	SaveTxt(ufile	ofile,int	depth);
};


void	sayout(ufile	ofile,int	depth,char* rtype,TokenCode tokencode,char* anytext,Defined defined);
void	sayout(ufile	ofile,int	depth,char* rtype,TokenCode tokencode,int anytext,Defined defined);


void	EmitSysErr(int line,char* mark,char* filename,char* &maintext);
void	EmitWarning(int line,char* mark,char* filename,char* &maintext);
inline	void	EmitSysErr(char *fmt, ...)
{
	va_list	marker;	 //this points to an array of pointers
	va_start(marker, fmt);
	EmitSysErr(__LINE__ , marker[0], __FILE__ ,  fmt);

}
void	EmitWarning(char *fmt, ...);

#define	Assert(expr)	((expr)?((void)0):(EmitSysErr("Assert failed: " #expr),((void)0)))
//#define	Assert(expr)	((void)0)
#define	NAssert(expr)	((expr)?(EmitSysErr("Assert succeeded: " #expr),((void)0)):((void)0))
//#define	NAssert(expr)	((void)0)

//------------------------------------------------------------------------------
struct	DataInst
{
	TokenName*	tokentext;
	TokenCode	tokencode;

	virtual	void	SaveTxt(ufile	ofile,int depth)=0;
	virtual	void	PreSave(ufile	ofile,int depth)=0;
	virtual void	PreSave2(ufile	ofile,int depth)=0;
	virtual	void	SaveBin(ufile	ofile,int depth)=0;
	virtual	DataInst*	FindNode(TokenCode	t,int	level)=0;

	virtual	DataInst&	operator=(DataInst &src)=0;

	struct	RecurseChk;
	struct	RecurseChk
	{
		void* 				v1;
		static 	RecurseChk*	base;
		RecurseChk*			next;

		RecurseChk(void* v)
		{
			next=base;
			v1=v;
			base=this;
		}

		~RecurseChk()
		{
			RecurseChk** s=&base;
			while (*s!=this)
				s=&s[0]->next;
			*s=next;
		}

		operator int()
		{
			RecurseChk* s=next;
			while (s && s->v1!=v1)
				s=s->next;
			return(!s);
		}
	};

	#define	RECURSECHK		RecurseChk recursechk(this);if(recursechk)

};

DataInst&	DataInst::operator=(DataInst &src)
{
	if (src.tokentext)
		tokentext=src.tokentext;

	if (tokencode!=src.tokencode)
		EmitSysErr("Internal error - copying between different types!");

	return	(*this);
}

struct	IntegerInst:public	DataInst
{
	int	value;
	IntegerInst()
	{
		tokencode = T_int;
		value = -1;
		tokentext = NULL;
	}

	void	SaveTxt(ufile	ofile,int depth)
	{
		RECURSECHK
		{
 			if (tokencode==T_int)
 				sayout(ofile,depth,"Integer Data",tokencode,value,tokentext->defined);
 	 		elseif (tokencode==T_nint)
 				sayout(ofile,depth,"Integer Data",tokencode,-value,tokentext->defined);
 	 		else
 				sayout(ofile,depth,"Integer Bad!",tokencode,value,tokentext->defined);
		}
	}

	DataInst&	operator=(DataInst &src)
	{
		return(operator=((IntegerInst&) src));
	}

	IntegerInst&	operator=(IntegerInst &src)
	{
		value=src.value;
		return(IntegerInst&) (DataInst::operator =(src));
	}


	void	PreSave(ufile	/*ofile*/,int /*depth*/)
	{;}
	void	PreSave2(ufile	/*ofile*/,int /*depth*/)
	{;}
	void	SaveBin(ufile	ofile,int /*depth*/)
	{
		fputc(tokencode,ofile);
		fwrite(&value,4,1,ofile);
	}

	DataInst*	FindNode(TokenCode	t,int	level)
	{
		if (	(tokencode == t)
			&&	(level != 0)	)
			return(this);
		else
			return(NULL);
	}
};

//----------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------
//
//	TokenSpell is the dictionary class
//

class	TokenSpell:public DataInst
{
	public:

		static	char	*names[MaxTotFileCount+1];
		static	UWord	currsrcfname;
		static	UWord	topsrcfname;
		static	UWord	currsrcfline;
		static	UWord	filenestlevel;
		static	UFILE*	filelistfile;
		static	char	filebuff[80];
		static	int		fileend;
		static	char	*whitechars;
		static	char	*endchars;
		static	char	wordbuff[180];
		static	TokenSpell	FirstSpell;

		//------------------------------------------------------------------------------

		TokenName*	spelling[96];

		TokenSpell()
		{
			tokencode = T_sortentry;
			tokentext = NULL;
			int i = 96;
			while (i--)
				spelling[i]=NULL;
		}

		DataInst&	operator=(DataInst&)
		{
			EmitSysErr("Can't copy TokenSpell records");
			return(*this);
		}

		void	SaveTxt(ufile	ofile,int	depth)
		{
			int i=' '-1;
			while (++i<'~')
				if (spelling[i-' '])
				{	
					spelling[i-' ']->SaveTxt(ofile,depth+1);
				}
		}

		void	PreSave(ufile	/*ofile*/,int /*depth*/)
		{;}
		void	PreSave2(ufile	/*ofile*/,int /*depth*/)
		{;}

		DataInst*	FindNode(TokenCode,int)
		{
			return(NULL);
		}

		void	SaveBin(ufile	/*ofile*/,int /*depth*/)
		{
			EmitSysErr("Can't binary save the dictionary! Neat idea, though!");
		}


		static	TokenName	statictoken;
		static	IntegerInst	staticinteger;


		static	file	readfile(char*	name);
		static	void	setwritefile(char* path);
		static	ufile	writefile(char*	name,char mode);
		static	Bool	testspelling(char*	newname,TokenName*	&newtoken);
		static	Bool	findspelling(char*	newname,TokenName*	&newtoken);
		static	Bool	findspelling(file	ifile,TokenName*	&newtoken);
		static 	string	getword(file	ifile);
		static	char*	safetext(char* oldtext);
		static	void	addspelling(TokenInit tokentoadd);
		static	void	addfixedspellings(TokenInit	*fixedtokens);
		static	Bool	stripwhite(file	ifile);

};
extern	TokenSpell _Token;

#endif

