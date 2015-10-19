#include <cstdio>
#include <vector>
#include <algorithm>

const int MAXN = 100001;
const int MAXM = 200001;
const int Maxlog = 20;

struct Node{
	int l, r, d;
}t[MAXN * 40];

struct Edge{
	int node, next;
}e[MAXM];

int n, m, q, tot, size, h[MAXN], f[MAXN][21], d[MAXN], b[MAXN], rt[MAXN];
std::vector<int> l[MAXN];

void insert(int rt, int &newrt, int l, int r, int x) {
	t[newrt = ++size] = t[rt]; t[newrt].d++;
	if (l == r) return;
	if (x <= (l + r >> 1)) insert(t[rt].l, t[newrt].l, l, l + r >> 1, x);
	else insert(t[rt].r, t[newrt].r, (l + r >> 1) + 1, r, x);
}

void addedge(int x, int y) {
	tot++; e[tot] = (Edge){y, h[x]}; h[x] = tot;
	tot++; e[tot] = (Edge){x, h[y]}; h[y] = tot;
}

void buildtree(int x) {
	static int q[MAXN];
	int left = 0, right = 0;
	q[++right] = x;
	for (std::vector<int>::iterator it = l[q[right]].begin(); it != l[q[right]].end(); it++) {
		insert(rt[q[right]], rt[q[right]], 1, m, *it);
		insert(b[q[right]], b[q[right]], 1, m, *it);
	}
	while (left < right) {
		left++;
		for (int i = h[q[left]]; i; i = e[i].next) {
			if (e[i].node == f[q[left]][0]) continue;
			q[++right] = e[i].node;
			f[q[right]][0] = q[left];
			d[q[right]] = d[q[left]] + 1;
			rt[q[right]] = rt[q[left]];
			for (std::vector<int>::iterator it = l[q[right]].begin(); it != l[q[right]].end(); it++) {
				insert(rt[q[right]], rt[q[right]], 1, m, *it);
				insert(b[q[right]], b[q[right]], 1, m, *it);
			}
		}
	}
	for (int j = 1; j <= Maxlog; j++)
		for (int i = 1; i <= n; i++)
			f[i][j] = f[f[i][j - 1]][j - 1];
}

void print(int xrt, int yrt, int lrt, int brt, int l, int r, int d) {
	if (!d) return;
	if (l == r) {
		int cnt = t[xrt].d + t[yrt].d - 2 * t[lrt].d + t[brt].d;
		for (int j = 1; j <= cnt && j <= d; j++)
			printf(" %d", l);
		return;
	}
	int cntleft = t[t[xrt].l].d + t[t[yrt].l].d - 2 * t[t[lrt].l].d + t[t[brt].l].d;
	int cntright = t[t[xrt].r].d + t[t[yrt].r].d - 2 * t[t[lrt].r].d + t[t[brt].r].d;
	if (cntleft) {
		print(t[xrt].l, t[yrt].l, t[lrt].l, t[brt].l, l, l + r >> 1, d);
		d = std::max(0, d - cntleft);
	}
	if (cntright) {
		print(t[xrt].r, t[yrt].r, t[lrt].r, t[brt].r, (l + r >> 1) + 1, r, d);
	}
}

int getanc(int x, int t) {
	for (int i = 0; i <= Maxlog; i++)
		if (t & (1 << i)) x = f[x][i];
	return x;
}

int getlca(int x, int y) {
	if (d[x] > d[y]) x = getanc(x, d[x] - d[y]);
	if (d[x] < d[y]) y = getanc(y, d[y] - d[x]);
	if (x == y) return x;
	for (int i = Maxlog; i >= 0; i--)
		if (f[x][i] != f[y][i]) {
			x = f[x][i];
			y = f[y][i];
		}
	return f[x][0];
}

int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d%d%d", &n, &m, &q);
	for (int i = 1; i < n; i++) {
		int x, y; scanf("%d%d", &x, &y);
		addedge(x, y);
	}
	for (int i = 1; i <= m; i++) {
		int x; scanf("%d", &x);
		l[x].push_back(i);
	}
	buildtree(1);
	for (int i = 1; i <= q; i++) {
		int x, y, c;
		scanf("%d%d%d", &x, &y, &c);
		int l = getlca(x, y);
		c = std::min(c, t[rt[x]].d + t[rt[y]].d - 2 * t[rt[l]].d + t[b[l]].d);
		printf("%d", c);
		print(rt[x], rt[y], rt[l], b[l], 1, m, c);
		puts("");
	}
	return 0;
}
