#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

enum { COUNT = 100 };

_Thread_local int c;

void* foo(void* arg) {
    printf("thread_id: %ld\n", (intptr_t)arg);
    while((c = getchar_unlocked()) != EOF) {
        printf("in: %ld\n", (intptr_t)arg);
        putchar_unlocked(c);
    }
    sched_yield();
    return NULL;
}
// планировщик сменяет нить
// 1) истекло выданное нити время (справедливости, приоритета)
// 2) нить закончила свое выполнение
// 3) переходит в состояние ожидания IO
// CPU - IO

int main() {
    pthread_t ids[COUNT];
    for (int i = 0; i < COUNT; ++i) {
        int err = pthread_create(&ids[i], NULL, foo, (void*)(intptr_t) i);
    }
    for (int i = 0; i < COUNT; ++i) {
        //pthread_join(ids[i], NULL);
    }
    sleep(40);
    return 0; // exit
}

//145678901234567890\n3