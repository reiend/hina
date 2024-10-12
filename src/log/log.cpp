#include "./log.h"

#include <iostream>

#include "cmake.h"

void display_project_meta() {
  std::cout << "hello world";
  std::cout << PROJECT_NAME;
  std::cout << " - v";
  std::cout << PROJECT_VERSION_MAJOR;
  std::cout << ".";
  std::cout << PROJECT_VERSION_MINOR;
  std::cout << ".";
  std::cout << PROJECT_VERSION_PATCH;
  std::cout << ".";
  std::cout << PROJECT_VERSION_TWEAK;
  std::cout << "\n";
  std::cout << "\n";
}
