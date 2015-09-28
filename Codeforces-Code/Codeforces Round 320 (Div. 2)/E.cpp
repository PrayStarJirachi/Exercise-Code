#include <cstdio>
#include <algorithm>

const int MAXN = 200001;
const long long INF = 1ll << 40;

int n, a[MAXN];
double d[MAXN];

double check(double x) {
	for (int i = 1; i <= n; i++) {
		d[i] = d[i - 1] + a[i] - x;
	}
	double zmin = 0, zmax = 0, ret = 0;
	for (int i = 1; i <= n; i++) {
		ret = std::max(ret, d[i] - zmin);
		zmin = std::min(zmin, d[i]);
		// S[r] - S[l - 1]
		// S[l - 1] - S[r]
		ret = std::max(ret, zmax - d[i]);
		zmax = std::max(zmax, d[i]);
	}
	return ret;
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", a + i);
	}
	double left = -INF, right = INF, answer = INF;
	for (int c = 1; c <= 150; c++) {
		double len = right - left;
		double m1 = left + len / 3.0;
		double m2 = left + len * 2.0 / 3.0;
		double c1 = check(m1), c2 = check(m2);
		answer = std::min(answer, c1);
		answer = std::min(answer, c2);
		if (c1 > c2) {
			left = m1;
		}
		else{
			right = m2;
		}
	}
	printf("%.10f\n", answer);
	return 0;
}
