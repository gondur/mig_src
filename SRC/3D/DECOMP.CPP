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
//Filename       decomp.cpp
//System         
//Author         Paul.   
//Date           Wed 26 Aug 1998
//Description    Mig Alley landscape decompression routines
//------------------------------------------------------------------------------

#ifdef FAST_LAND

	#define FINDEDGEPOINTS(p1) 	CDecompressData::FastFindEdgePoints(UByte*& p1)
	#define FINDPNTSLNSPLYS(p1)	CDecompressData::FastFindPointsLinesPolys(UByte*& p1)
	#define GETALT(p1)			CDecompressData::fastGetAltitude(UByte*& p1)
	#define GETALTW(p1)			CDecompressData::fastGetAltWord(UByte*& p1)
	#define STARPLUSPLUS(p1)	*(p1)++ /*.fastPostInc()*/
	#define PLUSPLUS(p1)		(p1)++ /*.fastInc()*/
	#define GETALTITUDE(p1)		fastGetAltitude(p1)
	#define GETALTWORD(p1)		fastGetAltWord(p1)

#else

	#define FINDEDGEPOINTS(p1) 	CDecompressData::FindEdgePoints(UByte*& p1)
	#define FINDPNTSLNSPLYS(p1)	CDecompressData::FindPointsLinesPolys(UByte*& p1)
	#define GETALT(p1)			CDecompressData::getAltitude(UByte*& p1)
	#define GETALTW(p1)			CDecompressData::getAltWord(UByte*& p1)
	#define STARPLUSPLUS(p1)	*(p1)++
	#define	PLUSPLUS(p1)		(p1)++
	#define GETALTITUDE(p1)		getAltitude(p1)
	#define GETALTWORD(p1)		getAltWord(p1)

#endif

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FINDEDGEPOINTS
//Author		Paul.   
//Date			Wed 26 Aug 1998
//
//------------------------------------------------------------------------------
UWord FINDEDGEPOINTS(ip)
{
	UByte*	inptr=ip;
	UByte	tmp[5];

	pointdec[0]=*pplPoint0;
	pointdec[1]=*pplPoint1;
	pointdec[2]=*pplPoint2;
	pointdec[3]=*pplPoint3;

	for (int i=4;i<256;pointdec[i++]=*pplReset);

	Max_Points=4;

	UByte*	b0=tmp;

	tmp[0]=STARPLUSPLUS(inptr);
	tmp[1]=STARPLUSPLUS(inptr);
	tmp[2]=STARPLUSPLUS(inptr);
	tmp[3]=STARPLUSPLUS(inptr);
	if (tmp[0]==0xFF && tmp[1]==0xFF && tmp[3]==0xFF)
	{
		ip=inptr;
		return UWord(tmp[2])+0x8000;
	}
	tmp[4]=STARPLUSPLUS(inptr);

	//test to see if altitude data is present...
	altData=NO_ALT;
	if (tmp[0]&0x80){
		tmp[0]&=0x7F;
		//this means that some extra bytes follow..
		baseAltitude=STARPLUSPLUS(inptr);	//base alt value for the tile
		scaleAltitude=STARPLUSPLUS(inptr); //scaling factor for the altitude

		if (baseAltitude==0xFF&&scaleAltitude==0xFF)
			altData=WORD_ALT;
		else
		{
			altData=BYTE_ALT;
			baseAltitude<<=6;
		}

		//get the corner point altitudes

		if (altData==BYTE_ALT)
		{
			pointdec[0].alt=GETALTITUDE(inptr);
			pointdec[1].alt=GETALTITUDE(inptr);
			pointdec[2].alt=GETALTITUDE(inptr);
			pointdec[3].alt=GETALTITUDE(inptr);
		}
		else
		{
			pointdec[0].alt=GETALTWORD(inptr);
			//and normal data
			pointdec[0].shadeVal=STARPLUSPLUS(inptr);

			pointdec[1].alt=GETALTWORD(inptr);
			//and normal data
			pointdec[1].shadeVal=STARPLUSPLUS(inptr);

			pointdec[2].alt=GETALTWORD(inptr);
			//and normal data
			pointdec[3].shadeVal=STARPLUSPLUS(inptr);

			pointdec[3].alt=GETALTWORD(inptr);
			//and normal data
			pointdec[2].shadeVal=STARPLUSPLUS(inptr);
		}
	}

	//Used for light shading later on...
	totalEdgePoints=tmp[0]+tmp[1]+tmp[2]+tmp[3]+4;

	int lastx,lasty;

	lastx=0;	  	//top edge
	lasty=0;
	int pts=*b0++;
	topEdgeCnt=pts;
	int upf=0;
	pointdec[upf].unpairedfrom[0]=1;
	if (pts)

	do{
		lastx+=STARPLUSPLUS(inptr);
		pointdec[Max_Points].x=lastx;
		pointdec[Max_Points].y=lasty;

		if (altData==BYTE_ALT)
		{
			pointdec[Max_Points].alt=GETALTITUDE(inptr);
		}
		else if (altData==WORD_ALT)
		{
			pointdec[Max_Points].alt=GETALTWORD(inptr);
			pointdec[Max_Points].shadeVal=STARPLUSPLUS(inptr);
		}
		else pointdec[Max_Points].alt=0;

		PointsConnected(upf,Max_Points);
		pointdec[Max_Points].lastfrom=
			pointdec[Max_Points].unpairedfrom[0]=1;
		pointdec[Max_Points].lastto=upf;
		pointdec[upf].lastfrom=
			pointdec[upf].unpairedfrom[0]=
				Max_Points;
		pointdec[1].lastto=Max_Points;
		upf=Max_Points;
		Max_Points++;
	}while (--pts!=0!=0);
	PointsConnected(upf,1);

	lastx=256;		//RHS edge
	lasty=0;
	pts=*b0++;
	rightEdgeCnt=pts;
	upf=1;
	pointdec[upf].unpairedfrom[0]=2;
	if (pts)
	do{
		lasty+=STARPLUSPLUS(inptr);
		pointdec[Max_Points].x=lastx;
		pointdec[Max_Points].y=lasty;

		if (altData==BYTE_ALT)
			pointdec[Max_Points].alt=GETALTITUDE(inptr);
		else if (altData==WORD_ALT)
		{
			pointdec[Max_Points].alt=GETALTWORD(inptr);
			pointdec[Max_Points].shadeVal=STARPLUSPLUS(inptr);
		}
		else pointdec[Max_Points].alt=0;

		PointsConnected(upf,Max_Points);
		pointdec[Max_Points].lastfrom=
			pointdec[Max_Points].unpairedfrom[0]=2;
		pointdec[Max_Points].lastto=upf;
		pointdec[upf].lastfrom=
			pointdec[upf].unpairedfrom[0]=Max_Points;
		pointdec[2].lastto=Max_Points;
		upf=Max_Points;
		Max_Points++;
	}while (--pts!=0!=0);
	PointsConnected(upf,2);


	lastx=0;		//BOT edge
	lasty=256;
	pts=*b0++;
	bottomEdgeCnt=pts;
	upf=3;
	pointdec[2].unpairedfrom[0]=(UByte)upf;
	if (pts)
	do{
		lastx+=STARPLUSPLUS(inptr);
		pointdec[Max_Points].x=lastx;
		pointdec[Max_Points].y=lasty;

		if (altData==BYTE_ALT)
			pointdec[Max_Points].alt=GETALTITUDE(inptr);
		else if (altData==WORD_ALT)
		{
			pointdec[Max_Points].alt=GETALTWORD(inptr);
			pointdec[Max_Points].shadeVal=STARPLUSPLUS(inptr);
		}
		else pointdec[Max_Points].alt=0;

		PointsConnected(upf,Max_Points);
		pointdec[Max_Points].lastfrom=
			pointdec[Max_Points].unpairedfrom[0]=(UByte)upf;
		pointdec[Max_Points].lastto=2;
		pointdec[upf].lastto=Max_Points;
		pointdec[2].lastfrom=
			pointdec[2].unpairedfrom[0]=Max_Points;
		upf=Max_Points;
		Max_Points++;
	}while (--pts!=0);
	PointsConnected(upf,2);

	lastx=0;		//LHS edge
	lasty=0;
	pts=*b0++;
	leftEdgeCnt=pts;
	upf=0;
	pointdec[3].unpairedfrom[0]=(UByte)upf;
	if (pts)
	do{
		lasty+=STARPLUSPLUS(inptr);
		pointdec[Max_Points].x=lastx;
		pointdec[Max_Points].y=lasty;

		if (altData==BYTE_ALT)
			pointdec[Max_Points].alt=GETALTITUDE(inptr);
		else if (altData==WORD_ALT)
		{
			pointdec[Max_Points].alt=GETALTWORD(inptr);
			pointdec[Max_Points].shadeVal=STARPLUSPLUS(inptr);
		}
		else pointdec[Max_Points].alt=0;

		PointsConnected(upf,Max_Points);
		pointdec[Max_Points].lastfrom=
			pointdec[Max_Points].unpairedfrom[0]=(UByte)upf;
		pointdec[Max_Points].lastto=3;
		pointdec[upf].lastto=Max_Points;
		pointdec[3].lastfrom=
			pointdec[3].unpairedfrom[0]=Max_Points;
		upf=Max_Points;
		Max_Points++;
	}while (--pts!=0);
	PointsConnected(upf,3);

	Highest_Point_Defined=Max_Points;
	pts=*b0++;
	if (pts)
	do{
			pointdec[Max_Points].x=0;
			pointdec[Max_Points].y=0;
			pointdec[Max_Points].alt=0;
			Max_Points++;
	}while (--pts!=0);

	ip=inptr;
	return UWord(0);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FINDPNTSLNSPLYS
//Author		Paul.   
//Date			Wed 26 Aug 1998
//------------------------------------------------------------------------------
void FINDPNTSLNSPLYS(ip)
{
	UByte* inptr=ip;

	int	coordslastpoint=0;
	UByte endcode=STARPLUSPLUS(inptr);
	for (int point=0;point<Max_Points;point++)
		while (pointdec[point].lastto==NULLCON || pointdec[point].unpairedfrom[0]!=NULLCON)
			if (endcode==JOIN_POLY_NEXT)
			{
				*PolyPtr++=JOIN_POLY_NEXT;
				*PolyPtr++=STARPLUSPLUS(inptr);
				*PolyPtr++=(UByte)point;
				if (point!=0 && pointdec[point].x==0 && pointdec[point].y==0)
				{
					pointdec[point].x=(UByte)(pointdec[coordslastpoint].x+STARPLUSPLUS(inptr));
					pointdec[point].y=(UByte)(pointdec[coordslastpoint].y+STARPLUSPLUS(inptr));

					if (altData==BYTE_ALT)
						pointdec[point].alt=GETALTITUDE(inptr);
					else if (altData==WORD_ALT)
					{
						pointdec[point].alt=GETALTWORD(inptr);
						pointdec[point].shadeVal=STARPLUSPLUS(inptr);
					}
					else pointdec[point].alt=0;

					assert(Highest_Point_Defined==point&&" new poly started with unknown point number?");
					Highest_Point_Defined++;
				}
				coordslastpoint=point;

				int curr=point;
				int last=NULLCON;
				if (pointdec[curr].unpairedfrom)
					endcode=pointdec[curr].unpairedfrom[0];
				else
					endcode=STARPLUSPLUS(inptr);

				while (endcode<JOIN_ROAD_NEXT)
				{
					if (endcode==JOIN_FOLLOW_TO)
						endcode=(UByte)pointdec[curr].lastto;
					elseif (endcode==JOIN_FOLLOW_FROM)
						endcode=(UByte)pointdec[curr].lastfrom;
					elseif (endcode==JOIN_NEW_COORDS)
					{
						endcode=Highest_Point_Defined++;
						pointdec[endcode].x=(UByte)(pointdec[coordslastpoint].x+STARPLUSPLUS(inptr));
						pointdec[endcode].y=(UByte)(pointdec[coordslastpoint].y+STARPLUSPLUS(inptr));

						if (altData==BYTE_ALT)
							pointdec[endcode].alt=GETALTITUDE(inptr);
						else if (altData==WORD_ALT)
						{
							pointdec[endcode].alt=GETALTWORD(inptr);
							pointdec[endcode].shadeVal=STARPLUSPLUS(inptr);
						}
						else pointdec[endcode].alt=0;
					}
					*PolyPtr++=endcode;
					coordslastpoint=endcode;
					PointsConnected(curr,endcode);

					if (last!=NULLCON)
						pointdec[curr].lastfrom=last;
					pointdec[curr].lastto=endcode;
					for (int i=0;i<4;i++)
						if (pointdec[curr].unpairedfrom[i]==endcode)
						{
							for (int j=i+1;j<4;j++)
								breakif (pointdec[curr].unpairedfrom[j]==NULLCON);
							pointdec[curr].unpairedfrom[i]=pointdec[curr].unpairedfrom[j-1];
							pointdec[curr].unpairedfrom[j-1]=NULLCON;
							break;
						}
					if (i==4)
					{
						for (int i=0;i<4;i++)
							breakif (pointdec[endcode].unpairedfrom[i]==NULLCON);
						//assert i!=4;
						pointdec[endcode].unpairedfrom[i]=(UByte)curr;
					}
					last=curr;
					curr=endcode;
					endcode=STARPLUSPLUS(inptr);
				}
				PointsConnected(curr,point);
				*PolyPtr++=(UByte)point;
				pointdec[curr].lastfrom=last;
				pointdec[curr].lastto=point;
				pointdec[point].lastfrom=curr;
				for (int i=0;i<4;i++)
					if (pointdec[curr].unpairedfrom[i]==point)
					{
						for (int j=i+1;j<4;j++)
							breakif (pointdec[curr].unpairedfrom[j]==NULLCON);
						pointdec[curr].unpairedfrom[i]=pointdec[curr].unpairedfrom[j-1];
						pointdec[curr].unpairedfrom[j-1]=NULLCON;
						break;
					}
				if (i==4)
				{
					for (int i=0;i<4;i++)
						breakif (pointdec[point].unpairedfrom[i]==NULLCON);
					//assert i!=4;
					pointdec[point].unpairedfrom[i]=(UByte)curr;
				}

			}
			else
			{	//its a road
				*LinePtr++=JOIN_ROAD_NEXT;
				*LinePtr++=STARPLUSPLUS(inptr);
				*LinePtr++=(UByte)point;
				int curr=point;
				endcode=(UByte)point;
				if (endcode!=0 && pointdec[endcode].x==0 && pointdec[endcode].y==0)
				{
					pointdec[endcode].x=(UByte)(pointdec[coordslastpoint].x+STARPLUSPLUS(inptr));
					pointdec[endcode].y=(UByte)(pointdec[coordslastpoint].y+STARPLUSPLUS(inptr));

					if (altData==BYTE_ALT)
						pointdec[endcode].alt=GETALTITUDE(inptr);
					else if (altData==WORD_ALT)
					{
						pointdec[endcode].alt=GETALTWORD(inptr);
						pointdec[endcode].shadeVal=STARPLUSPLUS(inptr);
					}
					else pointdec[endcode].alt=0;

					assert(Highest_Point_Defined==point&&" new poly started with unknown point number?");
					Highest_Point_Defined++;
				}
				coordslastpoint=endcode;


				if (pointdec[curr].unpairedfrom)
					endcode=pointdec[curr].unpairedfrom[0];
				else
					endcode=STARPLUSPLUS(inptr);
				int last=NULLCON;
				while (endcode<JOIN_ROAD_NEXT)
				{
					if (endcode==JOIN_FOLLOW_TO)
						endcode=(UByte)pointdec[curr].lastto;
					elseif (endcode==JOIN_FOLLOW_FROM)
						endcode=(UByte)pointdec[curr].lastfrom;
					elseif (endcode==JOIN_NEW_COORDS)
					{
						endcode=Highest_Point_Defined++;
						pointdec[endcode].x=(UByte)(pointdec[coordslastpoint].x+STARPLUSPLUS(inptr));
						pointdec[endcode].y=(UByte)(pointdec[coordslastpoint].y+STARPLUSPLUS(inptr));

						if (altData==BYTE_ALT)
							pointdec[endcode].alt=GETALTITUDE(inptr);
						else if (altData==WORD_ALT)
						{
							pointdec[endcode].alt=GETALTWORD(inptr);
							pointdec[endcode].shadeVal=STARPLUSPLUS(inptr);
						}
						else pointdec[endcode].alt=0;
					}
					PointsConnected(curr,endcode);
					*LinePtr++=endcode;
					coordslastpoint=endcode;

					if (last!=NULLCON)
						pointdec[curr].lastfrom=last;
					pointdec[curr].lastto=endcode;
					last=curr;
					curr=endcode;
					endcode=STARPLUSPLUS(inptr);
				}
			}
	coordslastpoint=0;
	//extra lines:
	while (endcode!=JOIN_POLY_NEXT)
	{
		*LinePtr++=JOIN_ROAD_NEXT;
		*LinePtr++=STARPLUSPLUS(inptr);
		endcode=STARPLUSPLUS(inptr);
		if (endcode==JOIN_NEW_COORDS)
		{
			endcode=Highest_Point_Defined++;
			pointdec[endcode].x=(UByte)(pointdec[coordslastpoint].x+STARPLUSPLUS(inptr));
			pointdec[endcode].y=(UByte)(pointdec[coordslastpoint].y+STARPLUSPLUS(inptr));

			if (altData==BYTE_ALT)
				pointdec[endcode].alt=GETALTITUDE(inptr);
			else if (altData==WORD_ALT)
			{
				pointdec[endcode].alt=GETALTWORD(inptr);
				pointdec[endcode].shadeVal=STARPLUSPLUS(inptr);
			}
			else pointdec[endcode].alt=0;
		}
		*LinePtr++=(UByte)(point=endcode);
		coordslastpoint=endcode;
		endcode=STARPLUSPLUS(inptr);
		int curr=point;
		int last=NULLCON;
		while (endcode<JOIN_ROAD_NEXT)
		{
			if (endcode==JOIN_FOLLOW_TO)
				endcode=(UByte)pointdec[curr].lastto;
			elseif (endcode==JOIN_FOLLOW_FROM)
				endcode=(UByte)pointdec[curr].lastfrom;
			elseif (endcode==JOIN_NEW_COORDS)
			{
				endcode=Highest_Point_Defined++;
				pointdec[endcode].x=(UByte)(pointdec[coordslastpoint].x+STARPLUSPLUS(inptr));
				pointdec[endcode].y=(UByte)(pointdec[coordslastpoint].y+STARPLUSPLUS(inptr));

				if (altData==BYTE_ALT)
					pointdec[endcode].alt=GETALTITUDE(inptr);
				else if (altData==WORD_ALT)
				{
					pointdec[endcode].alt=GETALTWORD(inptr);
					pointdec[endcode].shadeVal=STARPLUSPLUS(inptr);
				}
				else pointdec[endcode].alt=0;
			}
			PointsConnected(curr,endcode);
			*LinePtr++=endcode;
			coordslastpoint=endcode;
			if (last!=NULLCON)
				pointdec[curr].lastfrom=last;
			pointdec[curr].lastto=endcode;
			last=curr;
			curr=endcode;
			endcode=STARPLUSPLUS(inptr);
		}
	}
	*LinePtr++=JOIN_POLY_NEXT;
	*PolyPtr++=JOIN_ROAD_NEXT;
	if (altData==WORD_ALT) PLUSPLUS(inptr);
	ip=inptr;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GETALT
//Author		Paul.   
//Date			Wed 26 Aug 1998
//------------------------------------------------------------------------------
ULong GETALT(inptr)
{
	ULong altVal=ULong((ULong(STARPLUSPLUS(inptr))*scaleAltitude)+baseAltitude);
	if (altVal<lowestAlt) lowestAlt=altVal;
	if (altVal>highestAlt) highestAlt=altVal;
	return altVal;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GETALTW
//Author		Paul.   
//Date			Wed 26 Aug 1998
//------------------------------------------------------------------------------
ULong GETALTW(inptr)
{
	UByte lo,hi;
	lo=STARPLUSPLUS(inptr);
	hi=STARPLUSPLUS(inptr);
	UWord retVal=(hi<<8)+lo;
	if (retVal<lowestAlt) lowestAlt=retVal;
	if (retVal>highestAlt) highestAlt=retVal;
	return UWord(retVal);
}

#undef FINDEDGEPOINTS
#undef FINDPNTSLNSPLYS
#undef GETALT
#undef GETALTW
#undef STARPLUSPLUS
#undef PLUSPLUS
#undef GETALTITUDE
#undef GETALTWORD


