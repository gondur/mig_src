//------------------------------------------------------------------------------
//Filename       install.h
//System         
//Author         Dave Whiteside
//Date           Mon 1 Apr 1996
//Description    Install the game
//------------------------------------------------------------------------------
#ifndef	INSTALL_Included
#define	INSTALL_Included

#define	DEFAULT_INSTALL 0
#include	<s:\watcom\h\time.h>

class	Install
{
	public:
			Install();
			~Install();
	void	Initialize();

	void	GenerateFlist(char *directory);
	void	AddToFlist(char *);
	void	PrintFlist();
	Bool	MakeDirectories(char *);
	Bool	CopyFile(int eleval);
	int		CountSlashes(int eleval);
	int		GetPercentDone();
	char*	FindSrcDir(char * src);
	void	ChDir();											//DAW 25Apr96
	int		WriteRoots();										//DAW 16Aug96

	void	SetGenerated(Bool val);
	void	SetSrcDir(char *);
	void	SetDstDir(char *);
	void	SetSize(ULong f);
	void	ResetCopiedSize();									//DAW 22Jul96
	int		IncSize();											//DAW 12Aug96
	void	SetMessage(ULong m);								//DAW 19Aug96

	Bool	GetGenerated();
	char*	GetDstDir();
	char*	GetSrcDir();
	ULong	GetSize();
	ULong	GetNumberOfFiles();
	ULong	GetTotalFileSize();
	ULong	GetCopiedSize();
	char*	GetFname(int eleval);
	ULong	GetDFree();											//DAW 12Aug96
	char	GetSrcDisk();
	ULong	GetTotalDiskSpace();									//DAW 08Dec96
	
	void	poo();												//DAW 24Sep96
	void	Install::GenerateSizedFlist();						//DAW 25Sep96
	void	GenerateFlistNoRec(char *directory);				//DAW 25Sep96
	void	SetSpeed();

	protected:

	private:
		char	**Flist;				//array of fnames
		ULong	NumberOfFiles;			//number of fnames
		ULong	MaxNumberOfFiles;		//max number of fnames allowed bfore resizeing the array
		ULong	TotalFileSize;			//total number of bytes need for copy
		ULong	CopiedFileSize;			//how many bytes that have been copied
		ULong	TestFileSize;			//How many bytes in the speed test
		char	*SrcPath;				//src directory and path
		char	*SrcDir;				//src directory now should be .
		char	*DstDir;				//where to put it
		char	*LstDir;				//directory structure of the last copied fnmae
		char	*TmpFName;				//just tempory
		Bool	GeneratedFlist;			//is there a compleate flist generated yet
		ULong	Size;					//install size [i.e.] 0-1-2 sml,med,lrg
		ULong	ExitCond;				//Exit Condition.
		ULong	Speed;					//Speed 0=Duel 1=Quad
		ULong	MinimumFS;				//The Minimym Filesize
		ULong	ClustersRequired;		//Howman Clusters are reqired for Installed version
		clock_t	Time;					//How long to copy
};
#endif
