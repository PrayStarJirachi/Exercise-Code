#include <cstdio>
#include <numeric>
#include <iostream>
#include <algorithm>

typedef long long Int64;

const double EPS = 1e-7;
const double PI = 3.1415926535897932384626;

const int MAXN = 100101;
const Int64 INF = ~0u >> 2;

int n;
std::pair<Int64, Int64> r[MAXN];

Int64 sqr(const Int64 &x) {
	return x * x;
}

bool check(const Int64 &answer) {
	static Int64 predMax[MAXN], predMin[MAXN];
	static Int64 succMax[MAXN], succMin[MAXN];
	predMax[0] = -INF;
	predMin[0] = INF;
	for (int i = 1; i <= n; i++) {
		predMax[i] = std::max(predMax[i - 1], r[i].second);
		predMin[i] = std::min(predMin[i - 1], r[i].second);
	}
	succMax[n + 1] = -INF;
	succMin[n + 1] = INF;
	for (int i = n; i >= 1; i--) {
		succMax[i] = std::max(succMax[i + 1], r[i].second);
		succMin[i] = std::min(succMin[i + 1], r[i].second);
	}
	if (sqr(predMax[n] - predMin[n]) <= answer) return true;
	for (int i = 1, z = 1; i <= n; i++) {
		z = std::max(z, i);
		while (z < n && sqr(r[z + 1].first - r[i].first) <= answer) {
			Int64 yMax = std::max(predMax[i - 1], succMax[z + 1]);
			Int64 yMin = std::min(predMin[i - 1], succMin[z + 1]);
			bool flag = true;
			if (sqr(yMax - yMin) > answer) flag = false;
			if (sqr(yMin) + sqr(r[i].first) > answer) flag = false;
			if (sqr(yMax) + sqr(r[i].first) > answer) flag = false;
			if (sqr(yMin) + sqr(r[z].first) > answer) flag = false;
			if (sqr(yMax) + sqr(r[z].first) > answer) flag = false;
			if (flag) {
				return true;
			}
			z++;
		}
		bool flag = true;
		Int64 yMax = std::max(predMax[i - 1], succMax[z + 1]);
		Int64 yMin = std::min(predMin[i - 1], succMin[z + 1]);
		if (sqr(yMax - yMin) > answer) flag = false;
		if (sqr(yMin) + sqr(r[i].first) > answer) flag = false;
		if (sqr(yMax) + sqr(r[i].first) > answer) flag = false;
		if (sqr(yMin) + sqr(r[z].first) > answer) flag = false;
		if (sqr(yMax) + sqr(r[z].first) > answer) flag = false;
		if (flag) {
			return true;
		}
	}
	return false;
}

Int64 solve(int n) {
	std::sort(r + 1, r + n + 1);
	Int64 left = 0, right = sqr(r[n].first - r[1].first);
	while (left < right) {
		Int64 middle = left + right >> 1;
		if (check(middle)) {
			right = middle;
		} else {
			left = middle + 1;
		}
	}
	return left;
}

int main() {
	std::cin >> n;
	for (int i = 1; i <= n; i++) {
		std::cin >> r[i].first >> r[i].second;
	}
	Int64 answer = 1ll << 60;
	answer = std::min(answer, solve(n));
	for (int i = 1; i <= n; i++) {
		std::swap(r[i].first, r[i].second);
	}
	answer = std::min(answer, solve(n));
	std::cout << answer << std::endl;
	return 0;
}
