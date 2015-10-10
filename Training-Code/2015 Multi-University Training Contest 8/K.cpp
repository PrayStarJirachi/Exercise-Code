#include <cstdio>
#include <vector>
#include <cassert>
#include <algorithm>

const int MAXN = 100001;
const int MAXM = 200001;
const int MAXQ = 100001;
const int MAXT = 600001;
const int MAXI = 3000001;
const int Maxlog = 30;

struct Edge{
	int node, next;
}e[MAXM];

struct Query{
	int op, x, y, answer;
}q[MAXQ];

struct Trie{
	int size, c[MAXI][2], s[MAXI];
	int alloc() {
		size++;
		c[size][0] = c[size][1] = 0;
		s[size] = 0;
		return size;
	}
	void clear() {
		size = 0;
		alloc();
	}
	void modify(int x, int d) {
		for (int i = Maxlog, p = 1; i >= 0; i--) {
			int bit = x >> i & 1;
			if (!c[p][bit]) c[p][bit] = alloc();
			p = c[p][bit];
			s[p] += d;
			assert(s[p] >= 0);
		}
	}
	int query(int x) {
		int ret = 0;
		for (int i = Maxlog, p = 1; i >= 0; i--) {
			int bit = x >> i & 1 ^ 1;
			if (c[p][bit] && s[c[p][bit]]) {
				ret |= 1 << i;
				p = c[p][bit];
			}
			else p = c[p][bit ^ 1];
		}
		return ret;
	}
}trie;

struct Tuple{
	int first, second, third;
	Tuple() {}
	Tuple(int first, int second, int third) : first(first), second(second), third(third) {}
};

int T, n, m, t, tot, h[MAXN], oL[MAXN], oR[MAXN], a[MAXN], b[MAXN];
std::vector<Tuple> tree[MAXT];

void update(int &x, int y) {
	if (x < y) x = y;
}

void addedge(int x, int y) {
	t++; e[t] = (Edge){y, h[x]}; h[x] = t;
}

void dfs(int x) {
	oL[x] = ++tot;
	for (int i = h[x]; i; i = e[i].next) {
		dfs(e[i].node);
	}
	oR[x] = tot;
}

void cover(int n, int l, int r, int x, int y, const Tuple &p) {
	if (r < x || l > y) return;
	if (x <= l && r <= y) {
		tree[n].push_back(p);
		return;
	}
	cover(n << 1, l, l + r >> 1, x, y, p);
	cover(n << 1 ^ 1, (l + r >> 1) + 1, r, x, y, p);
}

void cover(int n, int l, int r, int x, const Tuple &p) {
	tree[n].push_back(p);
	if (l == r) return;
	if (x <= (l + r >> 1)) cover(n << 1, l, l + r >> 1, x, p);
	else cover(n << 1 ^ 1, (l + r >> 1) + 1, r, x, p);
}

void travel(int n, int l, int r) {
	trie.clear();
	for (std::vector<Tuple>::iterator it = tree[n].begin(); it != tree[n].end(); it++) {
		if (it -> third) trie.modify(it -> second, it -> third);
		else update(q[it -> first].answer, trie.query(it -> second));
	}
	tree[n].clear();
	if (l == r) return;
	travel(n << 1, l, l + r >> 1);
	travel(n << 1 ^ 1, (l + r >> 1) + 1, r);
}

int main() {
	freopen("K.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		t = tot = 0;
		std::fill(h + 1, h + n + 1, 0);
		for (int i = 2; i <= n; i++) {
			int fa; scanf("%d", &fa);
			addedge(fa, i);
		}
		dfs(1);
		for (int i = 1; i <= n; i++) {
			scanf("%d", a + i);
			b[i] = a[i];
			cover(1, 1, n, oL[i], oR[i], Tuple(i, a[i], 1));
		}
		for (int i = 1; i <= m; i++) {
			scanf("%d%d", &q[i].op, &q[i].x);
			if (q[i].op == 0) {
				scanf("%d", &q[i].y);
				cover(1, 1, n, oL[q[i].x], oR[q[i].x], Tuple(i, a[q[i].x], -1));	
				cover(1, 1, n, oL[q[i].x], oR[q[i].x], Tuple(i, a[q[i].x] = q[i].y, 1));
			}
			else{
				cover(1, 1, n, oL[q[i].x], Tuple(i, a[q[i].x], 0));
				q[i].answer = 0;
			}
		}
		travel(1, 1, n);
		for (int i = 1; i <= m; i++) {
			if (q[i].op == 1) {
				printf("%d\n", q[i].answer);
			}
		}
	}
	return 0;
}
