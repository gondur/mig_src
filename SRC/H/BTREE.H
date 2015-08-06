//------------------------------------------------------------------------------
//Filename       btree.h
//System         
//Author         Paul.   
//Date           Fri 13 Oct 1995
//Description    
//------------------------------------------------------------------------------
#ifndef	BTREE_Included
#define	BTREE_Included

//#include	"display.h"											//ARM 05Aug96

typedef	struct 	Base_Obj3D 	BaseObj3D,	*BaseObj3DPtr;
typedef	struct	Land_Obj 	LandObj3D,	*LandObj3DPtr;
typedef struct	Obj_3D		Obj3D,		*Obj3DPtr;
//DEAD typedef struct	Vert_Ex	 	landvertex,	*landvertexptr;



class	ViewPoint;
class	Window;
#define	DEFAULT_BTREE 0

class	btree
		{
			Obj3DPtr		*item_list_header;					//PD 12Mar96
			LandObj3DPtr	*land_list_header;					//PD 13Mar96

			ANGLES	hdgBuffet,pitchBuffet,rollBuffet;			//PD 29Oct98

			SLong	farobj,
					objcount;									//PD 15Oct96

			BaseObj3DPtr	start_index;						//PD 12Mar96

			Window *current_screen;
			ViewPoint* View_Point;
			SWord	item_list_index,
					item_list_size,
					land_list_index,
					land_list_size;

			public:
				CON				btree(SLong, SLong );			//PD 12Mar96
				DES				~btree();						//PD 12Mar96

				BaseObj3DPtr 	Get3DArea(ObjectType);			//PD 12Mar96
				void			SetupBTree(Window* w,ViewPoint* v)
								{current_screen=w;View_Point=v;}
				void 			insert_object(BaseObj3DPtr );	//PD 12Mar96
				void 			insert_object2(BaseObj3DPtr );	//PD 11Oct96
				void			draw_object(Window *,ViewPoint* vp);			//PD 12Mar96
				void			nz_draw_object(Window *,ViewPoint* vp);			//PD 12Mar96
				void  			Clear3DArea();					//PD 12Mar96
				void			PreparePossMoveCycle();			//PD 15Oct96

				void SetHPRBuffet(ANGLES,ANGLES,ANGLES);

			private:
				void  			recurse(BaseObj3DPtr );			//PD 12Mar96
				void  			nz_recurse(BaseObj3DPtr );			//PD 12Mar96
				void  			drw_obj(BaseObj3DPtr );			//PD 12Mar96
				void			drw_static(BaseObj3DPtr );		//PD 13Mar96
				void			drw_shadeoverride(BaseObj3DPtr );		//PD 4Apr99
				void			drw_mobile(BaseObj3DPtr );		//PD 13Mar96
				void			drw_land(BaseObj3DPtr );		//PD 13Mar96
				void			drw_special_land(BaseObj3DPtr );
//DEAD				void			drw_nrland(BaseObj3DPtr );		//PD 18Mar96
//DEAD				void			drw_sky(BaseObj3DPtr );			//PD 13Mar96
//DEAD				void			drw_horizon(BaseObj3DPtr );		//PD 13Mar96
				void			drw_shadow(BaseObj3DPtr );		//RJS 07May97
				void			drw_cockpit(BaseObj3DPtr );
				BaseObj3DPtr	RecycleObj3D();					//RDH 26Jul96
				void			drw_map(BaseObj3DPtr );			//RJS 08Sep98

			protected:

		};

#endif
