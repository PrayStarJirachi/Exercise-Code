#include <cstdio>
#include <algorithm>

const int MAXN = 2222;
const int INF = ~0u >> 2;

int n, h, pos[MAXN], nxt[MAXN][2];
bool vis[MAXN][MAXN][2][2];
double p, dp[MAXN][MAXN][2][2];

double prob(const int &dir) {
	if (dir == 0) return p;
	else return 1 - p;
}

double dfs(int x, int y, int l, int r, int vL, int vR) {
	//printf("[%d, %d, %d, %d] = (%d, %d)\n", x, y, l, r, vL, vR);
	if (vis[x][y][l][r]) return dp[x][y][l][r];
	vis[x][y][l][r] = true;
	double &now = dp[x][y][l][r] = 0;
	for (int nW = 0; nW < 2; nW++)
		for (int nD = 0; nD < 2; nD++) {
			int nX, nY;
			if (nW == 0 && nD == 0) {
				nX = x + 1, nY = y;
				double tmp = dfs(nX, nY, nD, r, pos[nX - 1], vR);
				tmp += h - std::max(0, vL - (pos[nX - 1] - h));
				now += tmp * 0.5 * prob(nD);
			}
			if (nW == 0 && nD == 1) {
				nX = std::min(nxt[x][1], y + 1), nY = y;
				double tmp = dfs(nX, nY, nD, r, pos[nX - 1] + h, vR);
				tmp += ((pos[nX - 1] + h) - pos[x]) - std::max(0, (pos[nX - 1] + h) - vR);
				now += tmp * 0.5 * prob(nD);
			}
			if (nW == 1 && nD == 0) {
				nX = x, nY = std::max(nxt[y][0], x - 1);
				double tmp = dfs(nX, nY, l, nD ^ 1, vL, pos[nY + 1] - h);
				tmp += (pos[y] - (pos[nY + 1] - h)) - std::max(0, vL - (pos[nY + 1] - h));
				now += tmp * 0.5 * prob(nD);
			}
			if (nW == 1 && nD == 1) {
				nX = x, nY = y - 1;
				double tmp = dfs(nX, nY, l, nD ^ 1, vL, pos[nY + 1]);
				tmp += h - std::max(0, (pos[nY + 1] + h) - vR);
				now += tmp * 0.5 * prob(nD);
			}
		}
	return now;
}

int main() {
	freopen("D.in", "r", stdin);
	scanf("%d%d%lf", &n, &h, &p);
	for (int i = 1; i <= n; i++) scanf("%d", pos + i);
	std::sort(pos + 1, pos + n + 1);
	for (int i = 1; i <= n; i++)
		for (int l = 0; l < 2; l++)
			for (int r = 0; r < 2; r++) {
				vis[i + 1][i][l][r] = true;
				vis[i][i - 1][l][r] = true;
				dp[i + 1][i][l][r] = 0;
				dp[i][i - 1][l][r] = 0;
			}
	nxt[n][1] = n + 1;
	for (int i = n - 1; i >= 1; i--) {
		nxt[i][1] = i + 1;
		if (pos[i] + h > pos[i + 1]) {
			nxt[i][1] = nxt[i + 1][1];
		}
	}
	nxt[1][0] = 0;
	for (int i = 2; i <= n; i++) {
		nxt[i][0] = i - 1;
		if (pos[i] - h < pos[i - 1]) {
			nxt[i][0] = nxt[i - 1][0];
		}
	}
	double answer = 0;
	for (int which = 0; which < 2; which++)
		for (int dir = 0; dir < 2; dir++) {
			answer += 0.5 * prob(dir) * dfs(1, n, 0, 0, -INF, INF);
		}
	printf("%.10f\n", answer);
	return 0;
}
