@echo off
cd S:\projects\mig\artsrc\
cd
copy s:landscap\daypal.pal ..\game\landmaps\
iff "%1"=="newpal" then
	call mlm.bat NewPal
	make45 -s -f makefile\makecntr.mke
else 
	make45 -s -f makefile\makecntr.mke %&
endiff
call mlm.bat
