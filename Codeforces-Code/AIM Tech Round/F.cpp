#include <cstdio>
#include <numeric>
#include <iostream>
#include <algorithm>

const long double EPS = 1e-7;
const long double PI = 3.1415926535897932384626;

const int MAXN = 1001;

int n;
long double p[MAXN], d[MAXN];

int main() {
	// freopen("input.txt", "r", stdin);
	std::cin >> n;
	for (int i = 1; i <= n; i++) {
		std::cin >> p[i];
		p[i] /= 100;
		p[i] = 1.0 - p[i];
	}
	std::sort(p + 1, p + n + 1);
	long double answer = 0.0, value = 1.0;
	for (int i = 1; i <= n; i++) {
		value *= 1.0 - p[i];
		d[i] = p[i];
	}
	answer = n * value;
	for (int i = n + 1; i <= 300000; i++) {
		answer -= i * value;
		long double tmp = 0;
		int which = 0;
		for (int j = 1; j <= n; j++) {
			long double now = 0;
			now = (1.0 - d[j] * p[j]) / (1.0 - d[j]);
			if (tmp < now) {
				tmp = now;
				which = j;
			}
		}
		d[which] *= p[which];
		answer += i * (value = tmp * value);
	}
	printf("%.10f\n", (double)answer);
	return 0;
}
