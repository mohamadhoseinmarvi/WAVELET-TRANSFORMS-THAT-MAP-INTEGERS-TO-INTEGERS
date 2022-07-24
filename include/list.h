
#ifndef _LIST_H_
#define _LIST_H_

template <class T>
class LIST
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

public:
  typedef list_type *handle;

public:
  LIST(void)
  {
    list = 0;
  }

  LIST( const LIST<T> &rhs )
  {
    list = rhs.list;
  }

  ~LIST() {}

  void dealloc(void)
  {
    while ( remove() != 0 )
      /* nada */;
  } // dealloc

  void add( T data )
  {
    list_type *t;

    t = new list_type();
    t->data = data;
    t->next = 0;
    if (list == 0) {
      list = t;
    }
    else {
      t->next = list;
      list = t;
    }
  }

  void reverse(void)
  {
    list_type *revlist = 0;
    list_type *next;

    for (list_type *t = list; t != 0; t = next) {
        next = t->next;
        t->next = revlist;
        revlist = t;
    }
    list = revlist;
  }

  size_t length(void)
  {
      list_type *elem;
      size_t cnt = 0;

      for (elem = list; elem != 0; elem = elem->next)
          cnt++;
      return cnt;
  }

  handle remove(void)
  {
    list_type *t;

    if (list != 0) {
      t = list;
      list = t->next;

    }
    return list;
  }

  T get_item( handle h)
  {

    return h->data;
  }

  handle first(void)
  {
    return list;
  }

  handle next(handle h)
  {
    list_type *next = 0;

    if (h != 0) {
        next = h->next;
    }

    return next;
  } // next

};  


#endif
