//---------------------------------------------------------------------------
#ifndef currshpH
#define currshpH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Buttons.hpp>
//---------------------------------------------------------------------------
class TCurrShape : public TForm
{
__published:	// IDE-managed Components
	TLabel *ShapeLabel;
	TComboBox *ShapeComboBox;
	TBitBtn *Ok;
	TBitBtn *Cancel;
private:	// User declarations
public:		// User declarations
	__fastcall TCurrShape(TComponent* Owner);
	void	__fastcall TCurrShape::OpenForm();
};
//---------------------------------------------------------------------------
extern TCurrShape *CurrShape;
//---------------------------------------------------------------------------
#endif
