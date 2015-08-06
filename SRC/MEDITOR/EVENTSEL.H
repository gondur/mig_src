//---------------------------------------------------------------------------
#ifndef eventselH
#define eventselH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TSelEvent : public TForm
{
__published:	// IDE-managed Components
	TComboBox *ListBox;
	
	
	
	TTimer *Timer1;
	void __fastcall FormShow(TObject *Sender);
	
	
	
	
	
	
	
	
	
	
	void __fastcall ListBoxChange(TObject *Sender);
	
	
	
	void __fastcall Timer1Timer(TObject *Sender);
private:	// User declarations
	int oldval;
	int Height;
public:		// User declarations
	__fastcall TSelEvent(TComponent* Owner);
int   ShowModal(int oldval=0,int stepsize=1);
};
//---------------------------------------------------------------------------
extern TSelEvent *SelEvent;
//---------------------------------------------------------------------------
#endif
 
