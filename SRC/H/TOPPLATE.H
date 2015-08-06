//DEAD//
//DEAD// Extension to give nested dialogue qualities...
//DEAD//
//DEAD//
//DEAD//
//DEAD#pragma once
//DEAD#ifndef	TOPPLATE_H_hevfvbl
//DEAD#define TOPPLATE_H_hevfvbl
//DEADclass	RDialog;
//DEADtypedef RDialog * RDialogPtr;
//DEADstruct	HideEdgeControl
//DEAD{
//DEAD	enum	EdgeCtrl
//DEAD	{	
//DEAD		ALIGN_MIN=		0,		//align with parent top/left
//DEAD		ALIGN_MAX=		1,		//align with parent bot/right
//DEAD		ALIGN_SPLIT=	2,		//align with splitter bar in parent
//DEAD		ALIGN_STRETCH=	4,		//coordinate is a proportion of starting coordinate
//DEAD		ALIGN_MASK=		0x0f,	
//DEAD
//DEAD		OCCLUDE_SCROLL=		0x00,	//will add scroll bars if box is smaller than child
//DEAD		OCCLUDE_INSIDE=		0x10,	//parent may be smaller than child, but no scroll bars
//DEAD		OCCLUDE_EXACT=		0x20,	//parent should match size of child
//DEAD		OCCLUDE_OUTSIDE=	0x30,	//parent may make box containing child larger, but not smaller
//DEAD		OCCLUDE_MASK=		0xf0,
//DEAD
//DEAD		ACTIONS_ARTDIAL=	0x000,	//normal artwork and dialogue window - draggable with title line
//DEAD		ACTIONS_ARTCHILD=	0x100,	//artt and dialogue window as a child - dragging scrolls
//DEAD		ACTIONS_SPLITTER=	0x200,	//splitter window - screen full of subscreens
//DEAD		ACTIONS_TABBED=		0x400,	//tabbed dialogue window	- resize to subscreens
//DEAD		ACTIONS_MASK=		0xf00,
//DEAD	};
//DEAD};
//DEAD
//DEAD
//DEADclass Edges
//DEAD{
//DEADpublic:
//DEAD	typedef	HideEdgeControl::EdgeCtrl	Edge;
//DEAD	typedef	HideEdgeControl	EDGE;
//DEAD
//DEAD
//DEAD	Edge	l,t,r,b;
//DEAD
//DEAD	Edges	(Edge ll=EDGE::ALIGN_MIN,Edge tt=EDGE::ALIGN_MIN,Edge rr=EDGE::ALIGN_MIN,Edge bb=EDGE::ALIGN_MIN)
//DEAD	{l=ll;t=tt;r=rr;b=bb;}
//DEAD
//DEAD};
//DEAD
//DEADstruct	DialMake
//DEAD{
//DEAD	const	Edges* edges;
//DEAD	int	art;
//DEAD	enum	ChildType	{NONE,CLUMP,SPLITH,SPLITV,TABT,TABR}	childtype;
//DEADprotected:
//DEAD	DialMake(const Edges *e,int artnum)
//DEAD	{	art=artnum;childtype=NONE;edges=e;	}
//DEAD};
//DEADstruct DialBox:DialMake
//DEAD{
//DEAD	RDialog* dial;
//DEAD	const DialBox*	diallist[10];
//DEAD	DialBox(int artnum,RDialog*	newdial,Edges& e=*(Edges*)NULL):
//DEAD	DialMake(&e,artnum)
//DEAD	{dial=newdial;diallist[0]=NULL;}
//DEADprotected:
//DEAD	DialBox(DialBox& d):DialMake(d.edges,d.art){dial=d.dial;}
//DEAD};
//DEAD
//DEADstruct DialList:DialBox
//DEAD{
//DEAD
//DEAD	DialList(DialBox& d,const DialBox& d0,
//DEAD			const DialBox& d1=*(DialBox*)NULL,
//DEAD			const DialBox& d2=*(DialBox*)NULL,
//DEAD			const DialBox& d3=*(DialBox*)NULL,
//DEAD			const DialBox& d4=*(DialBox*)NULL,
//DEAD			const DialBox& d5=*(DialBox*)NULL,
//DEAD			const DialBox& d6=*(DialBox*)NULL,
//DEAD			const DialBox& d7=*(DialBox*)NULL):
//DEAD	DialBox(d)
//DEAD	{
//DEAD		diallist[0]=&d0;
//DEAD		diallist[1]=&d1;
//DEAD		diallist[2]=&d2;
//DEAD		diallist[3]=&d3;
//DEAD		diallist[4]=&d4;
//DEAD		diallist[5]=&d5;
//DEAD		diallist[6]=&d6;
//DEAD		diallist[7]=&d7;
//DEAD		diallist[8]=NULL;
//DEAD		diallist[9]=NULL;
//DEAD		childtype=CLUMP;
//DEAD	}
//DEAD};
//DEAD
//DEADstruct DialTab:DialList
//DEAD{
//DEAD	DialTab(DialBox& d,const DialBox& d0,
//DEAD			const DialBox& d1=*(DialBox*)NULL,
//DEAD			const DialBox& d2=*(DialBox*)NULL,
//DEAD			const DialBox& d3=*(DialBox*)NULL,
//DEAD			const DialBox& d4=*(DialBox*)NULL,
//DEAD			const DialBox& d5=*(DialBox*)NULL,
//DEAD			const DialBox& d6=*(DialBox*)NULL,
//DEAD			const DialBox& d7=*(DialBox*)NULL):
//DEAD	DialList(d,d0,d1,d2,d3,d4,d5,d6,d7)
//DEAD	{childtype=TABT;}
//DEAD};
//DEAD
//DEADstruct DialVTab:DialList
//DEAD{
//DEAD	DialVTab(DialBox& d,const DialBox& d0,
//DEAD			const DialBox& d1=*(DialBox*)NULL,
//DEAD			const DialBox& d2=*(DialBox*)NULL,
//DEAD			const DialBox& d3=*(DialBox*)NULL,
//DEAD			const DialBox& d4=*(DialBox*)NULL,
//DEAD			const DialBox& d5=*(DialBox*)NULL,
//DEAD			const DialBox& d6=*(DialBox*)NULL,
//DEAD			const DialBox& d7=*(DialBox*)NULL):
//DEAD	DialList(d,d0,d1,d2,d3,d4,d5,d6,d7)
//DEAD	{childtype=TABR;}
//DEAD};
//DEAD
//DEAD
//DEADclass	RDialog:public CDialog
//DEAD{
//DEAD	static	int actscrw,actscrh;
//DEAD	int		currscrw,currscrh;
//DEAD	CRect	homesize;
//DEAD	CRect	minsize;
//DEAD	CRect	maxsize;
//DEAD	CRect	viewsize;
//DEAD	typedef	HideEdgeControl::EdgeCtrl	Edge;
//DEAD	typedef	HideEdgeControl	EDGE;
//DEAD	Edges	edges;
//DEAD	CPoint	lastdown;
//DEAD	int		artnum;
//DEAD	enum	DragSide	{DRAG_NO=0,DRAG_INIT=-2,DRAG_DIALOG=-1,
//DEAD						DRAG_LEFT=1,DRAG_RIGHT=2,DRAG_TOP=4,DRAG_BOT=8,
//DEAD						DRAG_MOVE=16,DRAG_SCROLL=32}
//DEAD			dragstate;
//DEADprotected:
//DEAD	RDialogPtr	dchild,fchild,sibling,parent;	//if we have a formparent then we are a panel
//DEAD//	RDialogPtr	dialchild,dialsibling,dialparent;
//DEAD	int		dialparentindex;
//DEAD	typedef	void	dialinterface(int childindex,CDialog* child,CDialog* parent,int rv);
//DEAD
//DEADprotected:
//DEAD	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
//DEAD	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
//DEAD	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
//DEAD	afx_msg void OnNcPaint();
//DEAD	afx_msg void OnPaint();
//DEAD	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
//DEAD	afx_msg void OnNcLButtonDown(unsigned int,class CPoint p);
//DEAD//	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
//DEAD	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
//DEAD	afx_msg void OnMove(int x, int y);
//DEAD	afx_msg void OnSize(UINT nType, int cx, int cy);
//DEAD	virtual void PostNcDestroy();
//DEAD	int		ModScroll(UINT id,UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
//DEAD	bool	OnSizeAxis(int oldw,int neww,long& curr,Edge act);
//DEAD	void EndDialog( int nResult );
//DEAD	virtual void OnOK( );
//DEAD	virtual void OnCancel( );
//DEAD
//DEAD	DECLARE_MESSAGE_MAP()
//DEAD	protected:
//DEAD	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
//DEAD	const int MY_IID;
//DEADprotected:
//DEAD	RDialog(int i,CWnd* w);
//DEAD	BOOL	PreCreateWindow(CREATESTRUCT& cs);
//DEADprivate:
//DEAD	static CDialog*	MakeParentDialog(CRect& e,RDialog* parent,DialBox* tree);
//DEAD	void	AddChildren(const DialBox** list);
//DEADpublic:
//DEAD	static	CDialog*	MakeTopDialog(CRect& e,DialList& tree)	
//DEAD		{return MakeParentDialog(e,NULL,&tree);}
//DEAD	static	CDialog*	MakeTopDialog(CRect& e,DialBox& tree)	
//DEAD		{return MakeParentDialog(e,NULL,&tree);}
//DEAD	CDialog*	MakeDialog(CRect& e,DialList& tree) 
//DEAD		{return MakeParentDialog(e,this,&tree);}
//DEAD	CDialog*	MakeDialog(CRect& e,DialBox& tree) 
//DEAD		{return MakeParentDialog(e,this,&tree);}
//DEAD};
//DEAD
//DEADnamespace Rowan
//DEAD{
//DEAD
//DEADclass	CDialog;
//DEADtypedef	CDialog *CDialogPtr;
//DEADclass	CDialog:public RDialog
//DEAD{
//DEADprotected:
//DEAD	CDialog(int i,CWnd* w):RDialog(i,w){};
//DEAD};	//class
//DEAD
//DEAD};	//namespace
//DEAD
//DEADclass	RowanDialog:public Rowan::CDialog
//DEAD{
//DEADprotected:
//DEAD	RowanDialog(int i,CWnd* w): Rowan::CDialog(i,w){};
//DEAD};
//DEAD
//DEAD#endif
//DEAD