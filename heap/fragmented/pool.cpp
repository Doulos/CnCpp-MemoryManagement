// This code tests the Pool class

#include <packet.hpp>
#include <pool.hpp>
#include <random>
#include <fmt/format.h>

Pool<Packet<20>,10> pool1;

int main()
{
  auto pkt1 = pool1.get();
  return 0;
}
