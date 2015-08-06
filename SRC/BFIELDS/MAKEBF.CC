//------------------------------------------------------------------------------
//Filename       makebf.CC
//System         
//Author         Jim Taylor
//Date           Thu 23 Nov 1995
//Description    Tool to make battlefields!
//
//The basic syntax constructs are typeassignment and valuesequence:
//typeassignment::
//		type	name	"="		value
//	|	type	value
//	|	type	"="		value
//
//where type is a predefined "U_typename" keyword
//
//value is one of:
//	predefined external variable
//	predefined 3ds variable
//  a name from a previous statement
//	or a valuesequence
//
//valuesequence::
//		"{"	 typeassignment	"," typeassignment ... "}"
//
//Formally, this is 
//valuesequence::
//		"{" typeassignmentlist
//typeassignmentlist::
//		typeassignment ","	typeassignmentlist
//	|	typeassignment "}"
//
//at present, value cannot be	value::	modifier	value
//you have to write {modifier value}
//
//The whole battlefield system generates a single valuesequence.
//The basic generation of typeassignments is the job of GetTypeAndValue().
//The association of types with values of different types
//and the legal typeassignments within a particular valuesequence
//are specified in the detailed grammar.
//
//This is built into trees using the constructs:
//	LinkInst	-	link-list sibling/dataref pair
//	ChainInst	-	tokentype+dataref
//	IntInst		-	integer value on all leaf nodes
//
//These are referenced from the dictionary which uses an alphatree for sorting
//There is also a pointer to the 'big cheese' battlefield LinkInst
//
//The whole thing is output using pre-traversal. 
//IntInst forms the leaf nodes, LinkInst forms the joins, and Chain is identifiers.
//
//Some important branch patterns:
//3dsref:
//				3dsref->Link->shape->int
//						Link->pos->abs->Link->x->int
//										Link->y->int
//										Link->z->int
//from which shape or pos trees can be pulled
//enum value: 	enum->int
//global var:	enum->global->int
//item ref:		type->enumUID->int
//
//filename:		references back to dictionary
//setUID:		references back to dictionary, and has integerinst
//
//------------------------------------------------------------------------------
#ifndef	SOURCE
#define	SOURCE

	#define	uidvals_included
	#include	"bfcommon.h"
#include	"bfields\persons.cpp"

//DeadCode JIM 05Jun96 	#include	"dosdefs.h"
//DeadCode JIM 05Jun96 	#include	<stdio.h>
//DeadCode JIM 05Jun96 	#include	<io.h>
//DeadCode JIM 05Jun96 //DeadCode JIM 12Feb96 typedef	FILE	*file;
//DeadCode JIM 05Jun96 	#include	<stdarg.h>
//DeadCode JIM 05Jun96 	#include	<stdlib.h>
//DeadCode JIM 05Jun96 	#include	<string.h>
//DeadCode JIM 05Jun96 	#include	"makebf.h"
//DeadCode JIM 05Jun96 	#include	"uidband.h"
//DeadCode JIM 05Jun96 	#include	"modfile.h"

//DeadCode JIM 25Apr96 	#include	"double.h"
//DeadCode JIM 25Apr96 static	SDouble	UDouble::ReturnValue(0);
#define	MaxFileCount 32
#define	MaxTotFileCount 50
#define MaxFileBits	5
char	*names[MaxTotFileCount+1]={"Internal list"};
UWord	currsrcfname=0;
UWord	topsrcfname=0;
UWord	topwsrcfname=MaxFileCount;
UWord	currsrcfline=0;
UWord	filenestlevel=0;
UWord	Current_Level=0;

//DeadCode JIM 24Jun96 UFILE*	filelistfile;
UFILE*	UIDlistfile=NULL;
int		unshaped3ds=0;
int		uidtable1[40], uidtable2[40];
int		uidtablesize=0;
int		newuidcount=0;

struct
{
	UFILE*	openhandle;
	char*	dirname;
	int		dirnum;
}	Battle_Dirs[256]={{0,0,0}};

//TempCode MS 25Mar96 enum	XY	{XYOrdMIN=-32767,XYOrdMAX=32767};
//TempCode MS 25Mar96 enum	ScreenXY	{SXYOrdMIN=0x00000000,SXYOrdMAX=0xffffffff};
//TempCode MS 25Mar96 enum	WH	{WHOrdMIN=-32767,WHOrdMAX=32767};
//TempCode MS 25Mar96 enum	ScreenWH	{SWHOrdMIN=0x00000000,SWHOrdMAX=0xffffffff};
//TempCode MS 25Mar96 
//TempCode MS 25Mar96 inline	ScreenXY	operator,(XY	X,int Y)
//TempCode MS 25Mar96 {return(ScreenXY) (	((ULong)X&0x0000FFFF)	|	(((ULong)Y&0x0000FFFF)<<16)	);}
//TempCode MS 25Mar96 
//TempCode MS 25Mar96 inline	ScreenWH	operator,(WH	X,int Y)
//TempCode MS 25Mar96 {return(ScreenWH) (	((ULong)X&0x0000FFFF)	|	(((ULong)Y&0x0000FFFF)<<16)	);}
//TempCode MS 25Mar96 
//TempCode MS 25Mar96 inline	SLong	X(ScreenXY S)	{return	 (SLong)(SWord)(S&0x0000FFFF);}
//TempCode MS 25Mar96 inline	SLong	Y(ScreenXY S)	{return	 (SLong)(SWord)((S>>16)&0x0000FFFF);}
//TempCode MS 25Mar96 
//TempCode MS 25Mar96 inline	SLong	W(ScreenWH S)	{return	 (SLong)(SWord)(S&0x0000FFFF);}
//TempCode MS 25Mar96 inline	SLong	H(ScreenWH S)	{return	 (SLong)(SWord)((S>>16)&0x0000FFFF);}


struct	RecurseChk;
struct	RecurseChk
{
	void* v1;
	static 	RecurseChk*	base;
	RecurseChk*	next;
	RecurseChk(void* v)
		{next=base;v1=v;base=this;}
	~RecurseChk()
		{RecurseChk** s=&base;while (*s!=this) s=&s[0]->next;*s=next;}
	operator int()
		{RecurseChk* s=next;while (s && s->v1!=v1) s=s->next;return(!s);}
}*	RecurseChk::base=NULL;
#define	RECURSECHK		RecurseChk recursechk(this);if(recursechk)
//------------------------------------------------------------------------------
//Enhanced error messaging. __FILE__ and __LINE__ are inserted using 
//inline functuions, so they should be accurate!
//
#undef	EmitSysErr
void	EmitSysErr(int line,char* mark,char* filename,char* &maintext)
{
	if (UIDlistfile)
	{
		fprintf(UIDlistfile,"#endif\n");
		fclose(UIDlistfile);
	}
	va_list	marker={mark};
	printf("Error : code: %s(%i). Reading: %s(%i)\n",
				filename,line,names[currsrcfname],currsrcfline);
	vprintf(maintext,marker);
	printf("\n");
	exit(10);
}

void	EmitWarning(int line,char* mark,char* filename,char* &maintext)
{
	va_list	marker={mark};
	printf("Warning: code: %s(%i); read: %s(%i):",
				filename,line,names[currsrcfname],currsrcfline);
	vprintf(maintext,marker);
	printf("\n");
}

//TempCode JIM 29Nov95 void	EmitSysErr(char *message)  
//TempCode JIM 29Nov95 {	//This is to stop message with no parameters getting % commands expanded!
//TempCode JIM 29Nov95 	char*	fred[2]={"%s",message};
//TempCode JIM 29Nov95 	EmitSysErr(__LINE__ , (char*) fred , __FILE__ ,  fred[0]);
//TempCode JIM 29Nov95 
//TempCode JIM 29Nov95 }

inline	void	EmitSysErr(char *fmt, ...)
{
	va_list	marker;	 //this points to an array of pointers
	va_start(marker, fmt);
	EmitSysErr(__LINE__ , marker[0], __FILE__ ,  fmt);

}

//TempCode JIM 29Nov95 void	EmitWarning(char *message)
//TempCode JIM 29Nov95 {
//TempCode JIM 29Nov95 	char*	fred[2]={"%s",message};
//TempCode JIM 29Nov95 	EmitWarning(__LINE__ , (char*) fred , __FILE__ ,  fred[0]);
//TempCode JIM 29Nov95 }


void	EmitWarning(char *fmt, ...)
{
	va_list	marker;	 //this points to an array of pointers
	va_start(marker, fmt);
	EmitWarning(__LINE__ , marker[0], __FILE__ ,  fmt);

}




//Need to stop expansion of any accidental %x in the expression
#define	Assert(expr)	((expr)?((void)0):(EmitSysErr("Assert failed: " #expr),((void)0)))
//#define	Assert(expr)	((void)0)
#define	NAssert(expr)	((expr)?(EmitSysErr("Assert succeeded: " #expr),((void)0)):((void)0))
//#define	NAssert(expr)	((void)0)

//------------------------------------------------------------------------------


struct	TokenInit
{
	char*	tokentext;
	UsageType	usage:4;			//max 16 //got 7 initially!
	TokenCode	tokencode:8;		//max 256 //got 47 initially!
	Defined		defined:2;
	UWord		srcfname:MaxFileBits;			//max 16 files
};

typedef struct	DataInst	*DataRef;

struct	TokenName:public	TokenInit
{
	UWord		srcfline;			//max 64K lines per file
	DataRef		instance;

	string	TokenText();
	TokenName()
	{
		tokencode=T_unknown;
		instance=NULL;
	}
void	SaveTxt(ufile	ofile,int	depth);
};

//------------------------------------------------------------------------------
string	itsanint="<integer value>";
string	itsaseq="<sequence>";
string	itsanono="<no name>";


	string	TokenName::TokenText()
	{
		if (this==NULL)			return(itsanono);
		if (tokentext)			return(tokentext);
		if (tokencode==T_int)	return(itsanint);
		return(itsaseq);
	}
//------------------------------------------------------------------------------
#define	ACCEPTCASELIST							   						\
			case	T_3dsref:	case	T_mainprog:						\
			case	T_bfsave:	case	T_itemgrp:	case	T_gndgrp:	\
			case	T_itemS:	case	T_itemG:	case	T_itemA:	\
			case	T_target:	case	T_pos:		case	T_abs:		\ 
			case	T_inwing:	case	T_inform:	case	T_leader:	\
			case	T_skill:	case	T_morale:	case	T_character:\
			case	T_x:		case	T_y:		case	T_z:		\
			case	T_enum:		case	T_UIDband:	case	T_briefID:	\
			case	T_type:		case	T_duty:		case	T_form:		\ 
			case	T_angle:	case	T_bearing:	case	T_asimuth:	\
			case	T_hdg:		case	T_pitch:	case	T_roll:		\
			case	T_setUID:	case	T_setval:						\ 
			case	T_random:	case	T_select:	case	T_list:		\
			case	T_airgrp:	case	T_route:						\
			case	T_waypoint:	case	T_vel:		case	T_paintscheme:\
			case	T_rel:		case	T_att:		case	T_attacker:	\
			case	T_damage:	case	T_squadron:	case	T_home:		\
			case	T_nation:	case	T_shape:	case	T_follower:	\
			case	T_move:		case	T_wpact:						\
			case	T_start:	case	T_window:	case	T_event:	\
			case	T_hours:	case	T_mins:		case	T_secs:		\
			case	T_range:	case	T_count:	case	T_bombs:	\
			case	T_icpt:		case	T_rangepc:						\

//------------------------------------------------------------------------------
char	*whitechars=" \t",		//doesn't include newline - handled separately
			//this list comes from the punctuation tokens identified below.
		*endchars=" \n\t" "<{([)}>],;+=:*@?";
TokenInit	fixedtokens[]=
	{	//these are the basic building blocks of punctuation:
		{"{",U_punctuation,T_brktopen},
		{"(",U_punctuation,T_brktopen},
		{"[",U_punctuation,T_brktopen},
		{"<",U_punctuation,T_brktopen},
		{"}",U_punctuation,T_brktclose},
		{")",U_punctuation,T_brktclose},
		{"]",U_punctuation,T_brktclose},
		{">",U_punctuation,T_brktclose},
		{",",U_punctuation,T_comma},
		{";",U_punctuation,T_comma},
		{"+",U_punctuation,T_comma},
		{"=",U_punctuation,T_equals},
		{":",U_punctuation,T_equals},
		{"*",U_punctuation,T_times},
		{"@",U_punctuation,T_times},
		{"?",U_punctuation,T_question},

//------------------------------------------------------------------------------
		//keyword list. This lists all the keywords handled
		//this lists everything after the first 2 lines in TokenCode
 		{"BattleField",U_typename,T_bfsave},
		{"ItemGroup",U_typename,T_itemgrp},
		{"GroundGroup",U_typename,T_gndgrp},
		{"GroundForm",U_typename,T_gndgrp},
		{"AirGroup",U_typename,T_airgrp},
		{"AirForm",U_typename,T_airgrp},
		{"Route",U_typename,T_route},
		{"SimpleItem",U_typename,T_itemS},
		{"Item",U_typename,T_itemS},
		{"GroundItem",U_typename,T_itemG},
		{"MobileItem",U_typename,T_itemG},
		{"Aircraft",U_typename,T_itemA},
		{"AirItem",U_typename,T_itemA},
		{"Target",U_typename,T_target},
		{"Leader",U_typename,T_leader},
		{"Follower",U_typename,T_follower},						//MS 28Aug96
		{"WayPoint",U_typename,T_waypoint},
		{"Posn",U_typename,T_pos},
		{"Position",U_typename,T_pos},
		{"Abs",U_typename,T_abs},
		{"Rel",U_typename,T_rel},
		{"Attitude",U_typename,T_att},
		{"NumInWing",U_typename,T_inwing},
		{"NumInForm",U_typename,T_inform},
		{"Damage",U_typename,T_damage},
		{"Level",U_typename,T_level},
		{"Vel",U_typename,T_vel},
		{"X",U_typename,T_x},
		{"Y",U_typename,T_y},
		{"Z",U_typename,T_z},
		{"UIDBand",U_typename,T_UIDband},
		{"SetUID",U_typename,T_setUID},
		{"BriefID",U_typename,T_briefID},
		{"Side",U_typename,T_nation},
		{"Shape",U_typename,T_shape},
		{"Type",U_typename,T_type},
		{"Duty",U_typename,T_duty},
		{"Formation",U_typename,T_form},
		{"MoveCode",U_typename,T_move},
		{"Action",U_typename,T_wpact},
		{"Angle",U_typename,T_angle},
		{"Heading",U_typename,T_hdg},
		{"Pitch",U_typename,T_pitch},
		{"Roll",U_typename,T_roll},
		{"Asimuth",U_typename,T_asimuth},
		{"Bearing",U_typename,T_bearing},
		{"Range",U_typename,T_range},
		{"FileName",U_typename,T_fname},
		{"#INCLUDE",U_typename,T_include},
		{"Int",U_typename,T_count},
		{"Count",U_typename,T_count},
		{"Setval",U_typename,T_setval},
		{"Event",U_typename,T_event},
		{"Start",U_typename,T_start},
		{"Time",U_typename,T_start},
		{"StartTime",U_typename,T_start},
		{"Window",U_typename,T_window},
		{"WindowTime",U_typename,T_window},
		{"H",U_typename,T_hours},
		{"Hours",U_typename,T_hours},
		{"M",U_typename,T_mins},
		{"Mins",U_typename,T_mins},
		{"S",U_typename,T_secs},
		{"Secs",U_typename,T_secs},
		{"Skill",U_typename,T_skill},
		{"Morale",U_typename,T_morale},
		{"Character",U_typename,T_character},
		{"Style",U_typename,T_character},
		{"Random",U_typename,T_random},
		{"Select",U_typename,T_select},
		{"Intercept",U_typename,T_icpt},
		{"RangePercent",U_typename,T_rangepc},
		{"List",U_typename,T_list},
		{"PaintScheme",U_typename,T_paintscheme},
		{"Squadron",U_typename,T_squadron},
		{"Home",U_typename,T_home},
		{"Attacker",U_typename,T_attacker},
		{"Bombs",U_typename,T_bombs},

//------------------------------------------------------------------------------
		//these are to allow enums to be recognised
		{"enum",U_typename,T_enum},
		{"const",U_value,T_enum},

//------------------------------------------------------------------------------
		//these are for 3d studio interpreter
		{"Named",U_typename,T_named},
		{"object",U_typename,T_object},
		{"Vertex",U_typename,T_vertex},
		{"Vertices",U_typename,T_vertex},
		{"Face",U_typename,T_face},
		{"Faces",U_typename,T_face},
		{"A",U_typename,T_a},
		{"B",U_typename,T_b},
		{"C",U_typename,T_c},
		{"Mtl",U_typename,T_mtl},
		{"Material",U_typename,T_mtl},

//------------------------------------------------------------------------------
		//this list must accomodate all required enums in the
		//current version.
		//in later versions we might allow an init syntax that
		//generates this information based on keywords

//DeadCode JIM 27Nov95 		{"UsageType",U_enumequiv,T_form},
//DeadCode JIM 27Nov95 		{"TokenCode",U_enumequiv,T_duty},
//DeadCode JIM 27Nov95 		{"Defined",U_enumequiv,T_duty},
//DeadCode JIM 05Dec95 		{"ANGLES",U_enumequiv,T_angle},
//DeadCode JIM 05Dec95 		{"UniqueIDBand",U_enumequiv,T_UIDband},
//DeadCode JIM 05Dec95 		{"ShapeNum",U_enumequiv,T_shape},
//DeadCode JIM 05Dec95 		{"BFieldWaypointActions",U_enumequiv,T_wpact},
//DeadCode JIM 05Dec95 		{"Nationality",U_enumequiv,T_nation},
//DeadCode JIM 05Dec95 		{"PlaneTypeSelect",U_enumequiv,T_type},
//DeadCode JIM 05Dec95 		{"DutyType",U_enumequiv,T_duty},
//DeadCode JIM 05Dec95 		{"AutoMoveCodeTypeSelect",U_enumequiv,T_move},
//DeadCode JIM 05Dec95 		{"SkillType",U_enumequiv,T_skill},

//not done these yet...
//			T_briefID
//			T_type,T_duty,T_form,T_move,
		
//------------------------------------------------------------------------------
		{"",U_punctuation,T_unknown}
	};
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//For forward referencing purposes.
//These toplevel versions of the routines are not context sensitive.
//Alternate versions could be called from contexts.
//
DataInst*	toplevel_bfsave(file	ifile,TokenName	*pvalue);
DataInst*	toplevel_itemgrp(file	ifile,TokenName	*type);
DataInst*	toplevel_gndgrp(file	ifile,TokenName	*value);
DataInst*	toplevel_airgrp(file	ifile,TokenName	*value);
DataInst*	toplevel_route(file	ifile,TokenName	*value);
DataInst*	toplevel_itemS(file	ifile,TokenName	*value);
DataInst*	toplevel_itemG(file	ifile,TokenName	*value);
DataInst*	toplevel_itemA(file	ifile,TokenName	*value);
DataInst*	toplevel_itemU(file	ifile,TokenName	*value);
DataInst*	toplevel_waypoint(file	ifile,TokenName	*value);
DataInst*	toplevel_pos(file	ifile,TokenName	*value);
DataInst*	toplevel_abs(file	ifile,TokenName	*value);
DataInst*	toplevel_rel(file	ifile,TokenName	*value);
DataInst*	toplevel_att(file	ifile,TokenName	*value);
DataInst*	toplevel_inwing(file	ifile,TokenName	*value);
DataInst*	toplevel_inform(file	ifile,TokenName	*value);
DataInst*	toplevel_skill(file	ifile,TokenName	*value);
DataInst*	toplevel_morale(file	ifile,TokenName	*value);
DataInst*	toplevel_character(file	ifile,TokenName	*value);
DataInst*	toplevel_damage(file	ifile,TokenName	*value);
DataInst*	toplevel_level(file	ifile,TokenName	*value);
DataInst*	toplevel_x(file	ifile,TokenName	*value);
DataInst*	toplevel_y(file	ifile,TokenName	*value);
DataInst*	toplevel_z(file	ifile,TokenName	*value);
DataInst*	toplevel_vel(file	ifile,TokenName	*pvalue);
DataInst*	toplevel_range(file	ifile,TokenName	*pvalue);
DataInst*	toplevel_count(file	ifile,TokenName	*pvalue);
DataInst*	toplevel_UIDband(file	ifile,TokenName	*value);
DataInst*	toplevel_briefID(file	ifile,TokenName	*value);
DataInst*	toplevel_nation(file	ifile,TokenName	*value);
DataInst*	toplevel_shape(file	ifile,TokenName	*value);
DataInst*	toplevel_type(file	ifile,TokenName	*value);
DataInst*	toplevel_duty(file	ifile,TokenName	*value);
DataInst*	toplevel_form(file	ifile,TokenName	*value);
DataInst*	toplevel_move(file	ifile,TokenName	*value);
DataInst*	toplevel_wpact(file	ifile,TokenName	*value);
DataInst*	toplevel_bearing(file	ifile,TokenName	*value);
//DeadCode JIM 20Mar96 DataInst*	toplevel_hdg(file	ifile,TokenName	*value);
DataInst*	toplevel_pitch(file	ifile,TokenName	*value);
DataInst*	toplevel_roll(file	ifile,TokenName	*value);
DataInst*	toplevel_fname(TokenName*&evalue,TokenName	*pvalue);
DataInst*	toplevel_event(file	ifile,TokenName	*value);
DataInst*	numeric_event(file	ifile,TokenName	*value);
DataInst*	toplevel_enumval(file	ifile,TokenName	*value,TokenCode);
DataInst*	toplevel_enumorint(file	ifile,TokenName	*value,TokenCode);
DataInst*	toplevel_enumorangle(file	ifile,TokenName	*value,TokenCode);
DataInst*	toplevel_time(file	ifile,TokenName	*value,TokenCode);
DataInst*	toplevel_hours(file	ifile,TokenName	*value);
DataInst*	toplevel_mins(file	ifile,TokenName	*value);
DataInst*	toplevel_secs(file	ifile,TokenName	*value);
DataInst*	toplevel_bombs(file	ifile,TokenName	*value);
DataInst*	itemlevel_setUID(file	ifile,TokenName	*value);
DataInst*	toplevel_rangepc(file	ifile,TokenName	*pvalue);
DataInst*	toplevel_target(file	ifile,TokenName	*pvalue,TokenCode tokencode);
DataInst*	toplevel_leader(file	ifile,TokenName	*pvalue);
DataInst*	toplevel_follower(file	ifile,TokenName	*pvalue);
DataInst*	toplevel_attacker(file	ifile,TokenName	*pvalue);
DataInst*	toplevel_home(file	ifile,TokenName	*pvalue);
DataInst*	toplevel_paintscheme(file	ifile,TokenName	*pvalue);
DataInst*	toplevel_squadron(file	ifile,TokenName	*pvalue);
ufile	writefile(char*	name,char mode,char* dirname=NULL);
void	studiointerpreter(file	ifile);
//---------------------------------------
struct ChainInst;
//---------------------------------------

struct	Coordinates
{
	int 	x, y, z;
};

struct	Connections
{
	int		a, b, c;
};

char	wordbuff[180]={0};
char	fbuff[10]="fault   ";

TokenCode	parentcode;

char*	getcodename(TokenCode code)
{
 	switch (code)
	{
	case T_sortentry:	return("sortentry");
	case T_unknown:		return("unknown");
	case T_brktopen:	return("brkt(open");
	case T_brktclose:	return("brkt)close");
	case T_comma:		return("comma(,)");
	case T_equals:		return("equals(=)");
	case T_times:		return("times(*)");
	case T_question:	return("question(?)");
	case T_int:			return("int");
	case T_nint:		return("negint");
	case T_byte:		return("byte");
	case T_word:		return("word");
	case T_long:		return("long");
	case T_nbyte:		return("nbyte");
	case T_nword:		return("nword");
	case T_nlong:		return("nlong");
	case T_count:		return("count");
	case T_include:		return("include");
	case T_3dsref:		return("3dsref");
	case T_mainprog:	return("mainprog");
	case T_bfsave:		return("bfsave");
	case T_itemgrp:		return("itemgrp");
	case T_gndgrp:		return("gndgrp");
	case T_airgrp:		return("airgrp");
	case T_route:		return("route");
	case T_itemS:		return("itemS");
	case T_itemG:		return("itemG");
	case T_itemA:		return("itemA");
	case T_waypoint:	return("waypoint");
	case T_target:		return("target");
	case T_attacker:		return("attacker");
	case T_pos:			return("pos");
	case T_abs:			return("abs");
	case T_rel:			return("rel");
	case T_att:			return("att");
	case T_inwing:		return("inwing");
	case T_inform:		return("inform");
	case T_damage:		return("damage");
	case T_level:		return("level");
	case T_skill:		return("skill");
	case T_morale:		return("morale");
	case T_character:		return("character");
	case T_x:			return("x");
	case T_y:			return("y");
	case T_z:			return("z");
	case T_enum:		return("enum");
	case T_UIDband:		return("UIDband");
	case T_briefID:		return("briefID");
	case T_nation:		return("nation");
	case T_shape:		return("shape");
	case T_bombs:		return("bombs");
	case T_type:		return("type");
	case T_duty:		return("duty");
	case T_form:		return("form");
	case T_move:		return("move");
	case T_wpact:		return("wpact");
	case T_angle:		return("angle");
	case T_bearing:		return("bearing");
	case T_asimuth:		return("asimuth");
	case T_range:		return("range");
	case T_hdg:			return("hdg");
	case T_pitch:		return("pitch");
	case T_roll:		return("roll");
	case T_fname:		return("fname");
	case T_setUID:		return("setUID");
	case T_setval:		return("setval");
	case T_random:		return("random");
	case T_select:		return("select");
	case T_repeat:		return("repeat");
	case T_linklist:	return("linklist");
	case T_everything:	return("everything");
	case T_event:		return("Event");			
	case T_start:		return("StartTime");		
	case T_window:		return("WindowTime");	
	case T_hours:		return("Hours");			
	case T_mins:		return("Mins");
	case T_secs:		return("Secs");
    case T_named:		return("Named");
	case T_object:		return("Object");
	case T_vertex:		return("Vertex");
	case T_face:		return("Face");
	case T_a:	  		return("A");
	case T_b:			return("B");
	case T_c:			return("C");
	case T_mtl:			return("Material");
	case T_icpt:		return("Intercept");
	case T_rangepc:		return("Range%");
	case T_leader:		return("Leader");
	case T_follower:	return("Follower");
	case T_list:		return("List");
	case T_vel:			return("Vel");
	case T_paintscheme:	return("Paint");
	case T_squadron:	return("Squad");
	}
	fbuff[6]=code/10+'0';
	fbuff[7]=code%10+'0';
	return(fbuff);
}
Bool	findspelling(char*	newname,TokenName*	&newtoken);

void	sayout(ufile	ofile,int	depth,char* rtype,TokenCode tokencode,char* anytext,Defined defined)
{

	TokenName*	tmptoken=NULL;
	if (defined==D_used)// && *anytext!='<')
	{
			findspelling(anytext,tmptoken);
			filenestlevel=1;
			printf("Undefined: %s. From %s(%i) Type: %s\n",
					anytext,names[tmptoken->srcfname],tmptoken->srcfline,getcodename(tokencode)
					);
	}
	if (ofile)
	{
		int i=0;
		while (i<depth)	fputc(wordbuff[i++],ofile);
		fprintf(ofile,"%-16s (%-8s) \"%s\"",rtype,getcodename(tokencode),anytext);
		if (tmptoken)
			fprintf(ofile,"		<-NOT DEFINED!\n");
		else
			fprintf(ofile,"\n");
}	}

void	sayout(ufile	ofile,int	depth,char* rtype,TokenCode tokencode,int anytext,Defined defined)
{
	if (defined==D_used)
	{
//DeadCode RDH 24Jun96 		TokenName*	tmptoken=NULL;
//DeadCode RDH 24Jun96 		char*	anytext;
//DeadCode RDH 24Jun96 		findspelling(anytext,tmptoken);
//DeadCode RDH 24Jun96 		filenestlevel=1;
//DeadCode RDH 24Jun96 		printf("Undefined: %s. From %s(%i) Type: %s\n",
//DeadCode RDH 24Jun96 				anytext,names[tmptoken->srcfname],tmptoken->srcfline,getcodename(tokencode)
//DeadCode RDH 24Jun96 				);
	}
	if (ofile)
	{
		int i=0;
		while (i<depth)	fputc(wordbuff[i++],ofile);
		fprintf(ofile,"%-16s (%-8s) =%00i 0x%04x",rtype,getcodename(tokencode),anytext,anytext);
		if (defined==D_used)
			fprintf(ofile,"		<-NOT DEFINED!\n");
		else
			fprintf(ofile,"\n");
}	}




//------------------------------------------------------------------------------
struct	DataInst
{
	TokenName*	tokentext;
	TokenCode	tokencode;//was:7
virtual	void	SaveTxt(ufile	ofile,int depth)=0;
virtual	void	PreSave(ufile	ofile,int depth)=0;
virtual void	PreSave2(ufile	ofile,int depth)=0;
virtual	void	SaveBin(ufile	ofile,int depth)=0;
virtual	DataInst*	FindNode(TokenCode	t,int	level)=0;
virtual	DataInst&	operator=(DataInst &src)=0;
};

//------------------------------------------------------------------------------
struct	NoValInst:public	DataInst
{
	NoValInst()	{};
	DataInst&	operator=(DataInst &src)
	{	return(NoValInst&) (DataInst::operator =(src));}
	void	SaveTxt(ufile	ofile,int depth)
	{sayout(ofile,depth,"Simple Data",tokencode,tokentext->TokenText(),tokentext->defined);}
	void	PreSave(ufile	/*ofile*/,int /*depth*/)	{;}
	void	PreSave2(ufile	/*ofile*/,int /*depth*/)	{;}
	void	SaveBin(ufile	/*ofile*/,int /*depth*/)	{;}
	DataInst*	FindNode(TokenCode	t,int	level);
};
//------------------------------------------------------------------------------
struct	FNameInst:public	DataInst
{
	TokenName*	filenumtext;
	DataInst*	filenumber;
	FNameInst()	{};
	DataInst&	operator=(DataInst &src)
	{	return(NoValInst&) (DataInst::operator =(src));}
	void	SaveTxt(ufile	ofile,int depth);
	void	PreSave(ufile	/*ofile*/,int /*depth*/)	{;}
	virtual	DataInst*	FindNode(TokenCode	t,int	level)	{return(NULL);}
	void	PreSave2(ufile	/*ofile*/,int /*depth*/);
	void	SaveBin(ufile	/*ofile*/,int /*depth*/)	{;}
};
//------------------------------------------------------------------------------
struct	IntegerInst:public	DataInst
{
	int	value;
	IntegerInst()	{tokencode=T_int;value=-1;tokentext=NULL;}
	void	SaveTxt(ufile	ofile,int depth);
DataInst&	operator=(DataInst &src)
	{return(operator=((IntegerInst&) src));}
IntegerInst&	operator=(IntegerInst &src);
	void	PreSave(ufile	/*ofile*/,int /*depth*/)	{;}
	void	PreSave2(ufile	/*ofile*/,int /*depth*/)	{;}
	void	SaveBin(ufile	ofile,int /*depth*/);
	DataInst*	FindNode(TokenCode	t,int	level);
};

//------------------------------------------------------------------------------
struct	LinkInst;
struct	LinkInst:public	DataInst
{
	DataRef		dataref;
	LinkInst	*sibling;
	LinkInst()
	{
		tokencode=T_linklist;tokentext=NULL;	//inherited
		dataref=NULL;sibling=NULL;				//child
	}
	void	SaveTxt(ufile	ofile,int depth);

DataInst&	operator=(DataInst &src)
	{return(operator=((LinkInst&) src));}
	LinkInst&	operator=(LinkInst &src);
	void	PreSave(ufile	ofile,int depth);
	void	PreSave2(ufile	ofile,int	depth);
	DataInst*	FindNode(TokenCode	t,int	level);
	void	SaveBin(ufile	ofile,int depth);
};



//------------------------------------------------------------------------------
struct ChainInst:public DataInst
{
	DataRef		dataref;
	ChainInst (TokenCode T)
	{
		tokencode=T;
		dataref=NULL;
		tokentext=NULL;
	}
	void	SaveTxt(ufile	ofile,int depth);
DataInst&	operator=(DataInst &src)
	{return(operator=((ChainInst&) src));}
	ChainInst&	operator=(ChainInst &src);
	void	PreSave(ufile	ofile,int depth);
	void	PreSave2(ufile	ofile,int	depth);
	DataInst*	FindNode(TokenCode	t,int	level);
	void	SaveBin(ufile	ofile,int depth);

};

//------------------------------------------------------------------------------

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PreSave
//Author		Jim Taylor
//Date			Fri 5 Apr 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
	void	LinkInst::PreSave(ufile	ofile,int depth)
	{
		LinkInst*	This=this;
		do{
			if	(This->dataref)
					This->dataref->PreSave(ofile,depth+1);

		}while ((This=This->sibling)!=NULL);
	}

	void	ChainInst::PreSave(ufile	ofile,int depth)
	{if (	(tokencode!=T_linklist)
		 && (tokencode!=T_nint)
		 && (tokencode!=T_int)	)

		if (	(tokencode == T_target)
//DeadCode JIM 22Apr96 			||	(tokencode == T_leader)	//leader now has target field
			)
		{
			DataInst	*tmpptr,*lookptr;						//JIM 28Mar96
			LinkInst	*tmplink;								//JIM 28Mar96
			ChainInst	*tmpchain;								//JIM 28Mar96
																//JIM 28Mar96
			lookptr = dataref;									//JIM 28Mar96
			if 		(lookptr->tokencode==T_airgrp)				//JIM 28Mar96
				lookptr = lookptr->FindNode(T_itemA,5);			//JIM 28Mar96
			elseif 	(lookptr->tokencode==T_gndgrp)				//JIM 28Mar96
				lookptr = lookptr->FindNode(T_itemG,5);			//JIM 28Mar96
			if (lookptr==NULL)									//JIM 28Mar96
			{													//JIM 28Mar96
				EmitSysErr("No mobile items in group??");		//JIM 28Mar96
			}													//JIM 28Mar96
			tmpptr = lookptr->FindNode(T_setUID,3);				//JIM 28Mar96
																//JIM 28Mar96
			if (tmpptr == NULL)									//JIM 28Mar96
			{													//JIM 28Mar96
				// If it expected, then add setUID...			//JIM 28Mar96
																//JIM 28Mar96
				TokenCode	tmptoken;							//JIM 28Mar96
																//JIM 28Mar96
				switch(lookptr->tokencode)						//JIM 28Mar96
				{												//JIM 28Mar96
				case T_itemA:									//JIM 28Mar96
				case T_itemG:									//JIM 28Mar96
				case T_itemS:									//JIM 28Mar96
				case T_waypoint:								//JIM 28Mar96
				{
					TokenName 	*newtoken;
					char		buffer[10];

					tmpchain = (ChainInst*) lookptr;
					tmplink = (LinkInst*) tmpchain->dataref;
					Assert(tmplink->tokencode == T_linklist);

					while(tmplink->sibling)
						tmplink = tmplink->sibling;

					tmplink = (LinkInst*)
						(tmplink->sibling = new LinkInst);

					Assert(tmplink&&"memory!");

					strcpy(wordbuff,"UI_");
					strcat(wordbuff,utoa(newuidcount,buffer,10));

					findspelling(wordbuff,newtoken);

					tmplink->dataref = 
						newtoken->instance = itemlevel_setUID(NULL,newtoken);

					newtoken->defined=D_defined;
					newtoken->usage=U_structrtn;
					newtoken->tokencode=T_setUID;

					newuidcount = newuidcount + 1;
					dataref=tmplink->dataref;							//JIM 27Mar96
				}
				break;
				case T_setUID:
				break;
				}
			}
			else
				dataref = tmpptr;
		}
		elseif
			(dataref)
				dataref->PreSave(ofile,depth+1);
	}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PreSave2
//Author		Jim Taylor
//Date			Fri 5 Apr 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	LinkInst::PreSave2(ufile	ofile,int	depth)
{
	LinkInst	*This = this;
	int			uidindex;
	int			count;
	ChainInst	*setuidnode, *uidbandnode;
	int			uidval;

	do
	{
		setuidnode = (ChainInst*) This->dataref;

		if (	(setuidnode)
			&&	(setuidnode->tokencode == T_setUID)
			&&	(setuidnode->dataref->tokencode == T_int)
			&&	(((IntegerInst*) setuidnode->dataref)->value == -1))
		{
			setuidnode->tokentext->defined=D_defused; //if we get here we guarantee to set a value
			uidbandnode = (ChainInst*) this->FindNode(T_UIDband,5);

			if (uidbandnode)
				uidval= ((IntegerInst*) uidbandnode->dataref)->value;
			else
			{
				switch(parentcode)
				{
				case T_itemA:
					uidval = RedAcBAND;
				break;
				case T_itemG:
					uidval = RedGroundMobileBAND;
				break;
				case T_itemS:
					uidval = RedCivilianBAND;
				break;
				case T_waypoint:
					uidval = WayPointBAND;
				break;
				}
			}

			// Search table for UID
			
			uidindex = -1;
			count = 0;

			while(count < uidtablesize)
			{
				if (uidtable1[count] == uidval)
				{
					uidindex = count;
					break;
				}

				count = count + 1;
			}

			if (uidindex == -1)
				EmitSysErr("UIDband %1 not known!",uidval);

			if (uidtable2[uidindex] == uidtable1[uidindex])
				EmitSysErr("UIDband full! Number %x",uidval);

			((IntegerInst*) setuidnode->dataref)->value = uidtable2[uidindex];
			fprintf(UIDlistfile,"		%s=0x%04x,\n",setuidnode->tokentext->TokenText(),uidtable2[uidindex]);
			uidtable2[uidindex]--;
		}
		else
		if	(This->dataref)
				This->dataref->PreSave2(ofile,depth+1);

	}while ((This=This->sibling)!=NULL);
}
	void	ChainInst::PreSave2(ufile	ofile,int	depth)
	{
		if (	(tokencode == T_itemA)
			||	(tokencode == T_itemG)
			||	(tokencode == T_itemS)
			||	(tokencode == T_waypoint))
			parentcode = tokencode;
		else
		if (	tokencode == T_setUID
			&&	(dataref->tokencode == T_int)
			&& 	(((IntegerInst*) dataref)->value == -1)
			)	//if we get here we have not set a value yet.
			tokentext->defined=D_used;
		if (dataref)
			dataref->PreSave2(ofile,depth+1);
	}

//------------------------------------------------------------
void	FNameInst::PreSave2(ufile	/*ofile*/,int /*depth*/)
{
	IntegerInst	*tmp=(IntegerInst*)filenumber;
	if (tmp)
	{

		int i=tmp->value>>8;
		if (++Battle_Dirs[i].dirnum>255)
			EmitSysErr("Too many files in directory: %s",Battle_Dirs[i].dirname);
		tmp->value+=Battle_Dirs[i].dirnum;
		char*	s1=tokentext->TokenText();
		if (*s1<='\"')	s1++;
		char*	s2=s1;
		while (*s2>'\"')	s2++;
		*s2=0;
		if (filenumtext)
			fprintf(Battle_Dirs[i].openhandle,"\t%s\t%s\n",
				s1,filenumtext->tokentext);
		else
			fprintf(Battle_Dirs[i].openhandle,"\t%s\n",
				s1);
}	}



//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SaveTxt
//Author		Jim Taylor
//Date			Thu 4 Apr 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
	void	FNameInst::SaveTxt(ufile	ofile,int depth)
	{
		RECURSECHK
		{
			sayout(ofile,depth,"File Name",tokencode,tokentext->TokenText(),tokentext->defined);
			string s=tokentext->TokenText();
			while (*s && *s!='.') s++;
			if (s-tokentext->TokenText()>8)
			{
				s=tokentext->TokenText();
				printf("File name truncated. %s --> %c%c%c%c%c%c%c%c (%s)\n",
					s,s[0],s[1],s[2],s[3],s[4],s[5],s[6],s[7],filenumtext->TokenText());
			}

			sayout(ofile,depth,"File Equate",tokencode,filenumtext->TokenText(),tokentext->defined);
			if (filenumber)
				filenumber->SaveTxt(ofile,depth+1);
		}
	}

	void	IntegerInst::SaveTxt(ufile	ofile,int depth)
	{
		RECURSECHK
		{
			if (tokencode==T_int)
				sayout(ofile,depth,"Integer Data",tokencode,value,tokentext->defined);
	 		elseif (tokencode==T_nint)
				sayout(ofile,depth,"Integer Data",tokencode,-value,tokentext->defined);
	 		else
				sayout(ofile,depth,"Integer Bad!",tokencode,value,tokentext->defined);
	}	}

	void	LinkInst::SaveTxt(ufile	ofile,int depth)
	{
		RECURSECHK
		{
			LinkInst*	This=this;
			do{
				if (This->tokencode==T_linklist)
					sayout(ofile,depth,"Link",This->tokencode,This->tokentext->TokenText(),This->tokentext->defined);
				else
					sayout(ofile,depth,"Bad Link",This->tokencode,This->tokentext->TokenText(),This->tokentext->defined);
				if (This->sibling)
					wordbuff[depth]='|';
				else
					wordbuff[depth]=' ';
				wordbuff[depth+1]=' ';
				if (This->dataref)
					This->dataref->SaveTxt(ofile,depth+1);
//DeadCode RJS 31Jan96 			if (sibling)
//DeadCode RJS 31Jan96 				sibling->SaveTxt(ofile,depth);
			}while ((This=This->sibling)!=NULL);
	}	}

	void	ChainInst::SaveTxt(ufile	ofile,int depth)
	{
		RECURSECHK
		{
			if (	(tokencode!=T_linklist)
			 && (tokencode!=T_nint)
			 && (tokencode!=T_int)	)
				sayout(ofile,depth,"Chain",tokencode,tokentext->TokenText(),tokentext->defined);
			else
				sayout(ofile,depth,"Bad Chain",tokencode,tokentext->TokenText(),tokentext->defined);
			wordbuff[depth]=' ';
			wordbuff[depth+1]=' ';
			if (dataref)
			dataref->SaveTxt(ofile,depth+1);
	}	}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SaveBin
//Author		Jim Taylor
//Date			Fri 5 Apr 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
	void	IntegerInst::SaveBin(ufile	ofile,int /*depth*/)
	{
		fputc(tokencode,ofile);
		fwrite(&value,4,1,ofile);
	}

	void	LinkInst::SaveBin(ufile	ofile,int depth)
	{
	if (dataref)
		dataref->SaveBin(ofile,depth+1);
	if (sibling)
		sibling->SaveBin(ofile,depth);
	}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FindNode
//Author		Jim Taylor
//Date			Thu 4 Apr 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
	DataInst*	ChainInst::FindNode(TokenCode	t,int	level)
	{
		if ((this != NULL) && (level > 0))
			if (tokencode == t)
				return(this);
			else
				return(dataref->FindNode(t,level-1));
		elser
			return(NULL);
	}

	DataInst*	IntegerInst::FindNode(TokenCode	t,int	level)
	{
		if (	(tokencode == t)
			&&	(level != 0)	)
			return(this);
		else
			return(NULL);
	}

	DataInst*	NoValInst::FindNode(TokenCode	t,int	level)
	{
		if (	(tokencode == t)
			&&	(level != 0)	)
			return(this);
		else
			return(NULL);
	}

	DataInst*	LinkInst::FindNode(TokenCode	t,int	level)
	{

		LinkInst	*This = this;

		while ((This != NULL) && (level > 0))
		{
			if (This->tokencode == t)
				return(This);
			else
			{
DataInst*		tmpptr = This->dataref->FindNode(t,level-1);

				if (tmpptr)
					return(tmpptr);
			}

			This = This->sibling;
		}
			
		return(NULL);
	}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		operator=
//Author		Jim Taylor
//Date			Thu 4 Apr 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
LinkInst&	LinkInst::operator=(LinkInst &src)
	{
	dataref=src.dataref;sibling=src.sibling;
	return(LinkInst&) (DataInst::operator =(src));
	}

IntegerInst&	IntegerInst::operator=(IntegerInst &src)
	{
	value=src.value;
	return(IntegerInst&) (DataInst::operator =(src));
	}

DataInst&	DataInst::operator=(DataInst &src)
	{
		if (src.tokentext)
			tokentext=src.tokentext;
		if (tokencode!=src.tokencode)
			EmitSysErr("Internal error - copying between different types!");
		return	(*this);
	}

ChainInst&	ChainInst::operator=(ChainInst &src)
	{
	dataref=src.dataref;
	return(ChainInst&) (DataInst::operator =(src));
	}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CountLinkInsts
//Author		Jim Taylor
//Date			Mon 4 Dec 1995
//
//Description	Counts the number of link instances in the list
//
//Inputs		pointer to list
//
//Returns		count
//
//------------------------------------------------------------------------------
int		CountLinkInsts(LinkInst* ref)
{
int	i=0;
	while (ref)
	{
		if (ref->dataref)	//ignore empty entries
			if (ref->dataref->tokencode==T_linklist)
				i+=CountLinkInsts((LinkInst*)	ref->dataref);
			elseif (	ref->dataref->tokencode!=T_fname
					&&	ref->dataref->tokencode!=T_level
					)
				i++;
			else;	//filename entries are ignored
		ref=ref->sibling;
	}
	return(i);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FindFileNameInBF
//Author		Jim Taylor
//Date			Mon 4 Dec 1995
//
//Description	Searches tree for T_filename
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
UFILE*		FindFileNameInBF(LinkInst*	ref)
{
	UFILE*	s;
	while (ref)
	{
		if (ref->dataref)	//ignore empty entries
			if (ref->dataref->tokencode==T_linklist)
			{
				s=FindFileNameInBF((LinkInst*)	ref->dataref);
				if (s)	return(s);			//EXIT POINT
			}
			elseif (ref->dataref->tokencode==T_bfsave)
			{
				s=FindFileNameInBF((LinkInst*)	ref->dataref);
				if (s)	return(s);			//EXIT POINT
			}
			elseif (ref->dataref->tokencode==T_fname)
			{

//TempCode JIM 03Apr96 				fwrite("	",1,1,filelistfile);
//TempCode JIM 03Apr96 				FNameInst*	F=(FNameInst*) (DataInst*) ref->dataref;
//TempCode JIM 03Apr96 				if (F->tokentext->TokenText()[0]=='"')
//TempCode JIM 03Apr96 					fwrite(&F->tokentext->TokenText()[1],1,strlen(F->tokentext->TokenText())-2,filelistfile);
//TempCode JIM 03Apr96 				else
//TempCode JIM 03Apr96 					fwrite(&F->tokentext->TokenText()[0],1,strlen(F->tokentext->TokenText()),filelistfile);
//TempCode JIM 03Apr96 				fwrite("	",1,1,filelistfile);
//TempCode JIM 03Apr96 				if (F->filenumtext->TokenText()[0]!='<')
//TempCode JIM 03Apr96 					if (F->filenumtext->TokenText()[0]=='"')
//TempCode JIM 03Apr96 						fwrite(&F->filenumtext->TokenText()[1],1,strlen(F->filenumtext->TokenText())-2,filelistfile);
//TempCode JIM 03Apr96 					else
//TempCode JIM 03Apr96 						fwrite(&F->filenumtext->TokenText()[0],1,strlen(F->filenumtext->TokenText()),filelistfile);
//TempCode JIM 03Apr96 				fwrite("\n",1,1,filelistfile);
				char* s1=ref->dataref->tokentext->tokentext;
				while (*s1<='\"')	s1++;
				char* s2=s1;
				while (*s2>'\"')	s2++;
				*s2=0;
				int dirnum=				((IntegerInst*)
									((FNameInst*)
									ref->dataref)
										->filenumber)
											->value;
				char* s3=Battle_Dirs[dirnum>>8].dirname;
				return(writefile(s1,'b',s3));
			}
			else;	//filename entries are what we want
		ref=ref->sibling;
	}
	return(NULL);
}

//DeadCode DAW 08Apr96 ufile	writefile(char*	name,char mode);
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ChainInst::SaveBin
//Author		Jim Taylor
//Date			Mon 4 Dec 1995
//
//Description	This is the central dispatch, so contains all the special cases:
//				1) We don't save anything if we have an empty file
//						-unless its a bfsave - in which case we open the file!
//				2) We cope with LinkInst here to reduce the data output
// 						
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
	void	ChainInst::SaveBin(ufile	ofile,int depth)
	{
		if (ofile)
			switch (tokencode)
			{
			ACCEPTCASELIST
				fputc(tokencode,ofile);
				if (dataref && dataref->tokencode==T_linklist)
				{
					fputc(T_linklist,ofile);
					fputc(CountLinkInsts((LinkInst*) dataref),ofile);
				}
				if (dataref)
					dataref->SaveBin(ofile,depth+1);
				else
					fputc(-1,ofile);
			break;
			case	T_fname:
			case	T_level:
				//Ignoring filenames at this point!
			break;
			default:
				EmitSysErr("Not expecting that symbol in chain node: %s",getcodename(tokencode));
			}
		elseif (tokencode==T_everything)
			dataref->SaveBin(ofile,depth+1);
		elseif (tokencode==T_bfsave)
		{	//need to find a filename entry
			UFILE*		MyTmpFile=FindFileNameInBF((LinkInst*) dataref);
//DeadCode JIM 04Apr96 string		filename=FindFileNameInBF((LinkInst*) dataref);
			if (MyTmpFile)
			{
//DeadCode JIM 04Apr96 				if (	(filename[0]=='\"') || (filename[0]=='\'')	)
//DeadCode JIM 04Apr96 				{	//remove quotes by skipping forward and truncating
//DeadCode JIM 04Apr96 string				t2=filename++;
//DeadCode JIM 04Apr96 					while ((*t2!='\"') && *(t2) && (*t2!='\''))	t2++;
//DeadCode JIM 04Apr96 					t2[0]=0;
//DeadCode JIM 04Apr96 				}
//DeadCode JIM 04Apr96 
//DeadCode JIM 04Apr96 ufile			MyTmpFile=writefile(filename,'b');
				//save length info		
					fprintf(MyTmpFile,"BATTLEFIELD %s\032\n",(string) (__DATE__));
					fputc(0,MyTmpFile);
					fputc(T_bfsave,MyTmpFile);
					fputc(T_linklist,MyTmpFile);
					fputc(CountLinkInsts((LinkInst*) dataref),MyTmpFile);
	
				dataref->SaveBin(MyTmpFile,depth+1);
				fclose(MyTmpFile);
				topwsrcfname--;
			}
			else	//Currently error if no name. Later, just ignore!
				EmitSysErr("No filename in BFSave. The concept of partial BFs not implemented!");
		}
		else
			;//Anything else declared at top level goes in list, but is ignored!
	}
//------------------------------------------------------------------------------
class	LPair
{
LinkInst	*head,
			*tail;
public:
	LPair()
		{tail=head=new LinkInst;
		Assert(head&&"Memory!");}
	Add(DataInst	*d)
		{
			tail->sibling=new LinkInst;
			tail=tail->sibling;
			tail->sibling=NULL;
			tail->dataref=d;
		}
ChainInst*
	Code(TokenCode T,TokenName *name)
		{
ChainInst*	tmp=new ChainInst(T);
			Assert(tmp&&"Memory!");
			tmp->tokentext=name;
			tmp->dataref=head->sibling;
			delete	head;
			head=NULL;
			tail=NULL;
			return(tmp);
		}
};

//------------------------------------------------------------------------------
//Add your data structures and static instances here!


ChainInst	*treeroot=NULL;
LPair	 	treelist;
//------------------------------------------------------------------------------


///////////////////////
//
// Black box parser starts here
//
//
/*
  Functions provided:

ufile	readfile(char*	name)
	Opens named file for reading, remembers name, and resets line count
ufile	writefile(char*	name,char mode)
	Opens named file for reading, remembers name, and resets line count

Bool	testspelling(char*	newname,TokenName*	&newtoken)
	Checks for spelling entry in dictionary. Returns newtoken, or FALSE.
	Integers return FALSE.

Bool	findspelling(char*	newname,TokenName*	&newtoken)
Bool	findspelling(file	ifile,TokenName*	&newtoken)
	Checks for spelling entry in dictionary. If not exist then creates entry.
	Returns TRUE if already known. False if new entry, and tokencode=T_unknown.
	Integers return FALSE, but tokencode=T_int and instance filled in.

void	addspelling(TokenInit tokentoadd)
	Adds a TokenInit to the dictionary.

void	addfixedspellings()
	Adds all entries in fixedtokens array.

Bool	stripwhite(ufile	ifile)
	Strips whitespace from input file. Returns FALSE if EOF.

string	getword(file	ifile)
	Gets a token from the file. Currently returns NULL if EOF.
	In future, this will EmitSysErr if EOF. Be warned!!!!

Bool	scantoword(ufile	ifile,UsageType	usage,TokenCode tokencode)
	Discards input up to matching token.
	Intended for error recovery and enum file skipping. Useless.

void	GetTypeAndValue(ufile	ifile,
		TokenName* &type,TokenName* &newname,TokenName* &value,TokenName* &sep)
	Parses lines in following formats to return type, newname, value and sep:
		type newname = value ,		
		type newname = value }
		type newname = value *
		type newname = {			-->value=sep={
		[newname =] is optional 	-->newname=NULL
		[type] is optional if value unique --> type=value

Bool	getlistseparator(TokenCode	*sep)
	if sep is '{' or '*' then reads additional separtor
	returns FALSE if sep is ','
	returns TRUE  if sep is '}'

void	setupnewnamereference(tokencode *newname,DataInst* &retval);
	Handle an assignment to a type on return from it's creation
	If name already exists then first record of retval is 
	copied into existing space and deleted. Retval ptr is modified.

DataInst*	initchainref(TokenName *pvalue,TokenCode	T)
	Define a default chainref type to an undefined symbol

void	ProcessEnumStatement(ufile	ifile)
	Processes body of enum statement after enum keyword.
	Only handles registered enums. Ignores rest.
	
void	ProcessConstStatement(ufile	ifile)
	Processes body of const statement after const keyword.
	Only handles registered enums. Ignores rest.

void	interpretenums(ufile	ifile)
	Searches the open file for recognised enum and const statements.
	Closes file on exit.

void	add3dsentry(string	name,int	X,int	Y,int	Z,ShapeNum	S)
	Adds name to dictionary as a 3dstudio tree

void	addglobalentry(string	name,TokenCode T)
	Adds global name to dictionary and aligns with code T
*/
///////////////////////
//
// Black box parser code starts here
//
//
string	getword(file	ifile);
//------------------------------------------------------------------------------
char*	safetext(char* oldtext);
file	readfile(char*	name)
{
	names[currsrcfname=++topsrcfname]=safetext(name);
	currsrcfline=1;
	if (currsrcfname==MaxFileCount)
		EmitSysErr("Max input files exceeded (%i)!",MaxFileCount);
	file	myfile=fopen(name,"rt");
		if (myfile==NULL)
			EmitSysErr("Error opening file!");
	return(myfile);
}

char	filebuff[80];
int	fileend;
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		setwritefile
//Author		Jim Taylor
//Date			Tue 5 Dec 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	setwritefile(char* path)
{
	fileend=0;
	while (*path)	filebuff[fileend++]=*(path++);
	if (	(filebuff[fileend-1]!=':')
		&&	(filebuff[fileend-1]!='\\')	)
		filebuff[fileend++]='\\';
}
//------------------------------------------------------------------------------
ufile	writefile(char*	name,char mode,char* dirname)
{
	if (dirname)
		setwritefile(dirname);
	names[currsrcfname=++topwsrcfname]=name;
	currsrcfline=0;
	if (currsrcfname==MaxTotFileCount)
		EmitSysErr("Max files exceeded (%i)!",MaxTotFileCount);
	int i=fileend;
	while (*name)
		filebuff[i++]=*(name++);
	filebuff[i++]=0;
	ufile	myfile=fopen(filebuff,mode);
	if (myfile==NULL)
		EmitSysErr("Error opening file!");
	return(myfile);
}
//------------------------------------------------------------------------------
struct	TokenSpell:public	DataInst
{		
	TokenName*	spelling[96];

	TokenSpell()
	{
		tokencode=T_sortentry;
		tokentext=NULL;
		int i=96;
		while (i--)
			spelling[i]=NULL;
	}
DataInst&	operator=(DataInst&)
	{
		EmitSysErr("Can't copy TokeSpell records");
		return(*this);
	}
void	SaveTxt(ufile	ofile,int	depth)
	{
		int i=' '-1;
		while (++i<'~')
			if (spelling[i-' '])
			{	
			 	sayout(ofile,depth,(char*) (&i),tokencode,spelling[i-' ']->TokenText(),D_defused);
				spelling[i-' ']->SaveTxt(ofile,depth+1);
			}
	}

	void	PreSave(ufile	/*ofile*/,int /*depth*/)
	{;}
	void	PreSave2(ufile	/*ofile*/,int /*depth*/)
	{;}
	DataInst*	FindNode(TokenCode,int)
	{
		return(NULL);
	}
	void	SaveBin(ufile	/*ofile*/,int /*depth*/)
	{
		EmitSysErr("Can't binary save the dictionary! Neat idea, though!");
	}

};
//------------------------------------------------------------------------------
void	TokenName::SaveTxt(ufile	ofile,int	depth)
	{
		if (instance==NULL)
			sayout(ofile,depth,"<leaf>",tokencode,TokenText(),D_defused);
		else
			instance->SaveTxt(ofile,depth);
	}
//------------------------------------------------------------------------------
//////////////
TokenSpell	FirstSpell;
TokenName	statictoken;
IntegerInst	staticinteger;

//////////////

Bool	testspelling(char*	newname,TokenName*	&newtoken)			//returns TRUE if already known
{

TokenSpell	*spellhunt=&FirstSpell;
int			compcharnum=0;
char		compchar;
newtoken=NULL;
	compchar=newname[compcharnum];
	if ((compchar>='0')&&(compchar<='9'))
		return(FALSE);
	elser
	{
		while  (	(compchar)
		   		&&	(spellhunt->spelling[compchar-32])
		   		&&	(spellhunt->spelling[compchar-32]->tokencode==T_sortentry)
				)
			{
				spellhunt=(TokenSpell*) spellhunt->spelling[compchar-32]->instance;
				compchar=newname[++compcharnum];
			}
		//any one of 3 end conditions may have occured.
	
		if (compchar) compchar-=32;
		if (spellhunt->spelling[compchar]==NULL)	//need to create an entry
			return(FALSE);

		//spelling correct up to now, but end of dictionary.
		//compare onward, but remember current index.
int		fwdcharnum=compcharnum;
char	*targ=spellhunt->spelling[compchar]->tokentext;
		while (newname[fwdcharnum] && (newname[fwdcharnum]==targ[fwdcharnum]))
			fwdcharnum++;
		if (newname[fwdcharnum]==targ[fwdcharnum])
		{
			newtoken=spellhunt->spelling[compchar];
			return(TRUE);
		}
		return(FALSE);
	}
}

//DeadCode JIM 04Dec95 char	wordbuff[80]={0};

char*	safetext(char* oldtext)
{
 	if (oldtext!=wordbuff)
		return(oldtext);
char*
	retval=new char [strlen(oldtext)+1];
	Assert(retval&&"Memory!");
	strcpy(retval,oldtext);
	return(retval);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		findspelling
//Author		Jim Taylor
//Date			Thu 23 May 1996
//
//Description	Finds a spelling in the dictionary and adds if necessary
//				Integers and negative integers make a new integerinst record
//				hooked off the statictoken dictionary entry.
//				Negated symbols require looking up the symbol 
//				and then creating a negated equivalent
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	findspelling(char*	newname,TokenName*	&newtoken)	//returns TRUE if already known
{
TokenSpell
	*spellhunt=&FirstSpell;
int	compcharnum=0;
char
	compchar=newname[0];
    if (compchar=='-' && newname[1] >='A')	//negated name
	{
		TokenName* srctoken;
		if (testspelling(newname+1,srctoken)==FALSE)
			EmitSysErr("Expecting named int to negate, but got unknown %s",newname+1);

		DataInst* link=(DataInst*) srctoken->instance;
		while (link->tokencode==T_count)
			link=((LinkInst*)link)->dataref;

		if (link->tokencode!=T_nint	&& link->tokencode!=T_int)
			EmitSysErr("Expecting named int to negate, but %s is type %s",
				newname,getcodename(link->tokencode));
		else
		{
			IntegerInst* src=(IntegerInst*)link;
		 	IntegerInst* trg=new IntegerInst;Assert(trg&&"memory!");
			*trg=*src;
			newtoken=&statictoken;
			statictoken.tokentext=newname;
			statictoken.usage=U_value;
			statictoken.defined=D_defined;
			statictoken.srcfline=(UWord) currsrcfline;
			statictoken.srcfname=(UWord) currsrcfname;
			statictoken.instance=trg;
			if (src->tokencode==T_nint)
				statictoken.tokencode=
					trg->tokencode=T_int;
			else
				statictoken.tokencode=
					trg->tokencode=T_nint;
			return(TRUE);
		}
	}
	elser
	if (((compchar>='0')&&(compchar<='9'))||(compchar=='-'))
	{
		newtoken=&statictoken;
		statictoken.tokentext=newname;
		statictoken.usage=U_value;
		statictoken.defined=D_defined;
		statictoken.srcfline=(UWord) currsrcfline;
		statictoken.srcfname=(UWord) currsrcfname;
		statictoken.instance=new IntegerInst;Assert(statictoken.instance&&"memory!");

		if (compchar=='-')
		{
			statictoken.instance->tokencode=
				statictoken.tokencode=T_nint;
			compchar=*(++newname);
			if (!((compchar>='0')&&(compchar<='9')))
				EmitSysErr("Expecting digit after '-', but found %s",newname);
		}
		else
			statictoken.instance->tokencode=
				statictoken.tokencode=T_int;


int		base=(compchar=='0')?8:10;
		compcharnum=compchar-'0';
		compchar=*++newname;
		if ((compchar=='x')||(compchar=='X'))
		{
			base=16;
			compchar=*++newname;
		}
		while (compchar)
		{
			if ((compchar>'9') || (compchar<'0'))
				if (compchar<'A')
					EmitSysErr("Number not terminated correctly: %s",statictoken.tokentext);
				else
					compchar=(char) ((compchar&0x1f)+9);
			else
				compchar=(char) (compchar&0x0f);
			if (compchar>=base)
				EmitSysErr("Number not terminated correctly: %s",statictoken.tokentext);
			compcharnum=compcharnum*base+compchar;
			compchar=*++newname;
		}
		statictoken.tokentext=NULL;
		((IntegerInst*) statictoken.instance)->value=compcharnum;
		return(FALSE);
	}
	elser
	{
		while  (	(compchar)
		   		&&	(spellhunt->spelling[compchar-32])
		   		&&	(spellhunt->spelling[compchar-32]->tokencode==T_sortentry)
				)
			{
				spellhunt=(TokenSpell*) spellhunt->spelling[compchar-32]->instance;
				compchar=newname[++compcharnum];
			}
		//any one of 3 end conditions may have occured.
	
		if (	(compchar==0)										//end of source
			&&	(spellhunt->spelling[0])							//entry in dictionary
			&&	(spellhunt->spelling[0]->tokentext[compcharnum]==0)	//that is ended here
			)
		{
			newtoken=spellhunt->spelling[0];		
			return(TRUE);
		}
		if (compchar) compchar-=32;
	
		if (spellhunt->spelling[compchar]==NULL)	//need to create an entry
		{
			newtoken=spellhunt->spelling[compchar]=new TokenName;Assert(newtoken&&"memory!");
			newtoken->tokentext=safetext(newname);
			newtoken->srcfline=(UWord) currsrcfline;
			newtoken->srcfname=(UWord) currsrcfname;
			return(FALSE);
		}
		//spelling correct up to now, but end of dictionary.
		//compare onward, but remember current index.
	int	fwdcharnum=compcharnum;
	char	*targ=spellhunt->spelling[compchar]->tokentext;
		while (newname[fwdcharnum] && (newname[fwdcharnum]==targ[fwdcharnum]))
			fwdcharnum++;
		if (newname[fwdcharnum]==targ[fwdcharnum])
		{
			newtoken=spellhunt->spelling[compchar];
			return(TRUE);
		}
		//they differ at some point. fwdcharnum says where, but don't matter!
	char	oldspellingletter;
		do
		{	//Make dictionary pages for all common letters. 1st letter is common.
			compcharnum++;
	TokenSpell*
			newspellpage=new TokenSpell;	Assert(newspellpage&&"memory!");
			oldspellingletter=targ[compcharnum];
			if (oldspellingletter)	oldspellingletter-=32;
			newspellpage->spelling[oldspellingletter]=spellhunt->spelling[compchar];
			spellhunt->spelling[compchar]=new TokenName;	Assert(spellhunt->spelling[compchar]&&"memory!");
			spellhunt->spelling[compchar]->tokentext=safetext(newname);
			spellhunt->spelling[compchar]->tokencode=T_sortentry;
			spellhunt->spelling[compchar]->srcfname=0;
			spellhunt->spelling[compchar]->srcfline=0;
			spellhunt->spelling[compchar]->instance=newspellpage;

			spellhunt=newspellpage;
			compchar=newname[compcharnum];
			if (compchar) compchar-=32;
		} while (compchar==oldspellingletter);

		//now, the common letters have been shared. 
		//add newname to current spellhunt
		spellhunt->spelling[compchar]=newtoken=new TokenName;	Assert(newtoken&&"memory!");
		spellhunt->spelling[compchar]->tokentext=safetext(newname);
		spellhunt->spelling[compchar]->tokencode=T_unknown;
		spellhunt->spelling[compchar]->srcfline=(UWord) currsrcfline;
		spellhunt->spelling[compchar]->srcfname=(UWord) currsrcfname;

		return(FALSE);
	}
}

Bool	findspelling(file	ifile,TokenName*	&newtoken)	//returns TRUE if already known
{
	return(findspelling(getword(ifile),newtoken));
}

void	addspelling(TokenInit tokentoadd)
{
TokenName	*newtoken;
	currsrcfline++;
	if (findspelling(tokentoadd.tokentext,newtoken))
		EmitSysErr("Already in dictionary: (%s) ",tokentoadd.tokentext);
	newtoken->usage=tokentoadd.usage;
	newtoken->tokencode=tokentoadd.tokencode;
	newtoken->defined=D_defined;
//DeadCode JIM 27Nov95 	newtoken->srcfname=(UWord) currsrcfname;
//DeadCode JIM 27Nov95 	newtoken->srcfline=(UWord) currsrcfline;
	newtoken->instance=NULL;
}

	
void	addfixedspellings()
{
TokenInit	*newtoken=fixedtokens;
	while (newtoken->tokentext[0])
		addspelling(*(newtoken++));
}

/////////////////////////////////////////////////////
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		stripwhite
//Author		Jim Taylor
//Date			Mon 27 Nov 1995
//
//Description	Strips out any whitespace characters, and counts carriage returns
//
//Inputs		
//
//Returns		returns FALSE if EOF read
//				returns TRUE if more symbols to follow
//------------------------------------------------------------------------------
Bool	stripwhite(file	ifile)
{
char c;
	for(;;)
	{
		if (feof(ifile))	return (FALSE);
		c=(char) fgetc(ifile);
		if (feof(ifile))	return (FALSE);
		if (c=='/')
		{
			if (feof(ifile))	return (FALSE);
			c='\n';
			while (fgetc(ifile)!=c)		//comments: single slash - to end of line
				if (feof(ifile))	return (FALSE);
		}
string	p1=whitechars;
		if (c=='\n')
			currsrcfline++;
		else
			while ((c!=*p1) && *p1) p1++;
	breakif (*p1==0);
	}
 if (feof(ifile))	return (FALSE);
 ungetc(c,ifile);
 return(TRUE);
}
/////////////////////////////////////////////////////

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		getword
//Author		Jim Taylor
//Date			Mon 27 Nov 1995
//
//Description	Gets 1 symbol... either a word or punctuation.
//				I think this routine can error if it runs out of data,
//				because the caller should know when to expect EOF,
//				but not yet!
//				Negation of symbols is not handled here.
//				
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
string	getword(file	ifile)
{	//2 stages to getting a word:
	//	1) leading white removal
	//	2) copy to terminator
	//1) leading white removal
char c;
string
	myword=NULL;
	if (!stripwhite(ifile))
		return(NULL);
	elser
	{
	 	c=(char) fgetc(ifile);
string 	outbuf=wordbuff;
		myword=outbuf;
		//test for punctuation (ok... spc/tab in there as well!)
string	p1=endchars;
		while ((c!=*p1) && *p1) p1++;	
		if (*p1)
		{	//punctuation only 1 char long...
			*(outbuf++)=c;
			*outbuf=0;
			return (myword);
		}
		elser
		{	
			for(;;)
			{	//build string up to next punctuation or white
				*(outbuf++)=c;
				*outbuf=0;		//handle early return for eof
				c=(char) fgetc(ifile);
				//EOF during a word read is not an error, really
				if (feof(ifile))	return (myword);
string			p1=endchars;
				while ((c!=*p1) && *p1) p1++;
			breakif (*p1);
			}
			ungetc(c,ifile);
			return (myword);
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		scantoword
//Author		Jim Taylor
//Date			Mon 27 Nov 1995
//
//Description	Scan forward to a particular symbol.
//				Intended for error recovery.
//				Not very useful in practice, unfortunately.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	scantoword(file	ifile,UsageType	usage,TokenCode tokencode)
{
char*	nextword;
TokenName	*tokenname;
	while((nextword=getword(ifile))!=NULL)
	 	if (testspelling(nextword,tokenname))
			if (	(tokenname->usage==usage)
				&&	(tokenname->tokencode==tokencode)
				)
				return (TRUE);
	return (FALSE);
}

//------------------------------------------------------------------------------

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetTypeAndValue
//Author		Jim Taylor
//Date			Tue 28 Nov 1995
//
//Description	
//				This routine processes:				into:
//				value	of known enum type	,/}		value	NULL	value  sep
//				type value ,/}						type	NULL	value  sep
//				type name = value ,/}				type	name	value  sep
//				type {								type	NULL	T_brktopen
//				type name = {						type	name	T_brktopen
//				TYPE	=	{
//				TYPE	=	value	,/}
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	GetTypeAndValue(file	ifile,TokenName* &type,TokenName* &newname,TokenName* &value,TokenName* &sep)
{
//DeadCode JIM 30Nov95 char*	nextword;
	findspelling(ifile,type);
	if (	(type->usage==U_value)
		||	(type->usage==U_structrtn)	)
	{	//specific enum or defined struct without type.
		//Just return as if there had been a type.
		//Need to pull a sep! This option is not absolutely necessary.
		value=type;
		newname=NULL;
		findspelling(getword(ifile),sep);
		if (	(sep->tokencode!=T_comma)
			&&	(sep->tokencode!=T_brktclose)	)
			EmitSysErr("Expecting '}' or ',' after uncast %s. Got %s!",
				type->TokenText(),sep->TokenText());
	}
	else
	if (type->usage!=U_typename)
		if (type->tokencode==T_unknown)
			EmitSysErr("Type name was expected. Encountered undefined %s",
				type->TokenText());
			//to support the next 2 options, type-->sep, NULL-->type, 
			//and cope with type=NULL in callers.
		elseif (type->tokencode==T_brktclose)
			EmitSysErr("Type name expected but got '}'. Empty braces not supported");
		elseif (type->tokencode==T_comma)
			EmitSysErr("Type name expected but got ','. Empty fields not supported");
		else
			EmitSysErr("Type name was expected, but encountered %s",
				type->TokenText());
	else
	{	//got typename look for optional name=
		//even if I get a new name, 
		//if it is followed by , or } then it is a forward reference
		//So, the correct logic is: 
		//Get the next symbol to newname
		//If it is an opening bracket then newname-->sep-->value;return
 		//Get the next symbol to sep
		//If sep is , or }
		//then newname-->value;NULL-->newname;return
		//sep is = error check
		//newname is unique definition error check
		//get the next symbol to value
		//If it is an opening bracket then sep-->value;return
 		//Get the next symbol to sep
		//sep is , or } error check
		//return

		findspelling(ifile,newname);

		if (newname->tokencode==T_equals)	//cope with type = value
			findspelling(ifile,newname);	//allows type = newname = value

		if (newname->tokencode==T_brktopen)
		{	//format is "type {"
			value=sep=newname;
			newname=NULL;
		}
		else
		{
			findspelling(ifile,sep);
			if (	(sep->tokencode==T_brktclose)
				||	(sep->tokencode==T_comma)
				||	(sep->tokencode==T_times)
				)
			{	//format is "type value ,"
				value=newname;
				newname=NULL;
			}
			elseif (sep->tokencode!=T_equals)
				EmitSysErr("Expecting one of '*},=' after %s %s, but found %s",
					type->TokenText(),
					newname->TokenText(),
					sep->TokenText());
			else
			{	//format is "type name =" - check that symbol not already defined
//to be defined you have to be known, and you have to be more than used
				if (	(newname->tokencode!=T_unknown)
					&&	(newname->defined!=D_used)	)
					EmitSysErr("Symbol already defined in assignment: %s\n"
								"Previous definition: %s(%i)",
								newname->TokenText(),
								names[newname->srcfname],newname->srcfline);
				findspelling(ifile,value);
				if (value->tokencode==T_brktopen)
				{	//format is "type name = {"
					sep=value;
				}
				else
				{	//format is "type name = value ,"
					//note that "type name = value" where value isn't defined is legal.
					findspelling(ifile,sep);
					if (!(	(sep->tokencode==T_brktclose)
						 || (sep->tokencode==T_comma)
						 || (sep->tokencode==T_times)
						))
						EmitSysErr("Expecting ',' or '}' after %s. Got %s",
							value->TokenText(),sep->TokenText());
				}
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		getlistseparator
//Author		Jim Taylor
//Date			Tue 28 Nov 1995
//
//Description	eats list separator symbol if necessary
//
//Inputs		
//
//Returns		TRUE	if end of list '}'
//				FALSE 	if separator ','
//------------------------------------------------------------------------------
Bool	getlistseparator(file	ifile,TokenName	*sep)
{
	if (	(sep->tokencode==T_brktopen)
		||	(sep->tokencode==T_times)
		)
		findspelling(ifile,sep);
	if (sep->tokencode==T_brktclose)	return(TRUE);
	if (sep->tokencode!=T_comma)
		EmitSysErr("Expecting comma to separate fields, but got %s",
			sep->TokenText());
	return(FALSE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		initchainref
//Author		Jim Taylor
//Date			Tue 28 Nov 1995
//
//Description	Defines a default chain for a symbol 
//				that is referenced before it is defined
//
//Inputs		pvalue		Dictionary entry to modify
//				T			Tokencode to assign
//
//Returns	
//
//------------------------------------------------------------------------------
DataInst*	initchainref(TokenName *pvalue,TokenCode	T)
{
		pvalue->instance=new ChainInst(T);	Assert(pvalue->instance&&"memory!");
		pvalue->instance->tokentext=pvalue;
		pvalue->instance->tokencode=
			pvalue->tokencode=T;
		pvalue->usage=U_structrtn;
		pvalue->defined=D_used;
		return(pvalue->instance);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		setupnewnamereference
//Author		Jim Taylor
//Date			Tue 28 Nov 1995
//
//Description	Handle an assignment to a type on return from it's creation
//				If name already exists then first record of retval is 
//				copied into existing space and deleted. 
//Inputs		
//
//Returns		Modifies retval pointer to a copy of same data.
//
//------------------------------------------------------------------------------
void	setupnewnamereference(TokenName *newname,DataInst* &retval)
{
	if (newname && retval)
	{
		if (newname->instance)
		{
			if (newname->instance==retval)
				EmitSysErr("Simple self-reference by %s",
					newname->TokenText());
			if (newname->tokencode!=retval->tokencode)
				EmitSysErr("Forward reference type doesn't match this declaration: %s\n"
							"Forward referenced from %s(%i)",
							newname->TokenText(),names[newname->srcfname],newname->srcfline);
			*(newname->instance)=*retval;	//how much will this copy?
			delete retval;					//or do I need to overload=?
			retval=newname->instance;
			retval->tokentext=newname;
			newname->defined=D_defused;
			newname->srcfname=currsrcfname;	//interested in definition position later
			newname->srcfline=currsrcfline;
		}
		else
		{
			if (	(retval->tokentext==NULL)
				||	(retval->tokentext->usage==U_punctuation)	)
				retval->tokentext=newname;
			newname->tokencode=retval->tokencode;
			newname->instance=retval;
			newname->defined=D_defined;
			newname->usage=U_structrtn;
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		repeattest
//Author		Jim Taylor
//Date			Tue 28 Nov 1995
//
//Description	Check for repeated toggle or blocker toggle
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
int	repeattest(int	bitlist,int	toggle,int	blocker,char* group,char* tokentext)
{
if (bitlist&toggle)
	EmitSysErr("%s repeated in %s",tokentext,group);
elseif (bitlist&blocker)
	EmitSysErr("%s after Item in %s",tokentext,group);
else
	bitlist|=toggle;
	return(bitlist);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessEnumStatement
//Author		Jim Taylor
//Date			Mon 27 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ProcessEnumStatement(file	ifile)
{

char*
	nextword;
TokenName
	*tokenname;
	nextword=getword(ifile);
	if (testspelling(nextword,tokenname) && (tokenname->usage==U_enumequiv))
	{	//if followed by "{"
TokenCode
		tokencode=tokenname->tokencode;
		nextword=getword(ifile);
		if (	testspelling(nextword,tokenname)
			&&	(tokenname->tokencode==T_brktopen)
			)
		{	//read all new parameters
			nextword=getword(ifile);
TokenName	*newword=NULL;
Bool		oldspelling=findspelling(nextword,newword);
int			lastval=0;

			while(newword->tokencode!=T_brktclose)
			{
				if (oldspelling)
					EmitSysErr("Not expecting known word at start of ENUM: %s",nextword);
				else
				{
					nextword=getword(ifile);
					findspelling(nextword,tokenname);
					if (tokenname->tokencode==T_equals)
					{
						nextword=getword(ifile);
						if	(	!findspelling(nextword,tokenname)
							 && (tokenname->tokencode!=T_int)
							 && (tokenname->tokencode!=T_nint)
							)
							EmitSysErr("RHS of assignment not defined in ENUM: %s=%s",
								newword->TokenText(),nextword);
						if (!(	(tokenname->tokencode==T_int)
							||	(tokenname->tokencode==T_nint)
							||	(	(tokenname->tokencode==tokencode)
									&& (tokenname->usage==U_value)
								)
							))
							EmitSysErr("RHS of assignment not correct type in ENUM: %s=%s",
								newword->TokenText(),nextword);
						//at this point newname=tokenname
						newword->usage=U_value;
						newword->tokencode=tokencode;
						newword->defined=D_defined;
						newword->instance=new ChainInst(tokencode);	Assert(newword->instance&&"memory!");
						newword->instance->tokentext=newword;
						((ChainInst*) newword->instance)->dataref=tokenname->instance;
						lastval=((IntegerInst*) tokenname->instance)->value;
						if (tokencode == T_UIDband)
						{
							uidtable1[uidtablesize] = lastval;
							uidtablesize++;
						}

						if (tokenname->instance->tokencode==T_nint)	lastval=-lastval;
						lastval++;
						nextword=getword(ifile);
						findspelling(nextword,tokenname);
						if (	(tokenname->tokencode!=T_comma)
							&&	(tokenname->tokencode!=T_brktclose)	)
							EmitSysErr("Expected one of ',}' but got '%s' after '%s=1234' in ENUM:",
									nextword,newword->TokenText());
					}
					else	//should be "}" or ","
					if (	(tokenname->tokencode!=T_comma)
						&&	(tokenname->tokencode!=T_brktclose)	)
						EmitSysErr("Expected one of '=,}' but got '%s' after '%s' in ENUM:",
								nextword,newword->TokenText());
					else
					{
						newword->usage=U_value;
						newword->tokencode=tokencode;
						newword->defined=D_defined;
						newword->instance=new ChainInst(tokencode);	Assert(newword->instance&&"memory!");
						((ChainInst*) newword->instance)->dataref=new IntegerInst;	Assert(((ChainInst*) newword->instance)->dataref&&"memory!");
						newword->instance->tokentext=newword;
						((ChainInst*) newword->instance)->dataref->tokentext=newword;
						if (lastval>=0)
						{
							((IntegerInst*)	((ChainInst*) newword->instance)->dataref)->value=lastval;
							((ChainInst*) newword->instance)->dataref->tokencode=T_int;
						}
						else
						{
							((IntegerInst*)	((ChainInst*) newword->instance)->dataref)->value=-lastval;
							((ChainInst*) newword->instance)->dataref->tokencode=T_nint;
						}
						if (tokencode == T_UIDband)
						{
							uidtable1[uidtablesize] = lastval;
							uidtablesize++;
						}
						lastval++;
					}
				}
				if (tokenname->tokencode==T_brktclose)
					newword=tokenname;
				else
				{
					nextword=getword(ifile);
					oldspelling=findspelling(nextword,newword);
				}
			}
		}			
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		sortuidtable
//Author		Robert Slater
//Date			Mon 5 Feb 1996
//
//Description	Sorts the Unique ID table and sets up a corresponding maximums
//				table.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------

void	sortuidtable()
{

	Bool	found;
	int		tempno,	counter;

	do
	{
		found = FALSE;
	
		for (counter = 0; counter < uidtablesize-1; counter ++)
		 	if (uidtable1[counter] > uidtable1[counter+1])
		 	{
		 		// Swap...
			 		
				tempno = uidtable1[counter+1];
		 		uidtable1[counter+1] = uidtable1[counter];
		 		uidtable1[counter] = tempno;
			 
				found = TRUE;
		 	}
	}
	while(found);

	for (counter = 0; counter < uidtablesize-1; counter ++)
		uidtable2[counter] = uidtable1[counter+1] - 1;

 	uidtable2[uidtablesize-1] = uidtable1[uidtablesize-1];
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessConstStatement
//Author		Jim Taylor
//Date			Mon 27 Nov 1995
//
//Description	handle const as possible static enum value
//
//Inputs		statement in form:
//				const	type	name=(type) value;
//				const	type	name=value;
//				const	type	name=value,name=value;
//				already parsed the const keyword
//				need to distinguish , and ;
//Returns	
//
//------------------------------------------------------------------------------
void	ProcessConstStatement(file	ifile)
{
char*
	nextword;
TokenName
	*tokenname;
	nextword=getword(ifile);
	if (testspelling(nextword,tokenname) && (tokenname->usage==U_enumequiv))
	{	//if followed by new name
TokenCode
		tokencode=tokenname->tokencode;
TokenName
		*newword=NULL;
		nextword=getword(ifile);
		if (!findspelling(nextword,newword))
			for(;;)
			{	//need to loop arround ,
				nextword=getword(ifile);
				findspelling(nextword,tokenname);
				if (tokenname->tokencode!=T_equals)
					EmitSysErr("Expecting '=' after %s, but found %s!",
						newword->TokenText(),nextword);
				nextword=getword(ifile);
				findspelling(nextword,tokenname);
				while (tokenname->tokencode==T_brktopen)
				{	//booring! skip ( type )
					nextword=getword(ifile);
					findspelling(nextword,tokenname);
					if (	(tokenname->usage!=U_enumequiv)
						||	(tokenname->tokencode!=tokencode))
						EmitSysErr("const TYPE and =(TYPE) do not match! %s",
							nextword);
					nextword=getword(ifile);
					findspelling(nextword,tokenname);
					if (tokenname->tokencode!=T_brktclose)
						EmitSysErr("Expecting closing bracket after type in const, but got %s",
							nextword);
					nextword=getword(ifile);
					findspelling(nextword,tokenname);
				}
				if (tokenname->usage!=U_value)
					if (tokenname->tokencode==T_unknown)
						EmitSysErr("Symbol %s not defined yet. Possibly not listed type?",
							nextword);
				else
					EmitSysErr("Expecting int or defined enum value, but found %s",
							nextword);
				newword->usage=U_value;
				newword->tokencode=tokencode;
				newword->defined=D_defined;

				if (tokenname->tokencode==tokencode)
				{
					//newword=tokenname... do your stuff!!
					newword->instance=tokenname->instance;
					newword->instance->tokencode=tokencode;
					newword->instance->tokentext=newword;
				}
				else
				{
					newword->instance=new ChainInst(tokencode);	Assert(newword->instance&&"memory!");
					newword->instance->tokentext=newword;
					if (tokenname->tokencode==T_int)
						((ChainInst*) newword->instance)->dataref=tokenname->instance;
					elseif (tokenname->tokencode==T_nint)
						((ChainInst*) newword->instance)->dataref=tokenname->instance;
					else
						((ChainInst*) newword->instance)->dataref=
							((ChainInst*) tokenname->instance)->dataref;
				}

				//need to get next symbol and loop arround
				nextword=getword(ifile);
				testspelling(nextword,tokenname);
				if (tokenname->tokencode!=T_comma)
					EmitSysErr("Expecting one of ',;', but got %s",nextword);
			breakif (tokenname->tokentext[0]==';');
				nextword=getword(ifile);
				if (findspelling(nextword,newword))
					EmitSysErr("Const enum already defined: %s",nextword);
}	}		} 


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		interpretenums
//Author		Jim Taylor
//Date			Mon 27 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	interpretenums(file	ifile)
{
char*	nextword;
TokenName
	*tokenname;
	//scan for 'enum'
	while (stripwhite(ifile))
	{
		nextword=getword(ifile);
	 	if (	testspelling(nextword,tokenname)
			&&	(tokenname->tokencode==T_enum)	)
		{
			if (tokenname->usage==U_value)
				ProcessConstStatement(ifile);
			else
			if (tokenname->usage==U_typename)
				ProcessEnumStatement(ifile);
		}
	}
	fclose(ifile);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		add3dsentry
//Author		Jim Taylor
//Date			Thu 30 Nov 1995
//
//Description	Builds tree for 3ds generated item info
//				and adds name to dictionary.
//				Note: if name is in wordbuff it will be safely copied.
//				Otherwise the caller must create a unique name string.
//Inputs		
//
//Structure created:
//
//				3dsref->Link->shape->int
//						Link->pos->abs->Link->x->int
//										Link->y->int
//										Link->z->int
//
//------------------------------------------------------------------------------
void	add3dsentry(string	name,int	X,int	Y,int	Z,string	shapename)
{
ChainInst	*tmpchain;
LinkInst	*tmplink;
IntegerInst		*tmpint;
TokenName	*entry,*shapeinst;
char		*permname, *permshape;


	// Make strings permanent
	
	if (name)
	{
		permname = new char[strlen(name)+1];	Assert(permname&&"memory!");
		strcpy(permname,name);
	}
	else
		permname = NULL;

	if (shapename && *shapename)
	{
		permshape = new char[strlen(shapename)+1];	Assert(permshape&&"memory!");
		strcpy(permshape,shapename);
	}
	else
		permshape = NULL;

	findspelling(permname,entry);
	if (entry->tokencode!=T_unknown)
		EmitSysErr("%s already loaded from 3ds file.",permname);
	entry->tokencode=T_3dsref;
	entry->defined=D_defined;
	entry->usage=U_structrtn;

	if (permshape && *permshape)
	{
		findspelling(permshape,shapeinst);
		if (shapeinst->tokencode==T_unknown)
			EmitWarning("Shape (%s)  requested by 3ds item (%s) not recognised.",
				permshape,permname);
		else
		if (	(shapeinst->tokencode!=T_shape)
			||	(shapeinst->usage!=U_value)	)
			EmitWarning("Symbol (%s)  requested by 3ds item (%s) not a shape.",
				permshape,permname);
	}
	else
		unshaped3ds++;

	entry->instance=
		tmpchain=new ChainInst(T_3dsref);	Assert(tmpchain&&"memory!");
						//;;entry->instance currently references the following tree:
									//;;3dsref
									//;;E-I=TC
	tmpchain->dataref=
		tmplink=new LinkInst;	Assert(tmplink&&"memory!");


	if (permshape)
		tmplink->dataref=shapeinst->instance;
	else
		tmplink->dataref=NULL;
	tmplink->tokentext=NULL;
									//;;3dsref->link->shape->int
									//;;E-I		TL			
									//;;TC
									//;;

	tmplink=
		tmplink->sibling=new LinkInst;	Assert(tmplink&&"memory!");
	tmplink->tokentext=NULL;


	tmplink->dataref=
		tmpchain=new ChainInst(T_pos);	Assert(tmpchain&&"memory!");
	tmpchain=(ChainInst*)
		(tmpchain->dataref=new ChainInst(T_abs));	Assert(tmpchain&&"memory!");
	tmpchain->tokentext=NULL;


	tmpchain->dataref=
		tmplink=new LinkInst;	Assert(tmplink&&"memory!");
	tmpchain->tokentext=NULL;
									//;;3dsref->	link->shape->int
									//;;			link->pos->abs->link
									//;;						TC	TL				
									//;;

	tmplink->dataref=
		tmpchain=new ChainInst(T_x);	Assert(tmpchain&&"memory!");
	tmpchain->tokentext=NULL;
	
	
	tmpchain->dataref=
		tmpint=new IntegerInst;	Assert(tmpint&&"memory!");
	tmpint->tokentext=NULL;


	tmpint->value=X;
									//;;3dsref->	link->shape->int
									//;;			link->pos->abs->link->X->int
									//;;						  	TL	  TC TI
									//;;
	tmplink=
		tmplink->sibling=new LinkInst;	Assert(tmplink&&"memory!");

	tmplink->tokentext=NULL;

	tmplink->dataref=
		tmpchain=new ChainInst(T_y);	Assert(tmpchain&&"memory!");
	tmpchain->tokentext=NULL;

	tmpchain->dataref=
		tmpint=new IntegerInst;	Assert(tmpint&&"memory!");
	tmpint->tokentext=NULL;


	tmpint->value=Y;
									//;;3dsref->	link->shape->int
									//;;			link->pos->abs->link->X->int
									//;;							link->Y->int
									//;;							TL	  TC TI
	tmplink=
		tmplink->sibling=new LinkInst;	Assert(tmplink&&"memory!");

	tmplink->tokentext=NULL;

	tmplink->dataref=
		tmpchain=new ChainInst(T_z);	Assert(tmpchain&&"memory!");

	tmpchain->tokentext=NULL;

	tmpchain->dataref=
		tmpint=new IntegerInst;	Assert(tmpint&&"memory!");
	tmpint->tokentext=NULL;

	tmpint->value=Z;
									//;;3dsref->	link->shape->int
									//;;			link->pos->abs->link->X->int   
									//;;							link->Y->int
									//;;							link->Z->int
									//;;						  	TL	  TC TI	

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		addassocenum
//Author		Jim Taylor
//Date			Tue 5 Dec 1995
//
//Description	Makes an emum association to an internal type keyword
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	addassocenum(string name,TokenCode T)
{
TokenName	*entry;
	findspelling(name,entry);
	if (entry->tokencode!=T_unknown)
		EmitSysErr("%s enum to type association already defined.",name);
	entry->tokencode=T;
	entry->usage=U_enumequiv;
	entry->defined=D_defined;
	entry->instance=NULL;
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		addglobalentry
//Author		Jim Taylor
//Date			Thu 30 Nov 1995
//
//Description	Constructs a sequence in the form below and increments int 
//				T->global->int
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	addglobalentry(ufile gf,string	name,TokenCode T)
{
static	globaltableentry=0;
ChainInst	*tmpchain;
IntegerInst		*tmpint;
TokenName	*entry;
FILE*	f;
	findspelling(name,entry);
	if (entry->tokencode!=T_unknown)
		EmitSysErr("%s global variable already defined.",name);
	entry->tokencode=T;
	entry->usage=U_value;
	entry->defined=D_defined;
	entry->instance=
		tmpchain=new ChainInst(T);	Assert(tmpchain&&"memory!");
	tmpchain=(ChainInst*)
		(tmpchain->dataref=new ChainInst(T_mainprog));	Assert(tmpchain&&"memory!");
	tmpchain->dataref=
		tmpint=new IntegerInst;	Assert(tmpint&&"memory!");
	tmpint->value=globaltableentry++;
	fprintf(gf,"\t\t{(void*) &GR_%s},\n",entry->TokenText());
}

//
// Black box parser ends here
//
//
///////////////////////

void	interpretglobals(file	ifile,ufile globfile)
{

char*	nextword;
TokenName	*tokenname;
TokenCode	tokentype;
	//scan for 'enum'
	findspelling(ifile,tokenname);
	if (tokenname->tokencode!=T_brktopen)
		EmitSysErr("Globals list file must start with '{'");
	for(;;)
	{
		findspelling(ifile,tokenname);
		if (	(tokenname->usage!=U_typename)
			&&	(tokenname->usage!=U_enumequiv)	)
			EmitSysErr("Expecting type name, but found %s",
				tokenname->TokenText());
		tokentype=tokenname->tokencode;
		nextword=getword(ifile);
		if (!testspelling(nextword,tokenname))
			addglobalentry(globfile,nextword,tokentype);
		elseif	(tokenname->tokencode!=T_brktopen)
			EmitSysErr("Expecting list of globals, but found %S",
				tokenname->TokenText());
		else
			for (;;)
			{	//got opening bracket so read list of globals
				nextword=getword(ifile);
				addglobalentry(globfile,nextword,tokentype);
				findspelling(ifile,tokenname);
			breakif (tokenname->tokencode==T_brktclose);
				if (tokenname->tokencode!=T_comma)
					EmitSysErr("Expecting comma, but got %s",
						tokenname->TokenText());
			}
		findspelling(ifile,tokenname);
	breakif (tokenname->tokencode==T_brktclose);
		if (tokenname->tokencode!=T_comma)
			EmitSysErr("Expecting comma, but got %s",
				tokenname->TokenText());
	}			
	fclose(ifile);
}

void	associateenums(file	ifile)
{

char*	nextword;
TokenName	*tokenname;
TokenCode	tokentype;
	//scan for 'enum'
	findspelling(ifile,tokenname);
	if (tokenname->tokencode!=T_brktopen)
		EmitSysErr("Enum assoc list file must start with '{'");
	for(;;)
	{
		findspelling(ifile,tokenname);
		if (	(tokenname->usage!=U_typename)
			&&	(tokenname->usage!=U_enumequiv)	)
			EmitSysErr("Expecting type name, but found %s",
				tokenname->TokenText());
		tokentype=tokenname->tokencode;
		nextword=getword(ifile);
		if (!testspelling(nextword,tokenname))
			addassocenum(nextword,tokentype);
		elseif	(tokenname->tokencode!=T_brktopen)
			EmitSysErr("Expecting list of enums, but found %S",
				tokenname->TokenText());
		else
			for (;;)
			{	//got opening bracket so read list of enums
				nextword=getword(ifile);
				addassocenum(nextword,tokentype);
				findspelling(ifile,tokenname);
			breakif (tokenname->tokencode==T_brktclose);
				if (tokenname->tokencode!=T_comma)
					EmitSysErr("Expecting comma, but got %s",
						tokenname->TokenText());
			}
		findspelling(ifile,tokenname);
	breakif (tokenname->tokencode==T_brktclose);
		if (tokenname->tokencode!=T_comma)
			EmitSysErr("Expecting comma, but got %s",
				tokenname->TokenText());
	}			
	fclose(ifile);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		interpretresponse
//Author		Jim Taylor
//Date			Tue 5 Dec 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	interpretresponse(string	name)
{
TokenName	*tokenname;
UWord	bufname,bufline;
file	ifile=readfile(name);
ufile	globfile=fopen("h\\bfrefs.g",'t');
	fprintf(globfile,"GlobalRef	BFieldGlobalTable[]=	{\n");
	findspelling(ifile,tokenname);
	if (tokenname->tokencode!=T_brktopen)
		EmitSysErr("Initialisation response file must start with '{'");
	for(;;)
	{
		findspelling(ifile,tokenname);
		if (tokenname->tokencode==T_setval)
		{
			bufname=currsrcfname;
			bufline=currsrcfline;
			interpretglobals(readfile(getword(ifile)),globfile);
			currsrcfname=bufname;
			currsrcfline=bufline;
		}
		elseif (tokenname->tokencode==T_enum)
		{
			bufname=currsrcfname;
			bufline=currsrcfline;
			interpretenums(readfile(getword(ifile)));
			currsrcfname=bufname;
			currsrcfline=bufline;
		}
		elseif (tokenname->tokencode==T_type)
		{
			bufname=currsrcfname;
			bufline=currsrcfline;
			associateenums(readfile(getword(ifile)));
			currsrcfname=bufname;
			currsrcfline=bufline;
		}
		elseif (tokenname->tokencode==T_pos)
		{
			bufname=currsrcfname;
			bufline=currsrcfline;
			studiointerpreter(readfile(getword(ifile)));
			currsrcfname=bufname;
			currsrcfline=bufline;
		}
		else
			EmitSysErr("Unexpected symbol in initialisation response file: %s",tokenname->TokenText());
		findspelling(ifile,tokenname);
	breakif (tokenname->tokencode==T_brktclose);
		if (tokenname->tokencode!=T_comma)
			EmitSysErr("Expecting comma, but got %s",
				tokenname->TokenText());

	}
	fprintf(globfile,"\t\tNULL};\n");
fclose(globfile);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		bfsave_setval
//Author		Jim Taylor
//Date			Wed 29 Nov 1995
//
//Description	Setval syntax is:
//					Setval	{global,src}
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
DataInst*	bfsave_setval(file	ifile,TokenName	*pvalue)
{
TokenName	*type,	*newname,	*value,	*sep;
DataInst	*v2;
LPair		list;
TokenCode	globalcode,sourcecode;
	if (pvalue->tokencode!=T_brktopen)
		EmitSysErr("SetVal syntax is SetVal {global,srcval}");
	elser
	{
		//parameter 1:
		GetTypeAndValue(ifile,type,newname,value,sep);
		if (newname!=NULL)
			EmitSysErr("Can't assign inside setval!!!");
		if (	(value->usage!=U_value)
			||	(value->defined==D_used)
			||	(value->tokencode==T_int)
			||	(value->tokencode==T_nint)
			||	(value->instance==NULL)
			||	(((ChainInst*) value->instance)->dataref->tokencode!=T_mainprog)
			)
			EmitSysErr("Target for SetVal (%s) is not a main prog variable",
								value->TokenText());
		if (type->tokencode!=value->tokencode)
			EmitSysErr("Type satatement at start of setval is irrelevent and wrong");
		globalcode=value->instance->tokencode;

		list.Add(value->instance);

		//comma
		if (getlistseparator(ifile,sep))
			EmitSysErr("Need 2 parameters in setval");

		//parameter 2
		GetTypeAndValue(ifile,type,newname,value,sep);
		if (newname!=NULL)
			EmitSysErr("Can't assign inside setval!!!");
		if (	globalcode!=T_setUID	)
			sourcecode=globalcode;
		else
			sourcecode=type->tokencode;
		switch (sourcecode)
		{
		case T_character:
		case T_UIDband:
		case T_briefID:
		case T_nation:
		case T_shape:
		case T_type:
		case T_duty:
		case T_form:
		case T_move:
		case T_event:
		case T_wpact:
		case T_squadron:
			v2=toplevel_enumval(ifile,value,sourcecode);
			if (v2->tokencode!=type->tokencode)
				EmitSysErr("2nd parameter type not as stated");
		break;
		case T_paintscheme:
		case T_inwing:
		case T_inform:
		case T_skill:
		case T_morale:
		case T_damage:
		case T_x:
		case T_y:
		case T_z:
		case T_range:
		case T_rangepc:
		case T_count:
		case T_hours:
		case T_mins:
		case T_secs:
		case T_bombs:
			v2=toplevel_enumorint(ifile,value,sourcecode);
		break;
		case T_asimuth:
		case T_bearing:
		case T_pitch:
		case T_hdg:
		case T_roll:
		case T_angle:
			v2=toplevel_enumorangle(ifile,value,sourcecode);
		break;
		case T_setUID:
		case T_target:
		case T_itemA:
		case T_itemS:
		case T_itemG:
		case T_waypoint:
//Old_Code DAW 26Mar96 			if (value->tokencode!=T_setUID)
//Old_Code DAW 26Mar96 				EmitSysErr("Input for setval is item, but global var is not UniqueID!");
//Old_Code DAW 26Mar96 			v2=toplevel_target(ifile,value);
			if (globalcode!=T_setUID)
				EmitSysErr("Input for setval is item, but global var is not UniqueID!");
			v2=toplevel_target(ifile,value,sourcecode);
		break;
		default:
			EmitSysErr("Can't handle %s in setval.",getcodename(type->tokencode));

		}
		//close bracket
		if (!getlistseparator(ifile,sep))
			EmitSysErr("Only 2 parameters in setval");
		list.Add(v2);
		return(list.Code(T_setval,pvalue));
	}
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		toplevel_bfsave
//Author		Jim Taylor
//Date			Mon 27 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
DataInst*	toplevel_bfsave(file	ifile,TokenName	*pvalue)
{
const	TokenCode	T_T=T_bfsave;
TokenName	*type,	*newname,	*value,	*sep;
DataInst	*retval;
LPair		list;
Bool	fnamerepeat=FALSE;
	if (pvalue->tokencode==T_unknown)			//if simple forward reference
		return(initchainref(pvalue,T_T));
	elser
	if (pvalue->tokencode==T_T)				//if simple reference
		return(pvalue->instance);
	elser
	if (pvalue->tokencode!=T_brktopen)
		EmitSysErr("Battlefield argument must be Battlefield type, not %s",
			pvalue->TokenText());
	elser
	{
UWord	LevelBackup=Current_Level;
		for(;;)
		{	//looping read of body of bfield header
			GetTypeAndValue(ifile,type,newname,value,sep);
			if (type)
			switch (type->tokencode)
			{
			case T_itemS:
				retval=toplevel_itemS(ifile,value);
			break;
			case T_itemgrp:
				retval=toplevel_itemgrp(ifile,value);
			break;
			case T_gndgrp:
				retval=toplevel_gndgrp(ifile,value);
			break;
			case T_airgrp:
				retval=toplevel_airgrp(ifile,value);
			break;
			case T_route:
				retval=toplevel_route(ifile,value);
			break;
			case T_fname:
				fnamerepeat=(Bool)
					repeattest(fnamerepeat,TRUE,0,"BattleField",type->TokenText());
				retval=toplevel_fname(newname,value);
			break;
			case T_setval:
				retval=bfsave_setval(ifile,value);
			break;
			case T_level:
				retval=toplevel_level(ifile,value);
			break;
			default:
				EmitSysErr("Type of symbol not valid within BattleField: %s",
					type->TokenText());
			}
			setupnewnamereference(newname,retval);
			list.Add(retval);
		breakif (getlistseparator(ifile,sep));
		}
		Current_Level=LevelBackup;
		return(list.Code(T_T,pvalue));
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		toplevel_itemgrp
//Author		Jim Taylor
//Date			Mon 27 Nov 1995
//
//Description	A group of items. 
//				This may only contain SimpleItem 
//				and pos abs assignments - which are not linked
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
DataInst*	toplevel_itemgrp(file	ifile,TokenName	*pvalue)
{
const	TokenCode	T_T=T_itemgrp;
TokenName	*type,*newname,*value,*sep;
DataInst 	*retval;
LPair	 	list;
	if (pvalue->tokencode==T_unknown)			//if simple forward reference
		return(initchainref(pvalue,T_T));
	elser
	if (pvalue->tokencode==T_T)				//if simple reference
		return(pvalue->instance);
	elser
	if (pvalue->tokencode==T_itemS)			//if single ref to item
	{										//then make single entry list
		list.Add(pvalue->instance);
		return(list.Code(T_T,pvalue));
	}
	elser
	if (pvalue->tokencode!=T_brktopen)
		EmitSysErr("Argument must be ItemGrp type , not %s",
			pvalue->TokenText());
	elser
	{
		for(;;)
		{	//looping read of body of bfield header
			GetTypeAndValue(ifile,type,newname,value,sep);
			if (type)
			switch (type->tokencode)	//will need to pass in sep to cope with
			{
			case T_itemS:
				retval=toplevel_itemS(ifile,value);
			break;
			case T_pos:
				//pos is supported only to allow writeback
				if (newname!=NULL)
					EmitSysErr("'POS name= {' is only acceptable syntax for POS in itemgrp");
			default:
				EmitSysErr("Type of symbol not valid within ItemGrp: %s",
					type->TokenText());
			}

			setupnewnamereference(newname,retval);
			if (type->tokencode==T_itemS)
				list.Add(retval);
		breakif (getlistseparator(ifile,sep));
		}
	return(list.Code(T_T,pvalue));
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		toplevel_gndgrp
//Author		Jim Taylor
//Date			Mon 27 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
DataInst*	toplevel_gndgrp(file	ifile,TokenName	*pvalue)
{
const	TokenCode	T_T=T_gndgrp;
TokenName	*type,*newname,*value,*sep;
DataInst 	*retval;
LPair	 	list;
enum		XClusive
			{Xzero=0,Xinform=1,Xpos=2,Xroute=4,Xform=8,Xitem=16}
			Xclusive=Xzero;
//DeadCode JIM 30Nov95 BITABLE		(XClusive);

	if (pvalue->tokencode==T_unknown)			//if simple forward reference
		return(initchainref(pvalue,T_T));
	elser
	if (pvalue->tokencode==T_T)				//if simple reference
		return(pvalue->instance);
	elser
	if (pvalue->tokencode!=T_brktopen)
		EmitSysErr("Argument must be gndgrp type, not %s",
			pvalue->TokenText());
	elser
	{
		for(;;)
		{	//looping read of body of bfield header
			GetTypeAndValue(ifile,type,newname,value,sep);
			if (type)
			switch (type->tokencode)	//will need to pass in sep to cope with
			{
			case T_inform:
				Xclusive=(XClusive)
					repeattest(Xclusive,Xinform,Xitem,"Groundgroup",type->TokenText());
				retval=toplevel_inform(ifile,value);
			break;
			case T_pos:
				Xclusive=(XClusive)
					repeattest(Xclusive,Xpos,Xitem,"Groundgroup",type->TokenText());
				retval=toplevel_pos(ifile,value);
			break;
			case T_route:
				Xclusive=(XClusive)
					repeattest(Xclusive,Xroute,Xitem,"Groundgroup",type->TokenText());
				retval=toplevel_route(ifile,value);
			break;
			case T_form:
				Xclusive=(XClusive)
					repeattest(Xclusive,Xform,Xitem,"Groundgroup",type->TokenText());
				retval=toplevel_form(ifile,value);
			break;
			case T_itemG:
					Xclusive=(XClusive)(Xclusive|Xitem);
				retval=toplevel_itemG(ifile,value);
			break;
			default:
				EmitSysErr("Type of symbol not valid within GroundGrp: %s",
					type->TokenText());
			}

			setupnewnamereference(newname,retval);
			list.Add(retval);
		breakif (getlistseparator(ifile,sep));
		}
	return(list.Code(T_T,pvalue));
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		toplevel_airgrp
//Author		Jim Taylor
//Date			Mon 27 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
DataInst*	toplevel_airgrp(file	ifile,TokenName	*pvalue)
{
const	TokenCode	T_T=T_airgrp;
TokenName	*type,*newname,*value,*sep;
DataInst 	*retval;
LPair	 	list;
enum		XClusive
			{Xzero=0,Xinform=1,Xpos=2,Xroute=4,Xform=8,Xitem=16,Xinwing=32,Xduty=64,Xhdg=128}
			Xclusive=Xzero;
//DeadCode JIM 30Nov95 BITABLE		(XClusive);

	if (pvalue->tokencode==T_unknown)			//if simple forward reference
		return(initchainref(pvalue,T_T));
	elser
	if (pvalue->tokencode==T_T)				//if simple reference
		return(pvalue->instance);
	elser
	if (pvalue->tokencode!=T_brktopen)
		EmitSysErr("Argument must be airgrp type, not %s",
			pvalue->TokenText());
	elser
	{
		for(;;)
		{	//looping read of body of bfield header
			GetTypeAndValue(ifile,type,newname,value,sep);
			if (type)
			switch (type->tokencode)	//will need to pass in sep to cope with
			{
			case T_inform:
				Xclusive=(XClusive)
					repeattest(Xclusive,Xinform,Xitem,"Airgroup",type->TokenText());
				retval=toplevel_inform(ifile,value);
			break;
			case T_duty:
				Xclusive=(XClusive)
					repeattest(Xclusive,Xduty,Xitem,"Airgroup",type->TokenText());
				retval=toplevel_duty(ifile,value);
			break;
			case T_inwing:
				Xclusive=(XClusive)
					repeattest(Xclusive,Xinwing,Xitem,"Airgroup",type->TokenText());
				retval=toplevel_inwing(ifile,value);
			break;
			case T_pos:
				Xclusive=(XClusive)
					repeattest(Xclusive,Xpos,Xitem,"Airgroup",type->TokenText());
				retval=toplevel_pos(ifile,value);
			break;
			case T_route:
				Xclusive=(XClusive)
					repeattest(Xclusive,Xroute,Xitem,"Airgroup",type->TokenText());
				retval=toplevel_route(ifile,value);
			break;
			case T_form:
				Xclusive=(XClusive)
					repeattest(Xclusive,Xform,Xitem,"Airgroup",type->TokenText());
				retval=toplevel_form(ifile,value);
			break;
			case T_itemA:
					Xclusive=(XClusive)(Xclusive|Xitem);
				retval=toplevel_itemA(ifile,value);
			break;
			default:
				EmitSysErr("Type of symbol not valid within AirGroup: %s",
					type->TokenText());
			}

			setupnewnamereference(newname,retval);
			list.Add(retval);
		breakif (getlistseparator(ifile,sep));
		}
	return(list.Code(T_T,pvalue));
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		toplevel_route
//Author		Jim Taylor
//Date			Mon 27 Nov 1995
//
//Description	A list of waypoints.
//				This may only contain WayPoint
//				and pos abs assignments - which are not linked
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
DataInst*	toplevel_route(file	ifile,TokenName	*pvalue)
{
const	TokenCode	T_T=T_route;
TokenName	*type,*newname,*value,*sep;
DataInst 	*retval;
LPair	 	list;
	if (pvalue->tokencode==T_unknown)			//if simple forward reference
		return(initchainref(pvalue,T_T));
	elser
	if (pvalue->tokencode==T_T)				//if simple reference
		return(pvalue->instance);
	elser
	if (	pvalue->tokencode==T_waypoint
		||	pvalue->tokencode==T_setUID	)
	{
		DataInst 	*retval=toplevel_target(ifile,pvalue,T_target);
ChainInst*
		retval2=new ChainInst(T_route);	Assert(retval2&&"memory!");
		retval2->dataref=retval;
		return(retval2);
	}
	elser
	if (pvalue->tokencode!=T_brktopen)
		EmitSysErr("Argument must be Route type , not %s",
			pvalue->TokenText());
	elser
	{
		for(;;)
		{	//looping read of body of bfield header
			GetTypeAndValue(ifile,type,newname,value,sep);
			if (type)
			switch (type->tokencode)	//will need to pass in sep to cope with
			{
			case T_waypoint:
				retval=toplevel_waypoint(ifile,value);
				setupnewnamereference(newname,retval);
				list.Add(retval);
			break;
			case T_pos:
				//pos is supported only to allow writeback
				if (newname!=NULL)
					EmitSysErr("'POS name= {' is only acceptable syntax for POS in route");
				setupnewnamereference(newname,retval);
			default:
				EmitSysErr("Type of symbol not valid within ItemGrp: %s",
					type->TokenText());
			}

//DeadCode JIM 15Feb96 			setupnewnamereference(newname,retval);
//DeadCode JIM 15Feb96 			if (type->tokencode==T_waypoint)
//DeadCode JIM 15Feb96 				list.Add(retval);
		breakif (getlistseparator(ifile,sep));
		}
	return(list.Code(T_T,pvalue));
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		itemlevel_setUID
//Author		Jim Taylor
//Date			Wed 29 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
DataInst*	itemlevel_setUID(file	/*ifile*/,TokenName	*pvalue)
{
	if (pvalue->tokencode==T_unknown)
	{
ChainInst*
		tmpchain;
		pvalue->instance=
			tmpchain=
				new ChainInst(T_setUID);	Assert(tmpchain&&"memory!");
		tmpchain->dataref=new IntegerInst;	Assert(tmpchain->dataref&&"memory!");
		tmpchain->dataref->tokentext=
			tmpchain->tokentext=
				pvalue;
		pvalue->usage=U_value;
		pvalue->defined=D_defused;
		pvalue->tokencode=T_setUID;
	}
	else
	if (pvalue->tokencode!=T_setUID)
		EmitSysErr("Expecting unique name to assign UID, but found %s (type %s)",
					pvalue->tokentext,getcodename(pvalue->tokencode));
	return(pvalue->instance);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		toplevel_itemS
//Author		Jim Taylor
//Date			Mon 27 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
DataInst*	toplevel_itemS(file	ifile,TokenName	*pvalue)
{
const	TokenCode	T_T=T_itemS;
TokenName	*type,*newname,*value,*sep;
DataInst 	*retval;
LPair	 	list;
enum		XClusive
			{Xzero=0,XsetUID=1,Xpos=2,Xshape=4,Xband=8,Xbrief=16,Xhdg=32}
			Xclusive=Xzero;
//DeadCode JIM 30Nov95 BITABLE		(XClusive);

	if (pvalue->tokencode==T_unknown)			//if simple forward reference
		return(initchainref(pvalue,T_T));
	elser
	if (pvalue->tokencode==T_T)				//if simple reference
		return(pvalue->instance);
	elser
	if (pvalue->tokencode==T_3dsref)				//if simple reference
	{	//I have SimpleItem	RendererID
		//want to create sequence UIDband=simple, pos=renderID, shape=RenderID
//DeadCode JIM 30Nov95 		EmitSysErr("not handling renderer IDs here properly yet!");
		retval=new ChainInst(T_itemS);	Assert(retval&&"memory!");
		((ChainInst*) retval)->dataref=((ChainInst*) pvalue->instance)->dataref;
		return(retval);
	}
	elser
	if (pvalue->tokencode!=T_brktopen)
		EmitSysErr("Argument must be SimpleItem type, not %s",
			pvalue->TokenText());
	elser
	{
		for(;;)
		{	//looping read of body of bfield header
			GetTypeAndValue(ifile,type,newname,value,sep);
			if (type)
			switch (type->tokencode)
			{
			case T_event:
//DeadCode DAW 05Nov96 				Xclusive=(XClusive)
//DeadCode DAW 05Nov96 					repeattest(Xclusive,Xevent,0,"SimpleItem",type->TokenText());
				retval=toplevel_event(ifile,value);
			break;
			case T_setUID:
				Xclusive=(XClusive)
					repeattest(Xclusive,XsetUID,0,"SimpleItem",type->TokenText());
				retval=itemlevel_setUID(ifile,value);
			break;
			case T_pos:
				Xclusive=(XClusive)
					repeattest(Xclusive,Xpos,Xhdg,"SimpleItem",type->TokenText());
				retval=toplevel_pos(ifile,value);
			break;
			case T_shape:
				Xclusive=(XClusive)
					repeattest(Xclusive,Xshape,0,"SimpleItem",type->TokenText());
				retval=toplevel_shape(ifile,value);
			break;
			case T_UIDband:
				Xclusive=(XClusive)
					repeattest(Xclusive,Xband,0,"SimpleItem",type->TokenText());
				if (Xclusive&XsetUID)
					EmitSysErr("UID band set after UID set!");
				retval=toplevel_UIDband(ifile,value);
			break;
			case T_hdg:
			case T_bearing:
				Xclusive=(XClusive)
					repeattest(Xclusive,Xhdg,0,"SimpleItem",type->TokenText());
				retval=toplevel_bearing(ifile,value);
			break;
	 		case T_target:
			{
				Xclusive=(XClusive)
					repeattest(Xclusive,Xhdg,0,"SimpleItem",type->TokenText());
				ChainInst* rv2=new ChainInst(T_target);
				rv2->dataref=toplevel_pos(ifile,value);
				retval=rv2;
			}
			break;

//DeadCode JIM 28Nov95 			case T_briefID:
//DeadCode JIM 28Nov95 				Xclusive=(XClusive)
//DeadCode JIM 28Nov95 					repeattest(Xclusive,Xbrief,0,"SimpleItem",type->TokenText());
//DeadCode JIM 28Nov95 				retval=toplevel_briefID(ifile,value);
//DeadCode JIM 28Nov95 			break;
			default:
				EmitSysErr("Type of symbol not valid within SimpleItem: %s",
					type->TokenText());
			}

			setupnewnamereference(newname,retval);
			list.Add(retval);
		breakif (getlistseparator(ifile,sep));
		}
		if (!(Xclusive & Xpos))
			EmitSysErr("No pos in simple item!");

	return(list.Code(T_T,pvalue));
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		toplevel_itemG
//Author		Jim Taylor
//Date			Mon 27 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
DataInst*	toplevel_itemG(file	ifile,TokenName	*pvalue)
{
const	TokenCode	T_T=T_itemG;
TokenName	*type,*newname,*value,*sep;
DataInst 	*retval;
LPair	 	list;
enum		XClusive
			{Xzero=0,XsetUID=1,Xnat=2,Xshape=4,Xband=8,Xmove=16,Xform=32,Xattitude=64,
			Xleader=128,Xevent=256,Xtype=512,Xvel=1024}
			Xclusive=Xzero;
//DeadCode JIM 30Nov95 BITABLE		(XClusive);

	if (pvalue->tokencode==T_unknown)			//if simple forward reference
		return(initchainref(pvalue,T_T));
	elser
	if (pvalue->tokencode==T_T)				//if simple reference
		return(pvalue->instance);
	elser
//DeadCode JIM 30Nov95 	if (pvalue->tokencode==T_3dsref)				//if simple reference
//DeadCode JIM 30Nov95 	{	//I have SimpleItem	RendererID
//DeadCode JIM 30Nov95 		//want to create sequence UIDband=simple, pos=renderID, shape=RenderID
//DeadCode JIM 30Nov95 		EmitSysErr("not handling renderer IDs here properly yet!");
//DeadCode JIM 30Nov95 	}
//DeadCode JIM 30Nov95 	elser
	if (pvalue->tokencode!=T_brktopen)
		EmitSysErr("Argument must be GroundItem type, not %s",
			pvalue->TokenText());
	elser
	{
		for(;;)
		{	//looping read of body of bfield header
			GetTypeAndValue(ifile,type,newname,value,sep);
			if (type)
			switch (type->tokencode)
			{
			case T_setUID:
				Xclusive=(XClusive)
					repeattest(Xclusive,XsetUID,0,"GroundItem",type->TokenText());
				retval=itemlevel_setUID(ifile,value);
			break;
			case T_nation:
				Xclusive=(XClusive)
					repeattest(Xclusive,Xnat,0,"GroundItem",type->TokenText());
				retval=toplevel_nation(ifile,value);
			break;
			case T_form:
				Xclusive=(XClusive)
					repeattest(Xclusive,Xform,0,"GroundItem",type->TokenText());
				retval=toplevel_form(ifile,value);
			break;
			case T_shape:
				Xclusive=(XClusive)
					repeattest(Xclusive,Xshape,0,"GroundItem",type->TokenText());
				retval=toplevel_shape(ifile,value);
			break;
			case T_UIDband:
				Xclusive=(XClusive)
					repeattest(Xclusive,Xband,0,"GroundItem",type->TokenText());
				if (Xclusive&XsetUID)
					EmitSysErr("UID band set after UID set!");
				retval=toplevel_UIDband(ifile,value);
			break;
			case T_move:
				Xclusive=(XClusive)
					repeattest(Xclusive,Xmove,0,"GroundItem",type->TokenText());
				retval=toplevel_move(ifile,value);
			break;
			case T_att:
				Xclusive=(XClusive)
					repeattest(Xclusive,Xattitude,0,"GroundItem",type->TokenText());
				retval=toplevel_att(ifile,value);
			break;
			case T_leader:
				Xclusive=(XClusive)
					repeattest(Xclusive,Xleader,0,"AirItem",type->TokenText());
				retval=toplevel_leader(ifile,value);
			break;
			case T_event:
//DeadCode DAW 05Nov96 				Xclusive=(XClusive)
//DeadCode DAW 05Nov96 					repeattest(Xclusive,Xevent,0,"AirItem",type->TokenText());
				retval=toplevel_event(ifile,value);
			break;
			case T_type:
				Xclusive=(XClusive)
					repeattest(Xclusive,Xtype,0,"AirItem",type->TokenText());
				retval=toplevel_type(ifile,value);
			break;
			case T_vel:
				Xclusive=(XClusive)
					repeattest(Xclusive,Xvel,0,"AirItem",type->TokenText());
				retval=toplevel_vel(ifile,value);
			break;
			default:
				EmitSysErr("Type of symbol not valid within GroundItem: %s",
					type->TokenText());
			}

			setupnewnamereference(newname,retval);
			list.Add(retval);
		breakif (getlistseparator(ifile,sep));
		}
	return(list.Code(T_T,pvalue));
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		toplevel_target
//Author		Jim Taylor
//Date			Wed 29 Nov 1995
//
//Description	Want to fill in a pointer to an item...
//				I assume that has already been built
//				Actually, at this stage all I can do is insert a chain 
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
DataInst*	toplevel_attacker(file	ifile,TokenName	*pvalue)
{
	DataInst 	*retval=toplevel_target(ifile,pvalue,T_target);
ChainInst*
		retval2=new ChainInst(T_attacker);	Assert(retval2&&"memory!");
		retval2->dataref=retval;
		return(retval2);
}

DataInst*	toplevel_leader(file	ifile,TokenName	*pvalue)
{
	DataInst 	*retval=toplevel_target(ifile,pvalue,T_target);
ChainInst*
		retval2=new ChainInst(T_leader);	Assert(retval2&&"memory!");
		retval2->dataref=retval;
		return(retval2);
}

DataInst*	toplevel_follower(file	ifile,TokenName	*pvalue)
{
	DataInst 	*retval=toplevel_target(ifile,pvalue,T_target);
ChainInst*
		retval2=new ChainInst(T_follower);	Assert(retval2&&"memory!");
		retval2->dataref=retval;
		return(retval2);
}

DataInst*	toplevel_home(file	ifile,TokenName	*pvalue)
{
	DataInst 	*retval=toplevel_target(ifile,pvalue,T_target);
ChainInst*
		retval2=new ChainInst(T_home);	Assert(retval2&&"memory!");
		retval2->dataref=retval;
		return(retval2);
}

DataInst*	toplevel_target(file	ifile,TokenName	*pvalue,TokenCode tokencode)
{
TokenName	*type,*newname,*value,*sep;
DataInst 	*retval;
	if (pvalue->tokencode==T_unknown && tokencode==T_target)
		return(initchainref(pvalue,tokencode));
	elser
	if (pvalue->tokencode==T_target)				//if simple reference
		return(pvalue->instance);
	type = value = pvalue;
	newname=NULL;
	if (pvalue->tokencode==T_brktopen)
		GetTypeAndValue(ifile,type,newname,value,sep);
	if (tokencode==T_target)
			tokencode=type->tokencode;

	if (type)
	switch (tokencode)
	{
	case T_itemS:
			retval=toplevel_itemS(ifile,value);
		break;
	case T_itemG:
			retval=toplevel_itemG(ifile,value);
		break;
	case T_itemA:
			retval=toplevel_itemA(ifile,value);
		break;
	case T_itemgrp:
		retval=toplevel_itemgrp(ifile,value);
	break;
	case T_gndgrp:
		retval=toplevel_gndgrp(ifile,value);
	break;
	case T_airgrp:
		retval=toplevel_airgrp(ifile,value);
	break;
	case T_route:
		retval=toplevel_route(ifile,value);
	break;
	case T_waypoint:
		retval=toplevel_waypoint(ifile,value);
	break;
	case T_setUID:
		retval=itemlevel_setUID(ifile,value);
	break;
	default:
		EmitSysErr("Expecting Item variant inside Target");
	}
	setupnewnamereference(newname,retval);
	if (value!=pvalue)
		if (!getlistseparator(ifile,sep))
			EmitSysErr("Can only specify 1 item in Target");
	{
ChainInst*
		retval2=new ChainInst(T_target);	Assert(retval2&&"memory!");
		retval2->dataref=retval;
		return(retval2);
	}
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		toplevel_itemA
//Author		Jim Taylor
//Date			Mon 27 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
DataInst*	toplevel_itemA(file	ifile,TokenName	*pvalue)
{
const	TokenCode	T_T=T_itemA;
TokenName	*type,*newname,*value,*sep;
DataInst 	*retval;
LPair	 	list;
enum		XClusive
			{Xzero=0,XsetUID=1,Xnat=2,Xshape=4,Xband=8,Xmove=16,Xskill=32,
			Xdamage=64,
			Xtarget=128,Xtype=256,Xduty=512,Xform=1024,Xattitude=2048,
			Xmorale=4096,Xcharacter=8192,Xevent=16384,Xleader=32768,
			Xattacker=65536,Xvel=0x20000,Xsquad=0x40000,Xhome=0x80000,Xfollower=0x100000,Xbombs=0x200000
			}
			Xclusive=Xzero;
//DeadCode JIM 30Nov95 BITABLE		(XClusive);

	if (pvalue->tokencode==T_unknown)			//if simple forward reference
		return(initchainref(pvalue,T_T));
	elser
	if (pvalue->tokencode==T_T)				//if simple reference
		return(pvalue->instance);
	elser
	if (pvalue->tokencode!=T_brktopen)
		EmitSysErr("Argument must be AirItem type, not %s",
			pvalue->TokenText());
	elser
	{
		for(;;)
		{	//looping read of body of bfield header
			GetTypeAndValue(ifile,type,newname,value,sep);
			if (type)
			switch (type->tokencode)
			{
			case T_setUID:
				Xclusive=(XClusive)
					repeattest(Xclusive,XsetUID,0,"AirItem",type->TokenText());
				retval=itemlevel_setUID(ifile,value);
			break;
			case T_nation:
				Xclusive=(XClusive)
					repeattest(Xclusive,Xnat,0,"AirItem",type->TokenText());
				retval=toplevel_nation(ifile,value);
			break;
			case T_shape:
				Xclusive=(XClusive)
					repeattest(Xclusive,Xshape,0,"AirItem",type->TokenText());
				retval=toplevel_shape(ifile,value);
			break;
			case T_type:
				Xclusive=(XClusive)
					repeattest(Xclusive,Xtype,0,"AirItem",type->TokenText());
				retval=toplevel_type(ifile,value);
			break;
			case T_vel:
				Xclusive=(XClusive)
					repeattest(Xclusive,Xvel,0,"AirItem",type->TokenText());
				retval=toplevel_vel(ifile,value);
			break;
			case T_UIDband:
				Xclusive=(XClusive)
					repeattest(Xclusive,Xband,0,"AirItem",type->TokenText());
				if (Xclusive&XsetUID)
					EmitSysErr("UID band set after UID set!");
				retval=toplevel_UIDband(ifile,value);
			break;
			case T_move:
				Xclusive=(XClusive)
					repeattest(Xclusive,Xmove,0,"AirItem",type->TokenText());
				retval=toplevel_move(ifile,value);
			break;
			case T_skill:
				Xclusive=(XClusive)
					repeattest(Xclusive,Xskill,0,"AirItem",type->TokenText());
				retval=toplevel_skill(ifile,value);
			break;
			case T_morale:
				Xclusive=(XClusive)
					repeattest(Xclusive,Xmorale,0,"AirItem",type->TokenText());
				retval=toplevel_morale(ifile,value);
			break;
			case T_character:
				Xclusive=(XClusive)
					repeattest(Xclusive,Xcharacter,0,"AirItem",type->TokenText());
				retval=toplevel_character(ifile,value);
			break;
			case T_damage:
				Xclusive=(XClusive)
					repeattest(Xclusive,Xdamage,0,"AirItem",type->TokenText());
				retval=toplevel_damage(ifile,value);
			break;
			case T_target:
				Xclusive=(XClusive)
					repeattest(Xclusive,Xtarget,0,"AirItem",type->TokenText());
				retval=toplevel_target(ifile,value,type->tokencode);
			break;
			case T_leader:
				Xclusive=(XClusive)
					repeattest(Xclusive,Xleader,0,"AirItem",type->TokenText());
				retval=toplevel_leader(ifile,value);
			break;
			case T_attacker:
				Xclusive=(XClusive)
					repeattest(Xclusive,Xattacker,0,"AirItem",type->TokenText());
				retval=toplevel_attacker(ifile,value);
			break;
			case T_follower:
				Xclusive=(XClusive)
					repeattest(Xclusive,Xfollower,0,"AirItem",type->TokenText());
				retval=toplevel_follower(ifile,value);
			break;
			case T_home:
				Xclusive=(XClusive)
					repeattest(Xclusive,Xhome,0,"AirItem",type->TokenText());
				retval=toplevel_home(ifile,value);
			break;
			case T_event:
				Xclusive=(XClusive)
					repeattest(Xclusive,Xevent,0,"AirItem",type->TokenText());
				retval=toplevel_event(ifile,value);
			break;
			case T_bombs:
				Xclusive=(XClusive)
					repeattest(Xclusive,Xbombs,0,"AirItem",type->TokenText());
				retval=toplevel_bombs(ifile,value);
			break;
			case T_att:
				Xclusive=(XClusive)
					repeattest(Xclusive,Xattitude,0,"AirItem",type->TokenText());
				retval=toplevel_att(ifile,value);
			break;
			case T_paintscheme:
//DeadCode JIM 19Aug96 				Xclusive=(XClusive)
//DeadCode JIM 19Aug96 					repeattest(Xclusive,Xpaint,0,"AirItem",type->TokenText());
				retval=toplevel_paintscheme(ifile,value);
			break;
			case T_squadron:
				Xclusive=(XClusive)
					repeattest(Xclusive,Xsquad,0,"AirItem",type->TokenText());
				retval=toplevel_squadron(ifile,value);
			break;
			default:
				EmitSysErr("Type of symbol not valid within AirItem: %s",
					type->TokenText());
			}

			setupnewnamereference(newname,retval);
			list.Add(retval);
		breakif (getlistseparator(ifile,sep));
		}
	return(list.Code(T_T,pvalue));
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		toplevel_waypoint
//Author		Jim Taylor
//Date			Mon 27 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
DataInst*	toplevel_waypoint(file	ifile,TokenName	*pvalue)
{
const	TokenCode	T_T=T_waypoint;
TokenName	*type,*newname,*value,*sep;
DataInst 	*retval;
LPair	 	list;
enum		XClusive
			{Xzero=0,XsetUID=1,Xpos=2,Xaction=4,Xtarget=8,Xrange=16,Xevent=32,Xvel=64}
			Xclusive=Xzero;
//DeadCode JIM 30Nov95 BITABLE		(XClusive);

	if (pvalue->tokencode==T_unknown)			//if simple forward reference
		return(initchainref(pvalue,T_T));
	elser
	if (pvalue->tokencode==T_T)				//if simple reference
		return(pvalue->instance);
	elser
	if (pvalue->tokencode==T_3dsref)				//if simple reference
	{	//I have SimpleItem	RendererID
		//want to create sequence UIDband=simple, pos=renderID, action=noaction
		return ((LinkInst*) ((ChainInst*) pvalue->instance)->dataref)->sibling->dataref;
	}
	elser
	if (pvalue->tokencode!=T_brktopen)
		EmitSysErr("Argument must be Waypoint type, not %s",
			pvalue->TokenText());
	elser
	{
		for(;;)
		{	//looping read of body of bfield header
			GetTypeAndValue(ifile,type,newname,value,sep);
			if (type)
			switch (type->tokencode)
			{
			case T_event:
//DeadCode MS 30May96 				Xclusive=(XClusive)
//DeadCode MS 30May96 					repeattest(Xclusive,Xevent,0,"WayPoint",type->TokenText());
				retval=toplevel_event(ifile,value);
			break;
			case T_start:
				retval=toplevel_time(ifile,value,T_start);
			break;
			case	T_vel:
				Xclusive=(XClusive)
					repeattest(Xclusive,Xvel,0,"WayPoint",type->TokenText());
				retval=toplevel_vel(ifile,value);
			break;
			case T_range:
				Xclusive=(XClusive)
					repeattest(Xclusive,Xrange,0,"WayPoint",type->TokenText());
				retval=toplevel_range(ifile,value);
			break;
			case T_rangepc:
				Xclusive=(XClusive)
					repeattest(Xclusive,Xrange,0,"WayPoint",type->TokenText());
				retval=toplevel_rangepc(ifile,value);
			break;

			case T_setUID:
				Xclusive=(XClusive)
					repeattest(Xclusive,XsetUID,0,"WayPoint",type->TokenText());
				retval=itemlevel_setUID(ifile,value);
			break;
			case T_pos:
				Xclusive=(XClusive)
					repeattest(Xclusive,Xpos,0,"WayPoint",type->TokenText());
				retval=toplevel_pos(ifile,value);
			break;
			case T_target:
				Xclusive=(XClusive)
					repeattest(Xclusive,Xtarget,0,"WayPoint",type->TokenText());
				if (Xclusive&Xpos)
					EmitSysErr("Error: Target must come before pos.");
				retval=toplevel_target(ifile,value,type->tokencode);
			break;
			case T_wpact:
				Xclusive=(XClusive)
					repeattest(Xclusive,Xaction,0,"WayPoint",type->TokenText());
				retval=toplevel_wpact(ifile,value);
			break;
			default:
				EmitSysErr("Type of symbol not valid within WayPoint: %s",
					type->TokenText());
			}

			setupnewnamereference(newname,retval);
			list.Add(retval);
		breakif (getlistseparator(ifile,sep));
		}
	return(list.Code(T_T,pvalue));
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		toplevel_event
//Author		Jim Taylor
//Date			Tue 9 Jan 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
DataInst*	toplevel_event(file	ifile,TokenName	*pvalue)
{
const	TokenCode	T_T=T_event;
TokenName	*type,*newname,*value,*sep;
DataInst 	*retval;
LPair	 	list;
enum		XClusive
			{Xzero=0,XsetUID=1,Xpos=2,Xaction=4,Xtarget=8,Xrange=16,Xevent=32}
			Xclusive=Xzero;
//DeadCode JIM 30Nov95 BITABLE		(XClusive);

	if (pvalue->tokencode==T_unknown)			//if simple forward reference
		return(initchainref(pvalue,T_T));
	elser
	if (pvalue->tokencode==T_T)				//if simple reference
		return(pvalue->instance);
	elser
	if (pvalue->tokencode!=T_brktopen)
		EmitSysErr("Argument must be Waypoint type, not %s",
			pvalue->TokenText());
	elser
	{
		for(;;)
		{	//looping read of body of bfield header
			GetTypeAndValue(ifile,type,newname,value,sep);
			if (type)
			switch (type->tokencode)
			{
			case T_event:
				retval=numeric_event(ifile,value);
			break;
			case T_start:
				retval=toplevel_time(ifile,value,T_start);
			break;
			case T_window:
				retval=toplevel_time(ifile,value,T_window);
			break;
			case T_setval:
				retval=bfsave_setval(ifile,value);
			break;
			default:
				EmitSysErr("Type of symbol not valid within WayPoint: %s",
					type->TokenText());
			}

			setupnewnamereference(newname,retval);
			list.Add(retval);
		breakif (getlistseparator(ifile,sep));
		}
	return(list.Code(T_T,pvalue));
	}

}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		toplevel_time
//Author		Jim Taylor
//Date			Tue 9 Jan 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
DataInst*	toplevel_time	(file	ifile,TokenName	*pvalue,TokenCode T_T)
{
TokenName	*type,*newname,*value,*sep;
DataInst 	*retval;
LPair	 	list;
enum		XClusive
			{Xzero=0,Xatt=4,X_x=8,X_y=16,X_z=32,Xabs=64,Xrel=128}
			Xclusive=Xzero;
//DeadCode JIM 30Nov95 BITABLE		(XClusive);

	if (pvalue->tokencode==T_unknown)			//if simple forward reference
		return(initchainref(pvalue,T_T));
	elser
	if (pvalue->tokencode==T_T)				//if simple reference
		return(pvalue->instance);
	elser
	if (pvalue->tokencode!=T_brktopen)
		EmitSysErr("Argument must be time type, not %s",
			pvalue->TokenText());
	elser
	{
		for(;;)
		{	//looping read of body of bfield header
			GetTypeAndValue(ifile,type,newname,value,sep);
			if (type)
			switch (type->tokencode)
			{
 			case T_hours:	//hours
				retval=toplevel_hours(ifile,value);
			break;
 			case T_mins:	//mins
				retval=toplevel_mins(ifile,value);
			break;
 			case T_secs:	//mins
				retval=toplevel_secs(ifile,value);
			break;
			default:
				EmitSysErr("Type of symbol not valid within WayPoint: %s",
					type->TokenText());
			}

			setupnewnamereference(newname,retval);
			list.Add(retval);
		breakif (getlistseparator(ifile,sep));
		}
	return(list.Code(T_T,pvalue));
	}

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		toplevel_pos
//Author		Jim Taylor
//Date			Mon 27 Nov 1995
//
//Description	make up a position
//				syntaxes:
//				Pos	renderID				--> pos {abs renderID}
//				Pos	itemS/itemG/itemA		--> pos {abs item}
//				pos{abs,rel,att}
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
DataInst*	toplevel_pos(file	ifile,TokenName	*pvalue)
{
const	TokenCode	T_T=T_pos;
TokenName	*type,*newname,*value,*sep;
DataInst 	*retval;
LPair	 	list;
enum		XClusive
			{Xzero=0,Xatt=4,X_x=8,X_y=16,X_z=32,Xabs=64,Xrel=128}
			Xclusive=Xzero;
//DeadCode JIM 30Nov95 BITABLE		(XClusive);

	if (pvalue->tokencode==T_unknown)			//if simple forward reference
		return(initchainref(pvalue,T_T));
	elser
	if (pvalue->tokencode==T_T)				//if simple reference
		return(pvalue->instance);
	elser
	if (pvalue->tokencode==T_3dsref)				//if simple reference
	{	//I have Pos	RendererID
		//want to create sequence pos{abs renderID}
		return ((LinkInst*) ((ChainInst*) pvalue->instance)->dataref)->sibling->dataref;
	}
	elser
	if (	(	(pvalue->tokencode==T_itemS)				//if simple reference
			||	(pvalue->tokencode==T_itemG)
			||	(pvalue->tokencode==T_itemA)
			)
		||	(	(pvalue->tokencode==T_itemgrp)				//if simple reference
			||	(pvalue->tokencode==T_gndgrp)
			||	(pvalue->tokencode==T_airgrp)
			)
		)
	{	//I have SimpleItem	pointer
		//want to create sequence pos{abs ref ID}
ChainInst*	retval=new ChainInst(T_pos);	Assert(retval&&"memory!");

		retval->dataref=new ChainInst(T_pos);	Assert(retval->dataref&&"memory!");

		// Insert target token between pos and item...

		ChainInst	*targptr;

		targptr = new ChainInst(T_target);	Assert(targptr&&"memory!");

  		targptr->dataref = pvalue->instance;

		((ChainInst*) retval->dataref)->dataref= targptr;

//DeadCode RJS 09Feb96 		((ChainInst*) retval->dataref)->dataref= pvalue->instance;
		return(retval);
	}
	elser
	if (pvalue->tokencode!=T_brktopen)
		EmitSysErr("Argument must be Pos (or item) type, not %s",
			pvalue->TokenText());
	elser
	{
		for(;;)
		{	//looping read of body of bfield header
			GetTypeAndValue(ifile,type,newname,value,sep);
			if (type)
			switch (type->tokencode)
			{
	 		case T_abs:
				if (	!(Xclusive&Xabs)
					&&	(Xclusive&Xrel)
					)
					EmitSysErr("First Abs after rel doesn't make sense!");
				Xclusive=(XClusive)(Xclusive|Xabs);
				retval=toplevel_abs(ifile,value);
			break;
	 		case T_rel:
				Xclusive=(XClusive)(Xclusive|Xrel);
				retval=toplevel_rel(ifile,value);
			break;
	 		case T_att:
				Xclusive=(XClusive)
					repeattest(Xclusive,Xatt,0,"Position",type->TokenText());
				retval=toplevel_att(ifile,value);
			break;
	 		case T_x:
				Xclusive=(XClusive)
					repeattest(Xclusive,X_x,0,"Position",type->TokenText());
				retval=toplevel_x(ifile,value);
			break;
	 		case T_y:
				Xclusive=(XClusive)
					repeattest(Xclusive,X_y,0,"Position",type->TokenText());
				retval=toplevel_y(ifile,value);
			break;
	 		case T_z:
				Xclusive=(XClusive)
					repeattest(Xclusive,X_z,0,"Position",type->TokenText());
				retval=toplevel_z(ifile,value);
			break;
			default:
				EmitSysErr("Type of symbol not valid within Pos: %s",
					type->TokenText());
			}

			setupnewnamereference(newname,retval);
			list.Add(retval);
		breakif (getlistseparator(ifile,sep));
		}
	return(list.Code(T_T,pvalue));
	}
}
					   
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		referenceonly_abs
//Author		Jim Taylor
//Date			Wed 29 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//DeadCode JIM 22Apr96 DataInst*	referenceonly_abs(file	ifile,TokenName	*pvalue)
//DeadCode JIM 22Apr96 {
//DeadCode JIM 22Apr96 	if (pvalue->tokencode==T_3dsref)
//DeadCode JIM 22Apr96 		return ((LinkInst*) ((ChainInst*) pvalue->instance)->dataref)->sibling->dataref;
//DeadCode JIM 22Apr96 	elser
//DeadCode JIM 22Apr96 		return(toplevel_target(ifile,pvalue));
//DeadCode JIM 22Apr96 }
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		toplevel_abs
//Author		Jim Taylor
//Date			Mon 27 Nov 1995
//
//Description	accept 3ds,item
//					or {abs,x,y,z}... abs disables x and z and v.v.
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
DataInst*	toplevel_abs(file	ifile,TokenName	*pvalue)
{
const	TokenCode	T_T=T_abs;
TokenName	*type,*newname,*value,*sep;
DataInst 	*retval;
LPair	 	list;
enum		XClusive
			{Xzero=0,Xabs=4,X_x=8,X_y=16,X_z=32}
			Xclusive=Xzero;
//DeadCode JIM 30Nov95 BITABLE		(XClusive);

	if (pvalue->tokencode==T_unknown)			//if simple forward reference
		return(initchainref(pvalue,T_T));
	elser
	if (	pvalue->tokencode==T_T				//if simple reference
	 	||	pvalue->tokencode==T_pos)				//if simple reference
		return(pvalue->instance);
	elser
	if (pvalue->tokencode==T_3dsref)				//if simple reference
	{	//I have Pos	RendererID
		//want to create sequence pos{abs renderID}
		EmitSysErr("not handling pos renderer IDs here properly yet!");
	}
	elser
	if (	(pvalue->tokencode==T_itemS)				//if simple reference
		||	(pvalue->tokencode==T_itemG)
		||	(pvalue->tokencode==T_itemA)
		||	(pvalue->tokencode==T_waypoint)
		)
	{	//I have SimpleItem	pointer
		//want to create sequence abs ref ID
ChainInst*	retval=new ChainInst(T_pos);	Assert(retval&&"memory!");
		retval->dataref=new ChainInst(T_pos);	Assert(retval->dataref&&"memory!");

		// Insert target token between pos and item...

		ChainInst	*targptr;

		targptr = new ChainInst(T_target);	Assert(targptr&&"memory!");

  		targptr->dataref = pvalue->instance;

		((ChainInst*) retval->dataref)->dataref= targptr;
		
//DeadCode RJS 09Feb96 		((ChainInst*) retval->dataref)->dataref=pvalue->instance;
		return(retval);
	}
	elser
	if (	(pvalue->tokencode==T_itemgrp)				//if simple reference
		||	(pvalue->tokencode==T_gndgrp)
		||	(pvalue->tokencode==T_airgrp)
		)
	{	//I have SimpleItem	coords info
		//want to create sequence abs ref ID
ChainInst*	retval=new ChainInst(T_pos);	Assert(retval&&"memory!");
		retval->dataref=new ChainInst(T_pos);	Assert(retval->dataref&&"memory!");
		((ChainInst*) retval->dataref)->dataref=pvalue->instance;
		return(retval);
	}
	elser
	if (pvalue->tokencode!=T_brktopen)
		EmitSysErr("Argument must be Abs (or item) type, not %s",
			pvalue->TokenText());
	elser
	{
		for(;;)
		{	//looping read of body of bfield header
			GetTypeAndValue(ifile,type,newname,value,sep);
			if (type)
			switch (type->tokencode)
			{
	 		case T_3dsref:
				Xclusive=(XClusive)
					repeattest(Xclusive,Xabs,0,"Absolute",type->TokenText());
				if (Xclusive&(X_x|X_z))
					EmitSysErr("Can't define position after Abs X or Y");
				retval=((LinkInst*) ((ChainInst*) value->instance)->dataref)->sibling->dataref;
			break;
	 		case T_pos:
	 		case T_abs:
				Xclusive=(XClusive)
					repeattest(Xclusive,Xabs,0,"Absolute",type->TokenText());
				if (Xclusive&(X_x|X_z))
					EmitSysErr("Can't define position after Abs X or Y");
				retval=toplevel_target(ifile,value,T_target);
			break;
			case T_setUID:
				Xclusive=(XClusive)
					repeattest(Xclusive,Xabs,0,"Absolute",type->TokenText());
				if (Xclusive&(X_x|X_z))
					EmitSysErr("Can't define position after Abs X or Y");
				retval=toplevel_target(ifile,value,T_setUID);
			break;
	 		case T_x:
				Xclusive=(XClusive)
					repeattest(Xclusive,X_x,0,"Absolute",type->TokenText());
				if (Xclusive&Xabs)
					EmitSysErr("Can't define abs X after position");
				retval=toplevel_x(ifile,value);
			break;
	 		case T_y:
				Xclusive=(XClusive)
					repeattest(Xclusive,X_y,0,"Absolute",type->TokenText());
				retval=toplevel_y(ifile,value);
			break;
	 		case T_z:
				Xclusive=(XClusive)
					repeattest(Xclusive,X_z,0,"Absolute",type->TokenText());
				if (Xclusive&Xabs)
					EmitSysErr("Can't define abs Z after position");
				retval=toplevel_z(ifile,value);
			break;
			default:
				EmitSysErr("Type of symbol not valid within Absolute: %s",
					type->TokenText());
			}

			setupnewnamereference(newname,retval);
			list.Add(retval);
		breakif (getlistseparator(ifile,sep));
		}
	return(list.Code(T_T,pvalue));
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		toplevel_icpt
//Author		Jim Taylor
//Date			Mon 27 Nov 1995									//JIM 08Feb96
//
//Description	Relative coord modification
//				
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
DataInst*	toplevel_icpt(file	ifile,TokenName	*pvalue)
{
const	TokenCode	T_T=T_icpt;
TokenName	*type,*newname,*value,*sep;
DataInst 	*retval;
LPair	 	list;
//DeadCode JIM 30Nov95 BITABLE		(XClusive);

	if (pvalue->tokencode==T_unknown)			//if simple forward reference
		return(initchainref(pvalue,T_T));
	elser
	if (pvalue->tokencode==T_T)				//if simple reference
		return(pvalue->instance);
	elser
	if (pvalue->tokencode!=T_brktopen)
		EmitSysErr("Argument must be Intercept type, not %s",
			pvalue->TokenText());
	elser
	{
		Bool	rv;
		int	i=1;
		for(rv=FALSE,i=2;i;rv=TRUE,i--)
		{	//looping read of body of bfield header
			GetTypeAndValue(ifile,type,newname,value,sep);
			if (type)
			switch (type->tokencode)
			{
	 		case T_rel:
	 		case T_setUID:
	 		case T_target:
	 		case T_itemS:
	 		case T_itemG:
	 		case T_itemA:
	 		case T_waypoint:
				retval=toplevel_target(ifile,value,type->tokencode);
			break;
			case T_3dsref:
			case T_pos:
				retval=toplevel_pos(ifile,value);
			break;
			default:
				EmitSysErr("Type of symbol not valid within Intercept: %s",
					type->TokenText());
			}

			setupnewnamereference(newname,retval);
			list.Add(retval);
		if (getlistseparator(ifile,sep)!=rv)
			EmitSysErr("Expecting 2 parameters in intercept");
		}
	return(list.Code(T_T,pvalue));
	}
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		toplevel_rel
//Author		Jim Taylor
//Date			Mon 27 Nov 1995
//
//Description	Relative coord modification
//				
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
DataInst*	toplevel_rel(file	ifile,TokenName	*pvalue)
{
const	TokenCode	T_T=T_rel;
TokenName	*type,*newname,*value,*sep;
DataInst 	*retval;
LPair	 	list;
enum		XClusive
			{Xzero=0,Xhdg=1,Xpitch=2,Xrange=4,X_x=8,X_y=16,X_z=32,Xtarg=64}
			Xclusive=Xzero;
//DeadCode JIM 30Nov95 BITABLE		(XClusive);

	if (pvalue->tokencode==T_unknown)			//if simple forward reference
		return(initchainref(pvalue,T_T));
	elser
	if (pvalue->tokencode==T_T)				//if simple reference
		return(pvalue->instance);
	elser
	if (pvalue->tokencode!=T_brktopen)
		EmitSysErr("Argument must be Abs (or item) type, not %s",
			pvalue->TokenText());
	elser
	{
		for(;;)
		{	//looping read of body of bfield header
			GetTypeAndValue(ifile,type,newname,value,sep);
			if (type)
			switch (type->tokencode)
			{
	 		case T_rel:
	 		case T_target:
	 		case T_itemG:
	 		case T_itemA:
				Xclusive=(XClusive)
					repeattest(Xclusive,Xtarg,0,"Relative",type->TokenText());
				if (Xclusive&(Xhdg|Xpitch))
					EmitSysErr("Must define source attitude before rel hdg/pitch statement ");
				if (Xclusive&(X_x|X_z))
					EmitSysErr("Dont define source item for delta X,Z");
				retval=toplevel_target(ifile,value,type->tokencode);
			break;
			case T_icpt:
				Xclusive=(XClusive)
					repeattest(Xclusive,Xtarg,0,"Relative",type->TokenText());
				retval=toplevel_icpt(ifile,value);
			break;
	 		case T_x:
				Xclusive=(XClusive)
					repeattest(Xclusive,X_x,0,"Relative",type->TokenText());
				if (Xclusive&(Xhdg|Xrange))
					EmitSysErr("Can't define rel X after hdg/range in 1 rel statement.");
				if (Xclusive&(Xtarg))
					EmitSysErr("Dont define source item for delta X,Z");
				retval=toplevel_x(ifile,value);
			break;
	 		case T_y:
				Xclusive=(XClusive)
					repeattest(Xclusive,X_y,0,"Relative",type->TokenText());
				if (Xclusive&(Xpitch))
					EmitSysErr("Can't define rel Y after asimuth pitch in 1 rel statement.");
				if (Xclusive&(Xtarg))
					EmitSysErr("Dont define source item for delta X,Z");
				retval=toplevel_y(ifile,value);
			break;
	 		case T_z:
				Xclusive=(XClusive)
					repeattest(Xclusive,X_z,0,"Relative",type->TokenText());
				if (Xclusive&(Xhdg|Xrange))
					EmitSysErr("Can't define rel Z after hdg/range in 1 rel statement.");
				retval=toplevel_z(ifile,value);
			break;
	 		case T_bearing:
	 		case T_hdg:
				Xclusive=(XClusive)
					repeattest(Xclusive,Xhdg,0,"Relative",type->TokenText());
				if (Xclusive&(X_x|X_z))
					EmitSysErr("Can't define hdg/range after rel Z in 1 rel statement.");
				retval=toplevel_bearing(ifile,value);
			break;
	 		case T_asimuth:
	 		case T_pitch:
				Xclusive=(XClusive)
					repeattest(Xclusive,Xpitch,0,"Relative",type->TokenText());
				if (Xclusive&X_y)
					EmitSysErr("Can't define asimuth after rel Y in 1 rel statement.");
				retval=toplevel_pitch(ifile,value);
			break;
			case T_range:
				Xclusive=(XClusive)
					repeattest(Xclusive,Xrange,0,"Relative",type->TokenText());
				if (Xclusive&(X_x|X_z))
					EmitSysErr("Can't define hdg/range after rel Z in 1 rel statement.");
				retval=toplevel_range(ifile,value);
			break;
			case T_rangepc:
				Xclusive=(XClusive)
					repeattest(Xclusive,Xrange,0,"Relative",type->TokenText());
				if (Xclusive&(X_x|X_z))
					EmitSysErr("Can't define hdg/range after rel Z in 1 rel statement.");
				retval=toplevel_rangepc(ifile,value);
			break;
			default:
				EmitSysErr("Type of symbol not valid within Relative: %s",
					type->TokenText());
			}

			setupnewnamereference(newname,retval);
			list.Add(retval);
		breakif (getlistseparator(ifile,sep));
		}
	if (	Xclusive&(Xhdg|Xpitch)
		 && !(Xclusive&(Xrange))
		)
		EmitSysErr("Rel statement contains bearing or asimuth, but no range!");
	return(list.Code(T_T,pvalue));
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		toplevel_att
//Author		Jim Taylor
//Date			Mon 27 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
DataInst*	toplevel_att(file	ifile,TokenName	*pvalue)
{
const	TokenCode	T_T=T_att;
TokenName	*type,*newname,*value,*sep;
DataInst 	*retval;
LPair	 	list;
enum		XClusive
			{Xzero=0,Xhdg=1,Xpitch=2,Xroll=4,Xtarg=8,Xrange=16}
			Xclusive=Xzero;
//DeadCode JIM 30Nov95 BITABLE		(XClusive);

	if (pvalue->tokencode==T_unknown)			//if simple forward reference
		return(initchainref(pvalue,T_T));
	elser
	if (pvalue->tokencode==T_T)					//if simple reference
		return(pvalue->instance);
	elser
	if (pvalue->tokencode!=T_brktopen)
		EmitSysErr("Argument must be Abs (or item) type, not %s",
			pvalue->TokenText());
	elser
	{
		for(;;)
		{	//looping read of body of bfield header
			GetTypeAndValue(ifile,type,newname,value,sep);
			if (type)
			switch (type->tokencode)
			{
	 		case T_rel:
	 		case T_target:
	 		case T_itemG:
	 		case T_itemA:
				Xclusive=(XClusive)
					repeattest(Xclusive,Xtarg,0,"Attitude",type->TokenText());
				if (Xclusive&(Xhdg|Xpitch|Xroll))
					EmitSysErr("Item to copy hdg from must come before deltas!");
				retval=toplevel_target(ifile,value,type->tokencode);
			break;
			case T_icpt:
				Xclusive=(XClusive)
					repeattest(Xclusive,Xtarg,0,"Relative",type->TokenText());
				retval=toplevel_icpt(ifile,value);
			break;
	 		case T_hdg:
				Xclusive=(XClusive)
					repeattest(Xclusive,Xhdg,0,"Attitude",type->TokenText());
				retval=toplevel_bearing(ifile,value);
			break;
	 		case T_pitch:
				Xclusive=(XClusive)
					repeattest(Xclusive,Xpitch,0,"Attitude",type->TokenText());
				retval=toplevel_pitch(ifile,value);
			break;
	 		case T_roll:
				Xclusive=(XClusive)
					repeattest(Xclusive,Xroll,0,"Attitude",type->TokenText());
				retval=toplevel_roll(ifile,value);
			break;
			default:
				EmitSysErr("Type of symbol not valid within Attitude: %s",
					type->TokenText());
			}

			setupnewnamereference(newname,retval);
			list.Add(retval);
		breakif (getlistseparator(ifile,sep));
		}
//DeadCode DAW 08Apr96 	if (	Xclusive&(Xhdg|Xpitch)
//DeadCode DAW 08Apr96 		 && !(Xclusive&(Xrange))
//DeadCode DAW 08Apr96 		)
//DeadCode DAW 08Apr96 		EmitSysErr("Rel statement contains bearing or asimuth, but no range!");
	return(list.Code(T_T,pvalue));
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		toplevel_att
//Author		Jim Taylor
//Date			Mon 27 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
DataInst*	toplevel_squadron(file	ifile,TokenName	*pvalue)
{
const	TokenCode	T_T=T_squadron;
TokenName	*type,*newname,*value,*sep;
DataInst 	*retval;
LPair	 	list;
enum		XClusive
			{Xzero=0,Xhome=1,Xtype=2,Xskill=4,Xchar=8,Xtext=16}
			Xclusive=Xzero;

	if (pvalue->tokencode==T_unknown)			//if simple forward reference
		return(initchainref(pvalue,T_T));
	elser
	if (pvalue->tokencode==T_T)					//if simple reference
		return(pvalue->instance);
	elser
	if (pvalue->tokencode!=T_brktopen)
		EmitSysErr("Argument must be Abs (or item) type, not %s",
			pvalue->TokenText());
	elser
	{
		for(;;)
		{	//looping read of body of bfield header
			GetTypeAndValue(ifile,type,newname,value,sep);
			if (type)
			switch (type->tokencode)
			{
			case T_squadron:
				 retval=toplevel_squadron(ifile,value);
			break;
			case T_paintscheme:
				 retval=toplevel_paintscheme(ifile,value);
			break;
			case T_home:
				 retval=toplevel_home(ifile,value);
			break;
			case T_type:
				 retval=toplevel_type(ifile,value);
			break;
			case T_skill:
				 retval=toplevel_skill(ifile,value);
			break;
			case T_character:
				 retval=toplevel_character(ifile,value);
			break;

			default:
				EmitSysErr("Type of symbol not valid within Attitude: %s",
					type->TokenText());
			}

			setupnewnamereference(newname,retval);
			list.Add(retval);
		breakif (getlistseparator(ifile,sep));
		}
//DeadCode DAW 08Apr96 	if (	Xclusive&(Xhdg|Xpitch)
//DeadCode DAW 08Apr96 		 && !(Xclusive&(Xrange))
//DeadCode DAW 08Apr96 		)
//DeadCode DAW 08Apr96 		EmitSysErr("Rel statement contains bearing or asimuth, but no range!");
	return(list.Code(T_T,pvalue));
	}


}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		toplevel_paintscheme
//Author		Jim Taylor
//Date			Mon 27 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
DataInst*	toplevel_paintscheme(file	ifile,TokenName	*pvalue)
{
	return(toplevel_enumorint(ifile,pvalue,T_paintscheme));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		toplevel_paintscheme
//Author		Jim Taylor
//Date			Mon 27 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//DeadCode JIM 31Jul96 DataInst*	toplevel_paintscheme(file	ifile,TokenName	*pvalue)
//DeadCode JIM 31Jul96 {
//DeadCode JIM 31Jul96 DataRef	tmpenumval=toplevel_enumval(ifile,pvalue,T_paintscheme);
//DeadCode JIM 31Jul96 	if (tmpenumval->tokencode!=T_paintscheme)
//DeadCode JIM 31Jul96 		EmitSysErr("Expecting PaintScheme enum, but got %s",
//DeadCode JIM 31Jul96 			pvalue->TokenText());
//DeadCode JIM 31Jul96 	elser
//DeadCode JIM 31Jul96 		return(tmpenumval);
//DeadCode JIM 31Jul96 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		toplevel_enumval
//Author		Jim Taylor
//Date			Wed 29 Nov 1995
//
//Description	Process the declaration of an enum value
//				returns an enum value chain or an integer value
//				integer value must be converted to enum value chain
//				
//				Syntax for Random and Select is done here:
//				{Random	steps,base,stepsize}
//				{Select	selvar,base,stepsize}
//				If any of the types if the fields are not int, 
//				then they must be the same type. 
//				The returned tree will be of this type
//
//				type ->	sel/rnd	-->	link -> steps/selvar
//									link -> base		(opt)
//									link -> stepsize	(opt)
//
//Inputs		tokenname is a name, an integer, or a "{"
//
//Returns		name, integer or expanded "{"
//
//------------------------------------------------------------------------------
DataInst*	enumval_list(file	ifile,TokenName	*pvalue,TokenCode	defaultcode,TokenName* sep)
{
TokenName	*type,	*newname,	*value;
DataInst	*retval;
LPair	 	list;
TokenCode	retcode=defaultcode;
			retval=toplevel_enumval(ifile,pvalue,defaultcode);
			list.Add(retval);
			while (!getlistseparator(ifile,sep))
			{
				GetTypeAndValue(ifile,type,newname,value,sep);
				retval=toplevel_enumval(ifile,value,defaultcode);
				if (retval->tokencode!=defaultcode)
					if (	retval->tokencode==T_count
						||	retval->tokencode==T_int
						||	retval->tokencode==T_nint
						)
						retcode=T_count;
					else
						EmitSysErr("Entry in list not same as list type");
				list.Add(retval);
			}
			if (retcode==T_count)
				return(list.Code(T_list,pvalue));
			else
			{
			ChainInst*
				tmplink=new	ChainInst(defaultcode);	Assert(tmplink&&"memory!");
				tmplink->dataref=list.Code(T_list,pvalue);
				return(tmplink);
			}
}
//------------------------------------------------------------------------------
DataInst*	toplevel_enumval(file	ifile,TokenName	*pvalue,TokenCode	defaultcode)
{
TokenName	*type,	*newname,	*value,	*sep;
DataInst	*retval;
LPair	 	list;
TokenCode	selcode=T_unknown,	conttype=T_count,
			starttype=T_count,steptype=T_count;
	if (pvalue->tokencode==T_unknown)			//if simple forward reference
		return(initchainref(pvalue,defaultcode));
	elser
	if (pvalue->tokencode!=T_brktopen)			//if simple reference
		return(pvalue->instance);				//leave to caller to check
	elser
	{	//not the usual mumbojumbo.
		//only 2 systems are allowed here - random or sequencevar
		//ADDITIONAL SYSEM: List
		GetTypeAndValue(ifile,type,newname,value,sep);
		if (type)
		{
			if (newname)
				EmitSysErr("Can't perform assignment inside Random/Select");
			selcode=type->tokencode;

			if (selcode==T_list)
				RETURN(enumval_list(ifile, value,defaultcode,sep));

			if (	(selcode!=T_random)
				&&	(selcode!=T_select)
				)
				EmitSysErr("Expecting Select or Random inside enum{");
			retval=toplevel_enumval(ifile,value,defaultcode);
			list.Add(retval);
			conttype=retval->tokencode;

			if (!getlistseparator(ifile,sep))
			{
				GetTypeAndValue(ifile,type,newname,value,sep);
				if (newname)
					EmitSysErr("Can't perform assignment inside Random/Select");
				if (type)
				{
					retval=toplevel_enumval(ifile,value,defaultcode);
					list.Add(retval);
					starttype=conttype;
					conttype=retval->tokencode;

					if (!getlistseparator(ifile,sep))
					{
						GetTypeAndValue(ifile,type,newname,value,sep);
						if (newname)
							EmitSysErr("Can't perform assignment inside Random/Select");
						if (type)
						{
							retval=toplevel_enumval(ifile,value,defaultcode);
							list.Add(retval);
							steptype=retval->tokencode;

							if (!getlistseparator(ifile,sep))
								EmitSysErr("Only expecting 3 params in Select/Random");
						}
					}
				}
			}
		}
		//at this point I have defined loads of things...
		//I have built a list and held the tokentypes
		//now check for non-int
		if (	(steptype==T_count)||(steptype==T_nint)||(steptype==T_int)	)
			steptype=conttype;
		if (	(starttype==T_count)&&(starttype==T_nint)&&(starttype!=T_int)
			 && (starttype!=steptype)
			)
				EmitSysErr("A:Types don't match for params in Select/Random");
		if (	(steptype==T_count )		//if all are integers
			&&	(defaultcode!=T_count)
			)
			return(list.Code(selcode,pvalue));
		elser
		{
			if (steptype==T_int || steptype==T_nint)
				steptype=T_count;
			retval=new ChainInst(steptype);	Assert(retval&&"memory!");
			((ChainInst*) retval)->dataref=list.Code(selcode,pvalue);
			return(retval);
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		toplevel_enumorint
//Author		Jim Taylor
//Date			Wed 20 Mar 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
DataInst*	toplevel_enumorint(file	ifile,TokenName *pvalue,TokenCode T)
{
DataRef	tmpenumval=toplevel_enumval(ifile,pvalue,T);
	if (tmpenumval->tokencode==T)
		return(tmpenumval);
	elser
	if (	(tmpenumval->tokencode!=T_int)
		&&	(tmpenumval->tokencode!=T_nint)
		&&	(tmpenumval->tokencode!=T_count)
		&&	(tmpenumval->tokencode!=T_random)
		&&	(tmpenumval->tokencode!=T_list)
		&&	(tmpenumval->tokencode!=T_select)
		)
		EmitSysErr("Expecting integer for %s, but got %s",
			getcodename(T),
			pvalue->TokenText());
	elser
	{
	ChainInst*
		tmplink=new	ChainInst(T);	Assert(tmplink&&"memory!");
		tmplink->dataref=tmpenumval;
		return(tmplink);
	}
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		toplevel_enumorangle
//Author		Jim Taylor
//Date			Wed 20 Mar 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
DataInst*	toplevel_enumorangle(file	ifile,TokenName *pvalue,TokenCode T)
{
DataRef	tmpenumval=toplevel_enumval(ifile,pvalue,T);
	if (tmpenumval->tokencode==T)
		return(tmpenumval);
	elser
	if (	(tmpenumval->tokencode!=T_angle)
		&&	(tmpenumval->tokencode!=T_random)
		&&	(tmpenumval->tokencode!=T_list)
		&&	(tmpenumval->tokencode!=T_select)
		)
		EmitSysErr("Expecting integer for %s, but got %s",
			getcodename(T),
			pvalue->TokenText());
	elser
	{
	ChainInst*
		tmplink=new	ChainInst(T);	Assert(tmplink&&"memory!");
		tmplink->dataref=tmpenumval;
		return(tmplink);
	}
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		toplevel_inwing
//Author		Jim Taylor
//Date			Mon 27 Nov 1995
//
//Description	how many in a wing?
//				this is an enumerated or integer value
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
DataInst*	toplevel_inwing(file	ifile,TokenName	*pvalue)
{
	return(toplevel_enumorint(ifile,pvalue,T_inwing));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		toplevel_inform
//Author		Jim Taylor
//Date			Mon 27 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
DataInst*	toplevel_inform(file	ifile,TokenName	*pvalue)
{
	return(toplevel_enumorint(ifile,pvalue,T_inform));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		toplevel_skill
//Author		Jim Taylor
//Date			Mon 27 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
DataInst*	toplevel_skill(file	ifile,TokenName	*pvalue)
{
	return(toplevel_enumorint(ifile,pvalue,T_skill));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		toplevel_morale
//Author		Jim Taylor
//Date			Mon 27 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
DataInst*	toplevel_morale(file	ifile,TokenName	*pvalue)
{
	return(toplevel_enumorint(ifile,pvalue,T_morale));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		toplevel_character
//Author		Jim Taylor
//Date			Mon 27 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
DataInst*	toplevel_character(file	ifile,TokenName	*pvalue)
{
DataRef	tmpenumval=toplevel_enumval(ifile,pvalue,T_character);
	if (tmpenumval->tokencode!=T_character)
		EmitSysErr("Expecting character enum, but got %s",
			pvalue->TokenText());
	elser
		return(tmpenumval);

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		toplevel_damage
//Author		Jim Taylor
//Date			Mon 27 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
DataInst*	toplevel_damage(file	ifile,TokenName	*pvalue)
{
	return(toplevel_enumorint(ifile,pvalue,T_damage));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		toplevel_bombs
//Author		Jim Taylor
//Date			Mon 27 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
DataInst*	toplevel_bombs(file	ifile,TokenName	*pvalue)
{
	return(toplevel_enumorint(ifile,pvalue,T_bombs));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		toplevel_vel
//Author		Jim Taylor
//Date			Mon 27 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
DataInst*	toplevel_vel(file	ifile,TokenName	*pvalue)
{
	return(toplevel_enumorint(ifile,pvalue,T_vel));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		toplevel_level
//Author		Jim Taylor
//Date			Mon 27 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
DataInst*	toplevel_level(file	ifile,TokenName	*pvalue)
{
ChainInst	*tmplink;
DataRef	tmpenumval=toplevel_enumval(ifile,pvalue,T_level);
	if (tmpenumval->tokencode==T_level)
		tmplink=(ChainInst*)tmpenumval;
	else
	if (	(tmpenumval->tokencode==T_random)
		||	(tmpenumval->tokencode==T_select)
		||	(tmpenumval->tokencode==T_list)
		)
		EmitSysErr("Can't set the Level to random!");
	else
	if (	(tmpenumval->tokencode!=T_int)
		&&	(tmpenumval->tokencode!=T_count)
		)
		EmitSysErr("Expecting integer for Level, but got %s",
			pvalue->TokenText());
	else
	{
		tmplink=new	ChainInst(T_level);	Assert(tmplink&&"memory!");
		tmplink->dataref=tmpenumval;
	}
	Current_Level=((IntegerInst*) ((ChainInst*) tmplink)->dataref)->value;
	return(tmplink);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		toplevel_x
//Author		Jim Taylor
//Date			Mon 27 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
DataInst*	toplevel_x(file	ifile,TokenName	*pvalue)
{
	return(toplevel_enumorint(ifile,pvalue,T_x));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		toplevel_y
//Author		Jim Taylor
//Date			Mon 27 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
DataInst*	toplevel_y(file	ifile,TokenName	*pvalue)
{
	return(toplevel_enumorint(ifile,pvalue,T_y));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		toplevel_z
//Author		Jim Taylor
//Date			Mon 27 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
DataInst*	toplevel_z(file	ifile,TokenName	*pvalue)
{
	return(toplevel_enumorint(ifile,pvalue,T_z));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		toplevel_range
//Author		Jim Taylor
//Date			Thu 30 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
DataInst*	toplevel_range(file	ifile,TokenName	*pvalue)
{
	return(toplevel_enumorint(ifile,pvalue,T_range));
}
//DeadCode DAW 08Apr96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode DAW 08Apr96 //Procedure		toplevel_range
//DeadCode DAW 08Apr96 //Author		Jim Taylor
//DeadCode DAW 08Apr96 //Date			Thu 30 Nov 1995
//DeadCode DAW 08Apr96 //
//DeadCode DAW 08Apr96 //Description	
//DeadCode DAW 08Apr96 //
//DeadCode DAW 08Apr96 //Inputs		
//DeadCode DAW 08Apr96 //
//DeadCode DAW 08Apr96 //Returns	
//DeadCode DAW 08Apr96 //
//DeadCode DAW 08Apr96 //------------------------------------------------------------------------------
//DeadCode DAW 08Apr96 DataInst*	toplevel_vel(file	ifile,TokenName	*pvalue)
//DeadCode DAW 08Apr96 {
//DeadCode DAW 08Apr96 	return(toplevel_enumorint(ifile,pvalue,T_vel));
//DeadCode DAW 08Apr96 }
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		toplevel_range
//Author		Jim Taylor
//Date			Thu 30 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
DataInst*	toplevel_rangepc(file	ifile,TokenName	*pvalue)
{
	return(toplevel_enumorint(ifile,pvalue,T_rangepc));
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		toplevel_count
//Author		Jim Taylor
//Date			Thu 30 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
DataInst*	toplevel_count(file	ifile,TokenName	*pvalue)
{
	return(toplevel_enumorint(ifile,pvalue,T_count));
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		toplevel_hours
//Author		Jim Taylor
//Date			Thu 30 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
DataInst*	toplevel_hours(file	ifile,TokenName	*pvalue)
{
	return(toplevel_enumorint(ifile,pvalue,T_hours));
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		toplevel_mins
//Author		Jim Taylor
//Date			Thu 30 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
DataInst*	toplevel_mins(file	ifile,TokenName	*pvalue)
{
	return(toplevel_enumorint(ifile,pvalue,T_mins));
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		toplevel_secs
//Author		Jim Taylor
//Date			Thu 30 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
DataInst*	toplevel_secs(file	ifile,TokenName	*pvalue)
{
	return(toplevel_enumorint(ifile,pvalue,T_secs));
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		toplevel_UIDband
//Author		Jim Taylor
//Date			Mon 27 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
DataInst*	toplevel_UIDband(file	ifile,TokenName	*pvalue)
{
DataRef	tmpenumval=toplevel_enumval(ifile,pvalue,T_UIDband);
	if (tmpenumval->tokencode!=T_UIDband)
		EmitSysErr("Expecting UIDband enum, but got %s",
			pvalue->TokenText());
	elser
		return(tmpenumval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		toplevel_briefID
//Author		Jim Taylor
//Date			Mon 27 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
DataInst*	toplevel_briefID(file	ifile,TokenName	*pvalue)
{
DataRef	tmpenumval=toplevel_enumval(ifile,pvalue,T_briefID);
	if (tmpenumval->tokencode!=T_briefID)
		EmitSysErr("Expecting briefUI enum, but got %s",
			pvalue->TokenText());
	elser
		return(tmpenumval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		toplevel_nation
//Author		Jim Taylor
//Date			Mon 27 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
DataInst*	toplevel_nation(file	ifile,TokenName	*pvalue)
{
DataRef	tmpenumval=toplevel_enumval(ifile,pvalue,T_nation);
	if (tmpenumval->tokencode!=T_nation)
		EmitSysErr("Expecting Nationality enum, but got %s",
			pvalue->TokenText());
	elser
		return(tmpenumval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		toplevel_shape
//Author		Jim Taylor
//Date			Mon 27 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
DataInst*	toplevel_shape(file	ifile,TokenName	*pvalue)
{
	if (pvalue->tokencode==T_3dsref)
	{
		EmitSysErr("Not handling 3ds items yet!");
	}
	elser
DataRef	tmpenumval=toplevel_enumval(ifile,pvalue,T_shape);
	if (tmpenumval->tokencode!=T_shape)
		EmitSysErr("Expecting shape enum, but got %s",
			pvalue->TokenText());
	elser
		return(tmpenumval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		toplevel_type
//Author		Jim Taylor
//Date			Mon 27 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
DataInst*	toplevel_type(file	ifile,TokenName	*pvalue)
{
DataRef	tmpenumval=toplevel_enumval(ifile,pvalue,T_type);
	if (tmpenumval->tokencode!=T_type)
		EmitSysErr("Expecting planetype/trucktype enum, but got %s",
			pvalue->TokenText());
	elser
		return(tmpenumval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		toplevel_duty
//Author		Jim Taylor
//Date			Mon 27 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
DataInst*	toplevel_duty(file	ifile,TokenName	*pvalue)
{
DataRef	tmpenumval=toplevel_enumval(ifile,pvalue,T_duty);
	if (tmpenumval->tokencode!=T_duty)
		EmitSysErr("Expecting duty enum, but got %s",
			pvalue->TokenText());
	elser
		return(tmpenumval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		toplevel_form
//Author		Jim Taylor
//Date			Mon 27 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
DataInst*	toplevel_form(file	ifile,TokenName	*pvalue)
{
DataRef	tmpenumval=toplevel_enumval(ifile,pvalue,T_form);
	if (tmpenumval->tokencode!=T_form)
		EmitSysErr("Expecting formation enum, but got %s",
			pvalue->TokenText());
	elser
		return(tmpenumval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		toplevel_move
//Author		Jim Taylor
//Date			Mon 27 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
DataInst*	toplevel_move(file	ifile,TokenName	*pvalue)
{
DataRef	tmpenumval=toplevel_enumval(ifile,pvalue,T_move);
	if (tmpenumval->tokencode!=T_move)
		EmitSysErr("Expecting movecode/manoeuvre enum, but got %s",
			pvalue->TokenText());
	elser
		return(tmpenumval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		toplevel_event
//Author		Jim Taylor
//Date			Mon 27 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
DataInst*	numeric_event(file	ifile,TokenName	*pvalue)
{
DataRef	tmpenumval=toplevel_enumval(ifile,pvalue,T_event);
	if (tmpenumval->tokencode==T_event)
		return(tmpenumval);
	else
	if (	tmpenumval->tokencode!=T_fname
		&&	tmpenumval->tokencode!=T_list
		&&	tmpenumval->tokencode!=T_random
		)
		EmitSysErr("Expecting Event name, but got %s",
			pvalue->TokenText());
	elser
	{
	ChainInst*
		tmplink=new	ChainInst(T_event);	Assert(tmplink&&"memory!");
		tmplink->dataref=tmpenumval;
		return(tmplink);
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		toplevel_wpact
//Author		Jim Taylor
//Date			Mon 27 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
DataInst*	toplevel_wpact(file	ifile,TokenName	*pvalue)
{
DataRef	tmpenumval=toplevel_enumval(ifile,pvalue,T_wpact);
	if (tmpenumval->tokencode!=T_wpact)
		EmitSysErr("Expecting waypoint action enum, but got %s",
			pvalue->TokenText());
	elser
		return(tmpenumval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		toplevel_bearing
//Author		Jim Taylor
//Date			Mon 27 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
DataInst*	toplevel_bearing(file	ifile,TokenName	*pvalue)
{
	return(toplevel_enumorangle(ifile,pvalue,T_bearing));
}

//DeadCode JIM 20Mar96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JIM 20Mar96 //Procedure		toplevel_hdg
//DeadCode JIM 20Mar96 //Author		Jim Taylor
//DeadCode JIM 20Mar96 //Date			Mon 27 Nov 1995
//DeadCode JIM 20Mar96 //
//DeadCode JIM 20Mar96 //Description	
//DeadCode JIM 20Mar96 //
//DeadCode JIM 20Mar96 //Inputs		
//DeadCode JIM 20Mar96 //
//DeadCode JIM 20Mar96 //Returns	
//DeadCode JIM 20Mar96 //
//DeadCode JIM 20Mar96 //------------------------------------------------------------------------------
//DeadCode JIM 20Mar96 DataInst*	toplevel_hdg(file	ifile,TokenName	*pvalue)
//DeadCode JIM 20Mar96 {
//DeadCode JIM 20Mar96 	return(toplevel_enumorangle(ifile,pvalue,T_hdg));
//DeadCode JIM 20Mar96 }
//DeadCode JIM 20Mar96 

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		toplevel_pitch
//Author		Jim Taylor
//Date			Mon 27 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
DataInst*	toplevel_pitch(file	ifile,TokenName	*pvalue)
{
	return(toplevel_enumorangle(ifile,pvalue,T_pitch));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		toplevel_roll
//Author		Jim Taylor
//Date			Mon 27 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
DataInst*	toplevel_roll(file	ifile,TokenName	*pvalue)
{
	return(toplevel_enumorangle(ifile,pvalue,T_roll));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		toplevel_fname
//Author		Jim Taylor
//Date			Mon 27 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
DataInst*	toplevel_dirname(TokenName*&evalue,TokenName	*pvalue)
{
	if (pvalue->tokencode!=T_unknown)
		EmitSysErr("Expecting new directory name, not reference");
	elser
	{
		FNameInst	*tmp;
		pvalue->instance=
			tmp=new FNameInst;	Assert(tmp&&"memory!");
		tmp->tokentext=pvalue;
		tmp->filenumtext=evalue;
		tmp->tokencode=T_fname;
		tmp->filenumber=NULL;
		if (Battle_Dirs[Current_Level].dirname)
			EmitSysErr("Directory already named for level %i.\n Was: %s, Now: %s",
				Current_Level,Battle_Dirs[Current_Level].dirname,pvalue->TokenText());
		Battle_Dirs[Current_Level].dirname=pvalue->TokenText();
		pvalue->tokencode=T_fname;
		pvalue->usage=U_value;
		pvalue->defined=D_defined;
		if (!Current_Level)
			EmitSysErr("Level has not been set before first fname");
		evalue=NULL;
		return(tmp);
	}
}


DataInst*	toplevel_fname(TokenName*&evalue,TokenName	*pvalue)
{
	if (evalue)
	{
		if (evalue->tokencode==T_unknown)
		{
			evalue->instance=new ChainInst(T_event);
			evalue->instance->tokentext=evalue;
			evalue->tokencode=T_event;
		}
		else
		if (	evalue->tokencode!=T_event
			||	evalue->defined==D_defined
			||	evalue->defined==D_defused
			)
			EmitSysErr("Fwd ref to file (%s) wrong type - from %s(%i)",
				evalue->TokenText(),names[evalue->srcfname],evalue->srcfline);
		ChainInst*		tmpch;
		tmpch=(ChainInst*) evalue->instance;
		IntegerInst*	tmpint;
		tmpch->dataref=tmpint=new IntegerInst;
		tmpint->tokentext=evalue;
		evalue->defined=D_defused;
		evalue->usage=U_value;
	}
	if (pvalue->tokencode==T_unknown)
	{
		FNameInst	*tmp;
		pvalue->instance=
			tmp=new FNameInst;	Assert(tmp&&"memory!");
		tmp->tokentext=pvalue;
		tmp->filenumtext=evalue;
		tmp->tokencode=T_fname;
		if (evalue)
		{
			tmp->filenumber=((ChainInst*) evalue->instance)->dataref;
		}
		else
		{	//not got equate name... but still need to assign integer.
			IntegerInst*	tmpint;
			tmp->filenumber=tmpint=new IntegerInst;
		}
		pvalue->tokencode=T_fname;
		pvalue->usage=U_value;
		pvalue->defined=D_defined;
		((IntegerInst*) tmp->filenumber)->value=Current_Level<<8;
		if (!Current_Level)
			EmitSysErr("Level has not been set before first fname");
		evalue=NULL;
		return(tmp);
	}
	else
	if (pvalue->tokencode!=T_fname)
		EmitSysErr("Expecting filename, but found %s",pvalue->tokentext);
	else
	if (pvalue->defined!=D_defined)
		EmitSysErr("Same filename saved twice!! %s",pvalue->tokentext);
	evalue=NULL;
	return(pvalue->instance);
}
//DeadCode JIM 04Apr96 DataInst*	toplevel_fname(TokenName *evalue,TokenName	*pvalue)
//DeadCode JIM 04Apr96 {
//DeadCode JIM 04Apr96 	if (pvalue->tokencode==T_unknown)
//DeadCode JIM 04Apr96 	{
//DeadCode JIM 04Apr96 		FNameInst	*tmp;
//DeadCode JIM 04Apr96 		pvalue->instance=
//DeadCode JIM 04Apr96 			tmp=new FNameInst;	Assert(tmp&&"memory!");
//DeadCode JIM 04Apr96 		tmp->tokentext=pvalue;
//DeadCode JIM 04Apr96 		tmp->filenumtext=evalue;
//DeadCode JIM 04Apr96 		tmp->tokencode=T_fname;
//DeadCode JIM 04Apr96 		pvalue->tokencode=T_fname;
//DeadCode JIM 04Apr96 		pvalue->usage=U_value;
//DeadCode JIM 04Apr96 		pvalue->defined=D_defined;
//DeadCode JIM 04Apr96 	}
//DeadCode JIM 04Apr96 	else
//DeadCode JIM 04Apr96 	if (pvalue->tokencode!=T_fname)
//DeadCode JIM 04Apr96 		EmitSysErr("Expecting filename, but found %s",pvalue->tokentext);
//DeadCode JIM 04Apr96 	else
//DeadCode JIM 04Apr96 	if (pvalue->defined!=D_defined)
//DeadCode JIM 04Apr96 		EmitSysErr("Same filename saved twice!! %s",pvalue->tokentext);
//DeadCode JIM 04Apr96 	return(pvalue->instance);
//DeadCode JIM 04Apr96 }
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		OpenDirFiles
//Author		Jim Taylor
//Date			Wed 3 Apr 1996
//
//Description	Opens all the directory .FIL files in parallel
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	OpenDirFiles()
{
	char* outname="bfieldsA.fil";
	for (int i=0;i<256;i++)
		if (Battle_Dirs[i].dirname)
		{
			if ((Battle_Dirs[i].openhandle=fopen(outname,'t'))==0)
				EmitSysErr("Problems opening file lister: %s",outname);
			fprintf(Battle_Dirs[i].openhandle,"[files]\n%i	dir.dir	//%s\n",
				i,Battle_Dirs[i].dirname);
			outname[7]++;
		}
	if (outname[7]>'Z')
		EmitSysErr("Over 26 battlefield directories!!!");
}

void	CloseDirFiles()
{
	for (int i=0;i<256;i++)
		if (Battle_Dirs[i].openhandle)
			fclose(Battle_Dirs[i].openhandle);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		processbfieldtext
//Author		Jim Taylor
//Date			Mon 27 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	processbfieldtext(file	ifile)
{
TokenName	*type,	*newname,	*value,	*sep;
DataInst	*retval;
	if (filenestlevel==0)
	{
		findspelling(ifile,sep);
		if (sep->tokencode!=T_brktopen)
			EmitSysErr("Very bad start. Battlefield didn't start with '{'");
	}
	while (stripwhite(ifile))
	{
		GetTypeAndValue(ifile,type,newname,value,sep);
		if (	newname==NULL			//The intent is to be able to name things at the top level
			&& type->tokencode!=T_bfsave		
			&& type->tokencode!=T_fname
			&& type->tokencode!=T_level		
			&& type->tokencode!=T_include
			&& value->tokencode!=T_unknown	//The intent is to forward reference at the top level
			)
			EmitWarning("Unnamed element at top level is not battlefield: %s",
					type->TokenText());
		if (type->tokencode==value->tokencode)
			retval=value->instance;
		else
			switch (type->tokencode)	//will need to pass in sep to cope with
			{							//* occurance multiplier
			case T_include:
			{
				if (newname)
					EmitSysErr("How can you assign an include file?");
				if (value->tokentext==NULL)
					EmitSysErr("Value for include has no text associated?");
				UWord currsrcflinebackup=currsrcfline;
				UWord currsrcfnamebackup=currsrcfname;
				filenestlevel++;
string			filename=value->TokenText();
				if (	(filename[0]=='\"') || (filename[0]=='\'')	)
				{	//remove quotes by skipping forward and truncating
string				t2=filename++;
					while ((*t2!='\"') && *(t2) && (*t2!='\''))	t2++;
					t2[0]=0;
				}
					processbfieldtext(readfile(filename));
					retval=NULL;
				filenestlevel--;
				currsrcfline=currsrcflinebackup;
				currsrcfname=currsrcfnamebackup;
			}
			break;
			case T_bfsave:
				retval=toplevel_bfsave(ifile,value);
			break;
			case T_itemgrp:
				retval=toplevel_itemgrp(ifile,value);
			break;
			case T_gndgrp:
				retval=toplevel_gndgrp(ifile,value);
			break;
			case T_airgrp:
				retval=toplevel_airgrp(ifile,value);
			break;
			case T_route:
				retval=toplevel_route(ifile,value);
			break;
			case T_itemS:
				retval=toplevel_itemS(ifile,value);
			break;
			case T_itemG:
				retval=toplevel_itemG(ifile,value);
			break;
			case T_itemA:
				retval=toplevel_itemA(ifile,value);
			break;
			case T_waypoint:
				retval=toplevel_waypoint(ifile,value);
			break;
			case T_target:
				retval=toplevel_target(ifile,value,T_target);
			break;
			case T_pos:
				if (value->tokencode==T_3dsref)
					retval=value->instance;
				else
					retval=toplevel_pos(ifile,value);
			break;
			case T_abs:
				retval=toplevel_abs(ifile,value);
			break;
			case T_rel:
				retval=toplevel_rel(ifile,value);
			break;
			case T_att:
				retval=toplevel_att(ifile,value);
			break;
			case T_inwing:
				retval=toplevel_inwing(ifile,value);
			break;
			case T_inform:
				retval=toplevel_inform(ifile,value);
			break;
			case T_skill:
				retval=toplevel_skill(ifile,value);
			break;
			case T_morale:
				retval=toplevel_morale(ifile,value);
			break;
			case T_character:
				retval=toplevel_character(ifile,value);
			break;
			case T_damage:
				retval=toplevel_damage(ifile,value);
			break;
			case T_bombs:
				retval=toplevel_bombs(ifile,value);
			break;
			case T_level:
				retval=toplevel_level(ifile,value);
			break;
			case T_x:
				retval=toplevel_x(ifile,value);
			break;
			case T_y:
				retval=toplevel_y(ifile,value);
			break;
			case T_z:
				retval=toplevel_z(ifile,value);
			break;
			case T_range:
				retval=toplevel_range(ifile,value);
			break;
			case T_vel:
				retval=toplevel_vel(ifile,value);
			break;
			case T_rangepc:
				retval=toplevel_rangepc(ifile,value);
			break;
			case T_int:
				retval=toplevel_count(ifile,value);
			break;
			case T_count:
				retval=toplevel_count(ifile,value);
			break;
			case T_UIDband:
				retval=toplevel_UIDband(ifile,value);
			break;
			case T_briefID:
				retval=toplevel_briefID(ifile,value);
			break;
			case T_nation:
				retval=toplevel_nation(ifile,value);
			break;
			case T_shape:
				retval=toplevel_shape(ifile,value);
			break;
			case T_type:
				retval=toplevel_type(ifile,value);
			break;
			case T_duty:
				retval=toplevel_duty(ifile,value);
			break;
			case T_form:
				retval=toplevel_form(ifile,value);
			break;
			case T_move:
				retval=toplevel_move(ifile,value);
			break;
			case T_wpact:
				retval=toplevel_wpact(ifile,value);
			break;
			case T_icpt:
				retval=toplevel_icpt(ifile,value);
			break;
			case T_bearing:
			case T_hdg:
				retval=toplevel_bearing(ifile,value);
			break;
			case T_asimuth:
			case T_pitch:
				retval=toplevel_pitch(ifile,value);
			break;
			case T_roll:
				retval=toplevel_roll(ifile,value);
			break;
			case T_event:
				retval=toplevel_event(ifile,value);
			break;
			case T_start:
				retval=toplevel_time(ifile,value,T_start);
			break;
			case T_window:
				retval=toplevel_time(ifile,value,T_start);
			break;
			case T_squadron:
				retval=toplevel_squadron(ifile,value);
			break;
			case T_paintscheme:
				retval=toplevel_paintscheme(ifile,value);
			break;
			case T_fname:
				if (newname)
					retval=toplevel_fname(newname,value);
				else
					retval=toplevel_dirname(newname,value);
			break;
			default:
				EmitSysErr("Can't have this type of symbol at top level: %s",
					type->TokenText());
			}

		setupnewnamereference(newname,retval);
		if (retval)	treelist.Add(retval);
 		

		//called code will discard up to and including close bracket, 
		//but I need to handle ",".
		//Currently, called routines can't read or modify sep.
		//To implement * {...} they must read sep=*
		//To implement * value they must parse sep=* value sep2
		//so they will need to return a modified sep.
		if (getlistseparator(ifile,sep))
		{
			treeroot=treelist.Code(T_everything,NULL);
			return(FALSE);
		}
	}
	fclose(ifile);
	return(TRUE);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		processbfieldtext
//Author		Jim Taylor
//Date			Mon 27 Nov 1995
//
//Description	This is the basic bfield processor
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	processbfieldtext(string name)
{
	processbfieldtext(readfile(name));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		checktoken
//Author		Robert Slater
//Date			Tue 30 Jan 1996
//
//Description	Informs whether the required tokencode has been found,
//				with regards to the current item of text.
//				If true, it returns the next item of text.	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	checktoken(file	ifile, string text, TokenCode requiredcode)
{
	TokenName	*tokenname;
	
	if (	testspelling(text,tokenname)
		&& (tokenname->tokencode == requiredcode)	)
	{
		text = getword(ifile);
		return(TRUE);
	}
	else
		return(FALSE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		isnumeric
//Author		Robert Slater
//Date			Tue 30 Jan 1996
//
//Description	Checks if text is a number, and returns sign
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	isnumeric(string numtext, char &sign)
{
	char	compchar;

	compchar = numtext[0];
	sign = '+';

	if (((compchar >= '0') && (compchar <= '9')) || (compchar == '-'))
	{
		// Could be a number...

		if (compchar == '-')
		{
			// Could be a negative number...

			compchar = *(++numtext);

			if (!((compchar >= '0') &&( compchar <= '9')))
				EmitSysErr("Expecting digit after '-', but found %s",numtext);
			else
			{
				sign = '-';
				return(TRUE);
			}
		}
		else
			return(TRUE);
	}
	elser
		return(FALSE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		texttoint
//Author		Robert Slater
//Date			Tue 30 Jan 1996
//
//Description	Converts text to an integer
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
int		texttoint(string text)
{
	char		compchar, sign;
	int			places, count, coreno, fstdec;
	char		temp[80];


	compchar = text[0];
	places = 0;
	count = 0;
	fstdec = 0;
	coreno = 0;

	if (isnumeric(text,sign))
	{
		if (sign == '-')
			compchar = *++text;

		while (compchar && (places == 0))
		{
			if (compchar == '.')
			{
				places = count;
				fstdec = *++text-'0';
			}
			else
			{
				temp[count] = compchar;
				count = count + 1;
				compchar = *++text;
			}
		}

		temp[count] = NULL;

		coreno = atoi(temp);

		// Round the number...

		if ((places > 0) && (fstdec >= 5))
			coreno = coreno + 1;

		// Adjust according to sign...

		if (sign == '-')
		{
			coreno = 0 - coreno;
		}
	}
	else
		EmitSysErr("Failed to convert to number : %s", text);

		
	return(coreno);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		striptilltoken
//Author		Robert Slater
//Date			Thu 1 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
string	striptilltoken(file	ifile, TokenCode requiredcode)
{
	char	*text;

	text = getword(ifile);

	while (!checktoken(ifile,text,requiredcode))
		text = getword(ifile);

	return(text);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		pullvertex
//Author		Robert Slater
//Date			Tue 30 Jan 1996
//
//Description	Extracts a single line of vertex points
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	pullvertex(file	ifile, int &x, int &y, int &z)
{
	char		*text;
	char		sign;

	// Default cock-up values...

	x = 0; y = 0; z = 0;

	text = striptilltoken(ifile,T_vertex);	

	Assert (isnumeric(text,sign));
	{
		text = getword(ifile);

		Assert (text[0] == ':');
		{
			// Get data...

			text = getword(ifile);

			Assert (	checktoken(ifile,text,T_x)
					&&	(text[0] == ':')	   		);
				x = texttoint(getword(ifile));

			text = getword(ifile);

			Assert (	checktoken(ifile,text,T_y)
					&&	(text[0] == ':')		   	);
				y = texttoint(getword(ifile));

			text = getword(ifile);

			Assert (	checktoken(ifile,text,T_z)
					&&	(text[0] == ':')		 	);
				z = texttoint(getword(ifile));

		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		pullfaceline
//Author		Robert Slater
//Date			Tue 30 Jan 1996
//
//Description	Extracts a single line of face information
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
string	pullfaceline(file	ifile, int &a, int &b, int &c)
{
	char		*text;
	string		material;
	char		*temp;
	char		sign;
	int			count;
	char		charcopy;
	Bool		stop;

	// Default cock-up values...

	a = -1; b = -1; c = -1;
	material = NULL;

	text = striptilltoken(ifile,T_face);

	Assert (isnumeric(text,sign));
	{
		text = getword(ifile);

		Assert (text[0] == ':');
		{
			text = getword(ifile);

			Assert (	checktoken(ifile,text,T_a)
					&&	(text[0] == ':')		  	);
			   	a = texttoint(getword(ifile));

			text = getword(ifile);

			Assert (	checktoken(ifile,text,T_b)
					&&	(text[0] == ':')		 	);
				b = texttoint(getword(ifile));

			text = getword(ifile);

			Assert (	checktoken(ifile,text,T_c)
					&&	(text[0] == ':')		  	);
				c = texttoint(getword(ifile));	 

			text = getword(ifile);

			while (!checktoken(ifile,text,T_mtl))
				text = getword(ifile);

			if (text[0] == ':')
			{
				material = temp = getword(ifile);
			
				// Remove quotes & full stops...

				count = 0;
				stop = FALSE;

				charcopy = temp[0];
				if (*temp=='"')
					material = ++temp;
				while (*temp!=0 && *temp!='"' && *temp!='.') temp++;
				*temp=0;
								
//				if (	testspelling(material,token)
//					&&	(token->tokencode == T_shape)	)
//				{
					// Material is a recognised shape, so check if Default

				if (strcmp(material,"Default") == 0)
					return(NULL);

//				}
//				else
//					return(NULL);
			}
			else
				EmitSysErr("Material description not found!");

		}
	}

	return(material);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		pullvertices
//Author		Robert Slater
//Date			Wed 31 Jan 1996
//
//Description	Creates a list of all the vertices
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	pullvertices(file	ifile, int noverts, Coordinates* &vertlist)
{
	int			count;
	int			x, y, z;

	vertlist = new Coordinates[noverts];	Assert(vertlist&&"memory!");

	
	// Clear header and garbage

	striptilltoken(ifile,T_vertex);

	// Loop through vertices and extract each vertex...

	for(count=0; count<noverts; count++)
	{
	    pullvertex(ifile,x,y,z);
		vertlist[count].x = x * 100;
		vertlist[count].y = z * 100;
		vertlist[count].z = -y * 100;							//JIM 01Apr96
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		pullfaces
//Author		Robert Slater
//Date			Wed 31 Jan 1996
//
//Description	Creates a list of all the faces
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
string	pullfaces(file	ifile, int nofaces, Connections* &facelist)
{
	char		*text, *material, *t2;
	int			count;
	int			a, b, c;

	facelist = new Connections[nofaces];	Assert(facelist&&"memory!");

	
	// Clear header and garbage 

	striptilltoken(ifile,T_face);

	// Loop through face list and extract...

	text = pullfaceline(ifile,a,b,c);

	if (text)
	{
		t2=material = new char[strlen(text)+1]; Assert(material&&"memory!");
		while	(*text<='\"')	text++;
		while	(*text<='\"')	t2++[0]=text++[0];
		t2[0]=0;
	}
	else
		material = NULL;

	facelist[0].a = a;
	facelist[0].b = b;
	facelist[0].c = c;

	for(count=1; count<nofaces; count++)
	{
		pullfaceline(ifile,a,b,c);

		facelist[count].a = a;
		facelist[count].b = b;
		facelist[count].c = c;
	}

	return(material);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		checkforroute
//Author		Robert Slater
//Date			Wed 31 Jan 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	checkforroute(Connections *facelist, int nofaces, int noverts)
{
	int			common, number, count;
	Bool		isroute;
	int			prev1, prev2;

	if (noverts == 3)
		return(TRUE);

	isroute = TRUE;

	for(count = 1; count < nofaces; count ++)
	{
		common = 0;

		number = facelist[count].a;

	   	if (	(number == facelist[count-1].a) 
			||	(number == facelist[count-1].b) 
			||	(number == facelist[count-1].c)	)
					common = common + 1;

		number = facelist[count].b;

	   	if (	(number == facelist[count-1].a) 
			||	(number == facelist[count-1].b) 
			||	(number == facelist[count-1].c)	)
					common = common + 2;

		number = facelist[count].c;

	   	if (	(number == facelist[count-1].a) 
			||	(number == facelist[count-1].b) 
			||	(number == facelist[count-1].c)	)
					common = common + 4;

		switch (common)
		{
		case 1:
		{
			// A is common. Do nothing, because it is in order
		}
		break;
		case 2:
		{
			// Rotate left if B is common
		
			prev1 = facelist[count].a;
			prev2 = facelist[count].c;
			
			facelist[count].a = facelist[count].b;
			facelist[count].b = prev2;
			facelist[count].c = prev1;
		}
		break;
		case 4:
		{
			// Rotate right	if C is common
			
			prev1 = facelist[count].b;
			prev2 = facelist[count].a;
			
			facelist[count].a = facelist[count].c;
			facelist[count].b = prev2;
			facelist[count].c = prev1;
		}
		break;
		default:
			isroute = FALSE;
		}
		
	}

	// Cater for Face0...

	if (isroute)
	{
		number = facelist[0].a;

		// Rotate left if A is common

	   	if (number == facelist[1].a)
		{
			prev1 = facelist[0].a;
			prev2 = facelist[0].c;
			
			facelist[0].a = facelist[0].b;
			facelist[0].b = prev2;
			facelist[0].c = prev1;
		}

		number = facelist[0].b;

		// Rotate right	if B is common
	   
		if (number == facelist[1].a)
		{
			prev1 = facelist[0].b;
			prev2 = facelist[0].a;
			
			facelist[0].a = facelist[0].c;
			facelist[0].b = prev2;
			facelist[0].c = prev1;
		}

	}

	return(isroute);

}
	
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		get3dsentry
//Author		Robert Slater
//Date			Tue 30 Jan 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	get3dsentry(file	ifile)
{	
	char		name[80], *nexttext, letter;
	char		nvertstext[80], nfacestext[80];
	Bool		finished, route;
	int			noverts, nofaces, vfrom;
	Coordinates	*vertex;
	Connections	*face;
	char		tag[4];
	char		routename[80];
	char		*material;


	material=getword(ifile);
	nexttext=name;
	while (*material<='\"')	material++;
	while (*material>'\"')	nexttext++[0]=material++[0];
	nexttext[0]=0;
//DeadCode JIM 26Mar96 	strcpy(name,getword(ifile));

	finished = FALSE;

	nexttext=striptilltoken(ifile,T_vertex);				//Tri-mesh , Vertices :
	Assert (*nexttext==':');
	noverts = texttoint(getword(ifile));		//nnnn
	nexttext = getword(ifile);					//Faces
	nexttext = getword(ifile);					//:
	Assert (*nexttext==':');
	nofaces = texttoint(getword(ifile));		//nnnn


	if (noverts <= 30)
	{
		pullvertices(ifile,noverts,vertex);
		material = pullfaces(ifile,nofaces,face);

		route = checkforroute(face,nofaces,noverts);

		if (route)
		{
			for(vfrom = 0; vfrom < noverts; vfrom++)
			{
				letter = (char)('A' + vfrom);

				tag[0] = '_';
				tag[1] = letter;
				tag[2] = 0;

				strcpy(routename,name);
				strcat(routename,tag);
				add3dsentry(routename, vertex[vfrom].x, vertex[vfrom].y,
							vertex[vfrom].z, NULL);
			}
		}
		else
			add3dsentry(name, vertex[0].x, vertex[0].y, vertex[0].z, material);
																
		delete []material;										
		delete []face;
		delete []vertex;
	}

}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//
//Procedure		studiointerpreter
//Author		Rob Slater
//Date			Mon 29 Jan 1996
//
//Description	Converts 3d studio information
//
//Inputs
//
//Returns
//
//------------------------------------------------------------------------------
void	studiointerpreter(file	ifile)
{
	char		*nexttext;


	// Hop through the file	until EOF

	while (stripwhite(ifile))
	{
		// Try and extract the object name...

		nexttext = getword(ifile);

		if (	checktoken(ifile,nexttext,T_named)
			&&	checktoken(ifile,nexttext,T_object)	)
		{
			if (nexttext[0] != ':')
				EmitSysErr("':' was expected...");

			get3dsentry(ifile);
 		}
	}

	fclose(ifile);
	if (unshaped3ds)
		EmitWarning("Total number of 3ds objects with no shape= %i",unshaped3ds);
}

//DeadCode JIM 28Oct96 extern "C" int	_amblksiz;
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		main
//Author		Jim Taylor
//Date			Mon 27 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
int	main(int	argc,string	argv[])
{

//TempCode JIM 04Dec95 	FirstSpell.SaveTxt(stdout,0);
	if (argc<4)
		EmitSysErr("MakeBF: Battlefield binary maker.\n"
					"3 parameters:\n"
					"\tinitialising response file name,\n"
					"\tmain battlefield source file name,\n"
					"\toutput directory name(s) (linked to level?).\n"
					"\nPlease try again!\n"
				);
	addfixedspellings();
	interpretresponse(argv[1]);
	sortuidtable();
//DeadCode DAW 08Apr96  	studiointerpreter(readfile("..\\world\\3ds\\franc.asc"));
//TempCode RJS 02Feb96 	FirstSpell.SaveTxt(stdout,0);
	processbfieldtext(argv[2]);
	setwritefile(argv[3]);
//DeadCode JIM 24Jun96 	filelistfile=fopen("bfields.fil",'t');
//DeadCode JIM 24Jun96 	if (filelistfile==NULL)
//DeadCode JIM 24Jun96 		EmitSysErr("Couldn't open 'bfields.fil' for writing!");
//DeadCode JIM 24Jun96 	fprintf(filelistfile,"[files]\n110\tdir.dir\n");
	ufile	outfile;
	treeroot->SaveTxt(NULL,0);									//JIM 28Mar96
//DeadCode JIM 28Mar96 	treeroot->SaveTxt(outfile=writefile("TextTree.err",'t'),0);
//DeadCode JIM 28Mar96 	fclose(outfile);
	if (filenestlevel)	EmitSysErr("There were undefined symbols. Please investigate.");
	UFILE	StdOut;
	StdOut.written=TRUE;
	StdOut.f=stdout;
	OpenDirFiles();
 	treeroot->PreSave(&StdOut,0);
	UIDlistfile=fopen("h\\uidvals.g",'t');
	fprintf(UIDlistfile,"//----------------------------------------\n");
	fprintf(UIDlistfile,"//Filename:	h\uidvals.g\n");
	fprintf(UIDlistfile,"//Desc:		Included into uniqueid.g to name uids\n");
	fprintf(UIDlistfile,"//----------------------------------------\n");
	fprintf(UIDlistfile,"#ifndef	uidvals_included\n");
	fprintf(UIDlistfile,"#define	uidvals_included\n");
	treeroot->PreSave2(&StdOut,0);
	fprintf(UIDlistfile,"#endif\n");
	fclose(UIDlistfile);
	UIDlistfile=NULL;

	CloseDirFiles();
 	treeroot->SaveTxt(outfile=writefile("TextFour.err",'t'),0);
	if (filenestlevel)	EmitSysErr("There were undefined symbols. Please investigate.");
	fclose(outfile);
 	treeroot->SaveBin(NULL,0);
    return(0);
}


/*
GRAMMAR FOR MAKEBF
==================

This note lists the various alternatives available by direct conversion,
and the options inside a bracketed list for each type.
The LHS is the internal type name. The RHS is the name typed in the source.

TopLevel: The top level is not named. Only T_bfsave generates data directly.
	{	T_bfsave:BattleField,
		T_itemgrp:ItemGroup,T_gndgrp:GroundGroup,
		T_airgrp:AirGroup,T_route:Route,
		T_itemS:SimpleItem,T_itemG:GroundItem,
		T_itemA:Aircraft,T_waypoint:WayPoint,
		T_target:Target,T_pos:Posn,
		T_abs:Abs,T_rel:Rel,				 
		T_att:Attitude,
		T_inwing:NumInWing,T_inform:NumInForm,
		T_skill:Skill,T_damage:Damage,
		T_level:Level,						 
		T_x:X,T_y:Y,T_z:Z,
		T_UIDband:UIDBand,T_briefID:BriefID,
		T_nation:Side,T_shape:Shape,T_type:Type,
		T_duty:Duty,T_form:Formation,
		T_move:MoveCode,T_wpact:Action,
		T_bearing:Bearing,T_hdg:Heading,T_pitch:Pitch,T_roll:Roll,
		T_fname:FileName
	}

T_bfsave:BattleField
	{
		T_itemS:SimpleItem,
		T_itemgrp:ItemGroup,T_gndgrp:GroundGroup,
		T_airgrp:AirGroup,T_route:Route,
		T_fname:FileName,
		T_setval:Setval,
	}

T_itemgrp:ItemGroup: Only itemS generates data directly.
	=	T_itemS:SimpleItem,
	{
		T_itemS:SimpleItem,T_pos:Posn,
	}

T_gndgrp:GroundGroup
	{
		T_inform:NumInForm,T_pos:Posn,
		T_route:Route,T_form:Formation,
		T_itemG:ItemGroup,
	}

T_airgrp:AirGroup
	{
	 	T_inform:NumInForm,T_duty:Duty,
		T_inwing:NumInWing,
		T_pos:Posn,T_route:Route,T_form:Formation,
		T_itemA:Aircraft,
	}

T_route:Route,:	Only T_waypoint generates data directly
	{
		T_waypoint:WayPoint,T_pos:Posn,
	}

T_itemS:SimpleItem,
	= 	T_3dsref:BattleField,
	{
		T_setUID:SetUID,T_pos:Posn,
		T_shape:Shape,T_UIDband:UIDBand,
	}

T_itemG:ItemGroup,
	{
	 	T_setUID:SetUID,T_nation:Side,T_form:Formation,
		T_shape:Shape,T_UIDband:UIDBand,T_move:MoveCode,
		T_att:Attitude,
	}

T_target:Target,
	={
	 	T_itemS:SimpleItem,T_itemG:ItemGroup,
		T_itemA:Aircraft,T_itemgrp:ItemGroup,
		T_gndgrp:GroundGroup,T_airgrp:AirGroup,T_route:Route,
	}

T_itemA:Aircraft,
	{
	 	T_setUID:SetUID,T_nation:Side,
		T_shape:Shape,T_type:Type,T_UIDband:UIDBand,
		T_move:MoveCode,T_damage:Damage,
		T_skill:Skill,T_morale:Morale,T_character:Character:Style,
		T_target:Target,T_att:Attitude,
		T_event
	}

T_waypoint:WayPoint,
	=	T_3dsref:(by name),
	{
	 	T_setUID:SetUID,T_pos:Posn,
		T_target:Target,T_wpact:Action,
adding:	T_range:Range,T_event:Event,
	}

T_pos:Posn,
	=	T_3dsref:(by name),
		T_itemS:SimpleItem,
		T_itemG:ItemGroup,
		T_itemA:Aircraft,
		T_itemgrp:ItemGroup,
		T_gndgrp:GroundGroup,
		T_airgrp:AirGroup,;
	{
	 	T_abs:Abs,T_rel:Rel,
		T_att:Attitude,
		T_x:X,T_y:Y,T_z:Z,
	}

T_abs:Abs
	=	T_3dsref:(by name),
	=	T_itemS:SimpleItem,T_itemG:ItemGroup,T_itemA:Aircraft,
	=	T_itemgrp:ItemGroup,T_gndgrp:GroundGroup,T_airgrp:AirGroup,;
	{
		T_3dsref:BattleField,T_pos:Posn,T_abs:Abs,T_x:X,T_y:Y,T_z:Z,
	}

T_rel:Rel,
	{	
		T_icpt:Intercept,
		T_rel:Rel,T_target:Target,
		T_itemG:ItemGroup,T_itemA:Aircraft,	- src hdg/pitch info
		T_x:X,T_y:Y,T_z:Z,
		T_bearing:Bearing,T_hdg:Heading,
		T_asimuth:Asimuth,T_pitch:Pitch,T_range:Range,
	}

T_icpt:Intercept	Get intercept between two items
	{
		T_pos,T_target,
		T_pos,T_target
	}

T_att:Attitude,
	{
		T_icpt:Intercept,
	 	T_rel:Rel,T_target:Target,
		T_itemG:ItemGroup,T_itemA:Aircraft,	- src hdg/pitch info
		T_hdg:Heading,T_pitch:Pitch,T_roll:Roll,
	}

T_event:Event	Can be enum or {}, but not rnd/seq/list
	=Event,
	{
		T_event:Event,	- this is enum/rnd/seq/list
		T_start:Start,	T_window:Window,	- these are time
		T_setval:SetVal						- these setvals logged for event load.
	}

time: T_start:Start,T_window:Window
		- no size tests. You can specify entirely in secs or mins
	{
		T_hours:H:Hours,
		T_mins:M:Mins,
		T_secs:S:Secs
	}
currently not possible to say
	=	Secs.

enumval: 	Any 'integer' field maps to enumval.
The following mappings will only allow enum mapping:
	T_UIDband:UIDBand,
	T_briefID:BriefID,
	T_nation:Side,
	T_shape:Shape,
	T_type:Type,
	T_duty:Duty,
	T_form:Formation,
	T_move:MoveCode,
	T_wpact:Action,
The following mappings allow enum or integer mapping:
	T_inwing:NumInWing,
	T_inform:NumInForm,
	T_skill:Skill,
	T_morale:Morale,
	T_character:Character:Style,
	T_damage:Damage,
	T_level:Level,
	T_bearing:Bearing,
	T_hdg:Heading,
	T_pitch:Pitch,
	T_roll:Roll,
The following mappings only allow integer mapping:
	T_x:X,T_y:Y,T_z:Z,
	T_range:Range,

	=	named enum entry
	=	named global variable
	=	number
	={	T_random:Random	start,control,stepsize}
	={	T_select:Select	start,control,stepsize}
	={	T_list:List		cv,n1,n2,n3,n4}	- don't work yet...

If integer mapping is not allowed then either
'start' and 'stepsize' must both be of the enum type, or
'start' and 'control' must be of the enum type, or start=0.
If (only) 2 parameters, then stepsize=1 (integer).
If (only) 1 parameter, then stepsize=1 and start=0.
List is indexed by position in formation.
A nested list is subsequently indexed by position in wing.
Ntries will be type checked.

*/
#endif
