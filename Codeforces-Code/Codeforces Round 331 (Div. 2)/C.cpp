#include <map>
#include <set>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

const int MAXN = 111111;

int n, o[MAXN];
std::pair<int, int> p[MAXN];
std::vector<int> w[MAXN], d, dx, dy;
std::set<std::pair<int, int> > set;

bool cmp(const int &a, const int &b) {
	return p[a] > p[b];
}

bool check() {
	for (int i = 1; i <= n; i++) {
		std::pair<int, int> now = p[o[i]];
		std::set<std::pair<int, int> >::iterator it = set.lower_bound(now);
		if (it == set.end()) {
			set.insert(now);
			continue;
		}
		if (now.second <= it -> second) return false;
	}
	return true;
}

int main() {
	freopen("C.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d%d", &p[i].first, &p[i].second);
		d.push_back(p[i].second - p[i].first);
		dx.push_back(p[i].first);
		dy.push_back(p[i].second);
	}
	std::sort(d.begin(), d.end());
	d.erase(std::unique(d.begin(), d.end()), d.end());
	for (int i = 1; i <= n; i++) {
		int tmp = p[i].second - p[i].first;
		tmp = std::lower_bound(d.begin(), d.end(), tmp) - d.begin();
		w[tmp].push_back(i);
	}
	for (int i = 0; i < (int)d.size(); i++) {
		std::sort(w[i].begin(), w[i].end(), cmp);
	}
	for (int i = 1, cnt = 0; i <= n; i++) {
		int x; scanf("%d", &x);
		int tmp = std::lower_bound(d.begin(), d.end(), x) - d.begin();
		if (d[tmp] != x || w[tmp].empty()) {
			puts("NO");
			return 0;
		}
		o[++cnt] = w[tmp][(int)w[tmp].size() - 1];
		w[tmp].pop_back();
	}
	if (!check()) {
		puts("NO");
		return 0;
	}
	puts("YES");
	for (int i = 1; i <= n; i++) {
		printf("%d %d\n", p[o[i]].first, p[o[i]].second);
	}
	return 0;
}
