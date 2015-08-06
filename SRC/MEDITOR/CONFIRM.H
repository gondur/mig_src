//---------------------------------------------------------------------------
#ifndef confirmH
#define confirmH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
//---------------------------------------------------------------------------
class TConfirmForm : public TForm
{
__published:	// IDE-managed Components
	TLabel *SaveLabel;
	TButton *YesButton;
	TButton *NoButton;
	TButton *CancelButton;
private:	// User declarations
public:		// User declarations
	__fastcall TConfirmForm(TComponent* Owner);
	int __fastcall TConfirmForm::OpenForm(char* caption);
	int __fastcall TConfirmForm::OpenSaveForm();

};
//---------------------------------------------------------------------------
extern TConfirmForm *ConfirmForm;
//---------------------------------------------------------------------------
#endif
