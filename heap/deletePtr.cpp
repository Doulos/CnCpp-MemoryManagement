/*
 * Demonstrate creation and deletion of dynamic memory in C++.
 */

#include <iostream>
using namespace std::literals;

int main(int argc, const char* argv[])
{
  std::cout << "Attempt to delete a nullptr\n";
  int* p = nullptr;
  delete p;
  std::cout << "Successfully delete the nullptr\n";

  std::cout << "Attempt to delete a created pointer\n";
  p = new int;
  std::cout << "Points to " << p << "\n";
  delete p;
  std::cout << "Successfully deleted once\n";

  if( argc == 2 and "2"s == argv[1] ) {
    delete p; //< should fail
    std::cout << "Deleted twice!\n";
  }

  std::cout << "Exiting\n";
  return 0;
}
