# Microsoft Developer Studio Generated NMAKE File, Based on RJoyCfg.dsp
!IF "$(CFG)" == ""
CFG=RJoyCfg - Win32 Debug
!MESSAGE No configuration specified. Defaulting to RJoyCfg - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "RJoyCfg - Win32 Release" && "$(CFG)" !=\
 "RJoyCfg - Win32 Debug" && "$(CFG)" != "RJoyCfg - Win32 Unicode Debug" &&\
 "$(CFG)" != "RJoyCfg - Win32 Unicode Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "RJoyCfg.mak" CFG="RJoyCfg - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "RJoyCfg - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "RJoyCfg - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "RJoyCfg - Win32 Unicode Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "RJoyCfg - Win32 Unicode Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "RJoyCfg - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
TargetName=RJoyCfg
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OutDir)\$(TargetName).lic" "$(OUTDIR)\RJoyCfg.ocx"\
 "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OutDir)\$(TargetName).lic" "$(OUTDIR)\RJoyCfg.ocx"\
 "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\RJoyCfg.obj"
	-@erase "$(INTDIR)\RJoyCfg.res"
	-@erase "$(INTDIR)\RJoyCfg.tlb"
	-@erase "$(INTDIR)\RJoyCfgC.obj"
	-@erase "$(INTDIR)\RJoyCfgP.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\RJoyCfg.exp"
	-@erase "$(OUTDIR)\RJoyCfg.lib"
	-@erase "$(OUTDIR)\RJoyCfg.ocx"
	-@erase "$(OutDir)\$(TargetName).lic"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /Fp"$(INTDIR)\RJoyCfg.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
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
RSC_PROJ=/l 0x809 /fo"$(INTDIR)\RJoyCfg.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\RJoyCfg.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\RJoyCfg.pdb" /machine:I386 /def:".\RJoyCfg.def"\
 /out:"$(OUTDIR)\RJoyCfg.ocx" /implib:"$(OUTDIR)\RJoyCfg.lib" 
DEF_FILE= \
	".\RJoyCfg.def"
LINK32_OBJS= \
	"$(INTDIR)\RJoyCfg.obj" \
	"$(INTDIR)\RJoyCfg.res" \
	"$(INTDIR)\RJoyCfgC.obj" \
	"$(INTDIR)\RJoyCfgP.obj"

"$(OUTDIR)\RJoyCfg.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Release
TargetPath=.\Release\RJoyCfg.ocx
InputPath=.\Release\RJoyCfg.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ELSEIF  "$(CFG)" == "RJoyCfg - Win32 Debug"

OUTDIR=\mig\Debug\exe
INTDIR=\mig\Debug\axobj
# Begin Custom Macros
OutDir=\mig\Debug\exe
TargetName=RJoyCfg
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OutDir)\$(TargetName).lic" "$(OUTDIR)\RJoyCfg.ocx"\
 "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OutDir)\$(TargetName).lic" "$(OUTDIR)\RJoyCfg.ocx"\
 "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\RJoyCfg.obj"
	-@erase "$(INTDIR)\RJoyCfg.res"
	-@erase "$(INTDIR)\RJoyCfgC.obj"
	-@erase "$(INTDIR)\RJoyCfgP.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\RJoyCfg.exp"
	-@erase "$(OUTDIR)\RJoyCfg.ilk"
	-@erase "$(OUTDIR)\RJoyCfg.lib"
	-@erase "$(OUTDIR)\RJoyCfg.ocx"
	-@erase "$(OUTDIR)\RJoyCfg.pdb"
	-@erase "..\..\Debug\exe\RJoyCfg.tlb"
	-@erase "$(OutDir)\$(TargetName).lic"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "\mig\src\h" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
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
RSC_PROJ=/l 0x809 /fo"$(INTDIR)\RJoyCfg.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\RJoyCfg.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)\RJoyCfg.pdb" /debug /machine:I386 /def:".\RJoyCfg.def"\
 /out:"$(OUTDIR)\RJoyCfg.ocx" /implib:"$(OUTDIR)\RJoyCfg.lib" /pdbtype:sept 
DEF_FILE= \
	".\RJoyCfg.def"
LINK32_OBJS= \
	"$(INTDIR)\RJoyCfg.obj" \
	"$(INTDIR)\RJoyCfg.res" \
	"$(INTDIR)\RJoyCfgC.obj" \
	"$(INTDIR)\RJoyCfgP.obj"

"$(OUTDIR)\RJoyCfg.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=\mig\Debug\exe
TargetPath=\mig\Debug\exe\RJoyCfg.ocx
InputPath=\mig\Debug\exe\RJoyCfg.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ELSEIF  "$(CFG)" == "RJoyCfg - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
TargetName=RJoyCfg
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OutDir)\$(TargetName).lic" "$(OUTDIR)\RJoyCfg.ocx"\
 "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OutDir)\$(TargetName).lic" "$(OUTDIR)\RJoyCfg.ocx"\
 "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\RJoyCfg.obj"
	-@erase "$(INTDIR)\RJoyCfg.res"
	-@erase "$(INTDIR)\RJoyCfg.tlb"
	-@erase "$(INTDIR)\RJoyCfgC.obj"
	-@erase "$(INTDIR)\RJoyCfgP.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\RJoyCfg.exp"
	-@erase "$(OUTDIR)\RJoyCfg.ilk"
	-@erase "$(OUTDIR)\RJoyCfg.lib"
	-@erase "$(OUTDIR)\RJoyCfg.ocx"
	-@erase "$(OUTDIR)\RJoyCfg.pdb"
	-@erase "$(OutDir)\$(TargetName).lic"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\RJoyCfg.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\DebugU/
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
RSC_PROJ=/l 0x809 /fo"$(INTDIR)\RJoyCfg.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\RJoyCfg.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)\RJoyCfg.pdb" /debug /machine:I386 /def:".\RJoyCfg.def"\
 /out:"$(OUTDIR)\RJoyCfg.ocx" /implib:"$(OUTDIR)\RJoyCfg.lib" /pdbtype:sept 
DEF_FILE= \
	".\RJoyCfg.def"
LINK32_OBJS= \
	"$(INTDIR)\RJoyCfg.obj" \
	"$(INTDIR)\RJoyCfg.res" \
	"$(INTDIR)\RJoyCfgC.obj" \
	"$(INTDIR)\RJoyCfgP.obj"

"$(OUTDIR)\RJoyCfg.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\DebugU
TargetPath=.\DebugU\RJoyCfg.ocx
InputPath=.\DebugU\RJoyCfg.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ELSEIF  "$(CFG)" == "RJoyCfg - Win32 Unicode Release"

OUTDIR=.\ReleaseU
INTDIR=.\ReleaseU
# Begin Custom Macros
OutDir=.\ReleaseU
TargetName=RJoyCfg
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OutDir)\$(TargetName).lic" "$(OUTDIR)\RJoyCfg.ocx"\
 "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OutDir)\$(TargetName).lic" "$(OUTDIR)\RJoyCfg.ocx"\
 "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\RJoyCfg.obj"
	-@erase "$(INTDIR)\RJoyCfg.res"
	-@erase "$(INTDIR)\RJoyCfg.tlb"
	-@erase "$(INTDIR)\RJoyCfgC.obj"
	-@erase "$(INTDIR)\RJoyCfgP.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\RJoyCfg.exp"
	-@erase "$(OUTDIR)\RJoyCfg.lib"
	-@erase "$(OUTDIR)\RJoyCfg.ocx"
	-@erase "$(OutDir)\$(TargetName).lic"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\RJoyCfg.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\ReleaseU/
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
RSC_PROJ=/l 0x809 /fo"$(INTDIR)\RJoyCfg.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\RJoyCfg.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\RJoyCfg.pdb" /machine:I386 /def:".\RJoyCfg.def"\
 /out:"$(OUTDIR)\RJoyCfg.ocx" /implib:"$(OUTDIR)\RJoyCfg.lib" 
DEF_FILE= \
	".\RJoyCfg.def"
LINK32_OBJS= \
	"$(INTDIR)\RJoyCfg.obj" \
	"$(INTDIR)\RJoyCfg.res" \
	"$(INTDIR)\RJoyCfgC.obj" \
	"$(INTDIR)\RJoyCfgP.obj"

"$(OUTDIR)\RJoyCfg.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseU
TargetPath=.\ReleaseU\RJoyCfg.ocx
InputPath=.\ReleaseU\RJoyCfg.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ENDIF 


!IF "$(CFG)" == "RJoyCfg - Win32 Release" || "$(CFG)" ==\
 "RJoyCfg - Win32 Debug" || "$(CFG)" == "RJoyCfg - Win32 Unicode Debug" ||\
 "$(CFG)" == "RJoyCfg - Win32 Unicode Release"
SOURCE=.\RJoyCfg.cpp
DEP_CPP_RJOYC=\
	".\RJoyCfg.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\RJoyCfg.obj" : $(SOURCE) $(DEP_CPP_RJOYC) "$(INTDIR)"\
 "$(INTDIR)\RJoyCfg.pch"


SOURCE=.\RJoyCfg.odl

!IF  "$(CFG)" == "RJoyCfg - Win32 Release"

MTL_SWITCHES=/nologo /D "NDEBUG" /tlb "$(OUTDIR)\RJoyCfg.tlb" /mktyplib203 /o\
 NUL /win32 

"$(OUTDIR)\RJoyCfg.tlb" : $(SOURCE) "$(OUTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RJoyCfg - Win32 Debug"

MTL_SWITCHES=/nologo /D "_DEBUG" /tlb "$(OUTDIR)\RJoyCfg.tlb" /mktyplib203 /o\
 NUL /win32 

"$(OUTDIR)\RJoyCfg.tlb" : $(SOURCE) "$(OUTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RJoyCfg - Win32 Unicode Debug"

MTL_SWITCHES=/nologo /D "_DEBUG" /tlb "$(OUTDIR)\RJoyCfg.tlb" /mktyplib203 /o\
 NUL /win32 

"$(OUTDIR)\RJoyCfg.tlb" : $(SOURCE) "$(OUTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RJoyCfg - Win32 Unicode Release"

MTL_SWITCHES=/nologo /D "NDEBUG" /tlb "$(OUTDIR)\RJoyCfg.tlb" /mktyplib203 /o\
 NUL /win32 

"$(OUTDIR)\RJoyCfg.tlb" : $(SOURCE) "$(OUTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\RJoyCfg.rc

!IF  "$(CFG)" == "RJoyCfg - Win32 Release"

DEP_RSC_RJOYCF=\
	".\RJoyCfgC.bmp"\
	".\Wfly.ico"\
	
NODEP_RSC_RJOYCF=\
	".\Release\RJoyCfg.tlb"\
	

"$(INTDIR)\RJoyCfg.res" : $(SOURCE) $(DEP_RSC_RJOYCF) "$(INTDIR)"\
 "$(INTDIR)\RJoyCfg.tlb"
	$(RSC) /l 0x809 /fo"$(INTDIR)\RJoyCfg.res" /i "Release" /d "NDEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "RJoyCfg - Win32 Debug"

DEP_RSC_RJOYCF=\
	"..\..\Debug\exe\RJoyCfg.tlb"\
	".\RJoyCfgC.bmp"\
	".\Wfly.ico"\
	

"$(INTDIR)\RJoyCfg.res" : $(SOURCE) $(DEP_RSC_RJOYCF) "$(INTDIR)"\
 "..\..\Debug\exe\RJoyCfg.tlb"
	$(RSC) /l 0x809 /fo"$(INTDIR)\RJoyCfg.res" /i "\mig\Debug\exe" /d "_DEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "RJoyCfg - Win32 Unicode Debug"

DEP_RSC_RJOYCF=\
	".\RJoyCfgC.bmp"\
	".\Wfly.ico"\
	
NODEP_RSC_RJOYCF=\
	".\DebugU\RJoyCfg.tlb"\
	

"$(INTDIR)\RJoyCfg.res" : $(SOURCE) $(DEP_RSC_RJOYCF) "$(INTDIR)"\
 "$(INTDIR)\RJoyCfg.tlb"
	$(RSC) /l 0x809 /fo"$(INTDIR)\RJoyCfg.res" /i "DebugU" /d "_DEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "RJoyCfg - Win32 Unicode Release"

DEP_RSC_RJOYCF=\
	".\RJoyCfgC.bmp"\
	".\Wfly.ico"\
	
NODEP_RSC_RJOYCF=\
	".\ReleaseU\RJoyCfg.tlb"\
	

"$(INTDIR)\RJoyCfg.res" : $(SOURCE) $(DEP_RSC_RJOYCF) "$(INTDIR)"\
 "$(INTDIR)\RJoyCfg.tlb"
	$(RSC) /l 0x809 /fo"$(INTDIR)\RJoyCfg.res" /i "ReleaseU" /d "NDEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ENDIF 

SOURCE=.\RJoyCfgC.cpp

!IF  "$(CFG)" == "RJoyCfg - Win32 Release"

DEP_CPP_RJOYCFG=\
	".\RJoyCfg.h"\
	".\RJoyCfgC.h"\
	".\RJoyCfgP.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\RJoyCfgC.obj" : $(SOURCE) $(DEP_CPP_RJOYCFG) "$(INTDIR)"\
 "$(INTDIR)\RJoyCfg.pch"


!ELSEIF  "$(CFG)" == "RJoyCfg - Win32 Debug"

DEP_CPP_RJOYCFG=\
	".\RJoyCfg.h"\
	".\RJoyCfgC.h"\
	".\RJoyCfgP.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\RJoyCfgC.obj" : $(SOURCE) $(DEP_CPP_RJOYCFG) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "RJoyCfg - Win32 Unicode Debug"

DEP_CPP_RJOYCFG=\
	".\RJoyCfg.h"\
	".\RJoyCfgC.h"\
	".\RJoyCfgP.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\RJoyCfgC.obj" : $(SOURCE) $(DEP_CPP_RJOYCFG) "$(INTDIR)"\
 "$(INTDIR)\RJoyCfg.pch"


!ELSEIF  "$(CFG)" == "RJoyCfg - Win32 Unicode Release"

DEP_CPP_RJOYCFG=\
	".\RJoyCfg.h"\
	".\RJoyCfgC.h"\
	".\RJoyCfgP.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\RJoyCfgC.obj" : $(SOURCE) $(DEP_CPP_RJOYCFG) "$(INTDIR)"\
 "$(INTDIR)\RJoyCfg.pch"


!ENDIF 

SOURCE=.\RJoyCfgP.cpp
DEP_CPP_RJOYCFGP=\
	".\RJoyCfg.h"\
	".\RJoyCfgP.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\RJoyCfgP.obj" : $(SOURCE) $(DEP_CPP_RJOYCFGP) "$(INTDIR)"\
 "$(INTDIR)\RJoyCfg.pch"


SOURCE=.\RJoyCfg.lic

!IF  "$(CFG)" == "RJoyCfg - Win32 Release"

OutDir=.\Release
ProjDir=.
TargetName=RJoyCfg
InputPath=.\RJoyCfg.lic

"$(OutDir)\$(TargetName).lic"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(ProjDir)\$(TargetName).lic" "$(OutDir)"

!ELSEIF  "$(CFG)" == "RJoyCfg - Win32 Debug"

OutDir=\mig\Debug\exe
ProjDir=.
TargetName=RJoyCfg
InputPath=.\RJoyCfg.lic

"$(OutDir)\$(TargetName).lic"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(ProjDir)\$(TargetName).lic" "$(OutDir)"

!ELSEIF  "$(CFG)" == "RJoyCfg - Win32 Unicode Debug"

OutDir=.\DebugU
ProjDir=.
TargetName=RJoyCfg
InputPath=.\RJoyCfg.lic

"$(OutDir)\$(TargetName).lic"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(ProjDir)\$(TargetName).lic" "$(OutDir)"

!ELSEIF  "$(CFG)" == "RJoyCfg - Win32 Unicode Release"

OutDir=.\ReleaseU
ProjDir=.
TargetName=RJoyCfg
InputPath=.\RJoyCfg.lic

"$(OutDir)\$(TargetName).lic"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(ProjDir)\$(TargetName).lic" "$(OutDir)"

!ENDIF 


!ENDIF 

