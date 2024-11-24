#!/bin/sh

set -e  # Exit immediately on error

echo "Root directory: " $PWD
PROJECT_NAME="Snake"

# Need to set these variables in CMakeLists.txt, to spefify build folder
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR})
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR})
BUILD_FOLDER="./build" 

# CMake to generate build instruction
cmake -S . -B $BUILD_FOLDER

# Clean Only
# cmake --build $BUILD_FOLDER --target clean

# Clean and Build
cmake --build $BUILD_FOLDER --target $PROJECT_NAME --clean-first

echo "The program starts .."

# Run the executable
if [[ "$OSTYPE" == "darwin"* ]] || [[ "$OSTYPE" == "linux"* ]]; then
#MacOSX, Linux
$BUILD_FOLDER/$PROJECT_NAME
else
#Windows
$BUILD_FOLDER/$PROJECT_NAME.exe
fi

echo "The program completed!"


