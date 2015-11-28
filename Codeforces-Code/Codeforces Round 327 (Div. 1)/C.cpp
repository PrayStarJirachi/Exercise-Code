#include <cstdio>
#include <algorithm>

const int MAXN = 1111;
const int MAXQ = 6666666;
const int INF = ~0u >> 3;

const int DX[] = {1, -1, 0, 0};
const int DY[] = {0, 0, 1, -1};

int n, m, d[4][MAXN][MAXN];
char map[MAXN][MAXN];
std::pair<int, int> Q[MAXQ];
bool v[MAXN][MAXN];

void solve(int a) {
	int left = 0, right = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			d[a][i][j] = INF;
	std::pair<int, int> *queue = Q + 3333333;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			if (map[i][j] == '0' + a) {
				d[a][i][j] = 0;
				queue[++right] = std::make_pair(i, j);
				v[i][j] = true;
			}
		}
	while (left < right) {
		left++;
		std::pair<int, int> now = queue[left];
		for (int dir = 0; dir < 4; dir++) {
			int nx = now.first + DX[dir];
			int ny = now.second + DY[dir];
			if (nx < 1 || nx > n || ny < 1 || ny > m || map[nx][ny] == '#') continue;
			int cost = (map[nx][ny] == '.');
			if (d[a][nx][ny] > d[a][now.first][now.second] + cost) {
				d[a][nx][ny] = d[a][now.first][now.second] + cost;
				if (!v[nx][ny]) {
					if (cost == 0) queue[left--] = std::make_pair(nx, ny);
					else queue[++right] = std::make_pair(nx, ny);
					v[nx][ny] = true;
				}
			}
		}
		v[now.first][now.second] = false;
	}
}

int main() {
	freopen("C.in", "r", stdin);
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%s", map[i] + 1);
	}
	int answer = INF;
	for (int a = 1; a <= 3; a++) solve(a);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			if (map[i][j] == '.') {
				answer = std::min(answer, d[1][i][j] + d[2][i][j] + d[3][i][j] - 2);
			} else if (map[i][j] != '#') {
				answer = std::min(answer, d[1][i][j] + d[2][i][j] + d[3][i][j]);
			}
		}
	if (answer == INF) puts("-1");
	else printf("%d\n", answer);
	return 0;
}
