
/** \file

  This file contains test code for wavelet packet tree construction
  and for testing the best basis calculation. 

  The documentation in this file is formatted for doxygen
  (see www.doxygen.org).

<h4>
    
</h4>

<p>
   You may use this source code without limitation and without
   fee as long as you include:
</p>
<blockquote>
     This software was written and is copyrighted by Ian Kaplan, Bear
     Products International,  ,  .
</blockquote>
<p>
   This software is provided "as is", without any warranty or
   claim as to its usefulness.  Anyone who uses this source code
   uses it at their own risk.  Nor is any support provided by
   Ian Kaplan and Bear Products International.
<p>
   Please send any bug fixes or suggested source changes to:
<pre>
      
</pre>

   

 */

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

/** \file

  Test code for the floating point form of the wavelet packet
  algorithm.

 */


double data[] = { 32.0, 10.0, 20.0, 38.0, 37.0, 28.0, 38.0, 34.0,
                  18.0, 24.0, 18.0, 9.0, 23.0, 24.0, 28.0, 34.0 };


/**
double data[] = { 56.0, 40.0, 8.0, 24.0, 48.0, 48.0, 40.0, 16.0 };
*/


/** \function
  
  Print a vector of doubles whose length is len.

 */
void prVec( double *vec, size_t len )
{
  for (int i = 0; i < len; i++) {
    printf("%7.4f ", vec[i] );
  }
  printf("\n");
}


/**

  Test that the wavelet transform is invertable
  
 */
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

} // testWaveletTrans



/**

  The entry point for code to test the wavelet packet transform.

  The code in main provides a simple example of how to call the
  wavelet packet transform code.

*/
int
main()
{
  size_t len = sizeof(data)/sizeof(double);
  // testWaveletTrans( data, len );

  // The "Haar" classic transform
  haar_classic<packcontainer> h;

  // calculate the wavelet packet tree, using the wavelet transform h
  packtree tree( data, len, &h );
  // print the wavelet transform tree (breadth first)
  tree.pr();

  // get the root of the wavelet packet transform tree
  packnode<double> *treeRoot = tree.getRoot();

  // assign the Shannon entropy cost function to the tree
  costshannon cost( treeRoot );

  // Calculate a simple threshold cost function on the 
  // wavelet packet transform tree
  // costthresh thresh( treeRoot, 1.0 );

  printf("\n");
  // Print the wavelet packet transform tree showing the cost
  // function result.
  tree.prCost();

  // Calculate the "best basis" function from the tree
  tree.bestBasis();

  printf("\n");

  // Print the wavelet packet tree showing the nodes selected
  // as part of the "best basis" set.
  tree.prBestBasis();

  // Check that the best basis function succeeded.  That is,
  // that the best basis function does not include the 
  // original data.
  if (tree.bestBasisOK()) {
    printf("Best basis calculation succeeded\n");
  }
  else {
    printf("Best basis calculation failed\n");
  }

  printf("\n");

  // Get the best basis list.  This will be a list of
  // nodes consisting of the best basis set.  This set is
  // obtained by traversing the tree, top down, left to
  // right.
  packdata_list<double> bestBasis = tree.getBestBasisList();

  // Print the "best basis" set.
  bestBasis.pr();

  printf("\n");

  // Calculate the inverse wavelet packet transform from the
  // "best basis" list.
  invpacktree invtree( bestBasis, &h );

  printf("Inverse wavelet packet transform result:\n");
  invtree.pr();

  // free the memory pool
  block_pool mem_pool;
  mem_pool.free_pool();

  return 0;
}
