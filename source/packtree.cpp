#include <assert.h>
#include <stdio.h>
#include "packcontainer.h"
#include "packtree.h"

packtree::packtree( const double *vec,
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
  newLevel( root, false, false );
}

void packtree::cleanTree(packnode<double> *top, bool removeMark )
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
void packtree::prCost()
{
  if (root != 0) {
    breadthFirstPrint(printCost);
  }
}

void packtree::prBestBasis()
{
  if (root != 0) {
    cleanTree( root, false );
    breadthFirstPrint(printBestBasis);
  }
}
double packtree::bestBasisWalk( packnode<double> *top )
{
  double cost = 0.0;

  if (top != 0) {
    packnode<double> *lhs = top->lhsChild();
    packnode<double> *rhs = top->rhsChild();

    if (lhs == 0 && rhs == 0) {
      cost = top->cost();
    }
    else if (lhs != 0 && rhs != 0) {

      double lhsCost = bestBasisWalk( lhs );
      double rhsCost = bestBasisWalk( rhs );

      double v1 = top->cost();
      double v2 = lhsCost + rhsCost;

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
void packtree::bestBasis()
{
  bestBasisWalk( root );
}
void packtree::checkBestBasis( packnode<double> *top )
{
  if (top != 0) {
    if (top->mark()) {
      foundBestBasisVal = true;
      if (top->getKind() == packdata<double>::OriginalData) {
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
bool packtree::bestBasisOK()
{
  foundOriginalData = false;
  foundBestBasisVal = false;
  checkBestBasis( root );

  bool rslt = (foundBestBasisVal && (!foundOriginalData));

  return rslt;
}
void packtree::buildBestBasisList( packnode<double> *top,
				   packdata_list<double> &list )
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
packdata_list<double> packtree::getBestBasisList()
{
  packdata_list<double> list;

  buildBestBasisList( root, list );
  return list;
}
