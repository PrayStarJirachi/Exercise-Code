#include <cstdio>
#include <vector>
#include <algorithm>

const int MAXN = 200001;
const int mod = 1000000007;

int n, t, h[MAXN], dp[MAXN], answer[MAXN];
std::vector<int> pred[MAXN], succ[MAXN], whe[MAXN];

void predfs(int x, int fa) {
	dp[x] = 1;
	for (int i = 0; i < (int)whe[x].size(); i++) {
		if (whe[x][i] == fa) continue;
		predfs(whe[x][i], x);
		dp[x] = (long long)dp[x] * (dp[whe[x][i]] + 1) % mod;
	}
}

void dfs(int x, int fa) {
	pred[x].resize((int)whe[x].size() + 1);
	succ[x].resize((int)whe[x].size() + 1);
	pred[x][0] = 1;
	for (int i = 0; i < (int)whe[x].size(); i++) {
		int now = whe[x][i];
		pred[x][i + 1] = (long long)pred[x][i] * (dp[now] + 1) % mod;
	}
	succ[x][(int)whe[x].size()] = 1;
	for (int i = (int)whe[x].size() - 1; i >= 0; i--) {
		int now = whe[x][i];
		succ[x][i] = (long long)succ[x][i + 1] * (dp[now] + 1) % mod;
	}
	answer[x] = dp[x];
	for (int i = 0; i < (int)whe[x].size(); i++) {
		if (whe[x][i] == fa) continue;
		int tmp = dp[whe[x][i]];
		dp[x] = (long long)pred[x][i] * succ[x][i + 1] % mod;
		dp[whe[x][i]] = (long long)dp[whe[x][i]] * (dp[x] + 1) % mod;
		dfs(whe[x][i], x);
		dp[x] = answer[x];
		dp[whe[x][i]] = tmp;
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d", &n);
	for (int i = 2; i <= n; i++) {
		int fa; scanf("%d", &fa);
		whe[fa].push_back(i);
		whe[i].push_back(fa);
	}
	predfs(1, 0);
	dfs(1, 0);
	for (int i = 1; i <= n; i++)
		printf("%d%c", answer[i], " \n"[i == n]);
	return 0;
}
