#if !defined(AFX_RSPINBUTCTL_H__C3270E73_6D6B_11D1_A1F0_444553540000__INCLUDED_)
#define AFX_RSPINBUTCTL_H__C3270E73_6D6B_11D1_A1F0_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// RSpinButCtl.h : Declaration of the CRSpinButCtrl ActiveX Control class.
#include <afxtempl.h>
#include "dosdefs.h"
#include "files.g"

/////////////////////////////////////////////////////////////////////////////
// CRSpinButCtrl : See RSpinButCtl.cpp for implementation.

class CRSpinButCtrl : public COleControl
{
	DECLARE_DYNCREATE(CRSpinButCtrl)

// Constructor
public:
	CRSpinButCtrl();
	void DrawBitmap(FileNum filenum,CDC* pdc,int x,int y);
	void DrawTransparentBitmap(FileNum filenum,CDC * pDC, int x, int y);
private:
	enum {STATE_NORMAL = 0,
		  STATE_PRICE = 1,
		  STATE_VALUE = 2,
		  STATE_SEARCHVALUE = 3,
		  STATE_PLAYERNEG = 4} ;
	char* GetCurrentText(char*) ;
	void ResetStepSize() ; // newcode Woody
	void ValueToMoneyString(long value, char* buffer) ; // newcode Woody
	void StringToPassWord(char* String, char*	buffer);
	void FindSearchValue();
	char* StrEnd (char*	st ) ;
	char* StrTrimZeros(char* startbuffer) ;
	Bool	m_password;
	Bool	m_visible;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSpinButCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CRSpinButCtrl();
	BEGIN_OLEFACTORY(CRSpinButCtrl)        // Class factory and guid
		virtual BOOL VerifyUserLicense();
		virtual BOOL GetLicenseKey(DWORD, BSTR FAR*);
	END_OLEFACTORY(CRSpinButCtrl)

	DECLARE_OLETYPELIB(CRSpinButCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CRSpinButCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CRSpinButCtrl)		// Type name and misc status

// Message maps
public:
	afx_msg void OnTimer(UINT nIDEvent);
protected:
	//{{AFX_MSG(CRSpinButCtrl)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CRSpinButCtrl)
	afx_msg long GetRepeatDelay();
	afx_msg void SetRepeatDelay(long nNewValue);
	afx_msg long GetIndex();
	afx_msg void SetIndex(long nNewValue);
	afx_msg long GetFontNum();
	afx_msg void SetFontNum(long nNewValue);
	afx_msg long GetCurrentValue();
	afx_msg void SetCurrentValue(long nNewValue);
	afx_msg void AddString(LPCTSTR text);
	afx_msg void DeleteString(long index);
	afx_msg void Clear();
	afx_msg BOOL SetPriceOption(long min, long max, long current);
	afx_msg BOOL SetValueOption(long min, long max, long current);
	afx_msg void SetPassWord(BOOL ispassword);
	afx_msg BOOL SetSearchValueOption(long min, long max, long current);
	afx_msg BOOL SetPlayerNegPriceOption(long min, long max, long current);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

// Event maps
	//{{AFX_EVENT(CRSpinButCtrl)
	void FireTextChanged(LPCTSTR text)
		{FireEvent(eventidTextChanged,EVENT_PARAM(VTS_BSTR), text);}
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	long m_RepeatDelay;
	long m_index;
	UINT m_timerid;
	BOOL m_bGoingDown;
	BOOL m_bLButtonDown;
	BYTE m_SpinState;		//NewCode JW 01Dec98 
	long m_Min ;			//NewCode JW 01Dec98 
	long m_Max ;			//NewCode JW 01Dec98 
	long m_CurrentValue ;	//NewCode JW 01Dec98 
	long m_Delta ;//NewCode JW 01Dec98 
	static BOOL m_bDrawing;
	CList<char*,char*> m_list;
	long m_FontNum;
	enum {
	//{{AFX_DISP_ID(CRSpinButCtrl)
	dispidRepeatDelay = 1L,
	dispidIndex = 2L,
	dispidFontNum = 3L,
	dispidCurrentValue = 4L,
	dispidAddString = 5L,
	dispidDeleteString = 6L,
	dispidClear = 7L,
	dispidSetPriceOption = 8L,
	dispidSetValueOption = 9L,
	dispidSetPassWord = 10L,
	dispidSetSearchValueOption = 11L,
	dispidSetPlayerNegPriceOption = 12L,
	eventidTextChanged = 1L,
	//}}AFX_DISP_ID
	};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RSPINBUTCTL_H__C3270E73_6D6B_11D1_A1F0_444553540000__INCLUDED)
