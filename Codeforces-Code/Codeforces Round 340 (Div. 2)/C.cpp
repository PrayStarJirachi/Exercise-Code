#include <cstdio>
#include <numeric>
#include <iostream>
#include <algorithm>

const int MAXN = 10001;

struct Point{
	long long x, y;
}c1, c2, p[MAXN];

int n;

long long dist(const Point &a, const Point &b) {
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

bool cmp1(const Point &a, const Point &b) {
	return dist(c1, a) < dist(c1, b);
}

bool cmp2(const Point &a, const Point &b) {
	return dist(c2, a) < dist(c2, b);
}

int main() {
	// freopen("input.txt", "r", stdin);
	std::cin >> n >> c1.x >> c1.y >> c2.x >> c2.y;
	for (int i = 1; i <= n; i++) {
		std::cin >> p[i].x >> p[i].y;
	}
	std::sort(p + 1, p + n + 1, cmp1);
	long long answer = 1ll << 60;
	for (int i = 1; i <= n; i++) {
		long long mindist = 0;
		for (int j = i + 1; j <= n; j++) {
			mindist = std::max(mindist, dist(c2, p[j]));
		}
		answer = std::min(answer, mindist + dist(c1, p[i]));
	}
	std::sort(p + 1, p + n + 1, cmp2);
	for (int i = 1; i <= n; i++) {
		long long mindist = 0;
		for (int j = i + 1; j <= n; j++) {
			mindist = std::max(mindist, dist(c1, p[j]));
		}
		answer = std::min(answer, mindist + dist(c2, p[i]));
	}
	std::cout << answer << std::endl;
	return 0;
}
