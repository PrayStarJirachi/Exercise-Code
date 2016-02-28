#include <bits/stdc++.h>

const int MAXN = 1001;

int n, a[MAXN];
std::map<int, int> map;

int main() {
	std::cin >> n;
	for (int i = 1; i <= n; i++) {
		std::cin >> a[i];
		map[a[i]]++;
	}
	int answer = 2;
	answer = std::max(answer, map[0] + (map[0] == 1));
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (i == j) continue;
			int p = a[i], q = a[j];
			if (p == 0 && q == 0) continue;
			static int d[MAXN], tot;
			tot = 0;
			map[p]--;
			map[q]--;
			d[++tot] = p;
			d[++tot] = q;
			for (int k = 1; k <= n; k++) {
				q = p + q;
				p = q - p;
				int counter = map[q];
				if (counter == 0) break;
				map[d[++tot] = q]--;
				answer = std::max(answer, k + 2);
			}
			for (int k = 1; k <= tot; k++) map[d[k]]++;
		}
	}
	std::cout << answer << std::endl;
	return 0;
}
