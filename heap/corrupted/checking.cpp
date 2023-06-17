#include <vector>
#include <array>
#include <iostream>

int main()
{
  int i=3;
  int value = 42;

  std::vector<int> vec = {1,2,3};

  try {
    vec.at(i) = value;
  } catch (const std::exception& e) {
    std::cout << "Caught " << e.what() << '\n';
  }

  std::array<int,3> arr={1,2,3};

  try {
    arr.at(i) = value;
  } catch (const std::exception& e) {
    std::cout << "Caught " << e.what() << '\n';
  }

  return 0;
}
