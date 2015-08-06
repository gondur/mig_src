#if !defined(AFX_SQDNLIST_H__64D4AFA2_CE2F_11D1_A5A3_0040052179B6__INCLUDED_)
#define AFX_SQDNLIST_H__64D4AFA2_CE2F_11D1_A5A3_0040052179B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Sqdnlist.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSqdnlist dialog

class CSqdnlist : public RowanDialog
{
// Construction
public:
	CSqdnlist(int squadnum,CWnd* pParent = NULL);   // standard constructor
	static RDialog*	Make();

// Dialog Data
	//{{AFX_DATA(CSqdnlist)
	enum { IDD = IDD_SQDNLIST };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
	

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSqdnlist)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
//	CRStatic	m_IDC_TEXT_[6];
	CREdtBt		m_IDC_BUT_F[6];
	CREdtBt		m_IDC_BUT_E[2][6];
	CREdtBt		m_IDC_BUT_P[2][2][6];
// Implementation
protected:

	void CSqdnlist::PilotDetails(int pilot);
	void CSqdnlist::SwapPilot(int src,int dest);
	void CSqdnlist::SwapElement(int src, int dest);
	void CSqdnlist::SwapFlight(int src, int dest);
	void CSqdnlist::PrintPilotName(CREdtBt& m_slot,int slot, int pilot);
	BOOL CSqdnlist::SwapValid(int srcbtn, int destbutn);
	bool CSqdnlist::CommsPlayer(int pos, int& i);



	// Generated message map functions
	//{{AFX_MSG(CSqdnlist)
	virtual BOOL OnInitDialog();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	afx_msg	void OnClickedSqButtonID(int id);
	afx_msg	void OnCanAcceptDropSqbuttonID(int targid,long sourcedropID, BOOL FAR* pReply);
	afx_msg	void OnDroppedOnSqbuttonID(int targid,long sourcedropID); 

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SQDNLIST_H__64D4AFA2_CE2F_11D1_A5A3_0040052179B6__INCLUDED_)
