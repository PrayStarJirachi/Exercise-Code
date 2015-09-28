#include <cstdio>
#include <queue>

int n, cur;
std::priority_queue<int> heap;

int main() {
	scanf("%d", &n);
	scanf("%d", &cur);
	for (int i = 2; i <= n; i++) {
		int x; scanf("%d", &x);
		heap.push(x);
	}
	int ans = 0;
	while (true) {
		int top = heap.top(); heap.pop();
		if (cur > top) break;
		cur++; ans++;
		heap.push(top - 1);
	}
	printf("%d\n", ans);
	return 0;
}
