//------------------------------------------------------------------------------
//Filename       ai.h
//System         
//Author         Jim Taylor
//Date           Tue 28 May 1996
//Description    artificial stupidity....
//------------------------------------------------------------------------------
#ifndef	AI_Included
#define	AI_Included
#ifndef	__BCPLUSPLUS__
#include	"rchatter.h"
#else
	typedef	int	PhraseTables;
#endif

#define	DEFAULT_AI 0

class	AirStruc;
//fake class interface between derivatives of ArtInt
class	MESSAGE_STRUC;
class	DecisionAI													  //JIM 22/01/99
{
public:
struct	OptionRef													  //JIM 22/01/99
{
	PhraseTables	optionmsg;		//this is printed in user alternatives. If null use saidmsg
	DecisionAI**	airesult;		//next user choice table	If null do nowt
	int	saidmsg;		//the message to say. If null say nowt. Recipient will respond anyway?
};
																  //JIM 22/01/99
	bool	UserMsgDecision(AirStrucPtr callee,ItemBasePtr trg,			  //JIM 22/01/99
		AirStrucPtr caller,ArtInt* artint,MESSAGE_STRUC* PriorityMessage);
	virtual OptionRef*	GetMsgOptions()=NULL;								  //JIM 22/01/99
	virtual	bool													  //JIM 22/01/99
		AutoMsgDecision(AirStrucPtr callee,ItemBasePtr trg,			  //JIM 22/01/99
		AirStrucPtr caller,ArtInt* artint,MESSAGE_STRUC* PriorityMessage=NULL)=0;						  //JIM 22/01/99
    #ifndef	__BCPLUSPLUS__
	PhraseTables GetDefaultPhrase(AirStrucPtr callee,ItemBasePtr trg);// {return PHRASE_CONTINUE;}
    #endif
	enum	{OPTIONTABLEMAX=100};
	static DecisionAI* optiontable[OPTIONTABLEMAX];
	static int optiontablemax;
	int		optionnumber;
	DecisionAI()	{optiontable[optionnumber=++optiontablemax]=this;}
};																	  //JIM 22/01/99




class	ArtInt
{
	friend	struct	AcArrayItterator;
	friend 	class	TrgListProc;
	friend	class	Replay;										//DAW 28Jun99
	friend	class	Inst3d;
	int		spotcount;
	enum	{ACARRAYSIZE=256};
	static	AirStruc*	ACArray[ACARRAYSIZE];
protected:
	int		gunstimer;
	enum	tGroupLevel {GROUP_LONER, GROUP_ELEMENT, GROUP_FLIGHT, GROUP_SQUADRON};
public:
	DecisionAI*	blocking;
	ArtInt()	{blocking=NULL;}
	int		ACArrayInd;
	bool	Add(AirStruc*);
	bool	Remove(AirStruc*);
	bool	Visible(AirStruc*,AirStruc*);
	bool	Seen(AirStruc*	eye,AirStruc*	trg);
	void	VisibleCheck();
	void	ArtInt::VisibleAcCheck();
	void	ArtInt::ProcessWPEvents();
	void	ArtInt::LaunchMiGs(AirStruc* trg,tAggressionLevel al);
	void	ArtInt::VisibleContrailsCheck();
	void	ArtInt::VisibleAAACheck();
	void	ArtInt::SpottedContrails(AirStruc* eye,AirStruc* trg);
	void	ArtInt::SpottedOldContrails(AirStruc* eye,AirStruc* trg);
	bool	ArtInt::AlertFighters(AirStruc* eye,AirStruc* trg, AirStruc* friendlythatneedshelp);
	void ArtInt::InterceptRangeFromTo(AirStruc* from, AirStruc* to);
	SLong ArtInt::RangeFromTo(AirStruc* from, AirStruc* to);
	bool ArtInt::AcHasBombs(AirStruc* trg);
	bool ArtInt::ForceHasBombers(AirStruc* trg);
	bool ArtInt::BingoFuel(AirStruc* trg);
	bool ArtInt::Winchester(AirStruc* trg);
	void ArtInt::ResetUnfriendly();

	void	ArtInt::GroupEngage(AirStruc* caller,AirStruc* trg);
	tGroupLevel ArtInt::GroupLevel(AirStruc* caller);
	tGroupLevel ArtInt::GroupLevelNotInFormation(AirStruc* caller);	  //RDH 10/05/99

//DeadCode RDH 17Feb99 	void	ArtInt::DefensiveSplit(AirStruc* caller,AirStruc* caller2,AirStruc* trg,ANGLES leftpitch,ANGLES rightpitch);
//DEADCODE RDH 17/02/99 	void	ArtInt::SetUpMultiWave(AirStruc* caller,AirStruc* caller2,AirStruc* trg);
	void	ArtInt::DefensiveSplitHiLo(AirStruc* caller,AirStruc* caller2,AirStruc* trg);
	void	ArtInt::ChooseSplitManoeuvre(AirStruc* caller,AirStruc* caller2,AirStruc* trg);
	void	ArtInt::SetUpPincer(AirStruc* caller,AirStruc* caller2,AirStruc* trg);
//	void	ArtInt::SetSurprisedEngage(AirStrucPtr caller,AirStrucPtr trg);
//	void	ArtInt::SetSurprisedEngage(AirStrucPtr caller,AirStrucPtr trg, MANOEUVRE manoeuvre,ANGLES   desiredhdg,ANGLES   desiredpitch);
	void	ArtInt::SetUpRemainderOfGroupToEngage(AirStruc* caller,AirStruc* trg,MANOEUVRE manoeuvre,ANGLES desiredhdg,ANGLES  desiredpitch, bool TRUE);
//DEADCODE RDH 19/02/99 	bool	ArtInt::MakeForceToRespond (AirStruc* caller, AirStruc* trg, tGroupLevel group);
	bool	ArtInt::MakeForceToRespond (AirStruc* caller, AirStruc* trg, tGroupLevel group, bool& splitmanappropriate);
	bool	ArtInt::TrgIsVulnerable(AirStruc* caller, AirStruc* trg);

	void	ArtInt::SubsequentIDasUnfriendly(AirStruc* caller,AirStruc* trg);
	void	ArtInt::InCombatWithoutUnfriendly(AirStruc* caller,AirStruc*  trg);
//DEADCODE RDH 08/03/99 	bool	ArtInt::DecoysInGroup(AirStruc*  caller);
//DEADCODE RDH 08/03/99 	void	ArtInt::SetDecoysInGroup(AirStruc*  ac);
	void	ArtInt::SetRoundAboutAc(AirStruc*  ac);
	AirStruc* FreeUpAFlight(AirStruc* caller, AirStruc*  currtrg);
	AirStruc* FindFreeFlight(AirStruc* caller);
    #ifndef __BCPLUSPLUS__
	ScriptTables BreakCall(AirStruc* caller,bool onright);
	#endif
	void	DefensiveSplit(AirStruc* caller,AirStruc* trg, ANGLES leftpitch,ANGLES rightpitch);
	bool	ChooseManoeuvre(AirStruc* caller,AirStruc* trg, bool newspot);
#ifndef     __BCPLUSPLUS__
	MESSAGE_STRUC	ChooseBanditRelMsg(MsgType mtype, AirStruc* caller,AirStruc* trg, AirStruc* callee, bool newspot);
	MESSAGE_STRUC	ChooseBanditOnTailMsg(MsgType mtype, AirStruc* caller,AirStruc* trg, AirStruc* callee, bool newspot);
	MESSAGE_STRUC	ChooseBanditHeadOnMsg(MsgType mtype, AirStruc* caller,AirStruc* trg, AirStruc* callee, bool newspot);
#endif
	bool		EyeIsAndTrgIsNotInPlayersGroup(AirStruc* caller,AirStruc* trg);
	bool		EngageAppropriate(AirStruc* caller,AirStruc* trg);
//DEADCODE RDH 03/03/99 	AirStruc* 	FindGroupLeader(AirStruc* ac);
	bool		Escorting(AirStruc* ac);

//DEADCODE RDH 03/03/99 	AirStruc*	FindGroupLeaderInFormation(AirStruc* ac);





//DEADCODE RDH 18/02/99 	ANGLES RelHdgIntFromTo(AirStruc* ac,AirStruc* trg);
	bool CallerOnRight(AirStruc* ac,AirStruc* trg);					  //RDH 18/02/99
	void SwitchCallerToLeft(AirStruc*& caller, AirStruc*& callee);

	void FindGroupAndLeader2(AirStruc*& caller, AirStruc*& caller2,tGroupLevel& group);

	ANGLES HdgIntFromTo(AirStruc* ac,AirStruc* trg);
	bool	ArtInt::TargetOnCallerTail(AirStruc*  caller,AirStruc*  trg,ANGLES angle);
	bool	ArtInt::CallerOnTargetTail(AirStruc*  caller,AirStruc*  trg,ANGLES angle);

	bool	ArtInt::TargetFacingCaller(AirStruc*  caller,AirStruc*  trg,ANGLES angle);
	bool	ArtInt::CallerFacingTarget(AirStruc*  caller,AirStruc*  trg,ANGLES angle);
	AirStrucPtr	ArtInt::SetFollowerEngage(AirStrucPtr eye,AirStrucPtr trg,MANOEUVRE  manoeuvre,ANGLES desiredhdg,ANGLES  desiredpitch, bool surprised);
	AirStrucPtr	ArtInt::SetFlightEngage(AirStrucPtr eye,AirStrucPtr trg,MANOEUVRE  manoeuvre,ANGLES desiredhdg,ANGLES  desiredpitch, bool surprised);


	bool	DoesFriendNeedHelp(AirStruc* eye,AirStruc* trg);
	bool	SpottedNeutral(AirStruc* eye,AirStruc* trg);
	bool	SpottedUnfriendly(AirStruc* eye,AirStruc* trg);
	bool	SpottedUnknown(AirStruc* eye,AirStruc* trg);
	bool	SpottedNewUnfriendly(AirStruc* eye,AirStruc* trg);
//DEADCODE RDH 13/06/99 	bool	AttackSpareInLeadersFlight(AirStruc* eye);
	bool	AttackSpareInLeadersGroup(AirStruc* eye);				  //RDH 13/06/99
	bool	LeadersGroupInCombat(AirStruc* eye);

//	void	SetEngage(AirStrucPtr eye,AirStrucPtr trg);
	void	ArtInt::SetEngage(AirStrucPtr eye,AirStrucPtr trg,MANOEUVRE manoeuvre,ANGLES   desiredhdg,ANGLES   desiredpitch, bool surprised);
	void	ArtInt::PrepareForCombat(AirStrucPtr caller);			  //RDH 04/03/99

	int		CountFormationSize(AirStrucPtr);
	int		GuessFormationSize(AirStrucPtr,AirStrucPtr);
	bool	SameFlight(AirStrucPtr a,AirStrucPtr b);			//DAW 30Jun96
	void	SetPreEngage(AirStrucPtr eye,AirStrucPtr trg);
	AirStrucPtr	SetFollowerPreEngage(AirStrucPtr eye,AirStrucPtr trg);	//returns last targ
	AirStrucPtr	SetFlightPreEngage(AirStrucPtr eye,AirStrucPtr trg);	//returns last targ
	AirStrucPtr	SetFollowerWhoCanEngage(AirStrucPtr eye,AirStrucPtr trg);	//returns last targ
	AirStrucPtr	SetFlightWhoCanEngage(AirStrucPtr eye,AirStrucPtr trg);	//returns last targ
	AirStrucPtr	nextfl(AirStrucPtr trg,bool unassigned=TRUE);
	AirStrucPtr	nextfol(AirStrucPtr trg,bool unassigned=TRUE);
	bool	AircraftAreClose(AirStrucPtr trg, AirStrucPtr foll);

	void	AllBreakOff(AirStrucPtr leadac);
	void	BreakOff(AirStrucPtr ac);
	void	AllEngage(AirStrucPtr leadac);
	void	ClearFollowerFormation(AirStrucPtr	eye);
	void	CleanUp();
	void	PlayerHitConvoy(FormationItemPtr);
	bool	OkToAccel();
	bool	PersonalThreat(AirStrucPtr trg,AirStrucPtr agg, bool process=FALSE);
	void	PersonalThreatMsg(AirStrucPtr trg,AirStrucPtr agg);
	void	DisEngageAll(AirStruc* caller, MESSAGE_STRUC* prioritymessage);	
	void	AllChangeMovecode(AirStrucPtr leadac, AirStrucPtr trg, AutoMoveCodeTypeSelect movecode);

		
	bool	SendMsgAndCall(const MESSAGE_STRUC& msg,DecisionAI* processor);
	void	ArtInt::ExpandMigs(AirStrucPtr placeholder);
	void	ArtInt::ReallyExpandMigs(AirStrucPtr placeholder);
	void	FakeMissionSuccess();

};
extern	ArtInt	Art_Int;

//////////////////////////////////////////////////////////////////////
//
// Class:		AcArrayItterator
// Date:		18/05/99
// Author:		RDH
//
//Description: 
//		An AcArrayItterator object pretends to be an AirStrucPtr
//		However, it has a member function .Next()
//		which moves it through the ArtInt::ACArray
//		When the end of the array is reached .Next() returns 'false'
//		This array can contain 'random' NULL entries
//
//////////////////////////////////////////////////////////////////////
struct	AcArrayItterator
{
	AirStrucPtr		THISTHIS;
	AirStrucPtr*	THISTHIS2;
	int	index;
	AcArrayItterator()	
	{index=-1;THISTHIS2=Art_Int.ACArray-1;THISTHIS=NULL;}
	bool	Next()		//true means there is a next one
	{	
		index++;
		THISTHIS2++;
		if (index<ArtInt::ACARRAYSIZE)
		{
			THISTHIS=*THISTHIS2;
			return true;
		}
		else
		{
			THISTHIS=NULL;
			return false;
		}
	}
	operator bool()	{return THISTHIS!=NULL;}
	operator int()	{return THISTHIS!=NULL;}
	operator AirStrucPtr()	{return THISTHIS;}
	AirStrucPtr operator->()	{return THISTHIS;}
};



#define	EXTERNAI(name,trgtype)	extern	DecisionAI*	name;

//Decisions are lumps of AI code that can be bypassed by the player
//and lead to Options. Decisions can be used as Options.

#define	DECISIONAI(name,trgtype)										\
class	trgtype##_##name##_AI:public ArtInt							 \
{																		  \
public:																	   \
  bool	name(AirStrucPtr eye,trgtype trg,AirStrucPtr sender,				\
					DecisionAI* currdecision,MESSAGE_STRUC* PM);			 \
};																			  \
class	trgtype##_##name:public	DecisionAI								 \
{																			  \
	static OptionRef opts[];													   \
public:																			\
	OptionRef*	GetMsgOptions() {return opts;}										 \
	bool	AutoMsgDecision(AirStrucPtr eye,ItemBasePtr trg,					  \
					AirStrucPtr sender,ArtInt* artint,MESSAGE_STRUC* PM)							   \
	{	return	((trgtype##_##name##_AI*)artint)->name(							\
							eye,(trgtype)*trg,sender,this,PM);}						 \
};																					  \
EXTERNAI(name,trgtype)


#define	OPTIONAI(name,trgtype)											\
class	trgtype##_##name##_AI:public ArtInt							 \
{																		  \
public:																	   \
  bool	name(AirStrucPtr eye,trgtype trg,AirStrucPtr sender,				\
					DecisionAI* currdecision,MESSAGE_STRUC* PM);			 \
};																			  \
class	trgtype##_##name:public	DecisionAI								 \
{																			  \
public:																			\
	OptionRef*	GetMsgOptions() {return NULL;}										 \
	bool	AutoMsgDecision(AirStrucPtr eye,ItemBasePtr trg,					  \
					AirStrucPtr sender,ArtInt* artint,MESSAGE_STRUC* PM)		   \
	{	return	((trgtype##_##name##_AI*)artint)->name(							\
							eye,(trgtype)*trg,sender,this,PM);}						 \
};																					  \
EXTERNAI(name,trgtype)

#define	TABLEAI(name,trgtype)							 \
DecisionAI::OptionRef	trgtype##_##name::opts[]	=
//Write body of option table here!
//{
//	{PHRASE_,	&DecisionAI,	SCRIPT_},
//	{PHRASE_,	&DecisionAI,	SCRIPT_},
//};

#define	INSTANCEAI(name,trgtype,options)							 \
trgtype##_##name	trgtype##_inst_##name;							  \
DecisionAI*	name=	&trgtype##_inst_##name;								\
bool	trgtype##_##name##_AI::name(AirStrucPtr callee,trgtype trg,AirStrucPtr caller,DecisionAI* currdecision,MESSAGE_STRUC* prioritymessage)
//Write the body of the decision routine here!
//{
//
//	return	true; //if handled. false if no child message
//}


EXTERNAI(JettisonStores,AirStrucPtr);
EXTERNAI(JettisonTanks,AirStrucPtr);
EXTERNAI(DoNothing,AirStrucPtr);
EXTERNAI(TestGuns,AirStrucPtr);
EXTERNAI(AllDisengage,AirStrucPtr);
EXTERNAI(Rendezvous,AirStrucPtr);
EXTERNAI(SecretMessages,ItemPtr);
EXTERNAI(PreCombatMsg,ItemPtr);
EXTERNAI(FACMsg,ItemPtr);	enum	{FAC_BombsAway=6};
#endif
