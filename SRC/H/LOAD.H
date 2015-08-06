#if !defined(AFX_LOAD_H__11348503_787F_11D2_9FD5_D0EC00C10000__INCLUDED_)
#define AFX_LOAD_H__11348503_787F_11D2_9FD5_D0EC00C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Load.h : header file
//
// The load panel handles load and save file name selection
//
//	CLoad(int dialresource,				//dialog layout
//	LSD_State initialstate,				//load/save/unselected
//	FileNum dirname,					//turned into pathname
//	CString wildcard,					//filename search string
//	CString& defaultandreturn,			//default filename and selected filename
//	LoadSaveDescriminate& loadsavediscriminator=loadsaveallowall,
//										//AllowFile() called for each selected file 
//		CWnd* pParent = NULL);			//std
//
//dialresource 
//	Allows extra text fields to be added and dialog to be resized.
//	LOAD must have:
//	CRButton	m_IDC_FILEOK;
//	CRListBox	m_IDC_RLISTBOXFILE;
//	CRStatic	m_IDC_LOADNAME;
//	SAVE must have:
//	CRButton	m_IDC_FILEOK;
//	CRListBox	m_IDC_RLISTBOXFILE;
//	CREdit		m_IDC_SAVENAME;
//initialstate
//	The active or only dialog panel should be	LSD_LOAD or LSD_SAVE 
//	Any other panel should be LSD_LOAD_DESELECT or LSD_SAVE_DESELECT
//loadsavediscriminator
//	This class can be subclassed to provide checking for priority and
//	legality.
//
//initialstate is stored into acnum
//dirname is stored in grpnum
//
//ACTIONS:
//	After specifying the above parameters, a text list is made of all matching
//	files. loadsavediscriminator.AllowFile() is called for each matching
//  wildcard and can be used to prioritise or disable each matching file.
//
//	If the panel is attatched to a tab, then when the tab is selected,
//	it will modify it's environment as follows:
//	1) Copy its current selection string to  defaultandreturn
//	2) Set all other panels to _DESELECT
//	3) Clear _DESELECT from it's own panel
//	It will modify it's grandparent as follows:
//	4) The grandparent probably owns defaultandreturn
//	5) Set acnum and grpnum to thius panels acnum and grpnum
//

/////////////////////////////////////////////////////////////////////////////
// CLoad dialog

class	LoadSaveDescriminate
{
public:
	enum	{MAXPRIORITY=10,NOLISTNOERROR=0,NOLISTERROR1=-1};
	virtual int	AllowFile(FileNum dirname,char* filename) const
	{return 1;}
	//0 means don't display
	//+ve is increasing priority to 10
	//-ve is error and don't display
};

enum	LSD_State	{LSD_LOAD,LSD_SAVE,LDS_DISABLE_SEP=4,LSD_LOAD_DESELECT=4,LSD_SAVE_DESELECT};

class CLoad : public RowanDialog
{
// Construction
public:
	static LoadSaveDescriminate	loadsaveallowall;
	CLoad(int dialresource,LSD_State initialstate,
		FileNum dirname,CString wildcard,CString& defaultandreturn,
		const LoadSaveDescriminate& loadsavediscriminator=loadsaveallowall,
		CWnd* pParent = NULL);   // standard constructor
//	CString	filename;
	FileNum	dirname;
	CString	wildcard;
	CString& filename;
	const	LoadSaveDescriminate& loadsavediscriminator;
	int currrow;
	bool	listempty;
// Dialog Data
	//{{AFX_DATA(CLoad)
	enum { IDD = IDD_LOAD };
		// NOTE: the ClassWizard will add data members here
	CRButton	m_IDC_FILEOK;
	CRListBox	m_IDC_RLISTBOXFILE;
	CRStatic	m_IDC_LOADNAME;
	CREdit		m_IDC_SAVENAME;
	CEdit		m_IDCX_SAVENAME;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLoad)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void PrintFileName();
	void MakeFileList();


	// Generated message map functions
	//{{AFX_MSG(CLoad)
	afx_msg void OnTextChangedSavename(LPTSTR text);
	afx_msg void OnReturnPressedSavename(LPCTSTR text);
	afx_msg void OnSelectRlistboxfile(long row, long column);
	virtual BOOL OnInitDialog();
	afx_msg void OnClickedFileok();
	afx_msg void OnUpdateSavename();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG

	afx_msg	void	OnSelectTab();
	MSG2(OnSelectTab)	{OnSelectTab();return 0;}

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOAD_H__11348503_787F_11D2_9FD5_D0EC00C10000__INCLUDED_)
