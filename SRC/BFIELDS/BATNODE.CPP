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

//
// Battle Node Generation
//
//
//
//
//
//
#include	<stdio.h>
#include	<string.h>
#define	F_GRAFIX
#define	F_COMMON
#define F_SOUNDS

#include	"dosdefs.h"
#include	"files.g"
#include	"..\mfc\resource.h"
#include "uniqueid.h"
#include "flyinit.h"

//the following include files are to silence "node.h"
	   
//With mark's changes, all these consts can be commented out!



/*
The following phrases are available for use in battlefields:
	IDS_PHRASE_RIVERBANK	" river bank"
	IDS_PHRASE_RUINEDBUILDINGS	" ruined buildings"
	IDS_PHRASE_PADDYFIELDS	" paddyfields"
	IDS_PHRASE_WOODEDAREA	" wooded area"
	IDS_PHRASE_RIDGELINE	" ridge line"
	IDS_PHRASE_HILLTOWN	" hill, overlooking town"
	IDS_PHRASE_HILLROAD	" hill, commanding the road"
	IDS_PHRASE_HILLSIDE	" hillside"
	IDS_PHRASE_HILLTOP	" hilltop"
	IDS_PHRASE_POSOTOWN	" outskirts"
	IDS_PHRASE_POSSTOWN	" suburbs"
	IDS_PHRASE_POSCIVILIAN	" civilian buildings"
	IDS_PHRASE_POSMAINSTREET	" positions covering street"
	IDS_PHRASE_LINEMAINROAD	" line over main road"
	IDS_PHRASE_ENTRYTOTOWN	" town entrance"
	IDS_PHRASE_ENTRYGULLEY	" gully entrance"
	IDS_PHRASE_RIVERFORD	" river ford"
	IDS_PHRASE_BRIDGECROSSING	" bridge crossing"
	IDS_PHRASE_FERRYPOINT	" ferry point"
	IDS_PHRASE_BLOCKINGPOS	" road block"
	IDS_PHRASE_TREELINE	" tree line"
	IDS_PHRASE_FORESTAREA	" forest area"
	IDS_PHRASE_OPENGROUND	" open ground"
	IDS_PHRASE_TOWNCENTRE	" town center"
	IDS_PHRASE_CROSSROADS	" crossroads"
	IDS_PHRASE_STREAM	" stream"
	IDS_PHRASE_SMALLVILLAGE	" small village"
	IDS_PHRASE_GROUPOFHUTS	" group of huts"
	IDS_PHRASE_VALLEYFLOOR	" valley floor"
	IDS_PHRASE_VALLEYRIM	" valley rim"

	IDS_PHRASE_ONMAINHIGHWAY	" on main highway."
	IDS_PHRASE_ONROAD	" on road."
	IDS_PHRASE_CROSSOPEN	" crossing open ground."
	IDS_PHRASE_THROUGHPADDY	" moving through paddyfields."
	IDS_PHRASE_FORDINGRIVER	" fording the river."
	IDS_PHRASE_INPASS	" in the pass."
	IDS_PHRASE_HEADMAINSTREET	" heading along the main-street."
	IDS_PHRASE_USESIDESTREET	" using side-streets."
	IDS_PHRASE_THROUGHBUILDINGS	" moving through buildings."
	IDS_PHRASE_THROUGHTREES	" cutting through the trees."
	IDS_PHRASE_SKIRTINGTREES	" skirting tree-line."
	IDS_PHRASE_ROUGHTERRAIN	" slowly crossing rough terrain."
	IDS_PHRASE_BASEOFSLOPE	" following base of slope."
	IDS_PHRASE_RAILCUTTING	" following rail-cutting."
*/
const int IDS_CP=IDS_PHRASE_BLOCKINGPOS;
const int IDS_FRONTLEFTFLANK=IDS_PHRASE_HILLROAD;
const int IDS_FRONTOPEN=IDS_PHRASE_OPENGROUND;
const int IDS_FRONTHILL=IDS_PHRASE_HILLSIDE;
const int IDS_FERRY=IDS_PHRASE_FERRYPOINT;
const int IDS_TOWN_NW=IDS_PHRASE_POSOTOWN;
const int IDS_TOWN_NE=IDS_PHRASE_POSSTOWN;
const int IDS_TOWN_W=IDS_PHRASE_ENTRYTOTOWN;
const int IDS_COVERROAD=IDS_PHRASE_LINEMAINROAD;
const int IDS_CITYSOUTHOFRIVER=IDS_PHRASE_RIVERBANK;
const int IDS_RIVERCROSSING=IDS_PHRASE_BRIDGECROSSING;


//these need fixing!!!!
//const UniqueID UID_BNW_2e=(UniqueID)-12;
//const UniqueID UID_BNW_3c=(UniqueID)-13;
//const UniqueID UID_BNW_4b=(UniqueID)-14;
//const UniqueID UID_BNC_1e_i=(UniqueID)-15;
//const UniqueID UID_BNW_0a_i=(UniqueID)-17;
//const UniqueID UID_BNW_0b_i=(UniqueID)-18;
//const UniqueID UID_BNW_0c_i=(UniqueID)-19;
//const UniqueID UID_BNW_0d_i=(UniqueID)-20;
//const UniqueID UID_BNW_0e_i=(UniqueID)-21;
//const UniqueID UID_BNW_0f_i=(UniqueID)-22;
//const UniqueID UID_BNW_2e_i=(UniqueID)-23;
//const UniqueID UID_BNW_3c_i=(UniqueID)-24;
//const UniqueID UID_BNW_4b_i=(UniqueID)-25;
//const UniqueID UID_BNC_1e_o=(UniqueID)-26;
//const UniqueID UID_BNW_2e_o=(UniqueID)0;//-33;
//const UniqueID UID_BNW_3c_o=(UniqueID)0;//-34;
//DEADCODE %JIM %DATE //const UniqueID UID_BNW_4b_o=(UniqueID)0;//-35;

//these are 'real' fakes!!
const UniqueID UID_BNW_0a_o=(UniqueID)0;
const UniqueID UID_BNW_0b_o=(UniqueID)0;
const UniqueID UID_BNW_0c_o=(UniqueID)0;
const UniqueID UID_BNW_0d_o=(UniqueID)0;
const UniqueID UID_BNW_0e_o=(UniqueID)0;
const UniqueID UID_BNW_0f_o=(UniqueID)0;
const UniqueID UID_BNC_0a_o=(UniqueID)0;
const UniqueID UID_BNC_0b_o=(UniqueID)0;
const UniqueID UID_BNC_0c_o=(UniqueID)0;
const UniqueID UID_BNC_0d_o=(UniqueID)0;
const UniqueID UID_BNC_0e_o=(UniqueID)0;
const UniqueID UID_BNC_0f_o=(UniqueID)0;
const UniqueID UID_BNE_0a_o=(UniqueID)0;
const UniqueID UID_BNE_0b_o=(UniqueID)0;
const UniqueID UID_BNE_0c_o=(UniqueID)0;
const UniqueID UID_BNE_0d_o=(UniqueID)0;
const UniqueID UID_BNE_0e_o=(UniqueID)0;
const UniqueID UID_BNE_0f_o=(UniqueID)0;


#undef	NODE
#define	NODE(x)	 set(x)
UniqueID	NodeTable[]=
{
	UID_NULL,
#pragma message(__HERE__ "include batuids.h")
#include "batuids.h"	
	UID_NULL,
	UID_NULL
};
#undef	NODE
#pragma message(__HERE__ "include batuids.h")
#define	NODE(x)	 set(x)_i
UniqueID	NodeTableI[]=
{
	UID_NULL,
#pragma message(__HERE__ "include batuids.h")
#include "batuids.h"	
	UID_NULL,
	UID_NULL
};
#undef	NODE
#pragma message(__HERE__ "include batuids.h")
#define	NODE(x)	 set(x)_o
UniqueID	NodeTableO[]=
{
	UID_NULL,
#pragma message(__HERE__ "include batuids.h")
#include "batuids.h"	
	UID_NULL,
	UID_NULL
};
#undef	NODE
#define	NODE(x)	#x
char*		NodeNames[]=
{
	"NULL",
#pragma message(__HERE__ "include batuids.h")
#include "batuids.h"
	"HEADER","HEADER"
};
enum	LocalUniqueID
{

#undef	NODE
#define NODE(x)		 set(x)_XX
	UID_NULL_XX,
#pragma message(__HERE__ "include batuids.h")
#include "batuids.h"
	HEADER_REF,
	MAX_BAT_BLOCKS,
	NUM_MASK =0x0fff,
	REF_LEFT =0x1000,
	REF_RIGHT=0x2000,
	REF_DOWN =0x3000,
	DEF_HERE =0x4000
};
#undef	NODE


struct	LocalUID
{
	typedef	LocalUniqueID	UniqueID;
	#include	"batnode.h"

};

typedef	LocalUID::SuperBattleNode::FlankLink	F;
typedef	LocalUID::SuperBattleNode::IntraLink	L;

#define INITFORCE(aforce,hforce) ((L::TerrainType) (L::INITFORCE+LocalUID::TeamDef::aforce+256*LocalUID::TeamDef::hforce))	


//#define	NODE(num)		UID_BNC_##num
//#define	NODE(num)		UID_BNW_##num

#define	PLACE(num,text)	NODE(num),IDS_##text
#define	BATTLE(fil,equ)	{fil,equ,__HERE__ "(" fil "): "}
#define	UID_NULL	UID_NULL_XX

#include	"BN_east.h"
#include	"BN_cent.h"
#include	"BN_west.h"
			

LocalUID::UniqueID	references[MAX_BAT_BLOCKS];
void	Translate(LocalUID::UniqueID& id)
{
	id=(LocalUID::UniqueID)NodeTable[id];
}
void	TranslateI(LocalUID::UniqueID& id,LocalUID::UniqueID main)
{
	id=(LocalUID::UniqueID)NodeTableI[main];
}
void	TranslateO(LocalUID::UniqueID& id,LocalUID::UniqueID main)
{
	id=(LocalUID::UniqueID)NodeTableO[main];
}
bool	Define(LocalUID::UniqueID id)
{
	if (references[id]&DEF_HERE)
		return false;
	references[id]=LocalUID::UniqueID(references[id]|DEF_HERE);
	return true;
}

void	Reference(LocalUID::UniqueID id,LocalUID::UniqueID by,LocalUID::UniqueID dir)
{
	references[id]=LocalUID::UniqueID(by+dir+(references[id]&DEF_HERE));
}

int main()
{
	FILE* d=fopen("\\mig\\src\\batnode.fil","wt");
	fputs("[files]\n135\tdir.dir\n",d);
	int errors=0,writes=0;
	LocalUID::SuperBattleDesc* battledescs=eastbattledescs;
	do{

		for (int i=0;battledescs[i].names.filename;i++)
		{
			int j;
			for (j=0;j<MAX_BAT_BLOCKS;j++)
				references[j]=UID_NULL_XX;
			char* defining=battledescs[i].names.filename;
			Reference(battledescs[i].header.awayreinforceleft,HEADER_REF,REF_DOWN);
			Translate(battledescs[i].header.awayreinforceleft);
			Reference(battledescs[i].header.homereinforceleft,HEADER_REF,REF_DOWN);
			Translate(battledescs[i].header.homereinforceleft);
			for (j=0;battledescs[i].nodelist[j].mainuid;j++)
			{

				LocalUID::UniqueID u=battledescs[i].nodelist[j].mainuid;
				if (!Define(battledescs[i].nodelist[j].mainuid))
					printf("%s Node %s defined twice\n",battledescs[i].names.linenum,NodeNames[u],errors++);
				if (	!(battledescs[i].nodelist[j].flanks.nonlinks&F::NOT_LEFT)
					&&	!battledescs[i].nodelist[j].flanks.left	)
					printf("%s Node %s left link null but not flagged!\n",battledescs[i].names.linenum,NodeNames[u],errors++);
				if (	!(battledescs[i].nodelist[j].flanks.nonlinks&F::NOT_RIGHT)
					&&	!battledescs[i].nodelist[j].flanks.right	)
					printf("%s Node %s right link null but not flagged!\n",battledescs[i].names.linenum,NodeNames[u],errors++);
				if (battledescs[i].nodelist[j].flanks.left==u)
					printf("%s Node %s left link self reference!\n",battledescs[i].names.linenum,NodeNames[u],errors++);
				if (battledescs[i].nodelist[j].flanks.right==u)
					printf("%s Node %s right link self reference!\n",battledescs[i].names.linenum,NodeNames[u],errors++);
				if (battledescs[i].nodelist[j].innerlink.uid==u)
					printf("%s Node %s down link self reference!\n",battledescs[i].names.linenum,NodeNames[u],errors++);

				Translate(battledescs[i].nodelist[j].mainuid);
				TranslateI(battledescs[i].nodelist[j].in.uid,u);
				TranslateO(battledescs[i].nodelist[j].out.uid,u);
//				if (	(battledescs[i].nodelist[j].out.uid==UID_NULL)
//					==	((battledescs[i].nodelist[j].out.terrain&32768)==0)
//					)
//					printf("%s Node %s: node0/terrain type incompatability!\n",battledescs[i].names.linenum,NodeNames[u],errors++);

				Reference(battledescs[i].nodelist[j].flanks.left,u,REF_LEFT);
				Reference(battledescs[i].nodelist[j].flanks.right,u,REF_RIGHT);
				Reference(battledescs[i].nodelist[j].innerlink.uid,u,REF_DOWN);
				Translate(battledescs[i].nodelist[j].flanks.left);
				Translate(battledescs[i].nodelist[j].flanks.right);
				Translate(battledescs[i].nodelist[j].innerlink.uid);
			}
			for (int k=1;k<MAX_BAT_BLOCKS;k++)
				if (references[k])
					if (!(references[k]&DEF_HERE))
						if ((references[k]&REF_DOWN)>REF_RIGHT)
							printf("%s Node %s references undefined node %s downwards!\n",battledescs[i].names.linenum,NodeNames[references[k]&NUM_MASK],NodeNames[k],errors++);
						else if ((references[k]&REF_DOWN)==REF_RIGHT)
							printf("%s Node %s references undefined node %s on right flank!\n",battledescs[i].names.linenum,NodeNames[references[k]&NUM_MASK],NodeNames[k],errors++);
						else
							printf("%s Node %s references undefined node %s on left flank!\n",battledescs[i].names.linenum,NodeNames[references[k]&NUM_MASK],NodeNames[k],errors++);
					else
						if (!(references[k]&REF_DOWN))
							printf("%s Node %s is defined but not used!\n",battledescs[i].names.linenum,NodeNames[k],errors++);

			char buffer[100];
			strcpy(buffer,"\\mig\\game\\bfields\\batnode\\");
			strcat(buffer,battledescs[i].names.filename);
			FILE* f=fopen(buffer,"wb");
			if (!f)
			{
				printf("%s couldn't write file %i called \"%s\"\n",battledescs[i].names.linenum,i,buffer);
				errors++;
			}
			else
			{
				writes++;
				fprintf(d,"\t%s\t%s\n",battledescs[i].names.filename,battledescs[i].names.equatename);
				fwrite(&battledescs[i].header,1,sizeof(LocalUID::SuperBattleDesc::Header),f);
				fwrite(battledescs[i].nodelist,j,sizeof(LocalUID::SuperBattleNode),f);
				fclose(f);
			}
		}
		if (battledescs==eastbattledescs)
		   battledescs=centralbattledescs;
		elseif (battledescs==centralbattledescs)
		   battledescs=westbattledescs;
		else
		   battledescs=NULL;
	}while (battledescs);
	printf("%i files written. %i problems\n",writes,errors);
	fclose(d);
	return errors;

}
