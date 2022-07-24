
#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "fifo_list.h"
#include "packnode.h"
template <class T>
class queueElem
{
private:
  queueElem() {}
public:
  packnode<T> *node;
  size_t indent;
  queueElem( packnode<T> *n, size_t i )
  {
    node = n;
    indent = i;
  }
  void *operator new(size_t num_bytes)
  {
    block_pool mem_pool;

    void *mem_addr = mem_pool.pool_alloc( num_bytes );
    return mem_addr;
  }
};
template <class T>
class queue : protected FIFO_LIST<queueElem<T> *>
{
public:
  queueElem<T> *queueStart()
  {
    handle h = first();
    queueElem<T> *elem = get_item( h );
    return elem;
  }
  void deleteStart()
  {
    handle h = first();
    if (h != 0) {
      queueElem<T> *elem = get_item( h );
      remove();

    }
  }
  void addQueue(packnode<T> *node, size_t indent )
  {
    queueElem<T> *elem = new queueElem<T>(node, indent);
    add( elem );
  }

  bool queueEmpty() { return (first() == 0); }
};

#endif
