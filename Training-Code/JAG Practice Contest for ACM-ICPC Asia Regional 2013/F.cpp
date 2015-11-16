#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>

const int MAXN = 555;
const int MAXS = 101111;
const int MAXH = 555;
const int MAXL = 555;
const long double eps = 1e-15;

int n, m, cnt, c[MAXN], l[MAXS], graph[MAXN][MAXN];
char a[MAXN][MAXN], b[MAXN][MAXN];

namespace Gaussian_Elimination{
	long double a[MAXH][MAXL + 1], x[MAXL];
	void init(int nE, int nV) {
		std::fill(x + 1, x + nV + 1, 0);
		for (int i = 1; i <= nE; i++)
			for (int j = 1; j <= nV + 1; j++)
				a[i][j] = 0;
	}
	int main(int nE, int nV) { // 0:Normal 1:No solution 2:multi-solution
		for (int h = 1; h <= nV; h++) {
			for (int i = h + 1; i <= nE; i++) {
				if (fabs(a[h][h]) > fabs(a[i][h])) continue;
				for (int j = 1; j <= nV + 1; j++)
					std::swap(a[h][j], a[i][j]);
			}
			if (fabs(a[h][h]) < eps) continue;
			for (int i = h + 1; i <= nE; i++) {
				if (fabs(a[i][h]) < eps) continue;
				long double t = a[i][h] / a[h][h];
				for (int j = h; j <= nV + 1; j++)
					a[i][j] -= a[h][j] * t;
			}
		}
		
		for (int h = nV + 1; h <= nE; h++) {
			if (fabs(a[h][nV + 1]) < eps) continue;
			return 1;
		}
		
		for (int h = nV; h >= 1; h--) {
			x[h] = a[h][nV + 1];
			for (int i = h + 1; i <= nV; i++)
				x[h] -= x[i] * a[h][i];
			if (fabs(a[h][h]) < eps) {
				if (fabs(x[h]) < eps) return 2;
				else return 1;
			}
			x[h] /= a[h][h];
		}
		return 0;
	}
};

int toInt(char c) {
	if (c == 'W') return 0;
	else return 1;
}

int getLabel(int *c) {
	int ret = 0;
	for (int i = 1; i <= n; i++)
		ret = ret * 6 + c[i];
	return ret;
}

void dfs(int h, int last) {
	if (h == n + 1) {
		l[getLabel(c)] = ++cnt;
		return;
	}
	for (int i = 0; i <= last; i++) {
		c[h] = i;
		dfs(h + 1, i);
	}
}

void getEquation(int h, int last) {
	if (h == n + 1) {
		static int tmp[MAXN][MAXN], cur[MAXN][MAXN], next[MAXN], graph[MAXN][MAXN];
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++)
				cur[i][j] = toInt(b[i][j]) ^ (j <= c[i]);
		}
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				for (int col = 0; col < 2; col++) {
					for (int k = 1; k <= n; k++)
						for (int l = 1; l <= m; l++) {
							tmp[k][l] = cur[k][l];
							graph[k][l] = 0;
						}
					for (int k = 1; k <= i; k++)
						for (int l = 1; l <= j; l++) {
							tmp[k][l] = col;
						}
					for (int k = 1; k <= n; k++)
						for (int l = 1; l <= m; l++)
							if (tmp[k][l] != toInt(b[k][l])) {
								for (int p = 1; p <= k; p++)
									for (int q = 1; q <= l; q++)
										graph[p][q] = 1;
							}
					for (int k = 1; k <= n; k++) {
						next[k] = 0;
						for (int l = 1; l <= m; l++)
							if (graph[k][l]) next[k] = l;
					}
					Gaussian_Elimination::a[l[getLabel(c)]][l[getLabel(next)]] -= 1.0 / n / m / 2.0;
					Gaussian_Elimination::a[l[getLabel(c)]][cnt + 1] += (long double)i * j / n / m / 2.0;
				}
		return;
	}
	for (int i = 0; i <= last; i++) {
		c[h] = i;
		getEquation(h + 1, i);
	}
}

int main() {
	freopen("F.in", "r", stdin);
	while (scanf("%d%d", &n, &m) == 2) {
		if (n == 0 && m == 0) break;
		for (int i = 1; i <= n; i++) scanf("%s", a[i] + 1);
		for (int i = 1; i <= n; i++) scanf("%s", b[i] + 1);
		cnt = 0;
		dfs(1, m);
		Gaussian_Elimination::init(cnt, cnt);
		getEquation(1, m);
		for (int i = 1; i <= cnt; i++)
			Gaussian_Elimination::a[i][i]++;
		static int now[MAXN];
		for (int i = 1; i <= n; i++) now[i] = 0;
		for (int i = 1; i <= cnt + 1; i++) {
			Gaussian_Elimination::a[l[getLabel(now)]][i] = 0;
		}
		Gaussian_Elimination::a[l[getLabel(now)]][l[getLabel(now)]] = 1;
		Gaussian_Elimination::main(cnt, cnt);
		for (int k = 1; k <= n; k++)
			for (int l = 1; l <= m; l++)
				graph[k][l] = 0;
		for (int k = 1; k <= n; k++)
			for (int l = 1; l <= m; l++)
				if (a[k][l] != b[k][l]) {
					for (int p = 1; p <= k; p++)
						for (int q = 1; q <= l; q++)
							graph[p][q] = 1;
				}
		for (int k = 1; k <= n; k++) {
			now[k] = 0;
			for (int l = 1; l <= m; l++)
				if (graph[k][l]) now[k] = l;
		}
		double answer = Gaussian_Elimination::x[l[getLabel(now)]];
		printf("%.10f\n", answer);
		//Gaussian_Elimination::print(cnt, cnt);
	}
	return 0;
}
