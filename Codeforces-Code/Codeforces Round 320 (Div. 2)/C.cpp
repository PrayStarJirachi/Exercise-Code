#include <cstdio>
#include <cmath>
#include <algorithm>

const double INF = 1e30;
const double eps = 1e-9;

int a, b;

double getUp(int a, int b) {
	int kmax = (int)floor(((double)a / b - 1) / 2.0);
	if (kmax <= 0) return INF;
	double ret = 1.0 * (a - b) / (2 * kmax);
	if (ret < 0) return INF;
	else return ret;
}

double getDown(int a, int b) {
	int kmax = (int)floor(((double)a / b - 1) / 2.0);
	if (kmax < 0) return INF;
	double ret = 1.0 * (a + b) / (2 * kmax + 2);
	if (ret < 0) return INF;
	else return ret;
}

int main() {
	scanf("%d%d", &a, &b);
	double aU = getUp(a, b);
	double aD = getDown(a, b);
	double answer = std::min(aU, aD);
	if (fabs(answer - INF) < eps) printf("-1\n");
	else printf("%.20f\n", answer);
	return 0;
}
