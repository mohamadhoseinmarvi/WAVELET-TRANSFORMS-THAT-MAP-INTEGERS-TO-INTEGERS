
#include <stdio.h>

#include "yahooTS.h"


main()
{
  const size_t VEC_SIZE = 512;
  double vec[VEC_SIZE];
  yahooTS ts( "equities\\" );
  
  size_t N = VEC_SIZE;
  if (ts.getTS( "aa", vec, N, yahooTS::Close )) {
    for (size_t i = 0; i < VEC_SIZE; i++) {
      printf("%3d  %f\n", i, vec[i] );
    }
  }
  else {
    fprintf(stderr, "main: getTS failed\n");
  }
}
