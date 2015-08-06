//---------------------------------------------------------------------------
#ifndef missobjH
#define missobjH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Buttons.hpp>

#include <dosdefs.h>


//---------------------------------------------------------------------------
class TMissionObjectivesForm : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TEdit *Edit0;
	TButton *Button0;
	TEdit *Edit1;
	TButton *Button1;
	TEdit *Edit2;
	TButton *Button2;
	TEdit *Edit3;
	TButton *Button3;
	TEdit *Edit4;
	TButton *Button4;
	TBitBtn *ObjectivesOk;
	TBitBtn *ObjectivesCancel;
	void __fastcall Button0Click(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TMissionObjectivesForm(TComponent* Owner);
	__fastcall TMissionObjectivesForm::OpenForm();
	__fastcall TMissionObjectivesForm::InitForm();
	__fastcall TMissionObjectivesForm::ProcessForm();
	__fastcall TMissionObjectivesForm::RefreshForm();



};
//---------------------------------------------------------------------------
extern TMissionObjectivesForm *MissionObjectivesForm;
//---------------------------------------------------------------------------
#endif
 