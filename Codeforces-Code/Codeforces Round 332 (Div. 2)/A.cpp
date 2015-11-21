#include <cstdio>
#include <algorithm>

const int INF = ~0u >> 1;

int a, b, c;

int main() {
	scanf("%d%d%d", &a, &b, &c);
	int answer = INF;
	answer = std::min(answer, a + b << 1);
	answer = std::min(answer, b + c << 1);
	answer = std::min(answer, a + c << 1);
	answer = std::min(answer, a + b + c);
	printf("%d\n", answer);
	return 0;
}
