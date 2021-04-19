#include "cmalloc.h"
#include "chunk_handler.h"
#include "rbtree.h"
#include "cfree.h"

rbtree empty_node = {0, 0, {NULL}, NODE_BLACK, NULL, NULL, NULL};
rbtree *null_node = &empty_node;
rbtree *tree = NULL;

void cmalloc(size_t size, void *ptr)
{	
	void *chunk_user_ptr;
	void *chunk_start_ptr;

	static void *last_chunk_ptr;

	static uint32_t call_ind = 0;
	static size_t free_space = HEAP_SIZE;

	assert(size > 0);

	size += USER_SEG_OFFSET;

	if(free_space < size)
	{	
		chunk_start_ptr = sbrk(size);
		
		free_space = size;
	}
	else
	{
		free_space -= size;
	}

	count_references(ptr);

	if(!call_ind)
	{
		chunk_start_ptr = sbrk(HEAP_SIZE);
	}
	else
	{

		chunk_start_ptr = free_chunks_reuse(size);

		if(chunk_start_ptr)
		{
			chunk_user_ptr = chunk_start_ptr + USER_SEG_OFFSET;

			*(size_t *)ptr = chunk_user_ptr;

			return;
		}
		else
		{
			chunk_start_ptr = last_chunk_ptr;
		}
	}

	chunk_list[call_ind].ptr = chunk_start_ptr;
	chunk_list[call_ind].size = (size_t *)chunk_start_ptr;
	chunk_list[call_ind].is_used = (uint32_t *)chunk_start_ptr + SIZE_SEG_OFFSET;

	*chunk_list[call_ind].size = size;
	*chunk_list[call_ind].is_used = 1;

	chunk_user_ptr = chunk_start_ptr + USER_SEG_OFFSET;
	last_chunk_ptr = chunk_start_ptr + size;

	tree = rbtree_add(tree, chunk_list + call_ind);

	*(size_t *)ptr = chunk_user_ptr;
	
	++call_ind;

}

void count_references(void *ptr)
{
	for(size_t i = 0; i < REF_COUNT; ++i)
	{
		if(references[i] == ptr)
		{	
			cfree(ptr, 1);

			return;
		}
	}

	for(size_t i = 0; i < REF_COUNT; ++i)
	{
		if(references[i] == NULL)
		{
			references[i] = ptr;
			
			break;
		}
	}
}
