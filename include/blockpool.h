
#ifndef _BLOCKPOOL_H_
#define _BLOCKPOOL_H_

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

class block_pool {
public:
  typedef enum { one_kay = 1024,
		 page_size = (4 * one_kay),
		 max_block_multiple = 256,
		 last_enum
	       } bogus;

  typedef struct block_chain_struct {
    void *block;
    size_t bytes_used;

    /** total block size */
    size_t block_size;

    /** pointer to the next block */
    block_chain_struct *next_block;
  } block_chain;

private:
  /** allocation granularity */
  static size_t alloc_gran;

  /** start of the block list for this pool */
  static block_chain *block_list_start;

  /** current block memory is being allocated from */
  static block_chain *current_block;


private: // class functions
  block_chain *new_block( size_t block_size );
  void *add_block( size_t block_size );
  void init_pool(void);


protected:
  virtual void *MemAlloc( size_t n_bytes )
  {
    void *rtn = calloc( n_bytes, 1 );
    return rtn;
  }
  /**
    Free memory that has been allocated with MemAlloc
   */
  virtual void MemFree( void *addr )
  {
    free( addr );
  }


public: 

  block_pool(void) {}

  void free_pool(void);
  void *pool_alloc( size_t block_size );
  void print_block_pool_info( FILE *fp = stdout );

};

#define Chain_block(p)            ((p)->block)

/** return the number of bytes used */
#define Chain_bytes_used(p)       ((p)->bytes_used)

/** return the size of the memory block */
#define Chain_block_size(p)       ((p)->block_size)

/** return the next block_chain structure in the list */
#define Chain_next(p)             ((p)->next_block)


#endif
