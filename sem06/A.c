//В аргументах командной строки вводится беззнаковое число N.
//
//Написать программу, которая считывает со стандартного входного потока вещественные числа x. И для каждого введенного аргумента выводит таблицу со значениями функций sin(x) и exp(x). Ширина колонок - N, количество разрядов дробной части - 1.
//
//Пример вывода при N==5:
//
//Arg  |sin  |exp  |
//0.0|  0.0|  0.0|
//Замечание. При компиляции программы важно подключить линковку с математической библиотекой (-lm):
//
//gcc -Wall -A.c -lm

//enum {
//    ZERO = 43, // iota  2 ** iota + 1 2 3 5 9 17
//    ONE,
//    TWO
//};

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
//    printf("%d %d %d", ZERO, ONE, TWO);
    float f; // = 1.434e-5f;
//    printf("%f %g\n", f, f);
    unsigned n = strtol(argv[1], NULL, 10);

    printf("%-*s|%-*s|%-*s", n, "Arg", n, "sin", n, "exp");
    while (scanf("%f", &f) == 1) {
        printf("%*.1f|%*.1f|%*.1f", n, f, n, sinf(f), n, -expf(f));
    }

//    printf("%d %s %s\n", argc, argv[0], argv[1]);
//    strto*
//    sscanf(argv[1], "%u", &n);
//    printf("\n%d\n", atoi("hello"));
//    printf("\n%d\n", strtol(argv[1], NULL, 10)); // 2 .. 36 0-9a-z
//
//
//    printf("%0*d", 6, 4);
}