#include <bits/stdc++.h>

const int MAXN = 500001;
const int MAXM = 1000001;

struct Edge{
	int node, next;
}e[2][MAXM];

int n, t[2], h[2][MAXN], f[2][MAXN], fa[MAXN];
std::map<std::pair<int, int>, int> map;
std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > answer;

int getfa(int x) {
	return fa[x] ? fa[x] = getfa(fa[x]) : x;
}

void merge(int x, int y) {
	//printf("Merge(%d, %d)\n", x, y);
	int fx = getfa(x), fy = getfa(y);
	if (fx == fy) return;
	fa[fx] = fy;
}

void addEdge(int id, int x, int y) {
	t[id]++; e[id][t[id]] = (Edge){y, h[id][x]}; h[id][x] = t[id];
	t[id]++; e[id][t[id]] = (Edge){x, h[id][y]}; h[id][y] = t[id];
}

void dfs(int id, int x) {
	for (int i = h[id][x]; i; i = e[id][i].next) {
		int now = e[id][i].node;
		if (now == f[id][x]) continue;
		f[id][now] = x;
		dfs(id, now);
		if (id == 0) {
			int ex = std::min(x, now), ey = std::max(x, now);
			if (map[std::make_pair(ex, ey)] != 2) {
				if (f[1][x] == now) {
					answer.push_back(std::make_pair(std::make_pair(now, x), std::make_pair(getfa(x), f[1][getfa(x)])));
					merge(getfa(x), f[1][getfa(x)]);
				} else {
					answer.push_back(std::make_pair(std::make_pair(now, x), std::make_pair(getfa(now), f[1][getfa(now)])));
					merge(getfa(now), f[1][getfa(now)]);
				}
			}
		} else {
			int ex = std::min(x, now), ey = std::max(x, now);
			if (map.count(std::make_pair(ex, ey))) {
				map[std::make_pair(ex, ey)] = 2;
				merge(now, x);
			}
		}
	}
}

int main() {
	freopen("E.in", "r", stdin);
	std::cin >> n;
	for (int i = 1; i < n; i++) {
		int x, y;
		std::cin >> x >> y;
		if (x > y) std::swap(x, y);
		map[std::make_pair(x, y)] = 1;
		addEdge(0, x, y);
	}
	for (int i = 1; i < n; i++) {
		int x, y;
		std::cin >> x >> y;
		addEdge(1, x, y);
	}
	dfs(1, 1);
	dfs(0, 1);
	std::cout << answer.size() << std::endl;
	for (auto x : answer) {
		std::cout << x.first.first << " " << x.first.second << " ";
		std::cout << x.second.first << " " << x.second.second << "\n";
	}
	return 0;
}
