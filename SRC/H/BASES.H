#if !defined(AFX_BASES_H__EF9ACC81_C4D6_11D1_A5A3_0040052179B6__INCLUDED_)
#define AFX_BASES_H__EF9ACC81_C4D6_11D1_A5A3_0040052179B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Bases.h : header file
//
#include "missman2.h"
int const ENTRYNOTUSED = -(SupplyTree::AIRFIELDSINWORLD + 1);		//defined in node.cpp as linked list!!!
int const DIALOGROWS = 23;		//combined airfields, gaps and squadrons cannot exceed this	
/////////////////////////////////////////////////////////////////////////////
// CBases dialog

class CBases : public RowanDialog
{
// Construction
public:
	CBases(CWnd* pParent = NULL);   // standard constructor
	
	int currleft, currtop, currright, currbottom; 
	int maxlines;
	int occupiedaf[PILOTABLE_SQUADRONS];	//PILOTABLE_SQUADRONS];
	int afuses[DIALOGROWS]; //-ve=(squad num. -1) +ve is af num  
// Dialog Data
	//{{AFX_DATA(CBases)
	enum { IDD = IDD_BASES };
		// NOTE: the ClassWizard will add data members here
	CREdtBt	m_IDC_AFBUTTON1;
	CRStatic	m_IDC_AFINFO1;
	CREdtBt	m_IDC_AFBUTTON2;
	CRStatic	m_IDC_AFINFO2;
	CREdtBt	m_IDC_AFBUTTON3;
	CRStatic	m_IDC_AFINFO3;
	CREdtBt	m_IDC_AFBUTTON4;
	CRStatic	m_IDC_AFINFO4;
	CREdtBt	m_IDC_AFBUTTON5;
	CRStatic	m_IDC_AFINFO5;
	CREdtBt	m_IDC_AFBUTTON6;
	CRStatic	m_IDC_AFINFO6;
	CREdtBt	m_IDC_AFBUTTON7;
	CRStatic	m_IDC_AFINFO7;
	CREdtBt	m_IDC_AFBUTTON8;
	CRStatic	m_IDC_AFINFO8;
	CREdtBt	m_IDC_AFBUTTON9;
	CRStatic	m_IDC_AFINFO9;
	CREdtBt	m_IDC_AFBUTTON10;
	CRStatic	m_IDC_AFINFO10;
	CREdtBt	m_IDC_AFBUTTON11;
	CRStatic	m_IDC_AFINFO11;
	CREdtBt	m_IDC_AFBUTTON12;
	CRStatic	m_IDC_AFINFO12;
	CREdtBt	m_IDC_AFBUTTON13;
	CRStatic	m_IDC_AFINFO13;
	CREdtBt	m_IDC_AFBUTTON14;
	CRStatic	m_IDC_AFINFO14;
	CREdtBt	m_IDC_AFBUTTON15;
	CRStatic	m_IDC_AFINFO15;
	CREdtBt	m_IDC_AFBUTTON16;
	CRStatic	m_IDC_AFINFO16;
	CREdtBt	m_IDC_AFBUTTON17;
	CRStatic	m_IDC_AFINFO17;
	CREdtBt	m_IDC_AFBUTTON18;
	CRStatic	m_IDC_AFINFO18;
	CREdtBt	m_IDC_AFBUTTON19;
	CRStatic	m_IDC_AFINFO19;
	CREdtBt	m_IDC_AFBUTTON20;
	CRStatic	m_IDC_AFINFO20;
	CREdtBt	m_IDC_AFBUTTON21;
	CRStatic	m_IDC_AFINFO21;
	CREdtBt	m_IDC_AFBUTTON22;
	CRStatic	m_IDC_AFINFO22;
	CREdtBt	m_IDC_AFBUTTON23;
	CRStatic	m_IDC_AFINFO23;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBases)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBases)
	virtual BOOL OnInitDialog();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	afx_msg void OnClickedAfButtonID(int ID);
	afx_msg void OnCanAcceptDropAfbuttonID(int ID,long sourcedropID, BOOL FAR* pReply);
	afx_msg void OnDroppedOnAfbuttonID(int ID,long sourcedropID);

	DECLARE_MESSAGE_MAP()
private:
	void OnClickedAfButton(int line);
	void PositionAfDisplay(int listindex);
	void PositionSquadDisplay(int listindex);

	BOOL CBases::AfInUse(int af);

	void CBases::FillOccupiedAf();
	void CBases::AddAirfield(int& listindex, int afnum);
	BOOL CBases::AirfieldValid(int afnum);
	void CBases::UpdateSquadronMovement(int srcline, int destline);
	void CBases::DisplaySquadronMovement(int listindex, int sqnum);
	void CBases::AddSquadron(int& listindex, int sqnum);
	int CBases::FindFreeSlots(int afnum);
	BOOL CBases::MoveValid(int& srcline, int& destline);
	void CBases::UpdateAirfieldDisplay(int listindex, int afnum);




};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BASES_H__EF9ACC81_C4D6_11D1_A5A3_0040052179B6__INCLUDED_)
