@echo off
start \\migalley\mig\vjhftu >Nul
goto proc_%1
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:proc_
echo Error: First param: UP to upload to network or DOWN to download to your machine
goto end
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:proc_up
echo You have chosen to upload to the network. Press Ctrl Break if a mistake.
pause
if %@files[..\game\frontmap\map*.bmp] gt 255] echo Too many BMP files in frontmap. Will run frontmap batch file to redistribute.
if %@files[..\game\frontmap\map*.bmp] gt 255] pause
if %@files[..\game\frontmap\map*.bmp] gt 255] del ..\game\frbigmap\map*.bmp
if %@files[..\game\frontmap\map*.bmp] gt 255] call frontmap
del \\migalley\mig\game\frontmap\*.bmp
del \\migalley\mig\game\frbigmap\*.bmp
copy ..\game\frontmap\*.* \\migalley\mig\game\frontmap\*.*
copy ..\game\frbigmap\*.* \\migalley\mig\game\frbigmap\*.*
copy frontmap.fil \\migalley\mig\game\frontmap\
copy h\frontmap.h \\migalley\mig\game\frontmap\
copy %@search[%0] \\migalley\mig\game\frontmap\
goto end
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:proc_down
del ..\game\frontmap\*.bmp
del ..\game\frbigmap\*.bmp
copy \\migalley\mig\game\frontmap\*.dir ..\game\frontmap\*.*
copy \\migalley\mig\game\frontmap\*.bmp ..\game\frontmap\*.*
copy \\migalley\mig\game\frbigmap\*.dir ..\game\frbigmap\*.*
copy \\migalley\mig\game\frbigmap\*.bmp ..\game\frbigmap\*.*
copy \\migalley\mig\game\frontmap\frontmap.fil* . 
copy \\migalley\mig\game\frontmap\frontmap.h* h
fmake2
goto end

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:end
