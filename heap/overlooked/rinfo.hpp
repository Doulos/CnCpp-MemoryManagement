#ifndef RINFO_HPP
#define RINFO_HPP

#include <cstddef>
#include <cstdint>

#define WW 8 /* sizeof(uint64_t) */
#define KB 1024ULL
#define MB (KB*KB)

#define HEAPSIZE (1*MB)
#define STACKSIZE (1*MB)

#define DEADSTACK 0xD15ea5edDeadBeefULL
#define DEADHEAP  0xAd0beAceBadCab1EULL

// Fill stack with an array of depth STACKSIZE containing DEADSTACK.
// Return byte pointer to bottom of deepest entry. Assumes descending stack.
uint64_t  fillStack(void);

// Return # bytes on stack still occupied with DEADSTACK
size_t usedStack(void);

// Fill stack with an array of depth HEAPSIZE containing DEADHEAP
uint64_t fillHeap(uint64_t depth=HEAPSIZE);

// Return # bytes on stack still occupied with DEADHEAP
size_t usedHeap(uint64_t depth=HEAPSIZE);

#endif/*RINFO_HPP*/
