cmake_minimum_required(VERSION 3.16)
project(asteroid-destroyer)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)
include_directories(src/engine)
include_directories(src/graphics)

add_executable(asteroid-destroyer
        src/engine/Engine.cpp
        src/engine/Engine.h src/main.cpp)
