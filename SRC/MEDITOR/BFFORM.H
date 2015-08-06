//---------------------------------------------------------------------------
#ifndef bfformH
#define bfformH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include "Grids.hpp"
#include <vcl\Buttons.hpp>
#include <vcl\ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TBfieldForm : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TPanel *EditPanel;
	TButton *DeleteButton;
	TButton *ReloadButton;
	TButton *WipeButton;
	TButton *Save;
	TPanel *NewPanel;
	TButton *Load;
	TButton *New;
	TPanel *Panel2;
	TBitBtn *BitBtn2;
	TBitBtn *BitBtn1;
	TPanel *Panel3;
	TStringGrid *BfieldGrid;
	void __fastcall WipeButtonClick(TObject *Sender);
	void __fastcall ReloadButtonClick(TObject *Sender);
	void __fastcall DeleteButtonClick(TObject *Sender);
	
	void __fastcall BfieldGridSelectCell(TObject *Sender, long Col, long Row,
	bool &CanSelect);
	
	
	void __fastcall BfieldGridMouseDown(TObject *Sender, TMouseButton Button,
	TShiftState Shift, int X, int Y);
	void __fastcall LoadClick(TObject *Sender);
	void __fastcall NewClick(TObject *Sender);
	
	void __fastcall SaveClick(TObject *Sender);
private:	// User declarations
	void __fastcall TBfieldForm::Refresh();
    int currsel;
public:		// User declarations
bool	QuerySaveChanges(int bfindex = -1);
bool __fastcall FileNameAvailable(int bfindex);
bool	SaveMission(int bfindex);
bool __fastcall LoadNewClick(bool load);
	__fastcall TBfieldForm(TComponent* Owner);
	void __fastcall TBfieldForm::OpenForm();
#ifdef  FILE_Included
void	LoadBf(int bfindex,FileNum dirnum,char* fname);
FileNum	FakeUserObj(FileNum dirnum,char* filename);
#endif

};
//---------------------------------------------------------------------------
extern TBfieldForm *BfieldForm;
//---------------------------------------------------------------------------
#endif
