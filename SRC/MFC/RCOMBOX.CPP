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

// RComboX.cpp: implementation of the CRComboExtra class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "RComboX.h"
#include	"bfnumber.h"
#include	"persons2.h"
#include	"worldinc.h"
#include	"mymath.h"
#include "migview.h"
#include	"messengn.h"

#ifdef _DEBUG
#ifndef	 THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRComboExtra::CRComboExtra()
{

}

CRComboExtra::~CRComboExtra()
{

}

CRComboExtra*	CRComboExtra::Clear()
{
	CRCombo::Clear();
	return this;
}

CRComboExtra*	CRComboExtra::SetList(int resid,int len)
{
	SetCaption(LoadResString(resid));
	while(len--)
		AddString(LoadResString(resid++));
	return this;	 //neat trick used by the streams stuff...
}

CRComboExtra*	CRComboExtra::SetIndex(int resid)
{
	CRCombo::SetIndex(resid);
	return this;
}

CRComboExtra*	CRComboExtra::MakeNumList(int steps,int base,int stepsize)
{
	while(steps--)
	{
		char buffer[10];
		sprintf(buffer,"%i",base);
		AddString(buffer);
		base+=stepsize;
	}
	return this;
}

int	CRComboExtra::GetIndex()
{
//	CRListBox*	l=(CRListBox*)GetListbox();
	//I don't think you have the info I need!!!
	return CRCombo::GetIndex();
}
// SpinButton version
CRSpinButExtra::CRSpinButExtra()
{

}

CRSpinButExtra::~CRSpinButExtra()
{

}

CRSpinButExtra*	CRSpinButExtra::Clear()
{
	CRSpinBut::Clear();
	return this;
}

CRSpinButExtra*	CRSpinButExtra::SetList(int resid,int len)
{
//	SetCaption(LoadResString(resid));
	while(len--)
		AddString(LoadResString(resid++));
	return this;	 //neat trick used by the streams stuff...
}

CRSpinButExtra*	CRSpinButExtra::SetIndex(int resid)
{
	CRSpinBut::SetIndex(resid);
	return this;
}

CRSpinButExtra*	CRSpinButExtra::MakeNumList(int steps,int base,int stepsize)
{
	while(steps--)
	{
		char buffer[10];
		sprintf(buffer,"%i",base);
		AddString(buffer);
		base+=stepsize;
	}
	return this;
}

int	CRSpinButExtra::GetIndex()
{
//	CRListBox*	l=(CRListBox*)GetListbox();
	//I don't think you have the info I need!!!
	return CRSpinBut::GetIndex();
}

CString		GetTargName(UniqueID u)	
{
	CString	name;
	name = LoadResString(IDS_PLACENAMES_START + u);
	if (name.IsEmpty())
	{
		info_itemS* p = *Persons2::SlowConvertPtrUID(u);
		if (p)
		if (p->Status.size!=WAYPOINTSIZE)
		{
			if (p->SGT != UID_Null)
			{
				name = GetTargName(p->SGT)+": "+GetShapeName(ShapeNum(p->shape.Evaluate()));
			}else
			{
				name = GetShapeName(ShapeNum(p->shape.Evaluate()));
			}
		}
		else
		{
			name = LoadResString(IDS_WAYPOINT) + ": "; 
			name = name + LoadResString(Profile::WPType(u));
		}
	}		
//	char buff[10];
//	sprintf(buff,"targ %04x",(UWord)u);
	return (name);
}
static int GetAreaNum(Coords3D* c)
{
	int x=c->X>>21;
	int y=c->Z>>21;
	x=((x&7)+(x&0x38)*8)*8;
	y=(y&7)+(y&0x38)*8;
	return x+y;//+01111;	//octal
}

CString		GetAreaName(Coords3D* c)	
{
	return (GetAreaName(*c));
}
CString		GetAreaName(Coords3D& c)	
{
	return (_MsgBuffer.GetPlaceName(c));
}
CString		GetAreaName(ItemBase* i)	
{
	return (GetAreaName(i->World));
}
CString		GetAreaName(info_waypoint* w)	
{	//some scope for naming the target item if near
	char buff[20];
	int u;
	if (w->target != GOT_UNDEFINED_VAL)
	{
		return(GetTargName((UniqueID)w->target.Evaluate()));
	}
	else
	{
		return (GetAreaName(&w->World));
	}
	return buff;
}
CString		GetAreaName(EventVal* e)	
{	//some scope for naming the intercept items if near
	Coords3D c;
	e->EvalW(c);

	return (GetAreaName(c));
}

CString		GetAreaName(EventVal& e)
{	//should just call above function
	Coords3D c;
	e.EvalW(c);

	return (GetAreaName(c));
}
CString		GetTimeName(int time)
{
	CString	ctime;
 
	SWord hr, mins;
	Math_Lib.TimeFromSecs (time, hr, mins);
	ctime.Format("%02i:%02i",hr, mins);
	return(ctime);
}

CString		GetDateName(int date,DateFormat form,int time)
{	//Save_Data.dateorder
  	SWord	month = 0;
	SWord	day = 0,year = 0;
	CString	cdate;
    

							   
	Math_Lib.DateFromSecs (date,day,month,year);
	year += 1901;
	switch (form)
	{
	case DATE_SHORT:
		{
//DEADCODE RDH 15/06/99 			cdate.Format("%i/%i/%i",day,month+1,year - 1900);
			cdate.Format("%i/%i/%i",month+1,day,year - 1900);	//use US format //RDH 15/06/99
			return(cdate);
		}
	case DATE_LONG:
		{
			cdate.Format("%s %i, %i",RESLIST(JANUARY, month),day,year);
			return(cdate);
		}
	default:
	case DATE_PERIOD:
		return "12th of Never, afternoon";
	}
}

CString		GetShapeName(ShapeNum s)
{
	return	LoadResString(IDS_SHAPESSTART  + s);

}

CString		GetElementName(ShapeNum s,int elt)
{
	return GetShapeName(s)+" "+CString('a'+elt);

}
//			C		Dn	|	En		F
//						|				
//		B				|				G
//						|
//		Aw				|				He
//						|
//	--------------------+--------------------
//						|
//		Pw				|				Ie
//						|
//		O				|				J
//						|
//			N		Ms	|	Ls		K
//



CString		GetRelativeName(ItemBase* trg,Coords3D* src,bool exact,bool nametrg)
{
	int	diffX=src->X-trg->World.X;
	int	diffZ=src->Z-trg->World.Z;
	int posx=diffX;if(posx<0)posx=-posx;
	int posz=diffZ;if(posz<0)posz=-posz;
	if (posx>2*posz)								//AHIP
		if (diffX<0)
			return (RESSTRING(CARDINAL_W));			//AP
		else
			return (RESSTRING(CARDINAL_E));			//HI
	else
	if (posz>2*posx)								//DELM
		if (diffZ<0)
			return (RESSTRING(CARDINAL_S));			//LM
		else
			return (RESSTRING(CARDINAL_N_AGAIN));	//DE
	else
		if (diffX<0)								//BCNO
			if (diffZ<0)
				return (RESSTRING(CARDINAL_SW));	//NO
			else
				return (RESSTRING(CARDINAL_NW));	//BC
		else
			if (diffZ<0)							//FGJK
				return (RESSTRING(CARDINAL_SE));	//JK
			else
				return (RESSTRING(CARDINAL_NE));	//FG
}

CString  GetRelativeName(UniqueID u,COORDS3D *src,bool a,bool b)
{	return GetRelativeName(*Persons2::ConvertPtrUID(u),src,a,b);	}

CString  GetEltDeltaName(COORDS3D const &	coords)
{
	int	diffX=coords.X;
	int	diffZ=coords.Z;
	int posx=diffX;if(posx<0)posx=-posx;
	int posz=diffZ;if(posz<0)posz=-posz;
	if (posx>2*posz)
		if (diffX<0)
			return (RESSTRING(CARDINAL_W));
		else
			return (RESSTRING(CARDINAL_E));
	else
	if (posz>2*posx)
		if (diffZ<0)
			return (RESSTRING(CARDINAL_S));
		else
			return (RESSTRING(CARDINAL_N_AGAIN));
	else
		if (diffX<0)
			if (diffZ<0)
				return (RESSTRING(CARDINAL_SW));
			else
				return (RESSTRING(CARDINAL_SE));
		else
			if (diffZ<0)
				return (RESSTRING(CARDINAL_NW));
			else
				return (RESSTRING(CARDINAL_NE));

}


CString		CSprintf(const char* format,...)
{
	class	CS2:public CString
{
public:
	void FormatV(LPCTSTR lpszFormat, va_list argList)
	{CString::FormatV(lpszFormat,argList);}
};
	va_list v;
	va_start(v,format);
	CS2 rv;
	rv.FormatV(format,v);
	va_end(v);
	return rv;
}

CRect	Place(PosnControl px,PosnControl py,int x,int y,RDialog* parent)
{
	int x2=0,y2=0;
	switch (px)
	{
	case POSN_MIN:
	case POSN_CENTRE:
	case POSN_MAX:
		x2=-px;
		break;
	case POSN_ABS:
		break;
	case POSN_CALLER:
		{
		assert (parent);
		CRect parentpos;
		parent->GetWindowRect(parentpos);
		x+=parentpos.left;
		}
		break;
	}
	switch (py)
	{
	case POSN_MIN:
	case POSN_CENTRE:
	case POSN_MAX:
		y2=-py;
		break;
	case POSN_ABS:
		break;
	case POSN_CALLER:
		{
		assert (parent);
		CRect parentpos;
		parent->GetWindowRect(parentpos);
		y+=parentpos.top;
		}
		break;
	}
	return CRect(x,y,x2,y2);
}

char*	trunc(char* s,int l)
{
	while (strlen(s)>l && s[0]==' ')
	{
		char l;
		int ind=0;
		do{
			s[ind]=l=s[ind+1];ind++;
		}while(l);
	}
	if (strlen(s)>l)
	{
		s[l]=0;
	}

	return s;
}

CString	MakePilotName(PilotName& name)
{
	CString rv=RESSTRING(PILOTNAMES_START +name.nameref);
	if (name.initial1)
	{
		int index=rv.Find(' ');
		if (index!=-1)
			rv=rv.Mid(index);
		if (name.initial2)
			return CSprintf("%c.%c. %s",name.initial1,name.initial2,rv);
		else
			return CSprintf("%c. %s",name.initial1,rv);
	}
	else
		return rv;
}
