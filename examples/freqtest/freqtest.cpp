#include <assert.h>
#include <stdio.h>

#include "packcontainer.h"
#include "haar_classicFreq.h"
#include "daub.h"
#include "packfreq.h"

double data[] = { 32.0, 10.0, 20.0, 38.0, 37.0, 28.0, 38.0, 34.0,
                  18.0, 24.0, 18.0, 9.0, 23.0, 24.0, 28.0, 34.0 };

void gen_freqMix( double *vecX, double *vecY, size_t N)
{
  const double PI = 3.1415926535897932384626433832795;
  const double range = 2 * PI;
  const double incr = range / (double)N;

  double point = 0.0;
  int i;
  for (i = 0; i < N; i++) {
    vecX[i] = point;
    vecY[i] = 4 * sin( 64 * point ) +
              2 * sin( 32 * point ) +
              1 * sin( 16 * point ) +
            0.5 * sin( 8  * point );
    point = point + incr;
  }
}

void gen_sinCombo( double *vecX, double *vecY, size_t N )
{
  const double PI = 3.1415926535897932384626433832795;
  const double range = 8 * PI;
  const double incr = range / (double)N;

  double point = 0.0;

  int stepCnt = 0;
  int i;
  for (i = 0; i < N; i++) {
    vecX[i] = point;
    vecY[i] = sin( 4 * PI * point );

    point = point + incr;
  }
}
void gen_steps( double *vecX, double *vecY, size_t N, size_t steps )
{
  const double PI = 3.1415926535897932384626433832795;
  const double range = 32 * PI;
  const double incr = range / (double)N;

  double point = 0.0;

  double mult = 1;
  const size_t stepWidth = N / steps;
  int stepCnt = 0;
  int i;
  for (i = 0; i < N; i++) {
    vecX[i] = point;
    vecY[i] = sin( mult * point );
    point = point + incr;
    stepCnt++;
    if (stepCnt == stepWidth) {
      mult = mult + (PI/2.0);
      stepCnt = 0;
    }
  }
}
void gen_chirp( double *vecX, double *vecY, size_t N )
{
  const double PI = 3.1415926535897932384626433832795;
  const double range = 2;

  const double incr = range / (double)N;

  double point = 0.0;

  int i;
  for (i = 0; i < N; i++) {
    vecX[i] = point;
    vecY[i] = sin( 128 * PI * point * point );
    point = point + incr;
  }
}

void prCoords( double *vecX, double *vecY, size_t len )
{
  for (int i = 0; i < len; i++) {
    printf("%7.4f  %7.4f\n", vecX[i], vecY[i] );
  }
}

void prVec( double *vec, size_t len )
{
  for (int i = 0; i < len; i++) {
    printf("%4d  %7.4f\n", i, vec[i] );
  }
}

int
main()
{
  const size_t N = 1024;
  double vecX[N], vecY[N];
  gen_freqMix( vecX, vecY, N );
  haar_classicFreq<packcontainer> h;
  packfreq tree( vecY, N, &h );
  tree.getLevel( 5 );

  tree.plotMat(N);
  block_pool mem_pool;
  mem_pool.free_pool();

  return 0;
}
