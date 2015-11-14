#include <cstdio>
#include <algorithm>

const int mod = 1000000007;
const int MAXN = 2001;

class AlmostEulerianGraph{
private:
	int f[MAXN], g[MAXN], h[MAXN], C[MAXN][MAXN];
	int fpm(int a, int b) {
		int ret = 1;
		for (; b; b >>= 1) {
			if (b & 1) ret = 1ll * ret * a % mod;
			a = 1ll * a * a % mod;
		}
		return ret;
	}
	void update(int &x, int y) {
		x += y;
		if (x >= mod) x -= mod;
	}
public:
	int calculateGraphs(int n) {
		for (int i = 0; i <= n; i++)
			for (int j = 0; j <= i; j++) {
				if (!i && !j) C[i][j] = 1;
				else if (!j) C[i][j] = C[i - 1][j];
				else C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
			}
		f[1] = 1;
		g[1] = 1;
		for (int i = 1; i <= n; i++)
			h[i] = fpm(2, (i - 1) * (i - 2) >> 1);
		for (int i = 2; i <= n; i++) {
			for (int j = 1; j < i; j++) {
				int tmp = C[i - 1][j - 1];
				tmp = 1ll * tmp * f[j] % mod;
				tmp = 1ll * tmp * h[i - j] % mod;
				update(g[i], tmp);
			}
			f[i] = (h[i] - g[i] + mod) % mod;
		}
		int answer = f[n];
		answer = 1ll * answer * ((n * (n - 1) >> 1) + 1) % mod;
		return answer;
	}
}T;

int n;

int main() {
	//freopen("input.txt", "r", stdin);
	scanf("%d", &n);
	printf("%d\n", T.calculateGraphs(n));
	return 0;
}
