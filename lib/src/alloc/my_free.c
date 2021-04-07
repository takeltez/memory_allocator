#include "my_free.h"
#include "my_malloc.h"
#include "rbtree.h"

extern rbtree *tree;

void delete_references(void *ptr)
{
	for(size_t i = 0; i < REF_COUNT; ++i)
	{
		if(references[i] == ptr)
		{
			references[i] = NULL;
			ref_vals[i] = NULL;
		}
	}
}

void count_references(void *ptr)
{
	for(size_t i = 0; i < REF_COUNT; ++i)
	{
		if(references[i] == ptr)
		{
			my_free(ref_vals[i]);

			ref_vals[i] = *(size_t *)ptr;

			return;
		}
	}

	for(size_t i = 0; i < REF_COUNT; ++i)
	{
		if(references[i] == NULL)
		{	
			references[i] = ptr;
			ref_vals[i] = *(size_t *)ptr;

			break;
		}
	}
}

void my_free(void *ptr)
{
	size_t *item;

	mem_chunk *chunk_for_free = NULL;

	size_t size = *(size_t *)(ptr - OFFSET_TO_USER_SEG);

	chunk_for_free = rbtree_lookup_chunk_for_free(tree, size, ptr);

	if (chunk_for_free)
	{
		*chunk_for_free->is_used = 0;

		item = (size_t *)ptr;

		*item = 0;

		ptr = NULL;
	}
}