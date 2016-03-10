#include <bits/stdc++.h>

const int MAXN = 510001;
const long long INF = 1ll << 50;

int n, a, b, t;
long long c[MAXN];
char s[MAXN];

long long check(const int &answer) {
	long long ret = INF;
	ret = std::min(ret, c[answer] + 1ll * (answer - 1) * a);
	ret = std::min(ret, c[n] - c[n - answer + 1] + c[1] + 1ll * (answer - 1) * a);
	for (int i = 1; i < answer; i++) {
		long long tmp = c[i] + 2ll * (i - 1) * a;
		long long rem = answer - i;
		tmp += c[n] - c[n - rem] + 1ll * rem * a;
		ret = std::min(ret, tmp);
	}
	for (int i = 2; i < answer; i++) {
		long long tmp = c[n] - c[n - i + 1] + c[1] + 2ll * (i - 1) * a;
		long long rem = answer - i;
		tmp += c[rem + 1] - c[1] + 1ll * rem * a;
		ret = std::min(ret, tmp);
	}
	return ret;
}

int main() {
	freopen("B.in", "r", stdin);
	std::cin >> n >> a >> b >> t;
	std::cin >> s + 1;
	for (int i = 1; i <= n; i++) {
		c[i] = c[i - 1] + 1;
		if (s[i] == 'w') c[i] += b;
	}
	int left = 0, right = n;
	while (left < right) {
		int middle = (left + right >> 1) + 1;
		if (check(middle) <= t) left = middle;
		else right = middle - 1;
	}
	std::cout << left << std::endl;
	return 0;
}
