//------------------------------------------------------------------------------
//Filename       vertex.h
//System         
//Author         Paul.   
//Date           Fri 22 Sep 1995
//Description    
//------------------------------------------------------------------------------
#ifndef	VERTEX_Included
#define	VERTEX_Included

#define	DEFAULT_VERTEX 0

//typedef	signed	char	SByte,*SByteP;
//typedef	unsigned char	UByte,*UByteP;

//typedef	signed	short	SWord,*SWordP;
//typedef	unsigned short	UWord,*UWordP;

//typedef	signed	long	SLong,*SLongP;
//typedef	unsigned long	ULong,*ULongP;

//typedef long double 	Float,*FloatP;							//PD 06Jan97

//TempCode PD 06Jan97 struct	vertex													//PD 30Oct95
//TempCode PD 06Jan97 		{														//PD 30Oct95
//TempCode PD 06Jan97 			SLong	bx,by,bz;	//Body coordinates				//PD 30Oct95
//TempCode PD 06Jan97 			SLong	sx,sy;		//Screen coordinates			//PD 30Oct95
//TempCode PD 06Jan97 			SLong	ix,iy;		//Image coordinates				//PD 30Oct95
//TempCode PD 06Jan97 			SLong	intensity;		//Colour / intensity			//PD 30Oct95
//TempCode PD 06Jan97 			SWord	scalefactor;								//PD 12Dec95
//TempCode PD 06Jan97 		};														//PD 30Oct95

//DeadCode PD 07Jan97 typedef union	ifshare
//DeadCode PD 07Jan97 {
//DeadCode PD 07Jan97 	SLong	i;
//DeadCode PD 07Jan97 	Float	f;
//DeadCode PD 07Jan97 }
//DeadCode PD 07Jan97 IFShare,*IFShareP;

struct	vertex
{
	struct colour
	{
		UByte r,g,b,a;
	};
	IFShare	bx,by,bz;
	IFShare	sx,sy;
	IFShare	ix,iy;
	SLong	intensity;
	IFShare	bigsx;
	UWord	clipFlags;
//	UByte	r,g,b,a;
	union
	{
		SLong	specular;
		colour col;
	};
	UByte	mist;
	UByte	snow;
//DEAD	float fsy;
};

#endif
