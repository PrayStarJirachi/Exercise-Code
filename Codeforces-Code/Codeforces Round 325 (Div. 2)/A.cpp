#include <cstdio>
#include <algorithm>

const int MAXN = 10001;

int n, a[MAXN];

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", a + i);
	}
	for (int i = 1; i <= n; i++) {
		if (a[i] == 0 && a[i - 1] == 1 && a[i + 1] == 1) {
			a[i] = 1;
		}
	}
	int counter = 0;
	for (int i = 1; i <= n; i++)
		counter += a[i];
	printf("%d\n", counter);
	return 0;
}
