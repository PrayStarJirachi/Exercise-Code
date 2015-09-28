#include <cstdio>
#include <algorithm>

const int MAXN = 100001;

int n, a[MAXN], answer[MAXN];

int main() {
	//freopen("B.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	int zmax = 0;
	for (int i = n; i >= 1; i--) {
		answer[i] = std::max(0, zmax + 1 - a[i]);
		zmax = std::max(zmax, a[i]);
	}
	for (int i = 1; i <= n; i++) {
		printf("%d%c", answer[i], " \n"[i == n]);
	}
	return 0;
}
