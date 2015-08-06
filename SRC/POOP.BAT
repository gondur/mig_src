:@echo off
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

mergelst h\uidvals.g mfc\resource.h %Lang%\uidnames.txt %Lang%\mig.rc h\shapenum.g %Lang%\shape_gm.txt h\radio.g h\radtxt.g %projpath\sounds\radio\%Lang%\radmast.res
endiff

