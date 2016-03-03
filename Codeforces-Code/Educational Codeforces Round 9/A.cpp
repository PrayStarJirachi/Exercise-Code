#include <bits/stdc++.h>

const int MAXN = 10001;

int n, p;
std::string s[MAXN];

int main() {
	// freopen("input.txt", "r", stdin);
	std::cin >> n >> p;
	for (int i = 1; i <= n; i++) {
		std::cin >> s[i];
	}
	long long answer = 0, a = 0;
	for (int i = n; i >= 1; i--) {
		if (s[i] == "halfplus") {
			a = a * 2 + 1;
			answer += 1ll * (a >> 1) * p + p / 2;
		} else {
			a = a * 2;
			answer += 1ll * (a >> 1) * p;
		}
	}
	std::cout << answer << std::endl;
	return 0;
}
