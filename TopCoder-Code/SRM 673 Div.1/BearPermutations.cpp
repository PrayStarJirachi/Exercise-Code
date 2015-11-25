#include <cstdio>
#include <algorithm>

const int MAXN = 111;
const int MAXS = 111;

class BearPermutations{
public:
	int countPermutations(int n, int s, int mod);
}T;

int n, s, mod, C[MAXN][MAXN], dp[MAXN][MAXN][MAXS], f[MAXN + MAXS];
bool v[MAXN][MAXN][MAXS];

int BearPermutations::countPermutations(int n, int s, int mod) {
	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= i; j++)
			if (i == 0 && j == 0) C[i][j] = 1;
			else if (j == 0) C[i][j] = C[i - 1][j];
			else C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
	dp[1][1][0] = 1;
	for (int i = 2; i <= n; i++)
		for (int j = 1; j <= i; j++)
			for (int k = 0; k <= s; k++) {
				if (j > (i + 1 >> 1)) {
					dp[i][j][k] = dp[i][i - j + 1][k];
					continue;
				}
				if (j == 1) {
					for (int p = 2; p <= i; p++) {
						dp[i][j][k] += dp[i - 1][p - 1][k];
						if (dp[i][j][k] >= mod) dp[i][j][k] -= mod;
					}
				} else {
					std::fill(f, f + i + s, 0);
					for (int p = 1; p <= i - 1; p++)
						for (int q = 0; q <= s; q++) {
							f[p + q] += dp[i - j][p][q];
							if (f[p + q] >= mod) f[p + q] -= mod;
						}
					for (int p = 1; p <= j - 1; p++)
						for (int r = 0; r <= k; r++) {
							int tmp = 1ll * f[k - r + p - j] * dp[j - 1][p][r] % mod;
							dp[i][j][k] += tmp;
							if (dp[i][j][k] >= mod) dp[i][j][k] -= mod;
						}
					dp[i][j][k] = 1ll * dp[i][j][k] * C[i - 1][j - 1] % mod;
				}
			}
	int answer = 0;
	for (int i = 1; i <= n; i++)
		for (int k = 0; k <= s; k++) {
			answer += dp[n][i][k];
			if (answer >= mod) answer -= mod;
		}
	return answer;
}

int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d%d%d", &n, &s, &mod);
	printf("%d\n", T.countPermutations(n, s, mod));
	return 0;
}
