#include <map>
#include <cstdio>
#include <iostream>
#include <algorithm>

int m;
std::pair<int, int> h, a, x, y;
std::map<long long, bool> map;

int gcd(int a, int b) {
	return b ? gcd(b, a % b) : a;
}
// a + y
// xa + y
// x^2a + xy + y
// x^3a + x^2y + xy + y
// x^ka + (x^{k - 1} + x^{k - 2} + ... + x^0)y
int getRem(int a, int b, int x, int y) {
	for (int i = 1; i <= 3 * m; i++) {
		a = ((long long)x * a % m + y) % m;
		if (a == b) return i;
	}
	return -1;
}

int main() {
	freopen("A.in", "r", stdin);
	scanf("%d", &m);
	scanf("%d%d", &h.first, &a.first);
	scanf("%d%d", &x.first, &y.first);
	scanf("%d%d", &h.second, &a.second);
	scanf("%d%d", &x.second, &y.second);
	std::pair<int, int> rem;
	std::pair<int, int> mod;
	rem.first = getRem(h.first, a.first, x.first, y.first);
	rem.second = getRem(h.second, a.second, x.second, y.second);
	mod.first = getRem(a.first, a.first, x.first, y.first);
	mod.second = getRem(a.second, a.second, x.second, y.second);
	if (rem.first == -1 || rem.second == -1) {
		puts("-1");
		return 0;
	}
	if (mod.first == -1 && mod.second == -1) {
		if (rem.first == rem.second) printf("%d\n", rem.first);
		else puts("-1");
	}
	else if (mod.first == -1) {
		// rem.first = rem.second + k * mod.second
		if (rem.first < rem.second || ((rem.first - rem.second) % mod.second)) puts("-1");
		else printf("%d\n", rem.first);
	}
	else if (mod.second == -1) {
		if (rem.second < rem.first || ((rem.second - rem.first) % mod.first)) puts("-1");
		else printf("%d\n", rem.second);
	}
	else{
		for (int i = 0; i < m; i++) {
			long long now = (long long) mod.first * i;
			now = (now + rem.first);
			map[now] = true;
		}
		long long answer = 1ll << 50;
		for (int i = 0; i < m; i++) {
			long long now = (long long)mod.second * i;
			now = (now + rem.second);
			if (map[now] && answer > now) {
				answer = now;
			}
		}
		if (answer == 1ll << 50) puts("-1");
		else std::cout << answer << std::endl;
	}
	return 0;
}
