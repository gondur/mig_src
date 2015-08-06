:@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by MIG.HPJ. >hlp\MIG.hm
echo. >>hlp\MIG.hm
echo // Commands (ID_* and IDM_*) >>hlp\MIG.hm
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>hlp\MIG.hm
echo. >>hlp\MIG.hm
echo // Prompts (IDP_*) >>hlp\MIG.hm
makehm IDP_,HIDP_,0x30000 resource.h >>hlp\MIG.hm
echo. >>hlp\MIG.hm
echo // Resources (IDR_*) >>hlp\MIG.hm
makehm IDR_,HIDR_,0x20000 resource.h >>hlp\MIG.hm
echo. >>hlp\MIG.hm
echo // Dialogs (IDD_*) >>hlp\MIG.hm
makehm IDD_,HIDD_,0x20000 resource.h >>hlp\MIG.hm
echo. >>hlp\MIG.hm
echo // Frame Controls (IDW_*) >>hlp\MIG.hm
makehm IDW_,HIDW_,0x50000 resource.h >>hlp\MIG.hm
REM -- Make help for Project MIG


echo Building Win32 Help files
hcw.exe /C /E /M hlp\MIG.hpj
if errorlevel 1 goto :Error
echo not error level 1
if not exist hlp\MIG.hlp goto :Error
echo here
if not exist hlp\MIG.cnt goto :Error
echo here
if exist \mig\Debug\nul copy hlp\MIG.hlp \mig\Debug\exe
echo here
if exist \mig\Debug\nul copy hlp\MIG.cnt \mig\debug\exe
echo here
if exist \mig\Release\nul copy hlp\MIG.hlp \mig\Release\exe
echo here
if exist \mig\Release\nul copy hlp\MIG.cnt \mig\Release\exe
echo.
goto done

:Error
echo hlp\MIG.hpj(1) : error: Problem encountered creating help file

:done
echo.
