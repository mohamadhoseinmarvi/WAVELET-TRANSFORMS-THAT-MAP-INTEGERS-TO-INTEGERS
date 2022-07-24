
#ifndef _HAAR_H_
#define _HAAR_H_

#include <math.h>

#include "liftbase.h"

template <class T>
class haar : public liftbase<T, double> {

protected:

  void predict( T& vec, int N, transDirection direction )
  {
    int half = N >> 1;

    for (int i = 0; i < half; i++) {
      double predictVal = vec[i];
      int j = i + half;

      if (direction == forward) {
	vec[j] = vec[j] - predictVal;
      }
      else if (direction == inverse) {
	vec[j] = vec[j] + predictVal;
      }
      else {
	printf("haar::predict: bad direction value\n");
      }
    }
  }

  void update( T& vec, int N, transDirection direction )
  {
    int half = N >> 1;

    for (int i = 0; i < half; i++) {
      int j = i + half;
      double updateVal = vec[j] / 2.0;

      if (direction == forward) {
	vec[i] = vec[i] + updateVal;
      }
      else if (direction == inverse) {
	vec[i] = vec[i] - updateVal;
      }
      else {
	printf("update: bad direction value\n");
      }
    }
  }

  void normalize( T& vec, int N, transDirection direction )
  {
    const double sqrt2 = sqrt( 2.0 );
    int half = N >> 1;

    for (int i = 0; i < half; i++) {
      int j = i + half;

      if (direction == forward) {
	vec[i] = sqrt2 * vec[i];
	vec[j] = vec[j]/sqrt2;
      }
      else if (direction == inverse) {
	vec[i] = vec[i]/sqrt2;
	vec[j] = sqrt2 * vec[j];
      }
      else {
	printf("normalize: bad direction value\n");
      }
    }
  }

  void inverseStep( T& vec, const int n )
  {
    normalize( vec, n, inverse );
    update( vec, n, inverse );
    predict( vec, n, inverse );
    merge( vec, n );
  }

  void forwardStep( T& vec, const int n )
  {
    split( vec, n );
    predict( vec, n, forward );
    update( vec, n, forward );
    normalize( vec, n, forward );
  }


}; 

#endif
