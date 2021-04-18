#include "chunk_handler.h"
#include "cmalloc.h"
#include "rbtree.h"

extern rbtree *tree;

void *free_chunks_reuse(size_t size)
{
	mem_chunk *free_chunk = NULL;
	
	free_chunk = rbtree_lookup_freed_chunk(tree, size);

	if (free_chunk)
	{
		*free_chunk->size = size;
		*free_chunk->is_used = 1;

		return free_chunk->ptr;
	}

	return NULL;
}