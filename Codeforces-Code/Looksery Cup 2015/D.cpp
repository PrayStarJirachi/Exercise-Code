#include <cstdio>
#include <algorithm>

const int MAXN = 222;

int n, m, r[MAXN][MAXN];
char s[MAXN][MAXN];

int main() {
	freopen("D.in", "r", stdin);
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%s", s[i] + 1);
		for (int j = 1; j <= m; j++)
			if (s[i][j] == 'B') r[i][j] = -1;
			else r[i][j] = 1;
	}
	int answer = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			int tmp = r[i][j] - r[i + 1][j] - r[i][j + 1] + r[i + 1][j + 1];
			if (tmp != 0) answer++;
		}
	printf("%d\n", answer);
	return 0;
}
