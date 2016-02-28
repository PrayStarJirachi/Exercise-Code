#include <set>
#include <map>
#include <ctime>
#include <queue>
#include <cmath>
#include <bitset>
#include <cctype>
#include <cstdio>
#include <vector>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <cstring>
#include <cassert>
#include <iostream>
#include <algorithm>

#define debug(...) fprintf(stderr, __VA_ARGS__)
#ifdef WIN32
	#define LL "%I64d"
#else
	#define LL "%lld"
#endif

using namespace std;

const int MAXN = 100001;
const long long INF = 1ll << 50;
const double eps = 1e-12;
const double PI = 3.1415926535897932384626;
const int mod = 0;

struct Point{
	double x, y;
	Point() {}
	Point(double x, double y):x(x), y(y) {}
	Point operator +(const Point &p)const {return Point(x + p.x, y + p.y);}
	Point operator -(const Point &p)const {return Point(x - p.x, y - p.y);}
	Point operator *(const double &p)const {return Point(x * p, y * p);}
	Point operator /(const double &p)const {return Point(x / p, y / p);}
	int read() {return scanf("%lf%lf", &x, &y);}
}p[MAXN], c;

struct Line{
	Point a, b;
	Line() {}
	Line(Point a, Point b):a(a), b(b) {}
};

bool dcmp(double a) {return fabs(a) < eps;}
bool dcmp(double a, double b) {return fabs(a - b) < eps;}
double det(Point a, Point b) {return a.x * b.y - b.x * a.y;}
double dot(Point a, Point b) {return a.x * b.x + a.y * b.y;}
Point getLeftNormalVector(const Point &a) {return Point(-a.y, a.x);}
Point getRightNormalVector(const Point &a) {return Point(a.y, -a.x);}
bool operator ==(const Point &a, const Point &b) {return dcmp(a.x - b.x) && dcmp(a.y - b.y);}
double sqrdist(Point a, Point b) {return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);}
double dist(Point a, Point b) {return sqrt(sqrdist(a, b));}
double sqrdist(Point a) {return a.x * a.x + a.y * a.y;}
double dist(Point a) {return sqrt(sqrdist(a));}
double dist(Point x, Line l) {return fabs(det(x - l.a, l.b - l.a)) / dist(l.b - l.a);}
int sign(double x) {
	if (fabs(x) < eps) return 0;
	else return (x > 0) ? 1 : -1;
}

double getdist(Point p, Point a, Point b) {
	Point v1 = b - a, v2 = p - a, v3 = p - b;
	double ret;
	if (dot(v1, v2) < 0) ret = dist(v2);
	else if (dot(v1, v3) > 0) ret = dist(v3);
	else ret = dist(p, Line(a, b));
	return ret * ret;
}

int n;

int main() {
	//freopen("input.txt", "r", stdin);
	scanf("%d", &n);
	c.read();
	double mindist = INF, maxdist = -INF;
	for (int i = 0; i < n; i++) {
		p[i].read();
	}
	for (int i = 0; i < n; i++) {
		maxdist = std::max(maxdist, sqrdist(p[i], c));
		mindist = std::min(mindist, getdist(c, p[i], p[(i + 1) % n]));
	}
	printf("%.10f\n", (maxdist - mindist) * PI);
	return 0;
}
