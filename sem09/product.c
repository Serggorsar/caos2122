#include <stdio.h>

double dp(int n, const double* a, const double* b);

int main(void) {
	double a[] = {1, -1, 100};
	double b[] = {4.6, 4.7, 9.1};

	int n = sizeof(a) / sizeof(*a);

	double ans = dp(n, a, b);

	printf("%lf\n", ans);
	return 0;
}
