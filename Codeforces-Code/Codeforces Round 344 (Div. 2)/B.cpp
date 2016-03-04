#include <bits/stdc++.h>

const int MAXN = 5101;

int n, m, k;
std::vector<std::pair<int, int> > r[MAXN], c[MAXN];

int main() {
	// freopen("input.txt", "r", stdin);
	std::cin >> n >> m >> k;
	for (int i = 1; i <= k; i++) {
		int op, x, value;
		std::cin >> op >> x >> value;
		if (op == 1) {
			r[x].push_back(std::make_pair(i, value));
		} else {
			c[x].push_back(std::make_pair(i, value));
		}
	}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			std::pair<int, int> lastC = std::make_pair(0, 0);
			std::pair<int, int> lastR = std::make_pair(0, 0);
			if ((int)r[i].size() > 0) lastC = *(--r[i].end());
			if ((int)c[j].size() > 0) lastR = *(--c[j].end());
			if (lastC < lastR) printf("%d", lastR.second);
			else printf("%d", lastC.second);
			printf("%c", " \n"[j == m]);
		}
	return 0;
}
