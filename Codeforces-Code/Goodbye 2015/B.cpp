#include <cstdio>
#include <iostream>
#include <algorithm>

long long a, b;

long long getAns(const long long &x) {
	long long answer = 0;
	for (int i = 1; i <= 63; i++)
		for (int j = 1; j < i; j++) {
			long long p = ((1ll << i) - 1ll) ^ (1ll << j - 1);
			if (p <= x) {
				answer++;
			}
		}
	return answer;
}

int main() {
	std::cin >> a >> b;
	std::cout << getAns(b) - getAns(a - 1) << std::endl;
	return 0;
}
