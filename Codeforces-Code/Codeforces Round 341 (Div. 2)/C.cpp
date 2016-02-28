#include <cstdio>
#include <iomanip>
#include <iostream>
#include <algorithm>

const int MAXN = 222222;

int n, p;
std::pair<long long, long long> a[MAXN];

double getNumber(const std::pair<long long, long long> &a, const std::pair<long long, long long> &b) {
	double ret = 0;
	ret += 1.0 * (b.second - b.first + 1) * (a.second / p - (a.first - 1) / p);
	ret += 1.0 * (a.second - a.first + 1) * (b.second / p - (b.first - 1) / p);
	ret -= 1.0 * (a.second / p - (a.first - 1) / p) * (b.second / p - (b.first - 1) / p);
	ret = ret / (a.second - a.first + 1) / (b.second - b.first + 1);
	return ret;
}

int main() {
	std::cin >> n >> p;
	double answer = 0, prod = 1;
	for (int i = 0; i < n; i++) {
		std::cin >> a[i].first >> a[i].second;
	}
	for (int i = 0; i < n; i++) {
		answer += getNumber(a[i], a[(i + 1) % n]);
	}
	answer = answer * 2000.0;
	printf("%.10f\n", answer);
	return 0;
}
