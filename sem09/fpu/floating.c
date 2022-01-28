#include <stdio.h>

double sqrt(double value);

long double mul(long double a, long double b);

int main(void) {
	double value = 2.0;
	printf("%lf\n", sqrt(value));

	printf("%Lf\n", mul(1.5, 2.0));

	return 0;
}
