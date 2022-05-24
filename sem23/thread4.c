#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

enum { COUNT = 100 };

//_Thread_local int c;
int a[1000];

void* foo(void* arg) {
    int num = (int*)arg;
    for (int i = 0; i < 10; i++) {
        //printf("%d ", i + 10 * num);
        a[i + 10 * num] = a[i + 10 * num] * a[i + 10 * num];
    }
    // while((c = getchar_unlocked()) != EOF) {
    //     putchar_unlocked(c);
    // }
    return NULL;
}

int main() {
    pthread_t ids[COUNT];
    
    for (int i = 0; i < 1000; i++) {
        a[i] = i;
    }
    
    for (int i = 0; i < COUNT; ++i) {
        int err = pthread_create(&ids[i], NULL, foo, (void*)i);
    }
    //printf("c middle: %d\n", c);
    for (int i = 0; i < COUNT; ++i) {
        //printf("c join: %d\n", c);
        pthread_join(ids[i], NULL);
    }

    for (int i = 0; i < 1000; i++) {
        printf("%d ", a[i]);
    }
    return 0; // exit
}

//145678901234567890\n3