#include <cstdio>
#include <cmath>
#include <algorithm>

const double EPS = 1e-8;
const int MAXT = 2222;
const int MAXN = 1111;

int n, d, k, t, size, c[MAXT][26], w[MAXT], answer[MAXN], q[MAXT], fail[MAXT], f[MAXT];
std::pair<std::pair<int, int>, int> pre[MAXN][MAXT];
double dp[MAXN][MAXT], p[MAXN][26];
char s[MAXN];
bool flag[MAXT];

void add(char *s) {
	int p = 1;
	for (int i = 1; i <= k; i++) {
		if (c[p][s[i] - 'a']) p = c[p][s[i] - 'a'];
		else{
			int newnode = ++size;
			c[p][s[i] - 'a'] = newnode;
			f[newnode] = p;
			w[newnode] = s[i] - 'a';
			p = newnode;
		}
	}
	flag[p] = true;
}

void buildfail() {
	int left = 0, right = 0;
	fail[1] = 0;
	for (int i = 0; i < t; i++) {
		c[0][i] = 1;
		if (c[1][i]) q[++right] = c[1][i];
	}
	while (left < right) {
		left++;
		int p = fail[f[q[left]]];
		while (!c[p][w[q[left]]]) p = fail[p];
		fail[q[left]] = c[p][w[q[left]]];
		for (int i = 0; i < t; i++)
			if (c[q[left]][i]) q[++right] = c[q[left]][i];
	}
	for (int i = 1; i <= size; i++)
		for (int j = 0; j < t; j++) {
			int p = i;
			while (!c[p][j]) p = fail[p];
			c[i][j] = c[p][j];
		}
}

int main() {
	freopen("C.in", "r", stdin);
	scanf("%d%d%d", &d, &k, &t);
	size = 1;
	for (int i = 1; i <= d; i++) {
		scanf("%s", s + 1);
		add(s);
	}
	buildfail();
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		for (int j = 0; j < t; j++) {
			scanf("%lf", &p[i][j]);
			if (p[i][j] <= 0.) p[i][j] = -1e100;
			else p[i][j] = log(p[i][j]);
		}
	for (int i = 0; i <= n; i++)
		for (int j = 1; j <= size; j++)
			dp[i][j] = -1e100;
	dp[0][1] = 0;
	for (int i = 0; i < n; i++)
		for (int j = 1; j <= size; j++) {
			if (dp[i][j] < -1e100) continue;
			for (int l = 0; l < t; l++) {
				if (i + 1 >= k && !flag[c[j][l]]) continue;
				double now = dp[i][j] + p[i + 1][l];
				if (dp[i + 1][c[j][l]] < now) {
					dp[i + 1][c[j][l]] = now;
					pre[i + 1][c[j][l]] = std::make_pair(std::make_pair(i, j), l);
				}
			}
		}
	double val = -1e100;
	std::pair<int, int> now = std::make_pair(0, 0);
	for (int i = 1; i <= size; i++)
		if (val < dp[n][i]) {
			val = dp[n][i];
			now = std::make_pair(n, i);
		}
	if (val < -1e50) return puts("---"), 0;
	for (int i = 1; i <= n; i++) {
		answer[i] = pre[now.first][now.second].second;
		now = pre[now.first][now.second].first;
	}
	std::reverse(answer + 1, answer + n + 1);
	for (int i = 1; i <= n; i++)
		putchar(answer[i] + 'a');
	puts("");
	return 0;
}
