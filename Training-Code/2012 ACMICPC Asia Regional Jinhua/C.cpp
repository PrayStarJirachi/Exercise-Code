#include <cstdio>
#include <vector>
#include <algorithm>

const int MAXN = 555;
const int MAXD = 111111;
const int MAXM = 222222;
const int MAXQ = 666666;
const int INF = ~0u >> 2;
const int COST[4][4] = {{0, 0, 1, 1}, {0, 0, 1, 1}, {1, 1, 0, 0}, {1, 1, 0, 0}};

struct Edge{
	int node, next, dist;
}e[MAXM];

int n, tot, id[MAXN][MAXN][4], h[MAXD], Q[MAXQ], d[MAXD];
std::vector<int> vx, vy;
bool go[MAXN][MAXN][4][4], v[MAXD];
std::pair<int, int> A, B;
std::pair<std::pair<int, int>, std::pair<int, int> > r[MAXN];

void addedge(int x, int y, int c) {
	tot++;
	e[tot].node = y;
	e[tot].next = h[x];
	e[tot].dist = c;
	h[x] = tot;
	tot++;
	e[tot].node = x;
	e[tot].next = h[y];
	e[tot].dist = c;
	h[y] = tot;
}

int main() {
	freopen("C.in", "r", stdin);
	while (true) {
		scanf("%d%d%d%d", &A.first, &A.second, &B.first, &B.second);
		if (A.first == 0 && A.second == 0 && B.first == 0 && B.second == 0) break;
		scanf("%d", &n);
		vx.clear();
		vy.clear();
		vx.push_back(A.first);
		vx.push_back(B.first);
		vy.push_back(A.second);
		vy.push_back(B.second);
		for (int p = 1; p <= n; p++) {
			scanf("%d%d%d%d", &r[p].first.first, &r[p].first.second, &r[p].second.first, &r[p].second.second);
			if (r[p].first.first > r[p].second.first) std::swap(r[p].first.first, r[p].second.first);
			if (r[p].first.second > r[p].second.second) std::swap(r[p].first.second, r[p].second.second);
			vx.push_back(r[p].first.first);
			vx.push_back(r[p].second.first);
			vy.push_back(r[p].first.second);
			vy.push_back(r[p].second.second);
		}
		std::sort(vx.begin(), vx.end());
		std::sort(vy.begin(), vy.end());
		vx.erase(std::unique(vx.begin(), vx.end()), vx.end());
		vy.erase(std::unique(vy.begin(), vy.end()), vy.end());
		int cnt = 0;
		for (int i = 0; i < (int)vx.size(); i++)
			for (int j = 0; j < (int)vy.size(); j++)
				for (int k = 0; k < 4; k++) {
					id[i][j][k] = ++cnt;
				}
		tot = 0;
		std::fill(h + 1, h + cnt + 1, 0);
		for (int i = 0; i < (int)vx.size(); i++)
			for (int j = 0; j < (int)vy.size(); j++) {
				for (int k = 0; k < 4; k++)
					for (int l = 0; l < 4; l++)
						go[i][j][k][l] = false;
				go[i][j][0][2] = go[i][j][0][3] = true;
				go[i][j][2][0] = go[i][j][2][1] = true;
				go[i][j][3][0] = go[i][j][3][1] = true;
				go[i][j][1][2] = go[i][j][1][3] = true;
				for (int p = 1; p <= n; p++) {
					if (r[p].first.first == vx[i]) {
						if (vy[j] == r[p].first.second) go[i][j][0][2] = go[i][j][2][0] = false;
						else if (vy[j] == r[p].second.second) go[i][j][1][2] = go[i][j][2][1] = false;
						else if (r[p].first.second < vy[j] && vy[j] < r[p].second.second) {
							go[i][j][0][2] = go[i][j][2][0] = false;
							go[i][j][1][2] = go[i][j][2][1] = false;
						}
					}
					else if (r[p].second.first == vx[i]) {
						if (vy[j] == r[p].first.second) go[i][j][0][3] = go[i][j][3][0] = false;
						else if (vy[j] == r[p].second.second) go[i][j][1][3] = go[i][j][3][1] = false;
						else if (r[p].first.second < vy[j] && vy[j] < r[p].second.second) {
							go[i][j][0][3] = go[i][j][3][0] = false;
							go[i][j][1][3] = go[i][j][3][1] = false;
						}
					}
					else if (r[p].first.first < vx[i] && vx[i] < r[p].second.first){
						if (vy[j] == r[p].first.second) {
							go[i][j][3][0] = go[i][j][0][3] = false;
							go[i][j][2][0] = go[i][j][0][2] = false;
						}
						else if (vy[j] == r[p].second.second){
							go[i][j][1][2] = go[i][j][2][1] = false;
							go[i][j][1][3] = go[i][j][3][1] = false;
						}
						else if (r[p].first.second < vy[j] && vy[j] < r[p].second.second) {
							go[i][j][3][0] = go[i][j][0][3] = false;
							go[i][j][2][0] = go[i][j][0][2] = false;
							go[i][j][1][2] = go[i][j][2][1] = false;
							go[i][j][1][3] = go[i][j][3][1] = false;
						}
					}
				}
				for (int k = 0; k < 4; k++)
					for (int p = 0; p < 4; p++)
						for (int q = 0; q < 4; q++)
							if (p != q && p != k && q != k) {
								go[i][j][p][q] |= go[i][j][p][k] & go[i][j][k][q];
							}
				for (int p = 0; p < 4; p++)
					for (int q = 0; q < 4; q++) {
						if (!go[i][j][p][q]) continue;
						addedge(id[i][j][p], id[i][j][q], COST[p][q]);
					}
			}
		for (int i = 0; i < (int)vx.size(); i++)
			for (int j = 0; j < (int)vy.size(); j++) {
				if (j + 1 < (int)vy.size()) addedge(id[i][j][0], id[i][j + 1][1], 0);
				if (j > 0) addedge(id[i][j][1], id[i][j - 1][0], 0);
				if (i + 1 < (int)vx.size()) addedge(id[i][j][2], id[i + 1][j][3], 0);
				if (i > 0) addedge(id[i][j][3], id[i - 1][j][2], 0);
			}
		std::fill(d + 1, d + cnt + 1, INF);
		std::fill(v + 1, v + cnt + 1, false);
		int left = 0, right = 0, *q = Q + 333333;
		for (int k = 0; k < 4; k++) {
			int px = std::lower_bound(vx.begin(), vx.end(), A.first) - vx.begin();
			int py = std::lower_bound(vy.begin(), vy.end(), A.second) - vy.begin();
			d[id[px][py][k]] = 0;
			v[q[++right] = id[px][py][k]] = true;
		}
		while (left < right) {
			left++;
			for (int i = h[q[left]]; i; i = e[i].next) {
				if (v[e[i].node]) continue;
				if (e[i].dist == 0) {
					d[e[i].node] = d[q[left]] + e[i].dist;
					v[q[left--] = e[i].node] = true;
				}
				else{
					d[e[i].node] = d[q[left]] + 1;
					v[q[++right] = e[i].node] = true;
				}
			}
		}
		int answer = INF;
		for (int k = 0; k < 4; k++) {
			int px = std::lower_bound(vx.begin(), vx.end(), B.first) - vx.begin();
			int py = std::lower_bound(vy.begin(), vy.end(), B.second) - vy.begin();
			answer = std::min(answer, d[id[px][py][k]]);
		}
		if (answer == INF) puts("-1");
		else printf("%d\n", answer);
	}
	return 0;
}
