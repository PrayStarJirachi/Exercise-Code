#include <cstdio>
#include <iostream>
#include <algorithm>

const int MAXK = 5001;
const int MAXN = 300001;
const long long INF = 1ll << 50;

int n, k, a[MAXN];
long long dp[MAXK][MAXK];

void update(long long &x, const long long &y) {
	if (x > y) x = y;
}

int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	std::sort(a + 1, a + n + 1);
	int cntSmall = k - n % k;
	int cntLarge = n % k;
	int sizeSmall = n / k;
	int sizeLarge = n / k + 1;
	for (int i = 0; i <= cntSmall; i++)
		for (int j = 0; j <= cntLarge; j++)
			dp[i][j] = INF;
	dp[0][0] = 0;
	for (int i = 0; i <= cntSmall; i++)
		for (int j = 0; j <= cntLarge; j++) {
			if (i < cntSmall) {
				int l = i * sizeSmall + j * sizeLarge + 1;
				int r = l + sizeSmall - 1;
				update(dp[i + 1][j], dp[i][j] + a[r] - a[l]);
			}
			if (j < cntLarge) {
				int l = i * sizeSmall + j * sizeLarge + 1;
				int r = l + sizeLarge - 1;
				update(dp[i][j + 1], dp[i][j] + a[r] - a[l]);
			}
		}
	std::cout << dp[cntSmall][cntLarge] << std::endl;
	return 0;
}
