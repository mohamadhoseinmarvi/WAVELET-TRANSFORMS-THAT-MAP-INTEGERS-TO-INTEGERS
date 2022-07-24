#include "queue.h"
#include "packnode.h"
#include "packcontainer.h"
#include "packtree_base.h"

void packtree_base::newLevel( packnode<double>* top,
			      bool freqCalc,
			      bool reverse )
{
  if (top != 0) {
    const size_t len = top->length();
    if (len > 1) {
      packcontainer container( top );

      if (reverse) {
	waveObj->forwardStepRev( container, len );
      }
      else {
	waveObj->forwardStep( container, len );
      }

      packnode<double> *lhs = new packnode<double>(container.lhsData(),
						   len/2,
						   packnode<double>::LowPass );
      packnode<double> *rhs = new packnode<double>(container.rhsData(),
						   len/2,
						   packnode<double>::HighPass );
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
void packtree_base::breadthFirstPrint(const printKind kind)
{
  queue<double> Q;

  Q.addQueue( root, 0 );
  while (! Q.queueEmpty() ) {
    packnode<double> *node = Q.queueStart()->node;
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
    }

    packnode<double> *lhs = node->lhsChild();
    packnode<double> *rhs = node->rhsChild();

    if (lhs != 0) {
      Q.addQueue( lhs, indent + 2 );
    }
    if (rhs != 0) {
      Q.addQueue( rhs, indent + 2 );
    }
  }
}

void packtree_base::pr()
{
  if (root != 0) {
    breadthFirstPrint(printData);
  }
}
