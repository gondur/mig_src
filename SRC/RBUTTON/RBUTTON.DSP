# Microsoft Developer Studio Project File - Name="RButton" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=RButton - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Rbutton.mak".
!MESSAGE 
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

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "RButton - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Ext "ocx"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "\mig\Release\exe"
# PROP Intermediate_Dir "\mig\Release\button"
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
TargetPath=\mig\Release\exe\Rbutton.ocx
InputPath=\mig\Release\exe\Rbutton.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "RButton - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Ext "ocx"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "\mig\Debug\exe"
# PROP Intermediate_Dir "\mig\Debug\rbutton"
# PROP Target_Ext "ocx"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I "\mig\src\h" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /FR /FD /c
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
TargetPath=\mig\Debug\exe\Rbutton.ocx
InputPath=\mig\Debug\exe\Rbutton.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > $(OutDir)\regsvr32.trg 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "RButton - Win32 Unicode Debug"

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
TargetPath=.\DebugU\Rbutton.ocx
InputPath=.\DebugU\Rbutton.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "RButton - Win32 Unicode Release"

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
TargetPath=.\ReleaseU\Rbutton.ocx
InputPath=.\ReleaseU\Rbutton.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "RButton - Win32 Release"
# Name "RButton - Win32 Debug"
# Name "RButton - Win32 Unicode Debug"
# Name "RButton - Win32 Unicode Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\all.cpp
# End Source File
# Begin Source File

SOURCE=.\getfile.cpp

!IF  "$(CFG)" == "RButton - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "RButton - Win32 Debug"

# PROP Exclude_From_Build 1
# ADD CPP /D "NO_AFX_AUTO"

!ELSEIF  "$(CFG)" == "RButton - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "RButton - Win32 Unicode Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Mfc\getresrc.cpp

!IF  "$(CFG)" == "RButton - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "RButton - Win32 Debug"

# PROP Exclude_From_Build 1
# ADD CPP /D "NO_AFX_AUTO"

!ELSEIF  "$(CFG)" == "RButton - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "RButton - Win32 Unicode Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Mfc\Getshadw.cpp

!IF  "$(CFG)" == "RButton - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "RButton - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "RButton - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "RButton - Win32 Unicode Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\RButton.cpp

!IF  "$(CFG)" == "RButton - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "RButton - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "RButton - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "RButton - Win32 Unicode Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\RButton.def
# End Source File
# Begin Source File

SOURCE=.\RButton.odl
# End Source File
# Begin Source File

SOURCE=.\RButton.rc

!IF  "$(CFG)" == "RButton - Win32 Release"

!ELSEIF  "$(CFG)" == "RButton - Win32 Debug"

!ELSEIF  "$(CFG)" == "RButton - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "RButton - Win32 Unicode Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\rbuttonc.cpp

!IF  "$(CFG)" == "RButton - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "RButton - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "RButton - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "RButton - Win32 Unicode Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\rbuttonp.cpp

!IF  "$(CFG)" == "RButton - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "RButton - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "RButton - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "RButton - Win32 Unicode Release"

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\MinFile.h
# End Source File
# Begin Source File

SOURCE=.\RButton.h
# End Source File
# Begin Source File

SOURCE=.\rbuttonc.h
# End Source File
# Begin Source File

SOURCE=.\rbuttonp.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\Res\Bye1.ico
# End Source File
# Begin Source File

SOURCE=.\res\close1.ico
# End Source File
# Begin Source File

SOURCE=.\res\helpdown.ico
# End Source File
# Begin Source File

SOURCE=.\res\helpup.ico
# End Source File
# Begin Source File

SOURCE=.\Rbuttonc.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tick.ico
# End Source File
# Begin Source File

SOURCE=.\Res\Tickup.ico
# End Source File
# End Group
# Begin Source File

SOURCE=.\RButton.lic

!IF  "$(CFG)" == "RButton - Win32 Release"

# Begin Custom Build - Copying license file...
OutDir=\mig\Release\exe
ProjDir=.
TargetName=Rbutton
InputPath=.\RButton.lic

"$(OutDir)\$(TargetName).lic" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(ProjDir)\$(TargetName).lic" "$(OutDir)"

# End Custom Build

!ELSEIF  "$(CFG)" == "RButton - Win32 Debug"

# Begin Custom Build - Copying license file...
OutDir=\mig\Debug\exe
ProjDir=.
TargetName=Rbutton
InputPath=.\RButton.lic

"$(OutDir)\$(TargetName).lic" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(ProjDir)\$(TargetName).lic" "$(OutDir)"

# End Custom Build

!ELSEIF  "$(CFG)" == "RButton - Win32 Unicode Debug"

# Begin Custom Build - Copying license file...
OutDir=.\DebugU
ProjDir=.
TargetName=Rbutton
InputPath=.\RButton.lic

"$(OutDir)\$(TargetName).lic" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(ProjDir)\$(TargetName).lic" "$(OutDir)"

# End Custom Build

!ELSEIF  "$(CFG)" == "RButton - Win32 Unicode Release"

# Begin Custom Build - Copying license file...
OutDir=.\ReleaseU
ProjDir=.
TargetName=Rbutton
InputPath=.\RButton.lic

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
