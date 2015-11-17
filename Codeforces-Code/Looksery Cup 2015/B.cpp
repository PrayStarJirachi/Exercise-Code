#include <cstdio>
#include <vector>
#include <algorithm>

const int MAXN = 111;

int n, g[MAXN];
char s[MAXN][MAXN];
std::vector<int> answer;

int main() {
	freopen("B.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%s", s[i] + 1);
	}
	for (int i = 1; i <= n; i++) scanf("%d", g + i);
	while (true) {
		bool check = true;
		for (int i = 1; i <= n; i++)
			if (g[i] == 0) {
				check = false;
				break;
			}
		if (check) break;
		for (int i = 1; i <= n; i++)
			if (g[i] == 0) {
				answer.push_back(i);
				for (int j = 1; j <= n; j++) {
					g[j] -= s[i][j] - '0';
				}
				break;
			}
	}
	printf("%d\n", (int)answer.size());
	for (int i = 0; i < (int)answer.size(); i++)
		printf("%d%c", answer[i], " \n"[i == (int)answer.size() - 1]);
	return 0;
}
