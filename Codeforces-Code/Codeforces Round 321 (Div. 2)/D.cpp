#include <cstdio>
#include <algorithm>

const int MAXN = 21;
const int MAXS = 300001;
const int INF = ~0u >> 2;

int n, m, k, a[MAXN][MAXN], c[MAXN], cnt[MAXS];
long long dp[MAXS][MAXN];

void update(long long &x, long long y) {
	if (x < y) x = y;
}

int main() {
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 0; i < (1 << n); i++) {
		for (int j = 1; j <= n; j++) {
			dp[i][j] = -INF;
			if (i & (1 << j - 1)) cnt[i]++;
		}
	}
	for (int i = 1; i <= n; i++) {
		scanf("%d", c + i);
		dp[1 << i - 1][i] = c[i];
	}
	for (int i = 1; i <= k; i++) {
		int x, y, c; scanf("%d%d%d", &x, &y, &c);
		a[x][y] = std::max(a[x][y], c);
	}
	long long answer = 0;
	for (int i = 1; i < (1 << n); i++) {
		if (cnt[i] > m) continue;
		for (int j = 1; j <= n; j++) {
			if (i & (1 << j - 1)) {
				for (int k = 1; k <= n; k++) {
					if (i & (1 << k - 1)) continue;
					update(dp[i | (1 << k - 1)][k], dp[i][j] + a[j][k] + c[k]);
				}
			}
			if (cnt[i] == m) {
				answer = std::max(answer, dp[i][j]);
			}
		}
	}
	printf("%I64d\n", answer);
	return 0;
}
