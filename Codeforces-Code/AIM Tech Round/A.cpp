#include <cstdio>
#include <numeric>
#include <iostream>
#include <algorithm>

const double EPS = 1e-7;
const double PI = 3.1415926535897932384626;

double d, L, v1, v2;

int main() {
	// freopen("input.txt", "r", stdin);
	std::cin >> d >> L >> v1 >> v2;
	printf("%.10f\n", (L - d) / (v1 + v2));
	return 0;
}
