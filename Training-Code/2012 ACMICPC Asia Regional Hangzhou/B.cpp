#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>

const double EPS = 1e-5;
const double PI = 3.1415926535897932384626;
const int INF = ~0u >> 2;

int dcmp(const double &x) {
	return fabs(x) < EPS ? 0 : (x > 0 ? 1 : -1);
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
	void read() {
		scanf("%lf%lf", &x, &y);
	}
}c, s, z[4];

double r;

double dot(const Point &a, const Point &b) {
	return a.x * b.x + a.y * b.y;
}

double det(const Point &a, const Point &b) {
	return a.x * b.y - b.x * a.y;
}

double dist(const Point &a) {
	return sqrt(a.x * a.x + a.y * a.y);
}

double dist(const Point &a, const Point &b) {
	return dist(a - b);
}

double getPointDist(const Point &a, const Point &b) {
	Point d = b - a;
	int sA = dcmp(dot(a, d)), sB = dcmp(dot(b, d));
	if (sA * sB <= 0) return fabs(det(a, b)) / dist(a, b);
	else return std::min(dist(a), dist(b));
}

double calculate(const double &theta) {
	Point now = Point(c.x + r * cos(theta), c.y + r * sin(theta));
	double answer = INF;
	for (int i = 0; i < 4; i++)
		for (int j = i + 1; j < 4; j++) {
			answer = std::min(answer, getPointDist(z[i] - now, z[j] - now));
		}
	return answer + dist(now, s);
}

int main() {
	freopen("D.in", "r", stdin);
	while (scanf("%lf%lf", &s.x, &s.y) == 2) {
		if (dcmp(s.x) == 0 && dcmp(s.y) == 0) break;
		c.read();
		scanf("%lf", &r);
		z[0].read();
		z[1].read();
		z[2] = Point(z[0].x, z[1].y);
		z[3] = Point(z[1].x, z[0].y);
		int nDivide = 50000;
		double answer = 1e50;
		for (int pick = 0; pick < nDivide; pick++) {
			double theta = 2 * PI / nDivide * pick;
			answer = std::min(answer, calculate(theta));
		}
		printf("%.2f\n", answer);
	}
	return 0;
}
