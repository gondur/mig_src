/*
	 MiG Alley
	 Copyright (C) 1998, 1999, 2000, 2001 Empire Interactive (Europe) Ltd,
	 677 High Road, North Finchley, London N12 0DA

	 Please see the document licence.doc for the full licence agreement

2. LICENCE
 2.1 	
 	Subject to the provisions of this Agreement we now grant to you the 
 	following rights in respect of the Source Code:
  2.1.1 
  	the non-exclusive right to Exploit  the Source Code and Executable 
  	Code on any medium; and 
  2.1.2 
  	the non-exclusive right to create and distribute Derivative Works.
 2.2 	
 	Subject to the provisions of this Agreement we now grant you the
	following rights in respect of the Object Code:
  2.2.1 
	the non-exclusive right to Exploit the Object Code on the same
	terms and conditions set out in clause 3, provided that any
	distribution is done so on the terms of this Agreement and is
	accompanied by the Source Code and Executable Code (as
	applicable).

3. GENERAL OBLIGATIONS
 3.1 
 	In consideration of the licence granted in clause 2.1 you now agree:
  3.1.1 
	that when you distribute the Source Code or Executable Code or
	any Derivative Works to Recipients you will also include the
	terms of this Agreement;
  3.1.2 
	that when you make the Source Code, Executable Code or any
	Derivative Works ("Materials") available to download, you will
	ensure that Recipients must accept the terms of this Agreement
	before being allowed to download such Materials;
  3.1.3 
	that by Exploiting the Source Code or Executable Code you may
	not impose any further restrictions on a Recipient's subsequent
	Exploitation of the Source Code or Executable Code other than
	those contained in the terms and conditions of this Agreement;
  3.1.4 
	not (and not to allow any third party) to profit or make any
	charge for the Source Code, or Executable Code, any
	Exploitation of the Source Code or Executable Code, or for any
	Derivative Works;
  3.1.5 
	not to place any restrictions on the operability of the Source 
	Code;
  3.1.6 
	to attach prominent notices to any Derivative Works stating
	that you have changed the Source Code or Executable Code and to
	include the details anddate of such change; and
  3.1.7 
  	not to Exploit the Source Code or Executable Code otherwise than
	as expressly permitted by  this Agreement.

questions about this file may be asked at http://www.simhq.com/
*/

//------------------------------------------------------------------------------
//Filename       install.cpp
//System         Instalation for flying corps
//Author         Dave Whiteside
//Date           Tue 19 Mar 1996
//Description    
//------------------------------------------------------------------------------
#include	<dos.h>
#include	<io.h>
#include	<direct.h>
#include	<stdio.h>
#include	<string.h>											//DAW 29Jul96
#include	<stdlib.h>
#include	<Signal.h>
#include	<fstream.h>

#include	"DOSDefs.H"
#include	"FileMan.h"
#include	"Main.H"
#include	"install.h"
#include	"UI.h"
#include	"miles.h"
#include	"Analogue.h"
#include	"Worldinc.h"
#include	"string.h"
#include	"mymath.h"

void	TextTest();
#define	DEST "C:\\ROWAN\\FLY"
FILE	*inb,*outb;


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Some stub routines and data records
//Author		Jim Taylor
//Date			Mon 15 Apr 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
#include	"textref.h"
#include	"imagemap.h"
#include	"viewsel.h"											//RJS 02Sep96
#include	"savegame.h"										//RJS 02Sep96

void	item::InterceptandRange(COORDS3D*)	{;}					//RJS 02Sep96
ViewPoint::ViewPoint()	{;}										//RJS 02Sep96
ViewPoint	View_Point;											//RJS 02Sep96

SaveData	Save_Data;											//RJS 02Sep96

void	TextB::LoadTextBlocks()									//JIM 15Apr96
{
}
ImageMap	Image_Map(0);
ImageMap::ImageMap(UWord)	{;}
ImageMap::~ImageMap()	{;}
ImageMapDescPtr	ImageMap::GetImageMapPtr(ImageMapNumber,Bool )	//RJS 15Dec96
{
	return(NULL);
}

WorldStuff * mobileitem::currworld=NULL;


Install::Install()
{
	MaxNumberOfFiles=100;
	NumberOfFiles=0;
	Flist = new char*[MaxNumberOfFiles];
	GeneratedFlist = FALSE;
	LstDir=NULL;
	SrcDir=NULL;
	DstDir= new char[strlen(DEST)+1];
	TmpFName=NULL;
	strcpy(DstDir,DEST);
	TotalFileSize=0;
	TestFileSize=0;
	CopiedFileSize=0;
	Size=2;
	ExitCond=1;
	Speed=0;
	Time=0;
	MinimumFS=1;
	ClustersRequired=0;
}

Install::~Install()
{
}

void	Install::Initialize()
{
//TempCode JIM 01Aug96 	fileman::quitonfailalloc=FALSE;								//ARM 27Jun96
	if (GeneratedFlist==TRUE)
	{
		for (int i=0;i<NumberOfFiles;i++)
			delete [] Flist[i];
		TotalFileSize=0;
		CopiedFileSize=0;
		NumberOfFiles=0;
		GeneratedFlist = FALSE;
		Speed=0;
		Time=0;
		ClustersRequired=0;
	}
}

void	Install::AddToFlist(char *fname)
{
	if (NumberOfFiles==MaxNumberOfFiles)
	{
		char	**Tlist;
		int		NewFcount=MaxNumberOfFiles+(MaxNumberOfFiles>>1);
		Tlist = new char*[NewFcount];
		for (int i=0;i<MaxNumberOfFiles;i++)
			Tlist[i]= Flist[i];
		delete [] Flist;
		Flist = Tlist;
		MaxNumberOfFiles=NewFcount;
	}
	Flist[NumberOfFiles]= new char[strlen(fname)+1];
	strcpy(Flist[NumberOfFiles],fname);
	NumberOfFiles++;

}

void	Install::PrintFlist()
{
	INT3();
	for (int i=0;i<NumberOfFiles;i++)
		printf("%s\n",Flist[i]);
}


void Install::GenerateFlist(char *directory)
{
	DIR		*dirp;
	struct	dirent *direntp;
	char	sourcefile[128];

	dirp = opendir(directory);
	if( dirp != NULL )
	{
	    for(;;)
		{
			direntp = readdir( dirp );
			if( direntp == NULL )
				break;
			if (direntp->d_attr & _A_SUBDIR)
			{
				if (!strcmp(direntp->d_name,".") ||
					!strcmp(direntp->d_name,"..") )
//TempCode DAW 16Aug96 					strstr(direntp->d_name,"SMACKER") )
				{
//					printf("Dont do nufin with %s\n",direntp->d_name);
				}
				else
				{
					strcpy(sourcefile,directory);
					if (strlen(sourcefile)!=3)
						strcat(sourcefile,"\\");
					strcat(sourcefile,direntp->d_name);
					GenerateFlist(sourcefile);
				}
			}
			else
			{
				strcpy(sourcefile,directory);
				if (strlen(sourcefile)!=3)
					strcat(sourcefile,"\\");
				strcat(sourcefile,direntp->d_name);
				TotalFileSize+=direntp->d_size;
				AddToFlist(sourcefile);
			}
   		}
		closedir( dirp );
	}
}

void	Install::SetGenerated(Bool val)
{
	GeneratedFlist=val;
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetFname
//Author		Dave Whiteside
//Date			Mon 8 Apr 1996
//
//Description	Return the file name of the numbered file
//
//Inputs		
//
//Returns		The Full file name with double slashes
//
//------------------------------------------------------------------------------
char*	Install::GetFname(int eleval)
{
	int	i,j=0;
	char	poo;
	if (eleval<NumberOfFiles)
	{
		TmpFName=new char[strlen(Flist[eleval])+CountSlashes(eleval)+1];
		for (i=0;i<strlen(Flist[eleval]);i++)
		{
			poo=Flist[eleval][i];
			TmpFName[j++]=poo;
			if (poo=='\\')
				TmpFName[j++]='\\';
		}
		TmpFName[j]=0x0;
	}
	return(TmpFName);
}

int	Install::CountSlashes(int eleval)
{
	int		retval=0;
	if (eleval<NumberOfFiles)
		for (int i=0;i<strlen(Flist[eleval]);i++)
			if (Flist[eleval][i]=='\\')
				retval++;
	return(retval);
}


Bool Install::MakeDirectories(char * dest)
{
	char	tmppath[100];
	char	builtpf[100];
	char	*tmppos=NULL;
	char	*tmppos1=NULL;
	int		retval=0;

	strcpy(tmppath,dest);
	if (strchr(tmppath,'\\')==strrchr(tmppath,'\\'))
		retval=mkdir(tmppath);
	else
	{
		tmppos=strchr(tmppath,'\\');
		*tmppos=0x0;
		strcpy(builtpf,tmppath);
		do
		{
			strcat(builtpf,"\\");
			tmppos++;
			tmppos1=strchr(tmppos,'\\');
			*tmppos1=0x0;
			strcat(builtpf,tmppos);
			tmppos=tmppos1;
			retval=mkdir(builtpf);
		}
		while (tmppos);
	}
	if (retval)
		return(FALSE);
	else
		return(TRUE);
}


void	Install::SetSrcDir(char *src)
{
	delete SrcDir;
	if (src[strlen(src)]=='\\')
		src[strlen(src)]=0;
	SrcDir= new char[strlen(src)+1];
	strcpy(SrcDir,src);
	SrcPath=getcwd(NULL,0);
}

char*	Install::FindSrcDir(char * src)
{
//TempCode DAW 02Oct96 	return(getcwd(src,strlen(src)));
	return("");
}

char*	Install::GetDstDir()
{
	return(DstDir);
}

char*	Install::GetSrcDir()
{
	return(SrcDir);
}

ULong	Install::GetTotalFileSize()
{
	return(TotalFileSize);
}

ULong	Install::GetTotalDiskSpace()
{
	return(ClustersRequired*MinimumFS);
}

void	Install::SetDstDir(char *src)
{
	delete DstDir;
	DstDir= new char[strlen(src)+1];
	strcpy(DstDir,src);
}

Bool	Install::GetGenerated()
{
	return(GeneratedFlist);
}

Bool Install::CopyFile(int eleval)
{
	struct	find_t fInfo;
	void	*ptr;
	FILE	*fp;
	Bool	retval=FALSE;
	char	src[128];
	char	dest[128];
	char	directory[128];
	char	*tmppos;

	if (eleval<NumberOfFiles)
	{
		retval=TRUE;
		strcpy(src,Flist[eleval]);
//TempCode DAW 03Oct96 		tmppos=strrchr(src,'\\');				//pure file name
//TempCode DAW 03Oct96 		*tmppos=0x0;

		if (LstDir==NULL)
		{
			MakeDirectories(DstDir);
			LstDir = new char[strlen(DstDir)+1];
			strcpy(LstDir,DstDir);
		}

		strcpy(dest,DstDir);
		strcat(dest,"\\");
//TempCode DAW 03Oct96 		strcpy(dest,DstDir);
//TempCode DAW 03Oct96 		tmppos=Flist[eleval]+strlen(SrcDir)+1;	//the common file name and directory
//TempCode DAW 03Oct96 		strcat(dest,"\\");
//TempCode DAW 03Oct96 		strcat(dest,tmppos);
//TempCode DAW 03Oct96 		tmppos=strrchr(dest,'\\');
//TempCode DAW 03Oct96 		*tmppos=0x0;

		strcpy(directory,DstDir);
		strcat(directory,"\\");
		strcat(directory,src);
		tmppos=strrchr(directory,'\\');
		*tmppos=0x0;

		if (stricmp(LstDir,directory)!=0)
		{
			delete LstDir;
			LstDir = new char[strlen(directory)+1];
			strcpy(LstDir,directory);
			MakeDirectories(directory);
		}

		strcat(dest,src);
//TempCode DAW 03Oct96 		tmppos=strrchr(Flist[eleval],'\\');
//TempCode DAW 03Oct96 		strcat(dest,tmppos);
//TempCode DAW 03Oct96 		strcpy(src,Flist[eleval]);

		if (retval==TRUE)					//OK making directories
		{
			if (!_dos_findfirst (src, _A_ARCH|_A_NORMAL|_A_RDONLY, &fInfo))
			{
				clock_t start,end;
				ptr = new char[fInfo.size];
				if (ptr)
				{
					fp=fopen(src,"rb");
					if (fp)
					{
						start=clock();
						fread(ptr,fInfo.size,1,fp);
						if (fInfo.size>200000)
						{
							Time+=clock()-start;
							TestFileSize+=fInfo.size;
						}
						fclose(fp);
						fp=fopen(dest,"wb");
						if (fp)
						{
							fwrite(ptr,fInfo.size,1,fp);
							fclose(fp);
						}
						else
						{
							retval=FALSE;
						}
					}
					else
					{
						retval=FALSE;
					}
					delete ptr;
				}
				else
				{		//Unfortunatly there is not enough memory to load the file
						//in in one go, so clever shit is required.
					FILE	*op;
					unsigned int memfree=fInfo.size;
					unsigned int fcount=fInfo.size;
					while (!ptr)
					{
						memfree-=(memfree/10);		//10% smaller
						ptr=new char[memfree];		//exits when it can new something
					}
					fp=fopen(src,"rb");
					op=fopen(dest,"wb");
					if (fp && op)
					{
						while (fcount)
						{
							if (fcount>memfree)
							{
								start=clock();
								fread(ptr,memfree,1,fp);
								if (fInfo.size>200000)
								{
									Time+=clock()-start;
									TestFileSize+=memfree;
								}
								fwrite(ptr,memfree,1,op);
								fcount-=memfree;
							}
							else
							{
								fread(ptr,fcount,1,fp);
								fwrite(ptr,fcount,1,op);
								fcount=0;
							}
						}
						fclose(fp);
						fclose(op);
					}
					else
					{
						retval=FALSE;
					}
					delete ptr;
				}
				CopiedFileSize+=fInfo.size;
			}
			else
			{
				retval=FALSE;
			}
		}
	}
	return(retval);
}

ULong	Install::GetNumberOfFiles()
{
	return(NumberOfFiles);
}

int	Install::GetPercentDone()
{
	int	bolox;
	bolox=	MULDIVUNS(CopiedFileSize,100,TotalFileSize);
	return(bolox);
}

ULong	Install::GetCopiedSize()
{
	return(CopiedFileSize);
}

ULong	Install::GetDFree()
{
	struct	diskfree_t	disk_data;
	_dos_getdiskfree((DstDir[0]-'@'),&disk_data);
	MinimumFS = disk_data.sectors_per_cluster*disk_data.bytes_per_sector;
	return(disk_data.avail_clusters*disk_data.sectors_per_cluster*disk_data.bytes_per_sector);
}

void	Install::ResetCopiedSize()
{
	CopiedFileSize=0;
}

void	Install::SetSize(ULong f)
{
	Size=f;
}

int	Install::IncSize()
{
	if (Size>=3)
		Size=1;
	else
		Size++;
	return(Size);
}

ULong Install::GetSize()
{
	return(Size);
}

void	Install::ChDir()
{
	unsigned	ignore;
	_dos_setdrive(*DstDir-'@',&ignore);
	chdir(DstDir+2);
	fileblocklink::deletelink(-1);
	FILEMAN.makerootdirlist();
	_Main.InitFileSystem(_Main);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Install::WriteRoots
//Author		Dave Whiteside
//Date			Fri 16 Aug 1996
//
//Description	Write out the Roots.dir file
//
//Inputs		Nothing
//
//Returns		0 if OK and some form of int if it failed
//
//------------------------------------------------------------------------------
int	Install::WriteRoots()
{
	char		srcdrv[128];
	char		*cwd;
	FILE		*fp;
	int			dir,org;

	ifstream	in("roots.dir");

	cwd=getcwd(NULL,0);
	fp=fopen("poo.dir","wt");
	if (fp)
	{
		for (dir=0;dir<Size;dir++)
			fprintf(fp,"%i\t\t.\\.\n",dir);
		for (;dir<4;dir++)
			fprintf(fp,"%i\t\t%s\\.\n",dir,SrcPath);
		do
			in >> srcdrv;
		while (srcdrv[0] !='4' );
		dir=atoi(srcdrv);
		do
		{
			in >> org;
			in >> srcdrv;
			if (dir==13)
			{
//TempCode DAW 14Nov96 				if (Speed<5)
//TempCode DAW 14Nov96 					fprintf(fp,"%i\t%i\tDUAL\\.\n",dir,org);
//TempCode DAW 14Nov96 				else
					fprintf(fp,"%i\t%i\tQUAD\\.\n",dir,org);
			}
			else
			{
				fprintf(fp,"%i\t%i\t%s\n",dir,org,srcdrv);
			}
			in >> dir;
		}
		while (dir != 15);
		in >> org;
		in >> srcdrv;
		fprintf(fp,"%i\t%i\t%s\n",dir,org,srcdrv);
	}
	free(cwd);
	fclose(fp);
	in.close();													//DAW 10Dec96
	unlink("ROOTS.DIR");
	rename("POO.DIR","ROOTS.DIR");
	fileblocklink::deletelink(-1);
	FILEMAN.makerootdirlist();
	_Main.InitFileSystem(_Main);

	return(0);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetMessage
//Author		Dave Whiteside
//Date			Mon 19 Aug 1996
//
//Description	Set The message for the exit screen
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Install::SetMessage(ULong m)
{
	ExitCond=m;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetSrcDisk
//Author		Dave Whiteside
//Date			Mon 19 Aug 1996
//
//Description	return the drive letter of the src disk
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
char	Install::GetSrcDisk()
{
	char	src[128];
	return(getcwd(src,strlen(src))[0]);
}

void	Install::poo()
{
	dirindex	test=0;
	for (dirindex i=16;i;i++)
	{
		test=FILEMAN.getbasedir(i);
	}
}


void	Install::GenerateSizedFlist()
{
	dirindex	current=0;
	char*		dirname;
	char*		tmp;

	for (dirindex i=15;i;i++)
	{
		current=FILEMAN.getbasedir(i);
		if (current != RAMCACHEHANDLEDIR)
			if (current < Size)
			{
				dirname=FILEMAN.namenumberedfile(dirnum(i));
				tmp=strstr(dirname,"dir.dir");
				*tmp=0;
//TempCode DAW 03Oct96 				printf("Add Directory %s\n",dirname);
				GenerateFlistNoRec(dirname);
			}
	}
}

void Install::GenerateFlistNoRec(char *directory)
{
	DIR		*dirp;
	struct	dirent *direntp;
	char	sourcefile[128];

	if (strlen(directory)==0)
		directory=".\\";											//DAW 03Oct96
	dirp = opendir(directory);
	if( dirp != NULL )
	{
	    for(;;)
		{
			direntp = readdir( dirp );
			if( direntp == NULL )
				break;
			if (!(direntp->d_attr & _A_SUBDIR))
			{
				strcpy(sourcefile,directory);
//TempCode DAW 03Oct96 				if (strlen(sourcefile)!=3)
//TempCode DAW 03Oct96 					strcat(sourcefile,"\\");
				strcat(sourcefile,direntp->d_name);
				TotalFileSize+=direntp->d_size;
				ClustersRequired+=(direntp->d_size/MinimumFS)+1;
				AddToFlist(sourcefile);
//TempCode DAW 03Oct96 				printf("Add file %s %s \n",directory, sourcefile);
			}
   		}
		closedir(dirp);
	}
}

void	Install::SetSpeed()
{
	Speed=TestFileSize/1780/Time; 				// 150k/sec
//DeadCode DAW 05Dec96 	INT3();
}
