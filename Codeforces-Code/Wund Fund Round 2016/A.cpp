#include <cstdio>
#include <numeric>
#include <iostream>
#include <algorithm>

const double EPS = 1e-7;
const double PI = 3.1415926535897932384626;
const int MAXN = 100001;

int n, a[MAXN];

int main() {
	// freopen("input.txt", "r", stdin);
	scanf("%d", &n);
	int top = 0;
	for (int i = 1; i <= n; i++) {
		a[++top] = 1;
		while (top > 1 && a[top] == a[top - 1]) a[--top]++;
	}
	for (int i = 1; i <= top; i++)
		std::cout << a[i] << " ";
	std::cout << std::endl;
	return 0;
}
