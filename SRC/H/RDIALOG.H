#if !defined(AFX_RDIALOG_H__19CD38F4_A868_11D1_9B68_444553540000__INCLUDED_)
#define AFX_RDIALOG_H__19CD38F4_A868_11D1_9B68_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// RDialog.h : header file
//
#include "globdefs.h"

//#define F_SOUNDS
#define F_BATTLE
//#define F_COMMON
#include "files.g"

enum	{MAXFONTS=14};
extern CFont* (g_AllFonts[][4]);
#define GETDLGITEM(name)	(&m_##name)
class	RDialog;
class   fileblock;
class	CMIGView;
class	RMdlDlg;
class	CHintBox;
class	CListBx;
class	CRScrlBar;
typedef RDialog * RDialogPtr;
enum	PosnControl	{POSN_ABS,POSN_MIN,POSN_CENTRE,POSN_MAX,POSN_CALLER};
CRect	Place(PosnControl px,PosnControl py,int x=0,int y=0,RDialog* parent=NULL);
struct	HideEdgeControl
{
	enum	EdgeCtrl
	{	
		ALIGN_MIN=		0,		//align with parent top/left
		ALIGN_MAX=		1,		//align with parent bot/right
		ALIGN_SPLIT=	2,		//align with splitter bar in parent
		ALIGN_STRETCH=	4,		//coordinate is a proportion of starting coordinate
		ALIGN_MASK=		0x0f,	

		OCCLUDE_SCROLL=		0x00,	//will add scroll bars if box is smaller than child
		OCCLUDE_INSIDE=		0x10,	//parent may be smaller than child, but no scroll bars
		OCCLUDE_EXACT=		0x20,	//parent should match size of child
		OCCLUDE_OUTSIDE=	0x40,	//parent may make box containing child larger, but not smaller
		OCCLUDE_MASK=		0xf0,

		ACTIONS_ARTDIAL=	0x000,	//normal artwork and dialogue window - draggable with title line
		ACTIONS_ARTCHILD=	0x100,	//artt and dialogue window as a child - dragging scrolls
									// now means that main window is a client window instead of a popup
		ACTIONS_SPLITTER=	0x200,	//splitter window - screen full of subscreens
		ACTIONS_TABBED=		0x400,	//tabbed dialogue window	- resize to subscreens
		ACTIONS_MASK=		0xf00,
	};
};
inline HideEdgeControl::EdgeCtrl operator | 
(HideEdgeControl::EdgeCtrl a,HideEdgeControl::EdgeCtrl b)
{return HideEdgeControl::EdgeCtrl(int(a)|int(b));}
inline HideEdgeControl::EdgeCtrl operator + 
(HideEdgeControl::EdgeCtrl a,HideEdgeControl::EdgeCtrl b)
{return (a|b);}

// some handy edge flag defines

#define EDGES_NOSCROLLBARS_NODRAGGING	Edges(EDGE::ACTIONS_ARTCHILD,	EDGE::ALIGN_MIN,EDGE::ALIGN_MIN + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MIN + EDGE::OCCLUDE_INSIDE)
#define EDGES_NOSCROLLBARS				Edges(EDGE::ALIGN_MIN,			EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE)
#define EDGES_ALIGN_MAX					Edges(EDGE::ALIGN_MIN,			EDGE::ALIGN_MIN,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX)
class Edges
{
public:
	typedef	HideEdgeControl::EdgeCtrl	Edge;
	typedef	HideEdgeControl	EDGE;


	Edge	l,t,r,b;

	Edges	(Edge ll=EDGE::ALIGN_MIN,Edge tt=EDGE::ALIGN_MIN,Edge rr=EDGE::ALIGN_MIN,Edge bb=EDGE::ALIGN_MIN)
	{l=ll;t=tt;r=rr;b=bb;}
};

struct	DialMake
{
	const	Edges* edges;
	FileNum	art;
	enum	ChildType	{NONE,CLUMP,SPLITH,SPLITV,TABT,TABR}	childtype;
protected:
	DialMake(const Edges *e,FileNum artnum)
	{	art=artnum;childtype=NONE;edges=e;	}
	DialMake()	{}

};

struct DialBox:DialMake
{
	RDialog*	dial;
	const	DialBox*	diallist[10];
	DialBox(FileNum artnum,RDialog*	newdial,const Edges& e=*(Edges*)NULL):
	DialMake(&e,artnum)
	{dial=newdial;diallist[0]=NULL;diallist[1]=(DialBox*)0x12345678;}
protected:
	DialBox(DialBox& d):DialMake(d.edges,d.art){dial=d.dial;}
	DialBox()	{dial=NULL; edges=NULL; art=FIL_NULL;}
};

struct DialList:DialBox
{
   
	DialList(DialBox& d,const DialBox& d0,
			const DialBox& d1=*(DialBox*)NULL,
			const DialBox& d2=*(DialBox*)NULL,
			const DialBox& d3=*(DialBox*)NULL,
			const DialBox& d4=*(DialBox*)NULL,
			const DialBox& d5=*(DialBox*)NULL,
			const DialBox& d6=*(DialBox*)NULL,
			const DialBox& d7=*(DialBox*)NULL):
	DialBox(d)
	{
		diallist[0]=&d0;
		diallist[1]=&d1;
		diallist[2]=&d2;
		diallist[3]=&d3;
		diallist[4]=&d4;
		diallist[5]=&d5;
		diallist[6]=&d6;
		diallist[7]=&d7;
		diallist[8]=NULL;
		diallist[9]=NULL;
		childtype=CLUMP;
	}
protected:
	DialList(const DialBox& d0,
			const DialBox& d1,
			const DialBox& d2,
			const DialBox& d3,
			const DialBox& d4,
			const DialBox& d5,
			const DialBox& d6,
			const DialBox& d7)
	{
		diallist[0]=&d0;
		diallist[1]=&d1;
		diallist[2]=&d2;
		diallist[3]=&d3;
		diallist[4]=&d4;
		diallist[5]=&d5;
		diallist[6]=&d6;
		diallist[7]=&d7;
		diallist[8]=NULL;
		diallist[9]=NULL;
		childtype=CLUMP;
	}
};


struct	IdEntry
{
	enum	IdType	{T_IDT,T_CHAR,T_GAP}
	idtype;
	union
	{
		const int textnum;
		const char* textstr;
	};
	IdEntry(const int i):	textnum(i)
					{if (i==0)
						{idtype=T_GAP;}
						{idtype=T_IDT;}
					}
	IdEntry(const char* s):	textnum(int(s))
			{idtype=T_CHAR;textstr=s;}

};
struct	IdList
{
	const IdEntry*	list[10];
	IdList(	const IdEntry& e0,
			const IdEntry& e1=*(IdEntry*)NULL,
			const IdEntry& e2=*(IdEntry*)NULL,
			const IdEntry& e3=*(IdEntry*)NULL,
			const IdEntry& e4=*(IdEntry*)NULL,
			const IdEntry& e5=*(IdEntry*)NULL,
			const IdEntry& e6=*(IdEntry*)NULL,
			const IdEntry& e7=*(IdEntry*)NULL,
			const IdEntry& e8=*(IdEntry*)NULL,
			const IdEntry& e9=*(IdEntry*)NULL)
	{
		list[0]=&e0;list[1]=&e1;list[2]=&e2;list[3]=&e3;list[4]=&e4;
		list[5]=&e5;list[6]=&e6;list[7]=&e7;list[8]=&e8;list[9]=&e9;
	}
};


struct HTabBox:DialList
{
	IdList* titles;
	HTabBox(FileNum artnum,IdList&idlist,Edges& e,
			const DialBox& d0,
			const DialBox& d1=*(DialBox*)NULL,
			const DialBox& d2=*(DialBox*)NULL,
			const DialBox& d3=*(DialBox*)NULL,
			const DialBox& d4=*(DialBox*)NULL,
			const DialBox& d5=*(DialBox*)NULL,
			const DialBox& d6=*(DialBox*)NULL,
			const DialBox& d7=*(DialBox*)NULL):
	DialList(d0,d1,d2,d3,d4,d5,d6,d7)
	{
		titles=&idlist;
		art=artnum;
		edges=&e;
		childtype=TABT;
	}
	HTabBox(FileNum artnum,Edges &e,
			const DialBox& d0,
			const DialBox& d1=*(DialBox*)NULL,
			const DialBox& d2=*(DialBox*)NULL,
			const DialBox& d3=*(DialBox*)NULL,
			const DialBox& d4=*(DialBox*)NULL,
			const DialBox& d5=*(DialBox*)NULL,
			const DialBox& d6=*(DialBox*)NULL,
			const DialBox& d7=*(DialBox*)NULL):
	DialList(d0,d1,d2,d3,d4,d5,d6,d7)
	{
		edges=&e;
		titles=NULL;
		art=artnum;
		childtype=TABT;
	}
};

struct VTabBox:HTabBox
{
	VTabBox(FileNum artnum,IdList&idlist,Edges &e,
			const DialBox& d0,
			const DialBox& d1=*(DialBox*)NULL,
			const DialBox& d2=*(DialBox*)NULL,
			const DialBox& d3=*(DialBox*)NULL,
			const DialBox& d4=*(DialBox*)NULL,
			const DialBox& d5=*(DialBox*)NULL,
			const DialBox& d6=*(DialBox*)NULL,
			const DialBox& d7=*(DialBox*)NULL):
	HTabBox(artnum,idlist,e,d0,d1,d2,d3,d4,d5,d6,d7)
	{childtype=TABR;}
	VTabBox(FileNum artnum,Edges &e,
			const DialBox& d0,
			const DialBox& d1=*(DialBox*)NULL,
			const DialBox& d2=*(DialBox*)NULL,
			const DialBox& d3=*(DialBox*)NULL,
			const DialBox& d4=*(DialBox*)NULL,
			const DialBox& d5=*(DialBox*)NULL,
			const DialBox& d6=*(DialBox*)NULL,
			const DialBox& d7=*(DialBox*)NULL):
	HTabBox(artnum,e,d0,d1,d2,d3,d4,d5,d6,d7)
	{childtype=TABR;}
};

const CRect RECT_MIN = CRect(0,0,50,20);
const CRect RECT_MAX = CRect(0,0,0x7FFF,0x7FFF);

inline	CString	LoadResString(int resnum)
{
	CString s;
	s.LoadString(resnum);
	return s;
};
#define	RESSTRING(name)	LoadResString(IDS_##name)
#define	RESLIST(name,val)	LoadResString(IDS_L_##name+val)
#define	 RESTABLESUM(wid,name,val)		IDS_L##wid##_##name+val*wid				  //RDH 23/03/99
#define	RESTABLE(wid,name,val)	LoadResString(IDS_L##wid##_##name+val*wid)
#define	RESCOL(wid,name,col,row)	LoadResString(IDS_L##wid##_##name##_##col+val*wid)
//#define	RESCOMBO(c,r,l)	FillCombo(c,IDS_L_##r,l)

//class	CRCombo;
class	RDialog;
class	CRToolBar;
//typedef	bool	(RDialog::*InterSheetProcZ)(RDialog*,int);
struct	DialogLinks
{
	enum	{MAX_CHILD_DIALS=16};
	RDialog*	*loggedchild;			//Other dialogs launched by this dialog
	RDialog*	*loggedchildlauncher;	//The pane on this dialog that launched
	CRToolBar	*loggedparenttool;	
	RDialog*	loggedparent;			//The dialog that launched this dialog
	RDialog*	loggedparentlauncher;	//The pane of this dialog that wants ParentClosed message. 
	DialogLinks()	{loggedchild=loggedchildlauncher=NULL;loggedparent=loggedparentlauncher=NULL;loggedparenttool=NULL;}
};


class RDialog: public CDialog
{

// Construction
//	DECLARE_DYNAMIC( RDialog )
public:

// Dialog Data
	//{{AFX_DATA(RDialog)
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
 	typedef	HideEdgeControl::EdgeCtrl	Edge;
	typedef	HideEdgeControl	EDGE;
	static	int actscrw,actscrh,borderwidth,fontdpi;
	static RDialog* skip;
	static CMIGView* m_pView;
	int		currscrw,currscrh;
	const int MY_IID;
	float m_scalingfactor;

	// scrollbars stuff

//	CRScrlBar m_rVertScrollBar;
//	CRScrlBar m_rHorzScrollBar;

	// system buttons and graphics
	// note these are quite small until they are created
	// which only occurs on the main parent dialog.
	static bool m_moving;
	BOOL m_ReallyDestroyed;
	fileblock* m_pfileblock;

	LPCTSTR cursor;
	BOOL m_bChangeCursor;
	BOOL m_bDrawBackground;
	CRScrlBar* m_pVertScrollBar;
	CRScrlBar* m_pHorzScrollBar;
	CRect	homesize;
	CRect	viewsize;
	CRect	viewsize2;
	CRect	maxsize;
	CRect	minsize;
	Edges	edges;
	CPoint	lastdown;
	FileNum	artnum;
	enum	DragSide	{DRAG_NO=0,DRAG_INIT=-2,DRAG_DIALOG=-1,
						DRAG_LEFT=1,DRAG_RIGHT=2,DRAG_TOP=4,DRAG_BOT=8,
						DRAG_MOVE=16,DRAG_SCROLL=32,DRAG_SHUTDOWN=64}
			dragstate;

	RDialogPtr	dchild,fchild,sibling,parent;	//if we have a formparent then we are a panel
//	RDialogPtr	dialchild,dialsibling,dialparent;

	//supposed to be the inter-sheet pseudo-modal interface
//	int		dialparentindex;
//	typedef	void	dialinterface(int childindex,CDialog* child,CDialog* parent,int rv);
//	InterSheetProcZ	NotifyClosedProc;RDialog* NotifyClosedSheet;
//	RDialog*	SetNotifyClosed(InterSheetProcZ i,RDialog* t);
//#define	SETNOTIFYCLOSED(p)	SetNotifyClosed(InterSheetProcZ(p),this)


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(RDialog)
	public:
	virtual int DoModal();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	RDialog(int i,CWnd* w);
	bool	OnSizeAxis(int oldw,int neww,long& curr,Edge act);
	CRect	Place(PosnControl px,PosnControl py,int x=0,int y=0)
	{	return	::Place(px,py,x,y,this);	}
public:
	virtual void	EndDialog( int nResult );
	virtual void	PreDestroyPanel();
	void	OnOK( );
	void	OnCancel( );
	void	DDX_Control(CDataExchange* pDX,int	dialid,CWnd&	m_dial);		

	DialogLinks	dialoglinks;
	int		LogChild(RDialog*);	//new system for managing intersheet comms
	bool	LogChild(int,RDialog*);	//as Dallas never implemented one!
	int		LoggedChild();
	RDialog*	LoggedChild(int);
	bool	CloseLoggedChild(int);	  //true means still open!!!
	void	CloseLoggedChildren(RDialog* skipthis=NULL);
	void	DialExitFix(int rv);
	void	RefreshChild(int rv);
	void	RefreshParent();
	virtual void ChildDialClosed(int dialnum,RDialog*,int rv);
	virtual void ParentDialClosed(RDialog*,int rv);
	virtual void RefreshData(int childnum);
	void	MakeChildrenVisible(bool);
private:
	
	int		ModScroll(UINT id,UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	static RDialog*	MakeParentDialog(CRect& e,RDialog* parent,DialBox* tree);
	RDialog*	AddChildren(const DialBox*const* diallist,int X2flag=0,CRect& rect=*(CRect*)NULL);
	void	AddChildren(const DialBox*const* diallist,DialMake::ChildType childtype,const IdList* titles);
public:
	static int RMessageBox(UINT TitleID, UINT MessageID, UINT Button0ID=NULL,UINT Button1ID=NULL, UINT Button2ID=NULL, FileNum art=FIL_NULL);
	static RMdlDlg* m_pMessageBox;
	static CHintBox* m_pHintBox;
	static CListBx* m_pListBox;
	CRect	RelCoords(const CRect& delta)	{return delta;}
	CRect	RelCoords(int x,int y,int x2=0,int y2=0)	{return CRect(x,y,x2,y2);}
	void ScaleDialog(float factor);
	static int GetFontScaling();
	void DestroyPanel();
	RDialog* AddPanel(RDialog* dial,int X2flag,CRect rect,FileNum artnum=FIL_NULL, const Edges& e=Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX));
	RDialog* AddPanel(const DialBox* diallist,int X2flag,CRect rect);
	void UpdateTitle();
	RDialog* InDialAncestor()	
	{
		if (parent)// && dragstate!=DRAG_DIALOG && dragstate!=DRAG_INIT)
			return parent->InDialAncestor();
		else
			return this;
	}
	CRect	RECT_NORMAL;
	void SetMaxSize(CRect rect);
	void SetMinSize(CRect rect);
	void AttachTabToTabControl(const struct IdEntry *const list);
	void AttachRelevantSplitterBars();
//	void InitArtwork(FileNum art);
	static	RDialog*	MakeTopDialog(CRect& e,DialList& tree)	
		{return MakeParentDialog(e,NULL,&tree);}
	static	RDialog*	MakeTopDialog(CRect& e,DialBox& tree)	
		{return MakeParentDialog(e,NULL,&tree);}
	RDialog*	MakeDialog(CRect& e,DialList& tree) 
		{return MakeParentDialog(e,this,&tree);}
	RDialog*	MakeDialog(CRect& e,DialBox& tree) 
		{return MakeParentDialog(e,this,&tree);}
	// Generated message map functions
public:
	afx_msg static void OnPlaySound(int filenum);
protected:
	//{{AFX_MSG(RDialog)
//	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
//	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	afx_msg void OnMove(int x, int y);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnNcMouseMove(UINT nHitTest, CPoint point);
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnDestroy();
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	afx_msg LRESULT OnRegisteredMouseWheel( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnCommandHelp(WPARAM, LPARAM lParam);
	afx_msg FileNum OnGetArt();
	afx_msg long OnGetXYOffset();
	afx_msg CFont* OnGetGlobalFont(int fontnum);
	afx_msg BYTE* OnGetFile(int filenum);
	afx_msg void OnReleaseLastFile();
	afx_msg BOOL OnGetX2Flag();
	afx_msg CDC* OnGetOffScreenDC();
	afx_msg CHintBox* OnGetHintBox();
	afx_msg CListBx* OnGetComboDialog();
	afx_msg CRListBox* OnGetComboListbox();
	afx_msg void OnActiveXScroll(int scrollpos, BOOL horzalign);
	afx_msg int OnGetString(int resourceID,char* workbuffer);
	MSG2(OnGetString)	{return OnGetString(a,(char*)b);}
	MSG2_0(OnGetArt);
	MSG2_0(OnGetXYOffset);
	MSG2_1(OnGetGlobalFont);
	MSG2_1(OnGetFile);
	MSG2_0v(OnReleaseLastFile);
	MSG2_0(OnGetX2Flag);
	MSG2_0(OnGetOffScreenDC);
	MSG2_0(OnGetHintBox);
	MSG2_1v(OnPlaySound);
	MSG2_0(OnGetComboListbox);
	MSG2_0(OnGetComboDialog);
	MSG2_2v(OnActiveXScroll);
	MSG2_2(OnCommandHelp);

	DECLARE_MESSAGE_MAP()
};

//namespace Rowan
struct	Rowan
{

class	CDialog;
typedef	CDialog *CDialogPtr;
class	CDialog:public RDialog
{
protected:
	CDialog(int i,CWnd* w):RDialog(i,w){};
};	//class

};	//namespace
class	CRComboExtra;
class	CRSpinButExtra;
class	DlgItem;
class	RFullPanelDial;
inline RFullPanelDial*	GetFullPanel(CMIGView* view);
class	RowanDialog:public Rowan::CDialog
{
private:
//	SetNotifyClosed();
protected:
	RowanDialog(int i,CWnd* w): Rowan::CDialog(i,w){SetProjSpecific();}
//EXTRA FIELDS USED BY MOST DIALOGS BUT PROJECT SPECIFIC
//In football this may be team number and player number
public:
	int		packnum;		//package
	int		wavenum;		//wave in package
	int		groupnum;		//group in wave
	int		acnum;			//ac/fl/elt leader in group
//protected:
	void	SetProjSpecific(int pack=-1,int wave=-1,int group=-1,int ac=-1)
	{packnum=pack;wavenum=wave;groupnum=group;acnum=ac;}

	typedef	CRComboExtra	CRCombo,*CRComboPtr;
	typedef	CRSpinButExtra	CRSpinBut,*CRSpinButPtr;
	DlgItem&	GetDlgItem(int ID)	{return *(DlgItem*)CDialog::GetDlgItem(ID);}
	RFullPanelDial* FullPanel()	{ASSERT(GetFullPanel(m_pView));return GetFullPanel(m_pView);}
	//
};

#define	RowanClass(name)	\
	class	name:public	RowanDialog

#define	RowanCon(name)				\
	RDialog*	Make##name(CWnd* w)  \
	{return	new name(w);}			  \
	name::name(CWnd* w):			   \
		RowanDialog(name::IDD,w)

		
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RDIALOG_H__19CD38F4_A868_11D1_9B68_444553540000__INCLUDED_)
