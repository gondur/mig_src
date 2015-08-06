//---------------------------------------------------------------------------
#ifndef LoadSaveH
#define LoadSaveH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\FileCtrl.hpp>
#include <vcl\Buttons.hpp>
#include <vcl\ExtCtrls.hpp>
//---------------------------------------------------------------------------
enum	FileModes {FM_OpenDirC,FM_NewDirC,FM_OpenDirM,FM_NewDirM,
					FM_OpenFile,FM_NewFile,FM_RenameFile,
					FM_OpenFrom,FM_OpenFromPilot,
                    FM_OpenBfDirs,FM_NewBfDirs,FM_SaveBfDirs,
					FM_Save,FM_SaveAs,FM_SaveDiscard,FM_SaveAsDiscard};
class TFileLoadSave : public TForm
{
	friend	WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR line, int);
__published:	// IDE-managed Components
	TFileListBox *FileListBox1;
	TDriveComboBox *Drive;
	TDirectoryListBox *DirName;
	TBitBtn *Open;
	TBitBtn *Cancel;
	TEdit *Title;
	TBitBtn *Save;
	TBitBtn *New;
	TBitBtn *Rename;
	TBitBtn *Discard;
	TLabel *Description;
	TBitBtn *Name;
	TPanel *Panel1;
	TPanel *Panel2;
	TPanel *Panel3;
	TEdit *FileName;
	TLabel *Label1;
	TLabel *Label2;
	TListBox *PathList;
	void __fastcall FileListBox1DblClick(TObject *Sender);
	void __fastcall FileNameChange(TObject *Sender);
//	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);

	void __fastcall PathListClick(TObject *Sender);
private:	// User declarations
	int			dirnums[32];
	int 		expecting;
	AnsiString	confirm;
	bool		dirmode;
	bool		fakedir;
	FileModes filemode;
	char* ext;
	AnsiString		InputTitle;
bool	TFileLoadSave::Able(TButton* b,bool setting);
public:		// User declarations
//void	DefaultDirectory();
	int		CurrDirNum;
	char*	HomeDir;
	bool	squelchdiscard;
	__fastcall TFileLoadSave(TComponent* Owner);
int __fastcall ShowModal(AnsiString path,AnsiString& currname,AnsiString& currtitle,FileModes mode);
#ifdef	FILE_Included
int __fastcall ShowModal(FileNum path,AnsiString& currname,AnsiString& currtitle,FileModes mode);
#endif

};
//---------------------------------------------------------------------------
extern TFileLoadSave *FileLoadSave;
//---------------------------------------------------------------------------
#endif
