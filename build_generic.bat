@echo off

if "%1"=="" goto args_error
if not "%2"=="" goto args_error

set bat_filename=%1

goto compile

:args_error
echo Expected single argument.
goto end

:compile

set build_dir=build/
if not exist "%build_dir%" mkdir "%build_dir%"

set compile_options=/nologo /D_CRT_SECURE_NO_WARNINGS /W4 /wd4100

call cl /D"BAT_FILENAME=L\"%bat_filename%\"" /Fe"%build_dir%%bat_filename%" /Fo"%build_dir%" /Fd"%build_dir%" %compile_options% call_bat.c
echo.

:end
