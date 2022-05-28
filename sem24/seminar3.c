#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int A, B, C, G;

struct data {
    int X0, dx, nx, Y0, dy, ny;
    int pthread_num;
};

void *foo(void * arg) {

    struct data *data = arg;
    pthread_mutex_lock(&mutex);
    if (data->pthread_num == 1) {   
        A -= data->dx;
        G += (int)(data->dx * 0.15);
        B += (int)(data->dx * 0.85);
    } else {
        B -= data->dx;
        G += (int)(data->dx * 0.2);
        C += (int)(data->dx * 0.8);

    }
    pthread_mutex_unlock(&mutex);
    return NULL;


}

int main(int agc, char** argv) {
    

    int X0, dx, nx, Y0, dy, ny;

    pthread_t tid_1 = 0;
    pthread_t tid_2 = 0;
    struct data data = {0};

    while (scanf("%d %d %d %d %d %d", &data.X0, &data.dx, &data.nx, &data.Y0, &data.dy, &data.ny) > 0) {
        data.pthread_num = 1;
        int err = pthread_create(&tid_1, NULL, foo,(void *)&data);
        data.pthread_num = 2;
        err = pthread_create(&tid_2, NULL, foo,(void *)&data);
        pthread_join(tid_1, NULL);
        pthread_join(tid_2, NULL);
        printf("%d %d %d %d\n", A, B, C, G);
    }
}