typedef	signed	char	SByte,*SByteP;
typedef	unsigned char	UByte,*UByteP;

typedef	signed	short	SWord,*SWordP;
typedef	unsigned short	UWord,*UWordP;

typedef	signed	long	SLong,*SLongP;
typedef	unsigned long	ULong,*ULongP;
typedef long double 	Float,*FloatP;							//PD 06Jan97
typedef void *HoriLineRtnPtr;									//PD 03Jan96
typedef int	GREY3DTYPE;
typedef int Colour;
typedef int SCANLINETYPE;
typedef SWord *MATRIX_PTR;
typedef	struct
{
	double	a,b,c,d;
}
Coeffs,*CoeffsP;

/*typedef int;
typedef int;
typedef int;
typedef int;
typedef int;
*/

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//DeadCode PD 5Nov97 struct	colourdata
//DeadCode PD 5Nov97 {
//DeadCode PD 5Nov97 	void*	imageptr;
//DeadCode PD 5Nov97 	ULong	imagexmask;
//DeadCode PD 5Nov97 	ULong	imageymask;
//DeadCode PD 5Nov97 	ULong	col;
//DeadCode PD 5Nov97 	void*	aliastblptr;
//DeadCode PD 5Nov97 	UByte	imageyshift;
//DeadCode PD 5Nov97 };
//DeadCode PD 5Nov97 
//DeadCode PD 5Nov97 static	struct colourdata colour_data;
//DeadCode PD 5Nov97 
//DeadCode PD 5Nov97 static	UByte	FadeData2[8198];
//DeadCode PD 5Nov97 
//DeadCode PD 5Nov97 static 	UByte	shadefromail[]=
//DeadCode PD 5Nov97 {
//DeadCode PD 5Nov97 	8,	0,	16,	4,	0,	8,
//DeadCode PD 5Nov97 	2,	0,	4,	1,	0,	2,
//DeadCode PD 5Nov97 	3,	2,	4,	6,	4,	8,
//DeadCode PD 5Nov97 	5,	4,	6,	7,	6,	8,
//DeadCode PD 5Nov97 	12,	8,	16,	10,	8,	12,
//DeadCode PD 5Nov97 	9,	8,	10,	11,	10,	12,
//DeadCode PD 5Nov97 	14,	12,	16,	13,	12,	14,
//DeadCode PD 5Nov97 	15,	14,	16
//DeadCode PD 5Nov97 };
//DeadCode PD 5Nov97 
//DeadCode PD 5Nov97 static	UByte	horizcol[]={0,0};
//DeadCode PD 5Nov97 
//DeadCode PD 5Nov97 static UWord	PixelWidth = 4;
//DeadCode PD 5Nov97 static UWord	Grey3DEnable = 0;
//DeadCode PD 5Nov97 static UWord	Trns3DEnabled = 0;
//DeadCode PD 5Nov97 
//DeadCode PD 5Nov97 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode PD 5Nov97 //Procedure		ASM_GetFadeColour
//DeadCode PD 5Nov97 //Author		Paul.   
//DeadCode PD 5Nov97 //Date			Wed 29 Oct 1997
//DeadCode PD 5Nov97 //
//DeadCode PD 5Nov97 //Description	
//DeadCode PD 5Nov97 //
//DeadCode PD 5Nov97 //Inputs		
//DeadCode PD 5Nov97 //
//DeadCode PD 5Nov97 //Returns	
//DeadCode PD 5Nov97 //
//DeadCode PD 5Nov97 //------------------------------------------------------------------------------
//DeadCode PD 5Nov97 SLong ASM_GetFadeColour(SLong a,SLong b)
//DeadCode PD 5Nov97 {
//DeadCode PD 5Nov97 	return a;
//DeadCode PD 5Nov97 }

//DeadCode PD 5Nov97 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode PD 5Nov97 //Procedure		ASM_SetPixelWidth
//DeadCode PD 5Nov97 //Author		Paul.   
//DeadCode PD 5Nov97 //Date			Wed 29 Oct 1997
//DeadCode PD 5Nov97 //
//DeadCode PD 5Nov97 //Description	
//DeadCode PD 5Nov97 //
//DeadCode PD 5Nov97 //Inputs		
//DeadCode PD 5Nov97 //
//DeadCode PD 5Nov97 //Returns	
//DeadCode PD 5Nov97 //
//DeadCode PD 5Nov97 //------------------------------------------------------------------------------
//DeadCode PD 5Nov97 SWord ASM_SetPixelWidth(SWord a)
//DeadCode PD 5Nov97 {
//DeadCode PD 5Nov97 	SWord	retval=PixelWidth;
//DeadCode PD 5Nov97 	PixelWidth = a;
//DeadCode PD 5Nov97 
//DeadCode PD 5Nov97 	return retval;
//DeadCode PD 5Nov97 }

//DeadCode PD 5Nov97 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode PD 5Nov97 //Procedure		ASM_SetTransparency
//DeadCode PD 5Nov97 //Author		Paul.   
//DeadCode PD 5Nov97 //Date			Wed 29 Oct 1997
//DeadCode PD 5Nov97 //
//DeadCode PD 5Nov97 //Description	
//DeadCode PD 5Nov97 //
//DeadCode PD 5Nov97 //Inputs		
//DeadCode PD 5Nov97 //
//DeadCode PD 5Nov97 //Returns	
//DeadCode PD 5Nov97 //
//DeadCode PD 5Nov97 //------------------------------------------------------------------------------
//DeadCode PD 5Nov97 void ASM_SetTransparency(SWord a)
//DeadCode PD 5Nov97 {
//DeadCode PD 5Nov97 	Trns3DEnabled=a;
//DeadCode PD 5Nov97 }

//DeadCode PD 5Nov97 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode PD 5Nov97 //Procedure		ASM_SetColour
//DeadCode PD 5Nov97 //Author		Paul.   
//DeadCode PD 5Nov97 //Date			Wed 29 Oct 1997
//DeadCode PD 5Nov97 //
//DeadCode PD 5Nov97 //Description	
//DeadCode PD 5Nov97 //
//DeadCode PD 5Nov97 //Inputs		
//DeadCode PD 5Nov97 //
//DeadCode PD 5Nov97 //Returns	
//DeadCode PD 5Nov97 //
//DeadCode PD 5Nov97 //------------------------------------------------------------------------------
//DeadCode PD 5Nov97 void ASM_SetColour(Colour a,SLong b,SLong c,UByteP d)
//DeadCode PD 5Nov97 {
//DeadCode PD 5Nov97 	colour_data.col = a;
//DeadCode PD 5Nov97 }

//DeadCode PD 5Nov97 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode PD 5Nov97 //Procedure		ASM_HoriLineAddr
//DeadCode PD 5Nov97 //Author		Paul.   
//DeadCode PD 5Nov97 //Date			Wed 29 Oct 1997
//DeadCode PD 5Nov97 //
//DeadCode PD 5Nov97 //Description	
//DeadCode PD 5Nov97 //
//DeadCode PD 5Nov97 //Inputs		
//DeadCode PD 5Nov97 //
//DeadCode PD 5Nov97 //Returns	
//DeadCode PD 5Nov97 //
//DeadCode PD 5Nov97 //------------------------------------------------------------------------------
//DeadCode PD 5Nov97 HoriLineRtnPtr ASM_HoriLineAddr(SCANLINETYPE a)
//DeadCode PD 5Nov97 {
//DeadCode PD 5Nov97 	HoriLineRtnPtr	retval;
//DeadCode PD 5Nov97 
//DeadCode PD 5Nov97 	_asm
//DeadCode PD 5Nov97 	{
//DeadCode PD 5Nov97 		jmp		short skipStub
//DeadCode PD 5Nov97 stubHori:
//DeadCode PD 5Nov97 
//DeadCode PD 5Nov97 
//DeadCode PD 5Nov97 
//DeadCode PD 5Nov97 
//DeadCode PD 5Nov97 //		int		3
//DeadCode PD 5Nov97 		ret
//DeadCode PD 5Nov97 skipStub:
//DeadCode PD 5Nov97 		push	eax
//DeadCode PD 5Nov97 		lea		eax,stubHori
//DeadCode PD 5Nov97 		mov		retval,eax
//DeadCode PD 5Nov97 		pop		eax
//DeadCode PD 5Nov97 	}
//DeadCode PD 5Nov97 	return retval;
//DeadCode PD 5Nov97 }

//DeadCode PD 5Nov97 //-----------------------------------------------------------------------------
//DeadCode PD 5Nov97 // Procedure    ASM_SetGrey3D
//DeadCode PD 5Nov97 // Author       
//DeadCode PD 5Nov97 // Date         30/10/97
//DeadCode PD 5Nov97 //
//DeadCode PD 5Nov97 // Description  
//DeadCode PD 5Nov97 //
//DeadCode PD 5Nov97 // Inputs       
//DeadCode PD 5Nov97 //
//DeadCode PD 5Nov97 // Returns      
//DeadCode PD 5Nov97 //
//DeadCode PD 5Nov97 //-----------------------------------------------------------------------------
//DeadCode PD 5Nov97 GREY3DTYPE ASM_SetGrey3D(GREY3DTYPE a)
//DeadCode PD 5Nov97 {
//DeadCode PD 5Nov97 //	_asm {int 3};
//DeadCode PD 5Nov97 	
//DeadCode PD 5Nov97 	return 0;
//DeadCode PD 5Nov97 }


//DeadCode PD 5Nov97 //-----------------------------------------------------------------------------
//DeadCode PD 5Nov97 // Procedure    ASM_SetFadeData
//DeadCode PD 5Nov97 // Author       
//DeadCode PD 5Nov97 // Date         30/10/97
//DeadCode PD 5Nov97 //
//DeadCode PD 5Nov97 // Description  
//DeadCode PD 5Nov97 //
//DeadCode PD 5Nov97 // Inputs       
//DeadCode PD 5Nov97 //
//DeadCode PD 5Nov97 // Returns      
//DeadCode PD 5Nov97 //
//DeadCode PD 5Nov97 //-----------------------------------------------------------------------------
//DeadCode PD 5Nov97 void ASM_SetFadeData(SLong a)
//DeadCode PD 5Nov97 {
//DeadCode PD 5Nov97 	_asm {int 3};
//DeadCode PD 5Nov97 
//DeadCode PD 5Nov97 //	return 0;
//DeadCode PD 5Nov97 }


//DeadCode PD 5Nov97 //-----------------------------------------------------------------------------
//DeadCode PD 5Nov97 // Procedure    ASM_SetFaded3D
//DeadCode PD 5Nov97 // Author       
//DeadCode PD 5Nov97 // Date         30/10/97
//DeadCode PD 5Nov97 //
//DeadCode PD 5Nov97 // Description  
//DeadCode PD 5Nov97 //
//DeadCode PD 5Nov97 // Inputs       
//DeadCode PD 5Nov97 //
//DeadCode PD 5Nov97 // Returns      
//DeadCode PD 5Nov97 //
//DeadCode PD 5Nov97 //-----------------------------------------------------------------------------
//DeadCode PD 5Nov97 GREY3DTYPE ASM_SetFaded3D(GREY3DTYPE a)
//DeadCode PD 5Nov97 {
//DeadCode PD 5Nov97 	_asm {int 3};
//DeadCode PD 5Nov97 	return 0;
//DeadCode PD 5Nov97 }


//-----------------------------------------------------------------------------
// Procedure    ASM_PlotPixel
// Author       
// Date         30/10/97
//
// Description  
//
// Inputs       
//
// Returns      
//
//-----------------------------------------------------------------------------
short	ASM_PlotPixel(long a, long b, long c, short d)
{
	_asm {int 3};
	return 0;
}

//DeadCode PD 5Nov97 //-----------------------------------------------------------------------------
//DeadCode PD 5Nov97 // Procedure    ASM_AliasTile
//DeadCode PD 5Nov97 // Author       
//DeadCode PD 5Nov97 // Date         30/10/97
//DeadCode PD 5Nov97 //
//DeadCode PD 5Nov97 // Description  
//DeadCode PD 5Nov97 //
//DeadCode PD 5Nov97 // Inputs       
//DeadCode PD 5Nov97 //
//DeadCode PD 5Nov97 // Returns      
//DeadCode PD 5Nov97 //
//DeadCode PD 5Nov97 //-----------------------------------------------------------------------------
//DeadCode PD 5Nov97 void	ASM_AliasTile(UByte* a,UByte* b,UByte* c,UByte* d)
//DeadCode PD 5Nov97 {
//DeadCode PD 5Nov97 	_asm {int 3};
//DeadCode PD 5Nov97 }

//DeadCode PD 5Nov97 //-----------------------------------------------------------------------------
//DeadCode PD 5Nov97 // Procedure    ASM_WidenRoutes
//DeadCode PD 5Nov97 // Author       
//DeadCode PD 5Nov97 // Date         30/10/97
//DeadCode PD 5Nov97 //
//DeadCode PD 5Nov97 // Description  
//DeadCode PD 5Nov97 //
//DeadCode PD 5Nov97 // Inputs       
//DeadCode PD 5Nov97 //
//DeadCode PD 5Nov97 // Returns      
//DeadCode PD 5Nov97 //
//DeadCode PD 5Nov97 //-----------------------------------------------------------------------------
//DeadCode PD 5Nov97 void ASM_WidenRoutes(UByte* a)
//DeadCode PD 5Nov97 {
//DeadCode PD 5Nov97 	_asm {int 3};
//DeadCode PD 5Nov97 }

//-----------------------------------------------------------------------------
// Procedure    ASMTransform
// Author       
// Date         30/10/97
//
// Description  
//
// Inputs       
//
// Returns      
//
//-----------------------------------------------------------------------------
//DeadCode PD 4Nov97 SLong ASMTransform(MATRIX_PTR lpMatrix,SLong* lpX,SLong* lpY,SLong* lpZ)
//DeadCode PD 4Nov97 {
//DeadCode PD 4Nov97 	_asm ( int 3 };
//DeadCode PD 4Nov97 }

//DeadCode PD 5Nov97 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode PD 5Nov97 //Procedure		ASM_SetAliasTblPtr
//DeadCode PD 5Nov97 //Author		Paul.   
//DeadCode PD 5Nov97 //Date			Wed 29 Oct 1997
//DeadCode PD 5Nov97 //
//DeadCode PD 5Nov97 //Description	
//DeadCode PD 5Nov97 //
//DeadCode PD 5Nov97 //Inputs		
//DeadCode PD 5Nov97 //
//DeadCode PD 5Nov97 //Returns	
//DeadCode PD 5Nov97 //
//DeadCode PD 5Nov97 //------------------------------------------------------------------------------
//DeadCode PD 5Nov97 UByteP ASM_SetAliasTblPtr(UByteP a)
//DeadCode PD 5Nov97 {
//DeadCode PD 5Nov97 	return FadeData2;
//DeadCode PD 5Nov97 }

//DeadCode PD 5Nov97 //-----------------------------------------------------------------------------
//DeadCode PD 5Nov97 // Procedure    ASM_NoAliasTile
//DeadCode PD 5Nov97 // Author       
//DeadCode PD 5Nov97 // Date         30/10/97
//DeadCode PD 5Nov97 //
//DeadCode PD 5Nov97 // Description  
//DeadCode PD 5Nov97 //
//DeadCode PD 5Nov97 // Inputs       
//DeadCode PD 5Nov97 //
//DeadCode PD 5Nov97 // Returns      
//DeadCode PD 5Nov97 //
//DeadCode PD 5Nov97 //-----------------------------------------------------------------------------
//DeadCode PD 5Nov97 void ASM_NoAliasTile(UByte* pSrc,UByte* pDst,UByte* pColorTbl,UByte* pAliasTbl)
//DeadCode PD 5Nov97 {
//DeadCode PD 5Nov97 	#define	RoadColoursMask	0xF0
//DeadCode PD 5Nov97 
//DeadCode PD 5Nov97 	_asm
//DeadCode PD 5Nov97 	{
//DeadCode PD 5Nov97 		push	eax
//DeadCode PD 5Nov97 		push	ebx
//DeadCode PD 5Nov97 		push	ecx
//DeadCode PD 5Nov97 		push	edx
//DeadCode PD 5Nov97 		push	esi
//DeadCode PD 5Nov97 
//DeadCode PD 5Nov97 		mov		eax,pSrc
//DeadCode PD 5Nov97 		mov		edx,pDst
//DeadCode PD 5Nov97 		mov		ebx,pColorTbl
//DeadCode PD 5Nov97 		mov		ecx,pAliasTbl
//DeadCode PD 5Nov97 
//DeadCode PD 5Nov97 		mov		esi,eax
//DeadCode PD 5Nov97 		xor		eax,eax
//DeadCode PD 5Nov97 		mov		ecx,257*257
//DeadCode PD 5Nov97 L1:
//DeadCode PD 5Nov97 		mov		al,[byte ptr esi]
//DeadCode PD 5Nov97 		test	al,RoadColoursMask
//DeadCode PD 5Nov97 		jnz		short NotRoadColour
//DeadCode PD 5Nov97 		mov		al,[byte ptr ebx+eax]
//DeadCode PD 5Nov97 		mov		[byte ptr esi],al
//DeadCode PD 5Nov97 NotRoadColour:
//DeadCode PD 5Nov97 		inc		esi
//DeadCode PD 5Nov97 		dec		ecx
//DeadCode PD 5Nov97 		jnz		short L1
//DeadCode PD 5Nov97 
//DeadCode PD 5Nov97 		pop		esi
//DeadCode PD 5Nov97 		pop		edx
//DeadCode PD 5Nov97 		pop		ecx
//DeadCode PD 5Nov97 		pop		ebx
//DeadCode PD 5Nov97 		pop		eax
//DeadCode PD 5Nov97 	}
//DeadCode PD 5Nov97 }


//-----------------------------------------------------------------------------
// Procedure    GroundHeight
// Author       
// Date         30/10/97
//
// Description  
//
// Inputs       
//
// Returns      
//
//-----------------------------------------------------------------------------
SLong GroundHeight(SLong x, SLong z, Coeffs coeff)
{
	_asm {int 3};
	return 0;
}


//-----------------------------------------------------------------------------
// Procedure    ASM_Blat2
// Author       
// Date         30/10/97
//
// Description  
//
// Inputs       
//
// Returns      
//
//-----------------------------------------------------------------------------
void ASM_Blat2(void *a,void *b, ULong c)
{
	_asm {int 3};
}












