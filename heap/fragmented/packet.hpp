#ifndef PACKET_HPP
#define PACKET_HPP

#include <cstdint>
#include <array>

template<int size>
struct Packet {
  uint64_t origin{0};
  uint64_t destination{0};
  std::array<uint8_t,size> data{0};
};

#endif/*PACKET_HPP*/
