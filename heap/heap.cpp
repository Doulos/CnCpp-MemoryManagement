#include <fmt/format.h>
#include <fmt/color.h>
#include <memory>
#include <cassert>

auto grn() { return fmt::emphasis::bold | fg( fmt::color::light_green );   }
auto red() { return fmt::emphasis::bold | fg( fmt::color::red );     }
auto blu() { return fmt::emphasis::bold | fg( fmt::color::light_sky_blue );    }
auto cyn() { return fmt::emphasis::bold | fg( fmt::color::cyan );    }
auto mag() { return fmt::emphasis::bold | fg( fmt::color::magenta ); }

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
// Setup for several slides
#include <vector>
using Type = uint64_t;
struct Data_t { Type x{}, y{}; };
[[maybe_unused]] Data_t const  okData = { 0xAd0beAceUL, 0xF00dCafeUL };
[[maybe_unused]] Data_t const badData = { 0xD15ea5edUL, 0xDeadBeefUL };

void slide_16() {
  fmt::print( grn(), "Starting {0:-<80}\n", __func__ );
  auto ptr = new Type{}; // C++
  auto v = std::vector<int>{}; // C++
  v.push_back( 10 );
  delete ptr;
  fmt::print( grn(), "Finished {}\n\n", __func__ );
}

//______________________________________
// Slides 18 & 19
struct S_t {
  Data_t d{};
  void processData() { fmt::print( "x={}, y={}\n", d.x, d.y); }
};

[[nodiscard]] S_t* create() {
  auto ptr = new S_t{};
  return ptr;
}

void destroy( S_t*& ptr ) {
  delete ptr;
  ptr = nullptr; //< slide_19
}

void slide_18() {
  fmt::print( grn(), "Starting {0:-<80}\n", __func__ );
  auto ptr = create();
  if( ptr != nullptr ) {
    ptr -> processData();
    destroy( ptr );
  }
  fmt::print( grn(), "Finished {}\n\n", __func__ );
}

//______________________________________
// Slide 20
class Design {
public:
  S_t* ptr;
  Design() : ptr{new S_t{}}
  {}
  ~Design() {
    delete ptr;
  }
};

void slide_20() {
  fmt::print( grn(), "Starting {0:-<80}\n", __func__ );
  auto d = Design();
  d.ptr -> processData();
  fmt::print( grn(), "Finished {}\n\n", __func__ );
}

//______________________________________
void slide_21() {
  fmt::print( grn(), "Starting {0:-<80}\n", __func__ );
  auto ptr = std::make_unique<S_t>();
  ptr -> processData();
}

void slide_23() {
  fmt::print( grn(), "Starting {0:-<80}\n", __func__ );
  {
    auto ptr1
      = std::shared_ptr<S_t>( new S_t{} );
    static auto ptr2 = ptr1;
  }
  {
    {
      auto ptr1
        = std::make_shared<S_t>();
      static auto ptr2 = ptr1;
    }

  }
  fmt::print( grn(), "Finished {}\n\n", __func__ );
}

//______________________________________
void slide_24( int i=3, int j=-1 ) {
  fmt::print( grn(), "Starting {0:-<80}\n", __func__ );
  /* Assume:
   *   i >= ( sizeof(arr)/sizeof(int) )
   *   j < 0
   */

  int* arr = new int[3];

  arr[i] = 0x0badBeef; // ?

  int* ptr = arr;

  *( ptr + j ) = 0x0badF00d; // ?

  fmt::print( grn(), "Finished {}\n\n", __func__ );
}

//______________________________________
void slide_25( int i ) {
  fmt::print( grn(), "Starting {0:-<80}\n", __func__ );
  std::vector<Type> vec = { 1, 2, 3 };
  vec.at( i ) = 0xDeadCab1eUL;
  fmt::print( grn(), "Finished {}\n\n", __func__ );
}

//______________________________________
// Slide 29
#define THINGS 8
class Thingy {
  static size_t next() { static size_t id = 0; return ++id; }
  size_t id{0};
  double f{0.0};
  bool   use{false};
public:
  Thingy() :id{next()} {}
  void init()  { use = true; id=next(); f = 0.0; print(); }
  void reset() { use = false; }
  [[nodiscard]] bool inUse() const { return use; }
  void process() { f += 0.1; print(); }
  void print() { fmt::print( "Thingy{} @{:x} use={} f={}\n", id, uintptr_t(this), use, f); }
  static Thingy* getNext()
  {
    static Thingy pool[THINGS];
    for (auto & entry: pool) {
      if ( not entry.inUse() ) {
        entry.init();
        return &entry;
      }
    }
    return nullptr;
  }
};

void slide_29() {
  fmt::print( grn(), "Starting {0:-<80}\n", __func__ );
  auto thing1 = Thingy::getNext();
  auto thing2 = Thingy::getNext();
  thing1 -> process();
  thing1 -> process();
  thing1 -> reset(); // when finished
  auto thing3 = Thingy::getNext();
  thing3 -> process();
  thing2 -> reset(); // when finished
  auto thing4 = Thingy::getNext();
  auto thing5 = Thingy::getNext();
  thing4 -> process();
  thing5 -> process();
  fmt::print( grn(), "Finished {}\n\n", __func__ );
}

//______________________________________
// Slide 30

#include <bitset>
#define POOL_MAXDEPTH 256
#define POOL_MAXSIZE  ( 8*1'024 )
template<typename T, size_t DEPTH>
class Pool {
  static_assert( DEPTH!=0, "Pool element depth must be non-zero." );
  static_assert( DEPTH<=POOL_MAXDEPTH, "Exceeds maximum pool depth." );
  static_assert( DEPTH*sizeof(T) <= POOL_MAXSIZE, "Exceeds max pool size.");
  struct Memory { std::byte buffer[sizeof(T)]{}; };
  Memory pool[DEPTH];
  std::bitset<DEPTH> used;
  size_t allocs{0}, frees{0};
public:
  void* alloc() {
    for( size_t i=0; i<DEPTH; ++i) {
      if( used[i] ) continue;
      ++allocs;
      used[i] = true;
      fmt::print( mag(), "Debug: Allocating {}\n", i);
      return reinterpret_cast<void*>( &pool[i].buffer );
    }
    return nullptr;
  }
  void free( void* ptr ) {
    if( ptr == nullptr ) return;
    auto i = reinterpret_cast<Memory*>( ptr ) - &pool[0];
    assert( 0 <= i and i < int(DEPTH) );
    ++frees;
    used[i] = false;
    fmt::print( mag(), "Debug: Deallocating {}\n", i);
  }
  ~Pool() {
    fmt::print( mag(), "Debug: {} allocations & {} freed\n", allocs, frees );
  }
};

class Widget {
  size_t id{0};
  std::string name{"*UNDEFINED*"};
  static size_t next() { static size_t id = 0; return ++id; }
  static Pool<Widget, 10>& pool() {
    static Pool<Widget, 10> pool; return pool;
  }
public:
  explicit Widget( std::string name_ )
  : id{next()}, name{ std::move(name_) }
  { fmt::print( "Constructing "); print(); }
  Widget() : Widget{ "anonymous" } {}
  ~Widget() { fmt::print( "Destructing " ); print(); }
  void* operator new(std::size_t count) {
    fmt::print( mag(), "Debug: new({})\n", count );
    auto ptr = static_cast<Widget*>(::new (pool().alloc()) Widget{});
    return ptr;
  }
  void operator delete( void* ptr ) {
    reinterpret_cast<Widget*>(ptr) -> ~Widget();
    pool().free( ptr );
  }
  void print() const {
    return fmt::print( "Widget {} named {}\n", id, name );
  }
};

void slide_30() {
  fmt::print( grn(), "Starting {0:-<80}\n", __func__ );
  fmt::print( mag(), "Debug: sizeof(Widget)={}\n", sizeof(Widget) );
  auto uniqPtr = std::make_unique<Widget>( "uniqPtr" );
  {
    Widget stacked1{"stacked1"};
    stacked1.print();
    Widget stacked2{"stacked2"};
    stacked2.print();
  }
  auto ptr1 = new Widget("ptr1");
  ptr1 -> print();
  auto ptr2 = new Widget("ptr1");
  ptr2 -> print();
  Widget stacked3{ "stacked3" };
  stacked3.print();
  fmt::print( grn(), "Finished {}\n\n", __func__ );
}

//______________________________________
bool check( void* const ptr
            , void* const start
            , void* const last
)
{
  if (( ptr >= start )
  &&  ( ptr <  last  )) return true;
  // Error action here
  fmt::print( red(), "Pointer {} is out of bounds!\n", ptr );
  return false;
}

#include <complex>
#define AREA_DEPTH 4
void slide_31() {
  fmt::print( grn(), "Starting {0:-<80}\n", __func__ );
  auto area = new std::complex<float>[AREA_DEPTH]{};
  auto last = &area[AREA_DEPTH-1];
  auto ptr = &area[AREA_DEPTH/2];
  fmt::print( blu(), "Check valid ptr\n" );
  if( check( ptr, area, last ) ) fmt::print( grn(), "PASS\n" );
  //...
  ptr = area - 1;
  fmt::print( cyn(), "Intentional violation ptr = {:x}\n", uintptr_t(ptr) );
  if( not check( ptr, area, last ) ) fmt::print( grn(), "PASS\n" );
  fmt::print( grn(), "Finished {}\n\n", __func__ );
}

//______________________________________
// Slide 33
constexpr const size_t CACHE_LINE_SIZE = 64; // Aarch64
constexpr const size_t QTY = 10ul;
struct Data { float f; uint32_t count; };
struct alignas(CACHE_LINE_SIZE) Chunk {
  uint32_t data[sizeof(Data)]{};
};
void slide_33() {
  fmt::print( grn(), "Starting {0:-<80}\n", __func__ );
  static Chunk pool[QTY];
  fmt::print( mag(), "Debug: &pool[0] is {:#b}\n", uintptr_t(&pool[0]) );
  fmt::print( mag(), "Debug: &pool[1] is {:#b}\n", uintptr_t(&pool[1]) );
  fmt::print( grn(), "Finished {}\n\n", __func__ );
}

//______________________________________
// Invoke to code to ensure no hidden bugs
int main()
{
  slide_16(); // "What is the heap?" - new, delete, and std::vector
  slide_18(); // "Forgetting to free (1)" - create and destroy
  slide_20(); // "Forgetting to free (2)" -
  slide_21();
  slide_23();
  slide_24();
  slide_25(2);
  slide_29();
  slide_30();
  slide_31();
  slide_33();
  return 0;
}
