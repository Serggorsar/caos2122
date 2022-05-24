#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

void bar() {
    pthread_exit((void*) strdup("exit\n"));
}

void* foo(void* arg) {
    printf("in thread\n");

    //bar();

    //sleep(4);
    return (void*)strdup("success");
}

int main() {
    pthread_t tid = 0;
    int err = pthread_create(&tid, NULL, foo, NULL);
    sleep(1);
    printf("in main\n");
    void *res = NULL;
    //pthread_join(tid, &res);
    printf("result: %s\n", res);
    return 0; // race condition
    // xor eax eax
    // _exit
    // int $0x80
}


// ./server - malloc, not free