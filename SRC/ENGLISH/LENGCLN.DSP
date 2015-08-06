# Microsoft Developer Studio Project File - Name="LEngCln" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=LEngCln - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Lengcln.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Lengcln.mak" CFG="LEngCln - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "LEngCln - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "LEngCln - Win32 Debug" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "LEngCln - Win32 Release"

# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Cmd_Line "NMAKE /f LEngCln.mak"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "LEngCln.exe"
# PROP BASE Bsc_Name "LEngCln.bsc"
# PROP BASE Target_Dir ""
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Cmd_Line "..\mycmds\mlangcln.bat"
# PROP Rebuild_Opt ""
# PROP Target_File "cleaned.flg"
# PROP Bsc_Name ""
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "LEngCln - Win32 Debug"

# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "LEngCln_"
# PROP BASE Intermediate_Dir "LEngCln_"
# PROP BASE Cmd_Line "NMAKE /f LEngCln.mak"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "LEngCln.exe"
# PROP BASE Bsc_Name "LEngCln.bsc"
# PROP BASE Target_Dir ""
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "LEngCln_"
# PROP Intermediate_Dir "LEngCln_"
# PROP Cmd_Line "..\mycmds\mlangcln.bat"
# PROP Rebuild_Opt ""
# PROP Target_File "cleaned.flg"
# PROP Bsc_Name ""
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "LEngCln - Win32 Release"
# Name "LEngCln - Win32 Debug"

!IF  "$(CFG)" == "LEngCln - Win32 Release"

!ELSEIF  "$(CFG)" == "LEngCln - Win32 Debug"

!ENDIF 

# Begin Source File

SOURCE=..\MYCMDS\mlangcln.bat
# End Source File
# End Target
# End Project
