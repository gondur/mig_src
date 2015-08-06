# Microsoft Developer Studio Generated NMAKE File, Based on analjoy.dsp
!IF "$(CFG)" == ""
CFG=analjoy - Win32 Debug
!MESSAGE No configuration specified. Defaulting to analjoy - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "analjoy - Win32 Release" && "$(CFG)" !=\
 "analjoy - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "analjoy.mak" CFG="analjoy - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "analjoy - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "analjoy - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "analjoy - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\analjoy.dll"

!ELSE 

ALL : "$(OUTDIR)\analjoy.dll"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\Analpub.obj"
	-@erase "$(INTDIR)\Analwin.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\analjoy.dll"
	-@erase "$(OUTDIR)\analjoy.exp"
	-@erase "$(OUTDIR)\analjoy.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)\analjoy.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Release/
CPP_SBRS=.

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\analjoy.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\analjoy.pdb" /machine:I386 /out:"$(OUTDIR)\analjoy.dll"\
 /implib:"$(OUTDIR)\analjoy.lib" 
LINK32_OBJS= \
	"$(INTDIR)\Analpub.obj" \
	"$(INTDIR)\Analwin.obj"

"$(OUTDIR)\analjoy.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "analjoy - Win32 Debug"

OUTDIR=\mig\game\libcode
INTDIR=\mig\Debug\axobj
# Begin Custom Macros
OutDir=\mig\game\libcode
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\analjoy.dll"

!ELSE 

ALL : "$(OUTDIR)\analjoy.dll"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\Analpub.obj"
	-@erase "$(INTDIR)\Analwin.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\analjoy.dll"
	-@erase "$(OUTDIR)\analjoy.exp"
	-@erase "$(OUTDIR)\analjoy.ilk"
	-@erase "$(OUTDIR)\analjoy.lib"
	-@erase "$(OUTDIR)\analjoy.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /I "..\h" /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /Fp"$(INTDIR)\analjoy.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD\
 /c 
CPP_OBJS=\mig\Debug\axobj/
CPP_SBRS=.

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 
RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\analjoy.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib dinput.lib dxguid.lib /nologo /subsystem:windows /dll\
 /incremental:yes /pdb:"$(OUTDIR)\analjoy.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)\analjoy.dll" /implib:"$(OUTDIR)\analjoy.lib" /pdbtype:sept\
 /libpath:"..\lib" 
LINK32_OBJS= \
	"$(INTDIR)\Analpub.obj" \
	"$(INTDIR)\Analwin.obj"

"$(OUTDIR)\analjoy.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(CFG)" == "analjoy - Win32 Release" || "$(CFG)" ==\
 "analjoy - Win32 Debug"
SOURCE=..\Input\Analpub.cpp

!IF  "$(CFG)" == "analjoy - Win32 Release"

DEP_CPP_ANALP=\
	{$(INCLUDE)}"3ddefs.h"\
	{$(INCLUDE)}"Analogue.h"\
	{$(INCLUDE)}"Bitfield.h"\
	{$(INCLUDE)}"dinput.h"\
	{$(INCLUDE)}"Display.h"\
	{$(INCLUDE)}"Dosdefs.h"\
	{$(INCLUDE)}"Enumbits.m"\
	{$(INCLUDE)}"F_battle.g"\
	{$(INCLUDE)}"F_common.g"\
	{$(INCLUDE)}"F_grafix.g"\
	{$(INCLUDE)}"F_sounds.g"\
	{$(INCLUDE)}"Files.g"\
	{$(INCLUDE)}"Hardpasm.h"\
	{$(INCLUDE)}"Keymaps.h"\
	{$(INCLUDE)}"Keytest.h"\
	{$(INCLUDE)}"Mathasm.h"\
	{$(INCLUDE)}"Myangles.h"\
	{$(INCLUDE)}"Myerror.h"\
	{$(INCLUDE)}"Palette.h"\
	{$(INCLUDE)}"Stub.m"\
	{$(INCLUDE)}"Text.h"\
	{$(INCLUDE)}"Textenum.g"\
	{$(INCLUDE)}"Textfixd.h"\
	{$(INCLUDE)}"Vertex.h"\
	

"$(INTDIR)\Analpub.obj" : $(SOURCE) $(DEP_CPP_ANALP) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "analjoy - Win32 Debug"

DEP_CPP_ANALP=\
	{$(INCLUDE)}"3ddefs.h"\
	{$(INCLUDE)}"Analogue.h"\
	{$(INCLUDE)}"Bitfield.h"\
	{$(INCLUDE)}"Display.h"\
	{$(INCLUDE)}"Dosdefs.h"\
	{$(INCLUDE)}"Enumbits.m"\
	{$(INCLUDE)}"Files.g"\
	{$(INCLUDE)}"Hardpasm.h"\
	{$(INCLUDE)}"Keymaps.h"\
	{$(INCLUDE)}"Keytest.h"\
	{$(INCLUDE)}"Mathasm.h"\
	{$(INCLUDE)}"Myangles.h"\
	{$(INCLUDE)}"Myerror.h"\
	{$(INCLUDE)}"Palette.h"\
	{$(INCLUDE)}"Stub.m"\
	{$(INCLUDE)}"Text.h"\
	{$(INCLUDE)}"Textenum.g"\
	{$(INCLUDE)}"Textfixd.h"\
	{$(INCLUDE)}"Vertex.h"\
	

"$(INTDIR)\Analpub.obj" : $(SOURCE) $(DEP_CPP_ANALP) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\Input\Analwin.cpp

!IF  "$(CFG)" == "analjoy - Win32 Release"

DEP_CPP_ANALW=\
	{$(INCLUDE)}"3ddefs.h"\
	{$(INCLUDE)}"Analogue.h"\
	{$(INCLUDE)}"Bitfield.h"\
	{$(INCLUDE)}"dinput.h"\
	{$(INCLUDE)}"Display.h"\
	{$(INCLUDE)}"Dosdefs.h"\
	{$(INCLUDE)}"Enumbits.m"\
	{$(INCLUDE)}"F_battle.g"\
	{$(INCLUDE)}"F_common.g"\
	{$(INCLUDE)}"F_grafix.g"\
	{$(INCLUDE)}"F_sounds.g"\
	{$(INCLUDE)}"Files.g"\
	{$(INCLUDE)}"Hardpasm.h"\
	{$(INCLUDE)}"Keymaps.h"\
	{$(INCLUDE)}"Keytest.h"\
	{$(INCLUDE)}"Mathasm.h"\
	{$(INCLUDE)}"Monotxt.h"\
	{$(INCLUDE)}"Myangles.h"\
	{$(INCLUDE)}"Palette.h"\
	{$(INCLUDE)}"Stub.m"\
	{$(INCLUDE)}"Text.h"\
	{$(INCLUDE)}"Textenum.g"\
	{$(INCLUDE)}"Textfixd.h"\
	{$(INCLUDE)}"Vertex.h"\
	

"$(INTDIR)\Analwin.obj" : $(SOURCE) $(DEP_CPP_ANALW) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "analjoy - Win32 Debug"

DEP_CPP_ANALW=\
	"..\H\Dinput.h"\
	{$(INCLUDE)}"3ddefs.h"\
	{$(INCLUDE)}"Analogue.h"\
	{$(INCLUDE)}"Bitfield.h"\
	{$(INCLUDE)}"Display.h"\
	{$(INCLUDE)}"Dosdefs.h"\
	{$(INCLUDE)}"Enumbits.m"\
	{$(INCLUDE)}"Files.g"\
	{$(INCLUDE)}"Hardpasm.h"\
	{$(INCLUDE)}"Keymaps.h"\
	{$(INCLUDE)}"Keytest.h"\
	{$(INCLUDE)}"Mathasm.h"\
	{$(INCLUDE)}"Monotxt.h"\
	{$(INCLUDE)}"Myangles.h"\
	{$(INCLUDE)}"Palette.h"\
	{$(INCLUDE)}"Stub.m"\
	{$(INCLUDE)}"Text.h"\
	{$(INCLUDE)}"Textenum.g"\
	{$(INCLUDE)}"Textfixd.h"\
	{$(INCLUDE)}"Vertex.h"\
	

"$(INTDIR)\Analwin.obj" : $(SOURCE) $(DEP_CPP_ANALW) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 


!ENDIF 

