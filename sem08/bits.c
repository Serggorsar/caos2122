#include <stdio.h>

enum { BUFSIZE = 64 };

void print_bits(unsigned u, int from, int to) {
    for (int i = to - 1; i >= from; i--) {
        printf("%d", (u & (1u << i)) != 0);
    }
}

union U {
    float f;
    unsigned u;
    struct {
        unsigned s: 1;
        unsigned e: 8;
        unsigned m: 23;
    } b;
};

struct point
{ // {4, 14};
    unsigned int y:3;   // 0-7
    unsigned int x:5;   // 0-31
};

union code
{
    struct point p; // {4, 14};
    unsigned char c;
    struct{
        unsigned a0:1;
        unsigned a1:1;
        unsigned a2:1;
        unsigned a3:1;
        unsigned a4:1;
        unsigned a5:1;
        unsigned a6:1;
        unsigned a7:1;
    } byte;
};


int foo(void)
{
    struct point center = {4, 14};
    union code c;

    c.p = center;
//    c.c = 67u; // 01000011
    printf("7 \t 6 \t 5 \t 4 \t 3 \t 2 \t 1 \t 0 \n");
    printf("%d \t %d \t %d \t %d \t %d \t %d \t %d \t %d \n",
           c.byte.a7, c.byte.a6, c.byte.a5, c.byte.a4,
           c.byte.a3, c.byte.a2, c.byte.a1, c.byte.a0);
    return 0;
}


int main() {
    foo();
    union U u;
    float f = 1.40129846432e-45f;
    unsigned un = *((unsigned *) &f);
    printf("%u\n\n", un);
    u.f = f;
    print_bits(un, 0, 32);
    printf("\n");
    for (int i = 0; i < 149; i++) {
        f *= 2.0f;
    }
    un = *((unsigned *) &f);
    printf("%f\n\n", f);

    u.f = f;
    print_bits(u.b.s, 0, 1);
    print_bits(u.b.e, 0, 8);
    print_bits(u.b.m, 0, 23);
    printf("\n");

    print_bits(un, 0, 32);
    printf("\n\n");

    while (scanf("%f", &f) == 1) {
        un = *((unsigned *) &f);
        print_bits(un, 31, 32);
        printf(" ");
        print_bits(un, 23, 31);
        printf(" ");
        print_bits(un, 0, 23);
        printf("\n");
    }
    return 0;
}
