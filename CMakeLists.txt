cmake_minimum_required(VERSION 3.20)

project(HeartBeat)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(
    libs/SFML-2.6.2/include
    include
)

link_directories(libs/SFML-2.6.2/lib)

add_executable(HeartBeat
    src/main.cpp
    src/Heart.cpp
    src/AmbientSystem.cpp
)

target_link_libraries(HeartBeat
    sfml-graphics
    sfml-window
    sfml-system
)
