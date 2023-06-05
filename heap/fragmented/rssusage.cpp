extern "C" {
#include "rssusage.h"
}
#include <fmt/format.h>
#include <locale>

int main( void )
{
  std::locale::global(std::locale("en_US.UTF-8"));
  fmt::print( "peak RSS: {:L}\n", getPeakRSS());
  fmt::print( "current RSS: {:L}\n", getCurrentRSS());
  return 0;
}
