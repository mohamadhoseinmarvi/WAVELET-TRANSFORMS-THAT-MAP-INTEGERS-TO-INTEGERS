
#ifndef _INVPACKTREE_H_
#define _INVPACKTREE_H_

#include "liftbase.h"
#include "list.h"
#include "packcontainer.h"
#include "packdata.h"
#include "packdata_list.h"

class invpacktree {
private:

  liftbase<packcontainer, double> *waveObj;

  invpacktree( const invpacktree &rhs ) {}

  LIST<packcontainer *> stack;

  const double *data;
  size_t N;

private:
  void new_level( packdata<double> *elem );
  void add_elem( packdata<double> *elem );
  void reduce();

public:
  invpacktree( packdata_list<double> &list,
	       liftbase<packcontainer, double> *w );
  ~invpacktree() {}
  const double *getData() { return data; }
  void pr();
};

#endif
