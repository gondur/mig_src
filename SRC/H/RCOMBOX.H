// RComboX.h: interface for the CRComboExtra class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RCOMBOX_H__E28400A1_FEC1_11D1_9FD6_D0EC00C10000__INCLUDED_)
#define AFX_RCOMBOX_H__E28400A1_FEC1_11D1_9FD6_D0EC00C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
#include	"UniqueID.h"
#include	"shapenum.g"
#include "RSpinBut.h"

//obviously, a number of these reference each other
class	ItemBase;
struct	info_waypoint;
struct	EventVal;

CString		GetTargName(UniqueID);//	{return "here, there,";}
CString		GetAreaName(Coords3D*);//	{return "here, coords3d*";}
CString		GetAreaName(Coords3D&);//	{return "here, coords3d&";}
CString		GetAreaName(ItemBase*);//	{return "here, item*";}
CString		GetAreaName(info_waypoint*);//	{return "here, wp*";}
CString		GetAreaName(EventVal*);//	{return "here, eventval*";}
CString		GetAreaName(EventVal&);//	{return "here, eventval&";}
CString		GetShapeName(ShapeNum s);
CString		GetElementName(ShapeNum s,int elt);
CString		GetEltDeltaName(const Coords3D& c);
CString		GetRelativeName(ItemBase* trg,Coords3D* src,bool exact=true,bool nametrg=false);
CString		GetRelativeName(UniqueID trg,Coords3D* src,bool exact=true,bool nametrg=false);


enum	DateFormat	{DATE_SHORT,DATE_LONG,DATE_PERIOD};
CString		GetDateName(int date,DateFormat form=DATE_SHORT,int time=0);
CString		GetTimeName(int time);

CString		CSprintf(const char* format,...);

enum	{TARGETFIELDWIDTH = 160};

class CRComboExtra : public CRCombo  
{
public:
	CRComboExtra();
	virtual ~CRComboExtra();
	CRComboExtra*	MakeNumList(int steps,int base=0,int stepsize=1);
	CRComboExtra*	SetList(int resstart,int rescount);
	CRComboExtra*	SetIndex(int index);
	int	GetIndex();
	CRComboExtra*	Clear();	
};

class CRSpinButExtra : public CRSpinBut
{
public:
	CRSpinButExtra();
	virtual ~CRSpinButExtra();
	CRSpinButExtra*	MakeNumList(int steps,int base=0,int stepsize=1);
	CRSpinButExtra*	SetList(int resstart,int rescount);
	CRSpinButExtra*	SetIndex(int index);
	int	GetIndex();
	CRSpinButExtra*	Clear();	
};

#define	RESCOMBO(start,count)	SetList(IDS_L_##start,count)

class	COleFont;
class	CPicture;
class	CRButton;
class	CRComboExtra;
class	CREdit;
class	CREditBt;
class	CREdtBt;
class	CRSpltBar;
class	CRTabs;
class	CRCombo;
class	CRTitle;
class	CRListBox;
class	CRRadio;
class	CRJoyCfg;
class	CRStatic;
class	CRSpinBut;

class DlgItem:public CWnd
{
public:
	operator COleFont*()	{return	(COleFont*)this;}
	operator CPicture*()	{return	(CPicture*)this;}
	operator CRButton*()	{return	(CRButton*)this;}
	operator CRComboExtra*(){return	(CRComboExtra*)this;}
	operator CREdit*()		{return	(CREdit*)this;}
	operator CREditBt*()	{return	(CREditBt*)this;}
	operator CREdtBt*()		{return	(CREdtBt*)this;}
	operator CRSpltBar*()	{return	(CRSpltBar*)this;}
	operator CRTabs*()		{return	(CRTabs*)this;}
	operator CRCombo*()		{return	(CRCombo*)this;}
	operator CRListBox*()	{return	(CRListBox*)this;}
	operator CRRadio*()		{return	(CRRadio*)this;}
	operator CRJoyCfg*()	{return	(CRJoyCfg*)this;}
	operator CRStatic*()	{return	(CRStatic*)this;}
	operator CRSpinBut*()	{return	(CRSpinBut*)this;}
//	operator *()		{return	(*)this;}
//	operator *()		{return	(*)this;}


};
char*	trunc(char* s,int l);

#endif // !defined(AFX_RCOMBOX_H__E28400A1_FEC1_11D1_9FD6_D0EC00C10000__INCLUDED_)
