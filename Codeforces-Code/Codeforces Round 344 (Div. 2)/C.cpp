#include <bits/stdc++.h>

const int MAXN = 200001;

int n, m, tot, a[MAXN], c[MAXN], answer[MAXN];
std::set<std::pair<int, int> > set;
std::pair<int, int> b[MAXN];

struct Range{
	int op, r, t;
}o[MAXN], s[MAXN];

void add(int x) {
	for (int i = x; i <= n; i += i & -i) {
		c[i]++;
	}
}

int sum(int x) {
	int ret = 0;
	for (int i = x; i; i -= i & -i) {
		ret += c[i];
	}
	return ret;
}

bool cmp(const std::pair<int, int> &x, const std::pair<int, int> &y) {
	return x.second < y.second;
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	for (int i = 1; i <= m; i++) {
		scanf("%d%d", &o[i].op, &o[i].r);
		o[i].t = i;
	}
	for (int i = m; i >= 1; i--) {
		add(n - o[i].r + 1);
		if (sum(n - o[i].r) == 0) {
			s[++tot] = o[i];
		}
	}
	std::reverse(s + 1, s + tot + 1);
	s[0].r = n;
	s[0].t = 0;
	for (int i = n; i > s[1].r; i--) {
		answer[i] = a[i];
	}
	for (int i = s[1].r; i >= 1; i--) {
		set.insert(std::make_pair(a[i], i));
	}
	for (int i = 2, tmp = n; i <= tot; i++) {
		int length = s[i - 1].r - s[i].r, t = 0;
		for (int j = 1; j <= length; j++)
			if (s[i - 1].op == 1) {
				auto it = --set.end();
				b[++t] = *it;
				set.erase(it);
			} else if (s[i - 1].op == 2) {
				auto it = set.begin();
				b[++t] = *it;
				set.erase(it);
			}
		for (int j = s[i - 1].r, z = 0; j > s[i].r; j--) {
			answer[j] = b[++z].first;
		}
	}
	if (s[tot].op == 1) {
		int p = 0;
		for (auto it = set.begin(); it != set.end(); it++) {
			answer[++p] = it -> first;
		}
	} else {
		int p = 0;
		for (auto it = set.rbegin(); it != set.rend(); it++) {
			answer[++p] = it -> first;
		}
	}
	for (int i = 1; i <= n; i++) {
		printf("%d%c", answer[i], " \n"[i == n]);
	}
	return 0;
}
