#include "rinfo.hpp"
#include <fmt/format.h>
#include <cstdint>


////////////////////////////////////////////////////////////////////////////////

uint64_t fillStack(void)
{
  uint64_t stack[STACKSIZE/sizeof(uint64_t)];
  for( auto& v : stack ) v = DEADSTACK;
  auto ptr = reinterpret_cast<uint64_t>(&stack[0]) + 0;
  return ptr;
}

size_t usedStack(void)
{
  uint64_t stack[STACKSIZE/sizeof(uint64_t)];
  size_t i = 0;
  for(; (i < STACKSIZE/sizeof(uint64_t)) and (stack[i] == DEADSTACK); ++i); // expect maybe uninitialized warning
  return STACKSIZE-i*WW;
}

////////////////////////////////////////////////////////////////////////////////

uint64_t fillHeap(uint64_t depth)
{
  depth &= ~(WW-1); // Clear LSB
  auto heap = static_cast<uint64_t*>(std::malloc(depth));
  for( auto i = 0ULL; i < depth/WW; ++i ) heap[i] = DEADHEAP;
  return uint64_t(heap);
}

size_t usedHeap(uint64_t depth)
{
  depth &= ~(WW-1); // Clear LSB
  auto heap = static_cast<uint64_t*>(std::malloc(depth));
  size_t used = 0;
  for( auto i = 0ULL; i < depth/WW; ++i ) used += (heap[i] == DEADHEAP)?0:1;
  return used;
}

////////////////////////////////////////////////////////////////////////////////
#ifdef SELFTEST_RINFO
int main([[maybe_unused]]int argc, [[maybe_unused]]const char* argv[])
{
  fillStack();
  fillHeap();
  //...
  fmt::print("Stack used {} bytes\n", usedStack());
  fmt::print("Heap used {} bytes\n", usedHeap()); // expect maybe uninitialized warning
  return 0;
}
#endif
