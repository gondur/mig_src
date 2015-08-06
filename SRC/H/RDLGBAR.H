////TEMPCODE DAW 07/05/99 #if !defined(AFX_RESIZABLEDLGBAR_H__5AF5D1E1_3653_11D1_A1F0_444553540000__INCLUDED_)
////TEMPCODE DAW 07/05/99 #define AFX_RESIZABLEDLGBAR_H__5AF5D1E1_3653_11D1_A1F0_444553540000__INCLUDED_
////TEMPCODE DAW 07/05/99 
////TEMPCODE DAW 07/05/99 #if _MSC_VER >= 1000
////TEMPCODE DAW 07/05/99 #pragma once
////TEMPCODE DAW 07/05/99 #endif // _MSC_VER >= 1000
////TEMPCODE DAW 07/05/99 // ResizableDlgBar.h : header file
////TEMPCODE DAW 07/05/99 //
////TEMPCODE DAW 07/05/99 class CMainFrame;
////TEMPCODE DAW 07/05/99 /////////////////////////////////////////////////////////////////////////////
////TEMPCODE DAW 07/05/99 // CResizableDlgBar window
////TEMPCODE DAW 07/05/99 class CResizableDlgBar : public CDialogBar
////TEMPCODE DAW 07/05/99 { 
////TEMPCODE DAW 07/05/99 // Construction
////TEMPCODE DAW 07/05/99 public: 
////TEMPCODE DAW 07/05/99 
////TEMPCODE DAW 07/05/99      BOOL Create( CWnd* pParentWnd, UINT nIDTemplate, UINT nStyle,
////TEMPCODE DAW 07/05/99                   UINT nID);
////TEMPCODE DAW 07/05/99      BOOL Create( CWnd* pParentWnd, LPCTSTR lpszTemplateName,
////TEMPCODE DAW 07/05/99                   UINT nStyle, UINT nID);
////TEMPCODE DAW 07/05/99 
////TEMPCODE DAW 07/05/99 // Attributes
////TEMPCODE DAW 07/05/99 public: 
////TEMPCODE DAW 07/05/99 	 
////TEMPCODE DAW 07/05/99 
////TEMPCODE DAW 07/05/99 // Operations
////TEMPCODE DAW 07/05/99 
////TEMPCODE DAW 07/05/99 
////TEMPCODE DAW 07/05/99 
////TEMPCODE DAW 07/05/99 public: 
////TEMPCODE DAW 07/05/99 
////TEMPCODE DAW 07/05/99 
////TEMPCODE DAW 07/05/99 
////TEMPCODE DAW 07/05/99 // Overrides
////TEMPCODE DAW 07/05/99     // ClassWizard generated virtual function overrides
////TEMPCODE DAW 07/05/99     //{{AFX_VIRTUAL(CResizableDlgBar)
////TEMPCODE DAW 07/05/99     //}}AFX_VIRTUAL
////TEMPCODE DAW 07/05/99     virtual CSize CalcDynamicLayout( int nLength, DWORD dwMode );
////TEMPCODE DAW 07/05/99 
////TEMPCODE DAW 07/05/99 // Implementation
////TEMPCODE DAW 07/05/99 
////TEMPCODE DAW 07/05/99 
////TEMPCODE DAW 07/05/99 
////TEMPCODE DAW 07/05/99 public: 
////TEMPCODE DAW 07/05/99 	int m_iAlign;
////TEMPCODE DAW 07/05/99 	CMainFrame* m_pParent;
////TEMPCODE DAW 07/05/99 	int m_iFixedWidth;
////TEMPCODE DAW 07/05/99 	int m_iFixedHeight;
////TEMPCODE DAW 07/05/99     int m_iBarLength;
////TEMPCODE DAW 07/05/99 	CPoint m_oldPoint;
////TEMPCODE DAW 07/05/99 	BOOL m_RButtonDown;
////TEMPCODE DAW 07/05/99 	BOOL m_bHorzAlign;
////TEMPCODE DAW 07/05/99 
////TEMPCODE DAW 07/05/99 // Generated message map functions
////TEMPCODE DAW 07/05/99 
////TEMPCODE DAW 07/05/99 
////TEMPCODE DAW 07/05/99 
////TEMPCODE DAW 07/05/99 protected: 
////TEMPCODE DAW 07/05/99 
////TEMPCODE DAW 07/05/99     //{{AFX_MSG(CResizableDlgBar)
////TEMPCODE DAW 07/05/99 	afx_msg void OnSize(UINT nType, int cx, int cy);
////TEMPCODE DAW 07/05/99 	afx_msg void OnPaint();
////TEMPCODE DAW 07/05/99 	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
////TEMPCODE DAW 07/05/99 	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
////TEMPCODE DAW 07/05/99 	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
////TEMPCODE DAW 07/05/99 	//}}AFX_MSG
////TEMPCODE DAW 07/05/99     DECLARE_MESSAGE_MAP()
////TEMPCODE DAW 07/05/99 
////TEMPCODE DAW 07/05/99 
////TEMPCODE DAW 07/05/99 
////TEMPCODE DAW 07/05/99 }; 
////TEMPCODE DAW 07/05/99 
////TEMPCODE DAW 07/05/99 /////////////////////////////////////////////////////////////////////////////
////TEMPCODE DAW 07/05/99 
////TEMPCODE DAW 07/05/99 //{{AFX_INSERT_LOCATION}}
////TEMPCODE DAW 07/05/99 // Microsoft Developer Studio will insert additional declarations immediately before the previous line.
////TEMPCODE DAW 07/05/99 
////TEMPCODE DAW 07/05/99 #endif // !defined(AFX_RESIZABLEDLGBAR_H__5AF5D1E1_3653_11D1_A1F0_444553540000__INCLUDED_)
////TEMPCODE DAW 07/05/99 