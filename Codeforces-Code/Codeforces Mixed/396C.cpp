#include <cstdio>
#include <algorithm>

const int MAXN = 300001;
const int MAXM = 300001;
const int mod = 1000000007;

struct Edge{
	int node, next;
}e[MAXM];

int n, q, t, tot, h[MAXN], d[MAXN], l[MAXN], r[MAXN], tree[MAXN * 6], qsum[MAXN];;
std::pair<int, int> flag[MAXN * 6];
bool v[MAXN * 6];

void addedge(int x, int y) {
	t++; e[t] = (Edge){y, h[x]}; h[x] = t;
}

void predfs(int x) {
	l[x] = ++tot;
	qsum[tot] = (qsum[tot - 1] + d[x]) % mod;
	for (int i = h[x]; i; i = e[i].next) {
		d[e[i].node] = d[x] + 1;
		predfs(e[i].node);
	}
	r[x] = tot;
}

void makeplus(int n, int l, int r, const std::pair<int, int> &p) {
	(tree[n] += (long long)p.first * (r - l + 1) % mod) %= mod;
	(tree[n] += (long long)p.second * (qsum[r] - qsum[l - 1]) % mod) %= mod;
	(flag[n].first += p.first) %= mod;
	(flag[n].second += p.second) %= mod;
	v[n] = true;
}

void pushdown(int n, int l, int r) {
	if (v[n]) {
		makeplus(n << 1, l, l + r >> 1, flag[n]);
		makeplus(n << 1 ^ 1, (l + r >> 1) + 1, r, flag[n]);
		flag[n] = std::make_pair(0, 0);
		v[n] = false;
	}
}

void modify(int n, int l, int r, int x, int y, const std::pair<int, int> &p) {
	if (x <= l && r <= y) {
		makeplus(n, l, r, p);
		return;
	}
	pushdown(n, l, r);
	if ((l + r >> 1) < x) modify(n << 1 ^ 1, (l + r >> 1) + 1, r, x, y, p);
	else if ((l + r >> 1) + 1 > y) modify(n << 1, l, l + r >> 1, x, y, p);
	else{
		modify(n << 1, l, l + r >> 1, x, y, p);
		modify(n << 1 ^ 1, (l + r >> 1) + 1, r, x, y, p);
	}
	tree[n] = tree[n << 1] + tree[n << 1 ^ 1];
}

int query(int n, int l, int r, int x) {
	if (l == r) return tree[n];
	pushdown(n, l, r);
	if (x <= (l + r >> 1)) return query(n << 1, l, l + r >> 1, x);
	else return query(n << 1 ^ 1, (l + r >> 1) + 1, r, x);
}

int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d", &n);
	for (int i = 2; i <= n; i++) {
		int fa; scanf("%d", &fa);
		addedge(fa, i);
	}
	scanf("%d", &q);
	predfs(1);
	for (int i = 1; i <= q; i++) {
		int op, v, x, k;
		scanf("%d", &op);
		if (op == 1) {
			scanf("%d%d%d", &v, &x, &k);
			std::pair<int, int> tmp = std::make_pair(((long long)k * d[v] + x) % mod, -k);
			modify(1, 1, n, l[v], r[v], tmp);
		}
		else{
			scanf("%d", &x);
			printf("%d\n", (query(1, 1, n, l[x]) % mod + mod) % mod);
		}
	}
	return 0;
}
