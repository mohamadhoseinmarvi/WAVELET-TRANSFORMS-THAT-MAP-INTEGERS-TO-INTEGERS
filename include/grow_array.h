
#ifndef _GROW_ARRAY_H_
#define _GROW_ARRAY_H_

#include "blockpool.h"

template <class T>
class GrowableArray {
private:
  typedef enum { StartArraySize = 128 } bogus;
  /** number of data elements */
  size_t num_elem;
  /** Array size (always <= num_elem) */
  size_t array_size;
  T *pArray;

private:

  bool twice()
  {
    bool rslt;
    T *old_array = pArray;
    size_t new_size = array_size * 2;

    pArray = new T [ new_size ];
    if (pArray != 0) {
      rslt = true;
      for (int i = 0; i < array_size; i++) {
	pArray[i] = old_array[i];
      }

      delete [] old_array;

      array_size = new_size;
    }
    else {
      rslt = false;
    }

    return rslt;
  } // twice


public:
  GrowableArray()
  {
    pArray = new T[ StartArraySize ];
    num_elem = 0;
    array_size = StartArraySize;
  }

  ~GrowableArray()
  {
    if (pArray != NULL) {
      delete [] pArray;
    }
  }

  const size_t length(void) const { return num_elem; }

  void set_to_zero()
  {
    num_elem = 0;
  }

  T &operator[](const size_t i)
  {
    assert( i < num_elem );
    return pArray[ i ];
  }

  T operator[](const size_t i ) const
  {
    assert( i < num_elem );
    return pArray[ i ];
  }

  const T *getData() const { return pArray; }

  /** append an item to the end of the array */
  void append( T item )
  {

    if (num_elem == array_size) {
      bool allocOK = twice();
      assert( allocOK );
    }

    pArray[ num_elem ] = item;
    num_elem++;
  }

  void expand( size_t amount )
  {
    bool allocOK = true;

    while (allocOK && num_elem + amount >= array_size) {
      allocOK = twice();
      assert( allocOK );
    }
    num_elem += amount;
  }

  void remove(void)
  {
    if (num_elem > 0)
      num_elem--;
  }

};

#endif
