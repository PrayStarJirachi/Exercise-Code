#include <cstdio>
#include <algorithm>

const int MAXN = 200001;

int n, a[MAXN], dp[MAXN];

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", a + i);
		if (a[i] >= a[i - 1]) dp[i] = dp[i - 1] + 1;
		else dp[i] = 1;
	}
	int answer = 0;
	for (int i = 1; i <= n; i++)
		answer = std::max(answer, dp[i]);
	printf("%d\n", answer);
	return 0;
}
