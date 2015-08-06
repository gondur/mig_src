:@echo off
iff "%Lang" == "" .AND. "%1" == "" then
echo You must provide a Language for MakeChat
else
if not "%1"=="" set Lang=%1
Echo MakeChat using %Lang
delete chaterrs.err
set projpath=u:
if not exist %projpath\game\player\*.wav set projpath=u:\mig
if not exist %projpath\game\player\*.wav set projpath=\\migalley\mig
if not exist %projpath\game\player\*.wav start %projpath\dgfvuyergv>NUL
if not exist %projpath\game\player\*.wav echo STILL CANT FIND PROJPATH=%projpath\game\player\*.wav

copy /qu %projpath\game\player\*.wav ..\game\player\
copy /qu %projpath\game\pexcite\*.wav ..\game\pexcite\
copy /qu %projpath\game\other\*.wav ..\game\other\
copy /qu %projpath\game\oexcite\*.wav ..\game\oexcite\
copy /qu %projpath\game\factac0\*.wav ..\game\factac0\
copy /qu %projpath\game\factac1\*.wav ..\game\factac1\
copy /qu %projpath\game\tower0\*.wav ..\game\tower0\
copy /qu %projpath\game\tower1\*.wav ..\game\tower1\
copy /qu %projpath\game\tower2\*.wav ..\game\tower2\
copy /qu %projpath\game\dentist\*.wav ..\game\dentist\

rchatter rchatter.grp places.res -x -d11000 -n -p -i %projpath\sounds\radio\%Lang% -o ..\game\
fmake2
