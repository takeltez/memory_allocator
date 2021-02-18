#include "my_malloc.h"
#include "chunk_handler.h"
#include "rbtree.h"

uint32_t call_ind = 0;

rbtree empty_node = {0, NODE_BLACK, NULL, NULL, NULL };
rbtree *null_node = &empty_node;
rbtree *tree = NULL;

void *my_malloc(size_t size)
{
	void *chunk_user_ptr;
	void *chunk_start_ptr;

	static void *last_chunk_ptr;
	static size_t free_space = HEAP_SIZE;

	assert(size > 0);

	size += OFFSET_TO_USER_SEG;

	free_space -= size;

	if (free_space < size)
	{
		chunk_start_ptr = sbrk(size);
	}

	if (!call_ind)
	{
		heap_start_ptr = sbrk(HEAP_SIZE);
		chunk_start_ptr = heap_start_ptr;
	}
	else
	{
		chunk_start_ptr = free_chunks_reuse(size);
		
		if (chunk_start_ptr)
		{
			chunk_user_ptr = chunk_start_ptr + OFFSET_TO_USER_SEG;

			return chunk_user_ptr;
		}
		else
		{
			chunk_start_ptr = last_chunk_ptr;
		}
	}

	chunk_list[call_ind].ptr = chunk_start_ptr;
	chunk_list[call_ind].size = (size_t *)chunk_start_ptr;
	chunk_list[call_ind].is_used = (uint32_t *)chunk_start_ptr + OFFSET_TO_IS_USED_SEG;

	*chunk_list[call_ind].size = size;
	*chunk_list[call_ind].is_used = 1;

	chunk_user_ptr = chunk_start_ptr + OFFSET_TO_USER_SEG;
	last_chunk_ptr = chunk_start_ptr + size;

	tree = rbtree_add(tree, chunk_list + call_ind);

	++call_ind;

	return chunk_user_ptr;
}

