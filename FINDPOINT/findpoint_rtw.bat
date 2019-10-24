@echo off

set MATLAB=F:\Program Files\MATLAB\R2018b

cd .

if "%1"=="" ("F:\PROGRA~2\MATLAB\R2018b\bin\win64\gmake"  -f findpoint_rtw.mk all) else ("F:\PROGRA~2\MATLAB\R2018b\bin\win64\gmake"  -f findpoint_rtw.mk %1)
@if errorlevel 1 goto error_exit

exit /B 0

:error_exit
echo The make command returned an error of %errorlevel%
An_error_occurred_during_the_call_to_make
