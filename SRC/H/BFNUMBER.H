#ifndef	BFNUMBER_Included
#define	BFNUMBER_Included

#define	DEFAULT_BFNUMBER 0

#include	"bfenum.h"


inline	bool	operator == (int i,EnableComplexVal e)	{return i==(int)e;}
inline	bool	operator != (int i,EnableComplexVal e)	{return i!=(int)e;}

struct	Expr;
typedef struct	Expr	*ExprPtr;
struct	ListExpr;
struct	WorldExpr;

struct	HP
#ifdef	ANGLES_Included
{
	ANGLES H;
	ANGLES P;
	HP(){H=P=ANGLES_0Deg;}			//DAW 22Feb99
}

#endif
;
class	BOStream;
struct	EventVal
{

	int			value;		//0x80000000 means use more complex stuff below
//mutable:
	ExprPtr		complex;	//more complex expression

	CON EventVal()		{value=0x80000000;complex=NULL;}
	CON EventVal(int i)		{value=i;complex=NULL;}
	CON EventVal(ExprPtr c)	{value=0x80000000;complex=c;}
	DES ~EventVal();

	operator 	int()		{return value;}
	int operator -()		{return -value;}
	EventVal& 	operator =(int v);
	operator 	ExprPtr()	{return complex;}
	EventVal& 	operator =(ExprPtr e);

	CON			EventVal(const EventVal& e);
	EventVal& 	operator =(const EventVal& e);
	ExprPtr		operator ->()	{return complex;}
	Expr&		operator *()	{return *complex;}
	EventVal&		operator [] (int i);	//passes param to Expr to select element
	EventVal	Clone();
	Bool		operator==(EventVal& e);
//private:
//	operator	bool()	{return (Evaluate()!=ENABLE_COMPLEX_VAL);}
public:
//Evaluate functionality:
	int 	Arguments();
	int 	Evaluate(int formpos=0);
		//For integers fields: 	returns the value, or ECV for undefined
		//For UID & World:		returns any UID code found
		//For icpt & rot:		returns the diagonal length or ECV if len not stored
	UniqueID	EvalW(Coords3D& c);
		//For integers:			returns IllegalSepID as error
		//For World:			returns coordinates
		//For UID:				returns coordinates of item or UID of not loaded item
		//For icpt & rot:		returns generated deltas or UID if not loaded, or IllegalSep if no length 
	UniqueID	EvalA(HP& c);
		//For integers:			returns IllegalSepID as error
		//For World:			returns IllegalSepID as error
		//For UID:				returns UID of not loaded or IllegalSepID if static, or item's hdg,pitch
		//For icpt & rot:		returns hdg and pitch or UID of not loaded
	int&		UsesGlobRef();
//Standard structure making:
	ListExpr*	MakeRndList(int size);
	WorldExpr*	MakeRelWorldPos(UniqueID	ID1);
	WorldExpr*	MakeGRRelWorldPos(int	ID1);
	void	MakeAbsWorldPos(int y=0);
	void	MakeIcptPCWorldPos();
	void	MakeIcptIPCWorldPos(UniqueID	ID1,UniqueID	ID2);
#ifdef	NODE_Included
	void	MakeIcptGRExpr(SavedGlobrefs a,SavedGlobrefs b);
	void	MakeAngWorldPos(SavedGlobrefs a,int y);
#endif
	bool	RecalcDeltasToMatch(COORDS3D);	//returns TRUE if can do

	void	Save(FILE* f,char* fname,int tabs=0,EnumListNames e=ENUM_RealInt);
	void	Save(BOStream& f,char* fname,int tabs=0,EnumListNames e=ENUM_RealInt);
};

struct	EventVar:EventVal
{
	int	index;
	EventVar& 	operator =(const EventVar& e)
	{
		index=e.index;
		EventVal::operator=(e);
		return *this;
	}
	EventVal& 	operator =(const EventVal& e)  {return EventVal::operator=(e);}
};

enum	UsesType	{EUCT_int=0,EUCT_caller=1,EUCT_UID,EUCT_coords,EUCT_percent,EUCT_angle,EUCT_silly};
enum	InsertType	{INS_no=0,INS_yes=1,
					INS_base=0x00010000,INS_off= 0x00020000,INS_rot=0x00040000,
					INS_item=0x00100000,INS_icpt=0x00200000};
inline InsertType operator+(InsertType a,InsertType b)	{return InsertType((int)a|(int)b);}

static int minus1=-1;

class	BOStream;
struct	Expr
{
//static int highestaddr,lowestaddr,numelts,indent;
static FILE* F;
//void	printit(int indent,char name,int value);
enum	Type{EXPR_BASE,EXPR_GLOB,EXPR_UID,EXPR_RND,EXPR_SEL,EXPR_LIST,EXPR_FORM,EXPR_WORLD,EXPR_XYZ,EXPR_ROT,EXPR_ICPT}
		type;
virtual	char*		FnName()=0;
virtual	int			Arguments()=0;
virtual	int			Evaluate(int formpos=0)=0;
		//For integers fields: 	returns the value, or ECV for undefined
		//For UID & World:		returns any UID code found
		//For icpt & rot:		returns the diagonal length or ECV if len not stored
virtual	UniqueID	EvalW(Coords3D&)	{return IllegalSepID;}
		//For integers:			returns FALSE as error
		//For World:			returns coordinates
		//For UID:				returns coordinates of item or FALSE if not loaded
		//For icpt & rot:		returns generated deltas or FALSE if length not resolved
virtual	UniqueID	EvalA(HP&)			{return IllegalSepID;}
		//For integers:			returns FALSE as error
		//For World:			returns FALSE as error
		//For UID:				returns FALSE if undefined or static, or item's hdg,pitch
		//For icpt & rot:		returns hdg and pitch
virtual	void	Save(FILE* f,char* fname,int tabs=0,EnumListNames e=ENUM_RealInt)=0;
#ifndef	__BCPLUSPLUS__
virtual	void	Save(BOStream& f,char* fname,int tabs=0,EnumListNames e=ENUM_RealInt)=0;
#endif
static void	putint(int val,FILE* f);
static void	putint(int val,BOStream& f);
virtual	char*		FieldName(int)=0;
virtual	EventVal*	ArgLine(int)=0;
virtual	UsesType	UsesCallerType(int)=0;
virtual	int&		UsesGlobRef()	{return minus1;}
virtual	Bool		AddEntry(int,EventVal)	{return FALSE;}
virtual	Bool		DelEntry(int)	{return FALSE;}
virtual	InsertType	CanAddEntry(int)	{return INS_no;}
virtual	InsertType	CanDelEntry(int)	{return INS_no;}
virtual	Expr*		Clone()=0;
virtual	Bool		operator==(Expr* e)=0;
virtual	DES			~Expr()				{;}
		CON			Expr()
		{

		}


};

inline int	operator == (Expr::Type a,Expr::Type b)	{return	(int)a==(int)b;}

////////EventVal

inline	int	EventVal::Arguments()
{
		if (complex)
			return complex->Arguments();
		else
			return 0;
}

inline	EventVal&		EventVal::operator [] (int i)	{return *complex->ArgLine(i);}

inline	DES EventVal::~EventVal()	{delete complex;complex=NULL;}
inline 	EventVal& EventVal::operator =(int v)
	{
		delete complex;
		complex=NULL;
		value=v;
		return *this;
	};

inline 	EventVal& EventVal::operator =(ExprPtr e)
	{
		delete complex;
		value=0x80000000;
		complex=e;
		return *this;
	}

inline	CON	EventVal::EventVal(const EventVal& e)
	{	value=e.value;
		complex=e.complex;
		((EventVal*) &e)->complex=NULL;;
	}
inline	EventVal& EventVal::operator=(const EventVal& e)
	{
		delete complex;
		value=e.value;
		complex=e.complex;
		((EventVal*) &e)->complex=NULL;;
		return *this;
	}

inline	int 	EventVal::Evaluate(int formpos)
	{
		if (complex)
			return complex->Evaluate(formpos);
		else
			return value;
	}
inline	UniqueID	EventVal::EvalW(Coords3D& c)
	{
		if (complex)
			return complex->EvalW(c);
		else
			return IllegalSepID;
	}
inline	UniqueID	EventVal::EvalA(HP& c)
	{
		if (complex)
			return complex->EvalA(c);
		else
			return IllegalSepID;
	}

inline	EventVal	EventVal::Clone()
{
	EventVal rv=value;
	if (complex)
		rv.complex=complex->Clone();
	return rv;
}
inline	Bool		EventVal::operator==(EventVal& e)
{
 	if (e.complex && complex)
		if (e.complex->type==complex->type)
			return (*complex==e.complex);
		else
			return FALSE;
	else
		if (e.complex==complex && e.value==value)
			return TRUE;
		else
			return FALSE;


}
inline	int&		EventVal::UsesGlobRef()
{
	if (complex)
		return complex->UsesGlobRef();
	else
		return minus1;
}
////////

struct	GlobRefExpr:Expr
{
	int 		globrefind;
	CON			GlobRefExpr(int ind=-1)		{type=EXPR_GLOB;globrefind=ind;}
	DES			~GlobRefExpr()		{;}
	char*		FnName()			{return "GLOBAL REFERENCE";}
	char*		FieldName(int)		{return "";}
	int			Arguments()			{return 0;}
	EventVal*	ArgLine(int)		{return NULL;}
	UsesType	UsesCallerType(int)	{return EUCT_silly;}
	int&		UsesGlobRef() 		{return globrefind;}
	int			Evaluate(int);
	UniqueID	EvalW(Coords3D& w);
	void	Save(FILE* f,char* fname,int tabs,EnumListNames e);
	void	Save(BOStream& f,char* fname,int tabs,EnumListNames e);
	Expr*		Clone()
	{
		GlobRefExpr* rv=new	GlobRefExpr;
		rv->globrefind=globrefind;
		return rv;
	}
	Bool		operator==(Expr* f)
	{
		GlobRefExpr *e=(GlobRefExpr*)f;
		if (e->globrefind==globrefind)
			return TRUE;
		else
			return FALSE;
	}

};


struct	UIDExpr:Expr
{
	EventVal	val;

	CON			UIDExpr()			{type=EXPR_UID;}
	DES			~UIDExpr()		{;}
	char*		FnName()			{return "UID";}
	char*		FieldName(int)		{return "";}
	int			Arguments()			{return 1;}
	EventVal*	ArgLine(int)		{return &val;}
	UsesType	UsesCallerType(int)	{return EUCT_UID;}
	int			Evaluate(int i)		{return val.Evaluate(i);}
	UniqueID	EvalW(Coords3D& c);
	UniqueID	EvalA(HP& c);
	void	Save(FILE* f,char* fname,int tabs,EnumListNames e);
	void	Save(BOStream& f,char* fname,int tabs,EnumListNames e);
	Expr*		Clone()
	{
		UIDExpr* rv=new UIDExpr;
		rv->val=val.Clone();
		return rv;
	}

	Bool		operator==(Expr* f)
	{
		UIDExpr *e=(UIDExpr*)f;
		return (val==e->val);

	}
};


struct	RndExpr:Expr
{
	EventVal	base;
	EventVal	stepsize;
	EventVal	maxsteps;
	Bool		maxstepsiscallertype;

	CON			RndExpr()			{maxstepsiscallertype=TRUE;type=EXPR_RND;}
	DES			~RndExpr()			{;}

	char*		FnName()			{return "RANDOM {Base + stepsize * RND(steps)}";}
	int			Arguments()			{return 3;}
	EventVal*	ArgLine(int l)		{	switch (l)
										{
										case 0:
											return &base;
										case 1:
											return &stepsize;
										case 2:
											return &maxsteps;
										}
										return(NULL);
									}


	char*		FieldName(int l)	{	switch (l)
										{
										case 0:
											return "base val";
										case 1:
											return "step size";
										case 2:
											return "rnd(steps)";
										}
										return "";
									}

	UsesType	UsesCallerType(int l){	switch (l)
										{
										case 0:
											if (base.value==0)
												return EUCT_int;
											else
												return EUCT_caller;
										case 1:
											if (maxstepsiscallertype)
												return EUCT_int;
											else
												return EUCT_caller;
										case 2:
											if (maxstepsiscallertype)
												return EUCT_caller;
											else
												return EUCT_int;
										}
										return EUCT_silly;
									}

	int			Evaluate(int);

	void	Save(FILE* f,char* fname,int tabs,EnumListNames e);
	void	Save(BOStream& f,char* fname,int tabs,EnumListNames e);

	Expr*		Clone()
	{
		RndExpr*  rv=new RndExpr;
		rv->maxstepsiscallertype=maxstepsiscallertype;
		rv->base=base.Clone();
		rv->stepsize=stepsize.Clone();
		rv->maxsteps=maxsteps.Clone();
		return rv;
	}
	Bool		operator==(Expr* f)
	{
		RndExpr *e=(RndExpr*)f;
		return Bool
		(	
			(int)e->maxstepsiscallertype==(int)maxstepsiscallertype
		&&	e->base==base
		&&	e->stepsize==stepsize
		&&	e->maxsteps==maxsteps
		);
	}
};

struct	SelExpr:Expr
{
	EventVal	base;
	EventVal	stepsize;
	EventVal	steps;
	EventVal	div;
	Bool		stepsiscallertype;
	CON			SelExpr()			{stepsiscallertype=TRUE;type=EXPR_SEL;}
	DES			~SelExpr()		{;}
	char*		FnName()			{return "SELECT {Base + (stepsize * steps) / div }";}
	int			Arguments()			{return 4;}
	EventVal*	ArgLine(int l)		{	switch (l)
										{
										case 0:
											return &base;
										case 1:
											return &stepsize;
										case 2:
											return &steps;
										case 3:
											return &div;
										}
										return(NULL);
									}

	char*		FieldName(int l)	{	switch (l)
										{
										case 0:
											return "base val";
										case 1:
											return "step size";
										case 2:
											return "num steps";
										case 3:
											return "div fact";
										}
										return "";
									}

	UsesType	UsesCallerType(int l){	switch (l)
										{
										case 0:
											if (base.value==0)
												return EUCT_int;
											else
												return EUCT_caller;
										case 1:
											if (stepsiscallertype)
												return EUCT_int;
											else
												return EUCT_caller;
										case 2:
											if (stepsiscallertype)
												return EUCT_caller;
											else
												return EUCT_int;
										case 3:
											return EUCT_int;
										}
										return EUCT_silly;
									}

	int			Evaluate(int);

	void	Save(FILE* f,char* fname,int tabs,EnumListNames e);
	void	Save(BOStream& f,char* fname,int tabs,EnumListNames e);

	Expr*		Clone()
	{
		SelExpr*  rv=new SelExpr;
		rv->stepsiscallertype=stepsiscallertype;
		rv->base=base.Clone();
		rv->stepsize=stepsize.Clone();
		rv->steps=steps.Clone();
		return rv;
	}
	Bool		operator==(Expr* f)
	{
		SelExpr *e=(SelExpr*)f;
		return Bool
		(	
			(int)e->stepsiscallertype==(int)stepsiscallertype
		&&	e->base==base
		&&	e->stepsize==stepsize
		&&	e->steps==steps
		);
	}
};

struct ListExpr:Expr
{
	EventVal	index;
	enum	{MAXENTRIES=250};
	int			maxentries;
	int			usecallertype;
	EventVal	entries[MAXENTRIES];

	CON			ListExpr()			{maxentries=0;usecallertype=-1;type=EXPR_LIST;}
	DES			~ListExpr()		{;}

	char*		FnName()			{return "LIST {Index, Entries...}";}
	int			Arguments()			{return maxentries+1;}
	EventVal*	ArgLine(int i)		{	if (i==0)
											return &index;
										elseif (i<=maxentries)
											return (entries+i-1);
										else
											return NULL;
									}

	char*		FieldName(int l)	{
										if (l==0)
											return "index";
										else
											return "option";
									}


	UsesType	UsesCallerType(int i){	if (i==0 || i>maxentries)
											return(EUCT_int);
										else
											return (UsesType) ((usecallertype>>(i-1))&1);
									}


	InsertType	CanAddEntry(int i)	{if (i>0 && i<=maxentries+1 && maxentries<(int)MAXENTRIES)
										return INS_yes;
									 else
										return INS_no;
									}
	InsertType	CanDelEntry(int i)	{if (i>0 && i<=maxentries)
										return INS_yes;
									 else
										return INS_no;
									}

	Bool 		AddEntry(int i,EventVal e)
									{	if (CanAddEntry(i))
										{
											i--;
											for (int j=maxentries;j>i;j--)
												entries[j]=entries[j-1];
											entries[maxentries]=e;
											maxentries++;
											return TRUE;
										}
										else
											return FALSE;
									}

	Bool 		DelEntry(int i)
									{	if (CanDelEntry(i))
										{
											i--;
											delete entries[i].complex;

											for (int j=i;j<maxentries;j++)
												entries[j]=entries[j+1];
											maxentries--;
											return TRUE;
										}
										else
											return FALSE;
									}

	int			Evaluate(int)			{return entries[index.Evaluate()].Evaluate();}
	void	Save(FILE* f,char* fname,int tabs,EnumListNames e);
	void	Save(BOStream& f,char* fname,int tabs,EnumListNames e);


	Expr*		Clone()
	{
		ListExpr* rv=new ListExpr;
		rv->maxentries=maxentries;
		rv->usecallertype=usecallertype;
		rv->index=index.Clone();
		for (int i=0;i<maxentries;i++)
			rv->entries[i]=entries[i].Clone();
		return rv;
	}
	Bool		operator==(Expr* f)
	{
		ListExpr *e=(ListExpr*)f;
		if (!	(	e->maxentries==maxentries
				&&	e->usecallertype==usecallertype
				&&	e->index==index
			)	)
			return FALSE;
		for (int i=0;i<maxentries;i++)
		if (!(e->entries[i]==entries[i]))
				return FALSE;
		return TRUE;
	}
};

struct ListFormExpr:Expr
{
	enum	{MAXENTRIES=32};
	int			maxentries;
	int			usecallertype;
	EventVal	entries[MAXENTRIES];

	CON			ListFormExpr(int max=0)
		{maxentries=max;usecallertype=-1;type=EXPR_FORM;}
	DES			~ListFormExpr()		{;}

	char*		FnName()			{return "LIST {<FormPos>, Entries...}";}
	int			Arguments()			{return maxentries;}
	EventVal*	ArgLine(int i)		{	if (i<maxentries)
											return (entries+i);
										else
											return NULL;
									}

	char*		FieldName(int l)	{	return	"option";
									}


	UsesType	UsesCallerType(int i){	if (i>=maxentries)
											return(EUCT_silly);
										else
											return (UsesType) ((usecallertype>>i)&1);
									}

	InsertType	CanAddEntry(int i)	{if (i>=0 && i<=maxentries && maxentries<(int)MAXENTRIES)
										return INS_yes;
									 else
										return INS_no;
									}

	InsertType	CanDelEntry(int i)	{if (i>=0 && i<=maxentries)
										return INS_yes;
									 else
										return INS_no;
									}

	Bool 		AddEntry(int i,EventVal e)
									{	if (CanAddEntry(i))
										{
											for (int j=maxentries;j>i;j--)
												entries[j]=entries[j-1];
											entries[maxentries]=e;
											maxentries++;
											return TRUE;
										}
										else
											return FALSE;
									}

	Bool 		DelEntry(int i)
									{	if (CanDelEntry(i))
										{
											delete entries[i].complex;

											for (int j=i;j<maxentries;j++)
												entries[j]=entries[j+1];
											maxentries--;
											return TRUE;
										}
										else
											return FALSE;
									}
	int			Evaluate(int fp)	{if ((fp&15)>=maxentries)
										return entries[maxentries-1].Evaluate(fp>>4);
									else
										return entries[fp&15].Evaluate(fp>>4);}
	void	Save(FILE* f,char* fname,int tabs,EnumListNames e);
	void	Save(BOStream& f,char* fname,int tabs,EnumListNames e);

	Expr*		Clone()
	{
		ListFormExpr* rv=new ListFormExpr;
		rv->maxentries=maxentries;
		rv->usecallertype=usecallertype;
		for (int i=0;i<maxentries;i++)
			rv->entries[i]=entries[i].Clone();
		return rv;
	}
	Bool		operator==(Expr* f)
	{
		ListFormExpr* e=(ListFormExpr*)f;
		if (!	(	e->maxentries==maxentries
				&&	e->usecallertype==usecallertype
			)	)
			return FALSE;
		for (int i=0;i<maxentries;i++)
		if (!(e->entries[i]==entries[i]))
				return FALSE;
		return TRUE;
	}
};

struct	XyzExpr;
struct	WorldExpr:Expr
{
	EventVal	uniqueID;
	EventVal	delta;
	Bool		deltaisabs;
	EventVal	rotate;

	CON			WorldExpr()			{type=EXPR_WORLD;deltaisabs=FALSE;}
	DES			~WorldExpr()		{;}
	char*		FnName()			{return "COORDS";}
	int			Arguments()			{	int i=0;
										if (uniqueID.complex || uniqueID.value!=ENABLE_COMPLEX_VAL)	i++;
										if (delta.complex)	i++;
										if (rotate.complex)	i++;
										return i;
									}

	int			Evaluate(int formpos)	{return uniqueID.Evaluate();}

	UniqueID	EvalW(Coords3D& c3);

	char*		FieldName(int i)	{
										if (i==0)
											return "location";
										else
											return "offset";
									};
	EventVal*	ArgLine(int i)		{
											if (i<0)
												return NULL;
											if (uniqueID.complex || uniqueID.value!=ENABLE_COMPLEX_VAL)
												i--;
											if (i<0)
												return	&uniqueID;
											if (delta.complex)
												i--;
											if (i<0)
												return	&delta;
											if (rotate.complex)
												i--;
											if (i<0)
												return	&rotate;
											return NULL;
									};
	UsesType	UsesCallerType(int i){	if (i==0 && uniqueID.complex)
											return	EUCT_UID;
										else
											return	EUCT_coords;
									}
	void	Save(FILE* f,char* fname,int tabs,EnumListNames e);
	void	Save(BOStream& f,char* fname,int tabs,EnumListNames e);
	Expr*		Clone()
	{
		WorldExpr*	rv=new WorldExpr;
		rv->deltaisabs=deltaisabs;
		rv->uniqueID=uniqueID.Clone();
		rv->delta=delta.Clone();
		rv->rotate=rotate.Clone();
		return rv;
	}
	Bool		operator==(Expr* f)
	{
		WorldExpr* e=(WorldExpr*)f;
		if (
			(int)e->deltaisabs==(int)deltaisabs
		&&	e->uniqueID==uniqueID
		&&	e->delta==delta
		&&	e->rotate==rotate
			)
			return TRUE;
		else
			return FALSE;
	}
};

struct	XyzExpr:Expr
{
	EventVal	X;
	EventVal	Y;
	EventVal	Z;


	CON	XyzExpr()	{X=0;Y=0;Z=0;type=EXPR_XYZ;}
	DES			~XyzExpr()		{;}

	char*		FnName()			{return "POSITION {X,Y,Z}";}
	int			Arguments()			{return 3;}

	int			Evaluate(int formpos)	{return 0x80000000;};
	UniqueID	EvalW(Coords3D& c)		{		c.X=X.Evaluate();
												c.Y=Y.Evaluate();
												c.Z=Z.Evaluate();
												return UID_Null;}
	char*		FieldName(int l)		{	switch (l)
											{
											case 0:
												return "X (E-W)";
											case 1:
												return "Y (alt)";
											case 2:
												return "Z (N-S)";
											}
											return	NULL;
										}

	EventVal*	ArgLine(int l)			{	switch (l)
											{
											case 0:
												return &X;
											case 1:
												return &Y;
											case 2:
												return &Z;
											}
											return NULL;
										}

	UsesType	UsesCallerType(int)		{return EUCT_int;}



	void	Save(FILE* f,char* fname,int tabs,EnumListNames e);
	void	Save(BOStream& f,char* fname,int tabs,EnumListNames e);
	Expr*		Clone()
	{
		XyzExpr*	rv=new XyzExpr;
		rv->X=X.Clone();
		rv->Y=Y.Clone();
		rv->Z=Z.Clone();
		return rv;
	}
	Bool		operator==(Expr* f)
	{
		XyzExpr *e=(XyzExpr*)f;
		if (
			e->X==X
		&&	e->Y==Y
		&&	e->Z==Z
			)
			return TRUE;
		else
			return FALSE;
	}
};

struct	RotExpr:Expr
{
	EventVal	icpt;
	EventVal	range;
	Bool		rangeispercent;
	EventVal	hdg;
	EventVal	pitch;


	CON	RotExpr()	{type=EXPR_ROT;rangeispercent=FALSE;}
	DES			~RotExpr()		{;}

	char*		FnName()			{return "ROTATION {Hdg,Pitch,Range}";}

	int			Arguments()			{
										if (icpt.complex)
												return 4;
										else
												return 3;
									}

	int			Evaluate(int);
	UniqueID	EvalA(HP&);
	UniqueID	EvalW(Coords3D& c);

	char*		FieldName(int l)		{
											if 	(icpt.complex)
												switch (l)
												{
													case 0:
														return "use";
													case 1:
														if (range.Evaluate()==ENABLE_COMPLEX_VAL)
															return	"ignore range";
														else
															if (rangeispercent)
																return "per1000 of range";
															else
																return "range M";
													case 2:
														if (hdg.Evaluate()==ENABLE_COMPLEX_VAL)
															return	"ignore bearing";
														else
															return	"add to bearing";
													case 3:
														if (pitch.Evaluate()==ENABLE_COMPLEX_VAL)
															return	"ignore pitch";
														else
															return	"add to pitch";
												}
											else
												switch (l)
												{
													case 0:
														return "range";
													case 1:
														return "bearing";
													case 2:
														return "pitch";
												}
											return "";
										}

	EventVal*	ArgLine(int l)			{	if 	(icpt.complex)
												if (l==0)
													return &icpt;
												else
													l--;
											switch (l)
											{
												case 0:
													return &range;
												case 1:
													return &hdg;
												case 2:
													return &pitch;
											}
											return NULL;
										}


	UsesType	UsesCallerType(int l)	{	if (icpt.complex)
												if (l==0)
													return EUCT_UID;
												else l--;
											if (l==2)
												if (rangeispercent)
													return EUCT_percent;
												else
													return EUCT_int;
											else
												return EUCT_angle;
										}

	InsertType	CanAddEntry(int l)		{	if (l==0 && icpt.complex==NULL)
												return INS_item+INS_icpt;
											else
												return INS_no;
										}
	InsertType	CanDelEntry(int l)		{	if (l==0 && icpt.complex!=NULL)
												return INS_yes;
											else
												return INS_no;
										}
	Bool		AddEntry(int i,EventVal e){	if (CanAddEntry(i))
											{
												icpt=e;
												return TRUE;
											}
											else
												return FALSE;
										}

	Bool		DelEntry(int i)			{	if (CanDelEntry(i))
											{
												delete icpt.complex;
												icpt.complex=NULL;
												icpt.value=0x80000000;
												return TRUE;
											}
											else
												return FALSE;
										}

	void	Save(FILE* f,char* fname,int tabs,EnumListNames e);
	void	Save(BOStream& f,char* fname,int tabs,EnumListNames e);
	Expr*		Clone()
	{
		RotExpr*	rv=new RotExpr;
		rv->rangeispercent=rangeispercent;
		rv->icpt=icpt.Clone();
		rv->range=range.Clone();
		rv->hdg=hdg.Clone();
		rv->pitch=pitch.Clone();
		return rv;
	}
	Bool		operator==(Expr* f)
	{
		RotExpr *e=(RotExpr*)f;
		if (
			(int)e->rangeispercent==(int)rangeispercent
		&&	e->icpt==icpt
		&&	e->range==range
		&&	e->hdg==hdg
		&&	e->pitch==pitch
			)
			return TRUE;
		else
			return FALSE;
	}
};

struct	IcptExpr:Expr
{
	EventVal	objA;
	EventVal	objB;


	CON	IcptExpr()	{type=EXPR_ICPT;}
	DES			~IcptExpr()		{;}

	char*		FnName()			{return "INTERCEPT {A - B}";}
	int			Arguments()			{return 2;}

	int			Evaluate(int formpos);
	UniqueID	EvalA(HP&);
	UniqueID	EvalW(Coords3D& c);

	char*		FieldName(int l)		{	if (l==0)	return "from";
											else		return "to";
										}

	EventVal*	ArgLine(int l)			{	if (l==0)	return &objA;
											else		return &objB;
										}
	UsesType	UsesCallerType(int)		{	return	EUCT_int;}

	void	Save(FILE* f,char* fname,int tabs,EnumListNames e);
	void	Save(BOStream& f,char* fname,int tabs,EnumListNames e);
	Expr*		Clone()
	{
		IcptExpr*	rv=new IcptExpr;
		rv->objA=objA.Clone();
		rv->objB=objB.Clone();
		return rv;
	}
	Bool		operator==(Expr* f)
	{
		IcptExpr *e=(IcptExpr*)f;
		if (
			e->objA==objA
		&&	e->objB==objB
			)
			return TRUE;
		else
			return FALSE;
	}
};
//
//	Makes a fixed size list indexed by a random number.
//
//
inline ListExpr*	EventVal::MakeRndList(int size)
{
	ListExpr*	L;
	
	*this=L=new ListExpr;
	if (size>(int)ListExpr::MAXENTRIES)
		size=ListExpr::MAXENTRIES;
	RndExpr* R;
	L->index=R=new RndExpr;
	R->base=0;
	R->stepsize=1;
	R->maxsteps=size;
	L->maxentries=size;
	return L;
}
//
//	Makes a world pos relative to another item
//	Sets the delta X,Y,Z to zero
//
inline WorldExpr*	EventVal::MakeRelWorldPos(UniqueID id1)
{
	WorldExpr*	W;
	*this=W=new WorldExpr;
	W->uniqueID=id1;
	W->delta=new XyzExpr;
	return W;
}
inline WorldExpr*	EventVal::MakeGRRelWorldPos(int id1)
{
	WorldExpr*	W;
	*this=W=new WorldExpr;
	W->uniqueID=new GlobRefExpr(id1);
	W->delta=new XyzExpr;
	return W;
}

//
//	Makes a world pos relative to another item
//	Sets the X,Y,Z to zero
//
#ifdef	NODE_Included
inline void	EventVal::MakeAngWorldPos(SavedGlobrefs a,int y)
{
	WorldExpr*	W;
	*this=W=new WorldExpr;
	GlobRefExpr*	G;
	UIDExpr*		U;
	G=new GlobRefExpr;
	G->globrefind=a;
	U=new UIDExpr;
	U->val=G;
	W->uniqueID=U;

	XyzExpr*	XYZ;
	W->delta=XYZ=new XyzExpr;
	RotExpr*	R;
	W->rotate=R=new RotExpr;
	R->rangeispercent=FALSE;
	R->hdg=0;
	R->pitch=0;
	W->deltaisabs=TRUE;
	XYZ->Y=y;
}
#endif


inline void	EventVal::MakeAbsWorldPos(int y)
{
	WorldExpr*	W;
	*this=W=new WorldExpr;
	W->delta=new XyzExpr;
	this[0][0][1]=y;
}
//
//  Makes a world pos as a percent intercept between two items
//	The range is undefined
//	The hdg and pitch are set to zero
//
inline void	EventVal::MakeIcptIPCWorldPos(UniqueID	id1,UniqueID	id2)
{
	WorldExpr*	W;
	*this=W=new WorldExpr;
	W->uniqueID=id1;
	RotExpr*	R;
	W->rotate=R=new RotExpr;
	R->rangeispercent=TRUE;
	R->hdg=0;
	R->pitch=0;
	IcptExpr*	I;
	R->icpt=I=new IcptExpr;
	I->objA=id1;
	I->objB=id2;
}

inline void	EventVal::MakeIcptPCWorldPos()
{
	WorldExpr*	W;
	*this=W=new WorldExpr;
	W->uniqueID=new XyzExpr;
	RotExpr*	R;
	W->rotate=R=new RotExpr;
	R->rangeispercent=TRUE;
	R->hdg=0;
	R->pitch=0;
	IcptExpr*	I;
	R->icpt=I=new IcptExpr;
	I->objA=new XyzExpr;
	I->objB=new XyzExpr;
}

#ifdef	NODE_Included
inline	void EventVal::MakeIcptGRExpr(SavedGlobrefs a,SavedGlobrefs b)
{
	WorldExpr* W;
	*this=W=new WorldExpr;
	GlobRefExpr*	G;
	UIDExpr*		U;
	G=new GlobRefExpr;
	G->globrefind=a;
	U=new UIDExpr;
	U->val=G;
	W->uniqueID=U;
	RotExpr*	R;
	W->delta=new XyzExpr;
	W->rotate=R=new RotExpr;
	R->rangeispercent=TRUE;
	R->hdg=0;
//	R->pitch=0;
	IcptExpr*	I;
	R->icpt=I=new IcptExpr;

	G=new GlobRefExpr;
	G->globrefind=a;
	U=new UIDExpr;
	U->val=G;
	I->objA=U;
	G=new GlobRefExpr;
	G->globrefind=b;
	U=new UIDExpr;
	U->val=G;
	I->objB=U;
}
#endif	
const int TITLE_LEN = 100;
const int DESCRIPT_LEN = 255;
const  int MAXEVENTS = 80;

#ifdef	FILE_Included
struct	BfieldDesc
{
	FileNum		file;
	int			index;	//to Bfields array...
	char		title[TITLE_LEN];
	char		name[TITLE_LEN];
	char		family[TITLE_LEN];
	char		description[DESCRIPT_LEN];
	char		news[DESCRIPT_LEN];
	int			reqrefs[MAXEVENTS];
	int 		usedreqrefs;

	EventVar	defrefs[MAXEVENTS];
	int 		useddefrefs;
	int			RAC,BAC,WP,ST,RGR,BGR;

	CON	BfieldDesc()	{usedreqrefs=useddefrefs=RAC=BAC=WP=ST=RGR=BGR=0;title[0]=name[0]=description[0]=family[0]=0;}
};
#endif




#endif

