#include <cstdio>
#include <cstring>
#include <algorithm>

const int MAXN = 2000001;

int n;
long long a[MAXN], b[MAXN];

void solve(long long const *a, long long const *b, bool flag) {
	static std::pair<int, int> map[MAXN];
	static bool visit[MAXN];
	memset(visit, 0, sizeof(visit));
	map[a[0] - b[0]] = std::make_pair(0, 0);
	visit[a[0] - b[0]] = true;
	for (int i = 1; i <= n; i++) {
		int w = std::upper_bound(b, b + n + 1, a[i]) - b - 1;
		if (!visit[a[i] - b[w]]) {
			map[a[i] - b[w]] = std::make_pair(i, w);
			visit[a[i] - b[w]] = true;
			continue;
		}
		std::pair<int, int> tmp = map[a[i] - b[w]];
		if (!flag) {
			printf("%d\n", std::abs(i - tmp.first));
			for (int k = tmp.first + 1; k <= i; k++) printf("%d ", k);
			for (int k = i + 1; k <= tmp.first; k++) printf("%d ", k);
			printf("%d\n", std::abs(w - tmp.second));
			for (int k = w + 1; k <= tmp.second; k++) printf("%d ", k);
			for (int k = tmp.second + 1; k <= w; k++) printf("%d ", k);
		} else {
			printf("%d\n", std::abs(w - tmp.second));
			for (int k = w + 1; k <= tmp.second; k++) printf("%d ", k);
			for (int k = tmp.second + 1; k <= w; k++) printf("%d ", k);
			puts("");
			printf("%d\n", std::abs(i - tmp.first));
			for (int k = tmp.first + 1; k <= i; k++) printf("%d ", k);
			for (int k = i + 1; k <= tmp.first; k++) printf("%d ", k);
			puts("");
		}
		return;
	}
	
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%I64d", a + i);
		a[i] += a[i - 1];
	}
	for (int i = 1; i <= n; i++) {
		scanf("%I64d", b + i);
		b[i] += b[i - 1];
	}
	
	if (a[n] <= b[n]) {
		solve(a, b, false);
	} else {
		solve(b, a, true);
	}
	return 0;
}
