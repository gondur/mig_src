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

// Load.cpp : implementation file
//

#include "stdafx.h"
#include "io.h"
#include "mig.h"
#include "Load.h"
#include "savegame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif
LoadSaveDescriminate  CLoad::loadsaveallowall;
/////////////////////////////////////////////////////////////////////////////
// CLoad dialog


CLoad::CLoad(int dialresource,LSD_State initialstate,
		FileNum dirnamei,CString wildcardi,CString& defaultandreturn,
		const LoadSaveDescriminate& loadsavediscriminatori,
		CWnd* pParent /*=NULL*/)
	: RowanDialog(dialresource, pParent),
	filename(defaultandreturn),
	loadsavediscriminator(loadsavediscriminatori)
{
	acnum=initialstate;
	groupnum=dirnamei;
	dirname=dirnamei;
	wildcard=wildcardi;
	
//	filename = "";


	//{{AFX_DATA_INIT(CLoad)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CLoad::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLoad)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX,IDC_FILEOK,m_IDC_FILEOK);
	DDX_Control(pDX,IDC_RLISTBOXFILE,m_IDC_RLISTBOXFILE);
	DDX_Control(pDX,IDC_LOADNAME,m_IDC_LOADNAME);
	DDX_Control(pDX,IDC_SAVENAME,m_IDC_SAVENAME);
	DDX_Control(pDX,IDCX_SAVENAME,m_IDCX_SAVENAME);
	//}}AFX_DATA_MAP
	if (m_IDCX_SAVENAME.m_hWnd)
		m_IDCX_SAVENAME.SetLimitText(40);

}


BEGIN_MESSAGE_MAP(CLoad, CDialog)
	//{{AFX_MSG_MAP(CLoad)
	ON_MESSAGE( WM_SELECTTAB, OnSelectTab)
	ON_EN_UPDATE(IDCX_SAVENAME, OnUpdateSavename)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CLoad message handlers

BEGIN_EVENTSINK_MAP(CLoad, CDialog)
    //{{AFX_EVENTSINK_MAP(CLoad)
	ON_EVENT(CLoad, IDC_SAVENAME, 2 /* TextChanged */, OnTextChangedSavename, VTS_I4)
	ON_EVENT(CLoad, IDC_SAVENAME, 3 /* ReturnPressed */, OnReturnPressedSavename, VTS_BSTR)
	ON_EVENT(CLoad, IDC_RLISTBOXFILE, 1 /* Select */, OnSelectRlistboxfile, VTS_I4 VTS_I4)
	ON_EVENT(CLoad, IDC_FILEOK, 1 /* Clicked */, OnClickedFileok, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CLoad::OnSelectTab()
{
	if (listempty)
		((RowanDialog*)parent->parent)->acnum=acnum;
	acnum&=LDS_DISABLE_SEP-1;
	if (!listempty)
		((RowanDialog*)parent->parent)->acnum=acnum;
	((RowanDialog*)parent->parent)->groupnum=groupnum;
	for (RowanDialog* other=(RowanDialog*)parent->fchild;other;other=(RowanDialog*)other->sibling)
		if (other!=this)
				other->acnum|=LDS_DISABLE_SEP;
	if (acnum==LSD_LOAD)
	{
		CRStatic*   s=GETDLGITEM(IDC_LOADNAME);
		filename=s->GetString()+strpbrk(wildcard, ".");
	}
	else if (acnum==LSD_SAVE)
	{
		if (m_IDCX_SAVENAME.m_hWnd)
		{
			CString buffer;
			m_IDCX_SAVENAME.GetWindowText(buffer);
			filename=buffer+strpbrk(wildcard, ".");
		}
		else
		{
			CREdit* e=GETDLGITEM(IDC_SAVENAME);
			filename=e->GetCaption()+strpbrk(wildcard, ".");
		}
	}
	
//	PrintFileName();
}

void CLoad::OnTextChangedSavename(LPTSTR text) 
{
   //## add ext to returned string ->filename
	currrow = -1;
	CRListBox*	l=GETDLGITEM(IDC_RLISTBOXFILE);
	l->SetHilightRow(currrow);
	trunc(text,20);

	CString ext;
	ext = strpbrk(wildcard, "."); 
	filename = text + ext;

}
void CLoad::OnUpdateSavename()
{
	CString buffer;
	m_IDCX_SAVENAME.GetWindowText(buffer);
	filename=buffer+strpbrk(wildcard, ".");
}

void CLoad::OnReturnPressedSavename(LPCTSTR text) 
{
	OnOK();
	
}

void CLoad::OnSelectRlistboxfile(long row, long column) 
{
	if (currrow == row)
	{
		OnOK();
	}else
	{
		if (!listempty)
		{
			CRListBox*	l=GETDLGITEM(IDC_RLISTBOXFILE);
			filename = (char*)l->GetString(row, column);
	//##strip *
	//		filename = filename + wildcard;
			CString ext;
			ext = strpbrk(wildcard, "."); 
			if (filename!="")
				filename = filename + ext;

			PrintFileName();
			currrow = row;
		}
	}

}

void CLoad::PrintFileName()
{
//##strip ext here
	char* ext;
	char	filename_noext[256];
	strncpy(filename_noext,filename,255);
	if (filename!="")
	{
		ext = strpbrk(filename_noext, ".");
		if (ext)
			*ext = 0;
	}
	if (acnum==LSD_LOAD || acnum==LSD_LOAD_DESELECT)
	{
		CRStatic*   s=GETDLGITEM(IDC_LOADNAME);
		s->SetString(filename_noext);
	}
	else
	{
		if (m_IDCX_SAVENAME.m_hWnd)
		{
			m_IDCX_SAVENAME.SetWindowText(filename_noext);
		}
		else
		{
			CREdit* e=GETDLGITEM(IDC_SAVENAME);
			e->SetCaption(filename_noext);
		}
	}

}


void	CLoad::MakeFileList()
{
	CRListBox*	l=GETDLGITEM(IDC_RLISTBOXFILE);
	l->Clear();
	int segindexes[(int)LoadSaveDescriminate::MAXPRIORITY+1]={0};
	l->AddColumn(200);
	int found=-1;
	_finddata_t filedesc;
	char buffer[120];
	char* dirnametext=
		File_Man.namenumberedfile(File_Man.fakefile(dirname,wildcard),buffer);
	long	ffh=_findfirst(dirnametext,&filedesc);
	listempty=true;
	int beforestar=0;
	int afterstar=0;
	while (wildcard[beforestar]!='*') beforestar++;
	afterstar=wildcard.GetLength()-beforestar-1;	  //CString
	strcpy(buffer,filename);
	if (buffer[0])
		buffer[strlen(buffer)-afterstar]=0;
	if (ffh!=-1)
	{
		do{
			int count=loadsavediscriminator.AllowFile(dirname,filedesc.name);
			if (count>0)
			{
				listempty=false;
				count--;
				l->InsertRow(segindexes[count]);
				//strip prefix and postfix from filename here
				filedesc.name[strlen(filedesc.name)-afterstar]=0;
				l->ReplaceString(filedesc.name+beforestar,segindexes[count],0);
				if (found>=segindexes[count])
					found++;
				else
				if (!strcmp(buffer+beforestar,filedesc.name+beforestar))
					found=segindexes[count];
				while(--count>=0)
					segindexes[count]++;
			}
		}while (!_findnext(ffh,&filedesc));
		_findclose(ffh);
	}
	if (found==-1)
		if (acnum==LSD_SAVE || acnum==LSD_SAVE_DESELECT)
		{
			l->InsertRow(0);
			l->ReplaceString(buffer+beforestar,0,0);
			found=0;
		}
		else
		{
			CRStatic*   s=GETDLGITEM(IDC_LOADNAME);
			s->SetString("");
			if (acnum==LSD_LOAD)	//current load panel
			{
				filename="";
			}
		}
	else
		if (acnum==LSD_SAVE_DESELECT || acnum==LSD_LOAD_DESELECT)
			((RowanDialog*)parent->parent)->acnum=(int)this;


	currrow=found;
	l->SetHilightRow(currrow);


}
BOOL CLoad::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	PrintFileName();

	MakeFileList();

//	currrow = 0;
//	filename = "file0";
//	CRListBox*	l=GETDLGITEM(IDC_RLISTBOXFILE);


//	l->SetHilightRow(currrow);


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CLoad::OnClickedFileok() 
{
	if ((!listempty || acnum==LSD_SAVE) && (filename=="" || filename[0]=='.'))
		return;
	OnOK();
}
