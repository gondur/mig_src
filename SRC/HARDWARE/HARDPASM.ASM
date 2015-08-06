;;------------------------------------------------------------------------------
;;Module	hardprim.asm
;;System
;;Author	Paul.
;;Date		Tue 4 Jul 1995
;;Description
;;------------------------------------------------------------------------------
	IDeal
	LOCALS	@@
p386
	include	"strucm.inc"

 	CODE_SEG	_TEXT

	assume	cs:_TEXT

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_OutDxAx
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Tue 4 Jul 1995
;;Modified
;;
;;Description
;;
;;Inputs	eax,edx Watcom convention ????
;;
;;Returns
;;
;;Externals
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
	out	dx,ax
	ret
	endp

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_OutDxAl
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Tue 4 Jul 1995
;;Modified
;;
;;Description
;;
;;Inputs	eax,edx Watcom convention ????
;;
;;Returns
;;
;;Externals
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
	out	dx,al
	ret
	endp

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_PlotPixel
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Tue 4 Jul 1995
;;Modified
;;
;;Description
;;
;;Inputs	eax = screenbase
;;		edx = xoffset
;;		ecx = yoffset
;;		ebx = colour
;;
;;Returns	eax = old colour
;;
;;Externals
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
	_save	esi,ebx,ecx,edx
	sar	ebx,1
	sar	ebx,1
	xchg	ebx,ecx
	mov	esi,eax
	add	esi,ecx
	mov	eax,edx
	sar	eax,2
	add	esi,eax

;;esi -> byte of screen RAM

	mov	cl,03h
	and	cl,dl

	mov	al,02h
	mov	dx,03C4h
	out	dx,al

	mov	dx,03CEh
	mov	al,04h
	out	dx,al

	mov	dx,03CFh	;;Set READ
	mov	al,cl
	out	dx,al

	mov	ax,01h
	sal	ax,cl
	mov	dx,03C5h	;;Set WRITE
	out	dx,al

	movzx	ax,[byte esi]	;;Get original pixel colour
	movzx	eax,ax
	mov	[byte esi],bl	;;Set new pixel colour
	_restore
	ret
	endp

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_WaitVBL
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Wed 5 Jul 1995
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
	_save	ax,dx
	mov	dx,03DAh
@@Wait:	in	al,dx
	test	al,08h
	jz	@@Wait
	_restore
	ret
	endp

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_Blat
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Fri 7 Jul 1995
;;Modified
;;
;;Description
;;
;;Inputs	eax = source
;;		edx = destination
;;		ebx = count
;;Inputs
;;
;;Returns
;;
;;Externals
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
	_save	esi,edi,eax,ecx
	mov	ecx,ebx
	mov	esi,eax
	mov	edi,edx
	sar	ecx,1
	jnc	@@NoBytes
	movsb
	jcxz	@@Done
@@NoBytes:
	sar	ecx,1
	jnc	@@NoWords
	movsw
	jcxz	@@Done
@@NoWords:
	rep	movsd
@@Done:
	_restore
	ret
	endp

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_CopyMainRAM2VidRAM
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Mon 10 Jul 1995
;;Modified
;;
;;Description
;;
;;Inputs	eax = (src ) ptr to Main RAM PSEUDO screen
;;		edx = (dest ) ptr to video RAM
;;
;;Returns
;;
;;Externals
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
	_save	eax,ebx,ecx,edx,esi,edi
	mov	esi,eax
	mov	edi,edx

	mov	al,02h
	mov	dx,03C4h
	out	dx,al

	mov	dx,03CEh
	mov	al,04h
	out	dx,al

	xor	cl,cl
@@L2:
	push	esi
	push	edi
	push	cx

;;TempCode JIM 01Nov95 	mov	al,cl
;;TempCode JIM 01Nov95 	mov	dl,0CFh
;;TempCode JIM 01Nov95 	out	dx,al

	mov	al,01h
	shl	ax,cl
	mov	dl,0C5h
	out	dx,al

	mov	ecx,20*240
@@L1:
	mov	al,[byte ptr esi+8]
	mov	ah,[byte ptr esi+12]
	shl	eax,16
 	mov	al,[byte ptr esi]
 	mov	ah,[byte ptr esi+4]
	add	esi,16
	mov	[edi],eax
	add	edi,4
;;DeadCode JIM 02Nov95 	add	esi,8
;;DeadCode JIM 02Nov95 	mov	[edi],ax
;;DeadCode JIM 02Nov95 	add	edi,2
	dec	cx
	jnz	@@L1

	pop	cx
	pop	edi
	pop	esi

	inc	esi
	inc	cl
	cmp	cl,4
	jb	@@L2

	_restore
	ret
	endp

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_CopyMainRAM2VidRAMF
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Mon 10 Jul 1995
;;Modified
;;
;;Description
;;
;;Inputs	eax = (src ) ptr to Main RAM PSEUDO screen
;;		edx = (dest ) ptr to video RAM
;;
;;Returns
;;
;;Externals
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
	_save	eax,ecx,esi,edi
	mov	esi,eax
	mov	edi,edx
	mov	ecx,(320*240)/4	;;640*480/4
	cld
	rep	movsd
	_restore
	ret
	endp

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_SetPalette
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Tue 11 Jul 1995
;;Modified	;;can't rep outsb on pallette 			;;JIM 16Nov95
;;		;;some cards too slow!
;;Description
;;
;;Inputs	eax = ptr to new palette
;;
;;Returns
;;
;;Externals
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
	_save	ax,ecx,edx,esi
	mov	esi,eax
	mov	ecx,0300h
	mov	edx,03C8h
	xor	al,al
	out	dx,al
	inc	dx
@@loop:
	outs	dx,[byte ds:esi]		;;be explicit about addressing
	loop	@@loop
	_restore
	ret
	endp

	ENDS

end
