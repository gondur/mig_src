//------------------------------------------------------------------------------
//Filename       makebf.h
//System         
//Author         Jim Taylor
//Date           Wed 3 Jan 1996
//Description    Communication between MakeBF.CPP and Persons.CPP
//------------------------------------------------------------------------------
#ifndef	MAKEBF_Included
#define	MAKEBF_Included
	#include	"flyinit.h"

#define	DEFAULT_MAKEBF 0

enum	UsageType
		{
			U_typename,				//just the name of the type
			U_enumequiv,			//equivalent enum name
			U_value,			//specific enum value for type
			U_structrtn,			//a routine for processing this structure
			U_punctuation
		};

enum	Defined
		{	D_dontcare=0,D_used=1,D_defined=2,D_defused=3};


enum	TokenCode
		{
			//this is the set of system types
			T_sortentry,T_unknown,	//Key to sorting system
			T_brktopen,T_brktclose,T_comma,T_equals,T_times,//punctuator
			T_question,
			T_int,T_byte,T_word,T_long,T_count,				//integer values
			T_nint,T_nbyte,T_nword,T_nlong,					//neg int
			T_include,
			T_3dsref,T_mainprog,

			//this is the set of gramar keyword types 
			T_bfsave,T_itemgrp,T_gndgrp,T_airgrp,T_route,	//groups
			T_itemS,T_itemG,T_itemA,T_waypoint,				//item groups
			T_target,T_pos,T_abs,T_rel,T_att,T_leader,		//position groups
			T_inwing,T_inform,T_damage,T_level,		//integer types
			T_skill,T_morale,T_character,
			T_x,T_y,T_z,
			T_enum,T_UIDband,T_briefID,T_nation,T_shape,	//item enums
			T_type,T_duty,T_form,T_move,T_wpact,			//mobile enums
			T_angle,T_bearing,T_asimuth,T_range,				//direction enums
			T_hdg,T_pitch,T_roll,							//direction enums
			T_fname,T_setUID,T_setval,						//force output
			T_random,T_select,T_list,						//integer control
			T_event,T_start,T_window,T_hours,T_mins,T_secs,	//Event stuff
			T_vel,T_paintscheme,
			T_attmethod,T_attpattern,T_radiosilence,						//integer control
			//this is a set of additional types generated to describe objects in
			//addition to the ones above
			T_repeat,  T_linklist,	T_everything,		//everything is in a link-list from 'everything'
			T_named, T_object, T_vertex,T_face,
			T_a, T_b, T_c, T_mtl,
			T_icpt,T_rangepc,
			T_squadron,T_home,T_follower,T_attacker,T_bombs,
			T_comment,T_name,T_family,
			T_applyac,T_applyelt,T_applyflight,T_applygroup,
			T_Last=255
		};


//------------------------------------------------------------------------------
struct	GlobalRef
	{	void* reference;
		UWord	fieldsize:5,
				fieldshift:5,
				ptrindx:5,
				spare:1;
	};

extern	GlobalRef	BFieldGlobalTable[];



#endif
