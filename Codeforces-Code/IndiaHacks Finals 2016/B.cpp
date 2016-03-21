#include <bits/stdc++.h>

int n, q, answer;
std::map<std::string, char> map;

void dfs(int h, const std::string &s) {
	if (h == n + 1) {
		std::string tmp = s;
		while (tmp.length() > 1) {
			if (map.find(tmp.substr(0, 2)) != map.end()) {
				std::string t = tmp.substr(0, 2);
				tmp.erase(0, 2);
				tmp = map[t] + tmp;
			} else break;
		}
		if (tmp == "a") {
			answer++;
		}
		return;
	}
	for (char c = 'a'; c <= 'f'; c++) {
		char tmp[20];
		sprintf(tmp, "%c", c);
		dfs(h + 1, s + tmp);
	}
}

int main() {
	std::cin >> n >> q;
	for (int i = 1; i <= q; i++) {
		std::string a;
		char b[20];
		std::cin >> a >> b;
		map[a] = b[0];
	}
	dfs(1, "");
	printf("%d\n", answer);
	return 0;
}
