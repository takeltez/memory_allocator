#include "my_malloc.h"

uint32_t call_ind = 0;

void chunk_disp(int32_t i, int32_t j)
{
	size_t size =  *chunk_list[i + 1].size; 
	uint32_t is_used = *chunk_list[i + 1].is_used; 

	if (j == -1)
	{
		chunk_list[i + 1].ptr = heap_start_ptr;
	}
	else
	{
		chunk_list[i + 1].ptr = chunk_list[j].ptr + *chunk_list[j].size;
	}

	chunk_list[i + 1].size = (size_t *)chunk_list[i + 1].ptr;
	chunk_list[i + 1].is_used = (uint32_t *)chunk_list[i + 1].ptr + OFFSET_TO_IS_USED_SEG;
	
	*chunk_list[i + 1].size = size;
	*chunk_list[i + 1].is_used = is_used;

	for (int32_t k = i + 2; k < call_ind; ++k)
	{
		if (!chunk_list[k].ptr)
		{
			continue;
		}

		size = *chunk_list[k].size; 
		is_used = *chunk_list[k].is_used; 

		int32_t q;

		for (q = k - 1; !chunk_list[q].ptr; --q);

		chunk_list[k].ptr = chunk_list[q].ptr + *chunk_list[q].size;

		chunk_list[k].size = (size_t *)chunk_list[k].ptr;
		chunk_list[k].is_used = (uint32_t *)chunk_list[k].ptr + OFFSET_TO_IS_USED_SEG;
		
		*chunk_list[k].size = size;
		*chunk_list[k].is_used = is_used;
	}
}

uint32_t count_last_free_chunks(int32_t i)
{
	uint32_t last_free_chunks_counter = 0;

	for (; !(*chunk_list[i].is_used); --i)
	{	
		if (!i)
		{
			break;
		}

		++last_free_chunks_counter;
	}

	return last_free_chunks_counter;
}

void *set_chunk_start_ptr(uint32_t last_free_chunks_counter)
{
	void *chunk_start_ptr = heap_start_ptr;

	for (size_t i = 0; i < call_ind - last_free_chunks_counter; ++i)
	{
		if (chunk_list[i].ptr)
		{
			chunk_start_ptr += *chunk_list[i].size;
		}
	}

	return chunk_start_ptr;
}

void *elim_fragm(void)
{
	uint32_t last_free_chunks_counter;

	for (int32_t i = call_ind - 1; i >= 0; --i)
	{
		if (!(*chunk_list[i].is_used))
		{
			if (i == call_ind - 1)
			{
				last_free_chunks_counter = count_last_free_chunks(i);

				i -= last_free_chunks_counter; 

				continue;
			}

			if (!i)
			{		
				chunk_disp(i, -1);
			}

			for (int32_t j = i - 1; j >= 0; --j)
			{
				if (j == 0 && !(*chunk_list[j].is_used))
				{
					chunk_disp(i, -1);
				}

				else if (*chunk_list[j].is_used)
				{
					chunk_disp(i, j);

					break;
				}

				*chunk_list[j].is_used = 1;
			}
		}
	}

	return set_chunk_start_ptr(last_free_chunks_counter);
}

void *my_malloc(size_t size)
{
	void *chunk_user_ptr;
	void *chunk_start_ptr;

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
		chunk_start_ptr = elim_fragm();
	}

	chunk_list[call_ind].ptr = chunk_start_ptr;
	chunk_list[call_ind].size = (size_t *)chunk_start_ptr;
	chunk_list[call_ind].is_used = (uint32_t *)chunk_start_ptr + OFFSET_TO_IS_USED_SEG;

	*chunk_list[call_ind].size = size;
	*chunk_list[call_ind].is_used = 1;

	chunk_user_ptr = chunk_start_ptr + OFFSET_TO_USER_SEG;

	++call_ind;

	return chunk_user_ptr;
}

void my_free(void *ptr)
{
	for (size_t i = 0; i < call_ind; ++i)
	{
		if (chunk_list[i].ptr == ptr - OFFSET_TO_USER_SEG)
		{
			*chunk_list[i].size = 0;
			*chunk_list[i].is_used = 0;

			 chunk_list[i].ptr = NULL;
			 chunk_list[i].size = NULL;

			 size_t *item = (size_t*)ptr;
			 
			 *item = 0;

			 ptr = NULL;
		}
	}
}

void chunk_log(void)
{
	for (size_t i = 0; i < call_ind; ++i)
	{
		if (chunk_list[i].ptr) 
		{
			printf("Chunk %ld: meta segment: [%p], chunk size - %ld, user segment: [%p]\n", 
					i, chunk_list[i].ptr, *chunk_list[i].size, chunk_list[i].ptr + OFFSET_TO_USER_SEG);
		}
		else
		{
			printf("Chunk %ld: meta segment: [%p]\n", i, chunk_list[i].ptr);
		}
	}
}