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

//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include	"dosdefs.h"

#define	F_COMMON
#include "Files.g"
#include "bfform.h"
#include "meMain.h"
#include	"loadsave.h"
#include	"precomp.h"


#include	"text.h"
#include	"persons2.h"
#include	"fileman.h"
#include	"bfenum.h"
#include	"readenum.h"

//---------------------------------------------------------------------------
#pragma link "Grids"
#pragma resource "*.dfm"
TBfieldForm *BfieldForm;
extern   StaticBand   staticbands [];

ItemBasePtr	WorldStuff::pItem[PITEMTABLESIZE];
//---------------------------------------------------------------------------
__fastcall TBfieldForm::TBfieldForm(TComponent* Owner)
	: TForm(Owner)
{
	FILE* f=fopen("..\\h\\uidtops.g","rt");
	if (!f)
    	exit(1);
	int i;
		fscanf(f,"%x %x",&i,&i);
	int c=-1;
	do
	{
		int i,j=0;
		fscanf(f,"%x %x",&i,&j);
		switch (i)
		{	//patch bands where we can have full spread.
//			case	RedGroundMobileBAND:
  //			case	BlueAcBAND:
	//		case	RedCivilianBAND:
	  //			uidbandmax[c]=i;
		}
		c++;
		i=fgetc(f);
		Persons2::uidbandmax[c]=j;
	}	while (c<2||(int)Persons2::uidbandmax[c]!=0);
	Persons2::pItem=WorldStuff::pItem;
}
//---------------------------------------------------------------------------
void __fastcall TBfieldForm::OpenForm()
{
	UWord i;
	for (i = 0; i < MAXLOADEDBFIELDS;i++)
		MissionEditor->tmploadedbfs[i] = MissionEditor->loadedbfs[i];
	BfieldGrid->Rows[0]->SetText("Name\nCurr\nView\nMove\nDelete\nNew\nChanged");
	currsel=MissionEditor->bfieldbeingfilled;
	Refresh();
	if (MissionEditor->loadedbfs[i].fnum == 0)
	{
		EditPanel->Enabled=false;
		NewPanel->Enabled=true;
		EditPanel->BevelOuter=bvLowered;
		NewPanel->BevelOuter=bvRaised;
	}
	else
	{
		EditPanel->Enabled=true;
		EditPanel->BevelOuter=bvRaised;
		NewPanel->Enabled=false;
		NewPanel->BevelOuter=bvLowered;
	}
	int result = ShowModal();
	switch (result)
	{
		case	mrOk:
		  {

				break;
		  }
		case	mrCancel:
		  {
				for (i = 0; i < MAXLOADEDBFIELDS;i++)
					MissionEditor->loadedbfs[i] = MissionEditor->tmploadedbfs[i];
				 break;
		  }
	  }
 }

void __fastcall TBfieldForm::Refresh()
{
	UWord i, j = 0;
	char buff[50];
	for (i = 0; i < MAXLOADEDBFIELDS;i++)
	{
		if (currsel==i)
		{
			struct	x:public TGridRect
			{	x(int l,int t,int r,int b)	{Left=(l),Top=(t),Right=(r),Bottom=(b);}	}
			X(6,j+1,0,j+1);
			BfieldGrid->Selection=X;
		}
		if	(MissionEditor->loadedbfs[i].fnum != 0)
		{
			if (MissionEditor->loadedbfs[i].name[0])
				BfieldGrid->Cells[0][j+1]= MissionEditor->loadedbfs[i].name;
			else
				BfieldGrid->Cells[0][j+1]= (AnsiString)MissionEditor->loadedbfs[i].fname+".BF";
			if (i == MissionEditor->bfieldbeingfilled)
				strcpy(buff,"true");
			else
				strcpy(buff,"false");
			BfieldGrid->Cells[1][j+1]= buff;

			if (MissionEditor->loadedbfs[i].viewable)
				strcpy(buff,"true");
			else
				strcpy(buff,"false");
			BfieldGrid->Cells[2][j+1]= buff;

			if (MissionEditor->loadedbfs[i].movable)
				strcpy(buff,"true");
			else
				strcpy(buff,"false");
			BfieldGrid->Cells[3][j+1]= buff;

			if (MissionEditor->loadedbfs[i].deletable)
				strcpy(buff,"true");
			else
				strcpy(buff,"false");
			BfieldGrid->Cells[4][j+1]= buff;

			if (MissionEditor->loadedbfs[i].newlynamed)
				strcpy(buff,"true");
			else
				strcpy(buff,"false");
			BfieldGrid->Cells[5][j+1]= buff;

			if (MissionEditor->loadedbfs[i].changed)
				strcpy(buff,"true");
			else
				strcpy(buff,"false");
			BfieldGrid->Cells[6][j+1]= buff;
			j++;
		}
	}
	for (j; j < MAXLOADEDBFIELDS;j++)
	{
		BfieldGrid->Cells[0][j+1]= "";
		BfieldGrid->Cells[1][j+1]= "";
		BfieldGrid->Cells[2][j+1]= "";
		BfieldGrid->Cells[3][j+1]= "";
		BfieldGrid->Cells[4][j+1]= "";
		BfieldGrid->Cells[5][j+1]= "";
		BfieldGrid->Cells[6][j+1]= "";
	}
}

void __fastcall TBfieldForm::BfieldGridSelectCell(TObject *Sender, long c,
	long r, bool &CanSelect)
{
	CanSelect=true;
	if (NewPanel->Enabled || c==0 || c>=5)
    	CanSelect=false;

}
////---------------------------------------------------------------------------
void __fastcall TBfieldForm::BfieldGridMouseDown(TObject *Sender,
	TMouseButton Button, TShiftState Shift, int X, int Y)
{
	long	c,r;
	TStringGrid* G=(TStringGrid*)Sender;
	G->MouseToCell(X,Y,c,r);
	bool CanSelect=true;
	UWord	i = 0, j = -1;
	//skip blanks
	while  (i < MAXLOADEDBFIELDS)
	{
		if	(MissionEditor->loadedbfs[i].fnum != 0)
			j++;
		if (j == (r -1))
			break;
		i++;
	}
	if (r==0)
		return;
	if (i==MAXLOADEDBFIELDS)
	{
		struct	x:public TGridRect
		{	x(int l,int t,int r,int b)	{Left=(l),Top=(t),Right=(r),Bottom=(b);}	}
		X(6,r,0,r);
		BfieldGrid->Selection=X;
		BfieldGrid->Col=0;
		BfieldGrid->Row=r;
		EditPanel->Enabled=false;
		NewPanel->Enabled=true;
		EditPanel->BevelOuter=bvLowered;
		NewPanel->BevelOuter=bvRaised;
		currsel=-1;
		return;
	}

	EditPanel->Enabled=true;
	EditPanel->BevelOuter=bvRaised;
	NewPanel->Enabled=false;
	NewPanel->BevelOuter=bvLowered;
	if (c == 0 || c>=5)
	{
		struct	x:public TGridRect
        {	x(int l,int t,int r,int b)	{Left=(l),Top=(t),Right=(r),Bottom=(b);}	}
        X(6,r,0,r);
    	BfieldGrid->Col=0;
        BfieldGrid->Row=r;
        BfieldGrid->Selection=X;
    	currsel=i;
		return;
    }
    currsel=-1;
	if (c == 1)
	{
		MissionEditor->bfieldbeingfilled = i;
	}
    else if (c == 2)
	{
		  if (MissionEditor->loadedbfs[i].viewable)
			MissionEditor->loadedbfs[i].viewable = false;
		  else
			MissionEditor->loadedbfs[i].viewable = true;
	}
    else if (c == 3)
	{
		  if (MissionEditor->loadedbfs[i].movable)
			MissionEditor->loadedbfs[i].movable = false;
		  else
			MissionEditor->loadedbfs[i].movable = true;
	}
    else if (c == 4)
	{
		  if (MissionEditor->loadedbfs[i].deletable)
			MissionEditor->loadedbfs[i].deletable = false;
		  else
			MissionEditor->loadedbfs[i].deletable = true;
	}
    else if (c == 5)
	{
    	CanSelect=false;
//		  if (MissionEditor->loadedbfs[i].newlynamed)
  //			MissionEditor->loadedbfs[i].newlynamed = false;
	//	  else
	  //		MissionEditor->loadedbfs[i].newlynamed = true;
	}
	else if (c == 6)
	{
		CanSelect=false;
//		  if (MissionEditor->loadedbfs[i].changed)
  //			MissionEditor->loadedbfs[i].changed = false;
	//	  else
	  //		MissionEditor->loadedbfs[i].changed = true;
	}
	Refresh();
	Invalidate();
}
void __fastcall TBfieldForm::WipeButtonClick(TObject *Sender)
{
	int wipe=MissionEditor->bfieldbeingfilled;
	if (currsel!=-1)
		wipe=currsel;
	MissionEditor->WipeBf(wipe);
	Refresh();
	Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TBfieldForm::ReloadButtonClick(TObject *Sender)
{
	int wipe=MissionEditor->bfieldbeingfilled;
	if (currsel!=-1)
		wipe=currsel;
	MissionEditor->WipeBf(wipe);
	LoadBf(wipe,MissionEditor->loadedbfs[wipe].fnum,MissionEditor->loadedbfs[wipe].fname);
	Refresh();
	Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TBfieldForm::DeleteButtonClick(TObject *Sender)
{
	int wipe=MissionEditor->bfieldbeingfilled;
	if (currsel!=-1)
		wipe=currsel;
	MissionEditor->WipeBf(wipe);
	MissionEditor->loadedbfs[wipe].fnum = 0;
	MissionEditor->bfieldbeingfilled = 0;
	Refresh();
	Invalidate();
}
//---------------------------------------------------------------------------



bool __fastcall TBfieldForm::LoadNewClick(bool load)
{
	int i=MAXLOADEDBFIELDS-1;
	if (MissionEditor->loadedbfs[i].fnum)
	{
		while(i>=0 && MissionEditor->loadedbfs[i].fnum)
			i--;
	}
	else
		while(i>0 && !MissionEditor->loadedbfs[i-1].fnum)
			i--;
	if (i<0)
	{
		return false;
	}

	int rv;
	AnsiString	name="";
	AnsiString	title="";
	if (load)
		rv=FileLoadSave->ShowModal(FIL_NULL,name,title,FM_OpenBfDirs);
	else
		rv=FileLoadSave->ShowModal(FIL_NULL,name,title,FM_NewBfDirs);
	switch (rv)
	{
	case mrCancel:
		return false;
	case	mrYes:
	{
		LoadBf(i,FileLoadSave->CurrDirNum,name.c_str());
		MissionEditor->loadedbfs[i].newlynamed=
			MissionEditor->loadedbfs[i].changed=false;
	}
	break;
	case	mrOk:
		MissionEditor->loadedbfs[i].newlynamed=true;
		break;
	}
	MissionEditor->loadedbfs[i].fnum=FileLoadSave->CurrDirNum;
	MissionEditor->bfieldbeingfilled = i;
	MissionEditor->loadedbfs[i].changed=false;
	MissionEditor->loadedbfs[i].viewable=
		MissionEditor->loadedbfs[i].movable=
			MissionEditor->loadedbfs[i].deletable=true;
	strcpy(MissionEditor->loadedbfs[i].fname,name.c_str());
	strcpy(MissionEditor->loadedbfs[i].name,title.c_str());
	return true;
}
////////////////////////////////////////////////////////////////////////
void __fastcall TBfieldForm::LoadClick(TObject *Sender)
{
	if (!LoadNewClick(true))
	{}
	Refresh();
	Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TBfieldForm::NewClick(TObject *Sender)
{
	if (!LoadNewClick(false))
	{}
	Refresh();
	Invalidate();

}

////////////////////////////////////////////////////////////////////////
static STARTUPINFO sui=
{
	sizeof(STARTUPINFO),
	NULL,NULL,                  //res/desk
	"Compiling... please wait",	//title
	0,0,						//x,y
	400,200,					//w,h
	40,20,                      //tw,th
	0,							//colour
	STARTF_USECOUNTCHARS+STARTF_USEPOSITION+STARTF_USESIZE+STARTF_USESHOWWINDOW,		//flags
	SW_SHOWMINIMIZED,
	0,
	NULL,
	0,0,0
};
static PROCESS_INFORMATION	pi;
extern	char	outname[];
////////////////////////////////////////////////////////////////////////
bool TBfieldForm::SaveMission(int bfindex)
{	//brought them all together here!
//	if (MissionEdited)	//MissionEditor->loadedbfs[bfindex].changed
	{
		if (FileNameAvailable(bfindex))
		{
			EnumStuff::savestrings("SNIP\tT_","\t=\t\"","\";\n",GetList(ENUM_UniqueID),"..\\english\\uidnames.txt",GetList(ENUM_UIDtitle));
			EnumStuff::savestrings("SNIP\tD_","\t=\t\"","\";\n",GetList(ENUM_UniqueID),"..\\english\\uiddescs.txt",GetList(ENUM_UIDdesc));

			MissionEditor->CheckObjectives();
//			FindWorldTemplateFiles(ActiveCampaign.mission[currmission].region);//DAW 06Sep97
            Persons4	Persons_2;
//DeadCode JIM 31May98             Persons2	Persons_2(NULL,NULL);
			Persons_2.currbfindex=bfindex;

            Persons_2.SaveBF(	MissionEditor->loadedbfs[bfindex].fnum,     	//get directory name
                                MissionEditor->loadedbfs[bfindex].fname,
								MissionEditor->loadedbfs[bfindex].name,
                                MissionEditor->loadedbfs[bfindex].newstext,
                                MissionEditor->loadedbfs[bfindex].newlynamed
                                );
			MissionEditor->loadedbfs[bfindex].newlynamed=false;
            MissionEditor->loadedbfs[bfindex].changed=false;
			Persons_2.justscanning=Persons2::LOAD;

			int	rv=mrOk;
			if (MissionEditor->EditMissionSrc1->Checked)
			do{
            	Editb4Compile->Edit2->Text=outname;
				rv=Editb4Compile->ShowModal();
				if (rv==mrRetry)
				{
					AnsiString s=Editb4Compile->Edit1->Text+" "+Editb4Compile->Edit2->Text;
					if (!CreateProcess(	NULL,s.c_str(),
							NULL,NULL,
							FALSE,CREATE_DEFAULT_ERROR_MODE | NORMAL_PRIORITY_CLASS,
							NULL,NULL,
							&sui,&pi
							))
					//error box... editor could not start!
					;
				}
			}while (rv==mrRetry);
			if (rv==mrCancel)
				return false;

			char	path[300];
			strcpy (path,GetCommandLine ());
			int i=1;
			while (path[i]>=' ' && path[i]!='"')
				i++;
			while (i>0 && path[i]!=':' && path[i]!='\\')
				i--;
			i--;
			while (i>0 && path[i]!=':' && path[i]!='\\')
				i--;
			if (i==2 && path[1]==':')
				i++;
			path[i]=0;
			char cmd[300];
			char line[300];
			strcpy(cmd,path);
			strcpy(line,path);
			if (i==3 && cmd[1]==':')
			{
				cmd[2]=0;
				line[2]=0;
			}
			strcat(cmd,"\\..\\debug\\exe\\makebf.exe");
			strcat(line,"\\..\\debug\\exe\\makebf.exe\" bfields\\initial.res bfields\\battle.src");

			CreateProcess(	cmd+1,line,
							NULL,NULL,
							FALSE,CREATE_DEFAULT_ERROR_MODE | NORMAL_PRIORITY_CLASS,
							NULL,path+1,
							&sui,&pi
							);
			DWORD	rc;
			do{
  					Sleep(1);
					GetExitCodeProcess(pi.hProcess,&rc);
	  		}while (rc==STILL_ACTIVE);

 //			MissionNew=false;
   //			MissionEdited=false;

		}
		else
			return false;
	}
//edited flag not set properly
//	else
//	{
//		char buff[100];
//		if (MissionEdited)
//			LoadString(HInstance,TEXT_NOTENOUGHEDITS,buff,sizeof(buff));
//		else
//			LoadString(HInstance,TEXT_NOEDITS,buff,sizeof(buff));
//		Application->MessageBox(buff,buff,MB_OK);
//		return false;
//	}

//	SetCaption(MissionEditor->ActiveCampaign.name,ActiveCampaign.mission[currmission].name);
	return true;
}
//---------------------------------------------------------------------------
void __fastcall TBfieldForm::SaveClick(TObject *Sender)
{
	if (currsel!=-1)
		SaveMission(currsel);
	else
		SaveMission(MissionEditor->bfieldbeingfilled);
}
//---------------------------------------------------------------------------
bool	TBfieldForm::QuerySaveChanges(int bfindex)
{
	int bfmin=0,bfmax=MAXLOADEDBFIELDS-1;
	if (bfindex!=-1)
    	bfmin=bfmax=bfindex;
	for (bfindex=bfmin;bfindex<=bfmax;bfindex++)
    	if (MissionEditor->loadedbfs[bfindex].fnum && MissionEditor->loadedbfs[bfindex].changed)
    {
		AnsiString name=MissionEditor->loadedbfs[bfindex].fname;
		AnsiString title=MissionEditor->loadedbfs[bfindex].name;//ActiveCampaign.mission[currmission].title;
		int rc=FileLoadSave->ShowModal(MissionEditor->loadedbfs[bfindex].fnum,name,title,
			MissionEditor->loadedbfs[bfindex].newlynamed?FM_SaveAsDiscard:FM_SaveDiscard);
		switch (rc)
        {
        	case	mrYes:
				strcpy(MissionEditor->loadedbfs[bfindex].fname,name.c_str());
				strcpy(MissionEditor->loadedbfs[bfindex].name,title.c_str());
        	    MissionEditor->loadedbfs[bfindex].fnum=FileLoadSave->CurrDirNum;
            	SaveMission(bfindex);
            break;
            case	mrNo:
            break;
            case	mrCancel:
            	return false;
        }
    }
	return true;
}

bool __fastcall TBfieldForm::FileNameAvailable(int bfindex)
{
	if (MissionEditor->loadedbfs[bfindex].fname[0])
		return true;
	else
	{
//		char *f=FILEMAN.namenumberedfile(dirnum(dirnum(FIL_USERMISSION1)));
//		f[strlen(f)-7]=0;
		AnsiString name=MissionEditor->loadedbfs[bfindex].fname;
		AnsiString title=MissionEditor->loadedbfs[bfindex].name;//ActiveCampaign.mission[currmission].title;
		int rc=FileLoadSave->ShowModal(MissionEditor->loadedbfs[bfindex].fnum,name,title,FM_SaveBfDirs);
		if (rc==mrCancel)
			return false;
		else
		{

			strcpy(MissionEditor->loadedbfs[bfindex].fname,name.c_str());
			strcpy(MissionEditor->loadedbfs[bfindex].name,title.c_str());
			MissionEditor->loadedbfs[bfindex].fnum=FileLoadSave->CurrDirNum;
			return true;
		}
	}

}
////////////////////////////////////////////////////////////////////////
void	TBfieldForm::LoadBf(int bfindex,FileNum reqdir,char* name)
{
		char fname[20];
		strcpy(fname,name);
		strcat(fname,".BF");

		Persons4	Persons_2;
		Persons_2.justscanning=Persons2::LOAD;
		Persons_2.LoadSubPiece(NULL,FakeUserObj(reqdir,fname),bfindex);
//	strcpy(MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].newstext,
//			Persons_2.bfdesc->news);
		MissionEditor->AccumulateLoadedCount();
		MissionEditor->CheckObjectives();
}
////////////////////////////////////////////////////////////////////////
FileNum	TBfieldForm::FakeUserObj(FileNum dirnum,char* filename)
{
	char* name=FILEMAN.namenumberedfilelessfail(dirnum);
	char* end=name+strlen(name);
	while (*end!=':' && *end!='\\' && end!=name)
		end--;
	*end=0;
	FILEMAN.fakedir(FIL_USERMISSION1,name);
	if (filename && filename[0])
		return	FILEMAN.fakefile(FIL_USERMISSION1,filename);
	else
		return	FIL_NULL;
}

