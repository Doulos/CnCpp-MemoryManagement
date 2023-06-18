#pragma once

#include <cstdint>
#include <bitset>
#include <array>
#include <cstring> //memset

#ifndef NDEBUG

#include <string>
#include <iostream>
#include <iomanip>

#endif

/// Create a pool for POOLDEPTH objects to avoid the need for using the heap.
//  - `Pool<T,S>()` creates an empty pool sized to contain S objects of type T
//  - `alloc()` returns nullptr if full; otherwise, default construct object in an empty slot and return a pointer.
//  - `alloc(o)` returns nullptr if full; otherwise, move object into an empty slot and return a pointer.
//  - `avail()` returns the number of available slots.
//  - `capacity()` returns the number of slots (available and used).
//  - `cfree(p)` returns an object to the pool after calling its destructor and clearing its data.
//  - `empty()` returns true if all slots are available.
//  - `free(p)` returns an object to the pool after calling its destructor.
//  - `full()` returns true if all slots are in use.
//  - `index(p)` returns the index of an object in the pool. If not in the pool, returns -1.
//  - `is_active(i)` returns true if the index refers to an actively used location
//  - `is_active(p)` returns true if the pointer refers to an actively used location
//  - `is_dirty(p)` returns true if the pointer refers to an entry with non-zero contents
//  - `is_valid(i)` returns true if the index is within the pool
//  - `is_valid(p)` returns true if the pointer is within the pool
//  - `slots()` returns a string with the current usage for debug
//  - `status(s)` streams status information to stdout for debug
//  - `used()` returns the current number of slots in use.
//  - `zero(p)` zeroes all data of an unused object in the pool. This is not the same as resetting the object.
//  - Header-only implementation
//  - Optionally clears contents of objects removed by using `cfree()`
//  - Frees and clears remaining objects when destroyed
//  - Debug features can be suppressed by defining NDEBUG

template< typename T, int POOLDEPTH >
struct Pool {
  // Establish reasonable limits
  static_assert( POOLDEPTH > 0 );

  Pool() // Constructor
  {
    for ( auto& e: m_buffer ) {
      zero( &e );
    }
  }

  ~Pool() // Destructor
  {
    for ( auto& e: m_buffer ) {
      auto p = &e;
      if ( is_active( p ) ) {
        free( p );
      }
      p = &e;
      zero( p );
    }
  }

  // Disallow copying or moving
  Pool( const Pool& ) = delete;
  Pool( Pool&& ) = delete;
  Pool& operator=( const Pool& ) = delete;
  Pool& operator=( Pool&& ) = delete;

  [[nodiscard]] auto full() const
  { return m_used.all(); }

  [[nodiscard]] auto empty() const
  { return not m_used.any(); }

  [[nodiscard]] constexpr auto capacity() const
  { return POOLDEPTH; }

  [[nodiscard]] auto used() const
  { return m_used.count(); }

  [[nodiscard]] auto avail() const
  { return POOLDEPTH - m_used.count(); }

  [[nodiscard]] T* alloc( T o )
  {
    if ( m_used.all() ) { return nullptr; }
    size_t i;
    for ( i = 0; m_used.test( i ); ++i );
    m_used.set( i );
    m_buffer[ i ] = std::move( o );
    return &m_buffer[ i ];
  }

  [[nodiscard]] T* alloc()
  {
    if ( m_used.all() ) { return nullptr; }
    size_t i;
    for ( i = 0; m_used.test( i ); ++i );
    m_used.set( i );
    return new( &m_buffer[ i ] ) T{};
  }

  [[nodiscard]] bool is_valid( int i ) const
  { return i >= 0 and i <= POOLDEPTH; }

  [[nodiscard]] bool is_valid( T* p ) const
  {
    auto within_pool = p != nullptr and &m_buffer[ 0 ] <= p and p <= &m_buffer[ POOLDEPTH - 1 ];
    return within_pool;
  }

  [[nodiscard]] bool is_active( int i ) const
  { return is_valid( i ) and m_used.test( i ); }

  [[nodiscard]] constexpr bool is_active( T* p ) const
  { return is_valid( p ) and m_used.test( index( p ) ); }

  [[nodiscard]] constexpr int index( T* p ) const
  {
    if ( not is_valid( p ) ) { return -1; }
    return p - &m_buffer[ 0 ];
  }

  void zero( T* p )
  {
    if ( is_active( p ) ) {
      return; // don't zero used entries
    }
    memset( p, 0, sizeof( *p ) );
  }

  void free( T*& p )
  {
    if ( p == nullptr ) { return; }
    if ( not is_active( p ) ) { return; } // don't free unused entries
    p->~T();
    m_used.reset( p - &m_buffer[ 0 ] );
    p = nullptr;
  }

  void cfree( T*& p )
  {
    auto z = p;
    free( p );
    zero( z );
  }

  [[nodiscard]] bool is_dirty( int index ) const
  {
    assert( is_valid( index ) );
    auto p = &m_buffer[ index ];
    void* b = ( void* ) p;
    for ( auto i = 0u; i < sizeof( T ); ++i ) {
      if ( static_cast<uint8_t*>(b)[ i ] != 0 ) {
        return true;
      }
    }
    return false;
  }

#ifndef NDEBUG

  [[nodiscard]] std::string slots() const
  {
    std::string result{};
    for ( int i = 0; i < POOLDEPTH; ++i ) {
      result += is_active( i ) ? "U" : is_dirty( i ) ? "*" : "_";
    }
    return result;
  }

  void dump( const std::string& label = "" )
  {
    void* raw = reinterpret_cast<void*>( &m_buffer[ 0 ] );
    std::cout << "Pool buffer ";
    if ( not label.empty() ) { std::cout << label << ' '; }
    std::cout << "dump:\n";
    auto elt_size = sizeof( m_buffer[ 0 ] );
    for ( auto i = 0u; i < sizeof( m_buffer ); ++i ) {
      if ( i % elt_size == 0 ) { std::cout << i / elt_size << ": "; }
      auto c = static_cast<uint8_t*>(raw)[ i ];
      if ( c == '\n' ) { std::cout << "\\n"; }
      else if ( c == '\r' ) { std::cout << "\\r"; }
      else if ( c == '\t' ) { std::cout << "\\t"; }
      else if ( c == 033 ) { std::cout << "\\e"; }
      else if ( c == '\0' ) { std::cout << "•"; }
      else if ( ' ' <= c and c <= '~' ) { std::cout << static_cast<char>(c); }
      else if ( c == '"' ) { std::cout << "\\\""; }
      else { std::cout << "\\x" << std::hex << int( c ); }
      if ( i % elt_size == elt_size - 1 ) { std::cout << '\n'; }
    }
  }

  void status( const std::string& label = "?" ) const
  {
    std::cout
            << "Pool " << label << ":"
            << " used=" << used()
            << " avail=" << avail()
            << " capacity=" << capacity();
    if ( full() ) { std::cout << " (full)"; }
    if ( empty() ) { std::cout << " (empty)"; }
    std::cout
            << " slots: " << slots()
            << std::endl;
  }

#endif
private:
  std::bitset<POOLDEPTH> m_used{ 0 }; // placed first to avoid issues of overflow in buffer
  std::array<T, POOLDEPTH> m_buffer{};
};
