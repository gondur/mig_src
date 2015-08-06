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
//Filename       memain3.cpp
//System
//Author         Jim Taylor
//Date           Mon 6 Apr 1998
//Description    Third module for MEMAIN. This contains all the drawing stuff.
//------------------------------------------------------------------------------


#include <dos.h>
#include <direct.h>
//#include "eventwp.h"
//#include "test.h"
//#include "direct.h"
//---------------------------------------------------------------------------
#include	"sysdefs.h"
#include	<INTABLE.h>
//#include "AcItem.h"
//#include	"PreComp.h"
//#include "eventwp.h"
//#include "Route.h"
//#include "piltlist.h"
//#include "misscond.h"
//#include "missbase.h"
#include	"uniqueid.h"
#include "Waypoint.h"
//#include "MissText.h"
#include "Static.h"
#include	"stdio.h"
//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#include	<vcl\clipbrd.hpp>
//#include	"loadsave.h"
#pragma hdrstop
#include "text.h"
//#include "bstream.h"
#include	"shapenum.g"
#define F_SOUNDS

#include	"mymath.h"
#include "bfenum.h"
#include "readenum.h"

//---------------------------------------------------------------------------
#include	"files.g"
#include	"myangles.h"
#include	"bfnumber.h"
#include	"persons2.h"
#include 	"meMain.h"
#include	"monotxt2.h"



INTABLE(TMissionEditor::GridConsts);
const int FULLY=8*64*256*1024-128*1024;
const int FULLX=128*1024;

#define	wx()	WX-FULLX
//+FULLX
#define	wy()	WY*-1+FULLY


static const int 	TRUCK=999,STAFF=998,TRAIN3=997,TRAIN4=996,
                    TROOPS=995,WOOD=994,FARMYRD=993,VILLAGE=992,DEADTOWN=991,
                    FLAKBRIT=990,FLAKGERM=989,BTHBRIT=988,BTHGERM=987,
                    BBALL=986,GBALL=985,BTANK=984,GTANK=983,DHOUS1=982,
                    TRAIN1=981,TRAIN2=980,WINCH=979

                    ;
void	DEBUGEXIT()
{
	exit(1);
}
//---------------------------------------------------------------------------
struct PtPair
{
	int x,y;
};
struct	DragBox
{
    PtPair	b2;
    PtPair	b1;

    PtPair	a;
	PtPair	c;

    PtPair	bw;
    bool	linear;

}	dragline={{0x80000000,0x80000000},{0x80000000,0x80000000}};
//---------------------------------------------------------------------------
void	TMissionEditor::GetDragLine(DragOrds d,int& X,int& Y)
{
	PtPair* p;
	switch (d)
	{
		case	D_B1:	p=&dragline.b1;	break;
		case	D_B2:	p=&dragline.b2;	break;
		case	D_A:	p=&dragline.a;	break;
		case	D_C:	p=&dragline.c;	break;
		case	D_W:	p=&dragline.bw;	break;
	}
	X=p->x;
	Y=p->y;
}
//---------------------------------------------------------------------------
void	TMissionEditor::CentreOnWorld(int X,int Z)
{
	Z=FULLY-Z;
    X=X+FULLX;
	if (X<HS_Scroll.GetPos() || X>HS_Scroll.GetPos()+HS_Scroll.GetCoverage())
		HS_Scroll.SetScroll(X-HS_Scroll.GetCoverage()/2);
	if (Z<VS_Scroll.GetPos() || Z>VS_Scroll.GetPos()+VS_Scroll.GetCoverage())
		VS_Scroll.SetScroll(Z-VS_Scroll.GetCoverage()/2);
}


//---------------------------------------------------------------------------
void __fastcall TMissionEditor::PGPaint(TObject *Sender)
{
	TPaintBox* PaintBox=(TPaintBox*)Sender;
	MapBlock& block=PaintGrid[PaintBox->Tag%65536][PaintBox->Tag/65536];

	if (CouldDoBetter(block))
    {
	   	Mono_Text.PrintF("Paint %i,%i: ",PaintBox->Tag%65536,PaintBox->Tag/65536);
        int os=block.scaled+block.dirty*2;
    	RescaleArt(block);
        if (os!=block.scaled+block.dirty*2)
        {

		    TRect t=PaintBox->Canvas->ClipRect;
			if (	(t.Left!=0 && PaintBox->Left>=0)
            	||	(t.Top!=0 && PaintBox->Top>=0)
                ||	(t.Right!=256 && PaintBox->Left<=ScrollBox->ClientRect.Right-256)
                ||	(t.Bottom!=256 && PaintBox->Top<=ScrollBox->ClientRect.Bottom-256)
            	)
				{
                	block.dirty=true;
                    block.scaled=false;
                }

        }
//        os=os;
    }
	PaintBox->Canvas->Brush->Style = bsSolid;
    PaintBox->Canvas->Draw(0,0,block.backdrop);

    CurrCanvas=&block;
    MapOriginX=block.wx();
	MapOriginY=FULLY-block.WZ;


	CurrCanvas->Pen(psSolid,(TColor)0xFFFFFF,2);

   DrawStatics();

   DrawDrag(block);
}
//---------------------------------------------------------------------------
void	TMissionEditor::PaintRefresh()
{

	for (int x=0;x<REALMAXPAINT;x++)
    	for (int y=0;y<REALMAXPAINT;y++)
        	paintpos[x][y]->Invalidate();
}
//---------------------------------------------------------------------------
float	TMissionEditor::GetScaleFactor()
{	//returns multiplier from world cm to pixels
	return	cmpixscale;
//	float rv=PIXEL640;
//	rv *= ZOOMINITIAL;
//    rv /= zoom;
//	rv *= (int)CONVERTTOSCRN_DIV;
//	rv /= scrnconvert;
//	rv *= 100.0;
//    if (rv==0)
//    	return rv;
//	return rv;
}
//---------------------------------------------------------------------------
int	TMissionEditor::MulScaleFactor(int w)
{	//converts world cm value from pixels value
	return int(w*GetScaleFactor());
}
//---------------------------------------------------------------------------
int	TMissionEditor::DivScaleFactor(int p)
{	//converts pixel value from world cm value
	return int(p/GetScaleFactor());
}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::WorldPosition(int& X, int& Z)
{
	X = MulScaleFactor(X);//*PIXEL640;
	X = X + MapOriginX;
	Z = MulScaleFactor(Z);//*PIXEL640;
	Z =  MapOriginY - Z;
}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::ScreenPosition(int& mapx, int& mapy)
{
					mapx = (mapx - MapOriginX);
					mapx = DivScaleFactor(mapx);
					mapy = (MapOriginY - mapy);
					mapy = DivScaleFactor(mapy);
}
//---------------------------------------------------------------------------
bool	TMissionEditor::MapBlock::Draw(Controls::TCustomImageList* l,int x,int y,iconbitmaps index)
{
	if (x<-1024 || x>1024 || y<-1024 || y>1024)
    	return false;
	l->Draw(box->Canvas,x,y,(int)index);
    return true;
}
//---------------------------------------------------------------------------
void	TMissionEditor::MapBlock::TextOut(int x,int y,AnsiString s)
{
	if (x<-10240 || x>10240 || y<-10240 || y>10240)
    	return;
    box->Canvas->TextOut(x,y,s);
}
void	TMissionEditor::MapBlock::Pen(TPenStyle style,Graphics::TColor col,int wid)
{
    box->Canvas->Pen->Style=style;
    box->Canvas->Pen->Color=col;
    box->Canvas->Pen->Width=wid;

}
void	TMissionEditor::MapBlock::Pen(Graphics::TColor col)
{
    box->Canvas->Brush->Style=bsClear;
    box->Canvas->Pen->Color=col;
}
void	TMissionEditor::MapBlock::Font(TFontStyles style,Graphics::TColor col,int wid)
{
 	box->Canvas->Font->Style=style;
    box->Canvas->Brush->Style=bsClear;
	box->Canvas->Font->Color=col;
    box->Canvas->Font->Height=wid;
}
void	TMissionEditor::MapBlock::Font(Graphics::TColor col)
{
	box->Canvas->Font->Color=col;
}
static int lastx=0,lasty=0;
void	TMissionEditor::MapBlock::MoveTo(int x,int y)
{
	lastx=x;
    lasty=y;

}

typedef	bool intcmp(int a,int b);
bool	GT(int a,int b)
{	return (a>b);	}
bool	LT(int a,int b)
{	return (a<b);	}

bool	trimedge(int& e1,int& f1,intcmp dir,int ev,	int e2,int f2)
{
	if (dir(e1,ev))
    {
    	if (dir(e2,ev))
        	return true;
        f1=f2+double(f1-f2)*(ev-e2)/(e1-e2);
		e1=ev;
    }
    return false;
}

void	TMissionEditor::MapBlock::LineTo(int x,int y)
{	//dont draw line under dragged line
	if (	(	lastx==dragline.b1.x && lasty==dragline.b1.y
            &&	(	(x==dragline.a.x && y==dragline.a.y)
            	||	(x==dragline.c.x && y==dragline.c.y)
	   		)	)
        ||	(	x==dragline.b1.x && y==dragline.b1.y
            &&	(	(lastx==dragline.a.x && lasty==dragline.a.y)
            	||	(lastx==dragline.c.x && lasty==dragline.c.y)
		)	)	)
    {
    	lastx=x;
        lasty=y;
    }
    else
		DragLineTo(x,y);
}

void	TMissionEditor::MapBlock::DragLineTo(int x,int y)
{
	int x1=lastx,
    	y1=lasty;
    lastx=x;
    lasty=y;

	if ((ULong)x1>256 || (ULong)x>256 || (ULong)y>256 || (ULong)y1>256)
    {
		if (trimedge(x,y,LT,0,		x1,y1))    	return;
		if (trimedge(x,y,GT,256,	x1,y1))    	return;
		if (trimedge(x1,y1,LT,0,	x,y))    	return;
		if (trimedge(x1,y1,GT,256,	x,y))    	return;
		if (trimedge(y,x,LT,0,		y1,x1))    	return;
		if (trimedge(y,x,GT,256,	y1,x1))    	return;
		if (trimedge(y1,x1,LT,0,	y,x))    	return;
		if (trimedge(y1,x1,GT,256,	y,x))    	return;
    }
    box->Canvas->MoveTo(x1,y1);
    box->Canvas->LineTo(x,y);
}
void	TMissionEditor::MapBlock::Rectangle(int x,int y,int x1,int y1)
{
	if (x<0)
    	if (x1<0)
        	return;
	if (x>256)
    	if (x1>256)
        	return;

	if (y<0)
    	if (y1<0)
        	return;
	if (y>256)
    	if (y1>256)
        	return;

    box->Canvas->Rectangle(x,y,x1,y1);
}

//---------------------------------------------------------------------------
void __fastcall TMissionEditor::PBMouseDown(TObject *Sender,
	TMouseButton Button, TShiftState Shift, int X, int Y)
{
	TPaintBox* PaintBox=(TPaintBox*)Sender;
	MapBlock& block=PaintGrid[PaintBox->Tag%65536][PaintBox->Tag/65536];
    CurrCanvas=&block;
    MapOriginX=block.wx();
	MapOriginY=FULLY-block.WZ;
	ImageMouseDown(Sender,Button,Shift,X,Y);

}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::PBMouseMove(TObject *Sender, TShiftState Shift,
	int X, int Y)
{
	TPaintBox* PaintBox=(TPaintBox*)Sender;
	MapBlock& block=PaintGrid[PaintBox->Tag%65536][PaintBox->Tag/65536];
    CurrCanvas=&block;
    MapOriginX=block.wx();
	MapOriginY=FULLY-block.WZ;
	ImageMouseMove(Sender,Shift,X,Y);

}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::PBMOuseUp(TObject *Sender, TMouseButton Button,
	TShiftState Shift, int X, int Y)
{
	TPaintBox* PaintBox=(TPaintBox*)Sender;
	MapBlock& block=PaintGrid[PaintBox->Tag%65536][PaintBox->Tag/65536];
    CurrCanvas=&block;
    MapOriginX=block.wx();
	MapOriginY=FULLY-block.WZ;
	ImageMouseUp(Sender,Button,Shift,X,Y);

}
//---------------------------------------------------------------------------
extern   StaticBand   staticbands [];

Bool __fastcall TMissionEditor::OverStatic( int X, int Y,UniqueID& currUID)
{

	int	tlx=X-ICONW/2,	//The icons are centred on the world position already,
		tly=Y-ICONW/2,	//
		brx=X+ICONW/2,	//I am considering a box around the mouse to be equivalent
		bry=Y+ICONW/2;	//to a box around the icon

		WorldPosition(brx,bry);
		WorldPosition(tlx,tly);

	int	uid=currobj;
	info_base* i=*Persons2::ConvertPtrUID(UniqueID(uid));
	if (!i
		||	brx<i->World.X || bry>i->World.Z
		||	tlx>i->World.X || tly<i->World.Z)
	for(SWord b = 0; b < (int)MaxBANDNum;b++)
	{
		i=NULL;
		if (b!=WayPointBANDNum && staticbands[b].visible)
		{
			for(uid = staticbands [b].startband;
				uid < (int)staticbands [b].endband;
				uid ++)
			{
				i=*Persons2::ConvertPtrUID(UniqueID(uid));
				if (i
					&&	brx>i->World.X && bry<i->World.Z
					&&	tlx<i->World.X && tly>i->World.Z)
				{
					if (	(MissionEditor->loadedbfs[i->bfieldindex].viewable)
						&&  (SuperGroupViewable(uid))
						)

//						if (	(i->bfieldindex || canmodifymainworld)
 //							||	(displayworldtemplateitems)
  //							)
							{
								b=MaxBANDNum;
								break;
							}
				}
				i=NULL;
			}
		}
	}
	if (i)
	{
		currUID=uid;
		return(true);
	}
	else
		return(false);
}

//---------------------------------------------------------------------------
void __fastcall TMissionEditor::DrawWp()
{

	int x,z;
	int xnext,znext;
	int xprev,zprev;

	info_waypoint* W=*Persons2::ConvertPtrUID(currwp);

	x = W->World.X;
	z = W->World.Z;
	ScreenPosition(x,z);

//	if (W->target.Evaluate() != ENABLE_COMPLEX_VAL)
//	{
  //		x+=ICONW/2;
	//	z+=ICONW/2;
//	}
	CurrCanvas->Rectangle(x-ICONW/2, z-ICONW/2, x+ICONW/2, z+ICONW/2);

	UniqueID	prevwp=W->prevwp;
	UniqueID	nextwp=W->nextwp;

	while (prevwp)		//scan back for non-event waypoint to draw line from
	{
		W=*Persons2::ConvertPtrUID(prevwp);
		if (W->events)
			prevwp=W->prevwp;
		else
		{
			xprev = W->World.X;
			zprev = W->World.Z;
			ScreenPosition(xprev,zprev);
			break;
		}
	}
	if (!prevwp)
	{
		ItemBasePtr I=Persons2::ConvertPtrUID(currobj);
		xprev = I->World.X;
		zprev = I->World.Z;
		ScreenPosition(xprev,zprev);
	}
	CurrCanvas->MoveTo(xprev,zprev);
	CurrCanvas->LineTo(x,z);


	while (nextwp)				//scan forward for non-event waypoint to draw line from
	{
		W=*Persons2::ConvertPtrUID(nextwp);
		if (W->events)
			nextwp=W->nextwp;
		else
		{
			xnext = W->World.X;
			znext = W->World.Z;
			ScreenPosition(xnext,znext);
			CurrCanvas->LineTo(xnext, znext);
			break;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::DrawStaticIcon(UniqueID uid,SLong x, SLong z,ShapeNum	shape)
{
	UniqueIDBand	uidband;

	uidband = Persons2::getbandfromUID(uid);

	switch	(uidband)
	{
		case AmberAirfieldBAND:
		case RedAirfieldBAND:
		{
			CurrCanvas->Draw(MapImageList,x, z, c_afbmp);
			break;
		}
		case RedAcBAND:
		{
			CurrCanvas->Draw(MapImageList,x, z, c_arcftbmp);
 //			if ((int)uid == (int)ActiveCampaign.PlayerAcuid)
   //				DrawHiBorder(x,z);

			break;
		}
		case RedMilitaryBAND:
		{
			CurrCanvas->Draw(MapImageList,x, z, c_battbmp);
			break;
		}
		case BlueMilitaryBAND:
		{
			CurrCanvas->Draw(MapImageList,x, z, a_battbmp);
			break;
		}
		case RedCCCBAND:
		{
			CurrCanvas->Draw(MapImageList,x, z, c_hqbmp);
			break;
		}
		case BlueAirfieldBAND:
		{
			CurrCanvas->Draw(MapImageList,x, z, a_afbmp);
			break;
		}
		case BlueSAMBAND:
		{
			CurrCanvas->Draw(MapImageList,x, z, a_tankbmp);
			break;
		}
		case RedSAMBAND:
		{
			CurrCanvas->Draw(MapImageList,x, z, c_tankbmp);
			break;
		}
		case BlueArmourBAND:
		{
			if (
//            	(	((int)shape == (int)TRUCK)
  //					||	((int)shape == (int)STAFF)
	//				)
	  //				&&
					(
						(MobilesVisible&TRUCKSVISIBLE)
						||((int)uid==(int)currobj)
					)
			   )
				CurrCanvas->Draw(MapImageList,x, z, a_truckbmp);
   //			else if (	(	((int)shape == (int)TRAIN3)
	 //					  || ((int)shape == (int)TRAIN4)
	   //					 )
		 //				 &&
		   //				 (
			 //				(MobilesVisible&TRAINSVISIBLE)
			   //				||((int)uid==(int)currobj)
                 //
				   //		 )
					 //)
//				CurrCanvas->Draw(MapImageList,x, z, a_trainbmp);
//			else if (	(	((int)shape == (int)TROOPS)
  //						  || ((int)shape == (int)TROOP1)
	//					 )
	  //					 &&
        // 			(MobilesVisible&TROOPSVISIBLE)
          //       )
			//	CurrCanvas->Draw(MapImageList,x, z, a_troopbmp);
			break;
		}
		case RedArmourBAND:
		{
			if (
//            	(	((int)shape == (int)TRUCK)
  //					||	((int)shape == (int)STAFF)
	//				)
	  //				&&
					(
						(MobilesVisible&TRUCKSVISIBLE)
					)
			   )
				CurrCanvas->Draw(MapImageList,x, z, c_truckbmp);
//			else if (	(	((int)shape == (int)TRAIN3)
  //						  || ((int)shape == (int)TRAIN4)
	//					 )
	  //					 &&
		//				 (
		  //					(MobilesVisible&TRAINSVISIBLE)
            //
			  //			 )
				//	 )
//				CurrCanvas->Draw(MapImageList,x, z, c_trainbmp);
  //			else if (	(	((int)shape == (int)TROOPS)
	//					  || ((int)shape == (int)TROOP1)
	  //					 )
		//				 &&
		  //			(MobilesVisible&TROOPSVISIBLE)
            //     )
			  //	CurrCanvas->Draw(MapImageList,x, z, c_troopbmp);
			break;
		}

		case BlueAAASiteBAND:
		{
			CurrCanvas->Draw(MapImageList,x, z, a_aaabmp);
			break;
		}
		case RedAAASiteBAND:
		{
			CurrCanvas->Draw(MapImageList,x, z, c_aaabmp);
			break;
		}
		case BlueAcBAND:
		{
			CurrCanvas->Draw(MapImageList,x, z, a_arcftbmp);
//			if ((int)uid == (int)ActiveCampaign.PlayerAcuid)
  //				DrawHiBorder(x,z);
			break;
		}
		case AmberBridgeBAND:
  		{
			CurrCanvas->Draw(MapImageList,x, z, a_bridgebmp);
	  		break;
		}
		case BlueCCCBAND:
		{
			CurrCanvas->Draw(MapImageList,x, z, a_hqbmp);
			break;
		}
		case RedGICBAND:
		{
			CurrCanvas->Draw(MapImageList,x, z, c_ballbmp);
			break;
		}
		case BlueGICBAND:
		{
			CurrCanvas->Draw(MapImageList,x, z, a_ballbmp);
			break;
		}
		case AmberCivilianBAND:
 		{
  			CurrCanvas->Draw(MapImageList,x, z, settlebmp);
 			break;
 		}
		case BLuePortBAND:
		{
			CurrCanvas->Draw(MapImageList,x, z, a_splybmp);
			break;
		}
        case	AmberSupplyBAND:
		case RedPortBAND:
		{
			CurrCanvas->Draw(MapImageList,x, z, c_splybmp);
			break;
		}
		case GreenVetoedBAND:
		{
			CurrCanvas->Draw(MapImageList,x, z, hospitalbmp);
			break;
		}
		case LandscapeBAND:
		{

			ItemBasePtr i=Persons2::ConvertPtrUID(uid);
			info_itemS* j=*i;
			if (j->events)
			{
				if (LandscapeVisible&EVENTVISIBLE)
					CurrCanvas->Draw(MapImageList,x, z, Eventbmp);
			}
			else
			{
				if (LandscapeVisible&SINGLEVISIBLE)
					CurrCanvas->Draw(MapImageList,x, z, singlebmp);
            }
			break;
		}
		default:;
		case MissileBAND:
		{

//			if (
  //					   	((int)shape == (int)WOOD)
	//				  || ((int)shape == (int)FARMYRD)
	  //				  || ((int)shape == (int)VILLAGE)
		//			  || ((int)shape == (int)DEADTOWN)
		  //		)

				CurrCanvas->Draw(MapImageList,x, z, groupbmp);

			break;
		}

//		default:
  //		case RedVetoedBAND:
	//	{
//			CurrCanvas->Draw(MapImageList,x, z, groupbmp);
  //			shape=shape;	//good place to breakpoint and find out the shape...
	//		shape=shape;
//			break;
  //		}

	}
}
//---------------------------------------------------------------------------
void __fastcall TMissionEditor::DrawSettlement(UniqueID uid,SLong x, SLong y)
{
//		char buff [50];
 //		LoadString(HInstance,(int)uid,buff,sizeof(buff));
		char*	tmp =  GetList(ENUM_UIDtitle).Translate(uid);

			CurrCanvas->TextOut(x,y, tmp);

}

//---------------------------------------------------------------------------
INTABLE(ITEM_SIZE);
void	TMissionEditor::StartDragItem()
{
	int x1=0x80000000,y1=0x80000000;
    int x2=0x80000000,y2=0x80000000;
    int	x3=0x80000000,y3=0x80000000;
    int	 w=0x80000000, h=0x80000000;
    dragline.linear=false;
	if (currwp)
    {
    	info_waypoint* i=*Persons2::ConvertPtrUID(currwp);
        x2=i->World.X;
        y2=i->World.Z;
    	ItemBasePtr  n;
        if (i->nextwp)
        {
	        n=Persons2::ConvertPtrUID(i->nextwp);
	        x3=n->World.X;
    	    y3=n->World.Z;
        }
        if (i->prevwp)
        	n=Persons2::ConvertPtrUID(i->prevwp);
        else
        	n=Persons2::ConvertPtrUID(currobj);
        x1=n->World.X;
        y1=n->World.Z;
        dragline.linear=(i->events);
    }
    else
    {
   		ItemBasePtr i=*Persons2::ConvertPtrUID(currobj);
       	x2=i->World.X;
        y2=i->World.Z;
    	if (dragging==DRAGGINGLEFT)
	    {
			if (i->Status.size>=MOBILESIZE)
        	{
				info_grndgrp* t=*i;
				i=Persons2::ConvertPtrUID(t->wpref);
				x3=i->World.X;
				y3=i->World.Z;
    	    }
        }
        else
        {
        	x1=x2;	//line comes out of source...
            y1=y2;
        }
	}
    h=w=(ICONW/2)*cmpixscale;
	StartDragLine2(x1,y1,x2,y2,x3,y3,w,h);
}

void	TMissionEditor::StartDragLine1(int xa,int ya,int xb,int yb,int wb,int hb)
{
	StartDragLine2(xa,ya,xb,yb,0x80000000,0x80000000,wb,hb);
}

void	TMissionEditor::StartDragBox(int x,int y,int w,int h)
{
	StartDragLine2(0x80000000,0x80000000,x,y,0x80000000,0x80000000,w,h);
}

void	TMissionEditor::StartDragLine2(int xa,int ya,int xb,int yb,int xc,int yc,int wb,int hb)
{
    dragline.a.x=xa;
    dragline.a.y=ya;
    dragline.b1.x=xb;
    dragline.b1.y=yb;
    dragline.b2.x=xb;
    dragline.b2.y=yb;
    dragline.c.x=xc;
    dragline.c.y=yc;
    dragline.bw.x=wb;
    dragline.bw.y=hb;
    InvalidateLine(dragline.a,dragline.b1);
    InvalidateLine(dragline.c,dragline.b1);
    InvalidateBox(dragline.b1,dragline.bw);
}


void	TMissionEditor::MoveDragPix(int x,int y)
{
    WorldPosition(x,y);
    MoveDrag(x,y);
}

void	TMissionEditor::MoveDrag(int x,int y)
{
	PtPair	b2p=dragline.b2;
    dragline.b2.x=x;
    dragline.b2.y=y;
    if (dragline.linear)
    {
    	if (	Math_Lib.AbsSign(SLong(dragline.a.x-dragline.c.x))
        	>	Math_Lib.AbsSign(SLong(dragline.a.y-dragline.c.y))
            )
			dragline.b2.y=dragline.a.y+	   double(dragline.b2.x-dragline.a.x)
			            	                	*(dragline.c.y-dragline.a.y)
            			    	                /(dragline.c.x-dragline.a.x);
        else
			dragline.b2.x=dragline.a.x+	   double(dragline.b2.y-dragline.a.y)
			            	                	*(dragline.c.x-dragline.a.x)
            			    	                /(dragline.c.y-dragline.a.y);
    }
    PushScreenDrag(dragline.b2);
    InvalidateLine(dragline.a,dragline.b2);
    InvalidateLine(dragline.c,dragline.b2);
    InvalidateLine(dragline.a,b2p);
    InvalidateLine(dragline.c,b2p);
    InvalidateBox(dragline.b2,dragline.bw);
    InvalidateBox(b2p,dragline.bw);
}

PtPair	Dxy={0,0};
void	TMissionEditor::EndDrag()
{
	Dxy.x=Dxy.y=0;
	PtPair	b2p=dragline.b2;
	PtPair	b1p=dragline.b1;
//    dragline.b2.x=0x80000000;       //keep note of last position dragged to.
//    dragline.b2.y=0x80000000;
    dragline.b1.x=0x80000000;
    dragline.b1.y=0x80000000;
    InvalidateLine(dragline.a,b1p);
    InvalidateLine(dragline.c,b1p);
    InvalidateLine(dragline.a,b2p);
    InvalidateLine(dragline.c,b2p);
    InvalidateBox(b1p,dragline.bw);
    InvalidateBox(b2p,dragline.bw);
}
void	TMissionEditor::PushScreenDrag(PtPair & a)
{
	PtPair sa;
    	sa.x=((a.x-(paintpos[0][0].wx()))/cmpixscale);
    	sa.y=((FULLY-a.y-paintpos[0][0].WZ)/cmpixscale);
	Dxy.x=Dxy.y=0;
	if (sa.x<-paintpos[0][0]->Left)
		Dxy.x=cmpixscale*(sa.x+paintpos[0][0]->Left);
//    	HS_Scroll.SetScroll(HS_Scroll.GetPos()-cmpixscale);	//move left
	else
	if (sa.x>ScrollBox->ClientWidth-paintpos[0][0]->Left)
		Dxy.x=+cmpixscale*(sa.x-(ScrollBox->ClientWidth-paintpos[0][0]->Left));
//    	HS_Scroll.SetScroll(HS_Scroll.GetPos()+cmpixscale);	//move right
	if (sa.y<-paintpos[0][0]->Top)
		Dxy.y=cmpixscale*(sa.y+paintpos[0][0]->Top);
//    	VS_Scroll.SetScroll(VS_Scroll.GetPos()-cmpixscale);	//move up
	else
	if (sa.y>ScrollBox->ClientHeight-paintpos[0][0]->Top)
		Dxy.y=+cmpixscale*(sa.y-(ScrollBox->ClientHeight-paintpos[0][0]->Top));
//    	VS_Scroll.SetScroll(VS_Scroll.GetPos()+cmpixscale);	//move down

}
bool	TMissionEditor::PushDragIdle()
{
	if (Dxy.x)
        HS_Scroll.SetScroll(HS_Scroll.GetPos()+Dxy.x);
    if (Dxy.y)
        VS_Scroll.SetScroll(VS_Scroll.GetPos()+Dxy.y);
    return (Dxy.x||Dxy.y);
}


void	TMissionEditor::DrawDrag(MapBlock& block)
{
   if (dragline.b1.x!=int(0x80000000))
   {
		CurrCanvas->Pen(psSolid,(TColor)0xFF0000,1);
    	int x1,x2,x3,w,y1,y2,y3,h;
        x2=dragline.b1.x;
        y2=dragline.b1.y;
        ScreenPosition(x2,y2);

        x1=dragline.a.x;
        y1=dragline.a.y;
		if (x1!=int(0x80000000))
        {
        	ScreenPosition(x1,y1);
			block.MoveTo(x2,y2);
			block.DragLineTo(x1,y1);
        }
        x3=dragline.c.x;
        y3=dragline.c.y;
		if (x3!=int(0x80000000))
        {
	        ScreenPosition(x3,y3);
			block.MoveTo(x3,y3);
			block.DragLineTo(x2,y2);
        }
        w=dragline.bw.x;
        h=dragline.bw.y;
		if (w!=int(0x80000000))
        {
        	w/=cmpixscale;
        	h/=cmpixscale;
            block.Rectangle(x2-w,y2-h,x2+w,y2+h);
        }
		CurrCanvas->Pen(psSolid,(TColor)0x0000FF,1);
        x2=dragline.b2.x;
        y2=dragline.b2.y;
        if (x2!=int(0x80000000))
        {
	        ScreenPosition(x2,y2);
			if (x1!=int(0x80000000))
        	{
				block.MoveTo(x1,y1);
				block.DragLineTo(x2,y2);
    	    }
			if (x3!=int(0x80000000))
	        {
				block.MoveTo(x3,y3);
				block.DragLineTo(x2,y2);
	        }
			if (w!=int(0x80000000))
        	{
            	block.Rectangle(x2-w,y2-h,x2+w,y2+h);
	        }
        }
   }
}

void	TMissionEditor::InvalidateLine(PtPair & a,PtPair& b)
{
	if (a.x!=int(0x80000000) && b.x!=int(0x80000000))
    {
		PtPair sa,sb;
    	sa.x=((a.x-(paintpos[0][0].wx()))/cmpixscale);
	    sb.x=((b.x-(paintpos[0][0].wx()))/cmpixscale);
    	sa.y=((FULLY-a.y-paintpos[0][0].WZ)/cmpixscale);
	    sb.y=((FULLY-b.y-paintpos[0][0].WZ)/cmpixscale);

//DDA along this line in 8-connected steps
    //the smaller I make DDA_STEP the slower the code gets,
    //but less corners will be crossed.
    //When I cross an edge I invalidate the 1 new square.
    //When I cross a corner I invalidate all 3 neighbours.
	const int	DDA_STEP=128;
		double dx=DDA_STEP;
        double dy=DDA_STEP+DDA_STEP;
        if (sb.x!=sa.x)
        {
	        if (sb.x-sa.x<0)
    	    	dx=-dx;
        	dy=dx*(sb.y-sa.y)/(sb.x-sa.x);
        }
        if (dy<-DDA_STEP || dy>DDA_STEP)
	        if (sb.y-sa.y!=0)
    	    {   //also covers dx=0
				dy=DDA_STEP;
	        	if (sb.y-sa.y<0)
    	    		dy=-dy;
	        	dx=dy*(sb.x-sa.x)/(sb.y-sa.y);
    	    }
            else
            	dx=dy=0;
        double sx=sa.x+0.5;
        double sy=sa.y+0.5;

        int x=int(sx)>>8;
        int y=int(sy)>>8;
        if (x>=0&&x<REALMAXPAINT&&y>=0&&y<REALMAXPAINT)
        	paintpos[x][y]->Invalidate();
        while (((int(sx)^sb.x)|(int(sy)^sb.y))&-256)
        {
            if ((int(sx)^int(sx+dx))&-256)
            {
	        int x=int(sx+dx)>>8;
    	    int y=int(sy)>>8;
        	if (x>=0&&x<REALMAXPAINT&&y>=0&&y<REALMAXPAINT)
        		paintpos[x][y]->Invalidate();
                if (!(((int(sx+dx)^sb.x)|(int(sy)^sb.y))&-256))
                	break;
	            if ((int(sy)^int(sy+dy))&-256)
    	        {
			        int x=int(sx)>>8;
    			    int y=int(sy+dy)>>8;
		        	if (x>=0&&x<REALMAXPAINT&&y>=0&&y<REALMAXPAINT)
        			paintpos[x][y]->Invalidate();
            	    if (!(((int(sx)^sb.x)|(int(sy+dy)^sb.y))&-256))
                		break;
			        x=int(sx+dx)>>8;
    			    y=int(sy+dy)>>8;
		        	if (x>=0&&x<REALMAXPAINT&&y>=0&&y<REALMAXPAINT)
        			paintpos[x][y]->Invalidate();
            	    if (!(((int(sx+dx)^sb.x)|(int(sy+dy)^sb.y))&-256))
                		break;
        		}
            }
            else
            if ((int(sy)^int(sy+dy))&-256)
            {
	        int x=int(sx)>>8;
    	    int y=int(sy+dy)>>8;
        	if (x>=0&&x<REALMAXPAINT&&y>=0&&y<REALMAXPAINT)
        		paintpos[x][y]->Invalidate();
                if (!(((int(sx)^sb.x)|(int(sy+dy)^sb.y))&-256))
                	break;
            }
        	sx+=dx;sy+=dy;
        }
	}
}

void	TMissionEditor::InvalidateBox(PtPair & a,PtPair& b)
{       //box is small enough that each corner is inside a neighboring box
		//just need to check for off-screen problems...
	if (a.x!=int(0x80000000) && b.x!=int(0x80000000))
    {
		PtPair sa,sb;
    	sa.x=((a.x-(paintpos[0][0].wx()))/cmpixscale);
    	sa.y=((FULLY-a.y-paintpos[0][0].WZ)/cmpixscale);
        sb.x=b.x/cmpixscale;
        sb.y=b.y/cmpixscale;
        sa.x-=sb.x;
        sa.y-=sb.y;
        sb.x+=sb.x;
        sb.y+=sb.y;
        int x=sa.x>>8;
        int y=sa.y>>8;
        if (x>=0&&x<REALMAXPAINT&&y>=0&&y<REALMAXPAINT)
        	paintpos[x][y]->Invalidate();
        sa.x+=sb.x;
        x=sa.x>>8;
        if (x>=0&&x<REALMAXPAINT&&y>=0&&y<REALMAXPAINT)
        	paintpos[x][y]->Invalidate();
        sa.y+=sb.y;
        y=sa.y>>8;
        if (x>=0&&x<REALMAXPAINT&&y>=0&&y<REALMAXPAINT)
        	paintpos[x][y]->Invalidate();
        sa.x-=sb.x;
        x=sa.x>>8;
        if (x>=0&&x<REALMAXPAINT&&y>=0&&y<REALMAXPAINT)
        	paintpos[x][y]->Invalidate();
    }
}

