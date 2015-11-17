#include <cstdio>
#include <cstring>

const int MAXN = 111;
const int dirX[] = {0, 0, 1, 1};
const int dirY[] = {0, 1, 0, 1};

int n, m;
char s[MAXN][MAXN];

int main() {
	freopen("A.in", "r", stdin);
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%s", s[i] + 1);
	int answer = 0;
	for (int i = 1; i < n; i++)
		for (int j = 1; j < m; j++) {
			bool F = false, A = false, C = false, E = false;
			for (int k = 0; k < 4; k++) {
				if (s[i + dirX[k]][j + dirY[k]] == 'f') F = true;
				if (s[i + dirX[k]][j + dirY[k]] == 'a') A = true;
				if (s[i + dirX[k]][j + dirY[k]] == 'c') C = true;
				if (s[i + dirX[k]][j + dirY[k]] == 'e') E = true;
			}
			answer += F && A && C && E;
		}
	printf("%d\n", answer);
	return 0;
}
