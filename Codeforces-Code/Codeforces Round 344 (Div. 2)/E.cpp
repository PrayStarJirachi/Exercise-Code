#include <bits/stdc++.h>

const long long MAXN = 500001;

long long n, top, a[MAXN], base;
long long s[MAXN];
std::pair<long long, long long> z[MAXN];

void lMove(long long x, long long need, long long &left, long long &right) {
	if (x > 1 && (z[x].second - z[x - 1].second) >= need * (z[x].first - z[x - 1].first)) {
		right = x;
	} else if (x < top && (z[x].second - z[x + 1].second) >= need * (z[x].first - z[x + 1].first)) {
		left = x;
	} else left = right = x;
}

void rMove(long long x, long long need, long long &left, long long &right) {
	if (x > 1 && (z[x].second - z[x - 1].second) >= need * (z[x].first - z[x - 1].first)) {
		right = x;
	} else if (x < top && (z[x].second - z[x + 1].second >= need * (z[x].first - z[x + 1].first))) {
		left = x;
	} else left = right = x;
}

int main() {
	//freopen("E.in", "r", stdin);
	std::cin >> n;
	for (long long i = 1; i <= n; i++) {
		std::cin >> a[i];
		base += a[i] * i;
	}
	for (long long i = 1; i <= n; i++) {
		s[i] = s[i - 1] + a[i];
	}
	long long answer = 0;
	std::pair<int, int> pos = std::make_pair(0, 0);
	for (long long i = 1; i <= n; i++) {
		long long left = 1, right = top;
		while (right - left >= 2) {
			lMove(left + right >> 1, a[i], left, right);
		}
		for (long long j = left; j <= right; j++) {
			long long tmp = (s[i - 1] - z[j].second) + a[i] * (z[j].first - (i - 1));
			if (tmp > answer) {
				answer = tmp;
				pos = std::make_pair(z[j].first, i);
			}
		}
		std::pair<long long, long long> now = std::make_pair(i - 1, s[i - 1]);
		while (top > 2 && (z[top].second - z[top - 1].second) * (now.first - z[top].first) >= (now.second - z[top].second) * (z[top].first - z[top - 1].first)) {
			top--;
		}
		z[++top] = now;
	}
	top = 0;
	for (long long i = n; i >= 1; i--) {
		long long left = 1, right = top;
		while (right - left >= 2) {
			rMove(left + right >> 1, a[i], left, right);
		}
		for (long long j = left; j <= right; j++) {
			long long tmp = (s[i] - z[j].second) + a[i] * (z[j].first - i);
			if (tmp > answer) {
				answer = tmp;
				pos = std::make_pair(z[j].first, i);
			}
		}
		std::pair<long long, long long> now = std::make_pair(i, s[i]);
		while (top > 2 && (z[top].second - z[top - 1].second) * (now.first - z[top].first) <= (now.second - z[top].second) * (z[top].first - z[top - 1].first)) {
			top--;
		}
		z[++top] = now;
	}
	std::cout << answer + base << std::endl;
	return 0;
}
