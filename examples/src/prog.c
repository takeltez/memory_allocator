#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <inttypes.h>

int main(int argc, char const **argv)
{
	void *handle = dlopen("../lib/dlib/libmalloc.so", RTLD_LAZY);

	void *(*cmalloc)(size_t size, void *ptr) = dlsym(handle, "cmalloc");
	void *(*cfree)(void *ptr, uint32_t flag) = dlsym(handle, "cfree");

	float *a;
	
	cmalloc(10 * sizeof(float), &a);

	for(size_t i = 0; i < 10; ++i)
	{
		a[i] = 12.32;

		printf("%.2f\n", a[i]);
	}

	cfree(&a, 0);

	for(size_t i = 0; i < 10; ++i)
	{	
		printf("%.2f\n", a[i]);
	}

	dlclose(handle);

	return 0;
}