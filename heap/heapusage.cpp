#include "heapusage.hpp"

#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cassert>
#include <algorithm>
#include <new>
#include <fmt/format.h>
#include <locale>

////////////////////////////////////////////////////////////////////////////////
// Keep statistics private
namespace {
  struct Stats {
    std::size_t used{0};
    std::size_t requested{0};
    std::size_t largest{0};
    std::size_t smallest{~0u};
    std::size_t max{0};
    std::size_t requests{0};
    std::size_t deletes{0};
    std::size_t nullDeletes{0};
    std::size_t zeroRequests{0};
    bool        debug{false};
    bool        track{true};
  } heap;
}

std::size_t heapRequests()
{
  return heap.requests;
}

std::size_t heapDeletes()
{
  return heap.deletes;
}

std::size_t heapUsage()
{
  return heap.used;
}

std::size_t heapMax()
{
  return heap.max;
}

////////////////////////////////////////////////////////////////////////////////
void heapStats()
{
  Stats snap{heap};
  heapTracking(false);
  std::puts(fmt::format( std::locale("en_US.UTF-8"), R"(
Heap statistics
---------------
  Current used:     {:L}  Maximum used:    {:L} (bytes)
  Smallest request: {:L}  Largest request: {:L} (bytes)
  Calls to new:     {:L}  Empty new calls: {:L}
  Calls to delete:  {:L}  Empty deletes:   {:L}
)"
  , snap.used
  , snap.max
  , snap.smallest
  , snap.largest
  , snap.requests
  , snap.zeroRequests
  , snap.deletes
  , snap.nullDeletes
  ).c_str());
  heapTracking(true);
}

////////////////////////////////////////////////////////////////////////////////
void heapDebug( bool on )
{
  heap.debug = on;
  std::printf("Heap debugging turned %s\n", (on?"ON":"OFF"));
}

////////////////////////////////////////////////////////////////////////////////
void heapTracking( bool on )
{
  heap.track = on;
}

////////////////////////////////////////////////////////////////////////////////
// replacement of a minimal set of functions:
struct Hidden {
  std::size_t sz{0};
  bool valid{true};
};
void* operator new ( std::size_t sz ) // no inline, required by [replacement.functions]/3
{
  if ( heap.debug and heap.track ) {
    std::printf( "Debug: global op new called, size = %zu\n", sz );
  }

  if ( void* ptr = std::malloc( sz + sizeof( Hidden ) ) ) {

    if( heap.track ) {
      ++heap.requests;
      heap.requested += sz;
      if( sz == 0 ) ++heap.zeroRequests;
      heap.used += sz;
      heap.smallest = std::min(sz,heap.smallest);
      heap.largest  = std::max(sz,heap.largest);
      heap.max      = std::max(heap.used,heap.max);
    }

    // Hide allocated meta-data
    ( static_cast<Hidden*>( ptr ) )->sz = sz;
    ( static_cast<Hidden*>( ptr ) )->valid = true;
    ptr = static_cast<void*>( static_cast<char*>( ptr ) + sizeof( Hidden ) );

    return ptr;
  }

  throw std::bad_alloc{}; // required by [new.delete.single]/3
}

////////////////////////////////////////////////////////////////////////////////
void operator delete ( void* ptr ) noexcept
{
  if( heap.track ) ++heap.deletes;
  if( ptr == nullptr ) {
    if( heap.track ) ++heap.nullDeletes;
    return;
  }

  // Recover hidden size and restore ptr
  ptr = static_cast<void*>( static_cast<char*>( ptr ) - sizeof( Hidden ) );
  if( ( static_cast<Hidden*>( ptr ) )->valid ) {
    std::size_t sz = ( static_cast<Hidden*>( ptr ) )->sz;
    ( static_cast<Hidden*>( ptr ) )->valid = false;

    if( heap.track ) {
      assert( heap.used >= sz );
      heap.used -= sz;
      if ( heap.debug ) {
        std::printf( "Debug: global op delete called, size = %zu\n", sz );
      }
    }
    std::free( ptr );
  } else {
    std::puts("Error: Attempt to delete more than once");
  }
}

////////////////////////////////////////////////////////////////////////////////
// Self-test
#ifdef SELFTEST_HEAPUSAGE
struct Widget {
  uint8_t i{};
  char c[15]{};
};
struct Pixel {
  uint32_t red:8;
  uint32_t grn:8;
  uint32_t blu:8;
};
template<std::size_t W, std::size_t H>
class Image {
  Pixel pel[W*H];
};
#include <string>
#include <cstring>
#include <random>
#include <memory>

using namespace std::literals;
int main(int argc, const char* argv[])
{
  for(int i=1; i<argc; ++i) {
    if(( std::strcmp(argv[i],"-d") == 0 ) or ( std::strcmp(argv[i],"-debug") == 0 )) {
      heapDebug();
    }
  }

  std::printf("sizeof(Widget) = %zu\n", sizeof(Widget));

  [[maybe_unused]]auto p1 = new int{};
  delete p1;

  [[maybe_unused]]auto p2 = new int[10]{}; // guaranteed to call the replacement in C++11
  delete[] p2;

  [[maybe_unused]]auto p3 = new Widget{};

  [[maybe_unused]]auto p4 = new Image<100,100>{};

  [[maybe_unused]]auto p5 = new Widget[1'000]{}; // guaranteed to call the replacement in C++11
  delete[] p5;

  delete p3;
  delete p4;

  heapStats();

  return 0;
}
#endif
