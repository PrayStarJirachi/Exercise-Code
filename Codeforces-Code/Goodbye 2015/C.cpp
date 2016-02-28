#include <cstdio>
#include <iostream>
#include <algorithm>

const int MAXN = 555;

int n, m, q;
char c[MAXN][MAXN];
int a[MAXN][MAXN][2], s[MAXN][MAXN][2];

int getAnswer(int k, int x1, int y1, int x2, int y2) {
	int ret = 0;
	ret += s[x2][y2][k];
	ret -= s[x1 - 1][y2][k];
	ret -= s[x2][y1 - 1][k];
	ret += s[x1 - 1][y1 - 1][k];
	return ret;
}

int main() {
	std::cin >> n >> m;
	for (int i = 1; i <= n; i++) std::cin >> c[i] + 1;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			if (c[i][j] == '.') {
				if (c[i][j - 1] == '.') a[i][j][0]++;
				if (c[i - 1][j] == '.') a[i][j][1]++;
			}
			s[i][j][0] = s[i][j - 1][0] + s[i - 1][j][0] + a[i][j][0] - s[i - 1][j - 1][0];
			s[i][j][1] = s[i][j - 1][1] + s[i - 1][j][1] + a[i][j][1] - s[i - 1][j - 1][1];
		}
	std::cin >> q;
	for (int i = 1; i <= q; i++) {
		int x1, x2, y1, y2;
		std::cin >> x1 >> y1 >> x2 >> y2;
		int answer = 0;
		answer += getAnswer(0, x1, y1 + 1, x2, y2);
		answer += getAnswer(1, x1 + 1, y1, x2, y2);
		std::cout << answer << std::endl;
	}
	return 0;
}

