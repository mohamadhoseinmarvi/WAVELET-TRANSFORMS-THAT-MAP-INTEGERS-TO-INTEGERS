#include <assert.h>
#include <stdio.h>

#include "haar.h"
#include "haar_classic.h"
#include "haar_classicFreq.h"

#include "packnode.h"
#include "packcontainer.h"
#include "packtree.h"
#include "invpacktree.h"

#include "costshannon.h"
#include "costthresh.h"

double data[] = { 32.0, 10.0, 20.0, 38.0, 37.0, 28.0, 38.0, 34.0,
                  18.0, 24.0, 18.0, 9.0, 23.0, 24.0, 28.0, 34.0 };

void prVec( double *vec, size_t len )
{
  for (int i = 0; i < len; i++) {
    printf("%7.4f ", vec[i] );
  }
  printf("\n");
}

void testWaveletTrans(const double *data, const size_t len )
{
  haar<double *> haarVec;
  block_pool mem_pool;

  size_t num_bytes = len * sizeof(double);
  double *vec = (double *)mem_pool.pool_alloc( num_bytes );

  for (int i = 0; i < len; i++) {
    vec[i] = data[i];
  }

  printf("Before forward trans:\n");
  prVec( vec, len );

  haarVec.forwardTrans( vec, len );
  printf("After forward trans:\n");
  prVec( vec, len );

  haarVec.inverseTrans( vec, len );
  printf("After inverse trans:\n");
  prVec( vec, len );

  printf("\n");

}

int
main()
{
  size_t len = sizeof(data)/sizeof(double);
  haar_classic<packcontainer> h;
  packtree tree( data, len, &h );
  tree.pr();
  packnode<double> *treeRoot = tree.getRoot();
  costshannon cost( treeRoot );
  printf("\n");
  tree.prCost();
  tree.bestBasis();
  printf("\n");
  tree.prBestBasis();
  if (tree.bestBasisOK()) {
    printf("Best basis calculation succeeded\n");
  }
  else {
    printf("Best basis calculation failed\n");
  }

  printf("\n");
  packdata_list<double> bestBasis = tree.getBestBasisList();
  bestBasis.pr();

  printf("\n");
  invpacktree invtree( bestBasis, &h );

  printf("Inverse wavelet packet transform result:\n");
  invtree.pr();
  block_pool mem_pool;
  mem_pool.free_pool();

  return 0;
}
