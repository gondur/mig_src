//------------------------------------------------------------------------------
//Filename       introbf.inc
//System         
//Author         R. Hyde 
//Date           Fri 10 Jan 1997
//Description    
//------------------------------------------------------------------------------

//---------------------------------------------------------------------------



	BattleField
	{
		FileName	BF_F51AIREVAC=BFF51AIR.BF,
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{FriendHomeBase}, 
						 Abs	{Y FT_2000},	
						 Rel	{Bearing	ANGLES_180Deg,
								 Range	METRES1000
								}
						},
					Action	wpacnoactionno
				}
 			},

  			DUTYMIGCAP,

  			Posn	{Abs	{FriendHomeBase}, 
					 	Abs	{Y FT_TakeOff}
  					},

  		   AirItem	
  			{
  				NAT_RED,
  				SKILL_ACE,
  				MORALE_HIGH,
 				MoveCode	AUTO_TAKEOFF,
				Home	FriendHomeBase,
				CHAR_CAVALIER
  			}
 		}
	};


	BattleField
	{
		FileName	BF_F51ATTACKNKFIELD = BF51NKAF.BF
	};

	BattleField
	{
		FileName	BF_F51ATTACKNKCOLUMN = BF51NKCL.BF	
	};
	BattleField
	{
		FileName	BF_F80ATTACKNKHQ = BF80NKHQ.BF	
	};
	BattleField
	{
		FileName	BF_F80BOWLINGALLEY = BF80ALLY.BF	
	};
	BattleField
	{
		FileName	BF_F80PUSANBREAKOUT = BF80BRKT.BF	
	};
	BattleField
	{
		FileName	BF_F86BOUNCEDBYMIGS = BF86BMIG.BF		
	};
	BattleField
	{
		FileName	BF_F86FIGHTERSWEEP = BF86SWEP.BF
	};
	BattleField
	{
		FileName	BF_F84YALUBRIDGE = BF84YALU.BF	
	};
