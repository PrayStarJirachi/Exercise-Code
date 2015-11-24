#include <cstdio>
#include <vector>
#include <algorithm>

const int MAXN = 5001;

namespace SCC_Tarjan{
	const int MAXN = 10001;
	const int MAXM = 24995001;
	struct Edge{
		short node;
		int next;
	}e[MAXM];
	short top, tot, col, dfn[MAXN], z[MAXN], low[MAXN], whe[MAXN];
	int t, h[MAXN];
	bool instack[MAXN];
	void addedge(int x, int y) {
		t++; e[t] = (Edge){y, h[x]}; h[x] = t;
	}
	int tarjan(int x) {
		low[x] = dfn[x] = ++tot;
		instack[z[++top] = x] = true;
		for (int i = h[x]; i; i = e[i].next)
			if (!dfn[e[i].node]) {
				tarjan(e[i].node);
				low[x] = std::min(low[x], low[e[i].node]);
			} else if (instack[e[i].node]) {
				low[x] = std::min(low[x], dfn[e[i].node]);
			}
		if (dfn[x] == low[x]) {
			int y;
			col++;
			do{
				instack[y = z[top--]] = false;
				whe[y] = col;
			}
			while (x != y);
		}
	}
	void main(int n) {
		for (int i = 1; i <= 2 * n; i++) {
			if (!dfn[i]) tarjan(i);
		}
	}
};

int n;
bool a[MAXN][MAXN];
std::vector<int> indep, group;

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		int tot;
		scanf("%d", &tot);
		for (int j = 1; j <= tot; j++) {
			int x;
			scanf("%d", &x);
			a[i][x] = true;
		}
	}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) {
			if (i == j) continue;
			if (a[i][j]) {
				SCC_Tarjan::addedge(n + i, j);
			} else {
				SCC_Tarjan::addedge(i, n + j);
			}
		}
	SCC_Tarjan::main(n);
	for (int i = 1; i <= n; i++) {
		using namespace SCC_Tarjan;
		if (whe[i] == whe[i + n]) return puts("0"), 0;
	}
	for (int i = 1; i <= n; i++) {
		using namespace SCC_Tarjan;
		if (whe[i] < whe[i + n]) group.push_back(i);
		else indep.push_back(i);
	}
	if (group.size() == 0) {
		return printf("%d\n", (int)indep.size()), 0;
	}
	if (indep.size() == 0) {
		return printf("%d\n", (int)group.size()), 0;
	}
	int answer = 1;
	if (indep.size() > 1) {
		for (int i = 0; i < (int)indep.size(); i++) {
			bool check = true;
			for (int j = 0; j < (int)group.size(); j++)
				if (!a[indep[i]][group[j]]) {
					check = false;
					break;
				}
			answer += check;
		}
	}
	if (group.size() > 1) {
		for (int i = 0; i < (int)group.size(); i++) {
			bool check = true;
			for (int j = 0; j < (int)indep.size(); j++)
				if (a[indep[j]][group[i]]) {
					check = false;
					break;
				}
			answer += check;
		}
	}
	if (indep.size() > 0) {
		static int sum[MAXN];
		std::fill(sum + 1, sum + n + 1, 0);
		for (int i = 0; i < (int)indep.size(); i++)
			for (int j = 0; j < (int)group.size(); j++)
				if (!a[indep[i]][group[j]]) {
					sum[i]++;
				}
		for (int i = 0; i < (int)group.size(); i++) {
			int flag = -1;
			for (int j = 0; j < (int)indep.size(); j++)
				if (a[group[i]][indep[j]]) {
					if (flag == -1) flag = indep[j];
					else if (flag != 0) flag = 0;
				}
			if (flag == 0) continue;
			if (flag != -1) {
				bool check = true;
				for (int j = 0; j < (int)group.size(); j++) {
					if (i == j) continue;
					if (!a[flag][group[j]]) {
						check = false;
						break;
					}
				}
				answer += check;
			} else {
				for (int j = 0; j < (int)indep.size(); j++)
					if (sum[j] == 1) answer++;
			}
		}
	}
	printf("%d\n", answer);
	return 0;
}
