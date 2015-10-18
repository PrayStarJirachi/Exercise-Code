#include <cstdio>
#include <vector>
#include <algorithm>

const int MAXN = 200001;
const int MAXM = 400001;

struct Edge{
	int node, next, pos;
}e[MAXM];

int n, m, t, h[MAXN], deg[MAXN], q[MAXN], c[MAXM];
std::pair<int, int> edge[MAXM];
std::vector<int> pos[MAXM], neg[MAXM];
bool v[MAXN];

void addedge(int x, int y, int p) {
	t++; e[t] = (Edge){y, h[x], p}; h[x] = t;
	t++; e[t] = (Edge){x, h[y], p}; h[y] = t;
}

void getCir(int x) {
	v[x] = true;
	for (int i = h[x]; i; i = e[i].next)
		if (!v[e[i].node]) {
			c[e[i].pos] = e[i].node;
			getCir(e[i].node);
		}
}

int main() {
	freopen("C.in", "r", stdin);
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		int tot; scanf("%d", &tot);
		for (int j = 1; j <= tot; j++) {
			int x; scanf("%d", &x);
			if (x > 0) {
				edge[x].first = i;
				pos[x].push_back(i);
			}
			else{
				edge[-x].second = i;
				neg[-x].push_back(i);
			}
		}
	}
	for (int i = 1; i <= m; i++) {
		if (!edge[i].first || !edge[i].second) continue;
		addedge(edge[i].first, edge[i].second, i);
		deg[edge[i].first]++;
		deg[edge[i].second]++;
	}
	int left = 0, right = 0;
	for (int i = 1; i <= m; i++) {
		if (edge[i].first && !edge[i].second) {
			c[i] = edge[i].first;
			for (int j = 0; j < (int)pos[i].size(); j++) {
				int now = pos[i][j];
				q[++right] = now;
				v[now] = true;
			}
		}
		else if (!edge[i].first && edge[i].second) {
			c[i] = edge[i].second;
			for (int j = 0; j < (int)neg[i].size(); j++) {
				int now = neg[i][j];
				q[++right] = now;
				v[now] = true;
			}
		}
		else c[i] = edge[i].first;
	}
	while (left < right) {
		left++;
		for (int i = h[q[left]]; i; i = e[i].next) {
			if (v[e[i].node]) continue;
			v[q[++right] = e[i].node] = true;
			c[e[i].pos] = e[i].node;
		}
	}
	left = right = 0;
	for (int i = 1; i <= n; i++) {
		if (!v[i] && deg[i] <= 1) {
			q[++right] = i;
			v[i] = true;
		}
	}
	while (left < right) {
		left++;
		for (int i = h[q[left]]; i; i = e[i].next) {
			if (v[e[i].node]) continue;
			deg[e[i].node]--;
			c[e[i].pos] = q[left];
			if (deg[e[i].node] <= 1) {
				q[++right] = e[i].node;
				v[e[i].node] = true;
			}
		}
	}
	std::fill(deg + 1, deg + n + 1, 0);
	for (int i = 1; i <= m; i++) {
		if (!edge[i].first || !edge[i].second) continue;
		if (v[edge[i].first] || v[edge[i].second]) continue;
		c[i] = edge[i].second;
		getCir(edge[i].second);
	}
	std::fill(deg + 1, deg + n + 1, 0);
	for (int i = 1; i <= m; i++) {
		if (c[i] == edge[i].first) {
			for (int j = 0; j < (int)pos[i].size(); j++) {
				deg[pos[i][j]]++;
			}
		}
		else{
			for (int j = 0; j < (int)neg[i].size(); j++) {
				deg[neg[i][j]]++;
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		if (!deg[i]) {
			puts("NO");
			return 0;
		}
	}
	puts("YES");
	for (int i = 1; i <= m; i++)
		putchar('0' + (c[i] == edge[i].first));
	puts("");
	return 0;
}
