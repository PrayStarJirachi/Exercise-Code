#include <cstdio>
#include <algorithm>

const char RNASET[] = "ACGT";
const int MAXN = 2000001;
const int mod = 998244353;
const int prt = 3;

int sLen, tLen, k, s[MAXN], A[MAXN], B[MAXN];
char sRaw[MAXN], tRaw[MAXN];
bool answer[MAXN];

int fpm(int a, int b, int p) {
	int ret = 1;
	for (; b; b >>= 1) {
		if (b & 1) ret = (long long)ret * a % p;
		a = (long long)a * a % p;
	}
	return ret;
}

int prepare(int n) {
	int len = 1;
	for (; len <= 2 * n; len <<= 1);
	return len;
}

void DFT(int *a, int n, int f) {
	for (int i = 0, j = 0; i < n; i++) {
		if (i > j) std::swap(a[i], a[j]);
		for (int t = n >> 1; (j ^= t) < t; t >>= 1);
	}
	for (int i = 2; i <= n; i <<= 1) {
		int z = (f == 0) ? ((mod - 1)) / i : ((mod - 1) / i * (i - 1));
		int wm = fpm(prt, z, mod);
		for (int j = 0; j < n; j += i) {
			for (int k = 0, w = 1; k < (i >> 1); k++) {
				int A = a[j + k];
				int B = (long long)a[j + k + (i >> 1)] * w % mod;
				a[j + k] = (A + B);
				a[j + k + (i >> 1)] = (A - B + mod);
				if (a[j + k] >= mod) a[j + k] -= mod;
				if (a[j + k + (i >> 1)] >= mod) a[j + k + (i >> 1)] -= mod;
				w = (long long)w * wm % mod;
			}
		}
	}
	if (f == 1) {
		long long rev = fpm(n, mod - 2, mod);
		for (int i = 0; i < n; i++) {
			a[i] = (long long)a[i] * rev % mod;
		}
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d%d%d", &sLen, &tLen, &k);
	scanf("%s", sRaw + 1);
	scanf("%s", tRaw + 1);
	int len = prepare(sLen + 1);
	std::fill(answer + 1, answer + (sLen - tLen + 1) + 1, true);
	for (int now = 0; now < 4; now++) {
		for (int i = 1; i <= sLen; i++) {
			s[i] = s[i - 1] + (sRaw[i] == RNASET[now]);
		}
		std::fill(A, A + len, 0);
		std::fill(B, B + len, 0);
		for (int i = 1; i <= sLen; i++) {
			int r = std::min(sLen, i + k);
			int l = std::max(1, i - k);
			if (s[r] - s[l - 1]) A[i] = 1;
			else A[i] = 0;
		}
		int tmp = 0;
		for (int i = 1; i <= tLen; i++) {
			B[tLen - i + 1] = (tRaw[i] == RNASET[now]);
			tmp += (tRaw[i] == RNASET[now]);
		}
		DFT(A, len, 0);
		DFT(B, len, 0);
		for (int i = 0; i < len; i++) {
			A[i] = (long long)A[i] * B[i] % mod;
		}
		DFT(A, len, 1);
		for (int i = tLen + 1; i <= tLen + (sLen - tLen + 1); i++) {
			if (tmp != A[i]) answer[i - tLen] = false;
		}
	}
	int counter = 0;
	for (int i = 1; i <= sLen - tLen + 1; i++)
		counter += answer[i];
	printf("%d\n", counter);
	return 0;
}
