// CntrItem.h : interface of the CMIGCntrItem class
//

#if !defined(AFX_CNTRITEM_H__19CD38D0_A868_11D1_9B68_444553540000__INCLUDED_)
#define AFX_CNTRITEM_H__19CD38D0_A868_11D1_9B68_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CMIGDoc;
class CMIGView;

class CMIGCntrItem : public COleClientItem
{
	DECLARE_SERIAL(CMIGCntrItem)

// Constructors
public:
	CMIGCntrItem(CMIGDoc* pContainer = NULL);
		// Note: pContainer is allowed to be NULL to enable IMPLEMENT_SERIALIZE.
		//  IMPLEMENT_SERIALIZE requires the class have a constructor with
		//  zero arguments.  Normally, OLE items are constructed with a
		//  non-NULL document pointer.

// Attributes
public:
	CMIGDoc* GetDocument()
		{ return (CMIGDoc*)COleClientItem::GetDocument(); }
	CMIGView* GetActiveView()
		{ return (CMIGView*)COleClientItem::GetActiveView(); }

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMIGCntrItem)
	public:
	virtual void OnChange(OLE_NOTIFICATION wNotification, DWORD dwParam);
	virtual void OnActivate();
	protected:
	virtual void OnGetItemPosition(CRect& rPosition);
	virtual void OnDeactivateUI(BOOL bUndoable);
	virtual BOOL OnChangeItemPosition(const CRect& rectPos);
	//}}AFX_VIRTUAL

// Implementation
public:
	~CMIGCntrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	virtual void Serialize(CArchive& ar);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CNTRITEM_H__19CD38D0_A868_11D1_9B68_444553540000__INCLUDED_)
