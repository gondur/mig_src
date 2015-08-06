////////////////////////////////////////////////////////////////////////
//
// Module:      package.h
//
// Created:     12/01/99 by JIM
//
// Description: 
//
////////////////////////////////////////////////////////////////////////
//package structure definition
//
//This defines everything that we don't want in battlefield file
//if packages are supposed to be reusable.
//There may be an instance of it at the top of the BF, 
//but we will often override it.
//

//Globrefs required to manage waypoint system:

////////////////////////////////////////////////////////////////////////
//
// Function:    SavedGlobrefs
// Date:        12/01/99
// Author:      JIM
//
// Description: 
//
////////////////////////////////////////////////////////////////////////
enum	SavedGlobrefs
{
	SGR_BLANK=0,
	SGR_Pack_Takeoff=1,	
	SGR_Pack_Target,	
	SGR_Pack_Regroup,
				SGR_Pack_Targ_F0_E0,	SGR_Pack_Targ_F0_E1,
				SGR_Pack_Targ_Fmax_E1=SGR_Pack_Targ_F0_E1+48,

	SGR_WPP_Rendevous,
	SGR_WPP_Ingress,
	SGR_WPP_Target,
	SGR_WPP_Regroup,
	SGR_WPP_Egress,
	SGR_WPP_Disperse,

	SGR_WPC_Rendevous,
	SGR_WPC_Ingress,
	SGR_WPC_Target,
	SGR_WPC_Regroup,
	SGR_WPC_Egress,
	SGR_WPC_Disperse,


};

struct	lchpak;
struct	Profile
{
	enum	{MAX_PACKS=10,MAX_WAVES=6,MAX_GROUPS=3,GRPSTRIKE = 0, GRPFLAKSUPP = 1, GRPESCORT = 2, MAX_FLIGHTS=4, MAX_CALLNAMES = 30};
	enum	WaveSplitting	{WS_SINGLE_PRIMARY,WS_SINGLE_OWN,WS_SEPERATE,WS_SEP_WING,WS_SEP_ELT};
	struct	TargetDescript
	{
		UniqueID	ID;			//the UID assigned to item given BFs loaded now

		UniqueID	SGT;		//which SGT owns item, usually=packagetarget
		UniqueIDBand	band;	//These 2 fields describe the target as 
		SWord		SGbandindex;//an index into the supergroup. -1=next avail
								//For patrols, this field holds cardinal direction backup
								//For patrols, groupindex holds range in 10metre units
		SWord		groupindex;	//Don't know if we need to be able to select an
								//element to target or we are just happy with
								//concentrate and scatter modes.

//		char		GlobrefUsed;//Can't afford to populate 16 a/c in each group in each wave
//		char		spare;		//so I'm making the globref dependent on the squadron and a/c index 
		bool	Independent();	//true if this target is set up independently
	};
	struct	Flight
	{
		int globrefind;
		TargetDescript			//actual methodology is in battlefield
					primary,  	//may be 1 target per element or alternate
					secondary;	//or 2 passes.
	};							

	struct	Group
	{
		UniqueID	uid;		//uid of first aircraft
		UniqueID	takeoffAF;	//each type of aircraft may be using different runway
		int			takeofftime;
		char		callname;

		struct	Secret1{
			char		squadron;
			operator int()	{return squadron;}
		}		squadron;
			struct	Secret2{
			char		numflights;
		operator int()	{return numflights;}
		}	numflights;
		Flight		flight[MAX_FLIGHTS];			
		Flight&	operator [](int i) {return flight[i];}
		void	SetSquad(int squadnum);
		void	SetFlights(int flights);

		lchpak*	GetWeapList();
		int		GetWeapIndex(int flight);
		int		GetExtFuel(int flight);
		int		GetStoresDrag(int flight);	//CSB 17/06/99	
		WaveSplitting	GetTargSplitting(int acnum,bool alloweltmode);
		
	};

	struct	Wave
	{
//		int			starttime;
		int			targettime;
		UniqueID	firstwp;
		Group		group[MAX_GROUPS];
		Group&	operator [](int i) {return group[i];}
		bool	GetKeyTargetWPs(UniqueID& targetarea,UniqueID& firststartpatrolbomb,UniqueID& laststartpatrolbomb,UniqueID& firstendpatrol,UniqueID& lastendpatrol,UniqueID& regrouparea);
		static UniqueID	FindWpBetween(UniqueID wp1,UniqueID wp2,int group,int flight=-1,int elt=-1);
		static UniqueID	FindWpAfter(UniqueID wp1,UniqueID wp2,int group,int flight=-1,int elt=-1);
		static void		RemoveWpBetween(UniqueID&wp1,UniqueID&wp2,UniqueID wptoremove);
		static UniqueID	InsertWpBetween(UniqueID&wp1,UniqueID&wp2,SavedGlobrefs targ,BFieldWaypointActions a,int group,int flight=-1,int elt=-1);
		void	SetPositionDescription(int grp,UniqueID wpid);
		UniqueID	MakeGroup(bool iswave0,bool AAA);
		void		MakeWayPoints(bool wave0,int grnum, int duty,UniqueID targ);
		WaveSplitting	GetRouteSplitting(int groupnum,int acnum);

	};
	UniqueID	MakeWave(int wave,int duty);
	char		packname[9];		//basis of file-name, probably
	bool		redo;
	bool		edited;
	int			wpsused;
	DutyType	duty;
	UniqueID	packagetakeoff;							
	UniqueID	packagetarget;	//this is the overview target
//	UniqueID	regrouploc;		//everyone flys to the same egress
	UniqueID	egressloc;		//everyone flys to the same egress
								//either east coast or west coast
								//bf route can delta from this default
	FileNum		loadedbf;
	Wave		wave[MAX_WAVES];
	Wave&	operator [](int i) {return wave[i];}
	UniqueID	MakePrimaryRoute(int Y);
	static UniqueID	MakeSecondaryRoute(DutyType duty);
	void	RecalcRoutePositions();
	void	ResetPatrolItems();
	void	SetTargetGlobrefs(bool fixconvoys=false);
	void	RecalcPrimaryPositions();
	void	RecalcSecondaryPositions(int wave);

	void	SetGlobRefsForRoute(UniqueID wpuid);
	void	RepositionSubWaypoints(UniqueID wpuid);
public:
	int		FindSpareGlobref();

	void	ModifyRoute(int wavenum,int	groupnum,int	acnum);
	void	ModifyPatrolRoute(int wavenum,int	groupnum,int	acnum);
	void	SetACTypesFromGeneric();
	static	UniqueID MakeInterceptWP(SavedGlobrefs a,SavedGlobrefs b,int percent,UniqueID next,SavedGlobrefs as=(SavedGlobrefs)-1,int relalt=0,BFieldWaypointActions action=wpacnoactionno);
	static int	CalcTime(COORDS3D* last,COORDS3D* wp,int type, int esctype, SWord StoresDrag);							//CSB 18/06/99	

	static int	ValidateTime(CString* buffer, int packnum, int wavenum);

	static int	CalcFuel(COORDS3D* last,COORDS3D* wp,int escorteetype,int escortertype, SWord StoresDrag);	//CSB 18/06/99	
	void CalcWPTimes( int wavenum);
	bool Profile::CalcFuel(int wavenum, int group, UniqueID wpuid, int& fuel);	
	static	bool Profile::NonLeadElementSet(int applyflight, int applyelt);

	static	Float RelDensity(SLong alt);

	static void CalcHoriAndClimbTime(struct COORDS3D * last,struct COORDS3D * wp,SLong& horitime,SLong& climbtime,int type, int esctype, SWord StoresDrag);	//CSB 18/06/99
	static	bool GetPackageFromWP(UniqueID req_wpuid,int& pack, int& wave, int& g);
	static	int Profile::WPType(UniqueID u);

	int		DecodePackage(string packstr,bool decodebinary); //returns num flights. -ve if other targets
	void	SetTargetUIDs(bool	fixconvoys=false);
	void	ClearWave(int wave);
	void	ClearGroup(int wave,int grp); //no shunt required
	void	ShuntWave(int wave);
	int		CountWaypoints();
	int		CountWaypoints(int wavenum);
};
struct	info_waypoint;
class	BOStream;
class	BIStream;
struct	PackageList
{
	void	SaveGame(BOStream&);
	void	LoadGame(BIStream&);
	void	SaveBin();
	static	CString&	CSprintf(const char* format,...);
	static	void	SaveBin(Profile* p,BOStream& f);
	static	void	SaveRouteBin(Profile::Wave* wave,BOStream&file);
	static	void	SaveWaypointBin(info_waypoint* wp,BOStream&file);
	static	void	SaveAirItemBin(Profile::Group* group,BOStream&file);
	Profile	pack[Profile::MAX_PACKS + 1];				//the top one is reserved for comms red
//	char	plpack,plwave,plgrp,plac;					//player's slot
	char	hipack, hiwave, higroup;
	UniqueID	hiwp;
	Profile&	operator[](int i)	{return pack[i];}
	int	NewPackage(UniqueID targ, int duty);
	bool	PackageHasBeenEdited();
	void	ProfileFlightsRequired(int pack, int& mb, int& f80,int& f84,int& f51,int& fb,int& f, int& f86a, int& f86b, int& b26, int& b29); //RDH 16/03/99
	void	FlightsAvailable(int pack, int& a_mb, int& a_f80,int& a_f84,int& a_f51,int& a_fb,int& a_f, 
			int& a_f86a, int& a_f86b, int& a_b26, int& a_b29); //RDH 16/03/99

	void	DeleteNonRedoPackages();
	int		FindPackage();
	int		FindSquad(int duty);
	int		FindSquadExlMedBombers();
	int PackageList::CAPAircraftcnt();


	void	SetWaveTimes(int p, int w,int targettime);	 //RDH 12/02/99
	void	UpDatePackageTimes();					 //RDH 12/02/99

	
	bool	GetSquadEntry(int p, int w, int g, int& squad, int& flight);
	bool	FlyableAircraftAvailable();
	bool	PackageList::GetPackage(int& i, int& wave, int& group, int squad, int flight);
	UniqueID FindEgressPoint(UniqueID targ);

	int	SquadACUsed(int squadnum);
	int SquadACAvail(int squadnum);	//every squadron initially has 19 aircraftso they
	//rdh{return 19;}			//can lose 3 aircraft before dropping to 3 flights
							//If Mark really wants restocking then I suggest 
							//setting a restocking max of 17 so you are fighting 
	bool	PreLoad(int packnum,FileNum fil=FIL_NULL,const char* filename=NULL,bool copyprimary=false,bool copysecondaries=false);
	void	Load(int packnum,FileNum fil=FIL_NULL,const char* filename=NULL);
	void	FixupAircraft(int packnum);	//post load
	void	WipeAll();
	void	ClearPack(int pack);
	void	ShuntPack(int pack);
	void	PackagePrepareForFrag();							//AMM 17Nov98

	int		MaxWaypoints()		{return	350;}
	int		UsedWaypoints();
	bool	CanAddMoreWaypoints(int	packnum);

};
extern	PackageList	Todays_Packages;

