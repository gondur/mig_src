//---------------------------------------------------------------------------
#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Buttons.hpp>
//---------------------------------------------------------------------------
class TPlayerForm : public TForm
{
__published:	// IDE-managed Components
	TGroupBox *PromotionCritGroup;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label8;
	TLabel *Label9;
	TLabel *Label10;
	TLabel *Label11;
	TLabel *Label12;
	TEdit *Edit6;
	TEdit *Edit7;
	TEdit *Edit8;
	TEdit *Edit9;
	TEdit *Edit10;
	TEdit *Edit11;
	TEdit *Edit12;
	TEdit *Edit13;
	TBitBtn *PlayerOk;
	TBitBtn *PlayerCancel;
private:	// User declarations
public:		// User declarations
	__fastcall TPlayerForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TPlayerForm *PlayerForm;
//---------------------------------------------------------------------------
#endif
 