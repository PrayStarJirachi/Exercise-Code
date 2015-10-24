#include <cstdio>
#include <iostream>
#include <algorithm>

const int MAXK = 201;

int T, n;
// 0 + 1 + 8
unsigned long long fpm[MAXK];
unsigned long long getValue(int p, int k) {
	unsigned long long ret = 0;
	fpm[0] = 1;
	for (int i = 1; i <= k; i++) fpm[i] = fpm[i - 1] * p;
	//bret = fpm[k] * 2 - 1;
	for (int i = 0; i <= k; i++) {
		unsigned long long tmp = 1;
		tmp = tmp * (fpm[k - i] - fpm[k - 1 - i]);
		tmp = tmp * fpm[i];
		ret += tmp;
	}
	//std::cout << fpm[k] << " " << ret << std::endl;
	return ret;
}

unsigned long long G(int p, int k) {
	unsigned long long ret = 0;
	for (int i = 0; i <= k; i++)
		ret += getValue(p, i);
	return ret;
}

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		unsigned long long answer = 0, tmp = 1;
		for (int i = 1; i * i <= n; i++) {
			if (n % i) continue;
			answer += (unsigned long long)i * i;
			if (i * i != n) {
				answer += (unsigned long long)(n / i) * (n / i);
			}
		}
		for (int i = 2; i * i <= n; i++) {
			if (n % i) continue;
			int exp = 0;
			while (n % i == 0) {
				n /= i;
				exp++;
			}
			tmp = tmp * G(i, exp);
		}
		if (n > 1) {
			tmp = tmp * G(n, 1);
		}
		std::cout << answer - tmp << std::endl;
	}
	return 0;
}
