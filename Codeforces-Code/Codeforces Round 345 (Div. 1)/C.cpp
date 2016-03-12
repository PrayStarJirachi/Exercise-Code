#include <bits/stdc++.h>

const int MAXM = 4000001;
const int MAXT = 4000001;

struct Edge{
	int node, next;
}e[MAXM];

int n, m, t, cnt, l[MAXT], tmp1[MAXT], h[MAXT], d[MAXT], fa[MAXT], deg[MAXT], a[MAXT], answer[MAXT], q[MAXT], r[MAXT][2];
bool v[MAXT];
std::pair<int, int> tmp2[MAXT];

int getfa(int x) {
	return fa[x] ? fa[x] = getfa(fa[x]) : x;
}

void merge(int x, int y) {
	int fx = getfa(x), fy = getfa(y);
	if (fx == fy) return;
	fa[fx] = fy;
}

void addEdge(int x, int y) {
	if (x == y) return;
	//printf("AddEdge(%d, %d)\n", x, y);
	t++; e[t] = (Edge){y, h[x]}; h[x] = t;
	deg[y]++;
}

int main() {
	std::cin >> n >> m;
	int tot = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			std::cin >> a[(i - 1) * m + j];
			d[++tot] = a[(i - 1) * m + j];
		}
	std::sort(d + 1, d + tot + 1);
	tot = std::unique(d + 1, d + tot + 1) - d - 1;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			a[(i - 1) * m + j] = std::lower_bound(d + 1, d + tot + 1, a[(i - 1) * m + j]) - d;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (!tmp1[a[(i - 1) * m + j]]) tmp1[a[(i - 1) * m + j]] = (i - 1) * m + j;
			else merge(tmp1[a[(i - 1) * m + j]], (i - 1) * m + j);
		}
		for (int j = 1; j <= m; j++) tmp1[a[(i - 1) * m + j]] = 0;
	}
	for (int j = 1; j <= m; j++) {
		for (int i = 1; i <= n; i++) {
			if (!tmp1[a[(i - 1) * m + j]]) tmp1[a[(i - 1) * m + j]] = (i - 1) * m + j;
			else merge(tmp1[a[(i - 1) * m + j]], (i - 1) * m + j);
		}
		for (int i = 1; i <= n; i++) tmp1[a[(i - 1) * m + j]] = 0;
	}
	for (int i = 1; i <= n * m; i++)
		if (!l[getfa(i)]) {
			l[getfa(i)] = ++cnt;
		}
	/*for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			printf("%d%c", l[getfa((i - 1) * m + j)], " \n"[j == m]);*/
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			tmp2[j] = std::make_pair(a[(i - 1) * m + j], (i - 1) * m + j);
		}
		std::sort(tmp2 + 1, tmp2 + m + 1);
		for (int j = 2, z = tmp2[1].second; j <= m; j++) {
			addEdge(l[getfa(tmp2[j].second)], l[getfa(z)]);
			if (tmp2[j].first != tmp2[j - 1].first) z = tmp2[j].second;
		}
	}
	for (int j = 1; j <= m; j++) {
		for (int i = 1; i <= n; i++) {
			tmp2[i] = std::make_pair(a[(i - 1) * m + j], (i - 1) * m + j);
		}
		std::sort(tmp2 + 1, tmp2 + n + 1);
		for (int i = 2, z = tmp2[1].second; i <= n; i++) {
			addEdge(l[getfa(tmp2[i].second)], l[getfa(z)]);
			if (tmp2[i].first != tmp2[i - 1].first) z = tmp2[i].second;
		}
	}
	int left = 0, right = 0, lMax = 0;
	for (int i = 1; i <= cnt; i++) {
		if (deg[i]) continue;
		v[q[++right] = i] = true;
		answer[i] = 1;
	}
	while (left < right) {
		left++;
		lMax = std::max(lMax, answer[q[left]]);
		for (int i = h[q[left]]; i; i = e[i].next) {
			if (v[e[i].node] || --deg[e[i].node]) continue;
			answer[e[i].node] = answer[q[left]] + 1;
			v[q[++right] = e[i].node] = true;
		}
	}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			printf("%d%c", lMax - answer[l[getfa((i - 1) * m + j)]] + 1, " \n"[j == m]);
	return 0;
}
