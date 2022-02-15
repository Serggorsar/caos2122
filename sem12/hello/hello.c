#include<stdio.h>

void printHello() {
#ifdef PIC
	printf("Hello, dynamic\n");
#else
	printf("Hello, static\n");
#endif
}
