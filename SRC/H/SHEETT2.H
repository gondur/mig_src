//------------------------------------------------------------------------------
//Filename       sheettop.h
//System         
//Author         Jim Taylor
//Date           Fri 17 Nov 1995
//Description    Defines the top of a sheet 
//				 Assumes that SHEETNAME has been defined
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
typedef		(SHEETNAME::*SNNoDataProcD)			(class	NoDataComp&);
typedef		(SHEETNAME::*SNIntProcD)				(class	IntComp&);
typedef		(SHEETNAME::*SNIntRefProcD)			(class	IntRefComp&);
typedef		(SHEETNAME::*SNIntWBProcD)			(class	IntWBComp&);
typedef		(SHEETNAME::*SNIntRefWBProcD)		(class	IntRefWBComp&);
typedef		(SHEETNAME::*SNTextProcD)			(class	TextComp&);
typedef		(SHEETNAME::*SNTextWBProcD)			(class	TextWBComp&);
typedef		(SHEETNAME::*SNTextIntProcD)			(class	TextIntComp&);
typedef		(SHEETNAME::*SNTextIntRefProcD)		(class	TextIntRefComp&);
typedef		(SHEETNAME::*SNTextIntWBProcD)		(class	TextIntWBComp&);
typedef		(SHEETNAME::*SNTextIntRefWBProcD)	(class	TextIntRefWBComp&);
typedef		(SHEETNAME::*SNStringWBProcD)		(class	StringWBComp&);
typedef		(SHEETNAME::*SNUIListDescProcD)		(class	UIListDescComp&);

typedef	void	(SHEETNAME::*SNNoDataProcE)			(class	NoDataComp&);
typedef	void	(SHEETNAME::*SNIntProcE)				(class	IntComp&);
typedef	void	(SHEETNAME::*SNIntRefProcE)			(class	IntRefComp&);
typedef	void	(SHEETNAME::*SNIntWBProcE)			(class	IntWBComp&);
typedef	void	(SHEETNAME::*SNIntRefWBProcE)		(class	IntRefWBComp&);
typedef	void	(SHEETNAME::*SNTextProcE)			(class	TextComp&);
typedef	void	(SHEETNAME::*SNTextWBProcE)			(class	TextWBComp&);
typedef	void	(SHEETNAME::*SNTextIntProcE)		(class	TextIntComp&);
typedef	void	(SHEETNAME::*SNTextIntRefProcE)		(class	TextIntRefComp&);
typedef	void	(SHEETNAME::*SNTextIntWBProcE)		(class	TextIntWBComp&);
typedef	void	(SHEETNAME::*SNTextIntRefWBProcE)	(class	TextIntRefWBComp&);
typedef	void	(SHEETNAME::*SNStringWBProcE)		(class	StringWBComp&);
typedef	void	(SHEETNAME::*SNUIListDescProcE)		(class	UIListDescComp&);

#ifndef NODATAPROC
//draw/drawhi is different to select/hilight/dehilight
//xxxPROC is the current view, where both are treated the same
//xxxPAINT is for draw/drawhi routines
//xxxEVENT is for select/hilight/dehilight routines
//at some time in the future I may make them different!

//DeadCode JIM 30Jan96 #define	NODATAPROC(procname,uicname)		void	procname(NoDataComp&		uicname)
//DeadCode JIM 30Jan96 #define	INTPROC(procname,uicname)			void	procname(IntComp&			uicname)
//DeadCode JIM 30Jan96 #define	INTREFPROC(procname,uicname)		void	procname(IntRefComp&		uicname)
//DeadCode JIM 30Jan96 #define	INTWBPROC(procname,uicname)			void	procname(IntWBComp&			uicname)
//DeadCode JIM 30Jan96 #define	INTREFWBPROC(procname,uicname)		void	procname(IntRefWBComp&		uicname)
//DeadCode JIM 30Jan96 #define	TEXTPROC(procname,uicname)			void	procname(TextComp&			uicname)
//DeadCode JIM 30Jan96 #define	TEXTWBPROC(procname,uicname)		void	procname(TextWBComp&		uicname)
//DeadCode JIM 30Jan96 #define	TEXTINTPROC(procname,uicname)		void	procname(TextIntComp&		uicname)
//DeadCode JIM 30Jan96 #define	TEXTINTREFPROC(procname,uicname)	void	procname(TextIntRefComp&	uicname)
//DeadCode JIM 30Jan96 #define	TEXTINTWBPROC(procname,uicname)		void	procname(TextIntWBComp&		uicname)
//DeadCode JIM 30Jan96 #define	TEXTINTREFWBPROC(procname,uicname)	void	procname(TextIntRefWBComp&	uicname)

#define	NODATAPAINT(procname,uicname)				procname(NoDataComp&		uicname)
#define	INTPAINT(procname,uicname)					procname(IntComp&			uicname)
#define	INTREFPAINT(procname,uicname)				procname(IntRefComp&		uicname)
#define	INTWBPAINT(procname,uicname)				procname(IntWBComp&			uicname)
#define	INTREFWBPAINT(procname,uicname)				procname(IntRefWBComp&		uicname)
#define	TEXTPAINT(procname,uicname)					procname(TextComp&			uicname)
#define	TEXTWBPAINT(procname,uicname)				procname(TextWBComp&		uicname)
#define	TEXTINTPAINT(procname,uicname)				procname(TextIntComp&		uicname)
#define	TEXTINTREFPAINT(procname,uicname)			procname(TextIntRefComp&	uicname)
#define	TEXTINTWBPAINT(procname,uicname)			procname(TextIntWBComp&		uicname)
#define	TEXTINTREFWBPAINT(procname,uicname)			procname(TextIntRefWBComp&	uicname)
#define	STRINGPAINT(procname,uicname)				procname(StringWBComp&		uicname)
#define	LISTPAINT(procname,uicname)					procname(UIListDescComp&		uicname)

#define	NODATAEVENT(procname,uicname)		void	procname(NoDataComp&		uicname)
#define	INTEVENT(procname,uicname)			void	procname(IntComp&			uicname)
#define	INTREFEVENT(procname,uicname)		void	procname(IntRefComp&		uicname)
#define	INTWBEVENT(procname,uicname)		void	procname(IntWBComp&			uicname)
#define	INTREFWBEVENT(procname,uicname)		void	procname(IntRefWBComp&		uicname)
#define	TEXTEVENT(procname,uicname)			void	procname(TextComp&			uicname)
#define	TEXTWBEVENT(procname,uicname)		void	procname(TextWBComp&		uicname)
#define	TEXTINTEVENT(procname,uicname)		void	procname(TextIntComp&		uicname)
#define	TEXTINTREFEVENT(procname,uicname) 	void	procname(TextIntRefComp&	uicname)
#define	TEXTINTWBEVENT(procname,uicname)	void	procname(TextIntWBComp&		uicname)
#define	TEXTINTREFWBEVENT(procname,uicname)	void	procname(TextIntRefWBComp&	uicname)
#define	STRINGEVENT(procname,uicname)		void	procname(StringWBComp&		uicname)
#define	LISTEVENT(procname,uicname)			void	procname(UIListDescComp&		uicname)
#endif

#ifndef	DEHILIGHT
//The following definition is required for each type of code supported:

#define	DRAW(procname)		->DrawCode		(((SheetProc) (TRANSVARd=procname)))
#define	DRAWHI(procname)	->DrawHiCode	(((SheetProc) (TRANSVARd=procname)))
#define	SELECT(procname)	->SelectCode	(((SheetProc) (TRANSVARe=procname)))
#define	SELECTR(procname)	->Select2Code	(((SheetProc) (TRANSVARe=procname)))
#define	HILIGHT(procname)	->HilightCode	(((SheetProc) (TRANSVARe=procname)))
#define	DEHILIGHT(procname)	->DeHilightCode	(((SheetProc) (TRANSVARe=procname)))
#define	WRITEBACK(procname) ->WriteCode		(((SheetProc) (TRANSVARe=procname)))

//Dataval is a special. It don't have a procedure, but variable arguments!
#define	 DATAVAL	->DataVal

//Setback is a special. It sets an input variable with the address of the component
#define	SETBACK		->SetBack
#endif
//------------------------------------------------------------------------------
public:
#undef	SHEETNAME
#ifdef	SHEETPARENT
#undef	SHEETPARENT

#endif
//------------------------------------------------------------------------------

