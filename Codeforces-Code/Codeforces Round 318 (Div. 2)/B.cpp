#include <cstdio>
#include <vector>
#include <algorithm>

const int MAXN = 4001;
const int INF = ~0u >> 2;

int n, m, deg[MAXN];
bool v[MAXN][MAXN];
std::vector<std::pair<int, int> > vec;

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		vec.push_back(std::make_pair(x, y));
		v[x][y] = true;
		v[y][x] = true;
		deg[x]++; deg[y]++;
	}
	int ans = INF;
	for (std::vector<std::pair<int, int> >::iterator it = vec.begin(); it != vec.end(); it++) {
		for (int i = 1; i <= n; i++) {
			if (!v[i][it -> first] || !v[i][it -> second]) continue;
			ans = std::min(ans, deg[it -> first] + deg[it -> second] + deg[i]);
		}
	}
	if (ans == INF) printf("-1\n");
	else printf("%d\n", ans - 6);
	return 0;
}
