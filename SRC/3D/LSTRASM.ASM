;;------------------------------------------------------------------------------
;;Module	lstrasm.asm
;;System
;;Author	Paul.
;;Date		Tue 22 Oct 1996
;;Description
;;------------------------------------------------------------------------------
;;	IDeal
;;	LOCALS	@@
;;p386
;;	INCLUDE "STRUCM.INC"

Procedure	Macro	name
			_X&name&	Proc
			public	_X&name&
			endm

EndProc		Macro	name
			_X&name&	EndP
			endm
.386

	_DATA SEGMENT PAGE PUBLIC USE32 'DATA'

DestBytesPerScanLine	Equ	257
RoadColoursMask		Equ	0f0h

RoadColoursEnd		Equ	16

RoadColoursTR 		Equ	0
RoadColoursBL 		Equ	1
RoadColoursBR		Equ	2

	ALIGN	4

srcptr		dd	?
destptr		dd	?
ailclrindexp	dd	?
ailtbl16p	dd	?

	_DATA	ENDS

	DGROUP	GROUP	_DATA

	_TEXT SEGMENT PAGE PUBLIC USE32 'CODE'

	ASSUME	CS:_TEXT, DS:DGROUP

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_WidenRoutes
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Tue 22 Oct 1996
;;Modified
;;
;;Description
;;
;;Inputs	eax = ptr src 257x257 tile
;;
;;Returns
;;
;;Externals
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
;;Widen the routes
	push	eax
	push	ebx
	push	ecx
	push	edx
	push	esi

	mov	ecx,DestBytesPerScanLine-1
	mov	esi,eax
	mov	bx,RoadColoursBL*256+RoadColoursTR
	mov	dx,RoadColoursMask*256+RoadColoursBR
@@L1:
	push	ecx
	mov	ecx,DestBytesPerScanLine-1
@@L2:
	mov	al,byte ptr ds:[esi]
	test	al,dh
	jnz	short @@NotRoadColour
	cmp	al,bl
	jz	short @@TR
	cmp	al,bh
	jz	short @@BL
	cmp	al,dl
	jz	short @@BR
@@Default:
	mov	al,byte ptr ds:[esi+1]
	test	al,dh
	jz	short @@Not1
	mov	byte ptr ds:[esi],bl				;;RoadColoursTR
@@Not1:
	mov	al,byte ptr ds:[esi+DestBytesPerScanLine]
	test	al,dh
	jz	short @@Not2
	mov	byte ptr ds:[esi+DestBytesPerScanLine],bh	;;RoadColoursBL
@@Not2:
	mov	al,byte ptr ds:[esi+DestBytesPerScanLine+1]
	test	al,dh
	jz	short @@DoneS
	mov	byte ptr ds:[esi+DestBytesPerScanLine+1],dl	;;RoadColoursBR
	jmp	short @@DoneS
@@TR:
	mov	al,byte ptr ds:[esi-1]
	mov	byte ptr ds:[esi],al
	jmp	short @@DoneS
@@BL:
	mov	al,byte ptr ds:[esi-DestBytesPerScanLine]
	mov	byte ptr ds:[esi],al
	jmp	short @@DoneS
@@BR:
	mov	al,byte ptr ds:[esi-DestBytesPerScanLine-1]
	mov	byte ptr ds:[esi],al
@@DoneS:
@@NotRoadColour:
	inc	esi
	dec	ecx
	jnz	short @@L2

	;;last pixel in each row is special

	mov	al,byte ptr ds:[esi]
	test	al,dh
	jnz	short @@NotRoadColour2
	cmp	al,bl
	jz	short @@TR2
	cmp	al,bh
	jz	short @@BL2
	cmp	al,dl
	jz	short @@BR2
	mov	al,byte ptr ds:[esi+DestBytesPerScanLine]
	test	al,dh
	jz	short @@DoneS2
	mov	byte ptr ds:[esi+DestBytesPerScanLine],bh	;;RoadColoursBL
	jmp	short @@DoneS2
@@TR2:
	mov	al,byte ptr ds:[esi-1]
	mov	byte ptr ds:[esi],al
	jmp	short @@DoneS2
@@BL2:
	mov	al,byte ptr ds:[esi-DestBytesPerScanLine]
	mov	byte ptr ds:[esi],al
	jmp	short @@DoneS2
@@BR2:
	mov	al,byte ptr ds:[esi-DestBytesPerScanLine-1]
	mov	byte ptr ds:[esi],al
@@DoneS2:
@@NotRoadColour2:
	pop	ecx
	inc	esi
	dec	ecx
	jnz	@@L1

	;;last row is special

	mov	ecx,DestBytesPerScanLine-1
@@L3:
	mov	al,byte ptr ds:[esi]
	test	al,dh
	jnz	short @@NotRoadColour3
	cmp	al,bl
	jz	short @@TR3
	cmp	al,bh
	jz	short @@BL3
	cmp	al,dl
	jz	short @@BR3
	mov	al,byte ptr ds:[esi+1]
	test	al,dh
	jz	short @@DoneS3
	mov	byte ptr ds:[esi+1],bl			;;RoadColoursTR
	jmp	short @@DoneS3
@@TR3:
	mov	al,byte ptr ds:[esi-1]
	mov	byte ptr ds:[esi],al
	jmp	short @@DoneS3
@@BL3:
	mov	al,byte ptr ds:[esi-DestBytesPerScanLine]
	mov	byte ptr ds:[esi],al
	jmp	short @@DoneS3
@@BR3:
	mov	al,byte ptr ds:[esi-DestBytesPerScanLine-1]
	mov	byte ptr ds:[esi],al
@@DoneS3:
@@NotRoadColour3:
	inc	esi
	dec	ecx
	jnz	short @@L3

	;;very last pixel in the block is special

	mov	al,byte ptr ds:[esi]
	test	al,dh
	jnz	short @@NotRoadColour4
	cmp	al,dl
	jz	short @@BR4
	cmp	al,bh
	jz	short @@BL4
	cmp	al,bl
	jnz	@@DoneS4
@@TR4:
	mov	al,byte ptr ds:[esi-1]
	mov	byte ptr ds:[esi],al
	jmp	short @@DoneS4
@@BL4:
	mov	al,byte ptr ds:[esi-DestBytesPerScanLine]
	mov	byte ptr ds:[esi],al
	jmp	short @@DoneS4
@@BR4:
	mov	al,byte ptr ds:[esi-DestBytesPerScanLine-1]
	mov	byte ptr ds:[esi],al
@@DoneS4:
@@NotRoadColour4:
	pop	esi
	pop	edx
	pop	ecx
	pop	ebx
	pop	eax
	ret
EndProc	ASM_WidenRoutes

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_AliasTile
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Tue 22 Oct 1996
;;Modified
;;
;;Description
;;
;;Inputs	eax = ptr src data
;;		edx = ptr dest data
;;		ebx = ptr colour lookup table
;;		ecx = ptr alias table
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
	push	ebp
	mov	[dword ptr ds:srcptr],eax
	mov	[dword ptr ds:destptr],edx
	mov	esi,eax
	mov	edi,edx
	xor	eax,eax
	mov	ebp,ecx
	xor	edx,edx

;;Special case code required in 3 cases;
;;
;;	(1) first pixel
;;
;;	(2) first row
;;
;;	(3) first column

;;------------------------------------------------------------------------------
;; (1) first pixel - has only 1 diagonal, 1 horizontal and 1 vertical neighbours
;;------------------------------------------------------------------------------
	mov	al,byte ptr ds:[esi]
	test	al,RoadColoursMask
	jnz	short @@NotRoadColour
	mov	dl,byte ptr ds:[ebx+eax]			;;real route colour

	mov	al,byte ptr ds:[esi+DestBytesPerScanLine+1]	;;S-E
	mov	dh,byte ptr ds:[ebx+eax]
	mov	dl,byte ptr ds:[ebp+edx]

	mov	al,byte ptr ds:[esi+1]				;;E
	mov	dh,byte ptr ds:[ebx+eax]
	mov	dl,byte ptr ds:[ebp+edx]

	mov	al,byte ptr ds:[esi+DestBytesPerScanLine]	;;S
	mov	dh,byte ptr ds:[ebx+eax]
	mov	al,byte ptr ds:[ebp+edx]
@@NotRoadColour:
	mov	byte ptr ds:[edi],al
	inc	esi
	inc	edi

;;----------------------------------------------------------------------------
;; (2) first row - has only 2 diagonal, 2 horizontal and 1 vertical neighbours
;;----------------------------------------------------------------------------
  	mov	ecx,DestBytesPerScanLine-2
@@LR1:
	mov	al,byte ptr ds:[esi]
	test	al,RoadColoursMask
	jnz	short @@NotRoadColour2
	mov	dl,byte ptr ds:[ebx+eax]			;;real route colour

	mov	al,byte ptr ds:[esi+DestBytesPerScanLine-1]	;;S-W
	mov	dh,byte ptr ds:[ebx+eax]
	mov	dl,byte ptr ds:[ebp+edx]

	mov	al,byte ptr ds:[esi+DestBytesPerScanLine+1]	;;S-E
	mov	dh,byte ptr ds:[ebx+eax]
	mov	dl,byte ptr ds:[ebp+edx]

	mov	al,byte ptr ds:[esi-1]				;;W
	mov	dh,byte ptr ds:[ebx+eax]
	mov	dl,byte ptr ds:[ebp+edx]

	mov	al,byte ptr ds:[esi+1]				;;E
	mov	dh,byte ptr ds:[ebx+eax]
	mov	dl,byte ptr ds:[ebp+edx]

	mov	al,byte ptr ds:[esi+DestBytesPerScanLine]	;;S
	mov	dh,byte ptr ds:[ebx+eax]
	mov	al,byte ptr ds:[ebp+edx]

@@NotRoadColour2:
	mov	byte ptr ds:[edi],al
	inc	esi
	inc	edi
	dec	ecx
	jnz	short @@LR1

;;last pixel

	mov	al,byte ptr ds:[esi]
	mov	al,byte ptr ds:[ebx+eax]
	mov	byte ptr ds:[edi],al

;;-------------------------------------------------------------------------------
;; (3) first column - has only 2 diagonal, 1 horizontal and 2 vertical neighbours
;;-------------------------------------------------------------------------------
	mov	esi,[dword ptr ds:srcptr]
	mov	edi,[dword ptr ds:destptr]
	add	esi,DestBytesPerScanLine
	add	edi,DestBytesPerScanLine
	mov	ecx,DestBytesPerScanLine-2
@@LC1:
	mov	al,byte ptr ds:[esi]
	test	al,RoadColoursMask
	jnz	short @@NotRoadColour3

	mov	dl,byte ptr ds:[ebx+eax]

	mov	al,byte ptr ds:[esi-DestBytesPerScanLine+1]	;;N-E
	mov	dh,byte ptr ds:[ebx+eax]
	mov	dl,byte ptr ds:[ebp+edx]

	mov	al,byte ptr ds:[esi+DestBytesPerScanLine+1]	;;S-E
	mov	dh,byte ptr ds:[ebx+eax]
	mov	dl,byte ptr ds:[ebp+edx]

	mov	al,byte ptr ds:[esi+1]				;;E
	mov	dh,byte ptr ds:[ebx+eax]
	mov	dl,byte ptr ds:[ebp+edx]

	mov	al,byte ptr ds:[esi+DestBytesPerScanLine]	;;S
	mov	dh,byte ptr ds:[ebx+eax]
	mov	dl,byte ptr ds:[ebp+edx]

	mov	al,byte ptr ds:[esi-DestBytesPerScanLine]	;;N
	mov	dh,byte ptr ds:[ebx+eax]
	mov	al,byte ptr ds:[ebp+edx]

@@NotRoadColour3:
	mov	byte ptr ds:[edi],al
	add	esi,DestBytesPerScanLine
	add	edi,DestBytesPerScanLine
	dec	ecx
	jnz	short @@LC1

;;last pixel

	mov	al,byte ptr ds:[esi]
	mov	al,byte ptr ds:[ebx+eax]
	mov	byte ptr ds:[edi],al

;;---------------------------------------------
;; now the main body of the tile can be aliased
;;---------------------------------------------

	mov	esi,[dword ptr ds:srcptr]
	mov	edi,[dword ptr ds:destptr]
	add	esi,DestBytesPerScanLine+1
	add	edi,DestBytesPerScanLine+1
	mov	ecx,DestBytesPerScanLine-2
@@MB1:
	push	ecx
	push	esi
	push	edi
	mov	ecx,DestBytesPerScanLine-2
@@MB2:
	mov	al,byte ptr ds:[esi]
	test	al,RoadColoursMask
	jnz	short @@NotRoadColour4

	mov	dl,byte ptr ds:[ebx+eax]

	mov	al,byte ptr ds:[esi-DestBytesPerScanLine-1]	;;N-W
	mov	dh,byte ptr ds:[ebx+eax]
	mov	dl,byte ptr ds:[ebp+edx]

	mov	al,byte ptr ds:[esi-DestBytesPerScanLine]	;;N
	mov	dh,byte ptr ds:[ebx+eax]
	mov	dl,byte ptr ds:[ebp+edx]

	mov	al,byte ptr ds:[esi-DestBytesPerScanLine+1]	;;N-E
	mov	dh,byte ptr ds:[ebx+eax]
	mov	dl,byte ptr ds:[ebp+edx]

	mov	al,byte ptr ds:[esi-1]				;;W
	mov	dh,byte ptr ds:[ebx+eax]
	mov	dl,byte ptr ds:[ebp+edx]

	mov	al,byte ptr ds:[esi+1]				;;E
	mov	dh,byte ptr ds:[ebx+eax]
	mov	dl,byte ptr ds:[ebp+edx]

	mov	al,byte ptr ds:[esi+DestBytesPerScanLine-1]	;;S-W
	mov	dh,byte ptr ds:[ebx+eax]
	mov	dl,byte ptr ds:[ebp+edx]

	mov	al,byte ptr ds:[esi+DestBytesPerScanLine]	;;S
	mov	dh,byte ptr ds:[ebx+eax]
	mov	dl,byte ptr ds:[ebp+edx]

	mov	al,byte ptr ds:[esi+DestBytesPerScanLine+1]	;;S-W
	mov	dh,byte ptr ds:[ebx+eax]
	mov	al,byte ptr ds:[ebp+edx]
@@NotRoadColour4:
	mov	byte ptr ds:[edi],al
	inc	esi
	inc	edi
	dec	ecx
	jnz	short @@MB2

;;last pixel

	mov	al,byte ptr ds:[esi]
	mov	al,byte ptr ds:[ebx+eax]
	mov	byte ptr ds:[edi],al

	pop	edi
	pop	esi
	add	edi,DestBytesPerScanLine
	pop	ecx
	add	esi,DestBytesPerScanLine
	dec	ecx
	jnz	@@MB1

;;bottom row of pixels

	mov	ecx,DestBytesPerScanLine-1
@@LpLp:
	mov	al,byte ptr ds:[esi]
	mov	al,byte ptr ds:[ebx+eax]
	mov	byte ptr ds:[edi],al
	inc	esi
	inc	edi
	dec	ecx
	jnz	short @@LpLp

	pop	ebp
	pop	edi
	pop	esi
	pop	edx
	pop	ecx
	pop	ebx
	pop	eax
	ret
EndProc	ASM_AliasTile

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_NoAliasTile
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Tue 22 Oct 1996
;;Modified
;;
;;Description
;;
;;Inputs	eax = ptr src data
;;		edx = ptr dest data
;;		ebx = ptr colour lookup table
;;		ecx = ptr alias table
;;
;;Returns
;;
;;Externals
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
	mov	esi,eax
	xor	eax,eax
	mov	ecx,257*257
@@Loop:	mov	al,byte ptr [esi]
	test	al,RoadColoursMask
	jnz	short @@NotRoadColour
	mov	al,byte ptr [ebx+eax]
	mov	byte ptr [esi],al
@@NotRoadColour:
	inc	esi
	dec	ecx
	jnz	short @@Loop
	ret
EndProc	ASM_NoAliasTile

	_TEXT	ENDS

END
