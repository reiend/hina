#include <iostream>

#include "version.h"

int main() {
  std::cout << "version major - " << VERSION_MAJOR << "\n";
  std::cout << "version minor - " << VERSION_MINOR << "\n";
  std::cout << "version patch - " << VERSION_PATCH << "\n";

  std::cout << "Hello World\n";

  return 0;
}
