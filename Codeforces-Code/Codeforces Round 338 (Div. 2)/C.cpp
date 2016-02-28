#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <string>

const int MAXL = 2222;

int n, m, lcp[2][MAXL][MAXL];
char s[MAXL], t[MAXL], r[MAXL];

int main() {
	std::cin >> s + 1 >> t + 1;
	n = strlen(s + 1);
	m = strlen(t + 1);
	for (int i = 1; i <= n; i++) r[i] = s[n - i + 1];
	for (int i = n; i >= 1; i--)
		for (int j = 1; j <= m; j++)
			if (s[i] == t[j]) {
				lcp[0][i][j] = lcp[0][i + 1][j + 1] + 1;
			}
	for (int i = n; i >= 1; i--)
		for (int j = 1; j <= m; j++)
			if (r[i] == t[j]) {
				lcp[1][i][j] = lcp[1][i + 1][j + 1] + 1;
			}
	static std::vector<std::pair<int, int> > answer;
	for (int i = 1; i <= m;) {
		int maxlen = 0;
		std::pair<int, int> substr;
		for (int j = 1; j <= n; j++)
			if (maxlen < lcp[0][j][i]) {
				maxlen = lcp[0][j][i];
				substr = std::make_pair(j, j + maxlen - 1);
			}
		for (int j = 1; j <= m; j++)
			if (maxlen < lcp[1][j][i]) {
				maxlen = lcp[1][j][i];
				substr = std::make_pair(n - j + 1, n - (j + maxlen - 1) + 1);
			}
		if (maxlen == 0) return std::cout << -1 << std::endl, 0;
		i += maxlen;
		answer.push_back(substr);
	}
	std::cout << answer.size() << std::endl;
	for (int i = 0; i < (int)answer.size(); i++) {
		std::cout << answer[i].first << " " << answer[i].second << std::endl;
	}
	return 0;
}
