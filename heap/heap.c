#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wunused-parameter"
#elif defined(__GNUC__) || defined(__GNUG__)
#  pragma GCC   diagnostic ignored "-Wunused-parameter"
#endif


//--------------------------------------
typedef uint64_t Type;
typedef struct { Type x, y; } Data_t;
#define badData { 0xD15ea5edULL, 0xDeadC0deULL }
#define SIZE (4*sizeof(Data_t))

void doWork( Type* ptr ) { *ptr += 2; }

void slide_16(void) {
  Type* ptr;
  ptr = (Type*)malloc( SIZE ); /* C */
  doWork( ptr );
  free(ptr);
}

//--------------------------------------
typedef struct { Data_t d; } S_t;
const S_t badCode = { badData };

void processData( S_t* ptr ) { ptr->d.x = 2*ptr->d.y; }

S_t* create(void) {
  S_t* ptr
    =(S_t*)malloc(sizeof(S_t));
  memset(ptr,0,sizeof(S_t));
  return ptr;
}

void destroy(S_t** pPtr) {
  free(*pPtr);
  *pPtr = NULL; /*< slide_19 */
}

void slide_18(void) {
  //...
  S_t* ptr = create();
  if( ptr ) {
    processData( ptr );
    destroy( &ptr );
  }
}

//--------------------------------------
void slide_22(void) {
  S_t* ptr1 = create();
  //…
  S_t* ptr2 = ptr1; // Share
  //…
  destroy( &ptr1 );
  //…
  if( ptr2 != NULL ){ // Valid?
    *ptr2 = badCode;//??? Write
    //…
#ifdef ALLOW_CRASH
    destroy( &ptr2 ); //!!! CRASH
#endif
  }
}

void slide_24(void) {
  /* Assume:
   *   i>=sizeof(arr)/sizeof(int)
   *   j<0
   */
  int i=3, j=-1; //< minimal values satisfying above

  Type* arr = (Type*)malloc(3*sizeof(Type));

  arr[i] = 0xDeadBeefUL; // ? Corrupt beyond end

  Type* ptr = arr;

  *(ptr + j) = 0xDeadF00dUL; // ? Corrupt before beginning

}

//--------------------------------------
typedef int Arr[4];
#define DEPTH (4*sizeof(Arr))
void slide_25(int i) {
  int* arr = (int*)malloc(DEPTH);
  assert(i>=0 && i<(int)sizeof(arr));
  arr[i] = 0x0BadC0de;
  free(arr);
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
  printf( "Pointer %p is out of bounds!\n", ptr );
  return false;
}

#define AREA_DEPTH 4
void slide_31(void) {
  printf( "Starting %-80s\n", __func__ );
  struct Complex { double re, im; } area[AREA_DEPTH] = {{0.0,0.0},{0.0,0.0},{0.0,0.0},{0.0,0.0}};
  struct Complex* last = &area[AREA_DEPTH-1];
  struct Complex* ptr = &area[AREA_DEPTH/2];
  printf( "Check valid ptr\n" );
  if( check( ptr, area, last ) ) printf( "Check indicates success - PASS\n" );
  //...
  ptr = area - 1;
  printf( "Intentional violation ptr = %p\n", (void*)ptr );
  if( ! check( (void*)ptr, (void*)area, last ) ) printf( "Check indicates failure - PASS\n" );
  printf( "Finished %s\n\n", __func__ );
}

//--------------------------------------
int main(int argc, const char* argv[])
{
//printf("Starting heap.c\n");
  slide_16(); // "What is the heap?" - malloc & free examples
  slide_18(); // "Forgetting to free (1)" - proper create & destroy
  slide_22(); // "Access after free and double free"
  slide_25(2);// "- valid heap access
  if( argc == 1 ) printf("Hiding corruption -- try adding an argument\n");
  slide_24(); // "Corrupt heap array - write outside array before and after"
  slide_31();
  return 0;
}
