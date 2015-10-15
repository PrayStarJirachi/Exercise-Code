#include <cstdio>
#include <vector>
#include <algorithm>

const int MAXN = 300001;
const int INF = 20000000;

struct Point{
	int x, y;
	Point() {}
	Point(int x, int y) : x(x), y(y) {}
	bool operator <(const Point &rhs)const {
		return x < rhs.x;
	}
}p[MAXN];

int T, n, w, h;
long long tree[MAXN * 6], flag[MAXN * 6];
std::vector<int> vector;

void buildtree(int n, int l, int r) {
	if (l == r) {
		tree[n] = 0;
		return;
	}
	flag[n] = 0;
	buildtree(n << 1, l, l + r >> 1);
	buildtree(n << 1 ^ 1, (l + r >> 1) + 1, r);
	tree[n] = std::max(tree[n << 1], tree[n << 1 ^ 1]);
}

void makedelta(int n, long long d) {
	tree[n] += d;
	flag[n] += d;
}

void pushdown(int n) {
	if (flag[n]) {
		makedelta(n << 1, flag[n]);
		makedelta(n << 1 ^ 1, flag[n]);
		flag[n] = 0;
	}
}

void modify(int n, int l, int r, int x, int y, int d) {
	if (r < x || l > y) return;
	if (x <= l && r <= y) {
		makedelta(n, d);
		return;
	}
	pushdown(n);
	modify(n << 1, l, l + r >> 1, x, y, d);
	modify(n << 1 ^ 1, (l + r >> 1) + 1, r, x, y, d);
	tree[n] = std::max(tree[n << 1], tree[n << 1 ^ 1]);
}

bool cmp(const Point &a, const Point &b) {
	return a.y < b.y;
}

int getId(int x) {
	int ret = std::lower_bound(vector.begin(), vector.end(), x) - vector.begin();
	if (ret == (int)vector.size()) {
		for (;;);
	}
	return std::lower_bound(vector.begin(), vector.end(), x) - vector.begin();
}

int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d", &T);
	for (int cs = 1; cs <= T; cs++) {
		scanf("%d%d%d", &n, &w, &h);
		vector.clear();
		for (int i = 1; i <= n; i++) {
			scanf("%d%d", &p[i].x, &p[i].y);
			vector.push_back(p[i].y);
			vector.push_back(p[i].y - h + 1);
		}
		std::sort(vector.begin(), vector.end());
		vector.erase(std::unique(vector.begin(), vector.end()), vector.end());
		std::sort(p + 1, p + n + 1, cmp);
		int tot = vector.size();
		buildtree(1, 0, tot - 1);
		for (int i = 1; i <= n; i++) {
			modify(1, 0, tot - 1, getId(p[i].y - h + 1), getId(p[i].y), 1);
		}
		std::sort(p + 1, p + n + 1);
		long long answer = 0;
		for (int i = 1, z = 0, l = 1; i <= n; i++) {
			if (i + 1 <= n && p[i + 1].x == p[i].x) continue;
			int tmp = z;
			//printf("I = %d\n", i);
			while (z + 1 <= n && p[z + 1].x <= p[i].x + w - 1) {
				z++;
				modify(1, 0, tot - 1, getId(p[z].y - h + 1), getId(p[z].y), -INF);
			}
			answer = std::max(answer, std::max(tree[1], 0ll) + z - l + 1);
			for (int j = l; j <= i; j++) {
				modify(1, 0, tot - 1, getId(p[j].y - h + 1), getId(p[j].y), INF);
			}
			answer = std::max(answer, std::max(tree[1], 0ll) + z - i);
			l = i + 1;
		}
		printf("Case #%d: %lld\n", cs, answer);
	}
	return 0;
}
