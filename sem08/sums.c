#include <stdlib.h>
#include <stdio.h>

enum {
    ARR_SIZE = (1u << 20),
};

float KahanSum(float *input) {
    float sum = 0;
    float c = 0;

    for (int i = 0; i < ARR_SIZE; ++i) {
        float y = input[i] - c;
        float t = sum + y;
        c = (t - sum) - y;
        sum = t;
    }
    return sum;
}

float RegularSum(float *arr) {
    float result = 0;
    for (int i = 0; i < ARR_SIZE; ++i) {
        result += arr[i];
    }
    return result;
}

int main(void) {
    float arr[ARR_SIZE];
    for (int i = 0; i < ARR_SIZE; ++i) {
        arr[i] = ((float) rand()) / RAND_MAX;
    }
    srand(time(NULL));
    printf("Regular sum: %f\n", RegularSum(arr));
    printf("Kahan sum: %f\n", KahanSum(arr));

}