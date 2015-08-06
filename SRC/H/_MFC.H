#pragma optimize( "g", off )
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
#define THIS_FILE __FILE__
#define	THIS_FILE_DEFINED

#endif
#define F_SOUNDS
#include "dosdefs.h"
#include "files.g"

#include	<afxmt.h>
#include	<dinput.h>
#include	<mmsystem.h>
#include	"stub3d.h" 
#include "display.h"  
#include "stdafx.h"
#include	"flyinit.h"
#include	"DEBRIEF.h"
CString	MakePilotName(PilotName& name);

MATHABLE(SquadSelect)
MATHABLE(Debrief::Types)
MATHABLE(Debrief::PlayerTypes)
#ifndef _DEBUG
#pragma message(__HERE__ "Non-debug version: global optimisation enabled when safe!")
#pragma optimize( "g", on )
#endif



