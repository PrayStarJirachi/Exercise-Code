#include <cstdio>
#include <algorithm>

const int Maxlog = 20;
const int MAXN = 333333;
const int MAXM = 666666;
const int MAXQ = 999999;
const int INF = ~0u >> 2;

struct Edge{
	int node, next, dist;
}e[MAXM];

int n, t, m, tot, h[MAXN], fa[MAXN][21], f[MAXN], dep[MAXN], d[MAXN], answer[MAXN], p[MAXN], r[MAXN], b[MAXN];
bool flag[MAXN];
std::pair<int, int> o[MAXN];

void addedge(int x, int y, int c) {
	t++; e[t] = (Edge){y, h[x], c}; h[x] = t;
	t++; e[t] = (Edge){x, h[y], c}; h[y] = t;
}

void dfs(int x) {
	o[x].first = ++tot;
	for (int i = h[x]; i; i = e[i].next) {
		if (e[i].node == fa[x][0]) continue;
		fa[e[i].node][0] = x;
		dep[e[i].node] = dep[x] + 1;
		dfs(e[i].node);
	}
	o[x].second = tot;
}

bool cmp(const int &a, const int &b) {
	return o[a].first < o[b].first;
}

int getAnc(int x, int t) {
	for (int i = 0; i <= Maxlog; i++)
		if (t & (1 << i)) x = fa[x][i];
	return x;
}

int getLca(int x, int y) {
	if (dep[x] > dep[y]) x = getAnc(x, dep[x] - dep[y]);
	if (dep[x] < dep[y]) y = getAnc(y, dep[y] - dep[x]);
	if (x == y) return x;
	for (int i = Maxlog; i >= 0; i--)
		if (fa[x][i] != fa[y][i]) {
			x = fa[x][i];
			y = fa[y][i];
		}
	return fa[x][0];
}

int main() {
	freopen("A.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i < n; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		addedge(x, y, 0);
	}
	dfs(1);
	for (int j = 1; j <= Maxlog; j++)
		for (int i = 1; i <= n; i++)
			fa[i][j] = fa[fa[i][j - 1]][j - 1];
	std::fill(h + 1, h + n + 1, 0);
	scanf("%d", &m);
	for (int cs = 1; cs <= m; cs++) {
		int tmp, cnt = 0, top = 0;
		static int z[MAXN], q[MAXQ];
		static bool v[MAXN];
		scanf("%d", &tmp);
		for (int i = 1; i <= tmp; i++) {
			scanf("%d", r + i);
			flag[p[++cnt] = r[i]] = true;
		}
		std::sort(p + 1, p + cnt + 1, cmp);
		for (int i = 2, size = cnt; i <= size; i++) {
			int now = getLca(p[i - 1], p[i]);
			if (!flag[now]) flag[p[++cnt] = now] = true;
		}
		std::sort(p + 1, p + cnt + 1, cmp);
		z[++top] = p[1];
		for (int i = 2; i <= cnt; i++) {
			while (o[p[i]].first < o[z[top]].first || o[p[i]].first > o[z[top]].second) top--;
			f[p[i]] = z[top];
			addedge(z[top], p[i], dep[p[i]] - dep[z[top]]);
			z[++top] = p[i];
		}
		int left = 0, right = 0;
		for (int i = 1; i <= cnt; i++) d[p[i]] = INF;
		for (int i = 1; i <= tmp; i++) {
			v[q[++right] = r[i]] = true;
			b[r[i]] = r[i];
			d[r[i]] = 0;
		}
		while (left < right) {
			left++;
			for (int i = h[q[left]]; i; i = e[i].next) {
				if (d[e[i].node] > d[q[left]] + e[i].dist || (d[e[i].node] == d[q[left]] + e[i].dist && b[e[i].node] > b[q[left]])) {
					d[e[i].node] = d[q[left]] + e[i].dist;
					b[e[i].node] = b[q[left]];
					if (!v[e[i].node]) v[q[++right] = e[i].node] = true;
				}
			}
			v[q[left]] = false;
		}
		for (int i = 1; i <= cnt; i++) {
			int now = p[i];
			answer[b[now]] += o[now].second - o[now].first + 1;
			for (int j = h[now]; j; j = e[j].next) {
				if (e[j].node == f[now]) continue;
				int tmp = getAnc(e[j].node, dep[e[j].node] - dep[now] - 1);
				answer[b[now]] -= o[tmp].second - o[tmp].first + 1;
			}
			if (!f[now]) answer[b[now]] += n - (o[now].second - o[now].first + 1);
		}
		for (int i = 1; i <= cnt; i++) {
			int now = p[i];
			if (!f[now]) continue;
			int sec = getAnc(now, dep[now] - dep[f[now]] - 1);
			if (b[now] == b[f[now]]) {
				answer[b[now]] += o[sec].second - o[sec].first + 1;
				answer[b[now]] -= o[now].second - o[now].first + 1;
			}
			else{
				int A = d[now], B = d[f[now]] + dep[now] - dep[f[now]], anc;
				if (b[now] > b[f[now]]) anc = getAnc(now, (B - A) / 2 - ((B - A) & 1 ^ 1));
				else anc = getAnc(now, (B - A) / 2);
				answer[b[now]] += o[anc].second - o[anc].first + 1;
				answer[b[now]] -= o[now].second - o[now].first + 1;
				answer[b[f[now]]] += o[sec].second - o[sec].first + 1;
				answer[b[f[now]]] -= o[anc].second - o[anc].first + 1;
			}
		}
		for (int i = 1; i <= tmp; i++) {
			printf("%d ", answer[r[i]]);
		}
		puts("");
		t = 0;
		for (int i = 1; i <= cnt; i++) {
			h[p[i]] = f[p[i]] = b[p[i]] = 0;
			answer[p[i]] = 0;
			flag[p[i]] = false;
		}
	}
	return 0;
}
