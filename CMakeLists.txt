cmake_minimum_required(VERSION 3.8)
project(asteroid-destroyer)

set(CMAKE_CXX_STANDARD 20)

include_directories(src)
include_directories(src/engine)
include_directories(src/visuals)

# engine
add_library(asteroid-destroyer-engine
        src/engine/Engine.h src/engine/Engine.cpp
        src/engine/Player.h src/engine/Player.cpp
        src/engine/Movable.h src/engine/Vec2.h src/engine/CircleCollider.h src/engine/Asteroid.h src/engine/Bullet.h
        src/engine/Input.h src/engine/Timer.h src/engine/utils.h src/Singleton.h)

add_executable(engine-run-test src/tests/engine-run-test.cpp)

target_link_libraries(engine-run-test asteroid-destroyer-engine)

# visuals
set(CMAKE_WIN32_EXECUTABLE "True")
set(CMAKE_CXX_FLAGS
        "/Wall /std:c++20 /DUNICODE /TP /Zc:__cplusplus /EHs /experimental:module")

add_library(asteroid-destroyer-visuals
        src/visuals/MainWindow.h src/visuals/MainWindow.cpp
        src/visuals/BitmapsManager.h src/visuals/BitmapsManager.cpp
        src/visuals/BaseWindow.h src/visuals/windows_h.h src/visuals/utils.h src/visuals/paths.h src/visuals/BitmapNames.h src/Singleton.h)

add_executable(visuals-run-test src/tests/visuals-run-test.cpp)

find_library(DIRECT2D d2d1)
if (NOT DIRECT2D)
    message(FATAL_ERROR "Could not find Direct2D.")
endif ()

target_link_libraries(visuals-run-test asteroid-destroyer-visuals ${DIRECT2D})

# game
add_executable(asteroid-destroyer src/main.cpp)

target_link_libraries(asteroid-destroyer asteroid-destroyer-engine asteroid-destroyer-visuals ${DIRECT2D})
