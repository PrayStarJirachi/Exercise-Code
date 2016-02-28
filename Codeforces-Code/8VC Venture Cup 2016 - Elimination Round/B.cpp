#include <cstdio>
#include <numeric>
#include <iostream>
#include <algorithm>

const double EPS = 1e-7;
const double PI = 3.1415926535897932384626;

const int MAXN = 201;

int n, cnt[3];
char s[MAXN];
bool vis[3];

void dfs(int B, int G, int R) {
	if (B + G + R == 1) {
		if (B) vis[0] = true;
		if (G) vis[1] = true;
		if (R) vis[2] = true;
		return;
	}
	if (B >= 2) dfs(B - 1, G, R);
	if (G >= 2) dfs(B, G - 1, R);
	if (R >= 2) dfs(B, G, R - 1);
	if (B && G) dfs(B - 1, G - 1, R + 1);
	if (B && R) dfs(B - 1, G + 1, R - 1);
	if (G && R) dfs(B + 1, G - 1, R - 1);
}

int main() {
	// freopen("input.txt", "r", stdin);
	std::cin >> n >> s + 1;
	for (int i = 1; i <= n; i++) {
		if (s[i] == 'B') cnt[0]++;
		if (s[i] == 'G') cnt[1]++;
		if (s[i] == 'R') cnt[2]++;
	}
	cnt[0] = std::min(cnt[0], 2);
	cnt[1] = std::min(cnt[1], 2);
	cnt[2] = std::min(cnt[2], 2);
	dfs(cnt[0], cnt[1], cnt[2]);
	if (vis[0]) putchar('B');
	if (vis[1]) putchar('G');
	if (vis[2]) putchar('R');
	puts("");
	return 0;
}
