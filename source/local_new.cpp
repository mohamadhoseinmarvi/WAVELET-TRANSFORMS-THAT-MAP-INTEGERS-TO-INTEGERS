
#include <stdio.h>
#include <stdlib.h>

void *operator new( size_t num_bytes )
{
  printf("global operator new\n");
  void *rtn = malloc( num_bytes );
  return rtn;
}


void *operator new[]( size_t num_bytes )
{
  printf("global operator new []\n");
  void *rtn = malloc( num_bytes );
  return rtn;
}


void operator delete( void *addr )
{
  printf("global operator delete\n");
  free( addr );
}


void operator delete[](void *addr )
{
  printf("global operator delete []\n");
  free( addr );
}
