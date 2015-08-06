//---------------------------------------------------------------------------
#ifndef NameListH
#define NameListH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Buttons.hpp>
#include <vcl\ComCtrls.hpp>
#include "Grids.hpp"
#include <vcl\ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TNameListSel : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TPanel *Panel2;
	TBitBtn *BitBtn1;
	TListBox *NameList;
	TPanel *Panel3;
	TEdit *Edit1;
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	
	void __fastcall Edit1Change(TObject *Sender);
///	void __fastcall NameListClick(TObject *Sender);
	
	
	void __fastcall NameListDrawItem(TWinControl *Control, int Index, TRect &Rect,
	TOwnerDrawState State);
	
	void __fastcall NameListMouseDown(TObject *Sender, TMouseButton Button,
	TShiftState Shift, int X, int Y);
private:	// User declarations
public:		// User declarations
	__fastcall TNameListSel(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TNameListSel *NameListSel;
//---------------------------------------------------------------------------
#endif
