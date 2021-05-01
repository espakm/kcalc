cmake_minimum_required(VERSION 3.13)

project(kcalc
    DESCRIPTION "KCalc - Prefix & Infix Calculator"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(BUILD_SHARED_LIBS OFF)

enable_testing()

add_subdirectory(apps)
add_subdirectory(libs)
add_subdirectory(tests)
