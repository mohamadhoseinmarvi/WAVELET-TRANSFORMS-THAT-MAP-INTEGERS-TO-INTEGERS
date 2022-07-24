
#ifndef _HAAR_CLASSIC_H_
#define _HAAR_CLASSIC_H_

#include <math.h>

#include "liftbase.h"

template <class T>
class haar_classic : public liftbase<T, double> {

protected:

  void predict( T& vec, int N, transDirection direction )
  {
    int half = N >> 1;
    int cnt = 0;

    for (int i = 0; i < half; i++) {
      double predictVal = vec[i];
      int j = i + half;

      if (direction == forward) {
	vec[j] = (predictVal - vec[j] )/2;
      }
      else if (direction == inverse) {
	vec[j] =  predictVal - (2 * vec[j]);
      }
      else {
	printf("haar_classic::predict: bad direction value\n");
      }
    }
  } // predict

  void update( T& vec, int N, transDirection direction )
  {
    int half = N >> 1;

    for (int i = 0; i < half; i++) {
      int j = i + half;
      double updateVal = vec[j];

      if (direction == forward) {
	vec[i] = vec[i] - updateVal;
      }
      else if (direction == inverse) {
	vec[i] = vec[i] + updateVal;
      }
      else {
	printf("update: bad direction value\n");
      }
    }
  } // update

}; // haar_classic

#endif
