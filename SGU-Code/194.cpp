#include <cstdio>
#include <algorithm>

const int MAXN = 111111;
const int MAXM = 222222;
const int INF = ~0u >> 2;

struct Edge{
	int node, next, flow, opp;
}e[MAXM];

int n, m, tot, h[MAXN], d[MAXN], pre[MAXN], gap[MAXN], delta[MAXN], cur[MAXN];
std::pair<int, int> road[MAXM];

void addedge(int x, int y, int f) {
	tot++; e[tot] = (Edge){y, h[x], f, tot + 1}; h[x] = tot;
	tot++; e[tot] = (Edge){x, h[y], 0, tot - 1}; h[y] = tot;
}

int Maxflow_Isap(int s,int t,int n) {
	std::fill(pre + 1, pre + n + 1, 0);
	std::fill(d + 1, d + n + 1, 0);
	std::fill(gap + 1, gap + n + 1, 0);
	for (int i = 1; i <= n; i++) cur[i] = h[i];
	gap[0] = n;
	int u = pre[s] = s, v, maxflow = 0;
	while (d[s] < n) {
		v = n + 1;
		for (int i = cur[u]; i; i = e[i].next)
		if (e[i].flow && d[u] == d[e[i].node] + 1) {
			v = e[i].node; cur[u]=i; break;
		}
		if (v <= n) {
			pre[v] = u; u = v;
			if (v == t) {
				int dflow = INF, p = t; u = s;
				while (p != s) {
					p = pre[p];
					dflow = std::min(dflow, e[cur[p]].flow);
				}
				maxflow += dflow; p = t;
				while (p != s) {
					p = pre[p];
					e[cur[p]].flow -= dflow;
					e[e[cur[p]].opp].flow += dflow;
				}
			}
		}
		else{
			int mindist = n + 1;
			for (int i = h[u]; i; i = e[i].next)
				if (e[i].flow && mindist > d[e[i].node]) {
					mindist = d[e[i].node]; cur[u] = i;
				}
			if (!--gap[d[u]]) return maxflow;
			gap[d[u] = mindist + 1]++; u = pre[u];
		}
	}
	return maxflow;
}


int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) {
		int x, y, l, r;
		scanf("%d%d%d%d", &x, &y, &l, &r);
		addedge(x, y, r - l);
		delta[x] -= l;
		delta[y] += l;
		road[i] = std::make_pair(tot, l);
	}
	int sumS = 0, sumT = 0;
	for (int i = 1; i <= n; i++) {
		if (delta[i] > 0) {
			addedge(n + 1, i, delta[i]);
			sumS += delta[i];
		}
		if (delta[i] < 0) {
			addedge(i, n + 2, -delta[i]);
			sumT += -delta[i];
		}
	}
	int maxflow = Maxflow_Isap(n + 1, n + 2, n + 2);
	if (maxflow != sumS || maxflow != sumT) return puts("NO"), 0;
	else{
		puts("YES");
		for (int i = 1; i <= m; i++) {
			printf("%d\n", road[i].second + e[road[i].first].flow);
		}
	}
	return 0;
}
