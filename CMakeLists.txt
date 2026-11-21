cmake_minimum_required(VERSION 3.20)
project(QuantEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # writes build/compile_commands.json so the editor sees the real include paths

add_compile_options(-Wall -Wextra -Wpedantic) 

enable_testing() #switches on CMake's test runner CTest

add_subdirectory(cpp) # this adds a folder to our build system and immediately runs the CMakeLists.txt file inside the cpp file
add_subdirectory(tests)