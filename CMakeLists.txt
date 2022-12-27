cmake_minimum_required(VERSION 3.16)
project(asteroid-destroyer)

set(CMAKE_CXX_STANDARD 20)

include_directories(src)
include_directories(src/engine)
include_directories(src/graphics)

add_executable(asteroid-destroyer
        src/main.cpp
        src/engine/Engine.h src/engine/Engine.cpp
        src/engine/Player.h src/engine/Player.cpp
        src/engine/Movable.h src/engine/Vec2.h src/engine/CircleCollider.h src/engine/Asteroid.h src/engine/Bullet.h
        src/engine/Input.h src/engine/Timer.h)

target_link_libraries(asteroid-destroyer -lpthread)