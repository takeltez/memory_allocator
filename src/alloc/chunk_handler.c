#include "chunk_handler.h"
#include "my_malloc.h"
#include "rbtree.h"

extern rbtree *tree;

void *free_chunks_cover(size_t size)
{
	rbtree *found_node = NULL; 

	found_node = rbtree_lookup_freed_chunk(tree, size);
	
	if (found_node)
	{
		mem_chunk free_chunk = *found_node->chunk_ptr;

		*free_chunk.is_used = 1;

		return free_chunk.ptr;
	}

	return NULL;
}