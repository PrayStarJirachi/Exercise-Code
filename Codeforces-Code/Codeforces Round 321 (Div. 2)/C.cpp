#include <cstdio>
#include <algorithm>

const int MAXN = 200001;
const int MAXM = 400001;

struct Edge{
	int node, next;
}e[MAXM];

int n, m, t, a[MAXN], f[MAXN], h[MAXN], dp[MAXN], deg[MAXN];

void addedge(int x, int y) {
	t++; e[t] = (Edge){y, h[x]}; h[x] = t;
	t++; e[t] = (Edge){x, h[y]}; h[y] = t;
}

void buildtree(int x) {
	static int q[MAXN];
	static bool v[MAXN];
	int l = 0, r = 0;
	std::fill(v + 1, v + n + 1, false);
	q[++r] = x; dp[x] = a[x]; v[x] = true;
	while (l < r) {
		l++;
		for (int i = h[q[l]]; i; i = e[i].next) {
			if (v[e[i].node]) continue;
			f[q[++r] = e[i].node] = q[l];
			v[q[r]] = true;
			if (a[q[r]]) dp[q[r]] = dp[q[l]] + 1;
			else dp[q[r]] = 0;
		}
	}
	for (int i = 1; i <= n; i++)
		for (int j = h[q[i]]; j; j = e[j].next)
			dp[e[j].node] = std::max(dp[e[j].node], dp[q[i]]);
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d", a + i);
	}
	for (int i = 1; i < n; i++) {
		int x, y; scanf("%d%d", &x, &y);
		addedge(x, y); deg[x]++; deg[y]++;
	}
	buildtree(1);
	int answer = 0;
	for (int i = 2; i <= n; i++)
		if (deg[i] == 1 && dp[i] <= m) answer++;
	printf("%d\n", answer);
	return 0;
}
