#include <bits/stdc++.h>

int n, m, k;
std::set<int> r;
std::set<std::pair<int, int> > e;

std::string getAnswer(bool b) {
	if (b != 0) return "possible";
	else return "impossible";
}

bool check(int x, int y) {
	if (x > y) std::swap(x, y);
	return e.find(std::make_pair(x, y)) == e.end();
}

void dfs(int x) {
	std::vector<int> s;
	for (auto now : r) {
		if (check(x, now)) {
			s.push_back(now);
		}
	}
	for (auto now : s) {
		r.erase(now);
	}
	for (auto now : s) {
		dfs(now);
	}
}

int main() {
	freopen("E.in", "r", stdin);
	std::cin >> n >> m >> k;
	for (int i = 1; i <= m; i++) {
		int x, y;
		static int deg = 0;
		std::cin >> x >> y;
		if (x > y) std::swap(x, y);
		e.insert(std::make_pair(x, y));
		if (x == 1 && ++deg > n - k - 1) {
			return puts(getAnswer(false).c_str()), 0; 
		}
	}
	for (int i = 2; i <= n; i++) {
		r.insert(i);
	}
	int nBlock = 0;
	for (int i = 2; i <= n; i++) {
		if (check(1, i) && r.find(i) != r.end()) {
			nBlock++;
			r.erase(i);
			dfs(i);
		}
	}
	std::cout << getAnswer(nBlock <= k && r.empty()) << std::endl;
	return 0;
}
