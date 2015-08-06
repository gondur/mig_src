Macro	Procedure	name
	Proc	&name&_
	public	&name&_
	endm

%nolist	;  strucm.mac: MACRO ASSEMBLER LANGUAGE EXTENSION
;
;; Activate by including this file in assembler source code using
;; the assembler INCLUDE directive.  This language extension provides
;; a set of structures based on those in Jim Holtman's  'struct.mac'.
;; The syntax supported by this language extension is a superset of
;; the earlier version - Terry Stancliffe, 1986.
;
_$on=1
_$lc=1
_$nl=0
_$lsp=1
_$csp=0
_$ssp=0
_$exitflag=0
_$tst=0
_$sreg=0
_$done=0

macro	@pop	list
	irp poopoo,<list>
		ifnb	<poopoo>
			pop	poopoo
	endif
	endm
endm

macro	@save	p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12
	irp	poopoo,<p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12>
		ifnb	<poopoo>
		push	poopoo
	endif
endm

macro	@restore
	@pop	<p12,p11,p10,p9,p8,p7,p6,p5,p4,p3,p2,p1>
	endm
endm

macro	m$dfpop	x,poplist
	macro	m$restore&x
		@pop    poplist
_$ssp = _$ssp - 1
	endm				;;&endm
endm

macro m$xqpop x
	m$restore&x
	purge	m$restore&x
endm

macro	_save	p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12
_$ssp = _$ssp + 1
	irp	poopoo,<p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12>
		ifnb	<poopoo>
			push	poopoo
		endif
	endm
	m$dfpop	%_$ssp,<<p12,p11,p10,p9,p8,p7,p6,p5,p4,p3,p2,p1>>
endm

macro	_restore
	m$xqpop %_$ssp
endm

ok=1
notok=0

macro	CODE_SEG	segname
	segment segname use32 para public 'CODE'
;;Old_Code DAW 14May94 	segment segname para public 'CODE'
ENDM


Macro	Procedure	name
	Proc	&name&_
	public	&name&_
	endm
