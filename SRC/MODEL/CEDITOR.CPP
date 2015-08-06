/*
	 MiG Alley
	 Copyright (C) 1998, 1999, 2000, 2001 Empire Interactive (Europe) Ltd,
	 677 High Road, North Finchley, London N12 0DA

	 Please see the document licence.doc for the full licence agreement

2. LICENCE
 2.1 	
 	Subject to the provisions of this Agreement we now grant to you the 
 	following rights in respect of the Source Code:
  2.1.1 
  	the non-exclusive right to Exploit  the Source Code and Executable 
  	Code on any medium; and 
  2.1.2 
  	the non-exclusive right to create and distribute Derivative Works.
 2.2 	
 	Subject to the provisions of this Agreement we now grant you the
	following rights in respect of the Object Code:
  2.2.1 
	the non-exclusive right to Exploit the Object Code on the same
	terms and conditions set out in clause 3, provided that any
	distribution is done so on the terms of this Agreement and is
	accompanied by the Source Code and Executable Code (as
	applicable).

3. GENERAL OBLIGATIONS
 3.1 
 	In consideration of the licence granted in clause 2.1 you now agree:
  3.1.1 
	that when you distribute the Source Code or Executable Code or
	any Derivative Works to Recipients you will also include the
	terms of this Agreement;
  3.1.2 
	that when you make the Source Code, Executable Code or any
	Derivative Works ("Materials") available to download, you will
	ensure that Recipients must accept the terms of this Agreement
	before being allowed to download such Materials;
  3.1.3 
	that by Exploiting the Source Code or Executable Code you may
	not impose any further restrictions on a Recipient's subsequent
	Exploitation of the Source Code or Executable Code other than
	those contained in the terms and conditions of this Agreement;
  3.1.4 
	not (and not to allow any third party) to profit or make any
	charge for the Source Code, or Executable Code, any
	Exploitation of the Source Code or Executable Code, or for any
	Derivative Works;
  3.1.5 
	not to place any restrictions on the operability of the Source 
	Code;
  3.1.6 
	to attach prominent notices to any Derivative Works stating
	that you have changed the Source Code or Executable Code and to
	include the details anddate of such change; and
  3.1.7 
  	not to Exploit the Source Code or Executable Code otherwise than
	as expressly permitted by  this Agreement.

questions about this file may be asked at http://www.simhq.com/
*/

//------------------------------------------------------------------------------
//Filename       ceditor.cpp
//System         
//Author         Andrew McRae
//Date           Mon 10 Feb 1997
//Description    Flight Model Curve Editor
//------------------------------------------------------------------------------


#define WIN32_LEAN_AND_MEAN

#include "dosdefs.h"

#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <c:\Program Files\DevStudio\Vc\include\math.h>
//DeadCode JIM 02Apr98 #include <c:\watcom\h\math.h>

//#include "myworldinc.h"
#include "modvec.h"

#define CURVEEDITOR
#include "curves.h"
#include "ceditor.h"
#define CEDITOR
#include "myerror.h"

Main _Main;
Editor _Editor;

int WINAPI WinMain (HANDLE hInstance, HANDLE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{

	static char szAppName[] = "Editor" ;
	MSG         msg ;
	WNDCLASS    wndclass ;

	if (!hPrevInstance) {
		wndclass.style			= CS_HREDRAW | CS_VREDRAW ;
		wndclass.lpfnWndProc   	= WndProc ;
		wndclass.cbClsExtra    	= 0 ;
		wndclass.cbWndExtra    	= 0 ;
		wndclass.hInstance     	= hInstance ;
		wndclass.hIcon         	= LoadIcon (NULL, IDI_APPLICATION) ;
		wndclass.hCursor       	= LoadCursor (NULL, IDC_CROSS) ;
		wndclass.hbrBackground 	= GetStockObject (WHITE_BRUSH) ;
		wndclass.lpszMenuName  	= szAppName;
		wndclass.lpszClassName 	= szAppName ;

		RegisterClass (&wndclass) ;
	}

	_Main.hWnd = CreateWindow (szAppName, // window class name
			"Curve Editor",			// window caption
			WS_OVERLAPPEDWINDOW,	// window style
			0,						// initial x position
			0,						// initial y position
			GetSystemMetrics (SM_CXSCREEN),
			GetSystemMetrics (SM_CYSCREEN),
			NULL,			// parent window handle
			NULL,			// window menu handle
			hInstance,		// program instance handle
			NULL);			// creation parameters

	_Editor.hWnd = _Main.hWnd;
	_Editor.pCurrView = new VIEW (_Main.hWnd);

	new EDFUNC (MovePoint, 'M', "MovePoint");
	new EDFUNC (AddPoint, 'A', "AddPoint");
	new EDFUNC (DeletePoint, 'D', "DeletePoint");
	new EDFUNC (Zoom, 'Z', "Zoom");
	new EDFUNC (Centre, 'X', "Centre");
	new EDFUNC (Snap2Grid, 'G', "Snap2Grid");
//TempCode ARM 03Jun97 	new EDFUNC (DuplicateCl, 'C', "DuplicateCl");

	Curves2Degs ();

	_Editor.pCurrCurve = _CurveRsc.pCurves;
	_Editor.ActiveCurve = 1;

	if (_Editor.pCurrCurve != NULL)
	{
		FP x1,x2,y1,y2;
		_Editor.pCurrCurve->CalcCurveLimitsAll (x1,x2,y1,y2);
		_Editor.pCurrView->InitView(x1,x2,y1,y2);
	}

	ShowWindow (_Main.hWnd, nCmdShow) ;
	UpdateWindow (_Main.hWnd) ;

	while (GetMessage (&msg, NULL, 0, 0)) {
		TranslateMessage (&msg) ;
		DispatchMessage (&msg) ;
	}

	lpszCmdParam = lpszCmdParam;

	return msg.wParam ;

}

long FAR PASCAL _export WndProc (HWND hWnd, UINT message, UINT wParam, LONG lParam)
{

	FP x1,x2,y1,y2;
	PCURVE pCurve;
	ULong Comb;

	Comb = 0;

	switch (message)
	{

	case WM_CREATE:
		return 0;

	case WM_ACTIVATE:
		return 0;

	case WM_DESTROY:
		PostQuitMessage (0) ;
		return 0 ;

//      case WM_COMMAND:
//	     	switch (wParam)
//			{
//         }
//         break;

	case WM_KEYDOWN:

		if (_Editor.SetFuncCode (wParam))
			_Editor.PrintFunctionName ();

		switch (wParam)
		{

		case VK_ESCAPE:
			DestroyWindow (hWnd);
			break;

		case 'S':
			WriteCurves (_CurveRsc.pCurves, "model\\cdat.cpp");
			break;

		case 'N':

			pCurve = _Editor.GetActiveCurve ();

			if (pCurve != NULL)
			{
				pCurve = NextCurve (_CurveRsc.pCurves, (Bool)FALSE);

				_Editor.SetCurrCurvePtr (pCurve);

				_Editor.ClearWindow ();

				pCurve->CalcCurveLimitsAll (x1,x2,y1,y2);
				_Editor.pCurrView->InitView(x1,x2,y1,y2);
			}


			break;

		case 'B':

			pCurve = _Editor.GetActiveCurve ();

			if (pCurve != NULL)
			{

				pCurve = NextCurve (_CurveRsc.pCurves, (Bool)TRUE);

				_Editor.ClearWindow ();

				_Editor.SetCurrCurvePtr (pCurve);

				pCurve->CalcCurveLimitsAll (x1,x2,y1,y2);
				_Editor.pCurrView->InitView(x1,x2,y1,y2);
			}


			break;

		case 'K':

			for (;;)
			{

				_Editor.ActiveCurve++;

				if (_Editor.ActiveCurve == 4)
					_Editor.ActiveCurve = 1;

				if (_Editor.GetActiveCurve () != NULL)
					break;
			}

			_Editor.ClearWindow ();

			break;

		case 'O':


			if (_Editor.ActiveCurve == 2)
				_Editor.pCurrCurve1 = NULL;

			if (_Editor.ActiveCurve == 3)
				_Editor.pCurrCurve2 = NULL;

			_Editor.ActiveCurve = 1;

			_Editor.ClearWindow ();

			pCurve = _Editor.GetActiveCurve ();
			pCurve->CalcCurveLimitsAll (x1,x2,y1,y2);
			_Editor.pCurrView->InitView(x1,x2,y1,y2);

			break;

		case 'H':

			if (_Editor.pCurrCurve1 == NULL)
			{
				_Editor.pCurrCurve1 = NextCurve (_CurveRsc.pCurves, (Bool)FALSE);
				_Editor.ActiveCurve = 2;
			}

			else if (_Editor.pCurrCurve2 == NULL)
			{
				_Editor.pCurrCurve2 = NextCurve (_CurveRsc.pCurves, (Bool)FALSE);
				_Editor.ActiveCurve = 3;
			}
			else
				break;

			_Editor.ClearWindow ();

			pCurve = _Editor.GetActiveCurve ();
			pCurve->CalcCurveLimitsAll (x1,x2,y1,y2);
			_Editor.pCurrView->InitView(x1,x2,y1,y2);

			break;

		case 'R':

			_Editor.ClearWindow ();

			pCurve = _Editor.GetActiveCurve ();
			if (pCurve != NULL)
			{
				pCurve->CalcCurveLimitsAll (x1,x2,y1,y2);
				_Editor.pCurrView->InitView(x1,x2,y1,y2);
			}

			break;

		case 'C':

			// Duplicate Cl Curve
			_Editor.GetActiveCurve ()-> DuplicateCl (0);

			break;

		case 'T':
			_Editor.ClearWindow ();
			break;

		case VK_NUMPAD4:
			Comb |= 0x11;	// 1st +
			break;

		case VK_NUMPAD5:
			Comb |= 0x12;	// 1st -
			break;

		case VK_NUMPAD1:
			Comb |= 0x24;	// 2nd +
			break;

		case VK_NUMPAD2:
			Comb |= 0x28;	// 2nd -
			break;

		case VK_NUMPAD7:
			Comb |= 0x35;	// 1st & 2nd +
			break;

		case VK_NUMPAD8:
			Comb |= 0x3a;	// 1st & 2nd -
			break;

		case VK_NUMPAD9:
			Comb |= 0x39;	// 1st + 2nd -
			break;

		case VK_NUMPAD6:
			Comb |= 0x36;	// 1st - 2nd +
			break;

  		}

		if (Comb)
		{
			// draw combination curve
			if (_Editor.pCurrView != NULL)
				_Editor.pCurrView->CombinationCurve (Comb);
		}

//		if (Comb) 
//			_Editor.ClearWindow ();

  		return 0;

	case WM_LBUTTONDOWN:
		_Editor.Function () (WM_LBUTTONDOWN);
		return 0;

	case WM_RBUTTONDOWN:
		_Editor.Function () (WM_RBUTTONDOWN);
         return 0;

	case WM_LBUTTONUP:
		_Editor.Function () (WM_LBUTTONUP);
		return 0;

	case WM_RBUTTONUP:
		_Editor.Function () (WM_RBUTTONUP);
		return 0;

	case WM_MOUSEMOVE:
		_Editor.MousePos.x = LOWORD(lParam);
		_Editor.MousePos.y = HIWORD(lParam);

		PrintMousePos (_Editor.pCurrView);

		_Editor.Function () (WM_MOUSEMOVE);
        return 0;

	case WM_PAINT:

		_Editor.PrintFunctionName ();

		PrintMousePos (_Editor.pCurrView);

		// curve names
		HDC hdc = GetDC (_Editor.pCurrView->hWnd);

		if (_Editor.pCurrCurve != NULL)
		{
			TextOut (hdc, 5, 5, _Editor.pCurrCurve->AircraftName, strlen(_Editor.pCurrCurve->AircraftName));
			TextOut (hdc, 5, 20, _Editor.pCurrCurve->CurveName, strlen(_Editor.pCurrCurve->CurveName));

			if (_Editor.ActiveCurve == 1)
				TextOut (hdc, 5, 35, "Active", 6);
			else
				TextOut (hdc, 5, 35, "Inert", 5);
		}
		else
			TextOut (hdc, 5, 5, "Empty", 5);

		if (_Editor.pCurrCurve1 != NULL)
		{
			TextOut (hdc, 5, 105, _Editor.pCurrCurve1->AircraftName, strlen(_Editor.pCurrCurve1->AircraftName));
			TextOut (hdc, 5, 120, _Editor.pCurrCurve1->CurveName, strlen(_Editor.pCurrCurve1->CurveName));

			if (_Editor.ActiveCurve == 2)
				TextOut (hdc, 5, 135, "Active", 6);
			else
				TextOut (hdc, 5, 135, "Inert", 5);
		}
		else
			TextOut (hdc, 5, 105, "Empty", 5);


		if (_Editor.pCurrCurve2 != NULL)
		{
			TextOut (hdc, 5, 205, _Editor.pCurrCurve2->AircraftName, strlen(_Editor.pCurrCurve2->AircraftName));
			TextOut (hdc, 5, 220, _Editor.pCurrCurve2->CurveName, strlen(_Editor.pCurrCurve2->CurveName));

			if (_Editor.ActiveCurve == 3)
				TextOut (hdc, 5, 235, "Active", 6);
			else
				TextOut (hdc, 5, 235, "Inert", 5);
		}
		else
			TextOut (hdc, 5, 205, "Empty", 5);

		ReleaseDC (_Editor.pCurrView->hWnd, &hdc);

		_Editor.GetActiveCurve()->DrawGrads (_Editor.pCurrView);

		if (_Editor.pCurrCurve != NULL)
			_Editor.pCurrCurve->DrawCurve (_Editor.pCurrView);

		if (_Editor.pCurrCurve1 != NULL)
			_Editor.pCurrCurve1->DrawCurve (_Editor.pCurrView);

		if (_Editor.pCurrCurve2 != NULL)
			_Editor.pCurrCurve2->DrawCurve (_Editor.pCurrView);

		// Validate the entire client area to stop looping WM_PAINT
		// BeginPaint normally does this
		RECT rect;
		GetClientRect (_Editor.hWnd, &rect);
		HRGN hRgn = CreateRectRgn (rect.left, rect.top, rect.right, rect.bottom);
		ValidateRgn (_Editor.hWnd, hRgn);

		_Editor.pCurrView->cRect = rect;

		return 0;
	}

	return DefWindowProc (hWnd, message, wParam, lParam) ;
}

void PrintMousePos (PVIEW pView)
{

	char str [32];
	FP x,y;
	POINT pos;

	pView->GetWorldPos (_Editor.MousePos, x, y);

	if (_Editor.pCurrCurve != NULL)
		if (_Editor.pCurrCurve->IndexType == IDT_WRAP)
			if (x > 180) x = x - 360;

	sprintf (str, "index %.6f    ", x);
	pos.x = 400;
	pos.y = 5;
	pView->DrawText (pos,str);

	sprintf (str, "value %.6f    ", y);
	pos.x = 400;
	pos.y = 25;
	pView->DrawText (pos,str);

}

// temorary function
PCURVE NextCurve (PCURVE pBase, Bool ac)
{

	static PCURVE pCurve = pBase;

	static char Name [CURVENAMESIZE];

	if (!ac)
	{

		pCurve = pCurve->List.NextItem();
	
		if (pCurve == NULL)
			pCurve = pBase;

	}

	if (ac)
	{

		strcpy (Name, pCurve->AircraftName);

		for (;;)
		{

			if (pCurve == NULL)
				pCurve = pBase;

			if (strncmp (pCurve->AircraftName, Name, CURVEMIN(strlen(pCurve->AircraftName), CURVENAMESIZE)))
				break;

			pCurve = pCurve->List.NextItem();

		}

	}

	return pCurve;

}

void Editor::ClearWindow ()
{
	RECT rect;
	HDC hdc;
	hdc = GetDC (hWnd);
	GetClientRect (hWnd, &rect);				
	FillRect (hdc, &rect, GetStockObject (WHITE_BRUSH));
	ReleaseDC (hWnd, hdc);
	InvalidateRect (hWnd, NULL, TRUE);
}


void Editor::PrintFunctionName ()
{

	char str [128];

	strcpy (str, FuncName());
	strcat (str, "       ");

	HDC hdc = GetDC (hWnd);
	TextOut (hdc, 200, 5, str, strlen(str));
	ReleaseDC (hWnd, &hdc);
}


EditorFunction::EditorFunction (ULong (*func)(ULong), ULong gokey, char* funcname)
{

	Func = func;
	GoKey = gokey;

	strncpy (FuncName, funcname, CURVEMIN(strlen(funcname),FUNCNAMESIZE));

	List.Attach (&_Editor.pFuncs, this);
}

EditorFunction::~EditorFunction ()
{
	List.Detach (this);
}


Bool Editor::SetFuncCode (ULong key)
{
	if (FuncCode == key)
		return (Bool)FALSE;

	FuncCode = key;
	return (Bool)TRUE;
}

ULong (* Editor::Function ())(ULong) 
{

	PEDFUNC pFunc = pFuncs;

	for (;;)
	{

		if (pFunc == NULL) break;

		if (FuncCode == pFunc->GoKey)
			return pFunc->Func;

		pFunc = pFunc->List.NextItem();

	}

	return &DoNothing;

}

char* Editor::FuncName ()
{

	PEDFUNC pFunc = pFuncs;

	for (;;)
	{

		if (pFunc == NULL) break;

		if (FuncCode == pFunc->GoKey)
			return pFunc->FuncName;

		pFunc = pFunc->List.NextItem();

	}

	return "None";
}

View::View (HWND hwnd)
{
	hWnd = hwnd;
}


void View::InitView (FP xmin, FP xmax, FP ymin, FP ymax)
{

	HDC hdc;

	RECT rect;
	POINT client;

	hdc = GetDC (hWnd);
	GetClientRect (hWnd, &rect);

	client.x = rect.right - rect.left;
	client.y = rect.bottom - rect.top;

	DPtoLP (hdc, &client, 1);

	ReleaseDC (hWnd, hdc);

	MaxScalex = (xmax - xmin) / (client.x * 0.75);
	MaxScaley = (ymin - ymax) / (client.y * 0.75);

	Scalex = MaxScalex;
	Scaley = MaxScaley;

	Org.x = (client.x * 0.125) - (xmin / MaxScalex);
	Org.y = (client.y * 0.875) - (ymin / MaxScaley);

}

void View::GetLimits (FP& x1, FP& x2, FP& y1, FP& y2)
{

	HDC hdc;

	RECT rect;
	POINT client;

	hdc = GetDC (hWnd);
	GetClientRect (hWnd, &rect);

	client.x = rect.right - rect.left;
	client.y = rect.bottom - rect.top;

	DPtoLP (hdc, &client, 1);

	ReleaseDC (hWnd, hdc);

	POINT p1,p2;

	p1.x = client.x * 0.125;
	p1.y = client.y * 0.125;

	GetWorldPos (p1, x1, y2);


	p2.x = client.x * 0.875;
	p2.y = client.y * 0.875;

	GetWorldPos (p2, x2, y1);

}


POINT View::GetScreenPos (FP x, FP y)
{
	POINT p;
	p.x = (x / Scalex) + Org.x;
	p.y = (y / Scaley) + Org.y;
	return p;
}


void View::GetWorldPos (POINT p, FP& x, FP& y)
{
	x = (p.x - Org.x) * Scalex;
	y = (p.y - Org.y) * Scaley;
}

void View::DrawPoint (FP x, FP y, DWORD color)
{

	HDC hdc;

	POINT SPos = GetScreenPos (x, y);

	hdc = GetDC (hWnd);

	RECT rect;

	rect.left = SPos.x - 1;
	rect.top = SPos.y - 1;
	rect.right = SPos.x + 2;
	rect.bottom = SPos.y + 2;

	HBRUSH hBrush = CreateSolidBrush (color);

	FillRect (hdc, &rect, hBrush);

	ReleaseDC (hWnd, hdc);
	DeleteObject (hBrush);

}

void View::DrawLine (FP x1, FP y1, FP x2, FP y2, DWORD color)
{

	HDC hdc;

	POINT SPos1 = GetScreenPos (x1,y1);
	POINT SPos2 = GetScreenPos (x2,y2);

	hdc = GetDC (hWnd);

	HPEN hPen = CreatePen (PS_SOLID, 1, color);

	SelectObject (hdc, hPen);

	MoveToEx (hdc, SPos1.x, SPos1.y, NULL);
	LineTo (hdc, SPos2.x, SPos2.y);

	ReleaseDC (hWnd, hdc);
	DeleteObject (hPen);

}

void View::DrawText (POINT pos, char* str)
{

	HDC hdc = GetDC (hWnd);
	TextOut (hdc, pos.x, pos.y, str, strlen(str));
	ReleaseDC (hWnd, &hdc);

}


Bool View::GetNearestPoint (PCURVE pCurve, POINT SPos, ULong& iPnt)
{


	FP x,y;

	GetWorldPos (SPos, x, y);

	ULong n;

	FP min = 1e9;

	Bool lock = FALSE;

	for (n=0; n<pCurve->cPoints; n++)
	{

		FP dist = FSqrt (((x - pCurve->CurveData[n].index) * (x - pCurve->CurveData[n].index)) +
			((y - pCurve->CurveData[n].value) * (y - pCurve->CurveData[n].value)));

		if (dist < min)
		{
			iPnt = n;
			lock = TRUE;
			min = dist;
		}
	}

	return lock;

}


void View::CombinationCurve (ULong Comb)
{


	if ((Comb & 0x10) && (_Editor.pCurrCurve1 == NULL))
		Comb &= !(0x13l);

	if ((Comb & 0x20) && (_Editor.pCurrCurve2 == NULL))
		Comb &= !(0x2cl);

	if (!Comb) return;

	// count no. of indexes
	ULong cIndexes = 0;

	cIndexes += _Editor.pCurrCurve->cPoints;
	if (Comb & 0x10) cIndexes += _Editor.pCurrCurve1->cPoints;
	if (Comb & 0x20) cIndexes += _Editor.pCurrCurve2->cPoints;

	cIndexes += 2;	// graph limits

	// make list of all indexes

	PFP pIndexes = new FP [cIndexes];
	ULong i = 0;

	pIndexes[i++] = 0;
	pIndexes[i++] = _Editor.pCurrCurve->MaxIndex;

	ULong n;

	for (n=0; n<_Editor.pCurrCurve->cPoints; n++, i++)
		pIndexes[i] = _Editor.pCurrCurve->CurveData[n].index;
		
	if (Comb & 0x10)
		for (n=0; n<_Editor.pCurrCurve1->cPoints; n++, i++)
			pIndexes[i] = _Editor.pCurrCurve1->CurveData[n].index;

	if (Comb & 0x20)
		for (n=0; n<_Editor.pCurrCurve2->cPoints; n++, i++)
			pIndexes[i] = _Editor.pCurrCurve2->CurveData[n].index;

	// sort into order

	ULong m;

	for (m=0; m<cIndexes; m++)
	{

		for (n=0; n<cIndexes-1; n++)
		{

			if (pIndexes[n] > pIndexes[n+1])
			{
				FP temp = pIndexes[n];
				pIndexes[n] = pIndexes[n+1];
				pIndexes[n+1] = temp;
			}

		}

	}

	// calc values

	PFP pValues = new FP [cIndexes];

	for (n=0; n<cIndexes; n++)
	{

		pValues[n] = _Editor.pCurrCurve->GetValue (pIndexes[n]);

		if (Comb & 0x01) pValues[n] += _Editor.pCurrCurve1->GetValue (pIndexes[n]);
		if (Comb & 0x02) pValues[n] -= _Editor.pCurrCurve1->GetValue (pIndexes[n]);

		if (Comb & 0x04) pValues[n] += _Editor.pCurrCurve2->GetValue (pIndexes[n]);
		if (Comb & 0x08) pValues[n] -= _Editor.pCurrCurve2->GetValue (pIndexes[n]);

	}

	// draw curve

	n=0;
	for (;;)
	{

		if (pIndexes[n] != pIndexes[n+1])
			DrawLine (pIndexes[n], pValues[n],
						pIndexes[n+1], pValues[n+1],				
						0x000000);

		n++;

		if (n == (cIndexes - 1)) break;

	}

	delete pValues;
	delete pIndexes;

}


void Curve::CalcCurveLimitsAll (FP& xmin, FP& xmax, FP& ymin, FP& ymax)
{

	FP x1,x2,y1,y2;

	xmin = 1e99;
	xmax = 1e-99;

	ymin = 1e99;
	ymax = 1e-99;

	if (_Editor.pCurrCurve != NULL)
	{
		_Editor.pCurrCurve->CalcCurveLimits (x1,x2,y1,y2);
		if (x1 < xmin) xmin = x1;
		if (x2 > xmax) xmax = x2;
		if (y1 < ymin) ymin = y1;
		if (y2 > ymax) ymax = y2;
	}

	if (_Editor.pCurrCurve1 != NULL)
	{
		_Editor.pCurrCurve1->CalcCurveLimits (x1,x2,y1,y2);
		if (x1 < xmin) xmin = x1;
		if (x2 > xmax) xmax = x2;
		if (y1 < ymin) ymin = y1;
		if (y2 > ymax) ymax = y2;
	}

	if (_Editor.pCurrCurve2 != NULL)
	{
		_Editor.pCurrCurve2->CalcCurveLimits (x1,x2,y1,y2);
		if (x1 < xmin) xmin = x1;
		if (x2 > xmax) xmax = x2;
		if (y1 < ymin) ymin = y1;
		if (y2 > ymax) ymax = y2;
	}

}

void Curve::CalcCurveLimits (FP& xmin, FP& xmax, FP& ymin, FP& ymax)
{

	xmin = MinIndex;
	xmax = MaxIndex;

	ULong n;

	ymin = 1e100;
	ymax = -1e100;

	for (n=0; n<cPoints; n++)
	{

		if (CurveData[n].value < ymin)
			ymin = CurveData[n].value;

		if (CurveData[n].value > ymax)
			ymax = CurveData[n].value;

	}

	ymin -= (ymax - ymin) / 6;
	ymax += (ymax - ymin) / 6;

	MaxValue = ymax;
	MinValue = ymin;

	if (ymin == ymax)
	{
		ymin -= 0.5;
		ymax += 0.5;
	}

}

void Curve::DrawGrads (PVIEW pView)
{


	FP xmin,xmax,ymin,ymax;

	pView->GetLimits (xmin,xmax,ymin,ymax);

	// fine graduations

	FP x,y;

	FP inc = 1e6;
	FP l = (xmax - xmin) / 10;

	while (inc > l)
		inc /= 10;

	FP xstart = (FP)((SLong)(xmin / inc)) * inc;

	for (x=xstart; x<xmax; x+=inc)
		pView->DrawLine (x, ymin, x, ymax, FINEGRADCOLOR);

	inc = 1e6;
	l = (ymax - ymin) / 10;

	while (inc > l)
		inc /= 10;

	FP ystart = (FP)((SLong)(ymin / inc)) * inc;

	for (y=ystart; y<ymax; y+=inc)
		pView->DrawLine (xmin, y, xmax, y, FINEGRADCOLOR);

	// numbers & grads

	inc = 1e6;
	l = (xmax - xmin) / 1;

	while (inc > l)
		inc /= 10;

	xstart = (FP)((SLong)(xmin / inc)) * inc;

	for (x=xstart; x<xmax; x+=inc)
	{

		POINT pos = pView->GetScreenPos (x, ymin);

		pos.x -= 15;
		pos.y += 3;

		char str [12];
		sprintf (str, "%.2f", x);

		pView->DrawText (pos, str);

		pView->DrawLine (x, ymin, x, ymax, GRADCOLOR);

	}

	inc = 1e6;
	l = (ymax - ymin) / 1;

	while (inc > l)
		inc /= 10;

	ystart = (FP)((SLong)(ymin / inc)) * inc;

	for (y=ystart; y<ymax; y+=inc)
	{

		POINT pos = pView->GetScreenPos (xmin, y);

//		pos.x -= 35;
		pos.x -= 15;
		pos.y -= 6;

		char str [12];
		sprintf (str, "%.4f", y);

		pView->DrawText (pos, str);
		pView->DrawLine (xmin, y, xmax, y, GRADCOLOR);

	}

	// max/min index
	if ((MinIndex >= xmin) && (MinIndex <= xmax))
		pView->DrawLine (MinIndex,ymin,MinIndex,ymax,LIMITCOLOR);

	if ((MaxIndex >= xmin) && (MaxIndex <= xmax))
		pView->DrawLine (MaxIndex,ymin,MaxIndex,ymax,LIMITCOLOR);

	// axes

	if (MinIndex <=0 && MaxIndex >= 0)
		pView->DrawLine (0,ymin,0,ymax,AXISCOLOR);

	if (MinValue <=0 && MaxValue >= 0)
		pView->DrawLine (xmin,0,xmax,0,AXISCOLOR);




}


void Curve::DrawCurve (PVIEW pView)
{

	ULong n;

	ULong LineColor;
	ULong PointColor;

	if (this == _Editor.GetActiveCurve())
	{
		LineColor = CURVELINECOLOR;
		PointColor = CURVEPOINTCOLOR;
	}
	else
	{
		LineColor = INERTCURVELINECOLOR;
		PointColor = INERTCURVEPOINTCOLOR;
	}

	// lines
	for (n=1; n<cPoints; n++)
		pView->DrawLine (CurveData[n-1].index, CurveData[n-1].value,
				CurveData[n].index, CurveData[n].value, LineColor);

	if (IndexType == IDT_WRAP)
	{

		pView->DrawLine (CurveData[cPoints-1].index - DeltaIndex, CurveData[cPoints-1].value,
				CurveData[0].index, CurveData[0].value, LineColor);

		pView->DrawLine (CurveData[cPoints-1].index, CurveData[cPoints-1].value,
				CurveData[0].index + DeltaIndex, CurveData[0].value, LineColor);

	}

	// points
	for (n=0; n<cPoints; n++)
		pView->DrawPoint (CurveData[n].index, CurveData[n].value, PointColor);


}

void Curve::UnDrawCurve (PVIEW pView)
{

	ULong n;

	// lines
	for (n=1; n<cPoints; n++)
		pView->DrawLine (CurveData[n-1].index, CurveData[n-1].value,
				CurveData[n].index, CurveData[n].value, WHITECOLOR);

	if (IndexType == IDT_WRAP)
	{

		pView->DrawLine (CurveData[cPoints-1].index - DeltaIndex, CurveData[cPoints-1].value,
				CurveData[0].index, CurveData[0].value, WHITECOLOR);

		pView->DrawLine (CurveData[cPoints-1].index, CurveData[cPoints-1].value,
				CurveData[0].index + DeltaIndex, CurveData[0].value, WHITECOLOR);

	}


	// points
	for (n=0; n<cPoints; n++)
		pView->DrawPoint (CurveData[n].index, CurveData[n].value, WHITECOLOR);

}


// Editor Functions

ULong MovePoint (ULong code)
{
	PCURVE pCurve =	_Editor.GetActiveCurve ();
	if (pCurve != NULL)
		return pCurve->movepoint (code);
	return FALSE;
}

ULong Curve::movepoint (ULong code)
{

	static ULong iPckedPnt = 0;

	static Bool lock = FALSE;

	if (code == WM_LBUTTONDOWN)
		if (_Editor.pCurrView->GetNearestPoint (this, _Editor.MousePos, iPckedPnt))
			lock = TRUE;

	if (code == WM_LBUTTONUP)
		lock = FALSE;

	if (lock)
	{
		FP x,y;
		_Editor.pCurrView->GetWorldPos (_Editor.MousePos, x, y);

		UnDrawCurve (_Editor.pCurrView);

		CurveData[iPckedPnt].index = x;
		CurveData[iPckedPnt].value = y;

		DrawCurve (_Editor.pCurrView);

	}

	return lock;

}

ULong AddPoint (ULong code)
{
	PCURVE pCurve =	_Editor.GetActiveCurve ();
	if (pCurve != NULL)
		return pCurve->addpoint (code);
	return FALSE;
}


ULong Curve::addpoint (ULong code)
{

	static ULong iPckedPnt = 0;

	if (code == WM_LBUTTONUP)
	{
		if (_Editor.pCurrView->GetNearestPoint (this, _Editor.MousePos, iPckedPnt))
		{

			UnDrawCurve (_Editor.pCurrView);

			PCURVE pCurve = this;

			PCURVEPNT pNewPnts = new CURVEPNT [pCurve->cPoints + 1];

			ULong n;

			for (n=0; n<=iPckedPnt; n++)
			{
				pNewPnts[n].index = pCurve->CurveData[n].index;
				pNewPnts[n].value = pCurve->CurveData[n].value;
			}
			 
			pNewPnts[n].index = (pCurve->CurveData[n-1].index + pCurve->CurveData[n].index) / 2;
			pNewPnts[n].value = (pCurve->CurveData[n-1].value + pCurve->CurveData[n].value) / 2;

			for (; n<pCurve->cPoints; n++)
			{
				pNewPnts[n+1].index = pCurve->CurveData[n].index;
				pNewPnts[n+1].value = pCurve->CurveData[n].value;
			}

			pCurve->cPoints++;

			delete pCurve->CurveData;

			pCurve->CurveData = pNewPnts;

			DrawGrads (_Editor.pCurrView);
			DrawCurve (_Editor.pCurrView);

		}
	}

	return iPckedPnt;

}

ULong DeletePoint (ULong code)
{
	PCURVE pCurve =	_Editor.GetActiveCurve ();
	if (pCurve != NULL)
		return pCurve->deletepoint (code);
	return FALSE;
}


ULong Curve::deletepoint (ULong code)
{

	static ULong iPckedPnt = 0;

	if (code == WM_LBUTTONUP)
	{
		if (_Editor.pCurrView->GetNearestPoint (this, _Editor.MousePos, iPckedPnt))
		{

			UnDrawCurve (_Editor.pCurrView);

			PCURVE pCurve = this;

			PCURVEPNT pNewPnts = new CURVEPNT [pCurve->cPoints - 1];

			ULong n,m;

			for (n=0, m=0; m<pCurve->cPoints; n++, m++)
			{
				if (m == iPckedPnt)
				{
					if ((m+1) == pCurve->cPoints)
						break;
					else
						m++;
				}

				pNewPnts[n].index = pCurve->CurveData[m].index;
				pNewPnts[n].value = pCurve->CurveData[m].value;
			}
			 
			pCurve->cPoints--;

			delete pCurve->CurveData;

			pCurve->CurveData = pNewPnts;

			DrawGrads (_Editor.pCurrView);
			DrawCurve (_Editor.pCurrView);

		}
	}

	return iPckedPnt;

}

ULong Zoom (ULong code)
{
	return _Editor.pCurrView->zoom (code);
}

ULong View::zoom (ULong code)
{

	POINT dOrg;

	switch (code)
	{
	case WM_LBUTTONDOWN:

		// Zoom In

		_Editor.ClearWindow ();

		dOrg.x = ((cRect.right - cRect.left) / 2) - _Editor.MousePos.x;
		dOrg.y = ((cRect.bottom - cRect.top) / 2) - _Editor.MousePos.y;

		dOrg.x += Org.x - _Editor.MousePos.x;
		dOrg.y += Org.y - _Editor.MousePos.y;

		Scalex /= 2;
		Scaley /= 2;

		Org.x += dOrg.x;
		Org.y += dOrg.y;

		InvalidateRect (hWnd, NULL, TRUE);

		return TRUE;
	
	case WM_RBUTTONDOWN:

		// Zoom Out

		_Editor.ClearWindow ();

		dOrg.x = ((cRect.right - cRect.left) / 2) - _Editor.MousePos.x;
		dOrg.y = ((cRect.bottom - cRect.top) / 2) - _Editor.MousePos.y;

		dOrg.x -= (Org.x - _Editor.MousePos.x) / 2;
		dOrg.y -= (Org.y - _Editor.MousePos.y) / 2;

		Scalex *= 2;
		Scaley *= 2;

		Org.x += dOrg.x;
		Org.y += dOrg.y;

		InvalidateRect (hWnd, NULL, TRUE);

		return TRUE;

	}

	return FALSE;

}


ULong Centre (ULong code)
{
	return _Editor.pCurrView->centre (code);
}

ULong View::centre (ULong code)
{

	POINT dOrg;

	switch (code)
	{
	case WM_LBUTTONDOWN:

		_Editor.ClearWindow ();

		dOrg.x = ((cRect.right - cRect.left) / 2) - _Editor.MousePos.x;
		dOrg.y = ((cRect.bottom - cRect.top) / 2) - _Editor.MousePos.y;

		Org.x += dOrg.x;
		Org.y += dOrg.y;

		InvalidateRect (hWnd, NULL, TRUE);

		return TRUE;

	}

	return FALSE;
}

ULong Snap2Grid (ULong code)
{
	return _Editor.pCurrView->snap2grid (code);
}

ULong View::snap2grid (ULong code)
{

	static ULong iPckedPnt = 0;

	static Bool lock = FALSE;

	if (code == WM_LBUTTONUP)
	{

		PCURVE pCurve = _Editor.GetActiveCurve ();

		if (pCurve != NULL)
		{

			if (_Editor.pCurrView->GetNearestPoint (pCurve, _Editor.MousePos, iPckedPnt))
			{

				lock = TRUE;

				FP x,y;

				x = _Editor.pCurrCurve->CurveData[iPckedPnt].index;
				y = _Editor.pCurrCurve->CurveData[iPckedPnt].value;

				// calc new position

				FP xmin,xmax,ymin,ymax;

				GetLimits (xmin,xmax,ymin,ymax);

				// numbers & grads

				FP incx = 1e6;
				FP incy = 1e6;

				FP lx = (xmax - xmin) / 10;
				FP ly = (ymax - ymin) / 10;

				while (incx > lx) incx /= 10;
				while (incy > ly) incy /= 10;

				x = (floor((x / incx) + 0.5)) * incx;
				y = (floor((y / incy) + 0.5)) * incy;

				// change point pos

				pCurve->UnDrawCurve (_Editor.pCurrView);

				pCurve->CurveData[iPckedPnt].index = x;
				pCurve->CurveData[iPckedPnt].value = y;

				pCurve->DrawCurve (_Editor.pCurrView);

			}
		}

	}

	return lock;

}

//TempCode ARM 03Jun97 ULong DuplicateCl (ULong code)
//TempCode ARM 03Jun97 {
//TempCode ARM 03Jun97 	if (code != WM_KEYDOWN) return FALSE;
//TempCode ARM 03Jun97 
//TempCode ARM 03Jun97 	PCURVE pCurve =	_Editor.GetActiveCurve ();
//TempCode ARM 03Jun97 	if (pCurve != NULL)
//TempCode ARM 03Jun97 		return pCurve->DuplicateCl (code);
//TempCode ARM 03Jun97 	return FALSE;
//TempCode ARM 03Jun97 }

ULong Curve::DuplicateCl (ULong code)
{

	UnDrawCurve (_Editor.pCurrView);

	PCURVE pCurve = this;

	ULong n;

	for (n=0; n<pCurve->cPoints; n++)
	{
		if (pCurve->CurveData[n].index > 180) break;
	}

	if (n < 2) return FALSE;

	if (n < pCurve->cPoints)
	{

		// remove points from n onwards (including n)
		// and duplicate & rotate through 180 

		PCURVEPNT pNewPnts = new CURVEPNT [n << 1];

		// copy wanted points into new array

		ULong m;
		for (m = 0; m<(n << 1); m++)
		{
			if (m < n)
			{
				pNewPnts[m].index = pCurve->CurveData[m].index;
				pNewPnts[m].value = pCurve->CurveData[m].value;
			}
			if (m >= n)
			{
				pNewPnts[m].index = 360 - pCurve->CurveData[(n<<1)-(m+1)].index;
				pNewPnts[m].value = - pCurve->CurveData[(n<<1)-(m+1)].value;
			}
		}

		pCurve->cPoints = n<<1;

		delete pCurve->CurveData;

		pCurve->CurveData = pNewPnts;
	}


	DrawGrads (_Editor.pCurrView);
	DrawCurve (_Editor.pCurrView);

	return TRUE;

	// ********

	static ULong iPckedPnt = 0;

	if (code == WM_LBUTTONUP)
	{
		if (_Editor.pCurrView->GetNearestPoint (this, _Editor.MousePos, iPckedPnt))
		{


			PCURVE pCurve = this;

			PCURVEPNT pNewPnts = new CURVEPNT [pCurve->cPoints - 1];

			ULong n,m;

			for (n=0, m=0; m<pCurve->cPoints; n++, m++)
			{
				if (m == iPckedPnt)
				{
					if ((m+1) == pCurve->cPoints)
						break;
					else
						m++;
				}

				pNewPnts[n].index = pCurve->CurveData[m].index;
				pNewPnts[n].value = pCurve->CurveData[m].value;
			}
			 
			pCurve->cPoints--;

			delete pCurve->CurveData;

			pCurve->CurveData = pNewPnts;


		}
	}

	return iPckedPnt;

}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		WriteCurves
//Author		Andrew McRae
//Date			Tue 11 Feb 1997
//
//Description	Writes out curve data into a C++ Source File
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void WriteCurves (PCURVE pCurve, char* Name)
{

	Snap2MinRes ();
	Curves2Rads ();

	// Count no. of types

	pCurve = _CurveRsc.pCurves;
	ULong cTypes = 0;
	char type [CURVENAMESIZE];
	strcpy (type, "noname");

	while (pCurve != NULL)
	{
		if (strcmp(type, pCurve->AircraftName))
		{
			strcpy (type, pCurve->AircraftName);
			cTypes++;
			WriteTypeCurves (type);
		}

		pCurve = pCurve->List.NextItem();
	}

//TempCode ARM 14Aug97 	// write curve list file
//TempCode ARM 14Aug97 
//TempCode ARM 14Aug97 	FILE* file;
//TempCode ARM 14Aug97 	char Line [LINESIZE];
//TempCode ARM 14Aug97 
//TempCode ARM 14Aug97 	file = fopen ("model\\cdat.lst", "wt");
//TempCode ARM 14Aug97 
//TempCode ARM 14Aug97 	if (file == NULL) return;
//TempCode ARM 14Aug97 
//TempCode ARM 14Aug97 	ULong c = 1;
//TempCode ARM 14Aug97 
//TempCode ARM 14Aug97 	pCurve = _CurveRsc.pCurves;
//TempCode ARM 14Aug97 
//TempCode ARM 14Aug97 	for (;;)
//TempCode ARM 14Aug97 	{
//TempCode ARM 14Aug97 
//TempCode ARM 14Aug97 		if (pCurve == NULL) break;
//TempCode ARM 14Aug97 
//TempCode ARM 14Aug97 		// write this curve
//TempCode ARM 14Aug97 
//TempCode ARM 14Aug97 		sprintf (Line, "%ld %s %s\n", c,
//TempCode ARM 14Aug97 			pCurve->AircraftName,
//TempCode ARM 14Aug97 			pCurve->CurveName);
//TempCode ARM 14Aug97 		fwrite (Line, strlen(Line), 1, file);
//TempCode ARM 14Aug97 
//TempCode ARM 14Aug97 		// next curve
//TempCode ARM 14Aug97 		pCurve = pCurve->List.NextItem ();
//TempCode ARM 14Aug97 
//TempCode ARM 14Aug97 		c++;
//TempCode ARM 14Aug97 
//TempCode ARM 14Aug97 	}
//TempCode ARM 14Aug97 
//TempCode ARM 14Aug97 	fclose (file);

	DestroyWindow (_Main.hWnd);

}

void WriteTypeCurves (char* Type)
{

	PCURVE pCurve;

	// make file name
	char fname [128];

	strcpy (fname, "aircraft\\cd_");
	strcat (fname, Type);
	strcat (fname, ".cpp");

	pCurve = _CurveRsc.pCurves;

	FILE* file;
	char Line [LINESIZE];

	file = fopen (fname, "wt");

	if (file == NULL) return;

	// print file headers

	strcpy (Line, "// Curves.cpp\n");
	fwrite (Line, strlen(Line), 1, file);
	strcpy (Line, "// Produced by ceditor.exe\n");
	fwrite (Line, strlen(Line), 1, file);
	strcpy (Line, "// Andrew McRae 10Feb97\n\n");
	fwrite (Line, strlen(Line), 1, file);

	sprintf (Line, "#include %cdosdefs.h%c\n", '"', '"');
	fwrite (Line, strlen(Line), 1, file);
	sprintf (Line, "#include %cmodvec.h%c\n", '"', '"');
	fwrite (Line, strlen(Line), 1, file);
	sprintf (Line, "#include %ccurves.h%c\n", '"', '"');
	fwrite (Line, strlen(Line), 1, file);

	strcpy (Line, "\nvoid LoadCurves");
	strcat (Line, Type);
	strcat (Line, " ()\n{\n\n");

//	strcpy (Line, "\nvoid LoadCurves ()\n{\n\n");
	fwrite (Line, strlen(Line), 1, file);

	for (;;)
	{

		if (pCurve == NULL) break;

		if (!strcmp (Type, pCurve->AircraftName))
		{

			// write this curve

			sprintf (Line, "\n\n// ****  %s  %s  **** //\n", 
				pCurve->AircraftName,
				pCurve->CurveName);
			fwrite (Line, strlen(Line), 1, file);

			sprintf (Line,
				"\nCURVEPNT %s_%s [%ld%] = {\n",
				pCurve->AircraftName,
				pCurve->CurveName,
				pCurve->cPoints);

			fwrite (Line, strlen(Line), 1, file);

			ULong n;
			PCURVEPNT pCurvePnt = pCurve->CurveData;

			for (n=0; n<pCurve->cPoints; n++, pCurvePnt++)
			{
				sprintf (Line, "\t%.12f,%.12f,\n", pCurvePnt->index, pCurvePnt->value);

				if ((n+1) == pCurve->cPoints)
					sprintf (Line, "\t%.12f,%.12f\n", pCurvePnt->index, pCurvePnt->value);

				fwrite (Line, strlen(Line), 1, file);
			}

			sprintf (Line, "};\n");
			fwrite (Line, strlen(Line), 1, file);

			sprintf (Line,
				"\nnew CURVE (%c%s%c,\n\t\t\t%c%s%c,\n\t\t\t%ld,\n\t\t\t%.12f,\n\t\t\t%.12f,\n\t\t\t%ld,\n\t\t\t%s_%s);\n",
				'"',pCurve->AircraftName,'"',
				'"',pCurve->CurveName,'"',
				pCurve->cPoints,
				pCurve->MinIndex,
				pCurve->MaxIndex,
				pCurve->IndexType,
				pCurve->AircraftName,
				pCurve->CurveName);

			fwrite (Line, strlen(Line), 1, file);

		}

		// next curve
		pCurve = pCurve->List.NextItem ();

	}

	strcpy (Line, "\n\n}\n\n// End.\n");
	fwrite (Line, strlen(Line), 1, file);

	fclose (file);

}

void Curves2Degs ()
{

	// convert rads to degs for IDT_WRAP curves

	PCURVE pCurve = _CurveRsc.pCurves;

	for (;;)
	{

		if (pCurve == NULL) break;

		if (pCurve->IndexType == IDT_WRAP)
		{

			pCurve->MinIndex = Rads2Degs (pCurve->MinIndex);
			pCurve->MaxIndex = Rads2Degs (pCurve->MaxIndex);
			pCurve->DeltaIndex = Rads2Degs (pCurve->DeltaIndex);

			ULong n;
			for (n=0; n<pCurve->cPoints; n++)
				pCurve->CurveData[n].index = Rads2Degs (pCurve->CurveData[n].index);

		}

		pCurve = pCurve->List.NextItem();
	}

}

void Curves2Rads ()
{

	// convert degs to rads for IDT_WRAP curves

	PCURVE pCurve = _CurveRsc.pCurves;

	for (;;)
	{

		if (pCurve == NULL) break;

		if (pCurve->IndexType == IDT_WRAP)
		{

			pCurve->MinIndex = Degs2Rads (pCurve->MinIndex);
			pCurve->MaxIndex = Degs2Rads (pCurve->MaxIndex);

			ULong n;
			for (n=0; n<pCurve->cPoints; n++)
				pCurve->CurveData[n].index = Degs2Rads (pCurve->CurveData[n].index);

		}

		pCurve = pCurve->List.NextItem();
	}

}


void Snap2MinRes ()
{

	// index 1e-6 degs

	// value 1e-6

	PCURVE pCurve = _CurveRsc.pCurves;

	for (;;)
	{

		if (pCurve == NULL) break;

		pCurve->MinIndex = Snap (pCurve->MinIndex, 1e6);
		pCurve->MaxIndex = Snap (pCurve->MaxIndex, 1e6);

		ULong n;
		for (n=0; n<pCurve->cPoints; n++)
		{
			pCurve->CurveData[n].index = Snap (pCurve->CurveData[n].index, 1e6);
			pCurve->CurveData[n].value = Snap (pCurve->CurveData[n].value, 1e6);
		}

		pCurve = pCurve->List.NextItem();
	}

}


FP Snap (FP v, FP res)
{
	return (floor ((v * res) + 0.5)) / res;
}

// For winerror.cpp
void Main::QuitGame ()
{
}
