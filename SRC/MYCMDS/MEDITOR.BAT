if "%1"=="" goto dirfiles
if %1==roots goto %1
if exist common.dir pkzip -eXrP %1 @makefile\meditor.res
:dirfiles
echo 14		\mig\src>>roots.dir
if exist roots.old del roots.old
ren roots.dir roots.old
for %i in (@roots.old) if not "%i"=="" call %0 roots %i
copy ..\game\common.dir
copy ..\game\battle.dir
copy ..\game\dir.dir
fmake2
goto end
:roots
if %2==14 		echo %2		\mig\src >>roots.dir
if not %2==14 	echo %2	%3	%4>>roots.dir

:end

