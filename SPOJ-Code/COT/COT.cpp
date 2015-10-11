#include <cstdio>
#include <cstring>
#include <algorithm>

const int MAXN = 200001;
const int MAXM = 400001;
const int Maxlog = 20;

struct Edge{
	int node, next;
}e[MAXM];

struct Node{
	int l, r, d;
}t[MAXN * 40];

int n, m, tot, cnt, size, h[MAXN], d[MAXN], w[MAXN], fa[MAXN][21], dep[MAXN], rt[MAXN], base[MAXN];

void addedge(int x, int y) {
	cnt++; e[cnt] = (Edge){y, h[x]}; h[x] = cnt;
	cnt++; e[cnt] = (Edge){x, h[y]}; h[y] = cnt;
}

void insert(int rt, int &newrt, int l, int r, int x) {
	t[newrt = ++size] = t[rt]; t[newrt].d++;
	if (l == r) return;
	if (x <= (l + r >> 1)) insert(t[rt].l, t[newrt].l, l, l + r >> 1, x);
	else insert(t[rt].r, t[newrt].r, (l + r >> 1) + 1, r, x);
}

int query(int xrt, int yrt, int lrt, int brt, int l, int r, int k) {
	if (l == r) return d[l];
	int cnt = t[t[xrt].l].d + t[t[yrt].l].d - 2 * t[t[lrt].l].d + t[t[brt].l].d;
	if (k <= cnt) return query(t[xrt].l, t[yrt].l, t[lrt].l, t[brt].l, l, l + r >> 1, k);
	else return query(t[xrt].r, t[yrt].r, t[lrt].r, t[brt].r, (l + r >> 1) + 1, r, k - cnt);
}

void buildtree(int x) {
	static int q[MAXN];
	int left = 0, right = 0;
	q[++right] = x;
	while (left < right) {
		left++;
		for (int i = h[q[left]]; i; i = e[i].next) {
			if (e[i].node == fa[q[left]][0]) continue;
			fa[e[i].node][0] = q[left];
			q[++right] = e[i].node;
			dep[q[right]] = dep[q[left]] + 1;
		}
	}
	for (int j = 1; j <= Maxlog; j++)
		for (int i = 1; i <= n; i++) {
			fa[i][j] = fa[fa[i][j - 1]][j - 1];
		}
	for (int i = 1; i <= n; i++) {
		w[q[i]] = std::lower_bound(d + 1, d + tot + 1, w[q[i]]) - d;
		insert(rt[fa[q[i]][0]], rt[q[i]], 1, tot, w[q[i]]);
		insert(base[q[i]], base[q[i]], 1, tot, w[q[i]]);
	}
}

int getanc(int x, int t) {
	for (int i = 0; i <= Maxlog; i++)
		if (t & (1 << i)) x = fa[x][i];
	return x;
}

int getlca(int x, int y) {
	if (dep[x] > dep[y]) x = getanc(x, dep[x] - dep[y]);
	if (dep[x] < dep[y]) y = getanc(y, dep[y] - dep[x]);
	if (x == y) return x;
	for (int i = Maxlog; i >= 0; i--)
		if (fa[x][i] != fa[y][i]) {
			x = fa[x][i];
			y = fa[y][i];
		}
	return fa[x][0];
}

int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d", w + i);
		d[i] = w[i];
	}
	for (int i = 1; i < n; i++) {
		int x, y; scanf("%d%d", &x, &y);
		addedge(x, y);
	}
	std::sort(d + 1, d + n + 1);
	tot = std::unique(d + 1, d + n + 1) - d - 1;
	buildtree(1);
	for (int i = 1; i <= m; i++) {
		int x, y, k; scanf("%d%d%d", &x, &y, &k);
		int l = getlca(x, y);
		printf("%d\n", query(rt[x], rt[y], rt[l], base[l], 1, tot, k));
	}
	return 0;
}
