#include <map>
#include <vector>
#include <cstdio>
#include <numeric>
#include <iostream>
#include <algorithm>

const double EPS = 1e-7;
const double PI = 3.1415926535897932384626;
const long long INF = 1ll << 50;

const int MAXP = 40001;
const int MAXN = 1010001;

int n, g, p[MAXP], d[MAXN];
long long a, b;
bool visit[MAXP];
std::map<int, std::vector<int> > map;

void add(int x, int pos) {
	for (int j = 1; j <= g && p[j] * p[j] <= x; j++) {
		int now = p[j];
		if (x % now) continue;
		if (map[now].empty() && (pos != 1 && pos != n)) continue;
		map[now].push_back(pos);
		while (x % now == 0) {
			x /= now;
		}
	}
	if (x > 1) {
		if (map[x].empty() && (pos != 1 && pos != n)) return;
		map[x].push_back(pos);
	}
}

void add(std::vector<int> data) {
	for (int i = 1; i <= g; i++) {
		bool flag = false;
		for (int j = 0; j < (int)data.size(); j++) {
			if (data[j] % p[i] == 0) {
				flag = true;
				break;
			}
		}
		if (!flag) continue;
		for (int j = 1; j <= n; j++)
			if (d[j] % p[i] == 0 || (d[j] - 1) % p[i] == 0 || (d[j] + 1) % p[i] == 0)  {
				map[p[i]].push_back(j);
			}
		for (int j = 0; j < (int)data.size(); j++) {
			while (data[j] % p[i] == 0) {
				data[j] /= p[i];
			}
		}
	}
	std::sort(data.begin(), data.end());
	data.erase(std::unique(data.begin(), data.end()), data.end());
	for (int i = 0; i < (int)data.size(); i++) {
		if (data[i] == 1) continue;
		for (int j = 1; j <= n; j++) {
			if (d[j] % data[i] == 0 || (d[j] - 1) % data[i] == 0 || (d[j] + 1) % data[i] == 0) {
				map[data[i]].push_back(j);
			}
		}
	}
}

int main() {
	std::cin >> n >> a >> b;
	for (int i = 1; i <= n; i++) scanf("%d", d + i);
	for (int i = 2; i <= MAXP; i++) {
		if (!visit[i]) p[++g] = i;
		for (int j = 1; j <= g && i * p[j] <= MAXP; j++) {
			visit[i * p[j]] = true;
			if (i % p[j] == 0) break;
		}
	}
	static std::vector<int> c;
	c.clear();
	c.push_back(d[1]);
	c.push_back(d[1] - 1);
	c.push_back(d[1] + 1);
	c.push_back(d[n]);
	c.push_back(d[n] - 1);
	c.push_back(d[n] + 1);
	add(c);
	long long answer = INF;
	for (std::map<int, std::vector<int> >::iterator it = map.begin(); it != map.end(); it++) {
		static long long Pred[MAXN], Succ[MAXN];
		long long *pred = Pred + 1, *succ = Succ;
		std::vector<int> &now = it -> second;
		//std::sort(now.begin(), now.end());
		now.erase(std::unique(now.begin(), now.end()), now.end());
		int left = (int)now.size(), right = -1;
		pred[0] = 0;
		for (int i = 0; i < (int)now.size(); i++) {
			pred[i] = pred[i - 1];
			if (i > 0 && now[i] != now[i - 1] + 1) pred[i] = INF;
			if (d[now[i]] % (it -> first) != 0) pred[i] = std::min(INF, pred[i] + b);
			if (i == 0 && now[i] != 1) pred[i] = INF;
		}
		succ[(int)now.size()] = 0;
		for (int i = (int)now.size() - 1; i >= 0; i--) {
			succ[i] = succ[i + 1];
			if (i < (int)now.size() - 1 && now[i] + 1 != now[i + 1]) succ[i] = INF;
			if (d[now[i]] % (it -> first) != 0) succ[i] = std::min(INF, succ[i] + b);
			if (i == (int)now.size() - 1 && now[i] != n) succ[i] = INF;
		}
		long long z = -a;
		for (int i = 0; i <= (int)now.size(); i++) {
			int nowPos = (i == (int)now.size()) ? n + 1 : now[i];
			answer = std::min(answer, z + succ[i] + 1ll * a * nowPos);
			z = std::min(z, pred[i] - 1ll * a * (nowPos + 1));
		}
	}
	std::cout << answer << std::endl;
	return 0;
}
