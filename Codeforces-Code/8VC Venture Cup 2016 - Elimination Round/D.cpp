#include <cstdio>
#include <iostream>
#include <algorithm>

const int MAXN = 10001;

int n, a[MAXN], counter[MAXN], suffix[MAXN];

int main() {
	//freopen("D.in", "r", stdin);
	std::cin >> n;
	for (int i = 1; i <= n; i++) std::cin >> a[i];
	std::sort(a + 1, a + n + 1);
	for (int i = 1; i <= n; i++)
		for (int j = i + 1; j <= n; j++)
			counter[a[j] - a[i]]++;
	for (int i = 5000; i >= 0; i--) {
		suffix[i] = suffix[i + 1] + counter[i];
	}
	long long answer = 0;
	for (int i = 0; i <= 5000; i++)
		for (int j = 0; j <= 5000; j++)
			answer += 1ll * counter[i] * counter[j] * suffix[i + j + 1];
	int total = n * (n - 1) >> 1;
	printf("%.10f\n", 1.0 * answer / total / total / total);
	return 0;
}
