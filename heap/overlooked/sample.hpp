#ifndef SAMPLE_HPP
#define SAMPLE_HPP

#include <stdint.h>

struct Sample
{
  uint64_t m_uniqueId;
  uint64_t m_timestamp;
  uint64_t m_value[4];
  uint16_t m_sampleType;
};


#endif/*SAMPLE_HPP*/
