#include <cstdio>
#include <algorithm>

const int MAXN = 111111;
const int INF = ~0u >> 2;

int n, bit[MAXN], a[MAXN], s[MAXN], q[MAXN];

struct Segment_Tree{
	int M, tree[MAXN * 6];
	void build(int n, int l, int r, int *a) {
		if (l == r) {
			tree[n] = a[l];
			return;
		}
		build(n << 1, l, l + r >> 1, a);
		build(n << 1 ^ 1, (l + r >> 1) + 1, r, a);
		tree[n] = std::min(tree[n << 1], tree[n << 1 ^ 1]);
	}
	int query(int n, int l, int r, int x, int y) {
		if (r < x || l > y) return INF;
		if (x <= l && r <= y) return tree[n];
		int left = query(n << 1, l, l + r >> 1, x, y);
		int right = query(n << 1 ^ 1, (l + r >> 1) + 1, r, x, y);
		return std::min(left, right);
	}
}t;

void add(int x, int d) {
	for (int i = x; i <= n; i += i & -i) {
		bit[i] = std::max(bit[i], d);
	}
}

int query(int x) {
	int ret = 0;
	for (int i = x; i; i -= i & -i) {
		ret = std::max(ret, bit[i]);
	}
	return ret;
}

int main() {
	freopen("C.in", "r", stdin);
	scanf("%d", &n);
	q[0] = -INF;
	for (int i = 1; i <= n; i++) {
		scanf("%d", a + i);
		q[i] = std::max(q[i - 1], a[i]);
	}
	s[n + 1] = INF;
	for (int i = n; i >= 1; i--) s[i] = std::min(s[i + 1], a[i]);
	int answer = 0;
	for (int i = 1; i <= n; i++)
		if (q[i - 1] <= s[i]) answer++;
	//printf("%d\n", dp[n]);
	printf("%d\n", answer);
	return 0;
}
