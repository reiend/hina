cmake_minimum_required(VERSION 3.5)

project(hina VERSION 0.0.0.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

configure_file(./src/cmake.h.in cmake.h)

file(GLOB_RECURSE SOURCE_DIR ./src/*.cpp)
file(GLOB_RECURSE HEADER_DIR ./src/*.h)
file(GLOB_RECURSE CMAKE_HEADER_DIR ./src/*.h.in)

source_group(
  TREE 
  ${CMAKE_SOURCE_DIR} 
  FILES 
  ${SOURCE_DIR}
  ${HEADER_DIR}
  ${CMAKE_HEADER_DIR}
)

add_executable(
  ${CMAKE_PROJECT_NAME}
  ${SOURCE_DIR}
)

target_include_directories(
  ${CMAKE_PROJECT_NAME} 
  PUBLIC 
  ${PROJECT_BINARY_DIR}
)


