#include <bits/stdc++.h>

const int MAXN = 800001;
const int MAXM = 800001;
const int INF = ~0u >> 2;

int n, m, tot, h[MAXN], p[MAXN], d[MAXN];
std::pair<int, int> dp[MAXN][2], c[MAXN];

struct Query{
	int a, b, id, answer;
	bool operator <(const Query &rhs)const {
		return a < rhs.a;
	}
}q[MAXM];

bool cmp(const Query &a, const Query &b) {
	return a.id < b.id;
}

void add(int x, const std::pair<int, int> &d) {
	for (int i = x; i <= tot; i += i & -i) {
		c[i] = std::max(c[i], d);
	}
}

void addtwo(int x, int d) {
	for (int i = x; i <= n; i += i & -i) {
		c[i].first += d;
	}
}

int sumtwo(int x) {
	int ret = 0;
	for (int i = x; i; i -= i & -i) {
		ret += c[i].first;
	}
	return ret;
}

std::pair<int, int> sum(int x) {
	std::pair<int, int> ret = std::make_pair(0, 0);
	for (int i = x; i; i -= i & -i) {
		ret = std::max(ret, c[i]);
	}
	return ret;
}

int main() {
	std::cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		scanf("%d", h + i);
		d[++tot] = h[i];
	}
	for (int i = 1; i <= m; i++) {
		scanf("%d%d", &q[i].a, &q[i].b);
		q[i].id = i;
		d[++tot] = q[i].b;
	}
	std::sort(d + 1, d + tot + 1);
	tot = std::unique(d + 1, d + tot + 1) - d - 1;
	for (int i = 1; i <= n; i++) {
		h[i] = std::lower_bound(d + 1, d + tot + 1, h[i]) - d;		
	}
	int maxlen = 0;
	for (int i = 1; i <= n; i++) {
		dp[i][0] = sum(h[i] - 1);
		dp[i][0].first++;
		if (i <= n) add(h[i], std::make_pair(dp[i][0].first, -i));
		maxlen = std::max(maxlen, dp[i][0].first);
	}
	dp[n + 1][0] = sum(tot);
	dp[n + 1][0].first++;
	std::fill(c + 1, c + tot + 1, std::make_pair(0, 0));
	for (int i = n; i >= 1; i--) {
		dp[i][1] = sum(tot - h[i]);
		dp[i][1].first++;
		add(tot - h[i] + 1, std::make_pair(dp[i][1].first, 0));
	}
	std::sort(q + 1, q + m + 1);
	std::fill(c + 1, c + tot + 1, std::make_pair(0, 0));
	for (int i = 1; i <= m; i++) {
		q[i].b = std::lower_bound(d + 1, d + tot + 1, q[i].b) - d;
	}
	for (int i = 1, z = 1; i <= m; i++) {
		while (z < q[i].a) {
			add(h[z], std::make_pair(dp[z][0].first, 0));
			z++;
		}
		q[i].answer = sum(q[i].b - 1).first + 1;
	}
	std::fill(c + 1, c + tot + 1, std::make_pair(0, 0));
	for (int i = m, z = n; i >= 1; i--) {
		while (z > q[i].a) {
			add(tot - h[z] + 1, std::make_pair(dp[z][1].first, 0));
			z--;
		}
		q[i].answer += sum(tot - q[i].b).first;
	}
	std::fill(c + 1, c + tot + 1, std::make_pair(0, 0));
	for (int i = m, z = n + 1, zero = 0; i >= 1; i--) {
		while (z > q[i].a) {
			if (dp[z][1].first + dp[z][0].first == maxlen + 1) {
				if (dp[z][0].second == 0) zero++;
				else addtwo(-dp[z][0].second, 1);
			}
			z--;
		}
		int pos = sumtwo(q[i].a - 1) + zero;
		if (pos != 0) {
			q[i].answer = std::max(q[i].answer, maxlen);
		} else {
			q[i].answer = std::max(q[i].answer, maxlen - 1);
		}
	}
	std::sort(q + 1, q + m + 1, cmp);
	for (int i = 1; i <= m; i++) {
		printf("%d\n", q[i].answer);	
	}
	return 0;
}
