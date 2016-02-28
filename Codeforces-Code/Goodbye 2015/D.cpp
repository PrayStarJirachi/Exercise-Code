#include <cstdio>
#include <iostream>
#include <algorithm>

const int MAXN = 5555;
const int mod = 1000000007;

int n, dp[MAXN][MAXN], g[MAXN][MAXN], s[MAXN][MAXN];
char d[MAXN];

int update(int &x, int y) {
	x += y;
	if (x >= mod) x -= mod;
}

int main() {
	std::cin >> n;
	std::cin >> d + 1;
	for (int i = n; i >= 1; i--)
		for (int j = i + 1; j <= n; j++) {
			if (d[i] == d[j]) g[i][j] = g[i + 1][j + 1] + 1;
			else g[i][j] = 0;
		}
	for (int i = n; i >= 1; i--) {
		if (d[i] != '0') {
			s[i][n + 1] = 1;
			dp[i][n + 1] = 1;
		}
	}
	d[n + 1] = '9' + 1;
	for (int i = n; i >= 1; i--) {
		for (int j = i + 1; j <= n; j++) {
			if (d[i] == '0' || d[j] == '0') continue;
			int len = std::min(g[i][j], j - i) + 1;
			if (d[i + len - 1] < d[j + len - 1] && j + std::max(len, (j - i)) <= n + 1) {
				update(dp[i][j], s[j][j + std::max(len, (j - i))]);
			}
			else if (j + std::max(len, (j - i) + 1) <= n + 1) {
				update(dp[i][j], s[j][j + std::max(len, (j - i) + 1)]);
			}
		}
		for (int j = n + 1; j > i; j--) {
			s[i][j] = (s[i][j + 1] + dp[i][j]) % mod;
		}
	}
	int answer = 0;
	for (int i = 2; i <= n + 1; i++)
		update(answer, dp[1][i]);
	std::cout << answer << std::endl;
	return 0;
}
