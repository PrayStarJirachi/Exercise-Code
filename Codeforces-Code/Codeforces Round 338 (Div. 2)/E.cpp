#include <cstdio>
#include <numeric>
#include <iostream>
#include <algorithm>

const double EPS = 1e-7;
const double PI = 3.1415926535897932384626;

const int DX[] = {-1, -2, -1,  1,  2,  1};
const int DY[] = { 2,  0, -2, -2,  0,  2};

long long n;

long long getStep(long long round) {
	long long ret = 0;
	ret = ((round + 1) * round >> 1) * 6;
	return ret;
}

long long getRound(long long n) {
	long long left = 0, right = 1ll << 30;
	while (left < right) {
		long long middle = left + right >> 1;
		if (getStep(middle) >= n) right = middle;
		else left = middle + 1;
	}
	return left;
}

int main() {
	// freopen("input.txt", "r", stdin);
	std::cin >> n;
	if (n == 0) return puts("0 0"), 0;
	long long round = getRound(n);
	n -= getStep(round - 1) + 1;
	long long sx = 1 + (round - 1) * 2, sy = 2;
	if (n <= round - 1) {
		std::cout << sx - n << " " << sy + 2 * n << std::endl;
	} else {
		sx -= (round - 1);
		sy += 2 * (round - 1);
		n -= round - 1;
		int dir = 1;
		while (n != 0) {
			int tmp = std::min(round, n);
			sx += DX[dir] * tmp;
			sy += DY[dir] * tmp;
			n -= tmp;
			dir++;
		}
		std::cout << sx << " " << sy << std::endl;
	}
	return 0;
}
