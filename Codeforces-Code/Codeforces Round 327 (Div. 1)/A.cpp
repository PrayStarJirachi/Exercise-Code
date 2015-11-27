#include <cstdio>
#include <algorithm>

const int MAXN = 555555;

int n, answer, a[MAXN];

int main() {
	freopen("A.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	for (int i = 2, last = 0; i <= n + 1; i++) {
		if (i == n + 1 || a[i] == a[i - 1]) {
			if (last != 0) {
				if ((i - last) & 1) {
					for (int j = last; j < i; j++) a[j] = a[last];
					answer = std::max(answer, (i - last >> 1));
				} else {
					int len = i - last >> 1;
					for (int j = last; j <= last + len - 1; j++) a[j] = a[last];
					for (int j = last + len; j < i; j++) a[j] = a[i - 1];
					answer = std::max(answer, (i - last >> 1) - 1);
				}
			}
			last = 0;
		} else if (last == 0) last = i - 1;
	}
	printf("%d\n", answer);
	for (int i = 1; i <= n; i++)
		printf("%d%c", a[i], " \n"[i == n]);
	return 0;
}
