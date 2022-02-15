#include <dlfcn.h>
#include <stdio.h>

int main() {
	void* handler = dlopen("hello/libhello.so", RTLD_LAZY);
	if (handler == NULL) {
		fprintf(stderr, "%s", dlerror());
		return 1;
	}
	void *sym = dlsym(handler, "printHello");
	if (sym == NULL) {
                fprintf(stderr, "%s", dlerror());
                return 1;
        }
	((void(*)())sym)();
	dlclose(handler);
	return 0;
}

