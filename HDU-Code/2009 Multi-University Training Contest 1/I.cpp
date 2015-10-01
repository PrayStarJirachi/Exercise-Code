#include <cstdio>
#include <cstring>
#include <algorithm>

const int mod = 20090717;
const int MAXT = 501;
const int MAXL = 101;
const int MAXS = 2001;
const int MAXC = 1001;

int n, m, k, size, c[MAXT][26], dp[MAXL][MAXT][MAXS], f[MAXT], fail[MAXT], d[MAXT], state[MAXT];
char s[MAXC];

int alloc() {
	size++;
	std::fill(c[size], c[size] + 26, 0);
	f[size] = fail[size] = d[size] = state[size] = 0;
	return size;
}

void insert(char *s, int pos) {
	int len = strlen(s + 1), p = 1;
	for (int i = 1; i <= len; i++) {
		if (c[p][s[i] - 'a']) p = c[p][s[i] - 'a'];
		else{
			int newnode = alloc();
			c[p][s[i] - 'a'] = newnode;
			d[newnode] = s[i] - 'a';
			f[newnode] = p;
			p = newnode;
		}
	}
	state[p] |= 1 << pos - 1;
}

void buildfail() {
	static int q[MAXT];
	int left = 0, right = 0;
	fail[1] = 0;
	for (int i = 0; i < 26; i++) {
		c[0][i] = 1;
		if (c[1][i]) q[++right] = c[1][i];
	}
	while (left < right) {
		left++;
		int p = fail[f[q[left]]];
		while (!c[p][d[q[left]]]) p = fail[p];
		fail[q[left]] = c[p][d[q[left]]];
		state[q[left]] |= state[fail[q[left]]];
		for (int i = 0; i < 26; i++) {
			if (c[q[left]][i]) {
				q[++right] = c[q[left]][i];
			}
		}
	}
	for (int i = 1; i <= size; i++)
		for (int j = 0; j < 26; j++) {
			int p = i;
			while (!c[p][j]) p = fail[p];
			c[i][j] = c[p][j];
		}
}

void update(int &x, const int &y) {
	x += y;
	if (x >= mod) x -= mod;
}

int main() {
	freopen("I.in", "r", stdin);
	while (scanf("%d%d%d", &n, &m, &k) == 3) {
		if (n == 0 && m == 0 && k == 0) continue;
		size = 0;
		alloc();
		for (int i = 1; i <= m; i++) {
			scanf("%s", s + 1);
			insert(s, i);
		}
		buildfail();
		for (int i = 0; i <= n; i++)
			for (int j = 1; j <= size; j++)
				for (int l = 0; l < (1 << m); l++) {
					dp[i][j][l] = 0;
				}
		dp[0][1][0] = 1;
		for (int i = 0; i < n; i++) {
			for (int j = 1; j <= size; j++) {
				for (int l = 0; l < (1 << m); l++) {
					if (!dp[i][j][l]) continue;
					for (int p = 0; p < 26; p++) {
						update(dp[i + 1][c[j][p]][l | state[c[j][p]]], dp[i][j][l]);
					}
				}
			}
		}
		int answer = 0;
		for (int s = 0; s < (1 << m); s++) {
			int counter = 0;
			for (int i = 1; i <= m; i++)
				if (s & (1 << i - 1)) counter++;
			if (counter >= k) {
				for (int w = 1; w <= size; w++) {
					update(answer, dp[n][w][s]);
				}
			}
		}
		printf("%d\n", answer);
	}
	return 0;
}
