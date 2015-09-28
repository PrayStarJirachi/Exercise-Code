#include <cstdio>
#include <algorithm>

const int MAXN = 10;

int n, a[MAXN];

int main() {
	//freopen("A.in", "r", stdin);
	//scanf("%d", &n);
	n = 2;
	for (int i = 1; i <= 2; i++) {
		scanf("%d", a + i);
	}
	int zmin = *std::min_element(a + 1, a + n + 1);
	int zmax = *std::max_element(a + 1, a + n + 1);
	printf("%d %d\n", zmin, zmax - zmin >> 1);
	return 0;
}
