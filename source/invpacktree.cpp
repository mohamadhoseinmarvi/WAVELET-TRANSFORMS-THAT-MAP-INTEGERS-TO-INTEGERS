#include <assert.h>
#include <stdio.h>
#include "blockpool.h"
#include "invpacktree.h"

void invpacktree::new_level( packdata<double> *elem )
{
  size_t half = elem->length();
  size_t n = half * 2;

  packcontainer *container = new packcontainer( n );
  container->lhsData( (double *)elem->getData() );
  stack.add( container );
}

void invpacktree::reduce()
{
  LIST<packcontainer *>::handle h;
  h = stack.first();
  packcontainer *tos = stack.get_item( h );

  assert( tos->lhsData() != 0 && tos->rhsData() != 0 );
  stack.remove();

  int n = tos->length();
  waveObj->inverseStep( (*tos), n );
  block_pool mem_pool;

  double *vec = (double *)mem_pool.pool_alloc( n * sizeof( double ) );
  for (int i = 0; i < n; i++) {
    vec[i] = (*tos)[i];
  }

  if (stack.first() != 0) {
    h = stack.first();
    packcontainer *tos = stack.get_item( h );

    if (tos->length() == n*2) {
      tos->rhsData( vec );
      reduce();
    }
    else {
      assert( tos->length() > n*2 );
      packcontainer *container = new packcontainer( n*2 );
      container->lhsData( vec );
      stack.add( container );
    }
  }
  else {
    packcontainer *container = new packcontainer( n*2 );
    container->lhsData( vec );
    stack.add( container );
  }
}
void invpacktree::add_elem( packdata<double> *elem )
{
  assert( elem != 0 );

  if (stack.first() == 0) {
    new_level( elem );
  }
  else {
    size_t half = elem->length();
    size_t n = half * 2;
    LIST<packcontainer *>::handle h;
    h = stack.first();
    packcontainer *tos = stack.get_item( h );

    if (tos->length() == n) {
      assert( tos->rhsData() == 0);
      tos->rhsData( (double *)elem->getData() );
      reduce();
    }
    else if (tos->length() > n) {
      new_level( elem );
    }
    else {
      printf("add_elem: the size of the TOS elem is wrong\n");
    }
  }
}

invpacktree::invpacktree( packdata_list<double> &list,
			  liftbase<packcontainer, double> *w )
{
  data = 0;
  N = 0;
  waveObj = w;

  packdata_list<double>::handle h;
  for (h = list.first(); h != 0; h = list.next( h )) {
    packdata<double> *elem = list.get_item( h );
    add_elem( elem );
  }

  LIST<packcontainer *>::handle tosHandle;
  tosHandle = stack.first();
  packcontainer *tos = stack.get_item( tosHandle );

  if (tos != 0) {
    size_t len = tos->length();
    N = len/2;

    data = tos->lhsData();
    stack.remove();
  }
}

void invpacktree::pr()
{
  if (data != 0) {
    for (int i = 0; i < N; i++) {
      printf("%7.4f ", data[i] );
    }
    printf("\n");
  }
} 
