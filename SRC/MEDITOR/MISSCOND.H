//---------------------------------------------------------------------------
#ifndef missionconditionsH
#define missionconditionsH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Buttons.hpp>
#include <vcl\Mask.hpp>
#include "sampreg.h"

#include <dosdefs.h>

//---------------------------------------------------------------------------
class TMissionConditionsForm : public TForm
{
__published:	// IDE-managed Components
	TBitBtn *ConditionsOk;
	TBitBtn *ConditionsCancel;
	TLabel *DateLabel;
	TLabel *TimeLabel;
	TLabel *WeatherLabel;
	TLabel *WindDirectionLabel;
	TLabel *WindSpeedLabel;
	TComboBox *MonthComboBox;
	TLabel *ColonLabel;
	TComboBox *WeatherComboBox;
	TComboBox *WindDirComboBox;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TComboBox *FormationComboBox;
	void __fastcall MonthComboBoxChange(TObject *Sender);
	void __fastcall YearSpinEditChange(TObject *Sender);
	
	
private:	// User declarations
void __fastcall TMissionConditionsForm::ResetMaxDay();
SLong __fastcall TMissionConditionsForm::SecsFromDate (SWord day,SWord month,SWord year);

public:		// User declarations
	__fastcall TMissionConditionsForm(TComponent* Owner);
	void __fastcall TMissionConditionsForm::OpenForm();
};
//---------------------------------------------------------------------------
extern TMissionConditionsForm *MissionConditionsForm;
//---------------------------------------------------------------------------
#endif
 