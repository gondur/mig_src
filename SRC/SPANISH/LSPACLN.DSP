# Microsoft Developer Studio Project File - Name="LSpaCln" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=LSpaCln - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "LSpacln.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "LSpacln.mak" CFG="LSpaCln - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "LSpaCln - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "LSpaCln - Win32 Debug" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "LSpaCln - Win32 Release"

# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Cmd_Line "NMAKE /f LSpaCln.mak"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "LSpaCln.exe"
# PROP BASE Bsc_Name "LSpaCln.bsc"
# PROP BASE Target_Dir ""
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Cmd_Line "..\mycmds\mlangcln.bat"
# PROP Rebuild_Opt ""
# PROP Target_File "cleaned.flg"
# PROP Bsc_Name ""
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "LSpaCln - Win32 Debug"

# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "LSpaCln_"
# PROP BASE Intermediate_Dir "LSpaCln_"
# PROP BASE Cmd_Line "NMAKE /f LSpaCln.mak"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "LSpaCln.exe"
# PROP BASE Bsc_Name "LSpaCln.bsc"
# PROP BASE Target_Dir ""
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "LSpaCln_"
# PROP Intermediate_Dir "LSpaCln_"
# PROP Cmd_Line "..\mycmds\mlangcln.bat"
# PROP Rebuild_Opt ""
# PROP Target_File "cleaned.flg"
# PROP Bsc_Name ""
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "LSpaCln - Win32 Release"
# Name "LSpaCln - Win32 Debug"

!IF  "$(CFG)" == "LSpaCln - Win32 Release"

!ELSEIF  "$(CFG)" == "LSpaCln - Win32 Debug"

!ENDIF 

# Begin Source File

SOURCE=..\MYCMDS\mlangcln.bat
# End Source File
# End Target
# End Project
