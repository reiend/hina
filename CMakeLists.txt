cmake_minimum_required(VERSION 3.5)

project(hina VERSION 0.0.0.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

configure_file(./src/cmake.h.in cmake.h)

message(${files})

add_executable(
  ${CMAKE_PROJECT_NAME}
  ./src/main.cpp
  ./src/log/log.cpp
)

target_include_directories(
  ${CMAKE_PROJECT_NAME} 
  PUBLIC 
  ${PROJECT_BINARY_DIR}
)


