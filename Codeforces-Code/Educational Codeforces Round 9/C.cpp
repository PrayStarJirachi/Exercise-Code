#include <bits/stdc++.h>

const int MAXN = 111111;

int n;
std::string s[MAXN];

bool cmp(const std::string &a, const std::string &b) {
	return a + b < b + a;
}

int main() {
	// freopen("input.txt", "r", stdin);
	std::cin >> n;
	for (int i = 1; i <= n; i++) {
		std::cin >> s[i];
	}
	std::sort(s + 1, s + n + 1, cmp);
	for (int i = 1; i <= n; i++) {
		std::cout << s[i];
	}
	std::cout << std::endl;
	return 0;
}
