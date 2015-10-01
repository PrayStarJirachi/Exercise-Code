#include <queue>
#include <cstdio>
#include <vector>
#include <algorithm>

const int MAXN = 1001;
const int MAXM = 4000001;
const int dx[] = {1, -1, 0, 0};
const int dy[] = {0, 0, 1, -1};
const int INF = ~0u >> 2;

int n, m, sx, sy, ex, ey, t, d[MAXN][MAXN];
char map[MAXN][MAXN];
bool v[MAXN][MAXN];
std::priority_queue<std::pair<int, std::pair<int, int> >, std::vector<std::pair<int, std::pair<int, int> > >, std::greater<std::pair<int, std::pair<int, int> > > > heap;

int main() {
	freopen("F.in", "r", stdin);
	while (scanf("%d%d", &n, &m) == 2 && n && m) {
		for (int i = 1; i <= n; i++) {
			scanf("%s", map[i] + 1);
		}
		scanf("%d%d", &sx, &sy);
		scanf("%d%d", &ex, &ey);
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++) {
				v[i][j] = false;
				d[i][j] = INF;
			}
		heap.push(std::make_pair(d[sx][sy] = 0, std::make_pair(sx, sy)));
		while (!heap.empty()) {
			std::pair<int, std::pair<int, int> > top = heap.top(); heap.pop();
			if (v[top.second.first][top.second.second]) continue;
			v[top.second.first][top.second.second] = true;
			for (int dir = 0; dir < 4; dir++) {
				int nx = top.second.first + dx[dir];
				int ny = top.second.second + dy[dir];
				if (nx < 1 || nx > n || ny < 1 || ny > m) continue;
				int cost = map[nx][ny] == '.';
				if (!v[nx][ny] && d[nx][ny] > d[top.second.first][top.second.second] + cost) {
					d[nx][ny] = d[top.second.first][top.second.second] + cost;
					heap.push(std::make_pair(d[nx][ny], std::make_pair(nx, ny)));
				}
			}
		}
		printf("%d\n", d[ex][ey]);
	}
	return 0;
}
