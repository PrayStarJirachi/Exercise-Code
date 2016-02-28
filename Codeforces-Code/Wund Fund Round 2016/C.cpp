#include <cstdio>
#include <vector>
#include <numeric>
#include <iostream>
#include <algorithm>

const double EPS = 1e-7;
const double PI = 3.1415926535897932384626;
const int MAXN = 111111;

int n, x[MAXN], y[MAXN];
std::vector<int> dx, dy, gx[MAXN], gy[MAXN];

bool isColinear(int a, int b, int c) {
	long long dx1 = dx[x[b]] - dx[x[a]], dy1 = dy[y[b]] - dy[y[a]];
	long long dx2 = dx[x[c]] - dx[x[a]], dy2 = dy[y[c]] - dy[y[a]];
	return dx1 * dy2 == dx2 * dy1;
}

bool cmpx(const int &a, const int &b) {
	return x[a] < x[b];
}

bool cmpy(const int &a, const int &b) {
	return y[a] < y[b];
}

int main() {
	std::cin >> n;
	for (int i = 1; i <= n; i++) {
		std::cin >> x[i] >> y[i];
		dx.push_back(x[i]);
		dy.push_back(y[i]);
	}
	std::sort(dx.begin(), dx.end());
	std::sort(dy.begin(), dy.end());
	dx.erase(std::unique(dx.begin(), dx.end()), dx.end());
	dy.erase(std::unique(dy.begin(), dy.end()), dy.end());
	for (int i = 1; i <= n; i++) {
		gx[x[i] = std::lower_bound(dx.begin(), dx.end(), x[i]) - dx.begin()].push_back(i);
		gy[y[i] = std::lower_bound(dy.begin(), dy.end(), y[i]) - dy.begin()].push_back(i);
		//std::cout << x[i] <<  " " << y[i] << std::endl;
	}
	for (int i = 0; i < (int)dx.size(); i++) {
		std::sort(gx[i].begin(), gx[i].end(), cmpy);
		if (gx[i].size() > 1) {
			if (i > 0) {
				std::cout << gx[i][0] << " " << gx[i][1] << " " << gx[i - 1][0] << std::endl;
				return 0;
			} else {
				std::cout << gx[i][0] << " " << gx[i][1] << " " << gx[i + 1][0] << std::endl;
				return 0;
			}
		}
	}
	for (int i = 0; i < (int)dy.size(); i++) {
		std::sort(gy[i].begin(), gy[i].end(), cmpx);
		if (gy[i].size() > 1) {
			if (i > 0) {
				std::cout << gy[i][0] << " " << gy[i][1] << " " << gy[i - 1][0] << std::endl;
				return 0;
			} else {
				std::cout << gy[i][0] << " " << gy[i][1] << " " << gy[i + 1][0] << std::endl;
				return 0;
			}
		}
	}
	for (int i = 1; i + 1 < (int)dx.size(); i++) {
		if (!isColinear(gx[i - 1][0], gx[i][0], gx[i + 1][0])) {
			std::cout << gx[i - 1][0] << " " << gx[i][0] << " " << gx[i + 1][0] << std::endl;
			return 0;
		}
	}
	return 0;
}
