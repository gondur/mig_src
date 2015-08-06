//---------------------------------------------------------------------------
#ifndef EventtxtH
#define EventtxtH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
//---------------------------------------------------------------------------
class TTextEvent : public TForm
{
__published:	// IDE-managed Components
	TEdit *Edit;
	void __fastcall EditClick(TObject *Sender);
	void __fastcall EditKeyPress(TObject *Sender, char &Key);
private:	// User declarations
public:		// User declarations
	__fastcall TTextEvent(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TTextEvent *TextEvent;
//---------------------------------------------------------------------------
#endif
