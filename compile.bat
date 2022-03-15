@echo off
del "include\video\shader.h"
cd build
make
asteroid.exe
cd ..