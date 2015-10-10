#include <cmath>
#include <cstdio>
#include <algorithm>

const int MAXN = 40001;
const int INF = ~0u >> 2;
const double eps = 1e-8;
const double pi = 3.1415926535897932384626;

int dcmp(const double &x) {
	return fabs(x) < eps ? 0 : (x > 0 ? 1 : -1);
}

struct Point{
	double x, y;
	Point() {}
	Point(double x, double y) : x(x), y(y) {}
	Point operator +(const Point &p)const {
		return Point(x + p.x, y + p.y);
	}
	Point operator -(const Point &p)const {
		return Point(x - p.x, y - p.y);
	}
	Point operator *(const double &p)const {
		return Point(x * p, y * p);
	}
	Point operator /(const double &p)const {
		return Point(x / p, y / p);
	}
	double arg() {
		return atan2(y, x);
	}
	void print()const {
		printf("(%.10f, %.10f)\n", x, y);
	}
	void read() {
		scanf("%lf%lf", &x, &y);
	}
};

double det(const Point &a, const Point &b) {
	return a.x * b.y - b.x * a.y;
}

double dot(const Point &a, const Point &b) {
	return a.x * b.x + a.y * b.y;
}

struct Line{
	Point a, b;
	Line() {}
	Line(Point a, Point b) : a(a), b(b) {}
}l[MAXN];

int n;
double amax, segmax[MAXN], arcmax[MAXN];

double dist(const Point &a, const Point &b) {
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double getDist(const Point &x, const Line &l) {
	return fabs(det(x - l.a, l.b - l.a)) / dist(l.a, l.b);
}

Point getNormalVector(const Point &a) {
	return Point(a.y, -a.x);
}

Point getIntersection(const Line &l, const Line &r) {
	double sA = det(r.a - l.a, l.b - l.a);
	double sB = det(l.b - l.a, r.b - l.a);
	return r.a + (r.b - r.a) * (sA / (sA + sB));
}

double getRadius(const Line &l, const Line &r) {
	Point nL = getNormalVector(l.b - l.a);
	Point nR = getNormalVector(r.b - r.a);
	Point I;
	if (dcmp(det(nL, nR))) {
		I = getIntersection(Line(l.b, l.b + nL), Line(r.b, r.b + nR));
	}
	else{
		I = (l.b + r.b) / 2.0;
	}
	return std::min(getDist(I, l), getDist(I, r));
}

double getMinSpeed(const double &startSpeed, const double &length) {
	double ret = startSpeed * startSpeed + 2 * amax * length;
	return sqrt(ret);
}

double getAnswer(const double &v1, const double &v2, const double &l) {
	double ret = 0;
	ret = (2.0 * sqrt((2.0 * amax * l + v1 * v1 + v2 * v2) / 2.0) - v1 - v2) / amax;
	return ret;
}

double getArcLength(const Line &l, const Line &r, bool print = false) {
	if (!dcmp(det(l.b - l.a, r.b - r.a))) return pi * getRadius(l, r);
	double alpha = acos(dot(l.b - l.a, r.b - r.a) / dist(l.b, l.a) / dist(r.b, r.a));
	Point I = getIntersection(l, r);
	if (dcmp(dot(l.b - l.a, I - l.b)) < 0) alpha += pi;
	return getRadius(l, r) * alpha;
}

int main() {
	freopen("E.in", "r", stdin);
	scanf("%d%lf", &n, &amax);
	for (int i = 1; i <= n; i++) {
		l[i].a.read();
		l[i].b.read();
		segmax[i] = INF;
	}
	for (int i = 2; i <= n; i++) {
		double tmp = getRadius(l[i - 1], l[i]);
		tmp = sqrt(tmp * amax);
		arcmax[i - 1] = tmp;
	}
	segmax[1] = 0;
	double nowSpeed;
	nowSpeed = 0;
	for (int i = 1; i < n; i++) {
		double nextSpeed = INF;
		nextSpeed = std::min(nextSpeed, arcmax[i]);
		nextSpeed = std::min(nextSpeed, getMinSpeed(nowSpeed, dist(l[i].a, l[i].b)));
		segmax[i + 1] = std::min(segmax[i + 1], nextSpeed);
		nowSpeed = nextSpeed;
	}
	nowSpeed = 0;
	for (int i = n; i > 1; i--) {
		double nextSpeed = INF;
		nextSpeed = std::min(nextSpeed, arcmax[i - 1]);
		nextSpeed = std::min(nextSpeed, getMinSpeed(nowSpeed, dist(l[i].a, l[i].b)));
		segmax[i] = std::min(segmax[i], nextSpeed);
		nowSpeed = nextSpeed;
	}
	double answer = 0;
	for (int i = 1; i < n; i++) {
		answer += getAnswer(segmax[i], segmax[i + 1], dist(l[i].a, l[i].b));
		answer += getArcLength(l[i], l[i + 1]) / segmax[i + 1];
	}
	answer += getAnswer(segmax[n], 0, dist(l[n].a, l[n].b));
	printf("%.10f\n", answer);
	return 0;
}
