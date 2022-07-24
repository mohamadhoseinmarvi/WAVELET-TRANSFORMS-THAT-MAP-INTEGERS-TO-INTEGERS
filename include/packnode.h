
#ifndef _PACKNODE_H_
#define _PACKNODE_H_

#include "packdata.h"

template<class T>
class packnode : public packdata<T> {

private:

  packnode* leftChild;

  packnode* rightChild;

  T costVal;

  bool chosen;

private:

  packnode( const packnode &rhs ) {};
  packnode() {};

public:

  packnode( T *vec,
            const size_t n,
            const transformKind k ) : packdata<T>(vec, n, k)
  {
    leftChild = 0;
    rightChild = 0;
    costVal = 0.0;
    chosen = false;
  }

  T &operator[]( const size_t i )
  {
    assert( i < N );
    return data[i];
  }

  T operator[]( const size_t i ) const
  {
    assert( i < N );
    return data[i];
  }

  void prCost() const
  {
    printf("%7.4f\n", costVal );
  }

  void prBestBasis() const
  {
    for (int i = 0; i < N; i++) {
      printf("%7.4f ", data[i] );
    }
    if (chosen) {
      printf("  *");
    }
    printf("\n");
  }

  void lhsChild( packnode *l ) { leftChild = l; }
  packnode *lhsChild(void) { return leftChild; }
  void rhsChild( packnode *r ) { rightChild = r; }
  packnode *rhsChild(void) { return rightChild; }
  void cost( T val ) { costVal = val; }
  T cost(void) { return costVal; }
  void mark( bool b ) { chosen = b; }
  bool mark() { return chosen; }

}; 

#endif
