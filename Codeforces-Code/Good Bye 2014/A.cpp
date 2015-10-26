#include <cstdio>
#include <algorithm>

const int MAXN = 100001;

int n, t, a[MAXN];
bool dp[MAXN];

int main(void) {
	//freopen("A.in", "r", stdin);
	scanf("%d%d", &n, &t);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	dp[1] = true;
	for (int i = 1; i <= n; i++) {
		if (!dp[i]) continue;
		dp[i + a[i]] = true;
	}
	printf("%s\n", dp[t] ? "YES" : "NO");
	return 0;
}
