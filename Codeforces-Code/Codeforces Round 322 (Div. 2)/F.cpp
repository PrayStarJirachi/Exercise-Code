#include <cstdio>

const int MAXN = 5001;
const int MAXM = 10001;
const int INF = ~0u >> 2;

struct Edge{
	int node, next;
}e[MAXM];

int n, t, counter, s[MAXN], h[MAXN], deg[MAXN], fa[MAXN], dp[MAXN][MAXN][2], tmp[MAXN][2];

void addedge(int x, int y) {
	t++; e[t] = (Edge){y, h[x]}; h[x] = t;
	t++; e[t] = (Edge){x, h[y]}; h[y] = t;
}

void update(int &x, int y) {
	if (x > y) x = y;
}

void dfs(int x) {
	if (deg[x] == 1) {
		s[x]++;
		dp[x][1][0] = 0;
		dp[x][0][1] = 0;
		return;
	}
	for (int i = h[x]; i; i = e[i].next) {
		if (e[i].node == fa[x]) continue;
		fa[e[i].node] = x;
		dfs(e[i].node);
		s[x] += s[e[i].node];
	}
	bool fir = true;
	for (int p = h[x]; p; p = e[p].next) {
		if (e[p].node == fa[x]) continue;
		int son = e[p].node;
		if (fir) {
			for (int i = 0; i < 2; i++) {
				for (int k = 0; k <= s[son]; k++) {
					dp[x][k][i] = INF;
					for (int l = 0; l < 2; l++) {
						update(dp[x][k][i], dp[son][k][l] + (i ^ l));
					}
				}
			}
			fir = false;
			continue;
		}
		for (int i = 0; i <= s[x]; i++) {
			tmp[i][0] = dp[x][i][0];
			tmp[i][1] = dp[x][i][1];
		}
		for (int i = 0; i < 2; i++)
			for (int j = 0; j <= s[x]; j++) {
				dp[x][j][i] = INF;
				for (int k = 0; k <= s[son] && k <= j; k++) {
					for (int l = 0; l < 2; l++) {
						update(dp[x][j][i], tmp[j - k][i] + dp[son][k][l] + (i ^ l));
					}
				}
			}
	}
}

int main() {
	freopen("F.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i < n; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		addedge(x, y);
		deg[x]++; deg[y]++;
	}
	if (n == 2) {
		printf("1\n");
		return 0;
	}
	for (int i = 1; i <= n; i++) {
		if (deg[i] == 1) {
			counter++;
		}
	}
	for (int i = 1; i <= n; i++)
		for (int j = 0; j <= n; j++)
			dp[i][j][0] = dp[i][j][1] = INF;
	for (int i = 1; i <= n; i++) {
		if (deg[i] > 1) {
			dfs(i);
			int answer = INF;
			update(answer, dp[i][s[i] >> 1][0]);
			update(answer, dp[i][s[i] >> 1][1]);
			printf("%d\n", answer);
			return 0;
		}
	}
	return 0;
}
