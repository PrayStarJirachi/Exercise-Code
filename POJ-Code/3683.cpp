#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

const int MAXN = 2222;
const int MAXM = 6666666;

struct Edge{
	int node, next;
}e[MAXM];

int n, t, top, tot, col, h[MAXN * 2], whe[MAXN], dfn[MAXN], low[MAXN], z[MAXN];
std::pair<std::pair<int, int>, int> s[MAXN];
bool instack[MAXN];

void addedge(int x, int y) {
	t++; e[t] = (Edge){y, h[x]}; h[x] = t;
}

int tarjan(int x) {
	low[x] = dfn[x] = ++tot;
	instack[z[++top] = x] = true;
	for (int i = h[x]; i; i = e[i].next)
		if (!dfn[e[i].node]) {
			tarjan(e[i].node);
			low[x] = std::min(low[x], low[e[i].node]);
		} else if (instack[e[i].node]) {
			low[x] = std::min(low[x], dfn[e[i].node]);
		}
	if (dfn[x] == low[x]) {
		int y;
		col++;
		do{
			instack[y = z[top--]] = false;
			whe[y] = col;
		}
		while (x != y);
	}
}

int readTime() {
	int hh, mm;
	scanf("%d:%d", &hh, &mm);
	return hh * 60 + mm;
}

void printTime(const int &data) {
	printf("%.2d:%.2d", data / 60, data % 60);
}

std::pair<int, int> getRange(int who, int dir) {
	if (dir == 0) return std::make_pair(s[who].first.first, s[who].first.first + s[who].second);
	else return std::make_pair(s[who].first.second - s[who].second, s[who].first.second);
}

bool isIntersect(const std::pair<int, int> &a, const std::pair<int, int> &b) {
	if (a.second <= b.first || a.first >= b.second) return false;
	return true;
}

int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {	
		s[i].first.first = readTime();
		s[i].first.second = readTime();
		scanf("%d", &s[i].second);
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (i == j) continue;
			if (isIntersect(getRange(i, 0), getRange(j, 0))) addedge(2 * i - 1, 2 * j);
			if (isIntersect(getRange(i, 0), getRange(j, 1))) addedge(2 * i - 1, 2 * j - 1);
			if (isIntersect(getRange(i, 1), getRange(j, 0))) addedge(2 * i, 2 * j);
			if (isIntersect(getRange(i, 1), getRange(j, 1))) addedge(2 * i, 2 * j - 1);
		}
	}
	for (int i = 1; i <= 2 * n; i++)
		if (!dfn[i]) tarjan(i);
	for (int i = 1; i <= n; i++)
		if (whe[2 * i - 1] == whe[2 * i]) {
			return puts("NO"), 0;
		}
	puts("YES");
	for (int i = 1; i <= n; i++) {
		std::pair<int, int> answer;
		if (whe[2 * i - 1] < whe[2 * i]) answer = getRange(i, 0);
		else answer = getRange(i, 1);
		printTime(answer.first);
		putchar(' ');
		printTime(answer.second);
		puts("");
	}
	return 0;
}
