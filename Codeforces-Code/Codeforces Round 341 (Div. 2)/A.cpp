#include <cstdio>
#include <numeric>
#include <iostream>
#include <algorithm>

const double EPS = 1e-7;
const double PI = 3.1415926535897932384626;
const int MAXN = 100001;

int n, a[MAXN];

int main() {
	// freopen("input.txt", "r", stdin);
	std::cin >> n;
	for (int i = 1; i <= n; i++) {
		std::cin >> a[i];
	}
	long long answer = 0;
	for (int i = 1; i <= n; i++) {
		answer += a[i];
	}
	std::sort(a + 1, a + n + 1);
	if (answer & 1) {
		for (int i = 1; i <= n; i++)
			if (a[i] & 1) {
				answer -= a[i];
				break;
			}
	}
	std::cout << answer << std::endl;
	return 0;
}
