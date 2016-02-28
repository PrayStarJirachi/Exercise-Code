#include <cstdio>
#include <iostream>
#include <algorithm>

long long l, r, k;

int main() {
	// freopen("input.txt", "r", stdin);
	std::cin >> l >> r >> k;
	bool flag = false;
	double tv = 1;
	for (long long q = 0, value = 1; q <= 1000; q++) {
		if (l <= value && value <= r) {
			std::cout << value << " ";
			flag = true;
		}
		value *= k;
		tv *= k;
		if (value > r || tv > r) break;
	}
	if (!flag) puts("-1");
	
	return 0;
}
