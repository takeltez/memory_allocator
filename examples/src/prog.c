#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <inttypes.h>
#include <time.h> 

int main(int argc, char const **argv)
{
	void *handle = dlopen("../lib/dlib/libmalloc.so", RTLD_LAZY);

	void *(*cmalloc)(size_t size, void *ptr) = dlsym(handle, "cmalloc");
	void *(*cfree)(void *ptr, uint32_t flag) = dlsym(handle, "cfree");

	int *ptr1[1000];
	int *ptr2[1000];

	srand(time(NULL));

	clock_t start, end;

	start = clock();

	for(size_t i = 0; i < 1000; ++i)
	{
		ptr1[i] = malloc(rand() % 100 + 1);
	}

	end = clock();

	printf("standart malloc total time: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

	start = clock();

	for(size_t i = 0; i < 1000; ++i)
	{
		cmalloc(rand() % 100 + 1, ptr2 + i);
	}

	end = clock();

	printf("cmalloc total time: %f seconds\n\n", (double)(end - start) / CLOCKS_PER_SEC);

	start = clock();

	for(size_t i = 0; i < 1000; ++i)
	{
		free(ptr1[i]);
	}

	end = clock();

	printf("standart free total time: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

	start = clock();

	for(size_t i = 0; i < 1000; ++i)
	{
		cfree(ptr2 + i, 0);
	}

	end = clock();

	printf("cfree total time: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

	dlclose(handle);

	return 0;
}