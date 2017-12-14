@echo off

rmdir /s /q tmpbuild
mkdir tmpbuild
cd tmpbuild
qmake ..\BankClient.pro
mingw32-make -f Makefile.Release
mingw32-make clean
cd release
windeployqt BankClient.exe
cd ..\..
move tmpbuild\release BUILD
rmdir /s /q tmpbuild
