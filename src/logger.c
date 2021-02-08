#include "logger.h"
#include "my_free.h"
#include "my_malloc.h"

extern uint32_t call_ind;

void chunk_log(void)
{
	for (size_t i = 0; i < call_ind; ++i)
	{
		printf("Chunk %ld: meta segment: [%p], chunk size - %ld, is used - %u, user segment: [%p]\n", 
				i, chunk_list[i].ptr, *chunk_list[i].size, *chunk_list[i].is_used, chunk_list[i].ptr + OFFSET_TO_USER_SEG);
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

	second = my_malloc(200);
	third = my_malloc(50);
	sixth = my_malloc(30);

	void *seventh = my_malloc(40);

	printf("\nChunks states after using free blocks again:\n");

	chunk_log();
}