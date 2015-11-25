#include <cstdio>
#include <algorithm>

const int MAXN = 444;
const int MAXQ = 111111;
const int INF = ~0u >> 2;

int n, m, a[MAXN][MAXN], b[MAXN][MAXN];

int main() {
	freopen("A.in", "r", stdin);
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) {
			a[i][j] = (i == j) ? 0 : INF;
			b[i][j] = (i == j) ? 0 : 1;
		}
	for (int i = 1; i <= m; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		a[x][y] = a[y][x] = 1;
		b[x][y] = b[y][x] = INF;
	}
	bool which = (a[1][n] == 1);
	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++) {
				if (i == j || i == k || k == j) continue;
				a[i][j] = std::min(a[i][j], a[i][k] + a[k][j]);
				b[i][j] = std::min(b[i][j], b[i][k] + b[k][j]);
			}
	if (a[1][n] == 1) {
		printf("%d\n", b[1][n] == INF ? -1 : b[1][n]);
	} else {
		printf("%d\n", a[1][n] == INF ? -1 : a[1][n]);
	}
	return 0;
}
