#ifndef	AAA_Included
#define	AAA_Included

struct	AaaMainList
{
	enum	{SUBLISTSIZE=16};
	struct	AaaSubList
	{
		ItemPtr	aaaitem[SUBLISTSIZE];
		AaaSubList*	next;
		ItemPtr&	operator[](int i) {return (aaaitem[i]);}

	CON	AaaSubList()	{next=this;for (int i=0;i<SUBLISTSIZE;i++)	aaaitem[i]=NULL;}
	};

	ULong	aaaind;
	AaaSubList	*aaalist;

	CON		AaaMainList()	{aaaind=0;aaalist=new AaaSubList;}
	DES		~AaaMainList();	

	void	operator +=(ItemPtr i);
	void	operator -=(ItemPtr i);

};

struct	EventRec;

struct	SleepList:AaaMainList
{
	AaaMainList& Live_List;
	CON	SleepList(AaaMainList& Live):	Live_List(Live) {blockradio=NULL;}
	void	Event();
	void	AddItemEvents(EventRec* evlist);
	AaaSubList* blockradio;
};

struct	LiveList:AaaMainList
{
  	SleepList	sleeplist;
  	SleepList	sleeplistbackup;
	CON		LiveList(WorldStuff* world);
	void	Event();
	void	operator +=(ItemPtr i)	{sleeplist+=i;}	  
	void	BackupSleepList();
	int		ArchiveLiveList(UWord* archive,int archivesize,int skipsize=0);
	void	RestoreSleepList();
	void	ApplyLiveList(UWord* archive,int archivesize);

};	
#endif
