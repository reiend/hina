add_library(log log.cpp)

target_include_directories(
  log
  PUBLIC
  "${PROJECT_BINARY_DIR}/src/meta"
)
