#if !defined(AFX_DAMAGE_H__FF688EC2_CA28_11D1_A5A3_0040052179B6__INCLUDED_)
#define AFX_DAMAGE_H__FF688EC2_CA28_11D1_A5A3_0040052179B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Damage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDamage dialog
struct	DamageDef;
class CDamage : public RowanDialog
{
// Construction
public:
	CDamage(int sgt,int uid,CWnd* pParent = NULL);   // standard constructor
	~CDamage();
// Dialog Data
	//{{AFX_DATA(CDamage)
	enum { IDD = IDD_DAMAGE };
		// NOTE: the ClassWizard will add data members here
	CRListBox	m_IDC_LIST_ELEMENTS;
	CRCombo	m_IDC_COMBO_ELEMENTS;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDamage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
	void		FillList();
protected:
	DamageDef	*damagedelements;
	int			numdamagedelts;
	enum		Mode	{M_DAMAGED,M_ALL,M_SPECIFIC}	mode;
	UniqueID	specificelt;
	int			specificeltdamage;
	ShapeNum	specificeltshape;

	// Generated message map functions
	//{{AFX_MSG(CDamage)
	afx_msg void OnTextChangedComboElements(LPCTSTR text);
	afx_msg void OnSelectListElements(long row, long column);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DAMAGE_H__FF688EC2_CA28_11D1_A5A3_0040052179B6__INCLUDED_)
