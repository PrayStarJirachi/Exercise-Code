#include <cstdio>
#include <algorithm>

const int MAXN = 200001;

struct People{
	long long m, s;
	bool operator <(const People &p)const {
		return m < p.m;
	}
}p[MAXN];

int n;
long long d, s[MAXN];

int main() {
	scanf("%d%I64d", &n, &d); d--;
	for (int i = 1; i <= n; i++) {
		scanf("%I64d%I64d", &p[i].m, &p[i].s);
	}
	std::sort(p + 1, p + n + 1);
	for (int i = 1; i <= n; i++) {
		s[i] = s[i - 1] + p[i].s;
	}
	long long answer = 0;
	for (int i = 1; i <= n; i++) {
		int pos = std::upper_bound(p + 1, p + n + 1, (People){p[i].m + d}) - p - 1;
		answer = std::max(answer, s[pos] - s[i - 1]);
	}
	printf("%I64d\n", answer);
	return 0;
}
