@echo off
set EXENAME=mig
set DEVPTH="c:\program files\devstudio\vc\bin"
set DPTHSH="c:\program files\devstudio\sharedide\bin"
copy /q %DEVPTH\plist.exe m:\
copy /q %DEVPTH\prep.exe m:\
copy /q %DEVPTH\profile.exe m:\
copy /q %DEVPTH\profile.dll m:\
copy /q %DPTHSH\mspdb50.dll m:\
set DEVPTH=
set DPTHSH=
cd ..\game
del ..\debug\obj\profile.lst >&nul
echo path=%path >m:oldpath.bat
set path=%path%;..\src\mycmds;m:\
set init=.
echo [profiler] >tools.ini
echo exclude:kernel32.dll >>tools.ini
echo exclude:user32.dll >>tools.ini
echo exclude:gdi32.dll >>tools.ini
echo exclude:winspool.dll >>tools.ini
echo exclude:comdlg32.dll >>tools.ini
echo exclude:advapi32.dll >>tools.ini
echo exclude:shell32.dll >>tools.ini
echo exclude:ole32.dll  >>tools.ini
echo exclude:oleaut32.dll  >>tools.ini
echo exclude:uuid.dll  >>tools.ini
echo exclude:odbc32.dll  >>tools.ini
echo exclude:odbccp32.dll  >>tools.ini
rem echo exclude:ddraw.dll  >>tools.ini
echo exclude:wail32.dll  >>tools.ini
echo exclude:dplay.dll  >>tools.ini
echo exclude:smackw32.dll  >>tools.ini
echo exclude:winmm.dll  >>tools.ini
echo exclude:analjoy.dll  >>tools.ini
echo exclude:dinput.dll  >>tools.ini
echo exclude:dxguid.dll  >>tools.ini
echo exclude:msvcrtd.dll >>tools.ini
goto %1_A
:_A
echo USAGE:
echo "PROF all - full profile of the executable"
echo "PROF dir <dir name> - profiles all modules from a specified directory"
echo "                      eg. PROF dir 3D"
echo "PROF module <module name> - profiles a single module"
echo "                            eg. PROF dir 3dcode.obj"
goto done

:all_A
prep /om /ft ..\debug\exe\%EXENAME.exe >&nul
if errorlevel == 1 goto done 
goto DonePhaseI

:gamelist_A
dir /b \%EXENAME\src\3d\*.cpp >m:temp1
dir /b \%EXENAME\src\ai\*.cpp >>m:temp1
dir /b \%EXENAME\src\aircraft\*.cpp >>m:temp1
dir /b \%EXENAME\src\bfields\*.cpp >>m:temp1
dir /b \%EXENAME\src\files\*.cpp >>m:temp1
dir /b \%EXENAME\src\graphics\*.cpp >>m:temp1
dir /b \%EXENAME\src\hardware\*.cpp >>m:temp1
dir /b \%EXENAME\src\mfc\*.cpp >>m:temp1
dir /b \%EXENAME\src\model\*.cpp >>m:temp1
dir /b \%EXENAME\src\movecode\*.cpp >>m:temp1
goto gamelistin

:Dir_A
dir /b \%EXENAME\src\%2\*.cpp >m:temp1
:gamelistin
echo /om >prep.res
echo /ft >>prep.res
echo /excall >>prep.res
for %i in (@m:temp1) do echo /inc %@NAME[%i].obj >>prep.res
echo ..\debug\exe\%EXENAME.exe >>prep.res
prep @prep.res
goto DonePhaseI

:hardpoly_A
prep /om /lv /excall /inc win3d.obj(0-0) ..\debug\exe\%EXENAME.exe
goto DonePhaseI

:Module_A
prep /om /ft /excall /inc %2 ..\debug\exe\%EXENAME.exe
:DonePhaseI

profile ..\debug\exe\%EXENAME
if errorlevel == 1 goto done 
prep /m ..\debug\exe\%EXENAME
if errorlevel == 1 goto done 
plist /stc ..\debug\exe\%EXENAME >..\debug\obj\profile.lst
:done
set EXENAME=
set init=
call m:oldpath
del tools.ini >&nul
del m:oldpath.bat >&nul
cd -
if EXIST ..\debug\obj\profile.lst (
 if NOT %@FILESIZE[..\debug\obj\profile.lst,b]=0 (
	copy %bfile m:profile.rst
	if NOT "%USER"=="JIM" set bfile=m:profile.rst
 	call e -m"edit_file ..\debug\obj\profile.lst" -mtop_of_buffer
 	if NOT "%USER"=="JIM" set bfile=%bfiles%
	if exist %bfile% sortrst %bfile%	
 )
 )

