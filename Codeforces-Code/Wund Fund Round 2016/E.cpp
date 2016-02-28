#include <bits/stdc++.h>

const int MAXN = 300001;
const long double pi = acos(-1.0);

struct Matrix{
	int n, m;
	long double a[4][4];
	Matrix operator *(const Matrix &rhs)const {
		Matrix ret;
		ret.n = n;
		ret.m = rhs.m;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < rhs.m; j++) {
				ret.a[i][j] = 0;
				for (int k = 0; k < m; k++)
					ret.a[i][j] += a[i][k] * rhs.a[k][j];
			}
		return ret;		
	}
}O;

int n, m, M;
Matrix t[MAXN * 4];
long double length[MAXN], angle[MAXN];

Matrix getRotate(const long double &angle) {
	Matrix ret;
	ret.n = 4;
	ret.m = 4;
	ret.a[0][0] = 1; ret.a[0][1] = 0; ret.a[0][2] = 0;            ret.a[0][3] = 0;
	ret.a[1][0] = 0; ret.a[1][1] = 1; ret.a[1][2] = 0;            ret.a[1][3] = 0;
	ret.a[2][0] = 0; ret.a[2][1] = 0; ret.a[2][2] = cos(angle);   ret.a[2][3] = sin(angle);
	ret.a[3][0] = 0; ret.a[3][1] = 0; ret.a[3][2] = -sin(angle);  ret.a[3][3] = cos(angle);
	return ret;
}

Matrix getMove(const long double &length) {
	Matrix ret;
	ret.n = 4;
	ret.m = 4;
	ret.a[0][0] = 1; ret.a[0][1] = 0; ret.a[0][2] = length;  ret.a[0][3] = 0;
	ret.a[1][0] = 0; ret.a[1][1] = 1; ret.a[1][2] = 0;       ret.a[1][3] = length;
	ret.a[2][0] = 0; ret.a[2][1] = 0; ret.a[2][2] = 1;       ret.a[2][3] = 0;
	ret.a[3][0] = 0; ret.a[3][1] = 0; ret.a[3][2] = 0;       ret.a[3][3] = 1;
	return ret;
}

void modify(int x, const Matrix &data) {
	for (t[x += M] = data, x >>= 1; x; x >>= 1) {
		t[x] = t[x << 1 ^ 1] * t[x << 1];
	}
}

Matrix getProd(int x, int y) {
	Matrix left = getRotate(0) * getMove(0);
	Matrix right = getRotate(0) * getMove(0);
	for (x += M - 1, y += M + 1; x ^ y ^ 1; x >>= 1, y >>= 1) {
		if (x & 1 ^ 1) left = t[x ^ 1] * left;
		if (y & 1) right = right * t[y ^ 1];
	}
	return right * left;
}

int main() {
	std::cin >> n >> m;
	for (M = 1; M <= n + 1; M <<= 1);
	for (int i = 1; i <= n; i++) {
		t[M + i] = getMove(length[i] = 1) * getRotate(angle[i] = 0);
	}
	for (int i = M; i >= 1; i--) {
		t[i] = t[i << 1] * t[i << 1 ^ 1];
	}
	O.n = 4; O.m = 1;
	O.a[0][0] = 0;
	O.a[1][0] = 0;
	O.a[2][0] = 1;
	O.a[3][0] = 0;
	for (int i = 1; i <= m; i++) {
		int id, pos;
		long double value;
		std::cin >> id >> pos >> value;
		if (id == 1) {
			modify(pos, getMove(length[pos] += value) * getRotate(angle[pos]));
		} else {
			modify(pos, getMove(length[pos]) * getRotate(angle[pos] += pi * value / 180));
		}
		Matrix tmp = getProd(1, n) * O;
		printf("%.10f %.10f\n", (double)tmp.a[0][0], (double)tmp.a[1][0]);
		//std::cout << std::endl;
	}
	return 0;
}
