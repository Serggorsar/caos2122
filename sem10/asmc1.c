#include<stdio.h>

int globvar = 1;

int main() {
	printf("%d\n", globvar);
	int result = 0;
	asm volatile("movl $1, %%eax\n"
	"movl %1, %%edx\n"
	"addl	%%edx, %%eax\n"
	"movl	%%eax, %0\n" : "=g"(result) : "g"(result) : "%eax", "%edx" );
	printf("%d %d\n", globvar, result);
	return 0;
}
