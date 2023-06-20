#ifndef HEAPUSAGE_HPP
#define HEAPUSAGE_HPP

#include <cstddef>

// This module provides for tracking heap size
// requirements of a program by overriding the
// global new and delete functions.

std::size_t heapRequests();
std::size_t heapDeletes();
std::size_t heapUsage(); //< current heap usage
std::size_t heapMax(); //< largest size of the heap ignoring fragmentation
void        heapStats(); //< display all heap statistics
// Turn-on verbose messaging about allocations and deletions
void        heapDebug( bool on = true ); //< turn on display of every new/delete operation
void        heapTracking( bool on );
void        heapLocale( bool on = true );

#endif/*HEAPUSAGE_HPP*/
