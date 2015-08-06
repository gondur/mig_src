md ..\shapes >&>nul
copy /qu s:\projects\mig\shapes\*.* ..\shapes
md ..\shapes\shpsrc >&>nul
md ..\shapes\shpdat >&>nul
md ..\shapes\shpani >&>nul

iff "%user"=="ROBERT" then
 	copy /qu s:\projects\mig\shapes\shpsrc\*.asc;*.grp ..\shapes\shpsrc
 	copy /qu s:\projects\mig\shapes\shpdat\*.dat ..\shapes\shpdat
 	copy /qu s:\projects\mig\shapes\shpani\*.vue ..\shapes\shpani
endiff

imgres3 -m -d master.fil -f imagemap.grp -s s:\projects\mig\artsrc
rem imgres2 -m -f imagemap.res
copy /q ..\shapes\shapenum.eol ..\shapes\shapenum.old
shpres2 ..\shapes\shapes.res

iff %?==10 then
	echo Naughty additions in the 'shapes.res' file...
	echo    Press 'CTRL & C'... then 'A' to keep these changes
	echo	    ... you will have to rebuild the game ...
	echo OR...
	echo	Press any other key to continue (you will get this message again)
	echo
	echo (If this message really pisses you off, press 'CTRL & C',
	echo           exit, and type 'CLEARSHP'!

	pause
	copy ..\shapes\shapenum.old ..\shapes\shapenum.eol
 else
 	call fmake2 %&
 	call makemaps %&
 	call mshp %&
 endiff
