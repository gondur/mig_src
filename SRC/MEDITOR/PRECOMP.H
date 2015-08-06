//---------------------------------------------------------------------------
#ifndef PreCompH
#define PreCompH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Buttons.hpp>
//---------------------------------------------------------------------------
class TEditb4Compile : public TForm
{
__published:	// IDE-managed Components
	TBitBtn *PreEdit;
	TBitBtn *BitBtn3;
	TEdit *Edit1;
	TEdit *Edit2;
	TBitBtn *Compile;
	TEdit *TargetName;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	void __fastcall FormShow(TObject *Sender);
	
private:	// User declarations
public:		// User declarations
	__fastcall TEditb4Compile(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TEditb4Compile *Editb4Compile;
//---------------------------------------------------------------------------
#endif
