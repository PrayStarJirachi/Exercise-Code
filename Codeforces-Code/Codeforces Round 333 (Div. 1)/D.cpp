#include <cstdio>
#include <vector>
#include <algorithm>

const int MAXN = 333333;
const int MAXM = 666666;

struct Edge{
	int node, next;
}e[MAXM];

int n, size, t, c[MAXN], child[MAXN][26], h[MAXN], f[MAXN], s[MAXN], val[MAXN];
char d[MAXN];

void addedge(int x, int y) {
	t++; e[t] = (Edge){y, h[x]}; h[x] = t;
	t++; e[t] = (Edge){x, h[y]}; h[y] = t;
}

int merge(int &x, int y) {
	if (y == 0) return x;
	if (x == 0) return y;
	s[x] = 1;
	for (int i = 0; i < 26; i++) {
		child[x][i] = merge(child[x][i], child[y][i]);
	}
	for (int i = 0; i < 26; i++) {
		s[x] += s[child[x][i]];
	}
	return x;
}

int solve(int x) {
	int now = ++size;
	s[now] = 1;
	for (int i = h[x]; i; i = e[i].next) {
		if (e[i].node == f[x]) continue;
		f[e[i].node] = x;
		child[now][d[e[i].node] - 'a'] = merge(child[now][d[e[i].node] - 'a'], solve(e[i].node));
	}
	for (int i = 0; i < 26; i++)
		s[now] += s[child[now][i]];
	val[x] = s[now];
	return now;
}

int main() {
	freopen("D.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", c + i);
	scanf("%s", d + 1);
	for (int i = 1; i < n; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		addedge(x, y);
	}
	solve(1);
	for (int i = 1; i <= n; i++) {
		val[i] += c[i];
		//printf("%d%c", val[i], " \n"[i == n]);
	}
	int valmax = *std::max_element(val + 1, val + n + 1), valcnt = 0;
	for (int i = 1; i <= n; i++)
		if (val[i] == valmax) valcnt++;
	printf("%d\n%d\n", valmax, valcnt);
	return 0;
}
