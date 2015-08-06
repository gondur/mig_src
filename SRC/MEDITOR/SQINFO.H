//---------------------------------------------------------------------------
#ifndef sqinfoH
#define sqinfoH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\ExtCtrls.hpp>
#include <vcl\Buttons.hpp>
//---------------------------------------------------------------------------
class TSquadronDataForm : public TForm
{
__published:	// IDE-managed Components
	TComboBox *AcComboBox;
	TLabel *AcItemBaseLabel;
	TLabel *AcItemSquadron;
	TLabel *AcItemAircraftLabel;
	TLabel *SqSkillLabel;
	TComboBox *SquadronComboBox;
	TLabel *SqMoraleLabel;
	TLabel *SqChar1Label;
	TComboBox *SkillComboBox;
	TComboBox *MoraleComboBox;
	TComboBox *CharComboBox;
	TBitBtn *Ok;
	TBitBtn *Cancel;
	TButton *HomeBaseButton;
	TEdit *HomeBaseEdit;
	void __fastcall SquadronComboBoxChange(TObject *Sender);
	
	
	void __fastcall HomeBaseButtonClick(TObject *Sender);
private:	// User declarations
//void	TSquadronDataForm::ForceSqadUpdate(int squadnum);
	#ifdef	PERSONS2_Included
void  	TSquadronDataForm::ProcessVar(EventVar& var);
	#endif
	  
public:		// User declarations
	__fastcall TSquadronDataForm(TComponent* Owner);
void	TSquadronDataForm::ForceSqadUpdate(int squadnum);
void	__fastcall TSquadronDataForm::OpenForm();
void	ScanSquad(bool	friends,TStrings& desc);
void	GetSquadName(int sqnum,char* buffer);
void	GetSquadName(bool friends,int sqnum,char* buffer);
	#ifdef	PERSONS2_Included
void	GetSquadInfo(bool	friends,int sqnum,info_event& ev);
void	GetSquadInfo(int sqnum,info_event& ev);
void	ScanSquad(FileNum f,TStrings& desc);
void	GetSquadName(FileNum f,int sqnum,char* buffer);
void	GetSquadInfo(FileNum f,int sqnum,info_event& ev);
void	AddDesc(string src,int len,TokenCode t);

	#endif
char	FullSquadronName[100];
void __fastcall TSquadronDataForm::ExtractSquadName();
void	__fastcall TSquadronDataForm::InitForm();
void __fastcall TSquadronDataForm::SetLandingWP();

int	AcComboBoxItemIndex;					 
int homebase;	
	TStrings*	descs;
//	sel file based on:		area=verd   side=Alies	file=friends
static	FileNum		squadfiles	[2]			[2]			[2];
};
//---------------------------------------------------------------------------
extern TSquadronDataForm *SquadronDataForm;
//---------------------------------------------------------------------------
#endif
