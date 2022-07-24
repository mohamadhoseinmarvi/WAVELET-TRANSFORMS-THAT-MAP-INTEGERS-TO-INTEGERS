#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "blockpool.h"


size_t block_pool::alloc_gran = (size_t)block_pool::page_size;
block_pool::block_chain *block_pool::current_block = 0;
block_pool::block_chain *block_pool::block_list_start = 0;

void block_pool::init_pool( void )
{

  block_chain *new_link;

  new_link = new_block( alloc_gran );
  block_list_start = new_link;
  current_block = new_link;
}

block_pool::block_chain *block_pool::new_block( size_t block_size )
{
  const size_t max_block_size = max_block_multiple * page_size;
  block_chain *new_link = 0;
  size_t alloc_amt, total_alloc;

  total_alloc = block_size + sizeof(block_chain);
  if (total_alloc < alloc_gran)
      alloc_amt = alloc_gran;
  else {

      alloc_amt = ((total_alloc + (page_size-1))/page_size) * page_size;
  }

  if (alloc_amt <= max_block_size) {

    new_link = (block_chain *)MemAlloc( alloc_amt );

    Chain_block(new_link) = (void *)(((size_t)new_link) + sizeof(block_chain));

    assert( alloc_amt >= block_size );

    Chain_bytes_used(new_link) = 0;
    Chain_block_size(new_link) = alloc_amt - sizeof(block_chain);
    Chain_next(new_link) = 0;
  }
  else {
    printf("block_pool::new_block: allocation request too large\n");
  }

  return new_link;
}

void *block_pool::add_block( size_t block_size )
{
  block_chain *block = 0;
  block_chain *last_block;

  last_block = current_block;
  block = new_block( block_size );
  Chain_next(current_block) = block;
  current_block = block;

  return (void *)block;
}

void *block_pool::pool_alloc( size_t num_bytes )
{
  const size_t align = sizeof( size_t );
  void *addr = 0;
  size_t amt_free;

  num_bytes = ((num_bytes + (align-1))/align) * align;

  if (current_block == 0) {
    init_pool();
  }

  amt_free = Chain_block_size(current_block) - Chain_bytes_used(current_block);

  if (num_bytes > amt_free) {
    if (add_block( num_bytes ) != 0) {
      amt_free = Chain_block_size(current_block);
    }
  }

  if (amt_free >= num_bytes) {
    addr = (void *)((size_t)Chain_block(current_block) + Chain_bytes_used(current_block));
    Chain_bytes_used(current_block) += num_bytes;
  }
  else {
    printf("block_pool::block_alloc: allocation error\n");
    exit(1);
  }
  return addr;
}

void block_pool::free_pool(void)
{
  block_chain *tmp;

  while (block_list_start != 0) {
    tmp = block_list_start;
    block_list_start = Chain_next(block_list_start);
    MemFree( (void *)tmp );
  }
}

void block_pool::print_block_pool_info( FILE *fp /*= stdout */)
{
  size_t total_allocated = 0;
  size_t total_unused = 0;
  block_chain *ptr = block_list_start;

  fprintf(fp, "Minimum memory allocation size: %d\n", alloc_gran );
  fprintf(fp, "Page size: %d\n", (size_t)page_size );
  fprintf(fp, "[block size, bytes_used]\n");
  while (ptr != 0) {
    fprintf(fp, "[%4d, %4d]", Chain_block_size(ptr), Chain_bytes_used(ptr));
    total_allocated += Chain_bytes_used(ptr);
    total_unused += (Chain_block_size(ptr) - Chain_bytes_used(ptr));
    if (Chain_next(ptr) != 0) {
      fprintf(fp, ", ");
    }
    else {
      fprintf(fp, "\n");
    }
    ptr = Chain_next(ptr);
  } 
  fprintf(fp, "Total allocated = %5d, total unused = %3d\n", total_allocated,
	 total_unused );
}
