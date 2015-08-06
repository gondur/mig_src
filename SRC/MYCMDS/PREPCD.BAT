call setproj mig
cd ..\game\
del *.rst;*.err;*.tmp /sq
del savegame\*.* /yq
del videos\*.* /qy

echo y|c:\windows\net use u: \\migalley\mig

copy /q english\StdProf\dir.dir french\StdProf
copy /q english\StdProf\dir.dir german\StdProf
copy /q english\StdProf\dir.dir italian\StdProf
copy /q english\StdProf\dir.dir spanish\StdProf
copy /q english\Text\dir.dir french\Text
copy /q english\Text\dir.dir german\Text
copy /q english\Text\dir.dir italian\Text
copy /q english\Text\dir.dir spanish\Text

copy /qsu u:\game\english\ english
copy /qsu u:\game\french\ french
copy /qsu u:\game\german\ german
copy /qsu u:\game\italian\ italian
copy /qsu u:\game\spanish\ spanish
copy /q u:\readmes\readme.txt c:\mig\cd
rem copy /q u:\readmes\readme.txt d:\mig\game
copy /q c:\mig\src\h\keymaps.h c:\mig\game\h\

copy /qu c:\mig\controls\release\controls.exe c:\mig\game 
copy /qu c:\mig\controls\hlp\controls.cnt c:\mig\game 
copy /qu c:\mig\controls\hlp\controls.hlp c:\mig\game 
rem copy c:\mig\release\exe\mig.exe d:\mig\game

cd keyboard
except ( dir.dir keyb3d.bin) del *.* /qy
cd -

cd ..\src

call mycmds\makechat english
call mycmds\mergetxt
call mycmds\makechat french
call mycmds\mergetxt
call mycmds\makechat german
call mycmds\mergetxt
call mycmds\makechat italian
call mycmds\mergetxt
call mycmds\makechat spanish
call mycmds\mergetxt
fmake2
