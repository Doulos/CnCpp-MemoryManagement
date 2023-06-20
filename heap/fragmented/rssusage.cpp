extern "C" {
#include "rssusage.h"
}
#include <fmt/format.h>
#include <locale>
#include <string>

int main( int argc, const char* argv[] )
{
  // locale not fully supported on all platforms
  if( argc > 1 && std::string{"-l"} == argv[1] ) std::locale::global(std::locale("en_US.UTF-8"));
  fmt::print( "peak RSS: {:L}\n", getPeakRSS());
  fmt::print( "current RSS: {:L}\n", getCurrentRSS());
  return 0;
}
