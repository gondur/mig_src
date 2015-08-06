////NOTE:	PLEASE READ THE NOTES!!!!
//// View matrix reserves 8x8 key entries - keys 64 to 127:
//// viewee:	unchanged, pilot, fr,unf, gr, home	  		//5/8
//// viewtype:  unchanged, inside, outside, satelite, chase //5/8
//// Keys are not mapped to all these entries, but extras can be added externally
//// This will make gaps in the key lists above.
////
////NOTE:
//// View matrix reserves 8x8 key entries - keys 64 to 127:
//// viewee:	unchanged, pilot, fr, unf, gr, home	  		//5/8
//// viewtype:  unchanged, inside, outside, satelite, chase //5/8
//// Keys are not mapped to all these entries, but extras can be added externally
//// This will make gaps in the key lists above.
////
////NOTE:
//// View matrix reserves 8x8 key entries - keys 64 to 127:
//// viewee:	unchanged, pilot, fr, unf, gr, home	  		//5/8
//// viewtype:  unchanged, inside, outside, satelite, chase //5/8
//// Keys are not mapped to all these entries, but extras can be added externally
//// This will make gaps in the key lists above.
////
////NOTE:
//// View matrix reserves 8x8 key entries - keys 64 to 127:
//// viewee:	unchanged, pilot, fr, unf, gr, home	  		//5/8
//// viewtype:  unchanged, inside, outside, satelite, chase //5/8
//// Keys are not mapped to all these entries, but extras can be added externally
//// This will make gaps in the key lists above.
////
////NOTE:
//// View matrix reserves 8x8 key entries - keys 64 to 127:
//// viewee:	unchanged, pilot, fr, unf, gr, home	  		//5/8
//// viewtype:  unchanged, inside, outside, satelite, chase //5/8
//// Keys are not mapped to all these entries, but extras can be added externally
//// This will make gaps in the key lists above.
////
////NOTE:
//// View matrix reserves 8x8 key entries - keys 64 to 127:
//// viewee:	unchanged, pilot, fr, unf, gr, home	  		//5/8
//// viewtype:  unchanged, inside, outside, satelite, chase //5/8
//// Keys are not mapped to all these entries, but extras can be added externally
//// This will make gaps in the key lists above.
////
////NOTE:
//// View matrix reserves 8x8 key entries - keys 64 to 127:
//// viewee:	unchanged, pilot, fr, unf, gr, home	  		//5/8
//// viewtype:  unchanged, inside, outside, satelite, chase //5/8
//// Keys are not mapped to all these entries, but extras can be added externally
//// This will make gaps in the key lists above.
////
////NOTE:
//// View matrix reserves 8x8 key entries - keys 64 to 127:
//// viewee:	unchanged, pilot, fr, unf, gr, home	  		//5/8
//// viewtype:  unchanged, inside, outside, satelite, chase //5/8
//// Keys are not mapped to all these entries, but extras can be added externally
//// This will make gaps in the key lists above.
////
////NOTE:
//// View matrix reserves 8x8 key entries - keys 64 to 127:
//// viewee:	unchanged, pilot, fr, unf, gr, home	  		//5/8
//// viewtype:  unchanged, inside, outside, satelite, chase //5/8
//// Keys are not mapped to all these entries, but extras can be added externally
//// This will make gaps in the key lists above.
////
////NOTE:
//// View matrix reserves 8x8 key entries - keys 64 to 127:
//// viewee:	unchanged, pilot, fr, unf, gr, home	  		//5/8
//// viewtype:  unchanged, inside, outside, satelite, chase //5/8
//// Keys are not mapped to all these entries, but extras can be added externally
//// This will make gaps in the key lists above.
////
////NOTE:
//// View matrix reserves 8x8 key entries - keys 64 to 127:
//// viewee:	unchanged, pilot, fr, unf, gr, home	  		//5/8
//// viewtype:  unchanged, inside, outside, satelite, chase //5/8
//// Keys are not mapped to all these entries, but extras can be added externally
//// This will make gaps in the key lists above.
//------------------------------------------------------------------------------
//Filename       keymaps.h
//System         
//Author         Jim Taylor
//Date           Fri 3 Nov 1995
//Description    Keyboard mappings definition include file
//				Generally, this file declares CONSTs, but it also can make data.
//
// I am implementing the bloody view matrix 'cos if I don't we will never fit it in!
//
//
//------------------------------------------------------------------------------
#ifndef	KEYMAPS_Included
#define	KEYMAPS_Included

#define	KeyName(keynum,keyname)				\
KeyVal3D	const	keyname=(KeyVal3D)(keynum*2);

//------------------------------------------------------------------------------
// Place new 3d key press equate definitions in the list below
// The first number must be sequential, but we can leave gaps
// The second field is the name used in the 3d
//The mapping to the keyboard keys goes in the next table 
//------------------------------------------------------------------------------

//DeadCode JIM 22Nov96 enum KeyVal3D	{
KeyName(00,ReservedKeyMapping)
//keys 01..07 now reserved for shifts:
KeyName(01,KeySrc_BN_extsh)/*(Extended Shift)*/
KeyName(02,KeySrc_BN_AltL)/*(Left Alt)*/
KeyName(03,KeySrc_BN_AltGR)/*(AltGr)*/
KeyName(04,KeySrc_BN_CtrlL)
KeyName(05,KeySrc_BN_CtrlR)
KeyName(06,KeySrc_BN_ShiftL)
KeyName(07,KeySrc_BN_ShiftR)


KeyName(8,ELEVATOR_BACK)/*Elevator Back*/
KeyName(9,ELEVATOR_FORWARD)/*Elevator Forward*/
KeyName(10,AILERON_RIGHT)/*Aieron Right*/
KeyName(11,AILERON_LEFT)/*Aileron Left*/
KeyName(12,SENS_UP)/*Increase Keyboard Sensitivity*/
KeyName(13,SENS_DOWN)/*Decrease Keyboard Sensitivity*/
/**/KeyName(14,RUDDER_CLR)
KeyName(15,RUDDER_LEFT)/*Rudder Left*/
KeyName(16,RUDDER_RIGHT)/*Rudder Right*/
/**/KeyName(17,RUDDER_KLEFT)
/**/KeyName(18,RUDDER_KRIGHT)
KeyName(19,RPM_UP)	  /*Throttle Up 1%*/
KeyName(20,RPM_DOWN)	/*Throttle Down 1%*/	
/**/KeyName(21,RPM_MIL)
/**/KeyName(22,RPM_MIN)
/**/KeyName(23,RPM_BIG_UP)
/**/KeyName(24,RPM_BIG_DOWN)
//DeadCode JIM 10Aug96 KeyName(25,RPM_UP)
//DeadCode JIM 10Aug96 KeyName(26,RPM_DOWN)


//PD 19Feb96 - view zoom / rotation keys
KeyName(26,BIGROTDOWN)/*Down Fast*/												//PD 19Feb96
KeyName(27,BIGROTUP)/*Up Fast*/											//PD 19Feb96
KeyName(28,BIGROTRIGHT)/*Right Fast*/										//PD 19Feb96
KeyName(29,BIGROTLEFT)/*Left Fast*/											//PD 19Feb96

KeyName(30,BIGROTDNLEFT)/*Down Left Fast*/										//PD 19Feb96
KeyName(31,BIGROTDNRIGHT)/*Down Right Fast*/										//PD 19Feb96
KeyName(32,BIGROTUPLEFT)/*Up Left Fast*/										//PD 19Feb96
KeyName(33,BIGROTUPRIGHT)/*Up Right Fast*/										//PD 19Feb96

KeyName(34,BIGZOOMIN)/*Zoom In Fast*/											//PD 19Feb96
KeyName(35,BIGZOOMOUT)/*Zoom Out Fast*/											//PD 19Feb96

KeyName(36,ROTDOWN)/*Down/Back*/				//jim killed this							//PD 19Feb96
KeyName(37,ROTUP)/*Up/Forward*/											//PD 19Feb96
KeyName(38,ROTRIGHT)/*Right*/										//PD 19Feb96
KeyName(39,ROTLEFT)/*Left*/											//PD 19Feb96

KeyName(40,ROTDNLEFT)/*Down/Back and Left*/											//PD 19Feb96
KeyName(41,ROTDNRIGHT)/*Down/Back and Right*/										//PD 19Feb96
KeyName(42,ROTUPLEFT)/*Up/Forward and Left*/										//PD 19Feb96
KeyName(43,ROTUPRIGHT)/*Up/Forward and Right*/										//PD 19Feb96

KeyName(44,ZOOMIN)/*Zoom In*/											//PD 19Feb96
KeyName(45,ZOOMOUT)/*Zoom Out*/											//PD 19Feb96

KeyName(46,ROTRESET)/*View Reset*/										//PD 19Feb96
KeyName(47,SCREENSHOT)/*Screenshot*/										//DAW 21Feb96
//DEADCODE RDH 16/04/99 KeyName(48,ZOOMMAP)												//RJS 08Sep98
//DEADCODE RDH 01/07/99 KeyName(49,ALIASDUMP)
KeyName(49,RPM_OFF)/*0%  Throttle*/									//DAW 14Sep99
KeyName(50,SHOOT)/*Fire*/											//PD 01Apr96
KeyName(51,PAUSEKEY)/*Pause*/										//PD 15Mar96
KeyName(52,RPM_10)/*10% Throttle*/											//RDH 22Apr96
KeyName(53,RPM_20)/*20% Throttle*/											//RDH 22Apr96
KeyName(54,RPM_30)/*30% Throttle*/											//RDH 22Apr96
KeyName(55,RPM_40)/*40% Throttle*/											//RDH 22Apr96
KeyName(56,RPM_50)/*50% Throttle*/											//RDH 22Apr96
KeyName(57,RPM_60)/*60% Throttle*/											//RDH 22Apr96
KeyName(58,RPM_70)/*70% Throttle*/											//RDH 22Apr96
KeyName(59,RPM_80)/*80% Throttle*/											//RDH 22Apr96
////NOTE:
//// View matrix reserves 8x8 key entries - keys 64 to 127:
//// viewee:	unchanged, pilot, fr, unf, gr, home	  		//5/8
//// viewtype:  unchanged, inside, outside, satelite, chase //5/8
//// Keys are not mapped to all these entries, but extras can be added externally
//// This will make gaps in the key lists above.
////
KeyName(60,RPM_90)/*90% Throttle*/											//RDH 22Apr96
KeyName(61,RPM_00)/*100% Throttle*/											//RDH 22Apr96
KeyName(62,INFOPANEL)/*Info Panel Toggle*/										//RDH 22Apr96
KeyName(63,DETAILUP)/*Increase 3d detail*/										//PD 20May96
////PLEASE READ COMMENTS.
////PLEASE READ COMMENTS.

////NOTE:
//// View matrix reserves 8x8 key entries - keys 64 to 127:
//// viewee:	unchanged, pilot, fr, unf, gr, home	  		//5/8
//// viewtype:  unchanged, inside, outside, satelite, chase //5/8
//// Keys are not mapped to all these entries, but extras can be added externally
//// This will make gaps in the key lists above.
////
////
//// The following keys will form the start of the view matrix
////
////
//
// Row 0,(65,66,67,68,69,70,71 and Col 0 (72,80,88,96,104,112,120) only effect 1 axis
//
// Values inside grid effect both axes. 
//
//
KeyName(65,RESETVIEW)/*Reset View*/											//PD 19Feb96
KeyName(66,ENEMYVIEW)/*Next Enemy View*/										//PD 19Feb96
KeyName(67,FRNDVIEW)/*Next Friend View*/										//PD 19Feb96
KeyName(68,GRNDTVIEW)/*Next Ground Target View*/										//PD 19Feb96
KeyName(69,WAYPTVIEW)/*Next Waypoint View*/										//PD 19Feb96


//PD 19Feb96 - view type select keys

KeyName(72,INSIDETOG)/*Cockpit Camera*/											//PD 19Feb96
//combination key
KeyName(74,INOUTTOG)/*Inside/Outside View Toggle*///inside+enemy-64						//JIM 23Oct96

KeyName(80,OUTSIDETOG)/*Track Camera*/										//PD 19Feb96
//combination key
KeyName(82,PADLOCKTOG)/*Padlock Toggle*/ //outside+enemy-64						//PD 26Sep96

KeyName(88,SATELLITOG)/*Satellite Cam*/										//PD 19Feb96
KeyName(96,CHASETOG)/*Chase Camera*/										//PD 19Feb96
/**/KeyName(104,NOPITTOG)										//PD 19Feb96
/**/KeyName(112,OUTREVLOCKTOG)									//PD 27Jun96

KeyName(114,RESETENEMYVIEW)/*Reset Enemy View*/									//PD 19Feb96
KeyName(115,RESETFRNDVIEW)/*Reset Friend View*/									//PD 19Feb96
KeyName(116,RESETGRNDTVIEW)/*Reset Ground Target View*/									//PD 19Feb96
KeyName(117,RESETWAYPTVIEW)	/*Reset Waypoint View*/								//PD 19Feb96




/**/KeyName(128,KEY_JOYSTICKCONFIG)										//PD 20May96
KeyName(129,KEY_CONFIGMENU)/*Preferences (Configuration*/											//PD 20May96
KeyName(130,ACCELKEY)/*Accelerated Mode Toggle*/											//PD 20May96
/**/KeyName(131,AUTOKEY)											//PD 20May96
KeyName(132,CHEATLIFTKEY)/*Increase Altitude by 1000ft*/										//RDH 21Jul96

KeyName(133,MSGVIEW)/*View of Subject of Current Msg*/											//PD 02Sep96
//DEADCODE RDH 01/07/99 KeyName(134,RESETMSG)											//PD 02Sep96
//KeyName(135,GOHOME)												//RDH 24Sep96
//DEADCODE RDH 16/04/99 KeyName(136,FRAMERATEKEY)										//RDH 06Oct96


/**/KeyName(140,DROPBOMB)											//RJS 12Aug96
//DEADCODE RDH 24/03/99 KeyName(141,REFORMATION)
KeyName(142,GOTOMAPKEY)/*Map*/											//RDH 03Nov96

/**/KeyName(143,SHAPECHEATTOG)										//RJS 11Nov96
KeyName(144,NEXTSHAPEUP)/*Field of View: Zoom In*/										//RJS 11Nov96
KeyName(145,NEXTSHAPEDN)/*Field of View: Zoom Out*/										//RJS 11Nov96

KeyName(146,RESURRECTKEY)/*Jump out of  Regeneration(comms)*/										//ARM 05Dec96
KeyName(147,LEFTWHEELBRAKE)/*Left Wheel Brake*/								//ARM 27Feb97
KeyName(148,RIGHTWHEELBRAKE)/*Right Wheel Brake*/								//ARM 27Feb97
KeyName(149,SPEEDBRAKE)/*Air Brake*/										//ARM 13Mar97
KeyName(150,GEARUPDOWN)/*Gear Toggle*/										//ARM 07Apr97
//DEADCODE RDH 16/04/99 KeyName(151,ENGINESTARTSTOP)									//ARM 11Apr97
KeyName(152,FLAPSUPDOWN)/*Flaps Toggle*/										//ARM 11Apr97

KeyName(153,LASTWEAPON)/*Previous Weapon*/											//RJS 09Jun97
KeyName(154,NEXTWEAPON)/*Next Weapon*/										//RJS 09Jun97

KeyName(155,RELOADWEAPON)/*Reload Weapons*/									//RJS 10Jun97
KeyName(156,DUMPWEAPONS)/*Dump Weapons*/									//RJS 10Jun97

//DEADCODE RDH 16/04/99 KeyName(157,FUELTOGGLE)											//RJS 10Jun97
KeyName(158,DUMPFUEL)/*Dump Fuel*/											//RJS 10Jun97

KeyName(159,ELEVTRIMFWD)/*Forward Elevator Trim*/									//ARM 31Jul97
KeyName(160,ELEVTRIMAFT)/*Aft Elevator Trim*/									//ARM 31Jul97
KeyName(161,ELEVTRIMNEU)/*Reset Elevator Trim*/									//ARM 31Jul97

KeyName(162,LOOKNE)/*Sticky Look Forward/Right*/												//PD 28Jan97
KeyName(163,LOOKE)/*Sticky Right*/											//PD 28Jan97
KeyName(164,LOOKSE)/*Sticky Look Back/Right*/											//PD 28Jan97
KeyName(165,LOOKS)/*Sticky Look Back*/											//PD 28Jan97
KeyName(166,LOOKSW)/*Sticky Look Back/Left*/											//PD 28Jan97
KeyName(167,LOOKW)/*Sticky Left*/											//PD 28Jan97
KeyName(168,LOOKNW)/*Sticky Look Forward/Left*/											//PD 28Jan97
KeyName(169,LOOKN)/*Sticky Look Forward*/											//PD 28Jan97
KeyName(170,LOOKUPNE)/*Sticky Look Up Forward/Right*/										//PD 28Jan97
KeyName(171,LOOKUPE)/*Sticky Look Up Righ*/										//PD 28Jan97
KeyName(172,LOOKUPSE)/*Sticky Look Up Back/Right*/										//PD 28Jan97
KeyName(173,LOOKUPS)/*Sticky Look Up Back*/										//PD 28Jan97
KeyName(174,LOOKUPSW)/*Sticky Look Up Back/Left*/										//PD 28Jan97
KeyName(175,LOOKUPW)/*Sticky Look Up Left*/										//PD 28Jan97
KeyName(176,LOOKUPNW)/*Sticky Look Up Forward/Left*/										//PD 28Jan97
KeyName(177,LOOKUPN)/*Sticky Look Up Forward*/										//PD 28Jan97
//DEADCODE RDH 17/05/99 KeyName(178,ROOKUPNE)										//PD 28Jan97
//DEADCODE RDH 17/05/99 KeyName(179,ROOKUPE)										//PD 28Jan97
//DEADCODE RDH 17/05/99 KeyName(180,ROOKUPSE)										//PD 28Jan97
//DEADCODE RDH 17/05/99 KeyName(181,ROOKUPS)										//PD 28Jan97
//DEADCODE RDH 17/05/99 KeyName(182,ROOKUPSW)										//PD 28Jan97
//DEADCODE RDH 17/05/99 KeyName(183,ROOKUPW)										//PD 28Jan97
//DEADCODE RDH 17/05/99 KeyName(184,ROOKUPNW)										//PD 28Jan97
//DEADCODE RDH 17/05/99 KeyName(185,ROOKUPN)										//PD 28Jan97
KeyName(186,LOOKUPTOG)/*Look up toggle for Sticky keys*/										//PD 28Jan97
//DEADCODE RDH 01/07/99 KeyName(187,SCREENSHOT2)
/**/KeyName(188,UNJAMGUNS)											//RDH 09May97
KeyName(189,VIEWMODETOG)/*Panning/Fixed View Toggle*/									//PD 15Jul97
KeyName(190,PANLEFT)/*Pan Left*/									//PD 15Jul97
KeyName(191,PANRIGHT)/*Pan Right*/									//PD 15Jul97
KeyName(192,SUICIDE)/*Stop death sequence(comms)*/										//AMM 19Jun97
//DEADCODE RDH 16/04/99 KeyName(193,MAGICK1)											//RJS 05Aug97
//DEADCODE RDH 16/04/99 KeyName(194,MAGICK2)											//RJS 05Aug97
//DEADCODE RDH 16/04/99 KeyName(195,MAGICK3)											//RJS 05Aug97
KeyName(196,AROTUPRIGHT)/*Alt: Up/Forward and Right*/										//PD 03Sep97
KeyName(197,AROTRIGHT)/*Alt: Right*/
KeyName(198,AROTDNRIGHT)/*Alt: Down/Back and Right*/
KeyName(199,AROTDOWN)/*Alt: Down/Back*/
KeyName(200,AROTDNLEFT)/*Alt: Down/Back and Left*/
KeyName(201,AROTLEFT)/*Alt: Left*/
KeyName(202,AROTUPLEFT)/*Alt: Up/Forward and Left*/
KeyName(203,AROTUP)/*Alt: Up/Forward*/
/**/KeyName(204,AZOOMOUT)/*Alt: Zoom Out*/
KeyName(205,APANLEFT)/*Pan Left in Fixed View Mode*/
KeyName(206,APANRIGHT)/*Pan Right in Fixed View Mode*/										//PD 03Sep97
KeyName(207,ALOOKNE)/*Alt: Forward Right*/										//PD 03Sep97
KeyName(208,ALOOKSE)/*Alt: Back Right*/
KeyName(209,ALOOKS)/*Alt: Back*/
/**/KeyName(210,ALOOKSW)/*Alt: Back Left*/
KeyName(211,ALOOKNW)/*Alt: Forward Left*/
KeyName(212,ALOOKN)	/*Alt: Forward*/										//PD 03Sep97
/**/KeyName(213,ALOOKUPNE)/*Alt: Forward Right Up*/										//PD 03Sep97
/**/KeyName(214,ALOOKUPSE)/*Alt: Back Right Up*/
/**/KeyName(215,ALOOKUPSW)/*Alt: Back Left Up*/
/**/KeyName(216,ALOOKUPNW)/*Alt: Forward Left Up*/										//PD 03Sep97
KeyName(217,ROTRESET2)/*Alt: View Reset*/										//RDH 15Sep97
KeyName(218,TOGGLEWOBBLEVIEW)/*Fixed/Free Camera for f6 View*/								//PD 07Oct97
KeyName(219,PREVENEMYVIEW)/*Previous Enemy View*/									//PD 08Oct97
KeyName(220,PREVFRNDVIEW)/*Previous Friend View*/										//PD 08Oct97
KeyName(221,PREVGRNDTVIEW)/*Previous Ground Target View*/									//PD 08Oct97
KeyName(222,PREVWAYPTVIEW)/*Previous Waypoint View*/									//PD 08Oct97
//DEADCODE RDH 01/07/99 KeyName(223,PREVMSGVIEW)/**/									//PD 08Oct97
KeyName(224,EJECTPILOT)	/*Eject Pilot*/									//RJS 27Jan98
/**/KeyName(225,DETAILDIALS)										//RJS 27Jan98
/**/KeyName(226,DETAILCANOPY)										//RJS 27Jan98
/**/KeyName(227,DETAILPANEL)										//RJS 27Jan98
/**/KeyName(228,DETAILSIDES)										//RJS 27Jan98
/**/KeyName(229,DETAILSIGHT)										//RJS 27Jan98
/**/KeyName(230,AB_UP)		//these were 0-7 before //0-7 now shift key specials//RJS 20Apr98
/**/KeyName(231,AB_DOWN)											//RJS 20Apr98
KeyName(232,IMPACTTOG)/*Impact Toggle*/											//RJS 20Apr98
KeyName(233,CHEATTOG)/*Forward View- no cockpit*/											//RJS 20Apr98
KeyName(234,EXITKEY)/*Exit Game*/											//RJS 20Apr98
KeyName(235,SPINRECOVERY)/*Spin Recovery*/										//RJS 20Apr98
KeyName(236,WINGSPANUP)/*Wingspan Up (gun sight)*/										//RJS 20Apr98
KeyName(237,WINGSPANDOWN)/*Wingspan Down (gun sight)*/									//RJS 20Apr98
KeyName(238,GUNRANGEUP)/*Increase Range (gun sight)*/										//RJS 20Apr98
KeyName(239,GUNRANGEDOWN)/*Reduce Range (gun sight)*/									//RJS 20Apr98
/**/KeyName(240,CANOPYEJECT)									//RJS 20Apr98
/**/KeyName(241,MENUMINUS)
/**/KeyName(242,MENUPLUS)
/**/KeyName(243,MENUBACK)
KeyName(244,BOXTARGET)/*Box Padlocked item*/										//RJS 05Nov98 //RDH 16/04/99
KeyName(245,RESTARTENGINE)/*Engine restart*/
KeyName(246,RECORDTOGGLE)/*Gun Camera Toggle*/
KeyName(247,RESETRECORD)/*Reset Gun Camera*/
KeyName(248,RPMTOGGLE)/*Power/Cruise setting for Mustang*/
KeyName(249,ACCELKEY2)/*Acclerated Mode on the Map*/											//PD 03Mar99
KeyName(250,RADIOCOMMS)	/*Initiate Radio Communications*/									//RDH 24/03/99
KeyName(251,HUDTOGGLE)/*Head Up InstrumentsToggle*/
KeyName(252,ANYBANDITS)/*Any Bandits*/													  //RDH 10/05/99
KeyName(253,CLEAR)/*Clear?/Clear*/
KeyName(254,BREAK)/*Break*/
KeyName(255,GROUPINFOMSG)/*Group Info Messages*/
KeyName(256,PRECOMBATMSG)/*Precombat Messages*/
KeyName(257,COMBATMSG)/*Combat Messages*/
KeyName(258,POSTCOMBATMSG)/*PostCombat Messages*/
KeyName(259,TOWERMSG)/*Tower Messages*/
KeyName(260,FACMSG)/*FAC  Messages*/													  //RDH 10/05/99
KeyName(261,CYCLETHROUGHWEAPONS)/*Cycle Through Weapons*/													  //RDH 10/05/99
KeyName(262,ESCORTEEVIEW)/*Escortee*/	
KeyName(263,AIUNFRIENDLYVIEW)/*A.I.Enemy View*/	
KeyName(264,SEEMIGS)/*See MiGs on 3d map*/
KeyName(265,TOGGLEMESSAGES)/*toggle displaying of radio message text in the 3d*/
KeyName(266,AROTRESET)/*View Reset*/
KeyName(267,ALOOKE)/*Look Right*/
KeyName(268,ALOOKW)/*Look Left*/
KeyName(269,ALOOKUP)/*Look Up*/
KeyName(270,DETAILDN)/*Decrease 3d detail*/
KeyName(271,VOICETOGGLE)/*Player Voice Toggle*/
KeyName(280,MENUSELECT)		//commented out for neatness [and they where duplicates]
KeyName(281,NEWFLAPSUP)	//New Flap controls for US version and Patch	//CSB 24/08/99	
KeyName(282,NEWFLAPSMID)	//New Flap controls for US version and Patch	//CSB 24/08/99	
KeyName(283,NEWFLAPSDOWN)	//New Flap controls for US version and Patch	//CSB 24/08/99	
KeyName(284,INSTVIEW)
KeyName(285,INSTVIEW2)
//DeadCode DAW 30Jun99 KeyName(281,MENU1)/*GOK 1*/
//DeadCode DAW 30Jun99 KeyName(282,MENU2)/*GOK 2*/
//DeadCode DAW 30Jun99 KeyName(283,MENU3)/*GOK 3*/
//DeadCode DAW 30Jun99 KeyName(284,MENU4)/*GOK 4*/
//DeadCode DAW 30Jun99 KeyName(285,MENU5)/*GOK 5*/
//DeadCode DAW 30Jun99 KeyName(286,MENU6)/*GOK 6*/
//DeadCode DAW 30Jun99 KeyName(287,MENU7)/*GOK 7*/
//DeadCode DAW 30Jun99 KeyName(288,MENU8)/*GOK 8*/
//DeadCode DAW 30Jun99 KeyName(289,MENU9)/*GOK 9*/
//DeadCode DAW 30Jun99 KeyName(290,MENU10)
//new keys go here^^^^^^^
KeyName(400,TOTALKEYBITFLAGS2)
//DeadCode JIM 22Nov96 };
#undef	KeyName
//------------------------------------------------------------------------------
// Place new 3d key press equate definitions in the list ABOVE
// The first number must be sequential
// The second field is the name used in the 3d
//The mapping to the keyboard keys goes in the next table 
//------------------------------------------------------------------------------
#endif		//file single pass

#ifdef	SPECIAL_KEYMAPS
#include	<dinput.h>

enum Raw_Keys	{
		Raw_esc		=DIK_ESCAPE   	,	//01,
		Raw_n1		=DIK_1        	,	//02,
		Raw_n2		=DIK_2        	,	//03,
		Raw_n3		=DIK_3        	,	//04,
		Raw_n4		=DIK_4        	,	//05,
		Raw_n5		=DIK_5        	,	//06,
		Raw_n6		=DIK_6        	,	//07,
		Raw_n7		=DIK_7        	,	//08,
		Raw_n8		=DIK_8        	,	//09,
		Raw_n9		=DIK_9        	,	//10,
		Raw_n0		=DIK_0        	,	//11,
		Raw_minus	=DIK_MINUS    	,	//12,
		Raw_equal	=DIK_EQUALS   	,	//13,
		Raw_backspc	=DIK_BACK     	,	//14,
		Raw_tab		=DIK_TAB      	,	//15,
		Raw_q		=DIK_Q        	,	//16,
		Raw_w		=DIK_W        	,	//17,
		Raw_e		=DIK_E        	,	//18,
		Raw_r		=DIK_R        	,	//19,
		Raw_t		=DIK_T        	,	//20,
		Raw_y		=DIK_Y        	,	//21,
		Raw_u		=DIK_U        	,	//22,
		Raw_i		=DIK_I        	,	//23,
		Raw_o		=DIK_O        	,	//24,
		Raw_p		=DIK_P        	,	//25,
		Raw_open	=DIK_LBRACKET 	,	//26,
		Raw_close	=DIK_RBRACKET 	,	//27,
		Raw_enter	=DIK_RETURN   	,	//28,
		Raw_shiftctl=DIK_LCONTROL 	,	//29,
		Raw_a		=DIK_A        	,	//30,
		Raw_s		=DIK_S        	,	//31,
		Raw_d		=DIK_D        	,	//32,
		Raw_f		=DIK_F        	,	//33,
		Raw_g		=DIK_G        	,	//34,
		Raw_h		=DIK_H        	,	//35,
		Raw_j		=DIK_J        	,	//36,
		Raw_k		=DIK_K        	,	//37,
		Raw_l		=DIK_L        	,	//38,
		Raw_semi	=DIK_SEMICOLON	,	//39,
		Raw_quote	=DIK_APOSTROPHE	,	//40,
		Raw_hash	=DIK_GRAVE    	,	//41,
		Raw_shiftlef=DIK_LSHIFT   	,	//42,
		Raw_bslash	=DIK_BACKSLASH	,	//43,
		Raw_z		=DIK_Z        	,	//44,
		Raw_x		=DIK_X        	,	//45,
		Raw_c		=DIK_C        	,	//46,
		Raw_v		=DIK_V        	,	//47,
		Raw_b		=DIK_B        	,	//48,
		Raw_n		=DIK_N        	,	//49,
		Raw_m		=DIK_M        	,	//50,
		Raw_comma	=DIK_COMMA    	,	//51,
		Raw_stop	=DIK_PERIOD   	,	//52,
		Raw_slash	=DIK_SLASH    	,	//53,
		Raw_shiftrig=DIK_RSHIFT   	,	//54,
		Raw_print	=DIK_MULTIPLY 	,	//55,
		Raw_shiftalt=DIK_LMENU    	,	//56,
		Raw_space	=DIK_SPACE    	,	//57,
		Raw_lockcap	=DIK_CAPITAL  	,	//58,
		Raw_f1		=DIK_F1       	,	//59,
		Raw_f2		=DIK_F2       	,	//60,
		Raw_f3		=DIK_F3       	,	//61,
		Raw_f4		=DIK_F4       	,	//62,
		Raw_f5		=DIK_F5       	,	//63,
		Raw_f6		=DIK_F6       	,	//64,
		Raw_f7		=DIK_F7       	,	//65,
		Raw_f8		=DIK_F8       	,	//66,
		Raw_f9		=DIK_F9       	,	//67,
		Raw_f10		=DIK_F10      	,	//68,
		Raw_locknum	=DIK_NUMLOCK 	,	//69,
		Raw_lockscr	=DIK_SCROLL  	,	//70,
		Raw_movehome=DIK_NUMPAD7 	,	//71,
		Raw_moveup	=DIK_NUMPAD8 	,	//72,
		Raw_pageup	=DIK_NUMPAD9 	,	//73,
		Raw_numminus=DIK_SUBTRACT	,	//74,
		Raw_moveleft=DIK_NUMPAD4 	,	//75,
		Raw_movefive=DIK_NUMPAD5 	,	//76,
		Raw_moveright=DIK_NUMPAD6 	,	//77,
		Raw_numplus	=DIK_ADD     	,	//78,
		Raw_moveend	=DIK_NUMPAD1 	,	//79,
		Raw_movedown=DIK_NUMPAD2 	,	//80,
		Raw_pagedown=DIK_NUMPAD3 	,	//81,
		Raw_insert	=DIK_NUMPAD0 	,	//82,
		Raw_delete	=DIK_DECIMAL 	,	//83,
		Raw_DISABLED=DIK_F11+1	,		//00,

		Raw_F11		=DIK_F11	,		//87,	//VF on Jap keyboard
		Raw_F12		=DIK_F12	,		//88,
		Raw_F13		=DIK_F13	,		//100,	//VF on Jap keyboard
		Raw_F14		=DIK_F14	 ,		//101,
		Raw_F15		=DIK_F15	  ,		//102,
//extra keys on japanese keyboard:
		Raw_J_kana		=DIK_KANA,           //112,
		Raw_J_convert	=DIK_CONVERT,		//121,
		Raw_J_noconv	=DIK_NOCONVERT,		//123,
		Raw_J_yen		=DIK_YEN,			//124,
		Raw_J_equal		=DIK_NUMPADEQUALS,  	//141,
		Raw_J_circum	=DIK_CIRCUMFLEX,		//144,
		Raw_J_at		=DIK_AT,				//145,
		Raw_J_colon		=DIK_COLON,			//146,
		Raw_J_under		=DIK_UNDERLINE,		//147,
		Raw_J_kanji		=DIK_KANJI,			//148,
		Raw_J_stop		=DIK_STOP,			//149,
		Raw_J_ax		=DIK_AX,				//150,
		Raw_J_blank		=DIK_UNLABELED,		//151,

		//Were ExtShift in MS-DOS: Called _J_ in Japanese conversion of FCG
		Raw_J_enter		=DIK_NUMPADENTER,	//156,
		Raw_shiftctr		=DIK_RCONTROL,	//157,
		Raw_J_comma		=DIK_NUMPADCOMMA,	//179,
		Raw_J_lockscr	=DIK_DIVIDE,		//181,
		Raw_J_sysreq	=DIK_SYSRQ,			//183,
		Raw_shiftagr	=DIK_RMENU,			//184,
		Raw_J_movehome	=DIK_HOME       ,	//199,
		Raw_J_moveup	=DIK_UP         ,	//200,
		Raw_J_pageup	=DIK_PRIOR      ,	//201,
		Raw_J_moveleft	=DIK_LEFT       ,	//203,
		Raw_J_moveright	=DIK_RIGHT		,	//205,
		Raw_J_moveend	=DIK_END        ,	//207,
		Raw_J_movedown	=DIK_DOWN       ,	//208,
		Raw_J_pagedown	=DIK_NEXT       ,	//209,
		Raw_J_insert	=DIK_INSERT     ,	//210,
		Raw_J_delete	=DIK_DELETE     ,	//211,

		//extra keys on win'95 keyboard:
		Raw_WinL	=DIK_LWIN	,			//219,
		Raw_WinR	=DIK_RWIN	,			//220,
		Raw_WinM	=DIK_APPS	,			//221,


		Raw_A1_Fire		=250,	//250,		//Joystick key codes
		Raw_A1_b1		=251,	//251,					//First 8 are reserved for buttons	//
		Raw_A1_b2		=252,	//252,
		Raw_A1_b3		=253,	//253,
		Raw_A1_b4		=254,	//254,
		Raw_A1_b5		=255,	//255,
		Raw_A1_b6		=256,	//256,
		Raw_A1_b7		=257,	//257,
		Raw_A1_b8		=258,	//258,
		Raw_A1_b9		=259,	//259,
		Raw_A1_b10		=260,	//260,
		Raw_A1_b11		=261,	//261,
		Raw_A1_b12		=262,	//262,
		Raw_A1_b13		=263,	//263,
		Raw_A1_b14		=264,	//264,
		Raw_A1_b15		=265,	//265,
		Raw_A1_b16		=266,	//266,
		Raw_A1_b17		=267,	//267,
		Raw_A1_b18		=268,	//268,
		Raw_A1_b19		=269,	//269,
		Raw_A1_b20		=270,	//270,
		Raw_A1_b21		=271,	//271,
		Raw_A1_b22		=272,	//272,
		Raw_A1_b23		=273,	//273,
		Raw_A1_b24		=274,	//274,
		Raw_A1_b25		=275,	//275,
		Raw_A1_b26		=276,	//276,
		Raw_A1_b27		=277,	//277,	//IF 3 hats, then the remaining buttons unavailable	//buttons 
		Raw_A1_b28		=278,	//278,
		Raw_A1_b29		=279,	//279,	////
		Raw_A1_b30		=280,	//280,	////
		Raw_A1_b31		=281,	//281,
		Raw_A1_b32		=282,	//282,
		Raw_A1_b33		=283,	//283,
		Raw_A1_b34		=284,	//284,	//IF 2 hats the remaining buttons are unavailable	//are 
		Raw_A1_b35		=285,	//285,
		Raw_A1_b36		=286,	//286,
		Raw_A1_b37		=287,	//287,
		Raw_A1_b38		=288,	//288,
		Raw_A1_b39		=289,	//289,
		Raw_A1_hat3N	=276,	//276,				//second 8 are reserved for first hat
		Raw_A1_hat3NE	=277,	//277,
		Raw_A1_hat3E	=278,	//278,
		Raw_A1_hat3SE	=279,	//279,
		Raw_A1_hat3S	=280,	//280,
		Raw_A1_hat3SW	=281,	//281,
		Raw_A1_hat3W	=282,	//282,
		Raw_A1_hat3NW	=283,	//283,
		Raw_A1_hat2N	=284,	//284,				//second 8 are reserved for first hat
		Raw_A1_hat2NE	=285,	//285,
		Raw_A1_hat2E	=286,	//286,
		Raw_A1_hat2SE	=287,	//287,
		Raw_A1_hat2S	=288,	//288,
		Raw_A1_hat2SW	=289,	//289,
		Raw_A1_hat2W	=290,	//290,
		Raw_A1_hat2NW	=291,	//291,
		Raw_A1_hat1N	=292,	//292,			//second 8 are reserved for first hat
		Raw_A1_hat1NE	=293,	//293,
		Raw_A1_hat1E	=294,	//294,
		Raw_A1_hat1SE	=295,	//295,
		Raw_A1_hat1S	=296,	//296,
		Raw_A1_hat1SW	=297,	//297,
		Raw_A1_hat1W	=298,	//298,
		Raw_A1_hat1NW	=299,	//299,

		Raw_A2_Fire		=300,	//300,		//Joystick key codes
		Raw_A2_b1		=301,	//301,				//First 8 are reserved for buttons	
		Raw_A2_b2	=302,	//302,
		Raw_A2_b3	=303,	//303,
		Raw_A2_b4	=304,	//304,
		Raw_A2_b5	=305,	//305,
		Raw_A2_b6	=306,	//306,
		Raw_A2_b7	=307,	//307,
		Raw_A2_b8	=308,	//308,
		Raw_A2_hat3N	=326,	//326,				//second 8 are reserved for first hat
		Raw_A2_hat3NW	=333,	//333,
		Raw_A2_hat2N	=334,	//334,				//second 8 are reserved for first hat
		Raw_A2_hat2NW	=341,	//341,
		Raw_A2_hat1N	=342,	//342,				//second 8 are reserved for first hat
		Raw_A2_hat1NW	=349,	//349,


		Raw_A3_Fire		=350,	//350,		//Joystick key codes
		Raw_A3_b1	=351,	//351,					//First 8 are reserved for buttons	
		Raw_A3_b2	=352,	//352,
		Raw_A3_b3	=353,	//353,
		Raw_A3_b4	=354,	//354,
		Raw_A3_b5	=355,	//355,
		Raw_A3_hat3N	=376,	//376,				//second 8 are reserved for first hat
		Raw_A3_hat3NW	=383,	//383,
		Raw_A3_hat2N	=384,	//384,				//second 8 are reserved for first hat
		Raw_A3_hat2NW	=391,	//391,
		Raw_A3_hat1N	=392,	//392,				//second 8 are reserved for first hat
		Raw_A3_hat1NW	=399,	//399,

		Raw_A4_Fire=	400,	//400,		//Joystick key codes
		Raw_A4_b1	=401,	//401,
		Raw_A4_b2	=402,	//402,
		Raw_A4_b3	=403,	//403,
		Raw_A4_b4	=404,	//404,
		Raw_A4_b5	=405,	//405,
		Raw_A4_b6	=406,	//406,
		Raw_A4_b7	=407,	//407,
		Raw_A4_b8	=408,	//408,
		Raw_A4_hat3N	=426,	//426,				//second 8 are reserved for first hat
		Raw_A4_hat3NW	=433,	//433,
		Raw_A4_hat2N	=434,	//434,				//second 8 are reserved for first hat
		Raw_A4_hat2NW	=441,	//441,
		Raw_A4_hat1N	=442,	//442,				//second 8 are reserved for first hat
		Raw_A4_hat1NW	=449,	//449,


		Raw_A5_Fire		=450,	//450,		//Joystick key codes
		Raw_A5_b1		=451,	//451,					//First 8 are reserved for buttons
		Raw_A5_b2	=452,	//452,
		Raw_A5_b3	=453,	//453,
		Raw_A5_b4	=454,	//454,
		Raw_A5_b5	=455,	//455,
		Raw_A5_hat3N	=476,	//476,				//second 8 are reserved for first hat
		Raw_A5_hat3NW	=483,	//483,
		Raw_A5_hat2N	=484,	//484,				//second 8 are reserved for first hat
		Raw_A5_hat2NW	=491,	//491,
		Raw_A5_hat1N	=492,	//492,				//second 8 are reserved for first hat
		Raw_A5_hat1NW	=499,	//499,

		Raw_NOMORE	=0,	//0,
		};

#if	SPECIAL_KEYMAPS

#define	KeyMap(keyname,rawname,rawshift)	\
		{Raw_##rawname,KEYSH_BN_##rawshift,keyname},

#define	KeyAll(keyname,rawname)	\
		{Raw_##rawname,KEYSH_BN_norm	,keyname},	\
		{Raw_##rawname,KEYSH_BN_extsh	,keyname},	\
		{Raw_##rawname,KEYSH_BN_AltL	,keyname},	\
		{Raw_##rawname,KEYSH_BN_AltGR	,keyname},	\
		{Raw_##rawname,KEYSH_BN_CtrlL	,keyname},	\
		{Raw_##rawname,KEYSH_BN_CtrlR	,keyname},	\
		{Raw_##rawname,KEYSH_BN_ShiftL	,keyname},	\
		{Raw_##rawname,KEYSH_BN_ShiftR	,keyname},

//------------------------------------------------------------------------------
//	Define the physical mapping of the keys in the table below. 
//	Order is unimportant for code but important for us to keep tabs on key usage//RDH 07Aug98
//  3 fields:
//		1)	name of key used in game, as defined in above table
//		2)	name of raw key to be pressed
//		3)	shift key that should be pressed
//			this is one of:
//				norm	-	white key with no shift
//				extsh	-	grey direction keys and grey enter
//				AltL	-	left alt key
//				AltGR	-	right alt key
//				CtrlL	-	left control key
//				CtrlR	-	right control key
//				ShiftL	-	Left shift key
//				ShiftR	-	Right shift key
//		If you want a key to work with a number of different shifts,
//		or a number of different keys, then list it separately for each mapping.
//		If you want it for all mappings you can use KeyAll instead of KeyMap
//------------------------------------------------------------------------------
static	KeyMapping	ThisKeyMapping[]	=	{
//------------------------------------------------------------------------------

//shift keys mapped to generate shifts...
	KeyAll(KeySrc_BN_extsh,lockcap)
	KeyAll(KeySrc_BN_AltL,shiftalt)
	KeyAll(KeySrc_BN_AltGR,shiftagr)
	KeyAll(KeySrc_BN_CtrlL,shiftctl)
	KeyAll(KeySrc_BN_CtrlR,shiftctr)
	KeyAll(KeySrc_BN_ShiftL,shiftlef)
	KeyAll(KeySrc_BN_ShiftR,shiftrig)

//Keys put in order to aid administration						//RDH 07Aug98

//------------------------------------------------------------------------------
//Top Line
		KeyMap(RESETVIEW,		esc,	norm)						

		KeyMap(ENEMYVIEW,		f1,		norm)						
		KeyMap(RESETENEMYVIEW,	f1,		CtrlL)						
		KeyMap(RESETENEMYVIEW,	f1,		CtrlR)						
		KeyMap(PREVENEMYVIEW,	f1,		ShiftL)						
		KeyMap(PREVENEMYVIEW,	f1,		ShiftR)						
		KeyMap(AIUNFRIENDLYVIEW,	f1,		AltL)						
		KeyMap(AIUNFRIENDLYVIEW,	f1,		AltGR)						

		KeyMap(FRNDVIEW,		f2,		norm)						
		KeyMap(RESETFRNDVIEW,	f2,		CtrlL)						
		KeyMap(RESETFRNDVIEW,	f2,		CtrlR)						
		KeyMap(PREVFRNDVIEW,	f2,		ShiftL)						
		KeyMap(PREVFRNDVIEW,	f2,		ShiftR)						
		KeyMap(ESCORTEEVIEW,	f2,		AltL)						
		KeyMap(ESCORTEEVIEW,	f2,		AltGR)						


		KeyMap(GRNDTVIEW,		f3,		norm)						
		KeyMap(RESETGRNDTVIEW,	f3,		CtrlL)						
		KeyMap(RESETGRNDTVIEW,	f3,		CtrlR)						
		KeyMap(PREVGRNDTVIEW,	f3,		ShiftL)						
		KeyMap(PREVGRNDTVIEW,	f3,		ShiftR)						

		KeyMap(WAYPTVIEW,		f4,		norm)						
		KeyMap(RESETWAYPTVIEW,	f4,		CtrlL)						
		KeyMap(RESETWAYPTVIEW,	f4,		CtrlR)						
		KeyMap(PREVWAYPTVIEW,	f4,		ShiftL)						
		KeyMap(PREVWAYPTVIEW,	f4,		ShiftR)						

//DEADCODE RDH 01/07/99 		KeyMap(PREVMSGVIEW,		f5,		ShiftL)						
//DEADCODE RDH 01/07/99 		KeyMap(PREVMSGVIEW,		f5,		ShiftR)						
		KeyMap(MSGVIEW,			f5,		norm)						
//DEADCODE RDH 01/07/99 		KeyMap(RESETMSG,		f5,		CtrlL)						
//DEADCODE RDH 01/07/99 		KeyMap(RESETMSG,		f5,		CtrlR)						

		KeyMap(OUTREVLOCKTOG,	f6,		AltL)						
		KeyMap(OUTSIDETOG,		f6,		norm)						
		KeyMap(TOGGLEWOBBLEVIEW,	f6,			ShiftL)				  //RDH 02/06/99
		KeyMap(TOGGLEWOBBLEVIEW,	f6,			ShiftR)				  //RDH 02/06/99

		KeyMap(INSIDETOG,		f7,		norm)						
		KeyMap(CHEATTOG,		f8,		norm)						
		KeyMap(CHASETOG,		f9,		norm)						
		KeyMap(SATELLITOG,		f10,	norm)						
		KeyMap(IMPACTTOG,		F11,	norm)						
		KeyAll(KEY_CONFIGMENU,	F12)						
//DeadCode DAW 01Nov99 		KeyMap(KEY_CONFIGMENU,	F12,	norm)						

		KeyAll(SCREENSHOT,		J_sysreq)							
		KeyAll(LOOKUPTOG,		lockscr)							
		KeyAll(VIEWMODETOG,		locknum)							
		KeyMap(PANLEFT,			J_lockscr, norm)			//slash key on number pad				
		KeyMap(PANRIGHT,print, norm)						//multiple in number pad		

//------------------------------------------------------------------------------
//numbers

		KeyMap(RPM_OFF,			bslash,		norm)				//DAW 14Sep99
		KeyMap(RPM_OFF,			hash,		norm)				//DAW 14Sep99
		KeyMap(RPM_10,			n1,			norm)
		KeyMap(RPM_20,			n2,			norm)
		KeyMap(RPM_30,			n3,			norm)
		KeyMap(RPM_40,			n4,			norm)
		KeyMap(RPM_50,			n5,			norm)
		KeyMap(RPM_60,			n6,			norm)
		KeyMap(RPM_70,			n7,			norm)
		KeyMap(RPM_80,			n8,			norm)
		KeyMap(RPM_90,			n9,			norm)
		KeyMap(RPM_00,			n0,			norm)

//DeadCode DAW 19Jun99 #if	defined(NDEBUG)
		KeyMap(GROUPINFOMSG,	n1,			ShiftL)
		KeyMap(PRECOMBATMSG,	n2,			ShiftL)
		KeyMap(COMBATMSG,		n3,			ShiftL)
		KeyMap(POSTCOMBATMSG,	n4,			ShiftL)
		KeyMap(TOWERMSG,		n5,			ShiftL)
		KeyMap(FACMSG,			n6,			ShiftL)
//DeadCode DAW 19Jun99 #endif
		KeyMap(GROUPINFOMSG,	n1,			ShiftR)
		KeyMap(PRECOMBATMSG,	n2,			ShiftR)
		KeyMap(COMBATMSG,		n3,			ShiftR)
		KeyMap(POSTCOMBATMSG,	n4,			ShiftR)
		KeyMap(TOWERMSG,		n5,			ShiftR)
		KeyMap(FACMSG,			n6,			ShiftR)

		KeyMap(AROTDNLEFT,		n1,			AltL)
		KeyMap(AROTDOWN,		n2,			AltL)
		KeyMap(AROTDNRIGHT,		n3,			AltL)
		KeyMap(AROTLEFT,		n4,			AltL)
		KeyMap(AROTRESET,		n5,			AltL)
		KeyMap(AROTRIGHT,		n6,			AltL)
		KeyMap(AROTUPLEFT,		n7,			AltL)
		KeyMap(AROTUP,			n8,			AltL)
		KeyMap(AROTUPRIGHT,		n9,			AltL)

		KeyMap(AROTDNLEFT,		n1,			AltL)
		KeyMap(AROTDOWN,		n2,			AltL)
		KeyMap(AROTDNRIGHT,		n3,			AltL)
		KeyMap(AROTLEFT,		n4,			AltL)
		KeyMap(AROTRESET,		n5,			AltL)
		KeyMap(AROTRIGHT,		n6,			AltL)
		KeyMap(AROTUPLEFT,		n7,			AltL)
		KeyMap(AROTUP,			n8,			AltL)
		KeyMap(AROTUPRIGHT,		n9,			AltL)

		KeyMap(ALOOKSW,			n1,			CtrlL)
		KeyMap(ALOOKS,	 		n2,			CtrlL)
		KeyMap(ALOOKSE,			n3,			CtrlL)
		KeyMap(ALOOKW,			n4,			CtrlL)
		KeyMap(ALOOKUP,			n5,			CtrlL)
		KeyMap(ALOOKE,			n6,			CtrlL)
		KeyMap(ALOOKNW,			n7,			CtrlL)
		KeyMap(ALOOKN,	 		n8,			CtrlL)
		KeyMap(ALOOKNE,			n9,			CtrlL)

		KeyMap(ALOOKSW,			n1,			CtrlL)
		KeyMap(ALOOKS,	 		n2,			CtrlL)
		KeyMap(ALOOKSE,			n3,			CtrlL)
		KeyMap(ALOOKW,			n4,			CtrlL)
		KeyMap(ALOOKUP,			n5,			CtrlL)
		KeyMap(ALOOKE,			n6,			CtrlL)
		KeyMap(ALOOKNW,			n7,			CtrlL)
		KeyMap(ALOOKN,	 		n8,			CtrlL)
		KeyMap(ALOOKNE,			n9,			CtrlL)
//DeadCode DAW 19Jun99 #if !defined(NDEBUG)					//see comment above//DAW 19Jun99
///**/	KeyMap(DETAILDIALS,		n1,			ShiftL)
//DEAD		KeyMap(DETAILDIALS,		n1,			ShiftR)
///**/	KeyMap(DETAILPANEL,		n2,			ShiftL)
//DEAD		KeyMap(DETAILPANEL,		n2,			ShiftR)
///**/	KeyMap(DETAILSIDES,		n3,			ShiftL)
//DEAD		KeyMap(DETAILSIDES,		n3,			ShiftR)
///**/	KeyMap(DETAILCANOPY,	n4,			ShiftL)
//DEAD		KeyMap(DETAILCANOPY,	n4,			ShiftR)
///**/	KeyMap(DETAILSIGHT,		n5,			ShiftL)
//DEAD		KeyMap(DETAILSIGHT,		n5,			ShiftR)
//DeadCode DAW 19Jun99 #endif
//		KeyMap(GUNRANGEUP,		n6,			ShiftL)
//		KeyMap(GUNRANGEUP,		n6,			ShiftR)
//		KeyMap(GUNRANGEDOWN,	n7,			ShiftL)
//		KeyMap(GUNRANGEDOWN,	n7,			ShiftR)
//DEADCODE RDH 16/04/99 		KeyMap(RESTARTENGINE,	n9,			ShiftL)
//DEADCODE RDH 16/04/99 		KeyMap(RESTARTENGINE,	n9,			ShiftR)

		KeyMap(RPMTOGGLE,		n0,			ShiftL)
		KeyMap(RPMTOGGLE,		n0,			ShiftR)

//------------------------------------------------------------------------------
//letters

		KeyAll(ANYBANDITS,				a)							  //RDH 10/05/99
		KeyMap(SPEEDBRAKE,			b,			norm)
		KeyMap(CLEAR,			c,			norm)					  //RDH 10/05/99
		KeyMap(SHAPECHEATTOG,		c,			CtrlL)
		KeyMap(SHAPECHEATTOG,		c,			CtrlR)
		KeyMap(DETAILUP,			d,			CtrlL)
		KeyMap(DETAILUP,			d,			CtrlR)
//DEADCODE RDH 16/04/99 		KeyMap(MAGICK2,				d,			AltL)
		KeyMap(DETAILDN,		 	d,			ShiftL)
		KeyMap(DETAILDN,		 	d,			ShiftR)
		KeyMap(BOXTARGET,		 	d,			norm)			//RJS 05Nov98 //RDH 16/04/99
		KeyMap(RESTARTENGINE,		e,			norm)
		KeyMap(EJECTPILOT,			e,			CtrlL)
		KeyMap(EJECTPILOT,			e,			CtrlR)
		KeyMap(FLAPSUPDOWN,			f,			norm)
		KeyMap(NEWFLAPSMID,			f,			ShiftL)	//CSB 24/08/99	
		KeyMap(NEWFLAPSMID,			f,			ShiftR)	//CSB 24/08/99	
//DEADCODE RDH 16/04/99 		KeyMap(FRAMERATEKEY,		f,			ShiftL)
//DEADCODE RDH 16/04/99 		KeyMap(FRAMERATEKEY,		f,			ShiftR)
//DEADCODE RDH 16/04/99 		KeyMap(FUELTOGGLE,			f,			AltL)
//DEADCODE RDH 16/04/99 		KeyMap(FUELTOGGLE,			f,			AltGR)
		KeyMap(DUMPFUEL,			f,			CtrlL)
		KeyMap(DUMPFUEL,			f,			CtrlR)
		KeyMap(GEARUPDOWN,			g,			norm)
//		KeyMap(GOHOME,				h,			norm)
		KeyMap(HUDTOGGLE,				h,			norm)
		KeyMap(INFOPANEL,			i,			norm)
//DeadCode CSB 13/01/99			KeyMap(LEFTWHEELBRAKE,		j,			norm)	//j key available
		KeyMap(RESURRECTKEY,		j,			norm)
//DeadCode RDH 19Apr99 		KeyMap(KEY_JOYSTICKCONFIG,	j,			AltL)
//DeadCode RDH 19Apr99 		KeyMap(KEY_JOYSTICKCONFIG,	j,			AltGR)
		KeyMap(SENS_UP,				k,			norm)
		KeyMap(SENS_DOWN,			k,			ShiftL)
		KeyMap(SENS_DOWN,			k,			ShiftR)
//DEADCODE RDH 16/04/99 		KeyMap(MAGICK1,				l,			AltL)
		KeyMap(ELEVTRIMAFT,			l,			norm)
		KeyMap(ELEVTRIMNEU,			l,			ShiftL)
		KeyMap(ELEVTRIMNEU,			l,			ShiftR)
//DEADCODE RDH 16/04/99 		KeyMap(ENEMYVIEW,			l,			CtrlL)
//DEADCODE RDH 16/04/99 		KeyMap(ENEMYVIEW,			l,			CtrlR)
		KeyMap(GOTOMAPKEY,			m,			norm)
		KeyMap(SEEMIGS,			m,			CtrlL)
		KeyMap(SEEMIGS,			m,			CtrlR)
		KeyMap(TOGGLEMESSAGES,	m,			ShiftL)
		KeyMap(TOGGLEMESSAGES,	m,			ShiftR)
		KeyMap(CYCLETHROUGHWEAPONS,			n,			norm)
//DeadCode CSB 13/01/99			KeyMap(RIGHTWHEELBRAKE,		n,			norm)	//n key available
		KeyMap(ELEVTRIMFWD,			o,			norm)
		KeyAll(PAUSEKEY,			p)
		KeyMap(SCREENSHOT,			p,			CtrlL)
		KeyMap(SCREENSHOT,			p,			CtrlR)
//TempCode ARM 29Jul97 		KeyMap(PROPLOWPITCH,p,CtrlL)							//ARM 24Jul97
//TempCode ARM 29Jul97 		KeyMap(PROPHIGHPITCH,p,CtrlR)							//ARM 24Jul97
//TempCode ARM 29Jul97 		KeyMap(PROPFEATHER,p,AltL)								//ARM 24Jul97
		KeyMap(WINGSPANUP,			q,			norm)
		KeyMap(DROPBOMB,			q,			AltL)
		KeyMap(RADIOCOMMS,			r,			norm)
		KeyMap(NEWFLAPSUP,			r,			ShiftL)	//CSB 24/08/99	
		KeyMap(NEWFLAPSUP,			r,			ShiftR)	//CSB 24/08/99	
//DEADCODE RDH 24/03/99 		KeyMap(RESTARTENGINE,		r,			norm)
		KeyMap(RELOADWEAPON,		r,			CtrlL)				  //RDH 16/04/99
		KeyMap(RELOADWEAPON,		r,			CtrlR)				  //RDH 16/04/99
		KeyMap(SUICIDE,				s,			norm)
		KeyMap(SPINRECOVERY,		s,			ShiftL)
		KeyMap(GUNRANGEDOWN,		t,			norm)

		KeyAll(CHEATLIFTKEY,		u)
//use v for video toggle
		KeyMap(RECORDTOGGLE,		v,			norm)
		KeyMap(NEWFLAPSDOWN,		v,			ShiftL)	//CSB 24/08/99	
		KeyMap(NEWFLAPSDOWN,		v,			ShiftR)	//CSB 24/08/99	
		KeyMap(VOICETOGGLE,			v,			CtrlL)
		KeyMap(VOICETOGGLE,			v,			CtrlR)
		KeyMap(WINGSPANDOWN,		w,			norm)
//DEADCODE RDH 16/04/99 		KeyMap(WINGSPANUP,			w,			CtrlL)
//DEADCODE RDH 16/04/99 		KeyMap(WINGSPANUP,			w,			CtrlR)
		KeyMap(DUMPWEAPONS,			w,		CtrlL)					  //RDH 16/04/99
		KeyMap(DUMPWEAPONS,			w,		CtrlR)					  //RDH 16/04/99
//DEADCODE RDH 02/06/99 		KeyMap(TOGGLEWOBBLEVIEW,	w,			ShiftL)
//DEADCODE RDH 02/06/99 		KeyMap(TOGGLEWOBBLEVIEW,	w,			ShiftR)
//use x for video reset
		KeyMap(RESETRECORD,			x,			norm)
		KeyMap(EXITKEY,				x,			AltL)
//DEADCODE RDH 01/07/99 		KeyMap(ALIASDUMP,			x,			AltGR)
		KeyMap(GUNRANGEUP,			y,			norm)
		KeyMap(BREAK,			z,			norm)
//DEADCODE RDH 16/04/99 		KeyMap(OUTREVLOCKTOG,		z,			AltL)
//DEADCODE RDH 16/04/99 		KeyMap(ZOOMMAP,			 	z,			norm)			//RJS 08Sep98

//------------------------------------------------------------------------------
//miscellaneous
//From top to bottom on keyboard

		KeyMap(ACCELKEY,			tab,		norm)
		KeyMap(ACCELKEY2,			tab,		ShiftL)
		KeyMap(ACCELKEY2,			tab,		ShiftR)

		KeyMap(RPM_DOWN,			minus,		norm)
		KeyMap(APANLEFT,			minus,		AltL)
		KeyMap(APANLEFT,			minus,		AltGR)

		KeyMap(RPM_UP,				equal,		norm)
		KeyMap(APANRIGHT,			equal,		AltL)
		KeyMap(APANRIGHT,			equal,		AltGR)

		KeyMap(INOUTTOG,			backspc,	norm)

		KeyMap(LASTWEAPON,			open,		norm)
//DEADCODE RDH 16/04/99 		KeyMap(RELOADWEAPON,		open,		AltL)
//DEADCODE RDH 16/04/99 		KeyMap(RELOADWEAPON,		open,		AltGR)

		KeyMap(NEXTWEAPON,			close,		norm)
//DEADCODE RDH 16/04/99 		KeyMap(DUMPWEAPONS,			close,		CtrlL)
//DEADCODE RDH 16/04/99 		KeyMap(DUMPWEAPONS,			close,		CtrlR)


		KeyMap(PADLOCKTOG,			enter,		norm)

//DeadCode CSB 13/01/99			KeyMap(RPM_MIL,				stop,		norm)
//DeadCode CSB 13/01/99			KeyMap(RPM_MIN,				comma,		norm)
		KeyMap(LEFTWHEELBRAKE,		comma,		norm)	//CSB 13/01/99
		KeyMap(RIGHTWHEELBRAKE,		stop,		norm)	//CSB 13/01/99


		KeyMap(AB_UP,  				slash,		norm)
		KeyMap(AB_DOWN,				slash,		AltL)
		KeyMap(AB_DOWN,				slash,		AltGR)

		KeyAll(SHOOT,				space)

//------------------------------------------------------------------------------
//numberpad


		KeyMap(ROTDOWN,				movedown,		norm)
		KeyMap(ROTUP,				moveup,			norm)
		KeyMap(ROTRIGHT,			moveright,		norm)
		KeyMap(ROTLEFT,				moveleft,		norm)
		KeyMap(ROTDNLEFT,			moveend,		norm)
		KeyMap(ROTDNRIGHT,			pagedown,		norm)
		KeyMap(ROTUPLEFT,			movehome,		norm)
		KeyMap(ROTUPRIGHT,			pageup,			norm)
		KeyMap(ZOOMOUT,				numplus,		norm)
		KeyMap(ZOOMIN,				numminus,		norm)
		KeyMap(ROTRESET,			movefive, 		norm)
		KeyMap(RUDDER_LEFT,			insert,			norm)
		KeyMap(RUDDER_RIGHT,		delete,			norm)
//Dead		KeyMap(DROPBOMB,			J_enter,		norm)

		KeyMap(BIGROTDOWN,			movedown,	 	ShiftL)
		KeyMap(BIGROTUP,			moveup,		 	ShiftL)
		KeyMap(BIGROTRIGHT,			moveright,	 	ShiftL)
		KeyMap(BIGROTLEFT,			moveleft,	 	ShiftL)
		KeyMap(BIGROTDNLEFT,		moveend, 		ShiftL)
		KeyMap(BIGROTDNRIGHT,		pagedown,		ShiftL)
		KeyMap(BIGROTUPLEFT, 		movehome,		ShiftL)
		KeyMap(BIGROTUPRIGHT,		pageup,	 		ShiftL)
		KeyMap(BIGZOOMOUT,	 		numplus, 		ShiftL)
		KeyMap(BIGZOOMIN,	 		numminus,		ShiftL)
		KeyMap(ROTRESET2,			movefive,		ShiftL)

		KeyMap(BIGROTDOWN,	 		movedown,	 	ShiftR)
		KeyMap(BIGROTUP,	 		moveup,		 	ShiftR)
		KeyMap(BIGROTRIGHT,	 		moveright,	 	ShiftR)
		KeyMap(BIGROTLEFT,	 		moveleft, 	 	ShiftR)
		KeyMap(BIGROTDNLEFT, 		moveend,  		ShiftR)
		KeyMap(BIGROTDNRIGHT,		pagedown, 		ShiftR)
		KeyMap(BIGROTUPLEFT, 		movehome, 		ShiftR)
		KeyMap(BIGROTUPRIGHT,		pageup,	  		ShiftR)
		KeyMap(BIGZOOMOUT,	 		numplus,  		ShiftR)
		KeyMap(BIGZOOMIN,	 		numminus, 		ShiftR)
		KeyMap(ROTRESET2,			movefive,		ShiftR)

		KeyMap(NEXTSHAPEUP,			numplus,		CtrlL)
		KeyMap(NEXTSHAPEDN,			numminus,		CtrlL)

		KeyMap(NEXTSHAPEDN,			numminus,		CtrlR)
		KeyMap(NEXTSHAPEUP,			numplus,		CtrlR)

		KeyMap(INSTVIEW,			movefive, 		CtrlL)
		KeyMap(INSTVIEW,			movefive, 		CtrlR)
		KeyMap(INSTVIEW2,			J_enter,		norm)

//------------------------------------------------------------------------------
//arrow keys
		KeyAll(AILERON_LEFT,		J_moveleft)
		KeyAll(AILERON_RIGHT,		J_moveright)
		KeyAll(ELEVATOR_FORWARD,	J_moveup)
		KeyAll(ELEVATOR_BACK,		J_movedown)


//------------------------------------------------------------------------------
//6 key pad

		KeyMap(LOOKNE,			J_pageup,			norm)
		KeyMap(LOOKSE,			J_pagedown,			norm)
		KeyMap(LOOKS,			J_moveend,			norm)
		KeyMap(LOOKSW,			J_delete,			norm)
		KeyMap(LOOKNW,			J_insert,			norm)
		KeyMap(LOOKN,			J_movehome,			norm)

		KeyMap(LOOKE,			moveright,			AltL)
		KeyMap(LOOKW,			moveleft,			AltL)
		KeyMap(LOOKE,			moveright,			AltGR)
		KeyMap(LOOKW,			moveleft,			AltGR)


		KeyMap(LOOKUPNE,		pageup,				CtrlL)
		KeyMap(LOOKUPE,			moveright,			CtrlL)
		KeyMap(LOOKUPSE,		pagedown,		 	CtrlL)
		KeyMap(LOOKUPS,			movedown,		  	CtrlL)
		KeyMap(LOOKUPSW,		moveend,			CtrlL)
		KeyMap(LOOKUPW,			moveleft,			CtrlL)
		KeyMap(LOOKUPNW,		movehome,			CtrlL)
		KeyMap(LOOKUPN,			moveup,				CtrlL)

		KeyMap(LOOKUPNE,		pageup,				CtrlR)
		KeyMap(LOOKUPE,			moveright,			CtrlR)
		KeyMap(LOOKUPSE,		pagedown,		 	CtrlR)
		KeyMap(LOOKUPS,			movedown,		  	CtrlR)
		KeyMap(LOOKUPSW,		moveend,			CtrlR)
		KeyMap(LOOKUPW,			moveleft,			CtrlR)
		KeyMap(LOOKUPNW,		movehome,			CtrlR)
		KeyMap(LOOKUPN,			moveup,				CtrlR)

//DEAD		KeyMap(ROOKUPNE,		pageup,				CtrlR)
//DEAD		KeyMap(ROOKUPE,			moveright,			CtrlR)
//DEAD		KeyMap(ROOKUPSE,		pagedown,		 	CtrlR)
//DEAD		KeyMap(ROOKUPS,			movedown,		  	CtrlR)
//DEAD		KeyMap(ROOKUPSW,		moveend,			CtrlR)
//DEAD		KeyMap(ROOKUPW,			moveleft,			CtrlR)
//DEAD		KeyMap(ROOKUPNW,		movehome,			CtrlR)
//DEAD		KeyMap(ROOKUPN,			moveup,				CtrlR)

//------------------------------------------------------------------------------
//Joystick keys:
// First joystick
		KeyAll(SHOOT,			A1_Fire)			//Joystick key codes
		KeyAll(ROTRESET,		A1_b1)						//First 8 are reserved for buttons
		KeyAll(PADLOCKTOG,		A1_b2)
		KeyAll(INOUTTOG,		A1_b3)
		KeyAll(ELEVTRIMFWD,	A1_b4)
		KeyAll(GUNRANGEUP,		A1_b5)
		KeyAll(ELEVTRIMAFT,	A1_b6)
		KeyAll(GUNRANGEDOWN,		A1_b7)
		KeyAll(SPEEDBRAKE,		A1_b8)
		KeyAll(ELEVTRIMNEU,		A1_b9)

		KeyAll(ROTUP,		A1_hat1N)					//second 8 are reserved for first hat
		KeyAll(ROTUPRIGHT ,	A1_hat1NE)
		KeyAll(ROTRIGHT,	A1_hat1E)
		KeyAll(ROTDNRIGHT ,	A1_hat1SE)
		KeyAll(ROTDOWN,		A1_hat1S)
		KeyAll(ROTDNLEFT ,	A1_hat1SW)
		KeyAll(ROTLEFT,		A1_hat1W)
		KeyAll(ROTUPLEFT ,	A1_hat1NW)

		KeyAll(LOOKN,		A1_hat2N)					//second 8 are reserved for first hat
		KeyAll(LOOKNE ,		A1_hat2NE)
		KeyAll(LOOKE,		A1_hat2E)
		KeyAll(LOOKSE,		A1_hat2SE)
		KeyAll(LOOKS,		A1_hat2S)
		KeyAll(LOOKSW,		A1_hat2SW)
		KeyAll(LOOKW,		A1_hat2W)
		KeyAll(LOOKNW,		A1_hat2NW)

		KeyAll(GROUPINFOMSG,	A1_hat3N)					//second 8 are reserved for first hat
		KeyAll(PRECOMBATMSG,	A1_hat3NE)
		KeyAll(COMBATMSG,		A1_hat3E)
		KeyAll(POSTCOMBATMSG,	A1_hat3SE)
		KeyAll(TOWERMSG,		A1_hat3S)
		KeyAll(FACMSG,			A1_hat3SW)
		KeyAll(GOTOMAPKEY,		A1_hat3W)
		KeyAll(KEY_CONFIGMENU,	A1_hat3NW)

//First mouse:
		KeyAll(MENUSELECT,	A2_Fire)			//Joystick key codes
		KeyAll(WINGSPANDOWN,A2_b1)						//First 8 are reserved for buttons
		KeyMap(WINGSPANUP,	A2_b1,ShiftL)
		KeyAll(SUICIDE,		A2_b2)

//Third analogue input device										  //JIM 13/05/99
		KeyAll(SHOOT,			A3_Fire)			//Joystick key codes
		KeyAll(ROTRESET,		A3_b1)						//First 8 are reserved for buttons
		KeyAll(PADLOCKTOG,		A3_b2)
		KeyAll(INOUTTOG,		A3_b3)
		KeyAll(ELEVTRIMFWD,		A3_b4)
		KeyAll(GUNRANGEUP,		A3_b5)


//------------------------------------------------------------------------------
				{0,0,0}			};
//------------------------------------------------------------------------------
//	Define the physical mapping of the keys in the table ABOVE. 
//	Order is unimportant
//  3 fields:
//		1)	name of key used in game, as defined in above table
//		2)	name of raw key to be pressed
//		3)	shift key that should be pressed
//			this is one of:
//				norm	-	white key with no shift
//				extsh	-	grey direction keys and grey enter
//				AltL	-	left alt key
//				AltGR	-	right alt key
//				CtrlL	-	left control key
//				CtrlR	-	right control key
//				ShiftL	-	Left shift key
//				ShiftR	-	Right shift key
//		If you want a key to work with a number of different shifts,
//		or a number of different keys, then list it separately for each mapping.
//		If you want it for all mappings you can use KeyAll instead of KeyMap
//------------------------------------------------------------------------------
#undef	KeyMap
#undef	KeyAll
#endif
#undef	SPECIAL_KEYMAPS
#endif

