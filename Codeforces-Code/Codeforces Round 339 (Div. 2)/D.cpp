#include <cstdio>
#include <iostream>
#include <algorithm>

const int MAXN = 100001;
const long long INF = 1ll << 50;

struct Node{
	long long value, pos;
	bool operator <(const Node &p)const {
		return value < p.value;
	}
}p[MAXN], a[MAXN];

bool cmp(const Node &a, const Node &b) {
	return a.pos < b.pos;
}

int n;
long long A, cf, cm, m, q[MAXN];

int main() {
	std::cin >> n >> A >> cf >> cm >> m;
	long long vmin = INF;
	for (int i = 1; i <= n; i++) {
		std::cin >> p[i].value;
		p[i].pos = i;
		vmin = std::min(vmin, p[i].value);
	}
	std::sort(p + 1, p + n + 1);
	for (int i = 1; i <= n; i++)
		q[i] = q[i - 1] + p[i].value;
	long long answer = -INF;
	std::pair<long long, long long> answerPP = std::make_pair(0, 0);
	for (long long i = 0; i <= n; i++) {
		long long base = i * A - (q[n] - q[n - i]);
		long long left = -1, right = std::min(A, vmin + m);
		if (base > m) continue;
		while (left < right) {
			long long mid = (left + right >> 1) + 1;
			int z = std::upper_bound(p + 1, p + n - i + 1, (Node){mid, INF}) - p - 1;
			if (base + z * mid - q[z] <= m) left = mid;
			else right = mid - 1;
		}
		if (answer < i * cf + left * cm) {
			answer = i * cf + left * cm;
			answerPP = std::make_pair(i, left);
		}
	}
	for (int j = 1; j <= n; j++) a[j] = p[j];
	for (int j = n - answerPP.first + 1; j <= n; j++) a[j].value = A;
	for (int j = 1; j <= n; j++) a[j].value = std::max(a[j].value, answerPP.second);
	std::sort(a + 1, a + n + 1, cmp);
	std::cout << answer << std::endl;
	for (int i = 1; i <= n; i++)
		std::cout << a[i].value << " ";
	return 0;
}
