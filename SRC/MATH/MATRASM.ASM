;; ------------------------------------------------------------------------------
;;Module	matrix.asm
;;System
;;Author	Paul.
;;Date		Thu 3 Oct 1996
;;Description
;;------------------------------------------------------------------------------
;;TempCode PD 04Nov97 	IDeal
;;TempCode PD 04Nov97 LOCALS	@@
;;TempCode PD 04Nov97 p386
;;TempCode PD 04Nov97 	INCLUDE "STRUCM.INC"

Procedure	Macro	name
	_X&name&	Proc
	public	_X&name&
		endm

EndProc		Macro	name
	_X&name&	EndP
		endm

.386
	_DATA SEGMENT PAGE PUBLIC USE32 'DATA'

	ALIGN	4

Arse		dd	?		;;dummy variable - never used
LocalX		dd	?
LocalY		dd	?
LocalZ		dd	?
ScaleFactor	dd	?

BodyXl		dd	?
BodyXh		dd	?

BodyYl		dd	?
BodyYh		dd	?

BodyZl		dd	?
BodyZh		dd	?

	_DATA	ENDS

	DGROUP	GROUP	_DATA

	_TEXT SEGMENT PAGE PUBLIC USE32 'CODE'

	ASSUME	CS:_TEXT, DS:DGROUP

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASMTransform
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Wed 2 Oct 1996
;;Modified
;;
;;Description
;;
;;Inputs	eax = MATRIX_PTR
;;		edx = ptr x coord
;;		ebx = ptr y coord
;;		ecx = ptr z coord
;;
;;Returns
;;
;;Externals
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
	push	esi
	push	edi
	push	ebp

;;Load up the input coordinates

	push	edx
	push	ebx
	mov	edx,dword ptr ds:[edx]
	push	ecx
	mov	ebx,dword ptr ds:[ebx]
	mov	ecx,dword ptr ds:[ecx]

;;Save the MATRIX_PTR for later

	mov	esi,eax

;;scale input values to 16 bit

	mov	[dword ptr ds:LocalX],edx
	mov	ebp,ebx
	mov	eax,ecx
	mov	edi,edx
	mov	[dword ptr ds:LocalY],ebx
	sar	eax,01fh
	sar	ebp,01fh
	mov	[dword ptr ds:LocalZ],ecx
	sar	edi,01fh
	xor	ecx,eax
	xor	edx,edi
	xor	ebx,ebp
	sub	ecx,eax
	sub	edx,edi
	mov	eax,ecx
	sub	ebx,ebp
	or	eax,edx
	or	eax,ebx
	cmp	eax,00007FFFh
	jl	short @@Quick
	bsr	ecx,eax
	sub	ecx,0Eh
	mov	ebx,[dword ptr ds:LocalY]
	mov	eax,[dword ptr ds:LocalX]
	sar	ebx,cl
	mov	edx,[dword ptr ds:LocalZ]
	sar	eax,cl
	mov	[dword ptr ds:LocalY],ebx
	sar	edx,cl
	mov	[dword ptr ds:LocalX],eax
	mov	[dword ptr ds:LocalZ],edx
	mov	[dword ptr ds:ScaleFactor],ecx
	jmp	short @@DoneScale
@@Quick:
	mov	[dword ptr ds:ScaleFactor],0
@@DoneScale:

;;X,Y and Z scaled by correct ammount and stored away for later

;;Calculate body x

	movsx	eax,word ptr ds:[esi]
	mov	ebx,[dword ptr ds:LocalX]
	mov	ecx,[dword ptr ds:LocalY]
	imul	ebx
	add	esi,2
	mov	ebp,eax
	mov	edi,edx
	movsx	eax,word ptr ds:[esi]
	mov	ebx,[dword ptr ds:LocalZ]
	imul	ecx
	add	esi,2
	add	ebp,eax
	adc	edi,edx
	movsx	eax,word ptr ds:[esi]
	imul	ebx
	add	esi,2
	add	ebp,eax
	adc	edi,edx
	add	ebp,ebp
	adc	edi,edi
	mov	[dword ptr ds:BodyXl],ebp
	mov	[dword ptr ds:BodyXh],edi

	movsx	eax,word ptr ds:[esi]
	mov	ebx,[dword ptr ds:LocalX]
	mov	ecx,[dword ptr ds:LocalY]
	imul	ebx
	add	esi,2
	mov	ebp,eax
	mov	edi,edx
	movsx	eax,word ptr ds:[esi]
	mov	ebx,[dword ptr ds:LocalZ]
	imul	ecx
	add	esi,2
	add	ebp,eax
	adc	edi,edx
	movsx	eax,word ptr ds:[esi]
	imul	ebx
	add	esi,2
	add	ebp,eax
	adc	edi,edx
	add	ebp,ebp
	adc	edi,edi
	mov	[dword ptr ds:BodyYl],ebp
	mov	[dword ptr ds:BodyYh],edi

	movsx	eax,word ptr ds:[esi]
	mov	ebx,[dword ptr ds:LocalX]
	mov	ecx,[dword ptr ds:LocalY]
	imul	ebx
	add	esi,2
	mov	ebp,eax
	mov	edi,edx
	movsx	eax,word ptr ds:[esi]
	mov	ebx,[dword ptr ds:LocalZ]
	imul	ecx
	add	esi,2
	add	ebp,eax
	adc	edi,edx
	movsx	eax,word ptr ds:[esi]
	imul	ebx
	add	ebp,eax
	adc	edi,edx
	add	ebp,ebp
	adc	edi,edi
	mov	[dword ptr ds:BodyZl],ebp
	mov	[dword ptr ds:BodyZh],edi

;;Final test for overflows during the additions above

	mov	eax,[dword ptr ds:BodyXl+2]
	mov	ebx,[dword ptr ds:BodyYl+2]
	mov	edx,eax
	mov	esi,ebx
	mov	ecx,[dword ptr ds:BodyZl+2]
	sar	edx,1fh
	mov	edi,ecx
	sar	esi,1fh
	sar	edi,1fh
	xor	eax,edx
	xor	ebx,esi
	xor	ecx,edi
	sub	eax,edx
	sub	ebx,esi
	sub	ecx,edi
	or	eax,ebx
	or	eax,ecx
	cmp	eax,00007FFFh
	ja	short @@OFlowFix
@@DoneRescale:
	mov	eax,[dword ptr ds:BodyZl]
	pop	ecx
	mov	dword ptr ds:[ecx],eax
	pop	ebx
	mov	eax,[dword ptr ds:BodyYl]
	pop	edx
	mov	dword ptr ds:[ebx],eax
	mov	eax,[dword ptr ds:BodyXl]
	mov	dword ptr ds:[edx],eax
	mov	eax,[dword ptr ds:ScaleFactor]
	pop	ebp
	pop	edi
	pop	esi
	ret
@@OFlowFix:
	bsr	ecx,eax
	sub	ecx,0Eh
	add	[dword ptr ds:ScaleFactor],ecx
	mov	eax,[dword ptr ds:BodyXl]
	mov	edx,[dword ptr ds:BodyXh]
	shrd	eax,edx,cl
	sar	edx,cl
	mov	[dword ptr ds:BodyXl],eax
	mov	[dword ptr ds:BodyXh],edx

	mov	eax,[dword ptr ds:BodyYl]
	mov	edx,[dword ptr ds:BodyYh]
	shrd	eax,edx,cl
	sar	edx,cl
	mov	[dword ptr ds:BodyYl],eax
	mov	[dword ptr ds:BodyYh],edx

	mov	eax,[dword ptr ds:BodyZl]
	mov	edx,[dword ptr ds:BodyZh]
	shrd	eax,edx,cl
	sar	edx,cl
	mov	[dword ptr ds:BodyZl],eax
	mov	[dword ptr ds:BodyZh],edx
	jmp	short @@DoneRescale
EndProc	ASMTransform

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASMDoBigXProd
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Wed 27 Nov 1996
;;Modified
;;
;;Description
;;
;;Inputs	(eax,edx) vector 1 dx and dy
;;		(ebx,ecx) vector 2 dx and dy
;;
;;Returns	TRUE or FALSE
;;
;;Externals
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------

	push	ebp
;;work out vector1.dx * vector2.dy (eax * ecx)
	mov	ebp,edx
	mov	edx,eax
	sar	edx,1Fh
	imul	ecx
	mov	edi,edx
	mov	esi,eax

;; edi:esi = v1.dx*v2.dy

;;work out vector1.dy * vector2.dx (ebp * ebx)
	mov	edx,ebp
	mov	eax,ebp
	sar	edx,1Fh
	imul	ebx

;;Now find the sign of the Z component of the cross product
	sub	esi,eax
	sbb	edi,edx
	mov	al,0
	js	short @@Fail
	mov	al,1
@@Fail:
	pop	ebp
	ret
EndProc	ASMDoBigXProd


	_TEXT	ENDS

END
