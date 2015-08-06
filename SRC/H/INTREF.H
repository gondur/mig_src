//------------------------------------------------------------------------------
//Filename       intref.h
//System         
//Author         Martin Alderton
//Date           Wed 10 Jan 1996
//Description    
//------------------------------------------------------------------------------
#ifndef	INTREF_Included
#define	INTREF_Included

#define	DEFAULT_INTREF 0

#include	"dosdefs.h"
//TempCode MGA 18Jan96 #include	"TEXT.G"
#include	"enumbits.m"
//TempCode MGA 18Jan96 #include 	"textref.h"

class  OFFSETCAST {


};

struct RefInputLine
{
	public:
		char type[80];
		char name[1024];
		char data[3][1024];

};

struct Constantstruc
{
  	public:
		char name[1024];
		int constant;
		char format[20];
		struct Constantstruc *link;

};
typedef struct Constantstruc *ConstantstrucPtr;

struct Addressstruc
{
  	public:
		char name[1024];
		char address[1024];
		char format1[20];
		char format2[20];
		struct Addressstruc *link;

};
typedef struct Addressstruc *AddressstrucPtr;

struct Offsetstruc
{
  	public:
		char name[1024];
		char mask_shift1[20];
		char mask_shift2[20];
		char format1[20];
		char format2[20];
		struct Offsetstruc *link;

};
typedef struct Offsetstruc *OffsetstrucPtr;

struct InputFormat
{
 	public:
		int mask;
		int shift;
		char maskword[20];
		char shiftword[20];
		char special[20];
};

struct OutputLine
{
	public:
		char code[20];
};


	RefInputLine ReadIntLine(char*,FILE * );
	void ProcessIntLine(RefInputLine);
	void ReadData(void );
	void AddToLinkedList(const Constantstruc&);
	void AddToLinkedList(const Addressstruc&);
	void AddToLinkedList(const Offsetstruc&);
	int  GetNumber(char* );
	OutputLine GetOutputFormat(char * );
	void AssignConstants(void );
	InputFormat GetInputFormat(char *);
	InputFormat TestForSpecial(InputFormat);
	void AssignAddresses(void );
	void AssignOffsets(void );

#endif
