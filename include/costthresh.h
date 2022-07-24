
#ifndef _COSTTHRESH_H_
#define _COSTTHRESH_H_

#include "costbase.h"
#include "packnode.h"

class costthresh : public costbase
{
private:
  /** cost threshold */
  double thresh;

  /** absolute value */
  double abs(const double x)
  {
    double retval = x;
    if (retval < 0.0)
      retval = -retval;
    return retval;
  } // abs

protected:


  double costCalc(packnode<double> *node)
  {
    double count = 0.0;
    if (node != 0) {
      size_t len = node->length();
      for (int i = 0; i < len; i++) {
	if (abs((*node)[i]) > thresh) {
	  count = count + 1.0;
	}
      }
    }
    return count;
  } // costCalc

public:

  costthresh(packnode<double> *node, double t )
  {
    thresh = t;
    traverse( node );
  }
}; // costthresh

#endif
