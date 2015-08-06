# Microsoft Developer Studio Generated NMAKE File, Based on Redit.dsp
!IF "$(CFG)" == ""
CFG=REdit - Win32 Debug
!MESSAGE No configuration specified. Defaulting to REdit - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "REdit - Win32 Release" && "$(CFG)" != "REdit - Win32 Debug" &&\
 "$(CFG)" != "REdit - Win32 Unicode Debug" && "$(CFG)" !=\
 "REdit - Win32 Unicode Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Redit.mak" CFG="REdit - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "REdit - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "REdit - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "REdit - Win32 Unicode Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "REdit - Win32 Unicode Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "REdit - Win32 Release"

OUTDIR=\mig\Release\exe
INTDIR=\mig\Release\axobj
# Begin Custom Macros
OutDir=\mig\Release\exe
TargetName=Redit
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OutDir)\$(TargetName).lic" "$(OUTDIR)\Redit.ocx"\
 "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OutDir)\$(TargetName).lic" "$(OUTDIR)\Redit.ocx"\
 "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\REdit.obj"
	-@erase "$(INTDIR)\REdit.res"
	-@erase "$(INTDIR)\REditCtl.obj"
	-@erase "$(INTDIR)\REditPpg.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\Redit.exp"
	-@erase "$(OUTDIR)\Redit.lib"
	-@erase "$(OUTDIR)\Redit.ocx"
	-@erase "..\..\Release\exe\REdit.tlb"
	-@erase "$(OutDir)\$(TargetName).lic"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /Fp"$(INTDIR)\Redit.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=\mig\Release\axobj/
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
RSC_PROJ=/l 0x809 /fo"$(INTDIR)\REdit.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Redit.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\Redit.pdb" /machine:I386 /def:".\REdit.def"\
 /out:"$(OUTDIR)\Redit.ocx" /implib:"$(OUTDIR)\Redit.lib" 
DEF_FILE= \
	".\REdit.def"
LINK32_OBJS= \
	"$(INTDIR)\REdit.obj" \
	"$(INTDIR)\REdit.res" \
	"$(INTDIR)\REditCtl.obj" \
	"$(INTDIR)\REditPpg.obj"

"$(OUTDIR)\Redit.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=\mig\Release\exe
TargetPath=\mig\Release\exe\Redit.ocx
InputPath=\mig\Release\exe\Redit.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ELSEIF  "$(CFG)" == "REdit - Win32 Debug"

OUTDIR=\mig\Debug\exe
INTDIR=\mig\Debug\axobj
# Begin Custom Macros
OutDir=\mig\Debug\exe
TargetName=Redit
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OutDir)\$(TargetName).lic" "$(OUTDIR)\Redit.ocx" "$(OUTDIR)\Redit.bsc"\
 "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OutDir)\$(TargetName).lic" "$(OUTDIR)\Redit.ocx" "$(OUTDIR)\Redit.bsc"\
 "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\REdit.obj"
	-@erase "$(INTDIR)\REdit.res"
	-@erase "$(INTDIR)\REdit.sbr"
	-@erase "$(INTDIR)\REditCtl.obj"
	-@erase "$(INTDIR)\REditCtl.sbr"
	-@erase "$(INTDIR)\REditPpg.obj"
	-@erase "$(INTDIR)\REditPpg.sbr"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\Redit.bsc"
	-@erase "$(OUTDIR)\Redit.exp"
	-@erase "$(OUTDIR)\Redit.ilk"
	-@erase "$(OUTDIR)\Redit.lib"
	-@erase "$(OUTDIR)\Redit.ocx"
	-@erase "$(OUTDIR)\Redit.pdb"
	-@erase "..\..\Debug\exe\REdit.tlb"
	-@erase "$(OutDir)\$(TargetName).lic"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "\mig\src\h" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /FR"$(INTDIR)\\"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=\mig\Debug\axobj/
CPP_SBRS=\mig\Debug\axobj/

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
RSC_PROJ=/l 0x809 /fo"$(INTDIR)\REdit.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Redit.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\REdit.sbr" \
	"$(INTDIR)\REditCtl.sbr" \
	"$(INTDIR)\REditPpg.sbr"

"$(OUTDIR)\Redit.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)\Redit.pdb" /debug /machine:I386 /def:".\REdit.def"\
 /out:"$(OUTDIR)\Redit.ocx" /implib:"$(OUTDIR)\Redit.lib" /pdbtype:sept 
DEF_FILE= \
	".\REdit.def"
LINK32_OBJS= \
	"$(INTDIR)\REdit.obj" \
	"$(INTDIR)\REdit.res" \
	"$(INTDIR)\REditCtl.obj" \
	"$(INTDIR)\REditPpg.obj"

"$(OUTDIR)\Redit.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=\mig\Debug\exe
TargetPath=\mig\Debug\exe\Redit.ocx
InputPath=\mig\Debug\exe\Redit.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ELSEIF  "$(CFG)" == "REdit - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
TargetName=Redit
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OutDir)\$(TargetName).lic" "$(OUTDIR)\Redit.ocx"\
 "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OutDir)\$(TargetName).lic" "$(OUTDIR)\Redit.ocx"\
 "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\REdit.obj"
	-@erase "$(INTDIR)\REdit.res"
	-@erase "$(INTDIR)\REdit.tlb"
	-@erase "$(INTDIR)\REditCtl.obj"
	-@erase "$(INTDIR)\REditPpg.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\Redit.exp"
	-@erase "$(OUTDIR)\Redit.ilk"
	-@erase "$(OUTDIR)\Redit.lib"
	-@erase "$(OUTDIR)\Redit.ocx"
	-@erase "$(OUTDIR)\Redit.pdb"
	-@erase "$(OutDir)\$(TargetName).lic"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\Redit.pch"\
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
RSC_PROJ=/l 0x809 /fo"$(INTDIR)\REdit.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Redit.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)\Redit.pdb" /debug /machine:I386 /def:".\REdit.def"\
 /out:"$(OUTDIR)\Redit.ocx" /implib:"$(OUTDIR)\Redit.lib" /pdbtype:sept 
DEF_FILE= \
	".\REdit.def"
LINK32_OBJS= \
	"$(INTDIR)\REdit.obj" \
	"$(INTDIR)\REdit.res" \
	"$(INTDIR)\REditCtl.obj" \
	"$(INTDIR)\REditPpg.obj"

"$(OUTDIR)\Redit.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\DebugU
TargetPath=.\DebugU\Redit.ocx
InputPath=.\DebugU\Redit.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ELSEIF  "$(CFG)" == "REdit - Win32 Unicode Release"

OUTDIR=.\ReleaseU
INTDIR=.\ReleaseU
# Begin Custom Macros
OutDir=.\ReleaseU
TargetName=Redit
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OutDir)\$(TargetName).lic" "$(OUTDIR)\Redit.ocx"\
 "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OutDir)\$(TargetName).lic" "$(OUTDIR)\Redit.ocx"\
 "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\REdit.obj"
	-@erase "$(INTDIR)\REdit.res"
	-@erase "$(INTDIR)\REdit.tlb"
	-@erase "$(INTDIR)\REditCtl.obj"
	-@erase "$(INTDIR)\REditPpg.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\Redit.exp"
	-@erase "$(OUTDIR)\Redit.lib"
	-@erase "$(OUTDIR)\Redit.ocx"
	-@erase "$(OutDir)\$(TargetName).lic"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\Redit.pch"\
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
RSC_PROJ=/l 0x809 /fo"$(INTDIR)\REdit.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Redit.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\Redit.pdb" /machine:I386 /def:".\REdit.def"\
 /out:"$(OUTDIR)\Redit.ocx" /implib:"$(OUTDIR)\Redit.lib" 
DEF_FILE= \
	".\REdit.def"
LINK32_OBJS= \
	"$(INTDIR)\REdit.obj" \
	"$(INTDIR)\REdit.res" \
	"$(INTDIR)\REditCtl.obj" \
	"$(INTDIR)\REditPpg.obj"

"$(OUTDIR)\Redit.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseU
TargetPath=.\ReleaseU\Redit.ocx
InputPath=.\ReleaseU\Redit.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ENDIF 


!IF "$(CFG)" == "REdit - Win32 Release" || "$(CFG)" == "REdit - Win32 Debug" ||\
 "$(CFG)" == "REdit - Win32 Unicode Debug" || "$(CFG)" ==\
 "REdit - Win32 Unicode Release"
SOURCE=.\REdit.cpp

!IF  "$(CFG)" == "REdit - Win32 Release"

DEP_CPP_REDIT=\
	".\REdit.h"\
	{$(INCLUDE)}"Dosdefs.h"\
	{$(INCLUDE)}"Rdialog.h"\
	{$(INCLUDE)}"Rsheets.h"\
	{$(INCLUDE)}"Sheetdef.h"\
	{$(INCLUDE)}"Stdafx.h"\
	

"$(INTDIR)\REdit.obj" : $(SOURCE) $(DEP_CPP_REDIT) "$(INTDIR)"\
 "$(INTDIR)\Redit.pch"


!ELSEIF  "$(CFG)" == "REdit - Win32 Debug"

DEP_CPP_REDIT=\
	".\REdit.h"\
	{$(INCLUDE)}"Dosdefs.h"\
	{$(INCLUDE)}"Rdialog.h"\
	{$(INCLUDE)}"Rsheets.h"\
	{$(INCLUDE)}"Sheetdef.h"\
	{$(INCLUDE)}"Stdafx.h"\
	

"$(INTDIR)\REdit.obj"	"$(INTDIR)\REdit.sbr" : $(SOURCE) $(DEP_CPP_REDIT)\
 "$(INTDIR)"


!ELSEIF  "$(CFG)" == "REdit - Win32 Unicode Debug"

DEP_CPP_REDIT=\
	".\REdit.h"\
	{$(INCLUDE)}"Dosdefs.h"\
	{$(INCLUDE)}"Rdialog.h"\
	{$(INCLUDE)}"Rsheets.h"\
	{$(INCLUDE)}"Sheetdef.h"\
	{$(INCLUDE)}"Stdafx.h"\
	

"$(INTDIR)\REdit.obj" : $(SOURCE) $(DEP_CPP_REDIT) "$(INTDIR)"\
 "$(INTDIR)\Redit.pch"


!ELSEIF  "$(CFG)" == "REdit - Win32 Unicode Release"

DEP_CPP_REDIT=\
	".\REdit.h"\
	{$(INCLUDE)}"Dosdefs.h"\
	{$(INCLUDE)}"Rdialog.h"\
	{$(INCLUDE)}"Rsheets.h"\
	{$(INCLUDE)}"Sheetdef.h"\
	{$(INCLUDE)}"Stdafx.h"\
	

"$(INTDIR)\REdit.obj" : $(SOURCE) $(DEP_CPP_REDIT) "$(INTDIR)"\
 "$(INTDIR)\Redit.pch"


!ENDIF 

SOURCE=.\REdit.odl

!IF  "$(CFG)" == "REdit - Win32 Release"

MTL_SWITCHES=/nologo /D "NDEBUG" /tlb "$(OUTDIR)\REdit.tlb" /mktyplib203 /o NUL\
 /win32 

"$(OUTDIR)\REdit.tlb" : $(SOURCE) "$(OUTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "REdit - Win32 Debug"

MTL_SWITCHES=/nologo /D "_DEBUG" /tlb "$(OUTDIR)\REdit.tlb" /mktyplib203 /o NUL\
 /win32 

"$(OUTDIR)\REdit.tlb" : $(SOURCE) "$(OUTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "REdit - Win32 Unicode Debug"

MTL_SWITCHES=/nologo /D "_DEBUG" /tlb "$(OUTDIR)\REdit.tlb" /mktyplib203 /o NUL\
 /win32 

"$(OUTDIR)\REdit.tlb" : $(SOURCE) "$(OUTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "REdit - Win32 Unicode Release"

MTL_SWITCHES=/nologo /D "NDEBUG" /tlb "$(OUTDIR)\REdit.tlb" /mktyplib203 /o NUL\
 /win32 

"$(OUTDIR)\REdit.tlb" : $(SOURCE) "$(OUTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\REdit.rc

!IF  "$(CFG)" == "REdit - Win32 Release"

DEP_RSC_REDIT_=\
	".\REditCtl.bmp"\
	
NODEP_RSC_REDIT_=\
	"..\..\Release\exe\REdit.tlb"\
	

"$(INTDIR)\REdit.res" : $(SOURCE) $(DEP_RSC_REDIT_) "$(INTDIR)"\
 "..\..\Release\exe\REdit.tlb"
	$(RSC) /l 0x809 /fo"$(INTDIR)\REdit.res" /i "\mig\Release\exe" /d "NDEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "REdit - Win32 Debug"

DEP_RSC_REDIT_=\
	"..\..\Debug\exe\REdit.tlb"\
	".\REditCtl.bmp"\
	

"$(INTDIR)\REdit.res" : $(SOURCE) $(DEP_RSC_REDIT_) "$(INTDIR)"\
 "..\..\Debug\exe\REdit.tlb"
	$(RSC) /l 0x809 /fo"$(INTDIR)\REdit.res" /i "\mig\Debug\exe" /d "_DEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "REdit - Win32 Unicode Debug"

DEP_RSC_REDIT_=\
	".\REditCtl.bmp"\
	
NODEP_RSC_REDIT_=\
	".\DebugU\REdit.tlb"\
	

"$(INTDIR)\REdit.res" : $(SOURCE) $(DEP_RSC_REDIT_) "$(INTDIR)"\
 "$(INTDIR)\REdit.tlb"
	$(RSC) /l 0x809 /fo"$(INTDIR)\REdit.res" /i "DebugU" /d "_DEBUG" /d "_AFXDLL"\
 $(SOURCE)


!ELSEIF  "$(CFG)" == "REdit - Win32 Unicode Release"

DEP_RSC_REDIT_=\
	".\REditCtl.bmp"\
	
NODEP_RSC_REDIT_=\
	".\ReleaseU\REdit.tlb"\
	

"$(INTDIR)\REdit.res" : $(SOURCE) $(DEP_RSC_REDIT_) "$(INTDIR)"\
 "$(INTDIR)\REdit.tlb"
	$(RSC) /l 0x809 /fo"$(INTDIR)\REdit.res" /i "ReleaseU" /d "NDEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ENDIF 

SOURCE=.\REditCtl.cpp

!IF  "$(CFG)" == "REdit - Win32 Release"

DEP_CPP_REDITC=\
	".\REdit.h"\
	".\REditCtl.h"\
	".\REditPpg.h"\
	{$(INCLUDE)}"Dosdefs.h"\
	{$(INCLUDE)}"Rdialog.h"\
	{$(INCLUDE)}"Rsheets.h"\
	{$(INCLUDE)}"Sheetdef.h"\
	{$(INCLUDE)}"Stdafx.h"\
	

"$(INTDIR)\REditCtl.obj" : $(SOURCE) $(DEP_CPP_REDITC) "$(INTDIR)"\
 "$(INTDIR)\Redit.pch"


!ELSEIF  "$(CFG)" == "REdit - Win32 Debug"

DEP_CPP_REDITC=\
	".\REdit.h"\
	".\REditCtl.h"\
	".\REditPpg.h"\
	{$(INCLUDE)}"Dosdefs.h"\
	{$(INCLUDE)}"Rdialog.h"\
	{$(INCLUDE)}"Rsheets.h"\
	{$(INCLUDE)}"Sheetdef.h"\
	{$(INCLUDE)}"Stdafx.h"\
	

"$(INTDIR)\REditCtl.obj"	"$(INTDIR)\REditCtl.sbr" : $(SOURCE) $(DEP_CPP_REDITC)\
 "$(INTDIR)"


!ELSEIF  "$(CFG)" == "REdit - Win32 Unicode Debug"

DEP_CPP_REDITC=\
	".\REdit.h"\
	".\REditCtl.h"\
	".\REditPpg.h"\
	{$(INCLUDE)}"Dosdefs.h"\
	{$(INCLUDE)}"Rdialog.h"\
	{$(INCLUDE)}"Rsheets.h"\
	{$(INCLUDE)}"Sheetdef.h"\
	{$(INCLUDE)}"Stdafx.h"\
	

"$(INTDIR)\REditCtl.obj" : $(SOURCE) $(DEP_CPP_REDITC) "$(INTDIR)"\
 "$(INTDIR)\Redit.pch"


!ELSEIF  "$(CFG)" == "REdit - Win32 Unicode Release"

DEP_CPP_REDITC=\
	".\REdit.h"\
	".\REditCtl.h"\
	".\REditPpg.h"\
	{$(INCLUDE)}"Dosdefs.h"\
	{$(INCLUDE)}"Rdialog.h"\
	{$(INCLUDE)}"Rsheets.h"\
	{$(INCLUDE)}"Sheetdef.h"\
	{$(INCLUDE)}"Stdafx.h"\
	

"$(INTDIR)\REditCtl.obj" : $(SOURCE) $(DEP_CPP_REDITC) "$(INTDIR)"\
 "$(INTDIR)\Redit.pch"


!ENDIF 

SOURCE=.\REditPpg.cpp

!IF  "$(CFG)" == "REdit - Win32 Release"

DEP_CPP_REDITP=\
	".\REdit.h"\
	".\REditPpg.h"\
	{$(INCLUDE)}"Dosdefs.h"\
	{$(INCLUDE)}"Rdialog.h"\
	{$(INCLUDE)}"Rsheets.h"\
	{$(INCLUDE)}"Sheetdef.h"\
	{$(INCLUDE)}"Stdafx.h"\
	

"$(INTDIR)\REditPpg.obj" : $(SOURCE) $(DEP_CPP_REDITP) "$(INTDIR)"\
 "$(INTDIR)\Redit.pch"


!ELSEIF  "$(CFG)" == "REdit - Win32 Debug"

DEP_CPP_REDITP=\
	".\REdit.h"\
	".\REditPpg.h"\
	{$(INCLUDE)}"Dosdefs.h"\
	{$(INCLUDE)}"Rdialog.h"\
	{$(INCLUDE)}"Rsheets.h"\
	{$(INCLUDE)}"Sheetdef.h"\
	{$(INCLUDE)}"Stdafx.h"\
	

"$(INTDIR)\REditPpg.obj"	"$(INTDIR)\REditPpg.sbr" : $(SOURCE) $(DEP_CPP_REDITP)\
 "$(INTDIR)"


!ELSEIF  "$(CFG)" == "REdit - Win32 Unicode Debug"

DEP_CPP_REDITP=\
	".\REdit.h"\
	".\REditPpg.h"\
	{$(INCLUDE)}"Dosdefs.h"\
	{$(INCLUDE)}"Rdialog.h"\
	{$(INCLUDE)}"Rsheets.h"\
	{$(INCLUDE)}"Sheetdef.h"\
	{$(INCLUDE)}"Stdafx.h"\
	

"$(INTDIR)\REditPpg.obj" : $(SOURCE) $(DEP_CPP_REDITP) "$(INTDIR)"\
 "$(INTDIR)\Redit.pch"


!ELSEIF  "$(CFG)" == "REdit - Win32 Unicode Release"

DEP_CPP_REDITP=\
	".\REdit.h"\
	".\REditPpg.h"\
	{$(INCLUDE)}"Dosdefs.h"\
	{$(INCLUDE)}"Rdialog.h"\
	{$(INCLUDE)}"Rsheets.h"\
	{$(INCLUDE)}"Sheetdef.h"\
	{$(INCLUDE)}"Stdafx.h"\
	

"$(INTDIR)\REditPpg.obj" : $(SOURCE) $(DEP_CPP_REDITP) "$(INTDIR)"\
 "$(INTDIR)\Redit.pch"


!ENDIF 

SOURCE=.\REdit.lic

!IF  "$(CFG)" == "REdit - Win32 Release"

OutDir=\mig\Release\exe
ProjDir=.
TargetName=Redit
InputPath=.\REdit.lic

"$(OutDir)\$(TargetName).lic"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(ProjDir)\$(TargetName).lic" "$(OutDir)"

!ELSEIF  "$(CFG)" == "REdit - Win32 Debug"

OutDir=\mig\Debug\exe
ProjDir=.
TargetName=Redit
InputPath=.\REdit.lic

"$(OutDir)\$(TargetName).lic"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(ProjDir)\$(TargetName).lic" "$(OutDir)"

!ELSEIF  "$(CFG)" == "REdit - Win32 Unicode Debug"

OutDir=.\DebugU
ProjDir=.
TargetName=Redit
InputPath=.\REdit.lic

"$(OutDir)\$(TargetName).lic"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(ProjDir)\$(TargetName).lic" "$(OutDir)"

!ELSEIF  "$(CFG)" == "REdit - Win32 Unicode Release"

OutDir=.\ReleaseU
ProjDir=.
TargetName=Redit
InputPath=.\REdit.lic

"$(OutDir)\$(TargetName).lic"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(ProjDir)\$(TargetName).lic" "$(OutDir)"

!ENDIF 


!ENDIF 

