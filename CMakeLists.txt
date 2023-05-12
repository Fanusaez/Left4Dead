# Ni idea que version sea mejor aca
cmake_minimum_required(VERSION 3.16)

project(Left4Dead
    DESCRIPTION "TP para Taller de Programación 1 1c2023 FIUBA"
    LANGUAGES CXX
)

option(TESTING "Build internal testing suite" OFF)

add_subdirectory(src)

if (TESTING)
    add_subdirectory(test)
endif()
