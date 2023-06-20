#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BUFFER_SIZE 256ul
#define PADDED_SIZE 256ul

void fill( uint64_t* buffer, size_t depth, uint64_t expected )
{
  for(unsigned int i=0; i!=depth/8; ++i) buffer[i] = expected;
}

const char* check( uint64_t* buffer, size_t depth, uint64_t expected )
{
  bool ok = true;
  for(unsigned int i=0; i!=depth/8; ++i) ok &= (buffer[i] == expected);
  return( ok?"OK":"Corrupted!" );
}
int main(int argc, const char* argv[])
{
  int arg = 0;
  if( argc > 1 ) {
    arg = atoi( argv[1] );
  }

  const uint64_t before_pattern = 0xD15ea5edCafeF00d;
  uint64_t* before;
  before = (uint64_t*)malloc(PADDED_SIZE);
  printf("before buffer at %p\n", (void*)before );
  
  int* array;
  array = (int*)malloc(BUFFER_SIZE);
  printf("Size of buffer is %zu\n", BUFFER_SIZE);
  printf("array buffer at %p\n", (void*)array );

  const uint64_t after_pattern = 0xD15ea5edCafeF00d;
  uint64_t* after;
  after = (uint64_t*)malloc(PADDED_SIZE);
  printf("after buffer at %p\n", (void*)after );

  //////////////////////////////////////////////////////////////////////////////
  fill( before, PADDED_SIZE, before_pattern );
  fill( after, PADDED_SIZE, after_pattern );

  printf( "Before is %s\n", check( before, PADDED_SIZE, before_pattern ));
  printf( "After  is %s\n", check( after,  PADDED_SIZE, after_pattern  ));
  
  printf("Attempt valid index %d\n", 0);
  array[0] = 0xC0DE;
  printf("Success!\n");

  size_t index = BUFFER_SIZE - 1 + arg;

  if( arg > 0 ) printf("WARNING: Attempting overflowing index %zu\n", index);
  printf("Before: array[%zu] = 0x%X\n", index, array[index]);
  array[index] = 0xDEAD;
  if( arg > 0 ) printf("WARNING: Stored past end of array!\n");

  printf("After: array[%zu] = 0x%X\n", index, array[index]);

  //////////////////////////////////////////////////////////////////////////////
  fill( before, PADDED_SIZE, before_pattern );
  fill( after, PADDED_SIZE, after_pattern );

  int* ptr = array;

  *ptr = 0xC0DE;

  if( arg < 0 ) printf("WARNING: Attempting negative offset %d\n", arg);
  if( arg > 0 && (size_t)arg >= BUFFER_SIZE ) printf("WARNING: Attempting past end of allocation!\n");

  printf("Before: *(ptr%+d) = 0x%X\n", arg, *ptr);
  *ptr = 0xDEAD;
  if( arg < 0 ) printf("WARNING: Stored before start of allocation!\n");
  if( arg > 0 && (size_t)arg >= BUFFER_SIZE ) printf("WARNING: Stored past end of allocation!\n");
  printf("After: *(ptr%+d) = 0x%X\n", arg, *ptr);

  printf( "Before is %s\n", check( before, PADDED_SIZE, before_pattern ));
  printf( "After  is %s\n", check( after,  PADDED_SIZE, after_pattern  ));

  free(before);
  free(array);
  free(after);

  puts("Done\n");

  return 0;
}
