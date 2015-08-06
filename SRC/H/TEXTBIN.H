//------------------------------------------------------------------------------
//Filename       textbin.h
//System         
//Author         Martin Alderton
//Date           Thu 7 Dec 1995
//Description    
//------------------------------------------------------------------------------
#ifndef	TEXTBIN_Included
#define	TEXTBIN_Included

#define	DEFAULT_TEXTBIN 0


#include	"dosdefs.h"
#include	"enumbits.m"
#include 	"textrefl.h"
#include 	"textref.h"

#define ARRAYSIZE 1024;
#define BIGARRAYSIZE 51200;

struct SnipLink
{
public: 
	char   	name[256];
//DeadCode MGA 21Dec95 	char	text[256];
	UByte	arguments;
	struct 	SnipLink *link;
};

typedef struct SnipLink *SnipLinkPtr;

struct ListLink
{
public:
	char   	name[256];
//DeadCode MGA 21Dec95 	char	text[256];
	struct  ListLink *link;
};

typedef struct ListLink *ListLinkPtr;

struct SeqLink
{
	public:
		char name[256];
//TempCode MGA 18Jan96 		char text[1024];
		struct SeqLink *link;
};

typedef struct SeqLink *SeqLinkPtr;

struct InputLine
{
	public:
		char type[80];
		char name[1024];
		char text[1024];
};
		

	string getcasesensitiveword(FILE * );
	void InitLinkLists(void );
  	InputLine ReadLine(char*,FILE * );
 	int  CountPerCent(char *,Bool);
	void ProcessLine(InputLine);
	void ReadData(void );
	void WriteToSnipFil(int,int);
	void WriteToListFil(int,int);
	void Assign(void );
//DeadCode MGA 22Jan96 	void Clear(void );
	void AddToLinkedList(int,const SnipLink&);
	void AddToLinkedList(int,const ListLink&);
	void AddToLinkedList(const SeqLink&);
//TempCode MGA 19Dec95 	int  SnipLinkListCount(int);
//TempCode MGA 19Dec95 	int  ListLinkListCount(int);
//TempCode MGA 20Dec95 	void HeaderWrite(void );
	char CheckSnip(SnipLinkPtr ,int );
	Bool CheckForError(string );
	int  CheckForBracketError(string, string, int );
	Bool ErrorCheck(string );
	void TestLine(int,FILE *,char*);
	void BuildBlock(void );
	void SaveBlock(int,int,TextSnipBlock *);
	void SaveBlock(int,int,TextListBlock *);
	void SaveBlock(int,TextSeqBlock *,int);
	Bool Scan(char );
	void SnipFileList(string );
	void ListFileList(string );
	void SeqFileList(string );
	void Delete(void );
 	void Main(void );
//DeadCode MGA 03Jan96  	void Main(int, char * );
	

#endif
