

#include <assert.h>
#include <stdio.h>

#include "blockpool.h"
#include "invpacktree_int.h"
void invpacktree_int::new_level( packdata<int> *elem )
{
  size_t half = elem->length();
  size_t n = half * 2;

  packcontainer_int *container = new packcontainer_int( n );
  container->lhsData( (int *)elem->getData() );
  stack.add( container );
} // new_level

void invpacktree_int::reduce()
{
  LIST<packcontainer_int *>::handle h;
  h = stack.first();
  packcontainer_int *tos = stack.get_item( h );

  assert( tos->lhsData() != 0 && tos->rhsData() != 0 );

  stack.remove();

  size_t n = tos->length();
  waveObj->inverseStep( (*tos), n );

  block_pool mem_pool;

  int *vec = (int *)mem_pool.pool_alloc( n * sizeof( int ) );
  for (int i = 0; i < n; i++) {
    vec[i] = (*tos)[i];
  }

  if (stack.first() != 0) {
    h = stack.first();
    packcontainer_int *tos = stack.get_item( h );

    if (tos->length() == n*2) {
      tos->rhsData( vec );
      reduce();
    }
    else {
      assert( tos->length() > n*2 );
      packcontainer_int *container = new packcontainer_int( n*2 );
      container->lhsData( vec );
      stack.add( container );
    }  // else
  }
  else {
    // the stack is empty
    packcontainer_int *container = new packcontainer_int( n*2 );
    container->lhsData( vec );
    stack.add( container );
  }
}

void invpacktree_int::add_elem( packdata<int> *elem )
{
  assert( elem != 0 );

  if (stack.first() == 0) {
    new_level( elem );
  }
  else {
    size_t half = elem->length();
    size_t n = half * 2;
    LIST<packcontainer_int *>::handle h;
    h = stack.first();
    packcontainer_int *tos = stack.get_item( h );

    if (tos->length() == n) {
      assert( tos->rhsData() == 0);
      tos->rhsData( (int *)elem->getData() );
      reduce();
    }
    else if (tos->length() > n) {
      new_level( elem );
    }
    else {
      printf("add_elem: the size of the TOS elem is wrong\n");
    }
  } // else
}

invpacktree_int::invpacktree_int( packdata_list<int> &list,
				  liftbase<packcontainer_int, int> *w )
{
  data = 0;
  N = 0;
  waveObj = w;

  packdata_list<int>::handle h;
  for (h = list.first(); h != 0; h = list.next( h )) {
    packdata<int> *elem = list.get_item( h );
    add_elem( elem );
  } // for

  LIST<packcontainer_int *>::handle tosHandle;
  tosHandle = stack.first();
  packcontainer_int *tos = stack.get_item( tosHandle );

  if (tos != 0) {
    size_t len = tos->length();
    N = len/2;

    data = tos->lhsData();
    stack.remove();
  }
}

void invpacktree_int::pr()
{
  if (data != 0) {
    for (int i = 0; i < N; i++) {
      printf("%7.4f ", data[i] );
    }
    printf("\n");
  }
} // pr
