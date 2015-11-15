#include <cstdio>
#include <cstring>
#include <algorithm>

const int MAXN = 22222;

int T, n, q, t, cnt, c[MAXN], last[MAXN], defend[MAXN];
std::pair<int, int> inteval[MAXN];

void add(int x, int d) {
	for (int i = x; i <= n; i += i & -i) {
		c[i] += d;
	}
}

int sum(int x) {
	int ret = 0;
	for (int i = x; i; i -= i & -i) {
		ret += c[i];
	}
	return ret;
}

int main() {
	freopen("A.in", "r", stdin);
	scanf("%d", &T);
	for (int cs = 1; cs <= T; cs++) {
		cnt = 0;
		scanf("%d%d%d", &n, &q, &t);
		for (int i = 1; i <= n; i++) {
			last[i] = 1 - t;
			defend[i] = c[i] = 0;
		}
		printf("Case %d:\n", cs);
		for (int i = 1; i <= q; i++) {
			char op[20];
			int x, y;
			scanf("%s", op);
			if (!strcmp(op, "Attack")) {
				scanf("%d%d", &x, &y);
				inteval[++cnt] = std::make_pair(x, y);
				add(x, 1);
				add(y + 1, -1);
			}
			else if (!strcmp(op, "Query")) {
				scanf("%d", &x);
				for (int i = last[x] + t; i <= cnt; ) {
					if (inteval[i].first <= x && x <= inteval[i].second) {
						last[x] = i;
						defend[x]++;
						i += t;
					}
					else i++;
				}
				printf("%d\n", sum(x) - defend[x]);
			}
		}
	}
	return 0;
}
