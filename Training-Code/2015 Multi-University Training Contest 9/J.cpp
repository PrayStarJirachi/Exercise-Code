#include <cstdio>
#include <algorithm>

const int MOD = 1000000007;
const int MAXN = 111111;
const int MAXM = 222222;

struct Edge{
	int node, next;
}e[MAXM];

int n, m, tot, wsum, cnt, h[MAXN], t[MAXN], d[MAXN], s[MAXN], z[MAXN], f[MAXN], w[MAXN], bit[2][MAXN];
std::pair<int, int> o[MAXN];

void addedge(int x, int y) {
	tot++; e[tot] = (Edge){y, h[x]}; h[x] = tot;
	tot++; e[tot] = (Edge){x, h[y]}; h[y] = tot;
}

void modify(int *c, int x, int d) {
	for (int i = x; i <= n; i += i & -i) {
		c[i] = (c[i] + d) % MOD;
	}
}

int query(int *c, int x, int y) {
	int ret = 0;
	for (int i = y; i; i -= i & -i) ret = (ret + c[i]) % MOD;
	for (int i = x - 1; i; i -= i & -i) ret = (ret - c[i]) % MOD;
	return ret;
}

void predfs(int x) {
	s[x] = 1; z[x] = 0;
	for (int i = h[x]; i; i = e[i].next) {
		if (e[i].node == f[x]) continue;
		f[e[i].node] = x;
		d[e[i].node] = d[x] + 1;
		predfs(e[i].node);
		s[x] += s[e[i].node];
		if (s[e[i].node] > s[z[x]]) z[x] = e[i].node;
	}
}

int getanc(int x, int anc) {
	t[x] = anc; o[x].first = ++cnt;
	if (z[x]) getanc(z[x], anc);
	for (int i = h[x]; i; i = e[i].next) {
		if (e[i].node == f[x] || e[i].node == z[x]) continue;
		getanc(e[i].node, e[i].node);
	}
	o[x].second = cnt;
}

void modify(int x, int d) {
	for (int i = f[t[x]], l = t[x]; i; l = t[i], i = f[t[i]]) {
		int tmp = query(bit[0], o[l].first, o[l].second);
		tmp = 2ll * tmp * d % MOD;
		tmp = (tmp + 1ll * d * d % MOD) % MOD;
		modify(bit[1], o[i].first, tmp);
	}
	modify(bit[0], o[x].first, d);
}

int query(int x, int y) {
	int fx = t[x], fy = t[y], ret = 0, tmp, lx = x, ly = y;
	while (fx != fy) {
		if (d[fx] > d[fy]) {
			if (z[x]) {
				tmp = query(bit[0], o[z[x]].first, o[z[x]].second);
				ret = (ret + 1ll * tmp * tmp % MOD) % MOD;
			}
			tmp = query(bit[1], o[fx].first, o[x].first);
			ret = (ret + tmp) % MOD;
			tmp = query(bit[0], o[fx].first, o[fx].second);
			ret = (ret - 1ll * tmp * tmp % MOD) % MOD;
			x = f[fx]; fx = t[x];
		}
		else{
			if (z[y]) {
				tmp = query(bit[0], o[z[y]].first, o[z[y]].second);
				ret = (ret + 1ll * tmp * tmp % MOD) % MOD;
			}
			tmp = query(bit[1], o[fy].first, o[y].first);
			ret = (ret + tmp) % MOD;
			tmp = query(bit[0], o[fy].first, o[fy].second);
			ret = (ret - 1ll * tmp * tmp % MOD) % MOD;
			y = f[fy]; fy = t[y];
		}
	}
	if (d[x] > d[y]) std::swap(x, y);
	tmp = query(bit[1], o[x].first, o[y].first);
	ret = (ret + tmp) % MOD;
	tmp = (wsum - query(bit[0], o[x].first, o[x].second)) % MOD;
	ret = (ret + 1ll * tmp * tmp % MOD) % MOD;
	if (z[y]) {
		tmp = query(bit[0], o[z[y]].first, o[z[y]].second);
		ret = (ret + 1ll * tmp * tmp % MOD) % MOD;
	}
	return ret;
}

int main() {
	freopen("J.in", "r", stdin);
	while (scanf("%d%d", &n, &m) == 2) {
		tot = wsum = cnt = 0;
		std::fill(h + 1, h + n + 1, 0);
		std::fill(bit[0] + 1, bit[0] + n + 1, 0);
		std::fill(bit[1] + 1, bit[1] + n + 1, 0);
		for (int i = 1; i <= n; i++) {
			scanf("%d", w + i);
			wsum = (wsum + w[i]) % MOD;
		}
		for (int i = 1; i < n; i++) {
			int x, y;
			scanf("%d%d", &x, &y);
			addedge(x, y);
		}
		predfs(1);
		getanc(1, 1);
		for (int i = 1; i <= n; i++) modify(i, w[i]);
		for (int i = 1; i <= m; i++) {
			int op, x, y;
			scanf("%d%d%d", &op, &x, &y);
			if (op == 1) {
				int delta = (y - w[x]) % MOD;
				wsum = (wsum + delta) % MOD;
				modify(x, delta);
				w[x] = y;
			}
			else{
				int answer = query(x, y);
				answer = (1ll * wsum * wsum % MOD - answer) % MOD;
				answer = (answer % MOD + MOD) % MOD;
				printf("%d\n", answer);
			}
		}
	}
	return 0;
}
