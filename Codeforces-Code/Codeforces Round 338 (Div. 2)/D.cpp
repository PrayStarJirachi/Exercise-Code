#include <cstdio>
#include <vector>
#include <numeric>
#include <iostream>
#include <algorithm>

const double EPS = 1e-7;
const double PI = 3.1415926535897932384626;
const int MAXN = 222222;
const int MOD = 1000000007;

int n, a[MAXN], pred[MAXN], succ[MAXN];
std::vector<std::pair<int, int> > group;

int fpm(int a, long long b) {
	int ret = 1;
	for (; b; b >>= 1) {
		if (b & 1) ret = 1ll * ret * a % MOD;
		a = 1ll * a * a % MOD;
	}
	return ret;
}

int main() {
	std::cin >> n;
	for (int i = 1; i <= n; i++)
		std::cin >> a[i];
	std::sort(a + 1, a + n + 1);
	for (int i = 1; i <= n; i++) {
		int z = i;
		while (i < n && a[i] == a[i + 1]) {
			i++;
		}
		group.push_back(std::make_pair(a[i], i - z + 1));
	}
	for (int i = 0; i < group.size(); i++) {
		pred[i] = 1ll * ((i == 0) ? 1 : pred[i - 1]) * (group[i].second + 1) % (MOD - 1);
	}
	succ[group.size()] = 1;
	for (int i = (int)group.size() - 1; i >= 0; i--) {
		succ[i] = 1ll * succ[i + 1] * (group[i].second + 1) % (MOD - 1);
	}
	int answer = 1;
	for (int i = 0, size = group.size(); i < size; i++) {
		long long exp = 0;
		exp = (1ll * group[i].second * (group[i].second + 1) >> 1) % (MOD - 1);
		exp = 1ll * exp * (i == 0 ? 1 : pred[i - 1]) % (MOD - 1) * succ[i + 1] % (MOD - 1);
		answer = 1ll * answer * fpm(group[i].first, exp) % MOD;
	}
	std::cout << answer << std::endl;
	return 0;
}
