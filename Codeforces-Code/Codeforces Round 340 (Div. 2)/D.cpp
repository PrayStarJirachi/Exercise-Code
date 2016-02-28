#include <cstdio>
#include <numeric>
#include <iostream>
#include <algorithm>

const double EPS = 1e-7;
const double PI = 3.1415926535897932384626;

struct Point{
	long long x, y;
	void read() {
		std::cin >> x >> y;
	}
}c1, c2, c3;

bool judgex(const Point &a, const Point &b, const Point &c) {
	if (a.y != b.y) return false;
	if (a.x > b.x) return false;
	if (a.x < c.x && c.x < b.x) return false;
	return true;
}

bool judgey(const Point &a, const Point &b, const Point &c) {
	if (a.x != b.x) return false;
	if (a.y > b.y) return false;
	if (a.y < c.y && c.y < b.y) return false;
	return true;
}

int main() {
	// freopen("input.txt", "r", stdin);
	c1.read();
	c2.read();
	c3.read();
	if (c1.x == c2.x && c2.x == c3.x || c1.y == c2.y && c2.y == c3.y) puts("1");
	else if (judgex(c1, c2, c3)) puts("2");
	else if (judgex(c1, c3, c2)) puts("2");
	else if (judgex(c2, c1, c3)) puts("2");
	else if (judgex(c2, c3, c1)) puts("2");
	else if (judgex(c3, c1, c2)) puts("2");
	else if (judgex(c3, c2, c1)) puts("2");
	else if (judgey(c1, c2, c3)) puts("2");
	else if (judgey(c1, c3, c2)) puts("2");
	else if (judgey(c2, c1, c3)) puts("2");
	else if (judgey(c2, c3, c1)) puts("2");
	else if (judgey(c3, c1, c2)) puts("2");
	else if (judgey(c3, c2, c1)) puts("2");
	else puts("3");
	return 0;
}
