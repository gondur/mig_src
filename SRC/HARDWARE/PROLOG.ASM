	IDeal
	LOCALS	@@
p386
	INCLUDE "STRUCM.INC"

	SEGMENT _DATA PAGE PUBLIC USE32 'DATA'


bPrologEnabled	DW	0			;;FALSE
lpTimerAddress	DD	0			;;Test address

	ENDS	_DATA

	GROUP	DGROUP	_DATA

	SEGMENT _TEXT PAGE PUBLIC USE32 'CODE'

	assume	cs:_TEXT, ds:DGROUP

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_PrologueCode
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Wed 23 Jul 1997
;;Modified
;;
;;Description	Wait for 1 timer tick & then quit
;;
;;Inputs
;;
;;Returns
;;
;;Externals
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
__PRO:	public	__PRO
	cmp	[ds:bPrologEnabled],0
	jz	@@Done
	;;test for timer increment here
	push	eax
	push	ecx
	push	esi

	mov	esi,[ds:lpTimerAddress]
	mov	eax,[dword ptr ds:esi]
	mov	ecx,1000000
@@Loop:
	cmp	eax,[dword ptr ds:esi]
	jnz	@@Okay
	loop	@@Loop
	int	03h
@@Okay:
	pop	esi
	pop	ecx
	pop	eax
@@Done:
	ret
	endp

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 Procedure	ASM_TogglePrologCode
;;------------------------------------------------------------------------------
;;Author	Paul.
;;Date		Wed 23 Jul 1997
;;Modified
;;
;;Description
;;
;;Inputs	eax = 0 --- OFF, 1 --- ON
;;		edx = ptr to timer variable to check
;;Returns
;;
;;Externals
;;------------------------------------------------------------------------------
;;------------------------------------------------------------------------------
	mov	[ds:lpTimerAddress],edx
	mov	[ds:bPrologEnabled],ax
 	ret
 	endp


	ENDS	_TEXT

ends
end
