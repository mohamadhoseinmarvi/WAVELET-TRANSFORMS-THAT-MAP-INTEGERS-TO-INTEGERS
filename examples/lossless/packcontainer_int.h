
#ifndef _PACKCONTAINER_INT_H_
#define _PACKCONTAINER_INT_H_

#include "packnode.h"

class packcontainer_int {
private:

  size_t N;

  int* lhs;

  int* rhs;

private:

  packcontainer_int( const packcontainer_int &rhs ) {};

  packcontainer_int() {};

public:
  packcontainer_int( packnode<int>* node )
  {
    assert( node != 0 );
    N = node->length();
    assert( N > 1 );

    size_t half = N >> 1;
    block_pool mem_pool;
    size_t num_bytes = half * sizeof(int);

    lhs = (int *)mem_pool.pool_alloc( num_bytes );
    rhs = (int *)mem_pool.pool_alloc( num_bytes );

    for (size_t i = 0; i < N; i++) {
      (*this)[i] = (*node)[i];
    }
  }

  packcontainer_int( size_t n )
  {
    N = n;
    lhs = 0;
    rhs = 0;
  }
  void *operator new( unsigned int num_bytes )
  {
    block_pool mem_pool;

    void *mem_addr = mem_pool.pool_alloc( num_bytes );
    return mem_addr;
  }

  int &operator[]( const size_t i )
  {
    assert( i < N );
    size_t half = N >> 1;

    if (i < half)
      return lhs[i];
    else {
      return rhs[i-half];
    }
  }

  int operator[]( const size_t i ) const
  {
    assert( i < N );
    size_t half = N >> 1;

    if (i < half)
      return lhs[i];
    else {
      return rhs[i-half];
    }
  }

  int* lhsData() { return lhs; }

  int* rhsData() { return rhs; }

  void lhsData(int* l) { lhs = l; }
  void rhsData(int* r) { rhs = r; }

  size_t length() { return N; }

}; 

#endif
