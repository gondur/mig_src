//---------------------------------------------------------------------------
#ifndef MissionTextH
#define MissionTextH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\ComCtrls.hpp>
#include <vcl\Buttons.hpp>
//---------------------------------------------------------------------------
class TMissionTextDlg : public TForm
{
__published:	// IDE-managed Components
	TPageControl *MissionTextPageControl;
	TTabSheet *MissionDescriptionSheet;
	TTabSheet *NewsTextSheet;
	TMemo *MissionDescriptionText;
	TBitBtn *MissionTextOk;
	TBitBtn *MissionTextCancel;
	TMemo *MissionNewsText;
	void __fastcall FormActivate(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TMissionTextDlg(TComponent* Owner);
	void __fastcall TMissionTextDlg::OpenForm();

};
//---------------------------------------------------------------------------
extern TMissionTextDlg *MissionTextDlg;
//---------------------------------------------------------------------------
#endif
 