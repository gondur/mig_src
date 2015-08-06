::input is header file to replace
@echo off
echo here...
if not "%1"=="" goto fixone
except (resource.h afxauto.h ) for %i in (*.h) if %@filesize[%i] GT 200 call %0 %i
goto end
:fixone
echo %1
move /q %1 ..\h
echo #ifndef %@name[%1]_INCLUDED>%1
echo #pragma once>>%1
echo #define %@name[%1]_INCLUDED>>%1
echo #include "..\h\%1">>%1
echo #include "%i">>afxauto.h
echo #endif>>%1
:end
