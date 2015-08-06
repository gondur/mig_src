# Microsoft Developer Studio Generated NMAKE File, Based on RTabs.dsp
!IF "$(CFG)" == ""
CFG=RTabs - Win32 Debug
!MESSAGE No configuration specified. Defaulting to RTabs - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "RTabs - Win32 Release" && "$(CFG)" != "RTabs - Win32 Debug" &&\
 "$(CFG)" != "RTabs - Win32 Unicode Debug" && "$(CFG)" !=\
 "RTabs - Win32 Unicode Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "RTabs.mak" CFG="RTabs - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "RTabs - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "RTabs - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "RTabs - Win32 Unicode Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "RTabs - Win32 Unicode Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "RTabs - Win32 Release"

OUTDIR=\mig\Release\exe
INTDIR=\mig\Release\axobj
# Begin Custom Macros
OutDir=\mig\Release\exe
TargetName=RTabs
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OutDir)\$(TargetName).lic" "$(OUTDIR)\RTabs.ocx"\
 "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OutDir)\$(TargetName).lic" "$(OUTDIR)\RTabs.ocx"\
 "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\RTabs.obj"
	-@erase "$(INTDIR)\RTabs.res"
	-@erase "$(INTDIR)\RTabsCtl.obj"
	-@erase "$(INTDIR)\RTabsPpg.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\RTabs.exp"
	-@erase "$(OUTDIR)\RTabs.lib"
	-@erase "$(OUTDIR)\RTabs.ocx"
	-@erase "..\..\Release\exe\RTabs.tlb"
	-@erase "$(OutDir)\$(TargetName).lic"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /Fp"$(INTDIR)\RTabs.pch" /Yu"stdafx.h"\
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
RSC_PROJ=/l 0x809 /fo"$(INTDIR)\RTabs.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\RTabs.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\RTabs.pdb" /machine:I386 /def:".\RTabs.def"\
 /out:"$(OUTDIR)\RTabs.ocx" /implib:"$(OUTDIR)\RTabs.lib" 
DEF_FILE= \
	".\RTabs.def"
LINK32_OBJS= \
	"$(INTDIR)\RTabs.obj" \
	"$(INTDIR)\RTabs.res" \
	"$(INTDIR)\RTabsCtl.obj" \
	"$(INTDIR)\RTabsPpg.obj"

"$(OUTDIR)\RTabs.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=\mig\Release\exe
TargetPath=\mig\Release\exe\RTabs.ocx
InputPath=\mig\Release\exe\RTabs.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ELSEIF  "$(CFG)" == "RTabs - Win32 Debug"

OUTDIR=\mig\Debug\exe
INTDIR=\mig\Debug\axobj
# Begin Custom Macros
OutDir=\mig\Debug\exe
TargetName=RTabs
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OutDir)\$(TargetName).lic" "$(OUTDIR)\RTabs.ocx"\
 "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OutDir)\$(TargetName).lic" "$(OUTDIR)\RTabs.ocx"\
 "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\RTabs.obj"
	-@erase "$(INTDIR)\RTabs.res"
	-@erase "$(INTDIR)\RTabsCtl.obj"
	-@erase "$(INTDIR)\RTabsPpg.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\RTabs.exp"
	-@erase "$(OUTDIR)\RTabs.ilk"
	-@erase "$(OUTDIR)\RTabs.lib"
	-@erase "$(OUTDIR)\RTabs.ocx"
	-@erase "$(OUTDIR)\RTabs.pdb"
	-@erase "..\..\Debug\exe\RTabs.tlb"
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
RSC_PROJ=/l 0x809 /fo"$(INTDIR)\RTabs.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\RTabs.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)\RTabs.pdb" /debug /machine:I386 /def:".\RTabs.def"\
 /out:"$(OUTDIR)\RTabs.ocx" /implib:"$(OUTDIR)\RTabs.lib" /pdbtype:sept 
DEF_FILE= \
	".\RTabs.def"
LINK32_OBJS= \
	"$(INTDIR)\RTabs.obj" \
	"$(INTDIR)\RTabs.res" \
	"$(INTDIR)\RTabsCtl.obj" \
	"$(INTDIR)\RTabsPpg.obj"

"$(OUTDIR)\RTabs.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=\mig\Debug\exe
TargetPath=\mig\Debug\exe\RTabs.ocx
InputPath=\mig\Debug\exe\RTabs.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > $(OutDir)\regsvr32.trg 
	

!ELSEIF  "$(CFG)" == "RTabs - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
TargetName=RTabs
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OutDir)\$(TargetName).lic" "$(OUTDIR)\RTabs.ocx"\
 "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OutDir)\$(TargetName).lic" "$(OUTDIR)\RTabs.ocx"\
 "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\RTabs.obj"
	-@erase "$(INTDIR)\RTabs.res"
	-@erase "$(INTDIR)\RTabs.tlb"
	-@erase "$(INTDIR)\RTabsCtl.obj"
	-@erase "$(INTDIR)\RTabsPpg.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\RTabs.exp"
	-@erase "$(OUTDIR)\RTabs.ilk"
	-@erase "$(OUTDIR)\RTabs.lib"
	-@erase "$(OUTDIR)\RTabs.ocx"
	-@erase "$(OUTDIR)\RTabs.pdb"
	-@erase "$(OutDir)\$(TargetName).lic"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\RTabs.pch"\
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
RSC_PROJ=/l 0x809 /fo"$(INTDIR)\RTabs.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\RTabs.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)\RTabs.pdb" /debug /machine:I386 /def:".\RTabs.def"\
 /out:"$(OUTDIR)\RTabs.ocx" /implib:"$(OUTDIR)\RTabs.lib" /pdbtype:sept 
DEF_FILE= \
	".\RTabs.def"
LINK32_OBJS= \
	"$(INTDIR)\RTabs.obj" \
	"$(INTDIR)\RTabs.res" \
	"$(INTDIR)\RTabsCtl.obj" \
	"$(INTDIR)\RTabsPpg.obj"

"$(OUTDIR)\RTabs.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\DebugU
TargetPath=.\DebugU\RTabs.ocx
InputPath=.\DebugU\RTabs.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ELSEIF  "$(CFG)" == "RTabs - Win32 Unicode Release"

OUTDIR=.\ReleaseU
INTDIR=.\ReleaseU
# Begin Custom Macros
OutDir=.\ReleaseU
TargetName=RTabs
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OutDir)\$(TargetName).lic" "$(OUTDIR)\RTabs.ocx"\
 "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OutDir)\$(TargetName).lic" "$(OUTDIR)\RTabs.ocx"\
 "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\RTabs.obj"
	-@erase "$(INTDIR)\RTabs.res"
	-@erase "$(INTDIR)\RTabs.tlb"
	-@erase "$(INTDIR)\RTabsCtl.obj"
	-@erase "$(INTDIR)\RTabsPpg.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\RTabs.exp"
	-@erase "$(OUTDIR)\RTabs.lib"
	-@erase "$(OUTDIR)\RTabs.ocx"
	-@erase "$(OutDir)\$(TargetName).lic"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\RTabs.pch"\
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
RSC_PROJ=/l 0x809 /fo"$(INTDIR)\RTabs.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\RTabs.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\RTabs.pdb" /machine:I386 /def:".\RTabs.def"\
 /out:"$(OUTDIR)\RTabs.ocx" /implib:"$(OUTDIR)\RTabs.lib" 
DEF_FILE= \
	".\RTabs.def"
LINK32_OBJS= \
	"$(INTDIR)\RTabs.obj" \
	"$(INTDIR)\RTabs.res" \
	"$(INTDIR)\RTabsCtl.obj" \
	"$(INTDIR)\RTabsPpg.obj"

"$(OUTDIR)\RTabs.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseU
TargetPath=.\ReleaseU\RTabs.ocx
InputPath=.\ReleaseU\RTabs.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ENDIF 


!IF "$(CFG)" == "RTabs - Win32 Release" || "$(CFG)" == "RTabs - Win32 Debug" ||\
 "$(CFG)" == "RTabs - Win32 Unicode Debug" || "$(CFG)" ==\
 "RTabs - Win32 Unicode Release"
SOURCE=.\RTabs.cpp

!IF  "$(CFG)" == "RTabs - Win32 Release"

DEP_CPP_RTABS=\
	".\RTabs.h"\
	{$(INCLUDE)}"Dosdefs.h"\
	{$(INCLUDE)}"Rdialog.h"\
	{$(INCLUDE)}"Rsheets.h"\
	{$(INCLUDE)}"Sheetdef.h"\
	{$(INCLUDE)}"Stdafx.h"\
	
CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /Fp"$(INTDIR)\RTabs.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\RTabs.obj" : $(SOURCE) $(DEP_CPP_RTABS) "$(INTDIR)"\
 "$(INTDIR)\RTabs.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RTabs - Win32 Debug"

DEP_CPP_RTABS=\
	".\RTabs.h"\
	{$(INCLUDE)}"Dosdefs.h"\
	{$(INCLUDE)}"Rdialog.h"\
	{$(INCLUDE)}"Rsheets.h"\
	{$(INCLUDE)}"Sheetdef.h"\
	{$(INCLUDE)}"Stdafx.h"\
	
CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "\mig\src\h" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\RTabs.obj" : $(SOURCE) $(DEP_CPP_RTABS) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RTabs - Win32 Unicode Debug"

DEP_CPP_RTABS=\
	".\RTabs.h"\
	{$(INCLUDE)}"Dosdefs.h"\
	{$(INCLUDE)}"Rdialog.h"\
	{$(INCLUDE)}"Rsheets.h"\
	{$(INCLUDE)}"Sheetdef.h"\
	{$(INCLUDE)}"Stdafx.h"\
	
CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE"\
 /Fp"$(INTDIR)\RTabs.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c\
 

"$(INTDIR)\RTabs.obj" : $(SOURCE) $(DEP_CPP_RTABS) "$(INTDIR)"\
 "$(INTDIR)\RTabs.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RTabs - Win32 Unicode Release"

DEP_CPP_RTABS=\
	".\RTabs.h"\
	{$(INCLUDE)}"Dosdefs.h"\
	{$(INCLUDE)}"Rdialog.h"\
	{$(INCLUDE)}"Rsheets.h"\
	{$(INCLUDE)}"Sheetdef.h"\
	{$(INCLUDE)}"Stdafx.h"\
	
CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\RTabs.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\RTabs.obj" : $(SOURCE) $(DEP_CPP_RTABS) "$(INTDIR)"\
 "$(INTDIR)\RTabs.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\RTabs.odl

!IF  "$(CFG)" == "RTabs - Win32 Release"

MTL_SWITCHES=/nologo /D "NDEBUG" /tlb "$(OUTDIR)\RTabs.tlb" /mktyplib203 /o NUL\
 /win32 

"$(OUTDIR)\RTabs.tlb" : $(SOURCE) "$(OUTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RTabs - Win32 Debug"

MTL_SWITCHES=/nologo /D "_DEBUG" /tlb "$(OUTDIR)\RTabs.tlb" /mktyplib203 /o NUL\
 /win32 

"$(OUTDIR)\RTabs.tlb" : $(SOURCE) "$(OUTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RTabs - Win32 Unicode Debug"

MTL_SWITCHES=/nologo /D "_DEBUG" /tlb "$(OUTDIR)\RTabs.tlb" /mktyplib203 /o NUL\
 /win32 

"$(OUTDIR)\RTabs.tlb" : $(SOURCE) "$(OUTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RTabs - Win32 Unicode Release"

MTL_SWITCHES=/nologo /D "NDEBUG" /tlb "$(OUTDIR)\RTabs.tlb" /mktyplib203 /o NUL\
 /win32 

"$(OUTDIR)\RTabs.tlb" : $(SOURCE) "$(OUTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\RTabs.rc

!IF  "$(CFG)" == "RTabs - Win32 Release"

DEP_RSC_RTABS_=\
	".\ico00001.ico"\
	".\icon1.ico"\
	".\RTabsCtl.bmp"\
	".\Sticker.bmp"\
	".\StickerU.bmp"\
	".\tab1.ico"\
	
NODEP_RSC_RTABS_=\
	"..\..\Release\exe\RTabs.tlb"\
	

"$(INTDIR)\RTabs.res" : $(SOURCE) $(DEP_RSC_RTABS_) "$(INTDIR)"\
 "..\..\Release\exe\RTabs.tlb"
	$(RSC) /l 0x809 /fo"$(INTDIR)\RTabs.res" /i "\mig\Release\exe" /d "NDEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "RTabs - Win32 Debug"

DEP_RSC_RTABS_=\
	"..\..\Debug\exe\RTabs.tlb"\
	".\ico00001.ico"\
	".\icon1.ico"\
	".\RTabsCtl.bmp"\
	".\Sticker.bmp"\
	".\StickerU.bmp"\
	".\tab1.ico"\
	

"$(INTDIR)\RTabs.res" : $(SOURCE) $(DEP_RSC_RTABS_) "$(INTDIR)"\
 "..\..\Debug\exe\RTabs.tlb"
	$(RSC) /l 0x809 /fo"$(INTDIR)\RTabs.res" /i "\mig\Debug\exe" /d "_DEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "RTabs - Win32 Unicode Debug"

DEP_RSC_RTABS_=\
	".\ico00001.ico"\
	".\icon1.ico"\
	".\RTabsCtl.bmp"\
	".\Sticker.bmp"\
	".\StickerU.bmp"\
	".\tab1.ico"\
	
NODEP_RSC_RTABS_=\
	".\DebugU\RTabs.tlb"\
	

"$(INTDIR)\RTabs.res" : $(SOURCE) $(DEP_RSC_RTABS_) "$(INTDIR)"\
 "$(INTDIR)\RTabs.tlb"
	$(RSC) /l 0x809 /fo"$(INTDIR)\RTabs.res" /i "DebugU" /d "_DEBUG" /d "_AFXDLL"\
 $(SOURCE)


!ELSEIF  "$(CFG)" == "RTabs - Win32 Unicode Release"

DEP_RSC_RTABS_=\
	".\ico00001.ico"\
	".\icon1.ico"\
	".\RTabsCtl.bmp"\
	".\Sticker.bmp"\
	".\StickerU.bmp"\
	".\tab1.ico"\
	
NODEP_RSC_RTABS_=\
	".\ReleaseU\RTabs.tlb"\
	

"$(INTDIR)\RTabs.res" : $(SOURCE) $(DEP_RSC_RTABS_) "$(INTDIR)"\
 "$(INTDIR)\RTabs.tlb"
	$(RSC) /l 0x809 /fo"$(INTDIR)\RTabs.res" /i "ReleaseU" /d "NDEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ENDIF 

SOURCE=.\RTabsCtl.cpp

!IF  "$(CFG)" == "RTabs - Win32 Release"

DEP_CPP_RTABSC=\
	".\RTabs.h"\
	".\RTabsCtl.h"\
	".\RTabsPpg.h"\
	{$(INCLUDE)}"Dosdefs.h"\
	{$(INCLUDE)}"Rdialog.h"\
	{$(INCLUDE)}"Rsheets.h"\
	{$(INCLUDE)}"Sheetdef.h"\
	{$(INCLUDE)}"Stdafx.h"\
	
CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /Fp"$(INTDIR)\RTabs.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\RTabsCtl.obj" : $(SOURCE) $(DEP_CPP_RTABSC) "$(INTDIR)"\
 "$(INTDIR)\RTabs.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RTabs - Win32 Debug"

DEP_CPP_RTABSC=\
	".\RTabs.h"\
	".\RTabsCtl.h"\
	".\RTabsPpg.h"\
	{$(INCLUDE)}"Dosdefs.h"\
	{$(INCLUDE)}"Rdialog.h"\
	{$(INCLUDE)}"Rsheets.h"\
	{$(INCLUDE)}"Sheetdef.h"\
	{$(INCLUDE)}"Stdafx.h"\
	
CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "\mig\src\h" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\RTabsCtl.obj" : $(SOURCE) $(DEP_CPP_RTABSC) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RTabs - Win32 Unicode Debug"

DEP_CPP_RTABSC=\
	".\RTabs.h"\
	".\RTabsCtl.h"\
	".\RTabsPpg.h"\
	{$(INCLUDE)}"Dosdefs.h"\
	{$(INCLUDE)}"Rdialog.h"\
	{$(INCLUDE)}"Rsheets.h"\
	{$(INCLUDE)}"Sheetdef.h"\
	{$(INCLUDE)}"Stdafx.h"\
	
CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE"\
 /Fp"$(INTDIR)\RTabs.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c\
 

"$(INTDIR)\RTabsCtl.obj" : $(SOURCE) $(DEP_CPP_RTABSC) "$(INTDIR)"\
 "$(INTDIR)\RTabs.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RTabs - Win32 Unicode Release"

DEP_CPP_RTABSC=\
	".\RTabs.h"\
	".\RTabsCtl.h"\
	".\RTabsPpg.h"\
	{$(INCLUDE)}"Dosdefs.h"\
	{$(INCLUDE)}"Rdialog.h"\
	{$(INCLUDE)}"Rsheets.h"\
	{$(INCLUDE)}"Sheetdef.h"\
	{$(INCLUDE)}"Stdafx.h"\
	
CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\RTabs.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\RTabsCtl.obj" : $(SOURCE) $(DEP_CPP_RTABSC) "$(INTDIR)"\
 "$(INTDIR)\RTabs.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\RTabsPpg.cpp

!IF  "$(CFG)" == "RTabs - Win32 Release"

DEP_CPP_RTABSP=\
	".\RTabs.h"\
	".\RTabsPpg.h"\
	{$(INCLUDE)}"Dosdefs.h"\
	{$(INCLUDE)}"Rdialog.h"\
	{$(INCLUDE)}"Rsheets.h"\
	{$(INCLUDE)}"Sheetdef.h"\
	{$(INCLUDE)}"Stdafx.h"\
	
CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /Fp"$(INTDIR)\RTabs.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\RTabsPpg.obj" : $(SOURCE) $(DEP_CPP_RTABSP) "$(INTDIR)"\
 "$(INTDIR)\RTabs.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RTabs - Win32 Debug"

DEP_CPP_RTABSP=\
	".\RTabs.h"\
	".\RTabsPpg.h"\
	{$(INCLUDE)}"Dosdefs.h"\
	{$(INCLUDE)}"Rdialog.h"\
	{$(INCLUDE)}"Rsheets.h"\
	{$(INCLUDE)}"Sheetdef.h"\
	{$(INCLUDE)}"Stdafx.h"\
	
CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "\mig\src\h" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\RTabsPpg.obj" : $(SOURCE) $(DEP_CPP_RTABSP) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RTabs - Win32 Unicode Debug"

DEP_CPP_RTABSP=\
	".\RTabs.h"\
	".\RTabsPpg.h"\
	{$(INCLUDE)}"Dosdefs.h"\
	{$(INCLUDE)}"Rdialog.h"\
	{$(INCLUDE)}"Rsheets.h"\
	{$(INCLUDE)}"Sheetdef.h"\
	{$(INCLUDE)}"Stdafx.h"\
	
CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE"\
 /Fp"$(INTDIR)\RTabs.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c\
 

"$(INTDIR)\RTabsPpg.obj" : $(SOURCE) $(DEP_CPP_RTABSP) "$(INTDIR)"\
 "$(INTDIR)\RTabs.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RTabs - Win32 Unicode Release"

DEP_CPP_RTABSP=\
	".\RTabs.h"\
	".\RTabsPpg.h"\
	{$(INCLUDE)}"Dosdefs.h"\
	{$(INCLUDE)}"Rdialog.h"\
	{$(INCLUDE)}"Rsheets.h"\
	{$(INCLUDE)}"Sheetdef.h"\
	{$(INCLUDE)}"Stdafx.h"\
	
CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\RTabs.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\RTabsPpg.obj" : $(SOURCE) $(DEP_CPP_RTABSP) "$(INTDIR)"\
 "$(INTDIR)\RTabs.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\RTabs.lic

!IF  "$(CFG)" == "RTabs - Win32 Release"

OutDir=\mig\Release\exe
ProjDir=.
TargetName=RTabs
InputPath=.\RTabs.lic

"$(OutDir)\$(TargetName).lic"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(ProjDir)\$(TargetName).lic" "$(OutDir)"

!ELSEIF  "$(CFG)" == "RTabs - Win32 Debug"

OutDir=\mig\Debug\exe
ProjDir=.
TargetName=RTabs
InputPath=.\RTabs.lic

"$(OutDir)\$(TargetName).lic"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy $(ProjDir)\$(TargetName).lic $(OutDir)

!ELSEIF  "$(CFG)" == "RTabs - Win32 Unicode Debug"

OutDir=.\DebugU
ProjDir=.
TargetName=RTabs
InputPath=.\RTabs.lic

"$(OutDir)\$(TargetName).lic"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(ProjDir)\$(TargetName).lic" "$(OutDir)"

!ELSEIF  "$(CFG)" == "RTabs - Win32 Unicode Release"

OutDir=.\ReleaseU
ProjDir=.
TargetName=RTabs
InputPath=.\RTabs.lic

"$(OutDir)\$(TargetName).lic"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(ProjDir)\$(TargetName).lic" "$(OutDir)"

!ENDIF 


!ENDIF 

