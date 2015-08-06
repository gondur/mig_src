//------------------------------------------------------------------------------
//Filename       anmradio.h
//System         
//Author         Robert Slater
//Date           Thu 4 Feb 1999
//Description    
//				Radio chatter messages triggered by damage effects...
//
//
//------------------------------------------------------------------------------
#ifndef	ANMRADIO_Included
#define	ANMRADIO_Included

#define	DEFAULT_ANMRADIO 0



enum	RadioDamage
{
	RADIO_NULL = 0,
	RADIO_GENERAL_LV1,
	RADIO_GENERAL_LV2,
	RADIO_BLACKSMOKE,
	RADIO_FUELLEAK,
	RADIO_BADNEWS
};

struct	HitEffectRecord;

class	DamageChat
{
	AirStrucPtr	acHit;
	AirStrucPtr	acHitter;
	AirStrucPtr	buddy;
	AirStrucPtr	leader;
	Bool		acHitIsFriend;


public:

	void	ExecuteRadio(ItemPtr,ItemPtr,HitEffectRecord&);		//RJS 04Feb99

	DamageChat();

	void	PlayerSideBlewUp(AirStrucPtr);						//RDH 29Apr99
	void	OtherSideBlewUp(AirStrucPtr,AirStrucPtr,bool);		//RDH 20May99
	void	PlayerSidePiledIn(AirStrucPtr);						//RDH 29Apr99
	void	SayWeapon(SLong);									//RJS 13May99



private:

	void	PlayerSideDamageLevel1();
	void	PlayerSideDamageLevel2();
	void	OtherSideDamageLevel1();
	void	OtherSideDamageLevel2();
	void	FuelLeak();
	void	LeaderLeaking();
	void	FollowerLeaking();
	void	FuelLeakMsg(AirStrucPtr);

	void	BlackSmoke();
	void	SmokingBadly(AirStrucPtr);
	void	BlackSmokeMsg(AirStrucPtr);

	void	EjectMsg(AirStrucPtr);

	void	PlayerSideKilled();
	void	OtherSideKilled();

	void	AlertGoHome(AirStrucPtr);

};

extern	DamageChat	_DamageChat;

#endif
