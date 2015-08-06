//---------------------------------------------------------------------------
#ifndef itemcntH
#define itemcntH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Buttons.hpp>
//---------------------------------------------------------------------------
class TCountForm : public TForm
{
__published:	// IDE-managed Components
	TLabel *AlliesAircraftLabel;
	TLabel *CPAircraftLabel;
	TLabel *AlliesGMLabel;
	TLabel *CPMLabel;
	TLabel *AlliesTanksLabel;
	TLabel *CPTanksLabel;
	TLabel *AACLabel;
	TLabel *CPACLabel;
	TLabel *AMCLabel;
	TLabel *CPMCLabel;
	TLabel *ATCLabel;
	TLabel *CPTCLabel;
	TLabel *AAMLabel;
	TLabel *CPAMLabel;
	TLabel *AMMLabel;
	TLabel *CPMMLabel;
	TLabel *ATMLabel;
	TLabel *CPTMLabel;
	TLabel *CurrentLabel;
	TLabel *MaxLabel;
	TBitBtn *BitBtn1;
	TMemo *Memo1;
private:	// User declarations
public:		// User declarations
	__fastcall TCountForm(TComponent* Owner);
	void	__fastcall TCountForm::OpenForm();
};
//---------------------------------------------------------------------------
extern TCountForm *CountForm;
//---------------------------------------------------------------------------
#endif
 