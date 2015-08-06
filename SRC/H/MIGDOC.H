// MIGDoc.h : interface of the CMIGDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MIGDOC_H__19CD38CB_A868_11D1_9B68_444553540000__INCLUDED_)
#define AFX_MIGDOC_H__19CD38CB_A868_11D1_9B68_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CMIGDoc : public COleDocument
{
protected: // create from serialization only
	CMIGDoc();
	DECLARE_DYNCREATE(CMIGDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMIGDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMIGDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMIGDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MIGDOC_H__19CD38CB_A868_11D1_9B68_444553540000__INCLUDED_)
