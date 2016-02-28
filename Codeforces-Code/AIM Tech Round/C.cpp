#include <cstdio>
#include <numeric>
#include <iostream>
#include <algorithm>

const double EPS = 1e-7;
const double PI = 3.1415926535897932384626;
const int MAXN = 501;

int n, m, tot, c[MAXN], answer[MAXN];
bool a[MAXN][MAXN];

bool dfs(int x) {
	tot++;
	for (int i = 1; i <= n; i++) {
		if (x == i || !a[x][i]) continue;
		int value = 3 - c[x];
		if (c[i]) {
			if (c[i] != value) return false;
			else continue;
		}
		c[i] = value;
		if (!dfs(i)) return false;
	}
	return true;
}

int main() {
	// freopen("input.txt", "r", stdin);
	std::cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		int x, y;
		std::cin >> x >> y;
		a[x][y] = a[y][x] = true;
	}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			a[i][j] = !a[i][j];
	for (int i = 1; i <= n; i++) {
		if (c[i]) continue;
		tot = 0;
		c[i] = 1;
		if (!dfs(i)) return puts("No"), 0;
		if (tot == 1) answer[i] = 1;
	}
	for (int i = 1; i <= n; i++) {
		if (answer[i] || c[i] != 1) continue;
		for (int j = 1; j <= n; j++) {
			if (answer[j] || c[j] != 2) continue;
			if (!a[i][j]) return puts("No"), 0;
		}
	}
	for (int i = 1; i <= n; i++) {
		if (answer[i]) continue;
		if (c[i] == 2) answer[i] = 2;
	}
	puts("Yes");
	for (int i = 1; i <= n; i++)
		putchar(answer[i] + 'a');
	puts("");
	return 0;
}
