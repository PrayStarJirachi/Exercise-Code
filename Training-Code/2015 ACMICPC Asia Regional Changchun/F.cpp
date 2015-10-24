#include <cstdio>
#include <algorithm>

const int MAXN = 200001;

int T, n, a[MAXN];
bool pred[MAXN], succ[MAXN];

bool check() {
	pred[1] = pred[0] = true;
	for (int i = 2; i <= n; i++) {
		pred[i] = pred[i - 1];
		if (a[i] < a[i - 1]) pred[i] = false;
	}
	succ[n + 1] = succ[n] = true;
	for (int i = n - 1; i >= 1; i--) {
		succ[i] = succ[i + 1];
		if (a[i] > a[i + 1]) succ[i] = false;
	}
	a[n + 1] = ~0u >> 1;
	for (int i = 1; i <= n; i++) {
		if (pred[i - 1] && succ[i + 1] && a[i - 1] <= a[i + 1]) return true;
	}
	return false;
}

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) {
			scanf("%d", a + i);
		}
		bool answer = false;
		answer |= check();
		std::reverse(a + 1, a + n + 1);
		answer |= check();
		printf("%s\n", answer ? "YES" : "NO");
	}
	return 0;
}
