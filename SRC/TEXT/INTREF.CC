//------------------------------------------------------------------------------
//Filename       intref.cpp
//System         
//Author         Martin Alderton
//Date           Wed 10 Jan 1996
//Description    Integer Referencing procedures 
//------------------------------------------------------------------------------
#include	<stdlib.h>
#include	<stdio.h>
#include	<conio.h>
#include	<io.h>
#include	<string.h>
#include	<stdarg.h>
#include	<string.h>
#include	<ctype.h>

#include	"dosdefs.h"
#include	"fileman.h"
#include	"textref.h"
#include	"intref.h"


// global variable area

char InputFile[80] = "intdata.txt";  //in font directory.
char EnumConstFile[80]= "..\\h\\const";
char EnumAddrFile[80]= "..\\h\\addr";
char EnumOffsFile[80]= "..\\h\\offs";

ConstantstrucPtr constant;
ConstantstrucPtr CStart;
AddressstrucPtr address;
AddressstrucPtr AStart;
OffsetstrucPtr offset;
OffsetstrucPtr OStart;

int concount=0;		//use to count up number of enteries of each 
int addcount=0;		//for putting into 256 blocks.
int offcount=0;

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
		*endchars=" \n\t" "\";!=,",
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
//TempCode MGA 15Jan96 		if (c=='\n')
				//currsrcfline++;
		//else
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
//Procedure		ReadLine
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
RefInputLine ReadIntLine(char* word,FILE *file)
{
//char lastchar;
//char c;
int i=0;
char*	tmpstrsrc;
RefInputLine inputline;

	tmpstrsrc=word;

	strcpy(inputline.type,tmpstrsrc);

	if (strcmp(inputline.type,"INT")==0)
	{
		
		tmpstrsrc=getword(file);
		strcpy(inputline.name,tmpstrsrc);

		tmpstrsrc=getword(file);
		if (tmpstrsrc[0]=='=')
			tmpstrsrc=getword(file);

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

delete tmpstrsrc;
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
		strcpy(oneoffs.mask_shift,(char *)inputline.data[0]);
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
int i;
filename = InputFile;
RefInputLine inputline;
char* tmpstrsrc;

if ((file=fopen(filename,"rt"))==NULL)
	{
		fprintf (stderr,"Cannot Open input file \n");
	}
else
	{
		while(!feof(file))
		{
			strcpy(inputline.type,"");
			strcpy(inputline.name,"");
			for (i=0;i<3;i++)
				strcpy(inputline.data[i],"");


			tmpstrsrc=getword(file);
			while ((tmpstrsrc[0]==';')||(tmpstrsrc[0]=='!')||(tmpstrsrc[0]=='\n'))
				tmpstrsrc=getword(file);
			
			while (tmpstrsrc)
			{
				inputline=ReadLine(tmpstrsrc,file);

				ProcessLine(inputline);

				strcpy(inputline.type,"");
				strcpy(inputline.name,"");
				for (i=0;i<3;i++)
					strcpy(inputline.data[i],"");

				tmpstrsrc=getword(file);
					while ((tmpstrsrc[0]==';')||(tmpstrsrc[0]=='!')||(tmpstrsrc[0]=='\n'))
						tmpstrsrc=getword(file);

			};
		};

	}
	fclose(file);
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

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetNumber
//Author		Martin Alderton
//Date			Fri 12 Jan 1996
//
//Description   gets first number form a text string	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
int GetNumber(char* text)
{
int num=0;
int j=0;

for (j=0;j<strlen(text);j++)
{
	
	if ((text[j]>='0')&&(text[j]<='9'))
	{
		if ((text[j+1]>='0')&&(text[j+1]<='9'))
			num=text[j+1]+10-'0';
		else if ((text[j]>='0')&&(text[j]<='9'))
			num=text[j]-'0';
	}
}
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
}

else if (strcmp(test,"NOPRINT")==0)
{
	strcpy(text.code,"OFORM_NO");
}

else if (strcmp(test,"TH")==0) //is this the right code ??
{
	strcpy(text.code,"OFORM_TH");
}

else if (strcmp(test,"SIGN")==0) //is this the right code ??
{
	strcpy(text.code,"OFORM_SIGN");
}

else if (strcmp(test,"ZEROS")==0) 
{
	strcpy(text.code,"OFORM_LZ");
}

else if ((strcmp(test,"MASK")!=0)&&(strcmp(test,"SH")!=0))
	EmitSysErr("Error in GetOutputFormat module");
//TempCode MGA 16Jan96 	strcpy(text.code,(char *)'0');


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
				fprintf(file,"TextBlock\tTextBlock_headerc%s\t=\t{TEXTTYPE_CONST,0,%d};\n",timesthrough,j);
				fprintf(file,"TextBlock_constants\tTextBlock_instance%d[]\t=\n",timesthrough);
				fprintf(file,"\t{\n");

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

							//get number
							num= GetNumber(conptr->format);
							if ((num<0)||(num>16))
								EmitSysErr("Minimum number of digits incorrectly specified 1");

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
							strcpy(text.code,"0");
					}
					else
					{
			 		EmitSysErr("Output Format Information MUST be supplied with a constant");
					}
					fprintf(file,"\t\t{%d,\t{0,31},{%d,%s}}",conptr->constant,num,text.code);
					conptr=conptr->link;
					if (conptr)
						fprintf(file,",\n");
				}

				// interpret and print text here (see above)

				fprintf(file,"\n\t};\n\n");

				//constant enum code to go in below
				//starts at constant 0x000 at the mo,
				//needs to be generated from elsewhere, no ?


				fprintf(file,"enum\tText_Const\t{\tText_ConstMIN=0x0000\n");
				conptr=CStart;
				for (i=0;conptr!=NULL;i++)
				{
		 			fprintf(file,"\t\t%s=Text_ConstMIN+0x%04x,\n",conptr->name,i);
					conptr=conptr->link;
				}
				fprintf(file,"\t\tText_ConstMAX=0x%04x\n",i);
  				fprintf(file,"\n\t};\n\n");

			fclose(file);
			}
		timesthrough++;
	}while (concount!=0);
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
char test[20]="";
int j = 0;


// take in whole chunk to be tested, search for the first word
// then the first number-place into appropriate part of structure
// then next word (test for validity obviously) then next number
// and return

 while (text[j]!=' ')
 {
 		stradd(test,text[j]);
 	j++;					
 };
	
	if (strcmp(test,"MASK")==0) 
	{
		j++;
		//get number
		if ((text[j+1]>='0')&&(text[j+1]<='9'))
			retval.mask=text[j+1]+10 - '0';
		else if ((text[j]>='0')&&(text[j]<='9'))
			retval.mask=text[j] - '0';
		else
			EmitSysErr("Mask incorrectly specified");
		strcpy(test,"");
		j++;
		j++;
		while (text[j]!=' ')
		{
				stradd(test,text[j]);
			j++;					
		};
		if (strcmp(test,"SH")!=0)
			EmitSysErr("No Shift value present !");
		else
		{
			j++;
			//get number
			if ((text[j+1]>='0')&&(text[j+1]<='9'))
				retval.shift=text[j+1]+10 - '0';
			else if ((text[j]>='0')&&(text[j]<='9'))
				retval.shift=text[j] - '0';
			else
				EmitSysErr("Shift incorrectly specified");
		}

	}
	else if (strcmp(test,"SH")==0) 
	{
		j++;
		//get number
		if ((text[j+1]>='0')&&(text[j+1]<='9'))
			retval.shift=text[j+1]+10 - '0';
		else if ((text[j]>='0')&&(text[j]<='9'))
			retval.shift=text[j] - '0';
		else
			EmitSysErr("Shift incorrectly specified");
		strcpy(test,"");
		j++;
		j++;
		while (text[j]!=' ')
		{
				stradd(test,text[j]);
			j++;					
		};
		if (strcmp(test,"MASK")!=0)
			EmitSysErr("No Mask value present !");
		else
		{
			j++;
			//get number
			if ((text[j+1]>='0')&&(text[j+1]<='9'))
				retval.mask=text[j+1]+10 - '0';
			else if ((text[j]>='0')&&(text[j]<='9'))
				retval.mask=text[j] - '0';
			else
				EmitSysErr("Mask incorrectly specified");
		}

	}
	else if ((strcmp(test,"SIGN")!=0)&&(strcmp(test,"TH")!=0)
		&&(strcmp(test,"MIN")!=0)&&(strcmp(test,"NOPRINT")!=0)
			&&(strcmp(test,"ZEROS")!=0))
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
			strcpy(InputF.special,"ILL_INDBEFORE");
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
				fprintf(file,"TextBlock\tTextBlock_headera%d\t=\t{TEXTTYPE_ADDR,0,%d};\n",timesthrough,j);
				fprintf(file,"TextBlock_addresses\tTextBlock_instance%d[]\t=\n",timesthrough);
				fprintf(file,"\t{\n");

				for (i=0;addptr!=NULL;i++)
				{
		 			int j1=0;
					int mask1=0;
					int shift1=31;
		 			int j2=0;
					int mask2=0;
					int shift2=31;
					int num1=0;
					int num2=0;
					OutputLine text1;
					char test1[10]="";  	//need to allow for the possibility of
					OutputLine text2;			//output formatting info coming before
					char test2[10]="";		//input data, and vice-versa
					InputFormat InputF;

					strcpy(text1.code,"0");
					strcpy(text2.code,"0");


 					if ((addptr->address[0]!='[')&&(addptr->address[0]!='"'))
					{
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
								EmitSysErr("Minimum number of digits incorrectly specified 2");

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
 						}

 						if (addptr->format2[j2]!=NULL)
 						{
 							while ((addptr->format2[j2]!=' ')&&(addptr->format2[j2]!=NULL))
 							{
 				 				stradd(test2,addptr->format2[j2]);
 								j2++;					
 							};
							text2=GetOutputFormat(test2);

							//get number
							num2= GetNumber(addptr->format2);
							if ((num2<0)||(num2>16))
								EmitSysErr("Minimum number of digits incorrectly specified 3");

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
 						}
					}
					else if (addptr->address[0]=='"')
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

					int shift;
					int mask;
					int num;
					char text[20];

					if (shift2!=31)
						shift=shift2;
					else
						shift=shift1;

					if (mask2!=0)
						mask=mask2;
					else
						mask=mask1;

					if (num2!=0)
						num=num2;
					else
						num=num1;

					if (strcmp(text2.code,"0")!=0)
						strcpy(text,text2.code);
					else 
						strcpy(text,text1.code);

					InputF.shift=shift;
					InputF.mask=mask;
					strcpy(InputF.special,"");

					//have to allow for illegal(special) shift/mask codes
					if (shift+mask>=32)
					{
						InputF=TestForSpecial(InputF);	
					}
			
					char addresstext[30]="";
					int m=0;
					for (m=0;m<strlen(addptr->address);m++)
					{
			 			if ((addptr->address[m]!='[')&&(addptr->address[m]!='+')&&(addptr->address[m]!=']')&&(addptr->address[m]!='"'))
							stradd(addresstext,addptr->address[m]);
					}
			
					if (strcmp(InputF.special,"")!=0)
					{
   						fprintf(file,"\t\t{(void*)&%s,{%d,%s},{%d,%s}}",addresstext,shift,InputF.special,num,text);
					}
					else
					{
   						fprintf(file,"\t\t{(void*)&%s,{%d,%d},{%d,%s}}",addresstext,shift,mask,num,text);
  					}
					addptr=addptr->link;
  					if (addptr)
  						fprintf(file,",\n");
  				}
  
  				// interpret and print text here (see above)

  
  				fprintf(file,"\n\t};\n\n");
  
  				//constant enum code to go in below
  
  				fprintf(file,"enum\tText_Addr\t{\tText_AddrMIN=0x0000\n");
  				addptr=AStart;
  				for (i=0;addptr!=NULL;i++)
  				{
  		 			fprintf(file,"\t\t%s=Text_AddrMIN+0x%04x,\n",addptr->name,i);
  					addptr=addptr->link;
				}
  				fprintf(file,"\t\tText_AddrMAX=0x%04x\n",i);

  				fprintf(file,"\n\t};\n\n");

			fclose(file);
			}
		timesthrough++;
	}while (addcount!=0);


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
				fprintf(file,"TextBlock\tTextBlock_headero%d\t=\t{TEXTTYPE_OFF,0,%d};\n",timesthrough,j);
				fprintf(file,"TextBlock_offsets\tTextBlock_instance%d[]\t=\n",timesthrough);
				fprintf(file,"\t{\n");

				for (i=0;offptr!=NULL;i++)
				{
		 			int j1=0;
					int mask1=0;
					int shift1=0;
		 			int j2=0;
					int mask2=0;
					int shift2=0;
					int num1=0;
					int num2=0;
					OutputLine text1;
					char test1[10]="";  //need to allow for the possibility of
					OutputLine text2;		//output formatting info coming before
					char test2[10]="";	//input data, and vice-versa
					InputFormat InputF;

					strcpy(text1.code,"0");
					strcpy(text2.code,"0");
 			
					if ((offptr->mask_shift[1]!='[')&&(offptr->mask_shift[1]!='"'))
					{

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
								EmitSysErr("Minimum number of digits incorrectly specified 5");

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
						}

 						if (offptr->format2[j2]!=NULL)
 						{
 							while ((offptr->format2[j2]!=' ')&&(offptr->format2[j2]!=NULL))
 							{
 				 				stradd(test2,offptr->format2[j2]);
 								j2++;					
 							};
							text2=GetOutputFormat(test2);

							//get number
							num1= GetNumber(offptr->format2);
							if ((num2<0)||(num2>16))
								EmitSysErr("Minimum number of digits incorrectly specified 6");

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

						}
					}
					else if (offptr->mask_shift[1]=='"')
					{
						shift1=31;
						mask1=1;
					}									
					else if (offptr->mask_shift[1]=='[')
					{
			 			shift1=31;
						int k;
						k = strlen(offptr->mask_shift);
						if (offptr->mask_shift[k-1]=='+')
							mask1=11;
						else if ((offptr->mask_shift[k-1]==']')&&(offptr->mask_shift[k-2]=='+'))
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

					int shift;
					int mask;
					int num;
					char text[20];

					if (shift2!=0)
						shift=shift2;
					else
						shift=shift1;

					if (mask2!=0)
						mask=mask2;
					else
						mask=mask1;

					if (num2!=0)
						num=num2;
					else
						num=num1;

					if (strcmp(text2.code,"0")!=0)
						strcpy(text,text2.code);
					else
						strcpy(text,text1.code);

					InputF.shift=shift;
					InputF.mask=mask;
					strcpy(InputF.special,"");

					//have to allow for illegal(special) shift/mask codes
					if (shift+mask>=32)
					{
						InputF=TestForSpecial(InputF);	

					}
			
					char offsettext[30]="";
					int m=0;
					for (m=0;m<strlen(offptr->mask_shift);m++)
					{
			 			if ((offptr->mask_shift[m]!='[')&&(offptr->mask_shift[m]!='+')&&(offptr->mask_shift[m]!='"'))
							stradd(offsettext,offptr->mask_shift[m]);
					}

					if (strcmp(InputF.special,"")!=0)
					{
   						fprintf(file,"\t\t{OFFSETCAST\t(%s),{%d,%s},{%d,%s}}",offsettext,shift,InputF.special,num,text);
					}
					else
					{
   						fprintf(file,"\t\t{OFFSETCAST\t(%s),{%d,%d},{%d,%s}}",offsettext,shift,mask,num,text);
  					}
					offptr=offptr->link;
  					if (offptr)
  						fprintf(file,",\n");
  				}
  
  				// interpret and print text here (see above)

  
  				fprintf(file,"\n\t};\n\n");
  
  				//constant enum code to go in below
  
  				fprintf(file,"enum\tText_Off\t{\tText_OffMIN=0x0000\n");
  				offptr=OStart;
  				for (i=0;offptr!=NULL;i++)
  				{
  		 			fprintf(file,"\t\t%s=Text_OffMIN+0x%04x,\n",offptr->name,i);
  					offptr=offptr->link;
				}
  				fprintf(file,"\t\tText_OffMAX=0x%04x\n",i);

  				fprintf(file,"\n\t};\n\n");

		fclose(file);
		}
	timesthrough++;
	}while (offcount!=0);

}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		main
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
int main()
{
 	ReadData();

	AssignConstants();

	AssignAddresses();

	AssignOffsets();

	return(0);

}
