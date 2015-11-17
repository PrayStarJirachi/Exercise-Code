#include <cmath>
#include <cstdio>
#include <algorithm>

const int INF = ~0u >> 2;
const long double EPS = 1e-18;

double aa, bb, cc, dd;
long double a, b, c, d;

int dcmp(const long double &a) {
	return fabs(a) < EPS ? 0 : (a > 0 ? 1 : -1);
}

std::pair<long double, long double> getRange(const std::pair<long double, long double> &a, const std::pair<long double, long double> &b) {
	std::pair<long double, long double> ret = std::make_pair(1ll << 60, -(1ll << 60));
	ret.first = std::min(ret.first, a.first * b.first);
	ret.first = std::min(ret.first, a.first * b.second);
	ret.first = std::min(ret.first, a.second * b.first);
	ret.first = std::min(ret.first, a.second * b.second);
	
	ret.second = std::max(ret.second, a.first * b.first);
	ret.second = std::max(ret.second, a.first * b.second);
	ret.second = std::max(ret.second, a.second * b.first);
	ret.second = std::max(ret.second, a.second * b.second);
	return ret;
}

bool isIntersect(const std::pair<long double, long double> &a, const std::pair<long double, long double> &b) {
	if (dcmp(a.second - b.first) < 0 || dcmp(a.first - b.second) > 0) return false;
	else return true;
}

bool check(const long double &answer) {
	std::pair<long double, long double> w, x, y, z;
	w = std::make_pair(a - answer, a + answer);
	x = std::make_pair(b - answer, b + answer);
	y = std::make_pair(c - answer, c + answer);
	z = std::make_pair(d - answer, d + answer);
	std::pair<long double, long double> left = getRange(w, z);
	std::pair<long double, long double> right = getRange(x, y);
	return isIntersect(left, right);
}

int main() {
	scanf("%lf%lf%lf%lf", &aa, &bb, &cc, &dd);
	a = aa; b = bb; c = cc; d = dd;
	long double left = 0, right = INF;
	for (int cs = 1; cs <= 300; cs++) {
		long double mid = (left + right) / 2.0;
		if (check(mid)) right = mid;
		else left = mid;
	}
	printf("%.12f\n", (double)left);
	return 0;
}
