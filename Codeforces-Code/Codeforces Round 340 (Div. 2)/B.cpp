#include <cstdio>
#include <numeric>
#include <iostream>
#include <algorithm>

const double EPS = 1e-7;
const double PI = 3.1415926535897932384626;
const int MAXN = 201;

int n, a[MAXN];
long long dp[MAXN];

int main() {
	// freopen("input.txt", "r", stdin);
	dp[0] = 1;
	std::cin >> n;
	for (int i = 1; i <= n; i++) {
		std::cin >> a[i];
		a[i] += a[i - 1];
	}
	for (int i = 1; i <= n; i++)
		for (int j = 0; j <= i; j++)
			if (a[i] - a[j] == 1) {
				dp[i] += dp[j];
			}
	std::cout << dp[n] << std::endl;
	return 0;
}
