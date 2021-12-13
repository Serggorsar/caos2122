//Написать программу, которая должна вызывать несколько раз функцию, имитирующую какую-то длительную работу. Эта имитация заключается в "засыпании" на 1 секунду. Будем считать, что каждый раз функция выполняет 5% всей запланированной работы.
//
//Программа должна печатать на экран ProgressBar и после каждого вызова указанной функции его обновлять. По достижению 100% программа должна завершиться.
//
//[--------------------] 0%
//... // через 2 секунды работы
//[**------------------] 10%
//... // и т.д.

#include <stdio.h>
#include <unistd.h>
#include <string.h>

enum {
    PERCENT = 5,
    LEN = 100 / PERCENT
};

void f() {
    sleep(1);
}

void print_bar(unsigned p) {
    unsigned p_ = p / PERCENT;
    // \r - возврат каретки
    // \r\n, \n\r
    printf("\r[");
//    printf("%**c", p_, '\0');
    for (int i = 0; i < p_; ++i) {
        printf("*");
    }
    for (int i = p_; i < LEN; ++i) {
        printf("-");
    }
    printf("]%4u%%", p);
    fflush(NULL);
}

int main(int argc, char *argv[]) {

    printf("%d", 434343);
    fflush(NULL);
    sleep(5);
    printf("\r");
    printf("%d", 1);
    print_bar(0);
    for (int i = 0; i <= LEN; ++i) {
        f();
        print_bar(PERCENT * i);
    }
    printf("\n");
}
