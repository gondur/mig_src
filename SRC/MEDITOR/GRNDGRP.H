//---------------------------------------------------------------------------
#ifndef GroungGrpH
#define GroungGrpH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Buttons.hpp>
#include <vcl\ExtCtrls.hpp>
#include "sampreg.h"


//---------------------------------------------------------------------------
class TGroundGroupForm : public TForm
{
__published:	// IDE-managed Components
	TLabel *GG_StatusLabel;
	TComboBox *GG_StatusComboBox;
	TPanel *GGPanel;
	TLabel *GGSpeedLabel;
	TLabel *GGFormationSizeLabel;
	TLabel *GGFormationTypeLabel;
	TEdit *GGSpeedData;
	TComboBox *GGFormTypeBox;
	TEdit *GGEditAlt;
	TLabel *GGAltLabel;
	TPanel *ButtonPanel;
	TComboBox *ShapeComboBox;
	TBitBtn *GGEventMore;
	TBitBtn *GGRoute;
	TBitBtn *GGDelete;
	TBitBtn *GGCancel;
	TBitBtn *GGOk;
	TComboBox *SpdComboBox;
	TPanel *Panel1;
	TLabel *Battlefield;
	TLabel *Super;
	TLabel *BfieldLabel;
	TLabel *Label1;
	TLabel *Label3;
	TLabel *Label4;
	TEdit *Edit_UID;
	TEdit *Edit_Title;
	TMemo *Memo_Description;
	TBitBtn *SuperGroupButton;
	TComboBox *SuperGroupCombo;
	TSpinEdit *GGFormationSpinEdit;
	TSpinButton *AltSpinButton;
	TComboBox *UIDGroupCombo;
	TLabel *Label2;
	TComboBox *ShapeCat;
	void __fastcall GG_StatusComboBoxChange(TObject *Sender);
	
	

	
	void __fastcall EventMoreClick(TObject *Sender);
	void __fastcall GGFormationSpinEditChange(TObject *Sender);
	
	void __fastcall SpdComboBoxChange(TObject *Sender);
	void __fastcall GGSpeedDataChange(TObject *Sender);
//	void __fastcall SpinButton1DownClick(TObject *Sender);
//	void __fastcall SpinButton1UpClick(TObject *Sender);
	
	
	
	void __fastcall SuperGroupButtonClick(TObject *Sender);
	void __fastcall SuperGroupComboChange(TObject *Sender);
	void __fastcall Edit_TitleClick(TObject *Sender);
	
	void __fastcall AltSpinButtonDownClick(TObject *Sender);
	void __fastcall AltSpinButtonUpClick(TObject *Sender);
	
	
	void __fastcall Edit_UIDExit(TObject *Sender);
	void __fastcall Edit_TitleEnter(TObject *Sender);
	void __fastcall Edit_TitleExit(TObject *Sender);
	void __fastcall Memo_DescriptionEnter(TObject *Sender);
	void __fastcall Memo_DescriptionExit(TObject *Sender);


	void __fastcall ShapeCatChange(TObject *Sender);
private:	// User declarations
	int	dialheight[2][3];
	void	__fastcall TGroundGroupForm::CheckandSetRoute();
	void __fastcall TGroundGroupForm::CheckSpeedField();
	void __fastcall TGroundGroupForm::RefreshSpeedInfo();
	 void __fastcall TGroundGroupForm::RefreshText();
     void __fastcall TGroundGroupForm::EditText();
	void	FillUIDBandList(int value);

public:		// User declarations
   int currshapecat;
	__fastcall TGroundGroupForm(TComponent* Owner);
void __fastcall TGroundGroupForm::OpenGroundGroupEvent(int X,int Y);
void __fastcall TGroundGroupForm::OpenGroundGroupMobile(int X,int Y);
void __fastcall TGroundGroupForm::OpenGroundGroupStatic(int X,int Y);
void __fastcall TGroundGroupForm::ValidSpinEdit(TSpinEdit *editbox);
int __fastcall TGroundGroupForm::FindShapes(int currshape,int& groupindex,int page);
int __fastcall TGroundGroupForm::GeneralFindShapes(int currshape);

int	grndvel;
};
//---------------------------------------------------------------------------
extern TGroundGroupForm *GroundGroupForm;
extern TComboBox *GG_StatusComboBox;
//---------------------------------------------------------------------------
#endif
 