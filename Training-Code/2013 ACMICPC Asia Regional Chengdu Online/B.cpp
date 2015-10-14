#include <cstdio>
#include <algorithm>

#ifdef WIN32
	#define LL "%I64d"
#else
	#define LL "%lld"
#endif

const int MAXN = 100101;
const int MAXM = 200101;
const int Maxlog = 20;
const unsigned long long INF = 1ll << 35;

struct Edge{
	int node, next, dist;
}e[MAXM];

struct Node{
	int l, r, cnt;
	unsigned long long d;
}tree[MAXN * 20];

int T, n, m, size, t, tot, rt[MAXN], h[MAXN], f[MAXN][21], dep[MAXN];
unsigned long long d[MAXN], val[MAXN][21];

void addedge(int x, int y, int c) {
	t++; e[t] = (Edge){y, h[x], c}; h[x] = t;
	t++; e[t] = (Edge){x, h[y], c}; h[y] = t;
}

void insert(int rt, int &newrt, int l, int r, int x) {
	tree[newrt = ++size] = tree[rt];
	tree[newrt].cnt++;
	tree[newrt].d += d[x];
	if (l == r) return;
	if (x <= (l + r >> 1)) insert(tree[rt].l, tree[newrt].l, l, l + r >> 1, x);
	else insert(tree[rt].r, tree[newrt].r, (l + r >> 1) + 1, r, x);
}

std::pair<int, unsigned long long> query(int xrt, int yrt, int lrt, int l, int r, int x, int y) {
	if (r < x || l > y) return std::make_pair(0, 0ll);
	if (x <= l && r <= y) {
		std::pair<int, unsigned long long> ret;
		ret.first = tree[xrt].cnt + tree[yrt].cnt - 2 * tree[lrt].cnt;
		ret.second = tree[xrt].d + tree[yrt].d - 2 * tree[lrt].d;
		return ret;
	}
	std::pair<int, unsigned long long> left = query(tree[xrt].l, tree[yrt].l, tree[lrt].l, l, l + r >> 1, x, y);
	std::pair<int, unsigned long long> right = query(tree[xrt].r, tree[yrt].r, tree[lrt].r, (l + r >> 1) + 1, r, x, y);
	return std::make_pair(left.first + right.first, left.second + right.second);
}

void buildtree(int x) {
	static int q[MAXN];
	int left = 0, right = 0;
	q[++right] = x;
	while (left < right) {
		left++;
		for (int i = h[q[left]]; i; i = e[i].next) {
			if (e[i].node == f[q[left]][0]) continue;
			q[++right] = e[i].node;
			f[q[right]][0] = q[left];
			dep[q[right]] = dep[q[left]] + 1;
			val[q[right]][0] = e[i].dist;
			int tmp = std::lower_bound(d + 1, d + tot + 1, e[i].dist) - d;
			insert(rt[q[left]], rt[q[right]], 1, tot, tmp);
		}
	}
	for (int j = 1; j <= Maxlog; j++)
		for (int i = 1; i <= n; i++) {
			f[i][j] = f[f[i][j - 1]][j - 1];
			val[i][j] = std::min(val[i][j - 1], val[f[i][j - 1]][j - 1]);
		}
}

int getanc(int x, int t) {
	for (int i = 0; i <= Maxlog; i++)
		if (t & (1 << i)) x = f[x][i];
	return x;
}

int getlca(int x, int y) {
	if (dep[x] > dep[y]) x = getanc(x, dep[x] - dep[y]);
	if (dep[x] < dep[y]) y = getanc(y, dep[y] - dep[x]);
	if (x == y) return x;
	for (int i = Maxlog; i >= 0; i--)
		if (f[x][i] != f[y][i]) {
			x = f[x][i];
			y = f[y][i];
		}
	return f[x][0];
}

int querymin(int x, int y) {
	int l = getlca(x, y);
	int stepX = dep[x] - dep[l];
	int stepY = dep[y] - dep[l];
	unsigned long long ret = INF;
	for (int i = 0; i <= Maxlog; i++)
		if (stepX & (1 << i)) {
			ret = std::min(ret, val[x][i]);
			x = f[x][i];
		}
	for (int i = 0; i <= Maxlog; i++)
		if (stepY & (1 << i)) {
			ret = std::min(ret, val[y][i]);
			y = f[y][i];
		}
	return ret;
}

bool check(int x, int y, int l, unsigned long long budget, unsigned long long initflow, unsigned long long A, unsigned long long B, const unsigned long long &ans) {
	B = std::min(A, B);
	unsigned long long cost = (ans - initflow - 1) * B + A;
	int tmp = std::upper_bound(d + 1, d + tot + 1, ans) - d - 1;
	std::pair<int, unsigned long long> ret = query(rt[x], rt[y], rt[l], 1, tot, 1, tmp);
	cost = std::min(cost, (ans * ret.first - ret.second) * B);
	return cost <= budget;
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("srcout.txt", "w", stdout);
	scanf("%d", &T);
	for (int cs = 1; cs <= T; cs++) {
		printf("Case #%d:\n", cs);
		scanf("%d%d", &n, &m);
		size = t = 0;
		std::fill(h + 1, h + n + 1, 0);
		for (int i = 1; i < n; i++) {
			int x, y, c; scanf("%d%d%d", &x, &y, &c);
			addedge(x, y, c);
			d[i] = c;
		}
		std::sort(d + 1, d + n);
		tot = std::unique(d + 1, d + n) - d - 1;
		buildtree(1);
		for (int i = 1; i <= m; i++) {
			int s, t;
			unsigned long long k, a, b;
			long long K, A, B;
			scanf("%d%d" LL LL LL, &s, &t, &K, &A, &B);
			k = K; a = A; b = B;
			int lca = getlca(s, t);
			unsigned long long initflow = querymin(s, t);
			unsigned long long left = initflow, right = INF;
			while (left < right) {
				unsigned long long mid = (left + right >> 1ll) + 1ll;
				if (check(s, t, lca, k, initflow, a, b, mid)) left = mid;
				else right = mid - 1;
			}
			long long L = left;
			printf(LL "\n", L);
		}
	}
	return 0;
}
