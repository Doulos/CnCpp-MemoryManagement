#include <fmt/core.h>
#include <fmt/color.h>
#include <locale>
#include <cstdint>
#include <random>
#include <algorithm>
#include <array>
#include <cassert>

auto grn() { return fmt::emphasis::bold | fg( fmt::color::light_green );   }
auto red() { return fmt::emphasis::bold | fg( fmt::color::red );     }
auto blu() { return fmt::emphasis::bold | fg( fmt::color::light_sky_blue );    }
auto cyn() { return fmt::emphasis::bold | fg( fmt::color::cyan );    }
auto mag() { return fmt::emphasis::bold | fg( fmt::color::magenta ); }

void fail(const char* file, int line, const char* mesg) noexcept
{
  fmt::print("FATAL {}:{}: {}\n", file, line, mesg);
  abort();
}

//______________________________________
// Following are turned off to avoid clutter & confusing discussion
// around C++17 [[maybe_unused]]
#if defined( __clang__ )
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wunused-const-variable"
#elif defined( __GNUC__ ) || defined( __GNUG__ )
#  pragma GCC   diagnostic ignored "-Wunused-parameter"
#  pragma GCC   diagnostic ignored "-Wunused-const-variable"
#endif

//______________________________________
// Stack depth

class StackProbe {
  uintptr_t base{0}; // base of stack (beginning)
  uintptr_t sp{0};   // active stack pointer
  inline static StackProbe* probe{nullptr};
  StackProbe() = default;
  static void dummy() { [[maybe_unused]]volatile int unused{0}; }
public:
  static void setup() noexcept
  {
    void* ref{&ref};
    //fmt::print( mag(), "{} ref={:x} &ref = {:x}\n", __func__, uintptr_t(ref), uintptr_t( &ref ) );
    dummy();
    static StackProbe instance{};
    probe = &instance;
    probe->sp   = uintptr_t(&ref);
    probe->base = probe->sp;
  }
  static void update() noexcept
  {
    void* ref{&ref};
    //fmt::print( mag(), "{} ref={:x} &ref = {:x}\n", __func__, uintptr_t(ref), uintptr_t( &ref ) );
    if ( probe and probe->sp ) {
      // Assume stack grows downward
      probe->sp = std::min( probe->sp, uintptr_t( &ref ));
    }
    else fail(__FILE__, __LINE__, "Bad probe");
  }
  static uint32_t maxDepth() noexcept
  {
    if ( probe and probe->base and probe->sp ) {
      return probe->base - probe->sp;
    }
    else {
      fail(__FILE__, __LINE__, "Bad probe");
      return 0ul;
    }
  }
  static void printDepth() noexcept
  {
    fmt::print( cyn(), "Stack depth {:L}\n", StackProbe::maxDepth());
  }
};

void oneDeep() noexcept {
  StackProbe::update();
}

// Following uses 32-bytes of stack on Armv8-A
// : Return address, Link register, & ?
int useDepth = 0;
void use32() noexcept {
  if( --useDepth > 0 ) use32();
  StackProbe::update();
}

void stackTest() noexcept
{
  void* anchor{&anchor};
  fmt::print( grn(), "Starting {0:-<80}\n", __func__ );

  StackProbe::setup();
  fmt::print( "Nothing called => " );
  StackProbe::update();
  StackProbe::printDepth();

  StackProbe::setup();
  fmt::print( "Calling oneDeep() => " );
  oneDeep();
  StackProbe::printDepth();

  for ( int i = 4; --i; ) {
    StackProbe::setup();
    fmt::print( "Calling use32() x {} => ", i );
    useDepth = i;
    use32();
    StackProbe::printDepth();
  }
  fmt::print( grn(), "Finished {}\n\n", __func__ );
}

//______________________________________
// Slide 49
template<uint_fast8_t BITS=2>
auto randNoise() {
  static std::mt19937 gen;
  return gen() & ((1<<BITS)-1);
}

uint32_t addNoise( uint32_t pel ) noexcept {
  auto r = ((pel >> 16) & 0xFF) ^ randNoise<4>();
  auto g = ((pel >>  8) & 0xFF) ^ randNoise<4>();
  auto b = ((pel >>  0) & 0xFF) ^ randNoise<4>();
  return  (r << 16) | (g << 8) | (b << 0);
}

template<int W=640, int H=480>
struct Image {
  size_t width{W};
  size_t height{H};
  std::array<uint32_t,W*H> pel{};
  Image() = default;
  Image(const Image&) = default;
  Image& operator=(const Image& rhs) = default;
  //____________________________________
  static Image enhance1( Image img )
  {
    fmt::print( mag(), "Starting {}\n", __func__ );
    Image<W, H> temp{};
    for ( size_t col = 0ul; col < img.width; ++col ) {
      for ( size_t row = 0ul; row < img.height; ++row ) {
        auto index = col * img.height + row;
        temp.pel[ index ] =  addNoise( img.pel[ index ] );
      }
    }
    StackProbe::update();
    return temp;
  }
  //____________________________________
  static auto enhance2( const Image& img ) noexcept
  {
    fmt::print( mag(), "Starting {}\n", __func__ );
    auto temp = std::make_unique<Image<W, H>>();
    for ( size_t col = 0ul; col < img.width; ++col ) {
      for ( size_t row = 0ul; row < img.height; ++row ) {
        auto index = col * img.height + row;
        temp->pel[ index ] =  addNoise( img.pel[ index ] );
      }
    }
    StackProbe::update();
    return std::move(temp);
  }
};

void slide_49() noexcept {
  fmt::print( grn(), "Starting {0:-<80}\n", __func__ );

  {
    void *anchor{ &anchor };
    StackProbe::setup();
    Image<> img;
    fmt::print( cyn(), "w={:L} h={:L} sizeof(img)={:L}\n", img.width, img.height, sizeof( img ));
    img = Image<>::enhance1( img );
    StackProbe::printDepth();
  }

  {
    static Image<> img;
    void *anchor{ &anchor };
    StackProbe::setup();
    auto pImg = Image<>::enhance2( img );
    fmt::print( cyn(), "w={:L} h={:L} sizeof(img)={:L}\n", pImg->width, pImg->height, sizeof( *pImg ));
    StackProbe::printDepth();
  }

  fmt::print( grn(), "Finished {}\n\n", __func__ );
}

template<int W=640, int H=480>
using Image_t = Image<>;

void image_enhance( Image_t<>& img )
{
  [[maybe_unused]]thread_local Image_t<> temp1;
}

void slide_51() noexcept {
}

//______________________________________
// Invoke to code to ensure no hidden bugs
int main()
{
  std::locale::global(std::locale("en_US.UTF-8"));
  stackTest();
  slide_49();
  return 0;
}
