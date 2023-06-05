#if __cplusplus < 201402L
#error This code requires C++14 or better.
#endif
#include <memory>
#include <fmt/format.h>

#define VALIDITY(p) fmt::print( "On line {}, {} is {}\n", __LINE__, #p, ( p ? "valid" : "invalid" ) )

class Noisy
{
public:
  Noisy()  { fmt::print( "Constructed noisy\n" ); }
  ~Noisy() { fmt::print( "Destroyed noisy\n" ); }
};

auto func(std::unique_ptr<Noisy>&& p)
{
  fmt::print( "Starting {}\n", __func__ );
  VALIDITY(p);
  fmt::print( "Finished {}\n", __func__ );
  return std::move(p);
}

auto func2() {
  auto ptr = std::unique_ptr<Noisy>{ new Noisy };
  return ptr;
}

int main()
{
  auto p1 = std::make_unique<Noisy>();
  auto p2 = std::unique_ptr<Noisy>{};
  VALIDITY(p1);
  VALIDITY(p2);

  fmt::print( "Transfer to p2\n" );
  p2 = std::move(p1);
  VALIDITY(p1);
  VALIDITY(p2);

  fmt::print( "Transfer to p3\n" );
  auto p3 { std::move(p2) };
  VALIDITY(p2);
  VALIDITY(p3);

  auto p4 = func(std::move(p3));
  VALIDITY(p3);
  VALIDITY(p4);

  {
    auto p5 = func2();
    VALIDITY(p5);
  }

  fmt::print( "Exiting\n" );
  return 0;
}
