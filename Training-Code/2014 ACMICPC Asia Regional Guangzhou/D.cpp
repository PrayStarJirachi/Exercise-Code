#include <cmath>
#include <cstdio>
#include <cassert>
#include <algorithm>

const double EPS = 1e-8;
const int MAXN = 555;

int dcmp(const double &x) {
	return fabs(x) < EPS ? 0 : (x > 0 ? 1 : -1);
}

struct Point{
	double x, y;
	Point () {}
	Point (double x, double y) : x(x), y(y) {}
	Point operator -(const Point &p)const {
		return Point(x - p.x, y - p.y);
	}
	Point operator +(const Point &p)const {
		return Point(x + p.x, y + p.y);
	}
	Point operator *(const double &p)const {
		return Point(x * p, y * p);
	}
	Point operator /(const double &p)const {
		return Point(x / p, y / p);
	}
	void read() {
		scanf("%lf%lf", &x, &y);
	}
}p[MAXN], A, B;

int n, cs;
double k;

double dot(const Point &a, const Point &b) {
	return a.x * b.x + a.y * b.y;
}

double det(const Point &a, const Point &b) {
	return a.x * b.y - b.x * a.y;
}

double dist(const Point &a, const Point &b) {
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double sqrdist(const Point &a, const Point &b) {
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

double dist(const Point &a) {
	return sqrt(a.x * a.x + a.y * a.y);
}

double getSectorArea(const Point &a, const Point &b, const double &r) {
	double c = (2.0 * r * r - sqrdist(a, b)) / (2.0 * r * r);
	double alpha = acos(c);
	return r * r * alpha / 2.0;
}

std::pair<double, double> getSolution(const double &a, const double &b, const double &c) {
	double delta = b * b - 4.0 * a * c;
	if (dcmp(delta) < 0) return std::make_pair(0, 0);
	else return std::make_pair((-b - sqrt(delta)) / (2.0 * a), (-b + sqrt(delta)) / (2.0 * a));
}

std::pair<Point, Point> getIntersection(const Point &a, const Point &b, const double &r) {
	Point d = b - a;
	double A = dot(d, d);
	double B = 2.0 * dot(d, a);
	double C = dot(a, a) - r * r;
	std::pair<double, double> s = getSolution(A, B, C);
	return std::make_pair(a + d * s.first, a + d * s.second);
}

double getPointDist(const Point &a, const Point &b) {
	Point d = b - a;
	int sA = dcmp(dot(a, d)), sB = dcmp(dot(b, d));
	if (sA * sB <= 0) return det(a, b) / dist(a, b);
	else return std::min(dist(a), dist(b));
}

double getArea(const Point &a, const Point &b, const double &r) {
	double dA = dot(a, a), dB = dot(b, b), dC = getPointDist(a, b), ans = 0.0;
	if (dcmp(dA - r * r) <= 0 && dcmp(dB - r * r) <= 0) return det(a, b) / 2.0;
	Point tA = a / dist(a) * r;
	Point tB = b / dist(b) * r;
	if (dcmp(dC - r) > 0) return getSectorArea(tA, tB, r);
	std::pair<Point, Point> ret = getIntersection(a, b, r);
	if (dcmp(dA - r * r) > 0 && dcmp(dB - r * r) > 0) {
		ans += getSectorArea(tA, ret.first, r);
		ans += det(ret.first, ret.second) / 2.0;
		ans += getSectorArea(ret.second, tB, r);
		return ans;
	}
	if (dcmp(dA - r * r) > 0) return det(ret.first, b) / 2.0 + getSectorArea(tA, ret.first, r);
	else return det(a, ret.second) / 2.0 + getSectorArea(ret.second, tB, r);
}

double getArea(int n, Point *p, const Point &c, const double r)  {
	double ret = 0.0;
	for (int i = 0; i < n; i++) {
		int sgn = dcmp(det(p[i] - c, p[(i + 1) % n] - c));
		if (sgn > 0) ret += getArea(p[i] - c, p[(i + 1) % n] - c, r);
		else ret -= getArea(p[(i + 1) % n] - c, p[i] - c, r);
	}
	return fabs(ret);
}

int main() {
	freopen("D.in", "r", stdin);
	while (scanf("%d%lf", &n, &k) == 2) {
		for (int i = 0; i < n; i++) p[i].read();
		A.read(); B.read();
		double D = (2.0 * k * k * A.x - 2.0 * B.x) / (1.0 - k * k);
		double E = (2.0 * k * k * A.y - 2.0 * B.y) / (1.0 - k * k);
		double F = (B.x * B.x - k * k * A.x * A.x + B.y * B.y - k * k * A.y * A.y) / (1.0 - k * k);
		Point c = Point(-D / 2.0, -E / 2.0);
		double r = (D * D + E * E - 4.0 * F) / 4.0;
		assert(dcmp(r) >= 0);
		r = sqrt(r);
		printf("Case %d: %.10f\n", ++cs, getArea(n, p, c, r));
	}
	return 0;
}
