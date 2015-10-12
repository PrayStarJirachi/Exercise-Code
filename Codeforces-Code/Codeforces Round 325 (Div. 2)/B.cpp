#include <cstdio>
#include <algorithm>

const int INF = ~0u >> 2;
const int MAXN = 10001;

int n, a[3][MAXN], b[MAXN];

int main() {
	freopen("B.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 2; i <= n; i++) {
		scanf("%d", a[1] + i);
		a[1][i] += a[1][i - 1];
	}
	for (int i = 2; i <= n; i++) {
		scanf("%d", a[2] + i);
		a[2][i] += a[2][i - 1];
	}
	for (int i = 1; i <= n; i++) scanf("%d", b + i);
	int answer = INF;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j < i; j++) {
			int tmp = a[1][i] + a[1][j];
			tmp += a[2][n] - a[2][j] + a[2][n] - a[2][i];
			tmp += b[i] + b[j];
			answer = std::min(answer, tmp);
		}
	printf("%d\n", answer);
	return 0;
}
