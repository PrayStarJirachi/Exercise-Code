#include <cstdio>
#include <algorithm>

const int mod = 1000000007;
const int MAXN = 501;

int n, a[MAXN], dp[MAXN][MAXN];

void update(int &x, int y) {
	x += y;
	if (x >= mod) x -= mod;
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	for (int i = 1; i <= n; i++) {
		dp[i][i] = 1;
		if (i > 1) dp[i][i - 1] = 1;
	}
	for (int k = 2; k <= n; k++)
		for (int i = 1; i <= n - k + 1; i++) {
			int j = i + k - 1;
			update(dp[i][j], dp[i + 1][j]);
			for (int p = i + 1; p <= j; p++)
				if (a[i] < a[p]) {
					update(dp[i][j], (long long)dp[i + 1][p - 1] * dp[p][j] % mod);
				}
		}
	if (n == 1) return printf("1\n"), 0;
	printf("%d\n", dp[2][n]);
	return 0;
}
