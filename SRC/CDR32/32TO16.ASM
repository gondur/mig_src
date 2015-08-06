	page	,132

;Thunk Compiler Version 1.8  May 11 1995 13:16:19
;File Compiled Wed Sep 23 14:31:39 1998

;Command Line: Y:\UTILEXE\thunk.exe -t thk -o 32to16.asm ..\cdr16\32to16.thk 

	TITLE	$32to16.asm

	.386
	OPTION READONLY
	OPTION OLDSTRUCTS

IFNDEF IS_16
IFNDEF IS_32
%out command line error: specify one of -DIS_16, -DIS_32
.err
ENDIF  ;IS_32
ENDIF  ;IS_16


IFDEF IS_32
IFDEF IS_16
%out command line error: you can't specify both -DIS_16 and -DIS_32
.err
ENDIF ;IS_16
;************************* START OF 32-BIT CODE *************************


	.model FLAT,STDCALL


;-- Import common flat thunk routines (in k32)

externDef MapHInstLS	:near32
externDef MapHInstLS_PN	:near32
externDef MapHInstSL	:near32
externDef MapHInstSL_PN	:near32
externDef FT_Prolog	:near32
externDef FT_Thunk	:near32
externDef QT_Thunk	:near32
externDef FT_Exit0	:near32
externDef FT_Exit4	:near32
externDef FT_Exit8	:near32
externDef FT_Exit12	:near32
externDef FT_Exit16	:near32
externDef FT_Exit20	:near32
externDef FT_Exit24	:near32
externDef FT_Exit28	:near32
externDef FT_Exit32	:near32
externDef FT_Exit36	:near32
externDef FT_Exit40	:near32
externDef FT_Exit44	:near32
externDef FT_Exit48	:near32
externDef FT_Exit52	:near32
externDef FT_Exit56	:near32
externDef SMapLS	:near32
externDef SUnMapLS	:near32
externDef SMapLS_IP_EBP_8	:near32
externDef SUnMapLS_IP_EBP_8	:near32
externDef SMapLS_IP_EBP_12	:near32
externDef SUnMapLS_IP_EBP_12	:near32
externDef SMapLS_IP_EBP_16	:near32
externDef SUnMapLS_IP_EBP_16	:near32
externDef SMapLS_IP_EBP_20	:near32
externDef SUnMapLS_IP_EBP_20	:near32
externDef SMapLS_IP_EBP_24	:near32
externDef SUnMapLS_IP_EBP_24	:near32
externDef SMapLS_IP_EBP_28	:near32
externDef SUnMapLS_IP_EBP_28	:near32
externDef SMapLS_IP_EBP_32	:near32
externDef SUnMapLS_IP_EBP_32	:near32
externDef SMapLS_IP_EBP_36	:near32
externDef SUnMapLS_IP_EBP_36	:near32
externDef SMapLS_IP_EBP_40	:near32
externDef SUnMapLS_IP_EBP_40	:near32

MapSL	PROTO NEAR STDCALL p32:DWORD



	.code 

;************************* COMMON PER-MODULE ROUTINES *************************

	.data

public thk_ThunkData32	;This symbol must be exported.
thk_ThunkData32 label dword
	dd	3130534ch	;Protocol 'LS01'
	dd	0123eh	;Checksum
	dd	0	;Jump table address.
	dd	3130424ch	;'LB01'
	dd	0	;Flags
	dd	0	;Reserved (MUST BE 0)
	dd	0	;Reserved (MUST BE 0)
	dd	offset QT_Thunk_thk - offset thk_ThunkData32
	dd	offset FT_Prolog_thk - offset thk_ThunkData32



	.code 


externDef ThunkConnect32@24:near32

public thk_ThunkConnect32@16
thk_ThunkConnect32@16:
	pop	edx
	push	offset thk_ThkData16
	push	offset thk_ThunkData32
	push	edx
	jmp	ThunkConnect32@24
thk_ThkData16 label byte
	db	"thk_ThunkData16",0


		


pfnQT_Thunk_thk	dd offset QT_Thunk_thk
pfnFT_Prolog_thk	dd offset FT_Prolog_thk
	.data
QT_Thunk_thk label byte
	db	32 dup(0cch)	;Patch space.

FT_Prolog_thk label byte
	db	32 dup(0cch)	;Patch space.


	.code 





;************************ START OF THUNK BODIES************************




;
public InitCDFS16@0
InitCDFS16@0:
	mov	cl,2
; InitCDFS16(16) = InitCDFS16(32) {}
;
;
public IIInitCDFS16@0
IIInitCDFS16@0:
	push	ebp
	mov	ebp,esp
	push	ecx
	sub	esp,60
	call	dword ptr [pfnQT_Thunk_thk]
	leave
	retn





;
public ExitCDFS16@0
ExitCDFS16@0:
	mov	cl,1
; ExitCDFS16(16) = ExitCDFS16(32) {}
;
;
public IIExitCDFS16@0
IIExitCDFS16@0:
	push	ebp
	mov	ebp,esp
	push	ecx
	sub	esp,60
	call	dword ptr [pfnQT_Thunk_thk]
	leave
	retn





;
public SeekToLocation16@8
SeekToLocation16@8:
	mov	cl,0
; SeekToLocation16(16) = SeekToLocation16(32) {}
;
; dword ptr [ebp+8]:  hFile
; dword ptr [ebp+12]:  seekPos
;
public IISeekToLocation16@8
IISeekToLocation16@8:
	push	ebp
	mov	ebp,esp
	push	ecx
	sub	esp,60
	push	word ptr [ebp+8]	;hFile: dword->word
	push	dword ptr [ebp+12]	;seekPos: dword->dword
	call	dword ptr [pfnQT_Thunk_thk]
	movzx	eax,ax
	leave
	retn	8




ELSE
;************************* START OF 16-BIT CODE *************************




	OPTION SEGMENT:USE16
	.model LARGE,PASCAL


	.code	



externDef SeekToLocation16:far16
externDef ExitCDFS16:far16
externDef InitCDFS16:far16


FT_thkTargetTable label word
	dw	offset SeekToLocation16
	dw	   seg SeekToLocation16
	dw	offset ExitCDFS16
	dw	   seg ExitCDFS16
	dw	offset InitCDFS16
	dw	   seg InitCDFS16




	.data

public thk_ThunkData16	;This symbol must be exported.
thk_ThunkData16	dd	3130534ch	;Protocol 'LS01'
	dd	0123eh	;Checksum
	dw	offset FT_thkTargetTable
	dw	seg    FT_thkTargetTable
	dd	0	;First-time flag.



	.code 


externDef ThunkConnect16:far16

public thk_ThunkConnect16
thk_ThunkConnect16:
	pop	ax
	pop	dx
	push	seg    thk_ThunkData16
	push	offset thk_ThunkData16
	push	seg    thk_ThkData32
	push	offset thk_ThkData32
	push	cs
	push	dx
	push	ax
	jmp	ThunkConnect16
thk_ThkData32 label byte
	db	"thk_ThunkData32",0





ENDIF
END
