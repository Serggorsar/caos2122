#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int flag = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c = PTHREAD_COND_INITIALIZER;
int X0, dx, n;
int cur_prime;
int printed = 0;

int is_prime(int n) {
    for (int i = 2; i*i <= n; ++i) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}



void* foo(void *arg) {
    int begin = X0;
    int i = 0;
    while (1) {
        if (is_prime(begin)) {
            if (i % dx == 0) {
                pthread_mutex_lock(&mutex);
                flag = 1;
                cur_prime = begin;
                int m = 0;
                while (m != 1000) {
                    m += 1;
                }
                pthread_cond_signal(&c);
                pthread_mutex_unlock(&mutex);
            }
            i += 1;
        }
        begin += 1;
    }
    return NULL;
}

int main() {
    scanf("%d %d %d", &X0, &dx, &n); 


    pthread_t tid;
    int err = pthread_create(&tid, NULL, foo, NULL);

    int j = 0;
    while (j != n) {
        pthread_mutex_lock(&mutex);
        while (!flag) {
            pthread_cond_wait(&c, &mutex);
        }
        flag = 0;
        pthread_mutex_unlock(&mutex);
        printf("%d\n", cur_prime);
        ++j;
    }
}