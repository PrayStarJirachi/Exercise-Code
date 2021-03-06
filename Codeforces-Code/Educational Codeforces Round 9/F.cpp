#include <bits/stdc++.h>

const int MAXN = 3000;

int n, tot, f[MAXN], a[MAXN][MAXN];
std::pair<int, std::pair<int, int> > d[MAXN * MAXN];

int getfa(int x) {
	return f[x] ? f[x] = getfa(f[x]) : x;
}

int main() {
	freopen("F.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) {
			scanf("%d", &a[i][j]);
			if (i < j) {
				d[++tot] = std::make_pair(a[i][j], std::make_pair(i, j));
			}
		}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			if (a[i][j] != a[j][i] || a[i][i]) {
				return puts("NOT MAGIC"), 0;
			}
	std::sort(d + 1, d + tot + 1);
	for (int i = 1, z = 1; i <= tot; i++) {
		if (i + 1 <= tot && d[i].first == d[i + 1].first) {
			continue;
		}
		for (int j = z; j <= i; j++) {
			int fx = getfa(d[j].second.first);
			int fy = getfa(d[j].second.second);
			if (fx == fy) return puts("NOT MAGIC"), 0;
		}
		for (int j = z; j <= i; j++) {
			int fx = getfa(d[j].second.first);
			int fy = getfa(d[j].second.second);
			if (fx == fy) continue;
			f[fx] = fy;
		}
		z = i + 1;
	}
	puts("MAGIC");
	return 0;
}
