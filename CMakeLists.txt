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
        src/engine/Input.h src/engine/Timer.h src/engine/Sprite.h src/engine/AsteroidsSpawnDelayer.h
        src/engine/Asteroid.cpp src/engine/AsteroidDebris.cpp src/engine/AsteroidDebris.h src/engine/Animator.h src/engine/Explosion.h src/engine/Explosion.cpp src/engine/AnimatorSequence.h)

# visuals
set(VISUALS-SOURCES
        src/visuals/MainWindow.h src/visuals/MainWindow.cpp
        src/visuals/BitmapsManager.h src/visuals/BitmapsManager.cpp
        src/visuals/BaseWindow.h src/visuals/windows_h.h src/visuals/paths.h src/visuals/BitmapNames.h
        src/visuals/TextWriter.cpp src/visuals/TextWriter.h
        src/visuals/gradientBrushes/LinearGradientBrush1.h src/visuals/gradientBrushes/LinearGradientBrush2.h src/visuals/ExplosionPath.h src/visuals/gradientBrushes/RadialGradientBrush1.h)

# common
set(COMMON-SOURCES src/common/utils.h src/common/Singleton.h src/common/constants.h)

find_library(DIRECT2D d2d1)
if (NOT DIRECT2D)
    message(FATAL_ERROR "Could not find Direct2D.")
endif ()

find_library(DWRITE dwrite)
if (NOT DWRITE)
    message(FATAL_ERROR "Could not find dwrite.lib.")
endif ()

# main game
add_executable(asteroid-destroyer src/main.cpp ${ENGINE-SOURCES} ${VISUALS-SOURCES} ${COMMON-SOURCES})

target_link_libraries(asteroid-destroyer ${DIRECT2D} ${DWRITE})
