#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>

const int MOD = 1000000007;
const int INF = ~0u >> 2;

class BearCavalry{
public:
	int countAssignments(std::vector<int> warriors, std::vector<int> horses);
}T;

int BearCavalry::countAssignments(std::vector<int> warriors, std::vector<int> horses) {
	int n = warriors.size(), tmp = warriors[0];
	warriors[0] = INF;
	std::sort(horses.begin(), horses.end());
	std::sort(warriors.rbegin(), warriors.rend());
	warriors[0] = tmp;
	int answer = 0;
	for (int i = 0; i < n; i++) {
		int tmp = horses[i] * warriors[0], counter = 1;
		for (int j = 1; j < n; j++) {
			int now = (tmp % warriors[j] == 0) ? (tmp / warriors[j] - 1) : (tmp / warriors[j]);
			now = std::upper_bound(horses.begin(), horses.end(), now) - horses.begin() - 1;
			if (now >= i) now--;
			counter = 1ll * counter * std::max(0, now + 1 - (j - 1)) % MOD;
		}
		answer = (answer + counter) % MOD;
	}
	return answer;
}

int n;
std::vector<int> warriors, horses;

int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		int x; scanf("%d", &x);
		warriors.push_back(x);
	}
	for (int i = 1; i <= n; i++) {
		int x; scanf("%d", &x);
		horses.push_back(x);
	}
	printf("%d\n", T.countAssignments(warriors, horses));
	return 0;
}
