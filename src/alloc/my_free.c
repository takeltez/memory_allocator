#include "my_free.h"
#include "my_malloc.h"
#include "rbtree.h"

extern rbtree *tree;

void my_free(void *ptr)
{
	rbtree *found_node = NULL; 

	size_t size = *((size_t *)(ptr - OFFSET_TO_USER_SEG));

	found_node = rbtree_lookup_chunk_for_free(tree, size, ptr);

	if (found_node)
	{
		mem_chunk chunk_for_free = *found_node->chunk_ptr;

		*chunk_for_free.is_used = 0;

		size_t *item = (size_t*)ptr;
			 
		*item = 0;

		ptr = NULL;
	}
}