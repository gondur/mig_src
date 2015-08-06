//---------------------------------------------------------------------------
#ifndef infoH
#define infoH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Buttons.hpp>
//---------------------------------------------------------------------------
class TInfoForm : public TForm
{
__published:	// IDE-managed Components
	TBitBtn *BitBtn1;
	TMemo *Memo1;
private:	// User declarations
public:		// User declarations
	__fastcall TInfoForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TInfoForm *InfoForm;
//---------------------------------------------------------------------------
#endif
