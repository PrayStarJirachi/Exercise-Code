#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>

const int MAXN = 222222;

int n, a[MAXN];

int main() {
	freopen("B.in", "r", stdin);
	scanf("%d", &n);
	long long answer = 0;
	for (int i = 1; i <= n; i++) {
		scanf("%d", a + i);
		answer += std::abs(a[i] - a[i - 1]);
	}
	std::cout << answer << std::endl;
	return 0;
}
