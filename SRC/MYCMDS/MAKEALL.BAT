@echo off
echo  Making english - can do french german italian spanish
Set Lang=English
set bigbuild=
if NOT "%1" == "" set Lang=%1
if "%#" == "2" set bigbuild=-a

echo y|c:\windows\net use u: \\migalley\mig
fmake2
call mycmds\mergetxt %Lang

md ..\debug
md ..\release
md ..\shapes
del ..\debug\*.* /qsy
del ..\release\*.* /qsy
del ..\game\savegame\*.* /qsy
del ..\game\shpbin\*.bin
del ..\game\shpbin2\*.bin
del ..\game\grpbin\*.bin
del ..\shapes\shapenum.eol
del ..\shapes\shapenum.old
del ..\game\samples\volumes.txt
del ..\game\samples\volumes.bin
del rchatter.fil

del ..\game\stdprof\*.* /qsy
rd ..\game\stdprof
mkdir ..\game\english
mkdir ..\game\french
mkdir ..\game\german
mkdir ..\game\italian
mkdir ..\game\spanish
mkdir ..\game\english\StdProf
mkdir ..\game\french\StdProf
mkdir ..\game\german\StdProf
mkdir ..\game\italian\StdProf
mkdir ..\game\spanish\StdProf
copy ..\game\english\dir.dir /s ..\game\german
copy ..\game\english\dir.dir /s ..\game\french
copy ..\game\english\dir.dir /s ..\game\italian
copy ..\game\english\dir.dir /s ..\game\spanish
copy u:\game\english ..\game\english /su
copy u:\game\french ..\game\french /su
copy u:\game\german ..\game\german /su
copy u:\game\italian ..\game\italian /su
copy u:\game\spanish ..\game\spanish /su


if NOT "%bigbuild"=="" call mycmds\newchat.bat
call mycmds\makechat.bat
call mycmds\mksample.bat
call mycmds\makexmi2.bat
call mycmds\makemile.bat

iff NOT "%bigbuild"=="" then
copy u:\game\ ..\game\ /suq
call UImap down
call landup new
endiff

call mkcntrs.bat %bigbuild
call makeshps.bat %bigbuild
call netart.bat

rem if exist e:\mig\game\landscap\dirtable.bin copy ..\game\landscap\*.bin /c e:\mig\game\landscap\

call mycmds\mergetxt
call mkcntrs.bat
call makeshps.bat

if not exist \mig\backup\history.lst md \mig\backup
if exist \mig\backup\history.lst del /y \mig\backup\*.* 
echo.>\mig\backup\history.lst
