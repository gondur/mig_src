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

// LoadProf.cpp : implementation file
//

#include "stdafx.h"
#include "mig.h"
#include "LoadProf.h"
#include "migview.h"
#include "savegame.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif
CString  CLoadProf::selectedfile;

/////////////////////////////////////////////////////////////////////////////
// CLoadProf dialog


CLoadProf::CLoadProf(int uid, CWnd* pParent /*=NULL*/)
	: RowanDialog(CLoadProf::IDD, pParent)
{
	trguid = uid;
	acnum=0;
	groupnum=FIL_STANDARD_PROFILES_DIR_LONG;
	//{{AFX_DATA_INIT(CLoadProf)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CLoadProf::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLoadProf)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

class	UserProfAttack:public LoadSaveDescriminate
{
public:	UniqueID	trguid;	UserProfAttack(UniqueID uid)	{trguid=uid;}
	int	AllowFile(FileNum dirname,char* filename)	const
	{
		int retval = 0;
		int pack=Todays_Packages.FindPackage();
		if (pack>=0)
		{
			int a_mb, a_f80,a_f84,a_f51,a_fb,a_f, a_f86a, a_f86b, a_b26, a_b29;
			Todays_Packages.FlightsAvailable(pack, a_mb, a_f80,a_f84,a_f51,a_fb,a_f, a_f86a, a_f86b, a_b26, a_b29);
			bool preloaded=
				Todays_Packages.PreLoad(pack,dirname,filename,true,true);
			if 	(Todays_Packages.UsedWaypoints()>Todays_Packages.MaxWaypoints())
				retval =0;
			else if 	(		(Todays_Packages.pack[pack].duty != DC_BOMB)
//DeadCode DAW 26Mar99 					&&	(Todays_Packages.pack[pack].duty != DUTYDIVEBOMB)
				)
					retval = 0;
			else
			{
				//check here if it is one we want, and set it's priority!
				int r_mb, r_f80,r_f84,r_f51,r_fb,r_f, r_f86a, r_f86b, r_b26, r_b29;
				Todays_Packages.ProfileFlightsRequired(pack, r_mb, r_f80,r_f84,r_f51,r_fb,r_f, r_f86a, r_f86b, r_b26, r_b29);
				if (r_mb > a_mb)
					retval = 0;
				else if (r_f80 > a_f80)
					retval = 0;
				else if (r_f84 > a_f84)
					retval = 0;
				else if (r_f51 > a_f51)
					retval = 0;
				else if (r_f > a_f)
					retval = 0;
				else if (trguid == Todays_Packages.pack[pack].packagetarget)
					retval = LoadSaveDescriminate::MAXPRIORITY;
				else 	if  ( 		(SupplyTree::WestRoute.frontline->forward->suppliee->associated_item == trguid)
								||	(SupplyTree::CentralRoute.frontline->forward->suppliee->associated_item == trguid)
								||	(SupplyTree::EastRoute.frontline->forward->suppliee->associated_item == trguid)
						)
				{
						if (Todays_Packages.pack[pack].duty == DC_CAS)
							retval = LoadSaveDescriminate::MAXPRIORITY-1;
						else
							retval = 0;
				}else
				{
					int uidband=Persons2::getbandfromUID(trguid);
					if	(		(uidband == RedRailBand)
							||	(uidband == RedRoadBAND)
						)

					{
						if (Todays_Packages.pack[pack].duty == DC_AR)
							retval = LoadSaveDescriminate::MAXPRIORITY -1;
						else
							retval = 0;
					}else
					{
						if (Todays_Packages.pack[pack].duty != DC_AR)
							retval = 1;
						else
							retval = 0;
					}
				}
			}
		}else
			retval =  0;
		Todays_Packages.ClearPack(pack);
		return (retval);
	}
};

class	UserProfPatrol:public LoadSaveDescriminate
{
public:	UniqueID	trguid;	UserProfPatrol(UniqueID uid)	{trguid=uid;}
	int	AllowFile(FileNum dirname,char* filename)	const
	{
		int retval = 0;
		int pack=Todays_Packages.FindPackage();
		if (pack>=0)
		{
			int a_mb, a_f80,a_f84,a_f51,a_fb,a_f, a_f86a, a_f86b, a_b26, a_b29;
			Todays_Packages.FlightsAvailable(pack, a_mb, a_f80,a_f84,a_f51,a_fb,a_f, a_f86a, a_f86b, a_b26, a_b29);
			bool preloaded=
				Todays_Packages.PreLoad(pack,dirname,filename,true,true);
			if 	(Todays_Packages.UsedWaypoints()>Todays_Packages.MaxWaypoints())
				retval =0;
			else if 	(		(Todays_Packages.pack[pack].duty == DC_BOMB)
//DEADCODE DAW 26/03/99 					||	(Todays_Packages.pack[pack].duty == DUTYDIVEBOMB)
				)
					retval =0;
			else
			{
				//check here if it is one we want, and set it's priority!
				int r_mb, r_f80,r_f84,r_f51,r_fb,r_f, r_f86a, r_f86b, r_b26, r_b29;
				Todays_Packages.ProfileFlightsRequired(pack, r_mb, r_f80,r_f84,r_f51,r_fb,r_f, r_f86a, r_f86b, r_b26, r_b29);
				if (r_mb > a_mb)
					retval = 0;
				else if (r_f80 > a_f80)
					retval = 0;
				else if (r_f84 > a_f84)
					retval = 0;
				else if (r_f51 > a_f51)
					retval = 0;
				else if (r_f > a_f)
					retval = 0;
				else if (trguid == Todays_Packages.pack[pack].packagetarget)
					retval = LoadSaveDescriminate::MAXPRIORITY;
				else if  ( 		(SupplyTree::WestRoute.frontline->forward->suppliee->associated_item == trguid)
								||	(SupplyTree::CentralRoute.frontline->forward->suppliee->associated_item == trguid)
								||	(SupplyTree::EastRoute.frontline->forward->suppliee->associated_item == trguid)
						)
					{
						if (Todays_Packages.pack[pack].duty == DC_CAS)
							 retval = LoadSaveDescriminate::MAXPRIORITY-1;
						else
							retval = 0;
				}else
				{
					int uidband=Persons2::getbandfromUID(trguid);
					if	(		(uidband == RedRailBand)
							||	(uidband == RedRoadBAND)
						)

					{
						if (Todays_Packages.pack[pack].duty == DC_AR)
							retval = LoadSaveDescriminate::MAXPRIORITY -1;
						else
							retval = 0;
					}else
					{
						if (Todays_Packages.pack[pack].duty != DC_AR)
							retval = 1;
						else
							retval = 0;
					}
				}
			}
		}else
			retval = 0;
		Todays_Packages.ClearPack(pack);
		return (retval);
	}
};

class	StdProf:public LoadSaveDescriminate
{
public:	UniqueID	trguid;	StdProf(UniqueID uid)	{trguid=uid;}
	int	AllowFile(FileNum dirname,char* filename)  const
	{	//ignore the system loaded standard profiles that have short names
		//perhaps we can guarantee 8 letters by putting "_" in, so filename[8]=='.'
		//or strlen(filename)<14
		int retval = 0;
		int pack=Todays_Packages.FindPackage();
		if (pack>=0)
		{
			int a_mb, a_f80,a_f84,a_f51,a_fb,a_f, a_f86a, a_f86b, a_b26, a_b29;
			Todays_Packages.FlightsAvailable(pack, a_mb, a_f80,a_f84,a_f51,a_fb,a_f, a_f86a, a_f86b, a_b26, a_b29);
			bool preloaded=
				Todays_Packages.PreLoad(pack,dirname,filename,true,true);
			//check here if it is one we want, and set it's priority!
			int r_mb, r_f80,r_f84,r_f51,r_fb,r_f, r_f86a, r_f86b, r_b26, r_b29;
			Todays_Packages.ProfileFlightsRequired(pack, r_mb, r_f80,r_f84,r_f51,r_fb,r_f, r_f86a, r_f86b, r_b26, r_b29);


			if  ( 		(SupplyTree::WestRoute.frontline->forward->suppliee->associated_item == trguid)
							||	(SupplyTree::CentralRoute.frontline->forward->suppliee->associated_item == trguid)
							||	(SupplyTree::EastRoute.frontline->forward->suppliee->associated_item == trguid)
					)
			{//front lines only allowed to have CAS, CAS only on frontline
				if (Todays_Packages.pack[pack].duty == DC_CAS)
					 retval = LoadSaveDescriminate::MAXPRIORITY-1;
				else
					retval = 0;
			}else if (Todays_Packages.pack[pack].duty == DC_CAS)	  //RDH 24/06/99
				retval = 0;
			else
			{//Armed reconn only on routes and vice versa
				int uidband=Persons2::getbandfromUID(trguid);
				if	(		(uidband == RedRailBand)
						||	(uidband == RedRoadBAND)
					)

				{
					if (Todays_Packages.pack[pack].duty == DC_AR)
						retval = LoadSaveDescriminate::MAXPRIORITY -1;
					else
						retval = 0;
				}else
				{
					if (Todays_Packages.pack[pack].duty != DC_AR)
						retval = 1;
					else
						retval = 0;
				}
			}
			if (retval)
			{//do we have the aircraft

				if (r_mb > a_mb)
					retval = 0;
				else if	(		(r_fb == 1)	
							&&	(r_fb > a_fb)
						 )//min strike
					retval = 0;
				else if	(		(r_fb > (a_f80+a_f84))			//f51 no good for alpha strike etc
							&&	(Todays_Packages.pack[pack].duty != DC_AR)
							&&	(Todays_Packages.pack[pack].duty != DC_CAS)
							&&	(r_fb > 1)		//let minimumstrike through //RDH 25/06/99
						)
						retval = 0;
				else if (		(r_fb > (a_fb))							  //RDH 24/06/99
							&&	(		(Todays_Packages.pack[pack].duty == DC_AR)
									||	(Todays_Packages.pack[pack].duty == DC_CAS)					
								)
						)
					retval = 0;
				else if (r_f > a_f)
					retval = 0;
			}
		}else
			retval = 0;
		Todays_Packages.ClearPack(pack);
		return (retval);
	}
};


BEGIN_MESSAGE_MAP(CLoadProf, CDialog)
	//{{AFX_MSG_MAP(CLoadProf)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

RDialog* CLoadProf::MakeSheet(int uid)
{
	typedef	HideEdgeControl	EDGE; 
	CString	wildcard="*.prf";
	selectedfile= Save_Data.lastpackname;
	RDialog* rv=
		MakeTopDialog(::Place(POSN_CENTRE,POSN_CENTRE),
								DialList(DialBox(FIL_NULL/*IDB_BBC3*/,new CLoadProf(uid),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE)), //rdh
									HTabBox(FIL_NULL,IdList(IDS_STANDARD,IDS_USERSTRIKE,IDS_USERCAP),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX), 
			  						DialBox(FIL_MAP_PLAYER_LOG/*IDB_BBC3*/,new CLoad(IDD_LOAD,LSD_LOAD_DESELECT	,FIL_STANDARD_PROFILES_DIR_LONG,	wildcard,CLoadProf::selectedfile,StdProf((UniqueID)uid))),
			  						DialBox(FIL_MAP_PLAYER_LOG/*IDB_BBC3*/,new CLoad(IDD_LOAD,LSD_LOAD_DESELECT	,FIL_USER_PROFILES_DIR,		wildcard,CLoadProf::selectedfile,UserProfAttack((UniqueID)uid))),
			  						DialBox(FIL_MAP_PLAYER_LOG/*IDB_BBC3*/,new CLoad(IDD_LOAD,LSD_LOAD_DESELECT ,FIL_USER_PROFILES_DIR,		wildcard,CLoadProf::selectedfile,UserProfPatrol((UniqueID)uid)))
									)	)	);
	CRTabs* tab=(CRTabs*)rv->fchild->GetDlgItem(IDJ_TABCTRL);
	RDialog* tabs=rv->fchild->fchild;	 //OnSelecttab
	int tabnum=2;
	if (((RowanDialog*)rv)->acnum==0)
		tabnum=0;
	else
	for (;tabnum>0;tabnum--,tabs=tabs->sibling)						  //JIM 15/04/99
		if (tabs==(RDialog*)(((RowanDialog*)rv)->acnum))
			break;
	tab->SelectTab(tabnum);
	return rv;
}


/////////////////////////////////////////////////////////////////////////////
// CLoadProf message handlers

BEGIN_EVENTSINK_MAP(CLoadProf, CDialog)
    //{{AFX_EVENTSINK_MAP(CLoadProf)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()


void CLoadProf::SwopFighterIfNecessary(int packnum, int wave, int group, int& Org_left, int& Opt_left, int Opt_Squad)
{
	Org_left -= Todays_Packages.pack[packnum].wave[wave].group[group].numflights;
	if (Org_left < 0)
	{
		Org_left += Todays_Packages.pack[packnum].wave[wave].group[group].numflights;
		Opt_left -= Todays_Packages.pack[packnum].wave[wave].group[group].numflights;
		if (Opt_left < 0)
		{
			Opt_left += Todays_Packages.pack[packnum].wave[wave].group[group].numflights;
			if (Opt_left <= 0)
			{
				if (Org_left <= 0)
					assert(false&&"nomore ac")
				else
				{
					Todays_Packages.pack[packnum].wave[wave].group[group].SetFlights(Org_left);
					Org_left = 0;
				}
			}
			else
			{
				Todays_Packages.pack[packnum].wave[wave].group[group].SetFlights(Opt_left);
				Todays_Packages.pack[packnum].wave[wave].group[group].SetSquad(Opt_Squad);
				Opt_left = 0;
			}
		}
		else
		{
			Todays_Packages.pack[packnum].wave[wave].group[group].SetSquad(Opt_Squad);
		}
	}

}
void CLoadProf::EnsureAvailMedBmbAndFighterUsed(int packnum, int f86a_left, int f86b_left)
{
//swop bombers if necessary
	int mbindex = SQ_B26;
	int offdutyindex = SQ_B29;
	if (MMC.directives.B29avail)
	{
		mbindex = SQ_B29;
		offdutyindex = SQ_B26;
	}
	int wave;
	int group;
	for (wave=0;wave<Profile::MAX_WAVES;wave++)
		for (group=0;group<Profile::MAX_GROUPS;group++)
		{
			if (Todays_Packages.pack[packnum].wave[wave].group[group].squadron == offdutyindex)
				Todays_Packages.pack[packnum].wave[wave].group[group].SetSquad(mbindex);
		}
//use up fighters
	for (wave=0;wave<Profile::MAX_WAVES;wave++)
		for (group=0;group<Profile::MAX_GROUPS;group++)
		{
			if (		(Todays_Packages.pack[packnum].wave[wave].group[group].squadron == SQ_F86A)
					&&	(Todays_Packages.pack[packnum].wave[wave].group[group].numflights > 0)
				)
				SwopFighterIfNecessary(packnum, wave, group, f86a_left, f86b_left, SQ_F86B);
			if (		(Todays_Packages.pack[packnum].wave[wave].group[group].squadron == SQ_F86B)
					&&	(Todays_Packages.pack[packnum].wave[wave].group[group].numflights > 0)
				)

				SwopFighterIfNecessary(packnum, wave, group, f86b_left, f86a_left, SQ_F86A);
		}
		
}	


void CLoadProf::OnOK() 
{
	//the type of profile chosen will determine the duty
	if (selectedfile!=".prf" && selectedfile!="")
	{
		const char* dirnametext=
			Save_Data.lastpackname=selectedfile;
		int pack=Todays_Packages.FindPackage();
		if (pack>=0)
		{
			int a_mb, a_f80,a_f84,a_f51,a_fb,a_f, a_f86a, a_f86b, a_b26, a_b29;
			Todays_Packages.FlightsAvailable(pack, a_mb, a_f80,a_f84,a_f51,a_fb,a_f, a_f86a, a_f86b, a_b26, a_b29);
			Todays_Packages[pack].packagetarget=UniqueID(trguid);
			bool preloaded=
				Todays_Packages.PreLoad(pack,FileNum(groupnum),selectedfile,false,true);
			if (preloaded)
			{

				Todays_Packages[pack].packagetarget=UniqueID(trguid);
				Todays_Packages.Load(pack,FileNum(groupnum),selectedfile);
				

				if (groupnum==FIL_STANDARD_PROFILES_DIR_LONG)
				{
					DirControl	dir_ctrl;
					dir_ctrl.AllocateAcToOneTarget(pack, UniqueID(trguid), true);
				}
				else
					EnsureAvailMedBmbAndFighterUsed(pack, a_f86a, a_f86b);
				SquadSelect bad=SQ_R_FLYABLE;
				for (int i=SQ_B_FLYABLE;i<SQ_B_NONFLYSPOT;i++)
					if (Todays_Packages.SquadACUsed(SquadSelect(i))>Todays_Packages.SquadACAvail(SquadSelect(i)))
						if (bad==SQ_R_FLYABLE)
							bad=SquadSelect(i);
						else
							bad=SQ_R_NONFLYABLE;
				if (bad!=SQ_R_FLYABLE)
					if (bad==SQ_R_NONFLYABLE)
						MessageBox("A number of aircraft type limits were exceeded.\nViewing or flying this setup may be fatal.\nPlease delete the package now!","Fault making package.",MB_OK);
					else
						MessageBox("The available aircraft of the above type was exceeded.\nFlying this scenario or viewing packages containing this type may be fatal.\nPlease delete the package","Fault making package for "+LoadResString(IDS_L_SQ_BF_F86A+bad),MB_OK);


				m_pView->ZoomToUID(UniqueID(trguid),m_pView->m_zoom);
				m_pView->m_mapdlg.ResetIcon(UniqueID(trguid));
				MainToolBar().CloseLoggedChildren(this);
				CMissionFolder::Make();
				Todays_Packages.hiwp = UID_NULL;					  //RDH 17/06/99
				CMissionFolder::OpenOneProfile(pack);
			}
//			else
//			if (groupnum==FIL_STANDARD_PROFILES_DIR)
//			{
//				int	pack=Todays_Packages.NewPackage(UniqueID(trguid), DC_BOMB);
//				if (pack>=0)
//				{
//					DirControl	dir_ctrl;
//					dir_ctrl.AllocateAcToOneTarget(pack, UniqueID(trguid));
//		
//					m_pView->ZoomToUID(UniqueID(trguid),m_pView->m_zoom);
//					m_pView->m_mapdlg.ResetIcon(UniqueID(trguid));
//					MainToolBar().CloseLoggedChildren(this);
//					CMissionFolder::Make();
//					CMissionFolder::OpenOneProfile(pack);
//				}
//			}
		}
	}
	else
	{
#ifndef NDEBUG
		int	pack=Todays_Packages.NewPackage(UniqueID(trguid), DC_BOMB);
		if (pack>=0)
		{
//DeadCode CSB 31/03/99	//			DirControl	dir_ctrl;
//DeadCode CSB 31/03/99	//			dir_ctrl.AllocateAcToOneTarget(pack, UniqueID(trguid));

			m_pView->ZoomToUID(UniqueID(trguid),m_pView->m_zoom);
			m_pView->m_mapdlg.ResetIcon(UniqueID(trguid));
			MainToolBar().CloseLoggedChildren(this);
			CMissionFolder::Make();
			CMissionFolder::OpenOneProfile(pack);
		}
#endif
	}
	CDialog::OnOK();
}

void CLoadProf::OnCancel() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}
