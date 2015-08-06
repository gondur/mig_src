#if !defined(AFX_RTESTSH1_H__67C77A87_A927_11D1_9B68_444553540000__INCLUDED_)
#define AFX_RTESTSH1_H__67C77A87_A927_11D1_9B68_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Rtestsh1.h : header file
//
#include "FlyInit.h"

/////////////////////////////////////////////////////////////////////////////
// Rtestsh1 dialog
class	Inst3d;
class	View3d;
class Rtestsh1 : public RowanDialog
{


// Construction
public:
	static	bool	tempblockkeys;
	static Inst3d*	tmpinst;//=NULL;
	static View3d*	tmpview;//=NULL;
	static int	setup3dstatus;
	static Rtestsh1* THISTHIS;
	enum	Setup3dStatuses	{S3D_STOPPED=0,S3D_STARTSETUP=1,S3D_DONESHEET=2,S3D_DONEBACK=4,S3D_NEED=3,S3D_GOING=8};
	bool wasrunning;
	bool	nestedcallsblocker;
	~Rtestsh1();
	Rtestsh1(CWnd* pParent = NULL,bool fIsRunning=false);   // standardish constructor
	Rtestsh1(UniqueID uid,CWnd* pParent = NULL,bool fIsRunning=false);   // standardish constructor
	PlaneTypeSelect m_actype;
	UniqueID trg_uid;
	void	Launch3d(bool);
	void	OnOK();
	void	OnCancel();
	static Setup3dStatuses Start3d(Setup3dStatuses);

// Dialog Data
	//{{AFX_DATA(Rtestsh1)
	enum { IDD = IDD_testch1 };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Rtestsh1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Rtestsh1)
	afx_msg void OnReplayPlayback();
	afx_msg void OnReplayRecord();
	afx_msg void OnComms();
	afx_msg void OnPaint();
	//}}AFX_MSG
	afx_msg void OnGetString();
	MSG2_0v(OnGetString);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RTESTSH1_H__67C77A87_A927_11D1_9B68_444553540000__INCLUDED_)
