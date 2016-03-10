#include <bits/stdc++.h>

int n;
std::map<int, int> gx, gy;
std::map<std::pair<int, int>, int> cnt;

int main() {
	// freopen("input.txt", "r", stdin);
	std::cin >> n;
	for (int i = 1; i <= n; i++) {
		int x, y;
		std::cin >> x >> y;
		gx[x]++;
		gy[y]++;
		cnt[std::make_pair(x, y)]++;
	}
	long long answer = 0;
	for (auto it = gx.begin(); it != gx.end(); it++) {
		answer += 1ll * (it -> second) * (it -> second - 1) >> 1;
	}
	for (auto it = gy.begin(); it != gy.end(); it++) {
		answer += 1ll * (it -> second) * (it -> second - 1) >> 1;
	}
	for (auto it = cnt.begin(); it != cnt.end(); it++) {
		answer -= 1ll * (it -> second) * (it -> second - 1) >> 1;
	}
	std::cout << answer << std::endl;
	return 0;
}
