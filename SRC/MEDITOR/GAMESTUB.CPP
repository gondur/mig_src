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

//---------------------------------------------------------------------------
#include	<stdlib.h>
//#include <vcl\vcl.h>
//---------------------------------------------------------------------------
#include	"dosdefs.h"
#include	"text.h"
#include	"myerror.h"
#include	"worldinc.h"
#include	"missman2.h"
#include	"shapes.h"
#include	"3dcode.h"
#include	"3dcom.h"
#include	"landscap.h"
#include	"lstream.h"
#include	"world.h"
#include	"bfnumber.h"
#include	"persons2.h"
#include	"aaa.h"
#include	"ai.h"
#include	"savegame.h"
#include	"winmove.h"
#include	"planetyp.h"
#include	"flymodel.h"
#include 	"mymath.h"
//#include 	"e:\CBuilder\CBuilder\INCLUDE\Math.h"
#include 	"c:\Program Files\Borland\CBuilder\INCLUDE\Math.h"
//#include 	"$(BCB)\include\Math.h"
#include 	"mytime.h"

FileNum	Persons2::FindNextBf( Persons2::BattlefieldType	& )	{} ; // undefined reference
Error	_Error ; // undefined reference
	Error::Error(){} ; // undefined reference
	Error::~Error(){} ; // undefined reference
Error	&	Error::ExitMode()	{} ; // undefined reference
Error	&	Error::Say( char	*, ... )	{} ; // undefined reference
//
//
//
RndVal	MathLib::rnd()	{return RndVal(0);} ; // undefined reference
//DPlay	_DPlay ; // undefined reference
  //	DPlay::DPlay(){} ; // undefined reference
	//DPlay::~DPlay(){} ; // undefined reference
//Bool	DPlay::Synchronise () {};								//DAW 21Aug97
//Bool	DPlay::UISendMessageToAll( char	*, long unsigned )	{} ; // undefined reference
//Bool	DPlay::UIGetMyNonSysMessage( char	*, long unsigned	& )	{} ; // undefined reference
//
//TimerCode	Timer_Code ; // undefined reference
//
shapestuff	SHAPESTUFF ; // undefined reference
	shapestuff::shapestuff(){};
	shapestuff::~shapestuff(){};
void	SendInitPacket()	{}
void	shapestuff::UnLoadRequiredShapes()	{} ; // undefined reference
MathLib	Math_Lib ; // undefined reference
struct	CDOpenFile
{int i;};
void 	fileman::setcdsavedata()	{};
void	fileman::SetupAreaFiles(FileNum*) {};
void	fileman::CloseAreaFiles() {};
void*	fileman::loadCDfile(FileNum,long,long,Bool) {};
void	fileman::pingCD()	{};
//void	fileman::CDSetup( char	* )	{} ; // undefined reference

ImageMap	Image_Map ; // undefined reference
CON	ImageMap::ImageMap() {};
CON	ImageMap::~ImageMap() {};
void	ImageMap::UnLoadImageMapPtrs()	{} ; // undefined reference
//ScreenXY	Window::conv( ScreenXY, Graphic const	* ) const	{} ; // undefined reference

WorldStuff::WorldStuff() {};
WorldStuff::~WorldStuff() {};

void	ItemBase::operator delete(void* v)
{

}

Bool	BITSET(void* v,ULong i)
{
	char* c=(char*)v;
	c+=i>>3;
	i=1<<(i&7);
	Bool rv=(*c&i)?FALSE:TRUE;
	*c|=i;
	return rv;
}

long	MULDIVSIN(long l1,long l2,long l3)
{
	__int64 v=l1;
	v*=l2;
	v/=l3;
	return(long)v;
}
ULong	SHDIVSIN(long l1,UByte l2,ULong l3)
{
	__int64 v=l1;
	v<<=l2;
	v/=l3;
	return(long)v;
}

long	MULSHSIN(long l1,long l2,UByte s)
{
	__int64 v=l1;
	v*=l2;
    v>>=s;
	return(long)v;
}


ULong   MathLib::a2iend(string& source)
{
	ULong   retval=0;
    while ((*source>='0') && (*source<='9'))
        retval=retval*10+(*(source++)&0x0f);
	return(retval);
}

ULong   MathLib::a2iend             //returns numeric value found
			(   string& source,     //input pointer is pushed forward
                ULong& lengthdec)   //remaining characters counter modified
{
	ULong   retval=0;
    while ((*source>='0') && (*source<='9'))
	{
		retval=retval*10+(*(source++)&0x0f);
		lengthdec--;
	}
	return(retval);
}
void	MathLib::Intercept( long x, long y, long z, long	&r, short	&h, short	&p )	
{
	double aa=atan2(x,z); //opposite to definition... we want clockwise from north. They do aclock from east
    h=aa*32768.0/M_PI;
    if (AbsSign(x)>AbsSign(z))
		r=x/sin(aa);
    else
    	r=z/cos(aa);
    aa=atan2(y,r);
    if (AbsSign(y)>AbsSign(r))
    	r=y/sin(aa);
    else
    	r=r/cos(aa);
    p=aa*32768.0/M_PI;        
} ; // undefined reference
void	MathLib::HighIntercept( long x, long y, long z, long	&r, short	&h, short	&p )	
{
	Intercept(x,y,z,r,h,p);
}
void	MathLib::sin_cos( ANGLES a, short	&s, short	&c )	
{
	double aa=(double)a*M_PI/32768.0;
    double ss=sin(aa);
    double cc=cos(aa);
	c=cc*32767.0;
    s=ss*32767.0;
}
void	MathLib::high_sin_cos( ANGLES a, short	&s, short	&c )
{
	double aa=(double)a*M_PI/32768.0;
    double ss=sin(aa);
    double cc=cos(aa);
	c=cc*32767.0;
    s=ss*32767.0;
}


SLong	mathlib_l_getsign(SLong v)	{if (v<0) return -1; else return 0;}
SLong	mathlib_l_applysign (SLong v,SLong s)	{if (s) return -v;else return v;}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DateFromSecs
//Author		R. Hyde 
//Date			Thu 4 Jan 1996
//
//Description	
//
//Inputs
//
//Returns
//
//------------------------------------------------------------------------------
void MathLib::DateFromSecs (SLong secs,SWord &day, SWord &month, SWord &year)
{

	SWord	daysinfullyears;
	SWord	daysinyear,leapyear;
	SWord	daysinfullmonths;

	day = (SWord)(1 + (secs / (int)SECSPERDAY));
	year = YearFromDays (day,daysinfullyears,leapyear);
	daysinyear = day - daysinfullyears;
	month =  MonthFromDays (daysinyear,daysinfullmonths,leapyear);
	day = daysinyear -  daysinfullmonths;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		YearFromDays
//Author		R. Hyde
//Date			Thu 4 Jan 1996
//
//Description
//
//Inputs
//
//Returns
//
//------------------------------------------------------------------------------
SWord MathLib::YearFromDays (SWord day, SWord &daysinfullyears, SWord &leapyear)
{
	SWord	year4,years;

	year4 = 4 * (day / (int)DAYSPER4YEAR);
	years = day % (int)DAYSPER4YEAR;
	years = years / (int)DAYSPERYEAR;

	if (years == 3)
	{
		leapyear =TRUE;
	}else
	{
		leapyear = FALSE;
	}

	daysinfullyears =  year4 *  (int)DAYSPER4YEAR / 4;
	daysinfullyears +=  (int)DAYSPERYEAR * years;

	years = years + year4;
	return (years);

}

//All dates are in seconds and are based on the xx01 year of the century
//For Flying Corps the origin is midnight on 1st Jan 1917
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MonthFromDays
//Author		R. Hyde
//Date			Thu 4 Jan 1996
//
//Description
//
//Inputs
//
//Returns
//
//------------------------------------------------------------------------------
SWord MathLib::MonthFromDays (SWord daysinyear, SWord &daysinfullmonth, SWord leapyear)
{
	SWord Days_in_Month[] =
	{
		31,28,31,30,31,30,31,31,30,31,30,31
	};

	SWord	truedays;
	SWord	i = 0;
	daysinfullmonth = 0;
	truedays = Days_in_Month[i];
	while (daysinyear >truedays)
	{
		daysinfullmonth += truedays;
		daysinyear -= truedays;
		i++;
		truedays = Days_in_Month[i];
		if ((i == 1) && leapyear == TRUE)
		{
			truedays += 1;
		}

	}
	return (i);

}
