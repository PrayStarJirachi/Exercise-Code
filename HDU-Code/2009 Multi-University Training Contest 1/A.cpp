#include <cstdio>
#include <algorithm>

#ifdef WIN32
	#define LL "%I64d"
#else
	#define LL "%lld"
#endif

const int mod = 200907;

int T, n;
long long a, b, c;

long long fpm(long long a, long long b) {
	long long ret = 1;
	for (; b; b >>= 1) {
		if (b & 1) ret = ret * a % mod;
		a = a * a % mod;
	}
	return ret;
}

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf(LL LL LL "%d", &a, &b, &c, &n);
		if (b - a == c - b) {
			long long d = (b - a + mod) % mod;
			printf(LL "\n", (a + (long long)(n - 1) * d % mod) % mod);
		}
		else{
			long long q = (b / a) % mod;
			printf(LL "\n", (a % mod) * fpm(q, n - 1) % mod);
		}
	}
	return 0;
}
