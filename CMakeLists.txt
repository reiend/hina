cmake_minimum_required()

project(cpp)
SET (CMAKE_C_COMPILER "clang.exe")
SET (CMAKE_CXX_COMPILER "clang++.exe")
# set(CMAKE_CXX_USE_RESPONSE_FILE_FOR_INCLUDES Off)

set(CMAKE_C clang-tidy -checks=-*,readability-*)
set(CMAKE_CXX_CLANG_TIDY clang-tidy -checks=-*,readability-*)

if(WIN32)
  set(TARGET "-target x86_64-w64-mingw32")
  set(CMAKE_C_FLAGS "${TARGET}")
  set(CMAKE_CXX_FLAGS "${TARGET}")
endif()

add_executable(main ./src/main.cpp)
