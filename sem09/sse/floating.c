#include <stdio.h>

double sqrt(double value);

double mul(double a, double b);

int main(void) {
	double value = 2.0;
	printf("%lf\n", sqrt(value));

	printf("%lf\n", mul(1.5, 2.0));

	return 0;
}
