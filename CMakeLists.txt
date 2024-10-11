cmake_minimum_required(VERSION 3.5)
project(hina VERSION 0.0.0.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)
set(PROJECT_SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")
set(PROJECT_BINARY_SOURCE_DIR "${PROJECT_BINARY_DIR}/src")

configure_file(
  "${PROJECT_SOURCE_DIR}/meta/meta.h.in"
  "${PROJECT_BINARY_SOURCE_DIR}/meta/meta.h"
)

add_subdirectory(
  "${PROJECT_SOURCE_DIR}/log"
)

add_executable(
  "${CMAKE_PROJECT_NAME}"
  "${PROJECT_SOURCE_DIR}/main.cpp"
)

target_link_libraries(
  "${CMAKE_PROJECT_NAME}"
  PUBLIC
  log
)

target_include_directories(
  "${CMAKE_PROJECT_NAME}" 
  PUBLIC 
  "${PROJECT_SOURCE_DIR}/log"
)

