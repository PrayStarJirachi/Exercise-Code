#include <bits/stdc++.h>

const int MAXN = 111111;

int n;
long long dp[MAXN][4], w[MAXN];
std::vector<int> g[MAXN];
bool v[MAXN][4];

long long dfs(int x, int fa, int k) {
	if (v[x][k]) return dp[x][k];
	v[x][k] = true;
	dp[x][k] = 0;
	for (auto son : g[x]) {
		if (son == fa) continue;
		for (int i = 0; i < 4; i++)
			dfs(son, x, i);
	}
	if (k == 0) { // 一个头
		dp[x][k] = w[x];
		for (auto son : g[x]) {
			if (son == fa) continue;
			dp[x][k] = std::max(dp[x][k], dp[son][0] + w[x]);
		}
	}
	if (k == 1) { // 一条链
		long long dmax = 0, dpos = 0;
		for (auto son : g[x]) {
			if (son == fa) continue;
			dp[x][k] = std::max(dp[x][k], dp[son][1]);
			if (dpos != 0) {
				dp[x][k] = std::max(dp[x][k], dmax + dp[son][0] + w[x]);
			}
			if (dmax < dp[son][0]) {
				dmax = dp[son][0];
				dpos = son;
			}
		}
	}
	if (k == 2) { // 一条链 + 一个头
		long long dmax = 0, cmax = 0, dpos = 0, cpos = 0;
		for (auto son : g[x]) {
			if (son == fa) continue;
			dp[x][k] = std::max(dp[x][k], dp[son][2] + w[x]);
			if (dp[son][0] > dmax) {
				assert(cmax <= dmax);
				cmax = dmax;
				cpos = dpos;
				dmax = dp[son][0];
				dpos = son;
			} else if (dp[son][0] > cmax) {
				cmax = dp[son][0];
				cpos = son;
			}
		}
		for (auto son : g[x]) {
			if (son == fa) continue;
			if (son == dpos) {
				dp[x][k] = std::max(dp[x][k], dp[son][1] + w[x] + cmax);
			} else {
				dp[x][k] = std::max(dp[x][k], dp[son][1] + w[x] + dmax);
			}
		}
	}
	if (k == 3) { // 两条链
		long long dmax = 0, cmax = 0, dpos = 0, cpos = 0, smax = 0, spos = 0;
		for (auto son : g[x]) {
			if (son == fa) continue;
			dp[x][k] = std::max(dp[x][k], dp[son][3]);
			if (dp[son][0] > dmax) {
				assert(smax <= cmax && cmax <= dmax);
				smax = cmax;
				spos = cpos;
				cmax = dmax;
				cpos = dpos;
				dmax = dp[son][0];
				dpos = son;
			} else if (dp[son][0] > cmax) {
				assert(smax <= cmax);
				smax = cmax;
				spos = cpos;
				cmax = dp[son][0];
				cpos = son;
			} else if (dp[son][0] > smax) {
				smax = dp[son][0];
				spos = son;
			}
		}
		for (auto son : g[x]) {
			if (son == fa) continue;
			if (son == dpos) {
				dp[x][k] = std::max(dp[x][k], dp[son][2] + w[x] + cmax);
			} else {
				dp[x][k] = std::max(dp[x][k], dp[son][2] + w[x] + dmax);
			}
		}
		for (auto son : g[x]) {
			if (son == fa) continue;
			if (son == dpos) {
				dp[x][k] = std::max(dp[x][k], dp[son][1] + w[x] + cmax + smax);
			} else if (son == cpos) {
				dp[x][k] = std::max(dp[x][k], dp[son][1] + w[x] + dmax + smax);
			} else {
				dp[x][k] = std::max(dp[x][k], dp[son][1] + w[x] + dmax + cmax);
			}
		}
		dmax = 0;
		dpos = 0;
		for (auto son : g[x]) {
			if (son == fa) continue;
			if (dpos != 0) {
				dp[x][k] = std::max(dp[x][k], dmax + dp[son][1]);
			}
			if (dp[son][1] > dmax) {
				dmax = dp[son][1];
				dpos = son;
			}
		}
	}
	if (k > 0) {
		dp[x][k] = std::max(dp[x][k], dfs(x, fa, k - 1));
	}
	return dp[x][k];
}

int main() {
	std::cin >> n;
	for (int i = 1; i <= n; i++) {
		std::cin >> w[i];
	}
	for (int i = 1; i < n; i++) {
		int x, y;
		std::cin >> x >> y;
		g[x].push_back(y);
		g[y].push_back(x);
	}
	std::cout << dfs(1, 0, 3) << std::endl;
	return 0;
}
