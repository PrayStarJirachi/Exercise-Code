#include <cstdio>
#include <algorithm>

const int MAXN = 10001;

struct Point{
	int x, y;
	Point() {}
	Point(int x, int y) : x(x), y(y) {}
	Point operator -(const Point &p)const {
		return Point(x - p.x, y - p.y);
	}
	void read() {
		scanf("%d%d", &x, &y);
	}
}p[MAXN], c[MAXN];

int T, n;

int det(const Point &a, const Point &b) {
	return a.x * b.y - b.x * a.y;
}

int sqrdist(const Point &a, const Point &b) {
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

int dot(const Point &a, const Point &b) {
	return a.x * b.x + a.y * b.y;
}

bool Pair_Comp(const Point &a, const Point &b) {
	if (a.x - b.x < 0) return true;
	if (a.x - b.x > 0) return false;
	return a.y - b.y < 0;
}

int Convex_Hull(int n, Point *P, Point *C) {
	std::sort(P, P + n, Pair_Comp);
	int top = 0;
	for (int i = 0; i < n; i++) {
		while (top >= 2 && det(C[top - 1] - C[top - 2], P[i] - C[top - 2]) <= 0) top--;
		C[top++] = P[i];
	}
	int lasttop = top;
	for (int i = n - 1; i >= 0; i--) {
		while (top > lasttop && det(C[top - 1] - C[top - 2], P[i] - C[top - 2]) <= 0) top--;
		C[top++] = P[i];
	}
	return top;
}

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++) c[i].read();
		int tot = Convex_Hull(n, c, p);
		bool check = true;
		if (tot - 1 != n) {
			puts("NO");
			continue;
		}
		int sqrlen = sqrdist(p[0], p[1]);
		for (int i = 1; i < n; i++) {
			int tmp = sqrdist(p[i], p[(i + 1) % n]);
			if (tmp != sqrlen) {
				check = false;
				break;
			}
		}
		if (!check) {
			puts("NO");
			continue;
		}
		sqrlen = dot(p[1] - p[0], p[2] - p[1]);
		for (int i = 1; i < n; i++) {
			int tmp = dot(p[(i + 1) % n] - p[i], p[(i + 2) % n] - p[(i + 1) % n]);
			if (tmp != sqrlen) {
				check = false;
				break;
			}
		}
		if (!check) {
			puts("NO");
			continue;
		}
		puts("YES");
	}
	return 0;
}
