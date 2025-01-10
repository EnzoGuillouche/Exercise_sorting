echo "Running on Windows"
@echo off
del bin\Exercise_sorting.exe
g++ -o bin\Exercise_sorting.exe main.cpp -std=c++17
bin\Exercise_sorting.exe
