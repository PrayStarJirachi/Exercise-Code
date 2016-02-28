#include <bits/stdc++.h>

int a, b, c;

int main() {
	// freopen("input.txt", "r", stdin);
	std::cin >> a >> b >> c;
	for (int i = 0; i <= 10000; i++) {
		int r = c - i * a;
		if (r < 0) break;
		if (r % b == 0) {
			return puts("Yes"), 0;
		}
	}
	puts("No");
	return 0;
}
