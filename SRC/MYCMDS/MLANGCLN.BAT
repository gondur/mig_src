cd
rem if exist resource.h	del	resource.h
if exist resource.h move resource.h ..\mfc\
for %%i in (res\*.*) do	del %%i
for %%i in (*.cur) do del %%i
@echo.>cleaned.flg

