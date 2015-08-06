//------------------------------------------------------------------------------
//Filename       getset.h
//System         
//Author         Paul.   
//Date           Mon 24 Jul 1995
//Description    
//------------------------------------------------------------------------------
#ifndef	getset_Included
#define	getset_Included

#include	"display.h"

class	GetSet:public InitDisplayDef	//defines resolution request.
{
	public:
//DeadCode JIM 12Dec95  		MODE	Mode;
//DeadCode JIM 12Dec95 		int	xres;
//DeadCode JIM 12Dec95 		int	yres;
//DeadCode JIM 12Dec95 		int	depth;

		GetSet::GetSet(void );

		void	GetSet::ReadArgs(int argc, char *argv[]);
		void	GetSet::ReadArgsInstall(int argc, char *argv[]);
//TempCode JIM 12Dec95 		MODE	GetSet::WhatMode(void );

	private:

		void	GetSet::EchoParameters();

	protected:

};


#endif
