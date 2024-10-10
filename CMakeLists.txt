cmake_minimum_required()
project(hina)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

set(VERSION_MAJOR 0)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)

configure_file(./src/version.h.in version.h)

add_executable(hina ./src/main.cpp)

target_include_directories(hina PUBLIC "${PROJECT_BINARY_DIR}")
