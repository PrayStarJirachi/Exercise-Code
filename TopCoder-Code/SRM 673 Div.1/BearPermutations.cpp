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
bool v[MAXN][MAXN][MAXS];

int dfs(int left, int right, int s, const int &mod) {
	if (v[left][right][s]) return dp[left][right][s];
	v[left][right][s] = true;
	int &now = dp[left][right][s];
	for (int i = left; i <= right; i++)
		for (int j = i + 2; j <= right; j++) {
			int tmp = 1;
			tmp = 1ll * tmp * dfs(left, i - 1) % mod;
			
		}
}

int BearPermutations::countPermutations(int n, int s, int mod) {
	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= i; j++)
			if (i == 0 && j == 0) C[i][j] = 1;
			else if (j == 0) C[i][j] = C[i - 1][j];
			else C[i][j] = (C[i - 1][j] + C[i][j - 1]) % mod;
	return dfs(1, n, s);
}

int main() {
}
