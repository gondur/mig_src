//
// The battlenode portion of node.h
//
//

struct	TeamDef;
struct	SuperBattleNode;
struct	SuperBattleNode
{
	struct	IntraLink
	{
		enum	TerrainType
		{
			ATTACKEASY=1024-30,
			ATTACKADV=1024-10,
			NOADV=1024,
			DEFENDADV=1024+10,
			DEFENDEASY=1024+30,
			TERRAINFLAGS=-2048,
			TANKSHIDE=2048,
			TANKSLOST=4096,
			INITFORCE=32768

		};
		TerrainType	terrain;
		int	TerrainAdvantage() {return int(terrain &~TERRAINFLAGS)-NOADV;}
		FileNum		waitreinforcehere,		//wait here to attack main node
					attackmain,				//attack main node
					defendmain,				//main node defenders
					retreatfromhere;		//
		UniqueID	uid;
		TeamDef*	occupier;					//filled at runtime
	};
	struct	InterLink
	{
		UniqueID	uid;
		FileNum		homeapproach,homeretreat,
					awayapproach,awayretreat;
		int		redtransportmethodname;
	};
	struct	FlankLink
	{
		enum	NonLinks
		{	ALL_LINKS_GOOD=0,
			NOT_OL=1,	NOT_OR=2,	NOT_OUT=3,
			NOT_ML=4,	NOT_MR=8,	NOT_MID=12,
			NOT_IL=16,	NOT_IR=32,	NOT_IN=48,
			NOT_LEFT=21,NOT_RIGHT=42,NOT_LINKED=63
		};
		UniqueID	left,right;
		NonLinks	nonlinks;
		SuperBattleNode		*leftnode,*rightnode;	//filled at loadtime
	};

	UniqueID	mainuid;int	mainids;
	FlankLink	flanks;
	IntraLink	in,out;
	InterLink	innerlink;
	TeamDef*	occupier;					//filled at runtime	
	SuperBattleNode	*innode,*firstoutnode;//filled at loadtime
};

BITABLE(SuperBattleNode::FlankLink::NonLinks);
BITABLE(SuperBattleNode::IntraLink::TerrainType);


struct	TeamDef
{	//all saved
enum	Team		{HOME,AWAY};

enum	ForceType	{TROOPSONLY,MORTAR,MORTARTRUCK,TANKS,ARTILLARY,MAXFORCETYPES,MAXFORCENAMES};
enum	Action	{	STAY_HERE,
					TELEPORT,
					LOSE_FORCE,
					MERGE_FORCE,
					MOVE_FORWARD,
					ATTACK,
					RETREAT,
					RETREAT_UNDER_FIRE,
					//extras to make front end interesting
					//However we had to think fast for the text!	  //JIM 18/06/99
					DEFEND_ATTACK,
					WAIT_REINFORCE,
					MOVE_REINFORCE,
					MOVE_TOATTACK=MOVE_REINFORCE,	//CLUDGE!!!		  //JIM 18/06/99
					STAY_BIGGUNS,
					NEW_FORCE
				};
	SWord			strength;
 	Team			team;			//home or away
	int				forcename;
	ForceType		forcetype;		//
	Action			action;
	Action			namedaction;
	enum			{LEFTFLANKFRIEND=0x10000,LEFTFLANKENEMY=0x20000,RIGHTFLANKFRIEND=0x40000,RIGHTFLANKENEMY=0x80000,REARGUNFRIEND=0x100000,REARGUNENEMY=0x200000};
	int				advantagepriority;
	UniqueID		location,nextlocation;
	enum	{MAX_LOSSES=16};
	UWord			lastlosses;
	UWord			lastlostforces;
	SuperBattleNode	*node,*nextnode;	//filled after loading
	void	DiagnosticOutput(char*);
};


struct	BattleStruct
{	//nodelist is loaded complete for current frontline
	bool	NextAttackDecisions();
	bool	PostAttackDecisions();
	bool	SetupFirstDay(Nationality hometeam,int homestrength,int awaystrength);
	bool	NewSetupFirstDay(const int* hometeamnames,const int* awayteamnames,int homestrength,int awaystrength);
	static	bool	NextAttackDecision(TeamDef* team);
	static	bool	PostAttackDecision(TeamDef* team);
	static	bool	PostMoveDecision(TeamDef* team);
	bool	BattleField(int teamnum,FileNum& fil,UniqueID& src,UniqueID& trg,int& mainforce,int& extraforce);
	enum	{MAXNODES=60,MAXTEAMS=32};
	SuperBattleNode	nodelist[MAXNODES];		//SOME FIXES ON LOADING
	SuperBattleNode* homenodes;
	SuperBattleNode* awaynodes;

	TeamDef		teamlist[MAXTEAMS];		//S
	int	usednodes,
		usedteams;						//S
	int		LoadBattleNodes(FileNum f);
	void	LinkBattleNodes();
	void	LinkTeams();
	bool useFAC;
	TeamDef*	FindTeamAtLocation(UniqueID u);
	int			FindLocationDescription(UniqueID u);
	int faccallsign;
};

	
struct	SuperBattleDesc
{

	enum	{MAXNODES=BattleStruct::MAXNODES};
	struct
	{
		char*	filename;
		char*   equatename;
		char*	linenum;
	}	names;
	struct	Header
	{
		UniqueID	awayreinforceleft,
					homereinforceleft;
	}	header;
	SuperBattleNode	nodelist[MAXNODES];
};
