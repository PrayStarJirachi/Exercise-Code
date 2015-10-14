#include <cstdio>
#include <iostream>
#include <algorithm>

int a, b, c, l;

long long solve(int a, int b, int c, int r) {
	int bound = std::min(a - b - c, r);
	if (bound < 0) return 0;
	return (long long)(bound + 1) * (bound + 2) >> 1;
}

int main() {
	freopen("input.txt", "r", stdin);
	std::cin >> a >> b >> c >> l;
	long long answer = (long long)(l + 3) * (l + 2) * (l + 1) / 6;
	for (int i = 0; i <= l; i++) {
		answer -= solve(a + i, b, c, l - i);
		answer -= solve(b + i, c, a, l - i);
		answer -= solve(c + i, a, b, l - i);
	}
	std::cout << answer << std::endl;
	return 0;
}
