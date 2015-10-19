#include <cstdio>
#include <algorithm>

#ifdef WIN32
	#define LL "%I64d"
#else
	#define LL "%lld"
#endif

const int MAXN = 1000001;
const int MAXP = 1000001;
const int mod = 1000000007;

int n, k, dp[MAXP], a[MAXN], sum[MAXN], d[MAXN];
long long l;

void update(int &x, int y) {
	x += y;
	if (x >= mod) x -= mod;
}

int main() {
	scanf("%d" LL "%d", &n, &l, &k);
	for (int i = 0; i < n; i++) {
		scanf("%d", a + i);
		dp[(1 - 1) * n + i] = 1;
		d[i + 1] = a[i];
	}
	std::sort(d + 1, d + n + 1);
	int tot = std::unique(d + 1, d + n + 1) - d - 1;
	for (int i = 0; i < n; i++) {
		a[i] = std::lower_bound(d + 1, d + tot + 1, a[i]) - d;
	}
	for (int i = 2; i <= k; i++) {
		for (int j = 1; j <= tot; j++) sum[j] = 0;
		for (int j = 0; j < n; j++) update(sum[a[j]], dp[(i - 1 - 1) * n + j]);
		for (int j = 1; j <= tot; j++) update(sum[j], sum[j - 1]);
		for (int j = 0; j < n; j++)	{
			dp[(i - 1) * n + j] = sum[a[j]];
		}
	}
	long long total = (l + n - 1) / n;
	int answer = l % mod;
	for (int c = 2; c <= k && c <= total; c++) {
		int tmp = 0;
		if (l % n == 0) {
			for (int i = 0; i < n; i++)
				update(tmp, dp[(c - 1) * n + i]);
			tmp = (long long)tmp * ((total - c + 1) % mod) % mod;
		}
		else{
			for (int i = 0; i < n; i++) update(tmp, dp[(c - 1) * n + i]);
			tmp = (long long)tmp * ((total - c) % mod) % mod;
			for (int j = 1; j <= tot; j++) sum[j] = 0;
			for (int j = 0; j < n; j++) update(sum[a[j]], dp[(c - 1 - 1) * n + j]);
			for (int j = 1; j <= tot; j++) update(sum[j], sum[j - 1]);
			for (int i = 0, rem = l % n; i < rem; i++) update(tmp, sum[a[i]]);
		}
		update(answer, tmp);
	}
	printf("%d\n", answer);
	return 0;
}
