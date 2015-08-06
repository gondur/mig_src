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

//
// Basic expression evaluator code...
// Used in both game and mission editor
//
//
//
//
// 
#include	"dosdefs.h"
#include	"uniqueid.h"
#include	"text.h"
#include	"mymath.h"
#include	"persons2.h"
#include	"bfnumber.h"

int			GlobRefExpr::Evaluate(int)	//formpos is irrelevent	
{return Persons2::GetLoc(globrefind);}

UniqueID	GlobRefExpr::EvalW(Coords3D& w)
{
	int uid=Persons2::GetLoc(globrefind);
	if (uid<=0 || uid>int(IllegalSepID))
		return IllegalSepID;
	ItemBasePtr p=Persons2::ConvertPtrUID(UniqueID(uid));
	if (!p)
		return UniqueID(uid);
	w=p->World;
	return	UID_Null;

}


UniqueID		UIDExpr::EvalW(Coords3D& c)
{	ItemBasePtr p=Persons2::ConvertPtrUID(UniqueID(val.Evaluate(0)));
	if (!p)
		return	UniqueID(val.Evaluate(0));	//target object not loaded yet!
	else
	{
		if (p->World.Y&0x40000000)			//target object's coords not set yet!
			return UniqueID(val.Evaluate(0));	
		c=p->World;
		if (p->Status.size==WAYPOINTSIZE)
		{	//It may be a target relative waypoint!!!
			WayPoint* w=*p;
			if ((int)w->next!=-1 && w->target)
			{
				if ((int)w->target==-1)			//outstanding warrant...
					return UniqueID(val.Evaluate(0));
				c.X+=w->target->World.X;
				c.Y+=w->target->World.Y;
				c.Z+=w->target->World.Z;
			}
		}
		return UID_Null;
	}
}
UniqueID		UIDExpr::EvalA(HP& c)
{	ItemBasePtr p=Persons2::ConvertPtrUID(UniqueID(val.Evaluate(0)));
	if (p && p->Status.size>=HPSIZE)
	{
		hpitem* q=*p;
		c.H=q->hdg;
		c.P=q->pitch;
		return UID_Null;
	}
	return UniqueID(val.Evaluate(0));
}


UniqueID		RotExpr::EvalA(HP& c)
{
	if (icpt.complex)
	{
		HP a;
		UniqueID t=icpt.EvalA(a);
		if (t)	RETURN(t);
		int v1;
		if ((v1=hdg.Evaluate())!=ENABLE_COMPLEX_VAL)
			c.H=Angles(v1)+a.H;
		if ((v1=pitch.Evaluate())!=ENABLE_COMPLEX_VAL)
			c.P=Angles(v1)+a.P;
	}
	else
	{
		int v1;
		if ((v1=hdg.Evaluate())!=ENABLE_COMPLEX_VAL)
			c.H=Angles(v1);
		if ((v1=pitch.Evaluate())!=ENABLE_COMPLEX_VAL)
			c.P=Angles(v1);
	}
	return UID_Null;
}


UniqueID	RotExpr::EvalW(Coords3D& p)
{
	HP a;//={ANGLES_0Deg,ANGLES_0Deg};
	UniqueID	rv=EvalA(a);
	if (rv)
		RETURN(rv);
	int r=range.Evaluate();
	if (r!=ENABLE_COMPLEX_VAL)
	{
		if (rangeispercent)
		{
			int l=icpt.Evaluate();
			if ((r&0x80000000) && !(r&0x40000000))	//bit 30 is toggled
			{	//r is actually a fixed point number where 65536=1
				r<<=2;
				if (l==ENABLE_COMPLEX_VAL)							  //JIM 08/04/99
					return IllegalSepID;		//THIS CAN'T HAPPEN (I hope)!!!
				else
					r=MULSHSIN(l,r,18);
			}
			else
			{
				if (l==ENABLE_COMPLEX_VAL)							  //JIM 08/04/99
					return IllegalSepID;		//THIS CAN'T HAPPEN (I hope)!!!
				else
				{
//					INT3;
					r=MULDIVSIN(l,r,100);							  //JIM 08/04/99
//					INT3;
				}
			}
		}
		SWord	s,c;
		Math_Lib.high_sin_cos(a.P,s,c);
		int l=MULSHSIN(r,c,ANGLES_SHIFT);
		p.Y=MULSHSIN(r,s,ANGLES_SHIFT);
		Math_Lib.high_sin_cos(a.H,s,c);
		p.X=MULSHSIN(l,s,ANGLES_SHIFT);
		p.Z=MULSHSIN(l,c,ANGLES_SHIFT);
		return UID_Null;
	}
	else
		return IllegalSepID;
}

int		RotExpr::Evaluate(int)
{
	int r=range.Evaluate();
	if (r!=ENABLE_COMPLEX_VAL)
		if (rangeispercent)
		{
			int l=icpt.Evaluate();
			if (l==ENABLE_COMPLEX_VAL)
				return l;
			else
				if ((r&0x80000000) && !(r&0x40000000))	//bit 30 is toggled
					return MULSHSIN(r<<2,l,18);
				else
					return MULDIVSIN(l,r,100);							  //JIM 08/04/99
		}
	return r;
}


UniqueID	IcptExpr::EvalW(Coords3D& c)
{
	Coords3D a,b;
	UniqueID	rv;
	if (objA.complex)
	{
		if (UID_NULL!=(rv=objA.EvalW(a)))
			return (rv);
	}
	else
	{
		UIDExpr u;
		u.val=objA.value;
		if (UID_NULL!=(rv=u.EvalW(a)))
			return rv;
	}

	if (objB.complex)
	{
		if (UID_NULL!=(rv=objB.EvalW(b)))
			return (rv);
	}
	else
	{
		UIDExpr u;
		u.val=objB.value;
		if (UID_NULL!=(rv=u.EvalW(b)))
			return rv;
	}
	c.X=b.X-a.X;
	c.Y=b.Y-a.Y;
	c.Z=b.Z-a.Z;
	return UID_Null;
}

UniqueID		IcptExpr::EvalA(HP& a)
{
	Coords3D d;
	UniqueID rv;
	if (UID_NULL==(rv=EvalW(d)))
	{
		long	range;
		Math_Lib.HighIntercept(d.X,d.Y,d.Z,range,a.H,a.P);

		return UID_Null;
	}
	else
		return rv;

}

int		IcptExpr::Evaluate(int)
{
	Coords3D d;
	if (!EvalW(d))
	{
		HP	a;
		long	range;
		Math_Lib.Intercept(d.X,d.Y,d.Z,range,a.H,a.P);
//		Math_Lib.HighIntercept(d.X,d.Y,d.Z,range,a.H,a.P);
		return range;
	}
	else
		return ENABLE_COMPLEX_VAL;
}

int			RndExpr::Evaluate(int)
{
	int b=base.Evaluate(0);
	if (b==ENABLE_COMPLEX_VAL)
		b=0;
	int s=stepsize.Evaluate(0);
	if (s==ENABLE_COMPLEX_VAL)
		s=1;
	int m=maxsteps.Evaluate(0);
	if (m==ENABLE_COMPLEX_VAL)
		m=1;
	return b+s*Math_Lib.rnd(m);
}
int			SelExpr::Evaluate(int)
{
	int b=base.Evaluate(0);
	if (b==ENABLE_COMPLEX_VAL)
		b=0;
	int s=stepsize.Evaluate(0);
	int m=steps.Evaluate(0);
	int d=div.Evaluate(0);
	if (s==ENABLE_COMPLEX_VAL)
		if (m==ENABLE_COMPLEX_VAL)
			s=0;
		else
			s=1;
	else
	if (m==ENABLE_COMPLEX_VAL)
		m=1;
	if (d==ENABLE_COMPLEX_VAL || d==0)
		d=1;
	return b+s*m/d;
}


static Coords3D* test=NULL;
UniqueID		WorldExpr::EvalW(Coords3D& c3)	//return code is error 
{												//UID refers to item not loaded
#ifndef __BCPLUSPLUS__
	if (&c3==test)
		INT3;
#endif
	Coords3D	a={0,0,0},b=a,c=b;c3=a;
	UniqueID rv=UID_Null;
	if (uniqueID.complex)
		rv=uniqueID.complex->EvalW(a);
	else if (uniqueID.value!=ENABLE_COMPLEX_VAL)
	{
		UIDExpr u;
		u.val=uniqueID;
		rv=u.EvalW(a);
	}
	if (rv)
		return (rv);

	if (deltaisabs && delta.complex && delta.complex->type==EXPR_XYZ)
	{
		XyzExpr* d=(XyzExpr*)delta.complex;
		int v;
		if ((v=d->X.Evaluate())!=ENABLE_COMPLEX_VAL)
			if (v!=0)
			a.X=v;
		if ((v=d->Y.Evaluate())!=ENABLE_COMPLEX_VAL)
			if (v!=0)
			a.Y=v;
		if ((v=d->Z.Evaluate())!=ENABLE_COMPLEX_VAL)
			if (v!=0)
			a.Z=v;
	}
	else
		delta.EvalW(b);
	if (rotate.complex)
		rv=rotate.EvalW(c);
	if (rv)
		return rv;
	c3.X=a.X+b.X+c.X;
	c3.Y=a.Y+b.Y+c.Y;
	c3.Z=a.Z+b.Z+c.Z;

	return UID_Null;
}

//////////////////////////////////////////////////////////////////////
//
// Function:    RecalcDeltasToMatch
// Date:		08/04/99
// Author:		JIM
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
bool	EventVal::RecalcDeltasToMatch(COORDS3D c)
{
	if (!complex || complex->type!=complex->EXPR_WORLD)
		return FALSE;
	WorldExpr* w=(WorldExpr*) complex;
	int deltay=0;
	if (w->uniqueID.complex)
	{
		COORDS3D base;
		w->uniqueID.EvalW(base);
		c.X-=base.X;
		deltay=-base.Y;
		c.Z-=base.Z;
	}
	XyzExpr* xyz=(XyzExpr*)w->delta.complex;
	RotExpr* rot=(RotExpr*)w->rotate.complex;
	if (rot)
	{
		HP baseang;
		int baserange=-1;
		if (rot->icpt.complex)
		{
			rot->icpt.EvalA(baseang);
			if (rot->rangeispercent)
				baserange=rot->icpt.Evaluate(0);
		}
		if (xyz &&	(	(xyz->Y.Evaluate(0) && xyz->Y.Evaluate(0)!=GOT_UNDEFINED_VAL)
					||	(!rot || rot->pitch.Evaluate(0)==GOT_UNDEFINED_VAL)
			)		)
		{
			if (!w->deltaisabs)
				c.Y+=deltay;
			xyz->Y=c.Y;
			c.Y=0;
		}
		SLong range;
		ANGLES h,p;
		if (rot->pitch.Evaluate(0)==GOT_UNDEFINED_VAL)
			Math_Lib.HighIntercept (c.X,0,c.Z,		range,h,p);
		else
			Math_Lib.HighIntercept (c.X,c.Y,c.Z,	range,h,p);
		if (!baserange)
			range=50;	//if endpoints in same place then put at 50%
		else
			if (baserange!=-1)
				if (range/baserange>=0x2000)		  //8200 times - if output is 800km, input is 100m
					range=MULDIVSIN(range,100,baserange);
				else
					range=(SHDIVSIN(range,16,baserange)&0x3fffffff)|0x80000000;
			//else use range as absolute
		h-=baseang.H;
		p-=baseang.P;
		rot->range=range;
		rot->hdg=h;

		if (rot->pitch.Evaluate(0)!=GOT_UNDEFINED_VAL)
			if (xyz	&& xyz->Y.Evaluate(0) && xyz->Y.Evaluate(0)!=GOT_UNDEFINED_VAL)
				rot->pitch=0;
			else
				rot->pitch=p;
	}
	else
	if (xyz)
	{	//modify x,y,z fields to match requirement
		xyz->X=c.X;
		xyz->Y=c.Y+deltay;
		xyz->Z=c.Z;
	}
	else
		return FALSE;

	return TRUE;
}

