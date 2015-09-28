#include <cstdio>
#include <cmath>
#include <algorithm>

int c, X1, Y1, X2, Y2, X3, Y3, x[4], y[4];

int getsqrt(int x) {
	int c = (int)sqrt(x);
	for (int i = c - 2; i <= c + 2; i++)
		if (x == i * i) return i;
	return -1;
}

bool canpaint(char A, char B, char C) {
	if (x[1] != c) return false;
	if (y[1] + x[2] != c) return false;
	if (y[2] + y[3] != c) return false;
	if (x[3] + y[1] != c) return false;
	if (x[2] != x[3]) return false;
	printf("%d\n", c);
	for (int i = 1; i <= c; i++) {
		for (int j = 1; j <= c; j++) {
			if (j <= y[1]) putchar(A);
			else{
				if (i <= y[2]) putchar(B);
				else putchar(C);
			}
		}
		puts("");
	}
	return true;
}

bool paint(int X1, int Y1, int X2, int Y2, int X3, int Y3, char A, char B, char C) {
	for (int i = 0; i < (1 << 3); i++) {
		x[1] = X1; y[1] = Y1;
		x[2] = X2; y[2] = Y2;
		x[3] = X3; y[3] = Y3;
		for (int j = 1; j <= 3; j++) {
			if (i & (1 << j - 1)) {
				std::swap(x[j], y[j]);
			}
		}
		if (canpaint(A, B, C)) return true;
	}
	return false;
}

int main() {
	freopen("D.in", "r", stdin);
	scanf("%d%d%d%d%d%d", &X1, &Y1, &X2, &Y2, &X3, &Y3);
	if (X1 > Y1) std::swap(X1, Y1);
	if (X2 > Y2) std::swap(X2, Y2);
	if (X3 > Y3) std::swap(X3, Y3);
	int area = X1 * Y1 + X2 * Y2 + X3 * Y3;
	c = getsqrt(area);
	if (c == -1) return printf("-1\n"), 0;
	if (Y1 == c && Y2 == c && Y3 == c && X1 + X2 + X3 == c) {
		printf("%d\n", c);
		for (int i = 1; i <= X1; i++) {
			for (int j = 1; j <= c; j++) putchar('A');
			puts("");
		}
		for (int i = 1; i <= X2; i++) {
			for (int j = 1; j <= c; j++) putchar('B');
			puts("");
		}
		for (int i = 1; i <= X3; i++) {
			for (int j = 1; j <= c; j++) putchar('C');
			puts("");
		}
	}
	else{
		if (paint(X1, Y1, X2, Y2, X3, Y3, 'A', 'B', 'C')) return 0;
		if (paint(X1, Y1, X3, Y3, X2, Y2, 'A', 'C', 'B')) return 0;
		if (paint(X2, Y2, X1, Y1, X3, Y3, 'B', 'A', 'C')) return 0;
		if (paint(X2, Y2, X3, Y3, X1, Y1, 'B', 'C', 'A')) return 0;
		if (paint(X3, Y3, X1, Y1, X2, Y2, 'C', 'A', 'B')) return 0;
		if (paint(X3, Y3, X2, Y2, X1, Y1, 'C', 'B', 'A')) return 0;
		printf("-1\n");
	}
	return 0;
}
