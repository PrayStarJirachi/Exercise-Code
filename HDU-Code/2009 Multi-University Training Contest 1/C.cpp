#include <cstdio>
#include <vector>
#include <algorithm>

const int MAXN = 1001;
const int MAXM = 20001;

struct Edge{
	int node, next;
}e[MAXM];

int n, t, p[MAXN], h[MAXN], whe[MAXN], a[MAXN][MAXN];
bool v[MAXN];
std::vector<std::pair<int, int> > vec;

void addedge(int x, int y) {
	t++; e[t] = (Edge){y, h[x]}; h[x] = t;
}

bool find(int x) {
	for (int i = h[x]; i; i = e[i].next) {
		if (v[e[i].node]) continue;
		v[e[i].node] = true;
		if (!p[e[i].node] || find(p[e[i].node])) {
			p[e[i].node] = x;
			return true;
		}
	}
	return false;
}

int main() {
	freopen("C.in", "r", stdin);
	while (scanf("%d", &n) == 1) {
		t = 0;
		std::fill(h + 1, h + n + 1, 0);
		std::fill(p + 1, p + n + 1, 0);
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++) {
				scanf("%d", &a[i][j]);
				if (a[i][j] == 1) {
					addedge(j, i);
				}
			}
		int ans = 0;
		for (int i = 1; i <= n; i++) {
			std::fill(v + 1, v + n + 1, false);
			if (find(i)) ans++;
		}
		if (ans < n) printf("-1\n");
		else{
			vec.clear();
			for (int i = 1; i <= n; i++) {
				whe[p[i]] = i;
			}
			std::fill(v + 1, v + n + 1, false);
			for (int i = 1; i <= n; i++) {
				if (v[i]) continue;
				v[i] = true;
				for (int j = whe[i]; j != i; j = whe[j]) {
					vec.push_back(std::make_pair(j, whe[j]));
					v[j] = true;
				}
			}
			printf("%d\n", (int)vec.size());
			for (std::vector<std::pair<int, int> >::iterator it = vec.begin(); it != vec.end(); ++it) {
				printf("R %d %d\n", it -> first, it -> second);
			}
		}
	}
	return 0;
}
