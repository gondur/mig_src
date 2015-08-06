//------------------------------------------------------------------------------
//Filename       textbin.cpp
//System         
//Author         Martin Alderton
//Date           Wed 6 Dec 1995
//Description    Text Binerifier 
//------------------------------------------------------------------------------
#include	<stdlib.h>
#include	<stdio.h>
#include	<conio.h>
#include	<io.h>
#include	<string.h>
#include	<stdarg.h>
#include	<ctype.h>
#include	<fstream.h>

typedef FILE	*file;
#include	"dosdefs.h"
#define	TEXTREF_NOTYPES
#include 	"textbin.h" 
#include	"intref.h"

#define	LINELEN	255

const	STRREFLISTSIZE	= 5120;
const	Array = ARRAYSIZE;
const	BigArray = BIGARRAYSIZE;
const	UIDLISTSIZE	=	16;

char	headerfile[50]=		"H\\TEXTENUM.TMP";					//DAW 31Oct96
char	InputFile[50]=		"FONT\\INPUTDAT.TXT";
char	dirstring[50]=		"..\\GAME\\TEXT\\";	//use to designate target directory

char	EnumConstFile[80]=	"h\\const";
char	EnumAddrFile[80]=	"h\\addr";
char	EnumOffsFile[80]=	"h\\offs";


SnipLinkPtr sniplink[20];	//one linked list for each number of arguments.

ListLinkPtr listlink[20];	//is that large enough ?

SnipLinkPtr SStart[20];

ListLinkPtr LStart[20];

SeqLinkPtr seqlink;

SeqLinkPtr SeqStart;

ConstantstrucPtr constant;
ConstantstrucPtr CStart;
AddressstrucPtr address;
AddressstrucPtr AStart;
OffsetstrucPtr offset;
OffsetstrucPtr OStart;



int numfiles=0;
int numsnipfiles=0;
int numlistfiles=0;
int numseqfiles=0;
char sstr[BigArray];
char	*sptr;
UWord seqstrref[STRREFLISTSIZE];
UWord	*otherseqptr;
UWord allstrref[STRREFLISTSIZE];
UWord *allstrrefptr;

int snipindex=0;
int snipletter=0;
int listletter=0;
int listindex=0;
int seqindex=0; 
int seqletter=0;

int UIDNamesBase=0;
int	base=0;
int basetable[44];

int currline=1;
char currfilename[80];

SnipLinkPtr snipptr;
ListLinkPtr listptr;
SeqLinkPtr seqptr;
ConstantstrucPtr constptr;
AddressstrucPtr addrptr;
OffsetstrucPtr offsptr;

int concount=0;		//use to count up number of enteries of each 
int addcount=0;		//for putting into 256 blocks.
int offcount=0;


char Letter[26]={'A','B','C','D','E','F','G','H','I','J','K',
				'L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
//------------------------------------------------------------------------------
//Enhanced error messaging. __FILE__ and __LINE__ are inserted using 
//inline functuions, so they should be accurate!
//
void	EmitSysErr(int line,char* mark,char* filename,char* &maintext)
{
	INT3();
	va_list	marker={mark};
	printf("Error : code position: %s@%i.", // Reading file: %s, line: %i\n",
				filename,line);//,names[currsrcfname],currsrcfline);
	vprintf(maintext,marker);
	printf("\n");
	exit(10);
}

void	EmitWarning(int line,char* mark,char* filename,char* &maintext)
{
	va_list	marker={mark};
	printf("Warning: code: %s(%i)",//; read: %s(%i):",
				filename,line/*,names[currsrcfname],currsrcfline*/);
	vprintf(maintext,marker);
	printf("\n");
}

//DeadCode MGA 18Dec95 void	EmitSysErr(char *message)  
//DeadCode MGA 18Dec95 {	//This is to stop message with no parameters getting % commands expanded!
//DeadCode MGA 18Dec95 	char*	fred[2]={"%s",message};
//DeadCode MGA 18Dec95 	EmitSysErr(__LINE__ , (char*) fred , __FILE__ ,  fred[0]);
//DeadCode MGA 18Dec95 
//DeadCode MGA 18Dec95 }

void	EmitSysErr(char *fmt, ...)
{
	va_list	marker;	 //this points to an array of pointers
	va_start(marker, fmt);
	EmitSysErr(__LINE__ , marker[0], __FILE__ ,  fmt);

}

void	EmitWarning(char *message)
{
	char*	fred[2]={"%s",message};
	EmitWarning(__LINE__ , (char*) fred , __FILE__ ,  fred[0]);
}


void	EmitWarning(char *fmt, ...)
{
	va_list	marker;	 //this points to an array of pointers
	va_start(marker, fmt);
	EmitWarning(__LINE__ , marker[0], __FILE__ ,  fmt);

}
//Need to stop expansion of any accidental %x in the expression
#define	Assert(expr)	((expr)?((void)0):(EmitSysErr("Assert failed: " #expr),((void)0)))
//#define	Assert(expr)	((void)0)
#define	NAssert(expr)	((expr)?(EmitSysErr("Assert failed: " #expr),((void)0)):((void)0))
//#define	NAssert(expr)	((void)0)

/////////////////////////////////////////////////////
char	*whitechars=" \t",		//doesn't include newline - handled separately
			//this list comes from the punctuation tokens identified below.
		*endchars=" \n\t" "\"';!=,",
		wordbuff[255];
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		stripwhite
//Author		Jim Taylor
//Date			Mon 27 Nov 1995
//
//Description	Strips out any whitespace characters, and counts carriage returns
//
//Inputs		
//
//Returns		returns FALSE if EOF read
//				returns TRUE if more symbols to follow
//------------------------------------------------------------------------------
Bool	stripwhite(file ifile)
{
char c;
	for(;;)
	{
		c=(char) fgetc(ifile);
		if (feof(ifile))	return (FALSE);
		if (c=='/')
		{
			if (feof(ifile))	return (FALSE);
			c='\n';
			while (fgetc(ifile)!=c);		//comments: single slash - to end of line
				if (feof(ifile))	return (FALSE);
		}
		if (feof(ifile))	return (FALSE);
string	p1=whitechars;
		if (c=='\n')
			currline++;//	currsrcfline++;
		else
			while ((c!=*p1) && *p1) p1++;
	breakif (*p1==0);
	}
 ungetc(c,ifile);
 return(TRUE);
}
/////////////////////////////////////////////////////

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		getword
//Author		Jim Taylor
//Date			Mon 27 Nov 1995
//
//Description	Gets 1 symbol... either a word or punctuation.
//				I think this routine can error if it runs out of data,
//				because the caller should know when to expect EOF,
//				but not yet!
//				
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
string	getword(file ifile)
{	//2 stages to getting a word:
	//	1) leading white removal
	//	2) copy to terminator
	//1) leading white removal
char c;
string
	myword=NULL;
	if (!stripwhite(ifile))
		return(NULL);
	elser
	{
	 	c=(char) fgetc(ifile);
string 	outbuf=wordbuff;
		myword=outbuf;
		//test for punctuation (ok... spc/tab in there as well!)

string	p1=endchars;
		while ((c!=*p1) && *p1) p1++;	
		if (*p1)
		{	//punctuation only 1 char long...
			*(outbuf++)=c;
			*outbuf=0;
			return (myword);
		}
		elser
		{	
			for(;;)
			{	//build string up to next punctuation or white
				if (islower(c))	c=(char)toupper(c);
				*(outbuf++)=c;
				*outbuf=0;		//handle early return for eof
				c=(char) fgetc(ifile);
				//EOF during a word read is not an error, really
				if (feof(ifile))	return (myword);

string			p1=endchars;
				while ((c!=*p1) && *p1) p1++;
			breakif (*p1);
			}
			ungetc(c,ifile);
			return (myword);
		}
	}
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		getcasesensitiveword
//Author		Martin Alderton
//Date			Tue 23 Jan 1996
//
//Description	copied from Jim's getword. does not turn everything to upper
//				case but leaves it as it finds it instead.
//				
//				
//				
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
string	getcasesensitiveword(file ifile)
{	
char c;
string
	myword=NULL;
	if (!stripwhite(ifile))
		return(NULL);
	elser
	{
	 	c=(char) fgetc(ifile);
string 	outbuf=wordbuff;
		myword=outbuf;
		//test for punctuation (ok... spc/tab in there as well!)

string	p1=endchars;
		while ((c!=*p1) && *p1) p1++;	
		if (*p1)
		{	//punctuation only 1 char long...
			*(outbuf++)=c;
			*outbuf=0;
			return (myword);
		}
		elser
		{	
			for(;;)
			{	//build string up to next punctuation or white
//DeadCode MGA 23Jan96 				if (islower(c))	c=(char)toupper(c);
				*(outbuf++)=c;
				*outbuf=0;		//handle early return for eof
				c=(char) fgetc(ifile);
				//EOF during a word read is not an error, really
				if (feof(ifile))	return (myword);

string			p1=endchars;
				while ((c!=*p1) && *p1) p1++;
			breakif (*p1);
			}
			ungetc(c,ifile);
			return (myword);
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		stradd
//Author		Martin Alderton
//Date			Mon 18 Dec 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	stradd(string text,char c)
{
int	l=strlen(text);
	text[l+1]=0;
	text[l]=c;
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitLinkLists
//Author		Martin Alderton
//Date			Fri 8 Dec 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void InitLinkLists()
{
	int i;

	for (i=0;i<20;i++)
	{
		sniplink[i]=NULL;
		listlink[i]=NULL;
		SStart[i]=NULL;
		LStart[i]=NULL;
	}
	constant=NULL;
	CStart=NULL;
	address=NULL;
	AStart=NULL;
	offset=NULL;
	OStart=NULL;

	for (i=0;i<43;i++)
	{
		basetable[i]=0;
	}

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ReadLine
//Author		Martin Alderton
//Date			Thu 4 Jan 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
InputLine ReadLine(char* word,FILE *file)
{
char lastchar;
char c;
char*	tmpstrsrc;
InputLine inputline;

	tmpstrsrc=word;

// start of line scanning code 					//MGA 07Dec95
			
//TempCode MGA 18Dec95 				c= (char)fgetc(file);
//TempCode MGA 18Dec95 				if ((c==';')||(c=='!'))
//DeadCode MGA 18Dec95 				{
//DeadCode MGA 18Dec95 					if ((tmpstrsrc[0]==';')||(tmpstrsrc[0]=='!'));
//DeadCode MGA 18Dec95 
//DeadCode MGA 18Dec95 				}	

	strcpy(inputline.type,tmpstrsrc);

	if ((inputline.type[0]!='/')&&(strcmp(inputline.type,"//")!=0))
	{
		
		tmpstrsrc=getword(file);
		strcpy(inputline.name,tmpstrsrc);

		tmpstrsrc=getword(file);
		if (tmpstrsrc[0]=='=')
			tmpstrsrc=getword(file);

		if (tmpstrsrc[0]=='"' || tmpstrsrc[0]=='\'')
		{
			inputline.text[0]=
				c=tmpstrsrc[0];
			inputline.text[1]='\0';
			do
			{
				lastchar=c;
				c=(char) fgetc(file);
//DeadCode JIM 28Aug96 				while (c=='\t')
//DeadCode JIM 28Aug96 					c=(char) fgetc(file);
				if (c=='\n')
				{
					currline++;

					c=(char) fgetc(file);
					while (c=='\t')
						c=(char) fgetc(file);
					if ((c!=' ') && (lastchar!=' '))
					{
						stradd(inputline.text,' ');
					}
				}
				stradd(inputline.text,c);
			}while (c!=tmpstrsrc[0]);
			tmpstrsrc=getword(file);
			if (tmpstrsrc[0]!=';')
				EmitSysErr("Expecting ; but found %s at text line %d of file %s",tmpstrsrc,currline,currfilename);

		}
		else
		{
			inputline.text[0]='\0';
//DeadCode MGA 21Dec95 				ungetc(c,file);
//DeadCode MGA 21Dec95 				tmpstrsrc=getword(file);
			if (tmpstrsrc[0]!=';')
			{
				strcpy(inputline.text,tmpstrsrc);

				tmpstrsrc=getword(file);

				while (tmpstrsrc && tmpstrsrc[0]!=';')
				{
					if (tmpstrsrc[0]!=',')
						EmitSysErr("Expecting ',' , not %s at text line %d of file %s",tmpstrsrc,currline,currfilename);
					stradd(inputline.text,',');
					tmpstrsrc=getword(file);
					strcat(inputline.text,tmpstrsrc);
					tmpstrsrc=getword(file);
				}
			}
			else
			{
				strcpy(inputline.text,"");
			}
		}

	}
//end of line scanning code 					//MGA 07Dec95
return(inputline);

}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CountPerCent
//Author		Martin Alderton
//Date			Mon 8 Jan 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
int CountPerCent(char *text,Bool tell)
{
int	argbits=0;
int	argnum=0;
int i;	
int count=0;

	for (i=0;i<strlen(text);)
	{
	 	if (text[i]=='%')
			if (	(text[i+1]!=0)
				&&	(text[i+1]>='0')
				&&	(text[i+1]<='9')
				)
			{
				argnum=text[i+1]-'0';
				if (argnum==0)
					argnum=text[i+2]+10-'0';
				if (tell==TRUE)
				{
					if (argbits&(1<<argnum))
						EmitWarning("%%%i repeated in string %s at text line %d of file %s",
							argnum,text,currline,currfilename);
				}
				argbits|=(1<<argnum);
				if (count<argnum)
					count=argnum;
			}
			else
			if (text[i+1]=='%')
				i++;
		i++;
	}//end of %x counting code
	if (tell==TRUE)
	{
		for (i=1;i<count;i++)
			if ((argbits&(1<<i))==0)
				EmitWarning("%%%i not used in string %s at text line %d of file %s"
					,i,text,currline,currfilename);
	}
	return(count);

}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessLine
//Author		Martin Alderton
//Date			Thu 4 Jan 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ProcessLine(InputLine inputline)
{
FILE *fp;
char *includefile;
int i;
int count=0;
int listcount=1;
Bool Add = TRUE;
struct SnipLink onesnip;
struct ListLink onelist;
struct SeqLink oneseq;
InputLine newinputline;
char* tmpstrsrc;
	 
if ((strcmp(inputline.type,"SNIP")==0))
	{
		//Snip dealing code
		count=CountPerCent(inputline.text,TRUE);

		//code to add entry to linked list
		
		strcpy(onesnip.name,(char *)inputline.name);
//DeadCode MGA 21Dec95 				strcpy(onesnip.text,(char *)inputline.text);
		onesnip.arguments=(UByte)count;

		onesnip.link = NULL;
		AddToLinkedList(count,onesnip);
		count=0;

	}//end of snip code
	else if ((strcmp(inputline.type,"LIST")==0))
	
		{
		//List code- assumes there will be at least one name in list
		listcount=1;
		for (i=0;i<strlen(inputline.text);i++)
		{
			if ((inputline.text[i]==',')&&(inputline.text[i+1]!=NULL))
			{
				listcount++;
			}
		}

		// code to add entry  to other linked list
		
		strcpy(onelist.name,(char *)inputline.name);
//DeadCode MGA 21Dec95 				strcpy(onelist.text,(char *)inputline.text);

		onelist.link = NULL;
		AddToLinkedList(listcount,onelist);

	}// end of list code

	else if (strcmp(inputline.type,"SEQ")==0)
	{
		strcpy(oneseq.name,(char *)inputline.name);
//TempCode MGA 18Jan96 		strcpy(oneseq.text,(char *)inputline.text);
		 					//this not needed this pass.
		oneseq.link=NULL;
		AddToLinkedList(oneseq);
	}

	else if (((strcmp(inputline.type,"#INCLUDE")==0))
		||((strcmp(inputline.type,"INCLUDE")==0))
			||((strcmp(inputline.type,"include")==0))
			||((strcmp(inputline.type,"#include")==0)))
	{
		includefile=inputline.name;
		if ((fp=fopen(includefile,"rt"))==NULL)
			{
				fprintf (stderr,"Cannot Open include file %s [ProcessLine]/n",includefile);
			}
		else
			{
				while(!feof(fp))
				{
					int oldline;
					char oldfilename[80];
					oldline=currline;
					currline=1;
					strcpy(oldfilename,currfilename);
					strcpy(currfilename,includefile);
					tmpstrsrc=getword(fp);
					while ((tmpstrsrc[0]==';')||(tmpstrsrc[0]=='!'))
						tmpstrsrc=getword(fp);

					while(tmpstrsrc)
					{
						newinputline=ReadLine(tmpstrsrc,fp);

						ProcessLine(newinputline);

						strcpy(newinputline.type,"");
						strcpy(newinputline.name,"");
						strcpy(newinputline.text,"");

						tmpstrsrc=getword(fp);
						while ((tmpstrsrc[0]==';')||(tmpstrsrc[0]=='!'))
							tmpstrsrc=getword(fp);

					};
					currline=oldline;
					strcpy(currfilename,oldfilename);
				};
			}
		fclose(fp);
	
	}	
	else
	{
		EmitSysErr("Invalid Type in Input File! at text line %d of file %s"
			,currline,currfilename);
	}

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ReadLine
//Author		Martin Alderton
//Date			Wed 10 Jan 1996
//
//Description	rewrite. The instructions need to retain their capitalisation
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
RefInputLine ReadIntLine(char* word,FILE *file)
{
//char lastchar;
//char c;
int i=0;
char*	tmpstrsrc;
RefInputLine inputline;

strcpy(inputline.name,"");
strcpy(inputline.data[0],"");
strcpy(inputline.data[1],"");
strcpy(inputline.data[2],"");


	tmpstrsrc=word;

	strcpy(inputline.type,tmpstrsrc);

	if (strcmp(inputline.type,"INT")==0)
	{
		
		tmpstrsrc=getword(file);
		strcpy(inputline.name,tmpstrsrc);

		tmpstrsrc=getcasesensitiveword(file);
		if (tmpstrsrc[0]=='=')
			tmpstrsrc=getcasesensitiveword(file);

		strcpy(inputline.data[i],tmpstrsrc);

		tmpstrsrc=getword(file);

				
		while (tmpstrsrc && tmpstrsrc[0]!=';')
			{
				if (tmpstrsrc[0]!=',')
				{
					stradd(inputline.data[i],' ');
					strcat(inputline.data[i],tmpstrsrc);
					tmpstrsrc=getword(file);

				}
				else if (tmpstrsrc[0]==',')
				{
					tmpstrsrc=getword(file);
					i++;
					strcat(inputline.data[i],tmpstrsrc);
					tmpstrsrc=getword(file);

				}

				if (i==3)
				{
					EmitSysErr("Too Many Parameters !");
				}
			}
	}
	else
		EmitSysErr("Input not of type INT !");

return(inputline);

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessLine
//Author		Martin Alderton
//Date			Wed 10 Jan 1996
//
//Description	Add Data to correct linked list.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ProcessIntLine(RefInputLine inputline)
{

struct Constantstruc oneconst;
struct Addressstruc oneaddr;
struct Offsetstruc oneoffs;
Bool CFlag = FALSE;
Bool AFlag = FALSE;
Bool OFlag = FALSE;

strcpy(oneconst.name,"");
oneconst.constant=0;
strcpy(oneconst.format,"");
oneconst.link=NULL;
strcpy(oneaddr.name,"");
strcpy(oneaddr.address,"");
strcpy(oneaddr.format1,"");
strcpy(oneaddr.format2,"");
oneaddr.link=NULL;
strcpy(oneoffs.name,"");
strcpy(oneoffs.mask_shift1,"");
strcpy(oneoffs.mask_shift2,"");
strcpy(oneoffs.format1,"");
strcpy(oneoffs.format2,"");
oneoffs.link=NULL;


	// work out what it is

	if ((inputline.data[0][0]>='0')&&(inputline.data[0][0]<='9'))
		CFlag=TRUE;
	else if (inputline.data[0][0]=='+')
		OFlag=TRUE;
	else
		AFlag=TRUE;

	//Code Debugging test only... 

	if (((CFlag==TRUE)&&(OFlag==TRUE))||((CFlag==TRUE)&&(AFlag==TRUE))||
		((AFlag==TRUE)&&(OFlag==TRUE)))
			EmitSysErr("Input type selection faliure in ProcessLine !");

	// then work out where to put it, and no smart answers please.
	// then put it there

	if (CFlag==TRUE)
	{
		strcpy(oneconst.name,(char *)inputline.name);
		oneconst.constant=atoi(inputline.data[0]);
		if (inputline.data[1]!=NULL)
			strcpy(oneconst.format,inputline.data[1]);
		oneconst.link=NULL;
		AddToLinkedList(oneconst);
	}
	else if (AFlag==TRUE)
	{
		strcpy(oneaddr.name,(char *)inputline.name);
		strcpy(oneaddr.address,(char *)inputline.data[0]);
		if (inputline.data[1]!=NULL)
			strcpy(oneaddr.format1,inputline.data[1]);
		if (inputline.data[2]!=NULL)
			strcpy(oneaddr.format2,inputline.data[2]);
		oneaddr.link=NULL;
		AddToLinkedList(oneaddr);
	}
	else if (OFlag==TRUE)
	{
		strcpy(oneoffs.name,(char *)inputline.name);
		char temp1[40]="";
		char temp2[40]="";
		int i;
		for (i=0;i<strlen(inputline.data[0]);i++)
		{
			while ((inputline.data[0][i]!=':')&&(inputline.data[0][i]!=NULL))
			{
				stradd(temp1,inputline.data[0][i]);
				i++;
			}
			if (inputline.data[0][i]==':')
			{
			 	i++;
				while (inputline.data[0][i]!=NULL)
				{
					i++;
					stradd(temp2,inputline.data[0][i]);
				}
			}
			else
			{
				strcpy(temp2,temp1);
				strcpy(temp1,"*void");
			}
		}

		strcpy(oneoffs.mask_shift1,temp1);
		strcpy(oneoffs.mask_shift2,temp2);
		if (inputline.data[1]!=NULL)
			strcpy(oneoffs.format1,inputline.data[1]);
		if (inputline.data[2]!=NULL)
			strcpy(oneoffs.format2,inputline.data[2]);
		oneoffs.link=NULL;
		AddToLinkedList(oneoffs);
	}


}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ReadData
//Author		Martin Alderton
//Date			Wed 6 Dec 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ReadData()
{
FILE *file;
char *filename;
filename = InputFile;
strcpy(currfilename,InputFile);
InputLine inputline;
char* tmpstrsrc;
RefInputLine refinputline;
int i;

strcpy(refinputline.type,"");
strcpy(refinputline.name,"");
for (i=0;i<3;i++)
	strcpy(refinputline.data[i],"");


if ((file=fopen(filename,"rt"))==NULL)
	{
		fprintf (stderr,"Cannot Open input file /n");
	}
else
	{
		while(!feof(file))
		{
			tmpstrsrc=getword(file);
			while ((tmpstrsrc[0]==';')||(tmpstrsrc[0]=='!'))
				tmpstrsrc=getword(file);
			
			while (tmpstrsrc)
			{
				if (strcmp(tmpstrsrc,"INT")!=0)
				{
					inputline=ReadLine(tmpstrsrc,file);

					ProcessLine(inputline);

					strcpy(inputline.type,"");
					strcpy(inputline.name,"");
					strcpy(inputline.text,"");
				}
				else
				{
					refinputline=ReadIntLine(tmpstrsrc,file);

					ProcessIntLine(refinputline);

					strcpy(refinputline.type,"");
					strcpy(refinputline.name,"");
					for (i=0;i<3;i++)
						strcpy(refinputline.data[i],"");
				}
				tmpstrsrc=getword(file);
					while ((tmpstrsrc[0]==';')||(tmpstrsrc[0]=='!'))
						tmpstrsrc=getword(file);
			};
		};
	}
	fclose(file);
//DeadCode MGA 23Jan96 //TempCode MGA 18Jan96  	Clear();
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Clear
//Author		Martin Alderton
//Date			Tue 19 Dec 1995
//
//Description	 A dead procedure that has a nasty habit of killing the stack
//					so don't even think about using it.
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//DeadCode MGA 22Jan96  void Clear()
//DeadCode MGA 22Jan96  {
//DeadCode MGA 22Jan96   	int i;
//DeadCode MGA 22Jan96  	for (i=0;i<20;i++)
//DeadCode MGA 22Jan96  	{
//DeadCode MGA 22Jan96  		sniplink[i]=NULL;
//DeadCode MGA 22Jan96  		listlink[i]=NULL;
//DeadCode MGA 22Jan96  	}
//DeadCode MGA 22Jan96 	constant=NULL;
//DeadCode MGA 22Jan96 	address=NULL;
//DeadCode MGA 22Jan96 	offset=NULL;
//DeadCode MGA 22Jan96  }
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddToLinkedList
//Author		Martin Alderton
//Date			Fri 8 Dec 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AddToLinkedList(int argnum,const	SnipLink& insnip)
{
SnipLink*	onesnip=new SnipLink;
	*onesnip=insnip;
 	onesnip->link=NULL;
 	if (SStart[argnum]==NULL)
	{
		SStart[argnum]=onesnip;
	}
	else
		sniplink[argnum]->link=onesnip;

	sniplink[argnum]=onesnip;

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddToLinkedList
//Author		Martin Alderton
//Date			Fri 8 Dec 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AddToLinkedList(int argnum,const ListLink& inlist)
{
ListLink*	onelist=new ListLink;
	*onelist=inlist;
	onelist->link=NULL;
 	if (LStart[argnum]==NULL)
	{
		LStart[argnum]=onelist;
	}
	else
		listlink[argnum]->link=onelist;

	listlink[argnum]=onelist;

}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddToLinkedList
//Author		Martin Alderton
//Date			Thu 18 Jan 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AddToLinkedList(const SeqLink& inseq)
{
SeqLink*	oneseq=new SeqLink;
	*oneseq=inseq;
	oneseq->link=NULL;
 	if (SeqStart==NULL)
	{
		SeqStart=oneseq;
	}
	else
		seqlink->link=oneseq;

	seqlink=oneseq;

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddToLinkedList
//Author		Martin Alderton
//Date			Wed 10 Jan 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AddToLinkedList(const	Constantstruc& inconst)
{
Constantstruc*	oneconst=new Constantstruc;
	*oneconst=inconst;
 	oneconst->link=NULL;
 	if (CStart==NULL)
	{
		CStart=oneconst;
	}
	else
		constant->link=oneconst;

	constant=oneconst;

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddToLinkedList
//Author		Martin Alderton
//Date			Wed 10 Jan 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AddToLinkedList(const	Addressstruc& inaddr)
{
Addressstruc*	oneaddr=new Addressstruc;
	*oneaddr=inaddr;
 	oneaddr->link=NULL;
 	if (AStart==NULL)
	{
		AStart=oneaddr;
	}
	else
		address->link=oneaddr;

	address=oneaddr;

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddToLinkedList
//Author		Martin Alderton
//Date			Wed 10 Jan 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AddToLinkedList(const	Offsetstruc& inoffs)
{
Offsetstruc*	oneoffs=new Offsetstruc;
	*oneoffs=inoffs;
 	oneoffs->link=NULL;
 	if (OStart==NULL)
	{
		OStart=oneoffs;
	}
	else
		offset->link=oneoffs;

	offset=oneoffs;

}


//TempCode MGA 19Dec95 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//TempCode MGA 19Dec95 //Procedure		LinkListCount
//TempCode MGA 19Dec95 //Author		Martin Alderton
//TempCode MGA 19Dec95 //Date			Fri 8 Dec 1995
//TempCode MGA 19Dec95 //
//TempCode MGA 19Dec95 //Description These routines not used in the end. May come in useful though.	
//TempCode MGA 19Dec95 //
//TempCode MGA 19Dec95 //Inputs		
//TempCode MGA 19Dec95 //
//TempCode MGA 19Dec95 //Returns	
//TempCode MGA 19Dec95 //
//TempCode MGA 19Dec95 //------------------------------------------------------------------------------
//TempCode MGA 19Dec95 int SnipLinkListCount(int argnum)
//TempCode MGA 19Dec95 {
//TempCode MGA 19Dec95  	int  SCount;
//TempCode MGA 19Dec95 	SnipLink *ptr;
//TempCode MGA 19Dec95 
//TempCode MGA 19Dec95 	ptr = (SnipLink *)SStart[argnum];
//TempCode MGA 19Dec95 
//TempCode MGA 19Dec95 	for (SCount=0;ptr!=NULL;SCount++)
//TempCode MGA 19Dec95 		ptr=ptr->link;
//TempCode MGA 19Dec95 
//TempCode MGA 19Dec95 	return(SCount);
//TempCode MGA 19Dec95 
//TempCode MGA 19Dec95 }
//TempCode MGA 19Dec95 
//TempCode MGA 19Dec95 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//TempCode MGA 19Dec95 //Procedure		LinkListCount
//TempCode MGA 19Dec95 //Author		Martin Alderton
//TempCode MGA 19Dec95 //Date			Fri 8 Dec 1995
//TempCode MGA 19Dec95 //
//TempCode MGA 19Dec95 //Description	
//TempCode MGA 19Dec95 //
//TempCode MGA 19Dec95 //Inputs		
//TempCode MGA 19Dec95 //
//TempCode MGA 19Dec95 //Returns	
//TempCode MGA 19Dec95 //
//TempCode MGA 19Dec95 //------------------------------------------------------------------------------
//TempCode MGA 19Dec95 int ListLinkListCount(int argnum)
//TempCode MGA 19Dec95 {
//TempCode MGA 19Dec95  	int  LCount;
//TempCode MGA 19Dec95 	ListLink *ptr;
//TempCode MGA 19Dec95 
//TempCode MGA 19Dec95 	ptr = (ListLink *)LStart[argnum];
//TempCode MGA 19Dec95 
//TempCode MGA 19Dec95 	for (LCount=0;ptr!=NULL;LCount++)
//TempCode MGA 19Dec95 		ptr=ptr->link;
//TempCode MGA 19Dec95 
//TempCode MGA 19Dec95 	return(LCount);
//TempCode MGA 19Dec95 
//TempCode MGA 19Dec95 }
//TempCode MGA 19Dec95
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		WriteToFil
//Author		Martin Alderton
//Date			Mon 8 Jan 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void WriteToSnipFil(int inc,int n)
{
	char outstring[40];
	char Let=Letter[inc];
	strcpy(outstring,"");

	strcpy(outstring,"SNIP");
	if (n>9)
		stradd(outstring,'1');
	else
		stradd(outstring,'0');
	stradd(outstring,(char) ((n%10)+'0'));
	stradd(outstring,'_');
	stradd(outstring,Let);
	strcat(outstring,".BIN");

	SnipFileList(outstring);
	numsnipfiles++;

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		WriteToFil
//Author		Martin Alderton
//Date			Mon 8 Jan 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void WriteToListFil(int inc,int n)
{
	char outstring[40];
	char Let=Letter[inc];
//DeadCode JIM 10Jun96 	strcpy(outstring,"");

	strcpy(outstring,"LIST");
	if (n>9)
		stradd(outstring,'1');
	else
		stradd(outstring,'0');
	stradd(outstring,(char) ((n%10)+'0'));
	stradd(outstring,'_');
	stradd(outstring,Let);
	strcat(outstring,".BIN");

	ListFileList(outstring);
	numlistfiles++;


}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Assign
//Author		Martin Alderton
//Date			Thu 7 Dec 1995
//
//Description	Assign Snips and Lists
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Assign()
{

	FILE *fp;
 
	int i;
 	SnipLink *ptr;
 	ListLink *lptr;
	SeqLink	 *Sequenceptr;
 	char name[Array];
	char* string="TextSnip";
	char min[5]="MIN";
	char max[5]="MAX";
	int n=0;
	int inc=0;
	int m=0;
	int finm=0;
 
	if ((fp = fopen(headerfile, "wt"))== NULL)
		{
			fprintf(stderr, "Cannot open file.\n",headerfile);
		}
	do
	{
	 
		ptr=SStart[n];
		inc=0;
	 	basetable[n]=base;

			fprintf(fp,"enum\t%s%d\t{\t%s%d%s\t=%#04x,\n",string,n,string,n,min,base);
 			for (i=0;ptr!=NULL;i++)
 			{
				strcpy(name,ptr->name);

				if (*(ULong*)name!=*(ULong*)"T_UI")
					if (m==0)
					fprintf(fp,"\t%-40s=\t%s%d%s,\n", name,string,n,min);
 					else
					fprintf(fp,"\t%-40s=\t%s%d%s+0x%04x,\n", name,string,n,min,m);

 				ptr=ptr->link;
			
				m++;
				finm++;
				if (finm==256)									//JIM 10Jun96
				{
					base=base+256;
					WriteToSnipFil(inc,n);
					inc++;
					finm=0;
				}
 			}
		fprintf(fp,"\t\t%s%d%s\t=%#04x};\n",string,n,max,base+finm);

		m=0;
		finm=0;
		base=base+256;
		WriteToSnipFil(inc,n);
		n++;

	}while (n<20);

 	string="TextList";
	n=0;

	do
	{
 		lptr=LStart[n];
		inc=0;
		basetable[n+20]=base;

			fprintf(fp,"enum\t%s%d\t{\t%s%d%s\t=%#04x,\n",string,n,string,n,min,base);
 			for (i=0;lptr!=NULL;i++)
 			{
				strcpy(name,lptr->name);

				if (m==0)
				fprintf(fp,"\t%-40s=\t%s%d%s,\n", name,string,n,min);
 				else
				fprintf(fp,"\t%-40s=\t%s%d%s+%#04x,\n", name,string,n,min,m);

 				lptr=lptr->link;
			
				m++;
				finm++;
				if (finm==256)
				{
					base=base+256;
					WriteToListFil(inc,n);
					inc++;
					finm=0;
				}
				
 			}
		fprintf(fp,"\t\t%s%d%s\t=%#04x};\n",string,n,max,base+finm);
		m=0;
		finm=0;
		base=base+256;
		WriteToListFil(inc,n);
		n++;
	
	}while (n<20);


	UIDNamesBase=base;											//JIM 10Jun96
	fprintf(fp,"\nenum\tUIDNamesPage	{TEXTUID_namespage=%#04x};\n\n",base);//JIM 10Jun96
	ListFileList("LIST_UID.BIN");
	base=base+256;												//JIM 10Jun96

 	string="TextSeq";

 	Sequenceptr=SeqStart;
	inc=0;
	basetable[40]=base;

		fprintf(fp,"enum\t%s\t{\t%s%s\t=%#04x,\n",string,string,min,base);
 		for (i=0;Sequenceptr!=NULL;i++)
 		{
			strcpy(name,Sequenceptr->name);

			if (m==0)
			fprintf(fp,"\t%-40s=\t%s%s,\n", name,string,min);
 			else
			fprintf(fp,"\t%-40s=\t%s%s+0x%04x,\n", name,string,min,m);

 			Sequenceptr=Sequenceptr->link;
		
			m++;
			finm++;
			if (finm==256)
			{
				base=base+256;
				inc++;
				finm=0;
			}
			
 		}
	fprintf(fp,"\t\t%s%s\t=%#04x};\n",string,max,base+finm);
//DeadCode JIM 10Jun96 	m=0;
//DeadCode JIM 10Jun96 	finm=0;
	base=base+256;
	fclose(fp);
//TempCode MGA 19Dec95 	ptr=NULL;
//TempCode MGA 19Dec95 	lptr=NULL;
	delete ptr;
	delete lptr;
	delete Sequenceptr;

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetNumber
//Author		Martin Alderton
//Date			Fri 12 Jan 1996
//
//Description   gets first number from a text string	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
int GetNumber(char* text)
{
int num,num1,num2=0;
int j=0;

for(j=0;j<strlen(text);j++)
{
	if ((text[j]>='0')&&(text[j]<='9'))
		if ((text[j+1]>='0')&&(text[j+1]<='9'))
			num2=text[j+1]-'0';
		else if ((text[j]>='0')&&(text[j]<='9'))
			num1=text[j]-'0';
}

num=num1+num2;
return(num);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetOutputFormat
//Author		Martin Alderton
//Date			Fri 12 Jan 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
OutputLine GetOutputFormat(char* test)
{
OutputLine text;
strcpy(text.code,"0");

if (strcmp(test,"MIN")==0)
{
	strcpy(text.code,"OFORM_MIN");
	return(text);
}

if (strcmp(test,"NORM")==0)
{
	strcpy(text.code,"OFORM_NORM");
	return(text);
}

else if (strcmp(test,"NOPRINT")==0)
{
	strcpy(text.code,"OFORM_NO");
	return(text);
}

else if (strcmp(test,"TH")==0) //is this the right code ??
{
	strcpy(text.code,"OFORM_TH");
	return(text);
}

else if (strcmp(test,"SIGN")==0) //is this the right code ??
{
	strcpy(text.code,"OFORM_SIGN");
	return(text);
}

else if (strcmp(test,"ZEROS")==0) 
{
	strcpy(text.code,"OFORM_LZ");
	return(text);
}

else if (strcmp(test,"UNIQUEID")==0 || strcmp(test,"UID")==0)
{
	strcpy(text.code,"ILLEGAL_UNIQUEID");
	return(text);
}

else if ((strcmp(test,"MASK")!=0)&&(strcmp(test,"SH")!=0))
	EmitSysErr("Error in GetOutputFormat module");

return(text);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AssignConstants
//Author		Martin Alderton
//Date			Thu 11 Jan 1996
//
//Description	go through the three linked lists in turn interpreting the input	
//				then  format and output to enum file
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AssignConstants()
{
FILE *file;
char *filename;
int i;
int j;
Constantstruc *conptr;
conptr=CStart;
int timesthrough=0;

	for (i=0;conptr!=NULL;i++)
	{
		concount++;
		conptr=conptr->link;
	}

	do
	{
		conptr=CStart;
		if (concount<=256)
		{
			j=concount;
			concount=concount-j;
		}
		else
		{
			j=256;
			concount=concount-256;
		}
		filename = EnumConstFile;
		if (timesthrough>9)
			stradd(filename,'1');
		else
			stradd(filename,'0');
		stradd(filename,(char) ((timesthrough%10)+'0'));
		strcat(filename,".g");

 
		if ((file=fopen(filename,"wt"))==NULL)
			{
				fprintf (stderr,"Cannot Open enum file %s /n",filename);
			}
		else
			{
				fprintf(file,"TextBlock\tTextBlock_headerc%d\t=\t{TEXTTYPE_Const,0,%d};\n",timesthrough,j);
				fprintf(file,"TextBlock_constants\tTextBlock_instancec%d[]\t=\n",timesthrough);
				fprintf(file,"\t{\n");

				if (conptr)										//DAW 15Jan97
				{		//If there are none then don't make it uncompilable
					for (i=0;conptr!=NULL;i++)
					{
		 				int j=0;
						int num=0;
						OutputLine text;
						char test[10]="";

						if (conptr->format[j]!=NULL)
						{
							while ((conptr->format[j]!=' ')&&(conptr->format[j]!=NULL))
							{
			 					stradd(test,conptr->format[j]);
								j++;					
							};

							text=GetOutputFormat(test);

							if (strcmp(text.code,"ILLEGAL_UNIQUEID")!=0)
							{
								//get number
								num= GetNumber(conptr->format);
								if ((num<0)||(num>16))
									EmitSysErr("Minimum number of digits incorrectly specified 1");
							}

							if (strcmp(text.code,"OFORM_NO")==0)
							{
								num=0;
								strcpy(text.code,"OFORM_TH");
							}
							if (strcmp(text.code,"TH")==0) //is this the right code ??
								num=1;
							if (strcmp(text.code,"SIGN")==0) //is this the right code ??
								num=1;
							if (text.code==NULL)
								strcpy(text.code,"OFORM_NORM");
						}
						else
						{
			 			EmitSysErr("Output Format Information MUST be supplied with a constant");
						}
					 
						if (strcmp(text.code,"ILLEGAL_UNIQUEID")!=0)
						{
							fprintf(file,"\t\t{%d,\t{0,31},{%d,%s}}",conptr->constant,num,text.code);
						}
						else
						{
							fprintf(file,"\t\t{%d,\t{0,ILL_UNIQUEID},{0,OFORM_NORM}}",conptr->constant);
						}
						conptr=conptr->link;
						if (conptr)
							fprintf(file,",\n");
					}
				}else{
					fprintf(file,"\t0");
				}

			fprintf(file,"\n\t};\n\n");

			fclose(file);
			}
			FILE *fp;
			char *fpname;
			fpname=headerfile;
			base=TextIntMIN; //set base value to 0xD000 MGA 24Jan96

			if ((fp=fopen(fpname,"at"))==NULL)
				{
					fprintf (stderr,"Cannot Open headerfile file /n");
				}
			else
				{
					//constant enum code to go in below

					fprintf(file,"enum\tTextConst\t{\tTextConstMIN=%d,\n",base);
					conptr=CStart;
					for (i=0;conptr!=NULL;i++)
					{
		 				fprintf(file,"\t\t%s=TextConstMIN+0x%04x,\n",conptr->name,i);
						conptr=conptr->link;
					}
					fprintf(file,"\t\tTextConstMAX=%d\t};\n",(base+i));
				}
				fclose(fp);
		
		if (timesthrough==0)
			basetable[41]=base;

		base=base+256;
		timesthrough++;
	}while (concount!=0);
	delete (conptr);

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetInputFormat
//Author		Martin Alderton
//Date			Fri 12 Jan 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
InputFormat GetInputFormat(char* text)
{
InputFormat retval;
retval.mask=0;
retval.shift=0;
strcpy(retval.maskword,"");
strcpy(retval.shiftword,"");
char test[10]="";
int j = 0;

 while (text[j]>' ')
 {
 		stradd(test,text[j]);
 	j++;					
 };
	
	if (strcmp(test,"MASK")==0) 
	{
		
		j++;
		strcpy(test,"");

		while (text[j]>' ')
		{
			stradd(test,text[j]);
			j++;
		}


		//get number

		if ((test[0]>='0')&&(test[0]<='9'))
			retval.mask=atoi(test)-1;
		else
		{
			if ((strcmp(test,"BYTE")==0)||(strcmp(test,"WORD")==0)||(strcmp(test,"LONG")==0))
				strcpy(retval.maskword,test);
			else
				EmitSysErr("Mask incorrectly specified");
		}
		strcpy(test,"");
		j++;
		while (text[j]>' ')
		{
				stradd(test,text[j]);
			j++;					
		};
		if (strcmp(test,"SH")!=0)
			EmitSysErr("No Shift value present !");
		else
		{
			j++;
			strcpy(test,"");

			while (text[j]>' ')
			{
				stradd(test,text[j]);
				j++;
			}

			//get number
			if ((test[0]>='0')&&(test[0]<='9'))
				retval.shift=atoi(test);
			else
			{
				if ((strcmp(test,"HIGH")==0)||(strcmp(test,"LOW")==0))
					strcpy(retval.shiftword,test);
				else
					EmitSysErr("Shift incorrectly specified");
			}
		}
		if (strcmp(retval.maskword,"BYTE")==0)
			retval.mask=7;
		if (strcmp(retval.maskword,"WORD")==0)
			retval.mask=15;
		if (strcmp(retval.maskword,"LONG")==0)
			retval.mask=31;
		if (strcmp(retval.shiftword,"LOW")==0)
			retval.shift=0;
		
		if ((strcmp(retval.shiftword,"HIGH")==0)
			&&(strcmp(retval.maskword,"BYTE")==0))
			retval.shift=8;
		else if ((strcmp(retval.shiftword,"HIGH")==0)
			&&(strcmp(retval.maskword,"WORD")==0))
			retval.shift=16;
		else if (strcmp(retval.shiftword,"HIGH")==0)
			EmitSysErr("No valid value fo HIGH");

	return (retval);
	}
	else if (strcmp(test,"SH")==0) 
	{
		j++;
		strcpy(test,"");

		while (text[j]>' ')
		{
			stradd(test,text[j]);
			j++;
		}
		//get number
		if ((test[0]>='0')&&(test[0]<='9'))
			retval.shift=atoi(test);
		else
		{
			if ((strcmp(test,"HIGH")==0)||(strcmp(test,"LOW")==0))
				strcpy(retval.shiftword,test);
			else
				EmitSysErr("Shift incorrectly specified");
		}
		strcpy(test,"");
		j++;
		while (text[j]>' ')
		{
				stradd(test,text[j]);
			j++;					
		};
		if (strcmp(test,"MASK")!=0)
			EmitSysErr("No Mask value present !");
		else
		{
			j++;
			strcpy(test,"");


			while (text[j]>' ')
			{											   	
				stradd(test,text[j]);					   	
				j++;									   	
			}											   	
		

			//get number
			if ((test[0]>='0')&&(test[0]<='9'))
			{
				retval.mask=atoi(test)-1;
			}
			else
			{
				if ((strcmp(test,"BYTE")==0)||(strcmp(test,"WORD")==0)||(strcmp(test,"LONG")==0))
					strcpy(retval.maskword,test);
				else
					EmitSysErr("Mask incorrectly specified,got %s instead",test);
			}
		}
		if (strcmp(retval.maskword,"BYTE")==0)
			retval.mask=7;
		if (strcmp(retval.maskword,"WORD")==0)
			retval.mask=15;
		if (strcmp(retval.maskword,"LONG")==0)
			retval.mask=31;
		if (strcmp(retval.shiftword,"LOW")==0)
			retval.shift=0;
		
		if ((strcmp(retval.shiftword,"HIGH")==0)
			&&(strcmp(retval.maskword,"BYTE")==0))
			retval.shift=8;
		else if ((strcmp(retval.shiftword,"HIGH")==0)
			&&(strcmp(retval.maskword,"WORD")==0))
			retval.shift=16;
		else if (strcmp(retval.shiftword,"HIGH")==0)
			EmitSysErr("No valid value fo HIGH");

	return (retval);
	}
	else if ((strcmp(test,"SIGN")!=0)&&(strcmp(test,"TH")!=0)
		&&(strcmp(test,"MIN")!=0)&&(strcmp(test,"NOPRINT")!=0)
			&&(strcmp(test,"NORM")!=0)&&(strcmp(test,"ZEROS")!=0))
				EmitSysErr("Error in GetInputFortmat Module");



return (retval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TestForSpecial
//Author		Martin Alderton
//Date			Mon 15 Jan 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
InputFormat TestForSpecial(InputFormat InputF)
{
 
	if (InputF.shift !=31)
	{
		EmitSysErr("Invalid values for shift & mask !");
	}
	else
	{
	 	if (InputF.mask==1)
		{
			strcpy(InputF.special,"ILL_TEXTREF");
		}

	 	else if (InputF.mask==2)
		{
 			strcpy(InputF.special,"ILL_OFFSET"); //is that he right code ?
		}

	 	else if (InputF.mask==10)
		{
			strcpy(InputF.special,"ILL_INDB4");
		}

	 	else if (InputF.mask==11)
		{
			strcpy(InputF.special,"ILL_INDAFTER");
		}

		else
		{
			EmitSysErr("Illegal combination of values for shift & mask !");
		}

	}
	return(InputF);

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AssignAddresses
//Author		Martin Alderton
//Date			Thu 11 Jan 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AssignAddresses()
{
FILE *file;
char *filename;
int i;
int j;
Addressstruc *addptr;
addptr=AStart;
int timesthrough=0;
 

	for (i=0;addptr!=NULL;i++)
	{
		addcount++;
		addptr=addptr->link;
	}


	do
	{
		addptr=AStart;
		if (addcount<=256)
		{
			j=addcount;
			addcount=addcount-j;
		}
		else
		{
			j=256;
			addcount=addcount-256;
		}
		filename = EnumAddrFile;
		if (timesthrough>9)
			stradd(filename,'1');
		else
			stradd(filename,'0');
		stradd(filename,(char) ((timesthrough%10)+'0'));
		strcat(filename,".g");


		if ((file=fopen(filename,"wt"))==NULL)
			{
				fprintf (stderr,"Cannot Open enum file %s /n",filename);
			}
		else
			{
				fprintf(file,"TextBlock\tTextBlock_headera%d\t=\t{TEXTTYPE_Addr,0,%d};\n",timesthrough,j);
				fprintf(file,"TextBlock_addresses\tTextBlock_instancea%d[]\t=\n",timesthrough);
				fprintf(file,"\t{\n");

				if (addptr)										//DAW 15Jan97
				{		//If there are none then don't make it uncompilable
					for (i=0;addptr!=NULL;i++)
					{
		 				int j1=0;
						int mask1=31;
						int shift1=0;
		 				int j2=0;
						int mask2=31;
						int shift2=0;
						int num1=0;
						int num2=0;
						char maskword1[30]="";
						char maskword2[30]="";
						OutputLine text1;
						char test1[10]="";  	//need to allow for the possibility of
						OutputLine text2;			//output formatting info coming before
						char test2[10]="";		//input data, and vice-versa
						InputFormat InputF;

						strcpy(text1.code,"0");
						strcpy(text2.code,"0");


 						if (	(addptr->address[0]!='[')
							&&	(addptr->address[0]!='"')
							&&	(addptr->address[0]!='\'')	)
						{
							if (addptr->format1[j1]!=NULL)
 							{
 								while ((addptr->format1[j1]!=' ')&&(addptr->format1[j1]!=NULL))
 								{
 				 					stradd(test1,addptr->format1[j1]);
 									j1++;					
 								};
								text1=GetOutputFormat(test1);
						
								if (strcmp(text1.code,"ILLEGAL_UNIQUEID")!=0)
								{
									//get number
									num1= GetNumber(addptr->format1);
									if ((num1<0)||(num1>16))
										EmitSysErr("Minimum number of digits incorrectly specified 2");
							
								}

								if (strcmp(text1.code,"OFORM_NO")==0)
								{
									num1=0;
									strcpy(text1.code,"OFORM_TH");
								}
								if (strcmp(text1.code,"TH")==0) //is this the right code ??
									num1=1;
								if (strcmp(text1.code,"SIGN")==0) //is this the right code ??
									num1=1;

								//test for input formatting
								if (strcmp(text1.code,"0")==0)
								{
									InputF=GetInputFormat(addptr->format1);
										mask1=InputF.mask;
										shift1=InputF.shift;
									num1=0;
								}
								if (strcmp(text1.code,"ILLEGAL_UNIQUEID")==0)
								{
							 		strcpy(maskword1,"ILL_UNIQUEID");
									shift1=31;
									strcpy(text1.code,"OFORM_NORM");
								}

 							}

 							if (addptr->format2[j2]!=NULL)
 							{
 								while ((addptr->format2[j2]!=' ')&&(addptr->format2[j2]!=NULL))
 								{
 				 					stradd(test2,addptr->format2[j2]);
 									j2++;					
 								};
								text2=GetOutputFormat(test2);
						
								if (strcmp(text2.code,"ILLEGAL_UNIQUEID")!=0)
								{

									//get number
									num2= GetNumber(addptr->format2);
									if ((num2<0)||(num2>16))
										EmitSysErr("Minimum number of digits incorrectly specified 3");
								}

								if (strcmp(text2.code,"OFORM_NO")==0)
								{
									num2=0;
									strcpy(text2.code,"OFORM_TH");
								}
								if (strcmp(text2.code,"TH")==0) //is this the right code ??
									num2=1;
								if (strcmp(text2.code,"SIGN")==0) //is this the right code ??
									num2=1;
					
								//test for input formatting
								if (strcmp(text2.code,"0")==0)
								{
									InputF=GetInputFormat(addptr->format2);
									mask2=InputF.mask;
									shift2=InputF.shift;

									num2=0;
								}
								if (strcmp(text2.code,"ILLEGAL_UNIQUEID")==0)
								{
							 		strcpy(maskword2,"ILL_UNIQUEID");
									shift2=31;
									strcpy(text2.code,"OFORM_NORM");
								}

 							}
						}
						else if (addptr->address[0]=='"'||addptr->address[0]=='\'')
						{
							shift1=31;
							mask1=1;
						}
						else if (addptr->address[0]=='[')
						{
			 				shift1=31;
							int k;
							k = strlen(addptr->address);
							if (addptr->address[k-1]=='+')
								mask1=11;
							else if ((addptr->address[k-1]==']')&&(addptr->address[k-2]=='+'))
								mask1=10;
							else
					 			EmitSysErr("Address illegally defined");

							if (addptr->format1[j1]!=NULL)
 							{
 								while ((addptr->format1[j1]!=' ')&&(addptr->format1[j1]!=NULL))
 								{
 				 					stradd(test1,addptr->format1[j1]);
 									j1++;					
 								};
								text1=GetOutputFormat(test1);

								//get number
								num1= GetNumber(addptr->format1);
								if ((num1<0)||(num1>16))
									EmitSysErr("Minimum number of digits incorrectly specified 4");

								if (strcmp(text1.code,"OFORM_NO")==0)
								{
									num1=0;
									strcpy(text1.code,"OFORM_TH");
								}
								if (strcmp(text1.code,"TH")==0) //is this the right code ??
									num1=1;
								if (strcmp(text1.code,"SIGN")==0) //is this the right code ??
									num1=1;

 							}

						}

						//need to choose which mask/shift/num/texts we are going to use.

						UWord shift;
						UWord mask;
						char maskword[10]="";
						UWord num;
						char text[20];

						if (shift1!=0)
							shift=(UWord)shift1;
						else
							shift=(UWord)shift2;

						
						if ((strcmp(maskword1,"")==0)&&(strcmp(maskword2,"")==0))
						{
							if (mask1!=31)
								mask=(UWord)mask1;
							else
								mask=(UWord)mask2;
						}
						else if(strcmp(maskword1,"")==0)
							strcpy(maskword,maskword2);
						else
							strcpy(maskword,maskword1);

						if (num2!=0)
							num=(UWord)num2;
						else
							num=(UWord)num1;

						if (strcmp(text2.code,"0")!=0)
							strcpy(text,text2.code);
						else if (strcmp(text1.code,"0")!=0)
							strcpy(text,text1.code);
						else
							strcpy(text,"OFORM_NORM");
						
						strcpy(InputF.special,"");

						if (strcmp(maskword,"")==0)
						{
							InputF.shift=shift;
							InputF.mask=mask;

							//have to allow for illegal(special) shift/mask codes
							if (shift+mask>=32)
							{
								InputF=TestForSpecial(InputF);	
							}
						}

						char addresstext[30]="";
						int m=0;
						for (m=0;m<strlen(addptr->address);m++)
						{
			 				if (	(addptr->address[m]!='[')
								&&	(addptr->address[m]!='+')
								&&	(addptr->address[m]!=']')
								&&	(addptr->address[m]!='"')
								&&	(addptr->address[m]!='\'')
								)
								stradd(addresstext,addptr->address[m]);
						}
			
						if (strcmp(InputF.special,"")!=0)
						{
   							fprintf(file,"\t\t{&%s,{%d,%s},{%d,%s}}",addresstext,shift,InputF.special,num,text);
						}
					
						else if (strcmp(maskword,"")!=0)
						{
   							fprintf(file,"\t\t{&%s,{%d,%s},{%d,%s}}",addresstext,shift,maskword,num,text);
						}
					
						else
						{
   							fprintf(file,"\t\t{&%s,{%d,%d},{%d,%s}}",addresstext,shift,mask,num,text);
  						}
						addptr=addptr->link;
  						if (addptr)
  							fprintf(file,",\n");
  					}
				}else{
					fprintf(file,"\t0");
				}
  				fprintf(file,"\n\t};\n\n");
			}
			fclose(file);
  
  				// interpret and print text here (see above)
			FILE *fp;
			char *fpname;
			fpname=headerfile;
			
			if ((fp=fopen(fpname,"at"))==NULL)
				{
					fprintf (stderr,"Cannot Open header file /n");
				}
			else
				{
  					//constant enum code to go in below
  
  					fprintf(file,"enum\tTextAddr\t{\tTextAddrMIN=%d,\n",base);
  					addptr=AStart;
  					for (i=0;addptr!=NULL;i++)
  					{
  		 				fprintf(file,"\t\t%s=TextAddrMIN+0x%04x,\n",addptr->name,i);
  						addptr=addptr->link;
					}
  					fprintf(file,"\t\tTextAddrMAX=%d\t};\n",(base+i));

				}
				fclose(fp);
		
		if (timesthrough==0)
			basetable[42]=base;

		base=base+256;
		timesthrough++;
	}while (addcount!=0);
	delete (addptr);


}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AssignOffsets
//Author		Martin Alderton
//Date			Thu 11 Jan 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AssignOffsets()
{
FILE *file;
char *filename;
int i;
int j;
Offsetstruc *offptr;
offptr=OStart;
int timesthrough=0;
 
	for (i=0;offptr!=NULL;i++)
	{
		offcount++;
		offptr=offptr->link;
	}


	do
	{
		offptr=OStart;
		if (offcount<=256)
		{
			j=offcount;
			offcount=offcount-j;
		}
		else
		{
			j=256;
			offcount=offcount-256;
		}
		filename = EnumOffsFile;
		if (timesthrough>9)
			stradd(filename,'1');
		else
			stradd(filename,'0');
		stradd(filename,(char) ((timesthrough%10)+'0'));
		strcat(filename,".g");


		if ((file=fopen(filename,"wt"))==NULL)
			{
				fprintf (stderr,"Cannot Open enum file %s /n",filename);
			}
		else
			{
				fprintf(file,"TextBlock\tTextBlock_headero%d\t=\t{TEXTTYPE_Offset,0,%d};\n",timesthrough,j);
				fprintf(file,"TextBlock_offsets\tTextBlock_instance%d[]\t=\n",timesthrough);
				fprintf(file,"\t{\n");

				if (offptr)										//DAW 15Jan97
				{		//If there are none then don't make it uncompilable
					for (i=0;offptr!=NULL;i++)
					{
		 				int j1=0;
						int mask1=31;
						int shift1=0;
		 				int j2=0;
						int mask2=31;
						int shift2=0;
						int num1=0;
						int num2=0;
						char maskword1[30]="";
						char maskword2[30]="";
						OutputLine text1;
						char test1[10]="";  //need to allow for the possibility of
						OutputLine text2;		//output formatting info coming before
						char test2[10]="";	//input data, and vice-versa
						InputFormat InputF;

						strcpy(text1.code,"0");
						strcpy(text2.code,"0");
 			
						if (	(offptr->mask_shift1[1]!='[')
							&&	(offptr->mask_shift1[1]!='"')
							&&	(offptr->mask_shift1[1]!='\'')	)
						{

 							if (offptr->format1[j1]!=NULL)
 							{
 								while ((offptr->format1[j1]!=' ')&&(offptr->format1[j1]!=NULL))
 								{
 				 					stradd(test1,offptr->format1[j1]);
 									j1++;					
 								};
								text1=GetOutputFormat(test1);
						
								if (strcmp(text1.code,"ILLEGAL_UNIQUEID")!=0)
								{

									//get number
									num1= GetNumber(offptr->format1);
									if ((num1<0)||(num1>16))
										EmitSysErr("Minimum number of digits incorrectly specified 5");
								}

								if (strcmp(text1.code,"OFORM_NO")==0)
								{
									num1=0;
									strcpy(text1.code,"OFORM_TH");
								}
								if (strcmp(text1.code,"TH")==0) //is this the right code ??
									num1=1;
								if (strcmp(text1.code,"SIGN")==0) //is this the right code ??
									num1=1;
					
								//test for input formatting
								if (strcmp(text1.code,"0")==0)
								{
									InputF=GetInputFormat(offptr->format1);
										mask1=InputF.mask;
										shift1=InputF.shift;
									num1=0;
								}
								if (strcmp(text1.code,"ILLEGAL_UNIQUEID")==0)
								{
							 		strcpy(maskword1,"ILL_UNIQUEID");
									shift1=31;
									strcpy(text1.code,"OFORM_NORM");
								}

							}

 							if (offptr->format2[j2]!=NULL)
 							{
 								while ((offptr->format2[j2]!=' ')&&(offptr->format2[j2]!=NULL))
 								{
 				 					stradd(test2,offptr->format2[j2]);
 									j2++;					
 								};
								text2=GetOutputFormat(test2);

								if (strcmp(text1.code,"ILLEGAL_UNIQUEID")!=0)
								{

									//get number
									num1= GetNumber(offptr->format2);
									if ((num2<0)||(num2>16))
										EmitSysErr("Minimum number of digits incorrectly specified 6");
								}

								if (strcmp(text2.code,"OFORM_NO")==0)
								{
									num2=0;
									strcpy(text2.code,"OFORM_TH");
								}
								if (strcmp(text2.code,"TH")==0) //is this the right code ??
									num2=1;
								if (strcmp(text2.code,"SIGN")==0) //is this the right code ??
									num2=1;
					
								//test for input formatting
								if (strcmp(text2.code,"0")==0)
								{
									InputF=GetInputFormat(offptr->format2);
									mask2=InputF.mask;
									shift2=InputF.shift;
									num2=0;
								}
								if (strcmp(text2.code,"ILLEGAL_UNIQUEID")==0)
								{
							 		strcpy(maskword2,"ILL_UNIQUEID");
									shift2=31;
									strcpy(text2.code,"OFORM_NORM");
								}

							}
						}
						else if (offptr->mask_shift1[1]=='"' || offptr->mask_shift1[1]=='\'')
						{
							shift1=31;
							mask1=1;
						}									
						else if (offptr->mask_shift1[1]=='[')
						{
			 				shift1=31;
							int k;
							k = strlen(offptr->mask_shift2);
							if (offptr->mask_shift2[k-1]=='+')
								mask1=11;
							else if ((offptr->mask_shift2[k-1]==']')&&(offptr->mask_shift2[k-2]=='+'))
								mask1=10;
							else
					 			EmitSysErr("Offset illegally defined");

							if (offptr->format1[j1]!=NULL)
 							{
 								while ((offptr->format1[j1]!=' ')&&(offptr->format1[j1]!=NULL))
 								{
 				 					stradd(test1,offptr->format1[j1]);
 									j1++;					
 								};
								text1=GetOutputFormat(test1);

								//get number
								num1= GetNumber(offptr->format1);
								if ((num1<0)||(num1>16))
									EmitSysErr("Minimum number of digits incorrectly specified 7");

								if (strcmp(text1.code,"OFORM_NO")==0)
								{
									num1=0;
									strcpy(text1.code,"OFORM_TH");
								}
								if (strcmp(text1.code,"TH")==0) //is this the right code ??
									num1=1;
								if (strcmp(text1.code,"SIGN")==0) //is this the right code ??
									num1=1;

 							}

			 	

						}
						//need to choose which mask/shift/num/texts we are going to use.

						UWord shift;
						UWord mask;
						char maskword[10]="";
						UWord num;
						char text[20];

						if (shift2!=0)
							shift=(UWord)shift2;
						else
							shift=(UWord)shift1;
						
						if ((strcmp(maskword1,"")==0)&&(strcmp(maskword2,"")==0))
						{
							if (mask2!=31)
								mask=(UWord)mask2;
							else
								mask=(UWord)mask1;
						}
						else if(strcmp(maskword1,"")==0)
							strcpy(maskword,maskword2);
						else
							strcpy(maskword,maskword1);

						if (num2!=0)
							num=(UWord)num2;
						else
							num=(UWord)num1;

						if (strcmp(text2.code,"0")!=0)
							strcpy(text,text2.code);
						else if (strcmp(text1.code,"0")!=0)
							strcpy(text,text1.code);
						else
							strcpy(text,"OFORM_NORM");
					
						strcpy(InputF.special,"");

						if (strcmp(maskword,"")==0)
						{

							InputF.shift=shift;
							InputF.mask=mask;

							//have to allow for illegal(special) shift/mask codes
							if (shift+mask>=32)
							{
								InputF=TestForSpecial(InputF);	

							}
						}

						char offsettext1[30]="";
						int m=0;
						for (m=0;m<strlen(offptr->mask_shift1);m++)
						{
			 				if (	(offptr->mask_shift1[m]!='[')
								&&	(offptr->mask_shift1[m]!='+')
								&&	(offptr->mask_shift1[m]!='"')
								&&	(offptr->mask_shift1[m]!='\'')
								&&	(offptr->mask_shift1[m]!=']')	)//RDH 08Feb96
								stradd(offsettext1,offptr->mask_shift1[m]);
						}
						char offsettext2[30]="";
						int p=0;
						for (p=0;p<strlen(offptr->mask_shift2);p++)
						{
			 				if (	(offptr->mask_shift2[p]!='[')
								&&	(offptr->mask_shift2[p]!='+')
								&&	(offptr->mask_shift2[p]!='"')
								&&	(offptr->mask_shift2[p]!='\'')
								&&	(offptr->mask_shift2[p]!=']')	)//RDH 08Feb96
								stradd(offsettext2,offptr->mask_shift2[p]);
						}

						if (strcmp(InputF.special,"")!=0)
						{
   							fprintf(file,"\t\t{OFFSETCAST\t(%s,%s),{%d,%s},{%d,%s}}",offsettext1,offsettext2,shift,InputF.special,num,text);
						}
						else if (strcmp(maskword,"")!=0)
						{
   							fprintf(file,"\t\t{OFFSETCAST\t(%s,%s),{%d,%s},{%d,%s}}",offsettext1,offsettext2,shift,maskword,num,text);
						}

						else
						{
   							fprintf(file,"\t\t{OFFSETCAST\t(%s,%s),{%d,%d},{%d,%s}}",offsettext1,offsettext2,shift,mask,num,text);
  						}
						offptr=offptr->link;
  						if (offptr)
  							fprintf(file,",\n");
  					}
				}else{
					fprintf(file,"\t0");
				}
  				fprintf(file,"\n\t};\n\n");
  
  				// interpret and print text here (see above)
			fclose(file);
			}
			FILE *fp;
			char *fpname;
			fpname=headerfile;
			
			if ((fp=fopen(fpname,"at"))==NULL)
				{
					fprintf (stderr,"Cannot Open headerfile file /n");
				}
			else
				{
  					//constant enum code to go in below
  
  					fprintf(file,"enum\tTextOffset\t{\tTextOffsetMIN=%d,\n",base);
  					offptr=OStart;
  					for (i=0;offptr!=NULL;i++)
  					{
  		 				fprintf(file,"\t\t%s=TextOffsetMIN+0x%04x,\n",offptr->name,i);
  						offptr=offptr->link;
					}
  					fprintf(file,"\t\tTextOffsetMAX=%d\t};\n",(base+i));

				}
			fclose(fp);
			
		if (timesthrough==0)
			basetable[43]=base;

	base=base+256;
	timesthrough++;
	}while (offcount!=0);
	delete (offptr);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SaveBlock
//Author		Martin Alderton
//Date			Fri 8 Dec 1995
//
//Description	Save completed blocks to SNIPnn_x.BIN
//
//Inputs		Number of Arguments (int) and signifying letter (char)		
//															(now an int)
//Returns	
//
//------------------------------------------------------------------------------
void SaveBlock(int argnum,int inc,TextSnipBlock *snipblock)
{
FILE *fred;
char filestring[62];
char Let=Letter[inc];

//DeadCode MGA 19Dec95 	strcpy((char *)filestring,(char *)dirstring);
//DeadCode MGA 19Dec95 	strcat((char *)filestring,(char *)"SNIP");
//DeadCode MGA 19Dec95 	strcat((char *)filestring,(char *)argnum);
//DeadCode MGA 19Dec95 	strcat((char *)filestring,(char *)"_");
//DeadCode MGA 19Dec95 	strcat((char *)filestring,(char *)inc);
//DeadCode MGA 19Dec95 	strcat((char *)filestring,(char *)".BIN");


	strcpy(filestring,dirstring);
	strcat(filestring,"SNIP");
	if (argnum>9)
		stradd(filestring,'1');
	else
		stradd(filestring,'0');
	stradd(filestring,(char) ((argnum%10)+'0'));
	stradd(filestring,'_');
	stradd(filestring,Let);
	strcat(filestring,".BIN");

	fred= fopen(filestring,"wb");

	if (fred != NULL)
	{
		int	filesize=sizeof(TextSnipBlock)
					+snipblock->textstarters[snipblock->lastelement+1];
		fwrite(snipblock,filesize,1,fred); //you can't do that, surely !
		delete [] ((char*) snipblock);
		fclose(fred);

	}
	numfiles++;


}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SaveBlock
//Author		Martin Alderton
//Date			Mon 11 Dec 1995
//
//Description	Save completed blocks to LISTnn_x.BIN
//
//Inputs		Number of Arguments (int) and signifying letter (char)		
//																(now an int)
//Returns	
//
//------------------------------------------------------------------------------
void SaveBlock(int argnum,int inc,TextListBlock *listblock)
{
FILE *fp;
char filestring[62];
char Let=Letter[inc];

//DeadCode MGA 19Dec95 	strcpy((char *)filestring,(char *)dirstring);
//DeadCode MGA 19Dec95 	strcat((char *)filestring,(char *)"LIST");
//DeadCode MGA 19Dec95 	strcat((char *)filestring,(char *)argnum);
//DeadCode MGA 19Dec95 	strcat((char *)filestring,(char *)"_");
//DeadCode MGA 19Dec95 	strcat((char *)filestring,(char *)inc);
//DeadCode MGA 19Dec95 	strcat((char *)filestring,(char *)".BIN");


	strcpy(filestring,dirstring);
	strcat(filestring,"LIST");
	if (argnum>9)
		stradd(filestring,'1');
	else
		stradd(filestring,'0');
	stradd(filestring,(char) ((argnum%10)+'0'));
	stradd(filestring,'_');
	stradd(filestring,Let);
	strcat(filestring,".BIN");

	fp= fopen(filestring,"wb");

	if (fp != NULL)
	{
		int	size=sizeof(TextListBlock)
				+2*listblock->lastelement*listblock->listentries
				+2*listblock->listentries;
		fwrite(listblock,size,1,fp); //you can't do that, surely !
		delete [] ((char*) listblock);
		fclose(fp);
		numfiles++;

 	}

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SaveBlock
//Author		Martin Alderton
//Date			Fri 19 Jan 1996
//
//Description	Save SEQuences in blocks of 256.
//
//Inputs		an int corresponding to the files signifying letter		
//
//Returns		saves a block to SEQ_x.BIN	
//
//------------------------------------------------------------------------------
void SaveBlock(int inc,TextSeqBlock *seqblock,int r)			//RDH 08Feb96
//DeadCode RDH 29Feb96 void SaveBlock(int inc,TextSeqBlock *seqblock,int seqindex)
{
FILE *fp;
char filestring[62];
char littlefilestring[15];
char Let=Letter[inc];

	strcpy(filestring,dirstring);
	strcat(filestring,"SEQ");
	strcpy(littlefilestring,"SEQ");
	stradd(filestring,'_');
	stradd(littlefilestring,'_');
	stradd(filestring,Let);
	stradd(littlefilestring,Let);
	strcat(filestring,".BIN");
	strcat(littlefilestring,".BIN");

	SeqFileList(littlefilestring);
	numseqfiles++;

	fp= fopen(filestring,"wb");

	if (fp != NULL)
	{

		int	filesize=sizeof(TextSeqBlock)+sizeof(TextRef)*(r-1);
//DeadCode RDH 08Feb96 		int filesize=sizeof(TextSeqBlock)+(2*((sizeof(TextRef)))
//DeadCode RDH 08Feb96 			*(2*(seqblock->lastelement-1)))+((seqindex)*sizeof(UWord))
//DeadCode RDH 08Feb96 				-(3*sizeof(UByte))-(2*sizeof(UWord))-(sizeof(TextRef));
		fwrite(seqblock,filesize,1,fp); 
		delete [] ((char*) seqblock);
		fclose(fp);

	}

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		getsnipnum
//Author		Martin Alderton
//Date			Wed 20 Dec 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
UWord	getsnipnumnoerr(string	tmpstrsrc)
{
SnipLink*	finder=SStart[0];
UWord	counter=0;
	while (finder)
	{
		if (strcmp(finder->name,tmpstrsrc)==0)
			return(counter);
		finder=finder->link;
		counter++;
	}
	return(0xFFFF);
}

UWord	getsnipnum(string	tmpstrsrc)
{
	UWord	counter=getsnipnumnoerr(tmpstrsrc);
	if (counter==0xffff)
		EmitSysErr("Couldn't find %s in snip0 list!",tmpstrsrc);
	return(counter);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetEquate
//Author		Martin Alderton
//Date			Mon 22 Jan 1996
//
//Description	just like above but checks through all snip,lists & ints	
//				therefore it's a much more long winded process.
//Inputs		
//
//Returns		the equate number of the text input plus it's base value	
//
//------------------------------------------------------------------------------
UWord GetEquate(string text)
{

	UWord retval=0;
	int j=0;
	int n;
	SnipLink* Sfinder;
	ListLink* Lfinder;
	SeqLink* Seqfinder;
	Constantstruc* Cfinder;
	Addressstruc* Afinder;
	Offsetstruc* Ofinder;
	UWord counter=0;


	for (n=0;n<20;n++)
	{
		Sfinder=SStart[n];
		counter=0;
		while (Sfinder)
		{
			if (strcmp(Sfinder->name,text)==0)
			{
				retval=counter+basetable[j];
				return(retval);
			}
			Sfinder=Sfinder->link;
			counter++;
		}
		j++;
	}
	for (n=0;n<20;n++)
	{
		Lfinder=LStart[n];
		counter=0;
		while (Lfinder)
		{
			if (strcmp(Lfinder->name,text)==0)
			{
				retval=counter+basetable[j];
				return(retval);
			}
			Lfinder=Lfinder->link;
			counter++;
		}
		j++;
	}
	
	Seqfinder=SeqStart;
	counter=0;
	while (Seqfinder)
	{
		if (strcmp(Seqfinder->name,text)==0)
		{
			retval=counter+basetable[j];
			return(retval);
		}
		Seqfinder=Seqfinder->link;
		counter++;
	}
	j++;

	Cfinder=CStart;
	counter=0;
	while (Cfinder)
	{
		if (strcmp(Cfinder->name,text)==0)
		{
			retval=counter+basetable[j];
			return(retval);
		}
		Cfinder=Cfinder->link;
		counter++;
	}
	j++;
	
	Afinder=AStart;
	counter=0;
	while (Afinder)
	{
		if (strcmp(Afinder->name,text)==0)
		{
			retval=counter+basetable[j];
			return(retval);
		}
		Afinder=Afinder->link;
		counter++;
	}
	j++;

	Ofinder=OStart;
	counter=0;
	while (Ofinder)
	{
		if (strcmp(Ofinder->name,text)==0)
		{
			retval=counter+basetable[j];
			return(retval);
		}
		Ofinder=Ofinder->link;
		counter++;
	}

	EmitSysErr("Couldn't find %s in any list!",text);
	return(0xFFFF);

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CheckForError
//Author		Martin Alderton
//Date			Tue 23 Jan 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool CheckForError(string temp)
{
	Bool foundagain=TRUE;
//TempCode MGA 05Feb96 	int l;
//TempCode MGA 05Feb96 
//TempCode MGA 05Feb96 		if (strncmp(temp,"TEXT",4)==0)
//TempCode MGA 05Feb96 		{
//TempCode MGA 05Feb96    
//TempCode MGA 05Feb96 			foundagain = FALSE;
//TempCode MGA 05Feb96 			for (l=0;l<20;l++)
//TempCode MGA 05Feb96 			{
//TempCode MGA 05Feb96 				snipptr=SStart[l];
//TempCode MGA 05Feb96 				while (snipptr!=NULL)
//TempCode MGA 05Feb96 				{
//TempCode MGA 05Feb96 					if (strcmp(temp,snipptr->name)==0)
//TempCode MGA 05Feb96 					{
//TempCode MGA 05Feb96 //TempCode MGA 23Jan96 						lfound =l;
//TempCode MGA 05Feb96 						foundagain =TRUE;
//TempCode MGA 05Feb96 					}
//TempCode MGA 05Feb96 					snipptr=snipptr->link;
//TempCode MGA 05Feb96 				}
//TempCode MGA 05Feb96 			}
//TempCode MGA 05Feb96 			if (foundagain==FALSE)
//TempCode MGA 05Feb96 			{
//TempCode MGA 05Feb96 				EmitSysErr("TextSnip not found by Sequence error checking module");
//TempCode MGA 05Feb96 			}
//TempCode MGA 05Feb96 		}
//TempCode MGA 05Feb96 		else if (strncmp(temp,"LIST",4)==0)
//TempCode MGA 05Feb96 		{
//TempCode MGA 05Feb96 			foundagain = FALSE;
//TempCode MGA 05Feb96 			for (l=0;l<20;l++)
//TempCode MGA 05Feb96 			{
//TempCode MGA 05Feb96 				listptr=LStart[l];
//TempCode MGA 05Feb96 				while (listptr!=NULL)
//TempCode MGA 05Feb96 				{
//TempCode MGA 05Feb96 					if (strcmp(temp,listptr->name)==0)
//TempCode MGA 05Feb96 					{
//TempCode MGA 05Feb96 //TempCode MGA 23Jan96 						lfound =l;
//TempCode MGA 05Feb96 						foundagain =TRUE;
//TempCode MGA 05Feb96 					}
//TempCode MGA 05Feb96 					listptr=listptr->link;
//TempCode MGA 05Feb96 				}
//TempCode MGA 05Feb96 			}
//TempCode MGA 05Feb96 			if (foundagain==FALSE)
//TempCode MGA 05Feb96 			{
//TempCode MGA 05Feb96 				EmitSysErr("TextList not found by Sequence error checking module");
//TempCode MGA 05Feb96 			}
//TempCode MGA 05Feb96 		}
//TempCode MGA 05Feb96 		else if (strncmp(temp,"DATA",4)==0)
//TempCode MGA 05Feb96 		{
//TempCode MGA 05Feb96 			foundagain = FALSE;
//TempCode MGA 05Feb96 			constptr=CStart;
//TempCode MGA 05Feb96 			while (constptr!=NULL)
//TempCode MGA 05Feb96 			{
//TempCode MGA 05Feb96 				if (strcmp(temp,constptr->name)==0)
//TempCode MGA 05Feb96 				{
//TempCode MGA 05Feb96 					foundagain=TRUE;
//TempCode MGA 05Feb96 //TempCode MGA 23Jan96 					lfound=0;
//TempCode MGA 05Feb96 				}
//TempCode MGA 05Feb96 				constptr=constptr->link;
//TempCode MGA 05Feb96 			}
//TempCode MGA 05Feb96 			if (foundagain==FALSE)
//TempCode MGA 05Feb96 			{
//TempCode MGA 05Feb96 				addrptr=AStart;
//TempCode MGA 05Feb96 				while (addrptr!=NULL)
//TempCode MGA 05Feb96 				{
//TempCode MGA 05Feb96 					if (strcmp(temp,addrptr->name)==0)
//TempCode MGA 05Feb96 					{
//TempCode MGA 05Feb96 						foundagain=TRUE;
//TempCode MGA 05Feb96 //TempCode MGA 23Jan96 						lfound=0;
//TempCode MGA 05Feb96 					}
//TempCode MGA 05Feb96 					addrptr=addrptr->link;
//TempCode MGA 05Feb96 				}
//TempCode MGA 05Feb96 			}	
//TempCode MGA 05Feb96 			if (foundagain==FALSE)
//TempCode MGA 05Feb96 			{
//TempCode MGA 05Feb96 				offsptr=OStart;
//TempCode MGA 05Feb96 				while (offsptr!=NULL)
//TempCode MGA 05Feb96 				{
//TempCode MGA 05Feb96 					if (strcmp(temp,offsptr->name)==0)
//TempCode MGA 05Feb96 					{
//TempCode MGA 05Feb96 						foundagain=TRUE;
//TempCode MGA 05Feb96 //TempCode MGA 23Jan96 						lfound=0;
//TempCode MGA 05Feb96 					}
//TempCode MGA 05Feb96 					offsptr=offsptr->link;
//TempCode MGA 05Feb96 				}
//TempCode MGA 05Feb96 			}
//TempCode MGA 05Feb96 			if (foundagain==FALSE)
//TempCode MGA 05Feb96 				EmitSysErr("Address,Constant or Offset not found by SEQuence error checking module");
//TempCode MGA 05Feb96 
//TempCode MGA 05Feb96 		}

return(foundagain);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CheckForBracketError
//Author		Martin Alderton
//Date			Tue 23 Jan 1996
//
//Description	currently temped out. whilst I work on something else.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
int CheckForBracketError(string text,string temp, int i)
{
//TempCode MGA 23Jan96 char newtemp[80];
//TempCode MGA 23Jan96 char openchar[1];
//TempCode MGA 23Jan96 char closechar[1];
//TempCode MGA 23Jan96 int k;
//TempCode MGA 23Jan96 
//TempCode MGA 23Jan96 		openchar[0]=temp[0];
//TempCode MGA 23Jan96 		strcpy(newtemp,"");
//TempCode MGA 23Jan96 		for (k=1;k<strlen(temp);k++)
//TempCode MGA 23Jan96 		{
//TempCode MGA 23Jan96 		 	stradd(newtemp,temp[k]);
//TempCode MGA 23Jan96 		}
//TempCode MGA 23Jan96 		if (strncmp(newtemp,"TEXT",4)==0)
//TempCode MGA 23Jan96 		{
//TempCode MGA 23Jan96 			Bool found = FALSE;
//TempCode MGA 23Jan96 			for (l=0;l<20;l++)
//TempCode MGA 23Jan96 			{
//TempCode MGA 23Jan96 				snipptr=SStart[l];
//TempCode MGA 23Jan96 				while (snipptr!=NULL)
//TempCode MGA 23Jan96 				{
//TempCode MGA 23Jan96 					if (strcmp(newtemp,snipptr->name)==0)
//TempCode MGA 23Jan96 					{
//TempCode MGA 23Jan96 						lfound =l;
//TempCode MGA 23Jan96 						found =TRUE;
//TempCode MGA 23Jan96 					}
//TempCode MGA 23Jan96 					snipptr=snipptr->link;
//TempCode MGA 23Jan96 				}
//TempCode MGA 23Jan96 			}
//TempCode MGA 23Jan96 			if (found==FALSE)
//TempCode MGA 23Jan96 			{
//TempCode MGA 23Jan96 				EmitSysErr("TextSnip not found by Sequence error checking module");
//TempCode MGA 23Jan96 			}
//TempCode MGA 23Jan96 			else
//TempCode MGA 23Jan96 			{
//TempCode MGA 23Jan96 	 		//what ? - 
//TempCode MGA 23Jan96  				for (j=0;j<lfound;j++)
//TempCode MGA 23Jan96  				{
//TempCode MGA 23Jan96 					strcpy(temp,"");
//TempCode MGA 23Jan96 
//TempCode MGA 23Jan96  					while ((text[i]!=',')&&(text[i]!=';')&&(text[i]!=')')
//TempCode MGA 23Jan96 						&&(text[i]!=']')&&(text[i]!='}')&&(text[i]!='>'))
//TempCode MGA 23Jan96  					{
//TempCode MGA 23Jan96  					stradd(temp,text[i]);
//TempCode MGA 23Jan96  					i++;
//TempCode MGA 23Jan96  					}
//TempCode MGA 23Jan96  					i++; // one for the ','
//TempCode MGA 23Jan96  
//TempCode MGA 23Jan96  					if ((temp[0]!='(')&&(temp[0]!='[')&&
//TempCode MGA 23Jan96  						(temp[0]!='{')&&(temp[0]!='<'))
//TempCode MGA 23Jan96  					{
//TempCode MGA 23Jan96 						Bool foundagain = FALSE;
//TempCode MGA 23Jan96 						foundagain=CheckForError(temp);
//TempCode MGA 23Jan96 						if (foundagain!=TRUE)
//TempCode MGA 23Jan96 							EmitSysErr("Failed recursion in Error Check module");
//TempCode MGA 23Jan96 
//TempCode MGA 23Jan96 					}
//TempCode MGA 23Jan96  					else if ((temp[0]=='(')&&(temp[0]=='[')&&
//TempCode MGA 23Jan96  						(temp[0]=='{')&&(temp[0]=='<'))
//TempCode MGA 23Jan96 			
//TempCode MGA 23Jan96 					{
//TempCode MGA 23Jan96 			 		//messy bracket dealing code in here
//TempCode MGA 23Jan96 						Bool foundagain = FALSE;
//TempCode MGA 23Jan96 						foundagain=CheckForBracketError(text,temp,i);
//TempCode MGA 23Jan96 						if (foundagain!=TRUE)
//TempCode MGA 23Jan96 							EmitSysErr("Failed recursion in Error Check module");
//TempCode MGA 23Jan96 
//TempCode MGA 23Jan96 					}
//TempCode MGA 23Jan96 				}
//TempCode MGA 23Jan96 				//test if closing bracket matches at this point. add one to i too.
//TempCode MGA 23Jan96  			}
//TempCode MGA 23Jan96  		}
//TempCode MGA 23Jan96  
//TempCode MGA 23Jan96 		else if (strncmp(newtemp,"LIST",4)==0)
//TempCode MGA 23Jan96  		{
//TempCode MGA 23Jan96  			Bool found = FALSE;
//TempCode MGA 23Jan96  			for (l=0;l<20;l++)
//TempCode MGA 23Jan96  			{
//TempCode MGA 23Jan96  				listptr=LStart[l];
//TempCode MGA 23Jan96  				while (listptr!=NULL)
//TempCode MGA 23Jan96  				{
//TempCode MGA 23Jan96  					if (strcmp(newtemp,listptr->name)==0)
//TempCode MGA 23Jan96  					{
//TempCode MGA 23Jan96  						lfound =l;
//TempCode MGA 23Jan96  						found =TRUE;
//TempCode MGA 23Jan96  					}
//TempCode MGA 23Jan96  					listptr=listptr->link;
//TempCode MGA 23Jan96  				}
//TempCode MGA 23Jan96  			}
//TempCode MGA 23Jan96  			if (found==FALSE)
//TempCode MGA 23Jan96  			{
//TempCode MGA 23Jan96  				EmitSysErr("TextList not found by Sequence error checking module");
//TempCode MGA 23Jan96  			}
//TempCode MGA 23Jan96  			else
//TempCode MGA 23Jan96  			{
//TempCode MGA 23Jan96  	 		//what ?
//TempCode MGA 23Jan96  				for (j=0;j<lfound;j++)
//TempCode MGA 23Jan96  				{
//TempCode MGA 23Jan96 					strcpy(temp,"");
//TempCode MGA 23Jan96 
//TempCode MGA 23Jan96  					while ((text[i]!=',')&&(text[i]!=';'))
//TempCode MGA 23Jan96  					{
//TempCode MGA 23Jan96  					stradd(temp,text[i]);
//TempCode MGA 23Jan96  					i++;
//TempCode MGA 23Jan96  					}
//TempCode MGA 23Jan96  					i++; // one for the ','
//TempCode MGA 23Jan96  
//TempCode MGA 23Jan96  					if ((temp[0]!='(')&&(temp[0]!='[')&&
//TempCode MGA 23Jan96  						(temp[0]!='{')&&(temp[0]!='<'))
//TempCode MGA 23Jan96  					{
//TempCode MGA 23Jan96 						Bool foundagain = FALSE;
//TempCode MGA 23Jan96 						foundagain=CheckForError(temp);
//TempCode MGA 23Jan96 						if (foundagain!=TRUE)
//TempCode MGA 23Jan96 							EmitSysErr("Failed recursion in Error Check module");
//TempCode MGA 23Jan96 
//TempCode MGA 23Jan96 					}
//TempCode MGA 23Jan96  					else
//TempCode MGA 23Jan96  					{
//TempCode MGA 23Jan96  			 		//messy bracket dealing code in here
//TempCode MGA 23Jan96  						//what messier than that up there ?
//TempCode MGA 23Jan96  						// Yes,quite possibly.
//TempCode MGA 23Jan96  					}
//TempCode MGA 23Jan96  				}
//TempCode MGA 23Jan96 			}
//TempCode MGA 23Jan96  		}
//TempCode MGA 23Jan96  
//TempCode MGA 23Jan96 		else if (strncmp(newtemp,"DATA",4)==0)
//TempCode MGA 23Jan96  		{
//TempCode MGA 23Jan96  			Bool found = FALSE;
//TempCode MGA 23Jan96  			constptr=CStart;
//TempCode MGA 23Jan96  			while (constptr!=NULL)
//TempCode MGA 23Jan96  			{
//TempCode MGA 23Jan96  				if (strcmp(newtemp,constptr->name)==0)
//TempCode MGA 23Jan96  				{
//TempCode MGA 23Jan96  					found=TRUE;
//TempCode MGA 23Jan96  					lfound=0;
//TempCode MGA 23Jan96  				}
//TempCode MGA 23Jan96  				constptr=constptr->link;
//TempCode MGA 23Jan96  			}
//TempCode MGA 23Jan96  			if (found==FALSE)
//TempCode MGA 23Jan96  			{
//TempCode MGA 23Jan96  				addrptr=AStart;
//TempCode MGA 23Jan96  				while (addrptr!=NULL)
//TempCode MGA 23Jan96  				{
//TempCode MGA 23Jan96  					if (strcmp(newtemp,addrptr->name)==0)
//TempCode MGA 23Jan96  					{
//TempCode MGA 23Jan96  						found=TRUE;
//TempCode MGA 23Jan96  						lfound=0;
//TempCode MGA 23Jan96  					}
//TempCode MGA 23Jan96  					addrptr=addrptr->link;
//TempCode MGA 23Jan96  				}
//TempCode MGA 23Jan96  			}	
//TempCode MGA 23Jan96  			if (found==FALSE)
//TempCode MGA 23Jan96  			{
//TempCode MGA 23Jan96  				offsptr=OStart;
//TempCode MGA 23Jan96  				while (offsptr!=NULL)
//TempCode MGA 23Jan96  				{
//TempCode MGA 23Jan96  					if (strcmp(newtemp,offsptr->name)==0)
//TempCode MGA 23Jan96  					{
//TempCode MGA 23Jan96  						found=TRUE;
//TempCode MGA 23Jan96  						lfound=0;
//TempCode MGA 23Jan96  					}
//TempCode MGA 23Jan96  					offsptr=offsptr->link;
//TempCode MGA 23Jan96  				}
//TempCode MGA 23Jan96  			}
//TempCode MGA 23Jan96  			if (found==FALSE)
//TempCode MGA 23Jan96  				EmitSysErr("Address,Constant or Offset not found by SEQuence error checking module");
//TempCode MGA 23Jan96  			else
//TempCode MGA 23Jan96  			{
//TempCode MGA 23Jan96  	 			//what ?
//TempCode MGA 23Jan96 				for (j=0;j<lfound;j++)
//TempCode MGA 23Jan96 				{
//TempCode MGA 23Jan96 					strcpy(temp,"");
//TempCode MGA 23Jan96 					while ((text[i]!=',')&&(text[i]!=';'))
//TempCode MGA 23Jan96 					{
//TempCode MGA 23Jan96 					stradd(temp,text[i]);
//TempCode MGA 23Jan96 					i++;
//TempCode MGA 23Jan96 					}
//TempCode MGA 23Jan96 					i++; // one for the ','
//TempCode MGA 23Jan96 
//TempCode MGA 23Jan96 					if ((temp[0]!='(')&&(temp[0]!='[')&&
//TempCode MGA 23Jan96 						(temp[0]!='{')&&(temp[0]!='<'))
//TempCode MGA 23Jan96 					{
//TempCode MGA 23Jan96 						Bool foundagain = FALSE;
//TempCode MGA 23Jan96 						foundagain=CheckForError(temp);
//TempCode MGA 23Jan96 						if (foundagain!=TRUE)
//TempCode MGA 23Jan96 							EmitSysErr("Failed recursion in Error Check module");
//TempCode MGA 23Jan96 
//TempCode MGA 23Jan96 					}
//TempCode MGA 23Jan96 
//TempCode MGA 23Jan96  					else
//TempCode MGA 23Jan96  					{
//TempCode MGA 23Jan96  			 		//messy bracket dealing code in here
//TempCode MGA 23Jan96  						//what messier than that up there ?
//TempCode MGA 23Jan96  						// Yes,quite possibly.
//TempCode MGA 23Jan96  					}
//TempCode MGA 23Jan96  				}
//TempCode MGA 23Jan96 			}
//TempCode MGA 23Jan96  		}
return(i);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ErrorCheck
//Author		Martin Alderton
//Date			Fri 19 Jan 1996
//
//Description		
//					
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool ErrorCheck(string text)
{
Bool retval =TRUE;

//TempCode MGA 05Feb96 int i=0;
//TempCode MGA 05Feb96 char temp[80];
//TempCode MGA 05Feb96 strcpy(temp,"");
//TempCode MGA 05Feb96 int l,lfound;
//TempCode MGA 05Feb96 int j,k;
//TempCode MGA 05Feb96 
//TempCode MGA 05Feb96 while ((text[i]!=',')&&(text[i]!=';'))
//TempCode MGA 05Feb96 {
//TempCode MGA 05Feb96 stradd(temp,text[i]);
//TempCode MGA 05Feb96 i++;
//TempCode MGA 05Feb96 }
//TempCode MGA 05Feb96 i++; // one for the ','
//TempCode MGA 05Feb96 
//TempCode MGA 05Feb96 if (strncmp(temp,"TEXT",4)==0)
//TempCode MGA 05Feb96 {
//TempCode MGA 05Feb96 	Bool found = FALSE;
//TempCode MGA 05Feb96 	for (l=0;l<20;l++)
//TempCode MGA 05Feb96 	{
//TempCode MGA 05Feb96 		snipptr=SStart[l];
//TempCode MGA 05Feb96 		while (snipptr!=NULL)
//TempCode MGA 05Feb96 		{
//TempCode MGA 05Feb96 			if (strcmp(temp,snipptr->name)==0)
//TempCode MGA 05Feb96 			{
//TempCode MGA 05Feb96 				lfound =l;
//TempCode MGA 05Feb96 				found =TRUE;
//TempCode MGA 05Feb96 			}
//TempCode MGA 05Feb96 			snipptr=snipptr->link;
//TempCode MGA 05Feb96 		}
//TempCode MGA 05Feb96 	}
//TempCode MGA 05Feb96 	if (found==FALSE)
//TempCode MGA 05Feb96 	{
//TempCode MGA 05Feb96 		EmitSysErr("TextSnip not found by Sequence error checking module");
//TempCode MGA 05Feb96 	}
//TempCode MGA 05Feb96 	else
//TempCode MGA 05Feb96 	{
//TempCode MGA 05Feb96 	 //what ? - 
//TempCode MGA 05Feb96  		for (j=0;j<lfound;j++)
//TempCode MGA 05Feb96  		{
//TempCode MGA 05Feb96 			strcpy(temp,"");
//TempCode MGA 05Feb96 
//TempCode MGA 05Feb96  			while ((text[i]!=',')&&(text[i]!=';'))
//TempCode MGA 05Feb96  			{
//TempCode MGA 05Feb96  			stradd(temp,text[i]);
//TempCode MGA 05Feb96  			i++;
//TempCode MGA 05Feb96  			}
//TempCode MGA 05Feb96  			i++; // one for the ','
//TempCode MGA 05Feb96  
//TempCode MGA 05Feb96  			if ((temp[0]!='(')&&(temp[0]!='[')&&
//TempCode MGA 05Feb96  				(temp[0]!='{')&&(temp[0]!='<'))
//TempCode MGA 05Feb96  			{
//TempCode MGA 05Feb96 				Bool foundagain = FALSE;
//TempCode MGA 05Feb96 				foundagain=CheckForError(temp);
//TempCode MGA 05Feb96 				if (foundagain!=TRUE)
//TempCode MGA 05Feb96 					EmitSysErr("Failed recursion in Error Check module");
//TempCode MGA 05Feb96 
//TempCode MGA 05Feb96 			}
//TempCode MGA 05Feb96  			else if ((temp[0]=='(')&&(temp[0]=='[')&&
//TempCode MGA 05Feb96  				(temp[0]=='{')&&(temp[0]=='<'))
//TempCode MGA 05Feb96 			
//TempCode MGA 05Feb96 			{
//TempCode MGA 05Feb96 //TempCode MGA 23Jan96 				Bool foundagain = FALSE;
//TempCode MGA 05Feb96 //TempCode MGA 23Jan96 				foundagain=CheckForBracketError(text,temp,i);
//TempCode MGA 05Feb96 //TempCode MGA 23Jan96 				if (foundagain!=TRUE)
//TempCode MGA 05Feb96 //TempCode MGA 23Jan96 					EmitSysErr("Failed recursion in Error Check module");
//TempCode MGA 05Feb96 
//TempCode MGA 05Feb96 			}
//TempCode MGA 05Feb96 		}
//TempCode MGA 05Feb96  	}
//TempCode MGA 05Feb96  }
//TempCode MGA 05Feb96  
//TempCode MGA 05Feb96 else if (strncmp(temp,"LIST",4)==0)
//TempCode MGA 05Feb96  {
//TempCode MGA 05Feb96  	Bool found = FALSE;
//TempCode MGA 05Feb96  	for (l=0;l<20;l++)
//TempCode MGA 05Feb96  	{
//TempCode MGA 05Feb96  		listptr=LStart[l];
//TempCode MGA 05Feb96  		while (listptr!=NULL)
//TempCode MGA 05Feb96  		{
//TempCode MGA 05Feb96  			if (strcmp(temp,listptr->name)==0)
//TempCode MGA 05Feb96  			{
//TempCode MGA 05Feb96  				lfound =l;
//TempCode MGA 05Feb96  				found =TRUE;
//TempCode MGA 05Feb96  			}
//TempCode MGA 05Feb96  			listptr=listptr->link;
//TempCode MGA 05Feb96  		}
//TempCode MGA 05Feb96  	}
//TempCode MGA 05Feb96  	if (found==FALSE)
//TempCode MGA 05Feb96  	{
//TempCode MGA 05Feb96  		EmitSysErr("TextList not found by Sequence error checking module");
//TempCode MGA 05Feb96  	}
//TempCode MGA 05Feb96  	else
//TempCode MGA 05Feb96  	{
//TempCode MGA 05Feb96  	 //what ?
//TempCode MGA 05Feb96  		for (j=0;j<lfound;j++)
//TempCode MGA 05Feb96  		{
//TempCode MGA 05Feb96 			strcpy(temp,"");
//TempCode MGA 05Feb96 
//TempCode MGA 05Feb96  			while ((text[i]!=',')&&(text[i]!=';'))
//TempCode MGA 05Feb96  			{
//TempCode MGA 05Feb96  			stradd(temp,text[i]);
//TempCode MGA 05Feb96  			i++;
//TempCode MGA 05Feb96  			}
//TempCode MGA 05Feb96  			i++; // one for the ','
//TempCode MGA 05Feb96  
//TempCode MGA 05Feb96  			if ((temp[0]!='(')&&(temp[0]!='[')&&
//TempCode MGA 05Feb96  				(temp[0]!='{')&&(temp[0]!='<'))
//TempCode MGA 05Feb96  			{
//TempCode MGA 05Feb96 				Bool foundagain = FALSE;
//TempCode MGA 05Feb96 				foundagain=CheckForError(temp);
//TempCode MGA 05Feb96 				if (foundagain!=TRUE)
//TempCode MGA 05Feb96 					EmitSysErr("Failed recursion in Error Check module");
//TempCode MGA 05Feb96 
//TempCode MGA 05Feb96 			}
//TempCode MGA 05Feb96  			else
//TempCode MGA 05Feb96  			{
//TempCode MGA 05Feb96  			 //messy bracket dealing code in here
//TempCode MGA 05Feb96  				//what messier than that up there ?
//TempCode MGA 05Feb96  				// Yes,quite possibly.
//TempCode MGA 05Feb96  			}
//TempCode MGA 05Feb96  		}
//TempCode MGA 05Feb96 	}
//TempCode MGA 05Feb96  }
//TempCode MGA 05Feb96  
//TempCode MGA 05Feb96 else if (strncmp(temp,"DATA",4)==0)
//TempCode MGA 05Feb96  {
//TempCode MGA 05Feb96  	Bool found = FALSE;
//TempCode MGA 05Feb96  	constptr=CStart;
//TempCode MGA 05Feb96  	while (constptr!=NULL)
//TempCode MGA 05Feb96  	{
//TempCode MGA 05Feb96  		if (strcmp(temp,constptr->name)==0)
//TempCode MGA 05Feb96  		{
//TempCode MGA 05Feb96  			found=TRUE;
//TempCode MGA 05Feb96  			lfound=0;
//TempCode MGA 05Feb96  		}
//TempCode MGA 05Feb96  		constptr=constptr->link;
//TempCode MGA 05Feb96  	}
//TempCode MGA 05Feb96  	if (found==FALSE)
//TempCode MGA 05Feb96  	{
//TempCode MGA 05Feb96  		addrptr=AStart;
//TempCode MGA 05Feb96  		while (addrptr!=NULL)
//TempCode MGA 05Feb96  		{
//TempCode MGA 05Feb96  			if (strcmp(temp,addrptr->name)==0)
//TempCode MGA 05Feb96  			{
//TempCode MGA 05Feb96  				found=TRUE;
//TempCode MGA 05Feb96  				lfound=0;
//TempCode MGA 05Feb96  			}
//TempCode MGA 05Feb96  			addrptr=addrptr->link;
//TempCode MGA 05Feb96  		}
//TempCode MGA 05Feb96  	}	
//TempCode MGA 05Feb96  	if (found==FALSE)
//TempCode MGA 05Feb96  	{
//TempCode MGA 05Feb96  		offsptr=OStart;
//TempCode MGA 05Feb96  		while (offsptr!=NULL)
//TempCode MGA 05Feb96  		{
//TempCode MGA 05Feb96  			if (strcmp(temp,offsptr->name)==0)
//TempCode MGA 05Feb96  			{
//TempCode MGA 05Feb96  				found=TRUE;
//TempCode MGA 05Feb96  				lfound=0;
//TempCode MGA 05Feb96  			}
//TempCode MGA 05Feb96  			offsptr=offsptr->link;
//TempCode MGA 05Feb96  		}
//TempCode MGA 05Feb96  	}
//TempCode MGA 05Feb96  	if (found==FALSE)
//TempCode MGA 05Feb96  		EmitSysErr("Address,Constant or Offset not found by SEQuence error checking module");
//TempCode MGA 05Feb96  	else
//TempCode MGA 05Feb96  	{
//TempCode MGA 05Feb96  	 	//what ?
//TempCode MGA 05Feb96 		for (j=0;j<lfound;j++)
//TempCode MGA 05Feb96 		{
//TempCode MGA 05Feb96 			strcpy(temp,"");
//TempCode MGA 05Feb96 			while ((text[i]!=',')&&(text[i]!=';'))
//TempCode MGA 05Feb96 			{
//TempCode MGA 05Feb96 			stradd(temp,text[i]);
//TempCode MGA 05Feb96 			i++;
//TempCode MGA 05Feb96 			}
//TempCode MGA 05Feb96 			i++; // one for the ','
//TempCode MGA 05Feb96 
//TempCode MGA 05Feb96 			if ((temp[0]!='(')&&(temp[0]!='[')&&
//TempCode MGA 05Feb96 				(temp[0]!='{')&&(temp[0]!='<'))
//TempCode MGA 05Feb96 			{
//TempCode MGA 05Feb96 				Bool foundagain = FALSE;
//TempCode MGA 05Feb96 				foundagain=CheckForError(temp);
//TempCode MGA 05Feb96 				if (foundagain!=TRUE)
//TempCode MGA 05Feb96 					EmitSysErr("Failed recursion in Error Check module");
//TempCode MGA 05Feb96 
//TempCode MGA 05Feb96 			}
//TempCode MGA 05Feb96 
//TempCode MGA 05Feb96  			else
//TempCode MGA 05Feb96  			{
//TempCode MGA 05Feb96  			 //messy bracket dealing code in here
//TempCode MGA 05Feb96  				//what messier than that up there ?
//TempCode MGA 05Feb96  				// Yes,quite possibly.
//TempCode MGA 05Feb96  			}
//TempCode MGA 05Feb96  		}
//TempCode MGA 05Feb96 	}
//TempCode MGA 05Feb96  }
return(retval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TestLine
//Author		Martin Alderton
//Date			Thu 4 Jan 1996
//
//Description   	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TestLine(int l,FILE *file,char* word)
{

RefInputLine refinputline;				
InputLine inputline;
char* tmpstrsrc;
FILE *fp;
char *includefile;

int i=0;
int g=0;
int r=0;

TextSnipBlock *tsb;
TextListBlock *tlb;
TextSeqBlock *tqb;
UWord index[257];

int p;
for (p=0;p<257;p++)
	index[p]=0;

	tmpstrsrc=word;
		
		while (tmpstrsrc)
		{
			
			if (strcmp(tmpstrsrc,"INT")!=0)
			{
				inputline=ReadLine(tmpstrsrc,file);
			}
			else
			{
				refinputline=ReadIntLine(tmpstrsrc,file);
			}

			if (strcmp(inputline.type,"SNIP")==0)
			{
					g=0;
					g=CountPerCent(inputline.text,FALSE);
					if (g==l)
					{
						if (!snipptr || (strcmp(inputline.name,snipptr->name)!=0)
							)
						{
							//Error message
							EmitSysErr("Data out of Sequence! (%s)at text line %d of file %s"
								,inputline.name,currline,currfilename);

						}
						else
						{
							char c,lastchar;
							char outtext[Array];
							int k=0;
							char ignorec=0;
							if (inputline.text[k]=='"' || inputline.text[k]=='\'')
							{
								ignorec=inputline.text[k];
//DeadCode JIM 28Aug96 								k++;
							}
							outtext[0]=c='\0';
							outtext[1]='\0';
							do
							{
								lastchar=c;
								c=inputline.text[k];

								if (c=='\n')
								{
									k++;
									c=inputline.text[k];
									while(c=='\t')
									{
										k++;
										c=inputline.text[k];
									}
									if ((c!=' ') && (lastchar!=' '))
										stradd(outtext,' ');
								}
								if (c!=ignorec)
									stradd(outtext,c);
								k++;
							}while(k<strlen(inputline.text));

							strcpy(sptr,outtext);
							sptr+=strlen(sptr)+1;
							if (snipptr->link==NULL)
							{
								tsb=TextSnipBlock::make(sstr,sptr,g);

								SaveBlock(g,snipletter,tsb);

								snipletter++;
								sptr=sstr;
								snipindex=0;
							}
							else
							{
								snipptr=snipptr->link;
								snipindex++;
								if (snipindex==256)
								{
									//build image entry compatible with TextSnipBlock 
	
									tsb=TextSnipBlock::make(sstr,sptr,g);
									
									SaveBlock(g,snipletter,tsb);
									
									snipletter++;
									if (snipletter==26)
										EmitSysErr("All letters of Alphabet used for this snip");
									sptr=sstr;
									snipindex=0;
								}

							}

						}

					}
					//else its not the one we want... so ignore
		
			}
			else
			if (strcmp(inputline.type,"LIST")==0)
			{	
				g=0;
				char temp[80];
				strcpy(temp,"");

				i=0;
				while ((inputline.text[i]!=',')&&(inputline.text[i]!=';'))
				{
				 stradd(temp,inputline.text[i]);
				 i++;
				}
				allstrrefptr[g++]=getsnipnum(temp);
				strcpy(temp,"");

				do
				{
					if (inputline.text[i]!=',')
					{
						if (inputline.text[i]!=';')
						{	
							EmitSysErr("Comma expected but found %s at text line %d of file %s"
								,inputline.text[i],currline,currfilename);
						}
					}
					i++;
					
					while ((inputline.text[i]!=',')&&(inputline.text[i]!=';')&&(inputline.text[i]!=0))
					{
				 	stradd(temp,inputline.text[i]);
				 	i++;
					}
					allstrrefptr[g++]=getsnipnum(temp);
					strcpy(temp,"");

				}while (i<strlen(inputline.text));

				if (g==l)
					if (strcmp(inputline.name,listptr->name)!=0)
						EmitSysErr("Data out of Sequence! at text line %d of file %s",currline,currfilename);
					else
					{
						allstrrefptr+=g;
						listindex++;
						if (listptr->link==NULL)
						{
							tlb=TextListBlock::make((TextRef *)allstrref,listindex,g);
								SaveBlock(g,listletter,tlb);
							listindex=0;
							listletter++;
							allstrrefptr=allstrref;
						}
						else
						{
							listptr=listptr->link;	
							if (listindex==256)
							{
								tlb=TextListBlock::make((TextRef *)allstrref,listindex,g);
									SaveBlock(g,listletter,tlb);
								listindex=0;
								listletter++;
								if (listletter==26)
									EmitSysErr("All letters of Alphabet used for this snip");
								allstrrefptr=allstrref;
							}

						}

					}
		
			}
			else if ((strcmp(inputline.type,"SEQ")==0)&&(l==19))
			{
			//only want to go through this once after all.
		
				if (strcmp(inputline.name, seqptr->name)!=0)
					EmitSysErr("Data Out of Sequrence at text line %d of file %s",currline,currfilename);
				else
				{

					
					Bool Bostin=FALSE;
					Bostin=ErrorCheck(inputline.text);

					if (Bostin==TRUE)
					{
						char temp[80];
						int openbrackets=0;
						strcpy(temp,"");
						if (seqindex!=0)
							index[seqindex]+=index[seqindex-1];

						i=0;
						while ((inputline.text[i]!=',')&&(inputline.text[i]!=';'))
						{
				 			stradd(temp,inputline.text[i]);
				 			i++;
						}
						index[seqindex]++;
						otherseqptr[r++]=GetEquate(temp);

						strcpy(temp,"");

						do
						{
							if (inputline.text[i]!=',')
							{
								if (inputline.text[i]!=';')
								{	
									EmitSysErr("Comma expected but found %s at text line %d of file %s"
										,inputline.text[i],currline,currfilename);
								}
							}
							i++;
					
							while ((inputline.text[i]!=',')&&(inputline.text[i]!=';')&&(inputline.text[i]!=0))
							{
				 				if ((inputline.text[i]!='(')&&(inputline.text[i]!='{')
									&&(inputline.text[i]!='[')&&(inputline.text[i]!='<')
									&&(inputline.text[i]!=')')&&(inputline.text[i]!='}')
									&&(inputline.text[i]!=']')&&(inputline.text[i]!='>'))
								{
										stradd(temp,inputline.text[i]);
								}
								else if ((inputline.text[i]=='(')||(inputline.text[i]=='{')
									||(inputline.text[i]=='[')||(inputline.text[i]=='<'))
								{
									openbrackets++;
								}
								else if ((inputline.text[i]==')')||(inputline.text[i]=='}')
									||(inputline.text[i]==']')||(inputline.text[i]=='>'))
								{
									openbrackets--;
								}

				 				i++;
							}
					
							otherseqptr[r++]=GetEquate(temp);
						
							index[seqindex]++;
							strcpy(temp,"");

						}while (i<strlen(inputline.text));
					
						if (openbrackets!=0)
							EmitSysErr("The brackets don't match in this SEQuence ! at %d of file %s", currline,currfilename);

						otherseqptr[r++]=-1;
						index[seqindex]++;
					
//TempCode MGA 22Jan96 						otherseqptr+=r;
//TempCode MGA 23Jan96 						seqindex++;
						if (seqptr->link==NULL)
						{
							seqindex++;
							
							tqb=TextSeqBlock::make((TextRef *)seqstrref,index,seqindex,r);

							SaveBlock(seqletter,tqb,r);
//DeadCode RDH 29Feb96 							SaveBlock(seqletter,tqb,seqindex);

							seqletter++;
							otherseqptr=seqstrref;
							seqindex=0;
							r=0;								//RDH 08Feb96

						}
						else
						{
							seqptr=seqptr->link;
							seqindex++;
							if (seqindex==256)
							{
								tqb=TextSeqBlock::make((TextRef *)seqstrref,index,seqindex,r);
							
								SaveBlock(seqletter,tqb,r);
//DeadCode RDH 29Feb96 								SaveBlock(seqletter,tqb,seqindex);
							
								seqletter++;
								if (seqletter==26)
									EmitSysErr("All letters of Alphabet used for this sequence");
								otherseqptr=seqstrref;
								seqindex=0;
							
							}
						}
					}
				}
			}

			else if (((strcmp(inputline.type,"#INCLUDE")==0))
				||((strcmp(inputline.type,"INCLUDE")==0)))
			{
				includefile=inputline.name;
				if ((fp=fopen(includefile,"rt"))==NULL)
					{
						fprintf (stderr,"Cannot Open include file %s [TestLine]/n",includefile);
					}
				else
					{
						int oldline;
						char oldfilename[80];
						oldline=currline;
						currline=1;
						strcpy(oldfilename,currfilename);
						strcpy(currfilename,includefile);
						tmpstrsrc=getword(fp);
						while ((tmpstrsrc[0]==';')||(tmpstrsrc[0]=='!'))
								tmpstrsrc=getword(fp);
		
						while (tmpstrsrc)
						{
							TestLine(l,fp,tmpstrsrc);

							tmpstrsrc=getword(fp);
							while ((tmpstrsrc[0]==';')||(tmpstrsrc[0]=='!'))
									tmpstrsrc=getword(fp);

						}
						fclose(fp);
						currline=oldline;
						strcpy(currfilename,oldfilename);
					}



			}	

			strcpy(inputline.type,"");
			strcpy(inputline.name,"");
			strcpy(inputline.text,"");

			tmpstrsrc=getword(file);
			while ((tmpstrsrc[0]==';')||(tmpstrsrc[0]=='!'))
				tmpstrsrc=getword(file);

		};

}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BuildUIDBlock
//Author		Jim Taylor
//Date			Mon 10 Jun 1996
//
//Description	Load whole UID table in and build a names list for it.
//				any unknown entries are assigned to TEXT_NULL.
//				All entries should be in textseq0, with T_ in front of the UID name.
//				
//				Now, block up into 16s and then into 256s, and then fill in
//				a List16 for all the non-text_null entries
//
//Inputs		"h\uidvals.g"
//
//Returns	
//
//------------------------------------------------------------------------------
struct	C
{
	UWord	c[16];
	C()	{c[0]=c[1]=c[2]=c[3]=c[4]=c[5]=c[6]=c[7]=
			c[8]=c[9]=c[10]=c[11]=c[12]=c[13]=c[14]=c[15]=0xFFFF;
		}
};
struct	B
{
	C*		b[16];
	B()	{b[0]=b[1]=b[2]=b[3]=b[4]=b[5]=b[6]=b[7]=
			b[8]=b[9]=b[10]=b[11]=b[12]=b[13]=b[14]=b[15]=0;
		}
};
struct	A
{
	B*		a[16];
	A()	{a[0]=a[1]=a[2]=a[3]=a[4]=a[5]=a[6]=a[7]=
			a[8]=a[9]=a[10]=a[11]=a[12]=a[13]=a[14]=a[15]=0;
		}
};


void	BuildUIDBlock()
{
	A*	UIDtable=new A;
	int	numtables=1;
	char	uidtext[40]="T_";
	char*	uidname=&uidtext[2];
	char	uidnum[5]="1234";
	file	uidfile;
	if ((uidfile=fopen("h\\uidvals.g","rt"))==NULL)
		EmitSysErr("Can't read uidvals.g");
	char ch=fgetc(uidfile);
	while (ch!='\t')
	{
		while (ch!='\n')
			ch=fgetc(uidfile);
		ch=fgetc(uidfile);
	}
//read whole table in
	while (ch=='\t')
	{
		int	ind=0,uid=0;
		while (ch=='\t')
			ch=fgetc(uidfile);
		while (ch!='=')
		{
			if (ch>='a')
				ch-=32;
			uidname[ind++]=ch;
			ch=fgetc(uidfile);
		}
		uidname[ind]=0;
		fgetc(uidfile);
		fgetc(uidfile);
		uidnum[0]=fgetc(uidfile);
		uidnum[1]=fgetc(uidfile);
		uidnum[2]=fgetc(uidfile);
		uidnum[3]=fgetc(uidfile);
		fgetc(uidfile);
		fgetc(uidfile);
		uid=strtol(uidnum,NULL,16);
		ind=getsnipnumnoerr(uidtext);
		if (ind!=0xffff)
		{
			int	a=uid / 256,
				b=(uid % 256) /16,
				c=(uid%16);
			if (UIDtable->a[a]==NULL)
			{
				UIDtable->a[a]=new B;
				numtables++;
			}
			if (UIDtable->a[a]->b[b]==NULL)
			{
				UIDtable->a[a]->b[b]=new C;
				numtables++;
			}
			UIDtable->a[a]->b[b]->c[c]=ind;
		}
		ch=fgetc(uidfile);
	}

	if (numtables>100)
		printf("UID text table with indexing now over 3K");
//write whole table as list block
	TextListBlock*	tlb=(TextListBlock*) new char [sizeof(TextListBlock)+numtables*16*sizeof(TextRef)];
	tlb->type=TEXTTYPE_List;
	tlb->parameters=1;
	tlb->lastelement=(UByte) (numtables-1);
	tlb->listentries=(UByte) 16;
	int	currentry=0;
	int	currbase=1;
	int a,b,c;
	for (a=0;a<16;a++)
		if (UIDtable->a[a])
			tlb->lists[currentry++]=(TextRef)(UIDNamesBase+currbase++);
		else
			tlb->lists[currentry++]=(TextRef)0xffff;
	for (a=0;a<16;a++)
		if (UIDtable->a[a])
			for (b=0;b<16;b++)
				if (UIDtable->a[a]->b[b])
					tlb->lists[currentry++]=(TextRef)(UIDNamesBase+currbase++);
				else				
					tlb->lists[currentry++]=(TextRef)0xffff;
	for (a=0;a<16;a++)
		if (UIDtable->a[a])
			for (b=0;b<16;b++)
				if (UIDtable->a[a]->b[b])
					for (c=0;c<16;c++)
						tlb->lists[currentry++]=(TextRef)UIDtable->a[a]->b[b]->c[c];
//save to disk
	char*	filestring=uidtext;
	strcpy(filestring,dirstring);
	strcat(filestring,"LIST_UID.BIN");
	file	fp= fopen(filestring,"wb");

	if (fp != NULL)
	{
		int	size=sizeof(TextListBlock)
				+2*tlb->lastelement*tlb->listentries
				+2*tlb->listentries;
		fwrite(tlb,size,1,fp);
		delete [] ((char*) tlb);
		fclose(fp);

 	}

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BuildBlock
//Author		Martin Alderton
//Date			Fri 8 Dec 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void BuildBlock()
{
FILE *file;
char filename[50];
strcpy(filename,InputFile);
strcpy(currfilename,InputFile);
char* tmpstrsrc;
int l;
seqptr=SeqStart;
otherseqptr=seqstrref;



	for (l=0;l<20;l++)
	{
			sptr=sstr;
			allstrrefptr=allstrref;
			snipptr=SStart[l];
			listptr=LStart[l];
			snipletter=0;
			snipindex=0;
			listletter=0;
			listindex=0;
			currline=0;

		if ((file=fopen(filename,"rt"))==NULL)
		{
			fprintf (stderr,"Cannot Open input file \n");
		}
		else
		{
			while (!feof(file))
			{	
				tmpstrsrc=getword(file);
				while ((tmpstrsrc[0]==';')||(tmpstrsrc[0]=='!'))
						tmpstrsrc=getword(file);
		
				while (tmpstrsrc)
				{
						TestLine(l,file,tmpstrsrc);


						tmpstrsrc=getword(file);
						while ((tmpstrsrc[0]==';')||(tmpstrsrc[0]=='!'))
							tmpstrsrc=getword(file);
				};
			};
		}
		fclose(file);

	}//end bracket of for l loop

	BuildUIDBlock();

}

//------------------------------------------------------------------------------

static	TextSnipBlock*	TextSnipBlock::make(string start,string end,int params)
{
	if (end<(start+2))
	{
		TextSnipBlock*	tsb=new TextSnipBlock;
		tsb->type=TEXTTYPE_Empty;
		tsb->parameters=(UByte) params;
		tsb->lastelement=0;
		return(tsb);
	}
	//else
	{
		ULong	j=(ULong) end-(ULong)start;
		ULong 	k=0,tt=0;
		TextSnipBlock*	tsb=(TextSnipBlock*) new char [sizeof(TextSnipBlock)+j];
		if (params)
			tsb->type=TEXTTYPE_Snipn;
		else
			tsb->type=TEXTTYPE_Snip0;
		tsb->parameters=(UByte)params;
char	*t=&(tsb->textdatas[0]),
		*s=start;
		tsb->textstarters[k++]=0;
		while(j--)		//don't want to trigger IF for last zero!
			if(((t[tt++])=*(s++))==0)
				tsb->textstarters[k++]=tt;
		tsb->lastelement=(UByte)(k-2);
		while (k<257) 
				tsb->textstarters[k++]=-1;

		return(tsb);
	}
}

static	TextListBlock*	TextListBlock::make(TextRef	init[],int initsize,int params)
{
	if (initsize==0)
	{
		TextListBlock*	tsb=new TextListBlock;
		tsb->type=TEXTTYPE_Empty;
		tsb->parameters=(UByte) params;
		tsb->lastelement=0;
		return(tsb);
	}
	//else
	{
int		i=initsize*params;
		TextListBlock*	tlb=(TextListBlock*) new char [sizeof(TextListBlock)+initsize*params*sizeof(TextRef)];
		tlb->type=TEXTTYPE_List;
		tlb->parameters=1;
		tlb->lastelement=(UByte) (initsize-1);
		tlb->listentries=(UByte) params;
		while (i--)	tlb->lists[i]=init[i];
		return(tlb);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		make
//Author		Martin Alderton
//Date			Fri 19 Jan 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
static TextSeqBlock* TextSeqBlock::make(TextRef init[], UWord index[],int seqindex, int r)
{
	if (seqindex==0)
	{
		TextSeqBlock*	tqb=new TextSeqBlock;
		tqb->type=TEXTTYPE_Empty;
		tqb->parameters=(UByte) r;
		tqb->lastelement=0;
		return(tqb);
	}
	//else
	{
		int i=r;
//DeadCode RDH 08Feb96 		TextSeqBlock*	tqb=(TextSeqBlock*) new char [sizeof(TextSeqBlock)+(i*sizeof(TextRef))+(seqindex*sizeof(UWord))];
		TextSeqBlock*	tqb=(TextSeqBlock*) new char [sizeof(TextSeqBlock)+(r*sizeof(TextRef))];
		tqb->type=TEXTTYPE_Seq;
		tqb->parameters=1;
		tqb->lastelement=(UByte) (seqindex-1);
		tqb->seqentries=(UByte) r;
		int m=0;
		do
		{
			tqb->index[m]=(UWord)index[m];
			m++;
		}while (index[m]!=NULL);
		tqb->index[m]=(UWord)(seqindex-1);
		while (m<257) 
				tqb->index[m++]=-1;
		while (i--) tqb->seqs[i]=init[i];
		return(tqb);
	}

}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FileList
//Author		Martin Alderton
//Date			Thu 21 Dec 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void SnipFileList(string filename)
{
	FILE *fp;
	if (numsnipfiles==0)
	{
		fp= fopen("textsnip.tmp","wt");
 		fprintf(fp,"[files]\n");
 		fprintf(fp,"113\n");
	}
	else
		fp= fopen("textsnip.tmp","at");

	if (fp != NULL)
	{
 			fprintf(fp,"%s\n",filename);

	 	fclose(fp);
	}
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FileList
//Author		Martin Alderton
//Date			Thu 21 Dec 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ListFileList(string filename)
{
FILE *fp;

	if (numlistfiles==0)
	{
		fp= fopen("textlist.tmp","wt");
 		fprintf(fp,"[files]\n");
 		fprintf(fp,"113\n");
	}
	else
		fp= fopen("textlist.tmp","at");

	if (fp != NULL)
	{
 			fprintf(fp,"%s\n",filename);

	 	fclose(fp);
	}
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FileList
//Author		Martin Alderton
//Date			Tue 23 Jan 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void SeqFileList(string filename)
{
FILE *fp;

	if (numseqfiles==0)
	{
		fp= fopen("textseq.tmp","wt");
 		fprintf(fp,"[files]\n");
 		fprintf(fp,"113\n");
	}
	else
		fp= fopen("textseq.tmp","at");

	if (fp != NULL)
	{
 			fprintf(fp,"%s\n",filename);

	 	fclose(fp);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Delete
//Author		Martin Alderton
//Date			Tue 19 Dec 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Delete()
{
 int i;

	for (i=0;i<20;i++)
	{
		SStart[i]=NULL;
		LStart[i]=NULL;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SafeCheckFile
//Author		Dave Whiteside
//Date			Thu 31 Oct 1996
//
//Description	compares the file fname.tmp with fname.ext and if they are 
//				different then del fname.ext and replace it with fname.tmp
//
//Inputs		fname	- filename to check can have path but no extension
//				ext		- extension for fname
//
//Returns		file nobbled or not on disk
//
//------------------------------------------------------------------------------
SafeCheckFile(char *fname,char *ext)
{
	char 		bolox[LINELEN];
	char 		rolox[LINELEN];
	char		orgnom[LINELEN];
	char		nuenom[LINELEN];
	int			changed=NULL;

	strcpy(orgnom,fname);
	strcat(orgnom,ext);
	strcpy(nuenom,fname);
	strcat(nuenom,".TMP");
//	cout << "Test "<< fname << "\t" << ext << "\n";

	ifstream	org(orgnom);
	ifstream	nue(nuenom);

	if (org.ios::bad() || nue.ios::bad())
	{
		if (org.ios::bad())
		{
			cerr << "WARNING: failed to find:" << orgnom << "\n";
			org.close();
			nue.close();
			rename(nuenom,orgnom);
		}
		else
		{
			if (nue.ios::bad())
			{
				cerr << "ERROR: failed to find:" << nuenom << "\n";
				exit(-4);
			}
		}
	}
	else
	{
		do
		{
			org >> bolox;
			nue	>> rolox;
			if (strcmp(bolox,rolox))
				changed=1;
		}
		while (!org.ios::eof() && (!nue.ios::eof()) && changed==0);
		org.close();
		nue.close();
		if (changed)
		{
			unlink(orgnom);
			rename(nuenom,orgnom);
		}
		else
			unlink(nuenom);
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Main
//Author		Martin Alderton
//Date			Mon 11 Dec 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
int main(int argc,char *argv[])
{
	char	*tmp;
	if (argc>1)
		for (int i=1;i<argc;i++)
		{
			if (argv[i][0]=='/' || argv[i][0]=='-')
			{
				char	c;

				c=argv[i][1];
				switch (c)
				{
					case 'H':
					case 'h':
					case '?':
						cout << "Usage: textbin [-?h] [-i] [-o] [-t]\n"
							<<	"-?	-h  This message\n"
							<<	"-idir  input [def to english]\n"
							<<	"-llang	Language - instead of -i -o -t\n"
							<<	"-onom	header file [def h\\textenum.g\n"
							<<	"-tdir	target directory [def ..\\game\\text\\\n";
						exit(0);
						break;
					case 'i':
					case 'I':
						tmp=&argv[i][2];
						strcpy(InputFile,tmp);
						strcat(InputFile,"\\inputdat.txt");
						break;
					case 'l':
					case 'L':
						tmp=&argv[i][2];
						strcpy(InputFile,tmp);
						strcat(InputFile,"\\inputdat.txt");
						strcpy(headerfile,"h\\");
						strcat(headerfile,tmp);
						strcat(headerfile,".TMP");
						strcpy(dirstring,"..\\game\\");
						strcat(dirstring,tmp);
						strcat(dirstring,"\\");
						break;
					case 'o':
					case 'O':
						tmp=&argv[i][2];
						strcpy(headerfile,tmp);
						strcat(headerfile,".TMP");
						break;
					case 't':
					case 'T':
						tmp=&argv[i][2];
						strcpy(dirstring,tmp);
						break;
					default:
						cerr << "Unknown option :" << c << ":\n";
						break;
				}
			}
			else
				cerr << "missing - or / sign ??\n";
		}
	cout <<	"Textbin Version " << __DATE__
		<< "\nHeader file\t" << headerfile
		<< "\nInput file\t" << InputFile
		<< "\nTarget dir\t" << dirstring
		<< "\n";


   	InitLinkLists(); //sets up values for later use
  	ReadData();		//reads in the data file designated at the top of the file
  	Assign();		//this file writes some enums to text.g
	AssignConstants();
	AssignAddresses();
	AssignOffsets();
  	BuildBlock();	//this builds blocks of snips and lists and exports them to .BIN files.

	SafeCheckFile("TEXTSEQ",".FIL");
	SafeCheckFile("TEXTSNIP",".FIL");
	SafeCheckFile("TEXTLIST",".FIL");

	tmp=strstr(headerfile,".TMP");
	*tmp=0;
	SafeCheckFile(headerfile,".G");

  	Delete();
	return(0);
}

