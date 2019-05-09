cmake_minimum_required(VERSION 3.10)
project(Simple)

set(CMAKE_CXX_STANDARD 17)
# Include Directory
include_directories(../lib/SFML-2.5.1/include/)
include_directories(../lib/Box2D/Box2D/)
#Lib Direcotry
link_directories(../lib/SFML-2.5.1/lib/)
link_directories(../lib/Box2D/cmake-build-debug/)
add_executable(Simple main.cpp)
target_link_libraries(Simple Box2D-cmake sfml-graphics-s-d sfml-window-s-d sfml-audio-s-d sfml-system-s-d)