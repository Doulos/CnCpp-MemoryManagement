#ifndef SAMPLE_H
#define SAMPLE_H

  //----------------------------------------------------------------------------
  // Types
  typedef struct {
    uint64_t m_uniqueId;
    uint64_t m_timestamp;
    uint64_t m_value[4];
    uint16_t m_sampleType;
  } sample_t;

  //----------------------------------------------------------------------------
  // Method declarations

  /**
   * @brief Construct sample
   */
  sample_t* SAMPLE_create(void);

  /**
   * @brief Close sample_module
   */
  void SAMPLE_destroy( sample_t* pSample );

  /**
   * @brief Obtain a sample
   */
  int SAMPLE_read( sample_t* this );

#endif/*SAMPLE_H*/

//------------------------------------------------------------------------------
// The end
