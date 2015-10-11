#include <cmath>
#include <cstdio>
#include <algorithm>

#ifdef WIN32
	#define LL "%I64d"
#else
	#define LL "%lld"
#endif

const int MAXN = 100001;

int n, q, cs;
long long treesum[MAXN * 4], treemax[MAXN * 4];

void modify(int n, int l, int r, int x, int y) {
	if (r < x || l > y) return;
	if (l == r) {
		long long tmp = (long long)floor(sqrt(treesum[n]));
		treemax[n] = treesum[n] = tmp;
		return;
	}
	if (treemax[n << 1] > 1) modify(n << 1, l, l + r >> 1, x, y);
	if (treemax[n << 1 ^ 1] > 1) modify(n << 1 ^ 1, (l + r >> 1) + 1, r, x, y);
	treemax[n] = std::max(treemax[n << 1], treemax[n << 1 ^ 1]);
	treesum[n] = treesum[n << 1] + treesum[n << 1 ^ 1];
}

void insert(int n, int l, int r, int x, long long d) {
	if (l == r) {
		treesum[n] = treemax[n] = d;
		return;
	}
	if (x <= (l + r >> 1)) insert(n << 1, l, l + r >> 1, x, d);
	else insert(n << 1 ^ 1, (l + r >> 1) + 1, r, x, d);
	treemax[n] = std::max(treemax[n << 1], treemax[n << 1 ^ 1]);
	treesum[n] = treesum[n << 1] + treesum[n << 1 ^ 1];
}

long long query(int n, int l, int r, int x, int y) {
	if (r < x || l > y) return 0;
	if (x <= l && r <= y) return treesum[n];
	long long left = query(n << 1, l, l + r >> 1, x, y);
	long long right = query(n << 1 ^ 1, (l + r >> 1) + 1, r, x, y);
	return left + right;
}

int main() {
	freopen("input.txt", "r", stdin);
	while (scanf("%d", &n) == 1) {
		printf("Case #%d:\n", ++cs);
		for (int i = 1; i <= n; i++) {
			long long x;
			scanf(LL, &x);
			insert(1, 1, n, i, x);
		}
		scanf("%d", &q);
		for (int i = 1; i <= q; i++) {
			int op, x, y;
			scanf("%d%d%d", &op, &x, &y);
			if (x > y) std::swap(x, y);
			if (op == 0) {
				modify(1, 1, n, x, y);
			}
			else{
				printf(LL "\n", query(1, 1, n, x, y));
			}
		}
		puts("");
	}
	return 0;
}
