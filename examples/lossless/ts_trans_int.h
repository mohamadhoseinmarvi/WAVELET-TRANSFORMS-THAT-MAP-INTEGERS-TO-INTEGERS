
#ifndef _TS_TRANS_INT_H_
#define _TS_TRANS_INT_H_

#include "stdio.h"
#include "haar_int.h"

class ts_trans_int : public haar_int
{
public:
  /** the constructor does nothing */
  ts_trans_int() {}
  /** the destructor does nothing */
  ~ts_trans_int() {}
  /** declare, but do not define the copy constructor */
  ts_trans_int( const ts_trans_int &rhs );

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
  void predict2( int *& vec, int N, transDirection direction )
  {
    int half = N >> 1;
    int predictVal;

    for (int i = 0; i < half; i++) {
      int j = i + half;
      int y_n_plus1;
      int y_n_minus1;

      if (N == 2) {
	y_n_minus1 = vec[0];
	y_n_plus1 = vec[0];
      }
      else if (i == 0) {
	y_n_minus1 = new_n_minus1( vec[0], vec[1] );
	y_n_plus1 = vec[1];
      }
      else if (i < half-1) {
	y_n_minus1 = vec[i-1];
	y_n_plus1  = vec[i+1];
      }
      else { // i == half-1
	y_n_minus1 = vec[i-1];
	y_n_plus1  = new_n_plus1( vec[i-1], vec[i] );
      }

      predictVal = (int)( (((float)y_n_minus1 - (float)y_n_plus1)/4.0) + 0.5 );

      if (direction == forward) {
	vec[j] = vec[j] + predictVal;
      }
      else if (direction == inverse) {
	vec[j] = vec[j] - predictVal;
      }
      else {
	printf("haar_int::predict: bad direction value\n");
      }
    }
  } // predict2

public:
  void forwardStep( int *& vec, const int n )
  {
    split( vec, n );
    predict( vec, n, forward );
    update( vec, n, forward );
    predict2( vec, n, forward );
  }
  void inverseStep( int *& vec, const int n )
  {
    predict2( vec, n, inverse );
    update( vec, n, inverse );
    predict( vec, n, inverse );
    merge( vec, n );
  } // inverseStep

}; // ts_trans_int


#endif
