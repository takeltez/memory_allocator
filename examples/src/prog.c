#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>

int main(int argc, char const **argv)
{
	void *handle = dlopen("../lib/dlib/libmalloc.so", RTLD_LAZY);

	void *(*cmalloc)(size_t size) = dlsym(handle, "cmalloc");
	void *(*cfree)(void *ptr) = dlsym(handle, "cfree");
	void *(*count_references)(void *ptr)= dlsym(handle, "count_references");
	void *(*delete_references)(void *ptr) = dlsym(handle, "delete_references");

	int *a = (int *)cmalloc(10 * sizeof(int));

	count_references(&a);

	for(size_t i = 0; i < 10; ++i)
	{
		a[i] = 12.32;

		printf("%d\n", a[i]);
	}

	cfree(a);

	delete_references(&a);

	for(size_t i = 0; i < 10; ++i)
	{	
		printf("%d\n", a[i]);
	}

	dlclose(handle);

	return 0;
}