#include <cstdio>
#include <vector>
#include <numeric>
#include <iostream>
#include <algorithm>

const double EPS = 1e-7;
const double PI = 3.1415926535897932384626;
const int MAXN = 222222;
const int MAXM = 444444;

struct Edge{
	int node, next;
}e[MAXM];

int n, x, y, t, h[MAXN], deg[MAXN], dp[MAXN][2];
bool v[MAXN][2];

void addEdge(int x, int y) {
	t++; e[t] = (Edge){y, h[x]}; h[x] = t; deg[x]++;
	t++; e[t] = (Edge){x, h[y]}; h[y] = t; deg[y]++;
}

int getMax(int x, int k, int fa) {
	if (v[x][k]) return dp[x][k];
	v[x][k] = true;
	dp[x][k] = 0;
	int sum = 0;
	for (int i = h[x]; i; i = e[i].next) {
		if (e[i].node == fa) continue;
		getMax(e[i].node, 0, x);
		getMax(e[i].node, 1, x);
		sum += dp[e[i].node][0];
	}
	if (k == 0) {
		static std::vector<std::pair<int, int> > array;
		array.clear();
		for (int i = h[x]; i; i = e[i].next) {
			if (e[i].node == fa) continue;
			array.push_back(std::make_pair(-dp[e[i].node][0] + dp[e[i].node][1] + 1, e[i].node));
		}
		dp[x][k] = sum;
		std::sort(array.rbegin(), array.rend());
		for (int i = 0; i < (int)array.size() && i < 2; i++) {
			dp[x][k] += array[i].first;
		}
		
		/*static std::vector<std::pair<int, int> > array;
		array.clear();
		for (int i = h[x]; i; i = e[i].next) {
			if (e[i].node == fa) continue;
			array.push_back(std::make_pair(dp[e[i].node][1], e[i].node));
		}
		std::sort(array.rbegin(), array.rend());
		for (int i = 0; i < (int)array.size(); i++) {
			if (i < 2) {
				dp[x][k] += array[i].first + 1;
			} else {
				dp[x][k] += dp[array[i].second][0];
			}
		}*/
	} else {
		for (int i = h[x]; i; i = e[i].next) {
			if (e[i].node == fa) continue;
			if (dp[x][k] < sum - dp[e[i].node][0] + dp[e[i].node][1] + 1) {
				dp[x][k] = sum - dp[e[i].node][0] + dp[e[i].node][1] + 1;
			}
		}
	}
	return dp[x][k];
}

int getMin() {
	for (int i = 1; i <= n; i++)
		if (deg[i] == n - 1) {
			return 1;
		}
	return 0;
}

int main() {
	std::cin >> n >> x >> y;
	for (int i = 1; i < n; i++) {
		int u, v;
		std::cin >> u >> v;
		addEdge(u, v);
	}
	
	if (x < y) {
		int maxEdge = getMax(1, 0, 0);
		std::cout << 1ll * (n - 1 - maxEdge) * y + 1ll * maxEdge * x << std::endl;
		//std::cout << maxEdge << std::endl;
	} else {
		int minEdge = getMin();
		std::cout << 1ll * (n - 1 - minEdge) * y + 1ll * minEdge * x << std::endl;
	}
	return 0;
}
