
#ifndef _LINE_INT_H_
#define _LINE_INT_H_

#include "stdio.h"
#include "liftbase.h"


template<class T>
class line_int : public liftbase<T, int>
{
public:
  line_int() {}

  ~line_int() {}

  line_int( const line_int &rhs );
private:

   int new_n_plus1( int y1, int y2)
   {
     int y = 2 * y2 - y1;
     return y;
   }

  int new_n_minus1( int y1, int y2)
  {
    int y = 2 * y1 - y2;
    return y;
  }

protected:

  void predict( T & vec, int N, transDirection direction )
  {
    int half = N >> 1;
    int predictVal;

    for (int i = 0; i < half; i++) {
      int j = i + half;
      if (i < half-1) {
	predictVal = (int)((((float)vec[i] + (float)vec[i+1])/2.0) + 0.5);
      }
      else if (N == 2) {
	predictVal = vec[0];
      }
      else {

	int n_plus1 = new_n_plus1( vec[i-1], vec[i] );
	predictVal = (int)((((float)vec[i] + (float)n_plus1)/2.0) + 0.5);
      }

      if (direction == forward) {
	vec[j] = vec[j] - predictVal;
      }
      else if (direction == inverse) {
	vec[j] = vec[j] + predictVal;
      }
      else {
	printf("line::predict: bad direction value\n");
      }
    }
  }

  void update( T & vec, int N, transDirection direction )
  {
    int half = N >> 1;

    for (int i = 0; i < half; i++) {
      int j = i + half;
      int val;

      if (i == 0 && N == 2) {
	val = (int)(((float)vec[j]/2.0) + 0.5);
      }
      else if (i == 0 && N > 2) {
	int v_n_minus_1 = new_n_minus1( vec[j], vec[j+1] );
	val = (int)((((float)v_n_minus_1 + (float)vec[j])/4.0) + 0.5);
      }
      else {
	val = (int)((((float)vec[j-1] + (float)vec[j])/4.0) + 0.5);
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
    }
  }


};


#endif
