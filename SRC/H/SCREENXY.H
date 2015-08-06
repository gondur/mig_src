//------------------------------------------------------------------------------
//Filename       screenxy.h
//System         New engine
//Author         Dave Whiteside
//Date           Mon 25 Sep 1995
//Description    There are two structures that are used a lot so here they are
//------------------------------------------------------------------------------
#ifndef	SCREENXY_Included
#define	SCREENXY_Included

#define	DEFAULT_SCREENXY 0

//------------------------------------------------------------------------------
//Author		Dave Whiteside
//Date			Mon 25 Sep 1995
//Modified	
//
//Description	
//
//Inputs		
//------------------------------------------------------------------------------
class	ScreenXY
	{
	public:
		ScreenXY::ScreenXY(SWord xx, SWord yy)
		{
			x=xx;
			y=yy;
		}

		ScreenXY::ScreenXY()
		{
			x=0;
			y=0;
		}

//DeadCode JIM 11Mar97 		ScreenXY::Set(SWord xx, SWord yy)
//DeadCode JIM 11Mar97 		{
//DeadCode JIM 11Mar97 			x=xx;
//DeadCode JIM 11Mar97 			y=yy;
//DeadCode JIM 11Mar97 		}

		ScreenXY	operator+(ScreenXY xy2)
		{
			ScreenXY rv(x+xy2.x,y+xy2.y);
			return(rv);
		}

		SWord	x;
		SWord	y;
	protected:
	private:
	};

//------------------------------------------------------------------------------
//Author		Dave Whiteside
//Date			Mon 25 Sep 1995
//Modified	
//
//Description	
//
//Inputs		
//------------------------------------------------------------------------------
class	ScreenWH
	{
	public:
		ScreenWH::ScreenWH()
		{
			w=0;
			h=0;
		}
//DeadCode JIM 15Nov95 		ScreenWH::~ScreenWH()
//DeadCode JIM 15Nov95 		{
//DeadCode JIM 15Nov95 			w=0;
//DeadCode JIM 15Nov95 			h=0;
//DeadCode JIM 15Nov95 		}
		ScreenWH::ScreenWH(SWord ww, SWord hh)
		{
			w=ww;
			h=hh;
		}
//DeadCode JIM 11Mar97 		ScreenWH::Set(SWord ww, SWord hh)
//DeadCode JIM 11Mar97 		{
//DeadCode JIM 11Mar97 			w=ww;
//DeadCode JIM 11Mar97 			h=hh;
//DeadCode JIM 11Mar97 		}

		SWord	w;
		SWord	h;
	protected:
	private:
	};


#endif
