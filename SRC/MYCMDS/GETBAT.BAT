:: Gets battlefields from other machines
:: Param 1 is name of machine to take battlefields from
:: At end, need to do a bfields
::
@echo off
if "%1"=="" echo GETBAT: Copies battlefields from other users.
if "%1"=="" echo parameter 1: user/machine name
if "%1"=="" goto end

goto a_%2
:::::::::::::::::::::::::::::::::::::::::::::::::
:a_

if exist bfields\workers\con goto gottree
echo Setting up user list for first time on this machine...
md  bfields\workers
cd.>bfields\workers\dirlist.txt
for %i in (AIRFIELD BATTLES CHOKES CONVOYS EVENTS FC_BFLDS HR_BFLDS) echo %i>>bfields\workers\dirlist.txt
for %i in (INTRBFLD MIGS NODES RAILAREA ROADAREA SO_BFLDS TB_BFLDS) echo %i>>bfields\workers\dirlist.txt
:gottree

if not exist bfields\workers\con md  bfields\workers
if exist bfields\workers\%1 goto gotuser
echo %1 is a new user. Creating file bfields\workers\%1 and tree bfields\workers\%1.own
cd bfields\workers
cd.>%1
md %1.own
for %i in (@dirlist.txt) md %1.own\%i
cd ..\..
:gotuser

c:\windows\command\start \\%1\not\realy\here.exe >NUL
cd bfields
cd.>difflist.err
echo Searching for updates...
for %i in (@workers\dirlist.txt) (echo %i^for %j in (%i\*.*) if %@fileage[\\%1\share_c\mig\src\bfields\%j] GT %@fileage[%j] echo %j>>difflist.err)
echo Following updates found
type difflist.err
cd ..
if %@filesize[bfields\difflist.err]==0 echo No updates found
if %@filesize[bfields\difflist.err]==0 goto end
echo Updating...
for %i in (@bfields\difflist.err) call %0 %1 testandcopy %i
bfields
goto end
:::::::::::::::::::::::::::::::::::::::::::::::::
:a_testandcopy
set owner=
for %j in (bfields\workers\*.) if not %j==bfields\workers\%1 if exist %j.own\%3 set owner=%j
if not "%owner"=="" echo Cant update %3. Owned by %owner!
if not "%owner"=="" goto end
echo Updating %3
copy /q \\%1\share_c\mig\src\bfields\%3* bfields\%3
touch bfields\%3
cd.>bfields\workers\%1.own\%3
:::::::::::::::::::::::::::::::::::::::::::::::::
:end
