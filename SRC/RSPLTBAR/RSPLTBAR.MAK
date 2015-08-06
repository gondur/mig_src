# Microsoft Developer Studio Generated NMAKE File, Based on RSpltBar.dsp
!IF "$(CFG)" == ""
CFG=RSpltBar - Win32 Debug
!MESSAGE No configuration specified. Defaulting to RSpltBar - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "RSpltBar - Win32 Release" && "$(CFG)" !=\
 "RSpltBar - Win32 Debug" && "$(CFG)" != "RSpltBar - Win32 Unicode Debug" &&\
 "$(CFG)" != "RSpltBar - Win32 Unicode Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "RSpltBar.mak" CFG="RSpltBar - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "RSpltBar - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "RSpltBar - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "RSpltBar - Win32 Unicode Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "RSpltBar - Win32 Unicode Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "RSpltBar - Win32 Release"

OUTDIR=\mig\Release\exe
INTDIR=\mig\Release\axobj
# Begin Custom Macros
OutDir=\mig\Release\exe
TargetName=RSpltBar
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OutDir)\$(TargetName).lic" "$(OUTDIR)\RSpltBar.ocx"

!ELSE 

ALL : "$(OutDir)\$(TargetName).lic" "$(OUTDIR)\RSpltBar.ocx"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\RSpltBar.obj"
	-@erase "$(INTDIR)\RSpltBar.res"
	-@erase "$(INTDIR)\rspltbC.obj"
	-@erase "$(INTDIR)\rspltbP.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\RSpltBar.exp"
	-@erase "$(OUTDIR)\RSpltBar.lib"
	-@erase "$(OUTDIR)\RSpltBar.ocx"
	-@erase "..\..\Release\exe\RSpltBar.tlb"
	-@erase "$(OutDir)\$(TargetName).lic"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /Fp"$(INTDIR)\RSpltBar.pch" /Yu"stdafx.h"\
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
RSC_PROJ=/l 0x809 /fo"$(INTDIR)\RSpltBar.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\RSpltBar.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\RSpltBar.pdb" /machine:I386 /def:".\RSpltBar.def"\
 /out:"$(OUTDIR)\RSpltBar.ocx" /implib:"$(OUTDIR)\RSpltBar.lib" 
DEF_FILE= \
	".\RSpltBar.def"
LINK32_OBJS= \
	"$(INTDIR)\RSpltBar.obj" \
	"$(INTDIR)\RSpltBar.res" \
	"$(INTDIR)\rspltbC.obj" \
	"$(INTDIR)\rspltbP.obj"

"$(OUTDIR)\RSpltBar.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "RSpltBar - Win32 Debug"

OUTDIR=\mig\debug\exe
INTDIR=\mig\Debug\axobj
# Begin Custom Macros
OutDir=\mig\debug\exe
TargetName=RSpltBar
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OutDir)\$(TargetName).lic" "$(OUTDIR)\RSpltBar.ocx"\
 "$(OUTDIR)\RSpltBar.bsc" "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OutDir)\$(TargetName).lic" "$(OUTDIR)\RSpltBar.ocx"\
 "$(OUTDIR)\RSpltBar.bsc" "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\RSpltBar.obj"
	-@erase "$(INTDIR)\RSpltBar.res"
	-@erase "$(INTDIR)\RSpltBar.sbr"
	-@erase "$(INTDIR)\rspltbC.obj"
	-@erase "$(INTDIR)\rspltbC.sbr"
	-@erase "$(INTDIR)\rspltbP.obj"
	-@erase "$(INTDIR)\rspltbP.sbr"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\RSpltBar.bsc"
	-@erase "$(OUTDIR)\RSpltBar.exp"
	-@erase "$(OUTDIR)\RSpltBar.ilk"
	-@erase "$(OUTDIR)\RSpltBar.lib"
	-@erase "$(OUTDIR)\RSpltBar.ocx"
	-@erase "$(OUTDIR)\RSpltBar.pdb"
	-@erase "..\..\debug\exe\RSpltBar.tlb"
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
RSC_PROJ=/l 0x809 /fo"$(INTDIR)\RSpltBar.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\RSpltBar.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\RSpltBar.sbr" \
	"$(INTDIR)\rspltbC.sbr" \
	"$(INTDIR)\rspltbP.sbr"

"$(OUTDIR)\RSpltBar.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)\RSpltBar.pdb" /debug /machine:I386 /def:".\RSpltBar.def"\
 /out:"$(OUTDIR)\RSpltBar.ocx" /implib:"$(OUTDIR)\RSpltBar.lib" /pdbtype:sept 
DEF_FILE= \
	".\RSpltBar.def"
LINK32_OBJS= \
	"$(INTDIR)\RSpltBar.obj" \
	"$(INTDIR)\RSpltBar.res" \
	"$(INTDIR)\rspltbC.obj" \
	"$(INTDIR)\rspltbP.obj"

"$(OUTDIR)\RSpltBar.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=\mig\debug\exe
TargetPath=\mig\debug\exe\RSpltBar.ocx
InputPath=\mig\debug\exe\RSpltBar.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > $(OutDir)\regsvr32.trg 
	

!ELSEIF  "$(CFG)" == "RSpltBar - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
TargetName=RSpltBar
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OutDir)\$(TargetName).lic" "$(OUTDIR)\RSpltBar.ocx"\
 "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OutDir)\$(TargetName).lic" "$(OUTDIR)\RSpltBar.ocx"\
 "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\RSpltBar.obj"
	-@erase "$(INTDIR)\RSpltBar.res"
	-@erase "$(INTDIR)\RSpltBar.tlb"
	-@erase "$(INTDIR)\rspltbC.obj"
	-@erase "$(INTDIR)\rspltbP.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\RSpltBar.exp"
	-@erase "$(OUTDIR)\RSpltBar.ilk"
	-@erase "$(OUTDIR)\RSpltBar.lib"
	-@erase "$(OUTDIR)\RSpltBar.ocx"
	-@erase "$(OUTDIR)\RSpltBar.pdb"
	-@erase "$(OutDir)\$(TargetName).lic"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE"\
 /Fp"$(INTDIR)\RSpltBar.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD\
 /c 
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
RSC_PROJ=/l 0x809 /fo"$(INTDIR)\RSpltBar.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\RSpltBar.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)\RSpltBar.pdb" /debug /machine:I386 /def:".\RSpltBar.def"\
 /out:"$(OUTDIR)\RSpltBar.ocx" /implib:"$(OUTDIR)\RSpltBar.lib" /pdbtype:sept 
DEF_FILE= \
	".\RSpltBar.def"
LINK32_OBJS= \
	"$(INTDIR)\RSpltBar.obj" \
	"$(INTDIR)\RSpltBar.res" \
	"$(INTDIR)\rspltbC.obj" \
	"$(INTDIR)\rspltbP.obj"

"$(OUTDIR)\RSpltBar.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\DebugU
TargetPath=.\DebugU\RSpltBar.ocx
InputPath=.\DebugU\RSpltBar.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ELSEIF  "$(CFG)" == "RSpltBar - Win32 Unicode Release"

OUTDIR=.\ReleaseU
INTDIR=.\ReleaseU
# Begin Custom Macros
OutDir=.\ReleaseU
TargetName=RSpltBar
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OutDir)\$(TargetName).lic" "$(OUTDIR)\RSpltBar.ocx"\
 "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OutDir)\$(TargetName).lic" "$(OUTDIR)\RSpltBar.ocx"\
 "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\RSpltBar.obj"
	-@erase "$(INTDIR)\RSpltBar.res"
	-@erase "$(INTDIR)\RSpltBar.tlb"
	-@erase "$(INTDIR)\rspltbC.obj"
	-@erase "$(INTDIR)\rspltbP.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\RSpltBar.exp"
	-@erase "$(OUTDIR)\RSpltBar.lib"
	-@erase "$(OUTDIR)\RSpltBar.ocx"
	-@erase "$(OutDir)\$(TargetName).lic"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\RSpltBar.pch"\
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
RSC_PROJ=/l 0x809 /fo"$(INTDIR)\RSpltBar.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\RSpltBar.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\RSpltBar.pdb" /machine:I386 /def:".\RSpltBar.def"\
 /out:"$(OUTDIR)\RSpltBar.ocx" /implib:"$(OUTDIR)\RSpltBar.lib" 
DEF_FILE= \
	".\RSpltBar.def"
LINK32_OBJS= \
	"$(INTDIR)\RSpltBar.obj" \
	"$(INTDIR)\RSpltBar.res" \
	"$(INTDIR)\rspltbC.obj" \
	"$(INTDIR)\rspltbP.obj"

"$(OUTDIR)\RSpltBar.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseU
TargetPath=.\ReleaseU\RSpltBar.ocx
InputPath=.\ReleaseU\RSpltBar.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > $(OutDir)\regsvr32.trg 
	

!ENDIF 


!IF "$(CFG)" == "RSpltBar - Win32 Release" || "$(CFG)" ==\
 "RSpltBar - Win32 Debug" || "$(CFG)" == "RSpltBar - Win32 Unicode Debug" ||\
 "$(CFG)" == "RSpltBar - Win32 Unicode Release"
SOURCE=.\RSpltBar.cpp

!IF  "$(CFG)" == "RSpltBar - Win32 Release"

DEP_CPP_RSPLT=\
	".\RSpltBar.h"\
	{$(INCLUDE)}"Dosdefs.h"\
	{$(INCLUDE)}"Rdialog.h"\
	{$(INCLUDE)}"Rsheets.h"\
	{$(INCLUDE)}"Sheetdef.h"\
	{$(INCLUDE)}"Stdafx.h"\
	

"$(INTDIR)\RSpltBar.obj" : $(SOURCE) $(DEP_CPP_RSPLT) "$(INTDIR)"\
 "$(INTDIR)\RSpltBar.pch"


!ELSEIF  "$(CFG)" == "RSpltBar - Win32 Debug"

DEP_CPP_RSPLT=\
	".\RSpltBar.h"\
	{$(INCLUDE)}"Dosdefs.h"\
	{$(INCLUDE)}"Rdialog.h"\
	{$(INCLUDE)}"Rsheets.h"\
	{$(INCLUDE)}"Sheetdef.h"\
	{$(INCLUDE)}"Stdafx.h"\
	

"$(INTDIR)\RSpltBar.obj"	"$(INTDIR)\RSpltBar.sbr" : $(SOURCE) $(DEP_CPP_RSPLT)\
 "$(INTDIR)"


!ELSEIF  "$(CFG)" == "RSpltBar - Win32 Unicode Debug"

DEP_CPP_RSPLT=\
	".\RSpltBar.h"\
	{$(INCLUDE)}"Dosdefs.h"\
	{$(INCLUDE)}"Rdialog.h"\
	{$(INCLUDE)}"Rsheets.h"\
	{$(INCLUDE)}"Sheetdef.h"\
	{$(INCLUDE)}"Stdafx.h"\
	

"$(INTDIR)\RSpltBar.obj" : $(SOURCE) $(DEP_CPP_RSPLT) "$(INTDIR)"\
 "$(INTDIR)\RSpltBar.pch"


!ELSEIF  "$(CFG)" == "RSpltBar - Win32 Unicode Release"

DEP_CPP_RSPLT=\
	".\RSpltBar.h"\
	{$(INCLUDE)}"Dosdefs.h"\
	{$(INCLUDE)}"Rdialog.h"\
	{$(INCLUDE)}"Rsheets.h"\
	{$(INCLUDE)}"Sheetdef.h"\
	{$(INCLUDE)}"Stdafx.h"\
	

"$(INTDIR)\RSpltBar.obj" : $(SOURCE) $(DEP_CPP_RSPLT) "$(INTDIR)"\
 "$(INTDIR)\RSpltBar.pch"


!ENDIF 

SOURCE=.\rspltbC.CPP

!IF  "$(CFG)" == "RSpltBar - Win32 Release"

DEP_CPP_RSPLTB=\
	".\RSpltBar.h"\
	".\rspltbC.H"\
	".\rspltbP.H"\
	{$(INCLUDE)}"Dosdefs.h"\
	{$(INCLUDE)}"Rdialog.h"\
	{$(INCLUDE)}"Rsheets.h"\
	{$(INCLUDE)}"Sheetdef.h"\
	{$(INCLUDE)}"Stdafx.h"\
	

"$(INTDIR)\rspltbC.obj" : $(SOURCE) $(DEP_CPP_RSPLTB) "$(INTDIR)"\
 "$(INTDIR)\RSpltBar.pch"


!ELSEIF  "$(CFG)" == "RSpltBar - Win32 Debug"

DEP_CPP_RSPLTB=\
	".\RSpltBar.h"\
	".\rspltbC.H"\
	".\rspltbP.H"\
	{$(INCLUDE)}"Dosdefs.h"\
	{$(INCLUDE)}"Rdialog.h"\
	{$(INCLUDE)}"Rsheets.h"\
	{$(INCLUDE)}"Sheetdef.h"\
	{$(INCLUDE)}"Stdafx.h"\
	

"$(INTDIR)\rspltbC.obj"	"$(INTDIR)\rspltbC.sbr" : $(SOURCE) $(DEP_CPP_RSPLTB)\
 "$(INTDIR)"


!ELSEIF  "$(CFG)" == "RSpltBar - Win32 Unicode Debug"

DEP_CPP_RSPLTB=\
	".\RSpltBar.h"\
	".\rspltbC.H"\
	".\rspltbP.H"\
	{$(INCLUDE)}"Dosdefs.h"\
	{$(INCLUDE)}"Rdialog.h"\
	{$(INCLUDE)}"Rsheets.h"\
	{$(INCLUDE)}"Sheetdef.h"\
	{$(INCLUDE)}"Stdafx.h"\
	

"$(INTDIR)\rspltbC.obj" : $(SOURCE) $(DEP_CPP_RSPLTB) "$(INTDIR)"\
 "$(INTDIR)\RSpltBar.pch"


!ELSEIF  "$(CFG)" == "RSpltBar - Win32 Unicode Release"

DEP_CPP_RSPLTB=\
	".\RSpltBar.h"\
	".\rspltbC.H"\
	".\rspltbP.H"\
	{$(INCLUDE)}"Dosdefs.h"\
	{$(INCLUDE)}"Rdialog.h"\
	{$(INCLUDE)}"Rsheets.h"\
	{$(INCLUDE)}"Sheetdef.h"\
	{$(INCLUDE)}"Stdafx.h"\
	

"$(INTDIR)\rspltbC.obj" : $(SOURCE) $(DEP_CPP_RSPLTB) "$(INTDIR)"\
 "$(INTDIR)\RSpltBar.pch"


!ENDIF 

SOURCE=.\rspltbP.CPP

!IF  "$(CFG)" == "RSpltBar - Win32 Release"

DEP_CPP_RSPLTBP=\
	".\RSpltBar.h"\
	".\rspltbP.H"\
	{$(INCLUDE)}"Dosdefs.h"\
	{$(INCLUDE)}"Rdialog.h"\
	{$(INCLUDE)}"Rsheets.h"\
	{$(INCLUDE)}"Sheetdef.h"\
	{$(INCLUDE)}"Stdafx.h"\
	

"$(INTDIR)\rspltbP.obj" : $(SOURCE) $(DEP_CPP_RSPLTBP) "$(INTDIR)"\
 "$(INTDIR)\RSpltBar.pch"


!ELSEIF  "$(CFG)" == "RSpltBar - Win32 Debug"

DEP_CPP_RSPLTBP=\
	".\RSpltBar.h"\
	".\rspltbP.H"\
	{$(INCLUDE)}"Dosdefs.h"\
	{$(INCLUDE)}"Rdialog.h"\
	{$(INCLUDE)}"Rsheets.h"\
	{$(INCLUDE)}"Sheetdef.h"\
	{$(INCLUDE)}"Stdafx.h"\
	

"$(INTDIR)\rspltbP.obj"	"$(INTDIR)\rspltbP.sbr" : $(SOURCE) $(DEP_CPP_RSPLTBP)\
 "$(INTDIR)"


!ELSEIF  "$(CFG)" == "RSpltBar - Win32 Unicode Debug"

DEP_CPP_RSPLTBP=\
	".\RSpltBar.h"\
	".\rspltbP.H"\
	{$(INCLUDE)}"Dosdefs.h"\
	{$(INCLUDE)}"Rdialog.h"\
	{$(INCLUDE)}"Rsheets.h"\
	{$(INCLUDE)}"Sheetdef.h"\
	{$(INCLUDE)}"Stdafx.h"\
	

"$(INTDIR)\rspltbP.obj" : $(SOURCE) $(DEP_CPP_RSPLTBP) "$(INTDIR)"\
 "$(INTDIR)\RSpltBar.pch"


!ELSEIF  "$(CFG)" == "RSpltBar - Win32 Unicode Release"

DEP_CPP_RSPLTBP=\
	".\RSpltBar.h"\
	".\rspltbP.H"\
	{$(INCLUDE)}"Dosdefs.h"\
	{$(INCLUDE)}"Rdialog.h"\
	{$(INCLUDE)}"Rsheets.h"\
	{$(INCLUDE)}"Sheetdef.h"\
	{$(INCLUDE)}"Stdafx.h"\
	

"$(INTDIR)\rspltbP.obj" : $(SOURCE) $(DEP_CPP_RSPLTBP) "$(INTDIR)"\
 "$(INTDIR)\RSpltBar.pch"


!ENDIF 

SOURCE=.\RSpltBar.odl

!IF  "$(CFG)" == "RSpltBar - Win32 Release"

MTL_SWITCHES=/nologo /D "NDEBUG" /tlb "$(OUTDIR)\RSpltBar.tlb" /mktyplib203 /o\
 NUL /win32 

"$(OUTDIR)\RSpltBar.tlb" : $(SOURCE) "$(OUTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RSpltBar - Win32 Debug"

MTL_SWITCHES=/nologo /D "_DEBUG" /tlb "$(OUTDIR)\RSpltBar.tlb" /mktyplib203 /o\
 NUL /win32 

"$(OUTDIR)\RSpltBar.tlb" : $(SOURCE) "$(OUTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RSpltBar - Win32 Unicode Debug"

MTL_SWITCHES=/nologo /D "_DEBUG" /tlb "$(OUTDIR)\RSpltBar.tlb" /mktyplib203 /o\
 NUL /win32 

"$(OUTDIR)\RSpltBar.tlb" : $(SOURCE) "$(OUTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RSpltBar - Win32 Unicode Release"

MTL_SWITCHES=/nologo /D "NDEBUG" /tlb "$(OUTDIR)\RSpltBar.tlb" /mktyplib203 /o\
 NUL /win32 

"$(OUTDIR)\RSpltBar.tlb" : $(SOURCE) "$(OUTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\RSpltBar.rc

!IF  "$(CFG)" == "RSpltBar - Win32 Release"

DEP_RSC_RSPLTBA=\
	".\RSpltBc.bmp"\
	
NODEP_RSC_RSPLTBA=\
	"..\..\Release\exe\RSpltBar.tlb"\
	

"$(INTDIR)\RSpltBar.res" : $(SOURCE) $(DEP_RSC_RSPLTBA) "$(INTDIR)"\
 "..\..\Release\exe\RSpltBar.tlb"
	$(RSC) /l 0x809 /fo"$(INTDIR)\RSpltBar.res" /i "\mig\Release\exe" /d "NDEBUG"\
 /d "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "RSpltBar - Win32 Debug"

DEP_RSC_RSPLTBA=\
	"..\..\debug\exe\RSpltBar.tlb"\
	".\RSpltBc.bmp"\
	

"$(INTDIR)\RSpltBar.res" : $(SOURCE) $(DEP_RSC_RSPLTBA) "$(INTDIR)"\
 "..\..\debug\exe\RSpltBar.tlb"
	$(RSC) /l 0x809 /fo"$(INTDIR)\RSpltBar.res" /i "\mig\debug\exe" /d "_DEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "RSpltBar - Win32 Unicode Debug"

DEP_RSC_RSPLTBA=\
	".\RSpltBc.bmp"\
	
NODEP_RSC_RSPLTBA=\
	".\DebugU\RSpltBar.tlb"\
	

"$(INTDIR)\RSpltBar.res" : $(SOURCE) $(DEP_RSC_RSPLTBA) "$(INTDIR)"\
 "$(INTDIR)\RSpltBar.tlb"
	$(RSC) /l 0x809 /fo"$(INTDIR)\RSpltBar.res" /i "DebugU" /d "_DEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "RSpltBar - Win32 Unicode Release"

DEP_RSC_RSPLTBA=\
	".\RSpltBc.bmp"\
	
NODEP_RSC_RSPLTBA=\
	".\ReleaseU\RSpltBar.tlb"\
	

"$(INTDIR)\RSpltBar.res" : $(SOURCE) $(DEP_RSC_RSPLTBA) "$(INTDIR)"\
 "$(INTDIR)\RSpltBar.tlb"
	$(RSC) /l 0x809 /fo"$(INTDIR)\RSpltBar.res" /i "ReleaseU" /d "NDEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ENDIF 

SOURCE=.\RSpltBar.lic

!IF  "$(CFG)" == "RSpltBar - Win32 Release"

OutDir=\mig\Release\exe
ProjDir=.
TargetName=RSpltBar
InputPath=.\RSpltBar.lic

"$(OutDir)\$(TargetName).lic"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy $(ProjDir)\$(TargetName).lic $(OutDir)

!ELSEIF  "$(CFG)" == "RSpltBar - Win32 Debug"

OutDir=\mig\debug\exe
ProjDir=.
TargetName=RSpltBar
InputPath=.\RSpltBar.lic

"$(OutDir)\$(TargetName).lic"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy $(ProjDir)\$(TargetName).lic $(OutDir)

!ELSEIF  "$(CFG)" == "RSpltBar - Win32 Unicode Debug"

OutDir=.\DebugU
ProjDir=.
TargetName=RSpltBar
InputPath=.\RSpltBar.lic

"$(OutDir)\$(TargetName).lic"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(ProjDir)\$(TargetName).lic" "$(OutDir)"

!ELSEIF  "$(CFG)" == "RSpltBar - Win32 Unicode Release"

OutDir=.\ReleaseU
ProjDir=.
TargetName=RSpltBar
InputPath=.\RSpltBar.lic

"$(OutDir)\$(TargetName).lic"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy $(ProjDir)\$(TargetName).lic $(OutDir)

!ENDIF 


!ENDIF 

