
#ifndef _COSTBASE_INT_H_
#define _COSTBASE_INT_H_

#include "packnode.h"

class costbase_int
{
private:
  /** disallow the copy constructor */
  costbase_int( const costbase_int &rhs ) {}

protected:

  void traverse( packnode<int> *node )
  {
    if (node != 0) {
      int cost = costCalc( node );
      node->cost( cost );

      traverse( node->lhsChild() );
      traverse( node->rhsChild() );
    }
  }

  virtual int costCalc(packnode<int> *node) = 0;

public:
  costbase_int() {}

};

#endif
