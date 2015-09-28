#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>

const int MAXN = 100001;

int n, g, p[MAXN], c[MAXN];
bool vis[MAXN];
std::vector<int> answer;

int main() {
	scanf("%d", &n);
	for (int i = 2; i <= n; i++) {
		if (!vis[i]) p[++g] = i;
		for (int j = 1; j <= g && i * p[j] <= n; j++) {
			vis[i * p[j]] = true;
			if (i % p[j] == 0) break;
		}
	}
	for (int i = 1; i <= g; i++) {
		for (int j = 1; j <= n; j++) {
			int tmp = j, exp = 0;
			while (tmp % p[i] == 0) {
				tmp /= p[i];
				exp++;
			}
			c[i] = std::max(c[i], exp);
		}
	}
	for (int i = 1; i <= g; i++) {
		if (!c[i]) continue;
		int tmp = p[i];
		for (int j = 1; j <= c[i]; j++) {
			answer.push_back(tmp);
			tmp *= p[i];
		}
	}
	printf("%d\n", (int)answer.size());
	for (int i = 0; i < (int)answer.size(); i++) {
		printf("%d%c", answer[i], " \n"[i + 1 == (int)answer.size()]);
	}
	return 0;
}
