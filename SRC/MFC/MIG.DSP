# Microsoft Developer Studio Project File - Name="MIG" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=MIG - Win32 Demo Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Mig.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Mig.mak" CFG="MIG - Win32 Demo Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MIG - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "MIG - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "MIG - Win32 Profile" (based on "Win32 (x86) Application")
!MESSAGE "MIG - Win32 Demo" (based on "Win32 (x86) Application")
!MESSAGE "MIG - Win32 Demo Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "\mig\release\exe"
# PROP Intermediate_Dir "\mig\release\obj"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /G6 /MD /W3 /GX /O2 /I "\mig\src\h" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD BASE RSC /l 0x809 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x809 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 ddraw.lib mss32.lib dplay.lib winmm.lib dinput.lib dxguid.lib smackw32.lib /nologo /subsystem:windows /machine:I386 /libpath:"..\lib"
# SUBTRACT LINK32 /debug
# Begin Special Build Tool
SOURCE=$(InputPath)
PreLink_Cmds=rem cl 000tools.cpp /c /nologo /W3 /GX /Zi /MD /I "..\h"\
                                                                     /FR"\mig\release\obj/" /Fo"\mig\release\obj/" /Fd"\mig\release\obj/"
# End Special Build Tool

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "\mig\debug\exe"
# PROP Intermediate_Dir "\mig\debug\obj"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W3 /GX /Zi /O2 /I "..\h" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD BASE RSC /l 0x809 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x809 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ddraw.lib mss32.lib dplay.lib winmm.lib dinput.lib dxguid.lib smackw32.lib /nologo /subsystem:windows /incremental:no /debug /machine:I386 /nodefaultlib:"libc" /libpath:"..\lib"
# SUBTRACT LINK32 /pdb:none /nodefaultlib
# Begin Special Build Tool
SOURCE=$(InputPath)
PreLink_Desc=Pre Link
PreLink_Cmds=cl 000tools.cpp /c /nologo /W3 /GX /Zi /I "..\h"\
                                                                                                 /FR"\mig\debug\obj/" /Od /D "_DEBUG" /Fo"\mig\debug\obj/" /Fd"\mig\debug\obj/"
# End Special Build Tool

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "MIG___Wi"
# PROP BASE Intermediate_Dir "MIG___Wi"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "\mig\debug\ttexe"
# PROP Intermediate_Dir "\mig\debug\ttobj"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /Gi /GX /Zi /Od /I "..\h" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W3 /Gm /Gi /GX /Zi /Od /I "..\h" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD BASE RSC /l 0x809 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x809 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ddraw.lib mss32.lib dplay.lib winmm.lib dinput.lib dxguid.lib smackw32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept /libpath:"..\lib"
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ddraw.lib mss32.lib dplay.lib winmm.lib dinput.lib dxguid.lib smackw32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept /libpath:"..\lib"
# SUBTRACT LINK32 /pdb:none
# Begin Special Build Tool
SOURCE=$(InputPath)
PreLink_Desc=Pre Link
PreLink_Cmds=cl 000tools.cpp /c /nologo /W3 /GX /Zi /I "..\h"\
                                                                                                 /FR"\mig\debug\obj/" /Od /D "_DEBUG"
# End Special Build Tool

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "MIG___Wi"
# PROP BASE Intermediate_Dir "MIG___Wi"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "\mig\demo\exe"
# PROP Intermediate_Dir "\mig\demo\obj"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /G6 /MD /W3 /GX /O2 /I "\mig\src\h" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /G6 /MD /W3 /GX /O2 /I "\mig\src\h" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "MIG_DEMO_VER" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD BASE RSC /l 0x809 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x809 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ddraw.lib mss32.lib dplay.lib winmm.lib dinput.lib dxguid.lib smackw32.lib /nologo /subsystem:windows /debug /machine:I386 /libpath:"..\lib"
# ADD LINK32 ddraw.lib mss32.lib dplay.lib winmm.lib dinput.lib dxguid.lib smackw32.lib /nologo /subsystem:windows /debug /machine:I386 /libpath:"..\lib"
# Begin Special Build Tool
SOURCE=$(InputPath)
PreLink_Cmds=rem cl 000tools.cpp /c /nologo /W3 /GX /Zi /MD /I "..\h"\
                                                                     /FR"\mig\release\obj/" /Fo"\mig\release\obj/" /Fd"\mig\release\obj/"
# End Special Build Tool

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "MIG___Wi"
# PROP BASE Intermediate_Dir "MIG___Wi"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "\mig\demodeb\exe"
# PROP Intermediate_Dir "\mig\demodeb\obj"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /GX /Zi /O2 /I "..\h" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W3 /GX /Zi /O2 /I "..\h" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "MIG_DEMO_VER" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD BASE RSC /l 0x809 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x809 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ddraw.lib mss32.lib dplay.lib winmm.lib dinput.lib dxguid.lib smackw32.lib /nologo /subsystem:windows /incremental:no /debug /machine:I386 /nodefaultlib:"libc" /libpath:"..\lib"
# SUBTRACT BASE LINK32 /pdb:none /nodefaultlib
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ddraw.lib mss32.lib dplay.lib winmm.lib dinput.lib dxguid.lib smackw32.lib /nologo /subsystem:windows /incremental:no /debug /machine:I386 /nodefaultlib:"libc" /libpath:"..\lib"
# SUBTRACT LINK32 /pdb:none /nodefaultlib
# Begin Special Build Tool
SOURCE=$(InputPath)
PreLink_Desc=Pre Link
PreLink_Cmds=cl 000tools.cpp /c /nologo /W3 /GX /Zi /I "..\h"\
                                                                                                 /FR"\mig\debug\obj/" /Od /D "_DEBUG" /Fo"\mig\debug\obj/" /Fd"\mig\debug\obj/"
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "MIG - Win32 Release"
# Name "MIG - Win32 Debug"
# Name "MIG - Win32 Profile"
# Name "MIG - Win32 Demo"
# Name "MIG - Win32 Demo Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "new files trap"

# PROP Default_Filter ".cpp"
# End Group
# Begin Group "tool dependency compiled first"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\000tools.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\H\000tools.h
# End Source File
# Begin Source File

SOURCE=.\stdafx.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# ADD CPP /O2 /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# ADD CPP /Od /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# ADD BASE CPP /O2 /Yc"stdafx.h"
# ADD CPP /O2 /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# ADD BASE CPP /Od /Yc"stdafx.h"
# ADD CPP /Od /Yc"stdafx.h"

!ENDIF 

# End Source File
# End Group
# Begin Group "assembler"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Graphics\Grafpasm.asm

!IF  "$(CFG)" == "MIG - Win32 Release"

# Begin Custom Build
IntDir=\mig\release\obj
InputPath=..\Graphics\Grafpasm.asm
InputName=Grafpasm

"$(IntDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ml /c /Cp /Cx /Fo$(IntDir)\$(InputName).obj $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# Begin Custom Build
IntDir=\mig\debug\obj
InputPath=..\Graphics\Grafpasm.asm
InputName=Grafpasm

"$(IntDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ml /c /Cp /Cx /Fo$(IntDir)\$(InputName).obj $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# Begin Custom Build
IntDir=\mig\debug\ttobj
InputPath=..\Graphics\Grafpasm.asm
InputName=Grafpasm

"$(IntDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ml /c /Cp /Cx /Fo$(IntDir)\$(InputName).obj $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# Begin Custom Build
IntDir=\mig\demo\obj
InputPath=..\Graphics\Grafpasm.asm
InputName=Grafpasm

"$(IntDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ml /c /Cp /Cx /Fo$(IntDir)\$(InputName).obj $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# Begin Custom Build
IntDir=\mig\demodeb\obj
InputPath=..\Graphics\Grafpasm.asm
InputName=Grafpasm

"$(IntDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ml /c /Cp /Cx /Fo$(IntDir)\$(InputName).obj $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\3d\Lstrasm.asm

!IF  "$(CFG)" == "MIG - Win32 Release"

# Begin Custom Build
IntDir=\mig\release\obj
InputPath=..\3d\Lstrasm.asm
InputName=Lstrasm

"$(IntDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ml /c /Cp /Cx /Fo$(IntDir)\$(InputName).obj $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# Begin Custom Build
IntDir=\mig\debug\obj
InputPath=..\3d\Lstrasm.asm
InputName=Lstrasm

"$(IntDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ml /c /Cp /Cx /Fo$(IntDir)\$(InputName).obj $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# Begin Custom Build
IntDir=\mig\debug\ttobj
InputPath=..\3d\Lstrasm.asm
InputName=Lstrasm

"$(IntDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ml /c /Cp /Cx /Fo$(IntDir)\$(InputName).obj $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# Begin Custom Build
IntDir=\mig\demo\obj
InputPath=..\3d\Lstrasm.asm
InputName=Lstrasm

"$(IntDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ml /c /Cp /Cx /Fo$(IntDir)\$(InputName).obj $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# Begin Custom Build
IntDir=\mig\demodeb\obj
InputPath=..\3d\Lstrasm.asm
InputName=Lstrasm

"$(IntDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ml /c /Cp /Cx /Fo$(IntDir)\$(InputName).obj $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Math\Matrasm.asm

!IF  "$(CFG)" == "MIG - Win32 Release"

# Begin Custom Build
IntDir=\mig\release\obj
InputPath=..\Math\Matrasm.asm
InputName=Matrasm

"$(IntDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ml /c /Cp /Cx /Fo$(IntDir)\$(InputName).obj $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# Begin Custom Build
IntDir=\mig\debug\obj
InputPath=..\Math\Matrasm.asm
InputName=Matrasm

"$(IntDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ml /c /Cp /Cx /Fo$(IntDir)\$(InputName).obj $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# Begin Custom Build
IntDir=\mig\debug\ttobj
InputPath=..\Math\Matrasm.asm
InputName=Matrasm

"$(IntDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ml /c /Cp /Cx /Fo$(IntDir)\$(InputName).obj $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# Begin Custom Build
IntDir=\mig\demo\obj
InputPath=..\Math\Matrasm.asm
InputName=Matrasm

"$(IntDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ml /c /Cp /Cx /Fo$(IntDir)\$(InputName).obj $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# Begin Custom Build
IntDir=\mig\demodeb\obj
InputPath=..\Math\Matrasm.asm
InputName=Matrasm

"$(IntDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ml /c /Cp /Cx /Fo$(IntDir)\$(InputName).obj $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "3D"

# PROP Default_Filter ".cpp"
# Begin Source File

SOURCE=..\3D\3dcode.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\3D\3dcom.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\3D\_3D.CPP

!IF  "$(CFG)" == "MIG - Win32 Release"

# ADD CPP /D "MIG_3D"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# ADD CPP /Gm- /Gi- /Od /D "MIG_3D"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# ADD BASE CPP /Gm- /Gi- /O2 /D "MIG_3D"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /Gm- /Gi- /O2 /D "MIG_3D"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# ADD BASE CPP /D "MIG_3D"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /D "MIG_3D"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# ADD BASE CPP /Gm- /Gi- /Od /D "MIG_3D"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /Gm- /Gi- /Od /D "MIG_3D"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\3d\Anmradio.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\3D\Btree.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\3D\Collided.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\3d\Decomp.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\3D\Imagemap.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\3D\Jimcol.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# ADD CPP /O2
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# ADD BASE CPP /O2
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /O2
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\3d\Jimtri.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\3D\Landscap.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\3D\Lstream.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\3D\Migland.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\3D\Overlay.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# ADD CPP /Od
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\3D\particle.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# ADD CPP /O2
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# ADD BASE CPP /O2
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /O2
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# ADD BASE CPP /O2
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /O2
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\3D\Shapes.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\3D\Shpbld.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\3d\Tilemake.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# ADD CPP /O2
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# ADD BASE CPP /O2
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /O2
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# ADD BASE CPP /O2
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /O2
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\3D\Transite.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\3D\Viewsel.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\3d\Weappak.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# ADD CPP /O2
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# ADD BASE CPP /O2
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /O2
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# ADD BASE CPP /O2
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /O2
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\3D\World.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Group "AI"

# PROP Default_Filter ".cpp"
# Begin Source File

SOURCE=..\AI\_AI.CPP

!IF  "$(CFG)" == "MIG - Win32 Release"

# ADD CPP /D "MIG_AI"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# ADD CPP /Od /D "MIG_AI"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# ADD BASE CPP /O2 /D "MIG_AI"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /O2 /D "MIG_AI"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# ADD BASE CPP /D "MIG_AI"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /D "MIG_AI"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# ADD BASE CPP /Od /D "MIG_AI"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /Od /D "MIG_AI"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\AI\Aaa.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\AI\Msgai.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\AI\Spotted.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Ai\Usermsg.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Group "AIRCRAFT"

# PROP Default_Filter ".cpp"
# Begin Source File

SOURCE=..\AIRCRAFT\_AIRC.CPP

!IF  "$(CFG)" == "MIG - Win32 Release"

# ADD CPP /D "MIG_AIRCRAFT"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# ADD CPP /O2 /D "MIG_AIRCRAFT"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# ADD BASE CPP /O2 /D "MIG_AIRCRAFT"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /O2 /D "MIG_AIRCRAFT"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# ADD BASE CPP /D "MIG_AIRCRAFT"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /D "MIG_AIRCRAFT"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# ADD BASE CPP /O2 /D "MIG_AIRCRAFT"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /O2 /D "MIG_AIRCRAFT"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Aircraft\Ai_f4u5.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Aircraft\Ai_f51d.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Aircraft\Ai_f8.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Aircraft\Ai_f80c.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Aircraft\Ai_f82g.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Aircraft\Ai_f84e.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Aircraft\Ai_f86e.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Aircraft\Ai_f9f2.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Aircraft\Ai_ffly.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Aircraft\Ai_mig15.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Aircraft\Ai_sfury.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Aircraft\Ai_yak9.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\AIRCRAFT\Cd_a1.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\AIRCRAFT\Cd_atmos.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\AIRCRAFT\Cd_comm.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\AIRCRAFT\Cd_f4u5.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\AIRCRAFT\Cd_f51d.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\AIRCRAFT\Cd_f8.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\AIRCRAFT\Cd_f80c.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\AIRCRAFT\Cd_f82g.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\AIRCRAFT\Cd_f84e.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\AIRCRAFT\Cd_f86e.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\AIRCRAFT\Cd_f94a.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\AIRCRAFT\Cd_f9f2.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\AIRCRAFT\Cd_ffly.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\AIRCRAFT\Cd_mig15.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\AIRCRAFT\Cd_sfury.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\AIRCRAFT\Cd_yak9.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\AIRCRAFT\Dt_f4u5.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\AIRCRAFT\Dt_f51d.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\AIRCRAFT\Dt_f8.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\AIRCRAFT\Dt_f80c.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\AIRCRAFT\Dt_f82g.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\AIRCRAFT\Dt_f84e.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\AIRCRAFT\Dt_f86e.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\AIRCRAFT\Dt_f9f2.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\AIRCRAFT\Dt_ffly.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\AIRCRAFT\Dt_mig15.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Aircraft\Dt_other.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\AIRCRAFT\Dt_sfury.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\AIRCRAFT\Dt_yak9.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Group "BFIELDS"

# PROP Default_Filter ".cpp"
# Begin Source File

SOURCE=..\BFIELDS\_BFIE.CPP

!IF  "$(CFG)" == "MIG - Win32 Release"

# ADD CPP /D "MIG_BFIELDS"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# ADD CPP /Od /D "MIG_BFIELDS"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# ADD BASE CPP /Od /D "MIG_BFIELDS"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /Od /D "MIG_BFIELDS"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# ADD BASE CPP /D "MIG_BFIELDS"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /D "MIG_BFIELDS"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# ADD BASE CPP /O2 /D "MIG_BFIELDS"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /O2 /D "MIG_BFIELDS"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\BFIELDS\Globrefs.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\BFIELDS\Mapcode.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\BFIELDS\Messages.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\BFIELDS\Persons2.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\BFIELDS\Persons3.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\BFIELDS\Persons4.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\BFIELDS\Persons7.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\BFIELDS\qmiss.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\BFIELDS\Savebin.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\BFIELDS\Tank.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Group "FILES"

# PROP Default_Filter ".cpp"
# Begin Source File

SOURCE=..\FILES\_FILE.CPP

!IF  "$(CFG)" == "MIG - Win32 Release"

# ADD CPP /D "MIG_FILES"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# ADD CPP /Od /D "MIG_FILES"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# ADD BASE CPP /Od /D "MIG_FILES"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /Od /D "MIG_FILES"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# ADD BASE CPP /D "MIG_FILES"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /D "MIG_FILES"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# ADD BASE CPP /Od /D "MIG_FILES"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /Od /D "MIG_FILES"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\FILES\Fileman.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\FILES\Loadlib.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\FILES\Loadlist.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\FILES\Winfile.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Group "GENERAL"

# PROP Default_Filter ".cpp"
# Begin Source File

SOURCE=..\GENERAL\_GENE.CPP

!IF  "$(CFG)" == "MIG - Win32 Release"

# ADD CPP /D "MIG_GENERAL"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# ADD CPP /Od /D "MIG_GENERAL"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# ADD BASE CPP /O2 /D "MIG_GENERAL"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /O2 /D "MIG_GENERAL"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# ADD BASE CPP /D "MIG_GENERAL"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /D "MIG_GENERAL"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# ADD BASE CPP /O2 /D "MIG_GENERAL"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /O2 /D "MIG_GENERAL"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\GENERAL\Malloc.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\GENERAL\Static.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\GENERAL\Winerror.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Group "GRAPHICS"

# PROP Default_Filter ".cpp"
# Begin Source File

SOURCE=..\GRAPHICS\_GRAP.CPP

!IF  "$(CFG)" == "MIG - Win32 Release"

# ADD CPP /D "MIG_GRAPHICS"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# ADD CPP /Od /D "MIG_GRAPHICS"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# ADD BASE CPP /O2 /D "MIG_GRAPHICS"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /O2 /D "MIG_GRAPHICS"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# ADD BASE CPP /D "MIG_GRAPHICS"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /D "MIG_GRAPHICS"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# ADD BASE CPP /O2 /D "MIG_GRAPHICS"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /O2 /D "MIG_GRAPHICS"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\GRAPHICS\Grafprim.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\GRAPHICS\Lbm.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\GRAPHICS\Polygon.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\GRAPHICS\Tga.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Graphics\Winsmack.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\GRAPHICS\Wrapper.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Group "HARDWARE"

# PROP Default_Filter ".cpp"
# Begin Source File

SOURCE=..\HARDWARE\_HARD.CPP

!IF  "$(CFG)" == "MIG - Win32 Release"

# ADD CPP /D "MIG_HARDWARE"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# ADD CPP /Od /D "MIG_HARDWARE"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# ADD BASE CPP /O2 /D "MIG_HARDWARE"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /O2 /D "MIG_HARDWARE"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# ADD BASE CPP /D "MIG_HARDWARE"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /D "MIG_HARDWARE"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# ADD BASE CPP /Od /D "MIG_HARDWARE"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /Od /D "MIG_HARDWARE"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Hardware\Config.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\HARDWARE\Ddrwinit.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\HARDWARE\Hardpub.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\HARDWARE\Hardwin.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Hardware\Messengn.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1
# ADD CPP /O2
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# ADD BASE CPP /O2
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /O2
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\HARDWARE\Miles.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\HARDWARE\Rchatter.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\HARDWARE\Sfonts.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\HARDWARE\Win3d.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Group "INPUT"

# PROP Default_Filter ".cpp"
# Begin Source File

SOURCE=..\INPUT\_INPU.CPP

!IF  "$(CFG)" == "MIG - Win32 Release"

# ADD CPP /D "MIG_INPUT"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# ADD CPP /O2 /D "MIG_INPUT"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# ADD BASE CPP /O2 /D "MIG_INPUT"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /O2 /D "MIG_INPUT"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# ADD BASE CPP /D "MIG_INPUT"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /D "MIG_INPUT"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# ADD BASE CPP /O2 /D "MIG_INPUT"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /O2 /D "MIG_INPUT"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\INPUT\Analogue.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Group "MATH"

# PROP Default_Filter ".cpp"
# Begin Source File

SOURCE=..\MATH\_MATH.CPP

!IF  "$(CFG)" == "MIG - Win32 Release"

# ADD CPP /D "MIG_MATH"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# ADD CPP /O2 /D "MIG_MATH"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# ADD BASE CPP /O2 /D "MIG_MATH"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /O2 /D "MIG_MATH"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# ADD BASE CPP /D "MIG_MATH"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /D "MIG_MATH"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# ADD BASE CPP /O2 /D "MIG_MATH"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /O2 /D "MIG_MATH"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MATH\Math.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MATH\Matrix.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Group "MISSMAN"

# PROP Default_Filter ".cpp"
# Begin Source File

SOURCE=..\MISSMAN\_MISS.CPP

!IF  "$(CFG)" == "MIG - Win32 Release"

# ADD CPP /D "MIG_MISSMAN"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# ADD CPP /Od /D "MIG_MISSMAN"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# ADD BASE CPP /Od /D "MIG_MISSMAN"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /Od /D "MIG_MISSMAN"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# ADD BASE CPP /D "MIG_MISSMAN"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /D "MIG_MISSMAN"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# ADD BASE CPP /Od /D "MIG_MISSMAN"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /Od /D "MIG_MISSMAN"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MISSMAN\Formatn.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MISSMAN\Intrmiss.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MISSMAN\Missinit.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MISSMAN\Node.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Missman\Noderev.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# ADD CPP /Od
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# ADD BASE CPP /Od
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /Od
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# ADD BASE CPP /Od
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /Od
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MISSMAN\Onemiss.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MISSMAN\packages.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MISSMAN\Peacmiss.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MISSMAN\Savegame.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MISSMAN\So51miss.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Group "MODEL"

# PROP Default_Filter ".cpp"
# Begin Source File

SOURCE=..\MODEL\_MODE.CPP

!IF  "$(CFG)" == "MIG - Win32 Release"

# ADD CPP /D "MIG_MODEL"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# ADD CPP /Od /D "MIG_MODEL"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# ADD BASE CPP /O2 /D "MIG_MODEL"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /O2 /D "MIG_MODEL"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# ADD BASE CPP /D "MIG_MODEL"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /D "MIG_MODEL"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# ADD BASE CPP /Od /D "MIG_MODEL"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /Od /D "MIG_MODEL"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MODEL\Acmai.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MODEL\Acmman.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MODEL\Acmmodel.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MODEL\Acmsimpl.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MODEL\Aerodev.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MODEL\Cdat.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MODEL\Ctrl.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MODEL\Curves.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MODEL\Dervs.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MODEL\Elmt.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MODEL\Engine.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MODEL\Gear.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MODEL\Model.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MODEL\Modint.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MODEL\Modvec.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MODEL\Sky.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Group "MOVECODE"

# PROP Default_Filter ".cpp"
# Begin Source File

SOURCE=..\MOVECODE\_MOVE.CPP

!IF  "$(CFG)" == "MIG - Win32 Release"

# ADD CPP /D "MIG_MOVECODE"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# ADD CPP /Od /D "MIG_MOVECODE"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# ADD BASE CPP /Od /D "MIG_MOVECODE"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /Od /D "MIG_MOVECODE"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# ADD BASE CPP /D "MIG_MOVECODE"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /D "MIG_MOVECODE"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# ADD BASE CPP /Od /D "MIG_MOVECODE"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /Od /D "MIG_MOVECODE"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MOVECODE\Automove.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MOVECODE\Flyinit.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MOVECODE\Flymodel.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MOVECODE\Keyfly.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MOVECODE\Moveall.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MOVECODE\Wpaction.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Group "TEXT"

# PROP Default_Filter ".cpp"
# Begin Source File

SOURCE=..\TEXT\_TEXT.CPP

!IF  "$(CFG)" == "MIG - Win32 Release"

# ADD CPP /D "MIG_TEXT"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# ADD CPP /O2 /D "MIG_TEXT"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# ADD BASE CPP /O2 /D "MIG_TEXT"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /O2 /D "MIG_TEXT"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# ADD BASE CPP /D "MIG_TEXT"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /D "MIG_TEXT"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# ADD BASE CPP /O2 /D "MIG_TEXT"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /O2 /D "MIG_TEXT"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\TEXT\Textinit.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\TEXT\Textref.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Group "COMMS"

# PROP Default_Filter ".cpp"
# Begin Source File

SOURCE=..\COMMS\_COMM.CPP

!IF  "$(CFG)" == "MIG - Win32 Release"

# ADD CPP /D "MIG_COMMS"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# ADD CPP /Od /D "MIG_COMMS"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# ADD BASE CPP /O2 /D "MIG_COMMS"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /O2 /D "MIG_COMMS"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# ADD BASE CPP /D "MIG_COMMS"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /D "MIG_COMMS"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# ADD BASE CPP /O2 /D "MIG_COMMS"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /O2 /D "MIG_COMMS"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\COMMS\Aggrgtor.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\COMMS\Comms.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\COMMS\Replay.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\COMMS\Winmove.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Group "MFCSTUFF"

# PROP Default_Filter ".cpp"
# Begin Source File

SOURCE=.\_MFC.CPP

!IF  "$(CFG)" == "MIG - Win32 Release"

# ADD CPP /O2

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# ADD CPP /Od

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# SUBTRACT BASE CPP /O<none>
# SUBTRACT CPP /O<none>

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# ADD BASE CPP /O2
# ADD CPP /O2

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# ADD BASE CPP /Od
# ADD CPP /Od

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\CntrItem.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\custbb.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Fullpane.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Hintbox.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Input\Keystub.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Listbx.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Maintbar.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MapDlg.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MIG.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MIGDoc.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MIGView.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\3d\Monotxt.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# ADD CPP /O2
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# ADD CPP /Od
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# ADD BASE CPP /O1
# ADD CPP /O2
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# ADD BASE CPP /Od
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /Od
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Msctlbr.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\RDEmptyD.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\RDEmptyP.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\rdiallog.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\RDialog.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Rdlgbar.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\RowTasks.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Stub3d.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\sysbox.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\thumnail.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Titlebar.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Group "AFXSTUB"

# PROP Default_Filter ".cpp"
# Begin Source File

SOURCE=.\_AFX.CPP

!IF  "$(CFG)" == "MIG - Win32 Release"

# ADD CPP /O2

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# ADD CPP /Od

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# ADD BASE CPP /Od
# ADD CPP /Od

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# ADD BASE CPP /O2
# ADD CPP /O2

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# ADD BASE CPP /Od
# ADD CPP /Od

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Afxauto.h

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\afxstub.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\font.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\picture.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\rbutton.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\rcombo.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\RComboX.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\redit.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\redtbt.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\rjoycfg.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\rlistbox.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\rscrlbar.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Rspinbut.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\rspltbar.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\rstatic.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\rtabs.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\rtitle.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Group "SHEETS"

# PROP Default_Filter ".cpp"
# Begin Source File

SOURCE=.\_SHEETS.CPP

!IF  "$(CFG)" == "MIG - Win32 Release"

# ADD CPP /O2

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# ADD CPP /Od

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# SUBTRACT BASE CPP /O<none>
# SUBTRACT CPP /O<none>

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# ADD BASE CPP /O2
# ADD CPP /O2

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# ADD BASE CPP /Od
# ADD CPP /Od

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\AC_view.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\AFields.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Apilot.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Army.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Army_dos.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ArmyDetl.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Armyrqst.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Author.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Bases.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Basest.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Battdetl.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Campback.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Camplist.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Campwar.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Career.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Choke.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ChSquad.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Cmbtview.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Comit_e.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Commsac.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Commspnt.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\credits.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# ADD CPP /Od

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# ADD BASE CPP /Od
# ADD CPP /Od

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Currembl.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Damage.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Dbrftlbr.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Directs2.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DIS.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Dis_note.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DosBut.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Dossier.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Filing.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Flt_Task.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Footage.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Frag.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\FragPilt.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\General.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Grndview.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\JoyConfg.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\JoyError.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Load.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Loadprof.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Locker.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Lstmsnlg.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1
# ADD CPP /Od

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# ADD BASE CPP /Od
# ADD CPP /Od

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MapFltrs.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MapFrag.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Misn_log.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Misntext.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Missfldr.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MResult.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Msndebrf.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1
# ADD CPP /Od
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# ADD BASE CPP /Od
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /Od
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MTChild.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\nose_art.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Notes.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Overview.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Paint.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\personal.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Pilots.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Plyr_log.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Prof_lib.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Profile.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Quikmisn.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Radio.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Ready.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\RIP_List.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Rmdldlg.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Route.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Rradio.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Rtestsh1.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Rtoolbar.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Sairclms.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Save.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Saveprof.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Scalebar.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Scamp.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Scontrol.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Sdetail.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Selects.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\service.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\session.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Sflight.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Sgame.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Sgrdclms.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Smkdlg.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Sqdnlb.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Sqdnlbut.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Sqdnlist.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Squads.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Squick1.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Squick2.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Squickp.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Squickun.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Sqview.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Sreplay.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Ssound.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Stores.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Supply.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Sviewer.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Task.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Tasktabs.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Traffic.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Userinst.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Variants.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Visitors.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Vwqlist.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Wave.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Waveins.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\WaveTabs.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Weapons.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Weather.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\WPBut.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Wpdetail.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\WPGround.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\WPShare.cpp

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "New Headers Trap"

# PROP Default_Filter "h"
# Begin Source File

SOURCE=..\H\animptr.h
# End Source File
# End Group
# Begin Group "0-9"

# PROP Default_Filter "h"
# Begin Source File

SOURCE=..\H\3dcode.h
# End Source File
# Begin Source File

SOURCE=..\H\3dcom.h
# End Source File
# Begin Source File

SOURCE=..\H\3ddefs.h
# End Source File
# Begin Source File

SOURCE=..\H\3dinstr.h
# End Source File
# End Group
# Begin Group "A"

# PROP Default_Filter "h"
# Begin Group "Astub"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\AC_view.h
# End Source File
# Begin Source File

SOURCE=.\AFields.h
# End Source File
# Begin Source File

SOURCE=.\Apilot.h
# End Source File
# Begin Source File

SOURCE=.\Army.h
# End Source File
# Begin Source File

SOURCE=.\Army_dos.h
# End Source File
# Begin Source File

SOURCE=.\ArmyDetl.h
# End Source File
# Begin Source File

SOURCE=.\Armyrqst.h
# End Source File
# Begin Source File

SOURCE=.\Author.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\H\Aaa.h
# End Source File
# Begin Source File

SOURCE=..\H\Ac_view.h
# End Source File
# Begin Source File

SOURCE=..\H\Acmmodel.h
# End Source File
# Begin Source File

SOURCE=..\H\Aerodev.h
# End Source File
# Begin Source File

SOURCE=..\H\Afields.h
# End Source File
# Begin Source File

SOURCE=..\H\Aggrgtor.h
# End Source File
# Begin Source File

SOURCE=..\H\Ai.h
# End Source File
# Begin Source File

SOURCE=..\H\Analogue.h
# End Source File
# Begin Source File

SOURCE=..\H\Animdata.h
# End Source File
# Begin Source File

SOURCE=..\H\Anmradio.h
# End Source File
# Begin Source File

SOURCE=..\H\Apilot.h
# End Source File
# Begin Source File

SOURCE=..\H\Areatype.h
# End Source File
# Begin Source File

SOURCE=..\H\Army.h
# End Source File
# Begin Source File

SOURCE=..\H\Army_dos.h
# End Source File
# Begin Source File

SOURCE=..\H\Armydetl.h
# End Source File
# Begin Source File

SOURCE=..\H\Armyrqst.h
# End Source File
# Begin Source File

SOURCE=..\H\Author.h
# End Source File
# End Group
# Begin Group "B"

# PROP Default_Filter ""
# Begin Group "Bstub"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Bases.h
# End Source File
# Begin Source File

SOURCE=.\Basest.h
# End Source File
# Begin Source File

SOURCE=.\Battdetl.h
# End Source File
# Begin Source File

SOURCE=.\Butonbar.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\H\Bases.h
# End Source File
# Begin Source File

SOURCE=..\H\Basest.h
# End Source File
# Begin Source File

SOURCE=..\H\Batnode.h
# End Source File
# Begin Source File

SOURCE=..\H\Battdetl.h
# End Source File
# Begin Source File

SOURCE=..\H\Bfcommon.h
# End Source File
# Begin Source File

SOURCE=..\H\Bfenum.h
# End Source File
# Begin Source File

SOURCE=..\H\Bfnumber.h
# End Source File
# Begin Source File

SOURCE=..\H\Bitcount.h
# End Source File
# Begin Source File

SOURCE=..\H\Bitfield.h
# End Source File
# Begin Source File

SOURCE=..\H\Boxcol.h
# End Source File
# Begin Source File

SOURCE=..\H\Briefing.h
# End Source File
# Begin Source File

SOURCE=..\H\Bstream.h
# End Source File
# Begin Source File

SOURCE=..\H\Btree.h
# End Source File
# Begin Source File

SOURCE=..\H\Butonbar.h
# End Source File
# End Group
# Begin Group "C"

# PROP Default_Filter ""
# Begin Group "Cstub"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Campback.h
# End Source File
# Begin Source File

SOURCE=.\Camplist.h
# End Source File
# Begin Source File

SOURCE=.\Campwar.h
# End Source File
# Begin Source File

SOURCE=.\Career.h
# End Source File
# Begin Source File

SOURCE=.\Chain.h
# End Source File
# Begin Source File

SOURCE=.\Choke.h
# End Source File
# Begin Source File

SOURCE=.\ChSquad.h
# End Source File
# Begin Source File

SOURCE=.\Cmbtview.h
# End Source File
# Begin Source File

SOURCE=.\Comit_e.h
# End Source File
# Begin Source File

SOURCE=.\Commsac.h
# End Source File
# Begin Source File

SOURCE=.\Commspnt.h
# End Source File
# Begin Source File

SOURCE=.\Currembl.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\H\Campback.h
# End Source File
# Begin Source File

SOURCE=..\H\Camplist.h
# End Source File
# Begin Source File

SOURCE=..\H\Campwar.h
# End Source File
# Begin Source File

SOURCE=..\H\Career.h
# End Source File
# Begin Source File

SOURCE=..\H\Cbuffer.h
# End Source File
# Begin Source File

SOURCE=..\H\Chain.h
# End Source File
# Begin Source File

SOURCE=..\H\Choke.h
# End Source File
# Begin Source File

SOURCE=..\H\Chsquad.h
# End Source File
# Begin Source File

SOURCE=..\H\Cmbtview.h
# End Source File
# Begin Source File

SOURCE=..\H\Cntritem.h
# End Source File
# Begin Source File

SOURCE=..\H\Collided.h
# End Source File
# Begin Source File

SOURCE=..\H\Comit_e.h
# End Source File
# Begin Source File

SOURCE=..\H\Comms.h
# End Source File
# Begin Source File

SOURCE=..\H\Commsac.h
# End Source File
# Begin Source File

SOURCE=..\H\Commspnt.h
# End Source File
# Begin Source File

SOURCE=..\H\Config.h
# End Source File
# Begin Source File

SOURCE=..\H\Contlist.h
# End Source File
# Begin Source File

SOURCE=..\H\Credits.h
# End Source File
# Begin Source File

SOURCE=.\Credits.h
# End Source File
# Begin Source File

SOURCE=..\H\Cstring.h
# End Source File
# Begin Source File

SOURCE=..\H\Ctimeout.h
# End Source File
# Begin Source File

SOURCE=..\H\Ctrl.h
# End Source File
# Begin Source File

SOURCE=..\H\Currembl.h
# End Source File
# Begin Source File

SOURCE=..\H\Curves.h
# End Source File
# Begin Source File

SOURCE=..\H\Custbb.h
# End Source File
# End Group
# Begin Group "D"

# PROP Default_Filter ""
# Begin Group "Dstub"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Damage.h
# End Source File
# Begin Source File

SOURCE=.\Dbrftlbr.h
# End Source File
# Begin Source File

SOURCE=.\Directs.h
# End Source File
# Begin Source File

SOURCE=.\Directs1.h
# End Source File
# Begin Source File

SOURCE=.\Directs2.h
# End Source File
# Begin Source File

SOURCE=.\DIS.h
# End Source File
# Begin Source File

SOURCE=.\disnotes.h
# End Source File
# Begin Source File

SOURCE=.\DosBut.h
# End Source File
# Begin Source File

SOURCE=.\Dossier.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\H\D3dmacs.h
# End Source File
# Begin Source File

SOURCE=..\H\Damage.h
# End Source File
# Begin Source File

SOURCE=..\H\Dbrftlbr.h
# End Source File
# Begin Source File

SOURCE=..\H\Debrief.h
# End Source File
# Begin Source File

SOURCE=.\Debrief.h
# End Source File
# Begin Source File

SOURCE=..\H\Dinput.h
# End Source File
# Begin Source File

SOURCE=..\H\Directs.h
# End Source File
# Begin Source File

SOURCE=..\H\Directs1.h
# End Source File
# Begin Source File

SOURCE=..\H\Directs2.h
# End Source File
# Begin Source File

SOURCE=..\H\Dis.h
# End Source File
# Begin Source File

SOURCE=..\H\Dis_note.h
# End Source File
# Begin Source File

SOURCE=.\Dis_note.h
# End Source File
# Begin Source File

SOURCE=..\H\Disnotes.h
# End Source File
# Begin Source File

SOURCE=..\H\Display.h
# End Source File
# Begin Source File

SOURCE=..\H\Dosbut.h
# End Source File
# Begin Source File

SOURCE=..\H\Dosdefs.h
# End Source File
# Begin Source File

SOURCE=..\H\Dossier.h
# End Source File
# Begin Source File

SOURCE=..\H\Dplobby.h
# End Source File
# End Group
# Begin Group "E"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\H\Elmt.h
# End Source File
# Begin Source File

SOURCE=..\H\Engine.h
# End Source File
# Begin Source File

SOURCE=..\H\Enumbits.m
# End Source File
# End Group
# Begin Group "F"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\H\Fileman.h
# End Source File
# Begin Source File

SOURCE=..\H\Filing.h
# End Source File
# Begin Source File

SOURCE=.\Filing.h
# End Source File
# Begin Source File

SOURCE=..\H\Filters.h
# End Source File
# Begin Source File

SOURCE=.\Filters.h
# End Source File
# Begin Source File

SOURCE=..\H\flt_task.h
# End Source File
# Begin Source File

SOURCE=.\Flt_Task.h
# End Source File
# Begin Source File

SOURCE=..\H\Flyinit.h
# End Source File
# Begin Source File

SOURCE=..\H\Flymodel.h
# End Source File
# Begin Source File

SOURCE=..\H\Font.h
# End Source File
# Begin Source File

SOURCE=.\Font.h
# End Source File
# Begin Source File

SOURCE=..\H\Fonts.h
# End Source File
# Begin Source File

SOURCE=..\H\Footage.h
# End Source File
# Begin Source File

SOURCE=.\Footage.h
# End Source File
# Begin Source File

SOURCE=..\H\Frag.h
# End Source File
# Begin Source File

SOURCE=.\Frag.h
# End Source File
# Begin Source File

SOURCE=..\H\Fragpilt.h
# End Source File
# Begin Source File

SOURCE=.\FragPilt.h
# End Source File
# Begin Source File

SOURCE=..\H\Frontmap.h
# End Source File
# Begin Source File

SOURCE=..\H\Fullpane.h
# End Source File
# Begin Source File

SOURCE=.\Fullpane.h
# End Source File
# End Group
# Begin Group "G"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\H\Gameset.h
# End Source File
# Begin Source File

SOURCE=..\H\Gear.h
# End Source File
# Begin Source File

SOURCE=..\H\General.h
# End Source File
# Begin Source File

SOURCE=.\General.h
# End Source File
# Begin Source File

SOURCE=..\H\Getset.h
# End Source File
# Begin Source File

SOURCE=..\H\Globdefs.h
# End Source File
# Begin Source File

SOURCE=..\H\globrefs.h
# End Source File
# Begin Source File

SOURCE=..\H\Grndview.h
# End Source File
# Begin Source File

SOURCE=.\Grndview.h
# End Source File
# Begin Source File

SOURCE=..\H\Groupitt.h
# End Source File
# End Group
# Begin Group "H"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\H\Hardpasm.h
# End Source File
# Begin Source File

SOURCE=..\H\Hdata.h
# End Source File
# Begin Source File

SOURCE=..\H\Hdata2.h
# End Source File
# Begin Source File

SOURCE=..\H\Hintbox.h
# End Source File
# Begin Source File

SOURCE=.\Hintbox.h
# End Source File
# Begin Source File

SOURCE=..\H\Hotkeys.h
# End Source File
# End Group
# Begin Group "I"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\H\Imagemap.h
# End Source File
# Begin Source File

SOURCE=..\H\Infoitem.h
# End Source File
# End Group
# Begin Group "J"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\H\Joyconfg.h
# End Source File
# Begin Source File

SOURCE=.\JoyConfg.h
# End Source File
# Begin Source File

SOURCE=..\H\Joyerror.h
# End Source File
# Begin Source File

SOURCE=.\JoyError.h
# End Source File
# End Group
# Begin Group "K"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\H\Keymaps.h
# End Source File
# Begin Source File

SOURCE=..\H\Keytest.h
# End Source File
# End Group
# Begin Group "L"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\H\Landscap.h
# End Source File
# Begin Source File

SOURCE=..\H\Lbm.h
# End Source File
# Begin Source File

SOURCE=..\H\Lbmcpp.h
# End Source File
# Begin Source File

SOURCE=..\H\Lghtshad.h
# End Source File
# Begin Source File

SOURCE=..\H\Libdefs.h
# End Source File
# Begin Source File

SOURCE=..\H\Link.h
# End Source File
# Begin Source File

SOURCE=..\H\Listbx.h
# End Source File
# Begin Source File

SOURCE=.\Listbx.h
# End Source File
# Begin Source File

SOURCE=..\H\Lnchrdat.h
# End Source File
# Begin Source File

SOURCE=..\H\Load.h
# End Source File
# Begin Source File

SOURCE=.\Load.h
# End Source File
# Begin Source File

SOURCE=..\H\Loadprof.h
# End Source File
# Begin Source File

SOURCE=.\Loadprof.h
# End Source File
# Begin Source File

SOURCE=..\H\Locker.h
# End Source File
# Begin Source File

SOURCE=.\Locker.h
# End Source File
# Begin Source File

SOURCE=..\H\Lstmsnlg.h
# End Source File
# Begin Source File

SOURCE=.\Lstmsnlg.h
# End Source File
# Begin Source File

SOURCE=..\H\Lstream.h
# End Source File
# End Group
# Begin Group "M"

# PROP Default_Filter ""
# Begin Group "Mstub"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Maintbar.h
# End Source File
# Begin Source File

SOURCE=.\MapFltrs.h
# End Source File
# Begin Source File

SOURCE=.\Misn_log.h
# End Source File
# Begin Source File

SOURCE=.\Misntext.h
# End Source File
# Begin Source File

SOURCE=.\Missfldr.h
# End Source File
# Begin Source File

SOURCE=.\Msctlbr.h
# End Source File
# Begin Source File

SOURCE=.\MTChild.h
# End Source File
# End Group
# Begin Group "MY"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\H\Myangles.h
# End Source File
# Begin Source File

SOURCE=..\H\Myerror.h
# End Source File
# Begin Source File

SOURCE=..\H\Mymath.h
# End Source File
# Begin Source File

SOURCE=..\H\Mystack.h
# End Source File
# Begin Source File

SOURCE=..\H\Mytime.h
# End Source File
# Begin Source File

SOURCE=..\H\Myvector.h
# End Source File
# End Group
# Begin Group "Mig"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\H\Mig.h
# End Source File
# Begin Source File

SOURCE=..\H\Migdoc.h
# End Source File
# Begin Source File

SOURCE=..\H\Migview.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\H\Mainfrm.h
# End Source File
# Begin Source File

SOURCE=..\H\maintbar.h
# End Source File
# Begin Source File

SOURCE=..\H\Makebf.h
# End Source File
# Begin Source File

SOURCE=..\H\MapDlg.h
# End Source File
# Begin Source File

SOURCE=..\H\Mapfltrs.h
# End Source File
# Begin Source File

SOURCE=..\H\Mathasm.h
# End Source File
# Begin Source File

SOURCE=..\H\Matrix.h
# End Source File
# Begin Source File

SOURCE=..\H\Messages.h
# End Source File
# Begin Source File

SOURCE=..\H\Messengn.h
# End Source File
# Begin Source File

SOURCE=..\H\Migland.h
# End Source File
# Begin Source File

SOURCE=..\H\Miles.h
# End Source File
# Begin Source File

SOURCE=..\H\Milesxtr.h
# End Source File
# Begin Source File

SOURCE=..\H\Misn_log.h
# End Source File
# Begin Source File

SOURCE=..\H\Misntext.h
# End Source File
# Begin Source File

SOURCE=..\H\missfldr.h
# End Source File
# Begin Source File

SOURCE=..\H\Missman2.h
# End Source File
# Begin Source File

SOURCE=..\H\Misssub.h
# End Source File
# Begin Source File

SOURCE=..\H\Model.h
# End Source File
# Begin Source File

SOURCE=..\H\Modfile.h
# End Source File
# Begin Source File

SOURCE=..\H\Modinst.h
# End Source File
# Begin Source File

SOURCE=..\H\Modint.h
# End Source File
# Begin Source File

SOURCE=..\H\Modvec.h
# End Source File
# Begin Source File

SOURCE=..\H\Monotxt.h
# End Source File
# Begin Source File

SOURCE=..\H\Mouse.h
# End Source File
# Begin Source File

SOURCE=..\H\Movement.h
# End Source File
# Begin Source File

SOURCE=..\H\Mresult.h
# End Source File
# Begin Source File

SOURCE=.\MResult.h
# End Source File
# Begin Source File

SOURCE=..\H\Mscdex.h
# End Source File
# Begin Source File

SOURCE=..\H\Msctlbr.h
# End Source File
# Begin Source File

SOURCE=..\H\Msn_ctrl.h
# End Source File
# Begin Source File

SOURCE=..\H\Msndebrf.h
# End Source File
# Begin Source File

SOURCE=.\Msndebrf.h
# End Source File
# Begin Source File

SOURCE=..\H\Mssw.h
# End Source File
# Begin Source File

SOURCE=..\H\Mtchild.h
# End Source File
# End Group
# Begin Group "N"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\H\Node.h
# End Source File
# Begin Source File

SOURCE=..\H\Nose_art.h
# End Source File
# Begin Source File

SOURCE=.\Nose_art.h
# End Source File
# Begin Source File

SOURCE=..\H\Notes.h
# End Source File
# Begin Source File

SOURCE=.\Notes.h
# End Source File
# End Group
# Begin Group "O"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\H\Overlay.h
# End Source File
# Begin Source File

SOURCE=..\H\Overview.h
# End Source File
# Begin Source File

SOURCE=.\Overview.h
# End Source File
# End Group
# Begin Group "P"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\H\package.h
# End Source File
# Begin Source File

SOURCE=..\H\Paint.h
# End Source File
# Begin Source File

SOURCE=.\Paint.h
# End Source File
# Begin Source File

SOURCE=..\H\Palette.h
# End Source File
# Begin Source File

SOURCE=..\H\Payload.h
# End Source File
# Begin Source File

SOURCE=.\Payload.h
# End Source File
# Begin Source File

SOURCE=..\H\Personal.h
# End Source File
# Begin Source File

SOURCE=.\personal.h
# End Source File
# Begin Source File

SOURCE=..\H\Persons2.h
# End Source File
# Begin Source File

SOURCE=..\H\Picture.h
# End Source File
# Begin Source File

SOURCE=.\picture.h
# End Source File
# Begin Source File

SOURCE=..\H\Pilots.h
# End Source File
# Begin Source File

SOURCE=.\Pilots.h
# End Source File
# Begin Source File

SOURCE=..\H\Planetyp.h
# End Source File
# Begin Source File

SOURCE=..\H\Plyr_log.h
# End Source File
# Begin Source File

SOURCE=.\Plyr_log.h
# End Source File
# Begin Source File

SOURCE=..\H\Polygon.h
# End Source File
# Begin Source File

SOURCE=..\H\Prof.h
# End Source File
# Begin Source File

SOURCE=..\H\Prof_lib.h
# End Source File
# Begin Source File

SOURCE=.\Prof_lib.h
# End Source File
# Begin Source File

SOURCE=..\H\profile.h
# End Source File
# Begin Source File

SOURCE=.\Profile.h
# End Source File
# End Group
# Begin Group "Q"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\H\Quikmisn.h
# End Source File
# Begin Source File

SOURCE=.\Quikmisn.h
# End Source File
# End Group
# Begin Group "R"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\H\rad.h
# End Source File
# Begin Source File

SOURCE=..\H\Radio.h
# End Source File
# Begin Source File

SOURCE=.\Radio.h
# End Source File
# Begin Source File

SOURCE=..\H\Ranges.h
# End Source File
# Begin Source File

SOURCE=..\H\Rbutton.h
# End Source File
# Begin Source File

SOURCE=.\rbutton.h
# End Source File
# Begin Source File

SOURCE=..\H\Rchatter.h
# End Source File
# Begin Source File

SOURCE=..\H\Rchatxtr.h
# End Source File
# Begin Source File

SOURCE=..\H\Rcombo.h
# End Source File
# Begin Source File

SOURCE=.\rcombo.h
# End Source File
# Begin Source File

SOURCE=..\H\RComboX.h
# End Source File
# Begin Source File

SOURCE=.\RComboX.h
# End Source File
# Begin Source File

SOURCE=..\H\Rcstmbtn.h
# End Source File
# Begin Source File

SOURCE=.\Rcstmbtn.h
# End Source File
# Begin Source File

SOURCE=..\H\Rdemptyd.h
# End Source File
# Begin Source File

SOURCE=.\RDEmptyD.h
# End Source File
# Begin Source File

SOURCE=..\H\Rdemptyp.h
# End Source File
# Begin Source File

SOURCE=.\RDEmptyP.h
# End Source File
# Begin Source File

SOURCE=..\H\Rdialog.h
# End Source File
# Begin Source File

SOURCE=..\H\rdlgbar.h
# End Source File
# Begin Source File

SOURCE=..\H\Ready.h
# End Source File
# Begin Source File

SOURCE=.\Ready.h
# End Source File
# Begin Source File

SOURCE=..\H\redit.h
# End Source File
# Begin Source File

SOURCE=.\Redit.h
# End Source File
# Begin Source File

SOURCE=..\H\redtbt.h
# End Source File
# Begin Source File

SOURCE=.\Redtbt.h
# End Source File
# Begin Source File

SOURCE=..\H\Replay.h
# End Source File
# Begin Source File

SOURCE=..\H\Rip_list.h
# End Source File
# Begin Source File

SOURCE=.\RIP_List.h
# End Source File
# Begin Source File

SOURCE=..\H\Rjoycfg.h
# End Source File
# Begin Source File

SOURCE=.\rjoycfg.h
# End Source File
# Begin Source File

SOURCE=..\H\rlistbox.h
# End Source File
# Begin Source File

SOURCE=.\rlistbox.h
# End Source File
# Begin Source File

SOURCE=..\H\Rmdldlg.h
# End Source File
# Begin Source File

SOURCE=.\Rmdldlg.h
# End Source File
# Begin Source File

SOURCE=..\H\Route.h
# End Source File
# Begin Source File

SOURCE=.\Route.h
# End Source File
# Begin Source File

SOURCE=..\H\Rowtasks.h
# End Source File
# Begin Source File

SOURCE=.\RowTasks.h
# End Source File
# Begin Source File

SOURCE=..\H\Rradio.h
# End Source File
# Begin Source File

SOURCE=.\Rradio.h
# End Source File
# Begin Source File

SOURCE=..\H\Rscrlbar.h
# End Source File
# Begin Source File

SOURCE=.\rscrlbar.h
# End Source File
# Begin Source File

SOURCE=..\H\Rsheets.h
# End Source File
# Begin Source File

SOURCE=..\H\Rspinbut.h
# End Source File
# Begin Source File

SOURCE=.\Rspinbut.h
# End Source File
# Begin Source File

SOURCE=..\H\Rspltbar.h
# End Source File
# Begin Source File

SOURCE=.\Rspltbar.h
# End Source File
# Begin Source File

SOURCE=..\H\Rstatic.h
# End Source File
# Begin Source File

SOURCE=.\rstatic.h
# End Source File
# Begin Source File

SOURCE=..\H\Rtabs.h
# End Source File
# Begin Source File

SOURCE=.\Rtabs.h
# End Source File
# Begin Source File

SOURCE=..\H\Rtest1.h
# End Source File
# Begin Source File

SOURCE=..\H\Rtestsh1.h
# End Source File
# Begin Source File

SOURCE=..\H\Rtickbox.h
# End Source File
# Begin Source File

SOURCE=.\Rtickbox.h
# End Source File
# Begin Source File

SOURCE=..\H\Rtitle.h
# End Source File
# Begin Source File

SOURCE=..\H\Rtoolbar.h
# End Source File
# Begin Source File

SOURCE=.\Rtoolbar.h
# End Source File
# End Group
# Begin Group "S"

# PROP Default_Filter ""
# Begin Group "Sstub"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Sairclms.h
# End Source File
# Begin Source File

SOURCE=.\Saveprof.h
# End Source File
# Begin Source File

SOURCE=.\Saverep.h
# End Source File
# Begin Source File

SOURCE=.\Scalebar.h
# End Source File
# Begin Source File

SOURCE=.\Scamp.h
# End Source File
# Begin Source File

SOURCE=.\Scontrol.h
# End Source File
# Begin Source File

SOURCE=.\Sdetail.h
# End Source File
# Begin Source File

SOURCE=.\Selects.h
# End Source File
# Begin Source File

SOURCE=.\service.h
# End Source File
# Begin Source File

SOURCE=.\session.h
# End Source File
# Begin Source File

SOURCE=.\Sgame.h
# End Source File
# Begin Source File

SOURCE=.\Sgrdclms.h
# End Source File
# Begin Source File

SOURCE=.\Smkdlg.h
# End Source File
# Begin Source File

SOURCE=.\Sqdnlb.h
# End Source File
# Begin Source File

SOURCE=.\Sqdnlbut.h
# End Source File
# Begin Source File

SOURCE=.\Sqdnlist.h
# End Source File
# Begin Source File

SOURCE=.\Squads.h
# End Source File
# Begin Source File

SOURCE=.\Squick1.h
# End Source File
# Begin Source File

SOURCE=.\Squick2.h
# End Source File
# Begin Source File

SOURCE=.\Squickp.h
# End Source File
# Begin Source File

SOURCE=.\Squickun.h
# End Source File
# Begin Source File

SOURCE=.\Sqview.h
# End Source File
# Begin Source File

SOURCE=.\Ssound.h
# End Source File
# Begin Source File

SOURCE=.\Stitle.h
# End Source File
# Begin Source File

SOURCE=.\Strike.h
# End Source File
# Begin Source File

SOURCE=.\Supply.h
# End Source File
# Begin Source File

SOURCE=.\Sviewer.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\H\Sairclms.h
# End Source File
# Begin Source File

SOURCE=..\H\Savegame.h
# End Source File
# Begin Source File

SOURCE=..\H\Saveprof.h
# End Source File
# Begin Source File

SOURCE=..\H\Saverep.h
# End Source File
# Begin Source File

SOURCE=..\H\Scalebar.h
# End Source File
# Begin Source File

SOURCE=..\H\Scamp.h
# End Source File
# Begin Source File

SOURCE=..\H\Scontrol.h
# End Source File
# Begin Source File

SOURCE=..\H\Screenxy.h
# End Source File
# Begin Source File

SOURCE=..\H\Sdetail.h
# End Source File
# Begin Source File

SOURCE=..\H\Selects.h
# End Source File
# Begin Source File

SOURCE=..\H\Service.h
# End Source File
# Begin Source File

SOURCE=..\H\Session.h
# End Source File
# Begin Source File

SOURCE=..\H\Sflight.h
# End Source File
# Begin Source File

SOURCE=.\Sflight.h
# End Source File
# Begin Source File

SOURCE=..\H\Sfman.h
# End Source File
# Begin Source File

SOURCE=..\H\Sg2combo.h
# End Source File
# Begin Source File

SOURCE=..\H\Sgame.h
# End Source File
# Begin Source File

SOURCE=..\H\Sgrdclms.h
# End Source File
# Begin Source File

SOURCE=..\H\Shapenam.h
# End Source File
# Begin Source File

SOURCE=..\H\Shapes.h
# End Source File
# Begin Source File

SOURCE=..\H\Shpbld.h
# End Source File
# Begin Source File

SOURCE=..\H\Shpinstr.h
# End Source File
# Begin Source File

SOURCE=..\H\Shpweap.h
# End Source File
# Begin Source File

SOURCE=..\H\Sky.h
# End Source File
# Begin Source File

SOURCE=..\H\Smack.h
# End Source File
# Begin Source File

SOURCE=..\H\Smkdlg.h
# End Source File
# Begin Source File

SOURCE=..\H\Sndfonts.h
# End Source File
# Begin Source File

SOURCE=..\H\Speed.h
# End Source File
# Begin Source File

SOURCE=..\H\Sqdnlb.h
# End Source File
# Begin Source File

SOURCE=..\H\Sqdnlbut.h
# End Source File
# Begin Source File

SOURCE=..\H\Sqdnlist.h
# End Source File
# Begin Source File

SOURCE=..\H\Squads.h
# End Source File
# Begin Source File

SOURCE=..\h\SQUICK1.H
# End Source File
# Begin Source File

SOURCE=..\H\Squick2.h
# End Source File
# Begin Source File

SOURCE=..\H\Squickp.h
# End Source File
# Begin Source File

SOURCE=..\H\Squickun.h
# End Source File
# Begin Source File

SOURCE=..\H\Sqview.h
# End Source File
# Begin Source File

SOURCE=..\H\Sreplay.h
# End Source File
# Begin Source File

SOURCE=.\Sreplay.h
# End Source File
# Begin Source File

SOURCE=..\H\Ssound.h
# End Source File
# Begin Source File

SOURCE=..\H\Stack.h
# End Source File
# Begin Source File

SOURCE=..\H\Stdafx.h
# End Source File
# Begin Source File

SOURCE=..\H\Stitle.h
# End Source File
# Begin Source File

SOURCE=.\Stores.h
# End Source File
# Begin Source File

SOURCE=..\H\Strike.h
# End Source File
# Begin Source File

SOURCE=..\H\Stub.m
# End Source File
# Begin Source File

SOURCE=..\H\Stub3d.h
# End Source File
# Begin Source File

SOURCE=..\H\Supply.h
# End Source File
# Begin Source File

SOURCE=..\H\Sviewer.h
# End Source File
# Begin Source File

SOURCE=..\H\Sw_error.hpp
# End Source File
# Begin Source File

SOURCE=..\H\Sw_force.h
# End Source File
# Begin Source File

SOURCE=..\H\Sw_guid.hpp
# End Source File
# Begin Source File

SOURCE=..\H\sysbox.h
# End Source File
# End Group
# Begin Group "T"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\H\Targets.h
# End Source File
# Begin Source File

SOURCE=..\H\Task.h
# End Source File
# Begin Source File

SOURCE=.\Task.h
# End Source File
# Begin Source File

SOURCE=..\H\Tasktabs.h
# End Source File
# Begin Source File

SOURCE=.\Tasktabs.h
# End Source File
# Begin Source File

SOURCE=..\H\Text.h
# End Source File
# Begin Source File

SOURCE=..\H\Textfixd.h
# End Source File
# Begin Source File

SOURCE=..\H\Textref.h
# End Source File
# Begin Source File

SOURCE=..\H\Textrefl.h
# End Source File
# Begin Source File

SOURCE=..\H\Tga.h
# End Source File
# Begin Source File

SOURCE=..\H\thumnail.h
# End Source File
# Begin Source File

SOURCE=..\H\Tilemake.h
# End Source File
# Begin Source File

SOURCE=..\H\Title.h
# End Source File
# Begin Source File

SOURCE=.\Title.h
# End Source File
# Begin Source File

SOURCE=..\H\Titlebar.h
# End Source File
# Begin Source File

SOURCE=.\Titlebar.h
# End Source File
# Begin Source File

SOURCE=..\H\Traffic.h
# End Source File
# Begin Source File

SOURCE=.\Traffic.h
# End Source File
# Begin Source File

SOURCE=..\H\Transite.h
# End Source File
# Begin Source File

SOURCE=..\H\Tstatic.h
# End Source File
# End Group
# Begin Group "U"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\H\Ui.h
# End Source File
# Begin Source File

SOURCE=..\H\Uniqueid.h
# End Source File
# Begin Source File

SOURCE=..\H\Userinst.h
# End Source File
# Begin Source File

SOURCE=.\Userinst.h
# End Source File
# End Group
# Begin Group "V"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\H\Variants.h
# End Source File
# Begin Source File

SOURCE=.\Variants.h
# End Source File
# Begin Source File

SOURCE=..\H\Vector.h
# End Source File
# Begin Source File

SOURCE=..\H\Vertex.h
# End Source File
# Begin Source File

SOURCE=..\H\Viewsel.h
# End Source File
# Begin Source File

SOURCE=..\H\Visitors.h
# End Source File
# Begin Source File

SOURCE=.\Visitors.h
# End Source File
# Begin Source File

SOURCE=..\H\Vwqlist.h
# End Source File
# Begin Source File

SOURCE=.\Vwqlist.h
# End Source File
# End Group
# Begin Group "W"

# PROP Default_Filter ""
# Begin Group "Wstub"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Waveins.h
# End Source File
# Begin Source File

SOURCE=.\Weapons.h
# End Source File
# Begin Source File

SOURCE=.\Weather.h
# End Source File
# Begin Source File

SOURCE=.\WPaaa.h
# End Source File
# Begin Source File

SOURCE=.\WPAir.h
# End Source File
# Begin Source File

SOURCE=.\Wpdetail.h
# End Source File
# Begin Source File

SOURCE=.\WPGround.h
# End Source File
# Begin Source File

SOURCE=.\WPShare.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\H\Wail.h
# End Source File
# Begin Source File

SOURCE=..\H\Wave.h
# End Source File
# Begin Source File

SOURCE=..\H\Waveins.h
# End Source File
# Begin Source File

SOURCE=..\H\WaveTabs.h
# End Source File
# Begin Source File

SOURCE=..\H\Weapons.h
# End Source File
# Begin Source File

SOURCE=..\H\Weappak.h
# End Source File
# Begin Source File

SOURCE=..\H\Weather.h
# End Source File
# Begin Source File

SOURCE=..\H\Win3d.h
# End Source File
# Begin Source File

SOURCE=..\H\Winfile.h
# End Source File
# Begin Source File

SOURCE=..\H\Winmain.h
# End Source File
# Begin Source File

SOURCE=..\H\Winmove.h
# End Source File
# Begin Source File

SOURCE=..\H\World.h
# End Source File
# Begin Source File

SOURCE=..\H\Worldinc.h
# End Source File
# Begin Source File

SOURCE=..\H\Wpaaa.h
# End Source File
# Begin Source File

SOURCE=..\H\Wpair.h
# End Source File
# Begin Source File

SOURCE=..\H\Wpbut.h
# End Source File
# Begin Source File

SOURCE=.\WPBut.h
# End Source File
# Begin Source File

SOURCE=..\H\Wpdetail.h
# End Source File
# Begin Source File

SOURCE=..\H\Wpground.h
# End Source File
# Begin Source File

SOURCE=..\H\wpshare.h
# End Source File
# End Group
# Begin Group "__"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\H\_3d.h
# End Source File
# Begin Source File

SOURCE=..\H\_ai.h
# End Source File
# Begin Source File

SOURCE=..\H\_airc.h
# End Source File
# Begin Source File

SOURCE=..\H\_bfie.h
# End Source File
# Begin Source File

SOURCE=..\H\_comm.h
# End Source File
# Begin Source File

SOURCE=..\H\_file.h
# End Source File
# Begin Source File

SOURCE=..\H\_gene.h
# End Source File
# Begin Source File

SOURCE=..\H\_grap.h
# End Source File
# Begin Source File

SOURCE=..\H\_hard.h
# End Source File
# Begin Source File

SOURCE=..\H\_inpu.h
# End Source File
# Begin Source File

SOURCE=..\H\_math.h
# End Source File
# Begin Source File

SOURCE=..\H\_mfc.h
# End Source File
# Begin Source File

SOURCE=..\H\_miss.h
# End Source File
# Begin Source File

SOURCE=..\H\_mode.h
# End Source File
# Begin Source File

SOURCE=..\H\_move.h
# End Source File
# Begin Source File

SOURCE=..\H\_text.h
# End Source File
# End Group
# End Group
# Begin Group "Generated Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\H\Addr00.g
# End Source File
# Begin Source File

SOURCE=..\H\Bfrefs.g
# End Source File
# Begin Source File

SOURCE=..\H\Const00.g
# End Source File
# Begin Source File

SOURCE=..\H\Deathnum.g
# End Source File
# Begin Source File

SOURCE=..\H\F_battle.g
# End Source File
# Begin Source File

SOURCE=..\H\F_common.g
# End Source File
# Begin Source File

SOURCE=..\H\F_grafix.g
# End Source File
# Begin Source File

SOURCE=..\H\F_sounds.g
# End Source File
# Begin Source File

SOURCE=..\H\Files.g
# End Source File
# Begin Source File

SOURCE=..\H\Imagemap.g
# End Source File
# Begin Source File

SOURCE=..\H\Offs00.g
# End Source File
# Begin Source File

SOURCE=..\H\Radio.g
# End Source File
# Begin Source File

SOURCE=..\H\Radioxtr.g
# End Source File
# Begin Source File

SOURCE=..\H\Shapenum.g
# End Source File
# Begin Source File

SOURCE=..\H\smktrl.g
# End Source File
# Begin Source File

SOURCE=..\H\Textenum.g
# End Source File
# Begin Source File

SOURCE=..\H\Uidvals.g
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Group "Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\MIG.rc

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Release.rc

!IF  "$(CFG)" == "MIG - Win32 Release"

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# End Group
# Begin Group "BMP (res)"

# PROP Default_Filter ".bmp"
# Begin Source File

SOURCE=.\Res\Airstrip.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\grip.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Image1d.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Image1f.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Image1u.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Tick.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\Arrow.cur
# End Source File
# Begin Source File

SOURCE=.\Arrowcop.cur
# End Source File
# Begin Source File

SOURCE=.\Res\Bitmap9.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Button.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Canclb.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\close.ico
# End Source File
# Begin Source File

SOURCE=.\Res\Close1.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\close1.ico
# End Source File
# Begin Source File

SOURCE=.\Res\gobig.ico
# End Source File
# Begin Source File

SOURCE=.\Res\gonormal.ico
# End Source File
# Begin Source File

SOURCE=.\res\MIG.ico
# End Source File
# Begin Source File

SOURCE=.\res\MIG.rc2
# End Source File
# Begin Source File

SOURCE=.\res\MIGDoc.ico
# End Source File
# Begin Source File

SOURCE=.\Nodrop.cur
# End Source File
# Begin Source File

SOURCE=.\Res\Rspltb.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Toolside.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Tooltop.bmp
# End Source File
# End Group
# Begin Group "Help Files"

# PROP Default_Filter ""
# Begin Group "Source "

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\MakeHelp.bat

!IF  "$(CFG)" == "MIG - Win32 Release"

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\MIG.cnt

!IF  "$(CFG)" == "MIG - Win32 Release"

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\MIG.hpj
USERDEP__MIG_H="$(ProjDir)\hlp\AfxCore.rtf"	

!IF  "$(CFG)" == "MIG - Win32 Release"

# Begin Custom Build - Making help file...
OutDir=\mig\release\exe
ProjDir=.
TargetName=Mig
InputPath=.\hlp\MIG.hpj

"$(OutDir)\$(TargetName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	call $(ProjDir)\makehelp.bat

# End Custom Build

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# Begin Custom Build - Making help file...
OutDir=\mig\debug\ttexe
ProjDir=.
TargetName=Mig
InputPath=.\hlp\MIG.hpj

"$(OutDir)\$(TargetName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd 
	echo call $(ProjDir)\makehelp.bat 
	call $(ProjDir)\makehelp.bat 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Group "RTF"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\hlp\AfxCore.rtf

!IF  "$(CFG)" == "MIG - Win32 Release"

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\AfxOleCl.rtf

!IF  "$(CFG)" == "MIG - Win32 Release"

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Group "BMP (help)"

# PROP Default_Filter ".bmp"
# Begin Source File

SOURCE=.\hlp\AppExit.bmp

!IF  "$(CFG)" == "MIG - Win32 Release"

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\Bullet.bmp

!IF  "$(CFG)" == "MIG - Win32 Release"

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\CurArw2.bmp

!IF  "$(CFG)" == "MIG - Win32 Release"

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\CurArw4.bmp

!IF  "$(CFG)" == "MIG - Win32 Release"

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\CurHelp.bmp

!IF  "$(CFG)" == "MIG - Win32 Release"

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\EditCopy.bmp

!IF  "$(CFG)" == "MIG - Win32 Release"

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\EditCut.bmp

!IF  "$(CFG)" == "MIG - Win32 Release"

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\EditPast.bmp

!IF  "$(CFG)" == "MIG - Win32 Release"

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\EditUndo.bmp

!IF  "$(CFG)" == "MIG - Win32 Release"

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\FileNew.bmp

!IF  "$(CFG)" == "MIG - Win32 Release"

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\FileOpen.bmp

!IF  "$(CFG)" == "MIG - Win32 Release"

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\FilePrnt.bmp

!IF  "$(CFG)" == "MIG - Win32 Release"

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\FileSave.bmp

!IF  "$(CFG)" == "MIG - Win32 Release"

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\HlpSBar.bmp

!IF  "$(CFG)" == "MIG - Win32 Release"

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\HlpTBar.bmp

!IF  "$(CFG)" == "MIG - Win32 Release"

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\RecFirst.bmp

!IF  "$(CFG)" == "MIG - Win32 Release"

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\RecLast.bmp

!IF  "$(CFG)" == "MIG - Win32 Release"

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\RecNext.bmp

!IF  "$(CFG)" == "MIG - Win32 Release"

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\RecPrev.bmp

!IF  "$(CFG)" == "MIG - Win32 Release"

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\Scmax.bmp

!IF  "$(CFG)" == "MIG - Win32 Release"

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\ScMenu.bmp

!IF  "$(CFG)" == "MIG - Win32 Release"

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\Scmin.bmp

!IF  "$(CFG)" == "MIG - Win32 Release"

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Source File

SOURCE=.\MIG.reg

!IF  "$(CFG)" == "MIG - Win32 Release"

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "MIG - Win32 Release"

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Group "Utilities"

# PROP Default_Filter ""
# Begin Group "Add all targets as dependencies of fmake.dep"

# PROP Default_Filter ".dep"
# Begin Source File

SOURCE=..\..\debug\obj\fmake.dep

!IF  "$(CFG)" == "MIG - Win32 Release"

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

USERDEP__FMAKE="\mig\game\keyboard\keyb3d.bin"	"\mig\src\bfieldsm.fil"\
	"\mig\src\mycmds\rowanu.flg"	
# Begin Custom Build - End of utilities
InputPath=..\..\debug\obj\fmake.dep

"..\h\000tools.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd.>..\h\000tools.h

# End Custom Build

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

USERDEP__FMAKE="\mig\game\keyboard\keyb3d.bin"	"\mig\src\bfieldsm.fil"\
	"\mig\src\mycmds\rowanu.flg"	
# Begin Custom Build - End of utilities
InputPath=..\..\debug\obj\fmake.dep

"..\h\000tools.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd.>..\h\000tools.h

# End Custom Build

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

USERDEP__FMAKE="\mig\game\keyboard\keyb3d.bin"	"\mig\src\bfieldsm.fil"\
	"\mig\src\mycmds\rowanu.flg"	
# Begin Custom Build - End of utilities
InputPath=..\..\debug\obj\fmake.dep

"..\h\000tools.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd.>..\h\000tools.h

# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Utility programs generate 1 target"

# PROP Default_Filter ".dep"
# Begin Source File

SOURCE=..\Bfields\Battle.src

!IF  "$(CFG)" == "MIG - Win32 Release"

# Begin Custom Build
InputPath=..\Bfields\Battle.src

"\mig\src\bfieldsl.fil" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	echo release bfields hello!

# End Custom Build

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

USERDEP__BATTL="..\bfields\battle.inc"	"..\bfields\globrefs.txt"\
	"..\bfields\initial.typ"	"..\bfields\mainmig.bfi"	"\mig\debug\exe\makebf.exe"\
	"..\bfields\paths.bfi"	"..\bfields\scramble.inc"	
# Begin Custom Build - Compiling battlefields
InputPath=..\Bfields\Battle.src

"\mig\src\bfieldsm.fil" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	if exist \mig\src\bfieldsm.fil del \mig\src\bfieldsm.fil 
	if exist \mig\src\bferr.txt del \mig\src\bferr.txt 
	start /w /m ..\bfields 
	echo :wait >wait.bat 
	echo delay 1>>wait.bat 
	echo if exist \mig\src\bferr.txt goto end>>wait.bat 
	echo if not exist \mig\src\bfieldsm.fil goto wait>>wait.bat 
	echo :end>>wait.bat 
	wait 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

USERDEP__BATTL="..\bfields\battle.inc"	"..\bfields\globrefs.txt"\
	"..\bfields\initial.typ"	"..\bfields\mainmig.bfi"	"\mig\debug\exe\makebf.exe"\
	"..\bfields\paths.bfi"	"..\bfields\scramble.inc"	
# Begin Custom Build - Compiling battlefields
InputPath=..\Bfields\Battle.src

"\mig\src\bfieldsm.fil" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	if exist \mig\src\bfieldsm.fil del \mig\src\bfieldsm.fil 
	if exist \mig\src\bferr.txt del \mig\src\bferr.txt 
	start /w /m ..\bfields 
	echo :wait >wait.bat 
	echo delay 1>>wait.bat 
	echo if exist \mig\src\bferr.txt goto end>>wait.bat 
	echo if not exist \mig\src\bfieldsm.fil goto wait>>wait.bat 
	echo :end>>wait.bat 
	wait 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# Begin Custom Build
InputPath=..\Bfields\Battle.src

"\mig\src\bfieldsl.fil" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	echo release bfields hello!

# End Custom Build

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

USERDEP__BATTL="..\bfields\battle.inc"	"..\bfields\globrefs.txt"\
	"..\bfields\initial.typ"	"..\bfields\mainmig.bfi"	"\mig\debug\exe\makebf.exe"\
	"..\bfields\paths.bfi"	"..\bfields\scramble.inc"	
# Begin Custom Build - Compiling battlefields
InputPath=..\Bfields\Battle.src

"\mig\src\bfieldsm.fil" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	if exist \mig\src\bfieldsm.fil del \mig\src\bfieldsm.fil 
	if exist \mig\src\bferr.txt del \mig\src\bferr.txt 
	start /w /m ..\bfields 
	echo :wait >wait.bat 
	echo delay 1>>wait.bat 
	echo if exist \mig\src\bferr.txt goto end>>wait.bat 
	echo if not exist \mig\src\bfieldsm.fil goto wait>>wait.bat 
	echo :end>>wait.bat 
	wait 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Master.fil

!IF  "$(CFG)" == "MIG - Win32 Release"

# Begin Custom Build
IntDir=\mig\release\obj
InputPath=..\Master.fil

"$(IntDir)\fmake.dep" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	echo release Fmake2 hello!

# End Custom Build

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

USERDEP__MASTE="..\bfieldsa.fil"	"..\roots.dir"	"..\"	"\mig\src\bfieldsm.fil"\
	"..\textseq.fil"	
# Begin Custom Build - Making file-lists
IntDir=\mig\debug\obj
InputPath=..\Master.fil

"$(IntDir)\fmake.dep" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	start /w /m ..\fmake2 
	echo.>$(IntDir)\fmake.dep 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

USERDEP__MASTE="..\bfieldsa.fil"	"..\roots.dir"	"..\"	"\mig\src\bfieldsm.fil"\
	"..\textseq.fil"	
# Begin Custom Build - Making file-lists
IntDir=\mig\debug\ttobj
InputPath=..\Master.fil

"$(IntDir)\fmake.dep" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	start /w /m ..\fmake2 
	echo.>$(IntDir)\fmake.dep 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# Begin Custom Build
IntDir=\mig\demo\obj
InputPath=..\Master.fil

"$(IntDir)\fmake.dep" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	echo release Fmake2 hello!

# End Custom Build

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

USERDEP__MASTE="..\bfieldsa.fil"	"..\roots.dir"	"..\"	"\mig\src\bfieldsm.fil"\
	"..\textseq.fil"	
# Begin Custom Build - Making file-lists
IntDir=\mig\demodeb\obj
InputPath=..\Master.fil

"$(IntDir)\fmake.dep" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	start /w /m ..\fmake2 
	echo.>$(IntDir)\fmake.dep 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Mycmds\Rowanx.dsm

!IF  "$(CFG)" == "MIG - Win32 Release"

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# Begin Custom Build
InputDir=\mig\Src\Mycmds
InputPath=..\Mycmds\Rowanx.dsm

"$(InputDir)\rowanu.flg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy $(InputPath) $(InputDir)\rowanu.dsm 
	echo Function myname():myname="%initials%":End\
                                                                                                     Function>>$(InputDir)\rowanu.dsm 
	echo Function myname():myname="%initials%":End\
                                                                                                     Function>$(InputDir)\rowanu.flg 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# Begin Custom Build
InputDir=\mig\Src\Mycmds
InputPath=..\Mycmds\Rowanx.dsm

"$(InputDir)\rowanu.dsm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy $(InputPath) $(InputDir)\rowanu.dsm 
	echo Function myname():myname="%initials%":End\
                                                                                                     Function>>$(InputDir)\rowanu.dsm 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# Begin Custom Build
InputDir=\mig\Src\Mycmds
InputPath=..\Mycmds\Rowanx.dsm

"$(InputDir)\rowanu.flg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy $(InputPath) $(InputDir)\rowanu.dsm 
	echo Function myname():myname="%initials%":End\
                                                                                                     Function>>$(InputDir)\rowanu.dsm 
	echo Function myname():myname="%initials%":End\
                                                                                                     Function>$(InputDir)\rowanu.flg 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\Debug\exe\Ukeylist.exe

!IF  "$(CFG)" == "MIG - Win32 Release"

# Begin Custom Build
InputPath=..\..\Debug\exe\Ukeylist.exe

"\mig\game\keyboard\keyb3d.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	echo debug UKeylist hello!

# End Custom Build

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# Begin Custom Build - making keyboard table
InputPath=..\..\Debug\exe\Ukeylist.exe

"\mig\game\keyboard\keyb3d.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	start /w /m $(InputPath) \mig\game\keyboard\keyb3d.bin

# End Custom Build

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# Begin Custom Build - making keyboard table
InputPath=..\..\Debug\exe\Ukeylist.exe

"\mig\game\keyboard\keyb3d.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	start /w /m $(InputPath) \mig\game\keyboard\keyb3d.bin

# End Custom Build

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# Begin Custom Build
InputPath=..\..\Debug\exe\Ukeylist.exe

"\mig\game\keyboard\keyb3d.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	echo debug UKeylist hello!

# End Custom Build

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# Begin Custom Build - making keyboard table
InputPath=..\..\Debug\exe\Ukeylist.exe

"\mig\game\keyboard\keyb3d.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	start /w /m $(InputPath) \mig\game\keyboard\keyb3d.bin

# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "associated files"

# PROP Default_Filter ""
# Begin Source File

SOURCE="..\bfields\battle.inc"
# End Source File
# Begin Source File

SOURCE=..\bfieldsA.fil
# End Source File
# Begin Source File

SOURCE=..\bfieldsM.fil
# End Source File
# Begin Source File

SOURCE="..\bfields\globrefs.txt"
# End Source File
# Begin Source File

SOURCE=..\Bfields\Initial.typ
# End Source File
# Begin Source File

SOURCE=..\..\game\Keyboard\keyb3d.bin
# End Source File
# Begin Source File

SOURCE=..\Bfields\Mainmig.bfi
# End Source File
# Begin Source File

SOURCE=..\Bfields\Makebf.cxx

!IF  "$(CFG)" == "MIG - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MIG - Win32 Demo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\debug\exe\makebf.exe
# End Source File
# Begin Source File

SOURCE=..\Bfields\Paths.bfi
# End Source File
# Begin Source File

SOURCE=..\Roots.dir
# End Source File
# Begin Source File

SOURCE=..\Mycmds\Rowanu.dsm
# End Source File
# Begin Source File

SOURCE=..\Mycmds\rowanu.flg
# End Source File
# Begin Source File

SOURCE=..\Bfields\Scramble.inc
# End Source File
# Begin Source File

SOURCE=..\Textseq.fil
# End Source File
# End Group
# End Group
# Begin Group "Removed stuff"

# PROP Default_Filter ""
# End Group
# Begin Source File

SOURCE=..\..\backup\history.lst
# End Source File
# Begin Source File

SOURCE=..\..\macros.txt
# End Source File
# Begin Source File

SOURCE=..\..\src
# End Source File
# End Target
# End Project
# Section MIG : {4A1E1986-8B31-11D1-A1F0-444553540000}
# 	2:21:DefaultSinkHeaderFile:rtabs.h
# 	2:16:DefaultSinkClass:CRTabs
# End Section
# Section MIG : {C42BAC3D-CA3C-11D1-A1F0-444553540000}
# 	2:21:DefaultSinkHeaderFile:rstatic.h
# 	2:16:DefaultSinkClass:CRStatic
# End Section
# Section MIG : {737CB0C7-B42B-11D1-A1F0-444553540000}
# 	2:5:Class:CRCombo
# 	2:10:HeaderFile:rcombo.h
# 	2:8:ImplFile:rcombo.cpp
# End Section
# Section MIG : {008F23E7-9243-11D1-A1F0-444553540000}
# 	2:5:Class:CRTitle
# 	2:10:HeaderFile:rtitle.h
# 	2:8:ImplFile:rtitle.cpp
# End Section
# Section MIG : {461A1FE1-B81B-11D1-A1F0-444553540000}
# 	2:5:Class:CREdtBt
# 	2:10:HeaderFile:redtbt.h
# 	2:8:ImplFile:redtbt.cpp
# End Section
# Section MIG : {C42BAC3B-CA3C-11D1-A1F0-444553540000}
# 	2:5:Class:CRStatic
# 	2:10:HeaderFile:rstatic.h
# 	2:8:ImplFile:rstatic.cpp
# End Section
# Section MIG : {4A1E1984-8B31-11D1-A1F0-444553540000}
# 	2:5:Class:CRTabs
# 	2:10:HeaderFile:rtabs.h
# 	2:8:ImplFile:rtabs.cpp
# End Section
# Section MIG : {48814009-65AE-11D1-A1F0-444553540000}
# 	2:21:DefaultSinkHeaderFile:rlistbox.h
# 	2:16:DefaultSinkClass:CRListBox
# End Section
# Section MIG : {78918644-A917-11D1-A1F0-444553540000}
# 	2:5:Class:CRButton
# 	2:10:HeaderFile:rbutton.h
# 	2:8:ImplFile:rbutton.cpp
# End Section
# Section MIG : {90B5EDA6-666F-11D1-A1F0-444553540000}
# 	2:5:Class:CRListBox
# 	2:10:HeaderFile:rlistbox.h
# 	2:8:ImplFile:rlistbox.cpp
# End Section
# Section MIG : {0542BF46-88DF-11D1-A1F0-444553540000}
# 	2:21:DefaultSinkHeaderFile:rspltbar.h
# 	2:16:DefaultSinkClass:CRSpltBar
# End Section
# Section MIG : {737CB0C9-B42B-11D1-A1F0-444553540000}
# 	2:21:DefaultSinkHeaderFile:rcombo.h
# 	2:16:DefaultSinkClass:CRCombo
# End Section
