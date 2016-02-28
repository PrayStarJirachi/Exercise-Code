#include <cstdio>
#include <numeric>
#include <iostream>
#include <algorithm>

const double EPS = 1e-7;
const double PI = 3.1415926535897932384626;

int n;
long long a[27];

int main() {
	// freopen("input.txt", "r", stdin);
	std::cin >> n;
	long long answer = 0;
	for (int i = 1; i <= n; i++) {
		std::cin >> a[i];
		answer += a[i];
	}
	while (true) {
		bool flag = false;
		std::sort(a + 1, a + n + 1);
		for (int i = n; i > 1; i--) {
			if (a[i] == 0) break;
			if (a[i] == a[i - 1]) {
				a[i - 1]--;
				answer--;
				flag = true;
				break;
			}
		}
		if (!flag) break;
	}
	std::cout << answer << std::endl;
	return 0;
}
