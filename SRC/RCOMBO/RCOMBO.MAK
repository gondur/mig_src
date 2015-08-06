# Microsoft Developer Studio Generated NMAKE File, Based on RCombo.dsp
!IF "$(CFG)" == ""
CFG=RCombo - Win32 Debug
!MESSAGE No configuration specified. Defaulting to RCombo - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "RCombo - Win32 Release" && "$(CFG)" != "RCombo - Win32 Debug"\
 && "$(CFG)" != "RCombo - Win32 Unicode Debug" && "$(CFG)" !=\
 "RCombo - Win32 Unicode Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "RCombo.mak" CFG="RCombo - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "RCombo - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "RCombo - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "RCombo - Win32 Unicode Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "RCombo - Win32 Unicode Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "RCombo - Win32 Release"

OUTDIR=\mig\Release\exe
INTDIR=\mig\Release\axobj
# Begin Custom Macros
OutDir=\mig\Release\exe
TargetName=RCombo
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OutDir)\$(TargetName).lic" "$(OUTDIR)\RCombo.ocx"\
 "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OutDir)\$(TargetName).lic" "$(OUTDIR)\RCombo.ocx"\
 "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\RCombo.obj"
	-@erase "$(INTDIR)\RCombo.res"
	-@erase "$(INTDIR)\RComboC.obj"
	-@erase "$(INTDIR)\RComboP.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\RCombo.exp"
	-@erase "$(OUTDIR)\RCombo.lib"
	-@erase "$(OUTDIR)\RCombo.ocx"
	-@erase "..\..\Release\exe\RCombo.tlb"
	-@erase "$(OutDir)\$(TargetName).lic"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /Fp"$(INTDIR)\RCombo.pch" /Yu"stdafx.h"\
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
RSC_PROJ=/l 0x809 /fo"$(INTDIR)\RCombo.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\RCombo.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\RCombo.pdb" /machine:I386 /def:".\RCombo.def"\
 /out:"$(OUTDIR)\RCombo.ocx" /implib:"$(OUTDIR)\RCombo.lib" 
DEF_FILE= \
	".\RCombo.def"
LINK32_OBJS= \
	"$(INTDIR)\RCombo.obj" \
	"$(INTDIR)\RCombo.res" \
	"$(INTDIR)\RComboC.obj" \
	"$(INTDIR)\RComboP.obj"

"$(OUTDIR)\RCombo.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=\mig\Release\exe
TargetPath=\mig\Release\exe\RCombo.ocx
InputPath=\mig\Release\exe\RCombo.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ELSEIF  "$(CFG)" == "RCombo - Win32 Debug"

OUTDIR=\mig\Debug\exe
INTDIR=\mig\Debug\axobj
# Begin Custom Macros
OutDir=\mig\Debug\exe
TargetName=RCombo
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OutDir)\$(TargetName).lic" "$(OUTDIR)\RCombo.ocx"\
 "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OutDir)\$(TargetName).lic" "$(OUTDIR)\RCombo.ocx"\
 "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\RCombo.obj"
	-@erase "$(INTDIR)\RCombo.res"
	-@erase "$(INTDIR)\RComboC.obj"
	-@erase "$(INTDIR)\RComboP.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\RCombo.exp"
	-@erase "$(OUTDIR)\RCombo.ilk"
	-@erase "$(OUTDIR)\RCombo.lib"
	-@erase "$(OUTDIR)\RCombo.ocx"
	-@erase "$(OUTDIR)\RCombo.pdb"
	-@erase "..\..\Debug\exe\RCombo.tlb"
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
RSC_PROJ=/l 0x809 /fo"$(INTDIR)\RCombo.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\RCombo.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)\RCombo.pdb" /debug /machine:I386 /def:".\RCombo.def"\
 /out:"$(OUTDIR)\RCombo.ocx" /implib:"$(OUTDIR)\RCombo.lib" /pdbtype:sept 
DEF_FILE= \
	".\RCombo.def"
LINK32_OBJS= \
	"$(INTDIR)\RCombo.obj" \
	"$(INTDIR)\RCombo.res" \
	"$(INTDIR)\RComboC.obj" \
	"$(INTDIR)\RComboP.obj"

"$(OUTDIR)\RCombo.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=\mig\Debug\exe
TargetPath=\mig\Debug\exe\RCombo.ocx
InputPath=\mig\Debug\exe\RCombo.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ELSEIF  "$(CFG)" == "RCombo - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
TargetName=RCombo
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OutDir)\$(TargetName).lic" "$(OUTDIR)\RCombo.ocx"\
 "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OutDir)\$(TargetName).lic" "$(OUTDIR)\RCombo.ocx"\
 "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\RCombo.obj"
	-@erase "$(INTDIR)\RCombo.res"
	-@erase "$(INTDIR)\RCombo.tlb"
	-@erase "$(INTDIR)\RComboC.obj"
	-@erase "$(INTDIR)\RComboP.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\RCombo.exp"
	-@erase "$(OUTDIR)\RCombo.ilk"
	-@erase "$(OUTDIR)\RCombo.lib"
	-@erase "$(OUTDIR)\RCombo.ocx"
	-@erase "$(OUTDIR)\RCombo.pdb"
	-@erase "$(OutDir)\$(TargetName).lic"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\RCombo.pch"\
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
RSC_PROJ=/l 0x809 /fo"$(INTDIR)\RCombo.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\RCombo.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)\RCombo.pdb" /debug /machine:I386 /def:".\RCombo.def"\
 /out:"$(OUTDIR)\RCombo.ocx" /implib:"$(OUTDIR)\RCombo.lib" /pdbtype:sept 
DEF_FILE= \
	".\RCombo.def"
LINK32_OBJS= \
	"$(INTDIR)\RCombo.obj" \
	"$(INTDIR)\RCombo.res" \
	"$(INTDIR)\RComboC.obj" \
	"$(INTDIR)\RComboP.obj"

"$(OUTDIR)\RCombo.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\DebugU
TargetPath=.\DebugU\RCombo.ocx
InputPath=.\DebugU\RCombo.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ELSEIF  "$(CFG)" == "RCombo - Win32 Unicode Release"

OUTDIR=.\ReleaseU
INTDIR=.\ReleaseU
# Begin Custom Macros
OutDir=.\ReleaseU
TargetName=RCombo
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OutDir)\$(TargetName).lic" "$(OUTDIR)\RCombo.ocx"\
 "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OutDir)\$(TargetName).lic" "$(OUTDIR)\RCombo.ocx"\
 "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\RCombo.obj"
	-@erase "$(INTDIR)\RCombo.res"
	-@erase "$(INTDIR)\RCombo.tlb"
	-@erase "$(INTDIR)\RComboC.obj"
	-@erase "$(INTDIR)\RComboP.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\RCombo.exp"
	-@erase "$(OUTDIR)\RCombo.lib"
	-@erase "$(OUTDIR)\RCombo.ocx"
	-@erase "$(OutDir)\$(TargetName).lic"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\RCombo.pch"\
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
RSC_PROJ=/l 0x809 /fo"$(INTDIR)\RCombo.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\RCombo.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\RCombo.pdb" /machine:I386 /def:".\RCombo.def"\
 /out:"$(OUTDIR)\RCombo.ocx" /implib:"$(OUTDIR)\RCombo.lib" 
DEF_FILE= \
	".\RCombo.def"
LINK32_OBJS= \
	"$(INTDIR)\RCombo.obj" \
	"$(INTDIR)\RCombo.res" \
	"$(INTDIR)\RComboC.obj" \
	"$(INTDIR)\RComboP.obj"

"$(OUTDIR)\RCombo.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseU
TargetPath=.\ReleaseU\RCombo.ocx
InputPath=.\ReleaseU\RCombo.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ENDIF 


!IF "$(CFG)" == "RCombo - Win32 Release" || "$(CFG)" == "RCombo - Win32 Debug"\
 || "$(CFG)" == "RCombo - Win32 Unicode Debug" || "$(CFG)" ==\
 "RCombo - Win32 Unicode Release"
SOURCE=.\RCombo.cpp

!IF  "$(CFG)" == "RCombo - Win32 Release"

DEP_CPP_RCOMB=\
	".\RCombo.h"\
	{$(INCLUDE)}"Dosdefs.h"\
	{$(INCLUDE)}"Rdialog.h"\
	{$(INCLUDE)}"Rsheets.h"\
	{$(INCLUDE)}"Sheetdef.h"\
	{$(INCLUDE)}"Stdafx.h"\
	

"$(INTDIR)\RCombo.obj" : $(SOURCE) $(DEP_CPP_RCOMB) "$(INTDIR)"\
 "$(INTDIR)\RCombo.pch"


!ELSEIF  "$(CFG)" == "RCombo - Win32 Debug"

DEP_CPP_RCOMB=\
	".\RCombo.h"\
	{$(INCLUDE)}"Dosdefs.h"\
	{$(INCLUDE)}"Rdialog.h"\
	{$(INCLUDE)}"Rsheets.h"\
	{$(INCLUDE)}"Sheetdef.h"\
	{$(INCLUDE)}"Stdafx.h"\
	

"$(INTDIR)\RCombo.obj" : $(SOURCE) $(DEP_CPP_RCOMB) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "RCombo - Win32 Unicode Debug"

DEP_CPP_RCOMB=\
	".\RCombo.h"\
	{$(INCLUDE)}"Dosdefs.h"\
	{$(INCLUDE)}"Rdialog.h"\
	{$(INCLUDE)}"Rsheets.h"\
	{$(INCLUDE)}"Sheetdef.h"\
	{$(INCLUDE)}"Stdafx.h"\
	

"$(INTDIR)\RCombo.obj" : $(SOURCE) $(DEP_CPP_RCOMB) "$(INTDIR)"\
 "$(INTDIR)\RCombo.pch"


!ELSEIF  "$(CFG)" == "RCombo - Win32 Unicode Release"

DEP_CPP_RCOMB=\
	".\RCombo.h"\
	{$(INCLUDE)}"Dosdefs.h"\
	{$(INCLUDE)}"Rdialog.h"\
	{$(INCLUDE)}"Rsheets.h"\
	{$(INCLUDE)}"Sheetdef.h"\
	{$(INCLUDE)}"Stdafx.h"\
	

"$(INTDIR)\RCombo.obj" : $(SOURCE) $(DEP_CPP_RCOMB) "$(INTDIR)"\
 "$(INTDIR)\RCombo.pch"


!ENDIF 

SOURCE=.\RCombo.odl

!IF  "$(CFG)" == "RCombo - Win32 Release"

MTL_SWITCHES=/nologo /D "NDEBUG" /tlb "$(OUTDIR)\RCombo.tlb" /mktyplib203 /o\
 NUL /win32 

"$(OUTDIR)\RCombo.tlb" : $(SOURCE) "$(OUTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RCombo - Win32 Debug"

MTL_SWITCHES=/nologo /D "_DEBUG" /tlb "$(OUTDIR)\RCombo.tlb" /mktyplib203 /o\
 NUL /win32 

"$(OUTDIR)\RCombo.tlb" : $(SOURCE) "$(OUTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RCombo - Win32 Unicode Debug"

MTL_SWITCHES=/nologo /D "_DEBUG" /tlb "$(OUTDIR)\RCombo.tlb" /mktyplib203 /o\
 NUL /win32 

"$(OUTDIR)\RCombo.tlb" : $(SOURCE) "$(OUTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RCombo - Win32 Unicode Release"

MTL_SWITCHES=/nologo /D "NDEBUG" /tlb "$(OUTDIR)\RCombo.tlb" /mktyplib203 /o\
 NUL /win32 

"$(OUTDIR)\RCombo.tlb" : $(SOURCE) "$(OUTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\RCombo.rc

!IF  "$(CFG)" == "RCombo - Win32 Release"

DEP_RSC_RCOMBO=\
	".\rcombobu.bmp"\
	".\RComboC.bmp"\
	
NODEP_RSC_RCOMBO=\
	"..\..\Release\exe\RCombo.tlb"\
	

"$(INTDIR)\RCombo.res" : $(SOURCE) $(DEP_RSC_RCOMBO) "$(INTDIR)"\
 "..\..\Release\exe\RCombo.tlb"
	$(RSC) /l 0x809 /fo"$(INTDIR)\RCombo.res" /i "\mig\Release\exe" /d "NDEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "RCombo - Win32 Debug"

DEP_RSC_RCOMBO=\
	"..\..\Debug\exe\RCombo.tlb"\
	".\rcombobu.bmp"\
	".\RComboC.bmp"\
	

"$(INTDIR)\RCombo.res" : $(SOURCE) $(DEP_RSC_RCOMBO) "$(INTDIR)"\
 "..\..\Debug\exe\RCombo.tlb"
	$(RSC) /l 0x809 /fo"$(INTDIR)\RCombo.res" /i "\mig\Debug\exe" /d "_DEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "RCombo - Win32 Unicode Debug"

DEP_RSC_RCOMBO=\
	".\rcombobu.bmp"\
	".\RComboC.bmp"\
	
NODEP_RSC_RCOMBO=\
	".\DebugU\RCombo.tlb"\
	

"$(INTDIR)\RCombo.res" : $(SOURCE) $(DEP_RSC_RCOMBO) "$(INTDIR)"\
 "$(INTDIR)\RCombo.tlb"
	$(RSC) /l 0x809 /fo"$(INTDIR)\RCombo.res" /i "DebugU" /d "_DEBUG" /d "_AFXDLL"\
 $(SOURCE)


!ELSEIF  "$(CFG)" == "RCombo - Win32 Unicode Release"

DEP_RSC_RCOMBO=\
	".\rcombobu.bmp"\
	".\RComboC.bmp"\
	
NODEP_RSC_RCOMBO=\
	".\ReleaseU\RCombo.tlb"\
	

"$(INTDIR)\RCombo.res" : $(SOURCE) $(DEP_RSC_RCOMBO) "$(INTDIR)"\
 "$(INTDIR)\RCombo.tlb"
	$(RSC) /l 0x809 /fo"$(INTDIR)\RCombo.res" /i "ReleaseU" /d "NDEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ENDIF 

SOURCE=.\RComboC.cpp

!IF  "$(CFG)" == "RCombo - Win32 Release"

DEP_CPP_RCOMBOC=\
	".\RCombo.h"\
	".\RComboC.h"\
	".\RComboP.h"\
	{$(INCLUDE)}"Dosdefs.h"\
	{$(INCLUDE)}"Rdialog.h"\
	{$(INCLUDE)}"Rsheets.h"\
	{$(INCLUDE)}"Sheetdef.h"\
	{$(INCLUDE)}"Stdafx.h"\
	

"$(INTDIR)\RComboC.obj" : $(SOURCE) $(DEP_CPP_RCOMBOC) "$(INTDIR)"\
 "$(INTDIR)\RCombo.pch"


!ELSEIF  "$(CFG)" == "RCombo - Win32 Debug"

DEP_CPP_RCOMBOC=\
	".\RCombo.h"\
	".\RComboC.h"\
	".\RComboP.h"\
	{$(INCLUDE)}"Dosdefs.h"\
	{$(INCLUDE)}"Rdialog.h"\
	{$(INCLUDE)}"Rsheets.h"\
	{$(INCLUDE)}"Sheetdef.h"\
	{$(INCLUDE)}"Stdafx.h"\
	

"$(INTDIR)\RComboC.obj" : $(SOURCE) $(DEP_CPP_RCOMBOC) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "RCombo - Win32 Unicode Debug"

DEP_CPP_RCOMBOC=\
	".\RCombo.h"\
	".\RComboC.h"\
	".\RComboP.h"\
	{$(INCLUDE)}"Dosdefs.h"\
	{$(INCLUDE)}"Rdialog.h"\
	{$(INCLUDE)}"Rsheets.h"\
	{$(INCLUDE)}"Sheetdef.h"\
	{$(INCLUDE)}"Stdafx.h"\
	

"$(INTDIR)\RComboC.obj" : $(SOURCE) $(DEP_CPP_RCOMBOC) "$(INTDIR)"\
 "$(INTDIR)\RCombo.pch"


!ELSEIF  "$(CFG)" == "RCombo - Win32 Unicode Release"

DEP_CPP_RCOMBOC=\
	".\RCombo.h"\
	".\RComboC.h"\
	".\RComboP.h"\
	{$(INCLUDE)}"Dosdefs.h"\
	{$(INCLUDE)}"Rdialog.h"\
	{$(INCLUDE)}"Rsheets.h"\
	{$(INCLUDE)}"Sheetdef.h"\
	{$(INCLUDE)}"Stdafx.h"\
	

"$(INTDIR)\RComboC.obj" : $(SOURCE) $(DEP_CPP_RCOMBOC) "$(INTDIR)"\
 "$(INTDIR)\RCombo.pch"


!ENDIF 

SOURCE=.\RComboP.cpp

!IF  "$(CFG)" == "RCombo - Win32 Release"

DEP_CPP_RCOMBOP=\
	".\RCombo.h"\
	".\RComboP.h"\
	{$(INCLUDE)}"Dosdefs.h"\
	{$(INCLUDE)}"Rdialog.h"\
	{$(INCLUDE)}"Rsheets.h"\
	{$(INCLUDE)}"Sheetdef.h"\
	{$(INCLUDE)}"Stdafx.h"\
	

"$(INTDIR)\RComboP.obj" : $(SOURCE) $(DEP_CPP_RCOMBOP) "$(INTDIR)"\
 "$(INTDIR)\RCombo.pch"


!ELSEIF  "$(CFG)" == "RCombo - Win32 Debug"

DEP_CPP_RCOMBOP=\
	".\RCombo.h"\
	".\RComboP.h"\
	{$(INCLUDE)}"Dosdefs.h"\
	{$(INCLUDE)}"Rdialog.h"\
	{$(INCLUDE)}"Rsheets.h"\
	{$(INCLUDE)}"Sheetdef.h"\
	{$(INCLUDE)}"Stdafx.h"\
	

"$(INTDIR)\RComboP.obj" : $(SOURCE) $(DEP_CPP_RCOMBOP) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "RCombo - Win32 Unicode Debug"

DEP_CPP_RCOMBOP=\
	".\RCombo.h"\
	".\RComboP.h"\
	{$(INCLUDE)}"Dosdefs.h"\
	{$(INCLUDE)}"Rdialog.h"\
	{$(INCLUDE)}"Rsheets.h"\
	{$(INCLUDE)}"Sheetdef.h"\
	{$(INCLUDE)}"Stdafx.h"\
	

"$(INTDIR)\RComboP.obj" : $(SOURCE) $(DEP_CPP_RCOMBOP) "$(INTDIR)"\
 "$(INTDIR)\RCombo.pch"


!ELSEIF  "$(CFG)" == "RCombo - Win32 Unicode Release"

DEP_CPP_RCOMBOP=\
	".\RCombo.h"\
	".\RComboP.h"\
	{$(INCLUDE)}"Dosdefs.h"\
	{$(INCLUDE)}"Rdialog.h"\
	{$(INCLUDE)}"Rsheets.h"\
	{$(INCLUDE)}"Sheetdef.h"\
	{$(INCLUDE)}"Stdafx.h"\
	

"$(INTDIR)\RComboP.obj" : $(SOURCE) $(DEP_CPP_RCOMBOP) "$(INTDIR)"\
 "$(INTDIR)\RCombo.pch"


!ENDIF 

SOURCE=.\RCombo.lic

!IF  "$(CFG)" == "RCombo - Win32 Release"

OutDir=\mig\Release\exe
ProjDir=.
TargetName=RCombo
InputPath=.\RCombo.lic

"$(OutDir)\$(TargetName).lic"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(ProjDir)\$(TargetName).lic" "$(OutDir)"

!ELSEIF  "$(CFG)" == "RCombo - Win32 Debug"

OutDir=\mig\Debug\exe
ProjDir=.
TargetName=RCombo
InputPath=.\RCombo.lic

"$(OutDir)\$(TargetName).lic"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(ProjDir)\$(TargetName).lic" "$(OutDir)"

!ELSEIF  "$(CFG)" == "RCombo - Win32 Unicode Debug"

OutDir=.\DebugU
ProjDir=.
TargetName=RCombo
InputPath=.\RCombo.lic

"$(OutDir)\$(TargetName).lic"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(ProjDir)\$(TargetName).lic" "$(OutDir)"

!ELSEIF  "$(CFG)" == "RCombo - Win32 Unicode Release"

OutDir=.\ReleaseU
ProjDir=.
TargetName=RCombo
InputPath=.\RCombo.lic

"$(OutDir)\$(TargetName).lic"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(ProjDir)\$(TargetName).lic" "$(OutDir)"

!ENDIF 


!ENDIF 

