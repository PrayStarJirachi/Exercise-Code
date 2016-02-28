#include <bits/stdc++.h>

const std::pair<int, int> MOD = std::make_pair(1000000021, 772347887), POW = std::make_pair(10009, 17);
const int MAXN = 110001;
const int MAXM = 110001;

int n, m, dp[MAXN], pre[MAXN], v[MAXN];
char s[MAXN];
std::pair<int, int> h[MAXN], hash[MAXM], fpm[MAXN];
std::map<std::pair<int, int>, int> map;
std::string c[MAXN];

std::pair<int, int> getHash(const char *c) {
	int len = strlen(c);
	std::pair<int, int> ret = std::make_pair(0, 0);
	for (int i = len - 1; i >= 0; i--) {
		char tmp = tolower(c[i]);
		ret.first = (1ll * ret.first * POW.first % MOD.first + tmp) % MOD.first;
		ret.second = (1ll * ret.second * POW.second % MOD.second + tmp) % MOD.second;
	}
	return ret;
}

std::pair<int, int> getSub(int x, int y) {
	std::pair<int, int> ret = std::make_pair(0, 0);
	ret.first = (h[y].first - 1ll * h[x - 1].first * fpm[y - x + 1].first % MOD.first + MOD.first) % MOD.first;
	ret.second = (h[y].second - 1ll * h[x - 1].second * fpm[y - x + 1].second % MOD.second + MOD.second) % MOD.second;
	return ret;
}

int main() {
	std::cin >> n;
	std::cin >> s + 1;
	fpm[0] = std::make_pair(1, 1);
	for (int i = 1; i <= n; i++) {
		s[i] = tolower(s[i]);
		h[i].first = (1ll * h[i - 1].first * POW.first % MOD.first + s[i]) % MOD.first;
		h[i].second = (1ll * h[i - 1].second * POW.second % MOD.second + s[i]) % MOD.second;
		fpm[i].first = 1ll * fpm[i - 1].first * POW.first % MOD.first;
		fpm[i].second = 1ll * fpm[i - 1].second * POW.second % MOD.second;
	}
	std::cin >> m;
	for (int i = 1; i <= m; i++) {
		std::cin >> c[i];
		map[getHash(c[i].c_str())] = i;
	}
	dp[0] = 1;
	v[0] = 1;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= 1000 && j <= i; j++) {
			if (!v[i - j]) continue;
			auto it = map.find(getSub(i - j + 1, i));
			if (it == map.end()) continue;
			dp[i] = i - j;
			v[i] = true;
			pre[i] = it -> second;
		}
	static std::vector<std::string> answer;
	answer.clear();
	for (int i = n; i; i = dp[i])
		answer.push_back(c[pre[i]]);
	std::reverse(answer.begin(), answer.end());
	for (auto x : answer)
		std::cout << x << " ";
	std::cout << std::endl;
	return 0;
}
