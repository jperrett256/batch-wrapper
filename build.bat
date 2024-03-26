@echo off

echo Building cl.exe
call build_generic.bat debug cl
call build_generic.bat release cl

echo Building clang-cl.exe
call build_generic.bat debug clang-cl
call build_generic.bat release clang-cl

echo Building clang.exe
call build_generic.bat debug clang
call build_generic.bat release clang

echo Building clang++.exe
call build_generic.bat debug clang++
call build_generic.bat release clang++

echo Building link.exe
call build_generic.bat debug link
call build_generic.bat release link

echo Building rc.exe
call build_generic.bat debug rc
call build_generic.bat release rc
