# Microsoft Developer Studio Generated NMAKE File, Based on REdtBt.dsp
!IF "$(CFG)" == ""
CFG=REdtBt - Win32 Debug
!MESSAGE No configuration specified. Defaulting to REdtBt - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "REdtBt - Win32 Release" && "$(CFG)" != "REdtBt - Win32 Debug"\
 && "$(CFG)" != "REdtBt - Win32 Unicode Debug" && "$(CFG)" !=\
 "REdtBt - Win32 Unicode Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "REdtBt.mak" CFG="REdtBt - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "REdtBt - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "REdtBt - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "REdtBt - Win32 Unicode Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "REdtBt - Win32 Unicode Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "REdtBt - Win32 Release"

OUTDIR=\mig\Release\exe
INTDIR=\mig\Release\axobj
# Begin Custom Macros
OutDir=\mig\Release\exe
TargetName=REdtBt
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OutDir)\$(TargetName).lic" "$(OUTDIR)\REdtBt.ocx"\
 "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OutDir)\$(TargetName).lic" "$(OUTDIR)\REdtBt.ocx"\
 "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\REdtBt.obj"
	-@erase "$(INTDIR)\REdtBt.res"
	-@erase "$(INTDIR)\redtbtc.obj"
	-@erase "$(INTDIR)\redtbtp.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\REdtBt.exp"
	-@erase "$(OUTDIR)\REdtBt.lib"
	-@erase "$(OUTDIR)\REdtBt.ocx"
	-@erase "..\..\Release\exe\REdtBt.tlb"
	-@erase "$(OutDir)\$(TargetName).lic"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /Fp"$(INTDIR)\REdtBt.pch" /Yu"stdafx.h"\
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
RSC_PROJ=/l 0x809 /fo"$(INTDIR)\REdtBt.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\REdtBt.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\REdtBt.pdb" /machine:I386 /def:".\REdtBt.def"\
 /out:"$(OUTDIR)\REdtBt.ocx" /implib:"$(OUTDIR)\REdtBt.lib" 
DEF_FILE= \
	".\REdtBt.def"
LINK32_OBJS= \
	"$(INTDIR)\REdtBt.obj" \
	"$(INTDIR)\REdtBt.res" \
	"$(INTDIR)\redtbtc.obj" \
	"$(INTDIR)\redtbtp.obj"

"$(OUTDIR)\REdtBt.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=\mig\Release\exe
TargetPath=\mig\Release\exe\REdtBt.ocx
InputPath=\mig\Release\exe\REdtBt.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ELSEIF  "$(CFG)" == "REdtBt - Win32 Debug"

OUTDIR=\mig\Debug\exe
INTDIR=\mig\Debug\axobj
# Begin Custom Macros
OutDir=\mig\Debug\exe
TargetName=REdtBt
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OutDir)\$(TargetName).lic" "$(OUTDIR)\REdtBt.ocx"\
 "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OutDir)\$(TargetName).lic" "$(OUTDIR)\REdtBt.ocx"\
 "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\REdtBt.obj"
	-@erase "$(INTDIR)\REdtBt.res"
	-@erase "$(INTDIR)\redtbtc.obj"
	-@erase "$(INTDIR)\redtbtp.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\REdtBt.exp"
	-@erase "$(OUTDIR)\REdtBt.ilk"
	-@erase "$(OUTDIR)\REdtBt.lib"
	-@erase "$(OUTDIR)\REdtBt.ocx"
	-@erase "$(OUTDIR)\REdtBt.pdb"
	-@erase "..\..\Debug\exe\REdtBt.tlb"
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
RSC_PROJ=/l 0x809 /fo"$(INTDIR)\REdtBt.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\REdtBt.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)\REdtBt.pdb" /debug /machine:I386 /def:".\REdtBt.def"\
 /out:"$(OUTDIR)\REdtBt.ocx" /implib:"$(OUTDIR)\REdtBt.lib" /pdbtype:sept 
DEF_FILE= \
	".\REdtBt.def"
LINK32_OBJS= \
	"$(INTDIR)\REdtBt.obj" \
	"$(INTDIR)\REdtBt.res" \
	"$(INTDIR)\redtbtc.obj" \
	"$(INTDIR)\redtbtp.obj"

"$(OUTDIR)\REdtBt.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=\mig\Debug\exe
TargetPath=\mig\Debug\exe\REdtBt.ocx
InputPath=\mig\Debug\exe\REdtBt.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ELSEIF  "$(CFG)" == "REdtBt - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
TargetName=REdtBt
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OutDir)\$(TargetName).lic" "$(OUTDIR)\REdtBt.ocx"\
 "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OutDir)\$(TargetName).lic" "$(OUTDIR)\REdtBt.ocx"\
 "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\REdtBt.obj"
	-@erase "$(INTDIR)\REdtBt.res"
	-@erase "$(INTDIR)\REdtBt.tlb"
	-@erase "$(INTDIR)\redtbtc.obj"
	-@erase "$(INTDIR)\redtbtp.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\REdtBt.exp"
	-@erase "$(OUTDIR)\REdtBt.ilk"
	-@erase "$(OUTDIR)\REdtBt.lib"
	-@erase "$(OUTDIR)\REdtBt.ocx"
	-@erase "$(OUTDIR)\REdtBt.pdb"
	-@erase "$(OutDir)\$(TargetName).lic"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\REdtBt.pch"\
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
RSC_PROJ=/l 0x809 /fo"$(INTDIR)\REdtBt.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\REdtBt.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)\REdtBt.pdb" /debug /machine:I386 /def:".\REdtBt.def"\
 /out:"$(OUTDIR)\REdtBt.ocx" /implib:"$(OUTDIR)\REdtBt.lib" /pdbtype:sept 
DEF_FILE= \
	".\REdtBt.def"
LINK32_OBJS= \
	"$(INTDIR)\REdtBt.obj" \
	"$(INTDIR)\REdtBt.res" \
	"$(INTDIR)\redtbtc.obj" \
	"$(INTDIR)\redtbtp.obj"

"$(OUTDIR)\REdtBt.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\DebugU
TargetPath=.\DebugU\REdtBt.ocx
InputPath=.\DebugU\REdtBt.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ELSEIF  "$(CFG)" == "REdtBt - Win32 Unicode Release"

OUTDIR=.\ReleaseU
INTDIR=.\ReleaseU
# Begin Custom Macros
OutDir=.\ReleaseU
TargetName=REdtBt
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OutDir)\$(TargetName).lic" "$(OUTDIR)\REdtBt.ocx"\
 "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OutDir)\$(TargetName).lic" "$(OUTDIR)\REdtBt.ocx"\
 "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\REdtBt.obj"
	-@erase "$(INTDIR)\REdtBt.res"
	-@erase "$(INTDIR)\REdtBt.tlb"
	-@erase "$(INTDIR)\redtbtc.obj"
	-@erase "$(INTDIR)\redtbtp.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\REdtBt.exp"
	-@erase "$(OUTDIR)\REdtBt.lib"
	-@erase "$(OUTDIR)\REdtBt.ocx"
	-@erase "$(OutDir)\$(TargetName).lic"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\REdtBt.pch"\
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
RSC_PROJ=/l 0x809 /fo"$(INTDIR)\REdtBt.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\REdtBt.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\REdtBt.pdb" /machine:I386 /def:".\REdtBt.def"\
 /out:"$(OUTDIR)\REdtBt.ocx" /implib:"$(OUTDIR)\REdtBt.lib" 
DEF_FILE= \
	".\REdtBt.def"
LINK32_OBJS= \
	"$(INTDIR)\REdtBt.obj" \
	"$(INTDIR)\REdtBt.res" \
	"$(INTDIR)\redtbtc.obj" \
	"$(INTDIR)\redtbtp.obj"

"$(OUTDIR)\REdtBt.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseU
TargetPath=.\ReleaseU\REdtBt.ocx
InputPath=.\ReleaseU\REdtBt.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ENDIF 


!IF "$(CFG)" == "REdtBt - Win32 Release" || "$(CFG)" == "REdtBt - Win32 Debug"\
 || "$(CFG)" == "REdtBt - Win32 Unicode Debug" || "$(CFG)" ==\
 "REdtBt - Win32 Unicode Release"
SOURCE=.\REdtBt.cpp

!IF  "$(CFG)" == "REdtBt - Win32 Release"

DEP_CPP_REDTB=\
	".\REdtBt.h"\
	{$(INCLUDE)}"Dosdefs.h"\
	{$(INCLUDE)}"Rdialog.h"\
	{$(INCLUDE)}"Rsheets.h"\
	{$(INCLUDE)}"Sheetdef.h"\
	{$(INCLUDE)}"Stdafx.h"\
	

"$(INTDIR)\REdtBt.obj" : $(SOURCE) $(DEP_CPP_REDTB) "$(INTDIR)"\
 "$(INTDIR)\REdtBt.pch"


!ELSEIF  "$(CFG)" == "REdtBt - Win32 Debug"

DEP_CPP_REDTB=\
	".\REdtBt.h"\
	{$(INCLUDE)}"Dosdefs.h"\
	{$(INCLUDE)}"Rdialog.h"\
	{$(INCLUDE)}"Rsheets.h"\
	{$(INCLUDE)}"Sheetdef.h"\
	{$(INCLUDE)}"Stdafx.h"\
	

"$(INTDIR)\REdtBt.obj" : $(SOURCE) $(DEP_CPP_REDTB) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "REdtBt - Win32 Unicode Debug"

DEP_CPP_REDTB=\
	".\REdtBt.h"\
	{$(INCLUDE)}"Dosdefs.h"\
	{$(INCLUDE)}"Rdialog.h"\
	{$(INCLUDE)}"Rsheets.h"\
	{$(INCLUDE)}"Sheetdef.h"\
	{$(INCLUDE)}"Stdafx.h"\
	

"$(INTDIR)\REdtBt.obj" : $(SOURCE) $(DEP_CPP_REDTB) "$(INTDIR)"\
 "$(INTDIR)\REdtBt.pch"


!ELSEIF  "$(CFG)" == "REdtBt - Win32 Unicode Release"

DEP_CPP_REDTB=\
	".\REdtBt.h"\
	{$(INCLUDE)}"Dosdefs.h"\
	{$(INCLUDE)}"Rdialog.h"\
	{$(INCLUDE)}"Rsheets.h"\
	{$(INCLUDE)}"Sheetdef.h"\
	{$(INCLUDE)}"Stdafx.h"\
	

"$(INTDIR)\REdtBt.obj" : $(SOURCE) $(DEP_CPP_REDTB) "$(INTDIR)"\
 "$(INTDIR)\REdtBt.pch"


!ENDIF 

SOURCE=.\REdtBt.odl

!IF  "$(CFG)" == "REdtBt - Win32 Release"

MTL_SWITCHES=/nologo /D "NDEBUG" /tlb "$(OUTDIR)\REdtBt.tlb" /mktyplib203 /o\
 NUL /win32 

"$(OUTDIR)\REdtBt.tlb" : $(SOURCE) "$(OUTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "REdtBt - Win32 Debug"

MTL_SWITCHES=/nologo /D "_DEBUG" /tlb "$(OUTDIR)\REdtBt.tlb" /mktyplib203 /o\
 NUL /win32 

"$(OUTDIR)\REdtBt.tlb" : $(SOURCE) "$(OUTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "REdtBt - Win32 Unicode Debug"

MTL_SWITCHES=/nologo /D "_DEBUG" /tlb "$(OUTDIR)\REdtBt.tlb" /mktyplib203 /o\
 NUL /win32 

"$(OUTDIR)\REdtBt.tlb" : $(SOURCE) "$(OUTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "REdtBt - Win32 Unicode Release"

MTL_SWITCHES=/nologo /D "NDEBUG" /tlb "$(OUTDIR)\REdtBt.tlb" /mktyplib203 /o\
 NUL /win32 

"$(OUTDIR)\REdtBt.tlb" : $(SOURCE) "$(OUTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\REdtBt.rc

!IF  "$(CFG)" == "REdtBt - Win32 Release"

DEP_RSC_REDTBT=\
	".\rcombobu.bmp"\
	".\redtbtc.bmp"\
	
NODEP_RSC_REDTBT=\
	"..\..\Release\exe\REdtBt.tlb"\
	

"$(INTDIR)\REdtBt.res" : $(SOURCE) $(DEP_RSC_REDTBT) "$(INTDIR)"\
 "..\..\Release\exe\REdtBt.tlb"
	$(RSC) /l 0x809 /fo"$(INTDIR)\REdtBt.res" /i "\mig\Release\exe" /d "NDEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "REdtBt - Win32 Debug"

DEP_RSC_REDTBT=\
	"..\..\Debug\exe\REdtBt.tlb"\
	".\rcombobu.bmp"\
	".\redtbtc.bmp"\
	

"$(INTDIR)\REdtBt.res" : $(SOURCE) $(DEP_RSC_REDTBT) "$(INTDIR)"\
 "..\..\Debug\exe\REdtBt.tlb"
	$(RSC) /l 0x809 /fo"$(INTDIR)\REdtBt.res" /i "\mig\Debug\exe" /d "_DEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "REdtBt - Win32 Unicode Debug"

DEP_RSC_REDTBT=\
	".\rcombobu.bmp"\
	".\redtbtc.bmp"\
	
NODEP_RSC_REDTBT=\
	".\DebugU\REdtBt.tlb"\
	

"$(INTDIR)\REdtBt.res" : $(SOURCE) $(DEP_RSC_REDTBT) "$(INTDIR)"\
 "$(INTDIR)\REdtBt.tlb"
	$(RSC) /l 0x809 /fo"$(INTDIR)\REdtBt.res" /i "DebugU" /d "_DEBUG" /d "_AFXDLL"\
 $(SOURCE)


!ELSEIF  "$(CFG)" == "REdtBt - Win32 Unicode Release"

DEP_RSC_REDTBT=\
	".\rcombobu.bmp"\
	".\redtbtc.bmp"\
	
NODEP_RSC_REDTBT=\
	".\ReleaseU\REdtBt.tlb"\
	

"$(INTDIR)\REdtBt.res" : $(SOURCE) $(DEP_RSC_REDTBT) "$(INTDIR)"\
 "$(INTDIR)\REdtBt.tlb"
	$(RSC) /l 0x809 /fo"$(INTDIR)\REdtBt.res" /i "ReleaseU" /d "NDEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ENDIF 

SOURCE=.\redtbtc.cpp

!IF  "$(CFG)" == "REdtBt - Win32 Release"

DEP_CPP_REDTBTC=\
	".\REdtBt.h"\
	".\redtbtc.h"\
	".\redtbtp.h"\
	{$(INCLUDE)}"Dosdefs.h"\
	{$(INCLUDE)}"Rdialog.h"\
	{$(INCLUDE)}"Rsheets.h"\
	{$(INCLUDE)}"Sheetdef.h"\
	{$(INCLUDE)}"Stdafx.h"\
	

"$(INTDIR)\redtbtc.obj" : $(SOURCE) $(DEP_CPP_REDTBTC) "$(INTDIR)"\
 "$(INTDIR)\REdtBt.pch"


!ELSEIF  "$(CFG)" == "REdtBt - Win32 Debug"

DEP_CPP_REDTBTC=\
	".\REdtBt.h"\
	".\redtbtc.h"\
	".\redtbtp.h"\
	{$(INCLUDE)}"Dosdefs.h"\
	{$(INCLUDE)}"Rdialog.h"\
	{$(INCLUDE)}"Rsheets.h"\
	{$(INCLUDE)}"Sheetdef.h"\
	{$(INCLUDE)}"Stdafx.h"\
	

"$(INTDIR)\redtbtc.obj" : $(SOURCE) $(DEP_CPP_REDTBTC) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "REdtBt - Win32 Unicode Debug"

DEP_CPP_REDTBTC=\
	".\REdtBt.h"\
	".\redtbtc.h"\
	".\redtbtp.h"\
	{$(INCLUDE)}"Dosdefs.h"\
	{$(INCLUDE)}"Rdialog.h"\
	{$(INCLUDE)}"Rsheets.h"\
	{$(INCLUDE)}"Sheetdef.h"\
	{$(INCLUDE)}"Stdafx.h"\
	

"$(INTDIR)\redtbtc.obj" : $(SOURCE) $(DEP_CPP_REDTBTC) "$(INTDIR)"\
 "$(INTDIR)\REdtBt.pch"


!ELSEIF  "$(CFG)" == "REdtBt - Win32 Unicode Release"

DEP_CPP_REDTBTC=\
	".\REdtBt.h"\
	".\redtbtc.h"\
	".\redtbtp.h"\
	{$(INCLUDE)}"Dosdefs.h"\
	{$(INCLUDE)}"Rdialog.h"\
	{$(INCLUDE)}"Rsheets.h"\
	{$(INCLUDE)}"Sheetdef.h"\
	{$(INCLUDE)}"Stdafx.h"\
	

"$(INTDIR)\redtbtc.obj" : $(SOURCE) $(DEP_CPP_REDTBTC) "$(INTDIR)"\
 "$(INTDIR)\REdtBt.pch"


!ENDIF 

SOURCE=.\redtbtp.cpp

!IF  "$(CFG)" == "REdtBt - Win32 Release"

DEP_CPP_REDTBTP=\
	".\REdtBt.h"\
	".\redtbtp.h"\
	{$(INCLUDE)}"Dosdefs.h"\
	{$(INCLUDE)}"Rdialog.h"\
	{$(INCLUDE)}"Rsheets.h"\
	{$(INCLUDE)}"Sheetdef.h"\
	{$(INCLUDE)}"Stdafx.h"\
	

"$(INTDIR)\redtbtp.obj" : $(SOURCE) $(DEP_CPP_REDTBTP) "$(INTDIR)"\
 "$(INTDIR)\REdtBt.pch"


!ELSEIF  "$(CFG)" == "REdtBt - Win32 Debug"

DEP_CPP_REDTBTP=\
	".\REdtBt.h"\
	".\redtbtp.h"\
	{$(INCLUDE)}"Dosdefs.h"\
	{$(INCLUDE)}"Rdialog.h"\
	{$(INCLUDE)}"Rsheets.h"\
	{$(INCLUDE)}"Sheetdef.h"\
	{$(INCLUDE)}"Stdafx.h"\
	

"$(INTDIR)\redtbtp.obj" : $(SOURCE) $(DEP_CPP_REDTBTP) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "REdtBt - Win32 Unicode Debug"

DEP_CPP_REDTBTP=\
	".\REdtBt.h"\
	".\redtbtp.h"\
	{$(INCLUDE)}"Dosdefs.h"\
	{$(INCLUDE)}"Rdialog.h"\
	{$(INCLUDE)}"Rsheets.h"\
	{$(INCLUDE)}"Sheetdef.h"\
	{$(INCLUDE)}"Stdafx.h"\
	

"$(INTDIR)\redtbtp.obj" : $(SOURCE) $(DEP_CPP_REDTBTP) "$(INTDIR)"\
 "$(INTDIR)\REdtBt.pch"


!ELSEIF  "$(CFG)" == "REdtBt - Win32 Unicode Release"

DEP_CPP_REDTBTP=\
	".\REdtBt.h"\
	".\redtbtp.h"\
	{$(INCLUDE)}"Dosdefs.h"\
	{$(INCLUDE)}"Rdialog.h"\
	{$(INCLUDE)}"Rsheets.h"\
	{$(INCLUDE)}"Sheetdef.h"\
	{$(INCLUDE)}"Stdafx.h"\
	

"$(INTDIR)\redtbtp.obj" : $(SOURCE) $(DEP_CPP_REDTBTP) "$(INTDIR)"\
 "$(INTDIR)\REdtBt.pch"


!ENDIF 

SOURCE=.\REdtBt.lic

!IF  "$(CFG)" == "REdtBt - Win32 Release"

OutDir=\mig\Release\exe
ProjDir=.
TargetName=REdtBt
InputPath=.\REdtBt.lic

"$(OutDir)\$(TargetName).lic"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(ProjDir)\$(TargetName).lic" "$(OutDir)"

!ELSEIF  "$(CFG)" == "REdtBt - Win32 Debug"

OutDir=\mig\Debug\exe
ProjDir=.
TargetName=REdtBt
InputPath=.\REdtBt.lic

"$(OutDir)\$(TargetName).lic"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(ProjDir)\$(TargetName).lic" "$(OutDir)"

!ELSEIF  "$(CFG)" == "REdtBt - Win32 Unicode Debug"

OutDir=.\DebugU
ProjDir=.
TargetName=REdtBt
InputPath=.\REdtBt.lic

"$(OutDir)\$(TargetName).lic"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(ProjDir)\$(TargetName).lic" "$(OutDir)"

!ELSEIF  "$(CFG)" == "REdtBt - Win32 Unicode Release"

OutDir=.\ReleaseU
ProjDir=.
TargetName=REdtBt
InputPath=.\REdtBt.lic

"$(OutDir)\$(TargetName).lic"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(ProjDir)\$(TargetName).lic" "$(OutDir)"

!ENDIF 


!ENDIF 

