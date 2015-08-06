#define	F_COMMON
#define	F_GRAFIX
//#define	WINMOVE_Included
#include	"DOSDefs.h"
#include	<stdio.h>
#include	<io.h>
#include	<stdarg.h>
#include	<stdlib.h>
#include	<string.h>
#include	"modfile.h"
#include	"myAngles.h"
#include	"WorldInc.h"
#include	"AnimData.h"									//RJS 10Feb97

#include	"UniqueID.h"										//ARM 09Aug96
#include	"World.h"
#include	"FileMan.h"
#include	"makebf.h"
#define		TEXTREF_NOTYPES
#include	"textref.h"
#include	"Persons2.h"
#include	<string.h>

#include	"myError.h"
#include	"shapes.h"
#include	"mymath.h"
#include	"flymodel.h"									//PD 01Nov95
#include	"missman2.h"
//MATHABLE	(ANGLES);

#include	"bitfield.h"
#include	"3dcom.h"
#include	"Mytime.h"
#include	"flymodel.h"

#include	"ai.h"

#include	"viewsel.h"											//PD 26Jun96

#include	"landscap.h"

#include	"savegame.h"
#include	"aaa.h"
#include	"shpinstr.h"										//RJS 01Dec97
#include	"stub3d.h"
//TempCode ARM 12Sep96 #include 	<windows.h>											//ARM 09Aug96
//TempCode ARM 12Sep96 #include 	<windowsx.h>										//ARM 09Aug96
//TempCode ARM 12Sep96 #include 	<mmsystem.h>										//ARM 09Aug96
//TempCode ARM 12Sep96 #include	"c:\dxsdk\sdk\inc\dplay.h"							//ARM 09Aug96
#include	"winmove.h"											//ARM 09Aug96

#include	"modinst.h"
//#include	"replay.h"
