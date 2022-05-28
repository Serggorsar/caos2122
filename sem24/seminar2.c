#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdint-gcc.h>

uint32_t* res_arr;
pthread_t* threads_arr;

int is_prime(uint32_t n) {
    for (uint32_t i = 2; i*i <= n; ++i) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}

void* foo(void* ptrno) {
    int current = (int)(intptr_t)(ptrno);
    uint32_t start;
    if (current > 0) {
        pthread_join(threads_arr[current - 1], NULL);
        start = res_arr[current-1];
    } else {
        start = res_arr[current];
    }
    for (uint32_t i = start + 1; 1; ++i) {
        if (is_prime(i)) {
            res_arr[current] = i;
            return NULL;
        }
    }
}

int main(int argc, char **argv) {
    if (argc < 3) {
        return 1;
    }

    uint32_t b = strtoul(argv[2], NULL, 10);
    uint32_t n = strtoul(argv[1], NULL, 10);

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setstacksize(&attr, sysconf(_SC_THREAD_STACK_MIN));
    pthread_attr_setguardsize(&attr,0);
    threads_arr = malloc(n * sizeof(pthread_t));
    res_arr = malloc(n * sizeof(int));

    res_arr[0] = b;

    for (size_t i = 0; i != n; ++i) {
        int err = pthread_create(&threads_arr[i], &attr, foo, (void *)(intptr_t)i);
    }

    pthread_join(threads_arr[n-1], NULL);
    for (size_t i = 0; i < n; ++i) {
        printf("%d\n", res_arr[i]);
    }
    pthread_attr_destroy(&attr);
    free(threads_arr);
    free(res_arr);
    return 0;
}
