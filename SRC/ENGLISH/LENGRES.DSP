# Microsoft Developer Studio Project File - Name="LEngRes" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=LEngRes - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "lengres.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "lengres.mak" CFG="LEngRes - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "LEngRes - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "LEngRes - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "LEngRes - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\release\english"
# PROP Intermediate_Dir "..\..\Release\english"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x809 /i "..\mfc" /i "..\mfc\res" /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386 /out:"..\..\release\english/miglang.dll" /NOENTRY
# SUBTRACT LINK32 /pdb:none
# Begin Special Build Tool
SOURCE=$(InputPath)
PostBuild_Desc=Copying
PostBuild_Cmds=copy ..\..\release\english\miglang.dll ..\..\game\english\text
# End Special Build Tool

!ELSEIF  "$(CFG)" == "LEngRes - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\debug\english"
# PROP Intermediate_Dir "..\..\debug\english"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD BASE RSC /l 0x809 /d "_DEBUG"
# ADD RSC /l 0x809 /i "..\mfc" /i "..\mfc\res" /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /dll /pdb:none /machine:I386 /out:"..\..\debug\english/miglang.dll" /NOENTRY
# Begin Special Build Tool
SOURCE=$(InputPath)
PostBuild_Desc=Copying resources
PostBuild_Cmds=copy ..\..\debug\english\miglang.dll ..\..\game\english\text
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "LEngRes - Win32 Release"
# Name "LEngRes - Win32 Debug"
# Begin Source File

SOURCE=.\arrow.cur
# End Source File
# Begin Source File

SOURCE=.\arrowcop.cur
# End Source File
# Begin Source File

SOURCE=.\res\Grip.bmp
# End Source File
# Begin Source File

SOURCE=.\LEngRes.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\res\MIG.ico
# End Source File
# Begin Source File

SOURCE=.\Mig.rc

!IF  "$(CFG)" == "LEngRes - Win32 Release"

!ELSEIF  "$(CFG)" == "LEngRes - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\MIGDoc.ico
# End Source File
# Begin Source File

SOURCE=.\nodrop.cur
# End Source File
# End Target
# End Project
