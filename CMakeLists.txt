cmake_minimum_required(VERSION 3.8)
project(asteroid-destroyer)

set(CMAKE_CXX_STANDARD 20)

include_directories(src)
include_directories(src/engine)
include_directories(src/visuals)

set(CMAKE_WIN32_EXECUTABLE "True")
set(CMAKE_CXX_FLAGS
        "/Wall /std:c++20 /DUNICODE /TP /Zc:__cplusplus /EHs /experimental:module /Zc:preprocessor")

# engine
set(ENGINE-SOURCES
        src/engine/Engine.h src/engine/Engine.cpp
        src/engine/Player.h src/engine/Player.cpp
        src/engine/GameObject.h src/engine/Vec2.h src/engine/CircleCollider.h src/engine/Asteroid.h src/engine/Bullet.h
        src/engine/Input.h src/engine/Timer.h src/engine/Sprite.h)

# visuals
set(VISUALS-SOURCES
        src/visuals/MainWindow.h src/visuals/MainWindow.cpp
        src/visuals/BitmapsManager.h src/visuals/BitmapsManager.cpp
        src/visuals/BaseWindow.h src/visuals/windows_h.h src/visuals/paths.h src/visuals/BitmapNames.h)

# common
set(COMMON-SOURCES src/common/utils.h src/common/Singleton.h)

find_library(DIRECT2D d2d1)
if (NOT DIRECT2D)
    message(FATAL_ERROR "Could not find Direct2D.")
endif ()

# main game
add_executable(asteroid-destroyer src/main.cpp ${ENGINE-SOURCES} ${VISUALS-SOURCES} ${COMMON-SOURCES})

target_link_libraries(asteroid-destroyer ${DIRECT2D})
