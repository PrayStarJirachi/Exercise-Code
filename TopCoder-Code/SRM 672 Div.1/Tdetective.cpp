#include <cstdio>
#include <vector>
#include <string>
#include <numeric>
#include <cassert>
#include <iostream>
#include <algorithm>

const int INF = ~0u >> 2;
const int MAXN = 111;

class Tdetective{
public:
	int reveal(const std::vector<std::string> &data);
}T;

int n, cnt, g[MAXN][MAXN], w[MAXN][MAXN], fa[MAXN], d[MAXN], q[MAXN], z[MAXN], pre[MAXN], val[MAXN];
bool v[MAXN], vis[MAXN];

int getfa(int x) {
	return fa[x] != -1 ? fa[x] = getfa(fa[x]) : x;
}

int dfs(int x, int limit) {
	vis[x] = true;
	bool check = false;
	for (int i = 0; i < n; i++)
		if (!vis[i] && g[x][i] > limit) {
			dfs(i, limit);
			check = true;
		}
}

int Tdetective::reveal(const std::vector<std::string> &data) {
	n = data.size();
	std::fill(fa, fa + n, -1);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			g[i][j] = data[i][j] - '0';
			w[i][j] = INF;
		}
	for (int c = 9; c >= 0; c--) {
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++) {
				if (g[i][j] != c) continue;
				int fx = getfa(i), fy = getfa(j);
				if (fx == fy) continue;
				fa[fx] = fy;
				w[i][j] = w[j][i] = c;
			}
	}
	int left = 0, right = 0;
	q[++right] = 0; z[0] = INF; v[0] = true;
	while (left < right) {
		left++;
		for (int i = 0; i < n; i++) {
			if (v[i] || w[q[left]][i] == INF) continue;
			v[q[++right] = i] = true;
			z[q[right]] = std::min(z[q[left]], w[q[left]][i]);
		}
	}
	int ret = 0;
	for (int x = 1; x < n; x++) {
		std::fill(v, v + n, false);
		std::fill(d, d + n, INF);
		int left = 0, right = 0, limit = z[x];
		q[++right] = 0; d[0] = 0;
		while (left < right) {
			left++;
			for (int i = 0; i < n; i++) {
				if (v[i] || g[q[left]][i] < limit) continue;
				v[q[++right] = i] = true;
				pre[q[right]] = q[left];
				d[q[right]] = d[q[left]] + 1;
			}
		}
		for (int i = 0; i <= n; i++) val[i] = INF;
		std::fill(vis, vis + n, false);
		for (int i = x; i != 0; i = pre[i]) {
			val[pre[i]] = g[pre[i]][i];
		}
		for (int i = pre[x]; i != 0; i = pre[i])
			dfs(i, limit);
		dfs(0, limit);
		std::fill(v, v + n, false);
		for (int i = x; i != 0; i = pre[i])
			v[i] = true;
		cnt = 0;
		for (int i = 0; i < n; i++)
			if (v[i] || vis[i]) cnt++;
		ret += (cnt - 1) * x;
		printf("D[%d] = %d\n", x, cnt - 1);
	}
	return ret;
}


int main() {
	freopen("input.txt", "r", stdin);
	int n;
	std::vector<std::string> data;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		std::string tmp;
		std::cin >> tmp;
		data.push_back(tmp);
	}
	std::cout << T.reveal(data) << std::endl;
	return 0;
}
