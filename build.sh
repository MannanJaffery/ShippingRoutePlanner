#!/bin/bash

g++ -Wall -std=c++17 \
-I"./src" \
-I"/c/Users/PMLS/Downloads/SFML-3.0.0/include" \
-L"/c/Users/PMLS/Downloads/SFML-3.0.0/lib" \
src/DataStructures/LinkedList/LinkedList.cpp \
src/DataStructures/Queue/Queue.cpp \
src/DataStructures/Stack/Stack.cpp \
src/DataStructures/Minheap/Minheap.cpp \
src/DataStructures/Graph/Graph.cpp \
src/Models/RouteData/RouteData.cpp \
src/Models/Port/Port.cpp \
src/Modules/FilesParser/FilesParser.cpp \
src/Graphics/graphics.cpp \
main.cpp \
-lsfml-graphics -lsfml-window -lsfml-system \
-o main.exe
