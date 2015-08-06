# Microsoft Developer Studio Project File - Name="RCombo" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=RCombo - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "RCombo.mak".
!MESSAGE 
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

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "RCombo - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Ext "ocx"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "\mig\Release\exe"
# PROP Intermediate_Dir "\mig\Release\combo"
# PROP Target_Ext "ocx"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "\mig\src\h" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD BASE RSC /l 0x809 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x809 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386
# Begin Custom Build - Registering ActiveX Control...
OutDir=\mig\Release\exe
TargetPath=\mig\Release\exe\RCombo.ocx
InputPath=\mig\Release\exe\RCombo.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "RCombo - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Ext "ocx"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "\mig\Debug\exe"
# PROP Intermediate_Dir "\mig\Debug\rcombo"
# PROP Target_Ext "ocx"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I "\mig\src\h" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD BASE RSC /l 0x809 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x809 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /dll /pdb:none /debug /machine:I386
# Begin Custom Build - Registering ActiveX Control...
OutDir=\mig\Debug\exe
TargetPath=\mig\Debug\exe\RCombo.ocx
InputPath=\mig\Debug\exe\RCombo.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "RCombo - Win32 Unicode Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DebugU"
# PROP BASE Intermediate_Dir "DebugU"
# PROP BASE Target_Ext "ocx"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugU"
# PROP Intermediate_Dir "DebugU"
# PROP Target_Ext "ocx"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD BASE RSC /l 0x809 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x809 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\DebugU
TargetPath=.\DebugU\RCombo.ocx
InputPath=.\DebugU\RCombo.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "RCombo - Win32 Unicode Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseU"
# PROP BASE Intermediate_Dir "ReleaseU"
# PROP BASE Target_Ext "ocx"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseU"
# PROP Intermediate_Dir "ReleaseU"
# PROP Target_Ext "ocx"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD BASE RSC /l 0x809 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x809 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\ReleaseU
TargetPath=.\ReleaseU\RCombo.ocx
InputPath=.\ReleaseU\RCombo.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "RCombo - Win32 Release"
# Name "RCombo - Win32 Debug"
# Name "RCombo - Win32 Unicode Debug"
# Name "RCombo - Win32 Unicode Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\all.cpp
# End Source File
# Begin Source File

SOURCE=..\Mfc\Getshadw.cpp

!IF  "$(CFG)" == "RCombo - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "RCombo - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "RCombo - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "RCombo - Win32 Unicode Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ListBx.cpp

!IF  "$(CFG)" == "RCombo - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "RCombo - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "RCombo - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "RCombo - Win32 Unicode Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\RCombo.cpp

!IF  "$(CFG)" == "RCombo - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "RCombo - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "RCombo - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "RCombo - Win32 Unicode Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\RCombo.def
# End Source File
# Begin Source File

SOURCE=.\RCombo.odl
# End Source File
# Begin Source File

SOURCE=.\RCombo.rc

!IF  "$(CFG)" == "RCombo - Win32 Release"

!ELSEIF  "$(CFG)" == "RCombo - Win32 Debug"

!ELSEIF  "$(CFG)" == "RCombo - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "RCombo - Win32 Unicode Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\RComboC.cpp

!IF  "$(CFG)" == "RCombo - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "RCombo - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "RCombo - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "RCombo - Win32 Unicode Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\RComboP.cpp

!IF  "$(CFG)" == "RCombo - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "RCombo - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "RCombo - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "RCombo - Win32 Unicode Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\rlistbox.cpp

!IF  "$(CFG)" == "RCombo - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "RCombo - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "RCombo - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "RCombo - Win32 Unicode Release"

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Afxauto.h
# End Source File
# Begin Source File

SOURCE=.\ListBx.h
# End Source File
# Begin Source File

SOURCE=.\RCombo.h
# End Source File
# Begin Source File

SOURCE=.\RComboC.h
# End Source File
# Begin Source File

SOURCE=.\RComboP.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\rlistbox.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\Escort2.bmp
# End Source File
# Begin Source File

SOURCE=.\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\rcombobu.bmp
# End Source File
# Begin Source File

SOURCE=.\rcombobu.ico
# End Source File
# Begin Source File

SOURCE=.\RComboC.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\RCombo.lic

!IF  "$(CFG)" == "RCombo - Win32 Release"

# Begin Custom Build - Copying license file...
OutDir=\mig\Release\exe
ProjDir=.
TargetName=RCombo
InputPath=.\RCombo.lic

"$(OutDir)\$(TargetName).lic" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(ProjDir)\$(TargetName).lic" "$(OutDir)"

# End Custom Build

!ELSEIF  "$(CFG)" == "RCombo - Win32 Debug"

# Begin Custom Build - Copying license file...
OutDir=\mig\Debug\exe
ProjDir=.
TargetName=RCombo
InputPath=.\RCombo.lic

"$(OutDir)\$(TargetName).lic" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(ProjDir)\$(TargetName).lic" "$(OutDir)"

# End Custom Build

!ELSEIF  "$(CFG)" == "RCombo - Win32 Unicode Debug"

# Begin Custom Build - Copying license file...
OutDir=.\DebugU
ProjDir=.
TargetName=RCombo
InputPath=.\RCombo.lic

"$(OutDir)\$(TargetName).lic" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(ProjDir)\$(TargetName).lic" "$(OutDir)"

# End Custom Build

!ELSEIF  "$(CFG)" == "RCombo - Win32 Unicode Release"

# Begin Custom Build - Copying license file...
OutDir=.\ReleaseU
ProjDir=.
TargetName=RCombo
InputPath=.\RCombo.lic

"$(OutDir)\$(TargetName).lic" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(ProjDir)\$(TargetName).lic" "$(OutDir)"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
# Section RCombo : {737CB0C7-B42B-11D1-A1F0-444553540000}
# 	2:5:Class:CRCombo
# 	2:10:HeaderFile:rcombo1.h
# 	2:8:ImplFile:rcombo1.cpp
# End Section
# Section RCombo : {48814009-65AE-11D1-A1F0-444553540000}
# 	2:21:DefaultSinkHeaderFile:rlistbox.h
# 	2:16:DefaultSinkClass:CRListBox
# End Section
# Section RCombo : {90B5EDA6-666F-11D1-A1F0-444553540000}
# 	2:5:Class:CRListBox
# 	2:10:HeaderFile:rlistbox.h
# 	2:8:ImplFile:rlistbox.cpp
# End Section
# Section RCombo : {737CB0C9-B42B-11D1-A1F0-444553540000}
# 	2:21:DefaultSinkHeaderFile:rcombo1.h
# 	2:16:DefaultSinkClass:CRCombo
# End Section
