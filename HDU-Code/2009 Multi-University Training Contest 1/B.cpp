#include <cstdio>
#include <algorithm>

const int MAXN = 40001;
const int Maxdata = 40000;

int T, fa[MAXN], s[MAXN], d[MAXN];

int getfa(int x) {
	if (fa[x] != x) {
		int g = getfa(fa[x]);
		d[x] += d[fa[x]] - 1;
		fa[x] = g;
		return g;
	}
	return x;
}

int main() {
	freopen("B.in", "r", stdin);
	scanf("%d", &T);
	std::fill(d + 1, d + Maxdata + 1, 1);
	std::fill(s + 1, s + Maxdata + 1, 1);
	for (int i = 1; i <= Maxdata; i++) fa[i] = i;
	for (int cs = 1; cs <= T; cs++) {
		char op[20];
		int x, y;
		scanf("%s", op);
		if (op[0] == 'M') {
			scanf("%d%d", &x, &y);
			x++; y++;
			int fx = getfa(x), fy = getfa(y);
			if (fx == fy) continue;
			fa[fy] = fx;
			d[fy] += s[fx];
			s[fx] += s[fy];
			s[fy] = 0;
		}
		else{
			scanf("%d", &x);
			x++;
			int fx = getfa(x);
			printf("%d\n", s[fx] - d[x]);
		}
	}
	return 0;
}
