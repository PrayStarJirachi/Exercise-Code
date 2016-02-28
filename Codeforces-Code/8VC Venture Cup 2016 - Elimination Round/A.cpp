#include <cstdio>
#include <numeric>
#include <iostream>
#include <algorithm>

const double EPS = 1e-7;
const double PI = 3.1415926535897932384626;

const int MAXN = 211;

int n;
char s[MAXN];
std::pair<int, int> qsum[MAXN];

int main() {
	// freopen("input.txt", "r", stdin);
	std::cin >> n >> s + 1;
	for (int i = 1; i <= n; i++) {
		switch (s[i]) {
			case 'U':
				qsum[i] = std::make_pair(qsum[i - 1].first, qsum[i - 1].second - 1);
				break;
			case 'L':
				qsum[i] = std::make_pair(qsum[i - 1].first - 1, qsum[i - 1].second);
				break;
			case 'D':
				qsum[i] = std::make_pair(qsum[i - 1].first, qsum[i - 1].second + 1);
				break;
			case 'R':
				qsum[i] = std::make_pair(qsum[i - 1].first + 1, qsum[i - 1].second);
				break;
		}
	}
	int answer = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < i; j++) {
			std::pair<int, int> tmp = std::make_pair(qsum[i].first - qsum[j].first, qsum[i].second - qsum[j].second);
			if (tmp == std::make_pair(0, 0)) {
				answer++;
			}
		}
	}
	std::cout << answer << std::endl;
	return 0;
}
