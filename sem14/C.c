#include <stdio.h>
#include <unistd.h>
#include <cstdlib>
#include <sys/mman.h>
#include <string.h>
#include <errno.h>

int main(void) {
    void* memory = mmap(NULL, 2 * sizeof(int), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, 0, 0);
    if (memory == MAP_FAILED) {
        printf("%s/n", strerror(errno));
        return 1;
    }
    int* data = (int *) memory;
    int n;
    scanf("%d", &n);
    if (!fork()) {
        int f1 = 1;
        int f2 = 1;
        int k = 0;
        for (size_t i = 1; i < n; ++i) {
            k = f2;
            f2 = f2 + f1;
            f1 = k;
        }
        data[0] = f2;
        _exit(0);
    }
    if (!fork()) {
        int k = 1;
        for (int i = 1; i <= n; ++i) {
            k *= i;
        }
        data[1] = k;
        _exit(0);
    }
    wait(NULL);
    wait(NULL);
    int a = data[0], b = data[1];
    munmap(memory, 2 * sizeof(int));
    printf("%d %d", a, b);
    return 0;
}