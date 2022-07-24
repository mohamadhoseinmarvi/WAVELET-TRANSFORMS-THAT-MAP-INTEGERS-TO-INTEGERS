

#include "queue.h"
#include "packnode.h"
#include "packcontainer_int.h"
#include "packtree_base_int.h"

void packtree_base_int::newLevel( packnode<int>* top,
			      bool freqCalc,
			      bool reverse )
{
  if (top != 0) {
    const size_t len = top->length();
    if (len > 1) {

      packcontainer_int container( top );

      if (reverse) {

	waveObj->forwardStepRev( container, len );
      }
      else {

	waveObj->forwardStep( container, len );
      }

      packnode<int> *lhs = new packnode<int>(container.lhsData(),
						   len/2,
						   packnode<int>::LowPass );
      packnode<int> *rhs = new packnode<int>(container.rhsData(),
						   len/2,
						   packnode<int>::HighPass );

      top->mark( false );
      lhs->mark( true );
      rhs->mark( true );

      top->lhsChild( lhs );
      top->rhsChild( rhs );

      newLevel( lhs, freqCalc, false );

      if (freqCalc) {

	newLevel( rhs, freqCalc, true );
      }
      else {
	newLevel( rhs, freqCalc, false );
      }
    }
  }
}

void packtree_base_int::breadthFirstPrint(const printKind kind)
{
  queue<int> Q;

  Q.addQueue( root, 0 );
  while (! Q.queueEmpty() ) {
    packnode<int> *node = Q.queueStart()->node;
    size_t indent = Q.queueStart()->indent;
    Q.deleteStart();

    if (indent > 0) {
      printf("%*c", indent, ' ');
    }

    switch (kind) {
    case printData: node->pr();
      break;
    case printCost: node->prCost();
      break;
    case printBestBasis: node->prBestBasis();
      break;
    default:
      assert( false );
      break;
    } // switch

    packnode<int> *lhs = node->lhsChild();
    packnode<int> *rhs = node->rhsChild();

    if (lhs != 0) {
      Q.addQueue( lhs, indent + 2 );
    }
    if (rhs != 0) {
      Q.addQueue( rhs, indent + 2 );
    }
  }
}

void packtree_base_int::pr()
{
  if (root != 0) {
    breadthFirstPrint(printData);
  }
}
