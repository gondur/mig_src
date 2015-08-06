@echo off
iff "%Lang" == "" .AND. "%1" == "" then
echo You must provide a Language for MergeTxt
else
if not "%1"=="" set Lang=%1
Echo MergeTxt using %Lang
copy %Lang%\mig.rc ..\%Lang%mig.rc
set projpath=u:
if not exist %projpath\game\player\*.wav set projpath=u:\mig
if not exist %projpath\game\player\*.wav set projpath=\\migalley\migalley\mig
if not exist %projpath\game\player\*.wav start %projpath\dgfvuyergv>NUL
if not exist %projpath\game\player\*.wav echo STILL CANT FIND PROJPATH=%projpath\game\player\*.wav
echo h\uidvals.g			>%lang%\mergelst.lst
echo mfc\resource.h			>>%lang%\mergelst.lst
echo %Lang%\uidnames.txt	>>%lang%\mergelst.lst
echo %Lang%\mig.rc			>>%lang%\mergelst.lst
echo h\shapenum.g			>>%lang%\mergelst.lst
echo %Lang%\shape_gm.txt	>>%lang%\mergelst.lst
echo h\radio.g				>>%lang%\mergelst.lst
echo h\radtxt.g				>>%lang%\mergelst.lst
echo %projpath\sounds\radio\%Lang%\radmast.res	>>%lang%\mergelst.lst
mergelst @%lang%\mergelst.lst
endiff

