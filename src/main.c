#include "my_malloc.h"

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

int main(int argc, char const **argv)
{
	test();

	return 0;
}