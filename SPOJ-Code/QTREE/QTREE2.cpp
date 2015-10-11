#include <cstdio>
#include <cstring>
#include <algorithm>

const int MAXN = 100001;
const int MAXM = 200001;
const int Maxlog = 20;

struct Edge{
	int node, next, dist;
}e[MAXM];

int T, n, t, h[MAXN], fa[MAXN][21], d[MAXN], s[MAXN];

void addedge(int x, int y, int c) {
	t++; e[t] = (Edge){y, h[x], c}; h[x] = t;
	t++; e[t] = (Edge){x, h[y], c}; h[y] = t;
}

void buildtree(int x) {
	static int q[MAXN];
	int left = 0, right = 0;
	q[++right] = x;
	while (left < right) {
		left++;
		for (int i = h[q[left]]; i; i = e[i].next) {
			if (e[i].node == fa[q[left]][0]) continue;
			fa[e[i].node][0] = q[left];
			d[e[i].node] = d[q[left]] + 1;
			s[e[i].node] = s[q[left]] + e[i].dist;
			q[++right] = e[i].node;
		}
	}
	for (int j = 1; j <= Maxlog; j++)
		for (int i = 1; i <= n; i++) {
			fa[i][j] = fa[fa[i][j - 1]][j - 1];
		}
}

int getanc(int x, int t) {
	for (int i = 0; i <= Maxlog; i++)
		if (t & (1 << i)) x = fa[x][i];
	return x;
}

int getlca(int x, int y) {
	if (d[x] > d[y]) x = getanc(x, d[x] - d[y]);
	if (d[x] < d[y]) y = getanc(y, d[y] - d[x]);
	if (x == y) return x;
	for (int i = Maxlog; i >= 0; i--) {
		if (fa[x][i] != fa[y][i]) {
			x = fa[x][i];
			y = fa[y][i];
		}
	}
	return fa[x][0];
}

int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		t = 0;
		std::fill(h + 1, h + n + 1, 0);
		scanf("%d", &n);
		for (int i = 1; i < n; i++) {
			int x, y, c; scanf("%d%d%d", &x, &y, &c);
			addedge(x, y, c);
		}
		buildtree(1);
		while (true) {
			char op[20];
			scanf("%s", op);
			if (!strcmp(op, "DIST")) {
				int x, y; scanf("%d%d", &x, &y);
				int l = getlca(x, y);
				printf("%d\n", s[x] + s[y] - 2 * s[l]);
			}
			else if (!strcmp(op, "KTH")) {
				int x, y, k;
				scanf("%d%d%d", &x, &y, &k);
				int l = getlca(x, y);
				int len = d[x] + d[y] - 2 * d[l];
				k--;
				if (k <= d[x] - d[l]) printf("%d\n", getanc(x, k));
				else{
					printf("%d\n", getanc(y, len - k));
				}
			}
			else break;
		}
		puts("");
	}
	return 0;
}
