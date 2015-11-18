#include <cstdio>
#include <algorithm>

const int MAXN = 222222;

int n, a[MAXN], b[MAXN];

int main() {
	freopen("G.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", a + i);
		a[i] += i;
	}
	std::sort(a + 1, a + n + 1);
	for (int i = 1; i <= n; i++) b[i] = (a[i] -= i);
	std::sort(b + 1, b + n + 1);
	for (int i = 1; i <= n; i++)
		if (a[i] != b[i]) {
			puts(":(");
			return 0;
		}
	for (int i = 1; i <= n; i++)
		printf("%d%c", a[i], " \n"[i == n]);
	return 0;
}
