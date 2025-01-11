echo "Architecture detected: macOS"
rm -f bin/Exercise_sorting
echo "Compiling..."
g++ -o bin/Exercise_sorting main.cpp -std=c++17
echo "Compilation done. Running..."
./bin/Exercise_sorting
