#include <stdio.h>
#include <math.h>
#include <string.h>

void printBits(size_t const size, void const * const ptr)
{
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;

    for (i = size-1; i >= 0; i--) {
        for (j = 7; j >= 0; j--) {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
    }
    puts("");
}

union U {
    float f;
    unsigned i;
    char c[4];
};


int main(int argc, char *argv[]) {

    long long l = 5; // 101.011 -> 1.01011 * 2 ** 2 -> exp = 127 + 2 =
    float f = 5.376f;
    double d = 5.376;
    long double ld = 5.376l;
    union U u;
    u.f = f;
    printf("%.23f %.23f\n", sin(f), sinf(f));
    printf("%.40lf\n", d);
    printf("%.40Lf\n", ld);
    printf("%x\n", u.i);

    printBits(sizeof(f), u.c);
    return 0;
}
