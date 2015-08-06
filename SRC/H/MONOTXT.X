//------------------------------------------------------------------------------
//Filename       monotxt.h
//System         
//Author         Paul.   
//Date           Wed 16 Oct 1996
//Description    
//------------------------------------------------------------------------------
#ifndef	MONOTXT_Included
#define	MONOTXT_Included

/////////////////////////////////////////////////////////
//just comment your own equate in when you take a version
//make sure any mono debugs you put in are removed when
//your #define is removed
/////////////////////////////////////////////////////////

//#define PAULS_DEBUG
//#define DAVES_DEBUG
//#define JIMS_DEBUG
//#define ROBS_DEBUG
//#define CRAIGS_DEBUG
//#define RODS_DEBUG
//#define MACCAS_DEBUG

#ifdef NDEBUG
	#undef PAULS_DEBUG
	#undef DAVES_DEBUG
	#undef JIMS_DEBUG
	#undef ROBS_DEBUG
	#undef CRAIGS_DEBUG
	#undef RODS_DEBUG
	#undef MACCAS_DEBUG
#endif

#define NO_MONO_DATA "no PrintVar"

/////////////////////////////////////////////////
//put any #defines or #undefs in your own section
/////////////////////////////////////////////////

#ifdef PAULS_DEBUG
#define SHOW_FRAMERATE
#endif

#ifdef DAVES_DEBUG

#endif

#ifdef JIMS_DEBUG

#endif

#ifdef ROBS_DEBUG

#endif

#ifdef CRAIGS_DEBUG
	#define DISPLAY_MONO_DATA
	#undef NO_MONO_DATA
#endif

#ifdef RODS_DEBUG
	#define DISPLAY_MONO_DATA
	#undef NO_MONO_DATA
#endif

#ifdef MACCAS_DEBUG

#endif

#ifdef	NDEBUG
#define	DUMMYMONOROUTINES	{}
#else
#define	DUMMYMONOROUTINES
#endif
/////////////////////////////////////////////////
/////////////////////////////////////////////////

class	MonoText
{
	SLong	cx,cy;	//cursor pos

	public:

		CON		MonoText()	{ClsMono();};
		DES		~MonoText() {};

		void ClsMono();
		void SetCursor(SLong rx=0,SLong ry=0)	DUMMYMONOROUTINES;
		void StartTimer(SLong& );
		void StopTimer(SLong& );
		void StopTimer(SLong& ,UByte* );
		void Print(SLong val, UByte* text)
			 {
			 	UByte	ltstring[] = "1234567890 \n";

			 	UByte*	tstring = ltstring;

			 	TextOutMono(text);

			 	BinToASCII(val,tstring);

			 	TextOutMono(tstring);
			 }
		void Print(UByte* text)
			 {
			 	TextOutMono(text);
			 }
		void Print(UByte* text,SLong length);

		void PrintAt(SLong x,SLong y,SLong& val, UByte* text)
			 {
			 	SetCursor(x,y);
			 	Print(val,text);
			 }
		void PrintAt(SLong x,SLong y,UByte* text)
			 {
			 	SetCursor(x,y);
			 	Print(text);
			 }

		void PrintHexAt(SLong x,SLong y,SLong h,SLong digits)
		{
			SetCursor(x,y);
			UByte lstring[9];
			BinToHEX(h,lstring);
			for (int i=0;i<8-digits;i++)
				if (lstring[i]!='0')
				{
					Print(lstring);
					return;
				}
			Print(lstring+8-digits);
		}

	private:

		void	BinToASCII(SLong ,UByte* )	DUMMYMONOROUTINES;
		void	BinToHEX(SLong,UByte*)	DUMMYMONOROUTINES;

		void	TextOutMono(UByte* )	DUMMYMONOROUTINES;
};

extern class MonoText Mono_Text;
#undef	DUMMYMONOROUTINES
#endif
