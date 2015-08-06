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

#include "stdafx.h"
#include "_mfc.h"

#ifndef	MIG_DEMO_VER

#include ".\AC_view.cpp"
#include ".\Apilot.cpp"
#include ".\Army.cpp"
#include ".\ArmyDetl.cpp"
#include ".\Armyrqst.cpp"
#include ".\Army_dos.cpp"
#include ".\Author.cpp"
#include ".\Bases.cpp"
#include ".\basest.cpp"
#include ".\battdetl.cpp"
#include ".\campback.cpp"
#include ".\Camplist.cpp"
#include ".\campwar.cpp"
#include ".\Career.cpp"
#include ".\Choke.cpp"
#include ".\chsquad.cpp"
#include ".\Cmbtview.cpp"
#include ".\Comit_e.cpp"
#include ".\commspnt.cpp"
#include ".\commsac.cpp"
#include ".\currembl.cpp"
#include ".\Damage.cpp"
#include ".\dbrftlbr.cpp"
#include ".\directs2.cpp"
#include ".\DIS.cpp"
#include ".\dis_note.cpp"
#include ".\dosbut.cpp"
#include ".\Dossier.cpp"
#include ".\filing.cpp"
#include ".\Flt_Task.cpp"
#include ".\footage.cpp"
#include ".\Frag.cpp"
#include ".\FragPilt.cpp"
#include ".\General.cpp"
#include ".\Grndview.cpp"
#include ".\load.cpp"
#include ".\loadprof.cpp"
#include ".\Locker.cpp"
#include ".\LstMsnlg.cpp"
#include ".\MapFltrs.cpp"
#include ".\Misntext.cpp"
#include ".\Misn_log.cpp"
#include ".\Missfldr.cpp"
#include ".\msndebrf.cpp"
#include ".\MResult.cpp"
#include ".\MTChild.cpp"
#include ".\nose_art.cpp"
#include ".\Notes.cpp"
#include ".\Overview.cpp"
#include ".\Paint.cpp"
#include ".\personal.cpp"
#include ".\Pilots.cpp"
#include ".\Plyr_log.cpp"
#include ".\Profile.cpp"
#include ".\Prof_lib.cpp"
#include ".\Radio.cpp"
#include ".\Ready.cpp"
#include ".\RIP_List.cpp"
#include ".\rmdldlg.cpp"
#include ".\Route.cpp"
#include ".\RowTasks.cpp"
#include ".\Rradio.cpp"
#include ".\rstatic.cpp"
#include ".\Rtestsh1.cpp"
#include ".\Rtoolbar.cpp"
#include ".\sairclms.cpp"
#include ".\saveprof.cpp"
#include ".\Scalebar.cpp"
#include ".\Scamp.cpp"
#include ".\scontrol.cpp"
#include ".\Sdetail.cpp"
#include ".\selects.cpp"
#include ".\service.cpp"
#include ".\session.cpp"
#include ".\sflight.cpp"
#include ".\Sgame.cpp"
#include ".\Sgrdclms.cpp"
#include ".\smkdlg.cpp"
#include ".\sqdnlb.cpp"
#include ".\Sqdnlist.cpp"
#include ".\Squads.cpp"
#include ".\Squick1.cpp"
#include ".\Sqdnlbut.cpp"
#include ".\Squick2.cpp"
#include ".\squickp.cpp"
#include ".\Squickun.cpp"
#include ".\sqview.cpp"
#include ".\Sreplay.cpp"
#include ".\Ssound.cpp"
#include ".\Supply.cpp"
#include ".\Sviewer.cpp"
#include ".\Task.cpp"
#include ".\tasktabs.cpp"
#include ".\userinst.cpp"
#include ".\variants.cpp"
#include ".\Visitors.cpp"
#include ".\vwqlist.cpp"
#include ".\waveins.cpp"
#include ".\WaveTabs.cpp"
#include ".\Weapons.cpp"
#include ".\Weather.cpp"
#include ".\WPBut.cpp"
#include ".\wpdetail.cpp"
#include ".\WPGround.cpp"
#include ".\WPShare.cpp"

#else

#include ".\rmdldlg.cpp"
#include ".\Weapons.cpp"
#include ".\Rradio.cpp"
#include ".\filing.cpp"
#include ".\MTChild.cpp"
#include ".\campback.cpp"
#include ".\Apilot.cpp"
//#include ".\Comit_e.cpp"
#include ".\currembl.cpp"
#include ".\Damage.cpp"
//#include ".\directs2.cpp"
#include ".\load.cpp"
#include ".\MResult.cpp"
#include ".\rstatic.cpp"
#include ".\Rtestsh1.cpp"
#include ".\sairclms.cpp"
#include ".\scontrol.cpp"
#include ".\Sdetail.cpp"
#include ".\sflight.cpp"
#include ".\Sgame.cpp"
#include ".\Sgrdclms.cpp"
#include ".\smkdlg.cpp"
#include ".\Squick1.cpp"
#include ".\Squick2.cpp"
#include ".\squickp.cpp"
#include ".\Squickun.cpp"
#include ".\Sreplay.cpp"
#include ".\Ssound.cpp"
#include ".\Sviewer.cpp"
#include ".\variants.cpp"
#include ".\Locker.cpp"
#include ".\Visitors.cpp"
#include ".\Radio.cpp"
#include ".\Ready.cpp"
#include ".\commspnt.cpp"
#include ".\commsac.cpp"

#endif
