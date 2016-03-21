#include <bits/stdc++.h>

int n, a[100];

int main() {
	// freopen("input.txt", "r", stdin);
	std::cin >> n;
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	for (int i = 1; i <= n; i++)
		for (int j = i + 1; j <= n; j++)
			for (int k = j + 1; k <= n; k++) {
				if (a[i] == a[j] || a[j] == a[k] || a[k] == a[i]) continue;
				int dmax = 0;
				dmax = std::max(dmax, std::abs(a[i] - a[j]));
				dmax = std::max(dmax, std::abs(a[j] - a[k]));
				dmax = std::max(dmax, std::abs(a[i] - a[k]));
				if (dmax <= 2) {
					return puts("YES"), 0;
				}
			}
	puts("NO");
	return 0;
}
