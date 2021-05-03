#include "cmalloc.h"
#include "chunk_handler.h"
#include "rbtree.h"
#include "cfree.h"

rbtree empty_node = {0, 0, {NULL}, NODE_BLACK, NULL, NULL, NULL};
rbtree *null_node = &empty_node;
rbtree *tree = NULL;

void cmalloc(size_t size, void *ptr)
{	
	assert(size > 0);

	void *user_seg_ptr;
	void *service_seg_ptr;

	static void *left_memory_ptr;

	static size_t call_ind = 0;
	static size_t free_space = HEAP_SIZE;

	size += USER_SEG;

	if(free_space < size)
	{	
		service_seg_ptr = sbrk(size);
		
		free_space = size;
	}
	else
	{
		free_space -= size;
	}

	count_references(ptr);

	if(!call_ind)
	{
		service_seg_ptr = sbrk(HEAP_SIZE);
	}
	else
	{

		service_seg_ptr = free_chunks_reuse(size);

		if(service_seg_ptr)
		{
			user_seg_ptr = service_seg_ptr + USER_SEG;

			*(size_t *)ptr = user_seg_ptr;

			return;
		}
		else
		{
			service_seg_ptr = left_memory_ptr;
		}
	}

	chunk_list[call_ind].ptr = service_seg_ptr;
	chunk_list[call_ind].size = (size_t *)service_seg_ptr;
	chunk_list[call_ind].is_used = (uint32_t *)(service_seg_ptr + SIZE_SEG);

	*chunk_list[call_ind].size = size;
	*chunk_list[call_ind].is_used = 1;

	user_seg_ptr = service_seg_ptr + USER_SEG;
	left_memory_ptr = service_seg_ptr + size;

	tree = add_chunk(tree, chunk_list + call_ind);

	*(size_t *)ptr = user_seg_ptr;
	
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
