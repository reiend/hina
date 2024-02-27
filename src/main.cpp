#include <iostream>

struct Car {
  std::string brand;
  std::string model;
  int year;
};

auto main() -> int {

  const short TOYOTA_YEAR = 2018;
  const short FORD_YEAR = 1969;

  // Allocate memory for Car objects using pointers
  Car *myCar1 = new Car{"Toyota", "Camry", TOYOTA_YEAR};
  Car *myCar2 = new Car{"Ford", "Mustang", FORD_YEAR};

  // Print out information about the cars
  std::cout << "Car 1:" << std::endl;
  std::cout << "Brand: " << myCar1->brand << std::endl;
  std::cout << "Model: " << myCar1->model << std::endl;
  std::cout << "Year: " << myCar1->year << std::endl;

  std::cout << "Car 2:" << std::endl;
  std::cout << "Brand: " << myCar2->brand << std::endl;
  std::cout << "Model: " << myCar2->model << std::endl;
  std::cout << "Year: " << myCar2->year << std::endl;

  // Free memory allocated for Car objects
  delete myCar1;
  delete myCar2;

  std::cout << std::endl;
  system("pause");

  return 0;
}
