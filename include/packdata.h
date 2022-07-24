
#ifndef _PACKDATA_H_
#define _PACKDATA_H_

#include "blockpool.h"

template <class T>
class packdata {
private:

  packdata( const packdata &rhs ) {}

public:
  typedef enum { BadNodeKind,
                 OriginalData,
                 LowPass,
                 HighPass } transformKind;

protected:

  transformKind kind;

  size_t N;

  /** Wavelet packet data */
  T* data;

  /** default constructor */
  packdata() {}

public:

  packdata( T *vec, const size_t n, const transformKind k )
  {
    data = vec;
    N = n;
    kind = k;
  }

  virtual ~packdata() {}

  void *operator new( size_t num_bytes )
  {
    block_pool mem_pool;

    void *mem_addr = mem_pool.pool_alloc( num_bytes );
    return mem_addr;
  } // new

  void pr() const
  {
    for (int i = 0; i < N; i++) {
      printf("%7.4f ", data[i] );
    }
    printf("\n");
  } // pr

  const T* getData() { return data; }

  const transformKind getKind() { return kind; }

  size_t length() { return N; }
}; 


#endif
