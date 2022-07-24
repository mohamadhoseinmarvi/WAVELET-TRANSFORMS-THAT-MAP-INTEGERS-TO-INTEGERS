
#ifndef _COSTWIDTH_H_
#define _COSTWIDTH_H_

#include "costbase_int.h"

class costwidth : public costbase_int
{
protected:
  int costCalc( packnode<int> *root );
public:
  costwidth( packnode<int> *root ) { traverse( root ); }
};

#endif
