#ifndef POOL_HPP
#define POOL_HPP

#include <cstdint>
#include <bitset>

/// Create a memory pool for POOLDEPTH objects.
//  - `Pool<T>()` creates a pool with no allocated objects.
//  - `get()` returns nullptr if full; otherwise, default construct object
//     in an empty slot and return a pointer.
//  - `put()` returns an object to the pool after calling its destructor.
//  - `count()` returns the current size.

template<typename T, int POOLDEPTH>
struct Pool {
  // Establish reasonable limits
  static_assert( POOLDEPTH > 0 );
  Pool() = default;
  ~Pool() {
    // Search for active elements
    for( size_t i = 0; used.any(); ++i ) {
      assert( i < POOLDEPTH );
      if( used.test(i) ) {
        T* p = reinterpret_cast<T*>(&buffer[i][0]);
        p->~T();
        used.reset(i);
      }
    }
  }
  auto count() const { return used.count(); }
  T* get() {
    if( used.all() ) return nullptr;
    size_t i = 0;
    for( i=0; used.test(i); ++i );
    used.set(i);
    return new (&buffer[i][0]) T{};
  }
  void put(T* p) {
    assert( buffer <= p and p < buffer+POOLDEPTH );
    p->~T();
    used(p-buffer);
  }
private:
  uint8_t buffer[POOLDEPTH][sizeof(T)];
  std::bitset<POOLDEPTH> used{0};
};

#endif/*POOL_HPP*/
