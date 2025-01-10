if [[ "$OSTYPE" == "darwin"* ]]; then
    # macOS specific commands
    echo "Running on macOS"
    g++ -o bin/Exercise_sorting main.cpp -std=c++17
    ./bin/Exercise_sorting
elif [[ "$OSTYPE" == "cygwin" || "$OSTYPE" == "msys" ]]; then
    # Windows specific commands (Cygwin or MinGW)
    echo "Running on Windows"
    g++ -o bin/Exercise_sorting.exe main.cpp -std=c++17
    ./bin/Exercise_sorting.exe
else
    echo "Unknown OS type: $OSTYPE"
    exit 1
fi
