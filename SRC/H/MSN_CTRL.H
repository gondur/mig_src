//------------------------------------------------------------------------------
//Filename       msn_ctrl.h
//System         
//Author         R. Hyde 
//Date           Wed 17 Jul 1996
//Description    
//------------------------------------------------------------------------------
#ifndef	MSN_CTRL_Included
#define	MSN_CTRL_Included

#define	DEFAULT_MSN_CTRL 0

//DeadCode RDH 04Apr97 	enum CtrlVar {	CTRL_NONE =0,CTRL_LOAD,CTRL_FLY,CTRL_NEWS,CTRL_SQUAD,
//DeadCode RDH 04Apr97 					CTRL_QUITDIAL,CTRL_MAIN,CTRL_SAVE,CTRL_CONFIG,
//DeadCode RDH 04Apr97 					CTRL_JOY1,CTRL_QUIT2CAMP,CTRL_MISSIONS,
//DeadCode RDH 04Apr97 					CTRL_PSEUDO,
//DeadCode RDH 04Apr97 					CTRL_MISSIONSELECT,
//DeadCode RDH 04Apr97 					CTRL_CAMPOBJECTIVES,
//DeadCode RDH 04Apr97 					CTRL_INPUTNAME,
//DeadCode RDH 04Apr97 
//DeadCode RDH 04Apr97 					CTRL_KILLSSHEET,
//DeadCode RDH 04Apr97 					CTRL_WOUNDEDSHEET,
//DeadCode RDH 04Apr97 
//DeadCode RDH 04Apr97 					CTRL_QUIT2DOS,CTRL_QUIT23D,CTRL_QUIT2MAP,
//DeadCode RDH 04Apr97 					CTRL_QUIT2PAINT,CTRL_QUIT2PERSONNEL,CTRL_QUIT2LOAD,
//DeadCode RDH 04Apr97 
//DeadCode RDH 04Apr97 					CTRL_CONFIG_FROM_MENU,
//DeadCode RDH 04Apr97 					CTRL_CONFIG_FROM_3D,
//DeadCode RDH 04Apr97 
//DeadCode RDH 04Apr97 					CTRL_H2HQUIT,CTRL_H2HPLAY
//DeadCode RDH 04Apr97 
//DeadCode RDH 04Apr97 					
//DeadCode RDH 04Apr97 					};

	enum CtrlVar {	CTRL_NONE =0,CTRL_LOAD,CTRL_FLY,

					CTRL_QUIT2DOS,
					CTRL_CANCEL,CTRL_ACCEPT,

					GOTOMAP,GOTOACCEL,CTRL_CONFIG_FROM_3D,CTRL_SAVE,


					CTRL_H2HQUIT,CTRL_H2HPLAY

					
					};

enum	{		CLIPBOARDAREAX = PIXEL640 * 85,					//RDH 20Jul96
				INTROCLIPBOARDAREAX = PIXEL640 * 14,
				CLIPBOARDAREAY = PIXEL640 * 136,
				CLIPBOARDAREAW = PIXEL640 * 412, 
				CLIPBOARDAREAH = PIXEL640 * 344,
				CRCTEXTAREAX = PIXEL640 * 148, 					//RDH 08Mar96
				CRCTEXTAREAY = PIXEL640 * 169,
				CRCTEXTAREAW = PIXEL640 * 339, 
				CRCTEXTAREAH = PIXEL640 * 311
				
				};



#endif
