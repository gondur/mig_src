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

// Damage.cpp : implementation file
//

#include "stdafx.h"
#include "mig.h"
#include "Damage.h"
#include "savegame.h"
#include "animdata.h"
#include	"worldinc.h"
#include	"bfnumber.h"
#include "persons2.h"

#include	"bstream.h"
#include	"savegame.h"
#include	"groupitt.h"
#include	"shpinstr.h"										//RJS 15Feb99
#include	"3dcom.h"											//RJS 15Feb99
#include	"shapes.h"
#include	"replay.h"
#include "rchatter.h"
#include "globrefs.h"
#include "ai.h"

//hole... no item   void		MaxKillTime(ITEM_STATUS&);	//highest value for howlongdead.



#ifdef _DEBUG
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif


/////////////////////////////////////////////////////////////////////////////
// CDamage dialog


CDamage::CDamage(int sgt,int uid,CWnd* pParent /*=NULL*/)
	: RowanDialog(CDamage::IDD, pParent)
{
	//{{AFX_DATA_INIT
//	info_base* i=*Persons2::ConvertPtrUID(UniqueID(uid));
//	if (i->SGT)
//	{
		specificelt=UniqueID(uid);
//		uid=i->SGT;
//	}
	//}}AFX_DATA_INIT
	SetProjSpecific(-1,sgt,uid);
	damagedelements=new DamageDef[100];
	numdamagedelts=Dead_Stream.DecodeDamage(UniqueID(sgt),damagedelements);
}

CDamage::~CDamage()
{
	delete [] damagedelements;
}


void CDamage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDamage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX,IDC_LIST_ELEMENTS,m_IDC_LIST_ELEMENTS);
	DDX_Control(pDX,IDC_COMBO_ELEMENTS,m_IDC_COMBO_ELEMENTS);
	//}}AFX_DATA_MAP
	CRCombo* s=GETDLGITEM(IDC_COMBO_ELEMENTS);
	s->AddString(GetTargName(UniqueID(wavenum))+": "+RESSTRING(SPC_ALLELTS));
	if (numdamagedelts==0)
		s->AddString(GetTargName(UniqueID(wavenum))+": "+RESSTRING(SPC_NODAMAGEDELTS));
	else
		s->AddString(GetTargName(UniqueID(wavenum))+": "+RESSTRING(SPC_DAMAGEDELTS));
	for (int i=0;i<numdamagedelts;i++)
	{
		if (damagedelements[i].loadedid)
		{
			ItemPtr p=*Persons2::ConvertPtrUID(damagedelements[i].loadedid);
			if (p->SGT)
				s->AddString(GetShapeName(p->shape)+GetRelativeName(p->SGT,&p->World));
			else
				s->AddString(GetTargName(UniqueID(wavenum)));
		}
		else
			s->AddString(GetShapeName(damagedelements[i].shape));
	}
	if (specificelt)
	{
		for (int i=numdamagedelts-1;i>=0;i--)
			breakif (damagedelements[i].loadedid==specificelt)
		if (i>=0)
		{
			specificeltdamage=i;
			specificeltshape=damagedelements[i].shape;
			mode=M_SPECIFIC;
			s->SetIndex(2+i);
		}
		else
		{
			s->SetIndex(0);
			mode=M_ALL;
		}
	}
	else
	{
		s->SetIndex(1);
		mode=M_DAMAGED;
	}
	FillList();

}





void	CDamage::FillList()
{
	int setindex=-1;
	int listlen=0;
	CRListBox*	l=GETDLGITEM(IDC_LIST_ELEMENTS);
	l->Clear();
	switch (mode)
	{
	case M_SPECIFIC:
		{	//step through each element of group...
			UniqueID startpoint=UID_NULL;
			UniqueID findpoint=(UniqueID)wavenum;
			if (wavenum!=groupnum)
			{
				if (!DeadStream::MainWorldBand(UniqueID(groupnum)))
					startpoint=findpoint;
				findpoint=damagedelements[specificeltdamage].memberid;
			}
			DeadStream::DeadBlockItterator itt(Dead_Stream.firstblock,startpoint);
			itt.SkipToItem(findpoint);
			l->AddColumn(TARGETFIELDWIDTH);
			l->AddColumn(45);
			l->AddColumn(50);
			l->AddString("",0);
			l->AddString("",1);
			l->AddString(RESSTRING(LEVEL),2);

			for (GroupItterator si(damagedelements[specificeltdamage].shape,&itt);si;si++)
			{
				l->AddString(GetShapeName(si.shape),0);
				l->AddString(GetEltDeltaName(si.delta),1);		//minanimdata
				l->AddString(RESLIST(DAMAGESTAT_ALIVE,((MinAnimData&)si.AnimDataByte()).itemstate),2);
			}
		}
	break;
	case M_ALL:
		{	//step through all items in world that are a member of the SGT
			//hilight the specificelt
			l->AddColumn(TARGETFIELDWIDTH);
			l->AddColumn(45);
			l->AddColumn(50);
			l->AddString("",0);
			l->AddString(RESSTRING(LEVEL),1);
			l->AddString(RESSTRING(ELEMENTS),2);
			{														  //RDH 28/04/99
				info_itemS* p = *Persons2::SlowConvertPtrUID(UniqueID(wavenum));
				CString  str = GetShapeName(ShapeNum(p->shape.Evaluate()));
				if (str.IsEmpty() || str[0]=='_')
					str=GetTargName(UniqueID(wavenum));
				l->AddString(str,0);
			}
//DEADCODE RDH 28/04/99 			l->AddString(GetTargName(UniqueID(wavenum)),0);
			if (damagedelements[0].loadedid==wavenum)
			{
				DeadStream::DeadBlockItterator itt(Dead_Stream.firstblock,UID_NULL);
				itt.SkipToItem(UniqueID(wavenum));

				int damagedeltc=0,totaleltc=0,damagedpoints=0;
				for (GroupItterator si(damagedelements[0].shape,&itt);si;si++)
					if (si.AnimDataMAD().itemstate>0)
					{
						damagedeltc++;
						totaleltc++;
						damagedpoints+=si.AnimDataMAD().itemstate*si.DamageWeight();
					}
					else
						totaleltc++;
				if (damagedpoints<750)
					l->AddString(CSprintf("%i%%",damagedpoints/8),1);
				else
					if (damagedpoints<1500)
						l->AddString(RESSTRING(DAMAGESTAT_DEAD),1);
					else
						l->AddString(RESSTRING(DAMAGESTAT_DEAD),1);
				l->AddString(CSprintf("%i/%i",damagedeltc,totaleltc),2);
			}
			else
			{
				l->AddString(RESSTRING(FULLY_F),1);
				l->AddString(RESSTRING(F_FUNCTIONAL),2);
			}
			if (specificelt==wavenum)
				setindex=listlen;
			listlen++;
			info_itemS*	p;
			for (int i=0;i<WorldStuff::PITEMTABLESIZE;i++)
				if ((p=*Persons2::ConvertPtrUID(UniqueID(i)))!=NULL)
					if (p->SGT==wavenum && p->shape.Evaluate()!=EMPTY)
					{
						l->AddString(GetShapeName(ShapeNum(p->shape.Evaluate()))+" "+GetRelativeName(p->SGT,&p->World),0);
						int de=numdamagedelts;
						while(de-->0)
							breakif (damagedelements[de].loadedid==i);
						if (de>=0)
						{
							UniqueID startpoint=UID_NULL;
							UniqueID findpoint=(UniqueID)wavenum;
//DEADCODE JIM 07/06/99 							if (wavenum!=groupnum)
							{
								if (!DeadStream::MainWorldBand(UniqueID(i)))
									startpoint=findpoint;
								findpoint=damagedelements[de].memberid;
							}
							DeadStream::DeadBlockItterator itt(Dead_Stream.firstblock,startpoint);
							itt.SkipToItem(findpoint);

							int damagedeltc=0,totaleltc=0,damagedpoints=0;
							for (GroupItterator si(damagedelements[de].shape,&itt);si;si++)
								if (si.AnimDataMAD().itemstate>0)
								{
									damagedeltc++;
									totaleltc++;
									damagedpoints+=si.AnimDataMAD().itemstate*si.DamageWeight();
								}
								else
									totaleltc++;
							if (damagedpoints<750)
								l->AddString(CSprintf("%i%%",damagedpoints/8),1);
							else
								if (damagedpoints<1500)
									l->AddString(RESSTRING(DAMAGESTAT_DEAD),1);
								else
									l->AddString(RESSTRING(DAMAGESTAT_DEAD),1);
							l->AddString(CSprintf("%i/%i",damagedeltc,totaleltc),2);
						}
						else
						{
							l->AddString(RESSTRING(FULLY_F),1);
							l->AddString(RESSTRING(F_FUNCTIONAL),2);
						}
						if (specificelt==i)
							setindex=listlen;
						listlen++;
					}
		}
	break;
	case M_DAMAGED:
		if (numdamagedelts)
		{
			l->AddColumn(TARGETFIELDWIDTH);
			l->AddColumn(45);
			l->AddColumn(50);
			l->AddString("",0);
			l->AddString(RESSTRING(LEVEL),1);
			l->AddString(RESSTRING(ELEMENTS),2);
			int de=0;
			if (damagedelements[0].loadedid==wavenum)
			{
				info_itemS* p = *Persons2::SlowConvertPtrUID(UniqueID(wavenum));
				CString  str = GetShapeName(ShapeNum(p->shape.Evaluate()));
				if (str.IsEmpty() || str[0]=='_')
					str=GetTargName(UniqueID(wavenum));
				l->AddString(str,0);
//DEADCODE RDH 28/04/99 				l->AddString(GetTargName(UniqueID(wavenum)),0);

				DeadStream::DeadBlockItterator itt(Dead_Stream.firstblock,UID_NULL);
				itt.SkipToItem(UniqueID(wavenum));

				int damagedeltc=0,totaleltc=0,damagedpoints=0;
				for (GroupItterator si(damagedelements[0].shape,&itt);si;si++)
					if (si.AnimDataMAD().itemstate>0)
					{
						damagedeltc++;
						totaleltc++;
						damagedpoints+=si.AnimDataMAD().itemstate*si.DamageWeight();
					}
					else
						totaleltc++;
				if (damagedpoints<750)
					l->AddString(CSprintf("%i%%",damagedpoints/8),1);
				else
					if (damagedpoints<1500)
						l->AddString(RESSTRING(DAMAGESTAT_DEAD),1);
					else
						l->AddString(RESSTRING(DAMAGESTAT_DEAD),1);
				l->AddString(CSprintf("%i/%i",damagedeltc,totaleltc),2);
				de++;
				if (specificelt==wavenum)
					setindex=listlen;
				listlen++;
			}

			for (;de<numdamagedelts;de++)
			{
				if (damagedelements[de].loadedid)
				{
					ItemPtr p=*Persons2::ConvertPtrUID(damagedelements[de].loadedid);
					l->AddString(GetShapeName(p->shape)+" "+GetRelativeName(p->SGT,&p->World),0);
				}
				else
					l->AddString(GetShapeName(damagedelements[de].shape),0);

				UniqueID startpoint=UID_NULL;
				UniqueID findpoint=(UniqueID)wavenum;
				if (wavenum!=groupnum)
				{
					if (!DeadStream::MainWorldBand(damagedelements[de].memberid))
						startpoint=findpoint;
					findpoint=damagedelements[de].memberid;
				}
				DeadStream::DeadBlockItterator itt(Dead_Stream.firstblock,startpoint);
				itt.SkipToItem(findpoint);

				int damagedeltc=0,totaleltc=0,damagedpoints=0;
				for (GroupItterator si(damagedelements[de].shape,&itt);si;si++)
					if (si.AnimDataMAD().itemstate>0)
					{
						damagedeltc++;
						totaleltc++;
						damagedpoints+=si.AnimDataMAD().itemstate*si.DamageWeight();
					}
					else
						totaleltc++;
				if (damagedpoints<750)
					l->AddString(CSprintf("%i%%",damagedpoints/8),1);
				else
					if (damagedpoints<1500)
						l->AddString(RESSTRING(DAMAGESTAT_DEAD),1);
					else
						l->AddString(RESSTRING(DAMAGESTAT_DEAD),1);
				l->AddString(CSprintf("%i/%i",damagedeltc,totaleltc),2);
			//	de++;
				if (specificelt==damagedelements[de].loadedid)
					setindex=listlen;
				listlen++;
			}
		}
		else
		{
			l->AddColumn(TARGETFIELDWIDTH+100);
			l->AddString(RESSTRING(SPC_NODAMAGEDELTS),0);
		}
	break;
	}
	l->SetHilightRow(setindex+1);
}


BEGIN_MESSAGE_MAP(CDamage, CDialog)
	//{{AFX_MSG_MAP(CDamage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_EVENTSINK_MAP(CDamage, CDialog)
    //{{AFX_EVENTSINK_MAP(CDamage)
	ON_EVENT(CDamage, IDC_COMBO_ELEMENTS, 1 /* TextChanged */, OnTextChangedComboElements, VTS_BSTR)
	ON_EVENT(CDamage, IDC_LIST_ELEMENTS, 1 /* Select */, OnSelectListElements, VTS_I4 VTS_I4)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CDamage::OnTextChangedComboElements(LPCTSTR text) 
{
	// TODO: Add your control notification handler code here
  	CRCombo* combo;
	combo=GETDLGITEM(IDC_COMBO_ELEMENTS);
	int comboindex = combo->GetIndex();	
	if (comboindex==0)
		mode=M_ALL;
	else
	if (comboindex==1)
		mode=M_DAMAGED;
	else
	{
		groupnum=specificelt=damagedelements[specificeltdamage=(comboindex-2)].loadedid;
		mode=M_SPECIFIC;
	}
	FillList();
}

void CDamage::OnSelectListElements(long row, long column) 
{
	// TODO: Add your control notification handler code here

//	m_pView->m_mapdlg.ResetIcon(damagedelements[row-1].loadedid);
	row--;
	UniqueID rv=UID_NULL;
	if (mode==M_ALL)
	{
		if (row==0)
			rv=UniqueID(wavenum);
		else
		{
			info_itemS*	p;
			for (int i=0;i<WorldStuff::PITEMTABLESIZE;i++)
				if ((p=*Persons2::ConvertPtrUID(UniqueID(i)))!=NULL)
					if (p->SGT==wavenum && p->shape.Evaluate()!=EMPTY) //DAW 07/06/99
						if (!--row)
							rv=UniqueID(i);
		}
	}
	else
	if (mode==M_DAMAGED)
	{
		if (numdamagedelts)
			rv=damagedelements[row].loadedid;
	}
	if (rv)
		m_pView->m_mapdlg.ResetIcon(rv);
}

/////////////////////////////////////////////////////
////
////
//// OTHER damage related stuff.
////
////
/////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//
// Function:    EnoughDamage3D
// Date:		08/06/99
// Author:		DAW
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
bool	FormationItem::EnoughDamage3D(ItemPtr currtarget)
{
	if ((duty&DUTYMASK)==DC_WW)
		return (currtarget->Status.deadtime!=0);
	else
	if (!currtarget)
		return	true;
	else
	if (currtarget->Status.size>=FORMATIONSIZE)
	{
		FormationItemPtr curr=*currtarget;
		if (curr->Status.deadtime && !curr->leader)
			return true;											  //JIM 01/09/99
		else
			return false;											  //JIM 01/09/99
	}
	else
	{
		UniqueID SGT=currtarget->SGT;
		if (SGT==UID_NULL)
			SGT=currtarget->uniqueID.count;
		ItemPtr	test=*Persons2::ConvertPtrUID(SGT);
		int	lowestdamage=900;
		int	scan=-1;
		int	totaltokens=0,deadtokens=0;
		int	totalpoints=0,deadpoints=0;
		if (!test)
			return	false;
		else
		{
			do{
				totalpoints+=500;									  //MS 06/05/99
				for (GroupItterator gi(test->shape,test->Anim);gi;gi++)
				{
					if (gi.AnimDataMAD().itemstate)
					{
						deadpoints+=gi.DamageWeight()*gi.AnimDataMAD().itemstate;
						if (gi.IsStoresToken())
							deadtokens++;
					}
					if (gi.IsStoresToken())
						totaltokens++;
				}
				while (++scan<IllegalSepID)
				{
					if (scan<WayPointBAND || scan>=WayPointBANDEND) 
						if ((test=*Persons2::ConvertPtrUID(UniqueID(scan)))!=NULL)
							if (test->SGT==SGT && test->shape!=EMPTY)
								if (Persons2::getbandfromUID(UniqueID(scan))!=RedAAASiteBAND)
									break;
				}
			}while (scan<IllegalSepID);
			if (totaltokens)
				if (totaltokens*2<deadtokens*3)
					return true;
				else
					return false;
			else
				if (totalpoints<deadpoints)
					return true;
				else
					return false;

		}


	}
}
////////////////////////////////////////////////////////////////////////
//
// Function:    SelectTarget
// Date:        04/03/99
// Author:      JIM
//
// Description: 
//
////////////////////////////////////////////////////////////////////////
ItemPtr	FormationItem::SelectTarget(ItemPtr currtarget,int* selectedelt,int counter/*=0*/)
{
	ItemPtr rv=NULL;
	if (currtarget)
		if (currtarget->Status.size>=FORMATIONSIZE)
		{
			FormationItemPtr curr=*currtarget;
			while (curr->leader)
				curr=curr->Leader();
			rv=curr;
			if (rv && selectedelt)
				*selectedelt=counter;
		}
		else
		{
			//count up damage
			//count up live tokens
			//if (damage-100*livetokens>700)
			//		pick another target
//DEADCODE DAW 01/07/99 			Bool	bombableSGT=CheckForWeapon(LT_BOMB);			  //DAW 01/07/99
			UniqueID SGT=currtarget->SGT;
			if (SGT==UID_NULL)
				SGT=currtarget->uniqueID.count;
			
//DeadCode DAW 01Jul99 			if (!bombableSGT && Persons2::getbandfromUID(SGT)!=AmberAirfieldBAND && Persons2::getbandfromUID(SGT)!=AmberBridgeBAND)
//DeadCode DAW 01Jul99 				bombableSGT=TRUE;

			int damage=0,livetokens=0;
//DeadCode DAW 01Jul99 			if (!bombableSGT && !currtarget->SGT)
//DeadCode DAW 01Jul99 				damage=800;
//DeadCode DAW 01Jul99 			else
			if (currtarget->shape==EMPTY)
				damage=1000;
			else
				for (GroupItterator gi(currtarget->shape,currtarget->Anim);gi;gi++)
					if (gi.AnimDataMAD().itemstate)
						damage+=gi.DamageWeight()*gi.AnimDataMAD().itemstate;
					else
						if (gi.IsStoresToken())
							livetokens++;
			if ((duty&DUTYMASK)==DC_WW)
			{
				if (selectedelt)
					*selectedelt=SelectElement(rv,counter);
				rv=currtarget;
			}
			else
			if (damage-livetokens*100<700)
				rv=currtarget;
			else
			{
//DeadCode DAW 27Jun99 				UniqueID SGT=currtarget->SGT;
//DeadCode DAW 27Jun99 				if (SGT==UID_NULL)
//DeadCode DAW 27Jun99 					SGT=currtarget->uniqueID.count;
				ItemPtr	test=*Persons2::ConvertPtrUID(SGT);
				int	lowestdamage=900;
				int	scan=-1;
				if (test)
					do{
						damage=0;livetokens=0;
//DeadCode DAW 01Jul99 						if (!bombableSGT)
//DeadCode DAW 01Jul99 							damage=1000;
//DeadCode DAW 01Jul99 						else

						if (test->shape==EMPTY)						  //JIM 01/09/99
							damage=1000;
						else
							for (GroupItterator gi(test->shape,test->Anim);gi;gi++)
							{
								if (gi.AnimDataMAD().itemstate)
									damage+=gi.DamageWeight()*gi.AnimDataMAD().itemstate;
								else
									if (gi.IsStoresToken())
										livetokens++;
							}
//DeadCode DAW 01Jul99 						bombableSGT=TRUE;
						if (damage-livetokens*200<lowestdamage)
						{
							rv=test;
							lowestdamage=damage-livetokens*200;
						}
						while (++scan<IllegalSepID)
						{
							if (scan<WayPointBAND || scan>=WayPointBANDEND)
								if ((test=*Persons2::ConvertPtrUID(UniqueID(scan)))!=NULL)
									if (test->SGT==SGT && test->shape!=EMPTY)
										break;
						}
					}while (scan<IllegalSepID);
			}
			if (rv && selectedelt)												//DAW 27Jun99
				*selectedelt=SelectElement(rv,counter);			//DAW 27Jun99
		}
//DeadCode DAW 27Jun99 	if (rv && selectedelt)
//DeadCode DAW 27Jun99 		if (rv->Status.size>=FORMATIONSIZE)
//DeadCode DAW 27Jun99 		{
//DeadCode DAW 27Jun99 			selectedelt=0;
//DeadCode DAW 27Jun99 			rv=SelectConvoyMember(*rv,counter);
//DeadCode DAW 27Jun99 		}
//DeadCode DAW 27Jun99 		else
	if(!rv)
		return currtarget;
	return	rv;
}

//DeadCode DAW 27Jun99 FormationItemPtr	FormationItem::SelectConvoyMember(FormationItemPtr curr,int count)
//DeadCode DAW 27Jun99 {
//DeadCode DAW 27Jun99 	if (count)
//DeadCode DAW 27Jun99 	{
//DeadCode DAW 27Jun99 		if (curr->Leader())
//DeadCode DAW 27Jun99 		{
//DeadCode DAW 27Jun99 			count--;
//DeadCode DAW 27Jun99 			curr=curr->Leader();
//DeadCode DAW 27Jun99 		}
//DeadCode DAW 27Jun99 		while (count)
//DeadCode DAW 27Jun99 		{
//DeadCode DAW 27Jun99 			if (curr->follower)
//DeadCode DAW 27Jun99 				curr=curr->Follower();
//DeadCode DAW 27Jun99 			else
//DeadCode DAW 27Jun99 				if (curr->Leader())
//DeadCode DAW 27Jun99 					curr=curr->Leader();	//make it loop....
//DeadCode DAW 27Jun99 			count--;
//DeadCode DAW 27Jun99 		}
//DeadCode DAW 27Jun99 	}
//DeadCode DAW 27Jun99 	return curr;
//DeadCode DAW 27Jun99 }

bool	FormationItem::SelectedElement(ItemPtr currtarget,int counter/*=0*/,Coords3D* coords/*=&despos*/)
{
	if (currtarget->shape==EMPTY)									  //DAW 16/06/99
		return false;												  //DAW 16/06/99
	else
	if (currtarget->Status.size>=FORMATIONSIZE)
	{
		FormationItemPtr curr=*currtarget;
		int count=counter;
		if (count)
		{
			if (curr->Leader())
			{
				count--;
				curr=curr->Leader();
			}
			while (count)
			{
				if (curr->follower)
					curr=curr->Follower();
				else
					if (curr->Leader())
						curr=curr->Leader();	//make it loop....
				count--;
			}
		}
		*coords=curr->World;
		return (curr->Status.deadtime==0);
	}
	else
	{
		GroupItterator gi(currtarget->shape,currtarget->Anim);
		for (;counter;gi++,counter--)
		{}	
		*coords=gi.delta;
		*coords+=currtarget->World;
		return gi.AnimDataMAD().itemstate!=DEAD;
	}
}

int		FormationItem::SelectElement(ItemPtr currtarget,int counter/*=0*/)
{
	const int maxscores=40;
	UByte scores[maxscores];
	int	slot=0;
	if (currtarget)
	{
		if (currtarget->Status.size>=FORMATIONSIZE)
			return counter;											  //RDH 27/06/99
		for (GroupItterator gi(currtarget->shape,currtarget->Anim);gi&&slot<maxscores;gi++,slot++)
		{
			if (gi.AnimDataMAD().itemstate!=ALIVE)
				if (gi.AnimDataMAD().itemstate!=DEAD)
					scores[slot]=2+gi.DamageWeight()/(gi.AnimDataMAD().itemstate+1);
				else
					scores[slot]=2;	//so zero is lower...
			else
				if (gi.IsStoresToken())
					scores[slot]=255;
				else
					scores[slot]=2+gi.DamageWeight();
		}
		int	bestslot=0;
		counter++;
		while (--counter>-1)
		{
			int	bestscore=0;

			for (int sl=0;sl<slot;sl++)
				if (scores[sl]>bestscore)
				{
					bestslot=sl;
					bestscore=scores[sl];
				}
			if (bestscore==1)
				scores[bestslot]=0;
			else
				scores[bestslot]=1;
		}
		return bestslot;
	}
	else
		return	-1;

}

////////////////////////////////////////////////////////////////////////
//
// Function:    ScoreSimpleItemKilled
// Date:        01/03/99
// Author:      JIM
//
// Description: Simple shapes are generally mobiles.
//				Mobile kill stats are logged while 3d is running.
//
////////////////////////////////////////////////////////////////////////
void	Item::ScoreSimpleItemKilled(bool itsdead,AirStrucPtr killer)
{
	if (_Replay.Playback)										//AMM 11Mar99
		return;													//AMM 11Mar99

	if (killer && killer->Status.size!=AIRSTRUCSIZE)
		killer=NULL;
	Debrief& debrief=MMC.debrief;
	bool	killerisplayer=false;
	bool	killerisgroundsite=true;
	SquadSelect		killersquad=SquadSelect(-1);
	int		killerpilot=-1;
	int		killernat=NAT_RED;
	if (killer)
	{  
		killernat=killer->nationality;
		killerisgroundsite=false;
		killerisplayer=killer->AcIsPlayer()!=NULL;
		if (killer->ai.pilotnum<ai_info::PROPER_PILOT_MAX)
		{
			killerpilot=killer->ai.pilotnum;
			killersquad=SquadSelect(killer->ai.squadnum());
		}
		else
			killersquad=SquadSelect(killer->ai.squadnum());

	}
	if (itsdead)
	{
		if (Status.size>=MOBILESIZE)
			if (Status.size==AIRSTRUCSIZE)
			{
				AirStrucPtr deader=*this;
				Nationality deadernat=deader->nationality;
				bool deaderisplayer=deader->AcIsPlayer()!=NULL;
				SquadSelect	deadersquad;
				int deaderpilot=-1;
				if (deader->ai.pilotnum<ai_info::PROPER_PILOT_MAX)
				{
					deaderpilot=deader->ai.pilotnum;
					deadersquad=SquadSelect(deader->ai.squadnum());
				}
				else
					deadersquad=SquadSelect(deader->ai.squadnum());
				if (killer && killerpilot>=0 && killernat!=deadernat)
				{
					MMC.Active_Pilots[killerpilot].airkillslastmsn++;
						MMC.Active_Pilots[killerpilot].kills++;
				}
				if (deaderpilot>=0)
						MMC.Active_Pilots[deaderpilot].status=KIA;
				if (deadersquad>=SQ_M15_0)
					MMC.migsquad[deadersquad-SQ_M15_0].aclosseslast++;
				if (killer && killernat==NAT_BLUE)
				{
					if (deadernat==NAT_BLUE)	  //LOSSESTOOTHER
					{
						debrief.lastperiod[deadersquad][Debrief::LOSSESTOOTHER]++;
						debrief.lastperiod[SQ_B_NONFLYSPOT][Debrief::LOSSESTOOTHER]++;
					}
					else
					{
						if (	killer->duty==DUTYMIGCAP ||  killer->duty==DUTYBARCAP )
							debrief.barcapkills++;

						if (deadersquad==SQ_YAK)
						{
							debrief.lastperiod[killersquad][Debrief::YAK]++;
							debrief.lastperiod[SQ_B_NONFLYSPOT][Debrief::YAK]++;
							debrief.lastperiod[killersquad][Debrief::REDAC]++;
							debrief.lastperiod[SQ_B_NONFLYSPOT][Debrief::REDAC]++;
						}
						else
						{
							debrief.lastperiod[killersquad][Debrief::MIG]++;
							debrief.lastperiod[SQ_B_NONFLYSPOT][Debrief::MIG]++;
							debrief.lastperiod[killersquad][Debrief::REDAC]++;
							debrief.lastperiod[SQ_B_NONFLYSPOT][Debrief::REDAC]++;
						}
					}
					debrief.unqmcounts[deadersquad]++;
				}
				else
				{
					debrief.redqmcounts[deadersquad]++;

					if (deadernat==NAT_BLUE)
					{
						if (!killer)
						{
							debrief.lastperiod[deadersquad][Debrief::LOSSESTOAAA]++;
							debrief.lastperiod[SQ_B_NONFLYSPOT][Debrief::LOSSESTOAAA]++;
						}
						else
						if (killersquad==SQ_YAK)
						{
							debrief.lastperiod[deadersquad][Debrief::LOSSESTOYAK]++;
							debrief.lastperiod[SQ_B_NONFLYSPOT][Debrief::LOSSESTOYAK]++;
							debrief.lastperiod[deadersquad][Debrief::LOSSESTOREDAC]++;
							debrief.lastperiod[SQ_B_NONFLYSPOT][Debrief::LOSSESTOREDAC]++;
						}
						else
						{
							debrief.lastperiod[deadersquad][Debrief::LOSSESTOMIG]++;
							debrief.lastperiod[SQ_B_NONFLYSPOT][Debrief::LOSSESTOMIG]++;
							debrief.lastperiod[deadersquad][Debrief::LOSSESTOREDAC]++;
							debrief.lastperiod[SQ_B_NONFLYSPOT][Debrief::LOSSESTOREDAC]++;
						}
						if (	deader->duty==DUTYMIGCAP || deader->duty==DUTYBARCAP)
						{	//need to ID wether this is barcap or escort.
	//						AirStrucPtr L=deader;
	//						if (L->leader)	L=L->Leader();
	//						while (L->fly.leadflight)
	//							L=L->fly.leadflight;
	//						if (L->duty==DUTYCAP)
								debrief.barcaplost++;
						}
					}
					else
					{
						if (deadersquad==SQ_YAK)
							debrief.lastperiod[SQ_B_NONFLYSPOT][Debrief::YAK]++;
						else
							debrief.lastperiod[SQ_B_NONFLYSPOT][Debrief::MIG]++;
					}
				}
				if (killerisplayer)
				{
					if (killernat!=deadernat)
						debrief.playertotals[killersquad][Debrief::KILLS]++;
					else
						debrief.playertotals[killersquad][Debrief::LOSSES]++;
					debrief.playerqmcounts[deadersquad]++;
				}
				if (deaderisplayer)
				{
					debrief.playertotals[deadersquad][Debrief::LOSSES]++;
				}
				if (killer && killer!=deader && killer->ai.eventlog!=deader->ai.eventlog)
					if (!killer->IsUsingPilotedAcLog())
						if (!deader->IsUsingPilotedAcLog())
						{
							Persons2::UpdateLog(killer,+1,EventLog::ATTACKEDBYOTHERS);
							Persons2::UpdateLog(deader,-1,EventLog::ATTACKEDBYOTHERS);
						}
						else
						{
							Persons2::UpdateLog(killer,-1,EventLog::KILLED);
						}
					else
						if (!deader->IsUsingPilotedAcLog())
						{
							Persons2::UpdateLog(deader,+1,EventLog::KILLED);
						}
						else
						{	//killed a friend! Can't log.
		//					Persons2::UpdateLog(deader,-1,EventLog::KILLED);
						}
			}
			else
			{	//target is a mobile
				Debrief::Types	counttype=Debrief::TARG_MAX;
				if (SGT)
				{	//either a ground battle target or a convoy or an extra at a main node!
					if (SGT==UID_CASDefend)
					{
						switch ((int)shape)
						{
						case	CHMORT:	counttype=Debrief::TROOPS;break;
						case	UNINFT:	counttype=Debrief::TROOPS;break;
						case	TRAM:  	counttype=Debrief::TROOPS;break;
						case	T34:	counttype=Debrief::TANK;break;
						case	BARGE:	counttype=Debrief::TROOPS;break;
						case	CHINFT:	counttype=Debrief::TROOPS;break;
						case	BARAGL:	counttype=Debrief::TARG_MAX;break;
						case	UNTANK:	counttype=Debrief::TANK;break;
						}
					}
					else
					if (Persons2::getbandfromUID(SGT)==AmberBattleNodeBAND)
					{	//it's a battle node jobbie
						int forcetype=FACReportDamage(itsdead);	//this handles the ground battle scoring as well...
						switch (forcetype)
						{
						case TeamDef::TROOPSONLY:	counttype=Debrief::TROOPS;break;
						case TeamDef::MORTAR:		counttype=Debrief::TROOPS;break;
						case TeamDef::MORTARTRUCK:	counttype=Debrief::TRUCK;break;
						case TeamDef::TANKS:		counttype=Debrief::TANK;break;
						case TeamDef::ARTILLARY:	counttype=Debrief::ARTILLERY;break;
						}
					}
					else
					if (Persons2::getbandfromUID(SGT)==RedRoadBAND || Persons2::getbandfromUID(SGT)==RedRailBand)
					{
						SupplyTree::Supply2UID	rel;
						SupplyNode* node=SupplyTree::FindSupplyNodeForItem(SGT,&rel);
						SupplyRoute* route=SupplyTree::FindBridge(SGT,node->route[rel-SupplyTree::S2U_ROUTE0]);
						route->stores_destroyed+=route->storespermobile;
						if (route->stores_destroyed>route->storeslaunched)
							route->stores_destroyed=route->storeslaunched;
						if (Persons2::getbandfromUID(SGT)==RedRoadBAND)
							counttype=Debrief::TRUCK;
						else
							counttype=Debrief::TRAIN;
					}
					//else you killed the guy on the bike!!!
				}
				//debrief kills:
				if (counttype==Debrief::TARG_MAX)	//not categorised so...
				switch ((int)shape)
				{
				case	CART1:		//	"Wooden train carriage"              
				case	TANKER:		//	"(Fuel) train carriage"              
				case	TCOAL:		//	"(Coal) train carriage"              
				case	THAUL:		//	"Train carriage (two metal boxes)"   
				case	CRANE:		//	"Train carriage crane"               
				case	TWOOD:		//	"Train carriage (stack of logs)"     
				case	TROOPC:		//	"Train carriage (Troop Transport)"   
				case	SUPPLY:		//	"Train carriage (Crates)"            
				case	TPIPE:		//	"Train carriage (Pipes)"             
				case	TCABLE:		//	"Train carriage (Oil)"               
				case	TEMPTY:		//	"Train carriage"                     
				case	TBACK:		//	"Guard carriage (last)"              
				case	TPINC:		//	"Train engine"                       
				case	TROLL:		//	"Train carriage (roll on roll off)"  
				case	TGOODS:		//	"Train carriage (Flat back)"         
				case	SHUNT:		//	"Train shunter"                      
					counttype=Debrief::TRAIN;	break;

				case	T34:		//	"Soviet T-34 (Tank)"                 
				case	UNTANK:		//	"UN Tank (Sherman)"                  
				case	HALFT:		//	"American half-track"                
					counttype=Debrief::TANK;	break;

				case	HTRUCK:		//	"Truck, Russian with roof"    //SPECIAL DIS!!!
					if (!MMC.debrief.OneOffDiss(Debrief::OOD_HutTruck))
						MMC.DisDayEntry(Debrief::TARGUID,SGT,Debrief::D_DeceptionFound02_H);

				case	STEPTO:		//	"Animal and cart"                    

				case	DUMMY7:		//	"Jeep with red cross markings"       
				case	JEEP1:		//	"Jeep (UN open top)"                 
				case	JEEP2:		//	"Covered UN jeep"                    
				case	TTRUCK:		//	"troop carrying Truck"               
				case	SFTRCK:		//	"Small fuel truck"                   
				case	RTRUCK:		//	"Radar trucks"                       
				case	CHTRCK:		//	"Truck (Russian)"                    
				case	UNTRCK:		//	"Truck (UN)"                         
				case	BULL:		//	"Bulldozer"                          
					counttype=Debrief::TRUCK;	break;

					
				case	MORSEL:		//	"Ammo Porter"                //SPECIAL DIS!!!!!!        
					if (!MMC.debrief.OneOffDiss(Debrief::OOD_Monk))
						MMC.DisDayEntry(Debrief::TARGUID,SGT,Debrief::D_DeceptionFound02_H);

				case	HARLEY:		//	"Guy on bike"                        
				case	GHANDI:		//	"Bhuddist Monk"                      

				case	BOAT:		//	"Large grey boat, like oil tanker"   
				case	FISHR:		//	"Canal Boat with sails"              
				case	BARGE:		//	"UN Transport boat"                  
				case	SAMPAN:		//	"Sampan(Small fishing boat)"         
				case	CARGO:		//	"Large cargo ship"                   
				default:
					counttype=Debrief::TARG_MAX;	break;
				}
				if (counttype!=Debrief::TARG_MAX)
				{
					if (killerisplayer)
						debrief.playerqmcounts[counttype]++;
					if (killernat==NAT_RED)
						debrief.redqmcounts[counttype]++;
					else
					{
						debrief.unqmcounts[counttype]++;	
						debrief.lastperiod[killersquad][counttype]++;
					}


				}
				if (killer && killer->IsUsingPilotedAcLog())
					Persons2::UpdateLog(MobileItemPtr(this),+1,EventLog::KILLEDTRUCK);

			}
		else
		{	//target is a static
			Debrief::Types	counttype=Debrief::TARG_MAX;
			if (SGT==UID_CASDefend)
			{
				switch ((int)shape)
				{
				case	CHMORT:	counttype=Debrief::TROOPS;break;
				case	UNINFT:	counttype=Debrief::TROOPS;break;
				case	TRAM:  	counttype=Debrief::TROOPS;break;
				case	T34:	counttype=Debrief::TANK;break;
				case	BARGE:	counttype=Debrief::TROOPS;break;
				case	CHINFT:	counttype=Debrief::TROOPS;break;
				case	BARAGL:	counttype=Debrief::TARG_MAX;break;
				case	UNTANK:	counttype=Debrief::TANK;break;
				}
			}
			else
			if (SGT && Persons2::getbandfromUID(SGT)==AmberBattleNodeBAND)
			{
				int forcetype=FACReportDamage(itsdead);	//this handles the ground battle scoring as well...
				switch (forcetype)
				{
				case TeamDef::TROOPSONLY:	counttype=Debrief::TROOPS;break;
				case TeamDef::MORTAR:		counttype=Debrief::TROOPS;break;
				case TeamDef::MORTARTRUCK:	counttype=Debrief::TRUCK;break;
				case TeamDef::TANKS:		counttype=Debrief::TANK;break;
				case TeamDef::ARTILLARY:	counttype=Debrief::ARTILLERY;break;
				}

			}
	//TEMPCODE JIM 18/05/99 		if (counttype==Debrief::TARG_MAX)
	//TEMPCODE JIM 18/05/99 		{
	//TEMPCODE JIM 18/05/99 			switch (Persons2::getbandfromUID(uniqueID.count))
	//TEMPCODE JIM 18/05/99 			{
	//TEMPCODE JIM 18/05/99 
	//TEMPCODE JIM 18/05/99 
	//TEMPCODE JIM 18/05/99 
	//TEMPCODE JIM 18/05/99 			}
	//TEMPCODE JIM 18/05/99 		}
			if (counttype==Debrief::TARG_MAX)
			{
				if (killer && killer->IsUsingPilotedAcLog() && killer->ai.homebase!=this && SGT!=killer->ai.homebase->uniqueID.count)
				{
					if (killer->EnoughDamage3D(this))
					{
						if (killerisplayer)
							_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLEE_TARGET_DESTROYED,MSG_FAC_SAYS_HIT,*killer,this,*killer));
						Persons2::UpdateLog(this,+1,EventLog::KILLEDSTATIC);
					}
					else
					{
						if (killerisplayer)
							_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLEE_GOODHIT,MSG_FAC_SAYS_HIT,*killer,this,*killer));
						Persons2::UpdateLog(this,+1,EventLog::DAMAGEDSTATIC);
					}
				}
				UniqueID id=SGT;
				if (!id)
					id=uniqueID.count;
				switch (Persons2::getbandfromUID(id))
				{
				case AmberBridgeBAND:	counttype=Debrief::RAILBRIDGE;	break;
				case AmberAirfieldBAND:	counttype=Debrief::AIRFIELD;	break; //RDH 19/06/99
				case AmberMYardBAND:	counttype=Debrief::MARTYARD;	break;
				case AmberSupplyBAND:	counttype=Debrief::SUPPLY;	break;
				}
			}
			if (counttype!=Debrief::TARG_MAX)
			{
				if (killerisplayer)
					debrief.playerqmcounts[counttype]++;
				if (killernat==NAT_RED)
					debrief.redqmcounts[counttype]++;
				else
				{
					debrief.unqmcounts[counttype]++;	
					debrief.lastperiod[killersquad][counttype]++;
				}


			}
		}
	}
	else	//its not dead, Jim!
	{
		if (Status.size>=MOBILESIZE)
			if (Status.size==AIRSTRUCSIZE)
			{	//aircraft
			}
			else
			{	//mobile
				if (SGT && Persons2::getbandfromUID(SGT)==AmberBattleNodeBAND)
				{
					int forcetype=FACReportDamage(itsdead);	//this handles the ground battle scoring as well...
				}
			}
		else
		{	//static
			if (SGT && Persons2::getbandfromUID(SGT)==AmberBattleNodeBAND)
			{
				int forcetype=FACReportDamage(itsdead);	//this handles the ground battle scoring as well...
			}
		}


	}
}

/////////////////////////////////////////////////////////////////////////////
// Group itterator stuff...
////////////////////////////////////////////////////////////////////////
//
// Function:    ScoreSGKills
// Date:        26/02/99
// Author:      JIM
//
// Description: 
//
////////////////////////////////////////////////////////////////////////
struct	WeightScheme
{
	int	peritem,	pertoken,		perbridge,
		perhangar,	perrevetment,	persupply,	perrunway,	pernoscore;

	int	totalscore,	damagescore,	damagebf,	damagemw,	tokenslost;
	Attacks*	scorestore;
	UniqueID	SGTuid;
	SupplyNode*	SGTnode;
	SupplyTree::Supply2UID	SGTrel;
	void	SetWeights(SupplyNode*	node,SupplyTree::Supply2UID	rel,UniqueID SGT)
	{
		SGTnode=node;
		SGTuid=SGT;
		SGTrel=rel;

		switch(rel)
		{
		case SupplyTree::S2U_MAIN:
		{
			peritem=100;
			if (SGT==node->associated_item)
			{
				pertoken=100;
				scorestore=&node->attackstats;
			}
			else
				scorestore=&node->attackstown;
		}
		break;

		case SupplyTree::S2U_AF0:
		case SupplyTree::S2U_AF1:
		case SupplyTree::S2U_AF2:
		{
			AirFieldInfo*	af=SupplyTree::FindAirfieldForItem(SGT);
			perhangar=af->hangarfactor;
			perrevetment=af->rivetfactor;
			persupply=af->supplyfactor;
			pernoscore=0;
			perrunway=af->otherfactor;
			scorestore=&af->attackstats;
		}
		break;
		case SupplyTree::S2U_ROUTE0:
		case SupplyTree::S2U_ROUTE1:
		case SupplyTree::S2U_ROUTE2:
		{
			SupplyRoute*	route=SupplyTree::FindBridge(SGT,node->route[rel-SupplyTree::S2U_ROUTE0]);
			peritem=1;
			perbridge=99;
			scorestore=&route->attackstats;
		}
		break;
		}
		damagebf=scorestore->damageinbf;
		damagemw=scorestore->damageinmw;
		damagescore=damagebf+damagemw;

	}

	void	ClearDamage(bool subworld)
	{
		if (subworld)
		{
			damagebf=0;
			scorestore->aaalevel=0;
		}
		else
		{
			damagemw=0;
			scorestore->LBaaalevel=0;
		}
	}
//This fix is for towns where genral damage should not require 100% kill level.
//However, Bridges and Airfields damage is worked out more precicely.
	enum	{FIX_PERCENT=150};
	void	AddWeightDamage(ShapeNum s,UniqueID member,DeadStream::DeadBlockItterator& gi,bool subworld)
	{	//totalise damage and tokens if interested in tokens.. but who cares!
		{
			int totaldamage=0,totaltokens=0,damagedtokens=0;
			int	damageLB=0,damageSB=0;
			for (GroupItterator  di(s,&gi);di;di++)
			{
				totaldamage+=(di.AnimDataMAD().itemstate*di.DamageWeight());	//max of *3
				if (di.IsStoresToken())	
				{
					totaltokens++;
					if (di.AnimDataMAD().itemstate)
						damagedtokens++;
				}
			}
			totaldamage=totaldamage*4/3;	//3 stages of status.
			if (totaldamage>1050)			//Fix to stop easy to kill groups 
				totaldamage=1050;			//swamping figures if 'overkill'
			switch (Persons2::getbandfromUID(member))
			{
			case AfHangerBAND:		totaldamage*=perhangar;		break;
			case AfRevetmentBAND:	totaldamage*=perrevetment;	break;
			case AfSupplyBAND:		totaldamage*=persupply;		break;
			case AfRunwayBAND:		totaldamage*=perrunway;		break;
			case AfNoScoreBAND:		totaldamage*=pernoscore;	break;
			case AmberAirfieldBAND: totaldamage*=100;			break;
			case AmberBridgeBAND:	totaldamage*=100;		break;
			case RedAAASiteBAND:	
			{
				if (totaldamage>=1000)
				{
					scorestore->aaalevel=scorestore->aaalevel*7/8;
				 	//rescan to revive aaa site
					DeadStream::DeadBlockItterator g2(&gi);
					for (GroupItterator  di(s);di;di++)
						g2.NextEltClearDamage();
				}
				totaldamage=0;
			}
			break;
			case RedAAALargeBAND:
			{
				if (totaldamage<1000)
					scorestore->LBaaalevel++;
				totaldamage=0;
			}
			break;
  			default:
				if (pertoken && damagedtokens)
				{	//rescan to revive damaged tokens for reuse
					DeadStream::DeadBlockItterator g2(&gi);
					for (GroupItterator  di(s);di;di++)
						if (di.IsStoresToken())
							g2.NextEltClearDamage();
						else
							g2.SkipNextDeadElt();
				}
				totaldamage*=peritem+pertoken*totaltokens;
			}
			totaldamage/=100;
			if (subworld)
				damagebf+=totaldamage;
			else
				damagemw+=totaldamage;
			tokenslost+=damagedtokens;
		}

	}

	void	AddWeightTotal(ShapeNum s,UniqueID member,bool subworld)
	{	//only interested in totalising members if members are tokens...

		if (peritem==0)
		{	//airfields have total damage=1000
			scorestore->totalinmw=0;
			scorestore->totalinbf=FIX_PERCENT*10;
		}
		else
		{
			int totaldamage=0,totaltokens=0;
			int	activeLB=0,activeSB=0;
			if (pertoken)
				for (GroupItterator  di(s);di;di++)
				{
					if (di.IsStoresToken())	totaltokens++;
				}
			totaldamage=1000;
			switch (Persons2::getbandfromUID(member))
			{
			case AfHangerBAND:		totaldamage*=perhangar;		break;
			case AfRevetmentBAND:	totaldamage*=perrevetment;	break;
			case AfSupplyBAND:		totaldamage*=persupply;		break;
			case AfRunwayBAND:		totaldamage*=perrunway;		break;
			case AfNoScoreBAND:		totaldamage*=pernoscore;	break;
			case AmberAirfieldBAND: totaldamage*=100;			break;
			case AmberBridgeBAND:	totaldamage*=FIX_PERCENT;	break;
			case RedAAASiteBAND:	
			{
//				if (totaldamage>=1000)
//					scorestore->aaaavail++;
				totaldamage=0;
			}
			break;
			case RedAAALargeBAND:
			{
//				if (totaldamage>=1000)
				scorestore->LBaaaavail++;
				totaldamage=0;
			}
			break;
  			default:				totaldamage*=peritem+pertoken*totaltokens;
			}
			totaldamage/=100;
			if (subworld)
			{
				scorestore->totalinbf+=totaldamage;
				scorestore->tokensinbf+=totaltokens;
			}
			else
			{
				scorestore->totalinmw+=totaldamage;
				scorestore->tokensinmw+=totaltokens;
			}
		}
	}
	bool	WriteBack()
	{
		int sumdamage=90;
		if (scorestore)
		{
			if (((scorestore->totalinbf+scorestore->totalinmw)))
				sumdamage=(int)(damagebf+damagemw)*FIX_PERCENT/((scorestore->totalinbf+scorestore->totalinmw));
#ifndef NDEBUG
			else
				INT3;
#endif
			scorestore->damageinbf=damagebf;
			scorestore->damageinmw=damagemw;
			if (scorestore->damagelevel==sumdamage)
				return false;
			if (	sumdamage<95 
				&& scorestore->damagelevel>=95
				&&	MMC.debrief.currlogday+1-scorestore->daylasthit<5
				)
				{
					if (perbridge)
			 			MMC.DisDayEntry(Debrief::TARGUID, SGTuid, Debrief::D_Repairs00_H);
					else if (perrunway)
			 			MMC.DisDayEntry(Debrief::TARGUID, SGTuid, Debrief::D_Repairs01_H);
				}
//TEMPCODE JIM 13/05/99 				else
//TEMPCODE JIM 13/05/99 		 			MMC.DisDayEntry(Debrief::DISCARDTARGUID, currroute->suppliee->associated_item, Debrief::T_Supply00_H);
			scorestore->damagelevel=sumdamage;
			scorestore->damagedtokens=tokenslost;
		}
		return true;
	}

};

//////////////////////////////////////////////////////////////////////
//
// Function:    ScoreSGKills
// Date:		13/05/99
// Author:		JIM
//
//Description: 
//
//////////////////////////////////////////////////////////////////////

void	DeadStream::ScoreSGKills()
{
	if (_Replay.Playback)										//AMM 11Mar99
		return;													//AMM 11Mar99

////	SupplyTree::ClearAllStatuses();
	MAKEFIELD(UniqueID,UID_NULL,IllegalSepID);
	UniqueIDField	callssgt,mainsgt;
	callssgt=0;
	{	//first, find all the SGTs
		DeadBlockItterator b(firstblock,UID_NULL);
		UniqueID used;
		while ((used=b.SkipItem())!=UID_NULL)
		{
			ItemPtr	p=*Persons2::ConvertPtrUID(used);
			if (p->SGT)
				mainsgt|=p->SGT;
			else
				mainsgt|=used;
		}
		while ((used=b.NextSGT())!=UID_NULL)
		{
			callssgt|=used;
			mainsgt|=used;
		}
	}
	for (int i=0;i<IllegalBAND;i++)
		if (callssgt[UniqueID(i)] || mainsgt[UniqueID(i)])
		{
			UniqueID	SGT=UniqueID(i);
			SupplyTree::Supply2UID	rel;
			SupplyNode*	node=SupplyTree::FindSupplyNodeForItem(SGT,&rel);

			if (node && Persons2::getbandfromUID(SGT)!=RedTruckBAND)
			{

				WeightScheme	weights={0};
				weights.SetWeights(node,rel,SGT);
				if (mainsgt[SGT])
				{	//mainworld member flaged in deadstream
					DeadBlockItterator b(firstblock,UID_NULL);
					UniqueID used;
					weights.ClearDamage(false);
					while ((used=b.SkipItem())!=UID_NULL)
					{
						if (used==SGT || ItemPtr(*Persons2::ConvertPtrUID(used))->SGT==SGT)
							weights.AddWeightDamage(ShapeNum(b.lastshape),used,b,false);
					}
					if (weights.scorestore->totalinmw<=1 && weights.scorestore->totalinbf<=1)//DAW 02Jul99
						if (weights.damagemw>0)
						{
							weights.scorestore->totalinbf=0;
							weights.scorestore->tokensinbf=0;
							for (int i=0;i<IllegalBAND;i++)
								if (i<WayPointBAND || i>WayPointBANDEND)
								{
									ItemPtr p=*Persons2::ConvertPtrUID(UniqueID(i));
									if (i==SGT || (p && p->SGT==SGT && MainWorldBand(UniqueID(i))))
										weights.AddWeightTotal((p->shape),UniqueID(i),false);
								}
						}
						else
						{
							weights.scorestore->totalinbf=1;
							weights.scorestore->tokensinbf=1;
						}
				}
				if (callssgt[SGT])
				{	//subworld member flagged in deadstream
					weights.ClearDamage(true);
					DeadBlockItterator b(firstblock,UID_NULL);
					b.SkipToSGT(SGT);
					while (b.SkipItem())
						weights.AddWeightDamage(ShapeNum(b.lastshape),UniqueID(b.lastuniqueID),b,true);
					if (weights.scorestore->totalinbf<=1 && weights.damagebf>0)
					{	//if had some effect on total damage then need comparator.	
						weights.scorestore->totalinbf=0;
						weights.scorestore->totalinmw=0;
						weights.scorestore->tokensinbf=0;
						weights.scorestore->tokensinmw=0;
						for (int i=0;i<IllegalBAND;i++)
							if (i<WayPointBAND || i>WayPointBANDEND)
							{
						
								ItemBasePtr p2=*Persons2::ConvertPtrUID(UniqueID(i));
								if (p2 && p2->Status.size!=WAYPOINTSIZE)
								{
									ItemPtr p=*p2;
									if (i==SGT)
										weights.AddWeightTotal((p->shape),UniqueID(i),false);
									else
										if (p->SGT==SGT)
											if (MainWorldBand(UniqueID(i)))
												weights.AddWeightTotal((p->shape),UniqueID(i),false);
											else
												weights.AddWeightTotal((p->shape),UniqueID(i),true);
					
				}	}		}	}
				weights.WriteBack();
		}	}
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitGroupFields
//Author		Robert Slater
//Date			Mon 15 Feb 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	GroupItterator::InitGroupFields()
{
	ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(group);

	baseanimdata = animdata;
	noelements = 0;
	totalpoints = 0;
	hitlimit = false;
	status = 0; 

	if (SHAPESTUFF.GetShapeScale(sdptr)==SHP_GRP)
	{
		UByteP			instr_ptr;
		DOGROUP_PTR		ptr;
		SWord			instruction;


		instr_ptr = (UByteP)sdptr + sdptr->liveshpref;

		forever
		{
			instruction = *instr_ptr;
			instr_ptr++;

			if (instruction == dogroupno)
			{
				ptr = (DOGROUP_PTR) instr_ptr;

				if (!noelements)
				{
					shape = (ShapeNum) ptr->shapenum;

					delta.X = ptr->xoffset;
					delta.Y = ptr->yoffset;
					delta.Z = ptr->zoffset;

					grpindexer = basegrpindexer = (char*)instr_ptr;
					
					if (animdata != NULL)
					{
						MinAnimData*	mad = (MinAnimData*) animdata;
						status = mad->itemstate;
						deadittfirstbyteptr=&animdata[0];		//RJS 27Apr99 //CSB 04/06/99
//DEADCODE DAW 26/04/99 #pragma message ("Deadbits need fixing Robert")
//DEADCODE DAW 26/04/99 						deadittfirstbyte=*animptr;
//DEADCODE DAW 26/04/99 						status = ((MinAnimData*)animdata)->itemstate;
//DeadCode DAW 26Apr99 						status = ((MinAnimData*)animptr)->itemstate;
					}
					percentdamage=ptr->element_number;
				}

				totalpoints += ptr->element_number;
				noelements++;

				instr_ptr += sizeof(DOGROUP);
			}
			else
				break;
		}
		if (noelements<2)
			hitlimit=true;
	}
	else
	{	//get same info for simple item, please!	//CSB 02/04/99	
		delta.X=delta.Y=delta.Z=0;
		shape=group;
		noelements=1;
		totalpoints=100;
		if (animdata != NULL)
		{
			MinAnimData*	mad = (MinAnimData*) animdata;
			status = mad->itemstate;
//DEADCODE DAW 26/04/99 #pragma message ("Deadbits need fixing Robert")
			deadittfirstbyteptr=&animdata[0];		//RJS 27Apr99	  //CSB 04/06/99
//DEADCODE DAW 26/04/99 			status = ((MinAnimData*)animdata)->itemstate;
		}
		percentdamage=300;

//DEADCODE RDH 20/05/99 		hitlimit=true;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NumElts
//Author		Robert Slater
//Date			Mon 15 Feb 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
int	GroupItterator::NumElts()
{
	return(noelements);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		EltAnimDataSize
//Author		Robert Slater
//Date			Mon 15 Feb 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
int	GroupItterator::EltAnimDataSize()
{
//	if (animdata)
	return(SHAPE.GetAnimDataSize(shape));

	return(0);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NextElement
//Author		Robert Slater
//Date			Mon 15 Feb 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool	GroupItterator::NextElement()
{
	if (!hitlimit)
	{
		DOGROUP_PTR		ptr;
		UByteP			instr_ptr;
		SWord			instruction;

		instr_ptr = (UByteP)grpindexer;
		instr_ptr += sizeof(DOGROUP);

		instruction = *instr_ptr;
		if (instruction == dogroupno)
		{
			ShapeNum	newshp;

			instr_ptr++;

			ptr = (DOGROUP_PTR) instr_ptr;

			newshp = (ShapeNum) ptr->shapenum;

			if (animdata != NULL)
			{
				animdata += SHAPE.GetElementAnimOffset(shape);
			 
				status = ((MinAnimData*)animdata)->itemstate;
				deadittfirstbyteptr=&animdata[0];
			}

			shape = newshp;

			delta.X = ptr->xoffset;
			delta.Y = ptr->yoffset;
			delta.Z = ptr->zoffset;

			percentdamage = ptr->element_number;

			grpindexer = (char*)instr_ptr;

			return(true);
		}
		else
			hitlimit = true;
	}

	return(false);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		IsStoresToken
//Author		Robert Slater
//Date			Mon 15 Feb 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool	GroupItterator::IsStoresToken()
{
	if (shape==group) return false;								//DAW 27May99 fix from JIM
	return (((DOGROUP_PTR)grpindexer)->tokenflag >= GRP_TKN_INVIS_DEP);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DamageWeight
//Author		Robert Slater
//Date			Mon 15 Feb 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
int		GroupItterator::DamageWeight()
{
	return(percentdamage);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MaxDamagePoints
//Author		Robert Slater
//Date			Mon 15 Feb 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
int		GroupItterator::MaxDamagePoints()
{
	return(totalpoints);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AnimDataByte
//Author		Robert Slater
//Date			Mon 15 Feb 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
UByte&	GroupItterator::AnimDataByte()
{
	if (deadittfirstbyteptr)
		return	*deadittfirstbyteptr;
	else
		_Error.EmitSysErr(__FILE__": deadittfirstbyteptr is notright!");

	UByte	retval = 0;

	return retval;
}
MinAnimData&	GroupItterator::AnimDataMAD()	
{return	(MinAnimData&) AnimDataByte();}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		EltLauncherDataSize
//Author		Robert Slater
//Date			Mon 15 Feb 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
int		GroupItterator::EltLauncherDataSize(animptr&	adptr)
{
	if (adptr != NULL)
	{
		MinAnimData*	mad = (MinAnimData*) adptr;

		return(mad->nolaunchers * sizeof(DOLAUNCHER)+sizeof(MinAnimData));
	}

	return(0);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PostLauncherDataSize
//Author		Robert Slater
//Date			Mon 15 Feb 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
int		GroupItterator::PostLauncherDataSize()
{
	return(EltAnimDataSize()-EltLauncherDataSize(animdata));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PostLauncherDataLoc
//Author		Robert Slater
//Date			Mon 15 Feb 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
char*	GroupItterator::PostLauncherDataLoc()
{
	if (animdata != NULL)
	{
		animptr	newanimdata = animdata;

		newanimdata += EltLauncherDataSize(newanimdata);	//RJS 27Apr99
//DEADCODE DAW 28/04/99 Now in ELDS
//DEADCODE DAW 28/04/99 		newanimdata += sizeof(MinAnimData);

		return((char*)&newanimdata);
	}

	return(0);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ResetLaunchers
//Author		Robert Slater
//Date			Mon 15 Feb 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	GroupItterator::ResetLaunchers()
{
	if (animdata != NULL)
	{
//DeadCode RJS 21Apr99 		animptr			mad = animdata;
		MinAnimData*	madold = (MinAnimData*) animdata;

		UByte	oldinvisible = madold->IsInvisible;

		SHAPE.InitGlobalItem();
//DeadCode RJS 21Apr99 		SHAPE.InitItemAnim(mad,shape);
		SHAPE.InitItemAnim(animdata,shape);						//RJS 21Apr99

		madold->IsInvisible = oldinvisible;
	}
}
void	ArtInt::FakeMissionSuccess()
{
	for (AcArrayItterator itt;itt.Next();)
		if (itt)
		{
			if (itt->nationality==NAT_BLUE)
				if (!itt->Status.deadtime)
					if (itt->movecode!=AUTO_FAC)
						itt->MissionDiceThrow();
		}
}

void	AirStruc::MissionDiceThrow(WayPointPtr startwp)
{	//called to decide wether a mission was a success...
	//Possible outcomes:
	//Big bomber killed/Pilot killed 1/(10+wpname+skill)
	//small number of targets killed
	//large number of targets killed	-	only big bomber 50%
	//
	//
	enum	{HARDER=5};	//4 or 5 for final version... 2 is easy - lots of kills
	if (!startwp)
		if (waypoint && waypoint->wpname && waypoint->wpname<=WPNAME_Target)
			startwp=waypoint->FindWP(WPNAME_Target);
	int migskillfactor=	( MMC.migsquad[0].generalskill*20+MMC.migsquad[0].morale+MMC.migsquad[0].agglevel*50+MMC.migsquad[0].maxevent*10
						+MMC.migsquad[1].generalskill*20+MMC.migsquad[1].morale+MMC.migsquad[1].agglevel*50+MMC.migsquad[1].maxevent*10)
						/300;
	if (nationality==NAT_BLUE)
		if (waypoint && waypoint->wpname && !Math_Lib.rnd(10+waypoint->wpname*8+ai.flyingskill*3-migskillfactor) && !AcIsPlayer())
		{
			ScoreSimpleItemKilled(true,NULL);
		}
		else
		if (startwp && startwp->wpname && !Math_Lib.rnd(10+startwp->wpname*8+ai.flyingskill*3-migskillfactor) && !AcIsPlayer())
		{
			ScoreSimpleItemKilled(true,NULL);
		}
		else
		if (startwp)
		{
			WayPointPtr targwp=startwp;
			while (targwp && targwp->wpnum)	  //SQ_B29=6 SQ_F86A=0
				targwp=targwp->prev;
				int	numkills=Math_Lib.rnd(HARDER+1+ai.squadnum()*3)/HARDER;
				//F86=rnd(HARDER+1)/HARDER
				//B29=rnd(HARDER+7)/HARDER
				if ((duty&ACTIONCODE)==DA_CAP)				//H=2						//H=5
				{		//F86=rnd(HARDER*3+7)/(HARDER*3)	13/6 =6x0,6x1,1x2 =>8/13	22/15==> 15x0,7x1 = 7/22 =0.31
						//B29=rnd(HARDER*3+1)/(HARDER*3)	7/6	 =6x0,1x1     =>1/7		16/15==> 15x0,1x1 = 1/16 =0.07
						int	sq=ai.squadnum();
						int migsq=Math_Lib.rnd(7+HARDER*3-sq);
						int numkills=migsq/(HARDER*3);
						migsq&=1;
						if (numkills && MMC.migsquad[migsq].ac_total_avail)
						{
							MMC.migsquad[migsq].aclosseslast+=numkills;
							if (MMC.migsquad[migsq].actype==PT_YAK)
								MMC.debrief.lastperiod[SquadSelect(sq)][Debrief::YAK]+=numkills;
							else
								MMC.debrief.lastperiod[SquadSelect(sq)][Debrief::MIG]+=numkills;
							MMC.debrief.lastperiod[SquadSelect(sq)][Debrief::REDAC]+=numkills;
						 	MMC.debrief.barcapkills+=numkills;
						}
				}
				else
					if (numkills)
					{
						UniqueID targuid=UID_NULL;
						if (targwp)
						{
							WayPointPtr patrolwp=targwp->NextWP(uniqueID.count);
							ItemBasePtr target=patrolwp->target;
							if (target==NULL || target==targwp)
							{
								AirStrucPtr topleader=NULL;
								if (formpos)
									if (fly.leadflight && fly.leadflight->fly.leadflight)
										topleader=fly.leadflight->fly.leadflight;
									else
										topleader=NULL;
								else
									if (fly.leadflight)
										topleader=fly.leadflight;
									else
										topleader=NULL;
								if (topleader)
								{
									patrolwp=targwp->NextWP(topleader->uniqueID.count);
									target=patrolwp->target;
								}
								if (target==NULL || target==targwp)
								{
									target=Persons2::ConvertPtrUID(UniqueID(GR_Pack_Target));
								}
							}
							if (target==targwp)
								target=NULL;
							
							if (target)
								if (target->Status.size>=ITEMSIZE && ItemPtr(target)->SGT)
									targuid=ItemPtr(target)->SGT;
								else
									targuid=target->uniqueID.count;

						}
						if (targuid!=UID_NULL)
						{
							SupplyTree::Supply2UID nodetype;
							SupplyNode* sn=SupplyTree::FindSupplyNodeForItem(targuid,&nodetype);
							SupplyRoute* sr=NULL;
							AirFieldInfo* af=NULL;
							Attacks* attacks=NULL;
							if (sn)
								switch (nodetype)
								{
								case SupplyTree::S2U_AF0:
								case SupplyTree::S2U_AF1:
								case SupplyTree::S2U_AF2:
								{
									af=SupplyTree::FindAirfieldForItem(targuid);
									attacks=&af->attackstats;
								}
								break;
								case SupplyTree::S2U_ROUTE0:
								case SupplyTree::S2U_ROUTE1:
								case SupplyTree::S2U_ROUTE2:
								{
									sr=SupplyTree::FindBridge(targuid,sn->route[nodetype-SupplyTree::S2U_ROUTE0]);
									attacks=&sr->attackstats;
								}
								break;
								default:
								{
									attacks=&sn->attackstats;
								}
								}

								switch(duty&DUTYMASK)
								{
								case DC_CAS:
								{	//find the right front and kill some trucks
									SupplyLine* sl=sn->supplyline;
									if (sl && sl->frontline->forward && sl->frontline->forward->suppliee==sn)
										while (--numkills>=0)
										{
									//pick a RED team
											TeamDef::Team	reqteam=(sl->initiative!=REDATTACKING)?TeamDef::HOME:TeamDef::AWAY;
											for (int count=sl->groundbattle.usedteams,team=Math_Lib.rnd(count);
													count;
													count--,team=(team==0)?(sl->groundbattle.usedteams-1):(team-1))
												breakif(sl->groundbattle.teamlist[team].team==reqteam);
											if (sl->groundbattle.teamlist[team].lastlosses<sl->groundbattle.teamlist[team].MAX_LOSSES)
												sl->groundbattle.teamlist[team].lastlosses++;
										}
								}
								break;
								case DC_WW:
								{	//find the right node and kill some AAA
									if (attacks)
										attacks->aaalevel=attacks->aaalevel*5/(numkills+4);
								}
								break;
								case DC_AR:
								{	//find the right routes and kill some trucks
									if (!sr)
									{
										UniqueID t1=UID_NULL,t2=UID_NULL;
										WayPoint* wp=startwp;
										while (wp && wp->wpname==WPNAME_Target)
										{
											if (wp->action==wpstartloopno && wp->target)
												if (wp->target->SGT)
													t1=wp->target->SGT;
												else
													t1=wp->target->uniqueID.count;
											if (wp->action==wpstoploopchkno && wp->target)
												if (wp->target->SGT)
													t2=wp->target->SGT;
												else
													t2=wp->target->uniqueID.count;	
											wp=wp->NextWP(uniqueID.count);
										}
										int r=Math_Lib.rnd()|0xffff0000;
										int route=r&3;
										for (int i=0;i<3;i++)
											if (sn->route[i])
												if (	sn->route[i]->supplier->associated_item==t1
													||	sn->route[i]->supplier->associated_item==t2
													||	sn->route[i]->supplier->associated_town==t1
													||	sn->route[i]->supplier->associated_town==t2
													)
												route=i;
										if (route!=3)
											sr=sn->route[route];
										else
											sr=sn->forward;
										if (sr)
											for (;sr->alternateroute;sr=sr->alternateroute) //JIM 30/06/99
												if (sr->storeslaunched)
													breakif((r>>=2)&3);

									}
									if (sr)
									{									
										sr->stores_destroyed+=3*numkills;//DAW 02Sep99
//DeadCode DAW 02Sep99 										sr->stores_destroyed+=sr->storespermobile*numkills/2;
										if (sr->stores_destroyed>sr->storeslaunched)
											sr->stores_destroyed=sr->storeslaunched;
									}
								}
								break;
								case DC_BOMB:
								{	//find items in the world with the right SGT and kill elements of them
									if (targuid)
									{
										int	skipcount=50/(numkills+1);
										UniqueID	curr=targuid;
										while (--numkills>=0)
										{
											ItemPtr target;
											int count=Math_Lib.rnd(skipcount);
											int	loopcheck=skipcount;
											forever
											{
												ItemBasePtr trg;
												trg=Persons2::ConvertPtrUID(curr);
												if (trg && trg->Status.size==ITEMSIZE)
												{
													target=*trg;
													if (curr==targuid || target->SGT==targuid)
														breakif(!count--);
												}
												if (!curr)
												{
													curr=IllegalSepID;
													if (count==skipcount)
													{
														target=NULL;
														break;
													}
													skipcount=count;
												}
												curr=UniqueID(curr-1);
											};
											if (target)
											{	//now kill an element!
												GroupItterator gi(target->shape,target->Anim);
												if (gi.NumElts())
												{
													for (int counter=Math_Lib.rnd(gi.NumElts());counter;gi++,counter--)
													{}
													if (gi.AnimDataMAD().itemstate!=DEAD)
														if (Math_Lib.rnd(280)>gi.DamageWeight())
															gi.AnimDataMAD().itemstate++;
												}
											}
										}
									}
								}
								break;
								}
						}
					}
		}
}
 
void		TeamDef::DiagnosticOutput(char* intro)
{	 //TRACE0
//TempCode DAW 22Jun99 	::AfxTrace("%s: %s %s = %s # %i - %i @ %s = %s ? %s = %s ==> %s = %s\n",
//TempCode DAW 22Jun99 		intro,(team==HOME)?"Home":"Away",
//TempCode DAW 22Jun99 				LoadResString(forcename),LoadResString(IDS_PHRASE_TROOPCOMPANY+forcetype),
//TempCode DAW 22Jun99 				strength,lastlosses,
//TempCode DAW 22Jun99 				LoadResString(IDS_PLACENAMES_START+location),location?node?LoadResString(node->mainids):"!NULL!":"null",
//TempCode DAW 22Jun99 				LoadResString(IDS_L_INACTIVE+action),LoadResString(IDS_L_INACTIVE+namedaction),
//TempCode DAW 22Jun99 				LoadResString(IDS_PLACENAMES_START+nextlocation),nextlocation?nextnode?LoadResString(nextnode->mainids):"!NULL!":"null"
//TempCode DAW 22Jun99 				);
//TempCode DAW 22Jun99 

}


void	SupplyLine::DiagnosticOutput(int type,char* intro)
{
//TempCode DAW 24Jun99 	::AfxTrace("%s: %s @ %s %s #%i/%i\n",
//TempCode DAW 24Jun99 			intro,
//TempCode DAW 24Jun99 			LoadResString(IDS_L_REDINITIATIVE+initiative),
//TempCode DAW 24Jun99 			(frontline->type==NOCONTEST)?"NoContest":"Battle",
//TempCode DAW 24Jun99 			LoadResString(IDS_PLACENAMES_START+frontline->associated_item),
//TempCode DAW 24Jun99 			frontline->currentstores,frontline->maxstorestonnes
//TempCode DAW 24Jun99 			);
}
