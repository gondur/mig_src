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

// Comit_e.cpp : implementation file
//

#define F_SOUNDS
#define F_BATTLE
#define F_COMMON
#include "stdafx.h"
#include "mig.h"
#include "Comit_e.h"
#include "rlistbox.h"
#include "Camplist.h"
#include	"node.h"
#include "bfnumber.h"
#include	"persons2.h"
#include	"migview.h"
#include	"mytime.h"

//#include	"persons2.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif
CDirects2 *  CComit_e::directivelines[MAXDIRECTIVES];
CSelectionResults *  CComit_e::directivedetails[MAXDIRECTIVES];
class CComit_e *  CComit_e::This = NULL;
/////////////////////////////////////////////////////////////////////////////
// CComit_e dialog


CComit_e::CComit_e(CWnd* pParent /*=NULL*/)
	: RowanDialog(CComit_e::IDD, pParent)
{
	//{{AFX_DATA_INIT(CComit_e)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	This = this;


}


void CComit_e::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CComit_e)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX,IDC_TSQUAD,m_IDC_TSQUAD);
	DDX_Control(pDX,IDC_TSQUAD2,m_IDC_TSQUAD2);
	DDX_Control(pDX,IDC_TSQUAD3,m_IDC_TSQUAD3);
	DDX_Control(pDX,IDC_TSQUAD4,m_IDC_TSQUAD4);
	DDX_Control(pDX,IDC_TSQUAD5,m_IDC_TSQUAD5);
	DDX_Control(pDX,IDC_AUTOGENERATE,m_IDC_AUTOGENERATE);
	DDX_Control(pDX,IDC_AUTODISPLAY,m_IDC_AUTODISPLAY);
	DDX_Control(pDX,IDC_TSQUAD6,m_IDC_TSQUAD6);
	DDX_Control(pDX,IDC_TSQUAD7,m_IDC_TSQUAD7);
	DDX_Control(pDX,IDCALPHAALLOWED,m_IDCALPHAALLOWED);
	DDX_Control(pDX,IDC_TSQUAD8,m_IDC_TSQUAD8);
	DDX_Control(pDX,IDC_TSQUAD9,m_IDC_TSQUAD9);
	DDX_Control(pDX,IDC_STRIKEINUSE,m_IDC_STRIKEINUSE);
	DDX_Control(pDX,IDC_FIGHTERSINUSE,m_IDC_FIGHTERSINUSE);
	DDX_Control(pDX,IDC_TARGETSINUSE,m_IDC_TARGETSINUSE);
	DDX_Control(pDX,IDC_MISSIONSINUSE,m_IDC_MISSIONSINUSE);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CComit_e, CDialog)
	//{{AFX_MSG_MAP(CComit_e)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CComit_e message handlers

BOOL CComit_e::OnInitDialog() 
{
	CDialog::OnInitDialog();
	RDialog* parent=(RDialog*)GetParent();
//	parent->SetMaxSize(CRect(0,0,450,380));

	dir_ctrl.AllocateAc();

	CRStatic*   s=GETDLGITEM(IDC_STRIKEINUSE);
	s->SetString(CSprintf("%i",dir_ctrl.TotalStrikeAcInUse));

	s=GETDLGITEM(IDC_FIGHTERSINUSE);
	s->SetString(CSprintf("%i",dir_ctrl.TotalFighterACInUse));

	s=GETDLGITEM(IDC_MISSIONSINUSE);
	s->SetString(CSprintf("%i",dir_ctrl.MissionsAlreadyDefined));

	s=GETDLGITEM(IDC_TARGETSINUSE);
	s->SetString(CSprintf("%i",dir_ctrl.TargetsAlreadyDefined));


	
	CRButton* b = GETDLGITEM(IDC_AUTOGENERATE);
	b->SetPressed(dir_ctrl.autogen);

	b = GETDLGITEM(IDC_AUTODISPLAY);
	b->SetPressed(dir_ctrl.autodisplay);



	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_EVENTSINK_MAP(CComit_e, CDialog)
    //{{AFX_EVENTSINK_MAP(CComit_e)
	ON_EVENT(CComit_e, IDC_CAMPLIST, 1 /* Clicked */, OnClickedCamplist, VTS_NONE)
	ON_EVENT(CComit_e, IDJ_TITLE, 3 /* OK */, OnOKTitle, VTS_NONE)
	ON_EVENT(CComit_e, IDC_AUTOGENERATE, 3 /* OK */, OnOKAutogenerate, VTS_NONE)
	ON_EVENT(CComit_e, IDC_AUTODISPLAY, 3 /* OK */, OnOKAutodisplay, VTS_NONE)
	ON_EVENT(CComit_e, IDC_AUTOGENERATE, 1 /* Clicked */, OnClickedAutogenerate, VTS_NONE)
	ON_EVENT(CComit_e, IDC_AUTODISPLAY, 1 /* Clicked */, OnClickedAutodisplay, VTS_NONE)
	ON_EVENT(CComit_e, IDCALPHAALLOWED, 1 /* Clicked */, OnClickedCalphaallowed, VTS_NONE)
	ON_EVENT(CComit_e, IDJ_TITLE, 1 /* Clicked */, OnClickedTitle, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CComit_e::OnClickedCamplist() 
{
}
void CComit_e::OnOKTitle() 
{
	if (Todays_Packages.PackageHasBeenEdited())
	{
		int rv = RDialog::RMessageBox(IDS_NEWMISSIONS, IDS_EDITSLOST,NULL,IDS_OK,IDS_CANCEL);
		if (rv > 1)
			return;
	}

	Todays_Packages.DeleteNonRedoPackages();

	dir_ctrl.SaveDirectiveChanges();

	dir_ctrl.SetPackagesFromDirectives();	

	m_pView->m_mapdlg.Invalidate();


	OnOK();


	
}

void CComit_e::OnOKAutogenerate() 
{
}

void CComit_e::OnOKAutodisplay() 
{
	
}

void CComit_e::OnClickedAutogenerate() 
{
	if (dir_ctrl.autogen)
		dir_ctrl.autogen = false;
	else
		dir_ctrl.autogen = true;
	
}

void CComit_e::OnClickedAutodisplay() 
{
	if (dir_ctrl.autodisplay)
		dir_ctrl.autodisplay = false;
	else
		dir_ctrl.autodisplay = true;
	
}

void CComit_e::OnClickedCalphaallowed() 
{
	if(dir_ctrl.alphastrikesallowed)
		dir_ctrl.alphastrikesallowed = false;
	else
		dir_ctrl.alphastrikesallowed = true;
	RedrawAll();

}
void CComit_e::OnClickedTitle() 
{
}

void CComit_e::RedrawAll()
{
	dir_ctrl.AllocateAc();



	int i = 0;

	while	(		(i < MAXDIRECTIVES)
			)
	{
		directivelines[i]->Redraw();
		i++;
	}
	i = 0;
	if (LoggedChild(0))
	{
		while	(		
					(i < (MAXDIRECTIVES - 1))
				)
		{
			directivedetails[i]->Redraw();
			i++;
		}
	}
}
void DirControl::InitDirectivesStruct()
{

	for (char i = 0; i < MAXDIRECTIVES; i++)
	{
		for (char j = 0; j < MAXMISSIONS; j++)
		{
			directives[i].missions[j].score = -1;
			directives[i].missions[j].target = UID_NULL;
			directives[i].missions[j].missionset = false;

		}
	}
}


void DirControl::ModifyAcInGrp(int packnum, int wavenum, int groupnum, int squad, int numflights)
{
	if (Todays_Packages[packnum][wavenum][groupnum].uid != UID_Null)  //RDH 19/06/99
	{
		Todays_Packages[packnum][wavenum][groupnum].SetSquad(squad);
		Todays_Packages[packnum][wavenum][groupnum].SetFlights(numflights);
		if (groupnum ==0)
			Todays_Packages[packnum].RecalcRoutePositions();
	}	
//	info_airgrp* a=*Persons2::ConvertPtrUID(Todays_Packages[packnum][wavenum][groupnum].uid);
//	a->type= squad;
//	a->inform= numflights*4;
//	Todays_Packages[packnum][wavenum][groupnum].numflights=numflights;

}


int  DirControl::MakePackage(int d, int i)
{
	int duty;
	duty = DC_BOMB;

	switch (directives[d].missions[i].profile)
	{
		case	FIL_ALPHASTRIKE:
		{
			duty = DC_BOMB;
			break;
		}
		case	FIL_FBSTRIKE:
		{
			duty = DC_BOMB;
			break;
		}
		case	FIL_MEDBSTRIKE:
		{
			duty = DC_BOMB;
			break;
		}
		case	FIL_CAS:
		{
			duty = DC_CAS;
			break;
		}
		case	FIL_BARCAP:
		{
			duty = DUTYBARCAP;
			break;
		}
		case	FIL_ARMEDRECONN:
		{
			duty = DC_AR;
			break;
		}
	}

	int packnum=Todays_Packages.NewPackage(directives[d].missions[i].target, duty);
	return (packnum);
}
void DirControl::UpdatePackageAircraft(int packnum, int d, int i)
{
	if (directives[d].missions[i].profile == FIL_BARCAP)
	{
		if (directives[d].missions[i].group[0].numflights != 0)
		{
			ModifyAcInGrp(packnum, 0, 0, 
						directives[d].missions[i].group[0].squadron, 
						directives[d].missions[i].group[0].numflights);
			Todays_Packages[packnum].ClearGroup(0,1);
			Todays_Packages[packnum].ClearGroup(0,2);
		}
		if (directives[d].missions[i].group[2].numflights != 0)
		{
			if (!Todays_Packages[packnum][1].firstwp)
				Todays_Packages[packnum].MakeWave(1,DUTYMIGCAP);

			ModifyAcInGrp(packnum, 1, 0, 
						directives[d].missions[i].group[2].squadron, 
						directives[d].missions[i].group[2].numflights);
			Todays_Packages[packnum].ClearGroup(1,1);
			Todays_Packages[packnum].ClearGroup(1,2);
		}else
		{
   			Todays_Packages[packnum].ClearWave(1);
		}
//DEADCODE RDH 26/04/99 		Todays_Packages[packnum].ClearWave(2);

	}else
	{
		if (	Todays_Packages[packnum][1][0].numflights			  //DAW 12/16/99
			&&	Todays_Packages[packnum][1][0].squadron==Todays_Packages[packnum][0][0].squadron //DAW 12/16/99
			)														  //DAW 12/16/99
		{															  //DAW 12/16/99
			if (directives[d].missions[i].group[0].numflights>Todays_Packages[packnum][1][0].numflights) //DAW 12/16/99
			{
				directives[d].missions[i].group[0].numflights-=Todays_Packages[packnum][1][0].numflights; //DAW 12/16/99
				Todays_Packages[packnum][1][0].SetSquad(directives[d].missions[i].group[0].squadron);
			}
			else													  //DAW 12/16/99
				Todays_Packages[packnum].ClearWave(1);				  //DAW 12/16/99
		}															  //DAW 12/16/99

		 for (char k = 0; k < Profile::MAX_GROUPS; k++)
		 {
			if (directives[d].missions[i].group[k].numflights != 0)
			{

				ModifyAcInGrp(packnum, 0, k, 
						directives[d].missions[i].group[k].squadron, 
						directives[d].missions[i].group[k].numflights);
			}else
			{
				Todays_Packages[packnum].ClearGroup(0,k);
			}
		 }
	 } 
   

}
void DirControl::SetPackagesFromDirectives()
{
	for (char d = 0; d < (MAXDIRECTIVES - 1);d++)
		for (char i = 0; i < directives[d].targets ;i++)	
		{
			if (		(directives[d].missions[i].missionset)
					&&	(directives[d].missions[i].target != UID_NULL)
				)
			{
				int packnum=Todays_Packages.FindPackage();
		  		
				if (packnum >=0)
				{
#ifndef	ACTUALLY_NEVER_DEFINED_JUST_PUT_HashIFNDEF_OR_HashIFDEF
					 Todays_Packages.pack[packnum].packagetarget=directives[d].missions[i].target;
					 Todays_Packages.PreLoad(packnum,directives[d].missions[i].profile,NULL,false,true);
					 Todays_Packages.Load(packnum,directives[d].missions[i].profile);
#else
//used to bootstrap profiles
					 packnum=MakePackage(d,i);
					if (directives[d].missions[i].group[Profile::GRPFLAKSUPP].numflights != 0)
						Todays_Packages[packnum][0].MakeGroup(true,true);
					if (directives[d].missions[i].group[Profile::GRPESCORT].numflights != 0)
						Todays_Packages[packnum][0].MakeGroup(true,false);
					Todays_Packages[packnum].RecalcRoutePositions();
#endif  

					UpdatePackageAircraft(packnum,d,i);
					//done again because squadron may have changed
					Todays_Packages[packnum].RecalcRoutePositions();
					

				}
			}
		}



//	SupplyTree::dir_ctrl = dir_ctrl;

//	int i = 0;
//	for (char directive = 0; directive < MAXDIRECTIVES; directive++)
//	{
//		for (char j = 0; j < CComit_e::This->directives[directive].targets ;j++)	
//		{
//			if (directives[directive].missions[j].missionset)
//			{
//				PackageList::PreLoad(i,FIL_NULL, false, true);
//		 		PackageList::Load(i,NULL);
//				i++;
//			}
//		}
//	}

}
void DirControl::AutoGenerate()
{
	AllocateAc();
	SetPackagesFromDirectives();
}

CON	 DirControl::DirControl()
{
	LoadDirectiveChanges();
	propfirst[0] = SQ_F51;
	propfirst[1] = SQ_F80;
	propfirst[2] = SQ_F84;
//   	maxscore[0] =	0;
  // 	maxscore[1] =	MAXMOBILESONDOUBLETRACK*STORES_TRAIN;
   	//maxscore[2] =	STORES_MAXSUPPLY;
//   	maxscore[3] =	12;
  // 	maxscore[4] =	MAXMOBILESONDOUBLETRACK*STORES_TRAIN;
   	//maxscore[5] =	MAXMOBILESONDOUBLETRACK*STORES_TRAIN;
//   	maxscore[6] =	200;



}
void DirControl::LoadDirectiveChanges()
{
	DirControlData::operator = (MMC.directives);
	for(int i = 0; i< MAXDIRECTIVES;i++)
	{
		directives[i] . SG_Directive::operator = (MMC.directives.directives[i]);
	}

}

void DirControl::SaveDirectiveChanges()
{
	MMC.directives . DirControlData::operator = (*this);
	for(int i = 0; i< MAXDIRECTIVES;i++)
	{
		MMC.directives.directives[i] . SG_Directive::operator = (directives[i]);
	}
}

void DirControl::AddMission(int d, int j, SupplyNode*  currnode)
{
	for (char i = (MAXMISSIONS - 1); i > j ; i--)
	{
		directives[d].missions[i] = directives[d].missions[i - 1];
	}	
	directives[d].missions[i].score = currnode->currentstores;
	directives[d].missions[i].target = currnode->associated_item;
	directives[d].missions[i].node  = currnode;
	directives[d].missions[i].profile =  FIL_FBSTRIKE;

	directives[d].targets++;
}
void DirControl::ListSupplyNodes(int d)
{
	SupplyNode* currnode;
	SupplyTree::Supply2UID rel;

	currnode = SupplyTree::FirstNode;
	while (currnode->type != LASTONE)
	{

		if  (		(currnode->attackstats.damagelevel < 100)
				&&
					(		(currnode->currentstores < (3 * maxscore[d] / 4))
						||	(alphastrikesallowed)
					)
				&&	(currnode->status != BEHINDBLUELINES)

			)
		{
			for (char j = 0; j < MAXMISSIONS; j++)
				if 	(currnode->currentstores > directives[d].missions[j].score)
				{
					AddMission(d,j,currnode);
					break;
				}
		}		
		currnode = currnode->next;
	};
}
void DirControl::AddAfMission(int d, int j, int af, int score)
{
	for (char i = (MAXMISSIONS - 1); i > j ; i--)
	{
		directives[d].missions[i] = directives[d].missions[i - 1];
	}	
	directives[d].missions[i].score = score;
	directives[d].missions[i].profile =  FIL_FBSTRIKE;
	directives[d].missions[i].target = SupplyTree::airfieldinfo[af].airfield;
	directives[d].missions[i].node  = SupplyTree::airfieldinfo[af].northnodes[0];
	directives[d].targets++;
}

void DirControl::ListAirfields(int d)
{

	for (int i = 0; i < SupplyTree::AIRFIELDSINWORLD; i++)
	{
		int score =   (1 + (int)(SupplyTree::airfieldinfo[i].type)) *  SupplyTree::airfieldinfo[i].capacity;
		if  (		(SupplyTree::airfieldinfo[i].attackstats.damagelevel < 100)
				&&
				(		(score < (3 * maxscore[d] / 4))
					||	(alphastrikesallowed)
				)
			)
		{
			for (char j = 0; j < MAXMISSIONS; j++)
			{
				if 	(		(score > directives[d].missions[j].score)
						&&	 (SupplyTree::airfieldinfo[i].nationality != NAT_BLUE)
					)
				{
					AddAfMission(d,j,i, score);
					break;
				}
			}
		}

	}
}
void DirControl::AddChokeMission(int d, int j, SupplyRoute*  currroute)
{
	for (char i = (MAXMISSIONS - 1); i > j ; i--)
	{
		directives[d].missions[i] = directives[d].missions[i - 1];
	}	
	directives[d].missions[i].score = currroute->maxcapacitysummer;
	directives[d].missions[i].profile =  FIL_FBSTRIKE;
	directives[d].missions[i].target = currroute->associated_brdg;
	SupplyNode*	node=SupplyTree::FindSupplyNodeForItem(currroute->associated_brdg);

	directives[d].missions[i].node  = node;
	directives[d].targets++;
}

void DirControl::ListChokes(int d)
{
	SupplyRoute* currroute;
	currroute = SupplyTree::FirstRoute;
	SupplyTree::Supply2UID rel;
	SupplyNode*	node;

	while (currroute->status != SR_LASTONE)
	{
		if 	(currroute->associated_brdg != NULL)
		{
			node=SupplyTree::FindSupplyNodeForItem(currroute->associated_brdg,&rel);
			if (		(currroute->attackstats.damagelevel < 100)
					&&  (		(		(currroute->maxcapacitysummer < (3 * maxscore[d] / 4))
									&&	(!CloseToChina(5, currroute->supplier))
								)
							||	(alphastrikesallowed)
						)
					&&	(node->status != BEHINDBLUELINES) 
				)
			{
				for (char j = 0; j < MAXMISSIONS; j++)
					if 	(currroute->maxcapacitysummer > directives[d].missions[j].score)
					{
						AddChokeMission(d,j,currroute);
						break;
					}
			}
		}
		currroute = currroute->next;
	};
}
void DirControl::AddRouteMission(int d, int j, SupplyRoute*  currroute, SWord type)
{
	for (char i = (MAXMISSIONS - 1); i > j ; i--)
	{
		directives[d].missions[i] = directives[d].missions[i - 1];
	}	
	directives[d].missions[i].score = currroute->storeslaunched;
	directives[d].missions[i].profile =  FIL_ARMEDRECONN;
	directives[d].missions[i].target = currroute->redsupplyUID;
	directives[d].missions[i].suppliee = currroute->suppliee->associated_item;
	directives[d].missions[i].node  = currroute->supplier;
	directives[d].targets++;
}

void DirControl::ListRoutes(int d, SWord type)
{
	SupplyRoute* currroute;

	currroute = SupplyTree::FirstRoute;
	while (currroute->status != SR_LASTONE)
	{
		if (	(currroute->status != SR_RESTING)	&&	(currroute->storespermobile == type)	&&	(currroute->supplier->status != BEHINDBLUELINES) && (currroute->redsupplyUID))
		{
			for (char j = 0; j < MAXMISSIONS; j++)
				if 	(currroute->storeslaunched > directives[d].missions[j].score)
				{
					AddRouteMission(d,j,currroute, type);
					break;
				}
		}
		currroute = currroute->next;
	};


}
void DirControl::AddCASMission(int d, int j, int score, SupplyLine* sl)
{
	for (char i = (MAXMISSIONS - 1); i > j ; i--)
	{
		directives[d].missions[i] = directives[d].missions[i - 1];
	}	
	directives[d].missions[i].score = score;
	directives[d].missions[i].profile =  FIL_CAS;
	directives[d].missions[i].target = sl->frontline->forward->suppliee->associated_item;
	directives[d].missions[i].node  = sl->frontline->forward->suppliee;
	directives[d].targets++;

}
void DirControl::ProcessFrontLine(int d, SupplyLine* sl)
{
	if  (		(sl->frontline->type == BATTLEFIELD)
			&&	(sl->frontline->status == FRONTLINE)
			&&	(		(sl->initiative == REDATTACKING)
					||	(sl->initiative == BLUEATTACKING)
				)
		)			
	{
		int score = 0;
		TeamDef::Team blueforce;
		if	(		(sl->initiative==REDATTACKING)
			)
			blueforce = TeamDef::HOME;
		else
			blueforce = TeamDef::AWAY;

		for (int i=0;i<sl->groundbattle.usedteams;i++)
		{
			if (sl->groundbattle.teamlist[i].team==blueforce)
					score += sl->groundbattle.teamlist[i].strength;
			if (sl->groundbattle.teamlist[i].team!=blueforce)
					score -= sl->groundbattle.teamlist[i].strength;
		}
		if (score < 0)
			score = 0;
		for (char j = 0; j < MAXMISSIONS; j++)
			if 	(score > directives[d].missions[j].score)
				{
					AddCASMission(d, j, score, sl);
					break;
				}

	}
}

void DirControl::ListFrontLines(int d)
{
	ProcessFrontLine(d, &SupplyTree::WestRoute);
//DEADCODE RDH 12/07/99 	ProcessFrontLine(d, &SupplyTree::EastRoute);
	ProcessFrontLine(d, &SupplyTree::CentralRoute);

}
void DirControl::FindTargets(int directive)
{
	directives[directive].targets = 0;
	for (char j = 0; j < MAXMISSIONS; j++)
		directives[directive].missions[j].score = -1;

	switch	(directives[directive].type)
	{
		case SupplyTree::D_AIRSUPERIORITY:
		{
			maxscore[directive] = 0;
			directives[directive].targets = 1;
			break;													  //RDH 18/03/99
		}
		case SupplyTree::D_CHOKE:
		{
			maxscore[directive] = MAJ_TRAINSPERDAY*STORES_TRAIN;
			ListChokes(directive);
			break;
		}
		case SupplyTree::D_SUPPLY:
		{
			maxscore[directive] = STORES_MAXSUPPLY;
			ListSupplyNodes(directive);
			break;
		}
		case  SupplyTree::D_AIRFIELDS:
		{
			maxscore[directive] = 12;
			ListAirfields(directive);
			break;
		}
		case SupplyTree::D_RAIL:
		{
			maxscore[directive] = MAJ_TRAINSPERDAY*STORES_TRAIN;
			ListRoutes(directive, STORES_TRAIN);
			break;
		}
		case SupplyTree::D_ROAD:
		{
			maxscore[directive] = MAJ_TRUCKSPERDAY*STORES_TRAIN;
			ListRoutes(directive, STORES_TRUCK);
			break;
		}
		case SupplyTree::D_ARMY:
		{
			maxscore[directive] = 200;
			ListFrontLines(directive);
			break;
		}

	}
}
void	DirControl::AllocateStrike(int d, int i,char& note, int profile)
{//can only use for alphastrike because return message is specific

	if (		(directives[d].strikeac < 48)
			||	(acresource[SQ_F80] < 16)
			||	(acresource[SQ_F84] < 16)
			||	((acresource[SQ_B29] + acresource[SQ_B26]) < 16)
	   )
	   {
			note = SupplyTree::M_ALPHANOTPOSSIBLE ;
			directives[d].missions[i].missionset = false;
		}
		else
		{
			note = -1;
			int strike;
			if (acresource[SQ_B26] > 0)
				strike = SQ_B26;
			else
				strike = SQ_B29;

			directives[d].missions[i].group[Profile::GRPSTRIKE].squadron = strike;
			directives[d].missions[i].group[Profile::GRPSTRIKE].numflights = 4;
			acresource[strike] -= 16;

			directives[d].missions[i].group[Profile::GRPFLAKSUPP].squadron = SQ_F80;
			directives[d].missions[i].group[Profile::GRPFLAKSUPP].numflights = 4;
			acresource[SQ_F80] -= 16;


			directives[d].missions[i].group[Profile::GRPESCORT].squadron = SQ_F84;
			directives[d].missions[i].group[Profile::GRPESCORT].numflights = 4;
			acresource[SQ_F84] -= 16;

		   directives[d].missionsset++;
		   directives[d].missions[i].profile = FIL_ALPHASTRIKE;
		   directives[d].missions[i].missionset = true;

		}




}
void	DirControl::AllocateFighters(int fightersrequired, int d, int i) 
{
	//It is possible to allocate more than a squadron here
	//Put the second squadron in as group 2 and modify to wave 2 later
		directives[d].missions[i].group[0].numflights = 0;
		int squada = fightersrequired;
		int squadb;
		if (squada > acresource[SQ_F86A])
			squada = acresource[SQ_F86A];
		directives[d].missions[i].group[0].squadron = SQ_F86A;
		directives[d].missions[i].group[0].numflights = squada/4;
		acresource[SQ_F86A] -= 4*(squada/4);
		if (squada < fightersrequired)
		{
			squadb =  fightersrequired - squada;
			int group = 0;
			if (squada >= 4)
				group = 2;		//group 0 has been used for squada
			if (squadb > acresource[SQ_F86B])
				squadb = acresource[SQ_F86B];
			directives[d].missions[i].group[group].squadron = SQ_F86B;
			directives[d].missions[i].group[group].numflights = squadb/4 ;
			acresource[SQ_F86B] -= squadb;
		}
		directives[d].missions[i].escort = true;
}

bool	DirControl::AllocateTargets(int d, char inputstriketype, bool escortreq)
{
	bool acalloc = false;
	int fighters;
	int strikeac;
	int fightersrequired;
	char note;
	int strikeacrequired = 0;
	int fighteracrequired = 0;

//force armed reconn to have no escort
	if (		(directives[d].type == SupplyTree::D_RAIL)
			||	(directives[d].type == SupplyTree::D_ROAD)
		)
		escortreq = false;											  //RDH 25/06/99


	if (directives[d].type == SupplyTree::D_AIRSUPERIORITY)
	{
		if (directives[d].fighterac >= 4)
		{
			if  (		(acresource[SQ_F86A] >= 4)
					||	(acresource[SQ_F86B] >= 4)
				)
			{
				fightersrequired = directives[d].fighterac;
				for (int k = 0; k < MAX_DIRGROUPS; k++)
				{
					directives[d].missions[0].group[k].numflights = 0;
					directives[d].missions[0].group[k].squadron = -1;
				}

			 	AllocateFighters(fightersrequired, d, 0);
			   directives[d].missionsset++;
			   directives[d].missions[0].missionset = true;
			   directives[d].missions[0].target = UID_BrRdYalu; 
			   directives[d].missions[0].profile = FIL_BARCAP;
			   acalloc = true;


			}else
			{
				directives[d].missions[0].escort = false;
				directives[d].missions[0].note = SupplyTree::M_NOFIGHTERS;
			}
		}else
		{
			directives[d].missions[0].escort = false;
			directives[d].missions[0].note = SupplyTree::M_NOFIGHTERS;
		}
	}else
	{
//		char striketype;
		int escort, flak, strike;
		bool acavailable;
		for (int i = 0; i < directives[d].targets;i++)
		{
			char striketype = inputstriketype;
			bool targetalreadyalloc = TargetAlreadyAlloc(directives[d].missions[i].target);
			if  (		(targetalreadyalloc)
					&&	(striketype  == UNDECIDEDSTRIKE)					
				)
			{//when strike type is undecided we are in directives. In other cases it is ok to repeat 
				//a target
				directives[d].missions[i].note = SupplyTree::M_TARGETALREADYALLOC;
				directives[d].missions[i].missionset = false;

			}else
			{
				char tempbmb;
				bool canchangestriketype = false;
				if (striketype  == UNDECIDEDSTRIKE)
				{
					striketype = StrikeTypeRequired(d, i);
					canchangestriketype = true;
				}
				if (striketype == ALPHASTRIKE)
				{
					int  p = FIL_ALPHASTRIKE;

					if 	(alphastrikesallowed)
						AllocateAlphaStrike(d, i);
					else
						directives[d].missions[i].note = SupplyTree::M_ALPHASDISABLED;
				}else
				{
					firsttype = ACT_NOTSET;
					acavailable = false;
					for (int k  = 0; k < MAX_DIRGROUPS; k++)
					{
						tmpgroup[k].numflights = 0;
						tmpgroup[k].squadron  = -1;
					}
					
					if  (		(Miss_Man.currcampaignnum == MissMan::F84_CAMPAIGN)
							||	(Miss_Man.currcampaignnum == MissMan::F80_CAMPAIGN)
							||	(Miss_Man.currcampaignnum == MissMan::F86_CAMPAIGN)
							||	(directives[d].missions[i].profile == FIL_CAS)
							||	(!escortreq)
						)
						escort = 0;
					else
						escort = EscortRequired(directives[d].missions[i].node);
					if (	(escort == 0)
						||	(AllocAc(Profile::GRPESCORT, escort, directives[d].type, d))
						)
						{
							if  (	(Miss_Man.currcampaignnum == MissMan::F86_CAMPAIGN)
									||	(Miss_Man.currcampaignnum == MissMan::F80_CAMPAIGN)
									//no flak available in this campaign
									||
									(!escortreq)
								)
								flak = 0;
							else 
								flak = FlakRequired(directives[d].missions[i].target, directives[d].missions[i].node);
							
							if  (		(flak == 0)
									||	(AllocAc(Profile::GRPFLAKSUPP,flak, directives[d].type,d))
								)

							{
								if (	(		(striketype == MEDIUMBOMBERSTRIKE)
											&&	(		(directives[d].missions[i].profile == FIL_FBSTRIKE)
													||	(directives[d].missions[i].profile == FIL_MEDBSTRIKE) //RDH 08/06/99
												)
										)
										||	 (Miss_Man.currcampaignnum == MissMan::F86_CAMPAIGN)

									)
								{
									directives[d].missions[i].profile = FIL_MEDBSTRIKE;
									if (escortreq)
										strike = MedBomberStrikeRequired(d, i, directives[d].missions[i].target);
									else
										strike = 4;
									int j;							  //RDH 08/06/99
									if (Miss_Man.camp.directives.B29avail)					  //RDH 08/06/99
										j = SQ_B29;					  //RDH 08/06/99
									else							  //RDH 08/06/99
										j = SQ_B26;					  //RDH 08/06/99
									if (strike > acresource[j]) //RDH 08/06/99
										strike = acresource[j]; //RDH 08/06/99

									if (strike)
										if (AllocMedBomberStrike(strike, directives[d].type))
											acavailable = true;
								}else
								{

									if (escortreq)
										strike = FBStrikeRequired(d, i, directives[d].missions[i].target);
									else
										strike = 4;
									if (strike)
									{//if med bombers available then use them
											int j;
											if (Miss_Man.camp.directives.B29avail)
												j = SQ_B29;
											else
												j = SQ_B26;
											int medbmbstrike = MedBomberStrikeRequired(d, i, directives[d].missions[i].target);
											if (medbmbstrike > acresource[j]) //RDH 08/06/99
												medbmbstrike = acresource[j]; //RDH 08/06/99
											if (	(canchangestriketype)
												&&	( medbmbstrike <= acresource[j])
												&&	(medbmbstrike)
												&&	(		(directives[d].missions[i].profile ==  FIL_FBSTRIKE)
														||	(directives[d].missions[i].profile == FIL_MEDBSTRIKE) //RDH 08/06/99
													)
												)
											{
												if (AllocMedBomberStrike(medbmbstrike, directives[d].type))
												{
													acavailable = true;
													directives[d].missions[i].profile = FIL_MEDBSTRIKE;
													striketype = MEDIUMBOMBERSTRIKE;
												}
											}
											if (!acavailable)
											{
												if  (Miss_Man.currcampaignnum == MissMan::F84_CAMPAIGN)
												{
													if ((strike + flak + escort) > 16)
														strike = 8;
												}
												if (AllocAc(Profile::GRPSTRIKE , strike, directives[d].type, d))
													acavailable = true;
											}
									}
								}

							}
						}
						if  (acavailable)
						{
//DEADCODE RDH 12/06/99 							acalloc = true;
					 		for (int j = 0; j < MAX_DIRGROUPS ; j++)
							{
								if (tmpgroup[j].squadron < 2)	//f86
									fighteracrequired += 4*tmpgroup[j].numflights;
								else
									strikeacrequired += 4*tmpgroup[j].numflights;
							}
							if  (		(strikeacrequired <= directives[d].strikeac)
									&&	(fighteracrequired <= directives[d].fighterac)
								)	
							{
								acalloc = true;						  //RDH 12/06/99
								for (int k  = 0; k < MAX_DIRGROUPS; k++)
									acresource[tmpgroup[k].squadron] -= 4*tmpgroup[k].numflights;
								directives[d].missionsset++;
								directives[d].missions[i].note = -1;
//								if (striketype == MEDIUMBOMBERSTRIKE)
//									directives[d].missions[i].profile = FIL_MEDBSTRIKE;
//								else
//									directives[d].missions[i].profile = FIL_FBSTRIKE;

								for (k = 0; k < MAX_DIRGROUPS; k++)
									directives[d].missions[i].group[k] = tmpgroup[k];

								directives[d].missions[i].missionset = true;
							}else
							{
							 	for (int j = 0; j < MAX_DIRGROUPS ; j++)
								{
									if (tmpgroup[j].squadron < 2)	//f86
										fighteracrequired -= 4*tmpgroup[j].numflights;
									else
										strikeacrequired -= 4*tmpgroup[j].numflights;
								}
								
								directives[d].missions[i].note = SupplyTree::M_INSUFFAC;
								directives[d].missions[i].missionset = false;
							}

						}else
						{
							directives[d].missions[i].note = SupplyTree::M_INSUFFAC;
							directives[d].missions[i].missionset = false;
						}
					}
				}
		}
	}
	return (acalloc);
}
int 	DirControl::MedBomberStrikeRequired(int d, int i, UniqueID target)
{
	int strike;
	if (directives[d].missions[i].score > (maxscore[d] / 2))
		strike = 16;
	else
		strike = 8;
	return(strike);
}
bool 	DirControl::AllocMedBomberStrike(int strike,  int type)
{
	int j;
	if (Miss_Man.camp.directives.B29avail)
		j = SQ_B29;
	else
		j = SQ_B26;
	tmpgroup[Profile::GRPSTRIKE].squadron = j;

	if ( strike <= acresource[j])
	{
		tmpgroup[Profile::GRPSTRIKE].numflights += strike/4;
		return(true);
	} else
		return (false);
}
int 	DirControl::FBStrikeRequired(int d, int i, UniqueID target)
{

	int  strike = 0;
	if (directives[d].missions[i].score > (3 * (maxscore[d] / 4)))
		strike = 16;
	else if (directives[d].missions[i].score > (maxscore[d] / 2))
		strike = 8;
	else
		strike = 4;

	if (directives[d].missions[i].profile ==  FIL_ARMEDRECONN)
		strike = strike/2;
	if (strike < 4)
		strike = 4;

	return(strike);
}
int 	DirControl::EscortRequired(SupplyNode*  node)
{
	int escort =0;
	
	SWord i = 0;
	COORDS3D& nodeworld=
					Persons2::ConvertPtrUID(node->associated_item)->World;

	while (SupplyTree::airfieldinfo[i].nationality != NAT_ALIGN)
	{
		if 	(		(SupplyTree::airfieldinfo[i].activeac)
				&&	(SupplyTree::airfieldinfo[i].nationality != NAT_BLUE)
			)
		{
			COORDS3D& afworld=
						Persons2::ConvertPtrUID(SupplyTree::airfieldinfo[i].airfield)->World;
			 
			SLong delta = (afworld.Z - nodeworld.Z);
			SLong deltax = (afworld.X - nodeworld.X);
			if (deltax < 0)
				deltax = - deltax;
			delta =	delta + deltax;
			if 	(delta < MILES50)	
				escort += 8;
			else if 	(delta < MILES100)	
				escort += 4;

		}
		i++;
	}
	if (escort > 8)
		escort = 8;
	return (escort);

//DEADCODE RDH 18/03/99 	for (int i = 0; i < 3; i++)
//DEADCODE RDH 18/03/99 	{
//DEADCODE RDH 18/03/99 		for (int j = 0; j < SupplyTree::AIRFIELDSINWORLD; j++)
//DEADCODE RDH 18/03/99 			if (node->airfield[i] == SupplyTree::airfieldinfo[j].airfield)
//DEADCODE RDH 18/03/99 				break;
//DEADCODE RDH 18/03/99 
//DEADCODE RDH 18/03/99 
//DEADCODE RDH 18/03/99 		if 	(		(j < SupplyTree::AIRFIELDSINWORLD)
//DEADCODE RDH 18/03/99 				&&	(SupplyTree::airfieldinfo[j].nationality != NAT_BLUE)
//DEADCODE RDH 18/03/99 				&&	(SupplyTree::RedAcAtAirfield(SupplyTree::airfieldinfo[j].airfield))
//DEADCODE RDH 18/03/99 
//DEADCODE RDH 18/03/99 			)
//DEADCODE RDH 18/03/99 		{//active red ac close by
//DEADCODE RDH 18/03/99 				escort++;
//DEADCODE RDH 18/03/99 		}
//DEADCODE RDH 18/03/99 
//DEADCODE RDH 18/03/99 	}
//DEADCODE RDH 18/03/99 	if (escort == 3)
//DEADCODE RDH 18/03/99 		escort = 8;
//DEADCODE RDH 18/03/99 	else if (escort > 0)
//DEADCODE RDH 18/03/99 		escort = 4;

}
int 	DirControl::FlakRequired(UniqueID target, SupplyNode*  node)
{//need to base ac required on flak levels in supergroup
 //must not exceed 8
	int flak =0;
	if	(CloseToChina(8, node))
		flak = 6;
	else if	(CloseToChina(16, node))
		flak = 3;
//new code to modify flak requirement based on aaalevel				  //RDH 12/06/99
	int currlevel = 0 ;			//fraction of 255 measures likelihodd of available guns being manned
	SupplyTree::Supply2UID rel;
	node=SupplyTree::FindSupplyNodeForItem(target,&rel);
		switch (rel)
		{
			case SupplyTree::S2U_MAIN:
				currlevel=node->attackstats.aaalevel;
			break;
			case SupplyTree::S2U_AF0:
			case SupplyTree::S2U_AF1:
			case SupplyTree::S2U_AF2:
				currlevel=SupplyTree::FindAirfieldForItem(target)->attackstats.aaalevel;
			break;
			case SupplyTree::S2U_ROUTE0:
			case SupplyTree::S2U_ROUTE1:
			case SupplyTree::S2U_ROUTE2:
				currlevel=node->route[rel-SupplyTree::S2U_ROUTE0]->attackstats.aaalevel;
			break;
		}
	int flak2 = currlevel /32;
	if (flak2 > flak)
		flak = flak2;
	flak = 4 * (flak /4);
	if (flak > 8)
		flak = 8;

	return (flak);
}
int	DirControl::CategoryAvailable(int d, int squad)
{
	int  fighteracrequired = 0;
	int strikeacrequired = 0;
	for (int j = 0; j < MAX_DIRGROUPS ; j++)
	{
		if (tmpgroup[j].squadron < 2)	//f86
			fighteracrequired += 4*tmpgroup[j].numflights;
		else
			strikeacrequired += 4*tmpgroup[j].numflights;
	}
	if  (squad < 2)
		return (directives[d].fighterac - fighteracrequired);
	else
		return (directives[d].strikeac - strikeacrequired);

}
bool	DirControl::AllocAc(int grptype, int ac, int type, int d)
{
	int squadavail;

	if (grptype != Profile::GRPESCORT)
	{
		jetfirst[0] = SQ_F84;
		jetfirst[1] = SQ_F80;
		jetfirst[2] = SQ_F51;
		squadavail = FBTYPES;
	}else
	{
		jetfirst[0] = SQ_F86A;
		jetfirst[1] = SQ_F86B;
		jetfirst[2] = SQ_F84;
		jetfirst[3] = SQ_F80;
		jetfirst[4] = SQ_F51;
		squadavail = 5;
	}

	char*	choice;
	if (		(type == SupplyTree::D_CHOKE)
			||	(type == SupplyTree::D_SUPPLY)
			||	(type == SupplyTree::D_AIRFIELDS)
		)
		choice = jetfirst;
	else
		choice = propfirst;

	for (int i = 0; i < squadavail; i++)
	{

		int acalreadyusedoftype = CalcAcUsedofType(choice[i]);
		if  (		( ac <= (acresource[choice[i]] - 	acalreadyusedoftype))
				&&	(ac <= CategoryAvailable(d, choice[i]))
				&&	(		(firsttype == ACT_NOTSET)
						||	(		(firsttype == ACT_JET)
								&&	(		(choice[i] == SQ_F80)
										||	(choice[i] == SQ_F84)
										||	(choice[i] == SQ_F86A)
										||	(choice[i] == SQ_F86B)
									)
							)
						||	(		(firsttype == ACT_PROP)
								&&	(		(choice[i] == SQ_F51)
									)
							)


					)
			)
		{
			if (choice[i] == SQ_F51)
				firsttype = ACT_PROP;
			else
				firsttype = ACT_JET;
			tmpgroup[grptype].squadron = choice[i];
			tmpgroup[grptype].numflights = ac/4;
			return(true);
		}

	}
	//not enough aircraft of required type, lets see if we can use other type
	//ie insufficient jets, try props
	if(firsttype != ACT_NOTSET)
	{
		if  (		(firsttype == ACT_JET)
				&&	(choice == jetfirst)
			)
		{
			int acreq = ac;
			for (int i = 0; i < MAX_DIRGROUPS; i++)
				acreq +=  4*tmpgroup[i].numflights;
			if (acreq <= acresource[SQ_F51])
			{
				for (int i = 0; i < MAX_DIRGROUPS; i++)
					if (tmpgroup[i].numflights > 0)
						tmpgroup[i].squadron = SQ_F51;
	  			tmpgroup[grptype].squadron = SQ_F51;
				tmpgroup[grptype].numflights = ac/4;

				firsttype = ACT_PROP;
				return(true);
			}

		}else if  (		(firsttype == ACT_PROP)
				&&	(choice == propfirst)
			)
		{
			int acreq = ac;
			for (int i = 0; i < MAX_DIRGROUPS; i++)
				acreq +=  4*tmpgroup[i].numflights;
			if (acreq <= acresource[SQ_F80])
			{
				for (int i = 0; i < MAX_DIRGROUPS; i++)
					if (tmpgroup[i].numflights > 0)
						tmpgroup[i].squadron = SQ_F80;
	  			tmpgroup[grptype].squadron = SQ_F80;
				tmpgroup[grptype].numflights = ac/4;
				firsttype = ACT_JET;
				return(true);
			}else if (acreq <= acresource[SQ_F84])
			{
				for (int i = 0; i < MAX_DIRGROUPS; i++)
					if (tmpgroup[i].numflights > 0)
						tmpgroup[i].squadron = SQ_F84;
				tmpgroup[grptype].squadron = SQ_F84;
				tmpgroup[grptype].numflights = ac/4;

				firsttype = ACT_JET;
				return(true);
			}


		}


	}
	return (false);
}
void	DirControl::AllocateAlphaStrike(int d, int i)	
{
	char note;
//DEADCODE RDH 19/03/99 	int fightersrequired;
//DEADCODE RDH 19/03/99 			int  p = FIL_ALPHASTRIKE;
//DEADCODE RDH 19/03/99 			fightersrequired = 16;
//DEADCODE RDH 19/03/99 			if (fightersrequired < (acresource[SQ_F86A] + acresource[SQ_F86B]))
//DEADCODE RDH 19/03/99 			{
//DEADCODE RDH 19/03/99 			 	AllocateFighters(fightersrequired, d, i);
//DEADCODE RDH 19/03/99 			}else
//DEADCODE RDH 19/03/99 			{
//DEADCODE RDH 19/03/99 				directives[d].missions[i].escort = false;
//DEADCODE RDH 19/03/99 				note = SupplyTree::M_NOTOPCOVER;
//DEADCODE RDH 19/03/99 			}
			AllocateStrike(d, i, note, FIL_ALPHASTRIKE);
			directives[d].missions[i].note = note;

}
int	DirControl::StrikeTypeRequired(int d, int i)
{
	int type;

	if (directives[d].missions[i].profile ==  FIL_FBSTRIKE)
	{
		if  (	(		(directives[d].missions[i].score >= (3 * maxscore[d] / 4))
					||	(CloseToChina(5, directives[d].missions[i].node))
				)
					&&	(alphastrikesallowed)
				
			)
				type = ALPHASTRIKE;
		else if (		(directives[d].missions[i].score > (maxscore[d] / 2))
					||	(CloseToChina(10, directives[d].missions[i].node))
				)
			type = MEDIUMBOMBERSTRIKE;
		else
			type = FBSTRIKE;
	}else
			type = FBSTRIKE;
	return(type);

}
bool		DirControl::CloseToChina(int node_num, SupplyNode*  node)
{

  	SupplyNode* currnode;
	SupplyRoute*  currroute;

	currnode = node->supplyline->firstnode;
	int cnt = 0;
	while (		(currnode->forward != NULL)
			&&	(cnt < node_num)
			&&	(currnode != node)
		   )
	{
		cnt++;
		currroute = currnode->forward;
		currnode = currroute->suppliee;
	};
	if (cnt < node_num)
		return (true);
	else
		return (false);
}
void	DirControl::InitAc()
{
	
	acresource[SQ_F86A] = Todays_Packages.SquadACAvail(SQ_F86A);
	acresource[SQ_F86B] = Todays_Packages.SquadACAvail(SQ_F86B);
	acresource[SQ_F80] = Todays_Packages.SquadACAvail(SQ_F80);
	acresource[SQ_F84] = Todays_Packages.SquadACAvail(SQ_F84);
	acresource[SQ_F51] = Todays_Packages.SquadACAvail(SQ_F51);

	int bombers = 0;
	if  (		(acresource[SQ_F86A] >=4)
			||	(acresource[SQ_F86B] >=4)			
			||	(acresource[SQ_F80] >=4)			
			||	(acresource[SQ_F84] >=4)			
		)
  		bombers = MAXACPERSQUAD;

 	if (Miss_Man.camp.directives.B29avail)
	{
		acresource[SQ_B29] = bombers;
		acresource[SQ_B26] = 0;
	}else
	{
		acresource[SQ_B26] = bombers;
		acresource[SQ_B29] = 0;
	}


	TotalStrikeAc =  acresource[SQ_F80]	+ acresource[SQ_F84] + acresource[SQ_F51] + acresource[SQ_B29] + acresource[SQ_B26];
	TotalFighterAC = acresource[SQ_F86A] + acresource[SQ_F86B];
	TotalStrikeAc -= TotalStrikeAcInUse;
	if (TotalStrikeAc < 0)
		TotalStrikeAc = 0;
	TotalFighterAC -= TotalFighterACInUse;
	if (TotalFighterAC < 0)
		TotalFighterAC = 0;
	for (int j = SQ_F86A; j <= SQ_B29; j++)
	{
		acresource[j] -= acalreadyinuse[j];
	}


}


void	DirControl::FindScoresAndProfile(int pack, UniqueID uid, SupplyNode* node, int& score, int& maxscore, FileNum& profile, int& type)
{
	maxscore = 65536;		//just a large number, should need it
	score = 0;
	profile = FIL_FBSTRIKE;
	type = SupplyTree::D_CHOKE;
	
	switch	(Todays_Packages.pack[pack].duty)
	{
		case DUTYMIGCAP:
		case DUTYBARCAP:
		{
			maxscore = 0;
			profile = FIL_BARCAP;
			type = SupplyTree::D_AIRSUPERIORITY;
			break;
		}
		case DC_BOMB:
		case DC_AR:
		{
			SupplyTree::Supply2UID	relation;
			SupplyNode*	node=SupplyTree::FindSupplyNodeForItem(uid,&relation);
			if  (		(relation == SupplyTree::S2U_ROUTE0)
				||	(relation == SupplyTree::S2U_ROUTE1)
				||	(relation == SupplyTree::S2U_ROUTE2)
				)
			{//bridge or mobiles
				int route = relation - SupplyTree::S2U_ROUTE0;
				if (route < 0)
					route = 0;
				if (route > 2)
					route = 0;
				SupplyRoute* sr = node->route[route];
				sr = SupplyTree::FindBridge(uid, sr);
				if	(sr)
				{
					if	(		(sr->storespermobile == STORES_TRUCK)
							&&	(uid == sr->redsupplyUID)
						)
					{
						type = SupplyTree::D_ROAD;
						maxscore = MAJ_TRUCKSPERDAY*STORES_TRUCK;
					}else//bridges are always based on train throughput
					{
						type = SupplyTree::D_RAIL;
						maxscore = MAJ_TRAINSPERDAY*STORES_TRAIN;
					}
					if (uid == sr->redsupplyUID)
					{
						score = sr->storeslaunched;
						profile =  FIL_ARMEDRECONN;
					}else
					{
						score = sr->maxcapacitysummer;
						profile = FIL_FBSTRIKE;
						type = SupplyTree::D_CHOKE;
					}
				}
			}else if  (		(relation == SupplyTree::S2U_AF0)
					||	(relation == SupplyTree::S2U_AF1)
					||	(relation == SupplyTree::S2U_AF2)
				)
			{
				maxscore = 12;
				AirFieldInfo* af=SupplyTree::FindAirfieldForItem(uid);
				score = (1 + (int)(af->type)) *  af->capacity;
				profile = FIL_FBSTRIKE;
				type= SupplyTree::D_AIRFIELDS;
			}else
			{
				maxscore = STORES_MAXSUPPLY;
				score = node->currentstores;
				profile = FIL_FBSTRIKE;
				type = SupplyTree::D_SUPPLY;
			}
			break;
		}
		case DC_CAS:
		{
			maxscore = 200;
			profile =  FIL_CAS;
			score = 0;
			type = SupplyTree::D_ARMY;
			break;
		}

	}

	
}

void	DirControl::MakeMiniCampaignMission()
{
	if (MMC.missions[MMC.curr_msn].msn_time> AFTERNOONPERIODSTART)
		MMC.currtime = AFTERNOONPERIODSTART;
	else if (MMC.missions[MMC.curr_msn].msn_time > MIDDAYPERIODSTART)
		MMC.currtime = MIDDAYPERIODSTART;
	else
		MMC.currtime = MORNINGPERIODSTART;

	MMC.DisDayEntry(Debrief::NAME, MMC.missions[MMC.curr_msn].target, MMC.dis+MMC.curr_msn);
	if  (Miss_Man.currcampaignnum == MissMan::F86_CAMPAIGN)
	{	//cap
		int pack=Todays_Packages.FindPackage();
		if (pack>=0)
		{
			Todays_Packages[pack].packagetarget = MMC.missions[MMC.curr_msn].captarget;
				bool preloaded=
					Todays_Packages.PreLoad(pack,FIL_BARCAP,
									NULL,false,true);
				if (preloaded)
				{
					Todays_Packages[pack][0].targettime = 
							MMC.missions[MMC.curr_msn].msn_time;
					Todays_Packages[pack][1].targettime = 
							MMC.missions[MMC.curr_msn].msn_time + MIN10;
					Todays_Packages[pack].packagetarget=MMC.missions[MMC.curr_msn].captarget;
					Todays_Packages.Load(pack,FIL_BARCAP, NULL);
					AllocateAcToOneTarget(pack, MMC.missions[MMC.curr_msn].captarget, false);

				}
		}
		//bombers
		pack=Todays_Packages.FindPackage();
		if (pack>=0)
		{
			Todays_Packages[pack].packagetarget = MMC.missions[MMC.curr_msn].target;
				bool preloaded=
					Todays_Packages.PreLoad(pack,MMC.missions[MMC.curr_msn].profile,
									NULL,false,true);
				if (preloaded)
				{
					Todays_Packages[pack][0].targettime = 
							MMC.missions[MMC.curr_msn].msn_time;
					Todays_Packages[pack].packagetarget=MMC.missions[MMC.curr_msn].target;
					Todays_Packages.Load(pack,MMC.missions[MMC.curr_msn].profile, NULL);
					AllocateAcToOneTarget(pack, MMC.missions[MMC.curr_msn].target, true);

				}
		}

	}else
	{
		int pack=Todays_Packages.FindPackage();
		if (pack>=0)
		{
			Todays_Packages[pack].packagetarget = MMC.missions[MMC.curr_msn].target;
				bool preloaded=
					Todays_Packages.PreLoad(pack,MMC.missions[MMC.curr_msn].profile,
									NULL,false,true);
				if (preloaded)
				{

					Todays_Packages[pack][0].targettime = 
							MMC.missions[MMC.curr_msn].msn_time;
					Todays_Packages[pack].packagetarget=MMC.missions[MMC.curr_msn].target;
					Todays_Packages.Load(pack,MMC.missions[MMC.curr_msn].profile, NULL);
					AllocateAcToOneTarget(pack, MMC.missions[MMC.curr_msn].target, false);

				}
		}
	}
}
bool	DirControl::ModifyRedoIfNecessary(int currpack)
{
	bool redopossible = true;
	for (int k  = 0; k < ACTYPES; k++)
		acalreadyinuse[k] = 0;
	for (int pack=0;pack<currpack;pack++)
	{
		if  (		(Todays_Packages[pack].packagetarget != UID_NULL)
				&&	(		(Todays_Packages[pack].redo)
					)
			)
		{
			for (int wave=0;wave<Profile::MAX_WAVES;wave++)
			{
				for (int group=0;group<Profile::MAX_GROUPS;group++)
				{
					if (Todays_Packages[pack][wave][group].uid)
						acalreadyinuse[Todays_Packages[pack][wave][group].squadron] += 4*Todays_Packages[pack][wave][group].numflights;
				}
			}
		}
	}
	InitAc();

	for (int wave=0;wave<Profile::MAX_WAVES;wave++)
	{
		for (int group=0;group<Profile::MAX_GROUPS;group++)
		{
			if (		(Todays_Packages[pack][wave][group].uid)
					&&	 (redopossible)
			   )
			{
				int acreq = 4*Todays_Packages[pack][wave][group].numflights;
				int squad = Todays_Packages[pack][wave][group].squadron;
				if (	(Miss_Man.camp.directives.B29avail)	&&	(squad == SQ_B26))
				{
						squad = SQ_B29;
						Todays_Packages[pack][wave][group].SetSquad(squad);

				}
				if (	(!Miss_Man.camp.directives.B29avail)	&&	(squad == SQ_B29))
				{
						squad = SQ_B26;
						Todays_Packages[pack][wave][group].SetSquad(squad);
				}
				int acavail = acresource[squad];
				if (acreq > acavail)
				{
					if (acavail < 4)
					{
						if (group == 0)
						{
							if (wave)
								Todays_Packages[currpack].ClearWave(wave);
							else
								redopossible = false;
							break;
						}else
						{
							Todays_Packages[currpack].ClearGroup(wave,group);
						}

					}else
					{
						Todays_Packages[pack][wave][group].SetFlights(acavail/4);
						acresource[Todays_Packages[pack][wave][group].squadron] -= 
								Todays_Packages[pack][wave][group].numflights*4;
					}
				}else
						acresource[Todays_Packages[pack][wave][group].squadron] -= 
							Todays_Packages[pack][wave][group].numflights*4;
			}
		}
	}

	return(redopossible);

}
void	DirControl::AllocateAcToOneTarget(int pack, UniqueID uid, bool countall)
{

	InitDirectivesStruct();

	alphastrikesallowed = false;
	directives[0].fighterac = 32;
	directives[0].strikeac = 64;

	AircraftAlreadyUsed(pack, countall);

	InitAc();

	SupplyNode* node = SupplyTree::FindSupplyNodeForNodeItem(uid);
	int score, scoremax;
	FileNum profile;
	int type;
	FindScoresAndProfile(pack, uid, node, score, scoremax, profile, type);
	directives[0].missions[0].score = score;
	directives[0].missions[0].target = uid;
	directives[0].missions[0].node  = node;
	directives[0].missions[0].profile =  profile;
	directives[0].type =  type;


	maxscore[0] = scoremax;
	directives[0].targets = 1;
	char striketype;
	int r_mb, r_f80,r_f84,r_f51,r_fb,r_f, r_f86a, r_f86b, r_b26, r_b29;
	Todays_Packages.ProfileFlightsRequired(pack, r_mb, r_f80,r_f84,r_f51,r_fb,r_f, r_f86a, r_f86b, r_b26, r_b29);
	int total = r_mb + r_fb;
	if (total >= 12)
	{
		striketype = ALPHASTRIKE;
		alphastrikesallowed = true;
	}else if (		(Todays_Packages[pack][0][0].squadron == SQ_B26)
			||	(Todays_Packages[pack][0][0].squadron == SQ_B29)			
		)
		striketype = MEDIUMBOMBERSTRIKE;
	else
		striketype = FBSTRIKE;

	if (!AllocateTargets(0,striketype, true))
		AllocateTargets(0,striketype, false);
//	AllocateTargets(0,UNDECIDEDSTRIKE);
	UpdatePackageAircraft(pack, 0, 0);
}

void	DirControl::AllocateAc()
{
	InitDirectivesStruct();

	AircraftAlreadyUsed(-1, false);

	InitAc();

	for (char i = 0; i < (MAXDIRECTIVES - 1); i++)
	{
		FindTargets(i);
		if (directives[i].targets > MAXMISSIONS)
			directives[i].targets = MAXMISSIONS;
		directives[i].missionsset = 0;


		if  (	(directives[i].strikeac != 0)
			||	(directives[i].type == SupplyTree::D_AIRSUPERIORITY)
			)
		{

//DEADCODE RDH 12/06/99 			if (!AllocateTargets(i, UNDECIDEDSTRIKE, true))
//DEADCODE RDH 12/06/99 				//nomissions were set and so try unescorted			  //RDH 10/06/99
				AllocateTargets(i, UNDECIDEDSTRIKE, true);

		}else
		{
			directives[i].missions[0].note = SupplyTree::M_NOACALLOC;
		}

	}

}
int	DirControl::CalcAcUsedofType(int squad)
{
	int numofac = 0;
	for (int j = 0; j < MAX_DIRGROUPS ; j++)
		if (tmpgroup[j].squadron == squad)
			numofac += (4*tmpgroup[j].numflights);

	return (numofac);
}

bool DirControl::TargetAlreadyAlloc(UniqueID target)
{
	for (int pack=0;pack<Profile::MAX_PACKS;pack++)
		if (targetsalloc[pack] == target)
			return (true);
	return(false);
}

void	DirControl::AircraftAlreadyUsed(int excludedpack, bool countall)
{
	for (int k  = 0; k < ACTYPES; k++)
		acalreadyinuse[k] = 0;
	MissionsAlreadyDefined = 0;
	TargetsAlreadyDefined = 0;


	for (int pack=0;pack<Profile::MAX_PACKS;pack++)
	{
		if  (		(Todays_Packages[pack].packagetarget != UID_NULL)
				&&	(pack != excludedpack)
				&&	(		(Todays_Packages[pack].redo)
						||
							(countall)
					)
			)
		{
			MissionsAlreadyDefined++;
			TargetsAlreadyDefined++;
			if (pack != excludedpack)
				targetsalloc[pack] = Todays_Packages[pack].packagetarget;

			for (int wave=0;wave<Profile::MAX_WAVES;wave++)
			{
				for (int group=0;group<Profile::MAX_GROUPS;group++)			  //RDH 22/06/99
				{
					if (Todays_Packages[pack][wave][group].uid)		  //RDH 10/06/99
						acalreadyinuse[Todays_Packages[pack][wave][group].squadron] += 4*Todays_Packages[pack][wave][group].numflights;
				}
			}
		}
	}
	TotalStrikeAcInUse = acalreadyinuse[SQ_F80]	+ acalreadyinuse[SQ_F84] + acalreadyinuse[SQ_F51] + acalreadyinuse[SQ_B29] + acalreadyinuse[SQ_B26];
	TotalFighterACInUse = acalreadyinuse[SQ_F86A] + acalreadyinuse[SQ_F86B];


}
