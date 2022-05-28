#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int is_prime(int n) {
    for (int i = 2; i*i <= n; ++i) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}

void get_prime() {
    
}

void* foo(void *arg) {
    int k_i;
    while (scanf("%d", &k_i) > 0) {
        int i = 0;
        int num = 1;
        while (i != k_i) {
            num += 1;
            if (is_prime(num)) {
                i += 1;
            }
        }
        printf("%d\n", num);
    }
    
}

int main(int argc, char **argv) {
    if (argc < 2) {
        return 1;
    }

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setstacksize(&attr, sysconf(_SC_THREAD_STACK_MIN));
    pthread_attr_setguardsize(&attr,0);
    size_t N = strtol(argv[1], NULL, 10);
    pthread_t tid[N];
    for (size_t i = 0; i != N; ++i) {
        int err = pthread_create(&tid[i], NULL, foo, NULL);
    }
    pthread_attr_destroy(&attr);
    for (size_t i = 0; i != N; ++i) {
        pthread_join(tid[i], NULL);
    }
    return 0;
}