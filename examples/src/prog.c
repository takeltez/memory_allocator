#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <inttypes.h>
#include <assert.h>
#include <time.h>

int main(int argc, char const **argv)
{
	void *handle = dlopen("../lib/dlib/libmalloc.so", RTLD_LAZY);

	void (*cmalloc)(size_t size, void *ptr) = dlsym(handle, "cmalloc");
	void (*cfree)(void *ptr) = dlsym(handle, "cfree");

	assert(argc > 1);

	int n = atoi(argv[1]);

	int *ptr1[n];
	int *ptr2[n];

	srand(time(NULL));

	clock_t start, end;

	start = clock();

	for(size_t i = 0; i < n; ++i)
	{
		ptr1[i] = malloc(rand() % 100 + 1);
	}

	end = clock();

	printf("standart malloc total time(%d elements): %f seconds\n", n, (double)(end - start) / CLOCKS_PER_SEC);

	start = clock();

	for(size_t i = 0; i < n; ++i)
	{
		cmalloc(rand() % 100 + 1, ptr2 + i);
	}

	end = clock();

	printf("cmalloc total time(%d elements): %f seconds\n\n", n, (double)(end - start) / CLOCKS_PER_SEC);

	start = clock();

	for(size_t i = 0; i < n; ++i)
	{
		free(ptr1[i]);
	}

	end = clock();

	printf("standart free total time(%d elements): %f seconds\n", n, (double)(end - start) / CLOCKS_PER_SEC);

	start = clock();

	for(size_t i = 0; i < n; ++i)
	{
		cfree(ptr2 + i);
	}

	end = clock();

	printf("cfree total time(%d elements): %f seconds\n", n, (double)(end - start) / CLOCKS_PER_SEC);

	dlclose(handle);

	return 0;
}