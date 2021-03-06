#include <cstdio>
#include <algorithm>

const int MAXN = 111111;

int n, m, a[MAXN], b[MAXN], c[MAXN], p[MAXN];

int main() {
	freopen("B.in", "r", stdin);
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d", a + i), c[a[i]]++;
		p[a[i]] = i;
	}
	for (int i = 1; i <= m; i++) {
		scanf("%d", b + i);
		if (c[b[i]] < 1) {
			puts("Impossible");
			return 0;
		}
	}
	for (int i = 1; i <= m; i++) {
		if (c[b[i]] > 1) {
			puts("Ambiguity");
			return 0;
		}
	}
	puts("Possible");
	for (int i = 1; i <= m; i++)
		printf("%d%c", p[b[i]], " \n"[i == m]);
	return 0;
}
