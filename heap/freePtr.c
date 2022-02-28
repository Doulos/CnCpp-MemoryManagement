#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef NULL
#warn Defining NULL
#define NULL ((int*)0)
#endif

int main(int argc, const char* argv[])
{
  printf("Attempt to free a null pointer\n");
  int* p = NULL;
  free(p);
  printf("Successfully freed a null pointer\n\n");

  printf("Attempt to free a pointer twice\n");
  p = (int*)malloc(sizeof(int));
  printf("Points to %p\n",(void*)p);
  free(p);
  printf("Successfully freed a null pointer once.\n");

  if( argc == 2 && strcmp(argv[1],"2") == 0 ) {
    free(p); /* This should fail! */
    printf("Freed a null pointer twice!\n");
  }

  printf("Exiting\n");
  return 0;
}
