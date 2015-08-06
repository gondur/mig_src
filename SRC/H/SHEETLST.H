//------------------------------------------------------------------------------
//Filename       sheetlst.h
//System         
//Author         Jim Taylor
//Date           Wed 22 Nov 1995
//Description    Lists all the MakeSheet routines for inclusion into UISHeet def
//				Should only be included into UI.H
//------------------------------------------------------------------------------
#bollocks
#ifndef	SHEETLST_Included
#define	SHEETLST_Included

#define	DEFAULT_SHEETLST 0





#ifndef	UI_Included
#error
#else
#


#include "msn_ctrl.h"											//RDH 17Jul96


//--------------------------------
//'base' sheets. No inputs allowed!!! 
//These must match BaseSheetDefType: 
//	no parameters - return is UISheetPtr constructed
//--------------------------------
static UISheetPtr	RequestExitGame();

static UISheetPtr	MakeFirstSelectSheet();
static UISheetPtr	MakeFirstSelectFirstTimeSheet();
	 static UISheetPtr	MakeScrambleSheet();
	 static UISheetPtr	MakeRealScrambleSheet();
	 static UISheetPtr	MakeSelectAircraftSheet();
//DeadCode RDH 16Jan97 	 static UISheetPtr	MakeCrcIntroSheet();					//RDH 07Dec95
	 static UISheetPtr	MakeCampIntroSheet();
	 static UISheetPtr	MakeCombatReportSheet();
	 static UISheetPtr	MakeSpecialSheet();
	 static UISheetPtr	MakeHatIntroSheet();
	 static UISheetPtr	MakeSOIntroSheet();
	 static UISheetPtr	MakeTnkIntroSheet();
	 static UISheetPtr	MakeCampaignSelectSheet();
	 static UISheetPtr	MakeScreenSheet();
	 static UISheetPtr	MakeAceListSheet();	
	 static UISheetPtr	MakePhaseSelectSheet();
	 static UISheetPtr	MakeCreditsSheet();
	 static UISheetPtr	MakeH2HmainSheet();

//DeadCode RDH 19Feb97 	 static UISheetPtr	MakeBackGroundSheet();					//RDH 07Dec95
//DeadCode RDH 19Feb97 	 static UISheetPtr	MakeHatMissionsSheet();						//RDH 01Apr96
//DeadCode RDH 17Feb97 	 static UISheetPtr	MakeFlightBoardSheet();						//RDH 09Aug96
//DeadCode RDH 17Feb97 	 static UISheetPtr	MakeSquadronBoardSheet();						//RDH 09Aug96
//DeadCode RDH 17Feb97 	 static UISheetPtr	RepeatSquadronBoardSheet();						//RDH 09Aug96
	 static UISheetPtr	MakePreferencesSheet();						//RDH 05Jan96
	 static UISheetPtr	MakeControlRoomSheet();						//RDH 05Jan96
	 static UISheetPtr	MakeMapSheet();						//RDH 05Jan96
//DeadCode RDH 11Feb97 	 static UISheetPtr	MakeUiMapSheet();							//RDH 04Mar96
//DeadCode RDH 11Feb97 	 static UISheetPtr	MakeTnkMapSheet();							//RDH 04Mar96
	 static UISheetPtr	MakeSOMapSheet();							//RDH 04Mar96
//DeadCode RDH 24Mar97 	 static UISheetPtr	MakePaintShopSheet();						//RDH 15Feb96
	 static UISheetPtr	MakeSpecialEventSheet();					//RDH 26Jan96
	 static UISheetPtr	MakeLostCampaignSheet();					//RDH 26Jan96
	 static UISheetPtr	MakeEndCampaignSheet();					//RDH 26Jan96
	 static UISheetPtr	MakeLostAnimSheet();					//RDH 26Jan96
	 static UISheetPtr	MakeState3dOnGoing();
	 static UISheetPtr	MakeP3dSheet();							//RDH 25Jan96
	 static UISheetPtr	RptP3dSheet();							//RDH 25Jan96
	 static UISheetPtr	MakeFullScrnSmk(FileNum f,SheetMake	NextMake);							//RDH 05Feb96
	 static UISheetPtr	MakeMIntFullScrnSmk();					//RDH 09Feb96
	 static UISheetPtr	MakeIntroAnimFullScrnSmk();					//RDH 09Feb96
	 static UISheetPtr	MakeDemoAnimFullScrnSmk();					//RDH 09Feb96
	 static UISheetPtr	MakeFirstTimeDemoAnimFullScrnSmk();			//RDH 01May96
	 static UISheetPtr	MakeCrcFullScrnSmk();							//RDH 05Feb96
	 static UISheetPtr	MakeHatFullScrnSmk();							//RDH 05Feb96
	 static UISheetPtr	MakeHatDebriefFullScrnSmk();				//RDH 13Feb96
	 static UISheetPtr	MakeSODebriefFullScrnSmk();				//RDH 13Feb96
	 static UISheetPtr	MakeSOFullScrnSmk();							//RDH 05Feb96
	 static UISheetPtr	MakeTnkFullScrnSmk();							//RDH 05Feb96
	 static UISheetPtr	MakeTnkDebriefFullScrnSmk();				//RDH 13Feb96
	 static UISheetPtr	MakeLostAnimFullScrnSmk();							//RDH 05Feb96
	 static UISheetPtr	MakeWonAnimFullScrnSmk();							//RDH 05Feb96
//DeadCode RDH 16Jan97 	 static UISheetPtr	MakeNewsSheet();							//JIM 15Apr96
	 static UISheetPtr	MakeHatNewsSheet();							//JIM 15Apr96
	 static UISheetPtr	MakeAfter3d();								//JIM 15Apr96
	 static UISheetPtr	MakeHardConfigSheet();						//DAW 29Apr96
	 static UISheetPtr	MakeAilMainNew();							//DAW 12Aug96
	 static UISheetPtr	MakeInstExitSheet();						//DAW 16Aug96

//--------------------------------
//'child' and 'sibling' sheets. Whatever parameters you need. 
//The return is static UISheetPtr constructed.
//--------------------------------

	 static UISheetPtr	MakeEditNameSheet(ScreenXY,const Window&);
	 static UISheetPtr	MakeHatMsnSelSheet(ScreenXY,const Window&);	//RDH 12Jan96
	 static UISheetPtr	MakeHistorySheet(ScreenXY,ScreenWH,const Window&);						//RDH 05Jan96
//DeadCode RDH 19Feb97 	 static UISheetPtr	MakeMissionIntroSheet(ScreenXY,ScreenWH,const Window&);						//RDH 05Jan96
	 static UISheetPtr	MakeSaveGameSheet(ScreenXY,const Window&);							//RDH 05Jan96
//DeadCode RDH 26Mar97 	 static UISheetPtr	MakeFlightSheet(ScreenXY,ScreenWH,const Window&,SWord YOffset,SWord XOffset,SWord titlecolour,SWord flightcolour,SWord pilotcolour,FlightInfoSelection& flightinfoselection);	//RDH 12Jan96
	 static UISheetPtr	MakeRecordsSheet(ScreenXY,const Window&, CtrlVar& ctrlvar);	
//DeadCode RDH 26Mar97 	 static UISheetPtr	MakeConfigureSheet(ScreenXY,const Window&, CtrlVar& ctrlvar);
	 static UISheetPtr	MakeIn3dMapSheet(ScreenXY,const Window&, CtrlVar& ctrlvar);//RDH 25Jan96
	 static UISheetPtr	MakeChangeSquadOrdersSheet(ScreenXY,ScreenWH,const Window&, SWord CurrOrder,SWord taggedflight);//RDH 11Aug96
	 static UISheetPtr	MakeChangeOrdersSheet(ScreenXY,ScreenWH,const Window&, SWord CurrOrder,SWord taggedpilot);//RDH 11Aug96
	 static UISheetPtr	MakeFlightParamsSheet(ScreenXY,ScreenWH,const Window&);//RDH 25Jan96
	 static UISheetPtr	MakeGameDiffSheet(ScreenXY,ScreenWH,const Window&);//RDH 25Jan96
	 static UISheetPtr	MakeTitleLoadGameSheet(ScreenXY,const Window&,CtrlVar& ctrlvar);//RDH 25Jan96
	 static UISheetPtr	MakeSfxConfigSheet(ScreenXY,const Window&);//RDH 25Jan96
	 static UISheetPtr	MakeInputConfigSheet(ScreenXY,ScreenWH,const Window&, ConfigureSelection& configureselection);//RDH 25Jan96
	 static UISheetPtr	MakeScreenResSheet(ScreenXY,ScreenWH,const Window&, ConfigureSelection& configureselection);//RDH 22Oct96
	 static UISheetPtr	MakeScreenResTestSheet(ScreenXY,ScreenWH,const Window&, ConfigureSelection& configureselection);//RDH 22Oct96

	 static UISheetPtr	MakeGraphicsConfigSheet(ScreenXY,const Window&);//RDH 25Jan96
	 static UISheetPtr	MakeJoyStickSheet(ScreenXY,const Window&);						//RDH 05Jan96

//DeadCode RDH 13Feb97 	 static UISheetPtr	MakeHatMsnTypeIconSheet(ScreenXY,const Window&, CtrlVar& ctrlvar);//RDH 25Jan96

//DeadCode RDH 19Feb97 	 static UISheetPtr	MakeMainSheet(ScreenXY,const Window&, CtrlVar& ctrlvar);//RDH 25Jan96
	 static UISheetPtr	MakeDrawMapSheet(ScreenXY,const Window&, CtrlVar& ctrlvar);
	 static UISheetPtr	MakeIntellSummarySheet();					//RDH 07Apr97
	 static UISheetPtr	MakeResourceSummarySheet();					//RDH 07Apr97
	 static UISheetPtr	MakePackageSheet(SWord package);
	 static UISheetPtr	MakeTypeInfoSheet(SWord flags,SWord package);
	 static UISheetPtr	MakePreDefinedPackageInfoSheet(ScreenXY,ScreenWH,const Window&,SWord flags,SWord package);
	 static UISheetPtr	MakeComponentInfoSheet(SWord flags,SWord package,SWord component);
//DeadCode RDH 19Feb97 	 static UISheetPtr	MakePackage1SummarySheet(ScreenXY,ScreenWH,const Window&);
//DeadCode RDH 19Feb97 	 static UISheetPtr	MakePackage2SummarySheet(ScreenXY,ScreenWH,const Window&);
//DeadCode RDH 19Feb97 	 static UISheetPtr	MakePackage3SummarySheet(ScreenXY,ScreenWH,const Window&);
//DeadCode RDH 19Feb97 	 static UISheetPtr	MakePackage4SummarySheet(ScreenXY,ScreenWH,const Window&);
//DeadCode RDH 08Apr97 	 static UISheetPtr	MakeHardwareSheet(ScreenXY,ScreenWH,const Window&);
	 static UISheetPtr	MakeHardwareChoiceSheet(ScreenXY,ScreenWH,const Window&);
//DeadCode RDH 08Apr97 	 static UISheetPtr	MakeGameDifficultySheet(ScreenXY,ScreenWH,const Window&);
//DeadCode RDH 08Apr97 	 static UISheetPtr	MakeFlightDifficultySheet(ScreenXY,ScreenWH,const Window&);
//DeadCode RDH 08Apr97 	 static UISheetPtr	MakePaintDrwSheet(ScreenXY,ScreenWH,const Window&);
//DeadCode RDH 08Apr97 	 static UISheetPtr	MakePersonnelDrwSheet(ScreenXY,ScreenWH,const Window&);
	 static UISheetPtr	MakePaintRequestSheet(ScreenXY,ScreenWH,const Window&);
	 static UISheetPtr	MakePersonnelSheet(ScreenXY,ScreenWH,const Window&);

	 static UISheetPtr	MakePackageSummarySheet();					//RDH 07Apr97
	 static UISheetPtr	MakeIntellSheet();							//RDH 07Apr97
	 static UISheetPtr	MakeResourceSheet(Squadron squadron);
//DeadCode RDH 04Apr97 	 static UISheetPtr	MakeListSheet(ScreenXY,ScreenWH,const Window&,
//DeadCode RDH 04Apr97 						SWord& currentry,TextRef thelist,SWord base = 0,
//DeadCode RDH 04Apr97 						SWord Flags = PASSIVE,SWord package = 0, CtrlVar& ctrlvar);
//DeadCode RDH 04Apr97 	 static UISheetPtr	MakeList2Sheet(ScreenXY,ScreenWH,const Window&,
//DeadCode RDH 04Apr97 						SWord& currentry,TextRef thelist,SWord base = 0,
//DeadCode RDH 04Apr97 						SWord Flags = PASSIVE,SWord package = 0, CtrlVar& ctrlvar);
	 static UISheetPtr	MakeListSheet(
						SWord& currentry,TextRef thelist,SWord base,
						SWord Flags,SWord package, CtrlVar& ctrlvar);
	 static UISheetPtr	MakeList2Sheet(ScreenXY,ScreenWH,const Window&,
						SWord& currentry,TextRef thelist,SWord base,
						SWord Flags,SWord package, CtrlVar& ctrlvar);
	 static UISheetPtr	MakePilotListSheet(ScreenXY,ScreenWH,const Window&,
						SWord numinlist,SWord& currentry,SWord base = 0);
	 static UISheetPtr	MakeTargetInfoSheet();						//RDH 07Apr97
	 static UISheetPtr	MakeOriginatorSheet();						//RDH 07Apr97
	 static UISheetPtr	MakeTargetDescriptionSheet();				//RDH 07Apr97
	 static UISheetPtr	MakeMiGActivitySheet();
	 static UISheetPtr	MakeAAAActivitySheet();
	 static UISheetPtr	MakeStatusSheet();

	 static UISheetPtr	MakeTargetTopLineSheet(ScreenXY,ScreenWH,const Window&);
	 static UISheetPtr	MakeDisplayMapSizeSheet(ScreenXY,ScreenWH,const Window&);
	 static UISheetPtr	MakeDisplayRangesSheet(ScreenXY,ScreenWH,const Window&);
	 static UISheetPtr	MakeDisplayItemsSheet(ScreenXY,ScreenWH,const Window&);



	 static UISheetPtr	MakeIntroMainSheet(ScreenXY,const Window&, CtrlVar& ctrlvar);//RDH 25Jan96
	 static UISheetPtr	MakeCRIconSheet(ScreenXY,const Window&, CtrlVar& ctrlvar);//RDH 25Jan96
	 static UISheetPtr	MakeSpecialIconSheet(ScreenXY,const Window&, CtrlVar& ctrlvar);//RDH 25Jan96
	 static UISheetPtr	MakeLostIconSheet(ScreenXY,const Window&, CtrlVar& ctrlvar);//RDH 25Jan96
	 static UISheetPtr	MakeEndIconSheet(ScreenXY,const Window&, CtrlVar& ctrlvar);//RDH 25Jan96
//DeadCode RDH 26Mar97 	 static UISheetPtr	MakeSquadSheet(ScreenXY,const Window&, CtrlVar& ctrlvar);//RDH 25Jan96
	 static UISheetPtr	MakeSaveIconSheet(ScreenXY,const Window&, CtrlVar& ctrlvar);//RDH 25Jan96
	 static UISheetPtr	MakeLoadIconSheet(ScreenXY,const Window&, CtrlVar& ctrlvar);//RDH 25Jan96
//DeadCode RDH 04Apr97 	 static UISheetPtr	MakeNewsIconSheet(ScreenXY,const Window&, CtrlVar& ctrlvar);//RDH 25Jan96
	 static UISheetPtr	MakeQuitIconSheet(ScreenXY,const Window&, CtrlVar& ctrlvar);//RDH 25Jan96
	 static UISheetPtr	MakeMultiplayerChoiceSheet(ScreenXY,const Window&, CtrlVar& ctrlvar);
	 static UISheetPtr	MakeMultiplayerEnterNameSheet(ScreenXY,const Window&, CtrlVar& ctrlvar);
	 static UISheetPtr	MakeMultiplayerGameChoiceSheet(ScreenXY,const Window&, CtrlVar& ctrlvar);
	 static UISheetPtr	MakeMultiplayerDialWaitChoiceSheet(ScreenXY,const Window&, CtrlVar& ctrlvar);



//DeadCode RDH 13Feb97 	 static UISheetPtr	MakeHatMsnTypeInfoSheet();//RDH 25Jan96
//DeadCode RDH 13Feb97 	 static UISheetPtr	MakeHatMissionInfoSheet();//RDH 25Jan96
//DeadCode RDH 13Feb97 	 static UISheetPtr	MakeHatMsnSelInfoSheet ();//RDH 25Jan96
friend	class	BackGroundSheet;
friend	class	CampIntroSheet;
friend	class	CombatReportSheet;
friend	class	SpecialSheet;

//DeadCode RDH 26Mar97 	 static UISheetPtr	MakeFlightInfoSheet ();//RDH 25Jan96
	 static UISheetPtr	MakeMissionInfoSheet();//RDH 25Jan96
//DeadCode RDH 04Apr97 	 static UISheetPtr	MakeNewsInfoSheet   ();//RDH 25Jan96
	 static UISheetPtr	MakeSaveInfoSheet   ();//RDH 25Jan96
	 static UISheetPtr	MakeLoadInfoSheet   ();//RDH 25Jan96
	 static UISheetPtr	MakeQuitInfoSheet   ();//RDH 25Jan96

	 static UISheetPtr	MakeObjectivesInfoSheet();					//RDH 20Jul96
	 static UISheetPtr	MakeCombatReportInfoSheet();					//RDH 20Jul96
	 static UISheetPtr	MakeSpecialInfoSheet();					//RDH 20Jul96
	 static UISheetPtr	MakeLostInfoSheet();					//RDH 20Jul96
	 static UISheetPtr	MakeEndInfoSheet();					//RDH 20Jul96
	 static UISheetPtr	MakeFirstMissionInfoSheet();				//RDH 20Jul96
	 static UISheetPtr	MakeInputNameSheet();					//RDH 20Jul96



	 static UISheetPtr	MakeTnkSquadronSheet(ScreenXY,const Window&, SquadPanelSelection& squadpanelselection);//RDH 26Feb96
//DeadCode RDH 13Feb97 	 static UISheetPtr	MakeTnkPopUpSheet(ScreenXY,const Window&,UniqueID subjectuid);	//RDH 01Mar96
//DeadCode RDH 13Feb97 	 static UISheetPtr	MakeTnkWpPopUpSheet(ScreenXY,const Window&,SWord	wpnum);	//RDH 01Mar96
//DeadCode RDH 13Feb97 	 static UISheetPtr	MakeWPPopUpSheet(ScreenXY,const Window&,UniqueID subjectuid);	//RDH 01Mar96
	 static UISheetPtr	MakeSureSheet(ScreenXY,const Window&,Bool& is_sure,TextRef questiontext,FileNum sheetart,Colour textcolour);//RDH 20Feb96
	 static UISheetPtr	MakeH2HUnavailableSheet(ScreenXY,const Window&);//RDH 02Oct96
	 static UISheetPtr	MakeH2HNewPlayerErrorSheet(ScreenXY,const Window&,ULong retvar);//RDH 02Oct96
	 static UISheetPtr	MakeH2HNewSessionErrorSheet(ScreenXY,const Window&,ULong retvar);//RDH 02Oct96
	 static UISheetPtr	MakeJoyErrorSheet(ScreenXY,const Window&,Bool& is_sure,TextRef warnerrortext,FileNum sheetart,int page);//RDH 23Apr96
	 static UISheetPtr	MakeInfoPanelSheet(ScreenXY,const Window&, SWord& infolines);//PD 04Sep96
	static UISheetPtr	MakeSmackWin(const Window* window,const ScreenXY &XY,const ScreenWH &WH,FileNum f);//DAW 05Feb96
	static UISheetPtr	MakePaint3DWin(const Window* window,const ScreenXY &XY,const ScreenWH &WH,SWord actype,SLong ImageMapTable[6]);//MGA 23Feb96
	 static UISheetPtr	MakeCopyingSheet(ScreenXY,const Window&,Install&);//DAW 08Apr96
	 static UISheetPtr	MakeDrvCngSheet(ScreenXY,const Window&,char *,int *);//DAW 09Apr96
	 static UISheetPtr	MakeSizeSheet(ScreenXY,const Window&,Install&);//DAW 19Apr96
	 static UISheetPtr	MakeSoundSheet(ScreenXY,const Window&,Install&);//DAW 19Apr96
	 static UISheetPtr	MakeGrafixSheet(ScreenXY,const Window&,Install&);//DAW 19Apr96
	 static UISheetPtr	MakeAilMain(ScreenXY,const Window&);		//DAW 11Jul96
	static UISheetPtr	MakeSureFileSheet(ScreenXY topleft,const Window& parent,FileNum *fn);

//--------------------------------
//Public 'global' UI service routines
//
//--------------------------------
//The following basic draw library routines can be found in ui\uitools.cpp:
//
void	Border(UIComponent& a,Colour	C);
void	InDentBorder(UIComponent& a,Colour	dark,Colour	light);
void	OutDentBorder(UIComponent& a,Colour	dark,Colour	light);
void	ShadeComp(UIComponent& UIC,Colour C);
void	DisabledBackground(UIComponent& UIC);	//disabled icon draw
void	RefreshBackground(UIComponent& UIC);	//enabled icon draw
void	HilightBackground(UIComponent& UIC);	//current icon draw
static void	XX_RefreshBackground(UISheet*,UIComponent& UIC);	//enabled icon draw
static void	XX_HilightBackground(UISheet*,UIComponent& UIC);	//current icon draw
void	ActionedBackground(UIComponent& UIC);	//current icon draw when on child
static	void	DrawHiPickup(UISheet*,ListEltComp& UIC);
static	void	DrawPickup(UISheet*,ListEltComp& UIC);
static	void	ScrollPickup(UISheet*,ListEltComp& UIC);
static	void	DoScroll(UISheet*,ListEltComp& UIC);
static	void	ListSlct(UISheet*,ListEltComp& UIC);
static	void	ListHi(UISheet*,ListEltComp& UIC);
static	void	ListDeHi(UISheet*,ListEltComp& UIC);
static	void	DrawScroll(UISheet*,ListEltComp& UIC);
static	void	DrawHiScroll(UISheet*,ListEltComp& UIC);
static	void	RefreshListValue(UISheet*,ListEltComp& UIC,int value);
	Bool	IsListValue(ListEltComp& UIC);
	void	RepositionScrollBar(UIListDescComp*	listctrl);
void	SlideAnimate(UIComponent& UIC,Window*&childwin,int&slidepos,UISheetPtr& curri,CtrlVar&	ctrlvar,Bool hand);

//The following basic draw library routines can be found in ui\uigen.cpp:
//
//
void	Draw_Date(UIComponent& UIC);	
void	SelectFont(UIComponent& UIC);			//RDH 20Jul96
void	SelectLightFont(UIComponent& UIC);			//RDH 20Jul96
void	SelectDarkFont(UIComponent& UIC);							//RDH 04Aug96
SWord	FindIconType (UniqueIDBand uidband);
SWord 	FindNoInList (TextRef thelist);
void	IncNumOfFlights(SLong package,SLong component);
void	DecNumOfFlights(SLong package,SLong component);
void	RecoverFlightsAllocated(SLong package);
void	AllocAircraft(UIComponent& UIC,SWord value,Squadron currsquadron);
void	DeAllocAircraft(UIComponent& UIC,SWord value,Squadron currsquadron);
void	ProcessFlightsUsed(SLong package);
void	Draw_Time(UIComponent& UIC);	
void	NewsOnlyInBox(UIComponent& UIC,NewsEvent currentnewsitem,
		SWord screenx,SWord screeny,SWord screenw,SWord screenh);//RDH 11Jul96
void	SetUpCampaign ();

void	Draw_SquadName(UIComponent& UIC,Squadron currsquadron);
void	Draw_AcType(UIComponent& UIC,Squadron currsquadron);
void	ClearListControl();



void DrawTextLo(UIComponent& UIC);
void DrawTextHi(UIComponent& UIC);
void DrawWingListText(UIComponent& UIC, SWord CurrWing);
void DrawIncIconHi(UIComponent& UIC);
void DrawIncIconLo(UIComponent& UIC);


void 	DrawSelectableLo (UIComponent& UIC);
void 	DrawSelectableHi (UIComponent& UIC);
void 	DrawPackageType (UIComponent& UIC,SWord value);
void 	DrawDuty (UIComponent& UIC,SWord package,SWord component);
SWord	FindPredefined (FamilyType familytype,Type type);
SWord	FindAcAlloc(UIComponent&UIC,SWord value,Squadron currsquadron);


Bool 	PrevNews (NewsEvent &currentnewssrc);
static Bool 	NextNews (NewsEvent &currentnewssrc);
void	ReturnToJunction ();									//RDH 15Feb96
void	GeneralCampaignGoTo3d ();								//RDH 15Jun96
static void	GeneralCampaignGoTo3dSub ();						//RDH 18Jun96



//game logic routines in noderev.cpp

void NodeReview();


//The following basic routines were written by dave...
		UWord	SmackNoPal(Smack *smk);							//DAW 09Feb96
		UWord	SmackFull(Smack *smk);							//DAW 09Feb96
		Smack*	OpenSmack(FileNum filenumber);					//DAW 09Feb96

//--------------------------------
//Some coordinates that used to be in SHEETTOP. No, I don't know why!

enum	CompCoords
{	
 	POPUPW 				= PIXEL640 * 250,
 	POPUPH 				= PIXEL640 * 200,
 	HATMSNSELX			= PIXEL640 * 166,
 	HATMSNSELY			= PIXEL640 * 0,
 	EDITNAMEX			= PIXEL640 * 350, 			//RDH 04Apr96
 	EDITNAMEY			= PIXEL640 * 160, 			//RDH 04Apr96
		SUREDIALOGUEW		= PIXEL640 * 302,			//RDH 20Feb96
		SUREDIALOGUEH		= PIXEL640 * 138,			//RDH 20Feb96
 	TNKOPPSX			= PIXEL640 * 426,
 	TNKOPPSW			= PIXEL640 * 214,
 	TNKOPPSH			= PIXEL640 * 480,
 	MAPW				= PIXEL640 * 558,
 	MAPH				= PIXEL640 * 469,
 	MSNW				= PIXEL640 * 335,
 	MSNH				= PIXEL640 * 480,
 	HATSQUADPNLX		= PIXEL640 * 0, 			//RDH 08Mar96
 	HATSQUADPNLY		= PIXEL640 * 0,
 	HATSQUADPNLW		= PIXEL640 * 640,
 	HATSQUADPNLH		= PIXEL640 * 480,
 	SOSQUADPNLX 		= PIXEL640 * 510,
 	SOSQUADPNLY 		= PIXEL640 * 0,
 	SOSQUADPNLW 		= PIXEL640 * 130,
 	SOSQUADPNLH 		= PIXEL640 * 480,
 	CRCSQUADPNLX		= PIXEL640 * 518,
 	CRCSQUADPNLY		= PIXEL640 * 0,
 	CRCSQUADPNLW		= PIXEL640 * 122,
 	CRCSQUADPNLH		= PIXEL640 * 269,
 	TNKSQUADPNLX		= PIXEL640 * 0,
 	TNKSQUADPNLY		= PIXEL640 * 82,
 	TNKSQUADPNLW		= PIXEL640 * 640,
 	TNKSQUADPNLH		= PIXEL640 * 280,
 	COPYDIALOGUEX		= PIXEL640 * 0,	 			//DAW 08Apr96
 	COPYDIALOGUEY		= PIXEL640 * 0,
 	COPYDIALOGUEW		= PIXEL640 * 640,
 	COPYDIALOGUEH		= PIXEL640 * 480,
 	HATMSNW				= PIXEL640 * 474,
 	HATMSNH				= PIXEL640 * 480,
	CONFIGUREX			= PIXEL640 * 0,
	CONFIGUREY			= PIXEL640 * 0,
	CONFIGUREW			= PIXEL640 * 640,
	CONFIGUREH			= PIXEL640 * 480,
	HATMAINX			= PIXEL640 * 517,
	HATMAINY			= PIXEL640 * 0,
	HATMAINW			= PIXEL640 * 123,
	HATMAINH			= PIXEL640 * 269,
	JUNCTIONICONX			= PIXEL640 * 517,
	JUNCTIONICONY			= PIXEL640 * 0,
	JUNCTIONICONW			= PIXEL640 * 123,
	JUNCTIONICONH			= PIXEL640 * 269,

	DRAWMAPX			= PIXEL640 * 184,
	DRAWMAPY			= PIXEL640 * 24,
	DRAWMAPW			= PIXEL640 * 448,
	DRAWMAPH			= PIXEL640 * 448,

	FOLDERX				= PIXEL640 * 0, 
	FOLDERY				= PIXEL640 * 30, 
	FOLDERW				= PIXEL640 * 184, 
	FOLDERH				= PIXEL640 * 450,

	ICONW = PIXEL640 * 34,	
	ICONH = PIXEL640 * 24,

	MAPTOPLINEX = PIXEL640 * 324,	
	MAPTOPLINEY = PIXEL640 * 0,	
	MAPTOPLINEW = PIXEL640 * 316,	
	MAPTOPLINEH = PIXEL640 * 24,


	FLIGHTPARAMSX			= PIXEL640 * 7,
	FLIGHTPARAMSY			= PIXEL640 * 55,
	FLIGHTPARAMSW			= PIXEL640 * 504,
	FLIGHTPARAMSH			= PIXEL640 * 320,
//DeadCode RDH 26Mar97 	GAMEDIFFX			= PIXEL640 * 8,
//DeadCode RDH 26Mar97 	GAMEDIFFY			= PIXEL640 * 28,
//DeadCode RDH 26Mar97 	GAMEDIFFW			= PIXEL640 * 624,
//DeadCode RDH 26Mar97 	GAMEDIFFH			= PIXEL640 * 400,
	TITLELOADGAMEX		= PIXEL640 * 157,
	TITLELOADGAMEY		= PIXEL640 * 6,
	TITLELOADGAMEW		= PIXEL640 * 340,
	TITLELOADGAMEH		= PIXEL640 * 311,
	SFXCONFIGX			= PIXEL640 * 7,
	SFXCONFIGY			= PIXEL640 * 55,
	SFXCONFIGW			= PIXEL640 * 504,
	SFXCONFIGH			= PIXEL640 * 400,
	INPUTSELCTX			= PIXEL640 * 7,
	INPUTSELCTY			= PIXEL640 * 55,
	INPUTSELCTW			= PIXEL640 * 504,
	INPUTSELCTH			= PIXEL640 * 320,

		FIRSTCOLUMNTEXTX = PIXEL640 * 20,
		FIRSTCOLUMNTEXTY = PIXEL640 * 90,	
		FIRSTCOLUMNTEXTW = PIXEL640 * 50,
		FIRSTCOLUMNTEXTH = PIXEL640 * 18,
		FULLCOLUMNW = PIXEL640 * 640,


		NAMETEXTX = PIXEL640 * 70,
		NAMETEXTY = PIXEL640 * 90,	
		NAMETEXTW = PIXEL640 * 110,
		NAMETEXTH = PIXEL640 * 18,

		RANKTEXTX = NAMETEXTX + NAMETEXTW,
		RANKTEXTY = PIXEL640 * 90,	
		RANKTEXTW = PIXEL640 * 70,
		RANKTEXTH = PIXEL640 * 18,

		KILLSTEXTX = RANKTEXTX + RANKTEXTW,
		KILLSTEXTY = PIXEL640 * 90,	
		KILLSTEXTW = PIXEL640 * 80,
		KILLSTEXTH = PIXEL640 * 18,

		MISSIONSTEXTX =  KILLSTEXTX + KILLSTEXTW,
		MISSIONSTEXTY = PIXEL640 * 90,	
		MISSIONSTEXTW = PIXEL640 * 80,
		MISSIONSTEXTH = PIXEL640 * 18,

		SKILLTEXTX = MISSIONSTEXTX + MISSIONSTEXTW,
		SKILLTEXTY = PIXEL640 * 90,	
		SKILLTEXTW = PIXEL640 * 80,
		SKILLTEXTH = PIXEL640 * 18,


		MORALETEXTX = SKILLTEXTX + SKILLTEXTW,
		MORALETEXTY = PIXEL640 * 90,	
		MORALETEXTW = PIXEL640 * 80,
		MORALETEXTH = PIXEL640 * 18,

		DISPOSITIONTEXTX = MORALETEXTX + MORALETEXTW,
		DISPOSITIONTEXTY = PIXEL640 * 90,	
		DISPOSITIONTEXTW = PIXEL640 * 80,
		DISPOSITIONTEXTH = PIXEL640 * 18,
		
		PILOTDETAILSTABLEY	= PIXEL640 * 110,





	GRAPHICSCONFIGX			= PIXEL640 * 460,
	GRAPHICSCONFIGY			= PIXEL640 * 64,
	GRAPHICSCONFIGW			= PIXEL640 * 160,
//DeadCode JIM 18Dec96 	GRAPHICSCONFIGH			= PIXEL640 * 220
	GRAPHICSCONFIGHSMALL			= PIXEL640 * 220,			//JIM 18Dec96
	GRAPHICSCONFIGH			= PIXEL640 * 324					//JIM 18Dec96

};

//--------------------------------
//END OF LIST: do not write below this line
#endif

#endif

