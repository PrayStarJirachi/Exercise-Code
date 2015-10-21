#include <queue>
#include <cstdio>
#include <algorithm>

const int MAXN = 400001;
const int MAXM = 800001;
const long long INF = 1ll << 40;
const int Maxlog = 20;

struct Edge{
	int node, next;
	long long dist;
}e[MAXM];

struct Road{
	int x, y, c;
	bool operator <(const Road &p)const {
		return c < p.c;
	}
}r[MAXM], tree[MAXM];

struct Heapnode{
	int dist, node;
	bool operator <(const Heapnode &p)const {
		return dist > p.dist;
	}
};

int n, s, m, q, t, h[MAXN], fa[MAXN], p[MAXN], f[MAXN][21], dep[MAXN], c[MAXN];
long long z[MAXN][21], d[MAXN];
bool v[MAXN], w[MAXN];
std::priority_queue<Heapnode> heap;

int getfa(int x) {
	return fa[x] ? fa[x] = getfa(fa[x]) : x;
}

void addedge(int x, int y, long long c) {
	t++; e[t] = (Edge){y, h[x], c}; h[x] = t;
	t++; e[t] = (Edge){x, h[y], c}; h[y] = t;
}

void dijkstra() {
	std::fill(d + 1, d + n + 1, INF);
	for (int i = 1; i <= n; i++) {
		if (!w[i]) continue;
		heap.push((Heapnode){d[i] = 0, i});
	}
	while (!heap.empty()) {
		Heapnode top = heap.top(); heap.pop();
		if (v[top.node]) continue;
		v[top.node] = true;
		for (int i = h[top.node]; i; i = e[i].next)
			if (!v[e[i].node] && d[e[i].node] > top.dist + e[i].dist) {
				d[e[i].node] = top.dist + e[i].dist;
				p[e[i].node] = top.node;
				heap.push((Heapnode){d[e[i].node], e[i].node});
			}
	}
	s = 0;
	for (int i = 1, cnt = 0; i <= n; i++) {
		if (!w[i]) continue;
		c[i] = ++s;
	}
	for (int i = 1; i <= n; i++) {
		if (w[i]) continue;
		fa[getfa(i)] = getfa(p[i]);
	}
	for (int i = 1; i <= n; i++) {
		if (w[i]) continue;
		c[i] = c[getfa(i)];
	}
}

void buildtree(int x) {
	static int q[MAXN];
	int left = 0, right = 0;
	q[++right] = x; v[x] = true;
	while (left < right) {
		left++;
		for (int i = h[q[left]]; i; i = e[i].next) {
			if (e[i].node == f[q[left]][0]) continue;
			dep[e[i].node] = dep[q[left]] + 1;
			f[e[i].node][0] = q[left];
			z[e[i].node][0] = e[i].dist;
			q[++right] = e[i].node;
			v[e[i].node] = true;
		}
	}
	for (int j = 1; j <= Maxlog; j++)
		for (int i = 1; i <= right; i++) {
			int now = q[i];
			f[now][j] = f[f[now][j - 1]][j - 1];
			z[now][j] = std::max(z[now][j - 1], z[f[now][j - 1]][j - 1]);
		}
}

int getAnc(int x, int t) {
	for (int i = 0; i <= Maxlog; i++)
		if (t & (1 << i)) x = f[x][i];
	return x;
}

long long getValue(int x, int t) {
	long long ret = -INF;
	if (t < 0) return ret;
	for (int i = 0; i <= Maxlog; i++)
		if (t & (1 << i)) {
			ret = std::max(ret, z[x][i]);
			x = f[x][i];
		}
	return ret;
}

int getLca(int x, int y) {
	if (dep[x] > dep[y]) x = getAnc(x, dep[x] - dep[y]);
	if (dep[x] < dep[y]) y = getAnc(y, dep[y] - dep[x]);
	if (x == y) return x;
	for (int i = Maxlog; i >= 0; i--) {
		if (f[x][i] == f[y][i]) continue;
		x = f[x][i];
		y = f[y][i];
	}
	return f[x][0];
}

int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d%d%d", &n, &s, &m);
	for (int i = 1; i <= s; i++) {
		int x; scanf("%d", &x);
		w[x] = true;
	}
	for (int i = 1; i <= m; i++) {
		scanf("%d%d%d", &r[i].x, &r[i].y, &r[i].c);
		addedge(r[i].x, r[i].y, r[i].c);
	}
	dijkstra();
	t = 0;
	std::fill(h + 1, h + n + 1, 0);
	std::fill(fa + 1, fa + s + 1, 0);
	for (int i = 1; i <= m; i++) {
		tree[i] = (Road){c[r[i].x], c[r[i].y], d[r[i].x] + d[r[i].y] + r[i].c};
	}
	std::sort(tree + 1, tree + m + 1);
	for (int i = 1; i <= m; i++) {
		int fx = getfa(tree[i].x), fy = getfa(tree[i].y);
		if (fx == fy) continue;
		addedge(tree[i].x, tree[i].y, tree[i].c);
		fa[fx] = fy;
	}
	std::fill(v + 1, v + n + 1, false);
	for (int i = 1; i <= s; i++)
		if (!v[i]) buildtree(i);
	scanf("%d", &q);
	for (int cs = 1; cs <= q; cs++) {
		int x, y, d;
		scanf("%d%d%d", &x, &y, &d);
		x = c[x];
		y = c[y];
		if (getfa(x) != getfa(y)) {
			puts("NIE");
			continue;
		}
		int l = getLca(x, y);
		long long vmax = -INF;
		vmax = std::max(vmax, getValue(x, dep[x] - dep[l]));
		vmax = std::max(vmax, getValue(y, dep[y] - dep[l]));
		printf("%s\n", (vmax <= d) ? "TAK" : "NIE");
	}
	return 0;
}
