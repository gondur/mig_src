//---------------------------------------------------------------------------
#ifndef waypointH
#define waypointH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Buttons.hpp>
#include <dosdefs.h>
#include <vcl\ExtCtrls.hpp>
#include <vcl\Mask.hpp>
#include <vcl\ComCtrls.hpp>
#include "sampreg.h"
#include "spin.h"

struct	RodsWayPoint;
struct 	info_waypoint;

struct	TypeData
{
	SWord	climbvel;
	SWord	cruisevel;
	SWord	maxvel;
	SWord	bestclimbpitch;
};

//---------------------------------------------------------------------------
class TWayPointForm : public TForm
{
	friend	class	TMissionEditor;
__published:	// IDE-managed Components
	TGroupBox *WpData;
	TLabel *WpPositionLabel;
	TLabel *WpAltitudeLabel;
	TLabel *WpRangeLabel;
	TLabel *WpAction;
	TEdit *WPAltEdit;
	TEdit *SpeedEdit;
	TEdit *RangeEdit;
	TComboBox *RouteListBox;
	TButton *WpPrev;
	TBitBtn *AcMoveto;
	TButton *WpNext;
	TGroupBox *WPGroupBox;
	TBitBtn *WPBefore;
	TBitBtn *WPAfter;
	TGroupBox *RouteEventGroupBox;
	TBitBtn *EventBefore;
	TBitBtn *EventAfter;
	TComboBox *WPActionComboBox;
	TBitBtn *WpDel;
	TBitBtn *WpUndo;
	TBitBtn *WpAccept;
	TGroupBox *EventData;
	TLabel *FixedOffsetLabel;
	TLabel *PercentLabel1;
	TLabel *RandomOffsetLabel;
	TLabel *PercentLabel2;
	TLabel *RangeLabel;
	TEdit *FixedOffsetEdit;
	TEdit *RandomOffsetEdit;
	TComboBox *EventRangeComboBox;
	TBitBtn *EventMore;
	TBitBtn *WaypointClose;
	TEdit *PositionEdit;
	TButton *PositionButton;
	TComboBox *SpdComboBox;
	TPanel *Panel1;
	TMaskEdit *MaskEdit1;
	TPanel *Panel2;
	TBitBtn *BitBtn1;
	TPanel *Panel3;
	TBitBtn *WpSpeedBtn;
	TEdit *TimeEdit;
	TSpinButton *SpinButton1;
	void __fastcall WPAfterClick(TObject *Sender);
	void __fastcall WpDelClick(TObject *Sender);
	void __fastcall WPBeforeClick(TObject *Sender);
	void __fastcall EventAfterClick(TObject *Sender);
	void __fastcall EventBeforeClick(TObject *Sender);
	void __fastcall RouteListBoxChange(TObject *Sender);
	void __fastcall WPActionComboBoxChange(TObject *Sender);
	
	void __fastcall WpNextClick(TObject *Sender);
	void __fastcall WpPrevClick(TObject *Sender);
	void __fastcall AcMovetoClick(TObject *Sender);
	void __fastcall EventMoreClick(TObject *Sender);


	void __fastcall FixedOffsetEditChange(TObject *Sender);
	void __fastcall RandomOffsetEditChange(TObject *Sender);

	void __fastcall WpAcceptClick(TObject *Sender);
	void __fastcall WPAltEditChange(TObject *Sender);
	void __fastcall WpUndoClick(TObject *Sender);
	void __fastcall PositionButtonClick(TObject *Sender);
	void __fastcall FixedOffsetEditKeyPress(TObject *Sender, char &Key);
	void __fastcall RandomOffsetEditKeyPress(TObject *Sender, char &Key);
	
	void __fastcall FixedOffsetEditKeyDown(TObject *Sender, WORD &Key,
	TShiftState Shift);
	void __fastcall FixedOffsetEditKeyUp(TObject *Sender, WORD &Key,
	TShiftState Shift);
	void __fastcall RandomOffsetEditKeyUp(TObject *Sender, WORD &Key,
	TShiftState Shift);
	void __fastcall EtaSpeedBitBtnClick(TObject *Sender);
	void __fastcall RangeEditChange(TObject *Sender);
	void __fastcall SpeedEditChange(TObject *Sender);
	
	void __fastcall Panel1Click(TObject *Sender);
	void __fastcall SpdComboBoxChange(TObject *Sender);
	
	void __fastcall SpinButton1DownClick(TObject *Sender);
	void __fastcall SpinButton1UpClick(TObject *Sender);
	
	void __fastcall EventRangeComboBoxChange(TObject *Sender);
	void __fastcall WPAltEditExit(TObject *Sender);
	void __fastcall RangeEditExit(TObject *Sender);
	
	
	void __fastcall WpAcceptMouseUp(TObject *Sender, TMouseButton Button,
	TShiftState Shift, int X, int Y);
	void __fastcall WaypointCloseClick(TObject *Sender);
private:	// User declarations
#ifdef   UNIQUEID_Included
public:
void __fastcall TWayPointForm::InsertWPAfter(UniqueID	prevu);
void __fastcall TWayPointForm::InsertWPBefore(UniqueID	nextu);
void __fastcall TWayPointForm::ReposEventWp(UniqueID u);
private:
void __fastcall TWayPointForm::FindNewWPPos(UniqueID u);
void __fastcall TWayPointForm::WPDelete(UniqueID curru);
#endif
//	 void __fastcall TWayPointForm::FindNewWPPos(RodsWayPoint*	wp,SLong prevx,SLong prevy,SLong prevz,
//												SLong nextx,SLong nexty,SLong nextz,int percent);
//	 void __fastcall TWayPointForm::WPDelete(RodsWayPoint*);
	void	__fastcall TWayPointForm::FillRouteList();
void	__fastcall TWayPointForm::FillWpActionList();
void __fastcall TWayPointForm::RefreshWayPointForm();
//void __fastcall TWayPointForm::ReposEventWp(RodsWayPoint* Wp,int offset);
void __fastcall TWayPointForm::AddEventButtons();
void	__fastcall TWayPointForm::FillEventRangeList();
void __fastcall TWayPointForm::SetMoveOnButtons();
void __fastcall TWayPointForm::FixedOffsetEditMade();
void __fastcall TWayPointForm::RandomOffsetEditMade();
void __fastcall TWayPointForm::CalcVel(info_waypoint* W);
void __fastcall TWayPointForm::CalcEta(info_waypoint* W);
int __fastcall TWayPointForm::LegStartTime(info_waypoint* W);
void __fastcall TWayPointForm::OnEtaChange();
int __fastcall TWayPointForm::LegTime (int levelvel,info_waypoint* W);
int __fastcall TWayPointForm::LegVel (int requiredtime,info_waypoint* W);
#ifdef	ANGLES_Included             
ANGLES __fastcall TWayPointForm::BestClimbwrtAlt(info_waypoint* W);
#endif
void __fastcall TWayPointForm::InterceptandRange ();
int  __fastcall TWayPointForm::FindVel( int& vel,info_waypoint* W);
void __fastcall TWayPointForm::EtaUpdate();
void __fastcall TWayPointForm::WpSpeedBtnClick(TObject *Sender);

 

void __fastcall TWayPointForm::NewEventWpPos(int X, int Y);
public:		// User declarations
	__fastcall TWayPointForm(TComponent* Owner);
//void  __fastcall TWayPointForm::InitWayPoint(RodsWayPoint* wp);


//	 RodsWayPoint* __fastcall TWayPointForm::InsertBefore(RodsWayPoint*	oldwp);
//	 RodsWayPoint* __fastcall TWayPointForm::InsertAfter(RodsWayPoint*	oldwp);
//	void __fastcall TWayPointForm::InsertWPAfter(RodsWayPoint* wp );
//	void __fastcall TWayPointForm::InsertWPBefore(RodsWayPoint* wp );
	void	__fastcall TWayPointForm::ShowWpDialog(int X, int Y);

void __fastcall TWayPointForm::PositionEvents();
void __fastcall TWayPointForm::WpDelete();
void __fastcall TWayPointForm::ResetTargetAction();
	  
bool WayPointFormEdits;
	SLong	Range;
	SWord	HdgIntercept;
	SWord	PitchIntercept;
   int wpvel;
   int wprange;
   int etas;
};
//---------------------------------------------------------------------------
extern TWayPointForm *WayPointForm;
//---------------------------------------------------------------------------
#endif
