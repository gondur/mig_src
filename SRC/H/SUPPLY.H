#if !defined(AFX_SUPPLY_H__7CC731A1_CA3D_11D1_A5A3_0040052179B6__INCLUDED_)
#define AFX_SUPPLY_H__7CC731A1_CA3D_11D1_A5A3_0040052179B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Supply.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSupply dialog

class CSupply : public RowanDialog
{
// Construction
public:
	CSupply(int index,CWnd* pParent = NULL);   // standard constructor
 	int sortindex;
	int currrow;

	int panel;
// Dialog Data
	//{{AFX_DATA(CSupply)
	enum { IDD = IDD_SUPPLY };
		// NOTE: the ClassWizard will add data members here
	CRStatic	m_IDC_RSTATICCTRL2;
	CRCombo	m_IDC_SORTCOMBO;
	CRListBox	m_IDC_RLISTBOXCTRL1;
	CRButton	m_IDC_AUTHORISE;
	CRButton	m_IDC_DOSSIER;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSupply)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
struct	Target
{
  	UniqueID	target;
	SupplyLine*	supplyline;
	int			capacity;
	int			activity;
	int			status;
};
enum	{MAX_TARGETS = 300};
Target target[MAX_TARGETS];
int	num_targets;

	void SortSupplyNodes();
	void AddSupplyMission(int j, SupplyNode*  currnode);
	void SortChokes();
	void SortTraffic();
	void SortAirfields();
	void SortArmy();
	void SortIntell();
	void ReDraw();
	void AddChokeMission(int j, SupplyRoute*  currroute);
	void AddArmyMission(int j, SupplyNode*  currnode);
	void AddAirfieldsMission(int j, int af, int score);
	void AddTrafficMission(int j, SupplyRoute*  currroute);
	void ReDrawButtons();



	// Generated message map functions
	//{{AFX_MSG(CSupply)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickedDossier();
	afx_msg void OnTextChangedSortcombo(LPCTSTR text);
	afx_msg void OnSelectRlistboxctrl1(long row, long column);
	afx_msg void OnClickedAuthorise();
	afx_msg void OnClose();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SUPPLY_H__7CC731A1_CA3D_11D1_A5A3_0040052179B6__INCLUDED_)
