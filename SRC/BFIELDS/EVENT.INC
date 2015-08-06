//------------------------------------------------------------------------------
//Filename       event.inc
//System         
//Author         Mark 'I hate battlefields more than pain' Shaw
//Date           MS 25Aug96
//Description    Source data to generate event battlefields
//------------------------------------------------------------------------------

//*****************************************************************************
//--------------------------------
//GENERIC EVENTS	(findme)
//--------------------------------

//	Level		138,

	BattleField
	{
		FileName	BFEV_ENEMYSCOUTLOST=EVlost00.BF,
		Setval	{HeightSize,Y {Select CloudBase,-FT_3000,1}},
		Setval	{AngleStepSize,Int {Random 0,2,1}},	
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup	EnemyScoutLostGroup =	
		{
			Route	RouteLostScout =
			{
				WayPoint	EnemyScoutLostWP00=	
				{
					Posn	{Abs	{CPP},
							 Abs	{Y HeightSize},
							 Rel	{Intercept	{CPP,CWP},
									 Bearing	{Select ANGLES_30Deg,AngleStepSize,ANGLES_300Deg},
						 			 Range		VISINEDGE
							 		}
							},	
					Action	wpacnoactionno,
					Range	MARGIN
				},
				WayPoint	EnemyScoutLostWP01=	
				{
					Posn	{Abs	EnemyScoutLostWP00,
							 Rel	{Intercept	{CPP,CWP},	
						 			 Bearing	{Select ANGLES_270Deg,AngleStepSize,ANGLES_180Deg},
						 			 Range	METRES3000
									}
							},
 					Action	wpstartloopno,
					Range	MARGIN
				},
				WayPoint	EnemyScoutLostWP02=
				{
					Posn	{Abs	EnemyScoutLostWP00,
							 Rel	{Intercept	{CPP,CWP},	
						 			 Bearing	{Select ANGLES_90Deg,AngleStepSize,ANGLES_180Deg},
						 			 Range	METRES3000
									}
							},
					Action	wpstoploopchkno,
					Range	MARGIN
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyScoutHomeBase}, 
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern,
					SetUID	UID_EnemyScoutLostWp01
				}
			},
			NumInWing	1,
			NumInForm	1,
			Duty		DUTYCAP,
			Formation	SQUAD_BAIT,

			Posn	{Abs	EnemyScoutLostWP00, 
					 Rel	{Intercept	{CPP,CWP},
					   		 Bearing	{Select ANGLES_90Deg,AngleStepSize,ANGLES_180Deg},
					   		 Range	METRES200
						 	}
					},

		   	AirItem	EnemyScoutLost_Item =			     	
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				MoveCode	AUTO_FOLLOWWP,
				Skill		SKILL_REGULAR,
				Character	EnemyScoutCavalier,
				Morale		{Random	EnemyScoutMorale,40,1},
				Squadron {EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase
			}
		}
	};

//--------------------------------------------------------------------------------

	BattleField
	{
		FileName	BFEV_ENEMYSCOUTLOSTAMBUSH=EVlost01.BF,
		Setval	{HeightSize,Y {Select CloudBase,1,-FT_3000}},
		Setval	{AngleStepSize,Int {Random 0,2,1}},	
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},

		AirGroup	
		{
			Route	RouteLostScout,
			
			NumInWing	1,
			NumInForm	1,
			Duty		DUTYCAP,
			Formation	SQUAD_BAIT,

			Posn	{Abs	EnemyScoutLostWP00, 
					 Rel	{Intercept	{CPP,CWP},
					   		 Bearing	{Select ANGLES_90Deg,AngleStepSize,ANGLES_180Deg},
					   		 Range	METRES200
						 	}
					},

		   	AirItem	EnemyScoutLost_Item01 =			     	
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				MoveCode	AUTO_FOLLOWWP,
				Skill		SKILL_REGULAR,
				Character	EnemyScoutTactician,
				Morale		{Random	EnemyScoutMorale,40,1},
				Squadron {EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				Event		{Event	BFCH_LOSTSCOUTAMBUSH,
							 Setval	{EnemyScoutType00, EnemyScoutType00},
							 Setval	{EnemyScoutHomeBase, EnemyScoutHomeBase},
							 Setval	{EnemyScoutMorale, EnemyScoutMorale},
							 Setval	{EnemyScoutTactician, EnemyScoutTactician},
							 Setval	{EnemyScoutMrAverage, EnemyScoutMrAverage},
							 Setval	{EnemyScoutCavalier, EnemyScoutCavalier},
							 Setval	{EnemyScoutSquad, EnemyScoutSquad},
							 Setval	{PS_1, PS_1},
							 Setval	{PS_1, PS_2},
							 Setval	{PS_1, PS_3},
							 Setval	{PS_1, PS_4}
							}
			}
		}
	};


//-----------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_ENEMYATTACKBALLOON00=evblln00.BF,

		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup
		{
			Route	
			{
				WayPoint
				{
					Target	EnemyObjective, 
					Posn	{Abs	{Y FT_BustAlt}
							},	
					Range	ATTACKBALLOONRANGE,
					Action	wpballoonbustno
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyScoutHomeBase}, 
						 	Abs	{Y FT_4000}
							},
					Action	wpacnoactionno,
					Range	STANDARDTRIGGER
				},
				WayPoint	
				{
					Target	EnemyScoutHomeBase,
					Posn 	{Abs	{Y FT_EnterLandingPattern}},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	6,
			NumInForm	EncounterList02,
			Duty		DUTYCAP,
			Formation	FORM_V,	

			Posn		{Abs	{EnemyObjective},
						 Abs	{Y FT_BustAlt},
						 Rel	{Intercept	{EnemyObjective,CPP},
								 Bearing	{Random	ANGLES_300Deg,2,ANGLES_120Deg},
								 Range		METRES1000
								}
						},

		   	AirItem	evblln00_Item00	=
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	EnemyScoutCavalier,
				Morale		{Random	EnemyScoutMorale,40,1}
			}
		}
	};

//----------------------------------------------------------------------------

	BattleField
	{
		FileName	BFEV_ENEMYATTACKBALLOON01		=evblln01.BF,

		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},

		AirGroup
		{
			Route	
			{
				WayPoint	ENEMYATTACKBALLOON00_WP01=		
				{
					Target	EnemyObjective, 
					Posn	{Abs	{Y FT_BustAlt}
							},	
					Range	ATTACKBALLOONRANGE,
					Action	wpballoonbustno
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyObjective}, 
							 Abs	{Y FT_4000},
							 Rel	{Intercept	{EnemyObjective,EnemyScoutHomeBase},
									 Bearing	ANGLES_0Deg,
									 RangePercent	30
									}
							},
					Range	MARGIN,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyScoutHomeBase}, 
						 	Abs	{Y FT_4000}
							},
					Action	wpacnoactionno,
					Range	STANDARDTRIGGER
				},
				WayPoint	
				{
					Target	EnemyScoutHomeBase,
					Posn 	{Abs	{Y FT_EnterLandingPattern}},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	6,
			NumInForm	EncounterList03,
			Duty		DUTYCAP,
			Formation	FORM_V,	

			Posn		{Abs	{EnemyObjective},
						 Abs	{Y {Select FT_BustAlt,1,FT_1000}},
						 Rel	{Intercept	{EnemyObjective,CPP},
								 Bearing	{Random	ANGLES_300Deg,2,ANGLES_120Deg},
								 Range		METRES1000
								}
						},

		   	AirItem	evblln00_Item01	=
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1}
			}
		},

		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup	
		{
			Route	ENEMYATTACKBALLOON00_WP01,

			NumInWing	6,
			NumInForm	EncounterList02,
			Duty		DUTYCAP,
			Formation	FORM_V,	

			Posn		{Abs	evblln00_Item01},

		   	AirItem
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_ACE,SKILL_REGULAR,SKILL_VETERAN,SKILL_VETERAN,SKILL_POOR,SKILL_REGULAR},
				Morale		{Random	EnemyScoutMorale,40,1},
				Character	EnemyScoutCavalier,
				Follower	evblln00_Item01
			}
		}
	};

//-----------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_ENEMYAPPROACHBALLOON00=evblln03.BF,
		Setval	{HeightSize, Y {Random FT_BustAlt,21,100}},

		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup	
		{
			Route	
			{
//DeadCode MS 14Dec96 				WayPoint
//DeadCode MS 14Dec96 				{
//DeadCode MS 14Dec96 					Posn	{Abs	{CPP}, 
//DeadCode MS 14Dec96 							 Abs	{Y HeightSize},
//DeadCode MS 14Dec96 							 Rel	{Intercept	{CPP,EnemyScoutHomeBase},
//DeadCode MS 14Dec96 									 Bearing	{Random ANGLES_90Deg,2,ANGLES_270Deg},
//DeadCode MS 14Dec96 									 Range	HALFVISINEDGE
//DeadCode MS 14Dec96 									}
//DeadCode MS 14Dec96 							},
//DeadCode MS 14Dec96 					Range	MARGIN,
//DeadCode MS 14Dec96 					Action	wpacnoactionno
//DeadCode MS 14Dec96 				},
				WayPoint	
				{
					Posn	{Abs	{CPP}, 
							 Abs	{Y HeightSize},
							 Rel	{Intercept	{CPP,EnemyObjective},
									 Bearing	ANGLES_0Deg,
									 RangePercent	100
									}
							},
					Range	STANDARDTRIGGER,
					Action	wpacnoactionno
				},										
				WayPoint	
				{
					Target	EnemyObjective, 
					Posn	{Abs	{Y FT_BustAlt}
							},	
					Range	ATTACKBALLOONRANGE,
					Action	wpballoonbustno
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyScoutHomeBase}, 
						 	Abs	{Y FT_4000}
							},
					Action	wpacnoactionno,
					Range	STANDARDTRIGGER
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyScoutHomeBase}, 
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	6,
			NumInForm	EncounterList02,
			Formation	FORM_V,	

			Duty		DUTYCAP,

			Posn		{Abs	{CPP},
						 Abs	{Y HeightSize},
						 Rel	{Intercept	{CPP,CWP},
								 Bearing	{Random	ANGLES_330Deg,2,ANGLES_60Deg},
								 Range	VISINEDGE
								}
						},

		   	AirItem
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List {Random 3}, SKILL_VETERAN,SKILL_REGULAR,SKILL_POOR},
				Character	EnemyScoutCavalier,
				Morale		{Random	EnemyScoutMorale,40,1}
			}
		}
	};

//----------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_ENEMYAPPROACHBALLOON01=evblln04.BF,
		Setval	{HeightSize, Y {Random FT_BustAlt,21,100}},

		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},

		AirGroup	
		{
			Route
			{
//DeadCode MS 14Dec96 				WayPoint	
//DeadCode MS 14Dec96 				{
//DeadCode MS 14Dec96 					Posn	{Abs	{CPP}, 
//DeadCode MS 14Dec96 							 Abs	{Y HeightSize},
//DeadCode MS 14Dec96 							 Rel	{Intercept	{CPP,EnemyScoutHomeBase},
//DeadCode MS 14Dec96 									 Bearing	{Random ANGLES_90Deg,2,ANGLES_270Deg},
//DeadCode MS 14Dec96 									 Range	HALFVISINEDGE
//DeadCode MS 14Dec96 									}
//DeadCode MS 14Dec96 							},
//DeadCode MS 14Dec96 					Range	MARGIN,
//DeadCode MS 14Dec96 					Action	wpacnoactionno
//DeadCode MS 14Dec96 				},
				WayPoint	evblln04_WP00 =			
				{
					Posn	{Abs	{CPP}, 
							 Abs	{Y HeightSize},
							 Rel	{Intercept	{CPP,EnemyObjective},
									 Bearing	ANGLES_0Deg,
									 RangePercent	100
									}
							},
					Range	STANDARDTRIGGER,
					Action	wpacnoactionno
				},										
				WayPoint	
				{
					Target	EnemyObjective, 
					Posn	{Abs	{Y FT_BustAlt}
							},	
					Range	ATTACKBALLOONRANGE,
					Action	wpballoonbustno
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyScoutHomeBase}, 
						 	Abs	{Y FT_4000}
							},
					Action	wpacnoactionno,
					Range	STANDARDTRIGGER
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyScoutHomeBase}, 
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},

			NumInWing	6,
			NumInForm	EncounterList03,
			Duty		DUTYCAP,
			Formation	FORM_V,	

			Posn		{Abs	{CPP},
						 Abs	{Y {Select	HeightSize,1,FT_1000}},
						 Rel	{Intercept	{CPP,CWP},
								 Bearing	{Random	ANGLES_330Deg,2,ANGLES_60Deg},
								 Range	VISINEDGE
								}
						},

		   	AirItem	evblln04_Item00 =		     	
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List {Random 4}, SKILL_VETERAN,SKILL_REGULAR,SKILL_REGULAR,SKILL_POOR},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1}
			}
		},
		AirGroup	
		{
			Route	evblln04_WP00,

			NumInWing	6,
			NumInForm	EncounterList02,
			Formation	FORM_V,	

			Posn		{Abs	evblln04_Item00,
						 Abs	{Y HeightSize}
						},

		   	AirItem
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List {Random 3}, SKILL_VETERAN,SKILL_REGULAR,SKILL_POOR},
				Character	EnemyScoutCavalier,
				Morale		{Random	EnemyScoutMorale,40,1},
				Follower	evblln04_Item00	
			}
		}
	};

//-----------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_ENEMYBOMBERRETURN00			=EVbomb04.BF,
		Setval	{GlobalSkillMin, EnemyChargeSkillMin},
		Setval	{GlobalSkillMax, EnemyChargeSkillMax},
		Setval	{HeightStepSize, Int {Random 0,40,1}},
		AirGroup
		{
			Route
			{
				WayPoint
				{
					Posn	{Abs {CWP},
							 Rel {Y {Select -FT_4000,HeightStepSize,FT_100}}
							},
					Range 	HALFSTANDARDTRIGGER,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	{Abs {CWP},
							 Rel {Y {Select -FT_4000,HeightStepSize,FT_100},
								  Intercept	{CWP,EnemyChargeHomeBase},
								  Bearing	ANGLES_0Deg,
							 	  RangePercent	100
								 }
							},
					Range	STANDARDTRIGGER,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyChargeHomeBase},
						 	 Abs	{Y FT_EnterLandingPattern}
							},
					Range	DistEnterLandingPattern,
					Action	wpalandingno
				}
			},
			NumInWing	6,
			NumInForm	EncounterList02,
			Formation	FORM_FLATBOX,
			Duty		DUTYBOMB,

			Posn		{Abs	{CWP},
						 Rel	{Y {Select -FT_4000,HeightStepSize,FT_100},
								 Intercept	{CWP,CPP},
							 	 Bearing	{Random ANGLES_60Deg,240,ANGLES_1Deg},
							 	 Range		{Random VISINEDGE,VISBOUNDARYSIZE,METRES01} 
								}
						}, 

		   	AirItem
			{
				Side		NAT_ENEMY,
				Type		EnemyChargeType00,
				Home		EnemyChargeHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List {Random 3}, SKILL_VETERAN,SKILL_REGULAR,SKILL_POOR},
				Character	EnemyChargeCharacter,
				Morale		{Random	EnemyChargeMorale,40,1},
				Squadron	{EnemyChargeSquad}
			}
		}
	};

//---------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_ENEMYBOMBERRETURN01			=EVbomb05.BF,
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		Setval	{HeightStepSize, Int {Random 0,40,1}},
		AirGroup
		{
			Route
			{
				WayPoint	WPBOMBERRETURN01_A =
				{
					Posn	{Abs {CWP},
							 Rel {Y {Select -FT_4000,HeightStepSize,FT_100}}
							},
					Range 	HALFSTANDARDTRIGGER,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	{Abs {CWP},
							 Rel {Y {Select -FT_4000,HeightStepSize,FT_100},
								  Intercept	{CWP,EnemyChargeHomeBase},
								  Bearing	ANGLES_0Deg,
							 	  RangePercent	100
								 }
							},
					Range	STANDARDTRIGGER,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	{Abs {EnemyChargeHomeBase},
							 Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},

			NumInWing	6,
			NumInForm	EncounterList03,
			Duty		DUTYCAP,
			Formation	SQUAD_BAIT,

 			Posn		{Abs	{CWP},
 						 Rel	{Y {Select FT_0,HeightStepSize,FT_100},
								 Intercept	{CWP,CPP},
 							 	 Bearing	{Random ANGLES_60Deg,240,ANGLES_1Deg},
 							 	 Range		VISINEDGE
 								}
 						}, 
 
		   	AirItem	ENEMYBOMBERRETURN01_Item00 =	
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1}
			}
		},

		Setval	{GlobalSkillMin, EnemyChargeSkillMin},
		Setval	{GlobalSkillMax, EnemyChargeSkillMax},

		AirGroup
		{
			Route	WPBOMBERRETURN01_A,

			NumInWing	6,
			NumInForm	EncounterList02,
			Formation	FORM_FLATBOX,

 			Posn		{Abs	ENEMYBOMBERRETURN01_Item00,
 						 Rel	{Y -FT_4000}
 						}, 

		   	AirItem
			{
				Side		NAT_ENEMY,
				Type		EnemyChargeType00,
				Squadron	{EnemyChargeSquad},
				Home		EnemyChargeHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		EnemyChargeSkillMax,
				Character	EnemyChargeCharacter,
				Morale		EnemyChargeMorale,
				Follower	ENEMYBOMBERRETURN01_Item00	
			}
		}
	};

//-----------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_ENEMYBOMBERRETURN02			=EVbomb06.BF,
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		Setval	{HeightStepSize, Int {Random 0,40,1}},
		AirGroup
		{
			Route
			{
				WayPoint	WPBOMBERRETURN02_A =
				{
					Posn	{Abs {CWP},
							 Rel {Y {Select -FT_4000,HeightStepSize,FT_100}}
							},
					Range 	HALFSTANDARDTRIGGER,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	{Abs {CWP},
							 Rel {Y {Select -FT_4000,HeightStepSize,FT_100},
								  Intercept	{CWP,EnemyChargeHomeBase},
								  Bearing	ANGLES_0Deg,
							 	  RangePercent	100
								 }
							},
					Range	STANDARDTRIGGER,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	{Abs {EnemyChargeHomeBase},
							 Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},

			NumInWing	6,
			NumInForm	EncounterList03,
			Formation	FORM_FLATBOX,

 			Posn		{Abs	{CWP},
 						 Rel	{Y	{Select -FT_3900,HeightStepSize,FT_100},
								 Intercept	{CWP,CPP},
 							 	 Bearing	{Random ANGLES_60Deg,240,ANGLES_1Deg},
 							 	 Range		VISINEDGE
 								}
 						}, 
 
		   	AirItem	ENEMYBOMBERRETURN02_Item00 =	
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1}
			}
		},
		Setval	{GlobalSkillMin, EnemyChargeSkillMin},
		Setval	{GlobalSkillMax, EnemyChargeSkillMax},
		AirGroup
		{
			Route	WPBOMBERRETURN02_A,

			NumInWing	6,
			NumInForm	EncounterList02,
			Formation	FORM_FLATBOX,

 			Posn		{Abs	ENEMYBOMBERRETURN02_Item00,
 						 Rel	{Y	-FT_200}
						},

		   	AirItem
			{
				Side		NAT_ENEMY,
				Type		EnemyChargeType00,
				Squadron	{EnemyChargeSquad},
				Home		EnemyChargeHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		EnemyChargeSkillMax,
				Character	EnemyChargeCharacter,
				Morale		EnemyChargeMorale,
				Follower	ENEMYBOMBERRETURN02_Item00	
			}
		}
	};

//---------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_ENEMYBOMBERRETURN04=EVBomb16.BF,
		Setval	{GlobalSkillMin, EnemyChargeSkillMin},
		Setval	{GlobalSkillMax, EnemyChargeSkillMax},
		Setval	{HeightStepSize, Int {Random 0,40,1}},
		AirGroup	
		{
			Route
			{
				WayPoint
				{
					Posn	{Abs {CWP},
							 Abs {Y HeightSize}
							},
					Range 	HALFSTANDARDTRIGGER,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	{Abs {EnemyChargeHomeBase},
							 Abs {Y HeightSize}
							},
					Range	STANDARDTRIGGER,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyChargeHomeBase},
						 	 Abs	{Y FT_EnterLandingPattern}
							},
					Range	DistEnterLandingPattern,
					Action	wpalandingno
				}
			},

			NumInWing	6,
			NumInForm	EncounterList04,
			Formation	FORM_FLATBOX,

			Posn		{Abs	{CWP},
						 Abs	{Y HeightSize},
						 Rel	{Intercept	{CWP,CPP},
							 	 Bearing	{Random ANGLES_90Deg,180,ANGLES_1Deg},
							 	 Range		VISINEDGE
								}
						}, 

		   	AirItem
			{
				Side		NAT_ENEMY,
				Type		EnemyChargeType00,
				Squadron	{EnemyChargeSquad},
				Home		EnemyChargeHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_VETERAN,SKILL_REGULAR,SKILL_POOR,SKILL_REGULAR},
				Character	EnemyChargeCharacter,
				Morale		{Random	EnemyChargeMorale,40,1},
				Event		{Event	BFCH_ENEMYBOMBERRETURN04,	
							 Setval	{EnemyChargeType00, EnemyChargeType00},
							 Setval	{EnemyChargeHomeBase, EnemyChargeHomeBase},
							 Setval {EnemyChargeSkillMin, EnemyChargeSkillMin},
							 Setval {EnemyChargeSkillMax, EnemyChargeSkillMax},
							 Setval	{EnemyChargeCharacter, EnemyChargeCharacter},
							 Setval	{EnemyChargeMorale, EnemyChargeMorale}
							}
			}
		}
	};

//---------------------------------------------------------------------------
	BattleField
	{
		FileName	BFCH_ENEMYBOMBERRETURN04=CHBomb12.BF,
		Setval	{GlobalSkillMin, EnemyChargeSkillMin},
		Setval	{GlobalSkillMax, EnemyChargeSkillMax},
		AirGroup	
		{
			Route	
			{
				WayPoint
				{
					Posn	{Abs {CPP}},
					Range 	HALFSTANDARDTRIGGER,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Target	EnemyObjective,
					Posn	{Abs	{Y FT_BombAlt}},
					Action	wpbombno,
					Range	BEGINBOMBRANGE
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyChargeHomeBase},
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	6,
			NumInForm	EncounterList04,
			Formation	FORM_FLATBOX,
			Duty		DUTYBOMB,

			Posn		{Abs	{CPP},
						 Rel	{Y {Random	-FT_500,1000,FT_1},
					 	 		 Intercept	{CPP,EnemyChargeHomeBase},
								 Bearing	ANGLES_0Deg,
							 	 Range	VISINEDGE
								}
						}, 

		   	AirItem
			{
				Side		NAT_ENEMY,
				Type		EnemyChargeType00,
				Squadron	{EnemyChargeSquad},
				Home		EnemyChargeHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List {Random 3}, SKILL_VETERAN,SKILL_REGULAR,SKILL_POOR},
				Character	EnemyChargeCharacter,
				Morale		{Random	EnemyChargeMorale,40,1},
				Bombs		8
			}
		}
	};


//-----------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_ENEMYRECONNRETURN00			=EVrecy04.BF,
		Setval	{GlobalSkillMin, EnemyChargeSkillMin},
		Setval	{GlobalSkillMax, EnemyChargeSkillMax},
		Setval	{HeightStepSize, Int {Random 0,40,1}},
		AirGroup
		{
			Route
			{
				WayPoint
				{
					Posn	{Abs {CWP},
							 Rel {Y {Select -FT_4000,HeightStepSize,FT_100}}
							},
					Range 	HALFSTANDARDTRIGGER,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	{Abs {CWP},
							 Rel {Y {Select -FT_4000,HeightStepSize,FT_100},
								  Intercept	{CWP,EnemyChargeHomeBase},
								  Bearing	ANGLES_0Deg,
							 	  RangePercent	100
								 }
							},
					Range	STANDARDTRIGGER,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyChargeHomeBase},
						 	 Abs	{Y FT_EnterLandingPattern}
							},
					Range	DistEnterLandingPattern,
					Action	wpalandingno
				}
			},
			NumInWing	6,
			NumInForm	EncounterList02,
			Duty		DUTYRECONN,

			Posn		{Abs	{CWP},
						 Rel	{Y {Select -FT_4000,HeightStepSize,FT_100},
								 Intercept	{CWP,CPP},
							 	 Bearing	{Random ANGLES_60Deg,240,ANGLES_1Deg},
							 	 Range		{Random VISINEDGE,VISBOUNDARYSIZE,METRES01} 
								}
						}, 

		   	AirItem
			{
				Side		NAT_ENEMY,
				Type		EnemyChargeType00,
				Squadron	{EnemyChargeSquad},
				Home		EnemyChargeHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List {Random 3}, SKILL_VETERAN,SKILL_REGULAR,SKILL_POOR},
				Character	EnemyChargeCharacter,
				Morale		{Random	EnemyChargeMorale,40,1}
			}
		}
	};

//---------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_ENEMYRECONNRETURN01			=EVrecy05.BF,
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		Setval	{HeightStepSize, Int {Random 0,40,1}},
		AirGroup
		{
			Route
			{
				WayPoint	WPRECONNRETURN01_A =
				{
					Posn	{Abs {CWP},
							 Rel {Y {Select -FT_4000,HeightStepSize,FT_100}}
							},
					Range 	HALFSTANDARDTRIGGER,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	{Abs {CWP},
							 Rel {Y {Select -FT_4000,HeightStepSize,FT_100},
								  Intercept	{CWP,EnemyChargeHomeBase},
								  Bearing	ANGLES_0Deg,
							 	  RangePercent	100
								 }
							},
					Range	STANDARDTRIGGER,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	{Abs {EnemyChargeHomeBase},
							 Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},

			NumInWing	6,
			NumInForm	EncounterList03,
			Duty		DUTYCAP,
			Formation	SQUAD_BAIT,

 			Posn		{Abs	{CWP},
 						 Rel	{Y {Select FT_0,HeightStepSize,FT_100},
								 Intercept	{CWP,CPP},
 							 	 Bearing	{Random ANGLES_60Deg,240,ANGLES_1Deg},
 							 	 Range		VISINEDGE
 								}
 						}, 
 
		   	AirItem	ENEMYRECONNRETURN01_Item00 =	
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1}
			}
		},

		Setval	{GlobalSkillMin, EnemyChargeSkillMin},
		Setval	{GlobalSkillMax, EnemyChargeSkillMax},

		AirGroup
		{
			Route	WPRECONNRETURN01_A,

			NumInWing	6,
			NumInForm	EncounterList04,
			Duty		DUTYRECONN,	

 			Posn		{Abs	ENEMYRECONNRETURN01_Item00,
 						 Rel	{Y -FT_4000}
 						}, 

		   	AirItem
			{
				Side		NAT_ENEMY,
				Type		EnemyChargeType00,
				Squadron	{EnemyChargeSquad},
				Home		EnemyChargeHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		EnemyChargeSkillMax,
				Character	EnemyChargeCharacter,
				Morale		EnemyChargeMorale,
				Follower	ENEMYRECONNRETURN01_Item00	
			}
		}
	};

//-----------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_ENEMYRECONNRETURN02			=EVrecy06.BF,
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		Setval	{HeightStepSize, Int {Random 0,40,1}},
		AirGroup
		{
			Route
			{
				WayPoint	WPReconnRETURN02_A =
				{
					Posn	{Abs {CWP},
							 Rel {Y {Select -FT_4000,HeightStepSize,FT_100}}
							},
					Range 	HALFSTANDARDTRIGGER,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	{Abs {CWP},
							 Rel {Y {Select -FT_4000,HeightStepSize,FT_100},
								  Intercept	{CWP,EnemyChargeHomeBase},
								  Bearing	ANGLES_0Deg,
							 	  RangePercent	100
								 }
							},
					Range	STANDARDTRIGGER,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	{Abs {EnemyChargeHomeBase},
							 Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},

			NumInWing	6,
			NumInForm	EncounterList03,
			Formation	FORM_FLATBOX,

 			Posn		{Abs	{CWP},
 						 Rel	{Y	{Select -FT_3900,HeightStepSize,FT_100},
								 Intercept	{CWP,CPP},
 							 	 Bearing	{Random ANGLES_60Deg,240,ANGLES_1Deg},
 							 	 Range		VISINEDGE
 								}
 						}, 
 
		   	AirItem	ENEMYRECONNRETURN02_Item00 =	
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1}
			}
		},
		Setval	{GlobalSkillMin, EnemyChargeSkillMin},
		Setval	{GlobalSkillMax, EnemyChargeSkillMax},
		AirGroup
		{
			Route	WPReconnRETURN02_A,

			NumInWing	6,
			NumInForm	EncounterList04,
			Duty		DUTYRECONN,	

 			Posn		{Abs	ENEMYRECONNRETURN02_Item00,
 						 Rel	{Y	-FT_200}
						},

		   	AirItem
			{
				Side		NAT_ENEMY,
				Type		EnemyChargeType00,
				Squadron	{EnemyChargeSquad},
				Home		EnemyChargeHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		EnemyChargeSkillMax,
				Character	EnemyChargeCharacter,
				Morale		EnemyChargeMorale,
				Follower	ENEMYRECONNRETURN02_Item00	
			}
		}
	};

//-----------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_ENEMYRECONNACTION00			=EVrecy00.BF,
		Setval	{HeightSize, Y {Random FT_4000,20,FT_100}},

		Setval	{GlobalSkillMin, EnemyChargeSkillMin},
		Setval	{GlobalSkillMax, EnemyChargeSkillMax},

		AirGroup
		{
			Route
			{
				WayPoint
				{
					Target	EnemyObjective,
					Posn	{Abs	{Y FT_ReconAlt}},
					Action	wpreccyno,
					Range	BEGINRECONRANGE
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyChargeHomeBase},
						 	Abs	{Y HeightSize}
							},
					Action	wpacnoactionno,
					Range	STANDARDTRIGGER
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyChargeHomeBase},
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	6,
			NumInForm	EncounterList02,
			Duty		DUTYRECONN,

			Posn		{Abs	{EnemyObjective}, 
						 Abs	{Y FT_ReconAlt},
						 Rel	{Bearing	{Random	ANGLES_0Deg,24,ANGLES_15Deg},
								 Range	METRES200
								}
						},

		   	AirItem
			{
				Side		NAT_ENEMY,
				Type		EnemyChargeType00,
				Squadron	{EnemyChargeSquad},
				Home		EnemyChargeHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List {Random 3}, SKILL_VETERAN,SKILL_REGULAR,SKILL_POOR},
				Character	EnemyChargeCharacter,
				Morale		{Random	EnemyChargeMorale,40,1}
			}
		}
	};

//---------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_ENEMYRECONNACTION01			=EVrecy01.BF,
		Setval	{HeightSize, Y {Random FT_ReconAlt,20,FT_100}},

		Setval	{GlobalSkillMin, EnemyChargeSkillMin},
		Setval	{GlobalSkillMax, EnemyChargeSkillMax},

		AirGroup
		{
			Route
			{
				WayPoint	ENEMYRECONNACTION01_WP00=
				{
					Target	EnemyObjective,
					Posn	{Abs	{Y FT_ReconAlt}},
					Action	wpreccyno,
					Range	BEGINRECONRANGE
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyChargeHomeBase},
						 	Abs	{Y HeightSize}
							},
					Action	wpacnoactionno,
					Range	STANDARDTRIGGER
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyChargeHomeBase},
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	6,
			NumInForm	EncounterList03,
			Duty		DUTYRECONN,
			Formation	SQUAD_BAIT,

			Posn		{Abs	{EnemyObjective}, 
						 Abs	{Y {Select HeightSize,1,FT_4000}},
						 Rel	{Bearing	{Random	ANGLES_0Deg,24,ANGLES_15Deg},
								 Range	METRES200
								}
						},

		   	AirItem	ENEMYRECONNACTION01_ITEM00 =
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_ACE,SKILL_REGULAR,SKILL_VETERAN,SKILL_REGULAR,SKILL_POOR,SKILL_REGULAR},
				Character	EnemyChargeCharacter,
				Morale		{Random	EnemyChargeMorale,40,1}
			}
		},
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup	
		{
			Route	ENEMYRECONNACTION01_WP00,
	
			NumInWing	6,
			NumInForm	EncounterList02,
			Duty		DUTYCAP,
			Formation	SQUAD_BAIT,

			Posn		{Abs	ENEMYRECONNACTION01_ITEM00,
						 Abs	{Y HeightSize}
						},

		   	AirItem		
			{
				Side		NAT_ENEMY,
				Type		EnemyChargeType00,
				Squadron	{EnemyChargeSquad},
				Home		EnemyChargeHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List {Random 3}, SKILL_VETERAN,SKILL_REGULAR,SKILL_POOR},
				Character	EnemyChargeCharacter,
				Morale		{Random	EnemyChargeMorale,40,1},
				Follower	ENEMYRECONNACTION01_ITEM00
			}
		}
	};

//-----------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_ENEMYRECONNACTION02			=EVrecy02.BF,
		Setval	{HeightSize, Y {Random FT_ReconAlt,20,FT_100}},

		Setval	{GlobalSkillMin, EnemyChargeSkillMin},
		Setval	{GlobalSkillMax, EnemyChargeSkillMax},

		AirGroup
		{
			Route
			{
				WayPoint	ENEMYRECONNACTION02_WP00=
				{
					Target	EnemyObjective,
					Posn	{Abs	{Y FT_ReconAlt}},
					Action	wpreccyno,
					Range	BEGINRECONRANGE
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyChargeHomeBase},
						 	Abs	{Y HeightSize}
							},
					Action	wpacnoactionno,
					Range	STANDARDTRIGGER
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyChargeHomeBase},
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	6,
			NumInForm	EncounterList03,
			Duty		DUTYRECONN,

			Posn		{Abs	{EnemyObjective}, 
						 Abs	{Y {Select HeightSize,1,FT_200}},
						 Rel	{Bearing	{Random	ANGLES_0Deg,24,ANGLES_15Deg},
								 Range	METRES200
								}
						},

		   	AirItem	ENEMYRECONNACTION02_ITEM00 =
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_ACE,SKILL_REGULAR,SKILL_VETERAN,SKILL_REGULAR,SKILL_POOR,SKILL_REGULAR},
				Character	EnemyChargeCharacter,
				Morale		{Random	EnemyChargeMorale,40,1}
			}
		},
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup	
		{
			Route	ENEMYRECONNACTION02_WP00,
	
			NumInWing	6,
			NumInForm	EncounterList02,
			Duty		DUTYCAP,

			Posn		{Abs	ENEMYRECONNACTION02_ITEM00,
						 Abs	{Y HeightSize}
						},

		   	AirItem		
			{
				Side		NAT_ENEMY,
				Type		EnemyChargeType00,
				Squadron	{EnemyChargeSquad},
				Home		EnemyChargeHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List {Random 3}, SKILL_VETERAN,SKILL_REGULAR,SKILL_POOR},
				Character	EnemyChargeCharacter,
				Morale		{Random	EnemyChargeMorale,40,1},
				Follower	ENEMYRECONNACTION02_ITEM00
			}
		}
	};

//-----------------------------------------------------------------------------

	BattleField
	{
		FileName	BFEV_ENEMYRECONNACTION03			=EVrecy03.BF,
		Setval	{HeightSize, Y {Random FT_4000,20,FT_100}},
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup
		{	
			Route
			{
				WayPoint	EVrecy03_WP00 =
				{
					Target	EnemyObjective,
					Posn	{Abs	{Y FT_ReconAlt}},
					Action	wpreccyno,
					Range	BEGINRECONRANGE
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyChargeHomeBase},
						 	Abs	{Y HeightSize}
							},
					Action	wpacnoactionno,
					Range	STANDARDTRIGGER
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyChargeHomeBase},
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},

			NumInWing	6,
			NumInForm	EncounterList03,
			Duty		DUTYCAP,

			Posn		{Abs	{EnemyObjective},
						 Abs	{Y	HeightSize},
						 Rel	{Intercept	{EnemyObjective,CPP},
							 	 Bearing	{Random ANGLES_60Deg,240,ANGLES_1Deg},
							 	 Range		METRES8000
								}
						}, 

		   	AirItem	EVrecy03_Item00 =	
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_ACE,SKILL_REGULAR,SKILL_VETERAN,SKILL_REGULAR,SKILL_POOR,SKILL_REGULAR},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1}
			}
		},
		Setval	{GlobalSkillMin, EnemyChargeSkillMin},
		Setval	{GlobalSkillMax, EnemyChargeSkillMax},
		AirGroup
		{	
			Route	EVrecy03_WP00,

			NumInWing	6,
			NumInForm	EncounterList02,
			Duty		DUTYRECONN,	

			Posn		{Abs	{EnemyObjective}, 
						 Abs	{Y FT_ReconAlt},
						 Rel	{Bearing	{Random	ANGLES_0Deg,359,ANGLES_1Deg},
								 Range	METRES200
								}
						},

		   	AirItem		
			{
				Side		NAT_ENEMY,
				Type		EnemyChargeType00,
				Squadron	{EnemyChargeSquad},
				Home		EnemyChargeHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_ACE,SKILL_REGULAR,SKILL_VETERAN,SKILL_REGULAR,SKILL_POOR,SKILL_REGULAR},
				Character	EnemyChargeCharacter,
				Morale		{Random	EnemyChargeMorale,40,1},
				Follower	EVrecy03_Item00
			}
		}
	};

//-----------------------------------------------------------------------------
	BattleField
	{
		FileName	BFCH_LATERECONNESCORT01=cblate05.BF,
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup
		{
			Route		
			{
				WayPoint	
				{
					Posn	{Abs	{EnemyScoutHomeBase},
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	6,
			NumInForm	EncounterList03,
			Duty		DUTYCAP,

			Posn		{Abs	EVrecy03_Item00, 
						 Rel	{Y	{Random	FT_500,1000,FT_100},
							 	 Intercept	{CPP,EnemyScoutHomeBase},
							 	 Bearing	{Random ANGLES_330Deg,60,ANGLES_1Deg},
							 	 Range	{Random VISOUTEDGE,1000,METRES01}
								}
						}, 
		   	AirItem	
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1},
				Leader		EVrecy03_Item00
			}
		}
	};

//----------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_ENEMYRECONNAPPROACH00		=EVrecy08.BF,
		Setval	{GlobalSkillMin, EnemyChargeSkillMin},
		Setval	{GlobalSkillMax, EnemyChargeSkillMax},
		AirGroup
		{
			Route
			{
				WayPoint
				{
					Posn	{Abs {CWP},
							 Abs	{Y	HeightSize}
							},
					Range 	HALFSTANDARDTRIGGER,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	{Abs {EnemyObjective},
							 Abs	{Y	HeightSize}
							},
					Range 	STANDARDTRIGGER,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Target	EnemyObjective,
					Posn	{Abs	{Y FT_ReconAlt}},
					Action	wpreccyno,
					Range	BEGINRECONRANGE
				},
				WayPoint	
				{
					Posn	{Abs {EnemyChargeHomeBase},
							 Abs	{Y HeightSize}
							},
					Action	wpacnoactionno,
					Range	STANDARDTRIGGER
				},
				WayPoint	
				{
					Posn	{Abs {EnemyChargeHomeBase},
							 Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	6,
			NumInForm	EncounterList04,
			Duty		DUTYRECONN,	
			Formation	FORM_V,

 			Posn		{Abs	{CWP},
 						 Abs	{Y	HeightSize},
 						 Rel	{Intercept	{CWP,CPP},
 							 	 Bearing	{Random ANGLES_60Deg,240,ANGLES_1Deg},
 							 	 Range		VISINEDGE
 								}
 						}, 

		   	AirItem
			{
				Side		NAT_ENEMY,
				Type		EnemyChargeType00,
				Squadron	{EnemyChargeSquad},
				Home		EnemyChargeHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		EnemyChargeSkillMax,
				Character	EnemyChargeCharacter,
				Morale		EnemyChargeMorale
			}
		}
	};

//-----------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_ENEMYRECONNAPPROACH01		=EVrecy09.BF,
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup
		{
			Route
			{
				WayPoint	WPReconnApproach01_A =
				{
					Posn	{Abs {CWP},
							 Abs	{Y	HeightSize}
							},
					Range 	HALFSTANDARDTRIGGER,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	{Abs {EnemyObjective},
							 Abs	{Y	HeightSize}
							},
					Range 	STANDARDTRIGGER,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Target	EnemyObjective,
					Posn	{Abs	{Y FT_ReconAlt}},
					Action	wpreccyno,
					Range	BEGINRECONRANGE
				},
				WayPoint	
				{
					Posn	{Abs {EnemyChargeHomeBase},
							 Abs	{Y HeightSize}
							},
					Action	wpacnoactionno,
					Range	STANDARDTRIGGER
				},
				WayPoint	
				{
					Posn	{Abs {EnemyChargeHomeBase},
							 Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},

			NumInWing	6,
			NumInForm	EncounterList03,
			Duty		DUTYCAP,
			Formation	SQUAD_BAIT,

 			Posn		{Abs	{CWP},
 						 Abs	{Y	{Select HeightSize,1,FT_4000}},
 						 Rel	{Intercept	{CWP,CPP},
 							 	 Bearing	{Random ANGLES_60Deg,240,ANGLES_1Deg},
 							 	 Range		VISINEDGE
 								}
 						}, 
 
		   	AirItem	ENEMYRECONNAPPROACH01_Item00 =	
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1}
			}
		},

		Setval	{GlobalSkillMin, EnemyChargeSkillMin},
		Setval	{GlobalSkillMax, EnemyChargeSkillMax},

		AirGroup
		{
			Route	WPReconnApproach01_A,

			NumInWing	6,
			NumInForm	EncounterList04,
			Duty		DUTYRECONN,	
			Formation	SQUAD_BAIT,

 			Posn		{Abs	ENEMYRECONNAPPROACH01_Item00,
 						 Abs	{Y	HeightSize}
 						}, 

		   	AirItem
			{
				Side		NAT_ENEMY,
				Type		EnemyChargeType00,
				Squadron	{EnemyChargeSquad},
				Home		EnemyChargeHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		EnemyChargeSkillMax,
				Character	EnemyChargeCharacter,
				Morale		EnemyChargeMorale,
				Follower	ENEMYRECONNAPPROACH01_Item00	
			}
		}
	};

//-----------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_ENEMYRECONNAPPROACH02		=EVrecy10.BF,
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup
		{
			Route
			{
				WayPoint	WPReconnAPPROACH02_A =
				{
					Posn	{Abs {CWP},
							 Abs	{Y	HeightSize}
							},
					Range 	HALFSTANDARDTRIGGER,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	{Abs {EnemyObjective},
							 Abs	{Y	HeightSize}
							},
					Range 	STANDARDTRIGGER,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Target	EnemyObjective,
					Posn	{Abs	{Y FT_ReconAlt}},
					Action	wpreccyno,
					Range	BEGINRECONRANGE
				},
				WayPoint	
				{
					Posn	{Abs {EnemyChargeHomeBase},
							 Abs	{Y HeightSize}
							},
					Action	wpacnoactionno,
					Range	STANDARDTRIGGER
				},
				WayPoint	
				{
					Posn	{Abs {EnemyChargeHomeBase},
							 Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},

			NumInWing	6,
			NumInForm	EncounterList03,

 			Posn		{Abs	{CWP},
 						 Abs	{Y	{Select HeightSize,1,FT_200}},
 						 Rel	{Intercept	{CWP,CPP},
 							 	 Bearing	{Random ANGLES_60Deg,240,ANGLES_1Deg},
 							 	 Range		VISINEDGE
 								}
 						}, 
 
		   	AirItem	ENEMYRECONNAPPROACH02_Item00 =	
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1}
			}
		},
		Setval	{GlobalSkillMin, EnemyChargeSkillMin},
		Setval	{GlobalSkillMax, EnemyChargeSkillMax},
		AirGroup
		{
			Route	WPReconnAPPROACH02_A,

			NumInWing	6,
			NumInForm	EncounterList04,
			Duty		DUTYRECONN,	

 			Posn		{Abs	ENEMYRECONNAPPROACH02_Item00,
 						 Abs	{Y	HeightSize}
 						}, 

		   	AirItem
			{
				Side		NAT_ENEMY,
				Type		EnemyChargeType00,
				Squadron	{EnemyChargeSquad},
				Home		EnemyChargeHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		EnemyChargeSkillMax,
				Character	EnemyChargeCharacter,
				Morale		EnemyChargeMorale,
				Follower	ENEMYRECONNAPPROACH02_Item00	
			}
		}
	};

//-----------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_ENEMYRECONNAPPROACH03		=EVrecy11.BF,
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup
		{	
			Route
			{
				WayPoint	WPReconnApproach03_A =
				{
					Posn	{Abs {CWP},
							 Abs	{Y	HeightSize}
							},
					Range 	HALFSTANDARDTRIGGER,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	{Abs {EnemyObjective},
							 Abs	{Y	HeightSize}
							},
					Range 	STANDARDTRIGGER,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Target	EnemyObjective,
					Posn	{Abs	{Y FT_ReconAlt}},
					Action	wpreccyno,
					Range	BEGINRECONRANGE
				},
				WayPoint	
				{
					Posn	{Abs {EnemyChargeHomeBase},
							 Abs	{Y HeightSize}
							},
					Action	wpacnoactionno,
					Range	STANDARDTRIGGER
				},
				WayPoint	
				{
					Posn	{Abs {EnemyChargeHomeBase},
							 Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},

			NumInWing	6,
			NumInForm	EncounterList03,
			Duty		DUTYCAP,
			Formation	FORM_V,

			Posn		{Abs	{CWP},
						 Abs	{Y	HeightSize},
						 Rel	{Intercept	{CWP,CPP},
							 	 Bearing	{Random ANGLES_60Deg,240,ANGLES_1Deg},
							 	 Range		METRES8000
								}
						}, 

		   	AirItem	EVrecy11_Item00 =	
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1}
			}
		},
		Setval	{GlobalSkillMin, EnemyChargeSkillMin},
		Setval	{GlobalSkillMax, EnemyChargeSkillMax},
		AirGroup
		{	
 			Route	WPReconnApproach03_A,

			NumInWing	6,
			NumInForm	EncounterList02,
			Duty		DUTYRECONN,	


			Posn		{Abs	{CWP},
						 Abs	{Y	HeightSize},
						 Rel	{Intercept	{CWP,EVrecy11_Item00},
							 	 Bearing	ANGLES_0Deg,
							 	 Range		VISINEDGE
								}
						}, 

		   	AirItem		
			{
				Side		NAT_ENEMY,
				Type		EnemyChargeType00,
				Squadron	{EnemyChargeSquad},
				Home		EnemyChargeHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List {Random 6}, SKILL_VETERAN,SKILL_VETERAN,SKILL_REGULAR,SKILL_REGULAR,SKILL_REGULAR,SKILL_POOR},
				Character	EnemyChargeCharacter,
				Morale		{Random	EnemyChargeMorale,40,1},
				Follower	EVrecy11_Item00
			}
		}
	};

//----------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_ENEMYRECONNAPPROACH04		=EVrecy12.BF,
		Setval	{GlobalSkillMin, EnemyChargeSkillMin},
		Setval	{GlobalSkillMax, EnemyChargeSkillMax},
		AirGroup	
		{
			Route	
			{
				WayPoint
				{
					Posn	{Abs {CPP},
							 Abs	{Y	HeightSize}
							},
					Range 	HALFVISINEDGE,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Target	EnemyObjective,
					Posn	{Abs	{Y	HeightSize}},
					Range 	STANDARDTRIGGER,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Target	EnemyObjective,
					Posn	{Abs	{Y FT_ReconAlt}},
					Action	wpreccyno,
					Range	BEGINRECONRANGE
				},
				WayPoint	
				{
					Posn	{Abs {EnemyChargeHomeBase},
							 Abs	{Y HeightSize}
							},
					Action	wpacnoactionno,
					Range	STANDARDTRIGGER
				},
				WayPoint	
				{
					Posn	{Abs {EnemyChargeHomeBase},
							 Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	6,
			NumInForm	EncounterList01,

			Posn		{Abs	{CPP},
						 Abs	{Y	HeightSize},
						 Rel	{Intercept	{CPP,EnemyChargeHomeBase},
							 	 Bearing	{Random ANGLES_315Deg,90,ANGLES_1Deg},
							 	 Range		VISINEDGE
								}
						}, 

		   	AirItem
			{
				Side		NAT_ENEMY,
				Type		EnemyChargeType00,
				Squadron	{EnemyChargeSquad},
				Home		EnemyChargeHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List {Random 6}, SKILL_VETERAN,SKILL_VETERAN,SKILL_REGULAR,SKILL_REGULAR,SKILL_REGULAR,SKILL_POOR},
				Character	EnemyChargeCharacter,
				Morale		{Random	EnemyChargeMorale,40,1}
			}
		}
	};

//-----------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_ENEMYRECONNAPPROACH05		=EVrecy13.BF,
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup
		{
			Route	
			{
				WayPoint	ENEMYRECONNAPPROACH05_WP00=
				{
					Posn	{Abs {CPP},
							 Abs	{Y	HeightSize}
							},
					Range 	HALFVISINEDGE,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Target	EnemyObjective,
					Posn	{Abs	{Y	HeightSize}},
					Range 	STANDARDTRIGGER,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Target	EnemyObjective,
					Posn	{Abs	{Y FT_ReconAlt}},
					Action	wpreccyno,
					Range	BEGINRECONRANGE
				},
				WayPoint	
				{
					Posn	{Abs {EnemyChargeHomeBase},
							 Abs	{Y HeightSize}
							},
					Action	wpacnoactionno,
					Range	STANDARDTRIGGER
				},
				WayPoint	
				{
					Posn	{Abs {EnemyChargeHomeBase},
							 Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},

			NumInWing	6,
			NumInForm	EncounterList03,
			Duty		DUTYCAP,

			Posn		{Abs	{CPP},
						 Abs	{Y	{Select HeightSize,1,FT_200}},
						 Rel	{Intercept	{CPP,EnemyChargeHomeBase},
							 	 Bearing	{Random ANGLES_315Deg,90,ANGLES_1Deg},
							 	 Range		VISINEDGE
								}
						}, 

		   	AirItem	ENEMYRECONNAPPROACH05_Item00 =	
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1}
			}
		},
		Setval	{GlobalSkillMin, EnemyChargeSkillMin},
		Setval	{GlobalSkillMax, EnemyChargeSkillMax},
		AirGroup
		{
			Route	ENEMYRECONNAPPROACH05_WP00,

			NumInWing	6,
			NumInForm	EncounterList04,
			Duty		DUTYRECONN,	

 			Posn		{Abs	ENEMYRECONNAPPROACH05_Item00,
 						 Abs	{Y	HeightSize}
 						}, 

		   	AirItem
			{
				Side		NAT_ENEMY,
				Type		EnemyChargeType00,
				Squadron	{EnemyChargeSquad},
				Home		EnemyChargeHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		EnemyChargeSkillMax,
				Character	EnemyChargeCharacter,
				Morale		EnemyChargeMorale,
				Follower	ENEMYRECONNAPPROACH05_Item00	
			}
		}
	};


//-----------------------------------------------------------------------------
//REDUNDANT
//DeadCode MS 03Oct96 
//DeadCode MS 03Oct96 	BattleField
//DeadCode MS 03Oct96 	{
//DeadCode MS 03Oct96 		FileName	BFCH_LATERECONNESCORT00=cblate04.BF
//DeadCode MS 03Oct96 	};
//DeadCode MS 03Oct96 
//DeadCode MS 03Oct96 
//*
//-----------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_ENEMYSPOTTERRETURN00			=EVspot04.BF,
		Setval	{GlobalSkillMin, EnemyChargeSkillMin},
		Setval	{GlobalSkillMax, EnemyChargeSkillMax},
		Setval	{HeightStepSize, Int {Random 0,40,1}},
		AirGroup
		{
			Route
			{
				WayPoint
				{
					Posn	{Abs {CWP},
							 Rel {Y {Select -FT_4000,HeightStepSize,FT_100}}
							},
					Range 	HALFSTANDARDTRIGGER,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	{Abs {CWP},
							 Rel {Y {Select -FT_4000,HeightStepSize,FT_100},
								  Intercept	{CWP,EnemyChargeHomeBase},
								  Bearing	ANGLES_0Deg,
							 	  RangePercent	100
								 }
							},
					Range	STANDARDTRIGGER,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyChargeHomeBase},
						 	 Abs	{Y FT_EnterLandingPattern}
							},
					Range	DistEnterLandingPattern,
					Action	wpalandingno
				}
			},
			NumInWing	6,
			NumInForm	EncounterList01,
			Duty		DUTYSPOT,

			Posn		{Abs	{CWP},
						 Rel	{Y {Select -FT_4000,HeightStepSize,FT_100},
								 Intercept	{CWP,CPP},
							 	 Bearing	{Random ANGLES_60Deg,240,ANGLES_1Deg},
							 	 Range		{Random VISINEDGE,VISBOUNDARYSIZE,METRES01} 
								}
						}, 

		   	AirItem
			{
				Side		NAT_ENEMY,
				Type		EnemyChargeType00,
				Squadron	{EnemyChargeSquad},
				Home		EnemyChargeHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List {Random 6}, SKILL_VETERAN,SKILL_VETERAN,SKILL_REGULAR,SKILL_REGULAR,SKILL_REGULAR,SKILL_POOR},
				Character	EnemyChargeCharacter,
				Morale		{Random	EnemyChargeMorale,40,1}
			}
		}
	};

//---------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_ENEMYSPOTTERRETURN01			=EVspot05.BF,
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		Setval	{HeightStepSize, Int {Random 0,40,1}},
		AirGroup
		{
			Route
			{
				WayPoint	WPSPOTTERRETURN01_A =
				{
					Posn	{Abs {CWP},
							 Rel {Y {Select -FT_4000,HeightStepSize,FT_100}}
							},
					Range 	HALFSTANDARDTRIGGER,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	{Abs {CWP},
							 Rel {Y {Select -FT_4000,HeightStepSize,FT_100},
								  Intercept	{CWP,EnemyChargeHomeBase},
								  Bearing	ANGLES_0Deg,
							 	  RangePercent	100
								 }
							},
					Range	STANDARDTRIGGER,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	{Abs {EnemyChargeHomeBase},
							 Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},

			NumInWing	6,
			NumInForm	EncounterList03,
			Duty		DUTYCAP,
			Formation	SQUAD_BAIT,

 			Posn		{Abs	{CWP},
 						 Rel	{Y {Select FT_0,HeightStepSize,FT_100},
								 Intercept	{CWP,CPP},
 							 	 Bearing	{Random ANGLES_60Deg,240,ANGLES_1Deg},
 							 	 Range		VISINEDGE
 								}
 						}, 
 
		   	AirItem	ENEMYSPOTTERRETURN01_Item00 =	
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1}
			}
		},

		Setval	{GlobalSkillMin, EnemyChargeSkillMin},
		Setval	{GlobalSkillMax, EnemyChargeSkillMax},

		AirGroup
		{
			Route	WPSPOTTERRETURN01_A,

			NumInWing	6,
			NumInForm	EncounterList01,
			Formation	SQUAD_BAIT,

 			Posn		{Abs	ENEMYSPOTTERRETURN01_Item00,
 						 Rel	{Y -FT_4000}
 						}, 

		   	AirItem
			{
				Side		NAT_ENEMY,
				Type		EnemyChargeType00,
				Squadron	{EnemyChargeSquad},
				Home		EnemyChargeHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		EnemyChargeSkillMax,
				Character	EnemyChargeCharacter,
				Morale		EnemyChargeMorale,
				Follower	ENEMYSPOTTERRETURN01_Item00	
			}
		}
	};

//-----------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_ENEMYSPOTTERRETURN02			=EVspot06.BF,
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		Setval	{HeightStepSize, Int {Random 0,40,1}},
		AirGroup
		{
			Route
			{
				WayPoint	WPSPOTTERRETURN02_A =
				{
					Posn	{Abs {CWP},
							 Rel {Y {Select -FT_4000,HeightStepSize,FT_100}}
							},
					Range 	HALFSTANDARDTRIGGER,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	{Abs {CWP},
							 Rel {Y {Select -FT_4000,HeightStepSize,FT_100},
								  Intercept	{CWP,EnemyChargeHomeBase},
								  Bearing	ANGLES_0Deg,
							 	  RangePercent	100
								 }
							},
					Range	STANDARDTRIGGER,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	{Abs {EnemyChargeHomeBase},
							 Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},

			NumInWing	6,
			NumInForm	EncounterList03,

 			Posn		{Abs	{CWP},
 						 Rel	{Y	{Select -FT_3900,HeightStepSize,FT_100},
								 Intercept	{CWP,CPP},
 							 	 Bearing	{Random ANGLES_60Deg,240,ANGLES_1Deg},
 							 	 Range		VISINEDGE
 								}
 						}, 
 
		   	AirItem	ENEMYSPOTTERRETURN02_Item00 =	
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1}
			}
		},
		Setval	{GlobalSkillMin, EnemyChargeSkillMin},
		Setval	{GlobalSkillMax, EnemyChargeSkillMax},
		AirGroup
		{
			Route	WPSPOTTERRETURN02_A,

			NumInWing	6,
			NumInForm	EncounterList01,

 			Posn		{Abs	ENEMYSPOTTERRETURN02_Item00,
 						 Rel	{Y	-FT_200}
						},

		   	AirItem
			{
				Side		NAT_ENEMY,
				Type		EnemyChargeType00,
				Squadron	{EnemyChargeSquad},
				Home		EnemyChargeHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		EnemyChargeSkillMax,
				Character	EnemyChargeCharacter,
				Morale		EnemyChargeMorale,
				Follower	ENEMYSPOTTERRETURN02_Item00	
			}
		}
	};

//-----------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_ENEMYSPOTTERACTION00			=EVspot00.BF,
		Setval	{HeightSize, Y {Random FT_4000,20,FT_100}},

		Setval	{GlobalSkillMin, EnemyChargeSkillMin},
		Setval	{GlobalSkillMax, EnemyChargeSkillMax},
		AirGroup
		{
			Route
			{
				WayPoint
				{
					Target	EnemyObjective,
					Posn	{Abs	{Y FT_SpotAlt}},
					Action	wpartspotno,
					Range	BEGINSPOTRANGE
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyChargeHomeBase},
						 	Abs	{Y HeightSize}
							},
					Action	wpacnoactionno,
					Range	STANDARDTRIGGER
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyChargeHomeBase},
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	6,
			NumInForm	EncounterList01,
			Duty		DUTYSPOT,

			Posn		{Abs	{EnemyObjective}, 
						 Abs	{Y FT_SpotAlt},
						 Rel	{Bearing	{Random	ANGLES_0Deg,24,ANGLES_15Deg},
								 Range	METRES200
							}
						},

		   	AirItem	
			{
				Side		NAT_ENEMY,
				Type		EnemyChargeType00,
				Squadron	{EnemyChargeSquad},
				Home		EnemyChargeHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List {Random 6}, SKILL_VETERAN,SKILL_VETERAN,SKILL_REGULAR,SKILL_REGULAR,SKILL_REGULAR,SKILL_POOR},
				Character	EnemyChargeCharacter,
				Morale		{Random	EnemyChargeMorale,40,1}
			}
		}
	};

//---------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_ENEMYSPOTTERACTION01			=EVspot01.BF,
		Setval	{HeightSize, Y {Random FT_SpotAlt,20,FT_100}},

		Setval	{GlobalSkillMin, EnemyChargeSkillMin},
		Setval	{GlobalSkillMax, EnemyChargeSkillMax},

		AirGroup
		{
			Route
			{
				WayPoint	ENEMYSPOTTERACTION01_WP00=
				{
					Target	EnemyObjective,
					Posn	{Abs	{Y FT_SpotAlt}},
					Action	wpartspotno,
					Range	BEGINSPOTRANGE
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyChargeHomeBase},
						 	Abs	{Y HeightSize}
							},
					Action	wpacnoactionno,
					Range	STANDARDTRIGGER
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyChargeHomeBase},
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	6,
			NumInForm	EncounterList03,
			Formation	SQUAD_BAIT,

			Posn		{Abs	{EnemyObjective}, 
						 Abs	{Y {Select HeightSize,1,FT_4000}},
						 Rel	{Bearing	{Random	ANGLES_0Deg,24,ANGLES_15Deg},
								 Range	METRES200
								}
						},

		   	AirItem	ENEMYSPOTTERACTION01_ITEM00 =
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_ACE,SKILL_REGULAR,SKILL_VETERAN,SKILL_REGULAR,SKILL_POOR,SKILL_REGULAR},
				Character	EnemyChargeCharacter,
				Morale		{Random	EnemyChargeMorale,40,1}
			}
		},
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup	
		{
			Route	ENEMYSPOTTERACTION01_WP00,
	
			NumInWing	6,
			NumInForm	EncounterList01,
			Duty		DUTYCAP,
			Formation	SQUAD_BAIT,

			Posn		{Abs	ENEMYSPOTTERACTION01_ITEM00,
						 Abs	{Y HeightSize}
						},

		   	AirItem		
			{
				Side		NAT_ENEMY,
				Type		EnemyChargeType00,
				Squadron	{EnemyChargeSquad},
				Home		EnemyChargeHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List {Random 3}, SKILL_VETERAN,SKILL_REGULAR,SKILL_POOR},
				Character	EnemyChargeCharacter,
				Morale		{Random	EnemyChargeMorale,40,1},
				Follower	ENEMYSPOTTERACTION01_ITEM00
			}
		}
	};

//-----------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_ENEMYSPOTTERACTION02			=EVspot02.BF,
		Setval	{HeightSize, Y {Random FT_SpotAlt,20,FT_100}},

		Setval	{GlobalSkillMin, EnemyChargeSkillMin},
		Setval	{GlobalSkillMax, EnemyChargeSkillMax},

		AirGroup
		{
			Route
			{
				WayPoint	ENEMYSPOTTERACTION02_WP00=
				{
					Target	EnemyObjective,
					Posn	{Abs	{Y FT_SpotAlt}},
					Action	wpartspotno,
					Range	BEGINSPOTRANGE
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyChargeHomeBase},
						 	Abs	{Y HeightSize}
							},
					Action	wpacnoactionno,
					Range	STANDARDTRIGGER
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyChargeHomeBase},
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	6,
			NumInForm	EncounterList03,

			Posn		{Abs	{EnemyObjective}, 
						 Abs	{Y {Select HeightSize,1,FT_200}},
						 Rel	{Bearing	{Random	ANGLES_0Deg,24,ANGLES_15Deg},
								 Range	METRES200
								}
						},

		   	AirItem	ENEMYSPOTTERACTION02_ITEM00 =
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_ACE,SKILL_REGULAR,SKILL_VETERAN,SKILL_REGULAR,SKILL_POOR,SKILL_REGULAR},
				Character	EnemyChargeCharacter,
				Morale		{Random	EnemyChargeMorale,40,1}
			}
		},
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup	
		{
			Route	ENEMYSPOTTERACTION02_WP00,
	
			NumInWing	6,
			NumInForm	EncounterList01,
			Duty		DUTYCAP,

			Posn		{Abs	ENEMYSPOTTERACTION02_ITEM00,
						 Abs	{Y HeightSize}
						},

		   	AirItem		
			{
				Side		NAT_ENEMY,
				Type		EnemyChargeType00,
				Squadron	{EnemyChargeSquad},
				Home		EnemyChargeHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List {Random 3}, SKILL_VETERAN,SKILL_REGULAR,SKILL_POOR},
				Character	EnemyChargeCharacter,
				Morale		{Random	EnemyChargeMorale,40,1},
				Follower	ENEMYSPOTTERACTION02_ITEM00
			}
		}
	};

//-----------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_ENEMYSPOTTERACTION03			=EVspot03.BF,
		Setval	{HeightSize, Y {Random FT_4000,20,FT_100}},
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup
		{	
			Route
			{
				WayPoint	EVspot03_WP00 =
				{
					Target	EnemyObjective,
					Posn	{Abs	{Y FT_SpotAlt}},
					Action	wpartspotno,
					Range	BEGINSPOTRANGE
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyChargeHomeBase},
						 	Abs	{Y HeightSize}
							},
					Action	wpacnoactionno,
					Range	STANDARDTRIGGER
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyChargeHomeBase},
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},

			NumInWing	6,
			NumInForm	EncounterList03,
			Duty		DUTYCAP,

			Posn		{Abs	{EnemyObjective},
						 Abs	{Y	HeightSize},
						 Rel	{Intercept	{EnemyObjective,CPP},
							 	 Bearing	{Random ANGLES_60Deg,240,ANGLES_1Deg},
							 	 Range		METRES8000
								}
						}, 

		   	AirItem	EVspot03_Item00 =	
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_ACE,SKILL_REGULAR,SKILL_VETERAN,SKILL_REGULAR,SKILL_POOR,SKILL_REGULAR},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1}
			}
		},
		Setval	{GlobalSkillMin, EnemyChargeSkillMin},
		Setval	{GlobalSkillMax, EnemyChargeSkillMax},
		AirGroup
		{	
			Route	EVspot03_WP00,

			NumInWing	6,
			NumInForm	EncounterList01,

			Posn		{Abs	{EnemyObjective}, 
						 Abs	{Y FT_SpotAlt},
						 Rel	{Bearing	{Random	ANGLES_0Deg,359,ANGLES_1Deg},
								 Range	METRES200
								}
						},

		   	AirItem		
			{
				Side		NAT_ENEMY,
				Type		EnemyChargeType00,
				Squadron	{EnemyChargeSquad},
				Home		EnemyChargeHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_ACE,SKILL_REGULAR,SKILL_VETERAN,SKILL_REGULAR,SKILL_POOR,SKILL_REGULAR},
				Character	EnemyChargeCharacter,
				Morale		{Random	EnemyChargeMorale,40,1},
				Follower	EVspot03_Item00
			}
		}
	};

//-----------------------------------------------------------------------------
//Redundant
//DeadCode MS 03Oct96 	BattleField
//DeadCode MS 03Oct96 	{
//DeadCode MS 03Oct96 		FileName	BFCH_LATESPOTESCORT01=cblate07.BF
//DeadCode MS 03Oct96 	};

//----------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_ENEMYSPOTTERAPPROACH00		=EVspot08.BF,
		Setval	{GlobalSkillMin, EnemyChargeSkillMin},
		Setval	{GlobalSkillMax, EnemyChargeSkillMax},
		AirGroup
		{
			Route
			{
				WayPoint
				{
					Posn	{Abs {CWP},
							 Abs	{Y	HeightSize}
							},
					Range 	HALFSTANDARDTRIGGER,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Target	EnemyObjective,
					Posn	{Abs	{Y	HeightSize}},
					Range 	STANDARDTRIGGER,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Target	EnemyObjective,
					Posn	{Abs	{Y FT_SpotAlt}},
					Action	wpartspotno,
					Range	BEGINSPOTRANGE
				},
				WayPoint	
				{
					Posn	{Abs {EnemyChargeHomeBase},
							 Abs	{Y HeightSize}
							},
					Action	wpacnoactionno,
					Range	STANDARDTRIGGER
				},
				WayPoint	
				{
					Posn	{Abs {EnemyChargeHomeBase},
							 Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	6,
			NumInForm	EncounterList01,
			Duty		DUTYSPOT,	

			Posn		{Abs	{CWP},
						 Abs	{Y	HeightSize},
						 Rel	{Intercept	{CWP,CPP},
							 	 Bearing	{Random ANGLES_60Deg,240,ANGLES_1Deg},
							 	 Range		VISINEDGE
								}
						}, 

		   	AirItem
			{
				Side		NAT_ENEMY,
				Type		EnemyChargeType00,
				Squadron	{EnemyChargeSquad},
				Home		EnemyChargeHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List {Random 6}, SKILL_VETERAN,SKILL_VETERAN,SKILL_REGULAR,SKILL_REGULAR,SKILL_REGULAR,SKILL_POOR},
				Character	EnemyChargeCharacter,
				Morale		{Random	EnemyChargeMorale,40,1}
			}
		}
	};

//-----------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_ENEMYSPOTTERAPPROACH01		=EVspot09.BF,
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup
		{
			Route
			{
				WayPoint	WPSPOTTERApproach01_A =
				{
					Posn	{Abs {CWP},
							 Abs	{Y	HeightSize}
							},
					Range 	HALFSTANDARDTRIGGER,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	{Abs {EnemyObjective},
							 Abs	{Y	HeightSize}
							},
					Range 	STANDARDTRIGGER,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Target	EnemyObjective,
					Posn	{Abs	{Y FT_SpotAlt}},
					Action	wpartspotno,
					Range	BEGINSPOTRANGE
				},
				WayPoint	
				{
					Posn	{Abs {EnemyChargeHomeBase},
							 Abs	{Y HeightSize}
							},
					Action	wpacnoactionno,
					Range	STANDARDTRIGGER
				},
				WayPoint	
				{
					Posn	{Abs {EnemyChargeHomeBase},
							 Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},

			NumInWing	6,
			NumInForm	EncounterList03,
			Duty		DUTYCAP,
			Formation	SQUAD_BAIT,

 			Posn		{Abs	{CWP},
 						 Abs	{Y	{Select HeightSize,1,FT_4000}},
 						 Rel	{Intercept	{CWP,CPP},
 							 	 Bearing	{Random ANGLES_60Deg,240,ANGLES_1Deg},
 							 	 Range		VISINEDGE
 								}
 						}, 
 
		   	AirItem	ENEMYSPOTTERAPPROACH01_Item00 =	
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1}
			}
		},

		Setval	{GlobalSkillMin, EnemyChargeSkillMin},
		Setval	{GlobalSkillMax, EnemyChargeSkillMax},

		AirGroup
		{
			Route	WPSPOTTERApproach01_A,

			NumInWing	6,
			NumInForm	EncounterList01,
			Formation	SQUAD_BAIT,

 			Posn		{Abs	ENEMYSPOTTERAPPROACH01_Item00,
 						 Abs	{Y	HeightSize}
 						}, 

		   	AirItem
			{
				Side		NAT_ENEMY,
				Type		EnemyChargeType00,
				Squadron	{EnemyChargeSquad},
				Home		EnemyChargeHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		EnemyChargeSkillMax,
				Character	EnemyChargeCharacter,
				Morale		EnemyChargeMorale,
				Follower	ENEMYSPOTTERAPPROACH01_Item00	
			}
		}
	};

//-----------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_ENEMYSPOTTERAPPROACH02		=EVspot10.BF,
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup
		{
			Route
			{
				WayPoint	WPSPOTTERAPPROACH02_A =
				{
					Posn	{Abs {CWP},
							 Abs	{Y	HeightSize}
							},
					Range 	HALFSTANDARDTRIGGER,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	{Abs {EnemyObjective},
							 Abs	{Y	HeightSize}
							},
					Range 	STANDARDTRIGGER,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Target	EnemyObjective,
					Posn	{Abs	{Y FT_SpotAlt}},
					Action	wpartspotno,
					Range	BEGINSPOTRANGE
				},
				WayPoint	
				{
					Posn	{Abs {EnemyChargeHomeBase},
							 Abs	{Y HeightSize}
							},
					Action	wpacnoactionno,
					Range	STANDARDTRIGGER
				},
				WayPoint	
				{
					Posn	{Abs {EnemyChargeHomeBase},
							 Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},

			NumInWing	6,
			NumInForm	EncounterList03,

 			Posn		{Abs	{CWP},
 						 Abs	{Y	{Select HeightSize,1,FT_200}},
 						 Rel	{Intercept	{CWP,CPP},
 							 	 Bearing	{Random ANGLES_60Deg,240,ANGLES_1Deg},
 							 	 Range		VISINEDGE
 								}
 						}, 
 
		   	AirItem	ENEMYSPOTTERAPPROACH02_Item00 =	
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1}
			}
		},
		Setval	{GlobalSkillMin, EnemyChargeSkillMin},
		Setval	{GlobalSkillMax, EnemyChargeSkillMax},
		AirGroup
		{
			Route	WPSPOTTERAPPROACH02_A,

			NumInWing	6,
			NumInForm	EncounterList01,

 			Posn		{Abs	ENEMYSPOTTERAPPROACH02_Item00,
 						 Abs	{Y	HeightSize}
 						}, 

		   	AirItem
			{
				Side		NAT_ENEMY,
				Type		EnemyChargeType00,
				Squadron	{EnemyChargeSquad},
				Home		EnemyChargeHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		EnemyChargeSkillMax,
				Character	EnemyChargeCharacter,
				Morale		EnemyChargeMorale,
				Follower	ENEMYSPOTTERAPPROACH02_Item00	
			}
		}
	};

//-----------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_ENEMYSPOTTERAPPROACH03		=EVspot11.BF,
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup
		{	
			Route
			{
				WayPoint	WPSPOTTERApproach03_A =
				{
					Posn	{Abs {CWP},
							 Abs	{Y	HeightSize}
							},
					Range 	HALFSTANDARDTRIGGER,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	{Abs {EnemyObjective},
							 Abs	{Y	HeightSize}
							},
					Range 	STANDARDTRIGGER,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Target	EnemyObjective,
					Posn	{Abs	{Y FT_SpotAlt}},
					Action	wpartspotno,
					Range	BEGINSPOTRANGE
				},
				WayPoint	
				{
					Posn	{Abs {EnemyChargeHomeBase},
							 Abs	{Y HeightSize}
							},
					Action	wpacnoactionno,
					Range	STANDARDTRIGGER
				},
				WayPoint	
				{
					Posn	{Abs {EnemyChargeHomeBase},
							 Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},

			NumInWing	6,
			NumInForm	EncounterList03,
			Duty		DUTYCAP,
			Formation	FORM_V,

			Posn		{Abs	{CWP},
						 Abs	{Y	HeightSize},
						 Rel	{Intercept	{CWP,CPP},
							 	 Bearing	{Random ANGLES_60Deg,240,ANGLES_1Deg},
							 	 Range		METRES8000
								}
						}, 

		   	AirItem	EVspot11_Item00 =	
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1}
			}
		},
		Setval	{GlobalSkillMin, EnemyChargeSkillMin},
		Setval	{GlobalSkillMax, EnemyChargeSkillMax},
		AirGroup
		{	
 			Route	WPSPOTTERApproach03_A,

			NumInWing	6,
			NumInForm	EncounterList01,

			Posn		{Abs	{CWP},
						 Abs	{Y	HeightSize},
						 Rel	{Intercept	{CWP,EVspot11_Item00},
							 	 Bearing	ANGLES_0Deg,
							 	 Range		VISINEDGE
								}
						}, 

		   	AirItem		
			{
				Side		NAT_ENEMY,
				Type		EnemyChargeType00,
				Squadron	{EnemyChargeSquad},
				Home		EnemyChargeHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List {Random 6}, SKILL_VETERAN,SKILL_VETERAN,SKILL_REGULAR,SKILL_REGULAR,SKILL_REGULAR,SKILL_POOR},
				Character	EnemyChargeCharacter,
				Morale		{Random	EnemyChargeMorale,40,1},
				Follower	EVspot11_Item00
			}
		}
	};


//----------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_ENEMYSPOTTERAPPROACH04		=EVspot12.BF,
		Setval	{GlobalSkillMin, EnemyChargeSkillMin},
		Setval	{GlobalSkillMax, EnemyChargeSkillMax},
		AirGroup	
		{
			Route	
			{
				WayPoint
				{
					Posn	{Abs {CPP},
							 Abs	{Y	HeightSize}
							},
					Range 	HALFVISINEDGE,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Target	EnemyObjective,
					Posn	{Abs	{Y	HeightSize}},
					Range 	STANDARDTRIGGER,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Target	EnemyObjective,
					Posn	{Abs	{Y FT_SpotAlt}},
					Action	wpartspotno,
					Range	BEGINSPOTRANGE
				},
				WayPoint	
				{
					Posn	{Abs {EnemyChargeHomeBase},
							 Abs	{Y HeightSize}
							},
					Action	wpacnoactionno,
					Range	STANDARDTRIGGER
				},
				WayPoint	
				{
					Posn	{Abs {EnemyChargeHomeBase},
							 Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	6,
			NumInForm	EncounterList01,

			Posn		{Abs	{CPP},
						 Abs	{Y	HeightSize},
						 Rel	{Intercept	{CPP,EnemyChargeHomeBase},
							 	 Bearing	{Random ANGLES_315Deg,90,ANGLES_1Deg},
							 	 Range		VISINEDGE
								}
						}, 

		   	AirItem
			{
				Side		NAT_ENEMY,
				Type		EnemyChargeType00,
				Squadron	{EnemyChargeSquad},
				Home		EnemyChargeHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List {Random 6}, SKILL_VETERAN,SKILL_VETERAN,SKILL_REGULAR,SKILL_REGULAR,SKILL_REGULAR,SKILL_POOR},
				Character	EnemyChargeCharacter,
				Morale		{Random	EnemyChargeMorale,40,1}
			}
		}
	};

//-----------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_ENEMYSPOTTERAPPROACH05		=EVspot13.BF,
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup
		{
			Route	
			{
				WayPoint	ENEMYSPOTTERAPPROACH05_WP00=
				{
					Posn	{Abs {CPP},
							 Abs	{Y	HeightSize}
							},
					Range 	HALFVISINEDGE,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Target	EnemyObjective,
					Posn	{Abs	{Y	HeightSize}},
					Range 	STANDARDTRIGGER,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Target	EnemyObjective,
					Posn	{Abs	{Y FT_SpotAlt}},
					Action	wpartspotno,
					Range	BEGINSPOTRANGE
				},
				WayPoint	
				{
					Posn	{Abs {EnemyChargeHomeBase},
							 Abs	{Y HeightSize}
							},
					Action	wpacnoactionno,
					Range	STANDARDTRIGGER
				},
				WayPoint	
				{
					Posn	{Abs {EnemyChargeHomeBase},
							 Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},

			NumInWing	6,
			NumInForm	EncounterList03,
			Duty		DUTYCAP,

			Posn		{Abs	{CPP},
						 Abs	{Y	{Select HeightSize,1,FT_200}},
						 Rel	{Intercept	{CPP,EnemyChargeHomeBase},
							 	 Bearing	{Random ANGLES_315Deg,90,ANGLES_1Deg},
							 	 Range		VISINEDGE
								}
						}, 

		   	AirItem	ENEMYSPOTTERAPPROACH05_Item00 =	
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1}
			}
		},
		Setval	{GlobalSkillMin, EnemyChargeSkillMin},
		Setval	{GlobalSkillMax, EnemyChargeSkillMax},
		AirGroup
		{
			Route	ENEMYSPOTTERAPPROACH05_WP00,

			NumInWing	6,
			NumInForm	EncounterList01,

 			Posn		{Abs	ENEMYSPOTTERAPPROACH05_Item00,
 						 Abs	{Y	HeightSize}
 						}, 

		   	AirItem
			{
				Side		NAT_ENEMY,
				Type		EnemyChargeType00,
				Squadron	{EnemyChargeSquad},
				Home		EnemyChargeHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		EnemyChargeSkillMax,
				Character	EnemyChargeCharacter,
				Morale		EnemyChargeMorale,
				Follower	ENEMYSPOTTERAPPROACH05_Item00	
			}
		}
	};


//-----------------------------------------------------------------------------
//REDUNDANT
	BattleField
	{
		FileName	BFCH_LATESPOTESCORT00=cblate08.BF
	};

//-----------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_ENEMYBOMBERACTION00			=EVbomb00.BF,
		Setval	{HeightSize, Y {Random FT_4000,20,FT_100}},

		Setval	{GlobalSkillMin, EnemyChargeSkillMin},
		Setval	{GlobalSkillMax, EnemyChargeSkillMax},
		AirGroup
		{
			Route
			{
				WayPoint
				{
					Target	EnemyObjective,
					Posn	{Abs	{Y FT_BombAlt}},
 					Action	wpbombno,
					Range	BEGINBOMBRANGE
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyChargeHomeBase},
						 	Abs	{Y HeightSize}
							},
					Action	wpacnoactionno,
					Range	STANDARDTRIGGER
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyChargeHomeBase},
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	6,
			NumInForm	EncounterList02,
			Formation	FORM_FLATBOX,
			Duty		DUTYBOMB,

			Posn		{Abs	{EnemyObjective}, 
						 Abs	{Y FT_BombAlt},
						 Rel	{Bearing	{Random	ANGLES_0Deg,359,ANGLES_1Deg},
								 Range	METRES400
								}
						},

		   	AirItem
			{
				Side		NAT_ENEMY,
				Type		EnemyChargeType00,
				Squadron	{EnemyChargeSquad},
				Home		EnemyChargeHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List {Random 6}, SKILL_VETERAN,SKILL_VETERAN,SKILL_REGULAR,SKILL_REGULAR,SKILL_REGULAR,SKILL_POOR},
				Character	EnemyChargeCharacter,
				Morale		{Random	EnemyChargeMorale,40,1},
				Bombs		8
			}
		}
	};

//---------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_ENEMYBOMBERACTION01			=EVbomb01.BF,
		Setval	{HeightSize, Y {Random FT_BombAlt,20,FT_100}},

		Setval	{GlobalSkillMin, EnemyChargeSkillMin},
		Setval	{GlobalSkillMax, EnemyChargeSkillMax},

		AirGroup
		{
			Route
			{
				WayPoint	ENEMYBOMBERACTION01_WP00=
				{
					Target	EnemyObjective,
					Posn	{Abs	{Y FT_BombAlt}},
					Action	wpbombno,
					Range	BEGINBOMBRANGE
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyChargeHomeBase},
						 	Abs	{Y HeightSize}
							},
					Action	wpacnoactionno,
					Range	STANDARDTRIGGER
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyChargeHomeBase},
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	6,
			NumInForm	EncounterList03,
			Formation	SQUAD_BAIT,

			Posn		{Abs	{EnemyObjective}, 
						 Abs	{Y {Select HeightSize,1,FT_4000}},
						 Rel	{Bearing	{Random	ANGLES_0Deg,24,ANGLES_15Deg},
								 Range	METRES200
								}
						},

		   	AirItem	ENEMYBOMBERACTION01_ITEM00 =
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_ACE,SKILL_REGULAR,SKILL_VETERAN,SKILL_REGULAR,SKILL_POOR,SKILL_REGULAR},
				Character	EnemyChargeCharacter,
				Morale		{Random	EnemyChargeMorale,40,1}
			}
		},
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup	
		{
			Route	ENEMYBOMBERACTION01_WP00,
	
			NumInWing	6,
			NumInForm	EncounterList02,
			Duty		DUTYCAP,
			Formation	SQUAD_BAIT,

			Posn		{Abs	ENEMYBOMBERACTION01_ITEM00,
						 Abs	{Y HeightSize}
						},

		   	AirItem		
			{
				Side		NAT_ENEMY,
				Type		EnemyChargeType00,
				Squadron	{EnemyChargeSquad},
				Home		EnemyChargeHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List {Random 3}, SKILL_VETERAN,SKILL_REGULAR,SKILL_POOR},
				Character	EnemyChargeCharacter,
				Morale		{Random	EnemyChargeMorale,40,1},
				Follower	ENEMYBOMBERACTION01_ITEM00
			}
		}
	};

//-----------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_ENEMYBOMBERACTION02			=EVbomb02.BF,
		Setval	{HeightSize, Y {Random FT_BombAlt,20,FT_100}},

		Setval	{GlobalSkillMin, EnemyChargeSkillMin},
		Setval	{GlobalSkillMax, EnemyChargeSkillMax},

		AirGroup
		{
			Route
			{
				WayPoint	ENEMYBOMBERACTION02_WP00=
				{
					Target	EnemyObjective,
					Posn	{Abs	{Y FT_BombAlt}},
					Action	wpbombno,
					Range	BEGINBOMBRANGE
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyChargeHomeBase},
						 	Abs	{Y HeightSize}
							},
					Action	wpacnoactionno,
					Range	STANDARDTRIGGER
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyChargeHomeBase},
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	6,
			NumInForm	EncounterList03,

			Posn		{Abs	{EnemyObjective}, 
						 Abs	{Y {Select HeightSize,1,FT_200}},
						 Rel	{Bearing	{Random	ANGLES_0Deg,24,ANGLES_15Deg},
								 Range	METRES400
								}
						},

		   	AirItem	ENEMYBOMBERACTION02_ITEM00 =
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_ACE,SKILL_REGULAR,SKILL_VETERAN,SKILL_REGULAR,SKILL_POOR,SKILL_REGULAR},
				Character	EnemyChargeCharacter,
				Morale		{Random	EnemyChargeMorale,40,1}
			}
		},
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup	
		{
			Route	ENEMYBOMBERACTION02_WP00,
	
			NumInWing	6,
			NumInForm	EncounterList02,
			Duty		DUTYCAP,
			Formation	FORM_FLATBOX,

			Posn		{Abs	ENEMYBOMBERACTION02_ITEM00,
						 Abs	{Y HeightSize}
						},

		   	AirItem		
			{
				Side		NAT_ENEMY,
				Type		EnemyChargeType00,
				Squadron	{EnemyChargeSquad},
				Home		EnemyChargeHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List {Random 3}, SKILL_VETERAN,SKILL_REGULAR,SKILL_POOR},
				Character	EnemyChargeCharacter,
				Morale		{Random	EnemyChargeMorale,40,1},
				Follower	ENEMYBOMBERACTION02_ITEM00
			}
		}
	};

//-----------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_ENEMYBOMBERACTION03			=EVbomb03.BF,
		Setval	{HeightSize, Y {Random FT_4000,20,FT_100}},
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup
		{	
			Route
			{
				WayPoint	EVbomb03_WP00=	
				{
					Target	EnemyObjective,
					Posn	{Abs	{Y FT_BombAlt}},
 					Action	wpbombno,
					Range	BEGINBOMBRANGE
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyChargeHomeBase},
						 	Abs	{Y HeightSize}
							},
					Action	wpacnoactionno,
					Range	STANDARDTRIGGER
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyChargeHomeBase},
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},

			NumInWing	6,
			NumInForm	EncounterList03,
			Duty		DUTYCAP,

			Posn		{Abs	{EnemyObjective},
						 Abs	{Y	HeightSize},
						 Rel	{Intercept	{EnemyObjective,CPP},
							 	 Bearing	{Random ANGLES_60Deg,240,ANGLES_1Deg},
							 	 Range		METRES8000
								}
						}, 

		   	AirItem	EVbomb03_Item00 =	
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1},
				Bombs		8
			}
		},
		Setval	{GlobalSkillMin, EnemyChargeSkillMin},
		Setval	{GlobalSkillMax, EnemyChargeSkillMax},
		AirGroup
		{	
			Route	EVbomb03_WP00,

			NumInWing	6,
			NumInForm	EncounterList02,
			Duty		DUTYBOMB,	
			Formation	FORM_FLATBOX,

			Posn		{Abs	{EnemyObjective}, 
						 Abs	{Y FT_BombAlt},
						 Rel	{Bearing	{Random	ANGLES_0Deg,359,ANGLES_1Deg},
								 Range	METRES400
								}
						},

		   	AirItem		
			{
				Side		NAT_ENEMY,
				Type		EnemyChargeType00,
				Squadron	{EnemyChargeSquad},
				Home		EnemyChargeHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List {Random 6}, SKILL_VETERAN,SKILL_VETERAN,SKILL_REGULAR,SKILL_REGULAR,SKILL_REGULAR,SKILL_POOR},
				Character	EnemyChargeCharacter,
				Morale		{Random	EnemyChargeMorale,40,1},
				Follower	EVbomb03_Item00
			}
		}
	};	   

//-----------------------------------------------------------------------------
	BattleField
	{
		FileName	BFLATEBOMBERESCORT00=cblate01.BF,
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup
		{
			Route		
			{
				WayPoint	
				{
					Posn	{Abs	{EnemyScoutHomeBase},
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	3,
			NumInForm	EncounterList01,
			Duty		DUTYCAP,

			Posn		{Abs	EVbomb03_Item00, 
						 Rel	{Y	{Random	FT_500,1000,FT_100},
							 	 Intercept	{CPP,EnemyScoutHomeBase},
							 	 Bearing	{Random ANGLES_330Deg,60,ANGLES_1Deg},
							 	 Range	{Random VISOUTEDGE,1000,METRES01}
								}
						}, 
		   	AirItem	
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1},
				Leader		EVbomb03_Item00
			}
		}
	};

//----------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_ENEMYBOMBERAPPROACH00		=EVbomb08.BF,
		Setval	{GlobalSkillMin, EnemyChargeSkillMin},
		Setval	{GlobalSkillMax, EnemyChargeSkillMax},
		AirGroup
		{
			Route	
			{
				WayPoint
				{
					Posn	{Abs {CWP},
							 Abs	{Y	HeightSize}
							},
					Range 	HALFSTANDARDTRIGGER,
					Action	wpacnoactionno
				},
				WayPoint
				{
					Posn	{Abs {EnemyObjective},
							 Abs	{Y	HeightSize}
							},
					Range 	STANDARDTRIGGER,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Target	EnemyObjective,
					Posn	{Abs	{Y FT_BombAlt}},
					Action	wpbombno,
					Range	BEGINBOMBRANGE
				},
				WayPoint	
				{
					Posn	{Abs {EnemyChargeHomeBase},
							 Abs	{Y HeightSize}
							},
					Action	wpacnoactionno,
					Range	STANDARDTRIGGER
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyChargeHomeBase},
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	6,
			NumInForm	EncounterList02,
			Formation	FORM_FLATBOX,

			Posn		{Abs	{CWP},
						 Abs	{Y	HeightSize},
						 Rel	{Intercept	{CWP,CPP},
							 	 Bearing	{Random ANGLES_60Deg,240,ANGLES_1Deg},
							 	 Range		{Random VISINEDGE,VISBOUNDARYSIZE,METRES01} 
								}
						}, 

		   	AirItem
			{
				Side		NAT_ENEMY,
				Type		EnemyChargeType00,
				Squadron	{EnemyChargeSquad},
				Home		EnemyChargeHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List {Random 6}, SKILL_VETERAN,SKILL_VETERAN,SKILL_REGULAR,SKILL_REGULAR,SKILL_REGULAR,SKILL_POOR},
				Character	EnemyChargeCharacter,
				Morale		{Random	EnemyChargeMorale,40,1},
				Bombs		8
			}
		}
	};

//-----------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_ENEMYBOMBERAPPROACH01		=EVbomb09.BF,
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup
		{
			Route
			{
				WayPoint	WPBOMBERApproach01_A =
				{
					Posn	{Abs {CWP},
							 Abs	{Y	HeightSize}
							},
					Range 	HALFSTANDARDTRIGGER,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	{Abs {EnemyObjective},
							 Abs	{Y	HeightSize}
							},
					Range 	STANDARDTRIGGER,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Target	EnemyObjective,
					Posn	{Abs	{Y FT_BombAlt}},
					Action	wpbombno,
					Range	BEGINBOMBRANGE
				},
				WayPoint	
				{
					Posn	{Abs {EnemyChargeHomeBase},
							 Abs	{Y HeightSize}
							},
					Action	wpacnoactionno,
					Range	STANDARDTRIGGER
				},
				WayPoint	
				{
					Posn	{Abs {EnemyChargeHomeBase},
							 Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},

			NumInWing	6,
			NumInForm	EncounterList03,
			Duty		DUTYCAP,
			Formation	SQUAD_BAIT,

 			Posn		{Abs	{CWP},
 						 Abs	{Y	{Select HeightSize,1,FT_4000}},
 						 Rel	{Intercept	{CWP,CPP},
 							 	 Bearing	{Random ANGLES_60Deg,240,ANGLES_1Deg},
 							 	 Range		VISINEDGE
 								}
 						}, 
 
		   	AirItem	ENEMYBOMBERAPPROACH01_Item00 =	
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1}
			}
		},

		Setval	{GlobalSkillMin, EnemyChargeSkillMin},
		Setval	{GlobalSkillMax, EnemyChargeSkillMax},

		AirGroup
		{
			Route	WPBOMBERApproach01_A,

			NumInWing	6,
			NumInForm	EncounterList02,
			Formation	SQUAD_BAIT,

 			Posn		{Abs	ENEMYBOMBERAPPROACH01_Item00,
 						 Abs	{Y	HeightSize}
 						}, 

		   	AirItem
			{
				Side		NAT_ENEMY,
				Type		EnemyChargeType00,
				Squadron	{EnemyChargeSquad},
				Home		EnemyChargeHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		EnemyChargeSkillMax,
				Character	EnemyChargeCharacter,
				Morale		EnemyChargeMorale,
				Follower	ENEMYBOMBERAPPROACH01_Item00	
			}
		}
	};

//-----------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_ENEMYBOMBERAPPROACH02		=EVbomb10.BF,
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup
		{
			Route
			{
				WayPoint	WPBOMBERAPPROACH02_A =
				{
					Posn	{Abs {CWP},
							 Abs	{Y	HeightSize}
							},
					Range 	HALFSTANDARDTRIGGER,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	{Abs {EnemyObjective},
							 Abs	{Y	HeightSize}
							},
					Range 	STANDARDTRIGGER,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Target	EnemyObjective,
					Posn	{Abs	{Y FT_BombAlt}},
					Action	wpbombno,
					Range	BEGINBOMBRANGE
				},
				WayPoint	
				{
					Posn	{Abs {EnemyChargeHomeBase},
							 Abs	{Y HeightSize}
							},
					Action	wpacnoactionno,
					Range	STANDARDTRIGGER
				},
				WayPoint	
				{
					Posn	{Abs {EnemyChargeHomeBase},
							 Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},

			NumInWing	6,
			NumInForm	EncounterList03,

 			Posn		{Abs	{CWP},
 						 Abs	{Y	{Select HeightSize,1,FT_200}},
 						 Rel	{Intercept	{CWP,CPP},
 							 	 Bearing	{Random ANGLES_60Deg,240,ANGLES_1Deg},
 							 	 Range		VISINEDGE
 								}
 						}, 
 
		   	AirItem	ENEMYBOMBERAPPROACH02_Item00 =	
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1}
			}
		},
		Setval	{GlobalSkillMin, EnemyChargeSkillMin},
		Setval	{GlobalSkillMax, EnemyChargeSkillMax},
		AirGroup
		{
			Route	WPBOMBERAPPROACH02_A,

			NumInWing	6,
			NumInForm	EncounterList02,
			Formation	FORM_FLATBOX,

 			Posn		{Abs	ENEMYBOMBERAPPROACH02_Item00,
 						 Abs	{Y	HeightSize}
 						}, 

		   	AirItem
			{
				Side		NAT_ENEMY,
				Type		EnemyChargeType00,
				Squadron	{EnemyChargeSquad},
				Home		EnemyChargeHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		EnemyChargeSkillMax,
				Character	EnemyChargeCharacter,
				Morale		EnemyChargeMorale,
				Follower	ENEMYBOMBERAPPROACH02_Item00	
			}
		}
	};

//-----------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_ENEMYBOMBERAPPROACH03		=EVbomb11.BF,
		Setval	{GlobalSkillMin, EnemyChargeSkillMin},
		Setval	{GlobalSkillMax, EnemyChargeSkillMax},
		AirGroup
		{	
			Route	
			{
				WayPoint	EvBomb11_WP00=
				{
					Posn	{Abs {EnemyObjective},
							 Abs	{Y	HeightSize}
							},
					Range 	STANDARDTRIGGER,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Target	EnemyObjective,
					Posn	{Abs	{Y FT_BombAlt}},
					Action	wpbombno,
					Range	BEGINBOMBRANGE
				},
				WayPoint	
				{
					Posn	{Abs {EnemyChargeHomeBase},
							 Abs	{Y HeightSize}
							},
					Action	wpacnoactionno,
					Range	STANDARDTRIGGER
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyChargeHomeBase},
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},

			NumInWing	6,
			NumInForm	EncounterList03,
			Duty		DUTYCAP,

			Posn		{Abs	{CWP},
						 Abs	{Y	HeightSize},
						 Rel	{Intercept	{CWP,CPP},
							 	 Bearing	{Random ANGLES_60Deg,240,ANGLES_1Deg},
							 	 Range		METRES8000
								}
						}, 

		   	AirItem	EVbomb11_Item00 =	
			{
				Side		NAT_ENEMY,
				Type		EnemyChargeType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyChargeHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List {Random 6}, SKILL_VETERAN,SKILL_VETERAN,SKILL_REGULAR,SKILL_REGULAR,SKILL_REGULAR,SKILL_POOR},
				Character	EnemyChargeCharacter,
				Morale		{Random	EnemyChargeMorale,40,1},
				Bombs		8
			}
		},
		Setval	{GlobalSkillMin, EnemyChargeSkillMin},
		Setval	{GlobalSkillMax, EnemyChargeSkillMax},
		AirGroup
		{	
 			Route	EvBomb11_WP00,

			NumInWing	6,
			NumInForm	EncounterList02,
			Duty		DUTYBOMB,	
			Formation	FORM_FLATBOX,

			Posn		{Abs	{CWP},
						 Abs	{Y	HeightSize},
						 Rel	{Intercept	{CWP,EVbomb11_Item00},
							 	 Bearing	ANGLES_0Deg,
							 	 Range		VISINEDGE
								}
						}, 

		   	AirItem		
			{
				Side		NAT_ENEMY,
				Type		EnemyChargeType00,
				Squadron	{EnemyChargeSquad},
				Home		EnemyChargeHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List {Random 6}, SKILL_VETERAN,SKILL_VETERAN,SKILL_REGULAR,SKILL_REGULAR,SKILL_REGULAR,SKILL_POOR},
				Character	EnemyChargeCharacter,
				Morale		{Random	EnemyChargeMorale,40,1},
 				Follower	EVbomb11_Item00
			}
		}
	};

//-----------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_ENEMYBOMBERAPPROACH04		=EVbomb12.BF,
		Setval	{GlobalSkillMin, EnemyChargeSkillMin},
		Setval	{GlobalSkillMax, EnemyChargeSkillMax},
		AirGroup
		{
			Route
			{
				WayPoint
				{
					Posn	{Abs {CPP},
							 Abs	{Y	HeightSize}
							},
					Range 	HALFVISINEDGE,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Target	EnemyObjective,
					Posn	{Abs	{Y	HeightSize}},
					Range 	STANDARDTRIGGER,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Target	EnemyObjective,
					Posn	{Abs	{Y FT_BombAlt}},
					Action	wpbombno,
					Range	BEGINBOMBRANGE
				},
				WayPoint	
				{
					Posn	{Abs {EnemyChargeHomeBase},
							 Abs	{Y HeightSize}
							},
					Action	wpacnoactionno,
					Range	STANDARDTRIGGER
				},
				WayPoint	
				{
					Posn	{Abs {EnemyChargeHomeBase},
							 Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	6,
			NumInForm	EncounterList02,
			Formation	FORM_FLATBOX,

			Posn		{Abs	{CPP},
						 Abs	{Y	HeightSize},
						 Rel	{Intercept	{CPP,EnemyChargeHomeBase},
							 	 Bearing	{Random ANGLES_315Deg,90,ANGLES_1Deg},
							 	 Range		VISINEDGE
								}
						}, 

		   	AirItem
			{
				Side		NAT_ENEMY,
				Type		EnemyChargeType00,
				Squadron	{EnemyChargeSquad},
				Home		EnemyChargeHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List {Random 6}, SKILL_VETERAN,SKILL_VETERAN,SKILL_REGULAR,SKILL_REGULAR,SKILL_REGULAR,SKILL_POOR},
				Character	EnemyChargeCharacter,
				Morale		{Random	EnemyChargeMorale,40,1}
			}
		}
	};

//-----------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_ENEMYBOMBERAPPROACH05		=EVbomb13.BF,
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup
		{
			Route	
			{
				WayPoint	ENEMYBOMBERAPPROACH05_WP00=
				{
					Posn	{Abs {CPP},
							 Abs	{Y	HeightSize}
							},
					Range 	HALFVISINEDGE,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Target	EnemyObjective,
					Posn	{Abs	{Y	HeightSize}},
					Range 	STANDARDTRIGGER,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Target	EnemyObjective,
					Posn	{Abs	{Y FT_BombAlt}},
					Action	wpbombno,
					Range	BEGINBOMBRANGE
				},
				WayPoint	
				{
					Posn	{Abs {EnemyChargeHomeBase},
							 Abs	{Y HeightSize}
							},
					Action	wpacnoactionno,
					Range	STANDARDTRIGGER
				},
				WayPoint	
				{
					Posn	{Abs {EnemyChargeHomeBase},
							 Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},

			NumInWing	6,
			NumInForm	EncounterList03,
			Duty		DUTYCAP,

			Posn		{Abs	{CPP},
						 Abs	{Y	{Select HeightSize,1,FT_200}},
						 Rel	{Intercept	{CPP,EnemyChargeHomeBase},
							 	 Bearing	{Random ANGLES_315Deg,90,ANGLES_1Deg},
							 	 Range		VISINEDGE
								}
						}, 

		   	AirItem	ENEMYBOMBERAPPROACH05_Item00 =	
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1}
			}
		},
		Setval	{GlobalSkillMin, EnemyChargeSkillMin},
		Setval	{GlobalSkillMax, EnemyChargeSkillMax},
		AirGroup
		{
			Route	ENEMYBOMBERAPPROACH05_WP00,

			NumInWing	6,
			NumInForm	EncounterList04,
			Formation	FORM_FLATBOX,

 			Posn		{Abs	ENEMYBOMBERAPPROACH05_Item00,
 						 Abs	{Y	HeightSize}
 						}, 

		   	AirItem
			{
				Side		NAT_ENEMY,
				Type		EnemyChargeType00,
				Squadron	{EnemyChargeSquad},
				Home		EnemyChargeHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		EnemyChargeSkillMax,
				Character	EnemyChargeCharacter,
				Morale		EnemyChargeMorale,
				Follower	ENEMYBOMBERAPPROACH05_Item00	
			}
		}
	};

//-----------------------------------------------------------------------------
//REDUNDANT
//DeadCode MS 03Oct96 	BattleField
//DeadCode MS 03Oct96 	{
//DeadCode MS 03Oct96 		FileName	BFLATEBOMBERESCORT01=cblate02.BF
//DeadCode MS 03Oct96 	};

//-----------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_ENEMYSCOUTSCROSSPATH=EVpath00.BF,
		Setval	{AngleStepSize,Int {Random 0,2,1}},	
		Setval	{HeightStepSize,Int {Random 0,51,100}},
//DeadCode MS 28Oct96 		Setval	{RangeStepSize,Int {Random 0,VISBOUNDARYSIZE,1}},
		Setval	{RandAngle, Bearing {Select ANGLES_20Deg,AngleStepSize,ANGLES_300Deg}},

		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},

		AirGroup	PathCrossGroup_00 =	
		{
			Route		
			{
				WayPoint	CrossPath00 =
				{
					Posn	{Abs	{CPP},
							 Rel	{Y {Select	-FT_3000,HeightStepSize,FT_1},
									 Intercept	{CPP,CWP},
									 Bearing	{Random RandAngle,21,ANGLES_1Deg},
						 			 Range		VISINEDGE
							 		}
							},
					Action	wpacnoactionno,
					Range	MARGIN
				},
				WayPoint	
				{
					Posn	{Abs	CrossPath00,
							 Rel	{Intercept	{CPP,CWP},	
						 			 Bearing	{Select ANGLES_270Deg,AngleStepSize,ANGLES_180Deg},
						 			 Range	METRES5000
									}
							},
					Action	wpacnoactionno,
					Range	MARGIN
				},
				WayPoint	
				{
					Posn	{Abs	{CPP},
							 Rel	{Y {Select	-FT_3000,HeightStepSize,FT_1},
									 Intercept	{CPP,EnemyScoutHomeBase},	
						 			 Bearing	ANGLES_0Deg,
						 			 RangePercent	70
									}
							},
					Action	wpacnoactionno,
					Range	MARGIN
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyScoutHomeBase},	
						 	 Abs	{Y FT_EnterLandingPattern}
							},
					Range	DistEnterLandingPattern,
					Action	wpalandingno
				}
			},
			NumInWing	6,
			NumInForm	EncounterList03,

			Duty		DUTYCAP,

//DeadCode MS 09Oct96 			Posn		{Abs	{CPP},
//DeadCode MS 09Oct96 						 Rel	{Y {Select	-FT_3000,HeightStepSize,FT_1},
//DeadCode MS 09Oct96 								 Intercept	{CPP,CWP},
//DeadCode MS 09Oct96 					 			 Bearing	{Select	ANGLES_320Deg,AngleStepSize,ANGLES_80Deg},
//DeadCode MS 09Oct96 					 			 Range		{Select	VISINEDGE,RangeStepSize,METRES01}
//DeadCode MS 09Oct96 								}
//DeadCode MS 09Oct96 						},

			Posn	{Abs	CrossPath00, 
					 Rel	{Intercept	{CPP,CWP},
					   		 Bearing	{Select ANGLES_90Deg,AngleStepSize,ANGLES_180Deg},
					   		 Range	METRES100
						 	}
					},

		   	AirItem		
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1}
			}
		}
	};

//-----------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_ENEMYSCOUTSCROSSPATHBEHIND	=EVpath01.BF,
		Setval	{AngleStepSize,Int {Random 0,2,1}},	
		Setval	{HeightStepSize,Int {Random 0,51,100}},
//DeadCode MS 28Oct96 		Setval	{RangeStepSize,Int {Random 0,VISBOUNDARYSIZE,1}},
		Setval	{RandAngle, Angle {Select ANGLES_60Deg,AngleStepSize,ANGLES_210Deg}},
//DeadCode MS 27Oct96 		Setval	{RandAngle, Bearing {Random RandAngle,21,ANGLES_1Deg}},

		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup
		{
			Route		
			{
				WayPoint	CrossPath01 =
				{
					Posn	{Abs	{CPP},
							 Rel	{Y {Select	-FT_3000,HeightStepSize,FT_1},
									 Intercept	{CPP,CWP},
									 Bearing	{Random	RandAngle,21,ANGLES_1Deg},
						 			 Range		VISINEDGE
//DeadCode MS 27Oct96 									 Bearing	{Select	ANGLES_135Deg,AngleStepSize,ANGLES_90Deg},
//DeadCode MS 27Oct96 						 			 Range		{Random	VISINEDGE,VISBOUNDARYSIZE,METRES01}
								}
							},
					Action	wpacnoactionno,
					Range	MARGIN
				},
				WayPoint	
				{
					Posn	{Abs	CrossPath01,
							 Rel	{Intercept	{CPP,CWP},	
						 			 Bearing	{Select ANGLES_270Deg,AngleStepSize,ANGLES_180Deg},
						 			 Range	METRES5000
									}
							},
					Action	wpacnoactionno,
					Range	MARGIN
				},
				WayPoint	
				{
					Posn	{Abs	{CPP},
							 Rel	{Y {Select	-FT_3000,HeightStepSize,FT_1},
									 Intercept	{CPP,EnemyScoutHomeBase},	
						 			 Bearing	ANGLES_0Deg,
						 			 RangePercent	70
									}
							},
					Action	wpacnoactionno,
					Range	MARGIN
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyScoutHomeBase},	
						 	 Abs	{Y FT_EnterLandingPattern}
							},
					Range	DistEnterLandingPattern,
					Action	wpalandingno
				}
			},
			NumInWing	6,
			NumInForm	EncounterList03,
			Duty		DUTYCAP,

//DeadCode MS 27Oct96 			Posn		{Abs	{CPP},
//DeadCode MS 27Oct96 						 Rel	{Y {Select	-FT_3000,HeightStepSize,FT_1},
//DeadCode MS 27Oct96 								 Intercept	{CWP,CPP},
//DeadCode MS 27Oct96 					 			 Bearing	{Select	ANGLES_210Deg,AngleStepSize,ANGLES_300Deg},
//DeadCode MS 27Oct96 					 			 Range		{Select	VISINEDGE,RangeStepSize,METRES01}
//DeadCode MS 27Oct96 								}
//DeadCode MS 27Oct96 						},

			Posn		{Abs	CrossPath01,
						 Rel	{Intercept	{CPP,CWP},
					 			 Bearing	{Select	ANGLES_90Deg,AngleStepSize,ANGLES_180Deg},
					 			 Range		METRES50
								}
						},

		   	AirItem		
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1}
			}
		}
	};

//---------------------------------------------------------------------------
//DeadCode MS 01Oct96 //BFEV_ENEMYLONESCOUTCROSSESPATH
//DeadCode MS 01Oct96 //Single scout cross path of player in distance
//DeadCode MS 01Oct96 
//DeadCode MS 01Oct96 	BattleField
//DeadCode MS 01Oct96 	{
//DeadCode MS 01Oct96 		FileName	BFEV_ENEMYLONESCOUTCROSSESPATH=EVpath02.BF,
//DeadCode MS 01Oct96 		Setval	{FormSize00,Int {Select 1,0,0}},
//DeadCode MS 01Oct96 		Setval	{AngleStepSize,Int {Random 0,1,1}},
//DeadCode MS 01Oct96 
//DeadCode MS 01Oct96 		AirGroup	PathCrossGroup_00 
//DeadCode MS 01Oct96 	};

//---------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_ENEMYSCOUTRESCUE			=rescue01.BF,
		Setval	{GlobalSkillMin, FriendlyScoutSkillMin},
		Setval	{GlobalSkillMax, FriendlyScoutSkillMax},
		AirGroup	
		{
			Route
			{
				WayPoint	
				{
					Posn	{Abs	{FriendlyScoutHomeBase},
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Range	DistEnterLandingPattern,
					Action	wpalandingno
				}
			},
			NumInWing	6,
			NumInForm	EncounterList02,
			Duty		DUTYCAP,
//fixme		Duty		Dumbbastardrunaway

			Posn		{Abs	{CPP},
						 Rel	{Y {Random	-FT_2500,50,FT_100},
								 Intercept	{FriendlyScoutHomeBase,CPP},
								 Bearing	{Random	ANGLES_300Deg,120,ANGLES_1Deg},
				 				 Range		{Random	VISINEDGE,VISBOUNDARYSIZE,METRES01}
							}
						},

		   	AirItem	FriendlyScoutInDanger00 =
			{
				Side		NAT_FRIEND,
				Type		FriendlyScoutType00,
				Home		FriendlyScoutHomeBase,
				Squadron	{FriendlyScoutSquad,PS_5,PS_6,PS_7,PS_8},
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, FriendlyScoutTactician,FriendlyScoutMrAverage,FriendlyScoutCavalier}},
				Morale		{Random	FriendlyScoutMorale,40,1}
			}
		},
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup
		{
			Route
			{
				WayPoint	
				{
					Posn	{Abs	FriendlyScoutInDanger00},
					Action	wpacnoactionno,
					Range	MARGIN
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyScoutHomeBase}, 
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	6,
			NumInForm	EncounterList08,
			Duty		DUTYCAP,

			Posn		{Abs	FriendlyScoutInDanger00,
						 Rel	{Y {Random	METRES500,50,METRES10},
							 	 Intercept	{CPP,FriendlyScoutInDanger00},
							 	 Bearing	{Random ANGLES_330Deg,60,ANGLES_1Deg},
							 	 Range		{Random	METRES500,30,METRES10} 
							}
						},
		   	AirItem		
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1}
			}
		}
	};

//---------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_ENEMYVULTURES			=rescue02.BF,
		Setval	{GlobalSkillMin, FriendlyScoutSkillMin},
		Setval	{GlobalSkillMax, FriendlyScoutSkillMax},
		AirGroup	
		{
			Route
			{
				WayPoint	
				{
					Posn	{Abs	{FriendlyScoutHomeBase}},
					Action	wpacnoactionno
				}
			},
			NumInWing	1,
			NumInForm	1,
			Duty		DUTYCAP,

			Posn		{Abs	{CPP},
						 Abs	{Y -FT_1},
						 Rel	{Intercept	{CPP,CWP},
								 Bearing	{Random	ANGLES_270Deg,180,ANGLES_1Deg},
				 				 Range	{Random	VISINEDGE,VISBOUNDARYSIZE,METRES01}
								}
						},

		   	AirItem	FriendlyScoutVultureVictim00 =
			{
				Side		NAT_FRIEND,
				Type		FriendlyScoutType00,
				Home		FriendlyScoutHomeBase,
				Squadron	{FriendlyScoutSquad,PS_5,PS_6,PS_7,PS_8},
				MoveCode	AUTO_NOPPILOT,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, FriendlyScoutTactician,FriendlyScoutMrAverage,FriendlyScoutCavalier}},
				Morale		{Random	FriendlyScoutMorale,40,1},
//DAMAGE IS IN H\3DINSTR.H
//FIXME predamage so gear is crushed and wing is off.
				Damage		0x0A
			}
		},
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup
		{
			Route
			{
				WayPoint	
				{
					Posn	{Abs	FriendlyScoutVultureVictim00,
							 Abs	{Y -FT_1000},	
							 Rel	{Bearing ANGLES_180Deg,
							 		 Range	METRES500
									}
							},
					Action	wpacnoactionno,
					Range	MARGIN
				},
				WayPoint	
				{
					Posn	{Abs	FriendlyScoutVultureVictim00,
							 Abs	{Y -FT_1000},	
							 Rel	{Bearing ANGLES_270Deg,
							 		 Range	METRES500
									}
							},
					Action	wpacnoactionno,
					Range	MARGIN
				},
				WayPoint	
				{
					Posn	{Abs	FriendlyScoutVultureVictim00,
							 Abs	{Y -FT_1000},	
							 Rel	{Bearing ANGLES_0Deg,
							 		 Range	METRES500
									}
							},
					Action	wpacnoactionno,
					Range	MARGIN
				},
				WayPoint	
				{
					Posn	{Abs	FriendlyScoutVultureVictim00,
							 Abs	{Y -FT_1000},	
							 Rel	{Bearing ANGLES_90Deg,
							 		 Range	METRES500
									}
							},
					Action	wpacnoactionno,
					Range	MARGIN
				},

//	I want him to start straffing the guy on the ground, FriendlyScoutVultureVictim00

				WayPoint	
				{
					Target	FriendlyScoutVultureVictim00,
					Posn	{Abs	{Y FT_Straffe}},
					Action	wpdivebombstraffeno,
					Range	BEGINSTRAFFERANGE
				},

				WayPoint	
				{
					Posn	{Abs	{EnemyScoutHomeBase}, 
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	1,
			NumInForm	2,
			Duty		DUTYCAP,


			Posn		{Abs	FriendlyScoutVultureVictim00,
						 Abs	{Y	-FT_1000},
						 Rel	{Bearing	ANGLES_90Deg,
							 	 Range		METRES500
								}
						},
				
		   	AirItem		
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1}
			}
		}
	};

//---------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_FRACAS1				=EVfrac01.BF,

		Setval	{GlobalSkillMin, FriendlyScoutSkillMin},
		Setval	{GlobalSkillMax, FriendlyScoutSkillMax},
		AirGroup	FriendlyFracas01A_Group =
		{
			Route	FriendlyFracas01_Route =	
			{
				WayPoint	EVfrac01_WP00 =	
				{
					Posn	{Abs	{CPP},
							 Rel	{Y {Random -FT_4000,4000,FT_1},
									 Intercept	{CPP,CWP},
 							 	 	 Bearing	{Random ANGLES_270Deg,180,ANGLES_1Deg},
								 	 Range		VISINEDGE
									}
							},
					Action	wpacnoactionno,
					Range	MARGIN
				},
				WayPoint	
				{
					Posn	{Abs	EVfrac01_WP00,
							 Rel	{Intercept	{EVfrac01_WP00,FriendlyScoutHomeBase},
									 Bearing	ANGLES_0Deg,
									 RangePercent	80
									}
							},	
					Action	wpacnoactionno,
					Range	MARGIN
				},
				WayPoint	
				{
					Posn	{Abs	{FriendlyScoutHomeBase}, 
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	4,
			NumInForm	EncounterList04,
			Duty		DUTYCAP,
			Formation	FORM_FLATBOX,
			
			Posn		{Abs	EVfrac01_WP00},

		   	AirItem	FriendlyFracas01A_Item =	
			{
				Side		NAT_FRIEND,
				Type		FriendlyScoutType00,
				Home		FriendlyScoutHomeBase,
				Squadron	{FriendlyScoutSquad,PS_5,PS_6,PS_7,PS_8},
				MoveCode	AUTO_COMBAT,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, FriendlyScoutTactician,FriendlyScoutMrAverage,FriendlyScoutCavalier}},
				Morale		{Random	FriendlyScoutMorale,40,1}
			}
		},

		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},

		AirGroup	EnemyFracas01A_Group =
		{
 			Route	EnemyFracas01_Route =			
 			{
  				WayPoint
  				{
  					Posn	{Abs	EVfrac01_WP00},
  					Action	wpacnoactionno,
  					Range	MARGIN
  				},
 				WayPoint	
 				{						   
 					Posn	{Abs	{EnemyScoutHomeBase}, 
 						 	Abs	{Y FT_EnterLandingPattern}
 							},
 					Action	wpalandingno,
 					Range	DistEnterLandingPattern
 				}
 			},
			NumInWing	4,
			NumInForm	EncounterList04,
			Duty		DUTYCAP,
			Formation	FORM_FLATBOX,


			Posn	EnemyFracas01A_Pos =	
					{Abs	FriendlyFracas01A_Item,
					 Rel	{Y FT_500,
							 Bearing	{Random	ANGLES_0Deg,359,ANGLES_1Deg},
							 Range	METRES300
							}
					},

		   	AirItem	EnemyFracas01A_Item =
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	ACM_STRAIGHTDIVE,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1},
				Target		FriendlyFracas01A_Item,
				Attacker	FriendlyFracas01A_Item,
 				Attitude	{
							 Intercept	{EnemyFracas01A_Pos,FriendlyFracas01A_Item},
							 Heading	ANGLES_0Deg,
							 Pitch	ANGLES_0Deg
							}
			}
		},
		Setval	{GlobalSkillMin, FriendlyScoutSkillMin},
		Setval	{GlobalSkillMax, FriendlyScoutSkillMax},

		AirGroup	FriendlyFracas01B_Group =
		{
   			Route
			{
				WayPoint
				{
					Posn	{Abs	{CPP},
							 Rel	{Y {Random -FT_4000,4000,FT_1},
									 Intercept	{CPP,CWP},
 							 	 	 Bearing	{Random ANGLES_270Deg,180,ANGLES_1Deg},
								 	 Range		VISINEDGE
									}
							},
					Action	wpacnoactionno,
					Range	MARGIN
				},
				WayPoint	
				{
					Posn	{Abs	{FriendlyScoutHomeBase}, 
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},

			NumInWing	4,
			NumInForm	EncounterList04,
			Duty		DUTYCAP,
			Formation	FORM_FLATBOX,

			Posn	FriendlyFracas01B_Pos =		
					{Abs	EnemyFracas01A_Item,
					 Rel	{Y FT_500,
							 Bearing	{Random	ANGLES_0Deg,359,ANGLES_1Deg},
							 Range	METRES300
							}
					},

		   	AirItem	FriendlyFracas01B_Item =	
			{
				Side		NAT_FRIEND,
 				Type		FriendlyScoutType00,
				Home		FriendlyScoutHomeBase,
				Squadron	{FriendlyScoutSquad,PS_5,PS_6,PS_7,PS_8},
				MoveCode	ACM_STRAIGHTDIVE,
				Target		EnemyFracas01A_Item,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, FriendlyScoutTactician,FriendlyScoutMrAverage,FriendlyScoutCavalier}},
				Morale		{Random	FriendlyScoutMorale,40,1},
 				Attitude	{
							 Intercept	{FriendlyFracas01B_Pos,EnemyFracas01A_Item},
							 Heading	ANGLES_0Deg,
							 Pitch	ANGLES_0Deg
							}
			}
		},
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},

		AirGroup	EnemyFracas01B_Group =
		{
   			Route
 			{
  				WayPoint
  				{
  					Posn	{Abs	EVfrac01_WP00},
  					Action	wpacnoactionno,
  					Range	MARGIN
  				},
 				WayPoint	
 				{						   
 					Posn	{Abs	{EnemyScoutHomeBase}, 
 						 	Abs	{Y FT_EnterLandingPattern}
 							},
 					Action	wpalandingno,
 					Range	DistEnterLandingPattern
 				}
 			},

			NumInWing	6,
			NumInForm	EncounterList06,
			Duty		DUTYCAP,

			Posn	EnemyFracas01B_Pos =	
					{Abs	FriendlyFracas01B_Item,
					 Rel	{Y FT_500,
							 Bearing	{Random	ANGLES_0Deg,359,ANGLES_1Deg},
							 Range	METRES300
							}
					},

		   	AirItem	EnemyFracas01B_Item =	
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	ACM_STRAIGHTDIVE,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1},
				Target		FriendlyFracas01B_Item,
 				Attitude	{
							 Intercept	{EnemyFracas01B_Pos,FriendlyFracas01B_Item},
							 Heading	ANGLES_0Deg,
							 Pitch	ANGLES_0Deg
							}
			}
		},
//This is the guy who was the chain

		AirGroup
		{
   			Route
 			{
  				WayPoint
  				{
  					Posn	{Abs	EVfrac01_WP00},
  					Action	wpacnoactionno,
  					Range	MARGIN
  				},
 				WayPoint	
 				{						   
 					Posn	{Abs	{EnemyScoutHomeBase}, 
 						 	Abs	{Y FT_EnterLandingPattern}
 							},
 					Action	wpalandingno,
 					Range	DistEnterLandingPattern
 				}
 			},

			NumInWing	4,
			NumInForm	EncounterList04,
			Duty		DUTYCAP,

			Posn	
					{Abs	EnemyFracas01B_Item,
					 Rel	{Y FT_5000,
							 Intercept	{CPP,EnemyFracas01B_Item},
							 Bearing	{Random	ANGLES_270Deg,180,ANGLES_1Deg},
							 RangePercent	100
							}
					},

		   	AirItem
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1}
			}
		}
	};

//---------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_FRACAS2				=EVfrac02.BF,
		Setval	{GlobalSkillMin, FriendlyScoutSkillMin},
		Setval	{GlobalSkillMax, FriendlyScoutSkillMax},
		AirGroup	
		{
			Route	
			{
				WayPoint	EVFrac02_WP00 =	
				{
					Posn	{Abs	{CPP},
							 Rel	{Y {Random -FT_4000,4000,FT_1},
									 Intercept	{CPP,CWP},
 							 	 	 Bearing	{Random ANGLES_270Deg,180,ANGLES_1Deg},
								 	 Range		VISINEDGE
									}
							},
					Action	wpacnoactionno,
					Range	MARGIN
				},
				WayPoint	
				{
					Posn	{Abs	EVFrac02_WP00,
							 Rel	{Intercept	{EVFrac02_WP00,FriendlyScoutHomeBase},
									 Bearing	ANGLES_0Deg,
									 RangePercent	80
									}
							},	
					Action	wpacnoactionno,
					Range	MARGIN
				},
				WayPoint	
				{
					Posn	{Abs	{FriendlyScoutHomeBase}, 
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	4,
			NumInForm	EncounterList04,
			Duty		DUTYCAP,
			Formation	FORM_FLATBOX,
			
			Posn		{Abs	EVFrac02_WP00},

		   	AirItem	FriendlyFracas02A_Item =	
			{
				Side		NAT_FRIEND,
				Type		FriendlyScoutType00,
				Home		FriendlyScoutHomeBase,
				Squadron	{FriendlyScoutSquad,PS_5,PS_6,PS_7,PS_8},
				MoveCode	AUTO_COMBAT,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, FriendlyScoutTactician,FriendlyScoutMrAverage,FriendlyScoutCavalier}},
				Morale		{Random	FriendlyScoutMorale,40,1}
			}
		},
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup	
		{
 			Route	
 			{
  				WayPoint
  				{
  					Posn	{Abs	EVFrac02_WP00},
  					Action	wpacnoactionno,
  					Range	MARGIN
  				},
 				WayPoint	
 				{						   
 					Posn	{Abs	{EnemyScoutHomeBase}, 
 						 	Abs	{Y FT_EnterLandingPattern}
 							},
 					Action	wpalandingno,
 					Range	DistEnterLandingPattern
 				}
 			},
			NumInWing	4,
			NumInForm	EncounterList04,
			Duty		DUTYCAP,
			Formation	FORM_FLATBOX,


			Posn	EnemyFracas02A_Pos =	
					{Abs	FriendlyFracas02A_Item,
					 Rel	{Y FT_500,
							 Bearing	{Random	ANGLES_0Deg,359,ANGLES_1Deg},
							 Range	METRES300
							}
					},

		   	AirItem	EnemyFracas02A_Item =
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	ACM_STRAIGHTDIVE,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1},
				Target		FriendlyFracas02A_Item,
				Attacker	FriendlyFracas02A_Item,
 				Attitude	{
							 Intercept	{EnemyFracas02A_Pos,FriendlyFracas02A_Item},
							 Heading	ANGLES_0Deg,
							 Pitch	ANGLES_0Deg
							}
			}
		},
		Setval	{GlobalSkillMin, FriendlyScoutSkillMin},
		Setval	{GlobalSkillMax, FriendlyScoutSkillMax},
		AirGroup	
		{
   			Route
			{
				WayPoint
				{
					Posn	{Abs	{CPP},
							 Rel	{Y {Random -FT_4000,4000,FT_1},
									 Intercept	{CPP,CWP},
 							 	 	 Bearing	{Random ANGLES_270Deg,180,ANGLES_1Deg},
								 	 Range		VISINEDGE
									}
							},
					Action	wpacnoactionno,
					Range	MARGIN
				},
				WayPoint	
				{
					Posn	{Abs	{FriendlyScoutHomeBase}, 
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},

			NumInWing	4,
			NumInForm	EncounterList04,
			Duty		DUTYCAP,
			Formation	FORM_FLATBOX,

			Posn	FriendlyFracas02B_Pos =		
					{Abs	EnemyFracas02A_Item,
					 Rel	{Y FT_500,
							 Bearing	{Random	ANGLES_0Deg,359,ANGLES_1Deg},
							 Range	METRES300
							}
					},

		   	AirItem	FriendlyFracas02B_Item =	
			{
				Side		NAT_FRIEND,
 				Type		FriendlyScoutType00,
				Home		FriendlyScoutHomeBase,
				Squadron	{FriendlyScoutSquad,PS_5,PS_6,PS_7,PS_8},
				MoveCode	ACM_STRAIGHTDIVE,
				Target		EnemyFracas02A_Item,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, FriendlyScoutTactician,FriendlyScoutMrAverage,FriendlyScoutCavalier}},
				Morale		{Random	FriendlyScoutMorale,40,1},
 				Attitude	{
							 Intercept	{FriendlyFracas02B_Pos,EnemyFracas02A_Item},
							 Heading	ANGLES_0Deg,
							 Pitch	ANGLES_0Deg
							}
			}
		},
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup	
		{
   			Route
 			{
  				WayPoint
  				{
  					Posn	{Abs	EVFrac02_WP00},
  					Action	wpacnoactionno,
  					Range	MARGIN
  				},
 				WayPoint	
 				{						   
 					Posn	{Abs	{EnemyScoutHomeBase}, 
 						 	Abs	{Y FT_EnterLandingPattern}
 							},
 					Action	wpalandingno,
 					Range	DistEnterLandingPattern
 				}
 			},

			NumInWing	6,
			NumInForm	EncounterList06,
			Duty		DUTYCAP,

			Posn	EnemyFracas02B_Pos =	
					{Abs	FriendlyFracas02B_Item,
					 Rel	{Y FT_500,
							 Bearing	{Random	ANGLES_0Deg,359,ANGLES_1Deg},
							 Range	METRES300
							}
					},

		   	AirItem	EnemyFracas02B_Item =	
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	ACM_STRAIGHTDIVE,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1},
				Target		FriendlyFracas02B_Item,
 				Attitude	{
							 Intercept	{EnemyFracas02B_Pos,FriendlyFracas02B_Item},
							 Heading	ANGLES_0Deg,
							 Pitch	ANGLES_0Deg
							}
			}
		},
//this guy was the chain

		AirGroup
		{
   			Route
 			{
  				WayPoint
  				{
  					Posn	{Abs	EVFrac02_WP00},
  					Action	wpacnoactionno,
  					Range	MARGIN
  				},
 				WayPoint	
 				{						   
 					Posn	{Abs	{EnemyScoutHomeBase}, 
 						 	Abs	{Y FT_EnterLandingPattern}
 							},
 					Action	wpalandingno,
 					Range	DistEnterLandingPattern
 				}
 			},

			NumInWing	4,
			NumInForm	EncounterList04,
			Duty		DUTYCAP,

			Posn	
					{Abs	EnemyFracas02B_Item,
					 Rel	{Y FT_500,
							 Intercept	{CPP,EnemyFracas02B_Item},
							 Bearing	{Random	ANGLES_270Deg,180,ANGLES_1Deg},
							 RangePercent	150
							}
					},

		   	AirItem
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1}
			}
		}
	};

//---------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_FRACAS3 				=EVfrac03.BF,
		Setval	{GlobalSkillMin, FriendlyScoutSkillMin},
		Setval	{GlobalSkillMax, FriendlyScoutSkillMax},
		AirGroup
		{
			Route
			{
				WayPoint	EVFrac03_WP00 =	
				{
					Posn	{Abs	{CPP},
							 Rel	{Y {Random -FT_4000,4000,FT_1},
									 Intercept	{CPP,CWP},
 							 	 	 Bearing	{Random ANGLES_270Deg,180,ANGLES_1Deg},
								 	 Range		VISINEDGE
									}
							},
					Action	wpacnoactionno,
					Range	MARGIN
				},
				WayPoint	
				{
					Posn	{Abs	EVFrac03_WP00,
							 Rel	{Intercept	{EVFrac03_WP00,FriendlyScoutHomeBase},
									 Bearing	ANGLES_0Deg,
									 RangePercent	80
									}
							},	
					Action	wpacnoactionno,
					Range	MARGIN
				},
				WayPoint	
				{
					Posn	{Abs	{FriendlyScoutHomeBase}, 
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	4,
			NumInForm	EncounterList04,
			Duty		DUTYCAP,
			Formation	FORM_FLATBOX,
			
			Posn		{Abs	EVFrac03_WP00},

		   	AirItem	FriendlyFracas03A_Item =	
			{
				Side		NAT_FRIEND,
				Type		FriendlyScoutType00,
				Home		FriendlyScoutHomeBase,
				Squadron	{FriendlyScoutSquad,PS_5,PS_6,PS_7,PS_8},
				MoveCode	AUTO_COMBAT,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, FriendlyScoutTactician,FriendlyScoutMrAverage,FriendlyScoutCavalier}},
				Morale		{Random	FriendlyScoutMorale,40,1}
			}
		},
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup
		{
 			Route
 			{
  				WayPoint
  				{
  					Posn	{Abs	EVFrac03_WP00},
  					Action	wpacnoactionno,
  					Range	MARGIN
  				},
 				WayPoint	
 				{						   
 					Posn	{Abs	{EnemyScoutHomeBase}, 
 						 	Abs	{Y FT_EnterLandingPattern}
 							},
 					Action	wpalandingno,
 					Range	DistEnterLandingPattern
 				}
 			},
			NumInWing	4,
			NumInForm	EncounterList04,
			Duty		DUTYCAP,
			Formation	FORM_FLATBOX,


			Posn	EnemyFracas03A_Pos =	
					{Abs	FriendlyFracas03A_Item,
					 Rel	{Y FT_500,
							 Bearing	{Random	ANGLES_0Deg,359,ANGLES_1Deg},
							 Range	METRES300
							}
					},

		   	AirItem	EnemyFracas03A_Item =
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	ACM_STRAIGHTDIVE,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1},
				Target		FriendlyFracas03A_Item,
				Attacker	FriendlyFracas03A_Item,
 				Attitude	{
							 Intercept	{EnemyFracas03A_Pos,FriendlyFracas03A_Item},
							 Heading	ANGLES_0Deg,
							 Pitch	ANGLES_0Deg
							}
			}
		},
		Setval	{GlobalSkillMin, FriendlyScoutSkillMin},
		Setval	{GlobalSkillMax, FriendlyScoutSkillMax},
		AirGroup	FriendlyFracas03B_Group =
		{
   			Route
			{
				WayPoint
				{
					Posn	{Abs	{CPP},
							 Rel	{Y {Random -FT_4000,4000,FT_1},
									 Intercept	{CPP,CWP},
 							 	 	 Bearing	{Random ANGLES_270Deg,180,ANGLES_1Deg},
								 	 Range		VISINEDGE
									}
							},
					Action	wpacnoactionno,
					Range	MARGIN
				},
				WayPoint	
				{
					Posn	{Abs	{FriendlyScoutHomeBase}, 
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},

			NumInWing	4,
			NumInForm	EncounterList04,
			Duty		DUTYCAP,
			Formation	FORM_FLATBOX,

			Posn	FriendlyFracas03B_Pos =		
					{Abs	EnemyFracas03A_Item,
					 Rel	{Y FT_500,
							 Bearing	{Random	ANGLES_0Deg,359,ANGLES_1Deg},
							 Range	METRES300
							}
					},

		   	AirItem	FriendlyFracas03B_Item =	
			{
				Side		NAT_FRIEND,
 				Type		FriendlyScoutType00,
				Home		FriendlyScoutHomeBase,
				Squadron	{FriendlyScoutSquad,PS_5,PS_6,PS_7,PS_8},
				MoveCode	ACM_STRAIGHTDIVE,
				Target		EnemyFracas03A_Item,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, FriendlyScoutTactician,FriendlyScoutMrAverage,FriendlyScoutCavalier}},
				Morale		{Random	FriendlyScoutMorale,40,1},
 				Attitude	{
							 Intercept	{FriendlyFracas03B_Pos,EnemyFracas03A_Item},
							 Heading	ANGLES_0Deg,
							 Pitch	ANGLES_0Deg
							}
			}
		},
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup 
		{
   			Route
 			{
  				WayPoint
  				{
  					Posn	{Abs	EVFrac03_WP00},
  					Action	wpacnoactionno,
  					Range	MARGIN
  				},
 				WayPoint	
 				{						   
 					Posn	{Abs	{EnemyScoutHomeBase}, 
 						 	Abs	{Y FT_EnterLandingPattern}
 							},
 					Action	wpalandingno,
 					Range	DistEnterLandingPattern
 				}
 			},

			NumInWing	6,
			NumInForm	EncounterList06,
			Duty		DUTYCAP,

			Posn	EnemyFracas03B_Pos =	
					{Abs	FriendlyFracas03B_Item,
					 Rel	{Y FT_500,
							 Bearing	{Random	ANGLES_0Deg,359,ANGLES_1Deg},
							 Range	METRES300
							}
					},

		   	AirItem	EnemyFracas03B_Item =	
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	ACM_STRAIGHTDIVE,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1},
				Target		FriendlyFracas03B_Item,
 				Attitude	{
							 Intercept	{EnemyFracas03B_Pos,FriendlyFracas03B_Item},
							 Heading	ANGLES_0Deg,
							 Pitch	ANGLES_0Deg
							}
			}
		}
	};

//---------------------------------------------------------------------------

	BattleField
	{
		FileName	BFEV_FRACAS4				=EVfrac04.BF,
		Setval	{GlobalSkillMin, FriendlyScoutSkillMin},
		Setval	{GlobalSkillMax, FriendlyScoutSkillMax},
		AirGroup
		{
			Route
			{
				WayPoint	EVFrac04_WP00 =	
				{
					Posn	{Abs	{CPP},
							 Rel	{Y {Random -FT_4000,4000,FT_1},
									 Intercept	{CPP,CWP},
 							 	 	 Bearing	{Random ANGLES_270Deg,180,ANGLES_1Deg},
								 	 Range		VISINEDGE
									}
							},
					Action	wpacnoactionno,
					Range	MARGIN
				},
				WayPoint	
				{
					Posn	{Abs	EVFrac04_WP00,
							 Rel	{Intercept	{EVFrac04_WP00,FriendlyScoutHomeBase},
									 Bearing	ANGLES_0Deg,
									 RangePercent	80
									}
							},	
					Action	wpacnoactionno,
					Range	MARGIN
				},
				WayPoint	
				{
					Posn	{Abs	{FriendlyScoutHomeBase}, 
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	4,
			NumInForm	EncounterList04,
			Duty		DUTYCAP,
			Formation	FORM_FLATBOX,
			
			Posn		{Abs	EVFrac04_WP00},

		   	AirItem	FriendlyFracas04A_Item =	
			{
				Side		NAT_FRIEND,
				Type		FriendlyScoutType00,
				Home		FriendlyScoutHomeBase,
				Squadron	{FriendlyScoutSquad,PS_5,PS_6,PS_7,PS_8},
				MoveCode	AUTO_COMBAT,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, FriendlyScoutTactician,FriendlyScoutMrAverage,FriendlyScoutCavalier}},
				Morale		{Random	FriendlyScoutMorale,40,1}
			}
		},
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup 
		{
 			Route
 			{
  				WayPoint
  				{
  					Posn	{Abs	EVFrac04_WP00},
  					Action	wpacnoactionno,
  					Range	MARGIN
  				},
 				WayPoint	
 				{						   
 					Posn	{Abs	{EnemyScoutHomeBase}, 
 						 	Abs	{Y FT_EnterLandingPattern}
 							},
 					Action	wpalandingno,
 					Range	DistEnterLandingPattern
 				}
 			},
			NumInWing	6,
			NumInForm	EncounterList08,
			Duty		DUTYCAP,
			Formation	FORM_FLATBOX,


			Posn	EnemyFracas04A_Pos =	
					{Abs	FriendlyFracas04A_Item,
					 Rel	{Y FT_500,
							 Bearing	{Random	ANGLES_0Deg,359,ANGLES_1Deg},
							 Range	METRES300
							}
					},

		   	AirItem	EnemyFracas04A_Item =
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	ACM_STRAIGHTDIVE,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1},
				Target		FriendlyFracas04A_Item,
				Attacker	FriendlyFracas04A_Item,
 				Attitude	{
							 Intercept	{EnemyFracas04A_Pos,FriendlyFracas04A_Item},
							 Heading	ANGLES_0Deg,
							 Pitch	ANGLES_0Deg
							}
			}
		},
		Setval	{GlobalSkillMin, FriendlyScoutSkillMin},
		Setval	{GlobalSkillMax, FriendlyScoutSkillMax},
		AirGroup 
		{
   			Route
			{
				WayPoint
				{
					Posn	{Abs	{CPP},
							 Rel	{Y {Random -FT_4000,4000,FT_1},
									 Intercept	{CPP,CWP},
 							 	 	 Bearing	{Random ANGLES_270Deg,180,ANGLES_1Deg},
								 	 Range		VISINEDGE
									}
							},
					Action	wpacnoactionno,
					Range	MARGIN
				},
				WayPoint	
				{
					Posn	{Abs	{FriendlyScoutHomeBase}, 
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},

			NumInWing	4,
			NumInForm	EncounterList04,
			Duty		DUTYCAP,
			Formation	FORM_FLATBOX,

			Posn	FriendlyFracas04B_Pos =		
					{Abs	EnemyFracas04A_Item,
					 Rel	{Y FT_2000,
							 Bearing	{Random	ANGLES_0Deg,359,ANGLES_1Deg},
							 Range	METRES500
							}
					},

		   	AirItem	FriendlyFracas04B_Item =	
			{
				Side		NAT_FRIEND,
 				Type		FriendlyScoutType00,
				Home		FriendlyScoutHomeBase,
				Squadron	{FriendlyScoutSquad,PS_5,PS_6,PS_7,PS_8},
				MoveCode	ACM_STRAIGHTDIVE,
				Target		EnemyFracas04A_Item,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, FriendlyScoutTactician,FriendlyScoutMrAverage,FriendlyScoutCavalier}},
				Morale		{Random	FriendlyScoutMorale,40,1},
 				Attitude	{
							 Intercept	{FriendlyFracas04B_Pos,EnemyFracas04A_Item},
							 Heading	ANGLES_0Deg,
							 Pitch	ANGLES_0Deg
							}
			}
		}
	};

//---------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_FRACAS5=fracas05.BF,
		Setval	{HeightStepSize, Y {Random 0,3000,1}},
		Setval	{AngleStepSize, Int {Random 0,4,1}},
		Setval	{GlobalSkillMin, FriendlyScoutSkillMin},
		Setval	{GlobalSkillMax, FriendlyScoutSkillMax},
		AirGroup	FriendlyFracas05A_Group =
		{
			Route	FriendlyFracas05_Route =	
			{
				WayPoint	
				{
					Target	CPP,
					Range	MARGIN2,
					Action	wpacnoactionno
				},
				WayPoint	FriendlyFracas05_Wp =		
				{
					Posn	{Abs {CPP},
							 Rel	{Y	{Select -FT_3000,HeightStepSize,FT_1},
									 Intercept	{CWP,CPP},
									 Bearing	{Random	ANGLES_357Deg,AngleStepSize,ANGLES_1Deg},
									 Range	VISINEDGE
									}
							},
					Range	MARGIN,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	{Abs FriendlyFracas05_Wp,
							 Rel	{Intercept	{FriendlyFracas05_Wp,FriendlyScoutHomeBase},
									 Bearing	ANGLES_0Deg,
									 RangePercent	80
									}
							},
					Range	MARGIN,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	{Abs	{FriendlyScoutHomeBase}, 
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	3,
			NumInForm	3,
			Duty		DUTYCAP,

			Posn		{Abs	FriendlyFracas05_Wp,
						 Rel	{Intercept	{FriendlyFracas05_Wp,CPP},
							 	 Bearing	ANGLES_0Deg,
						 	 	 RangePercent 170
								}
						}, 

		   	AirItem	FriendlyFracas05A_Item =	
			{
				Side		NAT_FRIEND,
				Type		FriendlyScoutType00,
				Home		FriendlyScoutHomeBase,
				Squadron	{FriendlyScoutSquad,PS_5,PS_6,PS_7,PS_8},
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, FriendlyScoutTactician,FriendlyScoutMrAverage,FriendlyScoutCavalier}},
				Morale		{Random	FriendlyScoutMorale,40,1}
			}
		},
//Can't chain them cos they're friendly and so won't be spotted, so put them in straight
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup	
		{
			Route	
			{
				WayPoint	
				{
					Posn	{Abs	FriendlyFracas05_Wp},
					Action	wpacnoactionno,
					Range	MARGIN
				},
				WayPoint	
				{
					Posn	{Abs FriendlyFracas05_Wp,
							 Rel	{Intercept	{FriendlyFracas05_Wp,EnemyScoutHomeBase},
									 Bearing	ANGLES_0Deg,
									 RangePercent	80
									}
							},
					Range	MARGIN,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	{Abs	{FriendlyScoutHomeBase}, 
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	6,
			NumInForm	18,
			Duty		DUTYCAP,

					Posn	{Abs	FriendlyFracas05A_Item,
							 Rel	{Intercept	{CPP,FriendlyFracas05A_Item},
						 	 		 Bearing	ANGLES_0Deg,
						 	 		 Range	{Select	METRES1000,1,METRES500}
									}
							},
		   	AirItem	
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_COMBAT,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1},
				Target		FriendlyFracas05A_Item	
			}
		}
	};

//---------------------------------------------------------------------------
	BattleField
	{
		FileName	BFCH_FRACAS5 = cbfrac05.BF,
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup	
		{
			Route	
			{
				WayPoint	
				{
					Posn	{Abs	FriendlyFracas05_Wp},
					Action	wpacnoactionno,
					Range	MARGIN
				},
				WayPoint	
				{
					Posn	{Abs FriendlyFracas05_Wp,
							 Rel	{Intercept	{FriendlyFracas05_Wp,EnemyScoutHomeBase},
									 Bearing	ANGLES_0Deg,
									 RangePercent	80
									}
							},
					Range	MARGIN,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	{Abs	{FriendlyScoutHomeBase}, 
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	6,
			NumInForm	12,
			Duty		DUTYCAP,

					Posn	{Abs	{CPP},
							 Rel	{Intercept	{FriendlyFracas05_Wp,CPP},
						 	 		 Bearing	ANGLES_0Deg,
						 	 		 Pitch		ANGLES_0Deg,
						 	 		 Range		VISINEDGE
									}
							},
		   	AirItem	
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	ACM_STRAIGHTANDLEVEL,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1},
				Target		FriendlyFracas05A_Item	
			}
		}
	};

//---------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_FRACAS6				=EVfrac06.BF,
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup	EnemyFracas06A_Group =
		{
			Route	EnemyFracas06_Route =			
			{
				WayPoint	EnemyFracas06_WP00 =	
				{
					Posn	{Abs	{CWP},
							 Rel	{Intercept	{EnemyScoutHomeBase,CWP},
									 Bearing	ANGLES_0Deg,
									 Range	{Random	METRES4000,4000,METRES01}
									}
							},
					Action	wpacnoactionno,
					Range	MARGIN
				},
				WayPoint	EnemyFracas06_WP01 =	
				{
					Posn	{Abs EnemyFracas06_WP00,
							 Rel	{Intercept	{EnemyScoutHomeBase,EnemyFracas06_WP00},
						 	 		 Bearing	{Random ANGLES_270Deg,180,ANGLES_1Deg},
						 	 		 Range		{Random	METRES2000,2000,METRES01}
									}
							},
					Action	wpacnoactionno,
					Range	MARGIN
				},
				WayPoint	
				{
					Posn	{Abs EnemyFracas06_WP01,
							 Rel	{Intercept	{EnemyFracas06_WP01,EnemyScoutHomeBase},
									 Bearing	ANGLES_0Deg,
									 RangePercent	80
									}
							},
					Range	MARGIN,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyScoutHomeBase}, 
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	6,
			NumInForm	EncounterList12,
			Duty		DUTYCAP,

					Posn	{Abs {CPP},
							 Rel	{Intercept	{CPP,EnemyScoutHomeBase},
						 	 		 Bearing	{Random	ANGLES_330Deg,60,ANGLES_1Deg},
						 	 		 Range		{Random	VISINEDGE,VISBOUNDARYSIZE,METRES01}
									}
							},

		   	AirItem	EnemyFracas06A_Item =
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1}
			}
		},
		Setval	{GlobalSkillMin, EnemyChargeSkillMin},
		Setval	{GlobalSkillMax, EnemyChargeSkillMax},
		AirGroup	
		{
			Route	
			{
				WayPoint	
				{
					Posn	{Abs	{EnemyChargeHomeBase}, 
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	6,
			NumInForm	EncounterList10,
			Duty		DUTYCAP,
//FIXME			Duty		DUTYCLOSEESCORT,

					Posn	{Abs EnemyFracas06A_Item,
							 Rel	{Intercept	{EnemyFracas06A_Item,CWP},
						 	 		 Bearing	{Random	ANGLES_135Deg,90,ANGLES_1Deg},
						 	 		 Range		{Random	METRES400,200,METRES01}
									}
							},

		   	AirItem	
			{
				Side		NAT_ENEMY,
				Type		EnemyChargeType00,
				Squadron	{EnemyChargeSquad},
				Home		EnemyChargeHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{Random SKILL_VETERAN,SKILL_REGULAR,SKILL_POOR},
				Character	EnemyScoutCharacter,
				Morale		EnemyScoutMorale,
				Leader		EnemyFracas06A_Item
			}
		},
		Setval	{GlobalSkillMin, FriendlyScoutSkillMin},
		Setval	{GlobalSkillMax, FriendlyScoutSkillMax},
		AirGroup	FriendlyFracas06A_Group =
		{
			Route	FriendlyFracas06_Route =	
			{
				WayPoint	FriendlyFracas06_WP00 =		
				{
					Posn		{Abs	{CWP}},
					Action	wpacnoactionno,
					Range	MARGIN
				},
				WayPoint	
				{
					Posn	{Abs FriendlyFracas06_WP00,
							 Rel	{Intercept	{FriendlyFracas06_WP00,FriendlyScoutHomeBase},
									 Bearing	ANGLES_0Deg,
									 RangePercent	80
									}
							},
					Range	MARGIN,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyScoutHomeBase}, 
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	6,
			NumInForm	EncounterList08,
			Duty		DUTYCAP,

					Posn	{Abs FriendlyFracas06_WP00,
							 Rel	{Intercept	{FriendlyFracas06_WP00,FriendlyScoutHomeBase},
									 Bearing	{Random	ANGLES_350Deg,20,ANGLES_1Deg},
									 Range	VISINEDGE
									}
							},

		   	AirItem	FriendlyFracas06A_Item =	
			{
				Side		NAT_FRIEND,
				Type		FriendlyScoutType00,
				Home		FriendlyScoutHomeBase,
				Squadron	{FriendlyScoutSquad,PS_5,PS_6,PS_7,PS_8},
				MoveCode	AUTO_FOLLOWWP,
				Target		EnemyFracas06A_Item,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, FriendlyScoutTactician,FriendlyScoutMrAverage,FriendlyScoutCavalier}},
				Morale		{Random	FriendlyScoutMorale,40,1}
			}
		}
	};

//---------------------------------------------------------------------------
	BattleField
	{					  
		FileName	BFCH_ENEMYFRACASTOPCOVER = cbfrac01.BF,
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup	
		{
			Route	EnemyFracas01_Route,

			NumInWing	6,
			NumInForm	EncounterList08,
			Duty		DUTYCAP,

			Posn		{Abs	{CPP},
						 Abs	{Y CloudBase},
						 Rel	{Bearing	{Random	ANGLES_0Deg,359,ANGLES_1Deg},
								 Range		{Random	METRES100,300,METRES01}
								}
						},

		   	AirItem	
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Target		CPP,
				Leader		EnemyFracas01A_Item,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1}
			}
		}
	};

//---------------------------------------------------------------------------
//ENEMYFRACASBACKUP,	 CBFRAC02.BF,
//In the distance.

	BattleField
	{
		FileName	BFCH_ENEMYFRACASBACKUP = cbfrac02.BF,
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup	
		{
			Route	
			{
				WayPoint	
				{
					Posn		{Abs	{CPP}},
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyScoutHomeBase}, 
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	6,
			NumInForm	EncounterList04,
			Duty		DUTYCAP,

			Posn		{Abs	{CPP},
						 Rel	{Y {Random	METRES800,10,METRES20},
								 Intercept	{CPP,EnemyScoutHomeBase},
							 	 Bearing	{Random ANGLES_270Deg,ANGLES_180Deg},
							 	 Range	{Random	METRES4000,METRES1000}
								}
						},

		   	AirItem	
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1},
				Target		CPP
			}
		}
	};

//---------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_FRACAS7=EVfrac08.BF,

		Setval	{GlobalSkillMin, FriendlyScoutSkillMin},
		Setval	{GlobalSkillMax, FriendlyScoutSkillMax},
		AirGroup
		{
			Route
			{
				WayPoint	EVFrac07_WP00 =	
				{
					Posn	{Abs	{CPP},
							 Rel	{Y {Random -FT_2000,2000,FT_1},
									 Intercept	{CPP,CWP},
 							 	 	 Bearing	{Random ANGLES_270Deg,180,ANGLES_1Deg},
								 	 Range		VISINEDGE
									}
							},
					Action	wpacnoactionno,
					Range	MARGIN
				},
				WayPoint	
				{
					Posn	{Abs	EVFrac07_WP00,
							 Rel	{Intercept	{EVFrac07_WP00,FriendlyScoutHomeBase},
									 Bearing	ANGLES_0Deg,
									 RangePercent	80
									}
							},	
					Action	wpacnoactionno,
					Range	MARGIN
				},
				WayPoint	
				{
					Posn	{Abs	{FriendlyScoutHomeBase}, 
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	4,
			NumInForm	EncounterList04,
			Duty		DUTYCAP,
			Formation	FORM_FLATBOX,
			
			Posn		{Abs	EVFrac07_WP00},

		   	AirItem	FriendlyFracas07A_Item =	
			{
				Side		NAT_FRIEND,
				Type		FriendlyScoutType00,
				Home		FriendlyScoutHomeBase,
				Squadron	{FriendlyScoutSquad,PS_5,PS_6,PS_7,PS_8},
				MoveCode	AUTO_COMBAT,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, FriendlyScoutTactician,FriendlyScoutMrAverage,FriendlyScoutCavalier}},
				Morale		{Random	FriendlyScoutMorale,40,1}
			}
		},
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup 
		{
 			Route
 			{
  				WayPoint
  				{
  					Posn	{Abs	{CPP}},
  					Action	wpacnoactionno,
  					Range	HALFSTANDARDTRIGGER
  				},
 				WayPoint	
 				{						   
 					Posn	{Abs	{EnemyScoutHomeBase}, 
 						 	Abs	{Y FT_EnterLandingPattern}
 							},
 					Action	wpalandingno,
 					Range	DistEnterLandingPattern
 				}
 			},
			NumInWing	4,
			NumInForm	EncounterList04,
			Duty		DUTYCAP,
			Formation	FORM_FLATBOX,


			Posn	EnemyFracas07A_Pos =	
					{Abs	FriendlyFracas07A_Item,
					 Rel	{Y FT_2000,
							 Bearing	{Random	ANGLES_0Deg,359,ANGLES_1Deg},
							 Range	METRES300
							}
					},

		   	AirItem	EnemyFracas07A_Item =
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	ACM_STRAIGHTDIVE,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1},
				Target		FriendlyFracas07A_Item,
				Attacker	FriendlyFracas07A_Item,
 				Attitude	{
							 Intercept	{EnemyFracas07A_Pos,FriendlyFracas07A_Item},
							 Heading	ANGLES_0Deg,
							 Pitch	ANGLES_0Deg
							}
			}
		},
		Setval	{GlobalSkillMin, FriendlyScoutSkillMin},
		Setval	{GlobalSkillMax, FriendlyScoutSkillMax},
		AirGroup 
		{
   			Route
			{
				WayPoint
				{
					Posn	{Abs	{CPP},
							 Rel	{Y {Random -FT_2000,2000,FT_1},
									 Intercept	{CPP,CWP},
 							 	 	 Bearing	{Random ANGLES_270Deg,180,ANGLES_1Deg},
								 	 Range		VISINEDGE
									}
							},
					Action	wpacnoactionno,
					Range	MARGIN
				},
				WayPoint	
				{
					Posn	{Abs	{FriendlyScoutHomeBase}, 
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},

			NumInWing	4,
			NumInForm	EncounterList04,
			Duty		DUTYCAP,
			Formation	FORM_FLATBOX,

			Posn	FriendlyFracas07B_Pos =		
					{Abs	FriendlyFracas07A_Item,
					 Rel	{Y FT_200,
							 Bearing	{Random	ANGLES_0Deg,359,ANGLES_1Deg},
							 Range	METRES200
							}
					},

		   	AirItem	FriendlyFracas07B_Item =	
			{
				Side		NAT_FRIEND,
 				Type		FriendlyScoutType00,
				Home		FriendlyScoutHomeBase,
				Squadron	{FriendlyScoutSquad,PS_5,PS_6,PS_7,PS_8},
				MoveCode	ACM_STRAIGHTDIVE,
				Target		EnemyFracas07A_Item,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, FriendlyScoutTactician,FriendlyScoutMrAverage,FriendlyScoutCavalier}},
				Morale		{Random	FriendlyScoutMorale,40,1},
 				Attitude	{
							 Intercept	{FriendlyFracas07B_Pos,EnemyFracas07A_Item},
							 Heading	ANGLES_0Deg,
							 Pitch	ANGLES_0Deg
							}
			}
		},
		Setval	{GlobalSkillMin, FriendlyScoutSkillMin},
		Setval	{GlobalSkillMax, FriendlyScoutSkillMax},
		AirGroup	
		{
			Route
			{
				WayPoint
				{
					Posn	{Abs	{CPP},
							 Rel	{Y {Random -FT_4000,4000,FT_1},
									 Intercept	{CPP,CWP},
 							 	 	 Bearing	{Random ANGLES_270Deg,180,ANGLES_1Deg},
								 	 Range		VISOUTEDGE
									}
							},
					Action	wpacnoactionno,
					Range	MARGIN
				},
				WayPoint	
				{
					Posn	{Abs	{FriendlyScoutHomeBase}, 
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},

			NumInWing	6,
			NumInForm	EncounterList03,
			Duty		DUTYCAP,

			Posn	BrianMay_Pos =	
					{Abs	EnemyFracas07A_Item,
					 Rel	{Y FT_200,
							 Bearing	{Random	ANGLES_0Deg,359,ANGLES_1Deg},
							 Range	METRES200
							}
					},

		   	AirItem	
			{
				Side		NAT_FRIEND,
				Type		FriendlyScoutType00,
				Home		FriendlyScoutHomeBase,
				Squadron	{FriendlyScoutSquad,PS_5,PS_6,PS_7,PS_8},
				MoveCode	ACM_STRAIGHTANDLEVEL,			
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, FriendlyScoutTactician,FriendlyScoutMrAverage,FriendlyScoutCavalier}},
				Morale		{Random	FriendlyScoutMorale,40,1},
				Target		EnemyFracas07A_Item,
 				Attitude	{
							 Intercept	{BrianMay_Pos,EnemyFracas07A_Item},
							 Heading	ANGLES_0Deg,
							 Pitch	ANGLES_0Deg
							}
			}
		}
	};

//---------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_ENEMYSCOUTS00=EVagrs00.BF,
		Setval	{HeightStepSize,Int {Random 0,60,100}},
		Setval	{RandAngle,Bearing {Random ANGLES_225Deg,2,ANGLES_135Deg}},

		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup	EnemyAggresivePatrolGroup00 =	
		{
			Route	EnemyAggresivePatrolRoute00 =
			{
				WayPoint	EnemyAggresivePatrolWaypoint00 =
				{
					Posn	{Abs	{CPP},
							 Rel	{Y {Select	-FT_4000,HeightStepSize,FT_1},
									 Intercept	{CWP, CPP},
									 Bearing	{Random	RandAngle,135,ANGLES_1Deg},
								 	 Range		VISINEDGE
									}
							},
					Action	wpacnoactionno,
					Range	MARGIN
				},
				WayPoint
				{
					Posn	{Abs	EnemyAggresivePatrolWaypoint00,
							 Rel	{Intercept	{CPP,CWP},	
						 			 Bearing	ANGLES_0Deg,
						 			 Range	VISINEDGE
									}
							},
					Action	wpacnoactionno,
					Range	MARGIN
				},
				WayPoint
				{
					Posn	{Abs	EnemyAggresivePatrolWaypoint00,
							 Rel	{Intercept	{EnemyAggresivePatrolWaypoint00,EnemyScoutHomeBase},	
						 			 Bearing	ANGLES_0Deg,
						 			 RangePercent	80
									}
							},
					Action	wpacnoactionno,
					Range	MARGIN
				},
				WayPoint
				{
					Posn	{Abs	{EnemyScoutHomeBase},	
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	4,
			NumInForm	EncounterList04,
			Duty		DUTYCAP,

			Posn		{Abs	{CPP},
						 Rel	{Y {Select	-FT_4000,HeightStepSize,FT_1},
								 Intercept	{CPP, CWP},
								 Bearing	{Random	RandAngle,135,ANGLES_1Deg},
							 	 Range	VISINEDGE
								}
						},

		   	AirItem	EnemyAggresivePatrolItem00	=
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1}
			}
		}
	};

//---------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_ENEMYSCOUTS01=EVagrs01.BF,
		Setval	{HeightStepSize,Int {Random 0,60,100}},
		Setval	{RandAngle,Bearing {Random ANGLES_225Deg,2,ANGLES_135Deg}},

		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup	EnemyAggresivePatrolGroup01 =	
		{
			Route	EnemyAggresivePatrolRoute01 =
			{
				WayPoint	EnemyAggresivePatrolWaypoint01 =
				{
					Posn	{Abs	{CPP},
							 Rel	{Y {Select	-FT_4000,HeightStepSize,FT_1},
									 Intercept	{CWP, CPP},
									 Bearing	{Random	RandAngle,135,ANGLES_1Deg},
								 	 Range		VISINEDGE
									}
							},
					Action	wpacnoactionno,
					Range	MARGIN
				},
				WayPoint
				{
					Posn	{Abs	EnemyAggresivePatrolWaypoint01,
							 Rel	{Intercept	{CPP,CWP},	
						 			 Bearing	ANGLES_0Deg,
						 			 Range	VISINEDGE
									}
							},
					Action	wpacnoactionno,
					Range	MARGIN
				},
				WayPoint
				{
					Posn	{Abs	EnemyAggresivePatrolWaypoint01,
							 Rel	{Intercept	{EnemyAggresivePatrolWaypoint01,EnemyScoutHomeBase},	
						 			 Bearing	ANGLES_0Deg,
						 			 RangePercent	80
									}
							},
					Action	wpacnoactionno,
					Range	MARGIN
				},
				WayPoint
				{
					Posn	{Abs	{EnemyScoutHomeBase},	
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	4,
			NumInForm	EncounterList08,
			Duty		DUTYCAP,
			Formation	SQUAD_BAIT,

			Posn		{Abs	{CPP},
						 Rel	{Y {Select	-FT_4000,HeightStepSize,FT_1},
								 Intercept	{CPP, CWP},
								 Bearing	{Random	RandAngle,135,ANGLES_1Deg},
							 	 Range	VISINEDGE
								}
						},

		   	AirItem	EnemyAggresivePatrolItem01	=
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1}
			}
		}
	};
	
//---------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_ENEMYSCOUTS02=EVagrs03.BF,
		Setval	{HeightStepSize,Int {Random 0,5000,1}},
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup	
		{
			Route	
			{
				WayPoint	
				{
					Posn	{Abs	{CPP},
							 Rel	{Y {Select	-FT_2500,HeightStepSize,FT_1},
									 Intercept	{CPP, EnemyObjective},
									 Bearing	ANGLES_0Deg,
								 	 RangePercent	100
									}
							},
					Action	wpacnoactionno,
					Range	MARGIN
				},
				WayPoint	
				{
					Posn	{Abs	{CPP},
							 Rel	{Y {Select	-FT_2500,HeightStepSize,FT_1},
									 Intercept	{CPP, EnemyScoutHomeBase},
									 Bearing	ANGLES_0Deg,
								 	 RangePercent	100
									}
							},
					Action	wpacnoactionno,
					Range	MARGIN
				},
				WayPoint
				{
					Posn	{Abs	{EnemyScoutHomeBase},	
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	6,
			NumInForm	EncounterList04,
			Duty		DUTYCAP,
			Formation	FORM_V,

			Posn		{Abs	{CPP},
						 Rel	{Y {Select	-FT_2500,HeightStepSize,FT_1},
								 Intercept	{CPP, EnemyScoutHomeBase},
								 Bearing	ANGLES_0Deg,
							 	 Range	{Random	VISINEDGE,VISBOUNDARYSIZE,METRES01}
								}
						},

		   	AirItem
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1}
			}
		}
	};
//---------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_ENEMYSCOUTSPARALLEL=EVpara00.BF,
		Setval	{AngleStepSize,Int {Random 0,2,1}},
		Setval	{HeightStepSize,Int {Random 0,400,1}},
		Setval	{RangeStepSize,Int {Random 0,VISBOUNDARYSIZE,1}},

		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup	
		{
			Route	
			{
				WayPoint	
				{
					Posn	{Abs	{CPP},
							 Rel	{Y	{Select -FT_2000,HeightStepSize,FT_10},
								 	 Intercept	{CPP,CWP},
							 	 	 Bearing	{Select ANGLES_150Deg,AngleStepSize,ANGLES_60Deg},
				 			 		 Range		{Select VISINEDGE,VISBOUNDARYSIZE,METRES01}
								}
							},
					Action	wpacnoactionno,
					Range	MARGIN
				},
				WayPoint
				{
					Posn	{Abs	{CPP},
							 Rel	{Y	{Select -FT_2000,HeightStepSize,FT_10},
									 Intercept	{CPP,EnemyScoutHomeBase},
						 			 Bearing	ANGLES_0Deg,
						 			 RangePercent	80
									}
							},
					Action	wpacnoactionno,
					Range	MARGIN
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyScoutHomeBase}, 
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	8,
			NumInForm	6,
//fixme			NumInForm	EncounterList04,
			Duty		DUTYCAP,

			Posn	{Abs	{CPP},
					 Rel	{Y	{Select -FT_2000,HeightStepSize,FT_10},
					 		 Intercept	{CPP,CWP},
				 			 Bearing	{Select ANGLES_30Deg,AngleStepSize,ANGLES_300Deg},
				 			 Range		{Select VISINEDGE,VISBOUNDARYSIZE,METRES01}
							}
					},

		   	AirItem	
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1}
			}
		}
	};

//---------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_ENEMYCHARGEDAMAGED=EVdamg00.BF,

		Setval{HeightStepSize,Int {Random 0,50,100}},
		Setval	{GlobalSkillMin, EnemyChargeSkillMin},
		Setval	{GlobalSkillMax, EnemyChargeSkillMax},
		AirGroup	
		{
			Route	
			{
				WayPoint	
				{
					Posn	{Abs	{CPP},
							 Rel	{Y	{Random	-FT_4000,HeightStepSize,FT_1},
							 		 Intercept	{CPP, EnemyChargeHomeBase},
						 	 		 Bearing	ANGLES_0Deg,
						 			 RangePercent	60
									}
							},
					Action	wpacnoactionno,
					Range	MARGIN
				},
				WayPoint
				{
					Posn	{Abs	{EnemyChargeHomeBase},	
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	1,
			NumInForm	1,
			Duty		DUTYRECONN,

					Posn	{Abs	{CPP},
							 Rel	{Y	{Random	-FT_4000,HeightStepSize,FT_1},
									 Intercept	{EnemyChargeHomeBase,CPP},
									 Bearing	{Random ANGLES_315Deg,90,ANGLES_1Deg},
							 		 Range	{Random	VISINEDGE,VISBOUNDARYSIZE,METRES01}
									 
									}
							},
		   	AirItem	
			{
				Side		NAT_ENEMY,
				Type		EnemyChargeType00,
				Squadron	{EnemyChargeSquad},
				Home		EnemyChargeHomeBase,
				MoveCode	AUTO_FOLLOWWP,
//DAMAGE IS IN H\3DINSTR.H
				Damage		0x12,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1}
			}
		}
	};

//---------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_ENEMYSCOUTDAMAGED=EVdamg01.BF,

		Setval{HeightStepSize,Int {Random 0,50,100}},
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup	
		{
			Route	
			{
				WayPoint	
				{
					Posn	{Abs	{CPP},
							 Rel	{Y	{Random	-FT_4000,HeightStepSize,FT_1},
							 		 Intercept	{CPP, EnemyScoutHomeBase},
						 	 		 Bearing	ANGLES_0Deg,
						 			 RangePercent	60
									}
							},
					Action	wpacnoactionno,
					Range	MARGIN
				},
				WayPoint
				{
					Posn	{Abs	{EnemyScoutHomeBase},	
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	1,
			NumInForm	1,
			Duty		DUTYCAP,

					Posn	{Abs	{CPP},
							 Rel	{Y	{Random	-FT_4000,HeightStepSize,FT_1},
									 Intercept	{EnemyScoutHomeBase,CPP},
									 Bearing	{Random ANGLES_315Deg,90,ANGLES_1Deg},
							 		 Range	{Random	VISINEDGE,VISBOUNDARYSIZE,METRES01}
									 
									}
							},
		   	AirItem	
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1},
//DAMAGE IS IN H\3DINSTR.H
				Damage		0x12
			}
		}
	};

//---------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_ENEMYSCOUTSKIM			=EVskim00.BF,
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup	
		{
			Route	
			{
				WayPoint
				{
					Posn	{Abs	{EnemyScoutHomeBase},	
						 	Abs	{Y -FT_200}
							},
					Action	wpacnoactionno,
					Range	STANDARDTRIGGER
				},
				WayPoint
				{
					Posn	{Abs	{EnemyScoutHomeBase},	
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	1,
			NumInForm	1,
			Duty		DUTYCAP,

					Posn	{Abs	{CPP},
							 Abs	{Y -FT_200},
							 Rel	{Intercept	{CPP,CWP},
									 Bearing	{Random ANGLES_270Deg,180,ANGLES_1Deg},
							 		 Range	{Random	VISINEDGE,VISBOUNDARYSIZE,METRES01}
									}
							},
		   	AirItem	
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1},
//DAMAGE IS IN H\3DINSTR.H
				Damage		0x12
			}
		}
	};

//---------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_ENEMYACESURPRISE =EVaces00.BF,

		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup	
		{
			Route	
			{
				WayPoint	
				{
					Posn	{Abs	{CPP},
							 Rel	{Intercept	{CPP,CWP},
									 Bearing	ANGLES_0Deg,
									 Range	METRES500
									}
							},
					Range	MARGIN,
					Action	wpacnoactionno
				},
				WayPoint
				{
					Posn	{Abs	{EnemyScoutHomeBase},
							 Abs	{Y	FT_5000}
							},
					Range	STANDARDTRIGGER,
					Action	wpacnoactionno
				},
				WayPoint
				{
					Posn	{Abs	{EnemyScoutHomeBase},
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	1,
			NumInForm	1,
			Duty		DUTYCAP,

			Posn		{Abs	{CPP}, 
//fix me						 Rel	{Intercept	{CPP, EnemyScoutHomeBase},
//						 		 Bearing	{Random ANGLES_359Deg,2,ANGLES_1Deg},
						 Rel	{Bearing ANGLES_180Deg,
								 Pitch	ANGLES_0Deg,
						 		 Range	JUMPINBAND
								}
						}, 
		   	AirItem	
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_COMBAT,
				Skill		SKILL_HERO,
				Character	EnemyScoutTactician,
				Morale		MORALE_HIGH,
				Target		CPP
			}
		}
	};

//---------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_ENEMYLOWLEVELSEARCH=EV_low00.BF,
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup	
		{
			Route	BluAttacksFriendHomeBase_Route =
			{
				WayPoint	
				{
					Target	EnemyObjective,
					Posn	{
							Abs	{Y	FT_Straffe}
							},
					Range	BEGINSTRAFFERANGE,
					Action	wpdivebombstraffeno
				},
				WayPoint
				{
					Posn	{Abs	{EnemyObjective},
							 Abs	{Y	FT_5000},
							 Rel	{Intercept	{EnemyObjective,EnemyScoutHomeBase},
						 			 Bearing	{Random	ANGLES_345Deg,2,ANGLES_60Deg},
						 			 RangePercent	10
									}
							},
					Action	wpacnoactionno,
					Range	MARGIN
				},
				WayPoint
				{
					Posn	{Abs	{EnemyScoutHomeBase},
						 	 Abs	{Y FT_5000}
							},
					Action	wpacnoactionno,
					Range	STANDARDTRIGGER
				},
				WayPoint
				{
					Posn	{Abs	{EnemyScoutHomeBase},
						 	 Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},

			NumInWing	6,
			NumInForm	EncounterList01,
			Duty		DUTYCAP,

			Posn		{Abs	{CPP}, 
						 Abs	{Y	FT_Straffe},
						 Rel	{Intercept	{CPP,EnemyObjective},
								 Bearing	{Random ANGLES_300Deg,120,ANGLES_1Deg},
							 	 Range	VISINEDGE
								}
						}, 
		   	AirItem	
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		SKILL_ACE,
				Character	EnemyScoutCavalier,
				Morale		MORALE_HIGH
			}
		}
	};

//---------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_FRIENDLYSCOUTBOUNCED00			=EVrscu03.BF,
		Setval	{HeightStepSize,Int {Random 0,40,100}},
		Setval	{AngleStepSize,Int {Random 0,2,1}},	
		Setval	{RandAngle,Int {Random ANGLES_0Deg,90,ANGLES_1Deg}},

		Setval	{GlobalSkillMin, FriendlyScoutSkillMin},
		Setval	{GlobalSkillMax, FriendlyScoutSkillMax},
		AirGroup	
		{
			Route
			{
				WayPoint	
				{
					Posn	{Abs	{CPP},
							 Rel	{Y	{Select	-FT_4000,HeightStepSize,FT_1},
									 Intercept	{CPP,CWP},
							     	 Bearing	ANGLES_0Deg,
				 					 Range	{Select	VISINEDGE,1,VISINEDGE}
									}
							},
					Range	MARGIN,
					Action	wpacnoactionno
				},
				WayPoint		
				{
					Posn	{Abs	{FriendlyScoutHomeBase}, 
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	4,
			NumInForm	EncounterList04,
			Duty		DUTYCAP,

			Posn		{Abs	{CPP},
						 Rel	{Y	{Select	-FT_4000,HeightStepSize,FT_1},
								 Intercept	{CPP,CWP},
							     Bearing	{Select	RandAngle,AngleStepSize,ANGLES_270Deg},
				 				 Range		VISINEDGE
								}
						},

		   	AirItem	FriendlyScoutInDanger01 =
			{
				Side		NAT_FRIEND,
				Type		FriendlyScoutType00,
				Home		FriendlyScoutHomeBase,
				Squadron	{FriendlyScoutSquad,PS_5,PS_6,PS_7,PS_8},
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, FriendlyScoutTactician,FriendlyScoutMrAverage,FriendlyScoutCavalier}},
				Morale		{Random	FriendlyScoutMorale,40,1}
			}
		},
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup
		{
			Route
			{
				WayPoint	
				{
					Posn	{Abs	FriendlyScoutInDanger01},
					Action	wpacnoactionno,
					Range	MARGIN
				},
				WayPoint		
				{
					Posn	{Abs	FriendlyScoutInDanger01,
							 Rel	{Intercept	{FriendlyScoutInDanger01,EnemyScoutHomeBase},
									 Bearing	ANGLES_0Deg,
				 					 RangePercent	100
									}
							},
					Action	wpacnoactionno,
					Range	STANDARDTRIGGER
				},
				WayPoint		
				{
					Posn	{Abs	{EnemyScoutHomeBase}, 
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	6,
			NumInForm	EncounterList06,
			Duty		DUTYCAP,

			Posn		{Abs	{CPP},
						 Rel	{Y	{Select	-FT_3000,HeightStepSize,FT_1},
								 Intercept	{CPP,FriendlyScoutInDanger01},
							 	 Bearing	{Select	ANGLES_30Deg,AngleStepSize,ANGLES_300Deg},
							 	 Range	VISINEDGE 
								}
						},

		   	AirItem		
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_COMBAT,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1},
				Target		FriendlyScoutInDanger01				
			}
		}
	};

//---------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_FRIENDLYCHARGEBOUNCED00		=EVrscu05.BF,
		Setval	{HeightStepSize,Int {Random 0,40,100}},
		Setval	{AngleStepSize,Int {Random 0,2,1}},	
		Setval	{RandAngle,Int {Random ANGLES_0Deg,90,ANGLES_1Deg}},

		Setval	{GlobalSkillMin, FriendlyChargeSkillMin},
		Setval	{GlobalSkillMax, FriendlyChargeSkillMax},
		AirGroup	FriendlyChargeBounced00_GroupA	=
		{
			Route	
			{
				WayPoint	FriendlyChargeBounced_WP00=
				{
					Posn	{Abs	{CPP},
							 Rel	{Y	{Select	-FT_4000,HeightStepSize,FT_1},
									 Intercept	{CPP,CWP},
									 Bearing	ANGLES_0Deg,
				 					 Range	{Select	VISINEDGE,1,VISINEDGE}
								}
							},
					Range	MARGIN,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	{Abs	{FriendlyChargeHomeBase}, 
						 	 Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	6,
			NumInForm	EncounterList02,

			Posn		{Abs	{CPP},
						 Rel	{Y	{Select	-FT_4000,HeightStepSize,FT_1},
								 Intercept	{CPP,CWP},
							     Bearing	{Select	RandAngle,AngleStepSize,ANGLES_270Deg},
				 				 Range		VISINEDGE
								}
						},

		   	AirItem	FriendlyChargeInDanger00 =
			{
				Side		NAT_FRIEND,
				Type		FriendlyChargeType00,
				Squadron	{FriendlyChargeSquad},
				Home		FriendlyChargeHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List {Random 6}, SKILL_VETERAN,SKILL_VETERAN,SKILL_REGULAR,SKILL_REGULAR,SKILL_REGULAR,SKILL_POOR},
				Character	FriendlyChargeCharacter,
				Morale		{Random	FriendlyChargeMorale,40,1}
			}
		},
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup	FriendlyChargeBounced00_GroupB =
		{
			Route
			{
				WayPoint	
				{
					Posn	{Abs	FriendlyChargeInDanger00},
					Range	MARGIN,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	{Abs	FriendlyChargeInDanger00,
							 Rel	{Intercept	{CPP, EnemyScoutHomeBase},
									 Bearing	ANGLES_0Deg,
				 					 RangePercent	100
								}
							},
					Range	STANDARDTRIGGER,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyScoutHomeBase}, 
						 	 Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	6,
			NumInForm	EncounterList04,
			Duty		DUTYCAP,

			Posn		{Abs	{CPP},
						 Rel	{Y	{Select	-FT_3000,HeightStepSize,FT_1},
								 Intercept	{CPP,FriendlyChargeInDanger00},
							 	 Bearing	{Select	ANGLES_30Deg,AngleStepSize,ANGLES_300Deg},
							 	 Range	VISINEDGE 
								}
						},
		   	AirItem		
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1},
				Target		FriendlyChargeInDanger00
			}
		}
	};

//---------------------------------------------------------------------------

	BattleField
	{
		FileName	BFEV_FRIENDLYCHARGEBOUNCED01		=EVrscu06.BF,
		Setval	{HeightStepSize,Int {Random 0,40,100}},
		Setval	{AngleStepSize,Int {Random 0,2,1}},	
		Setval	{RandAngle,Int {Random ANGLES_0Deg,90,ANGLES_1Deg}},

		Setval	{GlobalSkillMin, FriendlyChargeSkillMin},
		Setval	{GlobalSkillMax, FriendlyChargeSkillMax},
		AirGroup	FriendlyChargeBounced00_GroupA,
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup	FriendlyChargeBounced00_GroupB,
		Setval	{GlobalSkillMin, FriendlyScoutSkillMin},
		Setval	{GlobalSkillMax, FriendlyScoutSkillMax},
		AirGroup	
		{
			Route	FriendlyChargeBounced_WP00,

			NumInWing	6,
			NumInForm	EncounterList02,

			Posn		{Abs	FriendlyChargeInDanger00},

		   	AirItem	
			{
				Side		NAT_FRIEND,
				Type		FriendlyScoutType00,
				Home		FriendlyScoutHomeBase,
				Squadron	{FriendlyScoutSquad,PS_5,PS_6,PS_7,PS_8},
				MoveCode	AUTO_FOLLOWWP,
				Leader		FriendlyChargeInDanger00,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, FriendlyScoutTactician,FriendlyScoutMrAverage,FriendlyScoutCavalier}},
				Morale		{Random	FriendlyScoutMorale,40,1}
			}
		}
	};

//---------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_RESCUENOVICES			=EVrscu07.BF,
		Setval	{HeightStepSize, Y {Random 0,50,1}},

		Setval	{GlobalSkillMin, FriendlyScoutSkillMin},
		Setval	{GlobalSkillMax, FriendlyScoutSkillMax},
		AirGroup	
		{
			Route	Rescue7_Route =
			{
				WayPoint		
				{
					Posn	{Abs	{CPP},
							 Rel	{Y {Select	-FT_2500,HeightStepSize,FT_1},
									 Intercept	{CPP,FriendlyScoutHomeBase},
						 			 Bearing	ANGLES_0Deg,
						 			 RangePercent	100
									}
							},
					Action	wpacnoactionno,
					Range	STANDARDTRIGGER
				},
				WayPoint	
				{
					Posn	{Abs	{FriendlyScoutHomeBase},
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	2,
			NumInForm	EncounterList06,
			Duty		DUTYCAP,

			Posn		{Abs	{CPP},
						 Rel	{Y {Select	-FT_2500,HeightStepSize,FT_1},
								 Intercept	{CPP,CWP},
						 		 Bearing	{Random	ANGLES_270Deg,180,ANGLES_1Deg},
				 				 Range	VISINEDGE
								}
						},

		   	AirItem	FriendlyRescue7a_Item =
			{
				Side		NAT_FRIEND,
				Type		FriendlyScoutType00,
				Home		FriendlyScoutHomeBase,
				Squadron	{FriendlyScoutSquad,PS_5,PS_6,PS_7,PS_8},
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, FriendlyScoutTactician,FriendlyScoutMrAverage,FriendlyScoutCavalier}},
				Morale		{Random	FriendlyScoutMorale,40,1}
			}
		},
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup
		{
			Route
			{
				WayPoint	
				{
					Posn	{Abs	FriendlyRescue7a_Item},
					Action	wpacnoactionno,
					Range	MARGIN
				},
				WayPoint		
				{
					Posn	{Abs	{CPP},
							 Rel	{Y {Select	-FT_2500,HeightStepSize,FT_1},
									 Intercept	{CPP,EnemyScoutHomeBase},
						 			 Bearing	ANGLES_0Deg,
						 			 RangePercent	100
									}
							},
					Action	wpacnoactionno,
					Range	STANDARDTRIGGER
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyScoutHomeBase}, 
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	6,
			NumInForm	EncounterList03,
			Duty		DUTYCAP,

			Posn		{Abs	FriendlyRescue7a_Item,
						 Rel	{Bearing	{Random	ANGLES_315Deg,90,ANGLES_1Deg},
								 Y	FT_2000,
								 Range	METRES500 
								}
						},

		   	AirItem	EnemyRescue7a_Item =
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Target		FriendlyRescue7a_Item,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1}
			}
		}
	};

//---------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_ENEMYCHARGEROUT			=EVrscu08.BF,
		Setval	{HeightStepSize, Y {Random 0,40,100}},
		Setval	{GlobalSkillMin, FriendlyChargeSkillMin},
		Setval	{GlobalSkillMax, FriendlyChargeSkillMax},
		AirGroup	
		{
			Route	
			{
				WayPoint	ENEMYCHARGEROUT_WP00=		
				{
					Posn	{Abs	{CPP},
							 Rel	{Y	{Select -FT_2000,HeightStepSize,FT_1},
									 Intercept	{CPP,FriendlyChargeHomeBase},
									 Bearing	ANGLES_0Deg,
									 Range	VISINEDGE
									}
							},
					Action	wpacnoactionno,
					Range	STANDARDTRIGGER
				},
				WayPoint	
				{
					Posn	{Abs	{FriendlyChargeHomeBase}, 
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	6,
			NumInForm	EncounterList03,
			Duty		DUTYCAP,

			Posn		{Abs	{CPP},
						 Rel	{Y	{Select -FT_4000,HeightStepSize,FT_1},
				 				 Intercept	{ENEMYCHARGEROUT_WP00,CPP},
								 Bearing	{Random	ANGLES_270Deg,180,ANGLES_1Deg},
				 				 Range	VISINEDGE
								}
						},

		   	AirItem	FriendlyRescue8a_Item =	
			{
				Side		NAT_FRIEND,
				Type		FriendlyChargeType00,
				Home		FriendlyChargeHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List {Random 6}, SKILL_VETERAN,SKILL_VETERAN,SKILL_REGULAR,SKILL_REGULAR,SKILL_REGULAR,SKILL_POOR},
				Character	FriendlyChargeCharacter,
				Morale		{Random	FriendlyChargeMorale,40,1}
			}
		},
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup
		{
			Route
			{
				WayPoint	
				{
					Posn	{Abs	FriendlyRescue8a_Item},
					Action	wpacnoactionno,
					Range	MARGIN
				},
//DeadCode MS 03Oct96 				WayPoint		
//DeadCode MS 03Oct96 				{
//DeadCode MS 03Oct96 					Posn	{Abs	FriendlyRescue8a_Item,
//DeadCode MS 03Oct96 							 Rel	{Intercept	{FriendlyRescue8a_Item,EnemyChargeHomeBase},
//DeadCode MS 03Oct96 									 Bearing	ANGLES_0Deg,
//DeadCode MS 03Oct96 									 RangePercent	100
//DeadCode MS 03Oct96 									}
//DeadCode MS 03Oct96 							},
//DeadCode MS 03Oct96 					Action	wpacnoactionno,
//DeadCode MS 03Oct96 					Range	STANDARDTRIGGER
//DeadCode MS 03Oct96 				},
				WayPoint	
				{
					Posn	{Abs	{EnemyScoutHomeBase}, 
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	6,
			NumInForm	EncounterList02,
			Duty		DUTYCAP,

			Posn		{Abs	FriendlyRescue8a_Item,
						 Rel	{Y	{Random	FT_0,1000,FT_1},
								 Bearing	{Random	ANGLES_135Deg,90,ANGLES_1Deg},
								 Range	METRES2000
							}
						},

		   	AirItem	
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_COMBAT,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1},
				Target		FriendlyRescue8a_Item
					
			}
		}
	};

//---------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_ENEMYBEATUPGROUND00=EVbeat00.BF,
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Target	EnemyObjective,
					Posn	{
						 	 Abs	{Y FT_BombStraffe}
							},
					Action	wpdivebombstraffeno,
					Range	BEGINBOMBSTRAFFERANGE
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyScoutHomeBase}, 
						 	 Abs	{Y FT_5000}
							},
					Action	wpacnoactionno,
					Range	STANDARDTRIGGER
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyScoutHomeBase}, 
						 	 Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	6,
			NumInForm	EncounterList03,
			Duty		DUTYCAP,

			Posn	{Abs	{EnemyObjective}, 
					 Abs	{Y FT_BombStraffe},
					 Rel	{Intercept	{EnemyObjective, CPP},
							 Bearing {Random ANGLES_90Deg,180,ANGLES_1Deg},
				 	 		 Range	METRES400
							}
					},

		   	AirItem	
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1},
				Bombs		4
			}
		}
	};

//---------------------------------------------------------------------------

	BattleField
	{
		FileName	BFEV_ENEMYBEATUPGROUND01=EVbeat01.BF,
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup	
		{
			Route	
			{
				WayPoint	
				{
					Target	EnemyObjective,
					Posn	{
						 	 Abs	{Y FT_BombStraffe}
							},
					Action	wpdivebombstraffeno,
					Range	BEGINBOMBSTRAFFERANGE
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyScoutHomeBase}, 
						 	 Abs	{Y FT_5000}
							},
					Action	wpacnoactionno,
					Range	STANDARDTRIGGER
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyScoutHomeBase}, 
						 	 Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	6,
			NumInForm	EncounterList03,
			Duty		DUTYCAP,

			Posn	{Abs	{EnemyObjective}, 
					 Abs	{Y FT_BombStraffe},
					 Rel	{Intercept	{EnemyObjective, CPP},
							 Bearing {Random ANGLES_300Deg,2,ANGLES_120Deg},
				 	 		 Range	VISINEDGE
							}
					},

		   	AirItem	
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1},
				Bombs		4
			}
		}
	};

//---------------------------------------------------------------------------

	BattleField
	{
		FileName	BFEV_ENEMYBEATUPGROUND02=EVbeat02.BF,
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup
		{
			Route	
			{
				WayPoint	EVbeat02_WP00=
				{
					Target	EnemyObjective,
					Posn	{
						 	 Abs	{Y FT_BombStraffe}
							},
					Action	wpdivebombstraffeno,
					Range	BEGINBOMBSTRAFFERANGE
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyScoutHomeBase}, 
						 	 Abs	{Y FT_5000}
							},
					Action	wpacnoactionno,
					Range	STANDARDTRIGGER
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyScoutHomeBase}, 
						 	 Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	3,
			NumInForm	EncounterList03,
			Duty		DUTYCAP,

			Posn	{Abs	{EnemyObjective}, 
					 Abs	{Y {Select FT_BombStraffe,1,FT_500}},
					 Rel	{Intercept	{EnemyObjective, CPP},
							 Bearing {Random ANGLES_90Deg,180,ANGLES_1Deg},
				 	 		 Range	METRES400
							}
					},

		   	AirItem	EVbeat02_Item00 =	
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1},
				Bombs		4
			}
		},
		AirGroup
		{
			Route	EVbeat02_WP00,	

			NumInWing	6,
			NumInForm	EncounterList03,
			Duty		DUTYCAP,

			Posn	{Abs	EVbeat02_Item00, 
					 Abs	{Y FT_BombStraffe}
					},

		   	AirItem	
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1},
				Follower	EVbeat02_Item00,	
				Bombs		4
			}
		}
	};

//---------------------------------------------------------------------------

	BattleField
	{
		FileName	BFEV_ENEMYBEATUPGROUND03=EVbeat03.BF
	};

//---------------------------------------------------------------------------

	BattleField
	{
		FileName	BFEV_ENEMYBEATUPGROUND04=EVbeat04.BF,
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Target	EnemyObjective,
					Posn	{
						 	 Abs	{Y FT_BombStraffe}
							},
					Action	wpdivebombstraffeno,
					Range	BEGINBOMBSTRAFFERANGE
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyScoutHomeBase}, 
						 	 Abs	{Y FT_5000}
							},
					Action	wpacnoactionno,
					Range	STANDARDTRIGGER
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyScoutHomeBase}, 
						 	 Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	6,
			NumInForm	EncounterList03,
			Duty		DUTYCAP,

			Posn	{Abs	{EnemyObjective}, 
					 Abs	{Y FT_BombStraffe},
					 Rel	{Intercept	{EnemyObjective, CPP},
							 Bearing {Random ANGLES_90Deg,180,ANGLES_1Deg},
				 	 		 Range	METRES400
							}
					},

		   	AirItem	
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1},
				Bombs		4
			}
		},
		AirGroup	
		{
			Route	
			{
				WayPoint	
				{
					Posn	{Abs	{EnemyScoutHomeBase}, 
						 	 Abs	{Y FT_5000}
							},
					Action	wpacnoactionno,
					Range	STANDARDTRIGGER
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyScoutHomeBase}, 
						 	 Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	3,
			NumInForm	EncounterList03,

			Posn	{Abs	{EnemyObjective}, 
					 Abs	{Y FT_5000}
					},

		   	AirItem	
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1}
			}
		}
	};

//---------------------------------------------------------------------------
//DeadCode MS 01Oct96 //BFEV_ENEMYLOWLEVELATTACK00		
//DeadCode MS 01Oct96 //A cocky scout is preparing to attack your airbase.
//DeadCode MS 01Oct96 
//DeadCode MS 01Oct96 	BattleField
//DeadCode MS 01Oct96 	{
//DeadCode MS 01Oct96 		FileName	BFEV_ENEMYLOWLEVELATTACK00=EVafld00.BF,
//DeadCode MS 01Oct96 		Setval	{GlobalSkillMin, FriendlyScoutSkillMin},
//DeadCode MS 01Oct96 		Setval	{GlobalSkillMax, FriendlyScoutSkillMax},
//DeadCode MS 01Oct96 		AirGroup	CockyScout00 = 	
//DeadCode MS 01Oct96 		{
//DeadCode MS 01Oct96 			Route	
//DeadCode MS 01Oct96 			{
//DeadCode MS 01Oct96 				WayPoint	
//DeadCode MS 01Oct96 				{
//DeadCode MS 01Oct96 					Posn	{Abs 	{FriendlyScoutHomeBase},
//DeadCode MS 01Oct96 						 	 Abs	{Y FT_200}
//DeadCode MS 01Oct96 							},
//DeadCode MS 01Oct96 //					Action	beginstraffingairfield?????,	MARKPROB!!!
//DeadCode MS 01Oct96 					Action	wpacnoactionno,
//DeadCode MS 01Oct96 					Range	MARGIN
//DeadCode MS 01Oct96 				},
//DeadCode MS 01Oct96 				WayPoint	
//DeadCode MS 01Oct96 				{
//DeadCode MS 01Oct96 					Posn	{Abs	{FriendlyScoutHomeBase}, 
//DeadCode MS 01Oct96 						 	 Abs	{Y FT_EnterLandingPattern}
//DeadCode MS 01Oct96 							},
//DeadCode MS 01Oct96 					Action	wpalandingno,
//DeadCode MS 01Oct96 					Range	DistEnterLandingPattern
//DeadCode MS 01Oct96 				}
//DeadCode MS 01Oct96 			},
//DeadCode MS 01Oct96 			NumInWing	1,
//DeadCode MS 01Oct96 			NumInForm	1,
//DeadCode MS 01Oct96 //			Duty		BlowCrapOutOfAirfield,		MARKPROB!!!
//DeadCode MS 01Oct96 			Duty		DUTYCAP,
//DeadCode MS 01Oct96 
//DeadCode MS 01Oct96 			Posn	{Abs	{FriendlyScoutHomeBase}, 
//DeadCode MS 01Oct96 					 Rel	{Bearing	{Random	ANGLES_359Deg},
//DeadCode MS 01Oct96 				 	 Range	{Random MARGIN,2,METRES50},
//DeadCode MS 01Oct96 				 	 Y	{Random	FT_100,10,FT_10}
//DeadCode MS 01Oct96 				 	}
//DeadCode MS 01Oct96 				},
//DeadCode MS 01Oct96 
//DeadCode MS 01Oct96 		   	AirItem	
//DeadCode MS 01Oct96 			{
//DeadCode MS 01Oct96 				Side		NAT_ENEMY,
//DeadCode MS 01Oct96 				Type		FriendlyScoutType00,
//DeadCode MS 01Oct96 				Home		FriendlyScoutHomeBase,
//DeadCode MS 01Oct96 				Squadron	{FriendlyScoutSquad,PS_5,PS_6,PS_7,PS_8},
//DeadCode MS 01Oct96 				MoveCode	AUTO_FOLLOWWP,
//DeadCode MS 01Oct96 				Skill		SKILL_VETERAN
//DeadCode MS 01Oct96 			}
//DeadCode MS 01Oct96 		}
//DeadCode MS 01Oct96 	};
//DeadCode MS 01Oct96 
//DeadCode MS 01Oct96 //---------------------------------------------------------------------------
//DeadCode MS 01Oct96 //BFEV_ENEMYLOWLEVELATTACK01
//DeadCode MS 01Oct96 //A cocky scout is preparing to attack a friendly airbase.
//DeadCode MS 01Oct96 
//DeadCode MS 01Oct96 	BattleField
//DeadCode MS 01Oct96 	{
//DeadCode MS 01Oct96 		FileName	BFEV_ENEMYLOWLEVELATTACK01=EVafld01.BF,
//DeadCode MS 01Oct96 		Setval	{GlobalSkillMin, FriendlyScoutSkillMin},
//DeadCode MS 01Oct96 		Setval	{GlobalSkillMax, FriendlyScoutSkillMax},
//DeadCode MS 01Oct96 		AirGroup	CockyScout01 =	
//DeadCode MS 01Oct96 		{
//DeadCode MS 01Oct96 			Route	
//DeadCode MS 01Oct96 			{
//DeadCode MS 01Oct96 				WayPoint	
//DeadCode MS 01Oct96 				{
//DeadCode MS 01Oct96 					Posn	{Abs 	{MainObjective},
//DeadCode MS 01Oct96 						 	 Abs	{Y FT_200}	
//DeadCode MS 01Oct96 							},
//DeadCode MS 01Oct96 //					Action	beginstraffingairfield?????,	MARKPROB!!!
//DeadCode MS 01Oct96 					Action	wpacnoactionno,
//DeadCode MS 01Oct96 					Range	MARGIN
//DeadCode MS 01Oct96 				},
//DeadCode MS 01Oct96 				WayPoint	
//DeadCode MS 01Oct96 				{
//DeadCode MS 01Oct96 					Posn	{Abs	{EnemyScoutHomeBase}, 
//DeadCode MS 01Oct96 						 	 Abs	{Y FT_EnterLandingPattern}
//DeadCode MS 01Oct96 							},
//DeadCode MS 01Oct96 					Action	wpalandingno,
//DeadCode MS 01Oct96 					Range	DistEnterLandingPattern
//DeadCode MS 01Oct96 				}
//DeadCode MS 01Oct96 			},
//DeadCode MS 01Oct96 			NumInWing	1,
//DeadCode MS 01Oct96 			NumInForm	1,
//DeadCode MS 01Oct96 //			Duty		BlowCrapOutOfAirfield,	MARKPROB!!!
//DeadCode MS 01Oct96 			Duty		DUTYCAP,
//DeadCode MS 01Oct96 
//DeadCode MS 01Oct96 			Posn	{Abs	{MainObjective}, 
//DeadCode MS 01Oct96 					 Rel	{Bearing	{Random	ANGLES_359Deg},
//DeadCode MS 01Oct96 				 	 Range	{Random MARGIN,2,METRES50},
//DeadCode MS 01Oct96 				 	 Y	{Random	FT_100,10,FT_10}
//DeadCode MS 01Oct96 				 	}
//DeadCode MS 01Oct96 				},
//DeadCode MS 01Oct96 
//DeadCode MS 01Oct96 		   	AirItem	     	
//DeadCode MS 01Oct96 			{
//DeadCode MS 01Oct96 				Side		NAT_ENEMY,
//DeadCode MS 01Oct96 				Type		FriendlyScoutType00,
//DeadCode MS 01Oct96 				Home		FriendlyScoutHomeBase,
//DeadCode MS 01Oct96 				Squadron	{FriendlyScoutSquad,PS_5,PS_6,PS_7,PS_8},
//DeadCode MS 01Oct96 				MoveCode	AUTO_FOLLOWWP,
//DeadCode MS 01Oct96 				Skill		SKILL_VETERAN
//DeadCode MS 01Oct96 			}
//DeadCode MS 01Oct96 		}
//DeadCode MS 01Oct96 	};
//DeadCode MS 01Oct96 
//DeadCode MS 01Oct96 //---------------------------------------------------------------------------
//DeadCode MS 01Oct96 //BFEV_ENEMYLOWLEVELATTACK02
//DeadCode MS 01Oct96 //A cocky scout is circling above your base, waiting. Taunting.
//DeadCode MS 01Oct96 
//DeadCode MS 01Oct96 	BattleField
//DeadCode MS 01Oct96 	{
//DeadCode MS 01Oct96 		FileName	BFEV_ENEMYLOWLEVELATTACK02=EVafld02.BF,
//DeadCode MS 01Oct96 		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
//DeadCode MS 01Oct96 		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
//DeadCode MS 01Oct96 		AirGroup	CockyScout02 =		
//DeadCode MS 01Oct96 		{
//DeadCode MS 01Oct96 			Route	
//DeadCode MS 01Oct96 			{
//DeadCode MS 01Oct96 				WayPoint	
//DeadCode MS 01Oct96 				{
//DeadCode MS 01Oct96 					Posn	{Abs 	{EnemyScoutHomeBase},
//DeadCode MS 01Oct96 						 	 Abs	{Y FT_3000}	
//DeadCode MS 01Oct96 							},
//DeadCode MS 01Oct96 					Action	wpacircleno,
//DeadCode MS 01Oct96 					Range	MARGIN
//DeadCode MS 01Oct96 				},
//DeadCode MS 01Oct96 				WayPoint	
//DeadCode MS 01Oct96 				{
//DeadCode MS 01Oct96 					Posn	{Abs	{EnemyScoutHomeBase}, 
//DeadCode MS 01Oct96 						 	 Abs	{Y FT_EnterLandingPattern}
//DeadCode MS 01Oct96 							},
//DeadCode MS 01Oct96 					Action	wpalandingno,
//DeadCode MS 01Oct96 					Range	DistEnterLandingPattern
//DeadCode MS 01Oct96 				}
//DeadCode MS 01Oct96 			},
//DeadCode MS 01Oct96 			NumInWing	6,
//DeadCode MS 01Oct96 			NumInForm	EncounterList01,
//DeadCode MS 01Oct96 			Duty		DUTYCAP,
//DeadCode MS 01Oct96 
//DeadCode MS 01Oct96 			Posn	{Abs	{EnemyScoutHomeBase}, 
//DeadCode MS 01Oct96 					 Rel	{Bearing	{Random	ANGLES_359Deg},
//DeadCode MS 01Oct96 				 	 Range	{Random MARGIN,2,METRES50},
//DeadCode MS 01Oct96 				 	 Y	{Random	FT_3000,10,FT_100}
//DeadCode MS 01Oct96 				 	}
//DeadCode MS 01Oct96 				},
//DeadCode MS 01Oct96 
//DeadCode MS 01Oct96 		   	AirItem	CockyEnemyScout00 =     	
//DeadCode MS 01Oct96 			{
//DeadCode MS 01Oct96 				Side		NAT_ENEMY,
//DeadCode MS 01Oct96 				Type		EnemyScoutType00,
//DeadCode MS 01Oct96 				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
//DeadCode MS 01Oct96 				Home		EnemyScoutHomeBase,
//DeadCode MS 01Oct96 				MoveCode	AUTO_FOLLOWWP,
//DeadCode MS 01Oct96 				Skill		SKILL_VETERAN
//DeadCode MS 01Oct96 			}
//DeadCode MS 01Oct96 		}
//DeadCode MS 01Oct96 	};
//DeadCode MS 01Oct96 
//DeadCode MS 01Oct96 //---------------------------------------------------------------------------
//DeadCode MS 01Oct96 //BFEV_ENEMYLOWLEVELATTACK03
//DeadCode MS 01Oct96 //A cocky scout is circling above your base, waiting. Taunting.
//DeadCode MS 01Oct96 
//DeadCode MS 01Oct96 	BattleField
//DeadCode MS 01Oct96 	{
//DeadCode MS 01Oct96 		FileName	BFEV_ENEMYLOWLEVELATTACK03=EVafld03.BF,
//DeadCode MS 01Oct96 		Setval	{GlobalSkillMin, FriendlyScoutSkillMin},
//DeadCode MS 01Oct96 		Setval	{GlobalSkillMax, FriendlyScoutSkillMax},
//DeadCode MS 01Oct96 		AirGroup	CockyScout03 =	
//DeadCode MS 01Oct96 		{
//DeadCode MS 01Oct96 			Route	
//DeadCode MS 01Oct96 			{
//DeadCode MS 01Oct96 				WayPoint	
//DeadCode MS 01Oct96 				{
//DeadCode MS 01Oct96 					Posn	{Abs 	{MainObjective},
//DeadCode MS 01Oct96 						 	 Abs	{Y FT_3000}	
//DeadCode MS 01Oct96 							},
//DeadCode MS 01Oct96 					Action	wpacircleno,
//DeadCode MS 01Oct96 					Range	MARGIN
//DeadCode MS 01Oct96 				},
//DeadCode MS 01Oct96 				WayPoint	
//DeadCode MS 01Oct96 				{
//DeadCode MS 01Oct96 					Posn	{Abs	{EnemyScoutHomeBase}, 
//DeadCode MS 01Oct96 						 	 Abs	{Y FT_EnterLandingPattern}
//DeadCode MS 01Oct96 							},
//DeadCode MS 01Oct96 					Action	wpalandingno,
//DeadCode MS 01Oct96 					Range	DistEnterLandingPattern
//DeadCode MS 01Oct96 				}
//DeadCode MS 01Oct96 			},
//DeadCode MS 01Oct96 			NumInWing	6,
//DeadCode MS 01Oct96 			NumInForm	EncounterList01,
//DeadCode MS 01Oct96 			Duty		DUTYCAP,
//DeadCode MS 01Oct96 
//DeadCode MS 01Oct96 			Posn	{Abs	{MainObjective}, 
//DeadCode MS 01Oct96 					 Rel	{Bearing	{Random	ANGLES_359Deg},
//DeadCode MS 01Oct96 				 	 Range	{Random MARGIN,2,METRES50},
//DeadCode MS 01Oct96 				 	 Y	{Random	FT_3000,10,FT_100}
//DeadCode MS 01Oct96 				 	}
//DeadCode MS 01Oct96 				},
//DeadCode MS 01Oct96 
//DeadCode MS 01Oct96 		   	AirItem	
//DeadCode MS 01Oct96 			{
//DeadCode MS 01Oct96 				Side		NAT_ENEMY,
//DeadCode MS 01Oct96 				Type		FriendlyScoutType00,
//DeadCode MS 01Oct96 				Home		FriendlyScoutHomeBase,
//DeadCode MS 01Oct96 				Squadron	{FriendlyScoutSquad,PS_5,PS_6,PS_7,PS_8},
//DeadCode MS 01Oct96 				MoveCode	AUTO_FOLLOWWP,
//DeadCode MS 01Oct96 				Skill		SKILL_VETERAN
//DeadCode MS 01Oct96 			}
//DeadCode MS 01Oct96 		}
//DeadCode MS 01Oct96 	};
//DeadCode MS 01Oct96 
//DeadCode MS 01Oct96 //---------------------------------------------------------------------------
//DeadCode MS 01Oct96 //BFEV_ENEMYLOWLEVELATTACK04
//DeadCode MS 01Oct96 //A cocky scout is preparing to attack your airbase. His buddy is circling above.
//DeadCode MS 01Oct96 
//DeadCode MS 01Oct96 	BattleField
//DeadCode MS 01Oct96 	{
//DeadCode MS 01Oct96 		FileName	BFEV_ENEMYLOWLEVELATTACK04=EVafld04.BF,
//DeadCode MS 01Oct96 		AirGroup	CockyScout00,	
//DeadCode MS 01Oct96 		AirGroup	CockyScout02
//DeadCode MS 01Oct96 	};
//DeadCode MS 01Oct96 
//DeadCode MS 01Oct96 //---------------------------------------------------------------------------
//DeadCode MS 01Oct96 //BFEV_ENEMYLOWLEVELATTACK05
//DeadCode MS 01Oct96 //A cocky scout is preparing to attack a friendly airbase. His buddy is
//DeadCode MS 01Oct96 //circling above.
//DeadCode MS 01Oct96 
//DeadCode MS 01Oct96 	BattleField
//DeadCode MS 01Oct96 	{
//DeadCode MS 01Oct96 		FileName	BFEV_ENEMYLOWLEVELATTACK05=EVafld05.BF,
//DeadCode MS 01Oct96 		Setval{FormSize00,Int {Select 1,EncounterSize}},
//DeadCode MS 01Oct96 		AirGroup	CockyScout01,	
//DeadCode MS 01Oct96 		AirGroup	CockyScout03	
//DeadCode MS 01Oct96 	};
//DeadCode MS 01Oct96 
//DeadCode MS 01Oct96 //---------------------------------------------------------------------------
//DeadCode MS 01Oct96 //Objective being beaten up. Some friendlies are trying to take off. One has
//DeadCode MS 01Oct96 //already managed to but is being given a hard time. 
//DeadCode MS 01Oct96 
//DeadCode MS 01Oct96 	BattleField
//DeadCode MS 01Oct96 	{
//DeadCode MS 01Oct96 		FileName	BFEV_ENEMYLOWLEVELATTACK06=EVafld06.BF,
//DeadCode MS 01Oct96 		Setval{FormSize00,Int {Select 3,EncounterSize}},
//DeadCode MS 01Oct96 		Setval{FormSize01,Int {Select 4,EncounterSize}},
//DeadCode MS 01Oct96 		Setval{FormSize02,Int {Select 2,EncounterSize}},
//DeadCode MS 01Oct96 		Setval{FormSize03,Int {Select 3,EncounterSize}},
//DeadCode MS 01Oct96 		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
//DeadCode MS 01Oct96 		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
//DeadCode MS 01Oct96 		AirGroup	
//DeadCode MS 01Oct96 		{
//DeadCode MS 01Oct96 			Route	
//DeadCode MS 01Oct96 			{
//DeadCode MS 01Oct96 				WayPoint	
//DeadCode MS 01Oct96 				{
//DeadCode MS 01Oct96 					Posn	{Abs 	{MainObjective},
//DeadCode MS 01Oct96 						 	 Abs	{Y FT_3000}	
//DeadCode MS 01Oct96 							},
//DeadCode MS 01Oct96 					Action	wpacircleno,
//DeadCode MS 01Oct96 					Range	MARGIN
//DeadCode MS 01Oct96 				},
//DeadCode MS 01Oct96 				WayPoint	
//DeadCode MS 01Oct96 				{
//DeadCode MS 01Oct96 					Posn	{Abs	{EnemyScoutHomeBase}, 
//DeadCode MS 01Oct96 						 	 Abs	{Y FT_EnterLandingPattern}
//DeadCode MS 01Oct96 							},
//DeadCode MS 01Oct96 					Action	wpalandingno,
//DeadCode MS 01Oct96 					Range	DistEnterLandingPattern
//DeadCode MS 01Oct96 				}
//DeadCode MS 01Oct96 			},
//DeadCode MS 01Oct96 			NumInWing	3,
//DeadCode MS 01Oct96 			NumInForm	FormSize00,
//DeadCode MS 01Oct96 			Duty		DUTYCAP,
//DeadCode MS 01Oct96 
//DeadCode MS 01Oct96 			Posn	{Abs	{MainObjective}, 
//DeadCode MS 01Oct96 					 Rel	{Bearing	{Random	ANGLES_359Deg},
//DeadCode MS 01Oct96 				 	 		 Range	{Random MARGIN,2,METRES50},
//DeadCode MS 01Oct96 				 	 		 Y	{Random	FT_3000,10,FT_100}
//DeadCode MS 01Oct96 				 			}
//DeadCode MS 01Oct96 					},
//DeadCode MS 01Oct96 
//DeadCode MS 01Oct96 		   	AirItem	
//DeadCode MS 01Oct96 			{
//DeadCode MS 01Oct96 				Side		NAT_ENEMY,
//DeadCode MS 01Oct96 				Type		EnemyScoutType00,
//DeadCode MS 01Oct96 				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
//DeadCode MS 01Oct96 				Home		EnemyScoutHomeBase,
//DeadCode MS 01Oct96 				MoveCode	AUTO_FOLLOWWP,
//DeadCode MS 01Oct96 				Skill		SKILL_VETERAN
//DeadCode MS 01Oct96 			}
//DeadCode MS 01Oct96 		},
//DeadCode MS 01Oct96 		AirGroup	
//DeadCode MS 01Oct96 		{
//DeadCode MS 01Oct96 			Route	
//DeadCode MS 01Oct96 			{
//DeadCode MS 01Oct96 				WayPoint	
//DeadCode MS 01Oct96 				{
//DeadCode MS 01Oct96 					Posn	{Abs 	{MainObjective},
//DeadCode MS 01Oct96 						 	 Abs	{Y FT_5000}	
//DeadCode MS 01Oct96 							},
//DeadCode MS 01Oct96 					Action	wpacircleno,
//DeadCode MS 01Oct96 					Range	MARGIN
//DeadCode MS 01Oct96 				},
//DeadCode MS 01Oct96 				WayPoint	
//DeadCode MS 01Oct96 				{
//DeadCode MS 01Oct96 					Posn	{Abs	{MainObjective}, 
//DeadCode MS 01Oct96 						 	 Abs	{Y FT_EnterLandingPattern}
//DeadCode MS 01Oct96 							},
//DeadCode MS 01Oct96 					Action	wpalandingno,
//DeadCode MS 01Oct96 					Range	DistEnterLandingPattern
//DeadCode MS 01Oct96 				}
//DeadCode MS 01Oct96 			},
//DeadCode MS 01Oct96 			NumInWing	4,
//DeadCode MS 01Oct96 			NumInForm	FormSize01,
//DeadCode MS 01Oct96 			Duty		DUTYCAP,
//DeadCode MS 01Oct96 
//DeadCode MS 01Oct96 			Posn	{Abs	{MainObjective}, 
//DeadCode MS 01Oct96 				 	 Abs	{Y	FT_GRND}
//DeadCode MS 01Oct96 				 	},
//DeadCode MS 01Oct96 
//DeadCode MS 01Oct96 		   	AirItem BFEV_ENEMYLOWLEVELATTACK06_FriendItem00 =
//DeadCode MS 01Oct96 			{
//DeadCode MS 01Oct96 				Side		NAT_FRIEND,
//DeadCode MS 01Oct96 				Type		SQ_PUP,
//DeadCode MS 01Oct96 				MoveCode	AUTO_FOLLOWWP,
//DeadCode MS 01Oct96 //				movecode	Qtakeoff routine??					//MS 08Mar96
//DeadCode MS 01Oct96 				Skill		SKILL_VETERAN
//DeadCode MS 01Oct96 			}
//DeadCode MS 01Oct96 		},
//DeadCode MS 01Oct96 		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
//DeadCode MS 01Oct96 		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
//DeadCode MS 01Oct96 		AirGroup	
//DeadCode MS 01Oct96 		{
//DeadCode MS 01Oct96 			Route	
//DeadCode MS 01Oct96 			{
//DeadCode MS 01Oct96 				WayPoint	
//DeadCode MS 01Oct96 				{
//DeadCode MS 01Oct96 					Posn	{Abs 	{MainObjective},
//DeadCode MS 01Oct96 						 	 Abs	{Y FT_3000}	
//DeadCode MS 01Oct96 							},
//DeadCode MS 01Oct96 					Action	wpacircleno,
//DeadCode MS 01Oct96 					Range	MARGIN
//DeadCode MS 01Oct96 				},
//DeadCode MS 01Oct96 				WayPoint	
//DeadCode MS 01Oct96 				{
//DeadCode MS 01Oct96 					Posn	{Abs	{EnemyScoutHomeBase}, 
//DeadCode MS 01Oct96 						 	 Abs	{Y FT_EnterLandingPattern}
//DeadCode MS 01Oct96 							},
//DeadCode MS 01Oct96 					Action	wpalandingno,
//DeadCode MS 01Oct96 					Range	DistEnterLandingPattern
//DeadCode MS 01Oct96 				}
//DeadCode MS 01Oct96 			},
//DeadCode MS 01Oct96 			NumInWing	2,
//DeadCode MS 01Oct96 			NumInForm	FormSize02,
//DeadCode MS 01Oct96 			Duty		DUTYCAP,
//DeadCode MS 01Oct96 //			duty straffe and stuff								//MS 08Mar96
//DeadCode MS 01Oct96 
//DeadCode MS 01Oct96 			Posn	{Abs	BFEV_ENEMYLOWLEVELATTACK06_FriendItem00, 
//DeadCode MS 01Oct96 					 Abs	{Y	FT_500},
//DeadCode MS 01Oct96 					 Rel	{Bearing	{Random	0,359,ANGLES_1Deg},
//DeadCode MS 01Oct96 				 	 		 Range	{Random METRES100,100,METRES01}
//DeadCode MS 01Oct96 							}
//DeadCode MS 01Oct96 				 	},
//DeadCode MS 01Oct96 				
//DeadCode MS 01Oct96 
//DeadCode MS 01Oct96 		   	AirItem	BFEV_ENEMYLOWLEVELATTACK06_EnemyItem00 =
//DeadCode MS 01Oct96 			{
//DeadCode MS 01Oct96 				Side		NAT_ENEMY,
//DeadCode MS 01Oct96 				Type		EnemyScoutType00,
//DeadCode MS 01Oct96 				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
//DeadCode MS 01Oct96 				Home		EnemyScoutHomeBase,
//DeadCode MS 01Oct96 				MoveCode	AUTO_FOLLOWWP,
//DeadCode MS 01Oct96 				Target		BFEV_ENEMYLOWLEVELATTACK06_FriendItem00,	
//DeadCode MS 01Oct96 				Skill		SKILL_REGULAR
//DeadCode MS 01Oct96 			}
//DeadCode MS 01Oct96 		},
//DeadCode MS 01Oct96 		AirGroup	
//DeadCode MS 01Oct96 		{
//DeadCode MS 01Oct96 			Route	
//DeadCode MS 01Oct96 			{
//DeadCode MS 01Oct96 				WayPoint	
//DeadCode MS 01Oct96 				{
//DeadCode MS 01Oct96 					Posn	{Abs 	{MainObjective},
//DeadCode MS 01Oct96 						 	 Abs	{Y FT_5000}	
//DeadCode MS 01Oct96 							},
//DeadCode MS 01Oct96 					Action	wpacircleno,
//DeadCode MS 01Oct96 					Range	MARGIN
//DeadCode MS 01Oct96 				},
//DeadCode MS 01Oct96 				WayPoint	
//DeadCode MS 01Oct96 				{
//DeadCode MS 01Oct96 					Posn	{Abs	{MainObjective}, 
//DeadCode MS 01Oct96 						 	 Abs	{Y FT_EnterLandingPattern}
//DeadCode MS 01Oct96 							},
//DeadCode MS 01Oct96 					Action	wpalandingno,
//DeadCode MS 01Oct96 					Range	DistEnterLandingPattern
//DeadCode MS 01Oct96 				}
//DeadCode MS 01Oct96 			},
//DeadCode MS 01Oct96 			NumInWing	1,
//DeadCode MS 01Oct96 			NumInForm	1,
//DeadCode MS 01Oct96 			Duty		DUTYCAP,
//DeadCode MS 01Oct96 
//DeadCode MS 01Oct96 			Posn	{Abs	BFEV_ENEMYLOWLEVELATTACK06_EnemyItem00, 
//DeadCode MS 01Oct96 					 Rel	{Y	{Random	-FT_100,600,FT_1},
//DeadCode MS 01Oct96 							 Bearing	{Random	0,359,ANGLES_1Deg},
//DeadCode MS 01Oct96 				 	 		 Range	{Random METRES100,100,METRES01}
//DeadCode MS 01Oct96 							}
//DeadCode MS 01Oct96 					},
//DeadCode MS 01Oct96 
//DeadCode MS 01Oct96 		   	AirItem BFEV_ENEMYLOWLEVELATTACK06_FriendItem01 =
//DeadCode MS 01Oct96 			{
//DeadCode MS 01Oct96 				Side		NAT_FRIEND,
//DeadCode MS 01Oct96 				Type		SQ_PUP,
//DeadCode MS 01Oct96 				MoveCode	AUTO_FOLLOWWP,
//DeadCode MS 01Oct96 				Target		BFEV_ENEMYLOWLEVELATTACK06_EnemyItem00,
//DeadCode MS 01Oct96 				Skill		SKILL_VETERAN
//DeadCode MS 01Oct96 			}
//DeadCode MS 01Oct96 		},
//DeadCode MS 01Oct96 		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
//DeadCode MS 01Oct96 		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
//DeadCode MS 01Oct96 		AirGroup	
//DeadCode MS 01Oct96 		{
//DeadCode MS 01Oct96 			Route	
//DeadCode MS 01Oct96 			{
//DeadCode MS 01Oct96 				WayPoint	
//DeadCode MS 01Oct96 				{
//DeadCode MS 01Oct96 					Posn	{Abs 	{MainObjective},
//DeadCode MS 01Oct96 						 	 Abs	{Y FT_5000}	
//DeadCode MS 01Oct96 							},
//DeadCode MS 01Oct96 					Action	wpacircleno,
//DeadCode MS 01Oct96 					Range	MARGIN
//DeadCode MS 01Oct96 				},
//DeadCode MS 01Oct96 				WayPoint	
//DeadCode MS 01Oct96 				{
//DeadCode MS 01Oct96 					Posn	{Abs	{EnemyScoutHomeBase}, 
//DeadCode MS 01Oct96 						 	 Abs	{Y FT_EnterLandingPattern}
//DeadCode MS 01Oct96 							},
//DeadCode MS 01Oct96 					Action	wpalandingno,
//DeadCode MS 01Oct96 					Range	DistEnterLandingPattern
//DeadCode MS 01Oct96 				}
//DeadCode MS 01Oct96 			},
//DeadCode MS 01Oct96 			NumInWing	3,
//DeadCode MS 01Oct96 			NumInForm	FormSize03,
//DeadCode MS 01Oct96 			Duty		DUTYCAP,
//DeadCode MS 01Oct96 //			duty straffe and stuff								//MS 08Mar96
//DeadCode MS 01Oct96 
//DeadCode MS 01Oct96 			Posn	{Abs	BFEV_ENEMYLOWLEVELATTACK06_FriendItem01, 
//DeadCode MS 01Oct96 					 Abs	{Y	FT_750},
//DeadCode MS 01Oct96 					 Rel	{Bearing	{Random	0,359,ANGLES_1Deg},
//DeadCode MS 01Oct96 				 	 		 Range	{Random METRES100,100,METRES01}
//DeadCode MS 01Oct96 							}
//DeadCode MS 01Oct96 				 	},
//DeadCode MS 01Oct96 
//DeadCode MS 01Oct96 		   	AirItem	
//DeadCode MS 01Oct96 			{
//DeadCode MS 01Oct96 				Side		NAT_ENEMY,
//DeadCode MS 01Oct96 				Type		EnemyScoutType00,
//DeadCode MS 01Oct96 				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
//DeadCode MS 01Oct96 				Home		EnemyScoutHomeBase,
//DeadCode MS 01Oct96 				MoveCode	AUTO_FOLLOWWP,
//DeadCode MS 01Oct96 				Target		BFEV_ENEMYLOWLEVELATTACK06_FriendItem01,	
//DeadCode MS 01Oct96 				Skill		SKILL_REGULAR
//DeadCode MS 01Oct96 			}
//DeadCode MS 01Oct96 		}
//DeadCode MS 01Oct96 	};	
//DeadCode MS 01Oct96 
//DeadCode MS 01Oct96 //---------------------------------------------------------------------------
//DeadCode MS 01Oct96 //You've missed the main event. The main force of enemy fighters are retiring
//DeadCode MS 01Oct96 //from the area, as they are low on ammo. 1 or 2 are still beating up the
//DeadCode MS 01Oct96 //main objective. You have a distinct advantage.
//DeadCode MS 01Oct96 
//DeadCode MS 01Oct96 	BattleField
//DeadCode MS 01Oct96 	{
//DeadCode MS 01Oct96 		FileName	BFEV_ENEMYLOWLEVELATTACK07=EVafld07.BF,	
//DeadCode MS 01Oct96 		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
//DeadCode MS 01Oct96 		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
//DeadCode MS 01Oct96 		AirGroup	
//DeadCode MS 01Oct96 		{
//DeadCode MS 01Oct96 			Route	
//DeadCode MS 01Oct96 			{
//DeadCode MS 01Oct96 				WayPoint	
//DeadCode MS 01Oct96 				{
//DeadCode MS 01Oct96 					Posn	{Abs	{EnemyScoutHomeBase},
//DeadCode MS 01Oct96 							 Abs	{Y FT_300},
//DeadCode MS 01Oct96 							 Rel	{Intercept	{EnemyScoutHomeBase,MainObjective},
//DeadCode MS 01Oct96 								 	 Bearing	ANGLES_359Deg,
//DeadCode MS 01Oct96 								 	 RangePercent	100
//DeadCode MS 01Oct96 							 		}
//DeadCode MS 01Oct96 							},	
//DeadCode MS 01Oct96 					Action	wpacnoactionno,
//DeadCode MS 01Oct96 					Range	MARGIN
//DeadCode MS 01Oct96 				},
//DeadCode MS 01Oct96 				WayPoint	
//DeadCode MS 01Oct96 				{
//DeadCode MS 01Oct96 					Posn	{Abs	{EnemyScoutHomeBase},
//DeadCode MS 01Oct96 							 Abs	{Y FT_6000},
//DeadCode MS 01Oct96 							 Rel	{Intercept	{EnemyScoutHomeBase,MainObjective},
//DeadCode MS 01Oct96 								 	 Bearing	ANGLES_359Deg,
//DeadCode MS 01Oct96 								 	 RangePercent	70
//DeadCode MS 01Oct96 							 		}
//DeadCode MS 01Oct96 							},	
//DeadCode MS 01Oct96 					Action	wpacnoactionno,
//DeadCode MS 01Oct96 					Range	MARGIN
//DeadCode MS 01Oct96 				},
//DeadCode MS 01Oct96 				WayPoint	
//DeadCode MS 01Oct96 				{
//DeadCode MS 01Oct96 					Posn	{Abs	{EnemyScoutHomeBase},
//DeadCode MS 01Oct96 							 Abs	{Y FT_6000},
//DeadCode MS 01Oct96 							 Rel	{Intercept	{EnemyScoutHomeBase,MainObjective},
//DeadCode MS 01Oct96 								 	 Bearing	ANGLES_359Deg,
//DeadCode MS 01Oct96 								 	 RangePercent	30
//DeadCode MS 01Oct96 							 		}
//DeadCode MS 01Oct96 							},	
//DeadCode MS 01Oct96 					Action	wpacnoactionno,
//DeadCode MS 01Oct96 					Range	MARGIN
//DeadCode MS 01Oct96 				},
//DeadCode MS 01Oct96 				WayPoint	
//DeadCode MS 01Oct96 				{
//DeadCode MS 01Oct96 					Posn	{Abs	{EnemyScoutHomeBase}, 
//DeadCode MS 01Oct96 						 	 Abs	{Y FT_EnterLandingPattern}
//DeadCode MS 01Oct96 							},
//DeadCode MS 01Oct96 					Action	wpalandingno,
//DeadCode MS 01Oct96 					Range	DistEnterLandingPattern
//DeadCode MS 01Oct96 				}
//DeadCode MS 01Oct96 			},
//DeadCode MS 01Oct96 
//DeadCode MS 01Oct96 			NumInWing	6,
//DeadCode MS 01Oct96 			NumInForm	EncounterList06,
//DeadCode MS 01Oct96 			Duty		DUTYCAP,
//DeadCode MS 01Oct96 
//DeadCode MS 01Oct96 			Posn	{Abs	{MainObjective},
//DeadCode MS 01Oct96 					 Abs	{Y	FT_300}
//DeadCode MS 01Oct96 					}, 
//DeadCode MS 01Oct96 
//DeadCode MS 01Oct96 		   	AirItem	BFEV_ENEMYLOWLEVELATTACK07_EnemyItem00 =	
//DeadCode MS 01Oct96 			{
//DeadCode MS 01Oct96 				Side		NAT_ENEMY,
//DeadCode MS 01Oct96 				Type		EnemyScoutType00,
//DeadCode MS 01Oct96 				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
//DeadCode MS 01Oct96 				Home		EnemyScoutHomeBase,
//DeadCode MS 01Oct96 				MoveCode	AUTO_FOLLOWWP,
//DeadCode MS 01Oct96 				Skill		SKILL_VETERAN
//DeadCode MS 01Oct96 //				Low on fuel and ammo
//DeadCode MS 01Oct96 			}
//DeadCode MS 01Oct96 		},
//DeadCode MS 01Oct96 		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
//DeadCode MS 01Oct96 		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
//DeadCode MS 01Oct96 		AirGroup	
//DeadCode MS 01Oct96 		{
//DeadCode MS 01Oct96 			Route	
//DeadCode MS 01Oct96 			{
//DeadCode MS 01Oct96 				WayPoint	
//DeadCode MS 01Oct96 				{
//DeadCode MS 01Oct96 					Target	MainObjective,
//DeadCode MS 01Oct96 					Posn	{
//DeadCode MS 01Oct96 							 Abs	{Y FT_300}
//DeadCode MS 01Oct96 							},	
//DeadCode MS 01Oct96 					Action	wpstraffeno,
//DeadCode MS 01Oct96 					Range	MARGIN
//DeadCode MS 01Oct96 				},
//DeadCode MS 01Oct96 				WayPoint	
//DeadCode MS 01Oct96 				{
//DeadCode MS 01Oct96 					Posn	{Abs	{EnemyScoutHomeBase},
//DeadCode MS 01Oct96 							 Abs	{Y FT_300},
//DeadCode MS 01Oct96 							 Rel	{Intercept	{EnemyScoutHomeBase,MainObjective},
//DeadCode MS 01Oct96 								 	Bearing	ANGLES_359Deg,
//DeadCode MS 01Oct96 								 	RangePercent	100
//DeadCode MS 01Oct96 							 		}
//DeadCode MS 01Oct96 							},	
//DeadCode MS 01Oct96 					Action	wpacnoactionno,
//DeadCode MS 01Oct96 					Range	MARGIN
//DeadCode MS 01Oct96 				},
//DeadCode MS 01Oct96 				WayPoint	
//DeadCode MS 01Oct96 				{
//DeadCode MS 01Oct96 					Posn	{Abs	{EnemyScoutHomeBase},
//DeadCode MS 01Oct96 							 Abs	{Y FT_6000},
//DeadCode MS 01Oct96 							 Rel	{Intercept	{EnemyScoutHomeBase,MainObjective},
//DeadCode MS 01Oct96 								 	 Bearing	ANGLES_359Deg,
//DeadCode MS 01Oct96 								 	 RangePercent	70
//DeadCode MS 01Oct96 							 		}
//DeadCode MS 01Oct96 							},	
//DeadCode MS 01Oct96 					Action	wpacnoactionno,
//DeadCode MS 01Oct96 					Range	MARGIN
//DeadCode MS 01Oct96 				},
//DeadCode MS 01Oct96 				WayPoint	
//DeadCode MS 01Oct96 				{
//DeadCode MS 01Oct96 					Posn	{Abs	{EnemyScoutHomeBase},
//DeadCode MS 01Oct96 							 Abs	{Y FT_6000},
//DeadCode MS 01Oct96 							 Rel	{Intercept	{EnemyScoutHomeBase,MainObjective},
//DeadCode MS 01Oct96 								 	 Bearing	ANGLES_359Deg,
//DeadCode MS 01Oct96 								 	 RangePercent	30
//DeadCode MS 01Oct96 							 		}
//DeadCode MS 01Oct96 							},	
//DeadCode MS 01Oct96 					Action	wpacnoactionno,
//DeadCode MS 01Oct96 					Range	MARGIN
//DeadCode MS 01Oct96 				},
//DeadCode MS 01Oct96 				WayPoint	
//DeadCode MS 01Oct96 				{
//DeadCode MS 01Oct96 					Posn	{Abs	{EnemyScoutHomeBase}, 
//DeadCode MS 01Oct96 						 	 Abs	{Y FT_EnterLandingPattern}
//DeadCode MS 01Oct96 							},
//DeadCode MS 01Oct96 					Action	wpalandingno,
//DeadCode MS 01Oct96 					Range	DistEnterLandingPattern
//DeadCode MS 01Oct96 				}
//DeadCode MS 01Oct96 			},
//DeadCode MS 01Oct96 
//DeadCode MS 01Oct96 			NumInWing	6,
//DeadCode MS 01Oct96 			NumInForm	EncounterList06,
//DeadCode MS 01Oct96 			Duty		DUTYCAP,
//DeadCode MS 01Oct96 
//DeadCode MS 01Oct96 			Posn	{Abs	{MainObjective},
//DeadCode MS 01Oct96 					 Abs	{Y	FT_300},
//DeadCode MS 01Oct96 					 Rel	{Bearing	{Random	0,359,ANGLES_1Deg},
//DeadCode MS 01Oct96 							 Range	MARGIN
//DeadCode MS 01Oct96 							}
//DeadCode MS 01Oct96 					}, 
//DeadCode MS 01Oct96 
//DeadCode MS 01Oct96 		   	AirItem	
//DeadCode MS 01Oct96 			{
//DeadCode MS 01Oct96 				Side		NAT_ENEMY,
//DeadCode MS 01Oct96 				Type		EnemyScoutType00,
//DeadCode MS 01Oct96 				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
//DeadCode MS 01Oct96 				Home		EnemyScoutHomeBase,
//DeadCode MS 01Oct96 				MoveCode	AUTO_FOLLOWWP,
//DeadCode MS 01Oct96 				Leader		BFEV_ENEMYLOWLEVELATTACK07_EnemyItem00,
//DeadCode MS 01Oct96 				Skill		SKILL_VETERAN
//DeadCode MS 01Oct96 			}
//DeadCode MS 01Oct96 		}
//DeadCode MS 01Oct96 	};
//---------------------------------------------------------------------------
//BFEV_FRIENDLYSCOUTBAIT
//???? is bait, player is bounced by ?????

	BattleField
	{
		FileName	BFEV_FRIENDLYSCOUTBAIT=EVbait00.BF,
		Setval	{GlobalSkillMin, FriendlyScoutSkillMin},
		Setval	{GlobalSkillMax, FriendlyScoutSkillMax},
		AirGroup		
		{
			Route	
			{
				WayPoint	
				{
					Posn	{Abs 	{CPP},
							 Rel	{Bearing	ANGLES_359Deg,
									 Y	{Random	FT_2000},
									 Range	{Random	METRES2000}
									}
							},
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	{Abs	{FriendlyScoutHomeBase}, 
						 Abs	{Y FT_1000},	
						 Rel	{Z 1000}
						},
					Action	wpalandingno
				}
			},
			NumInWing	1,
			NumInForm	1,
			Duty		DUTYCAP,

			Posn	{Abs	{CPP}, 
				 Rel	{Bearing	{Random	ANGLES_0Deg,359,ANGLES_1Deg},
				 	 	 Range	{Random METRES800,10,METRES20},
				 	 	 Y	{Random	-500,100,10}
				 		}
					},

		   	AirItem		     	
			{
				Side		NAT_ENEMY,
				Type		FriendlyScoutType00,
				Home		FriendlyScoutHomeBase,
				Squadron	{FriendlyScoutSquad,PS_5,PS_6,PS_7,PS_8},
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, FriendlyScoutTactician,FriendlyScoutMrAverage,FriendlyScoutCavalier}},
				Morale		{Random	FriendlyScoutMorale,40,1}
			}
		}
	};


//---------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_ENEMYATTACKLOWBALLOON00=EVwnch00.BF,

		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup	EnemyBalloonLowAttack00 =	
		{
			Route	EnemyAttackLowBalloonRoute00 =	
			{
				WayPoint	ENEMYATTACKLOWBALLOON00_WP00 =	
				{
					Target	EnemyObjective, 
					Posn	{Abs	{Y -FT_200}
							},	
					Range	ATTACKBALLOONRANGE,
					Action	wpballoonbustno
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyObjective}, 
							 Abs	{Y FT_4000},
							 Rel	{Intercept	{EnemyObjective,EnemyScoutHomeBase},
									 Bearing	ANGLES_0Deg,
									 RangePercent	30
									}
							},
					Range	MARGIN,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyScoutHomeBase}, 
						 	Abs	{Y FT_4000}
							},
					Action	wpacnoactionno,
					Range	STANDARDTRIGGER
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyScoutHomeBase}, 
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	6,
			NumInForm	EncounterList02,
			Duty		DUTYCAP,
			Formation	FORM_V,

			Posn		{Abs	{EnemyObjective},
						 Abs	{Y -FT_200},
						 Rel	{Bearing	{Random	ANGLES_0Deg,359,ANGLES_1Deg},
								 Range		ATTACKBALLOONRANGE
								}
						},

		   	AirItem	EVwnch00_Item00	=
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1}
			}
		}
	};

//----------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_ENEMYATTACKLOWBALLOON01		=EVwnch01.BF,

		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup	EnemyBalloonLowAttack00, 
		AirGroup	
		{
			Route	ENEMYATTACKLOWBALLOON00_WP00,
		
			NumInWing	6,
			NumInForm	EncounterList03,
			Duty		DUTYCAP,
			Formation	FORM_V,

			Posn		{Abs	EVwnch00_Item00},

		   	AirItem		     	
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1},
				Leader		EVwnch00_Item00
			}
		}
	};

//-----------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_ENEMYAPPROACHLOWBALLOON00=EVwnch03.BF,

		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},

		AirGroup
		{
			Route
			{
				WayPoint
				{
					Target	EnemyObjective, 
					Posn	{Abs	{Y FT_1000}
							},	
					Range	ATTACKBALLOONRANGE,
					Action	wpballoonbustno
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyScoutHomeBase}, 
						 	Abs	{Y FT_4000}
							},
					Action	wpacnoactionno,
					Range	STANDARDTRIGGER
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyScoutHomeBase}, 
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	6,
			NumInForm	EncounterList02,

			Duty		DUTYCAP,
			Formation	FORM_V,

			Posn		{Abs	{CPP},
						 Abs	{Y FT_1000},
						 Rel	{Intercept	{CPP,CWP},
								 Bearing	{Random	ANGLES_330Deg,2,ANGLES_60Deg},
								 Range	VISINEDGE
								}
						},

		   	AirItem
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1}
			}
		}
	};

//----------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_ENEMYAPPROACHLOWBALLOON01=EVwnch04.BF,

		AirGroup	
		{
			Route
			{
				WayPoint	EVwnch04_WP00=
				{
					Target	EnemyObjective, 
					Posn	{Abs	{Y FT_1000}
							},	
					Range	ATTACKBALLOONRANGE,
					Action	wpballoonbustno
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyScoutHomeBase}, 
						 	Abs	{Y FT_4000}
							},
					Action	wpacnoactionno,
					Range	STANDARDTRIGGER
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyScoutHomeBase}, 
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},

			NumInWing	6,
			NumInForm	EncounterList03,
			Duty		DUTYCAP,
			Formation	FORM_V,	

			Posn		{Abs	{CPP},
						 Abs	{Y FT_2000},
						 Rel	{Intercept	{CPP,CWP},
								 Bearing	{Random	ANGLES_330Deg,2,ANGLES_60Deg},
								 Range	VISINEDGE
								}
						},

		   	AirItem	EVwnch04_Item00=
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List {Random 4}, SKILL_VETERAN,SKILL_REGULAR,SKILL_REGULAR,SKILL_POOR},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1}
			}
		},
		AirGroup	
		{
			Route	EVwnch04_WP00,

			NumInWing	6,
			NumInForm	EncounterList02,
			Formation	FORM_V,	

			Posn		{Abs	EVwnch04_Item00,
						 Abs	{Y FT_1000}
						},

		   	AirItem
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List {Random 3}, SKILL_VETERAN,SKILL_REGULAR,SKILL_POOR},
				Character	EnemyScoutCavalier,
				Morale		{Random	EnemyScoutMorale,40,1},
				Follower	EVwnch04_Item00	
			}
		}
	};


//---------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_FRIENDLYFRIENDS=EVFrds00.BF,
		Setval	{HeightStepSize,Int {Random 0,5000,1}},

		Setval	{GlobalSkillMin, FriendlyScoutSkillMin},
		Setval	{GlobalSkillMax, FriendlyScoutSkillMax},
		AirGroup	
		{
			Route	
			{
				WayPoint	EVFrds00_WP00=		
				{
					Posn	{Abs	{CPP},
							 Rel	{Y {Select	-FT_3000,HeightStepSize,FT_1},
									 Intercept	{CPP,CWP},
									 Bearing	{Random	ANGLES_0Deg,359,ANGLES_1Deg},
								 	 Range	VISINEDGE
									}
							},
					Action	wpacnoactionno,
					Range	MARGIN
				},
				WayPoint
				{
					Posn	{Abs	{CPP},
						 	 Rel	{Y {Select	-FT_3000,HeightStepSize,FT_1},
									 Intercept	{CPP,FriendlyScoutHomeBase},	
						 			 Bearing	ANGLES_0Deg,
						 			 RangePercent	90
									}
							},
					Action	wpacnoactionno,
					Range	MARGIN
				},
				WayPoint
				{
					Posn	{Abs	{FriendlyScoutHomeBase},	
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	6,
			NumInForm	EncounterList04,
			Duty		DUTYCAP,

					Posn	{Abs	{CPP},
							 Rel	{Y	{Select -FT_3000,HeightStepSize,FT_1},
									 Intercept	{EVFrds00_WP00,CWP},
							 		 Bearing	{Random	ANGLES_270Deg,180,ANGLES_1Deg},
							 		 Range	{Random VISINEDGE,VISBOUNDARYSIZE,METRES01}
									}
							},
		   	AirItem	
			{
				Side		NAT_FRIEND,
				Type		FriendlyScoutType00,
				Home		FriendlyScoutHomeBase,
				Squadron	{FriendlyScoutSquad,PS_5,PS_6,PS_7,PS_8},
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, FriendlyScoutTactician,FriendlyScoutMrAverage,FriendlyScoutCavalier}},
				Morale		{Random	FriendlyScoutMorale,40,1}
			}
		}
	};

//---------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_FRIENDLYPATROLTAKEOFF=EVFrds05.BF,
		Setval	{GlobalSkillMin, FriendlyScoutSkillMin},
		Setval	{GlobalSkillMax, FriendlyScoutSkillMax},
		AirGroup	
		{
			Route	
			{
				WayPoint
				{
					Posn	{Abs	{FriendlyObjective},
						 	 Abs	{Y	HeightSize}
							},
					Action	wpacnoactionno,
					Range	MARGIN
				},
				WayPoint
				{
					Posn	{Abs	{FriendlyObjective},
						 	 Abs	{Y	HeightSize},
							 Rel	{Intercept	{FriendlyScoutHomeBase, FriendlyObjective},
									 Bearing	ANGLES_270Deg,
								 	 Range	HALFSTANDARDTRIGGER
									}
							},
 					Action	wpstartloopno,
					Range	MARGIN
				},
				WayPoint
				{
					Posn	{Abs	{FriendlyObjective},
						 	 Abs	{Y	HeightSize},
							 Rel	{Intercept	{FriendlyScoutHomeBase, FriendlyObjective},
									 Bearing	ANGLES_90Deg,
								 	 Range	HALFSTANDARDTRIGGER
									}
							},
					Action	wpstoploopchkno,
					Range	MARGIN
				},
				WayPoint
				{
					Posn	{Abs	{FriendlyScoutHomeBase},	
						 	Abs	{Y HeightSize}
							},
					Action	wpacnoactionno,
					Range	STANDARDTRIGGER
				},
 				WayPoint
				{
					Posn	{Abs	{FriendlyScoutHomeBase},	
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	6,
			NumInForm	EncounterList04,
			Duty		DUTYCAP,

			Posn	{Abs	{FriendlyScoutHomeBase},
					 Abs	{Y FT_TakeOff}
					},

		   	AirItem	
			{
				Side		NAT_FRIEND,
				Type		FriendlyScoutType00,
				Home		FriendlyScoutHomeBase,
				Squadron	{FriendlyScoutSquad,PS_5,PS_6,PS_7,PS_8},
				MoveCode	AUTO_TAKEOFF,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, FriendlyScoutTactician,FriendlyScoutMrAverage,FriendlyScoutCavalier}},
				Morale		{Random	FriendlyScoutMorale,40,1}
			}
		}
	};

//---------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_FRIENDLYSTANDBY=EVFrds04.BF,
		Setval	{GlobalSkillMin, FriendlyScoutSkillMin},
		Setval	{GlobalSkillMax, FriendlyScoutSkillMax},
		AirGroup	
		{
			Route	
			{
				WayPoint
				{
					Posn	{Abs	{FriendlyScoutHomeBase},	
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	6,
			NumInForm	EncounterList04,
			Duty		DUTYCAP,

			Posn	{Abs	{FriendlyScoutHomeBase},
					 Abs	{Y FT_TakeOff}
					},

		   	AirItem	
			{
				Side		NAT_FRIEND,
				Type		FriendlyScoutType00,
				Home		FriendlyScoutHomeBase,
				Squadron	{FriendlyScoutSquad,PS_5,PS_6,PS_7,PS_8},
//fixme				STANDBY TO TAKEOFF
				MoveCode	AUTO_NOPPILOT,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, FriendlyScoutTactician,FriendlyScoutMrAverage,FriendlyScoutCavalier}},
				Morale		{Random	FriendlyScoutMorale,40,1}
			}
		}
	};

//---------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_ENEMYSTANDBY=EVEnmy00.BF,
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup	
		{
			Route	
			{
				WayPoint
				{
					Posn	{Abs	{EnemyScoutHomeBase},	
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	6,
			NumInForm	EncounterList04,
			Duty		DUTYCAP,

			Posn	{Abs	{EnemyScoutHomeBase},
					 Abs	{Y FT_TakeOff}
					},

		   	AirItem	
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Home		EnemyScoutHomeBase,
				Squadron	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				MoveCode	AUTO_NOPPILOT,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1}
			}
		}
	};

//---------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_FRIENDLYSCOUTLAND=EVFrds02.BF,
		Setval	{GlobalSkillMin, FriendlyScoutSkillMin},
		Setval	{GlobalSkillMax, FriendlyScoutSkillMax},
		AirGroup	
		{
			Route	
			{
				WayPoint	
				{
					Posn	{Abs	{FriendlyScoutHomeBase}, 
						 	 Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},

			NumInWing	6,
			NumInForm	EncounterList04,
			Duty		DUTYCAP,

			Posn	{Abs	{CPP},
					 Rel	{Y {Random	-FT_5000,25,FT_100},
							 Intercept	{CPP,FriendlyScoutHomeBase},
							 Bearing	{Select ANGLES_315Deg,90,ANGLES_1Deg},
					 		 Range	{Random	VISINEDGE,VISBOUNDARYSIZE,METRES01}
							 }
					},
		   	AirItem	
			{
				Side		NAT_FRIEND,
				Type		FriendlyScoutType00,
				Home		FriendlyScoutHomeBase,
				Squadron	{FriendlyScoutSquad,PS_5,PS_6,PS_7,PS_8},
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, FriendlyScoutTactician,FriendlyScoutMrAverage,FriendlyScoutCavalier}},
				Morale		{Random	FriendlyScoutMorale,40,1}
			}
		}
	};

//---------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_ENEMYSCOUTLAND=EVland00.BF,
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		Setval	{HeightStepSize, Int {Random 0,30,1}},
		Setval	{RandAngle, Bearing {Random ANGLES_300Deg,2,ANGLES_90Deg}},
		AirGroup	
		{
			Route	
			{
				WayPoint	
				{
					Posn	{Abs	{CPP}, 
//DeadCode MS 02Dec96 							 Rel	{Y {Select -FT_3000,HeightStepSize,FT_100},
							 Rel	{Intercept	{CPP,EnemyScoutHomeBase},
									 Bearing	ANGLES_0Deg,
									 Pitch		ANGLES_0Deg,
									 Range	HALFVISINEDGE	
									}
							},
					Action	wpacnoactionno,
					Range	MARGIN
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyScoutHomeBase}, 
						 	 Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},

			NumInWing	6,
			NumInForm	EncounterList04,
			Duty		DUTYCAP,

			Posn	{Abs	{CPP},
					 Rel	{Y {Select -FT_3000,HeightStepSize,FT_100},
							 Intercept	{CPP,EnemyScoutHomeBase},
							 Bearing	{Random RandAngle,30,ANGLES_1Deg},
					 		 Range		VISINEDGE
							 }
					},
		   	AirItem	
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Home		EnemyScoutHomeBase,
				Squadron	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1}
			}
		}
	};

//---------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_FRIENDLYCHARGELAND=EVFrds03.BF,
		Setval	{GlobalSkillMin, FriendlyChargeSkillMin},
		Setval	{GlobalSkillMax, FriendlyChargeSkillMax},
		AirGroup	
		{
			Route	
			{
				WayPoint	
				{
					Posn	{Abs	{FriendlyChargeHomeBase}, 
						 	 Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},

			NumInWing	6,
			NumInForm	EncounterList04,
			Duty		DUTYCAP,

			Posn	{Abs	{CPP},
					 Rel	{Y {Random	-FT_5000,25,FT_100},
							 Intercept	{CPP,FriendlyChargeHomeBase},
							 Bearing	{Select ANGLES_315Deg,90,ANGLES_1Deg},
					 		 Range	{Random	VISINEDGE,VISBOUNDARYSIZE,METRES01}
							 }
					},
		   	AirItem	
			{
				Side		NAT_FRIEND,
				Type		FriendlyChargeType00,
				Home		FriendlyChargeHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List {Random 6}, SKILL_VETERAN,SKILL_VETERAN,SKILL_REGULAR,SKILL_REGULAR,SKILL_REGULAR,SKILL_POOR},
				Character	FriendlyChargeCharacter,
				Morale		{Random	FriendlyChargeMorale,40,1}
			}
		}
	};

//---------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_STRAGGLER00=EVMeat00.BF,

		Setval	{GlobalSkillMin, EnemyChargeSkillMin},
		Setval	{GlobalSkillMax, EnemyChargeSkillMax},
		AirGroup	EnemyStragglers00_A =
		{
			Route	EnemyStragglersRoute00_A =	
			{
				WayPoint	WPEnemyStraggler00_A =	
				{
					Posn	{Abs	{EnemyObjective},
						 	 Abs	{Y HeightSize}
							},
					Range	MARGIN,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyChargeHomeBase},
						 	 Abs	{Y HeightSize}
							},
					Range	STANDARDTRIGGER,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyChargeHomeBase},
						 	 Abs	{Y FT_EnterLandingPattern}
							},
					Range	DistEnterLandingPattern,
					Action	wpalandingno
				}
			},

			NumInWing	1,
			NumInForm	1,
//			Duty		DUTYCHARGEDUTY, FIXME!!!
			Duty		DUTYRECONN,

			Posn		{Abs	{CPP}, 
						 Abs	{Y HeightSize},
						 Rel	{Intercept	{CPP,CWP},
								 Bearing	{Random	ANGLES_225Deg,270,ANGLES_1Deg},
								 Range	VISINEDGE
								}
						},

		   	AirItem	EnemyStragglersItem00_A	=
			{
				Side		NAT_ENEMY,
				Type		EnemyChargeType00,
				Squadron	{EnemyChargeSquad},
				Home		EnemyChargeHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List {Random 6}, SKILL_VETERAN,SKILL_VETERAN,SKILL_REGULAR,SKILL_REGULAR,SKILL_REGULAR,SKILL_POOR},
				Character	EnemyChargeCharacter,
				Morale		{Random	EnemyChargeMorale,40,1},
//DAMAGE IS IN H\3DINSTR.H
				Damage		0x12
			}
		},
		Setval	{GlobalSkillMin, EnemyChargeSkillMin},
		Setval	{GlobalSkillMax, EnemyChargeSkillMax},
		AirGroup	EnemyStragglers00_B=
		{
			Route	WPEnemyStraggler00_A,

			NumInWing	6,
			NumInForm	EncounterList03,
//			Duty		DUTYSITTINGDUCK,	FIXME!!!!
			Duty		DUTYRECONN,

			Posn		{Abs	EnemyStragglersItem00_A, 
						 Rel	{Intercept	{EnemyStragglersItem00_A, EnemyObjective},
								 Bearing	ANGLES_0Deg,
								 Range		{Random	METRES300,200,METRES01}
								}
						},

		   	AirItem	EnemyStragglersItem00_B	=
			{
				Side		NAT_ENEMY,
				Type		EnemyChargeType00,
				Squadron	{EnemyChargeSquad},
				Home		EnemyChargeHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Follower	EnemyStragglersItem00_A,
				Skill		{List {Random 6}, SKILL_VETERAN,SKILL_VETERAN,SKILL_REGULAR,SKILL_REGULAR,SKILL_REGULAR,SKILL_POOR},
				Character	EnemyChargeCharacter,
				Morale		{Random	EnemyChargeMorale,40,1}
			}
		}
	};

//***
		
//---------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_STRAGGLER01=EVMeat01.BF,
		Setval	{GlobalSkillMin, EnemyChargeSkillMin},
		Setval	{GlobalSkillMax, EnemyChargeSkillMax},
		AirGroup	EnemyStragglers01_A =
		{
			Route	EnemyStragglersRoute01_A =	
			{
				WayPoint	WPEnemyStraggler01_A =	
				{
					Posn	{Abs	{EnemyObjective},
						 	 Abs	{Y HeightSize}
							},
					Range	MARGIN,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyChargeHomeBase},
						 	 Abs	{Y HeightSize}
							},
					Range	STANDARDTRIGGER,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyChargeHomeBase},
						 	 Abs	{Y FT_EnterLandingPattern}
							},
					Range	DistEnterLandingPattern,
					Action	wpalandingno
				}
			},

			NumInWing	1,
			NumInForm	1,
//			Duty		DUTYCHARGEDUTY, FIXME!!!
			Duty		DUTYRECONN,

			Posn		{Abs	{CPP}, 
						 Abs	{Y HeightSize},
						 Rel	{Intercept	{CPP,CWP},
								 Bearing	{Random	ANGLES_225Deg,270,ANGLES_1Deg},
								 Range	VISINEDGE
								}
						},

		   	AirItem	EnemyStragglersItem01_A	=
			{
				Side		NAT_ENEMY,
				Type		EnemyChargeType00,
				Squadron	{EnemyChargeSquad},
				Home		EnemyChargeHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List {Random 6}, SKILL_VETERAN,SKILL_VETERAN,SKILL_REGULAR,SKILL_REGULAR,SKILL_REGULAR,SKILL_POOR},
				Character	EnemyChargeCharacter,
				Morale		{Random	EnemyChargeMorale,40,1},
//DAMAGE IS IN H\3DINSTR.H
				Damage		0x12
			}
		},
		Setval	{GlobalSkillMin, EnemyChargeSkillMin},
		Setval	{GlobalSkillMax, EnemyChargeSkillMax},
		AirGroup	EnemyStragglers01_B=
		{
			Route	WPEnemyStraggler01_A,

			NumInWing	6,
			NumInForm	EncounterList03,
//			Duty		DUTYSITTINGDUCK,	FIXME!!!!
			Duty		DUTYRECONN,

			Posn		{Abs	EnemyStragglersItem01_A, 
						 Rel	{Intercept	{EnemyStragglersItem01_A, EnemyObjective},
								 Bearing	ANGLES_0Deg,
								 Range		{Random	METRES300,200,METRES01}
								}
						},

		   	AirItem	EnemyStragglersItem01_B	=
			{
				Side		NAT_ENEMY,
				Type		EnemyChargeType00,
				Squadron	{EnemyChargeSquad},
				Home		EnemyChargeHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Follower	EnemyStragglersItem01_A,
				Skill		{List {Random 6}, SKILL_VETERAN,SKILL_VETERAN,SKILL_REGULAR,SKILL_REGULAR,SKILL_REGULAR,SKILL_POOR},
				Character	EnemyChargeCharacter,
				Morale		{Random	EnemyChargeMorale,40,1}
			}
		},
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
  		AirGroup
  		{
  			Route	WPEnemyStraggler01_A,
  	
  			NumInWing	6,
  			NumInForm	EncounterList03,
  			Duty		DUTYCAP,
  
  			Posn		{Abs	EnemyStragglersItem01_B}, 
  
  		   	AirItem 			
 			{
  				Side		NAT_ENEMY,
  				Type		EnemyScoutType00,
  				Home		EnemyScoutHomeBase,
  				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1},
  				Leader		EnemyStragglersItem01_A
  			}
  		}
 	};


		
//---------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_FRIENDLYCHARGEBAIT=EVtemp01.BF
	};

//where is this used??
//---------------------------------------------------------------------------
//DeadCode MS 03Oct96 	BattleField
//DeadCode MS 03Oct96 	{
//DeadCode MS 03Oct96 		FileName	BFEV_ENEMYCHARGERESCUE=EVtemp02.BF
//DeadCode MS 03Oct96 	};
//DeadCode MS 03Oct96 
//DeadCode MS 03Oct96 //where is this used??
//---------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_FRIENDLYMISTAKE=EVtemp03.BF,
		Setval	{GlobalSkillMin, FriendlyScoutSkillMin},
		Setval	{GlobalSkillMax, FriendlyScoutSkillMax},
		AirGroup		
		{
			Route	
			{
				WayPoint
				{
				    Target	CPP,	 
				    Action	wpfiregun,
					Range	METRES100
				},	
				WayPoint	
				{
					Posn	{Abs	{FriendlyScoutHomeBase},	 
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	1,
			NumInForm	1,
			Duty		DUTYCAP,	

			Posn	{Abs 	{CPP},
					 Rel	{Intercept	{CPP,CWP},
							 Bearing	{Random	ANGLES_225Deg,270,ANGLES_1Deg},
				 			 Range		VISINEDGE
							}
					},

		   	AirItem		     	
			{
				Side		NAT_FRIEND,
				Type		FriendlyScoutType00,
				Home		FriendlyScoutHomeBase,
				Squadron	{FriendlyScoutSquad,PS_5,PS_6,PS_7,PS_8},
				MoveCode	AUTO_FOLLOWWP,	
				Skill		SKILL_POOR,
				Character	FriendlyScoutCavalier,
				Morale		MORALE_HIGH
			}
		}
	};

//---------------------------------------------------------------------------

	BattleField
	{
		FileName	BFEV_CLEVERDECOY00=EVdcoy00.BF,
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup		
		{
			Route	
			{
				WayPoint	
				{
					Posn	{Abs 	{CPP}},
					Action	wpacnoactionno,
					Range	HALFIDENTRANGE
				},
				WayPoint	
				{
					Posn	{Abs 	{CPP},
							 Rel	{Intercept	{CPP,EnemyScoutHomeBase},
						 			 Bearing	ANGLES_0Deg,
						 			 RangePercent	80
									}
							},
					Action	wpacnoactionno,
					Range	MARGIN
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyScoutHomeBase},	 
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	6,
			NumInForm	EncounterList01,
			Duty		DUTYCAP,
//			duty		dumbassduty								//MS 08Mar96

			Posn	{Abs 	{CPP},
					 Rel	{Intercept	{CPP,CWP},
				 			 Bearing	{Random	ANGLES_345Deg,30,ANGLES_1Deg},
				 			 Pitch		ANGLES_0Deg,
				 			 Range		VISINEDGE
							}
					},

		   	AirItem		     	
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
//				movecode	dumbfollowwp???						//MS 08Mar96
				Skill		SKILL_VETERAN,
				Character	EnemyScoutCavalier,
				Morale		{Random	EnemyScoutMorale,40,1}
			}
		}
	};

//---------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_CLEVERDECOY01=EVdcoy01.BF,
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup		
		{
			Route	
			{
				WayPoint	
				{
					Posn	{Abs 	{CPP}},
					Action	wpacnoactionno,
					Range	MARGIN
				},
				WayPoint	
				{
					Posn	{Abs 	{CPP},
							 Rel	{Intercept	{CPP,CWP},
						 			 Bearing	ANGLES_180Deg,
						 			 Range		METRES5000
									}
							},
					Action	wpacnoactionno,
					Range	MARGIN
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyScoutHomeBase}, 
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	1,
			NumInForm	1,
			Duty		DUTYCAP,
//fixme			duty		dumbassduty								//MS 08Mar96

			Posn	{Abs 	{CPP},
					 Rel	{Y	{Random	FT_1000,1000,FT_1},
							 Intercept	{CPP,CWP},
				 			 Bearing	{Random	ANGLES_345Deg,30,ANGLES_1Deg},
				 			 Range		VISINEDGE
							}
					},

		   	AirItem		     	
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
//				movecode	dumbfollowwp???						//MS 08Mar96
				Skill		SKILL_REGULAR,
				Character	EnemyScoutCavalier,
				Morale		{Random	EnemyScoutMorale,40,1}
			}
		}
	};

//---------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_CLEVERDECOY02=EVdcoy02.BF,
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup		
		{
			Route	
			{
				WayPoint	
				{
					Posn	{Abs 	{CPP}},
					Action	wpacnoactionno,
					Range	MARGIN
				},
				WayPoint	
				{
					Posn	{Abs 	{CPP},
							 Rel	{Intercept	{CPP, CWP},
						 			 Bearing	ANGLES_180Deg,
						 			 Range		METRES5000
									}
							},
					Action	wpacnoactionno,
					Range	MARGIN
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyScoutHomeBase}, 
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	1,
			NumInForm	1,
			Duty		DUTYCAP,
//fixme			duty		dumbassduty								//MS 08Mar96

			Posn	{Abs 	{CPP},
					 Rel	{Y	{Random	FT_1000,1000,FT_1},
							 Intercept	{CPP, CWP},
				 			 Bearing	{Random	ANGLES_345Deg,30,ANGLES_1Deg},
				 			 Range		VISINEDGE
							}
					},

		   	AirItem		     	
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
//				movecode	dumbfollowwp???						//MS 08Mar96
				Skill		SKILL_REGULAR,
				Character	EnemyScoutCavalier,
				Morale		{Random	EnemyScoutMorale,40,1},
				Event		{Event	BFEV_ENEMYSUNATTACK,
							 Setval	{EnemyScoutType00, EnemyScoutType00},
							 Setval	{EnemyScoutHomeBase, EnemyScoutHomeBase},
							 Setval	{EnemyScoutMorale, EnemyScoutMorale},
							 Setval	{EnemyScoutCharacter, EnemyScoutCharacter}
							}
			}
		}
	};

//---------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_CLEVERDECOY03=EVdcoy03.BF,
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup		
		{
			Route	
			{
				WayPoint	
				{
					Posn	{Abs 	{CPP},
							 Rel	{Intercept	{CPP, CWP},
						 			 Bearing	ANGLES_0Deg,
						 			 Range	TWICEIDENTRANGE
									}
							},		
					Action	wpacnoactionno,
					Range	IDENTRANGE
				},
				WayPoint	
				{
					Posn	{Abs 	{CPP},
							 Rel	{Intercept	{CPP, EnemyScoutHomeBase},
						 			 Bearing	ANGLES_0Deg,
						 			 Range		STANDARDTRIGGER
									}
							},
					Action	wpacnoactionno,	
					Range	HALFSTANDARDTRIGGER,
					Event	{Event	BFCH_CLEVERDECOY03,
							 Setval	{EnemyScoutType00, EnemyScoutType00},
							 Setval	{EnemyScoutHomeBase, EnemyScoutHomeBase},
							 Setval	{EnemyScoutMorale, EnemyScoutMorale},
							 Setval	{EnemyScoutCharacter, EnemyScoutCharacter}
							}
				},
				WayPoint	
				{
					Posn	{Abs 	{CPP},
							 Rel	{Intercept	{CPP, EnemyScoutHomeBase},
						 			 Bearing	ANGLES_0Deg,
						 			 Range		METRES2000
									}
							},
					Action	wpacnoactionno,	//fixme release from dumb duty
					Range	QTRSTANDARDTRIGGER
				},
				WayPoint	
				{
					Posn	{Abs 	{CPP}},
					Action	wpacircleno,
					Range	MARGIN
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyScoutHomeBase}, 
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	1,
			NumInForm	1,
			Duty		DUTYCAP,
//fixme			duty		dumbassduty								//MS 08Mar96

			Posn	{Abs 	{CPP},
					 Rel	{Y	{Random	FT_1000,1000,FT_1},
							 Intercept	{CPP, CWP},
				 			 Bearing	{Random	ANGLES_345Deg,30,ANGLES_1Deg},
				 			 Range		{Random	VISINEDGE,VISBOUNDARYSIZE,METRES01}
							}
					},

		   	AirItem		Decoy03_Item =		     	
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
//fixme				movecode	dumbfollowwp???						//MS 08Mar96
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1}
			}
		}
	};

//---------------------------------------------------------------------------
	BattleField
	{
		FileName	BFCH_CLEVERDECOY03=CHdcoy03.BF,
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup		
		{
			Route
			{
				WayPoint	
				{
					Posn	{Abs	{EnemyScoutHomeBase}, 
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	2,
			NumInForm	4,
			Duty		DUTYCAP,
//fixme			duty		DUTYCLOSEESCORT							//MS 04Jul96

			Posn	{Abs 	{CWP}},

		   	AirItem		
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Leader		Decoy03_Item,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1}
			}
		}
	};

//---------------------------------------------------------------------------

	BattleField
	{
		FileName	BFEV_ENEMYSUNATTACK=EVSun00.BF,
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup		
		{
			Route	
			{
				WayPoint	
				{
					Posn	{Abs 	{CPP}},
					Action	wpacnoactionno,	
					Range	STANDARDTRIGGER
				},
				WayPoint	
				{
					Posn	{Abs	{CPP},
							 Rel	{Intercept	{CPP, EnemyScoutHomeBase},
									 Bearing	ANGLES_0Deg,
						 			 RangePercent	80
									}
							},
					Range 	MARGIN,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyScoutHomeBase}, 
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	3,
			NumInForm	EncounterList03,
			Duty		DUTYCAP,

			Posn	{Abs 	{CPP},
					 Rel	{Intercept	{CPP,EnemyScoutHomeBase},		
//fixme sunposition
				 			 Bearing	ANGLES_0Deg,
							 Pitch		ANGLES_0Deg,
				 			 Range		JUMPINBAND
							}
					},

		   	AirItem		
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1}
			}
		}
	};

//---------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_RAWS00=EVraws00.BF,
		Setval	{GlobalSkillMin, FriendlyScoutSkillMin},
		Setval	{GlobalSkillMax, FriendlyScoutSkillMax},
		AirGroup	BFEV_RAWS00_Airgroup00 =	
		{
			Route	
			{
				WayPoint	
				{
					Target	FriendlyObjective, 
					Posn	{Abs	{Y FT_EnterLandingPattern}},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	4,
			NumInForm	EncounterList04,
			Duty		DUTYCAP,
//fixme		Formation	LINEASTERN???

			Posn		{Abs	{CWP},
						 Abs	{Y	FT_EnterLandingPattern},
						 Rel	{Intercept	{EnemyScoutHomeBase,CPP},
								Bearing	{Random ANGLES_345Deg,30,ANGLES_1Deg},
							 	Range	METRES1000
								}
						}, 

		   	AirItem	BFEV_RAWS00_AirItem00 =	
			{
				Side		NAT_FRIEND,
				Type		FriendlyScoutType00,
				Home		FriendlyScoutHomeBase,
				Squadron	{FriendlyScoutSquad,PS_5,PS_6,PS_7,PS_8},
				MoveCode	ACM_GOHOME,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, FriendlyScoutTactician,FriendlyScoutMrAverage,FriendlyScoutCavalier}},
				Morale		{Random	FriendlyScoutMorale,40,1}
			}
		},
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Target	FriendlyObjective, 
					Posn	{Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpdivebombstraffeno,
					Range	DistEnterLandingPattern
				},
				WayPoint	
				{
					Posn	{Abs	{FriendlyObjective}, 
						 	 Abs	{Y FT_1000},
							 Rel	{Intercept	{FriendlyObjective,EnemyScoutHomeBase},
									 Bearing	ANGLES_0Deg,
									 RangePercent	10
									}
							},
					Range 	MARGIN,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	{Abs	{FriendlyObjective}, 
						 	 Abs	{Y FT_4000},
							 Rel	{Intercept	{FriendlyObjective,EnemyScoutHomeBase},
									 Bearing	ANGLES_0Deg,
									 RangePercent	30
									}
							},
					Range 	MARGIN,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyScoutHomeBase}, 
						 	Abs	{Y FT_4000}
							},
					Action	wpacnoactionno,
					Range	STANDARDTRIGGER
				},
				WayPoint	
				{
					Target	EnemyScoutHomeBase, 
					Posn	{Abs	{Y FT_EnterLandingPattern}},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	1,
			NumInForm	1,
			Duty		DUTYCAP,

			Posn		{Abs	BFEV_RAWS00_AirItem00,
						 Rel	{Y 	-FT_20,
								 Intercept	{BFEV_RAWS00_AirItem00,FriendlyObjective},
								 Bearing	ANGLES_180Deg,
						 		 Range	METRES50
								}
						},
		   	AirItem	
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		SKILL_ACE,
				Morale		MORALE_HIGH,
				Character	EnemyScoutTactician
			}
		}
	};

//---------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_ENEMYSCOUTGROUNDCAPABLE=EVstrf00.BF,
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup	
		{
			Route	
			{
				WayPoint	
				{
					Posn	{Abs	{FriendlyObjective},
							 Abs	{Y FT_Straffe}
							},
					Range	MARGIN,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyObjective},
							 Abs	{Y FT_Straffe}
							},
					Range	MARGIN,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyObjective},
							 Abs	{Y FT_5000},
							 Rel	{Intercept	{EnemyObjective,EnemyScoutHomeBase},
									 Bearing	ANGLES_0Deg,
									 RangePercent	20
									}
							},
					Range	MARGIN,
					Action	wpacnoactionno
				},
				WayPoint
				{
					Posn	{Abs	{EnemyScoutHomeBase},
						 	Abs	{Y	FT_5000}
							},
					Action	wpacnoactionno,
					Range	STANDARDTRIGGER
				},
				WayPoint
				{
					Posn	{Abs	{EnemyScoutHomeBase},
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	6,
			NumInForm	EncounterList02,
			Duty		DUTYCAP,
//fixeme			Duty		DUTYGroundcapable,

			Posn	{Abs	{CPP},
					 Abs	{Y FT_Straffe},		 
					 Rel	{Intercept	{CPP,FriendlyObjective},
						 	 Bearing	{Random	ANGLES_270Deg,180,ANGLES_1Deg},
						 	 Range		VISINEDGE
							}
					},

		   	AirItem	
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1}
			}
		}
	};

//---------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_ENEMYSWEEP=EVdfnd00.BF,	
		Setval{HeightStepSize,Int {Random 0,2500,1}},
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup	
		{
			Route	
			{
				WayPoint	
				{
					Posn	{Abs	{CPP},
							 Rel	{Y {Select	-FT_500,HeightStepSize,FT_1},
									 Intercept	{CPP, CWP},
								 	 Bearing	ANGLES_0Deg,
								 	 RangePercent	100
									 }
							},
					Range	MARGIN,
					Action	wpacnoactionno
				},
				WayPoint
				{
					Posn	{Abs	{EnemyScoutHomeBase},	
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	6,
			NumInForm	EncounterList06,
			Duty		DUTYCAP,

			Posn	{Abs	{CPP},
					 Rel	{Y {Select	-FT_500,HeightStepSize,FT_1},
							 Intercept	{CPP, CWP},
						 	 Bearing	{Random	ANGLES_270Deg,180,ANGLES_1Deg},
						 	 Range		VISINEDGE
							}
					},

		   	AirItem	
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1}
			}
		}
	};

//---------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_ENEMYHIDEFENCE00=EVdfnd02.BF,
		Setval{HeightStepSize,Int {Random 0,2500,1}},

		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup	BFEV_ENEMYHIDEFENCE00_Airgroup00=
		{
			Route	
			{
				WayPoint	
				{
					Posn	{Abs	{CPP},
							 Rel	{Y {Select	FT_1000,HeightStepSize,FT_1},
									 Intercept	{CPP, CWP},
								 	 Bearing	ANGLES_0Deg,
								 	 RangePercent	100
									 }
							},
					Range	MARGIN,
					Action	wpacircleno
				},
				WayPoint
				{
					Posn	{Abs	{EnemyScoutHomeBase},	
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	6,
			NumInForm	EncounterList01,
			Duty		DUTYCAP,

					Posn	{Abs	{CPP},
							 Rel	{Y {Select	FT_1000,HeightStepSize,FT_1},
									 Intercept	{CPP, CWP},
								 	 Bearing	ANGLES_0Deg,
								 	 RangePercent	100
									 }
							},

		   	AirItem	
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1}
			}
		}
	};

//---------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_ENEMYLOWDEFENCE00=EVdfnd03.BF,	
		Setval{HeightStepSize,Int {Random 0,2500,1}},

		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup	BFEV_ENEMYLOWDEFENCE00_Airgroup00=
		{
			Route	
			{
				WayPoint
				{
					Posn	{Abs	{CPP},
							 Rel	{Y {Select	-FT_2500,HeightStepSize,FT_1},
									 Intercept	{CPP, CWP},
								 	 Bearing	ANGLES_0Deg,
								 	 RangePercent	100
									 }
							},
					Range	MARGIN,
					Action	wpacircleno
				},
				WayPoint
				{
					Posn	{Abs	{EnemyScoutHomeBase},	
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	6,
			NumInForm	EncounterList03,
			Duty		DUTYCAP,

					Posn	{Abs	{CPP},
							 Rel	{Y {Select	-FT_2500,HeightStepSize,FT_1},
									 Intercept	{CPP, CWP},
								 	 Bearing	ANGLES_0Deg,
								 	 RangePercent	100
									 }
							},

		   	AirItem	
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1}
			}
		}
	};

//---------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_ENEMYHIANDLOWDEFENCE00=EVdfnd04.BF,	
		Setval{HeightStepSize,Int {Random 0,2500,1}},
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup	BFEV_ENEMYHIDEFENCE00_Airgroup00,
		AirGroup	BFEV_ENEMYLOWDEFENCE00_Airgroup00
	};

//---------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_LONEENEMYWARNSAF=EVdfnd05.BF,
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		Setval	{RandAngle, Bearing {Random ANGLES_300Deg,2,ANGLES_90Deg}},
		
		AirGroup	BFEV_LONEENEMYWARNSAF_EnemyAirGroup00 =
		{
			Route	
			{
				WayPoint	
				{
					Posn	{Abs	{CPP}, 
							 Rel	{Intercept	{CPP,EnemyScoutHomeBase},
									 Bearing	ANGLES_0Deg,
									 Range	VISINEDGE	
									}
							},
					Action	wpacnoactionno,
					Range	MARGIN
				},
				WayPoint
				{
					Posn	{Abs	{EnemyScoutHomeBase},
						 	 Abs	{Y FT_3000}
							},
					Action	wpacnoactionno,
					Range	HALFVISINEDGE,
					Event	{Event	BFEV_LONEENEMYWARNSAFBUDDIESSTALL,
							 Setval	{EnemyScoutType00, EnemyScoutType00},
							 Setval	{EnemyScoutHomeBase, EnemyScoutHomeBase},
							 Setval	{EnemyScoutMorale, EnemyScoutMorale},
							 Setval	{EnemyScoutTactician, EnemyScoutTactician},
							 Setval	{EnemyScoutMrAverage, EnemyScoutMrAverage},
							 Setval	{EnemyScoutCavalier, EnemyScoutCavalier},
							 Setval	{EnemyScoutSquad, EnemyScoutSquad},
							 Setval	{PS_1, PS_1},
							 Setval	{PS_1, PS_2},
							 Setval	{PS_1, PS_3},
							 Setval	{PS_1, PS_4}
							}
				},
				WayPoint	LoneEnemyWarnsAf_WP00 =
				{
					Posn	{Abs	{CWP},
							 Rel	{Intercept	{EnemyScoutHomeBase,CWP},
									 Bearing	ANGLES_90Deg,
									 Range	HALFSTANDARDTRIGGER
									}
							},
					Range	MARGIN,
 					Action	wpstartloopno
				},
				WayPoint
				{
					Posn	{Abs	{CWP},
							 Rel	{Intercept	{EnemyScoutHomeBase,CWP},
									 Bearing	ANGLES_270Deg,
									 Range	HALFSTANDARDTRIGGER
									}
							},
					Range	MARGIN,
					Action	wpstoploopchkno
				},
				WayPoint
				{
					Posn	{Abs	{EnemyScoutHomeBase},
						 	 Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	1,
			NumInForm	1,
			Duty		DUTYCAP,
			Formation	SQUAD_BAIT,

			Posn	{Abs	{CPP},
					 Rel	{Intercept	{CPP,EnemyScoutHomeBase},
							 Bearing	{Random RandAngle,30,ANGLES_1Deg},
					 		 Range		VISINEDGE
							 }
					},
												
		   	AirItem	BFEV_LONEENEMYWARNSAF_Item00 =
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		SKILL_REGULAR,
				Character	CHAR_TACTICIAN,
				Morale		MORALE_ROCKBOTTOM,
				SetUID		UID_LoneEnemyWarnsAf
			}
		}
	};

//---------------------------------------------------------------------------

	BattleField
	{
		FileName	BFEV_LONEENEMYWARNSAFBUDDIESSTALL=EVdfnd06.BF,	
//DeadCode MS 10Nov96 		Setval	{AngleStepSize,Int {Random 0,2,1}},
//DeadCode MS 10Nov96 
//DeadCode MS 10Nov96 		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
//DeadCode MS 10Nov96 		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
//DeadCode MS 10Nov96 		AirGroup	BFEV_LONEENEMYWARNSAF_EnemyAirGroup00,
//DeadCode MS 10Nov96 		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
//DeadCode MS 10Nov96 		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
//DeadCode MS 10Nov96 		AirGroup
//DeadCode MS 10Nov96 		{
//DeadCode MS 10Nov96 			Route	
//DeadCode MS 10Nov96 			{
//DeadCode MS 10Nov96 				WayPoint
//DeadCode MS 10Nov96 				{
//DeadCode MS 10Nov96 					Target	CPP,
//DeadCode MS 10Nov96 					Range	IDENTRANGE,
//DeadCode MS 10Nov96 					Action	wpacnoactionno
//DeadCode MS 10Nov96 				},
//DeadCode MS 10Nov96 				WayPoint
//DeadCode MS 10Nov96 				{
//DeadCode MS 10Nov96 					Posn	{Abs	{EnemyScoutHomeBase},
//DeadCode MS 10Nov96 						 	 Abs	{Y FT_EnterLandingPattern}
//DeadCode MS 10Nov96 							},
//DeadCode MS 10Nov96 					Action	wpalandingno,
//DeadCode MS 10Nov96 					Range	DistEnterLandingPattern
//DeadCode MS 10Nov96 				},
//DeadCode MS 10Nov96 				WayPoint
//DeadCode MS 10Nov96 				{
//DeadCode MS 10Nov96 					Posn	{Abs	{EnemyScoutHomeBase},
//DeadCode MS 10Nov96 						 	 Abs	{Y FT_EnterLandingPattern}
//DeadCode MS 10Nov96 							},
//DeadCode MS 10Nov96 					Action	wpalandingno,
//DeadCode MS 10Nov96 					Range	DistEnterLandingPattern
//DeadCode MS 10Nov96 				}
//DeadCode MS 10Nov96 			},
//DeadCode MS 10Nov96 			NumInWing	3,
//DeadCode MS 10Nov96 			NumInForm	EncounterList03,
//DeadCode MS 10Nov96 			Duty		DUTYCAP,
//DeadCode MS 10Nov96 
//DeadCode MS 10Nov96 			Posn	{Abs	BFEV_LONEENEMYWARNSAF_Item00,
//DeadCode MS 10Nov96 					 Rel	{Y {Random	0,50,FT_1},
//DeadCode MS 10Nov96 							 Bearing	ANGLES_0Deg,
//DeadCode MS 10Nov96 							 Range		METRES20
//DeadCode MS 10Nov96 							}
//DeadCode MS 10Nov96 					},
//DeadCode MS 10Nov96 
//DeadCode MS 10Nov96 		   	AirItem	
//DeadCode MS 10Nov96 			{
//DeadCode MS 10Nov96 				Side		NAT_ENEMY,
//DeadCode MS 10Nov96 				Type		EnemyScoutType00,
//DeadCode MS 10Nov96 				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
//DeadCode MS 10Nov96 				Home		EnemyScoutHomeBase,
//DeadCode MS 10Nov96 				MoveCode	AUTO_FOLLOWWP,
//DeadCode MS 10Nov96 				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
//DeadCode MS 10Nov96 				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
//DeadCode MS 10Nov96 				Morale		{Random	EnemyScoutMorale,40,1}
//DeadCode MS 10Nov96 			}
//DeadCode MS 10Nov96 		}
//DeadCode MS 10Nov96 	};

		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup
		{
			Route	LoneEnemyWarnsAf_WP00,
	
			NumInWing	3,
			NumInForm	3,
			Duty		DUTYCAP,
			Formation	SQUAD_BAIT,

			Posn	{Abs	{EnemyScoutHomeBase},
					 Abs	{Y	FT_TakeOff}
					},

		   	AirItem	
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1},
				Follower	UID_LoneEnemyWarnsAf
			}
		}
	};

//---------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_FRIENDLYCHARGEUNDERATTACK=EVdfnd07.BF,
		Setval{HeightStepSize,Int {Random 0,50,100}},

		Setval	{GlobalSkillMin, FriendlyChargeSkillMin},
		Setval	{GlobalSkillMax, FriendlyChargeSkillMax},
		AirGroup	
		{
			Route
			{
				WayPoint	BFEV_FRIENDLYCHARGEUNDERATTACK_Wp00 =	
				{
					Posn	{Abs	{CPP},
							 Rel	{Y	{Select	-FT_4000,HeightStepSize,FT_1},
									 Intercept	{CPP,FriendlyObjective},	
									 Bearing	ANGLES_0Deg,
				 					 Range	VISINEDGE
									}
							},
					Action	wpacnoactionno,
					Range	MARGIN
				},
				WayPoint	
				{
					Posn	{Abs	BFEV_FRIENDLYCHARGEUNDERATTACK_Wp00,
							 Rel	{Intercept	{BFEV_FRIENDLYCHARGEUNDERATTACK_Wp00,FriendlyChargeHomeBase},	
									 Bearing	ANGLES_0Deg,
				 					 RangePercent	100
									}
							},
					Action	wpacnoactionno,
					Range	STANDARDTRIGGER
				},
				WayPoint	
				{
					Posn	{Abs	{FriendlyChargeHomeBase},	
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	1,
			NumInForm	1,
			Duty		DUTYCAP,

			Posn		{Abs	BFEV_FRIENDLYCHARGEUNDERATTACK_Wp00,
						 Rel	{Intercept	{CPP,FriendlyObjective},	
								 Bearing	ANGLES_0Deg,
				 			 	 Range	METRES100
								}
						},

		   	AirItem	BFEV_FRIENDLYCHARGEUNDERATTACK_Item00 =
			{
				Side		NAT_FRIEND,
				Type		FriendlyChargeType00,
				Home		FriendlyChargeHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List {Random 6}, SKILL_VETERAN,SKILL_VETERAN,SKILL_REGULAR,SKILL_REGULAR,SKILL_REGULAR,SKILL_POOR},
				Character	FriendlyChargeCharacter,
				Morale		{Random	FriendlyChargeMorale,40,1}
			}
		},
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup
		{
			Route	BFEV_FRIENDLYCHARGEUNDERATTACK_Route00 =
			{
				WayPoint	
				{
					Posn	{Abs	BFEV_FRIENDLYCHARGEUNDERATTACK_Wp00},
					Action	wpacnoactionno,
					Range	MARGIN
				},
				WayPoint	
				{
					Posn	{Abs	BFEV_FRIENDLYCHARGEUNDERATTACK_Wp00,
							 Rel	{Intercept	{CPP,EnemyScoutHomeBase},	
									 Bearing	ANGLES_0Deg,
				 					 RangePercent	100
									}
							},
					Action	wpacnoactionno,
					Range	STANDARDTRIGGER
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyScoutHomeBase},	
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	6,
			NumInForm	EncounterList01,
			Duty		DUTYCAP,

			Posn		{Abs	{CPP},
						 Rel	{Y	{Random	FT_200,200,FT_1},
							 	 Intercept	{CPP,BFEV_FRIENDLYCHARGEUNDERATTACK_Item00},	
							 	 Bearing	ANGLES_330Deg,
							 	 Range	VISINEDGE
								}
						},
		   	AirItem		
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_COMBAT,	
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1},
				Target		BFEV_FRIENDLYCHARGEUNDERATTACK_Item00
			}
		},
		AirGroup
		{
			Route	BFEV_FRIENDLYCHARGEUNDERATTACK_Route00,

			NumInWing	6,
			NumInForm	EncounterList01,
			Duty		DUTYCAP,

			Posn		{Abs	BFEV_FRIENDLYCHARGEUNDERATTACK_Item00,
						 Rel	{Y	{Random	FT_500,100,FT_1},
							 	 Intercept	{BFEV_FRIENDLYCHARGEUNDERATTACK_Item00,FriendlyChargeHomeBase},	
							 	 Bearing	ANGLES_180Deg,
							 	 Range		{Random	METRES600,200,METRES01} 
								}
						},
		   	AirItem		
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_COMBAT,	
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1},
				Target		BFEV_FRIENDLYCHARGEUNDERATTACK_Item00
			}
		},
		AirGroup
		{
			Route	BFEV_FRIENDLYCHARGEUNDERATTACK_Route00,

			NumInWing	6,
			NumInForm	EncounterList01,
			Duty		DUTYCAP,

			Posn		{Abs	{CPP},
						 Rel	{Y	{Random	-FT_100,200,FT_1},
							 	 Intercept	{CPP,BFEV_FRIENDLYCHARGEUNDERATTACK_Item00},	
							 	 Bearing	ANGLES_30Deg,
							 	 Range	VISINEDGE
								}
						},
		   	AirItem		
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_COMBAT,	
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1},
				Target		BFEV_FRIENDLYCHARGEUNDERATTACK_Item00
			}
		}
	};

//---------------------------------------------------------------------------
//DeadCode MS 03Oct96 //Large number of aircraft are about to land. They are low on fuel and ammo. 
//DeadCode MS 03Oct96 //A smaller number have just taken off.
//DeadCode MS 03Oct96 
//DeadCode MS 03Oct96 	BattleField
//DeadCode MS 03Oct96 	{
//DeadCode MS 03Oct96 		FileName	BFEV_ENEMYRETURNSTOAF=EVdfnd12.BF,	
//DeadCode MS 03Oct96 		Setval	{AngleStepSize,Int {Random 0,1,1}},	
//DeadCode MS 03Oct96 
//DeadCode MS 03Oct96 		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
//DeadCode MS 03Oct96 		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
//DeadCode MS 03Oct96 		AirGroup	
//DeadCode MS 03Oct96 		{
//DeadCode MS 03Oct96 			Route	
//DeadCode MS 03Oct96 			{
//DeadCode MS 03Oct96 				WayPoint	
//DeadCode MS 03Oct96 				{
//DeadCode MS 03Oct96 					Posn	{Abs 	{MainObjective},
//DeadCode MS 03Oct96 						 	 Abs	{Y FT_5000}	
//DeadCode MS 03Oct96 							},
//DeadCode MS 03Oct96 					Action	wpacircleno,
//DeadCode MS 03Oct96 					Range	MARGIN
//DeadCode MS 03Oct96 				},
//DeadCode MS 03Oct96 				WayPoint   	
//DeadCode MS 03Oct96 				{
//DeadCode MS 03Oct96 					Posn	{Abs	{MainObjective}, 
//DeadCode MS 03Oct96 						 	 Abs	{Y FT_EnterLandingPattern}
//DeadCode MS 03Oct96 							},
//DeadCode MS 03Oct96 					Action	wpalandingno,
//DeadCode MS 03Oct96 					Range	DistEnterLandingPattern
//DeadCode MS 03Oct96 				}
//DeadCode MS 03Oct96 			},
//DeadCode MS 03Oct96 			NumInWing	6,
//DeadCode MS 03Oct96 			NumInForm	EncounterList04,
//DeadCode MS 03Oct96 			Duty		DUTYCAP,
//DeadCode MS 03Oct96 
//DeadCode MS 03Oct96 			Posn	{Abs	{MainObjective}, 
//DeadCode MS 03Oct96 				 	 Abs	{Y	FT_GRND}
//DeadCode MS 03Oct96 				 	},
//DeadCode MS 03Oct96 
//DeadCode MS 03Oct96 		   	AirItem 
//DeadCode MS 03Oct96 			{
//DeadCode MS 03Oct96 				Side		NAT_ENEMY,
//DeadCode MS 03Oct96 				Type		EnemyScoutType00,
//DeadCode MS 03Oct96 				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
//DeadCode MS 03Oct96 				Home		EnemyScoutHomeBase,
//DeadCode MS 03Oct96 				MoveCode	AUTO_FOLLOWWP,
//DeadCode MS 03Oct96 //				movecode	Qtakeoff routine??					//MS 08Mar96
//DeadCode MS 03Oct96 				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
//DeadCode MS 03Oct96 				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
//DeadCode MS 03Oct96 				Morale		{Random	EnemyScoutMorale,40,1}
//DeadCode MS 03Oct96 			}
//DeadCode MS 03Oct96 		},
//DeadCode MS 03Oct96 		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
//DeadCode MS 03Oct96 		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
//DeadCode MS 03Oct96 		AirGroup
//DeadCode MS 03Oct96 		{
//DeadCode MS 03Oct96 			Route	
//DeadCode MS 03Oct96 			{
//DeadCode MS 03Oct96 				WayPoint	
//DeadCode MS 03Oct96 				{
//DeadCode MS 03Oct96 					Posn	{Abs	{MainObjective}, 
//DeadCode MS 03Oct96 						 	Abs	{Y FT_EnterLandingPattern}
//DeadCode MS 03Oct96 							},
//DeadCode MS 03Oct96 					Action	wpalandingno,
//DeadCode MS 03Oct96 					Range	DistEnterLandingPattern
//DeadCode MS 03Oct96 				}
//DeadCode MS 03Oct96 			},
//DeadCode MS 03Oct96 			NumInWing	6,
//DeadCode MS 03Oct96 			NumInForm	EncounterList08,
//DeadCode MS 03Oct96 			Duty		DUTYCAP,
//DeadCode MS 03Oct96 
//DeadCode MS 03Oct96 			Posn	{Abs	{CPP},
//DeadCode MS 03Oct96 					 Abs	{Y FT_EnterLandingPattern}, 
//DeadCode MS 03Oct96 					 Rel	{Intercept	{CPP,MainObjective},
//DeadCode MS 03Oct96 							 Bearing	{Select	ANGLES_315Deg,AngleStepSize,ANGLES_90Deg},
//DeadCode MS 03Oct96 							 Range		VISINEDGE
//DeadCode MS 03Oct96 							}
//DeadCode MS 03Oct96 					},
//DeadCode MS 03Oct96 
//DeadCode MS 03Oct96 		   	AirItem	
//DeadCode MS 03Oct96 			{
//DeadCode MS 03Oct96 				Side		NAT_ENEMY,
//DeadCode MS 03Oct96 				Type		EnemyScoutType00,
//DeadCode MS 03Oct96 				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
//DeadCode MS 03Oct96 				Home		EnemyScoutHomeBase,
//DeadCode MS 03Oct96 				MoveCode	AUTO_FOLLOWWP,
//DeadCode MS 03Oct96 				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
//DeadCode MS 03Oct96 				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
//DeadCode MS 03Oct96 				Morale		{Random	EnemyScoutMorale,40,1}
//DeadCode MS 03Oct96 //need to be low on fuel and ammo, possibly one or two are damaged
//DeadCode MS 03Oct96 			}
//DeadCode MS 03Oct96 		}
//DeadCode MS 03Oct96 	};

//---------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_ENEMYAFDEFENCETAKEOFF=EVdfnd09.BF,	

		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup	
		{
			Route	
			{
				WayPoint	
				{
					Posn	{Abs 	{MainObjective},
						 	 Abs	{Y FT_5000}	
							},
					Action	wpacircleno,
					Range	MARGIN
				},
				WayPoint   	
				{
					Posn	{Abs	{MainObjective}, 
						 	 Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	6,
			NumInForm	EncounterList08,
			Duty		DUTYCAP,

			Posn	{Abs	{MainObjective}, 
				 	 Abs	{Y	FT_GRND}
				 	},

		   	AirItem 
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
//				movecode	Qtakeoff routine??					//MS 08Mar96
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1}
			}
		}
	};
//DeadCode MS 01Oct96 //---------------------------------------------------------------------------
//DeadCode MS 01Oct96 //truck convoy travels from CWP to WP2
//DeadCode MS 01Oct96 
//DeadCode MS 01Oct96 	BattleField
//DeadCode MS 01Oct96 	{
//DeadCode MS 01Oct96 		FileName	BFEV_ENEMYROADCONVOY00=EVroad00.BF	
//DeadCode MS 01Oct96 	};
//DeadCode MS 01Oct96 
//DeadCode MS 01Oct96 //---------------------------------------------------------------------------
//DeadCode MS 01Oct96 //truck convoy travels from CWP to WP2
//DeadCode MS 01Oct96 
//DeadCode MS 01Oct96 	BattleField
//DeadCode MS 01Oct96 	{
//DeadCode MS 01Oct96 		FileName	BFEV_ENEMYROADCONVOY01=EVroad01.BF	
//DeadCode MS 01Oct96 	};
//DeadCode MS 01Oct96 
//---------------------------------------------------------------------------
//A friendly scout has been downed and the victor has landed beside it to strip
//it of something of worth (only use this in enemy territory). As the player
//approaches, the pilot rushes back to his crate to escape.

	BattleField
	{
		FileName	BFEV_ENEMYTROPHYHUNTER=EVmeat02.BF,


		SimpleItem	ENEMYTROPHYHUNTER_Victim00=	
		{
			Posn	{Abs {CPP},
					 Abs {Y FT_TakeOff},
					 Rel	{Intercept	{CPP,CWP},
							 Bearing	{Random	ANGLES_315Deg,90,ANGLES_1Deg},
							 Range	VISINEDGE
							}
					},
			Shape	WRECK
		},

		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup	
		{
			Route	
			{
				WayPoint	BFEV_ENEMYTROPHYHUNTER_WP00=	
				{
					Posn	{Abs	ENEMYTROPHYHUNTER_Victim00,
							 Rel	{Intercept	{CPP,CWP},	
									 Bearing	ANGLES_270Deg,
				 					 Range	METRES10
									}
							},
					Action	wpacnoactionno,
					Range	METRES01,
					Vel	2
				},
				WayPoint	
				{
					Posn	{Abs	BFEV_ENEMYTROPHYHUNTER_WP00,
							 Rel	{Intercept	{CPP,CWP},	
									 Bearing	ANGLES_180Deg,
				 					 Range	METRES1000
									}
							},
					Action	wpacnoactionno,
					Range	MARGIN,
					Vel	270
				},
				WayPoint
				{
					Posn	{Abs	{EnemyScoutHomeBase},	
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},

			NumInWing	1,
			NumInForm	1,
			Duty		DUTYCAP,

			Posn	{Abs	BFEV_ENEMYTROPHYHUNTER_WP00,
					 Rel	{Intercept	{CPP,CWP},
							 Bearing	ANGLES_0Deg,
						 	 Range		METRES10
							}
					},

		   	AirItem	
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,//DumbBastard??? FIXME!!!!
//fixme			Needs to be on standby, ready to take off
				Skill		{List {Random 3},SKILL_VETERAN,SKILL_REGULAR,SKILL_POOR},
				Character	EnemyScoutCavalier,
				Morale		MORALE_MEDIUM,
				Vel	2
			}
		}
	};

//---------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_ENEMYPURSUIT=EVagrs02.BF,	

		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup	
		{
			Route	
			{
				WayPoint	
				{
					Target	CPP,
					Range	HALFSTANDARDTRIGGER,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	{Abs	{CPP},
							 Rel	{Intercept	{CPP, EnemyScoutHomeBase},
								 	 Bearing	ANGLES_0Deg,
								 	 RangePercent	40
									 }
							},
					Range	MARGIN,
					Action	wpacnoactionno
				},
				WayPoint
				{
					Posn	{Abs	{EnemyScoutHomeBase},	
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	6,
			NumInForm	EncounterList04,
			Duty		DUTYCAP,

			Posn	{Abs	{CPP},
					 Rel	{Y	FT_2000,
							 Intercept	{CWP,CPP},	
						 	 Bearing	{Random	ANGLES_345Deg,30,ANGLES_1Deg},
						 	 Range		VISINEDGE
							}
					},

		   	AirItem	
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
//DeadCode MS 29Oct96  				MoveCode	AUTO_COMBAT,
//DeadCode MS 29Oct96  				Target		CPP,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1}
			}
		}
	};


//---------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_FRIENDLYCHARGERETURN00=EVfrnd00.BF,	
		Setval	{HeightStepSize,Int {Random 0,400,1}},

		Setval	{GlobalSkillMin, FriendlyChargeSkillMin},
		Setval	{GlobalSkillMax, FriendlyChargeSkillMax},
		AirGroup	
		{
			Route	
			{
				WayPoint	
				{
					Posn	{Abs	{CPP},
							 Rel	{Y	{Select	-FT_2000,HeightStepSize,FT_10},
									 Intercept	{CPP, FriendlyChargeHomeBase},
								 	 Bearing	ANGLES_0Deg,
								 	 RangePercent	90
									 }
							},
					Range	MARGIN,
					Action	wpacnoactionno
				},
				WayPoint
				{
					Posn	{Abs	{FriendlyChargeHomeBase},	
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	6,
			NumInForm	EncounterList02,
			Duty		DUTYCAP,

			Posn	{Abs	{CPP},
					 Rel	{Y	{Select	-FT_2000,HeightStepSize,FT_10},
							 Intercept	{FriendlyChargeHomeBase,CPP},
							 Bearing	{Random	ANGLES_270Deg,180,ANGLES_1Deg},
						 	 Range		{Random	VISINEDGE,VISBOUNDARYSIZE,METRES01}
							}
					},

		   	AirItem	
			{
				Side		NAT_FRIEND,
				Type		FriendlyChargeType00,
				Home		FriendlyChargeHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List {Random 6}, SKILL_VETERAN,SKILL_VETERAN,SKILL_REGULAR,SKILL_REGULAR,SKILL_REGULAR,SKILL_POOR},
				Character	FriendlyChargeCharacter,
				Morale		{Random	FriendlyChargeMorale,40,1}
			}
		}
	};

//---------------------------------------------------------------------------

	BattleField
	{
		FileName	BFEV_ENEMYINTERCEPT00=BFevnt01.BF,
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup	
		{
			Route	
			{
				WayPoint	
				{
					Posn	{Abs	{CWP}},
					Action	wpacircleno,
					Range	MARGIN
				},
				WayPoint
				{
					Posn	{Abs	{EnemyScoutHomeBase},	
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	6,
			NumInForm	EncounterList04,
			Duty		DUTYCAP,

			Posn		{Abs	{CWP},
						 Rel	{Intercept	{CWP, EnemyScoutHomeBase},
								 Bearing	ANGLES_0Deg,
							 	 Range	{Random	VISINEDGE,VISBOUNDARYSIZE,METRES01}
								}
						},

		   	AirItem
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1}
			}
		}
	};

//---------------------------------------------------------------------------

	BattleField
	{
		FileName	BFEV_ENEMYINTERCEPT01=BFevnt02.BF,
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup	
		{
			Route	
			{
				WayPoint	
				{
					Posn	{Abs	{CWP}},
					Action	wpacircleno,
					Range	MARGIN
				},
				WayPoint
				{
					Posn	{Abs	{EnemyScoutHomeBase},	
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	6,
			NumInForm	EncounterList04,
			Duty		DUTYCAP,

			Posn		{Abs	{CPP},
						 Rel	{Y	{Random	FT_1000,2000,FT_1},
								 Intercept	{CPP, EnemyScoutHomeBase},
								 Bearing	ANGLES_0Deg,
							 	 Range	{Random	VISINEDGE,VISBOUNDARYSIZE,METRES01}
								}
						},

		   	AirItem
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1}
			}
		}
	};

//---------------------------------------------------------------------------

	BattleField
	{
		FileName	BFEV_FRIENDLYCHARGESRETURN=BFPOOOa2.BF
	};

//---------------------------------------------------------------------------

	BattleField
	{
		FileName	BFEV_FRIENDLYBOMBERSTRAGGLER=BFPOOOa3.BF,
		Setval	{GlobalSkillMin, FriendlyChargeSkillMin},
		Setval	{GlobalSkillMax, FriendlyChargeSkillMax},
		AirGroup	
		{
			Route	FRIENDLYBOMBERSTRAGGLER_Route00 =	
			{
				WayPoint	
				{
					Target	FriendlyObjective,
					Posn	{Abs	{Y HeightSize}},
					Range	BEGINBOMBRANGE,
					Action	wpbombno
				},
				WayPoint
				{
					Posn	{Abs	{FriendlyChargeHomeBase},	
						 	Abs	{Y HeightSize}
							},
					Action	wpacnoactionno,
					Range	STANDARDTRIGGER
				},
				WayPoint
				{
					Posn	{Abs	{FriendlyChargeHomeBase},	
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	6,
			NumInForm	EncounterList04,
			Formation	FORM_FLATBOX,
			Duty		DUTYCAP,

			Posn	{Abs	{CPP},
					 Abs	{Y 	HeightSize},
					 Rel	{Intercept	{CPP,EnemyChargeHomeBase},
							 Bearing	{Random	ANGLES_90Deg,180,ANGLES_1Deg},
						 	 Range		{Random	VISINEDGE,VISBOUNDARYSIZE,METRES01}
							}
					},

		   	AirItem	FRIENDLYBOMBERSTRAGGLER_Item00=	
			{
				Side		NAT_FRIEND,
				Type		FriendlyChargeType00,
				Home		FriendlyChargeHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List {Random 6}, SKILL_VETERAN,SKILL_VETERAN,SKILL_REGULAR,SKILL_REGULAR,SKILL_REGULAR,SKILL_POOR},
				Character	FriendlyChargeCharacter,
				Morale		{Random	FriendlyChargeMorale,40,1},
				Bombs		8
			}									   
		},

//This is the straggler

		Setval	{GlobalSkillMin, FriendlyChargeSkillMin},
		Setval	{GlobalSkillMax, FriendlyChargeSkillMax},
		AirGroup	
		{
			Route
			{
				WayPoint
				{
					Posn	{Abs	FRIENDLYBOMBERSTRAGGLER_Item00,	
						 	Abs	{Y HeightSize},
							Rel	{Intercept	{FRIENDLYBOMBERSTRAGGLER_Item00,FriendlyObjective},
								 Bearing	ANGLES_0Deg,
								 Range	METRES500
								}
							},
					Action	wpacnoactionno,
					Range	MARGIN
				},
				WayPoint
				{
					Posn	{Abs	{FriendlyChargeHomeBase},	
						 	Abs	{Y HeightSize}
							},
					Action	wpacnoactionno,
					Range	STANDARDTRIGGER
				},
				WayPoint
				{
					Posn	{Abs	{FriendlyChargeHomeBase},	
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	1,
			NumInForm	1,
			Duty		DUTYBOMB,

			Posn	{Abs	FRIENDLYBOMBERSTRAGGLER_Item00,
					 Rel	{Intercept	{FRIENDLYBOMBERSTRAGGLER_Item00,FriendlyObjective},
						 	 Bearing	ANGLES_180Deg,
						 	 Range	METRES50
							}
					},

		   	AirItem	FRIENDLYBOMBERSTRAGGLER_Item01=	
			{
				Side		NAT_FRIEND,
				Type		FriendlyChargeType00,
				Home		FriendlyChargeHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List {Random 6}, SKILL_VETERAN,SKILL_VETERAN,SKILL_REGULAR,SKILL_REGULAR,SKILL_REGULAR,SKILL_POOR},
				Character	FriendlyChargeCharacter,
				Morale		{Random	FriendlyChargeMorale,40,1},
//DAMAGE IS IN H\3DINSTR.H
				Damage		0x12
			}
		},
//EnemyScouts are gonna kill the straggler
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup
		{
			Route
			{
				WayPoint	
				{
					Posn	{Abs	{EnemyScoutHomeBase}, 
						 	Abs	{Y HeightSize}
							},
					Action	wpacnoactionno,
					Range	STANDARDTRIGGER
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyScoutHomeBase}, 
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},

			NumInWing	6,
			NumInForm	EncounterList03,
			Duty		DUTYCAP,
			Formation	FORM_V,

			Posn		FRIENDLYBOMBERSTRAGGLER_Item02=
						{Abs	FRIENDLYBOMBERSTRAGGLER_Item01,
						 Rel	{Y {Random	FT_0,10,FT_100},
								 Intercept	{FRIENDLYBOMBERSTRAGGLER_Item01,CPP},
							     Bearing	{Random ANGLES_90Deg,180,ANGLES_1Deg},
						 		 RangePercent	75
								}
						},

		   	AirItem
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_COMBAT,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1},
				Target		FRIENDLYBOMBERSTRAGGLER_Item01,
 				Attitude	{
							 Intercept	{FRIENDLYBOMBERSTRAGGLER_Item02,FRIENDLYBOMBERSTRAGGLER_Item01},
							 Heading	ANGLES_0Deg,
							 Pitch	ANGLES_0Deg
							}
			}
		}
	};

//---------------------------------------------------------------------------
//DeadCode MS 01Oct96 
//DeadCode MS 01Oct96 	BattleField
//DeadCode MS 01Oct96 	{
//DeadCode MS 01Oct96 		FileName	BFEV_ENEMYSTACK00=BFPOOOa4.BF
//DeadCode MS 01Oct96 	};
//DeadCode MS 01Oct96 
//DeadCode MS 01Oct96 
//---------------------------------------------------------------------------

	BattleField
	{
		FileName	BFEV_FRIENDLYATTACKSBALLOON=BFPOOOa5.BF,
		Setval	{GlobalSkillMin, FriendlyScoutSkillMin},
		Setval	{GlobalSkillMax, FriendlyScoutSkillMax},
		AirGroup	
		{
			Route	
			{
				WayPoint		
				{
					Target	FriendlyObjective, 
					Posn	{Abs	{Y FT_BustAlt}
							},	
					Range	ATTACKBALLOONRANGE,
					Action	wpballoonbustno
				},
				WayPoint	
				{
					Posn	{Abs	{FriendlyObjective}, 
							 Abs	{Y FT_4000},
							 Rel	{Intercept	{FriendlyObjective,FriendlyScoutHomeBase},
									 Bearing	ANGLES_0Deg,
									 RangePercent	30
									}
							},
					Range	MARGIN,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	{Abs	{FriendlyScoutHomeBase}, 
						 	Abs	{Y FT_4000}
							},
					Action	wpacnoactionno,
					Range	STANDARDTRIGGER
				},
				WayPoint	
				{
					Target	FriendlyScoutHomeBase,
					Posn 	{Abs	{Y FT_EnterLandingPattern}},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	6,
			NumInForm	EncounterList03,
			Duty		DUTYCAP,
			Formation	FORM_V,	

			Posn		{Abs	{FriendlyObjective},
						 Abs	{Y FT_BustAlt},
						 Rel	{Bearing	{Random	ANGLES_0Deg,359,ANGLES_1Deg},
								 Range		ATTACKBALLOONRANGE
								}
						},

		   	AirItem
			{
				Side		NAT_FRIEND,
				Type		FriendlyScoutType00,
				Home		FriendlyScoutHomeBase,
				Squadron	{FriendlyScoutSquad,PS_5,PS_6,PS_7,PS_8},
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List {Random 3},SKILL_VETERAN,SKILL_REGULAR,SKILL_POOR},
				Character	FriendlyScoutCavalier,
				Morale		{Select FriendlyScoutMorale,1,40}
			}
		}
	};

//---------------------------------------------------------------------------

	BattleField
	{
		FileName	BFEV_CASCADE00=BFevnt03.BF,
		Setval	{GlobalSkillMin, FriendlyScoutSkillMin},
		Setval	{GlobalSkillMax, FriendlyScoutSkillMax},
		AirGroup	BFEV_CASCADE00_Group00 =	
		{
			Route	
			{
				WayPoint	
				{
					Posn	{Abs	{EnemyObjective},
							 Abs	{Y HeightSize}
							},
					Action	wpacnoactionno,
					Range	MARGIN
				},
				WayPoint
				{
					Posn	{Abs	{FriendlyScoutHomeBase},	
						 	Abs	{Y HeightSize}
							},
					Action	wpacnoactionno,
					Range	STANDARDTRIGGER
				},
				WayPoint
				{
					Posn	{Abs	{FriendlyScoutHomeBase},	
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	6,
			NumInForm	EncounterList03,
			Duty		DUTYCAP,
			Formation	FORM_V,

			Posn		{Abs	{CPP},
						 Abs	{Y	HeightSize},
						 Rel	{Intercept	{CPP, CWP},
								 Bearing	{Random	ANGLES_315Deg,90,ANGLES_1Deg},
							 	 Range	{Select	VISINEDGE,RangeStepSize,VISBOUNDARYSIZE}
								}
						},

		   	AirItem
			{
				Side		NAT_FRIEND,
				Type		FriendlyScoutType00,
				Home		FriendlyScoutHomeBase,
				Squadron	{FriendlyScoutSquad,PS_5,PS_6,PS_7,PS_8},
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, FriendlyScoutTactician,FriendlyScoutMrAverage,FriendlyScoutCavalier}},
				Morale		{Random	FriendlyScoutMorale,40,1}
			}
		}
	};
//---------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_CASCADE01=BFevnt04.BF,
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup	
		{
			Route	
			{
				WayPoint	
				{
					Posn	{Abs	{EnemyObjective},
							 Abs	{Y HeightSize}
							},
					Action	wpacnoactionno,
					Range	MARGIN
				},
				WayPoint
				{
					Posn	{Abs	{EnemyScoutHomeBase},	
						 	Abs	{Y HeightSize}
							},
					Action	wpacnoactionno,
					Range	STANDARDTRIGGER
				},
				WayPoint
				{
					Posn	{Abs	{EnemyScoutHomeBase},	
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	6,
			NumInForm	EncounterList03,
			Duty		DUTYCAP,
			Formation	FORM_V,

			Posn		{Abs	{CPP},
						 Abs	{Y	HeightSize},
						 Rel	{Intercept	{CPP,CWP},
								 Bearing	{Random	ANGLES_315Deg,90,ANGLES_1Deg},
							 	 Range	{Select	VISINEDGE,RangeStepSize,VISINEDGE}
								}
						},

		   	AirItem
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1}
			}
		}
	};

//---------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_CASCADE02=BFPOOOa8.BF,
		Setval	{GlobalSkillMin, EnemyChargeSkillMin},
		Setval	{GlobalSkillMax, EnemyChargeSkillMax},
		AirGroup	
		{
			Route	
			{
				WayPoint	
				{
					Posn	{Abs	{EnemyObjective},
							 Abs	{Y HeightSize}
							},
					Action	wpacnoactionno,
					Range	MARGIN
				},
				WayPoint
				{
					Posn	{Abs	{EnemyChargeHomeBase},	
						 	Abs	{Y HeightSize}
							},
					Action	wpacnoactionno,
					Range	STANDARDTRIGGER
				},
				WayPoint
				{
					Posn	{Abs	{EnemyChargeHomeBase},	
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	6,
			NumInForm	EncounterList03,
			Duty		DUTYCAP,
			Formation	FORM_V,

			Posn		{Abs	{CPP},
						 Abs	{Y	HeightSize},
						 Rel	{Intercept	{CPP, CWP},
								 Bearing	{Random	ANGLES_315Deg,90,ANGLES_1Deg},
							 	 Range	{Select	VISINEDGE,RangeStepSize,VISBOUNDARYSIZE}
								}
						},

		   	AirItem
			{
				Side		NAT_ENEMY,
				Type		EnemyChargeType00,
				Squadron	{EnemyChargeSquad},
				Home		EnemyChargeHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List {Random 6}, SKILL_VETERAN,SKILL_VETERAN,SKILL_REGULAR,SKILL_REGULAR,SKILL_REGULAR,SKILL_POOR},
				Character	EnemyChargeCharacter,
				Morale		{Random	EnemyChargeMorale,40,1}
			}
		}
	};

//---------------------------------------------------------------------------

//DeadCode MS 03Oct96 	BattleField
//DeadCode MS 03Oct96 	{
//DeadCode MS 03Oct96 		FileName	BFEV_ENEMYWARNSAFBUDDIESSTALL=BFPOOOa9.BF
//DeadCode MS 03Oct96 	};

	BattleField
	{
		FileName	BFEV_FLAKTRAP=BFPOOOb1.BF,
		Setval	{GlobalSkillMin, EnemyChargeSkillMin},
		Setval	{GlobalSkillMax, EnemyChargeSkillMax},


		AirGroup	
		{
			Route	
			{
				WayPoint
				{
					Posn	{Abs	{EnemyChargeHomeBase},
						 	 Abs	{Y HeightSize}
							},
					Range	STANDARDTRIGGER,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyChargeHomeBase},
						 	 Abs	{Y FT_EnterLandingPattern}
							},
					Range	DistEnterLandingPattern,
					Action	wpalandingno
				}
			},
			NumInWing	6,
			NumInForm	EncounterList01,
			Formation	FORM_FLATBOX,
			Duty		DUTYBOMB,

			Posn		{Abs	{CWP},
						 Abs	{Y	HeightSize}
						}, 

		   	AirItem
			{
				Side		NAT_ENEMY,
				Type		EnemyChargeType00,
				Home		EnemyChargeHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List {Random 3}, SKILL_VETERAN,SKILL_REGULAR,SKILL_POOR},
				Character	EnemyChargeCharacter,
				Morale		{Random	EnemyChargeMorale,40,1},
				Squadron	{EnemyChargeSquad}
			}
		}
	};

//---------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_ENEMYPATROLTAKEOFF=BFPOOOb3.BF,
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup	
		{
			Route	
			{
//TempCode MS 12Nov96 				WayPoint
//TempCode MS 12Nov96 				{
//TempCode MS 12Nov96 					Posn	{Abs	{EnemyScoutHomeBase},
//TempCode MS 12Nov96 							 Abs	{Y HeightSize},
//TempCode MS 12Nov96 							 Rel	{Intercept	{EnemyScoutHomeBase, EnemyObjective},
//TempCode MS 12Nov96 									 Bearing	ANGLES_0Deg,
//TempCode MS 12Nov96 								 	 RangePercent	50
//TempCode MS 12Nov96 									}
//TempCode MS 12Nov96 							},
//TempCode MS 12Nov96 					Action	wpacnoactionno,
//TempCode MS 12Nov96 					Range	MARGIN
//TempCode MS 12Nov96 				},
				WayPoint
				{
					Posn	{Abs	{EnemyObjective},
						 	 Abs	{Y	HeightSize},
							 Rel	{Intercept	{EnemyScoutHomeBase, EnemyObjective},
									 Bearing	ANGLES_90Deg,
								 	 Range	QTRSTANDARDTRIGGER
									}
							},
 					Action	wpstartloopno,
					Range	MARGIN
				},
				WayPoint
				{
					Posn	{Abs	{EnemyObjective},
						 	 Abs	{Y	HeightSize},
							 Rel	{Intercept	{EnemyScoutHomeBase, EnemyObjective},
									 Bearing	ANGLES_270Deg,
								 	 Range	QTRSTANDARDTRIGGER
									}
							},
					Action	wpstoploopchkno,
					Range	MARGIN
				},
				WayPoint
				{
					Posn	{Abs	{EnemyScoutHomeBase},	
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	6,
			NumInForm	EncounterList04,
			Duty		DUTYCAP,

			Posn	{Abs	{EnemyScoutHomeBase},
					 Abs	{Y FT_TakeOff}
					},

		   	AirItem	
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Home		EnemyScoutHomeBase,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				MoveCode	AUTO_TAKEOFF,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1}
			}
		}
	};

//---------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_FRIENDLYCRAPLANDING=BFPOOOb4.BF,
		Setval	{GlobalSkillMin, FriendlyScoutSkillMin},
		Setval	{GlobalSkillMax, FriendlyScoutSkillMax},
		AirGroup	
		{
			Route	
			{
				WayPoint	FRIENDLYCRAPLANDING_WP00=	
				{
					Posn	{Abs	{FriendlyScoutHomeBase}, 
						 	 Abs	{Y FT_TakeOff},
							 Rel	{Intercept	{CPP,FriendlyScoutHomeBase},
									 Bearing	ANGLES_0Deg,
									 Range	METRES02
									}
							},
					Action	wpacnoactionno,
					Vel		100
				},
				WayPoint	
				{
					Posn	{Abs	{FriendlyScoutHomeBase}, 
						 	 Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},

			NumInWing	1,
			NumInForm	1,
			Duty		DUTYCAP,

			Posn	{Abs	FRIENDLYCRAPLANDING_WP00,
					 Abs	{Y FT_500},
					 Rel	{Intercept	{CPP,FriendlyScoutHomeBase},
							 Bearing	ANGLES_270Deg,
							 Range	HALFVISINEDGE
							}
					},
		   	AirItem	
			{
				Side		NAT_FRIEND,
				Type		FriendlyScoutType00,
				Home		FriendlyScoutHomeBase,
				Squadron	{FriendlyScoutSquad,PS_5,PS_6,PS_7,PS_8},
				MoveCode	AUTO_FOLLOWWP,
				Skill		SKILL_NOVICE,
				Character	FriendlyScoutCavalier,
				Morale		{Random	FriendlyScoutMorale,40,1},
				Vel		100
			}
		},
		AirGroup	
		{
			Route	
			{
				WayPoint	FRIENDLYCRAPLANDING_WP01=	
				{
					Posn	{Abs	{FriendlyScoutHomeBase}, 
						 	 Abs	{Y FT_TakeOff},
							 Rel	{Intercept	{CPP,FriendlyScoutHomeBase},
									 Bearing	ANGLES_180Deg,
									 Range	METRES02
									}
							},
					Action	wpacnoactionno,
					Vel		100
				},
				WayPoint	
				{
					Posn	{Abs	{FriendlyScoutHomeBase}, 
						 	 Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},

			NumInWing	1,
			NumInForm	1,
			Duty		DUTYCAP,

			Posn	{Abs	FRIENDLYCRAPLANDING_WP01,
					 Abs	{Y FT_500},
					 Rel	{Intercept	{CPP,FriendlyScoutHomeBase},
							 Bearing	ANGLES_90Deg,
							 Range	HALFVISINEDGE
							 }
					},
		   	AirItem	
			{
				Side		NAT_FRIEND,
				Type		FriendlyScoutType00,
				Home		FriendlyScoutHomeBase,
				Squadron	{FriendlyScoutSquad,PS_5,PS_6,PS_7,PS_8},
				MoveCode	AUTO_FOLLOWWP,
				Skill		SKILL_NOVICE,
				Character	FriendlyScoutCavalier,
				Morale		{Random	FriendlyScoutMorale,40,1},
				Vel		100
			}
		}
	};

//DeadCode MS 01Oct96 	BattleField
//DeadCode MS 01Oct96 	{
//DeadCode MS 01Oct96 		FileName	BFEV_ENEMYMISSIONRETURNSTOAF=BFPOOOb5.BF
//DeadCode MS 01Oct96 	};

//DeadCode MS 03Oct96 	BattleField
//DeadCode MS 03Oct96 	{
//DeadCode MS 03Oct96 		FileName	BFEV_ENEMYSCOUTDESTINATION=BFPOOOb6.BF
//DeadCode MS 03Oct96 	};

	BattleField
	{
		FileName	BFEV_ENEMYCLOUDTRAP=BFPOOOb7.BF,
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup	
		{
			Route	
			{
				WayPoint	ENEMYCLOUDTRAP_WP00=	
				{
					Posn	{Abs	{CPP},
							 Abs	{Y CloudBase},
							 Rel	{Intercept	{CPP,CWP},
									 Bearing	{Random	ANGLES_270Deg,180,ANGLES_1Deg},
									 Range	HALFVISINEDGE
									}
							},
					Action	wpacnoactionno,
					Range	MARGIN
				},
				WayPoint
				{
					Posn	{Abs	{CPP}},
					Action	wpacnoactionno,
					Range	MARGIN
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyScoutHomeBase}, 
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},

			NumInWing	3,
			NumInForm	EncounterList03,
			Duty		DUTYCAP,
			Formation	FORM_V,

			Posn	{Abs	ENEMYCLOUDTRAP_WP00, 
					 Rel	{Intercept	{CPP,ENEMYCLOUDTRAP_WP00},
					   		 Bearing	ANGLES_0Deg,
							 Pitch	ANGLES_0Deg,
					   		 Range	METRES01
						 	}
					},

		   	AirItem		     	
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron {PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	ACM_STRAIGHTDIVE,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutTactician,EnemyScoutMrAverage}},
				Morale		{Random	EnemyScoutMorale,40,1},
				Target		CPP
			}
		}
	};

//---------------------------------------------------------------------------

	BattleField
	{
		FileName	BFEV_ENEMYFLAKTAUNT=EvTrap00.BF,
		Setval	{HeightSize, Y {Select CloudBase,-FT_3000,FT_1}},
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup	
		{
			Route	EnemyFlakTaunt_Route00 =
			{
 				WayPoint	
 				{
 					Posn	{Abs	{EnemyObjective},
 							 Abs	{Y HeightSize}
 							},
 					Action	wpacnoactionno
 				},
 				WayPoint	
 				{
 					Posn	{Abs	{EnemyObjective},
 							 Abs	{Y HeightSize}
 							},
 					Action	wpacnoactionno
 				},
 				WayPoint	
 				{
 					Posn	{Abs	{EnemyObjective},
 							 Abs	{Y HeightSize}
 							},
 					Action	wpacnoactionno
 				},
 				WayPoint	
 				{
 					Posn	{Abs	{EnemyObjective},
 							 Abs	{Y HeightSize}
 							},
 					Action	wpacnoactionno
 				},
 				WayPoint	
 				{
 					Posn	{Abs	{EnemyObjective},
 							 Abs	{Y HeightSize}
 							},
 					Action	wpacnoactionno
 				},
				WayPoint
				{
					Posn	{Abs	{EnemyScoutHomeBase},
						 	 Abs	{Y FT_5000}
							},
					Action	wpacnoactionno,
					Range	STANDARDTRIGGER
				},
				WayPoint
				{
					Posn	{Abs	{EnemyScoutHomeBase},	
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	1,
			NumInForm	1,
			Duty		DUTYCAP,

			Posn	{Abs	{EnemyObjective},
					 Abs	{Y HeightSize}
					},

		   	AirItem	EvTrap00_Item00 =	
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron {PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List {Random 3},SKILL_VETERAN,SKILL_REGULAR,SKILL_POOR},
				Character	EnemyScoutCavalier,
				Morale		{Select EnemyScoutMorale,1,40},
				Event		{Event	BFCH_LOSTSCOUTAMBUSH,
							 Setval	{EnemyScoutType00, EnemyScoutType00},
							 Setval	{EnemyScoutHomeBase, EnemyScoutHomeBase},
							 Setval	{EnemyScoutMorale, EnemyScoutMorale},
							 Setval	{EnemyScoutTactician, EnemyScoutTactician},
							 Setval	{EnemyScoutMrAverage, EnemyScoutMrAverage},
							 Setval	{EnemyScoutCavalier, EnemyScoutCavalier},
							 Setval	{EnemyScoutSquad, EnemyScoutSquad},
							 Setval	{PS_1, PS_1},
							 Setval	{PS_1, PS_2},
							 Setval	{PS_1, PS_3},
							 Setval	{PS_1, PS_4}
							}
			}
		}


	};

//--------------------------------------------------------------------------------

//This is redundant now probably!!								//MS 21Aug96//
//Reused by flak taunt
//DeadCode MS 07Oct96 	BattleField
//DeadCode MS 07Oct96 	{
//DeadCode MS 07Oct96 		FileName	BFCH_LOSTSCOUTAMBUSH=CHtrap00.BF,
//DeadCode MS 07Oct96 		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
//DeadCode MS 07Oct96 		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
//DeadCode MS 07Oct96 		AirGroup		
//DeadCode MS 07Oct96 		{
//DeadCode MS 07Oct96 			Route		
//DeadCode MS 07Oct96 			{
//DeadCode MS 07Oct96 				WayPoint	
//DeadCode MS 07Oct96 				{
//DeadCode MS 07Oct96 					Posn	{Abs	{CPP}}, 
//DeadCode MS 07Oct96 					Action	wpacnoactionno,
//DeadCode MS 07Oct96 					Range	MARGIN
//DeadCode MS 07Oct96 				},
//DeadCode MS 07Oct96 				WayPoint	
//DeadCode MS 07Oct96 				{
//DeadCode MS 07Oct96 					Posn	{Abs	{EnemyScoutHomeBase}, 
//DeadCode MS 07Oct96 						 	Abs	{Y FT_5000}
//DeadCode MS 07Oct96 							},
//DeadCode MS 07Oct96 					Action	wpalandingno,
//DeadCode MS 07Oct96 					Range	DistEnterLandingPattern
//DeadCode MS 07Oct96 				}
//DeadCode MS 07Oct96 			},
//DeadCode MS 07Oct96 			NumInWing	6,
//DeadCode MS 07Oct96 			NumInForm	EncounterList03,
//DeadCode MS 07Oct96 			Duty		DUTYCAP,
//DeadCode MS 07Oct96 //fixme			Duty		DUTYHIGHESCORT,
//DeadCode MS 07Oct96 
//DeadCode MS 07Oct96 			Posn		{Abs	EvTrap00_Item00,
//DeadCode MS 07Oct96 						 Abs	{Y	CloudBase},
//DeadCode MS 07Oct96 						 Rel	{Bearing	{Random	ANGLES_135Deg,90,ANGLES_1Deg},
//DeadCode MS 07Oct96 								 Range	{Random	METRES200,200,METRES01}
//DeadCode MS 07Oct96 								}
//DeadCode MS 07Oct96 						},

	BattleField
	{
		FileName	BFCH_LOSTSCOUTAMBUSH=CHtrap00.BF,
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup	
		{
			Route	
			{
				WayPoint	
				{
					Posn	{Abs	{CPP}},
					Action	wpacnoactionno,
					Range	MARGIN
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyScoutHomeBase}, 
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},

			NumInWing	3,
			NumInForm	3,
			Duty		DUTYCAP,
			Formation	FORM_V,

			Posn	{Abs	{CPP}, 
					 Abs	{Y CloudBase},
					 Rel	{Intercept	{CPP,EnemyScoutLost_Item01},
					   		 Bearing	{Random ANGLES_150Deg,60,ANGLES_1Deg},
					   		 Range	METRES300
						 	}
					},

		   	AirItem		     	
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron {PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	ACM_STRAIGHTDIVE,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutTactician,EnemyScoutMrAverage}},
				Morale		{Random	EnemyScoutMorale,40,1},
				Target		CPP
			}
		}
	};



//---------------------------------------------------------------------------

	BattleField
	{
		FileName	BFEV_FRIENDCHARGENOMANSLAND=BFevnt00.BF,
		Setval	{GlobalSkillMin, FriendlyChargeSkillMin},
		Setval	{GlobalSkillMax, FriendlyChargeSkillMax},
		AirGroup	
		{
			Route	
			{
				WayPoint	BFEV_FRIENDCHARGENOMANSLAND_WP00 =	
				{
					Posn	{Abs	{FriendlyObjective},
							 Abs	{Y -FT_5},
							 Rel	{Intercept	{FriendHomeBase,FriendlyObjective},
								 	 Bearing	ANGLES_0Deg,
								 	 Range	METRES300
									}
							},
					Vel	0,
					Action	wpstopno,
					Event	{Event	BFCH_FRIENDCHARGENOMANSLAND,
							 Setval	{FriendlyObjective, FriendlyObjective}
							}
				}
//DeadCode RDH 04Oct96 				WayPoint			
//DeadCode RDH 04Oct96 				{
//DeadCode RDH 04Oct96 					Posn	{Abs	BFEV_FRIENDCHARGENOMANSLAND_WP00},
//DeadCode RDH 04Oct96 					Range	MARGIN,
//DeadCode RDH 04Oct96 					Vel	0,
//DeadCode RDH 04Oct96 					Action	wpacnoactionno,
//DeadCode RDH 04Oct96 					Event	{Event	BFCH_FRIENDCHARGENOMANSLAND}
//DeadCode RDH 04Oct96 				}
			},
			NumInWing	1,
			NumInForm	1,
			Duty		DUTYCAP,

			Posn	{Abs	BFEV_FRIENDCHARGENOMANSLAND_WP00,
					 Abs	{Y -FT_50},
					 Rel	{Intercept	{FriendHomeBase,BFEV_FRIENDCHARGENOMANSLAND_WP00},
							 Bearing	ANGLES_0Deg,
						 	 Range		METRES2000
							}
					},

		   	AirItem	
			{
				Side		NAT_FRIEND,
				Type		FriendlyChargeType00,
				Home		FriendlyChargeHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Vel			100,
//DAMAGE IS IN H\3DINSTR.H
				Damage		0x12,
				Skill		{List {Random 6}, SKILL_VETERAN,SKILL_VETERAN,SKILL_REGULAR,SKILL_REGULAR,SKILL_REGULAR,SKILL_POOR},
				Character	FriendlyChargeCharacter,
				Morale		{Random	FriendlyChargeMorale,40,1}
			}
		},
		SimpleItem
		{
			Posn	{Abs BFEV_FRIENDCHARGENOMANSLAND_WP00,
					 Abs	{Y -FT_1},
					 Rel	{Intercept	{FriendlyObjective,BFEV_FRIENDCHARGENOMANSLAND_WP00},
							 Bearing	ANGLES_0Deg,
				 			 Range	METRES50
							}
					},
			Shape	EMPTY,
//FixMe			Shape	Gunners????
			UIDBand	RedMilitaryBAND
		}
	};

//---------------------------------------------------------------------------
	BattleField
	{
		FileName	BFCH_FRIENDCHARGENOMANSLAND=BFCHAN00.BF,
		GroundGroup	
		{
			Route		
			{
//TempCode RDH 04Oct96 				WayPoint	BFCH_FRIENDCHARGENOMANSLAND_WP00=	
//TempCode RDH 04Oct96 				{
//TempCode RDH 04Oct96 					Posn	{Abs	BFEV_FRIENDCHARGENOMANSLAND_WP00,
//TempCode RDH 04Oct96 							 Abs	{Y -FT_1},
//TempCode RDH 04Oct96 							 Rel	{Intercept	{BFEV_FRIENDCHARGENOMANSLAND_WP00,FriendlyObjective},
//TempCode RDH 04Oct96 								 	 Bearing	ANGLES_0Deg,
//TempCode RDH 04Oct96 								 	 RangePercent	30
//TempCode RDH 04Oct96 									}
//TempCode RDH 04Oct96 							},
//TempCode RDH 04Oct96 					Range	MARGIN,
//TempCode RDH 04Oct96 					Vel	50,
//TempCode RDH 04Oct96 					Action	wpacnoactionno
//TempCode RDH 04Oct96 				},
//TempCode RDH 04Oct96 				WayPoint	
//TempCode RDH 04Oct96 				{
//TempCode RDH 04Oct96 					Posn	{Abs	BFevnt00_Gunners00,
//TempCode RDH 04Oct96 							 Abs	{Y -FT_1}
//TempCode RDH 04Oct96 							},
//TempCode RDH 04Oct96 					Vel	0,
//TempCode RDH 04Oct96 					Range	STANDARDTRIGGER,
//TempCode RDH 04Oct96 					Action	wpacnoactionno
//TempCode RDH 04Oct96 //fixme					Action	WAITUNTILDEAD
//TempCode RDH 04Oct96 				},
				WayPoint	
				{
					Posn	{Abs	{FriendlyObjective},
							 Abs	{Y -FT_1}
							},
					Vel	50,
					Action	wpdmbtrkstopno
//FIXME				signal that they are safe now
				}
			},
			
			NumInForm	2,
			Formation	FORM_SINGLEFILE,

			Posn	{Abs	BFEV_FRIENDCHARGENOMANSLAND_WP00,
					 Abs	{Y -FT_1}
					},

		   	GroundItem	
			{
				Type		SQ_ATruck,
				Side		NAT_FRIEND,
				Shape		EMPTY,
				Vel			50,
				MoveCode	GROUND_TAXI
			}
		}
//FIXME		I also need an invisible spotter that is going to get closer and closer to
//			BFCH_FRIENDCHARGENOMANSLAND_WP00
	};
//---------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_FRIENDLYSCOUTSAREAPATROL=BFPOOOc0.BF,
		Setval	{GlobalSkillMin, FriendlyScoutSkillMin},
		Setval	{GlobalSkillMax, FriendlyScoutSkillMax},
		AirGroup	
		{
			Route	
			{
				WayPoint	
				{
					Posn	{Abs	{FriendlyObjective},
							 Abs	{Y HeightSize},
							 Rel	{Bearing	ANGLES_270Deg,
									 Range	METRES500
									}
							},
 					Action	wpstartloopno,
					Range	MARGIN
				},
				WayPoint	
				{
					Posn	{Abs	{FriendlyObjective},
							 Abs	{Y HeightSize},
							 Rel	{Bearing	ANGLES_90Deg,
									 Range	METRES500
									}
							},
					Action	wpstoploopchkno,
					Range	MARGIN
				},
				WayPoint
				{
					Posn	{Abs	{FriendlyScoutHomeBase},	
						 	Abs	{Y HeightSize}
							},
					Action	wpacnoactionno,
					Range	STANDARDTRIGGER
				},
				WayPoint
				{
					Posn	{Abs	{FriendlyScoutHomeBase},	
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	4,
			NumInForm	EncounterList04,
			Duty		DUTYCAP,

					Posn	{Abs	{FriendlyObjective},
							 Abs	{Y	HeightSize}
							},


		   	AirItem	
			{
				Side		NAT_FRIEND,
				Type		FriendlyScoutType00,
				Home		FriendlyScoutHomeBase,
				Squadron	{FriendlyScoutSquad,PS_5,PS_6,PS_7,PS_8},
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, FriendlyScoutTactician,FriendlyScoutMrAverage,FriendlyScoutCavalier}},
				Morale		{Random	FriendlyScoutMorale,40,1}
			}
		}
	};

//---------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_FRIENDLYSCOUTSAGGRESSPATROL=BFfrnd10.BF,
		Setval	{GlobalSkillMin, FriendlyScoutSkillMin},
		Setval	{GlobalSkillMax, FriendlyScoutSkillMax},
		AirGroup	
		{
			Route	
			{
				WayPoint	
				{
					Posn	{Abs	{FriendlyObjective},
							 Abs	{Y HeightSize},
							 Rel	{Bearing	ANGLES_270Deg,
									 Range	METRES500
									}
							},
 					Action	wpstartloopno,
					Range	MARGIN
				},
				WayPoint	
				{
					Posn	{Abs	{FriendlyObjective},
							 Abs	{Y HeightSize},
							 Rel	{Bearing	ANGLES_90Deg,
									 Range	METRES500
									}
							},
					Action	wpstoploopchkno,
					Range	MARGIN
				},
				WayPoint
				{
					Posn	{Abs	{FriendlyScoutHomeBase},	
						 	Abs	{Y HeightSize}
							},
					Action	wpacnoactionno,
					Range	STANDARDTRIGGER
				},
				WayPoint
				{
					Posn	{Abs	{FriendlyScoutHomeBase},	
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	6,
			NumInForm	EncounterList04,
			Duty		DUTYCAP,

					Posn	{Abs	{CPP},
							 Abs	{Y	HeightSize},
							 Rel	{Bearing	{Random	ANGLES_0Deg,359,ANGLES_1Deg},
							 		 Range	{Random	VISINEDGE,VISBOUNDARYSIZE,METRES01}
									}
							},
		   	AirItem	
			{
				Side		NAT_FRIEND,
				Type		FriendlyScoutType00,
				Home		FriendlyScoutHomeBase,
				Squadron	{FriendlyScoutSquad,PS_5,PS_6,PS_7,PS_8},
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, FriendlyScoutTactician,FriendlyScoutMrAverage,FriendlyScoutCavalier}},
				Morale		{Random	FriendlyScoutMorale,40,1}
			}
		}
	};

//---------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_ENEMYSCOUTSAREAPATROL=BFPOOOc1.BF,
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup	
		{
			Route	
			{
				WayPoint	
				{
					Posn	{Abs	{EnemyObjective},
							 Abs	{Y HeightSize},
							 Rel	{Intercept {CPP,EnemyObjective},
									 Bearing	ANGLES_270Deg,
									 Range	METRES500
									}
							},
 					Action	wpstartloopno,
					Range	MARGIN
				},
				WayPoint	
				{
					Posn	{Abs	{EnemyObjective},
							 Abs	{Y HeightSize},
							 Rel	{Intercept {CPP,EnemyObjective},
									 Bearing	ANGLES_90Deg,
									 Range	METRES500
									}
							},
					Action	wpstoploopchkno,
					Range	MARGIN
				},
				WayPoint
				{
					Posn	{Abs	{EnemyScoutHomeBase},	
						 	Abs	{Y HeightSize}
							},
					Action	wpacnoactionno,
					Range	STANDARDTRIGGER
				},
				WayPoint
				{
					Posn	{Abs	{EnemyScoutHomeBase},	
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	4,
			NumInForm	EncounterList04,
			Duty		DUTYCAP,

					Posn	{Abs	{EnemyObjective},
							 Abs	{Y	HeightSize}
							},
		   	AirItem	
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron {PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1}
			}
		}
	};
//---------------------------------------------------------------------------

	BattleField
	{
		FileName	BFEV_FRIENDLYCHARGEDAMAGEDRETURN=BFPOOOc2.BF,
		Setval	{HeightStepSize,Int {Random 0,4000,1}},

		Setval	{GlobalSkillMin, FriendlyChargeSkillMin},
		Setval	{GlobalSkillMax, FriendlyChargeSkillMax},
		AirGroup	
		{
			Route	
			{
				WayPoint	
				{
					Posn	{Abs	{CPP},
							 Rel	{Y	{Select	-FT_2000,HeightStepSize,FT_1},
									 Intercept	{CPP, FriendlyChargeHomeBase},
								 	 Bearing	ANGLES_0Deg,
								 	 RangePercent	90
									 }
							},
					Range	MARGIN,
					Action	wpacnoactionno
				},
				WayPoint
				{
					Posn	{Abs	{FriendlyChargeHomeBase},	
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	2,
			NumInForm	EncounterList01,
			Duty		DUTYCAP,
//fixme			Duty		DUTYCHARGE????

			Posn	{Abs	{CPP},
					 Rel	{Y	{Select	-FT_2000,HeightStepSize,FT_1},
							 Bearing	{Random	ANGLES_0Deg,359,ANGLES_1Deg},
						 	 Range		{Random	VISINEDGE,VISBOUNDARYSIZE,METRES01}
							}
					},

		   	AirItem	
			{
				Side		NAT_FRIEND,
				Type		FriendlyChargeType00,
				Home		FriendlyChargeHomeBase,
				Squadron 	{FriendlyChargeSquad},
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List {Random 6}, SKILL_VETERAN,SKILL_VETERAN,SKILL_REGULAR,SKILL_REGULAR,SKILL_REGULAR,SKILL_POOR},
				Character	FriendlyChargeCharacter,
				Morale		{Random	FriendlyChargeMorale,40,1},
//DAMAGE IS IN H\3DINSTR.H
				Damage		0x12
			}
		}
	};

//---------------------------------------------------------------------------

	BattleField
	{
		FileName	BFEV_FRIENDRDVZ00=BFPOOOc3.BF,
		Setval	{GlobalSkillMin, FriendlyChargeSkillMin},
		Setval	{GlobalSkillMax, FriendlyChargeSkillMax},
		AirGroup	
		{
			Route	CWP,

			NumInWing	6,
			NumInForm	EncounterList08,
			Formation	FORM_STACKEDBOX,

 			Posn		{Abs	{CWP},
 						 Rel	{Y {Select -FT_2000,20,FT_100},
 								 Intercept	{CWP,FriendlyObjective},
 								 Bearing	ANGLES_0Deg,
 				 				 Range	{Select VISINEDGE,1,HALFVISINEDGE}
 								}
 						},

		   	AirItem	FRIENDRDVZ00_Item00=
			{
				Side		NAT_FRIEND,
				Type		FriendlyChargeType00,
				Home		FriendlyChargeHomeBase,
				Squadron 	{FriendlyChargeSquad},
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List {Random 6}, SKILL_VETERAN,SKILL_VETERAN,SKILL_REGULAR,SKILL_REGULAR,SKILL_REGULAR,SKILL_POOR},
				Character	FriendlyChargeCharacter,
				Morale		{Random	FriendlyChargeMorale,40,1},
 				Follower	CPP
			}
		}
	};

//---------------------------------------------------------------------------

	BattleField
	{
		FileName	BFEV_FRIENDRDVZ01=BFPOOOc4.BF,
		Setval	{GlobalSkillMin, FriendlyChargeSkillMin},
		Setval	{GlobalSkillMax, FriendlyChargeSkillMax},
		AirGroup	
		{
			Route	CWP,

			NumInWing	6,
			NumInForm	EncounterList08,
			Formation	FORM_STACKEDBOX,

 			Posn		{Abs	{CWP},
 						 Rel	{Y {Select -FT_2000,20,FT_100},
 								 Intercept	{CWP,FriendlyObjective},
 								 Bearing	ANGLES_0Deg,
 				 				 Range	{Select VISINEDGE,1,HALFVISINEDGE}
 								}
 						},

		   	AirItem	FRIENDRDVZ01_Item00=
			{
				Side		NAT_FRIEND,
				Type		FriendlyChargeType00,
				Home		FriendlyChargeHomeBase,
				Squadron 	{FriendlyChargeSquad},
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List {Random 6}, SKILL_VETERAN,SKILL_VETERAN,SKILL_REGULAR,SKILL_REGULAR,SKILL_REGULAR,SKILL_POOR},
				Character	FriendlyChargeCharacter,
				Morale		{Random	FriendlyChargeMorale,40,1},
 				Follower	CPP
			}
		},
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup
		{
			Route
			{
				WayPoint	
				{
					Posn	{Abs	{CWP}},
					Action	wpacnoactionno,
					Range	MARGIN
				},
				WayPoint		
				{
					Posn	{Abs	{EnemyScoutHomeBase}, 
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	6,
			NumInForm	EncounterList08,
			Formation	FORM_LOOSE,

			Posn		{Abs	FRIENDRDVZ01_Item00,
						 Rel	{Y	{Random	-FT_500,5,FT_100},
								 Intercept	{FRIENDRDVZ01_Item00,FriendlyObjective},
							 	 Bearing	{Random	ANGLES_355Deg,10,ANGLES_1Deg},
							 	 Range	HALFVISINEDGE
							}
						},

		   	AirItem		
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_COMBAT,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1},
				Target		FRIENDRDVZ01_Item00			
			}
		}
	};

//---------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_FRIENDRDVZ02=BFPOOOc5.BF,
		Setval	{GlobalSkillMin, FriendlyChargeSkillMin},
		Setval	{GlobalSkillMax, FriendlyChargeSkillMax},
		AirGroup	
		{
			Route	CWP,

			NumInWing	6,
			NumInForm	EncounterList08,
			Formation	FORM_STACKEDBOX,

 			Posn		{Abs	{CWP},
 						 Rel	{Y {Select -FT_2000,20,FT_100},
 								 Intercept	{CWP,FriendlyObjective},
 								 Bearing	ANGLES_0Deg,
 				 				 Range	{Select VISINEDGE,1,HALFVISINEDGE}
 								}
 						},

		   	AirItem	FRIENDRDVZ02_Item00=
			{
				Side		NAT_FRIEND,
				Type		FriendlyChargeType00,
				Home		FriendlyChargeHomeBase,
				Squadron 	{FriendlyChargeSquad},
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List {Random 6}, SKILL_VETERAN,SKILL_VETERAN,SKILL_REGULAR,SKILL_REGULAR,SKILL_REGULAR,SKILL_POOR},
				Character	FriendlyChargeCharacter,
				Morale		{Random	FriendlyChargeMorale,40,1},
 				Follower	CPP
			}
		},
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup
		{
			Route
			{
				WayPoint	
				{
					Posn	{Abs	{CWP}},
					Action	wpacnoactionno,
					Range	MARGIN
				},
				WayPoint		
				{
					Posn	{Abs	{EnemyScoutHomeBase}, 
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	6,
			NumInForm	EncounterList08,
			Formation	FORM_LOOSE,

			Posn		{Abs	FRIENDRDVZ02_Item00,
						 Rel	{Y	{Random	-FT_500,5,FT_100},
								 Intercept	{FRIENDRDVZ02_Item00,FriendlyObjective},
							 	 Bearing	{Random	ANGLES_355Deg,10,ANGLES_1Deg},
							 	 Range	HALFVISINEDGE
							}
						},

		   	AirItem		
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_COMBAT,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1},
				Target		FRIENDRDVZ02_Item00			
			}
		}
	};
//---------------------------------------------------------------------------

	BattleField
	{
		FileName	BFEV_FRIENDRDVZ03=BFPOOOc6.BF,
		Setval	{GlobalSkillMin, FriendlyChargeSkillMin},
		Setval	{GlobalSkillMax, FriendlyChargeSkillMax},
		AirGroup	
		{
			Route	CWP,

			NumInWing	6,
			NumInForm	EncounterList08,
			Formation	FORM_STACKEDBOX,

 			Posn		{Abs	{CWP},
 						 Rel	{Y {Select -FT_2000,20,FT_100},
 								 Intercept	{CWP,FriendlyObjective},
 								 Bearing	ANGLES_0Deg,
 				 				 Range	{Select VISINEDGE,1,HALFVISINEDGE}
 								}
 						},

		   	AirItem	FRIENDRDVZ03_Item00=
			{
				Side		NAT_FRIEND,
				Type		FriendlyChargeType00,
				Home		FriendlyChargeHomeBase,
				Squadron 	{FriendlyChargeSquad},
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List {Random 6}, SKILL_VETERAN,SKILL_VETERAN,SKILL_REGULAR,SKILL_REGULAR,SKILL_REGULAR,SKILL_POOR},
				Character	FriendlyChargeCharacter,
				Morale		{Random	FriendlyChargeMorale,40,1},
 				Follower	CPP
			}
		},
		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
		AirGroup
		{
			Route
			{
				WayPoint	
				{
					Posn	{Abs	{CWP}},
					Action	wpacnoactionno,
					Range	MARGIN
				},
				WayPoint		
				{
					Posn	{Abs	{EnemyScoutHomeBase}, 
						 	Abs	{Y FT_EnterLandingPattern}
							},
					Action	wpalandingno,
					Range	DistEnterLandingPattern
				}
			},
			NumInWing	6,
			NumInForm	EncounterList08,
			Formation	FORM_LOOSE,

			Posn		{Abs	FRIENDRDVZ03_Item00,
						 Rel	{Y	{Random	-FT_500,5,FT_100},
								 Intercept	{FRIENDRDVZ03_Item00,FriendlyObjective},
							 	 Bearing	{Random	ANGLES_355Deg,10,ANGLES_1Deg},
							 	 Range	HALFVISINEDGE
							}
						},

		   	AirItem		
			{
				Side		NAT_ENEMY,
				Type		EnemyScoutType00,
				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
				Home		EnemyScoutHomeBase,
				MoveCode	AUTO_COMBAT,
				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
				Morale		{Random	EnemyScoutMorale,40,1},
				Target		FRIENDRDVZ03_Item00			
			}
		}
	};

//DeadCode MS 03Dec96 	BattleField
//DeadCode MS 03Dec96 	{
//DeadCode MS 03Dec96 		FileName	BFEV_BLOCKADE=BFPOOOc7.BF
//DeadCode MS 03Dec96 	};

//---------------------------------------------------------------------------
	BattleField
	{
		FileName	BFEV_FRIENDRDVZSTRAFFERS=BFPOOOc8.BF,
		Setval	{GlobalSkillMin, FriendlyChargeSkillMin},
		Setval	{GlobalSkillMax, FriendlyChargeSkillMax},
		AirGroup	
		{
			Route	CWP,
			NumInWing	6,
			NumInForm	EncounterList02,
			Duty		DUTYCAP,

 			Posn		{Abs	{CPP},
 						 Rel	{Intercept	{CPP,CWP},
 								 Bearing	{Random	ANGLES_300Deg,2,ANGLES_120Deg},
 				 				 RangePercent	100
 							}
 						},

		   	AirItem
			{
				Side		NAT_FRIEND,
				Type		FriendlyChargeType00,
				Home		FriendlyChargeHomeBase,
				Squadron	{FriendlyChargeSquad},
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List {Random 6}, SKILL_VETERAN,SKILL_VETERAN,SKILL_REGULAR,SKILL_REGULAR,SKILL_REGULAR,SKILL_POOR},
				Character	FriendlyChargeCharacter,
				Morale		{Random	FriendlyChargeMorale,40,1},
				Follower	CPP
			}
		}
	};

//---------------------------------------------------------------------------

	BattleField
	{
		FileName	BFEV_FRIENDRDVZRECONN=BFPOOOc9.BF,
		Setval	{GlobalSkillMin, FriendlyChargeSkillMin},
		Setval	{GlobalSkillMax, FriendlyChargeSkillMax},
		AirGroup	
		{
			Route	CWP,
			NumInWing	1,
			NumInForm	EncounterList02,
			Duty		DUTYCAP,

 			Posn		{Abs	{CPP},
 						 Rel	{Intercept	{CPP,CWP},
 								 Bearing	{Random	ANGLES_300Deg,2,ANGLES_120Deg},
 				 				 RangePercent	100
 							}
 						},

		   	AirItem
			{
				Side		NAT_FRIEND,
				Type		FriendlyChargeType00,
				Home		FriendlyChargeHomeBase,
				Squadron	{FriendlyChargeSquad},
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List {Random 6}, SKILL_VETERAN,SKILL_VETERAN,SKILL_REGULAR,SKILL_REGULAR,SKILL_REGULAR,SKILL_POOR},
				Character	FriendlyChargeCharacter,
				Morale		{Random	FriendlyChargeMorale,40,1},
				Follower	CPP
			}
		}
	};

//---------------------------------------------------------------------------

	BattleField
	{
		FileName	BFEV_FRIENDRDVZSPOT=BFPOOOd1.BF,
		Setval	{GlobalSkillMin, FriendlyChargeSkillMin},
		Setval	{GlobalSkillMax, FriendlyChargeSkillMax},
		AirGroup	
		{
			Route	CWP,
			NumInWing	1,
			NumInForm	EncounterList01,
			Duty		DUTYCAP,

 			Posn		{Abs	{CPP},
 						 Rel	{Intercept	{CPP,CWP},
 								 Bearing	{Random	ANGLES_300Deg,2,ANGLES_120Deg},
 				 				 RangePercent	100
 							}
 						},

		   	AirItem
			{
				Side		NAT_FRIEND,
				Type		FriendlyChargeType00,
				Home		FriendlyChargeHomeBase,
				Squadron	{FriendlyChargeSquad},
				MoveCode	AUTO_FOLLOWWP,
				Skill		{List {Random 6}, SKILL_VETERAN,SKILL_VETERAN,SKILL_REGULAR,SKILL_REGULAR,SKILL_REGULAR,SKILL_POOR},
				Character	FriendlyChargeCharacter,
				Morale		{Random	FriendlyChargeMorale,40,1},
				Follower	CPP
			}
		}
	};

//---------------------------------------------------------------------------

//DeadCode MS 03Dec96 	BattleField
//DeadCode MS 03Dec96 	{
//DeadCode MS 03Dec96 		FileName	BFEV_ENEMYWARY=BFPOOOd2.BF
//DeadCode MS 03Dec96 	};
//MS 05Jul96
//DeadCode MS 03Dec96 	BattleField
//DeadCode MS 03Dec96 	{
//DeadCode MS 03Dec96 		FileName	BFEV_ENEMYBOMBANDSTRAFFE00=BFevnt05.BF
//DeadCode MS 03Dec96 	};
//DeadCode MS 03Dec96 
//DeadCode MS 03Dec96 	BattleField
//DeadCode MS 03Dec96 	{
//DeadCode MS 03Dec96 		FileName	BFEV_ENEMYBOMBANDSTRAFFE01=BFevnt06.BF
//DeadCode MS 03Dec96 	};
//DeadCode MS 03Dec96 
//DeadCode MS 03Dec96 	BattleField
//DeadCode MS 03Dec96 	{
//DeadCode MS 03Dec96 		FileName	BFEV_ENEMYBOMBANDSTRAFFE02=BFevnt07.BF
//DeadCode MS 03Dec96  	};

//---------------------------------------------------------------------------
// SPECIAL CAMPAIGN MISSION SPECIFIC EVENTS
//---------------------------------------------------------------------------
//DeadCode JIM 26Jun98 	BattleField
//DeadCode JIM 26Jun98 	{
//DeadCode JIM 26Jun98 		FileName	BFSP_HatPatrolHotSeptember00=BFSPHR00.BF,
//DeadCode JIM 26Jun98 		GroundGroup	
//DeadCode JIM 26Jun98 		{
//DeadCode JIM 26Jun98 			Route		
//DeadCode JIM 26Jun98 			{
//DeadCode JIM 26Jun98 				WayPoint
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Posn	{Abs	{ROUTE_HRVerdunManheulles_B},
//DeadCode JIM 26Jun98 					 		Abs	{Y -FT_1}
//DeadCode JIM 26Jun98 							},
//DeadCode JIM 26Jun98 					Action	wpdmbtrknoactno
//DeadCode JIM 26Jun98 				}, 
//DeadCode JIM 26Jun98 				WayPoint
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Posn	{Abs	{ROUTE_HRVerdunManheulles_C},
//DeadCode JIM 26Jun98 					 		Abs	{Y -FT_1}
//DeadCode JIM 26Jun98 							},
//DeadCode JIM 26Jun98 					Action	wpdmbtrknoactno
//DeadCode JIM 26Jun98 				}, 
//DeadCode JIM 26Jun98 				WayPoint
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Posn	{Abs	{ROUTE_HRVerdunManheulles_D},
//DeadCode JIM 26Jun98 					 		Abs	{Y -FT_1}
//DeadCode JIM 26Jun98 							},
//DeadCode JIM 26Jun98 					Action	wpdmbtrknoactno
//DeadCode JIM 26Jun98 				}, 
//DeadCode JIM 26Jun98 				WayPoint
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Posn	{Abs	{ROUTE_HRVerdunManheulles_E},
//DeadCode JIM 26Jun98 					 		Abs	{Y -FT_1}
//DeadCode JIM 26Jun98 							},
//DeadCode JIM 26Jun98 					Action	wpdmbtrknoactno
//DeadCode JIM 26Jun98 				}, 
//DeadCode JIM 26Jun98 				WayPoint
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Posn	{Abs	{ROUTE_HRVerdunManheulles_F},
//DeadCode JIM 26Jun98 					 		Abs	{Y -FT_1}
//DeadCode JIM 26Jun98 							},
//DeadCode JIM 26Jun98 					Action	wpdmbtrknoactno
//DeadCode JIM 26Jun98 				}, 
//DeadCode JIM 26Jun98 				WayPoint
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Posn	{Abs	{ROUTE_HRVerdunManheulles_G},
//DeadCode JIM 26Jun98 					 		Abs	{Y -FT_1}
//DeadCode JIM 26Jun98 							},
//DeadCode JIM 26Jun98 					Action	wpdmbtrknoactno
//DeadCode JIM 26Jun98 				}, 
//DeadCode JIM 26Jun98 				WayPoint
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Posn	{Abs	{ROUTE_HRVerdunManheulles_H},
//DeadCode JIM 26Jun98 					 		Abs	{Y -FT_1}
//DeadCode JIM 26Jun98 							},
//DeadCode JIM 26Jun98 					Action	wpdmbtrknoactno
//DeadCode JIM 26Jun98 				}, 
//DeadCode JIM 26Jun98 				WayPoint
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Posn	{Abs	{ROUTE_HRVerdunManheulles_I},
//DeadCode JIM 26Jun98 					 		Abs	{Y -FT_1}
//DeadCode JIM 26Jun98 							},
//DeadCode JIM 26Jun98 					Action	wpdmbtrknoactno
//DeadCode JIM 26Jun98 				}, 
//DeadCode JIM 26Jun98 				WayPoint
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Posn	{Abs	{ROUTE_HRVerdunManheulles_J},
//DeadCode JIM 26Jun98 					 		Abs	{Y -FT_1}
//DeadCode JIM 26Jun98 							},
//DeadCode JIM 26Jun98 					Action	wpdmbtrknoactno
//DeadCode JIM 26Jun98 				}, 
//DeadCode JIM 26Jun98 				WayPoint
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Posn	{Abs	{ROUTE_HRVerdunManheulles_K},
//DeadCode JIM 26Jun98 					 		Abs	{Y -FT_1}
//DeadCode JIM 26Jun98 							},
//DeadCode JIM 26Jun98 					Action	wpdmbtrknoactno
//DeadCode JIM 26Jun98 				}, 
//DeadCode JIM 26Jun98 				WayPoint
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Posn	{Abs	{ROUTE_HRVerdunManheulles_L},
//DeadCode JIM 26Jun98 					 		Abs	{Y -FT_1}
//DeadCode JIM 26Jun98 							},
//DeadCode JIM 26Jun98 					Action	wpdmbtrknoactno
//DeadCode JIM 26Jun98 				}, 
//DeadCode JIM 26Jun98 				WayPoint
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Posn	{Abs	{ROUTE_HRVerdunManheulles_M},
//DeadCode JIM 26Jun98 					 		Abs	{Y -FT_1}
//DeadCode JIM 26Jun98 							},
//DeadCode JIM 26Jun98 					Action	wpdmbtrknoactno
//DeadCode JIM 26Jun98 				}, 
//DeadCode JIM 26Jun98 				WayPoint
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Posn	{Abs	{ROUTE_HRVerdunManheulles_N},
//DeadCode JIM 26Jun98 					 		Abs	{Y -FT_1}
//DeadCode JIM 26Jun98 							},
//DeadCode JIM 26Jun98 					Action	wpdmbtrknoactno
//DeadCode JIM 26Jun98 				}, 
//DeadCode JIM 26Jun98 				WayPoint
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Posn	{Abs	{ROUTE_HRVerdunManheulles_O},
//DeadCode JIM 26Jun98 					 		Abs	{Y -FT_1}
//DeadCode JIM 26Jun98 							},
//DeadCode JIM 26Jun98 					Action	wpdmbtrknoactno
//DeadCode JIM 26Jun98 				}, 
//DeadCode JIM 26Jun98 				WayPoint
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Posn	{Abs	{ROUTE_HRVerdunManheulles_P},
//DeadCode JIM 26Jun98 					 		Abs	{Y -FT_1}
//DeadCode JIM 26Jun98 							},
//DeadCode JIM 26Jun98 					Action	wpdmbtrknoactno
//DeadCode JIM 26Jun98 				}, 
//DeadCode JIM 26Jun98 				WayPoint
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Posn	{Abs	{ROUTE_HRVerdunManheulles_Q},
//DeadCode JIM 26Jun98 					 		Abs	{Y -FT_1}
//DeadCode JIM 26Jun98 							},
//DeadCode JIM 26Jun98 					Action	wpdmbtrknoactno
//DeadCode JIM 26Jun98 				}, 
//DeadCode JIM 26Jun98 				WayPoint
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Posn	{Abs	{ROUTE_HRVerdunManheulles_R},
//DeadCode JIM 26Jun98 					 		Abs	{Y -FT_1}
//DeadCode JIM 26Jun98 							},
//DeadCode JIM 26Jun98 					Action	wpdmbtrknoactno
//DeadCode JIM 26Jun98 				}, 
//DeadCode JIM 26Jun98 				WayPoint
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Posn	{Abs	{ROUTE_HRVerdunManheulles_S},
//DeadCode JIM 26Jun98 					 		Abs	{Y -FT_1}
//DeadCode JIM 26Jun98 							},
//DeadCode JIM 26Jun98 					Action	wpdmbtrknoactno
//DeadCode JIM 26Jun98 				}, 
//DeadCode JIM 26Jun98 				WayPoint
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Posn	{Abs	{ROUTE_HRVerdunManheulles_T},
//DeadCode JIM 26Jun98 					 		Abs	{Y -FT_1}
//DeadCode JIM 26Jun98 							},
//DeadCode JIM 26Jun98 					Action	wpstopno
//DeadCode JIM 26Jun98 				}
//DeadCode JIM 26Jun98 			},
//DeadCode JIM 26Jun98 		
//DeadCode JIM 26Jun98 			NumInForm	8,
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 			Posn	{Abs	{ROUTE_HRVerdunManheulles_A},
//DeadCode JIM 26Jun98 					 Abs	{Y -FT_1}
//DeadCode JIM 26Jun98 					},
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 		   	GroundItem	HatPatrolHotSeptember_Item00 =
//DeadCode JIM 26Jun98 			{
//DeadCode JIM 26Jun98 				Type		SQ_ATruck,
//DeadCode JIM 26Jun98 				Side		NAT_FRIEND,
//DeadCode JIM 26Jun98 				Shape		EMPTY,
//DeadCode JIM 26Jun98 				MoveCode	GROUND_TAXI
//DeadCode JIM 26Jun98 			}
//DeadCode JIM 26Jun98 		},
//DeadCode JIM 26Jun98 		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
//DeadCode JIM 26Jun98 		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
//DeadCode JIM 26Jun98 		AirGroup	
//DeadCode JIM 26Jun98 		{
//DeadCode JIM 26Jun98 			Route	
//DeadCode JIM 26Jun98 			{
//DeadCode JIM 26Jun98 				WayPoint	
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Target	HatPatrolHotSeptember_Item00,
//DeadCode JIM 26Jun98 					Posn	{
//DeadCode JIM 26Jun98 							 Abs	{Y FT_Straffe}
//DeadCode JIM 26Jun98 							},
//DeadCode JIM 26Jun98 					Action	wpstraffeno,
//DeadCode JIM 26Jun98 					Range	BEGINSTRAFFERANGE
//DeadCode JIM 26Jun98 				},
//DeadCode JIM 26Jun98 				WayPoint
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Posn	{Abs	{EnemyScoutHomeBase},
//DeadCode JIM 26Jun98 						 	Abs	{Y FT_EnterLandingPattern}
//DeadCode JIM 26Jun98 							},
//DeadCode JIM 26Jun98 					Action	wpalandingno,
//DeadCode JIM 26Jun98 					Range	DistEnterLandingPattern
//DeadCode JIM 26Jun98 				}
//DeadCode JIM 26Jun98 			},
//DeadCode JIM 26Jun98 			NumInWing	1,
//DeadCode JIM 26Jun98 			NumInForm	1,
//DeadCode JIM 26Jun98 			Duty		DUTYCAP,
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 			Posn	{Abs	{CPP},
//DeadCode JIM 26Jun98 					 Abs	{Y FT_Straffe},		 
//DeadCode JIM 26Jun98 					 Rel	{Intercept	{CPP,HatPatrolHotSeptember_Item00},
//DeadCode JIM 26Jun98 						 	 Bearing	{Random	ANGLES_330Deg,2,ANGLES_60Deg},
//DeadCode JIM 26Jun98 						 	 Range		VISINEDGE
//DeadCode JIM 26Jun98 							}
//DeadCode JIM 26Jun98 					},
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 		   	AirItem	
//DeadCode JIM 26Jun98 			{
//DeadCode JIM 26Jun98 				Side		NAT_ENEMY,
//DeadCode JIM 26Jun98 				Type		SQ_MIG15,
//DeadCode JIM 26Jun98 				Squadron {EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
//DeadCode JIM 26Jun98 				Home		EnemyScoutHomeBase,
//DeadCode JIM 26Jun98 				MoveCode	AUTO_FOLLOWWP,
//DeadCode JIM 26Jun98 				Skill		SKILL_ACE,
//DeadCode JIM 26Jun98 				Character	EnemyScoutCavalier,
//DeadCode JIM 26Jun98 				Morale		MORALE_TOPMORALE
//DeadCode JIM 26Jun98 			}
//DeadCode JIM 26Jun98 		}
//DeadCode JIM 26Jun98 	};
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 //---------------------------------------------------------------------------
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 	BattleField
//DeadCode JIM 26Jun98 	{
//DeadCode JIM 26Jun98 		FileName	BFSP_HatPatrolHotSeptember01=BFSPHR01.BF,
//DeadCode JIM 26Jun98 		GroundGroup	
//DeadCode JIM 26Jun98 		{
//DeadCode JIM 26Jun98 			Route		
//DeadCode JIM 26Jun98 			{
//DeadCode JIM 26Jun98 				WayPoint
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Posn	{Abs	{UID_NODE_AnTung},
//DeadCode JIM 26Jun98 					 		Abs	{Y -FT_1}
//DeadCode JIM 26Jun98 							},
//DeadCode JIM 26Jun98 					Action	wpdmbtrkstopno,
//DeadCode JIM 26Jun98 					Range	MARGIN
//DeadCode JIM 26Jun98 				}
//DeadCode JIM 26Jun98 			},
//DeadCode JIM 26Jun98 		
//DeadCode JIM 26Jun98 			NumInForm	8,
//DeadCode JIM 26Jun98 			Formation	FORM_SINGLEFILE,
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 			Posn	{Abs	{UID_NODE_sinuiju},
//DeadCode JIM 26Jun98 					 Abs	{Y -FT_1}
//DeadCode JIM 26Jun98 					},
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 		   	GroundItem	
//DeadCode JIM 26Jun98 			{
//DeadCode JIM 26Jun98 				Type		SQ_ATruck,
//DeadCode JIM 26Jun98 				Side		NAT_ENEMY,
//DeadCode JIM 26Jun98 				Shape		EMPTY,
//DeadCode JIM 26Jun98 				MoveCode	GROUND_TAXI
//DeadCode JIM 26Jun98 			}
//DeadCode JIM 26Jun98 		}
//DeadCode JIM 26Jun98 	};
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 //---------------------------------------------------------------------------
//DeadCode JIM 26Jun98 	BattleField
//DeadCode JIM 26Jun98 	{
//DeadCode JIM 26Jun98 		FileName	BFSP_HatPatrolHotSeptember02=BFSPHR02.BF,
//DeadCode JIM 26Jun98 		GroundGroup	
//DeadCode JIM 26Jun98 		{
//DeadCode JIM 26Jun98 			Route		
//DeadCode JIM 26Jun98 			{
//DeadCode JIM 26Jun98 				WayPoint
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Posn	{Abs	{UID_NODE_sinuiju},
//DeadCode JIM 26Jun98 					 		Abs	{Y -FT_1}
//DeadCode JIM 26Jun98 							},
//DeadCode JIM 26Jun98 					Action	wpdmbtrkstopno
//DeadCode JIM 26Jun98 				}
//DeadCode JIM 26Jun98 			},
//DeadCode JIM 26Jun98 		
//DeadCode JIM 26Jun98 			NumInForm	8,
//DeadCode JIM 26Jun98 			Formation	FORM_SINGLEFILE,
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 			Posn	{Abs	{UID_NODE_sinuiju},
//DeadCode JIM 26Jun98 					 Abs	{Y -FT_1}
//DeadCode JIM 26Jun98 					},
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 		   	GroundItem	
//DeadCode JIM 26Jun98 			{
//DeadCode JIM 26Jun98 				Type		SQ_ATruck,
//DeadCode JIM 26Jun98 				Side		NAT_ENEMY,
//DeadCode JIM 26Jun98 				Shape		EMPTY,
//DeadCode JIM 26Jun98 				MoveCode	GROUND_TAXI
//DeadCode JIM 26Jun98 			}
//DeadCode JIM 26Jun98 		}
//DeadCode JIM 26Jun98 	};
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 //---------------------------------------------------------------------------
//DeadCode JIM 26Jun98 	BattleField
//DeadCode JIM 26Jun98 	{
//DeadCode JIM 26Jun98 		FileName	BFSP_HatReconnTrains_P2_A=BFSPHR03.BF
//DeadCode JIM 26Jun98 //DeadCode MS 01Dec96 		GroundGroup	
//DeadCode JIM 26Jun98 //DeadCode MS 01Dec96 		{
//DeadCode JIM 26Jun98 //DeadCode MS 01Dec96 			Route		
//DeadCode JIM 26Jun98 //DeadCode MS 01Dec96 			{
//DeadCode JIM 26Jun98 //DeadCode MS 01Dec96 				WayPoint	
//DeadCode JIM 26Jun98 //DeadCode MS 01Dec96 				{
//DeadCode JIM 26Jun98 //DeadCode MS 01Dec96 					Posn	{Abs	{UID_CvNtStenay},
//DeadCode JIM 26Jun98 //DeadCode MS 01Dec96 							 Abs	{Y -FT_1}
//DeadCode JIM 26Jun98 //DeadCode MS 01Dec96 							},
//DeadCode JIM 26Jun98 //DeadCode MS 01Dec96 					Vel	100,
//DeadCode JIM 26Jun98 //DeadCode MS 01Dec96 					Action	wpdmbtrkstopno
//DeadCode JIM 26Jun98 //DeadCode MS 01Dec96 				}
//DeadCode JIM 26Jun98 //DeadCode MS 01Dec96 			},
//DeadCode JIM 26Jun98 //DeadCode MS 01Dec96 			
//DeadCode JIM 26Jun98 //DeadCode MS 01Dec96 			NumInForm	12,
//DeadCode JIM 26Jun98 //DeadCode MS 01Dec96 			Formation	FORM_SINGLEFILE,
//DeadCode JIM 26Jun98 //DeadCode MS 01Dec96 
//DeadCode JIM 26Jun98 //DeadCode MS 01Dec96 			Posn	{Abs	{UID_CvNtMouzay},
//DeadCode JIM 26Jun98 //DeadCode MS 01Dec96 					 Abs	{Y -FT_1}
//DeadCode JIM 26Jun98 //DeadCode MS 01Dec96 					},
//DeadCode JIM 26Jun98 //DeadCode MS 01Dec96 
//DeadCode JIM 26Jun98 //DeadCode MS 01Dec96 		   	GroundItem	
//DeadCode JIM 26Jun98 //DeadCode MS 01Dec96 			{
//DeadCode JIM 26Jun98 //DeadCode MS 01Dec96 				Type		SQ_ATruck,
//DeadCode JIM 26Jun98 //DeadCode MS 01Dec96 				Side		NAT_FRIEND,
//DeadCode JIM 26Jun98 //DeadCode MS 01Dec96 				Shape		{List	TRAIN1,TRAIN3,TRAIN3,TRAIN3,TRAIN2,TRAIN2,
//DeadCode JIM 26Jun98 //DeadCode MS 01Dec96 									TRAIN2,TRAIN3,TRAIN2,TRAIN2,TRAIN3,TRAIN2},
//DeadCode JIM 26Jun98 //DeadCode MS 01Dec96 				Vel			100,
//DeadCode JIM 26Jun98 //DeadCode MS 01Dec96 				MoveCode	GROUND_TAXI
//DeadCode JIM 26Jun98 //DeadCode MS 01Dec96 			}
//DeadCode JIM 26Jun98 //DeadCode MS 01Dec96 		}
//DeadCode JIM 26Jun98 	};
//DeadCode JIM 26Jun98 //---------------------------------------------------------------------------
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 	BattleField
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 	{
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 		FileName	BFSP_HatReconnTrains_P2_B=BFSPHR04.BF
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 	};		  
//DeadCode JIM 26Jun98 //---------------------------------------------------------------------------
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 	BattleField
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 	{
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 		FileName	BFSP_HatReconnTrains_P2_C=BFSPHR05.BF
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 	};
//DeadCode JIM 26Jun98 //---------------------------------------------------------------------------
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 	BattleField
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 	{
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 		FileName	BFSP_HatReconnTrains_P2_D=BFSPHR06.BF,
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 		GroundGroup	
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 		{
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 			Route		
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 			{
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				WayPoint	
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				{
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 					Posn	{Abs	{UID_CvNtMontmedy},
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 							 Abs	{Y -FT_1}
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 							},
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 					Vel	100,
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 					Action	wpdmbtrkstopno
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				}
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 			},
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 			
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 			NumInForm	12,
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 			Formation	FORM_SINGLEFILE,
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 			Posn	{Abs	{UID_CvNtMetz},
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 					 Abs	{Y -FT_1}
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 					},
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 		   	GroundItem	
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 			{
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				Type		SQ_ATruck,
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				Side		NAT_FRIEND,
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				Shape		{List	TRAIN1,TRAIN3,TRAIN3,TRAIN4,TRAIN4,TRAIN4,
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 									TRAIN4,TRAIN4,TRAIN4,TRAIN4,TRAIN4,TRAIN4},
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				Vel			100,
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				MoveCode	GROUND_TAXI
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 			}
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 		}
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 	};
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 	BattleField
//DeadCode JIM 26Jun98 	{
//DeadCode JIM 26Jun98 		FileName	BFSP_BFHatBlCpDun00=BFSPHR07.BF,
//DeadCode JIM 26Jun98 		Setval	{GlobalSkillMin, FriendlyScoutSkillMin},
//DeadCode JIM 26Jun98 		Setval	{GlobalSkillMax, FriendlyScoutSkillMax},
//DeadCode JIM 26Jun98 		AirGroup	
//DeadCode JIM 26Jun98 		{
//DeadCode JIM 26Jun98 			Route	
//DeadCode JIM 26Jun98 			{
//DeadCode JIM 26Jun98 				WayPoint	
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Posn	{Abs	{WP3},
//DeadCode JIM 26Jun98 							 Abs	{Y HeightSize},
//DeadCode JIM 26Jun98 							 Rel	{Intercept {WP3,WP1},
//DeadCode JIM 26Jun98 									 Bearing	ANGLES_270Deg,
//DeadCode JIM 26Jun98 									 Range	METRES500
//DeadCode JIM 26Jun98 									}
//DeadCode JIM 26Jun98 							},
//DeadCode JIM 26Jun98 					Action	wpacnoactionno,
//DeadCode JIM 26Jun98 					Range	MARGIN
//DeadCode JIM 26Jun98 				},
//DeadCode JIM 26Jun98 				WayPoint	
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Posn	{Abs	{WP1},
//DeadCode JIM 26Jun98 							 Abs	{Y HeightSize},
//DeadCode JIM 26Jun98 							 Rel	{Intercept {WP1,WP2},
//DeadCode JIM 26Jun98 									 Bearing	ANGLES_270Deg,
//DeadCode JIM 26Jun98 									 Range	METRES500
//DeadCode JIM 26Jun98 									}
//DeadCode JIM 26Jun98 							},
//DeadCode JIM 26Jun98 					Action	wpacnoactionno,
//DeadCode JIM 26Jun98 					Range	MARGIN
//DeadCode JIM 26Jun98 				},
//DeadCode JIM 26Jun98 				WayPoint	
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Posn	{Abs	{WP1},
//DeadCode JIM 26Jun98 							 Abs	{Y HeightSize},
//DeadCode JIM 26Jun98 							 Rel	{Intercept {WP2,WP1},
//DeadCode JIM 26Jun98 									 Bearing	ANGLES_0Deg,
//DeadCode JIM 26Jun98 									 Range	METRES2000
//DeadCode JIM 26Jun98 									}
//DeadCode JIM 26Jun98 							},
//DeadCode JIM 26Jun98 					Action	wpacnoactionno,
//DeadCode JIM 26Jun98 					Range	MARGIN
//DeadCode JIM 26Jun98 				},
//DeadCode JIM 26Jun98 				WayPoint	
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Posn	{Abs	{WP2},
//DeadCode JIM 26Jun98 							 Abs	{Y HeightSize},
//DeadCode JIM 26Jun98 							 Rel	{Intercept {WP1,WP2},
//DeadCode JIM 26Jun98 									 Bearing	ANGLES_270Deg,
//DeadCode JIM 26Jun98 									 Range	METRES500
//DeadCode JIM 26Jun98 									}
//DeadCode JIM 26Jun98 							},
//DeadCode JIM 26Jun98 					Action	wpacnoactionno,
//DeadCode JIM 26Jun98 					Range	MARGIN
//DeadCode JIM 26Jun98 				},
//DeadCode JIM 26Jun98 				WayPoint	
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Posn	{Abs	{WP2},
//DeadCode JIM 26Jun98 							 Abs	{Y HeightSize},
//DeadCode JIM 26Jun98 							 Rel	{Intercept {WP2,WP1},
//DeadCode JIM 26Jun98 									 Bearing	ANGLES_0Deg,
//DeadCode JIM 26Jun98 									 Range	METRES2000
//DeadCode JIM 26Jun98 									}
//DeadCode JIM 26Jun98 							},
//DeadCode JIM 26Jun98 					Action	wpacnoactionno,
//DeadCode JIM 26Jun98 					Range	MARGIN
//DeadCode JIM 26Jun98 				},
//DeadCode JIM 26Jun98 				WayPoint	
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Posn	{Abs	{WP2},
//DeadCode JIM 26Jun98 							 Abs	{Y HeightSize},
//DeadCode JIM 26Jun98 							 Rel	{Intercept {WP1,WP2},
//DeadCode JIM 26Jun98 									 Bearing	ANGLES_270Deg,
//DeadCode JIM 26Jun98 									 Range	METRES500
//DeadCode JIM 26Jun98 									}
//DeadCode JIM 26Jun98 							},
//DeadCode JIM 26Jun98 					Action	wpacnoactionno,
//DeadCode JIM 26Jun98 					Range	MARGIN
//DeadCode JIM 26Jun98 				},
//DeadCode JIM 26Jun98 				WayPoint
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Posn	{Abs	{FriendlyScoutHomeBase},	
//DeadCode JIM 26Jun98 						 	Abs	{Y FT_EnterLandingPattern}
//DeadCode JIM 26Jun98 							},
//DeadCode JIM 26Jun98 					Action	wpalandingno,
//DeadCode JIM 26Jun98 					Range	DistEnterLandingPattern
//DeadCode JIM 26Jun98 				}
//DeadCode JIM 26Jun98 			},
//DeadCode JIM 26Jun98 			NumInWing	6,
//DeadCode JIM 26Jun98 			NumInForm	6,
//DeadCode JIM 26Jun98 			Duty		DUTYCAP,
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 					Posn	{Abs	{CPP},
//DeadCode JIM 26Jun98 							 Abs	{Y	HeightSize},
//DeadCode JIM 26Jun98 							 Rel	{Intercept	{CPP,CWP},
//DeadCode JIM 26Jun98  									 Bearing	{Random	ANGLES_300Deg,2,ANGLES_120Deg},
//DeadCode JIM 26Jun98 									 Range	{Select STANDARDTRIGGER,1,METRES3000}
//DeadCode JIM 26Jun98 									}	
//DeadCode JIM 26Jun98 							},
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 		   	AirItem	
//DeadCode JIM 26Jun98 			{
//DeadCode JIM 26Jun98 				Side		NAT_FRIEND,
//DeadCode JIM 26Jun98 				Type		FriendlyScoutType00,
//DeadCode JIM 26Jun98 				Home		FriendlyScoutHomeBase,
//DeadCode JIM 26Jun98 				Squadron	{FriendlyScoutSquad,PS_5,PS_6,PS_7,PS_8},
//DeadCode JIM 26Jun98 				MoveCode	AUTO_FOLLOWWP,
//DeadCode JIM 26Jun98 				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
//DeadCode JIM 26Jun98 				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
//DeadCode JIM 26Jun98 				Morale		{Random	EnemyScoutMorale,40,1}
//DeadCode JIM 26Jun98 			}
//DeadCode JIM 26Jun98 		}
//DeadCode JIM 26Jun98 	};
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 	BattleField
//DeadCode JIM 26Jun98 	{
//DeadCode JIM 26Jun98 		FileName	BFSP_BFHatBlCpDun01=BFSPHR08.BF,
//DeadCode JIM 26Jun98 		Setval	{GlobalSkillMin, FriendlyScoutSkillMin},
//DeadCode JIM 26Jun98 		Setval	{GlobalSkillMax, FriendlyScoutSkillMax},
//DeadCode JIM 26Jun98 		AirGroup	
//DeadCode JIM 26Jun98 		{
//DeadCode JIM 26Jun98 			Route	
//DeadCode JIM 26Jun98 			{
//DeadCode JIM 26Jun98 				WayPoint	
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Posn	{Abs	{WP3},
//DeadCode JIM 26Jun98 							 Abs	{Y HeightSize},
//DeadCode JIM 26Jun98 							 Rel	{Intercept {WP3,WP1},
//DeadCode JIM 26Jun98 									 Bearing	ANGLES_90Deg,
//DeadCode JIM 26Jun98 									 Range	METRES500
//DeadCode JIM 26Jun98 									}
//DeadCode JIM 26Jun98 							},
//DeadCode JIM 26Jun98 					Action	wpacnoactionno,
//DeadCode JIM 26Jun98 					Range	MARGIN
//DeadCode JIM 26Jun98 				},
//DeadCode JIM 26Jun98 				WayPoint	
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Posn	{Abs	{WP1},
//DeadCode JIM 26Jun98 							 Abs	{Y HeightSize},
//DeadCode JIM 26Jun98 							 Rel	{Intercept {WP1,WP2},
//DeadCode JIM 26Jun98 									 Bearing	ANGLES_90Deg,
//DeadCode JIM 26Jun98 									 Range	METRES500
//DeadCode JIM 26Jun98 									}
//DeadCode JIM 26Jun98 							},
//DeadCode JIM 26Jun98 					Action	wpacnoactionno,
//DeadCode JIM 26Jun98 					Range	MARGIN
//DeadCode JIM 26Jun98 				},
//DeadCode JIM 26Jun98 				WayPoint	
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Posn	{Abs	{WP1},
//DeadCode JIM 26Jun98 							 Abs	{Y HeightSize},
//DeadCode JIM 26Jun98 							 Rel	{Intercept {WP2,WP1},
//DeadCode JIM 26Jun98 									 Bearing	ANGLES_0Deg,
//DeadCode JIM 26Jun98 									 Range	METRES2000
//DeadCode JIM 26Jun98 									}
//DeadCode JIM 26Jun98 							},
//DeadCode JIM 26Jun98 					Action	wpacnoactionno,
//DeadCode JIM 26Jun98 					Range	MARGIN
//DeadCode JIM 26Jun98 				},
//DeadCode JIM 26Jun98 				WayPoint	
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Posn	{Abs	{WP2},
//DeadCode JIM 26Jun98 							 Abs	{Y HeightSize},
//DeadCode JIM 26Jun98 							 Rel	{Intercept {WP1,WP2},
//DeadCode JIM 26Jun98 									 Bearing	ANGLES_90Deg,
//DeadCode JIM 26Jun98 									 Range	METRES500
//DeadCode JIM 26Jun98 									}
//DeadCode JIM 26Jun98 							},
//DeadCode JIM 26Jun98 					Action	wpacnoactionno,
//DeadCode JIM 26Jun98 					Range	MARGIN
//DeadCode JIM 26Jun98 				},
//DeadCode JIM 26Jun98 				WayPoint	
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Posn	{Abs	{WP2},
//DeadCode JIM 26Jun98 							 Abs	{Y HeightSize},
//DeadCode JIM 26Jun98 							 Rel	{Intercept {WP2,WP1},
//DeadCode JIM 26Jun98 									 Bearing	ANGLES_0Deg,
//DeadCode JIM 26Jun98 									 Range	METRES2000
//DeadCode JIM 26Jun98 									}
//DeadCode JIM 26Jun98 							},
//DeadCode JIM 26Jun98 					Action	wpacnoactionno,
//DeadCode JIM 26Jun98 					Range	MARGIN
//DeadCode JIM 26Jun98 				},
//DeadCode JIM 26Jun98 				WayPoint	
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Posn	{Abs	{WP2},
//DeadCode JIM 26Jun98 							 Abs	{Y HeightSize},
//DeadCode JIM 26Jun98 							 Rel	{Intercept {WP1,WP2},
//DeadCode JIM 26Jun98 									 Bearing	ANGLES_90Deg,
//DeadCode JIM 26Jun98 									 Range	METRES500
//DeadCode JIM 26Jun98 									}
//DeadCode JIM 26Jun98 							},
//DeadCode JIM 26Jun98 					Action	wpacnoactionno,
//DeadCode JIM 26Jun98 					Range	MARGIN
//DeadCode JIM 26Jun98 				},
//DeadCode JIM 26Jun98 				WayPoint
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Posn	{Abs	{FriendlyScoutHomeBase},	
//DeadCode JIM 26Jun98 						 	Abs	{Y FT_EnterLandingPattern}
//DeadCode JIM 26Jun98 							},
//DeadCode JIM 26Jun98 					Action	wpalandingno,
//DeadCode JIM 26Jun98 					Range	DistEnterLandingPattern
//DeadCode JIM 26Jun98 				}
//DeadCode JIM 26Jun98 			},
//DeadCode JIM 26Jun98 			NumInWing	6,
//DeadCode JIM 26Jun98 			NumInForm	6,
//DeadCode JIM 26Jun98 			Duty		DUTYCAP,
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 					Posn	{Abs	{CPP},
//DeadCode JIM 26Jun98 							 Abs	{Y	HeightSize},
//DeadCode JIM 26Jun98 							 Rel	{Intercept	{CPP,CWP},
//DeadCode JIM 26Jun98  									 Bearing	{Random	ANGLES_300Deg,2,ANGLES_120Deg},
//DeadCode JIM 26Jun98 									 Range	{Select STANDARDTRIGGER,1,METRES3000}
//DeadCode JIM 26Jun98 									}	
//DeadCode JIM 26Jun98 							},
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 		   	AirItem	
//DeadCode JIM 26Jun98 			{
//DeadCode JIM 26Jun98 				Side		NAT_FRIEND,
//DeadCode JIM 26Jun98 				Type		FriendlyScoutType00,
//DeadCode JIM 26Jun98 				Home		FriendlyScoutHomeBase,
//DeadCode JIM 26Jun98 				Squadron	{FriendlyScoutSquad,PS_5,PS_6,PS_7,PS_8},
//DeadCode JIM 26Jun98 				MoveCode	AUTO_FOLLOWWP,
//DeadCode JIM 26Jun98 				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
//DeadCode JIM 26Jun98 				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
//DeadCode JIM 26Jun98 				Morale		{Random	EnemyScoutMorale,40,1}
//DeadCode JIM 26Jun98 			}
//DeadCode JIM 26Jun98 		}
//DeadCode JIM 26Jun98 	};
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 	BattleField
//DeadCode JIM 26Jun98 	{
//DeadCode JIM 26Jun98 		FileName	BFSP_HatAirfieldConvoysP2=BFSPHR09.BF
//DeadCode JIM 26Jun98 	};
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 //---------------------------------------------------------------------------
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 	BattleField
//DeadCode JIM 26Jun98 	{
//DeadCode JIM 26Jun98 		FileName	BFSP_LastPush=BFSPHR11.BF,
//DeadCode JIM 26Jun98 		GroundGroup	
//DeadCode JIM 26Jun98 		{
//DeadCode JIM 26Jun98 			Route		
//DeadCode JIM 26Jun98 			{
//DeadCode JIM 26Jun98 				WayPoint
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Posn	{Abs	{UID_NODE_sinuiju},
//DeadCode JIM 26Jun98 					 		Abs	{Y -FT_1},
//DeadCode JIM 26Jun98 							Rel	{Intercept {UID_NODE_sinuiju,UID_NODE_sinuiju},
//DeadCode JIM 26Jun98 									 Bearing	ANGLES_0Deg,
//DeadCode JIM 26Jun98 									 RangePercent 80
//DeadCode JIM 26Jun98 									}
//DeadCode JIM 26Jun98 							},
//DeadCode JIM 26Jun98 					Action	wpdmbtrkstopno
//DeadCode JIM 26Jun98 				}
//DeadCode JIM 26Jun98 			},
//DeadCode JIM 26Jun98 		
//DeadCode JIM 26Jun98 			NumInForm	2,
//DeadCode JIM 26Jun98 			Formation	FORM_SINGLEFILE,
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 					Posn	{Abs	{UID_NODE_sinuiju},
//DeadCode JIM 26Jun98 					 		Abs	{Y -FT_1},
//DeadCode JIM 26Jun98 							Rel	{Intercept {UID_NODE_sinuiju,UID_NODE_sinuiju},
//DeadCode JIM 26Jun98 									 Bearing	ANGLES_0Deg,
//DeadCode JIM 26Jun98 									 RangePercent 50
//DeadCode JIM 26Jun98 									}
//DeadCode JIM 26Jun98 							},
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 		   	GroundItem	LastPush_Item =
//DeadCode JIM 26Jun98 			{
//DeadCode JIM 26Jun98 				Type		SQ_ATruck,
//DeadCode JIM 26Jun98 				Side		NAT_FRIEND,
//DeadCode JIM 26Jun98 				Shape		EMPTY,
//DeadCode JIM 26Jun98 				MoveCode	GROUND_TAXI
//DeadCode JIM 26Jun98 			}
//DeadCode JIM 26Jun98 		},
//DeadCode JIM 26Jun98 		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
//DeadCode JIM 26Jun98 		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
//DeadCode JIM 26Jun98 		AirGroup	
//DeadCode JIM 26Jun98 		{
//DeadCode JIM 26Jun98 			Route	
//DeadCode JIM 26Jun98 			{
//DeadCode JIM 26Jun98 				WayPoint	
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Target	LastPush_Item,
//DeadCode JIM 26Jun98 					Posn	{
//DeadCode JIM 26Jun98 							 Abs	{Y FT_Straffe}
//DeadCode JIM 26Jun98 							},
//DeadCode JIM 26Jun98 					Action	wpstraffeno,
//DeadCode JIM 26Jun98 					Range	BEGINSTRAFFERANGE
//DeadCode JIM 26Jun98 				},
//DeadCode JIM 26Jun98 				WayPoint
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Posn	{Abs	{EnemyScoutHomeBase},
//DeadCode JIM 26Jun98 						 	Abs	{Y FT_EnterLandingPattern}
//DeadCode JIM 26Jun98 							},
//DeadCode JIM 26Jun98 					Action	wpalandingno,
//DeadCode JIM 26Jun98 					Range	DistEnterLandingPattern
//DeadCode JIM 26Jun98 				}
//DeadCode JIM 26Jun98 			},
//DeadCode JIM 26Jun98 			NumInWing	1,
//DeadCode JIM 26Jun98 			NumInForm	1,
//DeadCode JIM 26Jun98 			Duty		DUTYCAP,
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 			Posn	{Abs	{CPP},
//DeadCode JIM 26Jun98 					 Abs	{Y FT_Straffe},		 
//DeadCode JIM 26Jun98 					 Rel	{Intercept	{CPP,LastPush_Item},
//DeadCode JIM 26Jun98 						 	 Bearing	{Random	ANGLES_330Deg,2,ANGLES_60Deg},
//DeadCode JIM 26Jun98 						 	 Range		HALFVISINEDGE
//DeadCode JIM 26Jun98 							}
//DeadCode JIM 26Jun98 					},
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 		   	AirItem	
//DeadCode JIM 26Jun98 			{
//DeadCode JIM 26Jun98 				Side		NAT_ENEMY,
//DeadCode JIM 26Jun98 				Type		SQ_MIG15,
//DeadCode JIM 26Jun98 				Squadron {EnemyChargeSquad},
//DeadCode JIM 26Jun98 				Home		EnemyChargeHomeBase,
//DeadCode JIM 26Jun98 				MoveCode	AUTO_FOLLOWWP,
//DeadCode JIM 26Jun98 				Skill		SKILL_ACE,
//DeadCode JIM 26Jun98 				Character	CHAR_CAVALIER,
//DeadCode JIM 26Jun98 				Morale		MORALE_TOPMORALE
//DeadCode JIM 26Jun98 			}
//DeadCode JIM 26Jun98 		}
//DeadCode JIM 26Jun98 	};
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 //---------------------------------------------------------------------------
//DeadCode JIM 26Jun98 	BattleField
//DeadCode JIM 26Jun98 	{
//DeadCode JIM 26Jun98 		FileName	BFSP_STAFFCARLEAVESTHIAUCOURT=BFSPHR10.BF,
//DeadCode JIM 26Jun98 		GroundGroup	
//DeadCode JIM 26Jun98 		{
//DeadCode JIM 26Jun98 			Route		
//DeadCode JIM 26Jun98 			{
//DeadCode JIM 26Jun98 				WayPoint	
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Posn	{Abs	{ROUTE_HRThiaucourtRembercourt_A},
//DeadCode JIM 26Jun98 							 Abs	{Y -FT_1}
//DeadCode JIM 26Jun98 							},
//DeadCode JIM 26Jun98 					Vel	75,
//DeadCode JIM 26Jun98 					Action	wpdmbtrknoactno
//DeadCode JIM 26Jun98 				},
//DeadCode JIM 26Jun98 				WayPoint	
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Posn	{Abs	{ROUTE_HRThiaucourtRembercourt_B},
//DeadCode JIM 26Jun98 							 Abs	{Y -FT_1}
//DeadCode JIM 26Jun98 							},
//DeadCode JIM 26Jun98 					Vel	75,
//DeadCode JIM 26Jun98 					Action	wpdmbtrknoactno
//DeadCode JIM 26Jun98 				},
//DeadCode JIM 26Jun98 				WayPoint	
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Posn	{Abs	{ROUTE_HRThiaucourtRembercourt_C},
//DeadCode JIM 26Jun98 							 Abs	{Y -FT_1}
//DeadCode JIM 26Jun98 							},
//DeadCode JIM 26Jun98 					Vel	75,
//DeadCode JIM 26Jun98 					Action	wpdmbtrknoactno
//DeadCode JIM 26Jun98 				},
//DeadCode JIM 26Jun98 				WayPoint	
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Posn	{Abs	{ROUTE_HRThiaucourtRembercourt_D},
//DeadCode JIM 26Jun98 							 Abs	{Y -FT_1}
//DeadCode JIM 26Jun98 							},
//DeadCode JIM 26Jun98 					Vel	75,
//DeadCode JIM 26Jun98 					Action	wpdmbtrknoactno
//DeadCode JIM 26Jun98 				},
//DeadCode JIM 26Jun98 				WayPoint	
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Posn	{Abs	{ROUTE_HRThiaucourtRembercourt_E},
//DeadCode JIM 26Jun98 							 Abs	{Y -FT_1}
//DeadCode JIM 26Jun98 							},
//DeadCode JIM 26Jun98 					Vel	75,
//DeadCode JIM 26Jun98 					Action	wpdmbtrknoactno
//DeadCode JIM 26Jun98 				},
//DeadCode JIM 26Jun98 				WayPoint	
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Posn	{Abs	{ROUTE_HRThiaucourtRembercourt_F},
//DeadCode JIM 26Jun98 							 Abs	{Y -FT_1}
//DeadCode JIM 26Jun98 							},
//DeadCode JIM 26Jun98 					Vel	75,
//DeadCode JIM 26Jun98 					Action	wpdmbtrknoactno
//DeadCode JIM 26Jun98 				},
//DeadCode JIM 26Jun98 				WayPoint	
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Posn	{Abs	{ROUTE_HRThiaucourtRembercourt_G},
//DeadCode JIM 26Jun98 							 Abs	{Y -FT_1}
//DeadCode JIM 26Jun98 							},
//DeadCode JIM 26Jun98 					Vel	75,
//DeadCode JIM 26Jun98 					Action	wpdmbtrknoactno
//DeadCode JIM 26Jun98 				},
//DeadCode JIM 26Jun98 				WayPoint	
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Posn	{Abs	{ROUTE_HRThiaucourtRembercourt_H},
//DeadCode JIM 26Jun98 							 Abs	{Y -FT_1}
//DeadCode JIM 26Jun98 							},
//DeadCode JIM 26Jun98 					Vel	75,
//DeadCode JIM 26Jun98 					Action	wpdmbtrknoactno
//DeadCode JIM 26Jun98 				},
//DeadCode JIM 26Jun98 				WayPoint	
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Posn	{Abs	{ROUTE_HRThiaucourtRembercourt_I},
//DeadCode JIM 26Jun98 							 Abs	{Y -FT_1}
//DeadCode JIM 26Jun98 							},
//DeadCode JIM 26Jun98 					Vel	75,
//DeadCode JIM 26Jun98 					Action	wpdmbtrknoactno
//DeadCode JIM 26Jun98 				},
//DeadCode JIM 26Jun98 				WayPoint	
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Posn	{Abs	{ROUTE_HRThiaucourtRembercourt_J},
//DeadCode JIM 26Jun98 							 Abs	{Y -FT_1}
//DeadCode JIM 26Jun98 							},
//DeadCode JIM 26Jun98 					Vel	70,
//DeadCode JIM 26Jun98 					Action	wpdmbtrknoactno
//DeadCode JIM 26Jun98 				},
//DeadCode JIM 26Jun98 				WayPoint	
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Posn	{Abs	{ROUTE_HRThiaucourtRembercourt_K},
//DeadCode JIM 26Jun98 							 Abs	{Y -FT_1}
//DeadCode JIM 26Jun98 							},
//DeadCode JIM 26Jun98 					Vel	70,
//DeadCode JIM 26Jun98 					Action	wpdmbtrknoactno
//DeadCode JIM 26Jun98 				},
//DeadCode JIM 26Jun98 				WayPoint	
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Posn	{Abs	{ROUTE_HRThiaucourtRembercourt_L},
//DeadCode JIM 26Jun98 							 Abs	{Y -FT_1}
//DeadCode JIM 26Jun98 							},
//DeadCode JIM 26Jun98 					Vel	70,
//DeadCode JIM 26Jun98 					Action	wpdmbtrknoactno
//DeadCode JIM 26Jun98 				},
//DeadCode JIM 26Jun98 				WayPoint	
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Posn	{Abs	{ROUTE_HRThiaucourtRembercourt_M},
//DeadCode JIM 26Jun98 							 Abs	{Y -FT_1}
//DeadCode JIM 26Jun98 							},
//DeadCode JIM 26Jun98 					Vel	70,
//DeadCode JIM 26Jun98 					Action	wpdmbtrkstopno
//DeadCode JIM 26Jun98 				}
//DeadCode JIM 26Jun98 			},
//DeadCode JIM 26Jun98 			
//DeadCode JIM 26Jun98 			NumInForm	1,
//DeadCode JIM 26Jun98 			Formation	FORM_SINGLEFILE,
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 			Posn	{Abs	{ROUTE_HRThiaucourtRembercourt_A},
//DeadCode JIM 26Jun98 					 Abs	{Y -FT_1},
//DeadCode JIM 26Jun98 					 Rel	{Intercept	{ROUTE_HRThiaucourtRembercourt_B,ROUTE_HRThiaucourtRembercourt_A},
//DeadCode JIM 26Jun98 							 Bearing	ANGLES_0Deg,
//DeadCode JIM 26Jun98 							 Range	METRES10
//DeadCode JIM 26Jun98 							}
//DeadCode JIM 26Jun98 					},
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 		   	GroundItem	
//DeadCode JIM 26Jun98 			{
//DeadCode JIM 26Jun98 				Type		SQ_ATruck,
//DeadCode JIM 26Jun98 				Side		NAT_ENEMY,
//DeadCode JIM 26Jun98 				Shape		EMPTY,
//DeadCode JIM 26Jun98 				Vel			1,
//DeadCode JIM 26Jun98 				MoveCode	GROUND_TAXI
//DeadCode JIM 26Jun98 			}
//DeadCode JIM 26Jun98 		}
//DeadCode JIM 26Jun98 	};
//DeadCode JIM 26Jun98 //---------------------------------------------------------------------------
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 	BattleField
//DeadCode JIM 26Jun98 	{
//DeadCode JIM 26Jun98 		FileName	BFSP_CrcsSouthPatrol3WP00=BFSCrc00.BF,
//DeadCode JIM 26Jun98 		GroundGroup	
//DeadCode JIM 26Jun98 		{
//DeadCode JIM 26Jun98 			Route		
//DeadCode JIM 26Jun98 			{
//DeadCode JIM 26Jun98 				WayPoint	
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Posn	{Abs	{UID_NODE_AnTung},
//DeadCode JIM 26Jun98 							 Abs	{Y -FT_1}
//DeadCode JIM 26Jun98 							},
//DeadCode JIM 26Jun98 					Vel	10,
//DeadCode JIM 26Jun98 					Action	wpdmbtrkstopno
//DeadCode JIM 26Jun98 				}
//DeadCode JIM 26Jun98 			},
//DeadCode JIM 26Jun98 			
//DeadCode JIM 26Jun98 			NumInForm	3,
//DeadCode JIM 26Jun98 			Formation	FORM_SINGLEFILE,
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 			Posn	{Abs	{UID_NODE_AnTung},
//DeadCode JIM 26Jun98 					 Abs	{Y -FT_1},
//DeadCode JIM 26Jun98 					 Rel	{Intercept	{UID_NODE_AnTung,UID_NODE_AnTung},
//DeadCode JIM 26Jun98 							 Bearing	ANGLES_0Deg,
//DeadCode JIM 26Jun98 							 Range	HALFVISINEDGE
//DeadCode JIM 26Jun98 							}
//DeadCode JIM 26Jun98 					},
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 		   	GroundItem	
//DeadCode JIM 26Jun98 			{
//DeadCode JIM 26Jun98 				Type		SQ_ATruck,
//DeadCode JIM 26Jun98 				Side		NAT_FRIEND,
//DeadCode JIM 26Jun98 				Shape		EMPTY,
//DeadCode JIM 26Jun98 				Vel			10,
//DeadCode JIM 26Jun98 				MoveCode	GROUND_TAXI,
//DeadCode JIM 26Jun98 				SetUID		UID_FCTroopsCambraiBoursies
//DeadCode JIM 26Jun98 			}
//DeadCode JIM 26Jun98 		},
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
//DeadCode JIM 26Jun98 		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
//DeadCode JIM 26Jun98 		AirGroup
//DeadCode JIM 26Jun98 		{
//DeadCode JIM 26Jun98 			Route
//DeadCode JIM 26Jun98 			{
//DeadCode JIM 26Jun98 				WayPoint	
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Target	UID_FCTroopsCambraiBoursies,
//DeadCode JIM 26Jun98 					Posn	{Abs	{Y FT_Straffe}},
//DeadCode JIM 26Jun98 					Action	wpstraffeno,
//DeadCode JIM 26Jun98 					Range	BEGINSTRAFFERANGE
//DeadCode JIM 26Jun98 				},
//DeadCode JIM 26Jun98 				WayPoint	
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Posn	{Abs	{EnemyChargeHomeBase}, 
//DeadCode JIM 26Jun98 						 	Abs	{Y FT_EnterLandingPattern}
//DeadCode JIM 26Jun98 							},
//DeadCode JIM 26Jun98 					Action	wpalandingno,
//DeadCode JIM 26Jun98 					Range	DistEnterLandingPattern
//DeadCode JIM 26Jun98 				}
//DeadCode JIM 26Jun98 			},
//DeadCode JIM 26Jun98 			NumInWing	2,
//DeadCode JIM 26Jun98 			NumInForm	4,
//DeadCode JIM 26Jun98 			Duty		DUTYCAP,
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 			Posn	{Abs	{UID_NODE_AnTung},
//DeadCode JIM 26Jun98 					 Abs	{Y -FT_1},
//DeadCode JIM 26Jun98 					 Rel	{Intercept	{UID_NODE_AnTung,UID_NODE_AnTung},
//DeadCode JIM 26Jun98 							 Bearing	ANGLES_0Deg,
//DeadCode JIM 26Jun98 							 Range	HALFVISINEDGE
//DeadCode JIM 26Jun98 							}
//DeadCode JIM 26Jun98 					},
//DeadCode JIM 26Jun98 				
//DeadCode JIM 26Jun98 		   	AirItem		
//DeadCode JIM 26Jun98 			{
//DeadCode JIM 26Jun98 				Side		NAT_ENEMY,
//DeadCode JIM 26Jun98 				Type		EnemyChargeType00,
//DeadCode JIM 26Jun98 				Squadron 	{EnemyChargeSquad},
//DeadCode JIM 26Jun98 				Home		EnemyChargeHomeBase,
//DeadCode JIM 26Jun98 				MoveCode	AUTO_FOLLOWWP,
//DeadCode JIM 26Jun98 				Skill		{List SKILL_VETERAN,SKILL_REGULAR},
//DeadCode JIM 26Jun98 				Character	EnemyChargeCharacter,
//DeadCode JIM 26Jun98 				Morale		{Random	EnemyChargeMorale,40,1}
//DeadCode JIM 26Jun98 			}
//DeadCode JIM 26Jun98 		}
//DeadCode JIM 26Jun98 	};
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 //---------------------------------------------------------------------------
//DeadCode JIM 26Jun98 	BattleField
//DeadCode JIM 26Jun98 	{
//DeadCode JIM 26Jun98 		FileName	BFSP_CRCSNORTHPATROL3WP00=BFScrc01.BF,
//DeadCode JIM 26Jun98 		GroundGroup	
//DeadCode JIM 26Jun98 		{
//DeadCode JIM 26Jun98 			Route		
//DeadCode JIM 26Jun98 			{
//DeadCode JIM 26Jun98 				WayPoint	
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Posn	{Abs	{UID_NODE_AnTung},
//DeadCode JIM 26Jun98 							 Abs	{Y -FT_1}
//DeadCode JIM 26Jun98 							},
//DeadCode JIM 26Jun98 					Range	MARGIN,
//DeadCode JIM 26Jun98 					Vel	50,
//DeadCode JIM 26Jun98 					Action	wpdmbtrkstopno
//DeadCode JIM 26Jun98 				}
//DeadCode JIM 26Jun98 			},
//DeadCode JIM 26Jun98 			
//DeadCode JIM 26Jun98 			NumInForm	8,
//DeadCode JIM 26Jun98 			Formation	FORM_SINGLEFILE,
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 			Posn	{Abs	{UID_NODE_AnTung},
//DeadCode JIM 26Jun98 					 Abs	{Y -FT_1},
//DeadCode JIM 26Jun98 					 Rel	{Intercept	{UID_NODE_AnTung,UID_NODE_sinuiju},
//DeadCode JIM 26Jun98 							 Bearing	ANGLES_0Deg,
//DeadCode JIM 26Jun98 							 Range	VISINEDGE
//DeadCode JIM 26Jun98 							}
//DeadCode JIM 26Jun98 					},
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 		   	GroundItem		
//DeadCode JIM 26Jun98 			{
//DeadCode JIM 26Jun98 				Type		SQ_ATruck,
//DeadCode JIM 26Jun98 				Side		NAT_FRIEND,
//DeadCode JIM 26Jun98 				Shape		EMPTY,
//DeadCode JIM 26Jun98 				Vel			50,
//DeadCode JIM 26Jun98 				MoveCode	GROUND_TAXI,
//DeadCode JIM 26Jun98 				SetUID		UID_CRCSNORTHPATROL3WP00_Item00
//DeadCode JIM 26Jun98 			}
//DeadCode JIM 26Jun98 		},
//DeadCode JIM 26Jun98 		AirGroup	
//DeadCode JIM 26Jun98 		{
//DeadCode JIM 26Jun98 			Route	
//DeadCode JIM 26Jun98 			{
//DeadCode JIM 26Jun98 				WayPoint	
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Target	UID_CRCSNORTHPATROL3WP00_Item00,
//DeadCode JIM 26Jun98 					Posn	{Abs	{Y FT_SpotAlt}},
//DeadCode JIM 26Jun98 					Action	wpstraffeno,
//DeadCode JIM 26Jun98 					Range	BEGINSPOTRANGE
//DeadCode JIM 26Jun98 				},
//DeadCode JIM 26Jun98 				WayPoint	
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Posn	{Abs	{EnemyChargeHomeBase}, 
//DeadCode JIM 26Jun98 						 	Abs	{Y FT_EnterLandingPattern}
//DeadCode JIM 26Jun98 							},
//DeadCode JIM 26Jun98 					Action	wpalandingno,
//DeadCode JIM 26Jun98 					Range	DistEnterLandingPattern
//DeadCode JIM 26Jun98 				}
//DeadCode JIM 26Jun98 			},
//DeadCode JIM 26Jun98 			NumInWing	2,
//DeadCode JIM 26Jun98 			NumInForm	2,
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 			Posn		{Abs	{CPP},
//DeadCode JIM 26Jun98 						 Abs	{Y	FT_SpotAlt},
//DeadCode JIM 26Jun98 						 Rel	{Intercept	{CPP, UID_NODE_AnTung},
//DeadCode JIM 26Jun98 							 	 Bearing	{Random ANGLES_0Deg,45,ANGLES_1Deg},
//DeadCode JIM 26Jun98 							 	 Range		VISINEDGE
//DeadCode JIM 26Jun98 								}
//DeadCode JIM 26Jun98 						}, 
//DeadCode JIM 26Jun98 		   	AirItem		
//DeadCode JIM 26Jun98 			{
//DeadCode JIM 26Jun98 				Side		NAT_ENEMY,
//DeadCode JIM 26Jun98 				Type		EnemyChargeType00,
//DeadCode JIM 26Jun98 				Squadron 	{EnemyChargeSquad},
//DeadCode JIM 26Jun98 				Home		EnemyChargeHomeBase,
//DeadCode JIM 26Jun98 				MoveCode	AUTO_FOLLOWWP,
//DeadCode JIM 26Jun98 				Skill		{List SKILL_VETERAN,SKILL_REGULAR},
//DeadCode JIM 26Jun98 				Character	EnemyChargeCharacter,
//DeadCode JIM 26Jun98 				Morale		{Random	EnemyChargeMorale,40,1}
//DeadCode JIM 26Jun98 			}
//DeadCode JIM 26Jun98 		}
//DeadCode JIM 26Jun98 	};
//DeadCode JIM 26Jun98 //---------------------------------------------------------------------------
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 	BattleField
//DeadCode JIM 26Jun98 	{
//DeadCode JIM 26Jun98 		FileName	BFSP_BFCRCSBEHINDINTERCEPTUNESCORTED=BFScrc02.BF,
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
//DeadCode JIM 26Jun98 		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
//DeadCode JIM 26Jun98 		AirGroup	
//DeadCode JIM 26Jun98 		{
//DeadCode JIM 26Jun98 			Route	
//DeadCode JIM 26Jun98 			{
//DeadCode JIM 26Jun98 //DeadCode DAW 13Jan97 				WayPoint	
//DeadCode JIM 26Jun98 //DeadCode DAW 13Jan97 				{
//DeadCode JIM 26Jun98 //DeadCode DAW 13Jan97 					Target	UID_JournoCar,
//DeadCode JIM 26Jun98 //DeadCode DAW 13Jan97 					Posn	{Abs	{Y FT_Straffe}},
//DeadCode JIM 26Jun98 //DeadCode DAW 13Jan97 					Range	BEGINSTRAFFERANGE,
//DeadCode JIM 26Jun98 //DeadCode DAW 13Jan97 					Action	wpstraffeno
//DeadCode JIM 26Jun98 //DeadCode DAW 13Jan97 				},
//DeadCode JIM 26Jun98 				WayPoint
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Posn	{Abs	{EnemyScoutHomeBase},
//DeadCode JIM 26Jun98 						 	Abs	{Y	FT_4000}
//DeadCode JIM 26Jun98 							},
//DeadCode JIM 26Jun98 					Action	wpacnoactionno,
//DeadCode JIM 26Jun98 					Range	STANDARDTRIGGER
//DeadCode JIM 26Jun98 				},
//DeadCode JIM 26Jun98 				WayPoint
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Posn	{Abs	{EnemyScoutHomeBase},
//DeadCode JIM 26Jun98 						 	Abs	{Y FT_EnterLandingPattern}
//DeadCode JIM 26Jun98 							},
//DeadCode JIM 26Jun98 					Action	wpalandingno,
//DeadCode JIM 26Jun98 					Range	DistEnterLandingPattern
//DeadCode JIM 26Jun98 				}
//DeadCode JIM 26Jun98 			},
//DeadCode JIM 26Jun98 			NumInWing	1,
//DeadCode JIM 26Jun98 			NumInForm	3,
//DeadCode JIM 26Jun98 			Duty		DUTYCAP,
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 			Posn	{Abs	{CPP},
//DeadCode JIM 26Jun98 					 Abs	{Y FT_Straffe}		 
//DeadCode JIM 26Jun98 //DeadCode DAW 13Jan97 					 Rel	{Intercept	{CPP,UID_JournoCar},
//DeadCode JIM 26Jun98 //DeadCode DAW 13Jan97 						 	 Bearing	ANGLES_0Deg,
//DeadCode JIM 26Jun98 //DeadCode DAW 13Jan97 						 	 Range		VISINEDGE
//DeadCode JIM 26Jun98 //DeadCode DAW 13Jan97 							}
//DeadCode JIM 26Jun98 					},
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 		   	AirItem	
//DeadCode JIM 26Jun98 			{
//DeadCode JIM 26Jun98 				Side		NAT_ENEMY,
//DeadCode JIM 26Jun98 				Type		EnemyScoutType00,
//DeadCode JIM 26Jun98 				Squadron {EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
//DeadCode JIM 26Jun98 				Home		EnemyScoutHomeBase,
//DeadCode JIM 26Jun98 				MoveCode	AUTO_FOLLOWWP,
//DeadCode JIM 26Jun98 				Skill		SKILL_ACE,
//DeadCode JIM 26Jun98 				Character	EnemyScoutCavalier,
//DeadCode JIM 26Jun98 				Morale		255
//DeadCode JIM 26Jun98 			}
//DeadCode JIM 26Jun98 		}
//DeadCode JIM 26Jun98 	};
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 //---------------------------------------------------------------------------
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 	BattleField
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 	{
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 		FileName	BFSP_CRCSBEHINDBALLOONPATROL01=BFScrc03.BF
//DeadCode JIM 26Jun98 //dummy route until ROUTE_FCIwuyCambrai FIXME				//MS 09Sep96
//DeadCode JIM 26Jun98 //DeadCode MS 26Nov96 		GroundGroup	
//DeadCode JIM 26Jun98 //DeadCode MS 26Nov96 		{
//DeadCode JIM 26Jun98 //DeadCode MS 26Nov96 			Route		
//DeadCode JIM 26Jun98 //DeadCode MS 26Nov96 			{
//DeadCode JIM 26Jun98 //DeadCode MS 26Nov96 				WayPoint	
//DeadCode JIM 26Jun98 //DeadCode MS 26Nov96 				{
//DeadCode JIM 26Jun98 //DeadCode MS 26Nov96 					Posn	{Abs	{UID_NODE_AnTung},
//DeadCode JIM 26Jun98 //DeadCode MS 26Nov96 							 Abs	{Y -FT_1}
//DeadCode JIM 26Jun98 //DeadCode MS 26Nov96 							},
//DeadCode JIM 26Jun98 //DeadCode MS 26Nov96 					Range	MARGIN,
//DeadCode JIM 26Jun98 //DeadCode MS 26Nov96 					Action	wpdmbtrkstopno
//DeadCode JIM 26Jun98 //DeadCode MS 26Nov96 				}
//DeadCode JIM 26Jun98 //DeadCode MS 26Nov96 			},
//DeadCode JIM 26Jun98 //DeadCode MS 26Nov96 			
//DeadCode JIM 26Jun98 //DeadCode MS 26Nov96 			NumInForm	1,
//DeadCode JIM 26Jun98 //DeadCode MS 26Nov96 			Formation	FORM_SINGLEFILE,
//DeadCode JIM 26Jun98 //DeadCode MS 26Nov96 
//DeadCode JIM 26Jun98 //DeadCode MS 26Nov96 			Posn	{Abs	{UID_AfCpIwuy},
//DeadCode JIM 26Jun98 //DeadCode MS 26Nov96 					 Abs	{Y -FT_1}
//DeadCode JIM 26Jun98 //DeadCode MS 26Nov96 					},
//DeadCode JIM 26Jun98 //DeadCode MS 26Nov96 
//DeadCode JIM 26Jun98 //DeadCode MS 26Nov96 		   	GroundItem	
//DeadCode JIM 26Jun98 //DeadCode MS 26Nov96 			{
//DeadCode JIM 26Jun98 //DeadCode MS 26Nov96 				Type		SQ_ATruck,
//DeadCode JIM 26Jun98 //DeadCode MS 26Nov96 				Side		NAT_FRIEND,
//DeadCode JIM 26Jun98 //DeadCode MS 26Nov96 				Shape		WINCH,
//DeadCode JIM 26Jun98 //DeadCode MS 26Nov96 				MoveCode	GROUND_TAXI
//DeadCode JIM 26Jun98 //DeadCode MS 26Nov96 			}
//DeadCode JIM 26Jun98 //DeadCode MS 26Nov96 		}
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 	};
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 //---------------------------------------------------------------------------
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 	BattleField
//DeadCode JIM 26Jun98 	{
//DeadCode JIM 26Jun98 		FileName	BFSP_CRCSKillAlbertBall=BFfcsp00.BF,
//DeadCode JIM 26Jun98 //flight C
//DeadCode JIM 26Jun98 		Setval	{GlobalSkillMin, EnemyScoutSkillMin},
//DeadCode JIM 26Jun98 		Setval	{GlobalSkillMax, EnemyScoutSkillMax},
//DeadCode JIM 26Jun98 		AirGroup	
//DeadCode JIM 26Jun98 		{
//DeadCode JIM 26Jun98 			Route	
//DeadCode JIM 26Jun98 			{
//DeadCode JIM 26Jun98 				WayPoint	
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Posn	{Abs	{WP1},
//DeadCode JIM 26Jun98 							 Abs	{Y FT_9000}
//DeadCode JIM 26Jun98 							},	
//DeadCode JIM 26Jun98 					Action	wpacnoactionno,
//DeadCode JIM 26Jun98 					Range	MARGIN
//DeadCode JIM 26Jun98 				},
//DeadCode JIM 26Jun98 				WayPoint	
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Posn	{Abs	{WP3},
//DeadCode JIM 26Jun98 							 Abs	{Y FT_9000}
//DeadCode JIM 26Jun98 							},	
//DeadCode JIM 26Jun98 					Action	wpacnoactionno,
//DeadCode JIM 26Jun98 					Range	MARGIN
//DeadCode JIM 26Jun98 				},
//DeadCode JIM 26Jun98 				WayPoint
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Posn	{Abs	{EnemyScoutHomeBase},	
//DeadCode JIM 26Jun98 						 	Abs	{Y FT_EnterLandingPattern}
//DeadCode JIM 26Jun98 							},
//DeadCode JIM 26Jun98 					Action	wpalandingno,
//DeadCode JIM 26Jun98 					Range	DistEnterLandingPattern
//DeadCode JIM 26Jun98 				}
//DeadCode JIM 26Jun98 			},
//DeadCode JIM 26Jun98 			NumInWing	3,
//DeadCode JIM 26Jun98 			NumInForm	3,
//DeadCode JIM 26Jun98 			Duty		DUTYCAP,
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 			Posn		{Abs	{CWP},
//DeadCode JIM 26Jun98 						 Abs	{Y FT_9000},
//DeadCode JIM 26Jun98 						 Rel	{Intercept	{CPP,CWP},
//DeadCode JIM 26Jun98 								 Bearing	{Random	ANGLES_300Deg,120,ANGLES_1Deg},
//DeadCode JIM 26Jun98 								 Range	VISINEDGE
//DeadCode JIM 26Jun98 								}	
//DeadCode JIM 26Jun98 						},
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 		   	AirItem
//DeadCode JIM 26Jun98 			{
//DeadCode JIM 26Jun98 				Side		NAT_ENEMY,
//DeadCode JIM 26Jun98 				Type		EnemyScoutType00,
//DeadCode JIM 26Jun98 				Squadron {EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
//DeadCode JIM 26Jun98 				Home		EnemyScoutHomeBase,
//DeadCode JIM 26Jun98 				MoveCode	AUTO_FOLLOWWP,
//DeadCode JIM 26Jun98 				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
//DeadCode JIM 26Jun98 				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
//DeadCode JIM 26Jun98 				Morale		{Random	EnemyScoutMorale,40,1}
//DeadCode JIM 26Jun98 			}
//DeadCode JIM 26Jun98 		},
//DeadCode JIM 26Jun98 //flight B
//DeadCode JIM 26Jun98 		AirGroup	
//DeadCode JIM 26Jun98 		{
//DeadCode JIM 26Jun98 			Route	
//DeadCode JIM 26Jun98 			{
//DeadCode JIM 26Jun98 				WayPoint	
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Posn	{Abs	{WP1},
//DeadCode JIM 26Jun98 							 Abs	{Y FT_10000}
//DeadCode JIM 26Jun98 							},	
//DeadCode JIM 26Jun98 					Action	wpacnoactionno,
//DeadCode JIM 26Jun98 					Range	MARGIN
//DeadCode JIM 26Jun98 				},
//DeadCode JIM 26Jun98 				WayPoint	
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Posn	{Abs	{WP3},
//DeadCode JIM 26Jun98 							 Abs	{Y FT_10000}
//DeadCode JIM 26Jun98 							},	
//DeadCode JIM 26Jun98 					Action	wpacnoactionno,
//DeadCode JIM 26Jun98 					Range	MARGIN
//DeadCode JIM 26Jun98 				},
//DeadCode JIM 26Jun98 				WayPoint
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Posn	{Abs	{EnemyScoutHomeBase},	
//DeadCode JIM 26Jun98 						 	Abs	{Y FT_EnterLandingPattern}
//DeadCode JIM 26Jun98 							},
//DeadCode JIM 26Jun98 					Action	wpalandingno,
//DeadCode JIM 26Jun98 					Range	DistEnterLandingPattern
//DeadCode JIM 26Jun98 				}
//DeadCode JIM 26Jun98 			},
//DeadCode JIM 26Jun98 			NumInWing	3,
//DeadCode JIM 26Jun98 			NumInForm	3,
//DeadCode JIM 26Jun98 			Duty		DUTYCAP,
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 			Posn		{Abs	{CWP},
//DeadCode JIM 26Jun98 						 Abs	{Y FT_10000},
//DeadCode JIM 26Jun98 						 Rel	{Intercept	{CPP,CWP},
//DeadCode JIM 26Jun98 								 Bearing	{Random	ANGLES_300Deg,120,ANGLES_1Deg},
//DeadCode JIM 26Jun98 								 Range	VISINEDGE
//DeadCode JIM 26Jun98 								}	
//DeadCode JIM 26Jun98 						},
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 		   	AirItem
//DeadCode JIM 26Jun98 			{
//DeadCode JIM 26Jun98 				Side		NAT_ENEMY,
//DeadCode JIM 26Jun98 				Type		EnemyScoutType00,
//DeadCode JIM 26Jun98 				Squadron {EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
//DeadCode JIM 26Jun98 				Home		EnemyScoutHomeBase,
//DeadCode JIM 26Jun98 				MoveCode	AUTO_FOLLOWWP,
//DeadCode JIM 26Jun98 				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
//DeadCode JIM 26Jun98 				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
//DeadCode JIM 26Jun98 				Morale		{Random	EnemyScoutMorale,40,1}
//DeadCode JIM 26Jun98 			}
//DeadCode JIM 26Jun98 		},
//DeadCode JIM 26Jun98 //flight A, Albert Ball
//DeadCode JIM 26Jun98 		AirGroup	
//DeadCode JIM 26Jun98 		{
//DeadCode JIM 26Jun98 			Route	
//DeadCode JIM 26Jun98 			{
//DeadCode JIM 26Jun98 				WayPoint	KillBall_WP00=
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Posn	{Abs	{WP1},
//DeadCode JIM 26Jun98 							 Abs	{Y FT_12000}
//DeadCode JIM 26Jun98 							},	
//DeadCode JIM 26Jun98 					Action	wpacnoactionno,
//DeadCode JIM 26Jun98 					Range	MARGIN
//DeadCode JIM 26Jun98 				},
//DeadCode JIM 26Jun98 				WayPoint	
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Posn	{Abs	{WP3},
//DeadCode JIM 26Jun98 							 Abs	{Y FT_12000}
//DeadCode JIM 26Jun98 							},	
//DeadCode JIM 26Jun98 					Action	wpacnoactionno,
//DeadCode JIM 26Jun98 					Range	MARGIN
//DeadCode JIM 26Jun98 				},
//DeadCode JIM 26Jun98 				WayPoint
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Posn	{Abs	{EnemyScoutHomeBase},	
//DeadCode JIM 26Jun98 						 	Abs	{Y FT_EnterLandingPattern}
//DeadCode JIM 26Jun98 							},
//DeadCode JIM 26Jun98 					Action	wpalandingno,
//DeadCode JIM 26Jun98 					Range	DistEnterLandingPattern
//DeadCode JIM 26Jun98 				}
//DeadCode JIM 26Jun98 			},
//DeadCode JIM 26Jun98 			NumInWing	1,
//DeadCode JIM 26Jun98 			NumInForm	1,
//DeadCode JIM 26Jun98 			Duty		DUTYCAP,
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 			Posn		{Abs	{CPP},
//DeadCode JIM 26Jun98 						 Abs	{Y FT_12000},
//DeadCode JIM 26Jun98 						 Rel	{Intercept	{CPP,CWP},
//DeadCode JIM 26Jun98 								 Bearing	{Random	ANGLES_300Deg,120,ANGLES_1Deg},
//DeadCode JIM 26Jun98 								 Range	VISINEDGE
//DeadCode JIM 26Jun98 								}	
//DeadCode JIM 26Jun98 						},
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 		   	AirItem	AlbertBall_Item =
//DeadCode JIM 26Jun98 			{
//DeadCode JIM 26Jun98 				Side		NAT_ENEMY,
//DeadCode JIM 26Jun98 				Type		EnemyScoutType00,
//DeadCode JIM 26Jun98 				Squadron {SqdnAce56,
//DeadCode JIM 26Jun98 						  PaintScheme {Select COL_ALL,COL_E3}
//DeadCode JIM 26Jun98 						 },
//DeadCode JIM 26Jun98 				Home		EnemyScoutHomeBase,
//DeadCode JIM 26Jun98 				MoveCode	AUTO_FOLLOWWP,
//DeadCode JIM 26Jun98 				Skill		SKILL_HERO,
//DeadCode JIM 26Jun98 				Character	CHAR_CAVALIER,
//DeadCode JIM 26Jun98 				Morale		MORALE_TOPMORALE
//DeadCode JIM 26Jun98 			}
//DeadCode JIM 26Jun98 		},
//DeadCode JIM 26Jun98 //flight A, Knaggs
//DeadCode JIM 26Jun98 		AirGroup	
//DeadCode JIM 26Jun98 		{
//DeadCode JIM 26Jun98 			Route	KillBall_WP00,
//DeadCode JIM 26Jun98 	
//DeadCode JIM 26Jun98 			NumInWing	1,
//DeadCode JIM 26Jun98 			NumInForm	1,
//DeadCode JIM 26Jun98 			Duty		DUTYCAP,
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 			Posn		{Abs	AlbertBall_Item},
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 		   	AirItem
//DeadCode JIM 26Jun98 			{
//DeadCode JIM 26Jun98 				Side		NAT_ENEMY,
//DeadCode JIM 26Jun98 				Type		EnemyScoutType00,
//DeadCode JIM 26Jun98 				Squadron {EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
//DeadCode JIM 26Jun98 				Home		EnemyScoutHomeBase,
//DeadCode JIM 26Jun98 				MoveCode	AUTO_FOLLOWWP,
//DeadCode JIM 26Jun98 				Skill		SKILL_VETERAN,
//DeadCode JIM 26Jun98 				Character	CHAR_CAVALIER,
//DeadCode JIM 26Jun98 				Morale		{Random	EnemyScoutMorale,40,1},
//DeadCode JIM 26Jun98 				Leader		AlbertBall_Item
//DeadCode JIM 26Jun98 			}
//DeadCode JIM 26Jun98 		}
//DeadCode JIM 26Jun98 	};
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 //---------------------------------------------------------------------------
//DeadCode JIM 26Jun98 	BattleField
//DeadCode JIM 26Jun98 	{
//DeadCode JIM 26Jun98 		FileName	BFSP_CRCBIGWING=BFfcsp01.BF,
//DeadCode JIM 26Jun98 		Setval	{GlobalSkillMin, FriendlyScoutSkillMin},
//DeadCode JIM 26Jun98 		Setval	{GlobalSkillMax, FriendlyScoutSkillMax},
//DeadCode JIM 26Jun98 		AirGroup	
//DeadCode JIM 26Jun98 		{
//DeadCode JIM 26Jun98 			Route	
//DeadCode JIM 26Jun98 			{
//DeadCode JIM 26Jun98 				WayPoint	
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Posn	{Abs	{UID_NODE_AnTung},
//DeadCode JIM 26Jun98 							 Abs	{Y HeightSize}
//DeadCode JIM 26Jun98 							},
//DeadCode JIM 26Jun98 					Action	wpacnoactionno,
//DeadCode JIM 26Jun98 					Range	MARGIN
//DeadCode JIM 26Jun98 				},
//DeadCode JIM 26Jun98 				WayPoint	
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Posn	{Abs	{UID_NODE_sinuiju},
//DeadCode JIM 26Jun98 							 Abs	{Y HeightSize}
//DeadCode JIM 26Jun98 							},
//DeadCode JIM 26Jun98 					Action	wpacnoactionno,
//DeadCode JIM 26Jun98 					Range	MARGIN
//DeadCode JIM 26Jun98 				},
//DeadCode JIM 26Jun98 				WayPoint	
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Posn	{Abs	{UID_NODE_AnTung},
//DeadCode JIM 26Jun98 							 Abs	{Y HeightSize}
//DeadCode JIM 26Jun98 							},
//DeadCode JIM 26Jun98 					Action	wpacnoactionno,
//DeadCode JIM 26Jun98 					Range	MARGIN
//DeadCode JIM 26Jun98 				},
//DeadCode JIM 26Jun98 				WayPoint	
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Posn	{Abs	{UID_NODE_sinuiju},
//DeadCode JIM 26Jun98 							 Abs	{Y HeightSize}
//DeadCode JIM 26Jun98 							},
//DeadCode JIM 26Jun98 					Action	wpacnoactionno,
//DeadCode JIM 26Jun98 					Range	MARGIN
//DeadCode JIM 26Jun98 				},
//DeadCode JIM 26Jun98 //TempCode MS 29Oct96 				WayPoint
//DeadCode JIM 26Jun98 //TempCode MS 29Oct96 				{
//DeadCode JIM 26Jun98 //TempCode MS 29Oct96 					Posn	{Abs	{FriendlyScoutHomeBase},	
//DeadCode JIM 26Jun98 //TempCode MS 29Oct96 						 	Abs	{Y HeightSize}
//DeadCode JIM 26Jun98 //TempCode MS 29Oct96 							},
//DeadCode JIM 26Jun98 //TempCode MS 29Oct96 					Action	wpacnoactionno,
//DeadCode JIM 26Jun98 //TempCode MS 29Oct96 					Range	STANDARDTRIGGER
//DeadCode JIM 26Jun98 //TempCode MS 29Oct96 				},
//DeadCode JIM 26Jun98 				WayPoint
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Posn	{Abs	{FriendlyScoutHomeBase},	
//DeadCode JIM 26Jun98 						 	Abs	{Y FT_EnterLandingPattern}
//DeadCode JIM 26Jun98 							},
//DeadCode JIM 26Jun98 					Action	wpalandingno,
//DeadCode JIM 26Jun98 					Range	DistEnterLandingPattern
//DeadCode JIM 26Jun98 				}
//DeadCode JIM 26Jun98 			},
//DeadCode JIM 26Jun98 			NumInWing	6,
//DeadCode JIM 26Jun98 			NumInForm	6,
//DeadCode JIM 26Jun98 			Duty		DUTYCAP,
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 					Posn	{Abs	{CPP},
//DeadCode JIM 26Jun98 							 Abs	{Y	HeightSize},
//DeadCode JIM 26Jun98 							 Rel	{Intercept	{CPP,CWP},
//DeadCode JIM 26Jun98  									 Bearing	{Random	ANGLES_300Deg,2,ANGLES_120Deg},
//DeadCode JIM 26Jun98 									 Range	STANDARDTRIGGER
//DeadCode JIM 26Jun98 									}	
//DeadCode JIM 26Jun98 							},
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 		   	AirItem	
//DeadCode JIM 26Jun98 			{
//DeadCode JIM 26Jun98 				Side		NAT_FRIEND,
//DeadCode JIM 26Jun98 				Type		FriendlyScoutType00,
//DeadCode JIM 26Jun98 				Home		FriendlyScoutHomeBase,
//DeadCode JIM 26Jun98 				Squadron	{FriendlyScoutSquad,PS_5,PS_6,PS_7,PS_8},
//DeadCode JIM 26Jun98 				MoveCode	AUTO_FOLLOWWP,
//DeadCode JIM 26Jun98 				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
//DeadCode JIM 26Jun98 				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
//DeadCode JIM 26Jun98 				Morale		{Random	EnemyScoutMorale,40,1}
//DeadCode JIM 26Jun98 			}
//DeadCode JIM 26Jun98 		}
//DeadCode JIM 26Jun98 	};
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 //---------------------------------------------------------------------------
//DeadCode JIM 26Jun98 //SPECIALSPRINGS
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 	BattleField
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 	{
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 		FileName	BFSP_BOMBHQ=BFSPSO00.BF,
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 		GroundGroup	
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 		{
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 			Route		
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 			{
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				WayPoint	
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				{
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 					Posn	{Abs	{ROUTE_BOMBHQ_B},
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 							 Abs	{Y -FT_5}
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 							},
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 					Vel	5,
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 					Action	wpdmbtrknoactno
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				},
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				WayPoint	
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				{
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 					Posn	{Abs	{ROUTE_BOMBHQ_C},
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 							 Abs	{Y -FT_5}
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 							},
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 					Vel	50,
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 					Action	wpdmbtrknoactno
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				},
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				WayPoint	
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				{
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 					Posn	{Abs	{ROUTE_BOMBHQ_D},
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 							 Abs	{Y -FT_5}
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 							},
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 					Vel	50,
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 					Action	wpdmbtrknoactno
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				},
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				WayPoint	
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				{
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 					Posn	{Abs	{ROUTE_BOMBHQ_E},
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 							 Abs	{Y -FT_5}
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 							},
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 					Vel	50,
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 					Action	wpdmbtrknoactno
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				},
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				WayPoint	
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				{
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 					Posn	{Abs	{ROUTE_BOMBHQ_F},
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 							 Abs	{Y -FT_5}
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 							},
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 					Vel	50,
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 					Action	wpdmbtrknoactno
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				},
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				WayPoint	
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				{
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 					Posn	{Abs	{ROUTE_BOMBHQ_G},
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 							 Abs	{Y -FT_5}
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 							},
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 					Vel	50,
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 					Action	wpdmbtrknoactno
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				},
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				WayPoint	
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				{
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 					Posn	{Abs	{ROUTE_BOMBHQ_H},
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 							 Abs	{Y -FT_5}
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 							},
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 					Vel	50,
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 					Action	wpdmbtrknoactno
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				},
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				WayPoint	
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				{
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 					Posn	{Abs	{ROUTE_BOMBHQ_I},
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 							 Abs	{Y -FT_5}
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 							},
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 					Vel	50,
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 					Action	wpdmbtrknoactno
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				},
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				WayPoint	
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				{
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 					Posn	{Abs	{ROUTE_BOMBHQ_J},
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 							 Abs	{Y -FT_5}
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 							},
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 					Vel	50,
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 					Action	wpdmbtrkstopno
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				}
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 			},
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 			
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 			NumInForm	1,
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 			Formation	FORM_SINGLEFILE,
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 			Posn	{Abs	{ROUTE_BOMBHQ_A},
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 					 Abs	{Y -FT_5}
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 					},
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 		   	GroundItem	
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 			{
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				Type		SQ_ATruck,
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				Side		NAT_ENEMY,
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				Shape		STAFF,
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				Vel			5,
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				MoveCode	GROUND_TAXI
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 			}
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 		}
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 	};
//DeadCode JIM 26Jun98 //---------------------------------------------------------------------------
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 	BattleField
//DeadCode JIM 26Jun98 	{
//DeadCode JIM 26Jun98 		FileName	BFSP_SOATTROOPSVILLAGE=BFSPSO01.BF
//DeadCode JIM 26Jun98 //DeadCode MS 05Dec96 		GroundGroup	
//DeadCode JIM 26Jun98 //DeadCode MS 05Dec96 		{
//DeadCode JIM 26Jun98 //DeadCode MS 05Dec96 			Route		
//DeadCode JIM 26Jun98 //DeadCode MS 05Dec96 			{
//DeadCode JIM 26Jun98 //DeadCode MS 05Dec96 				WayPoint	
//DeadCode JIM 26Jun98 //DeadCode MS 05Dec96 				{
//DeadCode JIM 26Jun98 //DeadCode MS 05Dec96 					Posn	{Abs	{WP2},
//DeadCode JIM 26Jun98 //DeadCode MS 05Dec96 							 Abs	{Y -FT_1}
//DeadCode JIM 26Jun98 //DeadCode MS 05Dec96 							},
//DeadCode JIM 26Jun98 //DeadCode MS 05Dec96 					Action	wpdmbtrkstopno
//DeadCode JIM 26Jun98 //DeadCode MS 05Dec96 				}
//DeadCode JIM 26Jun98 //DeadCode MS 05Dec96 			},
//DeadCode JIM 26Jun98 //DeadCode MS 05Dec96 			
//DeadCode JIM 26Jun98 //DeadCode MS 05Dec96 			NumInForm	8,
//DeadCode JIM 26Jun98 //DeadCode MS 05Dec96 			Formation	FORM_SINGLEFILE,
//DeadCode JIM 26Jun98 //DeadCode MS 05Dec96 
//DeadCode JIM 26Jun98 //DeadCode MS 05Dec96 			Posn	{Abs	{WP1},
//DeadCode JIM 26Jun98 //DeadCode MS 05Dec96 					 Abs	{Y -FT_1}
//DeadCode JIM 26Jun98 //DeadCode MS 05Dec96 					},
//DeadCode JIM 26Jun98 //DeadCode MS 05Dec96 
//DeadCode JIM 26Jun98 //DeadCode MS 05Dec96 		   	GroundItem	BFSP_SOATTROOPSVILLAGE_ITEM00=
//DeadCode JIM 26Jun98 //DeadCode MS 05Dec96 			{
//DeadCode JIM 26Jun98 //DeadCode MS 05Dec96 				Type		SQ_ATruck,
//DeadCode JIM 26Jun98 //DeadCode MS 05Dec96 				Side		NAT_FRIEND,
//DeadCode JIM 26Jun98 //DeadCode MS 05Dec96 				Shape		TRUCK,
//DeadCode JIM 26Jun98 //DeadCode MS 05Dec96 				MoveCode	GROUND_TAXI
//DeadCode JIM 26Jun98 //DeadCode MS 05Dec96 			}
//DeadCode JIM 26Jun98 //DeadCode MS 05Dec96 		}
//DeadCode JIM 26Jun98 	};
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 //---------------------------------------------------------------------------
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 	BattleField
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 	{
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 		FileName	BFSP_SOPROTECTBRIDGE=BFSPSO02.BF,
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 //fixme Troops coming upto the bridge in a truck
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 		GroundGroup	
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 		{
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 			Route		
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 			{
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				WayPoint		
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				{
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 					Posn	{Abs {MainObjective},
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 							 Abs	{Y -FT_1}
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 							},
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 					Range	METRES200,
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 //fixme				Action	stop
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 					Event	BFCH_SOPROTECTBRIDGE
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				}
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 			},	
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 			NumInForm	1,
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 			Posn	{Abs	{MainObjective},
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 					 Abs	{Y -FT_1}
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 					},
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 		   	GroundItem	 BFSPSO02_Item00=		     	
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 			{
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				Type		SQ_ATruck,
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				Side		NAT_FRIEND,
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				Shape		TRUCK,
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				Vel			50,
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				MoveCode	GROUND_TAXI
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 			}
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 		},
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 //These are the flak guns on trucks
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 		GroundGroup	
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 		{
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 			Route		
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 			{
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				WayPoint		
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				{
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 					Posn	{Abs {MainObjective},
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 							 Abs	{Y -FT_1}
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 							},
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 					Range	METRES200
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 //fixme				Action	fanout
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				}
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 			},	
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 			NumInForm	1,
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 			Posn	{Abs	{MainObjective},
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 					 Abs	{Y -FT_1}
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 					},
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 		   	GroundItem	 
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 			{
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				Type		SQ_ATruck,
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				Side		NAT_FRIEND,
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				Shape		TRUCK,
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				Vel			50,
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				MoveCode	GROUND_TAXI
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 			}
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 		}
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 	};
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 //---------------------------------------------------------------------------
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 	BattleField
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 	{
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 		FileName	BFCH_SOPROTECTBRIDGE=BFCHSO02.BF,
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 //Troops pile out the truck, run across the bridge and waste the engineers
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 		GroundGroup	
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 		{
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 			Route		
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 			{
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				WayPoint		
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				{
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 					Posn	{Abs {MainObjective},
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 							 Abs	{Y -FT_1}
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 							}
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				}
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 			},	
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 			NumInForm	8,
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 			Posn	{Abs	BFSPSO02_Item00,
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 					 Abs	{Y -FT_1}
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 					},
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 		   	GroundItem	 		     	
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 			{
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				Type		SQ_ATruck,
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				Side		NAT_FRIEND,
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				Shape		TROOP1,
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				Vel			50,
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				MoveCode	GROUND_TAXI
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 			}
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 		}
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 	};
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 //---------------------------------------------------------------------------
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 //REDUNDANT
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 	BattleField
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 	{
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 		FileName	BFSP_SOBLOWBRIDGE=BFSPSO03.BF
//DeadCode JIM 26Jun98 //DeadCode MS 19Nov96 		GroundGroup	
//DeadCode JIM 26Jun98 //DeadCode MS 19Nov96 		{
//DeadCode JIM 26Jun98 //DeadCode MS 19Nov96 			Route		
//DeadCode JIM 26Jun98 //DeadCode MS 19Nov96 			{
//DeadCode JIM 26Jun98 //DeadCode MS 19Nov96 				WayPoint
//DeadCode JIM 26Jun98 //DeadCode MS 19Nov96 				{
//DeadCode JIM 26Jun98 //DeadCode MS 19Nov96 					Posn	{Abs	{MainObjective},
//DeadCode JIM 26Jun98 //DeadCode MS 19Nov96 					 		Abs	{Y -FT_1}
//DeadCode JIM 26Jun98 //DeadCode MS 19Nov96 							},
//DeadCode JIM 26Jun98 //DeadCode MS 19Nov96 					Action	wpdmbtrkstopno,
//DeadCode JIM 26Jun98 //DeadCode MS 19Nov96 					Range	MARGIN
//DeadCode JIM 26Jun98 //DeadCode MS 19Nov96 				}
//DeadCode JIM 26Jun98 //DeadCode MS 19Nov96 			},
//DeadCode JIM 26Jun98 //DeadCode MS 19Nov96 		
//DeadCode JIM 26Jun98 //DeadCode MS 19Nov96 			NumInForm	8,
//DeadCode JIM 26Jun98 //DeadCode MS 19Nov96 
//DeadCode JIM 26Jun98 //DeadCode MS 19Nov96 			Posn	{Abs	{MainObjective},
//DeadCode JIM 26Jun98 //DeadCode MS 19Nov96 					 Abs	{Y -FT_1},
//DeadCode JIM 26Jun98 //DeadCode MS 19Nov96 					 Rel	{Bearing	ANGLES_45Deg,
//DeadCode JIM 26Jun98 //DeadCode MS 19Nov96 							 Range	METRES2000
//DeadCode JIM 26Jun98 //DeadCode MS 19Nov96 							}
//DeadCode JIM 26Jun98 //DeadCode MS 19Nov96 					},
//DeadCode JIM 26Jun98 //DeadCode MS 19Nov96 
//DeadCode JIM 26Jun98 //DeadCode MS 19Nov96 		   	GroundItem	
//DeadCode JIM 26Jun98 //DeadCode MS 19Nov96 			{
//DeadCode JIM 26Jun98 //DeadCode MS 19Nov96 				Type		SQ_ATruck,
//DeadCode JIM 26Jun98 //DeadCode MS 19Nov96 				Side		NAT_ENEMY,
//DeadCode JIM 26Jun98 //DeadCode MS 19Nov96 				Shape		AAAG,
//DeadCode JIM 26Jun98 //DeadCode MS 19Nov96 				MoveCode	GROUND_TAXI
//DeadCode JIM 26Jun98 //DeadCode MS 19Nov96 			}
//DeadCode JIM 26Jun98 //DeadCode MS 19Nov96 		}
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 	};
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 //---------------------------------------------------------------------------
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 	BattleField
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 	{
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 		FileName	BFSP_SODAWNPATROL=BFSPSO04.BF
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 	};
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 //---------------------------------------------------------------------------
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 	BattleField
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 	{
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 		FileName	BFSP_SOPROTECTBOMBERS=BFSPSO05.BF,
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 		Setval	{GlobalSkillMin, EnemyChargeSkillMin},
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 		Setval	{GlobalSkillMax, EnemyChargeSkillMax},
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 		AirGroup	
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 		{
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 			Route	
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 			{
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				WayPoint	
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				{
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 					Target	SOPROTECTBOMBERS_Gun00,
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 					Posn	{Abs	{Y FT_BombStraffe}},
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 					Action	wpdivebombstraffeno,
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 					Range	BEGINBOMBSTRAFFERANGE
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				},
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				WayPoint	
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				{
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 					Target	SOPROTECTBOMBERS_Gun01,
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 					Posn	{Abs	{Y FT_BombStraffe}},
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 					Action	wpdivebombstraffeno,
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 					Range	BEGINBOMBSTRAFFERANGE
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				},
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				WayPoint	
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				{
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 					Posn	{Abs	{EnemyChargeHomeBase},
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 						 	Abs	{Y FT_EnterLandingPattern}
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 							},
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 					Action	wpalandingno,
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 					Range	DistEnterLandingPattern
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				}
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 			},
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 			NumInWing	4,
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 			NumInForm	4,
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 			Duty		DUTYBOMB,
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 			Posn		{Abs	{CPP}, 
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 						 Abs	{Y FT_BombStraffe},
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 						 Rel	{Intercept	{CPP,MainObjective},
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 								 Bearing	{Random	ANGLES_355Deg,10,ANGLES_1Deg},
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 								 Range	VISINEDGE	
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 								}
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 						},
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 		   	AirItem	
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 			{
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				Side		NAT_ENEMY,
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				Type		EnemyChargeType00,
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				Squadron	{EnemyChargeSquad},
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				Home		EnemyChargeHomeBase,
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				MoveCode	AUTO_FOLLOWWP,
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				Skill		{List {Random 6}, SKILL_VETERAN,SKILL_VETERAN,SKILL_REGULAR,SKILL_REGULAR,SKILL_REGULAR,SKILL_POOR},
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				Character	EnemyChargeCharacter,
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				Morale		{Random	EnemyChargeMorale,40,1},
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				Bombs		4
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 			}
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 		}
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 	};
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 //---------------------------------------------------------------------------
//DeadCode JIM 26Jun98 //NOW USED AS SPECIAL ACES. Konnecke and Rumey
//DeadCode JIM 26Jun98 	BattleField
//DeadCode JIM 26Jun98 	{
//DeadCode JIM 26Jun98 		FileName	BFSP_SOZONECALL=BFSPSO06.BF,
//DeadCode JIM 26Jun98 		Setval	{RandAngle,Bearing {Random ANGLES_240Deg,2,ANGLES_180Deg}},
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 Setval	{PaintScheme PS_1, PaintScheme {Select COL_ALL,COL_E2}},
//DeadCode JIM 26Jun98 Setval	{PaintScheme PS_2, PaintScheme {Select COL_TAIL,COL_E0}},
//DeadCode JIM 26Jun98 Setval	{PaintScheme PS_3, PaintScheme {Select COL_SIG,COL_E3}},
//DeadCode JIM 26Jun98 Setval	{PaintScheme PS_4, PaintScheme {Select COL_SIG,COL_E3}},
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 		AirGroup
//DeadCode JIM 26Jun98 		{
//DeadCode JIM 26Jun98 			Route
//DeadCode JIM 26Jun98 			{
//DeadCode JIM 26Jun98 				WayPoint	BFSP_SOZONECALL_WP00=	
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Target	CPP,
//DeadCode JIM 26Jun98 					Action	wpacnoactionno,
//DeadCode JIM 26Jun98 					Range	HALFVISINEDGE
//DeadCode JIM 26Jun98 				},
//DeadCode JIM 26Jun98 				WayPoint
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Posn	{Abs	{CWP}},	
//DeadCode JIM 26Jun98 					Action	wpacnoactionno,
//DeadCode JIM 26Jun98 					Range	MARGIN
//DeadCode JIM 26Jun98 				},
//DeadCode JIM 26Jun98 				WayPoint
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Posn	{Abs	{EnemyScoutHomeBase},	
//DeadCode JIM 26Jun98 						 	Abs	{Y FT_EnterLandingPattern}
//DeadCode JIM 26Jun98 							},
//DeadCode JIM 26Jun98 					Action	wpalandingno,
//DeadCode JIM 26Jun98 					Range	DistEnterLandingPattern
//DeadCode JIM 26Jun98 				}
//DeadCode JIM 26Jun98 			},
//DeadCode JIM 26Jun98 			NumInWing	1,
//DeadCode JIM 26Jun98 			NumInForm	1,
//DeadCode JIM 26Jun98 			Duty		DUTYCAP,
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 			Posn		{Abs	{CPP},
//DeadCode JIM 26Jun98 						 Rel	{Intercept	{CPP,CWP},
//DeadCode JIM 26Jun98 								 Bearing	{Random	RandAngle,60,ANGLES_1Deg},
//DeadCode JIM 26Jun98 								 Pitch		{Random	ANGLES_0Deg,20,ANGLES_1Deg},
//DeadCode JIM 26Jun98 							 	 Range	VISINEDGE
//DeadCode JIM 26Jun98 								}
//DeadCode JIM 26Jun98 						},
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 		   	AirItem	BFSP_SOZONECALL_Item00 =
//DeadCode JIM 26Jun98 			{
//DeadCode JIM 26Jun98 				Side		NAT_ENEMY,
//DeadCode JIM 26Jun98 				Type		SQ_MIG15,
//DeadCode JIM 26Jun98 				Squadron 	{OttoKonnecke,PS_1,PS_2,PS_3,PS_4},
//DeadCode JIM 26Jun98 				Home		UID_NODE_sinuiju,
//DeadCode JIM 26Jun98 				MoveCode	AUTO_FOLLOWWP,
//DeadCode JIM 26Jun98 				Skill		SKILL_HERO,
//DeadCode JIM 26Jun98 				Character	CHAR_CAVALIER,
//DeadCode JIM 26Jun98 				Morale		255
//DeadCode JIM 26Jun98 			}
//DeadCode JIM 26Jun98 		},
//DeadCode JIM 26Jun98 //DeadCode MS 28Nov96 Setval	{PaintScheme PS_1, PaintScheme {Select COL_ALL,COL_E2}},
//DeadCode JIM 26Jun98 //DeadCode MS 28Nov96 Setval	{PaintScheme PS_2, PaintScheme {Select COL_ALL,COL_E2}},
//DeadCode JIM 26Jun98 //DeadCode MS 28Nov96 Setval	{PaintScheme PS_3, PaintScheme {Select COL_ALL,COL_E2}},
//DeadCode JIM 26Jun98 //DeadCode MS 28Nov96 Setval	{PaintScheme PS_4, PaintScheme {Select COL_TAIL,COL_E0}},
//DeadCode JIM 26Jun98 //DeadCode MS 28Nov96 		AirGroup
//DeadCode JIM 26Jun98 //DeadCode MS 28Nov96 		{
//DeadCode JIM 26Jun98 //DeadCode MS 28Nov96 			Route	BFSP_SOZONECALL_WP00,
//DeadCode JIM 26Jun98 //DeadCode MS 28Nov96 			NumInWing	1,
//DeadCode JIM 26Jun98 //DeadCode MS 28Nov96 			NumInForm	1,
//DeadCode JIM 26Jun98 //DeadCode MS 28Nov96 			Duty		DUTYCAP,
//DeadCode JIM 26Jun98 //DeadCode MS 28Nov96 
//DeadCode JIM 26Jun98 //DeadCode MS 28Nov96 			Posn		{Abs	BFSP_SOZONECALL_Item00},
//DeadCode JIM 26Jun98 //DeadCode MS 28Nov96 
//DeadCode JIM 26Jun98 //DeadCode MS 28Nov96 		   	AirItem	
//DeadCode JIM 26Jun98 //DeadCode MS 28Nov96 			{
//DeadCode JIM 26Jun98 //DeadCode MS 28Nov96 				Side		NAT_ENEMY,
//DeadCode JIM 26Jun98 //DeadCode MS 28Nov96 				Type		SQ_MIG15,
//DeadCode JIM 26Jun98 //DeadCode MS 28Nov96 				Squadron 	{FritzRumey,PS_1,PS_2,PS_3,PS_4},
//DeadCode JIM 26Jun98 //DeadCode MS 28Nov96 				Home		UID_NODE_sinuiju,
//DeadCode JIM 26Jun98 //DeadCode MS 28Nov96 				MoveCode	AUTO_FOLLOWWP,
//DeadCode JIM 26Jun98 //DeadCode MS 28Nov96 				Skill		SKILL_HERO,
//DeadCode JIM 26Jun98 //DeadCode MS 28Nov96 				Character	CHAR_CAVALIER,
//DeadCode JIM 26Jun98 //DeadCode MS 28Nov96 				Morale		255,
//DeadCode JIM 26Jun98 //DeadCode MS 28Nov96 				Leader		BFSP_SOZONECALL_Item00	
//DeadCode JIM 26Jun98 //DeadCode MS 28Nov96 			}
//DeadCode JIM 26Jun98 //DeadCode MS 28Nov96 		},
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 Setval	{PaintScheme PS_1, PaintScheme {Select COL_ALL,COL_E5}},//AM 02Dec96
//DeadCode JIM 26Jun98 Setval	{PaintScheme PS_2, PaintScheme {Select COL_BOD,COL_E2}},//AM 02Dec96
//DeadCode JIM 26Jun98 Setval	{PaintScheme PS_3, PaintScheme {Select COL_ELEV,COL_E2}},//AM 02Dec96
//DeadCode JIM 26Jun98 Setval	{PaintScheme PS_4, PaintScheme {Select COL_WBOT,COL_VARY}},//AM 02Dec96
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 		AirGroup
//DeadCode JIM 26Jun98 		{
//DeadCode JIM 26Jun98 			Route	BFSP_SOZONECALL_WP00,
//DeadCode JIM 26Jun98 			NumInWing	3,
//DeadCode JIM 26Jun98 			NumInForm	3,
//DeadCode JIM 26Jun98 			Duty		DUTYCAP,
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 			Posn		{Abs	BFSP_SOZONECALL_Item00},
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 		   	AirItem
//DeadCode JIM 26Jun98 			{
//DeadCode JIM 26Jun98 				Side		NAT_ENEMY,
//DeadCode JIM 26Jun98 				Type		EnemyScoutType00,
//DeadCode JIM 26Jun98 				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
//DeadCode JIM 26Jun98 				Home		EnemyScoutHomeBase,
//DeadCode JIM 26Jun98 				MoveCode	AUTO_FOLLOWWP,
//DeadCode JIM 26Jun98 				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
//DeadCode JIM 26Jun98 				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
//DeadCode JIM 26Jun98 				Morale		{Random	EnemyScoutMorale,40,1},
//DeadCode JIM 26Jun98 				Leader		BFSP_SOZONECALL_Item00	
//DeadCode JIM 26Jun98 			}
//DeadCode JIM 26Jun98 		}
//DeadCode JIM 26Jun98 	};
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 //---------------------------------------------------------------------------
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 	BattleField
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 	{
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 		FileName	BFSP_SOBOMBRAILHEAD00=BFSPSO07.BF,
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 		Setval	{GlobalSkillMax, EnemyChargeSkillMax},
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 		GroundGroup	
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 		{
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 			Route		
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 			{
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				WayPoint		
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				{
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 					Posn	{Abs {MainObjective},
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 							 Abs	{Y -FT_1}
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 							},
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 					Range	METRES200,
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 					Action	wpacnoactionno
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				}
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 			},	
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 //fixme make me a train
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 			NumInForm	1,
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 			Posn	{Abs	{MainObjective},
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 					 Abs	{Y -FT_1}
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 					},
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 		   	GroundItem	 
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 			{
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				Type		SQ_ATruck,
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				Side		NAT_FRIEND,
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				Shape		TRUCK,
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				Vel			50,
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				MoveCode	GROUND_TAXI
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 			}
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 		}
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 	};									   
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 //---------------------------------------------------------------------------
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 	BattleField
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 	{
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 		FileName	BFSP_SOBOMBRAILHEAD01=BFSPSO08.BF,
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 		GroundGroup	
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 		{
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 			Route		
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 			{
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				WayPoint		
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				{
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 					Posn	{Abs {MainObjective},
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 							 Abs	{Y -FT_1}
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 							},
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 					Range	METRES200,
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 					Action	wpacnoactionno
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				}
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 			},	
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 			NumInForm	1,
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 			Posn	{Abs	{MainObjective},
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 					 Abs	{Y -FT_1}
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 					},
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 		   	GroundItem	 
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 			{
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				Type		SQ_ATruck,
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				Side		NAT_FRIEND,
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				Shape		TRUCK,
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				Vel			50,
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 				MoveCode	GROUND_TAXI
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 			}
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 		}
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 	};
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 //---------------------------------------------------------------------------
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 //NOW USED AS A DUMMY CHAIN
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 	BattleField
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 	{
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 		FileName	BFSP_SOWIRELESSWORK=BFSPSO09.BF
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 	};
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 //---------------------------------------------------------------------------
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 	BattleField
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 	{
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 		FileName	BFSP_SOKILLRICHTHOFEN00=BFSPSO10.BF
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 	};
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 //---------------------------------------------------------------------------
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 	BattleField
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 	{
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 		FileName	BFSP_SOKILLRICHTHOFEN01=BFSPSO11.BF
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 	};
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 //---------------------------------------------------------------------------
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 	BattleField
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 	{
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 		FileName	BFSP_SOTANKVSTANK=BFSPSO12.BF
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 	};
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 //---------------------------------------------------------------------------
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 	BattleField
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 	{
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 		FileName	BFSP_SOATTTROOPSWOODS=BFSPSO13.BF
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 	};
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 
//DeadCode JIM 26Jun98 //DeadCode MS 03Dec96 //---------------------------------------------------------------------------
//DeadCode JIM 26Jun98 //(findme)
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 //---------------------------------------------------------------------------
//DeadCode JIM 26Jun98 //KILL RICHTHOFEN
//DeadCode JIM 26Jun98 	BattleField
//DeadCode JIM 26Jun98 	{
//DeadCode JIM 26Jun98 		FileName	BFSP_SPECIAL00=BFSPEC00.BF,
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 Setval	{PaintScheme PS_1, PaintScheme {Select COL_ALL,COL_E1}},
//DeadCode JIM 26Jun98 Setval	{PaintScheme PS_2, PaintScheme {Select COL_ALL,COL_E1}},
//DeadCode JIM 26Jun98 Setval	{PaintScheme PS_3, PaintScheme {Select COL_ALL,COL_E1}},
//DeadCode JIM 26Jun98 Setval	{PaintScheme PS_4, PaintScheme {Select COL_SIG,COL_E0}},
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 		AirGroup
//DeadCode JIM 26Jun98 		{
//DeadCode JIM 26Jun98 			Route
//DeadCode JIM 26Jun98 			{
//DeadCode JIM 26Jun98 				WayPoint	BFSP_SPECIAL00_WP00=	
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Target	CPP,
//DeadCode JIM 26Jun98 					Action	wpacnoactionno,
//DeadCode JIM 26Jun98 					Range	HALFVISINEDGE
//DeadCode JIM 26Jun98 				},
//DeadCode JIM 26Jun98 				WayPoint
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Posn	{Abs	{CWP}},	
//DeadCode JIM 26Jun98 					Action	wpacnoactionno,
//DeadCode JIM 26Jun98 					Range	MARGIN
//DeadCode JIM 26Jun98 				},
//DeadCode JIM 26Jun98 				WayPoint
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Posn	{Abs	{EnemyScoutHomeBase},	
//DeadCode JIM 26Jun98 						 	Abs	{Y FT_EnterLandingPattern}
//DeadCode JIM 26Jun98 							},
//DeadCode JIM 26Jun98 					Action	wpalandingno,
//DeadCode JIM 26Jun98 					Range	DistEnterLandingPattern
//DeadCode JIM 26Jun98 				}
//DeadCode JIM 26Jun98 			},
//DeadCode JIM 26Jun98 			NumInWing	1,
//DeadCode JIM 26Jun98 			NumInForm	1,
//DeadCode JIM 26Jun98 			Duty		DUTYCAP,
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 			Posn		{Abs	{CPP},
//DeadCode JIM 26Jun98 						 Abs	{Y {Select CloudBase,2,FT_1000}},
//DeadCode JIM 26Jun98 						 Rel	{Intercept	{CPP,CWP},
//DeadCode JIM 26Jun98 								 Bearing	{Random	ANGLES_315Deg,90,ANGLES_1Deg},
//DeadCode JIM 26Jun98 							 	 Range	HALFVISINEDGE
//DeadCode JIM 26Jun98 								}
//DeadCode JIM 26Jun98 						},
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 		   	AirItem	BFSP_SPECIAL00_Item00 =
//DeadCode JIM 26Jun98 			{
//DeadCode JIM 26Jun98 				Side		NAT_ENEMY,
//DeadCode JIM 26Jun98 				Type		SQ_MIG15,
//DeadCode JIM 26Jun98 				Squadron 	{Jasta11Ace,PS_1,PS_2,PS_3,PS_4},
//DeadCode JIM 26Jun98 				Home		UID_NODE_AnTung,
//DeadCode JIM 26Jun98 				MoveCode	AUTO_FOLLOWWP,
//DeadCode JIM 26Jun98 				Skill		SKILL_HERO,
//DeadCode JIM 26Jun98 				Character	CHAR_TACTICIAN,
//DeadCode JIM 26Jun98 				Morale		255
//DeadCode JIM 26Jun98 			}
//DeadCode JIM 26Jun98 		},
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 Setval	{PaintScheme PS_1, PaintScheme {Select COL_ALL,COL_E1}},//AM 02Dec96
//DeadCode JIM 26Jun98 Setval	{PaintScheme PS_2, PaintScheme {Select COL_SIG,COL_E0}},//AM 02Dec96
//DeadCode JIM 26Jun98 Setval	{PaintScheme PS_3, PaintScheme {Select COL_WBOT,COL_VARY}},//AM 02Dec96
//DeadCode JIM 26Jun98 Setval	{PaintScheme PS_4, PaintScheme {Select COL_ELEV,COL_VARY}},//AM 02Dec96
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 		AirGroup
//DeadCode JIM 26Jun98 		{
//DeadCode JIM 26Jun98 			Route	BFSP_SPECIAL00_WP00,
//DeadCode JIM 26Jun98 			NumInWing	4,
//DeadCode JIM 26Jun98 			NumInForm	4,
//DeadCode JIM 26Jun98 			Duty		DUTYCAP,
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 			Posn		{Abs	BFSP_SPECIAL00_Item00},
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 		   	AirItem
//DeadCode JIM 26Jun98 			{
//DeadCode JIM 26Jun98 				Side		NAT_ENEMY,
//DeadCode JIM 26Jun98 				Type		EnemyScoutType00,
//DeadCode JIM 26Jun98 				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
//DeadCode JIM 26Jun98 				Home		EnemyScoutHomeBase,
//DeadCode JIM 26Jun98 				MoveCode	AUTO_FOLLOWWP,
//DeadCode JIM 26Jun98 				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
//DeadCode JIM 26Jun98 				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
//DeadCode JIM 26Jun98 				Morale		{Random	EnemyScoutMorale,40,1},
//DeadCode JIM 26Jun98 				Leader		BFSP_SPECIAL00_Item00	
//DeadCode JIM 26Jun98 			}
//DeadCode JIM 26Jun98 		}
//DeadCode JIM 26Jun98 	};
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 //---------------------------------------------------------------------------
//DeadCode JIM 26Jun98 	BattleField
//DeadCode JIM 26Jun98 	{
//DeadCode JIM 26Jun98 		FileName	BFSP_SPECIAL01=BFSPEC01.BF,
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 Setval	{PaintScheme PS_1, PaintScheme {Select COL_ALL,COL_E1}},
//DeadCode JIM 26Jun98 Setval	{PaintScheme PS_2, PaintScheme {Select COL_TAIL_ELEV,COL_E3}},
//DeadCode JIM 26Jun98 Setval	{PaintScheme PS_3, PaintScheme {Select COL_BOD,COL_E7}},
//DeadCode JIM 26Jun98 Setval	{PaintScheme PS_4, PaintScheme {Select COL_SIG,COL_E0}},
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 		AirGroup
//DeadCode JIM 26Jun98 		{
//DeadCode JIM 26Jun98 			Route
//DeadCode JIM 26Jun98 			{
//DeadCode JIM 26Jun98 				WayPoint	BFSP_SPECIAL01_WP00=	
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Target	CPP,
//DeadCode JIM 26Jun98 					Action	wpacnoactionno,
//DeadCode JIM 26Jun98 					Range	HALFVISINEDGE
//DeadCode JIM 26Jun98 				},
//DeadCode JIM 26Jun98 				WayPoint
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Posn	{Abs	{CWP}},	
//DeadCode JIM 26Jun98 					Action	wpacnoactionno,
//DeadCode JIM 26Jun98 					Range	MARGIN
//DeadCode JIM 26Jun98 				},
//DeadCode JIM 26Jun98 				WayPoint
//DeadCode JIM 26Jun98 				{
//DeadCode JIM 26Jun98 					Posn	{Abs	{EnemyScoutHomeBase},	
//DeadCode JIM 26Jun98 						 	Abs	{Y FT_EnterLandingPattern}
//DeadCode JIM 26Jun98 							},
//DeadCode JIM 26Jun98 					Action	wpalandingno,
//DeadCode JIM 26Jun98 					Range	DistEnterLandingPattern
//DeadCode JIM 26Jun98 				}
//DeadCode JIM 26Jun98 			},
//DeadCode JIM 26Jun98 			NumInWing	1,
//DeadCode JIM 26Jun98 			NumInForm	1,
//DeadCode JIM 26Jun98 			Duty		DUTYCAP,
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 			Posn		{Abs	{CPP},
//DeadCode JIM 26Jun98 						 Rel	{Y FT_2000,
//DeadCode JIM 26Jun98 								 Intercept	{CPP,CWP},
//DeadCode JIM 26Jun98 								 Bearing	{Random	ANGLES_270Deg,180,ANGLES_1Deg},
//DeadCode JIM 26Jun98 							 	 Range	VISINEDGE
//DeadCode JIM 26Jun98 								}
//DeadCode JIM 26Jun98 						},
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 		   	AirItem	BFSP_SPECIAL01_Item00 =
//DeadCode JIM 26Jun98 			{
//DeadCode JIM 26Jun98 				Side		NAT_ENEMY,
//DeadCode JIM 26Jun98 				Type		SQ_MIG15,
//DeadCode JIM 26Jun98 				Squadron 	{AnotherSquadAce,PS_1,PS_2,PS_3,PS_4},
//DeadCode JIM 26Jun98 				Home		UID_NODE_sinuiju,
//DeadCode JIM 26Jun98 				MoveCode	AUTO_FOLLOWWP,
//DeadCode JIM 26Jun98 				Skill		SKILL_HERO,
//DeadCode JIM 26Jun98 				Character	CHAR_TACTICIAN,
//DeadCode JIM 26Jun98 				Morale		255
//DeadCode JIM 26Jun98 			}
//DeadCode JIM 26Jun98 		},
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 Setval	{PaintScheme PS_1, PaintScheme {Select COL_ALL,COL_E1}},
//DeadCode JIM 26Jun98 Setval	{PaintScheme PS_2, PaintScheme {Select COL_WTOP_TAIL,COL_E0}},
//DeadCode JIM 26Jun98 Setval	{PaintScheme PS_3, PaintScheme {Select COL_WBOT,COL_E4}},
//DeadCode JIM 26Jun98 Setval	{PaintScheme PS_4, PaintScheme {Select COL_TAIL_ELEV,COL_VARY}},
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 		AirGroup
//DeadCode JIM 26Jun98 		{
//DeadCode JIM 26Jun98 			Route	BFSP_SPECIAL01_WP00,
//DeadCode JIM 26Jun98 			NumInWing	4,
//DeadCode JIM 26Jun98 			NumInForm	4,
//DeadCode JIM 26Jun98 			Duty		DUTYCAP,
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 			Posn		{Abs	BFSP_SPECIAL01_Item00},
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 		   	AirItem
//DeadCode JIM 26Jun98 			{
//DeadCode JIM 26Jun98 				Side		NAT_ENEMY,
//DeadCode JIM 26Jun98 				Type		EnemyScoutType00,
//DeadCode JIM 26Jun98 				Squadron 	{EnemyScoutSquad,PS_1,PS_2,PS_3,PS_4},
//DeadCode JIM 26Jun98 				Home		EnemyScoutHomeBase,
//DeadCode JIM 26Jun98 				MoveCode	AUTO_FOLLOWWP,
//DeadCode JIM 26Jun98 				Skill		{List SKILL_HERO,SKILL_REGULAR,SKILL_ACE,SKILL_REGULAR,SKILL_POOR,SKILL_VETERAN},
//DeadCode JIM 26Jun98 				Character	{Select {List {Random 3}, EnemyScoutTactician,EnemyScoutMrAverage,EnemyScoutCavalier}},
//DeadCode JIM 26Jun98 				Morale		{Random	EnemyScoutMorale,40,1},
//DeadCode JIM 26Jun98 				Leader		BFSP_SPECIAL01_Item00	
//DeadCode JIM 26Jun98 			}
//DeadCode JIM 26Jun98 		}
//DeadCode JIM 26Jun98 	};
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 //---------------------------------------------------------------------------
//DeadCode JIM 26Jun98 	BattleField
//DeadCode JIM 26Jun98 	{
//DeadCode JIM 26Jun98 		FileName	BFSP_SPECIAL02=BFSPEC02.BF
//DeadCode JIM 26Jun98 	};
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 //---------------------------------------------------------------------------
//DeadCode JIM 26Jun98 	BattleField
//DeadCode JIM 26Jun98 	{
//DeadCode JIM 26Jun98 		FileName	BFSP_SPECIAL03=BFSPEC03.BF
//DeadCode JIM 26Jun98 	};
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 //---------------------------------------------------------------------------
//DeadCode JIM 26Jun98 	BattleField
//DeadCode JIM 26Jun98 	{
//DeadCode JIM 26Jun98 		FileName	BFSP_SPECIAL04=BFSPEC04.BF
//DeadCode JIM 26Jun98 	};
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 //---------------------------------------------------------------------------
//DeadCode JIM 26Jun98 	BattleField
//DeadCode JIM 26Jun98 	{
//DeadCode JIM 26Jun98 		FileName	BFSP_SPECIAL05=BFSPEC05.BF
//DeadCode JIM 26Jun98 	};
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 //---------------------------------------------------------------------------
//DeadCode JIM 26Jun98 	BattleField
//DeadCode JIM 26Jun98 	{
//DeadCode JIM 26Jun98 		FileName	BFSP_SPECIAL06=BFSPEC06.BF
//DeadCode JIM 26Jun98 	};
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 
//DeadCode JIM 26Jun98 
