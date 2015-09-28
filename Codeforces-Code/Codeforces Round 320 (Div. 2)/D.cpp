#include <cstdio>
#include <iostream>
#include <algorithm>

const int MAXN = 200001;

int n, k, x;
long long a[MAXN], pred[MAXN], succ[MAXN];

int main() {
	scanf("%d%d%d", &n, &k, &x);
	for (int i = 1; i <= n; i++) scanf("%I64d", a + i);
	for (int i = 1; i <= n; i++) pred[i] = pred[i - 1] | a[i];
	for (int i = n; i >= 1; i--) succ[i] = succ[i + 1] | a[i];
	long long ans = 0, z = 1;
	for (int i = 0; i <= k; i++) {
		for (int j = 1; j <= n; j++) {
			long long tmp = pred[j - 1] | (a[j] * z) | succ[j + 1];
			ans = std::max(ans, tmp);
		}
		z *= x;
	}
	std::cout << ans << std::endl;
	return 0;
}
