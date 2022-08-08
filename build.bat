@echo off
call build_generic.bat debug cl
call build_generic.bat release cl

rem rem DEBUG
rem echo.
rem call "build/cl"

rem rem DEBUG
rem cp "build\cl.exe" ..
rem cp "build\cl_dbg.exe" ..
