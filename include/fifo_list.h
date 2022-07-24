
#ifndef FIFO_LIST_H
#define FIFO_LIST_H

#include "blockpool.h"


template <class T>
class FIFO_LIST
{
public:

    class list_type {
    public:

        T data;

        list_type *next;

        void *operator new(size_t num_bytes)
        {
          block_pool mem_pool;

          void *mem_addr = mem_pool.pool_alloc( num_bytes );
          return mem_addr;
        }
    };

private:

  list_type *list;

  list_type *tail;

public:

  typedef list_type *handle;

public:

  FIFO_LIST(void)
  {
    list = 0;
    tail = 0;
  }

  ~FIFO_LIST(void) {}


  /** deallocate the list */
  void dealloc(void)
  {
    while ( remove() != 0 )
      /* nada */;
  } // dealloc


  /** add an element to the FIFO list */
  void add( T data )
  {
    list_type *t;

    t = new list_type();
    t->data = data;
    t->next = 0;
    if (list == 0) {
      list = t;
      tail = t;
    }
    else {
      tail->next = t;
      tail = t;
    }
  }  // add


  /** reverse the list */
  void reverse(void)
  {
    list_type *elem, *prev, *next;

    prev = 0;
    next = 0;

    tail = list;
    for (elem = list; elem != 0; prev = elem, elem = next) {
      next = elem->next;
      elem->next = prev;
    } // for
    list = prev;
  }  // reverse


  /** return the lenght of the list */
  size_t length(void)
  {
      list_type *elem;
      size_t cnt = 0;

      for (elem = list; elem != 0; elem = elem->next)
          cnt++;
      return cnt;
  }  // lenght

  handle remove(void)
  {
    list_type *t;

    if (list != 0) {
      t = list;
      list = t->next;
      // no delete t;
    }

    if (list == 0)
        tail = 0;

    return list;
  } // remove

  T get_item( handle h)
  {

    return h->data;
  } // get_item


  /** get the first element from the list */
  handle first(void)
  {
    return list;
  } // first

  handle last(void)
  {
    return tail;
  } // last

  handle next(handle h)
  {
    list_type *next = 0;

    if (h != 0) {
        next = h->next;
    }

    return next;
  } // next

};  // template class FIFO_LIST


#endif
