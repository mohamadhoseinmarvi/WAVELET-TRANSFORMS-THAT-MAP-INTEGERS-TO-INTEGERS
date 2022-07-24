#include <assert.h>
#include <stdio.h>
#include <math.h>
#include "packfreq.h"

packfreq::packfreq( const double *vec,
		    const size_t N,
		    liftbase<packcontainer, double> *w )
{
  waveObj = w;

  block_pool mem_pool;
  double *vecCopy = (double *)mem_pool.pool_alloc( N * sizeof( double ) );

  for (int i = 0; i < N; i++) {
    vecCopy[i] = vec[i];
  }

  root = new packnode<double>( vecCopy, N, packnode<double>::OriginalData );
  root->mark( true );

  newLevel( root, true,     false );
}

void packfreq::findLevel( packnode<double>* top,
			  size_t cur_level,
			  const size_t level )
{
  if (top != 0) {
    if (cur_level == level) {
      mat.append(top);
    }
    else {
      findLevel( top->lhsChild(), cur_level+1, level );
      findLevel( top->rhsChild(), cur_level+1, level );
    }
  }
}

void packfreq::getLevel( const size_t level )
{
  findLevel( root, 0, level );
}

void packfreq::plotMat(const size_t N)
{
  size_t num_y = mat.length();
  const double incr = (double)N / (double)num_y;
  if (num_y > 0) {
    size_t num_x = mat[0]->length();

    double freq_start = 0.0;
    for (size_t y = 0; y < num_y; y++) {
      double time_start = 0.0;
      for (size_t x = 0; x < num_x; x++) {
	double val = (*mat[y])[ x ];

	printf(" %d  %d  %7.4f\n", y, x, log(1+(val*val)) );

	time_start = time_start + incr;
      }
      freq_start = freq_start + incr;
      printf("\n");
    }
  }
}

void packfreq::prMat()
{
  size_t num_y = mat.length();
  if (num_y > 0) {
    size_t num_x = mat[0]->length();
    for (size_t y = num_y-1; y >= 0; y--) {
      for (size_t x = 0; x < num_x; x++) {
	printf(" %7.4f ", (*mat[y])[ x ] );
      }
      printf("\n");
      fflush(stdout);
    }
  }
} 
