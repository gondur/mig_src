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

Bool abortNow;

#ifndef IN_MIGLAND_CPP

struct PntDef{
	UWord x,z;
	UWord alt;
	UByte used;
	UByte shadeVal;
};

#else

#define PntDef PointDef

static SLong globalTriCount;

//-----------------------------------------------------------------------------
// Procedure    minMax
// Author       Paul
// Date         16/12/97
//-----------------------------------------------------------------------------
inline void minMax(SLong in1,SLong in2,SLong& minVal,SLong& maxVal)
{
	if (in1>in2) 	minVal=in2, maxVal=in1;
	else			minVal=in1, maxVal=in2;
}

//-----------------------------------------------------------------------------
// Procedure    minMax
// Author       Paul
// Date         16/12/97
//-----------------------------------------------------------------------------
inline void minMax(UWord in1,UWord in2,UWord in3,ULong& minVal,ULong& maxVal)
{
	if (in1>in2){
		if (in1>in3){
			maxVal=in1;
			if (in2<in3)	minVal=in2;
			else			minVal=in3;
		}else{
			maxVal=in3;
			if (in2<in1)	minVal=in2;
			else			minVal=in1;
		}
	}else{
		if (in2>in3){
			maxVal=in2;
			if (in1<in3)	minVal=in1;
			else			minVal=in3;
		}else{
			maxVal=in3;
			if (in1<in2)	minVal=in1;
			else			minVal=in2;
		}
	}
}

#endif

#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoLinesIntersect
//Author		Dallas  
//Date			Thu 23 Jul 1998
//
//Description	Checks if 2 lines intersect
//
//Inputs	 	start and end coords of the 2 lines 
//				(line1 = coords 1 and 3, line2=coords 2 and 4)
//
//Returns		true or false
//
//------------------------------------------------------------------------------
Bool DoLinesIntersect(int x1,int y1,int x3,int y3,int x2,int y2,int x4,int y4)
{
	int dx1=x3-x1;
	int dx2=x4-x2;
	int dy1=y3-y1;
	int dy2=y4-y2;
	if (!dx1 || !dx2)
		if (dy1 && dy2)
			return DoLinesIntersect(y1,x1,y3,x3,y2,x2,y4,x4);

	// first the throwouts...
	// if outline boxes dont intersect then lines don't intersect
	// left edge box 1 > right edge box 2

	//If you have a fast way to do min() and max() then these tests can be reduced!
	int l,r;
	int L,R;
	if ((l=min(x1,x3))>(R=max(x2,x4))) return FALSE;
	// left edge box 2 > right edge box 1
	if ((L=min(x2,x4))>(r=max(x1,x3))) return FALSE;
	// top edge box 1 > bottom edge box 2
	if (min(y1,y3)>max(y2,y4)) return FALSE;
	// top edge box 2 > bottom edge box 1
	if (min(y2,y4)>max(y1,y3)) return FALSE;
	// if one line is vertical and the other horizontal they must intersect
	if ((dx2==0 && dy1==0) || (dx1==0 && dy2==0)) return TRUE;
	int divisor=(dx2*dy1 - dy2*dx1);
	// if parralel then no intersect
	if (!divisor) return FALSE;
	int x=((dx1*dx2)*(y2-y1) + x1*dy1*dx2 - x2*dy2*dx1)/divisor;
	L=max(l,L);
	R=min(r,R);
	if (x>=L && x<=R)
		return TRUE;
	return FALSE;
}


//During the landscape optimisation I can afford to cache cross product and dot product results!
//But not during the 3d as up to 16mb may be required!
//In the 3d I can cach the deltas calculated so far easily
//
//struct PntDef{
//	UWord x,z;
//	UWord alt;
//	UByte used;
//	UByte shadeVal;
//};

inline Bool	DotFront(int dx0,int dy0,int dx2,int dy2)
{
// Imagine rotating x2 through 90 degrees. 
// Then the cross product test becomes:
//
	return (Bool)(dx0*dx2>-dy2*dy0);



}
inline Bool	CrossClock(int dx0,int dy0,int dx2,int dy2)
{
	return (Bool)(dx0*dy2<dx2*dy0);
}


inline Bool	DotFront(PntDef* pntArray,int p0,int p1,int p2)
{
	return DotFront(pntArray[p0].x-pntArray[p1].x,
					pntArray[p0].z-pntArray[p1].z,
					pntArray[p2].x-pntArray[p1].x,
					pntArray[p2].z-pntArray[p1].z);
}

inline Bool	CrossClock(PntDef* pntArray,int p0,int p1,int p2)
{
	return CrossClock(	pntArray[p0].x-pntArray[p1].x,
						pntArray[p0].z-pntArray[p1].z,
						pntArray[p2].x-pntArray[p1].x,
						pntArray[p2].z-pntArray[p1].z);
}

inline Bool	DotFront(int p0x,int p0y,int p1x,int p1y,int p2x,int p2y)
{
	return DotFront(p0x-p1x,
					p0y-p1y,
					p2x-p1x,
					p2y-p1y);
}

inline Bool	CrossClock(int p0x,int p0y,int p1x,int p1y,int p2x,int p2y)
{
	return CrossClock(p0x-p1x,
					p0y-p1y,
					p2x-p1x,
					p2y-p1y);
}

enum	Checks {CROSSCLOCK=0x03,DOTFRONT=0x0c,INTERSECT=0x30,THINPOLY=0xc0,
				CHECK_WASSET=0x55,CHECK_WASCLEAR=0xaa				};

//BASIC OPERATION DOESN'T CACHE RESULT
#ifdef IN_MIGLAND_CPP
#define CHECK(flag,p0,p1,p2,boolroutine)		boolroutine
#else
char**	check3d[256]={NULL};
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClearChecks
//Author		Jim Taylor
//Date			Tue 6 Oct 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ClearChecks()
{
	for (int i=0;i<256;i++)
		if (check3d[i])
		{
			for (int j=0;j<256;j++)
				delete [](check3d[i][j]);
			delete [] check3d[i];
			check3d[i]=NULL;
		}
}

char*	getbyteloc(int x,int y,int z)
{
	if (!check3d[x])
	{
		check3d[x]=new char* [256];
		for (int y=0;y<256;y++)
			check3d[x][y]=NULL;
	}
	if (!check3d[x][y])
	{
		check3d[x][y]=new char [256];
		for (int z=0;z<256;z++)
			check3d[x][y][z]=NULL;
	}
	return &check3d[x][y][z];
}

//OPTIMISED OPERATION CACHES RESULT
#define CHECK(flag,p0,p1,p2,boolroutine)												\	
				(	(tmpindex=getbyteloc(p0,p1,p2)),										 \
					((*tmpindex&flag)													  \
					?	Bool(*tmpindex&flag&CHECK_WASSET)								   \
					:	boolroutine														\
						?	(*tmpindex|=(flag&CHECK_WASSET),TRUE)							 \
						:	(*tmpindex|=(flag&CHECK_WASCLEAR),FALSE)						  \
					)																	   	   \
				)
#endif


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TriSeq
//Author		Jim Taylor
//Date			Sun 4 Oct 1998
//
//Description	Generate a non-occluding triangle sequence
//				from a non-intersecting polygon
//				I am relying on the non-intersection to allow the 
//				triangling to be done efficiently
//
//
//
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
int TriSeq(PntDef* pntArray,UByte* startpoint,int pntCnt)
{
	char* tmpindex;
 	int tricount=1;

	//first keep adding triangles until we go anticlockwise
	int	p0=startpoint[0];
	int	p1=startpoint[1];
	int	p2=p1;;
	int s0x=pntArray[p0].x;
	int s0y=pntArray[p0].z;
	int s2x=pntArray[p1].x;
	int s2y=pntArray[p1].z;
	int s1x,s1y;
	while (		++tricount<pntCnt	)	//if this fails immediately, tc==2
	{
		s1x=s2x;
		s1y=s2y;
		p1=p2;
		p2=startpoint[tricount];
		s2x=pntArray[p2].x;
		s2y=pntArray[p2].z;

		breakif (!CHECK(CROSSCLOCK,p0,p1,p2,
						CrossClock(s0x,s0y,s1x,s1y,s2x,s2y)));
	}
	if (tricount==2)		return 0;			//first corner anticlockwise
	if (tricount==pntCnt)	return pntCnt-2;	//full poly complete

	enum	States	{OCCLUDE,ANTICLOCK,CLOCK,REVISIT}	state;


	int o1x=s2x;
	int o1y=s2y;

	s2x=	pntArray[startpoint[tricount-2]].x;
	s2y=	pntArray[startpoint[tricount-2]].z;
	if (CHECK(DOTFRONT,startpoint[tricount-2],p1,p2,
		CrossClock(s2x,s2y,s1x,s1y,o1x,o1y)))
		state=OCCLUDE;
	else
		state=ANTICLOCK;
	int testcnt=tricount;
	tricount--;	//indexes last good point

	//now reduce the size of this fan by looking for points which cut inside
	//having found a point which cuts inside, reduce the triangle count until it no longer does,
	//then continue searching until all remaining points in triangle have been checked.
	//
	//
	//Note that any occlusion must come from clockwise to anticlockwise
	//It must also cut through the line enclosing the last triangle.
	//If it does not cut through, then it must go clockwise again
	//before it can cut through again!
	//
	forever
	{	
		
		if (state==ANTICLOCK)
		{	//Point is anticlockwise and not occluding
			//use up points until clockwise again.

			while (testcnt<pntCnt)
			{
				p2=startpoint[testcnt];
				o1x=pntArray[p2].x;
				o1y=pntArray[p2].z;
				breakif(CHECK(CROSSCLOCK,p0,p1,p2,
					CrossClock(s0x,s0y,s1x,s1y,o1x,o1y)));
				testcnt++;
			}
			breakif(testcnt==pntCnt);
			state=CLOCK;
		}
		if (state==CLOCK)
		{	//Point is clockwise.
			//keep going until next point is anticlockwise
			//that line may OCCLUDE our poly by cutting through the front, 
			//or may just generate ANTICLOCK if it doesn't cut through.

			int o2x,o2y;
			while (testcnt<pntCnt)
			{
				o2x=o1x;
				o2y=o1y;
				p2=startpoint[testcnt];
				o1x=pntArray[p2].x;
				o1y=pntArray[p2].z;
				breakif (p2==p0 || p2==p1);
				breakif(!CHECK(CROSSCLOCK,p0,p1,p2,
					CrossClock(s0x,s0y,s1x,s1y,o1x,o1y)));
				testcnt++;
			}
			breakif(testcnt==pntCnt);
			//This is 10 multiplies and a divide, but it is only done
			//when the outline crosses the fan edge.
			if ((p2==p0 || p2==p1))
				state=REVISIT;
			else
				if (CHECK(INTERSECT,p0,p1,p2,
						DoLinesIntersect(s0x,s0y,s1x,s1y,o2x,o2y,o1x,o1y)))
					state=OCCLUDE;		//goes through our fan front
				else
					state=ANTICLOCK;	//goes arround our fan front
		}
		if (state==REVISIT)
		{
				testcnt++;
				p2=startpoint[testcnt];
				o1x=pntArray[p2].x;
				o1y=pntArray[p2].z;
				if (p2==p0 || p2==p1)
					state=REVISIT;	//again? can't happen. Said that about dejavu
				else
				if (CHECK(CROSSCLOCK,p0,p1,p2,
					CrossClock(s0x,s0y,s1x,s1y,o1x,o1y)))
					state=CLOCK;
				else
				{
					
					int	s2x=	pntArray[startpoint[tricount-2]].x;
					int	s2y=	pntArray[startpoint[tricount-2]].z;
					if (CHECK(DOTFRONT,startpoint[tricount-2],p1,p2,
						CrossClock(s2x,s2y,s1x,s1y,o1x,o1y)))
						state=OCCLUDE;	//I don't see how this can happen!
					else
						state=ANTICLOCK;
				}
		}
		if (state==OCCLUDE)
		{
			while (--tricount>1)

			{	//strip off triangles until OK again!
				p1=startpoint[tricount];
				s1x=pntArray[p1].x;
				s1y=pntArray[p1].z;
				breakif(CHECK(CROSSCLOCK,p0,p1,p2,
								CrossClock(s0x,s0y,s1x,s1y,o1x,o1y)));
			}
			breakif (tricount<2);
			state=CLOCK;
		}
	}
	return (tricount-1);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		genTri2
//Author		Paul.   
//Date			Mon 1 Jun 1998

//inputs:	pntCnt - number of points in the polygon
//			pntArray - array of point coordinate data
//			orgPolyDesc - original polygon point index list
//			triangleList - area to store the list of triangles & fans produced
//				<NO!!		1st byte = number of fans/triangles followed by>
//							a repeat of 1 byte = number of triangles in fan +
//							point indexes for the fan

//returns:	total number of fans produced
#define UBYTE(x) x
//------------------------------------------------------------------------------
int genTri2(UByte pntCnt,PntDef* pntArray,UByte* orgPolyDesc,UByte*& tL)
{
	abortNow=FALSE;

	UByte* triangleList=tL;

	UByte localpoly[1000];
	//2 copys of the polygon
	{
	UByte* src=orgPolyDesc;
	UByte* trg=localpoly;
	for (int i=pntCnt;--i>=0;)
		*trg++=*src++;
	src=orgPolyDesc;
	for (i=pntCnt;--i>=0;)
		*trg++=*src++;
	}
	//ok... got a doubled poly list. 
	//It doesn't matter where I start, I can always see the end of the poly!

	int startpoint=0;
	int minfan=1;
	int totalFans=0;
	while (pntCnt>3)
	{	//if pntCnt==3 then only 1 poly left, otherwise should be zero!
		int tricount=TriSeq(pntArray,localpoly+startpoint,pntCnt);
		if (tricount>minfan)
		{
			globalTriCount+=tricount;
			totalFans++;
			*triangleList++=UBYTE(tricount);	//+2 start points
			pntCnt-=tricount;
			UByte* src=localpoly+startpoint;
			*triangleList++=*src++;
			*triangleList++=*src++;
			while (--tricount>=0)
				*triangleList++=*src++;
			//copy remainder of poly down twice to make new list
			src-=1;
			UByte* trg=localpoly;
			UByte* src2=trg;
			for (tricount=pntCnt;--tricount>=0;)
				*trg++=*src++;
			for (tricount=pntCnt;--tricount>=0;)
				*trg++=*src2++;
			minfan=1;
			startpoint=0;	//but not the original zero.. that is on the end!
		}
		else
		{
			startpoint++;
			if (startpoint==pntCnt)	//dirty thought occurs to me... 
				if (minfan)			//I could let startpoint continue
					minfan=			//up to pntCnt*2 as I make only 1 triangle.
						startpoint=
							0;
				else
				{
					abortNow=TRUE;
					tL=triangleList;
					return totalFans;
				}
//DeadCode PD 15Oct98 					break;
		}
	}
	if (pntCnt==3)
	{
		globalTriCount++;
		*triangleList++=1;
		*triangleList++=localpoly[0];
		*triangleList++=localpoly[1];
		*triangleList++=localpoly[2];
		totalFans++;
	}
	else
		if (pntCnt>3)
		{
			_asm {int 3}
			totalFans=0;
		}

	tL=triangleList;

	return totalFans;
}


void TrimakerTestCode()
{
	/*
	PntDef pntArray[]=
	{
		{0, 0, 0,0},
		{256, 0, 0,0},
		{256, 256, 0,0},
		{0, 256, 0,0},
		{64, 0, 0,0},
		{128, 0, 0,0},
		{128, 64, 0,0},
		{192, 64, 0,0},
		{128, 128, 0,0},
		{192, 0, 0,0},
		{256, 64, 0,0},
		{256, 128, 0,0},
		{192, 128, 0,0},
		{192, 192, 0,0},
		{256, 192, 0,0},
		{192, 256, 0,0},
		{128, 256, 0,0},
		{128, 192, 0,0},
		{64, 192, 0,0},
		{64, 256, 0,0},
		{0, 192, 0,0},
		{0, 128, 0,0},
		{64, 128, 0,0},
		{64, 64, 0,0},
		{0, 64, 0,0}
	};

	UByte orgPolyDesc[]=
	{
		4,5,6,7,
		8,7,6,5,
		9,1,10,11,
		12,13,12,11,
		14,2,15,16,
		17,18,17,16,
		19,3,20,21,
		22,23,22,21,
		24,0
	};

	UByte triangleList[4096];
	UByte* tlp=triangleList;


	genTri2(34,pntArray,orgPolyDesc,tlp);
*/
}
