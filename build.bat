@echo off
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"
mkdir build
cd build
cmake -G "Visual Studio 17 2022" ..
msbuild /m /p:Configuration=Release /p:Platform=x64
cd ..
start build\Release\server.exe
