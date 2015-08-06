//------------------------------------------------------------------------------
//Filename       sheettop.h
//System         
//Author         Jim Taylor
//Date           Fri 17 Nov 1995
//Description    Defines the top of a sheet 
//				 Assumes that SHEETNAME has been defined
//
//				This header creates 'secret' classes for the UI for which only the 
//				MAKE procedure is actually available publicly.
//
//				The class will also have a constructor, called by the MAKE,
//				and may have a destructor called on exit.
//				
//				To make public ui states so that the code can be shared by 2 
//				modules is hard work:
//				1) Use this header file in the sheet.h to make the prototype.
//				2) Use sheetpub.h header file to declare the instance code.
//
//
//				To allow one-way independence between two sets of components
//				you could try internal inheritence. 
//				The lesser file is included before the greater, and the greater
//				is an overclass of the lesser.
//
//From the ui author's POV this provides 6 features:
//
//1) Starts off his class with that name
//
//2) a way to declare a draw routine for a particular type of component
//		namePROC(procname,componentparamname)					
//
//3) a simple way to create components:							ADD()
//		ADD(lists,type,initialiser,*routines*);
//	 a more complex way to add components for compiler errors	ADDTOP()
//		ADDTOP(lists,type,initialiser)
//			*routines*
//		);}
//
//4) a way to associate draw routines with created components:	DRAW()&SELECT()
//		ADD(lists,type,initialiser,
//			DRAW(procname)	SELECT(procname)	);
//
//5) a way to hold on to the address of a created component:	SETBACK()
//typeComp*	mycompptr;
//		ADD(lists,type,initialiser,
//			DRAW(procname)	SELECT(procname)	
//			SETBACK(mycompptr)	);
//
//6) A simple way to finish the class:							SHEETBOT
//	 A complex way to finish a class so it can input parameters:	
//		SHEETBOTPARAM((param,list,with,types),(param,list,no,types))
//	 paramlistnotypes should match your constructor's parameter list 
//		-but without the int and enum type names
//	 paramlistwithtypes are the values you want to provide
//		-often identical to the constructor
//	 They can be reordered, but why would you want to? 
//	 You may want to default some values though.
//	 A manual way to finish a class, SHEETEND
//	 After this you must provide the local/static/public interface
//
//In addition, the following line must be placed in SHEETLST.H
//	static	UISheetPtr	MakeSHEETNAME();
//------------------------------------------------------------------------------
#ifndef	SHEETNAME
#error	"Before including SHEETTOP.h #define SHEETNAME"
#endif
//------------------------------------------------------------------------------
class	SHEETNAME;

//DeadCode JIM 10May96 
//DeadCode JIM 10May96 #include	"UI.h"
//DeadCode JIM 10May96 
//DeadCode JIM 10May96 SLong const 	POPUPW 				= PIXEL640 * 347;
//DeadCode JIM 10May96 SLong const 	POPUPH 				= PIXEL640 * 297;
//DeadCode JIM 10May96 SLong const 	HATMSNSELX			= PIXEL640 * 166;
//DeadCode JIM 10May96 SLong const 	HATMSNSELY			= PIXEL640 * 0;
//DeadCode JIM 10May96 SLong const 	EDITNAMEX			= PIXEL640 * 350; 			//RDH 04Apr96
//DeadCode JIM 10May96 SLong const 	EDITNAMEY			= PIXEL640 * 160; 			//RDH 04Apr96
//DeadCode JIM 10May96 SLong const		SUREDIALOGUEW		= PIXEL640 * 302;			//RDH 20Feb96
//DeadCode JIM 10May96 SLong const		SUREDIALOGUEH		= PIXEL640 * 138;			//RDH 20Feb96
//DeadCode JIM 10May96 SLong const 	TNKOPPSX			= PIXEL640 * 426;
//DeadCode JIM 10May96 SLong const 	TNKOPPSW			= PIXEL640 * 214;
//DeadCode JIM 10May96 SLong const 	TNKOPPSH			= PIXEL640 * 480;
//DeadCode JIM 10May96 SLong const 	MAPW				= PIXEL640 * 558;
//DeadCode JIM 10May96 SLong const 	MAPH				= PIXEL640 * 469;
//DeadCode JIM 10May96 SLong const 	MSNW				= PIXEL640 * 335;
//DeadCode JIM 10May96 SLong const 	MSNH				= PIXEL640 * 480;
//DeadCode JIM 10May96 SLong const 	HATSQUADPNLX		= PIXEL640 * 517; 			//RDH 08Mar96
//DeadCode JIM 10May96 SLong const 	HATSQUADPNLY		= PIXEL640 * 0;
//DeadCode JIM 10May96 SLong const 	HATSQUADPNLW		= PIXEL640 * 123;
//DeadCode JIM 10May96 SLong const 	HATSQUADPNLH		= PIXEL640 * 270;
//DeadCode JIM 10May96 SLong const 	SOSQUADPNLX 		= PIXEL640 * 510;
//DeadCode JIM 10May96 SLong const 	SOSQUADPNLY 		= PIXEL640 * 0;
//DeadCode JIM 10May96 SLong const 	SOSQUADPNLW 		= PIXEL640 * 130;
//DeadCode JIM 10May96 SLong const 	SOSQUADPNLH 		= PIXEL640 * 480;
//DeadCode JIM 10May96 SLong const 	CRCSQUADPNLX		= PIXEL640 * 518;
//DeadCode JIM 10May96 SLong const 	CRCSQUADPNLY		= PIXEL640 * 0;
//DeadCode JIM 10May96 SLong const 	CRCSQUADPNLW		= PIXEL640 * 122;
//DeadCode JIM 10May96 SLong const 	CRCSQUADPNLH		= PIXEL640 * 269;
//DeadCode JIM 10May96 SLong const 	TNKSQUADPNLX		= PIXEL640 * 0;
//DeadCode JIM 10May96 SLong const 	TNKSQUADPNLY		= PIXEL640 * 82;
//DeadCode JIM 10May96 SLong const 	TNKSQUADPNLW		= PIXEL640 * 640;
//DeadCode JIM 10May96 SLong const 	TNKSQUADPNLH		= PIXEL640 * 280;
//DeadCode JIM 10May96 SLong const 	COPYDIALOGUEX		= PIXEL640 * 0;	 			//DAW 08Apr96
//DeadCode JIM 10May96 SLong const 	COPYDIALOGUEY		= PIXEL640 * 0;
//DeadCode JIM 10May96 SLong const 	COPYDIALOGUEW		= PIXEL640 * 640;
//DeadCode JIM 10May96 SLong const 	COPYDIALOGUEH		= PIXEL640 * 480;
//DeadCode JIM 10May96 SLong const 	HATMSNW				= PIXEL640 * 474;
//DeadCode JIM 10May96 SLong const 	HATMSNH				= PIXEL640 * 480;
//DeadCode JIM 10May96 

#ifndef	SHEETPARENT
class	SHEETNAME	:public	UISheet
#else
class	SHEETNAME	:public	SHEETPARENT
#endif
{
//------------------------------------------------------------------------------

#define	SHEETBOT(SHEETNAME)												\
};																\
UISheetPtr	UISheet::Make##SHEETNAME()					\
{	return(new SHEETNAME );};

//put brackets arround the list of parameters
#define	SHEETBOTPARAM(SHEETNAME,pwithtypes,pnotypes)						\
};																\
UISheetPtr	UISheet::Make##SHEETNAME pwithtypes		\
{	return(new SHEETNAME pnotypes);};

#define	SHEETEND	};
//------------------------------------------------------------------------------

/*
This is what makes the ADD macro.
When you get an error, you will want to make this macro more readable.
Simply modify your ADD which should look like:

	ADD(DRAW|TEST,
		Text,(currx,curry,currw,currh),					//here
		SELECT(SelectQuit)
		DATAVAL(QuitTEXT)
		DRAWCODE(Border)
		);

Replace with ADDTOP which looks like:

	ADDTOP(DRAW|TEST,
		Text,(currx,curry,currw,currh)	)				//here
		SELECT(SelectQuit)
		DATAVAL(QuitTEXT)
		DRAWCODE(Border)
		);	};

Note that:
	Start:		ADD		--> 	ADDTOP
	//here:		,		-->		)
	End:				add		};

When compiled again, this will identify the actual line containing an error
*/
//------------------------------------------------------------------------------

#define	ADD(FLAGS,TYPE,COORDS,OFFSIGN)							\
{																\
	SN##TYPE##ProcD	TRANSVARd;									\
	SN##TYPE##ProcE	TRANSVARe;									\
	Add(FLAGS,													\
		(new	TYPE##Comp	COORDS)								\
		OFFSIGN);												\
}																\

#define	ADDTOP(FLAGS,TYPE,COORDS)								\
{																\
	SN##TYPE##ProcD	TRANSVARd;									\
	SN##TYPE##ProcE	TRANSVARe;									\
	Add(FLAGS,													\
		(new	TYPE##Comp	COORDS)								\

#define	LIST(NAME,COORDS,OFFSIGN)								\
{																\
	SNUIListDescProcD TRANSVARd;								\
	SNUIListDescProcE TRANSVARe;								\
	(NAME).Coords COORDS;										\
	(&(NAME))	OFFSIGN;										\
}																\

#define	LISTTOP(NAME,COORDS)									\
{																\
	SNUIListDescProcD TRANSVARd;								\
	SNUIListDescProcE TRANSVARe;								\
	(NAME).Coords COORDS;										\
	(&(NAME));\
}

//------------------------------------------------------------------------------
//The following definitions are required for each type of component:

//I hope these go out of scope quickly!
typedef	void	(*SNNoDataProcD)			(SHEETNAME*,NoDataComp&);
typedef	void	(*SNIntProcD)				(SHEETNAME*,IntComp&);
typedef	void	(*SNIntRefProcD)			(SHEETNAME*,IntRefComp&);
typedef	void	(*SNIntWBProcD)				(SHEETNAME*,IntWBComp&);
typedef	void	(*SNIntRefWBProcD)			(SHEETNAME*,IntRefWBComp&);
typedef	void	(*SNTextProcD)				(SHEETNAME*,TextComp&);
typedef	void	(*SNTextWBProcD)			(SHEETNAME*,TextWBComp&);
typedef	void	(*SNTextIntProcD)			(SHEETNAME*,TextIntComp&);
typedef	void	(*SNTextIntRefProcD)		(SHEETNAME*,TextIntRefComp&);
typedef	void	(*SNTextIntWBProcD)			(SHEETNAME*,TextIntWBComp&);
typedef	void	(*SNTextIntRefWBProcD)		(SHEETNAME*,TextIntRefWBComp&);
typedef	void	(*SNStringWBProcD)			(SHEETNAME*,StringWBComp&);
typedef	void	(*SNUIListDescProcD)		(SHEETNAME*,UIListDescComp&);

typedef			(*SNNoDataProcE)			(SHEETNAME*,NoDataComp&);
typedef			(*SNIntProcE)				(SHEETNAME*,IntComp&);
typedef			(*SNIntRefProcE)			(SHEETNAME*,IntRefComp&);
typedef			(*SNIntWBProcE)				(SHEETNAME*,IntWBComp&);
typedef			(*SNIntRefWBProcE)			(SHEETNAME*,IntRefWBComp&);
typedef			(*SNTextProcE)				(SHEETNAME*,TextComp&);
typedef			(*SNTextWBProcE)			(SHEETNAME*,TextWBComp&);
typedef			(*SNTextIntProcE)			(SHEETNAME*,TextIntComp&);
typedef			(*SNTextIntRefProcE)		(SHEETNAME*,TextIntRefComp&);
typedef			(*SNTextIntWBProcE)			(SHEETNAME*,TextIntWBComp&);
typedef			(*SNTextIntRefWBProcE)		(SHEETNAME*,TextIntRefWBComp&);
typedef			(*SNStringWBProcE)			(SHEETNAME*,StringWBComp&);
typedef			(*SNUIListDescProcE)		(SHEETNAME*,UIListDescComp&);

#ifndef NODATAPROC
//draw/drawhi is different to select/hilight/dehilight
//xxxPROC is the current view, where both are treated the same
//xxxPAINT is for draw/drawhi routines
//xxxEVENT is for select/hilight/dehilight routines
//at some time in the future I may make them different!

#define	NODATAPAINT(procname,uicname)\
	static XX_##procname( SheetBase*s,UIComponent& u)	{YY_##procname((SHEETNAME*)s,(NoDataComp&)u);return 0;}\
	static void YY_##procname( SHEETNAME * s,NoDataComp& u) {s->procname(u);}\
	void procname(NoDataComp& 		uicname)

#define	INTPAINT(procname,uicname)			\
	static XX_##procname( SheetBase*s,UIComponent& u)	{YY_##procname((SHEETNAME*)s,(IntComp&)u);return 0;}\
	static void YY_##procname( SHEETNAME * s,IntComp& u) {s->procname(u);}\
	void procname(IntComp& 		uicname)

#define	INTREFPAINT(procname,uicname)		\
	static XX_##procname( SheetBase*s,UIComponent& u)	{YY_##procname((SHEETNAME*)s,(IntRefComp&)u);return 0;}\
	static void YY_##procname( SHEETNAME * s,IntRefComp& u) {s->procname(u);}\
	void procname(IntRefComp& 		uicname)

#define	INTWBPAINT(procname,uicname)	\
	static XX_##procname( SheetBase*s,UIComponent& u)	{YY_##procname((SHEETNAME*)s,(IntWBComp&)u);return 0;}\
	static void YY_##procname( SHEETNAME * s,IntWBComp& u) {s->procname(u);}\
	void procname(IntWBComp& 		uicname)

#define	INTREFWBPAINT(procname,uicname)		\
	static XX_##procname( SheetBase*s,UIComponent& u)	{YY_##procname((SHEETNAME*)s,(IntRefWBComp&)u);return 0;}\
	static void YY_##procname( SHEETNAME * s,IntRefWBComp& u) {s->procname(u);}\
	void procname(IntRefWBComp& 		uicname)

#define	TEXTPAINT(procname,uicname)			\
	static XX_##procname( SheetBase*s,UIComponent& u)	{YY_##procname((SHEETNAME*)s,(TextComp&)u);return 0;}\
	static void YY_##procname( SHEETNAME * s,TextComp& u) {s->procname(u);}\
	void procname(TextComp& 		uicname)

#define	TEXTWBPAINT(procname,uicname)		\
	static XX_##procname( SheetBase*s,UIComponent& u)	{YY_##procname((SHEETNAME*)s,(TextWBComp&)u);return 0;}\
	static void YY_##procname( SHEETNAME * s,TextWBComp& u) {s->procname(u);}\
	void procname(TextWBComp& 		uicname)

#define	TEXTINTPAINT(procname,uicname)		\
	static XX_##procname( SheetBase*s,UIComponent& u)	{YY_##procname((SHEETNAME*)s,(TextIntComp&)u);return 0;}\
	static void YY_##procname( SHEETNAME * s,TextIntComp& u) {s->procname(u);}\
	void procname(TextIntComp& 		uicname)

#define	TEXTINTREFPAINT(procname,uicname)	\
	static XX_##procname( SheetBase*s,UIComponent& u)	{YY_##procname((SHEETNAME*)s,(TextIntRefComp&)u);return 0;}\
	static void YY_##procname( SHEETNAME * s,TextIntRefComp& u) {s->procname(u);}\
	void procname(TextIntRefComp& 		uicname)

#define	TEXTINTWBPAINT(procname,uicname)	\
	static XX_##procname( SheetBase*s,UIComponent& u)	{YY_##procname((SHEETNAME*)s,(TextIntWBComp&)u);return 0;}\
	static void YY_##procname( SHEETNAME * s,TextIntWBComp& u) {s->procname(u);}\
	void procname(TextIntWBComp& 		uicname)

#define	TEXTINTREFWBPAINT(procname,uicname)	\
	static XX_##procname( SheetBase*s,UIComponent& u)	{YY_##procname((SHEETNAME*)s,(TextIntRefWBComp&)u);return 0;}\
	static void YY_##procname( SHEETNAME * s,TextIntRefWBComp& u) {s->procname(u);}\
	void procname(TextIntRefWBComp& 		uicname)

#define	STRINGPAINT(procname,uicname)		\
	static XX_##procname( SheetBase*s,UIComponent& u)	{YY_##procname((SHEETNAME*)s,(StringWBComp&)u);return 0;}\
	static void YY_##procname( SHEETNAME * s,StringWBComp& u) {s->procname(u);}\
	void procname(StringWBComp& 		uicname)

#define	LISTPAINT(procname,uicname)			\
	static XX_##procname( SheetBase*s,UIComponent& u)	{YY_##procname((SHEETNAME*)s,(UIListDescComp&)u);return 0;}\
	static void YY_##procname( SHEETNAME * s,UIListDescComp& u) {s->procname(u);}\
	void procname(UIListDescComp& 		uicname)


#define	NODATAEVENT(procname,uicname)		\
	static XX_##procname( SheetBase*s,UIComponent& u)	{YY_##procname((SHEETNAME*)s,(NoDataComp&)u);return 0;}\
	static YY_##procname( SHEETNAME * s,NoDataComp& u) {s->procname(u);return 0;}\
	void procname(NoDataComp& 		uicname)

#define	INTEVENT(procname,uicname)			\
	static XX_##procname( SheetBase*s,UIComponent& u)	{YY_##procname((SHEETNAME*)s,(IntComp&)u);return 0;}\
	static YY_##procname( SHEETNAME * s,IntComp& u) {s->procname(u);return 0;}\
	void procname(IntComp& 		uicname)

#define	INTREFEVENT(procname,uicname)		\
	static XX_##procname( SheetBase*s,UIComponent& u)	{return YY_##procname((SHEETNAME*)s,(IntRefComp&)u);}\
	static YY_##procname( SHEETNAME * s,IntRefComp& u) {s->procname(u);return 0;}\
	void procname(IntRefComp& 		uicname)

#define	INTWBEVENT(procname,uicname)		\
	static XX_##procname( SheetBase*s,UIComponent& u)	{return YY_##procname((SHEETNAME*)s,(IntWBComp&)u);}\
	static YY_##procname( SHEETNAME * s,IntWBComp& u) {s->procname(u);return 0;}\
	void procname(IntWBComp& 		uicname)

#define	INTREFWBEVENT(procname,uicname)		\
	static XX_##procname( SheetBase*s,UIComponent& u)	{return YY_##procname((SHEETNAME*)s,(IntRefWBComp&)u);}\
	static YY_##procname( SHEETNAME * s,IntRefWBComp& u) {s->procname(u);return 0;}\
	void procname(IntRefWBComp& 		uicname)

#define	TEXTEVENT(procname,uicname)			\
	static XX_##procname( SheetBase*s,UIComponent& u)	{return YY_##procname((SHEETNAME*)s,(TextComp&)u);}\
	static YY_##procname( SHEETNAME * s,TextComp& u) {s->procname(u);return 0;}\
	void procname(TextComp& 		uicname)

#define	TEXTWBEVENT(procname,uicname)		\
	static XX_##procname( SheetBase*s,UIComponent& u)	{return YY_##procname((SHEETNAME*)s,(TextWBComp&)u);}\
	static YY_##procname( SHEETNAME * s,TextWBComp& u) {s->procname(u);return 0;}\
	void procname(TextWBComp& 		uicname)

#define	TEXTINTEVENT(procname,uicname)		\
	static XX_##procname( SheetBase*s,UIComponent& u)	{return YY_##procname((SHEETNAME*)s,(TextIntComp&)u);}\
	static YY_##procname( SHEETNAME * s,TextIntComp& u) {s->procname(u);return 0;}\
	void procname(TextIntComp& 		uicname)

#define	TEXTINTREFEVENT(procname,uicname) 	\
	static XX_##procname( SheetBase*s,UIComponent& u)	{return YY_##procname((SHEETNAME*)s,(TextIntRefComp&)u);}\
	static YY_##procname( SHEETNAME * s,TextIntRefComp& u) {s->procname(u);return 0;}\
	void procname(TextIntRefComp& 		uicname)

#define	TEXTINTWBEVENT(procname,uicname)	\
	static XX_##procname( SheetBase*s,UIComponent& u)	{return YY_##procname((SHEETNAME*)s,(TextIntWBComp&)u);}\
	static YY_##procname( SHEETNAME * s,TextIntWBComp& u) {s->procname(u);return 0;}\
	void procname(TextIntWBComp& 		uicname)

#define	TEXTINTREFWBEVENT(procname,uicname)	\
	static XX_##procname( SheetBase*s,UIComponent& u)	{return YY_##procname((SHEETNAME*)s,(TextIntRefWBComp&)u);}\
	static YY_##procname( SHEETNAME * s,TextIntRefWBComp& u) {s->procname(u);return 0;}\
	void procname(TextIntRefWBComp& 		uicname)

#define	STRINGEVENT(procname,uicname)		\
	static XX_##procname( SheetBase*s,UIComponent& u)	{return YY_##procname((SHEETNAME*)s,(StringWBComp&)u);}\
	static YY_##procname( SHEETNAME * s,StringWBComp& u) {s->procname(u);return 0;}\
	void procname(StringWBComp& 		uicname)

#define	LISTEVENT(procname,uicname)			\
	static XX_##procname( SheetBase*s,UIComponent& u)	{return YY_##procname((SHEETNAME*)s,(UIListDescComp&)u);}\
	static YY_##procname( SHEETNAME * s,UIListDescComp& u) {s->procname(u);return 0;}\
	void procname(UIListDescComp& 		uicname)

#endif

#ifndef	DEHILIGHT
//The following definition is required for each type of code supported:

#define	DRAW(procname)		->DrawCode		((TRANSVARd=YY_##procname, XX_##procname))
#define	DRAWHI(procname)	->DrawHiCode	((TRANSVARd=YY_##procname, XX_##procname))
#define	SELECT(procname)	->SelectCode	((TRANSVARe=YY_##procname, XX_##procname))
#define	SELECTR(procname)	->Select2Code	((TRANSVARe=YY_##procname, XX_##procname))
#define	HILIGHT(procname)	->HilightCode	((TRANSVARe=YY_##procname, XX_##procname))
#define	DEHILIGHT(procname)	->DeHilightCode	((TRANSVARe=YY_##procname, XX_##procname))
#define	WRITEBACK(procname) ->WriteCode		((TRANSVARe=YY_##procname, XX_##procname))

//Dataval is a special. It don't have a procedure, but variable arguments!
#define	 DATAVAL	->DataVal

//Helptext fills the helptext field with a TextSnip0 equate.
#define	 HELPTEXT	->HelpText

//Setback is a special. It sets an input variable with the address of the component
#define	SETBACK		->SetBack
#endif
//------------------------------------------------------------------------------
public:
//DeadCode JIM 30May96 #undef	SHEETNAME
#ifdef	SHEETPARENT
#undef	SHEETPARENT
#endif
//------------------------------------------------------------------------------
