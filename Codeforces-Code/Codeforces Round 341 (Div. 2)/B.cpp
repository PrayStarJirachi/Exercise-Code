#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

const int MAXN = 222222;

int n, px[MAXN], py[MAXN];
std::vector<int> dx, dy;

int main() {
	std::cin >> n;
	for (int i = 1; i <= n; i++) {
		std::cin >> px[i] >> py[i];
		dx.push_back(px[i] + py[i]);
		dy.push_back(px[i] - py[i]);
	}
	std::sort(dx.begin(), dx.end());
	std::sort(dy.begin(), dy.end());
	for (int i = 1; i <= n; i++) {
		int x = px[i], y = py[i];
		px[i] = std::lower_bound(dx.begin(), dx.end(), x + y) - dx.begin();
		py[i] = std::lower_bound(dy.begin(), dy.end(), x - y) - dy.begin();
		//std::cout << px[i] << " " << py[i] << std::endl;
	}
	std::sort(px + 1, px + n + 1);
	std::sort(py + 1, py + n + 1);
	long long answer = 0;
	for (int i = 1; i <= n; i++) {
		int z = i;
		while (z < n && px[z] == px[z + 1]) z++;
		answer += 1ll * (z - i + 1) * (z - i) >> 1;
		//std::cout << z - i + 1 << std::endl;
		i = z;
	}
	
	for (int i = 1; i <= n; i++) {
		int z = i;
		while (z < n && py[z] == py[z + 1]) z++;
		answer += 1ll * (z - i + 1) * (z - i) >> 1;
		//std::cout << z - i + 1 << std::endl;
		i = z;
	}
	
	std::cout << answer << std::endl;
	return 0;
}
