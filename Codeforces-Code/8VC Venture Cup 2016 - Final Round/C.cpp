#include <bits/stdc++.h>

long long s, x, d, dp[51ll][2];

int main() {
	std::cin >> s >> x;
	if ((s - x) % 2 == 1ll || s < x) return puts("0"), 0;
	d = s - x >> 1ll;
	if ((d & (~x)) != d) return puts("0"), 0;
	dp[40][1] = 1;
	for (int i = 41; i > 0; i--) {
		for (int j = 0; j < 2; j++) {
			if (!dp[i][j]) continue;
			int now = (d >> i - 1ll) & 1ll, limit = (s >> i - 1ll) & 1ll;
			for (int k = now; k < 2; k++) {
				if (j && (k > limit)) continue;
				if (now == 0 && (k && ((~x >> i - 1ll) & 1ll))) continue;
				dp[i - 1][j && (k == limit)] += dp[i][j];
			}
		}
	}
	
	std::cout << dp[0][0] - (x == s) << std::endl;
	return 0;
}
