#include <cstdio>
#include <numeric>
#include <iostream>
#include <algorithm>

const double EPS = 1e-7;
const double PI = 3.1415926535897932384626;
const int MAXN = 10000001;

int n, dp[MAXN];

int main() {
	// freopen("input.txt", "r", stdin);
	std::cin >> n;
	for (int i = 1; i <= n; i++) {
		dp[i] = n + 1;
		for (int j = 1; j <= 5 &&  j <= i; j++)
			dp[i] = std::min(dp[i], dp[i - j] + 1);
	}
	std::cout << dp[n];
	return 0;
}
