#include <cstdio>
#include <vector>
#include <algorithm>

const int MAXN = 200001;

int n, k, a[MAXN], p[MAXN];

bool cmp(const int &x, const int &y) {
	return (a[x] % 10) > (a[y] % 10);
}

int main() {
	freopen("C.in", "r", stdin);
	scanf("%d%d", &n, &k);
	int answer = 0;
	for (int i = 1; i <= n; i++) {
		scanf("%d", a + i);
		answer += a[i] / 10;
		p[i] = i;
	}
	std::sort(p + 1, p + n + 1, cmp);
	for (int i = 1; i <= n && k; i++) {
		int now = p[i];
		if (a[now] % 10 == 0) continue;
		if (k >= 10 - (a[now] % 10)) {
			answer++;
			k -= 10 - (a[now] % 10);
			a[now] += 10 - (a[now] % 10);
		}
	}
	for (int i = 1; i <= n; i++) a[i] /= 10;
	for (int i = 1; i <= n && k >= 10; i++) {
		while (k >= 10 && a[i] < 10) {
			a[i]++;
			k -= 10;
			answer++;
		}
	}
	printf("%d\n", answer);
	return 0;
}
