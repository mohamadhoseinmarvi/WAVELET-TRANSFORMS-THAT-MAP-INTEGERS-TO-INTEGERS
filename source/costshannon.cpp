
#include <assert.h>
#include <stdio.h>
#include <math.h>
#include "costshannon.h"

double costshannon::costCalc( packnode<double> *node )
{
  assert( node != 0 );

  size_t len = node->length();
  const double *a = node->getData();

  double sum = 0.0;
  for (int i = 0; i < len; i++) {
    double val = 0.0;
    if (a[i] != 0.0) {
      double square = a[i] * a[i];
      val = square * log( square );
    }
    sum = sum + val;
  }

  return -sum;
}
