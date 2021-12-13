#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>

int main() {
	static const char * Hello = "Hello";
	
	size_t len = 0;
	const char * substring = Hello;
	for (; *substring; ++substring, ++len )
	{

	   // printf("%s\n", substring);
	}
	printf("%lu %lu %lu", len, strlen(Hello), substring-Hello);
	// printf("%d %d\n", CHAR_MIN, CHAR_MAX);
	// uint64_t addr;
 //    printf("Address: 0x%016llx\n", (unsigned long long) addr);
	// return 0;
	// open

	// a[i] == *(a + i) ~= *(a + i * sizeof(*a))

// 	int a = -1; //INT_MAX;
// 	int *p = &a;

// 	printf("%p, %d", p, *p);
// 	return 0;


// 	int b = INT_MAX;
// 	// int c = a + b;

// 	// if a >= 0, b >= 0
// 	int tmp = a - INT_MAX;
// 	tmp += b;
// 	// if tmp >= 0 , a + b - INT_MAX >= 0 -> a + b >= INT_MAX

// 	int c;
// 	int flag = __builtin_sadd_overflow(a, b, &c);
// 	printf("%d %d", c, flag);
// 	return 0;

// 	// int a = '1'; // getc(stdin); // NULL
// 	// // EOF ~= -1
// 	// int b = '2'; // getchar();
// 	// // read(0, &c, 1);
// 	// // 0, 1, 2 
// 	// char c = '\b'; // "" const char*
// 	// // printf("%d\n\n", c);
// 	// char s[5];
// 	// // scanf("%4s", s);
// 	// snprintf(s, 5, "%c %d%c %d%c", a, a, b, b, c);
// 	// // %Lf, %Lg long double
// 	// // printf("%s", s);
// 	// printf("%04lu\n", 51ul); // вывод: 00000200
// 	// printf("%f", 3.1415926535897932384626433832795028841971f); // вывод: 3.141593

// 	// fputs(s, stdout);
// 	// fflush(NULL);
// 	// sleep(5);



// 	// FILE* f = fopen("out.txt", "w");
// 	// putc(b + 2, f);
// 	// fputs("egfergior3emfgpr3", f);

// 	// fclose(f);
	
// 	return 0;
// }
}