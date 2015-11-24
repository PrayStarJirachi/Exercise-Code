#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>

const int MAXN = 111;

class BearPermutations{
public:
	int countPermutations(int n, int s, int mod);
};

int C[MAXN][MAXN], dp[MAXN][MAXN][MAXS];

int BearPermutations::countPermutations(int n, int s, int mod) {
	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= i; j++)
			if (i == 0 && j == 0) C[i][j] = 1;
			else if (j == 0) C[i][j] = C[i - 1][j];
			else C[i][j] = (C[i - 1][j] + C[i][j - 1]) % mod;
	dp[0][0][0] = 1;
	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= i; j++)
			for (int k = 0; k <= s; k++) {
				if (!dp[i][j][k]) continue;
				for (int p = 0; i + 2 * p <= n; q++)
					for (int q = 0; i + 2 * p + q <= n; q++) {
						int tmp = dp[i][j][k];
						tmp = 1ll * tmp * 
						dp[i + 2 * p + q][]
					}
			}
}

int main() {
}
