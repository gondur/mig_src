//------------------------------------------------------------------------------
//Filename       matrix.h
//System         
//Author         Paul.   
//Date           Wed 23 Aug 1995
//Description    
//------------------------------------------------------------------------------
#ifndef	matrix_Included
#define	matrix_Included

	#include	"3ddefs.h"
#include	"vertex.h"

class	Window;
//CLIPFLAGS3D	operator | (CLIPFLAGS3D a,CLIPFLAGS3D b)
//	{return CLIPFLAGS3D(int(a)|int(b));}
//CLIPFLAGS3D	operator |= (CLIPFLAGS3D& a,CLIPFLAGS3D b)
//	{return a=a|b;}

class	matrix
		{
			Float	fpxscale,fpyscale,fpzscale;					//PD 19Nov98
			Float	aspectRatio;
//			Float	FoV;
			ANGLES	viewConeAngle;

			Window* mat_win;
		
			public:

			Float	fpMaximumZ;
//DeadCode PD 13Oct98 				static fpmatrix_ IDENTITY;

				Float	FoV;

				void SetWin(Window* w) {mat_win=w;}

				void	SetZScale(Window *);					//PD 25Jul96
				void	TransformAngles(ANGLES,ANGLES,ANGLES,ANGLES&,ANGLES&,ANGLES&);//PD 03Jul96

				void	ViewAnglesTransform(ANGLES,ANGLES,ANGLES,//PD 06Dec96
											ANGLES,ANGLES,
											ANGLES&,ANGLES&,ANGLES&);//PD 06Dec96

				void	TransformAnglesB(SLong,SLong,SLong,		//PD 05Jul96
										 ANGLES&,ANGLES&,ANGLES&,
										 ANGLES&,ANGLES&);

				void	generate(ANGLES, ANGLES, ANGLES, MATRIX_PTR);//PD 20Dec95
				void	generate2(ANGLES, ANGLES, ANGLES, MATRIX_PTR);//PD 26Feb96
				void	generater(ANGLES,MATRIX_PTR);			//PD 06Jun96
				void	generatep(ANGLES,MATRIX_PTR);			//PD 06Jun96
				void	generateh(ANGLES,MATRIX_PTR);			//PD 02Jul96

				void	inverse(ANGLES, ANGLES, ANGLES, MATRIX_PTR);

				//void 	getxdeltas(MATRIX_PTR , SLong& , SLong& , SLong& );

				//void 	getzdeltas(MATRIX_PTR , SLong& , SLong& , SLong& );

				UWord transform(MATRIX_PTR, SLong&, SLong&, SLong& );

				void	rotate(MATRIX_PTR,SLong&,SLong&,SLong&);//PD 05Jun96

				//void	transform_y(MATRIX_PTR, SLong, SWord, SLong&, SLong&, SLong& );

				UWord 	scaleto16bit(SLong&, SLong&, SLong& );

				void	multiply(MATRIX_PTR,MATRIX_PTR);

				void 	body2screen(DoPointStruc &);			//PD 25Jul96

//DEAD				void 	body2screen(landvertex &);				//PD 25Jul96

				void 	body2screen(VERTEX &);					//PD 25Jul96

				Bool 	crossproduct(DoPointStruc &, DoPointStruc &, DoPointStruc &);

				Bool 	accuratecrossproduct(	DoPointStruc &,
												DoPointStruc &,
												DoPointStruc &);//PD 27Nov96

				inline	SLong matrix::realZ(UWord scalefactor)	//PD 01Nov95
						{return(ZPlane>>scalefactor);};			//PD 01Nov95

				inline	ULong matrix::realZmsk(UWord scalefactor)
						{
							return((ULong )(((SLong )ZMask)>>scalefactor));
						};

				void	SetViewParams(Window*,ANGLES,SLong viewRange=0x7FFFFFFF);

				void	generate(ANGLES, ANGLES, ANGLES, FPMATRIX_PTR);
				void	generate2(ANGLES, ANGLES, ANGLES, FPMATRIX_PTR);
				void	inverse(ANGLES, ANGLES, ANGLES, FPMATRIX_PTR);
				void 	getxdeltas(FPMATRIX_PTR, IFShare& , IFShare& , IFShare& );
				void 	getzdeltas(FPMATRIX_PTR, IFShare& , IFShare& , IFShare& );
				UWord	transform(FPMATRIX_PTR, IFShare&, IFShare&, IFShare& );
				void	transform(FPMATRIX_PTR, DoPointStruc&);
				void	transform_y(FPMATRIX_PTR, SLong, IFShare&, IFShare&, IFShare& );
//DeadCode PD 12Oct98 				inline void	transformNC(FPMATRIX_PTR, DoPointStruc*);
				UWord	transformNC(FPMATRIX_PTR, IFShare&, IFShare&, IFShare& );
				void	multiply(FPMATRIX_PTR, FPMATRIX_PTR);
				UWord	fptrans(FPMATRIX_PTR,IFShare&,IFShare&,IFShare&);

				void inverseMobileMatrix(ANGLES,ANGLES,ANGLES,FPMATRIX&);

				void Generate(ANGLES,ANGLES,ANGLES,FPMATRIX*);
				void GenerateV(ANGLES,ANGLES,ANGLES,FPMATRIX*);
				void Generate2(ANGLES,ANGLES,ANGLES,Float,FPMATRIX*);
				void GenerateXY(Float&,Float&);					//RJS 02Dec98
				void GenerateRadar(ANGLES,ANGLES,ANGLES,FPMATRIX*);//RJS 14May99



//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
// Procedure	transformNC
//------------------------------------------------------------------------------
//Author	Paul.   
//Date		Mon 12 Oct 1998
//------------------------------------------------------------------------------
inline void matrix::transformNC(FPMATRIX_PTR T, DoPointStruc* dp)
{
	double f[3];
	double* mp=(double*)T;
	f[0]=double(dp->bodyx.i);
	f[1]=double(dp->bodyy.i);
	f[2]=double(dp->bodyz.i);
	dp->bodyx.f=f[0]*mp[0]+f[1]*mp[1]+f[2]*mp[2];
	dp->bodyy.f=f[0]*mp[3]+f[1]*mp[4]+f[2]*mp[5];
	dp->bodyz.f=f[0]*mp[6]+f[1]*mp[7]+f[2]*mp[8];
	dp->clipFlags=CF3D_NULL;
}

				void PushViewData();
				void PopViewData();
				void Set3DWin(SLong,SLong,SLong,SLong);


//#ifdef	MATRIX_CODE_REQ
				inline UWord GenClipFlags(fpCOORDS3D& fpos)
				{
					UWord retval;
					_clipFB(retval,fpos.Z.f,1.,fpMaximumZ);
					_clipLR(retval,fpos.X.f,fpos.Z.f);
					_clipTB(retval,fpos.Y.f,fpos.Z.f);
					return retval;
				}

				inline void SetClipFlags(DoPointStruc& dp){
					_clipFB(dp.clipFlags,dp.bodyz.f,1.,fpMaximumZ);
					_clipLR(dp.clipFlags,dp.bodyx.f,dp.bodyz.f);
					_clipTB(dp.clipFlags,dp.bodyy.f,dp.bodyz.f);
				}

				inline void SetClipFlags(VERTEX& dp){
					_clipFB(dp.clipFlags,dp.bz.f,1.,fpMaximumZ);
					_clipLR(dp.clipFlags,dp.bx.f,dp.bz.f);
					_clipTB(dp.clipFlags,dp.by.f,dp.bz.f);
				}
//#endif
			private:
				void generateh(ANGLES,FPMATRIX&);
				void generatep(ANGLES,FPMATRIX&);
				void generater(ANGLES,FPMATRIX&);


			protected:

		};

extern	matrix	_matrix;

#endif
