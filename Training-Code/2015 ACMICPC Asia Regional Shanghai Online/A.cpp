#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

const int MAXN = 200001;
const int MAXM = 400001;
const int MAXS = 101;
const int MAXP = 101;

struct Edge{
	int node, next;
}e[MAXM];

int n, t, tot, cs, h[MAXN], fa[MAXN], p[MAXN][MAXP], cnt[MAXN], c[MAXN], rem[MAXN][MAXS], answer[MAXN];

void addedge(int x, int y) {
	t++; e[t] = (Edge){y, h[x]}; h[x] = t;
	t++; e[t] = (Edge){x, h[y]}; h[y] = t;
}

void dfs(int x) {
	int tmp = tot++;
	for (int i = 1; i < (1 << cnt[x]); i++) {
		int now = 1;
		for (int j = 0; j < cnt[x]; j++) {
			if (i & (1 << j)) {
				now *= p[x][j];
			}
		}
		rem[x][i] = c[now]++;
	}
	for (int i = h[x]; i; i = e[i].next) {
		if (e[i].node == fa[x]) continue;
		fa[e[i].node] = x;
		dfs(e[i].node);
	}
	answer[x] = tot - tmp;
	for (int i = 1; i < (1 << cnt[x]); i++) {
		int now = 1, counter = 0;
		for (int j = 0; j < cnt[x]; j++) {
			if (i & (1 << j)) {
				now *= p[x][j];
				counter++;
			}
		}
		if (counter & 1) {
			answer[x] -= c[now] - rem[x][i];
		}
		else{
			answer[x] += c[now] - rem[x][i];
		}
	}
}

int main() {
	freopen("A.in", "r", stdin);
	while (scanf("%d", &n) == 1) {
		t = 0;
		std::fill(h + 1, h + n + 1, 0);
		for (int i = 1; i < n; i++) {
			int x, y; scanf("%d%d", &x, &y);
			addedge(x, y);
		}
		for (int i = 1; i <= n; i++) {
			int x; scanf("%d", &x);
			cnt[i] = 0;
			for (int j = 2; j * j <= x; j++) {
				if (x % j) continue;
				p[i][cnt[i]++] = j;
				while (x % j == 0) {
					x /= j;
				}
			}
			if (x > 1) {
				p[i][cnt[i]++] = x;
			}
		}
		dfs(1);
		printf("Case #%d: ", ++cs);
		for (int i = 1; i <= n; i++) {
			printf("%d%c", answer[i], " \n"[i == n]);
		}
	}
	return 0;
}
