//------------------------------------------------------------------------------
//Filename       ceditor.h
//System         
//Author         Andrew McRae
//Date           Mon 10 Feb 1997
//Description    Curves Editor Header File
//------------------------------------------------------------------------------

#ifndef	CEDITOR_Included
#define	CEDITOR_Included

#define	DEFAULT_CEDITOR 0

#define CURVEPOINTCOLOR 0x0000ffl
#define CURVELINECOLOR 0xff0000l
#define INERTCURVEPOINTCOLOR 0xbbbbffl
#define INERTCURVELINECOLOR 0xffbbbbl
#define AXISCOLOR 0x000000l
#define FINEGRADCOLOR 0xccccccl
#define GRADCOLOR 0x999999l
#define WHITECOLOR 0xffffffl
#define LIMITCOLOR 0x00ff00l

#define FUNCNAMESIZE 16

typedef class EditorFunction {

public:

	ULong GoKey;
	ULong (*Func) (ULong); // actual function ptr

	char FuncName [FUNCNAMESIZE];

	EditorFunction (ULong (*) (ULong), ULong, char*);
	~EditorFunction ();
						  
	LINKEDLIST<EditorFunction> List;

} EDFUNC, *PEDFUNC;

ULong DoNothing (ULong) { return 0; }
ULong MovePoint (ULong);
ULong AddPoint (ULong);
ULong DeletePoint (ULong);
ULong Zoom (ULong);
ULong Centre (ULong);
ULong Snap2Grid (ULong);
//TempCode ARM 03Jun97 ULong DuplicateCl (ULong);

typedef class View {

public:

	HWND hWnd;

	POINT Org;	// Screen pos of (0,0,0) in World Coords
	FP Scalex;	// World units per logical pixel
	FP Scaley;	// World units per logical pixel

	FP MaxScalex,MaxScaley;

	RECT cRect;		// Client Rect Size

	View::View (HWND);

	void InitView (FP, FP, FP, FP);

	void GetLimits (FP&, FP&, FP&, FP&);

	POINT GetScreenPos (FP, FP);
	void GetWorldPos (POINT, FP&, FP&);

	void DrawPoint (FP, FP, DWORD);
	void DrawLine (FP, FP, FP, FP, DWORD);

	void DrawText (POINT, char*);


	Bool GetNearestPoint (PCURVE, POINT, ULong&);
	void CombinationCurve (ULong);

	ULong zoom (ULong);
	ULong centre (ULong);
	ULong snap2grid (ULong);

} VIEW, *PVIEW;

class Editor {

public:

	HWND hWnd;
	PVIEW pCurrView;
	PCURVE pCurrCurve;
	PCURVE pCurrCurve1;
	PCURVE pCurrCurve2;
	PEDFUNC pFuncs;

	ULong FuncCode;

	POINT MousePos;

	ULong ActiveCurve;

	Editor ()
	{
		pCurrView = NULL;
		pCurrCurve = NULL;
		pCurrCurve1 = NULL;
		pCurrCurve2 = NULL;
		pFuncs = NULL;

		ActiveCurve = 0;

	}
	~Editor ()
	{
		if (pCurrView != NULL) delete pCurrView;
		while (pFuncs != NULL) delete pFuncs;
	}

	Bool SetFuncCode (ULong);
	ULong (* Function ())(ULong);
	char* FuncName ();

	void ClearWindow ();
	void PrintFunctionName ();

	PCURVE GetActiveCurve ()
	{
		if (ActiveCurve == 1) return pCurrCurve;
		if (ActiveCurve == 2) return pCurrCurve1;
		if (ActiveCurve == 3) return pCurrCurve2;
		return NULL;
	}

	void SetCurrCurvePtr (PCURVE pCurve)
	{
		if (ActiveCurve == 1) pCurrCurve = pCurve;
		if (ActiveCurve == 2) pCurrCurve1 = pCurve;
		if (ActiveCurve == 3) pCurrCurve2 = pCurve;
	}

};

extern Editor _Editor;

class Main {

public:

	HWND hWnd;

	void QuitGame (); // winerror.cpp comp

};

extern Main _Main;

long FAR PASCAL _export WndProc (HWND hwnd, UINT message, UINT wParam, LONG lParam);

void PrintMousePos (PVIEW);

void WriteCurves (PCURVE, char*);
void WriteTypeCurves (char*);
FP Snap (FP, FP);
void Curves2Rads ();
void Curves2Degs ();
void Snap2MinRes ();
PCURVE NextCurve (PCURVE, Bool);

#endif


