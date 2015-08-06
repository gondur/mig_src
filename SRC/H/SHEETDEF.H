#bollocks
#if !defined(SHEETDEFS_INCLUDED)
#define SHEETDEFS_INCLUDED

typedef void (*rvproc)(CWnd* P, CWnd* C,int retcode);

#endif

#define LaunchWindow(childname) \
static void rv1_##childname(CWnd* P, CWnd* C,int retcode); \
\
void currsheetname::On##childname() \
{ \
	/* Checks to see if window does not exist */\
	if (##childname.m_hWnd == NULL && C##childname::EXISTS==FALSE) \
	{ \
	/* if not create it */ \
		C##childname::EXISTS=TRUE; \
		##childname.Init(C##childname::IDD,this,rv1_##childname); \
	} \
	else if (##childname.m_hWnd != NULL) \
	/* if it exists and we have the handle to it set the focus to it */ \
		(##childname).SetFocus(); \
	/* if we dont have the handle to it but it exists then we cant focus it */\
	/* so do nothing */\
} \
\
static void rv2_##childname(CWnd* P, CWnd* C,int retcode); \
static void rv1_##childname(CWnd* P, CWnd* C,int retcode) \
{ \
	C##childname::EXISTS=FALSE; \
	rv2_##childname(P,C,retcode); \
	C->DestroyWindow(); \
} \
static void rv2_##childname(CWnd* P, CWnd* C,int retcode)

