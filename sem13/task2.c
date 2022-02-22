#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>

int main() {
    struct stat st;
    lstat("input.txt", &st);
    int size = st.st_size;
    int fd = open("input.txt", O_RDONLY);
    void *mp = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (mp == MAP_FAILED) {
        puts("mmap filed :(");
        return 1;
    }
    
    char* c = mp;
    int result = 0;
    for (int i = 0; i < size; ++i) {
        if (c[i] == ' ') {
            ++result;
        }
    }
    printf("%d\n", result);
    munmap(mp, size);
    return 0;
}