#include "cfree.h"
#include "cmalloc.h"
#include "rbtree.h"

extern rbtree *tree;

void delete_references(void *ptr)
{
	for(size_t i = 0; i < REF_COUNT; ++i)
	{
		if(references[i] == ptr)
		{
			references[i] = NULL;
		}
	}
}

void cfree(void *ptr, uint32_t flag)
{
	if(!flag)
	{
		delete_references(ptr);
	}

	ptr = *(size_t *)ptr;

	mem_chunk *chunk_for_free = NULL;

	size_t size = *(size_t *)(ptr - USER_SEG_OFFSET);

	chunk_for_free = rbtree_lookup_chunk_for_free(tree, size, ptr);

	if (chunk_for_free)
	{
		*chunk_for_free->is_used = 0;
	}
}