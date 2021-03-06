#include <cstdio>
#include <iostream>
#include <algorithm>

const int MAXN = 100001;
const int MOD = 1000000007;

int n, k, factor[MAXN], invfac[MAXN], inv[3][3];

int fpm(int a, int b, int p) {
	int ret = 1;
	for (; b; b >>= 1) {
		if (b & 1) ret = 1ll * ret * a % p;
		a = 1ll * a * a % p;
	}
	return ret;
}

long long exGcd(const long long &a, const long long &b, long long &x, long long &y) {
	if (b == 0) {
		x = 1;
		y = 0;
		return a;
	} else {
		long long ox, oy, og = exGcd(b, a % b, ox, oy);
		x = oy;
		y = ox - (a / b) * oy;
		return og;
	}
}
long long inverse(long long a, long long p) {//const int &a, const int &p) {
	long long x, y;
	exGcd(a, p, x, y);
	return (x % p + p) % p;
}

class FastFourierTransform{
private:
	const int PRT;
public:
	const int MOD;
	FastFourierTransform(const int &mod, const int &prt) : MOD(mod), PRT(prt) {}
	static int prepare(int n) {
		int len = 1;
		for (; len <= 2 * n; len <<= 1);
		return len;
	}
	void DFT(int *a, int n, int f)const {
		for (int i = 0, j = 0; i < n; i++) {
			if (i > j) std::swap(a[i], a[j]);
			for (int t = n >> 1; (j ^= t) < t; t >>= 1);
		}
		for (int i = 2; i <= n; i <<= 1) {
			int z = (f == 0) ? ((MOD - 1)) / i : ((MOD - 1) / i * (i - 1));
			int wm = fpm(PRT, z, MOD);
			for (int j = 0; j < n; j += i) {
				for (int k = 0, w = 1; k < (i >> 1); k++) {
					int A = a[j + k] % MOD;
					int B = 1ll * a[j + k + (i >> 1)] * w % MOD;
					a[j + k] = (A + B) % MOD;
					a[j + k + (i >> 1)] = (A - B + MOD) % MOD;
					w = 1ll * w * wm % MOD;
				}
			}
		}
		if (f == 1) {
			long long rev = fpm(n, MOD - 2, MOD);
			for (int i = 0; i < n; i++) {
				a[i] = (long long)a[i] * rev % MOD;
			}
		}
	}
}fft1(994705409, 3), fft2(993263617, 5), fft3(995622913, 5);

const FastFourierTransform *FFT[3] = {&fft1, &fft2, &fft3};

int CRT(int *a) {
	int x[3];
	for (int i = 0; i < 3; i ++)
	{
		x[i] = a[i];
		for (int j = 0; j < i; j ++)
		{
			int t = (x[i] - x[j] + FFT[i] -> MOD) % FFT[i] -> MOD;
			if (t < 0) t += FFT[i] -> MOD;
			x[i] = 1LL * t * inv[j][i] % FFT[i] -> MOD;
		}
	}
	int sum = 1, ret = x[0] % MOD;
	for (int i = 1; i < 3; i ++)
	{
		sum = 1LL * sum * FFT[i - 1] -> MOD % MOD;
		ret += 1LL * x[i] * sum % MOD;
		if(ret >= MOD) ret -= MOD;
	}
	return ret;
}

void getArray(int *first, int *second, int *result, const int &length, const int &right) {
	static int a[MAXN], b[MAXN], ret[3][MAXN];
	for (int h = 0; h < 3; h++) {
		std::fill(a, a + length, 0);
		std::fill(b, b + length, 0);
		for (int i = 0, z = 1; i <= k; i++) {
			a[i] = 1ll * first[i] * invfac[i] % MOD;
			b[i] = 1ll * second[i] * invfac[i] % MOD;
			a[i] = 1ll * a[i] * fpm(2, 1ll * i * right % (MOD - 1), MOD) % MOD;
		}
		FFT[h] -> DFT(a, length, 0);
		FFT[h] -> DFT(b, length, 0);
		for (int i = 0; i < length; i++) {
			ret[h][i] = 1ll * a[i] * b[i] % FFT[h] -> MOD;
		}
		FFT[h] -> DFT(ret[h], length, 1);
	}
	std::fill(result, result + k + 1, 0);
	for (int c = 0; c <= k; c++) {
		int a[3];
		a[0] = ret[0][c];
		a[1] = ret[1][c];
		a[2] = ret[2][c];
		result[c] = 1ll * CRT(a) * factor[c] % MOD;
	}
}

int main(void) {
	std::cin >> n >> k;
	if (n > k) return puts("0");
	else{
		static int ret[MAXN], res[MAXN];
		int length = FastFourierTransform::prepare(k);
		factor[0] = invfac[0] = 1;
		for (int i = 1; i <= k; i++) {
			factor[i] = 1ll * factor[i - 1] * i % MOD;
			invfac[i] = inverse(factor[i], MOD);
		}
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				inv[i][j] = inverse(FFT[i] -> MOD, FFT[j] -> MOD);
		std::fill(ret, ret + length, 0);
		std::fill(res, res + length, 0);
		ret[0] = 1;
		for (int i = 1; i <= k; i++) res[i] = 1;
		for (int b = n, r = 1; b; b >>= 1, r <<= 1) {
			if (b & 1) {
				getArray(ret, res, ret, length, r);
			}
			getArray(res, res, res, length, r);
		}
		int answer = 0;
		for (int i = 0; i <= k; i++) {
			int tmp = ret[i];
			tmp = 1ll * tmp * factor[k] % MOD;
			tmp = 1ll * tmp * invfac[i] % MOD;
			tmp = 1ll * tmp * invfac[k - i] % MOD;
			(answer += tmp) %= MOD;
		}
		std::cout << answer << std::endl;
	}
	return 0;
}
