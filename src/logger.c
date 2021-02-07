#include "logger.h"
#include "my_free.h"
#include "my_malloc.h"

extern uint32_t call_ind;

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

void test(void)
{
	void *first = my_malloc(100);
	void *second = my_malloc(10);
	void *third = my_malloc(50);
	void *fourth = my_malloc(150);
	void *fiveth = my_malloc(40);
	void *sixth = my_malloc(30);

	printf("Chunks states before my_free:\n");

	chunk_log();

	printf("\nChunks states after my_free:\n");

	my_free(second);
	my_free(third);
	my_free(fiveth);
	my_free(sixth);
	
	chunk_log();

	void *seventh = my_malloc(130);

	printf("\nChunks states after displacements:\n");

	chunk_log();
}