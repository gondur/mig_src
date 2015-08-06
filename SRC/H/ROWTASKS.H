// RowTasks.h: interface for the RowanTasks class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ROWTASKS_H__C2978741_E0E8_11D1_9FD6_D0EC00C10000__INCLUDED_)
#define AFX_ROWTASKS_H__C2978741_E0E8_11D1_9FD6_D0EC00C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
struct	StackTimes
{
	int		RoutineAddr;
	int		EntryTime;	//probably in units of PT*64K - i.e. 200Mhz returns  3051 Hz
	char	Task;
	char	spare;
	UWord	EntryCount;	//number of times called
};

class RowanTasks  
{
	enum	{MAX_TASKS=32,MAX_IGNORES=512,MAX_STACKINGS=2048,MAX_LOGS=4096};
	//As each task starts, it's stack address is logged here.
	//A call with lower stack address is the same task.
	//If this table is empty then no logging can take place
	static	ULong		taskstacks[];
	//sanity checks... was last caller same as the return address being logged?
	//If not, logging must be disabled, as using pascal style ret n (probably)
	static	int		lastcaller[];		
	static	int		laststack[];

	//Until tasks are logged, they can't be stacked. 
	//This table logs top level routines that contain logging code 
	//and therefore can't be logged themsselves
	static	void*	RoutinesToIgnore[];

	//This table logs statistics for 
	static	StackTimes	stacktimes[];

	//These tables match the jump/call table of exit procedures
	static	int		RoutineAddresses[];
	static	int		ReturnAddresses[];
	static	int		StartTimes[];


//	static	int	ReturnAddresses[2048];

	static	int		semaphore;
	static	int		lasttasknum;

public:
	RowanTasks();
	~RowanTasks();
	static 	int	StartTask();
	static 	void	EndTask();
	static 	int		GetCurrTask();
	static 	Bool	SameTaskAs(int);
	static 	int		GetMyStackTimesIndex();
	static 	int		GetProcStackTimesIndex(void*);
	static 	int		GetTaskProcStackTimesIndex(int,void*);
	static 	StackTimes&	GetStackTimeStats(int);
};

#endif // !defined(AFX_ROWTASKS_H__C2978741_E0E8_11D1_9FD6_D0EC00C10000__INCLUDED_)
