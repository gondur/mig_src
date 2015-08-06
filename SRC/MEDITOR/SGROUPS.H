//---------------------------------------------------------------------------
#ifndef SGroupsH
#define SGroupsH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include "Grids.hpp"
#include <vcl\Buttons.hpp>
//---------------------------------------------------------------------------
class TSuperGroups : public TForm
{
__published:	// IDE-managed Components
	TStringGrid *SuperGroupGrid;
	TBitBtn *BitBtn1;
	TBitBtn *BitBtn2;
	void __fastcall SuperGroupGridMouseUp(TObject *Sender, TMouseButton Button,
	TShiftState Shift, int X, int Y);
private:	// User declarations
void __fastcall TSuperGroups::Refresh();

public:		// User declarations
	__fastcall TSuperGroups(TComponent* Owner);
	  void __fastcall TSuperGroups::OpenForm();

};
//---------------------------------------------------------------------------
extern TSuperGroups *SuperGroups;
//---------------------------------------------------------------------------
#endif
