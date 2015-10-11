#include <cstdio>
#include <cstring>
#include <algorithm>

const int MAXN = 40001;
const int MAXM = 80001;
const int INF = ~0u >> 1;

struct Edge{
	int node, next, dist;
}e[MAXM];

struct Road{
	int x, y, c;
}r[MAXM];

struct Node{
	int dmax, dmin;
	Node() {
		dmax = -INF;
		dmin = INF;
	}
	Node(int d) : dmax(d), dmin(d) {}
	Node operator +(const Node &p)const {
		Node ret;
		ret.dmax = std::max(dmax, p.dmax);
		ret.dmin = std::min(dmin, p.dmin);
		return ret;
	}
}tree[MAXN * 6];

int T, n, m, tot, cnt, h[MAXN], t[MAXN], w[MAXN], s[MAXN], z[MAXN], f[MAXN], d[MAXN];
bool flag[MAXN * 6];

void addedge(int x, int y, int c) {
	cnt++; e[cnt] = (Edge){y, h[x], c}; h[x] = cnt;
	cnt++; e[cnt] = (Edge){x, h[y], c}; h[y] = cnt;
}

void predfs(int x) {
	s[x] = 1; z[x] = 0;
	for (int i = h[x]; i; i = e[i].next) {
		if (e[i].node == f[x]) continue;
		f[e[i].node] = x;
		d[e[i].node] = d[x] + 1;
		predfs(e[i].node);
		s[x] += s[e[i].node];
		if (s[z[x]] < s[e[i].node]) z[x] = e[i].node;
	}
}

void getanc(int x, int anc) {
	t[x] = anc; w[x] = ++tot;
	if (z[x]) getanc(z[x], anc);
	for (int i = h[x]; i; i = e[i].next) {
		if (e[i].node == f[x] || e[i].node == z[x]) continue;
		getanc(e[i].node, e[i].node);
	}
}

void makeneg(int n) {
	flag[n] ^= 1;
	std::swap(tree[n].dmax, tree[n].dmin);
	tree[n].dmax = -tree[n].dmax;
	tree[n].dmin = -tree[n].dmin;
}

void pushdown(int n) {
	if (flag[n]) {
		makeneg(n << 1);
		makeneg(n << 1 ^ 1);
		flag[n] = false;
	}
}

void modify(int n, int l, int r, int x, int d) {
	if (l == r) {
		tree[n] = Node(d);
		return;
	}
	pushdown(n);
	if (x <= (l + r >> 1)) modify(n << 1, l, l + r >> 1, x, d);
	else modify(n << 1 ^ 1, (l + r >> 1) + 1, r, x, d);
	tree[n] = tree[n << 1] + tree[n << 1 ^ 1];
}

Node query(int n, int l, int r, int x, int y) {
	if (x <= l && r <= y) return tree[n];
	pushdown(n);
	if (x > (l + r >> 1)) return query(n << 1 ^ 1, (l + r >> 1) + 1, r, x, y);
	else if (y < (l + r >> 1) + 1) return query(n << 1, l, l + r >> 1, x, y);
	else{
		Node left = query(n << 1, l, l + r >> 1, x, y);
		Node right = query(n << 1 ^ 1, (l + r >> 1) + 1, r, x, y);
		return left + right;
	}
}

Node query(int x, int y) {
	int fx = t[x], fy = t[y];
	Node left = Node(), right = Node();
	while (fx != fy) {
		if (d[fx] > d[fy]) {
			left = left + query(1, 1, n, w[fx], w[x]);
			x = f[fx]; fx = t[x];
		}
		else{
			right = right + query(1, 1, n, w[fy], w[y]);
			y = f[fy]; fy = t[y];
		}
	}
	if (x != y) {
		if (d[x] < d[y]) left = left + query(1, 1, n, w[z[x]], w[y]);
		else right = right + query(1, 1, n, w[z[y]], w[x]);
	}
	return left + right;
}

int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		cnt = tot = 0;
		std::fill(h + 1, h + n + 1, 0);
		for (int i = 1; i < n; i++) {
			scanf("%d%d%d", &r[i].x, &r[i].y, &r[i].c);
			addedge(r[i].x, r[i].y, r[i].c);
		}
		predfs(1);
		getanc(1, 1);
		for (int i = 1; i < n; i++) {
			if (d[r[i].x] > d[r[i].y]) std::swap(r[i].x, r[i].y);
			modify(1, 1, n, w[r[i].y], r[i].c);
		}
		while (true) {
			char op[20];
			int x, y;
			scanf("%s", op);
			if (!strcmp(op, "CHANGE")) {
				scanf("%d%d", &x, &y);
				modify(1, 1, n, w[r[x].y], y);
			}
			else if (!strcmp(op, "QUERY")) {
				scanf("%d%d", &x, &y);
				Node ret = query(x, y);
				printf("%d\n", ret.dmax);
			}
			else if (!strcmp(op, "DONE")) break;
		}
	}
	return 0;
}
