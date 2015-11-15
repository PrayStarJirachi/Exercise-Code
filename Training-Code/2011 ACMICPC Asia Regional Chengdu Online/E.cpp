#include <cmath>
#include <cstdio>
#include <algorithm>

const int MAXN = 11111;
const int MAXM = 22222;
const double EPS = 1e-10;

struct Edge{
	int node, next;
}edge[MAXM];

int T, n, t, flag, h[MAXN], deg[MAXN];
double a[MAXN], b[MAXN], c[MAXN], k[MAXN], e[MAXN];

bool dcmp(const double &x) {
	return fabs(x) < EPS ? 0 : (x > 0 ? 1 : -1);
}

void addedge(int x, int y) {
	t++; edge[t] = (Edge){y, h[x]}; h[x] = t;
	t++; edge[t] = (Edge){x, h[y]}; h[y] = t;
	deg[x]++; deg[y]++;
}

void dfs(int x, int fa) {
	double q = 1;
	a[x] = k[x];
	b[x] = (1.0 - k[x] - e[x]) / deg[x];
	c[x] = (1.0 - k[x] - e[x]);
	for (int i = h[x]; i; i = edge[i].next) {
		if (edge[i].node == fa) continue;
		dfs(edge[i].node, x);
		q -= (1.0 - k[x] - e[x]) / deg[x] * b[edge[i].node];
		a[x] += (1.0 - k[x] - e[x]) / deg[x] * a[edge[i].node];
		c[x] += (1.0 - k[x] - e[x]) / deg[x] * c[edge[i].node];
	}
	if (dcmp(q) == 0) {
		flag = false;
	}
	a[x] /= q;
	b[x] /= q;
	c[x] /= q;
}

int main() {
	freopen("E.in", "r", stdin);
	scanf("%d", &T);
	for (int cs = 1; cs <= T; cs++) {
		scanf("%d", &n);
		t = 0; flag = true;
		std::fill(h + 1, h + n + 1, 0);
		std::fill(deg + 1, deg + n + 1, 0);
		for (int i = 1; i < n; i++) {
			int x, y;
			scanf("%d%d", &x, &y);
			addedge(x, y);
		}
		for (int i = 1; i <= n; i++) {
			scanf("%lf%lf", k + i, e + i);
			k[i] /= 100;
			e[i] /= 100;
		}
		dfs(1, 0);
		printf("Case %d: ", cs);
		if (!flag || dcmp(a[1] - 1) == 0) puts("impossible");
		else printf("%.10f\n", c[1] / (1 - a[1]));
	}
	return 0;
}
