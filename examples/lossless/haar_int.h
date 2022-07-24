#ifndef _HAAR_INT_H_
#define _HAAR_INT_H_


#include "stdio.h"
#include "liftbase.h"

class haar_int : public liftbase<int *, int>
{
public:
  /** the constructor does nothing */
  haar_int() {}
  /** the destructor does nothing */
  ~haar_int() {}

  haar_int( const haar_int &rhs );

protected:

  void predict( int *& vec, int N, transDirection direction )
  {
    int half = N >> 1;

    for (int i = 0; i < half; i++) {
      int predictVal = vec[i];
      int j = i + half;

      if (direction == forward) {
	vec[j] = vec[j] - predictVal;
      }
      else if (direction == inverse) {
	vec[j] = vec[j] + predictVal;
      }
      else {
	printf("haar_int::predict: bad direction value\n");
      }
    }
  } // predict

  void update( int *& vec, int N, transDirection direction )
  {
    int half = N >> 1;

    for (int i = 0; i < half; i++) {
      int j = i + half;
      int updateVal = vec[j] >> 1;

      if (direction == forward) {
	vec[i] = vec[i] + updateVal;
      }
      else if (direction == inverse) {
	vec[i] = vec[i] - updateVal;
      }
      else {
	printf("update_int: bad direction value\n");
      }
    }
  } // update

}; // haar_int


#endif
