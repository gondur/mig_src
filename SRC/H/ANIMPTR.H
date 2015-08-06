#ifdef	NDEBUG
#define NANIMDEBUG
#endif

#define	NANIMDEBUG	//THIS LINE DISABLES ANIMATION DEBUGGING!!!!!
//////////////////////////////////////////////////////////////////////////
class	GrpMinAnimData;
class	SunAnimData;
class	ExplodeAnimData;
class	FireAnimData;
class	BalloonAnimData;
class	BarageAnimData;
class	TroopAnimData;
class	TrainAnimData;
class	BlokesAnimData;					
class	WeapAnimData;
class	MoveGunAnimData;
class	TwoGunAnimData;
class	AircraftAnimData;
class	PolyPitAnimData;
class	LauncherAnimData;
class	WindsocAnimData;
class	CloneAnimData;
class	FlareAnimData;
class	ParachuteAnimData;
class	ThugAnimData;
class	MissileAnimData;
class	DebrisAnimData;
class	SmokeTrailAnimData;
struct	Coords3DList;						
class	MinAnimData;
 
typedef	char	(MinAnimData::*Animfieldref);
typedef	char	(MinAnimData::*AFR);

class	animptr
{
	//This anim class has been re-written by
	//RJS .... 30 June 1999

	void*	ptr;
#ifndef	NDEBUG
	ULong	size;		//bit 9 = minanim >... (23 anim flags)
						//1st 9 bits = user anim size
						//or size of group...
#endif
public:

	animptr()	
	{
		ptr=NULL;
#ifndef	NDEBUG
		size = 0;
#endif
	}

	void	operator = (UByteP a){ptr = a;};
	UByte&	operator[] (int a);
	UByte&	operator[] (SWord a);
	UByte&	operator[] (UWord a);
	UByte&	operator[] (UByte a);
	Bool	operator == (void* a){if (ptr==a) return TRUE; return FALSE;}
	int		operator - (animptr& a);
	Bool	operator != (void* a){if (ptr!=a) return TRUE; return FALSE;}
	void	operator += (int a);
	void	operator ++ ();
	UByteP	operator & ();
	ULong	Offset(void*	a);

#ifndef	NANIMDEBUG
void	MemTest();
void	Delete()	{delete [](char*)ptr; ptr=NULL; size = 0;}
void	operator = (animptr& a){ptr = a.ptr; size = a.size;};
void	operator = (int a){size = ULong(a);if (a==0)ptr = NULL;};

operator MinAnimData*();
operator GrpMinAnimData*();
operator SunAnimData*();
operator ExplodeAnimData*();
operator FireAnimData*();
operator BalloonAnimData*();
operator BarageAnimData*();
operator TroopAnimData*();
operator TrainAnimData*();
operator BlokesAnimData*();		
operator WeapAnimData*();
operator MoveGunAnimData*();
operator TwoGunAnimData*();
operator AircraftAnimData*();
operator PolyPitAnimData*();
operator LauncherAnimData*();
operator WindsocAnimData*();
operator CloneAnimData*();
operator FlareAnimData*();
operator ParachuteAnimData*();
operator ThugAnimData*();
operator MissileAnimData*();
operator DebrisAnimData*();
operator SmokeTrailAnimData*();
operator Coords3DList*();
#else
void	Delete()	{delete [](char*)ptr; ptr=NULL;}
void	operator = (animptr& a){ptr = a.ptr;};
void	operator = (int a){if (a==0)ptr = NULL;};

operator MinAnimData*(){return (MinAnimData*)ptr;}
operator GrpMinAnimData*(){return (GrpMinAnimData*)ptr;}
operator SunAnimData*(){return (SunAnimData*)ptr;}
operator ExplodeAnimData*(){return (ExplodeAnimData*)ptr;}
operator FireAnimData*(){return (FireAnimData*)ptr;}
operator BalloonAnimData*(){return (BalloonAnimData*)ptr;}
operator BarageAnimData*(){return (BarageAnimData*)ptr;}
operator TroopAnimData*(){return (TroopAnimData*)ptr;}
operator TrainAnimData*(){return (TrainAnimData*)ptr;}
operator BlokesAnimData*(){return (BlokesAnimData*)ptr;}
operator WeapAnimData*(){return (WeapAnimData*)ptr;}
operator MoveGunAnimData*(){return (MoveGunAnimData*)ptr;}
operator TwoGunAnimData*(){return (TwoGunAnimData*)ptr;}
operator AircraftAnimData*(){return (AircraftAnimData*)ptr;}
operator PolyPitAnimData*(){return (PolyPitAnimData*)ptr;}
operator LauncherAnimData*(){return (LauncherAnimData*)ptr;}
operator WindsocAnimData*(){return (WindsocAnimData*)ptr;}
operator CloneAnimData*(){return (CloneAnimData*)ptr;}
operator FlareAnimData*(){return (FlareAnimData*)ptr;}
operator ParachuteAnimData*(){return (ParachuteAnimData*)ptr;}
operator ThugAnimData*(){return (ThugAnimData*)ptr;}
operator MissileAnimData*(){return (MissileAnimData*)ptr;}
operator DebrisAnimData*(){return (DebrisAnimData*)ptr;}
operator SmokeTrailAnimData*(){return (SmokeTrailAnimData*)ptr;}
operator Coords3DList*(){return (Coords3DList*)ptr;}
#endif


};


inline UByte&	animptr::operator[] (int a)
{
#ifndef	NANIMDEBUG
	assert((size&~(1<<MINANIM))>a);
#endif
	return UByteP(ptr)[a];
}

inline UByte&	animptr::operator[] (SWord a)
{
#ifndef	NANIMDEBUG
	assert((size&~(1<<MINANIM))>a);
#endif
	return UByteP(ptr)[a];
}

inline UByte&	animptr::operator[] (UWord a)
{
#ifndef	NANIMDEBUG
	assert((size&~(1<<MINANIM))>a);
#endif
	return UByteP(ptr)[a];
}

inline UByte&	animptr::operator[] (UByte a)
{
#ifndef	NANIMDEBUG
	assert((size&~(1<<MINANIM))>a);
#endif
	return UByteP(ptr)[a];
}

inline void	animptr::operator += (int a)
{
	ptr = (void*)((UByteP)ptr + a);
#ifndef	NANIMDEBUG
	assert((size&0x3ff) >= a);
	size -= ULong(a);
	if ((size & 0x3ff)==0)	ptr = 0;							//RJS 26May99
#endif
}

inline void	animptr::operator ++ ()
{
	ptr = (void*)((UByteP)ptr + 1);
#ifndef	NANIMDEBUG
	assert((size&0x3ff) >= 1);
	size -= 1;
	if ((size & 0x3ff)==0)	ptr = 0;							//RJS 26May99
#endif
}

#ifndef	NANIMDEBUG
#define	AnimAssert	assert

animptr::operator MinAnimData*(){AnimAssert(size & (1<<MINANIM)); return (MinAnimData*)ptr;};
animptr::operator GrpMinAnimData*(){AnimAssert(size & (1<<MINANIM)); return (GrpMinAnimData*)ptr;};
animptr::operator SunAnimData*(){AnimAssert(size & (1<<SUNANIM)); return (SunAnimData*)ptr;};
animptr::operator ExplodeAnimData*(){INT3; return (ExplodeAnimData*)ptr;};
animptr::operator FireAnimData*(){INT3; return (FireAnimData*)ptr;};
animptr::operator BalloonAnimData*(){INT3; return (BalloonAnimData*)ptr;};
animptr::operator BarageAnimData*(){AnimAssert(size & (1<<BARAGEANIM)); return (BarageAnimData*)ptr;};
animptr::operator TroopAnimData*(){AnimAssert(size & (1<<TROOPANIM)); return (TroopAnimData*)ptr;};
animptr::operator TrainAnimData*(){AnimAssert(size & (1<<TRAINANIM)); return (TrainAnimData*)ptr;};
animptr::operator BlokesAnimData*(){AnimAssert(size & (1<<BLOKESANIM)); return (BlokesAnimData*)ptr;};		
animptr::operator WeapAnimData*(){AnimAssert(size & (1<<WEAPANIM)); return (WeapAnimData*)ptr;};
animptr::operator MoveGunAnimData*(){AnimAssert(size & (1<<MOVEGUNANIM)); return (MoveGunAnimData*)ptr;};
animptr::operator TwoGunAnimData*(){AnimAssert(size & (1<<MOVEGUNANIM)); return (TwoGunAnimData*)ptr;};
animptr::operator AircraftAnimData*(){AnimAssert(size & (1<<AIRCRAFTANIM)); return (AircraftAnimData*)ptr;};
animptr::operator PolyPitAnimData*(){AnimAssert(size & (1<<POLYPITANIM)); return (PolyPitAnimData*)ptr;};
animptr::operator LauncherAnimData*(){AnimAssert(size & (1<<LAUNCHERANIM)); return (LauncherAnimData*)ptr;};
animptr::operator WindsocAnimData*(){AnimAssert(size & (1<<WINDSOCANIM)); return (WindsocAnimData*)ptr;};
animptr::operator CloneAnimData*(){AnimAssert(size & (1<<CLONEANIM)); return (CloneAnimData*)ptr;};
animptr::operator FlareAnimData*(){AnimAssert(size & (1<<FLAREANIM)); return (FlareAnimData*)ptr;};
animptr::operator ParachuteAnimData*(){AnimAssert(size & (1<<PARACHUTEANIM)); return (ParachuteAnimData*)ptr;};
animptr::operator ThugAnimData*(){AnimAssert(size & (1<<THUGANIM)); return (ThugAnimData*)ptr;};
animptr::operator MissileAnimData*(){AnimAssert(size & (1<<MISSILEANIM)); return (MissileAnimData*)ptr;};
animptr::operator DebrisAnimData*(){AnimAssert(size & (1<<DEBRISANIM)); return (DebrisAnimData*)ptr;};
animptr::operator SmokeTrailAnimData*(){AnimAssert(size & (1<<SMOKETRAILANIM)); return (SmokeTrailAnimData*)ptr;};
animptr::operator Coords3DList*(){return (Coords3DList*)ptr;};
#undef	AnimAssert
#endif

inline UByteP	animptr::operator & ()
{
#ifndef	NANIMDEBUG
	if (size & 0x3ff)
		return (UByteP)ptr;
	
	return NULL;
#else
	return (UByteP)ptr;
#endif	
};

inline int		animptr::operator - (animptr& a)
{
#ifndef	NANIMDEBUG
	int	retval = (int)ptr - (int)a.ptr;

	assert((retval>=0)&&(retval<(size&0x3ff)));

	return (retval);
#else
	return (int)ptr - (int)a.ptr;
#endif
}

inline ULong	animptr::Offset(void*	a)
{
#ifndef	NANIMDEBUG
	SLong	offset = (UByteP)a - (UByteP)ptr;

	assert ((offset>=0)&&(offset<(size&0x3ff)));

	return ULong(offset);
#else
	return ULong((UByteP)a - (UByteP)ptr);
#endif
}
