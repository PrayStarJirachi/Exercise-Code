#include <cmath>
#include <cstdio>
#include <algorithm>

const double EPS = 1e-8;
const int INF = ~0u >> 2;

int dcmp(const double &x) {
	return fabs(x) < EPS ? 0 : (x > 0 ? 1 : -1);
}

class Point{
public:
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
	void read() {
		scanf("%lf%lf", &x, &y);
	}
	double dist()const {
		return sqrt(x * x + y * y);
	}
	double sqrdist()const {
		return x * x + y * y;
	}
}source, target, windPrevSpeed, windSuccSpeed;

double det(const Point &a, const Point &b) {
	return a.x * b.y - b.x * a.y;
}

double dot(const Point &a, const Point &b) {
	return a.x * b.x + a.y * b.y;
}

double vMax, tMax;

double getAngle(const Point &a, const Point &b) {
	return acos(dot(a, b) / a.dist() / b.dist());
}

bool checkAnswer(const double &answer) {
	Point relativeTarget;
	if (dcmp(answer - tMax) <= 0) relativeTarget = target - windPrevSpeed * answer;
	else relativeTarget = target - windPrevSpeed * tMax - windSuccSpeed * (answer - tMax);
	return dcmp((relativeTarget - source).dist() - vMax * answer) <= 0;
}

int main() {
	freopen("input.txt", "r", stdin);
	source.read();
	target.read();
	scanf("%lf%lf", &vMax, &tMax);
	windPrevSpeed.read();
	windSuccSpeed.read();
	double leftAnswer = 0, rightAnswer = INF;
	for (int binarySearchCounter = 0; binarySearchCounter <= 200; binarySearchCounter++) {
		double middleAnswer = (leftAnswer + rightAnswer) / 2.0;
		if (checkAnswer(middleAnswer)) rightAnswer = middleAnswer;
		else leftAnswer = middleAnswer;
	}
	printf("%.12f\n", leftAnswer);
	return 0;
}
