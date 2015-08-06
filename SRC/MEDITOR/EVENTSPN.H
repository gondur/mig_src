//---------------------------------------------------------------------------
#ifndef EventSpinH
#define EventSpinH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include "sampreg.h"
//---------------------------------------------------------------------------
class TSpinEvent : public TForm
{
__published:	// IDE-managed Components
	TSpinEdit *Edit;
	void __fastcall EditDblClick(TObject *Sender);
	void __fastcall EditKeyPress(TObject *Sender, char &Key);
	void __fastcall EditChange(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TSpinEvent(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TSpinEvent *SpinEvent;
//---------------------------------------------------------------------------
#endif
 