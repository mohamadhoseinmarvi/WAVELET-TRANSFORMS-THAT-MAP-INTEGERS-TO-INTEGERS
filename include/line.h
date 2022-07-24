

#ifndef _LINE_H_
#define _LINE_H_

#include "liftbase.h"

template <class T>
class line : public liftbase<T, double> {

private:
   double new_y( double y1, double y2)
   {
     double y = 2 * y2 - y1;
     return y;
   }


protected:
  void predict( T& vec, int N, transDirection direction )
  {
    int half = N >> 1;
    double predictVal;

    for (int i = 0; i < half; i++) {
      int j = i + half;
      if (i < half-1) {
	predictVal = (vec[i] + vec[i+1])/2;
      }
      else if (N == 2) {
	predictVal = vec[0];
      }
      else {
	double n_plus1 = new_y( vec[i-1], vec[i] );
	predictVal = (vec[i] + n_plus1)/2;
      }

      if (direction == forward) {
	vec[j] = vec[j] - predictVal;
      }
      else if (direction == inverse) {
	vec[j] = vec[j] + predictVal;
      }
      else {
	printf("predictline::predict: bad direction value\n");
      }
    }
  }

  void update( T& vec, int N, transDirection direction )
  {
    int half = N >> 1;

    for (int i = 0; i < half; i++) {
      int j = i + half;
      double val;

      if (i == 0) {
	val = vec[j]/2.0;
      }
      else {
	val = (vec[j-1] + vec[j])/4.0;
      }
      if (direction == forward) {
	vec[i] = vec[i] + val;
      }
      else if (direction == inverse) {
	vec[i] = vec[i] - val;
      }
      else {
	printf("update: bad direction value\n");
      }
    } // for
  }

}; // line

#endif
