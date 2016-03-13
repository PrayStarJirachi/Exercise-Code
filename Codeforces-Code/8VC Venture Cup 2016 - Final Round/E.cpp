#include <bits/stdc++.h>

typedef std::pair<int, int> Data;

const int MAXN = 210001;

int d, n, m, tot, c[MAXN], where[MAXN];
Data g[MAXN];
std::priority_queue<Data, std::vector<Data>, std::greater<Data> > heap;
std::vector<int> vector;

void add(int x, int d) {
	for (int i = x; i <= tot; i += i & -i) {
		c[i] = std::min(c[i], d);
	}
}

int sum(int x) {
	int ret = m + 1;
	for (int i = x; i; i -= i & -i) {
		ret = std::min(ret, c[i]);
	}
	return ret;
}

int main() {
	freopen("D.in", "r", stdin);
	std::cin >> d >> n >> m;
	for (int i = 1; i <= m; i++) {
		std::cin >> g[i].first >> g[i].second;
	}
	std::sort(g + 1, g + m + 1);
	for (int i = 1; i <= m; i++) {
		std::swap(g[i].first, g[i].second);
		vector.push_back(g[i].first);
	}
	vector.push_back(0);
	std::sort(vector.begin(), vector.end());
	vector.erase(std::unique(vector.begin(), vector.end()), vector.end());
	tot = vector.size();
	std::fill(c + 1, c + tot + 1, m + 1);
	for (int i = m; i >= 0; i--) {
		int tmp = std::lower_bound(vector.begin(), vector.end(), g[i].first) - vector.begin() + 1;
		where[i] = sum(tmp);
		add(tmp, i);
	}
	g[m + 1] = std::make_pair(0, d);
	int p = 0, z = 1, b = 0, r = n;
	long long answer = 0;
	while (p != d) {
		for (; g[b].second < p; b++);
		while (z <= m + 1 && g[z].second <= p + n) {
			heap.push(g[z]);
			z++;
		}
		int now = where[b];
		if (g[now].second - p > n) {
			answer += 1ll * (n - r) * g[b].first;
			r = n;
			int oldPos = p;
			while (!heap.empty()) {
				Data top = heap.top();
				heap.pop();
				if (top.second <= p) continue;
				r -= top.second - p;
				p = top.second;
				break;
			}
			if (oldPos == p) return puts("-1"), 0;
		} else {
			if (r < g[now].second - p) {
				answer += 1ll * (g[now].second - p - r) * g[b].first;
				r = g[now].second - p;
			}
			r -= g[now].second - p;
			p = g[now].second;
		}
	}
	std::cout << answer << std::endl;
	return 0;
}
