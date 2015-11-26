#include <cstdio>
#include <cstring>
#include <numeric>
#include <algorithm>

const int MAXN = 101;
const int MAXS = 100 * 10001;

int n, m, a[MAXN];
double dp[2][MAXS], q[MAXS];

int main() {
	freopen("C.in", "r", stdin);
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	dp[0][0] = m - 1;
	for (int i = 1; i <= n; i++) {
		q[0] = dp[i & 1 ^ 1][0];
		for (int j = 1; j <= i * m; j++) q[j] = q[j - 1] + dp[i & 1 ^ 1][j];
		for (int j = 0; j <= i * m; j++) {
			dp[i & 1][j] = q[j - 1];
			if (j - m - 1 >= 0) dp[i & 1][j] -= q[j - m - 1];
			if (j - a[i] >= 0) dp[i & 1][j] -= dp[i & 1 ^ 1][j - a[i]];
			if (m > 1) dp[i & 1][j] /= m - 1;
		}
	}
	double answer = 1.0;
	int tmp = std::accumulate(a + 1, a + n + 1, 0);
	for (int i = 0; i < tmp; i++) {
		answer += dp[n & 1][i];
	}
	printf("%.10f\n", answer);
	return 0;
}
