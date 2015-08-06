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
//Filename       trimaker.cpp
//System         
//Author         Paul.   
//Date           Wed 3 Jun 1998
//Description    Code shared with MiG Alley game code
//------------------------------------------------------------------------------

#ifndef IN_MIGLAND_CPP

#define bool Bool
#define true TRUE
#define false FALSE

struct PntDef{
	UWord x,z;
	UWord alt;
	UByte used;
	UByte shadeVal;
};

#else

#define PntDef PointDef

#endif

Bool abortNow;

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
inline void minMax(UWord in1,UWord in2,UWord in3,UWord& minVal,UWord& maxVal)
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

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CheckTri
//Author		Paul.   
//Date			Mon 1 Jun 1998
//------------------------------------------------------------------------------
bool CheckTri(int pntCnt,UByte* polyDef,PntDef* pntArray,int p0,int p1,int p2)
{
	const bool INSIDE=false;
	const bool OUTSIDE=true;

	UByte i0=polyDef[p0];
	UByte i1=polyDef[p1];
	UByte i2=polyDef[p2];

	PntDef& pt0=pntArray[i0];
	PntDef& pt1=pntArray[i1];
	PntDef& pt2=pntArray[i2];

	SLong vi,vj,wi,wj;

	vi=SLong(pt1.x)-SLong(pt0.x);
	vj=SLong(pt1.z)-SLong(pt0.z);

	wi=SLong(pt1.x)-SLong(pt2.x);
	wj=SLong(pt1.z)-SLong(pt2.z);

	if (vi*wj>=wi*vj) return false; //failed on crossproduct test

	//check that no other active points in the poly are contained
	//within this new triangle

	for (int x=(p2+1)%pntCnt;x!=p0;++x%=pntCnt)
	{
		UByte it=polyDef[x];

		if (it!=i0&&it!=i1&&it!=i2)
		{
			SWord ptx=pntArray[it].x;
			SWord ptz=pntArray[it].z;

			SWord x0,y0,x1,y1,x2,y2;

			x0=SWord(pt0.x)-ptx;
			y0=SWord(pt0.z)-ptz;

			//if the test point matches vertex 0 return false (inside)
			if (x0==0 && y0==0) return false;

			x1=SWord(pt1.x)-ptx;
			y1=SWord(pt1.z)-ptz;

			//if the test point matches vertex 1 return false (inside)
			if (x1==0 && y1==0) return false;

			x2=SWord(pt2.x)-ptx;
			y2=SWord(pt2.z)-ptz;

			//if the test point matches vertex 2 return false (inside)
			if (x2==0 && y2==0) return false;

			//if all points are to the left of the test point then no more
			//checks are required for this test point

			if (!(x0>0 && x1>0 && x2>0))
			{
				if (x0>0 || x1>0 || x2>0) 
				{
					SWord count;
				
					//if any of the triangle sides are horizontal and at the
					//same y as the test point then return false (inside) if
					//the test point lies between the sides endpoints

					if ((count=(y0==0)+(y1==0))==2 && (x0^x1)<0) 			
						return false;
					else if (count && (count=(y1==0)+(y2==0))==2 && (x1^x2)<0)	
						return false;
					else if (count && (count=(y2==0)+(y0==0))==2 && (x2^x0)<0)	
						return false;
					else if (!y0)
					{
						if ((y1^y2)<0) return false;
					}
					else if (!y1)
					{
						if ((y2^y0)<0) return false;
					}
					else if (!y2)
					{
						if ((y0^y1)<0) return false;
					}
					else
					{
						count=0;

						//test for intersection of segment v0->v1
						if ((y0^y1)<0)
						{
							if ((x0^x1)<0) 
							{
								SLong yiy0=SLong(-y0)<<16;
								SLong x1x0=SLong(x1-x0)<<16;
								SLong y1y0=SLong(y1-y0)<<16;
								SLong res=MULDIVSIN(yiy0,x1x0,y1y0)+(x0<<16);

								//point is classified as inside if it is on the line
								if (!((res+0x7F)&0xFFFFFF00)) return false;

								if (res>0) count++; //cross over detected
							}
							else count++; //cross over detected
						}

						if ((y1^y2)<0) 
						{
							if ((x1^x2)<0) 
							{
								SLong yiy1=SLong(-y1)<<16;
								SLong x2x1=SLong(x2-x1)<<16;
								SLong y2y1=SLong(y2-y1)<<16;
								SLong res=MULDIVSIN(yiy1,x2x1,y2y1)+(x1<<16);

								//point is classified as inside if it is on the line
								if (!((res+0x7F)&0xFFFFFF00)) return false;

								if (res>0) count++; //cross over detected
							}
							else count++;		//cross over detected
						}

						//if count is 2 then there's no need to do the final
						//test because the test ray cannot intersect more than
						//2 sides of the triangle
						if (count!=2)
						{
							if ((y2^y0)<0)
							{
								if ((x2^x0)<0) 
								{
									SLong yiy2=SLong(-y2)<<16;
									SLong x0x2=SLong(x0-x2)<<16;
									SLong y0y2=SLong(y0-y2)<<16;
									SLong res=MULDIVSIN(yiy2,x0x2,y0y2)+(x2<<16);

									//point is classified as inside if it is on the line
									if (!((res+0x7F)&0xFFFFFF00)) return false;
	
									if (res>0) count++; //cross over detected
								}
								else count++; //cross over detected
							}
					
							//even number of crossings means the point is outside
							//the triangle. odd number means the point is inside

							if (count&1) return false;
						}
					}
				}
				else if (x0==0 && x1==0)
				{
				 	if ((y0^y1)<0) return false;
				}
				else if (x1==0 && x2==0)
				{
				 	if ((y1^y2)<0) return false;
				}
				else if (x2==0 && x0==0)
				{
				 	if ((y2^y0)<0) return false;
				}
			}
		}
	}
	return true;
}

/*
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CheckTri
//Author		Paul.   
//Date			Mon 1 Jun 1998
//------------------------------------------------------------------------------
bool CheckTri(int pntCnt,UByte* polyDef,PntDef* pntArray,int p0,int p1,int p2)
{
//----------------------------
// Vector structure definition
//----------------------------

	struct BigVec{
		SLong	p[2];
		BigVec(int dx=0,int dy=0) {p[0]=dx; p[1]=dy;}
		SLong& operator[] (int i) {return p[i];}
		bool operator%(BigVec& pnt) { return (bool)(p[0]*pnt[1]<p[1]*pnt[0]); }
	};

//-----------------------------
//BigPnt structure definition
//-----------------------------
typedef struct BigPnt{
		enum {SCALE_FACTOR=16};

		SLong	p[2];

		BigPnt(int x=0,int y=0) {p[0]=SLong(x); p[1]=SLong(y);}
		BigPnt(PntDef& pnt) {p[0]=pnt.x<<SCALE_FACTOR; p[1]=pnt.z<<SCALE_FACTOR;}

		SLong& operator[] (int i) {return p[i];}
		bool operator==(BigPnt& pnt) {return (bool)(p[0]==pnt[0]&&p[1]==pnt[1]);}
		BigPnt operator-(BigPnt& pnt) {return BigPnt(p[0]-pnt[0],p[1]-pnt[1]);}
	}
	BigDelta;

//----------------
//Code starts here
//----------------

	UByte i0=polyDef[p0];
	UByte i1=polyDef[p1];
	UByte i2=polyDef[p2];

	PntDef& pt0=pntArray[i0];
	PntDef& pt1=pntArray[i1];
	PntDef& pt2=pntArray[i2];

	BigVec v((int)pt1.x-(int)pt0.x,(int)pt1.z-(int)pt0.z);
	BigVec w((int)pt1.x-(int)pt2.x,(int)pt1.z-(int)pt2.z);

	if (!(v%w)) return false;	//failed on crossproduct test

	//check that no other active points in the poly are contained
	//within this new triangle

	//generate coordinates of a box 
	//surrounding the new triangle

	UWord xmin,xmax,zmin,zmax;

	minMax(pt0.x,pt1.x,pt2.x,xmin,xmax);
	minMax(pt0.z,pt1.z,pt2.z,zmin,zmax);

	BigPnt bp[3]={pt0,pt1,pt2};
	BigDelta bd[3]={bp[1]-bp[0],bp[2]-bp[1],bp[0]-bp[2]};

	SLong bmaxx[3],bminx[3],bmaxz[3],bminz[3];

	for (int x=0;x<3;x++)
	{
		int y=(x+1)%3;
		minMax(bp[x][0],bp[y][0],bminx[x],bmaxx[x]);
		minMax(bp[x][1],bp[y][1],bminz[x],bmaxz[x]);
	}

	for (x=(p2+1)%pntCnt;x!=p0;x=(x+1)%pntCnt)
	{
		UByte it=polyDef[x];

		if (it!=i0&&it!=i1&&it!=i2)
		{
			PntDef& testPnt=pntArray[polyDef[x]];
	
			//bounding box test first
			if (testPnt.x>=xmin && testPnt.x<=xmax && testPnt.z>=zmin && testPnt.z<=zmax)
			{
				//the test point is inside the bounding box
				//further tests are required

				SLong btx=testPnt.x<<BigPnt::SCALE_FACTOR;
				SLong btz=testPnt.z<<BigPnt::SCALE_FACTOR;
	
				//Count intersections between the line
				//starting at point 
				int	intersectionCnt=0;
	
				for (int l=0;l<3;l++)
				{
					if (bd[l][1]!=0)
					{
						SLong brx=MULDIVSIN((btz-bp[l][1]),bd[l][0],bd[l][1])+bp[l][0];
						//reject immediately if the intersection
						//point is the starting point ie. the
						//test point lies on the line
//Old_Code PD 12Jun98 						if (((brx+0x7FFF)&0xFFFF0000)==btx)
						if (((brx+0x7F)&0xFFFFFF00)==btx)
//DeadCode PD 06Aug98 						if (((brx+0x7FF)&0xFFFFF000)==btx)
							//I know that the X ordinate is on the
							//line. Test the Y ordinate to make sure
							//that the point is on the line
							if (btz>=bminz[l] && btz<=bmaxz[l]) return false; //on the line is inside
	
						//test to see if the x intersection value
						//lies on the line segment that we're
						//interested in & that it is on the +ve
						//side of the initial starting point
						if (brx>btx)
						{
							if (brx==bmaxx[l] || brx==bminx[l])
							{
								//Only get 1/2 intersection if
								//we've hit a vertex
								BigPnt hit(brx,btz);
								if (hit==bp[0] || hit==bp[1] || hit==bp[2])
									intersectionCnt++;
								else
									intersectionCnt+=2;
							}
							else if (brx<bmaxx[l] && brx>bminx[l])							
								intersectionCnt+=2;
						}
					}
				}
				//odd number of intersections means that
				//the point is inside
				if ((intersectionCnt&0x02)==0x02) return false;
			}
		}
	}
	return true;
}*/

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		genTri2
//Author		Paul.   
//Date			Mon 1 Jun 1998

//inputs:	pntCnt - number of points in the polygon
//			pntArray - array of point coordinate data
//			orgPolyDesc - original polygon point index list
//			triangleList - area to store the list of triangles & fans produced
//							1st byte = number of fans/triangles followed by
//							a repeat of 1 byte = number of triangles in fan +
//							point indexes for the fan

//returns:	total number of fans produced

//------------------------------------------------------------------------------
int genTri2(UByte pntCnt,PntDef* pntArray,UByte* orgPolyDesc,UByte*& triangleList)
{
	int totalFans=0;
	UByte* pTri=triangleList;	//place to store triangle fan data
	int pointsLeft=pntCnt;

	UByte* localPoly=new UByte[pointsLeft];
	UByte* swapPoly=new UByte[pointsLeft];

	for (int x=0;x<pointsLeft;localPoly[x]=orgPolyDesc[x],x++) {}

	int fanMin=2; //minimum no of triangles allowed in a fan
	int p0=0;
	int testCnt=0;
	abortNow=FALSE;

	while (pointsLeft>3 && !abortNow)
	{
		int p1=(p0+1)%pointsLeft;
		int p2=(p0+2)%pointsLeft;
		int fanCount=0;

		//try to make as large a fan as possible
		while (CheckTri(pointsLeft,localPoly,pntArray,p0,p1,p2))
		{
			fanCount++;
			p1=p2;
			p2=(p1+1)%pointsLeft;
		}
		//Check to see if we've generated a fan properly

		if (fanCount>=fanMin)
		{
			globalTriCount+=fanCount;
			//Add this fan to the list
			*pTri++=UByte(fanCount);
			for (int x=0;x<fanCount+2;x++) *pTri++=localPoly[(p0+x)%pointsLeft];

			//remove points that are no longer required
			UByte* tmp=swapPoly;
			for (x=p1;x!=p0;x=(x+1)%pointsLeft) *tmp++=localPoly[x];
			*tmp++=localPoly[x]; 	
			tmp=swapPoly; swapPoly=localPoly; localPoly=tmp;
			p0=0;
			testCnt=0;
			fanMin=2;
			pointsLeft-=fanCount;
			totalFans++;
		}
		else
		{
		 	p0=(p0+1)%pointsLeft;
			testCnt++;			//number of tests done with no fans produced

			if (testCnt==pointsLeft)
			{
				testCnt=0;
				if (fanMin==2)	fanMin=1;
				else			abortNow=TRUE;
			}
		}
	}

	if (pointsLeft==3&&!abortNow)
	{
		//add the last single triangle
		*pTri++=UByte(1);				//fan of 1 triangle
		*pTri++=localPoly[0];
		*pTri++=localPoly[1];
		*pTri++=localPoly[2];

		totalFans++;
	}
	delete[]localPoly;
	delete[]swapPoly;

	triangleList=pTri;
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
