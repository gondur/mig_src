//------------------------------------------------------------------------------
//Filename       scramble.inc
//System         
//Author         R. Hyde 
//Date           Sun 25 Aug 1996
//Description    
//------------------------------------------------------------------------------

//--------------------------------
	Aircraft	OneOnOneBrit00;	
	Aircraft	OneOnOneBrit01;	
	BattleField
	{
		FileName	FIL_OneOnOneBrit=SCRM04AL.BF,
		Setval	{FriendHomeBase, UID_AfRdSinuiju},
		Setval	{EnemyScoutHomeBase, UID_AfRdSinuiju},
		AirGroup
		{
			Route	
			{
				WayPoint	OneOnOneBritAL_WP00=
				{
					Posn	
						{Abs	{FriendHomeBase}, 
						 Rel	{Y Scram_G1_Alt,X FT_1000}
						},
					Action	wpacnoactionno
				}
 			},
			
  			NumInWing	2,
  			NumInForm	1,	//Scram_G1_AC,
  			DUTYMIGCAP,

  			Posn	{Abs	EnemyScoutHomeBase, 
  					 Rel	{Y Scram_G1_Alt,X -FT_1000}
					},	
			AirItem	  OneOnOneBrit00=   	
			{
  				SetUID	UID_OneOnOneBrit00,
				Scram_G1_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RED,
  				Scram_G1_Skill,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER,
				Target	OneOnOneBrit01
  
  			}
 		},
		AirGroup
		{
			Route	
			{
				WayPoint	OneOnOneBritAL_WP01 =
				{
					Posn	
						{Abs	{EnemyScoutHomeBase}, 
						 Rel	{Y Scram_G0_Alt,Z FT_1000}
						},
					Action	wpacnoactionno
				}
 			},

			NumInWing	2,
  			NumInForm	1,	//Scram_G0_AC,

			DUTYMIGCAP,
  			Posn	{Abs	FriendHomeBase, 
  					 Rel	{Y Scram_G0_Alt,Z -FT_1000}
					},	

		   AirItem	OneOnOneBrit01 =
			{
  				SetUID	UID_OneOnOneBrit01,
				Home		FriendHomeBase,
				Scram_G0_Squad,
				NAT_BLUE,
  				Scram_G0_Skill,
				MORALE_HIGH,
				CHAR_CAVALIER,
				Attacker	OneOnOneBrit00
			}
		}



	};

//--------------------------------
//UN Fighter Bomber Strike 00

	BattleField
	{
		FileName	FIL_QUICKMISSION_00=QUICKM00.BF,

	 	Setval	{RandAngle, Bearing {Random ANGLES_90Deg,135,ANGLES_1Deg}},

		AirGroup	//group 00 - advance flak suppression
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target}, 
						 Abs	{Y Scram_G0_Alt}
						},
					Range	METRES5000,
					Action	wpacnoactionno	//FIXME BEGINFLAKSUPPRESSION
				},
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target}, 
						 Abs	{Y Scram_G0_Alt}
						},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	Pack_Sq0_Home, 
						 Abs	{Y Scram_G0_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				}
 			},
			
  			NumInWing	2,
  			NumInForm	Scram_G0_AC,
			Formation	SQUAD_FLATV,

			Duty	DC_WW,

  			Posn	{Abs	Pack_Target, 
  					 Abs	{Y Scram_G0_Alt},
  					 Rel	{Bearing	RandAngle,
							 Range	METRES5000
							}
					},	
			AirItem	  
			{
				Scram_G0_Squad,
				Home	Pack_Sq0_Home,
  				NAT_BLUE,
  				Scram_G0_Skill,
				MORALE_HIGH,
				Bombs Weap_RockFuel
  			}
 		},

		AirGroup	//group 1 - UN FB strike
		{
			Route	quick_00_G1_route =	
			{
				WayPoint	
				{
					Target	Pack_Target,	
					Posn	{
						 	 Abs	{Y Scram_G1_Alt}
							},
 					Range	METRES7000,
					Action	wpbombno	
				},
				WayPoint	
				{
					Target	Pack_Target,	
					Posn	{
						 	 Abs	{Y Scram_G1_Alt}
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	Pack_Sq0_Home, 
						 Abs	{Y Scram_G1_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				}
 			},

			NumInWing	2,
  			NumInForm	Scram_G1_AC,
			Formation	SQUAD_FLATV_Right,

			DUTY_DiveIndividual,

  			Posn	{Abs	Pack_Target, 
  					 Abs	{Y Scram_G1_Alt},
  					 Rel	{Bearing	RandAngle,
						 	 Range	KM10
							}
					},	

		   AirItem	quick_00_G1_aircraft =
			{
				Scram_G1_Squad,
				Home	Pack_Sq0_Home,
				NAT_BLUE,
  				Scram_G1_Skill,
				Morale	MORALE_HIGH,
				Bombs Weap_BombFuel,
				Target	Pack_Target
			}
		},

		AirGroup	//group 2 - UN close escort
		{
			Route	quick_00_G1_route,

			NumInWing	2,
  			NumInForm	Scram_G2_AC,
			Formation	SQUAD_FLATV_Right,

			DUTYESCORT,

  			Posn	{Abs	quick_00_G1_aircraft, 
  					 Abs	{Y Scram_G2_Alt},
  					 Rel	{Bearing	{Select RandAngle,1,ANGLES_270Deg},
						 	 Range	METRES1000
							}
					},	

		   AirItem	
			{
				Scram_G2_Squad,
				Home	Pack_Sq0_Home,
				NAT_BLUE,
  				Scram_G2_Skill,
				MORALE_HIGH,
				Leader	0,
				Attitude	{
							 Heading	{Select RandAngle,1,ANGLES_180Deg},
							 Pitch ANGLES_0Deg
							}
			}
		},

		AirGroup	//group 3 - MiG intercepters
		{
			Route	
			{
				WayPoint		
				{
					Posn	
						{Abs	quick_00_G1_aircraft, 
						 Abs	{Y Scram_G3_Alt}
						},
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	
						{Abs	UID_AfRdAntung, 
						 Abs	{Y Scram_G3_Alt}
						},
 					Range	METRES4000,
					Action	wpalandingno
				}
 			},

			NumInWing	16,	
  			NumInForm	Scram_G3_AC,
			Formation	SQUAD_CH_ABREAST,
			DUTYMIGCAP,

  			Posn	{Abs	quick_00_G1_aircraft, 
  					 Abs	{Y Scram_G3_Alt},
  					 Rel	{Intercept	{Pack_Target,quick_00_G1_aircraft},
							 Bearing	{Random ANGLES_90Deg,180,ANGLES_1Deg},
							 Range		{Random	METRES8000,5,METRES1000}
							}
					},	

		   AirItem	
			{
				Home		UID_AfRdAntung,
				Scram_G3_Squad,
				NAT_RED,
  				Scram_G3_Skill,
				Morale MORALE_HIGH
				
			}
		},

		AirGroup	//group 4 - MORE MiG intercepters
		{
			Route	
			{
				WayPoint		
				{
					Posn	
						{Abs	{Pack_Target}, 
						 Abs	{Y Scram_G4_Alt}
						},
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	
						{Abs	UID_AfRdAntung, 
						 Abs	{Y Scram_G4_Alt}
						},
 					Range	METRES4000,
					Action	wpalandingno
				}
 			},

			NumInWing	16,
  			NumInForm	Scram_G4_AC,
			Formation	SQUAD_ECHELONRIGHT,

			DUTYMIGCAP,

  			Posn	{Abs	{Pack_Target}, 
  					 Abs	{Y Scram_G4_Alt},
  					 Rel	{Intercept	{Pack_Target,quick_00_G1_aircraft},
  					 		 Bearing	{Random ANGLES_45Deg,270,ANGLES_1Deg},
							 Range		{Random	METRES8000,9,METRES1000}
							}
					},	

		   AirItem	
			{
				Home		UID_AfRdAntung,
				Scram_G4_Squad,
				NAT_RED,
  				Scram_G4_Skill,
				Morale MORALE_HIGH
				
			}
		}

	};


//--------------------------------
//UN Medium Bomber Strike 00

	BattleField
	{
		FileName	FIL_QUICKMISSION_01=QUICKM01.BF,

	 	Setval	{RandAngle, Bearing {Random ANGLES_90Deg,135,ANGLES_1Deg}},

		AirGroup	//group 00 - advance flak suppression
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target}, 
						 Abs	{Y Scram_G0_Alt}
						},
					Range	METRES5000,
					Action	wpacnoactionno	//FIXME BEGINFLAKSUPPRESSION
				},
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target}, 
						 Abs	{Y Scram_G0_Alt}
						},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	UID_AfBlKimpo, 
						 Abs	{Y Scram_G0_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				}
 			},
			
  			NumInWing	2,
  			NumInForm	Scram_G0_AC,
			Formation	SQUAD_FLATV,

			Duty	DC_WW,

  			Posn	{Abs	Pack_Target, 
  					 Abs	{Y Scram_G0_Alt},
  					 Rel	{Bearing	RandAngle,
							 Range	METRES5000
							}
					},	
			AirItem	  
			{
				Scram_G0_Squad,
				Home	UID_AfBlKimpo,
  				NAT_BLUE,
  				Scram_G0_Skill,
				MORALE_HIGH,
				Bombs Weap_RockFuel
  			}
 		},

		AirGroup	//group 1 - UN MB strike
		{
			Route	quick_01_G1_route =	
			{
				WayPoint	
				{
					Target	Pack_Target,	
					Posn	{
						 	 Abs	{Y Scram_G1_Alt}
							},
 					Range	KM10,
					Action	wpbombno	
				},
				WayPoint	
				{
					Target	Pack_Target,	
					Posn	{
						 	 Abs	{Y Scram_G1_Alt}
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	UID_Japan, 
						 Abs	{Y Scram_G1_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				}
 			},

			NumInWing	2,
  			NumInForm	Scram_G1_AC,
//DeadCode MS 24May99 			Formation	SQUAD_LINEABREAST_Right,
			Formation	SQUAD_FLATV,

			DA_LEVEL,

  			Posn	{Abs	Pack_Target, 
  					 Abs	{Y Scram_G1_Alt},
  					 Rel	{Bearing	RandAngle,
						 	 Range	KM10
							}
					},	

		   AirItem	quick_01_G1_aircraft =
			{
				Scram_G1_Squad,
				Home	UID_Japan,
				NAT_BLUE,
  				Scram_G1_Skill,
				Morale	MORALE_HIGH,
				Bombs	0
			}
		},

		AirGroup	//group 2 - UN close escort
		{
			Route	quick_01_G1_route,

			NumInWing	2,
  			NumInForm	Scram_G2_AC,
			Formation	SQUAD_FLATV_Right,

			DUTYESCORT,

  			Posn	{Abs	quick_01_G1_aircraft, 
  					 Abs	{Y Scram_G2_Alt},
  					 Rel	{Bearing	{Select RandAngle,1,ANGLES_315Deg},
						 	 Range	METRES4000
							}
					},	

		   AirItem	
			{
				Scram_G2_Squad,
				Home	UID_AfBlKimpo,
				NAT_BLUE,
  				Scram_G2_Skill,
				MORALE_HIGH,
				Leader	0,
				Attitude	{
							 Heading	{Select RandAngle,1,ANGLES_180Deg},
							 Pitch ANGLES_0Deg
							}
			}
		},

		AirGroup	//group 3 - MiG intercepters
		{
			Route	
			{
				WayPoint		
				{
					Posn	
						{Abs	quick_01_G1_aircraft, 
						 Abs	{Y Scram_G3_Alt}
						},
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	
						{Abs	UID_AfRdAntung, 
						 Abs	{Y Scram_G3_Alt}
						},
 					Range	METRES4000,
					Action	wpalandingno
				}
 			},

			NumInWing	16,	
  			NumInForm	Scram_G3_AC,
			Formation	SQUAD_CH_ABREAST,
			DUTYMIGCAP,

  			Posn	{Abs	quick_01_G1_aircraft, 
  					 Abs	{Y Scram_G3_Alt},
  					 Rel	{Intercept	{Pack_Target,quick_01_G1_aircraft},
							 Bearing	{Random ANGLES_90Deg,180,ANGLES_1Deg},
							 Range		{Random	METRES8000,5,METRES1000}
							}
					},	

		   AirItem	
			{
				Home		UID_AfRdAntung,
				Scram_G3_Squad,
				NAT_RED,
  				Scram_G3_Skill,
				Morale MORALE_HIGH
				
			}
		},

		AirGroup	//group 4 - MORE MiG intercepters
		{
			Route	
			{
				WayPoint		
				{
					Posn	
						{Abs	{Pack_Target}, 
						 Abs	{Y Scram_G4_Alt}
						},
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	
						{Abs	UID_AfRdAntung, 
						 Abs	{Y Scram_G4_Alt}
						},
 					Range	METRES4000,
					Action	wpalandingno
				}
 			},

			NumInWing	16,	
  			NumInForm	Scram_G4_AC,
			Formation	SQUAD_MIG_RIGHT,

			DUTYMIGCAP,

  			Posn	{Abs	{Pack_Target}, 
  					 Abs	{Y Scram_G4_Alt},
  					 Rel	{Intercept	{Pack_Target,quick_01_G1_aircraft},
  					 		 Bearing	{Random ANGLES_45Deg,270,ANGLES_1Deg},
							 Range		{Random	METRES8000,9,METRES1000}
							}
					},	

		   AirItem	
			{
				Home		UID_AfRdAntung,
				Scram_G4_Squad,
				NAT_RED,
  				Scram_G4_Skill,
				Morale MORALE_HIGH
			}
		}
	};

//--------------------------------
//Dogfight 1: No Advantage

//DeadCode MS 18Mar99 	Aircraft	quick_02_G0_aircraft;	
//DeadCode MS 18Mar99 	Aircraft	quick_02_G1_aircraft;	

	BattleField
	{
		FileName	FIL_QUICKMISSION_02=QUICKM02.BF,

//DeadCode MS 18Mar99 		Setval		(EnemyScoutMorale, (Select Scram_G0_Skill,0,0)),
//DeadCode MS 18Mar99 		Setval		(FriendlyScoutMorale, (Select Scram_G1_Skill,0,0)),
	 	Setval		{RandAngle, Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg}},
		Setval	{FriendHomeBase, UID_AfBlKimpo},
		Setval	{EnemyScoutHomeBase, UID_AfRdAntung},

//DeadCode MS 18Mar99 	SimpleItem	
//DeadCode MS 18Mar99 	{
//DeadCode MS 18Mar99 		Posn	
//DeadCode MS 18Mar99 		{
//DeadCode MS 18Mar99 			Abs	Pack_Target,
//DeadCode MS 18Mar99 			Rel	{Bearing {Select	ANGLES_260Deg,0,ANGLES_40Deg},
//DeadCode MS 18Mar99 			 	 Range METRES400
//DeadCode MS 18Mar99 				}
//DeadCode MS 18Mar99 		},
//DeadCode MS 18Mar99 		UIDBand		MissileBAND,
//DeadCode MS 18Mar99 		Shape		CITY1	
//DeadCode MS 18Mar99 	},
//DeadCode MS 18Mar99 
//DeadCode MS 18Mar99 	SimpleItem	
//DeadCode MS 18Mar99 	{
//DeadCode MS 18Mar99 		Posn	
//DeadCode MS 18Mar99 		{
//DeadCode MS 18Mar99 			Abs	Pack_Target,
//DeadCode MS 18Mar99 			Rel	{Bearing {Select	ANGLES_260Deg,2,ANGLES_40Deg},
//DeadCode MS 18Mar99 			 	 Range METRES400
//DeadCode MS 18Mar99 				}
//DeadCode MS 18Mar99 		},
//DeadCode MS 18Mar99 		UIDBand		MissileBAND,
//DeadCode MS 18Mar99 		Shape		SDISP2	
//DeadCode MS 18Mar99 	},
//DeadCode MS 18Mar99 
//DeadCode MS 18Mar99 	SimpleItem	
//DeadCode MS 18Mar99 	{
//DeadCode MS 18Mar99 		Posn	
//DeadCode MS 18Mar99 		{
//DeadCode MS 18Mar99 			Abs	Pack_Target,
//DeadCode MS 18Mar99 			Rel	{Bearing {Select	ANGLES_260Deg,4,ANGLES_40Deg},
//DeadCode MS 18Mar99 			 	 Range METRES400
//DeadCode MS 18Mar99 				}
//DeadCode MS 18Mar99 		},
//DeadCode MS 18Mar99 		UIDBand		MissileBAND,
//DeadCode MS 18Mar99 		Shape		WF7L	
//DeadCode MS 18Mar99 	},

		AirGroup	//group 00 - UN patrol
		{
			Route	
			{
				WayPoint
				{
					Posn		
						{Abs	Pack_Target, 
						 Abs	{Y Scram_G0_Alt},
				 		 Rel	{Bearing {Select RandAngle,1,ANGLES_45Deg},
								 Range	METRES20
								} 
						},
					Action	wpacnoactionno	
				},
				WayPoint		
				{
					Posn	
						{Abs	{Pack_Target}, 
						 Abs	{Y Scram_G0_Alt}
						},
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	
						{Abs	{FriendHomeBase}, 
						 Abs	{Y FT_5000}
						},
 					Range	METRES5000,
					Action	wpalandingno
				}
 			},
			
			Posn		
				{Abs	Pack_Target, 
				 Abs	{Y Scram_G0_Alt},
					 	 Rel	{Bearing {Select RandAngle,1,ANGLES_135Deg},
						 Range	METRES3000
						} 
				},

			NumInWing	2,
  			NumInForm	Scram_G0_AC,
//DeadCode MS 09Apr99   			NumInForm	1,

  			DUTYMIGCAP,
		    SQUAD_COMBAT_FLATV,

			AirItem	 
			{
				Scram_G0_Squad,
				Home	UID_AfBlKimpo,
  				NAT_BLUE,
				MORALE_HIGH,
  				Scram_G0_Skill
  			}
 		},

		AirGroup	//group 1 Migs
		{

			Route	
			{
				WayPoint
				{
					Posn		
						{Abs	Pack_Target, 
						 Abs	{Y Scram_G1_Alt},
				 		 Rel	{Bearing {Select RandAngle,1,ANGLES_225Deg},
								 Range	METRES20
								} 
						},
					Action	wpacnoactionno	
				},
				WayPoint		
				{
					Posn	
						{Abs	{Pack_Target}, 
						 Abs	{Y Scram_G1_Alt}
						},
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	
						{Abs	{EnemyScoutHomeBase}, 
						 Abs	{Y FT_5000}
						},
 					Range	METRES5000,
					Action	wpalandingno
				}
 			},
			
			Posn		
				{Abs	Pack_Target, 
				 Abs	{Y Scram_G1_Alt},
					 	 Rel	{Bearing {Select RandAngle,1,ANGLES_315Deg},
						 Range	METRES3000
						} 
				},

			NumInWing	2,
  			NumInForm	Scram_G1_AC,
//DeadCode MS 14Apr99   			NumInForm	1,

		   AirItem	 
			{
				Home		UID_AfRdAntung,
				Scram_G1_Squad,
				NAT_RED,
				MORALE_HIGH,
  				Scram_G1_Skill
			}
		}
	};

//--------------------------------
//Dogfight 2: Random Advantage

	BattleField
	{
		FileName	FIL_QUICKMISSION_03=QUICKM03.BF,
//		Setval	{Pack_Target, UID_AfRdSinuiju},
	 	Setval		{RandAngle, Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg}},
		Setval	{FriendHomeBase, UID_AfBlKimpo},
		Setval	{EnemyScoutHomeBase, UID_AfRdAntung},

//DeadCode MS 18Mar99 		Setval		(EnemyScoutMorale, (Select Scram_G0_Skill,0,0)),
//DeadCode MS 18Mar99 		Setval		(FriendlyScoutMorale, (Select Scram_G1_Skill,0,0)),

		AirGroup	//group 00 - UN 
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target},
						 Abs	{Y Scram_G0_Alt},
						 Rel	{Bearing	{Random ANGLES_0Deg,359,ANGLES_1Deg},
						 		 Range	METRES3000
								}
						},
					Action	wpacnoactionno
				},
				WayPoint		
				{
					Posn	
						{Abs	{Pack_Target}, 
						 Abs	{Y Scram_G0_Alt}
						},
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	
						{Abs	{FriendHomeBase}, 
						 Abs	{Y FT_5000}
						},
 					Range	METRES5000,
					Action	wpalandingno
				}
 			},
			
  			NumInWing	2,
  			NumInForm	Scram_G0_AC,
  			DUTYMIGCAP,
			SQUAD_COMBAT_FLATV,

  			Posn	{Abs	Pack_Target, 
  					 Abs	{Y Scram_G0_Alt},
				 	 Rel	{Intercept	{Pack_Target,UID_AfRdAntung},
  							 Bearing	{Random RandAngle,180,ANGLES_1Deg},
							 Range	METRES1000
							}
					},	
			AirItem	  
			{
				Scram_G0_Squad,
				Home	UID_AfBlKimpo,
  				NAT_BLUE,
				MORALE_HIGH,
  				Scram_G0_Skill

  			}
 		},

		AirGroup	//group 1 - Mig patrol
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target},
						 Abs	{Y Scram_G0_Alt},
						 Rel	{Bearing	{Random ANGLES_0Deg,359,ANGLES_1Deg},
						 		 Range	METRES3000
								}
						},
					Action	wpacnoactionno
				},
				WayPoint		
				{
					Posn	
						{Abs	{Pack_Target}, 
						 Abs	{Y Scram_G0_Alt}
						},
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	
						{Abs	{EnemyScoutHomeBase}, 
						 Abs	{Y FT_5000}
						},
 					Range	METRES5000,
					Action	wpalandingno
				}
 			},

			NumInWing	4,
  			NumInForm	Scram_G1_AC,

			DUTYMIGCAP,

  			Posn	{Abs	{Pack_Target}, 
  					 Abs	{Y Scram_G0_Alt},
				 	 Rel	{Intercept	{UID_AfRdAntung,Pack_Target},
  							 Bearing	{Random RandAngle,180,ANGLES_1Deg},
							 Range	METRES1000
							}
					},	

		   AirItem	
			{
				Home		UID_AfRdAntung,
				Scram_G1_Squad,
				NAT_RED,
				MORALE_HIGH,
  				Scram_G1_Skill

			}
		}
	};


//--------------------------------
//Dogfight 3: Advantage UN

	BattleField
	{
		FileName	FIL_QUICKMISSION_04=QUICKM04.BF,
	 	Setval	{RandAngle, Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg}},
		Setval	{FriendHomeBase, UID_AfBlKimpo},
		Setval	{EnemyScoutHomeBase, UID_AfRdAntung},
//MARK, DON'T SCREW WITH ANY ANGLES - TOO MUCH HEAD WRECK

		AirGroup	//group 1 - Mig patrol
		{
			Route
			{
				WayPoint		
				{
					Posn	
						{Abs	{Pack_Target},
						 Abs	{Y Scram_G1_Alt},
						 Rel	{Bearing	{Select RandAngle,1,ANGLES_225Deg},
						 		 Range	METRES3000
								}
						}
				},
				WayPoint	
				{
					Posn	
						{Abs	{EnemyScoutHomeBase}, 
						 Abs	{Y FT_5000}
						},
 					Range	METRES5000,
					Action	wpalandingno
				}
 			},

			NumInWing	4,
  			NumInForm	Scram_G1_AC,

			DUTYMIGCAP,

  			Posn	{Abs	{Pack_Target}, 
  					 Abs	{Y Scram_G1_Alt}
					},	

		   AirItem
			{
				Home		UID_AfRdAntung,
				Scram_G1_Squad,
				NAT_RED,
				MORALE_HIGH,
  				Scram_G1_Skill
			}
		},
		AirGroup	//group 00 - UN 
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target},
						 Abs	{Y Scram_G0_Alt}
						},
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	
						{Abs	{FriendHomeBase}, 
						 Abs	{Y FT_5000}
						},
 					Range	METRES5000,
					Action	wpalandingno
				}
 			},
			
  			NumInWing	2,
  			NumInForm	Scram_G0_AC,
  			DUTYMIGCAP,
			SQUAD_COMBAT_FLATV,

  			Posn	{Abs	{Pack_Target}, 
  					 Abs	{Y Scram_G0_Alt},
  					 Rel	{Bearing	{Random RandAngle,135,ANGLES_1Deg},
							 Range	METRES1000
							}
					},	
			AirItem	     	
			{
				Scram_G0_Squad,
				Home	UID_AfBlKimpo,
  				NAT_BLUE,
				EnemyScoutMorale,
  				Scram_G0_Skill
  			}
 		}
	};

//--------------------------------
//
//ADVANTAGE REDS
	BattleField
	{
		FileName	FIL_QUICKMISSION_05=QUICKM05.BF,
//		Setval	{Pack_Target, UID_AfRdSinuiju},
		Setval	{FriendHomeBase, UID_AfBlKimpo},
		Setval	{EnemyScoutHomeBase, UID_AfRdAntung},

	 	Setval	{RandAngle, Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg}},
//MARK, DON'T SCREW WITH ANY ANGLES - TOO MUCH HEAD WRECK

		AirGroup	//group 00 - UN
		{
			Route
			{
				WayPoint		
				{
					Posn	
						{Abs	{Pack_Target},
						 Abs	{Y Scram_G0_Alt},
						 Rel	{Bearing	{Select RandAngle,1,ANGLES_225Deg},
						 		 Range	METRES3000
								}
						}
				},
				WayPoint	
				{
					Posn	
						{Abs	{FriendHomeBase}, 
						 Abs	{Y FT_5000}
						},
 					Range	METRES5000,
					Action	wpalandingno
				}
 			},

			NumInWing	2,
  			NumInForm	Scram_G0_AC,
		    SQUAD_COMBAT_FLATV,

			DUTYMIGCAP,

  			Posn	{Abs	{Pack_Target}, 
  					 Abs	{Y Scram_G0_Alt}
					},	

		   AirItem
			{
				Home		FriendHomeBase,
				Scram_G0_Squad,
				NAT_BLUE,
				MORALE_HIGH,
  				Scram_G0_Skill
			}
		},
		AirGroup	//group 01 - REDS
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target},
						 Abs	{Y Scram_G1_Alt}
						},
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	
						{Abs	{EnemyScoutHomeBase}, 
						 Abs	{Y FT_5000}
						},
 					Range	METRES5000,
					Action	wpalandingno
				}
 			},
			
  			NumInWing	4,
  			NumInForm	Scram_G1_AC,
  			DUTYMIGCAP,

  			Posn	{Abs	{Pack_Target}, 
  					 Abs	{Y Scram_G1_Alt},
  					 Rel	{Bearing	{Random RandAngle,90,ANGLES_1Deg},
							 Range	METRES1000
							}
					},	
			AirItem	     	
			{
				Scram_G1_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RED,
				MORALE_HIGH,
  				Scram_G1_Skill
  			}
 		}
	};

//--------------------------------
//
//AR ROAD
	BattleField
	{
		FileName	FIL_QUICKMISSION_06=QUICKM06.BF,
//		Setval	{Pack_Target, UID_AfRdSinuiju},

			SimpleItem	
			{
				Posn
				{
					Abs
					{
							X	70382080,
							Z	63354880
					}
				},
				UIDBand		AmberCivilianBAND,
				SetUID		UID_AR_ROAD_TARGET,
				Shape		EMPTY
			},
			SimpleItem	
			{
				Posn
				{
					Abs
					{	X	70396416,
						Z	63139840
					}
				},
				UIDBand		RedAAASiteBAND,
				Shape		CH37ML
			},
			SimpleItem	
			{
				Posn
				{
					Abs
					{	X	70131712,
						Z	63585280
					}
				},
				UIDBand		RedAAASiteBAND,
				Shape		CH37ML
			},
		ItemGroup
		{	Target	UID_AR_ROAD_TARGET,
		GroundGroup
		{	
			Posn
			{
				Abs
				{	X	70119936,
					Z	63699968
				}
			},
			Route
			{
				WayPoint	
				{
					Posn
					{
						Abs
						{	X	70121472,
							Z	63665664
						}
					},
					Vel	87,
					Action	wpdmbtrknoactno
				},
				WayPoint	
				{
					Posn
					{
						Abs
						{	X	70123520,
							Z	63630848
						}
					},
					Vel	87,
					Action	wpdmbtrknoactno
				},
				WayPoint	
				{
					Posn
					{
						Abs
						{	X	70128128,
							Z	63609856
						}
					},
					Vel	87,
					Action	wpdmbtrknoactno
				},
				WayPoint	
				{
					Posn
					{
						Abs
						{	X	70132224,
							Z	63593984
						}
					},
					Vel	87,
					Action	wpdmbtrknoactno
				},
				WayPoint	
				{
					Posn
					{
						Abs
						{	X	70146560,
							Z	63593472
						}
					},
					Vel	87,
					Action	wpdmbtrkstopno,
					Range	0
				}
			},
			NumInForm		8,
			Formation	SQUAD_TRUCKCONVOY,
			GroundItem	
			{
				RedTruckBAND,
				Type	SQ_VEHICLES,
				Side	NAT_RED,
				Shape	CHTRCK,
				Vel	87
		}	},
		GroundGroup
		{
			Posn
			{
				Abs
				{	X	70302720,
					Z	63494656
				}
			},
			Route
			{
				WayPoint	
				{
					Posn
					{
						Abs
						{	X	70365184,
							Z	63491072
						}
					},
					Vel	87,
					Action	wpdmbtrknoactno
				},
				WayPoint	
				{
					Posn
					{
						Abs
						{	X	70368256,
							Z	63476736
						}
					},
					Vel	87,
					Action	wpdmbtrknoactno
				},
				WayPoint	
				{
					Posn
					{
						Abs
						{	X	70377472,
							Z	63451648
						}
					},
					Vel	87,
					Action	wpdmbtrknoactno
				},
				WayPoint	
				{
					Posn
					{
						Abs
						{	X	70379008,
							Z	63380480
						}
					},
					Vel	87,
					Action	wpdmbtrkstopno,
					Range	0
				}
			},
			NumInForm		8,
			Formation	SQUAD_TRUCKCONVOY,
			GroundItem	
			{
				RedTruckBAND,
				Type	SQ_VEHICLES,
				Side	NAT_RED,
				Shape	CHTRCK,
				Vel	87
		}	},
		GroundGroup
		{
			Posn
			{
				Abs
				{	X	70382080,
					Z	63354880
				}
			},
			Route
			{
				WayPoint	
				{
					Posn
					{
						Abs
						{	X	70381568,
							Z	63326208
						}
					},
					Vel	40,
					Action	wpdmbtrknoactno
				},
				WayPoint	
				{
					Posn
					{
						Abs
						{	X	70381056,
							Z	63276032
						}
					},
					Vel	40,
					Action	wpdmbtrknoactno
				},
				WayPoint	
				{
					Posn
					{
						Abs
						{	X	70374400,
							Z	63258624
						}
					},
					Vel	40,
					Action	wpdmbtrknoactno
				},
				WayPoint	
				{
					Posn
					{
						Abs
						{	X	70367744,
							Z	63224320
						}
					},
					Vel	40,
					Action	wpdmbtrkstopno,
					Range	0
				}
			},
			NumInForm		5,
			Formation	FORM_SINGLEFILE,
			GroundItem	
			{
				RedTruckBAND,
				Type	SQ_VEHICLES,
				Side	NAT_RED,
				Shape	CHTRCK,
				Vel	40
			}	
		}
		},

		AirGroup	//group 00 - UN 
		{
			Route	
			{
				WayPoint	
				{
					Posn
					{
						Abs
						{
								X	70382080,
								Z	63354880,
								Y	FT_0
						}
					},
					Range 	METRES2000,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Target	UID_AR_ROAD_TARGET,
					Posn
					{
						Abs	{Y 	Scram_G0_Alt}
					},
					wpstartloopno
				},
				WayPoint	
				{
					Posn
					{ 
						Abs	
						{	X	70382080,
							Z	63354880,
							Y 	Scram_G0_Alt
						}
					},
					wpstoploopchkno
				},
				WayPoint	
				{
					Posn	
						{Abs	UID_AfBlKimpo, 
						 Abs	{Y Scram_G0_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				}
 			},
			
  			NumInWing	2,
  			NumInForm	Scram_G0_AC,
  			DC_AR,
//			Formation	SQUAD_STACKEDV,

			Posn
			{ 
				Abs	
					{	X	70367744,
						Z	63100000,
						Y 	Scram_G0_Alt
					}
			},

			AirItem	  
			{
				Scram_G0_Squad,
				Home	UID_AfBlKimpo,
  				NAT_BLUE,
				MORALE_HIGH,
  				Scram_G0_Skill,
				Bombs	Weap_Rocket,
				Target	UID_AR_ROAD_TARGET	
  			}
 		}
	};

//--------------------------------
//
//AR RAIL
	BattleField
	{
		FileName	FIL_QUICKMISSION_07=QUICKM07.BF,

			SimpleItem	
			{
				Posn	
					{
						Abs	
						{X	66068480,
						 Z	72071168
						}
					},
				UIDBand		AmberCivilianBAND,
				SetUID		UID_AR_RAIL_TARGET,
				Shape		EMPTY
			},

		ItemGroup
		{
			SimpleItem	
			{
				Posn
				{
					Abs
					{	X	65925120,
						Z	71957504
					}
				},
	 			UIDBand		RedAAASiteBAND,
				Shape		CHLBAA
			},
			SimpleItem	
			{
				Posn
				{
					Abs
					{	X	66172416,
						Z	72282624
					}
				},
				UIDBand		RedAAASiteBAND,
				Shape		CHLBAA
			},
			SimpleItem	
			{
				Posn
				{
					Abs
					{	X	66229248,
						Z	72480256
					}
				},
				UIDBand		RedAAASiteBAND,
				Shape		CHLBAA
			},
			SimpleItem	
			{
				Posn
				{
					Abs
					{	X	65899520,
						Z	71685632
					}
				},
				UIDBand		RedAAASiteBAND,
				Shape		CHLBAA
			},
			SimpleItem	
			{
				Posn
				{
					Abs
					{	X	65692672,
						Z	71296000
					}
				},
				UIDBand		RedAAASiteBAND,
				Shape		CHLBAA
			}
		},
		ItemGroup
		{	Target	UID_AR_RAIL_TARGET,
		GroundGroup
		{
			Posn
			{
				Abs
				{	X	66068480,
					Z	72071168
				}
			},
			Route
			{
				WayPoint	
				{
					Posn
					{
						Abs
						{	X	66060288,
							Z	72059904
						}
					},
					Vel	84,
					Action	wpdmbtrknoactno
				},
				WayPoint	
				{
					Posn
					{
						Abs
						{	X	66042368,
							Z	72050688
						}
					},
					Vel	84,
					Action	wpdmbtrknoactno
				},
				WayPoint	
				{
					Posn
					{
						Abs
						{	X	66021376,
							Z	72032256
						}
					},
					Vel	84,
					Action	wpdmbtrknoactno
				},
				WayPoint	
				{
					Posn
					{
						Abs
						{	X	66010112,
							Z	72027648
						}
					},
					Vel	84,
					Action	wpdmbtrknoactno
				},
				WayPoint	
				{
					Posn
					{
						Abs
						{	X	65990656,
							Z	72012800
						}
					},
					Vel	84,
					Action	wpdmbtrknoactno
				},
				WayPoint	
				{
					Posn
					{
						Abs
						{	X	65975296,
							Z	72004096
						}
					},
					Vel	84,
					Action	wpdmbtrknoactno
				},
				WayPoint	
				{
					Posn
					{
						Abs
						{	X	65937920,
							Z	71965696
						}
					},
					Vel	84,
					Action	wpdmbtrknoactno
				},
				WayPoint	
				{
					Posn
					{
						Abs
						{	X	65930752,
							Z	71949824
						}
					},
					Vel	84,
					Action	wpdmbtrknoactno
				},
				WayPoint	
				{
					Posn
					{
						Abs
						{	X	65925632,
							Z	71944192
						}
					},
					Vel	84,
					Action	wpdmbtrknoactno
				},
				WayPoint	
				{
					Posn
					{
						Abs
						{	X	65927168,
							Z	71932928
						}
					},
					Vel	84,
					Action	wpdmbtrknoactno
				},
				WayPoint	
				{
					Posn
					{
						Abs
						{	X	65935872,
							Z	71916032
						}
					},
					Vel	84,
					Action	wpdmbtrknoactno
				},
				WayPoint	
				{
					Posn
					{
						Abs
						{	X	65937408,
							Z	71895552
						}
					},
					Vel	84,
					Action	wpdmbtrknoactno
				},
				WayPoint	
				{
					Posn
					{
						Abs
						{	X	65933312,
							Z	71879680
						}
					},
					Vel	84,
					Action	wpdmbtrknoactno
				},
				WayPoint	
				{
					Posn
					{
						Abs
						{	X	65900544,
							Z	71846400
						}
					},
					Vel	84,
					Action	wpdmbtrknoactno
				},
				WayPoint	
				{
					Posn
					{
						Abs
						{	X	65890816,
							Z	71831040
						}
					},
					Vel	84,
					Action	wpdmbtrkstopno,
					Range	0
				}
			},
			NumInForm		12,
			Formation	FORM_SINGLEFILE,
			GroundItem	
			{
				RedTrainBAND,
				Type	SQ_VEHICLES,
				Side	NAT_RED,
				Shape	TrainShapeInst1,
				Vel	84
			}
		}
		},

		AirGroup	//group 00 - UN 
		{
			Route	
			{
				WayPoint	
				{
					Posn
					{
						Abs
						{
								X	66068480,
						 		Z	72071168,
								Y	Scram_G0_Alt
						}
					},
					Range 	METRES2000,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Target	UID_AR_RAIL_TARGET,
					Posn
					{ 
						Abs	
						{
							Y 	Scram_G0_Alt
						}
					},
					wpstartloopno
				},
				WayPoint	
				{
					Posn	
						{
							Abs	
							{X	66068480,
							 Z	72071168,
						 	 Y Scram_G0_Alt
							}
						},
					wpstoploopchkno
				},
				WayPoint	
				{
					Posn	
						{Abs	UID_AfBlKimpo, 
						 Abs	{Y Scram_G0_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				}
 			},
			
  			NumInWing	2,
  			NumInForm	Scram_G0_AC,
  			DC_AR,
			Formation	SQUAD_STACKEDV,

					Posn	
						{
							Abs	
							{X	65890816,
							 Z	71731040,
						 	 Y Scram_G0_Alt
							}
						},
			AirItem	  
			{
				Scram_G0_Squad,
				Home	UID_AfBlKimpo,
  				NAT_BLUE,
				MORALE_HIGH,
  				Scram_G0_Skill,
				Bombs	Weap_Rocket,
				Target	UID_AR_RAIL_TARGET
  			}
 		}
	};

//--------------------------------
//
//RED GROUND ATTACK
 
	BattleField
	{
		FileName	FIL_QUICKMISSION_08=QUICKM08.BF,
	 	Setval	{RandAngle, Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg}},
		Setval	{RangeStepSize, Int {Random 0,4,1}},
		Setval	{HeightStepSize, Int {Random 4,5,1}},

		SimpleItem	
		{
			Posn
			{
				Abs
				{	Pack_Target
				}
			},
			UIDBand		AfNoScoreBAND,
			Shape		GRNDD4
		},
		SimpleItem	
		{
			Posn		
			{	
				Abs		Pack_Target, 
		 		 Rel	{Bearing {Select ANGLES_300Deg,3,ANGLES_1Deg},
						 Range	METRES200
						} 
			},
			UIDBand		AfNoScoreBAND,
			Shape		GRNDD4
		},

		AirGroup	
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	Pack_Target, 
						 Abs	{Y Scram_G1_Alt}
						},
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	
						{Abs	Pack_Target, 
						 Abs	{Y Scram_G1_Alt},
					 	 Rel	{Bearing RandAngle,
							 	 Range METRES5000
							}
						},
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	
						{Abs	Pack_Target, 
						 Abs	{Y Scram_G0_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				}
 			},
			
			NumInWing	2,
  			NumInForm	Scram_G0_AC,

  			DUTYMIGCAP,

			Posn		
				{Abs	Pack_Target, 
				 Abs	{Y Scram_G0_Alt},
		 		 Rel	{Bearing {Random ANGLES_0Deg,400,ANGLES_1Deg},
						 Range	{Random METRES1500,16,METRES100}
						} 
				},

			AirItem
			{
				Scram_G0_Squad,
				Home	Pack_Target,
  				NAT_BLUE,
				MORALE_HIGH,
  				Scram_G0_Skill
  			}
 		},

		AirGroup   
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	Pack_Target, 
						 Abs	{Y Scram_G1_Alt},
					 	 Rel	{Bearing RandAngle,
							 Range METRES5000
							}
						},
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	
						{Abs	Pack_Target, 
						 Abs	{Y Scram_G1_Alt}
						},
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	
						{Abs	UID_AfRdAntung, 
						 Abs	{Y Scram_G1_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				}
 			},

			NumInWing	HeightStepSize,
  			NumInForm	Scram_G1_AC,

			Formation	{List {Select RangeStepSize},
						SQUAD_MIG_RIGHT,
						SQUAD_GAGGLE,
						SQUAD_CH_ABREAST
					},

  			DUTYMIGCAP,

			Posn		
				{Abs	Pack_Target, 
				 Abs	{Y Scram_G1_Alt}
				},

		   AirItem
			{
				Home		UID_AfRdAntung,
				Scram_G1_Squad,
				NAT_RED,
  				Scram_G1_Skill,
				MORALE_HIGH
			}
		},

		AirGroup	
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	UID_AfBlTaegu, 
						 Abs	{Y FT_0}
						},
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	
						{Abs	UID_AfBlTaegu, 
						 Abs	{Y FT_1000},
					 	 Rel	{Bearing RandAngle,
							 Range METRES5000
							}
						},
					Action	wpalandingno
				}
 			},
			
			NumInWing	1,
  			NumInForm	1,

			Posn		
				{Abs	UID_AfBlTaegu, 
				 Abs	{Y FT_500},
		 		 Rel	{Bearing {Select ANGLES_300Deg,3,ANGLES_1Deg},
						 Range	METRES5000
						} 
				},

			AirItem
			{
				SQ_B29,
				Home	UID_AfBlTaegu,
  				NAT_BLUE,
				MORALE_HIGH,
  				Scram_G0_Skill
  			}
 		}
	};

//--------------------------------
//Travel the world

	BattleField
	{
		FileName	FIL_QUICKMISSION_09=QUICKM09.BF,

		AirGroup	
		{
			Route	
			{
				WayPoint  
				{
  					Posn	{Abs	{Pack_Target},
						 Abs	{Y -FT_2000}
						},
//DeadCode MS 11May99 						 	 Rel	{Y {Select Scram_G0_Alt,1,-METRES3000}}
//DeadCode MS 11May99 							},
					Action	wpacnoactionno	
				},
//TempCode MS 10May99 				WayPoint	
//TempCode MS 10May99 				{
//TempCode MS 10May99 					Posn	
//TempCode MS 10May99 						{Abs	Pack_Target, 
//TempCode MS 10May99 						 Abs	{Y FT_4000},
//TempCode MS 10May99 						 Rel	{Bearing ANGLES_180Deg,
//TempCode MS 10May99 							 Range METRES15KM,
//TempCode MS 10May99 							 Pitch ANGLES_0Deg
//TempCode MS 10May99 							}
//TempCode MS 10May99 						},
//TempCode MS 10May99  					Range	METRES1000,
//TempCode MS 10May99 					Action	wpalandingno
//TempCode MS 10May99 				}
				WayPoint	
				{
					Posn	
						{Abs	UID_AfBlKimpo, 
						 Abs	{Y Scram_G0_Alt}
						},
 					Range	METRES5000,
					Action	wpalandingno
				}
 			},
			
			NumInWing	1,
  			NumInForm	1,

			Posn		
				{Abs	Pack_Target, 
			   	 Abs	{Y Scram_G0_Alt},
				 Rel	{Bearing {Random ANGLES_90Deg,3,ANGLES_90Deg},
						 Range	METRES5000
						} 
				},
			

			AirItem	
			{
				Scram_G0_Squad,
				Home	UID_AfBlKimpo,
  				NAT_BLUE,
				MORALE_HIGH,
  				Scram_G0_Skill
//DeadCode MS 13Apr99 				Bombs 3
  			}
 		}
	};

//--------------------------------
//test convoy node


	BattleField
	{
		FileName	FIL_QUICKMISSION_10=QUICKM10.BF,
		AirGroup	
		{
			Route	
			{
				WayPoint  
				{
  					Posn	{Abs	Pack_Target,
						 Abs	{Y FT_4000}
						},
					Action	wpacnoactionno	
				}
 			},
			
			NumInWing	1,
  			NumInForm	1,

			Posn		
				{Abs	Pack_Target, 
			   	 Abs	{Y FT_4000},
				 Rel	{Bearing ANGLES_180Deg,
					 Range	METRES2000
					} 
				},
			

			AirItem	
			{
				Scram_G0_Squad,
				Home	UID_AfBlKimpo,
  				NAT_BLUE,
				MORALE_HIGH,
  				Scram_G0_Skill,
				Bombs 3
  			}
 		}
	};

//--------------------------------
//8 deathmathch battlefields

//THE RING OF DEATH

 	BattleField
	{
		FileName	FIL_deathmatch0= death0.BF,
		Setval	{FriendHomeBase, UID_AfRdSinuiju},
		Setval	{EnemyScoutHomeBase, UID_AfRdSinuiju},
		Setval	{Pack_Target, UID_AfRdPyongyangM},
	 	Setval	{HeightSize, Y {Random FT_4000,21,FT_1000}},
	 	Setval	{RandAngle, Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg}},
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn			//AMM 12May99
						{Abs	{Pack_Target}, //AMM 12May99
						 Abs	{Y HeightSize}//AMM 12May99
						},		//AMM 12May99
//DeadCode AMM 12Mar99 					Posn	
//DeadCode AMM 12Mar99 						{Abs	{Pack_Target}, 
//DeadCode AMM 12Mar99 						 Abs	{Y HeightSize}
//DeadCode AMM 12Mar99 						},
//DeadCode AMM 12May99 					Posn	
//DeadCode AMM 12May99 						{Abs	{EnemyScoutHomeBase}, 
//DeadCode AMM 12May99 						 Rel	{Y FT_2000,X FT_50}
//DeadCode AMM 12May99 						},

					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

  			Posn	{Abs	{Pack_Target}, 		
				     Abs	{Y {Random HeightSize,10,FT_100}},
  					 Rel	{Bearing {Select RandAngle,0,ANGLES_45Deg},
					 		 Range METRES750,
							 Pitch ANGLES_0Deg
							}
					},			
//DeadCode AMM 12Mar99   			Posn	{Abs	{Pack_Target}, 
//DeadCode AMM 12Mar99 				     Abs	{Y {Random HeightSize,10,FT_100}},
//DeadCode AMM 12Mar99   					 Rel	{Bearing {Select RandAngle,0,ANGLES_45Deg},
//DeadCode AMM 12Mar99 					 		 Range METRES750,
//DeadCode AMM 12Mar99 							 Pitch ANGLES_0Deg
//DeadCode AMM 12Mar99 							}
//DeadCode AMM 12Mar99 					},	
//DeadCode AMM 12May99   			Posn	{Abs	EnemyScoutHomeBase, 
//DeadCode AMM 12May99   					 Rel	{Y FT_2000,X FT_100},
//DeadCode AMM 12May99 		 		 Rel	{Bearing ANGLES_90Deg,Range METRES50}
//DeadCode AMM 12May99 					},	

			AirItem  	
			{
				Scram_G0_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RED,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		},
//NUMBER 2
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn			//AMM 12May99
						{Abs	{Pack_Target}, //AMM 12May99
						 Abs	{Y HeightSize}//AMM 12May99
						},		//AMM 12May99
//DeadCode AMM 12Mar99 					Posn	
//DeadCode AMM 12Mar99 						{Abs	{Pack_Target}, 
//DeadCode AMM 12Mar99 						 Abs	{Y HeightSize}
//DeadCode AMM 12Mar99 						},
//DeadCode AMM 12May99 					Posn	
//DeadCode AMM 12May99 						{Abs	{EnemyScoutHomeBase}, 
//DeadCode AMM 12May99 						 Rel	{Y FT_2000,X -FT_50}
//DeadCode AMM 12May99 						},

					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

  			Posn	{Abs	{Pack_Target}, 		
				     Abs	{Y {Random HeightSize,10,FT_100}},
  					 Rel	{Bearing {Select RandAngle,1,ANGLES_45Deg},
					 		 Range METRES750,
							 Pitch ANGLES_0Deg
							}	
					},		
//DeadCode AMM 12Mar99   			Posn	{Abs	{Pack_Target}, 
//DeadCode AMM 12Mar99 				     Abs	{Y {Random HeightSize,10,FT_100}},
//DeadCode AMM 12Mar99   					 Rel	{Bearing {Select RandAngle,1,ANGLES_45Deg},
//DeadCode AMM 12Mar99 					 		 Range METRES750,
//DeadCode AMM 12Mar99 							 Pitch ANGLES_0Deg
//DeadCode AMM 12Mar99 							}
//DeadCode AMM 12Mar99 					},	
//DeadCode AMM 12May99   			Posn	{Abs	EnemyScoutHomeBase, 
//DeadCode AMM 12May99   					 Rel	{Y FT_2000},
//DeadCode AMM 12May99 		 		 Rel	{Bearing ANGLES_90Deg,Range METRES50
//DeadCode AMM 12May99 						} 
//DeadCode AMM 12May99 
//DeadCode AMM 12May99 					},	

			AirItem  	
			{
				Scram_G1_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RED,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		},
//NUMBER 3
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target}, 
						 Abs	{Y HeightSize}
						},

					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

  			Posn	{Abs	{Pack_Target}, 
				     Abs	{Y {Random HeightSize,10,FT_100}},
  					 Rel	{Bearing {Select RandAngle,2,ANGLES_45Deg},
					 		 Range METRES750,
							 Pitch ANGLES_0Deg
							}
					},	

			AirItem  	
			{
				Scram_G2_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RED,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		},
//NUMBER 4
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target}, 
						 Abs	{Y HeightSize}
						},

					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

  			Posn	{Abs	{Pack_Target}, 
				     Abs	{Y {Random HeightSize,10,FT_100}},
  					 Rel	{Bearing {Select RandAngle,3,ANGLES_45Deg},
					 		 Range METRES750,
							 Pitch ANGLES_0Deg
							}
					},	

			AirItem  	
			{
				Scram_G3_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RED,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		},
//NUMBER 5
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target}, 
						 Abs	{Y HeightSize}
						},

					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

  			Posn	{Abs	{Pack_Target}, 
				     Abs	{Y {Random HeightSize,10,FT_100}},
  					 Rel	{Bearing {Select RandAngle,4,ANGLES_45Deg},
					 		 Range METRES750,
							 Pitch ANGLES_0Deg
							}
					},	

			AirItem  	
			{
				Scram_G4_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RED,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		},
//NUMBER 6
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target}, 
						 Abs	{Y HeightSize}
						},

					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

  			Posn	{Abs	{Pack_Target}, 
				     Abs	{Y {Random HeightSize,10,FT_100}},
  					 Rel	{Bearing {Select RandAngle,5,ANGLES_45Deg},
					 		 Range METRES750,
							 Pitch ANGLES_0Deg
							}
					},	

			AirItem  	
			{
				Scram_G5_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RED,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		},
//NUMBER 7
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target}, 
						 Abs	{Y HeightSize}
						},

					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

  			Posn	{Abs	{Pack_Target}, 
				     Abs	{Y {Random HeightSize,10,FT_100}},
  					 Rel	{Bearing {Select RandAngle,6,ANGLES_45Deg},
					 		 Range METRES750,
							 Pitch ANGLES_0Deg
							}
					},	

			AirItem  	
			{
				Scram_G6_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RED,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		},
//NUMBER 8
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target}, 
						 Abs	{Y HeightSize}
						},

					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

  			Posn	{Abs	{Pack_Target}, 
				     Abs	{Y {Random HeightSize,10,FT_100}},
  					 Rel	{Bearing {Select RandAngle,7,ANGLES_45Deg},
					 		 Range METRES750,
							 Pitch ANGLES_0Deg
							}
					},	

			AirItem  	
			{
				Scram_G7_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RED,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		}

	};

//**************************************************************************
//PAIRS

 	BattleField
	{
		FileName	FIL_deathmatch1= death1.BF,
		Setval	{FriendHomeBase, UID_AfRdSinuiju},
		Setval	{EnemyScoutHomeBase, UID_AfRdSinuiju},
		Setval	{Pack_Target, UID_StSeoul},
	 	Setval	{HeightSize, Y {Random FT_4000,21,FT_1000}},
//PAIR 1
		AirGroup
		{
			Route	
			{
				WayPoint D1_WP_00 =	
				{
					Posn	
						{Abs	{Pack_Target}, 
				    	 Abs	{Y {Random HeightSize,10,FT_100}},
						 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
								 Range METRES2000,
								 Pitch ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},


			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

  			Posn	{Abs	{Pack_Target}, 
				     Abs	{Y {Random HeightSize,10,FT_100}},
  					 Rel	{Bearing {Random ANGLES_135Deg,90,ANGLES_1Deg},
					 		 Range METRES1000,
							 Pitch ANGLES_0Deg
							}
					},	
			AirItem	D1_AC_00 =  	
			{
				Scram_G0_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RED,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		},
//ELEMENT
		AirGroup
		{
			Route	
			{
				WayPoint
				{
						Posn	
							{Abs	D1_WP_00}, 
						Action	wpacnoactionno
				}
 			},


			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

  			Posn	{Abs	D1_AC_00, 
  					 Rel	{Bearing {Random ANGLES_315Deg,1,ANGLES_180Deg},
					 		 Range METRES50,
							 Pitch ANGLES_0Deg
							}
					},
	
			AirItem  	
			{
				Scram_G1_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RED,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		},
//PAIR 2
		AirGroup
		{
			Route	
			{
				WayPoint D1_WP_02 =	
				{
					Posn	
						{Abs	{Pack_Target}, 
				    	 Abs	{Y {Random HeightSize,10,FT_100}},
						 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
								 Range METRES2000,
								 Pitch ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},


			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

  			Posn	{Abs	{Pack_Target}, 
				     Abs	{Y {Random HeightSize,10,FT_100}},
  					 Rel	{Bearing {Random ANGLES_225Deg,90,ANGLES_1Deg},
					 		 Range METRES1000,
							 Pitch ANGLES_0Deg
							}
					},	
			AirItem	D1_AC_02 =  	
			{
				Scram_G2_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RED,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		},
//ELEMENT
		AirGroup
		{
			Route	
			{
				WayPoint
				{
						Posn	
							{Abs	D1_WP_02}, 
						Action	wpacnoactionno
				}
 			},


			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

  			Posn	{Abs	D1_AC_02, 
  					 Rel	{Bearing {Random ANGLES_315Deg,1,ANGLES_180Deg},
					 		 Range METRES50,
							 Pitch ANGLES_0Deg
							}
					},
	
			AirItem  	
			{
				Scram_G3_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RED,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		},
//PAIR 3
		AirGroup
		{
			Route	
			{
				WayPoint D1_WP_04 =	
				{
					Posn	
						{Abs	{Pack_Target}, 
				    	 Abs	{Y {Random HeightSize,10,FT_100}},
						 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
								 Range METRES2000,
								 Pitch ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},


			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

  			Posn	{Abs	{Pack_Target}, 
				     Abs	{Y {Random HeightSize,10,FT_100}},
  					 Rel	{Bearing {Random ANGLES_315Deg,90,ANGLES_1Deg},
					 		 Range METRES1000,
							 Pitch ANGLES_0Deg
							}
					},	
			AirItem	D1_AC_04 =  	
			{
				Scram_G4_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RED,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		},
//ELEMENT
		AirGroup
		{
			Route	
			{
				WayPoint
				{
						Posn	
							{Abs	D1_WP_04}, 
						Action	wpacnoactionno
				}
 			},


			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

  			Posn	{Abs	D1_AC_04, 
  					 Rel	{Bearing {Random ANGLES_315Deg,1,ANGLES_180Deg},
					 		 Range METRES50,
							 Pitch ANGLES_0Deg
							}
					},
	
			AirItem  	
			{
				Scram_G5_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RED,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		},
//PAIR 4
		AirGroup
		{
			Route	
			{
				WayPoint D1_WP_06 =	
				{
					Posn	
						{Abs	{Pack_Target}, 
				    	 Abs	{Y {Random HeightSize,10,FT_100}},
						 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
								 Range METRES2000,
								 Pitch ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},


			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

  			Posn	{Abs	{Pack_Target}, 
				     Abs	{Y {Random HeightSize,10,FT_100}},
  					 Rel	{Bearing {Random ANGLES_45Deg,90,ANGLES_1Deg},
					 		 Range METRES1000,
							 Pitch ANGLES_0Deg
							}
					},	
			AirItem	D1_AC_06 =  	
			{
				Scram_G6_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RED,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		},
//ELEMENT
		AirGroup
		{
			Route	
			{
				WayPoint
				{
						Posn	
							{Abs	D1_WP_06}, 
						Action	wpacnoactionno
				}
 			},


			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

  			Posn	{Abs	D1_AC_06, 
  					 Rel	{Bearing {Random ANGLES_315Deg,1,ANGLES_180Deg},
					 		 Range METRES50,
							 Pitch ANGLES_0Deg
							}
					},
	
			AirItem  	
			{
				Scram_G7_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RED,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		}
	};

//**************************************************************************
//THE STRING/WHEEL OF DEATH

 	BattleField
	{
		FileName	FIL_deathmatch2= death2.BF,

		Setval	{FriendHomeBase, UID_AfRdSinuiju},
		Setval	{EnemyScoutHomeBase, UID_AfRdSinuiju},

		Setval	{Pack_Target, UID_StSeoul},
	 	Setval	{HeightSize, Y {Random FT_4000,21,FT_1000}},
	 	Setval	{RandAngle, Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg}},

		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y {Select HeightSize,1,FT_750}},	
						 Rel	{Bearing {Select RandAngle,7,ANGLES_45Deg},
								 Range	METRES750,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing RandAngle,
								 Range	METRES750,
								 Pitch	ANGLES_0Deg
								}
						},

			AirItem  	
			{
				Scram_G0_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RED,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		},
//NUMBER 2
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing RandAngle,
								 Range	METRES750,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y {Select HeightSize,1,FT_750}},	
						 Rel	{Bearing {Select RandAngle,1,ANGLES_45Deg},
								 Range	METRES750,
								 Pitch	ANGLES_0Deg
								}
						},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,
	
			AirItem  	
			{
				Scram_G1_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RED,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		},
//NUMBER 3
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y {Select HeightSize,1,FT_750}},	
						 Rel	{Bearing {Select RandAngle,1,ANGLES_45Deg},
								 Range	METRES750,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y {Select HeightSize,2,FT_750}},	
						 Rel	{Bearing {Select RandAngle,2,ANGLES_45Deg},
								 Range	METRES750,
								 Pitch	ANGLES_0Deg
								}
						},
			AirItem  	
			{
				Scram_G2_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RED,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		},
//NUMBER 4
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y {Select HeightSize,2,FT_750}},	
						 Rel	{Bearing {Select RandAngle,2,ANGLES_45Deg},
								 Range	METRES750,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y {Select HeightSize,1,FT_750}},	
						 Rel	{Bearing {Select RandAngle,3,ANGLES_45Deg},
								 Range	METRES750,
								 Pitch	ANGLES_0Deg
								}
						},
			AirItem  	
			{
				Scram_G3_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RED,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		},
//NUMBER 5
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y {Select HeightSize,1,FT_750}},	
						 Rel	{Bearing {Select RandAngle,3,ANGLES_45Deg},
								 Range	METRES750,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,4,ANGLES_45Deg},
								 Range	METRES750,
								 Pitch	ANGLES_0Deg
								}
						},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

			AirItem  	
			{
				Scram_G4_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RED,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		},
//NUMBER 6
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,4,ANGLES_45Deg},
								 Range	METRES750,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y {Select HeightSize,1,FT_750}},	
						 Rel	{Bearing {Select RandAngle,5,ANGLES_45Deg},
								 Range	METRES750,
								 Pitch	ANGLES_0Deg
								}
						},
			AirItem  	
			{
				Scram_G5_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RED,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		},
//NUMBER 7
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y {Select HeightSize,1,FT_750}},	
						 Rel	{Bearing {Select RandAngle,5,ANGLES_45Deg},
								 Range	METRES750,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y {Select HeightSize,2,FT_750}},	
						 Rel	{Bearing {Select RandAngle,6,ANGLES_45Deg},
								 Range	METRES750,
								 Pitch	ANGLES_0Deg
								}
						},
			AirItem  	
			{
				Scram_G6_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RED,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		},
//NUMBER 8
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y {Select HeightSize,2,FT_750}},	
						 Rel	{Bearing {Select RandAngle,6,ANGLES_45Deg},
								 Range	METRES750,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y {Select HeightSize,1,FT_750}},	
						 Rel	{Bearing {Select RandAngle,7,ANGLES_45Deg},
								 Range	METRES750,
								 Pitch	ANGLES_0Deg
								}
						},
			AirItem  	
			{
				Scram_G7_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RED,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		}
	};

//**************************************************************************
//RANDOM HORIZ

 	BattleField
	{
		FileName	FIL_deathmatch3= death3.BF,
		Setval	{FriendHomeBase, UID_AfRdSinuiju},
		Setval	{EnemyScoutHomeBase, UID_AfRdSinuiju},

		Setval	{Pack_Target, UID_StSeoul},
	 	Setval	{HeightSize, Y {Random FT_4000,21,FT_1000}},

		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y {Random HeightSize,20,FT_100}},	
						 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
								 Range	{Random METRES100,20,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y {Random HeightSize,20,FT_100}},	
						 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
								 Range	{Random METRES100,20,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},

			AirItem  	
			{
				Scram_G0_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RED,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		},
//NUMBER 2
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y {Random HeightSize,20,FT_100}},	
						 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
								 Range	{Random METRES100,20,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y {Random HeightSize,20,FT_100}},	
						 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
								 Range	{Random METRES100,20,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,
	
			AirItem  	
			{
				Scram_G1_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RED,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		},
//NUMBER 3
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y {Random HeightSize,20,FT_100}},	
						 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
								 Range	{Random METRES100,20,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y {Random HeightSize,20,FT_100}},	
						 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
								 Range	{Random METRES100,20,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
			AirItem  	
			{
				Scram_G2_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RED,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		},
//NUMBER 4
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y {Random HeightSize,20,FT_100}},	
						 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
								 Range	{Random METRES100,20,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y {Random HeightSize,20,FT_100}},	
						 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
								 Range	{Random METRES100,20,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
			AirItem  	
			{
				Scram_G3_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RED,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		},
//NUMBER 5
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y {Random HeightSize,20,FT_100}},	
						 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
								 Range	{Random METRES100,20,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y {Random HeightSize,20,FT_100}},	
						 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
								 Range	{Random METRES100,20,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

			AirItem  	
			{
				Scram_G4_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RED,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		},
//NUMBER 6
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y {Random HeightSize,20,FT_100}},	
						 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
								 Range	{Random METRES100,20,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y {Random HeightSize,20,FT_100}},	
						 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
								 Range	{Random METRES100,20,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
			AirItem  	
			{
				Scram_G5_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RED,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		},
//NUMBER 7
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y {Random HeightSize,20,FT_100}},	
						 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
								 Range	{Random METRES100,20,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y {Random HeightSize,20,FT_100}},	
						 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
								 Range	{Random METRES100,20,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
			AirItem  	
			{
				Scram_G6_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RED,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		},
//NUMBER 8
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y {Random HeightSize,20,FT_100}},	
						 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
								 Range	{Random METRES100,20,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y {Random HeightSize,20,FT_100}},	
						 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
								 Range	{Random METRES100,20,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
			AirItem  	
			{
				Scram_G7_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RED,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		}
	};

//**************************************************************************
//RANDOM VERT

 	BattleField
	{
		FileName	FIL_deathmatch4= death4.BF,
		Setval	{FriendHomeBase, UID_AfRdSinuiju},
		Setval	{EnemyScoutHomeBase, UID_AfRdSinuiju},

		Setval	{Pack_Target, UID_StSeoul},
	 	Setval	{HeightSize, Y {Random FT_4000,16,FT_1000}},

		AirGroup
		{
			Route	
			{
				WayPoint						 
				{
					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y {Random HeightSize,100,FT_100}},	
						 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
								 Range	{Random METRES100,20,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y {Random HeightSize,100,FT_100}},	
						 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
								 Range	{Random METRES100,20,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},

			AirItem  	
			{
				Scram_G0_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RED,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		},
//NUMBER 2
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y {Random HeightSize,100,FT_100}},	
						 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
								 Range	{Random METRES100,20,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y {Random HeightSize,100,FT_100}},	
						 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
								 Range	{Random METRES100,20,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,
	
			AirItem  	
			{
				Scram_G1_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RED,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		},
//NUMBER 3
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y {Random HeightSize,100,FT_100}},	
						 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
								 Range	{Random METRES100,20,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y {Random HeightSize,100,FT_100}},	
						 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
								 Range	{Random METRES100,20,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
			AirItem  	
			{
				Scram_G2_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RED,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		},
//NUMBER 4
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y {Random HeightSize,100,FT_100}},	
						 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
								 Range	{Random METRES100,20,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y {Random HeightSize,100,FT_100}},	
						 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
								 Range	{Random METRES100,20,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
			AirItem  	
			{
				Scram_G3_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RED,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		},
//NUMBER 5
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y {Random HeightSize,100,FT_100}},	
						 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
								 Range	{Random METRES100,20,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y {Random HeightSize,100,FT_100}},	
						 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
								 Range	{Random METRES100,20,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

			AirItem  	
			{
				Scram_G4_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RED,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		},
//NUMBER 6
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y {Random HeightSize,100,FT_100}},	
						 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
								 Range	{Random METRES100,20,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y {Random HeightSize,100,FT_100}},	
						 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
								 Range	{Random METRES100,20,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
			AirItem  	
			{
				Scram_G5_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RED,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		},
//NUMBER 7
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y {Random HeightSize,100,FT_100}},	
						 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
								 Range	{Random METRES100,20,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y {Random HeightSize,100,FT_100}},	
						 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
								 Range	{Random METRES100,20,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
			AirItem  	
			{
				Scram_G6_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RED,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		},
//NUMBER 8
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y {Random HeightSize,100,FT_100}},	
						 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
								 Range	{Random METRES100,20,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y {Random HeightSize,100,FT_100}},	
						 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
								 Range	{Random METRES100,20,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
			AirItem  	
			{
				Scram_G7_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RED,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		}
	};
//**************************************************************************
//EXPLODE

 	BattleField
	{
		FileName	FIL_deathmatch5= death5.BF,
		Setval	{FriendHomeBase, UID_AfRdSinuiju},
		Setval	{EnemyScoutHomeBase, UID_AfRdSinuiju},

		Setval	{Pack_Target, UID_StSeoul},
	 	Setval	{HeightSize, Y {Random FT_4000,21,FT_1000}},
	 	Setval	{RandAngle, Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg}},

		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,0,ANGLES_45Deg},
								 Range	METRES2000,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,0,ANGLES_45Deg},
								 Range	METRES20,
								 Pitch	ANGLES_0Deg
								}
						},

			AirItem  	
			{
				Scram_G0_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RED,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		},
//NUMBER 2
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,1,ANGLES_45Deg},
								 Range	METRES2000,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,1,ANGLES_45Deg},
								 Range	METRES20,
								 Pitch	ANGLES_0Deg
								}
						},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,
	
			AirItem  	
			{
				Scram_G1_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RED,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		},
//NUMBER 3
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,2,ANGLES_45Deg},
								 Range	METRES2000,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,2,ANGLES_45Deg},
								 Range	METRES20,
								 Pitch	ANGLES_0Deg
								}
						},
			AirItem  	
			{
				Scram_G2_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RED,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		},
//NUMBER 4
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,3,ANGLES_45Deg},
								 Range	METRES2000,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,3,ANGLES_45Deg},
								 Range	METRES20,
								 Pitch	ANGLES_0Deg
								}
						},
			AirItem  	
			{
				Scram_G3_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RED,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		},
//NUMBER 5
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,4,ANGLES_45Deg},
								 Range	METRES2000,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,4,ANGLES_45Deg},
								 Range	METRES20,
								 Pitch	ANGLES_0Deg
								}
						},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

			AirItem  	
			{
				Scram_G4_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RED,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		},
//NUMBER 6
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,5,ANGLES_45Deg},
								 Range	METRES2000,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,5,ANGLES_45Deg},
								 Range	METRES20,
								 Pitch	ANGLES_0Deg
								}
						},
			AirItem  	
			{
				Scram_G5_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RED,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		},
//NUMBER 7
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,6,ANGLES_45Deg},
								 Range	METRES2000,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,6,ANGLES_45Deg},
								 Range	METRES20,
								 Pitch	ANGLES_0Deg
								}
						},
			AirItem  	
			{
				Scram_G6_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RED,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		},
//NUMBER 8
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,7,ANGLES_45Deg},
								 Range	METRES2000,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,7,ANGLES_45Deg},
								 Range	METRES20,
								 Pitch	ANGLES_0Deg
								}
						},
			AirItem  	
			{
				Scram_G7_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RED,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		}
	};
//**************************************************************************
//PIGGEY IN THE MIDDLE
 	BattleField
	{
		FileName	FIL_deathmatch6= death6.BF,
		Setval	{FriendHomeBase, UID_AfRdSinuiju},
		Setval	{EnemyScoutHomeBase, UID_AfRdSinuiju},
		Setval	{Pack_Target, UID_StSeoul},
	 	Setval	{HeightSize, Y {Random FT_4000,21,FT_1000}},
	 	Setval	{RandAngle, Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg}},
		Setval	{ParentRand, Int {Random 0,8,1}},

		Setval	(RangeStepSize, Int (List ParentRand,0,1,1,1,1,1,1,1)),

		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing RandAngle,
								 Range	METRES10,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

			Posn	
				{Abs	{Pack_Target},
	  			 Abs	{Y HeightSize},	
				 Rel	{Bearing {Select RandAngle,0,ANGLES_45Deg},
						 Range	{Select 0,RangeStepSize,METRES1000},
						 Pitch	ANGLES_0Deg
						}
				},

			AirItem  	
			{
				Scram_G0_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RED,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		},
//NUMBER 2
		Setval	(RangeStepSize, Int (List ParentRand,1,0,1,1,1,1,1,1)),

		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing RandAngle,
								 Range	METRES10,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

			Posn	
				{Abs	{Pack_Target},
	  			 Abs	{Y HeightSize},	
				 Rel	{Bearing {Select RandAngle,1,ANGLES_45Deg},
						 Range	{Select 0,RangeStepSize,METRES1000},
						 Pitch	ANGLES_0Deg
						}
				},

			AirItem  	
			{
				Scram_G1_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RED,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		},

//NUMBER 3
		Setval	(RangeStepSize, Int (List ParentRand,1,1,0,1,1,1,1,1)),

		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing RandAngle,
								 Range	METRES10,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

			Posn	
				{Abs	{Pack_Target},
	  			 Abs	{Y HeightSize},	
				 Rel	{Bearing {Select RandAngle,2,ANGLES_45Deg},
						 Range	{Select 0,RangeStepSize,METRES1000},
						 Pitch	ANGLES_0Deg
						}
				},

			AirItem  	
			{
				Scram_G2_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RED,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		},
//NUMBER 4
		Setval	(RangeStepSize, Int (List ParentRand,1,1,1,0,1,1,1,1)),

		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing RandAngle,
								 Range	METRES10,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

			Posn	
				{Abs	{Pack_Target},
	  			 Abs	{Y HeightSize},	
				 Rel	{Bearing {Select RandAngle,3,ANGLES_45Deg},
						 Range	{Select 0,RangeStepSize,METRES1000},
						 Pitch	ANGLES_0Deg
						}
				},

			AirItem  	
			{
				Scram_G3_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RED,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		},
//NUMBER 5
		Setval	(RangeStepSize, Int (List ParentRand,1,1,1,1,0,1,1,1)),

		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing RandAngle,
								 Range	METRES10,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

			Posn	
				{Abs	{Pack_Target},
	  			 Abs	{Y HeightSize},	
				 Rel	{Bearing {Select RandAngle,4,ANGLES_45Deg},
						 Range	{Select 0,RangeStepSize,METRES1000},
						 Pitch	ANGLES_0Deg
						}
				},

			AirItem  	
			{
				Scram_G4_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RED,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		},
//NUMBER 6
		Setval	(RangeStepSize, Int (List ParentRand,1,1,1,1,1,0,1,1)),

		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing RandAngle,
								 Range	METRES10,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

			Posn	
				{Abs	{Pack_Target},
	  			 Abs	{Y HeightSize},	
				 Rel	{Bearing {Select RandAngle,5,ANGLES_45Deg},
						 Range	{Select 0,RangeStepSize,METRES1000},
						 Pitch	ANGLES_0Deg
						}
				},

			AirItem  	
			{
				Scram_G5_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RED,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		},
//NUMBER 7
		Setval	(RangeStepSize, Int (List ParentRand,1,1,1,1,1,1,0,1)),

		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing RandAngle,
								 Range	METRES10,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

			Posn	
				{Abs	{Pack_Target},
	  			 Abs	{Y HeightSize},	
				 Rel	{Bearing {Select RandAngle,6,ANGLES_45Deg},
						 Range	{Select 0,RangeStepSize,METRES1000},
						 Pitch	ANGLES_0Deg
						}
				},

			AirItem  	
			{
				Scram_G6_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RED,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		},
//NUMBER 8
		Setval	(RangeStepSize, Int (List ParentRand,1,1,1,1,1,1,1,0)),

		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing RandAngle,
								 Range	METRES10,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

			Posn	
				{Abs	{Pack_Target},
	  			 Abs	{Y HeightSize},	
				 Rel	{Bearing {Select RandAngle,7,ANGLES_45Deg},
						 Range	{Select 0,RangeStepSize,METRES1000},
						 Pitch	ANGLES_0Deg
						}
				},

			AirItem  	
			{
				Scram_G7_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RED,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		}
	};
//**************************************************************************
//FLYBY
 	BattleField
	{
		FileName	FIL_deathmatch7= death7.BF,
		Setval	{FriendHomeBase, UID_AfRdSinuiju},
		Setval	{EnemyScoutHomeBase, UID_AfRdSinuiju},
		Setval	{FriendHomeBase, UID_AfRdSinuiju},
		Setval	{EnemyScoutHomeBase, UID_AfRdSinuiju},
		Setval	{Pack_Target, UID_StSeoul},
	 	Setval	{RangeStepSize, Int {Random 0,7,1}},
	 	Setval	{HeightSize, Y {Random FT_4000,21,FT_1000}},
	 	Setval	{RandAngle, Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg}},

		AirGroup
		{
			Route	
			{
				WayPoint	WP_D7_00 =
				{
					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y {Random HeightSize,10,FT_100}},	
						 Rel	{Bearing {Select RandAngle,1,ANGLES_0Deg},
								 Range	{Select METRES250,3,METRES500},
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	WP_D7_00,
						 Rel	{Bearing {Select RandAngle,1,ANGLES_270Deg},
								 Range	METRES500,
								 Pitch	ANGLES_0Deg
								}
						},

			AirItem  	
			{
				Type	Scram_G0_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RED,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		},
//NUMBER 2
		AirGroup
		{
			Route	
			{
				WayPoint	WP_D7_01 =
				{
					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y {Random HeightSize,10,FT_100}},	
						 Rel	{Bearing {Select RandAngle,1,ANGLES_0Deg},
								 Range	{Select METRES250,2,METRES500},
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	WP_D7_01,
						 Rel	{Bearing {Select RandAngle,1,ANGLES_90Deg},
								 Range	METRES500,
								 Pitch	ANGLES_0Deg
								}
						},

			AirItem  	
			{
				Type	Scram_G1_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RED,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		},
//NUMBER 3
		AirGroup
		{
			Route	
			{
				WayPoint	WP_D7_02 =
				{
					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y {Random HeightSize,10,FT_100}},	
						 Rel	{Bearing {Select RandAngle,1,ANGLES_0Deg},
								 Range	{Select METRES250,1,METRES500},
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	WP_D7_02,
						 Rel	{Bearing {Select RandAngle,1,ANGLES_270Deg},
								 Range	METRES500,
								 Pitch	ANGLES_0Deg
								}
						},

			AirItem  	
			{
				Type	Scram_G2_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RED,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		},
//NUMBER 4
		AirGroup
		{
			Route	
			{
				WayPoint	WP_D7_03 =
				{
					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y {Random HeightSize,10,FT_100}},	
						 Rel	{Bearing {Select RandAngle,1,ANGLES_0Deg},
								 Range	{Select METRES250,0,METRES500},
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	WP_D7_03,
						 Rel	{Bearing {Select RandAngle,1,ANGLES_90Deg},
								 Range	METRES500,
								 Pitch	ANGLES_0Deg
								}
						},

			AirItem  	
			{
				Type	Scram_G3_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RED,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		},
//NUMBER 5
		AirGroup
		{
			Route	
			{
				WayPoint	WP_D7_04 =
				{
					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y {Random HeightSize,10,FT_100}},	
						 Rel	{Bearing {Select RandAngle,1,ANGLES_180Deg},
								 Range	{Select METRES250,0,METRES500},
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	WP_D7_04,
						 Rel	{Bearing {Select RandAngle,1,ANGLES_270Deg},
								 Range	METRES500,
								 Pitch	ANGLES_0Deg
								}
						},

			AirItem  	
			{
				Type	Scram_G4_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RED,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		},
//NUMBER 6
		AirGroup
		{
			Route	
			{
				WayPoint	WP_D7_05 =
				{
					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y {Random HeightSize,10,FT_100}},	
						 Rel	{Bearing {Select RandAngle,1,ANGLES_180Deg},
								 Range	{Select METRES250,1,METRES500},
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	WP_D7_05,
						 Rel	{Bearing {Select RandAngle,1,ANGLES_270Deg},
								 Range	METRES500,
								 Pitch	ANGLES_0Deg
								}
						},

			AirItem  	
			{
				Type	Scram_G5_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RED,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		},
//NUMBER 7
		AirGroup
		{
			Route	
			{
				WayPoint	WP_D7_06 =
				{
					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y {Random HeightSize,10,FT_100}},	
						 Rel	{Bearing {Select RandAngle,1,ANGLES_180Deg},
								 Range	{Select METRES250,2,METRES500},
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	WP_D7_06,
						 Rel	{Bearing {Select RandAngle,1,ANGLES_90Deg},
								 Range	METRES500,
								 Pitch	ANGLES_0Deg
								}
						},

			AirItem  	
			{
				Type	Scram_G6_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RED,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		},
//NUMBER 8
		AirGroup
		{
			Route	
			{
				WayPoint	WP_D7_07 =
				{
					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y {Random HeightSize,10,FT_100}},	
						 Rel	{Bearing {Select RandAngle,1,ANGLES_180Deg},
								 Range	{Select METRES250,3,METRES500},
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	WP_D7_07,
						 Rel	{Bearing {Select RandAngle,1,ANGLES_90Deg},
								 Range	METRES500,
								 Pitch	ANGLES_0Deg
								}
						},

			AirItem  	
			{
				Type	Scram_G7_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RED,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		}
	};
//-----------------------------------------------------------------
//8 team play battlefields
//-----------------------------------------------------------------
//TEAM, NO ADVANTAGE


 	BattleField
	{
		FileName	FIL_teamplay0= teamply0.BF,

	 	Setval	{RandAngle, Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg}},
		Setval	{Pack_Target, UID_StSeoul},
	 	Setval	{HeightSize, Y {Random FT_4000,21,FT_1000}},

//AC 00--------------

	 	Setval	{EncounterSize, Int {List  Scram_G0_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
	 	Setval	{AngleStepSize, Int {List  EncounterSize,1,3)),
	 	Setval	{HeightStepSize, Int {List  EncounterSize,0,1)),
	 	Setval	{NAT_ENEMY, Side {List  Scram_G0_Squad,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED)),

		SimpleItem	Item_Team00_End00 =	
		{
  			Posn	
					{Abs	Pack_Target, 
				 	 Abs	{Y HeightSize},
					 	 	Rel	{Bearing {Select RandAngle,AngleStepSize,ANGLES_90Deg},
						 	Range	METRES500
							} 
					},
			UIDBand		AmberCivilianBAND,
			Shape		EMPTY
		},

		SimpleItem	Item_Team00_Start00 =	
		{
			Posn		
					{Abs	Item_Team00_End00, 
				 	 Abs	{Y HeightSize},
					 	 	Rel	{Bearing {Select RandAngle,HeightStepSize,ANGLES_180Deg},
						 	Range	METRES1000
							} 
					},
			UIDBand		AmberCivilianBAND,
			Shape		EMPTY
		},

		AirGroup	
		{
			Route	
			{
				WayPoint
				{
					Posn	{Abs Item_Team00_End00},	
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AfBlKimpo}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
			Posn		
					{Abs	Item_Team00_Start00, 
					 Rel	{Intercept 	{Item_Team00_Start00,Item_Team00_End00},
							 Bearing	ANGLES_135Deg,
							 Range		{Select 0,0,FT_200},
							 Pitch		ANGLES_0Deg
							}
					},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQUAD_COMBAT_FLATV,

			AirItem	 
			{
				Scram_G0_Squad,
				Home	UID_AfBlKimpo,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},

//AC 1--------------

	 	Setval	{EncounterSize, Int {List  Scram_G1_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
	 	Setval	{AngleStepSize, Int {List  EncounterSize,1,3)),
	 	Setval	{HeightStepSize, Int {List  EncounterSize,0,1)),
	 	Setval	{NAT_ENEMY, Side {List  Scram_G1_Squad,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED)),

		SimpleItem	Item_Team00_End01 =	
		{
  			Posn	
					{Abs	Pack_Target, 
				 	 Abs	{Y HeightSize},
					 	 	Rel	{Bearing {Select RandAngle,AngleStepSize,ANGLES_90Deg},
						 	Range	METRES500
							} 
					},
			UIDBand		AmberCivilianBAND,
			Shape		EMPTY
		},

		SimpleItem	Item_Team00_Start01 =	
		{
			Posn		
					{Abs	Item_Team00_End01, 
				 	 Abs	{Y HeightSize},
					 	 	Rel	{Bearing {Select RandAngle,HeightStepSize,ANGLES_180Deg},
						 	Range	METRES1000
							} 
					},
			UIDBand		AmberCivilianBAND,
			Shape		EMPTY
		},

		AirGroup	
		{
			Route	
			{
				WayPoint
				{
					Posn	{Abs Item_Team00_End01},	
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AfBlKimpo}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
			Posn		
					{Abs	Item_Team00_Start01, 
					 Rel	{Intercept 	{Item_Team00_Start01,Item_Team00_End01},
							 Bearing	ANGLES_135Deg,
							 Range		{Select 0,1,FT_200},
							 Pitch		ANGLES_0Deg
							}
					},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQUAD_COMBAT_FLATV,

			AirItem	 
			{
				Scram_G1_Squad,
				Home	UID_AfBlKimpo,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},

//AC 2--------------

	 	Setval	{EncounterSize, Int {List  Scram_G2_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
	 	Setval	{AngleStepSize, Int {List  EncounterSize,1,3)),
	 	Setval	{HeightStepSize, Int {List  EncounterSize,0,1)),
	 	Setval	{NAT_ENEMY, Side {List  Scram_G2_Squad,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED)),

		SimpleItem	Item_Team00_End02 =	
		{
  			Posn	
					{Abs	Pack_Target, 
				 	 Abs	{Y HeightSize},
					 	 	Rel	{Bearing {Select RandAngle,AngleStepSize,ANGLES_90Deg},
						 	Range	METRES500
							} 
					},
			UIDBand		AmberCivilianBAND,
			Shape		EMPTY
		},

		SimpleItem	Item_Team00_Start02 =	
		{
			Posn		
					{Abs	Item_Team00_End02, 
				 	 Abs	{Y HeightSize},
					 	 	Rel	{Bearing {Select RandAngle,HeightStepSize,ANGLES_180Deg},
						 	Range	METRES1000
							} 
					},
			UIDBand		AmberCivilianBAND,
			Shape		EMPTY
		},

		AirGroup	
		{
			Route	
			{
				WayPoint
				{
					Posn	{Abs Item_Team00_End02},	
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AfBlKimpo}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
			Posn		
					{Abs	Item_Team00_Start02, 
					 Rel	{Intercept 	{Item_Team00_Start02,Item_Team00_End02},
							 Bearing	ANGLES_135Deg,
							 Range		{Select 0,2,FT_200},
							 Pitch		ANGLES_0Deg
							}
					},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQUAD_COMBAT_FLATV,

			AirItem	 
			{
				Scram_G2_Squad,
				Home	UID_AfBlKimpo,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},

//AC 3--------------

	 	Setval	{EncounterSize, Int {List  Scram_G3_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
	 	Setval	{AngleStepSize, Int {List  EncounterSize,1,3)),
	 	Setval	{HeightStepSize, Int {List  EncounterSize,0,1)),
	 	Setval	{NAT_ENEMY, Side {List  Scram_G3_Squad,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED)),

		SimpleItem	Item_Team00_End03 =	
		{
  			Posn	
					{Abs	Pack_Target, 
				 	 Abs	{Y HeightSize},
					 	 	Rel	{Bearing {Select RandAngle,AngleStepSize,ANGLES_90Deg},
						 	Range	METRES500
							} 
					},
			UIDBand		AmberCivilianBAND,
			Shape		EMPTY
		},

		SimpleItem	Item_Team00_Start03 =	
		{
			Posn		
					{Abs	Item_Team00_End03, 
				 	 Abs	{Y HeightSize},
					 	 	Rel	{Bearing {Select RandAngle,HeightStepSize,ANGLES_180Deg},
						 	Range	METRES1000
							} 
					},
			UIDBand		AmberCivilianBAND,
			Shape		EMPTY
		},

		AirGroup	
		{
			Route	
			{
				WayPoint
				{
					Posn	{Abs Item_Team00_End03},	
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AfBlKimpo}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
			Posn		
					{Abs	Item_Team00_Start03, 
					 Rel	{Intercept 	{Item_Team00_Start03,Item_Team00_End03},
							 Bearing	ANGLES_135Deg,
							 Range		{Select 0,3,FT_200},
							 Pitch		ANGLES_0Deg
							}
					},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQUAD_COMBAT_FLATV,

			AirItem	 
			{
				Scram_G3_Squad,
				Home	UID_AfBlKimpo,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},

//AC 4--------------

	 	Setval	{EncounterSize, Int {List  Scram_G4_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
	 	Setval	{AngleStepSize, Int {List  EncounterSize,1,3)),
	 	Setval	{HeightStepSize, Int {List  EncounterSize,0,1)),
	 	Setval	{NAT_ENEMY, Side {List  Scram_G4_Squad,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED)),

		SimpleItem	Item_Team00_End04 =	
		{
  			Posn	
					{Abs	Pack_Target, 
				 	 Abs	{Y HeightSize},
					 	 	Rel	{Bearing {Select RandAngle,AngleStepSize,ANGLES_90Deg},
						 	Range	METRES500
							} 
					},
			UIDBand		AmberCivilianBAND,
			Shape		EMPTY
		},

		SimpleItem	Item_Team00_Start04 =	
		{
			Posn		
					{Abs	Item_Team00_End04, 
				 	 Abs	{Y HeightSize},
					 	 	Rel	{Bearing {Select RandAngle,HeightStepSize,ANGLES_180Deg},
						 	Range	METRES1000
							} 
					},
			UIDBand		AmberCivilianBAND,
			Shape		EMPTY
		},

		AirGroup	
		{
			Route	
			{
				WayPoint
				{
					Posn	{Abs Item_Team00_End04},	
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AfBlKimpo}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
			Posn		
					{Abs	Item_Team00_Start04, 
					 Rel	{Intercept 	{Item_Team00_Start04,Item_Team00_End04},
							 Bearing	ANGLES_135Deg,
							 Range		{Select 0,4,FT_200},
							 Pitch		ANGLES_0Deg
							}
					},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQUAD_COMBAT_FLATV,

			AirItem	 
			{
				Scram_G4_Squad,
				Home	UID_AfBlKimpo,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},

//AC 5--------------

	 	Setval	{EncounterSize, Int {List  Scram_G5_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
	 	Setval	{AngleStepSize, Int {List  EncounterSize,1,3)),
	 	Setval	{HeightStepSize, Int {List  EncounterSize,0,1)),
	 	Setval	{NAT_ENEMY, Side {List  Scram_G5_Squad,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED)),

		SimpleItem	Item_Team00_End05 =	
		{
  			Posn	
					{Abs	Pack_Target, 
				 	 Abs	{Y HeightSize},
					 	 	Rel	{Bearing {Select RandAngle,AngleStepSize,ANGLES_90Deg},
						 	Range	METRES500
							} 
					},
			UIDBand		AmberCivilianBAND,
			Shape		EMPTY
		},

		SimpleItem	Item_Team00_Start05 =	
		{
			Posn		
					{Abs	Item_Team00_End05, 
				 	 Abs	{Y HeightSize},
					 	 	Rel	{Bearing {Select RandAngle,HeightStepSize,ANGLES_180Deg},
						 	Range	METRES1000
							} 
					},
			UIDBand		AmberCivilianBAND,
			Shape		EMPTY
		},

		AirGroup	
		{
			Route	
			{
				WayPoint
				{
					Posn	{Abs Item_Team00_End05},	
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AfBlKimpo}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
			Posn		
					{Abs	Item_Team00_Start05, 
					 Rel	{Intercept 	{Item_Team00_Start05,Item_Team00_End05},
							 Bearing	ANGLES_135Deg,
							 Range		{Select 0,5,FT_200},
							 Pitch		ANGLES_0Deg
							}
					},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQUAD_COMBAT_FLATV,

			AirItem	 
			{
				Scram_G5_Squad,
				Home	UID_AfBlKimpo,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},

//AC 6--------------

	 	Setval	{EncounterSize, Int {List  Scram_G6_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
	 	Setval	{AngleStepSize, Int {List  EncounterSize,1,3)),
	 	Setval	{HeightStepSize, Int {List  EncounterSize,0,1)),
	 	Setval	{NAT_ENEMY, Side {List  Scram_G6_Squad,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED)),

		SimpleItem	Item_Team00_End06 =	
		{
  			Posn	
					{Abs	Pack_Target, 
				 	 Abs	{Y HeightSize},
					 	 	Rel	{Bearing {Select RandAngle,AngleStepSize,ANGLES_90Deg},
						 	Range	METRES500
							} 
					},
			UIDBand		AmberCivilianBAND,
			Shape		EMPTY
		},

		SimpleItem	Item_Team00_Start06 =	
		{
			Posn		
					{Abs	Item_Team00_End06, 
				 	 Abs	{Y HeightSize},
					 	 	Rel	{Bearing {Select RandAngle,HeightStepSize,ANGLES_180Deg},
						 	Range	METRES1000
							} 
					},
			UIDBand		AmberCivilianBAND,
			Shape		EMPTY
		},

		AirGroup	
		{
			Route	
			{
				WayPoint
				{
					Posn	{Abs Item_Team00_End06},	
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AfBlKimpo}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
			Posn		
					{Abs	Item_Team00_Start06, 
					 Rel	{Intercept 	{Item_Team00_Start06,Item_Team00_End06},
							 Bearing	ANGLES_135Deg,
							 Range		{Select 0,6,FT_200},
							 Pitch		ANGLES_0Deg
							}
					},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQUAD_COMBAT_FLATV,

			AirItem	 
			{
				Scram_G6_Squad,
				Home	UID_AfBlKimpo,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},

//AC 7--------------

	 	Setval	{EncounterSize, Int {List  Scram_G7_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
	 	Setval	{AngleStepSize, Int {List  EncounterSize,1,3)),
	 	Setval	{HeightStepSize, Int {List  EncounterSize,0,1)),
	 	Setval	{NAT_ENEMY, Side {List  Scram_G7_Squad,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED)),

		SimpleItem	Item_Team00_End07 =	
		{
  			Posn	
					{Abs	Pack_Target, 
				 	 Abs	{Y HeightSize},
					 	 	Rel	{Bearing {Select RandAngle,AngleStepSize,ANGLES_90Deg},
						 	Range	METRES500
							} 
					},
			UIDBand		AmberCivilianBAND,
			Shape		EMPTY
		},

		SimpleItem	Item_Team00_Start07 =	
		{
			Posn		
					{Abs	Item_Team00_End07, 
				 	 Abs	{Y HeightSize},
					 	 	Rel	{Bearing {Select RandAngle,HeightStepSize,ANGLES_180Deg},
						 	Range	METRES1000
							} 
					},
			UIDBand		AmberCivilianBAND,
			Shape		EMPTY
		},

		AirGroup	
		{
			Route	
			{
				WayPoint
				{
					Posn	{Abs Item_Team00_End07},	
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AfBlKimpo}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
			Posn		
					{Abs	Item_Team00_Start07, 
					 Rel	{Intercept 	{Item_Team00_Start07,Item_Team00_End07},
							 Bearing	ANGLES_135Deg,
							 Range		{Select 0,7,FT_200},
							 Pitch		ANGLES_0Deg
							}
					},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQUAD_COMBAT_FLATV,

			AirItem	 
			{
				Scram_G7_Squad,
				Home	UID_AfBlKimpo,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		}
	};

//-------------------------------------------------------------------------
//TEAM01: FLIGHTS, UN ADVANTAGE

//EncounterSize is the side: 0 is red, 1 is blue
//RandAngle is the Angle that UN come in at


 	BattleField
	{
		FileName	FIL_teamplay1= teamply1.BF,
	 	Setval	{RandAngle, Bearing {Random ANGLES_135Deg,90,ANGLES_1Deg}},
		Setval	{Pack_Target, UID_StSeoul},
	 	Setval	{HeightSize, Y {Random FT_4000,25,FT_1000}},

//AC 00--------------

	 	Setval	{EncounterSize, Int {List  Scram_G0_Squad,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0)),
	 	Setval	{NAT_ENEMY, Side {List  Scram_G0_Squad,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED)),

		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	Pack_Target, 
				 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_1000}},
					 	 		 	 Rel	{Bearing ANGLES_0Deg,
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES1000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AfBlKimpo}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
			Posn		
					{Abs	Pack_Target, 
		 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_1000}},
					 Rel	{Bearing	{Select 0,EncounterSize,RandAngle},
							 Range		{Select 0,EncounterSize,METRES500},
							 Pitch		ANGLES_0Deg
							}
					},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQUAD_COMBAT_FLATV,

			AirItem	 
			{
				Scram_G0_Squad,
				Home	UID_AfBlKimpo,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},

//AC 1--------------

	 	Setval	{EncounterSize, Int {List  Scram_G1_Squad,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0)),
	 	Setval	{NAT_ENEMY, Side {List  Scram_G1_Squad,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED)),

		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	Pack_Target, 
				 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_1000}},
					 	 		 	 Rel	{Bearing ANGLES_0Deg,
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES1000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AfBlKimpo}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
			Posn		
					{Abs	Pack_Target, 
		 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_1000}},
					 Rel	{Bearing	{Select 0,EncounterSize,RandAngle},
							 Range		{Select FT_200,EncounterSize,METRES500},
							 Pitch		ANGLES_0Deg
							}
					},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQUAD_COMBAT_FLATV,

			AirItem	 
			{
				Scram_G1_Squad,
				Home	UID_AfBlKimpo,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},

//AC 2--------------


	 	Setval	{EncounterSize, Int {List  Scram_G2_Squad,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0)),
	 	Setval	{NAT_ENEMY, Side {List  Scram_G2_Squad,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED)),

		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	Pack_Target, 
				 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_1000}},
					 	 		 	 Rel	{Bearing ANGLES_0Deg,
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES1000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AfBlKimpo}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
			Posn		
					{Abs	Pack_Target, 
		 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_1000}},
					 Rel	{Bearing	{Select 0,EncounterSize,RandAngle},
							 Range		{Select FT_400,EncounterSize,METRES500},
							 Pitch		ANGLES_0Deg
							}
					},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQUAD_COMBAT_FLATV,

			AirItem	 
			{
				Scram_G2_Squad,
				Home	UID_AfBlKimpo,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},

//AC 3--------------

	 	Setval	{EncounterSize, Int {List  Scram_G3_Squad,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0)),
	 	Setval	{NAT_ENEMY, Side {List  Scram_G3_Squad,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED)),

		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	Pack_Target, 
				 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_1000}},
					 	 		 	 Rel	{Bearing ANGLES_0Deg,
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES1000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AfBlKimpo}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
			Posn		
					{Abs	Pack_Target, 
		 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_1000}},
					 Rel	{Bearing	{Select 0,EncounterSize,RandAngle},
							 Range		{Select FT_600,EncounterSize,METRES500},
							 Pitch		ANGLES_0Deg
							}
					},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQUAD_COMBAT_FLATV,

			AirItem	 
			{
				Scram_G3_Squad,
				Home	UID_AfBlKimpo,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},

//AC 4--------------


	 	Setval	{EncounterSize, Int {List  Scram_G4_Squad,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0)),
	 	Setval	{NAT_ENEMY, Side {List  Scram_G4_Squad,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED)),

		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	Pack_Target, 
				 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_1000}},
					 	 		 	 Rel	{Bearing ANGLES_0Deg,
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES1000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AfBlKimpo}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
			Posn		
					{Abs	Pack_Target, 
		 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_1000}},
					 Rel	{Bearing	{Select 0,EncounterSize,RandAngle},
							 Range		{Select FT_800,EncounterSize,METRES500},
							 Pitch		ANGLES_0Deg
							}
					},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQUAD_COMBAT_FLATV,

			AirItem	 
			{
				Scram_G4_Squad,
				Home	UID_AfBlKimpo,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},

//AC 5--------------

	 	Setval	{EncounterSize, Int {List  Scram_G5_Squad,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0)),
	 	Setval	{NAT_ENEMY, Side {List  Scram_G5_Squad,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED)),

		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	Pack_Target, 
				 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_1000}},
					 	 		 	 Rel	{Bearing ANGLES_0Deg,
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES1000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AfBlKimpo}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
			Posn		
					{Abs	Pack_Target, 
		 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_1000}},
					 Rel	{Bearing	{Select 0,EncounterSize,RandAngle},
							 Range		{Select FT_1000,EncounterSize,METRES500},
							 Pitch		ANGLES_0Deg
							}
					},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQUAD_COMBAT_FLATV,

			AirItem	 
			{
				Scram_G5_Squad,
				Home	UID_AfBlKimpo,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},

//AC 6--------------


	 	Setval	{EncounterSize, Int {List  Scram_G6_Squad,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0)),
	 	Setval	{NAT_ENEMY, Side {List  Scram_G6_Squad,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED)),

		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	Pack_Target, 
				 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_1000}},
					 	 		 	 Rel	{Bearing ANGLES_0Deg,
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES1000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AfBlKimpo}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
			Posn		
					{Abs	Pack_Target, 
		 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_1000}},
					 Rel	{Bearing	{Select 0,EncounterSize,RandAngle},
							 Range		{Select FT_1200,EncounterSize,METRES500},
							 Pitch		ANGLES_0Deg
							}
					},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQUAD_COMBAT_FLATV,

			AirItem	 
			{
				Scram_G6_Squad,
				Home	UID_AfBlKimpo,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},

//AC 7--------------


	 	Setval	{EncounterSize, Int {List  Scram_G7_Squad,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0)),
	 	Setval	{NAT_ENEMY, Side {List  Scram_G7_Squad,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED)),

		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	Pack_Target, 
				 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_1000}},
					 	 		 	 Rel	{Bearing ANGLES_0Deg,
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES1000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AfBlKimpo}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
			Posn		
					{Abs	Pack_Target, 
		 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_1000}},
					 Rel	{Bearing	{Select 0,EncounterSize,RandAngle},
							 Range		{Select FT_1400,EncounterSize,METRES500},
							 Pitch		ANGLES_0Deg
							}
					},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQUAD_COMBAT_FLATV,

			AirItem	 
			{
				Scram_G7_Squad,
				Home	UID_AfBlKimpo,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		}
	};

//-------------------------------------------------------------------------
//TEAM02: FLIGHTS, RED ADVANTAGE

//EncounterSize is the side: 1 is red, 0 is blue
//RandAngle is the Angle that UN come in at

 	BattleField
	{
		FileName	FIL_teamplay2= teamply2.BF,
	 	Setval	{RandAngle, Bearing {Random ANGLES_135Deg,90,ANGLES_1Deg}},
		Setval	{Pack_Target, UID_StSeoul},
	 	Setval	{HeightSize, Y {Random FT_4000,25,FT_1000}},

//AC 00--------------

	 	Setval	{EncounterSize, Int {List  Scram_G0_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
	 	Setval	{NAT_ENEMY, Side {List  Scram_G0_Squad,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED)),


		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	Pack_Target, 
				 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_1000}},
					 	 		 	 Rel	{Bearing ANGLES_0Deg,
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES1000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AfBlKimpo}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
			Posn		
					{Abs	Pack_Target, 
		 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_1000}},
					 Rel	{Bearing	{Select 0,EncounterSize,RandAngle},
							 Range		{Select 0,EncounterSize,METRES500},
							 Pitch		ANGLES_0Deg
							}
					},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQUAD_COMBAT_FLATV,

			AirItem	 
			{
				Scram_G0_Squad,
				Home	UID_AfBlKimpo,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},

//AC 1--------------

	 	Setval	{EncounterSize, Int {List  Scram_G1_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
	 	Setval	{NAT_ENEMY, Side {List  Scram_G1_Squad,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED)),

		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	Pack_Target, 
				 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_1000}},
					 	 		 	 Rel	{Bearing ANGLES_0Deg,
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES1000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AfBlKimpo}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
			Posn		
					{Abs	Pack_Target, 
		 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_1000}},
					 Rel	{Bearing	{Select 0,EncounterSize,RandAngle},
							 Range		{Select FT_200,EncounterSize,METRES500},
							 Pitch		ANGLES_0Deg
							}
					},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQUAD_COMBAT_FLATV,

			AirItem	 
			{
				Scram_G1_Squad,
				Home	UID_AfBlKimpo,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},

//AC 2--------------


	 	Setval	{EncounterSize, Int {List  Scram_G2_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
	 	Setval	{NAT_ENEMY, Side {List  Scram_G2_Squad,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED)),


		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	Pack_Target, 
				 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_1000}},
					 	 		 	 Rel	{Bearing ANGLES_0Deg,
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES1000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AfBlKimpo}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
			Posn		
					{Abs	Pack_Target, 
		 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_1000}},
					 Rel	{Bearing	{Select 0,EncounterSize,RandAngle},
							 Range		{Select FT_400,EncounterSize,METRES500},
							 Pitch		ANGLES_0Deg
							}
					},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQUAD_COMBAT_FLATV,

			AirItem	 
			{
				Scram_G2_Squad,
				Home	UID_AfBlKimpo,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},

//AC 3--------------

	 	Setval	{EncounterSize, Int {List  Scram_G3_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
	 	Setval	{NAT_ENEMY, Side {List  Scram_G3_Squad,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED)),

		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	Pack_Target, 
				 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_1000}},
					 	 		 	 Rel	{Bearing ANGLES_0Deg,
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES1000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AfBlKimpo}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
			Posn		
					{Abs	Pack_Target, 
		 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_1000}},
					 Rel	{Bearing	{Select 0,EncounterSize,RandAngle},
							 Range		{Select FT_600,EncounterSize,METRES500},
							 Pitch		ANGLES_0Deg
							}
					},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQUAD_COMBAT_FLATV,

			AirItem	 
			{
				Scram_G3_Squad,
				Home	UID_AfBlKimpo,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},

//AC 4--------------


	 	Setval	{EncounterSize, Int {List  Scram_G4_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
	 	Setval	{NAT_ENEMY, Side {List  Scram_G4_Squad,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED)),


		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	Pack_Target, 
				 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_1000}},
					 	 		 	 Rel	{Bearing ANGLES_0Deg,
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES1000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AfBlKimpo}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
			Posn		
					{Abs	Pack_Target, 
		 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_1000}},
					 Rel	{Bearing	{Select 0,EncounterSize,RandAngle},
							 Range		{Select FT_800,EncounterSize,METRES500},
							 Pitch		ANGLES_0Deg
							}
					},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQUAD_COMBAT_FLATV,

			AirItem	 
			{
				Scram_G4_Squad,
				Home	UID_AfBlKimpo,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},

//AC 5--------------

	 	Setval	{EncounterSize, Int {List  Scram_G5_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
	 	Setval	{NAT_ENEMY, Side {List  Scram_G5_Squad,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED)),


		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	Pack_Target, 
				 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_1000}},
					 	 		 	 Rel	{Bearing ANGLES_0Deg,
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES1000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AfBlKimpo}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
			Posn		
					{Abs	Pack_Target, 
		 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_1000}},
					 Rel	{Bearing	{Select 0,EncounterSize,RandAngle},
							 Range		{Select FT_1000,EncounterSize,METRES500},
							 Pitch		ANGLES_0Deg
							}
					},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQUAD_COMBAT_FLATV,

			AirItem	 
			{
				Scram_G5_Squad,
				Home	UID_AfBlKimpo,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},

//AC 6--------------


	 	Setval	{EncounterSize, Int {List  Scram_G6_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
	 	Setval	{NAT_ENEMY, Side {List  Scram_G6_Squad,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED)),


		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	Pack_Target, 
				 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_1000}},
					 	 		 	 Rel	{Bearing ANGLES_0Deg,
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES1000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AfBlKimpo}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
			Posn		
					{Abs	Pack_Target, 
		 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_1000}},
					 Rel	{Bearing	{Select 0,EncounterSize,RandAngle},
							 Range		{Select FT_1200,EncounterSize,METRES500},
							 Pitch		ANGLES_0Deg
							}
					},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQUAD_COMBAT_FLATV,

			AirItem	 
			{
				Scram_G6_Squad,
				Home	UID_AfBlKimpo,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},

//AC 7--------------


	 	Setval	{EncounterSize, Int {List  Scram_G7_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
	 	Setval	{NAT_ENEMY, Side {List  Scram_G7_Squad,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED)),


		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	Pack_Target, 
				 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_1000}},
					 	 		 	 Rel	{Bearing ANGLES_0Deg,
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES1000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AfBlKimpo}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
			Posn		
					{Abs	Pack_Target, 
		 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_1000}},
					 Rel	{Bearing	{Select 0,EncounterSize,RandAngle},
							 Range		{Select FT_1400,EncounterSize,METRES500},
							 Pitch		ANGLES_0Deg
							}
					},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQUAD_COMBAT_FLATV,

			AirItem	 
			{
				Scram_G7_Squad,
				Home	UID_AfBlKimpo,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		}

	};

//-------------------------------------------------------------------------
//TEAM03: FLIGHTS, RANDOM ADVANTAGE

//EncounterSize is the side: 
//RangeStepsize is the side index:
//RandAngle is the Angle that UN come in at

 	BattleField
	{
		FileName	FIL_teamplay3= teamply3.BF,
	 	Setval	{RandAngle, Bearing {Random ANGLES_0Deg,2,ANGLES_180Deg}},
		Setval	{Pack_Target, UID_StSeoul},
	 	Setval	{HeightSize, Y {Random FT_4000,25,FT_1000}},
		Setval	{RangeStepSize, Int {Random 0,2,1}},

//AC 00--------------

	 	Setval	{EncounterSize, Int {List  Scram_G0_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
	 	Setval	{NAT_ENEMY, Side {List  Scram_G0_Squad,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED)),


		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	Pack_Target, 
				 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_0}},
					 	 		 	 Rel	{Bearing ANGLES_0Deg,
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES1000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AfBlKimpo}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
			Posn		
					{Abs	Pack_Target, 
		 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_0}},
					 Rel	{Bearing	{Select 0,EncounterSize,RandAngle},
							 Range		{Select 0,EncounterSize,METRES500},
							 Pitch		ANGLES_0Deg
							}
					},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQUAD_COMBAT_FLATV,

			AirItem	 
			{
				Scram_G0_Squad,
				Home	UID_AfBlKimpo,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},

//AC 1--------------

	 	Setval	{EncounterSize, Int {List  Scram_G1_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
	 	Setval	{NAT_ENEMY, Side {List  Scram_G1_Squad,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED)),

		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	Pack_Target, 
				 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_0}},
					 	 		 	 Rel	{Bearing ANGLES_0Deg,
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES1000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AfBlKimpo}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
			Posn		
					{Abs	Pack_Target, 
		 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_0}},
					 Rel	{Bearing	{Select 0,EncounterSize,RandAngle},
							 Range		{Select FT_200,EncounterSize,METRES500},
							 Pitch		ANGLES_0Deg
							}
					},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQUAD_COMBAT_FLATV,

			AirItem	 
			{
				Scram_G1_Squad,
				Home	UID_AfBlKimpo,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},

//AC 2--------------


	 	Setval	{EncounterSize, Int {List  Scram_G2_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
	 	Setval	{NAT_ENEMY, Side {List  Scram_G2_Squad,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED)),


		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	Pack_Target, 
				 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_0}},
					 	 		 	 Rel	{Bearing ANGLES_0Deg,
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES1000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AfBlKimpo}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
			Posn		
					{Abs	Pack_Target, 
		 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_0}},
					 Rel	{Bearing	{Select 0,EncounterSize,RandAngle},
							 Range		{Select FT_400,EncounterSize,METRES500},
							 Pitch		ANGLES_0Deg
							}
					},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQUAD_COMBAT_FLATV,

			AirItem	 
			{
				Scram_G2_Squad,
				Home	UID_AfBlKimpo,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},

//AC 3--------------

	 	Setval	{EncounterSize, Int {List  Scram_G3_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
	 	Setval	{NAT_ENEMY, Side {List  Scram_G3_Squad,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED)),

		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	Pack_Target, 
				 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_0}},
					 	 		 	 Rel	{Bearing ANGLES_0Deg,
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES1000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AfBlKimpo}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
			Posn		
					{Abs	Pack_Target, 
		 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_0}},
					 Rel	{Bearing	{Select 0,EncounterSize,RandAngle},
							 Range		{Select FT_600,EncounterSize,METRES500},
							 Pitch		ANGLES_0Deg
							}
					},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQUAD_COMBAT_FLATV,

			AirItem	 
			{
				Scram_G3_Squad,
				Home	UID_AfBlKimpo,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},

//AC 4--------------


	 	Setval	{EncounterSize, Int {List  Scram_G4_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
	 	Setval	{NAT_ENEMY, Side {List  Scram_G4_Squad,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED)),


		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	Pack_Target, 
				 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_0}},
					 	 		 	 Rel	{Bearing ANGLES_0Deg,
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES1000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AfBlKimpo}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
			Posn		
					{Abs	Pack_Target, 
		 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_0}},
					 Rel	{Bearing	{Select 0,EncounterSize,RandAngle},
							 Range		{Select FT_800,EncounterSize,METRES500},
							 Pitch		ANGLES_0Deg
							}
					},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQUAD_COMBAT_FLATV,

			AirItem	 
			{
				Scram_G4_Squad,
				Home	UID_AfBlKimpo,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},

//AC 5--------------

	 	Setval	{EncounterSize, Int {List  Scram_G5_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
	 	Setval	{NAT_ENEMY, Side {List  Scram_G5_Squad,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED)),


		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	Pack_Target, 
				 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_0}},
					 	 		 	 Rel	{Bearing ANGLES_0Deg,
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES1000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AfBlKimpo}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
			Posn		
					{Abs	Pack_Target, 
		 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_0}},
					 Rel	{Bearing	{Select 0,EncounterSize,RandAngle},
							 Range		{Select FT_0,EncounterSize,METRES500},
							 Pitch		ANGLES_0Deg
							}
					},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQUAD_COMBAT_FLATV,

			AirItem	 
			{
				Scram_G5_Squad,
				Home	UID_AfBlKimpo,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},

//AC 6--------------


	 	Setval	{EncounterSize, Int {List  Scram_G6_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
	 	Setval	{NAT_ENEMY, Side {List  Scram_G6_Squad,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED)),


		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	Pack_Target, 
				 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_0}},
					 	 		 	 Rel	{Bearing ANGLES_0Deg,
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES1000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AfBlKimpo}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
			Posn		
					{Abs	Pack_Target, 
		 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_0}},
					 Rel	{Bearing	{Select 0,EncounterSize,RandAngle},
							 Range		{Select FT_1200,EncounterSize,METRES500},
							 Pitch		ANGLES_0Deg
							}
					},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQUAD_COMBAT_FLATV,

			AirItem	 
			{
				Scram_G6_Squad,
				Home	UID_AfBlKimpo,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},

//AC 7--------------


	 	Setval	{EncounterSize, Int {List  Scram_G7_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
	 	Setval	{NAT_ENEMY, Side {List  Scram_G7_Squad,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED)),


		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	Pack_Target, 
				 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_0}},
					 	 		 	 Rel	{Bearing ANGLES_0Deg,
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES1000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AfBlKimpo}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
			Posn		
					{Abs	Pack_Target, 
		 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_0}},
					 Rel	{Bearing	{Select 0,EncounterSize,RandAngle},
							 Range		{Select FT_1400,EncounterSize,METRES500},
							 Pitch		ANGLES_0Deg
							}
					},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQUAD_COMBAT_FLATV,

			AirItem	 
			{
				Scram_G7_Squad,
				Home	UID_AfBlKimpo,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		}



	};


//-------------------------------------------------------------------------
//TEAM04: ELEMENTS SCATTERED

//EncounterSize is the side: 
//RandAngle is the Angle that each element comes in at
//AngleStepSize is their waypoint offset

 	BattleField
	{
		FileName	FIL_teamplay4= teamply4.BF,
		Setval	{Pack_Target, UID_StSeoul},
	 	Setval	{HeightSize, Y {Random FT_4000,25,FT_1000}},

//AC 00-------------- LEAD

	 	Setval	{EncounterSize, Int {List  Scram_G0_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
	 	Setval	{RandAngle, Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg}},
	 	Setval	{AngleStepSize, Int {Random 0,359,1}},
	 	Setval	{HeightStepSize, Int {Random 0,50,1}},
		Setval	{RangeStepSize, Int {Select 0,EncounterSize,1}},
		
	 	Setval	{NAT_ENEMY, Side {List  Scram_G0_Squad,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED)),

		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	Pack_Target, 
				 	 		 Abs	{Y {Select HeightSize,HeightStepSize,FT_100}},
					 	 		 	 Rel	{Bearing {Select 0,AngleStepSize,ANGLES_1Deg},
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES5000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AfBlKimpo}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
  					Posn	
							{Abs	Pack_Target, 
				 	 		 Abs	{Y {Select HeightSize,HeightStepSize,FT_100}},
					 	 		 	 Rel	{Bearing {Select RandAngle,RangeStepSize,ANGLES_180Deg},
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES1000
									} 
							},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQUAD_COMBAT_FLATV,

			AirItem	 
			{
				Scram_G0_Squad,
				Home	UID_AfBlKimpo,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},

//AC 1--------------	WINGMAN

	 	Setval	{EncounterSize, Int {List  Scram_G1_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
		Setval	{RangeStepSize, Int {Select 0,EncounterSize,1}},
		
	 	Setval	{NAT_ENEMY, Side {List  Scram_G1_Squad,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED)),

		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	Pack_Target, 
				 	 		 Abs	{Y {Select HeightSize,HeightStepSize,FT_100}},
					 	 		 	 Rel	{Bearing {Select 0,AngleStepSize,ANGLES_1Deg},
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES5000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AfBlKimpo}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
  					Posn	
							{Abs	Pack_Target, 
				 	 		 Abs	{Y {Select HeightSize,HeightStepSize,FT_100}},
					 	 		 	 Rel	{Bearing {Select RandAngle,RangeStepSize,ANGLES_180Deg},
									 Pitch	ANGLES_0Deg,
						 		 	 Range	{Select METRES1000,1,FT_250}
									} 
							},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQUAD_COMBAT_FLATV,

			AirItem	 
			{
				Scram_G1_Squad,
				Home	UID_AfBlKimpo,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},

//AC 02-------------- LEAD

	 	Setval	{EncounterSize, Int {List  Scram_G2_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
	 	Setval	{RandAngle, Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg}},
	 	Setval	{AngleStepSize, Int {Random 0,359,1}},
	 	Setval	{HeightStepSize, Int {Random 0,50,1}},
		Setval	{RangeStepSize, Int {Select 0,EncounterSize,1}},
		
	 	Setval	{NAT_ENEMY, Side {List  Scram_G2_Squad,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED)),

		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	Pack_Target, 
				 	 		 Abs	{Y {Select HeightSize,HeightStepSize,FT_100}},
					 	 		 	 Rel	{Bearing {Select 0,AngleStepSize,ANGLES_1Deg},
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES5000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AfBlKimpo}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
  					Posn	
							{Abs	Pack_Target, 
				 	 		 Abs	{Y {Select HeightSize,HeightStepSize,FT_100}},
					 	 		 	 Rel	{Bearing {Select RandAngle,RangeStepSize,ANGLES_180Deg},
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES1000
									} 
							},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQUAD_COMBAT_FLATV,

			AirItem	 
			{
				Scram_G2_Squad,
				Home	UID_AfBlKimpo,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},

//AC 3--------------	WINGMAN

	 	Setval	{EncounterSize, Int {List  Scram_G3_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
		Setval	{RangeStepSize, Int {Select 0,EncounterSize,1}},
	 	Setval	{NAT_ENEMY, Side {List  Scram_G3_Squad,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED)),
		

		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	Pack_Target, 
				 	 		 Abs	{Y {Select HeightSize,HeightStepSize,FT_100}},
					 	 		 	 Rel	{Bearing {Select 0,AngleStepSize,ANGLES_1Deg},
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES5000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AfBlKimpo}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
  					Posn	
							{Abs	Pack_Target, 
				 	 		 Abs	{Y {Select HeightSize,HeightStepSize,FT_100}},
					 	 		 	 Rel	{Bearing {Select RandAngle,RangeStepSize,ANGLES_180Deg},
									 Pitch	ANGLES_0Deg,
						 		 	 Range	{Select METRES1000,1,FT_250}
									} 
							},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQUAD_COMBAT_FLATV,

			AirItem	 
			{
				Scram_G3_Squad,
				Home	UID_AfBlKimpo,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},
//AC 04-------------- LEAD

	 	Setval	{EncounterSize, Int {List  Scram_G4_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
	 	Setval	{RandAngle, Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg}},
	 	Setval	{AngleStepSize, Int {Random 0,359,1}},
	 	Setval	{HeightStepSize, Int {Random 0,50,1}},
		Setval	{RangeStepSize, Int {Select 0,EncounterSize,1}},
		
	 	Setval	{NAT_ENEMY, Side {List  Scram_G4_Squad,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED)),

		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	Pack_Target, 
				 	 		 Abs	{Y {Select HeightSize,HeightStepSize,FT_100}},
					 	 		 	 Rel	{Bearing {Select 0,AngleStepSize,ANGLES_1Deg},
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES5000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AfBlKimpo}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
  					Posn	
							{Abs	Pack_Target, 
				 	 		 Abs	{Y {Select HeightSize,HeightStepSize,FT_100}},
					 	 		 	 Rel	{Bearing {Select RandAngle,RangeStepSize,ANGLES_180Deg},
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES1000
									} 
							},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQUAD_COMBAT_FLATV,

			AirItem	 
			{
				Scram_G4_Squad,
				Home	UID_AfBlKimpo,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},

//AC 5--------------	WINGMAN

	 	Setval	{EncounterSize, Int {List  Scram_G5_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
		Setval	{RangeStepSize, Int {Select 0,EncounterSize,1}},
		
	 	Setval	{NAT_ENEMY, Side {List  Scram_G5_Squad,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED)),

		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	Pack_Target, 
				 	 		 Abs	{Y {Select HeightSize,HeightStepSize,FT_100}},
					 	 		 	 Rel	{Bearing {Select 0,AngleStepSize,ANGLES_1Deg},
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES5000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AfBlKimpo}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
  					Posn	
							{Abs	Pack_Target, 
				 	 		 Abs	{Y {Select HeightSize,HeightStepSize,FT_100}},
					 	 		 	 Rel	{Bearing {Select RandAngle,RangeStepSize,ANGLES_180Deg},
									 Pitch	ANGLES_0Deg,
						 		 	 Range	{Select METRES1000,1,FT_250}
									} 
							},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQUAD_COMBAT_FLATV,

			AirItem	 
			{
				Scram_G5_Squad,
				Home	UID_AfBlKimpo,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},
//AC 06-------------- LEAD

	 	Setval	{EncounterSize, Int {List  Scram_G6_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
	 	Setval	{RandAngle, Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg}},
	 	Setval	{AngleStepSize, Int {Random 0,359,1}},
	 	Setval	{HeightStepSize, Int {Random 0,50,1}},
		Setval	{RangeStepSize, Int {Select 0,EncounterSize,1}},
		
	 	Setval	{NAT_ENEMY, Side {List  Scram_G6_Squad,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED)),

		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	Pack_Target, 
				 	 		 Abs	{Y {Select HeightSize,HeightStepSize,FT_100}},
					 	 		 	 Rel	{Bearing {Select 0,AngleStepSize,ANGLES_1Deg},
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES5000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AfBlKimpo}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
  					Posn	
							{Abs	Pack_Target, 
				 	 		 Abs	{Y {Select HeightSize,HeightStepSize,FT_100}},
					 	 		 	 Rel	{Bearing {Select RandAngle,RangeStepSize,ANGLES_180Deg},
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES1000
									} 
							},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQUAD_COMBAT_FLATV,

			AirItem	 
			{
				Scram_G6_Squad,
				Home	UID_AfBlKimpo,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},

//AC 7--------------	WINGMAN

	 	Setval	{EncounterSize, Int {List  Scram_G7_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
		Setval	{RangeStepSize, Int {Select 0,EncounterSize,1}},
		
	 	Setval	{NAT_ENEMY, Side {List  Scram_G7_Squad,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED)),

		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	Pack_Target, 
				 	 		 Abs	{Y {Select HeightSize,HeightStepSize,FT_100}},
					 	 		 	 Rel	{Bearing {Select 0,AngleStepSize,ANGLES_1Deg},
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES5000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AfBlKimpo}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
  					Posn	
							{Abs	Pack_Target, 
				 	 		 Abs	{Y {Select HeightSize,HeightStepSize,FT_100}},
					 	 		 	 Rel	{Bearing {Select RandAngle,RangeStepSize,ANGLES_180Deg},
									 Pitch	ANGLES_0Deg,
						 		 	 Range	{Select METRES1000,1,FT_250}
									} 
							},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQUAD_COMBAT_FLATV,

			AirItem	 
			{
				Scram_G7_Squad,
				Home	UID_AfBlKimpo,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		}
	};


//-------------------------------------------------------------------------
//TEAM05: ELEMENTS CLOSE

//EncounterSize is the side: 
//RandAngle is the Angle that each element comes in at
//AngleStepSize is their waypoint offset

 	BattleField
	{
		FileName	FIL_teamplay5= teamply5.BF,
		Setval	{Pack_Target, UID_StSeoul},
	 	Setval	{HeightSize, Y {Random FT_4000,25,FT_1000}},

//AC 00-------------- LEAD

	 	Setval	{EncounterSize, Int {List  Scram_G0_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
	 	Setval	{RandAngle, Bearing {Random ANGLES_135Deg,90,ANGLES_1Deg}},
		Setval	{RangeStepSize, Int {Random 0,11,1}},
		Setval	{HeightStepSize, Int {Random 0,20,1}},
	
	 	Setval	{NAT_ENEMY, Side {List  Scram_G0_Squad,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED)),
		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	Pack_Target, 
				 	 		 Abs	{Y {Select HeightSize,HeightStepSize,FT_100}},
					 	 		 	 Rel	{Bearing {Select RandAngle,EncounterSize,ANGLES_0Deg},
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES5000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AfBlKimpo}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
  					Posn	
							{Abs	Pack_Target, 
				 	 		 Abs	{Y {Select HeightSize,HeightStepSize,FT_100}},
					 	 		 	 Rel	{Bearing {Select RandAngle,EncounterSize,ANGLES_180Deg},
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES1000
									} 
							},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQUAD_COMBAT_FLATV,

			AirItem	 
			{
				Scram_G0_Squad,
				Home	UID_AfBlKimpo,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},

//AC 1--------------	WINGMAN

	 	Setval	{EncounterSize, Int {List  Scram_G1_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
		
	 	Setval	{NAT_ENEMY, Side {List  Scram_G1_Squad,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED)),
		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	Pack_Target, 
				 	 		 Abs	{Y {Select HeightSize,HeightStepSize,FT_100}},
					 	 		 	 Rel	{Bearing {Select RandAngle,EncounterSize,ANGLES_0Deg},
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES5000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AfBlKimpo}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
  					Posn	
							{Abs	Pack_Target, 
				 	 		 Abs	{Y {Select HeightSize,HeightStepSize,FT_100}},
					 	 		 	 Rel	{Bearing {Select RandAngle,EncounterSize,ANGLES_180Deg},
									 Pitch	ANGLES_0Deg,
						 		 	 Range	{Select METRES1000,1,FT_250}
									} 
							},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQUAD_COMBAT_FLATV,

			AirItem	 
			{
				Scram_G1_Squad,
				Home	UID_AfBlKimpo,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},

//AC 02-------------- LEAD

	 	Setval	{EncounterSize, Int {List  Scram_G2_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
	 	Setval	{RandAngle, Bearing {Random ANGLES_135Deg,90,ANGLES_1Deg}},
		Setval	{RangeStepSize, Int {Random 0,11,1}},
		Setval	{HeightStepSize, Int {Random 0,20,1}},
	
	 	Setval	{NAT_ENEMY, Side {List  Scram_G2_Squad,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED)),
		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	Pack_Target, 
				 	 		 Abs	{Y {Select HeightSize,HeightStepSize,FT_100}},
					 	 		 	 Rel	{Bearing {Select RandAngle,EncounterSize,ANGLES_0Deg},
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES5000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AfBlKimpo}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
  					Posn	
							{Abs	Pack_Target, 
				 	 		 Abs	{Y {Select HeightSize,HeightStepSize,FT_100}},
					 	 		 	 Rel	{Bearing {Select RandAngle,EncounterSize,ANGLES_180Deg},
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES1000
									} 
							},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQUAD_COMBAT_FLATV,

			AirItem	 
			{
				Scram_G2_Squad,
				Home	UID_AfBlKimpo,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},

//AC 3--------------	WINGMAN

	 	Setval	{EncounterSize, Int {List  Scram_G3_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
		
	 	Setval	{NAT_ENEMY, Side {List  Scram_G3_Squad,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED)),
		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	Pack_Target, 
				 	 		 Abs	{Y {Select HeightSize,HeightStepSize,FT_100}},
					 	 		 	 Rel	{Bearing {Select RandAngle,EncounterSize,ANGLES_0Deg},
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES5000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AfBlKimpo}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
  					Posn	
							{Abs	Pack_Target, 
				 	 		 Abs	{Y {Select HeightSize,HeightStepSize,FT_100}},
					 	 		 	 Rel	{Bearing {Select RandAngle,EncounterSize,ANGLES_180Deg},
									 Pitch	ANGLES_0Deg,
						 		 	 Range	{Select METRES1000,1,FT_250}
									} 
							},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQUAD_COMBAT_FLATV,

			AirItem	 
			{
				Scram_G3_Squad,
				Home	UID_AfBlKimpo,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},
//AC 04-------------- LEAD

	 	Setval	{EncounterSize, Int {List  Scram_G4_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
	 	Setval	{RandAngle, Bearing {Random ANGLES_135Deg,90,ANGLES_1Deg}},
		Setval	{RangeStepSize, Int {Random 0,11,1}},
		Setval	{HeightStepSize, Int {Random 0,20,1}},
	
	 	Setval	{NAT_ENEMY, Side {List  Scram_G4_Squad,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED)),
		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	Pack_Target, 
				 	 		 Abs	{Y {Select HeightSize,HeightStepSize,FT_100}},
					 	 		 	 Rel	{Bearing {Select RandAngle,EncounterSize,ANGLES_0Deg},
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES5000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AfBlKimpo}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
  					Posn	
							{Abs	Pack_Target, 
				 	 		 Abs	{Y {Select HeightSize,HeightStepSize,FT_100}},
					 	 		 	 Rel	{Bearing {Select RandAngle,EncounterSize,ANGLES_180Deg},
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES1000
									} 
							},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQUAD_COMBAT_FLATV,

			AirItem	 
			{
				Scram_G4_Squad,
				Home	UID_AfBlKimpo,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},

//AC 5--------------	WINGMAN

	 	Setval	{EncounterSize, Int {List  Scram_G5_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
		
	 	Setval	{NAT_ENEMY, Side {List  Scram_G5_Squad,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED)),
		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	Pack_Target, 
				 	 		 Abs	{Y {Select HeightSize,HeightStepSize,FT_100}},
					 	 		 	 Rel	{Bearing {Select RandAngle,EncounterSize,ANGLES_0Deg},
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES5000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AfBlKimpo}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
  					Posn	
							{Abs	Pack_Target, 
				 	 		 Abs	{Y {Select HeightSize,HeightStepSize,FT_100}},
					 	 		 	 Rel	{Bearing {Select RandAngle,EncounterSize,ANGLES_180Deg},
									 Pitch	ANGLES_0Deg,
						 		 	 Range	{Select METRES1000,1,FT_250}
									} 
							},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQUAD_COMBAT_FLATV,

			AirItem	 
			{
				Scram_G5_Squad,
				Home	UID_AfBlKimpo,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},
//AC 06-------------- LEAD

	 	Setval	{EncounterSize, Int {List  Scram_G6_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
	 	Setval	{RandAngle, Bearing {Random ANGLES_135Deg,90,ANGLES_1Deg}},
		Setval	{RangeStepSize, Int {Random 0,11,1}},
		Setval	{HeightStepSize, Int {Random 0,20,1}},
	
	 	Setval	{NAT_ENEMY, Side {List  Scram_G6_Squad,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED)),
		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	Pack_Target, 
				 	 		 Abs	{Y {Select HeightSize,HeightStepSize,FT_100}},
					 	 		 	 Rel	{Bearing {Select RandAngle,EncounterSize,ANGLES_0Deg},
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES5000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AfBlKimpo}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
  					Posn	
							{Abs	Pack_Target, 
				 	 		 Abs	{Y {Select HeightSize,HeightStepSize,FT_100}},
					 	 		 	 Rel	{Bearing {Select RandAngle,EncounterSize,ANGLES_180Deg},
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES1000
									} 
							},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQUAD_COMBAT_FLATV,

			AirItem	 
			{
				Scram_G6_Squad,
				Home	UID_AfBlKimpo,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},

//AC 7--------------	WINGMAN

	 	Setval	{EncounterSize, Int {List  Scram_G7_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
		
	 	Setval	{NAT_ENEMY, Side {List  Scram_G7_Squad,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED)),
		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	Pack_Target, 
				 	 		 Abs	{Y {Select HeightSize,HeightStepSize,FT_100}},
					 	 		 	 Rel	{Bearing {Select RandAngle,EncounterSize,ANGLES_0Deg},
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES5000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AfBlKimpo}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
  					Posn	
							{Abs	Pack_Target, 
				 	 		 Abs	{Y {Select HeightSize,HeightStepSize,FT_100}},
					 	 		 	 Rel	{Bearing {Select RandAngle,EncounterSize,ANGLES_180Deg},
									 Pitch	ANGLES_0Deg,
						 		 	 Range	{Select METRES1000,1,FT_250}
									} 
							},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQUAD_COMBAT_FLATV,

			AirItem	 
			{
				Scram_G7_Squad,
				Home	UID_AfBlKimpo,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		}
	};


//-------------------------------------------------
//TEAM 06: IMPLODE !!!!!
 	BattleField
	{
		FileName	FIL_teamplay6= teamply6.BF,

		Setval	{Pack_Target, UID_StSeoul},
	 	Setval	{HeightSize, Y {Random FT_4000,21,FT_1000}},
	 	Setval	{RandAngle, Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg}},

	 	Setval	{NAT_ENEMY, Side {List  Scram_G0_Squad,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED)),
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,0,ANGLES_45Deg},
								 Range	METRES200,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,0,ANGLES_45Deg},
								 Range	{Random METRES1000,5,METRES500},
								 Pitch	ANGLES_0Deg
								}
						},

			AirItem  	
			{
				Scram_G0_Squad,
				Home	UID_AfBlKimpo,
  				NAT_ENEMY,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		},
//NUMBER 2
	 	Setval	{NAT_ENEMY, Side {List  Scram_G1_Squad,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED)),
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,1,ANGLES_45Deg},
								 Range	METRES200,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,1,ANGLES_45Deg},
								 Range	{Random METRES1000,5,METRES500},
								 Pitch	ANGLES_0Deg
								}
						},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,
	
			AirItem  	
			{
				Scram_G1_Squad,
				Home	UID_AfBlKimpo,
  				NAT_ENEMY,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		},
//NUMBER 3
	 	Setval	{NAT_ENEMY, Side {List  Scram_G2_Squad,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED)),
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,2,ANGLES_45Deg},
								 Range	METRES200,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,2,ANGLES_45Deg},
								 Range	{Random METRES1000,5,METRES500},
								 Pitch	ANGLES_0Deg
								}
						},
			AirItem  	
			{
				Scram_G2_Squad,
				Home	UID_AfBlKimpo,
  				NAT_ENEMY,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		},
//NUMBER 4
	 	Setval	{NAT_ENEMY, Side {List  Scram_G3_Squad,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED)),
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,3,ANGLES_45Deg},
								 Range	METRES200,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,3,ANGLES_45Deg},
								 Range	{Random METRES1000,5,METRES500},
								 Pitch	ANGLES_0Deg
								}
						},
			AirItem  	
			{
				Scram_G3_Squad,
				Home	UID_AfBlKimpo,
  				NAT_ENEMY,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		},
//NUMBER 5
	 	Setval	{NAT_ENEMY, Side {List  Scram_G4_Squad,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED)),
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,4,ANGLES_45Deg},
								 Range	METRES200,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,4,ANGLES_45Deg},
								 Range	{Random METRES1000,5,METRES500},
								 Pitch	ANGLES_0Deg
								}
						},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

			AirItem  	
			{
				Scram_G4_Squad,
				Home	UID_AfBlKimpo,
  				NAT_ENEMY,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		},
//NUMBER 6
	 	Setval	{NAT_ENEMY, Side {List  Scram_G5_Squad,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED)),
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,5,ANGLES_45Deg},
								 Range	METRES200,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,5,ANGLES_45Deg},
								 Range	{Random METRES1000,5,METRES500},
								 Pitch	ANGLES_0Deg
								}
						},
			AirItem  	
			{
				Scram_G5_Squad,
				Home	UID_AfBlKimpo,
  				NAT_ENEMY,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		},
//NUMBER 7
	 	Setval	{NAT_ENEMY, Side {List  Scram_G6_Squad,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED)),
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,6,ANGLES_45Deg},
								 Range	METRES200,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,6,ANGLES_45Deg},
								 Range	{Random METRES1000,5,METRES500},
								 Pitch	ANGLES_0Deg
								}
						},
			AirItem  	
			{
				Scram_G6_Squad,
				Home	UID_AfBlKimpo,
  				NAT_ENEMY,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		},
//NUMBER 8
	 	Setval	{NAT_ENEMY, Side {List  Scram_G7_Squad,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED)),
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,7,ANGLES_45Deg},
								 Range	METRES200,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,7,ANGLES_45Deg},
								 Range	{Random METRES1000,5,METRES500},
								 Pitch	ANGLES_0Deg
								}
						},
			AirItem  	
			{
				Scram_G7_Squad,
				Home	UID_AfBlKimpo,
  				NAT_ENEMY,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		}
	};

//--------------------------------------------------------------------------
//TEAM 07 EXPLODE
 	BattleField
	{
		FileName	FIL_teamplay7= teamply7.BF,
		Setval	{Pack_Target, UID_StSeoul},
	 	Setval	{HeightSize, Y {Random FT_4000,21,FT_1000}},
	 	Setval	{RandAngle, Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg}},

	 	Setval	{NAT_ENEMY, Side {List  Scram_G0_Squad,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED)),
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,0,ANGLES_45Deg},
								 Range	METRES2000,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,0,ANGLES_45Deg},
								 Range	{Random METRES20,10,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},

			AirItem  	
			{
				Scram_G0_Squad,
				Home	UID_AfBlKimpo,
  				NAT_ENEMY,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		},
//NUMBER 2
	 	Setval	{NAT_ENEMY, Side {List  Scram_G1_Squad,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED)),
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,1,ANGLES_45Deg},
								 Range	METRES2000,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,1,ANGLES_45Deg},
								 Range	{Random METRES20,10,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,
	
			AirItem  	
			{
				Scram_G1_Squad,
				Home	UID_AfBlKimpo,
  				NAT_ENEMY,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		},
//NUMBER 3
	 	Setval	{NAT_ENEMY, Side {List  Scram_G2_Squad,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED)),
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,2,ANGLES_45Deg},
								 Range	METRES2000,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,2,ANGLES_45Deg},
								 Range	{Random METRES100,10,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
			AirItem  	
			{
				Scram_G2_Squad,
				Home	UID_AfBlKimpo,
  				NAT_ENEMY,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		},
//NUMBER 4
	 	Setval	{NAT_ENEMY, Side {List  Scram_G3_Squad,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED)),
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,3,ANGLES_45Deg},
								 Range	METRES2000,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,3,ANGLES_45Deg},
								 Range	{Random METRES100,10,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
			AirItem  	
			{
				Scram_G3_Squad,
				Home	UID_AfBlKimpo,
  				NAT_ENEMY,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		},
//NUMBER 5
	 	Setval	{NAT_ENEMY, Side {List  Scram_G4_Squad,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED)),
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,4,ANGLES_45Deg},
								 Range	METRES2000,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,4,ANGLES_45Deg},
								 Range	{Random METRES100,10,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

			AirItem  	
			{
				Scram_G4_Squad,
				Home	UID_AfBlKimpo,
  				NAT_ENEMY,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		},
//NUMBER 6
	 	Setval	{NAT_ENEMY, Side {List  Scram_G5_Squad,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED)),
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,5,ANGLES_45Deg},
								 Range	METRES2000,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,5,ANGLES_45Deg},
								 Range	{Random METRES100,10,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
			AirItem  	
			{
				Scram_G5_Squad,
				Home	UID_AfBlKimpo,
  				NAT_ENEMY,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		},
//NUMBER 7
	 	Setval	{NAT_ENEMY, Side {List  Scram_G6_Squad,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED)),
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,6,ANGLES_45Deg},
								 Range	METRES2000,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,6,ANGLES_45Deg},
								 Range	{Random METRES100,10,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
			AirItem  	
			{
				Scram_G6_Squad,
				Home	UID_AfBlKimpo,
  				NAT_ENEMY,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		},
//NUMBER 8
	 	Setval	{NAT_ENEMY, Side {List  Scram_G7_Squad,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED,NAT_RED)),
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,7,ANGLES_45Deg},
								 Range	METRES2000,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	{Pack_Target},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,7,ANGLES_45Deg},
								 Range	{Random METRES100,10,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
			AirItem  	
			{
				Scram_G7_Squad,
				Home	UID_AfBlKimpo,
  				NAT_ENEMY,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				CHAR_CAVALIER
  			}
 		}
	};

//--------------------------------
//LAND / TAKEOFF PRACTICE
	BattleField
	{
		FileName	FIL_QUICKMISSION_11=QUICKM11.BF,
		AirGroup	
		{
			Route	
			{
				WayPoint  
				{
  					Posn	{Abs	Pack_Target,
						 	 Abs	{Y Scram_G0_Alt},
							 Rel	{Y -FT_1000}
							},
					Range 	METRES8000,
					Action	wpalandingno
				}
 			},
			
			NumInWing	1,
  			NumInForm	1,

			Posn		
				{Abs	Pack_Target, 
			   	 Abs	{Y Scram_G0_Alt},
				 Rel	{Bearing ANGLES_0Deg,
						 Range METRES8000
						}
				},
			

			AirItem	
			{
				Scram_G0_Squad,
				Home	Pack_Target,
  				NAT_BLUE,
				MORALE_HIGH,
  				Scram_G0_Skill,
				Bombs Weap_Basic
  			}
 		}
	};


//--------------------------------
//CAS: Seoul, UN Defend

	BattleField
	{
		FileName	FIL_QUICKMISSION_12=QUICKM12.BF,
	
		SimpleItem
		{
			Posn
			{
				Abs
//DeadCode MS 02Sep99 				{	X	62763008,
//DeadCode MS 02Sep99 					Z	61043712
				{	X	62820352,
					Z	61088000
				}
			},
			UIDBand		MissileBAND,
			Shape		BARAGL
		},

		SimpleItem
		{
			Posn
			{
				Abs
				{	X	62820352,
					Z	61093400
//TempCode MS 02Sep99 				{	X	62820352,
//TempCode MS 02Sep99 					Z	61088000
				}
			},
			UIDBand		AmberBattleNodeBAND,
			SetUID		UID_CASDefend,
//TempCode MS 31Aug99 			SHAPE_TroopDefend
			Shape		EMPTY
		},
		
		ItemGroup
		{	Target UID_CASDefend,

		GroundGroup
		{
			Posn	POS_Landing =
			{
				Abs
				{	X	62843904,
					Z	61119488
				}
			},
			Route
			{
				WayPoint 	
				{
					Posn	POS_Landing2 =
					{
						Abs
						{	X	62820352,
							Z	61094400
						}
					},
					Action	wpdmbtrkstopno
				}
			},
			NumInForm		1,
			Formation	SQUAD_BATTLELINE,
			GroundItem	
			{
				RedArmourBAND,
				Type	SQ_VEHICLES,
				Side	NAT_RED,
				Shape	BARGE,
				Vel	60
		}	},
		GroundGroup
		{
			Posn	
			{
				Abs
				{	X	62843904,
					Z	61119488
				}
			},
			Route
			{
				WayPoint	
				{
					Posn
					{
						Abs
						{	X	62820352,
							Z	61094400
						}
					},
					Action	wpdmbtrknoactno
				},
				WayPoint	
				{
					Posn	POS_Landing3 =
					{
						Abs
						{	X	62785024,
							Z	61057024
						}
					},
					Action	wpdmbtrkstopno
				}
			},
			NumInForm		1,
			Formation	SQUAD_BATTLELINE,
			GroundItem	
			{
				RedArmourBAND,
				Type	SQ_VEHICLES,
				Side	NAT_RED,
				Shape	SHAPE_TroopMove,
				Vel 60
		}	},
//river crossing 2
		GroundGroup
		{
			Route
			{
				WayPoint	
				{
					Posn	POS_Landing4 =
					{
						Abs	POS_Landing2,
						Rel	{Intercept {POS_Landing,POS_Landing2},
							 Bearing ANGLES_90Deg,
							 Pitch ANGLES_0Deg,
						 	 Range METRES100
							}
					},
					Action	wpdmbtrkstopno
				}
			},

			Posn	POS_Landing5 =
			{
				Abs	POS_Landing4,
				Rel	{Intercept {POS_Landing2,POS_Landing},
					 Bearing ANGLES_0Deg,
					 Pitch	ANGLES_0Deg,
					 Range	METRES50
				}
			},

			NumInForm		1,
			Formation	SQUAD_BATTLELINE,
			GroundItem	
			{
				RedArmourBAND,
				Type	SQ_VEHICLES,
				Side	NAT_RED,
				Shape	BARGE,
				Vel	60
		}	},
		GroundGroup
		{
			Posn	
			{
				Abs	POS_Landing5
			},
			Route
			{
				WayPoint	
				{
					Posn POS_Landing4,
					Action	wpdmbtrknoactno
				},
				WayPoint	
				{
					Posn	
					{
						Abs	POS_Landing4,
						Rel	{Intercept {POS_Landing5,POS_Landing4},
							 Bearing ANGLES_0Deg,
							 Pitch ANGLES_0Deg,
						 	 Range METRES500
							}
					},
					Action	wpdmbtrkstopno
				}
			},
			NumInForm		1,
			Formation	SQUAD_BATTLELINE,
			GroundItem	
			{
				RedArmourBAND,
				Type	SQ_VEHICLES,
				Side	NAT_RED,
				Shape	T34,
				Vel 60
		}	},

//river crossing 3
		GroundGroup
		{
			Route
			{
				WayPoint	
				{
					Posn	POS_Landing6 =
					{
						Abs	POS_Landing2,
						Rel	{Intercept {POS_Landing,POS_Landing2},
							 Bearing ANGLES_270Deg,
							 Pitch ANGLES_0Deg,
						 	 Range METRES400
							}
					},
					Action	wpdmbtrkstopno
				}
			},

			Posn	POS_Landing7 =
			{
				Abs	POS_Landing6,
				Rel	{Intercept {POS_Landing2,POS_Landing},
					 Bearing ANGLES_0Deg,
					 Pitch	ANGLES_0Deg,
					 Range	METRES200
				}
			},

			NumInForm		1,
			Formation	SQUAD_BATTLELINE,
			GroundItem	
			{
				RedArmourBAND,
				Type	SQ_VEHICLES,
				Side	NAT_RED,
				Shape	BARGE,
				Vel	60
		}	},
		GroundGroup
		{
			Posn	
			{
				Abs	POS_Landing7
			},
			Route
			{
				WayPoint	
				{
					Posn POS_Landing6,
					Action	wpdmbtrknoactno
				},
				WayPoint	
				{
					Posn	
					{
						Abs	POS_Landing6,
						Rel	{Intercept {POS_Landing7,POS_Landing6},
							 Bearing ANGLES_0Deg,
							 Pitch ANGLES_0Deg,
						 	 Range METRES500
							}
					},
					Action	wpdmbtrkstopno
				}
			},
			NumInForm		1,
			Formation	SQUAD_BATTLELINE,
			GroundItem	
			{
				RedArmourBAND,
				Type	SQ_VEHICLES,
				Side	NAT_RED,
				Shape	SHAPE_TroopMove,
				Vel 60
		}	},

//river crossing 4
		GroundGroup
		{
			Route
			{
				WayPoint	
				{
					Posn	POS_Landing8 =
					{
						Abs	POS_Landing2,
						Rel	{Intercept {POS_Landing,POS_Landing2},
							 Bearing ANGLES_270Deg,
							 Pitch ANGLES_0Deg,
						 	 Range METRES200
							}
					},
					Action	wpdmbtrkstopno
				}
			},

			Posn	POS_Landing9 =
			{
				Abs	POS_Landing8,
				Rel	{Intercept {POS_Landing2,POS_Landing},
					 Bearing ANGLES_0Deg,
					 Pitch	ANGLES_0Deg,
					 Range	METRES300
				}
			},

			NumInForm		1,
			Formation	SQUAD_BATTLELINE,
			GroundItem	
			{
				RedArmourBAND,
				Type	SQ_VEHICLES,
				Side	NAT_RED,
				Shape	BARGE,
				Vel	60
		}	},
		GroundGroup
		{
			Posn	
			{
				Abs	POS_Landing9
			},
			Route
			{
				WayPoint	
				{
					Posn POS_Landing8,
					Action	wpdmbtrknoactno
				},
				WayPoint	
				{
					Posn	
					{
						Abs	POS_Landing8,
						Rel	{Intercept {POS_Landing9,POS_Landing8},
							 Bearing ANGLES_0Deg,
							 Pitch ANGLES_0Deg,
						 	 Range METRES500
							}
					},
					Action	wpdmbtrkstopno
				}
			},
			NumInForm		1,
			Formation	SQUAD_BATTLELINE,
			GroundItem	
			{
				RedArmourBAND,
				Type	SQ_VEHICLES,
				Side	NAT_RED,
				Shape	SHAPE_TroopMove,
				Vel 60
		}	},
		GroundGroup
		{
			Posn
			{
				Abs
				{	X	63058944,
					Z	60772352
				}
			},
			Route
			{
				WayPoint	
				{
					Posn
					{
						Abs
						{	X	63012864,
							Z	60765696
						}
					},
					Action	wpdmbtrknoactno
				},
				WayPoint	
				{
					Posn
					{
						Abs
						{	X	62930944,
							Z	60680704
						}
					},
					Action	wpdmbtrknoactno
				},
				WayPoint	
				{
					Posn
					{
						Abs
						{	X	62907392,
							Z	60651520
						}
					},
					Action	wpdmbtrknoactno
				},
				WayPoint	
				{
					Posn
					{
						Abs
						{	X	62902272,
							Z	60628992
						}
					},
					Action	wpdmbtrknoactno
				},
				WayPoint	
				{
					Posn
					{
						Abs
						{	X	62903296,
							Z	60473344
						}
					},
					Action	wpdmbtrkstopno
				}
			},
			NumInForm		3,
			Formation	SQUAD_TRUCKCONVOY,
			GroundItem	
			{
				RedArmourBAND,
				Type	SQ_VEHICLES,
				Side	NAT_RED,
				Shape	T34,
				Vel	100
		}	},
		GroundGroup
		{
			Posn
			{
				Abs
				{	X	63045632,
					Z	60785664
				}
			},
			Route
			{
				WayPoint	
				{
					Posn
					{
						Abs
						{	X	63020032,
							Z	60785664
						}
					},
					Action	wpdmbtrkstopno
				}
			},
			NumInForm		8,
			Formation	SQUAD_BATTLELINE,
			GroundItem	
			{
				RedArmourBAND,
				Type	SQ_VEHICLES,
				Side	NAT_RED,
				Shape	SHAPE_TroopAttack,
				Vel	30
		}	},
		GroundGroup
		{
			Posn
			{
				Abs
				{	X	63009792,
					Z	60806144
				}
			},
			Route
			{
				WayPoint	
				{
					Posn
					{
						Abs
						{	X	62985216,
							Z	60783616
						}
					},
					Action	wpdmbtrkstopno
				}
			},
			NumInForm		8,
			Formation	SQUAD_BATTLELINE,
			GroundItem	
			{
				RedArmourBAND,
				Type	SQ_VEHICLES,
				Side	NAT_RED,
				Shape	SHAPE_TroopAttack,
				Vel	30
		}	}


		},
		AirGroup	
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	UID_CASDefend}, 
 					Range	METRES3000,
					Action	wpacnoactionno
				},
				WayPoint  
				{
					Target	UID_CASDefend,
					Action	wpbombno,
					Range	METRES3000	
				},
				WayPoint	
				{
					Posn	
						{Abs	UID_AfBlKimpo, 
						 Abs	{Y Scram_G0_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				}
 			},
			
			NumInWing	2,
  			NumInForm	Scram_G0_AC,

			DUTY_DiveSingle,

				Posn
				{
					Abs	POS_Landing,
					Abs {Y	FT_2000},
					 Rel	{Bearing ANGLES_180Deg,
							 Pitch ANGLES_0Deg,
							 Range METRES3000
							}
				},
			AirItem	
			{
				Scram_G0_Squad,
				Bombs Weap_NapmRock,
				Home	UID_AfBlKimpo,
  				NAT_BLUE,
				MORALE_HIGH,
  				Scram_G0_Skill,
				Target	UID_CASDefend
  			}
 		}
	};

//--------------------------------
//ONE ON ONE

	BattleField
	{
		FileName	FIL_QUICKMISSION_13=QUICKM13.BF,
//DeadCode MS 16May99 		Setval	(Scram_G0_AC,(List Scram_G0_AC,0,0,0,0,0,1,2,3,4,5,6,7,8,9,10,11,12)),
		AirGroup	
		{
			Route	
			{
				WayPoint	
				{
					Posn		
						{Abs	Pack_Target, 
						 Abs	{Y Scram_G0_Alt},
				 		 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
								 Range	METRES5000
								} 
						},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	UID_AfBlKimpo, 
						 Abs	{Y Scram_G0_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				}
 			},
			
			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,

  			Posn	{Abs	Pack_Target, 
  					 Abs	{Y Scram_G0_Alt}
					},	

			AirItem
			{
				Scram_G0_Squad,
				Home	UID_AfBlKimpo,
  				NAT_BLUE,
				MORALE_HIGH,
  				Scram_G0_Skill
  			}
 		},

		AirGroup   
		{
			Route	
			{
				WayPoint	
				{
					Posn		
						{Abs	Pack_Target, 
						 Abs	{Y Scram_G1_Alt},
				 		 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
								 Range	METRES5000
								} 
						},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	UID_AfRdAntung, 
						 Abs	{Y Scram_G0_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				}
 			},

			NumInWing	1,
  			NumInForm	1,

			DUTYMIGCAP,

			Posn		
				{Abs	Pack_Target, 
				 Abs	{Y Scram_G1_Alt},
		 		 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
						 Range	METRES500
						} 
				},

		   AirItem
			{
				Home		UID_AfRdAntung,
				Scram_G1_Squad,
				NAT_RED,
  				Scram_G1_Skill,
				MORALE_HIGH
			}
		}

//DeadCode MS 16May99 		AirGroup	
//DeadCode MS 16May99 		{
//DeadCode MS 16May99 			Route	
//DeadCode MS 16May99 			{
//DeadCode MS 16May99 				WayPoint	
//DeadCode MS 16May99 				{
//DeadCode MS 16May99 					Posn		
//DeadCode MS 16May99 						{Abs	Pack_Target, 
//DeadCode MS 16May99 						 Abs	{Y Scram_G0_Alt},
//DeadCode MS 16May99 				 		 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
//DeadCode MS 16May99 								 Range	METRES5000
//DeadCode MS 16May99 								} 
//DeadCode MS 16May99 						},
//DeadCode MS 16May99 					Action	wpacnoactionno	
//DeadCode MS 16May99 				},
//DeadCode MS 16May99 				WayPoint	
//DeadCode MS 16May99 				{
//DeadCode MS 16May99 					Posn	
//DeadCode MS 16May99 						{Abs	UID_AfBlKimpo, 
//DeadCode MS 16May99 						 Abs	{Y Scram_G0_Alt}
//DeadCode MS 16May99 						},
//DeadCode MS 16May99  					Range	METRES6000,
//DeadCode MS 16May99 					Action	wpalandingno
//DeadCode MS 16May99 				}
//DeadCode MS 16May99  			},
//DeadCode MS 16May99 			
//DeadCode MS 16May99 			NumInWing	2,
//DeadCode MS 16May99   			NumInForm	3,
//DeadCode MS 16May99 
//DeadCode MS 16May99   			DUTYMIGCAP,
//DeadCode MS 16May99 
//DeadCode MS 16May99   			Posn	{Abs	Pack_Target, 
//DeadCode MS 16May99   					 Abs	{Y Scram_G0_Alt}
//DeadCode MS 16May99 					},	
//DeadCode MS 16May99 
//DeadCode MS 16May99 			AirItem
//DeadCode MS 16May99 			{
//DeadCode MS 16May99 				Scram_G0_Squad,
//DeadCode MS 16May99 				Home	UID_AfBlKimpo,
//DeadCode MS 16May99   				NAT_BLUE,
//DeadCode MS 16May99 				MORALE_HIGH,
//DeadCode MS 16May99   				Scram_G0_Skill
//DeadCode MS 16May99   			}
//DeadCode MS 16May99  		},

//DeadCode MS 16May99 		AirGroup	
//DeadCode MS 16May99 		{
//DeadCode MS 16May99 			Route	
//DeadCode MS 16May99 			{
//DeadCode MS 16May99 				WayPoint	
//DeadCode MS 16May99 				{
//DeadCode MS 16May99 					Posn		
//DeadCode MS 16May99 						{Abs	Pack_Target, 
//DeadCode MS 16May99 						 Abs	{Y Scram_G0_Alt},
//DeadCode MS 16May99 				 		 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
//DeadCode MS 16May99 								 Range	METRES5000
//DeadCode MS 16May99 								} 
//DeadCode MS 16May99 						},
//DeadCode MS 16May99 					Action	wpacnoactionno	
//DeadCode MS 16May99 				},
//DeadCode MS 16May99 				WayPoint	
//DeadCode MS 16May99 				{
//DeadCode MS 16May99 					Posn	
//DeadCode MS 16May99 						{Abs	UID_AfBlKimpo, 
//DeadCode MS 16May99 						 Abs	{Y Scram_G0_Alt}
//DeadCode MS 16May99 						},
//DeadCode MS 16May99  					Range	METRES6000,
//DeadCode MS 16May99 					Action	wpalandingno
//DeadCode MS 16May99 				}
//DeadCode MS 16May99  			},
//DeadCode MS 16May99 			
//DeadCode MS 16May99 			NumInWing	2,
//DeadCode MS 16May99   			NumInForm	Scram_G0_AC,
//DeadCode MS 16May99 
//DeadCode MS 16May99   			DUTYMIGCAP,
//DeadCode MS 16May99 
//DeadCode MS 16May99   			Posn	{Abs	Pack_Target, 
//DeadCode MS 16May99   					 Abs	{Y Scram_G0_Alt}
//DeadCode MS 16May99 					},	
//DeadCode MS 16May99 
//DeadCode MS 16May99 			AirItem
//DeadCode MS 16May99 			{
//DeadCode MS 16May99 				Scram_G0_Squad,
//DeadCode MS 16May99 				Home	UID_AfBlKimpo,
//DeadCode MS 16May99   				NAT_BLUE,
//DeadCode MS 16May99 				MORALE_HIGH,
//DeadCode MS 16May99   				Scram_G0_Skill
//DeadCode MS 16May99   			}
//DeadCode MS 16May99  		}
	};

//--------------------------------
//TURKEY SHOOT

	BattleField
	{
		FileName	FIL_QUICKMISSION_14=QUICKM14.BF,

		Setval		(EnemyScoutMorale, (Select Scram_G0_Skill,0,0)),
		Setval		(FriendlyScoutMorale, (Select Scram_G1_Skill,0,0)),

		AirGroup	
		{
			Route	
			{
				WayPoint	
				{
					Posn		
						{Abs	Pack_Target, 
						 Abs	{Y Scram_G0_Alt},
				 		 Rel	{Bearing ANGLES_0Deg,
								 Range	METRES5000
								} 
						},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	UID_AfBlKimpo, 
						 Abs	{Y Scram_G0_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				}
 			},
			
			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,

  			Posn	{Abs	Pack_Target, 
  					 Abs	{Y Scram_G0_Alt}
					},	

			AirItem
			{
				Scram_G0_Squad,
				Home	UID_AfBlKimpo,
  				NAT_BLUE,
				MORALE_HIGH,
  				Scram_G0_Skill
  			}
 		},

		AirGroup   
		{
			Route	
			{
				WayPoint	
				{
					Posn		
						{Abs	Pack_Target, 
						 Abs	{Y Scram_G1_Alt},
				 		 Rel	{Bearing ANGLES_0Deg,
								 Range	METRES5000
								} 
						},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	UID_AfRdAntung, 
						 Abs	{Y Scram_G1_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				}
 			},

			NumInWing	1,
  			NumInForm	1,

			DUTYMIGCAP,

			Posn		
				{Abs	Pack_Target, 
				 Abs	{Y Scram_G1_Alt},
		 		 Rel	{Bearing ANGLES_0Deg,
						 Range	METRES500
						} 
				},

		   AirItem
			{
				Home		UID_AfRdAntung,
				Scram_G1_Squad,
				NAT_RED,
  				Scram_G1_Skill,
				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL
			}
		}
	};

//--------------------------------
//DEMO 1: Ground Battle
//CAS: UN attack Hoengsong

	BattleField
	{
		FileName	FIL_QUICKMISSION_15=QUICKM15.BF,

		Setval	{TroopShape,Shape(List (Random 2), F82, CORS)},

		SimpleItem	
		{
			Posn	Mortar_Pos01 =
			{
				Abs
				{	X	72065024,
					Z	60348416
				}
			},
			UIDBand		AmberBattleNodeBAND,
			SetUID		UID_CASDefend,
			Shape		CHMORT
		},

//BUNKERS AND STUFF
		ItemGroup
		{	Target	UID_CASDefend,	
				SimpleItem	
				{
					Posn	Mortar_Pos00 =
					{
						Abs
						{	X	72075264,
							Z	60385280
						}
					},
					UIDBand		AmberCivilianBAND,
					Shape		CHMORT
				},
				SimpleItem	
				{
					Posn	
					{
						Abs	Mortar_Pos00,
						Rel	{Intercept {Mortar_Pos00,Mortar_Pos01},
						 	 Bearing ANGLES_0Deg,
					 		 RangePercent	10,
						 	 Pitch ANGLES_0Deg
						}
					},
					UIDBand		AmberCivilianBAND,
					Shape		SHAPE_TroopAttack
				},
				SimpleItem	
				{
					Posn	
					{
						Abs	Mortar_Pos00,
						Rel	{Intercept {Mortar_Pos00,Mortar_Pos01},
						 	 Bearing ANGLES_0Deg,
					 		 RangePercent	20,
						 	 Pitch ANGLES_0Deg
						}
					},
					UIDBand		AmberCivilianBAND,
					Shape		CHMORT
				},
				SimpleItem	
				{
					Posn	
					{
						Abs	Mortar_Pos00,
						Rel	{Intercept {Mortar_Pos00,Mortar_Pos01},
						 	 Bearing ANGLES_0Deg,
					 		 RangePercent	30,
						 	 Pitch ANGLES_0Deg
						}
					},
					UIDBand		AmberCivilianBAND,
					Shape		SHAPE_TroopAttack
				},
				SimpleItem	
				{
					Posn	
					{
						Abs	Mortar_Pos00,
						Rel	{Intercept {Mortar_Pos00,Mortar_Pos01},
						 	 Bearing ANGLES_0Deg,
					 		 RangePercent	40,
						 	 Pitch ANGLES_0Deg
						}
					},
					UIDBand		AmberCivilianBAND,
					Shape		CHMORT
				},
				SimpleItem	
				{
					Posn	
					{
						Abs	Mortar_Pos00,
						Rel	{Intercept {Mortar_Pos00,Mortar_Pos01},
						 	 Bearing ANGLES_0Deg,
					 		 RangePercent	50,
						 	 Pitch ANGLES_0Deg
						}
					},
					UIDBand		AmberCivilianBAND,
//TempCode MS 01Sep99 					Shape		BARAGL
					Shape		SHAPE_TroopAttack
				},
				SimpleItem	
				{
					Posn	
					{
						Abs	Mortar_Pos00,
						Rel	{Intercept {Mortar_Pos00,Mortar_Pos01},
						 	 Bearing ANGLES_0Deg,
					 		 RangePercent	60,
						 	 Pitch ANGLES_0Deg
						}
					},
					UIDBand		AmberCivilianBAND,
					Shape		CHMORT
				},
				SimpleItem	
				{
					Posn	
					{
						Abs	Mortar_Pos00,
						Rel	{Intercept {Mortar_Pos00,Mortar_Pos01},
						 	 Bearing ANGLES_0Deg,
					 		 RangePercent	70,
						 	 Pitch ANGLES_0Deg
						}
					},
					UIDBand		AmberCivilianBAND,
					Shape		SHAPE_TroopAttack
				},
				SimpleItem	
				{
					Posn	
					{
						Abs	Mortar_Pos00,
						Rel	{Intercept {Mortar_Pos00,Mortar_Pos01},
						 	 Bearing ANGLES_0Deg,
					 		 RangePercent	80,
						 	 Pitch ANGLES_0Deg
						}
					},
					UIDBand		AmberCivilianBAND,
					Shape		CHMORT
				},
				SimpleItem	
				{
					Posn	
					{
						Abs	Mortar_Pos00,
						Rel	{Intercept {Mortar_Pos00,Mortar_Pos01},
						 	 Bearing ANGLES_0Deg,
					 		 RangePercent	90,
						 	 Pitch ANGLES_0Deg
						}
					},
					UIDBand		AmberCivilianBAND,
					Shape		SHAPE_TroopAttack
				},
			GroundGroup
			{
				Posn
				{
					Abs
					{	X	71988300,
						Z	60661760
					}
				},
				Route
				{
					WayPoint	
					{
						Posn
						{
							Abs
							{	X	71988300,
								Z	60614896
							}
						},
						Vel	40,
						Action	wpdmbtrkstopno,
						Range	0
					}
				},
				NumInForm		6,
				Formation	SQUAD_TRUCKCONVOY,
				GroundItem	
				{
					RedArmourBAND,
					Type	SQ_ATank,
					Side	NAT_RED,
					Shape	T34,
					Vel	40,
					MoveCode	GROUND_TAXI
			}	}
		},

		SimpleItem	
		{
			Posn	
			{
				Abs
				{	X	71952933,
					Z	60475514
				}
			},
			UIDBand		AmberCivilianBAND,
			Shape		BARAGL
		},

		AirGroup	
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	UID_CASDefend, 
						 Abs	{Y FT_1000}
						},
					Action	wpacnoactionno,
					Range	METRES5000
				},
				WayPoint  
				{
					Target	UID_CASDefend,
//TempCode MS 07Jun99 					Posn
//TempCode MS 07Jun99 					{
//TempCode MS 07Jun99 						Abs {Y	FT_1000}
//TempCode MS 07Jun99 					},
					Range METRES5000,
					Action	wpbombno
				},
				WayPoint	
				{
					Posn	
						{Abs	UID_AfBlKimpo, 
						 Abs	{Y FT_4000}
						},
					Action	wpalandingno
				}
 			},
			
			NumInWing	2,
  			NumInForm	Scram_G0_AC,

  			DUTY_DiveSingle,

				Posn
				{
						Abs Mortar_Pos00,
						Abs {Y	{Select Scram_G0_Alt,1,-FT_1000}},
					 	Rel	{Bearing ANGLES_340Deg,
							 Range	METRES5500
							}
				},

			AirItem	
			{
				Scram_G0_Squad,
				Home	UID_AfBlKimpo,
  				NAT_BLUE,
				MORALE_HIGH,
  				Scram_G0_Skill,
				Bombs Weap_NapmRock,
				Target	UID_CASDefend
  			}
 		},


//NON PLAYER EYE CANDY

		AirGroup	
		{
			Route	
			{
				WayPoint
				{
					Posn
					{
						Abs Mortar_Pos00,
						Abs {Y	FT_1000}
					},
//TempCode MS 13May99 					Action	wpfiregun,
					Action	wpacnoactionno,	
					Range	METRES1000
				},
				WayPoint
				{
					Posn
					{
						Abs Mortar_Pos00,
						Abs {Y	FT_1000}
					},
					Action	wpacnoactionno,	
//TempCode MS 26Nov98 					Action	wpfiregun,
					Range	METRES500
				},
				WayPoint
				{
					Posn
					{
						Abs Mortar_Pos00,
						Abs {Y	FT_3000}
					},
					Action	wpacnoactionno	
				},
				WayPoint
				{
					Posn
					{
						Abs	Pack_Target,
						Abs	{Y FT_3000}
					},
 					Action	wpacnoactionno
				},
				WayPoint
				{
					Posn
					{
						Abs
						{	X	72080384,
							Z	60466176,
							Y	FT_3000
						}
					},
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	
						{Abs	UID_Japan, 
						 Abs	{Y FT_4000}
						},
					Action	wpalandingno
				}
 			},
			
			NumInWing	2,
  			NumInForm	2,

  			DUTYMIGCAP,

				Posn
				{
					Abs	Mortar_Pos00,
					Abs	{Y {Select FT_2000,1,FT_200}},
					Rel	{Bearing	{Select ANGLES_340Deg,1,ANGLES_1Deg},
						 Range	{Select METRES4000,1,METRES800}
						}
				},

			AirItem	
			{
				SQ_4U,
				Shape	TroopShape,
				Home	UID_Japan,
  				NAT_BLUE,
				MORALE_HIGH,
  				Scram_G0_Skill,
				Bombs Weap_Basic
  			}
 		},

//DeadCode MS 07Jun99 		AirGroup	
//DeadCode MS 07Jun99 		{
//DeadCode MS 07Jun99 			Route	
//DeadCode MS 07Jun99 			{
//DeadCode MS 07Jun99 				WayPoint  
//DeadCode MS 07Jun99 				{
//DeadCode MS 07Jun99 					Posn
//DeadCode MS 07Jun99 					{
//DeadCode MS 07Jun99 						Abs
//DeadCode MS 07Jun99 						{	X	72080384,
//DeadCode MS 07Jun99 							Z	60466176,
//DeadCode MS 07Jun99 							Y	FT_2000
//DeadCode MS 07Jun99 						}
//DeadCode MS 07Jun99 					},
//DeadCode MS 07Jun99 					Action	wpacnoactionno,	
//DeadCode MS 07Jun99 					Range	METRES8000
//DeadCode MS 07Jun99 				},
//DeadCode MS 07Jun99 				WayPoint
//DeadCode MS 07Jun99 				{
//DeadCode MS 07Jun99 					Posn
//DeadCode MS 07Jun99 					{
//DeadCode MS 07Jun99 						Abs	Pack_Target,
//DeadCode MS 07Jun99 						Abs	{Y FT_2000}
//DeadCode MS 07Jun99 					},
//DeadCode MS 07Jun99 					Action	wpacnoactionno	
//DeadCode MS 07Jun99 				},
//DeadCode MS 07Jun99 				WayPoint  
//DeadCode MS 07Jun99 				{
//DeadCode MS 07Jun99 					Posn
//DeadCode MS 07Jun99 					{
//DeadCode MS 07Jun99 						Abs
//DeadCode MS 07Jun99 						{	X	72080384,
//DeadCode MS 07Jun99 							Z	60466176,
//DeadCode MS 07Jun99 							Y	FT_4000
//DeadCode MS 07Jun99 						}
//DeadCode MS 07Jun99 					},
//DeadCode MS 07Jun99  					Action	wpacnoactionno	
//DeadCode MS 07Jun99 				},
//DeadCode MS 07Jun99 				WayPoint
//DeadCode MS 07Jun99 				{
//DeadCode MS 07Jun99 					Posn
//DeadCode MS 07Jun99 					{
//DeadCode MS 07Jun99 						Abs	Pack_Target,
//DeadCode MS 07Jun99 						Abs	{Y FT_4000}
//DeadCode MS 07Jun99 					},
//DeadCode MS 07Jun99 					Action	wpacnoactionno	
//DeadCode MS 07Jun99 				},
//DeadCode MS 07Jun99 				WayPoint	
//DeadCode MS 07Jun99 				{
//DeadCode MS 07Jun99 					Posn	
//DeadCode MS 07Jun99 						{Abs	UID_Japan, 
//DeadCode MS 07Jun99 						 Abs	{Y FT_4000}
//DeadCode MS 07Jun99 						},
//DeadCode MS 07Jun99 					Action	wpalandingno
//DeadCode MS 07Jun99 				}
//DeadCode MS 07Jun99  			},
//DeadCode MS 07Jun99 			
//DeadCode MS 07Jun99 			NumInWing	1,
//DeadCode MS 07Jun99   			NumInForm	1,
//DeadCode MS 07Jun99 
//DeadCode MS 07Jun99   			DUTYMIGCAP,
//DeadCode MS 07Jun99 
//DeadCode MS 07Jun99 				Posn
//DeadCode MS 07Jun99 				{
//DeadCode MS 07Jun99 					Abs	Pack_Target,
//DeadCode MS 07Jun99 					Abs	{Y {Select FT_2000,1,FT_200}},
//DeadCode MS 07Jun99 					Rel	{Bearing	{Select ANGLES_330Deg,-1,ANGLES_1Deg},
//DeadCode MS 07Jun99 						 Range	{Select METRES2000,2,METRES200}
//DeadCode MS 07Jun99 						}
//DeadCode MS 07Jun99 				},
//DeadCode MS 07Jun99 
//DeadCode MS 07Jun99 			AirItem	
//DeadCode MS 07Jun99 			{
//DeadCode MS 07Jun99 				SQ_4U,
//DeadCode MS 07Jun99 				Shape	TroopShape,
//DeadCode MS 07Jun99 				Home	UID_Japan,
//DeadCode MS 07Jun99   				NAT_BLUE,
//DeadCode MS 07Jun99 				MORALE_HIGH,
//DeadCode MS 07Jun99   				Scram_G0_Skill,
//DeadCode MS 07Jun99 				Bombs Weap_Basic
//DeadCode MS 07Jun99   			}
//DeadCode MS 07Jun99  		},

//GROUND MOBILES !!!!
	ItemGroup
	{	Target	UID_CASDefend,	
			GroundGroup
			{
				Posn
				{
					Abs
					{	X	71952933,
						Z	60475514
					}
				},
				Route
				{
					WayPoint  
					{
						Posn	
						{
							Abs	Mortar_Pos00,
							Rel	{Intercept {Mortar_Pos00,Mortar_Pos01},
						 		 Bearing ANGLES_0Deg,
					 			 RangePercent	50,
						 		 Pitch ANGLES_0Deg
							}
						},
						Vel	15,
						Action	wpdmbtrkstopno,
						Range METRES100
					}
				},
				NumInForm		4,
				Formation	SQUAD_BATTLELINE,
				GroundItem	
				{
					BlueArmourBAND,
					Type	SQ_ATank,
					Side	NAT_BLUE,
					Shape	SHAPE_TroopAttack,
					Vel	15,
					MoveCode	GROUND_TAXI
			}	},
			GroundGroup
			{
				Posn
				{
					Abs
					{	X	71939963,
						Z	60475514
					}
				},
				Route
				{
					WayPoint	
					{
						Posn
						{
							Abs
							{	X	71972048,
								Z	60554021
							}
						},
						Vel	30,
						Action	wpdmbtrkstopno,
						Range	0
					}
				},
				NumInForm		6,
				Formation	SQUAD_TRUCKCONVOY,
				GroundItem	
				{
					BlueArmourBAND,
					Type	SQ_ATank,
					Side	NAT_BLUE,
					Shape	UNTANK,
					Vel	30,
					MoveCode	GROUND_TAXI
			}	}
		}
  	};

//--------------------------------
//Fighter Bomber Strike 2


	BattleField
	{
		FileName	FIL_QUICKMISSION_16=QUICKM16.BF,

		AirGroup	
		{
			Route	
			{
				WayPoint	
				{
					Posn	{Abs	Pack_Target}, 
 					Range	METRES5000,
					Action	wpacnoactionno	
				},
				WayPoint  
				{
					Target	Pack_Target,
					Range 	METRES5000,
					Action	wpbombno	
				},
				WayPoint	
				{
					Posn	
						{Abs	UID_AfBlKimpo, 
						 Abs	{Y Scram_G0_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				}
 			},
			
			NumInWing	2,
  			NumInForm	Scram_G0_AC,

			DUTY_DiveIndividual,

			Posn		
				{Abs	Pack_Target, 
			 	 Abs	{Y Scram_G0_Alt},
				 Rel	{Bearing {Random ANGLES_135Deg,90,ANGLES_1Deg},
					 	 Range METRES5000
						}
				},

			AirItem	
			{
				Scram_G0_Squad,
				Home	UID_AfBlKimpo,
  				NAT_BLUE,
				MORALE_HIGH,
  				Scram_G0_Skill,
				Bombs	7,			//MS 31Aug99
				Target Pack_Target
  			}
 		}

	};

//--------------------------------

	BattleField
	{
		FileName	FIL_QUICKMISSION_17=QUICKM17.BF,

		AirGroup	
		{
			Route	
			{
				WayPoint  
				{
					Posn		
						{Abs	Pack_Target, 
						 Abs	{Y FT_2000},
				 		 Rel	{Bearing ANGLES_0Deg,
							 	 Range	METRES200
								} 
						},
					Action	wpacnoactionno	
				}
 			},
			
			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,

				Posn
				{
						Abs	Pack_Target, 
						 Abs	{Y FT_2000}
						
				},

			AirItem	
			{
				Scram_G0_Squad,
				Home	UID_AfBlKimpo,
  				NAT_BLUE,
				MORALE_HIGH,
  				Scram_G0_Skill,
				Bombs Weap_BombRock
  			}
 		}
	};


//TempCode MS 01Mar99 		AirGroup	
//TempCode MS 01Mar99 		{
//TempCode MS 01Mar99 			Route	
//TempCode MS 01Mar99 			{
//TempCode MS 01Mar99 				WayPoint  
//TempCode MS 01Mar99 				{
//TempCode MS 01Mar99 					Posn
//TempCode MS 01Mar99 					{
//TempCode MS 01Mar99 						Abs
//TempCode MS 01Mar99 						{	X	71581184,
//TempCode MS 01Mar99 							Z	59243520,
//TempCode MS 01Mar99 							Y 	FT_1
//TempCode MS 01Mar99 						}
//TempCode MS 01Mar99 					},
//TempCode MS 01Mar99 					Vel 0,
//TempCode MS 01Mar99 					Range	METRES200
//TempCode MS 01Mar99 				}
//TempCode MS 01Mar99  			},
//TempCode MS 01Mar99 			
//TempCode MS 01Mar99 			NumInWing	1,
//TempCode MS 01Mar99   			NumInForm	1,
//TempCode MS 01Mar99 
//TempCode MS 01Mar99   			DUTYMIGCAP,
//TempCode MS 01Mar99 
//TempCode MS 01Mar99 					Posn
//TempCode MS 01Mar99 					{
//TempCode MS 01Mar99 						Abs
//TempCode MS 01Mar99 						{	X	71581184,
//TempCode MS 01Mar99 							Z	59243520,
//TempCode MS 01Mar99 							Y 	FT_1
//TempCode MS 01Mar99 						}						
//TempCode MS 01Mar99 					},
//TempCode MS 01Mar99 
//TempCode MS 01Mar99 			AirItem	
//TempCode MS 01Mar99 			{
//TempCode MS 01Mar99 				SQ_MIG15,
//TempCode MS 01Mar99 				Home	UID_AfBlKimpo,
//TempCode MS 01Mar99   				NAT_RED,
//TempCode MS 01Mar99 				MORALE_HIGH,
//TempCode MS 01Mar99   				Scram_G0_Skill,
//TempCode MS 01Mar99 				Vel 0,
//TempCode MS 01Mar99 				AUTO_NOPPILOT
//TempCode MS 01Mar99   			}
//TempCode MS 01Mar99  		}
//TempCode MS 01Mar99 	};

//						Rel	{Pitch	ANGLES_270Deg,
//							 Range	METRES10
//							}	

//--------------------------------

	BattleField
	{
		FileName	FIL_QUICKMISSION_18=QUICKM18.BF,

		AirGroup	
		{
			Route	
			{
				WayPoint  
				{
					Posn		
						{Abs	Pack_Target, 
						 Abs	{Y Scram_G0_Alt},
				 		 Rel	{Bearing ANGLES_0Deg,
							 	 Range	METRES200
								} 
						},
					Action	wpacnoactionno	
				}
 			},
			
			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,

				Posn
				{
					Abs
					{	X	62644224,
						Z	61542400,
						Y	FT_600
					}
				},

			AirItem	
			{
				Scram_G0_Squad,
				Home	UID_AfBlKimpo,
  				NAT_BLUE,
				MORALE_HIGH,
  				Scram_G0_Skill
  			}
 		}

	};

//--------------------------------

	BattleField
	{
		FileName	FIL_QUICKMISSION_19=QUICKM19.BF,

		AirGroup	
		{
			Route	
			{
				WayPoint  
				{
					Posn		
						{Abs	Pack_Target, 
						 Abs	{Y Scram_G0_Alt},
				 		 Rel	{Bearing ANGLES_0Deg,
							 	 Range	METRES200
								} 
						},
					Action	wpacnoactionno	
				}
 			},
			
			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,

				Posn
				{
					Abs
					{	X	62644224,
						Z	61542400,
						Y	FT_600
					}
				},

			AirItem	
			{
				Scram_G0_Squad,
				Home	UID_AfBlKimpo,
  				NAT_BLUE,
				MORALE_HIGH,
  				Scram_G0_Skill
  			}
 		}

	};

//--------------------------------

	BattleField
	{
		FileName	FIL_QUICKMISSION_20=QUICKM20.BF,

		AirGroup	
		{
			Route	
			{
				WayPoint  
				{
					Posn		
						{Abs	Pack_Target, 
						 Abs	{Y Scram_G0_Alt},
				 		 Rel	{Bearing ANGLES_0Deg,
							 	 Range	METRES200
								} 
						},
					Action	wpacnoactionno	
				}
 			},
			
			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,

				Posn
				{
					Abs
					{	X	62644224,
						Z	61542400,
						Y	FT_600
					}
				},

			AirItem	
			{
				Scram_G0_Squad,
				Home	UID_AfBlKimpo,
  				NAT_BLUE,
				MORALE_HIGH,
  				Scram_G0_Skill
  			}
 		}

	};

/////////////////////////////////////
//
// FAC battlefields
//
//
//
/////////////////////////////////////
	Posn	FACStartDelta=
	{
  		 Rel	{Intercept	{MainObjective,Pack_Targ_F0_E0},
			 Bearing	ANGLES_0Deg,
				 RangePercent	75
				},
		Rel		{Y			METRES1000}
	},

	BattleField
	{
		FileName	FIL_FAC_1TARGET= fac_1.BF,
		Setval	{FriendHomeBase, UID_AfRdSinuiju},
		Setval	{EnemyScoutHomeBase, UID_AfRdSinuiju},
		AirGroup
		{
			Route	
			{
 				WayPoint	
				{
					Target	MainObjective, 
					FACStartDelta,
					Vel		700,
					Action	WP_waitfriendly
				},
 				WayPoint	
				{
					Target	MainObjective,
					FACStartDelta,
					Vel	1500,
					Action	wpstartloopno
				},

 				WayPoint	
				{	Target	Pack_Targ_F0_E0,
					Posn{	Rel	{Y CloudBase}	},
					Vel	1500,
					Action	wpacircleno
				},
 				WayPoint	
				{	Target	Pack_Targ_F0_E1,
					Posn{	Rel	{Y CloudBase}	},
					Vel	1800,
					Action	wpengagetargetno
				},
//DEADCODE JIM 30/03/99 				WayPoint	
//DEADCODE JIM 30/03/99 				{	Target	Pack_Targ_F1_E0,
//DEADCODE JIM 30/03/99 					Posn{	Rel	{Y METRES500}	},
//DEADCODE JIM 30/03/99 					Vel	1500,
//DEADCODE JIM 30/03/99 					Action	wpacircleno
//DEADCODE JIM 30/03/99 				},
//DEADCODE JIM 30/03/99  				WayPoint	
//DEADCODE JIM 30/03/99 				{	Target	Pack_Targ_F1_E1,
//DEADCODE JIM 30/03/99 					Posn{	Rel	{Y METRES500}	},
//DEADCODE JIM 30/03/99 					Vel	1800,
//DEADCODE JIM 30/03/99 					Action	wpengagetargetno
//DEADCODE JIM 30/03/99 				},
//DEADCODE JIM 30/03/99 				WayPoint	
//DEADCODE JIM 30/03/99 				{	Target	Pack_Targ_F2_E0,
//DEADCODE JIM 30/03/99 					Posn{	Rel	{Y METRES500}	},
//DEADCODE JIM 30/03/99 					Vel	1500,
//DEADCODE JIM 30/03/99 					Action	wpacircleno
//DEADCODE JIM 30/03/99 				},
//DEADCODE JIM 30/03/99  				WayPoint	
//DEADCODE JIM 30/03/99 				{	Target	Pack_Targ_F2_E1,
//DEADCODE JIM 30/03/99 					Posn{	Rel	{Y METRES500}	},
//DEADCODE JIM 30/03/99 					Vel	1800,
//DEADCODE JIM 30/03/99 					Action	wpengagetargetno
//DEADCODE JIM 30/03/99 				},

				WayPoint	
				{
					Target	MainObjective,
					FACStartDelta,
					Vel	1000,
					Action	wpstoploopchkno
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_Japan}, 
						 Rel	{Y CloudBase}
						},
					Action	wpalandingno
				}
 			},


			
  			NumInWing	2,
  			NumInForm	1,	//Scram_G1_AC,
			DC_BOMB,											//MS 20May99

  			Posn	{Abs	MainObjective, 
				 FACStartDelta
				},	
			AirItem	  = 
			{
				SQ_T6,
				Home	UID_Japan,
  				NAT_BLUE,
  				SKILL_VETERAN,
  				MORALE_HIGH,
 				MoveCode	AUTO_FAC,
				FriendlyScoutSquad,			//callsign!!!
				CHAR_CAVALIER
  			}
 		}
	};

	BattleField
	{
		FileName	FIL_FAC_2TARGET= fac_2.BF,
		Setval	{FriendHomeBase, UID_AfRdSinuiju},
		Setval	{EnemyScoutHomeBase, UID_AfRdSinuiju},
		AirGroup
		{
			Route	
			{
 				WayPoint	
				{
					Target	MainObjective,
					FACStartDelta,
					Vel		700,
					Action	WP_waitfriendly
				},
 				WayPoint	
				{
					Target	MainObjective,
					FACStartDelta,
					Vel	1500,
					Action	wpstartloopno
				},

 				WayPoint	
				{	Target	Pack_Targ_F0_E0,
					Posn{	Rel	{Y CloudBase}	},
					Vel	1500,
					Action	wpacircleno
				},
 				WayPoint	
				{	Target	Pack_Targ_F0_E1,
					Posn{	Rel	{Y CloudBase}	},
					Vel	1800,
					Action	wpengagetargetno
				},
				WayPoint	
				{	Target	Pack_Targ_F1_E0,
					Posn{	Rel	{Y CloudBase}	},
					Vel	1500,
					Action	wpacircleno
				},
 				WayPoint	
				{	Target	Pack_Targ_F1_E1,
					Posn{	Rel	{Y CloudBase}	},
					Vel	1800,
					Action	wpengagetargetno
				},
//DEADCODE JIM 30/03/99 				WayPoint	
//DEADCODE JIM 30/03/99 				{	Target	Pack_Targ_F2_E0,
//DEADCODE JIM 30/03/99 					Posn{	Rel	{Y METRES500}	},
//DEADCODE JIM 30/03/99 					Vel	1500,
//DEADCODE JIM 30/03/99 					Action	wpacircleno
//DEADCODE JIM 30/03/99 				},
//DEADCODE JIM 30/03/99  				WayPoint	
//DEADCODE JIM 30/03/99 				{	Target	Pack_Targ_F2_E1,
//DEADCODE JIM 30/03/99 					Posn{	Rel	{Y METRES500}	},
//DEADCODE JIM 30/03/99 					Vel	1800,
//DEADCODE JIM 30/03/99 					Action	wpengagetargetno
//DEADCODE JIM 30/03/99 				},

				WayPoint	
				{
					Target	MainObjective,
					FACStartDelta,
					Vel	1000,
					Action	wpstoploopchkno
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_Japan}, 
						 Rel	{Y METRES700}
						},
					Action	wpalandingno
				}
 			},


			
  			NumInWing	2,
  			NumInForm	1,	//Scram_G1_AC,
			DC_BOMB,											//MS 20May99

  			Posn	{Abs	MainObjective, 
				 FACStartDelta
					},	
			AirItem	  = 
			{
				SQ_T6,
				Home	UID_Japan,
  				NAT_BLUE,
  				SKILL_VETERAN,
  				MORALE_HIGH,
 				MoveCode	AUTO_FAC,
				FriendlyScoutSquad,			//callsign!!!
				CHAR_CAVALIER
  			}
 		}
	};
	BattleField
	{
		FileName	FIL_FAC_3TARGET= fac_3.BF,
		Setval	{FriendHomeBase, UID_AfRdSinuiju},
		Setval	{EnemyScoutHomeBase, UID_AfRdSinuiju},
		AirGroup
		{
			Route	
			{
 				WayPoint	
				{
					Target	MainObjective,
					FACStartDelta,
					Vel		700,
					Action	WP_waitfriendly
				},
 				WayPoint	
				{
					Target	MainObjective,
					FACStartDelta,
					Vel	1500,
					Action	wpstartloopno
				},

 				WayPoint	
				{	Target	Pack_Targ_F0_E0,
					Posn{	Rel	{Y CloudBase}	},
					Vel	1500,
					Action	wpacircleno
				},
 				WayPoint	
				{	Target	Pack_Targ_F0_E1,
					Posn{	Rel	{Y CloudBase}	},
					Vel	1800,
					Action	wpengagetargetno
				},
				WayPoint	
				{	Target	Pack_Targ_F1_E0,
					Posn{	Rel	{Y CloudBase}	},
					Vel	1500,
					Action	wpacircleno
				},
 				WayPoint	
				{	Target	Pack_Targ_F1_E1,
					Posn{	Rel	{Y CloudBase}	},
					Vel	1800,
					Action	wpengagetargetno
				},
				WayPoint	
				{	Target	Pack_Targ_F2_E0,
					Posn{	Rel	{Y CloudBase}	},
					Vel	1500,
					Action	wpacircleno
				},
 				WayPoint	
				{	Target	Pack_Targ_F2_E1,
					Posn{	Rel	{Y CloudBase}	},
					Vel	1800,
					Action	wpengagetargetno
				},

				WayPoint	
				{
					Target	MainObjective,
					FACStartDelta,
					Vel	1000,
					Action	wpstoploopchkno
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_Japan}, 
						 Rel	{Y METRES700}
						},
					Action	wpalandingno
				}
 			},


			
  			NumInWing	2,
  			NumInForm	1,	//Scram_G1_AC,
			DC_BOMB,											//MS 20May99

  			Posn	{Abs	MainObjective, 
				 FACStartDelta
					},	
			AirItem	  = 
			{
				SQ_T6,
				Home	UID_Japan,
  				NAT_BLUE,
  				SKILL_VETERAN,
  				MORALE_HIGH,
 				MoveCode	AUTO_FAC,
				FriendlyScoutSquad,			//callsign!!!
				CHAR_CAVALIER
  			}
 		}
	};

	BattleField
	{
		FileName	FIL_TAC_1TARGET= tac_1.BF,
		Setval	{FriendHomeBase, UID_AfRdSinuiju},
		Setval	{EnemyScoutHomeBase, UID_AfRdSinuiju},
		AirGroup
		{
			Route	
			{
 				WayPoint	
				{
					Target	Pack_Targ_F0_E0, 
//					Posn{ Rel	{Y METRES500}	},
					Vel	700,
					Action	WP_waitfriendly
				},
 				WayPoint	
				{
					Posn{	Abs	{Pack_Targ_F0_E0}//,
//							Rel	{Y METRES500}
						},
					Vel	1500,
					Action	wpstartloopno
				},
 				WayPoint	
				{	Target	Pack_Targ_F0_E0,
//					Posn{	Rel	{Y METRES500}	},
					Vel	1500,
					Action	wpacircleno
				},
 				WayPoint	
				{	Target	Pack_Targ_F0_E1,
//					Posn{	Rel	{Y METRES500}	},
					Vel	1800,
					Action	wpengagetargetno
				},
//DEADCODE JIM 30/03/99 				WayPoint	
//DEADCODE JIM 30/03/99 				{	Target	Pack_Targ_F1_E0,
//DEADCODE JIM 30/03/99 					Posn{	Rel	{Y METRES500}	},
//DEADCODE JIM 30/03/99 					Vel	1500,
//DEADCODE JIM 30/03/99 					Action	wpacircleno
//DEADCODE JIM 30/03/99 				},
//DEADCODE JIM 30/03/99  				WayPoint	
//DEADCODE JIM 30/03/99 				{	Target	Pack_Targ_F1_E1,
//DEADCODE JIM 30/03/99 					Posn{	Rel	{Y METRES500}	},
//DEADCODE JIM 30/03/99 					Vel	1800,
//DEADCODE JIM 30/03/99 					Action	wpengagetargetno
//DEADCODE JIM 30/03/99 				},
//DEADCODE JIM 30/03/99 				WayPoint	
//DEADCODE JIM 30/03/99 				{	Target	Pack_Targ_F2_E0,
//DEADCODE JIM 30/03/99 					Posn{	Rel	{Y METRES500}	},
//DEADCODE JIM 30/03/99 					Vel	1500,
//DEADCODE JIM 30/03/99 					Action	wpacircleno
//DEADCODE JIM 30/03/99 				},
//DEADCODE JIM 30/03/99  				WayPoint	
//DEADCODE JIM 30/03/99 				{	Target	Pack_Targ_F2_E1,
//DEADCODE JIM 30/03/99 					Posn{	Rel	{Y METRES500}	},
//DEADCODE JIM 30/03/99 					Vel	1800,
//DEADCODE JIM 30/03/99 					Action	wpengagetargetno
//DEADCODE JIM 30/03/99 				},

				WayPoint	
				{
					Posn	
						{Abs	{MainObjective}//, 
//						 Rel	{Y METRES500}
						},
					Vel	1000,
					Action	wpstoploopchkno
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_Japan}//, 
//						 Rel	{Y METRES500}
						},
					Action	wpalandingno
				}
 			},


			
  			NumInWing	2,
  			NumInForm	1,	//Scram_G1_AC,
			DC_BOMB,											//MS 20May99

  			Posn	{Abs	MainObjective, 
  					 Rel	{Y METRES500}
					},	
			AirItem	  = 
			{
				SQ_T6,
				SUPMIG,
				Home	MainObjective,
  				NAT_BLUE,
  				SKILL_VETERAN,
  				MORALE_HIGH,
 				MoveCode	AUTO_FAC,
				FriendlyScoutSquad,			//callsign!!!
				CHAR_CAVALIER
  			}
 		};

		ItemGroup					//DAW 10Sep99
		{	Target	Pack_Targ_F0_E0,
			SimpleItem 
			{
				Posn { Abs	Pack_Targ_F0_E0,Rel	{Z	METRES10}	},
				JEEP1
		}	}
//DEADCODE JIM 31/03/99 		;
//DEADCODE JIM 31/03/99 		SimpleItem 
//DEADCODE JIM 31/03/99 		{
//DEADCODE JIM 31/03/99 			Posn { Abs	Pack_Targ_F1_E0,Rel	{Z	METRES500}	},
//DEADCODE JIM 31/03/99 			JEEP1,
//DEADCODE JIM 31/03/99 		};
//DEADCODE JIM 31/03/99 		SimpleItem 
//DEADCODE JIM 31/03/99 		{
//DEADCODE JIM 31/03/99 			Posn { Abs	Pack_Targ_F2_E0,Rel	{Z	METRES500}	},
//DEADCODE JIM 31/03/99 			JEEP1,
//DEADCODE JIM 31/03/99 		};


	};

	BattleField
	{
		FileName	FIL_TAC_2TARGET= tac_2.BF,
		Setval	{FriendHomeBase, UID_AfRdSinuiju},
		Setval	{EnemyScoutHomeBase, UID_AfRdSinuiju},
		AirGroup
		{
			Route	
			{
 				WayPoint	
				{
					Target	Pack_Targ_F0_E0, 
//					Posn{ Rel	{Y METRES500}	},
					Vel		700,
					Action	WP_waitfriendly
				},
 				WayPoint	
				{
					Posn{	Abs	{Pack_Targ_F0_E0}//,
//							Rel	{Y METRES500}
						},
					Vel	1500,
					Action	wpstartloopno
				},
 				WayPoint	
				{	Target	Pack_Targ_F0_E0,
//					Posn{	Rel	{Y METRES500}	},
					Vel	1500,
					Action	wpacircleno
				},
 				WayPoint	
				{	Target	Pack_Targ_F0_E1,
//					Posn{	Rel	{Y METRES500}	},
					Vel	1800,
					Action	wpengagetargetno
				},
				WayPoint	
				{	Target	Pack_Targ_F1_E0,
//					Posn{	Rel	{Y METRES500}	},
					Vel	1500,
					Action	wpacircleno
				},
 				WayPoint	
				{	Target	Pack_Targ_F1_E1,
//					Posn{	Rel	{Y METRES500}	},
					Vel	1800,
					Action	wpengagetargetno
				},
//DEADCODE JIM 30/03/99 				WayPoint	
//DEADCODE JIM 30/03/99 				{	Target	Pack_Targ_F2_E0,
//DEADCODE JIM 30/03/99 					Posn{	Rel	{Y METRES500}	},
//DEADCODE JIM 30/03/99 					Vel	1500,
//DEADCODE JIM 30/03/99 					Action	wpacircleno
//DEADCODE JIM 30/03/99 				},
//DEADCODE JIM 30/03/99  				WayPoint	
//DEADCODE JIM 30/03/99 				{	Target	Pack_Targ_F2_E1,
//DEADCODE JIM 30/03/99 					Posn{	Rel	{Y METRES500}	},
//DEADCODE JIM 30/03/99 					Vel	1800,
//DEADCODE JIM 30/03/99 					Action	wpengagetargetno
//DEADCODE JIM 30/03/99 				},

				WayPoint	
				{
					Posn	
						{Abs	{MainObjective}//, 
//						 Rel	{Y METRES500}
						},
					Vel	1000,
					Action	wpstoploopchkno
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_Japan}//, 
//						 Rel	{Y METRES500}
						},
					Action	wpalandingno
				}
 			},


			
  			NumInWing	2,
  			NumInForm	1,	//Scram_G1_AC,
			DC_BOMB,											//MS 20May99

  			Posn	{Abs	MainObjective, 
  					 Rel	{Y METRES500}
					},	
			AirItem	  = 
			{
				SQ_T6,
				SUPMIG,
				Home	MainObjective,
  				NAT_BLUE,
  				SKILL_VETERAN,
  				MORALE_HIGH,
 				MoveCode	AUTO_FAC,
				FriendlyScoutSquad,			//callsign!!!
				CHAR_CAVALIER
  			}
 		};
		ItemGroup					//DAW 10Sep99
		{	Target	Pack_Targ_F0_E0,
			SimpleItem 
			{
				Posn { Abs	Pack_Targ_F0_E0,Rel	{Z	METRES10}	},
				JEEP1
			};
			SimpleItem 
			{
				Posn { Abs	Pack_Targ_F1_E0,Rel	{Z	METRES10}	},
				JEEP1
			}
		}
//DEADCODE JIM 31/03/99 		;
//DEADCODE JIM 31/03/99 		SimpleItem 
//DEADCODE JIM 31/03/99 		{
//DEADCODE JIM 31/03/99 			Posn { Abs	Pack_Targ_F2_E0,Rel	{Z	METRES500}	},
//DEADCODE JIM 31/03/99 			JEEP1,
//DEADCODE JIM 31/03/99 		};
	};

	BattleField
	{
		FileName	FIL_TAC_3TARGET= tac_3.BF,
		Setval	{FriendHomeBase, UID_AfRdSinuiju},
		Setval	{EnemyScoutHomeBase, UID_AfRdSinuiju},
		AirGroup
		{
			Route	
			{
 				WayPoint	
				{
					Target	Pack_Targ_F0_E0, 
//					Posn{ Rel	{Y METRES500}	},
					Vel		700,
					Action	WP_waitfriendly
				},
 				WayPoint	
				{
					Posn{	Abs	{Pack_Targ_F0_E0}//,
//							Rel	{Y METRES500}
						},
					Vel	1500,
					Action	wpstartloopno
				},

 				WayPoint	
				{	Target	Pack_Targ_F0_E0,
//					Posn{	Rel	{Y METRES500}	},
					Vel	1500,
					Action	wpacircleno
				},
 				WayPoint	
				{	Target	Pack_Targ_F0_E1,
//					Posn{	Rel	{Y METRES500}	},
					Vel	1800,
					Action	wpengagetargetno
				},
				WayPoint	
				{	Target	Pack_Targ_F1_E0,
//					Posn{	Rel	{Y METRES500}	},
					Vel	1500,
					Action	wpacircleno
				},
 				WayPoint	
				{	Target	Pack_Targ_F1_E1,
//					Posn{	Rel	{Y METRES500}	},
					Vel	1800,
					Action	wpengagetargetno
				},
				WayPoint	
				{	Target	Pack_Targ_F2_E0,
//					Posn{	Rel	{Y METRES500}	},
					Vel	1500,
					Action	wpacircleno
				},
 				WayPoint	
				{	Target	Pack_Targ_F2_E1,
//					Posn{	Rel	{Y METRES500}	},
					Vel	1800,
					Action	wpengagetargetno
				},

				WayPoint	
				{
					Posn	
						{Abs	{MainObjective}//, 
//						 Rel	{Y METRES500}
						},
					Vel	1000,
					Action	wpstoploopchkno
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_Japan}, 
						 	 Abs	{Y FT_10000,X -MILES200}
						},
					Action	wpalandingno
				}
 			},


			
  			NumInWing	2,
  			NumInForm	1,	//Scram_G1_AC,
			DC_BOMB,											//MS 20May99

  			Posn	{Abs	MainObjective, 
  					 Rel	{Y METRES500}
					},	
			AirItem	  = 
			{
				SQ_T6,
				SUPMIG,
				Home	MainObjective,
  				NAT_BLUE,
  				SKILL_VETERAN,
  				MORALE_HIGH,
 				MoveCode	AUTO_FAC,
				FriendlyScoutSquad,			//callsign!!!
				CHAR_CAVALIER
  			}
 		};
		ItemGroup					//DAW 10Sep99
		{	Target	Pack_Targ_F0_E0,
			SimpleItem 
			{
				Posn { Abs	Pack_Targ_F0_E0,Rel	{Z	METRES10}	},
				JEEP1
			};
			SimpleItem 
			{
				Posn { Abs	Pack_Targ_F1_E0,Rel	{Z	METRES10}	},
				JEEP1
			};
			SimpleItem 
			{
				Posn { Abs	Pack_Targ_F2_E0,Rel	{Z	METRES10}	},
				JEEP1
			}
		}
	};


//--------------------------------
//AIRFIELD BUZZ: HELICOPTER	LAND

	BattleField
	{
		FileName	FIL_AFBUZZ00=AFBUZZ00.BF,

	 	Setval	{RandAngle, Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg}},
		Setval	{TroopShape, HO3S},
	 	Setval	{AngleStepSize, Int {Random 1,2,1}},
	 	Setval	{HeightSize, Y {Random FT_1000,3,FT_1000}},

		AirGroup	
		{
			Route	
			{
				WayPoint  
				{
  					Posn	{Abs	UID_PARK1,
							 Abs	{Y FT_300},
						 	 Rel	{Intercept {UID_PARK0,UID_PARK1},
									 Bearing ANGLES_0Deg,
					 		 		 Range	METRES500,
									 Pitch ANGLES_0Deg
									}
							},
					Action	wpacnoactionno,
					Vel 200	
				},
				WayPoint  
				{
  					Posn	{Abs	UID_Japan,
						 	 Abs	{Y FT_2000,Z -MILES200}
							},
					Range METRES1000,
					Vel 500,
					Action	wpstopno	
				}

 			},
			
			NumInWing	1,
  			NumInForm	1,
			Formation	SQUAD_FLATV,
			DC_BOMB,											//MS 20May99

			Posn	{Abs	UID_PARK0,
					 Abs	{Y FT_300}
					},

			AirItem	
			{
				SQ_4U,
				Shape	TroopShape,
				Home	UID_Japan,
  				NAT_BLUE,
				MORALE_HIGH,
  				SKILL_HERO,
				Vel 100
  			}
 		}
	};

//--------------------------------
//AIRFIELD BUZZ: TRANSPORT

	BattleField
	{
		FileName	FIL_AFBUZZ01=AFBUZZ01.BF,
		Setval	{RangeStepSize, Int {Random 0,2,1}},
	 	Setval	{RandAngle, Bearing {Random ANGLES_0Deg,2,ANGLES_180Deg}},
		Setval	{TroopShape,Shape(List RangeStepSize, C47, C54)},
	 	Setval	{HeightSize, Y {Random FT_500,3,FT_1000}},

		AirGroup	
		{
			Route	
			{
				WayPoint  
				{
  					Posn	{Abs	UID_PARK1,
							 Abs	{Y HeightSize},
						 	 Rel	{Intercept {UID_PARK0,UID_PARK1},
									 Bearing RandAngle,
					 		 		 Range	KM10,
									 Pitch ANGLES_0Deg
									}
							},
					Action	wpacnoactionno,
					Vel 900	
				},
				WayPoint  
				{
  					Posn	{Abs	UID_Japan,
						 	 Abs	{Y FT_5000,Z -MILES200}
							},
					Range METRES1000,
					Action	wpstopno	
				}

 			},
			
			NumInWing	1,
  			NumInForm	1,
			Formation	SQUAD_FLATV,
			DC_BOMB,											//MS 20May99

			Posn	{Abs	UID_PARK0,
					 Abs	{Y HeightSize},
				 	 Rel	{Intercept {UID_PARK0,UID_PARK1},
							 Bearing {Select RandAngle,1,ANGLES_180Deg},
			 		 		 Range	METRES1000,
							 Pitch ANGLES_0Deg
							}
					},

			AirItem	
			{
				SQ_4U,
				Shape	TroopShape,
				Home	UID_Japan,
  				NAT_BLUE,
				MORALE_HIGH,
  				SKILL_HERO,
				Vel 900
  			}
 		}
	};

//--------------------------------
//AIRFIELD BUZZ: FIGHTERS

	BattleField
	{
		FileName	FIL_AFBUZZ02=AFBUZZ02.BF,
	 	Setval	{RandAngle, Bearing {Random ANGLES_0Deg,9,ANGLES_45Deg}},
		Setval	{RangeStepSize, Int {Random 0,2,1}},
		Setval	{TroopShape,Shape(List RangeStepSize, MET, F82)},
	 	Setval	{HeightSize, Y {Random FT_500,4,FT_500}},
		Setval	{FormSize00, Int {Random 0,3,2}},

		AirGroup	
		{
			Route	
			{
				WayPoint  
				{
  					Posn	{Abs	UID_PARK0,
							 Abs	{Y HeightSize},
						 	 Rel	{Intercept {UID_PARK0,UID_PARK1},
									 Bearing RandAngle,
					 		 		 Range	METRES1000,
									 Pitch ANGLES_0Deg
									}
							},
					Action	wpacnoactionno,
					Vel 300	
				},
				WayPoint  
				{
  					Posn	{Abs	UID_Japan,
						 	 Abs	{Y FT_10000,Z -MILES200}
							},
					Range METRES1000,
					Action	wpstopno	
				}
 			},
			
			NumInWing	2,
  			NumInForm	FormSize00,
			Formation	SQUAD_FLATV,
			DC_BOMB,											//MS 20May99

			Posn	{Abs	UID_PARK0,
					 Abs	{Y HeightSize},
				 	 Rel	{Intercept {UID_PARK0,UID_PARK1},
							 Bearing {Select RandAngle,1,ANGLES_180Deg},
			 		 		 Range	{Random METRES10,5,METRES500},
							 Pitch ANGLES_0Deg
							}
					},

			AirItem	
			{
				SQ_4U,
				Shape	TroopShape,
				Home	UID_Japan,
  				NAT_BLUE,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		}
	};


//--------------------------------
//AIRFIELD BUZZ: NAVY AIRCRAFT

	BattleField
	{
		FileName	FIL_AFBUZZ03=AFBUZZ03.BF,

	 	Setval	{RandAngle, Bearing {Random ANGLES_0Deg,9,ANGLES_45Deg}},
		Setval	{RangeStepSize, Int {Random 0,2,1}},
		Setval	{TroopShape,Shape(List RangeStepSize, CORS, HO3S)},
	 	Setval	{HeightSize, Y {Random FT_500,4,FT_500}},
		Setval	{FormSize00, Int {Random 0,3,1}},

		AirGroup	
		{
			Route	
			{
				WayPoint  
				{
  					Posn	{Abs	UID_PARK0,
							 Abs	{Y HeightSize},
						 	 Rel	{Intercept {UID_PARK0,UID_PARK1},
									 Bearing RandAngle,
					 		 		 Range	METRES1000,
									 Pitch ANGLES_0Deg
									}
							},
					Action	wpacnoactionno
				},
				WayPoint  
				{
  					Posn	{Abs	UID_Japan,
						 	 Abs	{Y FT_10000,Z -MILES200}
							},
					Range METRES1000,
					Action	wpstopno	
				}
 			},
			
			NumInWing	2,
  			NumInForm	FormSize00,
			Formation	SQUAD_FLATV,
			DC_BOMB,											//MS 20May99

			Posn	{Abs	UID_PARK0,
					 Abs	{Y HeightSize},
				 	 Rel	{Intercept {UID_PARK0,UID_PARK1},
							 Bearing {Select RandAngle,1,ANGLES_180Deg},
			 		 		 Range	{Random METRES10,5,METRES500},
							 Pitch ANGLES_0Deg
							}
					},

			AirItem	
			{
				SQ_4U,
				Shape	TroopShape,
				Home	UID_Japan,
  				NAT_BLUE,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		}
	};

//--------------------------------
//EGRESS BUZZ: GENERAL

	BattleField
	{
		FileName	FIL_RVBUZZ00=RVBUZZ00.BF,
	 	Setval	{RandAngle, Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg}},
		Setval	{RangeStepSize, Int {Random 0,3,1}},
		Setval	{TroopShape,Shape(List RangeStepSize, HO3S, CORS, CORS)},
	 	Setval	{AngleStepSize, Int {Random 1,2,1}},
	 	Setval	{HeightSize, Y {Random FT_6000,8,FT_1000}},
		Setval	{FormSize00, Int {Random 0,2,1}},

		AirGroup	
		{
			Route	
			{
				WayPoint  
				{
  					Posn	{Abs	MainObjective,
						 	 Abs	{Y HeightSize},
						 	 Rel	{Bearing ANGLES_0Deg,
					 		 		 Range	METRES2000,
									 Pitch ANGLES_0Deg
									}
							},
					Action	wpstartloopno
				},
				WayPoint  
				{
  					Posn	{Abs	MainObjective,
						 	 Abs	{Y HeightSize},
						 	 Rel	{Bearing ANGLES_120Deg,
					 		 		 Range	METRES2000,
									 Pitch ANGLES_0Deg
									}
							},
					Action	wpacnoactionno		
				},
				WayPoint  
				{
  					Posn	{Abs	MainObjective,
						 	 Abs	{Y HeightSize},
						 	 Rel	{Bearing ANGLES_240Deg,
					 		 		 Range	METRES2000,
									 Pitch ANGLES_0Deg
									}
							},
					Action	wpstoploopchkno
				},
				WayPoint  
				{
  					Posn	{Abs	UID_Japan,
						 	 Abs	{Y FT_10000,Z -MILES200}
							},
					Range METRES1000,
					Action	wpstopno	
				}

 			},
			
			NumInWing	2,
  			NumInForm	FormSize00,
			Formation	SQUAD_FLATV,
			DC_BOMB,											//MS 20May99

 					Posn	{Abs	MainObjective,
					 	 Abs	{Y HeightSize},
					 	 Rel	{Bearing ANGLES_240Deg,
				 		 		 Range	METRES2000,
								 Pitch ANGLES_0Deg
								}
						},

			AirItem	
			{
//TempCode MS 15Apr99 				SQ_F51,
				SQ_4U,
				Shape	TroopShape,
				Home	UID_Japan,
  				NAT_BLUE,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		}
	};

//--------------------------------
//RENDEZVOUS BUZZ: OTHER

	BattleField
	{
		FileName	FIL_RVBUZZ01=RVBUZZ01.BF,

	 	Setval	{RandAngle, Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg}},
		Setval	{RangeStepSize, Int {Random 0,1,1}},

		AirGroup	
		{
			Route	
			{
				WayPoint  
				{
  					Posn	{Abs	UID_PARK0,
						 	 Abs	{Y FT_1000},
						 	 Rel	{Bearing {Random RandAngle,3,ANGLES_90Deg},
					 		 		 Range	METRES500
									}
							},
					Action	wpacnoactionno	
				},
				WayPoint  
				{
  					Posn	{Abs	UID_PARK0,
						 	 Abs	{Y FT_2000},
						 	 Rel	{Bearing RandAngle,
					 		 		 Range	METRES500
									}
							},
					Range METRES1000,
					Action	wpacnoactionno	
				}
 			},
			
			NumInWing	2,
  			NumInForm	4,
			Formation	SQUAD_FLATV,
			DC_BOMB,											//MS 20May99

			Posn	{Abs	UID_PARK0,
				 	 Abs	{Y FT_1000},
				 	 Rel	{Bearing {Select RandAngle,1,ANGLES_180Deg},
			 		 		 Range	METRES500
							}
					},

			AirItem	
			{
				SQ_F51,
				Shape	CORS,
//				Shape {List RangeStepSize,C54,C47},
				Home	UID_AfBlKimpo,
  				NAT_BLUE,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		}
	};
