#include <cstdio>
#include <algorithm>

#ifdef WIN32
	#define LL "%I64d"
#else
	#define LL "%lld"
#endif

const char s[] = "AB";

long long x, y;

long long gcd(long long a, long long b) {
	return b ? gcd(b, a % b) : a;
}

void gcd(long long x, long long y, char a, char b) {
	while (!(x == 1 && y == 1)) {
		if (x < y) {
			std::swap(x, y);
			std::swap(a, b);
		}
		printf(LL "%c", (x - 1) / y, a);
		long long ox = x, oy = y;
		x = ox - (ox - 1) / oy * oy;
		y = oy;
	}
}

int main() {
	scanf(LL LL, &x, &y);
	if (gcd(x, y) != 1ll) return puts("Impossible"), 0;
	else{
		gcd(x, y, 'A', 'B');
		puts("");
	}
	return 0;
}

