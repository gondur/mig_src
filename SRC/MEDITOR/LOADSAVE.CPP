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

#define	F_GRAFIX
#define	F_COMMON
#include	"dosdefs.h"
#include	"files.g"
#include "LoadSave.h"
#include "dir.h"
//#include "memain.h"
#include "strings.h"
#include	"text.h"
#include "persons2.h"
#include "fileman.h"

#include "bfnumber.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TFileLoadSave *FileLoadSave;
inline operator <=	(char i,TFileAttr j)	{return int(i)<=int(j);}
inline operator >=	(char i,TFileAttr j)	{return int(i)>=int(j);}
inline operator <=	(TFileAttr i,char j)	{return int(i)<=int(j);}
inline operator >=	(TFileAttr i,char j)	{return int(i)>=int(j);}
inline operator /	(TFileAttr i,char j)	{return int(i)/int(j);}
inline operator %	(TFileAttr i,char j)	{return int(i)%int(j);}
//---------------------------------------------------------------------------
__fastcall TFileLoadSave::TFileLoadSave(TComponent* Owner)
	: TForm(Owner)
{
	Font->Color = clWindow;
	Font->Color = clWindowText;
	squelchdiscard=false;
	fakedir=false;

    PathList->Items->Clear();
    int i,f;
    for (i=0,f=120*256;f<140*256;f+=256)
    {
    	char* n=FILEMAN.namenumberedfilelessfail(FileNum(f));
        if (n)
        {
        	dirnums[i]=f;
            char* c;
            for (c=n+strlen(n);*c!='\\';--c)
	            *c=0;
			PathList->Items->Add(n);
            i++;
        }
    }
    while (i<32)
    	dirnums[i++]=0;

}
//---------------------------------------------------------------------------
void __fastcall TFileLoadSave::FileListBox1DblClick(TObject *Sender)
{
   if (Open->Visible && !FileName->Text.IsEmpty())
	   ModalResult=mrYes;
}
//---------------------------------------------------------------------------

//void	CampaignType::FileList::Clear()
//{
//(ULong&) data[0][0]=*(ULong*)"dir.";
//(ULong&) data[0][4]=*(ULong*)"dir";
//(ULong&) data[0][8]=0;
//(ULong&) data[0][12]=0;
//for (int i=1;i<(int)maxfiles;i++)
//	data[i][0]=0;
//
//(ULong&) data[(int)maxfiles-2][0]=*(ULong*)"camp";
//(ULong&) data[(int)maxfiles-2][4]=*(ULong*)"aign";
//(ULong&) data[(int)maxfiles-2][8]=*(ULong*)".def";
//(ULong&) data[(int)maxfiles-2][12]=0;
//(ULong&) data[(int)maxfiles-1][0]=*(ULong*)"camp";
//(ULong&) data[(int)maxfiles-1][4]=*(ULong*)"aign";
//(ULong&) data[(int)maxfiles-1][8]=*(ULong*)".plt";
//(ULong&) data[(int)maxfiles-1][12]=0;
//
//}

void __fastcall TFileLoadSave::FileNameChange(TObject *Sender)
{
	if (	!FileName->Text.IsEmpty()
		&&	FileName->SelStart
		&& strrchr(" ]})[{(,;:+=/<>.#",FileName->Text[FileName->SelStart]))
	{
		char work[20];
		strcpy(work,FileName->Text.c_str());
		int i=FileName->SelStart-1;
		strcpy(work+i,work+i+1);
		FileName->Text=work;
		FileName->SelStart=i;
	}

	if (!FileName->Text.IsEmpty())
		if (FileName->Text[1]=='*'	||	FileName->Text[2]=='*')
			FileName->Text="";

	if (!FileName->Text.IsEmpty())
	{
		char work[20];
		if (FileName->Text[1]=='[')
		{
			strcpy(work,FileName->Text.c_str());
			work[strlen(work)-1]=0;
			FileName->Text=work+1;
		}

		strcpy(work,FileName->Text.c_str());
		char*	finddot=work;
		while (*finddot!='.' && *finddot!=0)
			finddot++;
		if (*finddot)
		{
			*finddot=0;
			FileName->Text=work;
		}
	}
	if (FileName->Text.IsEmpty())
	{
		Panel2->Caption="";
		Able(Save,false);
		Able(New,false);
		Able(Rename,false);
		Able(Name,false);
		Able(Open,false);
		Title->Enabled=false;
		char buff[50];
		LoadString(HInstance,TEXT_FILE_0LEN,buff,50);
		Title->Text=buff;
		return;

	}
	else
	if (FileName->Text[1]>='0' && FileName->Text[1]<='9')
	{
		Able(Save,false);
		Able(New,false);
		Able(Rename,false);
		Able(Name,false);
		Able(Open,false);
		Title->Enabled=false;
		char buff[50];
		LoadString(HInstance,TEXT_FILE_DIGIT,buff,50);
		Title->Text=buff;
		return;
	}
	if (dirmode)
	{
		char pathname[100];
		strcpy(pathname,FileListBox1->Directory.c_str());
		strcat(pathname,"\\");
		char buff[12];
		strcpy(buff,FileName->Text.c_str());
		if (	FileName->Text[1]==ext[0]
			||	FileName->Text[1]==ext[1]
			)
		{
			FileName->Text=buff+1;
		}

		if (ext[0]=='c' || strcmpi(buff,"DEFAULT"))
		{
			strcat(pathname,ext+1);
			Panel2->Caption=ext+1;
		}
		else
			Panel2->Caption="";
		FileName->MaxLength=7;

		strcat(pathname,FileName->Text.c_str());
		if (!_mkdir(pathname))
		{
			_rmdir(pathname);
			Able(New,true);
			Able(Rename,true);
			Able(Name,true);
			Able(Open,false);
			if (ext[0]=='c')
				Title->Enabled=true;
			else
				Title->Enabled=false;
			Title->Text=InputTitle;
		}
		else
		{
			Able(New,false);
			Able(Rename,false);
			Able(Name,false);
			strcat(pathname,"\\direxist.tst");
			Title->Enabled=false;
			Title->Text="";
			FILE* F=fopen(pathname,"wb");
			if (F)
			{
				fclose(F);
				remove(pathname);
				Able(Open,true);
				pathname[strlen(pathname)-13]=0;
				strcat(pathname,"\\campaign.def");
				F=fopen(pathname,"rb");
				if (F)
				{
 //					MeCampaignTexts tmp;
   //					fread(&tmp,sizeof(tmp),1,F);
	 //				fclose(F);
	   //				Title->Enabled=false;
		 //			Title->Text=tmp.title;
				}
			}
			else
			{
				Title->Enabled=false;
				char buff[50];
				LoadString(HInstance,TEXT_FILE_ILLEGAL,buff,50);
				Title->Text=buff;
				Able(Open,false);
			}
		}
	}
	else
	{
		char pathname[100];
		strcpy(pathname,FileListBox1->Directory.c_str());
		strcat(pathname,"\\");
		strcat(pathname,FileName->Text.c_str());
		strcat(pathname,ext);
		FILE* F=fopen(pathname,"rb");
		if (F)
		{
			fclose(F);
			Title->Enabled=false;
			if (*(ULong*)ext==*(ULong*)".BF")
			{
				if (fakedir)
					FILEMAN.fakedir(FIL_USERMISSION1,FileListBox1->Directory.c_str());
				strcpy(pathname,FileName->Text.c_str());
				strcat(pathname,ext);
                Persons4	Persons_2;
//				Persons_2.justscanning=true;
				Persons_2.LoadSubPiece(NULL,FILEMAN.fakefile(FIL_USERMISSION1,pathname),(int)Persons2::LOADEDBFS-1,Persons2::SCANNAMES);
  //				Persons_2.justscanning=false;
				Title->Text="";//Persons_2.bfdesc->title;
			}
			else
				Title->Text="";
			if (Save->Visible)
				Title->Enabled=true;
			else
				Title->Enabled=false;
			Able(Open,true);
			Able(New,false);
			Able(Rename,false);
			Able(Name,false);
			if (FileName->Enabled)
				Able(Save,false);
			else
				Able(Save,true);
		}
		else
		{
			F=fopen(pathname,"wb");
			if (F)
			{
				fclose(F);
				remove(pathname);

				Able(Save,true);
				Able(New,true);
				Able(Rename,true);
				Able(Name,true);
				Able(Open,false);
				Title->Text=InputTitle;
				Title->Enabled=true;
			}
			else
			{
				Able(Save,false);
				Able(New,false);
				Able(Rename,false);
				Able(Name,false);
				Able(Open,false);
				char buff[50];
				LoadString(HInstance,TEXT_FILE_ILLEGAL,buff,50);
				Title->Text=buff;
				Title->Enabled=false;
			}
		}
	}
}

bool	TFileLoadSave::Able(TButton* b,bool setting)
{
	if (b->Visible)
	{
		b->Default=
			b->Enabled=setting;
	//	if (setting)
	  //		b->SetFocus();
		return true;
	}
	else
		return false;
}
//---------------------------------------------------------------------------
int __fastcall TFileLoadSave::ShowModal(FileNum path,AnsiString& currname,AnsiString& currtitle,FileModes mode)
{
	int i=0;
	while(dirnums[i] && dirnums[i]!=path)
    	i++;
    if (dirnums[i]==0)
		i=0;
	PathList->ItemIndex=i;
	return ShowModal(PathList->Items->Strings[i],currname,currtitle,mode);
}
int __fastcall TFileLoadSave::ShowModal(AnsiString path,AnsiString& currname,AnsiString& currtitle,FileModes mode)
{
	InputTitle=currtitle;
	ext="";
	Cancel->Default=false;
	Cancel->Enabled=
		Cancel->Visible=true;		//result =	mrCancel
//	Cancel->SetFocus();
	Save->Default=
		Save->Enabled=
			Save->Visible=false;		//result=	mrYes
	New->Default=
		New->Visible=
			New->Enabled=false;			//result=	mrOk
	Rename->Default=
		Rename->Enabled=
			Rename->Visible=false;		//result=	mrYes
	Name->Default=
		Name->Enabled=
			Name->Visible=false;		//result=	mrYes
	Discard->Default=
		Discard->Enabled=
			Discard->Visible=false;		//result=	mrNo
	Open->Default=
		Open->Enabled=
			Open->Visible=false;		//result=	mrYes

	FileListBox1->Enabled=true;
	FileListBox1->FileType>>ftDirectory;
	Drive->Font->Color=clInactiveCaptionText;
	DirName->Font->Color=clInactiveCaptionText;
	FileListBox1->FileType>>ftNormal;
	FileListBox1->Color=clWindow;
	DirName->Enabled=false;
	DirName->Visible=true;
	PathList->Enabled=
		PathList->Visible=false;
	Drive->Enabled=
		Drive->Visible=false;

	FileName->Enabled=true;
	char	captiontext[50];
	char	desctext[100];
	char	suretext[100];
	suretext[0]=0;
	dirmode=false;

	Description->Font->Color=clWindowText;
	Description->Color=clBtnFace;
	Panel2->Visible=false;
	FileListBox1->Mask="*.*";  //force changes
	FileName->Text="";
	switch (mode)
	{
	case FM_NewDirM:
		dirmode=true;
		LoadString(HInstance,TEXT_SELECTDIR,captiontext,50);
		LoadString(HInstance,TEXT_NEWGRP,desctext,100);
		LoadString(HInstance,TEXT_SUREOPENDIR,suretext,100);
		expecting=mrOk;
		FileListBox1->Mask="M*;default";
		ext="mM";
		FileListBox1->FileType<<ftDirectory;
		Panel2->Visible=true;
		New->Visible=true;
		Open->Visible=true;
	break;
	case FM_OpenDirM:
		dirmode=true;
		LoadString(HInstance,TEXT_SELECTDIR,captiontext,50);
		LoadString(HInstance,TEXT_OPENGRP,desctext,100);
		LoadString(HInstance,TEXT_SURENEWDIR,suretext,100);
		expecting=mrYes;
		FileListBox1->Mask="M*;default";
		ext="mM";
		FileListBox1->FileType<<ftDirectory;
		Panel2->Visible=true;
		New->Visible=true;
		Open->Visible=true;
	break;
	case FM_NewDirC:
		dirmode=true;
		LoadString(HInstance,TEXT_SELECTDIR,captiontext,50);
		LoadString(HInstance,TEXT_NEWCAMP,desctext,100);
		LoadString(HInstance,TEXT_SUREOPENDIR,suretext,100);
		expecting=mrOk;
		FileListBox1->Mask="C*";
		ext="cC";
		FileListBox1->FileType<<ftDirectory;
		Panel2->Visible=true;
		New->Visible=true;
		Open->Visible=true;
	break;
	case FM_OpenDirC:
		dirmode=true;
		LoadString(HInstance,TEXT_SELECTDIR,captiontext,50);
		LoadString(HInstance,TEXT_OPENCAMP,desctext,100);
		LoadString(HInstance,TEXT_SURENEWDIR,suretext,100);
		expecting=mrYes;
		FileListBox1->Mask="C*";
		ext="cC";
		FileListBox1->FileType<<ftDirectory;
		Panel2->Visible=true;
		Panel2->Enabled=true;
		New->Visible=true;
		Open->Visible=true;
	break;
	case FM_OpenBfDirs:
		fakedir=true;
		LoadString(HInstance,TEXT_SELECTFILE,captiontext,50);
		LoadString(HInstance,TEXT_OPENMISS,desctext,100);
		LoadString(HInstance,TEXT_SURENEWMISS,suretext,100);
		expecting=mrYes;
		FileListBox1->Mask="*.BF";
		ext=".BF";
		FileListBox1->FileType<<ftNormal;
		New->Visible=true;
		Open->Visible=true;
		DirName->Enabled=
			DirName->Visible=false;
		PathList->Enabled=
			PathList->Visible=true;
	break;
	case FM_SaveAsDiscard:
		fakedir=true;
		LoadString(HInstance,TEXT_SAVEALERTTITLE,captiontext,50);
		LoadString(HInstance,TEXT_SAVEALERTNONAME,desctext,100);
		expecting=0;
		FileListBox1->Mask="*.BF";
		ext=".BF";
		FileListBox1->FileType<<ftNormal;
		Save->Visible=true;
		if (!squelchdiscard)
			Discard->Enabled=
				Discard->Visible=true;
		Description->Font->Color=clRed;
		Description->Color=clYellow;
		DirName->Enabled=
			DirName->Visible=false;
		PathList->Enabled=
			PathList->Visible=true;
	break;
	case FM_SaveDiscard:
		fakedir=true;
		LoadString(HInstance,TEXT_SAVEALERTTITLE,captiontext,50);
		LoadString(HInstance,TEXT_SAVEALERT,desctext,100);
		expecting=0;
		FileListBox1->Mask="*.BF";
		ext=".BF";
		FileListBox1->FileType<<ftNormal;
		FileListBox1->Enabled=false;
		FileListBox1->Color=clInactiveCaptionText;
		FileName->Enabled=false;
		Save->Visible=true;
		if (!squelchdiscard)
			Discard->Enabled=
				Discard->Visible=true;
		Description->Font->Color=clRed;
		Description->Color=clYellow;
		DirName->Enabled=
			DirName->Visible=false;
		PathList->Enabled=false;
		PathList->Visible=true;
	break;
	case FM_NewBfDirs:
		fakedir=true;
		LoadString(HInstance,TEXT_SELECTFILE,captiontext,50);
		LoadString(HInstance,TEXT_NEWMISS,desctext,100);
		LoadString(HInstance,TEXT_SUREOPENMISS,suretext,100);
		expecting=mrOk;
		FileListBox1->Mask="*.BF";
		ext=".BF";
		FileListBox1->FileType<<ftNormal;
		New->Visible=true;
		Open->Visible=true;
		DirName->Enabled=
			DirName->Visible=false;
		PathList->Enabled=
			PathList->Visible=true;
	break;

	case FM_SaveBfDirs:
		fakedir=true;
		LoadString(HInstance,TEXT_SAVEFILE,captiontext,50);
		LoadString(HInstance,TEXT_SAVEMISSNAME,desctext,100);
		expecting=0;
		FileListBox1->Mask="*.BF";
		ext=".BF";
		FileListBox1->FileType<<ftNormal;
		Save->Visible=true;
		DirName->Enabled=
			DirName->Visible=false;
		PathList->Enabled=
			PathList->Visible=true;
	break;


	case FM_OpenFile:
		LoadString(HInstance,TEXT_SELECTFILE,captiontext,50);
		LoadString(HInstance,TEXT_OPENMISS,desctext,100);
		LoadString(HInstance,TEXT_SURENEWMISS,suretext,100);
		expecting=mrYes;
		FileListBox1->Mask="*.BF";
		ext=".BF";
		FileListBox1->FileType<<ftNormal;
		New->Visible=true;
		Open->Visible=true;
	break;
	case FM_NewFile:
		LoadString(HInstance,TEXT_SELECTFILE,captiontext,50);
		LoadString(HInstance,TEXT_NEWMISS,desctext,100);
		LoadString(HInstance,TEXT_SUREOPENMISS,suretext,100);
		expecting=mrOk;
		FileListBox1->Mask="*.BF";
		ext=".BF";
		FileListBox1->FileType<<ftNormal;
		New->Visible=true;
		Open->Visible=true;
	break;
	case FM_RenameFile:
		LoadString(HInstance,TEXT_SELECTFILE,captiontext,50);
		LoadString(HInstance,TEXT_RENAMEMISS,desctext,100);
		expecting=0;
		FileListBox1->Mask="*.BF";
		ext=".BF";
		FileListBox1->FileType<<ftNormal;
		if (currname.IsEmpty())
			Name->Visible=true;
		else
			Rename->Visible=true;
	break;
	case FM_OpenFrom:
		fakedir=true;
		LoadString(HInstance,TEXT_LOADFROMMISSTITLE,captiontext,50);
		LoadString(HInstance,TEXT_LOADFROMMISS,desctext,100);
		expecting=0;
		FileListBox1->Mask="*.BF";
		ext=".BF";
		FileListBox1->FileType<<ftNormal;
		Open->Visible=true;
		Drive->Visible=true;
		DirName->Enabled=true;
		Drive->Font->Color=clWindowText;
		DirName->Font->Color=clWindowText;
	break;
	case FM_OpenFromPilot:
		LoadString(HInstance,TEXT_LOADFROMPILOTTITLE,captiontext,50);
		LoadString(HInstance,TEXT_LOADFROMPILOT,desctext,100);
		expecting=0;
		FileListBox1->Mask="*.PLT";
		ext=".PLT";
		FileListBox1->FileType<<ftNormal;
		Open->Visible=true;
		Drive->Visible=true;
		DirName->Enabled=true;
		Drive->Font->Color=clWindowText;
		DirName->Font->Color=clWindowText;
	break;
	case FM_Save:
	case FM_SaveAs:
		LoadString(HInstance,TEXT_SAVEFILE,captiontext,50);
		LoadString(HInstance,TEXT_SAVEMISSNAME,desctext,100);
		expecting=0;
		FileListBox1->Mask="*.BF";
		ext=".BF";
		FileListBox1->FileType<<ftNormal;
		Save->Visible=true;
	break;
	}
	FileListBox1->Directory=path;
	DirName->Directory=path;


	Caption=captiontext;
	Description->Caption=desctext;
	confirm=suretext;

	Title->Text=currtitle;
//	if (FileName->Enabled)
  //		FileName->SetFocus();
	FileName->Text=currname;

	forever
	{

		int result=TForm::ShowModal();

		if (result!=mrCancel)
		{
			if (expecting && expecting!=result)
			{	//confirm dialogue can generate repeat...
				if (Application->MessageBox(suretext,desctext,MB_YESNO+MB_ICONQUESTION)==IDNO)
					continue;
			}
			if (mode==FM_OpenFrom || mode==FM_OpenFromPilot)
				currname=FileListBox1->Directory+"\\"+FileName->Text;
			else
				currname=FileName->Text;
			currtitle=Title->Text;
		}
//	  char *dirname=FILEMAN.namenumberedfile(dirnum(UByte(14)));
  //	  dirname[strlen(dirname)-7]=0;
	//  strcat(dirname,"meditor");
    	DirName->Visible=true;

//	dirnums[0]=dirnums[0];
//	expecting=expecting;
//	confirm=confirm;
//	dirmode=dirmode;
//	fakedir=fakedir;
//	filemode=filemode;
//	ext=ext;
//	InputTitle=InputTitle;
//	CurrDirNum=CurrDirNum;
//	HomeDir=HomeDir;
//	squelchdiscard=squelchdiscard;




		DirName->Directory=HomeDir;
		fakedir=false;
		return result;
	}
}

void __fastcall TFileLoadSave::FormShow(TObject *Sender)
{
	if (FileName->Enabled)
		FileName->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TFileLoadSave::PathListClick(TObject *Sender)
{
   CurrDirNum=dirnums[PathList->ItemIndex];
   AnsiString s=PathList->Items->Strings[PathList->ItemIndex];
   FileListBox1->Directory=s;
}
//---------------------------------------------------------------------------

