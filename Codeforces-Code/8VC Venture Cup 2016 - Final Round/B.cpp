#include <bits/stdc++.h>

const int MAXN = 210001;

int n, a[MAXN], b[MAXN];

int main() {
	// freopen("input.txt", "r", stdin);
	std::cin >> n;
	for (int i = 0, z = 0; i < n; i++) {
		int x;
		std::cin >> x;
		if (x != 0) a[x] = z++;
	}
	for (int i = 0, z = 0; i < n; i++) {
		int x;
		std::cin >> x;
		if (x != 0) b[x] = z++;
	}
	int delta = b[1] - a[1];
	for (int i = 1; i < n; i++) {
		int p = (a[i] + delta) % (n - 1);
		if (p < 0) p += n - 1;
		if (b[i] != p) {
			return puts("NO"), 0;
		}
	}
	puts("YES");
	return 0;
}
