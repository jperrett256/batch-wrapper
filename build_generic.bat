@echo off

if "%1"=="" goto args_error
if "%2"=="" goto args_error
if not "%3"=="" goto args_error

set target=%1
set bat_filename=%2

goto start

:args_error
echo Usage: %0 ^<target^> ^<bat_filename^>
exit /B 1

:start

set build_dir=build/
if not exist "%build_dir%" mkdir "%build_dir%"

set compile_options=/nologo /D_CRT_SECURE_NO_WARNINGS /W4 /wd4100

if %target%==debug goto debug
if %target%==release goto release

echo %0: Did not find '%target%' in available targets.
exit /B 1

rem ---- TARGETS ----
rem DEBUG
:debug

set compile_options=%compile_options% /DDEBUG
call :compile
mv %build_dir%%bat_filename%.exe %build_dir%%bat_filename%_dbg.exe

goto end

rem RELEASE
:release

call :compile

goto end
rem -----------------

rem should not get here
echo ?
exit /B 1

rem --- FUNCTIONS ---
:compile

call cl /D"BAT_FILENAME=L\"%bat_filename%\"" /Fe"%build_dir%%bat_filename%" /Fo"%build_dir%" /Fd"%build_dir%" %compile_options% call_bat.c
echo.

exit /B 0
rem -----------------

:end
