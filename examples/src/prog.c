#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>

int main(int argc, char const **argv)
{
	void *handle = dlopen("../lib/dlib/libmalloc.so", RTLD_LAZY);

	void *(*my_malloc)(size_t size) = dlsym(handle, "my_malloc");
	void *(*my_free)(void *ptr) = dlsym(handle, "my_free");
	void *(*count_references)(void *ptr)= dlsym(handle, "count_references");
	void *(*delete_references)(void *ptr) = dlsym(handle, "delete_references");

	int *a = (int *)my_malloc(10 * sizeof(int));

	count_references(&a);

	for(size_t i = 0; i < 10; ++i)
	{
		a[i] = 12.32;

		printf("%d\n", a[i]);
	}

	my_free(a);

	delete_references(&a);

	for(size_t i = 0; i < 10; ++i)
	{	
		printf("%d\n", a[i]);
	}

	dlclose(handle);

	return 0;
}