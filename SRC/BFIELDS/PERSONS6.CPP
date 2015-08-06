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
//Filename       persons6.cpp
//System
//Author         Jim Taylor
//Date           Wed 23 Jul 1997
//Description    ENUM header file reading...
//------------------------------------------------------------------------------
#include	"stdlib.h"
#include	"dosdefs.h"
#include	"fstream.h"

#include	"bfenum.h"

#include	"readenum.h"

#define		UP_ONE_LEVEL

EnumStuff	IEnumStuff;

char*		EnumStuff::listcmpnames[30]=
{	"Angle","UIDBand","Shape","Action","Side","Type","Duty","MoveCode",
	"Skill","Morale","Character","Int","PaintScheme","Squadron","Formation","UniqueID","FileNum",
	0
};

int			EnumStuff::listcmp2listname[30];
EnumCtrl	EnumStuff::listentries[30];

EnumCtrl::EnumCtrl()
{
	min=0x7fffffff;
	max=0;
	sillymax=0;
	links=NULL;
	arr=NULL;
}

EnumCtrl::~EnumCtrl()
{
	delete links;
	delete arr;
}
Bool	EnumCtrl::Add(int i,char* s)
{
	if (arr)
		if (i<max && i>=min)
		{
			Strcpy(arr[i-min].name,s);//,enumeltnamelen);
			return	TRUE;
		}
		else
			return FALSE;
	else
	{
		enumlinkelt**	tmp=&links;
		while (*tmp && tmp[0]->value<=i)
        {
        	if (tmp[0]->value==0xdbf)
            	tmp=tmp;
			tmp=&tmp[0]->next;
        }
		if (tmp==&links)
			min=i;
		if (!*tmp)
		{
			max=sillymax;
			sillymax=i;
		}
		enumlinkelt* t2=new	enumlinkelt;
        if (t2==NULL)
        	exit(1);
		Strcpy(t2->name,s);//,enumeltnamelen);
		t2->value=i;
		t2->next=tmp[0];
		tmp[0]=t2;
		return TRUE;
	}
}
char*	EnumCtrl::Translate(int i)
{
	if (i<min || i>sillymax)
		return NULL;
	if (arr)
		if (arr[i-min].name[0])
			return	(arr[i-min].name);
		else
			return NULL;
	else
	{
		enumlinkelt* t2=links;
		while (t2 && t2->value<i)
			t2=t2->next;
		if (t2 &&t2->value==i)
			return	t2->name;
		else
			return NULL;
	}
}

int	EnumCtrl::Translate(char* name)
{
	char	name2[enumeltnamelen];
	Strcpy(name2,name);//,enumeltnamelen);
	if (arr)
		for (int i=max-min;i>=0;i--)
			if (    arr[i].name[0]
				&&	(int&)arr[i].name[0]==(int&)name2[0]
				&&	(int&)arr[i].name[4]==(int&)name2[4]
				&&	(int&)arr[i].name[8]==(int&)name2[8]
				&&	(int&)arr[i].name[12]==(int&)name2[12]
                &&	(int&)arr[i].name[16]==(int&)name2[16]
				)
				return(i+min);
			else;
	else
		for (enumlinkelt* t2=links;t2;t2=t2->next)
			if (    t2->name[0]
				&&	(int&)t2->name[0]==(int&)name2[0]
				&&	(int&)t2->name[4]==(int&)name2[4]
				&&	(int&)t2->name[8]==(int&)name2[8]
				&&	(int&)t2->name[12]==(int&)name2[12]
                &&	(int&)t2->name[16]==(int&)name2[16]
				)
				return(t2->value);
			else;
	return(0x80000000);
}

Bool	EnumCtrl::Optimise(int breakeven)
{
	int	usemax=sillymax;
	if (sillymax>4*max)
		usemax=max;
	else
		max=usemax;
	if (arr)
		return TRUE;
	int	totelts=0;
	int	lastval=0x80000000;
	for (enumlinkelt* t2=links;t2;t2=t2->next)
	{
//		if (t2->value==lastval)
  //		return FALSE;
		totelts++;
	//	lastval=t2->value;
	}
	if (usemax-min>40000000 || totelts*100<(usemax-min)*breakeven)
		return (FALSE);
	arr=new enumarrelt[1+usemax-min];
	lastval=min;
    arr[0].name[0]=0;
	if (usemax==sillymax)
		for (enumlinkelt* t2=links;t2;t2=t2->next)
		{
			while (lastval<t2->value)
				arr[(lastval++)-min].name[0]=0;
			if (t2->value==lastval)
				Strcpy(arr[(lastval++)-min].name,t2->name);//,enumeltnamelen);
			else
				if	(links==NULL)
					return(FALSE);
		}
	else
		for (enumlinkelt* t2=links,*t3=t2->next;t3;t3=(t2=t3)->next)
		{
			while (lastval<t2->value)
				arr[(lastval++)-min].name[0]=0;
			if (t2->value==lastval)
				Strcpy(arr[(lastval++)-min].name,t2->name);//,enumeltnamelen);
		}

	delete links;
	links=NULL;
	return TRUE;
}


void	EnumStuff::readenums()
{
	readfilelist("..\\bfields\\initial.res");
	readfilesfromlist();
        int i;
	for (i=0;listnames[i][0];i++)
	{
		listentries[i].Optimise();
		for (int j=0;listnames[j][0];j++)
			if (!strcmp(listnames[j],listcmpnames[i]))
				 listcmp2listname[i]=j;
	}
        convertstrings("SNIP","T_",GetList(ENUM_UniqueID),"..\\english\\uidnames.txt",i++,ENUM_UIDtitle);
		convertstrings("SNIP","D_",GetList(ENUM_UniqueID),"..\\english\\uiddescs.txt",i++,ENUM_UIDdesc);
		//to start a new shapenum.g modify line in bfields\resource.h
		convertstrings("SNIP","T_SHP_",GetList(ENUM_Shape),"..\\english\\shape.txt",i++,ENUM_ShapeTitle);

//		savestrings("SNIP\tT_","\t=\t\"","\";\n",GetList(ENUM_UniqueID),"titles.tst",GetList(ENUM_UIDtitle));
  //		savestrings("SNIP\tD_","\t=\t\"","\";\n",GetList(ENUM_UniqueID),"descs.tst",GetList(ENUM_UIDdesc));

}
void	EnumStuff::Strcpy(char*t,char*s)
{
	if (::strlen(s)>=35)//EnumCtrl::enumeltnamelen)
    	t=t;
	::strncpy(t,s,35);
}

void	EnumCtrl::Strcpy(char*t,char*s)
{
	if (::strlen(s)>=36)//EnumCtrl::enumeltnamelen)
		t=t;
	::strncpy(t,s,36);
}
void	EnumStuff::readfilelist(char* name)
{
	ifstream	f=name;
	f.setf(f.skipws);
	char	wordbuff[40];
	do{
		f>>wordbuff;
	}while (wordbuff[0]!='{');
	int	currname=0;
	forever
	{
		f>>wordbuff;
		if ((int&) wordbuff[0] == (int&)*"Type")
		{
			#ifdef	UP_ONE_LEVEL
			wordbuff[0]=wordbuff[1]='.';
			wordbuff[2]='\\';
			f>>(wordbuff+3);
			#else
			f>>wordbuff;		//fix 'cos in wrong directory...
			#endif
			wordbuff[strlen(wordbuff)-1]=0;
			readenumlist(wordbuff);
		}
		else
		if	((int&) wordbuff[0] == (int&)*"enum")
		{
			#ifdef	UP_ONE_LEVEL
			wordbuff[0]=wordbuff[1]='.';
			wordbuff[2]='\\';

			f>>(wordbuff+3);
			#else
			f>>wordbuff;		//fix 'cos in wrong directory...
			#endif
			if (wordbuff[strlen(wordbuff)-1]==',')
				wordbuff[strlen(wordbuff)-1]=0;
			Strcpy(fnames[currname++],wordbuff);

		}
		else
			break;
	};

//	#ifdef	UP_ONE_LEVEL
//	strcpy(fnames[currname],"..\\h\\uniqueid.h");
//	#else
//	strcpy(fnames[currname],"h\\uniqueid.h");
//	#endif
	Strcpy(fnames[currname++],"..\\h\\files.g");

	fnames[currname][0]=0;
}

void	EnumStuff::readenumlist(char* name)
{
	ifstream	f=name;
	f.setf(f.skipws);
	char	wordbuff[40];
	char	wordbuffe[40];
	do{
		f>>wordbuff;
	}while (wordbuff[0]!='{');
	int currname=0;
	int	currlist=0;
	Strcpy(enumnames[currname],"FileNum");
	Strcpy(listnames[currlist],"FileNum");
	enumname2listname[currname++]=currlist++;

	forever
	{
		f>>wordbuff;
		if (wordbuff[0]=='/')
		{
			while (f.get()!='\n')	{}
			continue;
		}

		if (wordbuff[0]=='}')
			break;
		f>>wordbuffe;
		if (wordbuffe[strlen(wordbuffe)-1]==',')
			wordbuffe[strlen(wordbuffe)-1]=0;
		Strcpy(enumnames[currname],wordbuffe);
		int	i;
		for(i=0;i<currlist;i++)
			if (!strcmp(listnames[i],wordbuff))
				break;
		Strcpy(listnames[i],wordbuff);
		enumname2listname[currname]=i;
		if (i==currlist)
			currlist++;
		currname++;
	}
	Strcpy(enumnames[currname],"UniqueID");
	Strcpy(listnames[currlist],"UniqueID");
	enumname2listname[currname++]=currlist++;
	enumnames[currname][0]=0;
	listnames[currlist][0]=0;
}


void	EnumStuff::readfilesfromlist()
{
	for (int currfile=0;fnames[currfile][0];currfile++)
	{
		ifstream f(fnames[currfile]);
		f.setf(f.skipws);
		char wordbuff[500];
		do
		{
			do
			{
				f>>wordbuff;
				while (wordbuff[0]=='/')
				{
					while (f.get()!='\n')	{}
//				f.ignore(-1,'\n');
					f>>wordbuff;
				}
			}while (	!f.eof()
					&& 	*(int*)wordbuff!=*(int*)"enum"
					&& 	*(int*)wordbuff!=*(int*)"cons"
					);

			if (f.eof())
				break;
			int	wasenum=*(int*)wordbuff;


			f.ipfx(0);
			char	ch=f.get();
			int i;
			for (i=0;ch>' ' && ch!='{';i++)
			{
				wordbuff[i]=ch;
				ch=f.get();
			}
			wordbuff[i]=0;
			while (ch<=' ' || ch=='{')
				ch=f.get();
			f.putback(ch);
			int len=strlen(wordbuff)-1;
			while(wordbuff[len]=='{'
				|| wordbuff[len]==' '
				|| wordbuff[len]=='\t'
				|| wordbuff[len]=='\n'
				)	len--;
			wordbuff[len+1]=0;
			int	enumname=0;
			while (		enumnames[enumname][0]
					&&	strcmp(wordbuff,enumnames[enumname])	)
					enumname++;
			if (enumnames[enumname][0])
				if (wasenum==*(int*)"enum")
					listentries[enumname2listname[enumname]].readenumfromfile(f);
				else
					listentries[enumname2listname[enumname]].readconstfromfile(f);

		}while (!f.eof());
	}
}

void	EnumCtrl::readconstfromfile(ifstream& f)
{
	char	wordbuff[500];
	int i;
	f>>wordbuff;
	char ch=f.get();
	while(ch!='=')
		ch=f.get();
	ch=f.get();
	while(ch<=' ')
		ch=f.get();
	if (ch=='(')
	{
		while(ch!=')')
			ch=f.get();
		ch=f.get();
		while(ch<=' ')
			ch=f.get();
	}
	f.putback(ch);
	if ((ch>='0' && ch<='9') || ch=='-')
		f>>i;
	else
	{
		char	wordbuff[80];
		int j=0;
		while (ch>=' ' && ch!='}' && ch!=',')
			wordbuff[j++]=ch=f.get();
		wordbuff[j-1]=0;
		i=Translate(wordbuff);
	}
	Add(i,wordbuff);
}

void	EnumCtrl::readenumfromfile(ifstream& f)
{
	char	wordbuff[500];
	int i=-1;
	do
	{
		char ch=f.get();
		while(!f.eof() && (ch<=' ' || ch=='{'))
			ch=f.get();

		if (f.eof() || ch=='}')
			break;
		{
		int chind=0;
		wordbuff[chind]=ch;
		while(ch>' ' && ch!='=' && ch!=',' && ch!='}')
			wordbuff[++chind]=ch=f.get();
		wordbuff[chind]=0;
		}

		if (!strcmp("#include",wordbuff))
		{
			while (ch!='<' && ch!='"')
				ch=f.get();
			i=2;
			wordbuff[0]='h';wordbuff[1]='\\';
			#ifdef	UP_ONE_LEVEL
			i=5;		//cludge for wrong directory...
			wordbuff[0]=wordbuff[1]='.';
			wordbuff[2]='\\';wordbuff[3]='h';wordbuff[4]='\\';
			#endif
			wordbuff[i]=ch=f.get();
			while (ch!='>' && ch!='"')
				wordbuff[++i]=ch=f.get();
			wordbuff[i]=0;
			ifstream f(wordbuff);
			readenumfromfile(f);
			continue;
		}
		else
		if (wordbuff[0]=='/' || wordbuff[0]=='#')
		{
			while (ch!='\n')	{ch=f.get();}
//			f.ignore(-1,'\n');
			continue;
		}

		while(ch!='=' && ch!=',' && ch!='}')
			ch=f.get();
		if (ch=='=')
		{
			ch=f.get();
			while(ch<=' ')
				ch=f.get();
			f.putback(ch);
			if ((ch>='0' && ch<='9') || ch=='-')
			{
				f>>i;
				ch=f.get();
			}
			else
			{
				char	wordbuff[80];
				int j=0;
				while (ch>=' ' && ch!='}' && ch!=',')
					wordbuff[j++]=ch=f.get();
	  			wordbuff[j-1]=0;
				i=Translate(wordbuff);
			}
		}
		else
			i++;
		if (*(UWord*)wordbuff!=*(UWord*)"UI"		//discard UI_nnn
		||	wordbuff[2]!='_'
		||	wordbuff[3]<'0' || wordbuff[3]>'9')
			Add(i,wordbuff);
		while(ch<=' ' && !f.eof())
			ch=f.get();
		wordbuff[0]=ch;
	}while (!f.eof() && wordbuff[0]!='}');
}
//////////////////////
//
//   convertstrings: converts any strings in the file into indexable tokens
//	keyword:	preceeds the token name
//	leadchars:	are stripped from the token name
//	tokenlist:	should contain the token name - returns the corresponding index value
//	fname:		the file to search
//	newentry:	the actual list entry to create
//	tokenentry:	the indirect list entry to create
//
//////////////////////
void	EnumStuff::convertstrings(char*keyword,char*leadchars,EnumCtrl& tokenlist,char*fname,int newentry,int tokenentry)
{
	EnumStuff::listcmp2listname[tokenentry]=newentry;
	ifstream f(fname);
    if (f.bad())
    	return;
	char	wordbuff[500];
	int i=-1;
	forever
	{
		char ch=f.get();
		while(!f.eof() && (ch<=' '))
			ch=f.get();

		if (f.eof())
			break;
		int j=0;
        wordbuff[j++]=ch;
		while (ch>=' ')
			wordbuff[j++]=ch=f.get();
		wordbuff[j-1]=0;
		if (strcmp(wordbuff,keyword))
         	continue;

		while(!f.eof() && (ch<=' '))
			ch=f.get();

		if (f.eof())
			break;

		j=0;
        if (leadchars)
	        while (leadchars[j])
    	    {
        		if (ch!=leadchars[j++])
            		break;
	            ch=f.get();
    	    }
        if (leadchars && leadchars[j])
        	continue;
        j=0;
		wordbuff[j++]=ch;
        while (ch>=' ')
			wordbuff[j++]=ch=f.get();
		wordbuff[j-1]=0;

        int val=tokenlist.Translate(wordbuff);
        if (val==0xc58)
        	val=val;
        while (ch!='"' && ch!='\'')
	            ch=f.get();
        j=0;
        do
        	wordbuff[j++]=ch=f.get();
        while (ch!='"' && ch!='\'');
        wordbuff[j-1]=0;
        if (val!=ENABLE_COMPLEX_VAL)
	        listentries[newentry].Add(val,wordbuff);
	}
}
void	EnumStuff::savestrings(char* prestring,char* midstring,char* poststring,EnumCtrl& tokenlist,char*fname,EnumCtrl& textlist)
{
	ofstream f(fname);
	for (int i=tokenlist.min;i<tokenlist.max;i++)
    {
    	char	*token,*text;
        if (i==0xdfd)
        	i=i;
        token=tokenlist.Translate(i);
        text=textlist.Translate(i);
		if (token && text)
        {
        	f	<<prestring
                <<token
                <<midstring
                <<text
                <<poststring;
        }
    }
}


