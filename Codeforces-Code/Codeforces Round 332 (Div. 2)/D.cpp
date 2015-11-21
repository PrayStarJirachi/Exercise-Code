#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

long long a;
std::vector<std::pair<long long, long long> > answer;

int main() {
	//freopen("D.in", "r", stdin);
	std::cin >> a;
	for (long long n = 1; (2 * n + 1) * n * (n + 1) <= 6 * a; n++) {
		if (6 * a % (n * (n + 1))) continue;
		long long m = 6 * a / n / (n + 1);
		m += (n - 1);
		if (m % 3) continue;
		m /= 3;
		answer.push_back(std::make_pair(n, m));
		if (n != m) answer.push_back(std::make_pair(m, n));
	}
	std::sort(answer.begin(), answer.end());
	answer.erase(std::unique(answer.begin(), answer.end()), answer.end());
	printf("%d\n", (int)answer.size());
	for (int i = 0; i < (int)answer.size(); i++) {
		std::cout << answer[i].first << " " << answer[i].second << std::endl;
	}
	return 0;
}
