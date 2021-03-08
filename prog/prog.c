#include <stdio.h>
#include <dlfcn.h>

int main(int argc, char const **argv)
{
	void *handle = dlopen("../lib/dlib/my_malloc.so", RTLD_LAZY);

	void *(*my_malloc)(size_t size) = dlsym(handle, "my_malloc");
	void *(*my_free)(void *ptr) = dlsym(handle, "my_free");

	double *a = (double *)(*my_malloc)(10);

	a[0] = 12.32;

	printf("%.2lf\n", a[0]);

	my_free(a);

	printf("%.2lf\n", a[0]);

	dlclose(handle);

	return 0;
}