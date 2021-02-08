#include "chunk_handler.h"
#include "my_malloc.h"

extern uint32_t call_ind;

void *set_chunk_start_ptr()
{
	void *chunk_start_ptr = heap_start_ptr;

	for (size_t i = 0; i < call_ind; ++i)
	{
		chunk_start_ptr += *chunk_list[i].size;
	}

	return chunk_start_ptr;
}

void *free_chunks_cover(uint32_t *is_free_chunk_avl, size_t size)
{
	for (int32_t i = call_ind - 1; i >= 0; --i)
	{
		if ((!(*chunk_list[i].is_used)) && (*chunk_list[i].size == size))
		{
			*is_free_chunk_avl = 1;
			*chunk_list[i].is_used = 1;

			return chunk_list[i].ptr;
		}
	}

	return set_chunk_start_ptr();
}