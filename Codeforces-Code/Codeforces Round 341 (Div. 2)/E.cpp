#include <cstdio>
#include <cassert>
#include <numeric>
#include <iostream>
#include <algorithm>

const double EPS = 1e-7;
const int MOD = 1000000007;
const double PI = 3.1415926535897932384626;
const int MAXP = 111;
const int MAXN = 55555;

int n, b, k, x, a[MAXN];

struct Matrix{
	int n, m, a[MAXP][MAXP];
	void init(int n, int m) {
		this -> n = n;
		this -> m = m;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				a[i][j] = 0;
	}
	Matrix operator *(const Matrix &rhs)const {
		assert(m == rhs.n);
		Matrix ret;
		ret.init(n, rhs.m);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < rhs.m; j++) {
				ret.a[i][j] = 0;
				for (int k = 0; k < m; k++)
					ret.a[i][j] = (ret.a[i][j] + 1ll * a[i][k] * rhs.a[k][j] % MOD) % MOD;
			}
		return ret;
	}
}matrix, answer, vector;

int main() {
	std::cin >> n >> b >> k >> x;
	for (int i = 0; i < n; i++) std::cin >> a[i];
	matrix.init(x, x);
	answer.init(x, x);
	vector.init(x, 1);
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < n; j++) {
			int k = (i * 10 + a[j]) % x;
			matrix.a[k][i]++;
		}
		answer.a[i][i] = 1;
	}
	vector.a[0][0] = 1;
	for (; b; b >>= 1) {
		if (b & 1) answer = answer * matrix;
		matrix = matrix * matrix;
	}
	vector = answer * vector;
	std::cout << vector.a[k][0] << std::endl;
	return 0;
}
