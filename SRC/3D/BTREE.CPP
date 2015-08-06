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
//Filename       btree.cpp
//System         
//Author         Paul.   
//Date           Wed 23 Aug 1995
//Description    
//------------------------------------------------------------------------------
	#include	"DOSDefs.h"
	#include	"myError.h"
	#include	"myAngles.h"
	#include	"WorldInc.h"
	#include	"AnimData.h"									//RJS 10Feb97
	#include	"world.h"
	#include	"3DDefs.h"
	#include	"matrix.h"
	#include	"btree.h"
	#include	"3DCom.h"
	#include	"3DCode.h"
	#include	"LandScap.H"									//PD 13Mar96
	#include	"Polygon.H"									//PD 13Mar96
	#include	"flymodel.H"									//RJS 07May97
#include "monotxt.h"

//#define NO_BTREE
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	btree
//LastModified:	PD 12Mar96
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 23 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
btree::btree(SLong land_tree_size,SLong item_tree_size)
{

	hdgBuffet=
		pitchBuffet=
		rollBuffet=ANGLES_0Deg;

	item_list_size = item_tree_size;
	land_list_size = land_tree_size;

	item_list_header = new Obj3DPtr[item_tree_size];			//PD 12Mar96
	land_list_header = new LandObj3DPtr[land_tree_size];		//PD 12Mar96

	int	temp;

	for(temp=item_tree_size;temp--;)
	{
		item_list_header[temp] = new Obj3D;
		item_list_header[temp]->lptr = NULL;
		item_list_header[temp]->rptr = NULL;
	}

	for(temp=land_tree_size;temp--;)
	{
		land_list_header[temp] = new LandObj3D;
		land_list_header[temp]->lptr = NULL;
		land_list_header[temp]->rptr = NULL;
	}

	start_index = NULL;

	item_list_index =
	land_list_index = 0;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	~btree
//LastModified:	PD 12Mar96
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 23 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
btree::~btree()
{
	int	temp;

	for(temp=item_list_size;temp--;)
	{
		delete item_list_header[temp];
	}

	for(temp=land_list_size;temp--;)
	{
		delete land_list_header[temp];
	}

	delete[]item_list_header;
	delete[]land_list_header;
	item_list_header=NULL;
	land_list_header=NULL;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	Get3DArea
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Thu 24 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
BaseObj3DPtr btree::Get3DArea(ObjectType objecttype)
{
	BaseObj3DPtr	new_obj3d;									//PD 12Mar96

	switch(objecttype)
	{
//DEAD		case NRGRND_TILE_OBJECT:
		case GROUND_TILE_OBJECT:
			new_obj3d = land_list_header[land_list_index++];
			if(land_list_index>land_list_size)					//PD 17Dec96
			{													//PD 17Dec96
				land_list_index--;								//PD 17Dec96
				new_obj3d = RecycleObj3D();						//PD 17Dec96
			}													//PD 17Dec96
			new_obj3d->objtype=GROUND_TILE_OBJECT;
			break;

		case SPECIAL_TILE_OBJECT:
			new_obj3d = land_list_header[land_list_index++];
			if(land_list_index>land_list_size)					//PD 17Dec96
			{													//PD 17Dec96
				land_list_index--;								//PD 17Dec96
				new_obj3d = RecycleObj3D();						//PD 17Dec96
			}													//PD 17Dec96
			new_obj3d->objtype=SPECIAL_TILE_OBJECT;
			break;

		case STATIC_OBJECT:
		case MOBILE_OBJECT:
		case SHADOW_OBJECT:										//RJS 07May97
//DeadCode DAW 18Aug99 		case SMOKE_OBJECT:										//RJS 08Sep97
		case COCKPIT_OBJECT:

			new_obj3d = item_list_header[item_list_index++];

			if(item_list_index>item_list_size)
			{													//PD 26Jul96
				item_list_index--;								//PD 26Jul96
				new_obj3d = RecycleObj3D();						//PD 26Jul96
			}													//PD 26Jul96
			break;
		case SMOKE_OBJECT:										//RJS 08Sep97
			new_obj3d = item_list_header[item_list_index++];

			if(item_list_index>item_list_size)
			{													//PD 26Jul96
				item_list_index--;								//PD 26Jul96
				new_obj3d = NULL;						//PD 26Jul96
			}	
			break;
	}
	return(new_obj3d);
}

#ifndef NO_BTREE
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	insert_object
//LastModified:	PD 12Mar96
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Thu 24 Aug 1995
//Modified	
//
//Description	Insert an object into the binary tree for drawing
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void btree::insert_object(BaseObj3DPtr new_object)				//PD 12Mar96
{
	BaseObj3DPtr	scan_index,									//PD 12Mar96
					next_index;

	Float		scan_bodyz,
				new_bodyz;

	Bool		inserted = FALSE;								//PD 12Mar96

	if(start_index == NULL)
	{
		start_index = new_object;
	}
	else
	{
		next_index = start_index;

		while(!inserted)
		{
			scan_index = next_index;
			
			scan_bodyz = scan_index->realbz.f;
			new_bodyz = new_object->realbz.f;
			
			if(scan_bodyz > new_bodyz)
			{
				if((next_index = scan_index->lptr)==NULL)
				{
					scan_index->lptr = new_object;
					inserted = TRUE;
					objcount++;									//PD 15Oct96
					if (new_bodyz>farobj)
						farobj = new_bodyz;
				}
			}
			else
			{
				if((next_index = scan_index->rptr)==NULL)
				{
					scan_index->rptr = new_object;
					inserted = TRUE;
					objcount++;									//PD 15Oct96
					if (new_bodyz>farobj)
						farobj = new_bodyz;
				}	
			}
		}
	}		
}
#else
void btree::insert_object(BaseObj3DPtr new_object)
{
	drw_obj(new_object);
}
#endif

#ifndef NO_BTREE
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	insert_object2
//LastModified:	PD 12Mar96
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Thu 24 Aug 1995
//Modified	
//
//Description	Insert an object into the binary tree for drawing
//				ensures transients get drawn first
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void btree::insert_object2(BaseObj3DPtr new_object)				//PD 12Mar96
{
	BaseObj3DPtr	scan_index,									//PD 12Mar96
					next_index;

	Obj3DPtr		o3dp = (Obj3DPtr )new_object;

	itemptr			ip = o3dp->ItemPtr;

	Float		scan_bodyz,
				new_bodyz;

	Bool		inserted = FALSE;								//PD 12Mar96

	new_bodyz = new_object->realbz.f;

	if(start_index == NULL)
	{
		start_index = new_object;
	}
	else
	{
		next_index = start_index;

		while(!inserted)
		{
			scan_index = next_index;
			
			scan_bodyz = scan_index->realbz.f;					//PD 12Mar96

			if(scan_bodyz > new_bodyz)
			{
				if((next_index = scan_index->lptr)==NULL)
				{
					scan_index->lptr = new_object;
					inserted = TRUE;
					objcount++;									//PD 15Oct96
					if (new_bodyz>farobj)
						farobj = new_bodyz;
				}
			}
			else
			{
				if((next_index = scan_index->rptr)==NULL)
				{
					scan_index->rptr = new_object;
					inserted = TRUE;
					objcount++;									//PD 15Oct96
					if (new_bodyz>farobj)
						farobj = new_bodyz;
				}	
			}
		}
	}		
}
#else
void btree::insert_object2(BaseObj3DPtr new_object)
{
	drw_obj(new_object);
}
#endif

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	draw_object
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Thu 24 Aug 1995
//Modified	
//
//Description	Scans the current binary tree and, starting with the most distant
//			object calls draw code for each one.
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void btree::draw_object(Window *screen,ViewPoint* vp)
{
	current_screen = screen;
	View_Point=vp;

	//Check to see if the binary tree is empty

	if(start_index != NULL)
	{
		recurse(start_index);	
	}
	//dead POLYGON.SelectPalette(0);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		nz_draw_object
//Author		Paul.   
//Date			Wed 28 Oct 1998
//------------------------------------------------------------------------------
void btree::nz_draw_object(Window *screen,ViewPoint* vp)
{
	current_screen = screen;
	View_Point=vp;

//DeadCode PD 30Nov98 	Bool oldState=current_screen->DoSetZUpdate(FALSE);
	bool oldState2=current_screen->DoSetMipMap(false);

	//Check to see if the binary tree is empty

	if(start_index != NULL)
	{
		nz_recurse(start_index);	
	}

//DeadCode PD 30Nov98 	current_screen->DoSetZUpdate(oldState);
	current_screen->DoSetMipMap(oldState2);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	recurse
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Thu 24 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void btree::recurse(BaseObj3DPtr next_index)					//PD 12Mar96
{
	BaseObj3DPtr scan_index;									//PD 12Mar96

	do
	{
		scan_index = next_index;

		if((next_index = scan_index->rptr)!=NULL)

			recurse(next_index);

		drw_obj(scan_index);

	}
	while((next_index = scan_index->lptr)!=NULL);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		nz_recurse
//Author		Paul.   
//Date			Wed 28 Oct 1998
//------------------------------------------------------------------------------
void btree::nz_recurse(BaseObj3DPtr next_index)					//PD 12Mar96
{
	BaseObj3DPtr scan_index;									//PD 12Mar96

	do
	{
		scan_index = next_index;

		if((next_index = scan_index->rptr)!=NULL)

			recurse(next_index);

		Bool oldState=current_screen->DoSetZUpdate(FALSE);
		drw_obj(scan_index);
		current_screen->DoFlushAll(FALSE);
		current_screen->DoSetZUpdate(oldState);
	}
	while((next_index = scan_index->lptr)!=NULL);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RecycleObj3D
//Author		R. Hyde 
//Date			Fri 26 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
BaseObj3DPtr btree::RecycleObj3D()
{
	BaseObj3DPtr scan_index,
				 prev_index;

	scan_index = start_index;

	if (scan_index->rptr==NULL)
	{
		start_index=scan_index->lptr;
		scan_index->lptr =
			scan_index->rptr = NULL;
		return (scan_index);
	}

	while (scan_index->rptr!=NULL)
	{
		prev_index=scan_index;
		scan_index=scan_index->rptr;
	}

	prev_index->rptr = scan_index->lptr;

	scan_index->lptr =
		scan_index->rptr = NULL;

	return(scan_index);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	drw_obj
//LastModified:	PD 26Feb96 - 
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Thu 24 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void btree::drw_obj(BaseObj3DPtr this_obj3d)					//PD 12Mar96
{
//	*(char*)(0xb0000+160*24+112)='A'+this_obj3d->objtype;
	switch(this_obj3d->objtype)									//PD 12Mar96
	{
		case COCKPIT_OBJECT:
//dead			POLYGON.SelectPalette(0);
			drw_cockpit(this_obj3d);
			break;

		case SHADOW_OBJECT:										//RJS 07May97
//dead			POLYGON.SelectPalette(0);
			drw_shadow(this_obj3d);								//RJS 07May97
			break;												//RJS 07May97

		case SMOKE_OBJECT:										//RJS 08Sep97
		case STATIC_OBJECT:										//RJS 08Sep97
//dead			POLYGON.SelectPalette(0);
			drw_static(this_obj3d);
			break;
		case SHADEOVERRIDE_OBJECT:
//dead			POLYGON.SelectPalette(0);
			drw_shadeoverride(this_obj3d);
			break;

		case MOBILE_OBJECT:
//dead			POLYGON.SelectPalette(0);
			drw_mobile(this_obj3d);
			break;

		case GROUND_TILE_OBJECT:
//dead			POLYGON.SelectPalette(-1);
			drw_land(this_obj3d);
			break;

		case SPECIAL_TILE_OBJECT:
			drw_special_land(this_obj3d);
			break;

		case MAP_OBJECT:										//RJS 08Sep98
//dead			POLYGON.SelectPalette(0);
			drw_map(this_obj3d);								//RJS 08Sep98
			break;												//RJS 08Sep98
	}

//	*(char*)(0xb0000+160*24+112)='Z';
}

static FPMATRIX fpmTimes4=
{
 	4.0, 0, 0,
	0, 4.0, 0,
	0, 0, 4.0
};

static FPMATRIX fpmTimes16=
{
 	16.0, 0, 0,
	0, 16.0, 0,
	0, 0, 16.0
};

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		drw_static
//Author		Paul.   
//Date			Tue 12 Mar 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void btree::drw_shadeoverride(BaseObj3DPtr this_obj3d)
{
	UByte saveR,saveG,saveB;
	UByte fR,fG,fB;
	SLong dummy;
	current_screen->DoGetFog(saveR,saveG,saveB,dummy,dummy);
	fR=Land_Scape.currentLighting.horizonAtClouds.red();
	fG=Land_Scape.currentLighting.horizonAtClouds.green();
	fB=Land_Scape.currentLighting.horizonAtClouds.blue();
	current_screen->DoGammaCorr(fR,fG,fB);
//	Land_Scape.GreyPalette(&fR,&fG,&fB);
	current_screen->DoSetFog(saveR,saveG,saveB,Land_Scape.skyFogBegin,Land_Scape.skyFogEnd);
	current_screen->DoSetFog(fR,fG,fB);
	SHAPE.fSpecialShade=true;
	drw_static(this_obj3d);
	SHAPE.fSpecialShade=false;
	current_screen->DoSetFog(saveR,saveG,saveB,Land_Scape.groundFogBegin,Land_Scape.groundFogEnd);
	current_screen->DoSetFog(saveR,saveG,saveB);
}

void btree::drw_static(BaseObj3DPtr this_obj3d)
{
	FPMATRIX	objmat;											//PD 25Jul96
	Obj3DPtr	real_obj3d = (Obj3DPtr )this_obj3d;

	FPMATRIX_PTR	fpobj_matrix = &objmat;							//PD 09Jan97

	//Just copy the normal viewer matrix

	ShapeDescPtr sdp=SHAPESTUFF.GetShapePtr(real_obj3d->Shape);
	ScaleType st=SHAPESTUFF.GetShapeScale(sdp);

	if (st==SHP_1CM)
	{
		*fpobj_matrix=*Three_Dee.fpviewer_matrix;
	}
	else
	{
		if (st==SHP_4CM)	*fpobj_matrix=fpmTimes4;
		else				*fpobj_matrix=fpmTimes16;
		_matrix.multiply(fpobj_matrix,Three_Dee.fpviewer_matrix);
	}

//DEAD	POLYGON.SetPixelWidth(1);									//PD 05Apr96

	current_screen->DoPushPull(1);
	SHAPE.process_shape(current_screen,View_Point,real_obj3d,fpobj_matrix);
	current_screen->DoPushPull(0);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		drw_cockpit
//Author		Paul.   
//Date			Fri 9 Oct 1998
//------------------------------------------------------------------------------
void btree::drw_cockpit(BaseObj3DPtr this_obj3d)
{
	FPMATRIX bmat;
	FPMATRIX omat;
	FPMATRIX _identity;
	FPMATRIX _scaledIdentity;
	FPMATRIX backupViewerMatrix;
	ClassPtr clstyp = Manual_Pilot.ControlledAC2->classtype;	//RJS 19Jan99

	_identity.L11=
	_identity.L22=
	_identity.L33=1.;
	_identity.L12=
	_identity.L13=
	_identity.L21=
	_identity.L23=
	_identity.L31=
	_identity.L32=0.;
	_scaledIdentity=_identity;
	_scaledIdentity.L11=
	_scaledIdentity.L22=
	_scaledIdentity.L33=clstyp->cockscale;

	Obj3DPtr robj3d=(Obj3DPtr )this_obj3d;

	ShapeDescPtr sdp=SHAPESTUFF.GetShapePtr(robj3d->Shape);

	ScaleType st=SHAPESTUFF.GetShapeScale(sdp);

	ANGLES pitHdg,pitPitch,pitRoll;

	pitHdg=robj3d->AngH;
	pitPitch=robj3d->AngC;
	pitRoll=robj3d->AngR;

	bool fNoBuffet=(hdgBuffet==ANGLES_0Deg &&
					pitchBuffet==ANGLES_0Deg &&
					rollBuffet==ANGLES_0Deg)?true:false;

	if (!fNoBuffet)	_matrix.Generate2(hdgBuffet,pitchBuffet,rollBuffet,clstyp->cockscale,&bmat);//RJS 19Jan99
	else			bmat=_scaledIdentity;		//RJS 13May99

	switch (st)
	{
		case SHP_1CM:
		_matrix.Generate2(pitHdg,pitPitch,pitRoll,1,&omat);
		_matrix.multiply(&bmat,&omat);
		_matrix.multiply(&bmat,Three_Dee.fpviewer_matrix);
		break;

		case SHP_4CM:
		_matrix.Generate2(pitHdg,pitPitch,pitRoll,4,&omat);
		_matrix.multiply(&bmat,&omat);
		_matrix.multiply(&bmat,Three_Dee.fpviewer_matrix);
		break;

		case SHP_16CM:
		_matrix.Generate2(pitHdg,pitPitch,pitRoll,16,&omat);
		_matrix.multiply(&bmat,&omat);
		_matrix.multiply(&bmat,Three_Dee.fpviewer_matrix);
		break;
	}

	//Scaling fix for sub-shapes
	FPMATRIX_PTR	submat = &SHAPE.subMatrix;					//DAW 07May99
	if (!fNoBuffet)	_matrix.Generate2(hdgBuffet,pitchBuffet,rollBuffet,1,submat);
	else			SHAPE.subMatrix=_identity;
	_matrix.Generate2(pitHdg,pitPitch,pitRoll,4.0,&omat);			//RJS 13May99
	_matrix.multiply(submat,&omat);
	_matrix.multiply(submat,Three_Dee.fpviewer_matrix);
	SHAPE.subMatrixP = &SHAPE.subMatrix;

//DEAD	POLYGON.SetPixelWidth(1);
	SHAPE.fPolyPitShade=true;
	SHAPE.process_shape(current_screen,View_Point,robj3d,&bmat);
	SHAPE.fPolyPitShade=false;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetHPRBuffet
//Author		Paul.   
//Date			Thu 29 Oct 1998
//------------------------------------------------------------------------------
void btree::SetHPRBuffet(ANGLES h,ANGLES p,ANGLES r)
{
	hdgBuffet=h;
	pitchBuffet=p;
	rollBuffet=r;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		drw_mobile
//Author		Paul.   
//Date			Tue 12 Mar 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void btree::drw_mobile(BaseObj3DPtr this_obj3d)
{
	FPMATRIX omat;
	FPMATRIX copymat;

	Obj3DPtr robj3d=(Obj3DPtr )this_obj3d;

	bool	fOldState,
			fIsAc=robj3d->ItemPtr && robj3d->ItemPtr->Status.size==AirStrucSize?true:false;

	if (fIsAc) fOldState=current_screen->DoSetMipMap(false);

	ShapeDescPtr sdp=SHAPESTUFF.GetShapePtr(robj3d->Shape);

	ScaleType st=SHAPESTUFF.GetShapeScale(sdp);

	switch (st)
	{
		case SHP_1CM:
		_matrix.Generate2(robj3d->AngH,robj3d->AngC,robj3d->AngR,1,&omat);
		copymat = omat;											//RJS 15Jan99
		_matrix.multiply(&omat,Three_Dee.fpviewer_matrix);
		break;

		case SHP_4CM:
		_matrix.Generate2(robj3d->AngH,robj3d->AngC,robj3d->AngR,4,&omat);
		copymat = omat;											//RJS 15Jan99
		_matrix.multiply(&omat,Three_Dee.fpviewer_matrix);
		break;

		case SHP_16CM:
		_matrix.Generate2(robj3d->AngH,robj3d->AngC,robj3d->AngR,16,&omat);
		copymat = omat;											//RJS 15Jan99
		_matrix.multiply(&omat,Three_Dee.fpviewer_matrix);
		break;
	}

//DEAD	POLYGON.SetPixelWidth(1);

	SHAPE.subMatrixP = &omat;
	SHAPE.process_shape(current_screen,View_Point,robj3d,&omat,FALSE,&copymat);//RJS 15Jan99

	if (fIsAc) current_screen->DoSetMipMap(fOldState);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		drw_shadow
//Author		Robert Slater
//Date			Wed 7 May 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void btree::drw_shadow(BaseObj3DPtr this_obj3d)
{
	FPMATRIX omat,fmat;											

	Obj3DPtr robj3d=(Obj3DPtr )this_obj3d;
	rotitem*	itm = (rotitem*)robj3d->ItemPtr;
	ANGLES		relroll,relpitch;									//RJS 20Apr99

	relpitch = itm->pitch - robj3d->AngC;
	relroll = itm->roll - robj3d->AngR;

	ShapeDescPtr sdp=SHAPESTUFF.GetShapePtr(robj3d->Shape);

	ScaleType st=SHAPESTUFF.GetShapeScale(sdp);

	_matrix.Generate2(	ANGLES_0Deg,
						relpitch,									//RJS 20Apr99
						relroll,									//RJS 20Apr99
						1,&omat);

	omat.L12=omat.L21=omat.L22=omat.L23=omat.L32=0.;

	switch (st)
	{
	case SHP_1CM:
	_matrix.Generate2(robj3d->AngH,robj3d->AngC,robj3d->AngR,1,&fmat);
	break;
	case SHP_4CM:
	_matrix.Generate2(robj3d->AngH,robj3d->AngC,robj3d->AngR,4,&fmat);
	break;
	case SHP_16CM:
	_matrix.Generate2(robj3d->AngH,robj3d->AngC,robj3d->AngR,16,&fmat);
	break;
	}

	_matrix.multiply(&omat,&fmat);
	_matrix.multiply(&omat,Three_Dee.fpviewer_matrix);

//DEAD	POLYGON.SetPixelWidth(1);

	SHAPE.subMatrixP = &omat;
	SHAPE.process_shape(current_screen,View_Point,robj3d,&omat);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		drw_land
//Author		Paul.   
//Date			Tue 12 Mar 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//DEAD void btree::drw_land(BaseObj3DPtr this_obj3d)
//DEAD{
//DEAD	LandObj3DPtr real_obj3d =
//DEAD		(LandObj3DPtr )this_obj3d;

//DEAD	Land_Scape.RenderLandPoly(real_obj3d);
//DEAD}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		drw_nrland
//Author		Paul.   
//Date			Mon 18 Mar 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
/*DEAD void btree::drw_nrland(BaseObj3DPtr this_obj3d)
{
	LandObj3DPtr real_obj3d =
		(LandObj3DPtr )this_obj3d;

}
DEAD*/

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		drw_sky
//Author		Paul.   
//Date			Tue 12 Mar 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
/*DEADvoid btree::drw_sky(BaseObj3DPtr this_obj3d)
{
	LandObj3DPtr real_obj3d =
		(LandObj3DPtr )this_obj3d;

	Land_Scape.RenderSkyPoly(real_obj3d);
}
DEAD*/

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		drw_horizon
//Author		Paul.   
//Date			Tue 12 Mar 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
/*DEADvoid btree::drw_horizon(BaseObj3DPtr this_obj3d)
{
	LandObj3DPtr real_obj3d =
		(LandObj3DPtr )this_obj3d;

}
DEAD*/

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	Clear3DArea
//LastModified:	PD 12Mar96
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Thu 24 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void btree::Clear3DArea()
{
	int	temp;

	for(temp=item_list_index;temp--;)
	{
		item_list_header[temp]->lptr = NULL;
		item_list_header[temp]->rptr = NULL;
	}

	for(temp=land_list_index;temp--;)
	{
		land_list_header[temp]->lptr = NULL;
		land_list_header[temp]->rptr = NULL;
	}

	start_index = NULL;

	item_list_index =
		land_list_index =
		farobj =
		objcount = 0;											//PD 15Oct96
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PreparePossMoveCycle
//Author		Paul.   
//Date			Tue 15 Oct 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void btree::PreparePossMoveCycle()
{
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		drw_map
//Author		Robert Slater
//Date			Tue 8 Sep 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void btree::drw_map(BaseObj3DPtr this_obj3d)
{
	FPMATRIX	objmat;											//PD 25Jul96
	Obj3DPtr	real_obj3d = (Obj3DPtr )this_obj3d;

	SWord	*src,*dst;
	int		j;

	FPMATRIX_PTR	fpobj_matrix = &objmat;							//PD 09Jan97

//DeadCode RJS 08Sep98 	//Just copy the normal viewer matrix
 	*fpobj_matrix=*Three_Dee.fpviewer_matrix;

	// Identity...												//RJS 20Oct98
	fpobj_matrix->L11 = 1;										//RJS 20Oct98
	fpobj_matrix->L12 = 0;										//RJS 20Oct98
	fpobj_matrix->L13 = 0;										//RJS 20Oct98
	fpobj_matrix->L21 = 0;										//RJS 20Oct98
	fpobj_matrix->L22 = 1;										//RJS 20Oct98
	fpobj_matrix->L23 = 0;										//RJS 20Oct98
	fpobj_matrix->L31 = 0;										//RJS 20Oct98
	fpobj_matrix->L32 = 0;										//RJS 20Oct98
	fpobj_matrix->L33 = 1;										//RJS 20Oct98

//DEAD	POLYGON.SetPixelWidth(1);									//PD 05Apr96

	SHAPE.subMatrixP = fpobj_matrix;							//DAW 07May99
	SHAPE.process_shape(current_screen,View_Point,real_obj3d,fpobj_matrix);
}

