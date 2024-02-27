cmake_minimum_required()
project(cpp)
SET (CMAKE_C_COMPILER "clang")
SET (CMAKE_CXX_COMPILER "clang++")
SET (CMAKE_EXPORT_COMPILE_COMMANDS "ON")

# build for windows
if(WIN32)
  set(TARGET "-target x86_64-w64-mingw32")
  set(CMAKE_C_FLAGS "${TARGET}")
  set(CMAKE_CXX_FLAGS "${TARGET} -I$ENV{USERPROFILE}\\scoop\\apps\\mingw-mstorsjo-llvm-ucrt\\17.0.6-20231128\\include\\c++\\v1")
endif()

# build for mac

# build for linux

# run linting before build
set(CMAKE_C_CLANG_TIDY "clang-tidy")
set(CMAKE_CXX_CLANG_TIDY "clang-tidy")

add_executable(main ./src/main.cpp)
