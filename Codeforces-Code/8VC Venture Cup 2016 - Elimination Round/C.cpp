#include <cstdio>
#include <iostream>
#include <algorithm>

int n, m;

int main() {
	std::cin >> n >> m;
	int left = 0, right = 6000000;
	while (left < right) {
		int middle = left + right >> 1;
		int a = middle / 2 - middle / 6;
		int b = middle / 3 - middle / 6;
		int c = middle / 6;
		c -= std::max(0, n - a);
		if (c >= 0 && b + c >= m) right = middle;
		else left = middle + 1;
	}
	std::cout << left << std::endl;
	return 0;
}
