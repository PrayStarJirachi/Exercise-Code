#include <cstdio>
#include <algorithm>

const int MAXN = 100001;
const int MAXM = 200001;
const int INF = ~0u >> 2;

struct Edge{
	int node, next;
}e[MAXM];

struct Node{
	int asum, lsum, rsum, zsum;
	Node() {
		asum = 0;
		lsum = -INF;
		rsum = -INF;
		zsum = -INF;
	}
	Node(int d) : asum(d), lsum(d), rsum(d), zsum(d) {}
	Node operator +(const Node &rhs)const {
		Node ret;
		ret.asum = asum + rhs.asum;
		ret.lsum = std::max(lsum, asum + rhs.lsum);
		ret.rsum = std::max(rsum + rhs.asum, rhs.rsum);
		ret.zsum = std::max(zsum, rhs.zsum);
		ret.zsum = std::max(ret.zsum, rsum + rhs.lsum);
		return ret;
	}
}tree[MAXN * 6];

int n, q, cnt, tot, h[MAXN], d[MAXN], t[MAXN], f[MAXN], s[MAXN], z[MAXN], w[MAXN], o[MAXN], a[MAXN];
std::pair<bool, int> flag[MAXN * 6];

void addedge(int x, int y) {
	cnt++; e[cnt] = (Edge){y, h[x]}; h[x] = cnt;
	cnt++; e[cnt] = (Edge){x, h[y]}; h[y] = cnt;
}

void makesame(int n, int l, int r, int d) {
	flag[n] = std::make_pair(true, d);
	tree[n].asum = d * (r - l + 1);
	if (d > 0) {
		tree[n].lsum = d * (r - l + 1);
		tree[n].rsum = d * (r - l + 1);
		tree[n].zsum = d * (r - l + 1);
	}
	else{
		tree[n].lsum = d;
		tree[n].rsum = d;
		tree[n].zsum = d;
	}
}

void pushdown(int n, int l, int r) {
	if (flag[n].first) {
		makesame(n << 1, l, l + r >> 1, flag[n].second);
		makesame(n << 1 ^ 1, (l + r >> 1) + 1, r, flag[n].second);
		flag[n] = std::make_pair(false, 0);
	}
}

void modify(int n, int l, int r, int x, int y, int d) {
	if (x <= l && r <= y) {
		makesame(n, l, r, d);
		return;
	}
	pushdown(n, l, r);
	if ((l + r >> 1) < x) modify(n << 1 ^ 1, (l + r >> 1) + 1, r, x, y, d);
	else if ((l + r >> 1) + 1 > y) modify(n << 1, l, l + r >> 1, x, y, d);
	else{
		modify(n << 1, l, l + r >> 1, x, y, d);
		modify(n << 1 ^ 1, (l + r >> 1) + 1, r, x, y, d);
	}
	tree[n] = tree[n << 1] + tree[n << 1 ^ 1];
}

Node query(int n, int l, int r, int x, int y) {
	if (x <= l && r <= y) return tree[n];
	pushdown(n, l, r);
	if ((l + r >> 1) < x) return query(n << 1 ^ 1, (l + r >> 1) + 1, r, x, y);
	else if ((l + r >> 1) + 1 > y) return query(n << 1, l, l + r >> 1, x, y);
	else{
		Node left = query(n << 1, l, l + r >> 1, x, y);
		Node right = query(n << 1 ^ 1, (l + r >> 1) + 1, r, x, y);
		return left + right;
	}
}

void modify(int x, int y, int val) {
	int fx = t[x], fy = t[y];
	while (fx != fy) {
		if (d[fx] > d[fy]) {
			modify(1, 1, n, w[fx], w[x], val);
			x = f[fx]; fx = t[x];
		}
		else{
			modify(1, 1, n, w[fy], w[y], val);
			y = f[fy]; fy = t[y];
		}
	}
	if (d[x] < d[y]) modify(1, 1, n, w[x], w[y], val);
	else modify(1, 1, n, w[y], w[x], val);
}

Node query(int x, int y) {
	int fx = t[x], fy = t[y];
	Node left = Node(), right = Node();
	while (fx != fy) {
		if (d[fx] > d[fy]) {
			left = query(1, 1, n, w[fx], w[x]) + left;
			x = f[fx]; fx = t[x];
		}
		else{
			right = query(1, 1, n, w[fy], w[y]) + right;
			y = f[fy]; fy = t[y];
		}
	}
	if (d[x] < d[y]) {
		right = query(1, 1, n, w[x], w[y]) + right;
	}
	else{
		left = query(1, 1, n, w[y], w[x]) + left;
	}
	std::swap(left.lsum, left.rsum);
	return left + right;
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
	t[x] = anc; w[x] = ++tot; o[tot] = x;
	if (z[x]) getanc(z[x], anc);
	for (int i = h[x]; i; i = e[i].next) {
		if (e[i].node == f[x] || e[i].node == z[x]) continue;
		getanc(e[i].node, e[i].node);
	}
}

void buildtree(int n, int l, int r) {
	if (l == r) {
		tree[n] = Node(a[o[l]]);
		return;
	}
	buildtree(n << 1, l, l + r >> 1);
	buildtree(n << 1 ^ 1, (l + r >> 1) + 1, r);
	tree[n] = tree[n << 1] + tree[n << 1 ^ 1];
}

int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	for (int i = 1; i < n; i++) {
		int x, y; scanf("%d%d", &x, &y);
		addedge(x, y);
	}
	predfs(1);
	getanc(1, 1);
	buildtree(1, 1, n);
	scanf("%d", &q);
	for (int i = 1; i <= q; i++) {
		int op, x, y, c;
		scanf("%d", &op);
		if (op == 1) {
			scanf("%d%d", &x, &y);
			Node ret = query(x, y);
			printf("%d\n", std::max(0, ret.zsum));
		}
		else{
			scanf("%d%d%d", &x, &y, &c);
			modify(x, y, c);
		}
	}
	return 0;
}
