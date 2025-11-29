#!/bin/bash

g++ main.cpp \
-I"/c/Users/PMLS/Downloads/SFML-3.0.0/include" \
-L"/c/Users/PMLS/Downloads/SFML-3.0.0/lib" \
-lsfml-graphics -lsfml-window -lsfml-system \
-o main.exe
