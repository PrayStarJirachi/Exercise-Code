#include <bits/stdc++.h>

const int MAXN = 2000001;

int n, m, a[MAXN], b[MAXN], answer[MAXN];

long long gcd(const long long &a, const long long &b) {
	return b ? gcd(b, a % b) : a;
}

int main() {
	freopen("D.in", "r", stdin);
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d", a + i);
		b[i] = a[i];
	}
	std::sort(a + 1, a + n + 1);
	for (int i = 1; i <= m; i++) {
		int tmp = std::upper_bound(a + 1, a + n + 1, i) - std::lower_bound(a + 1, a + n + 1, i);
		for (int j = i; j <= m; j += i)
			answer[j] += tmp;
	}
	int cmax = 0, cpos = 1;
	for (int i = 1; i <= m; i++) {
		if (cmax < answer[i]) {
			cpos = i;
			cmax = answer[i];
		}
	}
	long long lcm = 1;
	for (int i = 1; i <= n; i++) {
		if (cpos % b[i] == 0) {
			lcm = 1ll * b[i] * lcm / gcd(b[i], lcm);
		}
	}
	std::cout << lcm << " " << cmax << std::endl;
	for (int i = 1; i <= n; i++) {
		if (cpos % b[i] == 0) {
			std::cout << i << " ";
		}
	}
	std::cout << std::endl;
	return 0;
} 
