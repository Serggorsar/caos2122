#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

const char *verdict(int is_equal) {
    return is_equal? "==": "!=";
}

void floats(void) {
    float small = 0.001f;
    float large = 100000.f;
    printf("large = %.18f\n", large);
    printf("small = %.23f\n", small);
    assert(large + small == large);

    float summ = 0;
    for (int i = 0; i < 100; i++) {
        summ += small;
    }
    summ += large;
    printf("summ(small) + large = %.10f %s large\n", summ, verdict(summ == large));

    summ = 0;
    summ += large;
    for (int i = 0; i < 100; i++) {
        summ += small;
    }
    printf("large + summ(small) = %.10f %s large\n", summ, verdict(summ == large));
}
void doubles(void) {
    double small = 0.00000001;
    double large = 1000000000;
    printf("large = %.6f\n", large);
    printf("small = %.15f\n", small);
    assert(large + small == large);

    double summ = 0;
    for (int i = 0; i < 1000; i++) {
        summ += small;
    }
    summ += large;
    printf("summ(small) + large = %.25f %s large\n", summ, verdict(summ == large));

    summ = 0;
    summ += large;
    for (int i = 0; i < 1000; i++) {
        summ += small;
    }
    printf("large + summ(small) = %.25f %s large\n", summ, verdict(summ == large));
}

int main(void) {
    floats();
    printf("-------------------------------------------------\n");
    doubles();
}