
#ifndef _COSTSHANNON_H_
#define _COSTSHANNON_H_

#include "costbase.h"
#include "packnode.h"

class costshannon : public costbase
{
protected:
  double costCalc( packnode<double> *node);

public:

  costshannon( packnode<double> *node ) { traverse( node ); }
};

#endif
