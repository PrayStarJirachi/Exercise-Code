#include <cstdio>
#include <cstring>
#include <algorithm>

const int MAXN = 1001;

int n, x[MAXN], y[MAXN];

int main() {
	freopen("A.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d%d", x + i, y + i);
	if (n == 1) {
		puts("-1");
	}
	else if (n == 2) {
		if (x[1] == x[2] || y[1] == y[2]) puts("-1\n");
		else printf("%d\n", std::abs(x[1] - x[2]) * std::abs(y[1] - y[2]));
	}
	else{
		int ymax = *std::max_element(y + 1, y + n + 1);
		int ymin = *std::min_element(y + 1, y + n + 1);
		int xmax = *std::max_element(x + 1, x + n + 1);
		int xmin = *std::min_element(x + 1, x + n + 1);
		printf("%d\n", (xmax - xmin) * (ymax - ymin));
	}
	return 0;
}
