;;------------------------------------------------------------------------------
;;Module	keytasm.asm
;;System
;;Author	Jim Taylor
;;Date		Mon 23 Oct 1995
;;Description	key testing assembler routines
;;------------------------------------------------------------------------------
	IDeal
	locals	@@
p386
	include	"strucm.inc"
	include	"keytest.i"

	SEGMENT _DATA PUBLIC USE32 'DATA'
	ENDS	_DATA

	GROUP	DGROUP	_DATA



;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
;;
;; The following macro defines the procedures called from the keyboard isr
;; They will be expanded into 16 bit and 32 bit segment variants
;;
;; ds:ebx	can be relied upon to be a valid pointer in both modes
;; al 		contains a scancode
;; MONO		identifies a region of mono monitor in the correct convention
;;
;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
	MACRO	KeyboardHandlingBody	MONO


;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
@@TestForPassThrough:
;;------------------------------------------------------------------------------
;;Author	Jim Taylor
;;Date		Mon 23 Oct 1995
;;Modified
;;
;;Description	Certain keys must be passed through to the system keyboard handler
;;		Otherwise the debugger stops, and so will windows.
;;
;;Keys passed:
;;		Ctrl
;;		Alt
;;		Break	-only if ctrl or alt set
;;		Esc	-only if ctrl or alt set
;;		Tab	-only if ctrl or alt set
;;
;;Inputs	al = key press
;;Outputs	carry flag set 		to return from interrupt
;;		carry flag clear 	to pass through
;;
;;
;;------------------------------------------------------------------------------
	test	[(keymap ds:ebx).active.f],40h	;;ignore when E0 flagged
	stc
	jnz	@@Reset
	mov	ah,al
	and	ah,07fh
	cmp	ah,KEYSC_Ctrl
	je	@@Pass
	cmp	ah,KEYSC_Alt
	je	@@Pass
	test	[(keymap ds:ebx).currshifts],KEYSH_CtrlL+KEYSH_Alt
	stc
	jz	@@Reset
	cmp	ah,01h	;;esc
	je	@@Pass
	cmp	ah,0fh	;;tab
	je	@@Pass
	cmp	ah,46h	;;break=scroll lock
@@Pass:
@@Reset:
	ret


;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
@@GetShift:
;;------------------------------------------------------------------------------
;;Author	Jim Taylor
;;Date		Mon 23 Oct 1995
;;Modified
;;
;;Description	Handles shift keys
;;		Sets and clears local flags to match shift keys
;;		and returns pattern
;;
;;Events that happen:
;;		1)	E0:	Special shift on next character - flag in .active:7
;;				Flag to skip main routine
;;
;;		2)	Shift key
;;			2.1)	.a:7==0:	set/clear normal shift flag
;;						Flag to skip main routine
;;
;;			2.2)	.a:7==1:	set/clear alt shift flag
;;						clear .a:7
;;						Flag to skip
;;
;;		3)	Non-shift character
;;			3.1)	.a:7==0:	Clear Ext shift flag
;;						Flag to process
;;
;;			3.2)	.a:7==1:	Set Ext shift flag
;;						clear .a:7
;;						Flag to process
;;What about held shift keys?
;;		Not a problem - some wasted effort setting bits repeatedly
;;
;;Inputs	al = raw key flag
;;		ds:ebx=commomkeymap - contains flags
;;Returns	zero set - key used up - exit caller
;;		zero clear - cont - cl = shift bits currently active
;;
;;Externals	cx,ah are available
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
	and	[(keymap ds:ebx).active.f],not(40h)
	mov	cl,[(keymap ds:ebx).currshifts]
;;DeadCode JIM 30Jan96 	mov	[byte ptr MONO],cl
	mov	ah,al
	cmp	ah,KEYSC_ExtSh
	je	@@Case1_E0
	and	ah,7fh
     	mov	cx,KEYSH_CtrlL*256+KEYSH_CtrlR
	cmp	ah,KEYSC_Ctrl
	je	@@ShKey
     	mov	cx,KEYSH_AltL*256+KEYSH_AltGR
	cmp	ah,KEYSC_Alt
	je	@@ShKey
	mov	cx,KEYSH_ShiftL*256
	cmp	ah,KEYSC_ShiftL
	je	@@ShKey
	mov	cx,KEYSH_ShiftR*256
	cmp	ah,KEYSC_ShiftR
	jne	@@Case3_Key

@@Case2_shift:
@@ShKey:
	test	[(keymap ds:ebx).active.f],80h
	jz	@@NotFollowsE0
	mov	ch,cl
	or	[(keymap ds:ebx).active.f],40h
@@NotFollowsE0:		;;CL is bit to set/clear
	mov	cl,ch
	not	ch
	and	ch,[(keymap ds:ebx).currshifts]	;;clear the bit
	test	al,80h
	jnz	@@Release	;;if press event
	or	ch,cl		;;set the bit
@@Release:
;;DeadCode JIM 30Jan96 	mov	[MONO],ch
	mov	[(keymap ds:ebx).currshifts],ch
	and	[(keymap ds:ebx).active.f],not(80h)
	xor	cx,cx	       	;;set ZERO
	jmp short @@DoneSh

@@Case1_E0:
	or	[(keymap ds:ebx).active.f],80h
	xor	cx,cx		;;set ZERO
	jmp	@@DoneSh

@@Case3_Key:
	mov	cl,[(keymap ds:ebx).currshifts]
;;//DeadCode JIM 30Jan96 	mov	[MONO],cl
	and	cl,not(KEYSH_ExtSh)
	mov	dl,[(keymap ds:ebx).active.f]
	btr	dx,7
	mov	[(keymap ds:ebx).active.f],dl
	jnc	@@Alreadyclear
	or	cl,KEYSH_ExtSh
@@Alreadyclear:
	mov	[(keymap ds:ebx).currshifts],cl
	test	esp,esp		;;set non-zero
@@DoneSh:
	ret

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
@@reftable3dpress:
;;------------------------------------------------------------------------------
;;Author	Jim Taylor
;;Date		Mon 23 Oct 1995
;;Modified
;;
;;Description	ISR for 3d keyboard
;;
;;Inputs	al=keypress
;;		DS:BX->KeyMap3d
;;Stack:	BX,DS,EAX
;;Returns
;;
;;Externals
;;------------------------------------------------------------------------------
;;DeadCode JIM 02Nov95 	cmp	[byte ds:ebx],0	;;enabled flag
;;DeadCode JIM 02Nov95 	jz	@@Done
 	call	@@GetShift
 	jz	@@Done
	test	al,80h
	jz	@@Press3d

	and	Eax,07fh
	btr	[word	(keymap ebx).keyholds],ax
	;;clear all 8 mappings
	shl	eax,4
	mov	cx,[(KeyMap3d (ebx+eax)).mappings]
	btr	[word	(KeyMap3d ebx).bitflags],cx
	mov	cx,[(KeyMap3d (ebx+eax+2)).mappings]
	btr	[word	(KeyMap3d ebx).bitflags],cx
	mov	cx,[(KeyMap3d (ebx+eax+4)).mappings]
	btr	[word	(KeyMap3d ebx).bitflags],cx
	mov	cx,[(KeyMap3d (ebx+eax+6)).mappings]
	btr	[word	(KeyMap3d ebx).bitflags],cx
	mov	cx,[(KeyMap3d (ebx+eax+8)).mappings]
	btr	[word	(KeyMap3d ebx).bitflags],cx
	mov	cx,[(KeyMap3d (ebx+eax+10)).mappings]
	btr	[word	(KeyMap3d ebx).bitflags],cx
	mov	cx,[(KeyMap3d (ebx+eax+12)).mappings]
	btr	[word	(KeyMap3d ebx).bitflags],cx
	mov	cx,[(KeyMap3d (ebx+eax+14)).mappings]
	btr	[word	(KeyMap3d ebx).bitflags],cx
	jmp short @@Done3d
@@Press3d:
	and	Eax,07fh
	bts	[word	(keymap ebx).keyholds],ax
	jc	@@AlreadySet3d
	xor	ch,ch
	bsf	cx,cx	;;if cx=0 then unchanged=>0
	add	cx,cx
	shl	eax,4
	add	ax,cx
	mov	cx,[(KeyMap3d ebx+eax).mappings]
	bts	[word	(KeyMap3d ebx).bitflags],cx
	inc	cx
	bts	[word	(KeyMap3d ebx).bitflags],cx
@@AlreadySet3d:
@@Done3d:
	ret

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
@@hitqueueuipress:
;;------------------------------------------------------------------------------
;;Author	Jim Taylor
;;Date		Mon 23 Oct 1995
;;Modified
;;
;;Description
;;
;;Inputs	al=keypress
;;		DS:BX->UIKeyQueue
;;Stack:	BX,DS,EAX
;;Returns
;;
;;Externals
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
	call	@@GetShift
	jz	@@Done
	test	al,80h
	jz	@@PressUI

	and	ax,7fh
	btr	[word	(keymap ds:ebx).keyholds],ax
	mov	ah,KeyBounce_KeyRel
	jmp short @@Got
@@PressUI:
	and	ax,7fh
	bts	[word	(keymap ds:ebx).keyholds],ax
	mov	ah,KeyBounce_KeyHit
	jnc short @@Got
	mov	ah,KeyBounce_KeyHeld
	movsx	edx,[(UIKeyQueue ds:ebx).addref]
	cmp	dx,[(UIKeyQueue ds:ebx).takeref]
	je	@@Got
	imul	edx,offset (UIKeyEvent 0).SEND
	cmp	[byte (UIKeyEvent (((UIKeyQueue ds:ebx).keyqueue)+edx)).keyhit],ah
	je	@@Done				;;don't log unused repeated key helds
@@Got:	;;insert key into queue
	push	esi
	movzx	esi,[(UIKeyQueue ds:ebx).addref]
	mov	edx,esi
	inc	edx
	cmp	dx,[(UIKeyQueue ds:ebx).queuesize]
	jne	@@ok1
	mov	edx,0
@@ok1:
	cmp	dx,[(UIKeyQueue ds:ebx).takeref]
	je	@@full
	mov	[(UIKeyQueue ds:ebx).addref],dx
	imul	esi,offset (UIKeyEvent 0).SEND
	mov	[(UIKeyEvent (((UIKeyQueue ds:ebx).keyqueue)+esi)).keycode],al
	mov	[(UIKeyEvent (((UIKeyQueue ds:ebx).keyqueue)+esi)).keyshifts],cl
	mov	[byte (UIKeyEvent (((UIKeyQueue ds:ebx).keyqueue)+esi)).keyhit],ah
	mov	edx,[(UIKeyQueue ds:ebx).ScreenXY]
	mov	[(UIKeyEvent (((UIKeyQueue ds:ebx).keyqueue)+esi)).ScreenXY],edx
@@full:
	pop	esi
@@Done:
	ret

	ENDM



	CODE_SEG	_TEXT
	ASSUME	cs:_TEXT, ds:_TEXT
;;;;;;;;;;;;;;;;;;;;;;;;;;
;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	keytests__dexISRstart
;;------------------------------------------------------------------------------
;;Author	Jim Taylor
;;Date		Tue 24 Oct 1995
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
public	keytests__dexISRtables_
keytests__dexISRtables_	dd	0,0,0,0,0,0,0	;;32 bytes	;;used 14 + 4
			db	'JIM',0
;;------------------------------------------------------------------------------

Procedure	keytests__dexISRcode
;;------------------------------------------------------------------------------
	push	ds
	push	eax
	push	ebx
	push	ecx
	push	edx
	mov	bx,_DATA
	mov	ds,bx
	in	al,60h			;reads the keyboard port PA

;;DeadCode JIM 01Nov95 	mov	[MONO+160*6],al
;;DeadCode JIM 01Nov95 	inc	[byte	MONO+160*6+2]

	mov	ebx,[keytests__dexISRtables_]
	test	[(keymap ds:ebx).active.f],1
	jz	@@Skip1
	push	ax
	call	@@hitqueueuipress
	pop	ax
@@Skip1:

	mov	ebx,[keytests__dexISRtables_+4]
	test	[(keymap ds:ebx).active.f],1
	jz	@@Skip2
	push	ax
	call	@@reftable3dpress
	pop	ax
@@Skip2:
	mov	ebx,[keytests__dexISRtables_+4]
	test	[(keymap ds:ebx).active.f],1
	jnz	@@PassTest
	mov	ebx,[keytests__dexISRtables_]
	test	[(keymap ds:ebx).active.f],1
	jz	@@PassPassThrough		;;carry clear as well!
@@PassTest:
	call	@@TestForPassThrough
@@PassPassThrough:
	pop	edx
	pop	ecx
	pop	ebx
	pop	eax
	pop	ds
	jc	@@Return
	jmp	[FWORD cs:keytests__dexISRtables_+8]
@@Return:
	push	ax
	in	al,61h			;reads the 8255 port PB
	or	al,80h			;start the acknowledge signal
	out	61h,al
	and	al,7fh
	out	61h,al			;end of acknowledge signal
	mov	al,20h      ;       indicate end of interupt
	out	20h,al
	pop	ax

	iretd

	KeyboardHandlingBody   DS:0B0000h

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	keytests__dexISRend
;;------------------------------------------------------------------------------
;;Author	Jim Taylor
;;Date		Tue 24 Oct 1995
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
	endp
	endp



;;;;;;;;;;;;;;;;;;;;;;;;;;
	ENDS	_TEXT

p286

	SEGMENT	_TEXT16	BYTE PUBLIC USE16 'CODE'
	ASSUME	cs:_TEXT16

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	keytests__dosISRstart
;;------------------------------------------------------------------------------
;;Author	Jim Taylor
;;Date		Tue 24 Oct 1995
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
;;Want a 32 byte header here = 8 dd's
hitqueueuiptr	dd	0
reftable3dptr	dd	0
oldisr		dd	0

;;TempCode JIM 31Oct95 OldISR		dd	0

	dd	0,0,0,0
   	db	'JIM',0

p386
;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	keytests__dosISRcode
;;------------------------------------------------------------------------------
;;Author	Jim Taylor
;;Date		Mon 23 Oct 1995
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
	push	ds
	push	es
	push	eax
	push	ebx
	push	ecx
	push	edx
	in	al,60h			;reads the keyboard port PA
	mov	ebx,0000b000h
	mov	es,bx
;;DeadCode JIM 01Nov95 	mov	[es:160*4],al
;;DeadCode JIM 01Nov95 	inc	[byte es:160*4+2]

	mov	ebx,0

	lds	bx,[cs:0]
	test	[(keymap ds:ebx).active.f],1
	jz	@@Skip1
	push	ax
	call	@@hitqueueuipress
	pop	ax
@@Skip1:

	lds	bx,[cs:4]
	test	[(keymap ds:ebx).active.f],1
	jz	@@Skip2
	push	ax
	call	@@reftable3dpress
	pop	ax
@@Skip2:
	lds	bx,[cs:4]
	test	[(keymap ds:ebx).active.f],1
	jnz	@@PassTest
	lds	bx,[cs:0]
	test	[(keymap ds:ebx).active.f],1
	jz	@@PassPassThrough		;;carry clear as well!
@@PassTest:
	call	@@TestForPassThrough
@@PassPassThrough:
	pop	edx
	pop	ecx
	pop	ebx
	pop	eax
	pop	es
	pop	ds
	jc	@@DontPass
	jmp	[dword cs:8]
@@DontPass:
	push	ax
	in	al,61h			;reads the 8255 port PB
	or	al,80h			;start the acknowledge signal
	out	61h,al
	and	al,7fh
	out	61h,al			;end of acknowledge signal
	mov	al,20h      ;       indicate end of interupt
	out	20h,al
	pop	ax

	iret

	KeyboardHandlingBody  ES:1600

	endp
;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	keytests__dosISRend
;;------------------------------------------------------------------------------
;;Author	Jim Taylor
;;Date		Tue 24 Oct 1995
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
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	ends	_TEXT16



end
