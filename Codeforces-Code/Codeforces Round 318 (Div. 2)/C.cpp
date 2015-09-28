#include <cstdio>
#include <algorithm>

const int MAXN = 100001;

int n, a[MAXN];

int gcd(int a, int b) {return b ? gcd(b, a % b) : a;}

int main() {
	scanf("%d", &n);
	int g = 0;
	for (int i = 1; i <= n; i++) {
		scanf("%d", a + i);
		g = gcd(g, a[i]);
	}
	for (int i = 1; i <= n; i++) {
		a[i] /= g;
		while (a[i] & 1 ^ 1) a[i] >>= 1;
		while (a[i] % 3 == 0) a[i] /= 3;
		if (a[i] != 1) return printf("No\n"), 0;
	}
	printf("Yes\n");
	return 0;
}
