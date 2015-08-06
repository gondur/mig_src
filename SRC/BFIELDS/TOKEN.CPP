/*
	 MiG Alley
	 Copyright (C) 1998, 1999, 2000, 2001 Empire Interactive (Europe) Ltd,
	 677 High Road, North Finchley, London N12 0DA

	 Please see the document licence.doc for the full licence agreement

2. LICENCE
 2.1 	
 	Subject to the provisions of this Agreement we now grant to you the 
 	following rights in respect of the Source Code:
  2.1.1 
  	the non-exclusive right to Exploit  the Source Code and Executable 
  	Code on any medium; and 
  2.1.2 
  	the non-exclusive right to create and distribute Derivative Works.
 2.2 	
 	Subject to the provisions of this Agreement we now grant you the
	following rights in respect of the Object Code:
  2.2.1 
	the non-exclusive right to Exploit the Object Code on the same
	terms and conditions set out in clause 3, provided that any
	distribution is done so on the terms of this Agreement and is
	accompanied by the Source Code and Executable Code (as
	applicable).

3. GENERAL OBLIGATIONS
 3.1 
 	In consideration of the licence granted in clause 2.1 you now agree:
  3.1.1 
	that when you distribute the Source Code or Executable Code or
	any Derivative Works to Recipients you will also include the
	terms of this Agreement;
  3.1.2 
	that when you make the Source Code, Executable Code or any
	Derivative Works ("Materials") available to download, you will
	ensure that Recipients must accept the terms of this Agreement
	before being allowed to download such Materials;
  3.1.3 
	that by Exploiting the Source Code or Executable Code you may
	not impose any further restrictions on a Recipient's subsequent
	Exploitation of the Source Code or Executable Code other than
	those contained in the terms and conditions of this Agreement;
  3.1.4 
	not (and not to allow any third party) to profit or make any
	charge for the Source Code, or Executable Code, any
	Exploitation of the Source Code or Executable Code, or for any
	Derivative Works;
  3.1.5 
	not to place any restrictions on the operability of the Source 
	Code;
  3.1.6 
	to attach prominent notices to any Derivative Works stating
	that you have changed the Source Code or Executable Code and to
	include the details anddate of such change; and
  3.1.7 
  	not to Exploit the Source Code or Executable Code otherwise than
	as expressly permitted by  this Agreement.

questions about this file may be asked at http://www.simhq.com/
*/

//------------------------------------------------------------------------------
//Filename       trans3d.cpp
//System         
//Author         Robert Slater
//Date           Mon 1 Apr 1996
//Description    Dictionary and 3dstudio translation
//------------------------------------------------------------------------------

#include	"token.h"


char	*TokenSpell::names[MaxTotFileCount+1] = {"Internal list"};

UWord	TokenSpell::currsrcfname = 0;
UWord	TokenSpell::topsrcfname = 0;
UWord	TokenSpell::currsrcfline = 0;
UWord	TokenSpell::filenestlevel = 0;

UFILE*	TokenSpell::filelistfile;
char	TokenSpell::filebuff[80];
int		TokenSpell::fileend;

char	*TokenSpell::whitechars = " \t";							//doesn't include newline - handled separately
char	*TokenSpell::endchars = " \n\t" "<{([)}>],;+=:*@?";		//this list comes from the punctuation tokens identified below.

char	TokenSpell::wordbuff[180] = {0};

TokenName	TokenSpell::statictoken;
IntegerInst	TokenSpell::staticinteger;

TokenSpell	TokenSpell::FirstSpell;

DataInst::RecurseChk* DataInst::RecurseChk::base=NULL;

//------------------------------------------------------------------------------
//Enhanced error messaging. __FILE__ and __LINE__ are inserted using 
//inline functions, so they should be accurate!
//
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		EmitSysErr
//Author		Robert Slater
//Date			Mon 1 Apr 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	EmitSysErr(int line,char* mark,char* filename,char* &maintext)
{
	va_list	marker={mark};
	printf("Error : code: %s(%i). Reading: %s(%i)\n",
				filename,line,TokenSpell::names[TokenSpell::currsrcfname],TokenSpell::currsrcfline);
	vprintf(maintext,marker);
	printf("\n");
	exit(10);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		EmitWarning
//Author		Robert Slater
//Date			Mon 1 Apr 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	EmitWarning(int line,char* mark,char* filename,char* &maintext)
{
	va_list	marker={mark};
	printf("Warning: code: %s(%i); read: %s(%i):",
				filename,line,TokenSpell::names[TokenSpell::currsrcfname],TokenSpell::currsrcfline);
	vprintf(maintext,marker);
	printf("\n");
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		EmitWarning
//Author		Robert Slater
//Date			Mon 1 Apr 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	EmitWarning(char *fmt, ...)
{
	va_list	marker;	 //this points to an array of pointers
	va_start(marker, fmt);
	EmitWarning(__LINE__ , marker[0], __FILE__ ,  fmt);

}

///////////////////////
//
// Black box parser starts here
//
//
/*
  Functions provided:

ufile	readfile(char*	name)
	Opens named file for reading, remembers name, and resets line count
ufile	writefile(char*	name,char mode)
	Opens named file for reading, remembers name, and resets line count

Bool	testspelling(char*	newname,TokenName*	&newtoken)
	Checks for spelling entry in dictionary. Returns newtoken, or FALSE.
	Integers return FALSE.

Bool	findspelling(char*	newname,TokenName*	&newtoken)
Bool	findspelling(file	ifile,TokenName*	&newtoken)
	Checks for spelling entry in dictionary. If not exist then creates entry.
	Returns TRUE if already known. False if new entry, and tokencode=T_unknown.
	Integers return FALSE, but tokencode=T_int and instance filled in.

void	addspelling(TokenInit tokentoadd)
	Adds a TokenInit to the dictionary.

void	addfixedspellings()
	Adds all entries in fixedtokens array.

Bool	stripwhite(ufile	ifile)
	Strips whitespace from input file. Returns FALSE if EOF.

string	getword(file	ifile)
	Gets a token from the file. Currently returns NULL if EOF.
	In future, this will EmitSysErr if EOF. Be warned!!!!

*/

///////////////////////
//
// Black box parser code starts here
//
//
//------------------------------------------------------------------------------

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		readfile
//Author		Robert Slater
//Date			Mon 1 Apr 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
static	file	TokenSpell::readfile(char*	name)
{
	file	myfile;

	names[currsrcfname=++topsrcfname] = safetext(name);

	currsrcfline = 1;

	if (currsrcfname == MaxFileCount)
		EmitSysErr("Max input files exceeded (%i)!",MaxFileCount);

	myfile = fopen(name,"rt");

	if (myfile == NULL)
		EmitSysErr("Error opening file!");

	return(myfile);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		setwritefile
//Author		Jim Taylor
//Date			Tue 5 Dec 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
static	void	TokenSpell::setwritefile(char* path)
{
	fileend = 0;

	while (*path)
		filebuff[fileend++]=*(path++);

	if (	(filebuff[fileend-1]!=':')
		&&	(filebuff[fileend-1]!='\\')	)
		filebuff[fileend++]='\\';
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		writefile
//Author		Robert Slater
//Date			Mon 1 Apr 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
static	ufile	TokenSpell::writefile(char*	name,char mode)
{
	int		i;
	ufile	myfile;

	names[currsrcfname=++topsrcfname] = name;
	currsrcfline=0;

	if (currsrcfname==MaxTotFileCount)
		EmitSysErr("Max files exceeded (%i)!",MaxFileCount);

	i=fileend;

	while (*name)
		filebuff[i++] = *(name++);

	filebuff[i++] = 0;

	myfile = fopen(filebuff,mode);

	if (myfile==NULL)
		EmitSysErr("Error opening file!");

	return(myfile);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SaveTxt
//Author		Robert Slater
//Date			Mon 1 Apr 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TokenName::SaveTxt(ufile	ofile,int	depth)
{
	if (instance)
		instance->SaveTxt(ofile,depth);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TokenText
//Author		Robert Slater
//Date			Mon 1 Apr 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
string	TokenName::TokenText()
{
	if (this==NULL)			return("<no name>");
	if (tokentext)			return(tokentext);
	if (tokencode==T_int)	return("<integer value>");

	return("<sequence>");
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		testspelling
//Author		Robert Slater
//Date			Mon 1 Apr 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
static	Bool	TokenSpell::testspelling(char*	newname,TokenName*	&newtoken)			//returns TRUE if already known
{

	TokenSpell	*spellhunt=&FirstSpell;
	int			compcharnum=0;
	char		compchar;

	newtoken=NULL;

	compchar=newname[compcharnum];

	if ((compchar>='0')&&(compchar<='9'))
		return(FALSE);
	elser
	{
		while  (	(compchar)
		   		&&	(spellhunt->spelling[compchar-32])
		   		&&	(spellhunt->spelling[compchar-32]->tokencode==T_sortentry)
				)
		{
			spellhunt=(TokenSpell*) spellhunt->spelling[compchar-32]->instance;
			compchar=newname[++compcharnum];
		}

		//any one of 3 end conditions may have occured.
	
		if (compchar) compchar-=32;
		if (spellhunt->spelling[compchar]==NULL)	//need to create an entry
			return(FALSE);

		//spelling correct up to now, but end of dictionary.
		//compare onward, but remember current index.

int		fwdcharnum=compcharnum;
char	*targ=spellhunt->spelling[compchar]->tokentext;

		while (newname[fwdcharnum] && (newname[fwdcharnum]==targ[fwdcharnum]))
			fwdcharnum++;

		if (newname[fwdcharnum]==targ[fwdcharnum])
		{
			newtoken=spellhunt->spelling[compchar];
			return(TRUE);
		}

		return(FALSE);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		findspelling
//Author		Robert Slater
//Date			Mon 1 Apr 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
static	Bool	TokenSpell::findspelling(char*	newname,TokenName*	&newtoken)	//returns TRUE if already known
{
	TokenSpell	*spellhunt = &FirstSpell;
	int			compcharnum = 0;
	char		compchar = newname[0];

	if (	(	(compchar >= '0')
		 	 && (compchar<='9'))
		||	(compchar=='-')			)
	{
		newtoken=&statictoken;

		statictoken.tokentext=newname;
		statictoken.usage=U_value;
		statictoken.defined=D_defined;
		statictoken.srcfline=(UWord) currsrcfline;
		statictoken.srcfname=(UWord) currsrcfname;
		statictoken.instance=new IntegerInst;
		
		Assert(statictoken.instance&&"memory!");

		if (compchar=='-')
		{
			statictoken.instance->tokencode=
				statictoken.tokencode=T_nint;

			compchar=*(++newname);

			if (!((compchar>='0')&&(compchar<='9')))
				EmitSysErr("Expecting digit after '-', but found %s",newname);
		}
		else
			statictoken.instance->tokencode = statictoken.tokencode=T_int;


int		base=(compchar=='0')?8:10;
		compcharnum=compchar-'0';
		compchar=*++newname;
		if ((compchar=='x')||(compchar=='X'))
		{
			base=16;
			compchar=*++newname;
		}

		while (compchar)
		{
			if ((compchar>'9') || (compchar<'0'))
				if (compchar<'A')
					EmitSysErr("Number not terminated correctly: %s",statictoken.tokentext);
				else
					compchar=(char) ((compchar&0x1f)+9);
			else
				compchar=(char) (compchar&0x0f);
			if (compchar>=base)
				EmitSysErr("Number not terminated correctly: %s",statictoken.tokentext);
			compcharnum=compcharnum*base+compchar;
			compchar=*++newname;
		}

		statictoken.tokentext=NULL;
		((IntegerInst*) statictoken.instance)->value=compcharnum;
		return(FALSE);
	}
	elser
	{
		while  (	(compchar)
		   		&&	(spellhunt->spelling[compchar-32])
		   		&&	(spellhunt->spelling[compchar-32]->tokencode==T_sortentry)
				)
		{
			spellhunt=(TokenSpell*) spellhunt->spelling[compchar-32]->instance;
			compchar=newname[++compcharnum];
		}
		//any one of 3 end conditions may have occured.
	
		if (	(compchar==0)										//end of source
			&&	(spellhunt->spelling[0])							//entry in dictionary
			&&	(spellhunt->spelling[0]->tokentext[compcharnum]==0)	//that is ended here
			)
		{
			newtoken=spellhunt->spelling[0];		
			return(TRUE);
		}

		if (compchar) compchar-=32;
	
		if (spellhunt->spelling[compchar]==NULL)	//need to create an entry
		{
			newtoken=spellhunt->spelling[compchar] = new TokenName;
			
			Assert(newtoken&&"memory!");

			newtoken->tokentext = safetext(newname);
			newtoken->srcfline = (UWord) currsrcfline;
			newtoken->srcfname = (UWord) currsrcfname;
			return(FALSE);
		}
		//spelling correct up to now, but end of dictionary.
		//compare onward, but remember current index.
	int	fwdcharnum=compcharnum;
	char	*targ=spellhunt->spelling[compchar]->tokentext;
		while (newname[fwdcharnum] && (newname[fwdcharnum]==targ[fwdcharnum]))
			fwdcharnum++;
		if (newname[fwdcharnum]==targ[fwdcharnum])
		{
			newtoken=spellhunt->spelling[compchar];
			return(TRUE);
		}
		//they differ at some point. fwdcharnum says where, but don't matter!
	char	oldspellingletter;
		do
		{	//Make dictionary pages for all common letters. 1st letter is common.
			compcharnum++;
	TokenSpell*
			newspellpage=new TokenSpell;
			Assert(newspellpage&&"memory!");

			oldspellingletter=targ[compcharnum];
			if (oldspellingletter)	oldspellingletter-=32;
			newspellpage->spelling[oldspellingletter]=spellhunt->spelling[compchar];
			spellhunt->spelling[compchar]=new TokenName;
			Assert(spellhunt->spelling[compchar]&&"memory!");

			spellhunt->spelling[compchar]->tokentext=safetext(newname);
			spellhunt->spelling[compchar]->tokencode=T_sortentry;
			spellhunt->spelling[compchar]->srcfname=0;
			spellhunt->spelling[compchar]->srcfline=0;
			spellhunt->spelling[compchar]->instance=newspellpage;

			spellhunt=newspellpage;
			compchar=newname[compcharnum];
			if (compchar) compchar-=32;
		} while (compchar==oldspellingletter);

		//now, the common letters have been shared. 
		//add newname to current spellhunt
		spellhunt->spelling[compchar]=newtoken=new TokenName;
		Assert(newtoken&&"memory!");

		spellhunt->spelling[compchar]->tokentext=safetext(newname);
		spellhunt->spelling[compchar]->tokencode=T_unknown;
		spellhunt->spelling[compchar]->srcfline=(UWord) currsrcfline;
		spellhunt->spelling[compchar]->srcfname=(UWord) currsrcfname;

		return(FALSE);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		safetext
//Author		Robert Slater
//Date			Tue 2 Apr 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
char*	TokenSpell::safetext(char* oldtext)
{
 	if (oldtext!=wordbuff)
		return(oldtext);
char*
	retval=new char [strlen(oldtext)+1];
	Assert(retval&&"Memory!");
	strcpy(retval,oldtext);
	return(retval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		findspelling
//Author		Robert Slater
//Date			Mon 1 Apr 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
static	Bool	TokenSpell::findspelling(file	ifile,TokenName*	&newtoken)	//returns TRUE if already known
{
	return(findspelling(getword(ifile),newtoken));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		addspelling
//Author		Robert Slater
//Date			Mon 1 Apr 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
static	void	TokenSpell::addspelling(TokenInit tokentoadd)
{
	TokenName	*newtoken;

	currsrcfline++;

	if (findspelling(tokentoadd.tokentext,newtoken))
		EmitSysErr("Already in dictionary: (%s) ",tokentoadd.tokentext);

	newtoken->usage=tokentoadd.usage;
	newtoken->tokencode=tokentoadd.tokencode;
	newtoken->defined=D_defined;
	newtoken->instance=NULL;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		addfixedspellings
//Author		Robert Slater
//Date			Mon 1 Apr 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
static	void	TokenSpell::addfixedspellings(TokenInit	*fixedtokens)
{
	TokenInit	*newtoken = fixedtokens;

	while (newtoken->tokentext[0])
		addspelling(*(newtoken++));
}

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
Bool	TokenSpell::stripwhite(file	ifile)
{
	char c;

	for(;;)
	{
		if (feof(ifile))
			return (FALSE);

		c = (char) fgetc(ifile);

		if (feof(ifile))
			return (FALSE);

		if (c=='/')
		{
			if (feof(ifile))
				return (FALSE);

			c='\n';

			while (fgetc(ifile)!=c)		//comments: single slash - to end of line
				if (feof(ifile))
					return (FALSE);
		}

string	p1=whitechars;

		if (c=='\n')
			currsrcfline++;
		else
			while ((c!=*p1) && *p1) p1++;
	breakif (*p1==0);
	}

	if (feof(ifile))
		return (FALSE);

 	ungetc(c,ifile);

	return(TRUE);
}

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
static	string	TokenSpell::getword(file	ifile)
{
	//2 stages to getting a word:
	//	1) leading white removal
	//	2) copy to terminator
	//1) leading white removal

	char 	c;
	string	myword = NULL;

	if (!stripwhite(ifile))
		return(NULL);
	elser
	{
	 	c=(char) fgetc(ifile);
string 	outbuf=wordbuff;
		myword=outbuf;
		//test for punctuation (ok... spc/tab in there as well!)
string	p1=endchars;

		while ((c!=*p1) && *p1)
			p1++;

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
				*(outbuf++)=c;
				*outbuf=0;		//handle early return for eof
				c=(char) fgetc(ifile);
				//EOF during a word read is not an error, really
				if (feof(ifile))
					return (myword);

string			p1=endchars;

				while ((c!=*p1) && *p1)
					p1++;

			breakif (*p1);
			}
			ungetc(c,ifile);
			return (myword);
		}
	}
}




