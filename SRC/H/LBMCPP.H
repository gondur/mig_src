//------------------------------------------------------------------------------
//Filename       lbmcpp.h
//System         
//Author         Jim Taylor
//Date           Mon 7 Apr 1997
//Description    This is the communial body of the LBM row unpack routine.
//				 I have put it in a header file rather than a macro so that you
//				 can debug it.
//					
//				It is included a number of times into LBM.CPP with different inputs
//				
//
//------------------------------------------------------------------------------





//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	Graphic::UnpackNRow
//------------------------------------------------------------------------------
//Author		Paul.   
//Date			Fri 7 Jul 1995
//Modified		DAW 11Jan96
//
//Description	Unpack a row of artwork
//
//Inputs		Source data
//				Length of line in data
//				start	x
//				start	y
//				physical min x
//				physical max x
//
//Returns		Data ptr moved
//
//Externals
//------------------------------------------------------------------------------
//UByte *Graphic::UnpackNRow(UByte *c, SLong width, SLong x, SLong y, SLong minx, SLong maxx)
//------------------------------------------------------------------------------
//{
//THIS IS AN EXAMPLE OF WHAT MAY NEED TO BE DEFINED

//	minx=(minx>>1);
//	maxx=((maxx+1)>>1);
//	x>>=1;
//	#define	TRANSFERVALUESIZE UWord

//	#define LOADVALUE(x)	TRANSFERVALUE=*(TRANSFERVALUESIZE*)(ExpandBuff[x])
//	#define COPYVALUE(x,y)	*((TRANSFERVALUESIZE*&)x)++=*(TRANSFERVALUESIZE*)(ExpandBuff[x])

	#ifndef SAVEVALUE
	#define SAVEVALUE(x)	*((TRANSFERVALUESIZE*&)x)++=TRANSFERVALUE
	#endif
	#ifndef DELTAVALUE
	#define DELTAVALUE(x,d) (TRANSFERVALUESIZE*&)x += d
	#endif

	TRANSFERVALUESIZE TRANSFERVALUE;

//THIS IS THE ACTUAL START

	LogicalPtr	scraddr=	((long)BytesPerScanLine * y) + logicalscreenptr;
//TempCode JIM 19Feb96 	Colour		srccol;
	UByte		b;
	SLong		i,Count;




//DeadCode JIM 22May97 	assert((BytesPerPixel==1)&&("LBM Must only have 1byte/pixel"));
	int	residue=0;
//DeadCode JIM 08Apr97  	enum	{RT_SKIP,RT_RUN,RT_COPY}	residuetype=RT_SKIP;
	Bool	skipplotting=FALSE;

	////// CASE 1: starting off left clip - clip necessary

	if (x<minx && x+width>=minx)
	{
		while (x<minx)
		{
			b=*(c++);
			if (b<0x80)
			{	//COPY
				Count = 1+(SByte) b;
				x+=Count;
				width-=Count;
					c+=Count;
			}
			elseif (b==0x80)
			{	//SKIP
				Count= 1 + *(c++);
				x+=Count;
				width-=Count;
			}
			else
			{	//RUN
				Count = 1-(SByte)b;
				c++;
				width-=Count;
				x+=Count;
			}
		}

	//////1.2 Handle overflow of segment overlapping left clip
		if (b<0x80)
		{
			residue=x-minx;
			c-=residue;
			x=minx;
			DELTAVALUE(scraddr,x);			//set to starting pixel...
			x+=Count=residue;
			residue=0;
			if (x>maxx)
			{
				residue=x-maxx-1;
				Count=Count-residue;
				skipplotting=TRUE;
			}
			if (Count)
			do
			{
				COPYVALUE(scraddr,*c++);
			}
			while (--Count!=0);
			c+=residue;	
		}
		else
		if (b!=0x80)
		{
			LOADVALUE(*(c-1));
			residue=x-minx;
			x=minx;
			DELTAVALUE(scraddr,x);			//set to starting pixel...
			x+=Count=residue;
			residue=0;
			if (x>maxx)
			{
				skipplotting=TRUE;
				residue=x-maxx-1;
				Count=Count-residue;
			}
			if (Count)
			do
			{
				SAVEVALUE(scraddr);
			}
			while (--Count!=0);
		}
		else
			{
				DELTAVALUE(scraddr,x);			//set to starting pixel...
				if (x>maxx)
					skipplotting=TRUE;
			}
	}
	else
		if (x>=minx && x<=maxx)
		{
			DELTAVALUE(scraddr,x);			//set to starting pixel...
		}
		else
			skipplotting=TRUE;

	residue=0;
	if (!skipplotting)
	///// CASE 3: MAIN ARTWORK UNPACK
		if (x+width<=maxx)
	/////CASE 3A: FAST UNPACK - CLIP TO WIDTH
			while (width)
			{
				b=*(c++);
				if (b<0x80)
				{	//COPY
					Count = 1+(SByte) b;
					width-=Count;
					do
					{
						COPYVALUE(scraddr,*c++);
					}
					while (--Count!=0);
				}
				elseif (b==0x80)
				{	//SKIP
					Count= 1 + *(c++);
					width-=Count;
					DELTAVALUE(scraddr,Count);
				}
				else
				{	//RUN
					Count = 1-(SByte) b;
					width-=Count;
					LOADVALUE(*c++);
					do
					{
						SAVEVALUE(scraddr);
					}
					while (--Count!=0);
				}
			}
		else
	/////CASE 3B: SLOW UNPACK - CLIP TO MAXX
		{
			while (x<=maxx)
			{
				b=*(c++);
				if (b<0x80)
				{	//COPY
					Count = 1+(SByte) b;
					x+=Count;
					width-=Count;
					if (x<=maxx)
						do
						{
							COPYVALUE(scraddr,*c++);
						}
						while (--Count!=0);
				}
				elseif (b==0x80)
				{	//SKIP
					Count= 1 + *(c++);
					width-=Count;
					x+=Count;
					DELTAVALUE(scraddr,Count);
				}
				else
				{	//RUN
					Count = 1-(SByte) b;
					x+=Count;
					width-=Count;
					LOADVALUE(*c++);
					if (x<=maxx)
						do
						{
							SAVEVALUE(scraddr);
						}
						while (--Count!=0);

				}
			}
			////// 3B2: Overflow of last unpack
			if (x>maxx)
			{
				if (b<0x80)
				{
					residue=x-maxx-1;
					Count-=residue;
					do
					{
						COPYVALUE(scraddr,*c++);
					}
					while (--Count!=0);
					c+=residue;
				}
				elseif (b!=0x80)
				{
					residue=x-maxx-1;
					Count-=residue;
					do
					{
						SAVEVALUE(scraddr);
					}
					while (--Count!=0);
				}
			}
		}

	///// CASE 4: RHS CLIPPED DATA - UP TO WIDTH
	if (width)
		while(width>0)
		{
			b=*(c++);
			if (b<0x80)
			{	//COPY
				Count = 1+(SByte) b;
				width-=Count;
				c+=Count;
			}
			elseif (b==0x80)
			{	//SKIP
				Count= 1 + *(c++);
				width-=Count;
			}
			else
			{	//RUN
				Count = 1-(SByte)b;
				c++;
				width-=Count;
			}
		}

	return(c);
	//THAT'S YER LOT
}

#undef	LOADVALUE
#undef	SAVEVALUE
#undef	COPYVALUE
#undef	DELTAVALUE
#undef TRANSFERVALUESIZE
