#include <cstdio>
#include <numeric>
#include <algorithm>

const int MAXM = 101;

int n, m, v[MAXM];

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		int t;
		scanf("%d", &t);
		for (int j = 1; j <= t; j++) {
			int x;
			scanf("%d", &x);
			v[x] = true;
		}
	}
	int sum = std::accumulate(v + 1, v + m + 1, 0);
	if (sum != m) puts("NO");
	else puts("YES");
	return 0;
}
