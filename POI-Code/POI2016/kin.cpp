#include <cstdio>
#include <iostream>
#include <algorithm>

const int MAXN = 1100001;
const long long INF = 1ll << 50;
int n, m, M, a[MAXN], p[MAXN], hash[MAXN], w[MAXN];
long long value[MAXN], tree[MAXN * 6], tag[MAXN * 6];

void buildtree(int n, int l, int r) {
	if (l == r) {
		tree[n] = value[l];
		return;
	}
	buildtree(n << 1, l, l + r >> 1);
	buildtree(n << 1 ^ 1, (l + r >> 1) + 1, r);
	tree[n] = std::max(tree[n << 1], tree[n << 1 ^ 1]);
}

void makedelta(int n, long long d) {
	tree[n] += d;
	tag[n] += d;
}

void pushdown(int n) {
	if (tag[n]) {
		makedelta(n << 1, tag[n]);
		makedelta(n << 1 ^ 1, tag[n]);
		tag[n] = 0;
	}
}

void modify(int n, int l, int r, int x, int y, int d) {
	if (r < x || l > y) return;
	if (x <= l && r <= y) {
		makedelta(n, d);
		return;
	}
	pushdown(n);
	modify(n << 1, l, l + r >> 1, x, y, d);
	modify(n << 1 ^ 1, (l + r >> 1) + 1, r, x, y, d);
	tree[n] = std::max(tree[n << 1], tree[n << 1 ^ 1]);
}

long long query(int n, int l, int r, int x, int y) {
	if (r < x || l > y) return -INF;
	if (x <= l && r <= y) return tree[n];
	pushdown(n);
	long long left = query(n << 1, l, l + r >> 1, x, y);
	long long right = query(n << 1 ^ 1, (l + r >> 1) + 1, r, x, y);
	return std::max(left, right);
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d", a + i);
	}
	for (int i = 1; i <= m; i++) {
		scanf("%d", w + i);
	}
	for (int i = 1; i <= n; i++) {
		p[i] = hash[a[i]];
		hash[a[i]] = i;
	}
	std::fill(hash + 1, hash + m + 1, 0);
	for (int i = n; i >= 1; i--) {
		value[i] = value[i + 1];
		if (hash[a[i]] == 0) value[i] += w[a[i]];
		else if (hash[a[i]] == 1) value[i] -= w[a[i]];
		hash[a[i]]++;
	}
	buildtree(1, 1, n);
	long long answer = -INF;
	for (int i = n; i >= 1; i--) {
		answer = std::max(answer, query(1, 1, n, 1, i));
		modify(1, 1, n, p[i] + 1, i - 1, -w[a[i]]);
		modify(1, 1, n, p[p[i]] + 1, p[i], w[a[i]]);
	}
	std::cout << answer << std::endl;
	return 0;
}
