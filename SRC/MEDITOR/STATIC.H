//---------------------------------------------------------------------------
#ifndef StaticH
#define StaticH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Buttons.hpp>
//---------------------------------------------------------------------------
class TStaticForm : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *NatLabel;
	TLabel *BandLabel;
	TLabel *ShapeLabel;
	TBitBtn *BitBtn1;
private:	// User declarations
public:		// User declarations
	__fastcall TStaticForm(TComponent* Owner);
	void	__fastcall TStaticForm::OpenForm();
int __fastcall TStaticForm::FindNationality(UniqueID uid);

};
//---------------------------------------------------------------------------
extern TStaticForm *StaticForm;
//---------------------------------------------------------------------------
#endif
 