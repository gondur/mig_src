@echo off
if "%1"=="" %0 debug
if "%2"=="" if exist \windows\system\regsvr32.exe %0 %1 \windows\system\regsvr32.exe
if "%2"=="" %0 %1 regsvr32.exe
if "%3"=="" if exist ..\%1\*.ocx %0 %1 %2 \ ..\ 
if "%3"=="" if exist ..\%1*.ocx %0 %1 %2 .\ ..\
if "%3"=="" if exist ..\%1exe\*.ocx %0 %1 %2 .\exe\ ..\
if "%3"=="" if exist ..\%1\exe\*.ocx %0 %1 %2 \exe\ ..\
if "%3"=="" %0 %1 %2 \
if not exist %4%1%3*.ocx echo could not find %4%1%3*.ocx 
echos Registering OCX files in %4%1%3
for %%i in (%4%1%3*.ocx) (echos .^%2 /c /s %%i)
echo Complete!
