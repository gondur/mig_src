//---------------------------------------------------------------------------
#ifndef AcItemH
#define AcItemH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Buttons.hpp>
#include <vcl\ComCtrls.hpp>
#include "sampreg.h"
#include <vcl\ExtCtrls.hpp>

#include <uniqueid.h>
#include "spin.h"

//---------------------------------------------------------------------------
class TAcItemForm : public TForm
{
__published:	// IDE-managed Components
	TBitBtn *AcItemOk;
	TBitBtn *AcItemCancel;
	TBitBtn *AcItemRoute;
	TBitBtn *AcItemDelete;
	TGroupBox *FlightDataBox;
	TLabel *AltLabel;
	TEdit *SpeedEdit;
	TLabel *SpeedLabel;
	TEdit *AltEdit;
	TGroupBox *AcItemSquadronData;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TComboBox *FormComboBox;
	TEdit *Position;
	TButton *PositionButton;
	TLabel *Label4;
	TCheckBox *PlayerCheckBox;
	TPanel *SquadronPanel;
	TLabel *SquadronLabel;
	TButton *SquadButton;
	TComboBox *SpdComboBox;
	TComboBox *AircraftComboBox;
	TLabel *AircraftLabel;
	TCheckBox *Bombs;
	TSpinEdit *FormSizeSpinEdit;
	TSpinEdit *WingSizeSpinEdit;
	TSpinButton *SpeedSpin;
	void __fastcall SquadButtonClick(TObject *Sender);
	

	
	
	
	
	
	void __fastcall PositionButtonClick(TObject *Sender);
	void __fastcall AltEditExit(TObject *Sender);

	void __fastcall PlayerCheckBoxMouseDown(TObject *Sender, TMouseButton Button,
	TShiftState Shift, int X, int Y);
	
	
	
	void __fastcall SpeedEditChange(TObject *Sender);
	void __fastcall SpdComboBoxChange(TObject *Sender);
	void __fastcall FormSizeSpinEditMouseDown(TObject *Sender, TMouseButton Button,
	TShiftState Shift, int X, int Y);
	void __fastcall WingSizeSpinEditMouseDown(TObject *Sender, TMouseButton Button,
	TShiftState Shift, int X, int Y);
	void __fastcall FormSizeSpinEditChange(TObject *Sender);
	void __fastcall WingSizeSpinEditChange(TObject *Sender);
	
	
	
//	void __fastcall SpinButton1DownClick(TObject *Sender);
//	void __fastcall SpinButton1UpClick(TObject *Sender);
	void __fastcall AltEditChange(TObject *Sender);
	
	
	
//	void __fastcall SpinEdit1MouseDown(TObject *Sender, TMouseButton Button,
//	TShiftState Shift, int X, int Y);
	void __fastcall SpeedSpinDownClick(TObject *Sender);
	void __fastcall SpeedSpinUpClick(TObject *Sender);
private:	// User declarations
	void __fastcall TAcItemForm::CheckSpeedField();
	void __fastcall TAcItemForm::SetMaxAc();
public:		// User declarations
	__fastcall TAcItemForm(TComponent* Owner);
	void		__fastcall TAcItemForm::DeleteCurrTransItem();
	void __fastcall TAcItemForm::OpenAcItem(int X, int Y);
	void __fastcall TAcItemForm::AcceptChanges();
	void __fastcall TAcItemForm::InitForm(int X, int Y);
	void __fastcall TAcItemForm::ProcessForm(int X, int Y);
	void __fastcall TAcItemForm::RefreshForm();
	int  __fastcall TAcItemForm::FindVel( int& vel);

	int	acvel;
	int	tmpplayeracuid;
	int	Squadron;
	char	SquadronName[100];
   int	WorldY;
   UniqueID    tmphomebase;
};
//---------------------------------------------------------------------------
extern TAcItemForm *AcItemForm;
extern	TComboBox *SquadronComboBox;
extern	TComboBox *NationaltiyComboBox;
//---------------------------------------------------------------------------
#endif
