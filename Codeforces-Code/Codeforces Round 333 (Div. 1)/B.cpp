#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>

const int MAXN = 111111;
const int INF = ~0u >> 2;

int n, q, tot, h[MAXN], d[MAXN], a[MAXN], bit[MAXN], l[MAXN], r[MAXN];

void add(int x, int d) {
	for (int i = x; i <= tot; i += i & -i) {
		bit[i] = std::max(bit[i], d);
	}
}

int query(int x, int zero) {
	int ret = zero;
	for (int i = x; i; i -= i & -i) {
		ret = std::max(ret, bit[i]);
	}
	return ret;
}

int main() {
	scanf("%d%d", &n, &q);
	for (int i = 1; i <= n; i++) scanf("%d", h + i); n--;
	for (int i = 1; i <= n; i++) {
		d[i] = a[i] = std::abs(h[i + 1] - h[i]);
	}
	std::sort(d + 1, d + n + 1);
	tot = std::unique(d + 1, d + n + 1) - d - 1;
	std::fill(bit + 1, bit + tot + 1, 0);
	for (int i = 1; i <= n; i++) a[i] = std::lower_bound(d + 1, d + tot + 1, a[i]) - d;
	for (int i = 1; i <= n; i++) {
		l[i] = query(tot - (a[i] + 1) + 1, 0);
		add(tot - a[i] + 1, i);
	}
	std::fill(bit + 1, bit + tot + 1, -(n + 1));
	for (int i = n; i >= 1; i--) {
		r[i] = -query(tot - a[i] + 1, -(n + 1));
		add(tot - a[i] + 1, -i);
	}
	for (int i = 1; i <= q; i++) {
		int left, right;
		long long answer = 0;
		scanf("%d%d", &left, &right);
		right--;
		for (int p = left; p <= right; p++) {
			int nowL = std::max(left - 1, l[p]);
			int nowR = std::min(right + 1, r[p]);
			answer += 1ll * (p - nowL) * (nowR - p) * d[a[p]];
		}
		std::cout << answer << std::endl;
	}
	return 0;
}
