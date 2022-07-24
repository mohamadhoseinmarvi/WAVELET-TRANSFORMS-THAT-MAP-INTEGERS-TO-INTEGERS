
#ifndef _PACKCONTAINER_H_
#define _PACKCONTAINER_H_

#include "packnode.h"

class packcontainer {
private:
  /** number of elements at this packet tree level */
  size_t N;
  /** left (low pass) half of the packcontainer data */
  double* lhs;
  /** right (high pass) half of the packnode data */
  double* rhs;

private:
  /** disallow the copy constructor */
  packcontainer( const packcontainer &rhs ) {};
  /** disallow default constructor */
  packcontainer() {};

public:

  packcontainer( packnode<double>* node )
  {
    assert( node != 0 );
    N = node->length();
    assert( N > 1 );

    size_t half = N >> 1;
    block_pool mem_pool;
    size_t num_bytes = half * sizeof(double);

    lhs = (double *)mem_pool.pool_alloc( num_bytes );
    rhs = (double *)mem_pool.pool_alloc( num_bytes );

    for (size_t i = 0; i < N; i++) {
      (*this)[i] = (*node)[i];
    }
  }

  packcontainer( size_t n )
  {
    N = n;
    lhs = 0;
    rhs = 0;
  }

  void *operator new( size_t num_bytes )
  {
    block_pool mem_pool;

    void *mem_addr = mem_pool.pool_alloc( num_bytes );
    return mem_addr;
  } // new

  double &operator[]( const size_t i )
  {
    assert( i < N );
    size_t half = N >> 1;

    if (i < half)
      return lhs[i];
    else {
      return rhs[i-half];
    }
  }

  /** RHS [] operator */
  double operator[]( const size_t i ) const
  {
    assert( i < N );
    size_t half = N >> 1;

    if (i < half)
      return lhs[i];
    else {
      return rhs[i-half];
    }
  }

  double* lhsData() { return lhs; }

  double* rhsData() { return rhs; }


  void lhsData(double* l) { lhs = l; }

  void rhsData(double* r) { rhs = r; }

  size_t length() { return N; }

}; // packcontainer

#endif
