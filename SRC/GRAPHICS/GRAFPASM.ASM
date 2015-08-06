;;------------------------------------------------------------------------------
;;Module	grasm16.asm
;;System
;;Author	Paul.
;;Date		Mon 12 Apr 1999
;;Description	16 bit horiline routine for MiG Alley
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------

Procedure Macro name
	_X&name&	Proc
	public	_X&name&
	endm

EndProc Macro name
	_X&name&	EndP
	endm

.386
	_DATA SEGMENT PAGE PUBLIC USE32 'DATA'

vertex	STRUC
		qbx              DD      ?
		dummy1			DD		?
		by              DD      ?
		dummy2			DD		?
		bz              DD      ?
		dummy3			DD		?
		sx              DD      ?
		dummy4			DD		?
		sy              DD      ?
		dummy5			DD		?
		ix              DD      ?
		dummy6			DD		?
		iy              DD      ?
		dummy7			DD		?
		intensity       DD      ?
		dummy8			DD		?
		dummy9			DD		?
vertex	ENDS

colourdata	STRUC
		imageptr	DD	?
		alphaptr	DD	?
		imagexmask	DD	?
		imageymask	DD	?
		aliastblptr	DD	?
		lumtblptr	DD	?
		col		DB	?
		imageyshift	DB	?
		pad2		DB	?
		pad3		DB	?
colourdata	ENDS

;;-----------------------------------------------------------------------------
;;-----------------------------------------------------------------------------
;;		Horizontal line draw routine address tables
;;-----------------------------------------------------------------------------
;;-----------------------------------------------------------------------------

;; palette look up table for 8 -> 16 bit conversion

	dw 256 dup(0)				;;landscape palette
palette_buffer label word
	dw 256*8 dup(0)

palette_table label word
	dw 256 dup (0)

horiline_data1 LABEL DWORD
		DD	_XASM_PlainHoriLine1
		DD	_XASM_GouraudHoriLine1
		DD	_XASM_PlainHoriLine1
		DD	_XASM_ImageHoriLine1
		DD	_XASM_MImageHoriLine1
		DD	_XASM_SImageHoriLine1
		DD	_XASM_ImageHoriLine1
		DD	_XASM_ImageHoriLine1
		DD	_XASM_ImageHoriLine1
		DD	_XASM_MImageHoriLine1
		DD	_XASM_TFImageHoriline1
		DD	_XASM_AImageHoriline1
		DD	_XASM_CImageHoriLine1

horiline_data2	LABEL	DWORD
		DD	_XASM_PlainHoriLine1			;;done
		DD	_XASM_GouraudHoriLine2			;;done
		DD	_XASM_PlainHoriLine2			;;done
		DD	_XASM_ImageHoriLine2			;;done
		DD	_XASM_MImageHoriLine2			;;done
		DD	_XASM_SImageHoriLine2			;;done
		DD	_XASM_ImageHoriLine2			;;done
		DD	_XASM_ImageHoriLine2			;;done
		DD	_XASM_ImageHoriLine2			;;done
		DD	_XASM_MImageHoriLine2			;;done
		DD	_XASM_TFImageHoriline2			;;done
		DD	_XASM_AImageHoriline2			;;done
		DD	_XASM_CImageHoriLine2

horiline_data4	LABEL	DWORD
		DD	_XASM_PlainHoriLine1			;;no point having x4
		DD	_XASM_GouraudHoriLine4			;;done
		DD	_XASM_PlainHoriLine2			;;no point having x4
		DD	_XASM_ImageHoriLine4			;;done
		DD	_XASM_MImageHoriLine4			;;done
		DD	_XASM_SImageHoriLine4			;;done
		DD	_XASM_ImageHoriLine4			;;done
		DD	_XASM_ImageHoriLine4			;;done
		DD	_XASM_ImageHoriLine4			;;done
		DD	_XASM_MImageHoriLine4			;;done
		DD	_XASM_TFImageHoriline4			;;done
		DD	_XASM_AImageHoriline4			;;done
		DD	_XASM_CImageHoriLine4

nullscan_data	LABEL	DWORD
		DD	_XASM_NullScanLine

;;-----------------------------------------------------------------------------
;;-----------------------------------------------------------------------------
;;			Fade data tables
;;-----------------------------------------------------------------------------
;;-----------------------------------------------------------------------------

LandFadeData	db	4098*2 dup (0)
SkyFadeData		db	4098*2 dup (0)
HorizonFadeData	db	16*2 dup(0)
TransparencyData LABEL BYTE
	db	00000000b,00000000b,00000000b,00000000b,00000000b,00000000b,00000000b,00000000b
	db	10000000b,01000000b,00100000b,00010000b,00001000b,00000100b,00000010b,00000001b
	db	10001000b,01000100b,00100010b,00010001b,10001000b,01000100b,00100010b,00010001b
	db	10001001b,01010100b,00101010b,01010001b,10101000b,01010100b,00101010b,00010101b
	db	10011001b,01010101b,01101010b,01010011b,10101010b,01010101b,10101010b,01010101b
	db	11011001b,01011101b,01101110b,01011011b,11101010b,01010111b,10111010b,01110101b
	db	11011101b,11011101b,01101111b,01111011b,11101110b,01110111b,10111011b,01111101b
	db	11011111b,11111101b,01111111b,11111011b,11111110b,11110111b,10111111b,11111101b
TOFF db 0
TSHIFT db 0

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
Lum3DEnabled	DB	0	;;0 OFF, !=0 ON			//RJS 19Jan98
Haze3DEnabled	DB	0	;;0 OFF, !=0 ON			//RJS 30Jan98


	ALIGN	16

IX	DD	?
DIX	DD	?
IY	DD	?
DIY	DD	?
INTENS	DD	?
DINTENS	DD	?
JITTER	DW	0,0						;;PD 15May96
FUP	DB 5,1,7,3,4,0,6,2
	DW	9 dup (?)

	ALIGN	4						;;PD 30Apr96

LclAilBuf	db 64 dup(?)					;;PD 30Apr96

	ALIGN	2

	_DATA	ENDS

	DGROUP	GROUP	_DATA

	_TEXT SEGMENT PAGE PUBLIC USE32 'CODE'


	assume	cs:_TEXT, ds:DGROUP

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_GetPaletteEntry
;;------------------------------------------------------------------------------
;;Inputs	eax = colour index
;;
;;Returns	ax = colour value
;;
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
	mov ax,[palette_table+2*eax] 
	ret
EndProc	ASM_GetPaletteEntry

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_SetPaletteEntry
;;------------------------------------------------------------------------------
;;Inputs	eax = colour index, dx = colour value
;;
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
	mov [palette_table+2*eax],dx
	ret
EndProc	ASM_SetPaletteEntry

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
	movzx	eax,[byte ptr ds:LandFadeData+eax]

	;;If grey 3d is enabled then further modification
	;;of the colour is required

	cmp	[word ptr ds:Grey3DEnabled],0
	jz	short @@Ret
	mov	al,[byte ptr ds:Grey3DTable+eax]
@@Ret:
	ret
EndProc	ASM_GetFadeColour

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
;; Procedure	ASM_SetFadeData
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
;;	cmp	eax,[ds:LastFadeRequest]
;;	jnz	short @@NewFade
;;	ret
;;@@NewFade:
;;	push	eax
;;	push	ebx
;;	push	ecx
;;	push	edx
;;	push	esi
;;	push	edi
;;	push	ebp
;;	mov	[ds:LastFadeRequest],eax
;;	or	eax,eax
;;	jz	short @@GotFadeType	;;Black out
;;	cmp	eax,1
;;	mov	eax,0Fh
;;	jnz	short @@GotFadeType	;;White out
;;	mov	eax,04h			;;Red out
;;@@GotFadeType:
;;	call	MakeBlackoutFadeRanges
;;	pop	ebp
;;	pop	edi
;;	pop	esi
;;	pop	edx
;;	pop	ecx
;;	pop	ebx
;;	pop	eax
;;	ret
;;EndProc	ASM_SetFadeData

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
;;MakeBlackoutFadeRanges	proc
;;	push	eax
;;	push	ebx
;;	push	ecx
;;	push	esi
;;	push	edi
;;	push	ebp

;;	mov	[byte ptr ds:horizcol],al
;;	xor	cx,cx
;;	lea	edi,[ds:FadeData3]
;;	mov	ebp,[colour_data.aliastblptr]
;;	xor	ebx,ebx
;;@@Loopy:
;;	mov	byte ptr ds:[edi],cl
;;	mov	al,[byte ptr ds:horizcol]
;;	mov	byte ptr ds:[edi+16],al
;;	push	cx

;;	mov	cx,0Fh
;;	lea	esi,[ds:shadefromail]
;;@@Loop2:

;;	xor	eax,eax

;;	mov	bl,byte ptr ds:[esi+1]
;;	mov	al,byte ptr ds:[edi+ebx]	;;colour 1

;;	mov	bl,byte ptr ds:[esi+2]
;;	mov	ah,byte ptr ds:[edi+ebx]	;;colour 2

;;	mov	al,byte ptr ds:[ebp+eax]	;;ave(1 & 2)

;;	mov	bl,byte ptr ds:[esi+0]
;;	mov	byte ptr ds:[edi+ebx],al	;;store new val

;;	add	esi,3

;;	dec	cx
;;	jnz	short @@Loop2

;;	add	edi,10h

;;	pop	cx
;;	inc	cx
;;	cmp	cx,256
;;	jnz	@@Loopy

;;	pop	ebp
;;	pop	edi
;;	pop	esi
;;	pop	ecx
;;	pop	ebx
;;	pop	eax
;;	ret
;;MakeBlackoutFadeRanges	endp

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
;; Procedure	ASM_SetGrey3D
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
;;	cmp	ax,[Grey3DEnabled]
;;	jnz	short @@HasChanged
;;	ret
;;@@HasChanged:
;;	push	[word ptr Grey3DEnabled]
;;	mov	[Grey3DEnabled],ax
;;	or	ax,ax
;;	jz	short @@Done

;;	push	eax
;;	push	ebx
;;	push	ecx
;;	push	esi
;;	push	edi

;;	lea	edi,[ds:Grey3DTable]
;;	cmp	eax,0Fh
;;	jl	short @@Okay
;;	mov	eax,0Fh
;;@@Okay:
;;	lea	ebx,[ds:FadeData2+eax]
;;	xor	ecx,ecx
;;@@CLoop:
;;	mov	al,byte ptr ds:[ebx]
;;	mov	byte ptr ds:[edi],al
;;	inc	edi
;;	lea	ebx,ds:[ebx+10h]
;;	inc	ecx
;;	cmp	ecx,100h
;;	jb	short @@CLoop

;;	pop	edi
;;	pop	esi
;;	pop	ecx
;;	pop	ebx
;;	pop	eax
;;@@Done:
;;	pop	ax
;;	ret
;;EndProc	ASM_SetGrey3D

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
;; Procedure	ASM_SetFaded3D
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
;;	cmp	ax,[Grey3DEnabled]
;;	jnz	short @@HasChanged
;;	ret
;;@@HasChanged:
;;	push	[word ptr Grey3DEnabled]
;;	mov	[Grey3DEnabled],ax
;;	or	ax,ax
;;	jz	short @@Done
;;	push	eax
;;	push	ebx
;;	push	ecx
;;	push	esi
;;	push	edi
;;	lea	edi,[ds:Grey3DTable]
;;	cmp	eax,0Fh
;;	jl	short @@Okay
;;	mov	eax,0Fh
;;@@Okay:
;;	lea	ebx,[ds:FadeData3+eax]
;;	xor	ecx,ecx
;;@@CLoop:
;;	mov	al,byte ptr ds:[ebx]
;;	mov	byte ptr ds:[edi],al
;;	inc	edi
;;	lea	ebx,ds:[ebx+10h]
;;	inc	ecx
;;	cmp	ecx,100h
;;	jb	short @@CLoop
;;	pop	edi
;;	pop	esi
;;	pop	ecx
;;	pop	ebx
;;	pop	eax
;;@@Done:
;;	pop	ax
;;	ret
;;EndProc	ASM_SetFaded3D

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
EndProc ASM_SetPixelWidth

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_GetPaletteTable
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
	lea eax,[palette_buffer]
	ret
EndProc ASM_GetPaletteTable

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_SelectPalette
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Thu 21 Dec 1995
;;Modified
;;
;;Description
;;
;;Inputs	ax=palette number
;;
;;Returns
;;
;;Externals
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
	push esi
	push edi
	push ecx
	movsx eax,ax
	shl eax,9
	lea esi,[palette_buffer+eax]
	lea edi,[palette_table]
	mov ecx,128
	rep movsd
	pop ecx
	pop edi
	pop esi
	ret
EndProc ASM_SelectPalette


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
	push	edi
	push	ebp
	push	edx
	push	ecx
	lea	ebx,[horiline_data1]
	cmp	[PixelWidth],1
	jz	short @@OK
	lea	ebx,[horiline_data2]
	cmp	[PixelWidth],2
	jz	short @@OK
	lea	ebx,[horiline_data4]
@@OK:
@@Done:	
	mov	eax,[ebx+4*eax]
	pop	ecx
	pop	edx
	pop	ebp
	pop	edi
	pop	esi
	pop	ebx
	ret
EndProc	ASM_HoriLineAddr


;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
;; Procedure	ASM_SetAliasTblPtr
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

;;	mov	[colour_data.aliastblptr],eax
;;	mov	eax,offset LandFadeData
;;	xor	eax,eax
;;	ret
;;EndProc	ASM_SetAliasTblPtr

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_GetLandFadeTable
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Mon 25 Mar 1996
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
	mov	eax,offset LandFadeData
	mov edx,offset SkyFadeData
	ret
EndProc	ASM_GetLandFadeTable

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_GetHorizonFadeTable
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Mon 25 Mar 1996
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
	mov	eax,offset HorizonFadeData
	ret
EndProc	ASM_GetHorizonFadeTable

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

	push	eax
	push	esi
	push	edi
	push	ecx

	mov	esi,-1
@@L1:	shr	edx,1
	inc	esi
	or	edx,edx
	jnz	short @@L1
	mov	edx,esi
	mov	esi,-1
@@L2:	shr	ebx,1
	inc	esi
	or	ebx,ebx
	jnz	short @@L2
	mov	ebx,esi
	mov	esi,ecx
	cmp eax,0ffh
	lea	edi,[colour_data]
	jbe short @@colour
	mov [edi+colourdata.alphaptr],eax
	jmp short @@lq
@@colour:
	mov	[edi+colourdata.col],al
@@lq:
	mov	eax,00000001h
	mov	cl,dl
	shl	eax,cl
	dec	eax
	shl	eax,16
	mov	[edi+colourdata.imagexmask],eax
	mov	al,16
	sub	al,dl				;;ugly shift thing dl & bl
	mov	[edi+colourdata.imageyshift],al
	mov	eax,00000001h
	mov	cl,bl
	shl	eax,cl
	dec	eax
	shl	eax,16
	mov	[edi+colourdata.imageymask],eax
	mov	[edi+colourdata.imageptr],esi
	pop	ecx
	pop	edi
	pop	esi
	pop	eax
;;TempCode PD 07Jun96 	call	ASM_MakeShadeTable_
	ret
EndProc	ASM_SetColour

;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
;;	PLAIN POLYGON SCAN LINE ROUTINES @ x1 and x2 pixel rez.
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
	int 3
	push	ebx
	push	ecx
	push	edx
	push	esi						;;PD 10Jul96
	push	edi
	mov	ecx,[ebx+vertex.sx]	;;right vertex
	mov	edi,[edx+vertex.sx]	;;left vertex
	inc	ecx
	sub	ecx,edi
	push	eax
	jle	short @@Out
	add	edi,eax			;;start scr. adr.
	mov	esi,[colour_data.aliastblptr]
	xor	edx,edx
	mov	dh,[byte ptr colour_data.col]
;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width
;;eax = colour.b, colour.b, colour.b, colour.b
@@Loop:								;;PD 23Feb96
	mov	dl,byte ptr ds:[edi]
	mov	al,byte ptr ds:[esi+edx]
	inc	edi						;;PD 23Feb96
	dec	cx						;;PD 23Feb96
	mov	byte ptr [edi-1],al				;;PD 23Feb96
	jnz	short @@Loop					;;PD 23Feb96
@@Out:
	pop	eax
	pop	edi
	pop	esi
	pop	edx						;;PD 10Jul96
	pop	ecx
	pop	ebx
	ret
EndProc	ASM_SmokedGlassLine
;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_PlainHoriLine1
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Mon 12 Apr 1999
;;Modified	Made 16-bit for MiG Alley
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
	mov	ecx,[ebx+vertex.sx]	;;right vertex
	mov	edi,[edx+vertex.sx]	;;left vertex
	sar	ecx,16						;;PD 08Feb96
	sar	edi,16						;;PD 08Feb96
	sub	ecx,edi
	inc	ecx
	jle	@@Out
	add edi,edi
	add	edi,eax			;;start scr. adr.

	xor	eax,eax
	mov	al,[colour_data.col]
	add	ax,ax
	mov	ax,word ptr [palette_table+eax]

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width
;;eax = colour.b, colour.b, colour.b, colour.b
	rep	stosw
@@Out:
	pop	edi
	pop	ecx
	ret
EndProc	ASM_PlainHoriLine1

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
	push	edx
	mov	ecx,[ebx+vertex.sx]	;;right vertex
	mov	edi,[edx+vertex.sx]	;;left vertex
	add	ecx,20000h
	sar	edi,17
	sar	ecx,17
	add	eax,edi
	sub	ecx,edi
	jle	@@Out
	add	edi,eax
	xor	eax,eax
	mov	al,[colour_data.col]
	add	ax,ax
	mov	ax,[palette_table+eax]
	mov	dx,ax
	shl	eax,16
	mov	ax,dx

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width
;;eax = colour.b, colour.b, colour.b, colour.b
	rep	stosd
@@Out:
	pop	edx
	pop	edi
	pop	ecx
	ret
EndProc	ASM_PlainHoriLine2

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
	mov	ecx,[ebx+vertex.sx]	;;right vertex
	mov	edi,[esi+vertex.sx]	;;left vertex
	sar	ecx,16						;;PD 08Feb96
	sar	edi,16						;;PD 08Feb96
	sub	ecx,edi
	inc	ecx
	jle	@@Out
	add	edi,edi
	add	edi,eax			;;start scr. adr.
	mov	ebp,[esi+vertex.sy]
	mov	eax,[esi+vertex.intensity]
	and	ebp,0ffh
	mov	[INTENS],eax
	lea	ebp,[LandFadeData+ebp]
	sub	eax,[ebx+vertex.intensity]
	movzx	ebp,word ptr [ebp]
	neg	eax
	mov	word ptr [JITTER],bp
	mov	edx,eax
	sar	edx,01fh
	idiv	ecx
	dec	edi
	dec	edi
	mov	[DINTENS],eax
@@Loop:
	xor	eax,eax
	mov	edx,dword ptr [INTENS]
	movzx	ebp,word ptr [JITTER]
 	add	edx,ebp
	inc	edi
	inc	edi
	shr	edx,16
	add	bp,9136h
	cmp	edx,0fh
	jbe	short @@Okay
       	mov	edx,0fh
@@Okay:
	ror	bp,3
	mov	ax,word ptr [HorizonFadeData+2*edx]
	mov	edx,dword ptr [DINTENS]
	mov	word ptr [edi],ax
	add	dword ptr [INTENS],edx
	dec	ecx
	mov	word ptr [JITTER],bp
	jnz	short @@Loop
@@Out:
	pop	ebp
	pop	edi
	pop	esi
	pop	edx
	pop	ecx
	pop	eax
	ret
EndProc	ASM_GouraudHoriLine1

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
	mov	ecx,[ebx+vertex.sx]	;;right vertex
	mov	edi,[esi+vertex.sx]	;;left vertex
	add	ecx,20000h
	sar	ecx,17						;;PD 08Feb96
	sar	edi,17						;;PD 08Feb96
	sub	ecx,edi
	inc	ecx
	jle	@@Out
	add	edi,edi
	add	edi,edi
	add	edi,eax			;;start scr. adr.
	mov	ebp,[esi+vertex.sy]
	mov	eax,[esi+vertex.intensity]
	and	ebp,0ffh
	mov	[INTENS],eax
	lea	ebp,[LandFadeData+ebp]
	sub	eax,[ebx+vertex.intensity]
	movzx	ebp,word ptr [ebp]
	neg	eax
	mov	word ptr [JITTER],bp
	mov	edx,eax
	sar	edx,01fh
	idiv	ecx
	sub edi,4
	mov	[DINTENS],eax
@@Loop:
	xor	eax,eax
	mov	edx,dword ptr [INTENS]
	movzx	ebp,word ptr [JITTER]
 	add	edx,ebp
	add edi,4
	shr	edx,16
	add	bp,9136h
	cmp	edx,0fh
	jbe	short @@Okay
       	mov	edx,0fh
@@Okay:
	ror	bp,3
	mov	ax,word ptr [HorizonFadeData+2*edx]
	mov	edx,dword ptr [DINTENS]
	mov	word ptr [edi],ax
	mov	word ptr [edi+2],ax
	add	dword ptr [INTENS],edx
	dec	ecx
	mov	word ptr [JITTER],bp
	jnz	short @@Loop
@@Out:
	pop	ebp
	pop	edi
	pop	esi
	pop	edx
	pop	ecx
	pop	eax
	ret
EndProc	ASM_GouraudHoriLine2

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
	mov	ecx,[ebx+vertex.sx]	;;right vertex
	mov	edi,[esi+vertex.sx]	;;left vertex
	add	ecx,40000h
	sar	ecx,18						;;PD 08Feb96
	sar	edi,18						;;PD 08Feb96
	sub	ecx,edi
	inc	ecx
	jle	@@Out
	add	edi,edi
	add	edi,edi
	add	edi,edi
	add	edi,eax			;;start scr. adr.
	mov	ebp,[esi+vertex.sy]
	mov	eax,[esi+vertex.intensity]
	and	ebp,0ffh
	mov	[INTENS],eax
	lea	ebp,[LandFadeData+ebp]
	sub	eax,[ebx+vertex.intensity]
	movzx	ebp,word ptr [ebp]
	neg	eax
	mov	word ptr [JITTER],bp
	mov	edx,eax
	sar	edx,01fh
	idiv	ecx
	sub edi,8
	mov	[DINTENS],eax
@@Loop:
	xor	eax,eax
	mov	edx,dword ptr [INTENS]
	movzx	ebp,word ptr [JITTER]
 	add	edx,ebp
	add edi,8
	shr	edx,16
	add	bp,9136h
	cmp	edx,0fh
	jbe	short @@Okay
       	mov	edx,0fh
@@Okay:
	ror	bp,3
	mov	ax,word ptr [HorizonFadeData+2*edx]
	mov	edx,dword ptr [DINTENS]
	mov	word ptr [edi],ax
	mov	word ptr [edi+2],ax
	mov	word ptr [edi+4],ax
	mov	word ptr [edi+6],ax
	add	dword ptr [INTENS],edx
	dec	ecx
	mov	word ptr [JITTER],bp
	jnz	short @@Loop
@@Out:
	pop	ebp
	pop	edi
	pop	esi
	pop	edx
	pop	ecx
	pop	eax
	ret
EndProc	ASM_GouraudHoriLine4

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
	mov	ecx,[ebx+vertex.sx]	;;right vertex
	mov	edi,[edx+vertex.sx]	;;left vertex
	add	ecx,10000h
	sar	edi,16
	sar	ecx,16
	mov	esi,edx
	sub	ecx,edi
	jle	@@Out
	add	edi,edi
	add	edi,eax			;;start scr. adr.
	mov	eax,[esi+vertex.ix]	;;left vertex
	mov	edx,[ebx+vertex.ix]	;;right vertex
	mov	[IX],eax
	sub	edx,eax
	mov	ebp,[esi+vertex.iy]
	mov	eax,edx
	sar	edx,31
	idiv	ecx
	mov	[IY],ebp
	mov	[DIX],eax		;;image x delta
	mov	edx,[ebx+vertex.iy]	;;right vertex
	mov	eax,ebp
	sub	edx,ebp
	jz	@@Horizontal
	cmp	edx,0fffeff9ah
	jl	short @@NotHorizontal
	cmp	edx,000010066h
	jle	@@Horizontal
@@NotHorizontal:
	mov	eax,edx
	mov	esi,[colour_data.imageptr]
	sar	edx,31
	idiv	ecx
	dec	edi
	dec	edi
	mov	[DIY],eax					;;image y delta
	mov	edx,[IX]

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width

@@Loop:
	push	ecx
	mov	ebx,[colour_data.imagexmask]
	mov	eax,[DIX]
	and	ebx,edx
	add	edx,eax
	mov	ecx,[colour_data.imageymask]
	mov	eax,ebp
	mov	cl,[colour_data.imageyshift]
	shr	ebx,16
	and	eax,ecx
	add	ebx,esi
	shr	eax,cl
	inc	edi
	inc	edi
	mov	ecx,[DIY]
	add	ebx,eax
	add	ebp,ecx
	pop	ecx
	mov	eax,[dword ptr ebx]
	and eax,0FFh
	add ax,ax
	dec	ecx
	mov ax,[palette_table+eax]
	mov	word ptr [edi],ax
	jnz	short @@Loop
@@Out:
	pop	ebp
	pop	edi
	pop	ecx
	ret
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


@@Horizontal:
	mov	esi,[colour_data.imageptr]
	or	ecx,[colour_data.imagexmask]
	mov	edx,[IX]
	push	ecx
	and	ebp,[colour_data.imageymask]
	mov	cl,[colour_data.imageyshift]
	shr	ebp,cl
	pop	ecx
	add	esi,ebp
	dec	edi
	dec	edi
	mov	ebp,[DIX]
@@Loop2:
	mov	ebx,edx
	add	edx,ebp
	and	ebx,ecx
	inc	edi
	inc	edi
	shr	ebx,16
	mov	bl,byte ptr [esi+ebx]
	and ebx,0FFh
	add bx,bx
	dec	cx
	mov bx,[palette_table+ebx]
	mov	word ptr [edi],bx
	jnz	short @@Loop2
	pop	ebp
	pop	edi
	pop	ecx
	ret
EndProc	ASM_ImageHoriLine1

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
	mov	ecx,[ebx+vertex.sx]	;;right vertex
	mov	edi,[edx+vertex.sx]	;;left vertex
	add	ecx,20000h
	sar	edi,17
	sar	ecx,17
	mov	esi,edx
	sub	ecx,edi
	jle	@@Out
	add	edi,edi
	add	edi,edi
	add	edi,eax			;;start scr. adr.
	mov	eax,[esi+vertex.ix]	;;left vertex
	mov	edx,[ebx+vertex.ix]	;;right vertex
	mov	[IX],eax
	sub	edx,eax
	mov	ebp,[esi+vertex.iy]
	mov	eax,edx
	sar	edx,31
	idiv	ecx
	mov	[IY],ebp
	mov	[DIX],eax		;;image x delta
	mov	edx,[ebx+vertex.iy]	;;right vertex
	mov	eax,ebp
	sub	edx,ebp
	jz	@@Horizontal
	cmp	edx,0fffeff9ah
	jl	short @@NotHorizontal
	cmp	edx,000010066h
	jle	@@Horizontal
@@NotHorizontal:
	mov	eax,edx
	mov	esi,[colour_data.imageptr]
	sar	edx,31
	idiv	ecx
	sub	edi,4
	mov	[DIY],eax					;;image y delta
	mov	edx,[IX]

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width

@@Loop:
	push	ecx
	mov	ebx,[colour_data.imagexmask]
	mov	eax,[DIX]
	and	ebx,edx
	add	edx,eax
	mov	ecx,[colour_data.imageymask]
	mov	eax,ebp
	mov	cl,[colour_data.imageyshift]
	shr	ebx,16
	and	eax,ecx
	add	ebx,esi
	shr	eax,cl
	add	edi,4
	mov	ecx,[DIY]
	add	ebx,eax
	add	ebp,ecx
	pop	ecx
	mov	eax,[dword ptr ebx]
	and eax,0FFh
	add ax,ax
	dec	ecx
	mov ax,[palette_table+eax]
	mov	word ptr [edi],ax
	mov	word ptr [edi+2],ax
	jnz	short @@Loop
@@Out:
	pop	ebp
	pop	edi
	pop	ecx
	ret
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


@@Horizontal:
	mov	esi,[colour_data.imageptr]
	or	ecx,[colour_data.imagexmask]
	mov	edx,[IX]
	push	ecx
	and	ebp,[colour_data.imageymask]
	mov	cl,[colour_data.imageyshift]
	shr	ebp,cl
	pop	ecx
	add	esi,ebp
	sub edi,4
	mov	ebp,[DIX]
@@Loop2:
	mov	ebx,edx
	add	edx,ebp
	and	ebx,ecx
	add edi,4
	shr	ebx,16
	mov	bl,byte ptr [esi+ebx]
	and ebx,0FFh
	add bx,bx
	dec	cx
	mov bx,[palette_table+ebx]
	mov	word ptr [edi],bx
	mov	word ptr [edi+2],bx
	jnz	short @@Loop2
	pop	ebp
	pop	edi
	pop	ecx
	ret
EndProc	ASM_ImageHoriLine2

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_ImageHoriLine4
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
	mov	ecx,[ebx+vertex.sx]	;;right vertex
	mov	edi,[edx+vertex.sx]	;;left vertex
	add	ecx,40000h
	sar	edi,18
	sar	ecx,18
	mov	esi,edx
	sub	ecx,edi
	jle	@@Out
	add	edi,edi
	add	edi,edi
	add	edi,edi
	add	edi,eax			;;start scr. adr.
	mov	eax,[esi+vertex.ix]	;;left vertex
	mov	edx,[ebx+vertex.ix]	;;right vertex
	mov	[IX],eax
	sub	edx,eax
	mov	ebp,[esi+vertex.iy]
	mov	eax,edx
	sar	edx,31
	idiv	ecx
	mov	[IY],ebp
	mov	[DIX],eax		;;image x delta
	mov	edx,[ebx+vertex.iy]	;;right vertex
	mov	eax,ebp
	sub	edx,ebp
	jz	@@Horizontal
	cmp	edx,0fffeff9ah
	jl	short @@NotHorizontal
	cmp	edx,000010066h
	jle	@@Horizontal
@@NotHorizontal:
	mov	eax,edx
	mov	esi,[colour_data.imageptr]
	sar	edx,31
	idiv	ecx
	sub	edi,8
	mov	[DIY],eax					;;image y delta
	mov	edx,[IX]

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width

@@Loop:
	push	ecx
	mov	ebx,[colour_data.imagexmask]
	mov	eax,[DIX]
	and	ebx,edx
	add	edx,eax
	mov	ecx,[colour_data.imageymask]
	mov	eax,ebp
	mov	cl,[colour_data.imageyshift]
	shr	ebx,16
	and	eax,ecx
	add	ebx,esi
	shr	eax,cl
	add	edi,8
	mov	ecx,[DIY]
	add	ebx,eax
	add	ebp,ecx
	pop	ecx
	mov	eax,[dword ptr ebx]
	and eax,0FFh
	add ax,ax
	dec	ecx
	mov ax,[palette_table+eax]
	mov	word ptr [edi],ax
	mov	word ptr [edi+2],ax
	mov	word ptr [edi+4],ax
	mov	word ptr [edi+6],ax
	jnz	short @@Loop
@@Out:
	pop	ebp
	pop	edi
	pop	ecx
	ret
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


@@Horizontal:
	mov	esi,[colour_data.imageptr]
	or	ecx,[colour_data.imagexmask]
	mov	edx,[IX]
	push	ecx
	and	ebp,[colour_data.imageymask]
	mov	cl,[colour_data.imageyshift]
	shr	ebp,cl
	pop	ecx
	add	esi,ebp
	sub edi,8
	mov	ebp,[DIX]
@@Loop2:
	mov	ebx,edx
	add	edx,ebp
	and	ebx,ecx
	add edi,8
	shr	ebx,16
	mov	bl,byte ptr [esi+ebx]
	and ebx,0FFh
	add bx,bx
	dec	cx
	mov bx,[palette_table+ebx]
	mov	word ptr [edi],bx
	mov	word ptr [edi+2],bx
	mov	word ptr [edi+4],bx
	mov	word ptr [edi+6],bx
	jnz	short @@Loop2
	pop	ebp
	pop	edi
	pop	ecx
	ret
EndProc	ASM_ImageHoriLine4

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
	mov	ecx,[ebx+vertex.sx]	;;right vertex
	mov	esi,edx
	mov	edi,[edx+vertex.sx]	;;left vertex
	add	ecx,10000h
	sar	edi,16						;;PD 08Feb96
	sar	ecx,16						;;PD 08Feb96
	sub	ecx,edi
	jle	@@Out
	push	ebp
	add	edi,edi
	add	edi,eax			;;start scr. adr.
	mov	eax,[esi+vertex.ix]	;;left vertex
	mov	edx,[ebx+vertex.ix]	;;right vertex
	mov	[IX],eax
	sub	edx,eax
	mov	eax,edx
	sar	edx,31
	idiv	ecx
	mov	[DIX],eax		;;image x delta
	mov	ebp,[esi+vertex.iy]	;;left vertex
	mov	edx,[ebx+vertex.iy]	;;right vertex
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
	or	ecx,[colour_data.imagexmask]
	mov	esi,[colour_data.imageptr]
	mov	[DIY],eax		;;image y delta
	mov	edx,[IX]
	mov	ebp,[IY]

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width

	dec	edi
	dec	edi
@@Loop:
	push	ecx
	mov	eax,ebp
	mov	ebx,edx
	and	eax,[colour_data.imageymask]
	and	ebx,ecx
	add	edx,[dword ptr ds:DIX]
	shr	ebx,16
	mov	cl,[colour_data.imageyshift]
	add	ebp,[dword ptr ds:DIY]
	shr	eax,cl
	inc	edi
	inc	edi
	add	ebx,eax
	mov	al,[esi+ebx]
	cmp	al,0FEh
	pop	ecx
	jz	short @@MaskByte
	and eax,0ffh
	add ax,ax
	mov ax,[palette_table+eax]
	mov	word ptr ds:[edi],ax
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
	mov	esi,[colour_data.imageptr]
	mov	edx,[IX]
	or	ecx,[colour_data.imagexmask]
	push	ecx
	and	ebp,[colour_data.imageymask]
	mov	cl,[colour_data.imageyshift]
	shr	ebp,cl
	pop	ecx
	add	esi,ebp
	dec	edi
	dec	edi
	mov	ebp,[dword ptr ds:DIX]
@@Loop2:
	mov	ebx,edx
	add	edx,ebp
	and	ebx,ecx
	inc	edi
	inc	edi
	shr	ebx,16
	mov	bl,byte ptr ds:[esi+ebx]
	cmp	bl,0feh
	jz	short @@mb
	and ebx,0ffh
	add bx,bx
	mov bx,[palette_table+ebx]
	mov	word ptr ds:[edi],bx
@@mb:
	dec	cx
	jnz	short @@Loop2
	pop	ebp
	pop	edi
	pop	ecx
	ret
EndProc	ASM_MImageHoriLine1

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
	mov	ecx,[ebx+vertex.sx]	;;right vertex
	mov	esi,edx
	mov	edi,[edx+vertex.sx]	;;left vertex
	add	ecx,20000h
	sar	edi,17						;;PD 08Feb96
	sar	ecx,17						;;PD 08Feb96
	sub	ecx,edi
	jle	@@Out
	push	ebp
	add	edi,edi
	add	edi,edi
	add	edi,eax			;;start scr. adr.
	mov	eax,[esi+vertex.ix]	;;left vertex
	mov	edx,[ebx+vertex.ix]	;;right vertex
	mov	[IX],eax
	sub	edx,eax
	mov	eax,edx
	sar	edx,31
	idiv	ecx
	mov	[DIX],eax		;;image x delta
	mov	ebp,[esi+vertex.iy]	;;left vertex
	mov	edx,[ebx+vertex.iy]	;;right vertex
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
	or	ecx,[colour_data.imagexmask]
	mov	esi,[colour_data.imageptr]
	mov	[DIY],eax		;;image y delta
	mov	edx,[IX]
	mov	ebp,[IY]

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width

	sub	edi,4
@@Loop:
	push	ecx
	mov	eax,ebp
	mov	ebx,edx
	and	eax,[colour_data.imageymask]
	and	ebx,ecx
	add	edx,[dword ptr ds:DIX]
	shr	ebx,16
	mov	cl,[colour_data.imageyshift]
	add	ebp,[dword ptr ds:DIY]
	shr	eax,cl
	add	edi,4
	add	ebx,eax
	mov	al,[esi+ebx]
	cmp	al,0FEh
	pop	ecx
	jz	short @@MaskByte
	and eax,0ffh
	add ax,ax
	mov ax,[palette_table+eax]
	mov	word ptr ds:[edi],ax
	mov	word ptr ds:[edi+2],ax
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
	mov	esi,[colour_data.imageptr]
	mov	edx,[IX]
	or	ecx,[colour_data.imagexmask]
	push	ecx
	and	ebp,[colour_data.imageymask]
	mov	cl,[colour_data.imageyshift]
	shr	ebp,cl
	pop	ecx
	add	esi,ebp
	sub edi,4
	mov	ebp,[dword ptr ds:DIX]
@@Loop2:
	mov	ebx,edx
	add	edx,ebp
	and	ebx,ecx
	add	edi,4
	shr	ebx,16
	mov	bl,byte ptr ds:[esi+ebx]
	cmp	bl,0feh
	jz	short @@mb
	and ebx,0ffh
	add bx,bx
	mov bx,[palette_table+ebx]
	mov	word ptr ds:[edi],bx
	mov	word ptr ds:[edi+2],bx
@@mb:
	dec	cx
	jnz	short @@Loop2
	pop	ebp
	pop	edi
	pop	ecx
	ret
EndProc	ASM_MImageHoriLine2

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_MImageHoriLine4
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
	mov	ecx,[ebx+vertex.sx]	;;right vertex
	mov	esi,edx
	mov	edi,[edx+vertex.sx]	;;left vertex
	add	ecx,40000h
	sar	edi,18						;;PD 08Feb96
	sar	ecx,18						;;PD 08Feb96
	sub	ecx,edi
	jle	@@Out
	push	ebp
	add	edi,edi
	add	edi,edi
	add	edi,edi
	add	edi,eax			;;start scr. adr.
	mov	eax,[esi+vertex.ix]	;;left vertex
	mov	edx,[ebx+vertex.ix]	;;right vertex
	mov	[IX],eax
	sub	edx,eax
	mov	eax,edx
	sar	edx,31
	idiv	ecx
	mov	[DIX],eax		;;image x delta
	mov	ebp,[esi+vertex.iy]	;;left vertex
	mov	edx,[ebx+vertex.iy]	;;right vertex
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
	or	ecx,[colour_data.imagexmask]
	mov	esi,[colour_data.imageptr]
	mov	[DIY],eax		;;image y delta
	mov	edx,[IX]
	mov	ebp,[IY]

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width

	sub	edi,8
@@Loop:
	push	ecx
	mov	eax,ebp
	mov	ebx,edx
	and	eax,[colour_data.imageymask]
	and	ebx,ecx
	add	edx,[dword ptr ds:DIX]
	shr	ebx,16
	mov	cl,[colour_data.imageyshift]
	add	ebp,[dword ptr ds:DIY]
	shr	eax,cl
	add	edi,8
	add	ebx,eax
	mov	al,[esi+ebx]
	cmp	al,0FEh
	pop	ecx
	jz	short @@MaskByte
	and eax,0ffh
	add ax,ax
	mov ax,[palette_table+eax]
	mov	word ptr ds:[edi],ax
	mov	word ptr ds:[edi+2],ax
	mov	word ptr ds:[edi+4],ax
	mov	word ptr ds:[edi+6],ax
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
	mov	esi,[colour_data.imageptr]
	mov	edx,[IX]
	or	ecx,[colour_data.imagexmask]
	push	ecx
	and	ebp,[colour_data.imageymask]
	mov	cl,[colour_data.imageyshift]
	shr	ebp,cl
	pop	ecx
	add	esi,ebp
	sub edi,8
	mov	ebp,[dword ptr ds:DIX]
@@Loop2:
	mov	ebx,edx
	add	edx,ebp
	and	ebx,ecx
	add	edi,8
	shr	ebx,16
	mov	bl,byte ptr ds:[esi+ebx]
	cmp	bl,0feh
	jz	short @@mb
	and ebx,0ffh
	add bx,bx
	mov bx,[palette_table+ebx]
	mov	word ptr ds:[edi],bx
	mov	word ptr ds:[edi+2],bx
	mov	word ptr ds:[edi+4],bx
	mov	word ptr ds:[edi+6],bx
@@mb:
	dec	cx
	jnz	short @@Loop2
	pop	ebp
	pop	edi
	pop	ecx
	ret
EndProc	ASM_MImageHoriLine4

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
	mov	ecx,[ebx+vertex.sx]	;;right vertex
	sar	ecx,16						;;PD 08Feb96
	mov	esi,edx
	mov	edi,[esi+vertex.sx]	;;left vertex
	sar	edi,16						;;PD 08Feb96
	sub	ecx,edi
	inc	ecx
	jle	@@Out

	mov	ebp,[esi+vertex.sy]
	add	edi,edi
	add	edi,eax			;;start scr. adr.
;;	add	ebp,1024
	and ebp,0FFh
	mov	eax,[esi+vertex.intensity]
	lea	ebp,[LandFadeData+ebp]
	mov	[INTENS],eax
	mov	bp,word ptr ds:[ebp]				;;PD 16May96
	sub	eax,[ebx+vertex.intensity]
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

	mov	eax,[esi+vertex.ix]	;;left vertex
	mov	[IX],eax

	sub	eax,[ebx+vertex.ix]	;;right vertex
	neg	eax
	mov	edx,eax
	sar	edx,31
	idiv	ecx
	mov	[DIX],eax		;;image x delta

	mov	eax,[esi+vertex.iy]	;;left vertex
	mov	[IY],eax
	sub	eax,[ebx+vertex.iy]	;;right vertex
	neg	eax
	mov	edx,eax
	sar	edx,31
	idiv	ecx
	mov	[DIY],eax		;;image y delta

	mov	esi,[colour_data.imageptr]
	mov	edx,[IX]
	mov	ebp,[IY]

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width
	or	ecx,[colour_data.imagexmask]
	dec	edi
	dec	edi
@@Loop:
	push	ecx
	mov	ebx,edx
	mov	eax,ebp
	and	ebx,ecx
	add	ebp,[dword ptr ds:DIY]
	shr	ebx,16
	and	eax,[colour_data.imageymask]
	mov	cl,[colour_data.imageyshift]
	inc	edi
	inc	edi
	shr	eax,cl
	add	edx,[dword ptr ds:DIX]
	add	ebx,eax
	mov	eax,[dword ptr ds:INTENS]
	xor	cx,cx
 	add	eax,[dword ptr ds:JITTER]
 	mov	ch,byte ptr ds:[esi+ebx]
  	shr	eax,16
 	shr	cx,4
	cmp	eax,0Fh
	mov	ebx,[dword ptr ds:DINTENS]
	jbe	short @@OKay
	mov	eax,0Fh
@@OKay:
 	or	ax,cx
	add	[dword ptr ds:INTENS],ebx
 	mov	ax,[word ptr ds:LandFadeData+eax*2]
	mov	bx,[word ptr ds:JITTER]
	pop	ecx
	add	bx,9136h
	ror	bx,3
 	mov	word ptr ds:[edi],ax
	dec	cx
	mov	[word ptr ds:JITTER],bx
	jnz	short @@Loop
@@Out:
	pop	ebp
	pop	edi
	pop	ecx
	ret
@@Fast:
	mov	eax,[esi+vertex.ix]	;;left vertex
	mov	[IX],eax
	sub	eax,[ebx+vertex.ix]	;;right vertex
	neg	eax
	mov	edx,eax
	sar	edx,31
	idiv	ecx
	mov	[DIX],eax		;;image x delta

	mov	eax,[esi+vertex.iy]	;;left vertex
	mov	[IY],eax
	sub	eax,[ebx+vertex.iy]	;;right vertex
	neg	eax
	mov	edx,eax
	sar	edx,31
	idiv	ecx
	mov	[DIY],eax		;;image y delta

	mov	esi,[colour_data.imageptr]
	mov	edx,[IX]
	mov	ebp,[IY]

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width
	or	ecx,[colour_data.imagexmask]
	dec	edi
	dec	edi
@@FLoop:
	push	ecx
	mov	ebx,edx
	mov	eax,ebp
	and	ebx,ecx
	add	ebp,[dword ptr ds:DIY]
	shr	ebx,16
	and	eax,[colour_data.imageymask]
	mov	cl,[colour_data.imageyshift]
	inc	edi
	inc	edi
	shr	eax,cl
	add	edx,[dword ptr ds:DIX]
	add	ebx,eax
	mov	eax,[INTENS]
	xor	cx,cx
 	add	eax,[dword ptr ds:JITTER]
	mov	ch,byte ptr ds:[esi+ebx]
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
	mov	ax,[word ptr ds:LandFadeData+2*eax]
	mov	[word ptr ds:JITTER],bx
	pop	ecx
	mov	word ptr ds:[edi],ax
	dec	cx
	jnz	short @@FLoop
	pop	ebp
	pop	edi
	pop	ecx
	ret
EndProc	ASM_SImageHoriLine1

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
	mov	ecx,[ebx+vertex.sx]	;;right vertex
	sar	ecx,17						;;PD 08Feb96
	mov	esi,edx
	mov	edi,[esi+vertex.sx]	;;left vertex
	sar	edi,17						;;PD 08Feb96
	sub	ecx,edi
	inc	ecx
	jle	@@Out

	mov	ebp,[esi+vertex.sy]
	add	edi,edi
	add	edi,edi
	add	edi,eax			;;start scr. adr.
;;	add	ebp,1024
	and ebp,0FFh
	mov	eax,[esi+vertex.intensity]
	lea	ebp,[LandFadeData+ebp]
	mov	[INTENS],eax
	mov	bp,word ptr ds:[ebp]				;;PD 16May96
	sub	eax,[ebx+vertex.intensity]
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

	mov	eax,[esi+vertex.ix]	;;left vertex
	mov	[IX],eax

	sub	eax,[ebx+vertex.ix]	;;right vertex
	neg	eax
	mov	edx,eax
	sar	edx,31
	idiv	ecx
	mov	[DIX],eax		;;image x delta

	mov	eax,[esi+vertex.iy]	;;left vertex
	mov	[IY],eax
	sub	eax,[ebx+vertex.iy]	;;right vertex
	neg	eax
	mov	edx,eax
	sar	edx,31
	idiv	ecx
	mov	[DIY],eax		;;image y delta

	mov	esi,[colour_data.imageptr]
	mov	edx,[IX]
	mov	ebp,[IY]

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width
	or	ecx,[colour_data.imagexmask]
	sub edi,4
@@Loop:
	push	ecx
	mov	ebx,edx
	mov	eax,ebp
	and	ebx,ecx
	add	ebp,[dword ptr ds:DIY]
	shr	ebx,16
	and	eax,[colour_data.imageymask]
	mov	cl,[colour_data.imageyshift]
	add edi,4
	shr	eax,cl
	add	edx,[dword ptr ds:DIX]
	add	ebx,eax
	mov	eax,[dword ptr ds:INTENS]
	xor	cx,cx
 	add	eax,[dword ptr ds:JITTER]
 	mov	ch,byte ptr ds:[esi+ebx]
  	shr	eax,16
 	shr	cx,4
	cmp	eax,0Fh
	mov	ebx,[dword ptr ds:DINTENS]
	jbe	short @@OKay
	mov	eax,0Fh
@@OKay:
 	or	ax,cx
	add	[dword ptr ds:INTENS],ebx
 	mov	ax,[word ptr ds:LandFadeData+eax*2]
	mov	bx,[word ptr ds:JITTER]
	pop	ecx
	add	bx,9136h
	ror	bx,3
 	mov	word ptr ds:[edi],ax
 	mov	word ptr ds:[edi+2],ax
	dec	cx
	mov	[word ptr ds:JITTER],bx
	jnz	@@Loop
@@Out:
	pop	ebp
	pop	edi
	pop	ecx
	ret
@@Fast:
	mov	eax,[esi+vertex.ix]	;;left vertex
	mov	[IX],eax
	sub	eax,[ebx+vertex.ix]	;;right vertex
	neg	eax
	mov	edx,eax
	sar	edx,31
	idiv	ecx
	mov	[DIX],eax		;;image x delta

	mov	eax,[esi+vertex.iy]	;;left vertex
	mov	[IY],eax
	sub	eax,[ebx+vertex.iy]	;;right vertex
	neg	eax
	mov	edx,eax
	sar	edx,31
	idiv	ecx
	mov	[DIY],eax		;;image y delta

	mov	esi,[colour_data.imageptr]
	mov	edx,[IX]
	mov	ebp,[IY]

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width
	or	ecx,[colour_data.imagexmask]
	sub edi,4
@@FLoop:
	push	ecx
	mov	ebx,edx
	mov	eax,ebp
	and	ebx,ecx
	add	ebp,[dword ptr ds:DIY]
	shr	ebx,16
	and	eax,[colour_data.imageymask]
	mov	cl,[colour_data.imageyshift]
	add edi,4
	shr	eax,cl
	add	edx,[dword ptr ds:DIX]
	add	ebx,eax
	mov	eax,[INTENS]
	xor	cx,cx
 	add	eax,[dword ptr ds:JITTER]
	mov	ch,byte ptr ds:[esi+ebx]
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
	mov	ax,[word ptr ds:LandFadeData+2*eax]
	mov	[word ptr ds:JITTER],bx
	pop	ecx
	mov	word ptr ds:[edi],ax
	mov	word ptr ds:[edi+2],ax
	dec	cx
	jnz	short @@FLoop
	pop	ebp
	pop	edi
	pop	ecx
	ret
EndProc	ASM_SImageHoriLine2

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_SImageHoriLine4
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
	mov	ecx,[ebx+vertex.sx]	;;right vertex
	sar	ecx,18						;;PD 08Feb96
	mov	esi,edx
	mov	edi,[esi+vertex.sx]	;;left vertex
	sar	edi,18						;;PD 08Feb96
	sub	ecx,edi
	inc	ecx
	jle	@@Out

	mov	ebp,[esi+vertex.sy]
	add	edi,edi
	add	edi,edi
	add	edi,edi
	add	edi,eax			;;start scr. adr.
	and ebp,0FFh
	mov	eax,[esi+vertex.intensity]
	lea	ebp,[LandFadeData+ebp]
	mov	[INTENS],eax
	mov	bp,word ptr ds:[ebp]				;;PD 16May96
	sub	eax,[ebx+vertex.intensity]
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

	mov	eax,[esi+vertex.ix]	;;left vertex
	mov	[IX],eax

	sub	eax,[ebx+vertex.ix]	;;right vertex
	neg	eax
	mov	edx,eax
	sar	edx,31
	idiv	ecx
	mov	[DIX],eax		;;image x delta

	mov	eax,[esi+vertex.iy]	;;left vertex
	mov	[IY],eax
	sub	eax,[ebx+vertex.iy]	;;right vertex
	neg	eax
	mov	edx,eax
	sar	edx,31
	idiv	ecx
	mov	[DIY],eax		;;image y delta

	mov	esi,[colour_data.imageptr]
	mov	edx,[IX]
	mov	ebp,[IY]

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width
	or	ecx,[colour_data.imagexmask]
	sub edi,8
@@Loop:
	push	ecx
	mov	ebx,edx
	mov	eax,ebp
	and	ebx,ecx
	add	ebp,[dword ptr ds:DIY]
	shr	ebx,16
	and	eax,[colour_data.imageymask]
	mov	cl,[colour_data.imageyshift]
	add edi,8
	shr	eax,cl
	add	edx,[dword ptr ds:DIX]
	add	ebx,eax
	mov	eax,[dword ptr ds:INTENS]
	xor	cx,cx
 	add	eax,[dword ptr ds:JITTER]
 	mov	ch,byte ptr ds:[esi+ebx]
  	shr	eax,16
 	shr	cx,4
	cmp	eax,0Fh
	mov	ebx,[dword ptr ds:DINTENS]
	jbe	short @@OKay
	mov	eax,0Fh
@@OKay:
 	or	ax,cx
	add	[dword ptr ds:INTENS],ebx
 	mov	ax,[word ptr ds:LandFadeData+eax*2]
	mov	bx,[word ptr ds:JITTER]
	pop	ecx
	add	bx,9136h
	ror	bx,3
 	mov	word ptr ds:[edi],ax
 	mov	word ptr ds:[edi+2],ax
 	mov	word ptr ds:[edi+4],ax
 	mov	word ptr ds:[edi+6],ax
	dec	cx
	mov	[word ptr ds:JITTER],bx
	jnz	@@Loop
@@Out:
	pop	ebp
	pop	edi
	pop	ecx
	ret
@@Fast:
	mov	eax,[esi+vertex.ix]	;;left vertex
	mov	[IX],eax
	sub	eax,[ebx+vertex.ix]	;;right vertex
	neg	eax
	mov	edx,eax
	sar	edx,31
	idiv	ecx
	mov	[DIX],eax		;;image x delta

	mov	eax,[esi+vertex.iy]	;;left vertex
	mov	[IY],eax
	sub	eax,[ebx+vertex.iy]	;;right vertex
	neg	eax
	mov	edx,eax
	sar	edx,31
	idiv	ecx
	mov	[DIY],eax		;;image y delta

	mov	esi,[colour_data.imageptr]
	mov	edx,[IX]
	mov	ebp,[IY]

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width
	or	ecx,[colour_data.imagexmask]
	sub edi,8
@@FLoop:
	push	ecx
	mov	ebx,edx
	mov	eax,ebp
	and	ebx,ecx
	add	ebp,[dword ptr ds:DIY]
	shr	ebx,16
	and	eax,[colour_data.imageymask]
	mov	cl,[colour_data.imageyshift]
	add edi,8
	shr	eax,cl
	add	edx,[dword ptr ds:DIX]
	add	ebx,eax
	mov	eax,[INTENS]
	xor	cx,cx
 	add	eax,[dword ptr ds:JITTER]
	mov	ch,byte ptr ds:[esi+ebx]
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
	mov	ax,[word ptr ds:LandFadeData+2*eax]
	mov	[word ptr ds:JITTER],bx
	pop	ecx
	mov	word ptr ds:[edi],ax
	mov	word ptr ds:[edi+2],ax
	mov	word ptr ds:[edi+4],ax
	mov	word ptr ds:[edi+6],ax
	dec	cx
	jnz	@@FLoop
	pop	ebp
	pop	edi
	pop	ecx
	ret
EndProc	ASM_SImageHoriLine4

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_CImageHoriLine1
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
	mov	ecx,[ebx+vertex.sx]	;;right vertex
	sar	ecx,16						;;PD 08Feb96
	mov	esi,edx
	mov	edi,[esi+vertex.sx]	;;left vertex
	sar	edi,16						;;PD 08Feb96
	sub	ecx,edi
	inc	ecx
	jle	@@Out

	mov	ebp,[esi+vertex.sy]
	add	edi,edi
	add	edi,eax			;;start scr. adr.
;;	add	ebp,1024
	and ebp,0FFh
	mov	eax,[esi+vertex.intensity]
	lea	ebp,[SkyFadeData+ebp]
	mov	[INTENS],eax
	mov	bp,word ptr ds:[ebp]				;;PD 16May96
	sub	eax,[ebx+vertex.intensity]
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

	mov	eax,[esi+vertex.ix]	;;left vertex
	mov	[IX],eax

	sub	eax,[ebx+vertex.ix]	;;right vertex
	neg	eax
	mov	edx,eax
	sar	edx,31
	idiv	ecx
	mov	[DIX],eax		;;image x delta

	mov	eax,[esi+vertex.iy]	;;left vertex
	mov	[IY],eax
	sub	eax,[ebx+vertex.iy]	;;right vertex
	neg	eax
	mov	edx,eax
	sar	edx,31
	idiv	ecx
	mov	[DIY],eax		;;image y delta

	mov	esi,[colour_data.imageptr]
	mov	edx,[IX]
	mov	ebp,[IY]

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width
	or	ecx,[colour_data.imagexmask]
	dec	edi
	dec	edi
@@Loop:
	push	ecx
	mov	ebx,edx
	mov	eax,ebp
	and	ebx,ecx
	add	ebp,[dword ptr ds:DIY]
	shr	ebx,16
	and	eax,[colour_data.imageymask]
	mov	cl,[colour_data.imageyshift]
	inc	edi
	inc	edi
	shr	eax,cl
	add	edx,[dword ptr ds:DIX]
	add	ebx,eax
	mov	eax,[dword ptr ds:INTENS]
	xor	cx,cx
 	add	eax,[dword ptr ds:JITTER]
 	mov	ch,byte ptr ds:[esi+ebx]
  	shr	eax,16
 	shr	cx,4
	cmp	eax,0Fh
	mov	ebx,[dword ptr ds:DINTENS]
	jbe	short @@OKay
	mov	eax,0Fh
@@OKay:
 	or	ax,cx
	add	[dword ptr ds:INTENS],ebx
 	mov	ax,[word ptr ds:SkyFadeData+eax*2]
	mov	bx,[word ptr ds:JITTER]
	pop	ecx
	add	bx,9136h
	ror	bx,3
 	mov	word ptr ds:[edi],ax
	dec	cx
	mov	[word ptr ds:JITTER],bx
	jnz	short @@Loop
@@Out:
	pop	ebp
	pop	edi
	pop	ecx
	ret
@@Fast:
	mov	eax,[esi+vertex.ix]	;;left vertex
	mov	[IX],eax
	sub	eax,[ebx+vertex.ix]	;;right vertex
	neg	eax
	mov	edx,eax
	sar	edx,31
	idiv	ecx
	mov	[DIX],eax		;;image x delta

	mov	eax,[esi+vertex.iy]	;;left vertex
	mov	[IY],eax
	sub	eax,[ebx+vertex.iy]	;;right vertex
	neg	eax
	mov	edx,eax
	sar	edx,31
	idiv	ecx
	mov	[DIY],eax		;;image y delta

	mov	esi,[colour_data.imageptr]
	mov	edx,[IX]
	mov	ebp,[IY]

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width
	or	ecx,[colour_data.imagexmask]
	dec	edi
	dec	edi
@@FLoop:
	push	ecx
	mov	ebx,edx
	mov	eax,ebp
	and	ebx,ecx
	add	ebp,[dword ptr ds:DIY]
	shr	ebx,16
	and	eax,[colour_data.imageymask]
	mov	cl,[colour_data.imageyshift]
	inc	edi
	inc	edi
	shr	eax,cl
	add	edx,[dword ptr ds:DIX]
	add	ebx,eax
	mov	eax,[INTENS]
	xor	cx,cx
 	add	eax,[dword ptr ds:JITTER]
	mov	ch,byte ptr ds:[esi+ebx]
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
	mov	ax,[word ptr ds:SkyFadeData+2*eax]
	mov	[word ptr ds:JITTER],bx
	pop	ecx
	mov	word ptr ds:[edi],ax
	dec	cx
	jnz	short @@FLoop
	pop	ebp
	pop	edi
	pop	ecx
	ret
EndProc	ASM_CImageHoriLine1

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_CImageHoriLine2
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
	mov	ecx,[ebx+vertex.sx]	;;right vertex
	sar	ecx,17						;;PD 08Feb96
	mov	esi,edx
	mov	edi,[esi+vertex.sx]	;;left vertex
	sar	edi,17						;;PD 08Feb96
	sub	ecx,edi
	inc	ecx
	jle	@@Out

	mov	ebp,[esi+vertex.sy]
	add	edi,edi
	add	edi,edi
	add	edi,eax			;;start scr. adr.
;;	add	ebp,1024
	and ebp,0FFh
	mov	eax,[esi+vertex.intensity]
	lea	ebp,[SkyFadeData+ebp]
	mov	[INTENS],eax
	mov	bp,word ptr ds:[ebp]				;;PD 16May96
	sub	eax,[ebx+vertex.intensity]
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

	mov	eax,[esi+vertex.ix]	;;left vertex
	mov	[IX],eax

	sub	eax,[ebx+vertex.ix]	;;right vertex
	neg	eax
	mov	edx,eax
	sar	edx,31
	idiv	ecx
	mov	[DIX],eax		;;image x delta

	mov	eax,[esi+vertex.iy]	;;left vertex
	mov	[IY],eax
	sub	eax,[ebx+vertex.iy]	;;right vertex
	neg	eax
	mov	edx,eax
	sar	edx,31
	idiv	ecx
	mov	[DIY],eax		;;image y delta

	mov	esi,[colour_data.imageptr]
	mov	edx,[IX]
	mov	ebp,[IY]

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width
	or	ecx,[colour_data.imagexmask]
	sub edi,4
@@Loop:
	push	ecx
	mov	ebx,edx
	mov	eax,ebp
	and	ebx,ecx
	add	ebp,[dword ptr ds:DIY]
	shr	ebx,16
	and	eax,[colour_data.imageymask]
	mov	cl,[colour_data.imageyshift]
	add edi,4
	shr	eax,cl
	add	edx,[dword ptr ds:DIX]
	add	ebx,eax
	mov	eax,[dword ptr ds:INTENS]
	xor	cx,cx
 	add	eax,[dword ptr ds:JITTER]
 	mov	ch,byte ptr ds:[esi+ebx]
  	shr	eax,16
 	shr	cx,4
	cmp	eax,0Fh
	mov	ebx,[dword ptr ds:DINTENS]
	jbe	short @@OKay
	mov	eax,0Fh
@@OKay:
 	or	ax,cx
	add	[dword ptr ds:INTENS],ebx
 	mov	ax,[word ptr ds:SkyFadeData+eax*2]
	mov	bx,[word ptr ds:JITTER]
	pop	ecx
	add	bx,9136h
	ror	bx,3
 	mov	word ptr ds:[edi],ax
 	mov	word ptr ds:[edi+2],ax
	dec	cx
	mov	[word ptr ds:JITTER],bx
	jnz	@@Loop
@@Out:
	pop	ebp
	pop	edi
	pop	ecx
	ret
@@Fast:
	mov	eax,[esi+vertex.ix]	;;left vertex
	mov	[IX],eax
	sub	eax,[ebx+vertex.ix]	;;right vertex
	neg	eax
	mov	edx,eax
	sar	edx,31
	idiv	ecx
	mov	[DIX],eax		;;image x delta

	mov	eax,[esi+vertex.iy]	;;left vertex
	mov	[IY],eax
	sub	eax,[ebx+vertex.iy]	;;right vertex
	neg	eax
	mov	edx,eax
	sar	edx,31
	idiv	ecx
	mov	[DIY],eax		;;image y delta

	mov	esi,[colour_data.imageptr]
	mov	edx,[IX]
	mov	ebp,[IY]

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width
	or	ecx,[colour_data.imagexmask]
	sub edi,4
@@FLoop:
	push	ecx
	mov	ebx,edx
	mov	eax,ebp
	and	ebx,ecx
	add	ebp,[dword ptr ds:DIY]
	shr	ebx,16
	and	eax,[colour_data.imageymask]
	mov	cl,[colour_data.imageyshift]
	add edi,4
	shr	eax,cl
	add	edx,[dword ptr ds:DIX]
	add	ebx,eax
	mov	eax,[INTENS]
	xor	cx,cx
 	add	eax,[dword ptr ds:JITTER]
	mov	ch,byte ptr ds:[esi+ebx]
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
	mov	ax,[word ptr ds:SkyFadeData+2*eax]
	mov	[word ptr ds:JITTER],bx
	pop	ecx
	mov	word ptr ds:[edi],ax
	mov	word ptr ds:[edi+2],ax
	dec	cx
	jnz	short @@FLoop
	pop	ebp
	pop	edi
	pop	ecx
	ret
EndProc	ASM_CImageHoriLine2

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_CImageHoriLine4
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
	mov	ecx,[ebx+vertex.sx]	;;right vertex
	sar	ecx,18						;;PD 08Feb96
	mov	esi,edx
	mov	edi,[esi+vertex.sx]	;;left vertex
	sar	edi,18						;;PD 08Feb96
	sub	ecx,edi
	inc	ecx
	jle	@@Out

	mov	ebp,[esi+vertex.sy]
	add	edi,edi
	add	edi,edi
	add	edi,edi
	add	edi,eax			;;start scr. adr.
	and ebp,0FFh
	mov	eax,[esi+vertex.intensity]
	lea	ebp,[SkyFadeData+ebp]
	mov	[INTENS],eax
	mov	bp,word ptr ds:[ebp]				;;PD 16May96
	sub	eax,[ebx+vertex.intensity]
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

	mov	eax,[esi+vertex.ix]	;;left vertex
	mov	[IX],eax

	sub	eax,[ebx+vertex.ix]	;;right vertex
	neg	eax
	mov	edx,eax
	sar	edx,31
	idiv	ecx
	mov	[DIX],eax		;;image x delta

	mov	eax,[esi+vertex.iy]	;;left vertex
	mov	[IY],eax
	sub	eax,[ebx+vertex.iy]	;;right vertex
	neg	eax
	mov	edx,eax
	sar	edx,31
	idiv	ecx
	mov	[DIY],eax		;;image y delta

	mov	esi,[colour_data.imageptr]
	mov	edx,[IX]
	mov	ebp,[IY]

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width
	or	ecx,[colour_data.imagexmask]
	sub edi,8
@@Loop:
	push	ecx
	mov	ebx,edx
	mov	eax,ebp
	and	ebx,ecx
	add	ebp,[dword ptr ds:DIY]
	shr	ebx,16
	and	eax,[colour_data.imageymask]
	mov	cl,[colour_data.imageyshift]
	add edi,8
	shr	eax,cl
	add	edx,[dword ptr ds:DIX]
	add	ebx,eax
	mov	eax,[dword ptr ds:INTENS]
	xor	cx,cx
 	add	eax,[dword ptr ds:JITTER]
 	mov	ch,byte ptr ds:[esi+ebx]
  	shr	eax,16
 	shr	cx,4
	cmp	eax,0Fh
	mov	ebx,[dword ptr ds:DINTENS]
	jbe	short @@OKay
	mov	eax,0Fh
@@OKay:
 	or	ax,cx
	add	[dword ptr ds:INTENS],ebx
 	mov	ax,[word ptr ds:SkyFadeData+eax*2]
	mov	bx,[word ptr ds:JITTER]
	pop	ecx
	add	bx,9136h
	ror	bx,3
 	mov	word ptr ds:[edi],ax
 	mov	word ptr ds:[edi+2],ax
 	mov	word ptr ds:[edi+4],ax
 	mov	word ptr ds:[edi+6],ax
	dec	cx
	mov	[word ptr ds:JITTER],bx
	jnz	@@Loop
@@Out:
	pop	ebp
	pop	edi
	pop	ecx
	ret
@@Fast:
	mov	eax,[esi+vertex.ix]	;;left vertex
	mov	[IX],eax
	sub	eax,[ebx+vertex.ix]	;;right vertex
	neg	eax
	mov	edx,eax
	sar	edx,31
	idiv	ecx
	mov	[DIX],eax		;;image x delta

	mov	eax,[esi+vertex.iy]	;;left vertex
	mov	[IY],eax
	sub	eax,[ebx+vertex.iy]	;;right vertex
	neg	eax
	mov	edx,eax
	sar	edx,31
	idiv	ecx
	mov	[DIY],eax		;;image y delta

	mov	esi,[colour_data.imageptr]
	mov	edx,[IX]
	mov	ebp,[IY]

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width
	or	ecx,[colour_data.imagexmask]
	sub edi,8
@@FLoop:
	push	ecx
	mov	ebx,edx
	mov	eax,ebp
	and	ebx,ecx
	add	ebp,[dword ptr ds:DIY]
	shr	ebx,16
	and	eax,[colour_data.imageymask]
	mov	cl,[colour_data.imageyshift]
	add edi,8
	shr	eax,cl
	add	edx,[dword ptr ds:DIX]
	add	ebx,eax
	mov	eax,[INTENS]
	xor	cx,cx
 	add	eax,[dword ptr ds:JITTER]
	mov	ch,byte ptr ds:[esi+ebx]
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
	mov	ax,[word ptr ds:SkyFadeData+2*eax]
	mov	[word ptr ds:JITTER],bx
	pop	ecx
	mov	word ptr ds:[edi],ax
	mov	word ptr ds:[edi+2],ax
	mov	word ptr ds:[edi+4],ax
	mov	word ptr ds:[edi+6],ax
	dec	cx
	jnz	@@FLoop
	pop	ebp
	pop	edi
	pop	ecx
	ret
EndProc	ASM_CImageHoriLine4

;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
;;	TRANSPARENT FADED IMAGE MAPPING SCAN LINE ROUTINES @ x1, x2 and x4 pixel rez.
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_TFImageHoriLine1
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Thu 14 Dec 1995
;;Modified
;;
;;Description
;;
;;Inputs	eax = screen ptr
;;			edx = left vertex
;;			ebx = right vertex
;;
;;Returns
;;
;;Externals
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
	push	ecx
	push	edi
	push	ebp
	mov	ecx,[ebx+vertex.sx]	;;right vertex
	sar ecx,10h
;;	mov	ebp,ecx
;;	and cl,07h
;;	mov [byte ptr ds:TSHIFT],cl
;;	mov	ecx,ebp
	mov	esi,edx
	mov	edi,[esi+vertex.sx]	;;left vertex
	sar	edi,16
	push eax
	mov ax,di
	and eax,07h
	mov al,[byte ptr ds:FUP+eax]
	mov [byte ptr ds:TSHIFT],al
	pop eax
	sub	ecx,edi
	inc	ecx
	jle	@@Out
	mov	edx,[esi+vertex.sy]
	and dl,07h
	mov [byte ptr ds:TOFF],dl
	add	edi,edi
	add	edi,eax			;;start scr. adr.
	mov	eax,[esi+vertex.intensity]
	mov	[INTENS],eax
	sub	eax,[ebx+vertex.intensity]
	mov	edx,eax
	neg	edx
	mov	eax,edx
	sar	edx,31
	idiv	ecx
	mov	[DINTENS],eax
	mov	eax,[esi+vertex.ix]	;;left vertex
	mov	[IX],eax
	sub	eax,[ebx+vertex.ix]	;;right vertex
	neg	eax
	mov	edx,eax
	sar	edx,31
	idiv	ecx
	mov	[DIX],eax		;;image x delta
	mov	eax,[esi+vertex.iy]	;;left vertex
	mov	[IY],eax
	sub	eax,[ebx+vertex.iy]	;;right vertex
	neg	eax
	mov	edx,eax
	sar	edx,31
	idiv	ecx
	mov	[DIY],eax		;;image y delta
	mov	esi,[colour_data.imageptr]
	mov	edx,[IX]
	mov	ebp,[IY]
;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width
	or	ecx,[colour_data.imagexmask]
	dec	edi
	dec	edi
@@Loop:
	push	ecx
	mov	ebx,edx
	mov	eax,ebp
	and	ebx,ecx
	add	ebp,[dword ptr ds:DIY]
	shr	ebx,16
	and	eax,[colour_data.imageymask]
	mov	cl,[colour_data.imageyshift]
	inc	edi
	inc	edi
	shr	eax,cl
	add	edx,[dword ptr ds:DIX]
	add	ebx,eax
	mov	eax,[dword ptr ds:INTENS]
	xor	cx,cx
 	mov	ch,byte ptr ds:[esi+ebx]
  	shr	eax,14
	and eax,078h
	cmp	eax,038h
	mov	ebx,[dword ptr ds:DINTENS]
	jbe	short @@OKay
	mov	eax,038h
@@OKay:
;;ch = colour index
;;eax = intensity value (0x00...0x38)
	add	[dword ptr ds:INTENS],ebx
	mov cl,[byte ptr ds:TSHIFT]
	inc cl
	test cl,08h
	jz short @@noreload
	mov cl,[byte ptr ds:TOFF]
	inc cl
	and cl,07h
	mov [byte ptr ds:TOFF],cl
	xor cl,cl
@@noreload:
	mov [byte ptr ds:TSHIFT],cl
	or	al,[byte ptr ds:TOFF]			;;current transp offset
	mov al,[byte ptr ds:TransparencyData+eax]
	shr al,cl
	test al,01h
	jz short @@nowrite
;;ch = colour index
	and ecx,0000FF00h
	shr ecx,7
	mov ax,[word ptr ds:palette_table+ecx]
	mov word ptr ds:[edi],ax
@@nowrite:
	pop	ecx
	dec	cx
	jnz	@@Loop
@@Out:
	pop	ebp
	pop	edi
	pop	ecx
	ret
EndProc	ASM_TFImageHoriLine1

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_TFImageHoriLine2
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Thu 14 Dec 1995
;;Modified
;;
;;Description
;;
;;Inputs	eax = screen ptr
;;			edx = left vertex
;;			ebx = right vertex
;;
;;Returns
;;
;;Externals
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
	push	ecx
	push	edi
	push	ebp
	mov	ecx,[ebx+vertex.sx]	;;right vertex
	sar ecx,11h
;;	mov	ebp,ecx
;;	and cl,07h
;;	mov [byte ptr ds:TSHIFT],cl
;;	mov	ecx,ebp
	mov	esi,edx
	mov	edi,[esi+vertex.sx]	;;left vertex
	sar	edi,17
	push eax
	mov ax,di
	and eax,07h
	mov al,[byte ptr ds:FUP+eax]
	mov [byte ptr ds:TSHIFT],al
	pop eax
	sub	ecx,edi
	inc	ecx
	jle	@@Out
	mov	edx,[esi+vertex.sy]
	and dl,07h
	mov [byte ptr ds:TOFF],dl
	add	edi,edi
	add	edi,edi
	add	edi,eax			;;start scr. adr.
	mov	eax,[esi+vertex.intensity]
	mov	[INTENS],eax
	sub	eax,[ebx+vertex.intensity]
	mov	edx,eax
	neg	edx
	mov	eax,edx
	sar	edx,31
	idiv	ecx
	mov	[DINTENS],eax
	mov	eax,[esi+vertex.ix]	;;left vertex
	mov	[IX],eax
	sub	eax,[ebx+vertex.ix]	;;right vertex
	neg	eax
	mov	edx,eax
	sar	edx,31
	idiv	ecx
	mov	[DIX],eax		;;image x delta
	mov	eax,[esi+vertex.iy]	;;left vertex
	mov	[IY],eax
	sub	eax,[ebx+vertex.iy]	;;right vertex
	neg	eax
	mov	edx,eax
	sar	edx,31
	idiv	ecx
	mov	[DIY],eax		;;image y delta
	mov	esi,[colour_data.imageptr]
	mov	edx,[IX]
	mov	ebp,[IY]
;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width
	or	ecx,[colour_data.imagexmask]
	sub edi,4
@@Loop:
	push	ecx
	mov	ebx,edx
	mov	eax,ebp
	and	ebx,ecx
	add	ebp,[dword ptr ds:DIY]
	shr	ebx,16
	and	eax,[colour_data.imageymask]
	mov	cl,[colour_data.imageyshift]
	add edi,4
	shr	eax,cl
	add	edx,[dword ptr ds:DIX]
	add	ebx,eax
	mov	eax,[dword ptr ds:INTENS]
	xor	cx,cx
 	mov	ch,byte ptr ds:[esi+ebx]
  	shr	eax,14
	and eax,078h
	cmp	eax,038h
	mov	ebx,[dword ptr ds:DINTENS]
	jbe	short @@OKay
	mov	eax,038h
@@OKay:
;;ch = colour index
;;eax = intensity value (0x00...0x38)
	add	[dword ptr ds:INTENS],ebx
	mov cl,[byte ptr ds:TSHIFT]
	inc cl
	test cl,08h
	jz short @@noreload
	mov cl,[byte ptr ds:TOFF]
	inc cl
	and cl,07h
	mov [byte ptr ds:TOFF],cl
	xor cl,cl
@@noreload:
	mov [byte ptr ds:TSHIFT],cl
	or	al,[byte ptr ds:TOFF]			;;current transp offset
	mov al,[byte ptr ds:TransparencyData+eax]
	shr al,cl
	test al,01h
	jz short @@nowrite
;;ch = colour index
	and ecx,0000FF00h
	shr ecx,7
	mov ax,[word ptr ds:palette_table+ecx]
	mov word ptr ds:[edi],ax
	mov word ptr ds:[edi+2],ax
@@nowrite:
	pop	ecx
	dec	cx
	jnz	@@Loop
@@Out:
	pop	ebp
	pop	edi
	pop	ecx
	ret
EndProc	ASM_TFImageHoriLine2

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_TFImageHoriLine4
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Thu 14 Dec 1995
;;Modified
;;
;;Description
;;
;;Inputs	eax = screen ptr
;;			edx = left vertex
;;			ebx = right vertex
;;
;;Returns
;;
;;Externals
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
	push	ecx
	push	edi
	push	ebp
	mov	ecx,[ebx+vertex.sx]	;;right vertex
	sar ecx,12h
;;	mov	ebp,ecx
;;	and cl,07h
;;	mov [byte ptr ds:TSHIFT],cl
;;	mov	ecx,ebp
	mov	esi,edx
	mov	edi,[esi+vertex.sx]	;;left vertex
	sar	edi,18
	push eax
	mov ax,di
	and eax,07h
	mov al,[byte ptr ds:FUP+eax]
	mov [byte ptr ds:TSHIFT],al
	pop eax
	sub	ecx,edi
	inc	ecx
	jle	@@Out
	mov	edx,[esi+vertex.sy]
	and dl,07h
	mov [byte ptr ds:TOFF],dl
	add	edi,edi
	add	edi,edi
	add	edi,edi
	add	edi,eax			;;start scr. adr.
	mov	eax,[esi+vertex.intensity]
	mov	[INTENS],eax
	sub	eax,[ebx+vertex.intensity]
	mov	edx,eax
	neg	edx
	mov	eax,edx
	sar	edx,31
	idiv	ecx
	mov	[DINTENS],eax
	mov	eax,[esi+vertex.ix]	;;left vertex
	mov	[IX],eax
	sub	eax,[ebx+vertex.ix]	;;right vertex
	neg	eax
	mov	edx,eax
	sar	edx,31
	idiv	ecx
	mov	[DIX],eax		;;image x delta
	mov	eax,[esi+vertex.iy]	;;left vertex
	mov	[IY],eax
	sub	eax,[ebx+vertex.iy]	;;right vertex
	neg	eax
	mov	edx,eax
	sar	edx,31
	idiv	ecx
	mov	[DIY],eax		;;image y delta
	mov	esi,[colour_data.imageptr]
	mov	edx,[IX]
	mov	ebp,[IY]
;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width
	or	ecx,[colour_data.imagexmask]
	sub edi,8
@@Loop:
	push	ecx
	mov	ebx,edx
	mov	eax,ebp
	and	ebx,ecx
	add	ebp,[dword ptr ds:DIY]
	shr	ebx,16
	and	eax,[colour_data.imageymask]
	mov	cl,[colour_data.imageyshift]
	add edi,8
	shr	eax,cl
	add	edx,[dword ptr ds:DIX]
	add	ebx,eax
	mov	eax,[dword ptr ds:INTENS]
	xor	cx,cx
 	mov	ch,byte ptr ds:[esi+ebx]
  	shr	eax,14
	and eax,078h
	cmp	eax,038h
	mov	ebx,[dword ptr ds:DINTENS]
	jbe	short @@OKay
	mov	eax,038h
@@OKay:
;;ch = colour index
;;eax = intensity value (0x00...0x38)
	add	[dword ptr ds:INTENS],ebx
	mov cl,[byte ptr ds:TSHIFT]
	inc cl
	test cl,08h
	jz short @@noreload
	mov cl,[byte ptr ds:TOFF]
	inc cl
	and cl,07h
	mov [byte ptr ds:TOFF],cl
	xor cl,cl
@@noreload:
	mov [byte ptr ds:TSHIFT],cl
	or	al,[byte ptr ds:TOFF]			;;current transp offset
	mov al,[byte ptr ds:TransparencyData+eax]
	shr al,cl
	test al,01h
	jz short @@nowrite
;;ch = colour index
	and ecx,0000FF00h
	shr ecx,7
	mov ax,[word ptr ds:palette_table+ecx]
	mov word ptr ds:[edi],ax
	mov word ptr ds:[edi+2],ax
	mov word ptr ds:[edi+4],ax
	mov word ptr ds:[edi+6],ax
@@nowrite:
	pop	ecx
	dec	cx
	jnz	@@Loop
@@Out:
	pop	ebp
	pop	edi
	pop	ecx
	ret
EndProc	ASM_TFImageHoriLine4

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_AImageHoriLine1
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Thu 14 Dec 1995
;;Modified
;;
;;Description
;;
;;Inputs	eax = screen ptr
;;			edx = left vertex
;;			ebx = right vertex
;;
;;Returns
;;
;;Externals
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
	push	ecx
	push	edi
	push	ebp
	mov	ecx,[ebx+vertex.sx]	;;right vertex
	mov	edi,[edx+vertex.sx]	;;left vertex
	add	ecx,10000h
	sar	edi,16
	push eax
	mov ax,di
	and eax,07h
	mov al,[byte ptr ds:FUP+eax]
	mov [byte ptr ds:TSHIFT],al
	pop eax
	sar	ecx,16
	mov	esi,edx
	sub	ecx,edi
	jle	@@Out
	add	edi,edi
	add	edi,eax			;;start scr. adr.
	mov	eax,[esi+vertex.ix]	;;left vertex
	mov	edx,[ebx+vertex.ix]	;;right vertex
	mov	[IX],eax
	sub	edx,eax
	mov	ebp,[esi+vertex.iy]
	mov eax,[esi+vertex.sy]
	and al,07h
	mov [byte ptr ds:TOFF],al
	mov	eax,edx
	sar	edx,31
	idiv	ecx
	mov	[IY],ebp
	mov	[DIX],eax		;;image x delta
	mov	edx,[ebx+vertex.iy]	;;right vertex
	mov	eax,ebp
	sub	edx,ebp
;;	jz	@@Horizontal
;;	cmp	edx,0fffeff9ah
;;	jl	short @@NotHorizontal
;;	cmp	edx,000010066h
;;	jle	@@Horizontal
;;@@NotHorizontal:
	mov	eax,edx
	mov	esi,[colour_data.imageptr]
	sar	edx,31
	idiv	ecx
	dec	edi
	dec	edi
	mov	[DIY],eax					;;image y delta
	mov	edx,[IX]

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width

@@Loop:
	push	ecx
	mov	ebx,[colour_data.imagexmask]
	mov	eax,[DIX]
	and	ebx,edx
	add	edx,eax
	mov	ecx,[colour_data.imageymask]
	mov	eax,ebp
	mov	cl,[colour_data.imageyshift]
	shr	ebx,16
	and	eax,ecx
	shr	eax,cl
	inc	edi
	inc	edi
	mov	ecx,[DIY]
	add	ebx,eax
	add	ebp,ecx
	mov esi,[colour_data.alphaptr]
	mov eax,[dword ptr esi+ebx]
	sar eax,5-3
	and eax,38h
	mov cl,[byte ptr ds:TSHIFT]
	inc cl
	test cl,08h
	jz short @@noreload
	mov cl,[byte ptr ds:TOFF]
	inc cl
	and cl,07h
	mov [byte ptr ds:TOFF],cl
	xor cl,cl
@@noreload:
	mov [byte ptr ds:TSHIFT],cl
	or al,[byte ptr ds:TOFF]
	mov al,[byte ptr ds:TransparencyData+eax]
	shr al,cl
	test al,01h
	pop	ecx
	jz short @@nowrite
	mov esi,[colour_data.imageptr]
	mov	eax,[dword ptr esi+ebx]
	and eax,0FFh
	add ax,ax
	mov ax,[palette_table+eax]
	mov	word ptr [edi],ax
@@nowrite:
	dec	ecx
	jnz	@@Loop
@@Out:
	pop	ebp
	pop	edi
	pop	ecx
	ret
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


@@Horizontal:
	mov	esi,[colour_data.imageptr]
	or	ecx,[colour_data.imagexmask]
	mov	edx,[IX]
	push	ecx
	and	ebp,[colour_data.imageymask]
	mov	cl,[colour_data.imageyshift]
	shr	ebp,cl
	pop	ecx
	add	esi,ebp
	dec	edi
	dec	edi
	mov	ebp,[DIX]
@@Loop2:
	mov	ebx,edx
	add	edx,ebp
	and	ebx,ecx
	inc	edi
	inc	edi
	shr	ebx,16
	mov	bl,byte ptr [esi+ebx]
	and ebx,0FFh
	add bx,bx
	dec	cx
	mov bx,[palette_table+ebx]
	mov	word ptr [edi],bx
	jnz	short @@Loop2
	pop	ebp
	pop	edi
	pop	ecx
	ret
EndProc	ASM_AImageHoriLine1

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_AImageHoriLine2
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Thu 14 Dec 1995
;;Modified
;;
;;Description
;;
;;Inputs	eax = screen ptr
;;			edx = left vertex
;;			ebx = right vertex
;;
;;Returns
;;
;;Externals
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
	push	ecx
	push	edi
	push	ebp
	mov	ecx,[ebx+vertex.sx]	;;right vertex
	mov	edi,[edx+vertex.sx]	;;left vertex
	add	ecx,20000h
	sar	edi,17
	push eax
	mov ax,di
	and eax,07h
	mov al,[byte ptr ds:FUP+eax]
	mov [byte ptr ds:TSHIFT],al
	pop eax
	sar	ecx,17
	mov	esi,edx
	sub	ecx,edi
	jle	@@Out
	add	edi,edi
	add	edi,edi
	add	edi,eax			;;start scr. adr.
	mov	eax,[esi+vertex.ix]	;;left vertex
	mov	edx,[ebx+vertex.ix]	;;right vertex
	mov	[IX],eax
	sub	edx,eax
	mov	ebp,[esi+vertex.iy]
	mov eax,[esi+vertex.sy]
	and al,07h
	mov [byte ptr ds:TOFF],al
	mov	eax,edx
	sar	edx,31
	idiv	ecx
	mov	[IY],ebp
	mov	[DIX],eax		;;image x delta
	mov	edx,[ebx+vertex.iy]	;;right vertex
	mov	eax,ebp
	sub	edx,ebp
	mov	eax,edx
	mov	esi,[colour_data.imageptr]
	sar	edx,31
	idiv	ecx
	sub edi,4
	mov	[DIY],eax					;;image y delta
	mov	edx,[IX]

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width

@@Loop:
	push	ecx
	mov	ebx,[colour_data.imagexmask]
	mov	eax,[DIX]
	and	ebx,edx
	add	edx,eax
	mov	ecx,[colour_data.imageymask]
	mov	eax,ebp
	mov	cl,[colour_data.imageyshift]
	shr	ebx,16
	and	eax,ecx
	shr	eax,cl
	add edi,4
	mov	ecx,[DIY]
	add	ebx,eax
	add	ebp,ecx
	mov esi,[colour_data.alphaptr]
	mov eax,[dword ptr esi+ebx]
	sar eax,5-3
	and eax,38h
	mov cl,[byte ptr ds:TSHIFT]
	inc cl
	test cl,08h
	jz short @@noreload
	mov cl,[byte ptr ds:TOFF]
	inc cl
	and cl,07h
	mov [byte ptr ds:TOFF],cl
	xor cl,cl
@@noreload:
	mov [byte ptr ds:TSHIFT],cl
	or al,[byte ptr ds:TOFF]
	mov al,[byte ptr ds:TransparencyData+eax]
	shr al,cl
	test al,01h
	pop	ecx
	jz short @@nowrite
	mov esi,[colour_data.imageptr]
	mov	eax,[dword ptr esi+ebx]
	and eax,0FFh
	add ax,ax
	mov ax,[palette_table+eax]
	mov	word ptr [edi],ax
	mov	word ptr [edi+2],ax
@@nowrite:
	dec	ecx
	jnz	@@Loop
@@Out:
	pop	ebp
	pop	edi
	pop	ecx
	ret
EndProc	ASM_AImageHoriLine2

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_AImageHoriLine4
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Thu 14 Dec 1995
;;Modified
;;
;;Description
;;
;;Inputs	eax = screen ptr
;;			edx = left vertex
;;			ebx = right vertex
;;
;;Returns
;;
;;Externals
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
	push	ecx
	push	edi
	push	ebp
	mov	ecx,[ebx+vertex.sx]	;;right vertex
	mov	edi,[edx+vertex.sx]	;;left vertex
	add	ecx,40000h
	sar	edi,18
	push eax
	mov ax,di
	and eax,07h
	mov al,[byte ptr ds:FUP+eax]
	mov [byte ptr ds:TSHIFT],al
	pop eax
	sar	ecx,18
	mov	esi,edx
	sub	ecx,edi
	jle	@@Out
	add	edi,edi
	add	edi,edi
	add	edi,edi
	add	edi,eax			;;start scr. adr.
	mov	eax,[esi+vertex.ix]	;;left vertex
	mov	edx,[ebx+vertex.ix]	;;right vertex
	mov	[IX],eax
	sub	edx,eax
	mov	ebp,[esi+vertex.iy]
	mov eax,[esi+vertex.sy]
	and al,07h
	mov [byte ptr ds:TOFF],al
	mov	eax,edx
	sar	edx,31
	idiv	ecx
	mov	[IY],ebp
	mov	[DIX],eax		;;image x delta
	mov	edx,[ebx+vertex.iy]	;;right vertex
	mov	eax,ebp
	sub	edx,ebp
	mov	eax,edx
	mov	esi,[colour_data.imageptr]
	sar	edx,31
	idiv	ecx
	sub edi,8
	mov	[DIY],eax					;;image y delta
	mov	edx,[IX]

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width

@@Loop:
	push	ecx
	mov	ebx,[colour_data.imagexmask]
	mov	eax,[DIX]
	and	ebx,edx
	add	edx,eax
	mov	ecx,[colour_data.imageymask]
	mov	eax,ebp
	mov	cl,[colour_data.imageyshift]
	shr	ebx,16
	and	eax,ecx
	shr	eax,cl
	add edi,8
	mov	ecx,[DIY]
	add	ebx,eax
	add	ebp,ecx
	mov esi,[colour_data.alphaptr]
	mov eax,[dword ptr esi+ebx]
	sar eax,5-3
	and eax,38h
	mov cl,[byte ptr ds:TSHIFT]
	inc cl
	test cl,08h
	jz short @@noreload
	mov cl,[byte ptr ds:TOFF]
	inc cl
	and cl,07h
	mov [byte ptr ds:TOFF],cl
	xor cl,cl
@@noreload:
	mov [byte ptr ds:TSHIFT],cl
	or al,[byte ptr ds:TOFF]
	mov al,[byte ptr ds:TransparencyData+eax]
	shr al,cl
	test al,01h
	pop	ecx
	jz short @@nowrite
	mov esi,[colour_data.imageptr]
	mov	eax,[dword ptr esi+ebx]
	and eax,0FFh
	add ax,ax
	mov ax,[palette_table+eax]
	mov	word ptr [edi],ax
	mov	word ptr [edi+2],ax
	mov	word ptr [edi+4],ax
	mov	word ptr [edi+6],ax
@@nowrite:
	dec	ecx
	jnz	@@Loop
@@Out:
	pop	ebp
	pop	edi
	pop	ecx
	ret
EndProc	ASM_AImageHoriLine4

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
	int	3
	push	ecx
	push	edi
	mov	ecx,[ebx+vertex.sx]	;;right vertex
	sar	ecx,16						;;PD 08Feb96
	mov	esi,edx
	mov	edi,[esi+vertex.sx]	;;left vertex
	sar	edi,16						;;PD 08Feb96
	sub	ecx,edi
	inc	ecx
	jle	@@Out
	add	edi,eax			;;start scr. adr.

	xor	ebx,ebx
	mov	bl,[byte ptr colour_data.col]	;;PD 08Jan96
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
EndProc	ASM_GPlainHoriLine1

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
	int	3
	push	ecx
	push	edi
	mov	ecx,[ebx+vertex.sx]	;;right vertex
	sar	ecx,17						;;PD 08Feb96
	mov	esi,edx
	mov	edi,[esi+vertex.sx]	;;left vertex
	sar	edi,17						;;PD 08Feb96
	sub	ecx,edi
	inc	ecx
	jle	@@Out
	add	edi,edi
	add	edi,eax			;;start scr. adr.

	xor	ebx,ebx
	mov	bl,[byte ptr colour_data.col]	;;PD 08Jan96
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
EndProc	ASM_GPlainHoriLine2


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
	int	3
	push	eax
	push	ecx
	push	edx
	push	esi
	push	edi
	push	ebp
	mov	esi,edx
	mov	ecx,[ebx+vertex.sx]	;;right vertex
	mov	edi,[esi+vertex.sx]	;;left vertex
	add	ecx,10000h
	sar	edi,16
	sar	ecx,16
	mov	ebp,[esi+vertex.sy]
	sub	ecx,edi
	jle	@@Out
	add	edi,eax			;;start scr. adr.
	mov	eax,[esi+vertex.intensity]
	add	ebp,1024
	mov	[INTENS],eax
	add	ebp,[colour_data.aliastblptr]
	mov	edx,[ebx+vertex.intensity]
	mov	ebp,dword ptr ds:[ebp]
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
	mov	ah,[byte ptr colour_data.col]
	and	ebp,0FFFFh
	shr	eax,4
 	add	edx,ebp
	inc	edi
	shr	edx,16
	add	bp,9136h
	or	eax,edx
	ror	bp,3
	mov	edx,[DINTENS]
	mov	al,[byte ptr LandFadeData+eax]
	mov	byte ptr [edi],al
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
EndProc	ASM_GGouraudHoriLine1


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
	int	3
	push	eax
	push	ecx
	push	edx
	push	esi
	push	edi
	push	ebp
	mov	esi,edx
	mov	ecx,[ebx+vertex.sx]	;;right vertex
	mov	edi,[esi+vertex.sx]	;;left vertex
	sar	ecx,17
	sar	edi,17
	sub	ecx,edi
	inc	ecx
	jle	@@Out
	mov	ebp,[esi+vertex.sy]
	add	edi,edi
	add	ebp,1024
	add	edi,eax			;;start scr. adr.
	add	ebp,[colour_data.aliastblptr]
	mov	eax,[esi+vertex.intensity]
	mov	bp,word ptr ds:[ebp]
	mov	[INTENS],eax
	mov	[word ptr ds:JITTER],bp
	sub	eax,[ebx+vertex.intensity]
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
	mov	ah,[byte ptr colour_data.col]
 	add	edx,[dword ptr ds:JITTER]
	shr	ax,4
	mov	bp,[word ptr ds:JITTER]
	shr	edx,16
	add	bp,9136h
	inc	edi
	ror	bp,3
	or	ax,dx
	mov	[word ptr ds:JITTER],bp
	mov	al,[byte ptr ds:LandFadeData+eax]
	mov	edx,[dword ptr ds:DINTENS]
	xor	ah,ah
	add	[dword ptr ds:INTENS],edx
	mov	al,[Grey3DTable+eax]
	inc	edi
	mov	ah,al
	dec	ecx
	mov	word ptr ds:[edi],ax
	jnz	short @@Loop
@@Out:
	pop	ebp
	pop	edi
	pop	esi
	pop	edx
	pop	ecx
	pop	eax
	ret
EndProc	ASM_GGouraudHoriLine2


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
	int	3
	push	ecx
	push	edi
	push	ebp
	mov	ecx,[ebx+vertex.sx]	;;right vertex
	sar	ecx,16						;;PD 08Feb96
	mov	esi,edx
	mov	edi,[esi+vertex.sx]	;;left vertex
	sar	edi,16						;;PD 08Feb96
	sub	ecx,edi
	inc	ecx
	jle	@@Out
	add	edi,eax			;;start scr. adr.

	mov	eax,[esi+vertex.ix]	;;left vertex
	mov	[IX],eax
	sub	eax,[ebx+vertex.ix]	;;right vertex
	neg	eax
	;;cdq							;;PD 12Feb96
	mov	edx,eax
	sar	edx,01fh
	idiv	ecx
	mov	[DIX],eax		;;image x delta

	mov	eax,[esi+vertex.iy]	;;left vertex
	mov	[IY],eax
	sub	eax,[ebx+vertex.iy]	;;right vertex
	neg	eax
	;;cdq							;;PD 12Feb96
	mov	edx,eax
	sar	edx,01fh
	idiv	ecx
	mov	[DIY],eax		;;image y delta

	mov	esi,[colour_data.imageptr]
	mov	edx,[IX]
	mov	ebp,[IY]

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width
	or	ecx,[colour_data.imagexmask]

;;DeadCode PD 10Jun96 	ALIGN	16
@@Loop:
	push	cx
	mov	ebx,edx
	and	ebx,ecx
	shr	ebx,16
	mov	eax,ebp
	and	eax,[colour_data.imageymask]
	mov	cl,[colour_data.imageyshift]
	shr	eax,cl
	add	ebx,eax
	xor	eax,eax						;;PD 02Apr96
	mov	al,byte ptr ds:[esi+ebx]			;;PD 02Apr96
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
EndProc	ASM_GImageHoriLine1

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
	int	3
	push	ecx
	push	edi
	push	ebp
	mov	ecx,[ebx+vertex.sx]	;;right vertex
	sar	ecx,17						;;PD 08Feb96
	mov	esi,edx
	mov	edi,[esi+vertex.sx]	;;left vertex
	sar	edi,17						;;PD 08Feb96
	sub	ecx,edi
	inc	ecx
	jle	@@Out
	add	edi,edi
	add	edi,eax			;;start scr. adr.

	mov	eax,[esi+vertex.ix]	;;left vertex
	mov	[IX],eax
	sub	eax,[ebx+vertex.ix]	;;right vertex
	neg	eax
	;;cdq							;;PD 12Feb96
	mov	edx,eax
	sar	edx,01fh
	idiv	ecx
	mov	[DIX],eax		;;image x delta

	mov	eax,[esi+vertex.iy]	;;left vertex
	mov	[IY],eax
	sub	eax,[ebx+vertex.iy]	;;right vertex
	neg	eax
	;;cdq							;;PD 12Feb96
	mov	edx,eax
	sar	edx,01fh
	idiv	ecx
	mov	[DIY],eax		;;image y delta

	mov	esi,[colour_data.imageptr]
	mov	edx,[IX]
	mov	ebp,[IY]

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width
	or	ecx,[colour_data.imagexmask]

;;DeadCode PD 10Jun96 	ALIGN	16
@@Loop:
	push	cx
	mov	ebx,edx
	and	ebx,ecx
	shr	ebx,16
	mov	eax,ebp
	and	eax,[colour_data.imageymask]
	mov	cl,[colour_data.imageyshift]
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
EndProc	ASM_GImageHoriLine2



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
	int	3
	push	ecx
	push	edi
	push	ebp
	mov	ecx,[ebx+vertex.sx]	;;right vertex
	sar	ecx,16						;;PD 08Feb96
	mov	esi,edx
	mov	edi,[esi+vertex.sx]	;;left vertex
	sar	edi,16						;;PD 08Feb96
	sub	ecx,edi
	inc	ecx
	jle	@@Out
	add	edi,eax			;;start scr. adr.

	mov	eax,[esi+vertex.ix]	;;left vertex
	mov	[IX],eax
	sub	eax,[ebx+vertex.ix]	;;right vertex
	neg	eax
	;;cdq							;;PD 12Feb96
	mov	edx,eax
	sar	edx,01fh
	idiv	ecx
	mov	[DIX],eax		;;image x delta

	mov	eax,[esi+vertex.iy]	;;left vertex
	mov	[IY],eax
	sub	eax,[ebx+vertex.iy]	;;right vertex
	neg	eax
	;;cdq							;;PD 12Feb96
	mov	edx,eax
	sar	edx,01fh
	idiv	ecx
	mov	[DIY],eax		;;image y delta

	mov	esi,[colour_data.imageptr]
	mov	edx,[IX]
	mov	ebp,[IY]

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width
	or	ecx,[colour_data.imagexmask]

;;DeadCode PD 10Jun96 	ALIGN	16
@@Loop:
	push	cx
	mov	ebx,edx
	and	ebx,ecx
	shr	ebx,16
	mov	eax,ebp
	and	eax,[colour_data.imageymask]
	mov	cl,[colour_data.imageyshift]
	shr	eax,cl
	add	ebx,eax
	xor	eax,eax						;;PD 02Apr96
	mov	al,byte ptr ds:[esi+ebx]			;;PD 02Apr96
	cmp	al,0FEh						;;PD 03Apr96
	jz	short @@MaskByte				;;PD 03Apr96
	mov	al,[Grey3DTable+eax]				;;PD 02Apr96
	mov	byte ptr ds:[edi],al
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
EndProc	ASM_GMImageHoriLine1

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
	int	3
	push	ecx
	push	edi
	push	ebp
	mov	ecx,[ebx+vertex.sx]	;;right vertex
	sar	ecx,17						;;PD 08Feb96
	mov	esi,edx
	mov	edi,[esi+vertex.sx]	;;left vertex
	sar	edi,17						;;PD 08Feb96
	sub	ecx,edi
	inc	ecx
	jle	@@Out
	add	edi,edi
	add	edi,eax			;;start scr. adr.

	mov	eax,[esi+vertex.ix]	;;left vertex
	mov	[IX],eax
	sub	eax,[ebx+vertex.ix]	;;right vertex
	neg	eax
	;;cdq							;;PD 12Feb96
	mov	edx,eax
	sar	edx,01fh
	idiv	ecx
	mov	[DIX],eax		;;image x delta

	mov	eax,[esi+vertex.iy]	;;left vertex
	mov	[IY],eax
	sub	eax,[ebx+vertex.iy]	;;right vertex
	neg	eax
	;;cdq							;;PD 12Feb96
	mov	edx,eax
	sar	edx,01fh
	idiv	ecx
	mov	[DIY],eax		;;image y delta

	mov	esi,[colour_data.imageptr]
	mov	edx,[IX]
	mov	ebp,[IY]

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width
	or	ecx,[colour_data.imagexmask]

;;DeadCode PD 10Jun96 	ALIGN	16
@@Loop:
	push	cx
	mov	ebx,edx
	and	ebx,ecx
	shr	ebx,16
	mov	eax,ebp
	and	eax,[colour_data.imageymask]
	mov	cl,[colour_data.imageyshift]
	shr	eax,cl
	add	ebx,eax
	mov	bl,[esi+ebx]
	cmp	bl,0FEh						;;PD 03Apr96
	jz	short @@MaskByte				;;PD 03Apr96
	movzx	ebx,bl
	mov	al,[Grey3DTable+ebx]
	mov	ah,al
	mov	word ptr ds:[edi],ax
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
EndProc	ASM_GMImageHoriLine2



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
	int	3
	push	ecx
	push	edi
	push	ebp
	mov	ecx,[ebx+vertex.sx]	;;right vertex
	sar	ecx,16						;;PD 08Feb96
	mov	esi,edx
	mov	edi,[esi+vertex.sx]	;;left vertex
	sar	edi,16						;;PD 08Feb96
	sub	ecx,edi
	inc	ecx
	jle	@@Out
	add	edi,eax			;;start scr. adr.

	mov	eax,[esi+vertex.intensity]
	mov	[INTENS],eax
	sub	eax,[ebx+vertex.intensity]
	neg	eax
	;;cdq							;;PD 12Feb96
	mov	edx,eax
	sar	edx,01fh
	idiv	ecx
	mov	[DINTENS],eax

	mov	eax,[esi+vertex.ix]	;;left vertex
	mov	[IX],eax
	sub	eax,[ebx+vertex.ix]	;;right vertex
	neg	eax
	;;cdq							;;PD 12Feb96
	mov	edx,eax
	sar	edx,01fh
	idiv	ecx
	mov	[DIX],eax		;;image x delta

	mov	eax,[esi+vertex.iy]	;;left vertex
	mov	[IY],eax
	sub	eax,[ebx+vertex.iy]	;;right vertex
	neg	eax
	;;cdq							;;PD 12Feb96
	mov	edx,eax
	sar	edx,01fh
	idiv	ecx
	mov	[DIY],eax		;;image y delta

	mov	esi,[colour_data.imageptr]
	mov	edx,[IX]
	mov	ebp,[IY]

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width
	or	ecx,[colour_data.imagexmask]

;;DeadCode PD 10Jun96 	ALIGN	16
@@Loop:
	push	cx
	mov	ebx,edx
	and	ebx,ecx
	shr	ebx,16
	mov	eax,ebp
	and	eax,[colour_data.imageymask]
	mov	cl,[colour_data.imageyshift]
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
EndProc	ASM_GSImageHoriLine1

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
	int	3
	push	ecx
	push	edi
	push	ebp
	mov	ecx,[ebx+vertex.sx]	;;right vertex
	sar	ecx,17						;;PD 08Feb96
	mov	esi,edx
	mov	edi,[esi+vertex.sx]	;;left vertex
	sar	edi,17						;;PD 08Feb96
	sub	ecx,edi
	inc	ecx
	jle	@@Out
	add	edi,edi
	add	edi,eax			;;start scr. adr.

	mov	eax,[esi+vertex.intensity]
	mov	[INTENS],eax
	sub	eax,[ebx+vertex.intensity]
	neg	eax
	;;cdq							;;PD 12Feb96
	mov	edx,eax
	sar	edx,01fh
	idiv	ecx
	mov	[DINTENS],eax

	mov	eax,[esi+vertex.ix]	;;left vertex
	mov	[IX],eax
	sub	eax,[ebx+vertex.ix]	;;right vertex
	neg	eax
	;;cdq							;;PD 12Feb96
	mov	edx,eax
	sar	edx,01fh
	idiv	ecx
	mov	[DIX],eax		;;image x delta

	mov	eax,[esi+vertex.iy]	;;left vertex
	mov	[IY],eax
	sub	eax,[ebx+vertex.iy]	;;right vertex
	neg	eax
	;;cdq							;;PD 12Feb96
	mov	edx,eax
	sar	edx,01fh
	idiv	ecx
	mov	[DIY],eax		;;image y delta

	mov	esi,[colour_data.imageptr]
	mov	edx,[IX]
	mov	ebp,[IY]

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width
	or	ecx,[colour_data.imagexmask]

;;DeadCode PD 10Jun96 	ALIGN	16
@@Loop:
	push	cx
	mov	ebx,edx
	and	ebx,ecx
	shr	ebx,16
	mov	eax,ebp
	and	eax,[colour_data.imageymask]
	mov	cl,[colour_data.imageyshift]
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
EndProc	ASM_GSImageHoriLine2



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
	int	3
	push	ecx
	push	edi
	push	ebp
	mov	ecx,[ebx+vertex.sx]	;;right vertex
	sar	ecx,16						;;PD 08Feb96
	mov	esi,edx
	mov	edi,[esi+vertex.sx]	;;left vertex
	sar	edi,16						;;PD 08Feb96
	sub	ecx,edi
	inc	ecx
	jle	@@Out
	add	edi,eax			;;start scr. adr.

	mov	eax,[esi+vertex.ix]	;;left vertex
	mov	[IX],eax
	sub	eax,[ebx+vertex.ix]	;;right vertex
	neg	eax
	;;cdq							;;PD 12Feb96
	mov	edx,eax
	sar	edx,01fh
	idiv	ecx
	mov	[DIX],eax		;;image x delta

	mov	eax,[esi+vertex.iy]	;;left vertex
	mov	[IY],eax
	sub	eax,[ebx+vertex.iy]	;;right vertex
	neg	eax
	;;cdq							;;PD 12Feb96
	mov	edx,eax
	sar	edx,01fh
	idiv	ecx
	mov	[DIY],eax		;;image y delta

	mov	esi,[colour_data.imageptr]
	mov	edx,[IX]
	mov	ebp,[IY]

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width
	or	ecx,[colour_data.imagexmask]

;;DeadCode PD 10Jun96 	ALIGN	16
@@Loop:
	push	cx
	mov	ebx,edx
	and	ebx,ecx
	shr	ebx,16
	mov	eax,ebp
	and	eax,[colour_data.imageymask]
	mov	cl,[colour_data.imageyshift]
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
EndProc	ASM_OImageHoriLine1

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
	int	3
	push	ecx
	push	edi
	push	ebp
	mov	ecx,[ebx+vertex.sx]	;;right vertex
	sar	ecx,16						;;PD 08Feb96
	mov	esi,edx
	mov	edi,[esi+vertex.sx]	;;left vertex
	sar	edi,16						;;PD 08Feb96
	sub	ecx,edi
	inc	ecx
	jle	@@Out
	add	edi,eax			;;start scr. adr.

	mov	eax,[esi+vertex.ix]	;;left vertex
	mov	[IX],eax
	sub	eax,[ebx+vertex.ix]	;;right vertex
	neg	eax
	;;cdq							;;PD 12Feb96
	mov	edx,eax
	sar	edx,01fh
	idiv	ecx
	mov	[DIX],eax		;;image x delta

	mov	eax,[esi+vertex.iy]	;;left vertex
	mov	[IY],eax
	sub	eax,[ebx+vertex.iy]	;;right vertex
	neg	eax
	;;cdq							;;PD 12Feb96
	mov	edx,eax
	sar	edx,01fh
	idiv	ecx
	mov	[DIY],eax		;;image y delta

	mov	esi,[colour_data.imageptr]
	mov	edx,[IX]
	mov	ebp,[IY]

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width
	or	ecx,[colour_data.imagexmask]

;;DeadCode PD 10Jun96 	ALIGN	16
@@Loop:
	push	cx
	mov	ebx,edx
	and	ebx,ecx
	shr	ebx,16
	mov	eax,ebp
	and	eax,[colour_data.imageymask]
	mov	cl,[colour_data.imageyshift]
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
EndProc	ASM_OMImageHoriLine1

	ALIGN	2

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_TLPlainHoriLine1
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
	int	3
	push	ecx
	push	edi
	push	ebx
	mov	ecx,[ebx+vertex.sx]	;;right vertex
	sar	ecx,16						;;PD 08Feb96
	mov	esi,edx
	mov	edi,[esi+vertex.sx]	;;left vertex
	sar	edi,16						;;PD 08Feb96
	sub	ecx,edi
	inc	ecx
	jle	@@Out
	add	edi,eax			;;start scr. adr.

	xor	eax,eax
	mov	ah,[byte ptr colour_data.col]
	sub	ah,240
	mov	ebx,[colour_data.lumtblptr]

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width
@@Loop:								;;PD 23Feb96
	mov	al,byte ptr ds:[edi]
	mov	al,byte ptr ds:[ebx+eax]
	mov	byte ptr ds:[edi],al				;;PD 23Feb96
	inc	edi						;;PD 23Feb96
	dec	cx						;;PD 23Feb96
	jnz	short @@Loop					;;PD 23Feb96
@@Out:
	pop	ebx
	pop	edi
	pop	ecx
	ret
EndProc	ASM_TLPlainHoriLine1

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_TLMImageHoriLine1
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
	int	3
	push	ecx
	push	edi
	push	ebp
	mov	esi,edx
	mov	ecx,[ebx+vertex.sx]	;;right vertex
	mov	edi,[esi+vertex.sx]	;;left vertex
	add	ecx,10000h
	sar	edi,16						;;PD 08Feb96
	sar	ecx,16						;;PD 08Feb96
	sub	ecx,edi
	jle	@@Out
	add	edi,eax			;;start scr. adr.
	mov	eax,[esi+vertex.ix]	;;left vertex
	mov	edx,[ebx+vertex.ix]	;;right vertex
	mov	[IX],eax
	sub	edx,eax
	mov	eax,edx
	sar	edx,31
	idiv	ecx
	mov	[DIX],eax		;;image x delta
	mov	eax,[esi+vertex.iy]	;;left vertex
	mov	edx,[ebx+vertex.iy]	;;right vertex
	mov	[IY],eax
	sub	edx,eax
	mov	eax,edx
	sar	edx,31
	idiv	ecx
	mov	[DIY],eax		;;image y delta
	or	ecx,[colour_data.imagexmask]
	mov	esi,[colour_data.imageptr]
	mov	edx,[IX]
	mov	ebp,[IY]

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width

@@Loop:
	push	ecx
	mov	eax,ebp
	mov	ebx,edx
	and	eax,[colour_data.imageymask]
	and	ebx,ecx
	shr	ebx,16
	mov	cl,[colour_data.imageyshift]
	shr	eax,cl
	add	ebx,eax
	xor	eax,eax
	pop	ecx
	add	edx,[DIX]
	mov	ah,[esi+ebx]
	mov	ebx,[colour_data.lumtblptr]
	sub	ah,240
	mov	al,byte ptr [edi]
	mov	al,byte ptr [ebx+eax]
	add	ebp,[DIY]
	mov	byte ptr [edi],al
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
EndProc	ASM_TLMImageHoriLine1

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
	int	3
	push	ecx
	push	edi
	push	ebx
	mov	ecx,[ebx+vertex.sx]	;;right vertex
	sar	ecx,16						;;PD 08Feb96
	mov	esi,edx
	mov	edi,[esi+vertex.sx]	;;left vertex
	sar	edi,16						;;PD 08Feb96
	sub	ecx,edi
	inc	ecx
	jle	@@Out
	add	edi,eax			;;start scr. adr.

	xor	eax,eax
	mov	ah,[byte ptr colour_data.col]
	mov	ebx,[colour_data.aliastblptr]

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width
@@Loop:								;;PD 23Feb96
	mov	al,byte ptr ds:[edi]
	mov	al,byte ptr ds:[ebx+eax]
	mov	byte ptr ds:[edi],al				;;PD 23Feb96
	inc	edi						;;PD 23Feb96
	dec	cx						;;PD 23Feb96
	jnz	short @@Loop					;;PD 23Feb96
@@Out:
	pop	ebx
	pop	edi
	pop	ecx
	ret
EndProc	ASM_TIPlainHoriLine1

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
	int	3
	push	ecx
	push	edi
	push	ebx
	mov	ecx,[ebx+vertex.sx]	;;right vertex
	sar	ecx,17						;;PD 08Feb96
	mov	esi,edx
	mov	edi,[esi+vertex.sx]	;;left vertex
	sar	edi,17						;;PD 08Feb96
	sub	ecx,edi
	inc	ecx
	jle	@@Out
	add	edi,edi
	add	edi,eax			;;start scr. adr.

	xor	eax,eax
	mov	ah,[byte ptr colour_data.col]
	mov	ebx,[colour_data.aliastblptr]

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width
;;eax = colour.b, colour.b, colour.b, colour.b
@@Loop:
	mov	al,byte ptr ds:[edi]
	mov	al,byte ptr ds:[ebx+eax]
	mov	byte ptr ds:[edi],al
	mov	byte ptr ds:[edi+1],al
	inc	edi
	inc	edi
	dec	cx
	jnz	short @@Loop
@@Out:
	pop	ebx
	pop	edi
	pop	ecx
	ret
EndProc	ASM_TIPlainHoriLine2


;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_HHPlainHoriLine1
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
	int	3
	push	ecx
	push	edi
	push	ebx
	push	edx
	mov	esi,[ebx+vertex.sx]	;;right vertex
	sar	esi,16
	mov	ecx,edx
	mov	edi,[ecx+vertex.sx]	;;left vertex
	sar	edi,16
	sub	esi,edi
	sar	esi,2				;;RJS 18Feb98
	inc	esi
	jle	@@Out
	add	edi,eax			;;start scr. adr.

	xor	eax,eax
	mov	ebx,[colour_data.aliastblptr]
	mov	ecx,[dword ptr colour_data.col]
	ror	[dword ptr colour_data.col],2
  	and 	edi,-4						;;RJS 18Feb98
  	and 	ecx,30h						;;RJS 18Feb98

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width
@@Loop:
	mov	edx,dword ptr ds:[edi]				;;RJS 18Feb98
	ror	edx,cl
	and	edx,0ffffh
	add	edi,4						;;RJS 18Feb98
	mov	al,byte ptr ds:[ebx+edx]			;;RJS 18Feb98
	mov	ah,al						;;RJS 18Feb98
	mov	edx,eax						;;RJS 18Feb98
	sal	edx,16						;;RJS 18Feb98
	add	edx,eax						;;RJS 18Feb98
	dec	esi						;;RJS 18Feb98
	mov	dword ptr ds:[edi-4],edx			;;RJS 18Feb98
	jnz	short @@Loop
@@Out:
	pop	edx
	pop	ebx
	pop	edi
	pop	ecx
	ret
EndProc	ASM_HHPlainHoriLine1


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
	int	3
	push	ecx
	push	edi
	push	ebx
	mov	ecx,[ebx+vertex.sx]	;;right vertex
	sar	ecx,16						;;PD 08Feb96
	mov	esi,edx
	mov	edi,[esi+vertex.sx]	;;left vertex
	sar	edi,16						;;PD 08Feb96
	sub	ecx,edi
	inc	ecx
	jle	@@Out
	add	edi,eax			;;start scr. adr.

	xor	eax,eax
	mov	al,[byte ptr colour_data.col]
	mov	ebx,[colour_data.aliastblptr]

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width
@@Loop:								;;PD 23Feb96
	mov	ah,byte ptr ds:[edi]
	mov	ah,byte ptr ds:[ebx+eax]
	mov	byte ptr ds:[edi],ah				;;PD 23Feb96
	inc	edi						;;PD 23Feb96
	dec	cx						;;PD 23Feb96
	jnz	short @@Loop					;;PD 23Feb96
@@Out:
	pop	ebx
	pop	edi
	pop	ecx
	ret
EndProc	ASM_TPlainHoriLine1

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
	int	3
	push	ecx
	push	edi
	push	ebx
	mov	ecx,[ebx+vertex.sx]	;;right vertex
	sar	ecx,17						;;PD 08Feb96
	mov	esi,edx
	mov	edi,[esi+vertex.sx]	;;left vertex
	sar	edi,17						;;PD 08Feb96
	sub	ecx,edi
	inc	ecx
	jle	@@Out
	add	edi,edi
	add	edi,eax			;;start scr. adr.

	xor	eax,eax
	mov	al,[byte ptr colour_data.col]
	mov	ebx,[colour_data.aliastblptr]

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width
;;eax = colour.b, colour.b, colour.b, colour.b
@@Loop:
	mov	ah,byte ptr ds:[edi]
	mov	ah,byte ptr ds:[ebx+eax]
	mov	byte ptr ds:[edi],ah
	mov	byte ptr ds:[edi+1],ah
	inc	edi
	inc	edi
	dec	cx
	jnz	short @@Loop
@@Out:
	pop	ebx
	pop	edi
	pop	ecx
	ret
EndProc	ASM_TPlainHoriLine2



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
	int	3
	push	ecx
	push	edi
	push	ebp
	mov	esi,edx
	mov	ecx,[ebx+vertex.sx]	;;right vertex
	mov	edi,[esi+vertex.sx]	;;left vertex
	add	ecx,10000h
	sar	edi,16						;;PD 08Feb96
	sar	ecx,16						;;PD 08Feb96
	sub	ecx,edi
	jle	@@Out
	add	edi,eax			;;start scr. adr.
	mov	eax,[esi+vertex.ix]	;;left vertex
	mov	edx,[ebx+vertex.ix]	;;right vertex
	mov	[IX],eax
	sub	edx,eax
	mov	eax,edx
	sar	edx,31
	idiv	ecx
	mov	[DIX],eax		;;image x delta
	mov	eax,[esi+vertex.iy]	;;left vertex
	mov	edx,[ebx+vertex.iy]	;;right vertex
	mov	[IY],eax
	sub	edx,eax
	mov	eax,edx
	sar	edx,31
	idiv	ecx
	mov	[DIY],eax		;;image y delta
	or	ecx,[colour_data.imagexmask]
	mov	esi,[colour_data.imageptr]
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
	and	eax,[colour_data.imageymask]
	and	ebx,ecx
	shr	ebx,16
	mov	cl,[colour_data.imageyshift]
	shr	eax,cl
	add	ebx,eax
	xor	eax,eax
	pop	ecx
	add	edx,[DIX]
	mov	al,[esi+ebx]
	mov	ebx,[colour_data.aliastblptr]
;;DeadCode RJS 11Jul97 	cmp	al,0FEh
	mov	ah,byte ptr [edi]
;;DeadCode RJS 11Jul97 	jz	short @@MaskByte
	mov	al,byte ptr [ebx+eax]
	add	ebp,[DIY]
	mov	byte ptr [edi],al
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
EndProc	ASM_TMImageHoriLine1


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
	int	3
	push	ecx
	push	edi
	push	ebp
	mov	esi,edx
	mov	ecx,[ebx+vertex.sx]	;;right vertex
	mov	edi,[esi+vertex.sx]	;;left vertex
	add	ecx,20000h
	sar	edi,17						;;PD 08Feb96
	sar	ecx,17						;;PD 08Feb96
	sub	ecx,edi
	jle	@@Out
	add	edi,edi
	add	edi,eax			;;start scr. adr.
	mov	eax,[esi+vertex.ix]	;;left vertex
	mov	edx,[ebx+vertex.ix]	;;right vertex
	mov	[IX],eax
	sub	edx,eax
	mov	eax,edx
	sar	edx,31
	idiv	ecx
	mov	[DIX],eax		;;image x delta
	mov	eax,[esi+vertex.iy]	;;left vertex
	mov	edx,[ebx+vertex.iy]	;;right vertex
	mov	[IY],eax
	sub	edx,eax
	mov	eax,edx
	sar	edx,31
	idiv	ecx
	mov	[DIY],eax		;;image y delta
	or	ecx,[colour_data.imagexmask]
	mov	esi,[colour_data.imageptr]
	mov	edx,[IX]
	mov	ebp,[IY]

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width

@@Loop:
	push	ecx
	mov	eax,ebp
	mov	ebx,edx
	and	eax,[colour_data.imageymask]
	and	ebx,ecx
	shr	ebx,16
	mov	cl,[colour_data.imageyshift]
	shr	eax,cl
	add	ebx,eax
	xor	eax,eax
	pop	ecx
	add	edx,[DIX]
	mov	al,[esi+ebx]
	mov	ebx,[colour_data.aliastblptr]
;;DeadCode RJS 11Jul97 	cmp	al,0FEh
	mov	ah,byte ptr [edi]
;;DeadCode RJS 11Jul97 	jz	short @@MaskByte
	mov	al,byte ptr [ebx+eax]
	add	ebp,[DIY]
	mov	byte ptr [edi],al
	mov	byte ptr [edi+1],al
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
EndProc	ASM_TMImageHoriLine2


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
	int	3
	push	ecx
	push	edi
	push	ebp
	mov	esi,edx
	mov	ecx,[ebx+vertex.sx]	;;right vertex
	mov	edi,[esi+vertex.sx]	;;left vertex
	add	ecx,10000h
	sar	edi,16						;;PD 08Feb96
	sar	ecx,16						;;PD 08Feb96
	sub	ecx,edi
	jle	@@Out
	add	edi,eax			;;start scr. adr.
	mov	eax,[esi+vertex.ix]	;;left vertex
	mov	edx,[ebx+vertex.ix]	;;right vertex
	mov	[IX],eax
	sub	edx,eax
	mov	eax,edx
	sar	edx,31
	idiv	ecx
	mov	[DIX],eax		;;image x delta
	mov	eax,[esi+vertex.iy]	;;left vertex
	mov	edx,[ebx+vertex.iy]	;;right vertex
	mov	[IY],eax
	sub	edx,eax
	mov	eax,edx
	sar	edx,31
	idiv	ecx
	mov	[DIY],eax		;;image y delta
	or	ecx,[colour_data.imagexmask]
	mov	esi,[colour_data.imageptr]
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
	and	eax,[colour_data.imageymask]
	and	ebx,ecx
	shr	ebx,16
	mov	cl,[colour_data.imageyshift]
	shr	eax,cl
	add	ebx,eax
	xor	eax,eax
	pop	ecx
	add	edx,[DIX]
	mov	ah,[esi+ebx]
	mov	ebx,[colour_data.aliastblptr]
;;DeadCode RJS 11Jul97  	cmp	ah,0FEh
	mov	al,byte ptr [edi]
;;DeadCode RJS 11Jul97 	jz	short @@MaskByte
	mov	al,byte ptr [ebx+eax]
	add	ebp,[DIY]
	mov	byte ptr [edi],al
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
EndProc	ASM_TIMImageHoriLine1


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
	int	3
	push	ecx
	push	edi
	push	ebp
	mov	esi,edx
	mov	ecx,[ebx+vertex.sx]	;;right vertex
	mov	edi,[esi+vertex.sx]	;;left vertex
	add	ecx,20000h
	sar	edi,17						;;PD 08Feb96
	sar	ecx,17						;;PD 08Feb96
	sub	ecx,edi
	jle	@@Out
	add	edi,edi
	add	edi,eax			;;start scr. adr.
	mov	eax,[esi+vertex.ix]	;;left vertex
	mov	edx,[ebx+vertex.ix]	;;right vertex
	mov	[IX],eax
	sub	edx,eax
	mov	eax,edx
	sar	edx,31
	idiv	ecx
	mov	[DIX],eax		;;image x delta
	mov	eax,[esi+vertex.iy]	;;left vertex
	mov	edx,[ebx+vertex.iy]	;;right vertex
	mov	[IY],eax
	sub	edx,eax
	mov	eax,edx
	sar	edx,31
	idiv	ecx
	mov	[DIY],eax		;;image y delta
	or	ecx,[colour_data.imagexmask]
	mov	esi,[colour_data.imageptr]
	mov	edx,[IX]
	mov	ebp,[IY]

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width

@@Loop:
	push	ecx
	mov	eax,ebp
	mov	ebx,edx
	and	eax,[colour_data.imageymask]
	and	ebx,ecx
	shr	ebx,16
	mov	cl,[colour_data.imageyshift]
	shr	eax,cl
	add	ebx,eax
	xor	eax,eax
	pop	ecx
	add	edx,[DIX]
	mov	ah,[esi+ebx]
	mov	ebx,[colour_data.aliastblptr]
;;DeadCode RJS 11Jul97 	cmp	ah,0FEh
	mov	al,byte ptr [edi]
;;DeadCode RJS 11Jul97 	jz	short @@MaskByte
	mov	al,byte ptr [ebx+eax]
	add	ebp,[DIY]
	mov	byte ptr [edi],al
	mov	byte ptr [edi+1],al
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
EndProc	ASM_TIMImageHoriLine2



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
;;TEMP01	int	3
	mov	[ds:Trns3DEnabled],ax
	ret
EndProc	ASM_SetTransparency

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_SetLuminosity
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
;;TEMP01	int	3
	mov	[ds:Lum3DEnabled],al
	ret
EndProc	ASM_SetLuminosity

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_SetHeatHaze
;;------------------------------------------------------------------------------
;;Author	Rob.
;;Date		Fri 30 Jan 1998
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
;;TEMP01	int	3
	mov	[ds:Haze3DEnabled],al
	ret
EndProc	ASM_SetHeatHaze

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_GetTransparency
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
;;TEMP01	int	3
	mov	ax,[ds:Trns3DEnabled]
	ret
EndProc	ASM_GetTransparency


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
	int	3
	push	eax
	push	ecx
	push	edx
	push	esi
	push	edi
	push	ebp
	mov	esi,edx
	mov	ecx,[ebx+vertex.sx]	;;right vertex
	mov	edi,[esi+vertex.sx]	;;left vertex
	sar	ecx,16						;;PD 08Feb96
	sar	edi,16						;;PD 08Feb96
	sub	ecx,edi
	inc	ecx
	jle	@@Out
	add	edi,eax			;;start scr. adr.
	mov	eax,[esi+vertex.intensity]
	mov	[INTENS],eax
	sub	eax,[ebx+vertex.intensity]
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
	mov	ah,[byte ptr colour_data.col]
	shr	edx,16
	shr	ax,4
	inc	edi
	or	ax,dx
	add	ebp,[dword ptr ds:DINTENS]
	mov	al,[byte ptr ds:LandFadeData+eax]
	dec	ecx
	mov	byte ptr ds:[edi],al
	jnz	short @@Loop
@@Out:
	pop	ebp
	pop	edi
	pop	esi
	pop	edx
	pop	ecx
	pop	eax
	ret
EndProc	ASM_NDGHoriLine1

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
	int	3
	push	ecx
	push	edi
	push	ebp
	mov	ecx,[ebx+vertex.sx]	;;right vertex
	sar	ecx,16						;;PD 08Feb96
	mov	esi,edx
	mov	edi,[esi+vertex.sx]	;;left vertex
	sar	edi,16						;;PD 08Feb96
	sub	ecx,edi
	inc	ecx
	jle	@@Out

	add	edi,eax			;;start scr. adr.

	mov	eax,[esi+vertex.intensity]
	mov	[INTENS],eax
	sub	eax,[ebx+vertex.intensity]
	neg	eax

	mov	edx,eax
	sar	edx,01fh
	idiv	ecx
	mov	[DINTENS],eax

	mov	eax,[esi+vertex.ix]	;;left vertex
	mov	[IX],eax					;;PD 15May96

	sub	eax,[ebx+vertex.ix]	;;right vertex
	neg	eax
	mov	edx,eax
	sar	edx,01fh
	idiv	ecx
	mov	[DIX],eax		;;image x delta

	mov	eax,[esi+vertex.iy]	;;left vertex
	mov	[IY],eax
	sub	eax,[ebx+vertex.iy]	;;right vertex
	neg	eax
	mov	edx,eax
	sar	edx,01fh
	idiv	ecx
	mov	[DIY],eax		;;image y delta

	mov	esi,[colour_data.imageptr]
	mov	edx,[IX]
	mov	ebp,[IY]

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width
	or	ecx,[colour_data.imagexmask]
	dec	edi
@@Loop:
	push	ecx
	mov	ebx,edx
	mov	eax,ebp
	and	ebx,ecx
	add	ebp,[dword ptr ds:DIY]
	shr	ebx,16
	and	eax,[colour_data.imageymask]
	mov	cl,[colour_data.imageyshift]
	inc	edi
	shr	eax,cl
	add	edx,[dword ptr ds:DIX]
	add	ebx,eax
	mov	eax,[dword ptr ds:INTENS]
	xor	cx,cx
	mov	ch,byte ptr ds:[esi+ebx]
	shr	eax,16
	shr	cx,4
	mov	ebx,[dword ptr ds:DINTENS]
	or	ax,cx
	add	[dword ptr ds:INTENS],ebx
	mov	al,[ds:LandFadeData+eax]
	pop	ecx
	mov	byte ptr ds:[edi],al
	dec	cx
	jnz	short @@Loop
@@Out:
	pop	ebp
    	pop	edi
	pop	ecx
	ret
EndProc	ASM_NDSIHoriLine1

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
	int	3
	push	eax
	push	ecx
	push	edx
	push	esi
	push	edi
	push	ebp
	mov	esi,edx
	mov	ecx,[ebx+vertex.sx]	;;right vertex
	mov	edi,[esi+vertex.sx]	;;left vertex
	sar	ecx,17
	sar	edi,17
	sub	ecx,edi
	inc	ecx
	jle	@@Out
	add	edi,edi
	add	edi,eax			;;start scr. adr.
	mov	eax,[esi+vertex.intensity]
	mov	[INTENS],eax
	sub	eax,[ebx+vertex.intensity]
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
	mov	ah,[byte ptr colour_data.col]
	shr	ax,4
	shr	edx,16
	inc	edi
	or	ax,dx
	add	ebp,[dword ptr ds:DINTENS]
	mov	al,[byte ptr ds:LandFadeData+eax]
	inc	edi
	mov	ah,al
	dec	ecx
	mov	word ptr ds:[edi],ax
	jnz	short @@Loop
@@Out:
	pop	ebp
	pop	edi
	pop	esi
	pop	edx
	pop	ecx
	pop	eax
	ret
EndProc	ASM_NDGHoriLine2
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
	int	3
	push	ecx
	push	edi
	push	ebp
	mov	ecx,[ebx+vertex.sx]	;;right vertex
	sar	ecx,17						;;PD 08Feb96
	mov	esi,edx
	mov	edi,[esi+vertex.sx]	;;left vertex
	sar	edi,17						;;PD 08Feb96
	sub	ecx,edi
	inc	ecx
	jle	@@Out
	add	edi,edi

	add	edi,eax			;;start scr. adr.
	mov	eax,[esi+vertex.intensity]
	mov	[INTENS],eax
	sub	eax,[ebx+vertex.intensity]

	mov	edx,eax
	xor	ax,ax
	test	eax,eax
	jz	@@Fast
	neg	edx
	mov	eax,edx
	sar	edx,31
	idiv	ecx
	mov	[DINTENS],eax

	mov	eax,[esi+vertex.ix]	;;left vertex
	mov	[IX],eax

	sub	eax,[ebx+vertex.ix]	;;right vertex
	neg	eax
	mov	edx,eax
	sar	edx,31
	idiv	ecx
	mov	[DIX],eax		;;image x delta

	mov	eax,[esi+vertex.iy]	;;left vertex
	mov	[IY],eax
	sub	eax,[ebx+vertex.iy]	;;right vertex
	neg	eax
	mov	edx,eax
	sar	edx,31
	idiv	ecx
	mov	[DIY],eax		;;image y delta

	mov	esi,[colour_data.imageptr]
	mov	edx,[IX]
	mov	ebp,[IY]

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width
	or	ecx,[colour_data.imagexmask]
	sub	edi,2
@@Loop:
	push	ecx
	mov	ebx,edx
	mov	eax,ebp
	and	ebx,ecx
	add	ebp,[dword ptr ds:DIY]
	shr	ebx,16
	and	eax,[colour_data.imageymask]
	mov	cl,[colour_data.imageyshift]
	inc	edi
	shr	eax,cl
	add	edx,[dword ptr ds:DIX]
	inc	edi
	add	ebx,eax
	mov	eax,[dword ptr ds:INTENS]
	xor	cx,cx
 	mov	ch,byte ptr ds:[esi+ebx]
  	shr	eax,16
 	shr	cx,4
	cmp	eax,0Fh
	mov	ebx,[dword ptr ds:DINTENS]
	jbe	short @@OKay
	mov	eax,0Fh
@@OKay:
 	or	ax,cx
	add	[dword ptr ds:INTENS],ebx
 	mov	al,[ds:LandFadeData+eax]
	pop	ecx
 	mov	ah,al
	dec	cx
 	mov	word ptr ds:[edi],ax
	jnz	short @@Loop
@@Out:
	pop	ebp
	pop	edi
	pop	ecx
	ret
@@Fast:
	mov	eax,[esi+vertex.ix]	;;left vertex
	mov	[IX],eax
	sub	eax,[ebx+vertex.ix]	;;right vertex
	neg	eax
	mov	edx,eax
	sar	edx,31
	idiv	ecx
	mov	[DIX],eax		;;image x delta

	mov	eax,[esi+vertex.iy]	;;left vertex
	mov	[IY],eax
	sub	eax,[ebx+vertex.iy]	;;right vertex
	neg	eax
	mov	edx,eax
	sar	edx,31
	idiv	ecx
	mov	[DIY],eax		;;image y delta

	mov	esi,[colour_data.imageptr]
	mov	edx,[IX]
	mov	ebp,[IY]

;;edi = screen ptr
;;esi = image map data ptr
;;ecx = line width
	or	ecx,[colour_data.imagexmask]
	sub	edi,2
@@FLoop:
	push	ecx
	mov	ebx,edx
	mov	eax,ebp
	and	ebx,ecx
	add	ebp,[dword ptr ds:DIY]
	shr	ebx,16
	and	eax,[colour_data.imageymask]
	mov	cl,[colour_data.imageyshift]
	add	edi,2
	shr	eax,cl
	add	edx,[dword ptr ds:DIX]
	add	ebx,eax
	xor	cx,cx
	mov	eax,[INTENS]
	mov	ch,byte ptr ds:[esi+ebx]
	shr	eax,16
	shr	cx,4
	cmp	eax,0Fh
	jbe	short @@OKay2
	mov	eax,0Fh
@@OKay2:
	or	ax,cx
	mov	al,[ds:LandFadeData+eax]
	pop	ecx
	mov	ah,al
	dec	cx
	mov	word ptr ds:[edi],ax
	jnz	short @@FLoop
	pop	ebp
	pop	edi
	pop	ecx
	ret
EndProc	ASM_NDSIHoriLine2
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
	int	3
	push	eax
	push	ecx
	push	edx
	push	esi
	push	edi
	push	ebp
	mov	esi,edx
	mov	ecx,[ebx+vertex.sx]	;;right vertex
	mov	edi,[esi+vertex.sx]	;;left vertex
	sar	ecx,16						;;PD 08Feb96
	sar	edi,16						;;PD 08Feb96
	sub	ecx,edi
	inc	ecx
	jle	@@Out
	add	edi,eax			;;start scr. adr.
	mov	ebp,[esi+vertex.sy]
	mov	eax,[esi+vertex.intensity]
	add	ebp,1024
	mov	[INTENS],eax
	sub	eax,[ebx+vertex.intensity]
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
	mov	ah,[byte ptr colour_data.col]
	shr	edx,16
	shr	ax,4
	inc	edi
	or	ax,dx
	add	ebp,[dword ptr ds:DINTENS]
	mov	al,[byte ptr ds:LandFadeData+eax]
	xor	ah,ah
	mov	al,[Grey3DTable+eax]
	dec	ecx
	mov	byte ptr ds:[edi],al
	jnz	short @@Loop
@@Out:
	pop	ebp
	pop	edi
	pop	esi
	pop	edx
	pop	ecx
	pop	eax
	ret
EndProc	ASM_GNDGHoriLine1

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
	int	3
	push	eax
	push	ebx
	push	ecx
	push	edx
	push	esi
	push	edi
	mov	[dword ptr ds:ScreenStart],ebx
	mov	[dword ptr ds:BytesPerScanLine],ecx
	mov	esi,dword ptr ds:[eax+4]
	mov	edi,dword ptr ds:[edx+4]
	mov	[dword ptr ds:Y1],esi
	mov	[dword ptr ds:Y2],edi
	mov	eax,dword ptr ds:[eax]
	mov	ebx,dword ptr ds:[edx]
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
;;TEMPCODE	mov	eax,[colour_data.col]
	mov	al,[colour_data.col]
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
;;TEMPCODE	mov	eax,[colour_data.col]
	mov	al,[colour_data.col]
@@L5:	add	edi,edx
	dec	ecx
	mov	byte ptr ds:[edi],al
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
;;TEMPCODE	mov	eax,[colour_data.col]
	mov	al,[colour_data.col]
	add	edi,edx
	mov	byte ptr ds:[edi],al			;;plot start pixel

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
	mov	byte ptr ds:[edi],al
	jnz	short @@L9
	jmp	short @@L11
@@L10:	inc	[dword ptr ds:SX]
	inc	edi
	add	esi,[dword ptr ds:Const2]
	dec	ecx
	mov	byte ptr ds:[edi],al
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
	mov	byte ptr ds:[edi],al
	jnz	short @@L12
	jmp	short @@L14
@@L13:	dec	[dword ptr ds:SX]
	dec	edi
	add	esi,[dword ptr ds:Const2]
	dec	ecx
	mov	byte ptr ds:[edi],al
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
;;TEMPCODE	mov	eax,[colour_data.col]
	mov	al,[colour_data.col]
@@L8:	add	edi,edx
	dec	ecx
	mov	byte ptr ds:[edi],al
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
;;TEMPCODE	mov	eax,[colour_data.col]
	mov	al,[colour_data.col]
	add	edi,edx
	mov	byte ptr ds:[edi],al			;;plot start pixel


	pop	edi
	pop	esi
	pop	edx
	pop	ecx
	pop	ebx
	pop	eax
	ret
EndProc	ASM_PlainLine

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_NullScanLine
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Thu 17 Oct 1996
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

	int	3
	ret
EndProc	ASM_NullScanLine


	_TEXT	ENDS

;;ends
end
