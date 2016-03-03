#include <bits/stdc++.h>

const int MAXN = 600001;

int n, p[MAXN];
long long prefixCnt[MAXN][2], suffixCnt[MAXN][2];
char s[MAXN];

int main() {
	// freopen("input.txt", "r", stdin);
	std::cin >> n;
	for (int i = 1; i <= n; i++) std::cin >> p[i];
	std::cin >> s + 1;
	for (int i = 1; i <= n; i++) {
		prefixCnt[i][0] = prefixCnt[i - 1][0];
		prefixCnt[i][1] = prefixCnt[i - 1][1];
		if (s[i] == 'A') prefixCnt[i][0] += p[i];
		if (s[i] == 'B') prefixCnt[i][1] += p[i];
	}
	for (int i = n; i >= 1; i--) {
		suffixCnt[i][0] = suffixCnt[i + 1][0];
		suffixCnt[i][1] = suffixCnt[i + 1][1];
		if (s[i] == 'A') suffixCnt[i][0] += p[i];
		if (s[i] == 'B') suffixCnt[i][1] += p[i];
	}
	long long answer = 0;
	for (int i = 0; i <= n; i++) {
		answer = std::max(answer, prefixCnt[i][0] + suffixCnt[i + 1][1]);
	}
	for (int i = n + 1; i >= 1; i--) {
		answer = std::max(answer, suffixCnt[i][0] + prefixCnt[i - 1][1]);
	}
	std::cout << answer << std::endl;
	return 0;
}
