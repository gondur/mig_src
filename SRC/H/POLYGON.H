//------------------------------------------------------------------------------
//Filename       polygon.h
//System         
//Author         Paul.   
//Date           Wed 18 Oct 1995
//Description    
//------------------------------------------------------------------------------
#ifndef	POLYGON_Included
#define	POLYGON_Included

#define	DEFAULT_POLYGON 0

	#include	"DOSDefs.h"
	#include	"myAngles.h"
	#include	"myError.h"
	#include	"display.h"
	#include	"3DDefs.h"
	#include	"Files.g"
	#include	"FileMan.h"
	#include	"Worldinc.h"
	#include	"ImageMap.h"
	#include	"vertex.h"

#define	MaxIVertz	32											//RJS 11Jul96

typedef float R3DVALUE;

#ifdef __MSVC__
inline void	ASM_Call(HoriLineRtnPtr num1,UWord * num2, VERTEX& num3, VERTEX& num4)
{
    __asm
    {
		push	esi
		mov 	esi,num1
		mov 	eax,num2
		mov 	edx,num3
		mov 	ebx,num4
		call 	esi
		pop		esi
    }
}
#endif

class	polygon;												//PD 30Jan96

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////PD 03May96
//
//										Aliased image cacheing
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////PD 03May96

class	polygon
		{
			enum	DIRECTION	{BACKWARDS = -1,FORWARDS = 1};

			enum	CLIPPERFLAG {CLIPF_NULL=0,CLIPF_TEXTURE=1,CLIPF_INTENSITY=2};

			struct	hlinelist
					{
						SLong		length;						//PD 11Dec95
						SLong		starty;
						VERTEX_PTR	*minilp,
									*minirp,
									*maxip;
						DIRECTION	led;
					};

			typedef	struct	hlinelist	HLINELIST,*HLINELIST_PTR;

			typedef	void(polygon::*scfp) (HLINELIST &);

			typedef	struct	ViewData
			{
				Float	originx,originy;
				Float	scalex,scaley;
				Float	D,F,h;
				Float	hoD,R;
				Float	FoR;												//PD 13Jun97
				Float	sD;													//PD 13Jun97
				Float	FogStart,
						FogEnd;
				Float	sqFogStart,
						sqFogEnd;
				Float	rangeFogConst;
				Float	clipTop,
						clipBot,
						clipLft,
						clipRgt;
				ANGLES	viewang;
			}
			ViewData;

			UByte fogRed,fogGreen,fogBlue;
			SLong fogStart,fogEnd;

			UWord	clipperflag;
			UWord	doclip;
	
			IFShare		lightx,lighty,lightz;

			POLYTYPE	polyType;

			HoriLineRtnPtr	horilinertn;						//PD 03Jan96

			scfp	scanconvert;
			scfp	scanconvertflat;							//PD 24Oct96

			VERTEX_PTR	vertex_index,
						vertex_end;

			VERTEX	**nvertptr,
					*buffered_nvertptr[MaxIVertz+4];
			VERTEX	**cvertptr,
					**zvertptr,
					*buffered_cvertptr[MaxIVertz+4];

			#define MaxSubdivisions 24

			struct PolyRecord
			{
				SLong vertexcount;
				VERTEX_PTR vptr[MaxIVertz];
			}
			polyrecord[MaxSubdivisions];
			SLong subdivisioncount;

			Window	*currscreen;
				
//dead			Float	LeftX,RightX,TopY,BotY;						//PD 04Jan96

			SLong	vertexcount;						//PD 12Dec95

			VERTEX	vertex_list[MaxIVertz*2*(MaxSubdivisions<<1)];

			Colour		polycolour;
			ColourRange	polyrange;

			ImageMapNumber 		polyimage;
			OpacityMapNumber 	polyoimage;

			UWord fontColour;

			SCANLINETYPE	polytype;

			Bool	ditherflag,
					lshadeon,
					textureloaded;								//PD 10Mar97

			SWord	SphereRadius;								//RJS 17Nov97
			SLong	SphIxStart,SphIyStart;						//RJS 17Nov97
			SWord	SphereDepth;								//RJS 25Nov97
			SWord	HaloWidth;									//RJS 16Jan98

			bool	fFoggingRequired;

			void SoftwareRedOut();
			void SoftwareBlackOut();
			void SoftwareWhiteOut();

			UWord fadeType;	// 0==red,1=black,2=white
			UWord fadeStage; //0-15 (0==no fade, 15=max fade

			bool fPerspective,fClouds;
			bool subdivisionneeded(VERTEX_PTR*,SLong);
			UWord subdivisionaxis(VERTEX_PTR*,SLong);
			void split(PolyRecord*,PolyRecord*,UWord);
			void perspectivepoly();

			public:
//TEMP				void SetPixelWidth(SWord pw) {currscreen->SetPixelWidth(pw);}
				void SetPixelWidth(SWord pw) {SWord x=1;currscreen->SetPixelWidth(x);}
				void DoSmokedGlassBox(SWord,SWord,SWord,SWord,Colour);
				bool SetClouds(bool flag) {bool oldval=fClouds;fClouds=flag;return oldval;}
				bool SetPerspectiveCorrection(bool flag) {bool oldval=fPerspective;fPerspective=flag;return oldval;}
				void DoLine3D(Colour,DoPointStruc&,DoPointStruc&);
				void DoLine2D(Colour,SWord,SWord,SWord,SWord);
				void DoPutC(ImageMapDesc*,DoPointStruc*);
				void SetSoftwareFades(UWord type,UWord level)	{fadeType=type; fadeStage=level;}
				void DoSoftwareFades();
				ViewData viewdata,saveviewdata;
				bool	fSoftware;
				bool	fFoggingActive;
				void	SetLightVector(IFShare&,IFShare&,IFShare&);//PD 14Jan97

				Bool	CalcIXYError();							//PD 08Sep96
				void	SetOpacityON();							//PD 17Apr96
				void	SetDither(Bool df){ditherflag=df;};		//PD 10Oct96
				void	ShiftIY(SLong );						//MGA 21Feb96

				void*	GetPaletteTable() 
				{
					if (currscreen) return currscreen->GetPaletteTable();
					return NULL;
				}

				UWord GetPaletteEntry(UWord c)
				{
					if (currscreen) return currscreen->GetPaletteEntry(c);
					return 0;
				}

				void SetPaletteEntry(UWord c,UWord v)
				{
					if (currscreen) currscreen->SetPaletteEntry(c,v);
				}
				void SetFontColour(Colour c) {fontColour=UWord(c);}

				SWord selectedPalette;

				void	SelectPalette(SWord palNum)
				{
					if (fSoftware && palNum!=selectedPalette && currscreen) 
					{
						currscreen->SelectPalette(palNum);
						selectedPalette=palNum;
					}
				}
				Bool	SetLShade(Bool newval)
				{
					Bool retval = lshadeon;
					lshadeon = newval;
					return (retval);
				}

				//Multiple versions of create polygon

				void	createpoly(ImageMapDescPtr,SCANLINETYPE);
				void	createpoly();							//PD 03May96
				void	createpoly(Colour );
				void	createpoly(ImageMapNumber );
				void	createfakefog(ImageMapNumber );
				void	createpoly(ImageMapDescPtr );			//PD 02Aug96
				void	createpoly(OpacityMapNumber );			//PD 18Jan96
				void	createpoly(ImageMapNumber ,Colour);
				void	createpoly(ImageMapNumber ,Colour, ColourRange);
				void	createpoly(ImageMapNumber ,ColourRange );//DAW 18Dec95
				void	createpoly(ImageMapDescPtr ,ColourRange );//PD 02Aug96
				void	createpoly(PolyType::PolyTypes);
				void	createpoly(ULong);							//PD 03May96
				void	createpoly(ROWANSURFACEDESC*,Float&);

				void	createpoly(UByte,UByte,UByte,UByte,UByte,UByte);

				//Multiple versions of create sphere

				void	createsphere(Colour );					//RJS 17Nov97
				void	createsphere(Colour,SWord );					//RJS 17Nov97
				void	createsphere(Colour,LUMINOSITYTYPE);
				void	createsphere(ImageMapNumber );			//RJS 17Nov97
				void	createhalo(Colour,SWord );				//RJS 16Jan98
				void	createhalo(ImageMapNumber,SWord );	//RJS 16Jan98
				void	createhaze(Colour );					//RJS 30Jan98

				//Multiple versions of create vertex

				void	gouraudvert(DoPointStruc&,UWord);

				void	createvert(DoPointStruc &);
				void	softwarevert(DoPointStruc &);
				void	createvert(DoPointStruc &, SWord &);
				void	createvert(DoPointStruc &, SWord &, SWord &);//PD 25Jan96
				void	createvert(DoPointStruc &, SWord &, SWord &, SWord&);//PD 25Jan96
				void	createvert(DoPointStruc &, SWord &, SWord &, SWord&,SWord&);

				void	createsphvert(DoPointStruc,SWord);		//RJS 17Nov97
				void	createsphvert(DoPointStruc,SWord,SLong, SLong,SLong, SLong);//RJS 17Nov97
				void	createsphvert(DoPointStruc,SWord,SWord);//RJS 16Jan98

				//More for landscape code

				void	createvert(VERTEX& );					//PD 30Jan96
				void	createvert(DoPointStruc&,UByte,UByte,UByte,UByte);

				//Only the one draw routine

				Bool	setpolyscrn(Window *,SLong,ANGLES);
				void	drawpoly();								//PD 07Feb96
				inline void hardpoly();
				void softpoly();
				void	drawsphere();							//RJS 17Nov97
				Bool	sign(SLong a){return((a<0)?FALSE:TRUE);};//PD 17Jan96

				void	Sparkle(SWord,SWord,SWord);				//RJS 16Dec97
				
				CON		polygon()								//PD 30Jan96
				{
					vertex_end = &vertex_list[MaxIVertz*2];

					int	j;
					for(j=MaxIVertz+1;j>=0;j--)
					{
						buffered_nvertptr[j] = NULL;
						buffered_cvertptr[j] = NULL;
					}
					nvertptr = &buffered_nvertptr[1];
					cvertptr =
						zvertptr = &buffered_cvertptr[1];

					fPerspective=false;
					fClouds=false;
					ditherflag = TRUE;							//PD 10Oct96
					lshadeon=FALSE;								//PD 14Jan97
					fSoftware=false;
					fogRed=fogGreen=fogBlue=0;
					fogStart=fogEnd=0;
					fFoggingActive=false;
					selectedPalette=-2;
				};


				DES		~polygon()								//PD 16Feb96
				{												//PD 19Feb96
				};

				SWord	Cos_ArcSin(SWord);						//RJS 13Feb98

				void	SetFog(UByte,UByte,UByte,SLong,SLong);
				void	SetFog(UByte,UByte,UByte);
				void	GetFog(UByte&,UByte&,UByte&,SLong&,SLong&);

			private:

				void	VertexSpaceError();

			protected:

				VERTEX	*AllocateVertex()
				{
					return(vertex_index++);
				};

				void PutBackVertex() {vertex_index--;}

				void	VertexOFlowTest()
				{
					#if	DEBUGGING

					if(vertex_index>vertex_end)
						VertexSpaceError();
					#endif
				};

//DEAD				bool PerspectiveCorrectionNeeded();

				//Plain polygon routines

				void	cpolyscancnvrt(HLINELIST &);
				void	cflatscancnvrt(HLINELIST &);

				//Gouraud polygon routines

				void	gpolyscancnvrt(HLINELIST &);
				void	gflatscancnvrt(HLINELIST &);

				//Image mapped polygon routines

				void	ipolyscancnvrt(HLINELIST &);
				void	wideipolyscancnvrt(HLINELIST &);
				void	iflatscancnvrt(HLINELIST &);

				//Shaded image mapped polygon routines

				void	sipolyscancnvrt(HLINELIST &);
				void	widesipolyscancnvrt(HLINELIST &);
				void	siflatscancnvrt(HLINELIST &);

				//Sphere scan convert routines

				void	cspherescancnvrt(HLINELIST &);			//RJS 18Nov97
				void	ispherescancnvrt(HLINELIST &);			//RJS 18Nov97
				void	csphfadescancnvrt(HLINELIST &);			//RJS 18Nov97
				void	csphlumscancnvrt(HLINELIST &);			//RJS 20Jan98

				//Halo sphere scan convert routines

				void	chalofadescancnvrt(HLINELIST &);		//RJS 16Jan98

				//Heat haze sphere scan convert routines

				void	chazescancnvrt(HLINELIST &);			//RJS 30Jan98


				void	setscale(void );

				void 	copyvertex(VERTEX &dest,VERTEX &src) {dest = src;};//PD 09Sep96

				void	CalcNewIXY(VERTEX*,VERTEX*,VERTEX*);	//PD 30Jan96
				void	CalcNewIXY_X(VERTEX*,VERTEX*,VERTEX*);	//PD 09Sep96
				void	CalcNewIXY_Y(VERTEX*,VERTEX*,VERTEX*);	//PD 09Sep96

				Float	FtoIPoly();								//PD 06Jan97
				void	KillBackClipFlags();
		public:

				bool GenericPolyClip();
				bool PolyCross();
				inline void BodyToScreen(VERTEX_PTR);
				inline void FullBodyToScreen(VERTEX_PTR);
				inline void GetSxy(VERTEX_PTR,R3DVALUE&,R3DVALUE&);
				inline void ClipToFront(VERTEX_PTR vin,VERTEX_PTR vout,VERTEX_PTR vclip);
				inline void ClipToBack(VERTEX_PTR vin,VERTEX_PTR vout,VERTEX_PTR vclip);
				inline void ClipToEast(VERTEX_PTR vin,VERTEX_PTR vout,VERTEX_PTR vclip);
				inline void ClipToWest(VERTEX_PTR vin,VERTEX_PTR vout,VERTEX_PTR vclip);
				inline void ClipToTop(VERTEX_PTR vin,VERTEX_PTR vout,VERTEX_PTR vclip);
				inline void ClipToBottom(VERTEX_PTR vin,VERTEX_PTR vout,VERTEX_PTR vclip);
				void PushViewData();
				void PopViewData();
				void Set3DWin(SLong,SLong,SLong,SLong);
		};

		extern	class polygon POLYGON;

#endif
