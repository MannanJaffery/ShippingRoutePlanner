@echo off
cd /d "c:\Users\PMLS\Desktop\ShippingRoutePlanner"
echo Building OceanRoute Nav...
g++ -Wall -std=c++17 ^
  -I"./src" ^
  -I"C:\Users\PMLS\Downloads\SFML-3.0.0-windows-gcc-14.2.0-mingw-64-bit\SFML-3.0.0\include" ^
  -L"C:\Users\PMLS\Downloads\SFML-3.0.0-windows-gcc-14.2.0-mingw-64-bit\SFML-3.0.0\lib" ^
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
  -lsfml-graphics -lsfml-window -lsfml-system ^
  -o main.exe

if %ERRORLEVEL% == 0 (
    echo Build successful!
    echo Running OceanRoute Nav...
    main.exe
) else (
    echo Build failed with errors!
)
pause
