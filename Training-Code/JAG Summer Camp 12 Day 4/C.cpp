#include <cstdio>
#include <cstring>
#include <algorithm>

const int MAXR = 201;
const int MAXC = 31;
const int MAXS = 65537;
const int INF = ~0u >> 2;

int r, c, len[MAXR], dp[2][MAXS], presum[MAXS][MAXC], sufsum[MAXS][MAXC], t[MAXS][MAXC][2];
char s[MAXR][MAXC];

void update(int &x, int y) {
	if (x < y) x = y;
}

int main() {
	freopen("C.in", "r", stdin);
	scanf("%d%d", &r, &c);
	for (int i = 1; i <= r; i++) {
		scanf("%s", s[i] + 1);
		len[i] = strlen(s[i] + 1);
	}
	for (int i = 0; i < (1 << c); i++) {
		for (int j = 1; j <= c; j++) {
			presum[i][j] = presum[i][j - 1];
			if (i & (1 << j - 1)) presum[i][j]++;
		}
		for (int j = c; j >= 1; j--) {
			sufsum[i][j] = sufsum[i][j + 1];
			if (i & (1 << j - 1)) sufsum[i][j]++;
		}
	}
	for (int i = 0; i < (1 << c); i++)
		for (int j = 1; j <= c; j++) {
			t[i][j][0] = i & (((1 << c) - 1) ^ (1 << (j - 1)));
			t[i][j][1] = i | (1 << j - 1);
		}
	for (int i = 0; i < (1 << c); i++) {
		dp[0][i] = -INF;
		dp[1][i] = -INF;
	}
	dp[0][0] = 0;
	for (int i = 1; i <= r; i++) {
		for (int j = 1; j <= c; j++) {
			std::pair<int, int> nxt;
			nxt.first = (j == c) ? i + 1 : i;
			nxt.second = (j == c) ? 1 : j + 1;
			for (int k = 0; k < (1 << c); k++) {
				int cost = 0, posnow = presum[k][j - 1], pospre = len[i - 1] - sufsum[k][j] + 1;
				if (len[i] - posnow >= 0 && len[i] - posnow <= c - j) {
					update(dp[1][t[k][j][0]], dp[0][k]);
				}
				if (posnow < len[i]) {
					if (1 <= posnow && (k & (1 << j - 2)) && s[i][posnow] == s[i][posnow + 1]) {
						cost += 2;
					}
					if ((k & (1 << j - 1)) && pospre <= len[i - 1] && s[i - 1][pospre] == s[i][posnow + 1]) {
						cost += 2;
					}
					update(dp[1][t[k][j][1]], dp[0][k] + cost);
				}
			}
			for (int k = 0; k < (1 << c); k++) {
				dp[0][k] = dp[1][k];
				dp[1][k] = -INF;
			}
		}
	}
	int answer = 0;
	for (int i = 0; i < (1 << c); i++) {
		int counter = 0;
		for (int j = 1; j <= c; j++)
			if (i & (1 << j - 1)) counter++;
		if (counter == len[r]) {
			update(answer, dp[0][i]);
		}
	}
	printf("%d\n", answer);
	return 0;
}
