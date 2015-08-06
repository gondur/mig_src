//
// converts between Save game and combo fields
//
//
// Redefines and reuses the macro OPTIONS to say what the list of options will do
// OPTIONS is a list of SETFIELD(whatbit, combo,strings,	 level)
// The first and last SETFIELDs are specials to drive a master level control field
// If a variable 
//
//		whatbit is a macro which defines where the value is stored. Save_Data is implied:
//			BIT(fieldname,enumname)					//1 bit flag
//			ADDBIT(fieldname,enum1,enum2)			//2 flags = 4 states: 0=off, 1=e1, 2=e2, 3=both
//			CHAR(fieldname,base,multiplier)			//numeric field. Combo is multiplied and base added
//			LOCAL(name)								//a local variable counting from 0
//			MASTER
//		combo is the combo box resource ID
//		strings is a macro defining the list of strings is can be:
//			RESCOMBO(firstID,count)					//IDS_L_ is prepended to firstID
//			NumList(steps,base,stepsize)			//default base=0,stepsize=1
//		level is a macro relating this field to the general level control field:
//			LEVELS(l0,l1,l2,l3,l4)					//values for each level
//			NOTLEVELS								//not effected by levels 
//		level is also used to introduce first and last line in list
//			PRESETLEVEL					//field for level control	//must be first in list - both!
//			POSTSETLEVEL(customlevel)	//field for level control	//must be last in list - both!
//
// The OPTIONS macro is redefined in 4 different ways:
// #define SG2C_DISPLAY		levelfield	
	//Fill the display with Save_Date values and set level field during	OnInitDialog
// #define SG2C_WRITEBACK
	//Read the display into the Save_Data values during OnDestroy
// 
// #define SG2C_CHANGELEVEL	levelfield
	//Level combo caption changed message - redo display for others in OnClickedAll
// #define SG2C_CHANGEFIELD	customnum			
	//Other field changed. Change Level combo to custom in OnClickedanyother
//
// In addition, preceed and finish with 
//	#define SG2C_CLEANUP
//
//

#ifdef	SG2C_CLEANUP
#undef	SG2C_CLEANUP
#undef	SG2C_WRITEBACK
#undef	SG2C_DISPLAY
#undef	SG2C_CHANGELEVEL
#undef	SG2C_CHANGEFIELD
#undef	OPTIONS
#undef	BIT
#undef  ADDBIT
#undef	CHAR
#undef	TYPE
#undef  LOCAL
#undef  SETFIELD
#undef  PRESETLEVEL
#undef	LEVELS
#undef	NOLEVEL
#undef	POSTSETLEVEL
#undef	MASTER1
#undef	MASTER2
#endif

#ifdef SG2C_WRITEBACK
#undef SG2C_DISPLAY
#endif
#ifdef SG2C_CHANGELEVEL
#undef SG2C_DISPLAY
#endif
#ifdef SG2C_CHANGEFIELD
#undef SG2C_DISPLAY
#endif

//////////////////////////////////////////////////////////////////////////
#ifdef SG2C_DISPLAY

#undef	BIT
#undef  ADDBIT
#undef	CHAR
#undef	TYPE
#undef  LOCAL
#undef  SETFIELD
#undef  PRESETLEVEL
#undef	LEVELS
#undef	NOLEVEL
#undef	POSTSETLEVEL
#undef	MASTER1
#undef	MASTER2

#define BIT(fieldname,enumname)		val=(int)Save_Data.fieldname[enumname];
#define ADDBIT(field,enum1,enum2)	val=(int)Save_Data.field[enum1]+2*(int)Save_Data.field[enum2];
#define CHAR(fieldname,base,mul)	val=(int)(Save_Data.fieldname-base)/mul;
#define TYPE(fieldname,type)		val=(int)(Save_Data.fieldname);
#define LOCAL(name)					val=(int)name;
#define PRESETLEVEL(x)	}int SG2C_DISPLAY=0;{ int val=x;
#define LEVELS(l0,l1,l2,l3,l4)				   \
		if	(val!=l0)	SG2C_DISPLAY|=1;		\
		if	(val!=l1)	SG2C_DISPLAY|=2;		 \
		if	(val!=l2)	SG2C_DISPLAY|=4;		  \
		if	(val!=l3)	SG2C_DISPLAY|=8;		   \
		if	(val!=l4)	SG2C_DISPLAY|=16;

#define	NOLEVEL						  //SetCircularStyle(TRUE);
#define DISABLEDINCOMMS
#define MASTER1
#define MASTER2

#define POSTSETLEVEL(custnum)	   \
	val=custnum;					\
	if (!(SG2C_DISPLAY&1))	val=0;	 \
	if (!(SG2C_DISPLAY&2))	val=1;	  \
	if (!(SG2C_DISPLAY&4))	val=2;	   \
	if (!(SG2C_DISPLAY&8))	val=3;		\
	if (!(SG2C_DISPLAY&16))	val=4;		 

#define SETFIELD(whatbit,whatcombo,whatstring,level)\
{\
	int val;\
	whatbit;\
	level;\
	CRCombo* rcombo=GetDlgItem(whatcombo);\
	rcombo->whatstring;\
	rcombo->SetIndex(val);\
}\


#endif
////////////////////////////////////////////////////////////////////////////
#ifdef SG2C_WRITEBACK

#undef	BIT
#undef  ADDBIT
#undef	CHAR
#undef	TYPE
#undef  LOCAL
#undef  SETFIELD
#undef  PRESETLEVEL
#undef	LEVELS
#undef	NOLEVEL
#undef	POSTSETLEVEL
#undef	MASTER1
#undef	MASTER2
#define MASTER1
#define MASTER2

#define BIT(fieldname,enumname)		if (val) Save_Data.fieldname|=enumname;else Save_Data.fieldname%=enumname;
#define ADDBIT(field,enum1,enum2)												\
	{	if (val&1) Save_Data.field|=enum1;else Save_Data.field%=enum1;	 \
		if (val&2) Save_Data.field|=enum2;else Save_Data.field%=enum2;	  \
	}

#define CHAR(fieldname,base,mul)	Save_Data.fieldname=val*mul+base;
#define TYPE(fieldname,type)		Save_Data.fieldname=type(val);
#define LOCAL(name)					name=val;
#define SETFIELD(whatbit,whatcombo,whatstring,level)\
{\
	int val;\
	CRCombo* rcombo=GetDlgItem(whatcombo);\
	val=rcombo->GetIndex();\
	whatbit;\
}

#undef SG2C_DISPLAY
#undef SG2C_WRITEBACK
#undef SG2C_CHANGELEVEL
#undef SG2C_CHANGEFIELD
#endif

////////////////////////////////////////////////////////////////////////////
#ifdef SG2C_CHANGELEVEL


#undef	BIT
#undef  ADDBIT
#undef	CHAR
#undef	TYPE
#undef  LOCAL
#undef  SETFIELD
#undef  PRESETLEVEL
#undef	LEVELS
#undef	NOLEVEL
#undef	POSTSETLEVEL
#undef	MASTER1
#undef	MASTER2

#define PRESETLEVEL(custlevel)			\
	if (rcombo->GetIndex()!=custlevel)		\
		SG2C_CHANGELEVEL=rcombo->GetIndex();	 \

#define BIT(a,b)
#define	ADDBIT(a,b,c)
#define CHAR(a,b,c)
#define	TYPE(a,b)
#define LOCAL()
#define MASTER1		int SG2C_CHANGELEVEL=-1;
#define MASTER2
#define POSTSETLEVEL(x)


#define	LEVELS(l0,l1,l2,l3,l4)							  \
	if		(SG2C_CHANGELEVEL==0)		rcombo->SetIndex(l0);\
	elseif	(SG2C_CHANGELEVEL==1)		rcombo->SetIndex(l1); \
	elseif	(SG2C_CHANGELEVEL==2)		rcombo->SetIndex(l2);  \
	elseif	(SG2C_CHANGELEVEL==3)		rcombo->SetIndex(l3);	\
	elseif	(SG2C_CHANGELEVEL==4)		rcombo->SetIndex(l4);	 \

#define SETFIELD(whatbit,whatcombo,whatstring,level)	\
whatbit													 \
{														  \
	CRCombo* rcombo=GetDlgItem(whatcombo); 				   \
	level													\
}												


#undef SG2C_DISPLAY
#undef SG2C_WRITEBACK
#undef SG2C_CHANGELEVEL
#undef SG2C_CHANGEFIELD
#endif
////////////////////////////////////////////////////////////////////////////
#ifdef SG2C_CHANGEFIELD
#undef	BIT
#undef  ADDBIT
#undef	CHAR
#undef	TYPE
#undef  LOCAL
#undef  SETFIELD
#undef  PRESETLEVEL
#undef	LEVELS
#undef	NOLEVEL
#undef	POSTSETLEVELS
#undef	MASTER1
#undef	MASTER2

#define SETFIELD(whatbit,whatcombo,whatstring,level) \
{													  \
	CRCombo* rcombo=GetDlgItem(whatcombo);			   \
	level												\
}

#define	POSTSETLEVEL(custind)
#define	NOLEVEL
#define LEVELS(a,b,c,d,e)

#define	PRESETLEVEL(custind)	rcombo->SetIndex(custind);

#undef SG2C_DISPLAY
#undef SG2C_WRITEBACK
#undef SG2C_CHANGELEVEL
#undef SG2C_CHANGEFIELD
#endif
////////////////////////////////////////////////////////////////////////////
