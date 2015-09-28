#include <cstdio>
#include <algorithm>

const int mod = 1000000007;
const int MAXN = 100001;
const int Maxdata = 100000;

int T, g, fac[MAXN], ifac[MAXN], inv[MAXN], p[MAXN], mu[MAXN];
bool v[MAXN];

int fpm(int a, int b) {
	int ret = 1;
	for (; b; b >>= 1) {
		if (b & 1) ret = (long long)ret * a % mod;
		a = (long long)a * a % mod;
	}
	return ret;
}

int calc(int n, int m) {
	// C(n - 1, m - 1);
	if (n < m) return 0;
	int ret = 1;
	ret = (long long)ret * fac[n - 1] % mod;
	ret = (long long)ret * ifac[m - 1] % mod;
	ret = (long long)ret * ifac[n - m] % mod;
	return ret;
}

int solve(int n, int m) {
	// x1 + x2 + ... + xm = n
	int ans = 0;
	for (int d = 1; d * d <= n; d++) {
		if (n % d) continue;
		int tmp = (long long)mu[d] * calc(n / d, m) % mod;
		ans = ((ans + tmp) % mod + mod) % mod;
		if (d * d != n) {
			tmp = (long long)mu[n / d] * calc(d, m) % mod;
			ans = ((ans + tmp) % mod + mod) % mod;
		}
	}
	return ans;
}

int main() {
	scanf("%d", &T);
	fac[0] = ifac[0] = 1;
	for (int i = 1; i <= Maxdata; i++) {
		fac[i] = (long long)fac[i - 1] * i % mod;
		if (i > 1) {
			inv[i] = mod - (long long)(mod / i) * inv[mod % i] % mod;
		}
		else inv[i] = 1;
		ifac[i] = (long long)ifac[i - 1] * inv[i] % mod;
	}
	mu[1] = 1;
	for (int i = 2; i <= Maxdata; i++) {
		if (!v[i]) mu[p[++g] = i] = -1;
		for (int j = 1; j <= g && i * p[j] <= Maxdata; j++) {
			v[i * p[j]] = true;
			if (i % p[j] == 0) {mu[i * p[j]] = 0; break;}
			else mu[i * p[j]] = mu[i] * mu[p[j]];
		}
	}
	while (T--) {
		int n, f;
		scanf("%d%d", &n, &f);
		printf("%d\n", solve(n, f));
	}
	return 0;
}
