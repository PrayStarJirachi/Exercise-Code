#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <iostream>

const int MAXN = 1001;

int n, answer[MAXN];
std::priority_queue<std::pair<int, std::pair<int, int> > > heap;

int main() {
	scanf("%d", &n);
	for (int i = 2; i <= 2 * n; i++) {
		for (int j = 1; j < i; j++) {
			int x; scanf("%d", &x);
			heap.push(std::make_pair(x, std::make_pair(i, j)));
		}
	}
	while (!heap.empty()) {
		std::pair<int, std::pair<int, int> > top = heap.top();
		heap.pop();
		if (answer[top.second.first] || answer[top.second.second]) continue;
		answer[top.second.first] = top.second.second;
		answer[top.second.second] = top.second.first;
	}
	for (int i = 1; i <= 2 * n; i++) printf("%d%c", answer[i], " \n"[i == 2 * n]);
	return 0;
}
