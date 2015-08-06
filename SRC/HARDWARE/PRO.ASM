;;------------------------------------------------------------------------------
;;Module	profile.asm
;;System
;;Author	Paul.
;;Date		Fri 17 Apr 1998
;;Description
;;------------------------------------------------------------------------------
Procedure Macro	name
	&name&	Proc
	public	&name&
	endm

EndProc	Macro name
	&name&	EndP
	endm
.386

;;returns pentium internal counter in edx:eax
RDTSCmac	Macro
	db	15,49
			EndM

Repeats=16384

	_DATA SEGMENT PAGE PUBLIC USE32 'DATA'

public retTbl
retTbl		dd Repeats dup (0)
pastIt		dd 0
lockIt		db 0
saveEax		dd 0
saveEcx		dd 0
saveEdi		dd 0

	_DATA	ENDS

	DGROUP	GROUP	_DATA

	_TEXT SEGMENT PAGE PUBLIC USE32 'CODE'

	ASSUME	CS:_TEXT, DS:DGROUP

Procedure jumpTable
REPT Repeats
	call	__pexit
ENDM
EndProc jumpTable

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
;;Procedure	__penter
;;Author	Paul.
;;Date		Fri 17 Apr 1998
;;------------------------------------------------------------------------------
Procedure __penter
	push	eax
	mov		al,1
@@locked: 
	xchg	[lockit],al
	cmp		al,1
	jnz		short @@locked
	pop		eax
;;	mov		[lockIt],1
;;Slight mods to make sure that I don't have to
;;worry about which task is currently in control...
	mov		[saveEax],eax
	mov		[saveEcx],ecx
	mov		[saveEdi],edi
	xor		eax,eax
	mov		ecx,Repeats
	lea		edi,[retTbl]
	repne	scasd
	sub		edi,4
;;edi points to the first available entry in the table...
	pop		ecx
	pop		dword ptr es:[edi]
	lea		eax,dword ptr es:[retTbl]
	sub		edi,eax
	mov		eax,edi
	shr		eax,2
	add		edi,eax
	lea		eax,dword ptr cs:[jumpTable]
	add		edi,eax
	push	edi
	push	ecx
	mov		eax,[saveEax]
	mov		ecx,[saveEcx]
	mov		edi,[saveEdi]

	cmp		[pastIt],0
	jz		short @@fine
	int		3
@@fine:
	mov		[lockIt],0
	ret
EndProc __penter

;;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
;;Procedure	__pexit
;;Author	Paul.
;;Date		Fri 17 Apr 1998
;;------------------------------------------------------------------------------
Procedure __pexit
@@locked: 
	cmp		[lockIt],0
	jnz		short @@locked
	mov		[lockIt],1
;;	int		3
	mov		[saveEax],eax
	mov		[saveEcx],ecx
	mov		[saveEdi],edx
	pop		eax
	lea		ecx,dword ptr cs:[jumpTable+5]
	sub		eax,ecx
	mov		ecx,5
	xor		edx,edx
	idiv	ecx
	lea		edx,dword ptr ds:[retTbl+4*eax]
	push	dword ptr ds:[edx]
	mov		dword ptr ds:[edx],0
	mov		eax,[saveEax]
	mov		ecx,[saveEcx]
	mov		edx,[saveEdi]
	mov		[lockIt],0
	ret
EndProc __pexit


_TEXT	ENDS

end
