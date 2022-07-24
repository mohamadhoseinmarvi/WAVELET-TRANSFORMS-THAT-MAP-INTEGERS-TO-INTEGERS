
#ifndef _INVPACKTREE_INT_H_
#define _INVPACKTREE_INt_H_

#include "liftbase.h"
#include "list.h"
#include "packcontainer_int.h"
#include "packdata.h"
#include "packdata_list.h"

class invpacktree_int {
private:
  liftbase<packcontainer_int, int> *waveObj;
  invpacktree_int( const invpacktree_int &rhs ) {}

  LIST<packcontainer_int *> stack;

  const int *data;

  size_t N;

private:
  void new_level( packdata<int> *elem );
  void add_elem( packdata<int> *elem );
  void reduce();

public:
  invpacktree_int( packdata_list<int> &list,
		   liftbase<packcontainer_int, int> *w );
  ~invpacktree_int() {}

  const int *getData() { return data; }
  void pr();
};

#endif
