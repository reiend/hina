cmake_minimum_required()

project(cpp)

SET (CMAKE_C_COMPILER "clang")
SET (CMAKE_CXX_COMPILER "clang++")

set(TARGET "-target x86_64-w64-mingw32")
set(CMAKE_ASM_FLAGS "${TARGET}")
set(CMAKE_C_FLAGS "${TARGET}")
set(CMAKE_CXX_FLAGS "${TARGET}")

add_executable(main ./src/main.cpp)
