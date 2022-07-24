

#ifndef _PACKDATA_LIST_H_
#define _PACKDATA_LIST_H_

#include "fifo_list.h"
#include "packdata.h"

template <class T>
class packdata_list : public FIFO_LIST<packdata<T> *>
{
public:

  void pr()
  {
    handle h;
    packdata<T> *elem;

    for (h = first(); h != 0; h = next( h )) {
      elem = get_item( h );
      elem->pr();
    } // for h
    printf("\n");
  } // pr

};


#endif
