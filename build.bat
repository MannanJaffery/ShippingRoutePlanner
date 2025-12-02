@echo off
REM Windows batch build script for OceanRoute Nav

setlocal enabledelayedexpansion

REM Set compiler and flags
set CXX=g++
set CXXFLAGS=-Wall -std=c++17 -g
set INCLUDE_PATH=-I"./src" -I"C:\Users\PMLS\Downloads\SFML-3.0.0-windows-gcc-14.2.0-mingw-64-bit\SFML-3.0.0\include"
set LIB_PATH=-L"C:\Users\PMLS\Downloads\SFML-3.0.0-windows-gcc-14.2.0-mingw-64-bit\SFML-3.0.0\lib"
set LIBS=-lsfml-graphics -lsfml-window -lsfml-system

REM Compile all source files
echo Compiling OceanRoute Nav...
%CXX% %CXXFLAGS% %INCLUDE_PATH% %LIB_PATH% ^
  src/DataStructures/LinkedList/LinkedList.cpp ^
  src/DataStructures/Queue/Queue.cpp ^
  src/DataStructures/Stack/Stack.cpp ^
  src/DataStructures/Minheap/Minheap.cpp ^
  src/DataStructures/Graph/Graph.cpp ^
  src/Models/RouteData/RouteData.cpp ^
  src/Models/Port/Port.cpp ^
  src/Modules/FilesParser/FilesParser.cpp ^
  src/Graphics/graphics.cpp ^
  main.cpp ^
  %LIBS% ^
  -o main.exe

if errorlevel 1 (
    echo Build failed!
    exit /b 1
)

echo Build successful!
echo Running OceanRoute Nav...
main.exe
