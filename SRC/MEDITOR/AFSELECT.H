//---------------------------------------------------------------------------
#ifndef afselectH
#define afselectH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TSelectAirfield : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TBevel *Bevel1;
	TLabel *Label;
	void __fastcall FormMouseDown(TObject *Sender, TMouseButton Button,
	TShiftState Shift, int X, int Y);
	
	void __fastcall FormMouseUp(TObject *Sender, TMouseButton Button,
	TShiftState Shift, int X, int Y);
	void __fastcall FormMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	
private:	// User declarations
	bool	move;
public:		// User declarations
	__fastcall TSelectAirfield(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TSelectAirfield *SelectAirfield;
//---------------------------------------------------------------------------
#endif
 