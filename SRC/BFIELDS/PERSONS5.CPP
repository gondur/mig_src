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
//Filename       persons5.cpp
//System         
//Author         Jim Taylor
//Date           Wed 23 Jul 1997
//Description    Mission editor save functionality
//------------------------------------------------------------------------------
#include <vcl\vcl.h>

	#include	"dosdefs.h"
	#include	"files.g"

#include	"sqinfo.h"
#include	"memain.h"
//#include	"choosebf.h"

	#include	<stdio.h>
	//DON'T WRITE INCLUDE FILES HERE, PUT THEM IN BFCOMMON
	#define	TEXTREF_Included
	#include	"text.h"
//	#include	"error.h"
	#include	"mymath.h"
	#include	"worldinc.h"
    
	#include	"bfnumber.h"

//	#include	"bfcommon.h"
	#include	"bfnumber.h"	//intensional double include
	#include	"readenum.h"
    #include	"persons2.h"
   #include "globals.h"
   #include	"fileman.h"
////////////////////////////////////////////////////////////////////
//
// Writing battlefields... time for persons5 methinks!
//

int	fputs(FILE* f,char* s)
{

	return(fputs(s,f));
}
int	fputc(FILE* f,char s)
{
	return(fputc(s,f));
}

void	fputnl(FILE* f,int & going)
{
	if (going)
		fputs(f,",\n");
	going++;
}
void	fputtabs(FILE* f,int t)
{
	while(t--)
		fputc('\t',f);
}

//
//
//
//
inline bool operator==(EnumListNames a,EnumListNames b) {return int(a)==int(b);}
void	EventVal::Save(FILE* f,char* fname,int tabs,EnumListNames e)
{

	if (complex)
		complex->Save(f,fname,tabs,e);
	else
		if (e==ENUM_RealInt)
			fprintf(f,"\t%i",value);
		else
			if (e==ENUM_UniqueID)
			{
				char* tmp=GetList(ENUM_UniqueID).Translate(value);
				if (tmp)
					fprintf(f,"\t%s",tmp);
				else
				{
					info_base* I=*Persons2::ConvertPtrUID((UniqueID)value);
					if (I)
						if (!I->bfieldindex)
							fprintf(f,"\t0x%04x",value);
						else
							fprintf(f,"\t%s_%04x",fname,value);
					else
					{
						Application->MessageBox(
							"Object referenced in event has been deleted!\n"
							"That field is now undefined. Sorry!","Error:",MB_OK);
						value=ENABLE_COMPLEX_VAL;
						fprintf(f,"\t000000000 //Error value!!!\n");
					}
				}
			}
			else
			{
				char* tmp=GetList(e).Translate(value);
				if (tmp)
					fprintf(f,"\t%s",tmp);
				else
					fprintf(f,"\t%i",value);
			}
}

void	GlobRefExpr::Save(FILE* f,char* fname,int tabs,EnumListNames)
{

//////		char buff[30];
//////		int text ;//////= ((GlobalsInfo*)BFieldGlobalTable[grind].reference)->text;
//////		LoadString(HInstance,text,buff,sizeof(buff));
		fputs(f,"\t");
		fputs(f,
			((GlobalsInfo*)BFieldGlobalTable[globrefind].reference)
			->identifier);
}

void	UIDExpr::Save(FILE* f,char* fname,int tabs,EnumListNames)
	{
		if (val.complex)
			val.Save(f,fname,tabs,ENUM_UniqueID);
		else
		{
			char* tmp=GetList(ENUM_UniqueID).Translate(val);
			if (tmp)
				fprintf(f,"\t%s",tmp);
			else
			{
				info_base* I=*Persons2::ConvertPtrUID((UniqueID)val.value);
				if (I)
					if (!I->bfieldindex)
						fprintf(f,"\t0x%04x",val.value);
					else
						fprintf(f,"\t%s_%04x",fname,val.value);
				else
				{
					Application->MessageBox(
						"Object referenced in event has been deleted!\n"
						"That field is now undefined. Sorry!","Error:",MB_OK);
					val.value=ENABLE_COMPLEX_VAL;
					fprintf(f,"\t000000000 //Error value!!!\n");
				}

			}
		}

	}

void	RndExpr::Save(FILE* f,char* fname,int tabs,EnumListNames e)
	{
		fputc(f,'\n');
		fputtabs(f,tabs);
		fputs(f,"{Random");
		if (base.value==0)
			base.Save(f,fname,tabs+1);
		else
			base.Save(f,fname,tabs+1,e);
		if (maxsteps.Evaluate()!=ENABLE_COMPLEX_VAL)
		{
			fputc(f,',');
			if (maxstepsiscallertype)
				maxsteps.Save(f,fname,tabs+1,e);
			else
				maxsteps.Save(f,fname,tabs+1);
		}
		if (stepsize.Evaluate()!=ENABLE_COMPLEX_VAL)
		{
			fputc(f,',');
			if (maxstepsiscallertype)
				stepsize.Save(f,fname,tabs+1);
			else
				stepsize.Save(f,fname,tabs+1,e);
		}
		fputc(f,'}');
	}
void	SelExpr::Save(FILE* f,char* fname,int tabs,EnumListNames e)
	{
		fputc(f,'\n');
		fputtabs(f,tabs);
		fputs(f,"{Select");
		if (base.value==0)
			base.Save(f,fname,tabs+1);
		else
			base.Save(f,fname,tabs+1,e);
		if (stepsize.Evaluate()!=ENABLE_COMPLEX_VAL)
		{
			fputc(f,',');
			if (stepsiscallertype)
				stepsize.Save(f,fname,tabs+1);
			else
				stepsize.Save(f,fname,tabs+1,e);
		}
		if (steps.Evaluate()!=ENABLE_COMPLEX_VAL)
		{
			fputc(f,',');
			if (stepsiscallertype)
				steps.Save(f,fname,tabs+1,e);
			else
				steps.Save(f,fname,tabs+1);
		}
		fputc(f,'}');
	}
void	ListExpr::Save(FILE* f,char* fname,int tabs,EnumListNames e)
	{
		fputc(f,'\n');
		fputtabs(f,tabs);
		fputs(f,"{List");
		index.Save(f,fname,tabs+1);
		for (int i=0;i<maxentries;i++)
		{
			fputc(f,',');
			fputc(f,'\n');
			fputtabs(f,tabs);
			entries[i].Save(f,fname,tabs+1,e);
		}
		fputc(f,'\n');
		fputtabs(f,tabs);
		fputc(f,'}');
	}
void	ListFormExpr::Save(FILE* f,char* fname,int tabs,EnumListNames e)
	{
		fputc(f,'\n');
		fputtabs(f,tabs);
		fputs(f,"{List");
		for (int i=0;i<maxentries;i++)
		{
			if (i)
				fputc(f,',');
			fputc(f,'\n');
			fputtabs(f,tabs);
			entries[i].Save(f,fname,tabs+1,e);
		}
		fputc(f,'\n');
		fputtabs(f,tabs);
		fputc(f,'}');
	}
void	WorldExpr::Save(FILE* f,char* fname,int tabs,EnumListNames)
//	EventVal	uniqueID;		Assume Position has already been written
//	EventVal	delta;
//	EventVal	rotate;
	{
		fputc(f,'\n');
		fputtabs(f,tabs);
		fputc(f,'{');
		int doneone=0;
		if (uniqueID.complex)
		{
			fputc(f,'\n');
			fputtabs(f,tabs+1);
			fputs(f,"Posn");
			uniqueID.Save(f,fname,tabs+1,ENUM_UniqueID);
			doneone=1;
		}
		else if (uniqueID.value!=ENABLE_COMPLEX_VAL)
		{
			fputs(f,"Posn");
			UIDExpr tmp;
			tmp.val=uniqueID.value;
			tmp.Save(f,fname,tabs+1,ENUM_UniqueID);
			doneone=1;
		}

		if (delta.complex)
		{
			if (doneone)	//relative
				fputc(f,',');
			fputc(f,'\n');
			fputtabs(f,tabs+1);
			if (deltaisabs || !doneone)				
				fputs(f,"Abs");
			else	
				fputs(f,"Rel");
			delta.Save(f,fname,tabs+1);
		}
		if (rotate.complex)
			{
				fputc(f,',');
				fputc(f,'\n');
				fputtabs(f,tabs+1);
				fputs(f,"Rel");
				rotate.Save(f,fname,tabs+1);
			}
		fputc(f,'\n');
		fputtabs(f,tabs);
		fputc(f,'}');

	}
void	XyzExpr::Save(FILE* f,char* fname,int tabs,EnumListNames)
	{
		fputc(f,'\n');
		fputtabs(f,tabs);
		fputs(f,"{\t");
		int doneone=0;
		for (int r=0;r<3;r++)
		{
			if (ArgLine(r) && ArgLine(r)->Evaluate() && ArgLine(r)->Evaluate()!= ENABLE_COMPLEX_VAL)
			{
				if (doneone)
				{
					fputs(f,",\n");
					fputtabs(f,tabs+1);
				}
				fputc(f,FieldName(r)[0]);
				ArgLine(r)->Save(f,fname,tabs+1);
				doneone++;
			}
		}
		if (!doneone)
			fputs(f,"Y	0");
		fputc(f,'\n');
		fputtabs(f,tabs);
		fputs(f,"}");
	}
void	RotExpr::Save(FILE* f,char* fname,int tabs,EnumListNames)
	{
		fputc(f,'\n');
		fputtabs(f,tabs);
		fputc(f,'{');
		fputc(f,'\n');
		int doneone=0;
		if (icpt.complex)
		{
			fputc(f,'\n');
			fputtabs(f,tabs+1);
			fputs(f,"Intercept");
			icpt.Save(f,fname,tabs+1);
			doneone++;
		}
		if (hdg.Evaluate()!=ENABLE_COMPLEX_VAL)
		{
			if (doneone++)
				fputc(f,',');
			fputc(f,'\n');
			fputtabs(f,tabs+1);
			fputs(f,"Heading");
			hdg.Save(f,fname,tabs+1);
		}
		if (pitch.Evaluate()!=ENABLE_COMPLEX_VAL)
		{
			if (doneone++)
				fputc(f,',');
			fputc(f,'\n');
			fputtabs(f,tabs+1);
			fputs(f,"Pitch");
			pitch.Save(f,fname,tabs+1);
		}
		if (range.Evaluate()!=ENABLE_COMPLEX_VAL)
		{
			if (doneone++)
				fputc(f,',');
			fputc(f,'\n');
			fputtabs(f,tabs+1);
			fputs(f,"Range");
			if (rangeispercent)
				fputs(f,"Percent");
			range.Save(f,fname,tabs+1);
//			doneone++;
		}
		fputc(f,'\n');
		fputtabs(f,tabs);
		fputs(f,"}");
	}

void	IcptExpr::Save(FILE* f,char* fname,int tabs,EnumListNames)
	{
		fputc(f,'\n');
		fputtabs(f,tabs);
		fputc(f,'{');
			fputc(f,'\t');
			fputs(f,"Posn");
		int doneone=0;
		if (objA.complex)
		{
			objA.Save(f,fname,tabs+1,ENUM_UniqueID);
			doneone++;
		}
		else
		{
			UIDExpr tmp;
			tmp.val=objA.value;
			tmp.Save(f,fname,tabs+1,ENUM_UniqueID);
		}
		fputs(f,",\n");
		fputtabs(f,tabs);
			fputc(f,'\t');
			fputs(f,"Posn");
		if (objB.complex)
		{
			objB.Save(f,fname,tabs+1,ENUM_UniqueID);
//			doneone++;
		}
		else
		{
			UIDExpr tmp;
			tmp.val=objB.value;
			tmp.Save(f,fname,tabs+1,ENUM_UniqueID);
		}
		fputc(f,'\n');
		fputtabs(f,tabs);
		fputs(f,"}");
	}

//
//
//
//
bool	operator ==(UniqueID a,UniqueID b)	{return int(a)==int(b);}
EventLogPtr	Persons2::eventloglist=NULL,Persons2::TargLog=NULL,Persons2::TruckLog=NULL,Persons2::PlayerLog=NULL;

char outname[100];
void	Persons2::SaveBF(FileNum dirnum,char* fname,char* name,char* comment,bool newfile)
{

	UniqueID	SGtargets[100]={UID_Null};
//	char outname[100];
    char* incpath=outname;
    char* s=FILEMAN.namenumberedfilelessfail(dirnum);
    char* t=outname;
    while (*s && *(ULong*)s!=*(ULong*)"game")
		*t++=*s++;
    if (*s)
    {
    	*(ULong*)t=*(ULong*)"src";
        t+=3;
        s+=4;
        incpath=t+1;
    }
    while (*s)
		*t++=*s++;
    while (*--t!='\\')
    	{}
    t++;
    char* namepart=t;
    s=fname;
    while (*s)
		*t++=*s++;
    *(ULong*)t=*(ULong*)".BFI";
    t+=4;
	*t=0;


	FILE* f;
    if (newfile)
    {
    	char incsub[100];
        for (s=outname,t=incsub;s!=namepart;)
        	*t++=*s++;
        strcpy(t,"subinc.bfi");
    	f=fopen(incsub,"at");
		fprintf(f,"#INCLUDE %s,\n",incpath);
        fclose(f);
    }

	f=fopen(outname,"wt");

//	fprintf(f,"Level\t%i;\n",dirnum/256);

//	sprintf(outname,"..\\USERSRC\\%s\\%s.bfi",dirname,fname);

	for (int uid=0;uid<(int)IllegalBAND;uid++)
	{
		info_base* I=*ConvertPtrUID(UniqueID(uid));
		if (I && (int)I->bfieldindex==currbfindex)
		{
			char*	tmp =  GetList(ENUM_UniqueID).Translate(I->uid.Evaluate());
			if (!tmp)
			switch (I->Status.size)
			{
				case	AIRSTRUCSIZE:
					fprintf(f,"\tAirItem	%s_%04x,\n",fname,I->uniqueID.count);
				break;
				case	MOBILESIZE:
					fprintf(f,"\tGroundItem	%s_%04x,\n",fname,I->uniqueID.count);
				break;
				case	ITEMSIZE:
					fprintf(f,"\tSimpleItem	%s_%04x,\n",fname,I->uniqueID.count);
				break;
				case	WAYPOINTSIZE:
					fprintf(f,"\tWayPoint	%s_%04x,\n",fname,I->uniqueID.count);
				break;
			}
			int i;
			if (I->SGT)
			{
				for (i=0;SGtargets[i]!=UID_Null;i++)
					breakif(SGtargets[i]==I->SGT);
				if (SGtargets[i]==0)
					SGtargets[i]=I->SGT;
			}
		}
	}
	for (int uid=(int)IllegalBAND-1;uid>=0;uid--)
	{
		info_base* I=*ConvertPtrUID(UniqueID(uid));
		if (I && (int)I->bfieldindex==currbfindex)
		{
			char*	tmp =  GetList(ENUM_UniqueID).Translate(I->uid.Evaluate());
			if (tmp)
			switch (I->Status.size)
			{
				case	AIRSTRUCSIZE:
					fprintf(f,"\tAirItem	%s_%04x,\n",fname,I->uniqueID.count);
				break;
				case	MOBILESIZE:
					fprintf(f,"\tGroundItem	%s_%04x,\n",fname,I->uniqueID.count);
				break;
				case	ITEMSIZE:
					fprintf(f,"\tSimpleItem	%s_%04x,\n",fname,I->uniqueID.count);
				break;
				case	WAYPOINTSIZE:
					fprintf(f,"\tWayPoint	%s_%04x,\n",fname,I->uniqueID.count);
				break;
			}
		}
	}
    char fn2[20]={0};
	for (int conv=0;fname[conv];conv++)
    	fn2[conv]=toupper(fname[conv]);
        
	fprintf(f,	"\tBattleField\n"
				"\t{\n"
				"\t\tFileName\tFIL_%i_%s=%s.BF,\n",
				dirnum/256,fn2,fname
			);
	fprintf(f,	"\t\tTitle\t{%s},\n",name);
	fprintf(f,	"\t\tComment\t{%s}\n",comment);
//	fprintf(f,	"\t\tComment\t{%s}",news);
	int	doingitemgrp=0;
	int going=1;
//this call writes out the comment strings... it doesn't output a comma
//	fputnl(f,going);
//	fputc(f,'\t');
//camp tmp	MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].Save(f);
	int sgtcount=0,SGT=0,indent=0;
	do{
		if (SGT)
		{
			fputnl(f,going);
			fputs("\tItemGroup\n\t{\tTarget	",f);
			char* tmp=GetList(ENUM_UniqueID).Translate(SGT);
			if (tmp)
				fputs(tmp,f);
			else
				;;;//serious problems....
			indent=1;
		}
		bool    txtcheck=true;
		int 	uidstart=(int)IllegalBAND-1;
		int		uiddelta=-1;
		int		uidend=-1;
		do		//cludge to allow 2 passes
		{
			for (int uid=uidstart;uid!=uidend;uid+=uiddelta)
			{
				info_base* I=*ConvertPtrUID(UniqueID(uid));
				if (	I
					&&	(int)I->SGT==SGT
					&& (int)I->bfieldindex==currbfindex
					&&	((int)I->uniqueID.count&(-256))!=WayPointBAND
					&&	(bool)GetList(ENUM_UniqueID).Translate(I->uid.Evaluate())==txtcheck
					)
				{
					if (doingitemgrp && (int)I->Status.size!=(int)ITEMSIZE)
						fputs("\n\t\t}",f);
					fputnl(f,going);
					switch (I->Status.size)
					{
						case AIRSTRUCSIZE:
							doingitemgrp=0;
							SaveAirGrp(f,I,fname,2+indent);
						break;
						case MOBILESIZE:
							doingitemgrp=0;
							SaveGrndGrp(f,I,fname,2+indent);
						break;
						case ITEMSIZE:
							if (!doingitemgrp)
								fputs("\t\tItemGroup\n\t\t{\n",f);
							doingitemgrp++;
							SaveItem(f,I,fname,3+indent);
							if (doingitemgrp==200)
							{
								fputs("\n\t\t}",f);
								doingitemgrp=0;
							}
						break;
					}
				}
			}
			uidstart=0;
			uiddelta=+1;
			uidend=(int)IllegalBAND;
			txtcheck=!txtcheck;
		}
		while(!txtcheck);

		if (doingitemgrp)
			fputs("\n\t\t}",f);
		doingitemgrp=0;
		if (SGT)
		{
			fputs("\t}",f);
		}
    }while ((SGT=SGtargets[sgtcount++])!=0);
	fputs("\n\t};\n",f);
	fclose(f);
}

Bool	Persons2::SaveEvents(FILE* f,info_event* E,char* fname,int tabs)
{
	if (E)
	{
		int	going=0;
		while (E)
		{
			if (E->usedsetvals || E->bfields.Evaluate()!=ENABLE_COMPLEX_VAL)
			{
				fputnl(f,going);
				fputtabs(f,tabs);
				fprintf(f,"Event\n");
				fputtabs(f,tabs++);
				fputs(f,"{\n");
				{
					int	going=0;
					char	workbuff[80];
					//FrFighterSq,FrBomberSq,EnFighterSq,EnBomberSq
					if (E->FrFighterSq)
					{
						fputnl(f,going);fputtabs(f,tabs);
						fprintf(f,"Title\t{F%03d}",E->FrFighterSq);
/////////						SquadronDataForm->GetSquadName(E->FrFighterSq,workbuff);
/////////						fputs(f,workbuff);
					}
					if (E->FrBomberSq)
					{
						fputnl(f,going);fputtabs(f,tabs);
						fprintf(f,"Title\t{F%03d}",E->FrBomberSq);
/////////						SquadronDataForm->GetSquadName(E->FrBomberSq,workbuff);
/////////						fputs(f,workbuff);
					}
					if (E->EnFighterSq)
					{
						fputnl(f,going);fputtabs(f,tabs);
						fprintf(f,"Title\t{E%03d}",-E->EnFighterSq);
/////////						SquadronDataForm->GetSquadName(E->EnFighterSq,workbuff);
/////////						fputs(f,workbuff);
					}
					if (E->EnBomberSq)
					{
						fputnl(f,going);fputtabs(f,tabs);
						fprintf(f,"Title\t{E%03d}",-E->EnBomberSq);
/////////						SquadronDataForm->GetSquadName(E->EnBomberSq,workbuff);
/////////						fputs(f,workbuff);
					}


	//	usedsetvals=allsetvals=0;}
	//	EventVar	setvals[MAXEVENTS];
	//	EventVal	starth;
	//	EventVal	startm;
	//	EventVal	starts;
	//	EventVal	winh;
	//	EventVal	winm;
	//	EventVal	wins;
	//	EventVal	bfields;
					if (E->starth.Evaluate()!=ENABLE_COMPLEX_VAL
						||	E->startm.Evaluate()!=ENABLE_COMPLEX_VAL
						||	E->starts.Evaluate()!=ENABLE_COMPLEX_VAL
						)
					{
						fputnl(f,going);
						fputtabs(f,tabs);fputs(f,"Start\n");
						fputtabs(f,tabs++);fputs(f,"{\n");
						{
							int going=0;
							if (E->starth.Evaluate()!=ENABLE_COMPLEX_VAL)
								{fputnl(f,going);fputc(f,'H');SaveNumber(f,E->starth,fname,tabs);}
							if (E->startm.Evaluate()!=ENABLE_COMPLEX_VAL)
								{fputnl(f,going);fputc(f,'M');SaveNumber(f,E->startm,fname,tabs);}
							if (E->starts.Evaluate()!=ENABLE_COMPLEX_VAL)
								{fputnl(f,going);fputc(f,'S');SaveNumber(f,E->starts,fname,tabs);}
						}
						fputc(f,'\n');
						fputtabs(f,--tabs);fputc(f,'}');
					}
					if (E->winh.Evaluate()!=ENABLE_COMPLEX_VAL
						||	E->winm.Evaluate()!=ENABLE_COMPLEX_VAL
						||	E->wins.Evaluate()!=ENABLE_COMPLEX_VAL
						)
					{
						fputnl(f,going);
						fputtabs(f,tabs);fputs(f,"Window\n");
						fputtabs(f,tabs++);fputs(f,"{\n");
						{
							int going=0;
							if (E->winh.Evaluate()!=ENABLE_COMPLEX_VAL)
								{fputnl(f,going);fputc(f,'H');SaveNumber(f,E->winh,fname,tabs);}
							if (E->winm.Evaluate()!=ENABLE_COMPLEX_VAL)
								{fputnl(f,going);fputc(f,'M');SaveNumber(f,E->winm,fname,tabs);}
							if (E->wins.Evaluate()!=ENABLE_COMPLEX_VAL)
								{fputnl(f,going);fputc(f,'S');SaveNumber(f,E->wins,fname,tabs);}
						}
						fputc(f,'\n');
						fputtabs(f,--tabs);fputc(f,'}');
					}
//					fputnl(f,going);
					for (int i=0;i<E->usedsetvals;i++)
						if (E->setvals[i].Evaluate()!=ENABLE_COMPLEX_VAL)
						{
							fputnl(f,going);
							fputtabs(f,tabs);fputs(f,"Setval\t{");
//							fputs(f,"<vname>");	//use setvals[i].index to find name of var
							fputs(f,
						((GlobalsInfo*)BFieldGlobalTable[E->setvals[i].index].reference)
							->identifier);
							fputc(f,',');
//							SaveNumber(f,E->setvals[i],fname,tabs+1,ENUM_RealInt); //get proper equatename
							SaveNumber(f,E->setvals[i],fname,tabs+1,
						((GlobalsInfo*)BFieldGlobalTable[E->setvals[i].index].reference)
							->processor->enumtype);
							if (E->setvals[i].complex)
								{fputc(f,'\n');fputtabs(f,tabs);}
							fputc(f,'}');
						}
					if (E->bfields.Evaluate()!=ENABLE_COMPLEX_VAL)
					{
						fputnl(f,going);
						fputtabs(f,tabs);fputs(f,"Event");
						SaveNumber(f,E->bfields,fname,tabs,ENUM_Files);
					}
				}
				fputc(f,'\n');
				fputtabs(f,--tabs);
				fputc(f,'}');
			}
			E=E->next;
		}
		if (going)
			return TRUE;
	}
	return FALSE;
}

void	Persons2::SaveAirGrp(FILE* f,ItemBasePtr B,char* fname,int tabs)
{
	info_airgrp*	G=*B;
 //	PreSaveRoute(f,G->wpref,fname,tabs);
	fputtabs(f,tabs);
	fprintf(f,"AirGroup\n");
	fputtabs(f,tabs);
	fputs(f,"{\n");
	tabs++;
	int	going=0;

	if (G->position.complex)
	{
		SavePosition(f,G->position,fname,tabs);
		going++;
	}
	if (G->wpref)
	{
		fputnl(f,going);
		SaveRoute(f,G->wpref,fname,tabs);
	}
	if (G->inform.Evaluate()!=ENABLE_COMPLEX_VAL)
	{
		fputnl(f,going);
		fputtabs(f,tabs);
		fputs(f,"NumInForm\t");
		SaveNumber(f,G->inform,fname,tabs);
	}
	if (G->inwing.Evaluate()!=ENABLE_COMPLEX_VAL)
	{
		fputnl(f,going);
		fputtabs(f,tabs);
		fputs(f,"NumInWing\t");
		SaveNumber(f,G->inwing,fname,tabs);
	}
	if (G->form.Evaluate()!=ENABLE_COMPLEX_VAL)
	{
		fputnl(f,going);
		fputtabs(f,tabs);
		fputs(f,"Formation\t");
		SaveNumber(f,G->form,fname,tabs,ENUM_Formation);
	}
	fputnl(f,going);
	fputtabs(f,tabs);
	fprintf(f,"AirItem\t%s_%04x=\n",fname,G->uniqueID.count);
	fputtabs(f,tabs);
	tabs++;
	fputs(f,"{\n");
	going=0;

//	   	GroundItem BritishNoyellesTanks =
//			{
//				Type		PT_ATank,
//				Side		NAT_ENEMY,
//				Shape		BTANK,
//				Vel		50,
//				MoveCode	GROUND_TAXI,
//				UIDBand		BlueSAMBAND,
//				SetUID		UID_BritishNoyellesTanks
//			}

	going=SaveEvents(f,G->events,fname,tabs);

	if (G->band.Evaluate()!=ENABLE_COMPLEX_VAL)
	{
		fputnl(f,going);
		fputtabs(f,tabs-1);SaveNumber(f,G->band,fname,tabs,ENUM_UIDBand);
	}
	if (G->uid.Evaluate()!=ENABLE_COMPLEX_VAL)
	{
		char*	tmp =  GetList(ENUM_UniqueID).Translate(G->uid.Evaluate());
		if (tmp)
		{
			fputnl(f,going);
			fputtabs(f,tabs);
			fputs(f,"SetUID\t");
			fputs(f,tmp);
		}
	}
	if (G->squadron)
	{
			fputnl(f,going);fputtabs(f,tabs);
			if (G->squadron>0)
				fprintf(f,"Title\t{F%03d}",G->squadron);
			else
				fprintf(f,"Title\t{E%03d}",-G->squadron);
	}

	if (G->type.Evaluate()!=ENABLE_COMPLEX_VAL)
	{
		fputnl(f,going);
		fputtabs(f,tabs);fputs(f,"Type");SaveNumber(f,G->type,fname,tabs,ENUM_Type);
	}


	if (G->nat.Evaluate()!=ENABLE_COMPLEX_VAL)
	{
		fputnl(f,going);
		fputtabs(f,tabs);fputs(f,"Side");SaveNumber(f,G->nat,fname,tabs,ENUM_Side);
	}
	if (G->shape.Evaluate()!=ENABLE_COMPLEX_VAL)
	{
		fputnl(f,going);
		fputtabs(f,tabs);fputs(f,"Shape");SaveNumber(f,G->shape,fname,tabs,ENUM_Shape);
	}
	if (G->vel.Evaluate()!=ENABLE_COMPLEX_VAL)
	{
		fputnl(f,going);
		fputtabs(f,tabs);fputs(f,"Vel");SaveNumber(f,G->vel,fname,tabs);
	}
	if (G->movecode.Evaluate()!=ENABLE_COMPLEX_VAL)
	{
		fputnl(f,going);
		fputtabs(f,tabs);fputs(f,"MoveCode");SaveNumber(f,G->movecode,fname,tabs,ENUM_MoveCode);
	}
	if (G->duty.Evaluate()!=ENABLE_COMPLEX_VAL)
	{
		fputnl(f,going);
		fputtabs(f,tabs);fputs(f,"Duty");SaveNumber(f,G->duty,fname,tabs,ENUM_Duty);
	}
	if (G->skill.Evaluate()!=ENABLE_COMPLEX_VAL)
	{
		fputnl(f,going);
		fputtabs(f,tabs);fputs(f,"Skill");SaveNumber(f,G->skill,fname,tabs,ENUM_Skill);
	}
	if (G->character.Evaluate()!=ENABLE_COMPLEX_VAL)
	{
		fputnl(f,going);
		fputtabs(f,tabs);fputs(f,"Character");SaveNumber(f,G->character,fname,tabs,ENUM_Character);
	}
	if (G->morale.Evaluate()!=ENABLE_COMPLEX_VAL)
	{
		fputnl(f,going);
		fputtabs(f,tabs);fputs(f,"Morale");SaveNumber(f,G->morale,fname,tabs,ENUM_Morale);
	}

	if (G->damage.Evaluate()!=ENABLE_COMPLEX_VAL)
	{
		fputnl(f,going);
		fputtabs(f,tabs);fputs(f,"Damage");SaveNumber(f,G->damage,fname,tabs);
	}
	if (G->bombs.Evaluate()!=ENABLE_COMPLEX_VAL)
	{
		fputnl(f,going);
		fputtabs(f,tabs);fputs(f,"Bombs");SaveNumber(f,G->bombs,fname,tabs);
	}

	if (G->leader.Evaluate()!=ENABLE_COMPLEX_VAL)
	{
		fputnl(f,going);
		fputtabs(f,tabs);fputs(f,"Leader");SaveNumber(f,G->leader,fname,tabs,ENUM_UniqueID);
	}
	if (G->target.Evaluate()!=ENABLE_COMPLEX_VAL)
	{
		fputnl(f,going);
		fputtabs(f,tabs);fputs(f,"Target");SaveNumber(f,G->target,fname,tabs,ENUM_UniqueID);
	}
	if (G->attacker.Evaluate()!=ENABLE_COMPLEX_VAL)
	{
		fputnl(f,going);
		fputtabs(f,tabs);fputs(f,"Attacker");SaveNumber(f,G->attacker,fname,tabs,ENUM_UniqueID);
	}
	if (G->follower.Evaluate()!=ENABLE_COMPLEX_VAL)
	{
		fputnl(f,going);
		fputtabs(f,tabs);fputs(f,"Follower");SaveNumber(f,G->follower,fname,tabs,ENUM_UniqueID);
	}
	if (G->homebase.Evaluate()!=ENABLE_COMPLEX_VAL)
	{
		fputnl(f,going);
		fputtabs(f,tabs);fputs(f,"Home");SaveNumber(f,G->homebase,fname,tabs,ENUM_UniqueID);
	}
	if (G->squadname.Evaluate()!=ENABLE_COMPLEX_VAL)
	{
		fputnl(f,going);
		fputtabs(f,tabs);SaveNumber(f,G->squadname,fname,tabs,ENUM_Squadron);
	}
	for (int i=0;i<G->usedpaintrules;i++)
	{
		fputnl(f,going);
		fputtabs(f,tabs);fputs(f,"PaintScheme");SaveNumber(f,G->paintrules[i],fname,tabs,ENUM_UniqueID);
	}


	fputc(f,'\n');
	fputtabs(f,tabs-2);
	fputs(f,"}\t}");


}
void	Persons2::SaveGrndGrp(FILE* f,ItemBasePtr B,char* fname,int tabs)
{
	info_grndgrp*	G=*B;
//	PreSaveRoute(f,G->wpref,fname,tabs);
	fputtabs(f,tabs);
	fprintf(f,"GroundGroup\n");
	fputtabs(f,tabs);
	fputs(f,"{\n");
	tabs++;
	int	going=0;


	if (G->position.complex)
	{
		fputnl(f,going);
		SavePosition(f,G->position,fname,tabs);
	}
	if (G->wpref)
	{
		fputnl(f,going);
		SaveRoute(f,G->wpref,fname,tabs);
	}
	if (G->inform.Evaluate()!=ENABLE_COMPLEX_VAL)
	{
		fputnl(f,going);
		fputtabs(f,tabs);
		fputs(f,"NumInForm\t");
		SaveNumber(f,G->inform,fname,tabs);
	}
	if (G->form.Evaluate()!=ENABLE_COMPLEX_VAL)
	{
		fputnl(f,going);
		fputtabs(f,tabs);fputs(f,"Formation");SaveNumber(f,G->form,fname,tabs,ENUM_Formation);
	}
	fputnl(f,going);
	fputtabs(f,tabs);
	fprintf(f,"GroundItem\t%s_%04x=\n",fname,G->uniqueID.count);
	fputtabs(f,tabs);
	tabs++;
	fputs(f,"{\n");

//	   	GroundItem BritishNoyellesTanks =
//			{
//				Type		PT_ATank,
//				Side		NAT_ENEMY,
//				Shape		BTANK,
//				Vel		50,
//				MoveCode	GROUND_TAXI,
//				UIDBand		BlueSAMBAND,
//				SetUID		UID_BritishNoyellesTanks
//			}
	going=SaveEvents(f,G->events,fname,tabs);

	if (G->band.Evaluate()!=ENABLE_COMPLEX_VAL)
	{
		fputnl(f,going);
		fputtabs(f,tabs-1);SaveNumber(f,G->band,fname,tabs,ENUM_UIDBand);
	}
	if (G->uid.Evaluate()!=ENABLE_COMPLEX_VAL)
	{
		char*	tmp =  GetList(ENUM_UniqueID).Translate(G->uid.Evaluate());
		if (tmp)
		{
			fputnl(f,going);
			fputtabs(f,tabs);
			fputs(f,"SetUID\t");
			fputs(f,tmp);
		}
	}
	if (G->type.Evaluate()!=ENABLE_COMPLEX_VAL)
	{
		fputnl(f,going);
		fputtabs(f,tabs);fputs(f,"Type");SaveNumber(f,G->type,fname,tabs,ENUM_Type);
	}
	if (G->nat.Evaluate()!=ENABLE_COMPLEX_VAL)
	{
		fputnl(f,going);
		fputtabs(f,tabs);fputs(f,"Side");SaveNumber(f,G->nat,fname,tabs,ENUM_Side);
	}
	if (G->shape.Evaluate()!=ENABLE_COMPLEX_VAL)
	{
		fputnl(f,going);
		fputtabs(f,tabs);fputs(f,"Shape");SaveNumber(f,G->shape,fname,tabs,ENUM_Shape);
	}
	if (G->vel.Evaluate()!=ENABLE_COMPLEX_VAL)
	{
		fputnl(f,going);
		fputtabs(f,tabs);fputs(f,"Vel");SaveNumber(f,G->vel,fname,tabs);
	}
	if (G->movecode.Evaluate()!=ENABLE_COMPLEX_VAL)
	{
		fputnl(f,going);
		fputtabs(f,tabs);fputs(f,"MoveCode");SaveNumber(f,G->movecode,fname,tabs,ENUM_MoveCode);
	}

	if (G->damage.Evaluate()!=ENABLE_COMPLEX_VAL)
	{
		fputnl(f,going);
		fputtabs(f,tabs);fputs(f,"Damage");SaveNumber(f,G->damage,fname,tabs);
	}
	if (G->leader.Evaluate()!=ENABLE_COMPLEX_VAL)
	{
		fputnl(f,going);
		fputtabs(f,tabs);fputs(f,"Leader");SaveNumber(f,G->leader,fname,tabs,ENUM_UniqueID);
	}
	fputc(f,'\n');
	fputtabs(f,tabs-2);
	fputs(f,"}\t}");
}
void	Persons2::SaveItem(FILE* f,ItemBasePtr B,char* fname,int tabs)
{
	info_itemS*	I=*B;
	fputtabs(f,tabs);
	fprintf(f,"SimpleItem\t%s_%04x=\n",fname,I->uniqueID.count);
	fputtabs(f,tabs);
	fputs(f,"{\n");
	tabs++;
	int	going=0;
	going=SaveEvents(f,I->events,fname,tabs);

	if (I->position.complex)
	{
		fputnl(f,going);
		SavePosition(f,I->position,fname,tabs);
	}
	if (I->band.Evaluate()!=ENABLE_COMPLEX_VAL)
	{
		fputnl(f,going);
		fputtabs(f,tabs);
		fputs(f,"UIDBand\t");
		SaveNumber(f,I->band,fname,tabs+1,ENUM_UIDBand);
	}
//	if (I->uid.Evaluate()!=ENABLE_COMPLEX_VAL)
	{
		char*	tmp =  GetList(ENUM_UniqueID).Translate(I->uniqueID.count);
		if (tmp)
		{
			fputnl(f,going);
			fputtabs(f,tabs);
			fputs(f,"SetUID\t");
			fputs(f,tmp);
  		}
	}
	if (I->shape.Evaluate()!=ENABLE_COMPLEX_VAL)
	{
		fputnl(f,going);
		fputtabs(f,tabs);
		fputs(f,"Shape\t");
		SaveNumber(f,I->shape,fname,tabs+1,ENUM_Shape);
	}
	if (I->attitude.Evaluate()!=ENABLE_COMPLEX_VAL)
	{
		fputnl(f,going);
		fputtabs(f,tabs);
		fputs(f,"Heading\t");
		SaveNumber(f,I->attitude,fname,tabs+1,ENUM_RealInt);
	}
	if (I->events)
	{
 //		going=SaveEvents(f,I->events,fname,tabs+1);
	}
	fputc(f,'\n');
	fputtabs(f,tabs-1);
	fputs(f,"}");


}

void	Persons2::PreSaveRoute(FILE* f,UniqueID U,char* fname,int tabs)
{
	info_waypoint*	W=*Persons2::ConvertPtrUID(U);
	while (U&&W)
	{
		fputtabs(f,tabs);
		fprintf(f,"WayPoint	%s_%04x,\n",fname,U);
		U=W->nextwp;
		W=*Persons2::ConvertPtrUID(U);
	}
}
void	Persons2::SaveRoute(FILE* f,UniqueID U,char* fname,int tabs)
{
	info_waypoint*	W=*Persons2::ConvertPtrUID(U);
	fputtabs(f,tabs);
	fprintf(f,"Route\n");
	fputtabs(f,tabs);
	fputs(f,"{\n");
	tabs++;
	int	going=0;
	while (U && W)
	{
		fputnl(f,going);
//		if (W->nextwp)
//		{
//			fputtabs(f,tabs);
//			fprintf(f,"Posn	%s_%04x;\n",fname,W->nextwp);
//		}
		fputtabs(f,tabs);
		fprintf(f,"WayPoint	%s_%04x=\n",fname,U);
		fputtabs(f,tabs);
		fputs(f,"{\n");
		tabs++;
		{
			int	going=0;
			going=SaveEvents(f,W->events,fname,tabs);
//			char	namebuf[30];
  //			sprintf(namebuf,"%s_%04x",fname,U);
			if (W->target.Evaluate()!=ENABLE_COMPLEX_VAL)
			{
				fputnl(f,going);
				fputtabs(f,tabs);fputs(f,"Target");SaveNumber(f,W->target,fname,tabs,ENUM_UniqueID);
			}
			if (W->position.complex)
			{
				fputnl(f,going);
				SavePosition(f,W->position,fname,tabs);
			}
			if (W->vel.Evaluate()!=ENABLE_COMPLEX_VAL)
			{
				fputnl(f,going);
				fputtabs(f,tabs);fputs(f,"Vel");SaveNumber(f,W->vel,fname,tabs);
			}
			if (W->wpact.Evaluate()!=ENABLE_COMPLEX_VAL)
			{
				fputnl(f,going);
				fputtabs(f,tabs);fputs(f,"Action");SaveNumber(f,W->wpact,fname,tabs,ENUM_Action);
			}
			if (W->range.Evaluate()!=ENABLE_COMPLEX_VAL)
			{
				fputnl(f,going);
				fputtabs(f,tabs);
				fputs(f,"Range");
				if (W->rangeispercent)
					fputs(f,"Percent");
				SaveNumber(f,W->range,fname,tabs);
			}
		}
		tabs--;
		fputc(f,'\n');
		fputtabs(f,tabs);
		fputc(f,'}');
		U=W->nextwp;
		W=*Persons2::ConvertPtrUID(U);
	}
	fputc(f,'\n');
	fputtabs(f,tabs-1);
	fputc(f,'}');
}

void	Persons2::SaveNumber(FILE* f,EventVal& V,char* fname,int tabs,EnumListNames e)
{
		V.Save(f,fname,tabs+1,e);
}

void	Persons2::SavePosition(FILE* f,EventVal& V,char* fname,int tabs,char* namedpos)
{	//the position of a waypoint is named, rather than the waypoint itself
	fputtabs(f,tabs);
	fputs(f,"Posn");
	if (namedpos)
		fprintf(f,"\t%s=",namedpos);

	V.Save(f,fname,tabs);
}

/////////////////////////////////////////////////////////////////


//void	MissionType::Save(FILE* f)
//{
//	fputs(f,"Family {");
//	fprintf(f,
//		"%i %i "
//		"%hi %hi "
//		"%c %c "
//		"%hi %hi %hi "
//		"%hi "
//		"%hi %hi "
//		"%hi %hi "
//		"%hi %hi "
//		"%hi %hi %hi "
//		,
//		missiondate,timeofday,
//		numofsquadronac,numofflightac,
//		PlayerNationality+'@',formationtypeindex+'@',
//		weathernum,windspeed,winddirection,
//        0,
///		ChooseBfForm->BFields[ChooseBfForm->AvailBf[era]].file,//main world
//		region,PlayerAcType,
//		PlayerHomeBase,EnemyHomeBase,
//		MainObjective,SubObjective,
//		WP1,WP2,WP3
//		);
//	fputs(f,"}");
//	if(MainObjective)
//	{
//		fprintf(f,",\n\t\tSetval	{MainObjective,");
//		EventVal	v=MainObjective;
//		v.Save(f,name,2,ENUM_UniqueID);
//		fprintf(f,"}");
//	}
//	if(SubObjective)
//	{
//		fprintf(f,",\n\t\tSetval	{SubObjective,");
//		EventVal	v=SubObjective;
//		v.Save(f,name,2,ENUM_UniqueID);
//		fprintf(f,"}");
//	}
//	if(WP1)
//	{
//		fprintf(f,",\n\t\tSetval	{WP1,");
//		EventVal	v=WP1;
//		v.Save(f,name,2,ENUM_UniqueID);
//		fprintf(f,"}");
//	}
//	if(WP2)
//	{
//		fprintf(f,",\n\t\tSetval	{WP2,");
//		EventVal	v=WP2;
//		v.Save(f,name,2,ENUM_UniqueID);
//		fprintf(f,"}");
//	}
//	if(WP3)
//	{
//		fprintf(f,",\n\t\tSetval	{WP3,");
//		EventVal	v=WP3;
//		v.Save(f,name,2,ENUM_UniqueID);
//		fprintf(f,"}");
//	}
//}

