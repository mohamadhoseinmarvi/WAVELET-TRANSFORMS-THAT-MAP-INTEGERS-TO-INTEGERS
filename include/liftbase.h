
#ifndef _LIFTBASE_H_
#define _LIFTBASE_H_
#include <assert.h>

template <class T, class T_elem >
class liftbase {

protected:

  typedef enum {

    forward = 1,
    inverse = 2
  } transDirection;

  void split( T& vec, int N )
  {

    int start = 1;
    int end = N - 1;

    while (start < end) {
      for (int i = start; i < end; i = i + 2) {
	T_elem tmp = vec[i];
	vec[i] = vec[i+1];
	vec[i+1] = tmp;
      }
      start = start + 1;
      end = end - 1;
    }
  }

  void merge( T& vec, int N )
  {
    int half = N >> 1;
    int start = half-1;
    int end = half;

    while (start > 0) {
      for (int i = start; i < end; i = i + 2) {
	T_elem tmp = vec[i];
	vec[i] = vec[i+1];
	vec[i+1] = tmp;
      }
      start = start - 1;
      end = end + 1;
    }
  }

  virtual void predict( T& vec, int N, transDirection direction ) = 0;

  virtual void predictRev( T& vec, int N, transDirection direction ) {};

  virtual void update( T& vec, int N, transDirection direction ) = 0;

  virtual void updateRev( T& vec, int N, transDirection direction ) {}

public:

  virtual void forwardStep( T& vec, const int n )
  {
    split( vec, n );
    predict( vec, n, forward );
    update( vec, n, forward );
  }

  virtual void forwardStepRev( T& vec, const int N )
  {
    assert(false);
  }

  virtual void forwardTrans( T& vec, const int N )
  {

    for (int n = N; n > 1; n = n >> 1) {
      forwardStep( vec, n );
    }
  }

  virtual void inverseStep( T& vec, const int n )
  {
    update( vec, n, inverse );
    predict( vec, n, inverse );
    merge( vec, n );
  }

  virtual void inverseStepRev( T& vec, const int n )
  {
    assert( false );
  }
  virtual void inverseTrans( T& vec, const int N )
  {

    for (int n = 2; n <= N; n = n << 1) {
      inverseStep( vec, n );
    }
  }


}; 

#endif
