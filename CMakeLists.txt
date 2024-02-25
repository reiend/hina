cmake_minimum_required()
project(cpp)
SET (CMAKE_C_COMPILER "clang")
SET (CMAKE_CXX_COMPILER "clang++")
SET (CMAKE_EXPORT_COMPILE_COMMANDS "ON")
set(CMAKE_C_USE_RESPONSE_FILE_FOR_INCLUDES Off)
set(CMAKE_CXX_USE_RESPONSE_FILE_FOR_INCLUDES Off)

# build for windows
if(WIN32)
  set(TARGET "-target x86_64-w64-mingw32")
  set(CMAKE_C_FLAGS "${TARGET}")
  set(CMAKE_CXX_FLAGS "${TARGET}")
endif()

# build for mac

# build for linux

# run linting before build
set(CMAKE_C_CLANG_TIDY "clang-tidy")
set(CMAKE_CXX_CLANG_TIDY "clang-tidy")


add_executable(main ./src/main.cpp)
