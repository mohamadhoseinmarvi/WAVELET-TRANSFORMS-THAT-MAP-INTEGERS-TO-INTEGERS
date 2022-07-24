
#ifndef _COSTBASE_H_
#define _COSTBASE_H_

#include "packnode.h"

class costbase
{
private:
  /** disallow the copy constructor */
  costbase( const costbase &rhs ) {}

protected:

  void traverse( packnode<double> *node )
  {
    if (node != 0) {
      double cost = costCalc( node );
      node->cost( cost );

      traverse( node->lhsChild() );
      traverse( node->rhsChild() );
    }
  } // traverse

  /** Cost function to be defined by the subclass */
  virtual double costCalc(packnode<double> *node) = 0;

public:
  /** The default constructor does nothing */
  costbase() {}

}; // costbase

#endif
