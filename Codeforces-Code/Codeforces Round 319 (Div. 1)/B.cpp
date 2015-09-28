#include <cstdio>
#include <algorithm>

const int MAXN = 100001;

int n, p[MAXN];
bool v[MAXN];

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", p + i);
	}
	bool check = false, haveone = false;
	std::pair<int, int> base;
	for (int i = 1; i <= n; i++) {
		if (v[i]) continue;
		int cnt = 1; v[i] = true;
		for (int j = p[i]; j != i; j = p[j]) {
			cnt++;
			v[j] = true;
		}
		if (cnt == 1) {
			printf("YES\n");
			for (int k = 1; k <= n; k++) {
				if (k != i) printf("%d %d\n", k, i);
			}
			return 0;
		}
		if (cnt == 2) {
			base = std::make_pair(i, p[i]);
			check = true;
		}
		if (cnt & 1) haveone = true;
	}
	if (!check || haveone) return printf("NO\n"), 0;
	printf("YES\n");
	printf("%d %d\n", base.first, base.second);
	std::fill(v + 1, v + n + 1, false);
	v[base.first] = v[base.second] = true;
	for (int i = 1; i <= n; i++) {
		if (v[i]) continue;
		int cnt = 1; v[i] = true;
		printf("%d %d\n", base.first, i);
		for (int j = p[i]; j != i; j = p[j]) {
			cnt++;
			if (cnt & 1) printf("%d %d\n", base.first, j);
			else printf("%d %d\n", base.second, j);
			v[j] = true;
		}
	}
	return 0;
}
