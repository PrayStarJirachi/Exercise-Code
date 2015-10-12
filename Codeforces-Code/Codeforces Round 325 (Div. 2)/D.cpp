#include <cstdio>
#include <algorithm>

const int MAXN = 201;

int T, n, k;
bool dp[MAXN][4];
char map[4][MAXN];

int main() {
	freopen("D.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &k);
		for (int i = 1; i <= 3; i++) scanf("%s", map[i] + 1);
		for (int i = n + 1; i <= n + 3; i++) {
			map[1][i] = map[2][i] = map[3][i] = '.';
		}
		for (int y = 1; y <= n + 3; y++)
			for (int x = 1; x <= 3; x++)
				dp[y][x] = false;
		for (int x = 1; x <= 3; x++)
			if (map[x][1] == 's') {
				dp[1][x] = true;
			}
		for (int y = 1; y <= n; y++)
			for (int x = 1; x <= 3; x++) {
				if (!dp[y][x]) continue;
				// Up
				if (x > 1 && map[x][y + 1] == '.' && map[x - 1][y + 1] == '.' && 
				    map[x - 1][y + 2] == '.' && map[x - 1][y + 3] == '.') {
				    dp[y + 3][x - 1] = true;
				}
				// Pause
				if (map[x][y + 1] == '.' && map[x][y + 2] == '.' && map[x][y + 3] == '.') {
					dp[y + 3][x] = true;
				}
				if (x < 3 && map[x][y + 1] == '.' && map[x + 1][y + 1] == '.' && 
				    map[x + 1][y + 2] == '.' && map[x + 1][y + 3] == '.') {
				    dp[y + 3][x + 1] = true;
				}
			}
		bool answer = false;
		for (int y = n + 1; y <= n + 3; y++)
			for (int x = 1; x <= 3; x++)
				answer |= dp[y][x];
		printf("%s\n", answer ? "YES" : "NO");
	}
	return 0;
}
