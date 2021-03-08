#include <dlfcn.h>

int main(int argc, char const **argv)
{
	void *handle = dlopen("../lib/dlib/my_malloc.so", RTLD_LAZY);

	void (*testFunc)(void) = dlsym(handle, "test");

	(*testFunc)();

	dlclose(handle);

	return 0;
}