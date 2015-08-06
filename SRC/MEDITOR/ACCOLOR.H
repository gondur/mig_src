//---------------------------------------------------------------------------
#ifndef accolorH
#define accolorH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include "sampreg.h"
#include <vcl\Buttons.hpp>
//---------------------------------------------------------------------------
class TPaintScheme : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	TSpinEdit *OverallSpinEdit;
	TSpinEdit *TopWingSpinEdit;
	TSpinEdit *BottomWingSpinEdit;
	TSpinEdit *TailSpinEdit;
	TSpinEdit *FuselageSpinEdit;
	TSpinEdit *EmblemSpinEdit;
	TSpinEdit *DetailSpinEdit;
	TBitBtn *BitBtn1;
	TBitBtn *BitBtn2;
	void __fastcall OverallSpinEditChange(TObject *Sender);
	void __fastcall TopWingSpinEditChange(TObject *Sender);
	void __fastcall TailSpinEditChange(TObject *Sender);
	void __fastcall BottomWingSpinEditChange(TObject *Sender);
	void __fastcall FuselageSpinEditChange(TObject *Sender);
	void __fastcall DetailSpinEditChange(TObject *Sender);
	void __fastcall EmblemSpinEditChange(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TPaintScheme(TComponent* Owner);
void	__fastcall TPaintScheme::OpenForm(MEPilotType&	pilot);

};
//---------------------------------------------------------------------------
extern TPaintScheme *PaintScheme;
//---------------------------------------------------------------------------
#endif
