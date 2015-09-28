#include <cstdio>
#include <cstring>
#include <algorithm>

const int MAXN = 1000001;

int n, sBlock;

struct Point{
	int x, y, id;
	void read(int num) {
		id = num;
		scanf("%d%d", &x, &y);
	}
}p[MAXN];

bool cmpx(const Point &a, const Point &b) {
	if (a.x / sBlock < b.x / sBlock) return true;
	if (a.x / sBlock > b.x / sBlock) return false;
	if ((a.x / sBlock) & 1) return a.y < b.y;
	else return a.y > b.y;
}

bool cmpy(const Point &a, const Point &b) {
	if (a.y / sBlock < b.y / sBlock) return true;
	if (a.y / sBlock > b.y / sBlock) return false;
	if ((a.y / sBlock) & 1) return a.x < b.x;
	else return a.x > b.x;
}

bool check() {
	long long answer = 0;
	for (int i = 2; i <= n; i++) {
		answer += std::abs(p[i].x - p[i - 1].x) + std::abs(p[i].y - p[i - 1].y);
	}
	return answer <= 2500000000ll;
}

int main() {
	sBlock = 1000;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) p[i].read(i);
	std::sort(p + 1, p + n + 1, cmpx);
	if (check()) {
		for (int i = 1; i <= n; i++)
			printf("%d%c", p[i].id, " \n"[i == n]);
		return 0;
	}
	std::sort(p + 1, p + n + 1, cmpy);
	if (check()) {
		for (int i = 1; i <= n; i++)
			printf("%d%c", p[i].id, " \n"[i == n]);
		return 0;
	}
	return 0;
}
