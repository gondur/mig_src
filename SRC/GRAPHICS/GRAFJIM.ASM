;;------------------------------------------------------------------------------
;;Module	grafpasm.asm
;;System
;;Author	Paul.
;;Date		Thu 14 Dec 1995
;;Description
;;------------------------------------------------------------------------------
	IDeal
	LOCALS	@@
p386
	INCLUDE "STRUCM.INC"

	SEGMENT _DATA PAGE PUBLIC USE32 'DATA'

	STRUC		vertex
	bx              DD      ?
	by              DD      ?
	bz              DD      ?
	sx              DD      ?
	sy              DD      ?
	ix              DD      ?
	iy              DD      ?
	intensity       DD      ?
	scalefactor     DW      ?
	ENDS

	STRUC		colourdata
	imageptr	DD	?
	imagexmask	DD	?
	imageymask	DD	?
	col		DD	?
	aliastblptr	DD	?				;;PD 25Mar96
	imageyshift	DB	?
	ENDS

;;-----------------------------------------------------------------------------
;;-----------------------------------------------------------------------------
;;		Horizontal line draw routine address tables
;;-----------------------------------------------------------------------------
;;-----------------------------------------------------------------------------

horiline_data1	DD	ASM_PlainHoriLine1_		;;PLAIN
		DD	ASM_GouraudHoriLine1_		;;GOURAUD
		DD	ASM_ImageHoriLine1_		;;IMAPPED
		DD	ASM_MImageHoriLine1_		;;IMAPPED_M
		DD	ASM_ImageHoriLine1_		;;IMAPPED_S
		DD	ASM_ImageHoriLine1_		;;IMAPPED_B
		DD	ASM_SImageHoriLine1_		;;IMAPPED_SH
		DD	ASM_OImageHoriLine1_		;;OMAPPED
		DD	ASM_OMImageHoriLine1_		;;OMAPPED_M

horiline_data2	DD	ASM_PlainHoriLine2_		;;PLAIN
		DD	ASM_GouraudHoriLine2_		;;GOURAUD
		DD	ASM_ImageHoriLine2_		;;IMAPPED
		DD	ASM_MImageHoriLine2_		;;IMAPPED_M
		DD	ASM_ImageHoriLine2_		;;IMAPPED_S
		DD	ASM_ImageHoriLine2_		;;IMAPPED_B
		DD	ASM_SImageHoriLine2_		;;IMAPPED_SH
		DD	ASM_OImageHoriLine1_		;;OMAPPED
		DD	ASM_OMImageHoriLine1_		;;OMAPPED_M

horiline_data4	DD	ASM_PlainHoriLine4_		;;PLAIN
		DD	ASM_GouraudHoriLine4_		;;GOURAUD
		DD	ASM_ImageHoriLine4_		;;IMAPPED
		DD	ASM_MImageHoriLine4_		;;IMAPPED_M
		DD	ASM_ImageHoriLine4_		;;IMAPPED_S
		DD	ASM_ImageHoriLine4_		;;IMAPPED_B
		DD	ASM_SImageHoriLine4_		;;IMAPPED_SH
		DD	ASM_OImageHoriLine1_		;;OMAPPED
		DD	ASM_OMImageHoriLine1_		;;OMAPPED_M

;;Colour indirected 3D versions of all the above

Ghoriline_data1	DD	ASM_GPlainHoriLine1_		;;PLAIN
		DD	ASM_GGouraudHoriLine1_		;;GOURAUD
		DD	ASM_GImageHoriLine1_		;;IMAPPED
		DD	ASM_GMImageHoriLine1_		;;IMAPPED_M//PD 03Apr96
		DD	ASM_GImageHoriLine1_		;;IMAPPED_S
		DD	ASM_GImageHoriLine1_		;;IMAPPED_B
		DD	ASM_GSImageHoriLine1_		;;IMAPPED_SH
		DD	ASM_OImageHoriLine1_		;;OMAPPED
		DD	ASM_OMImageHoriLine1_		;;OMAPPED_M

Ghoriline_data2	DD	ASM_GPlainHoriLine2_		;;PLAIN
		DD	ASM_GGouraudHoriLine2_		;;GOURAUD
		DD	ASM_GImageHoriLine2_		;;IMAPPED
		DD	ASM_GMImageHoriLine2_		;;IMAPPED_M//PD 03Apr96
		DD	ASM_GImageHoriLine2_		;;IMAPPED_S
		DD	ASM_GImageHoriLine2_		;;IMAPPED_B
		DD	ASM_GSImageHoriLine2_		;;IMAPPED_SH
		DD	ASM_OImageHoriLine1_		;;OMAPPED
		DD	ASM_OMImageHoriLine1_		;;OMAPPED_M

Ghoriline_data4	DD	ASM_GPlainHoriLine4_		;;PLAIN
		DD	ASM_GGouraudHoriLine4_		;;GOURAUD
		DD	ASM_GImageHoriLine4_		;;IMAPPED
		DD	ASM_GMImageHoriLine4_		;;IMAPPED_M//PD 03Apr96
		DD	ASM_GImageHoriLine4_		;;IMAPPED_S
		DD	ASM_GImageHoriLine4_		;;IMAPPED_B
		DD	ASM_GSImageHoriLine4_		;;IMAPPED_SH
		DD	ASM_OImageHoriLine1_		;;OMAPPED
		DD	ASM_OMImageHoriLine1_		;;OMAPPED_M

Thoriline_data1	DD	ASM_TPlainHoriLine1_		;;PLAIN	//PD 02Apr96
		DD	ASM_GouraudHoriLine1_		;;GOURAUD
		DD	ASM_ImageHoriLine1_		;;IMAPPED
		DD	ASM_TMImageHoriLine1_		;;IMAPPED_M
		DD	ASM_ImageHoriLine1_		;;IMAPPED_S
		DD	ASM_ImageHoriLine1_		;;IMAPPED_B
		DD	ASM_SImageHoriLine1_		;;IMAPPED_SH
		DD	ASM_OImageHoriLine1_		;;OMAPPED
		DD	ASM_OMImageHoriLine1_		;;OMAPPED_M

Thoriline_data2	DD	ASM_TPlainHoriLine2_		;;PLAIN	//PD 02Apr96
		DD	ASM_GouraudHoriLine2_		;;GOURAUD
		DD	ASM_ImageHoriLine2_		;;IMAPPED
		DD	ASM_TMImageHoriLine1_		;;IMAPPED_M
		DD	ASM_ImageHoriLine2_		;;IMAPPED_S
		DD	ASM_ImageHoriLine2_		;;IMAPPED_B
		DD	ASM_SImageHoriLine2_		;;IMAPPED_SH
		DD	ASM_OImageHoriLine1_		;;OMAPPED
		DD	ASM_OMImageHoriLine1_		;;OMAPPED_M

Thoriline_data4	DD	ASM_TPlainHoriLine4_		;;PLAIN	//PD 02Apr96
		DD	ASM_GouraudHoriLine4_		;;GOURAUD
		DD	ASM_ImageHoriLine4_		;;IMAPPED
		DD	ASM_TMImageHoriLine1_		;;IMAPPED_M
		DD	ASM_ImageHoriLine4_		;;IMAPPED_S
		DD	ASM_ImageHoriLine4_		;;IMAPPED_B
		DD	ASM_SImageHoriLine4_		;;IMAPPED_SH
		DD	ASM_OImageHoriLine1_		;;OMAPPED
		DD	ASM_OMImageHoriLine1_		;;OMAPPED_M

;;-----------------------------------------------------------------------------
;;-----------------------------------------------------------------------------
;;			Fade data tables
;;-----------------------------------------------------------------------------
;;-----------------------------------------------------------------------------

;;DeadCode PD 07Jun96 shade_data	DD	range0,range1,range2,range3
;;DeadCode PD 07Jun96 		DD	range4,range5,range6,range7
;;DeadCode PD 07Jun96 		DD	range8,range9,rangeA,rangeB
;;DeadCode PD 07Jun96 		DD	rangeC,rangeD,rangeE,rangeF

;;DeadCode PD 07Jun96 range0		DB	16 DUP (0)
;;DeadCode PD 07Jun96 range1		DB	16 DUP (0)
;;DeadCode PD 07Jun96 range2		DB	16 DUP (0)
;;DeadCode PD 07Jun96 range3		DB	16 DUP (0)
;;DeadCode PD 07Jun96 range4		DB	16 DUP (0)
;;DeadCode PD 07Jun96 range5		DB	16 DUP (0)
;;DeadCode PD 07Jun96 range6		DB	16 DUP (0)
;;DeadCode PD 07Jun96 range7		DB	16 DUP (0)
;;DeadCode PD 07Jun96 range8		DB	16 DUP (0)
;;DeadCode PD 07Jun96 range9		DB	16 DUP (0)
;;DeadCode PD 07Jun96 rangeA		DB	16 DUP (0)
;;DeadCode PD 07Jun96 rangeB		DB	16 DUP (0)
;;DeadCode PD 07Jun96 rangeC		DB	16 DUP (0)
;;DeadCode PD 07Jun96 rangeD		DB	16 DUP (0)
;;DeadCode PD 07Jun96 rangeE		DB	16 DUP (0)
;;DeadCode PD 07Jun96 rangeF		DB	16 DUP (0)

ShadeData2	db	4098 dup (0)

FadeData2	db	4098 dup (0)				;;PD 07Jun96
		db	0,0					;;PD 25Jun96

;;PD 21Jun96 - for blackouts /redouts/ whiteouts
FadeData3	db	4098 dup (0)				;;PD 07Jun96
		db	0,0					;;PD 25Jun96

LastFadeRequest	dd	-1					;;PD 24Jun96

;;		    (dst indx)  (a indx)  (b indx)
shadefromail	db	08,	  00,	    16
		db	04,	  00,	    08
		db	02,	  00,	    04
		db	01,	  00,	    02
		db	03,	  02,	    04
		db	06,	  04,	    08
		db	05,	  04,	    06
		db	07,	  06,	    08
		db	12,	  08,	    16
		db	10,	  08,	    12
		db	09,	  08,	    10
		db	11,	  10,	    12
		db	14,	  12,	    16
		db	13,	  12,	    14
		db	15,	  14,	    16
horizcol	db	0,0

;;-----------------------------------------------------------------------------
;;-----------------------------------------------------------------------------
;;			Colour indirected 3D data
;;-----------------------------------------------------------------------------
;;-----------------------------------------------------------------------------

Grey3DTable	DB	256 DUP (?)

;;DeadCode PD 02Apr96 Grey3DInitTable	DD	Cloud00,Cloud01,Cloud02,Cloud03
;;DeadCode PD 02Apr96 		DD	Cloud04,Cloud05,Cloud06,Cloud07
;;DeadCode PD 02Apr96 		DD	Cloud08,Cloud09,Cloud0A,Cloud0B
;;DeadCode PD 02Apr96 		DD	Cloud0C,Cloud0D,Cloud0E,Cloud0F
;;DeadCode PD 02Apr96 		DD	Cloud10,Cloud11,Cloud12,Cloud13
;;DeadCode PD 02Apr96 		DD	Cloud14,Cloud15,Cloud16,Cloud17
;;DeadCode PD 02Apr96 		DD	Cloud18,Cloud19,Cloud1A,Cloud1B
;;DeadCode PD 02Apr96 		DD	Cloud1C,Cloud1D,Cloud1E,Cloud1F
;;DeadCode PD 02Apr96
;;DeadCode PD 02Apr96 Cloud00		DB	1,2,3,4,5,6,7,8,248 DUP (?)
;;DeadCode PD 02Apr96 Cloud01		DB	256 DUP (?)
;;DeadCode PD 02Apr96 Cloud02		DB	256 DUP (?)
;;DeadCode PD 02Apr96 Cloud03		DB	256 DUP (?)
;;DeadCode PD 02Apr96 Cloud04		DB	256 DUP (?)
;;DeadCode PD 02Apr96 Cloud05		DB	256 DUP (?)
;;DeadCode PD 02Apr96 Cloud06		DB	256 DUP (?)
;;DeadCode PD 02Apr96 Cloud07		DB	256 DUP (?)
;;DeadCode PD 02Apr96 Cloud08		DB	256 DUP (?)
;;DeadCode PD 02Apr96 Cloud09		DB	256 DUP (?)
;;DeadCode PD 02Apr96 Cloud0A		DB	256 DUP (?)
;;DeadCode PD 02Apr96 Cloud0B		DB	256 DUP (?)
;;DeadCode PD 02Apr96 Cloud0C		DB	256 DUP (?)
;;DeadCode PD 02Apr96 Cloud0D		DB	256 DUP (?)
;;DeadCode PD 02Apr96 Cloud0E		DB	256 DUP (?)
;;DeadCode PD 02Apr96 Cloud0F		DB	256 DUP (?)
;;DeadCode PD 02Apr96
;;DeadCode PD 02Apr96 Cloud10		DB	1,2,3,4,5,6,7,8,248 DUP (?)
;;DeadCode PD 02Apr96 Cloud11		DB	256 DUP (?)
;;DeadCode PD 02Apr96 Cloud12		DB	256 DUP (?)
;;DeadCode PD 02Apr96 Cloud13		DB	256 DUP (?)
;;DeadCode PD 02Apr96 Cloud14		DB	256 DUP (?)
;;DeadCode PD 02Apr96 Cloud15		DB	256 DUP (?)
;;DeadCode PD 02Apr96 Cloud16		DB	256 DUP (?)
;;DeadCode PD 02Apr96 Cloud17		DB	256 DUP (?)
;;DeadCode PD 02Apr96 Cloud18		DB	256 DUP (?)
;;DeadCode PD 02Apr96 Cloud19		DB	256 DUP (?)
;;DeadCode PD 02Apr96 Cloud1A		DB	256 DUP (?)
;;DeadCode PD 02Apr96 Cloud1B		DB	256 DUP (?)
;;DeadCode PD 02Apr96 Cloud1C		DB	256 DUP (?)
;;DeadCode PD 02Apr96 Cloud1D		DB	256 DUP (?)
;;DeadCode PD 02Apr96 Cloud1E		DB	256 DUP (?)
;;DeadCode PD 02Apr96 Cloud1F		DB	256 DUP (?)

	ALIGN	4

colour_data	colourdata <>

PixelWidth	DW	4
Grey3DEnabled	DW	0	;;0=OFF, 1,2,3,... select indirection data
Trns3DEnabled	DW	0	;;0 OFF, !=0 ON			//PD 02Apr96


	ALIGN	16

IX	DD	?
DIX	DD	?
IY	DD	?
DIY	DD	?
INTENS	DD	?
DINTENS	DD	?
JITTER	DW	0,0						;;PD 15May96

	DW	9 dup (?)

	ALIGN	4						;;PD 30Apr96

LclAilBuf	db 64 dup(?)					;;PD 30Apr96

	ALIGN	2

	ENDS	_DATA

	GROUP	DGROUP	_DATA

	SEGMENT _TEXT PAGE PUBLIC USE32 'CODE'
;;;;TempCode PD 23Jan96 	CODE_SEG _TEXT

	assume	cs:_TEXT, ds:DGROUP
;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_GetFadeColour
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Fri 10 May 1996
;;Modified
;;
;;Description
;;
;;Inputs	eax = colour, edx = intensity
;;
;;Returns	eax = new colour
;;
;;Externals
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
	mov	ah,al
	xor	al,al
	shr	ax,4
	and	dl,0Fh
	or	al,dl
	movzx	eax,[byte ptr ds:ShadeData2+eax]

	;;If grey 3d is enabled then further modification
	;;of the colour is required

	cmp	[word ptr ds:Grey3DEnabled],0			;;PD 07Jun96
	jz	short @@Ret					;;PD 07Jun96
	mov	al,[byte ptr ds:Grey3DTable+eax]		;;PD 07Jun96
@@Ret:								;;PD 07Jun96
	ret
	endp

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
;; Procedure	MakeFadeRanges
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Wed 8 May 1996
;;Modified
;;
;;Description
;;
;;Inputs	al = horizon colour
;;
;;Returns	fade table generated
;;
;;Externals
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
proc	MakeFadeRanges
	push	eax
	push	ebx
	push	ecx
	push	esi
	push	edi
	push	ebp

	mov	[byte ptr ds:horizcol],al
	xor	cx,cx
	lea	edi,[ds:ShadeData2]
	mov	ebp,[(colourdata colour_data).aliastblptr]
	xor	ebx,ebx
@@Loopy:
	mov	[byte ptr ds:edi],cl
	mov	al,[byte ptr ds:horizcol]
	mov	[byte ptr ds:edi+16],al
	push	cx

	mov	cx,0Fh
	lea	esi,[ds:shadefromail]
@@Loop2:

	xor	eax,eax

	mov	bl,[byte ptr ds:esi+1]
	mov	al,[byte ptr ds:edi+ebx]	;;colour 1

	mov	bl,[byte ptr ds:esi+2]
	mov	ah,[byte ptr ds:edi+ebx]	;;colour 2

	mov	al,[byte ptr ds:ebp+eax]	;;ave(1 & 2)

	mov	bl,[byte ptr ds:esi+0]
	mov	[byte ptr ds:edi+ebx],al	;;store new val

	add	esi,3

	dec	cx
	jnz	short @@Loop2

	add	edi,10h

	pop	cx
	inc	cx
	cmp	cx,256
	jnz	@@Loopy

	pop	ebp
	pop	edi
	pop	esi
	pop	ecx
	pop	ebx
	pop	eax
	ret
	endp

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
;; Procedure	MakeCloudFadeRanges
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Wed 8 May 1996
;;Modified
;;
;;Description
;;
;;Inputs	al = cloud fade colour
;;
;;Returns	fade table generated
;;
;;Externals
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
proc	MakeCloudFadeRanges
	push	eax
	push	ebx
	push	ecx
	push	esi
	push	edi
	push	ebp

	mov	[byte ptr ds:horizcol],al
	xor	cx,cx
	lea	edi,[ds:FadeData2]
	mov	ebp,[(colourdata colour_data).aliastblptr]
	xor	ebx,ebx
@@Loopy:
	mov	[byte ptr ds:edi],cl
	mov	al,[byte ptr ds:horizcol]
	mov	[byte ptr ds:edi+16],al
	push	cx

	mov	cx,0Fh
	lea	esi,[ds:shadefromail]
@@Loop2:

	xor	eax,eax

	mov	bl,[byte ptr ds:esi+1]
	mov	al,[byte ptr ds:edi+ebx]	;;colour 1

	mov	bl,[byte ptr ds:esi+2]
	mov	ah,[byte ptr ds:edi+ebx]	;;colour 2

	mov	al,[byte ptr ds:ebp+eax]	;;ave(1 & 2)

	mov	bl,[byte ptr ds:esi+0]
	mov	[byte ptr ds:edi+ebx],al	;;store new val

	add	esi,3

	dec	cx
	jnz	short @@Loop2

	add	edi,10h

	pop	cx
	inc	cx
	cmp	cx,256
	jnz	@@Loopy

	pop	ebp
	pop	edi
	pop	esi
	pop	ecx
	pop	ebx
	pop	eax
	ret
	endp

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_SetFadeData
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Mon 24 Jun 1996
;;Modified
;;
;;Description
;;
;;Inputs	eax = required fade type
;;
;;Returns
;;
;;Externals
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
	cmp	eax,[ds:LastFadeRequest]
	jnz	short @@NewFade
	ret
@@NewFade:
	push	eax
	push	ebx
	push	ecx
	push	edx
	push	esi
	push	edi
	push	ebp
	mov	[ds:LastFadeRequest],eax
	or	eax,eax
	jz	short @@GotFadeType	;;Black out
	cmp	eax,1
	mov	eax,0Fh
	jnz	short @@GotFadeType	;;White out
	mov	eax,04h			;;Red out
@@GotFadeType:
	call	MakeBlackoutFadeRanges
	pop	ebp
	pop	edi
	pop	esi
	pop	edx
	pop	ecx
	pop	ebx
	pop	eax
	ret
	endp

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
;; Procedure	MakeBlackoutFadeRanges
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		21Jun96
;;Modified
;;
;;Description
;;
;;Inputs	al = cloud fade colour
;;
;;Returns	fade table generated
;;
;;Externals
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
proc	MakeBlackoutFadeRanges
	push	eax
	push	ebx
	push	ecx
	push	esi
	push	edi
	push	ebp

	mov	[byte ptr ds:horizcol],al
	xor	cx,cx
	lea	edi,[ds:FadeData3]
	mov	ebp,[(colourdata colour_data).aliastblptr]
	xor	ebx,ebx
@@Loopy:
	mov	[byte ptr ds:edi],cl
	mov	al,[byte ptr ds:horizcol]
	mov	[byte ptr ds:edi+16],al
	push	cx

	mov	cx,0Fh
	lea	esi,[ds:shadefromail]
@@Loop2:

	xor	eax,eax

	mov	bl,[byte ptr ds:esi+1]
	mov	al,[byte ptr ds:edi+ebx]	;;colour 1

	mov	bl,[byte ptr ds:esi+2]
	mov	ah,[byte ptr ds:edi+ebx]	;;colour 2

	mov	al,[byte ptr ds:ebp+eax]	;;ave(1 & 2)

	mov	bl,[byte ptr ds:esi+0]
	mov	[byte ptr ds:edi+ebx],al	;;store new val

	add	esi,3

	dec	cx
	jnz	short @@Loop2

	add	edi,10h

	pop	cx
	inc	cx
	cmp	cx,256
	jnz	@@Loopy

	pop	ebp
	pop	edi
	pop	esi
	pop	ecx
	pop	ebx
	pop	eax
	ret
	endp

;;-----------------------------------------------------------------------------
;;-----------------------------------------------------------------------------
;;			Colour indirected 3D data
;;-----------------------------------------------------------------------------
;;-----------------------------------------------------------------------------

;;DeadCode DAW 30Jun96 Grey3DTable	DB	256 DUP (?)

;;DeadCode PD 02Apr96 Grey3DInitTable	DD	Cloud00,Cloud01,Cloud02,Cloud03
;;DeadCode PD 02Apr96 		DD	Cloud04,Cloud05,Cloud06,Cloud07
;;DeadCode PD 02Apr96 		DD	Cloud08,Cloud09,Cloud0A,Cloud0B
;;DeadCode PD 02Apr96 		DD	Cloud0C,Cloud0D,Cloud0E,Cloud0F
;;DeadCode PD 02Apr96 		DD	Cloud10,Cloud11,Cloud12,Cloud13
;;DeadCode PD 02Apr96 		DD	Cloud14,Cloud15,Cloud16,Cloud17
;;DeadCode PD 02Apr96 		DD	Cloud18,Cloud19,Cloud1A,Cloud1B
;;DeadCode PD 02Apr96 		DD	Cloud1C,Cloud1D,Cloud1E,Cloud1F
;;DeadCode PD 02Apr96
;;DeadCode PD 02Apr96 Cloud00		DB	1,2,3,4,5,6,7,8,248 DUP (?)
;;DeadCode PD 02Apr96 Cloud01		DB	256 DUP (?)
;;DeadCode PD 02Apr96 Cloud02		DB	256 DUP (?)
;;DeadCode PD 02Apr96 Cloud03		DB	256 DUP (?)
;;DeadCode PD 02Apr96 Cloud04		DB	256 DUP (?)
;;DeadCode PD 02Apr96 Cloud05		DB	256 DUP (?)
;;DeadCode PD 02Apr96 Cloud06		DB	256 DUP (?)
;;DeadCode PD 02Apr96 Cloud07		DB	256 DUP (?)
;;DeadCode PD 02Apr96 Cloud08		DB	256 DUP (?)
;;DeadCode PD 02Apr96 Cloud09		DB	256 DUP (?)
;;DeadCode PD 02Apr96 Cloud0A		DB	256 DUP (?)
;;DeadCode PD 02Apr96 Cloud0B		DB	256 DUP (?)
;;DeadCode PD 02Apr96 Cloud0C		DB	256 DUP (?)
;;DeadCode PD 02Apr96 Cloud0D		DB	256 DUP (?)
;;DeadCode PD 02Apr96 Cloud0E		DB	256 DUP (?)
;;DeadCode PD 02Apr96 Cloud0F		DB	256 DUP (?)
;;DeadCode PD 02Apr96
;;DeadCode PD 02Apr96 Cloud10		DB	1,2,3,4,5,6,7,8,248 DUP (?)
;;DeadCode PD 02Apr96 Cloud11		DB	256 DUP (?)
;;DeadCode PD 02Apr96 Cloud12		DB	256 DUP (?)
;;DeadCode PD 02Apr96 Cloud13		DB	256 DUP (?)
;;DeadCode PD 02Apr96 Cloud14		DB	256 DUP (?)
;;DeadCode PD 02Apr96 Cloud15		DB	256 DUP (?)
;;DeadCode PD 02Apr96 Cloud16		DB	256 DUP (?)
;;DeadCode PD 02Apr96 Cloud17		DB	256 DUP (?)
;;DeadCode PD 02Apr96 Cloud18		DB	256 DUP (?)
;;DeadCode PD 02Apr96 Cloud19		DB	256 DUP (?)
;;DeadCode PD 02Apr96 Cloud1A		DB	256 DUP (?)
;;DeadCode PD 02Apr96 Cloud1B		DB	256 DUP (?)
;;DeadCode PD 02Apr96 Cloud1C		DB	256 DUP (?)
;;DeadCode PD 02Apr96 Cloud1D		DB	256 DUP (?)
;;DeadCode PD 02Apr96 Cloud1E		DB	256 DUP (?)
;;DeadCode PD 02Apr96 Cloud1F		DB	256 DUP (?)

;;DeadCode DAW 30Jun96 	ALIGN	4
;;DeadCode DAW 30Jun96
;;DeadCode DAW 30Jun96 colour_data	colourdata <>
;;DeadCode DAW 30Jun96
;;DeadCode DAW 30Jun96 PixelWidth	DW	4
;;DeadCode DAW 30Jun96 Grey3DEnabled	DW	0	;;0=OFF, 1,2,3,... select indirection data
;;DeadCode DAW 30Jun96 Trns3DEnabled	DW	0	;;0 OFF, !=0 ON			//PD 02Apr96
;;DeadCode DAW 30Jun96
	ALIGN	2

;;-----------------------------------------------------------------------------
;;-----------------------------------------------------------------------------
;;			General routines
;;-----------------------------------------------------------------------------
;;-----------------------------------------------------------------------------

;;DeadCode PD 02Apr96 ;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
;;DeadCode PD 02Apr96  Procedure	ASM_GetPalFxTableAddr
;;DeadCode PD 02Apr96 ;;------------------------------------------------------------------------------
;;DeadCode PD 02Apr96 ;;Author	Paul.
;;DeadCode PD 02Apr96 ;;Date		Fri 5 Jan 1996
;;DeadCode PD 02Apr96 ;;Modified
;;DeadCode PD 02Apr96 ;;
;;DeadCode PD 02Apr96 ;;Description
;;DeadCode PD 02Apr96 ;;
;;DeadCode PD 02Apr96 ;;Returns	eax = ptr to palette effects table
;;DeadCode PD 02Apr96 ;;
;;DeadCode PD 02Apr96 ;;Externals
;;DeadCode PD 02Apr96 ;;------------------------------------------------------------------------------
;;DeadCode PD 02Apr96 ;;------------------------------------------------------------------------------
;;DeadCode PD 02Apr96 	lea	eax,[Grey3DInitTable]
;;DeadCode PD 02Apr96 	ret
;;DeadCode PD 02Apr96 	endp

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_SetGrey3D
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Fri 5 Jan 1996
;;Modified
;;
;;Description	Sets up grey 3D data
;;
;;Inputs	ax = new grey 3D state (0..0x0F)
;;
;;Returns	ax = last grey 3D state
;;
;;Externals
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
	cmp	ax,[Grey3DEnabled]
	jnz	short @@HasChanged
	ret
@@HasChanged:
	push	[word ptr Grey3DEnabled]
	mov	[Grey3DEnabled],ax
	or	ax,ax
	jz	short @@Done

	push	eax
	push	ebx
	push	ecx
	push	esi
	push	edi

	lea	edi,[ds:Grey3DTable]
	cmp	eax,0Fh
	jl	short @@Okay
	mov	eax,0Fh
@@Okay:
	lea	ebx,[ds:FadeData2+eax]
	xor	ecx,ecx
@@CLoop:
	mov	al,[byte ptr ds:ebx]
	mov	[byte ptr ds:edi],al
	inc	edi
	lea	ebx,[ds:ebx+10h]
	inc	ecx
	cmp	ecx,100h
	jb	short @@CLoop

	pop	edi
	pop	esi
	pop	ecx
	pop	ebx
	pop	eax
@@Done:
	pop	ax
	ret
	endp

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_SetFaded3D
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Fri 5 Jan 1996
;;Modified
;;
;;Description	Sets up faded 3D data
;;
;;Inputs	ax = new faded 3D state (0..0x0F)
;;
;;Returns	ax = last faded 3D state
;;		(if new value !=0 then switch off cloud fades)
;;
;;Externals
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
	cmp	ax,[Grey3DEnabled]
	jnz	short @@HasChanged
	ret
@@HasChanged:
	push	[word ptr Grey3DEnabled]
	mov	[Grey3DEnabled],ax
	or	ax,ax
	jz	short @@Done
	push	eax
	push	ebx
	push	ecx
	push	esi
	push	edi
	lea	edi,[ds:Grey3DTable]
	cmp	eax,0Fh
	jl	short @@Okay
	mov	eax,0Fh
@@Okay:
	lea	ebx,[ds:FadeData3+eax]
	xor	ecx,ecx
@@CLoop:
	mov	al,[byte ptr ds:ebx]
	mov	[byte ptr ds:edi],al
	inc	edi
	lea	ebx,[ds:ebx+10h]
	inc	ecx
	cmp	ecx,100h
	jb	short @@CLoop
	pop	edi
	pop	esi
	pop	ecx
	pop	ebx
	pop	eax
@@Done:
	pop	ax
	ret
	endp

;;DeadCode PD 07Jun96 ;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
;;DeadCode PD 07Jun96  Procedure	ASM_MakeShadeTable
;;DeadCode PD 07Jun96 ;;------------------------------------------------------------------------------
;;DeadCode PD 07Jun96 ;;Author	Paul.
;;DeadCode PD 07Jun96 ;;Date		Wed 3 Jan 1996
;;DeadCode PD 07Jun96 ;;Modified
;;DeadCode PD 07Jun96 ;;
;;DeadCode PD 07Jun96 ;;Description
;;DeadCode PD 07Jun96 ;;
;;DeadCode PD 07Jun96 ;;Inputs
;;DeadCode PD 07Jun96 ;;
;;DeadCode PD 07Jun96 ;;Returns
;;DeadCode PD 07Jun96 ;;
;;DeadCode PD 07Jun96 ;;Externals
;;DeadCode PD 07Jun96 ;;------------------------------------------------------------------------------
;;DeadCode PD 07Jun96 ;;------------------------------------------------------------------------------
;;DeadCode PD 07Jun96 	cmp	[range1],0
;;DeadCode PD 07Jun96 	jz	short @@NotDone
;;DeadCode PD 07Jun96 	ret
;;DeadCode PD 07Jun96 @@NotDone:
;;DeadCode PD 07Jun96 	push	eax
;;DeadCode PD 07Jun96 	push	ebx
;;DeadCode PD 07Jun96 	push	ecx
;;DeadCode PD 07Jun96 	push	edx
;;DeadCode PD 07Jun96 	push	esi
;;DeadCode PD 07Jun96 	push	edi
;;DeadCode PD 07Jun96 	push	ebp
;;DeadCode PD 07Jun96 	lea	esi,[shade_data]
;;DeadCode PD 07Jun96 	xor	ecx,ecx
;;DeadCode PD 07Jun96 @@Next:
;;DeadCode PD 07Jun96 	mov	edi,[esi+4*ecx]
;;DeadCode PD 07Jun96 	mov	dh,00Fh
;;DeadCode PD 07Jun96 	sub	dh,cl
;;DeadCode PD 07Jun96 	xor	dl,dl
;;DeadCode PD 07Jun96 	shr	dx,5
;;DeadCode PD 07Jun96 	mov	ah,cl
;;DeadCode PD 07Jun96 	xor	al,al
;;DeadCode PD 07Jun96
;;DeadCode PD 07Jun96 	xor	bp,bp
;;DeadCode PD 07Jun96 ;;ax = current value
;;DeadCode PD 07Jun96 ;;dx = increment to next value
;;DeadCode PD 07Jun96 @@InnerLoop:
;;DeadCode PD 07Jun96 	mov	[byte ptr edi],ah				;;PD 23Feb96
;;DeadCode PD 07Jun96 	inc	edi						;;PD 23Feb96
;;DeadCode PD 07Jun96 	add	ax,dx
;;DeadCode PD 07Jun96
;;DeadCode PD 07Jun96 	inc	bp
;;DeadCode PD 07Jun96 	cmp	bp,020h
;;DeadCode PD 07Jun96 	jb	short @@InnerLoop
;;DeadCode PD 07Jun96
;;DeadCode PD 07Jun96 	inc	ecx
;;DeadCode PD 07Jun96 	cmp	ecx,010h
;;DeadCode PD 07Jun96 	jb	short @@Next
;;DeadCode PD 07Jun96 	pop	ebp
;;DeadCode PD 07Jun96 	pop	edi
;;DeadCode PD 07Jun96 	pop	esi
;;DeadCode PD 07Jun96 	pop	edx
;;DeadCode PD 07Jun96 	pop	ecx
;;DeadCode PD 07Jun96 	pop	ebx
;;DeadCode PD 07Jun96 	pop	eax
;;DeadCode PD 07Jun96 	ret
;;DeadCode PD 07Jun96 	endp

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_SetPixelWidth
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Thu 21 Dec 1995
;;Modified
;;
;;Description
;;
;;Inputs
;;
;;Returns
;;
;;Externals
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
	xchg	ax,[PixelWidth]
	ret
	endp

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_HoriLineAddr
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Wed 3 Jan 1996
;;Modified
;;
;;Description	Takes line type and pixel width and returns the
;;		call address for the correct horizontal line draw
;;		routine. Line types are as defined in the enumerated
;;		type SCANLINETYPE. The table 'horiline_data' at the
;;		top of this file needs to be kept up to date with
;;		the current set of SCANLINETYPE equates defined in
;;		3DDefs.h
;;
;;
;;Inputs	eax = scan line type & [PixelWidth] = 1, 2 or 4
;;
;;Returns	eax = address of correct horizontal line draw routine.
;;
;;Externals
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
	push	ebx
	push	esi
	push	edi						;;PD 02Apr96
	lea	ebx,[horiline_data1]
	lea	esi,[Ghoriline_data1]
	lea	edi,[Thoriline_data1]				;;PD 02Apr96
	cmp	[PixelWidth],1
	jz	short @@OK
	lea	ebx,[horiline_data2]
	lea	esi,[Ghoriline_data2]
	lea	edi,[Thoriline_data2]				;;PD 02Apr96
	cmp	[PixelWidth],2
	jz	short @@OK
	lea	ebx,[horiline_data4]
	lea	esi,[Ghoriline_data4]
	lea	edi,[Thoriline_data4]				;;PD 02Apr96
@@OK:
	cmp	[Trns3DEnabled],0
	jz	short @@Don2					;;PD 02Apr96
	mov	ebx,edi						;;PD 02Apr96
@@Don2:	cmp	[Grey3DEnabled],0
	jz	short @@Done
	mov	ebx,esi
@@Done:	mov	eax,[ebx+4*eax]					;;PD 02Apr96
	pop	edi						;;PD 02Apr96
	pop	esi
	pop	ebx
	ret
	endp


;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_SetAliasTblPtr
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Mon 25 Mar 1996
;;Modified
;;
;;Description
;;
;;Inputs	eax = ptr to alias table
;;
;;Returns
;;
;;Externals
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
	push	eax
	mov	[(colourdata colour_data).aliastblptr],eax
	mov	al,208		;;63				;;RJS 16Jun97
	call	MakeFadeRanges
	mov	al,0Fh						;;PD 07Jun96
	call	MakeCloudFadeRanges				;;PD 07Jun96
;;DeadCode PD 24Jun96 	xor	eax,eax						;;PD 21Jun96
;;DeadCode PD 24Jun96 	call	MakeBlackoutFadeRanges				;;PD 21Jun96
	pop	eax
	ret
	endp

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_SetColour
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Thu 14 Dec 1995
;;Modified
;;
;;Description
;;
;;Inputs	eax = colour
;;		edx = image.width
;;		ebx = image.height
;;		ecx = image.data
;;
;;Returns
;;
;;Externals
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------

;;DeadCode ARM 24Jun96 	ret

	push	eax
	push	esi
	push	edi
	push	ecx
	mov	esi,ecx
	lea	edi,[colour_data]
	mov	ah,al
	mov	cx,ax
	shl	eax,16
	mov	ax,cx
	mov	[(colourdata edi).col],eax
	mov	eax,00000001h
	mov	cl,dl
	shl	eax,cl
	dec	eax
	shl	eax,16
	mov	[(colourdata edi).imagexmask],eax
	mov	al,16
	sub	al,dl						;;PD 12Jan96
	mov	[(colourdata edi).imageyshift],al
	mov	eax,00000001h
	mov	cl,bl
	shl	eax,cl
	dec	eax
	shl	eax,16
	mov	[(colourdata edi).imageymask],eax
	mov	[(colourdata edi).imageptr],esi
	pop	ecx
	pop	edi
	pop	esi
	pop	eax
;;TempCode PD 07Jun96 	call	ASM_MakeShadeTable_
	ret
	endp

;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
;;	PLAIN POLYGON SCAN LINE ROUTINES @ x1, x2 and x4 pixel rez.
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------

	ALIGN	2

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_SmokedGlassLine
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Thu 21 Dec 1995
;;Modified
;;
;;Description
;;
;;Inputs	eax = screen ptr
;;		edx = left vertex
;;		ebx = right vertex
;;
;;Returns
;;
;;Externals
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
	push	eax
	push	ebx
	push	ecx
	push	edx
	push	esi						;;PD 10Jul96
	push	edi
	mov	ecx,[(vertex ebx).sx]	;;right vertex
	mov	esi,edx
	mov	edi,[(vertex esi).sx]	;;left vertex
	sub	ecx,edi
	inc	ecx
	jle	@@Out
	add	edi,eax			;;start scr. adr.

	xor	eax,eax
	mov	ah,[byte ptr (colourdata colour_data).col]
	mov	esi,[(colourdata colour_data).aliastblptr]
;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width
;;eax = colour.b, colour.b, colour.b, colour.b
@@Loop:								;;PD 23Feb96
	mov	al,[byte ptr ds:edi]
	mov	al,[byte ptr ds:esi+eax]
	mov	[byte ptr edi],al				;;PD 23Feb96
	inc	edi						;;PD 23Feb96
	dec	cx						;;PD 23Feb96
	jnz	short @@Loop					;;PD 23Feb96
@@Out:
	pop	edi
	pop	esi
	pop	edx						;;PD 10Jul96
	pop	ecx
	pop	ebx
	pop	eax
	ret
	endp

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_PlainHoriLine1
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Thu 21 Dec 1995
;;Modified
;;
;;Description
;;
;;Inputs
;;
;;Returns
;;
;;Externals
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
	push	ecx
	push	edi
	mov	ecx,[(vertex ebx).sx]	;;right vertex
	sar	ecx,16						;;PD 08Feb96
	mov	esi,edx
	mov	edi,[(vertex esi).sx]	;;left vertex
	sar	edi,16						;;PD 08Feb96
	sub	ecx,edi
	inc	ecx
	jle	@@Out
	add	edi,eax			;;start scr. adr.

	mov	eax,[(colourdata colour_data).col]

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width
;;eax = colour.b, colour.b, colour.b, colour.b
;;	rep	stosb						;;PD 23Feb96
@@Loop:								;;PD 23Feb96
	mov	[byte ptr edi],al				;;PD 23Feb96
	inc	edi						;;PD 23Feb96
	dec	cx						;;PD 23Feb96
	jnz	short @@Loop					;;PD 23Feb96
@@Out:
	pop	edi
	pop	ecx
	ret
	endp

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_PlainHoriLine2
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Thu 4 Jan 1996
;;Modified
;;
;;Description
;;
;;Inputs
;;
;;Returns
;;
;;Externals
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
	push	ecx
	push	edi
	mov	ecx,[(vertex ebx).sx]	;;right vertex
	sar	ecx,17						;;PD 08Feb96
	mov	esi,edx
	mov	edi,[(vertex esi).sx]	;;left vertex
	sar	edi,17						;;PD 08Feb96
	sub	ecx,edi
	inc	ecx
	jle	@@Out
	add	edi,edi
	add	edi,eax			;;start scr. adr.

	mov	eax,[(colourdata colour_data).col]

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width
;;eax = colour.b, colour.b, colour.b, colour.b
	rep	stosw
@@Out:
	pop	edi
	pop	ecx
	ret
	endp

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_PlainHoriLine4
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Thu 4 Jan 1996
;;Modified
;;
;;Description
;;
;;Inputs
;;
;;Returns
;;
;;Externals
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
	push	ecx
	push	edi
	mov	ecx,[(vertex ebx).sx]	;;right vertex
	sar	ecx,18						;;PD 08Feb96
	mov	esi,edx
	mov	edi,[(vertex esi).sx]	;;left vertex
	sar	edi,18						;;PD 08Feb96
	sub	ecx,edi
	inc	ecx
	jle	@@Out
	shl	edi,2
	add	edi,eax			;;start scr. adr.

	mov	eax,[(colourdata colour_data).col]

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width
;;eax = colour.b, colour.b, colour.b, colour.b
	rep	stosd
@@Out:
	pop	edi
	pop	ecx
	ret
	endp

;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
;;	SHADED POLYGON SCAN LINE ROUTINES @ x1, x2 and x4 pixel rez.
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------

	ALIGN	2

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_GouraudHoriLine1
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Thu 21 Dec 1995
;;Modified
;;
;;Description
;;
;;Inputs
;;
;;Returns
;;
;;Externals
;;------------------------------------------------------------------------------
;;DeadCode PD 10Jun96 	public	ASM_GouraudHoriLine2_,ASM_GouraudHoriLine4_
;;DeadCode PD 10Jun96 ASM_GouraudHoriLine2_:
;;DeadCode PD 10Jun96 ASM_GouraudHoriLine4_:
;;------------------------------------------------------------------------------
	push	eax
	push	ecx
	push	edx
	push	esi
	push	edi
	push	ebp
	mov	ecx,[(vertex ebx).sx]	;;right vertex
	sar	ecx,16						;;PD 08Feb96
	mov	esi,edx
	mov	edi,[(vertex esi).sx]	;;left vertex
	sar	edi,16						;;PD 08Feb96
	sub	ecx,edi
	inc	ecx
	jle	@@Out

	add	edi,eax			;;start scr. adr.

	mov	ebp,[(vertex esi).sy]				;;PD 10Jun96
	add	ebp,1024					;;PD 10Jun96
	add	ebp,[(colourdata colour_data).aliastblptr]	;;PD 10Jun96
	mov	bp,[word ptr ds:ebp]				;;PD 10Jun96
	mov	[word ptr ds:JITTER],bp				;;PD 10Jun96

	mov	eax,[(vertex esi).intensity]			;;PD 10Jun96
	mov	[INTENS],eax					;;PD 10Jun96
	sub	eax,[(vertex ebx).intensity]			;;PD 10Jun96
	neg	eax						;;PD 10Jun96

	mov	edx,eax						;;PD 10Jun96
	sar	edx,01fh					;;PD 10Jun96
	idiv	ecx						;;PD 10Jun96
	mov	[DINTENS],eax					;;PD 10Jun96

@@Loop:
	xor	eax,eax
	mov	ah,[byte ptr (colourdata colour_data).col]
	mov	edx,[dword ptr ds:INTENS]
	add	edx,[dword ptr ds:JITTER]
	shr	edx,16	;;20					//PD 10Jun96
	shr	ax,4
	or	ax,dx
	mov	al,[byte ptr ds:ShadeData2+eax]
	mov	[byte ptr ds:edi],al
	inc	edi
	mov	dx,[word ptr ds:JITTER]				;;PD 16May96
	add	dx,9136h					;;PD 16May96
	ror	dx,3						;;PD 16May96
	mov	[word ptr ds:JITTER],dx				;;PD 16May96

	mov	eax,[dword ptr ds:INTENS]
	add	eax,[dword ptr ds:DINTENS]
	mov	[dword ptr ds:INTENS],eax

	dec	ecx
	jnz	short @@Loop
@@Out:
	pop	ebp
	pop	edi
	pop	esi
	pop	edx
	pop	ecx
	pop	eax
	ret

	endp

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_GouraudHoriLine2
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Thu 21 Dec 1995
;;Modified
;;
;;Description
;;
;;Inputs
;;
;;Returns
;;
;;Externals
;;------------------------------------------------------------------------------
;;DeadCode PD 10Jun96 	public	ASM_GouraudHoriLine2_,ASM_GouraudHoriLine4_
;;DeadCode PD 10Jun96 ASM_GouraudHoriLine2_:
;;DeadCode PD 10Jun96 ASM_GouraudHoriLine4_:
;;------------------------------------------------------------------------------
	push	eax
	push	ecx
	push	edx
	push	esi
	push	edi
	push	ebp
	mov	ecx,[(vertex ebx).sx]	;;right vertex
	sar	ecx,17						;;PD 08Feb96
	mov	esi,edx
	mov	edi,[(vertex esi).sx]	;;left vertex
	sar	edi,17						;;PD 08Feb96
	sub	ecx,edi
	inc	ecx
	jle	@@Out

	add	edi,edi
	add	edi,eax			;;start scr. adr.

	mov	ebp,[(vertex esi).sy]				;;PD 10Jun96
	add	ebp,1024					;;PD 10Jun96
	add	ebp,[(colourdata colour_data).aliastblptr]	;;PD 10Jun96
	mov	bp,[word ptr ds:ebp]				;;PD 10Jun96
	mov	[word ptr ds:JITTER],bp				;;PD 10Jun96

	mov	eax,[(vertex esi).intensity]			;;PD 10Jun96
	mov	[INTENS],eax					;;PD 10Jun96
	sub	eax,[(vertex ebx).intensity]			;;PD 10Jun96
	neg	eax						;;PD 10Jun96

	mov	edx,eax						;;PD 10Jun96
	sar	edx,01fh					;;PD 10Jun96
	idiv	ecx						;;PD 10Jun96
	mov	[DINTENS],eax					;;PD 10Jun96

@@Loop:
	xor	eax,eax
	mov	ah,[byte ptr (colourdata colour_data).col]
	mov	edx,[dword ptr ds:INTENS]
	add	edx,[dword ptr ds:JITTER]
	shr	edx,16	;;20					//PD 10Jun96
	shr	ax,4
	or	ax,dx
	mov	al,[byte ptr ds:ShadeData2+eax]
	mov	ah,al
	mov	[word ptr ds:edi],ax
	inc	edi
	inc	edi
	mov	dx,[word ptr ds:JITTER]				;;PD 16May96
	add	dx,9136h					;;PD 16May96
	ror	dx,3						;;PD 16May96
	mov	[word ptr ds:JITTER],dx				;;PD 16May96

	mov	eax,[dword ptr ds:INTENS]
	add	eax,[dword ptr ds:DINTENS]
	mov	[dword ptr ds:INTENS],eax

	dec	ecx
	jnz	short @@Loop
@@Out:
	pop	ebp
	pop	edi
	pop	esi
	pop	edx
	pop	ecx
	pop	eax
	ret
	endp

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_GouraudHoriLine4
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Thu 21 Dec 1995
;;Modified
;;
;;Description
;;
;;Inputs
;;
;;Returns
;;
;;Externals
;;------------------------------------------------------------------------------
;;DeadCode PD 10Jun96 	public	ASM_GouraudHoriLine2_,ASM_GouraudHoriLine4_
;;DeadCode PD 10Jun96 ASM_GouraudHoriLine2_:
;;DeadCode PD 10Jun96 ASM_GouraudHoriLine4_:
;;------------------------------------------------------------------------------
	push	eax
	push	ecx
	push	edx
	push	esi
	push	edi
	push	ebp
	mov	ecx,[(vertex ebx).sx]	;;right vertex
	sar	ecx,18						;;PD 08Feb96
	mov	esi,edx
	mov	edi,[(vertex esi).sx]	;;left vertex
	sar	edi,18						;;PD 08Feb96
	sub	ecx,edi
	inc	ecx
	jle	@@Out

	add	edi,edi
	add	edi,edi
	add	edi,eax			;;start scr. adr.

	mov	ebp,[(vertex esi).sy]				;;PD 10Jun96
	add	ebp,1024					;;PD 10Jun96
	add	ebp,[(colourdata colour_data).aliastblptr]	;;PD 10Jun96
	mov	bp,[word ptr ds:ebp]				;;PD 10Jun96
	mov	[word ptr ds:JITTER],bp				;;PD 10Jun96

	mov	eax,[(vertex esi).intensity]			;;PD 10Jun96
	mov	[INTENS],eax					;;PD 10Jun96
	sub	eax,[(vertex ebx).intensity]			;;PD 10Jun96
	neg	eax						;;PD 10Jun96

	mov	edx,eax						;;PD 10Jun96
	sar	edx,01fh					;;PD 10Jun96
	idiv	ecx						;;PD 10Jun96
	mov	[DINTENS],eax					;;PD 10Jun96

@@Loop:
	xor	eax,eax
	mov	ah,[byte ptr (colourdata colour_data).col]
	mov	edx,[dword ptr ds:INTENS]
	add	edx,[dword ptr ds:JITTER]
	shr	edx,16	;;20					//PD 10Jun96
	cmp	edx,0Fh
	jbe	short @@OKay
	mov	edx,0Fh
@@OKay:
	shr	ax,4
	or	ax,dx
	mov	al,[byte ptr ds:ShadeData2+eax]
	mov	ah,al
	mov	[word ptr ds:edi],ax
	mov	[word ptr ds:edi+2],ax
	add	edi,4
	mov	dx,[word ptr ds:JITTER]				;;PD 16May96
	add	dx,9136h					;;PD 16May96
	ror	dx,3						;;PD 16May96
	mov	[word ptr ds:JITTER],dx				;;PD 16May96

	mov	eax,[dword ptr ds:INTENS]
	add	eax,[dword ptr ds:DINTENS]
	mov	[dword ptr ds:INTENS],eax
	dec	ecx
	jnz	short @@Loop
@@Out:
	pop	ebp
	pop	edi
	pop	esi
	pop	edx
	pop	ecx
	pop	eax
	ret
	endp

;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
;;	NORMAL IMAGE MAPPING SCAN LINE ROUTINES @ x1, x2 and x4 pixel rez.
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_ImageHoriLine1
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Thu 14 Dec 1995
;;Modified
;;
;;Description	Want imageymask to go to top bits
;;		Want imagexmask to go just below it
;;		Leaves shift behind
;;
;;
;;
;;
;;
;;Inputs	eax = screen ptr
;;		edx = left vertex
;;		ebx = right vertex
;;
;;Returns
;;
;;Externals
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
	push	ecx
	push	edi
	push	ebp
;;//want fiddlefactor for shift...
  ;;	mov	cx,16
    ;;	sub	cl,[(colourdata ds:colour_data).imageyshift]


	mov	ecx,[(vertex ebx).sx]	;;right vertex
	sar	ecx,16						;;PD 08Feb96
	mov	esi,edx
	mov	edi,[(vertex esi).sx]	;;left vertex
	sar	edi,16						;;PD 08Feb96
	sub	ecx,edi
	inc	ecx
	jle	@@Out
	add	edi,eax			;;start scr. adr.

	mov	eax,[(vertex esi).ix]	;;left vertex
	mov	[IX],eax
	sub	eax,[(vertex ebx).ix]	;;right vertex
	neg	eax
	mov	edx,eax						;PD 26Jan96
	sar	edx,31						;PD 26Jan96
	idiv	ecx
	mov	[dword ptr ds:DIX],eax		;;image x delta



	mov	eax,[(vertex esi).iy]	;;left vertex
	mov	[IY],eax
	mov	ebp,eax						;PD 26Jan96
	sub	eax,[(vertex ebx).iy]	;;right vertex
	jz	@@Horizontal
	cmp	eax,0ffff0000h
	ja	@@Horizontal
	cmp	eax,000010000h
	jb	@@Horizontal
	neg	eax
	mov	edx,eax						;PD 26Jan96
	sar	edx,31						;PD 26Jan96

 	idiv	ecx
	mov	[dword ptr ds:DIY],eax		;;image y delta

	mov	esi,[(colourdata colour_data).imageptr]
	mov	edx,[IX]


;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width
	or	ecx,[(colourdata colour_data).imagexmask]

;;we got deltaY
;;DeadCode PD 10Jun96 	ALIGN	16


;;ecx=X mask
;;edx=X
;;ebp=Y
;;esi=imagemap
;;edi=display
  	dec 	edi
;;
@@Loop:
	push	ecx
	mov	ebx,edx
	mov	eax,ebp
	and	ebx,ecx
	and	eax,[(colourdata ds:colour_data).imageymask]
	inc	edi
	shr	ebx,16
	add	edx,[dword ptr ds:DIX]
	mov	cl,[(colourdata ds:colour_data).imageyshift]
	shr	eax,cl
	add	ebp,[dword ptr ds:DIY]
	add	ebx,eax
	pop	ecx
	mov	al,[byte ptr ds:esi+ebx]
	mov	[byte ptr ds:edi],al
	dec	cx
	jnz	short @@Loop
@@Out:
	pop	ebp
	pop	edi
	pop	ecx
	ret
 ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
@@Horizontal:
	mov	esi,[(colourdata colour_data).imageptr]
	mov	edx,[IX]
	or	ecx,[(colourdata colour_data).imagexmask]
	push	cx
	and	ebp,[(colourdata ds:colour_data).imageymask]
	mov	cl,[(colourdata ds:colour_data).imageyshift]
	shr	ebp,cl
	pop	cx
	dec	edi
@@Loop2:
	mov	ebx,edx
;//DeadCode JIM 09Aug96 	push	ecx
;//DeadCode JIM 09Aug96 	mov	eax,ebp
	and	ebx,ecx
;//DeadCode JIM 09Aug96 	and	eax,[(colourdata ds:colour_data).imageymask]
	inc	edi
	shr	ebx,16
	add	edx,[dword ptr ds:DIX]
;//DeadCode JIM 09Aug96 	mov	cl,[(colourdata ds:colour_data).imageyshift]
;//DeadCode JIM 09Aug96 	shr	eax,cl
;//DeadCode JIM 09Aug96 	add	ebp,[dword ptr ds:DIY]
	add	ebx,ebp
;//DeadCode JIM 09Aug96 	pop	ecx
	mov	bl,[byte ptr ds:esi+ebx]
	mov	[byte ptr ds:edi],bl
	dec	cx
	jnz	short @@Loop2
;//DeadCode JIM 09Aug96 @@Out:
	pop	ebp
	pop	edi
	pop	ecx
	ret




	endp

;;//DeadCode JIM 09Aug96 ;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
;;//DeadCode JIM 09Aug96  Procedure	ASM_ImageHoriLine1
;;//DeadCode JIM 09Aug96 ;;------------------------------------------------------------------------------
;;//DeadCode JIM 09Aug96 ;;Author	Paul.
;;//DeadCode JIM 09Aug96 ;;Date		Thu 14 Dec 1995
;;//DeadCode JIM 09Aug96 ;;Modified
;;//DeadCode JIM 09Aug96 ;;
;;//DeadCode JIM 09Aug96 ;;Description
;;//DeadCode JIM 09Aug96 ;;
;;//DeadCode JIM 09Aug96 ;;Inputs	eax = screen ptr
;;//DeadCode JIM 09Aug96 ;;		edx = left vertex
;;//DeadCode JIM 09Aug96 ;;		ebx = right vertex
;;//DeadCode JIM 09Aug96 ;;
;;//DeadCode JIM 09Aug96 ;;Returns
;;//DeadCode JIM 09Aug96 ;;
;;//DeadCode JIM 09Aug96 ;;Externals
;;//DeadCode JIM 09Aug96 ;;------------------------------------------------------------------------------
;;//DeadCode JIM 09Aug96 ;;------------------------------------------------------------------------------
;;//DeadCode JIM 09Aug96 	push	ecx
;;//DeadCode JIM 09Aug96 	push	edi
;;//DeadCode JIM 09Aug96 	push	ebp
;;//DeadCode JIM 09Aug96 	mov	ecx,[(vertex ebx).sx]	;;right vertex
;;//DeadCode JIM 09Aug96 	sar	ecx,16						;;PD 08Feb96
;;//DeadCode JIM 09Aug96 	mov	esi,edx
;;//DeadCode JIM 09Aug96 	mov	edi,[(vertex esi).sx]	;;left vertex
;;//DeadCode JIM 09Aug96 	sar	edi,16						;;PD 08Feb96
;;//DeadCode JIM 09Aug96 	sub	ecx,edi
;;//DeadCode JIM 09Aug96 	inc	ecx
;;//DeadCode JIM 09Aug96 	jle	@@Out
;;//DeadCode JIM 09Aug96 	add	edi,eax			;;start scr. adr.
;;//DeadCode JIM 09Aug96
;;//DeadCode JIM 09Aug96 	mov	eax,[(vertex esi).ix]	;;left vertex
;;//DeadCode JIM 09Aug96 	mov	[IX],eax
;;//DeadCode JIM 09Aug96 	sub	eax,[(vertex ebx).ix]	;;right vertex
;;//DeadCode JIM 09Aug96 	neg	eax
;;//DeadCode JIM 09Aug96 	mov	edx,eax						;PD 26Jan96
;;//DeadCode JIM 09Aug96 	sar	edx,31						;PD 26Jan96
;;//DeadCode JIM 09Aug96 	idiv	ecx
;;//DeadCode JIM 09Aug96 	mov	[dword ptr ds:DIX],eax		;;image x delta
;;//DeadCode JIM 09Aug96
;;//DeadCode JIM 09Aug96 	mov	eax,[(vertex esi).iy]	;;left vertex
;;//DeadCode JIM 09Aug96 	mov	[IY],eax
;;//DeadCode JIM 09Aug96 	mov	ebp,eax						;PD 26Jan96
;;//DeadCode JIM 09Aug96 	sub	eax,[(vertex ebx).iy]	;;right vertex
;;//DeadCode JIM 09Aug96 	neg	eax
;;//DeadCode JIM 09Aug96 	mov	edx,eax						;PD 26Jan96
;;//DeadCode JIM 09Aug96 	sar	edx,31						;PD 26Jan96
;;//DeadCode JIM 09Aug96 	idiv	ecx
;;//DeadCode JIM 09Aug96 	mov	[dword ptr ds:DIY],eax		;;image y delta
;;//DeadCode JIM 09Aug96
;;//DeadCode JIM 09Aug96 	mov	esi,[(colourdata colour_data).imageptr]
;;//DeadCode JIM 09Aug96 	mov	edx,[IX]
;;//DeadCode JIM 09Aug96
;;//DeadCode JIM 09Aug96
;;//DeadCode JIM 09Aug96 ;;edi = screen ptr
;;//DeadCode JIM 09Aug96 ;;esi = image map data ptr
;;//DeadCode JIM 09Aug96 ;;ecx = line width
;;//DeadCode JIM 09Aug96 	or	ecx,[(colourdata colour_data).imagexmask]
;;//DeadCode JIM 09Aug96
;;//DeadCode JIM 09Aug96 ;;we got deltaY
;;//DeadCode JIM 09Aug96 ;;DeadCode PD 10Jun96 	ALIGN	16
;;//DeadCode JIM 09Aug96
;;//DeadCode JIM 09Aug96
;;//DeadCode JIM 09Aug96 ;;ecx=X mask
;;//DeadCode JIM 09Aug96 ;;edx=X
;;//DeadCode JIM 09Aug96 ;;ebp=Y
;;//DeadCode JIM 09Aug96 ;;esi=imagemap
;;//DeadCode JIM 09Aug96 ;;edi=display
;;//DeadCode JIM 09Aug96
;;//DeadCode JIM 09Aug96 ;;
;;//DeadCode JIM 09Aug96
;;//DeadCode JIM 09Aug96 @@Loop:
;;//DeadCode JIM 09Aug96 	push	cx
;;//DeadCode JIM 09Aug96 	mov	ebx,edx
;;//DeadCode JIM 09Aug96 	and	ebx,ecx
;;//DeadCode JIM 09Aug96 	shr	ebx,16
;;//DeadCode JIM 09Aug96 	mov	eax,ebp
;;//DeadCode JIM 09Aug96 	and	eax,[(colourdata ds:colour_data).imageymask]
;;//DeadCode JIM 09Aug96 	mov	cl,[(colourdata ds:colour_data).imageyshift]
;;//DeadCode JIM 09Aug96 	shr	eax,cl
;;//DeadCode JIM 09Aug96 	add	ebx,eax
;;//DeadCode JIM 09Aug96 	mov	al,[byte ptr ds:esi+ebx]
;;//DeadCode JIM 09Aug96 	mov	[byte ptr ds:edi],al
;;//DeadCode JIM 09Aug96 	pop	cx
;;//DeadCode JIM 09Aug96 	add	edx,[dword ptr ds:DIX]
;;//DeadCode JIM 09Aug96 	add	ebp,[dword ptr ds:DIY]
;;//DeadCode JIM 09Aug96 	inc	edi
;;//DeadCode JIM 09Aug96 	dec	cx
;;//DeadCode JIM 09Aug96 	jnz	short @@Loop
;;//DeadCode JIM 09Aug96 @@Out:
;;//DeadCode JIM 09Aug96 	pop	ebp
;;//DeadCode JIM 09Aug96 	pop	edi
;;//DeadCode JIM 09Aug96 	pop	ecx
;;//DeadCode JIM 09Aug96 	ret
;;//DeadCode JIM 09Aug96 	endp
;;//DeadCode JIM 09Aug96
;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_ImageHoriLine2
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Thu 14 Dec 1995
;;Modified
;;
;;Description	Same as ASM_ImageHoriLine1 but double pixel fill
;;
;;Inputs	eax = screen ptr
;;		edx = left vertex
;;		ebx = right vertex
;;
;;Returns
;;
;;Externals
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
	push	ecx
	push	edi
	push	ebp
	mov	ecx,[(vertex ebx).sx]	;;right vertex
	sar	ecx,17						;;PD 08Feb96
	mov	esi,edx
	mov	edi,[(vertex esi).sx]	;;left vertex
	sar	edi,17						;;PD 08Feb96
	sub	ecx,edi
	inc	ecx
	jle	@@Out
	add	edi,edi
	add	edi,eax			;;start scr. adr.

	mov	eax,[(vertex esi).ix]	;;left vertex
	mov	[IX],eax
	sub	eax,[(vertex ebx).ix]	;;right vertex
	neg	eax
	mov	edx,eax
	sar	edx,01fh
	idiv	ecx
	mov	[DIX],eax		;;image x delta

	mov	eax,[(vertex esi).iy]	;;left vertex
	mov	[IY],eax
	sub	eax,[(vertex ebx).iy]	;;right vertex
	neg	eax
	mov	edx,eax
	sar	edx,01fh
	idiv	ecx
	mov	[DIY],eax		;;image y delta

	mov	esi,[(colourdata colour_data).imageptr]
	mov	edx,[IX]
	mov	ebp,[IY]

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width
	or	ecx,[(colourdata colour_data).imagexmask]

;;DeadCode PD 10Jun96 	ALIGN	16
@@Loop:
	push	cx
	mov	ebx,edx
	and	ebx,ecx
	shr	ebx,16
	mov	eax,ebp
	and	eax,[(colourdata colour_data).imageymask]
	mov	cl,[(colourdata colour_data).imageyshift]
	shr	eax,cl
	add	ebx,eax
	mov	al,[esi+ebx]
	mov	ah,al
	stosw
	mov	eax,[DIX]
	add	edx,eax
	mov	eax,[DIY]
	add	ebp,eax
	pop	cx
	dec	cx
	jnz	short @@Loop
@@Out:
	pop	ebp
	pop	edi
	pop	ecx
	ret
	endp

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_ImageHoriLine4
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Thu 14 Dec 1995
;;Modified
;;
;;Description	Same as ASM_ImageHoriLine1 but quad pixel fill
;;
;;Inputs	eax = screen ptr
;;		edx = left vertex
;;		ebx = right vertex
;;
;;Returns
;;
;;Externals
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
	push	ecx
	push	edi
	push	ebp
	mov	ecx,[(vertex ebx).sx]	;;right vertex
	sar	ecx,18						;;PD 08Feb96
	mov	esi,edx
	mov	edi,[(vertex esi).sx]	;;left vertex
	sar	edi,18						;;PD 08Feb96
	sub	ecx,edi
	inc	ecx
	jle	@@Out
	shl	edi,2
	add	edi,eax			;;start scr. adr.

	mov	eax,[(vertex esi).ix]	;;left vertex
	mov	[IX],eax
	sub	eax,[(vertex ebx).ix]	;;right vertex
	neg	eax
	mov	edx,eax
	sar	edx,01fh
	idiv	ecx
	mov	[DIX],eax		;;image x delta

	mov	eax,[(vertex esi).iy]	;;left vertex
	mov	[IY],eax
	sub	eax,[(vertex ebx).iy]	;;right vertex
	neg	eax
	mov	edx,eax
	sar	edx,01fh
	idiv	ecx
	mov	[DIY],eax		;;image y delta

	mov	esi,[(colourdata colour_data).imageptr]
	mov	edx,[IX]
	mov	ebp,[IY]

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width
	or	ecx,[(colourdata colour_data).imagexmask]

;;DeadCode PD 10Jun96 	ALIGN	16
@@Loop:
	push	cx
	mov	ebx,edx
	and	ebx,ecx
	shr	ebx,16
	mov	eax,ebp
	and	eax,[(colourdata colour_data).imageymask]
	mov	cl,[(colourdata colour_data).imageyshift]
	shr	eax,cl
	add	ebx,eax
	mov	al,[esi+ebx]
	mov	ah,al
	stosw
	stosw
	pop	cx
	add	edx,[DIX]
	add	ebp,[DIY]
	dec	cx
	jnz	short @@Loop
@@Out:
	pop	ebp
	pop	edi
	pop	ecx
	ret
	endp

;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
;;	MASKED IMAGE MAPPING SCAN LINE ROUTINES @ x1, x2 and x4 pixel rez.
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
;;	ALIGN	16
;;//DeadCode ARM 24Jun96 	DW	0,0,0,0,0,0,0
;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_MImageHoriLine1
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Thu 14 Dec 1995
;;Modified
;;
;;Description
;;
;;Inputs	eax = screen ptr
;;		edx = left vertex
;;		ebx = right vertex
;;
;;Returns
;;
;;Externals
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
	push	ecx
	push	edi
	mov	ecx,[(vertex ebx).sx]	;;right vertex
	sar	ecx,16						;;PD 08Feb96
	mov	esi,edx
	mov	edi,[(vertex esi).sx]	;;left vertex
	sar	edi,16						;;PD 08Feb96
	sub	ecx,edi
	inc	ecx
	jle	@@Out
	add	edi,eax			;;start scr. adr.
	push	ebp
	mov	eax,[(vertex esi).ix]	;;left vertex
	mov	[IX],eax
	sub	eax,[(vertex ebx).ix]	;;right vertex
	neg	eax
	mov	edx,eax
	sar	edx,31
	idiv	ecx
	mov	[DIX],eax		;;image x delta
	mov	eax,[(vertex esi).iy]	;;left vertex
	mov	[IY],eax
	sub	eax,[(vertex ebx).iy]	;;right vertex
	neg	eax
	mov	edx,eax
	sar	edx,31
	idiv	ecx
	mov	[DIY],eax		;;image y delta
	or	ecx,[(colourdata colour_data).imagexmask]
	mov	esi,[(colourdata colour_data).imageptr]
	mov	edx,[IX]
	mov	ebp,[IY]

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width

;;DeadCode PD 10Jun96 	ALIGN	16
@@Loop:
	push	cx
	mov	eax,ebp
	mov	ebx,edx
	and	eax,[(colourdata colour_data).imageymask]
	and	ebx,ecx
	shr	ebx,16
	mov	cl,[(colourdata colour_data).imageyshift]
	shr	eax,cl
	add	ebx,eax
	mov	al,[esi+ebx]
	cmp	al,0FEh
	pop	cx
	jz	short @@MaskByte
	stosb
	add	edx,[dword ptr ds:DIX]
	add	ebp,[dword ptr ds:DIY]
	dec	cx
	jnz	short @@Loop
	pop	ebp
@@Out:
	pop	edi
	pop	ecx
	ret

@@MaskByte:
	inc	edi
	add	edx,[dword ptr ds:DIX]
	add	ebp,[dword ptr ds:DIY]
	dec	cx
	jnz	short @@Loop
	pop	ebp
	pop	edi
	pop	ecx
	ret
	endp

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_MImageHoriLine2
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Thu 14 Dec 1995
;;Modified
;;
;;Description	Same as ASM_ImageHoriLine1 but double pixel fill
;;
;;Inputs	eax = screen ptr
;;		edx = left vertex
;;		ebx = right vertex
;;
;;Returns
;;
;;Externals
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
	push	ecx
	push	edi
	push	ebp
	mov	ecx,[(vertex ebx).sx]	;;right vertex
	sar	ecx,17						;;PD 08Feb96
	mov	esi,edx
	mov	edi,[(vertex esi).sx]	;;left vertex
	sar	edi,17
	sub	ecx,edi
	inc	ecx
	jle	@@Out
	add	edi,edi
	add	edi,eax			;;start scr. adr.

	mov	eax,[(vertex esi).ix]	;;left vertex
	mov	[IX],eax
	sub	eax,[(vertex ebx).ix]	;;right vertex
	neg	eax
	;;cdq							;;PD 12Feb96
	mov	edx,eax
	sar	edx,01fh
	idiv	ecx
	mov	[DIX],eax		;;image x delta

	mov	eax,[(vertex esi).iy]	;;left vertex
	mov	[IY],eax
	sub	eax,[(vertex ebx).iy]	;;right vertex
	neg	eax
	;;cdq							;;PD 12Feb96
	mov	edx,eax
	sar	edx,01fh
	idiv	ecx
	mov	[DIY],eax		;;image y delta

	mov	esi,[(colourdata colour_data).imageptr]
	mov	edx,[IX]
	mov	ebp,[IY]

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width
	or	ecx,[(colourdata colour_data).imagexmask]

;;DeadCode PD 10Jun96 	ALIGN	16
@@Loop:
	push	cx
	mov	ebx,edx
	and	ebx,ecx
	shr	ebx,16
	mov	eax,ebp
	and	eax,[(colourdata colour_data).imageymask]
	mov	cl,[(colourdata colour_data).imageyshift]
	shr	eax,cl
	add	ebx,eax
	mov	al,[esi+ebx]
	cmp	al,0FEh
	jz	short @@MaskByte
	mov	ah,al
	stosw
	mov	eax,[DIX]
	add	edx,eax
	mov	eax,[DIY]
	add	ebp,eax
	pop	cx
	dec	cx
	jnz	short @@Loop
@@Out:
	pop	ebp
	pop	edi
	pop	ecx
	ret

@@MaskByte:
	add	edi,2
	mov	eax,[DIX]
	add	edx,eax
	mov	eax,[DIY]
	add	ebp,eax
	pop	cx
	dec	cx
	jnz	short @@Loop
	pop	ebp
	pop	edi
	pop	ecx
	ret
	endp

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_MImageHoriLine4
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Thu 14 Dec 1995
;;Modified
;;
;;Description	Same as ASM_ImageHoriLine1 but quad pixel fill
;;
;;Inputs	eax = screen ptr
;;		edx = left vertex
;;		ebx = right vertex
;;
;;Returns
;;
;;Externals
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
	push	ecx
	push	edi
	push	ebp
	mov	ecx,[(vertex ebx).sx]	;;right vertex
	sar	ecx,18						;;PD 08Feb96
	mov	esi,edx
	mov	edi,[(vertex esi).sx]	;;left vertex
	sar	edi,18						;;PD 08Feb96
	sub	ecx,edi
	inc	ecx
	jle	@@Out
	shl	edi,2
	add	edi,eax			;;start scr. adr.

	mov	eax,[(vertex esi).ix]	;;left vertex
	mov	[IX],eax
	sub	eax,[(vertex ebx).ix]	;;right vertex
	neg	eax
	;;cdq							;;PD 12Feb96
	mov	edx,eax
	sar	edx,01fh
	idiv	ecx
	mov	[DIX],eax		;;image x delta

	mov	eax,[(vertex esi).iy]	;;left vertex
	mov	[IY],eax
	sub	eax,[(vertex ebx).iy]	;;right vertex
	neg	eax
	;;cdq							;;PD 12Feb96
	mov	edx,eax
	sar	edx,01fh
	idiv	ecx
	mov	[DIY],eax		;;image y delta

	mov	esi,[(colourdata colour_data).imageptr]
	mov	edx,[IX]
	mov	ebp,[IY]

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width
	or	ecx,[(colourdata colour_data).imagexmask]

;;DeadCode PD 10Jun96 	ALIGN	16
@@Loop:
	push	cx
	mov	ebx,edx
	and	ebx,ecx
	shr	ebx,16
	mov	eax,ebp
	and	eax,[(colourdata colour_data).imageymask]
	mov	cl,[(colourdata colour_data).imageyshift]
	shr	eax,cl
	add	ebx,eax
	mov	al,[esi+ebx]
	cmp	al,0FEh
	jz	short @@MaskByte
	mov	ah,al
	stosw
	stosw
	mov	eax,[DIX]
	add	edx,eax
	mov	eax,[DIY]
	add	ebp,eax
	pop	cx
	dec	cx
	jnz	short @@Loop
@@Out:
	pop	ebp
	pop	edi
	pop	ecx
	ret

@@MaskByte:
	add	edi,4
	mov	eax,[DIX]
	add	edx,eax
	mov	eax,[DIY]
	add	ebp,eax
	pop	cx
	dec	cx
	jnz	short @@Loop
	pop	ebp
	pop	edi
	pop	ecx
	ret

	endp

;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
;;	SHADED IMAGE MAPPING SCAN LINE ROUTINES @ x1, x2 and x4 pixel rez.
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_SImageHoriLine1
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Thu 14 Dec 1995
;;Modified
;;
;;Description
;;
;;Inputs	eax = screen ptr
;;		edx = left vertex
;;		ebx = right vertex
;;
;;Returns
;;
;;Externals
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
	push	ecx
	push	edi
	push	ebp
	mov	ecx,[(vertex ebx).sx]	;;right vertex
	sar	ecx,16						;;PD 08Feb96
	mov	esi,edx
	mov	edi,[(vertex esi).sx]	;;left vertex
	sar	edi,16						;;PD 08Feb96
	sub	ecx,edi
	inc	ecx
	jle	@@Out

	mov	ebp,[(vertex esi).sy]
	add	ebp,1024
	add	ebp,[(colourdata colour_data).aliastblptr]
	mov	bp,[word ptr ds:ebp]				;;PD 16May96
	mov	[word ptr ds:JITTER],bp				;;PD 16May96

	add	edi,eax			;;start scr. adr.

	mov	eax,[(vertex esi).intensity]
	mov	[INTENS],eax
	sub	eax,[(vertex ebx).intensity]
	neg	eax
	;;cdq							;;PD 12Feb96
	mov	edx,eax
	sar	edx,01fh
	idiv	ecx
	mov	[DINTENS],eax

	mov	eax,[(vertex esi).ix]	;;left vertex
	mov	[IX],eax					;;PD 15May96

	sub	eax,[(vertex ebx).ix]	;;right vertex
	neg	eax
	;;cdq							;;PD 12Feb96
	mov	edx,eax
	sar	edx,01fh
	idiv	ecx
	mov	[DIX],eax		;;image x delta

	mov	eax,[(vertex esi).iy]	;;left vertex
	mov	[IY],eax
	sub	eax,[(vertex ebx).iy]	;;right vertex
	neg	eax
	;;cdq							;;PD 12Feb96
	mov	edx,eax
	sar	edx,01fh
	idiv	ecx
	mov	[DIY],eax		;;image y delta

	mov	esi,[(colourdata colour_data).imageptr]
	mov	edx,[IX]
	mov	ebp,[IY]

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width
	or	ecx,[(colourdata colour_data).imagexmask]

;;DeadCode PD 10Jun96 	ALIGN	16
@@Loop:
	push	cx
	mov	ebx,edx
	and	ebx,ecx
	shr	ebx,16
	mov	eax,ebp
	and	eax,[(colourdata colour_data).imageymask]
	mov	cl,[(colourdata colour_data).imageyshift]
	shr	eax,cl
	add	ebx,eax
;;TempCode PD 15May96 	mov	eax,[INTENS]
;;TempCode PD 15May96 	shr	eax,20
;;TempCode PD 15May96 	mov	ch,[esi+ebx]
;;TempCode PD 15May96 	mov	ah,ch
;;TempCode PD 15May96 	and	ah,0F0h
;;TempCode PD 15May96 	and	ch,00Fh
;;TempCode PD 15May96 	add	al,ch
;;TempCode PD 15May96 	cmp	al,00Fh
;;TempCode PD 15May96 	jbe	short @@GotShade
;;TempCode PD 15May96 	mov	al,00Fh
;;TempCode PD 15May96 @@GotShade:
;;TempCode PD 15May96 	or	al,ah
	mov	eax,[INTENS]					;;PD 15May96
;;//TempCode JIM 09Aug96 	add	eax,[dword ptr ds:JITTER];;			//PD 10Jun96
	shr	eax,16 ;;20					//PD 10Jun96
	xor	cl,cl						;;PD 15May96
	mov	ch,[esi+ebx]					;;PD 15May96
	shr	cx,4						;;PD 15May96
	or	ax,cx						;;PD 15May96
	mov	al,[ds:ShadeData2+eax]				;;PD 15May96

	mov	[byte ptr ds:edi],al				;;PD 15May96

	mov	eax,[DIX]
	add	edx,eax
	mov	eax,[DIY]
	add	ebp,eax
;;//TempCode JIM 09Aug96 	mov	eax,[DINTENS]
;;//TempCode JIM 09Aug96 	add	[INTENS],eax
	pop	cx
	dec	cx
	jnz	short @@Loop
@@Out:
	pop	ebp
    	pop	edi
	pop	ecx
	ret
	endp

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_SImageHoriLine2
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Thu 14 Dec 1995
;;Modified
;;
;;Description	Same as ASM_ImageHoriLine1 but double pixel fill
;;
;;Inputs	eax = screen ptr
;;		edx = left vertex
;;		ebx = right vertex
;;
;;Returns
;;
;;Externals
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
	push	ecx
	push	edi
	push	ebp
	mov	ecx,[(vertex ebx).sx]	;;right vertex
	sar	ecx,17						;;PD 08Feb96
	mov	esi,edx
	mov	edi,[(vertex esi).sx]	;;left vertex
	sar	edi,17						;;PD 08Feb96
	sub	ecx,edi
	inc	ecx
	jle	@@Out
	add	edi,edi

	mov	ebp,[(vertex esi).sy]
	add	ebp,1024
	add	ebp,[(colourdata colour_data).aliastblptr]
	mov	bp,[word ptr ds:ebp]				;;PD 16May96
	mov	[word ptr ds:JITTER],bp				;;PD 16May96

	add	edi,eax			;;start scr. adr.

	mov	eax,[(vertex esi).intensity]
	mov	[INTENS],eax
	sub	eax,[(vertex ebx).intensity]
	xor	ax,ax
	test	eax,eax
	jz	@@Fast
	neg	eax
	mov	edx,eax
	sar	edx,31
	idiv	ecx
	mov	[DINTENS],eax

	mov	eax,[(vertex esi).ix]	;;left vertex
	mov	[IX],eax

	sub	eax,[(vertex ebx).ix]	;;right vertex
	neg	eax
	mov	edx,eax
	sar	edx,31
	idiv	ecx
	mov	[DIX],eax		;;image x delta

	mov	eax,[(vertex esi).iy]	;;left vertex
	mov	[IY],eax
	sub	eax,[(vertex ebx).iy]	;;right vertex
	neg	eax
	mov	edx,eax
	sar	edx,31
	idiv	ecx
	mov	[DIY],eax		;;image y delta

	mov	esi,[(colourdata colour_data).imageptr]
	mov	edx,[IX]
	mov	ebp,[IY]

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width
	or	ecx,[(colourdata colour_data).imagexmask]

;;DeadCode PD 10Jun96 	ALIGN	16
@@Loop:
	push	cx
	mov	ebx,edx
	and	ebx,ecx
	shr	ebx,16
	mov	eax,ebp
	and	eax,[(colourdata colour_data).imageymask]
	mov	cl,[(colourdata colour_data).imageyshift]
	shr	eax,cl
	add	ebx,eax

	mov	eax,[INTENS]
	add	eax,[dword ptr ds:JITTER]			;;PD 16May96
  	shr	eax,16	;;20					//PD 10Jun96
	cmp	eax,0Fh
	jbe	short @@OKay
	mov	eax,0Fh
@@OKay:
 	xor	cl,cl						;;PD 15May96
 	mov	ch,[esi+ebx]					;;PD 15May96
 	shr	cx,4						;;PD 15May96
 	or	ax,cx						;;PD 15May96
 	mov	al,[ds:ShadeData2+eax]				;;PD 15May96
 	mov	ah,al						;;PD 15May96

 	mov	[word ptr ds:edi],ax				;;PD 15May96
 	inc	edi						;;PD 15May96
 	inc	edi						;;PD 15May96

	pop	cx
	add	edx,[dword ptr ds:DIX]
	add	ebp,[dword ptr ds:DIY]
	mov	eax,[DINTENS]
	add	[INTENS],eax

	mov	ax,[word ptr ds:JITTER]				;;PD 16May96
	add	ax,9136h					;;PD 16May96
	ror	ax,3						;;PD 16May96
	mov	[word ptr ds:JITTER],ax				;;PD 16May96

	dec	cx
	jnz	short @@Loop
@@Out:
	pop	ebp
	pop	edi
	pop	ecx
	ret
@@Fast:
	mov	eax,[(vertex esi).ix]	;;left vertex
	mov	[IX],eax
	sub	eax,[(vertex ebx).ix]	;;right vertex
	neg	eax
	mov	edx,eax
	sar	edx,31
	idiv	ecx
	mov	[DIX],eax		;;image x delta

	mov	eax,[(vertex esi).iy]	;;left vertex
	mov	[IY],eax
	sub	eax,[(vertex ebx).iy]	;;right vertex
	neg	eax
	mov	edx,eax
	sar	edx,31
	idiv	ecx
	mov	[DIY],eax		;;image y delta

	mov	esi,[(colourdata colour_data).imageptr]
	mov	edx,[IX]
	mov	ebp,[IY]

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width
	or	ecx,[(colourdata colour_data).imagexmask]

;;DeadCode PD 10Jun96 	ALIGN	16
@@FLoop:
	push	cx
	mov	ebx,edx
	and	ebx,ecx
	shr	ebx,16
	mov	eax,ebp
	and	eax,[(colourdata colour_data).imageymask]
	mov	cl,[(colourdata colour_data).imageyshift]
	shr	eax,cl
	add	ebx,eax

	mov	eax,[INTENS]					;;PD 15May96
	add	eax,[dword ptr ds:JITTER]			;;PD 16May96
	shr	eax,16	;;20					//PD 10Jun96
	cmp	eax,0Fh
	jbe	short @@OKay2
	mov	eax,0Fh
@@OKay2:
	xor	cl,cl						;;PD 15May96
	mov	ch,[esi+ebx]					;;PD 15May96
	shr	cx,4						;;PD 15May96
	or	ax,cx						;;PD 15May96
	mov	al,[ds:ShadeData2+eax]				;;PD 15May96
	mov	ah,al						;;PD 15May96
	mov	[word ptr ds:edi],ax				;;PD 15May96
	inc	edi						;;PD 15May96
	inc	edi						;;PD 15May96

	pop	cx
	add	edx,[dword ptr ds:DIX]
	add	ebp,[dword ptr ds:DIY]

	mov	ax,[word ptr ds:JITTER]				;;PD 16May96
	add	ax,9136h					;;PD 16May96
	ror	ax,3						;;PD 16May96
	mov	[word ptr ds:JITTER],ax				;;PD 16May96

	dec	cx
	jnz	short @@FLoop
	pop	ebp
	pop	edi
	pop	ecx
	ret
	endp

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_SImageHoriLine4
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Thu 14 Dec 1995
;;Modified
;;
;;Description	Same as ASM_ImageHoriLine1 but quad pixel fill
;;
;;Inputs	eax = screen ptr
;;		edx = left vertex
;;		ebx = right vertex
;;
;;Returns
;;
;;Externals
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
	push	ecx
	push	edi
	push	ebp
	mov	ecx,[(vertex ebx).sx]	;;right vertex
	sar	ecx,18						;;PD 08Feb96
	mov	esi,edx
	mov	edi,[(vertex esi).sx]	;;left vertex
	sar	edi,18						;;PD 08Feb96
	sub	ecx,edi
	inc	ecx
	jle	@@Out
	shl	edi,2

	mov	ebp,[(vertex esi).sy]
	add	ebp,1024
	add	ebp,[(colourdata colour_data).aliastblptr]
	mov	bp,[word ptr ds:ebp]				;;PD 16May96
	mov	[word ptr ds:JITTER],bp				;;PD 16May96

	add	edi,eax			;;start scr. adr.

	mov	eax,[(vertex esi).intensity]
	mov	[INTENS],eax
	sub	eax,[(vertex ebx).intensity]
	xor	ax,ax
	test	eax,eax
	jz	@@Fast
	neg	eax
	mov	edx,eax
	sar	edx,01fh
	idiv	ecx
	mov	[DINTENS],eax

	mov	eax,[(vertex esi).ix]	;;left vertex
	mov	[IX],eax

	sub	eax,[(vertex ebx).ix]	;;right vertex
	neg	eax
	mov	edx,eax
	sar	edx,01fh
	idiv	ecx
	mov	[DIX],eax		;;image x delta

	mov	eax,[(vertex esi).iy]	;;left vertex
	mov	[IY],eax
	sub	eax,[(vertex ebx).iy]	;;right vertex
	neg	eax
	mov	edx,eax
	sar	edx,01fh
	idiv	ecx
	mov	[DIY],eax		;;image y delta

	mov	esi,[(colourdata colour_data).imageptr]
	mov	edx,[IX]
	mov	ebp,[IY]

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width
	or	ecx,[(colourdata colour_data).imagexmask]

;;DeadCode PD 10Jun96 	ALIGN	16
@@Loop:
	push	cx
	mov	ebx,edx
	and	ebx,ecx
	shr	ebx,16
	mov	eax,ebp
	and	eax,[(colourdata colour_data).imageymask]
	mov	cl,[(colourdata colour_data).imageyshift]
	shr	eax,cl
	add	ebx,eax

	mov	eax,[INTENS]
	add	eax,[dword ptr ds:JITTER];;			//PD 10Jun96
	shr	eax,16	;;20					//PD 10Jun96

	cmp	eax,0Fh
	jbe	short @@OKay
       	mov	eax,0Fh
@@OKay:

	xor	cl,cl						;;PD 15May96
	mov	ch,[esi+ebx]					;;PD 15May96
	shr	cx,4						;;PD 15May96
	or	ax,cx						;;PD 15May96
	mov	al,[ds:ShadeData2+eax]				;;PD 15May96
	mov	ah,al						;;PD 15May96
	stosw							;;PD 15May96
	stosw							;;PD 15May96

	pop	cx
	add	edx,[dword ptr ds:DIX]
	add	ebp,[dword ptr ds:DIY]
	mov	eax,[DINTENS]
	add	[INTENS],eax

	mov	dx,[word ptr ds:JITTER]				;;PD 16May96
	add	dx,9136h					;;PD 16May96
	ror	dx,3						;;PD 16May96
	mov	[word ptr ds:JITTER],dx				;;PD 16May96

	dec	cx
	jnz	short @@Loop
@@Out:
	pop	ebp
	pop	edi
	pop	ecx
	ret
@@Fast:
	mov	eax,[(vertex esi).ix]	;;left vertex
	mov	[IX],eax
	sub	eax,[(vertex ebx).ix]	;;right vertex
	neg	eax
	mov	edx,eax
	sar	edx,31
	idiv	ecx
	mov	[DIX],eax		;;image x delta

	mov	eax,[(vertex esi).iy]	;;left vertex
	mov	[IY],eax
	sub	eax,[(vertex ebx).iy]	;;right vertex
	neg	eax
	mov	edx,eax
	sar	edx,31
	idiv	ecx
	mov	[DIY],eax		;;image y delta

	mov	esi,[(colourdata colour_data).imageptr]
	mov	edx,[IX]
	mov	ebp,[IY]

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width
	or	ecx,[(colourdata colour_data).imagexmask]

;;DeadCode PD 10Jun96 	ALIGN	16
@@FLoop:
	push	cx
	mov	ebx,edx
	and	ebx,ecx
	shr	ebx,16
	mov	eax,ebp
	and	eax,[(colourdata colour_data).imageymask]
	mov	cl,[(colourdata colour_data).imageyshift]
	shr	eax,cl
	add	ebx,eax

;;TempCode PD 15May96 	mov	al,[byte ptr INTENS+2]
;;TempCode PD 15May96 	shr	al,4
;;TempCode PD 15May96 	mov	ch,[esi+ebx]
;;TempCode PD 15May96 	mov	ah,ch
;;TempCode PD 15May96 	and	ah,0F0h
;;TempCode PD 15May96 	and	ch,00Fh
;;TempCode PD 15May96 	add	al,ch
;;TempCode PD 15May96 	cmp	al,00Fh
;;TempCode PD 15May96 	jbe	short @@FGotShade
;;TempCode PD 15May96 	mov	al,00Fh
;;TempCode PD 15May96 @@FGotShade:
;;TempCode PD 15May96 	or	al,ah
;;TempCode PD 15May96
;;TempCode PD 15May96 	mov	ah,al
;;TempCode PD 15May96 	stosw
;;TempCode PD 15May96 	stosw

	mov	eax,[INTENS]					;;PD 15May96
	shr	eax,16	;;20					//PD 10Jun96
	xor	cl,cl						;;PD 15May96
	mov	ch,[esi+ebx]					;;PD 15May96
	shr	cx,4						;;PD 15May96
	or	ax,cx						;;PD 15May96
	mov	al,[ds:ShadeData2+eax]				;;PD 15May96
	mov	ah,al						;;PD 15May96

	stosw							;;PD 15May96
	stosw							;;PD 15May96

	pop	cx
	add	edx,[dword ptr ds:DIX]
	add	ebp,[dword ptr ds:DIY]
	dec	cx
	jnz	short @@FLoop
	pop	ebp
	pop	edi
	pop	ecx
	ret
	endp

;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
;; PLAIN GREY 3D POLYGON SCAN LINE ROUTINES @ x1, x2 and x4 pixel rez.
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------

	ALIGN	2

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_GPlainHoriLine1
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Thu 21 Dec 1995
;;Modified
;;
;;Description
;;
;;Inputs
;;
;;Returns
;;
;;Externals
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
	push	ecx
	push	edi
	mov	ecx,[(vertex ebx).sx]	;;right vertex
	sar	ecx,16						;;PD 08Feb96
	mov	esi,edx
	mov	edi,[(vertex esi).sx]	;;left vertex
	sar	edi,16						;;PD 08Feb96
	sub	ecx,edi
	inc	ecx
	jle	@@Out
	add	edi,eax			;;start scr. adr.

	xor	ebx,ebx
	mov	bl,[byte ptr (colourdata colour_data).col]	;;PD 08Jan96
	mov	al,[Grey3DTable+ebx]				;;PD 08Jan96
	mov	ah,al
	mov	bx,ax
	shl	eax,16
	mov	ax,bx
;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width
;;eax = colour.b, colour.b, colour.b, colour.b
;;//TempCode JIM 09Aug96 	rep	stosb
	cmp	ecx,10
	jb	@@slow
@@startloop:
	mov	[ds:edi],al
	dec	cl
	inc	di
	test	di,3
	jnz	@@startloop
	sub	cx,3
@@evenloop:
	mov	[ds:edi],eax
	add	di,4
	sub	cx,4
	jg	@@evenloop
	add	cx,3
@@slow:
	rep	stosb
@@Out:
	pop	edi
	pop	ecx
	ret
	endp

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_GPlainHoriLine2
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Thu 4 Jan 1996
;;Modified
;;
;;Description
;;
;;Inputs
;;
;;Returns
;;
;;Externals
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
	push	ecx
	push	edi
	mov	ecx,[(vertex ebx).sx]	;;right vertex
	sar	ecx,17						;;PD 08Feb96
	mov	esi,edx
	mov	edi,[(vertex esi).sx]	;;left vertex
	sar	edi,17						;;PD 08Feb96
	sub	ecx,edi
	inc	ecx
	jle	@@Out
	add	edi,edi
	add	edi,eax			;;start scr. adr.

	xor	ebx,ebx
	mov	bl,[byte ptr (colourdata colour_data).col]	;;PD 08Jan96
	mov	al,[Grey3DTable+ebx]				;;PD 08Jan96
	mov	ah,al						;;PD 08Jan96

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width
;;eax = colour.b, colour.b, colour.b, colour.b
	rep	stosw
@@Out:
	pop	edi
	pop	ecx
	ret
	endp

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_GPlainHoriLine4
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Thu 4 Jan 1996
;;Modified
;;
;;Description
;;
;;Inputs
;;
;;Returns
;;
;;Externals
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
	push	ecx
	push	edi
	mov	ecx,[(vertex ebx).sx]	;;right vertex
	sar	ecx,18						;;PD 08Feb96
	mov	esi,edx
	mov	edi,[(vertex esi).sx]	;;left vertex
	sar	edi,18						;;PD 08Feb96
	sub	ecx,edi
	inc	ecx
	jle	@@Out
	shl	edi,2
	add	edi,eax			;;start scr. adr.

	xor	ebx,ebx
	mov	bl,[byte ptr (colourdata colour_data).col]	;;PD 08Jan96
	mov	al,[Grey3DTable+ebx]				;;PD 08Jan96
	mov	ah,al						;;PD 08Jan96
	mov	bx,ax						;;PD 08Jan96
	shl	eax,16						;;PD 08Jan96
	mov	ax,bx						;;PD 08Jan96

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width
;;eax = colour.b, colour.b, colour.b, colour.b
	rep	stosd
@@Out:
	pop	edi
	pop	ecx
	ret
	endp

;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
;; SHADED GREY 3D POLYGON SCAN LINE ROUTINES @ x1, x2 and x4 pixel rez.
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------

	ALIGN	2

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_GGouraudHoriLine1
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Thu 21 Dec 1995
;;Modified
;;
;;Description
;;
;;Inputs
;;
;;Returns
;;
;;Externals
;;------------------------------------------------------------------------------
	public	ASM_GGouraudHoriLine2_,ASM_GGouraudHoriLine4_
ASM_GGouraudHoriLine2_:
ASM_GGouraudHoriLine4_:
;;------------------------------------------------------------------------------
	push	ecx
	push	edi
	mov	ecx,[(vertex ebx).sx]	;;right vertex
	sar	ecx,16						;;PD 08Feb96
	mov	esi,edx
	mov	edi,[(vertex esi).sx]	;;left vertex
	sar	edi,16						;;PD 08Feb96
	sub	ecx,edi
	inc	ecx
	jle	@@Out
	add	edi,eax			;;start scr. adr.

	mov	eax,[(colourdata colour_data).col]

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width
;;eax = colour.b, colour.b, colour.b, colour.b
	rep	stosb
@@Out:
	pop	edi
	pop	ecx
	ret
	endp

;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
;; NORMAL GREY 3D IMAGE MAPPING SCAN LINE ROUTINES @ x1, x2 and x4 pixel rez.
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------

	ALIGN	2

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_GImageHoriLine1
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Thu 14 Dec 1995
;;Modified
;;
;;Description
;;
;;Inputs	eax = screen ptr
;;		edx = left vertex
;;		ebx = right vertex
;;
;;Returns
;;
;;Externals
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
	push	ecx
	push	edi
	push	ebp
	mov	ecx,[(vertex ebx).sx]	;;right vertex
	sar	ecx,16						;;PD 08Feb96
	mov	esi,edx
	mov	edi,[(vertex esi).sx]	;;left vertex
	sar	edi,16						;;PD 08Feb96
	sub	ecx,edi
	inc	ecx
	jle	@@Out
	add	edi,eax			;;start scr. adr.

	mov	eax,[(vertex esi).ix]	;;left vertex
	mov	[IX],eax
	sub	eax,[(vertex ebx).ix]	;;right vertex
	neg	eax
	;;cdq							;;PD 12Feb96
	mov	edx,eax
	sar	edx,01fh
	idiv	ecx
	mov	[DIX],eax		;;image x delta

	mov	eax,[(vertex esi).iy]	;;left vertex
	mov	[IY],eax
	sub	eax,[(vertex ebx).iy]	;;right vertex
	neg	eax
	;;cdq							;;PD 12Feb96
	mov	edx,eax
	sar	edx,01fh
	idiv	ecx
	mov	[DIY],eax		;;image y delta

	mov	esi,[(colourdata colour_data).imageptr]
	mov	edx,[IX]
	mov	ebp,[IY]

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width
	or	ecx,[(colourdata colour_data).imagexmask]

;;DeadCode PD 10Jun96 	ALIGN	16
@@Loop:
	push	cx
	mov	ebx,edx
	and	ebx,ecx
	shr	ebx,16
	mov	eax,ebp
	and	eax,[(colourdata colour_data).imageymask]
	mov	cl,[(colourdata colour_data).imageyshift]
	shr	eax,cl
	add	ebx,eax
	xor	eax,eax						;;PD 02Apr96
	mov	al,[byte ptr ds:esi+ebx]			;;PD 02Apr96
	mov	al,[Grey3DTable+eax]				;;PD 02Apr96
	stosb
	mov	eax,[DIX]
	add	edx,eax
	mov	eax,[DIY]
	add	ebp,eax
	pop	cx
	dec	cx
	jnz	short @@Loop
@@Out:
	pop	ebp
	pop	edi
	pop	ecx
	ret
	endp

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_GImageHoriLine2
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Thu 14 Dec 1995
;;Modified
;;
;;Description	Same as ASM_ImageHoriLine1 but double pixel fill
;;
;;Inputs	eax = screen ptr
;;		edx = left vertex
;;		ebx = right vertex
;;
;;Returns
;;
;;Externals
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
	push	ecx
	push	edi
	push	ebp
	mov	ecx,[(vertex ebx).sx]	;;right vertex
	sar	ecx,17						;;PD 08Feb96
	mov	esi,edx
	mov	edi,[(vertex esi).sx]	;;left vertex
	sar	edi,17						;;PD 08Feb96
	sub	ecx,edi
	inc	ecx
	jle	@@Out
	add	edi,edi
	add	edi,eax			;;start scr. adr.

	mov	eax,[(vertex esi).ix]	;;left vertex
	mov	[IX],eax
	sub	eax,[(vertex ebx).ix]	;;right vertex
	neg	eax
	;;cdq							;;PD 12Feb96
	mov	edx,eax
	sar	edx,01fh
	idiv	ecx
	mov	[DIX],eax		;;image x delta

	mov	eax,[(vertex esi).iy]	;;left vertex
	mov	[IY],eax
	sub	eax,[(vertex ebx).iy]	;;right vertex
	neg	eax
	;;cdq							;;PD 12Feb96
	mov	edx,eax
	sar	edx,01fh
	idiv	ecx
	mov	[DIY],eax		;;image y delta

	mov	esi,[(colourdata colour_data).imageptr]
	mov	edx,[IX]
	mov	ebp,[IY]

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width
	or	ecx,[(colourdata colour_data).imagexmask]

;;DeadCode PD 10Jun96 	ALIGN	16
@@Loop:
	push	cx
	mov	ebx,edx
	and	ebx,ecx
	shr	ebx,16
	mov	eax,ebp
	and	eax,[(colourdata colour_data).imageymask]
	mov	cl,[(colourdata colour_data).imageyshift]
	shr	eax,cl
	add	ebx,eax
	mov	bl,[esi+ebx]
	movzx	ebx,bl
	mov	al,[Grey3DTable+ebx]
	mov	ah,al
	stosw
	mov	eax,[DIX]
	add	edx,eax
	mov	eax,[DIY]
	add	ebp,eax
	pop	cx
	dec	cx
	jnz	short @@Loop
@@Out:
	pop	ebp
	pop	edi
	pop	ecx
	ret
	endp

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_GImageHoriLine4
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Thu 14 Dec 1995
;;Modified
;;
;;Description	Same as ASM_ImageHoriLine1 but quad pixel fill
;;
;;Inputs	eax = screen ptr
;;		edx = left vertex
;;		ebx = right vertex
;;
;;Returns
;;
;;Externals
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
	push	ecx
	push	edi
	push	ebp
	mov	ecx,[(vertex ebx).sx]	;;right vertex
	sar	ecx,18						;;PD 08Feb96
	mov	esi,edx
	mov	edi,[(vertex esi).sx]	;;left vertex
	sar	edi,18						;;PD 08Feb96
	sub	ecx,edi
	inc	ecx
	jle	@@Out
	shl	edi,2
	add	edi,eax			;;start scr. adr.

	mov	eax,[(vertex esi).ix]	;;left vertex
	mov	[IX],eax
	sub	eax,[(vertex ebx).ix]	;;right vertex
	neg	eax
	;;cdq							;;PD 12Feb96
	mov	edx,eax
	sar	edx,01fh
	idiv	ecx
	mov	[DIX],eax		;;image x delta

	mov	eax,[(vertex esi).iy]	;;left vertex
	mov	[IY],eax
	sub	eax,[(vertex ebx).iy]	;;right vertex
	neg	eax
	;;cdq							;;PD 12Feb96
	mov	edx,eax
	sar	edx,01fh
	idiv	ecx
	mov	[DIY],eax		;;image y delta

	mov	esi,[(colourdata colour_data).imageptr]
	mov	edx,[IX]
	mov	ebp,[IY]

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width
	or	ecx,[(colourdata colour_data).imagexmask]

;;DeadCode PD 10Jun96 	ALIGN	16
@@Loop:
	push	cx
	mov	ebx,edx
	and	ebx,ecx
	shr	ebx,16
	mov	eax,ebp
	and	eax,[(colourdata colour_data).imageymask]
	mov	cl,[(colourdata colour_data).imageyshift]
	shr	eax,cl
	add	ebx,eax
	mov	bl,[esi+ebx]
	movzx	ebx,bl
	mov	al,[Grey3DTable+ebx]
	mov	ah,al
	stosw
	stosw
	mov	eax,[DIX]
	add	edx,eax
	mov	eax,[DIY]
	add	ebp,eax
	pop	cx
	dec	cx
	jnz	short @@Loop
@@Out:
	pop	ebp
	pop	edi
	pop	ecx
	ret
	endp


;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_GMImageHoriLine1
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Thu 14 Dec 1995
;;Modified
;;
;;Description
;;
;;Inputs	eax = screen ptr
;;		edx = left vertex
;;		ebx = right vertex
;;
;;Returns
;;
;;Externals
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
	push	ecx
	push	edi
	push	ebp
	mov	ecx,[(vertex ebx).sx]	;;right vertex
	sar	ecx,16						;;PD 08Feb96
	mov	esi,edx
	mov	edi,[(vertex esi).sx]	;;left vertex
	sar	edi,16						;;PD 08Feb96
	sub	ecx,edi
	inc	ecx
	jle	@@Out
	add	edi,eax			;;start scr. adr.

	mov	eax,[(vertex esi).ix]	;;left vertex
	mov	[IX],eax
	sub	eax,[(vertex ebx).ix]	;;right vertex
	neg	eax
	;;cdq							;;PD 12Feb96
	mov	edx,eax
	sar	edx,01fh
	idiv	ecx
	mov	[DIX],eax		;;image x delta

	mov	eax,[(vertex esi).iy]	;;left vertex
	mov	[IY],eax
	sub	eax,[(vertex ebx).iy]	;;right vertex
	neg	eax
	;;cdq							;;PD 12Feb96
	mov	edx,eax
	sar	edx,01fh
	idiv	ecx
	mov	[DIY],eax		;;image y delta

	mov	esi,[(colourdata colour_data).imageptr]
	mov	edx,[IX]
	mov	ebp,[IY]

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width
	or	ecx,[(colourdata colour_data).imagexmask]

;;DeadCode PD 10Jun96 	ALIGN	16
@@Loop:
	push	cx
	mov	ebx,edx
	and	ebx,ecx
	shr	ebx,16
	mov	eax,ebp
	and	eax,[(colourdata colour_data).imageymask]
	mov	cl,[(colourdata colour_data).imageyshift]
	shr	eax,cl
	add	ebx,eax
	xor	eax,eax						;;PD 02Apr96
	mov	al,[byte ptr ds:esi+ebx]			;;PD 02Apr96
	cmp	al,0FEh						;;PD 03Apr96
	jz	short @@MaskByte				;;PD 03Apr96
	mov	al,[Grey3DTable+eax]				;;PD 02Apr96
	mov	[byte ptr ds:edi],al
@@MaskByte:							;;PD 03Apr96
	inc	edi						;;PD 03Apr96
	mov	eax,[DIX]
	add	edx,eax
	mov	eax,[DIY]
	add	ebp,eax
	pop	cx
	dec	cx
	jnz	short @@Loop
@@Out:
	pop	ebp
	pop	edi
	pop	ecx
	ret
	endp

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_GMImageHoriLine2
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Thu 14 Dec 1995
;;Modified
;;
;;Description	Same as ASM_ImageHoriLine1 but double pixel fill
;;
;;Inputs	eax = screen ptr
;;		edx = left vertex
;;		ebx = right vertex
;;
;;Returns
;;
;;Externals
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
	push	ecx
	push	edi
	push	ebp
	mov	ecx,[(vertex ebx).sx]	;;right vertex
	sar	ecx,17						;;PD 08Feb96
	mov	esi,edx
	mov	edi,[(vertex esi).sx]	;;left vertex
	sar	edi,17						;;PD 08Feb96
	sub	ecx,edi
	inc	ecx
	jle	@@Out
	add	edi,edi
	add	edi,eax			;;start scr. adr.

	mov	eax,[(vertex esi).ix]	;;left vertex
	mov	[IX],eax
	sub	eax,[(vertex ebx).ix]	;;right vertex
	neg	eax
	;;cdq							;;PD 12Feb96
	mov	edx,eax
	sar	edx,01fh
	idiv	ecx
	mov	[DIX],eax		;;image x delta

	mov	eax,[(vertex esi).iy]	;;left vertex
	mov	[IY],eax
	sub	eax,[(vertex ebx).iy]	;;right vertex
	neg	eax
	;;cdq							;;PD 12Feb96
	mov	edx,eax
	sar	edx,01fh
	idiv	ecx
	mov	[DIY],eax		;;image y delta

	mov	esi,[(colourdata colour_data).imageptr]
	mov	edx,[IX]
	mov	ebp,[IY]

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width
	or	ecx,[(colourdata colour_data).imagexmask]

;;DeadCode PD 10Jun96 	ALIGN	16
@@Loop:
	push	cx
	mov	ebx,edx
	and	ebx,ecx
	shr	ebx,16
	mov	eax,ebp
	and	eax,[(colourdata colour_data).imageymask]
	mov	cl,[(colourdata colour_data).imageyshift]
	shr	eax,cl
	add	ebx,eax
	mov	bl,[esi+ebx]
	cmp	bl,0FEh						;;PD 03Apr96
	jz	short @@MaskByte				;;PD 03Apr96
	movzx	ebx,bl
	mov	al,[Grey3DTable+ebx]
	mov	ah,al
	mov	[word ptr ds:edi],ax
@@MaskByte:							;;PD 03Apr96
	inc	edi						;;PD 03Apr96
	inc	edi						;;PD 03Apr96
	mov	eax,[DIX]
	add	edx,eax
	mov	eax,[DIY]
	add	ebp,eax
	pop	cx
	dec	cx
	jnz	short @@Loop
@@Out:
	pop	ebp
	pop	edi
	pop	ecx
	ret
	endp

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_GMImageHoriLine4
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Thu 14 Dec 1995
;;Modified
;;
;;Description	Same as ASM_ImageHoriLine1 but quad pixel fill
;;
;;Inputs	eax = screen ptr
;;		edx = left vertex
;;		ebx = right vertex
;;
;;Returns
;;
;;Externals
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
	push	ecx
	push	edi
	push	ebp
	mov	ecx,[(vertex ebx).sx]	;;right vertex
	sar	ecx,18						;;PD 08Feb96
	mov	esi,edx
	mov	edi,[(vertex esi).sx]	;;left vertex
	sar	edi,18						;;PD 08Feb96
	sub	ecx,edi
	inc	ecx
	jle	@@Out
	shl	edi,2
	add	edi,eax			;;start scr. adr.

	mov	eax,[(vertex esi).ix]	;;left vertex
	mov	[IX],eax
	sub	eax,[(vertex ebx).ix]	;;right vertex
	neg	eax
	;;cdq							;;PD 12Feb96
	mov	edx,eax
	sar	edx,01fh
	idiv	ecx
	mov	[DIX],eax		;;image x delta

	mov	eax,[(vertex esi).iy]	;;left vertex
	mov	[IY],eax
	sub	eax,[(vertex ebx).iy]	;;right vertex
	neg	eax
	;;cdq							;;PD 12Feb96
	mov	edx,eax
	sar	edx,01fh
	idiv	ecx
	mov	[DIY],eax		;;image y delta

	mov	esi,[(colourdata colour_data).imageptr]
	mov	edx,[IX]
	mov	ebp,[IY]

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width
	or	ecx,[(colourdata colour_data).imagexmask]

;;DeadCode PD 10Jun96 	ALIGN	16
@@Loop:
	push	cx
	mov	ebx,edx
	and	ebx,ecx
	shr	ebx,16
	mov	eax,ebp
	and	eax,[(colourdata colour_data).imageymask]
	mov	cl,[(colourdata colour_data).imageyshift]
	shr	eax,cl
	add	ebx,eax
	mov	bl,[esi+ebx]
	cmp	bl,0FEh						;;PD 03Apr96
	jz	short @@MaskByte				;;PD 03Apr96
	movzx	ebx,bl
	mov	al,[Grey3DTable+ebx]
	mov	ah,al
	mov	[word ptr ds:edi],ax
	mov	[word ptr ds:edi+2],ax
@@MaskByte:							;;PD 03Apr96
	add	edi,4						;;PD 03Apr96
	mov	eax,[DIX]
	add	edx,eax
	mov	eax,[DIY]
	add	ebp,eax
	pop	cx
	dec	cx
	jnz	short @@Loop
@@Out:
	pop	ebp
	pop	edi
	pop	ecx
	ret
	endp


;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
;;	SHADED IMAGE MAPPING SCAN LINE ROUTINES @ x1, x2 and x4 pixel rez.
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_GSImageHoriLine1
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Thu 14 Dec 1995
;;Modified
;;
;;Description
;;
;;Inputs	eax = screen ptr
;;		edx = left vertex
;;		ebx = right vertex
;;
;;Returns
;;
;;Externals
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
	push	ecx
	push	edi
	push	ebp
	mov	ecx,[(vertex ebx).sx]	;;right vertex
	sar	ecx,16						;;PD 08Feb96
	mov	esi,edx
	mov	edi,[(vertex esi).sx]	;;left vertex
	sar	edi,16						;;PD 08Feb96
	sub	ecx,edi
	inc	ecx
	jle	@@Out
	add	edi,eax			;;start scr. adr.

	mov	eax,[(vertex esi).intensity]
	mov	[INTENS],eax
	sub	eax,[(vertex ebx).intensity]
	neg	eax
	;;cdq							;;PD 12Feb96
	mov	edx,eax
	sar	edx,01fh
	idiv	ecx
	mov	[DINTENS],eax

	mov	eax,[(vertex esi).ix]	;;left vertex
	mov	[IX],eax
	sub	eax,[(vertex ebx).ix]	;;right vertex
	neg	eax
	;;cdq							;;PD 12Feb96
	mov	edx,eax
	sar	edx,01fh
	idiv	ecx
	mov	[DIX],eax		;;image x delta

	mov	eax,[(vertex esi).iy]	;;left vertex
	mov	[IY],eax
	sub	eax,[(vertex ebx).iy]	;;right vertex
	neg	eax
	;;cdq							;;PD 12Feb96
	mov	edx,eax
	sar	edx,01fh
	idiv	ecx
	mov	[DIY],eax		;;image y delta

	mov	esi,[(colourdata colour_data).imageptr]
	mov	edx,[IX]
	mov	ebp,[IY]

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width
	or	ecx,[(colourdata colour_data).imagexmask]

;;DeadCode PD 10Jun96 	ALIGN	16
@@Loop:
	push	cx
	mov	ebx,edx
	and	ebx,ecx
	shr	ebx,16
	mov	eax,ebp
	and	eax,[(colourdata colour_data).imageymask]
	mov	cl,[(colourdata colour_data).imageyshift]
	shr	eax,cl
	add	ebx,eax
	mov	eax,[INTENS]
	shr	eax,16	;;20					//PD 10Jun96
	mov	ch,[esi+ebx]
	mov	ah,ch
	and	ah,0F0h
	and	ch,00Fh
	add	al,ch
	cmp	al,00Fh
	jbe	short @@GotShade
	mov	al,00Fh
@@GotShade:
	xor	ebx,ebx
	or	al,ah
	mov	bl,al						;;PD 08Jan96
	mov	al,[Grey3DTable+ebx]				;;PD 08Jan96
	stosb
	mov	eax,[DIX]
	add	edx,eax
	mov	eax,[DIY]
	add	ebp,eax
	mov	eax,[DINTENS]
	add	[INTENS],eax
	pop	cx
	dec	cx
	jnz	short @@Loop
@@Out:
	pop	ebp
    	pop	edi
	pop	ecx
	ret
	endp

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_GSImageHoriLine2
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Thu 14 Dec 1995
;;Modified
;;
;;Description	Same as ASM_ImageHoriLine1 but double pixel fill
;;
;;Inputs	eax = screen ptr
;;		edx = left vertex
;;		ebx = right vertex
;;
;;Returns
;;
;;Externals
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
	push	ecx
	push	edi
	push	ebp
	mov	ecx,[(vertex ebx).sx]	;;right vertex
	sar	ecx,17						;;PD 08Feb96
	mov	esi,edx
	mov	edi,[(vertex esi).sx]	;;left vertex
	sar	edi,17						;;PD 08Feb96
	sub	ecx,edi
	inc	ecx
	jle	@@Out
	add	edi,edi
	add	edi,eax			;;start scr. adr.

	mov	eax,[(vertex esi).intensity]
	mov	[INTENS],eax
	sub	eax,[(vertex ebx).intensity]
	neg	eax
	;;cdq							;;PD 12Feb96
	mov	edx,eax
	sar	edx,01fh
	idiv	ecx
	mov	[DINTENS],eax

	mov	eax,[(vertex esi).ix]	;;left vertex
	mov	[IX],eax
	sub	eax,[(vertex ebx).ix]	;;right vertex
	neg	eax
	;;cdq							;;PD 12Feb96
	mov	edx,eax
	sar	edx,01fh
	idiv	ecx
	mov	[DIX],eax		;;image x delta

	mov	eax,[(vertex esi).iy]	;;left vertex
	mov	[IY],eax
	sub	eax,[(vertex ebx).iy]	;;right vertex
	neg	eax
	;;cdq							;;PD 12Feb96
	mov	edx,eax
	sar	edx,01fh
	idiv	ecx
	mov	[DIY],eax		;;image y delta

	mov	esi,[(colourdata colour_data).imageptr]
	mov	edx,[IX]
	mov	ebp,[IY]

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width
	or	ecx,[(colourdata colour_data).imagexmask]

;;DeadCode PD 10Jun96 	ALIGN	16
@@Loop:
	push	cx
	mov	ebx,edx
	and	ebx,ecx
	shr	ebx,16
	mov	eax,ebp
	and	eax,[(colourdata colour_data).imageymask]
	mov	cl,[(colourdata colour_data).imageyshift]
	shr	eax,cl
	add	ebx,eax

	mov	eax,[INTENS]
	shr	eax,16	;;20					//PD 10Jun96
	mov	ch,[esi+ebx]
	mov	ah,ch
	and	ah,0F0h
	and	ch,00Fh
	add	al,ch
	cmp	al,00Fh
	jbe	short @@GotShade
	mov	al,00Fh
@@GotShade:
	xor	ebx,ebx
	or	al,ah
	mov	bl,al						;;PD 08Jan96
	mov	al,[Grey3DTable+ebx]				;;PD 08Jan96

	mov	ah,al
	stosw
	mov	eax,[DIX]
	add	edx,eax
	mov	eax,[DIY]
	add	ebp,eax
	mov	eax,[DINTENS]
	add	[INTENS],eax
	pop	cx
	dec	cx
	jnz	short @@Loop
@@Out:
	pop	ebp
	pop	edi
	pop	ecx
	ret
	endp

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_GSImageHoriLine4
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Thu 14 Dec 1995
;;Modified
;;
;;Description	Same as ASM_ImageHoriLine1 but quad pixel fill
;;
;;Inputs	eax = screen ptr
;;		edx = left vertex
;;		ebx = right vertex
;;
;;Returns
;;
;;Externals
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
	push	ecx
	push	edi
	push	ebp
	mov	ecx,[(vertex ebx).sx]	;;right vertex
	sar	ecx,18						;;PD 08Feb96
	mov	esi,edx
	mov	edi,[(vertex esi).sx]	;;left vertex
	sar	edi,18						;;PD 08Feb96
	sub	ecx,edi
	inc	ecx
	jle	@@Out
	shl	edi,2
	add	edi,eax			;;start scr. adr.

	mov	eax,[(vertex esi).intensity]
	mov	[INTENS],eax
	sub	eax,[(vertex ebx).intensity]
	neg	eax
	;;cdq							;;PD 12Feb96
	mov	edx,eax
	sar	edx,01fh
	idiv	ecx
	mov	[DINTENS],eax

	mov	eax,[(vertex esi).ix]	;;left vertex
	mov	[IX],eax
	sub	eax,[(vertex ebx).ix]	;;right vertex
	neg	eax
	;;cdq							;;PD 12Feb96
	mov	edx,eax
	sar	edx,01fh
	idiv	ecx
	mov	[DIX],eax		;;image x delta

	mov	eax,[(vertex esi).iy]	;;left vertex
	mov	[IY],eax
	sub	eax,[(vertex ebx).iy]	;;right vertex
	neg	eax
	;;cdq							;;PD 12Feb96
	mov	edx,eax
	sar	edx,01fh
	idiv	ecx
	mov	[DIY],eax		;;image y delta

	mov	esi,[(colourdata colour_data).imageptr]
	mov	edx,[IX]
	mov	ebp,[IY]

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width
	or	ecx,[(colourdata colour_data).imagexmask]

;;DeadCode PD 10Jun96 	ALIGN	16
@@Loop:
	push	cx
	mov	ebx,edx
	and	ebx,ecx
	shr	ebx,16
	mov	eax,ebp
	and	eax,[(colourdata colour_data).imageymask]
	mov	cl,[(colourdata colour_data).imageyshift]
	shr	eax,cl
	add	ebx,eax

	mov	eax,[INTENS]
	shr	eax,16	;;20					//PD 10Jun96
	mov	ch,[esi+ebx]
	mov	ah,ch
	and	ah,0F0h
	and	ch,00Fh
	add	al,ch
	cmp	al,00Fh
	jbe	short @@GotShade
	mov	al,00Fh
@@GotShade:
	xor	ebx,ebx
	or	al,ah
	mov	bl,al						;;PD 08Jan96
	mov	al,[Grey3DTable+ebx]				;;PD 08Jan96

	mov	ah,al
	stosw
	stosw
	mov	eax,[DIX]
	add	edx,eax
	mov	eax,[DIY]
	add	ebp,eax
	mov	eax,[DINTENS]
	add	[INTENS],eax
	pop	cx
	dec	cx
	jnz	short @@Loop
@@Out:
	pop	ebp
	pop	edi
	pop	ecx
	ret
	endp


;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_OImageHoriLine1
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Thu 14 Dec 1995
;;Modified
;;
;;Description
;;
;;Inputs	eax = screen ptr
;;		edx = left vertex
;;		ebx = right vertex
;;
;;Returns
;;
;;Externals
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
	push	ecx
	push	edi
	push	ebp
	mov	ecx,[(vertex ebx).sx]	;;right vertex
	sar	ecx,16						;;PD 08Feb96
	mov	esi,edx
	mov	edi,[(vertex esi).sx]	;;left vertex
	sar	edi,16						;;PD 08Feb96
	sub	ecx,edi
	inc	ecx
	jle	@@Out
	add	edi,eax			;;start scr. adr.

	mov	eax,[(vertex esi).ix]	;;left vertex
	mov	[IX],eax
	sub	eax,[(vertex ebx).ix]	;;right vertex
	neg	eax
	;;cdq							;;PD 12Feb96
	mov	edx,eax
	sar	edx,01fh
	idiv	ecx
	mov	[DIX],eax		;;image x delta

	mov	eax,[(vertex esi).iy]	;;left vertex
	mov	[IY],eax
	sub	eax,[(vertex ebx).iy]	;;right vertex
	neg	eax
	;;cdq							;;PD 12Feb96
	mov	edx,eax
	sar	edx,01fh
	idiv	ecx
	mov	[DIY],eax		;;image y delta

	mov	esi,[(colourdata colour_data).imageptr]
	mov	edx,[IX]
	mov	ebp,[IY]

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width
	or	ecx,[(colourdata colour_data).imagexmask]

;;DeadCode PD 10Jun96 	ALIGN	16
@@Loop:
	push	cx
	mov	ebx,edx
	and	ebx,ecx
	shr	ebx,16
	mov	eax,ebp
	and	eax,[(colourdata colour_data).imageymask]
	mov	cl,[(colourdata colour_data).imageyshift]
	shr	eax,cl
	add	ebx,eax
	mov	al,[esi+ebx]	;;opacity map byte

	mov	ah,al
	and	ah,0Fh		;;ah = intensity
	sub	al,ah		;;al = colour range
	mov	cl,[edi]
	and	cl,0Fh		;;cl = intensity of destination pixel
	add	ah,cl
	cmp	ah,10h
	jb	short @@IntensOK	;;clip to max. intensity
	mov	ah,0Fh
@@IntensOK:
	add	al,ah		;;restore original colour range (from opacity map)
	stosb
	mov	eax,[DIX]
	add	edx,eax
	mov	eax,[DIY]
	add	ebp,eax
	pop	cx
	dec	cx
	jnz	short @@Loop
@@Out:
	pop	ebp
	pop	edi
	pop	ecx
	ret
	endp

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_OMImageHoriLine1
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Thu 14 Dec 1995
;;Modified
;;
;;Description
;;
;;Inputs	eax = screen ptr
;;		edx = left vertex
;;		ebx = right vertex
;;
;;Returns
;;
;;Externals
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
	push	ecx
	push	edi
	push	ebp
	mov	ecx,[(vertex ebx).sx]	;;right vertex
	sar	ecx,16						;;PD 08Feb96
	mov	esi,edx
	mov	edi,[(vertex esi).sx]	;;left vertex
	sar	edi,16						;;PD 08Feb96
	sub	ecx,edi
	inc	ecx
	jle	@@Out
	add	edi,eax			;;start scr. adr.

	mov	eax,[(vertex esi).ix]	;;left vertex
	mov	[IX],eax
	sub	eax,[(vertex ebx).ix]	;;right vertex
	neg	eax
	;;cdq							;;PD 12Feb96
	mov	edx,eax
	sar	edx,01fh
	idiv	ecx
	mov	[DIX],eax		;;image x delta

	mov	eax,[(vertex esi).iy]	;;left vertex
	mov	[IY],eax
	sub	eax,[(vertex ebx).iy]	;;right vertex
	neg	eax
	;;cdq							;;PD 12Feb96
	mov	edx,eax
	sar	edx,01fh
	idiv	ecx
	mov	[DIY],eax		;;image y delta

	mov	esi,[(colourdata colour_data).imageptr]
	mov	edx,[IX]
	mov	ebp,[IY]

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width
	or	ecx,[(colourdata colour_data).imagexmask]

;;DeadCode PD 10Jun96 	ALIGN	16
@@Loop:
	push	cx
	mov	ebx,edx
	and	ebx,ecx
	shr	ebx,16
	mov	eax,ebp
	and	eax,[(colourdata colour_data).imageymask]
	mov	cl,[(colourdata colour_data).imageyshift]
	shr	eax,cl
	add	ebx,eax
	mov	al,[esi+ebx]	;;opacity map byte
	cmp	al,0FEh
	jz	short @@MaskByte

;;;TempCode PD 22Jan96 	mov	ah,[edi]
;;;TempCode PD 22Jan96 	and	ah,00Fh
;;;TempCode PD 22Jan96 	xor	al,ah

	mov	ah,al
	and	ah,0Fh		;;ah = intensity
	sub	al,ah		;;al = colour range
	mov	cl,[edi]
	and	cl,0Fh		;;cl = intensity of destination pixel
	add	ah,cl
	cmp	ah,10h
	jb	short @@IntensOK	;;clip to max. intensity
	mov	ah,0Fh
@@IntensOK:
	add	al,ah		;;restore original colour range (from opacity map)
	stosb
	mov	eax,[DIX]
	add	edx,eax
	mov	eax,[DIY]
	add	ebp,eax
	pop	cx
	dec	cx
	jnz	short @@Loop
@@Out:
	pop	ebp
	pop	edi
	pop	ecx
	ret

@@MaskByte:
	inc	edi
	mov	eax,[DIX]
	add	edx,eax
	mov	eax,[DIY]
	add	ebp,eax
	pop	cx
	dec	cx
	jnz	short @@Loop
	pop	ebp
	pop	edi
	pop	ecx
	ret
	endp

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_AliasMappingLo
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Mon 25 Mar 1996
;;Modified
;;
;;Description
;;
;;Inputs	eax = imagemap x
;;		edx = imagemap y
;;		ebx = dest ptr
;;Returns
;;
;;Externals
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
	push	eax
	push	ebx
	push	ecx
	push	esi
	push	edi
	push	ebp
	mov	edi,ebx
	shl	eax,16
	shl	edx,16
	mov	[ds:IX],eax
	mov	[ds:IY],edx
	mov	ebp,[(colourdata colour_data).aliastblptr]
	push	edi
;;Double horizontal rez first
	mov	cx,08h
@@L1:
	mov	esi,[(colourdata colour_data).imageptr]
	mov	ebx,[ds:IY]
	inc	[word ptr ds:IY+2]
	and	ebx,[(colourdata colour_data).imageymask]
	push	ecx
	mov	cl,[(colourdata colour_data).imageyshift]
	shr	ebx,cl
	add	esi,ebx

;;esi = ptr to correct image map scan line
	mov	cx,08h
	mov	eax,[ds:IX]
	mov	[ds:DIX],eax

@@L2:
	mov	eax,[ds:DIX]
	inc	[word ptr ds:DIX+2]
	and	eax,[(colourdata colour_data).imagexmask]
	shr	eax,16
	mov	ebx,esi
	add	ebx,eax
	xor	eax,eax
	mov	ax,[word ptr ds:ebx]
	mov	[byte ptr ds:edi],al
	inc	edi
	mov	al,[byte ptr ebp+eax]
	mov	[byte ptr ds:edi],al
	inc	edi
	dec	cx
	jnz	short @@L2
	pop	ecx
	add	edi,16
	dec	cx
	jnz	short @@L1

;;Now, double vertical rez
	pop	edi
	push	edi						;;PD 09Apr96
	add	edi,16
	mov	cx,07h						;;PD 09Apr96
@@L3:
	push	ecx
	mov	cx,10h
@@L4:
	xor	eax,eax
	mov	al,[byte ptr ds:edi-16]
	mov	ah,[byte ptr ds:edi+16]
	mov	al,[byte ptr ds:ebp+eax]
	mov	[byte ptr ds:edi],al
	inc	edi
	dec	cx
	jnz	short @@L4
	add	edi,16
	pop	ecx
	dec	cx
	jnz	short @@L3

;;Alias bottom line with the top line				;;PD 09Apr96
	pop	esi						;;PD 09Apr96
	mov	cx,10h						;;PD 09Apr96
@@L5:								;;PD 09Apr96
	xor	eax,eax						;;PD 09Apr96
	mov	al,[byte ptr ds:edi-16]				;;PD 09Apr96
	mov	ah,[byte ptr ds:esi]				;;PD 09Apr96
	mov	al,[byte ptr ds:ebp+eax]			;;PD 09Apr96
	mov	[byte ptr ds:edi],al				;;PD 09Apr96
	inc	edi						;;PD 09Apr96
	inc	esi						;;PD 09Apr96
	dec	cx						;;PD 09Apr96
	jnz	short @@L5					;;PD 09Apr96

	pop	ebp
	pop	edi
	pop	esi
	pop	ecx
	pop	ebx
	pop	eax
	ret
	endp

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_AliasMappingHi
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Mon 25 Mar 1996
;;Modified
;;
;;Description
;;
;;Inputs	eax = imagemap x
;;		edx = imagemap y
;;		ebx = dest ptr
;;
;;Returns
;;
;;Externals
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
	push	eax
	push	ebx
	push	ecx
	push	esi
	push	edi
	push	ebp
	mov	edi,ebx
	shl	eax,16
	shl	edx,16
	mov	[ds:IX],eax
	mov	[ds:IY],edx
	mov	ebp,[(colourdata colour_data).aliastblptr]
	push	edi
;;Horizontal rez x4 first

	mov	cx,08h
@@L1:
	mov	esi,[(colourdata colour_data).imageptr]
	mov	ebx,[ds:IY]
	inc	[word ptr ds:IY+2]
	and	ebx,[(colourdata colour_data).imageymask]
	push	ecx
	mov	cl,[(colourdata colour_data).imageyshift]
	shr	ebx,cl
	add	esi,ebx

;;esi = ptr to correct image map scan line
	mov	cx,08h
	mov	eax,[ds:IX]
	mov	[ds:DIX],eax

@@L2:
	mov	eax,[ds:DIX]
	inc	[word ptr ds:DIX+2]
	and	eax,[(colourdata colour_data).imagexmask]
	shr	eax,16
	mov	ebx,esi
	add	ebx,eax
	xor	eax,eax
	xor	edx,edx
	mov	ax,[word ptr ds:ebx]

;;1st dest colour is original

	mov	[byte ptr ds:edi],al

;;3rd dest colour is average of 1st and next source

	mov	dl,[byte ptr ebp+eax]
	mov	[byte ptr ds:edi+2],dl

;;2nd dest colour is average of 1st and 3rd

	mov	dh,al
	mov	al,[byte ptr ds:ebp+edx]
	mov	[byte ptr ds:edi+1],al

;;4th dest colour is average of 3rd and next source

	mov	dh,ah
	mov	al,[byte ptr ds:ebp+edx]
	mov	[byte ptr ds:edi+3],al

	add	edi,4

	dec	cx
	jnz	short @@L2
	pop	ecx
	add	edi,60h
	dec	cx
	jnz	short @@L1

	lea	edi,[ds:LclAilBuf]				;;PD 30Apr96
	mov	esi,[(colourdata colour_data).imageptr]
	mov	ebx,[ds:IY]
	and	ebx,[(colourdata colour_data).imageymask]
	mov	cl,[(colourdata colour_data).imageyshift]
	shr	ebx,cl
	add	esi,ebx

;;esi = ptr to correct image map scan line
	mov	cx,08h
	mov	eax,[ds:IX]
	mov	[ds:DIX],eax

@@L2b:
	mov	eax,[ds:DIX]
	inc	[word ptr ds:DIX+2]
	and	eax,[(colourdata colour_data).imagexmask]
	shr	eax,16
	mov	ebx,esi
	add	ebx,eax
	xor	eax,eax
	xor	edx,edx
	mov	ax,[word ptr ds:ebx]

;;1st dest colour is original

	mov	[byte ptr ds:edi],al

;;3rd dest colour is average of 1st and next source

	mov	dl,[byte ptr ebp+eax]
	mov	[byte ptr ds:edi+2],dl

;;2nd dest colour is average of 1st and 3rd

	mov	dh,al
	mov	al,[byte ptr ds:ebp+edx]
	mov	[byte ptr ds:edi+1],al

;;4th dest colour is average of 3rd and next source

	mov	dh,ah
	mov	al,[byte ptr ds:ebp+edx]
	mov	[byte ptr ds:edi+3],al

	add	edi,4

	dec	cx
	jnz	short @@L2b					;;PD 30Apr96

;;Now, 4x vertical rez

	pop	edi
;;DeadCode PD 30Apr96 	push	edi						;;PD 09Apr96
	add	edi,20h
	mov	cx,07h						;;PD 09Apr96
@@L3:
	push	ecx
	mov	cx,20h
@@L4:
	xor	eax,eax
	xor	edx,edx
	mov	al,[byte ptr ds:edi-20h]
	mov	ah,[byte ptr ds:edi+60h]

;;mid dest colour first

	mov	dl,[byte ptr ds:ebp+eax]
	mov	[byte ptr ds:edi+20h],dl

;;start dest colour is average of edi-20h and mid col

	mov	dh,al
	mov	al,[byte ptr ds:ebp+edx]
	mov	[byte ptr ds:edi],al

;;end dest colour is average of mid col and edi+60h

	mov	dh,ah
	mov	al,[byte ptr ds:ebp+edx]
	mov	[byte ptr ds:edi+40h],al

	inc	edi
	dec	cx
	jnz	short @@L4
	add	edi,60h
	pop	ecx
	dec	cx
	jnz	short @@L3

	lea	esi,[ds:LclAilBuf]				;;PD 30Apr96
	mov	cx,20h
@@L5:
	xor	eax,eax
	xor	edx,edx
	mov	al,[byte ptr ds:edi-20h]
	mov	ah,[byte ptr ds:esi]				;;PD 09Apr96
								;;PD 09Apr96
;;mid dest colour first						;;PD 09Apr96
								;;PD 09Apr96
	mov	dl,[byte ptr ds:ebp+eax]			;;PD 09Apr96
	mov	[byte ptr ds:edi+20h],dl			;;PD 09Apr96
								;;PD 09Apr96
;;start dest colour is average of edi-20h and mid col		;;PD 09Apr96
								;;PD 09Apr96
	mov	dh,al						;;PD 09Apr96
	mov	al,[byte ptr ds:ebp+edx]			;;PD 09Apr96
	mov	[byte ptr ds:edi],al				;;PD 09Apr96
								;;PD 09Apr96
;;end dest colour is average of mid col and edi+60h		;;PD 09Apr96
								;;PD 09Apr96
	mov	dh,ah						;;PD 09Apr96
	mov	al,[byte ptr ds:ebp+edx]			;;PD 09Apr96
	mov	[byte ptr ds:edi+40h],al			;;PD 09Apr96
								;;PD 09Apr96
	inc	edi						;;PD 09Apr96
	inc	esi						;;PD 09Apr96
	dec	cx
	jnz	short @@L5

	pop	ebp
	pop	edi
	pop	esi
	pop	ecx
	pop	ebx
	pop	eax
	ret
	endp

	ALIGN	2

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_TPlainHoriLine1
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Thu 21 Dec 1995
;;Modified
;;
;;Description
;;
;;Inputs
;;
;;Returns
;;
;;Externals
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
	push	ecx
	push	edi
	push	ebx
	mov	ecx,[(vertex ebx).sx]	;;right vertex
	sar	ecx,16						;;PD 08Feb96
	mov	esi,edx
	mov	edi,[(vertex esi).sx]	;;left vertex
	sar	edi,16						;;PD 08Feb96
	sub	ecx,edi
	inc	ecx
	jle	@@Out
	add	edi,eax			;;start scr. adr.

	xor	eax,eax
	mov	ah,[byte ptr (colourdata colour_data).col]
	mov	ebx,[(colourdata colour_data).aliastblptr]

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width
@@Loop:								;;PD 23Feb96
	mov	al,[byte ptr ds:edi]
	mov	al,[byte ptr ds:ebx+eax]
	mov	[byte ptr ds:edi],al				;;PD 23Feb96
	inc	edi						;;PD 23Feb96
	dec	cx						;;PD 23Feb96
	jnz	short @@Loop					;;PD 23Feb96
@@Out:
	pop	ebx
	pop	edi
	pop	ecx
	ret
	endp

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_TPlainHoriLine2
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Thu 4 Jan 1996
;;Modified
;;
;;Description
;;
;;Inputs
;;
;;Returns
;;
;;Externals
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
	push	ecx
	push	edi
	push	ebx
	mov	ecx,[(vertex ebx).sx]	;;right vertex
	sar	ecx,17						;;PD 08Feb96
	mov	esi,edx
	mov	edi,[(vertex esi).sx]	;;left vertex
	sar	edi,17						;;PD 08Feb96
	sub	ecx,edi
	inc	ecx
	jle	@@Out
	add	edi,edi
	add	edi,eax			;;start scr. adr.

	xor	eax,eax
	mov	ah,[byte ptr (colourdata colour_data).col]
	mov	ebx,[(colourdata colour_data).aliastblptr]

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width
;;eax = colour.b, colour.b, colour.b, colour.b
@@Loop:
	mov	al,[byte ptr ds:edi]
	mov	al,[byte ptr ds:ebx+eax]
	mov	[byte ptr ds:edi],al
	mov	[byte ptr ds:edi+1],al
	inc	edi
	inc	edi
	dec	cx
	jnz	short @@Loop
@@Out:
	pop	ebx
	pop	edi
	pop	ecx
	ret
	endp

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_TPlainHoriLine4
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Thu 4 Jan 1996
;;Modified
;;
;;Description
;;
;;Inputs
;;
;;Returns
;;
;;Externals
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
	push	ecx
	push	edi
	push	ebx
	mov	ecx,[(vertex ebx).sx]	;;right vertex
	sar	ecx,18						;;PD 08Feb96
	mov	esi,edx
	mov	edi,[(vertex esi).sx]	;;left vertex
	sar	edi,18						;;PD 08Feb96
	sub	ecx,edi
	inc	ecx
	jle	@@Out
	shl	edi,2
	add	edi,eax			;;start scr. adr.

	xor	eax,eax
	mov	ah,[byte ptr (colourdata colour_data).col]
	mov	ebx,[(colourdata colour_data).aliastblptr]

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width
;;eax = colour.b, colour.b, colour.b, colour.b
@@Loop:
	mov	al,[byte ptr ds:edi]
	mov	al,[byte ptr ds:ebx+eax]
	mov	[byte ptr ds:edi],al
	mov	[byte ptr ds:edi+1],al
	mov	[byte ptr ds:edi+2],al
	mov	[byte ptr ds:edi+3],al
	inc	edi
	inc	edi
	inc	edi
	inc	edi
	dec	cx
	jnz	short @@Loop
@@Out:
	pop	ebx
	pop	edi
	pop	ecx
	ret
	endp

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_TMImageHoriLine1
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Thu 14 Dec 1995
;;Modified
;;
;;Description
;;
;;Inputs	eax = screen ptr
;;		edx = left vertex
;;		ebx = right vertex
;;
;;Returns
;;
;;Externals
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
	push	ecx
	push	edi
	mov	ecx,[(vertex ebx).sx]	;;right vertex
	sar	ecx,16						;;PD 08Feb96
	mov	esi,edx
	mov	edi,[(vertex esi).sx]	;;left vertex
	sar	edi,16						;;PD 08Feb96
	sub	ecx,edi
	inc	ecx
	jle	@@Out
	add	edi,eax			;;start scr. adr.
	push	ebp
	mov	eax,[(vertex esi).ix]	;;left vertex
	mov	[IX],eax
	sub	eax,[(vertex ebx).ix]	;;right vertex
	neg	eax
	mov	edx,eax
	sar	edx,31
	idiv	ecx
	mov	[DIX],eax		;;image x delta
	mov	eax,[(vertex esi).iy]	;;left vertex
	mov	[IY],eax
	sub	eax,[(vertex ebx).iy]	;;right vertex
	neg	eax
	mov	edx,eax
	sar	edx,31
	idiv	ecx
	mov	[DIY],eax		;;image y delta
	or	ecx,[(colourdata colour_data).imagexmask]
	mov	esi,[(colourdata colour_data).imageptr]
	mov	edx,[IX]
	mov	ebp,[IY]

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width

;;DeadCode PD 10Jun96 	ALIGN	16
@@Loop:
	push	cx
	mov	eax,ebp
	mov	ebx,edx
	and	eax,[(colourdata colour_data).imageymask]
	and	ebx,ecx
	shr	ebx,16
	mov	cl,[(colourdata colour_data).imageyshift]
	shr	eax,cl
	add	ebx,eax
	xor	eax,eax
	mov	al,[esi+ebx]
	cmp	al,0FEh
	pop	cx
	jz	short @@MaskByte
	mov	ebx,[(colourdata colour_data).aliastblptr]
	mov	ah,[byte ptr ds:edi]
	mov	al,[byte ptr ds:ebx+eax]
	mov	[byte ptr ds:edi],al
	inc	edi
	add	edx,[dword ptr ds:DIX]
	add	ebp,[dword ptr ds:DIY]
	dec	cx
	jnz	short @@Loop
	pop	ebp
@@Out:
	pop	edi
	pop	ecx
	ret

@@MaskByte:
	inc	edi
	add	edx,[dword ptr ds:DIX]
	add	ebp,[dword ptr ds:DIY]
	dec	cx
	jnz	short @@Loop
	pop	ebp
	pop	edi
	pop	ecx
	ret
	endp


;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_SetTransparency
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Tue 2 Apr 1996
;;Modified
;;
;;Description
;;
;;Inputs
;;
;;Returns
;;
;;Externals
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
	mov	[ds:Trns3DEnabled],ax
	ret
	endp

	ENDS	_TEXT


ends
end
