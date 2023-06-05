#include <vector>
#include <array>

int main()
{
  int i=3, j=-1;

  std::vector<int> vec = {1,2,3};

  try {
    vec.at(i) = value;
  } catch (const std::exception& e) {
    std::cout << "Caught " << e.what() << '\n';
  }

  std::arr<int,3> array={1,2,3};

  try {
    arr.at(i) = value;
  } catch (const std::exception& e) {
    std::cout << "Caught " << e.what() << '\n';
  }

  return 0;
}
