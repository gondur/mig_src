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

//
// Logging dialog inter-relationships:
//
//
//

#include "stdafx.h"


//dummy notify routines that can be overloaded
void	RDialog::ParentDialClosed(RDialog*,int)
{}
void	RDialog::ChildDialClosed(int,RDialog*,int)
{}
void	CRToolBar::ChildDialClosed(int,RDialog*,int)
{}
void	RDialog::RefreshData(int)
{}
void	CRToolBar::RefreshData(int)
{}

//
//real management code
//

int RDialog::LogChild(RDialog* child)
{
	//first have to find right pane...
	RDialog* top=InDialAncestor();
	RDialog* chtop=child->InDialAncestor();
	int rv=0;
	if (!top->dialoglinks.loggedchild)
	{
		top->dialoglinks.loggedchild=new RDialog* [dialoglinks.MAX_CHILD_DIALS];
		top->dialoglinks.loggedchildlauncher=new RDialog* [dialoglinks.MAX_CHILD_DIALS];
		for (int i=0;i<dialoglinks.MAX_CHILD_DIALS;i++)
			top->dialoglinks.loggedchild[i]=top->dialoglinks.loggedchildlauncher[i]=NULL;
	}
	while (top->dialoglinks.loggedchild[rv])	rv++;
	top->dialoglinks.loggedchild[rv]=chtop;
	top->dialoglinks.loggedchildlauncher[rv]=this;
	chtop->dialoglinks.loggedparent=top;
	chtop->dialoglinks.loggedparentlauncher=child;
	return rv;
}
bool	RDialog::LogChild(int rv,RDialog* child)
{
	//first have to find right pane...
	RDialog* top=InDialAncestor();
	RDialog* chtop=child->InDialAncestor();
	if (!top->dialoglinks.loggedchild)
	{
		top->dialoglinks.loggedchild=new RDialog* [dialoglinks.MAX_CHILD_DIALS];
		top->dialoglinks.loggedchildlauncher=new RDialog* [dialoglinks.MAX_CHILD_DIALS];
		for (int i=0;i<dialoglinks.MAX_CHILD_DIALS;i++)
			top->dialoglinks.loggedchild[i]=top->dialoglinks.loggedchildlauncher[i]=NULL;
	}
	else
		if	(top->dialoglinks.loggedchild[rv])
			return false;
	top->dialoglinks.loggedchild[rv]=chtop;
	top->dialoglinks.loggedchildlauncher[rv]=this;
	chtop->dialoglinks.loggedparent=top;
	chtop->dialoglinks.loggedparentlauncher=child;
	return true;
}
int CRToolBar::LogChild(RDialog* child)
{
	//first have to find right pane...
	RDialog* chtop=child->InDialAncestor();
	int rv=0;
	if (!dialoglinks.loggedchild)
	{
		dialoglinks.loggedchild=new RDialog* [dialoglinks.MAX_CHILD_DIALS];
		dialoglinks.loggedchildlauncher=new RDialog* [dialoglinks.MAX_CHILD_DIALS];
		for (int i=0;i<dialoglinks.MAX_CHILD_DIALS;i++)
			dialoglinks.loggedchild[i]=dialoglinks.loggedchildlauncher[i]=NULL;
	}
	while (dialoglinks.loggedchild[rv])	rv++;
	dialoglinks.loggedchild[rv]=chtop;
	dialoglinks.loggedchildlauncher[rv]=NULL;
	chtop->dialoglinks.loggedparenttool=this;
	chtop->dialoglinks.loggedparentlauncher=child;
	return rv;
}
bool	CRToolBar::LogChild(int rv,RDialog* child)
{
	//first have to find right pane...
	RDialog* chtop=child->InDialAncestor();
	if (!dialoglinks.loggedchild)
	{
		dialoglinks.loggedchild=new RDialog* [dialoglinks.MAX_CHILD_DIALS];
		dialoglinks.loggedchildlauncher=new RDialog* [dialoglinks.MAX_CHILD_DIALS];
		for (int i=0;i<dialoglinks.MAX_CHILD_DIALS;i++)
			dialoglinks.loggedchild[i]=dialoglinks.loggedchildlauncher[i]=NULL;
	}
	else
		if	(dialoglinks.loggedchild[rv])
			return false;
	dialoglinks.loggedchild[rv]=chtop;
	dialoglinks.loggedchildlauncher[rv]=NULL;
	chtop->dialoglinks.loggedparenttool=this;
	chtop->dialoglinks.loggedparentlauncher=child;
	return true;
}

void	CRToolBar::DialExitFix(int rv)
{	//never got logged parent!
	if (dialoglinks.loggedchild)
	{
		for (int ind=0;ind<dialoglinks.MAX_CHILD_DIALS;ind++)
			if (dialoglinks.loggedchild[ind])
			{
				RDialog* ch=dialoglinks.loggedchild[ind];
				dialoglinks.loggedchild[ind]=NULL;
				ch->dialoglinks.loggedparent=NULL;
				ch->dialoglinks.loggedparentlauncher->ParentDialClosed(dialoglinks.loggedchildlauncher[ind],rv);
			}
		RDialog** lct=dialoglinks.loggedchild;
		dialoglinks.loggedchild=NULL;
		delete []lct;
		lct=dialoglinks.loggedchildlauncher;
		dialoglinks.loggedchildlauncher=NULL;
		delete []lct;
	}
}

void	RDialog::DialExitFix(int rv)
{
	if (dialoglinks.loggedparent)
	{	//need to find child in parent's list
		int ind=0;
		RDialog* ch=dialoglinks.loggedparent;
		dialoglinks.loggedparent=NULL;
		while (ch->dialoglinks.loggedchild[ind]!=this)
			ind++;
		ch->dialoglinks.loggedchild[ind]=NULL;
		ch->dialoglinks.loggedchildlauncher[ind]->ChildDialClosed(ind,dialoglinks.loggedparentlauncher,rv);
	}
	if (dialoglinks.loggedparenttool)
	{
		int ind=0;
		CRToolBar* ch=dialoglinks.loggedparenttool;
		dialoglinks.loggedparenttool=NULL;
		while (ch->dialoglinks.loggedchild[ind]!=this)
			ind++;
		ch->dialoglinks.loggedchild[ind]=NULL;
		ch->ChildDialClosed(ind,dialoglinks.loggedparentlauncher,rv);
	}
	if (dialoglinks.loggedchild)
	{
		for (int ind=0;ind<dialoglinks.MAX_CHILD_DIALS;ind++)
			if (dialoglinks.loggedchild[ind])
			{
				RDialog* ch=dialoglinks.loggedchild[ind];
				dialoglinks.loggedchild[ind]=NULL;
				ch->dialoglinks.loggedparent=NULL;
				ch->dialoglinks.loggedparentlauncher->ParentDialClosed(dialoglinks.loggedchildlauncher[ind],rv);
			}
		RDialog** lct=dialoglinks.loggedchild;
		dialoglinks.loggedchild=NULL;
		delete []lct;
		lct=dialoglinks.loggedchildlauncher;
		dialoglinks.loggedchildlauncher=NULL;
		delete []lct;
	}
}		 

int		RDialog::LoggedChild()
{
	RDialog* top=InDialAncestor();
	if (!top->dialoglinks.loggedchild)
		return -1;
	for (int i=0;i<dialoglinks.MAX_CHILD_DIALS;i++)
		if (top->dialoglinks.loggedchild[i])
			return i;
	return -1;
}

RDialog* RDialog::LoggedChild(int i)
{
	RDialog* top=InDialAncestor();
	if (!top->dialoglinks.loggedchild) 
		return (NULL);
	else
		return (top->dialoglinks.loggedchild[i]);
}

int		CRToolBar::LoggedChild()
{
	if (!dialoglinks.loggedchild)
		return -1;
	for (int i=0;i<dialoglinks.MAX_CHILD_DIALS;i++)
		if (dialoglinks.loggedchild[i])
			return i;
	return -1;
}

RDialog* CRToolBar::LoggedChild(int i)
{
	if (!dialoglinks.loggedchild) 
		return (NULL);
	else
		return (dialoglinks.loggedchild[i]);
}
bool	RDialog::CloseLoggedChild(int i)
{	//returns true if child still there!
	RDialog* top=InDialAncestor();
	if (!top->dialoglinks.loggedchild)
		return false;
	if (top->dialoglinks.loggedchild[i])
		top->dialoglinks.loggedchild[i]->dialoglinks.loggedparentlauncher->OnCancel();
	return (top->dialoglinks.loggedchild[i]!=NULL);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CloseLoggedChildren
//Author		Jim Taylor
//Date			Fri 19 Feb 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RDialog::CloseLoggedChildren(RDialog* skipthis)
{
	if (skipthis)
		skipthis=skipthis->InDialAncestor();
	RDialog* top=InDialAncestor();
	if (!top->dialoglinks.loggedchild)
		return;
	for (int i=0;i<dialoglinks.MAX_CHILD_DIALS;i++)
		if (top->dialoglinks.loggedchild[i] && top->dialoglinks.loggedchild[i]!=skipthis)
			top->dialoglinks.loggedchild[i]->dialoglinks.loggedparentlauncher->OnCancel();
}

void	CRToolBar::CloseLoggedChildren(RDialog* skipthis)
{
	if (skipthis)
		skipthis=skipthis->InDialAncestor();
	if (!dialoglinks.loggedchild)
		return;
	for (int i=0;i<dialoglinks.MAX_CHILD_DIALS;i++)
		if (dialoglinks.loggedchild[i] && dialoglinks.loggedchild[i]!=skipthis)
			dialoglinks.loggedchild[i]->dialoglinks.loggedparentlauncher->OnCancel();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CloseLoggedChild
//Author		Jim Taylor
//Date			Fri 19 Feb 1999
//
//Description	
//
//Inputs		
//
//Returns		true if child slot still active
//
//------------------------------------------------------------------------------
bool	CRToolBar::CloseLoggedChild(int i)
{	//returns true if child still there!
	if (!dialoglinks.loggedchild)
		return false;
	if (dialoglinks.loggedchild[i])
		dialoglinks.loggedchild[i]->dialoglinks.loggedparentlauncher->OnCancel();
	return (dialoglinks.loggedchild[i]!=NULL);
}

void	RDialog::RefreshChild(int i)
{
	RDialog* top=InDialAncestor();
	if (!top->dialoglinks.loggedchild)
		return;
	if (top->dialoglinks.loggedchild[i])
		top->dialoglinks.loggedchild[i]->dialoglinks.loggedparentlauncher->RefreshData(-1);
}

void	CRToolBar::RefreshChild(int i)
{
	if (!dialoglinks.loggedchild)
		return;
	if (dialoglinks.loggedchild[i])
		dialoglinks.loggedchild[i]->dialoglinks.loggedparentlauncher->RefreshData(-1);
}

void	RDialog::RefreshParent()
{
	RDialog* top=InDialAncestor();
	if (top->dialoglinks.loggedparent)
		for (int i=0;i<dialoglinks.MAX_CHILD_DIALS;i++)
			if (top->dialoglinks.loggedparent->dialoglinks.loggedchild[i]==top)
			{
				top->dialoglinks.loggedparent->dialoglinks.loggedchildlauncher[i]->RefreshData(i);
				return;
			}
}

void	CRToolBar::MakeChildrenVisible(bool enable)
{
	if (!dialoglinks.loggedchild)
		return;
	int setting;
	if (enable)
		setting=SW_SHOW;
	else
		setting=SW_HIDE;
	for (int i=0;i<dialoglinks.MAX_CHILD_DIALS;i++)
		if (dialoglinks.loggedchild[i])
		{
			dialoglinks.loggedchild[i]->ShowWindow(setting);
			dialoglinks.loggedchild[i]->dialoglinks.loggedparentlauncher->MakeChildrenVisible(enable);
		}
}


void	RDialog::MakeChildrenVisible(bool enable)
{
	RDialog* top=InDialAncestor();
	if (!top->dialoglinks.loggedchild)
		return;
	int setting;
	if (enable)
		setting=SW_SHOW;
	else
		setting=SW_HIDE;
	for (int i=0;i<dialoglinks.MAX_CHILD_DIALS;i++)
		if (top->dialoglinks.loggedchild[i])
		{
			top->dialoglinks.loggedchild[i]->ShowWindow(setting);
			top->dialoglinks.loggedchild[i]->dialoglinks.loggedparentlauncher->MakeChildrenVisible(enable);
		}
}
