project(hina VERSION 0.0.0.0)

configure_file(cmake.h.in cmake.h)

file(GLOB_RECURSE SOURCE_DIR ./*.cpp)
file(GLOB_RECURSE HEADER_DIR ./*.h)
file(GLOB_RECURSE CMAKE_HEADER_DIR ./*.h.in)

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
