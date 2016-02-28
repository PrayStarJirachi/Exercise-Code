#include <cstdio>
#include <iostream>
#include <algorithm>

const int MAXN = 111111;
const int MAXM = 222222;

struct Edge{
	int node, next;
}e[MAXM];

int n, m, t, h[MAXN], dp[MAXN], deg[MAXN];

void addEdge(int x, int y) {
	t++; e[t] = (Edge){y, h[x]}; h[x] = t;
}

int dfs(int x) {
	if (dp[x]) return dp[x];
	for (int i = h[x]; i; i = e[i].next)
		dp[x] = std::max(dp[x], dfs(e[i].node));
	return ++dp[x];
}

int main() {
	// freopen("input.txt", "r", stdin);
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		if (x < y) std::swap(x, y);
		addEdge(x, y);
		deg[x]++;
		deg[y]++;
	}
	long long answer = 0;
	for (int i = 1; i <= n; i++)
		answer = std::max(answer, 1ll * dfs(i) * deg[i]);
	std::cout << answer << std::endl;
	return 0;
}
