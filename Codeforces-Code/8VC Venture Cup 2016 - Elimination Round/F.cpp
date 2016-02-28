#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int MAXN = 201;
const int MAXK = 3001;
const int MOD = 1000000007;

int n, k, a[MAXN], dp[20][MAXN][MAXK];

void update(int &x, int y) {
	x += y;
	if (x >= MOD) x -= MOD;
}

int main() {
	std::cin >> n >> k;
	for (int i = 1; i <= n; i++) {
		std::cin >> a[i];
	}
	std::sort(a + 1, a + n + 1);
	dp[0][0][0] = 1;
	for (int i = 0; i < n; i++) {
		int delta = a[i + 1] - a[i];
		memset(dp[i & 1 ^ 1], 0, sizeof(dp[i & 1 ^ 1]));
		for (int j = 0; j <= n; j++)
			for (int l = 0; l <= k; l++) {
				//printf("Dp[%d, %d, %d] = %d\n", i, j, l, dp[i & 1][j][l]);
				if (!dp[i & 1][j][l]) continue;
				if (l + j * delta > k) continue;
				update(dp[i & 1 ^ 1][j + 1][l + j * delta], dp[i & 1][j][l]);
				if (j > 0) {
					update(dp[i & 1 ^ 1][j - 1][l + j * delta], 1ll * dp[i & 1][j][l] * j % MOD);
				}
				update(dp[i & 1 ^ 1][j][l + j * delta], 1ll * dp[i & 1][j][l] * j % MOD);
				update(dp[i & 1 ^ 1][j][l + j * delta], dp[i & 1][j][l]);
			}
	}
	int answer = 0;
	for (int i = 0; i <= k; i++)
		update(answer, dp[n & 1][0][i]);
	std::cout << answer << std::endl;
	return 0;
}
