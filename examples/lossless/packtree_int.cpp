
#include <assert.h>
#include <stdio.h>

#include "packcontainer_int.h"
#include "packtree_int.h"

packtree_int::packtree_int( const int *vec,
			    const size_t N,
			    liftbase<packcontainer_int, int> *w )
{
  waveObj = w;

  block_pool mem_pool;
  int *vecCopy = (int *)mem_pool.pool_alloc( N * sizeof( int ) );

  for (int i = 0; i < N; i++) {
    vecCopy[i] = vec[i];
  }

  root = new packnode<int>( vecCopy, N, packnode<int>::OriginalData );
  root->mark( true );
  newLevel( root, false, false );
}
void packtree_int::cleanTree(packnode<int> *top, bool removeMark )
{
  if (top != 0) {
    if (removeMark) {
      if (top->mark()) {
        top->mark( false );
      }
    }
    else {

      if (top->mark()) {
        removeMark = true;
      }
    }
    cleanTree( top->lhsChild(), removeMark );
    cleanTree( top->rhsChild(), removeMark );
  }
}

void packtree_int::prCost()
{
  if (root != 0) {
    breadthFirstPrint(printCost);
  }
}
void packtree_int::prBestBasis()
{
  if (root != 0) {
    cleanTree( root, false );
    breadthFirstPrint(printBestBasis);
  }
}

int packtree_int::bestBasisWalk( packnode<int> *top )
{
  int cost = 0;

  if (top != 0) {
    packnode<int> *lhs = top->lhsChild();
    packnode<int> *rhs = top->rhsChild();

    if (lhs == 0 && rhs == 0) {
      cost = top->cost();
    }
    else if (lhs != 0 && rhs != 0) {

      int lhsCost = bestBasisWalk( lhs );
      int rhsCost = bestBasisWalk( rhs );

      int v1 = top->cost();
      int v2 = lhsCost + rhsCost;

      if (v1 <= v2) {
        top->mark( true );
        lhs->mark( false );
        rhs->mark( false );
      }
      else {
        top->cost( v2 );
      }
      cost = top->cost();
    }
    else {
      assert( false );
    }
  }

  return cost;
}

void packtree_int::bestBasis()
{
  bestBasisWalk( root );
}

void packtree_int::checkBestBasis( packnode<int> *top )
{
  if (top != 0) {
    if (top->mark()) {
      foundBestBasisVal = true;
      if (top->getKind() == packdata<int>::OriginalData) {
        foundOriginalData = true;
      }
    }
    if (!foundOriginalData) {
      checkBestBasis( top->lhsChild() );
    }
    if (!foundOriginalData) {
      checkBestBasis( top->rhsChild() );
    }
  }
}

bool packtree_int::bestBasisOK()
{
  foundOriginalData = false;
  foundBestBasisVal = false;
  checkBestBasis( root );

  bool rslt = (foundBestBasisVal && (!foundOriginalData));

  return rslt;
}

void packtree_int::buildBestBasisList( packnode<int> *top,
				       packdata_list<int> &list )
{
  if (top != 0) {
    if (top->mark()) {
      list.add( top );
    }
    else {
      buildBestBasisList( top->lhsChild(), list );
      buildBestBasisList( top->rhsChild(), list );
    }
  }
}

packdata_list<int> packtree_int::getBestBasisList()
{
  packdata_list<int> list;

  buildBestBasisList( root, list );
  return list;
} 
