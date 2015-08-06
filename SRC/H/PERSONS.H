#error	dead module!

//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 //Filename       persons.h
//DeadCode JIM 18Jun96 //System         
//DeadCode JIM 18Jun96 //Author         Paul.   
//DeadCode JIM 18Jun96 //Date           Tue 19 Sep 1995
//DeadCode JIM 18Jun96 //Description    
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 #ifndef	PERSONS_Included
//DeadCode JIM 18Jun96 #define	PERSONS_Included
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 #define	DEFAULT_PERSONS 0
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 //-------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 // list of equates for battle field loading routines
//DeadCode JIM 18Jun96 // for use in battle field files, indexs spcodetable in persons.aol
//DeadCode JIM 18Jun96 // go up in 2's to avoid add bx,bx
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 enum	BFINST	{duffroutineno = 0,
//DeadCode JIM 18Jun96 				 rtbeginno,
//DeadCode JIM 18Jun96 				 rtendno,
//DeadCode JIM 18Jun96 				 startitemno,
//DeadCode JIM 18Jun96 				 enditemno,
//DeadCode JIM 18Jun96 				 bfposvarno,
//DeadCode JIM 18Jun96 				 bfwxyzno,
//DeadCode JIM 18Jun96 				 bfrouteptrno,
//DeadCode JIM 18Jun96 				 bfielddoneno,
//DeadCode JIM 18Jun96 				 bfnationalityno,
//DeadCode JIM 18Jun96 				 bftypeno,
//DeadCode JIM 18Jun96 				 bftargetno,
//DeadCode JIM 18Jun96 				 bfaltno,
//DeadCode JIM 18Jun96 				 bfbuddyno,
//DeadCode JIM 18Jun96 				 bfsetactypeno,
//DeadCode JIM 18Jun96 				 bffirstviewno,
//DeadCode JIM 18Jun96 				 wpvarno,
//DeadCode JIM 18Jun96 				 wpaltno,
//DeadCode JIM 18Jun96 				 wpwxyzno,
//DeadCode JIM 18Jun96 				 wpactionno,
//DeadCode JIM 18Jun96 				 wpbeginno,
//DeadCode JIM 18Jun96 				 wpendno,
//DeadCode JIM 18Jun96 				 wploopno,
//DeadCode JIM 18Jun96 				 wpflagsno,
//DeadCode JIM 18Jun96 				 bfweapsetno,
//DeadCode JIM 18Jun96 				 bfaltrndno,
//DeadCode JIM 18Jun96 				 bfsetacptrno,
//DeadCode JIM 18Jun96 				 bfsetcounterno,
//DeadCode JIM 18Jun96 				 bfdeccounterjeno,
//DeadCode JIM 18Jun96 				 bfrelaltno,
//DeadCode JIM 18Jun96 				 bfrelposno,
//DeadCode JIM 18Jun96 				 bfsetposno,
//DeadCode JIM 18Jun96 				 bfsetvarno,
//DeadCode JIM 18Jun96 				 bfshapeno,
//DeadCode JIM 18Jun96 				 bfcmpjeno,
//DeadCode JIM 18Jun96 				 bfdutyno,
//DeadCode JIM 18Jun96 				 bfsetviewanglesrangeno,
//DeadCode JIM 18Jun96 				 bfscripttypeno,
//DeadCode JIM 18Jun96 				 bfacmovecodeno,
//DeadCode JIM 18Jun96 				 bfsetclipregionno,
//DeadCode JIM 18Jun96 				 bfacsetattackno,
//DeadCode JIM 18Jun96 				 bfheadingno,
//DeadCode JIM 18Jun96 				 bfpitchno,
//DeadCode JIM 18Jun96 				 bfforegroundno,
//DeadCode JIM 18Jun96 				 bfbackgroundno,
//DeadCode JIM 18Jun96 				 wpvelno,
//DeadCode JIM 18Jun96 				 bfformleaderno,
//DeadCode JIM 18Jun96 				 bfsetunfvarno,
//DeadCode JIM 18Jun96 				 bfvelno,
//DeadCode JIM 18Jun96 				 bfformationno,
//DeadCode JIM 18Jun96 				 bfuniquebandno,
//DeadCode JIM 18Jun96 				 bfrelcourseno,
//DeadCode JIM 18Jun96 				 bfsetmissionno,
//DeadCode JIM 18Jun96 				 wpposvarno,
//DeadCode JIM 18Jun96 				 wprangeno,
//DeadCode JIM 18Jun96 				 bfdamageno,
//DeadCode JIM 18Jun96 				 bfskillno
//DeadCode JIM 18Jun96 				};
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 class	Persons;
//DeadCode JIM 18Jun96 extern	Persons	_Persons;
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 typedef	void (Persons::*PMFI)	(UWord *&);
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 class	Persons
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		{
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		WorldStuff	*currentworldptr;
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		UWord	*bfield_start;
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		itemptr	tempitemptr;
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		UWord	tempitemtype;
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		ANGLES 	tempheading;
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		ANGLES 	temppitch;
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		UWord	alt;
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		UWord	firstview;
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		UWord 	counter;
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		UWord 	requiredshapes[256];
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		UWord	shapesrequested;
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		UByte	finished;
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		static void CheckBFVersion(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void	duffroutine(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void rtbegin(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void rtend(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void startitem(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void enditem(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void bfposvar(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void bfwxyz(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void bfrouteptr(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void bfielddone(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void bfnationality(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void bftype(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void bftarget(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void bfalt(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void bfbuddy(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void bfsetactype(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void bffirstview(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void wpvar(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void wpalt(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void wpwxyz(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void wpaction(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void wpbegin(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void wpend(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void wploop(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void wpflags(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void bfweapset(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void bfaltrnd(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void bfsetacptr(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		UWord gettextequate(UWord);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void bfsetcounter(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void bfdeccounterje(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void bfrelalt(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void bfrelpos(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void bfsetpos(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void bfsetvar(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void bfshape(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void bfcmpje(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void bfduty(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void bfsetviewanglesrange(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void bfscripttype(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void bfacmovecode(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void bfsetclipregion(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void bfacsetattack(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void bfheading(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void bfpitch(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void bfforeground(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void bfbackground(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void wpvel(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void bfformleader(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void bfsetunfvar(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void bfvel(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void bfformation(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void bfuniqueband(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void bfrelcourse(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void bfsetmission(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void wpposvar(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void wprange(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void bfdamage(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void bfskill(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void	startsimpleitem(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void	startaircraft(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void	startrotateditem(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void	startgrndformationleader(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void	startgrndformationitem(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void	startgrndformationtail(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void	startairformationleader(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void	endsimpleitem(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void	endaircraft(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void	endrotateditem(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void	endgrndformationleader(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void	endgrndformationitem(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void	endgrndformationtail(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void 	endairformationleader(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void 	InitInFlight ();
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void	Static(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void	autofollowwp(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void	autofollowwpwing(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void	autotaxi(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void	autowait(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void	autoescort(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void	autoescortwing(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void	grndfollowwp(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void	autoquicktakeoff(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void	autoengage(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void	autoengagewing(UWord *&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void	autoimmediatewpaction(UWord*&);
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		PMFI	bfintrptable[bfskillno];
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		public:
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 			Persons::Persons(void );
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 			void Persons::LoadSetPiece(WorldStuff *, UWord );
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		private:
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		protected:
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		};
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 ////script type equates
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 #define		standardscript		0
//DeadCode JIM 18Jun96 #define		artworkbackdrop 	1
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 #define		autorotate	1
//DeadCode JIM 18Jun96 #define		setchase	2
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 ////backdrop art file equates
//DeadCode JIM 18Jun96 //DeadCode JIM 27Nov95 #define		noartwork		-1
//DeadCode JIM 18Jun96 //DeadCode JIM 27Nov95 #define		gateallno		3
//DeadCode JIM 18Jun96 //DeadCode JIM 27Nov95 #define		loaderallno		6
//DeadCode JIM 18Jun96 //DeadCode JIM 27Nov95 #define		gateforegroundno	34
//DeadCode JIM 18Jun96 //DeadCode JIM 27Nov95 #define		gatebackgroundno	35
//DeadCode JIM 18Jun96 //DeadCode JIM 27Nov95 #define		towerbackgroundno	6
//DeadCode JIM 18Jun96 //DeadCode JIM 27Nov95 #define		towerforegroundno	36
//DeadCode JIM 18Jun96 //DeadCode JIM 27Nov95 #define		delta				1
//DeadCode JIM 18Jun96 //DeadCode JIM 27Nov95 #define		predef				2
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 struct	person
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		{
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		UWord	job,		// f16 pilot, a10 pilot etc
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 				location,	// screen no, initialise to starting screen #
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 				locafter3d;	////set 20sep91 - screen to goto on quit of 3d
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		itemptr	vehicle;	// ptr to item representing vehicle in 3d world
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		UWord	ability, 	// binary fraction 0 very poor, 0ffffh excellent
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 				morale,		// binary fraction 0 very poor, 0ffffh excellent
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 				fatigue,	// binary fraction 0 very poor, 0ffffh excellent
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 				filenum;	// used to generate related text file name
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		void	*screenlist,////set 13sep91 - pointer to name text
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 				*nametext;
//DeadCode JIM 18Jun96 //DeadCode JIM 22Jan96 		};
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 // character history simple technique have a text file for 
//DeadCode JIM 18Jun96 // each character provided, within the person structure have
//DeadCode JIM 18Jun96 // a field which is used to generate a unique filename for
//DeadCode JIM 18Jun96 // each person instance.eg: filenum dw 0021h gives peep0021.txt
//DeadCode JIM 18Jun96 // hope fully this technique will allow user characters to have
//DeadCode JIM 18Jun96 // histories defined as ascii text files
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 // jobs
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 //DeadCode JIM 27Nov95 #define		spitfirepilot		0			//1 ////set 17sep91 - made these into offsets
//DeadCode JIM 18Jun96 //DeadCode JIM 27Nov95 #define		typhoonpilot 		2			//2 for jobdescrtable
//DeadCode JIM 18Jun96 //DeadCode JIM 27Nov95 #define		mustangpilot 		4			//3
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 // macros used to define battlefield data follow
//DeadCode JIM 18Jun96 // list of equates for characters 
//DeadCode JIM 18Jun96 // for use in battle field files
//DeadCode JIM 18Jun96 // go up in 2's to avoid add bx,bx
//DeadCode JIM 18Jun96 //DeadCode JIM 27Nov95 #define		duffcharacterno			0
//DeadCode JIM 18Jun96 //DeadCode JIM 27Nov95 #define		spitfirepilot1no		duffcharacterno + 2
//DeadCode JIM 18Jun96 //DeadCode JIM 27Nov95 #define		typhoonpilot1no			spitfirepilot1no+ 2
//DeadCode JIM 18Jun96 //DeadCode JIM 27Nov95 #define		mustangpilot1no			typhoonpilot1no + 2
//DeadCode JIM 18Jun96 //DeadCode JIM 27Nov95 
//DeadCode JIM 18Jun96 //DeadCode JIM 27Nov95 #define		lastcharno				mustangpilot1no	
//DeadCode JIM 18Jun96 //DeadCode JIM 27Nov95 #define		numofpeeps				lastcharno/2
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 //-------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 // item type equates for bfield files routine tables
//DeadCode JIM 18Jun96 enum	BFieldItemSizes
//DeadCode JIM 18Jun96 	{			
//DeadCode JIM 18Jun96 	notanitemno				=0,
//DeadCode JIM 18Jun96 	simpleitemno			=2,	
//DeadCode JIM 18Jun96 	mobileitemno			=4,
//DeadCode JIM 18Jun96 	aircraftitemno			=6,
//DeadCode JIM 18Jun96 	rotateditemno			=8,
//DeadCode JIM 18Jun96 	grndformationleaderno	=10,
//DeadCode JIM 18Jun96 	grndformationitemno		=12,
//DeadCode JIM 18Jun96 	grndformationtailno		=14,
//DeadCode JIM 18Jun96 	airformationleaderno	=16
//DeadCode JIM 18Jun96 	};
//DeadCode JIM 18Jun96 		  
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 //-------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 //waypoint action equates for bfield files
//DeadCode JIM 18Jun96 //indexs table in wpaction.arp
//DeadCode JIM 18Jun96 //indexes modified to avoid confusion, rdh 22/2/1993
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 enum	BFieldEvents
//DeadCode JIM 18Jun96 	{
//DeadCode JIM 18Jun96 	BOMBEREVENT=0,		 BFIELDEVENTSODDDUMMY0000,
//DeadCode JIM 18Jun96 	SCOUTEVENT,			 BFIELDEVENTSODDDUMMY0001,
//DeadCode JIM 18Jun96 	AMBUSHEVENT,		 BFIELDEVENTSODDDUMMY0002,
//DeadCode JIM 18Jun96 	MAINEVENT,			 BFIELDEVENTSODDDUMMY0003,
//DeadCode JIM 18Jun96 	SECONDEVENT,		 BFIELDEVENTSODDDUMMY0004,
//DeadCode JIM 18Jun96 	SUBPLOT0,			 BFIELDEVENTSODDDUMMY0005,
//DeadCode JIM 18Jun96 	SUBPLOT1,			 BFIELDEVENTSODDDUMMY0006,
//DeadCode JIM 18Jun96 	SUBPLOT2,			 BFIELDEVENTSODDDUMMY0007,
//DeadCode JIM 18Jun96 	LOSTSCOUTAMBUSH,	 EBTRAP00.BF,
//DeadCode JIM 18Jun96 	LATEESCORT,	 		 CBLATE00.BF,
//DeadCode JIM 18Jun96 	BLUEFRACASTOPCOVER,	 CBFRAC01.BF,
//DeadCode JIM 18Jun96 	BLUEFRACASBACKUP,	 CBFRAC02.BF,
//DeadCode JIM 18Jun96 	FRACAS5CHAIN,		 CBFRAC05.BF,
//DeadCode JIM 18Jun96 	};
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 enum	BFieldWaypointActions
//DeadCode JIM 18Jun96 	{	
//DeadCode JIM 18Jun96 	duffwpactionno			=0,
//DeadCode JIM 18Jun96 	wpacnoactionno			=2,
//DeadCode JIM 18Jun96 	wpatakeoffno			=4,
//DeadCode JIM 18Jun96 	wpalandingno			=6,
//DeadCode JIM 18Jun96 	wpacircleno				=8,
//DeadCode JIM 18Jun96 	wpacruiseformno			=10,
//DeadCode JIM 18Jun96 	wpaccombatformno		=12,
//DeadCode JIM 18Jun96 	wpajinkstartno			=14,
//DeadCode JIM 18Jun96 	wpajinkstoptno			=16,
//DeadCode JIM 18Jun96 	wpfiregunno				=18,					
//DeadCode JIM 18Jun96 	wpbarrelrollno			=20,		
//DeadCode JIM 18Jun96 	wpshrtflybysndno		=22,					
//DeadCode JIM 18Jun96 	wpclimbrollno			=24,
//DeadCode JIM 18Jun96 	wpinitlandno			=26,						
//DeadCode JIM 18Jun96 	wpdmbtrknoactno			=28,					
//DeadCode JIM 18Jun96 	wpdmbtrkstopno			=30,					
//DeadCode JIM 18Jun96 	wpstartloopno			=32,					
//DeadCode JIM 18Jun96 	wpstoploopchkno 		=34,					
//DeadCode JIM 18Jun96 	wplaunchrcktsno 		=36,
//DeadCode JIM 18Jun96 	wpdropbombno			=38,
//DeadCode JIM 18Jun96 	wpreccyno				=40,						
//DeadCode JIM 18Jun96 	wpartspotno				=42,						
//DeadCode JIM 18Jun96 	wplauncha2gno			=44,						
//DeadCode JIM 18Jun96 	wppickleno				=46,						
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 	wpswitchtoa2gcapableno	 =48,					
//DeadCode JIM 18Jun96 	wpswitchtoa2acapableno	 =50,					
//DeadCode JIM 18Jun96 	wpeyeballtargetno		 =52,					
//DeadCode JIM 18Jun96 	wpbuzztargetno			 =54,					
//DeadCode JIM 18Jun96 	wpwarntargetno			 =56,					
//DeadCode JIM 18Jun96 	wpengagetargetno		 =58,					
//DeadCode JIM 18Jun96 	dumbshipfiremissileno	 =60,					
//DeadCode JIM 18Jun96 	dmbshpfiremslno			 =dumbshipfiremissileno,
//DeadCode JIM 18Jun96 	dumbshipescortno		 =62,
//DeadCode JIM 18Jun96 	wpattackconvoyno		 =64,					
//DeadCode JIM 18Jun96 	wptruckbridge			 =66,					
//DeadCode JIM 18Jun96 	wptruckescort			 =68,					
//DeadCode JIM 18Jun96 	last			 		 =68,	odddummy0001,
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 //for the fixed entries... not
//DeadCode JIM 18Jun96 ////the following equates index the wpactions used
//DeadCode JIM 18Jun96 ////by the 3d scripting code
//DeadCode JIM 18Jun96 	wpendscriptno,		odddummy0002,
//DeadCode JIM 18Jun96 	wpviewtargetno,		odddummy0003,
//DeadCode JIM 18Jun96 	wpstopno,			odddummy0004,
//DeadCode JIM 18Jun96 	settrackviewno,		odddummy0005,
//DeadCode JIM 18Jun96 	wpflybysndno,		odddummy0006,
//DeadCode JIM 18Jun96 	wpkillburnno,		odddummy0007,
//DeadCode JIM 18Jun96 	wpkillbrkupno,		odddummy0008,
//DeadCode JIM 18Jun96 	wpkillchuteno,		odddummy0009,
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 ////set 25aug93 - waypoint action that causes a "mission-complete"
//DeadCode JIM 18Jun96 ////message to be sent to my ai stuff
//DeadCode JIM 18Jun96 	stopmovingeventno, 	odddummy0010,			
//DeadCode JIM 18Jun96 	wptriggermainno,	odddummy0011,
//DeadCode JIM 18Jun96 	wptriggersub0no,	odddummy0012,
//DeadCode JIM 18Jun96 	wptriggersub1no,	odddummy0013,
//DeadCode JIM 18Jun96 	wptriggersub2no,	odddummy0014
//DeadCode JIM 18Jun96 	};
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 //end of mods, rdh 22/2/1993
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 //equates for use with acitemptrlist in persons			////rdh 11aug94
//DeadCode JIM 18Jun96 enum	ACItemPtrListIndx
//DeadCode JIM 18Jun96 	{	
//DeadCode JIM 18Jun96 	blueitem0num=0x0000,
//DeadCode JIM 18Jun96 	blueitem1num,
//DeadCode JIM 18Jun96 	blueitem2num,
//DeadCode JIM 18Jun96 	blueitem3num,
//DeadCode JIM 18Jun96 	blueitem4num,
//DeadCode JIM 18Jun96 	blueitem5num,
//DeadCode JIM 18Jun96 	blueitem6num,
//DeadCode JIM 18Jun96 	blueitem7num,
//DeadCode JIM 18Jun96 	reditem0num=0x0008,
//DeadCode JIM 18Jun96 	reditem1num	,
//DeadCode JIM 18Jun96 	reditem2num	,
//DeadCode JIM 18Jun96 	reditem3num	,
//DeadCode JIM 18Jun96 	reditem4num	,
//DeadCode JIM 18Jun96 	reditem5num	,
//DeadCode JIM 18Jun96 	reditem6num	,
//DeadCode JIM 18Jun96 	reditem7num	,
//DeadCode JIM 18Jun96 								
//DeadCode JIM 18Jun96 //flgreditem0num is used in wpvar and bfposvar			
//DeadCode JIM 18Jun96 //the top bit indicated that the equate is not a uniqueid	
//DeadCode JIM 18Jun96 	flgblueitem0num=	0x8000,
//DeadCode JIM 18Jun96 	flgblueitem1num,
//DeadCode JIM 18Jun96 	flgreditem0num=		0x8008,
//DeadCode JIM 18Jun96 	flgreditem1num
//DeadCode JIM 18Jun96 	};
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 //DeadCode JIM 27Nov95 #define		redaaabandno			0
//DeadCode JIM 18Jun96 //DeadCode JIM 27Nov95 #define		redgicbandno			2
//DeadCode JIM 18Jun96 //DeadCode JIM 27Nov95 #define		redsambandno			4
//DeadCode JIM 18Jun96 //DeadCode JIM 27Nov95 #define		redgrndmblbandno		6
//DeadCode JIM 18Jun96 //DeadCode JIM 27Nov95 #define		blueaaabandno			8
//DeadCode JIM 18Jun96 //DeadCode JIM 27Nov95 #define		bluegicbandno			10
//DeadCode JIM 18Jun96 //DeadCode JIM 27Nov95 #define		bluesambandno			12
//DeadCode JIM 18Jun96 //DeadCode JIM 27Nov95 #define		blugrndmblbandno	 	14
//DeadCode JIM 18Jun96 //DeadCode JIM 27Nov95 #define		redacbandno				16					
//DeadCode JIM 18Jun96 //DeadCode JIM 27Nov95 #define		blueacbandno			18					
//DeadCode JIM 18Jun96 //DeadCode JIM 27Nov95 #define		redmilbandno			20
//DeadCode JIM 18Jun96 //DeadCode JIM 27Nov95 #define		redairfldbandno			22					
//DeadCode JIM 18Jun96 //DeadCode JIM 27Nov95 #define		groupsepno				24					
//DeadCode JIM 18Jun96 //DeadCode JIM 27Nov95 #define		groupsepno				24					
//DeadCode JIM 18Jun96 //DeadCode JIM 27Nov95 #define		civilianbandno			26					
//DeadCode JIM 18Jun96 //DeadCode JIM 27Nov95 #define		smplesepbandno  	 	28					
//DeadCode JIM 18Jun96 //DeadCode JIM 27Nov95 
//DeadCode JIM 18Jun96 //DeadCode JIM 27Nov95 //formation equates						
//DeadCode JIM 18Jun96 //DeadCode JIM 27Nov95 #define		redlandcnvynum			0				
//DeadCode JIM 18Jun96 //DeadCode JIM 27Nov95 #define		redseacnvynum			redlandcnvynum + 2				
//DeadCode JIM 18Jun96 //DeadCode JIM 27Nov95 #define		aircnvynum				redseacnvynum + 2			
//DeadCode JIM 18Jun96 //DeadCode JIM 27Nov95 #define		redlandcmbtnum			aircnvynum	+	2		
//DeadCode JIM 18Jun96 //DeadCode JIM 27Nov95 #define		blueaircnvynum			redlandcmbtnum	+	2		
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 // macro		bfieldversion
//DeadCode JIM 18Jun96 // author	chris orton.
//DeadCode JIM 18Jun96 // date		wed 27 nov 1991
//DeadCode JIM 18Jun96 // description	give version control (unused at the moment) and 
//DeadCode JIM 18Jun96 //		initialise any global equates which need it at 
//DeadCode JIM 18Jun96 //		the start of a battlefield file.
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //inputs		
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //returns	
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 class	bfieldversionstruc
//DeadCode JIM 18Jun96 	{
//DeadCode JIM 18Jun96 	public:
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 	UWord	versnum,
//DeadCode JIM 18Jun96 			chknum;
//DeadCode JIM 18Jun96 	SWord	shapelist;
//DeadCode JIM 18Jun96 	};
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 // macro		bfscripttype
//DeadCode JIM 18Jun96 // author	chris orton.
//DeadCode JIM 18Jun96 // date		wed 27 nov 1991
//DeadCode JIM 18Jun96 // description	sets the type of 3d script to be played ie. normal 3d or
//DeadCode JIM 18Jun96 //		a script with an artwork backdrop instead of the normal
//DeadCode JIM 18Jun96 //		horizon code etc.
//DeadCode JIM 18Jun96 //inputs		
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //returns	
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 class	bfscripttypestruc
//DeadCode JIM 18Jun96 	{
//DeadCode JIM 18Jun96 	public:
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 	UWord	opcode,
//DeadCode JIM 18Jun96 			typenum;
//DeadCode JIM 18Jun96 	};
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 // macro		bfforeground
//DeadCode JIM 18Jun96 // author	chris orton.
//DeadCode JIM 18Jun96 // date		wed 27 nov 1991
//DeadCode JIM 18Jun96 // description	sets the file numbe for the foreground artwork
//DeadCode JIM 18Jun96 //inputs		
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //returns	
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 class	bfforegroundstruc
//DeadCode JIM 18Jun96 	{
//DeadCode JIM 18Jun96 	public:
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 	UWord	opcode,
//DeadCode JIM 18Jun96 			artfile;
//DeadCode JIM 18Jun96 	};
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 // macro		bfbackground
//DeadCode JIM 18Jun96 // author	chris orton.
//DeadCode JIM 18Jun96 // date		wed 27 nov 1991
//DeadCode JIM 18Jun96 // description	sets the file numbe for the background artwork
//DeadCode JIM 18Jun96 //inputs		
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //returns	
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 class	bfbackgroundstruc
//DeadCode JIM 18Jun96 	{
//DeadCode JIM 18Jun96 	public:
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 	UWord	opcode,
//DeadCode JIM 18Jun96 			artfile;
//DeadCode JIM 18Jun96 	};
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 // macro		bfpitch
//DeadCode JIM 18Jun96 // author	chris orton.
//DeadCode JIM 18Jun96 // date		wed 27 nov 1991
//DeadCode JIM 18Jun96 // description	sets the initial pitch for a camera item
//DeadCode JIM 18Jun96 //inputs		
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //returns	
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 class	bfpitchstruc
//DeadCode JIM 18Jun96 	{
//DeadCode JIM 18Jun96 	public:
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 	UWord	opcode;
//DeadCode JIM 18Jun96 	ANGLES	pitch;
//DeadCode JIM 18Jun96 	};
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 // macro		bfheading
//DeadCode JIM 18Jun96 // author	chris orton.
//DeadCode JIM 18Jun96 // date		wed 27 nov 1991
//DeadCode JIM 18Jun96 // description	sets the initial heading for a camera item
//DeadCode JIM 18Jun96 //inputs		
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //returns	
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 class	bfheadingstruc
//DeadCode JIM 18Jun96 	{
//DeadCode JIM 18Jun96 	public:
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 	UWord	opcode;
//DeadCode JIM 18Jun96 	ANGLES	heading;
//DeadCode JIM 18Jun96 	};
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 // macro		bfclearworld
//DeadCode JIM 18Jun96 // author	chris orton.
//DeadCode JIM 18Jun96 // date		wed 27 nov 1991
//DeadCode JIM 18Jun96 // description	clears all items loaded into the world
//DeadCode JIM 18Jun96 //		
//DeadCode JIM 18Jun96 //		
//DeadCode JIM 18Jun96 //inputs		
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //returns	
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 class	bfclearworldstruc
//DeadCode JIM 18Jun96 	{
//DeadCode JIM 18Jun96 	public:
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 	UWord	opcode;
//DeadCode JIM 18Jun96 	};
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 // macro		bfsetviewanglesrange
//DeadCode JIM 18Jun96 // author	chris orton.
//DeadCode JIM 18Jun96 // date		tue 12 nov 1991
//DeadCode JIM 18Jun96 // description	initialise the data area for a new item in
//DeadCode JIM 18Jun96 //		the battle field 
//DeadCode JIM 18Jun96 //		flags added					////rdh 07oct93
//DeadCode JIM 18Jun96 //inputs		
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //returns	
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 class	bfsetviewanglesrangestruc
//DeadCode JIM 18Jun96 	{
//DeadCode JIM 18Jun96 	public:
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 	UWord	opcode;
//DeadCode JIM 18Jun96 	ANGLES	heading,
//DeadCode JIM 18Jun96 			pitch;
//DeadCode JIM 18Jun96 	UWord	zoom;
//DeadCode JIM 18Jun96 	ANGLES	angle;
//DeadCode JIM 18Jun96 	UWord	flags;
//DeadCode JIM 18Jun96 	};
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 // macro		bfstartitemstruc
//DeadCode JIM 18Jun96 // author	chris orton.
//DeadCode JIM 18Jun96 // date		tue 12 nov 1991
//DeadCode JIM 18Jun96 // description	initialise the data area for a new item in
//DeadCode JIM 18Jun96 //		the battle field 
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //inputs		
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //returns	
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 class	bfstartitemstruc
//DeadCode JIM 18Jun96 	{
//DeadCode JIM 18Jun96 	public:
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 	UWord	opcode,
//DeadCode JIM 18Jun96 			type;
//DeadCode JIM 18Jun96 	};
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 class	bfenditemstruc
//DeadCode JIM 18Jun96 	{
//DeadCode JIM 18Jun96 	public:
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 	UWord	opcode;
//DeadCode JIM 18Jun96 	};
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 class	bfielddonestruc
//DeadCode JIM 18Jun96 	{
//DeadCode JIM 18Jun96 	public:
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 	UWord	opcode;
//DeadCode JIM 18Jun96 	};
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 // macro		foend
//DeadCode JIM 18Jun96 // author	chris orton.
//DeadCode JIM 18Jun96 // date		wed 27 nov 1991
//DeadCode JIM 18Jun96 // description	firing order end 
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //inputs		
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //returns	
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 class	foendstruc
//DeadCode JIM 18Jun96 	{
//DeadCode JIM 18Jun96 	public:
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 	UWord	opcode;
//DeadCode JIM 18Jun96 	};
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 // macro		fominrange   
//DeadCode JIM 18Jun96 // author	chris orton.
//DeadCode JIM 18Jun96 // date		wed 27 nov 1991
//DeadCode JIM 18Jun96 // description	set the minimum range at 
//DeadCode JIM 18Jun96 //		which the item should fire 
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //inputs		
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //returns	
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 class	fominrangestruc
//DeadCode JIM 18Jun96 	{
//DeadCode JIM 18Jun96 	public:
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 	UWord	opcode,
//DeadCode JIM 18Jun96 			range;
//DeadCode JIM 18Jun96 	};
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 // macro		fomaxrange   
//DeadCode JIM 18Jun96 // author	chris orton.
//DeadCode JIM 18Jun96 // date		wed 27 nov 1991
//DeadCode JIM 18Jun96 // description	set the maximum range at 
//DeadCode JIM 18Jun96 //		which the item should fire 
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //inputs		
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //returns	
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 class	fomaxrangestruc
//DeadCode JIM 18Jun96 	{
//DeadCode JIM 18Jun96 	public:
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 	UWord	opcode,
//DeadCode JIM 18Jun96 			range;
//DeadCode JIM 18Jun96 	};
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 // macro		fominhdg   
//DeadCode JIM 18Jun96 // author	chris orton.
//DeadCode JIM 18Jun96 // date		wed 27 nov 1991
//DeadCode JIM 18Jun96 // description	set the minimum hdg at 
//DeadCode JIM 18Jun96 //		which the item should fire 
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //inputs		
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //returns	
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 class	fominhdgstruc
//DeadCode JIM 18Jun96 	{
//DeadCode JIM 18Jun96 	public:
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 	UWord	opcode;
//DeadCode JIM 18Jun96 	ANGLES	hdg;
//DeadCode JIM 18Jun96 	};
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 // macro		fomaxhdg   
//DeadCode JIM 18Jun96 // author	chris orton.
//DeadCode JIM 18Jun96 // date		wed 27 nov 1991
//DeadCode JIM 18Jun96 // description	set the maximum hdg at 
//DeadCode JIM 18Jun96 //		which the item should fire 
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //inputs		
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //returns	
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 class	fomaxhdgstruc
//DeadCode JIM 18Jun96 	{
//DeadCode JIM 18Jun96 	public:
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 	UWord	opcode;
//DeadCode JIM 18Jun96 	ANGLES	hdg;
//DeadCode JIM 18Jun96 	};
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 // macro		bfitemfireorderptr
//DeadCode JIM 18Jun96 // author	chris orton.
//DeadCode JIM 18Jun96 // date		wed 4 sep 1991
//DeadCode JIM 18Jun96 // description	 
//DeadCode JIM 18Jun96 //		declare a ptr to a fire order
//DeadCode JIM 18Jun96 //inputs		
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //returns	
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 class	bffireorderptrstruc
//DeadCode JIM 18Jun96 	{
//DeadCode JIM 18Jun96 	public:
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 	UWord	opcode;
//DeadCode JIM 18Jun96 	SWord	fireorderptr;
//DeadCode JIM 18Jun96 	};
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 // macro		rtbeginno     
//DeadCode JIM 18Jun96 // author	chris orton.
//DeadCode JIM 18Jun96 // date		thu 10 oct 1991
//DeadCode JIM 18Jun96 // description
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //inputs		
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //returns	
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 class	rtbeginstruc
//DeadCode JIM 18Jun96 	{
//DeadCode JIM 18Jun96 	public:
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 	UWord	opcode;
//DeadCode JIM 18Jun96 	};
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 // macro		rtendno     
//DeadCode JIM 18Jun96 // author	chris orton.
//DeadCode JIM 18Jun96 // date		thu 10 oct 1991
//DeadCode JIM 18Jun96 // description	
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //inputs		
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //returns	
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 class	rtendstruc
//DeadCode JIM 18Jun96 	{
//DeadCode JIM 18Jun96 	public:
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 	UWord	opcode;
//DeadCode JIM 18Jun96 	};
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 //structure	wpvar        
//DeadCode JIM 18Jun96 //author		chris orton.
//DeadCode JIM 18Jun96 //date		tue 21 apr 1992
//DeadCode JIM 18Jun96 //description	 
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 class	wpvarstruc
//DeadCode JIM 18Jun96 	{
//DeadCode JIM 18Jun96 	public:
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 	UWord	opcode;
//DeadCode JIM 18Jun96 	SWord	varequ;
//DeadCode JIM 18Jun96 	};
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 //structure	wpposvar
//DeadCode JIM 18Jun96 //author		stephen tickle
//DeadCode JIM 18Jun96 //date		thu 09 dec 1993
//DeadCode JIM 18Jun96 //description	fill a waypoint's xyz from a variable via
//DeadCode JIM 18Jun96 //		the wpvar table
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 class	wpposvarstruc
//DeadCode JIM 18Jun96 	{
//DeadCode JIM 18Jun96 	public:
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 	UWord	opcode;
//DeadCode JIM 18Jun96 	SWord	varequ;
//DeadCode JIM 18Jun96 	};
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 class	wprangestruc
//DeadCode JIM 18Jun96 	{
//DeadCode JIM 18Jun96 	public:
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 	UWord	opcode;
//DeadCode JIM 18Jun96 	ULong	range;
//DeadCode JIM 18Jun96 	};
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 // macro		wplatno     
//DeadCode JIM 18Jun96 // author	chris orton.
//DeadCode JIM 18Jun96 // date		thu 10 oct 1991
//DeadCode JIM 18Jun96 // description	set the lattitude of the way point being constructed 
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //inputs		
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //returns	
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 class	wplatstruc
//DeadCode JIM 18Jun96 	{
//DeadCode JIM 18Jun96 	public:
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 	UWord	opcode;
//DeadCode JIM 18Jun96 	UWord	latdeg,
//DeadCode JIM 18Jun96     		latmin,
//DeadCode JIM 18Jun96     		latsec;
//DeadCode JIM 18Jun96 	};
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 // macro		wpvel     
//DeadCode JIM 18Jun96 // author	chris orton.
//DeadCode JIM 18Jun96 // date		thu 10 oct 1991
//DeadCode JIM 18Jun96 // description	set the velocity field of the way point being constructed 
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //inputs		
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //returns	
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 class	wpvelstruc
//DeadCode JIM 18Jun96 		{
//DeadCode JIM 18Jun96 		public:
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 		UWord	opcode;
//DeadCode JIM 18Jun96 		UWord	vel;
//DeadCode JIM 18Jun96 		};
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 // macro		bfvel     
//DeadCode JIM 18Jun96 // author	chris orton.
//DeadCode JIM 18Jun96 // date								////rdh 06may93
//DeadCode JIM 18Jun96 // description	set the velocity field of the mobileitem
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //inputs		
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //returns	
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 class	bfvelstruc
//DeadCode JIM 18Jun96 	{
//DeadCode JIM 18Jun96 	public:
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 	UWord	opcode;
//DeadCode JIM 18Jun96 	UWord	vel;
//DeadCode JIM 18Jun96 	};
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 // macro		bfformation     
//DeadCode JIM 18Jun96 // author							////rdh 07may93
//DeadCode JIM 18Jun96 // date								////rdh 06may93
//DeadCode JIM 18Jun96 // description	set the formation
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //inputs		
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //returns	
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 class	bfformationstruc
//DeadCode JIM 18Jun96 	{
//DeadCode JIM 18Jun96 	public:
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 	UWord	opcode;
//DeadCode JIM 18Jun96 	UWord	formation;
//DeadCode JIM 18Jun96 	};
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 // macro		bfuniqueband     
//DeadCode JIM 18Jun96 // author							////rdh 07may93
//DeadCode JIM 18Jun96 // date								////rdh 06may93
//DeadCode JIM 18Jun96 // description	set the uniqueband
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //inputs		
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //returns	
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 class	bfuniquebandstruc
//DeadCode JIM 18Jun96 	{
//DeadCode JIM 18Jun96 	public:
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 	UWord	opcode;
//DeadCode JIM 18Jun96     UWord	uniqueband;
//DeadCode JIM 18Jun96 	};
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 // macro		bfformleader
//DeadCode JIM 18Jun96 // author	rdh
//DeadCode JIM 18Jun96 // date		27/2/1993
//DeadCode JIM 18Jun96 // description	
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //inputs		
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //returns	
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 class	bfformleaderstruc
//DeadCode JIM 18Jun96 	{
//DeadCode JIM 18Jun96 	public:
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 	UWord	opcode;
//DeadCode JIM 18Jun96 	};
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 // macro		wplongno     
//DeadCode JIM 18Jun96 // author	chris orton.
//DeadCode JIM 18Jun96 // date		thu 10 oct 1991
//DeadCode JIM 18Jun96 // description	set the longtitude of the way point being constructed 
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //inputs		
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //returns	
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 class	wplongstruc
//DeadCode JIM 18Jun96 	{
//DeadCode JIM 18Jun96 	public:
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 	UWord	opcode,
//DeadCode JIM 18Jun96 			longdeg,
//DeadCode JIM 18Jun96 			longmin,
//DeadCode JIM 18Jun96 			longsec;
//DeadCode JIM 18Jun96 	};
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 // macro		wpaltno     
//DeadCode JIM 18Jun96 // author	chris orton.
//DeadCode JIM 18Jun96 // date		thu 10 oct 1991
//DeadCode JIM 18Jun96 // description	set the alttitude of the way point being constructed 
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //inputs		
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //returns	
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 class	wpaltstruc
//DeadCode JIM 18Jun96 	{
//DeadCode JIM 18Jun96 	public:
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 	UWord	opcode,
//DeadCode JIM 18Jun96 			altfeet;
//DeadCode JIM 18Jun96 	};
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 // macro		wpwxyzno     
//DeadCode JIM 18Jun96 // author	chris orton.
//DeadCode JIM 18Jun96 // date		thu 10 oct 1991
//DeadCode JIM 18Jun96 // description	set the wxyz of the way point being constructed 
//DeadCode JIM 18Jun96 //		many edits, rdh 2/3/1993
//DeadCode JIM 18Jun96 //inputs		
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //returns	
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 class	wpwxyzstruc
//DeadCode JIM 18Jun96 	{
//DeadCode JIM 18Jun96 	public:
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 	UWord	opcode;
//DeadCode JIM 18Jun96 	ULong	wx,
//DeadCode JIM 18Jun96 			wy,
//DeadCode JIM 18Jun96 			wz;
//DeadCode JIM 18Jun96 	UWord	ctrl;
//DeadCode JIM 18Jun96 	};
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 // macro		wpaction     
//DeadCode JIM 18Jun96 // author	chris orton.
//DeadCode JIM 18Jun96 // date		thu 10 oct 1991
//DeadCode JIM 18Jun96 // description	set the action for the way point being constructed 
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //inputs		
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //returns	
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 class	wpactionstruc
//DeadCode JIM 18Jun96 	{
//DeadCode JIM 18Jun96 	public:
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 	UWord	opcode,
//DeadCode JIM 18Jun96 			action;
//DeadCode JIM 18Jun96 	};
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 //author		stephen tickle.
//DeadCode JIM 18Jun96 //date		tue 8 mar 1994
//DeadCode JIM 18Jun96 //description	set flags in waypoint structure
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 class	wpflagsstruc
//DeadCode JIM 18Jun96 	{
//DeadCode JIM 18Jun96 	public:
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 	UWord	opcode,
//DeadCode JIM 18Jun96 			flags;
//DeadCode JIM 18Jun96 	};
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 // macro		wpbegin      
//DeadCode JIM 18Jun96 // author	chris orton.
//DeadCode JIM 18Jun96 // date		thu 10 oct 1991
//DeadCode JIM 18Jun96 // description	signal the begining of a waypoint structure 
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //inputs		
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //returns	
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 class	wpbeginstruc
//DeadCode JIM 18Jun96 	{
//DeadCode JIM 18Jun96 	public:
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 	UWord	opcode;
//DeadCode JIM 18Jun96 	};
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 // macro		wpend        
//DeadCode JIM 18Jun96 // author	chris orton.
//DeadCode JIM 18Jun96 // date		thu 10 oct 1991
//DeadCode JIM 18Jun96 // description	signal the end of a waypoint structure 
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //inputs		
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //returns	
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 class	wpendstruc
//DeadCode JIM 18Jun96 	{
//DeadCode JIM 18Jun96 	public:
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 	UWord	opcode;
//DeadCode JIM 18Jun96 	};
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 // macro		wploop        
//DeadCode JIM 18Jun96 // author	chris orton.
//DeadCode JIM 18Jun96 // date		thu 10 oct 1991
//DeadCode JIM 18Jun96 // description	loop the last wp of a route to the first
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //inputs		
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //returns	
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 class	wploopstruc
//DeadCode JIM 18Jun96 	{
//DeadCode JIM 18Jun96 	public:
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 	UWord	opcode;
//DeadCode JIM 18Jun96 	};
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 //structure	bfsetunfvar	
//DeadCode JIM 18Jun96 //author		
//DeadCode JIM 18Jun96 //date		
//DeadCode JIM 18Jun96 //description	
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 class	bfsetunfvarstruc
//DeadCode JIM 18Jun96 	{
//DeadCode JIM 18Jun96 	public:
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 	UWord	opcode,
//DeadCode JIM 18Jun96 			unfcode;
//DeadCode JIM 18Jun96 	};
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 //structure	bfdutystruc  
//DeadCode JIM 18Jun96 //author		chris orton.
//DeadCode JIM 18Jun96 //date		mon 13 apr 1992
//DeadCode JIM 18Jun96 //description	 
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 class	bfdutystruc  
//DeadCode JIM 18Jun96 	{
//DeadCode JIM 18Jun96 	public:
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 	UWord	opcode,
//DeadCode JIM 18Jun96 			duty;
//DeadCode JIM 18Jun96 	};
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 //structure	bfshapestruc
//DeadCode JIM 18Jun96 //author		chris orton.
//DeadCode JIM 18Jun96 //date		fri 3 apr 1992
//DeadCode JIM 18Jun96 //description	 
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 ////set 29nov93	added extra parameter to exclude shapes from bfshapelist
//DeadCode JIM 18Jun96 ////		(useful for excluding generic shape numbers)
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 class	bfshapestruc
//DeadCode JIM 18Jun96 	{
//DeadCode JIM 18Jun96 	public:
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 	UWord			opcode;
//DeadCode JIM 18Jun96 	ShapeNum		shapeno;
//DeadCode JIM 18Jun96 	};
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 // macro		bfsetactype
//DeadCode JIM 18Jun96 // author	////rdh 10sep93
//DeadCode JIM 18Jun96 // description	 
//DeadCode JIM 18Jun96 //inputs		
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //returns	
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 class	bfsetactypestruc
//DeadCode JIM 18Jun96 	{
//DeadCode JIM 18Jun96 	public:
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 	UWord	opcode,
//DeadCode JIM 18Jun96 			actype;
//DeadCode JIM 18Jun96 	};
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 // macro		bfsetpos
//DeadCode JIM 18Jun96 // author	////rdh 10sep93
//DeadCode JIM 18Jun96 // description	 
//DeadCode JIM 18Jun96 //inputs		
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //returns	
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 class	bfsetposstruc
//DeadCode JIM 18Jun96 	{
//DeadCode JIM 18Jun96 	public:
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 	UWord	opcode,
//DeadCode JIM 18Jun96 			uniqueid,
//DeadCode JIM 18Jun96 			genericpos;
//DeadCode JIM 18Jun96 	};
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 // macro		bfsetvar
//DeadCode JIM 18Jun96 // author	////rdh 10sep93
//DeadCode JIM 18Jun96 // description	 
//DeadCode JIM 18Jun96 //inputs		
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //returns	
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 class	bfsetvarstruc
//DeadCode JIM 18Jun96 	{
//DeadCode JIM 18Jun96 	public:
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 	UWord	opcode,
//DeadCode JIM 18Jun96 			variable,
//DeadCode JIM 18Jun96 			lowlimit,
//DeadCode JIM 18Jun96 			stepsize,
//DeadCode JIM 18Jun96 			noofsteps;
//DeadCode JIM 18Jun96 	};
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 // macro		bffirstview  
//DeadCode JIM 18Jun96 // author	chris orton.
//DeadCode JIM 18Jun96 // date		mon 7 oct 1991
//DeadCode JIM 18Jun96 // description	set the initial view from this item 
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //inputs		
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //returns	
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 class	bffirstviewstruc
//DeadCode JIM 18Jun96 	{
//DeadCode JIM 18Jun96 	public:
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 	UWord	opcode,
//DeadCode JIM 18Jun96 			view;
//DeadCode JIM 18Jun96 	};
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 #define	frontno				pilotedacview+insideview
//DeadCode JIM 18Jun96 #define	outsideviewno		pilotedacview+notrackview	
//DeadCode JIM 18Jun96 #define	trackviewno			pilotedacview+trackview		
//DeadCode JIM 18Jun96 #define	sateliteviewno		pilotedacview+satview		
//DeadCode JIM 18Jun96 #define	homebaseviewno		homebaseview+notrackview	
//DeadCode JIM 18Jun96 #define	padlockviewno		nearunfrview+outlockview
//DeadCode JIM 18Jun96 #define	combatviewno		aiunfrview+outlockview
//DeadCode JIM 18Jun96 #define	missileviewno		missileview+trackview
//DeadCode JIM 18Jun96 #define	unfriendlyviewno	aiunfrview+trackview
//DeadCode JIM 18Jun96 #define	chaseviewno			pilotedacview+chaseview	
//DeadCode JIM 18Jun96 #define	fleaderlockno		actualfrleadview+outlockview
//DeadCode JIM 18Jun96 #define	uiviewno		 	alreadysetview+trackview
//DeadCode JIM 18Jun96 #define	nrgrndtrgno			neargndview+outlockview
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 //structure	bfposvar     
//DeadCode JIM 18Jun96 //author		chris orton.
//DeadCode JIM 18Jun96 //date		tue 21 apr 1992
//DeadCode JIM 18Jun96 //description	 
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 class	bfposvarstruc
//DeadCode JIM 18Jun96 	{
//DeadCode JIM 18Jun96 	public:
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 	UWord	opcode,
//DeadCode JIM 18Jun96 			varequ;
//DeadCode JIM 18Jun96 	};
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 // macro		bfwxyz
//DeadCode JIM 18Jun96 // author	chris orton.
//DeadCode JIM 18Jun96 // date		wed 4 sep 1991
//DeadCode JIM 18Jun96 // description	 
//DeadCode JIM 18Jun96 //		declare an initial world coordinate
//DeadCode JIM 18Jun96 //inputs		
//DeadCode JIM 18Jun96 //	many edits, rdh 2/3/1993
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //returns	
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //usage
//DeadCode JIM 18Jun96 //		_bfwxyz	000ab937h,00000080h,0017dbe8h,ctrl
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //		ctrl options: nothing and delta
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 class	bfwxyzstruc
//DeadCode JIM 18Jun96 	{
//DeadCode JIM 18Jun96 	public:
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 	UWord	opcode;
//DeadCode JIM 18Jun96 	ULong	wx;
//DeadCode JIM 18Jun96 	UWord	wy;
//DeadCode JIM 18Jun96 	ULong	wz;
//DeadCode JIM 18Jun96 	UWord	ctrl;
//DeadCode JIM 18Jun96 	};
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 // macro		bfitemlat
//DeadCode JIM 18Jun96 // author	chris orton.
//DeadCode JIM 18Jun96 // date		wed 4 sep 1991
//DeadCode JIM 18Jun96 // description	 
//DeadCode JIM 18Jun96 //		declare an initial world coordinate
//DeadCode JIM 18Jun96 //inputs		
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //returns	
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 class	bflatstruc
//DeadCode JIM 18Jun96 	{
//DeadCode JIM 18Jun96 	public:
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 	UWord	opcode,
//DeadCode JIM 18Jun96 		   	latdeg,
//DeadCode JIM 18Jun96     		latmin,
//DeadCode JIM 18Jun96     		latsec;
//DeadCode JIM 18Jun96 	};
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 // macro		bfitemlong
//DeadCode JIM 18Jun96 // author	chris orton.
//DeadCode JIM 18Jun96 // date		wed 4 sep 1991
//DeadCode JIM 18Jun96 // description	 
//DeadCode JIM 18Jun96 //		declare an initial world coordinate
//DeadCode JIM 18Jun96 //inputs		
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //returns	
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 class	bflongstruc
//DeadCode JIM 18Jun96 	{
//DeadCode JIM 18Jun96 	public:
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 	UWord	opcode,
//DeadCode JIM 18Jun96 			longdeg,
//DeadCode JIM 18Jun96 			longmin,
//DeadCode JIM 18Jun96 			longsec;
//DeadCode JIM 18Jun96 	};
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 // macro		bfitemalt
//DeadCode JIM 18Jun96 // author	chris orton.
//DeadCode JIM 18Jun96 // date		wed 4 sep 1991
//DeadCode JIM 18Jun96 // description	 
//DeadCode JIM 18Jun96 //		declare an initial world coordinate
//DeadCode JIM 18Jun96 //inputs		
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //returns	
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 class	bfaltstruc
//DeadCode JIM 18Jun96 	{
//DeadCode JIM 18Jun96 	public:
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 	UWord	opcode,
//DeadCode JIM 18Jun96 			altfeet;
//DeadCode JIM 18Jun96 	};
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 // macro		bfaltrnd
//DeadCode JIM 18Jun96 // author	////rdh 10sep93
//DeadCode JIM 18Jun96 // description	 
//DeadCode JIM 18Jun96 //inputs		
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //returns	
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 class	bfaltrndstruc
//DeadCode JIM 18Jun96 	{
//DeadCode JIM 18Jun96 	public:
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 	UWord	opcode,
//DeadCode JIM 18Jun96     		altfeet,
//DeadCode JIM 18Jun96 			stepsize,
//DeadCode JIM 18Jun96 			noofsteps;
//DeadCode JIM 18Jun96 	};
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 // macro		bfrelalt
//DeadCode JIM 18Jun96 // author	////rdh 10sep93
//DeadCode JIM 18Jun96 // description	 
//DeadCode JIM 18Jun96 //inputs		
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //returns	
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 class	bfrelaltstruc
//DeadCode JIM 18Jun96 	{
//DeadCode JIM 18Jun96 	public:
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 	UWord	opcode;
//DeadCode JIM 18Jun96 	UWord	relac,
//DeadCode JIM 18Jun96 	    	altfeet,
//DeadCode JIM 18Jun96 			stepsize,
//DeadCode JIM 18Jun96 			noofsteps;
//DeadCode JIM 18Jun96 	};
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 // macro		bfrelcourse
//DeadCode JIM 18Jun96 // author						   ////cpo 30sep93
//DeadCode JIM 18Jun96 // description	 
//DeadCode JIM 18Jun96 //inputs		
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //returns	
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 class	bfrelcoursestruc
//DeadCode JIM 18Jun96 	{
//DeadCode JIM 18Jun96 	public:
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 	UWord	opcode;
//DeadCode JIM 18Jun96 	UWord	relac,
//DeadCode JIM 18Jun96     		hdgoffset,
//DeadCode JIM 18Jun96 			stepsize,
//DeadCode JIM 18Jun96 			noofsteps;
//DeadCode JIM 18Jun96 	};
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 // macro		bfsetmission
//DeadCode JIM 18Jun96 // author						   ////cpo 30sep93
//DeadCode JIM 18Jun96 // description	 
//DeadCode JIM 18Jun96 //inputs		
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //returns	
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 class	bfsetmissionstruc
//DeadCode JIM 18Jun96 	{
//DeadCode JIM 18Jun96 	public:
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 	UWord	opcode;
//DeadCode JIM 18Jun96 	union
//DeadCode JIM 18Jun96 		{
//DeadCode JIM 18Jun96 		UWord	variable;
//DeadCode JIM 18Jun96 		UWord	targetlist;
//DeadCode JIM 18Jun96 		};
//DeadCode JIM 18Jun96 	union
//DeadCode JIM 18Jun96 		{
//DeadCode JIM 18Jun96 		UWord	case0;
//DeadCode JIM 18Jun96 		UWord	trgtbrief;
//DeadCode JIM 18Jun96 		};
//DeadCode JIM 18Jun96 	union
//DeadCode JIM 18Jun96 		{
//DeadCode JIM 18Jun96 		UWord	case1;
//DeadCode JIM 18Jun96 		UWord	acbfield;
//DeadCode JIM 18Jun96 		};
//DeadCode JIM 18Jun96 	UWord	case2;
//DeadCode JIM 18Jun96 	};
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 // macro		bfrelpos
//DeadCode JIM 18Jun96 // author	////rdh 10sep93
//DeadCode JIM 18Jun96 // description	 
//DeadCode JIM 18Jun96 //inputs		
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //returns	
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 class	bfrelposstruc
//DeadCode JIM 18Jun96 	{
//DeadCode JIM 18Jun96 	public:
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 	UWord	opcode,
//DeadCode JIM 18Jun96 			relac;
//DeadCode JIM 18Jun96 	ANGLES	relhdg,
//DeadCode JIM 18Jun96 			hdgstep;
//DeadCode JIM 18Jun96 	UWord	hdgnoofsteps,
//DeadCode JIM 18Jun96     		range,
//DeadCode JIM 18Jun96 			rngstepsize,
//DeadCode JIM 18Jun96 			rngnoofsteps;
//DeadCode JIM 18Jun96 	};
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 // macro		bfsetclipregion
//DeadCode JIM 18Jun96 // author	chris orton.
//DeadCode JIM 18Jun96 // date		wed 4 sep 1991
//DeadCode JIM 18Jun96 // description	 
//DeadCode JIM 18Jun96 //		set the area of the screen to be updated each cycle during
//DeadCode JIM 18Jun96 //		the script playback
//DeadCode JIM 18Jun96 //inputs		
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //returns	
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 class	bfsetclipregionstruc
//DeadCode JIM 18Jun96 	{
//DeadCode JIM 18Jun96 	public:
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 	UWord	opcode,
//DeadCode JIM 18Jun96 			left,right,top,bottom;
//DeadCode JIM 18Jun96 	};
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 // macro		bfacmovecode
//DeadCode JIM 18Jun96 // author	chris orton.
//DeadCode JIM 18Jun96 // date		wed 4 sep 1991
//DeadCode JIM 18Jun96 // description	 
//DeadCode JIM 18Jun96 //		set an aircraft items move code
//DeadCode JIM 18Jun96 //inputs		
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //returns	
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 class	bfacmovecodestruc
//DeadCode JIM 18Jun96 	{
//DeadCode JIM 18Jun96 	public:
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 	UWord	opcode,
//DeadCode JIM 18Jun96 			leadermovec,
//DeadCode JIM 18Jun96 			leadermvstat,
//DeadCode JIM 18Jun96 			wingmovec,
//DeadCode JIM 18Jun96 			wingmvstat;
//DeadCode JIM 18Jun96 	};
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 //status definitions
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 #define takingoff 0
//DeadCode JIM 18Jun96 #define ready 0
//DeadCode JIM 18Jun96 #define combat 0
//DeadCode JIM 18Jun96 #define combatwing 0
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 // macro		bfsetattack
//DeadCode JIM 18Jun96 // author	////rdh 12sep93
//DeadCode JIM 18Jun96 // description	 
//DeadCode JIM 18Jun96 //		
//DeadCode JIM 18Jun96 //inputs		
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //returns	
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 class	bfacsetattackstruc
//DeadCode JIM 18Jun96 	{
//DeadCode JIM 18Jun96 	public:
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 	UWord	opcode,
//DeadCode JIM 18Jun96     		manoeuvreflag,
//DeadCode JIM 18Jun96     		unfriendly;
//DeadCode JIM 18Jun96 	};
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 #define	stationarynum		0
//DeadCode JIM 18Jun96 #define	autofollowwpnum		stationarynum	+ 2
//DeadCode JIM 18Jun96 #define	autotaxinum			autofollowwpnum + 2
//DeadCode JIM 18Jun96 #define	autowaitnum			autotaxinum	+2
//DeadCode JIM 18Jun96 #define	autoescortnum	 	autowaitnum	+2
//DeadCode JIM 18Jun96 #define	grndfollowwpnum	 	autoescortnum	+2
//DeadCode JIM 18Jun96 #define	autoqtakeoffnum  	grndfollowwpnum + 2
//DeadCode JIM 18Jun96 #define	autoengagenum		autoqtakeoffnum +2
//DeadCode JIM 18Jun96 #define	immediatewpnum		autoengagenum	+2
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 // macro		bfbuddy
//DeadCode JIM 18Jun96 // author	chris orton.
//DeadCode JIM 18Jun96 // date		wed 4 sep 1991
//DeadCode JIM 18Jun96 // description	 
//DeadCode JIM 18Jun96 //		place the current vehicle in position as the buddy
//DeadCode JIM 18Jun96 //		of a previously placed vehicle
//DeadCode JIM 18Jun96 //inputs		
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //returns	
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 class	bfbuddystruc
//DeadCode JIM 18Jun96 	{
//DeadCode JIM 18Jun96 	public:
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 	UWord	opcode,
//DeadCode JIM 18Jun96 			formation;
//DeadCode JIM 18Jun96 	};
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 // macro		bfsetacptr
//DeadCode JIM 18Jun96 // author	////rdh 10sep93
//DeadCode JIM 18Jun96 // description	 
//DeadCode JIM 18Jun96 //inputs		
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //returns	
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 class	bfsetacptrstruc
//DeadCode JIM 18Jun96 	{
//DeadCode JIM 18Jun96 	public:
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 	UWord	opcode,
//DeadCode JIM 18Jun96 			acnum;
//DeadCode JIM 18Jun96 	};
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 // macro		bfsetcounter
//DeadCode JIM 18Jun96 // author	////rdh 10sep93
//DeadCode JIM 18Jun96 // description	 
//DeadCode JIM 18Jun96 //inputs		
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //returns	
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 class	bfsetcounterstruc
//DeadCode JIM 18Jun96 	{
//DeadCode JIM 18Jun96 	public:
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 	UWord	opcode,
//DeadCode JIM 18Jun96 			counter;
//DeadCode JIM 18Jun96 	};
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 // macro		bfdeccounterje
//DeadCode JIM 18Jun96 // author	////rdh 10sep93
//DeadCode JIM 18Jun96 // description	 
//DeadCode JIM 18Jun96 //inputs		
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //returns	
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 class	bfdeccounterjestruc
//DeadCode JIM 18Jun96 	{
//DeadCode JIM 18Jun96 	public:
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 	UWord	opcode;
//DeadCode JIM 18Jun96     SWord	plabel;
//DeadCode JIM 18Jun96 	};
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 // macro		bfcmpje
//DeadCode JIM 18Jun96 // author	////rdh 15sep93
//DeadCode JIM 18Jun96 // description	 
//DeadCode JIM 18Jun96 //inputs		
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //returns	
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 class	bfcmpjestruc
//DeadCode JIM 18Jun96 	{
//DeadCode JIM 18Jun96 	public:
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 	UWord	opcode,
//DeadCode JIM 18Jun96 			variable;
//DeadCode JIM 18Jun96 	SWord	constant,
//DeadCode JIM 18Jun96     		plabel;
//DeadCode JIM 18Jun96 	};
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 // macro		bfitemrouteptr
//DeadCode JIM 18Jun96 // author	chris orton.
//DeadCode JIM 18Jun96 // date		wed 4 sep 1991
//DeadCode JIM 18Jun96 // description	 
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //inputs		
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //returns	
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 class	bfrouteptrstruc
//DeadCode JIM 18Jun96 	{
//DeadCode JIM 18Jun96 	public:
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 	UWord	opcode;
//DeadCode JIM 18Jun96     SWord	routeptr;
//DeadCode JIM 18Jun96 	};
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 // macro		bfnationality
//DeadCode JIM 18Jun96 // author	chris orton.
//DeadCode JIM 18Jun96 // date		wed 4 sep 1991
//DeadCode JIM 18Jun96 // description	
//DeadCode JIM 18Jun96 //		set the nationality of an item 
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //inputs		
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //returns	
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 #define	manualpilotac  0x4000
//DeadCode JIM 18Jun96 #define	subjectac      0x8000
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 #define	bluepilotsub	blueforce+manualpilotac+subjectac
//DeadCode JIM 18Jun96 #define	bluepilot		blueforce+manualpilotac
//DeadCode JIM 18Jun96 #define	redpilotsub		redforce+manualpilotac+subjectac
//DeadCode JIM 18Jun96 #define	redpilot		redforce+manualpilotac
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 class	bfnationalitystruc
//DeadCode JIM 18Jun96 	{
//DeadCode JIM 18Jun96 	public:
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 	UWord	opcode,
//DeadCode JIM 18Jun96     		country;
//DeadCode JIM 18Jun96 	};
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 // macro		bfaddtype    
//DeadCode JIM 18Jun96 // author	chris orton.
//DeadCode JIM 18Jun96 // date		wed 4 sep 1991
//DeadCode JIM 18Jun96 // description	set the aircraft or vehicle type f16, a10 etc
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //inputs		
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //returns	
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 class	bftypestruc
//DeadCode JIM 18Jun96 	{
//DeadCode JIM 18Jun96 	public:
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 	UWord	opcode,
//DeadCode JIM 18Jun96 			type;
//DeadCode JIM 18Jun96 	};
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 // macro		bfaddtarget
//DeadCode JIM 18Jun96 // author	////rdh 04jun93
//DeadCode JIM 18Jun96 // description	make an item a target for ground attack
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //inputs		
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //returns	
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 class	bftargetstruc
//DeadCode JIM 18Jun96 	{
//DeadCode JIM 18Jun96 	public:
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 	UWord	opcode,
//DeadCode JIM 18Jun96 			side;
//DeadCode JIM 18Jun96 	};
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 // macro		bfdamage
//DeadCode JIM 18Jun96 // author	////rdh 25apr94
//DeadCode JIM 18Jun96 // description	give ac some initial damage
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //inputs		
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //returns	
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 class	bfdamagestruc
//DeadCode JIM 18Jun96 	{
//DeadCode JIM 18Jun96 	public:
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 	UWord	opcode,
//DeadCode JIM 18Jun96 			damagelevel;
//DeadCode JIM 18Jun96 	};
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 // macro		bfskill
//DeadCode JIM 18Jun96 // author	////rdh 05jul94
//DeadCode JIM 18Jun96 // description	modifies the group skill
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //inputs		
//DeadCode JIM 18Jun96 //
//DeadCode JIM 18Jun96 //returns	
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 class	bfskillstruc
//DeadCode JIM 18Jun96 	{
//DeadCode JIM 18Jun96 	public:
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 	UWord	opcode;
//DeadCode JIM 18Jun96 	SWord	modifier;
//DeadCode JIM 18Jun96 	};
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 //author         jim     
//DeadCode JIM 18Jun96 //date           wed 27 nov 1991
//DeadCode JIM 18Jun96 //description    declare  use of a particular set of weapons
//DeadCode JIM 18Jun96 //inputs		armspackage is an integer (equate mayhap?)
//DeadCode JIM 18Jun96 //		to reference the actual weapon set declared in main memory.
//DeadCode JIM 18Jun96 //------------------------------------------------------------------------------
//DeadCode JIM 18Jun96 #define	fuel		2
//DeadCode JIM 18Jun96 #define	medbomb  	4
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 class	bfweapsetstruc
//DeadCode JIM 18Jun96 	{
//DeadCode JIM 18Jun96 	public:
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 	UWord	opcode,
//DeadCode JIM 18Jun96 			weapsel;
//DeadCode JIM 18Jun96 	};
//DeadCode JIM 18Jun96 
//DeadCode JIM 18Jun96 #endif
