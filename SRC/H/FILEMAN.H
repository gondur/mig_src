//------------------------------------------------------------------------------
//Filename       fileman.h
//System         
//Author         Jim Taylor
//Date           Thu 21 Sep 1995
//Description    
//------------------------------------------------------------------------------
#ifndef	FILEMAN_Included
#define	FILEMAN_Included


#include	"myError.h"
#include	"files.g"											//JIM 07Nov95
//DeadCode PD 29Oct96 #include	"mscdex.h"

struct RequestHeader; struct CDComm; struct dir_entry;

#define	DEFAULT_FILEMAN 0
//v1: (Being implemented)
//File number translation:
// to pathname (low level)					fileman
// to open handle for read or for write		fileman
// to allocated data block					fileblock	-new constructor
// Auto-loading of translation data			fileman
// Allocation of variable sized filebuffer		fileblock
// Freeing of variable sized filebuffer		fileblock	-destructor
// External translation of data support		fileblock
// ET support for own memory allocation		fileblock
//Raw file processing:
// Seek file position						fileman
// Read data from handle to memory area		fileman
// Close handle							fileman
// Get file size							fileman
//Resolution switching support				fileman
//
//
//v2: (To follow)
//Concatenation of directory data				fileman
//Cacheing								fileman
//Write data from memory area to handle		fileman
//Resolution switching support & cacheing		fileman
//
//
//
extern class	FileMan File_Man;
#define FILEMAN	File_Man
typedef class	fileblock *fileblockptr;

typedef	char	voidbigblock;

//DeadCode JIM 29Jul96 typedef void	proc;
//Old_Code PD 13Oct95 #ifndef	_STDIO_H_INCLUDED
//Old_Code PD 13Oct95 struct	FILE;
//Old_Code PD 13Oct95 #endif
//typedef 	FILE	*file;

typedef  void	filetrans
					(void* &dataarea,ULong& datasize);

class	fileblocklink;

struct	bilist
{
	fileblocklink
			*next,
			**back;
	void insert(fileblocklink *me,fileblocklink *&to);
	void remove(fileblocklink *me);
};


class	fileblocklink
{
	friend	struct	bilist;
	friend	class	fileman;

	FileNum	filenum;
	ULong	fileoffset;
	bilist	dir,heap;
public:
	ULong	datasize;
	void	*fileblockdata;
	int		filehandle;
	static	void*	makelink(FileNum,ULong fileoffset,ULong datasize,fileblocklink*&link);
			//returns data area if already known
	Bool	breaklink();
	static Bool	deletelink(ULong size);
	static Bool	purgelink(FileNum);
	static void	deletedirchain(FileNum fnum);

};

inline	void bilist::insert(fileblocklink *me,fileblocklink *&to)
	{
		next=to;
		back=&to;
		to=me;
		if (next)
			(&next->dir)[this-&me->dir].back=&next;
	}
inline	void bilist::remove(fileblocklink *me)
	{
		*back=next;
		if (next)
			(&next->dir)[this-&me->dir].back=back;
	}

class	fileblock
{
private:
	fileblocklink	*link;
	void	*fileblockdata;
//there will be extra pointers to help manage the free heap itself probably!
public:
//constructors:
//Wow! Down to 1 constructor with a god-awful syntax!
//Legal parameter usages:
//
//A: MyFile is a real file number to be loaded
//
//1) MyFile only parameter
//		Completely loads that FILE*. Applies no pre-processing
//
//2) MyFile + MyTrans - pre-processing function
//		Completely loads file. Pre-processor called if reloaded really.
//
//3) MyFile + MyTrans + BlockSize - maximum ammount to load
//		Loads that much file from start. Pre-processor called if reloaded really.
//
//4) MyFile + MyTrans + BlocksSize + Offset - index in file to start loading at
//		Seeks to offset, loads fixed ammount, preprocesses unless cached already.
//
//B: MyFile is an assigned dummy memory handle - recognised by DIR being invalid
//
//	 In principal this is useful for holding on to a datastructure that can be
//	 rebuilt, but where it is more convenient to keep it if memory is not short.
//	 MyTrans would rebuild the structure, and therefore is not optional.
//   Blocksize defines the size of the area, and therefore is not optional.
//
//3) MyFile + MyTrans + BlockSize
//		Allows preformatted memory to be offered for cacheing and recovered
//
//4) MyFile + MyTrans + BlockSize + offset
//		Allows 1 dummy handle to manage a number of similar data areas
//

public:
	CON	fileblock(	FileNum MyFile,
				filetrans* MyTrans=NULL,
				ULong blocksize=0x7fffffffL,
				ULong offset=0L
				)
 {	assert(MyFile);makefileblock(MyFile,MyTrans,blocksize,offset,true);	}


private:
	CON	fileblock(	FileNum MyFile,
				filetrans* MyTrans,
				ULong blocksize,
				ULong offset,
				bool	processlock
			)
 {	makefileblock(MyFile,MyTrans,blocksize,offset,processlock);	}

	void makefileblock(	FileNum MyFile,
				filetrans* MyTrans,
				ULong blocksize,
				ULong offset,
				bool	processlock
			);

protected:

	friend	class	fileman;
//The following constructor is intended for use only when
//A fileblockptr is created by a call to the file man system, and that
//fileblock is then to be considered temporary scope.
//The original object is copied and deleted. The pointer is invalid.
 fileblock( const	fileblockptr srcblockptr);

//The following constructor is for use inside the file man system.
//It allows the input file to be 'faked' temporarily.
 fileblock(	void*	MyData);



public:
//destructor
 ~fileblock();

//access routine
 ULong	getsize() {if (link==0) return (0); else return (link->datasize);}
 void*	getdata() {return fileblockdata;}
//friend	ULong	getsize(fileblock	fb);
//friend	void*	getdata(fileblock	fb);
//friend	ULong	getsize(fileblockptr	fb);
//friend	void*	getdata(fileblockptr	fb);

};

inline	ULong	getsize(fileblock&		fb)	{return(fb.getsize());};
inline  void*	getdata(fileblock&		fb)	{return(fb.getdata());};
inline	ULong	getsize(fileblockptr	fb)	{return(fb->getsize());};
inline  void*	getdata(fileblockptr	fb)	{return(fb->getdata());};


//typedef	uword	dirindex;
const	MAXDIRENTRIES		=	256;
const	MAXCDFILEENTRIES 	=	2;  							//PD 18Nov96


/////////////////////////////////////////////////////////

struct CDOpenFile;
struct CDCurrOpenFile;

/////////////////////////////////////////////////////////
class	fileman
{
	friend class FileMan;
	friend class fileman;
	friend	class	fileblock;
	friend  class	fileblocklink;

	fileblocklink	*allfreedfiles,
					*allactivefiles;
	enum	DirNameInd	{FIRSTdirnameind=0,MAXDIRIND=254,ALIASDIRIND=255};

	#ifdef	_WINBASE_
void	fileman::CDseekreadfilepos(HANDLE winhandle,int index,void* buffer,int sizecopy);
	#endif

private:
//Status info
dirindex	currdirnum;
FileNum		currfilenum;
fileblockptr
			currfileblock;		//Future optimisation: keep hold of last file
fileblock*	filrootblock;
void		*dirfakeblock,		//Temporary:	Fake cacheing of  defaults 
			*dirrootblock;		//Temporary:	Fake cacheing of ROOTS.DIR
ULong		currfilesize;
FILE*		currfilehandle;
int			nestcount;
//workspace
char		pathname[86];
enum		{filenameindex=70};
int			pathnameindex;
string		pathnameptr;

	struct	OpenFileBase										//PD 18Nov96
	{
		FileNum	number;
		SWord	dummy;
		FILE*	handle;
		int		maxfilesize;
	};

	struct	OpenFile : public OpenFileBase						//PD 18Nov96
	{
		int		currfileindex;
		int		actualfileindex;
		CON	OpenFile()	{number=INVALIDFILENUM;}
	};

#ifdef _WINBASE_
	struct CDOpenFile : public OpenFileBase						//PD 18Nov96
	{
		CDOpenFile() {number=INVALIDFILENUM;handle=NULL;maxfilesize=0;winhandle=INVALID_HANDLE_VALUE;}
		int	filebase;											//PD 30Nov96
		HANDLE winhandle;
	};

	struct CDCurrOpenFile : public CDOpenFile					//PD 18Nov96
	{
		int	currindex,
			actualindex,
			seekingtoposition;
		CDCurrOpenFile() {currindex=0;actualindex=-1;}
	};
#endif

	struct	dirfileentry
	{
//DeadCode RDH 30Sep96 	public:
	FileNum			driverfile;
	DirNameInd		dirnameind;
	dirindex		parentdir;
	fileblocklink	*freedfiles,
					*openfiles;
	
	OpenFile		openfile;
	dirfileentry();
	};

	dirfileentry	direntries[MAXDIRENTRIES];					//PD 18Nov96
	CDOpenFile* 	cdfiles;	//[MAXCDFILEENTRIES];									//PD 18Nov96
	CDCurrOpenFile*	cdfile;										//PD 18Nov96

//memory management - stage B

//CD-ROM bits
		UWord	driveletter;									//PD 30Oct96
		UWord	noofdrives;										//PD 30Oct96
		UWord	sectorsize;										//PD 30Oct96
		UWord	real_mode_seg;									//PD 30Oct96
		UWord	old_int18h_seg;									//PD 04Nov96
		UWord	old_int18h_off;									//PD 04Nov96
		UWord	CDGetDirectoryEntry(struct dir_entry*,string);	//PD 30Oct96
		UWord	CDSeek(ULong);									//PD 30Oct96
		UWord	CDReadFileBlock(ULong,void*,ULong);				//PD 30Oct96
//DeadCode PD 25Sep98 		void	SendCDCommand(UByteP);							//PD 16Dec96
//Old_Code PD 18Nov96 		void	CDReSeek();										//PD 04Nov96
//Old_Code PD 18Nov96 		void	CDMakeFileBlock(fileblock*,
//Old_Code PD 18Nov96 								fileblocklink*,
//Old_Code PD 18Nov96 								FileNum,
//Old_Code PD 18Nov96 								ULong,
//Old_Code PD 18Nov96 								ULong);							//PD 04Nov96
//Old_Code PD 18Nov96 		Bool	CDgetthedata;									//PD 04Nov96

public:															//JIM 10May96
void		InitFileSystem();
void		makerootdirlist();									//JIM 10May96
//void		CDSetup(string);									//PD 30Oct96
void		CDCloseDown();										//PD 29Oct96
//DeadCode PD 24Sep98 void		SetupAreaFiles(FileNum*);							//PD 18Nov96
//DeadCode PD 24Sep98 void		CloseAreaFiles();									//PD 18Nov96
//DeadCode PD 24Sep98 void		resetCDfile(FileNum);								//PD 18Nov96
//DeadCode PD 24Sep98 void*		loadCDfile(FileNum,SLong,SLong,Bool skipread=TRUE);	//PD 18Nov96
//DeadCode PD 24Sep98 void		pingCD();											//PD 17Dec96
private:														//JIM 10May96
//Don't tell anyone about these functions... they are a secret!	//JIM 10May96
fileblockptr
			readfilelist(dirindex);
FILE*		easyopennumberedfile(FileNum filenum);	//builds pathname and opens file
void		Getexedirectory(string	exedir);
void		GetCDdirectory (string	cddir);
void		GetParamDir(string		paramdir);
void		discarddirlist(FileNum	filenum)	{fileblocklink::deletedirchain(filenum);}
void		makedirectoryname(dirindex	reqdir,int	pathend=filenameindex);
friend void	translatedirlist(void*	&dataarea,ULong&	datalength);
friend void	retranslatedirlist(void*	&dataarea,ULong&	datalength);

static  int		(*MemFailPFU) (unsigned);								//JIM 28Mar96

public:
static	int	MyMemFailPFU(unsigned);						//JIM 28Mar96
	int	totalmem;
	int	totalfilesysmem;
	int	totalmemused;
	int	totalfilesysmemused;
void	MakeRoomFor(int delta);

//constructor - one-off
CON	fileman();

//destructor - possible for memory manager
DES	~fileman();

//low level routines

//You must delete the returned fileblock or that entry remains in memory.
fileblockptr	loaddirlist(FileNum filenum);		//defines link between res and directory names

string	namenumberedfile(FileNum);		//fills in pathname buffer & returns ptr to start
string	namenumberedfilelessfail(FileNum);		//fills in pathname buffer & returns ptr to start
int		filesindir(FileNum dirnum);		//Returns number of files in dir
void	flushcachedfiles();

FILE*	opennamedfile();				//opens the file named in the pathname buffer
FILE*	opennumberedfile(FileNum filenum);	//builds pathname and opens file

void	setcdsavedata();

void		SetupAreaFiles(FileNum*);							//PD 18Nov96
void		CloseAreaFiles();									//PD 18Nov96
void		resetCDfile(FileNum);								//PD 18Nov96
void*		loadCDfile(FileNum,SLong,SLong,Bool skipread=TRUE);	//PD 18Nov96
void		pingCD();											//PD 17Dec96

Bool	existnumberedfile(FileNum filenum);	//builds pathname and opens file
Bool	loadednumberedfile(FileNum filenum,int offset=0);	//builds pathname and opens file
Bool	IsConcatinatedFile(FileNum filenum);	//Is dir.dir a concatinated file//DAW 25Feb97

ULong	getfilesize(FILE* openhandle);		//gets size of file
ULong	readfileblock(FILE* openhandle,void* dataarea,ULong areasize);
									//read block of data from file
ULong	writefileblock(FILE* openhandle,void* dataarea,ULong areasize);
									//write block of data into file
ULong	seekfilepos(FILE* openhandle,ULong offset);
									//index to location in file
void	closefile(FILE* openhandle);		//close that file!
dirindex	getbasedir(dirindex	d);								//DAW 24Sep96
void	preload();
FILE*	errhandle;
static	Bool	quitonfailalloc;
		Bool	fileloadedthisframe;
void	fakedir(FileNum thisdir,char* dirname);
FileNum	fakefile(FileNum thisdir,const char* filename);
int	assumefakedir;
	static	void	translatedirlist(void*	&dataarea,ULong&	datalengthin);
};

class	FileMan:protected fileman	
{
	friend	class	dirlist;
public:
int		filesindir(FileNum dirnum);		//Returns number of files in dir
Bool	existnumberedfile(FileNum filenum);	//builds pathname and opens file
ULong	readfileblock(FILE* openhandle,void* dataarea,ULong areasize);
ULong	seekfilepos(FILE* openhandle,ULong offset);
FILE*	opennumberedfile(FileNum filenum);	//builds pathname and opens file
void	setcdsavedata();
void	closefile(FILE* openhandle);		//close that file!
char*	makedirectoryname(dirindex	reqdir);
string	namenumberedfile(FileNum);		//fills in pathname buffer & returns ptr to start
string	namenumberedfilelessfail(FileNum);		//fills in pathname buffer & returns ptr to start
string	namenumberedfile(FileNum, string s);	//fills in pathname buffer & returns ptr to start and is thread safe
void		InitFileSystem();
void	flushcachedfiles();
void		DiscardDirList(FileNum	filenum)	{discarddirlist(filenum);}


void		SetupAreaFiles(FileNum*);							//PD 18Nov96
void		CloseAreaFiles(); 									//PD 18Nov96
void		resetCDfile(FileNum);								//PD 18Nov96
void*		loadCDfile(FileNum,SLong,SLong,Bool skipread=TRUE);	//PD 18Nov96
void		pingCD();											//PD 17Dec96


//aliasses with capitalisation:
int		FilesInDir(FileNum dirnum)			{return	filesindir(dirnum);}
Bool	ExistNumberedFile(FileNum filenum)	{return existnumberedfile(filenum);}
ULong	ReadBlock(FILE* openhandle,void* dataarea,ULong areasize)
											{return readfileblock(openhandle,dataarea,areasize);}
ULong	SeekPos(FILE* openhandle,ULong offset)
											{return	seekfilepos(openhandle,offset);}
FILE*	OpenNumberedFile(FileNum filenum)	{return opennumberedfile(filenum);}
void	SetCDSaveData()						{setcdsavedata();}
void	CloseFile(FILE* openhandle)			{		closefile(openhandle);}
char*	MakeDirectoryName(dirindex	reqdir)	{return makedirectoryname(reqdir);}
string	NameNumberedFile(FileNum f)			{return namenumberedfile(f);}
string	NameNumberedFile(FileNum f,char* b)			{return namenumberedfile(f,b);}
string	NameNumberedFileLessFail(FileNum f)	{return namenumberedfilelessfail(f);}
void	FlushCachedFiles()					{flushcachedfiles();}

void	fakedir(FileNum thisdir,char* dirname)		{		fileman::fakedir(thisdir,dirname);}
FileNum	fakefile(FileNum thisdir,const char* filename)	{return	fileman::fakefile(thisdir,filename);}

SLong	getTotalMem();												//RJS 01Apr99
SLong	getTotalFileMemUsed();										//RJS 08Jun99


};



class	dirlist
{
public:
	enum	{FNAMESIZE = 16,MAXFLIST=100};
private:
	void	makedirlist(char* path,char* wild);
	FileNum		dirnum;
	char*		pathname;
	int			pathlen;
	char*		wildname;
	Bool		ownfilelist;
	char*		filelist;
	SLong		numfiles;
public:
	~dirlist();
	
	dirlist(FileNum d);
	dirlist(FileNum d,char* wild);
	dirlist(char* path,char* wild);
	operator	int		()		{return (int)numfiles;}
	char* operator	[](int i)
		{
		#ifdef	assert
			assert(i<=numfiles&&"wild enum too high");
		#endif
			return &filelist[i*(int)FNAMESIZE];
		}
	char*	operator+(char *);
	void operator	-=(int i);
	void operator	-=(char *);
};


#endif

