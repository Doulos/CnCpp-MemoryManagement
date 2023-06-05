#include "sample.h"
#include <stdlib.h>

//------------------------------------------------------------------------------
// Implementation includes

//------------------------------------------------------------------------------
// Local gobals (class static)
static size_t SAMPLE_count = 0;

//------------------------------------------------------------------------------
/**
 * @brief Construct sample
 */
sample_t* SAMPLE_create( void )
{
  sample_t* pSample;
  pSample = (sample_t*)malloc(sizeof(sample_t));
  pSample->m_uniqueId = ++SAMPLE_count;
  return pSample;
}

//------------------------------------------------------------------------------
/**
 * @brief Destruct sample
 */
void SAMPLE_destroy( sample_t* pSample )
{
  //{:BODY:}
}

//------------------------------------------------------------------------------
/**
 * @brief {:IMPLEMENTATION_DETAILS:}
 */
int SAMPLE_read( pSample )
{
  //{:BODY:}
}

//------------------------------------------------------------------------------
// The end
