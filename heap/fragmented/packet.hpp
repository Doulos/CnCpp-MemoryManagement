#ifndef PACKET_HPP
#define PACKET_HPP

#include <cstdint>
#include <array>
#include <string>

template<int size>
struct Packet {
  static constexpr const int maxSize = 1u << 20;
  static_assert( size >= 0 );
  static_assert( size <= maxSize );
  uint64_t origin{0};
  uint64_t destination{0};
  std::array<uint8_t,size> data{0};
  std::string to_string();
  Packet(uint64_t origin, uint64_t dest, std::initializer_list<uint8_t> init )
  : origin{ origin }, destination{ dest }
  {
    int i=0;
    for( auto v : init ) {
      if( i >= size ) break;
      data[i++] = v;
    }
  }
  Packet() = default;
  Packet( const Packet& pkt ) = default;
  Packet( Packet&& pkt ) noexcept = default;
  Packet& operator=( const Packet& pkt ) = default;
  Packet& operator=( Packet&& pkt ) noexcept = default;
  ~Packet() noexcept {
    // Cleanup
    for( auto& e : data ) e = '\377';
  }
};

#include <sstream>
#include <iomanip>

template<int size>
std::string Packet<size>::to_string()
{
  static std::ostringstream result{};
  result.str("");
  result
    << "{ "
    << "origin: " << std::to_string(origin) << ", "
    << "destination: " << std::to_string(destination) << ", "
    << "size: " << std::to_string(size) << ", "
    << "data: " << std::hex;
  for( auto d : data ) {
    if( ' ' <= d and d <= '~' ) {
      result << char( d );
    }
    else if ( d == 0 ) {
      result << "\\0";
    }
    else {
      result << "\\x" << int( d );
    }
  }
  result << " }" << std::dec;
  return result.str();
}

#endif/*PACKET_HPP*/
