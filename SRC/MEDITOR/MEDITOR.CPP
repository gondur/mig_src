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

//---------------------------------------------------------------------------

#include <vcl\vcl.h>
#include <dir.h>
#include "loadsave.h" 
#include "memain.h"
#include "fileman.h"
#pragma hdrstop

//---------------------------------------------------------------------------
USEFORM("About.cpp", AboutBox);
USEFORM("AcItem.cpp", AcItemForm);
USEFORM("sqinfo.cpp", SquadronDataForm);
USEFORM("Static.cpp", StaticForm);
USEFORM("MissText.cpp", MissionTextDlg);
USEFORM("afselect.cpp", SelectAirfield);
USEFORM("missobj.cpp", MissionObjectivesForm);
USEFORM("SelTarg.cpp", SelectTarget);
USEFILE("reserves.h");
USEFORM("GrndGrp.cpp", GroundGroupForm);
USEFORM("currshp.cpp", CurrShape);
USEFORM("info.cpp", InfoForm);
USEFILE("Wp.h");
USEFORM("Confirm.cpp", ConfirmForm);
USEFORM("Precomp.cpp", Editb4Compile);
USERC("Meditor.rc");
USEFORM("itemcnt.cpp", CountForm);
USEFORM("bfform.cpp", BfieldForm);
USEUNIT("\MIG\SRC\BFIELDS\Meglobal.cpp");
USEUNIT("\MIG\SRC\BFIELDS\Persons6.cpp");
USEUNIT("\MIG\SRC\BFIELDS\Persons5.cpp");
USEUNIT("\MIG\SRC\BFIELDS\Persons2.cpp");
USEFORM("Sgroups.cpp", SuperGroups);
USEUNIT("gamestub.cpp");
USEFORM("Memain.cpp", MissionEditor);
USEUNIT("Memain2.cpp");
USEFORM("Loadsave.cpp", FileLoadSave);
USEFORM("waypoint.cpp", WayPointForm);
USEUNIT("\MIG\SRC\FILES\Fileman.cpp");
USEUNIT("mapload.cpp");
USEUNIT("Memain3.cpp");
USEFORM("Eventtxt.cpp", TextEvent);
USEFORM("eventsel.cpp", SelEvent);
USEFORM("Eventspn.cpp", SpinEvent);
USEUNIT("\mig\SRC\BFIELDS\Persons4.cpp");
USEUNIT("\mig\SRC\BFIELDS\persons7.cpp");
USEFORM("NameList.cpp", NameListSel);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR line, int)
{
//	Application->MessageBox(line,line,MB_OK);
	char winname[80];
	char*cmd=Application->ExeName.c_str();
	if (cmd[0]=='"')
		cmd++;
	char* copy=winname;
	while (*cmd>' ' && *cmd!='"')
		*copy++=*cmd++;
	copy--;
	while (*copy!='\\')
		copy--;
	copy--;
	while (*copy!='\\')
		copy--;
	*copy=0;
//	Application->MessageBox(winname,Application->ExeName.c_str(),MB_OK);
	chdir(winname);
    FILEMAN.InitFileSystem();
//	if(!((Main*)NULL)->InitFileSystem(*(Main*)NULL))
  //		exit(1);
	cmd=Application->ExeName.c_str();
	if (cmd[0]=='"')
	cmd++;
	copy=winname;
	while (*cmd>' ' && *cmd!='"')
		*copy++=*cmd++;
	copy--;
	while (*copy!='\\')
		copy--;
	*copy=0;
	chdir(winname);        
  //	}
//	else
  //		if(!((Main*)NULL)->InitFileSystem(*(Main*)NULL))
	//		exit(1);

//		_Error.EmitSysErr(__FILE__":Failed to init file system\n");


    if (!*line)
	try
	{
		Application->Initialize();
		Application->Title = "Mission Editor V1.00";
		Application->HelpFile = "Mehelp.hlp";
		Application->Icon->LoadFromFile("Meditor.ico");

		Application->CreateForm(__classid(TMissionEditor), &MissionEditor);
		Application->CreateForm(__classid(TSuperGroups), &SuperGroups);
		Application->CreateForm(__classid(TBfieldForm), &BfieldForm);
		Application->CreateForm(__classid(TFileLoadSave), &FileLoadSave);
		Application->CreateForm(__classid(TWayPointForm), &WayPointForm);
		Application->CreateForm(__classid(TAboutBox), &AboutBox);
		Application->CreateForm(__classid(TAcItemForm), &AcItemForm);
		Application->CreateForm(__classid(TSquadronDataForm), &SquadronDataForm);
		Application->CreateForm(__classid(TStaticForm), &StaticForm);
		Application->CreateForm(__classid(TMissionTextDlg), &MissionTextDlg);
		Application->CreateForm(__classid(TSelectAirfield), &SelectAirfield);
		Application->CreateForm(__classid(TMissionObjectivesForm), &MissionObjectivesForm);
		Application->CreateForm(__classid(TSelectTarget), &SelectTarget);
		Application->CreateForm(__classid(TGroundGroupForm), &GroundGroupForm);
		Application->CreateForm(__classid(TCurrShape), &CurrShape);
		Application->CreateForm(__classid(TInfoForm), &InfoForm);
//////////////////////		Application->CreateForm(__classid(TFileLoadSave), &FileLoadSave);
		Application->CreateForm(__classid(TConfirmForm), &ConfirmForm);
		Application->CreateForm(__classid(TEditb4Compile), &Editb4Compile);
		Application->CreateForm(__classid(TCountForm), &CountForm);
		Application->CreateForm(__classid(TTextEvent), &TextEvent);
		Application->CreateForm(__classid(TSelEvent), &SelEvent);
		Application->CreateForm(__classid(TSpinEvent), &SpinEvent);
		Application->CreateForm(__classid(TNameListSel), &NameListSel);
		FileLoadSave->HomeDir=winname;
	Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	if(*line)
    {
		Application->Initialize();
		Application->CreateForm(__classid(TMissionEditor), &MissionEditor);
		MissionEditor->QuickDisassemble(line);
		exit(1);
    }
	return 0;
}
//---------------------------------------------------------------------------

