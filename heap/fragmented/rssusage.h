#ifndef RSSUSAGE_H
#define RSSUSAGE_H

#include <stddef.h>

/**
 * Returns the peak (maximum so far) resident set size (physical
 * memory use) measured in bytes, or zero if the value cannot be
 * determined on this OS.
 */
size_t getPeakRSS( void );

/**
 * Returns the current resident set size (physical memory use) measured
 * in bytes, or zero if the value cannot be determined on this OS.
 */
size_t getCurrentRSS( void );

#endif/*RSSUSAGE_H*/
