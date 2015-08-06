# Microsoft Developer Studio Project File - Name="CDR32" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=CDR32 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "CDR32.MAK".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "CDR32.MAK" CFG="CDR32 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CDR32 - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "CDR32 - Win32 Debug" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "CDR32 - Win32 Release"

# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Cmd_Line "NMAKE /f CDR32.MAK"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "CDR32.EXE"
# PROP BASE Bsc_Name "CDR32.BSC"
# PROP BASE Target_Dir ""
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Cmd_Line "NMAKE /f CDR32.MAK"
# PROP Rebuild_Opt "/a"
# PROP Target_File "CDR32.EXE"
# PROP Bsc_Name "CDR32.BSC"
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "CDR32 - Win32 Debug"

# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Cmd_Line "NMAKE /f CDR32.MAK"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "CDR32.EXE"
# PROP BASE Bsc_Name "CDR32.BSC"
# PROP BASE Target_Dir ""
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Cmd_Line "NMAKE /f CDR32.MAK"
# PROP Rebuild_Opt "/a"
# PROP Target_File "CDR32.EXE"
# PROP Bsc_Name "CDR32.BSC"
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "CDR32 - Win32 Release"
# Name "CDR32 - Win32 Debug"

!IF  "$(CFG)" == "CDR32 - Win32 Release"

!ELSEIF  "$(CFG)" == "CDR32 - Win32 Debug"

!ENDIF 

# Begin Source File

SOURCE=.\CDR32.c
# End Source File
# Begin Source File

SOURCE=.\Cdr32.def
# End Source File
# Begin Source File

SOURCE=.\Cdr32.h
# End Source File
# Begin Source File

SOURCE=.\cdr32.mak
# End Source File
# Begin Source File

SOURCE=.\Cdr32.rc
# End Source File
# Begin Source File

SOURCE=.\cdr32exp.c
# End Source File
# Begin Source File

SOURCE=.\Dllglob.h
# End Source File
# Begin Source File

SOURCE=.\Globals.h
# End Source File
# End Target
# End Project
