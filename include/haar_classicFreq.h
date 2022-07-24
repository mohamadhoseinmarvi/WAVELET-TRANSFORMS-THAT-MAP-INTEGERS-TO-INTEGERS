
#ifndef _HAAR_CLASSICFREQ_H_
#define _HAAR_CLASSICFREQ_H_

#include "haar_classic.h"

template <class T>
class haar_classicFreq : public haar_classic<T> {
protected:

  void predictRev( T& vec, int N, transDirection direction )
  {
    int half = N >> 1;
    int cnt = 0;

    for (int i = 0; i < half; i++) {
      int j = i + half;

      if (direction == forward) {
	vec[i] = (vec[i] - vec[j] )/2;
      }
      else if (direction == inverse) {
	vec[i] =  (2 * vec[i]) + vec[j];
      }
      else {
	printf("predictRev: bad direction value\n");
      }
    }
  }

  void updateRev( T& vec, int N, transDirection direction )
  {
    int half = N >> 1;

    for (int i = 0; i < half; i++) {
      int j = i + half;

      if (direction == forward) {
	vec[j] = vec[j] + vec[i];
      }
      else if (direction == inverse) {
	vec[j] = vec[j] - vec[i];
      }
      else {
	printf("updateRev: bad direction value\n");
      }
    }
  }

public:

  void forwardStepRev( T& vec, const int n )
  {
    split( vec, n );
    predictRev( vec, n, forward );
    updateRev( vec, n, forward );
  }

  void inverseStepRev( T& vec, const int n )
  {
    updateRev( vec, n, inverse );
    predictRev( vec, n, inverse );
    merge( vec, n );
  }

}; 


#endif
