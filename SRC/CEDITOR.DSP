# Microsoft Developer Studio Project File - Name="Ceditor" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Ceditor - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Ceditor.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Ceditor.mak" CFG="Ceditor - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Ceditor - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Ceditor - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Ceditor - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "Ceditor - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Ceditor_"
# PROP BASE Intermediate_Dir "Ceditor_"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Ceditor_"
# PROP Intermediate_Dir "Ceditor_"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /W3 /Gm /GX /Zi /Od /I "H" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "__MSVC__" /D "__CEDITOR__" /YX /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD BASE RSC /l 0x809 /d "_DEBUG"
# ADD RSC /l 0x809 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Ceditor - Win32 Release"
# Name "Ceditor - Win32 Debug"
# Begin Source File

SOURCE=.\aircraft\cd_a1.cpp
# End Source File
# Begin Source File

SOURCE=.\aircraft\cd_atmos.cpp
# End Source File
# Begin Source File

SOURCE=.\aircraft\cd_comm.cpp
# End Source File
# Begin Source File

SOURCE=.\aircraft\cd_f4u5.cpp
# End Source File
# Begin Source File

SOURCE=.\aircraft\cd_f51d.cpp
# End Source File
# Begin Source File

SOURCE=.\aircraft\cd_f8.cpp
# End Source File
# Begin Source File

SOURCE=.\aircraft\cd_f80c.cpp
# End Source File
# Begin Source File

SOURCE=.\aircraft\cd_f82g.cpp
# End Source File
# Begin Source File

SOURCE=.\aircraft\cd_f84e.cpp
# End Source File
# Begin Source File

SOURCE=.\aircraft\cd_f86e.cpp
# End Source File
# Begin Source File

SOURCE=.\aircraft\cd_f94a.cpp
# End Source File
# Begin Source File

SOURCE=.\aircraft\cd_f9f2.cpp
# End Source File
# Begin Source File

SOURCE=.\aircraft\cd_ffly.cpp
# End Source File
# Begin Source File

SOURCE=.\aircraft\cd_mig15.cpp
# End Source File
# Begin Source File

SOURCE=.\aircraft\cd_sfury.cpp
# End Source File
# Begin Source File

SOURCE=.\aircraft\cd_yak9.cpp
# End Source File
# Begin Source File

SOURCE=.\model\ceditor.cpp
# End Source File
# Begin Source File

SOURCE=.\model\ceditor.rc

!IF  "$(CFG)" == "Ceditor - Win32 Release"

!ELSEIF  "$(CFG)" == "Ceditor - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\model\curves.cpp
# End Source File
# Begin Source File

SOURCE=.\h\curves.h
# End Source File
# Begin Source File

SOURCE=.\h\dosdefs.h
# End Source File
# Begin Source File

SOURCE=.\model\modvec.cpp
# End Source File
# Begin Source File

SOURCE=.\h\modvec.h
# End Source File
# End Target
# End Project
