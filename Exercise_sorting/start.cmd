@echo off
echo "Architecture detected: Windows"
del bin\Exercise_sorting.exe
echo "Compiling..."
g++ -o bin\Exercise_sorting.exe main.cpp -std=c++17
echo "Compilation done. Running..."
bin\Exercise_sorting.exe
