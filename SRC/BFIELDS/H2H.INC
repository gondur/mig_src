//;;------------------------------------------------------------------------------
//;;Filename       h2h.inc
//;;System         
//;;Author         R. Hyde 
//;;Date           Thu 5 Sep 1996
//;;Description    
//;;------------------------------------------------------------------------------




//--------------------------------
	BattleField
	{
		FileName	FIL_H2HRandom=H2HRAND.BF,
		Setval	{FriendHomeBase, UID_NODE_AnTung},
		AirGroup
		{
			Route	
			{
				WayPoint
				{
					Posn	
						{Abs	{FriendHomeBase}, 
						 Abs	{Y FT_6000},	
						 Rel	{Bearing	ANGLES_180Deg,
								 Range	METRES1000
								}
						},
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	
						{Abs	{FriendHomeBase}, 
						 Abs	{Y FT_6000},	
						 Rel	{Bearing	ANGLES_270Deg,
								 Range	METRES1000
								}
						},
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	
						{Abs	{FriendHomeBase}, 
						 Abs	{Y FT_6000},	
						 Rel	{Bearing	ANGLES_0Deg,
								 Range	METRES1000
								}
						},
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	
						{Abs	{FriendHomeBase}, 
						 Abs	{Y FT_6000},	
						 Rel	{Bearing	ANGLES_90Deg,
								 Range	METRES1000
								}
						},
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	
						{Abs	{FriendHomeBase}, 
						 Abs	{Y FT_6000},	
						 Rel	{Bearing	ANGLES_180Deg,
								 Range	METRES1000
								}
						},
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Target	FriendHomeBase, 
					Action	wpalandingno,
					Range	METRES1000
				}
 			},

  			DUTYCAP,
			Formation	FORM_RANDOM,

  			Posn	{Abs	{FriendHomeBase}, 
  					 Abs	{Y FT_6000}
  					},

  			NumInWing	50,
			NumInForm	amberstrength;
//DeadCode ARM 30Oct96   			NumInForm	2,



		   AirItem	
			{
//DeadCode JIM 04Mar99 				PS_PLAYER,
				NAT_RED,
				SKILL_ACE,
				MORALE_HIGH,
				Home		FriendHomeBase,
				CHAR_CAVALIER
			}
		}
	};



//--------------------------------
	BattleField
	{
		FileName	FIL_H2HExplode=H2HEXP.BF,
		Setval	{FriendHomeBase, UID_NODE_AnTung},
		AirGroup
		{
			Route	
			{
				WayPoint
				{
					Posn	
						{Abs	{FriendHomeBase}, 
						 Abs	{Y FT_6000},	
						 Rel	{Bearing	ANGLES_0Deg,
								 Range	METRES8000
								}
						},
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Target	FriendHomeBase, 
					Action	wpalandingno,
					Range	METRES1000
				}
 			},

  			DUTYCAP,
			Formation	FORM_EXPLODE,

  			Posn	{Abs	{FriendHomeBase}, 
  					 Abs	{Y FT_6000}
  					},

  			NumInWing	50,
			NumInForm	amberstrength;
//DeadCode ARM 30Oct96   			NumInForm	8,



		   AirItem	
			{
//DeadCode JIM 04Mar99 				PS_PLAYER,
				NAT_RED,
				SKILL_ACE,
				MORALE_HIGH,
				Home		FriendHomeBase,
				CHAR_CAVALIER
			}
		}
	};




//--------------------------------
	BattleField
	{
		FileName	FIL_H2HImplode=H2HIMP.BF,
		Setval	{FriendHomeBase, UID_NODE_AnTung},
		AirGroup
		{
			Route	
			{
				WayPoint
				{
					Posn	
						{Abs	{FriendHomeBase}, 
						 Abs	{Y FT_6000},	
						 Rel	{Bearing	ANGLES_180Deg,
								 Range	METRES8000
								}
						},
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Target	FriendHomeBase, 
					Action	wpalandingno,
					Range	METRES1000
				}
 			},

  			DUTYCAP,
			Formation	FORM_IMPLODE,

  			Posn	{Abs	{FriendHomeBase}, 
  					 Abs	{Y FT_6000}
  					},

  			NumInWing	50,
			NumInForm	amberstrength;
//DeadCode ARM 30Oct96   			NumInForm	8,



		   AirItem	
			{
//DeadCode JIM 04Mar99 				PS_PLAYER,
				NAT_RED,
				SKILL_ACE,
				MORALE_HIGH,
				Home		FriendHomeBase,
				CHAR_CAVALIER
			}
		}
	};
