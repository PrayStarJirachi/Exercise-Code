#include <bits/stdc++.h>

int n;

int main() {
	//freopen("B.in", "r", stdin);
	std::cin >> n;
	static std::vector<int> answer;
	answer.clear();
	int cnt = 0;
	for (int i = 1; cnt <= n; i++) {
		int tmp = i;
		while (tmp % 5 == 0) {
			tmp /= 5;
			cnt++;
		}
		if (cnt == n) {
			answer.push_back(i);
		}
	}
	std::cout << answer.size() << std::endl;
	for (auto it = answer.begin(); it != answer.end(); it++) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
	return 0;
}
