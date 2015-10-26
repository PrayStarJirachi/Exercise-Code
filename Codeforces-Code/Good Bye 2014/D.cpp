#include <cstdio>
#include <iostream>
#include <algorithm>

const int MAXN = 100001;
const int MAXM = 200001;

struct Edge{
	int node, next;
}e[MAXM];

struct Road{
	int x, y, c;
}r[MAXM];

int n, q, t, h[MAXN], s[MAXN], f[MAXN];

void addedge(int x, int y) {
	t++; e[t] = (Edge){y, h[x]}; h[x] = t;
	t++; e[t] = (Edge){x, h[y]}; h[y] = t;
}

void buildtree(int x) {
	static int q[MAXN];
	int left = 0, right = 0;
	q[++right] = x;
	while (left < right) {
		left++;
		for (int i = h[q[left]]; i; i = e[i].next) {
			if (e[i].node == f[q[left]]) continue;
			q[++right] = e[i].node;
			f[e[i].node] = q[left];
		}
	}
	for (int i = n; i >= 1; i--) {
		s[q[i]] = 1;
		for (int j = h[q[i]]; j; j = e[j].next)
			s[q[i]] += s[e[j].node];
	}
}

int main() {
	freopen("D.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i < n; i++) {
		std::cin >> r[i].x >> r[i].y >> r[i].c;
		addedge(r[i].x, r[i].y);
	}
	buildtree(1);
	long long answer = 0;
	for (int i = 1; i < n; i++) {
		if (f[r[i].y] == r[i].x) std::swap(r[i].x, r[i].y);
		answer += (long long)s[r[i].x] * (n - s[r[i].x]) * r[i].c;
	}
	scanf("%d", &q);
	for (int i = 1; i <= q; i++) {
		int x, w;
		scanf("%d%d", &x, &w);
		answer -= (long long)s[r[x].x] * (n - s[r[x].x]) * r[x].c;
		r[x].c = w;
		answer += (long long)s[r[x].x] * (n - s[r[x].x]) * r[x].c;
		printf("%.10f\n", answer * 6.0 / n / (n - 1));
	}
	return 0;
}
