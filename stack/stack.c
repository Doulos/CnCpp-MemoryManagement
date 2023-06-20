#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wunused-parameter"
#elif defined(__GNUC__) || defined(__GNUG__)
#  pragma GCC   diagnostic ignored "-Wunused-parameter"
#endif

#include "stack.h"

void fail(const char* file, int line, const char* mesg)
{
  printf("FATAL %s:%d: %s\n", file, line, mesg);
  abort();
}

//--------------------------------------
// Slide 29

typedef struct {
  uintptr_t tos;
  uintptr_t bos;
} StackProbe;

StackProbe  instance = { 0, 0 };
StackProbe* probe = &instance;

void StackProbe__setup(void* top) {
  uint32_t ref;
  printf( "Setting up StackProbe\n" );
  probe = &instance;
  instance.bos = (top != NULL) ? (uintptr_t)(top) : (uintptr_t)(&ref);
  instance.tos = instance.bos;
}

uintptr_t min_uintptr( uintptr_t a, uintptr_t b ) { return (a<b) ? a : b; }

void StackProbe__update() {
  uint32_t ref;
  if( probe && probe->bos ) {
    probe->bos = min_uintptr( probe->bos, ( uintptr_t ) ( &ref ));
  }
  else fail(__FILE__, __LINE__, "Bad probe");
}

uint32_t StackProbe__maxDepth() {
  if( probe && probe->bos && probe->tos ) {
    return probe->tos - probe->bos;
  }
  else {
    fail(__FILE__, __LINE__, "Bad probe");
    return 0;
  }
}

void StackProbe__printDepth()
{
  printf( "Stack depth %u\n", StackProbe__maxDepth());
}

void oneDeep() {
  StackProbe__update();
}

// Following uses 32-bytes of stack on Armv8-A
// : Return address, Link register, & ?
void use32(int n) {
  if( --n > 0 ) use32( n-1 );
  StackProbe__update();
}

#define W10 "----------"
#define W40 W10 W10 W10 W10
#define W80 W40 W40

void stackTest()
{
  void* anchor = &anchor;
  printf( "Starting %-80s\n", __func__ );

  StackProbe__setup(anchor);
  printf( "Nothing called => " );
  StackProbe__printDepth();

  StackProbe__setup(anchor);
  printf( "Calling oneDeep() => " );
  oneDeep();
  StackProbe__printDepth();

  for ( int i = 8; --i; ) {
    StackProbe__setup(anchor);
    printf( "Calling use32(%d) => ", i );
    use32( i );
    StackProbe__printDepth();
  }
  printf( "Finished %s\n\n", __func__ );
}

//--------------------------------------
// Slide 49

uint32_t randNoise(uint_fast8_t bits) {
  // Discard lower-8 bits due to poor distribution
  return (random()>>8)&((1<<bits)-1);
}

uint32_t addNoise(uint32_t pel) {
  uint_fast8_t r = ((pel >> 16) & 0xFF) ^ randNoise(4);
  uint_fast8_t g = ((pel >>  8) & 0xFF) ^ randNoise(4);
  uint_fast8_t b = ((pel >>  0) & 0xFF) ^ randNoise(4);
  return  (r << 16) | (g << 8) | (b << 0);
}

#define W 640
#define H 480
typedef struct {
  size_t width;
  size_t height;
  uint32_t pel[W*H];
} Image;

//______________________________________
Image image_enhance1( Image img )
{
  Image temp;
  temp.width = img.width;
  temp.height = img.height;
  for( size_t col=0ul; col<img.width; ++col) {
    for( size_t row=0ul; row<img.height; ++row) {
      size_t index = col * img.height + row;
      temp.pel[ index ] =  addNoise( img.pel[ index ] );
    }
  }
  StackProbe__update();
  return temp;
}

//______________________________________
Image image_enhance2( Image* img )
{
  Image temp;
  temp.width = img->width;
  temp.height = img->height;
  for( size_t col=0ul; col<img->width; ++col) {
    for( size_t row=0ul; row<img->height; ++row) {
      size_t index = col * img->height + row;
      temp.pel[ index ] =  addNoise( img->pel[ index ] );
    }
  }
  StackProbe__update();
  return temp;
}

void slide_49() {
  printf( "Starting %-80s\n", __func__ );

  void* anchor = &anchor;
  StackProbe__setup(anchor);
  Image img = { 640, 480, { 0 } };
  printf( "Calling image_enhance1(img:w=%zu h=%zu sizeof(img)=%zu) => ", img.width, img.height, sizeof(img) );
  img = image_enhance1( img );
  StackProbe__printDepth();

  StackProbe__setup(NULL);
  printf( "Calling image_enhance2(&img:w=%zu h=%zu sizeof(img)=%zu) => ", img.width, img.height, sizeof(img) );
  img = image_enhance2( &img );
  StackProbe__printDepth();

  printf( "Finished %s\n\n", __func__ );
}

//______________________________________
int main()
{
  stackTest();
  slide_49();
  return 0;
}
