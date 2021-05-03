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
	uint32_t *is_used;
	
	if(!flag)
	{
		delete_references(ptr);
	}
	
	ptr = *(size_t *)ptr;

	is_used = (uint32_t *)(ptr - IS_USED_SEG_OFFSET);

	*is_used = 0;
}