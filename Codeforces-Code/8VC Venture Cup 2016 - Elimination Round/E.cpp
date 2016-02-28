#include <cstdio>
#include <iostream>
#include <algorithm>

const int MAXN = 210001;
const int INF = ~0u >> 2;

int n;
long long s[MAXN], a[MAXN];

int main() {
	std::cin >> n;
	for (int i = 1; i <= n; i++) {
		std::cin >> a[i];
	}
	std::sort(a + 1, a + n + 1);
	for (int i = 1; i <= n; i++) {
		s[i] = s[i - 1] + a[i];
	}
	long long answer = -INF;
	int pos = 0, len = 0;
	for (int i = 1; i <= n; i++) {
		// r = min(i - 1, n - i)
		int left = 0, right = std::min(i - 1, n - i);
		long long maxsum = -INF;
		long long maxlen = 0;
		while (right - left > 2) {
			int length = right - left + 1;
			int middle1 = left + length / 3;
			int middle2 = left + length / 3 * 2;
			long long sum1 = s[i] - s[i - 1 - middle1] + s[n] - s[n - middle1];
			long long sum2 = s[i] - s[i - 1 - middle2] + s[n] - s[n - middle2];
			if (sum1 * (2 * maxlen + 1) > maxsum * (2 * middle1 + 1)) {
				maxsum = sum1;
				maxlen = middle1;
			}
			if (sum2 * (2 * maxlen + 1) > maxsum * (2 * middle2 + 1)) {
				maxsum = sum2;
				maxlen = middle2;
			}
			if (sum1 * (2 * middle2 + 1) < sum2 * (2 * middle1 + 1)) {
				left = middle1;
			} else {
				right = middle2;
			}
		}
		for (int l = left; l <= right; l++) {
			long long sum = s[i] - s[i - 1 - l] + s[n] - s[n - l];
			if (maxsum * (2 * l + 1) < sum * (2 * maxlen + 1)) {
				maxsum = sum;
				maxlen = l;
			}
		}
		//maxsum / (2 * maxlen + 1) - a[i] > answer / (2 * len + 1) - a[pos]
		if (maxsum * (2 * len + 1) - a[i] * (2 * len + 1) * (2 * maxlen + 1) > 
		    answer * (2 * maxlen + 1) - a[pos] * (2 * len + 1) * (2 * maxlen + 1)) {
		    answer = maxsum;
		    len = maxlen;
		    pos = i;
		}
	}
	std::cout << 2 * len + 1 << std::endl;
	for (int i = pos - len; i < pos; i++) std::cout << a[i] << " ";
	std::cout << a[pos];
	for (int i = n - len + 1; i <= n; i++) std::cout << " " << a[i];
	std::cout << std::endl;
	return 0;
}
