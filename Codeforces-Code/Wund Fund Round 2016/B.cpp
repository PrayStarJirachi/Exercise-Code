#include <cstdio>
#include <numeric>
#include <iostream>
#include <algorithm>

const double EPS = 1e-7;
const double PI = 3.1415926535897932384626;
const int MAXN = 55;

int n, a[MAXN][MAXN];

int main() {
	// freopen("input.txt", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) 
		for (int j = 1; j <= n; j++)
			scanf("%d", &a[i][j]);
	for (int h = 1; h <= n; h++) {
		for (int i = 1; i <= n; i++) {
			if (a[i][i]) continue;
			bool check = true;
			for (int j = 1; j <= n; j++) {
				if (i == j || a[j][j]) continue;
				if (a[i][j] != h || a[j][i] != h) {
					check = false;
					break;
				}
			}
			if (check) {
				a[i][i] = h;
				break;
			}
		}
	}
	for (int i = 1; i <= n; i++)
		std::cout << a[i][i] << " ";
	std::cout << std::endl;
	return 0;
}
