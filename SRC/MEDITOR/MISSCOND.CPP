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
#pragma hdrstop

#include "misscond.h"
#include "Memain.h"

#include "strings.h"

#include	"mymath.h"
#include	"myangles.h"
#include	"mytime.h"
MaxDaysinMonth[] = {31,28,31,30,31,30,31,31,30,31,30,31};

//---------------------------------------------------------------------------
#pragma link "sampreg"
#pragma resource "*.dfm"
TMissionConditionsForm *MissionConditionsForm;
//---------------------------------------------------------------------------
__fastcall TMissionConditionsForm::TMissionConditionsForm(TComponent* Owner)
	: TForm(Owner)
{
	Font->Color = clWindow;
	Font->Color = clWindowText;
}
//---------------------------------------------------------------------------
void __fastcall TMissionConditionsForm::ResetMaxDay()
{
//spin	if (	(MonthComboBox->ItemIndex == 1)
//spin			&&   (YearSpinEdit->Value == 1916)
//spin	   )
//spin		DateSpinEdit->MaxValue = 29;
//spin	else
//spin		DateSpinEdit->MaxValue = MaxDaysinMonth[MonthComboBox->ItemIndex];
//spin
//spin	if (DateSpinEdit->Value > DateSpinEdit->MaxValue)
//spin		DateSpinEdit->Value = DateSpinEdit->MaxValue;
//spin	if (DateSpinEdit->Value < DateSpinEdit->MinValue)
//spin		DateSpinEdit->Value = DateSpinEdit->MinValue;

}

//---------------------------------------------------------------------------
SLong __fastcall TMissionConditionsForm::SecsFromDate (SWord day,SWord month,SWord year)
{
	SWord	j=0,year4;
	SLong	date;

	while(j<month)
	{
		if (	(j == 1)
				&&   (year == 1916)
			)
			day += 29;
		else
			day += MaxDaysinMonth[j];
		j++;
	};

	year -= 1901;
	year4 = year/4;
	year = year - year4*4;
	day = day + year4*(SWord)DAYSPER4YEAR + year*(SWord)DAYSPERYEAR-1;
	date = (SLong)day*(SLong)SECSPERDAY;
	return(date);
}

//---------------------------------------------------------------------------
void __fastcall TMissionConditionsForm::OpenForm()
{
	SWord	month = 1;
	SWord	day = 1,year = 1;
//DeadCode RDH 04Mar96 	window->SetColour (WHITE);
	char buff[50];


//camp	Math_Lib.DateFromSecs (MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].missiondate
//								,day,month,year);
	year += 1901;

	SLong	timeinsecs = (int)SECSPERHR*12;//MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].timeofday;
//spin	 HourSpinEdit->Value = timeinsecs/ (int)SECSPERHR;
//spin	 SLong	fullhrinsecs = HourSpinEdit->Value *(int)SECSPERHR;
//spin	 timeinsecs  =  (timeinsecs - fullhrinsecs)/ (int) SECSPERMIN;
//spin	 MinuteSpinEdit->Value =  timeinsecs;

//spin	 YearSpinEdit->Value = year;
//spin	 DateSpinEdit->Value = day;
	 MissionEditor->FillComboBox(TEXT_JANUARY,TEXT_DECEMBER,MonthComboBox,
										month);

	ResetMaxDay();

//spin	FormSpinEdit->Value = 1;//camp MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].numofflightac;
//spin	WingSpinEdit->Value = 1;//camp MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].numofsquadronac;
#define		TEXT_STACKED						4680
#define		TEXT_SHEPHERD           			4687
	MissionEditor->FillComboBox(TEXT_STACKED, TEXT_SHEPHERD, FormationComboBox,1);
//camp			MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].formationtypeindex);

	 LoadString(HInstance,TEXT_SPD2,buff,sizeof(buff));

	if (MissionEditor->Configure_Units == METRIC)
	{
	   strcat(buff,"m/s");
//spin	  WindSpeedSpinEdit->Value = 0	;//camp MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].windspeed/10;
//spin	  WindSpeedSpinEdit->MaxValue = 7;
	  MissionEditor->FillComboBox(IDS_TEXT_LOWCLOUDM,IDS_TEXT_BADWEATHERM,WeatherComboBox,1);
//camp			MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].weathernum);

	}else if (MissionEditor->Configure_Units == IMPERIAL)
	{
   	strcat(buff,"mph");
//spin	  WindSpeedSpinEdit->Value = 0;//camp MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].windspeed *224/1000;
//spin	  WindSpeedSpinEdit->MaxValue = 15;
		 MissionEditor->FillComboBox(IDS_TEXT_LOWCLOUD,IDS_TEXT_BADWEATHER,WeatherComboBox,1);
//camp			MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].weathernum);
	}else
	{
	  WindSpeedLabel->Caption = "m/s";
//spin	  WindSpeedSpinEdit->Value = 0; //camp MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].windspeed/10;
//spin	  WindSpeedSpinEdit->MaxValue = 7;
		 MissionEditor->FillComboBox(IDS_TEXT_LOWCLOUD,IDS_TEXT_BADWEATHER,WeatherComboBox,1);
//camp			MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].weathernum);
	}

     WindSpeedLabel->Caption = buff;

	 int index = 0;	//MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].winddirection;
	 index = index / (int) ANGLES_45Deg;
	 MissionEditor->FillComboBox(IDS_TEXT_NORTH,IDS_TEXT_NORTHWEST,WindDirComboBox,
			  index);

	int result = ShowModal();
	switch (result)
	{
		case	mrOk:
		  {
			MissionEditor->loadedbfs[MissionEditor->bfieldbeingfilled].changed=true;
//		  	MissionEditor->MissionEdited=true;

//camp			MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].timeofday =
//				 HourSpinEdit->Value * (int)SECSPERHR + MinuteSpinEdit->Value * (int) SECSPERMIN;
//
//
//			MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].missiondate =
//				SecsFromDate (DateSpinEdit->Value,MonthComboBox->ItemIndex,YearSpinEdit->Value);
//
//			MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].
//				formationtypeindex = FormationComboBox->ItemIndex;
//			MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].numofflightac = FormSpinEdit->Value;
//			MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].numofsquadronac = WingSpinEdit->Value;
//
//			MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].winddirection =
//				WindDirComboBox->ItemIndex * (int)ANGLES_45Deg;
//
//			MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].weathernum =
//						WeatherComboBox->ItemIndex;
//
//
//			if (MissionEditor->Configure_Units == METRIC)
//			  MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].windspeed =
//							WindSpeedSpinEdit->Value  * 10;
//			else if (MissionEditor->Configure_Units == IMPERIAL)
//			  MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].windspeed =
//							WindSpeedSpinEdit->Value  * 1000/224;
//			else
//			  MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].windspeed =
//							WindSpeedSpinEdit->Value  * 10;


			 break;
		  }
		case	mrCancel:
		  {

				 break;
		  }
	  }

}
//---------------------------------------------------------------------------
void __fastcall TMissionConditionsForm::MonthComboBoxChange(TObject *Sender)
{
		ResetMaxDay();
}
//---------------------------------------------------------------------------
void __fastcall TMissionConditionsForm::YearSpinEditChange(TObject *Sender)
{
		ResetMaxDay();
}
//---------------------------------------------------------------------------
