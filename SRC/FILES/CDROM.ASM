;;------------------------------------------------------------------------------
;;Module	cdrom.asm
;;System
;;Author	Paul.
;;Date		Fri 1 Nov 1996
;;Description
;;------------------------------------------------------------------------------
	IDeal
	LOCALS	@@
	include	"strucm.inc"

p386
	SEGMENT _DATA PUBLIC USE32 'DATA'
	ENDS	_DATA

	GROUP	DGROUP	_DATA

	CODE_SEG	_TEXT
	ASSUME	cs:_TEXT, ds:_TEXT

	ENDS	_TEXT

p286

	SEGMENT	_TEXT16	BYTE PUBLIC USE16 'CODE'
	ASSUME	cs:_TEXT16


struc	READLONG
	length		db	?		;;
	unit		db	?		;;
	func		db	?		;;Standard request
	status		dw	?		;;header
	reserved	db	8 dup(?)	;;

	addrmode	db	?
	trnoff		dw	?
	trnseg		dw	?
	nosectoread	dw	?
	startsectno	dd	?
	readmode	db	?
	interlvsize	db	?
	interlvskip	db	?
ends

struc	SEEKREQ
	length		db	?		;;
	unit		db	?		;;
	func		db	?		;;Standard request
	status		dw	?		;;header
	reserved	db	8 dup(?)	;;

	addrmode	db	?
	trnoff		dw	?
	trnseg		dw	?
	nosectoread	dw	?
	startsectno	dd	?
ends

struc	POSNREQ
	length		db	?		;;
	unit		db	?		;;
	func		db	?		;;Standard request
	status		dw	?		;;header
	reserved	db	8 dup(?)	;;

	mediadesc	db	?
	trnoff		dw	?
	trnseg		dw	?
	bytestotrn	dw	?
	startsectno	dw	?
	requestedvol	dd	?
ends

struc	LOCHEAD
	request		db	?
	addrmode	db	?
	locofhead	dd	?
ends

MASM
	READLONGSize 	= SIZE READLONG
	SEEKREQSize 	= SIZE SEEKREQ
	POSNREQSize	= SIZE POSNREQ
	LOCHEADSize	= SIZE LOCHEAD
Ideal

public	fileman__DeviceHdrSeg_
public	fileman__DeviceHdrOff_
public	fileman__DriveLetter_

p386
;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	fileman__dosIRstart
;;------------------------------------------------------------------------------
;;DON'T PUT ANY CODE OR DATA HERE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
;;DON'T PUT ANY CODE OR DATA HERE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
;;DON'T PUT ANY CODE OR DATA HERE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
;;DON'T PUT ANY CODE OR DATA HERE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
;;DON'T PUT ANY CODE OR DATA HERE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	endp
;;DON'T PUT ANY CODE OR DATA HERE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
;;DON'T PUT ANY CODE OR DATA HERE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
;;DON'T PUT ANY CODE OR DATA HERE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
;;DON'T PUT ANY CODE OR DATA HERE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
;;DON'T PUT ANY CODE OR DATA HERE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	fileman__dosIRcode
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Fri 1 Nov 1996
;;Modified
;;
;;Description	Replacement int 18h handler
;;
;;Inputs	ax	= function number
;;			  (0 = seek, 1 = read block, 2 = return head location)
;;
;;		for function 0 (seek)
;;			edx	= CD-ROM logical block number
;;
;;		for function 1 (read block)
;;			edx 	= CD-ROM logical block number to read
;;			cx:bx 	= ptr to buffer to load the data
;;
;;		for function 2 (return head position)
;;			returns	edx = current head position (logical blocks)
;;
;;Externals
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
	cmp	ax,0
	jz	@@SeekFileBlock
	cmp	ax,1
	jz	@@ReadFileBlock
	cmp	ax,2
	jz	short @@LocateHeadPosition
	xor	ax,ax
	stc
	iret

@@LocateHeadPosition:
	push	ds
	push	es
	call	near @@LNext
@@LNext:
	pop	si
	push	cs
	pop	es
	mov	di,offset fileman__PosnReq_ - offset @@LNext
	add	di,si
	mov	[(POSNREQ es:di).mediadesc], 0
	mov	[(POSNREQ es:di).startsectno],	0
	mov	[(POSNREQ es:di).requestedvol], 0
	mov	[(POSNREQ es:di).unit], 0
	mov	[(POSNREQ es:di).length],POSNREQSize
	mov	[(POSNREQ es:di).func], 12

	mov	[(POSNREQ es:di).status], 0
	mov	[(POSNREQ es:di).trnoff], di
	add	[(POSNREQ es:di).trnoff], POSNREQSize
	mov	ax,es
	mov	[(POSNREQ es:di).trnseg], ax
	mov	[(POSNREQ es:di).bytestotrn],LOCHEADSize
	mov	[(LOCHEAD (es:di + POSNREQSize)).request],1
	mov	[(LOCHEAD (es:di + POSNREQSize)).addrmode],0
	push	es
	push	di
	mov	bx,di
	mov	di,si
	mov	cx,[word ptr es:si + (offset fileman__DriveLetter_ - offset @@LNext)]
	mov	ax,[word ptr es:si + (offset fileman__DeviceHdrSeg_- offset @@LNext)]
	mov	ds,ax
	mov	si,[word ptr es:si + (offset fileman__DeviceHdrOff_- offset @@LNext)]
	add	di,offset @@LDone - offset @@LNext
 	push	cs
 	push	di				;;return address
  	push	ds
  	push	[word ptr ds:si+8]		;;interupt rtn
 	push	ds
 	push	[word ptr ds:si+6]		;;strategy rtn
 	retf
@@LDone:
	pop	di
	pop	es
	mov	edx,[(LOCHEAD (es:di + POSNREQSize)).locofhead]
	mov	ax,[(POSNREQ es:di).status]
	pop	es
	pop	ds
	iret

@@SeekFileBlock:
	push	ds
	push	es
	call	near @@SNext
@@SNext:
	pop	si
	push	cs
	pop	es
	mov	di,offset fileman__SeekReq_ - offset @@SNext
	add	di,si
	mov	[(SEEKREQ es:di).length],SEEKREQSize
	mov	[(SEEKREQ es:di).unit], 0
	mov	[(SEEKREQ es:di).func], 131
	mov	[(SEEKREQ es:di).status], 0
	mov	[(SEEKREQ es:di).addrmode], 0
	mov	[(SEEKREQ es:di).trnoff], 0
	mov	[(SEEKREQ es:di).trnseg], 0
	mov	[(SEEKREQ es:di).nosectoread],	0
	mov	[(SEEKREQ es:di).startsectno],	edx
	push	es
	push	di
	mov	bx,di
	mov	di,si
	mov	cx,[word ptr es:si + (offset fileman__DriveLetter_ - offset @@SNext)]
	mov	ax,[word ptr es:si + (offset fileman__DeviceHdrSeg_- offset @@SNext)]
	mov	ds,ax
	mov	si,[word ptr es:si + (offset fileman__DeviceHdrOff_- offset @@SNext)]
	add	di,offset @@SDone - offset @@SNext
 	push	cs
 	push	di				;;return address
  	push	ds
  	push	[word ptr ds:si+8]		;;interupt rtn
 	push	ds
 	push	[word ptr ds:si+6]		;;strategy rtn
 	retf
@@SDone:
	pop	di
	pop	es
	mov	ax,[(SEEKREQ es:di).status]
	pop	es
	pop	ds
	iret

@@ReadFileBlock:
	push	ds
	push	es
	call	near @@RNext
@@RNext:
	pop	si
	push	cs
	pop	es
	mov	di,offset fileman__ReadLong_ - offset @@RNext
	add	di,si
	mov	[(READLONG es:di).length],READLONGSize
	mov	[(READLONG es:di).unit], 0
	mov	[(READLONG es:di).func], 128
	mov	[(READLONG es:di).status], 0
	mov	[(READLONG es:di).addrmode], 0
	mov	[(READLONG es:di).trnoff], bx
	mov	[(READLONG es:di).trnseg], cx
	mov	[(READLONG es:di).nosectoread],	1
	mov	[(READLONG es:di).startsectno],	edx
	mov	[(READLONG es:di).readmode], 0
	push	es
	push	di
	mov	bx,di
	mov	di,si
	mov	cx,[word ptr es:si + (offset fileman__DriveLetter_ - offset @@RNext)]
	mov	ax,[word ptr es:si + (offset fileman__DeviceHdrSeg_- offset @@RNext)]
	mov	ds,ax
	mov	si,[word ptr es:si + (offset fileman__DeviceHdrOff_- offset @@RNext)]
	add	di,offset @@RDone - offset @@RNext
 	push	cs
 	push	di				;;return address
  	push	ds
  	push	[word ptr ds:si+8]		;;interupt rtn
 	push	ds
 	push	[word ptr ds:si+6]		;;strategy rtn
 	retf
@@RDone:
	pop	di
	pop	es
	mov	ax,[(READLONG es:di).status]
	pop	es
	pop	ds
	iret
	endp

fileman__DeviceHdrSeg_	dw	4321h
fileman__DeviceHdrOff_	dw	5678h

fileman__DriveLetter_	dw	5678h

fileman__ReadLong_	READLONG <>

fileman__SeekReq_	SEEKREQ <>

fileman__PosnReq_	POSNREQ <>
			LOCHEAD <>

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	fileman__dosIRend
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Fri 1 Nov 1996
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
	endp


	ENDS	_TEXT16
	END
