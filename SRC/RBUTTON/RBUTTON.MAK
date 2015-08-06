# Microsoft Developer Studio Generated NMAKE File, Based on Rbutton.dsp
!IF "$(CFG)" == ""
CFG=RButton - Win32 Debug
!MESSAGE No configuration specified. Defaulting to RButton - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "RButton - Win32 Release" && "$(CFG)" !=\
 "RButton - Win32 Debug" && "$(CFG)" != "RButton - Win32 Unicode Debug" &&\
 "$(CFG)" != "RButton - Win32 Unicode Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Rbutton.mak" CFG="RButton - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "RButton - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "RButton - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "RButton - Win32 Unicode Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "RButton - Win32 Unicode Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "RButton - Win32 Release"

OUTDIR=\mig\Release\exe
INTDIR=\mig\Release\axobj
# Begin Custom Macros
OutDir=\mig\Release\exe
TargetName=Rbutton
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OutDir)\$(TargetName).lic" "$(OUTDIR)\Rbutton.ocx"\
 "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OutDir)\$(TargetName).lic" "$(OUTDIR)\Rbutton.ocx"\
 "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\RButton.obj"
	-@erase "$(INTDIR)\RButton.res"
	-@erase "$(INTDIR)\rbuttonc.obj"
	-@erase "$(INTDIR)\rbuttonp.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\Rbutton.exp"
	-@erase "$(OUTDIR)\Rbutton.lib"
	-@erase "$(OUTDIR)\Rbutton.ocx"
	-@erase "..\..\Release\exe\RButton.tlb"
	-@erase "$(OutDir)\$(TargetName).lic"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /Fp"$(INTDIR)\Rbutton.pch" /Yu"stdafx.h"\
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
RSC_PROJ=/l 0x809 /fo"$(INTDIR)\RButton.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Rbutton.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\Rbutton.pdb" /machine:I386 /def:".\RButton.def"\
 /out:"$(OUTDIR)\Rbutton.ocx" /implib:"$(OUTDIR)\Rbutton.lib" 
DEF_FILE= \
	".\RButton.def"
LINK32_OBJS= \
	"$(INTDIR)\RButton.obj" \
	"$(INTDIR)\RButton.res" \
	"$(INTDIR)\rbuttonc.obj" \
	"$(INTDIR)\rbuttonp.obj"

"$(OUTDIR)\Rbutton.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=\mig\Release\exe
TargetPath=\mig\Release\exe\Rbutton.ocx
InputPath=\mig\Release\exe\Rbutton.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ELSEIF  "$(CFG)" == "RButton - Win32 Debug"

OUTDIR=\mig\Debug\exe
INTDIR=\mig\Debug\axobj
# Begin Custom Macros
OutDir=\mig\Debug\exe
TargetName=Rbutton
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OutDir)\$(TargetName).lic" "$(OUTDIR)\Rbutton.ocx"\
 "$(OUTDIR)\Rbutton.bsc" "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OutDir)\$(TargetName).lic" "$(OUTDIR)\Rbutton.ocx"\
 "$(OUTDIR)\Rbutton.bsc" "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\RButton.obj"
	-@erase "$(INTDIR)\RButton.res"
	-@erase "$(INTDIR)\RButton.sbr"
	-@erase "$(INTDIR)\rbuttonc.obj"
	-@erase "$(INTDIR)\rbuttonc.sbr"
	-@erase "$(INTDIR)\rbuttonp.obj"
	-@erase "$(INTDIR)\rbuttonp.sbr"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\Rbutton.bsc"
	-@erase "$(OUTDIR)\Rbutton.exp"
	-@erase "$(OUTDIR)\Rbutton.ilk"
	-@erase "$(OUTDIR)\Rbutton.lib"
	-@erase "$(OUTDIR)\Rbutton.ocx"
	-@erase "$(OUTDIR)\Rbutton.pdb"
	-@erase "..\..\Debug\exe\RButton.tlb"
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
RSC_PROJ=/l 0x809 /fo"$(INTDIR)\RButton.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Rbutton.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\RButton.sbr" \
	"$(INTDIR)\rbuttonc.sbr" \
	"$(INTDIR)\rbuttonp.sbr"

"$(OUTDIR)\Rbutton.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)\Rbutton.pdb" /debug /machine:I386 /def:".\RButton.def"\
 /out:"$(OUTDIR)\Rbutton.ocx" /implib:"$(OUTDIR)\Rbutton.lib" /pdbtype:sept 
DEF_FILE= \
	".\RButton.def"
LINK32_OBJS= \
	"$(INTDIR)\RButton.obj" \
	"$(INTDIR)\RButton.res" \
	"$(INTDIR)\rbuttonc.obj" \
	"$(INTDIR)\rbuttonp.obj"

"$(OUTDIR)\Rbutton.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=\mig\Debug\exe
TargetPath=\mig\Debug\exe\Rbutton.ocx
InputPath=\mig\Debug\exe\Rbutton.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > $(OutDir)\regsvr32.trg 
	

!ELSEIF  "$(CFG)" == "RButton - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
TargetName=Rbutton
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OutDir)\$(TargetName).lic" "$(OUTDIR)\Rbutton.ocx"\
 "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OutDir)\$(TargetName).lic" "$(OUTDIR)\Rbutton.ocx"\
 "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\RButton.obj"
	-@erase "$(INTDIR)\RButton.res"
	-@erase "$(INTDIR)\RButton.tlb"
	-@erase "$(INTDIR)\rbuttonc.obj"
	-@erase "$(INTDIR)\rbuttonp.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\Rbutton.exp"
	-@erase "$(OUTDIR)\Rbutton.ilk"
	-@erase "$(OUTDIR)\Rbutton.lib"
	-@erase "$(OUTDIR)\Rbutton.ocx"
	-@erase "$(OUTDIR)\Rbutton.pdb"
	-@erase "$(OutDir)\$(TargetName).lic"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\Rbutton.pch"\
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
RSC_PROJ=/l 0x809 /fo"$(INTDIR)\RButton.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Rbutton.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)\Rbutton.pdb" /debug /machine:I386 /def:".\RButton.def"\
 /out:"$(OUTDIR)\Rbutton.ocx" /implib:"$(OUTDIR)\Rbutton.lib" /pdbtype:sept 
DEF_FILE= \
	".\RButton.def"
LINK32_OBJS= \
	"$(INTDIR)\RButton.obj" \
	"$(INTDIR)\RButton.res" \
	"$(INTDIR)\rbuttonc.obj" \
	"$(INTDIR)\rbuttonp.obj"

"$(OUTDIR)\Rbutton.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\DebugU
TargetPath=.\DebugU\Rbutton.ocx
InputPath=.\DebugU\Rbutton.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ELSEIF  "$(CFG)" == "RButton - Win32 Unicode Release"

OUTDIR=.\ReleaseU
INTDIR=.\ReleaseU
# Begin Custom Macros
OutDir=.\ReleaseU
TargetName=Rbutton
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OutDir)\$(TargetName).lic" "$(OUTDIR)\Rbutton.ocx"\
 "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OutDir)\$(TargetName).lic" "$(OUTDIR)\Rbutton.ocx"\
 "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\RButton.obj"
	-@erase "$(INTDIR)\RButton.res"
	-@erase "$(INTDIR)\RButton.tlb"
	-@erase "$(INTDIR)\rbuttonc.obj"
	-@erase "$(INTDIR)\rbuttonp.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\Rbutton.exp"
	-@erase "$(OUTDIR)\Rbutton.lib"
	-@erase "$(OUTDIR)\Rbutton.ocx"
	-@erase "$(OutDir)\$(TargetName).lic"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\Rbutton.pch"\
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
RSC_PROJ=/l 0x809 /fo"$(INTDIR)\RButton.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Rbutton.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\Rbutton.pdb" /machine:I386 /def:".\RButton.def"\
 /out:"$(OUTDIR)\Rbutton.ocx" /implib:"$(OUTDIR)\Rbutton.lib" 
DEF_FILE= \
	".\RButton.def"
LINK32_OBJS= \
	"$(INTDIR)\RButton.obj" \
	"$(INTDIR)\RButton.res" \
	"$(INTDIR)\rbuttonc.obj" \
	"$(INTDIR)\rbuttonp.obj"

"$(OUTDIR)\Rbutton.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseU
TargetPath=.\ReleaseU\Rbutton.ocx
InputPath=.\ReleaseU\Rbutton.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ENDIF 


!IF "$(CFG)" == "RButton - Win32 Release" || "$(CFG)" ==\
 "RButton - Win32 Debug" || "$(CFG)" == "RButton - Win32 Unicode Debug" ||\
 "$(CFG)" == "RButton - Win32 Unicode Release"
SOURCE=.\RButton.cpp

!IF  "$(CFG)" == "RButton - Win32 Release"

DEP_CPP_RBUTT=\
	".\RButton.h"\
	{$(INCLUDE)}"Dosdefs.h"\
	{$(INCLUDE)}"Rdialog.h"\
	{$(INCLUDE)}"Rsheets.h"\
	{$(INCLUDE)}"Sheetdef.h"\
	{$(INCLUDE)}"Stdafx.h"\
	

"$(INTDIR)\RButton.obj" : $(SOURCE) $(DEP_CPP_RBUTT) "$(INTDIR)"\
 "$(INTDIR)\Rbutton.pch"


!ELSEIF  "$(CFG)" == "RButton - Win32 Debug"

DEP_CPP_RBUTT=\
	".\RButton.h"\
	{$(INCLUDE)}"Dosdefs.h"\
	{$(INCLUDE)}"Rdialog.h"\
	{$(INCLUDE)}"Rsheets.h"\
	{$(INCLUDE)}"Sheetdef.h"\
	{$(INCLUDE)}"Stdafx.h"\
	

"$(INTDIR)\RButton.obj"	"$(INTDIR)\RButton.sbr" : $(SOURCE) $(DEP_CPP_RBUTT)\
 "$(INTDIR)"


!ELSEIF  "$(CFG)" == "RButton - Win32 Unicode Debug"

DEP_CPP_RBUTT=\
	".\RButton.h"\
	{$(INCLUDE)}"Dosdefs.h"\
	{$(INCLUDE)}"Rdialog.h"\
	{$(INCLUDE)}"Rsheets.h"\
	{$(INCLUDE)}"Sheetdef.h"\
	{$(INCLUDE)}"Stdafx.h"\
	

"$(INTDIR)\RButton.obj" : $(SOURCE) $(DEP_CPP_RBUTT) "$(INTDIR)"\
 "$(INTDIR)\Rbutton.pch"


!ELSEIF  "$(CFG)" == "RButton - Win32 Unicode Release"

DEP_CPP_RBUTT=\
	".\RButton.h"\
	{$(INCLUDE)}"Dosdefs.h"\
	{$(INCLUDE)}"Rdialog.h"\
	{$(INCLUDE)}"Rsheets.h"\
	{$(INCLUDE)}"Sheetdef.h"\
	{$(INCLUDE)}"Stdafx.h"\
	

"$(INTDIR)\RButton.obj" : $(SOURCE) $(DEP_CPP_RBUTT) "$(INTDIR)"\
 "$(INTDIR)\Rbutton.pch"


!ENDIF 

SOURCE=.\RButton.odl

!IF  "$(CFG)" == "RButton - Win32 Release"

MTL_SWITCHES=/nologo /D "NDEBUG" /tlb "$(OUTDIR)\RButton.tlb" /mktyplib203 /o\
 NUL /win32 

"$(OUTDIR)\RButton.tlb" : $(SOURCE) "$(OUTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RButton - Win32 Debug"

MTL_SWITCHES=/nologo /D "_DEBUG" /tlb "$(OUTDIR)\RButton.tlb" /mktyplib203 /o\
 NUL /win32 

"$(OUTDIR)\RButton.tlb" : $(SOURCE) "$(OUTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RButton - Win32 Unicode Debug"

MTL_SWITCHES=/nologo /D "_DEBUG" /tlb "$(OUTDIR)\RButton.tlb" /mktyplib203 /o\
 NUL /win32 

"$(OUTDIR)\RButton.tlb" : $(SOURCE) "$(OUTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RButton - Win32 Unicode Release"

MTL_SWITCHES=/nologo /D "NDEBUG" /tlb "$(OUTDIR)\RButton.tlb" /mktyplib203 /o\
 NUL /win32 

"$(OUTDIR)\RButton.tlb" : $(SOURCE) "$(OUTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\RButton.rc

!IF  "$(CFG)" == "RButton - Win32 Release"

DEP_RSC_RBUTTO=\
	".\Rbuttonc.bmp"\
	
NODEP_RSC_RBUTTO=\
	"..\..\Release\exe\RButton.tlb"\
	

"$(INTDIR)\RButton.res" : $(SOURCE) $(DEP_RSC_RBUTTO) "$(INTDIR)"\
 "..\..\Release\exe\RButton.tlb"
	$(RSC) /l 0x809 /fo"$(INTDIR)\RButton.res" /i "\mig\Release\exe" /d "NDEBUG"\
 /d "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "RButton - Win32 Debug"

DEP_RSC_RBUTTO=\
	"..\..\Debug\exe\RButton.tlb"\
	".\Rbuttonc.bmp"\
	

"$(INTDIR)\RButton.res" : $(SOURCE) $(DEP_RSC_RBUTTO) "$(INTDIR)"\
 "..\..\Debug\exe\RButton.tlb"
	$(RSC) /l 0x809 /fo"$(INTDIR)\RButton.res" /i "\mig\Debug\exe" /d "_DEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "RButton - Win32 Unicode Debug"

DEP_RSC_RBUTTO=\
	".\Rbuttonc.bmp"\
	
NODEP_RSC_RBUTTO=\
	".\DebugU\RButton.tlb"\
	

"$(INTDIR)\RButton.res" : $(SOURCE) $(DEP_RSC_RBUTTO) "$(INTDIR)"\
 "$(INTDIR)\RButton.tlb"
	$(RSC) /l 0x809 /fo"$(INTDIR)\RButton.res" /i "DebugU" /d "_DEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "RButton - Win32 Unicode Release"

DEP_RSC_RBUTTO=\
	".\Rbuttonc.bmp"\
	
NODEP_RSC_RBUTTO=\
	".\ReleaseU\RButton.tlb"\
	

"$(INTDIR)\RButton.res" : $(SOURCE) $(DEP_RSC_RBUTTO) "$(INTDIR)"\
 "$(INTDIR)\RButton.tlb"
	$(RSC) /l 0x809 /fo"$(INTDIR)\RButton.res" /i "ReleaseU" /d "NDEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ENDIF 

SOURCE=.\rbuttonc.cpp

!IF  "$(CFG)" == "RButton - Win32 Release"

DEP_CPP_RBUTTON=\
	".\RButton.h"\
	".\rbuttonc.h"\
	".\rbuttonp.h"\
	{$(INCLUDE)}"Dosdefs.h"\
	{$(INCLUDE)}"Rdialog.h"\
	{$(INCLUDE)}"Rsheets.h"\
	{$(INCLUDE)}"Sheetdef.h"\
	{$(INCLUDE)}"Stdafx.h"\
	

"$(INTDIR)\rbuttonc.obj" : $(SOURCE) $(DEP_CPP_RBUTTON) "$(INTDIR)"\
 "$(INTDIR)\Rbutton.pch"


!ELSEIF  "$(CFG)" == "RButton - Win32 Debug"

DEP_CPP_RBUTTON=\
	".\RButton.h"\
	".\rbuttonc.h"\
	".\rbuttonp.h"\
	{$(INCLUDE)}"Dosdefs.h"\
	{$(INCLUDE)}"Rdialog.h"\
	{$(INCLUDE)}"Rsheets.h"\
	{$(INCLUDE)}"Sheetdef.h"\
	{$(INCLUDE)}"Stdafx.h"\
	

"$(INTDIR)\rbuttonc.obj"	"$(INTDIR)\rbuttonc.sbr" : $(SOURCE)\
 $(DEP_CPP_RBUTTON) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "RButton - Win32 Unicode Debug"

DEP_CPP_RBUTTON=\
	".\RButton.h"\
	".\rbuttonc.h"\
	".\rbuttonp.h"\
	{$(INCLUDE)}"Dosdefs.h"\
	{$(INCLUDE)}"Rdialog.h"\
	{$(INCLUDE)}"Rsheets.h"\
	{$(INCLUDE)}"Sheetdef.h"\
	{$(INCLUDE)}"Stdafx.h"\
	

"$(INTDIR)\rbuttonc.obj" : $(SOURCE) $(DEP_CPP_RBUTTON) "$(INTDIR)"\
 "$(INTDIR)\Rbutton.pch"


!ELSEIF  "$(CFG)" == "RButton - Win32 Unicode Release"

DEP_CPP_RBUTTON=\
	".\RButton.h"\
	".\rbuttonc.h"\
	".\rbuttonp.h"\
	{$(INCLUDE)}"Dosdefs.h"\
	{$(INCLUDE)}"Rdialog.h"\
	{$(INCLUDE)}"Rsheets.h"\
	{$(INCLUDE)}"Sheetdef.h"\
	{$(INCLUDE)}"Stdafx.h"\
	

"$(INTDIR)\rbuttonc.obj" : $(SOURCE) $(DEP_CPP_RBUTTON) "$(INTDIR)"\
 "$(INTDIR)\Rbutton.pch"


!ENDIF 

SOURCE=.\rbuttonp.cpp

!IF  "$(CFG)" == "RButton - Win32 Release"

DEP_CPP_RBUTTONP=\
	".\RButton.h"\
	".\rbuttonp.h"\
	{$(INCLUDE)}"Dosdefs.h"\
	{$(INCLUDE)}"Rdialog.h"\
	{$(INCLUDE)}"Rsheets.h"\
	{$(INCLUDE)}"Sheetdef.h"\
	{$(INCLUDE)}"Stdafx.h"\
	

"$(INTDIR)\rbuttonp.obj" : $(SOURCE) $(DEP_CPP_RBUTTONP) "$(INTDIR)"\
 "$(INTDIR)\Rbutton.pch"


!ELSEIF  "$(CFG)" == "RButton - Win32 Debug"

DEP_CPP_RBUTTONP=\
	".\RButton.h"\
	".\rbuttonp.h"\
	{$(INCLUDE)}"Dosdefs.h"\
	{$(INCLUDE)}"Rdialog.h"\
	{$(INCLUDE)}"Rsheets.h"\
	{$(INCLUDE)}"Sheetdef.h"\
	{$(INCLUDE)}"Stdafx.h"\
	

"$(INTDIR)\rbuttonp.obj"	"$(INTDIR)\rbuttonp.sbr" : $(SOURCE)\
 $(DEP_CPP_RBUTTONP) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "RButton - Win32 Unicode Debug"

DEP_CPP_RBUTTONP=\
	".\RButton.h"\
	".\rbuttonp.h"\
	{$(INCLUDE)}"Dosdefs.h"\
	{$(INCLUDE)}"Rdialog.h"\
	{$(INCLUDE)}"Rsheets.h"\
	{$(INCLUDE)}"Sheetdef.h"\
	{$(INCLUDE)}"Stdafx.h"\
	

"$(INTDIR)\rbuttonp.obj" : $(SOURCE) $(DEP_CPP_RBUTTONP) "$(INTDIR)"\
 "$(INTDIR)\Rbutton.pch"


!ELSEIF  "$(CFG)" == "RButton - Win32 Unicode Release"

DEP_CPP_RBUTTONP=\
	".\RButton.h"\
	".\rbuttonp.h"\
	{$(INCLUDE)}"Dosdefs.h"\
	{$(INCLUDE)}"Rdialog.h"\
	{$(INCLUDE)}"Rsheets.h"\
	{$(INCLUDE)}"Sheetdef.h"\
	{$(INCLUDE)}"Stdafx.h"\
	

"$(INTDIR)\rbuttonp.obj" : $(SOURCE) $(DEP_CPP_RBUTTONP) "$(INTDIR)"\
 "$(INTDIR)\Rbutton.pch"


!ENDIF 

SOURCE=.\RButton.lic

!IF  "$(CFG)" == "RButton - Win32 Release"

OutDir=\mig\Release\exe
ProjDir=.
TargetName=Rbutton
InputPath=.\RButton.lic

"$(OutDir)\$(TargetName).lic"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(ProjDir)\$(TargetName).lic" "$(OutDir)"

!ELSEIF  "$(CFG)" == "RButton - Win32 Debug"

OutDir=\mig\Debug\exe
ProjDir=.
TargetName=Rbutton
InputPath=.\RButton.lic

"$(OutDir)\$(TargetName).lic"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(ProjDir)\$(TargetName).lic" "$(OutDir)"

!ELSEIF  "$(CFG)" == "RButton - Win32 Unicode Debug"

OutDir=.\DebugU
ProjDir=.
TargetName=Rbutton
InputPath=.\RButton.lic

"$(OutDir)\$(TargetName).lic"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(ProjDir)\$(TargetName).lic" "$(OutDir)"

!ELSEIF  "$(CFG)" == "RButton - Win32 Unicode Release"

OutDir=.\ReleaseU
ProjDir=.
TargetName=Rbutton
InputPath=.\RButton.lic

"$(OutDir)\$(TargetName).lic"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(ProjDir)\$(TargetName).lic" "$(OutDir)"

!ENDIF 


!ENDIF 

