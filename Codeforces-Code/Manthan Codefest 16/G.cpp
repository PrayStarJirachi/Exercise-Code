#include <bits/stdc++.h>

const int MAXN = 110001;
const int MAXM = 1100;

int n, m, q, tot, w[MAXN], depth, M, v[MAXM], b[MAXN * 5];
std::vector<int> g[MAXN];
std::pair<int, int> o[MAXN];
std::bitset<MAXM> prime, tree[MAXN * 5];

void rotate(int n, int d) {
	(b[n] += d) %= m;
	tree[n] = (tree[n] >> (m - d)) | (tree[n] << (MAXM - m) << d >> (MAXM - m));
}

void pushdown(int x) {
	if (b[x]) {
		rotate(x << 1, b[x]);
		rotate(x << 1 ^ 1, b[x]);
		b[x] = 0;
	}
}

void dfs(int x, int fa) {
	o[x].first = ++tot;
	for (auto son : g[x]) {
		if (son == fa) continue;
		dfs(son, x);
	}
	o[x].second = tot;
}

void add(int x, int y, int c) {
	x += M - 1;
	y += M + 1;
	int l = x, r = y;
	for (int i = depth; i >= 0; i--) {
		pushdown(x >> i);
		pushdown(y >> i);
	}
	for (; x ^ y ^ 1; x >>= 1, y >>= 1) {
		if (x & 1 ^ 1) rotate(x ^ 1, c);
		if (y & 1) rotate(y ^ 1, c);
	}
	for (l >>= 1; l; l >>= 1) tree[l] = tree[l << 1] | tree[l << 1 ^ 1];
	for (r >>= 1; r; r >>= 1) tree[r] = tree[r << 1] | tree[r << 1 ^ 1];
}

std::bitset<MAXM> query(int x, int y) {
	x += M - 1;
	y += M + 1;
	for (int i = depth; i >= 0; i--) {
		pushdown(x >> i);
		pushdown(y >> i);
	}
	std::bitset<MAXM> ret;
	ret.reset();
	for (; x ^ y ^ 1; x >>= 1, y >>= 1) {
		if (x & 1 ^ 1) ret |= tree[x ^ 1];
		if (y & 1) ret |= tree[y ^ 1];
	}
	return ret;
}

int main() {
	std::cin >> n >> m;
	for (M = 1; M <= n + 1; M <<= 1) depth++;
	for (int i = 2; i < m; i++) {
		if (v[i]) continue;
		prime.set(i);
		for (int j = 2 * i; j < m; j += i) {
			v[j] = true;
		}
	}
	for (int i = 1; i <= n; i++) std::cin >> w[i];
	for (int i = 1; i < n; i++) {
		int x, y;
		std::cin >> x >> y;
		g[x].push_back(y);
		g[y].push_back(x);
	}
	dfs(1, 0);
	for (int i = 1; i <= n; i++) {
		tree[M + o[i].first].set(w[i] % m);
	}
	for (int i = M; i >= 1; i--) {
		tree[i] = tree[i << 1] | tree[i << 1 ^ 1];
	}
	std::cin >> q;
	for (int i = 1; i <= q; i++) {
		int id, x, value;
		std::cin >> id >> x;
		if (id == 1) {
			std::cin >> value;
			add(o[x].first, o[x].second, value % m);
		} else {
			auto tmp = query(o[x].first, o[x].second);
			std::cout << (tmp & prime).count() << std::endl;
		}
	}
	return 0;
}
