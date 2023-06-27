# Ni idea que version sea mejor aca
cmake_minimum_required(VERSION 3.16)

project(Left4Dead
    DESCRIPTION "TP para Taller de Programación 1 1c2023 FIUBA"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

option(DEBUG "Compile in debug mode" OFF)
if (DEBUG)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -ggdb")
endif()
option(TESTING "Build internal testing suite" OFF)

add_subdirectory(src)

if (TESTING)
    add_subdirectory(test)
endif()
