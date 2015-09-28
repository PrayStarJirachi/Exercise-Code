#include <cstdio>
#include <algorithm>

int x;

int main() {
	scanf("%d", &x);
	int answer = 0;
	for (; x; x >>= 1) {
		if (x & 1) answer++;
	}
	printf("%d\n", answer);
	return 0;
}
