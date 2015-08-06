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
	dummy1		DD	?				;;PD 06Jan97
	by              DD      ?
	dummy2		DD	?				;;PD 06Jan97
	bz              DD      ?
	dummy3		DD	?				;;PD 06Jan97
	sx              DD      ?
	dummy4		DD	?				;;PD 06Jan97
	sy              DD      ?
	dummy5		DD	?				;;PD 06Jan97
	ix              DD      ?
	dummy6		DD	?
	iy              DD      ?
	dummy7		DD	?
	intensity       DD      ?
	dummy8		DD	?
	dummy9		DD	?
;;DeadCode PD 06Jan97 	scalefactor     DW      ?
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
		DD	ASM_NDGHoriLine1_		;;GOURAUD - no dither
		DD	ASM_ImageHoriLine1_		;;IMAPPED
		DD	ASM_MImageHoriLine1_		;;IMAPPED_M
		DD	ASM_ImageHoriLine1_		;;IMAPPED_S
		DD	ASM_SImageHoriLine1_		;;IMAPPED_SH
		DD	ASM_NDSIHoriLine1_		;;IMAPPED_SH - no dither
		DD	ASM_OImageHoriLine1_		;;OMAPPED
		DD	ASM_OMImageHoriLine1_		;;OMAPPED_M

horiline_data2	DD	ASM_PlainHoriLine2_		;;PLAIN
		DD	ASM_GouraudHoriLine2_		;;GOURAUD
		DD	ASM_NDGHoriLine2_		;;GOURAUD - no dither
		DD	ASM_ImageHoriLine2_		;;IMAPPED
		DD	ASM_MImageHoriLine2_		;;IMAPPED_M
		DD	ASM_ImageHoriLine2_		;;IMAPPED_S
		DD	ASM_SImageHoriLine2_		;;IMAPPED_SH
		DD	ASM_NDSIHoriLine2_		;;IMAPPED_SH - no dither
		DD	ASM_OImageHoriLine1_		;;OMAPPED
		DD	ASM_OMImageHoriLine1_		;;OMAPPED_M

horiline_data4	DD	ASM_PlainHoriLine4_		;;PLAIN
		DD	ASM_GouraudHoriLine4_		;;GOURAUD
		DD	ASM_NDGHoriLine4_		;;GOURAUD - no dither
		DD	ASM_ImageHoriLine4_		;;IMAPPED
		DD	ASM_MImageHoriLine4_		;;IMAPPED_M
		DD	ASM_ImageHoriLine4_		;;IMAPPED_S
		DD	ASM_SImageHoriLine4_		;;IMAPPED_SH
		DD	ASM_NDSIHoriLine4_		;;IMAPPED_SH - no dither
		DD	ASM_OImageHoriLine1_		;;OMAPPED
		DD	ASM_OMImageHoriLine1_		;;OMAPPED_M

;;Colour indirected 3D versions of all the above

Ghoriline_data1	DD	ASM_GPlainHoriLine1_		;;PLAIN
		DD	ASM_GGouraudHoriLine1_		;;GOURAUD
		DD	ASM_GGouraudHoriLine1_			;;PD 07Dec96
		DD	ASM_GImageHoriLine1_		;;IMAPPED
		DD	ASM_GMImageHoriLine1_		;;IMAPPED_M//PD 03Apr96
		DD	ASM_GImageHoriLine1_		;;IMAPPED_S
		DD	ASM_GSImageHoriLine1_		;;IMAPPED_SH
		DD	ASM_GSImageHoriLine1_			;;PD 07Dec96
		DD	ASM_OImageHoriLine1_		;;OMAPPED
		DD	ASM_OMImageHoriLine1_		;;OMAPPED_M

Ghoriline_data2	DD	ASM_GPlainHoriLine2_		;;PLAIN
		DD	ASM_GGouraudHoriLine2_		;;GOURAUD
		DD	ASM_GGouraudHoriLine2_			;;PD 07Dec96
		DD	ASM_GImageHoriLine2_		;;IMAPPED
		DD	ASM_GMImageHoriLine2_		;;IMAPPED_M//PD 03Apr96
		DD	ASM_GImageHoriLine2_		;;IMAPPED_S
		DD	ASM_GSImageHoriLine2_		;;IMAPPED_SH
		DD	ASM_GSImageHoriLine2_			;;PD 07Dec96
		DD	ASM_OImageHoriLine1_		;;OMAPPED
		DD	ASM_OMImageHoriLine1_		;;OMAPPED_M

Ghoriline_data4	DD	ASM_GPlainHoriLine4_		;;PLAIN
		DD	ASM_GGouraudHoriLine4_		;;GOURAUD
		DD	ASM_GGouraudHoriLine4_			;;PD 07Dec96
		DD	ASM_GImageHoriLine4_		;;IMAPPED
		DD	ASM_GMImageHoriLine4_		;;IMAPPED_M//PD 03Apr96
		DD	ASM_GImageHoriLine4_		;;IMAPPED_S
		DD	ASM_GSImageHoriLine4_		;;IMAPPED_SH
		DD	ASM_GSImageHoriLine4_			;;PD 07Dec96
		DD	ASM_OImageHoriLine1_		;;OMAPPED
		DD	ASM_OMImageHoriLine1_		;;OMAPPED_M

;;Transparency shite....

Thoriline_data1	DD	ASM_TPlainHoriLine1_		;;PLAIN	//PD 02Apr96
		DD	ASM_GouraudHoriLine1_		;;GOURAUD
		DD	ASM_GouraudHoriLine1_			;;PD 07Dec96
		DD	ASM_ImageHoriLine1_		;;IMAPPED
		DD	ASM_TMImageHoriLine1_		;;IMAPPED_M
		DD	ASM_ImageHoriLine1_		;;IMAPPED_S
		DD	ASM_SImageHoriLine1_		;;IMAPPED_SH
		DD	ASM_SImageHoriLine1_			;;PD 07Dec96
		DD	ASM_OImageHoriLine1_		;;OMAPPED
		DD	ASM_OMImageHoriLine1_		;;OMAPPED_M

Thoriline_data2	DD	ASM_TPlainHoriLine2_		;;PLAIN	//PD 02Apr96
		DD	ASM_GouraudHoriLine2_		;;GOURAUD
		DD	ASM_GouraudHoriLine2_			;;PD 07Dec96
		DD	ASM_ImageHoriLine2_		;;IMAPPED
		DD	ASM_TMImageHoriLine2_		;;IMAPPED_M
		DD	ASM_ImageHoriLine2_		;;IMAPPED_S
		DD	ASM_SImageHoriLine2_		;;IMAPPED_SH
		DD	ASM_SImageHoriLine2_			;;PD 07Dec96
		DD	ASM_OImageHoriLine1_		;;OMAPPED
		DD	ASM_OMImageHoriLine1_		;;OMAPPED_M

Thoriline_data4	DD	ASM_TPlainHoriLine4_		;;PLAIN	//PD 02Apr96
		DD	ASM_GouraudHoriLine4_		;;GOURAUD
		DD	ASM_GouraudHoriLine4_			;;PD 07Dec96
		DD	ASM_ImageHoriLine4_		;;IMAPPED
		DD	ASM_TMImageHoriLine4_		;;IMAPPED_M
		DD	ASM_ImageHoriLine4_		;;IMAPPED_S
		DD	ASM_SImageHoriLine4_		;;IMAPPED_SH
		DD	ASM_SImageHoriLine4_			;;PD 07Dec96
		DD	ASM_OImageHoriLine1_		;;OMAPPED
		DD	ASM_OMImageHoriLine1_		;;OMAPPED_M


;;More transparency shite, but aliastable is looked at the opposite way round...
;;  (At this point, the 75% alias table will have been loaded)
;;  This cheat is for a 25% bias....

TIhorline_data1	DD	ASM_TIPlainHoriLine1_		;;PLAIN
		DD	ASM_GouraudHoriLine1_		;;GOURAUD
		DD	ASM_GouraudHoriLine1_
		DD	ASM_ImageHoriLine1_		;;IMAPPED
		DD	ASM_TIMImageHoriLine1_		;;IMAPPED_M
		DD	ASM_ImageHoriLine1_		;;IMAPPED_S
		DD	ASM_SImageHoriLine1_		;;IMAPPED_SH
		DD	ASM_SImageHoriLine1_
		DD	ASM_OImageHoriLine1_		;;OMAPPED
		DD	ASM_OMImageHoriLine1_		;;OMAPPED_M

TIhorline_data2	DD	ASM_TIPlainHoriLine2_		;;PLAIN
		DD	ASM_GouraudHoriLine2_		;;GOURAUD
		DD	ASM_GouraudHoriLine2_
		DD	ASM_ImageHoriLine2_		;;IMAPPED
		DD	ASM_TIMImageHoriLine2_		;;IMAPPED_M
		DD	ASM_ImageHoriLine2_		;;IMAPPED_S
		DD	ASM_SImageHoriLine2_		;;IMAPPED_SH
		DD	ASM_SImageHoriLine2_
		DD	ASM_OImageHoriLine1_		;;OMAPPED
		DD	ASM_OMImageHoriLine1_		;;OMAPPED_M

TIhorline_data4	DD	ASM_TIPlainHoriLine4_		;;PLAIN
		DD	ASM_GouraudHoriLine4_		;;GOURAUD
		DD	ASM_GouraudHoriLine4_
		DD	ASM_ImageHoriLine4_		;;IMAPPED
		DD	ASM_TIMImageHoriLine4_		;;IMAPPED_M
		DD	ASM_ImageHoriLine4_		;;IMAPPED_S
		DD	ASM_SImageHoriLine4_		;;IMAPPED_SH
		DD	ASM_SImageHoriLine4_
		DD	ASM_OImageHoriLine1_		;;OMAPPED
		DD	ASM_OMImageHoriLine1_		;;OMAPPED_M


;;-----------------------------------------------------------------------------
;;-----------------------------------------------------------------------------
;;			Fade data tables
;;-----------------------------------------------------------------------------
;;-----------------------------------------------------------------------------


	public	_FadeData2					;;PD 28Aug96
_FadeData2:							;;PD 28Aug96
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

	ALIGN	2

;;-----------------------------------------------------------------------------
;;-----------------------------------------------------------------------------
;;			General routines
;;-----------------------------------------------------------------------------
;;-----------------------------------------------------------------------------

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
	push	ebp						;;RJS 17Jun97
	lea	ebx,[horiline_data1]
	lea	esi,[Ghoriline_data1]
	lea	edi,[Thoriline_data1]				;;PD 02Apr96
	lea	ebp,[TIhorline_data1]				;;RJS 17Jun97
	cmp	[PixelWidth],1
	jz	short @@OK
	lea	ebx,[horiline_data2]
	lea	esi,[Ghoriline_data2]
	lea	edi,[Thoriline_data2]				;;PD 02Apr96
	lea	ebp,[TIhorline_data2]				;;RJS 17Jun97
	cmp	[PixelWidth],2
	jz	short @@OK
	lea	ebx,[horiline_data4]
	lea	esi,[Ghoriline_data4]
	lea	edi,[Thoriline_data4]				;;PD 02Apr96
	lea	ebp,[TIhorline_data4]				;;RJS 17Jun97
@@OK:
	cmp	[Trns3DEnabled],0
	jz	short @@Don2					;;PD 02Apr96
	cmp	[Trns3DEnabled],50				;;RJS 17Jun97
	jge	short @@Don3					;;RJS 17Jun97
	mov	ebx,ebp						;;RJS 17Jun97
	jmp	short @@Don2					;;RJS 17Jun97
@@Don3: mov	ebx,edi						;;PD 02Apr96
@@Don2:	cmp	[Grey3DEnabled],0
	jz	short @@Done
	mov	ebx,esi
@@Done:	mov	eax,[ebx+4*eax]					;;PD 02Apr96
	pop	ebp						;;PD 02Apr96
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

	mov	[(colourdata colour_data).aliastblptr],eax
	mov	eax,offset ShadeData2
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
	push	ebx
	push	ecx
	push	edx
	push	esi						;;PD 10Jul96
	push	edi
	mov	ecx,[(vertex ebx).sx]	;;right vertex
	mov	edi,[(vertex edx).sx]	;;left vertex
	inc	ecx
	sub	ecx,edi
	push	eax
	jle	short @@Out
	add	edi,eax			;;start scr. adr.
	mov	esi,[(colourdata colour_data).aliastblptr]
	xor	edx,edx
	mov	dh,[byte ptr (colourdata colour_data).col]
;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width
;;eax = colour.b, colour.b, colour.b, colour.b
@@Loop:								;;PD 23Feb96
	mov	dl,[byte ptr ds:edi]
	mov	al,[byte ptr ds:esi+edx]
	inc	edi						;;PD 23Feb96
	dec	cx						;;PD 23Feb96
	mov	[byte ptr edi-1],al				;;PD 23Feb96
	jnz	short @@Loop					;;PD 23Feb96
@@Out:
	pop	eax
	pop	edi
	pop	esi
	pop	edx						;;PD 10Jul96
	pop	ecx
	pop	ebx
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
	mov	edi,[(vertex edx).sx]	;;left vertex
	sar	ecx,16						;;PD 08Feb96
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
	mov	edi,[(vertex edx).sx]	;;left vertex
	add	ecx,20000h
	sar	edi,17
	sar	ecx,17
	add	eax,edi
	sub	ecx,edi
	jle	@@Out
	add	edi,eax
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
	push	edi
	mov	edi,[(vertex edx).sx]	;;left vertex
	push	ecx
	sar	edi,18
	mov	ecx,[(vertex ebx).sx]	;;right vertex
	add	eax,edi
	add	ecx,40000h
	add	eax,edi
	sar	ecx,18
	add	eax,edi
	sub	ecx,edi
	jle	@@Out
	add	edi,eax			;;start scr. adr.
	mov	eax,[(colourdata colour_data).col]

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width
;;eax = colour.b, colour.b, colour.b, colour.b
	rep	stosd
@@Out:
	pop	ecx
	pop	edi
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
;;------------------------------------------------------------------------------
	push	eax
	push	ecx
	push	edx
	push	esi
	push	edi
	push	ebp
	mov	esi,edx
	mov	ecx,[(vertex ebx).sx]	;;right vertex
	mov	edi,[(vertex esi).sx]	;;left vertex
	sar	ecx,16						;;PD 08Feb96
	sar	edi,16						;;PD 08Feb96
	sub	ecx,edi
	inc	ecx
	jle	@@Out
	add	edi,eax			;;start scr. adr.
	mov	ebp,[(vertex esi).sy]
	mov	eax,[(vertex esi).intensity]
	add	ebp,1024
	mov	[INTENS],eax
	add	ebp,[(colourdata colour_data).aliastblptr]
	sub	eax,[(vertex ebx).intensity]
	mov	bp,[word ptr ds:ebp]
	neg	eax
	mov	[word ptr ds:JITTER],bp
	mov	edx,eax
	sar	edx,01fh
	idiv	ecx
	dec	edi
	mov	[DINTENS],eax
@@Loop:
	xor	eax,eax
	mov	edx,[dword ptr ds:INTENS]
	mov	ah,[byte ptr (colourdata colour_data).col]
	movzx	ebp,[word ptr ds:JITTER]
	shr	ax,4
 	add	edx,ebp
	inc	edi
	shr	edx,16
	add	bp,9136h
	cmp	edx,0fh						;;PD 19Dec96
	jbe	short @@Okay					;;PD 19Dec96
       	mov	edx,0fh						;;PD 19Dec96
@@Okay:								;;PD 19Dec96
	or	ax,dx
	ror	bp,3
	mov	al,[byte ptr ds:ShadeData2+eax]
	mov	edx,[dword ptr ds:DINTENS]
	mov	[byte ptr ds:edi],al
	add	[dword ptr ds:INTENS],edx
	dec	ecx
	mov	[word ptr ds:JITTER],bp
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
;;------------------------------------------------------------------------------
	push	eax
	push	ecx
	push	edx
	push	esi
	push	edi
	push	ebp
	mov	esi,edx
	mov	ecx,[(vertex ebx).sx]	;;right vertex
	mov	edi,[(vertex esi).sx]	;;left vertex
	add	ecx,20000h
	sar	edi,17
	sar	ecx,17
	mov	ebp,[(vertex esi).sy]
	add	eax,edi
	sub	ecx,edi
	jle	@@Out
	add	edi,eax			;;start scr. adr.
	mov	eax,[(vertex esi).intensity]
	add	ebp,1024
	mov	[INTENS],eax
	add	ebp,[(colourdata colour_data).aliastblptr]
	mov	edx,[(vertex ebx).intensity]
	mov	ebp,[dword ptr ds:ebp]
	sub	edx,eax
	and	ebp,0FFFFh
	mov	eax,edx
	mov	[dword ptr JITTER],ebp
	sar	edx,01fh
	idiv	ecx
	sub	edi,2
	mov	[DINTENS],eax
@@Loop:
	xor	eax,eax
	mov	edx,[INTENS]
	mov	ebp,[dword ptr JITTER]
	mov	ah,[byte ptr (colourdata colour_data).col]
	and	ebp,0FFFFh
	shr	eax,4
 	add	edx,ebp
	add	edi,2
	shr	edx,16
	add	bp,9136h
	cmp	edx,0fh
	jbe	short @@Okay
       	mov	edx,0fh
@@Okay:
	ror	bp,3
	or	eax,edx
	mov	edx,[DINTENS]
	mov	[dword ptr JITTER],ebp
	mov	al,[byte ptr ShadeData2+eax]
	add	[INTENS],edx
	mov	ah,al
	dec	ecx
	mov	[word ptr edi],ax
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
;;------------------------------------------------------------------------------
	push	eax
	push	ecx
	push	edx
	push	esi
	push	edi
	push	ebp
	mov	esi,edx
	mov	ecx,[(vertex ebx).sx]	;;right vertex
	mov	edi,[(vertex esi).sx]	;;left vertex
	add	ecx,40000h
	sar	edi,18
	sar	ecx,18
	add	eax,edi
	mov	ebp,[(vertex esi).sy]
	add	eax,edi
	sub	ecx,edi
	jle	@@Out
	add	edi,edi
	add	edi,eax			;;start scr. adr.
	mov	eax,[(vertex esi).intensity]
	add	ebp,1024
	mov	[INTENS],eax
	add	ebp,[(colourdata colour_data).aliastblptr]
	mov	edx,[(vertex ebx).intensity]
	mov	ebp,[dword ptr ds:ebp]
	sub	edx,eax
	and	ebp,0FFFFh
	mov	eax,edx
	mov	[dword ptr JITTER],ebp
	sar	edx,01fh
	idiv	ecx
	sub	edi,4
	mov	[DINTENS],eax
@@Loop:
	xor	eax,eax
	mov	edx,[INTENS]
	mov	ebp,[dword ptr JITTER]
	mov	ah,[byte ptr (colourdata colour_data).col]
	and	ebp,0FFFFh
	shr	eax,4
 	add	edx,ebp
	add	edi,4
	shr	edx,16
	add	bp,9136h
	cmp	edx,0Fh
	jbe	short @@OKay
	mov	edx,0Fh
@@OKay:
	ror	bp,3
	or	eax,edx
	mov	edx,[DINTENS]
	mov	[dword ptr JITTER],ebp
	mov	al,[byte ptr ShadeData2+eax]
	add	[INTENS],edx
	mov	ah,al
	dec	ecx
	mov	[word ptr edi],ax
	mov	[word ptr edi+2],ax
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
	mov	edi,[(vertex edx).sx]	;;left vertex
	add	ecx,10000h
	sar	edi,16
	sar	ecx,16
	mov	esi,edx
	sub	ecx,edi
	jle	@@Out
	add	edi,eax			;;start scr. adr.
	mov	eax,[(vertex esi).ix]	;;left vertex
	mov	edx,[(vertex ebx).ix]	;;right vertex
	mov	[IX],eax
	sub	edx,eax
	mov	ebp,[(vertex esi).iy]
	mov	eax,edx
	sar	edx,31
	idiv	ecx
	mov	[IY],ebp
	mov	[DIX],eax		;;image x delta
	mov	edx,[(vertex ebx).iy]	;;right vertex
	mov	eax,ebp
	sub	edx,ebp
	jz	@@Horizontal
	cmp	edx,0fffeff9ah
	jl	short @@NotHorizontal
	cmp	edx,000010066h
	jle	@@Horizontal
@@NotHorizontal:
	mov	eax,edx
	mov	esi,[(colourdata colour_data).imageptr]
	sar	edx,31
	idiv	ecx
	dec	edi
	mov	[DIY],eax					;;image y delta
	mov	edx,[IX]

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width

@@Loop:
	push	ecx
	mov	ebx,[(colourdata colour_data).imagexmask]
	mov	eax,[DIX]
	and	ebx,edx
	add	edx,eax
	mov	ecx,[(colourdata colour_data).imageymask]
	mov	eax,ebp
	mov	cl,[(colourdata colour_data).imageyshift]
	shr	ebx,16
	and	eax,ecx
	add	ebx,esi
	shr	eax,cl
	inc	edi
	mov	ecx,[DIY]
	add	ebx,eax
	add	ebp,ecx
	pop	ecx
	dec	ecx
	mov	eax,[dword ptr ebx]
	mov	[byte ptr edi],al
	jnz	short @@Loop
@@Out:
	pop	ebp
	pop	edi
	pop	ecx
	ret
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


@@Horizontal:
	mov	esi,[(colourdata colour_data).imageptr]
	or	ecx,[(colourdata colour_data).imagexmask]
	mov	edx,[IX]
	push	ecx
	and	ebp,[(colourdata colour_data).imageymask]
	mov	cl,[(colourdata colour_data).imageyshift]
	shr	ebp,cl
	pop	ecx
	add	esi,ebp
	dec	edi
	mov	ebp,[DIX]
@@Loop2:
	mov	ebx,edx
	add	edx,ebp
	and	ebx,ecx
	inc	edi
	shr	ebx,16
	dec	cx
	mov	bl,[byte ptr esi+ebx]
	mov	[byte ptr edi],bl
	jnz	short @@Loop2
	pop	ebp
	pop	edi
	pop	ecx
	ret
	endp


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
	mov	edi,[(vertex edx).sx]	;;left vertex
	add	ecx,20000h
	sar	edi,17						;;PD 08Feb96
	sar	ecx,17						;;PD 08Feb96
	mov	esi,edx
	sub	ecx,edi
;;DeadCode PD 20Nov96 	inc	ecx
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

	sub	edi,2
;;DeadCode PD 10Jun96 	ALIGN	16
@@Loop:
	push	ecx
	mov	ebx,edx
	mov	eax,ebp
	and	ebx,ecx
	add	edi,2
	shr	ebx,16
	and	eax,[(colourdata colour_data).imageymask]
	mov	cl,[(colourdata colour_data).imageyshift]
	add	ebp,[dword ptr ds:DIY]
	shr	eax,cl
	add	ebx,eax
	mov	al,[esi+ebx]
	add	edx,[dword ptr ds:DIX]
	mov	ah,al
	pop	ecx
	mov	[word ptr ds:edi],ax
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

	sub	edi,4
;;DeadCode PD 10Jun96 	ALIGN	16
@@Loop:
	push	ecx
	mov	ebx,edx
	mov	eax,ebp
	and	ebx,ecx
	add	edi,4
	shr	ebx,16
	and	eax,[(colourdata colour_data).imageymask]
	mov	cl,[(colourdata colour_data).imageyshift]
	add	ebp,[dword ptr ds:DIY]
	shr	eax,cl
	add	ebx,eax
	mov	al,[esi+ebx]
	mov	ah,al
	add	edx,[dword ptr ds:DIX]
	mov	[word ptr ds:edi],ax
	pop	ecx
	mov	[word ptr ds:edi+2],ax
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
;;;;DeadCode ARM 24Jun96 	DW	0,0,0,0,0,0,0
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
	mov	esi,edx
	mov	edi,[(vertex edx).sx]	;;left vertex
	add	ecx,10000h
	sar	edi,16						;;PD 08Feb96
	sar	ecx,16						;;PD 08Feb96
	sub	ecx,edi
	jle	@@Out
	push	ebp
	add	edi,eax			;;start scr. adr.
	mov	eax,[(vertex esi).ix]	;;left vertex
	mov	edx,[(vertex ebx).ix]	;;right vertex
	mov	[IX],eax
	sub	edx,eax
	mov	eax,edx
	sar	edx,31
	idiv	ecx
	mov	[DIX],eax		;;image x delta
	mov	ebp,[(vertex esi).iy]	;;left vertex
	mov	edx,[(vertex ebx).iy]	;;right vertex
	mov	eax,ebp
	mov	[IY],ebp
	sub	edx,eax
	jz	@@Horizontal
	cmp	edx,0fffeff9ah
	jl	short @@NotHorizontal
	cmp	edx,000010066h
	jle	@@Horizontal
@@NotHorizontal:
	mov	eax,edx
	sar	edx,31
	idiv	ecx
	or	ecx,[(colourdata colour_data).imagexmask]
	mov	esi,[(colourdata colour_data).imageptr]
	mov	[DIY],eax		;;image y delta
	mov	edx,[IX]
	mov	ebp,[IY]

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width

	dec	edi
;;DeadCode PD 10Jun96 	ALIGN	16
@@Loop:
	push	ecx
	mov	eax,ebp
	mov	ebx,edx
	and	eax,[(colourdata colour_data).imageymask]
	and	ebx,ecx
	add	edx,[dword ptr ds:DIX]
	shr	ebx,16
	mov	cl,[(colourdata colour_data).imageyshift]
	add	ebp,[dword ptr ds:DIY]
	shr	eax,cl
	inc	edi
	add	ebx,eax
	mov	al,[esi+ebx]
	cmp	al,0FEh
	pop	ecx
	jz	short @@MaskByte
	mov	[byte ptr ds:edi],al
@@MaskByte:
	dec	cx
	jnz	short @@Loop
	pop	ebp
@@Out:
	pop	edi
	pop	ecx
	ret
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
@@Horizontal:
	mov	esi,[(colourdata colour_data).imageptr]
	mov	edx,[IX]
	or	ecx,[(colourdata colour_data).imagexmask]
	push	ecx
	and	ebp,[(colourdata ds:colour_data).imageymask]
	mov	cl,[(colourdata ds:colour_data).imageyshift]
	shr	ebp,cl
	pop	ecx
	add	esi,ebp
	dec	edi
	mov	ebp,[dword ptr ds:DIX]
@@Loop2:
	mov	ebx,edx
	add	edx,ebp
	and	ebx,ecx
	inc	edi
	shr	ebx,16
	mov	bl,[byte ptr ds:esi+ebx]
	cmp	bl,0feh
	jz	short @@mb
	mov	[byte ptr ds:edi],bl
@@mb:
	dec	cx
	jnz	short @@Loop2
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
;;DeadCode JIM 04Dec96 	push	ebp
	mov	ecx,[(vertex ebx).sx]	;;right vertex
	sar	ecx,17						;;PD 08Feb96
	mov	esi,edx
	mov	edi,[(vertex esi).sx]	;;left vertex
	sar	edi,17
	sub	ecx,edi
	inc	ecx
	jle	@@Out
	add	edi,edi
 	push	ebp
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
	sub	edi,2
@@Loop:
	push	ecx
	mov	eax,ebp
	mov	ebx,edx
	and	eax,[(colourdata colour_data).imageymask]
	and	ebx,ecx
	add	edx,[dword ptr ds:DIX]
	shr	ebx,16
	mov	cl,[(colourdata colour_data).imageyshift]
	add	ebp,[dword ptr ds:DIY]
	shr	eax,cl
	add	edi,2
	add	ebx,eax
	mov	al,[esi+ebx]
	cmp	al,0FEh
	pop	ecx
	jz	short @@MaskByte
	mov	ah,al
	mov	[word ptr ds:edi],ax
@@MaskByte:
	dec	cx
	jnz	short @@Loop
	pop	ebp						;;JIM 04Dec96
@@Out:								;;JIM 04Dec96
	pop	edi						;;JIM 04Dec96
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

	sub	edi,4

;;DeadCode PD 10Jun96 	ALIGN	16
@@Loop:
	push	ecx
	mov	eax,ebp
	mov	ebx,edx
	and	eax,[(colourdata colour_data).imageymask]
	and	ebx,ecx
	add	edx,[dword ptr ds:DIX]
	shr	ebx,16
	mov	cl,[(colourdata colour_data).imageyshift]
	add	ebp,[dword ptr ds:DIY]
	shr	eax,cl
	add	edi,4
	add	ebx,eax
	mov	al,[esi+ebx]
	cmp	al,0FEh
	pop	ecx
	jz	short @@MaskByte
	mov	ah,al
	mov	[word ptr ds:edi],ax
	mov	[word ptr ds:edi+2],ax
@@MaskByte:
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
	add	edi,eax			;;start scr. adr.
	add	ebp,1024
	mov	eax,[(vertex esi).intensity]
	add	ebp,[(colourdata colour_data).aliastblptr]
	mov	[INTENS],eax
	mov	bp,[word ptr ds:ebp]				;;PD 16May96
	sub	eax,[(vertex ebx).intensity]
	mov	[word ptr ds:JITTER],bp				;;PD 16May96
	mov	edx,eax
	xor	ax,ax
	test	eax,eax
	jz	@@Fast
	neg	edx
	mov	eax,edx
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
	dec	edi
@@Loop:
	push	ecx
	mov	ebx,edx
	mov	eax,ebp
	and	ebx,ecx
	add	ebp,[dword ptr ds:DIY]
	shr	ebx,16
	and	eax,[(colourdata colour_data).imageymask]
	mov	cl,[(colourdata colour_data).imageyshift]
	inc	edi
	shr	eax,cl
	add	edx,[dword ptr ds:DIX]
	add	ebx,eax
	mov	eax,[dword ptr ds:INTENS]
	xor	cx,cx
 	add	eax,[dword ptr ds:JITTER]
 	mov	ch,[byte ptr ds:esi+ebx]
  	shr	eax,16
 	shr	cx,4
	cmp	eax,0Fh
	mov	ebx,[dword ptr ds:DINTENS]
	jbe	short @@OKay
	mov	eax,0Fh
@@OKay:
 	or	ax,cx
	add	[dword ptr ds:INTENS],ebx
 	mov	al,[ds:ShadeData2+eax]
	mov	bx,[word ptr ds:JITTER]
	pop	ecx
	add	bx,9136h
	ror	bx,3
 	mov	[byte ptr ds:edi],al
	dec	cx
	mov	[word ptr ds:JITTER],bx
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
	dec	edi
@@FLoop:
	push	ecx
	mov	ebx,edx
	mov	eax,ebp
	and	ebx,ecx
	add	ebp,[dword ptr ds:DIY]
	shr	ebx,16
	and	eax,[(colourdata colour_data).imageymask]
	mov	cl,[(colourdata colour_data).imageyshift]
	inc	edi
	shr	eax,cl
	add	edx,[dword ptr ds:DIX]
	add	ebx,eax
	mov	eax,[INTENS]
	xor	cx,cx
 	add	eax,[dword ptr ds:JITTER]
	mov	ch,[byte ptr ds:esi+ebx]
	shr	eax,16
	shr	cx,4
	cmp	eax,0Fh
	mov	bx,[word ptr ds:JITTER]
	jbe	short @@OKay2
	mov	eax,0Fh
@@OKay2:
	add	bx,9136h
	or	ax,cx
	ror	bx,3
	mov	al,[ds:ShadeData2+eax]
	mov	[word ptr ds:JITTER],bx
	mov	ah,al
	pop	ecx
	mov	[byte ptr ds:edi],al
	dec	cx
	jnz	short @@FLoop
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
	add	edi,eax			;;start scr. adr.
	add	ebp,1024
	mov	eax,[(vertex esi).intensity]
	add	ebp,[(colourdata colour_data).aliastblptr]
	mov	[INTENS],eax
	mov	bp,[word ptr ds:ebp]				;;PD 16May96
	sub	eax,[(vertex ebx).intensity]
	mov	[word ptr ds:JITTER],bp				;;PD 16May96
	mov	edx,eax
	xor	ax,ax
	test	eax,eax
	jz	@@Fast
	neg	edx
	mov	eax,edx
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
	sub	edi,2
@@Loop:
	push	ecx
	mov	ebx,edx
	mov	eax,ebp
	and	ebx,ecx
	add	ebp,[dword ptr ds:DIY]
	shr	ebx,16
	and	eax,[(colourdata colour_data).imageymask]
	mov	cl,[(colourdata colour_data).imageyshift]
	inc	edi
	shr	eax,cl
	add	edx,[dword ptr ds:DIX]
	inc	edi
	add	ebx,eax
	mov	eax,[dword ptr ds:INTENS]
	xor	cx,cx
 	add	eax,[dword ptr ds:JITTER]
 	mov	ch,[byte ptr ds:esi+ebx]
  	shr	eax,16
 	shr	cx,4
	cmp	eax,0Fh
	mov	ebx,[dword ptr ds:DINTENS]
	jbe	short @@OKay
	mov	eax,0Fh
@@OKay:
 	or	ax,cx
	add	[dword ptr ds:INTENS],ebx
 	mov	al,[ds:ShadeData2+eax]
	mov	bx,[word ptr ds:JITTER]
	pop	ecx
	add	bx,9136h
 	mov	ah,al
	ror	bx,3
 	mov	[word ptr ds:edi],ax
	dec	cx
	mov	[word ptr ds:JITTER],bx
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
	sub	edi,2
@@FLoop:
	push	ecx
	mov	ebx,edx
	mov	eax,ebp
	and	ebx,ecx
	add	ebp,[dword ptr ds:DIY]
	shr	ebx,16
	and	eax,[(colourdata colour_data).imageymask]
	mov	cl,[(colourdata colour_data).imageyshift]
	add	edi,2
	shr	eax,cl
	add	edx,[dword ptr ds:DIX]
	add	ebx,eax
	mov	eax,[INTENS]
	xor	cx,cx
 	add	eax,[dword ptr ds:JITTER]
	mov	ch,[byte ptr ds:esi+ebx]
	shr	eax,16
	shr	cx,4
	cmp	eax,0Fh
	mov	bx,[word ptr ds:JITTER]
	jbe	short @@OKay2
	mov	eax,0Fh
@@OKay2:
	add	bx,9136h
	or	ax,cx
	ror	bx,3
	mov	al,[ds:ShadeData2+eax]
	mov	[word ptr ds:JITTER],bx
	mov	ah,al
	pop	ecx
	mov	[word ptr ds:edi],ax
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
	add	edi,eax			;;start scr. adr.
	add	ebp,1024
	mov	eax,[(vertex esi).intensity]
	add	ebp,[(colourdata colour_data).aliastblptr]
	mov	[INTENS],eax
	mov	bp,[word ptr ds:ebp]				;;PD 16May96
	sub	eax,[(vertex ebx).intensity]
	mov	[word ptr ds:JITTER],bp				;;PD 16May96

	mov	edx,eax
	xor	ax,ax
	test	eax,eax
	jz	@@Fast
	neg	edx
	mov	eax,edx
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
	sub	edi,4
@@Loop:
	push	ecx
	mov	ebx,edx
	mov	eax,ebp
	and	ebx,ecx
	add	ebp,[dword ptr ds:DIY]
	shr	ebx,16
	and	eax,[(colourdata colour_data).imageymask]
	mov	cl,[(colourdata colour_data).imageyshift]
	inc	edi
	shr	eax,cl
	add	edx,[dword ptr ds:DIX]
	inc	edi
	add	ebx,eax
	mov	eax,[dword ptr ds:INTENS]
	xor	cx,cx
 	add	eax,[dword ptr ds:JITTER]
	mov	ch,[byte ptr ds:esi+ebx]
	shr	eax,16
	shr	cx,4
	cmp	eax,0Fh
	mov	ebx,[dword ptr ds:DINTENS]
	jbe	short @@OKay
       	mov	eax,0Fh
@@OKay:
	inc	edi
	or	ax,cx
	add	[dword ptr ds:INTENS],ebx
	mov	al,[ds:ShadeData2+eax]
	pop	ecx
	inc	edi
	mov	ah,al
	mov	bx,[word ptr ds:JITTER]
 	mov	[word ptr ds:edi],ax
	add	bx,9136h
 	mov	[word ptr ds:edi+2],ax
	ror	bx,3
	dec	cx
	mov	[word ptr ds:JITTER],bx
	jnz	@@Loop
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
	sub	edi,4
@@FLoop:
	push	ecx
	mov	ebx,edx
	mov	eax,ebp
	and	ebx,ecx
	add	ebp,[dword ptr ds:DIY]
	shr	ebx,16
	and	eax,[(colourdata colour_data).imageymask]
	mov	cl,[(colourdata colour_data).imageyshift]
	inc	edi
	shr	eax,cl
	add	edx,[dword ptr ds:DIX]
	inc	edi
	add	ebx,eax
	inc	edi
	mov	eax,[INTENS]
	xor	cx,cx
	shr	eax,16
	mov	ch,[esi+ebx]
	inc	edi
	shr	cx,4
	or	ax,cx
	pop	ecx
	mov	al,[ds:ShadeData2+eax]
	mov	ah,al
	mov	[word ptr ds:edi],ax
	mov	[word ptr ds:edi+2],ax
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
;;------------------------------------------------------------------------------
	push	eax
	push	ecx
	push	edx
	push	esi
	push	edi
	push	ebp
	mov	esi,edx
	mov	ecx,[(vertex ebx).sx]	;;right vertex
	mov	edi,[(vertex esi).sx]	;;left vertex
	add	ecx,10000h
	sar	edi,16
	sar	ecx,16
	mov	ebp,[(vertex esi).sy]
	sub	ecx,edi
	jle	@@Out
	add	edi,eax			;;start scr. adr.
	mov	eax,[(vertex esi).intensity]
	add	ebp,1024
	mov	[INTENS],eax
	add	ebp,[(colourdata colour_data).aliastblptr]
	mov	edx,[(vertex ebx).intensity]
	mov	ebp,[dword ptr ds:ebp]
	sub	edx,eax
	and	ebp,0FFFFh
	mov	eax,edx
	mov	[dword ptr JITTER],ebp
	sar	edx,01fh
	idiv	ecx
	dec	edi
	mov	[DINTENS],eax
@@Loop:
	xor	eax,eax
	mov	edx,[INTENS]
	mov	ebp,[dword ptr JITTER]
	mov	ah,[byte ptr (colourdata colour_data).col]
	and	ebp,0FFFFh
	shr	eax,4
 	add	edx,ebp
	inc	edi
	shr	edx,16
	add	bp,9136h
	or	eax,edx
	ror	bp,3
	mov	edx,[DINTENS]
	mov	al,[byte ptr ShadeData2+eax]
	mov	[byte ptr edi],al
	add	[INTENS],edx
	dec	ecx
	mov	[dword ptr JITTER],ebp
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
 Procedure	ASM_GGouraudHoriLine2
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
	push	eax
	push	ecx
	push	edx
	push	esi
	push	edi
	push	ebp
	mov	esi,edx
	mov	ecx,[(vertex ebx).sx]	;;right vertex
	mov	edi,[(vertex esi).sx]	;;left vertex
	sar	ecx,17
	sar	edi,17
	sub	ecx,edi
	inc	ecx
	jle	@@Out
	mov	ebp,[(vertex esi).sy]
	add	edi,edi
	add	ebp,1024
	add	edi,eax			;;start scr. adr.
	add	ebp,[(colourdata colour_data).aliastblptr]
	mov	eax,[(vertex esi).intensity]
	mov	bp,[word ptr ds:ebp]
	mov	[INTENS],eax
	mov	[word ptr ds:JITTER],bp
	sub	eax,[(vertex ebx).intensity]
	dec	edi
	neg	eax
	dec	edi
	mov	edx,eax
	sar	edx,01fh
	idiv	ecx
	mov	[DINTENS],eax
@@Loop:
	xor	eax,eax
	mov	edx,[dword ptr ds:INTENS]
	mov	ah,[byte ptr (colourdata colour_data).col]
 	add	edx,[dword ptr ds:JITTER]
	shr	ax,4
	mov	bp,[word ptr ds:JITTER]
	shr	edx,16
	add	bp,9136h
	inc	edi
	ror	bp,3
	or	ax,dx
	mov	[word ptr ds:JITTER],bp
	mov	al,[byte ptr ds:ShadeData2+eax]
	mov	edx,[dword ptr ds:DINTENS]
	xor	ah,ah
	add	[dword ptr ds:INTENS],edx
	mov	al,[Grey3DTable+eax]
	inc	edi
	mov	ah,al
	dec	ecx
	mov	[word ptr ds:edi],ax
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
 Procedure	ASM_GGouraudHoriLine4
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
	push	eax
	push	ecx
	push	edx
	push	esi
	push	edi
	push	ebp
	mov	ecx,[(vertex ebx).sx]	;;right vertex
	sar	ecx,18
	mov	esi,edx
	mov	edi,[(vertex esi).sx]	;;left vertex
	sar	edi,18
	sub	ecx,edi
	inc	ecx
	jle	@@Out
	add	edi,edi
	mov	ebp,[(vertex esi).sy]
	add	ebp,1024
	add	edi,edi
	add	ebp,[(colourdata colour_data).aliastblptr]
	add	edi,eax			;;start scr. adr.
	mov	bp,[word ptr ds:ebp]
	mov	eax,[(vertex esi).intensity]
	mov	[word ptr ds:JITTER],bp
	mov	[INTENS],eax
	sub	eax,[(vertex ebx).intensity]
	neg	eax
	mov	edx,eax
	sar	edx,01fh
	idiv	ecx
	sub	edi,4
	mov	[DINTENS],eax
@@Loop:
	xor	eax,eax
	mov	edx,[dword ptr ds:INTENS]
	mov	ah,[byte ptr (colourdata colour_data).col]
 	add	edx,[dword ptr ds:JITTER]
	shr	ax,4
	shr	edx,16
	cmp	edx,0Fh
	jbe	short @@OKay
	mov	edx,0Fh
@@OKay:
	mov	bp,[word ptr ds:JITTER]
	or	ax,dx
	add	edi,4
	mov	al,[byte ptr ds:ShadeData2+eax]
	add	bp,9136h
	xor	ah,ah
	ror	bp,3
	mov	al,[Grey3DTable+eax]
	mov	edx,[dword ptr ds:DINTENS]
	mov	ah,al
	mov	[word ptr ds:JITTER],bp
	mov	[word ptr ds:edi],ax
	add	[dword ptr ds:INTENS],edx
	mov	[word ptr ds:edi+2],ax
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
 Procedure	ASM_TIPlainHoriLine1
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
	mov	al,[byte ptr (colourdata colour_data).col]
	mov	ebx,[(colourdata colour_data).aliastblptr]

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width
@@Loop:								;;PD 23Feb96
	mov	ah,[byte ptr ds:edi]
	mov	ah,[byte ptr ds:ebx+eax]
	mov	[byte ptr ds:edi],ah				;;PD 23Feb96
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
 Procedure	ASM_TIPlainHoriLine2
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
	mov	al,[byte ptr (colourdata colour_data).col]
	mov	ebx,[(colourdata colour_data).aliastblptr]

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width
;;eax = colour.b, colour.b, colour.b, colour.b
@@Loop:
	mov	ah,[byte ptr ds:edi]
	mov	ah,[byte ptr ds:ebx+eax]
	mov	[byte ptr ds:edi],ah
	mov	[byte ptr ds:edi+1],ah
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
 Procedure	ASM_TIPlainHoriLine4
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
	mov	al,[byte ptr (colourdata colour_data).col]
	mov	ebx,[(colourdata colour_data).aliastblptr]

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width
;;eax = colour.b, colour.b, colour.b, colour.b
@@Loop:
	mov	ah,[byte ptr ds:edi]
	mov	ah,[byte ptr ds:ebx+eax]
	mov	[byte ptr ds:edi],ah
	mov	[byte ptr ds:edi+1],ah
	mov	[byte ptr ds:edi+2],ah
	mov	[byte ptr ds:edi+3],ah
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
	push	ebp
	mov	esi,edx
	mov	ecx,[(vertex ebx).sx]	;;right vertex
	mov	edi,[(vertex esi).sx]	;;left vertex
	add	ecx,10000h
	sar	edi,16						;;PD 08Feb96
	sar	ecx,16						;;PD 08Feb96
	sub	ecx,edi
	jle	@@Out
	add	edi,eax			;;start scr. adr.
	mov	eax,[(vertex esi).ix]	;;left vertex
	mov	edx,[(vertex ebx).ix]	;;right vertex
	mov	[IX],eax
	sub	edx,eax
	mov	eax,edx
	sar	edx,31
	idiv	ecx
	mov	[DIX],eax		;;image x delta
	mov	eax,[(vertex esi).iy]	;;left vertex
	mov	edx,[(vertex ebx).iy]	;;right vertex
	mov	[IY],eax
	sub	edx,eax
	mov	eax,edx
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
	push	ecx
	mov	eax,ebp
	mov	ebx,edx
	and	eax,[(colourdata colour_data).imageymask]
	and	ebx,ecx
	shr	ebx,16
	mov	cl,[(colourdata colour_data).imageyshift]
	shr	eax,cl
	add	ebx,eax
	xor	eax,eax
	pop	ecx
	add	edx,[DIX]
	mov	al,[esi+ebx]
	mov	ebx,[(colourdata colour_data).aliastblptr]
	cmp	al,0FEh
	mov	ah,[byte ptr edi]
	jz	short @@MaskByte
	mov	al,[byte ptr ebx+eax]
	add	ebp,[DIY]
	mov	[byte ptr edi],al
	inc	edi
	dec	cx
	jnz	short @@Loop
@@Out:
	pop	ebp
	pop	edi
	pop	ecx
	ret

@@MaskByte:
	inc	edi
	add	ebp,[DIY]
	dec	cx
	jnz	short @@Loop
	pop	ebp
	pop	edi
	pop	ecx
	ret
	endp


;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_TMImageHoriLine2
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
	mov	esi,edx
	mov	ecx,[(vertex ebx).sx]	;;right vertex
	mov	edi,[(vertex esi).sx]	;;left vertex
	add	ecx,20000h
	sar	edi,17						;;PD 08Feb96
	sar	ecx,17						;;PD 08Feb96
	sub	ecx,edi
	jle	@@Out
	add	edi,edi
	add	edi,eax			;;start scr. adr.
	mov	eax,[(vertex esi).ix]	;;left vertex
	mov	edx,[(vertex ebx).ix]	;;right vertex
	mov	[IX],eax
	sub	edx,eax
	mov	eax,edx
	sar	edx,31
	idiv	ecx
	mov	[DIX],eax		;;image x delta
	mov	eax,[(vertex esi).iy]	;;left vertex
	mov	edx,[(vertex ebx).iy]	;;right vertex
	mov	[IY],eax
	sub	edx,eax
	mov	eax,edx
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

@@Loop:
	push	ecx
	mov	eax,ebp
	mov	ebx,edx
	and	eax,[(colourdata colour_data).imageymask]
	and	ebx,ecx
	shr	ebx,16
	mov	cl,[(colourdata colour_data).imageyshift]
	shr	eax,cl
	add	ebx,eax
	xor	eax,eax
	pop	ecx
	add	edx,[DIX]
	mov	al,[esi+ebx]
	mov	ebx,[(colourdata colour_data).aliastblptr]
	cmp	al,0FEh
	mov	ah,[byte ptr edi]
	jz	short @@MaskByte
	mov	al,[byte ptr ebx+eax]
	add	ebp,[DIY]
	mov	[byte ptr edi],al
	mov	[byte ptr edi+1],al
	add	edi,2
	dec	cx
	jnz	short @@Loop
@@Out:
	pop	ebp
	pop	edi
	pop	ecx
	ret

@@MaskByte:
	add	edi,2
	add	ebp,[DIY]
	dec	cx
	jnz	short @@Loop
	pop	ebp
	pop	edi
	pop	ecx
	ret
	endp

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_TMImageHoriLine4
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
	mov	esi,edx
	mov	ecx,[(vertex ebx).sx]	;;right vertex
	mov	edi,[(vertex esi).sx]	;;left vertex
	add	ecx,40000h
	sar	edi,18						;;PD 08Feb96
	sar	ecx,18						;;PD 08Feb96
	sub	ecx,edi
	jle	@@Out
	add	edi,edi
	add	edi,edi
	add	edi,eax			;;start scr. adr.
	mov	eax,[(vertex esi).ix]	;;left vertex
	mov	edx,[(vertex ebx).ix]	;;right vertex
	mov	[IX],eax
	sub	edx,eax
	mov	eax,edx
	sar	edx,31
	idiv	ecx
	mov	[DIX],eax		;;image x delta
	mov	eax,[(vertex esi).iy]	;;left vertex
	mov	edx,[(vertex ebx).iy]	;;right vertex
	mov	[IY],eax
	sub	edx,eax
	mov	eax,edx
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

@@Loop:
	push	ecx
	mov	eax,ebp
	mov	ebx,edx
	and	eax,[(colourdata colour_data).imageymask]
	and	ebx,ecx
	shr	ebx,16
	mov	cl,[(colourdata colour_data).imageyshift]
	shr	eax,cl
	add	ebx,eax
	xor	eax,eax
	pop	ecx
	add	edx,[DIX]
	mov	al,[esi+ebx]
	mov	ebx,[(colourdata colour_data).aliastblptr]
	cmp	al,0FEh
	mov	ah,[byte ptr edi]
	jz	short @@MaskByte
	mov	al,[byte ptr ebx+eax]
	add	ebp,[DIY]
	mov	[byte ptr edi],al
	mov	[byte ptr edi+1],al
	mov	[byte ptr edi+2],al
	mov	[byte ptr edi+3],al
	add	edi,4
	dec	cx
	jnz	short @@Loop
@@Out:
	pop	ebp
	pop	edi
	pop	ecx
	ret

@@MaskByte:
	add	edi,4
	add	ebp,[DIY]
	dec	cx
	jnz	short @@Loop
	pop	ebp
	pop	edi
	pop	ecx
	ret
	endp

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_TIMImageHoriLine1
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
	mov	esi,edx
	mov	ecx,[(vertex ebx).sx]	;;right vertex
	mov	edi,[(vertex esi).sx]	;;left vertex
	add	ecx,10000h
	sar	edi,16						;;PD 08Feb96
	sar	ecx,16						;;PD 08Feb96
	sub	ecx,edi
	jle	@@Out
	add	edi,eax			;;start scr. adr.
	mov	eax,[(vertex esi).ix]	;;left vertex
	mov	edx,[(vertex ebx).ix]	;;right vertex
	mov	[IX],eax
	sub	edx,eax
	mov	eax,edx
	sar	edx,31
	idiv	ecx
	mov	[DIX],eax		;;image x delta
	mov	eax,[(vertex esi).iy]	;;left vertex
	mov	edx,[(vertex ebx).iy]	;;right vertex
	mov	[IY],eax
	sub	edx,eax
	mov	eax,edx
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
	push	ecx
	mov	eax,ebp
	mov	ebx,edx
	and	eax,[(colourdata colour_data).imageymask]
	and	ebx,ecx
	shr	ebx,16
	mov	cl,[(colourdata colour_data).imageyshift]
	shr	eax,cl
	add	ebx,eax
	xor	eax,eax
	pop	ecx
	add	edx,[DIX]
	mov	ah,[esi+ebx]
	mov	ebx,[(colourdata colour_data).aliastblptr]
 	cmp	ah,0FEh
	mov	al,[byte ptr edi]
	jz	short @@MaskByte
	mov	al,[byte ptr ebx+eax]
	add	ebp,[DIY]
	mov	[byte ptr edi],al
	inc	edi
	dec	cx
	jnz	short @@Loop
@@Out:
	pop	ebp
	pop	edi
	pop	ecx
	ret

@@MaskByte:
	inc	edi
	add	ebp,[DIY]
	dec	cx
	jnz	short @@Loop
	pop	ebp
	pop	edi
	pop	ecx
	ret
	endp


;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_TIMImageHoriLine2
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
	mov	esi,edx
	mov	ecx,[(vertex ebx).sx]	;;right vertex
	mov	edi,[(vertex esi).sx]	;;left vertex
	add	ecx,20000h
	sar	edi,17						;;PD 08Feb96
	sar	ecx,17						;;PD 08Feb96
	sub	ecx,edi
	jle	@@Out
	add	edi,edi
	add	edi,eax			;;start scr. adr.
	mov	eax,[(vertex esi).ix]	;;left vertex
	mov	edx,[(vertex ebx).ix]	;;right vertex
	mov	[IX],eax
	sub	edx,eax
	mov	eax,edx
	sar	edx,31
	idiv	ecx
	mov	[DIX],eax		;;image x delta
	mov	eax,[(vertex esi).iy]	;;left vertex
	mov	edx,[(vertex ebx).iy]	;;right vertex
	mov	[IY],eax
	sub	edx,eax
	mov	eax,edx
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

@@Loop:
	push	ecx
	mov	eax,ebp
	mov	ebx,edx
	and	eax,[(colourdata colour_data).imageymask]
	and	ebx,ecx
	shr	ebx,16
	mov	cl,[(colourdata colour_data).imageyshift]
	shr	eax,cl
	add	ebx,eax
	xor	eax,eax
	pop	ecx
	add	edx,[DIX]
	mov	ah,[esi+ebx]
	mov	ebx,[(colourdata colour_data).aliastblptr]
	cmp	ah,0FEh
	mov	al,[byte ptr edi]
	jz	short @@MaskByte
	mov	al,[byte ptr ebx+eax]
	add	ebp,[DIY]
	mov	[byte ptr edi],al
	mov	[byte ptr edi+1],al
	add	edi,2
	dec	cx
	jnz	short @@Loop
@@Out:
	pop	ebp
	pop	edi
	pop	ecx
	ret

@@MaskByte:
	add	edi,2
	add	ebp,[DIY]
	dec	cx
	jnz	short @@Loop
	pop	ebp
	pop	edi
	pop	ecx
	ret
	endp

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_TIMImageHoriLine4
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
	mov	esi,edx
	mov	ecx,[(vertex ebx).sx]	;;right vertex
	mov	edi,[(vertex esi).sx]	;;left vertex
	add	ecx,40000h
	sar	edi,18						;;PD 08Feb96
	sar	ecx,18						;;PD 08Feb96
	sub	ecx,edi
	jle	@@Out
	add	edi,edi
	add	edi,edi
	add	edi,eax			;;start scr. adr.
	mov	eax,[(vertex esi).ix]	;;left vertex
	mov	edx,[(vertex ebx).ix]	;;right vertex
	mov	[IX],eax
	sub	edx,eax
	mov	eax,edx
	sar	edx,31
	idiv	ecx
	mov	[DIX],eax		;;image x delta
	mov	eax,[(vertex esi).iy]	;;left vertex
	mov	edx,[(vertex ebx).iy]	;;right vertex
	mov	[IY],eax
	sub	edx,eax
	mov	eax,edx
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

@@Loop:
	push	ecx
	mov	eax,ebp
	mov	ebx,edx
	and	eax,[(colourdata colour_data).imageymask]
	and	ebx,ecx
	shr	ebx,16
	mov	cl,[(colourdata colour_data).imageyshift]
	shr	eax,cl
	add	ebx,eax
	xor	eax,eax
	pop	ecx
	add	edx,[DIX]
	mov	ah,[esi+ebx]
	mov	ebx,[(colourdata colour_data).aliastblptr]
	cmp	ah,0FEh
	mov	al,[byte ptr edi]
	jz	short @@MaskByte
	mov	al,[byte ptr ebx+eax]
	add	ebp,[DIY]
	mov	[byte ptr edi],al
	mov	[byte ptr edi+1],al
	mov	[byte ptr edi+2],al
	mov	[byte ptr edi+3],al
	add	edi,4
	dec	cx
	jnz	short @@Loop
@@Out:
	pop	ebp
	pop	edi
	pop	ecx
	ret

@@MaskByte:
	add	edi,4
	add	ebp,[DIY]
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

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_NDGHoriLine1
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Thu 10 Oct 1996
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
	push	eax
	push	ecx
	push	edx
	push	esi
	push	edi
	push	ebp
	mov	esi,edx
	mov	ecx,[(vertex ebx).sx]	;;right vertex
	mov	edi,[(vertex esi).sx]	;;left vertex
	sar	ecx,16						;;PD 08Feb96
	sar	edi,16						;;PD 08Feb96
	sub	ecx,edi
	inc	ecx
	jle	@@Out
	add	edi,eax			;;start scr. adr.
	mov	eax,[(vertex esi).intensity]
	mov	[INTENS],eax
	sub	eax,[(vertex ebx).intensity]
	neg	eax
	mov	edx,eax
	sar	edx,01fh
	idiv	ecx
	dec	edi
	mov	[DINTENS],eax
	mov	ebp,[dword ptr ds:INTENS]
@@Loop:
	xor	eax,eax
	mov	edx,ebp
	mov	ah,[byte ptr (colourdata colour_data).col]
	shr	edx,16
	shr	ax,4
	inc	edi
	or	ax,dx
	add	ebp,[dword ptr ds:DINTENS]
	mov	al,[byte ptr ds:ShadeData2+eax]
	dec	ecx
	mov	[byte ptr ds:edi],al
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
 Procedure	ASM_NDSIHoriLine1
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Thu 10 Oct 1996
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

	mov	edx,eax
	sar	edx,01fh
	idiv	ecx
	mov	[DINTENS],eax

	mov	eax,[(vertex esi).ix]	;;left vertex
	mov	[IX],eax					;;PD 15May96

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
	dec	edi
@@Loop:
	push	ecx
	mov	ebx,edx
	mov	eax,ebp
	and	ebx,ecx
	add	ebp,[dword ptr ds:DIY]
	shr	ebx,16
	and	eax,[(colourdata colour_data).imageymask]
	mov	cl,[(colourdata colour_data).imageyshift]
	inc	edi
	shr	eax,cl
	add	edx,[dword ptr ds:DIX]
	add	ebx,eax
	mov	eax,[dword ptr ds:INTENS]
	xor	cx,cx
	mov	ch,[byte ptr ds:esi+ebx]
	shr	eax,16
	shr	cx,4
	mov	ebx,[dword ptr ds:DINTENS]
	or	ax,cx
	add	[dword ptr ds:INTENS],ebx
	mov	al,[ds:ShadeData2+eax]
	pop	ecx
	mov	[byte ptr ds:edi],al
	dec	cx
	jnz	short @@Loop
@@Out:
	pop	ebp
    	pop	edi
	pop	ecx
	ret
	endp
;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_NDGHoriLine2
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Thu 10 Oct 1996
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
	push	eax
	push	ecx
	push	edx
	push	esi
	push	edi
	push	ebp
	mov	esi,edx
	mov	ecx,[(vertex ebx).sx]	;;right vertex
	mov	edi,[(vertex esi).sx]	;;left vertex
	sar	ecx,17
	sar	edi,17
	sub	ecx,edi
	inc	ecx
	jle	@@Out
	add	edi,edi
	add	edi,eax			;;start scr. adr.
	mov	eax,[(vertex esi).intensity]
	mov	[INTENS],eax
	sub	eax,[(vertex ebx).intensity]
	dec	edi
	neg	eax
	dec	edi
	mov	edx,eax
	sar	edx,01fh
	idiv	ecx
	mov	[DINTENS],eax
	mov	ebp,[dword ptr ds:INTENS]
@@Loop:
	xor	eax,eax
	mov	edx,ebp
	mov	ah,[byte ptr (colourdata colour_data).col]
	shr	ax,4
	shr	edx,16
	inc	edi
	or	ax,dx
	add	ebp,[dword ptr ds:DINTENS]
	mov	al,[byte ptr ds:ShadeData2+eax]
	inc	edi
	mov	ah,al
	dec	ecx
	mov	[word ptr ds:edi],ax
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
 Procedure	ASM_NDSIHoriLine2
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Thu 10 Oct 1996
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

	mov	edx,eax
	xor	ax,ax
	test	eax,eax
	jz	@@Fast
	neg	edx
	mov	eax,edx
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
	sub	edi,2
@@Loop:
	push	ecx
	mov	ebx,edx
	mov	eax,ebp
	and	ebx,ecx
	add	ebp,[dword ptr ds:DIY]
	shr	ebx,16
	and	eax,[(colourdata colour_data).imageymask]
	mov	cl,[(colourdata colour_data).imageyshift]
	inc	edi
	shr	eax,cl
	add	edx,[dword ptr ds:DIX]
	inc	edi
	add	ebx,eax
	mov	eax,[dword ptr ds:INTENS]
	xor	cx,cx
 	mov	ch,[byte ptr ds:esi+ebx]
  	shr	eax,16
 	shr	cx,4
	cmp	eax,0Fh
	mov	ebx,[dword ptr ds:DINTENS]
	jbe	short @@OKay
	mov	eax,0Fh
@@OKay:
 	or	ax,cx
	add	[dword ptr ds:INTENS],ebx
 	mov	al,[ds:ShadeData2+eax]
	pop	ecx
 	mov	ah,al
	dec	cx
 	mov	[word ptr ds:edi],ax
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
	sub	edi,2
@@FLoop:
	push	ecx
	mov	ebx,edx
	mov	eax,ebp
	and	ebx,ecx
	add	ebp,[dword ptr ds:DIY]
	shr	ebx,16
	and	eax,[(colourdata colour_data).imageymask]
	mov	cl,[(colourdata colour_data).imageyshift]
	add	edi,2
	shr	eax,cl
	add	edx,[dword ptr ds:DIX]
	add	ebx,eax
	xor	cx,cx
	mov	eax,[INTENS]
	mov	ch,[byte ptr ds:esi+ebx]
	shr	eax,16
	shr	cx,4
	cmp	eax,0Fh
	jbe	short @@OKay2
	mov	eax,0Fh
@@OKay2:
	or	ax,cx
	mov	al,[ds:ShadeData2+eax]
	pop	ecx
	mov	ah,al
	dec	cx
	mov	[word ptr ds:edi],ax
	jnz	short @@FLoop
	pop	ebp
	pop	edi
	pop	ecx
	ret
	endp
;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_NDGHoriLine4
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Thu 10 Oct 1996
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
	push	eax
	push	ecx
	push	edx
	push	esi
	push	edi
	push	ebp
	mov	ecx,[(vertex ebx).sx]	;;right vertex
	sar	ecx,18
	mov	esi,edx
	mov	edi,[(vertex esi).sx]	;;left vertex
	sar	edi,18
	sub	ecx,edi
	inc	ecx
	jle	@@Out
	add	edi,edi
	add	edi,edi
	add	edi,eax			;;start scr. adr.
	mov	eax,[(vertex esi).intensity]
	mov	[INTENS],eax
	sub	eax,[(vertex ebx).intensity]
	neg	eax
	mov	edx,eax
	sar	edx,01fh
	idiv	ecx
	sub	edi,4
	mov	[DINTENS],eax
	mov	ebp,[dword ptr ds:INTENS]
@@Loop:
	xor	eax,eax
	mov	edx,ebp
	mov	ah,[byte ptr (colourdata colour_data).col]
	shr	edx,16
	shr	ax,4
	cmp	edx,0Fh
	jbe	short @@OKay
	mov	edx,0Fh
@@OKay:
	or	ax,dx
	add	edi,4
	mov	al,[byte ptr ds:ShadeData2+eax]
	mov	ah,al
	add	ebp,[dword ptr ds:DINTENS]
	mov	[word ptr ds:edi],ax
	dec	ecx
	mov	[word ptr ds:edi+2],ax
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
 Procedure	ASM_NDSIHoriLine4
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Thu 10 Oct 1996
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

	mov	edx,eax
	xor	ax,ax
	test	eax,eax
	jz	@@Fast
	neg	edx
	mov	eax,edx
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
	sub	edi,4
@@Loop:
	push	ecx
	mov	ebx,edx
	mov	eax,ebp
	and	ebx,ecx
	add	ebp,[dword ptr ds:DIY]
	shr	ebx,16
	and	eax,[(colourdata colour_data).imageymask]
	mov	cl,[(colourdata colour_data).imageyshift]
	inc	edi
	shr	eax,cl
	add	edx,[dword ptr ds:DIX]
	inc	edi
	add	ebx,eax
	xor	cx,cx
	mov	eax,[dword ptr ds:INTENS]
	mov	ch,[byte ptr ds:esi+ebx]
	shr	eax,16
	shr	cx,4
	cmp	eax,0Fh
	mov	ebx,[dword ptr ds:DINTENS]
	jbe	short @@OKay
       	mov	eax,0Fh
@@OKay:
	inc	edi
	or	ax,cx
	add	[dword ptr ds:INTENS],ebx
	mov	al,[ds:ShadeData2+eax]
	pop	ecx
	mov	ah,al
	inc	edi
 	mov	[word ptr ds:edi],ax
	dec	cx
 	mov	[word ptr ds:edi+2],ax
	jnz	@@Loop
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
	sub	edi,4
@@FLoop:
	push	ecx
	mov	ebx,edx
	mov	eax,ebp
	and	ebx,ecx
	add	ebp,[dword ptr ds:DIY]
	shr	ebx,16
	and	eax,[(colourdata colour_data).imageymask]
	mov	cl,[(colourdata colour_data).imageyshift]
	inc	edi
	shr	eax,cl
	add	edx,[dword ptr ds:DIX]
	inc	edi
	add	ebx,eax
	inc	edi
	mov	eax,[INTENS]
	xor	cx,cx
	shr	eax,16
	mov	ch,[esi+ebx]
	inc	edi
	shr	cx,4
	or	ax,cx
	pop	ecx
	mov	al,[ds:ShadeData2+eax]
	mov	ah,al
	mov	[word ptr ds:edi],ax
	mov	[word ptr ds:edi+2],ax
	dec	cx
	jnz	short @@FLoop
	pop	ebp
	pop	edi
	pop	ecx
	ret
	endp
;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_GNDGHoriLine1
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Thu 10 Oct 1996
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
	push	eax
	push	ecx
	push	edx
	push	esi
	push	edi
	push	ebp
	mov	esi,edx
	mov	ecx,[(vertex ebx).sx]	;;right vertex
	mov	edi,[(vertex esi).sx]	;;left vertex
	sar	ecx,16						;;PD 08Feb96
	sar	edi,16						;;PD 08Feb96
	sub	ecx,edi
	inc	ecx
	jle	@@Out
	add	edi,eax			;;start scr. adr.
	mov	ebp,[(vertex esi).sy]
	mov	eax,[(vertex esi).intensity]
	add	ebp,1024
	mov	[INTENS],eax
	sub	eax,[(vertex ebx).intensity]
	neg	eax
	mov	edx,eax
	sar	edx,01fh
	idiv	ecx
	dec	edi
	mov	[DINTENS],eax
	mov	ebp,[dword ptr ds:INTENS]
@@Loop:
	xor	eax,eax
	mov	edx,ebp
	mov	ah,[byte ptr (colourdata colour_data).col]
	shr	edx,16
	shr	ax,4
	inc	edi
	or	ax,dx
	add	ebp,[dword ptr ds:DINTENS]
	mov	al,[byte ptr ds:ShadeData2+eax]
	xor	ah,ah
	mov	al,[Grey3DTable+eax]
	dec	ecx
	mov	[byte ptr ds:edi],al
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
 Procedure	ASM_NDGSIHoriLine1
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Thu 10 Oct 1996
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
	_save

	_restore
	ret
	endp
;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_GNDGHoriLine2
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Thu 10 Oct 1996
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
	_save

	_restore
	ret
	endp
;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_NDGSIHoriLine2
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Thu 10 Oct 1996
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
	_save

	_restore
	ret
	endp
;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_GNDGHoriLine4
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Thu 10 Oct 1996
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
	push	eax
	push	ecx
	push	edx
	push	esi
	push	edi
	push	ebp
	mov	ecx,[(vertex ebx).sx]	;;right vertex
	sar	ecx,18
	mov	esi,edx
	mov	edi,[(vertex esi).sx]	;;left vertex
	sar	edi,18
	sub	ecx,edi
	inc	ecx
	jle	@@Out
	add	edi,edi
	add	edi,edi
	add	edi,eax			;;start scr. adr.
	mov	eax,[(vertex esi).intensity]
	mov	[INTENS],eax
	sub	eax,[(vertex ebx).intensity]
	neg	eax
	mov	edx,eax
	sar	edx,01fh
	idiv	ecx
	sub	edi,4
	mov	[DINTENS],eax
	mov	ebp,[dword ptr ds:INTENS]
@@Loop:
	xor	eax,eax
	mov	edx,ebp
	mov	ah,[byte ptr (colourdata colour_data).col]
	shr	edx,16
	shr	ax,4
	cmp	edx,0Fh
	jbe	short @@OKay
	mov	edx,0Fh
@@OKay:
	or	ax,dx
	add	edi,4
	mov	al,[byte ptr ds:ShadeData2+eax]
	add	ebp,[dword ptr ds:DINTENS]
	xor	ah,ah
	mov	al,[Grey3DTable+eax]
	mov	ah,al
	mov	[word ptr ds:edi],ax
	dec	ecx
	mov	[word ptr ds:edi+2],ax
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
 Procedure	ASM_NDGSIHoriLine4
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Thu 10 Oct 1996
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
	_save

	_restore
	ret
	endp


ScreenStart		dd	?
BytesPerScanLine	dd	?
X1			dd	?
Y1			dd	?
X2			dd	?
Y2			dd	?
Const1			dd	?
Const2			dd	?
P			dd	?
SX			dd	?
SY			dd	?

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_PlainLine
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Thu 17 Oct 1996
;;Modified
;;
;;Description
;;
;;Inputs	eax = ptr to (x1,y1)
;;		edx = ptr to (x2,y2)
;;		ebx = screen address ptr
;;		ecx = screen bytes per scan line
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
	push	esi
	push	edi
	mov	[dword ptr ds:ScreenStart],ebx
	mov	[dword ptr ds:BytesPerScanLine],ecx
	mov	esi,[dword ptr ds:eax+4]
	mov	edi,[dword ptr ds:edx+4]
	mov	[dword ptr ds:Y1],esi
	mov	[dword ptr ds:Y2],edi
	mov	eax,[dword ptr ds:eax]
	mov	ebx,[dword ptr ds:edx]
	mov	[dword ptr ds:X1],eax
	mov	[dword ptr ds:X2],ebx
	mov	edx,esi
	mov	ecx,edi
	sub	ebx,eax		;;ebx = x2 - x1
	sub	ecx,edx		;;ecx = y2 - y1
	mov	eax,ebx
	mov	edx,ecx
	sar	eax,1fh		;;eax = sign(x2-x1)
	sar	edx,1fh		;;edx = sign(y2-y1)
	xor	ebx,eax
	xor	ecx,edx
	sub	ebx,eax		;;ebx = |x2-x1|
	sub	ecx,edx		;;ecx = |y2-y1|
	test	ecx,ecx
	jnz	short @@DyGt0

;;dy is == 0	horizontal case
	mov	eax,[dword ptr ds:X1]
	mov	edi,[dword ptr ds:Y1]
	cmp	eax,[dword ptr ds:X2]
	jle	short @@L1
	mov	eax,[dword ptr ds:X2]
@@L1:	imul	edi,[dword ptr ds:BytesPerScanLine]
	mov	ecx,ebx
	add	edi,eax
	add	edi,[dword ptr ds:ScreenStart]
	shr	ecx,1
	mov	eax,[(colourdata colour_data).col]
	jnc	short @@L2
	stosb
@@L2:	jz	short @@Done1
	shr	ecx,1
	jnc	short @@L3
	stosw
@@L3:	jz	short @@Done1
	rep	stosd
@@Done1:
	pop	edi
	pop	esi
	pop	edx
	pop	ecx
	pop	ebx
	pop	eax
	ret

@@DyGt0:
	test	ebx,ebx
	jnz	short @@DxGt0

;;dx is == 0	vertical case
	mov	eax,[dword ptr ds:Y1]
	cmp	eax,[dword ptr ds:Y2]
	jle	short @@L4
	mov	eax,[dword ptr ds:Y2]
@@L4:	mov	edi,[dword ptr ds:X1]
	imul	eax,[dword ptr ds:BytesPerScanLine]
	add	edi,[dword ptr ds:ScreenStart]
	mov	edx,[dword ptr ds:BytesPerScanLine]
	add	edi,eax
	sub	edi,edx
	mov	eax,[(colourdata colour_data).col]
@@L5:	add	edi,edx
	dec	ecx
	mov	[byte ptr ds:edi],al
	jnz	short @@L5
	pop	edi
	pop	esi
	pop	edx
	pop	ecx
	pop	ebx
	pop	eax
	ret

@@DxGt0:
	;; ebx = delta x
	;; ecx = delta y
	cmp	ebx,ecx
	ja	@@DxGtDy
	jz	@@DxEqDy

@@DyGtDx:
	mov	edx,ecx
	mov	eax,ebx
	add	edx,edx
	add	eax,eax
	mov	esi,eax
	neg	edx
	sub	esi,ecx
	add	edx,eax

;;eax = const1
;;edx = const2
;;esi = p

	mov	[dword ptr ds:Const1],eax
	mov	[dword ptr ds:Const2],edx
	mov	[dword ptr ds:P],esi

	mov	eax,[dword ptr ds:X1]
	mov	edx,[dword ptr ds:Y1]
	cmp	edx,[dword ptr ds:Y2]
	jl	short @@GotXY
	mov	eax,[dword ptr ds:X2]
	mov	edx,[dword ptr ds:Y2]
@@GotXY:

;;Calc screen address for the start pixel eax=X, edx=Y

	mov	[dword ptr ds:SX],eax
	mov	[dword ptr ds:SY],edx
	mov	edi,eax
	imul	edx,[dword ptr ds:BytesPerScanLine]
	add	edi,[dword ptr ds:ScreenStart]
	mov	eax,[(colourdata colour_data).col]
	add	edi,edx
	mov	[byte ptr ds:edi],al			;;plot start pixel

	mov	edx,[dword ptr ds:SY]
	cmp	edx,[dword ptr ds:Y1]
	mov	esi,[dword ptr ds:X2]
	jz	short @@Pass1
;;y==y2
	cmp	esi,[dword ptr ds:X1]
	jl	short @@Else1
	jmp	short @@If1
@@Pass1:
	;;y==y1
	cmp	esi,[dword ptr ds:X1]
	jg	short @@Else1
@@If1:

@@L9:	add	edi,[dword ptr ds:BytesPerScanLine]
	mov	esi,[dword ptr ds:P]
	inc	[dword ptr ds:SY]
	test	esi,esi
	jge	short @@L10
	add	esi,[dword ptr ds:Const1]
	dec	ecx
	mov	[byte ptr ds:edi],al
	jnz	short @@L9
	jmp	short @@L11
@@L10:	inc	[dword ptr ds:SX]
	inc	edi
	add	esi,[dword ptr ds:Const2]
	dec	ecx
	mov	[byte ptr ds:edi],al
	jnz	short @@L9
@@L11:
	pop	edi
	pop	esi
	pop	edx
	pop	ecx
	pop	ebx
	pop	eax
	ret

@@Else1:
@@L12:	add	edi,[dword ptr ds:BytesPerScanLine]
	mov	esi,[dword ptr ds:P]
	inc	[dword ptr ds:SY]
	test	esi,esi
	jge	short @@L13
	add	esi,[dword ptr ds:Const1]
	dec	ecx
	mov	[byte ptr ds:edi],al
	jnz	short @@L12
	jmp	short @@L14
@@L13:	dec	[dword ptr ds:SX]
	dec	edi
	add	esi,[dword ptr ds:Const2]
	dec	ecx
	mov	[byte ptr ds:edi],al
	jnz	short @@L12
@@L14:
	pop	edi
	pop	esi
	pop	edx
	pop	ecx
	pop	ebx
	pop	eax
	ret

@@DxEqDy:
	mov	edi,[dword ptr ds:Y1]
	mov	eax,[dword ptr ds:X1]
	cmp	edi,[dword ptr ds:Y2]
	jle	short @@L6
	mov	edi,[dword ptr ds:Y2]
@@L6:	cmp	eax,[dword ptr ds:X2]
	jle	short @@L7
     	mov	eax,[dword ptr ds:X2]
@@L7:	imul	edi,[dword ptr ds:BytesPerScanLine]
	mov	edx,[dword ptr ds:BytesPerScanLine]
	add	edi,eax
	inc	edx
	add	edi,[dword ptr ds:ScreenStart]
	sub	edi,edx
	mov	eax,[(colourdata colour_data).col]
@@L8:	add	edi,edx
	dec	ecx
	mov	[byte ptr ds:edi],al
	jnz	short @@L8
	pop	edi
	pop	esi
	pop	edx
	pop	ecx
	pop	ebx
	pop	eax
	ret

@@DxGtDy:
	mov	edx,ebx
	mov	eax,ecx
	add	edx,edx
	add	eax,eax
	neg	edx
	mov	esi,eax
	add	edx,eax
	sub	esi,ebx

;;eax = const1
;;edx = const2
;;esi = p

	mov	[dword ptr ds:Const1],eax
	mov	[dword ptr ds:Const2],edx
	mov	[dword ptr ds:P],esi

	mov	eax,[dword ptr ds:X1]
	mov	edx,[dword ptr ds:Y1]
	cmp	eax,[dword ptr ds:X2]
	jl	short @@GotXY2
	mov	eax,[dword ptr ds:X2]
	mov	edx,[dword ptr ds:Y2]
@@GotXY2:

;;Calc screen address for the start pixel eax=X, edx=Y

	mov	[dword ptr ds:SX],eax
	mov	[dword ptr ds:SY],edx
	mov	edi,eax
	imul	edx,[dword ptr ds:BytesPerScanLine]
	add	edi,[dword ptr ds:ScreenStart]
	mov	eax,[(colourdata colour_data).col]
	add	edi,edx
	mov	[byte ptr ds:edi],al			;;plot start pixel


	pop	edi
	pop	esi
	pop	edx
	pop	ecx
	pop	ebx
	pop	eax
	ret
	endp



	ENDS	_TEXT


ends
end
