//------------------------------------------------------------------------------
//Filename       ui3dcomp.h
//System         
//Author         Jim Taylor
//Date           Fri 18 Apr 1997
//Description    UIComponent controls for 3d items.
//				This header file makes lists of INT components associated with
//				items on the map.
//
//There are 4 lists:
//	BandList:
//		Specifies a draw routine for any items in a selected UID band
//		For each specification a number of components will be created on screen
//		Each contains the actual UID for the item under that component
//		The hot area w/h is specified by the caller.
//
//  ObjectList:
//		Specifies a draw routine for a specific item selected by UID
//		The hot area w/h is specified by the caller.
//
//  LineList:
//		Specifies a line draw routine between two items selected by 2 UIDs
//		the x,y,w,h of the component define the extent of the line
//		Check xalign and yalign to find which corner of the box to start.
//		This will define the position of the first UID.
//		At this stage lines are not selectable.
//			If I wanted to make lines selectable, 
//			I would need a second list, I think, to place a hot comp at midpoint.
//
//	CircleList:
//		Specifies a circle draw routine around an item selected by UID, 
//		and the radius.
//		The component passed to the draw routine will define a bounding box 
//		for the circle. The value field contains the radius.
//		Check xalign and yalign to find where in the box is the centre.
//		Draw the relevent quarter arcs.
//		These components will never be selectable.
//
//------------------------------------------------------------------------------

#ifndef	UI3DCOMP_Included
#define	UI3DCOMP_Included

#define	DEFAULT_UI3DCOMP 0

#ifndef UI_Included
	#error	"Need to include UI.H"
#endif

#include	"UniqueID.h"
class UI3DPosLists;
extern	UI3DPosLists	*UI3D_PosLists;

class	UI3DPosLists
{
public:
	class	UI3DListArrPtr;
	class	UI3DPosComp
	{
	public:
		friend	class UI3DPosLists;
		friend	class UI3DListArrPtr;
		UniqueID		objectID;
		union
		{
			UniqueID		objectID2;
			int				radius;
		};
		SheetProc		drawrtn,drawhirtn,select,select2,hilight,dehilight;
		TextSnip0		helptext;
		ScreenWH		hitsize;
	protected:
		UI3DPosComp*	SetWH			(int w,int h)
		{	hitsize.w=w;hitsize.h=h;return this;}
		UI3DPosComp*	DrawCode		(SheetProc XX_)
		{	drawrtn=XX_;return this;}
		UI3DPosComp*	DrawHiCode		(SheetProc XX_)
		{	drawhirtn=XX_;return this;}
		UI3DPosComp*	SelectCode		(SheetProc XX_)
		{	select=XX_;return this;}
		UI3DPosComp*	Select2Code		(SheetProc XX_)
		{	select2=XX_;return this;}
		UI3DPosComp*	HilightCode		(SheetProc XX_)
		{	hilight=XX_;return this;}
		UI3DPosComp*	DeHilightCode	(SheetProc XX_)
		{	dehilight=XX_;return this;}
		UI3DPosComp*	DataVal			(UniqueID uidv,int rad)
		{	objectID=uidv;radius=rad;return this;}
		UI3DPosComp*	HelpText		(TextSnip0 t)
		{	helptext=t;return this;}
	};

	class UI3DPosCompBandList: public UI3DPosComp
	{
	public:
		UI3DPosCompBandList*	SetWH			(int w,int h)
		{		return (UI3DPosCompBandList*) UI3DPosComp::SetWH(w,h);	}
		UI3DPosCompBandList*	DrawCode		(SheetProc XX_)
		{		return (UI3DPosCompBandList*) UI3DPosComp::DrawCode(XX_);	}
		UI3DPosCompBandList*	DrawHiCode		(SheetProc XX_)
		{		return (UI3DPosCompBandList*) UI3DPosComp::DrawHiCode(XX_);	}
		UI3DPosCompBandList*	SelectCode		(SheetProc XX_)
		{		return (UI3DPosCompBandList*) UI3DPosComp::SelectCode(XX_);	}
		UI3DPosCompBandList*	Select2Code		(SheetProc XX_)
		{		return (UI3DPosCompBandList*) UI3DPosComp::Select2Code(XX_);	}
		UI3DPosCompBandList*	HilightCode		(SheetProc XX_)
		{		return (UI3DPosCompBandList*) UI3DPosComp::HilightCode(XX_);	}
		UI3DPosCompBandList*	DeHilightCode	(SheetProc XX_)
		{		return (UI3DPosCompBandList*) UI3DPosComp::DeHilightCode(XX_);	}
		UI3DPosCompBandList*	DataVal			(UniqueIDBand uidv)
		{		return (UI3DPosCompBandList*) UI3DPosComp::DataVal((UniqueID)uidv,0);	}
		UI3DPosCompBandList*	HelpText		(TextSnip0 t)
		{		return (UI3DPosCompBandList*) UI3DPosComp::HelpText(t);	}
	};

	class UI3DPosCompObjectList: public UI3DPosComp
	{
	public:
		UI3DPosCompObjectList*	SetWH			(int w,int h)
		{		return (UI3DPosCompObjectList*) UI3DPosComp::SetWH(w,h);	}
		UI3DPosCompObjectList*	DrawCode		(SheetProc XX_)
		{		return (UI3DPosCompObjectList*) UI3DPosComp::DrawCode(XX_);	}
		UI3DPosCompObjectList*	DrawHiCode		(SheetProc XX_)
		{		return (UI3DPosCompObjectList*) UI3DPosComp::DrawHiCode(XX_);	}
		UI3DPosCompObjectList*	SelectCode		(SheetProc XX_)
		{		return (UI3DPosCompObjectList*) UI3DPosComp::SelectCode(XX_);	}
		UI3DPosCompObjectList*	Select2Code		(SheetProc XX_)
		{		return (UI3DPosCompObjectList*) UI3DPosComp::Select2Code(XX_);	}
		UI3DPosCompObjectList*	HilightCode		(SheetProc XX_)
		{		return (UI3DPosCompObjectList*) UI3DPosComp::HilightCode(XX_);	}
		UI3DPosCompObjectList*	DeHilightCode	(SheetProc XX_)
		{		return (UI3DPosCompObjectList*) UI3DPosComp::DeHilightCode(XX_);	}
		UI3DPosCompObjectList*	DataVal			(UniqueID uidv)
		{		return (UI3DPosCompObjectList*) UI3DPosComp::DataVal(uidv,0);	}
		UI3DPosCompObjectList*	HelpText		(TextSnip0 t)
		{		return (UI3DPosCompObjectList*) UI3DPosComp::HelpText(t);	}
	};

	class UI3DPosCompLineList: public UI3DPosComp
	{
	public:
		UI3DPosCompLineList*	SetWH			(int w,int h)
		{		return (UI3DPosCompLineList*) UI3DPosComp::SetWH(w,h);	}
		UI3DPosCompLineList*	DrawCode		(SheetProc XX_)
		{		return (UI3DPosCompLineList*) UI3DPosComp::DrawCode(XX_);	}
		UI3DPosCompLineList*	DrawHiCode		(SheetProc XX_)
		{		return (UI3DPosCompLineList*) UI3DPosComp::DrawHiCode(XX_);	}
		UI3DPosCompLineList*	SelectCode		(SheetProc XX_)
		{		return (UI3DPosCompLineList*) UI3DPosComp::SelectCode(XX_);	}
		UI3DPosCompLineList*	Select2Code		(SheetProc XX_)
		{		return (UI3DPosCompLineList*) UI3DPosComp::Select2Code(XX_);	}
		UI3DPosCompLineList*	HilightCode		(SheetProc XX_)
		{		return (UI3DPosCompLineList*) UI3DPosComp::HilightCode(XX_);	}
		UI3DPosCompLineList*	DeHilightCode	(SheetProc XX_)
		{		return (UI3DPosCompLineList*) UI3DPosComp::DeHilightCode(XX_);	}
		UI3DPosCompLineList*	DataVal			(UniqueID uidv)
		{		return (UI3DPosCompLineList*) UI3DPosComp::DataVal(uidv,0);	}
		UI3DPosCompLineList*	HelpText		(TextSnip0 t)
		{		return (UI3DPosCompLineList*) UI3DPosComp::HelpText(t);	}
	};

	class UI3DPosCompCircleList: public UI3DPosComp
	{
	public:
		UI3DPosCompCircleList*	SetWH			(int w,int h)
		{		return (UI3DPosCompCircleList*) UI3DPosComp::SetWH(w,h);	}
		UI3DPosCompCircleList*	DrawCode		(SheetProc XX_)
		{		return (UI3DPosCompCircleList*) UI3DPosComp::DrawCode(XX_);	}
		UI3DPosCompCircleList*	DrawHiCode		(SheetProc XX_)
		{		return (UI3DPosCompCircleList*) UI3DPosComp::DrawHiCode(XX_);	}
		UI3DPosCompCircleList*	SelectCode		(SheetProc XX_)
		{		return (UI3DPosCompCircleList*) UI3DPosComp::SelectCode(XX_);	}
		UI3DPosCompCircleList*	Select2Code		(SheetProc XX_)
		{		return (UI3DPosCompCircleList*) UI3DPosComp::Select2Code(XX_);	}
		UI3DPosCompCircleList*	HilightCode		(SheetProc XX_)
		{		return (UI3DPosCompCircleList*) UI3DPosComp::HilightCode(XX_);	}
		UI3DPosCompCircleList*	DeHilightCode	(SheetProc XX_)
		{		return (UI3DPosCompCircleList*) UI3DPosComp::DeHilightCode(XX_);	}
		UI3DPosCompCircleList*	DataVal			(UniqueID uidv)
		{		return (UI3DPosCompCircleList*) UI3DPosComp::DataVal(uidv,0);	}
		UI3DPosCompCircleList*	HelpText		(TextSnip0 t)
		{		return (UI3DPosCompCircleList*) UI3DPosComp::HelpText(t);	}
	};

	struct	UI3DListArr
	{
		enum
			{MaxPerArr=	32};	//MUST BE EVEN!
		UI3DPosComp		posrec[MaxPerArr];
		UI3DListArr*	nextarr;
	};

	class	UI3DListArrPtr
	{
	public:
		UI3DListArr*	p;
		UI3DListArr* operator *		()				{return p;}
		UI3DListArr* operator ->	()				{return p;}
		UI3DListArr* operator =	(UI3DListArr*	q)	{return p=q;}
		UI3DListArr* operator =	(int i)				{assert(i==0);return p=0;}
		void	Add(const UI3DPosComp& c);
		void	Remove(UniqueID u,int r);
		CON		UI3DListArrPtr()	{p=NULL;}
	};

	class	UI3DBandListPtr:public UI3DListArrPtr
	{
		void	Remove(UniqueIDBand u)
		{	UI3DListArrPtr::Remove((UniqueID) u,0);}
		UIComponentPtr	MakeVisibleComponents(int wx,int wy,int ww,int wh,int scale);
	}	BandList;

	class	UI3DObjectListPtr:public UI3DListArrPtr
	{
		void	Remove(UniqueID u)
		{	UI3DListArrPtr::Remove( u,0);}
		UIComponentPtr	MakeVisibleComponents(int wx,int wy,int ww,int wh,int scale);
	}	ObjectList;

	class	UI3DLineListPtr:public UI3DListArrPtr
	{
		void	Remove(UniqueID u,UniqueID u2)
		{	UI3DListArrPtr::Remove( u,u2);}
		UIComponentPtr	MakeVisibleComponents(int wx,int wy,int ww,int wh,int scale);
	}	LineList;

	class	UI3DCircleListPtr:public UI3DListArrPtr
	{
		void	Remove(UniqueID u,int r)
		{	UI3DListArrPtr::Remove( u,r);}
		UIComponentPtr	MakeVisibleComponents(int wx,int wy,int ww,int wh,int scale);
	}	CircleList;

	CON	UI3DPosLists()		{UI3D_PosLists=this;}
	DES	~UI3DPosLists()	{UI3D_PosLists=NULL;}

};

#define	SETWH		->SetWH

#define	ADDMAPCOMP(listname,actions)				\
{													\
	SNIntProcD				TRANSVARd;				\					\
	SNIntProcE				TRANSVARe;				\					\
	UI3DPosComp##listname	tempinst;				\
	tempinst.SetWH(10*PIXEL640,10*PIXEL640)			\
		actions;									\
	UI3D_PosLists. listname .Add(tempinst);		\
}

#define	REMOVEMAPCOMP(listname,paramsinbrackets)	\
	UI3D_PosLists. listname .Remove paramsinbrackets






#endif
