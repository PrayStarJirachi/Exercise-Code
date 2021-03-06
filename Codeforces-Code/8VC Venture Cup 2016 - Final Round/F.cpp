#include <bits/stdc++.h>

const int MAXN = 210001;
const int MAXM = 400001;

struct Edge{
	int node, next;
}e[MAXM];

int n, k, t, h[MAXN], a[MAXN], d[MAXN], dp[MAXN], f[MAXN], s[MAXN], dmax[MAXN][2], dsum[MAXN], v[MAXN];

void addEdge(int x, int y) {
	t++; e[t] = (Edge){y, h[x]}; h[x] = t;
	t++; e[t] = (Edge){x, h[y]}; h[y] = t;
}

void predfs(int x) {
	s[x] = 1;
	dsum[x] = 0;
	dmax[x][0] = dmax[x][1] = 0;
	dp[x] = 0;
	for (int i = h[x]; i; i = e[i].next) {
		if (e[i].node == f[x]) continue;
		f[e[i].node] = x;
		predfs(e[i].node);
		if (dp[e[i].node] == s[e[i].node]) {
			dsum[x] += dp[e[i].node];
		} else {
			if (dp[e[i].node] > dmax[x][0]) {
				dmax[x][1] = dmax[x][0];
				dmax[x][0] = dp[e[i].node];
			} else if (dp[e[i].node] > dmax[x][1]) {
				dmax[x][1] = dp[e[i].node];
			}
		}
		s[x] += s[e[i].node];
	}
	if (v[x] == 1) {
		dp[x] = dsum[x] + dmax[x][0] + 1;
	} else {
		dsum[x] = 0;
		dmax[x][0] = dmax[x][1] = 0;
	}
}

void dfs(int x, int &answer) {
	for (int i = h[x]; i; i = e[i].next) {
		if (e[i].node == f[x]) continue;
		int tmp = dp[x], value = dp[e[i].node];
		if (v[x] == 1) {
			if (s[e[i].node] == dp[e[i].node]) {
				tmp -= dp[e[i].node];
			} else if (dp[e[i].node] == dmax[x][0]) {
				tmp -= dp[e[i].node];
				tmp += dmax[x][1];
			}
		}
		int oldMax[2], oldSum = 0, oldDp = 0;
		oldMax[0] = dmax[e[i].node][0];
		oldMax[1] = dmax[e[i].node][1];
		oldSum = dsum[e[i].node];
		oldDp = dp[e[i].node];
		if (v[e[i].node] == 1) {
			if (tmp == n - s[e[i].node]) {
				dsum[e[i].node] += tmp;
			} else {
				if (tmp > dmax[e[i].node][0]) {
					dmax[e[i].node][1] = dmax[e[i].node][0];
					dmax[e[i].node][0] = tmp;
				} else if (tmp > dmax[e[i].node][1]) {
					dmax[e[i].node][1] = tmp;
				}
			}
			dp[e[i].node] = dsum[e[i].node] + dmax[e[i].node][0] + 1;
		}
		answer = std::max(answer, dp[e[i].node]);
		dfs(e[i].node, answer);
		dmax[e[i].node][0] = oldMax[0];
		dmax[e[i].node][1] = oldMax[1];
		dsum[e[i].node] = oldSum;
		dp[e[i].node] = oldDp;
	}
}

bool check(const int &answer) {
	for (int i = 1; i <= n; i++) {
		v[i] = (a[i] >= answer);
	}
	predfs(1);
	int counter = dp[1];
	dfs(1, counter);
	return counter >= k;
}

int main() {
	freopen("D.in", "r", stdin);
	std::cin >> n >> k;
	for (int i = 1; i <= n; i++) {
		std::cin >> a[i];
		d[i] = a[i];
	}
	for (int i = 1; i < n; i++) {
		int x, y;
		std::cin >> x >> y;
		addEdge(x, y);
	}
	std::sort(d + 1, d + n + 1);
	int tot = std::unique(d + 1, d + n + 1) - d - 1;
	int left = 1, right = tot;
	while (left < right) {
		int middle = (left + right >> 1) + 1;
		if (check(d[middle])) {
			left = middle;
		} else {
			right = middle - 1;
		}
	}
	std::cout << d[left] << std::endl;
	return 0;
}
